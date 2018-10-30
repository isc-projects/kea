// Copyright (C) 2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

/// @file netconf.h

#ifndef NETCONF_H
#define NETCONF_H

#include <netconf/netconf_cfg_mgr.h>
#include <netconf/control_socket.h>
#include <netconf/http_control_socket.h>
#include <netconf/stdout_control_socket.h>
#include <netconf/unix_control_socket.h>
#include <sysrepo-cpp/Session.h>
#include <map>

namespace isc {
namespace netconf {

/// @brief Forward declaration to the @c NetconfAgent.
class NetconfAgent;

/// @brief Type definition for the pointer to the @c NetconfAgent.
typedef boost::shared_ptr<NetconfAgent> NetconfAgentPtr;

/// @brief Netconf agent.
///
/// Service performed by the Netconf agent:
///  - at boot get and display Kea server configurations.
///  - load Kea server configurations from YANG datastore.
///  - validate YANG datastore changes using Kea configuration test.
///  - load updated Kea server configurations from YANG datastore.
///  - on shutdown close subscriptions.
class NetconfAgent {
public:
    /// @brief Constructor.
    NetconfAgent();

    /// @brief Destructor (call clear).
    virtual ~NetconfAgent();

    /// @brief Initialize sysrepo sessions.
    ///
    /// Must be called before init.
    void initSysrepo();

    /// @brief Initialization.
    ///
    /// Get and display Kea server configurations.
    /// Load Kea server configurations from YANG datastore.
    /// Subscribe configuration changes in YANG datastore.
    ///
    /// If @c NetconfProcess::global_shut_down_flag becomes true
    /// returns as soon as possible.
    ///
    /// @param cfg_mgr The configuration manager (can be null).
    void init(NetconfCfgMgrPtr cfg_mgr);

    /// @brief Clear.
    ///
    /// Close subscriptions and sysrepo.
    void clear();

    /// @brief Validate.
    ///
    /// Validate YANG datastore changes using Kea configuration test.
    ///
    /// @param sess The sysrepo running datastore session.
    /// @param service_pair The service name and configuration pair.
    /// @return return code for sysrepo.
    static int validate(S_Session sess, const CfgServersMapPair& service_pair);

    /// @brief Update.
    ///
    /// Update a Kea configuration from YANG datastore changes.
    ///
    /// @param sess The sysrepo running datastore session.
    /// @param service_pair The service name and configuration pair.
    /// @return return code for sysrepo.
    static int update(S_Session sess, const CfgServersMapPair& service_pair);

    /// @brief Print changes.
    ///
    /// @param sess The sysrepo running datastore session.
    /// @param model The model name.
    static void logChanges(S_Session sess, const std::string& model);

    /// @brief Cancel flag.
    bool cancel_;

protected:
    /// @brief Get and display Kea server configuration.
    ///
    /// Retrieves current configuration via control socket (unix or http)
    /// from a running Kea server. If boot-update is set to false, this
    /// operation is a no-op.
    ///
    /// @param service_pair The service name and configuration pair.
    void keaConfig(const CfgServersMapPair& service_pair);

    /// @brief Retrieve Kea server configuration from the YANG startup
    ///        datastore and applies it to servers.
    ///
    /// This method retrieves the configuation from sysrepo first, then
    /// established control socket connection to Kea servers (currently
    /// dhcp4 and/or dhcp6) and then attempts to send configuration
    /// using config-set.
    ///
    /// If boot-update is set to false, this operation is a no-op.
    ///
    /// @param service_pair The service name and configuration pair.
    void yangConfig(const CfgServersMapPair& service_pair);

    /// @brief Subscribe changes for a module in YANG datastore.
    ///
    /// @param service_pair The service name and configuration pair.
    void subscribeConfig(const CfgServersMapPair& service_pair);

    /// @brief Sysrepo connection.
    S_Connection conn_;

    /// @brief Sysrepo startup datastore session.
    S_Session startup_sess_;

    /// @brief Sysrepo running datastore session.
    S_Session running_sess_;

    /// @brief Subscription map.
    std::map<const std::string, S_Subscribe> subscriptions_;
};

} // namespace netconf
} // namespace isc

#endif // NETCONF_H
