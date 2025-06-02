// Copyright (C) 2023-2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef ICMP_SOCKET_H
#define ICMP_SOCKET_H 1

#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

#include <cstddef>

#include <asiolink/io_asio_socket.h>
#include <asiolink/io_service.h>
#include <icmp_endpoint.h>

#include <exceptions/isc_assert.h>

namespace isc {
namespace ping_check {

/// @brief The @c ICMPSocket class is a concrete derived class of @c IOAsioSocket
/// that represents a ICMP socket.
///
/// @param C Callback type
template <typename C>
class ICMPSocket : public asiolink::IOAsioSocket<C> {
private:
    /// @brief Class is non-copyable
    explicit ICMPSocket(const ICMPSocket&);
    ICMPSocket& operator=(const ICMPSocket&);

public:
    enum {
        MIN_SIZE = 4096         // Minimum send and receive size
    };

    /// @brief Constructor from an ASIO ICMP socket.
    ///
    /// @param socket The ASIO representation of the ICMP socket.  It is assumed
    ///        that the caller will open and close the socket, so these
    ///        operations are a no-op for that socket.
    explicit ICMPSocket(boost::asio::ip::icmp::socket& socket);

    /// @brief Constructor
    ///
    /// Used when the ICMPSocket is being asked to manage its own internal
    /// socket.  In this case, the open() and close() methods are used.
    ///
    /// @param service I/O Service object used to manage the socket.
    explicit ICMPSocket(const asiolink::IOServicePtr& service);

    /// @brief Destructor
    virtual ~ICMPSocket();

    /// @brief Return file descriptor of underlying socket
    ///
    /// @return socket's native file descriptor as an int.
    virtual int getNative() const {
#if BOOST_VERSION < 106600
        return (socket_.native());
#else
        return (socket_.native_handle());
#endif
    }

    /// @brief Return protocol of socket
    ///
    /// @return Always IPPROTO_ICMP.
    virtual int getProtocol() const {
        return (IPPROTO_ICMP);
    }

    /// @brief Is "open()" synchronous?
    ///
    /// Indicates that the opening of a ICMP socket is synchronous.
    /// @return Always true.
    virtual bool isOpenSynchronous() const {
        return true;
    }

    /// @brief Indicates if the socket is currently open.
    ///
    /// @return true if socket is open.
    virtual bool isOpen() const {
        return isopen_;
    }

    /// @brief Open Socket
    ///
    /// Opens the ICMP socket.  This is a synchronous operation.
    ///
    /// @param endpoint Endpoint to which the socket will send data.  This is
    ///        used to determine the address family that should be used for the
    ///        underlying socket.
    /// @param callback Unused as the operation is synchronous.
    virtual void open(const asiolink::IOEndpoint* endpoint, C& callback);

    /// @brief Send Asynchronously
    ///
    /// Calls the underlying socket's async_send_to() method to send a packet of
    /// data asynchronously to the remote endpoint.  The callback will be called
    /// on completion.
    ///
    /// @param data Data to send
    /// @param length Length of data to send
    /// @param endpoint Target of the send
    /// @param callback Callback object.
    virtual void asyncSend(const void* data, size_t length,
                           const asiolink::IOEndpoint* endpoint, C& callback);

    /// @brief Receive Asynchronously
    ///
    /// Calls the underlying socket's async_receive_from() method to read a
    /// packet of data from a remote endpoint.  Arrival of the data is signalled
    /// via a call to the callback function.
    ///
    /// @param data Buffer to receive incoming message
    /// @param length Length of the data buffer
    /// @param offset Offset into buffer where data is to be put
    /// @param endpoint Source of the communication
    /// @param callback Callback object
    virtual void asyncReceive(void* data, size_t length, size_t offset,
                              asiolink::IOEndpoint* endpoint, C& callback);

    /// @brief Process received data
    ///
    /// See the description of IOAsioSocket::receiveComplete for a complete
    /// description of this method.
    ///
    /// @param staging Pointer to the start of the staging buffer.
    /// @param length Amount of data in the staging buffer.
    /// @param cumulative Amount of data received before the staging buffer is
    ///        processed.
    /// @param offset Unused.
    /// @param expected unused.
    /// @param outbuff Output buffer.  Data in the staging buffer is be copied
    ///        to this output buffer in the call.
    ///
    /// @return Always true
    virtual bool processReceivedData(const void* staging, size_t length,
                                     size_t& cumulative, size_t& offset,
                                     size_t& expected,
                                     isc::util::OutputBufferPtr& outbuff);

    /// @brief Cancel I/O On Socket
    virtual void cancel();

    /// @brief Close socket
    virtual void close();

    /// @brief Calculates the checksum for the given buffer of data.
    ///
    /// @param buf pointer to the data buffer.
    /// @param buf_size number of bytes in the data buffer.
    ///
    /// @return calculated checksum of the data as a uint16_t.
    static uint16_t calcChecksum(const uint8_t* buf, const uint32_t buf_size);

private:
    /// @brief The IO service used to handle events.
    isc::asiolink::IOServicePtr io_service_;

    // Two variables to hold the socket - a socket and a pointer to it.  This
    // handles the case where a socket is passed to the ICMPSocket on
    // construction, or where it is asked to manage its own socket.

    /// Pointer to own socket
    std::unique_ptr<boost::asio::ip::icmp::socket> socket_ptr_;

    // Socket
    boost::asio::ip::icmp::socket& socket_;

    // True when socket is open
    bool isopen_;
};

// Constructor - caller manages socket

template <typename C>
ICMPSocket<C>::ICMPSocket(boost::asio::ip::icmp::socket& socket) :
    socket_ptr_(), socket_(socket), isopen_(true) {
}

// Constructor - create socket on the fly

template <typename C>
ICMPSocket<C>::ICMPSocket(const asiolink::IOServicePtr& io_service) :
    io_service_(io_service),
    socket_ptr_(new boost::asio::ip::icmp::socket(io_service_->getInternalIOService())),
    socket_(*socket_ptr_), isopen_(false) {
}

// Destructor.

template <typename C>
ICMPSocket<C>::~ICMPSocket() {
}

// Open the socket.

template <typename C> void
ICMPSocket<C>::open(const asiolink::IOEndpoint* endpoint, C&) {

    // Ignore opens on already-open socket.  (Don't throw a failure because
    // of uncertainties as to what precedes when using asynchronous I/O.)
    // It also allows us a treat a passed-in socket in exactly the same way as
    // a self-managed socket (in that we can call the open() and close() methods
    // of this class).
    if (!isopen_) {
        if (endpoint->getFamily() == AF_INET) {
            socket_.open(boost::asio::ip::icmp::v4());
        } else {
            socket_.open(boost::asio::ip::icmp::v6());
        }
        isopen_ = true;

        // Ensure it can send and receive at least 4K buffers.
        boost::asio::ip::icmp::socket::send_buffer_size snd_size;
        socket_.get_option(snd_size);
        if (snd_size.value() < MIN_SIZE) {
            snd_size = MIN_SIZE;
            socket_.set_option(snd_size);
        }

        boost::asio::ip::icmp::socket::receive_buffer_size rcv_size;
        socket_.get_option(rcv_size);
        if (rcv_size.value() < MIN_SIZE) {
            rcv_size = MIN_SIZE;
            socket_.set_option(rcv_size);
        }

        boost::asio::socket_base::do_not_route option(false);
        socket_.set_option(option);
    }
}

// Send a message.  Should never do this if the socket is not open, so throw
// an exception if this is the case.

template <typename C> void
ICMPSocket<C>::asyncSend(const void* data, size_t length,
                         const asiolink::IOEndpoint* endpoint, C& callback) {
    if (isopen_) {

        // Upconvert to a ICMPEndpoint.  We need to do this because although
        // IOEndpoint is the base class of ICMPEndpoint and TCPEndpoint, it
        // does not contain a method for getting at the underlying endpoint
        // type - that is in the derived class and the two classes differ on
        // return type.
        isc_throw_assert(endpoint->getProtocol() == IPPROTO_ICMP);
        const ICMPEndpoint* udp_endpoint =
            static_cast<const ICMPEndpoint*>(endpoint);

        // ... and send the message.
        socket_.async_send_to(boost::asio::buffer(data, length),
            udp_endpoint->getASIOEndpoint(), callback);
    } else {
        isc_throw(asiolink::SocketNotOpen,
            "attempt to send on a ICMP socket that is not open");
    }
}

// Receive a message.   Should never do this if the socket is not open, so throw
// an exception if this is the case.

template <typename C> void
ICMPSocket<C>::asyncReceive(void* data, size_t length, size_t offset,
                            asiolink::IOEndpoint* endpoint, C& callback) {
    if (isopen_) {

        // Upconvert the endpoint again.
        isc_throw_assert(endpoint->getProtocol() == IPPROTO_ICMP);
        ICMPEndpoint* udp_endpoint = static_cast<ICMPEndpoint*>(endpoint);

        // Ensure we can write into the buffer
        if (offset >= length) {
            isc_throw(asiolink::BufferOverflow, "attempt to read into area beyond end of "
                                      "ICMP receive buffer");
        }
        void* buffer_start = static_cast<void*>(static_cast<uint8_t*>(data) + offset);

        // Issue the read
        socket_.async_receive_from(boost::asio::buffer(buffer_start, length - offset),
                                   udp_endpoint->getASIOEndpoint(), callback);
    } else {
        isc_throw(asiolink::SocketNotOpen,
            "attempt to receive from a ICMP socket that is not open");
    }
}

// Receive complete.  Just copy the data across to the output buffer and
// update arguments as appropriate.

template <typename C> bool
ICMPSocket<C>::processReceivedData(const void* staging, size_t length,
                                   size_t& cumulative, size_t& offset,
                                   size_t& expected,
                                   isc::util::OutputBufferPtr& outbuff) {
    // Set return values to what we should expect.
    cumulative = length;
    expected = length;
    offset = 0;

    // Copy data across
    outbuff->writeData(staging, length);

    // ... and mark that we have everything.
    return (true);
}

// Cancel I/O on the socket.  No-op if the socket is not open.

template <typename C> void
ICMPSocket<C>::cancel() {
    if (isopen_) {
        socket_.cancel();
    }
}

// Close the socket down.  Can only do this if the socket is open and we are
// managing it ourself.

template <typename C> void
ICMPSocket<C>::close() {
    if (isopen_ && socket_ptr_) {
        socket_.close();
        isopen_ = false;
    }
}

template <typename C> uint16_t
ICMPSocket<C>::calcChecksum(const uint8_t* buf, const uint32_t buf_size) {
    uint32_t sum = 0;
    uint32_t i;
    for (i = 0; i < (buf_size & ~1U); i += 2) {
        uint16_t chunk = buf[i] << 8 | buf[i + 1];
        sum += chunk;
        if (sum > 0xFFFF) {
            sum -= 0xFFFF;
        }
    }
    // If one byte has left, we also need to add it to the checksum.
    if (i < buf_size) {
        sum += buf[i] << 8;
        if (sum > 0xFFFF) {
            sum -= 0xFFFF;
        }
    }

    return (sum);
}

} // namespace ping_check
} // namespace isc
#endif // ICMP_SOCKET_H
