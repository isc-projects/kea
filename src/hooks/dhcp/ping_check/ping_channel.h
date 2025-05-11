// Copyright (C) 2023-2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef PING_CHANNEL_H
#define PING_CHANNEL_H

#include <asiolink/asio_wrapper.h>
#include <asiolink/io_address.h>
#include <asiolink/io_service.h>
#include <util/watch_socket.h>
#include <icmp_msg.h>
#include <icmp_socket.h>

#include <boost/scoped_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>

#include <iostream>
#include <mutex>

namespace isc {
namespace ping_check {

/// @brief Type of the function implementing a callback invoked by the
/// @c SocketCallback functor.
typedef std::function<void(boost::system::error_code ec, size_t length)> SocketCallbackFunction;

/// @brief Functor associated with the socket object.
///
/// This functor calls a callback function specified in the constructor.
class SocketCallback {
public:
    /// @brief Constructor.
    ///
    /// @param socket_callback Callback to be invoked by the functor upon
    /// an event associated with the socket.
    explicit inline SocketCallback(SocketCallbackFunction socket_callback)
        : callback_(socket_callback) {
    };

    /// @brief Operator called when event associated with a socket occurs.
    ///
    /// This operator returns immediately when received @c boost::system::error_code
    /// is equal to @c boost::asio::error::operation_aborted.
    ///
    /// @param ec Error code.
    /// @param length Data length.
    inline void operator()(boost::system::error_code ec, size_t length = 0) {
        if (ec.value() == boost::asio::error::operation_aborted) {
            return;
        }

        callback_(ec, length);
    };

private:
    /// @brief Supplied callback.
    SocketCallbackFunction callback_;
};

/// @brief Socket type for performing ICMP socket IO.
typedef ICMPSocket<SocketCallback> PingSocket;

/// @brief Defines a pointer to PingSocket.
typedef boost::shared_ptr<PingSocket> PingSocketPtr;

/// @brief Function type for callback that fetches next IOAddress to ping.
typedef std::function<bool(asiolink::IOAddress& target)> NextToSendCallback;

/// @brief Function type for callback to invoke upon ECHO send completion.
typedef std::function<void(ICMPMsgPtr& echo, bool send_failed)> EchoSentCallback;

/// @brief Function type for callback to invoke when an ICMP reply has been
/// received.
typedef std::function<void(ICMPMsgPtr& reply)> ReplyReceivedCallback;

/// @brief Function type for callback to invoke when the channel has shutdown.
typedef std::function<void()> ShutdownCallback;

/// @brief Provides thread-safe ICMP ECHO REQUEST/ECHO REPLY service
///
/// PingChannel uses a @ref PingSocket to send out ECHO REQUESTs and
/// receive ICMP replies.  It is thread-safe and can be driven either
/// with a single-threaded IOService or a multi-threaded
/// IOServiceThreadPool.  It uses series of callbacks to perpetually
/// send requests to target addresses and feed back replies received:
///
/// -# next_to_send_cb_  -  callback to invoke to fetch the next address to ping
/// -# echo_sent_cb_  - callback to invoke when an ECHO REQUEST has been sent out
/// -# reply_received_cb_ - callback to invoke when an ICMP reply has been received.
/// -# channel_shutdown_cb_ - callback to invoke when the channel has shutdown
///
/// Callback handlers are supplied via the PingChannel constructor. Higher order
/// functions are provided, that once instantiated, can be used by calling layers
/// to control the channel (e.g. open the channel, initiate reading, initiate
/// writing, and close the channel).
///
/// @note Callbacks handlers must be thread-safe if the channel is
/// driven by an IOServiceThreadPool.
///
class PingChannel : public boost::enable_shared_from_this<PingChannel> {
public:
    /// @brief Constructor
    ///
    /// Instantiates the channel with its socket closed.
    ///
    /// @param io_service pointer to the IOService instance that will manage
    /// the channel's IO. Must not be empty
    /// @param next_to_send_cb callback to invoke to fetch the next IOAddress
    /// to ping
    /// @param echo_sent_cb callback to invoke when an ECHO send has completed
    /// @param reply_received_cb callback to invoke when an ICMP reply has been
    /// received.  This callback is passed all inbound ICMP messages (e.g. ECHO
    /// REPLY, UNREACHABLE, etc...)
    /// @param shutdown_cb callback to invoke when the channel has shutdown due
    /// to an error
    ///
    /// @throw BadValue if io_service is empty.
    PingChannel(asiolink::IOServicePtr& io_service,
                NextToSendCallback next_to_send_cb,
                EchoSentCallback echo_sent_cb,
                ReplyReceivedCallback reply_received_cb,
                ShutdownCallback shutdown_cb = ShutdownCallback());

    /// @brief Destructor
    ///
    /// Closes the socket if its open.
    virtual ~PingChannel();

    /// @brief Opens the socket for communications
    ///
    /// (Re)Creates the @ref PingSocket instance and opens it.
    ///
    /// @throw Unexpected if the open fails.
    void open();

    /// @brief Indicates whether or not the channel socket is open.
    ///
    /// @return true if the socket is open.
    bool isOpen() const;

    // @brief Schedules the next send.
    //
    // If the socket is not currently sending it posts a call to @c sendNext()
    // to the channel's IOService.
    virtual void startSend();

    // @brief Schedules the next read.
    //
    // If the socket is not currently reading it posts a call to @c doRead()
    // to the channel's IOService.
    void startRead();

    /// @brief Closes the channel's socket.
    void close();

    /// @brief Fetches the channel's IOService
    ///
    /// @return pointer to the IOService.
    asiolink::IOServicePtr getIOService() {
        return (io_service_);
    }

protected:
    /// @brief Receive data on the socket asynchronously
    ///
    /// Calls the underlying socket's asyncReceive() method to read a
    /// packet of data from a remote endpoint.  Arrival of the data is signalled
    /// via a call to the callback function.
    ///
    /// This virtual function is provided as means to inject errors during
    /// read operations to facilitate testing.
    ///
    /// @param data buffer to receive incoming message
    /// @param length length of the data buffer
    /// @param offset offset into buffer where data is to be put
    /// @param endpoint source of the communication
    /// @param callback callback object
    virtual void asyncReceive(void* data, size_t length, size_t offset,
                              asiolink::IOEndpoint* endpoint, SocketCallback& callback);

    /// @brief Send data on the socket asynchronously
    ///
    /// Calls the underlying socket's asyncSend() method to send a
    /// packet of data from a remote endpoint.  Arrival of the data is signalled
    /// via a call to the callback function.
    ///
    /// This virtual function is provided as means to inject errors during
    /// write operations to facilitate testing.
    ///
    /// @param data buffer containing the data to send
    /// @param length length of the data buffer
    /// @param endpoint destination of the communication
    /// @param callback callback object
    virtual void asyncSend(void* data, size_t length, asiolink::IOEndpoint* endpoint,
                          SocketCallback& callback);

protected:
    /// @brief Initiates an asynchronous socket read.
    ///
    /// If the channel is able to read (is open, not stopping and not
    /// currently reading) it invokes @ref PingSocket::asyncReceive()
    /// otherwise it simply returns.  If the call to asyncReceive() fails
    /// it calls @c stopChannel() otherwise, when it completes it will
    /// invoke @c socketReadCallback().
    void doRead();

    /// @brief Socket read completion callback
    ///
    /// Invoked when PingSocket::asyncRead() completes.
    /// Upon read success and data received:
    ///
    /// -# Unpacks the wire data
    /// -# Pass the resultant ICMPMsg to reply received callback
    /// -# start next read
    ///
    /// On error conditions:
    ///
    /// -# Operation aborted: socket is shutting down, simply return
    /// -# Operation would block/try again: start a new read
    /// -# Any other error, shut down the channel
    ///
    /// @param ec error code indicating either success or the error encountered
    /// @param length number of bytes read
    void socketReadCallback(boost::system::error_code ec, size_t length);

    /// @brief Initiates sending the next ECHO REQUEST
    ///
    /// If the channel is able to send (i.e is open, not stopping and not
    /// currently writing):
    /// -# Invoke next to send callback to fetch the next target IP address
    /// -# If there is no next target, return
    /// -# Construct the ECHO REQUEST for the target and pack it into wire form
    /// -# Begin sending the request by passing to @c PingSocket::asyncSend()
    /// -# If the asyncSend() call fails shutdown the channel, otherwise when
    /// it completes it invokes @c socketWriteCallback().
    virtual void sendNext();

    /// @brief Socket write completion callback
    ///
    /// Invoked when PingSocket::asyncWrite() completes.
    /// Upon write success:
    ///
    /// -# Pass the ECHO REQUEST (i.e. echo_sent) to echo sent callback
    /// -# start next write
    ///
    /// On error conditions:
    ///
    /// -# Operation aborted: socket is shutting down, simply return
    /// -# Operation would block/try again: start a new write
    /// -# Any other error, shut down the channel
    ///
    /// @param echo_sent ECHO REQUEST that was written (or attempted to be
    /// written)
    /// @param ec error code indicating either success or the error encountered
    /// @param length number of bytes written
    void socketWriteCallback(ICMPMsgPtr echo_sent, boost::system::error_code ec,
                             size_t length);

    /// @brief Closes the socket channel and invokes the shutdown callback.
    ///
    /// This function is invoked to notify the calling layer that the socket
    /// has encountered an unrecoverable error and is stopping operations.
    void stopChannel();

    /// @brief returns the next unique ECHO instance number.
    ///
    /// This method generates and returns the next ECHO instance
    /// number by incrementing the current value.  It is a strictly
    /// monotonously increasing value beginning at 0x00010001.
    /// At roll over it resets to 0x00010001.
    ///
    /// Must be called in a thread-safe context
    ///
    /// @return the next unique instance number.
    static uint32_t nextEchoInstanceNum();

    /// @brief Indicates whether or not a send can be initiated.
    ///
    /// Must be called in a thread-safe context
    ///
    /// @return True if the socket is open, is not attempting to stop, and is
    /// not currently sending.
    bool canSend() {
        return (socket_ && socket_->isOpen() && !stopping_ && !sending_);
    }

    /// @brief Indicates whether or not a read can be initiated.
    ///
    /// Must be called in a thread-safe context
    ///
    /// @return True if the socket is open, is not attempting to stop, and is
    /// not currently reading.
    bool canRead() {
        return (socket_ && socket_->isOpen() && !stopping_ && !reading_);
    }

    /// @brief Returns input buffer size.
    ///
    /// Must be called in a thread-safe context
    ///
    /// @return size of the input buf
    size_t getInputBufSize() const;

    /// @brief Returns pointer to the first byte of the input buffer.
    ///
    /// Must be called in a thread-safe context
    ///
    /// @return pointer to the data buffer
    /// @throw InvalidOperation if called when the buffer is empty.
    unsigned char* getInputBufData();

    /// @brief IOService instance the drives socket IO
    asiolink::IOServicePtr io_service_;

    /// @brief Callback to invoke to fetch the next address to ping.
    NextToSendCallback next_to_send_cb_;

    /// @brief Callback to invoke when an ECHO write has completed.
    EchoSentCallback echo_sent_cb_;

    /// @brief Callback to invoke when an ICMP reply has been received.
    ReplyReceivedCallback reply_received_cb_;

    /// @brief Callback to invoke when the channel has shutdown.
    ShutdownCallback shutdown_cb_;

    /// @brief Socket through which to ping.
    PingSocketPtr socket_;

    /// @brief Buffer to hold the contents for most recent socket read.
    std::vector<uint8_t> input_buf_;

    /// @brief Retains the endpoint from which the most recent reply was received.
    ICMPEndpoint reply_endpoint_;

    /// @brief Indicates whether or not the socket has a read in progress.
    bool reading_;

    /// @brief Indicates whether or not the socket has a write in progress.
    bool sending_;

    /// @brief Indicates whether or not the channel has been told to stop.
    bool stopping_;

    /// @brief The mutex used to protect internal state.
    const boost::scoped_ptr<std::mutex> mutex_;

    /// @brief True if channel was opened in single-threaded mode, false
    /// otherwise.
    bool single_threaded_;

    /// @brief Pointer to WatchSocket instance supplying the "select-fd".
    util::WatchSocketPtr watch_socket_;

    /// @brief WatchSocket fd registered with IfaceMgr.
    int registered_write_fd_;

    /// @brief ICMPSocket fd registered with IfaceMgr.
    int registered_read_fd_;
};

/// @brief Defines a smart pointer to PingChannel
typedef boost::shared_ptr<PingChannel> PingChannelPtr;

} // end of namespace ping_check
} // end of namespace isc

#endif
