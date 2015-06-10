// Copyright (C) 2012-2014 Internet Systems Consortium, Inc. ("ISC")
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

#include <asiolink/asiolink.h>
#include <cc/data.h>
#include <cc/session.h>
#include <cc/command_interpreter.h>
#include <dhcp/iface_mgr.h>
#include <dhcp4/json_config_parser.h>
#include <dhcp4/ctrl_dhcp4_srv.h>
#include <dhcp4/dhcp4_log.h>
#include <dhcp4/spec_config.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/dhcp_config_parser.h>
#include <exceptions/exceptions.h>
#include <hooks/hooks_manager.h>
#include <util/buffer.h>

#include <cassert>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace isc::asiolink;
using namespace isc::cc;
using namespace isc::config;
using namespace isc::data;
using namespace isc::dhcp;
using namespace isc::hooks;
using namespace isc::log;
using namespace isc::util;
using namespace std;

namespace isc {
namespace dhcp {

/// @brief Helper session object that represents raw connection to msgq.
isc::cc::Session* cc_session_ = NULL;

/// @brief Session that receives configuration and commands
isc::config::ModuleCCSession* config_session_ = NULL;

/// @brief A dummy configuration handler that always returns success.
///
/// This configuration handler does not perform configuration
/// parsing and always returns success. A dummy handler should
/// be installed using \ref isc::config::ModuleCCSession ctor
/// to get the initial configuration. This initial configuration
/// comprises values for only those elements that were modified
/// the previous session. The \ref dhcp4ConfigHandler can't be
/// used to parse the initial configuration because it needs the
/// full configuration to satisfy dependencies between the
/// various configuration values. Installing the dummy handler
/// that guarantees to return success causes initial configuration
/// to be stored for the session being created and that it can
/// be later accessed with
/// \ref isc::config::ConfigData::getFullConfig().
///
/// @param new_config new configuration.
///
/// @return success configuration status.
ConstElementPtr
dhcp4StubConfigHandler(ConstElementPtr) {
    // This configuration handler is intended to be used only
    // when the initial configuration comes in. To receive this
    // configuration a pointer to this handler must be passed
    // using ModuleCCSession constructor. This constructor will
    // invoke the handler and will store the configuration for
    // the configuration session when the handler returns success.
    // Since this configuration is partial we just pretend to
    // parse it and always return success. The function that
    // initiates the session must get the configuration on its
    // own using getFullConfig.
    return (isc::config::createAnswer(0, "Configuration accepted."));
}

ConstElementPtr
bundyConfigHandler(ConstElementPtr new_config) {
    if (!ControlledDhcpv4Srv::getInstance() || !config_session_) {
        // That should never happen as we install config_handler
        // after we instantiate the server.
        ConstElementPtr answer =
            isc::config::createAnswer(1, "Configuration rejected,"
                                      " server is during startup/shutdown phase.");
        return (answer);
    }

    // The configuration passed to this handler function is partial.
    // In other words, it just includes the values being modified.
    // In the same time, there are dependencies between various
    // DHCP configuration parsers. For example: the option value can
    // be set if the definition of this option is set. If someone removes
    // an existing option definition then the partial configuration that
    // removes that definition is triggered while a relevant option value
    // may remain configured. This eventually results in the DHCP server
    // configuration being in the inconsistent state.
    // In order to work around this problem we need to merge the new
    // configuration with the existing (full) configuration.

    // Let's create a new object that will hold the merged configuration.
    boost::shared_ptr<MapElement> merged_config(new MapElement());
    // Let's get the existing configuration.
    ConstElementPtr full_config = config_session_->getFullConfig();
    // The full_config and merged_config should be always non-NULL
    // but to provide some level of exception safety we check that they
    // really are (in case we go out of memory).
    if (full_config && merged_config) {
        merged_config->setValue(full_config->mapValue());

        // Merge an existing and new configuration.
        isc::data::merge(merged_config, new_config);
        LOG_DEBUG(dhcp4_logger, DBG_DHCP4_COMMAND, DHCP4_CONFIG_UPDATE)
            .arg(full_config->str());
    }

    // Configure the server.
    return (ControlledDhcpv4Srv::processConfig(merged_config));
}




void ControlledDhcpv4Srv::init(const std::string& config_file) {
    // Call base class's init.
    Daemon::init(config_file);

    string specfile;
    if (getenv("KEA_FROM_BUILD")) {
        specfile = string(getenv("KEA_FROM_BUILD")) +
            "/src/bin/dhcp4/dhcp4.spec";
    } else {
        specfile = string(DHCP4_SPECFILE_LOCATION);
    }

    /// @todo: Check if session is not established already. Throw, if it is.

    LOG_DEBUG(dhcp4_logger, DBG_DHCP4_START, DHCP4_CCSESSION_STARTING)
              .arg(specfile);
    cc_session_ = new Session(io_service_.get_io_service());
    // Create a session with the dummy configuration handler.
    // Dumy configuration handler is internally invoked by the
    // constructor and on success the constructor updates
    // the current session with the configuration that had been
    // committed in the previous session. If we did not install
    // the dummy handler, the previous configuration would have
    // been lost.
    config_session_ = new ModuleCCSession(specfile, *cc_session_,
                                          dhcp4StubConfigHandler,
                                          processCommand, false);
    config_session_->start();

    // We initially create ModuleCCSession() without configHandler, as
    // the session module is too eager to send partial configuration.
    // We want to get the full configuration, so we explicitly call
    // getFullConfig() and then pass it to our configHandler.
    config_session_->setConfigHandler(bundyConfigHandler);

    try {
        configureDhcp4Server(*this, config_session_->getFullConfig());

        // Server will start DDNS communications if its enabled.
        server_->startD2();

        // Configuration may disable or enable interfaces so we have to
        // reopen sockets according to new configuration.
        CfgMgr::instance().getCurrentCfg()->cfg_iface_
            .openSockets(getPort(), useBroadcast());

    } catch (const std::exception& ex) {
        LOG_ERROR(dhcp4_logger, DHCP4_CONFIG_LOAD_FAIL).arg(ex.what());

    }

    /// Integrate the asynchronous I/O model of former BIND 10/Bundy
    /// configuration control with the "select" model of the DHCP server.
    /// This is fully explained in \ref dhcpv4Session.
    int ctrl_socket = cc_session_->getSocketDesc();
    LOG_DEBUG(dhcp4_logger, DBG_DHCP4_START, DHCP4_CCSESSION_STARTED)
              .arg(ctrl_socket);
    IfaceMgr::instance().addExternalSocket(ctrl_socket, sessionReader);
}


void ControlledDhcpv4Srv::cleanup() {
    if (config_session_) {
        delete config_session_;
        config_session_ = NULL;
    }
    if (cc_session_) {

        int ctrl_socket = cc_session_->getSocketDesc();
        cc_session_->disconnect();

        IfaceMgr::instance().deleteExternalSocket(ctrl_socket);
        delete cc_session_;
        cc_session_ = NULL;
    }
}

};
};
