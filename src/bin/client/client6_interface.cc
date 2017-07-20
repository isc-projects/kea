// Copyright (C) 2013-2017 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <boost/bind.hpp>
#include <client/client6_interface.h>
#include <client/client_log.h>
#include <iostream>

using namespace isc::util;

namespace isc {
namespace client {

// Constructor.
Client6Interface::Client6Interface(const std::string& name, int ifindex,
                isc::asiolink::IOServicePtr& io_service) :
                isc::dhcp::Iface(name, ifindex), isc::util::StateModel(),
                io_service_(io_service), solicit_timer_running_(false) {
}

// Destructor
Client6Interface::~Client6Interface() {
}

// Convenience function to log that a state has been entered with an unexpected
// event.

void
Client6Interface::logUnexpectedEvent() {
    LOG_ERROR(client_logger, CLIENT6_UNEXPECTED_EVENT)
              .arg(getStateLabel(getCurrState()))
              .arg(getEventLabel(getNextEvent()));
}

// Event methods.

void
Client6Interface::defineEvents() {
    // Call superclass impl first.
    StateModel::defineEvents();

    defineEvent(EVT_SERVER_DISCOVERY, "EVT_SERVER_DISCOVERY");
    defineEvent(EVT_SEND_SOLICIT, "EVT_SEND_SOLICIT");
    defineEvent(EVT_ADVERTISE_RECEIVED, "EVT_ADVERTISE_RECEIVED");
    defineEvent(EVT_SOLICIT_TIMEOUT, "EVT_SOLICIT_TIMEOUT");
    defineEvent(EVT_SEND_REQUEST, "EVT_SEND_REQUEST");
    defineEvent(EVT_REQUEST_TIMEOUT, "EVT_REQUEST_TIMEOUT");
    defineEvent(EVT_REPLY_RECEIVED, "EVT_REPLY_RECEIVED");
    defineEvent(EVT_DUPLICATE_CHECK, "EVT_DUPLICATE_CHECK");
    defineEvent(EVT_DUPLICATE_TIMEOUT, "EVT_DUPLICATE_TIMEOUT");
    defineEvent(EVT_CONFIGURED, "EVT_CONFIGURED");
    defineEvent(EVT_START_RENEW, "EVT_START_RENEW");
    defineEvent(EVT_RESEND_RENEW, "EVT_RESEND_RENEW");
    defineEvent(EVT_REBINDING, "EVT_REBINDING");
    defineEvent(EVT_PROCESS_REBINDING, "EVT_PROCESS_REBINDING");
    defineEvent(EVT_REBINDING_TIMEOUT, "EVT_REBINDING_TIMEOUT");
}

void
Client6Interface::verifyEvents() {
    // Call superclass impl first.
    StateModel::verifyEvents();

    // Verify events by trying to get them.
    getEvent(EVT_SERVER_DISCOVERY);
    getEvent(EVT_SEND_SOLICIT);
    getEvent(EVT_ADVERTISE_RECEIVED);
    getEvent(EVT_SOLICIT_TIMEOUT);
    getEvent(EVT_SEND_REQUEST);
    getEvent(EVT_REQUEST_TIMEOUT);
    getEvent(EVT_REPLY_RECEIVED);
    getEvent(EVT_DUPLICATE_CHECK);
    getEvent(EVT_DUPLICATE_TIMEOUT);
    getEvent(EVT_CONFIGURED);
    getEvent(EVT_START_RENEW);
    getEvent(EVT_RESEND_RENEW);
    getEvent(EVT_REBINDING);
    getEvent(EVT_PROCESS_REBINDING);
    getEvent(EVT_REBINDING_TIMEOUT);
}

// State methods

void
Client6Interface::defineStates() {
    // Call superclass impl first.
    StateModel::defineStates();

    // This class is "abstract" in that it does not supply handlers for its
    // states, derivations must do that therefore they must define them.
    defineState(ST_BEGIN, "ST_BEGIN",
                boost::bind(&Client6Interface::beginHandler, this));
    defineState(ST_SERVER_DISCOVERY, "ST_SERVER_DISCOVERY",
                boost::bind(&Client6Interface::serverDiscoveryHandler, this));
    defineState(ST_SEND_SOLICIT, "ST_SEND_SOLICIT",
                boost::bind(&Client6Interface::sendSolicitHandler, this));
    defineState(ST_SOLICIT_TIMEOUT, "ST_SOLICIT_TIMEOUT",
                boost::bind(&Client6Interface::solicitTimeoutHandler, this));
    defineState(ST_ADVERTISE_RECEIVED, "ST_ADVERTISE_RECEIVED",
                boost::bind(&Client6Interface::advertiseReceivedHandler, this));
    defineState(ST_SEND_REQUEST, "ST_SEND_REQUEST",
                boost::bind(&Client6Interface::sendRequestHandler, this));
    defineState(ST_REQUEST_TIMEOUT, "ST_REQUEST_TIMEOUT",
                boost::bind(&Client6Interface::requestTimeoutHandler, this));
    defineState(ST_REPLY_RECEIVED, "ST_REPLY_RECEIVED",
                boost::bind(&Client6Interface::replyReceivedHandler, this));
    defineState(ST_DUPLICATE_CHECK, "ST_DUPLICATE_CHECK",
                boost::bind(&Client6Interface::duplicateCheckHandler, this));
    defineState(ST_DUPLICATE_TIMEOUT, "ST_DUPLICATE_TIMEOUT",
                boost::bind(&Client6Interface::duplicateTimeoutHandler, this));
    defineState(ST_CONFIGURED, "ST_CONFIGURED",
                boost::bind(&Client6Interface::configuredHandler, this));
    defineState(ST_START_RENEW, "ST_START_RENEW",
                boost::bind(&Client6Interface::startRenewHandler, this));
    defineState(ST_RESEND_RENEW, "ST_RESEND_RENEW",
                boost::bind(&Client6Interface::resendRenewHandler, this));
    defineState(ST_RENEW_COMPLETE, "ST_RENEW_COMPLETE",
                boost::bind(&Client6Interface::renewCompleteHandler, this));
    defineState(ST_REBINDING, "ST_REBINDING",
                boost::bind(&Client6Interface::rebindingHandler, this));
    defineState(ST_PROCESS_REBINDING, "ST_PROCESS_REBINDING",
                boost::bind(&Client6Interface::processRebindingHandler, this));
    defineState(ST_REBINDING_TIMEOUT, "ST_REBINDING_TIMEOUT",
                boost::bind(&Client6Interface::rebindingTimeoutHandler, this));
    defineState(ST_BEGIN, "ST_BEGIN",
                boost::bind(&Client6Interface::beginHandler, this));
}

void
Client6Interface::verifyStates() {
    // Call the superclass implementation first
    StateModel::verifyStates();

    // Verify Client6Interface states by attempting to fetch them.
    getState(ST_BEGIN);
    getState(ST_SERVER_DISCOVERY);
    getState(ST_SEND_SOLICIT);
    getState(ST_SOLICIT_TIMEOUT);
    getState(ST_ADVERTISE_RECEIVED);
    getState(ST_SEND_REQUEST);
    getState(ST_REQUEST_TIMEOUT);
    getState(ST_REPLY_RECEIVED);
    getState(ST_DUPLICATE_CHECK);
    getState(ST_DUPLICATE_TIMEOUT);
    getState(ST_CONFIGURED);
    getState(ST_START_RENEW);
    getState(ST_RESEND_RENEW);
    getState(ST_RENEW_COMPLETE);
    getState(ST_REBINDING);
    getState(ST_PROCESS_REBINDING);
    getState(ST_REBINDING_TIMEOUT);
}


// Asynchronous operation completion handler.  Justs post the appropriate
// event and enters the given state.

void
Client6Interface::asynchCompletion(const boost::system::error_code&, int event) {
// TODO: Check error code
    runModel(event);
}


// BEGIN State Handler
//
// The entry point of the state machine, this opens sockets on the interface
// and performs other initialization.

void
Client6Interface::beginHandler() {
    std::cout << "beginHandler()\n";

    switch (getNextEvent()) {

        case START_EVT:
            // TODO: Initialization

            // Move to the server discovery stage.
            transition(ST_SERVER_DISCOVERY, EVT_SERVER_DISCOVERY);
            break;

        default:
            logUnexpectedEvent();
            break;
    }

    return;
}

// SERVER_DISCOVERY State Handler
//
// Initializes list of available servers (to empty), then moves to the next
// state.  The split between BEGIN and this state is BEGIN contains the
// initialization that only needs to be done once for the interface, this
// state holds teh initialization that needs to be performed every time we
// decide to try and find servers.

void
Client6Interface::serverDiscoveryHandler() {
    std::cout << "serverDiscoveryHandler()\n";

    switch (getNextEvent()) {

        case EVT_SERVER_DISCOVERY:
            // Initialize list of servers

            // TODO: Initialize list of servers

            transition(ST_SEND_SOLICIT, EVT_SEND_SOLICIT);
            break;

        default:
            logUnexpectedEvent();
            break;
    }

    return;
}

// SEND_SOLICIT State Handler
//
// The client sends a SOLICIT message then waits in this state until either
// an ADVERTISE message is received from a server, or the timer associated
// with the sending of the SOLICIT has timed out.

void
Client6Interface::sendSolicitHandler() {
    std::cout << "sendSOlicitHandler()\n";

    switch (getNextEvent()) {

        case EVT_SEND_SOLICIT:
            // Entry via an internal transfer from another state.  Broadcast
            // the SOLICIT message to all listening servers.

            // TODO: Send the SOLICIT message

            // Issue the read for the ADVERTISE message
            // TODO: Issue read.

            // Kick off the solicit timer if it is not already running.
            if (! solicit_timer_running_) {
                // TODO: Start solicit timer

                solicit_timer_running_ = true;
            }

            // Now exit the state.  The state will be re-entered when either
            // the ADVERTISE message is received or when the solicit timer
            // times out.
            postNextEvent(NOP_EVT);
            break;

        case EVT_ADVERTISE_RECEIVED:
            // Entered the state because a server responded with an ADVERTISE
            // message.
            transition(ST_ADVERTISE_RECEIVED, EVT_ADVERTISE_RECEIVED);
            break;

        case EVT_SOLICIT_TIMEOUT:
            // Entered the state because the timer started when we sent the
            // first SOLICIT message has finally expired.
            transition(ST_SOLICIT_TIMEOUT, EVT_SOLICIT_TIMEOUT);
            break;

        default:
            logUnexpectedEvent();
            break;
    }

    return;
}

} // namespace isc::client
} // namespace isc
