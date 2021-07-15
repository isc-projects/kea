// Copyright (C) 2018-2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef NETCONF_CFG_MGR_H
#define NETCONF_CFG_MGR_H

#include <cc/data.h>
#include <hooks/hooks_config.h>
#include <process/d_cfg_mgr.h>
#include <netconf/netconf_config.h>
#include <boost/pointer_cast.hpp>
#include <map>
#include <string>

namespace isc {
namespace netconf {

class NetconfConfig;
/// @brief Pointer to a configuration context.
typedef boost::shared_ptr<NetconfConfig> NetconfConfigPtr;

/// @brief Netconf Configuration Context.
///
/// Implement the storage container for configuration context.
/// It provides a single enclosure for the storage of configuration parameters
/// and any other Netconf specific information that needs to be accessible
/// during configuration parsing as well as to the application as a whole.
/// It is derived from the context base class, ConfigBase.
class NetconfConfig : public process::ConfigBase {
public:

    /// @brief Default constructor
    NetconfConfig();

    /// @brief Returns pointer to configured global parameters.
    ///
    /// @todo revisit this at the toElement first use.
    isc::data::ConstElementPtr getConfiguredGlobals() const {
        return (isc::data::ConstElementPtr(configured_globals_));
    }

    /// @brief Saves scalar elements from the global scope of a configuration.
    void extractConfiguredGlobals(isc::data::ConstElementPtr config);

    /// @brief Adds a parameter to the collection configured globals.
    ///
    /// @param name std::string name of the global to add.
    /// @param value ElementPtr containing the value of the global.
    void addConfiguredGlobal(const std::string& name,
                             isc::data::ConstElementPtr value) {
        configured_globals_->set(name, value);
    }

    /// @brief Returns non-const reference to the managed servers map.
    ///
    /// @return non-const reference to the managed servers map.
    CfgServersMapPtr& getCfgServersMap() {
        return (servers_map_);
    }

    /// @brief Returns const reference to the managed servers map.
    ///
    /// @return const reference to the managed servers map.
    const CfgServersMapPtr& getCfgServersMap() const {
        return (servers_map_);
    }

    /// @brief Returns non-const reference to configured hooks libraries.
    ///
    /// @return non-const reference to configured hooks libraries.
    isc::hooks::HooksConfig& getHooksConfig() {
        return (hooks_config_);
    }

    /// @brief Returns const reference to configured hooks libraries.
    ///
    /// @return const reference to configured hooks libraries.
    const isc::hooks::HooksConfig& getHooksConfig() const {
        return (hooks_config_);
    }

    /// @brief Unparse a configuration object
    ///
    /// Returns an element which must parse into the same object, i.e.
    /// @code
    /// for all valid config C parse(parse(C)->toElement()) == parse(C)
    /// @endcode
    ///
    /// @return a pointer to a configuration which can be parsed into
    /// the initial configuration object
    virtual isc::data::ElementPtr toElement() const;

private:

    /// @brief Private copy constructor
    ///
    /// It is private to forbid anyone outside of this class to make copies.
    ///
    /// @param orig the original context to copy from
    NetconfConfig(const NetconfConfig& orig);

    /// @brief Private assignment operator to avoid potential for slicing.
    ///
    /// @param rhs Context to be assigned.
    NetconfConfig& operator=(const NetconfConfig& rhs);

    /// @brief Stores the global parameters specified via configuration.
    isc::data::ElementPtr configured_globals_;

    /// @brief CfgServers map.
    CfgServersMapPtr servers_map_;

    /// @brief Configured hooks libraries.
    isc::hooks::HooksConfig hooks_config_;
};

/// @brief Ctrl Netconf Configuration Manager.
///
/// Provides the mechanisms for managing the Netconf application's
/// configuration.
class NetconfCfgMgr : public process::DCfgMgrBase {
public:

    /// @brief Constructor.
    NetconfCfgMgr();

    /// @brief Destructor
    virtual ~NetconfCfgMgr() = default;

    /// @brief Convenience method that returns the Netconf configuration
    /// context.
    ///
    /// @return returns a pointer to the configuration context.
    NetconfConfigPtr getNetconfConfig() {
        return (boost::dynamic_pointer_cast<NetconfConfig>(getContext()));
    }

    /// @brief Returns configuration summary in the textual format.
    ///
    /// @param selection Bitfield which describes the parts of the configuration
    /// to be returned. This parameter is ignored for Netconf.
    ///
    /// @return Summary of the configuration in the textual format.
    virtual std::string getConfigSummary(const uint32_t selection);

    /// @brief Return a list of all paths that contain passwords or secrets for
    /// kea-netconf.
    ///
    /// @return the list of lists of sequential JSON map keys needed to reach
    /// the passwords and secrets.
    std::list<std::list<std::string>> jsonPathsToRedact() const;

protected:

    /// @brief Parses configuration of Netconf.
    ///
    /// @param config Pointer to a configuration specified for netconf.
    /// @param check_only Boolean flag indicating if this method should
    /// only verify correctness of the provided configuration.
    /// @return Pointer to a result of configuration parsing.
    virtual isc::data::ConstElementPtr
    parse(isc::data::ConstElementPtr config, bool check_only);

    /// @brief Creates a new, blank NetconfConfig context.
    ///
    ///
    /// This method is used at the beginning of configuration process to
    /// create a fresh, empty copy of a NetconfConfig. This new context
    /// will be populated during the configuration process and will replace the
    /// existing context provided the configuration process completes without
    /// error.
    ///
    /// @return Returns a ConfigPtr to the new context instance.
    virtual process::ConfigPtr createNewContext();
};

/// @brief Defines a shared pointer to NetconfCfgMgr.
typedef boost::shared_ptr<NetconfCfgMgr> NetconfCfgMgrPtr;

} // namespace isc::netconf
} // namespace isc

#endif // NETCONF_CFG_MGR_H
