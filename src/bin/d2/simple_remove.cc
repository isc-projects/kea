// Copyright (C) 2013-2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <d2/simple_remove.h>
#include <d2srv/d2_cfg_mgr.h>
#include <d2srv/d2_log.h>

#include <functional>

namespace isc {
namespace d2 {


// SimpleRemoveTransaction states
const int SimpleRemoveTransaction::REMOVING_FWD_RRS_ST;
const int SimpleRemoveTransaction::REMOVING_REV_PTRS_ST;

// SimpleRemoveTransaction events
// Currently SimpleRemoveTransaction does not define any events.

SimpleRemoveTransaction::
SimpleRemoveTransaction(asiolink::IOServicePtr& io_service,
                   dhcp_ddns::NameChangeRequestPtr& ncr,
                   DdnsDomainPtr& forward_domain,
                   DdnsDomainPtr& reverse_domain,
                   D2CfgMgrPtr& cfg_mgr)
    : NameChangeTransaction(io_service, ncr, forward_domain, reverse_domain,
                            cfg_mgr) {
    if (ncr->getChangeType() != isc::dhcp_ddns::CHG_REMOVE) {
        isc_throw (SimpleRemoveTransactionError,
                   "SimpleRemoveTransaction, request type must be CHG_REMOVE");
    }
}

SimpleRemoveTransaction::~SimpleRemoveTransaction(){
}

void
SimpleRemoveTransaction::defineEvents() {
    // Call superclass impl first.
    NameChangeTransaction::defineEvents();

    // Define SimpleRemoveTransaction events.
    // Currently SimpleRemoveTransaction does not define any events.
    // defineEvent(TBD_EVENT, "TBD_EVT");
}

void
SimpleRemoveTransaction::verifyEvents() {
    // Call superclass implementation first to verify its events. These are
    // events common to all transactions, and they must be defined.
    // SELECT_SERVER_EVT
    // SERVER_SELECTED_EVT
    // SERVER_IO_ERROR_EVT
    // NO_MORE_SERVERS_EVT
    // IO_COMPLETED_EVT
    // UPDATE_OK_EVT
    // UPDATE_FAILED_EVT
    NameChangeTransaction::verifyEvents();

    // Verify SimpleRemoveTransaction events by attempting to fetch them.
    // Currently SimpleRemoveTransaction does not define any events.
    // getEvent(TBD_EVENT);
}

void
SimpleRemoveTransaction::defineStates() {
    // Call superclass impl first.
    NameChangeTransaction::defineStates();

    // Define SimpleRemoveTransaction states.
    defineState(READY_ST, "READY_ST",
                std::bind(&SimpleRemoveTransaction::readyHandler, this));

    defineState(SELECTING_FWD_SERVER_ST, "SELECTING_FWD_SERVER_ST",
                std::bind(&SimpleRemoveTransaction::selectingFwdServerHandler,
                          this));

    defineState(SELECTING_REV_SERVER_ST, "SELECTING_REV_SERVER_ST",
                std::bind(&SimpleRemoveTransaction::selectingRevServerHandler,
                          this));

    defineState(REMOVING_FWD_RRS_ST, "REMOVING_FWD_RRS_ST",
                std::bind(&SimpleRemoveTransaction::removingFwdRRsHandler,
                          this));

    defineState(REMOVING_REV_PTRS_ST, "REMOVING_REV_PTRS_ST",
                std::bind(&SimpleRemoveTransaction::removingRevPtrsHandler,
                          this));

    defineState(PROCESS_TRANS_OK_ST, "PROCESS_TRANS_OK_ST",
                std::bind(&SimpleRemoveTransaction::processRemoveOkHandler,
                          this));

    defineState(PROCESS_TRANS_FAILED_ST, "PROCESS_TRANS_FAILED_ST",
                std::bind(&SimpleRemoveTransaction::processRemoveFailedHandler,
                          this));
}

void
SimpleRemoveTransaction::verifyStates() {
    // Call superclass implementation first to verify its states. These are
    // states common to all transactions, and they must be defined.
    // READY_ST
    // SELECTING_FWD_SERVER_ST
    // SELECTING_REV_SERVER_ST
    // PROCESS_TRANS_OK_ST
    // PROCESS_TRANS_FAILED_ST
    NameChangeTransaction::verifyStates();

    // Verify SimpleRemoveTransaction states by attempting to fetch them.
    getStateInternal(REMOVING_FWD_RRS_ST);
    getStateInternal(REMOVING_REV_PTRS_ST);
}

void
SimpleRemoveTransaction::readyHandler() {
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
        isc_throw(SimpleRemoveTransactionError,
                  "Wrong event for context: " << getContextStr());
    }
}

void
SimpleRemoveTransaction::selectingFwdServerHandler() {
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
        isc_throw(SimpleRemoveTransactionError,
                  "Wrong event for context: " << getContextStr());
    }

    // Select the next server from the list of forward servers.
    if (selectNextServer()) {
        // We have a server to try.
        transition(REMOVING_FWD_RRS_ST, SERVER_SELECTED_EVT);
    } else {
        // Server list is exhausted, so fail the transaction.
        transition(PROCESS_TRANS_FAILED_ST, NO_MORE_SERVERS_EVT);
    }
}

void
SimpleRemoveTransaction::removingFwdRRsHandler() {
    if (doOnEntry()) {
        // Clear the update attempts count on initial transition.
        clearUpdateAttempts();
    }

    switch(getNextEvent()) {
    case UPDATE_OK_EVT:
    case SERVER_SELECTED_EVT:
        try {
            clearDnsUpdateRequest();
            buildRemoveFwdRRsRequest();
        } catch (const std::exception& ex) {
            // While unlikely, the build might fail if we have invalid
            // data.  Should that be the case, we need to fail the
            // transaction.
            LOG_ERROR(d2_to_dns_logger,
                      DHCP_DDNS_FORWARD_REMOVE_RRS_BUILD_FAILURE)
                .arg(getRequestId())
                .arg(getNcr()->toText())
                .arg(ex.what());
            transition(PROCESS_TRANS_FAILED_ST, UPDATE_FAILED_EVT);
            break;
        }

        // Call sendUpdate() to initiate the async send. Note it also sets
        // next event to NOP_EVT.
        sendUpdate("Forward RR Remove");
        break;

    case IO_COMPLETED_EVT: {
        switch (getDnsUpdateStatus()) {
        case DNSClient::SUCCESS: {
            // We successfully received a response packet from the server.
            // The RCODE will be based on a value-dependent RRset search,
            // see RFC 2136 section 3.2.3/3.2.4.
            const dns::Rcode& rcode = getDnsUpdateResponse()->getRcode();
            if ((rcode == dns::Rcode::NOERROR()) ||
                (rcode == dns::Rcode::NXRRSET())) {
                // We were able to remove them or they were not there (
                // Rcode of NXRRSET means there are no matching RRsets).
                // In either case, we consider it success and mark it as done.
                setForwardChangeCompleted(true);

                // If request calls for reverse update then do that next,
                // otherwise we can process ok.
                if (getReverseDomain()) {
                    transition(SELECTING_REV_SERVER_ST, SELECT_SERVER_EVT);
                } else {
                    transition(PROCESS_TRANS_OK_ST, UPDATE_OK_EVT);
                }
            } else {
                // Any other value means cease.
                // If we get not authorized should try the next server in
                // the list? @todo  This needs some discussion perhaps.
                LOG_ERROR(d2_to_dns_logger, DHCP_DDNS_FORWARD_REMOVE_RRS_REJECTED)
                          .arg(getRequestId())
                          .arg(getCurrentServer()->toText())
                          .arg(getNcr()->getFqdn())
                          .arg(rcode.getCode());
                transition(PROCESS_TRANS_FAILED_ST, UPDATE_FAILED_EVT);
            }

            break;
        }

        case DNSClient::TIMEOUT:
            // No response from the server, log it and set up
            // to select the next server for a retry.
            LOG_ERROR(d2_to_dns_logger, DHCP_DDNS_FORWARD_REMOVE_RRS_TIMEOUT)
                      .arg(getRequestId())
                      .arg(getNcr()->getFqdn())
                      .arg(getCurrentServer()->toText());

            retryTransition(SELECTING_FWD_SERVER_ST);
            break;

        case DNSClient::OTHER:
            // We couldn't send to the current server, log it and set up
            // to select the next server for a retry.
            LOG_ERROR(d2_to_dns_logger, DHCP_DDNS_FORWARD_REMOVE_RRS_IO_ERROR)
                      .arg(getRequestId())
                      .arg(getNcr()->getFqdn())
                      .arg(getCurrentServer()->toText());

            retryTransition(SELECTING_FWD_SERVER_ST);
            break;

        case DNSClient::INVALID_RESPONSE:
            // A response was received but was corrupt. Retry it like an IO
            // error.
            LOG_ERROR(d2_to_dns_logger, DHCP_DDNS_FORWARD_REMOVE_RRS_RESP_CORRUPT)
                      .arg(getRequestId())
                      .arg(getCurrentServer()->toText())
                      .arg(getNcr()->getFqdn());

            retryTransition(SELECTING_FWD_SERVER_ST);
            break;

        default:
            // Any other value and we will fail this transaction, something
            // bigger is wrong.
            LOG_ERROR(d2_to_dns_logger,
                      DHCP_DDNS_FORWARD_REMOVE_RRS_BAD_DNSCLIENT_STATUS)
                      .arg(getRequestId())
                      .arg(getDnsUpdateStatus())
                      .arg(getNcr()->getFqdn())
                      .arg(getCurrentServer()->toText());

            transition(PROCESS_TRANS_FAILED_ST, UPDATE_FAILED_EVT);
            break;
        } // end switch on dns_status

        break;
    } // end case IO_COMPLETE_EVT

    default:
        // Event is invalid.
        isc_throw(SimpleRemoveTransactionError,
                  "Wrong event for context: " << getContextStr());
    }
}

void
SimpleRemoveTransaction::selectingRevServerHandler() {
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
        isc_throw(SimpleRemoveTransactionError,
                  "Wrong event for context: " << getContextStr());
    }

    // Select the next server from the list of forward servers.
    if (selectNextServer()) {
        // We have a server to try.
        transition(REMOVING_REV_PTRS_ST, SERVER_SELECTED_EVT);
    } else {
        // Server list is exhausted, so fail the transaction.
        transition(PROCESS_TRANS_FAILED_ST, NO_MORE_SERVERS_EVT);
    }
}


void
SimpleRemoveTransaction::removingRevPtrsHandler() {
    if (doOnEntry()) {
        // Clear the update attempts count on initial transition.
        clearUpdateAttempts();
    }

    switch(getNextEvent()) {
    case SERVER_SELECTED_EVT:
        try {
            clearDnsUpdateRequest();
            buildRemoveRevPtrsRequest();
        } catch (const std::exception& ex) {
            // While unlikely, the build might fail if we have invalid
            // data.  Should that be the case, we need to fail the
            // transaction.
            LOG_ERROR(d2_to_dns_logger, DHCP_DDNS_REVERSE_REMOVE_BUILD_FAILURE)
                .arg(getRequestId())
                .arg(getNcr()->toText())
                .arg(ex.what());
            transition(PROCESS_TRANS_FAILED_ST, UPDATE_FAILED_EVT);
            break;
        }

        // Call sendUpdate() to initiate the async send. Note it also sets
        // next event to NOP_EVT.
        sendUpdate("Reverse Remove");
        break;

    case IO_COMPLETED_EVT: {
        switch (getDnsUpdateStatus()) {
        case DNSClient::SUCCESS: {
            // We successfully received a response packet from the server.
            // The RCODE will be based on a value-dependent RRset search,
            // see RFC 2136 section 3.2.3/3.2.4.
            const dns::Rcode& rcode = getDnsUpdateResponse()->getRcode();
            if ((rcode == dns::Rcode::NOERROR()) ||
                (rcode == dns::Rcode::NXRRSET())) {
                // We were able to remove the reverse mapping or they were
                // not there (Rcode of NXRRSET means there are no matching
                // RRsets). In either case, mark it as done.
                setReverseChangeCompleted(true);
                transition(PROCESS_TRANS_OK_ST, UPDATE_OK_EVT);
            } else {
                // Per RFC4703 any other value means cease.
                // If we get not authorized should try the next server in
                // the list? @todo  This needs some discussion perhaps.
                LOG_ERROR(d2_to_dns_logger, DHCP_DDNS_REVERSE_REMOVE_REJECTED)
                          .arg(getRequestId())
                          .arg(getCurrentServer()->toText())
                          .arg(getNcr()->getFqdn())
                          .arg(rcode.getCode());
                transition(PROCESS_TRANS_FAILED_ST, UPDATE_FAILED_EVT);
            }

            break;
        }

        case DNSClient::TIMEOUT:
            // No response from the server, log it and set up
            // to select the next server for a retry.
            LOG_ERROR(d2_to_dns_logger, DHCP_DDNS_REVERSE_REMOVE_TIMEOUT)
                      .arg(getRequestId())
                      .arg(getNcr()->getFqdn())
                      .arg(getCurrentServer()->toText());

            // If we are out of retries on this server, we go back and start
            // all over on a new server.
            retryTransition(SELECTING_REV_SERVER_ST);
            break;


        case DNSClient::OTHER:
            // We couldn't send to the current server, log it and set up
            // to select the next server for a retry.
            LOG_ERROR(d2_to_dns_logger, DHCP_DDNS_REVERSE_REMOVE_IO_ERROR)
                      .arg(getRequestId())
                      .arg(getNcr()->getFqdn())
                      .arg(getCurrentServer()->toText());

            // If we are out of retries on this server, we go back and start
            // all over on a new server.
            retryTransition(SELECTING_REV_SERVER_ST);
            break;

        case DNSClient::INVALID_RESPONSE:
            // A response was received but was corrupt. Retry it like an IO
            // error.
            LOG_ERROR(d2_to_dns_logger, DHCP_DDNS_REVERSE_REMOVE_RESP_CORRUPT)
                      .arg(getRequestId())
                      .arg(getCurrentServer()->toText())
                      .arg(getNcr()->getFqdn());

            // If we are out of retries on this server, we go back and start
            // all over on a new server.
            retryTransition(SELECTING_REV_SERVER_ST);
            break;

        default:
            // Any other value and we will fail this transaction, something
            // bigger is wrong.
            LOG_ERROR(d2_to_dns_logger,
                      DHCP_DDNS_REVERSE_REMOVE_BAD_DNSCLIENT_STATUS)
                      .arg(getRequestId())
                      .arg(getDnsUpdateStatus())
                      .arg(getNcr()->getFqdn())
                      .arg(getCurrentServer()->toText());

            transition(PROCESS_TRANS_FAILED_ST, UPDATE_FAILED_EVT);
            break;
        } // end switch on dns_status

        break;
    } // end case IO_COMPLETE_EVT

    default:
        // Event is invalid.
        isc_throw(SimpleRemoveTransactionError,
                  "Wrong event for context: " << getContextStr());
    }
}


void
SimpleRemoveTransaction::processRemoveOkHandler() {
    switch(getNextEvent()) {
    case UPDATE_OK_EVT:
        LOG_INFO(d2_to_dns_logger, DHCP_DDNS_REMOVE_SUCCEEDED)
                .arg(getRequestId())
                .arg(getNcr()->toText());
        setNcrStatus(dhcp_ddns::ST_COMPLETED);
        endModel();
        break;
    default:
        // Event is invalid.
        isc_throw(SimpleRemoveTransactionError,
                  "Wrong event for context: " << getContextStr());
    }
}

void
SimpleRemoveTransaction::processRemoveFailedHandler() {
    switch(getNextEvent()) {
    case UPDATE_FAILED_EVT:
    case NO_MORE_SERVERS_EVT:
    case SERVER_IO_ERROR_EVT:
        setNcrStatus(dhcp_ddns::ST_FAILED);
        LOG_ERROR(d2_to_dns_logger, DHCP_DDNS_REMOVE_FAILED)
                  .arg(getRequestId())
                  .arg(transactionOutcomeString());
        endModel();
        break;
    default:
        // Event is invalid.
        isc_throw(SimpleRemoveTransactionError,
                  "Wrong event for context: " << getContextStr());
    }
}

void
SimpleRemoveTransaction::buildRemoveFwdRRsRequest() {
    // Construct an empty request.
    D2UpdateMessagePtr request = prepNewRequest(getForwardDomain());

    // There are no pre-requisites.

    // Build the Update Section
    // Construct dns::Name from NCR fqdn.
    dns::Name fqdn(dns::Name(getNcr()->getFqdn()));

    // Build the Update Section.

    // Create the FQDN/IP 'delete' RR and add it to update section.
    dns::RRsetPtr update(new dns::RRset(fqdn, dns::RRClass::ANY(),
                         getAddressRRType(), dns::RRTTL(0)));

    request->addRRset(D2UpdateMessage::SECTION_UPDATE, update);

    // Create the DHCID 'delete' RR and add it to the update section.
    update.reset(new dns::RRset(fqdn, dns::RRClass::ANY(),
                                dns::RRType::DHCID(), dns::RRTTL(0)));
    request->addRRset(D2UpdateMessage::SECTION_UPDATE, update);

    // Set the transaction's update request to the new request.
    setDnsUpdateRequest(request);
}

void
SimpleRemoveTransaction::buildRemoveRevPtrsRequest() {
    // Construct an empty request.
    D2UpdateMessagePtr request = prepNewRequest(getReverseDomain());

    // Create the reverse IP address "FQDN".
    std::string rev_addr = D2CfgMgr::reverseIpAddress(getNcr()->getIpAddress());
    dns::Name rev_ip(rev_addr);

    // There are no pre-requisites.

    // Build the Update section.

    // Create the FQDN/IP PTR 'delete' RR for this IP and add it to
    // the update section.
    dns::RRsetPtr update(new dns::RRset(rev_ip, dns::RRClass::ANY(),
                         dns::RRType::PTR(), dns::RRTTL(0)));
    request->addRRset(D2UpdateMessage::SECTION_UPDATE, update);

    // Create the DHCID 'delete' RR and add it to the update section.
    update.reset(new dns::RRset(rev_ip, dns::RRClass::ANY(),
                                dns::RRType::DHCID(), dns::RRTTL(0)));
    request->addRRset(D2UpdateMessage::SECTION_UPDATE, update);

    // Set the transaction's update request to the new request.
    setDnsUpdateRequest(request);
}

} // namespace isc::d2
} // namespace isc
