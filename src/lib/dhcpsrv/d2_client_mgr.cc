// Copyright (C) 2014-2015 Internet Systems Consortium, Inc. ("ISC")
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

#include <dhcp/iface_mgr.h>
#include <dhcp_ddns/ncr_udp.h>
#include <dhcpsrv/d2_client_mgr.h>
#include <dhcpsrv/dhcpsrv_log.h>

#include <boost/bind.hpp>

#include <string>

using namespace std;

namespace isc {
namespace dhcp {

D2ClientMgr::D2ClientMgr() : d2_client_config_(new D2ClientConfig()),
    name_change_sender_(), private_io_service_(),
    registered_select_fd_(util::WatchSocket::SOCKET_NOT_VALID) {
    // Default constructor initializes with a disabled configuration.
}

D2ClientMgr::~D2ClientMgr(){
    stopSender();
}

void
D2ClientMgr::suspendUpdates() {
    if (ddnsEnabled()) {
        /// @todo For now we will disable updates and stop sending.
        /// This at least provides a means to shut it off if there are errors.
        LOG_WARN(dhcpsrv_logger, DHCPSRV_DHCP_DDNS_SUSPEND_UPDATES);
        d2_client_config_->enableUpdates(false);
        if (name_change_sender_) {
            stopSender();
        }
    }
}

void
D2ClientMgr::setD2ClientConfig(D2ClientConfigPtr& new_config) {
    if (!new_config) {
        isc_throw(D2ClientError,
                  "D2ClientMgr cannot set DHCP-DDNS configuration to NULL.");
    }

    // Don't do anything unless configuration values are actually different.
    if (*d2_client_config_ != *new_config) {
        // Make sure we stop sending first.
        stopSender();
        if (!new_config->getEnableUpdates()) {
            // Updating has been turned off.
            // Destroy current sender (any queued requests are tossed).
            name_change_sender_.reset();
        } else {
            dhcp_ddns::NameChangeSenderPtr new_sender;
            switch (new_config->getNcrProtocol()) {
            case dhcp_ddns::NCR_UDP: {
                // Instantiate a new sender.
                new_sender.reset(new dhcp_ddns::NameChangeUDPSender(
                                                new_config->getSenderIp(),
                                                new_config->getSenderPort(),
                                                new_config->getServerIp(),
                                                new_config->getServerPort(),
                                                new_config->getNcrFormat(),
                                                *this,
                                                new_config->getMaxQueueSize()));
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
        if (!d2_client_config_->getEnableUpdates()) {
            server_s = false;
            server_n = true;
        } else {
            // If updates are enabled and we are overriding client delegation
            // then S flag should be true.  N-flag should be false.
            server_s = d2_client_config_->getOverrideClientUpdate();
            server_n = false;
        }
        break;

    case 1:
        server_s = d2_client_config_->getEnableUpdates();
        server_n = !server_s;
        break;

    case 2:
        // If updates are enabled and we are overriding "no updates" then
        // S flag should be true.
        server_s = (d2_client_config_->getEnableUpdates() &&
                    d2_client_config_->getOverrideNoUpdate());
        server_n = !server_s;
        break;

    default:
        // RFCs declare this an invalid combination.
        isc_throw(isc::BadValue,
                  "Invalid client FQDN - N and S cannot both be 1");
        break;
    }
}

std::string
D2ClientMgr::generateFqdn(const asiolink::IOAddress& address,
                          const bool trailing_dot) const {
    std::string hostname = address.toText();
    std::replace(hostname.begin(), hostname.end(),
                 (address.isV4() ? '.' : ':'), '-');

    std::ostringstream gen_name;
    gen_name << d2_client_config_->getGeneratedPrefix() << "-" << hostname;
    return (qualifyName(gen_name.str(), trailing_dot));
}


std::string
D2ClientMgr::qualifyName(const std::string& partial_name,
                         const bool trailing_dot) const {
    std::ostringstream gen_name;

    gen_name << partial_name;
    if (!d2_client_config_->getQualifyingSuffix().empty()) {
        std::string str = gen_name.str();
        size_t len = str.length();
        if ((len > 0) && (str[len - 1] != '.')) {
            gen_name << ".";
        }

        gen_name << d2_client_config_->getQualifyingSuffix();
    }

    std::string str = gen_name.str();
    size_t len = str.length();

    if (trailing_dot) {
        // If trailing dot should be added but there is no trailing dot,
        // append it.
        if ((len > 0) && (str[len - 1] != '.')) {
            gen_name << ".";
        }

    } else {
        // If the trailing dot should not be appended but it is present,
        // remove it.
        if ((len > 0) && (str[len - 1] == '.')) {
            gen_name.str(str.substr(0,len-1));
        }

    }

    return (gen_name.str());
}

void
D2ClientMgr::startSender(D2ClientErrorHandler error_handler) {
    if (amSending()) {
        return;
    }

    // Create a our own service instance when we are not being multiplexed
    // into an external service..
    private_io_service_.reset(new asiolink::IOService());
    startSender(error_handler, *private_io_service_);
    LOG_INFO(dhcpsrv_logger, DHCPSRV_DHCP_DDNS_SENDER_STARTED)
             .arg(d2_client_config_->toText());
}

void
D2ClientMgr::startSender(D2ClientErrorHandler error_handler,
                         isc::asiolink::IOService& io_service) {
    if (amSending()) {
        return;
    }

    if (!name_change_sender_)  {
        isc_throw(D2ClientError, "D2ClientMgr::startSender sender is null");
    }

    if (!error_handler) {
        isc_throw(D2ClientError, "D2ClientMgr::startSender handler is null");
    }

    // Set the error handler.
    client_error_handler_ = error_handler;

    // Start the sender on the given service.
    name_change_sender_->startSending(io_service);

    // Register sender's select-fd with IfaceMgr.
    // We need to remember the fd that is registered so we can unregister later.
    // IO error handling in the sender may alter its select-fd.
    registered_select_fd_ = name_change_sender_->getSelectFd();
    IfaceMgr::instance().addExternalSocket(registered_select_fd_,
                                           boost::bind(&D2ClientMgr::runReadyIO,
                                                       this));
}

bool
D2ClientMgr::amSending() const {
    return (name_change_sender_ && name_change_sender_->amSending());
}

void
D2ClientMgr::stopSender() {
    /// Unregister sender's select-fd.
    if (registered_select_fd_ != util::WatchSocket::SOCKET_NOT_VALID) {
        IfaceMgr::instance().deleteExternalSocket(registered_select_fd_);
        registered_select_fd_ = util::WatchSocket::SOCKET_NOT_VALID;
    }

    // If its not null, call stop.
    if (amSending()) {
        name_change_sender_->stopSending();
        LOG_INFO(dhcpsrv_logger, DHCPSRV_DHCP_DDNS_SENDER_STOPPED);
    }
}

void
D2ClientMgr::sendRequest(dhcp_ddns::NameChangeRequestPtr& ncr) {
    if (!amSending()) {
        // This is programmatic error so bust them for it.
        isc_throw(D2ClientError, "D2ClientMgr::sendRequest not in send mode");
    }

    try {
        name_change_sender_->sendRequest(ncr);
    } catch (const std::exception& ex) {
        LOG_ERROR(dhcpsrv_logger, DHCPSRV_DHCP_DDNS_NCR_REJECTED)
                  .arg(ex.what()).arg((ncr ? ncr->toText() : " NULL "));
        invokeClientErrorHandler(dhcp_ddns::NameChangeSender::ERROR, ncr);
    }
}

void
D2ClientMgr::invokeClientErrorHandler(const dhcp_ddns::NameChangeSender::
                                      Result result,
                                      dhcp_ddns::NameChangeRequestPtr& ncr) {
    // Handler is mandatory to enter send mode but test it just to be safe.
    if (!client_error_handler_) {
        LOG_ERROR(dhcpsrv_logger, DHCPSRV_DHCP_DDNS_HANDLER_NULL);
    } else {
        // Handler is not supposed to throw, but catch just in case.
        try {
            (client_error_handler_)(result, ncr);
        } catch (const std::exception& ex) {
            LOG_ERROR(dhcpsrv_logger, DHCPSRV_DHCP_DDNS_ERROR_EXCEPTION)
                      .arg(ex.what());
        }
    }
}

size_t
D2ClientMgr::getQueueSize() const {
    if (!name_change_sender_) {
        isc_throw(D2ClientError, "D2ClientMgr::getQueueSize sender is null");
    }

    return(name_change_sender_->getQueueSize());
}

size_t
D2ClientMgr::getQueueMaxSize() const {
    if (!name_change_sender_) {
        isc_throw(D2ClientError, "D2ClientMgr::getQueueMaxSize sender is null");
    }

    return(name_change_sender_->getQueueMaxSize());
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
        invokeClientErrorHandler(result, ncr);
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
    if (!name_change_sender_) {
        // This should never happen.
        isc_throw(D2ClientError, "D2ClientMgr::runReadyIO"
                  " name_change_sender is null");
    }

    name_change_sender_->runReadyIO();
}

};  // namespace dhcp

};  // namespace isc
