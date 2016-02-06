// Copyright (c) 2013-2016 mogemimi. Distributed under the MIT license.

#include "Connection.h"
#include <utility>

namespace somera {

Connection::Connection(std::unique_ptr<ConnectionBody> && bodyIn)
    : body(std::forward<std::unique_ptr<ConnectionBody>>(bodyIn))
{}

Connection::Connection(Connection const& connection)
{
    if (connection.body) {
        body = connection.body->DeepCopy();
    }
}

Connection & Connection::operator=(Connection const& connection)
{
    if (connection.body) {
        body = connection.body->DeepCopy();
    }
    return *this;
}

Connection::operator bool() const noexcept
{
    return body && body->Valid();
}

void Connection::Disconnect()
{
    if (body) {
        body->Disconnect();
        body.reset();
    }
}

ScopedConnection::ScopedConnection(Connection const& c)
    : connection(c)
{}

ScopedConnection::ScopedConnection(Connection && c)
    : connection(std::move(c))
{}

ScopedConnection::~ScopedConnection()
{
    connection.Disconnect();
}

ScopedConnection & ScopedConnection::operator=(Connection const& c)
{
    connection.Disconnect();
    connection = c;
    return *this;
}

ScopedConnection & ScopedConnection::operator=(Connection && c)
{
    connection.Disconnect();
    connection = std::move(c);
    return *this;
}

ScopedConnection::operator bool() const noexcept
{
    return this->connection.operator bool();
}

void ScopedConnection::Disconnect()
{
    connection.Disconnect();
}

} // namespace somera
