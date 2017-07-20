// Copyright (C) 2013-2017 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef CLIENT6_INTERFACE_H
#define CLIENT6_INTERFACE_H

#include <asiolink/io_service.h>
#include <dhcp/iface_mgr.h>
#include <exceptions/exceptions.h>
#include <util/state_model.h>
#include <client/client_log.h>

#include <string>

namespace isc {
namespace client {

/// @brief Thrown if the some error is encountered
class Client6InterfaceError : public isc::Exception {
public:
    Client6InterfaceError(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) {};
};

/// @brief DHCPv6 Client Interface
///
/// This is the class that represents an interface that the client is managing.
/// It has a dual inheritance:
///
/// The first parent is the Iface class, representing a physical interface. It
/// contains all information, e.g.  name, MAC address etc.
///
/// The other parent is the StateModel, which defines the state the interface
/// is in and handles the logic for the process of acquring an address. Each
/// state has an associate method that handles the processing of the state.
/// Transitions between states are mainly (not always) triggered by the
/// completion of an asynchronous operation. 
///
/// To illustrate the flow of control in such a situation, assume the following:
/// The Client Interface moves from state A to state B.  In state B, it queues
/// an asynchronous operation, the completion of which causes it to move to
/// state C.  The processing is as follows:
///
/// 1. State A is entered from state B.  Any processing required on entry to
///    state B is done in the state B's handler at that time: either
///    the state is entered via a unique event, when a check on the event is
///    sufficient to determine that the state has been entered from state A,
///    or the single-shot doOnEntry() flag is checked.
///
/// 2. State B's handler queues an asynchronous I/O operation, passing to it
///    as a parameter the event to invoke when the operation completes.
///
/// 3. The handler calls postNextEvent(NOP_EVT) then exits, causing the
///    runModel() call that invoked the state machine processing to exit.
///    The process goes back to waiting on the IOService object.
///
/// 4. The asynchronous event completes, and the completion handler calls
///    the state machine's runModel() method, passing to it the event that
///    was associated with the operation.
///
/// 5. The state machine calls state B's handler again, passing to it the
///    event associated with the asynchronous operation.  The handler calls
///    the state machine's "transition" method to move to state C.
///
/// The upshot of this is that if an asynchronous operation is triggered, the
/// Client Interface will wait for completion in the state that triggered the
/// operation, transitioning to the new state when the operation completes.

class Client6Interface : public isc::dhcp::Iface,
                         public isc::util::StateModel {
public:

    /// @brief State list
    ///
    /// See http://kea.isc.org/wiki/ClientDesign for the definitions of each
    /// state.
    enum {
        ST_BEGIN = SM_DERIVED_STATE_MIN + 1,
        ST_SERVER_DISCOVERY,
        ST_SEND_SOLICIT,
        ST_SOLICIT_TIMEOUT,
        ST_ADVERTISE_RECEIVED,
        ST_SEND_REQUEST,
        ST_REQUEST_TIMEOUT,
        ST_REPLY_RECEIVED,
        ST_DUPLICATE_CHECK,
        ST_DUPLICATE_TIMEOUT,
        ST_CONFIGURED,
        ST_START_RENEW,
        ST_RESEND_RENEW,
        ST_RENEW_COMPLETE,
        ST_REBINDING,
        ST_PROCESS_REBINDING,
        ST_REBINDING_TIMEOUT
    };

    /// @brief Event List
    ///
    /// List of events.  Effectively these are the list of states, as each
    /// event indicates the target of the transition.
    enum {
        EVT_SERVER_DISCOVERY = SM_DERIVED_EVENT_MIN + 1,
        EVT_SEND_SOLICIT,
        EVT_ADVERTISE_RECEIVED,
        EVT_SOLICIT_TIMEOUT,
        EVT_SEND_REQUEST,
        EVT_REQUEST_TIMEOUT,
        EVT_REPLY_RECEIVED,
        EVT_DUPLICATE_CHECK,
        EVT_DUPLICATE_TIMEOUT,
        EVT_CONFIGURED,
        EVT_START_RENEW,
        EVT_RESEND_RENEW,
        EVT_REBINDING,
        EVT_PROCESS_REBINDING,
        EVT_REBINDING_TIMEOUT
    };
        
    /// @brief Constructor
    ///
    /// @param name Name of the interface
    /// @param index Index of the interface
    /// @param io_service Pointer to the IOService object used to keep track of
    /// all asynchronous operations.
    Client6Interface(const std::string& name, int ifindex,
                    isc::asiolink::IOServicePtr& io_service);

    /// @brief Destructor
    virtual ~Client6Interface();

    /// @brief Adds events defined by Client6Interface to the event set.
    ///
    /// This method adds the events defined for this state machine to the set
    /// of defined events.  It invokes the superclass's implementation
    /// first to maintain the hierarchical chain of event definition.
    ///
    /// @throw StateModelError if an event definition is invalid or a duplicate.
    virtual void defineEvents();

    /// @brief Validates the contents of the set of events.
    ///
    /// This method verifies that the events defined by both the superclass and
    /// this class are defined.  As with defineEvents, this method calls the
    /// superclass's implementation first, to verify events defined by it and
    /// then this implementation to verify events defined by
    /// NameChangeTransaction.
    ///
    /// @throw StateModelError if an event value is undefined.
    virtual void verifyEvents();

    /// @brief Adds states defined by Client6Interface to the state set.
    ///
    /// This method adds the states associated with the Client6Interface to
    /// the dictionary of states.  It invokes the superclass's implementation
    /// first to maintain the hierarchical chain of state definition.
    ///
    /// @throw StateModelError if an state definition is invalid or a duplicate.
    virtual void defineStates();

    /// @brief Validates the contents of the set of states.
    ///
    /// This method verifies that the states defined by both the superclass and
    /// this class are defined.  As with defineStates, this method calls the
    /// superclass's implementation first, to verify states defined by it and
    /// then this implementation to verify states defined by Client6Interface.
    ///
    /// @throw StateModelError if an event value is undefined.
    virtual void verifyStates();


    //@{ State Methods

    /// @brief State handler for BEGIN
    ///
    /// BEGIN is the state the model transitions into when the method
    /// startTransaction is called,  It is the entry point into the state
    /// machine.  It performs all the initialization then unconditionally
    /// transitions to the SERVER_DISCOVERY state.
    void beginHandler();

    /// @brief State handler for SERVER_DISCOVERY
    ///
    /// The second part of the initialization, this state initializes the
    /// list of available servers before transitioning to the SEND_SOLICIT
    /// state.
    void serverDiscoveryHandler();

    /// @brief State handler for SEND_SOLICIT
    ///
    /// SEND_SOLICIT is the state that initiates the discovery of servers.
    /// It initializes the list of servers, then broadcasts the SOLICIT message.
    /// It then kicks off an asynchronous read, as well as a read timer.
    void sendSolicitHandler();

    /// @brief State handler for ADVERTISE_RECEIVED
    ///
    /// The client enters this state when an ADVERTISE is received from the
    /// server.  If the SOLICIT has not timed out, it will - unless the
    /// server is one with the maximum preference value - loop round and
    /// wait for more responses until the solicit timer times out.
    void advertiseReceivedHandler();

    /// @brief State handler for SOLICIT_TIMEOUT
    ///
    /// This state is entered when the timer associated with the SOLICIT
    /// message has timed out.  Providing that some servers advertised
    /// themselves, the client moves from this state into SEND_REQUEST.
    void solicitTimeoutHandler();

    /// @brief State handler for SEND_REQUEST
    ///
    /// Starts a timer and sends the REQUEST to the server at the top of the
    /// servers list.
    void sendRequestHandler();

    /// @brief State handler for REQUEST_TIMEOUT
    ///
    /// Called when the timer associated with waiting for a REPLY from the
    /// server has timed out, this either sends another request (to the same
    /// or a different server) or goes back to looking for servers.
    void requestTimeoutHandler();

    /// @brief State handler for REPLY_RECEIVED
    ///
    /// When the server responds with a REPLY message, the client enters this
    /// state.  Depending on the response, it will either look for duplicate
    /// addresses or try to contact another server.
    void replyReceivedHandler();

    /// @brief State handler for DUPLICATE_CHECK
    ///
    /// The client enters this state to look for duplicates.  It waits here
    /// for a fixed period of time to see if the kernel realises that there
    /// are duplicate addresses.
    void duplicateCheckHandler();

    /// @brief State handler for DUPLICATE_TIMEOUT
    ///
    /// This state is entered when the duplicate wait period expires.  The
    /// client consults the kernel to see if duplicate addresses were found.
    void duplicateTimeoutHandler();

    /// @brief State handler for CONFIGURED
    ///
    /// The CONFIGURED state is the state where the client should spend most of
    /// its time.  It only leaves this state when the T1 timer expires,
    /// telling it that it should renew its lease.
    void configuredHandler();

    /// @brief State handler for START_RENEW
    ///
    /// The client enters this state when the T1 timer expires.  From here, it
    /// tries to renew its lease.
    void startRenewHandler();

    /// @brief State handler for RESEND_RENEW
    ///
    /// Entered when the iretransmission timer associated with receiving a
    /// response to the renewal request times out, the renew request is resent
    /// to the server.
    void resendRenewHandler();

    /// @brief State handler for RENEW_COMPLETE
    ///
    /// Entered when a response is received to the renew request, in this state
    /// the client decides whether it can accept the answer or has to start
    /// the process of acquiring a new lease.
    void renewCompleteHandler();

    /// @brief State handler for REBINDING
    ///
    /// If the T2 timer times out (this is started when a renewal request is
    /// made), the client will start the process of rebinding to a new address.
    void rebindingHandler();

    /// @brief State handler for PROCESS_REBINDING
    ///
    /// Entered when a rebinding response has been received, in this state
    /// the client decides whether to acept the response of take some other
    /// action.
    void processRebindingHandler();

    /// @brief State handler for REBINDING_TIMEOUT
    ///
    /// Enters when the timer assoiated with the rebinding request expires,
    /// the client tidies up and starts the server discovery process again.
    void rebindingTimeoutHandler();

    //@}

    /// @brief Asynchronous Operation Completion Handler
    ///
    /// Called when any asynchronous option completes, it causes the state
    /// machine to transition to the next state.
    ///
    /// @param ec System error code
    /// @param event Event that causes the transition
    void asynchCompletion(const boost::system::error_code& ec, int event);


    /// @brief Fetches the IOService the transaction uses for IO processing.
    ///
    /// @return returns a const pointer to the IOService.
    const asiolink::IOServicePtr& getIOService() {
        return (io_service_);
    }

private:
    /// @brief Log State Error
    ///
    /// This is a convenience function to log an error due to the current
    /// state not expecting to be entered with the current (next) event.
    /// Although it breaks the Kea idea that each LOG_XXX should be with a
    /// unique error code, the combination of error code and state (the
    /// first parameter) is unique.
    void logUnexpectedEvent();

    /// @brief The IOService which should be used to for IO processing.
    asiolink::IOServicePtr io_service_;

    // Flags to indicate that timers are running.  The names are fairly
    // self-explanatory.
    bool solicit_timer_running_;
    
};

/// @brief Defines a pointer to a Client6Interface
typedef boost::shared_ptr<Client6Interface> Client6InterfacePtr;

} // namespace isc::client
} // namespace isc

#endif  // CLIENT6_INTERFACE_H
