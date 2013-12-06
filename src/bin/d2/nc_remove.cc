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
// @todo none so far

NameRemoveTransaction::
NameRemoveTransaction(IOServicePtr& io_service,
                   dhcp_ddns::NameChangeRequestPtr& ncr,
                   DdnsDomainPtr& forward_domain,
                   DdnsDomainPtr& reverse_domain)
    : NameChangeTransaction(io_service, ncr, forward_domain, reverse_domain) {
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
    // @todo none so far
    // defineEvent(TBD_EVENT, "TBD_EVT");
}

void
NameRemoveTransaction::verifyEvents() {
    // Call superclass impl first.
    NameChangeTransaction::verifyEvents();

    // Verify NameRemoveTransaction events.
    // @todo none so far
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
    // Call superclass impl first.
    NameChangeTransaction::verifyStates();

    // Verify NameRemoveTransaction states.
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
                LOG_ERROR(dctl_logger, 
                          DHCP_DDNS_FORWARD_REMOVE_ADDRS_BUILD_FAILURE)
                          .arg(getNcr()->toText())
                          .arg(ex.what());
                transition(PROCESS_TRANS_FAILED_ST, UPDATE_FAILED_EVT);
                break;
            }
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
            if ((rcode == dns::Rcode::NOERROR()) ||
                (rcode == dns::Rcode::NXDOMAIN())) {
                // We were able to remove it or it wasn't there, now we
                // need to remove any other RRs for this FQDN.
                transition(REMOVING_FWD_RRS_ST, UPDATE_OK_EVT);
            } else {
                // Per RFC4703 any other value means cease.
                // If we get not authorized should we try the next server in
                // the list? @todo  This needs some discussion perhaps.
                LOG_ERROR(dctl_logger, DHCP_DDNS_FORWARD_REMOVE_ADDRS_REJECTED)
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
            LOG_ERROR(dctl_logger, DHCP_DDNS_FORWARD_REMOVE_ADDRS_IO_ERROR)
                      .arg(getNcr()->getFqdn())
                      .arg(getCurrentServer()->getIpAddress());

            retryTransition(SELECTING_FWD_SERVER_ST);
            break;

        case DNSClient::INVALID_RESPONSE:
            // A response was received but was corrupt. Retry it like an IO
            // error.
            LOG_ERROR(dctl_logger, DHCP_DDNS_FORWARD_REMOVE_ADDRS_RESP_CORRUPT)
                      .arg(getCurrentServer()->getIpAddress())
                      .arg(getNcr()->getFqdn());

            retryTransition(SELECTING_FWD_SERVER_ST);
            break;

        default:
            // Any other value and we will fail this transaction, something
            // bigger is wrong.
            LOG_ERROR(dctl_logger, 
                      DHCP_DDNS_FORWARD_REMOVE_ADDRS_BAD_DNSCLIENT_STATUS)
                      .arg(getDnsUpdateStatus())
                      .arg(getNcr()->getFqdn())
                      .arg(getCurrentServer()->getIpAddress());

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
                LOG_ERROR(dctl_logger, 
                          DHCP_DDNS_FORWARD_REMOVE_RRS_BUILD_FAILURE)
                          .arg(getNcr()->toText())
                          .arg(ex.what());
                transition(PROCESS_TRANS_FAILED_ST, UPDATE_FAILED_EVT);
                break;
            }
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
            // @todo Not sure if NXDOMAIN is ok here, but I think so.
            // A Rcode of NXDOMAIN would mean there are no RRs for the FQDN,
            // which is fine.  We were asked to delete them, they are not there
            // so all is well. 
            if ((rcode == dns::Rcode::NOERROR()) || 
                (rcode == dns::Rcode::NXDOMAIN())) {
                // We were able to remove the forward mapping. Mark it as done.
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
                LOG_ERROR(dctl_logger, DHCP_DDNS_FORWARD_REMOVE_RRS_REJECTED)
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
            LOG_ERROR(dctl_logger, DHCP_DDNS_FORWARD_REMOVE_RRS_IO_ERROR)
                      .arg(getNcr()->getFqdn())
                      .arg(getCurrentServer()->getIpAddress());

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
            LOG_ERROR(dctl_logger, DHCP_DDNS_FORWARD_REMOVE_RRS_RESP_CORRUPT)
                      .arg(getCurrentServer()->getIpAddress())
                      .arg(getNcr()->getFqdn());

            // If we are out of retries on this server abandon the transaction.
            // (Same logic as the case for TIMEOUT above).
            retryTransition(PROCESS_TRANS_FAILED_ST);
            break;

        default:
            // Any other value and we will fail this transaction, something
            // bigger is wrong.
            LOG_ERROR(dctl_logger,
                      DHCP_DDNS_FORWARD_REMOVE_RRS_BAD_DNSCLIENT_STATUS)
                      .arg(getDnsUpdateStatus())
                      .arg(getNcr()->getFqdn())
                      .arg(getCurrentServer()->getIpAddress());

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
                LOG_ERROR(dctl_logger, DHCP_DDNS_REVERSE_REMOVE_BUILD_FAILURE)
                          .arg(getNcr()->toText())
                          .arg(ex.what());
                transition(PROCESS_TRANS_FAILED_ST, UPDATE_FAILED_EVT);
                break;
            }
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
            if ((rcode == dns::Rcode::NOERROR()) ||
                (rcode == dns::Rcode::NXDOMAIN())) {
                // We were able to update the reverse mapping. Mark it as done.
                // @todo For now we are also treating NXDOMAIN as success.
                setReverseChangeCompleted(true);
                transition(PROCESS_TRANS_OK_ST, UPDATE_OK_EVT);
            } else {
                // Per RFC4703 any other value means cease.
                // If we get not authorized should try the next server in
                // the list? @todo  This needs some discussion perhaps.
                LOG_ERROR(dctl_logger, DHCP_DDNS_REVERSE_REMOVE_REJECTED)
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
            LOG_ERROR(dctl_logger, DHCP_DDNS_REVERSE_REMOVE_IO_ERROR)
                      .arg(getNcr()->getFqdn())
                      .arg(getCurrentServer()->getIpAddress());

            // If we are out of retries on this server, we go back and start
            // all over on a new server.
            retryTransition(SELECTING_REV_SERVER_ST);
            break;

        case DNSClient::INVALID_RESPONSE:
            // A response was received but was corrupt. Retry it like an IO
            // error.
            LOG_ERROR(dctl_logger, DHCP_DDNS_REVERSE_REMOVE_RESP_CORRUPT)
                      .arg(getCurrentServer()->getIpAddress())
                      .arg(getNcr()->getFqdn());

            // If we are out of retries on this server, we go back and start
            // all over on a new server.
            retryTransition(SELECTING_REV_SERVER_ST);
            break;

        default:
            // Any other value and we will fail this transaction, something
            // bigger is wrong.
            LOG_ERROR(dctl_logger,
                      DHCP_DDNS_REVERSE_REMOVE_BAD_DNSCLIENT_STATUS)
                      .arg(getDnsUpdateStatus())
                      .arg(getNcr()->getFqdn())
                      .arg(getCurrentServer()->getIpAddress());

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
        LOG_DEBUG(dctl_logger, DBGLVL_TRACE_DETAIL, DHCP_DDNS_REMOVE_SUCCEEDED)
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
        LOG_ERROR(dctl_logger, DHCP_DDNS_REMOVE_FAILED).arg(getNcr()->toText());
        setNcrStatus(dhcp_ddns::ST_FAILED);
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

#if 0
    // Construct dns::Name from NCR fqdn.
    dns::Name fqdn(dns::Name(getNcr()->getFqdn()));

    // First build the Prerequisite Section.

    // Create 'FQDN Is Not In Use' prerequisite (RFC 2136, section 2.4.5)
    // Add the RR to prerequisite section.
    dns::RRsetPtr prereq(new dns::RRset(fqdn, dns::RRClass::NONE(),
                             dns::RRType::ANY(), dns::RRTTL(0)));
    request->addRRset(D2UpdateMessage::SECTION_PREREQUISITE, prereq);

    // Next build the Update Section.

    // Create the FQDN/IP 'add' RR (RFC 2136, section 2.5.1)
    // Set the message RData to lease address.
    // Add the RR to update section.
    dns::RRsetPtr update(new dns::RRset(fqdn, dns::RRClass::IN(),
                         getAddressRRType(), dns::RRTTL(0)));

    addLeaseAddressRdata(update);
    request->addRRset(D2UpdateMessage::SECTION_UPDATE, update);
    // Now create the FQDN/DHCID 'add' RR per RFC 4701)
    // Set the message RData to DHCID.
    // Add the RR to update section.
    update.reset(new dns::RRset(fqdn, dns::RRClass::IN(),
                                dns::RRType::DHCID(), dns::RRTTL(0)));
    addDhcidRdata(update);
    request->addRRset(D2UpdateMessage::SECTION_UPDATE, update);
#endif

    // Set the transaction's update request to the new request.
    setDnsUpdateRequest(request);
}

void
NameRemoveTransaction::buildRemoveFwdRRsRequest() {
    // Construct an empty request.
    D2UpdateMessagePtr request = prepNewRequest(getForwardDomain());

#if 0
    // Construct dns::Name from NCR fqdn.
    dns::Name fqdn(dns::Name(getNcr()->getFqdn()));

    // First build the Prerequisite Section.

    // Create an 'FQDN Is In Use' prerequisite (RFC 2136, section 2.4.4)
    // Add it to the pre-requisite section.
    dns::RRsetPtr prereq(new dns::RRset(fqdn, dns::RRClass::ANY(),
                               dns::RRType::ANY(), dns::RRTTL(0)));
    request->addRRset(D2UpdateMessage::SECTION_PREREQUISITE, prereq);

    // Now create an DHCID matches prerequisite RR.
    // Set the RR's RData to DHCID.
    // Add it to the pre-requisite section.
    prereq.reset(new dns::RRset(fqdn, dns::RRClass::IN(),
                 dns::RRType::DHCID(), dns::RRTTL(0)));
    addDhcidRdata(prereq);
    request->addRRset(D2UpdateMessage::SECTION_PREREQUISITE, prereq);

    // Next build the Update Section.

    // Create the FQDN/IP 'delete' RR (RFC 2136, section 2.5.1)
    // Set the message RData to lease address.
    // Add the RR to update section.
    dns::RRsetPtr update(new dns::RRset(fqdn, dns::RRClass::ANY(),
                         getAddressRRType(), dns::RRTTL(0)));
    request->addRRset(D2UpdateMessage::SECTION_UPDATE, update);

    // Create the FQDN/IP 'add' RR (RFC 2136, section 2.5.1)
    // Set the message RData to lease address.
    // Add the RR to update section.
    update.reset(new dns::RRset(fqdn, dns::RRClass::IN(),
                                getAddressRRType(), dns::RRTTL(0)));
    addLeaseAddressRdata(update);
    request->addRRset(D2UpdateMessage::SECTION_UPDATE, update);
#endif

    // Set the transaction's update request to the new request.
    setDnsUpdateRequest(request);
}

void
NameRemoveTransaction::buildRemoveRevPtrsRequest() {
    // Construct an empty request.
    D2UpdateMessagePtr request = prepNewRequest(getReverseDomain());

#if 0
    // Create the reverse IP address "FQDN".
    std::string rev_addr = D2CfgMgr::reverseIpAddress(getNcr()->getIpAddress());
    dns::Name rev_ip(rev_addr);

    // Reverse replacement has no prerequisites so straight on to
    // building the Update section.

    // Create the PTR 'delete' RR and add it to update section.
    dns::RRsetPtr update(new dns::RRset(rev_ip, dns::RRClass::ANY(),
                         dns::RRType::PTR(), dns::RRTTL(0)));
    request->addRRset(D2UpdateMessage::SECTION_UPDATE, update);

    // Create the DHCID 'delete' RR and add it to the update section.
    update.reset(new dns::RRset(rev_ip, dns::RRClass::ANY(),
                                dns::RRType::DHCID(), dns::RRTTL(0)));
    request->addRRset(D2UpdateMessage::SECTION_UPDATE, update);

    // Create the FQDN/IP PTR 'add' RR, add the FQDN as the PTR Rdata
    // then add it to update section.
    update.reset(new dns::RRset(rev_ip, dns::RRClass::IN(),
                                dns::RRType::PTR(), dns::RRTTL(0)));
    addPtrRdata(update);
    request->addRRset(D2UpdateMessage::SECTION_UPDATE, update);

    // Create the FQDN/IP PTR 'add' RR, add the DHCID Rdata
    // then add it to update section.
    update.reset(new dns::RRset(rev_ip, dns::RRClass::IN(),
                                dns::RRType::DHCID(), dns::RRTTL(0)));
    addDhcidRdata(update);
    request->addRRset(D2UpdateMessage::SECTION_UPDATE, update);
#endif

    // Set the transaction's update request to the new request.
    setDnsUpdateRequest(request);
}

} // namespace isc::d2
} // namespace isc
