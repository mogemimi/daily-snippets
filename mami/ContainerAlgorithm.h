// Copyright (c) 2016 mogemimi. Distributed under the MIT license.

#pragma once

#include <algorithm>
#include <iterator>

namespace somera {

template <class Container, class Func>
void EraseIf(Container & c, Func f)
{
    c.erase(std::remove_if(std::begin(c), std::end(c), f), std::end(c));
}

template <class Container, class Func>
void EraseMapIf(Container & c, Func f)
{
    typename Container::iterator it = std::begin(c);
    while (it != std::end(c)) {
        if (f(*it)) {
            c.erase(it++);
        } else {
            ++it;
        }
    }
}

template <class Container, class T>
auto Find(Container & c, const T& value)
{
    return std::find(std::begin(c), std::end(c), value);
}

template <class Container, class Func>
auto FindIf(Container & c, Func f)
{
    return std::find_if(std::begin(c), std::end(c), f);
}

} // namespace somera
