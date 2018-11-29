// Copyright (C) 2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

/// @file netconf.h

#ifndef NETCONF_H
#define NETCONF_H

#ifndef HAVE_SYSREPO
#error "config.h must be included before netconf.h"
#endif

#include <netconf/netconf_cfg_mgr.h>
#include <netconf/control_socket.h>
#include <netconf/http_control_socket.h>
#include <netconf/stdout_control_socket.h>
#include <netconf/unix_control_socket.h>
#ifndef HAVE_PRE_0_7_6_SYSREPO
#include <sysrepo-cpp/Session.hpp>
#else
#include <sysrepo-cpp/Session.h>
#endif
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
#ifndef HAVE_PRE_0_7_6_SYSREPO
    static int validate(sysrepo::S_Session sess,
                        const CfgServersMapPair& service_pair);
#else
    static int validate(S_Session sess, const CfgServersMapPair& service_pair);
#endif

    /// @brief Update.
    ///
    /// Update a Kea configuration from YANG datastore changes.
    ///
    /// @param sess The sysrepo running datastore session.
    /// @param service_pair The service name and configuration pair.
    /// @return return code for sysrepo.
#ifndef HAVE_PRE_0_7_6_SYSREPO
    static int update(sysrepo::S_Session sess,
                      const CfgServersMapPair& service_pair);
#else
    static int update(S_Session sess, const CfgServersMapPair& service_pair);
#endif

    /// @brief Log changes.
    ///
    /// Iterate on changes logging them. Sysrepo changes are an operation
    /// (created, modified, deleted or moved) with old and new values
    /// (cf sr_change_oper_e sysrepo documentation).
    ///
    /// @param sess The sysrepo running datastore session.
    /// @param model The model name.
#ifndef HAVE_PRE_0_7_6_SYSREPO
    static void logChanges(sysrepo::S_Session sess, const std::string& model);
#else
    static void logChanges(S_Session sess, const std::string& model);
#endif

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
#ifndef HAVE_PRE_0_7_6_SYSREPO
    sysrepo::S_Connection conn_;
#else
    S_Connection conn_;
#endif

    /// @brief Sysrepo startup datastore session.
#ifndef HAVE_PRE_0_7_6_SYSREPO
    sysrepo::S_Session startup_sess_;
#else
    S_Session startup_sess_;
#endif

    /// @brief Sysrepo running datastore session.
#ifndef HAVE_PRE_0_7_6_SYSREPO
    sysrepo::S_Session running_sess_;
#else
    S_Session running_sess_;
#endif

    /// @brief Subscription map.
#ifndef HAVE_PRE_0_7_6_SYSREPO
    std::map<const std::string, sysrepo::S_Subscribe> subscriptions_;
#else
    std::map<const std::string, S_Subscribe> subscriptions_;
#endif
};

} // namespace netconf
} // namespace isc

#endif // NETCONF_H
