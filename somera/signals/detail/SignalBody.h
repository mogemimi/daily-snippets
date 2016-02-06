// Copyright (c) 2013-2016 mogemimi. Distributed under the MIT license.

#pragma once

#include "somera/signals/detail/ForwardDeclarations.h"
#include "somera/signals/Connection.h"
#include <algorithm>
#include <cassert>
#include <cstdint>
#include <functional>
#include <limits>
#include <memory>
#include <mutex>
#include <type_traits>
#include <utility>
#include <vector>

namespace somera {
namespace detail {
namespace signals {

template <typename Function>
using Slot = std::function<Function>;

template <typename Function>
class ConnectionBodyOverride final: public ConnectionBody {
private:
    typedef std::weak_ptr<Slot<Function>> WeakSlot;
    typedef std::weak_ptr<SignalBody<Function>> WeakSignal;

    WeakSignal weakSignal;
    WeakSlot weakSlot;

public:
    ConnectionBodyOverride(WeakSignal && weakSignalIn, WeakSlot && weakSlotIn)
        : weakSignal(std::forward<WeakSignal>(weakSignalIn))
        , weakSlot(std::forward<WeakSlot>(weakSlotIn))
    {}

    ConnectionBodyOverride(const WeakSignal& weakSignalIn, const WeakSlot& weakSlotIn)
        : weakSignal(weakSignalIn)
        , weakSlot(weakSlotIn)
    {}

    void Disconnect() override
    {
        if (weakSlot.expired()) {
            return;
        }

        auto lockedSlot = weakSlot.lock();

        if (auto lockedSignal = weakSignal.lock()) {
            lockedSignal->Disconnect(lockedSlot.get());
            weakSignal.reset();
        }

        weakSlot.reset();
    }

    bool Valid() const noexcept override
    {
        return !weakSlot.expired() && !weakSignal.expired();
    }

    std::unique_ptr<ConnectionBody> DeepCopy() const override
    {
        return std::make_unique<ConnectionBodyOverride>(weakSignal, weakSlot);
    }
};

template <typename...Arguments>
class SignalBody<void(Arguments...)> final
    : public std::enable_shared_from_this<SignalBody<void(Arguments...)>> {
private:
    typedef Slot<void(Arguments...)> SlotType;
    typedef ConnectionBodyOverride<void(Arguments...)> ConnectionBodyType;

public:
    SignalBody() = default;

    SignalBody(SignalBody const&) = delete;
    SignalBody & operator=(SignalBody const&) = delete;

    SignalBody(SignalBody &&) = delete;///@todo
    SignalBody & operator=(SignalBody &&) = delete;///@todo

    template <typename Function>
    std::unique_ptr<ConnectionBodyType> Connect(Function && slot);

    void Disconnect(SlotType const* observer);

    void operator()(Arguments &&... arguments);

    std::size_t InvocationCount() const;

private:
    void PushBackAddedListeners();
    void EraseRemovedListeners();

private:
    std::vector<std::shared_ptr<SlotType>> observers;
    std::vector<std::shared_ptr<SlotType>> addedObservers;

    std::recursive_mutex addingProtection;
    std::recursive_mutex slotsProtection;

    std::int32_t nestedMethodCallCount = 0;
};

template <typename...Arguments>
template <typename Function>
auto SignalBody<void(Arguments...)>::Connect(Function && slot)
    ->std::unique_ptr<ConnectionBodyType>
{
    assert(slot);
    auto observer = std::make_shared<SlotType>(std::forward<Function>(slot));
    {
        std::lock_guard<std::recursive_mutex> lock(addingProtection);

        assert(std::end(addedObservers) == std::find(
            std::begin(addedObservers), std::end(addedObservers), observer));
        addedObservers.push_back(observer);
    }

    std::weak_ptr<SignalBody> weakSignal = this->shared_from_this();
    assert(!weakSignal.expired());
    return std::make_unique<ConnectionBodyType>(std::move(weakSignal), observer);
}

template <typename...Arguments>
void SignalBody<void(Arguments...)>::Disconnect(SlotType const* observer)
{
    assert(observer);
    {
        std::lock_guard<std::recursive_mutex> lock(addingProtection);

        addedObservers.erase(std::remove_if(std::begin(addedObservers), std::end(addedObservers),
            [observer](std::shared_ptr<SlotType> const& p) {
                return p.get() == observer;
            }),
            std::end(addedObservers));
    }

    auto const iter = std::find_if(std::begin(observers), std::end(observers),
        [observer](std::shared_ptr<SlotType> const& p) {
            return p.get() == observer;
        });

    if (std::end(observers) == iter) {
        // FUS RO DAH
        return;
    }

    iter->reset();
}

template <typename...Arguments>
void SignalBody<void(Arguments...)>::PushBackAddedListeners()
{
    std::vector<std::shared_ptr<SlotType>> temporarySlots;
    {
        std::lock_guard<std::recursive_mutex> lock(addingProtection);
        std::swap(temporarySlots, addedObservers);
    }
    {
        std::lock_guard<std::recursive_mutex> lock(slotsProtection);

        for (auto & slot: temporarySlots) {
            assert(std::end(observers) == std::find(
                std::begin(observers), std::end(observers), slot));
            observers.push_back(slot);
        }
    }
}

template <typename...Arguments>
void SignalBody<void(Arguments...)>::EraseRemovedListeners()
{
    std::lock_guard<std::recursive_mutex> lock(slotsProtection);

    observers.erase(std::remove_if(std::begin(observers), std::end(observers),
        [](std::shared_ptr<SlotType> const& slot){ return !slot; }),
        std::end(observers));
}

template <typename...Arguments>
void SignalBody<void(Arguments...)>::operator()(Arguments &&... arguments)
{
    if (nestedMethodCallCount <= 0) {
        PushBackAddedListeners();
    }

    if (nestedMethodCallCount >= std::numeric_limits<std::int16_t>::max()) {
        return;
    }

    assert(nestedMethodCallCount >= 0);
    ++nestedMethodCallCount;

    try {
        for (auto & observer: observers) {
            if (auto scoped = observer) {
                scoped->operator()(std::forward<Arguments>(arguments)...);
            }
        }
    }
    catch (std::exception const& e) {
        --nestedMethodCallCount;
        throw e;
    }

    assert(nestedMethodCallCount > 0);
    --nestedMethodCallCount;

    if (nestedMethodCallCount <= 0) {
        EraseRemovedListeners();
    }
}

template <typename...Arguments>
std::size_t SignalBody<void(Arguments...)>::InvocationCount() const
{
    std::lock_guard<std::recursive_mutex> lock(slotsProtection);
    auto count = observers.size();
    return count;
}

} // namespace signals
} // namespace detail
} // namespace somera
