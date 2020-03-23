// Copyright (C) 2013-2020 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef NCR_IO_H
#define NCR_IO_H

/// @file ncr_io.h
/// @brief This file defines abstract classes for exchanging NameChangeRequests.
///
/// These classes are used for sending and receiving requests to update DNS
/// information for FQDNs embodied as NameChangeRequests (aka NCRs). Ultimately,
/// NCRs must move through the following three layers in order to implement
/// DHCP-DDNS:
///
///    * Application layer - the business layer which needs to
///    transport NameChangeRequests, and is unaware of the means by which
///    they are transported.
///
///    * NameChangeRequest layer - This is the layer which acts as the
///    intermediary between the Application layer and the IO layer.  It must
///    be able to move NameChangeRequests to the IO layer as raw data and move
///    raw data from the IO layer in the Application layer as
///    NameChangeRequests.
///
///    * IO layer - the low-level layer that is directly responsible for
///    sending and receiving data asynchronously and is supplied through
///    other libraries.  This layer is largely unaware of the nature of the
///    data being transmitted.  In other words, it doesn't know beans about
///    NCRs.
///
/// The abstract classes defined here implement the latter, middle layer,
/// the NameChangeRequest layer.  There are two types of participants in this
/// middle ground:
///
///    * listeners - Receive NCRs from one or more sources. The DHCP-DDNS
///   application, (aka D2), is a listener. Listeners are embodied by the
///   class, NameChangeListener.
///
///    * senders - sends NCRs to a given target.  DHCP servers are senders.
///   Senders are embodied by the class, NameChangeSender.
///
/// These two classes present a public interface for asynchronous
/// communications that is independent of the IO layer mechanisms.  While the
/// type and details of the IO mechanism are not relevant to either class, it
/// is presumed to use isc::asiolink library for asynchronous event processing.

#include <asiolink/io_address.h>
#include <asiolink/io_service.h>
#include <dhcp_ddns/ncr_msg.h>
#include <exceptions/exceptions.h>

#include <boost/scoped_ptr.hpp>

#include <deque>
#include <mutex>

namespace isc {
namespace dhcp_ddns {

/// @brief Defines the list of socket protocols supported.
/// Currently only UDP is implemented.
/// @todo TCP is intended to be implemented prior 1.0 release.
/// @todo Give some thought to an ANY protocol which might try
/// first as UDP then as TCP, etc.
enum NameChangeProtocol {
  NCR_UDP,
  NCR_TCP
};

/// @brief Function which converts text labels to @ref NameChangeProtocol enums.
///
/// @param protocol_str text to convert to an enum.
/// Valid string values: "UDP", "TCP"
///
/// @return NameChangeProtocol value which maps to the given string.
///
/// @throw isc::BadValue if given a string value which does not map to an
/// enum value.
extern NameChangeProtocol stringToNcrProtocol(const std::string& protocol_str);

/// @brief Function which converts @ref NameChangeProtocol enums to text labels.
///
/// @param protocol enum value to convert to label
///
/// @return std:string containing the text label if the value is valid, or
/// "UNKNOWN" if not.
extern std::string ncrProtocolToString(NameChangeProtocol protocol);

/// @brief Exception thrown if an NcrListenerError encounters a general error.
class NcrListenerError : public isc::Exception {
public:
    NcrListenerError(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) { };
};

/// @brief Exception thrown if an error occurs during IO source open.
class NcrListenerOpenError : public isc::Exception {
public:
    NcrListenerOpenError(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) { };
};

/// @brief Exception thrown if an error occurs initiating an IO receive.
class NcrListenerReceiveError : public isc::Exception {
public:
    NcrListenerReceiveError(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) { };
};


/// @brief Abstract interface for receiving NameChangeRequests.
///
/// NameChangeListener provides the means to:
/// -  Supply a callback to invoke upon receipt of an NCR or a listening
/// error
/// -  Start listening using a given IOService instance to process events
/// -  Stop listening
///
/// It implements the high level logic flow to listen until a request arrives,
/// invoke the implementation's handler and return to listening for the next
/// request.
///
/// It provides virtual methods that allow derivations supply implementations
/// to open the appropriate IO source, perform a listen, and close the IO
/// source.
///
/// The overall design is based on a callback chain. The listener's caller (the
/// application) supplies an "application" layer callback through which it will
/// receive inbound NameChangeRequests.  The listener derivation will supply
/// its own callback to the IO layer to process receive events from its IO
/// source.  This is referred to as the NameChangeRequest completion handler.
/// It is through this handler that the NameChangeRequest layer gains access
/// to the low level IO read service results.  It is expected to assemble
/// NameChangeRequests from the inbound data and forward them to the
/// application layer by invoking the application layer callback registered
/// with the listener.
///
/// The application layer callback is structured around a nested class,
/// RequestReceiveHandler.  It consists of single, abstract operator() which
/// accepts a result code and a pointer to a NameChangeRequest as parameters.
/// In order to receive inbound NCRs, a caller implements a derivation of the
/// RequestReceiveHandler and supplies an instance of this derivation to the
/// NameChangeListener constructor. This "registers" the handler with the
/// listener.
///
/// To begin listening, the caller invokes the listener's startListener()
/// method, passing in an IOService instance.  This in turn will pass the
/// IOService into the virtual method, open().  The open method is where the
/// listener derivation performs the steps necessary to prepare its IO source
/// for reception (e.g. opening a socket, connecting to a database).
///
/// Assuming the open is successful, startListener will call receiveNext, to
/// initiate an asynchronous receive.  This method calls the virtual method,
/// doReceive().  The listener derivation uses doReceive to instigate an IO
/// layer asynchronous receive passing in its IO layer callback to
/// handle receive events from the IO source.
///
/// As stated earlier, the derivation's NameChangeRequest completion handler
/// MUST invoke the application layer handler registered with the listener.
/// This is done by passing in either a success status and a populated
/// NameChangeRequest or an error status and an empty request into the
/// listener's invokeRecvHandler method. This is the mechanism by which the
/// listener's caller is handed inbound NCRs.
class NameChangeListener {
public:

    /// @brief Defines the outcome of an asynchronous NCR receive
    enum Result {
        SUCCESS,
        TIME_OUT,
        STOPPED,
        ERROR
    };

    /// @brief Abstract class for defining application layer receive callbacks.
    ///
    /// Applications which will receive NameChangeRequests must provide a
    /// derivation of this class to the listener constructor in order to
    /// receive NameChangeRequests.
    class RequestReceiveHandler {
    public:

        /// @brief Function operator implementing a NCR receive callback.
        ///
        /// This method allows the application to receive the inbound
        /// NameChangeRequests. It is intended to function as a hand off of
        /// information and should probably not be time-consuming.
        ///
        /// @param result contains that receive outcome status.
        /// @param ncr is a pointer to the newly received NameChangeRequest if
        /// result is NameChangeListener::SUCCESS.  It is indeterminate other
        /// wise.
        ///
        /// @throw This method MUST NOT throw.
        virtual void operator ()(const Result result,
                                 NameChangeRequestPtr& ncr) = 0;

        virtual ~RequestReceiveHandler() {
        }
    };

    /// @brief Constructor
    ///
    /// @param recv_handler is a pointer the application layer handler to be
    /// invoked each time a NCR is received or a receive error occurs.
    NameChangeListener(RequestReceiveHandler& recv_handler);

    /// @brief Destructor
    virtual ~NameChangeListener() {
    };

    /// @brief Prepares the IO for reception and initiates the first receive.
    ///
    /// Calls the derivation's open implementation to initialize the IO layer
    /// source for receiving inbound requests.  If successful, it starts the
    /// first asynchronous read by receiveNext.
    ///
    /// @param io_service is the IOService that will handle IO event processing.
    ///
    /// @throw NcrListenError if the listener is already "listening" or
    /// in the event the open or doReceive methods fail.
    void startListening(isc::asiolink::IOService& io_service);

    /// @brief Closes the IO source and stops listen logic.
    ///
    /// Calls the derivation's implementation of close and marks the state
    /// as not listening.
    void stopListening();

protected:
    /// @brief Initiates an asynchronous receive
    ///
    /// Sets context information to indicate that IO is in progress and invokes
    /// the derivation's asynchronous receive method, doReceive.  Note doReceive
    /// should not be called outside this method to ensure context information
    /// integrity.
    ///
    /// @throw Derivation's doReceive method may throw isc::Exception upon
    /// error.
    void receiveNext();

    /// @brief Calls the NCR receive handler registered with the listener.
    ///
    /// This is the hook by which the listener's caller's NCR receive handler
    /// is called.  This method MUST be invoked by the derivation's
    /// implementation of doReceive.
    ///
    /// NOTE:
    /// The handler invoked by this method MUST NOT THROW. The handler is
    /// at application level and should trap and handle any errors at
    /// that level, rather than throw exceptions.  If an error has occurred
    /// prior to invoking the handler, it will be expressed in terms a failed
    /// result being passed to the handler, not a throw.  Therefore any
    /// exceptions at the handler level are application issues and should be
    /// dealt with at that level.
    ///
    /// This method does wrap the handler invocation within a try-catch
    /// block as a fail-safe.  The exception will be logged but the
    /// receive logic will continue.  What this implies is that continued
    /// operation may or may not succeed as the application has violated
    /// the interface contract.
    ///
    /// @param result contains that receive outcome status.
    /// @param ncr is a pointer to the newly received NameChangeRequest if
    /// result is NameChangeListener::SUCCESS.  It is indeterminate other
    /// wise.
    void invokeRecvHandler(const Result result, NameChangeRequestPtr& ncr);

    /// @brief Abstract method which opens the IO source for reception.
    ///
    /// The derivation uses this method to perform the steps needed to
    /// prepare the IO source to receive requests.
    ///
    /// @param io_service is the IOService that process IO events.
    ///
    /// @throw If the implementation encounters an error it MUST
    /// throw it as an isc::Exception or derivative.
    virtual void open(isc::asiolink::IOService& io_service) = 0;

    /// @brief Abstract method which closes the IO source.
    ///
    /// The derivation uses this method to perform the steps needed to
    /// "close" the IO source.
    ///
    /// @throw If the implementation encounters an error it  MUST
    /// throw it as an isc::Exception or derivative.
    virtual void close() = 0;

    /// @brief Initiates an IO layer asynchronous read.
    ///
    /// The derivation uses this method to perform the steps needed to
    /// initiate an asynchronous read of the IO source with the
    /// derivation's IO layer handler as the IO completion callback.
    ///
    /// @throw If the implementation encounters an error it  MUST
    /// throw it as an isc::Exception or derivative.
    virtual void doReceive() = 0;

public:

    /// @brief Returns true if the listener is listening, false otherwise.
    ///
    /// A true value indicates that the IO source has been opened successfully,
    /// and that receive loop logic is active.  This implies that closing the
    /// IO source will interrupt that operation, resulting in a callback
    /// invocation.
    ///
    /// @return The listening mode.
    bool amListening() const {
        return (listening_);
    }

    /// @brief Returns true if the listener has an IO call in progress.
    ///
    /// A true value indicates that the listener has an asynchronous IO in
    /// progress which will complete at some point in the future. Completion
    /// of the call will invoke the registered callback.  It is important to
    /// understand that the listener and its related objects should not be
    /// deleted while there is an IO call pending.  This can result in the
    /// IO service attempting to invoke methods on objects that are no longer
    /// valid.
    ///
    /// @return The IO pending flag.
    bool isIoPending() const {
        return (io_pending_);
    }

private:
    /// @brief Sets the listening indicator to the given value.
    ///
    /// Note, this method is private as it is used the base class is solely
    /// responsible for managing the state.
    ///
    /// @param value is the new value to assign to the indicator.
    void setListening(bool value) {
        listening_ = value;
    }

    /// @brief Indicates if the listener is in listening mode.
    bool listening_;

    /// @brief Indicates that listener has an async IO pending completion.
    bool io_pending_;

    /// @brief Application level NCR receive completion handler.
    RequestReceiveHandler& recv_handler_;
};

/// @brief Defines a smart pointer to an instance of a listener.
typedef boost::shared_ptr<NameChangeListener> NameChangeListenerPtr;


/// @brief Thrown when a NameChangeSender encounters an error.
class NcrSenderError : public isc::Exception {
public:
    NcrSenderError(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) { };
};

/// @brief Exception thrown if an error occurs during IO source open.
class NcrSenderOpenError : public isc::Exception {
public:
    NcrSenderOpenError(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) { };
};

/// @brief Exception thrown if an error occurs initiating an IO send.
class NcrSenderQueueFull : public isc::Exception {
public:
    NcrSenderQueueFull(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) { };
};

/// @brief Exception thrown if an error occurs initiating an IO send.
class NcrSenderSendError : public isc::Exception {
public:
    NcrSenderSendError(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) { };
};


/// @brief Abstract interface for sending NameChangeRequests.
///
/// NameChangeSender provides the means to:
/// - Supply a callback to invoke upon completing the delivery of an NCR or a
/// send error
/// - Start sending using a given IOService instance to process events
/// - Queue NCRs for delivery
/// - Stop sending
///
/// It implements the high level logic flow to queue requests for delivery,
/// and ship them one at a time, waiting for the send to complete prior to
/// sending the next request in the queue.  If a send fails, the request
/// will remain at the front of queue and the send will be retried
/// endlessly unless the caller dequeues the request.  Note, it is presumed that
/// a send failure is some form of IO error such as loss of connectivity and
/// not a message content error.  It should not be possible to queue an invalid
/// message.
///
/// It should be noted that once a request is placed onto the send queue it
/// will remain there until one of three things occur:
///     * It is successfully delivered
///     * @c NameChangeSender::skipNext() is called
///     * @c NameChangeSender::clearSendQueue() is called
///
/// The queue contents are preserved across start and stop listening
/// transitions. This is to provide for error recovery without losing
/// undelivered requests.

/// It provides virtual methods so derivations may supply implementations to
/// open the appropriate IO sink, perform a send, and close the IO sink.
///
/// The overall design is based on a callback chain.  The sender's caller (the
/// application) supplies an "application" layer callback through which it will
/// be given send completion notifications. The sender derivation will employ
/// its own callback at the IO layer to process send events from its IO sink.
/// This callback is expected to forward the outcome of each asynchronous send
/// to the application layer by invoking the application layer callback
/// registered with the sender.
///
/// The application layer callback is structured around a nested class,
/// RequestSendHandler.  It consists of single, abstract operator() which
/// accepts a result code and a pointer to a NameChangeRequest as parameters.
/// In order to receive send completion notifications, a caller implements a
/// derivation of the RequestSendHandler and supplies an instance of this
/// derivation to the NameChangeSender constructor. This "registers" the
/// handler with the sender.
///
/// To begin sending, the caller invokes the listener's startSending()
/// method, passing in an IOService instance.  This in turn will pass the
/// IOService into the virtual method, open().  The open method is where the
/// sender derivation performs the steps necessary to prepare its IO sink for
/// output (e.g. opening a socket, connecting to a database).  At this point,
/// the sender is ready to send messages.
///
/// In order to send a request, the application layer invokes the sender
/// method, sendRequest(), passing in the NameChangeRequest to send.  This
/// method places the request onto the back of the send queue, and then invokes
/// the sender method, sendNext().
///
/// If there is already a send in progress when sendNext() is called, the method
/// will return immediately rather than initiate the next send.  This is to
/// ensure that sends are processed sequentially.
///
/// If there is not a send in progress and the send queue is not empty,
/// the sendNext method will pass the NCR at the front of the send queue into
/// the virtual doSend() method.
///
/// The sender derivation uses this doSend() method to instigate an IO layer
/// asynchronous send with its IO layer callback to handle send events from its
/// IO sink.
///
/// As stated earlier, the derivation's IO layer callback MUST invoke the
/// application layer handler registered with the sender.  This is done by
/// passing in  a status indicating the outcome of the send into the sender's
/// invokeSendHandler method. This is the mechanism by which the sender's
/// caller is handed outbound notifications.

/// After invoking the application layer handler, the invokeSendHandler method
/// will call the sendNext() method to initiate the next send.  This ensures
/// that requests continue to dequeue and ship.
///
class NameChangeSender {
public:

    /// @brief Defines the type used for the request send queue.
    typedef std::deque<NameChangeRequestPtr> SendQueue;

    /// @brief Defines a default maximum number of entries in the send queue.
    static const size_t MAX_QUEUE_DEFAULT = 1024;

    /// @brief Defines the outcome of an asynchronous NCR send.
    enum Result {
        SUCCESS,
        TIME_OUT,
        STOPPED,
        ERROR
    };

    /// @brief Abstract class for defining application layer send callbacks.
    ///
    /// Applications which will send NameChangeRequests must provide a
    /// derivation of this class to the sender constructor in order to
    /// receive send outcome notifications.
    class RequestSendHandler {
    public:

        /// @brief Function operator implementing a NCR send callback.
        ///
        /// This method allows the application to receive the outcome of
        /// each send.  It is intended to function as a hand off of information
        /// and should probably not be time-consuming.
        ///
        /// @param result contains that send outcome status.
        /// @param ncr is a pointer to the NameChangeRequest that was
        /// delivered (or attempted).
        ///
        /// @throw This method MUST NOT throw.
        virtual void operator ()(const Result result,
                                 NameChangeRequestPtr& ncr) = 0;

        virtual ~RequestSendHandler() {
        }
    };

    /// @brief Constructor
    ///
    /// @param send_handler is a pointer the application layer handler to be
    /// invoked each time a NCR send attempt completes.
    /// @param send_queue_max is the maximum number of entries allowed in the
    /// send queue.  Once the maximum number is reached, all calls to
    /// sendRequest will fail with an exception.
    NameChangeSender(RequestSendHandler& send_handler,
                     size_t send_queue_max = MAX_QUEUE_DEFAULT);

    /// @brief Destructor
    virtual ~NameChangeSender() {
    }

    /// @brief Prepares the IO for transmission.
    ///
    /// Calls the derivation's open implementation to initialize the IO layer
    /// sink for sending outbound requests.
    ///
    /// @param io_service is the IOService that will handle IO event processing.
    ///
    /// @throw NcrSenderError if the sender is already "sending" or
    /// NcrSenderOpenError if the open fails.
    void startSending(isc::asiolink::IOService & io_service);

    /// @brief Closes the IO sink and stops send logic.
    ///
    /// Calls the derivation's implementation of close and marks the state
    /// as not sending.
    void stopSending();

    /// @brief Queues the given request to be sent.
    ///
    /// The given request is placed at the back of the send queue and then
    /// sendNext is invoked.
    ///
    /// @param ncr is the NameChangeRequest to send.
    ///
    /// @throw NcrSenderError if the sender is not in sending state or
    /// the request is empty; NcrSenderQueueFull if the send queue has reached
    /// capacity.
    void sendRequest(NameChangeRequestPtr& ncr);

    /// @brief Move all queued requests from a given sender into the send queue
    ///
    /// Moves all of the entries in the given sender's queue and places them
    /// into send queue.  This provides a mechanism of reassigning queued
    /// messages from one sender to another. This is useful for dealing with
    /// dynamic configuration changes.
    ///
    /// @param source_sender from whom the queued messages will be taken
    ///
    /// @throw NcrSenderError if either sender is in send mode, if the number of
    /// messages in the source sender's queue is larger than this sender's
    /// maximum queue size, or if this sender's queue is not empty.
    void assumeQueue(NameChangeSender& source_sender);

    /// @brief Returns a file descriptor suitable for use with select
    ///
    /// The value returned is an open file descriptor which can be used with
    /// select() system call to monitor the sender for IO events.  This allows
    /// NameChangeSenders to be used in applications which use select, rather
    /// than IOService to wait for IO events to occur.
    ///
    /// @warning Attempting other use of this value may lead to unpredictable
    /// behavior in the sender.
    ///
    /// @return Returns an "open" file descriptor
    ///
    /// @throw NcrSenderError if the sender is not in send mode,
    virtual int getSelectFd() = 0;

    /// @brief Returns whether or not the sender has IO ready to process.
    ///
    /// @return true if the sender has at IO ready, false otherwise.
    virtual bool ioReady() = 0;

private:

    /// @brief Prepares the IO for transmission in a thread safe context.
    ///
    /// @param io_service is the IOService that will handle IO event processing.
    void startSendingInternal(isc::asiolink::IOService & io_service);

    /// @brief Queues the given request to be sent in a thread safe context.
    ///
    /// @param ncr is the NameChangeRequest to send.
    ///
    /// @throw NcrSenderQueueFull if the send queue has reached capacity.
    void sendRequestInternal(NameChangeRequestPtr& ncr);

    /// @brief Move all queued requests from a given sender into the send queue
    /// in a thread safe context.
    ///
    /// @param source_sender from whom the queued messages will be taken
    ///
    /// @throw NcrSenderError if this sender's queue is not empty.
    void assumeQueueInternal(NameChangeSender& source_sender);

    /// @brief Calls the NCR send completion handler registered with the
    /// sender in a thread safe context.
    ///
    /// @param result contains that send outcome status.
    void invokeSendHandlerInternal(const NameChangeSender::Result result);

    /// @brief Removes the request at the front of the send queue in a thread
    /// safe context.
    void skipNextInternal();

    /// @brief Returns the number of entries currently in the send queue in a
    /// thread safe context.
    ///
    /// @return the queue size.
    size_t getQueueSizeInternal() const;

    /// @brief Returns the entry at a given position in the queue in a thread
    /// safe context.
    ///
    /// @return Pointer reference to the queue entry.
    ///
    /// @throw NcrSenderError if the given index is beyond the
    /// end of the queue.
    const NameChangeRequestPtr& peekAtInternal(const size_t index) const;

protected:

    /// @brief Dequeues and sends the next request on the send queue in a thread
    /// safe context.
    ///
    /// If there is already a send in progress just return. If there is not
    /// a send in progress and the send queue is not empty the grab the next
    /// message on the front of the queue and call doSend().
    void sendNext();

    /// @brief Calls the NCR send completion handler registered with the
    /// sender.
    ///
    /// This is the hook by which the sender's caller's NCR send completion
    /// handler is called.  This method MUST be invoked by the derivation's
    /// implementation of doSend.  Note that if the send was a success, the
    /// entry at the front of the queue is removed from the queue.
    /// If not we leave it there so we can retry it.  After we invoke the
    /// handler we clear the pending ncr value and queue up the next send.
    ///
    /// NOTE:
    /// The handler invoked by this method MUST NOT THROW. The handler is
    /// application level logic and should trap and handle any errors at
    /// that level, rather than throw exceptions.  If IO errors have occurred
    /// prior to invoking the handler, they are expressed in terms a failed
    /// result being passed to the handler.  Therefore any exceptions at the
    /// handler level are application issues and should be dealt with at that
    /// level.
    ///
    /// This method does wrap the handler invocation within a try-catch
    /// block as a fail-safe.  The exception will be logged but the
    /// send logic will continue.  What this implies is that continued
    /// operation may or may not succeed as the application has violated
    /// the interface contract.
    ///
    /// @param result contains that send outcome status.
    void invokeSendHandler(const NameChangeSender::Result result);

    /// @brief Abstract method which opens the IO sink for transmission.
    ///
    /// The derivation uses this method to perform the steps needed to
    /// prepare the IO sink to send requests.
    ///
    /// @param io_service is the IOService that process IO events.
    ///
    /// @throw If the implementation encounters an error it MUST
    /// throw it as an isc::Exception or derivative.
    virtual void open(isc::asiolink::IOService& io_service) = 0;

    /// @brief Abstract method which closes the IO sink.
    ///
    /// The derivation uses this method to perform the steps needed to
    /// "close" the IO sink.
    ///
    /// @throw If the implementation encounters an error it MUST
    /// throw it as an isc::Exception or derivative.
    virtual void close() = 0;

    /// @brief Initiates an IO layer asynchronous send
    ///
    /// The derivation uses this method to perform the steps needed to
    /// initiate an asynchronous send through the IO sink of the given NCR.
    ///
    /// @param ncr is a pointer to the NameChangeRequest to send.
    /// derivation's IO layer handler as the IO completion callback.
    ///
    /// @throw If the implementation encounters an error it MUST
    /// throw it as an isc::Exception or derivative.
    virtual void doSend(NameChangeRequestPtr& ncr) = 0;

public:

    /// @brief Removes the request at the front of the send queue
    ///
    /// This method can be used to avoid further retries of a failed
    /// send. It is provided primarily as a just-in-case measure. Since
    /// a failed send results in the same request being retried continuously
    /// this method makes it possible to remove that entry, causing the
    /// subsequent entry in the queue to be attempted on the next send.
    /// It is presumed that sends will only fail due to some sort of
    /// communications issue. In the unlikely event that a request is
    /// somehow tainted and causes an send failure based on its content,
    /// this method provides a means to remove the message.
    void skipNext();

    /// @brief Flushes all entries in the send queue
    ///
    /// This method can be used to discard all of the NCRs currently in the
    /// the send queue.  Note it may not be called while the sender is in
    /// the sending state.
    ///
    /// @throw NcrSenderError if called and sender is in sending state.
    void clearSendQueue();

    /// @brief Returns true if the sender is in send mode, false otherwise.
    ///
    /// A true value indicates that the IO sink has been opened successfully,
    /// and that send loop logic is active.
    ///
    /// @return The send mode.
    bool amSending() const {
        return (sending_);
    }

    /// @brief Returns true when a send is in progress.
    ///
    /// A true value indicates that a request is actively in the process of
    /// being delivered.
    ///
    /// @return The send in progress flag.
    bool isSendInProgress() const;

    /// @brief Returns the maximum number of entries allowed in the send queue.
    ///
    /// @return The queue maximum size.
    size_t getQueueMaxSize() const  {
        return (send_queue_max_);
    }

    /// @brief Sets the maximum queue size to the given value.
    ///
    /// Sets the maximum number of entries allowed in the queue to the
    /// the given value.
    ///
    /// @param new_max the new value to use as the maximum
    ///
    /// @throw NcrSenderError if the value is less than one.
    void setQueueMaxSize(const size_t new_max);

    /// @brief Returns the number of entries currently in the send queue.
    ///
    /// @return The queue size.
    size_t getQueueSize() const;

    /// @brief Returns the entry at a given position in the queue.
    ///
    /// Note that the entry is not removed from the queue.
    ///
    /// @param index the index of the entry in the queue to fetch.
    /// Valid values are 0 (front of the queue) to (queue size - 1).
    ///
    /// @return Pointer reference to the queue entry.
    ///
    /// @throw NcrSenderError if the given index is beyond the
    /// end of the queue.
    const NameChangeRequestPtr& peekAt(const size_t index) const;

    /// @brief Processes sender IO events
    ///
    /// Executes at most one ready handler on the sender's IO service. If
    /// no handlers are ready it returns immediately.
    ///
    /// @warning - Running all ready handlers, in theory, could process all
    /// messages currently queued.
    ///
    /// NameChangeSender daisy chains requests together in its completion
    /// by one message completion's handler initiating the next message's send.
    /// When using UDP, a send immediately marks its event handler as ready
    /// to run.  If this occurs inside a call to ioservice::poll() or run(),
    /// that event will also be run.  If that handler calls UDP send then
    /// that send's handler will be marked ready and executed and so on.  If
    /// there were 1000 messages in the queue then all them would be sent from
    /// within the context of one call to runReadyIO().
    /// By running only one handler at time, we ensure that NCR IO activity
    /// doesn't starve other processing.  It is unclear how much of a real
    /// threat this poses but for now it is best to err on the side of caution.
    virtual void runReadyIO();

protected:

    /// @brief Returns a reference to the send queue.
    ///
    /// @return The send queue.
    SendQueue& getSendQueue() {
        return (send_queue_);
    }

private:

    /// @brief Sets the sending indicator to the given value.
    ///
    /// Note, this method is private as it is used the base class is solely
    /// responsible for managing the state.
    ///
    /// @param value is the new value to assign to the indicator.
    void setSending(bool value) {
        sending_ = value;
    }

    /// @brief Boolean indicator which tracks sending status.
    bool sending_;

    /// @brief A pointer to registered send completion handler.
    RequestSendHandler& send_handler_;

    /// @brief Maximum number of entries permitted in the send queue.
    size_t send_queue_max_;

    /// @brief Queue of the requests waiting to be sent.
    SendQueue send_queue_;

    /// @brief Pointer to the request which is in the process of being sent.
    NameChangeRequestPtr ncr_to_send_;

    /// @brief Pointer to the IOService currently being used by the sender.
    /// @note We need to remember the io_service but we receive it by
    /// reference.  Use a raw pointer to store it.  This value should never be
    /// exposed and is only valid while in send mode.
    asiolink::IOService* io_service_;

    /// @brief The mutex used to protect internal state.
    const boost::scoped_ptr<std::mutex> mutex_;
};

/// @brief Defines a smart pointer to an instance of a sender.
typedef boost::shared_ptr<NameChangeSender> NameChangeSenderPtr;

}  // namespace dhcp_ddns
}  // namespace isc

#endif
