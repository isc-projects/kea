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
#include <d2/nc_trans.h>

namespace isc {
namespace d2 {

// Common transaction states
const int NameChangeTransaction::READY_ST;
const int NameChangeTransaction::SELECTING_FWD_SERVER_ST;
const int NameChangeTransaction::SELECTING_REV_SERVER_ST;
const int NameChangeTransaction::PROCESS_TRANS_OK_ST;
const int NameChangeTransaction::PROCESS_TRANS_FAILED_ST;

const int NameChangeTransaction::NCT_STATE_MAX;

// Common transaction events
const int NameChangeTransaction::SELECT_SERVER_EVT;
const int NameChangeTransaction::SERVER_SELECTED_EVT;
const int NameChangeTransaction::SERVER_IO_ERROR_EVT;
const int NameChangeTransaction::NO_MORE_SERVERS_EVT;
const int NameChangeTransaction::IO_COMPLETED_EVT;
const int NameChangeTransaction::UPDATE_OK_EVT;
const int NameChangeTransaction::UPDATE_FAILED_EVT;

const int NameChangeTransaction::NCT_EVENT_MAX;

NameChangeTransaction::
NameChangeTransaction(isc::asiolink::IOService& io_service,
                      dhcp_ddns::NameChangeRequestPtr& ncr,
                      DdnsDomainPtr& forward_domain,
                      DdnsDomainPtr& reverse_domain)
    : io_service_(io_service), ncr_(ncr), forward_domain_(forward_domain),
     reverse_domain_(reverse_domain), dns_client_(),
     dns_update_status_(DNSClient::OTHER), dns_update_response_(),
     forward_change_completed_(false), reverse_change_completed_(false),
     current_server_list_(), current_server_(), next_server_pos_(0) {
    if (!ncr_) {
        isc_throw(NameChangeTransactionError, "NameChangeRequest cannot null");
    }

    if (ncr_->isForwardChange() && !(forward_domain_)) {
        isc_throw(NameChangeTransactionError,
                 "Forward change must have a forward domain");
    }

    if (ncr_->isReverseChange() && !(reverse_domain_)) {
        isc_throw(NameChangeTransactionError,
                 "Reverse change must have a reverse domain");
    }
}

NameChangeTransaction::~NameChangeTransaction(){
}

void
NameChangeTransaction::startTransaction() {
    startModel(READY_ST);
}

void
NameChangeTransaction::operator()(DNSClient::Status status) {
    // Stow the completion status and re-enter the run loop with the event
    // set to indicate IO completed.
    // runModel is exception safe so we are good to call it here.
    // It won't exit until we hit the next IO wait or the state model ends.
    setDnsUpdateStatus(status);
    runModel(IO_COMPLETED_EVT);
}


void
NameChangeTransaction::verifyStateHandlerMap() {
    getStateHandler(READY_ST);
    getStateHandler(SELECTING_FWD_SERVER_ST);
    getStateHandler(SELECTING_REV_SERVER_ST);
    getStateHandler(PROCESS_TRANS_OK_ST);
    getStateHandler(PROCESS_TRANS_FAILED_ST);
}

void
NameChangeTransaction::onModelFailure() {
    setNcrStatus(dhcp_ddns::ST_FAILED);
}

void
NameChangeTransaction::setDnsUpdateStatus(const DNSClient::Status& status) {
    dns_update_status_ = status;
}

void
NameChangeTransaction::setForwardChangeCompleted(const bool value) {
    forward_change_completed_ = value;
}

void
NameChangeTransaction::setReverseChangeCompleted(const bool value) {
    reverse_change_completed_ = value;
}

const dhcp_ddns::NameChangeRequestPtr&
NameChangeTransaction::getNcr() const {
    return (ncr_);
}

const TransactionKey&
NameChangeTransaction::getTransactionKey() const {
    return (ncr_->getDhcid());
}

dhcp_ddns::NameChangeStatus
NameChangeTransaction::getNcrStatus() const {
    return (ncr_->getStatus());
}

DdnsDomainPtr&
NameChangeTransaction::getForwardDomain() {
    return (forward_domain_);
}

DdnsDomainPtr&
NameChangeTransaction::getReverseDomain() {
    return (reverse_domain_);
}

void
NameChangeTransaction::initServerSelection(const DdnsDomainPtr& domain) {
    if (!domain) {
        isc_throw(NameChangeTransactionError,
                  "initServerSelection called with an empty domain");
    }
    current_server_list_ = domain->getServers();
    next_server_pos_ = 0;
    current_server_.reset();
}

bool
NameChangeTransaction::selectNextServer() {
    if ((current_server_list_) &&
        (next_server_pos_ < current_server_list_->size())) {
        current_server_  = (*current_server_list_)[next_server_pos_];
        dns_update_response_.reset(new
                                   D2UpdateMessage(D2UpdateMessage::INBOUND));
        // @todo  Protocol is set on DNSClient constructor.  We need
        // to propagate a configuration value downward, probably starting
        // at global, then domain, then server
        // Once that is supported we need to add it here.
        dns_client_.reset(new DNSClient(dns_update_response_ , this,
                                        DNSClient::UDP));
        ++next_server_pos_;
        return (true);
    }

    return (false);
}

const DNSClientPtr&
NameChangeTransaction::getDNSClient() const {
    return (dns_client_);
}

const DnsServerInfoPtr&
NameChangeTransaction::getCurrentServer() const {
    return (current_server_);
}


void
NameChangeTransaction::setNcrStatus(const dhcp_ddns::NameChangeStatus& status) {
    return (ncr_->setStatus(status));
}

DNSClient::Status
NameChangeTransaction::getDnsUpdateStatus() const {
    return (dns_update_status_);
}

const D2UpdateMessagePtr&
NameChangeTransaction::getDnsUpdateResponse() const {
    return (dns_update_response_);
}

bool
NameChangeTransaction::getForwardChangeCompleted() const {
    return (forward_change_completed_);
}

bool
NameChangeTransaction::getReverseChangeCompleted() const {
    return (reverse_change_completed_);
}

const char*
NameChangeTransaction::getStateLabel(const int state) const {
    const char* str = "Unknown";
    switch(state) {
    case READY_ST:
        str = "NameChangeTransaction::READY_ST";
        break;
    case SELECTING_FWD_SERVER_ST:
        str = "NameChangeTransaction::SELECTING_FWD_SERVER_ST";
        break;
    case SELECTING_REV_SERVER_ST:
        str = "NameChangeTransaction::SELECTING_REV_SERVER_ST";
        break;
    case PROCESS_TRANS_OK_ST:
        str = "NameChangeTransaction::PROCESS_TRANS_OK_ST";
        break;
    case PROCESS_TRANS_FAILED_ST:
        str = "NameChangeTransaction::PROCESS_TRANS_FAILED_ST";
        break;
    default:
        str = StateModel::getStateLabel(state);
        break;
    }

    return (str);
}

const char*
NameChangeTransaction::getEventLabel(const int event) const {
    const char* str = "Unknown";
    switch(event) {
    case SELECT_SERVER_EVT:
        str = "NameChangeTransaction::SELECT_SERVER_EVT";
        break;
    case SERVER_SELECTED_EVT:
        str = "NameChangeTransaction::SERVER_SELECTED_EVT";
        break;
    case SERVER_IO_ERROR_EVT:
        str = "NameChangeTransaction::SERVER_IO_ERROR_EVT";
        break;
    case NO_MORE_SERVERS_EVT:
        str = "NameChangeTransaction::NO_MORE_SERVERS_EVT";
        break;
    case IO_COMPLETED_EVT:
        str = "NameChangeTransaction::IO_COMPLETED_EVT";
        break;
    case UPDATE_OK_EVT:
        str = "NameChangeTransaction::UPDATE_OK_EVT";
        break;
    case UPDATE_FAILED_EVT:
        str = "NameChangeTransaction::UPDATE_FAILED_EVT";
        break;
    default:
        str = StateModel::getEventLabel(event);
        break;
    }

    return (str);
}


} // namespace isc::d2
} // namespace isc
