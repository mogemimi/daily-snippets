// Copyright (c) 2015 mogemimi. Distributed under the MIT license.

#pragma once

#include "somera/Optional.h"
extern "C" {
#include <curl/curl.h>
}
#include <chrono>
#include <cstdint>
#include <functional>
#include <map>
#include <string>
#include <thread>
#include <type_traits>
#include <vector>

namespace somera {

enum class HttpRequestMethod {
    HEAD,
    POST,
    GET,
    PUT,
    DELETE,
};

struct HttpRequestOptions {
    Optional<std::string> hostname;
    Optional<std::string> path;
    Optional<int> port;
    Optional<HttpRequestMethod> method;
    Optional<std::string> postFields;
    Optional<std::string> agent;
    std::map<std::string, std::string> headers;
};

class HttpRequest {
private:
    std::function<void(bool error, const std::vector<std::uint8_t>& data)> callback;
    std::vector<std::uint8_t> blob;
    CURL* curl;

public:
    HttpRequest(
        const std::string& url,
        std::function<void(bool error, const std::vector<std::uint8_t>& data)> callback);

    HttpRequest(
        const HttpRequestOptions& options,
        std::function<void(bool error, const std::vector<std::uint8_t>& data)> callback);

    ~HttpRequest();

    HttpRequest(HttpRequest const&) = delete;
    HttpRequest & operator=(HttpRequest const&) = delete;

    CURL* getCurl() const;
    void onCompleted();
    void onError();

    void setTimeout(const std::chrono::seconds& timeout);

private:
    static size_t writeCallback(
        void const* contents,
        size_t size,
        size_t nmemb,
        void* userPointer);
};

class HttpService {
private:
    CURLM* multiHandle;
    std::map<CURL*, std::unique_ptr<HttpRequest>> sessions;
    std::chrono::seconds timeout;

public:
    HttpService();
    ~HttpService();

    HttpService(const HttpService&) = delete;
    HttpService & operator=(const HttpService&) = delete;

    void setTimeout(const std::chrono::seconds& timeout);

    void poll();

    void waitAll();

    void request(
        const HttpRequestOptions& options,
        std::function<void(bool, const std::vector<std::uint8_t>&)> callback);

    void get(
        const std::string& uri,
        std::function<void(bool, const std::vector<std::uint8_t>&)> callback);

    bool empty() const;
};

} // namespace somera
