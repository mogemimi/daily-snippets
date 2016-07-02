// Copyright (c) 2013-2016 mogemimi. Distributed under the MIT license.

#include "EventQueue.h"
#include "detail/SignalBody.h"
#include "Connection.h"

namespace somera {

EventQueue::EventQueue()
    : signalBody(std::make_shared<SignalBody>())
{}

Connection EventQueue::Connect(std::function<void(const Any&)> const& slot)
{
    assert(slot);
    assert(this->signalBody);
    return Connection{signalBody->Connect(slot)};
}

Connection EventQueue::Connect(std::function<void(const Any&)> && slot)
{
    assert(slot);
    assert(this->signalBody);
    return Connection{signalBody->Connect(slot)};
}

void EventQueue::Enqueue(Any && event)
{
    std::lock_guard<std::recursive_mutex> lock(notificationMutex);
    events.emplace_back(std::move(event));
}

void EventQueue::Emit()
{
    assert(signalBody);
    std::vector<Any> notifications;
    {
        std::lock_guard<std::recursive_mutex> lock(notificationMutex);
        std::swap(notifications, events);
    }
    for (auto & event : notifications) {
        signalBody->operator()(event);
    }
}

} // namespace somera
