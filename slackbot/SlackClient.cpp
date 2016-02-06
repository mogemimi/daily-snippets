// Copyright (c) 2015 mogemimi. Distributed under the MIT license.

#include "SlackClient.h"
#include "HttpUtility.h"
#include <rapidjson/document.h>
#include <cstdint>
#include <sstream>
#include <utility>

namespace somera {
namespace {

void fromJson(std::string& output, const rapidjson::Value& value)
{
    if (value.IsString()) {
        output = value.GetString();
    }
}

void fromJson(int& output, const rapidjson::Value& value)
{
    if (value.IsInt()) {
        output = value.GetInt();
    }
}

void fromJson(bool& output, const rapidjson::Value& value)
{
    if (value.IsBool()) {
        output = value.GetBool();
    }
}

template <typename T>
void fromJsonMember(T& output, const std::string& name, const rapidjson::Value& object)
{
    assert(object.IsObject());
    assert(!name.empty());
    if (object.HasMember(name.c_str())) {
        fromJson(output, object[name.c_str()]);
    }
}

template <typename Container, typename Func, typename T>
auto find(const Container& container, Func thunk, const T& value)
    -> typename Container::const_iterator
{
    return std::find_if(std::begin(container), std::end(container),
            [&](const typename Container::value_type& v) {
                return thunk(v) == value;
            });
}

} // namespace

SlackClient::SlackClient(const std::string& tokenIn)
    : token(tokenIn)
{
    http.setTimeout(std::chrono::seconds(60));
}

void SlackClient::login()
{
    // NOTE: Please see https://api.slack.com/methods/channels.list
    apiCall("channels.list", {}, [this](const std::string& json) {
        rapidjson::Document doc;
        doc.Parse(json.c_str());

        if (doc.HasParseError()) {
            this->emitError("Failed to parse JSON");
            return;
        }
        if (!doc.IsObject()
            || !doc.HasMember("ok") || !doc["ok"].IsBool()
            || !doc.HasMember("channels") || !doc["channels"].IsArray()
            ) {
            this->emitError("Invalid JSON");
            return;
        }
        if (!doc["ok"].GetBool()) {
            this->emitError("Invalid JSON");
            return;
        }

        auto & channelsObject = doc["channels"];
        for (auto c = channelsObject.Begin(); c != channelsObject.End(); ++c) {
            if (!c->IsObject()) {
                this->emitError("Invalid JSON");
                break;
            }
            SlackChannel channel;
            fromJsonMember(channel.id, "id", *c);
            fromJsonMember(channel.name, "name", *c);
            fromJsonMember(channel.creator, "creator", *c);
            fromJsonMember(channel.created, "created", *c);
            fromJsonMember(channel.is_archived, "is_archived", *c);
            fromJsonMember(channel.is_general, "is_general", *c);
            fromJsonMember(channel.is_member, "is_member", *c);
            channels.push_back(std::move(channel));
        }
    });
}

Optional<SlackChannel> SlackClient::getChannelByID(const std::string& id)
{
    auto channel = find(channels, [](const SlackChannel& c){ return c.id; }, id);
    if (channel != std::end(channels)) {
        return *channel;
    }
    return NullOpt;
}

Optional<SlackChannel> SlackClient::getChannelByName(const std::string& name)
{
    auto channel = find(channels, [](const SlackChannel& c){ return c.name; }, name);
    if (channel != std::end(channels)) {
        return *channel;
    }
    return NullOpt;
}

void SlackClient::apiCall(
    const std::string& method,
    std::map<std::string, std::string> && paramsIn,
    std::function<void(std::string)> && callbackIn)
{
    auto params = std::move(paramsIn);

    assert(!token.empty());
    params["token"] = token;

    const auto postData = HttpUtility::stringify(params);

    somera::HttpRequestOptions options;
    options.hostname = "https://slack.com";
    options.path = "/api/" + method;
    options.postFields = postData;
    options.method = HttpRequestMethod::POST;

    http.request(options,
        [callback = std::move(callbackIn), this](bool error, const std::vector<std::uint8_t>& blob) {
            if (error) {
                this->emitError("Failed to call 'api.test'");
                return;
            }
            if (callback) {
                std::string json(reinterpret_cast<const char*>(blob.data()), blob.size());
                callback(json);
            }
        });

    http.waitAll();
}

void SlackClient::onError(std::function<void(std::string)> callback)
{
    errorCallback = callback;
}

void SlackClient::emitError(const std::string& errorMessage)
{
    if (errorCallback) {
        errorCallback(errorMessage);
    }
}

void SlackClient::apiTest(std::function<void(std::string)> callback)
{
    apiCall("api.test", {}, std::move(callback));
}

void SlackClient::authTest(std::function<void(std::string)> callback)
{
    apiCall("auth.test", {}, std::move(callback));
}

void SlackClient::chatPostMessage(
    const SlackChatPostMessageOptions& options,
    std::function<void(std::string)> callback)
{
    std::map<std::string, std::string> params;
    params["channel"] = options.channel;
    params["text"] = options.text;

    if (options.username) {
        params["username"] = *options.username;
    }
    if (options.icon_url) {
        params["icon_url"] = *options.icon_url;
    }
    if (options.icon_emoji) {
        params["icon_emoji"] = *options.icon_emoji;
    }
    if (options.as_user && *options.as_user) {
        params["as_user"] = "true";
    }
    apiCall("chat.postMessage", std::move(params), std::move(callback));
}

void SlackClient::channelsHistory(
    const SlackChannelsHistoryOptions& options,
    std::function<void(SlackHistory)> callbackIn)
{
    std::map<std::string, std::string> params;
    params["channel"] = options.channel;
    if (options.count) {
        params["channel"] = std::to_string(*options.count);
    }
    if (options.latest) {
        params["latest"] = *options.latest;
    }
    if (options.oldest) {
        params["oldest"] = *options.oldest;
    }

    auto callbackWrapper = [callback = std::move(callbackIn), this](const std::string& json) {
        rapidjson::Document doc;
        doc.Parse(json.c_str());

        if (doc.HasParseError()) {
            this->emitError("Failed to parse JSON");
            return;
        }

        if (!doc.IsObject()
            || !doc.HasMember("ok") || !doc["ok"].IsBool()) {
            this->emitError("Invalid JSON");
            return;
        }

        if (!doc["ok"].GetBool()) {
            std::string errorMessage = "Failed to call channelsHistory";
            if (doc.HasMember("error") && doc["error"].IsString()) {
                errorMessage = doc["error"].GetString();
            }
            this->emitError(errorMessage);
            return;
        }

        SlackHistory history;
        history.has_more = false;
        fromJsonMember(history.latest, "latest", doc);
        fromJsonMember(history.has_more, "has_more", doc);

        if (doc.HasMember("messages") && doc["messages"].IsArray()) {
            auto & messagesObject = doc["messages"];
            for (auto iter = messagesObject.Begin(); iter != messagesObject.End(); ++iter) {
                const auto& channelObject = (*iter);
                if (!channelObject.IsObject()) {
                    // error
                    std::fprintf(stderr, "JSON parse error in %s, %d\n", __FILE__, __LINE__);
                    continue;
                }

                SlackMessage message;
                fromJsonMember(message.type, "type", channelObject);
                fromJsonMember(message.user, "user", channelObject);
                fromJsonMember(message.text, "text", channelObject);
                fromJsonMember(message.channel, "channel", channelObject);
                fromJsonMember(message.subtype, "subtype", channelObject);
                fromJsonMember(message.ts, "ts", channelObject);
                using std::chrono::system_clock;
                message.timestamp = system_clock::from_time_t(::atoi(message.ts.c_str()));

                history.messages.push_back(std::move(message));
            }
        }

        if (callback) {
            callback(std::move(history));
        }
    };

    apiCall("channels.history", std::move(params), std::move(callbackWrapper));
}

} // namespace somera
