// Copyright (c) 2016 mogemimi. Distributed under the MIT license.

#pragma once

#include <utility>

namespace somera {

template <typename T>
struct ArrayView {
    T* data = nullptr;
    size_t size = 0;
};

template <typename T>
ArrayView<T> MakeArrayView(T* data, size_t size)
{
    ArrayView<T> view;
    view.data = data;
    view.size = size;
    return std::move(view);
}

template <typename R, typename T>
ArrayView<R> CastArrayView(const ArrayView<T>& source)
{
    ArrayView<R> view;
    view.data = reinterpret_cast<R*>(source.data);
    view.size = source.size * (sizeof(T) / sizeof(R));
    return std::move(view);
}

} // namespace somera
