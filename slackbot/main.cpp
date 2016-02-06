// Copyright (c) 2015 mogemimi. Distributed under the MIT license.

#include "HttpService.h"
#include "SlackClient.h"
#include "iTunesNowPlaying.h"
#include "TerminalHelper.h"
#include "somera/CommandLineParser.h"
#include "somera/StringHelper.h"
#include <iostream>
#include <thread>
#include <fstream>
#include <regex>

using somera::CommandLineParser;

namespace {

void chatNowPlayingMusic(somera::SlackClient & slack, const std::string& channelName)
{
    auto channel = slack.getChannelByName(channelName);
    if (!channel) {
        // error
        std::cout << "Could not find channel." << std::endl;
        return;
    }

    auto track = somera::iTunesNowPlaying::getCurrentTrack();
    if (!track) {
        std::cout << "Your iTunes is not enabled." << std::endl;
        return;
    }

    std::string message;
    message += u8":saxophone: ";
    message += "*" + track->trackName + "*" + "  ";
    message += u8":simple_smile: ";
    message += "_" + track->artistName + "_" + "  ";
    message += u8":cd: ";
    message += "_" + track->albumName + "_";

    slack.chatPostMessage(
        somera::SlackChatPostMessageOptions {
            .channel = channel->id,
            .text = message,
            .as_user =  true,
        },
        [](std::string json) {
            std::cout << json << std::endl;
        });
}

void historyToMarkdown(
    somera::SlackClient & slack,
    const std::string& channelName,
    const std::string& markdownFileName)
{
    auto channel = slack.getChannelByName(channelName);
    if (!channel) {
        // error
        std::cout << "Could not find channel." << std::endl;
        return;
    }

    bool hasMore = true;
    somera::Optional<std::string> latest;

    std::vector<somera::SlackMessage> messages;

    while (hasMore) {
        slack.channelsHistory(
            somera::SlackChannelsHistoryOptions {
                .channel = channel->id,
                .latest = latest,
            },
            [&](somera::SlackHistory history) {
                messages.insert(
                    std::end(messages),
                    history.messages.begin(),
                    history.messages.end());
                hasMore = history.has_more;
                latest = history.messages.back().ts;
                if (hasMore) {
                    std::cout << "read more..." << std::endl;
                } else {
                    std::cout << "completed." << std::endl;
                }
            });
    }

    std::ofstream stream(markdownFileName);

    stream << "# " << channelName << std::endl;
    stream << std::endl;

    std::reverse(std::begin(messages), std::end(messages));
    std::chrono::system_clock::time_point prevTimestamp;
    if (!messages.empty()) {
        prevTimestamp = messages.front().timestamp;
    }

    for (auto & message : messages) {
        if (message.type != "message") {
            continue;
        }
        if (message.subtype == "channel_join") {
            continue;
        }
        if (message.subtype == "file_share") {
            continue;
        }
        if (message.timestamp - prevTimestamp > std::chrono::minutes(5)) {
            stream << "----" << std::endl;
            stream << std::endl;
        }

        // NOTE: Insertion linebreak for markdown's list
        std::regex re(R"((^[^\-][^\n]*\n)(\-\s[^\n]+))");
        auto result = std::regex_replace(message.text, re, "$1\n$2");
        result = somera::StringHelper::replace(result, "&gt;", ">");
        result = somera::StringHelper::replace(result, "&lt;", "<");

        stream << result << std::endl;
        stream << std::endl;
        prevTimestamp = message.timestamp;
    }
}

void setupCommandLineParser(CommandLineParser & parser)
{
    using somera::CommandLineArgumentType::Flag;
    using somera::CommandLineArgumentType::JoinedOrSeparate;
    parser.setUsageText("slackbot [options ...]"
        "\n\n"
        "# ./slackbot -nowplaying -channel general\n"
        "# ./slackbot -history-markdown -channel general\n"
        "# ./slackbot -history-markdown -channel general -file readme.md\n"
        "# ./slackbot -api-test\n"
        "# ./slackbot -auth-test");

    parser.addArgument("-h", Flag, "Display available options");
    parser.addArgument("-help", Flag, "Display available options");
    parser.addArgument("-token-from-env", Flag,
        "Get the access token from environment path");
    parser.addArgument("-token-from-file", Flag,
        "Get the access token from file");

    parser.addArgument("-channel", JoinedOrSeparate, "Post to channel name");
    parser.addArgument("-nowplaying", Flag,
        "Chat now playing music");
    parser.addArgument("-file", JoinedOrSeparate, "Write to file");
    parser.addArgument("-history-markdown", Flag,
        "Write channel history to markdown file");

    parser.addArgument("-api-test", Flag,
        "Call 'api.test' method");
    parser.addArgument("-auth-test", Flag,
        "Call 'auth.test' method");
}

} // unnamed namespace

int main(int argc, char *argv[])
{
    CommandLineParser parser;
    setupCommandLineParser(parser);
    parser.parse(argc, argv);

    if (parser.hasParseError()) {
        std::cerr << parser.getErrorMessage() << std::endl;
        return 1;
    }
    if (parser.exists("-h") || parser.exists("-help")) {
        std::cout << parser.getHelpText() << std::endl;
        return 0;
    }

    std::string token;
    if (parser.exists("-token-from-env")) {
        token = ::getenv("SLACKBOT_ACCESS_TOKEN");
        if (token.empty()) {
            std::printf("Cannot find your access token.");
            return 1;
        }
    }
    else {
    //else if (parser.exists("-token-from-file")) {
        auto path = somera::getHomeDirectory() + "/.slackbot/access_token";
        std::ifstream stream(path);
        if (!stream) {
            std::printf("Cannot find file %s", path.c_str());
            return 1;
        }
        std::getline(stream, token);
        if (token.empty()) {
            std::printf("Invalid token from %s", path.c_str());
            return 1;
        }
    }

    somera::SlackClient slack(token);

    slack.onError([](std::string message) {
        std::cout << message << std::endl;
    });

    slack.login();

    if (parser.exists("-nowplaying")) {
        auto channel = parser.getValue("-channel");
        if (!channel) {
            std::printf("Invalid channel name");
            return 1;
        }
        if (!slack.getChannelByName(*channel)) {
            std::printf("Channot find channel.");
        }
        chatNowPlayingMusic(slack, *channel);
    }
    else if (parser.exists("-history-markdown")) {
        auto channel = parser.getValue("-channel");
        if (!channel) {
            std::printf("Invalid channel name");
            return 1;
        }
        if (!slack.getChannelByName(*channel)) {
            std::printf("Channot find channel.");
        }

        std::string outputFile = *channel + ".md";
        if (auto fileName = parser.getValue("-file")) {
            outputFile = *fileName;
        }
        historyToMarkdown(slack, *channel, outputFile);
    }
    else if (parser.exists("-api-test")) {
        slack.apiTest([](const std::string& json) {
            std::cout << json << std::endl;
        });
    }
    else if (parser.exists("-auth-test")) {
        slack.authTest([](const std::string& json) {
            std::cout << json << std::endl;
        });
    }
    else {
        std::cout << parser.getHelpText() << std::endl;
    }
    return 0;
}
