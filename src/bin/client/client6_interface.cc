// Copyright (C) 2013-2017 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <boost/bind.hpp>
#include <client/client_interface.h>
#include <iostream>

using namespace isc::util;

namespace isc {
namespace client {

// Define the constants
const int ClientInterface::ST_BEGIN;
const int ClientInterface::ST_SERVER_DISCOVERY;
const int ClientInterface::ST_AWAITING_RECOGNITION;

const int ClientInterface::EVT_SEND_SOLICIT;
const int ClientInterface::EVT_SOLICIT_RESPONSE_RECEIVED;
const int ClientInterface::EVT_SOLICIT_TIMEOUT;
const int ClientInterface::EVT_SEND_REQUEST;


// Constructor.
ClientInterface::ClientInterface(const std::string& name, int ifindex,
                isc::asiolink::IOServicePtr& io_service) :
    isc::dhcp::Iface(name, ifindex), io_service_(io_service)
    {
}

ClientInterface::~ClientInterface() {
}

void
ClientInterface::defineEvents() {
    // Call superclass impl first.
    StateModel::defineEvents();

    // Define NCT events.
    defineEvent(EVT_SEND_SOLICIT, "EVT_SEND_SOLICIT");
    defineEvent(EVT_SOLICIT_RESPONSE_RECEIVED, "EVT_SOLICIT_RESPONSE_RECEIVED");
    defineEvent(EVT_SOLICIT_TIMEOUT, "EVT_SOLICIT_TIMEOUT");
    defineEvent(EVT_SEND_REQUEST, "EVT_SEND_REQUEST");
    defineEvent(EVT_REQUEST_RESPONSE_RECEIVED, "EVT_REQUEST_RESPONSE_RECEIVED");
    defineEvent(EVT_REQUEST_RESPONSE_TIMEOUT, "EVT_REQUEST_RESPONSE_TIMEOUT");
    defineEvent(EVT_DUPLICATE_TIMEOUT, "EVT_DUPLICATE_TIMEOUT");
    defineEvent(EVT_T1_TIMEOUT, "EVT_T1_TIMEOUT");
    defineEvent(EVT_RENEW_RESPONSE_RECEIVED, "EVT_RENEW_RESPONSE_RECEIVED");
    defineEvent(EVT_RENEW_RESPONSE_TIMEOUT, "EVT_RENEW_RESPONSE_TIMEOUT");
    defineEvent(EVT_T2_TIMEOUT, "EVT_T2_TIMEOUT");
    defineEvent(EVT_RETRANSMISSION_TIMEOUT, "EVT_RETRANSMISSION_TIMEOUT");
}

void
ClientInterface::verifyEvents() {
    // Call superclass impl first.
    StateModel::verifyEvents();

    // Verify events by trying to get them.
    getEvent(EVT_SEND_SOLICIT);
    getEvent(EVT_SOLICIT_RESPONSE_RECEIVED);
    getEvent(EVT_SOLICIT_TIMEOUT);
    getEvent(EVT_SEND_REQUEST);
    getEvent(EVT_REQUEST_RESPONSE_RECEIVED);
    getEvent(EVT_REQUEST_RESPONSE_TIMEOUT);
    getEvent(EVT_DUPLICATE_TIMEOUT);
    getEvent(EVT_T1_TIMEOUT);
    getEvent(EVT_RENEW_RESPONSE_RECEIVED);
    getEvent(EVT_RENEW_RESPONSE_TIMEOUT);
    getEvent(EVT_T2_TIMEOUT);
    getEvent(EVT_RETRANSMISSION_TIMEOUT);
}

void
ClientInterface::defineStates() {
    // Call superclass impl first.
    StateModel::defineStates();
    // This class is "abstract" in that it does not supply handlers for its
    // states, derivations must do that therefore they must define them.

    defineState(ST_BEGIN, "ST_BEGIN",
                boost::bind(&ClientInterface::beginHandler, this));

    defineState(ST_SERVER_DISCOVERY, "ST_SERVER_DISCOVERY",
                boost::bind(&ClientInterface::serverDiscoveryHandler, this));

    defineState(ST_AWAITING_RECOGNITION, "ST_AWAITING_RECOGNITION",
                boost::bind(&ClientInterface::awaitingRecognitionHandler,
                            this));

}

void
ClientInterface::verifyStates() {
    // Call the superclass implementation first
    StateModel::verifyStates();

    // Verify ClientInterface states by attempting to fetch them.
    getState(ST_BEGIN);
    getState(ST_SERVER_DISCOVERY);
    getState(ST_AWAITING_RECOGNITION);
}


// Asynchronous operation completion handler.  Justs post the appropriate
// event and enters the given state.

void
ClientInterface::asynchCompletion(const boost::system::error_code&, int event) {
// TODO: Check error code
    runModel(event);
}


// Begin handler.  Initialise, then transition to SERVER_DISCOVERY

void
ClientInterface::beginHandler() {
    std::cout << "beginHandler()\n";
    // TODO: Initialization

    // Move to the server discovery stage.
    transition(ST_SERVER_DISCOVERY, EVT_SEND_SOLICIT);
}

// Server discovery handler.  Broadcast a SOLICT message, then start a timer
// and issue a read for a response.

void
ClientInterface::serverDiscoveryHandler() {
    if (doOnEntry()) {
        std::cout << "serverDiscoveryHandler()\n";
        postNextEvent(NOP_EVT);

    } else {
        // All events (the completion of the I/O or the expiry of the timer)
        // cause a transition to the AWAITING_RECOGNITION state.
        transition(ST_AWAITING_RECOGNITION, getNextEvent());
    }
}

// Awaiting recognition state. Process the response and timer handlers.

void
ClientInterface::awaitingRecognitionHandler() {
    std::cout << "awaitingRecognitionHandler()\n";

    // Stay in the AWAITING_RECOGNITION state.
    transition(ST_AWAITING_RECOGNITION, NOP_EVT);
}

} // namespace isc::client
} // namespace isc
