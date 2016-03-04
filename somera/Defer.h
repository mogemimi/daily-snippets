// Copyright (c) 2015 mogemimi. Distributed under the MIT license.

#pragma once

#include <functional>
#include <utility>

namespace somera {

class Defer final {
    std::function<void()> callback;
public:
    Defer() = delete;
    Defer(const Defer&) = delete;
    Defer(Defer && other) = delete;
    Defer & operator=(const Defer&) = delete;
    Defer & operator=(Defer && other) = delete;

    explicit Defer(std::function<void()> && func)
        : callback(std::move(func))
    {}

    explicit Defer(const std::function<void()>& func)
        : callback(func)
    {}

    ~Defer()
    {
        if (callback) {
            callback();
        }
    }
};

} // namespace somera
