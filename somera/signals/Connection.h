// Copyright (c) 2013-2016 mogemimi. Distributed under the MIT license.

#pragma once

#include <memory>

namespace somera {
namespace detail {

class ConnectionBody {
public:
    virtual ~ConnectionBody() = default;
    virtual void Disconnect() = 0;
    virtual bool Valid() const noexcept = 0;
    virtual std::unique_ptr<ConnectionBody> DeepCopy() const = 0;
};

} // namespace detail

class Connection final {
private:
    using ConnectionBody = detail::ConnectionBody;
    std::unique_ptr<ConnectionBody> body;

public:
    Connection() = default;

    explicit Connection(std::unique_ptr<ConnectionBody> && body);

    Connection(Connection const& connection);
    Connection(Connection && connection) = default;

    Connection & operator=(Connection const& connection);
    Connection & operator=(Connection && connection) = default;

    operator bool() const noexcept;

    void Disconnect();
};

class ScopedConnection final {
private:
    Connection connection;

public:
    ScopedConnection() = default;
    ScopedConnection(ScopedConnection const&) = delete;
    ScopedConnection(ScopedConnection &&) = default;

    ScopedConnection(Connection const& connection);
    ScopedConnection(Connection && connection);

    ~ScopedConnection();

    ScopedConnection & operator=(ScopedConnection const&) = delete;
    ScopedConnection & operator=(ScopedConnection &&) = default;

    ScopedConnection & operator=(Connection const& c);
    ScopedConnection & operator=(Connection && c);

    operator bool() const noexcept;

    void Disconnect();
};

} // namespace somera
