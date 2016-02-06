// Copyright (c) 2015 mogemimi. Distributed under the MIT license.

#pragma once

#include <cassert>
#include <utility>

namespace somera {

struct NullOptionalType final {
    struct init { constexpr init() = default; };
    constexpr explicit NullOptionalType(init) noexcept {}
};

constexpr NullOptionalType NullOpt{ NullOptionalType::init{} };

template <typename T>
struct Optional {
private:
    T data;
    bool valid = false;

public:
    constexpr Optional()
        : data()
        , valid(false)
    {}

    constexpr Optional(NullOptionalType const&)
        : data()
        , valid(false)
    {}

    Optional(Optional const&) = default;
    Optional(Optional &&) = default;

    constexpr Optional(T const& v)
        : data(v)
        , valid(true)
    {}

    constexpr Optional(T && v)
        : data(std::move(v))
        , valid(true)
    {}

    Optional & operator=(NullOptionalType const&)
    {
        valid = false;
        data.~T();
        return *this;
    }

    Optional & operator=(Optional const&) = default;
    Optional & operator=(Optional &&) = default;

    Optional & operator=(T const& v)
    {
        this->valid = true;
        this->data = v;
        return *this;
    }

    Optional & operator=(T && v)
    {
        this->valid = true;
        this->data = std::move(v);
        return *this;
    }

    T const* operator->() const noexcept
    {
        assert(valid);
        return &data;
    }

    T* operator->() noexcept
    {
        assert(valid);
        return &data;
    }

    T const& operator*() const
    {
        assert(valid);
        return data;
    }

    T & operator*()
    {
        assert(valid);
        return data;
    }

    explicit operator bool() const noexcept
    {
        return valid;
    }

    T const& value() const
    {
        assert(valid);
        return data;
    }

    T & value()
    {
        assert(valid);
        return data;
    }
};

} // namespace somera
