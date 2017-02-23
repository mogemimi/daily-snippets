// Copyright (c) 2017 mogemimi. Distributed under the MIT license.

#pragma once

#include <cassert>
#include <utility>

namespace aligndiff {

// TODO:
// In C++17, this 'Optional' class should be marked as deprecated
// in favour of std::optional<T>.

struct NullOptionalType final {
    struct init { constexpr init() = default; };
    constexpr explicit NullOptionalType(init) noexcept {}
};

constexpr NullOptionalType nullopt{ NullOptionalType::init{} };

template <typename T>
struct optional {
private:
    T data;
    bool valid = false;

public:
    constexpr optional()
        : data()
        , valid(false)
    {}

    constexpr optional(NullOptionalType const&)
        : data()
        , valid(false)
    {}

    optional(optional const&) = default;
    optional(optional &&) = default;

    constexpr optional(T const& v)
        : data(v)
        , valid(true)
    {}

    constexpr optional(T && v)
        : data(std::move(v))
        , valid(true)
    {}

    optional & operator=(NullOptionalType const&)
    {
        valid = false;
        data.~T();
        return *this;
    }

    optional & operator=(optional const&) = default;
    optional & operator=(optional &&) = default;

    optional & operator=(T const& v)
    {
        this->valid = true;
        this->data = v;
        return *this;
    }

    optional & operator=(T && v)
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

} // namespace aligndiff
