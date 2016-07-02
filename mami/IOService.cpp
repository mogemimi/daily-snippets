// Copyright (c) 2016 mogemimi. Distributed under the MIT license.

#include "IOService.h"
#include "ContainerAlgorithm.h"
#include <cassert>
#include <utility>
#include <thread>

namespace somera {
namespace {

// MARK: ConnectionEventLoop

class ConnectionEventLoop final : public detail::ConnectionBody {
public:
    ConnectionEventLoop(IOService* serviceIn, int connectionIdIn)
        : service(serviceIn)
        , connectionId(connectionIdIn)
    {
    }

    void Disconnect() override
    {
        if (service == nullptr) {
            return;
        }
        service->Disconnect(connectionId);
        service = nullptr;
        connectionId = 0;
    }

    bool Valid() const noexcept override
    {
        return (service != nullptr) && service->IsConnected(connectionId);
    }

    std::unique_ptr<ConnectionBody> DeepCopy() const override
    {
        auto copy = std::make_unique<ConnectionEventLoop>(service, connectionId);
        return std::move(copy);
    }

private:
    IOService* service = nullptr;
    int connectionId = 0;
};

} // unnamed namespace

// MARK: IOService

void IOService::Run()
{
    while (!exitRequest) {
        Step();

        // NOTE: I want to suppress energy impact if possible.
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

void IOService::Step()
{
    for (auto & listener : listeners) {
        if (Find(removedListeners, listener.id) != std::end(removedListeners)) {
            listener.needToRemove = true;
            continue;
        }

        // NOTE: Execute listener's callback
        if (listener.callback) {
            listener.callback();
        }
    }
    // TODO: mutex for addedListeners
    if (!addedListeners.empty()) {
        // NOTE: Add listener to listeners container
        std::vector<Listener> temp;
        std::swap(temp, addedListeners);
        for (auto & listener : temp) {
            listeners.push_back(std::move(listener));
        }
    }
    // TODO: mutex for removedListeners
    if (!removedListeners.empty()) {
        // NOTE: Remove listener from listeners container
        std::vector<int> temp;
        std::swap(temp, removedListeners);
        EraseIf(listeners, [&temp](const Listener& listener) {
            return listener.needToRemove
                || (Find(temp, listener.id) != std::end(temp));
        });
    }
}

void IOService::ExitLoop()
{
    exitRequest = true;
}

Connection IOService::ScheduleTask(std::function<void()> func)
{
    if (!func) {
        return {};
    }
    Listener listener;
    listener.callback = std::move(func);
    listener.id = this->nextListenersId;
    nextListenersId++;

    addedListeners.push_back(std::move(listener));

    auto body = std::make_unique<ConnectionEventLoop>(this, listener.id);
    Connection connection(std::move(body));
    return connection;
}

bool IOService::IsConnected(int connectionId) const
{
    if (Find(removedListeners, connectionId) != std::end(removedListeners)) {
        return false;
    }
    const auto equal = [&connectionId](const Listener& listener)-> bool {
        return listener.id == connectionId;
    };
    if (FindIf(listeners, equal) != std::end(listeners)) {
        return true;
    }
    if (FindIf(addedListeners, equal) != std::end(addedListeners)) {
        return true;
    }
    return false;
}

void IOService::Disconnect(int connectionId)
{
    removedListeners.push_back(connectionId);
}

} // namespace somera
