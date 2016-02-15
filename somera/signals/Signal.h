// Copyright (c) 2013-2016 mogemimi. Distributed under the MIT license.

#pragma once

#include "detail/ForwardDeclarations.h"
#include "detail/SignalBody.h"
#include <cassert>
#include <memory>
#include <functional>
#include <utility>

namespace somera {

template <typename Function>
class Signal;

template <typename...Args>
class Signal<void(Args...)> final {
public:
    Signal();
    Signal(const Signal&) = delete;
    Signal(Signal &&) = default;
    Signal & operator=(const Signal&) = delete;
    Signal & operator=(Signal &&) = default;

    Connection Connect(const std::function<void(Args...)>& slot);

    Connection Connect(std::function<void(Args...)> && slot);

    void operator()(Args &&... args);

    std::size_t InvocationCount() const;

private:
    using SignalBody = detail::signals::SignalBody<void(Args...)>;
    std::shared_ptr<SignalBody> body;
};

template <typename...Args>
Signal<void(Args...)>::Signal()
    : body(std::make_shared<SignalBody>())
{}

template <typename...Args>
Connection
Signal<void(Args...)>::Connect(const std::function<void(Args...)>& slot)
{
    assert(slot);
    assert(body);
    return Connection{body->Connect(slot)};
}

template <typename...Args>
Connection
Signal<void(Args...)>::Connect(std::function<void(Args...)> && slot)
{
    assert(slot);
    assert(body);
    return Connection{body->Connect(std::move(slot))};
}

template <typename...Args>
void Signal<void(Args...)>::operator()(Args &&... args)
{
    assert(body);
    body->operator()(std::forward<Args>(args)...);
}

template <typename...Args>
std::size_t Signal<void(Args...)>::InvocationCount() const
{
    return body->InvocationCount();
}

} // namespace somera
