// Copyright (C) 2013-2015 Internet Systems Consortium, Inc. ("ISC")
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

#include <config.h>

#include <d2/d2_log.h>
#include <d2/d2_cfg_mgr.h>
#include <d2/nc_remove.h>

#include <boost/function.hpp>
#include <boost/bind.hpp>

namespace isc {
namespace d2 {


// NameRemoveTransaction states
const int NameRemoveTransaction::REMOVING_FWD_ADDRS_ST;
const int NameRemoveTransaction::REMOVING_FWD_RRS_ST;
const int NameRemoveTransaction::REMOVING_REV_PTRS_ST;

// NameRemoveTransaction events
// Currently NameRemoveTransaction does not define any events.

NameRemoveTransaction::
NameRemoveTransaction(asiolink::IOServicePtr& io_service,
                   dhcp_ddns::NameChangeRequestPtr& ncr,
                   DdnsDomainPtr& forward_domain,
                   DdnsDomainPtr& reverse_domain,
                   D2CfgMgrPtr& cfg_mgr)
    : NameChangeTransaction(io_service, ncr, forward_domain, reverse_domain,
                            cfg_mgr) {
    if (ncr->getChangeType() != isc::dhcp_ddns::CHG_REMOVE) {
        isc_throw (NameRemoveTransactionError,
                   "NameRemoveTransaction, request type must be CHG_REMOVE");
    }
}

NameRemoveTransaction::~NameRemoveTransaction(){
}

void
NameRemoveTransaction::defineEvents() {
    // Call superclass impl first.
    NameChangeTransaction::defineEvents();

    // Define NameRemoveTransaction events.
    // Currently NameRemoveTransaction does not define any events.
    // defineEvent(TBD_EVENT, "TBD_EVT");
}

void
NameRemoveTransaction::verifyEvents() {
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

    // Verify NameRemoveTransaction events by attempting to fetch them.
    // Currently NameRemoveTransaction does not define any events.
    // getEvent(TBD_EVENT);
}

void
NameRemoveTransaction::defineStates() {
    // Call superclass impl first.
    NameChangeTransaction::defineStates();

    // Define NameRemoveTransaction states.
    defineState(READY_ST, "READY_ST",
                boost::bind(&NameRemoveTransaction::readyHandler, this));

    defineState(SELECTING_FWD_SERVER_ST, "SELECTING_FWD_SERVER_ST",
                boost::bind(&NameRemoveTransaction::selectingFwdServerHandler,
                            this));

    defineState(SELECTING_REV_SERVER_ST, "SELECTING_REV_SERVER_ST",
                boost::bind(&NameRemoveTransaction::selectingRevServerHandler,
                            this));

    defineState(REMOVING_FWD_ADDRS_ST, "REMOVING_FWD_ADDRS_ST",
                boost::bind(&NameRemoveTransaction::removingFwdAddrsHandler,
                            this));

    defineState(REMOVING_FWD_RRS_ST, "REMOVING_FWD_RRS_ST",
                boost::bind(&NameRemoveTransaction::removingFwdRRsHandler,
                            this));

    defineState(REMOVING_REV_PTRS_ST, "REMOVING_REV_PTRS_ST",
                boost::bind(&NameRemoveTransaction::removingRevPtrsHandler,
                            this));

    defineState(PROCESS_TRANS_OK_ST, "PROCESS_TRANS_OK_ST",
                boost::bind(&NameRemoveTransaction::processRemoveOkHandler,
                            this));

    defineState(PROCESS_TRANS_FAILED_ST, "PROCESS_TRANS_FAILED_ST",
                boost::bind(&NameRemoveTransaction::processRemoveFailedHandler,
                            this));
}

void
NameRemoveTransaction::verifyStates() {
    // Call superclass implementation first to verify its states. These are
    // states common to all transactions, and they must be defined.
    // READY_ST
    // SELECTING_FWD_SERVER_ST
    // SELECTING_REV_SERVER_ST
    // PROCESS_TRANS_OK_ST
    // PROCESS_TRANS_FAILED_ST
    NameChangeTransaction::verifyStates();

    // Verify NameRemoveTransaction states by attempting to fetch them.
    getState(REMOVING_FWD_ADDRS_ST);
    getState(REMOVING_FWD_RRS_ST);
    getState(REMOVING_REV_PTRS_ST);
}

void
NameRemoveTransaction::readyHandler() {
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
        isc_throw(NameRemoveTransactionError,
                  "Wrong event for context: " << getContextStr());
    }
}

void
NameRemoveTransaction::selectingFwdServerHandler() {
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
        isc_throw(NameRemoveTransactionError,
                  "Wrong event for context: " << getContextStr());
    }

    // Select the next server from the list of forward servers.
    if (selectNextServer()) {
        // We have a server to try.
        transition(REMOVING_FWD_ADDRS_ST, SERVER_SELECTED_EVT);
    }
    else {
        // Server list is exhausted, so fail the transaction.
        transition(PROCESS_TRANS_FAILED_ST, NO_MORE_SERVERS_EVT);
    }
}

void
NameRemoveTransaction::removingFwdAddrsHandler() {
    if (doOnEntry()) {
        // Clear the request on initial transition. This allows us to reuse
        // the request on retries if necessary.
        clearDnsUpdateRequest();
    }

    switch(getNextEvent()) {
    case SERVER_SELECTED_EVT:
        if (!getDnsUpdateRequest()) {
            // Request hasn't been constructed yet, so build it.
            try {
                buildRemoveFwdAddressRequest();
            } catch (const std::exception& ex) {
                // While unlikely, the build might fail if we have invalid
                // data.  Should that be the case, we need to fail the
                // transaction.
                LOG_ERROR(d2_to_dns_logger,
                          DHCP_DDNS_FORWARD_REMOVE_ADDRS_BUILD_FAILURE)
                          .arg(getRequestId())
                          .arg(getNcr()->toText())
                          .arg(ex.what());
                transition(PROCESS_TRANS_FAILED_ST, UPDATE_FAILED_EVT);
                break;
            }
        }

        // Call sendUpdate() to initiate the async send. Note it also sets
        // next event to NOP_EVT.
        sendUpdate("Forward A/AAAA Remove");
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
                // We were able to remove it or it wasn't there, now we
                // need to remove any other RRs for this FQDN.
                transition(REMOVING_FWD_RRS_ST, UPDATE_OK_EVT);
            } else {
                // Per RFC4703 any other value means cease.
                // If we get not authorized should we try the next server in
                // the list? @todo  This needs some discussion perhaps.
                LOG_ERROR(d2_to_dns_logger, DHCP_DDNS_FORWARD_REMOVE_ADDRS_REJECTED)
                          .arg(getRequestId())
                          .arg(getCurrentServer()->toText())
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
            LOG_ERROR(d2_to_dns_logger, DHCP_DDNS_FORWARD_REMOVE_ADDRS_IO_ERROR)
                      .arg(getRequestId())
                      .arg(getNcr()->getFqdn())
                      .arg(getCurrentServer()->toText());

            retryTransition(SELECTING_FWD_SERVER_ST);
            break;

        case DNSClient::INVALID_RESPONSE:
            // A response was received but was corrupt. Retry it like an IO
            // error.
            LOG_ERROR(d2_to_dns_logger, DHCP_DDNS_FORWARD_REMOVE_ADDRS_RESP_CORRUPT)
                      .arg(getRequestId())
                      .arg(getCurrentServer()->toText())
                      .arg(getNcr()->getFqdn());

            retryTransition(SELECTING_FWD_SERVER_ST);
            break;

        default:
            // Any other value and we will fail this transaction, something
            // bigger is wrong.
            LOG_ERROR(d2_to_dns_logger,
                      DHCP_DDNS_FORWARD_REMOVE_ADDRS_BAD_DNSCLIENT_STATUS)
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
        isc_throw(NameRemoveTransactionError,
                  "Wrong event for context: " << getContextStr());
    }
}


void
NameRemoveTransaction::removingFwdRRsHandler() {
    if (doOnEntry()) {
        // Clear the request on initial transition. This allows us to reuse
        // the request on retries if necessary.
        clearDnsUpdateRequest();
    }

    switch(getNextEvent()) {
    case UPDATE_OK_EVT:
    case SERVER_SELECTED_EVT:
        if (!getDnsUpdateRequest()) {
            // Request hasn't been constructed yet, so build it.
            try {
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
                // Per RFC4703 any other value means cease.
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
        case DNSClient::OTHER:
            // We couldn't send to the current server, log it and set up
            // to select the next server for a retry.
            // @note For now we treat OTHER as an IO error like TIMEOUT. It
            // is not entirely clear if this is accurate.
            LOG_ERROR(d2_to_dns_logger, DHCP_DDNS_FORWARD_REMOVE_RRS_IO_ERROR)
                      .arg(getRequestId())
                      .arg(getNcr()->getFqdn())
                      .arg(getCurrentServer()->toText());

            // @note If we exhaust the IO retries for the current server
            // due to IO failures, we will abort the remaining updates.
            // The rational is that we are only in this state, if the remove
            // of the forward address RR succeeded (removingFwdAddrsHandler)
            // on the current server. Therefore  we should not attempt another
            // removal on a different server.  This is perhaps a point
            // for discussion.
            // @todo Should we go ahead with the reverse remove?
            retryTransition(PROCESS_TRANS_FAILED_ST);
            break;

        case DNSClient::INVALID_RESPONSE:
            // A response was received but was corrupt. Retry it like an IO
            // error.
            LOG_ERROR(d2_to_dns_logger, DHCP_DDNS_FORWARD_REMOVE_RRS_RESP_CORRUPT)
                      .arg(getRequestId())
                      .arg(getCurrentServer()->toText())
                      .arg(getNcr()->getFqdn());

            // If we are out of retries on this server abandon the transaction.
            // (Same logic as the case for TIMEOUT above).
            retryTransition(PROCESS_TRANS_FAILED_ST);
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
        isc_throw(NameRemoveTransactionError,
                  "Wrong event for context: " << getContextStr());
    }
}


void
NameRemoveTransaction::selectingRevServerHandler() {
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
        isc_throw(NameRemoveTransactionError,
                  "Wrong event for context: " << getContextStr());
    }

    // Select the next server from the list of forward servers.
    if (selectNextServer()) {
        // We have a server to try.
        transition(REMOVING_REV_PTRS_ST, SERVER_SELECTED_EVT);
    }
    else {
        // Server list is exhausted, so fail the transaction.
        transition(PROCESS_TRANS_FAILED_ST, NO_MORE_SERVERS_EVT);
    }
}


void
NameRemoveTransaction::removingRevPtrsHandler() {
    if (doOnEntry()) {
        // Clear the request on initial transition. This allows us to reuse
        // the request on retries if necessary.
        clearDnsUpdateRequest();
    }

    switch(getNextEvent()) {
    case SERVER_SELECTED_EVT:
        if (!getDnsUpdateRequest()) {
            // Request hasn't been constructed yet, so build it.
            try {
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
        case DNSClient::OTHER:
            // We couldn't send to the current server, log it and set up
            // to select the next server for a retry.
            // @note For now we treat OTHER as an IO error like TIMEOUT. It
            // is not entirely clear if this is accurate.
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
        isc_throw(NameRemoveTransactionError,
                  "Wrong event for context: " << getContextStr());
    }
}


void
NameRemoveTransaction::processRemoveOkHandler() {
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
        isc_throw(NameRemoveTransactionError,
                  "Wrong event for context: " << getContextStr());
    }
}

void
NameRemoveTransaction::processRemoveFailedHandler() {
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
        isc_throw(NameRemoveTransactionError,
                  "Wrong event for context: " << getContextStr());
    }
}

void
NameRemoveTransaction::buildRemoveFwdAddressRequest() {
    // Construct an empty request.
    D2UpdateMessagePtr request = prepNewRequest(getForwardDomain());

    // Content on this request is based on RFC 4703, section 5.5, paragraph 4.
    // Construct dns::Name from NCR fqdn.
    dns::Name fqdn(dns::Name(getNcr()->getFqdn()));
    // First build the Prerequisite Section

    // Create an DHCID matches prerequisite RR and add it to the
    // pre-requisite section
    // Based on RFC 2136, section 2.4.2.
    dns::RRsetPtr prereq(new dns::RRset(fqdn, dns::RRClass::IN(),
                                        dns::RRType::DHCID(), dns::RRTTL(0)));
    addDhcidRdata(prereq);
    request->addRRset(D2UpdateMessage::SECTION_PREREQUISITE, prereq);

    // Next build the Update Section

    // Create the FQDN/IP 'delete' RR and add it to the update section.
    // Add the RR to update section.
    // Based on 2136 section 2.5.4
    dns::RRsetPtr update(new dns::RRset(fqdn, dns::RRClass::NONE(),
                         getAddressRRType(), dns::RRTTL(0)));
    addLeaseAddressRdata(update);
    request->addRRset(D2UpdateMessage::SECTION_UPDATE, update);

    // Set the transaction's update request to the new request.
    setDnsUpdateRequest(request);
}

void
NameRemoveTransaction::buildRemoveFwdRRsRequest() {
    // Construct an empty request.
    D2UpdateMessagePtr request = prepNewRequest(getForwardDomain());

    // Construct dns::Name from NCR fqdn.
    dns::Name fqdn(dns::Name(getNcr()->getFqdn()));

    // Content on this request is based on RFC 4703, section 5.5, paragraph 5.
    // First build the Prerequisite Section.

    // Now create an DHCID matches prerequisite RR.
    // Set the RR's RData to DHCID.
    // Add it to the pre-requisite section.
    // Based on RFC 2136, section 2.4.2.
    dns::RRsetPtr prereq(new dns::RRset(fqdn, dns::RRClass::IN(),
                         dns::RRType::DHCID(), dns::RRTTL(0)));
    addDhcidRdata(prereq);
    request->addRRset(D2UpdateMessage::SECTION_PREREQUISITE, prereq);

    // Create an assertion that there are no A RRs for the FQDN.
    // Add it to the pre-reqs.
    // Based on RFC 2136, section 2.4.3.
    prereq.reset(new dns::RRset(fqdn, dns::RRClass::NONE(),
                                dns::RRType::A(), dns::RRTTL(0)));
    request->addRRset(D2UpdateMessage::SECTION_PREREQUISITE, prereq);

    // Create an assertion that there are no A RRs for the FQDN.
    // Add it to the pre-reqs.
    // Based on RFC 2136, section 2.4.3.
    prereq.reset(new dns::RRset(fqdn, dns::RRClass::NONE(),
                                dns::RRType::AAAA(), dns::RRTTL(0)));
    request->addRRset(D2UpdateMessage::SECTION_PREREQUISITE, prereq);

    // Next build the Update Section.

    // Create the 'delete' of all RRs for FQDN.
    // Set the message RData to lease address.
    // Add the RR to update section.
    // Based on RFC 2136, section 2.5.3.
    dns::RRsetPtr update(new dns::RRset(fqdn, dns::RRClass::ANY(),
                         dns::RRType::ANY(), dns::RRTTL(0)));
    request->addRRset(D2UpdateMessage::SECTION_UPDATE, update);

    // Set the transaction's update request to the new request.
    setDnsUpdateRequest(request);
}

void
NameRemoveTransaction::buildRemoveRevPtrsRequest() {
    // Construct an empty request.
    D2UpdateMessagePtr request = prepNewRequest(getReverseDomain());

    // Create the reverse IP address "FQDN".
    std::string rev_addr = D2CfgMgr::reverseIpAddress(getNcr()->getIpAddress());
    dns::Name rev_ip(rev_addr);

    // Content on this request is based on RFC 4703, section 5.5, paragraph 2.
    // First build the Prerequisite Section.
    // (Note that per RFC 4703, section 5.4, there is no need to validate
    // DHCID RR for PTR entries.)

    // Create an assertion that the PTRDNAME in the PTR record matches the
    // client's FQDN for the address that was released.
    // Based on RFC 2136, section 3.2.3
    dns::RRsetPtr prereq(new dns::RRset(rev_ip, dns::RRClass::IN(),
                                        dns::RRType::PTR(), dns::RRTTL(0)));
    addPtrRdata(prereq);
    request->addRRset(D2UpdateMessage::SECTION_PREREQUISITE, prereq);

    // Now, build the Update section.

    // Create a delete of any RRs for the FQDN and add it to update section.
    // Based on RFC 2136, section 3.4.2.3
    dns::RRsetPtr update(new dns::RRset(rev_ip, dns::RRClass::ANY(),
                         dns::RRType::ANY(), dns::RRTTL(0)));
    request->addRRset(D2UpdateMessage::SECTION_UPDATE, update);

    // Set the transaction's update request to the new request.
    setDnsUpdateRequest(request);
}

} // namespace isc::d2
} // namespace isc
