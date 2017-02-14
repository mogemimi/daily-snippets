// Copyright (c) 2017 mogemimi. Distributed under the MIT license.

#include "somera/Optional.h"
#include "HttpService.h"
#include <functional>
#include <string>
#include <vector>
#include <map>
#include <chrono>

namespace somera {

// NOTE: https://developer.github.com/v3/pulls/#get-a-single-pull-request
struct GitHubPullRequest {
    std::string url;
    int id;
    std::string html_url;
    std::string diff_url;
    std::string patch_url;
    std::string issue_url;
    int number;
    std::string state;
    bool locked;
    std::string title;
    
    std::string body;
    std::string created_at;
    std::string updated_at;
    std::string closed_at;
    std::string merged_at;
    std::string merge_commit_sha;

    std::string commits_url;
    std::string review_comments_url;
    std::string review_comment_url;
    std::string comments_url;
    std::string statuses_url;

    bool merged = false;

    int comments = 0;
    int review_comments = 0;
    bool maintainer_can_modify = false;
    int commits = 0;
    int additions = 0;
    int deletions = 0;
    int changed_files = 0;
};

class GitHubClient final {
private:
    somera::HttpService http;
    std::function<void(const std::string&)> errorCallback;

public:
    GitHubClient();

    void onError(std::function<void(std::string)> callback);

    void apiTest(std::function<void(std::string)> callback);

    // NOTE: https://developer.github.com/v3/pulls/#get-a-single-pull-request
    void getPullRequest(
        std::string repositoryOwner,
        std::string repositoryName,
        int pullRequestNumber,
        std::function<void(GitHubPullRequest)> callback);

private:
    void apiCall(
        const std::string& method,
        std::map<std::string, std::string> && params,
        std::function<void(std::string)> && callback,
        HttpRequestMethod httpVerbs);

    void emitError(const std::string& errorMessage);
};

} // namespace somera
