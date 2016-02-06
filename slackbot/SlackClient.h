// Copyright (c) 2015 mogemimi. Distributed under the MIT license.

#include "somera/Optional.h"
#include "HttpService.h"
#include <functional>
#include <string>
#include <vector>
#include <map>
#include <chrono>

namespace somera {

//struct SlackTopic {
//    std::string value;
//    std::string creator;
//    int last_set;
//};
//
//struct SlackPurpose {
//    std::string value;
//    std::string creator;
//    int last_set;
//};

struct SlackChannel {
//    std::vector<std::string> members;
//    SlackTopic topic;
//    SlackPurpose purpose;
    std::string id;
    std::string name;
    int created;
    std::string creator;
    bool is_archived;
    bool is_general;
    bool is_member;
};

struct SlackMessage {
    std::string type;
    std::string channel;
    std::string user;
    std::string text;
    std::string subtype;
    std::string ts;
    std::chrono::system_clock::time_point timestamp;
};

struct SlackHistory {
    std::vector<SlackMessage> messages;
    std::string latest;
    bool has_more;
};

struct SlackChatPostMessageOptions {
    std::string channel;
    std::string text;
    Optional<std::string> username;
    Optional<std::string> icon_url;
    Optional<std::string> icon_emoji;
    Optional<bool> as_user;
};

struct SlackChannelsHistoryOptions {
    std::string channel;
    Optional<std::string> latest;
    Optional<std::string> oldest;
    Optional<int> count;
};

class SlackClient final {
private:
    somera::HttpService http;
    std::string token;
    std::function<void(const std::string&)> errorCallback;
    std::vector<SlackChannel> channels;

public:
    explicit SlackClient(const std::string& token);

    void login();

    Optional<SlackChannel> getChannelByID(const std::string& id);

    Optional<SlackChannel> getChannelByName(const std::string& name);

    ///@brief See https://api.slack.com/methods/api.test
    ///@example
    /// ```
    /// slack.apiTest([](std::string json) {
    ///     std::cout << json << std::endl;
    /// });
    /// ```
    void apiTest(std::function<void(std::string)> callback);

    ///@brief See https://api.slack.com/methods/auth.test
    ///@example
    /// ```
    /// slack.authTest([](std::string json) {
    ///     std::cout << json << std::endl;
    /// });
    /// ```
    void authTest(std::function<void(std::string)> callback);

    /// See https://api.slack.com/methods/channels.history
    void channelsHistory(
        const SlackChannelsHistoryOptions& options,
        std::function<void(SlackHistory)> callback);

    /// See https://api.slack.com/methods/chat.postMessage
    void chatPostMessage(
        const SlackChatPostMessageOptions& options,
        std::function<void(std::string)> callback);

    void onError(std::function<void(std::string)> callback);

private:
    void apiCall(
        const std::string& method,
        std::map<std::string, std::string> && params,
        std::function<void(std::string)> && callback);

    void emitError(const std::string& errorMessage);
};

} // namespace somera
