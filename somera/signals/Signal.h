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

template <typename...Arguments>
class Signal<void(Arguments...)> final {
public:
    Signal();
    Signal(Signal const&) = delete;
    Signal(Signal &&) = default;
    Signal & operator=(Signal const&) = delete;
    Signal & operator=(Signal &&) = default;

    Connection Connect(std::function<void(Arguments...)> const& slot);

    Connection Connect(std::function<void(Arguments...)> && slot);

    void operator()(Arguments... arguments);

    std::size_t InvocationCount() const;

private:
    using SignalBody = detail::signals::SignalBody<void(Arguments...)>;
    std::shared_ptr<SignalBody> body;
};

template <typename...Arguments>
Signal<void(Arguments...)>::Signal()
    : body(std::make_shared<SignalBody>())
{}

template <typename...Arguments>
Connection Signal<void(Arguments...)>::Connect(
    std::function<void(Arguments...)> const& slot)
{
    assert(slot);
    assert(body);
    return Connection{body->Connect(slot)};
}

template <typename...Arguments>
Connection Signal<void(Arguments...)>::Connect(
    std::function<void(Arguments...)> && slot)
{
    assert(slot);
    assert(body);
    return Connection{body->Connect(std::move(slot))};
}

template <typename...Arguments>
void Signal<void(Arguments...)>::operator()(Arguments... arguments)
{
    assert(body);
    body->operator()(std::forward<Arguments>(arguments)...);
}

template <typename...Arguments>
std::size_t Signal<void(Arguments...)>::InvocationCount() const
{
    return body->InvocationCount();
}

} // namespace somera
