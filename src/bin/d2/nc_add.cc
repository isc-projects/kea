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
#include <d2/nc_add.h>

#include <boost/function.hpp>
#include <boost/bind.hpp>

#include <util/buffer.h>
#include <dns/rdataclass.h>

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
NameAddTransaction(asiolink::IOServicePtr& io_service,
                   dhcp_ddns::NameChangeRequestPtr& ncr,
                   DdnsDomainPtr& forward_domain,
                   DdnsDomainPtr& reverse_domain,
                   D2CfgMgrPtr& cfg_mgr)
    : NameChangeTransaction(io_service, ncr, forward_domain, reverse_domain,
                            cfg_mgr) {
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

    // Define NameAddTransaction events.
    defineEvent(FQDN_IN_USE_EVT, "FQDN_IN_USE_EVT");
    defineEvent(FQDN_NOT_IN_USE_EVT, "FQDN_NOT_IN_USE_EVT");
}

void
NameAddTransaction::verifyEvents() {
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

    // Verify NameAddTransaction events by attempting to fetch them.
    getEvent(FQDN_IN_USE_EVT);
    getEvent(FQDN_NOT_IN_USE_EVT);
}

void
NameAddTransaction::defineStates() {
    // Call superclass impl first.
    NameChangeTransaction::defineStates();

    // Define NameAddTransaction states.
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
    // Call superclass implementation first to verify its states. These are
    // states common to all transactions, and they must be defined.
    // READY_ST
    // SELECTING_FWD_SERVER_ST
    // SELECTING_REV_SERVER_ST
    // PROCESS_TRANS_OK_ST
    // PROCESS_TRANS_FAILED_ST
    NameChangeTransaction::verifyStates();

    // Verify NameAddTransaction states by attempting to fetch them.
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
            try {
                buildAddFwdAddressRequest();
            } catch (const std::exception& ex) {
                // While unlikely, the build might fail if we have invalid
                // data.  Should that be the case, we need to fail the
                // transaction.
                LOG_ERROR(d2_to_dns_logger, DHCP_DDNS_FORWARD_ADD_BUILD_FAILURE)
                          .arg(getRequestId())
                          .arg(getNcr()->toText())
                          .arg(ex.what());
                transition(PROCESS_TRANS_FAILED_ST, UPDATE_FAILED_EVT);
                break;
            }
        }

        // Call sendUpdate() to initiate the async send. Note it also sets
        // next event to NOP_EVT.
        sendUpdate("Foward Add");
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
                LOG_ERROR(d2_to_dns_logger, DHCP_DDNS_FORWARD_ADD_REJECTED)
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
            LOG_ERROR(d2_to_dns_logger, DHCP_DDNS_FORWARD_ADD_IO_ERROR)
                      .arg(getRequestId())
                      .arg(getNcr()->getFqdn())
                      .arg(getCurrentServer()->toText());

            retryTransition(SELECTING_FWD_SERVER_ST);
            break;

        case DNSClient::INVALID_RESPONSE:
            // A response was received but was corrupt. Retry it like an IO
            // error.
            LOG_ERROR(d2_to_dns_logger, DHCP_DDNS_FORWARD_ADD_RESP_CORRUPT)
                      .arg(getRequestId())
                      .arg(getCurrentServer()->toText())
                      .arg(getNcr()->getFqdn());

            retryTransition(SELECTING_FWD_SERVER_ST);
            break;

        default:
            // Any other value and we will fail this transaction, something
            // bigger is wrong.
            LOG_ERROR(d2_to_dns_logger, DHCP_DDNS_FORWARD_ADD_BAD_DNSCLIENT_STATUS)
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
            try {
                buildReplaceFwdAddressRequest();
            } catch (const std::exception& ex) {
                // While unlikely, the build might fail if we have invalid
                // data.  Should that be the case, we need to fail the
                // transaction.
                LOG_ERROR(d2_to_dns_logger, DHCP_DDNS_FORWARD_REPLACE_BUILD_FAILURE)
                          .arg(getRequestId())
                          .arg(getNcr()->toText())
                          .arg(ex.what());
                transition(PROCESS_TRANS_FAILED_ST, UPDATE_FAILED_EVT);
                break;
            }
        }

        // Call sendUpdate() to initiate the async send. Note it also sets
        // next event to NOP_EVT.
        sendUpdate("Forward Replace");
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
                LOG_ERROR(d2_to_dns_logger, DHCP_DDNS_FORWARD_REPLACE_REJECTED)
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
            LOG_ERROR(d2_to_dns_logger, DHCP_DDNS_FORWARD_REPLACE_IO_ERROR)
                      .arg(getRequestId())
                      .arg(getNcr()->getFqdn())
                      .arg(getCurrentServer()->toText());

            // If we are out of retries on this server, we go back and start
            // all over on a new server.
            retryTransition(SELECTING_FWD_SERVER_ST);
            break;

        case DNSClient::INVALID_RESPONSE:
            // A response was received but was corrupt. Retry it like an IO
            // error.
            LOG_ERROR(d2_to_dns_logger, DHCP_DDNS_FORWARD_REPLACE_RESP_CORRUPT)
                      .arg(getRequestId())
                      .arg(getCurrentServer()->toText())
                      .arg(getNcr()->getFqdn());

            // If we are out of retries on this server, we go back and start
            // all over on a new server.
            retryTransition(SELECTING_FWD_SERVER_ST);
            break;

        default:
            // Any other value and we will fail this transaction, something
            // bigger is wrong.
            LOG_ERROR(d2_to_dns_logger,
                      DHCP_DDNS_FORWARD_REPLACE_BAD_DNSCLIENT_STATUS)
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
            try {
                buildReplaceRevPtrsRequest();
            } catch (const std::exception& ex) {
                // While unlikely, the build might fail if we have invalid
                // data.  Should that be the case, we need to fail the
                // transaction.
                LOG_ERROR(d2_to_dns_logger, DHCP_DDNS_REVERSE_REPLACE_BUILD_FAILURE)
                          .arg(getRequestId())
                          .arg(getNcr()->toText())
                          .arg(ex.what());
                transition(PROCESS_TRANS_FAILED_ST, UPDATE_FAILED_EVT);
                break;
            }
        }

        // Call sendUpdate() to initiate the async send. Note it also sets
        // next event to NOP_EVT.
        sendUpdate("Reverse Replace");
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
                LOG_ERROR(d2_to_dns_logger, DHCP_DDNS_REVERSE_REPLACE_REJECTED)
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
            LOG_ERROR(d2_to_dns_logger, DHCP_DDNS_REVERSE_REPLACE_IO_ERROR)
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
            LOG_ERROR(d2_to_dns_logger, DHCP_DDNS_REVERSE_REPLACE_RESP_CORRUPT)
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
                      DHCP_DDNS_REVERSE_REPLACE_BAD_DNSCLIENT_STATUS)
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
        isc_throw(NameAddTransactionError,
                  "Wrong event for context: " << getContextStr());
    }
}

void
NameAddTransaction::processAddOkHandler() {
    switch(getNextEvent()) {
    case UPDATE_OK_EVT:
        LOG_INFO(d2_to_dns_logger, DHCP_DDNS_ADD_SUCCEEDED)
                 .arg(getRequestId())
                 .arg(getNcr()->toText());
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
    case NO_MORE_SERVERS_EVT:
        setNcrStatus(dhcp_ddns::ST_FAILED);
        LOG_ERROR(d2_to_dns_logger, DHCP_DDNS_ADD_FAILED)
                  .arg(getRequestId())
                  .arg(transactionOutcomeString());
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
    // Construct an empty request.
    D2UpdateMessagePtr request = prepNewRequest(getForwardDomain());

    // Construct dns::Name from NCR fqdn.
    dns::Name fqdn(dns::Name(getNcr()->getFqdn()));

    // Content on this request is based on RFC 4703, section 5.3.1
    // First build the Prerequisite Section.

    // Create 'FQDN Is Not In Use' prerequisite and add it to the
    // prerequisite section.
    // Based on RFC 2136, section 2.4.5
    dns::RRsetPtr prereq(new dns::RRset(fqdn, dns::RRClass::NONE(),
                             dns::RRType::ANY(), dns::RRTTL(0)));
    request->addRRset(D2UpdateMessage::SECTION_PREREQUISITE, prereq);

    // Next build the Update Section.

    // Create the TTL based on lease length.
    dns::RRTTL lease_ttl(getNcr()->getLeaseLength());

    // Create the FQDN/IP 'add' RR and add it to the to update section.
    // Based on RFC 2136, section 2.5.1
    dns::RRsetPtr update(new dns::RRset(fqdn, dns::RRClass::IN(),
                         getAddressRRType(), lease_ttl));

    addLeaseAddressRdata(update);
    request->addRRset(D2UpdateMessage::SECTION_UPDATE, update);

    // Now create the FQDN/DHCID 'add' RR and add it to update section.
    // Based on RFC 2136, section 2.5.1
    update.reset(new dns::RRset(fqdn, dns::RRClass::IN(),
                                dns::RRType::DHCID(), lease_ttl));
    addDhcidRdata(update);
    request->addRRset(D2UpdateMessage::SECTION_UPDATE, update);

    // Set the transaction's update request to the new request.
    setDnsUpdateRequest(request);
}

void
NameAddTransaction::buildReplaceFwdAddressRequest() {
    // Construct an empty request.
    D2UpdateMessagePtr request = prepNewRequest(getForwardDomain());

    // Construct dns::Name from NCR fqdn.
    dns::Name fqdn(dns::Name(getNcr()->getFqdn()));

    // Content on this request is based on RFC 4703, section 5.3.2
    // First build the Prerequisite Section.

    // Create an 'FQDN Is In Use' prerequisite and add it to the
    // pre-requisite section.
    // Based on RFC 2136, section 2.4.4
    dns::RRsetPtr prereq(new dns::RRset(fqdn, dns::RRClass::ANY(),
                               dns::RRType::ANY(), dns::RRTTL(0)));
    request->addRRset(D2UpdateMessage::SECTION_PREREQUISITE, prereq);

    // Create an DHCID matches prerequisite RR and add it to the
    // pre-requisite section.
    // Based on RFC 2136, section 2.4.2.
    prereq.reset(new dns::RRset(fqdn, dns::RRClass::IN(),
                 dns::RRType::DHCID(), dns::RRTTL(0)));
    addDhcidRdata(prereq);
    request->addRRset(D2UpdateMessage::SECTION_PREREQUISITE, prereq);

    // Next build the Update Section.

    // Create the TTL based on lease length.
    dns::RRTTL lease_ttl(getNcr()->getLeaseLength());

    // Create the FQDN/IP 'delete' RR and add it to the update section.
    // Based on RFC 2136, section 2.5.2
    dns::RRsetPtr update(new dns::RRset(fqdn, dns::RRClass::ANY(),
                         getAddressRRType(), dns::RRTTL(0)));
    request->addRRset(D2UpdateMessage::SECTION_UPDATE, update);

    // Create the FQDN/IP 'add' RR and add it to the update section.
    // Based on RFC 2136, section 2.5.1
    update.reset(new dns::RRset(fqdn, dns::RRClass::IN(),
                                getAddressRRType(), lease_ttl));
    addLeaseAddressRdata(update);
    request->addRRset(D2UpdateMessage::SECTION_UPDATE, update);

    // Set the transaction's update request to the new request.
    setDnsUpdateRequest(request);
}

void
NameAddTransaction::buildReplaceRevPtrsRequest() {
    // Construct an empty request.
    D2UpdateMessagePtr request = prepNewRequest(getReverseDomain());

    // Create the reverse IP address "FQDN".
    std::string rev_addr = D2CfgMgr::reverseIpAddress(getNcr()->getIpAddress());
    dns::Name rev_ip(rev_addr);

    // Create the TTL based on lease length.
    dns::RRTTL lease_ttl(getNcr()->getLeaseLength());

    // Content on this request is based on RFC 4703, section 5.4
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
                                dns::RRType::PTR(), lease_ttl));
    addPtrRdata(update);
    request->addRRset(D2UpdateMessage::SECTION_UPDATE, update);

    // Create the FQDN/IP PTR 'add' RR, add the DHCID Rdata
    // then add it to update section.
    update.reset(new dns::RRset(rev_ip, dns::RRClass::IN(),
                                dns::RRType::DHCID(), lease_ttl));
    addDhcidRdata(update);
    request->addRRset(D2UpdateMessage::SECTION_UPDATE, update);

    // Set the transaction's update request to the new request.
    setDnsUpdateRequest(request);
}

} // namespace isc::d2
} // namespace isc
