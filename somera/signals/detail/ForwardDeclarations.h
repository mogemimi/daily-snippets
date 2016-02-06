// Copyright (c) 2013-2016 mogemimi. Distributed under the MIT license.

#pragma once

namespace somera {
namespace detail {
namespace signals {

template <typename Function>
class SignalBody;

} // namespace signals
} // namespace detail

class Connection;
class EventQueue;
class ScopedConnection;

template <typename Function>
class Signal;

} // namespace somera
