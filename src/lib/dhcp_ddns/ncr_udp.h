// Copyright (C) 2013-2020 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef NCR_UDP_LISTENER_H
#define NCR_UDP_LISTENER_H

/// @file ncr_udp.h
/// @brief This file provides UDP socket based implementation for sending and
/// receiving NameChangeRequests
///
/// These classes are derived from the abstract classes, NameChangeListener
/// and NameChangeSender (see ncr_io.h).
///
/// The following discussion will refer to three layers of communications:
///
///    * Application layer - This is the business layer which needs to
///    transport NameChangeRequests, and is unaware of the means by which
///    they are transported.
///
///    * IO layer - This is the low-level layer that is directly responsible
///    for sending and receiving data asynchronously and is supplied through
///    other libraries.  This layer is largely unaware of the nature of the
///    data being transmitted.  In other words, it doesn't know beans about
///    NCRs.
///
///    * NameChangeRequest layer - This is the layer which acts as the
///    intermediary between the Application layer and the IO layer.  It must
///    be able to move NameChangeRequests to the IO layer as raw data and move
///    raw data from the IO layer in the Application layer as
///    NameChangeRequests.
///
/// This file defines NameChangeUDPListener class for receiving NCRs, and
/// NameChangeUDPSender for sending NCRs.
///
/// Both the listener and sender implementations utilize the same underlying
/// construct to move NCRs to and from a UDP socket. This construct consists
/// of a set of classes centered around isc::asiolink::UDPSocket.  UDPSocket
/// is a templated class that supports asio asynchronous event processing; and
/// which accepts as its parameter, the name of a callback class.
///
/// The asynchronous services provided by UDPSocket typically accept a buffer
/// for transferring data (either in or out depending on the service direction)
/// and an object which supplies a callback to invoke upon completion of the
/// service.
///
/// The callback class must provide an operator() with the following signature:
/// @code
///    void operator ()(const boost::system::error_code error_code,
///                     const size_t bytes_transferred);
/// @endcode
///
/// Upon completion of the service, the callback instance's operator() is
/// invoked by the asio layer.  It is given both a outcome result and the
/// number of bytes either read or written, to or from the buffer supplied
/// to the service.
///
/// Typically, an asiolink based implementation would simply implement the
/// callback operator directly.  However, the nature of the asiolink library
/// is such that the callback object may be copied several times during course
/// of a service invocation.  This implies that any class being used as a
/// callback class must be copyable.  This is not always desirable.  In order
/// to separate the callback class from the NameChangeRequest, the construct
/// defines the UDPCallback class for use as a copyable, callback object.
///
/// The UDPCallback class provides the asiolink layer callback operator(),
/// which is invoked by the asiolink layer upon service completion.  It
/// contains:
///    * a pointer to the transfer buffer
///    * the capacity of the transfer buffer
///    * a IO layer outcome result
///    * the number of bytes transferred
///    * a method pointer to a NameChangeRequest layer completion handler
///
/// This last item, is critical. It points to an instance method that
/// will be invoked by the UDPCallback operator.  This provides access to
/// the outcome of the service call to the NameChangeRequest layer without
/// that layer being used as the actual callback object.
///
/// The completion handler method signature is codified in the typedef,
/// UDPCompletionHandler, and must be as follows:
///
/// @code
///     void(const bool, const UDPCallback*)
/// @endcode
///
/// Note that is accepts two parameters.  The first is a boolean indicator
/// which indicates if the service call completed successfully or not.  The
/// second is a pointer to the callback object invoked by the IOService upon
/// completion of the service.  The callback instance will contain all of the
/// pertinent information about the invocation and outcome of the service.
///
/// Using the contents of the callback, it is the responsibility of the
/// UDPCompletionHandler to interpret the results of the service invocation and
/// pass the interpretation to the application layer via either
/// NameChangeListener::invokeRecvHandler in the case of the UDP listener, or
/// NameChangeSender::invokeSendHandler in the case of UDP sender.
///

#include <asiolink/asio_wrapper.h>
#include <asiolink/io_address.h>
#include <asiolink/io_service.h>
#include <asiolink/udp_endpoint.h>
#include <asiolink/udp_socket.h>
#include <dhcp_ddns/ncr_io.h>
#include <util/buffer.h>
#include <util/watch_socket.h>

#include <boost/shared_array.hpp>


/// responsibility of the completion handler to perform the steps necessary
/// to interpret the raw data provided by the service outcome.   The
/// UDPCallback operator implementation is mostly a pass through.
///
namespace isc {
namespace dhcp_ddns {

/// @brief Thrown when a UDP level exception occurs.
class NcrUDPError : public isc::Exception {
public:
    NcrUDPError(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) { };
};

class UDPCallback;
/// @brief Defines a function pointer for NameChangeRequest completion handlers.
typedef std::function<void(const bool, const UDPCallback*)>
          UDPCompletionHandler;

/// @brief Defines a dynamically allocated shared array.
typedef boost::shared_array<uint8_t> RawBufferPtr;

typedef boost::shared_ptr<asiolink::UDPEndpoint> UDPEndpointPtr;

/// @brief Implements the callback class passed into UDPSocket calls.
///
/// It serves as the link between the asiolink::UDPSocket asynchronous services
/// and the NameChangeRequest layer. The class provides the asiolink layer
/// callback operator(), which is invoked by the asiolink layer upon service
/// completion.  It contains all of the data pertinent to both the invocation
/// and completion of a service, as well as a pointer to NameChangeRequest
/// layer completion handler to invoke.
///
class UDPCallback {

public:
    /// @brief Container class which stores service invocation related data.
    ///
    /// Because the callback object may be copied numerous times during the
    /// course of service invocation, it does not directly contain data values.
    /// Rather it will retain a shared pointer to an instance of this structure
    /// thus ensuring that all copies of the callback object, ultimately refer
    /// to the same data values.
    struct Data {

        /// @brief Constructor
        ///
        /// @param buffer is a pointer to the data transfer buffer. This is
        /// the buffer data will be written to on a read, or read from on a
        /// send.
        /// @param buf_size is the capacity of the buffer
        /// @param data_source storage for UDP endpoint which supplied the data
        Data(RawBufferPtr& buffer, const size_t buf_size,
             UDPEndpointPtr& data_source)
            : buffer_(buffer), buf_size_(buf_size), data_source_(data_source),
              put_len_(0), error_code_(), bytes_transferred_(0) {
        };

        /// @brief A pointer to the data transfer buffer.
        RawBufferPtr buffer_;

        /// @brief Storage capacity of the buffer.
        size_t buf_size_;

        /// @brief The UDP endpoint that is the origin of the data transferred.
        UDPEndpointPtr data_source_;

        /// @brief Stores this size of the data within the buffer when written
        /// there manually. (See UDPCallback::putData()) .
        size_t put_len_;

        /// @brief Stores the IO layer result code of the completed IO service.
        boost::system::error_code error_code_;

        /// @brief Stores the number of bytes transferred by completed IO
        /// service.
        /// For a read it is the number of bytes written into the
        /// buffer.  For a write it is the number of bytes read from the
        /// buffer.
        size_t bytes_transferred_;

    };

    /// @brief Used as the callback object for UDPSocket services.
    ///
    /// @param buffer is a pointer to the data transfer buffer. This is
    /// the buffer data will be written to on a read, or read from on a
    /// send.
    /// @param buf_size is the capacity of the buffer
    /// @param data_source storage for UDP endpoint which supplied the data
    /// @param handler is a method pointer to the completion handler that
    /// is to be called by the operator() implementation.
    ///
    /// @throw NcrUDPError if either the handler or buffer pointers
    /// are invalid.
    UDPCallback (RawBufferPtr& buffer, const size_t buf_size,
                 UDPEndpointPtr& data_source,
                 const UDPCompletionHandler& handler);

    /// @brief Operator that will be invoked by the asiolink layer.
    ///
    /// @param error_code is the IO layer result code of the
    /// completed IO service.
    /// @param bytes_transferred is the number of bytes transferred by
    /// completed IO.
    /// For a read it is the number of bytes written into the
    /// buffer.  For a write it is the number of bytes read from the
    /// buffer.
    void operator ()(const boost::system::error_code error_code,
                     const size_t bytes_transferred);

    /// @brief Returns the number of bytes transferred by the completed IO
    /// service.
    ///
    /// For a read it is the number of bytes written into the
    /// buffer.  For a write it is the number of bytes read from the
    /// buffer.
    size_t getBytesTransferred() const {
        return (data_->bytes_transferred_);
    }

    /// @brief Sets the number of bytes transferred.
    ///
    /// @param value is the new value to assign to bytes transferred.
    void setBytesTransferred(const size_t value) {
        data_->bytes_transferred_ = value;
    }

    /// @brief Returns the completed IO layer service outcome status.
    boost::system::error_code getErrorCode() const {
        return (data_->error_code_);
    }

    /// @brief Sets the completed IO layer service outcome status.
    ///
    /// @param value is the new value to assign to outcome status.
    void setErrorCode(const boost::system::error_code value) {
        data_->error_code_  = value;
    }

    /// @brief Returns the data transfer buffer.
    RawBufferPtr getBuffer() const {
        return (data_->buffer_);
    }

    /// @brief Returns the data transfer buffer capacity.
    size_t getBufferSize() const {
        return (data_->buf_size_);
    }

    /// @brief Returns a pointer the data transfer buffer content.
    const uint8_t* getData() const {
        return (data_->buffer_.get());
    }

    /// @brief Copies data into the data transfer buffer.
    ///
    /// Copies the given number of bytes from the given source buffer
    /// into the data transfer buffer, and updates the value of put length.
    /// This method may be used when performing sends to make a copy of
    /// the "raw data" that was shipped (or attempted) accessible to the
    /// upstream callback.
    ///
    /// @param src is a pointer to the data source from which to copy
    /// @param len is the number of bytes to copy
    ///
    /// @throw NcrUDPError if the number of bytes to copy exceeds
    /// the buffer capacity or if the source pointer is invalid.
    void putData(const uint8_t* src, size_t len);

    /// @brief Returns the number of bytes manually written into the
    /// transfer buffer.
    size_t getPutLen() const {
        return (data_->put_len_);
    }

    /// @brief Sets the data source to the given endpoint.
    ///
    /// @param endpoint is the new value to assign to data source.
    void setDataSource(UDPEndpointPtr& endpoint) {
        data_->data_source_ = endpoint;
    }

    /// @brief Returns the UDP endpoint that provided the transferred data.
    const UDPEndpointPtr& getDataSource() {
        return (data_->data_source_);
    }

  private:
    /// @brief NameChangeRequest layer completion handler to invoke.
    UDPCompletionHandler handler_;

    /// @brief Shared pointer to the service data container.
    boost::shared_ptr<Data> data_;
};

/// @brief Convenience type for UDP socket based listener
typedef isc::asiolink::UDPSocket<UDPCallback> NameChangeUDPSocket;

/// @brief Provides the ability to receive NameChangeRequests via  UDP socket
///
/// This class is a derivation of the NameChangeListener which is capable of
/// receiving NameChangeRequests through a UDP socket.  The caller need only
/// supply network addressing and a RequestReceiveHandler instance to receive
/// NameChangeRequests asynchronously.
class NameChangeUDPListener : public NameChangeListener {
public:
    /// @brief Defines the maximum size packet that can be received.
    static const size_t RECV_BUF_MAX = isc::asiolink::
                                       UDPSocket<UDPCallback>::MIN_SIZE;

    /// @brief Constructor
    ///
    /// @param ip_address is the network address on which to listen
    /// @param port is the UDP port on which to listen
    /// @param format is the wire format of the inbound requests. Currently
    /// only JSON is supported
    /// @param ncr_recv_handler the receive handler object to notify when
    /// a receive completes.
    /// @param reuse_address enables IP address sharing when true
    /// It defaults to false.
    ///
    /// @throw base class throws NcrListenerError if handler is invalid.
    NameChangeUDPListener(const isc::asiolink::IOAddress& ip_address,
                          const uint32_t port,
                          const NameChangeFormat format,
                          RequestReceiveHandler& ncr_recv_handler,
                          const bool reuse_address = false);

    /// @brief Destructor.
    virtual ~NameChangeUDPListener();

    /// @brief Opens a UDP socket using the given IOService.
    ///
    /// Creates a NameChangeUDPSocket bound to the listener's ip address
    /// and port, that is monitored by the given IOService instance.
    ///
    /// @param io_service the IOService which will monitor the socket.
    ///
    /// @throw NcrUDPError if the open fails.
    virtual void open(isc::asiolink::IOService& io_service);

    /// @brief Closes the UDPSocket.
    ///
    /// It first invokes the socket's cancel method which should stop any
    /// pending read and remove the socket callback from the IOService. It
    /// then calls the socket's close method to actually close the socket.
    ///
    /// @throw NcrUDPError if the open fails.
    virtual void close();

    /// @brief Initiates an asynchronous read on the socket.
    ///
    /// Invokes the asyncReceive() method on the socket passing in the
    /// recv_callback_ member's transfer buffer as the receive buffer, and
    /// recv_callback_ itself as the callback object.
    ///
    /// @throw NcrUDPError if the open fails.
    void doReceive();

    /// @brief Implements the NameChangeRequest level receive completion
    /// handler.
    ///
    /// This method is invoked by the UPDCallback operator() implementation,
    /// passing in the boolean success indicator and pointer to itself.
    ///
    /// If the indicator denotes success, then the method will attempt to
    /// to construct a NameChangeRequest from the received data.  If the
    /// construction was successful, it will send the new NCR to the
    /// application layer by calling invokeRecvHandler() with a success
    /// status and a pointer to the new NCR.
    ///
    /// If the buffer contains invalid data such that construction fails,
    /// the method will log the failure and then call doReceive() to start a
    /// initiate the next receive.
    ///
    /// If the indicator denotes failure the method will log the failure and
    /// notify the application layer by calling invokeRecvHandler() with
    /// an error status and an empty pointer.
    ///
    /// @param successful boolean indicator that should be true if the
    /// socket receive completed without error, false otherwise.
    /// @param recv_callback pointer to the callback instance which handled
    /// the socket receive completion.
    void receiveCompletionHandler(const bool successful,
                                  const UDPCallback* recv_callback);
private:
    /// @brief IP address on which to listen for requests.
    isc::asiolink::IOAddress ip_address_;

    /// @brief Port number on which to listen for requests.
    uint32_t port_;

    /// @brief Wire format of the inbound requests.
    NameChangeFormat format_;

    /// @brief Low level socket underneath the listening socket
    boost::shared_ptr<boost::asio::ip::udp::socket> asio_socket_;

    /// @brief NameChangeUDPSocket listening socket
    boost::shared_ptr<NameChangeUDPSocket> socket_;

    /// @brief Pointer to the receive callback
    boost::shared_ptr<UDPCallback> recv_callback_;

    /// @brief Flag which enables the reuse address socket option if true.
    bool reuse_address_;

    ///
    /// @name Copy and constructor assignment operator
    ///
    /// The copy constructor and assignment operator are private to avoid
    /// potential issues with multiple listeners attempting to share sockets
    /// and callbacks.
private:
    NameChangeUDPListener(const NameChangeUDPListener& source);
    NameChangeUDPListener& operator=(const NameChangeUDPListener& source);
    //@}
};


/// @brief Provides the ability to send NameChangeRequests via  UDP socket
///
/// This class is a derivation of the NameChangeSender which is capable of
/// sending NameChangeRequests through a UDP socket.  The caller need only
/// supply network addressing and a RequestSendHandler instance to send
/// NameChangeRequests asynchronously.
class NameChangeUDPSender : public NameChangeSender {
public:

    /// @brief Defines the maximum size packet that can be sent.
    static const size_t SEND_BUF_MAX =  NameChangeUDPListener::RECV_BUF_MAX;

    /// @brief Constructor
    ///
    /// @param ip_address the IP address from which to send
    /// @param port the port from which to send
    /// @param server_address the IP address of the target listener
    /// @param server_port is the IP port  of the target listener
    /// @param format is the wire format of the outbound requests.
    /// @param ncr_send_handler the send handler object to notify when
    /// when a send completes.
    /// @param send_que_max sets the maximum number of entries allowed in
    /// the send queue.
    /// It defaults to NameChangeSender::MAX_QUEUE_DEFAULT
    /// @param reuse_address enables IP address sharing when true
    /// It defaults to false.
    ///
    NameChangeUDPSender(const isc::asiolink::IOAddress& ip_address,
        const uint32_t port, const isc::asiolink::IOAddress& server_address,
        const uint32_t server_port, const NameChangeFormat format,
        RequestSendHandler& ncr_send_handler,
        const size_t send_que_max = NameChangeSender::MAX_QUEUE_DEFAULT,
        const bool reuse_address = false);

    /// @brief Destructor
    virtual ~NameChangeUDPSender();


    /// @brief Opens a UDP socket using the given IOService.
    ///
    /// Creates a NameChangeUDPSocket bound to the sender's IP address
    /// and port, that is monitored by the given IOService instance.
    ///
    /// @param io_service the IOService which will monitor the socket.
    ///
    /// @throw NcrUDPError if the open fails.
    virtual void open(isc::asiolink::IOService& io_service);


    /// @brief Closes the UDPSocket.
    ///
    /// It first invokes the socket's cancel method which should stop any
    /// pending send and remove the socket callback from the IOService. It
    /// then calls the socket's close method to actually close the socket.
    ///
    /// @throw NcrUDPError if the open fails.
    virtual void close();

    /// @brief Sends a given request asynchronously over the socket
    ///
    /// The given NameChangeRequest is converted to wire format and copied
    /// into the send callback's transfer buffer.  Then the socket's
    /// asyncSend() method is called, passing in send_callback_ member's
    /// transfer buffer as the send buffer and the send_callback_ itself
    /// as the callback object.
    /// @param ncr NameChangeRequest to send.
    virtual void doSend(NameChangeRequestPtr& ncr);

    /// @brief Implements the NameChangeRequest level send completion handler.
    ///
    /// This method is invoked by the UDPCallback operator() implementation,
    /// passing in the boolean success indicator and pointer to itself.
    ///
    /// If the indicator denotes success, then the method will notify the
    /// application layer by calling invokeSendHandler() with a success
    /// status.
    ///
    /// If the indicator denotes failure the method will log the failure and
    /// notify the application layer by calling invokeRecvHandler() with
    /// an error status.
    ///
    /// @param successful boolean indicator that should be true if the
    /// socket send completed without error, false otherwise.
    /// @param send_callback pointer to the callback instance which handled
    /// the socket receive completion.
    void sendCompletionHandler(const bool successful,
                               const UDPCallback* send_callback);

    /// @brief Returns a file descriptor suitable for use with select
    ///
    /// The value returned is an open file descriptor which can be used with
    /// select() system call to monitor the sender for IO events.  This allows
    /// NameChangeUDPSenders to be used in applications which use select,
    /// rather than IOService to wait for IO events to occur.
    ///
    /// @warning Attempting other use of this value may lead to unpredictable
    /// behavior in the sender.
    ///
    /// @return Returns an "open" file descriptor
    ///
    /// @throw NcrSenderError if the sender is not in send mode,
    virtual int getSelectFd();

    /// @brief Returns whether or not the sender has IO ready to process.
    ///
    /// @return true if the sender has at IO ready, false otherwise.
    virtual bool ioReady();

private:

    /// @brief Closes watch socket if the socket is open.
    ///
    /// This method closes watch socket if its instance exists and if the
    /// socket is open. An error message is logged when this operation fails.
    void closeWatchSocket();

    /// @brief IP address from which to send.
    isc::asiolink::IOAddress ip_address_;

    /// @brief Port from which to send.
    uint32_t port_;

    /// @brief IP address of the target listener.
    isc::asiolink::IOAddress server_address_;

    /// @brief Port of the target listener.
    uint32_t server_port_;

    /// @brief Wire format of the outbound requests.
    NameChangeFormat format_;

    /// @brief Low level socket underneath the sending socket.
    boost::shared_ptr<boost::asio::ip::udp::socket> asio_socket_;

    /// @brief NameChangeUDPSocket sending socket.
    boost::shared_ptr<NameChangeUDPSocket> socket_;

    /// @brief Endpoint of the target listener.
    boost::shared_ptr<isc::asiolink::UDPEndpoint> server_endpoint_;

    /// @brief Pointer to the send callback
    boost::shared_ptr<UDPCallback> send_callback_;

    /// @brief Flag which enables the reuse address socket option if true.
    bool reuse_address_;

    /// @brief Pointer to WatchSocket instance supplying the "select-fd".
    util::WatchSocketPtr watch_socket_;
};

} // namespace isc::dhcp_ddns
} // namespace isc

#endif
