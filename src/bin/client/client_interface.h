// Copyright (C) 2013-2017 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef CLIENT_INTERFACE_H
#define CLIENT_INTERFACE_H

#include <asiolink/io_service.h>
#include <exceptions/exceptions.h>
#include <util/state_model.h>

#include <string>

namespace isc {
namespace client {

/// @brief Thrown if the some error is encountered
class ClientInterfaceError : public isc::Exception {
public:
    ClientInterfaceError(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) {};
};

/// @brief Client Interface
///
/// This is the class that represents an interface that the client is managing.
/// It has a dual inheritance: the first parent is the Iface class,
/// representing a physical interface. It contains all information, e.g.
/// name, MAC address etc.
///
/// The other parent is the StateModel, which defines the state the interface
/// is in and handles the logic for the process of acquring an address. Each
/// state has an associate method, which is invoked when the  state is entered.
/// This will usually carry out a certain amount of processing before
/// initiating an asynchronous operation (either an I/O or setting a timer).
/// The callback handlers on these operations are methods in this class and
/// after performing the necessary processing, cause a transition to some other
/// state.
///
/// The processing required for the client is quite lengthy and is described in
/// http://kea.isc.org/wiki/ClientDesign.

class ClientInterface : public isc::util::StateModel, isc::dhcp::Iface {
public:

    //@{ States

    /// @brief ST_BEGIN - Initialization
    ///
    /// The entry point into the state machine.  The relevant sockets are
    /// opened, and the timer interval initialzied.
    static const int ST_BEGIN =  SM_DERIVED_STATE_MIN + 1;

    /// @brief ST_SERVER_DISCOVERY - Initiate I/O to find servers
    ///
    /// Sends a SOLICIT meassage on the relevant interface and starts a timer.
    /// A wait state is then entered until the timer expires.
    static const int ST_ SERVER_DISCOVERY = SM_DERIVED_STATE_MIN + 2;

    /// @brief ST_AWAITING_RECOGNITION - Wait for server to respond
    ///
    /// A request has been broadcast, so we are now waiting for a server to
    /// respond.
    static const int ST_AWAITING_RECOGNITION = SM_DERIVED_STATE_MIN + 3;

    /// @brief ST_SEND_REQUEST - Send REQUEST to server
    ///
    /// One or more servers have responded, so select a server and send it
    /// a REQUEST.
    static const int ST_SEND_REQUEST = SM_DERIVED_STATE_MIN +4;

    /// @brief ST_AWAITING_RESPONSE - Await response from chosen server
    ///
    /// After a request has been sent to the selected server, the client must
    /// wait for a response.
    static const int ST_AWAITING_RESPONSE = SM_DERIVED_STATE_MIN + 5;

    /// @brief ST_DUPLICATE_CHECK - Look for address already in use
    ///
    /// Before starting to use the address, we need to wait for a bit to ensure
    /// that the address is not already in use.
    static const int ST_DUPLICATE_CHECK = SM_DERIVED_STATE_MIN + 6;

    /// @brief ST_DUPLICATE_CHECK_TIMEOUT - Duplicate check period has ended
    ///
    /// The waiting period for the duplicate check has ended, so now process
    /// the results.
    static const int ST_DUPLICATE_CHECK_TIMEOUT = SM_DERIVED_STATE_MIN + 7;

    /// @brief ST_CONFIGURED - Successful configuration
    ///
    /// The client has now been successfully configured, so now prepare it for
    /// renewing its configuration.
    static const int ST_CONFIGURED = SM_DERIVED_STATE_MIN + 8;

    /// @brief ST_START_RENEW - Start renewal process
    ///
    /// Send a RENEW message to the server from which we originally got our
    /// configuration and start all the relavnt timers associated with this
    /// process
    static const int ST_START_RENEW = SM_DERIVED_STATE_MIN + 9;

    /// @brief ST_RESEND_RENEW - Resend RENEW request
    static const int ST_RENEW_COMPLETE = SM_DERIVED_STATE_MIN + 10;

    /// @brief ST_RESEND_RENEW - Response to RENEW request received
    static const int ST_RENEW_COMPLETE = SM_DERIVED_STATE_MIN + 11;

    /// @brief ST_REBINDING - Handle rebinding
    ///
    /// The client was unable to renew its configuration, so move to the
    /// rebinding processing.
    static const int REBINDING = SM_DERIVED_STATE_MIN + 12;

    //@}

    //@{ Events

    /// @brief EVT_SEND_SOLICT - Trigger sending of SOLICIT message to server
    static const int EVT_SEND_SOLICIT = SM_DERIVED_EVENT_MIN + 1;

    /// @brief EVT_SOLICIT_RESPONSE_RECEIVED - Received response to SOLICT
    ///
    /// The server has responded with a message (that should be an ADVERTISE
    /// message).
    static const int EVT_SOLICIT_RESPONSE_RECEIVED = SM_DERIVED_EVENT_MIN + 2;

    /// @brief EVT_SOLICIT_TIMEOUT - No response to SOLICIT message
    static const int EVT_SOLICIT_TIMEOUT = SM_DERIVED_EVENT_MIN +  3;

    /// @brief - EVT_SEND_REQUEST - Initiate sending of REQUEST to server
    static const int EVT_SEND_REQUEST = SM_DERIVED_EVENT_MIN +  4;

    /// @brief EVT_REQUEST_RESPONSE_RECEIVED - Received response to REQUEST
    ///
    /// The server has responded to the client's REQUEST message with a response
    /// that should be a REPLY message.
    static const int EVT_REQUEST_RESPONSE_RECEIVED = SM_DERIVED_EVENT_MIN + 5;

    /// @brief EVT_REQUEST_RESPONSE_TIMEOUT - No response to REQUEST message
    static const int EVT_REQUEST_RESPONSE_TIMEOUT = SM_DERIVED_EVENT_MIN + 6;

    /// @brief EVT_DUPLICATE_TIMEOUT - Duplicate check timer has expired
    static const int EVT_DUPLICATE_TIMEOUT = SM_DERIVED_EVENT_MIN + 7;

    /// @brief EVT_T1_TIMEOUT - Timeout of T1 Timer
    static const int EVT_T1_TIMEOUT = SM_DERIVED_EVENT_MIN + 8;

    /// @brief EVT_RENEW_RESPONSE_RECEIVED - Received response to RENEW request
    static const int EVT_RENEW_RESPONSE_RECEIVED = SM_DERIVED_EVENT_MIN + 9;

    /// @brief EVT_RENEW_RESPONSE_TIMEOUT - RENEW response request timed out
    static const int EVT_RENEW_RESPONSE_TIMEOUT = SM_DERIVED_EVENT_MIN + 10;

    /// @brief EVT_T2_TIMEOUT - Timeout of T2 Timer
    static const int EVT_T2_TIMEOUT = SM_DERIVED_EVENT_MIN + 11;

    /// @brief EVT_RETRANSMISSION_TIMEOUT - Timeout of RETRANSMISSION Timer
    static const int EVT_RETRANSMISSION_TIMEOUT = SM_DERIVED_EVENT_MIN + 12;

    //@}


    /// @brief Constructor
    ///
    /// @param name Name of the interface
    /// @param index Index of the interface
    /// @param io_service Pointer to the IOService object used to keep track of
    /// all asynchronous operations.
    ClientInterface(const std::string& name, int ifindex,
                    IOServicePtr& io_service);

    /// @brief Destructor
    virtual ~ClientInterface();

    /// @brief Adds events defined by ClientInterface to the event set.
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

    /// @brief Adds states defined by ClientInterface to the state set.
    ///
    /// This method adds the states associated with the ClientInterface to
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
    /// then this implementation to verify states defined by ClientInterface.
    ///
    /// @throw StateModelError if an event value is undefined.
    virtual void verifyStates();


    //@{ State Methods

    /// @brief State handler for BEGIN
    ///
    /// Entered from:
    ///     INIT_ST with next event of START_EVT
    ///
    /// BEGIN is the state the model transitions into when the method
    /// startTransaction is called,  It is the entry point into the state
    /// machine.  It performs all the initialization.
    ///
    /// Transitions to:
    /// - SERVER_DISCOVERY with the next event of EVT_SEND_SOLICIT.  This is an
    /// unconditional transition.
    void beginHandler();

    /// @brief State handler for SERVER_DISCOVERY
    ///
    /// Entered from:
    ///     BEGIN with next event of EVT_SEND_SOLICIT
    ///     AWAITING_RECOGNITION with next event of EVT_SEND_SOLICIT
    ///     SEND_REQUEST with next event of EVT_SEND_SOLICIT
    ///
    /// SERVER_DISCOVERY is the state that initiates the discovery of servers.
    /// It initializes the list of servers, then broadcasts the SOLICIT message.
    /// It then kicks off an asynchronous read, as well as a read timer.
    ///
    /// Transitions to:
    /// - AWAITING_RECOGNITION with next event of EVT_SOLICIT_RESPONSE RECEIVED
    /// - AWAITING_RECOGNITION with next event of EVT_SOLICIT_TIMEOUT
    void serverDiscoveryHandler();

    //@}

    /// @brief Asynchronous Operation Completion Handler
    ///
    /// Called when any asynchronous option completes, it causes the state
    /// machine to transition to the next state.
    ///
    /// @param ec System error code
    /// @param next_state State to which a transition should be made
    /// @param event Event that causes the transition
    void asynchCompletion(const boost::system::error_code& ec,
                          int next_state, int event);


    /// @brief Fetches the IOService the transaction uses for IO processing.
    ///
    /// @return returns a const pointer to the IOService.
    const asiolink::IOServicePtr& getIOService() {
        return (io_service_);
    }

private:
    /// @brief The IOService which should be used to for IO processing.
    asiolink::IOServicePtr io_service_;
};

/// @brief Defines a pointer to a ClientInterface
typedef boost::shared_ptr<ClientInterface> ClientInterfacePtr;

} // namespace isc::client
} // namespace isc
#endif
