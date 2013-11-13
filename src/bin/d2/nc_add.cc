// Copyright (C) 2013 Internet Systems Consortium, Inc. ("ISC")
//
// Permission to use, copy, modify, and/or distribute this software for any
// purpose with or without fee is hereby granted, provided that the above
// copyright notice and this permission notice appear in all copies.
//
// THE SOFTWARE IS PROVIDED "AS IS" AND ISC DISCLAIMS ALL WARRANTIES WITH
// REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
// AND FITNESS.  IN NO EVENT SHALL ISC BE LIABLE FOR ANY SPECIAL, DIRECT,
// INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
// LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE
// OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
// PERFORMANCE OF THIS SOFTWARE.

#include <d2/d2_log.h>
#include <d2/nc_add.h>

#include <boost/function.hpp>
#include <boost/bind.hpp>

namespace isc {
namespace d2 {

// NameAddTransaction states
const int NameAddTransaction::ADDING_FWD_ADDRS_ST;
const int NameAddTransaction::REPLACING_FWD_ADDRS_ST;
const int NameAddTransaction::REPLACING_REV_PTRS_ST;

// NameAddTransaction events
const int NameAddTransaction::FQDN_IN_USE_EVT;
const int NameAddTransaction::FQDN_NOT_IN_USE_EVT;

NameAddTransaction::
NameAddTransaction(IOServicePtr& io_service,
                   dhcp_ddns::NameChangeRequestPtr& ncr,
                   DdnsDomainPtr& forward_domain,
                   DdnsDomainPtr& reverse_domain)
    : NameChangeTransaction(io_service, ncr, forward_domain, reverse_domain) {
    if (ncr->getChangeType() != isc::dhcp_ddns::CHG_ADD) {
        isc_throw (NameAddTransactionError,
                   "NameAddTransaction, request type must be CHG_ADD");
    }
}

NameAddTransaction::~NameAddTransaction(){
}

void
NameAddTransaction::defineEvents() {
    // Call superclass impl first.
    NameChangeTransaction::defineEvents();

    // Define NCT events.
    defineEvent(FQDN_IN_USE_EVT, "FQDN_IN_USE_EVT");
    defineEvent(FQDN_NOT_IN_USE_EVT, "FQDN_NOT_IN_USE_EVT");
}

void
NameAddTransaction::verifyEvents() {
    // Call superclass impl first.
    NameChangeTransaction::verifyEvents();

    // Verify NCT events.
    getEvent(FQDN_IN_USE_EVT);
    getEvent(FQDN_NOT_IN_USE_EVT);
}

void
NameAddTransaction::defineStates() {
    // Call superclass impl first.
    NameChangeTransaction::defineStates();

    // Define the states.
    defineState(READY_ST, "READY_ST",
             boost::bind(&NameAddTransaction::readyHandler, this));

    defineState(SELECTING_FWD_SERVER_ST, "SELECTING_FWD_SERVER_ST",
             boost::bind(&NameAddTransaction::selectingFwdServerHandler, this));

    defineState(SELECTING_REV_SERVER_ST, "SELECTING_REV_SERVER_ST",
             boost::bind(&NameAddTransaction::selectingRevServerHandler, this));

    defineState(ADDING_FWD_ADDRS_ST, "ADDING_FWD_ADDRS_ST",
             boost::bind(&NameAddTransaction::addingFwdAddrsHandler, this));

    defineState(REPLACING_FWD_ADDRS_ST, "REPLACING_FWD_ADDRS_ST",
             boost::bind(&NameAddTransaction::replacingFwdAddrsHandler, this));

    defineState(REPLACING_REV_PTRS_ST, "REPLACING_REV_PTRS_ST",
             boost::bind(&NameAddTransaction::replacingRevPtrsHandler, this));

    defineState(PROCESS_TRANS_OK_ST, "PROCESS_TRANS_OK_ST",
             boost::bind(&NameAddTransaction::processAddOkHandler, this));

    defineState(PROCESS_TRANS_FAILED_ST, "PROCESS_TRANS_FAILED_ST",
             boost::bind(&NameAddTransaction::processAddFailedHandler, this));

}
void
NameAddTransaction::verifyStates() {
    // Call superclass impl first.
    NameChangeTransaction::verifyStates();

    // Verify NCT states. This ensures that derivations provide the handlers.
    getState(ADDING_FWD_ADDRS_ST);
    getState(REPLACING_FWD_ADDRS_ST);
    getState(REPLACING_REV_PTRS_ST);
}

void
NameAddTransaction::readyHandler() {
    switch(getNextEvent()) {
    case START_EVT:
        if (getForwardDomain()) {
            // Request includes a forward change, do that first.
            transition(SELECTING_FWD_SERVER_ST, SELECT_SERVER_EVT);
        } else {
            // Reverse change only, transition accordingly.
            transition(SELECTING_REV_SERVER_ST, SELECT_SERVER_EVT);
        }

        break;
    default:
        // Event is invalid.
        isc_throw(NameAddTransactionError,
                  "Wrong event for context: " << getContextStr());
    }
}

void
NameAddTransaction::selectingFwdServerHandler() {
    switch(getNextEvent()) {
    case SELECT_SERVER_EVT:
        // First time through for this transaction, so initialize server
        // selection.
        initServerSelection(getForwardDomain());
        break;
    case SERVER_IO_ERROR_EVT:
        // We failed to communicate with current server. Attempt to select
        // another one below.
        break;
    default:
        // Event is invalid.
        isc_throw(NameAddTransactionError,
                  "Wrong event for context: " << getContextStr());
    }

    // Select the next server from the list of forward servers.
    if (selectNextServer()) {
        // We have a server to try.
        transition(ADDING_FWD_ADDRS_ST, SERVER_SELECTED_EVT);
    }
    else {
        // Server list is exhausted, so fail the transaction.
        transition(PROCESS_TRANS_FAILED_ST, NO_MORE_SERVERS_EVT);
    }
}

void
NameAddTransaction::addingFwdAddrsHandler() {
    if (doOnEntry()) {
        // Clear the request on initial transition. This allows us to reuse
        // the request on retries if necessary.
        clearDnsUpdateRequest();
    }

    switch(getNextEvent()) {
    case SERVER_SELECTED_EVT:
        if (!getDnsUpdateRequest()) {
            // Request hasn't been constructed yet, so build it.
            buildAddFwdAddressRequest();
        }

        // Call sendUpdate() to initiate the async send. Note it also sets
        // next event to NOP_EVT.
        sendUpdate();
        break;

    case IO_COMPLETED_EVT: {
        switch (getDnsUpdateStatus()) {
        case DNSClient::SUCCESS: {
            // We successfully received a response packet from the server.
            const dns::Rcode& rcode = getDnsUpdateResponse()->getRcode();
            if (rcode == dns::Rcode::NOERROR()) {
                // We were able to add it. Mark it as done.
                setForwardChangeCompleted(true);

                // If request calls for reverse update then do that next,
                // otherwise we can process ok.
                if (getReverseDomain()) {
                    transition(SELECTING_REV_SERVER_ST, SELECT_SERVER_EVT);
                } else {
                    transition(PROCESS_TRANS_OK_ST, UPDATE_OK_EVT);
                }
            } else if (rcode == dns::Rcode::YXDOMAIN()) {
                // FQDN is in use so we need to attempt to replace
                // forward address.
                transition(REPLACING_FWD_ADDRS_ST, FQDN_IN_USE_EVT);
            } else {
                // Per RFC4703 any other value means cease.
                // If we get not authorized should we try the next server in
                // the list? @todo  This needs some discussion perhaps.
                LOG_ERROR(dctl_logger, DHCP_DDNS_FORWARD_ADD_REJECTED)
                          .arg(getCurrentServer()->getIpAddress())
                          .arg(getNcr()->getFqdn())
                          .arg(rcode.getCode());
                transition(PROCESS_TRANS_FAILED_ST, UPDATE_FAILED_EVT);
            }

            break;
        }

        case DNSClient::TIMEOUT:
        case DNSClient::OTHER:
            // We couldn't send to the current server, log it and set up
            // to select the next server for a retry.
            // @note For now we treat OTHER as an IO error like TIMEOUT. It
            // is not entirely clear if this is accurate.
            LOG_ERROR(dctl_logger, DHCP_DDNS_FORWARD_ADD_IO_ERROR)
                      .arg(getCurrentServer()->getIpAddress())
                      .arg(getNcr()->getFqdn());

            retryTransition(SELECTING_FWD_SERVER_ST);
            break;

        case DNSClient::INVALID_RESPONSE:
            // A response was received but was corrupt. Retry it like an IO
            // error.
            LOG_ERROR(dctl_logger, DHCP_DDNS_FORWARD_ADD_RESP_CORRUPT)
                      .arg(getNcr()->getFqdn())
                      .arg(getCurrentServer()->getIpAddress());

            retryTransition(SELECTING_FWD_SERVER_ST);
            break;

        default:
            // Any other value and we will fail this transaction, something
            // bigger is wrong.
            LOG_ERROR(dctl_logger, DHCP_DDNS_FORWARD_ADD_UNKNOWN_FAILURE)
                      .arg(getNcr()->getFqdn())
                      .arg(getCurrentServer()->getIpAddress());

            transition(PROCESS_TRANS_FAILED_ST, UPDATE_FAILED_EVT);
            break;
        } // end switch on dns_status

        break;
    } // end case IO_COMPLETE_EVT

    default:
        // Event is invalid.
        isc_throw(NameAddTransactionError,
                  "Wrong event for context: " << getContextStr());
    }
}

void
NameAddTransaction::replacingFwdAddrsHandler() {
    if (doOnEntry()) {
        // Clear the request on initial transition. This allows us to reuse
        // the request on retries if necessary.
        clearDnsUpdateRequest();
    }

    switch(getNextEvent()) {
    case FQDN_IN_USE_EVT:
    case SERVER_SELECTED_EVT:
        if (!getDnsUpdateRequest()) {
            // Request hasn't been constructed yet, so build it.
            buildReplaceFwdAddressRequest();
        }

        // Call sendUpdate() to initiate the async send. Note it also sets
        // next event to NOP_EVT.
        sendUpdate();
        break;

    case IO_COMPLETED_EVT: {
        switch (getDnsUpdateStatus()) {
        case DNSClient::SUCCESS: {
            // We successfully received a response packet from the server.
            const dns::Rcode& rcode = getDnsUpdateResponse()->getRcode();
            if (rcode == dns::Rcode::NOERROR()) {
                // We were able to replace the forward mapping. Mark it as done.
                setForwardChangeCompleted(true);

                // If request calls for reverse update then do that next,
                // otherwise we can process ok.
                if (getReverseDomain()) {
                    transition(SELECTING_REV_SERVER_ST, SELECT_SERVER_EVT);
                } else {
                    transition(PROCESS_TRANS_OK_ST, UPDATE_OK_EVT);
                }
            } else if (rcode == dns::Rcode::NXDOMAIN()) {
                // FQDN is NOT in use so go back and do the forward add address.
                // Covers the case that it was there when we tried to add it,
                // but has since been removed per RFC 4703.
                transition(ADDING_FWD_ADDRS_ST, SERVER_SELECTED_EVT);
            } else {
                // Per RFC4703 any other value means cease.
                // If we get not authorized should try the next server in
                // the list? @todo  This needs some discussion perhaps.
                LOG_ERROR(dctl_logger, DHCP_DDNS_FORWARD_REPLACE_REJECTED)
                          .arg(getCurrentServer()->getIpAddress())
                          .arg(getNcr()->getFqdn())
                          .arg(rcode.getCode());
                transition(PROCESS_TRANS_FAILED_ST, UPDATE_FAILED_EVT);
            }

            break;
        }

        case DNSClient::TIMEOUT:
        case DNSClient::OTHER:
            // We couldn't send to the current server, log it and set up
            // to select the next server for a retry.
            // @note For now we treat OTHER as an IO error like TIMEOUT. It
            // is not entirely clear if this is accurate.
            LOG_ERROR(dctl_logger, DHCP_DDNS_FORWARD_REPLACE_IO_ERROR)
                      .arg(getCurrentServer()->getIpAddress())
                      .arg(getNcr()->getFqdn());

            // If we are out of retries on this server, we go back and start
            // all over on a new server.
            retryTransition(SELECTING_FWD_SERVER_ST);
            break;

        case DNSClient::INVALID_RESPONSE:
            // A response was received but was corrupt. Retry it like an IO
            // error.
            LOG_ERROR(dctl_logger, DHCP_DDNS_FORWARD_REPLACE_RESP_CORRUPT)
                      .arg(getNcr()->getFqdn())
                      .arg(getCurrentServer()->getIpAddress());

            // If we are out of retries on this server, we go back and start
            // all over on a new server.
            retryTransition(SELECTING_FWD_SERVER_ST);
            break;

        default:
            // Any other value and we will fail this transaction, something
            // bigger is wrong.
            LOG_ERROR(dctl_logger, DHCP_DDNS_FORWARD_REPLACE_UNKNOWN_FAILURE)
                      .arg(getNcr()->getFqdn())
                      .arg(getCurrentServer()->getIpAddress());

            transition(PROCESS_TRANS_FAILED_ST, UPDATE_FAILED_EVT);
            break;
        } // end switch on dns_status

        break;
    } // end case IO_COMPLETE_EVT

    default:
        // Event is invalid.
        isc_throw(NameAddTransactionError,
                  "Wrong event for context: " << getContextStr());
    }
}

void
NameAddTransaction::selectingRevServerHandler() {
    switch(getNextEvent()) {
    case SELECT_SERVER_EVT:
        // First time through for this transaction, so initialize server
        // selection.
        initServerSelection(getReverseDomain());
        break;
    case SERVER_IO_ERROR_EVT:
        // We failed to communicate with current server. Attempt to select
        // another one below.
        break;
    default:
        // Event is invalid.
        isc_throw(NameAddTransactionError,
                  "Wrong event for context: " << getContextStr());
    }

    // Select the next server from the list of forward servers.
    if (selectNextServer()) {
        // We have a server to try.
        transition(REPLACING_REV_PTRS_ST, SERVER_SELECTED_EVT);
    }
    else {
        // Server list is exhausted, so fail the transaction.
        transition(PROCESS_TRANS_FAILED_ST, NO_MORE_SERVERS_EVT);
    }
}


void
NameAddTransaction::replacingRevPtrsHandler() {
    if (doOnEntry()) {
        // Clear the request on initial transition. This allows us to reuse
        // the request on retries if necessary.
        clearDnsUpdateRequest();
    }

    switch(getNextEvent()) {
    case SERVER_SELECTED_EVT:
        if (!getDnsUpdateRequest()) {
            // Request hasn't been constructed yet, so build it.
            buildReplaceRevPtrsRequest();
        }

        // Call sendUpdate() to initiate the async send. Note it also sets
        // next event to NOP_EVT.
        sendUpdate();
        break;

    case IO_COMPLETED_EVT: {
        switch (getDnsUpdateStatus()) {
        case DNSClient::SUCCESS: {
            // We successfully received a response packet from the server.
            const dns::Rcode& rcode = getDnsUpdateResponse()->getRcode();
            if (rcode == dns::Rcode::NOERROR()) {
                // We were able to update the reverse mapping. Mark it as done.
                setReverseChangeCompleted(true);
                transition(PROCESS_TRANS_OK_ST, UPDATE_OK_EVT);
            } else {
                // Per RFC4703 any other value means cease.
                // If we get not authorized should try the next server in
                // the list? @todo  This needs some discussion perhaps.
                LOG_ERROR(dctl_logger, DHCP_DDNS_REVERSE_REPLACE_REJECTED)
                          .arg(getCurrentServer()->getIpAddress())
                          .arg(getNcr()->getFqdn())
                          .arg(rcode.getCode());
                transition(PROCESS_TRANS_FAILED_ST, UPDATE_FAILED_EVT);
            }

            break;
        }

        case DNSClient::TIMEOUT:
        case DNSClient::OTHER:
            // We couldn't send to the current server, log it and set up
            // to select the next server for a retry.
            // @note For now we treat OTHER as an IO error like TIMEOUT. It
            // is not entirely clear if this is accurate.
            LOG_ERROR(dctl_logger, DHCP_DDNS_REVERSE_REPLACE_IO_ERROR)
                      .arg(getCurrentServer()->getIpAddress())
                      .arg(getNcr()->getFqdn());

            // If we are out of retries on this server, we go back and start
            // all over on a new server.
            retryTransition(SELECTING_REV_SERVER_ST);
            break;

        case DNSClient::INVALID_RESPONSE:
            // A response was received but was corrupt. Retry it like an IO
            // error.
            LOG_ERROR(dctl_logger, DHCP_DDNS_REVERSE_REPLACE_RESP_CORRUPT)
                      .arg(getNcr()->getFqdn())
                      .arg(getCurrentServer()->getIpAddress());

            // If we are out of retries on this server, we go back and start
            // all over on a new server.
            retryTransition(SELECTING_REV_SERVER_ST);
            break;

        default:
            // Any other value and we will fail this transaction, something
            // bigger is wrong.
            LOG_ERROR(dctl_logger, DHCP_DDNS_REVERSE_REPLACE_UNKNOWN_FAILURE)
                      .arg(getNcr()->getFqdn())
                      .arg(getCurrentServer()->getIpAddress());

            transition(PROCESS_TRANS_FAILED_ST, UPDATE_FAILED_EVT);
            break;
        } // end switch on dns_status

        break;
    } // end case IO_COMPLETE_EVT

    default:
        // Event is invalid.
        isc_throw(NameAddTransactionError,
                  "Wrong event for context: " << getContextStr());
    }
}

void
NameAddTransaction::processAddOkHandler() {
    switch(getNextEvent()) {
    case UPDATE_OK_EVT:
        // @todo do we need a log statement here?
        setNcrStatus(dhcp_ddns::ST_COMPLETED);
        endModel();
        break;
    default:
        // Event is invalid.
        isc_throw(NameAddTransactionError,
                  "Wrong event for context: " << getContextStr());
    }
}

void
NameAddTransaction::processAddFailedHandler() {
    switch(getNextEvent()) {
    case UPDATE_FAILED_EVT:
        // @todo do we need a log statement here?
        setNcrStatus(dhcp_ddns::ST_FAILED);
        endModel();
        break;
    default:
        // Event is invalid.
        isc_throw(NameAddTransactionError,
                  "Wrong event for context: " << getContextStr());
    }
}

void
NameAddTransaction::buildAddFwdAddressRequest() {
    // @todo For now construct a blank outbound message.
    D2UpdateMessagePtr msg(new D2UpdateMessage(D2UpdateMessage::OUTBOUND));
    setDnsUpdateRequest(msg);
}

void
NameAddTransaction::buildReplaceFwdAddressRequest() {
    // @todo For now construct a blank outbound message.
    D2UpdateMessagePtr msg(new D2UpdateMessage(D2UpdateMessage::OUTBOUND));
    setDnsUpdateRequest(msg);
}

void
NameAddTransaction::buildReplaceRevPtrsRequest() {
    // @todo For now construct a blank outbound message.
    D2UpdateMessagePtr msg(new D2UpdateMessage(D2UpdateMessage::OUTBOUND));
    setDnsUpdateRequest(msg);
}

} // namespace isc::d2
} // namespace isc
