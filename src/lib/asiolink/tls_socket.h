// Copyright (C) 2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef TLS_SOCKET_H
#define TLS_SOCKET_H

#ifndef BOOST_ASIO_HPP
#error "asio.hpp must be included before including this, see asiolink.h as to why"
#endif

#include <asiolink/crypto_tls.h>
#include <asiolink/tcp_socket.h>

#include <boost/noncopyable.hpp>

namespace isc {
namespace asiolink {

/// @brief The @c TLSSocket class is a concrete derived class of @c IOAsioSocket
/// that represents a TLS socket.
///
/// @tparam C Callback type.
template <typename C>
class TLSSocket : public IOAsioSocket<C>, private boost::noncopyable {
public:

    /// @brief Constructor from a TLS stream.
    ///
    /// It is assumed that the caller will open and close the stream,
    /// so these operations are a no-op for that stream.
    ///
    /// @param stream The TLS stream.
    TLSSocket(TlsStream<C>& stream);

    /// @brief Constructor.
    ///
    /// Used when the TLSSocket is being asked to manage its own internal
    /// socket.  In this case, the open() and close() methods are used.
    ///
    /// @param service I/O Service object used to manage the socket.
    /// @param context Pointer to TLS context.
    TLSSocket(IOService& service, TlsContextPtr context);

    /// @brief Destructor.
    virtual ~TLSSocket() { }

    /// @brief Return file descriptor of underlying socket.
    virtual int getNative() const {
#if BOOST_VERSION < 106600
        return (socket_.native());
#else
        return (socket_.native_handle());
#endif
    }

    /// @brief Return protocol of socket.
    virtual int getProtocol() const {
        return (IPPROTO_TCP);
    }

    /// @brief Is "open()" synchronous predicate.
    ///
    /// Indicates that the opening of a TLS socket is asynchronous.
    virtual bool isOpenSynchronous() const {
        return (false);
    }

    /// @brief Checks if the connection is usable.
    ///
    /// The connection is usable if the socket is open and the peer has not
    /// closed its connection.
    ///
    /// @return true if the connection is usable.
    bool isUsable() const {
        // If the socket is open it doesn't mean that it is still
        // usable. The connection could have been closed on the other
        // end. We have to check if we can still use this socket.
        if (socket_.is_open()) {
            // Remember the current non blocking setting.
            const bool non_blocking_orig = socket_.non_blocking();

            // Set the socket to non blocking mode. We're going to
            // test if the socket returns would_block status on the
            // attempt to read from it.
            socket_.non_blocking(true);

            // Use receive with message peek flag to avoid removing
            // the data awaiting to be read.
            char data[2];
            int err = 0;
            int cc = recv(getNative(), data, sizeof(data), MSG_PEEK);
            if (cc < 0) {
                // Error case.
                err = errno;
            } else if (cc == 0) {
                // End of file.
                err = -1;
            }

            // Revert the original non_blocking flag on the socket.
            socket_.non_blocking(non_blocking_orig);

            // If the connection is alive we'd typically get
            // would_block status code.  If there are any data that
            // haven't been read we may also get success status. We're
            // guessing that try_again may also be returned by some
            // implementations in some situations. Any other error
            // code indicates a problem with the connection so we
            // assume that the connection has been closed.
            return ((err == 0) || (err == EAGAIN) || (err == EWOULDBLOCK));
        }

        return (false);
    }

    /// @brief Open Socket.
    ///
    /// Opens the TLS socket.  This is an asynchronous operation, completion of
    /// which will be signalled via a call to the callback function.
    ///
    /// @param endpoint Endpoint to which the socket will connect.
    /// @param callback Callback object.
    virtual void open(const IOEndpoint* endpoint, C& callback);

    /// @brief Perform Handshake.
    ///
    /// Perform the TLS handshake. This is an asynchronous operation,
    /// completion of which will be signalled via a call to the callback
    /// function.
    ///
    /// @param callback Callback object.
    virtual void handshake(C& callback);

    /// @brief Send Asynchronously.
    ///
    /// Calls the underlying socket's async_send() method to send a
    /// packet of data asynchronously to the remote endpoint.  The
    /// callback will be called on completion.
    ///
    /// @param data Data to send.
    /// @param length Length of data to send.
    /// @param endpoint Target of the send. (Unused for a TLS socket because
    /// that was determined when the connection was opened.)
    /// @param callback Callback object.
    /// @throw BufferTooLarge on attempt to send a buffer larger than 64kB.
    virtual void asyncSend(const void* data, size_t length,
                           const IOEndpoint* endpoint, C& callback);

    /// @brief Send Asynchronously without count.
    ///
    /// This variant of the method sends data over the TLS socket without
    /// preceding the data with a data count. Eventually, we should migrate
    /// the virtual method to not insert the count but there are existing
    /// classes using the count. Once this migration is done, the existing
    /// virtual method should be replaced by this method.
    ///
    /// @param data Data to send.
    /// @param length Length of data to send.
    /// @param callback Callback object.
    /// @throw BufferTooLarge on attempt to send a buffer larger than 64kB.
    void asyncSend(const void* data, size_t length, C& callback);

    /// @brief Receive Asynchronously.
    ///
    /// Calls the underlying socket's async_receive() method to read a packet
    /// of data from a remote endpoint.  Arrival of the data is signalled via a
    /// call to the callback function.
    ///
    /// @param data Buffer to receive incoming message.
    /// @param length Length of the data buffer.
    /// @param offset Offset into buffer where data is to be put.
    /// @param endpoint Source of the communication.
    /// @param callback Callback object.
    virtual void asyncReceive(void* data, size_t length, size_t offset,
                              IOEndpoint* endpoint, C& callback);

    /// @brief Process received data packet.
    ///
    /// See the description of IOAsioSocket::receiveComplete for a complete
    /// description of this method.
    ///
    /// @param staging Pointer to the start of the staging buffer.
    /// @param length Amount of data in the staging buffer.
    /// @param cumulative Amount of data received before the staging buffer is
    /// processed.
    /// @param offset Unused.
    /// @param expected unused.
    /// @param outbuff Output buffer.  Data in the staging buffer is be copied
    ///        to this output buffer in the call.
    ///
    /// @return Always true.
    virtual bool processReceivedData(const void* staging, size_t length,
                                     size_t& cumulative, size_t& offset,
                                     size_t& expected,
                                     isc::util::OutputBufferPtr& outbuff);

    /// @brief Cancel I/O On Socket.
    virtual void cancel();

    /// @brief Close socket.
    virtual void close();

    /// @brief TLS shutdown.
    ///
    /// The callback is called on completion i.e. when the peer performs
    /// a shutdown or a close.
    virtual void shutdown(C& callback);

    /// @brief Returns reference to the underlying ASIO socket.
    ///
    /// @return Reference to underlying ASIO socket.
    virtual typename TlsStream<C>::lowest_layer_type& getASIOSocket() const {
        return (socket_);
    }

    /// @brief Returns reference to the underlying TLS stream.
    ///
    /// @return Reference to underlying TLS stream.
    virtual TlsStream<C>& getTlsStream() const {
        return (stream_);
    }

private:
    /// Two variables to hold the stream - a stream and a pointer to it.  This
    /// handles the case where a stream is passed to the TLSSocket on
    /// construction, or where it is asked to manage its own stream.

    /// @brief Pointer to own stream.
    std::unique_ptr<TlsStream<C>> stream_ptr_;

    /// @brief TLS stream.
    TlsStream<C>& stream_;

    /// @brief Underlying TCP socket.
    typename TlsStream<C>::lowest_layer_type& socket_;

    /// @todo Remove temporary buffer
    /// The current implementation copies the buffer passed to asyncSend() into
    /// a temporary buffer and precedes it with a two-byte count field.  As
    /// ASIO should really be just about sending and receiving data, the TCP
    /// code should not do this.  If the protocol using this requires a two-byte
    /// count, it should add it before calling this code.  (This may be best
    /// achieved by altering isc::dns::buffer to have pairs of methods:
    /// getLength()/getTCPLength(), getData()/getTCPData(), with the getTCPXxx()
    /// methods taking into account a two-byte count field.)
    ///
    /// The option of sending the data in two operations, the count followed by
    /// the data was discounted as that would lead to two callbacks which would
    /// cause problems with the stackless coroutine code.

    /// @brief Send buffer.
    isc::util::OutputBufferPtr send_buffer_;
};

// Constructor - caller manages socket.

template <typename C>
TLSSocket<C>::TLSSocket(TlsStream<C>& stream) :
    stream_ptr_(), stream_(stream),
    socket_(stream_.lowest_layer()), send_buffer_() {
}

// Constructor - create socket on the fly.

template <typename C>
TLSSocket<C>::TLSSocket(IOService& service, TlsContextPtr context) :
    stream_ptr_(new TlsStream<C>(service, context)),
    stream_(*stream_ptr_), socket_(stream_.lowest_layer()), send_buffer_()
{
}

// Open the socket.

template <typename C> void
TLSSocket<C>::open(const IOEndpoint* endpoint, C& callback) {
    // Ignore opens on already-open socket.  Don't throw a failure because
    // of uncertainties as to what precedes when using asynchronous I/O.
    // Also allows us a treat a passed-in socket as a self-managed socket.
    if (!socket_.is_open()) {
        if (endpoint->getFamily() == AF_INET) {
            socket_.open(boost::asio::ip::tcp::v4());
        } else {
            socket_.open(boost::asio::ip::tcp::v6());
        }

        // Set options on the socket:

        // Reuse address - allow the socket to bind to a port even if the port
        // is in the TIMED_WAIT state.
        socket_.set_option(boost::asio::socket_base::reuse_address(true));
    }

    // Upconvert to a TCPEndpoint.  We need to do this because although
    // IOEndpoint is the base class of UDPEndpoint and TCPEndpoint, it does not
    // contain a method for getting at the underlying endpoint type - that is in
    /// the derived class and the two classes differ on return type.
    isc_throw_assert(endpoint->getProtocol() == IPPROTO_TCP);
    const TCPEndpoint* tcp_endpoint =
        static_cast<const TCPEndpoint*>(endpoint);

    // Connect to the remote endpoint.  On success, the handler will be
    // called (with one argument - the length argument will default to
    // zero).
    socket_.async_connect(tcp_endpoint->getASIOEndpoint(), callback);
}

// Perform the handshake.

template <typename C> void
TLSSocket<C>::handshake(C& callback) {
    if (!socket_.is_open()) {
        isc_throw(SocketNotOpen, "attempt to perform handshake on "
                  "a TLS socket that is not open");
    }
    stream_.handshake(callback);
}

// Send a message.  Should never do this if the socket is not open, so throw
// an exception if this is the case.

template <typename C> void
TLSSocket<C>::asyncSend(const void* data, size_t length, C& callback)
{
    if (!socket_.is_open()) {
        isc_throw(SocketNotOpen,
                  "attempt to send on a TLS socket that is not open");
    }

    try {
        send_buffer_.reset(new isc::util::OutputBuffer(length));
        send_buffer_->writeData(data, length);

        // Send the data.
        boost::asio::async_write(stream_,
                                 boost::asio::buffer(send_buffer_->getData(),
                                                     send_buffer_->getLength()),
                                 callback);
    } catch (const boost::numeric::bad_numeric_cast&) {
        isc_throw(BufferTooLarge,
                  "attempt to send buffer larger than 64kB");
    }
}

template <typename C> void
TLSSocket<C>::asyncSend(const void* data, size_t length,
                        const IOEndpoint*, C& callback)
{
    if (!socket_.is_open()) {
        isc_throw(SocketNotOpen,
                  "attempt to send on a TLS socket that is not open");
    }

    /// Need to copy the data into a temporary buffer and precede it with
    /// a two-byte count field.
    /// @todo arrange for the buffer passed to be preceded by the count
    try {
        // Ensure it fits into 16 bits
        uint16_t count = boost::numeric_cast<uint16_t>(length);

        // Copy data into a buffer preceded by the count field.
        send_buffer_.reset(new isc::util::OutputBuffer(length + 2));
        send_buffer_->writeUint16(count);
        send_buffer_->writeData(data, length);

        // ... and send it
        boost::asio::async_write(stream_,
                                 boost::asio::buffer(send_buffer_->getData(),
                                                     send_buffer_->getLength()),
                                 callback);
    } catch (const boost::numeric::bad_numeric_cast&) {
        isc_throw(BufferTooLarge,
                  "attempt to send buffer larger than 64kB");
    }
}

// Receive a message. Note that the "offset" argument is used as an index
// into the buffer in order to decide where to put the data.  It is up to the
// caller to initialize the data to zero
template <typename C> void
TLSSocket<C>::asyncReceive(void* data, size_t length, size_t offset,
                           IOEndpoint* endpoint, C& callback)
{
    if (!socket_.is_open()) {
        isc_throw(SocketNotOpen,
                  "attempt to receive from a TLS socket that is not open");
    }

    // Upconvert to a TCPEndpoint.  We need to do this because although
    // IOEndpoint is the base class of UDPEndpoint and TCPEndpoint, it
    // does not contain a method for getting at the underlying endpoint
    // type - that is in the derived class and the two classes differ on
    // return type.
    isc_throw_assert(endpoint->getProtocol() == IPPROTO_TCP);
    TCPEndpoint* tcp_endpoint = static_cast<TCPEndpoint*>(endpoint);

    // Write the endpoint details from the communications link.  Ideally
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
    void* buffer_start =
        static_cast<void*>(static_cast<uint8_t*>(data) + offset);

    // ... and kick off the read.
    stream_.async_read_some(boost::asio::buffer(buffer_start, length - offset),
                            callback);
}

// Is the receive complete?

template <typename C> bool
TLSSocket<C>::processReceivedData(const void* staging, size_t length,
                                  size_t& cumulative, size_t& offset,
                                  size_t& expected,
                                  isc::util::OutputBufferPtr& outbuff)
{
    // Point to the data in the staging buffer and note how much there is.
    const uint8_t* data = static_cast<const uint8_t*>(staging);
    size_t data_length = length;

    // Is the number is "expected" valid?  It won't be unless we have received
    // at least two bytes of data in total for this set of receives.
    if (cumulative < 2) {

        // "expected" is not valid.  Did this read give us enough data to
        // work it out?
        cumulative += length;
        if (cumulative < 2) {

            // Nope, still not valid.  This must have been the first packet and
            // was only one byte long.  Tell the fetch code to read the next
            // packet into the staging buffer beyond the data that is already
            // there so that the next time we are called we have a complete
            // TCP count.
            offset = cumulative;
            return (false);
        }

        // Have enough data to interpret the packet count, so do so now.
        expected = isc::util::readUint16(data, cumulative);

        // We have two bytes less of data to process.  Point to the start of the
        // data and adjust the packet size.  Note that at this point,
        // "cumulative" is the true amount of data in the staging buffer, not
        // "length".
        data += 2;
        data_length = cumulative - 2;
    } else {

        // Update total amount of data received.
        cumulative += length;
    }

    // Regardless of anything else, the next read goes into the start of the
    // staging buffer.
    offset = 0;

    // Work out how much data we still have to put in the output buffer. (This
    // could be zero if we have just interpreted the TCP count and that was
    // set to zero.)
    if (expected >= outbuff->getLength()) {

        // Still need data in the output packet.  Copy what we can from the
        // staging buffer to the output buffer.
        size_t copy_amount = std::min(expected - outbuff->getLength(),
                                      data_length);
        outbuff->writeData(data, copy_amount);
    }

    // We can now say if we have all the data.
    return (expected == outbuff->getLength());
}

// Cancel I/O on the socket.  No-op if the socket is not open.

template <typename C> void
TLSSocket<C>::cancel() {
    if (socket_.is_open()) {
        socket_.cancel();
    }
}

// TLS shutdown.  Can be used for orderly close.

template <typename C> void
TLSSocket<C>::shutdown(C& callback) {
    if (!socket_.is_open()) {
        isc_throw(SocketNotOpen, "attempt to perform shutdown on "
                  "a TLS socket that is not open");
    }
    stream_.shutdown(callback);
}

// Close the socket down.  Can only do this if the socket is open and we are
// managing it ourself.

template <typename C> void
TLSSocket<C>::close() {
    if (socket_.is_open() && stream_ptr_) {
        socket_.close();
    }
}

} // namespace asiolink
} // namespace isc

#endif // TLS_SOCKET_H
