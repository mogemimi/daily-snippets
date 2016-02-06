// Copyright (c) 2013-2016 mogemimi. Distributed under the MIT license.

#pragma once

#include "detail/ForwardDeclarations.h"
#include "somera/Any.h"
#include <functional>
#include <memory>
#include <mutex>
#include <utility>
#include <vector>

namespace somera {

class EventQueue final {
public:
    EventQueue();

    EventQueue(EventQueue const&) = delete;
    EventQueue(EventQueue &&) = delete;
    EventQueue & operator=(EventQueue const&) = delete;
    EventQueue & operator=(EventQueue &&) = delete;

    Connection Connect(std::function<void(const Any&)> const& slot);

    Connection Connect(std::function<void(const Any&)> && slot);

    void Enqueue(Any && event);

    template <typename T>
    void Enqueue(T && argument)
    {
        Any event{std::forward<std::remove_reference_t<T>>(argument)};
        Enqueue(std::move(event));
    }

    template <typename T>
    void Enqueue(const T & argument)
    {
        Any event{std::remove_reference_t<T>(argument)};
        Enqueue(std::move(event));
    }

    void Emit();

private:
    using SignalBody = detail::signals::SignalBody<void(const Any&)>;
    std::vector<Any> events;
    std::recursive_mutex notificationMutex;
    std::shared_ptr<SignalBody> signalBody;
};

} // namespace somera
