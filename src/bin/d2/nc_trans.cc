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
const int NameChangeTransaction::NEW_ST;
const int NameChangeTransaction::READY_ST;
const int NameChangeTransaction::SELECTING_FWD_SERVER_ST;
const int NameChangeTransaction::SELECTING_REV_SERVER_ST;
const int NameChangeTransaction::DONE_ST;

const int NameChangeTransaction::DERIVED_STATES;

// Common transaction events
const int NameChangeTransaction::NOP_EVT;
const int NameChangeTransaction::START_TRANSACTION_EVT;
const int NameChangeTransaction::SELECT_SERVER_EVT;
const int NameChangeTransaction::SERVER_SELECTED_EVT;
const int NameChangeTransaction::SERVER_IO_ERROR_EVT;
const int NameChangeTransaction::NO_MORE_SERVERS_EVT;
const int NameChangeTransaction::IO_COMPLETED_EVT;
const int NameChangeTransaction::UPDATE_OK_EVT;
const int NameChangeTransaction::UPDATE_FAILED_EVT;
const int NameChangeTransaction::CANCEL_TRANSACTION_EVT;
const int NameChangeTransaction::ALL_DONE_EVT;

const int NameChangeTransaction::DERIVED_EVENTS;

NameChangeTransaction::
NameChangeTransaction(isc::asiolink::IOService& io_service,
                      dhcp_ddns::NameChangeRequestPtr& ncr,
                      DdnsDomainPtr forward_domain,
                      DdnsDomainPtr reverse_domain)
    : state_handlers_(), io_service_(io_service), ncr_(ncr),
     forward_domain_(forward_domain), reverse_domain_(reverse_domain),
     dns_client_(), state_(NEW_ST), next_event_(NOP_EVT),
     dns_update_status_(DNSClient::OTHER), dns_update_response_(),
     forward_change_completed_(false), reverse_change_completed_(false) {
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
    
    // Use setters here so we get proper values for previous state, last event.
    setState(state_);
    setNextEvent(NOP_EVT);
}

NameChangeTransaction::~NameChangeTransaction(){
}

void
NameChangeTransaction::startTransaction() {
    // Initialize the state handler map first.
    initStateHandlerMap();

    // Set the current state to READY and enter the run loop.
    setState(READY_ST);
    runStateModel(START_TRANSACTION_EVT);
}

void
NameChangeTransaction::cancelTransaction() {
    //@todo It is up to the deriving state model to handle this event.
    runStateModel(CANCEL_TRANSACTION_EVT);
}

void
NameChangeTransaction::operator()(DNSClient::Status status) {
    // Stow the completion status and re-enter the run loop with the event
    // set to indicate IO completed.
    // runStateModel is exception safe so we are good to call it here.  
    // It won't exit until we hit the next IO wait or the state model ends.
    setDnsUpdateStatus(status);
    runStateModel(IO_COMPLETED_EVT);
}

void
NameChangeTransaction::runStateModel(unsigned int run_event) {
    try {
        // Seed the loop with the given event as the next to process.
        setNextEvent(run_event);
        do {
            // Invoke the current state's handler.  It should consume the 
            // next event, then determine what happens next by setting
            // current state and/or the next event.  
            (getStateHandler(state_))();

            // Keep going until a handler sets next event to a NOP_EVT. 
        } while (getNextEvent() != NOP_EVT);
    }
    catch (const std::exception& ex) {
        // Transaction has suffered an unexpected exception.  This indicates
        // a programmatic shortcoming.  Log it and set status to ST_FAILED.
        // In theory, the model should account for all error scenarios and
        // deal with them accordingly.
        LOG_ERROR(dctl_logger, DHCP_DDNS_TRANS_PROCESS_EROR).arg(ex.what());
        setNcrStatus(dhcp_ddns::ST_FAILED);
    }
}


StateHandler
NameChangeTransaction::getStateHandler(unsigned int state) {
    StateHandlerMap::iterator it = state_handlers_.find(state);
    if (it == state_handlers_.end()) {
        isc_throw(NameChangeTransactionError, "Invalid state: " << state);
    }

    return ((*it).second);
}

void
NameChangeTransaction::addToMap(unsigned int state, StateHandler handler) {
    StateHandlerMap::iterator it = state_handlers_.find(state);
    if (it != state_handlers_.end()) {
        isc_throw(NameChangeTransactionError,
                  "Attempted duplicate entry in state handler mape, state: "
                   << state);
    }

    state_handlers_[state] = handler;
}

void
NameChangeTransaction::setState(unsigned int state) {
    prev_state_ = state_;
    state_ = state;
}

void
NameChangeTransaction::setNextEvent(unsigned int event) {
    last_event_ = next_event_;
    next_event_ = event;
}

void
NameChangeTransaction::setDnsUpdateStatus(const DNSClient::Status& status) {
    dns_update_status_ = status;
}

void
NameChangeTransaction::setDnsUpdateResponse(D2UpdateMessagePtr& response) {
    dns_update_response_ = response;
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

void
NameChangeTransaction::setNcrStatus(const dhcp_ddns::NameChangeStatus& status) {
    return (ncr_->setStatus(status));
}

unsigned int
NameChangeTransaction::getState() const {
    return (state_);
}

unsigned int
NameChangeTransaction::getPrevState() const {
    return (prev_state_);
}

unsigned int
NameChangeTransaction::getLastEvent() const {
    return (last_event_);
}

unsigned int
NameChangeTransaction::getNextEvent() const {
    return (next_event_);
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


} // namespace isc::d2
} // namespace isc
