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
#include <d2/nc_trans.h>
#include <dns/rdata.h>

#include <sstream>

namespace isc {
namespace d2 {

// Common transaction states
const int NameChangeTransaction::READY_ST;
const int NameChangeTransaction::SELECTING_FWD_SERVER_ST;
const int NameChangeTransaction::SELECTING_REV_SERVER_ST;
const int NameChangeTransaction::PROCESS_TRANS_OK_ST;
const int NameChangeTransaction::PROCESS_TRANS_FAILED_ST;

const int NameChangeTransaction::NCT_DERIVED_STATE_MIN;

// Common transaction events
const int NameChangeTransaction::SELECT_SERVER_EVT;
const int NameChangeTransaction::SERVER_SELECTED_EVT;
const int NameChangeTransaction::SERVER_IO_ERROR_EVT;
const int NameChangeTransaction::NO_MORE_SERVERS_EVT;
const int NameChangeTransaction::IO_COMPLETED_EVT;
const int NameChangeTransaction::UPDATE_OK_EVT;
const int NameChangeTransaction::UPDATE_FAILED_EVT;

const int NameChangeTransaction::NCT_DERIVED_EVENT_MIN;

const unsigned int NameChangeTransaction::MAX_UPDATE_TRIES_PER_SERVER;

NameChangeTransaction::
NameChangeTransaction(asiolink::IOServicePtr& io_service,
                      dhcp_ddns::NameChangeRequestPtr& ncr,
                      DdnsDomainPtr& forward_domain,
                      DdnsDomainPtr& reverse_domain,
                      D2CfgMgrPtr& cfg_mgr)
    : io_service_(io_service), ncr_(ncr), forward_domain_(forward_domain),
     reverse_domain_(reverse_domain), dns_client_(), dns_update_request_(),
     dns_update_status_(DNSClient::OTHER), dns_update_response_(),
     forward_change_completed_(false), reverse_change_completed_(false),
     current_server_list_(), current_server_(), next_server_pos_(0),
     update_attempts_(0), cfg_mgr_(cfg_mgr), tsig_key_() {
    /// @todo if io_service is NULL we are multi-threading and should
    /// instantiate our own
    if (!io_service_) {
        isc_throw(NameChangeTransactionError, "IOServicePtr cannot be null");
    }

    if (!ncr_) {
        isc_throw(NameChangeTransactionError,
                  "NameChangeRequest cannot be null");
    }

    if (ncr_->isForwardChange() && !(forward_domain_)) {
        isc_throw(NameChangeTransactionError,
                 "Forward change must have a forward domain");
    }

    if (ncr_->isReverseChange() && !(reverse_domain_)) {
        isc_throw(NameChangeTransactionError,
                 "Reverse change must have a reverse domain");
    }

    if (!cfg_mgr_) {
        isc_throw(NameChangeTransactionError,
                  "Configuration manager cannot be null");
    }
}

NameChangeTransaction::~NameChangeTransaction(){
}

void
NameChangeTransaction::startTransaction() {
    LOG_DEBUG(d2_to_dns_logger, DBGLVL_TRACE_DETAIL,
              DHCP_DDNS_STARTING_TRANSACTION)
              .arg(getRequestId());

    setNcrStatus(dhcp_ddns::ST_PENDING);
    startModel(READY_ST);
}

void
NameChangeTransaction::operator()(DNSClient::Status status) {
    // Stow the completion status and re-enter the run loop with the event
    // set to indicate IO completed.
    // runModel is exception safe so we are good to call it here.
    // It won't exit until we hit the next IO wait or the state model ends.
    setDnsUpdateStatus(status);
    LOG_DEBUG(d2_to_dns_logger, DBGLVL_TRACE_DETAIL,
              DHCP_DDNS_UPDATE_RESPONSE_RECEIVED)
              .arg(getRequestId())
              .arg(current_server_->toText())
              .arg(responseString());

    runModel(IO_COMPLETED_EVT);
}

std::string
NameChangeTransaction::responseString() const {
    std::ostringstream stream;
    switch (getDnsUpdateStatus()) {
        case DNSClient::SUCCESS:
            stream << "SUCCESS, rcode: ";
            if (getDnsUpdateResponse()) {
                 stream << getDnsUpdateResponse()->getRcode().toText();
            } else {
                stream << " update response is NULL";
            }
            break;
        case DNSClient::TIMEOUT:
            stream << "TIMEOUT";
            break;
        case DNSClient::IO_STOPPED:
            stream << "IO_STOPPED";
            break;
        case DNSClient::INVALID_RESPONSE:
            stream << "INVALID_RESPONSE";
            break;
        case DNSClient::OTHER:
            stream << "OTHER";
            break;
        default:
            stream << "UKNOWNN("
                   << static_cast<int>(getDnsUpdateStatus()) << ")";
            break;

    }

    return (stream.str());
}

std::string
NameChangeTransaction::transactionOutcomeString() const {
    std::ostringstream stream;
    stream << "Status: " << (getNcrStatus() == dhcp_ddns::ST_COMPLETED
                             ? "Completed, " : "Failed, ")
           << "Event: " << getEventLabel(getNextEvent()) << ", ";

    if (ncr_->isForwardChange()) {
        stream << " Forward change:" << (getForwardChangeCompleted()
                                         ? " completed, " : " failed, ");
    }

    if (ncr_->isReverseChange()) {
        stream << " Reverse change:" << (getReverseChangeCompleted()
                                          ? " completed, " : " failed, ");
    }

    stream << " request: " << ncr_->toText();
    return (stream.str());
}


void
NameChangeTransaction::sendUpdate(const std::string& comment) {
    try {
        ++update_attempts_;
        // @todo add logic to add/replace TSIG key info in request if
        // use_tsig_ is true. We should be able to navigate to the TSIG key
        // for the current server.  If not we would need to add that.

        D2ParamsPtr d2_params = cfg_mgr_->getD2Params();
        dns_client_->doUpdate(*io_service_, current_server_->getIpAddress(),
                              current_server_->getPort(), *dns_update_request_,
                              d2_params->getDnsServerTimeout(), tsig_key_);
        // Message is on its way, so the next event should be NOP_EVT.
        postNextEvent(NOP_EVT);
        LOG_DEBUG(d2_to_dns_logger, DBGLVL_TRACE_DETAIL,
                  DHCP_DDNS_UPDATE_REQUEST_SENT)
                  .arg(getRequestId())  
                  .arg(comment)
                  .arg(current_server_->toText());
    } catch (const std::exception& ex) {
        // We were unable to initiate the send.
        // It is presumed that any throw from doUpdate is due to a programmatic
        // error, such as an unforeseen permutation of data, rather than an IO
        // failure. IO errors should be caught by the underlying asiolink
        // mechanisms and manifested as an unsuccessful IO status in the
        // DNSClient callback.  Any problem here most likely means the request
        // is corrupt in some way and cannot be completed, therefore we will
        // log it and transition it to failure.
        LOG_ERROR(d2_to_dns_logger, DHCP_DDNS_TRANS_SEND_ERROR)
                  .arg(getRequestId())  
                  .arg(ex.what());
        transition(PROCESS_TRANS_FAILED_ST, UPDATE_FAILED_EVT);
    }
}

void
NameChangeTransaction::defineEvents() {
    // Call superclass impl first.
    StateModel::defineEvents();

    // Define NCT events.
    defineEvent(SELECT_SERVER_EVT, "SELECT_SERVER_EVT");
    defineEvent(SERVER_SELECTED_EVT, "SERVER_SELECTED_EVT");
    defineEvent(SERVER_IO_ERROR_EVT, "SERVER_IO_ERROR_EVT");
    defineEvent(NO_MORE_SERVERS_EVT, "NO_MORE_SERVERS_EVT");
    defineEvent(IO_COMPLETED_EVT, "IO_COMPLETED_EVT");
    defineEvent(UPDATE_OK_EVT, "UPDATE_OK_EVT");
    defineEvent(UPDATE_FAILED_EVT, "UPDATE_FAILED_EVT");
}

void
NameChangeTransaction::verifyEvents() {
    // Call superclass impl first.
    StateModel::verifyEvents();

    // Verify NCT events.
    getEvent(SELECT_SERVER_EVT);
    getEvent(SERVER_SELECTED_EVT);
    getEvent(SERVER_IO_ERROR_EVT);
    getEvent(NO_MORE_SERVERS_EVT);
    getEvent(IO_COMPLETED_EVT);
    getEvent(UPDATE_OK_EVT);
    getEvent(UPDATE_FAILED_EVT);
}

void
NameChangeTransaction::defineStates() {
    // Call superclass impl first.
    StateModel::defineStates();
    // This class is "abstract" in that it does not supply handlers for its
    // states, derivations must do that therefore they must define them.
}

void
NameChangeTransaction::verifyStates() {
    // Call superclass impl first.
    StateModel::verifyStates();

    // Verify NCT states. This ensures that derivations provide the handlers.
    getState(READY_ST);
    getState(SELECTING_FWD_SERVER_ST);
    getState(SELECTING_REV_SERVER_ST);
    getState(PROCESS_TRANS_OK_ST);
    getState(PROCESS_TRANS_FAILED_ST);
}

void
NameChangeTransaction::onModelFailure(const std::string& explanation) {
    setNcrStatus(dhcp_ddns::ST_FAILED);
    LOG_ERROR(d2_to_dns_logger, DHCP_DDNS_STATE_MODEL_UNEXPECTED_ERROR)
              .arg(getRequestId())
              .arg(explanation);
}

void
NameChangeTransaction::retryTransition(const int fail_to_state) {
    if (update_attempts_ < MAX_UPDATE_TRIES_PER_SERVER) {
        // Re-enter the current state with same server selected.
        transition(getCurrState(), SERVER_SELECTED_EVT);
    } else  {
        // Transition to given fail_to_state state if we are out
        // of retries.
        transition(fail_to_state, SERVER_IO_ERROR_EVT);
    }
}

void
NameChangeTransaction::setDnsUpdateRequest(D2UpdateMessagePtr& request) {
    dns_update_request_ = request;
}

void
NameChangeTransaction::clearDnsUpdateRequest() {
    update_attempts_ = 0;
    dns_update_request_.reset();
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
NameChangeTransaction::clearDnsUpdateResponse() {
    dns_update_response_.reset();
}

void
NameChangeTransaction::setForwardChangeCompleted(const bool value) {
    forward_change_completed_ = value;
}

void
NameChangeTransaction::setReverseChangeCompleted(const bool value) {
    reverse_change_completed_ = value;
}

void
NameChangeTransaction::setUpdateAttempts(const size_t value) {
    update_attempts_ = value;
}

D2UpdateMessagePtr
NameChangeTransaction::prepNewRequest(DdnsDomainPtr domain) {
    if (!domain) {
        isc_throw(NameChangeTransactionError,
                  "prepNewRequest - domain cannot be null");
    }

    try {
        // Create a "blank" update request.
        D2UpdateMessagePtr request(new D2UpdateMessage(D2UpdateMessage::
                                                       OUTBOUND));
        // Construct the Zone Section.
        dns::Name zone_name(domain->getName());
        request->setZone(zone_name, dns::RRClass::IN());
        return (request);
    } catch (const std::exception& ex) {
        isc_throw(NameChangeTransactionError, "Cannot create new request :"
                  << ex.what());
    }
}

void
NameChangeTransaction::addLeaseAddressRdata(dns::RRsetPtr& rrset) {
    if (!rrset) {
        isc_throw(NameChangeTransactionError,
                  "addLeaseAddressRdata - RRset cannot cannot be null");
    }

    try {
        // Manufacture an RData from the lease address then add it to the RR.
        dns::rdata::ConstRdataPtr rdata;
        if (ncr_->isV4()) {
            rdata.reset(new dns::rdata::in::A(ncr_->getIpAddress()));
        } else {
            rdata.reset(new dns::rdata::in::AAAA(ncr_->getIpAddress()));
        }
        rrset->addRdata(rdata);
    } catch (const std::exception& ex) {
        isc_throw(NameChangeTransactionError, "Cannot add address rdata: "
                  << ex.what());
    }
}

void
NameChangeTransaction::addDhcidRdata(dns::RRsetPtr& rrset) {
    if (!rrset) {
        isc_throw(NameChangeTransactionError,
                  "addDhcidRdata - RRset cannot cannot be null");
    }

    try {
        const std::vector<uint8_t>& ncr_dhcid = ncr_->getDhcid().getBytes();
        util::InputBuffer buffer(ncr_dhcid.data(), ncr_dhcid.size());
        dns::rdata::ConstRdataPtr rdata (new dns::rdata::in::
                                         DHCID(buffer, ncr_dhcid.size()));
        rrset->addRdata(rdata);
    } catch (const std::exception& ex) {
        isc_throw(NameChangeTransactionError, "Cannot add DCHID rdata: "
                  << ex.what());
    }

}

void
NameChangeTransaction::addPtrRdata(dns::RRsetPtr& rrset) {
    if (!rrset) {
        isc_throw(NameChangeTransactionError,
                  "addPtrRdata - RRset cannot cannot be null");
    }

    try {
        dns::rdata::ConstRdataPtr rdata(new dns::rdata::generic::
                                        PTR(getNcr()->getFqdn()));
        rrset->addRdata(rdata);
    } catch (const std::exception& ex) {
        isc_throw(NameChangeTransactionError, "Cannot add PTR rdata: "
                  << ex.what());
    }
}

const dhcp_ddns::NameChangeRequestPtr&
NameChangeTransaction::getNcr() const {
    return (ncr_);
}

const TransactionKey&
NameChangeTransaction::getTransactionKey() const {
    return (ncr_->getDhcid());
}

std::string
NameChangeTransaction::getRequestId() const {
    return (ncr_->getRequestId());
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

    // Set the tsig_key to that of the DdnsDomain.
    TSIGKeyInfoPtr tsig_key_info = domain->getTSIGKeyInfo();
    if (tsig_key_info) {
        tsig_key_ = tsig_key_info->getTSIGKey();
    } else {
        tsig_key_.reset();
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
        // Toss out any previous response.
        dns_update_response_.reset();

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

const D2UpdateMessagePtr&
NameChangeTransaction::getDnsUpdateRequest() const {
    return (dns_update_request_);
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

size_t
NameChangeTransaction::getUpdateAttempts() const {
    return (update_attempts_);
}

const dns::RRType&
NameChangeTransaction::getAddressRRType() const {
    return (ncr_->isV4() ?  dns::RRType::A() : dns::RRType::AAAA());
}

} // namespace isc::d2
} // namespace isc
