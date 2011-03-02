// Copyright (C) 2011  Internet Systems Consortium, Inc. ("ISC")
//
// Permission to use, copy, modify, and/or distribute this software for any
// purpose with or without fee is hereby granted, provided that the above
// copyright notice and this permission notice appear in all copies.
//
// THE SOFTWARE IS PROVIDED "AS IS" AND ISC DISCLAIMS ALL WARRANTIES WITH
// REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
// AND FITNESS.  IN NO EVENT SHALL ISC BE LIABLE FOR ANY SPECIAL, DIRECT,
// INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
// LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE
// OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
// PERFORMANCE OF THIS SOFTWARE.

#ifndef __TCP_SOCKET_H
#define __TCP_SOCKET_H 1

#ifndef ASIO_HPP
#error "asio.hpp must be included before including this, see asiolink.h as to why"
#endif

#include <log/dummylog.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>             // for some IPC/network system calls

#include <cstddef>

#include <boost/bind.hpp>
#include <boost/numeric/conversion/cast.hpp>

#include <config.h>

#include <dns/buffer.h>

#include <asiolink/asiolink_utilities.h>
#include <asiolink/io_asio_socket.h>
#include <asiolink/io_endpoint.h>
#include <asiolink/io_service.h>
#include <asiolink/tcp_endpoint.h>

namespace asiolink {

/// \brief Buffer Too Large
///
/// Thrown on an attempt to send a buffer > 64k
class BufferTooLarge : public IOError {
public:
    BufferTooLarge(const char* file, size_t line, const char* what) :
        IOError(file, line, what) {}
};

/// \brief The \c TCPSocket class is a concrete derived class of \c IOAsioSocket
/// that represents a TCP socket.
///
/// \param C Callback type
template <typename C>
class TCPSocket : public IOAsioSocket<C> {
private:
    /// \brief Class is non-copyable
    TCPSocket(const TCPSocket&);
    TCPSocket& operator=(const TCPSocket&);

public:

    /// \brief Constructor from an ASIO TCP socket.
    ///
    /// \param socket The ASIO representation of the TCP socket.  It is assumed
    ///        that the caller will open and close the socket, so these
    ///        operations are a no-op for that socket.
    TCPSocket(asio::ip::tcp::socket& socket);

    /// \brief Constructor
    ///
    /// Used when the TCPSocket is being asked to manage its own internal
    /// socket.  In this case, the open() and close() methods are used.
    ///
    /// \param service I/O Service object used to manage the socket.
    TCPSocket(IOService& service);

    /// \brief Destructor
    virtual ~TCPSocket();

    /// \brief Return file descriptor of underlying socket
    virtual int getNative() const {
        return (socket_.native());
    }

    /// \brief Return protocol of socket
    virtual int getProtocol() const {
        return (IPPROTO_TCP);
    }

    /// \brief Is "open()" synchronous?
    ///
    /// Indicates that the opening of a TCP socket is asynchronous.
    virtual bool isOpenSynchronous() const {
        return (false);
    }

    /// \brief Open Socket
    ///
    /// Opens the TCP socket.  This is an asynchronous operation, completion of
    /// which will be signalled via a call to the callback function.
    ///
    /// \param endpoint Endpoint to which the socket will connect.
    /// \param callback Callback object.
    virtual void open(const IOEndpoint* endpoint, C& callback);

    /// \brief Send Asynchronously
    ///
    /// Calls the underlying socket's async_send() method to send a packet of
    /// data asynchronously to the remote endpoint.  The callback will be called
    /// on completion.
    ///
    /// \param data Data to send
    /// \param length Length of data to send
    /// \param endpoint Target of the send. (Unused for a TCP socket because
    ///        that was determined when the connection was opened.)
    /// \param callback Callback object.
    virtual void asyncSend(const void* data, size_t length,
                           const IOEndpoint* endpoint, C& callback);

    /// \brief Receive Asynchronously
    ///
    /// Calls the underlying socket's async_receive() method to read a packet
    /// of data from a remote endpoint.  Arrival of the data is signalled via a
    /// call to the callback function.
    ///
    /// \param data Buffer to receive incoming message
    /// \param length Length of the data buffer
    /// \param offset Offset into buffer where data is to be put
    /// \param endpoint Source of the communication
    /// \param callback Callback object
    virtual void asyncReceive(void* data, size_t length, size_t offset,
                              IOEndpoint* endpoint, C& callback);

    /// \brief Checks if the data received is complete.
    ///
    /// Checks if all the data has been received by checking that the amount
    /// of data received is equal to the number in the first two bytes of the
    /// message plus two (for the count field itself).
    ///
    /// \param data Data buffer containing data to date (ignored)
    /// \param length Amount of data in the buffer.
    ///
    /// \return true if the receive is complete, false if not.
    virtual bool receiveComplete(const void* data, size_t length);

    /// \brief Append Normalized Data
    ///
    /// When a UDP buffer is received, the entire buffer contains the data.
    /// When a TCP buffer is received, the first two bytes of the buffer hold
    /// a length count.  This method removes those bytes from the buffer.
    ///
    /// \param inbuf Input buffer.  This contains the data received over the
    ///        network connection.
    /// \param length Amount of data in the input buffer.  If TCP, this includes
    ///        the two-byte count field.
    /// \param outbuf Pointer to output buffer to which the data will be
    ///        appended
    virtual void appendNormalizedData(const void* inbuf, size_t length,
                                      isc::dns::OutputBufferPtr outbuf);

    /// \brief Cancel I/O On Socket
    virtual void cancel();

    /// \brief Close socket
    virtual void close();


private:
    // Two variables to hold the socket - a socket and a pointer to it.  This
    // handles the case where a socket is passed to the TCPSocket on
    // construction, or where it is asked to manage its own socket.
    asio::ip::tcp::socket*      socket_ptr_;    ///< Pointer to own socket
    asio::ip::tcp::socket&      socket_;        ///< Socket
    bool                        isopen_;        ///< true when socket is open

    // TODO: Remove temporary buffer
    // The current implementation copies the buffer passed to asyncSend() into
    // a temporary buffer and precedes it with a two-byte count field.  As
    // ASIO should really be just about sendiong and receiving data, the TCP
    // code should not do this.  If the protocol using this requires a two-byte
    // count, it should add it before calling this code.  (This may be best
    // achieved by altering isc::dns::buffer to have pairs of methods:
    // getLength()/getTCPLength(), getData()/getTCPData(), with the getTCPXxx()
    // methods taking into account a two-byte count field.)
    //
    // The option of sending the data in two operations, the count followed by
    // the data was discounted as that would lead to two callbacks which would
    // cause problems with the stackless coroutine code.
    isc::dns::OutputBufferPtr   send_buffer_;   ///< Send buffer
};

// Constructor - caller manages socket

template <typename C>
TCPSocket<C>::TCPSocket(asio::ip::tcp::socket& socket) :
    socket_ptr_(NULL), socket_(socket), isopen_(true), send_buffer_()
{
}

// Constructor - create socket on the fly

template <typename C>
TCPSocket<C>::TCPSocket(IOService& service) :
    socket_ptr_(new asio::ip::tcp::socket(service.get_io_service())),
    socket_(*socket_ptr_), isopen_(false)
{
}

// Destructor.  Only delete the socket if we are managing it.

template <typename C>
TCPSocket<C>::~TCPSocket()
{
    delete socket_ptr_;
}

// Open the socket.

template <typename C> void
TCPSocket<C>::open(const IOEndpoint* endpoint, C& callback) {

    // Ignore opens on already-open socket.  Don't throw a failure because
    // of uncertainties as to what precedes whan when using asynchronous I/O.
    // At also allows us a treat a passed-in socket as a self-managed socket.
    if (!isopen_) {
        if (endpoint->getFamily() == AF_INET) {
            socket_.open(asio::ip::tcp::v4());
        }
        else {
            socket_.open(asio::ip::tcp::v6());
        }
        isopen_ = true;

        // Set options on the socket:

        // Reuse address - allow the socket to bind to a port even if the port
        // is in the TIMED_WAIT state.
        socket_.set_option(asio::socket_base::reuse_address(true));
    }

    // Upconvert to a TCPEndpoint.  We need to do this because although
    // IOEndpoint is the base class of UDPEndpoint and TCPEndpoint, it does not
    // contain a method for getting at the underlying endpoint type - that is in
    /// the derived class and the two classes differ on return type.
    assert(endpoint->getProtocol() == IPPROTO_TCP);
    const TCPEndpoint* tcp_endpoint =
        static_cast<const TCPEndpoint*>(endpoint);

    // Connect to the remote endpoint.  On success, the handler will be
    // called (with one argument - the length argument will default to
    // zero).
    socket_.async_connect(tcp_endpoint->getASIOEndpoint(), callback);
}

// Send a message.  Should never do this if the socket is not open, so throw
// an exception if this is the case.

template <typename C> void
TCPSocket<C>::asyncSend(const void* data, size_t length, const IOEndpoint*,
                        C& callback)
{
    if (isopen_) {

        // Need to copy the data into a temporary buffer and precede it with
        // a two-byte count field.
        // TODO: arrange for the buffer passed to be preceded by the count
        try {
            // Ensure it fits into 16 bits
            uint16_t count = boost::numeric_cast<uint16_t>(length);

            // Copy data into a buffer preceded by the count field.
            send_buffer_.reset(new isc::dns::OutputBuffer(length + 2));
            send_buffer_->writeUint16(count);
            send_buffer_->writeData(data, length);

            // ... and send it
            socket_.async_send(asio::buffer(send_buffer_->getData(),
                               send_buffer_->getLength()), callback);
        } catch (boost::numeric::bad_numeric_cast& e) {
            isc_throw(BufferTooLarge,
                      "attempt to send buffer larger than 64kB");
        }

    } else {
        isc_throw(SocketNotOpen,
            "attempt to send on a TCP socket that is not open");
    }
}

// Receive a message. Note that the "offset" argument is used as an index
// into the buffer in order to decide where to put the data.  It is up to the
// caller to initialize the data to zero
template <typename C> void
TCPSocket<C>::asyncReceive(void* data, size_t length, size_t offset,
    IOEndpoint* endpoint, C& callback)
{
    if (isopen_) {
        // Upconvert to a TCPEndpoint.  We need to do this because although
        // IOEndpoint is the base class of UDPEndpoint and TCPEndpoint, it
        // does not contain a method for getting at the underlying endpoint
        // type - that is in the derived class and the two classes differ on
        // return type.
        assert(endpoint->getProtocol() == IPPROTO_TCP);
        TCPEndpoint* tcp_endpoint = static_cast<TCPEndpoint*>(endpoint);

        // Write the endpoint details from the comminications link.  Ideally
        // we should make IOEndpoint assignable, but this runs in to all sorts
        // of problems concerning the management of the underlying Boost
        // endpoint (e.g. if it is not self-managed, is the copied one
        // self-managed?) The most pragmatic solution is to let Boost take care
        // of everything and copy details of the underlying endpoint.
        tcp_endpoint->getASIOEndpoint() = socket_.remote_endpoint();

        // Ensure we can write into the buffer and if so, set the pointer to
        // where the data will be written.
        if (offset >= length) {
            isc_throw(BufferOverflow, "attempt to read into area beyond end of "
                                      "TCP receive buffer");
        }
        void* buffer_start = static_cast<void*>(static_cast<uint8_t*>(data) + offset);

        // ... and kick off the read.
        socket_.async_receive(asio::buffer(buffer_start, length - offset), callback);

    } else {
        isc_throw(SocketNotOpen,
            "attempt to receive from a TCP socket that is not open");
    }
}

// Is the receive complete?

template <typename C> bool
TCPSocket<C>::receiveComplete(const void* data, size_t length) {

    bool complete = false;

    // If we have read at least two bytes, we can work out how much we should be
    // reading.
    if (length >= 2) {

        // Convert first two bytes to a count and check that the following data
        // is that length.
        // TODO: Should we check to see if we have received too much data?
        uint16_t expected = readUint16(data);
        complete = ((expected + 2) == length);
    }

    return (complete);
}

// Copy buffer less leading two bytes to the target buffer.

template <typename C> void
TCPSocket<C>::appendNormalizedData(const void* inbuf, size_t length,
                                   isc::dns::OutputBufferPtr outbuf)
{
    const uint8_t* bytebuff = static_cast<const uint8_t*>(inbuf);
    outbuf->writeData(bytebuff + 2, length - 2);
}

// Cancel I/O on the socket.  No-op if the socket is not open.

template <typename C> void
TCPSocket<C>::cancel() {
    if (isopen_) {
        socket_.cancel();
    }
}

// Close the socket down.  Can only do this if the socket is open and we are
// managing it ourself.

template <typename C> void
TCPSocket<C>::close() {
    if (isopen_ && socket_ptr_) {
        socket_.close();
        isopen_ = false;
    }
}

} // namespace asiolink

#endif // __TCP_SOCKET_H
