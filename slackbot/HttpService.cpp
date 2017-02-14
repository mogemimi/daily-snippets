// Copyright (c) 2015 mogemimi. Distributed under the MIT license.

#include "HttpService.h"
#include <algorithm>
#include <cassert>

namespace somera {

HttpRequest::HttpRequest(
    const HttpRequestOptions& options,
    std::function<void(bool error, const std::vector<std::uint8_t>& data)> callbackIn)
    : callback(callbackIn)
    , curl(nullptr)
{
    curl = curl_easy_init();
    if (curl == nullptr) {
        throw std::runtime_error("curl_easy_init() failed");
    }

    std::string uri;
    if (options.hostname) {
        uri += *options.hostname;
    }
    if (options.path) {
        uri += *options.path;
    }
    if (!uri.empty()) {
        curl_easy_setopt(curl, CURLOPT_URL, uri.c_str());
    }

    if (options.postFields && !options.postFields->empty()) {
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, options.postFields->c_str());
    }
    if (options.agent && !options.agent->empty()) {
        curl_easy_setopt(curl, CURLOPT_USERAGENT, options.agent->c_str());
    }
    if (options.port) {
        curl_easy_setopt(curl, CURLOPT_PORT, *options.port);
    }
    if (options.method) {
        if (*options.method == HttpRequestMethod::POST) {
            curl_easy_setopt(curl, CURLOPT_POST, 1);
        }
        else if (*options.method == HttpRequestMethod::GET) {
            curl_easy_setopt(curl, CURLOPT_HTTPGET, 1);
        }
    }
    if (!options.headers.empty()) {
        // TODO: Please add implementation.
    }

    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, this);
//    curl_easy_setopt(curl, CURLOPT_HEADER, 0L);
//    curl_easy_setopt(curl, CURLOPT_VERBOSE, 0L);
}

HttpRequest::HttpRequest(
    const std::string& uri,
    std::function<void(bool error, const std::vector<std::uint8_t>& data)> callbackIn)
    : callback(callbackIn)
    , curl(nullptr)
{
    curl = curl_easy_init();
    if (curl == nullptr) {
        throw std::runtime_error("curl_easy_init() failed");
    }
    curl_easy_setopt(curl, CURLOPT_URL, uri.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, this);
}

HttpRequest::~HttpRequest()
{
    if (curl != nullptr) {
        curl_easy_cleanup(curl);
        curl = nullptr;
    }
}

CURL* HttpRequest::getCurl() const
{
    return curl;
}

void HttpRequest::setTimeout(const std::chrono::seconds& timeout)
{
    if (timeout >= timeout.zero()) {
        curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, timeout.count());
    }
}

size_t HttpRequest::writeCallback(
    void const* contents,
    size_t size,
    size_t nmemb,
    void* userPointer)
{
    auto userData = reinterpret_cast<HttpRequest*>(userPointer);
    auto & blob = userData->blob;
    const auto inputSize = size * nmemb;
    blob.resize(blob.size() + inputSize);
    std::memcpy(blob.data() + blob.size() - inputSize, contents, inputSize);
    return inputSize;
}

void HttpRequest::onCompleted()
{
    if (callback) {
        callback(false, blob);
    }
}

void HttpRequest::onError()
{
    if (callback) {
        callback(true, {});
    }
}

HttpService::HttpService()
    : multiHandle(nullptr)
    , timeout(decltype(timeout)::zero())
{
    multiHandle = curl_multi_init();
}

HttpService::~HttpService()
{
    if (multiHandle != nullptr) {
        curl_multi_cleanup(multiHandle);
        multiHandle = nullptr;
    }
}

void HttpService::poll()
{
    assert(multiHandle != nullptr);

    int runningCount = 0;
    curl_multi_perform(multiHandle, &runningCount);

    int messageCount = 0;
    CURLMsg* message = nullptr;

    while ((message = curl_multi_info_read(multiHandle, &messageCount)) != nullptr)
    {
        CURL* curl = message->easy_handle;

        curl_multi_remove_handle(multiHandle, curl);

        auto pair = sessions.find(curl);
        assert(pair != std::end(sessions));

        if (pair != std::end(sessions)) {
            auto request = std::move(pair->second);
            if (message->msg != CURLMSG_DONE) {
                //std::fprintf(stderr, "CURL error in %s, %d\n", __FILE__, __LINE__);
                request->onError();
            }
            else if (message->data.result != CURLE_OK) {
                //std::fprintf(stderr, "CURL error in %s, %d\n", __FILE__, __LINE__);
                request->onError();
            }
            else {
                request->onCompleted();
            }
            sessions.erase(pair);
        }
    }
}

void HttpService::waitAll()
{
    for (;;) {
        this->poll();
        if (this->empty()) {
            break;
        }

//        {
//            int n = 0;
//            curl_multi_wait(multiHandle, nullptr, 0, 30 * 1000, &n);
//        }
        std::this_thread::sleep_for(std::chrono::microseconds(500));
    }
}

void HttpService::request(
    const HttpRequestOptions& options,
    std::function<void(bool, const std::vector<std::uint8_t>&)> callback)
{
    auto request = std::make_unique<HttpRequest>(options, callback);
    if (timeout > decltype(timeout)::zero()) {
        request->setTimeout(timeout);
    }

    auto result = curl_multi_add_handle(multiHandle, request->getCurl());
    if (result != CURLE_OK) {
        throw std::runtime_error("curl_multi_add_handle() failed");
    }
    sessions.emplace(request->getCurl(), std::move(request));
}

void HttpService::get(
    const std::string& uri,
    std::function<void(bool, const std::vector<std::uint8_t>&)> callback)
{
    auto request = std::make_unique<HttpRequest>(uri, callback);
    if (timeout > decltype(timeout)::zero()) {
        request->setTimeout(timeout);
    }

    auto result = curl_multi_add_handle(multiHandle, request->getCurl());
    if (result != CURLE_OK) {
        throw std::runtime_error("curl_multi_add_handle() failed");
    }
    sessions.emplace(request->getCurl(), std::move(request));
}

bool HttpService::empty() const
{
    return sessions.size() <= 0;
}

void HttpService::setTimeout(const std::chrono::seconds& timeoutIn)
{
    assert(timeout >= timeout.zero());
    this->timeout = timeoutIn;
}

} // namespace somera
