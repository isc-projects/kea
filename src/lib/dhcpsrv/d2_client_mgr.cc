// Copyright (C) 2014 Internet Systems Consortium, Inc. ("ISC")
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

#include <dhcp_ddns/ncr_udp.h>
#include <dhcpsrv/d2_client_mgr.h>
#include <dhcpsrv/dhcpsrv_log.h>

#include <string>

using namespace std;

namespace isc {
namespace dhcp {

D2ClientMgr::D2ClientMgr() : d2_client_config_(new D2ClientConfig()),
    name_change_sender_(), private_io_service_(), sender_io_service_(NULL) {
    // Default constructor initializes with a disabled configuration.
}

D2ClientMgr::~D2ClientMgr(){
}

void
D2ClientMgr::setD2ClientConfig(D2ClientConfigPtr& new_config) {
    if (!new_config) {
        isc_throw(D2ClientError,
                  "D2ClientMgr cannot set DHCP-DDNS configuration to NULL.");
    }

    // Don't do anything unless configuration values are actually different.
    if (*d2_client_config_ != *new_config) {
        if (!new_config->getEnableUpdates()) {
            // Updating has been turned off, destroy current sender.
            // Any queued requests are tossed.
            name_change_sender_.reset();
        } else {
            dhcp_ddns::NameChangeSenderPtr new_sender;
            switch (new_config->getNcrProtocol()) {
            case dhcp_ddns::NCR_UDP: {
                /// @todo Should we be able to configure a sender's client
                /// side ip and port?  We should certainly be able to
                /// configure a maximum queue size.  These were overlooked
                /// but are covered in Trac# 3328.
                isc::asiolink::IOAddress any_addr("0.0.0.0");
                uint32_t any_port = 0;
                uint32_t queue_max = 1024;

                // Instantiate a new sender.
                new_sender.reset(new dhcp_ddns::NameChangeUDPSender(
                                                any_addr, any_port,
                                                new_config->getServerIp(),
                                                new_config->getServerPort(),
                                                new_config->getNcrFormat(),
                                                *this, queue_max));
                break;
                }
            default:
                // In theory you can't get here.
                isc_throw(D2ClientError, "Invalid sender Protocol: "
                          << new_config->getNcrProtocol());
                break;
            }

            // Transfer queued requests from previous sender to the new one.
            /// @todo - Should we consider anything queued to be wrong?
            /// If only server values changed content might still be right but
            /// if content values changed (e.g. suffix or an override flag)
            /// then the queued contents might now be invalid.  There is
            /// no way to regenerate them if they are wrong.
            if (name_change_sender_) {
                name_change_sender_->stopSending();
                new_sender->assumeQueue(*name_change_sender_);
            }

            // Replace the old sender with the new one.
            name_change_sender_ = new_sender;
        }
    }

    // Update the configuration.
    d2_client_config_ = new_config;
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE, DHCPSRV_CFGMGR_CFG_DHCP_DDNS)
              .arg(!ddnsEnabled() ? "DHCP-DDNS updates disabled" :
                   "DHCP_DDNS updates enabled");
}

bool
D2ClientMgr::ddnsEnabled() {
    return (d2_client_config_->getEnableUpdates());
}

const D2ClientConfigPtr&
D2ClientMgr::getD2ClientConfig() const {
    return (d2_client_config_);
}

void
D2ClientMgr::analyzeFqdn(const bool client_s, const bool client_n,
                         bool& server_s, bool& server_n) const {
    // Per RFC 4702 & 4704, the client N and S flags allow the client to
    // request one of three options:
    //
    //  N flag  S flag   Option
    // ------------------------------------------------------------------
    //    0       0      client wants to do forward updates (section 3.2)
    //    0       1      client wants server to do forward updates (section 3.3)
    //    1       0      client wants no one to do updates (section 3.4)
    //    1       1      invalid combination
    // (Note section numbers cited are for 4702, for 4704 see 5.1, 5.2, and 5.3)
    //
    // Make a bit mask from the client's flags and use it to set the response
    // flags accordingly.
    const uint8_t mask = ((client_n ? 2 : 0) + (client_s ? 1 : 0));

    switch (mask) {
    case 0:
        // If updates are enabled and we are overriding client delegation
        // then S flag should be true.
        server_s = (d2_client_config_->getEnableUpdates() &&
                    d2_client_config_->getOverrideClientUpdate());
        break;

    case 1:
        server_s = d2_client_config_->getEnableUpdates();
        break;

    case 2:
        // If updates are enabled and we are overriding "no updates" then
        // S flag should be true.
        server_s = (d2_client_config_->getEnableUpdates() &&
                    d2_client_config_->getOverrideNoUpdate());
        break;

    default:
        // RFCs declare this an invalid combination.
        isc_throw(isc::BadValue,
                  "Invalid client FQDN - N and S cannot both be 1");
        break;
    }

    /// @todo Currently we are operating under the premise that N should be 1
    /// if the server is not doing updates nor do we have configuration
    /// controls to govern forward and reverse updates independently.
    /// In addition, the client FQDN flags cannot explicitly suggest what to
    /// do with reverse updates. They request either forward updates or no
    /// updates.  In other words, the client cannot request the server do or
    /// not do reverse updates.  For now, we are either going to do updates in
    /// both directions or none at all.  If and when additional configuration
    /// parameters are added this logic will have to be reassessed.
    server_n = !server_s;
}

std::string
D2ClientMgr::generateFqdn(const asiolink::IOAddress& address) const {
    std::string hostname = address.toText();
    std::replace(hostname.begin(), hostname.end(),
                 (address.isV4() ? '.' : ':'), '-');

    std::ostringstream gen_name;
    gen_name << d2_client_config_->getGeneratedPrefix() << "-" << hostname;
    return (qualifyName(gen_name.str()));
}

std::string
D2ClientMgr::qualifyName(const std::string& partial_name) const {
    std::ostringstream gen_name;
    gen_name << partial_name << "." << d2_client_config_->getQualifyingSuffix();

    // Tack on a trailing dot in case suffix doesn't have one.
    std::string str = gen_name.str();
    size_t len = str.length();
    if ((len > 0) && (str[len - 1] != '.')) {
        gen_name << ".";
    }

    return (gen_name.str());
}

void
D2ClientMgr::startSender(D2ClientErrorHandler error_handler) {
    // Create a our own service instance when we are not being multiplexed
    // into an external service..
    private_io_service_.reset(new asiolink::IOService());
    startSender(error_handler, *private_io_service_);
}

void
D2ClientMgr::startSender(D2ClientErrorHandler error_handler,
                         isc::asiolink::IOService& io_service) {
    if (!name_change_sender_)  {
        isc_throw(D2ClientError, "D2ClientMgr::startSender sender is null");
    }

    if (!error_handler) {
        isc_throw(D2ClientError, "D2ClientMgr::startSender handler is null");
    }

    // Set the error handler.
    client_error_handler_ = error_handler;

    // Remember the io service being used.
    sender_io_service_ = &io_service;

    // Start the sender on the given service.
    name_change_sender_->startSending(*sender_io_service_);

    /// @todo need to register sender's select-fd with IfaceMgr once 3315 is
    /// done.
}

bool
D2ClientMgr::amSending() const {
    return (name_change_sender_ && name_change_sender_->amSending());
}

void
D2ClientMgr::stopSender() {
    if (!name_change_sender_)  {
        isc_throw(D2ClientError, "D2ClientMgr::stopSender sender is null");
    }

    /// @todo need to unregister sender's select-fd with IfaceMgr once 3315 is
    /// done.

    name_change_sender_->stopSending();
}

void
D2ClientMgr::sendRequest(dhcp_ddns::NameChangeRequestPtr& ncr) {
    if (!name_change_sender_) {
        isc_throw(D2ClientError, "D2ClientMgr::sendRequest sender is null");
    }

    name_change_sender_->sendRequest(ncr);
}

size_t
D2ClientMgr::getQueueSize() const {
    if (!name_change_sender_) {
        isc_throw(D2ClientError, "D2ClientMgr::getQueueSize sender is null");
    }

    return(name_change_sender_->getQueueSize());
}


const dhcp_ddns::NameChangeRequestPtr&
D2ClientMgr::peekAt(const size_t index) const {
    if (!name_change_sender_) {
        isc_throw(D2ClientError, "D2ClientMgr::peekAt sender is null");
    }

    return (name_change_sender_->peekAt(index));
}

void
D2ClientMgr::clearQueue() {
    if (!name_change_sender_) {
        isc_throw(D2ClientError, "D2ClientMgr::clearQueue sender is null");
    }

    name_change_sender_->clearSendQueue();
}

void
D2ClientMgr::operator()(const dhcp_ddns::NameChangeSender::Result result,
                        dhcp_ddns::NameChangeRequestPtr& ncr) {
    if (result == dhcp_ddns::NameChangeSender::SUCCESS) {
        LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
                  DHCPSRV_DHCP_DDNS_NCR_SENT).arg(ncr->toText());
    } else {
        // Handler is mandatory but test it just to be safe.
        /// @todo Until we have a better feel for how errors need to be
        /// handled we farm it out to the application layer.
        if (client_error_handler_) {
            // Handler is not supposed to throw, but catch just in case.
            try {
                (client_error_handler_)(result, ncr);
            } catch (const std::exception& ex) {
                LOG_ERROR(dhcpsrv_logger, DHCPSRV_DHCP_DDNS_ERROR_EXCEPTION)
                          .arg(ex.what());
            }
        } else {
            LOG_ERROR(dhcpsrv_logger, DHCPSRV_DHCP_DDNS_HANDLER_NULL);
        }
   }
}

int
D2ClientMgr::getSelectFd() {
    if (!amSending()) {
        isc_throw (D2ClientError, "D2ClientMgr::getSelectFd "
                   " not in send mode");
    }

    return (name_change_sender_->getSelectFd());
}

void
D2ClientMgr::runReadyIO() {
    if (!sender_io_service_) {
        // This should never happen.
        isc_throw(D2ClientError, "D2ClientMgr::runReadyIO"
                  " sender io service is null");
    }

    // We shouldn't be here if IO isn't ready to execute.
    // By running poll we're gauranteed not to hang.
    /// @todo Trac# 3325 requests that asiolink::IOService provide a
    /// wrapper for poll().
    sender_io_service_->get_io_service().poll();
}

};  // namespace dhcp

};  // namespace isc
