// Copyright (C) 2013, 2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef D2_QUEUE_MGR_H
#define D2_QUEUE_MGR_H

/// @file d2_queue_mgr.h This file defines the class D2QueueMgr.

#include <asiolink/io_service.h>
#include <exceptions/exceptions.h>
#include <dhcp_ddns/ncr_msg.h>
#include <dhcp_ddns/ncr_io.h>

#include <boost/noncopyable.hpp>
#include <deque>

namespace isc {
namespace d2 {

/// @brief Defines a queue of requests.
/// @todo This may be replaced with an actual class in the future.
typedef std::deque<dhcp_ddns::NameChangeRequestPtr> RequestQueue;

/// @brief Thrown if the queue manager encounters a general error.
class D2QueueMgrError : public isc::Exception {
public:
    D2QueueMgrError(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) { };
};

/// @brief Thrown if the queue manager's receive handler is passed
/// a failure result.
class D2QueueMgrReceiveError : public isc::Exception {
public:
    D2QueueMgrReceiveError(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) { };
};


/// @brief Thrown if the request queue is full when an enqueue is attempted.
class D2QueueMgrQueueFull : public isc::Exception {
public:
    D2QueueMgrQueueFull(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) { };
};

/// @brief Thrown if the request queue empty and a read is attempted.
class D2QueueMgrQueueEmpty : public isc::Exception {
public:
    D2QueueMgrQueueEmpty(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) { };
};

/// @brief Thrown if a queue index is beyond the end of the queue
class D2QueueMgrInvalidIndex : public isc::Exception {
public:
    D2QueueMgrInvalidIndex(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) { };
};


/// @brief D2QueueMgr creates and manages a queue of DNS update requests.
///
/// D2QueueMgr is a class specifically designed as an integral part of DHCP-DDNS.
/// Its primary responsibility is to listen for NameChangeRequests from
/// DHCP-DDNS clients (e.g. DHCP servers) and queue them for processing. In
/// addition it may provide a number of services to locate entries in the queue
/// such as by FQDN or DHCID.  These services may eventually be used
/// for processing optimization.  The initial implementation will support
/// simple FIFO access.
///
/// D2QueueMgr uses a NameChangeListener to asynchronously receive requests.
/// It derives from NameChangeListener::RequestReceiveHandler and supplies an
/// implementation of the operator()(Result, NameChangeRequestPtr).  It is
/// through this operator() that D2QueueMgr is passed inbound NCRs. D2QueueMgr
/// will add each newly received request onto the back of the request queue
///
/// D2QueueMgr defines a simple state model constructed around the status of
/// its NameChangeListener, consisting of the following states:
///
///     * NOT_INITTED - D2QueueMgr has been constructed, but its listener has
///     not been initialized.
///
///     * INITTED - The listener has been initialized, but it is not open for
///     listening.   To move from NOT_INITTED to INITTED, one of the D2QueueMgr
///     listener initialization methods must be invoked.  Currently there is
///     only one type of listener, NameChangeUDPListener, hence there is only
///     one listener initialization method, initUDPListener.  As more listener
///     types are created, listener initialization methods will need to be
///     added.
///
///     * RUNNING - The listener is open and listening for requests.
///     Once initialized, in order to begin listening for requests, the
///     startListener() method must be invoked.  Upon successful completion of
///     of this call, D2QueueMgr will begin receiving requests as they arrive
///     without any further steps.   This method may be called from the INITTED
///     or one of the STOPPED states.
///
///     * STOPPING - The listener is in the process of stopping active
///     listening. This is transitory state between RUNNING and STOPPED, which
///     is completed by IO cancellation event.
///
///     * STOPPED - The listener has been listening but has been stopped
///     without error. To return to listening, startListener() must be invoked.
///
///     * STOPPED_QUEUE_FULL - Request queue is full, the listener has been
///     stopped.  D2QueueMgr will enter this state when the request queue
///     reaches the maximum queue size.  Once this limit is reached, the
///     listener will be closed and no further requests will be received.
///     To return to listening, startListener() must be invoked.  Note that so
///     long as the queue is full, any attempt to queue a request will fail.
///
///     * STOPPED_RECV_ERROR - The listener has experienced a receive error
///     and has been stopped.  D2QueueMgr will enter this state when it is
///     passed a failed status into the request completion handler.  To return
///     to listening, startListener() must be invoked.
///
/// D2QueueMgr does not attempt to recover from stopped conditions, this is left
/// to upper layers.
///
/// It is important to note that the queue contents are preserved between
/// state transitions.  In other words entries in the queue remain there
/// until they are removed explicitly via the deque() or implicitly by
/// via the clearQueue() method.
///
class D2QueueMgr : public dhcp_ddns::NameChangeListener::RequestReceiveHandler,
                   boost::noncopyable {
public:
    /// @brief Maximum number of entries allowed in the request queue.
    /// NOTE that 1024 is an arbitrary choice picked for the initial
    /// implementation.
    static const size_t MAX_QUEUE_DEFAULT = 1024;

    /// @brief Defines the list of possible states for D2QueueMgr.
    enum State {
      NOT_INITTED,
      INITTED,
      RUNNING,
      STOPPING,
      STOPPED_QUEUE_FULL,
      STOPPED_RECV_ERROR,
      STOPPED,
    };

    /// @brief Constructor
    ///
    /// Creates a D2QueueMgr instance.  Note that the listener is not created
    /// in the constructor. The initial state will be NOT_INITTED.
    ///
    /// @param io_service IOService instance to be passed into the listener for
    /// IO management.
    /// @param max_queue_size the maximum number of entries allowed in the
    /// queue.
    /// This value must be greater than zero. It defaults to MAX_QUEUE_DEFAULT.
    ///
    /// @throw D2QueueMgrError if max_queue_size is zero.
    D2QueueMgr(asiolink::IOServicePtr& io_service,
               const size_t max_queue_size = MAX_QUEUE_DEFAULT);

    /// @brief Destructor
    virtual ~D2QueueMgr();

    /// @brief Initializes the listener as a UDP listener.
    ///
    /// Instantiates the listener_ member as NameChangeUDPListener passing
    /// the given parameters.  Upon successful completion, the D2QueueMgr state
    /// will be INITTED.
    ///
    /// @param ip_address is the network address on which to listen
    /// @param port is the IP port on which to listen
    /// @param format is the wire format of the inbound requests.
    /// @param reuse_address enables IP address sharing when true
    /// It defaults to false.
    void initUDPListener(const isc::asiolink::IOAddress& ip_address,
                         const uint32_t port,
                         const dhcp_ddns::NameChangeFormat format,
                         const bool reuse_address = false);

    /// @brief Starts actively listening for requests.
    ///
    /// Invokes the listener's startListening method passing in our
    /// IOService instance.
    ///
    /// @throw D2QueueMgrError if the listener has not been initialized,
    /// state is already RUNNING, or the listener fails to actually start.
    void startListening();

    /// @brief Function operator implementing the NCR receive callback.
    ///
    /// This method is invoked by the listener as part of its receive
    /// completion callback and is how the inbound NameChangeRequests are
    /// passed up to the D2QueueMgr for queueing.
    /// If the given result indicates a successful receive completion and
    /// there is room left in the queue, the given request is queued.
    ///
    /// If the queue is at maximum capacity, stopListening() is invoked and
    /// the state is set to STOPPED_QUEUE_FULL.
    ///
    /// If the result indicates IO stopped, then the state is set to STOPPED.
    /// Note this is not an error, it results from a deliberate cancellation
    /// of listener IO as part of a normal stopListener call.
    ///
    /// If the result indicates a failed receive, stopListening() is invoked
    /// and the state is set to STOPPED_RECV_ERROR.
    ///
    /// This method specifically avoids throwing on an error as any such throw
    /// would surface at the io_service::run (or run variant) method invocation
    /// site. The upper layers are expected to monitor D2QueueMgr's state and
    /// act accordingly.
    ///
    /// @param result contains that receive outcome status.
    /// @param ncr is a pointer to the newly received NameChangeRequest if
    /// result is NameChangeListener::SUCCESS.  It is indeterminate other
    /// wise.
    virtual void operator ()(const dhcp_ddns::NameChangeListener::Result result,
                             dhcp_ddns::NameChangeRequestPtr& ncr);

    /// @brief Stops listening for requests.
    ///
    /// Invokes the listener's stopListening method which will cause it to
    /// cancel any pending IO and close its IO source.  It the sets target
    /// stop state to the given value.
    ///
    /// If there is no IO pending, the manager state is immediately set to the
    /// target stop state, otherwise the manager state is set to STOPPING.
    ///
    /// @param target_stop_state is one of the three stopped state values.
    ///
    /// @throw D2QueueMgrError if stop_state is a valid stop state.
    void stopListening(const State target_stop_state = STOPPED);


    /// @brief Deletes the current listener
    ///
    /// This method will delete the current listener and returns the manager
    /// to the NOT_INITTED state.  This is provided to support reconfiguring
    /// a new listener without losing queued requests.
    ///
    /// @throw D2QueMgrError if called when the manager state is RUNNING.
    void removeListener();

    /// @brief Returns the number of entries in the queue.
    size_t getQueueSize() const {
        return (ncr_queue_.size());
    };

    /// @brief Returns the maximum number of entries allowed in the queue.
    size_t getMaxQueueSize() const {
        return (max_queue_size_);
    }

    /// @brief Sets the maximum number of entries allowed in the queue.
    ///
    /// @param max_queue_size is the new maximum size of the queue.
    ///
    /// @throw D2QueueMgrError if the new value is less than one or if
    /// the new value is less than the number of entries currently in the
    /// queue.
    void setMaxQueueSize(const size_t max_queue_size);

    /// @brief Returns the current state.
    State getMgrState() const {
        return (mgr_state_);
    }

    /// @brief Returns the entry at the front of the queue.
    ///
    /// The entry returned is next in line to be processed, assuming a FIFO
    /// approach to task selection.  Note, the entry is not removed from the
    /// queue.
    ///
    /// @return Pointer reference to the queue entry.
    ///
    /// @throw D2QueueMgrQueEmpty if there are no entries in the queue.
    const dhcp_ddns::NameChangeRequestPtr& peek() const;

    /// @brief Returns the entry at a given position in the queue.
    ///
    /// Note that the entry is not removed from the queue.
    /// @param index the index of the entry in the queue to fetch.
    /// Valid values are 0 (front of the queue) to (queue size - 1).
    ///
    /// @return Pointer reference to the queue entry.
    ///
    /// @throw D2QueueMgrInvalidIndex if the given index is beyond the
    /// end of the queue.
    const dhcp_ddns::NameChangeRequestPtr& peekAt(const size_t index) const;

    /// @brief Removes the entry at a given position in the queue.
    ///
    /// @param index the index of the entry in the queue to remove.
    /// Valid values are 0 (front of the queue) to (queue size - 1).
    ///
    /// @throw D2QueueMgrInvalidIndex if the given index is beyond the
    /// end of the queue.
    void dequeueAt(const size_t index);

    /// @brief Removes the entry at the front of the queue.
    ///
    /// @throw D2QueueMgrQueEmpty if there are no entries in the queue.
    void dequeue();

    /// @brief Adds a request to the end of the queue.
    ///
    /// @param ncr pointer to the NameChangeRequest to add to the queue.
    void enqueue(dhcp_ddns::NameChangeRequestPtr& ncr);

    /// @brief Removes all entries from the queue.
    void clearQueue();

  private:
    /// @brief Sets the manager state to the target stop state.
    ///
    /// Convenience method which sets the manager state to the target stop
    /// state and logs that the manager is stopped.
    void updateStopState();

    /// @brief IOService that our listener should use for IO management.
    asiolink::IOServicePtr io_service_;

    /// @brief Dictates the maximum number of entries allowed in the queue.
    size_t max_queue_size_;

    /// @brief Queue of received NameChangeRequests.
    RequestQueue ncr_queue_;

    /// @brief Listener instance from which requests are received.
    boost::shared_ptr<dhcp_ddns::NameChangeListener> listener_;

    /// @brief Current state of the manager.
    State mgr_state_;

    /// @brief Tracks the state the manager should be in once stopped.
    State target_stop_state_;
};

/// @brief Defines a pointer for manager instances.
typedef boost::shared_ptr<D2QueueMgr> D2QueueMgrPtr;

} // namespace isc::d2
} // namespace isc

#endif
