// Copyright (C) 2018-2021 Internet Systems Consortium, Inc. ("ISC")
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

#include <sysrepo-cpp/Session.hpp>

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
    /// @brief Destructor (call clear).
    virtual ~NetconfAgent();

    /// @brief Initialize sysrepo sessions.
    ///
    /// Must be called before init. Collect the list of available
    /// modules with their revisions.
    void initSysrepo();

    /// @brief Initialization.
    ///
    /// Check available modules / revisions.
    /// Get and display Kea server configurations.
    /// Load Kea server configurations from YANG datastore.
    /// Subscribe configuration changes in YANG datastore.
    ///
    /// @param cfg_mgr The configuration manager (can be null).
    void init(NetconfCfgMgrPtr cfg_mgr);

    /// @brief Clear.
    ///
    /// Close subscriptions and sysrepo.
    void clear();

    /// @brief SR_EV_CHANGE callback.
    ///
    /// Validate YANG datastore changes using Kea configuration test.
    ///
    /// @param sess The sysrepo running datastore session.
    /// @param service_pair The service name and configuration pair.
    /// @return return code for sysrepo.
    static sr_error_t
    change(sysrepo::S_Session sess, const CfgServersMapPair& service_pair);

    /// @brief SR_EV_DONE callback.
    ///
    /// Get notified that a Kea configuration has been written to the YANG
    /// datastore.
    ///
    /// @param sess The sysrepo running datastore session.
    /// @param service_pair The service name and configuration pair.
    /// @return return code for sysrepo.
    static sr_error_t
    done(sysrepo::S_Session sess, const CfgServersMapPair& service_pair);

    /// @brief Log changes.
    ///
    /// Iterate on changes logging them. Sysrepo changes are an operation
    /// (created, modified, deleted or moved) with old and new values
    /// (cf sr_change_oper_e sysrepo documentation).
    ///
    /// @param sess The sysrepo running datastore session.
    /// @param model The model name.
    static void logChanges(sysrepo::S_Session sess, const std::string& model);

protected:
    /// @brief Get and display Kea server configuration.
    ///
    /// Retrieves current configuration via control socket (unix or http)
    /// from a running Kea server. If boot-update is set to false, this
    /// operation is a no-op.
    ///
    /// @param service_pair The service name and configuration pair.
    void keaConfig(const CfgServersMapPair& service_pair);

    /// @brief Check essential module availability.
    ///
    /// Emit a fatal error if an essential one (i.e. required in
    /// a further phase) is missing or does not have the expected revision.
    ///
    /// @param module_name The module name.
    /// @return true if available, false if not.
    bool checkModule(const std::string& module_name) const;

    /// @brief Retrieve names and revisions of installed modules through the
    /// sysrepo API.
    ///
    /// @throw Unexpected if module information cannot be retrieved from sysrepo
    void getModules();

    /// @brief Check module availability.
    ///
    /// Emit a warning if a module is missing or does not have
    /// the expected revision.
    ///
    /// @param servers the configured servers to check against YANG_REVISIONS.
    /// Is empty by default for when the caller only wants to check
    /// installed modules.
    ///
    /// @throw Unexpected if a module from YANG_REVISIONS is not installed or
    /// has the wrong revision.
    void checkModules(CfgServersMapPtr const& servers = {}) const;

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

    /// @brief Subscribe to notifications for a given YANG module.
    ///
    /// @param service_pair the service name and configuration pair
    void subscribeToNotifications(const CfgServersMapPair& service_pair);

    /// @brief Set the shutdown flag of the process to true so that it can exit
    /// at the earliest convenient time.
    void announceShutdown() const;

    /// @brief Check the shutdown flag of the process.
    bool shouldShutdown() const;

    /// @brief Sysrepo connection.
    sysrepo::S_Connection conn_;

    /// @brief Sysrepo startup datastore session.
    sysrepo::S_Session startup_sess_;

    /// @brief Sysrepo running datastore session.
    sysrepo::S_Session running_sess_;

    /// @brief Available modules and revisions in Sysrepo.
    std::map<const std::string, const std::string> modules_;

    /// @brief Subscription map.
    std::map<const std::string, sysrepo::S_Subscribe> subscriptions_;
};

} // namespace netconf
} // namespace isc

#endif // NETCONF_H
