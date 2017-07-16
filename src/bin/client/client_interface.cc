// Copyright (C) 2013-2017 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <client/client_interface.h>

using namespace isc::util;

namespace isc {
namespace client {

// Constructor.
ClientInterface(const str::string& name, int ifindex,
                IOServicePtr& io_service) :
    isc::dhcp::Iface(string, ifindex), io_service_(io_service)
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
    defineEvent(EVT_SOLICIT_RESPONSE_TIMEOUT, "EVT_SOLICIT_RESPONSE_TIMEOUT");
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
    getEvent(EVT_SOLICIT_RESPONSE_TIMEOUT);
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

}

} // namespace isc::client
} // namespace isc
