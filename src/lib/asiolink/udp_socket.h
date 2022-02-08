// Copyright (C) 2011-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef UDP_SOCKET_H
#define UDP_SOCKET_H 1

#ifndef BOOST_ASIO_HPP
#error "asio.hpp must be included before including this, see asiolink.h as to why"
#endif

#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>             // for some IPC/network system calls

#include <cstddef>

#include <asiolink/io_asio_socket.h>
#include <asiolink/io_endpoint.h>
#include <asiolink/io_service.h>
#include <asiolink/udp_endpoint.h>

#include <exceptions/isc_assert.h>

namespace isc {
namespace asiolink {

/// \brief The \c UDPSocket class is a concrete derived class of \c IOAsioSocket
/// that represents a UDP socket.
///
/// \param C Callback type
template <typename C>
class UDPSocket : public IOAsioSocket<C> {
private:
    /// \brief Class is non-copyable
    UDPSocket(const UDPSocket&);
    UDPSocket& operator=(const UDPSocket&);

public:
    enum {
        MIN_SIZE = 4096         // Minimum send and receive size
    };

    /// \brief Constructor from an ASIO UDP socket.
    ///
    /// \param socket The ASIO representation of the UDP socket.  It is assumed
    ///        that the caller will open and close the socket, so these
    ///        operations are a no-op for that socket.
    UDPSocket(boost::asio::ip::udp::socket& socket);

    /// \brief Constructor
    ///
    /// Used when the UDPSocket is being asked to manage its own internal
    /// socket.  In this case, the open() and close() methods are used.
    ///
    /// \param service I/O Service object used to manage the socket.
    UDPSocket(IOService& service);

    /// \brief Destructor
    virtual ~UDPSocket();

    /// \brief Return file descriptor of underlying socket
    virtual int getNative() const {
#if BOOST_VERSION < 106600
        return (socket_.native());
#else
        return (socket_.native_handle());
#endif
    }

    /// \brief Return protocol of socket
    virtual int getProtocol() const {
        return (IPPROTO_UDP);
    }

    /// \brief Is "open()" synchronous?
    ///
    /// Indicates that the opening of a UDP socket is synchronous.
    virtual bool isOpenSynchronous() const {
        return true;
    }

    /// \brief Open Socket
    ///
    /// Opens the UDP socket.  This is a synchronous operation.
    ///
    /// \param endpoint Endpoint to which the socket will send data.  This is
    ///        used to determine the address family that should be used for the
    ///        underlying socket.
    /// \param callback Unused as the operation is synchronous.
    virtual void open(const IOEndpoint* endpoint, C& callback);

    /// \brief Send Asynchronously
    ///
    /// Calls the underlying socket's async_send_to() method to send a packet of
    /// data asynchronously to the remote endpoint.  The callback will be called
    /// on completion.
    ///
    /// \param data Data to send
    /// \param length Length of data to send
    /// \param endpoint Target of the send
    /// \param callback Callback object.
    virtual void asyncSend(const void* data, size_t length,
                           const IOEndpoint* endpoint, C& callback);

    /// \brief Receive Asynchronously
    ///
    /// Calls the underlying socket's async_receive_from() method to read a
    /// packet of data from a remote endpoint.  Arrival of the data is signalled
    /// via a call to the callback function.
    ///
    /// \param data Buffer to receive incoming message
    /// \param length Length of the data buffer
    /// \param offset Offset into buffer where data is to be put
    /// \param endpoint Source of the communication
    /// \param callback Callback object
    virtual void asyncReceive(void* data, size_t length, size_t offset,
                              IOEndpoint* endpoint, C& callback);

    /// \brief Process received data
    ///
    /// See the description of IOAsioSocket::receiveComplete for a complete
    /// description of this method.
    ///
    /// \param staging Pointer to the start of the staging buffer.
    /// \param length Amount of data in the staging buffer.
    /// \param cumulative Amount of data received before the staging buffer is
    ///        processed.
    /// \param offset Unused.
    /// \param expected unused.
    /// \param outbuff Output buffer.  Data in the staging buffer is be copied
    ///        to this output buffer in the call.
    ///
    /// \return Always true
    virtual bool processReceivedData(const void* staging, size_t length,
                                     size_t& cumulative, size_t& offset,
                                     size_t& expected,
                                     isc::util::OutputBufferPtr& outbuff);

    /// \brief Cancel I/O On Socket
    virtual void cancel();

    /// \brief Close socket
    virtual void close();


private:
    // Two variables to hold the socket - a socket and a pointer to it.  This
    // handles the case where a socket is passed to the UDPSocket on
    // construction, or where it is asked to manage its own socket.

    /// Pointer to own socket
    std::unique_ptr<boost::asio::ip::udp::socket> socket_ptr_;

    // Socket
    boost::asio::ip::udp::socket& socket_;

    // True when socket is open
    bool isopen_;
};

// Constructor - caller manages socket

template <typename C>
UDPSocket<C>::UDPSocket(boost::asio::ip::udp::socket& socket) :
    socket_ptr_(), socket_(socket), isopen_(true)
{
}

// Constructor - create socket on the fly

template <typename C>
UDPSocket<C>::UDPSocket(IOService& service) :
    socket_ptr_(new boost::asio::ip::udp::socket(service.get_io_service())),
    socket_(*socket_ptr_), isopen_(false)
{
}

// Destructor.

template <typename C>
UDPSocket<C>::~UDPSocket()
{
}

// Open the socket.

template <typename C> void
UDPSocket<C>::open(const IOEndpoint* endpoint, C&) {

    // Ignore opens on already-open socket.  (Don't throw a failure because
    // of uncertainties as to what precedes when using asynchronous I/O.)
    // It also allows us a treat a passed-in socket in exactly the same way as
    // a self-managed socket (in that we can call the open() and close() methods
    // of this class).
    if (!isopen_) {
        if (endpoint->getFamily() == AF_INET) {
            socket_.open(boost::asio::ip::udp::v4());
        } else {
            socket_.open(boost::asio::ip::udp::v6());
        }
        isopen_ = true;

        // Ensure it can send and receive at least 4K buffers.
        boost::asio::ip::udp::socket::send_buffer_size snd_size;
        socket_.get_option(snd_size);
        if (snd_size.value() < MIN_SIZE) {
            snd_size = MIN_SIZE;
            socket_.set_option(snd_size);
        }

        boost::asio::ip::udp::socket::receive_buffer_size rcv_size;
        socket_.get_option(rcv_size);
        if (rcv_size.value() < MIN_SIZE) {
            rcv_size = MIN_SIZE;
            socket_.set_option(rcv_size);
        }
    }
}

// Send a message.  Should never do this if the socket is not open, so throw
// an exception if this is the case.

template <typename C> void
UDPSocket<C>::asyncSend(const void* data, size_t length,
                        const IOEndpoint* endpoint, C& callback)
{
    if (isopen_) {

        // Upconvert to a UDPEndpoint.  We need to do this because although
        // IOEndpoint is the base class of UDPEndpoint and TCPEndpoint, it
        // does not contain a method for getting at the underlying endpoint
        // type - that is in the derived class and the two classes differ on
        // return type.
        isc_throw_assert(endpoint->getProtocol() == IPPROTO_UDP);
        const UDPEndpoint* udp_endpoint =
            static_cast<const UDPEndpoint*>(endpoint);

        // ... and send the message.
        socket_.async_send_to(boost::asio::buffer(data, length),
            udp_endpoint->getASIOEndpoint(), callback);
    } else {
        isc_throw(SocketNotOpen,
            "attempt to send on a UDP socket that is not open");
    }
}

// Receive a message.   Should never do this if the socket is not open, so throw
// an exception if this is the case.

template <typename C> void
UDPSocket<C>::asyncReceive(void* data, size_t length, size_t offset,
                           IOEndpoint* endpoint, C& callback)
{
    if (isopen_) {

        // Upconvert the endpoint again.
        isc_throw_assert(endpoint->getProtocol() == IPPROTO_UDP);
        UDPEndpoint* udp_endpoint = static_cast<UDPEndpoint*>(endpoint);

        // Ensure we can write into the buffer
        if (offset >= length) {
            isc_throw(BufferOverflow, "attempt to read into area beyond end of "
                                      "UDP receive buffer");
        }
        void* buffer_start = static_cast<void*>(static_cast<uint8_t*>(data) + offset);

        // Issue the read
        socket_.async_receive_from(boost::asio::buffer(buffer_start, length - offset),
            udp_endpoint->getASIOEndpoint(), callback);
    } else {
        isc_throw(SocketNotOpen,
            "attempt to receive from a UDP socket that is not open");
    }
}

// Receive complete.  Just copy the data across to the output buffer and
// update arguments as appropriate.

template <typename C> bool
UDPSocket<C>::processReceivedData(const void* staging, size_t length,
                                  size_t& cumulative, size_t& offset,
                                  size_t& expected,
                                  isc::util::OutputBufferPtr& outbuff)
{
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
UDPSocket<C>::cancel() {
    if (isopen_) {
        socket_.cancel();
    }
}

// Close the socket down.  Can only do this if the socket is open and we are
// managing it ourself.

template <typename C> void
UDPSocket<C>::close() {
    if (isopen_ && socket_ptr_) {
        socket_.close();
        isopen_ = false;
    }
}

} // namespace asiolink
} // namespace isc

#endif // UDP_SOCKET_H
