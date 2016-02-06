// Copyright (c) 2016 mogemimi. Distributed under the MIT license.

#pragma once

#include "ArrayView.h"
#include "EndPoint.h"
#include "Error.h"
#include "IOService.h"
#include "somera/signals/Connection.h"
#include "somera/Optional.h"
#include <array>
#include <chrono>
#include <cstdint>
#include <functional>
#include <vector>
#include <string>
#include <tuple>

namespace somera {
namespace detail {

enum class ProtocolType {
    Tcp,
    //Udp,
};

class DescriptorPOSIX final {
public:
    DescriptorPOSIX() = default;

    DescriptorPOSIX(const DescriptorPOSIX&) = delete;

    DescriptorPOSIX(DescriptorPOSIX && other);

    DescriptorPOSIX & operator=(const DescriptorPOSIX&) = delete;

    DescriptorPOSIX & operator=(DescriptorPOSIX && other);

    void Bind(const EndPoint& endPoint);

    std::tuple<bool, errno_t> Connect(const EndPoint& endPoint);

    std::tuple<DescriptorPOSIX, EndPoint> Accept(ProtocolType protocolType);

    void Close();

    int GetHandle() const;

private:
    ///@brief The file descriptor for socket
    Optional<int> descriptor_;
};

} // namespace detail

enum class SocketError {
    TimedOut,
    Shutdown,
    NotConnected,
};

class Socket {
public:
    Socket() = default;

    Socket(IOService & service);

    Socket(
        IOService & service,
        detail::DescriptorPOSIX && descriptor,
        EndPoint && endPoint);

    ~Socket();

    Socket(const Socket&) = delete;
    Socket & operator=(const Socket&) = delete;

    Socket(Socket && other);
    Socket & operator=(Socket && other);

    void Connect(const EndPoint& endPoint, std::function<void(Socket & socket)> onConnected);

    void Close();

    void Read(const std::function<void(Socket&, const ArrayView<uint8_t>&)>& onRead);

//    void ReadError(const std::function<void(Socket&, const Error&)>& onReadError);
//
//    void Timeout(const std::function<void(Socket&)>& onReadError);
//
//    void Disconnect(const std::function<void(Socket&)>& onReadError);

    void Write(const ArrayView<uint8_t const>& data);

    ///@brief Sets the interval to wait for socket activity.
    void SetTimeout(const std::chrono::milliseconds& timeout);

    ///@brief Sets the interval to wait for socket activity.
    void SetTimeout(
        const std::chrono::milliseconds& timeout,
        const std::function<void(Socket&)>& callback);

    void SetErrorListener(const std::function<void(Socket & socket, const Error&)>& callback);

    void SetCloseListener(const std::function<void(Socket &)>& callback);

    EndPoint GetEndPoint() const;

    int GetHandle() const;

private:
    void ConnectEventLoop(const std::chrono::system_clock::time_point& startTime);

    void ReadEventLoop();

private:
    using DescriptorType = detail::DescriptorPOSIX;
    IOService* service_ = nullptr;
    DescriptorType descriptor_;
    EndPoint endPoint_;
    ScopedConnection connectionActive_;
    std::chrono::milliseconds timeout_;
    std::function<void(Socket & socket)> onConnected_;
    std::function<void(Socket & socket)> onTimeout_;
    std::function<void(Socket & socket, const ArrayView<uint8_t>& view)> onRead_;
    std::function<void(Socket & socket, const Error&)> onError_;
    std::function<void(Socket & socket)> onClose_;
};

class Server {
public:
    Server(IOService & service);

    ~Server();

    void Listen(
        const EndPoint& endPoint,
        int backlog,
        const std::function<void(const std::shared_ptr<Socket>&)>& onAccept);

    void Close();

    void Read(const std::function<void(const std::shared_ptr<Socket>&, const ArrayView<uint8_t>&)>& onRead);

//    void ReadError(const std::function<void(Socket&, const Error&)>& onReadError);
//
//    void Timeout(const std::function<void(Socket&)>& onReadError);
//
//    void Disconnect(const std::function<void(Socket&)>& onReadError);

    void SetErrorListener(const std::function<void(const Error&)>& callback);

    void SetCloseListener(const std::function<void(const std::shared_ptr<Socket>&)>& callback);

private:
    void ListenEventLoop();

    void ReadEventLoop();

private:
    struct Session {
        std::shared_ptr<Socket> socket;
        bool isClosed = false;
    };

private:
    using DescriptorType = detail::DescriptorPOSIX;
    IOService* service_ = nullptr;
    DescriptorType descriptor_;
    EndPoint endPoint_;
    std::vector<Session> sessions_;
    ScopedConnection connectionListen_;
    ScopedConnection connectionRead_;
    int maxSessionCount_ = 5;
    std::function<void(const std::shared_ptr<Socket>&)> onAccept_;
    std::function<void(const std::shared_ptr<Socket>&, const ArrayView<uint8_t>&)> onRead_;
    std::function<void(const std::shared_ptr<Socket>&)> onClose_;
    std::function<void(const Error&)> onError_;
};

} // namespace somera
