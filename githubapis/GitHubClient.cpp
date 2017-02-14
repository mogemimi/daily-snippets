// Copyright (c) 2015 mogemimi. Distributed under the MIT license.

#include "GitHubClient.h"
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

GitHubClient::GitHubClient()
{
    http.setTimeout(std::chrono::seconds(60));
}

void GitHubClient::apiCall(
    const std::string& method,
    std::map<std::string, std::string> && paramsIn,
    std::function<void(std::string)> && callbackIn,
    HttpRequestMethod httpVerbs)
{
    auto params = std::move(paramsIn);

    const auto postData = HttpUtility::stringify(params);

    somera::HttpRequestOptions options;
    options.hostname = "https://api.github.com";
    options.path = "/" + method;
    options.postFields = postData;
    options.method = httpVerbs;
    options.agent = "application/vnd.github.v3+json";

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

void GitHubClient::onError(std::function<void(std::string)> callback)
{
    errorCallback = callback;
}

void GitHubClient::emitError(const std::string& errorMessage)
{
    if (errorCallback) {
        errorCallback(errorMessage);
    }
}

void GitHubClient::apiTest(std::function<void(std::string)> callback)
{
    apiCall(
        "repos/vmg/redcarpet/issues",
        {
            {"state", "closed"}
        },
        std::move(callback),
        HttpRequestMethod::GET);
}

void GitHubClient::getPullRequest(
    std::string repositoryOwner,
    std::string repositoryName,
    int pullRequestNumber,
    std::function<void(GitHubPullRequest)> callbackIn)
{
    auto method = "repos/" + repositoryOwner + "/" + repositoryName + "/pulls/" + std::to_string(pullRequestNumber);

    auto callbackWrapper = [callback = std::move(callbackIn), this](const std::string& json) {
        rapidjson::Document doc;
        doc.Parse(json.c_str());

        if (doc.HasParseError()) {
            this->emitError("Failed to parse JSON");
            return;
        }

        if (!doc.IsObject()) {
            this->emitError("Invalid JSON");
            return;
        }

        GitHubPullRequest pullRequest;

        fromJsonMember(pullRequest.url, "url", doc);
        fromJsonMember(pullRequest.id, "id", doc);
        fromJsonMember(pullRequest.html_url, "html_url", doc);
        fromJsonMember(pullRequest.diff_url, "diff_url", doc);
        fromJsonMember(pullRequest.patch_url, "patch_url", doc);
        fromJsonMember(pullRequest.issue_url, "issue_url", doc);
        fromJsonMember(pullRequest.number, "number", doc);
        fromJsonMember(pullRequest.state, "state", doc);
        fromJsonMember(pullRequest.locked, "locked", doc);
        fromJsonMember(pullRequest.title, "title", doc);
        fromJsonMember(pullRequest.body, "body", doc);
        fromJsonMember(pullRequest.created_at, "created_at", doc);
        fromJsonMember(pullRequest.updated_at, "updated_at", doc);
        fromJsonMember(pullRequest.closed_at, "closed_at", doc);
        fromJsonMember(pullRequest.merged_at, "merged_at", doc);
        fromJsonMember(pullRequest.merge_commit_sha, "memerge_commit_sharged", doc);
        fromJsonMember(pullRequest.merged, "commits_url", doc);
        fromJsonMember(pullRequest.merged, "review_comments_url", doc);
        fromJsonMember(pullRequest.merged, "review_comment_url", doc);
        fromJsonMember(pullRequest.merged, "comments_url", doc);
        fromJsonMember(pullRequest.merged, "statuses_url", doc);
        fromJsonMember(pullRequest.merged, "merged", doc);
        fromJsonMember(pullRequest.commits, "commits", doc);
        fromJsonMember(pullRequest.comments, "comments", doc);
        fromJsonMember(pullRequest.review_comments, "review_comments", doc);
        fromJsonMember(pullRequest.maintainer_can_modify, "maintainer_can_modify", doc);
        fromJsonMember(pullRequest.additions, "additions", doc);
        fromJsonMember(pullRequest.deletions, "deletions", doc);
        fromJsonMember(pullRequest.changed_files, "changed_files", doc);

        if (callback) {
            callback(std::move(pullRequest));
        }
    };

    apiCall(
        method,
        {},
        callbackWrapper,
        HttpRequestMethod::GET);
}

} // namespace somera
