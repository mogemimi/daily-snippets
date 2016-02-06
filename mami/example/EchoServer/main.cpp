// Copyright (c) 2016 mogemimi. Distributed under the MIT license.

#include "mami/IOService.h"
#include "mami/Socket.h"
#include "somera/signals/EventQueue.h"
#include "somera/CommandLineParser.h"
#include "somera/StringHelper.h"
#include <iostream>
#include <thread>

using namespace somera;

namespace {

void SetupCommandLineParser(CommandLineParser & parser)
{
    using somera::CommandLineArgumentType::Flag;
    using somera::CommandLineArgumentType::JoinedOrSeparate;
    parser.setUsageText("mami [options ...]");
    parser.addArgument("-h", Flag, "Display available options");
    parser.addArgument("-help", Flag, "Display available options");
    parser.addArgument("-s", Flag, "server");
    parser.addArgument("-c", Flag, "client");
    parser.addArgument("port", JoinedOrSeparate, "port number (default is 8000)");
}

void Log(const std::string& text)
{
    std::puts(text.c_str());
}

void RunServer(uint16_t port)
{
    IOService service;

    Server server(service);
    server.SetErrorListener([](const Error& error) {
        Log("Error: " + error.What());
    });
    server.SetCloseListener([](std::shared_ptr<Socket> client) {
        Log(StringHelper::format("Close: client = { fd : %d }", client->GetHandle()));
    });
    server.Listen(EndPoint::CreateFromV4("localhost", port), 5, [](std::shared_ptr<Socket> client) {
        Log(StringHelper::format("Listen: client = { fd : %d }", client->GetHandle()));
    });
    server.Read([](std::shared_ptr<Socket> client, const ArrayView<uint8_t>& view) {
        std::string text(reinterpret_cast<const char*>(view.data), view.size);
        text = StringHelper::trimRight(text, '\n');
        text = StringHelper::trimRight(text, '\r');
        text = StringHelper::trimRight(text, '\n');

        Log(StringHelper::format(
            "Read: client = { fd : %d, result = %s }",
            client->GetHandle(),
            text.c_str()));
    });

    Log("Run");
    service.Run();
}

void RunClient(uint16_t port)
{
    IOService service;
    EventQueue eventQueue;

    Socket socket(service);
    socket.SetTimeout(std::chrono::seconds(500), [](Socket &) {
        Log("Timeout.");
    });
    socket.SetErrorListener([&socket](Socket &, const Error& error) {
        Log("Error: " + error.What());
        socket.Close();
    });
    socket.SetCloseListener([](Socket&) {
        Log("Close.");
    });
    socket.Connect(EndPoint::CreateFromV4("localhost", port),
        [&eventQueue, &service, &socket](Socket &) {
        Log("Connected.");
        eventQueue.Connect([&socket, &service](const Any& event) {
            if (!event.is<std::string>()) {
                return;
            }
            auto text = event.as<std::string>();
            auto view = MakeArrayView(text.data(), text.size());
            socket.Write(CastArrayView<uint8_t const>(view));

            if (StringHelper::startWith(text, "exit")) {
                socket.Close();
                service.ExitLoop();
            }
        });
    });
    socket.Read([&socket](Socket &, const ArrayView<uint8_t>& view) {
        std::string text(reinterpret_cast<const char*>(view.data), view.size);
        text = StringHelper::trimRight(text, '\n');
        text = StringHelper::trimRight(text, '\r');
        text = StringHelper::trimRight(text, '\n');

        Log(StringHelper::format(
            "Read: server = { fd : %d, result = %s }",
            socket.GetHandle(),
            text.c_str()));
    });

    std::thread keyboardWorker([&] {
        std::this_thread::sleep_for(std::chrono::seconds(5));
        bool exitLoop = false;
        while (!exitLoop) {
            std::string text;
            std::cin >> text;
            if (StringHelper::startWith(text, "exit")) {
                exitLoop = true;
            }
            eventQueue.Enqueue<std::string>(std::move(text));
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    });

    ScopedConnection conn = service.ScheduleTask([&] {
        eventQueue.Emit();
    });

    Log("Run");
    service.Run();
    keyboardWorker.join();
}

} // unnamed namespace

int main(int argc, char *argv[])
{
    somera::CommandLineParser parser;
    SetupCommandLineParser(parser);
    parser.parse(argc, argv);

    if (parser.hasParseError()) {
        std::cerr << parser.getErrorMessage() << std::endl;
        return 1;
    }
    if (parser.exists("-h") || parser.exists("-help")) {
        std::cout << parser.getHelpText() << std::endl;
        return 0;
    }

    uint16_t port = 8000;
    if (auto p = parser.getValue("port")) {
        try {
            port = static_cast<uint16_t>(std::stoi(*p));
        }
        catch (const std::invalid_argument&) {
            return 1;
        }
    }
    if (parser.exists("-s")) {
        RunServer(port);
    }
    else if (parser.exists("-c")) {
        RunClient(port);
    }

    Log("Done");
    return 0;
}
