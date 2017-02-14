// Copyright (c) 2017 mogemimi. Distributed under the MIT license.

#include "StringHelper.h"
#include "GitHubClient.h"
#include <iostream>
#include <fstream>
#include <array>
#include <unordered_map>
#include <experimental/optional>
#include <sstream>
#include <cassert>

int main(int argc, char *argv[])
{
    somera::GitHubClient client;

    client.onError([](std::string message) {
        std::cout << message << std::endl;
    });

    const std::vector<int> pullRequestNumbers = {
        17334,
        17333
    };

    int additions = 0;
    int deletions = 0;

    for (auto pullRequestNumber : pullRequestNumbers) {
        client.getPullRequest("cocos2d", "cocos2d-x", pullRequestNumber, [&](somera::GitHubPullRequest pr) {
            std::cout << pr.url << std::endl;
            std::cout << pr.title << std::endl;
            std::cout
                << "state: " << pr.state
                << "  "
                << "+" << pr.additions
                << " "
                << "-" << pr.deletions
                << "  "
                << pr.commits << " commits"
                << std::endl;
            std::cout << "----" << std::endl;
            additions += pr.additions;
            deletions += pr.deletions;
        });
    }

    std::cout << "Additions: " << additions << std::endl;
    std::cout << "Deletions: " << deletions << std::endl;

    return 0;
}
