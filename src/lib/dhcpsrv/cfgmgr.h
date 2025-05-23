// Copyright (C) 2012-2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef CFGMGR_H
#define CFGMGR_H

#include <asiolink/io_address.h>
#include <dhcp/option.h>
#include <dhcp/option_space.h>
#include <dhcp/classify.h>
#include <dhcpsrv/d2_client_mgr.h>
#include <dhcpsrv/pool.h>
#include <dhcpsrv/srv_config.h>
#include <util/buffer.h>
#include <util/filesystem.h>
#include <util/optional.h>

#include <boost/shared_ptr.hpp>
#include <boost/noncopyable.hpp>

#include <map>
#include <string>
#include <vector>
#include <list>

namespace isc {
namespace dhcp {

/// @brief Exception thrown when the same interface has been specified twice.
///
/// In particular, this exception is thrown when adding interface to the set
/// of interfaces on which server is supposed to listen.
class DuplicateListeningIface : public Exception {
public:
    DuplicateListeningIface(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) { }
};

/// @brief Configuration Manager
///
/// This singleton class holds the whole configuration for DHCPv4 and DHCPv6
/// servers.
///
/// Below is a sketch of configuration inheritance.
/// Let's investigate the following configuration:
///
/// @code
/// preferred-lifetime 500;
/// valid-lifetime 1000;
/// subnet6 2001:db8:1::/48 {
///     pool6 2001::db8:1::1 - 2001::db8:1::ff;
/// };
/// subnet6 2001:db8:2::/48 {
///     valid-lifetime 2000;
///     pool6 2001::db8:2::1 - 2001::db8:2::ff;
/// };
/// @endcode
///
/// Parameters defined in a global scope are applicable to everything until
/// they are overwritten in a smaller scope, in this case subnet6.
/// In the example above, the first subnet6 has preferred lifetime of 500s
/// and a valid lifetime of 1000s. The second subnet has preferred lifetime
/// of 500s, but valid lifetime of 2000s.
///
/// Parameter inheritance is implemented in dedicated classes. See
/// @ref isc::dhcp::SimpleParser4::deriveParameters and
/// @ref isc::dhcp::SimpleParser6::deriveParameters.
class CfgMgr : public boost::noncopyable {
public:
    /// @brief returns a single instance of Configuration Manager
    ///
    /// CfgMgr is a singleton and this method is the only way of
    /// accessing it.
    static CfgMgr& instance();

    /// @brief Fetches the supported DHCP data directory.
    ///
    /// The first call to this function with no arguments will set the default
    /// hooks path to either the value of DHCP_DATA_DIR or the environment
    /// variable KEA_DHCP_DATA_DIR if it is defined.  Subsequent calls with no
    /// arguments will simply return this value.
    ///
    /// @param reset recalculate when true, defaults to false. This is for
    /// testing purposes only.
    /// @param explicit_path set default hooks path to this value. This is
    /// for testing purposes only.
    ///
    /// @return String containing the default data directory.
    std::string getDataDir(bool reset = false,
                           const std::string explicit_path = "");

    /// @brief Validates a file path against the supported directory for DHDP data.
    ///
    /// @param data_path data path to validate.
    ///
    /// @return validated path
    std::string validatePath(const std::string data_path) const;

    /// @brief Updates the DHCP-DDNS client configuration to the given value.
    ///
    /// Passes the new configuration to the D2ClientMgr instance,
    /// d2_client_mgr_, which will attempt to apply the new configuration
    /// by shutting down its sender and opening a new connection per the new
    /// configuration (see @c D2ClientMgr::setD2ClientConfig()).
    ///
    /// @param new_config pointer to the new client configuration.
    ///
    /// @throw Underlying method(s) will throw D2ClientError if given an empty
    /// pointer.
    void setD2ClientConfig(D2ClientConfigPtr& new_config);

    /// @brief Convenience method for checking if DHCP-DDNS updates are enabled.
    ///
    /// @return True if the D2 configuration is enabled.
    bool ddnsEnabled();

    /// @brief Fetches the DHCP-DDNS configuration pointer.
    ///
    /// @return a reference to the current configuration pointer.
    const D2ClientConfigPtr& getD2ClientConfig() const;

    /// @brief Fetches the DHCP-DDNS manager.
    ///
    /// @return a reference to the DHCP-DDNS manager.
    D2ClientMgr& getD2ClientMgr();

    /// @name Methods managing the collection of configurations.
    ///
    /// The following methods manage the process of preparing a configuration
    /// without affecting a currently used configuration and then committing
    /// the configuration to replace current configuration atomically.
    ///
    /// @todo Migrate all configuration parameters to use the model supported
    /// by these functions.
    ///
    //@{

    /// @brief Remove current, staging, and external configurations.
    ///
    /// This function removes all configurations, including current,
    /// staging and external configurations. It creates a new current
    /// configuration with default settings.
    ///
    /// This function is exception safe.
    void clear();

    /// @brief Remove staging configuration.
    ///
    /// This function is exception safe.
    void clearStagingConfiguration();

    /// @brief Commits the staging configuration.
    ///
    /// The staging configuration becomes current configuration when this
    /// function is called.
    ///
    /// This function is exception safe.
    void commit();

    /// @brief Returns a pointer to the current configuration.
    ///
    /// This function returns pointer to the current configuration. If the
    /// current configuration is not set it will create a default configuration
    /// and return it.
    ///
    /// In the previous Kea releases this method used to return a const pointer
    /// to the current configuration to ensure that it is not accidentally
    /// modified while the server is running. This has been changed in Kea 1.3
    /// release and now this function returns a non-const pointer. The reason
    /// is that there are certain use cases when current configuration must
    /// be modified without going through a full cycle of server
    /// reconfiguration, e.g. add a subnet to the current configuration as
    /// a result of receiving a command over control API. In such case the
    /// performance of processing such command is critical and rebuilding the
    /// whole configuration just for this small configuration change is out
    /// of question.
    ///
    /// Nevertheless, such configuration updates should always be made with
    /// caution and one has to make sure that the configuration data integrity
    /// is preserved.
    ///
    /// @return Non-null pointer to the current configuration.
    SrvConfigPtr getCurrentCfg();

    /// @brief Returns a pointer to the staging configuration.
    ///
    /// The staging configuration is used by the configuration parsers to
    /// create new configuration. The staging configuration doesn't affect the
    /// server's operation until it is committed. The staging configuration
    /// is a non-const object which can be modified by the caller.
    ///
    /// Multiple consecutive calls to this function return the same object
    /// which can be modified from various places of the code (e.g. various
    /// configuration parsers).
    ///
    /// @return non-null pointer to the staging configuration.
    SrvConfigPtr getStagingCfg();

    /// @brief Creates an external configuration and returns pointer to it.
    ///
    /// External configurations are those that come from other sources than
    /// from the configuration file, e.g. a database or a command. They
    /// are created aside and merged into the staging or current configuration.
    /// External configurations are accessed by their sequence numbers. The
    /// sequence numbers are autogenerated when the external configuration
    /// instance is created.
    ///
    /// @return non-null pointer to created external configuration.
    SrvConfigPtr createExternalCfg();

    /// @brief Merges external configuration with the given sequence number
    /// into the staging configuration.
    ///
    /// After the merge, the source configuration is discarded from the
    /// @c CfgMgr as it should not be used anymore.
    ///
    /// @param seq Source configuration sequence number.
    ///
    /// @throw BadValue if the external configuration with the given sequence
    /// number doesn't exist.
    void mergeIntoStagingCfg(const uint32_t seq);

    /// @brief Merges external configuration with the given sequence number
    /// into the current configuration.
    ///
    /// After the merge, the source configuration is discarded from the
    /// @c CfgMgr as it should not be used anymore.
    ///
    /// @param seq Source configuration sequence number.
    ///
    /// @throw BadValue if the external configuration with the given sequence
    /// number doesn't exist.
    void mergeIntoCurrentCfg(const uint32_t seq);

    //@}

    /// @brief Sets address family (AF_INET or AF_INET6)
    void setFamily(uint16_t family) {
        family_ = family == AF_INET ? AF_INET : AF_INET6;
    }

    /// @brief Returns address family.
    uint16_t getFamily() const {
        return (family_);
    }

    //@}

protected:

    /// @brief Protected constructor.
    ///
    /// This constructor is protected for 2 reasons. First, it forbids any
    /// instantiations of this class (CfgMgr is a singleton). Second, it
    /// allows derived class to instantiate it. That is useful for testing
    /// purposes.
    CfgMgr();

    /// @brief virtual destructor
    virtual ~CfgMgr() = default;

private:
    /// @brief Merges external configuration with the given sequence number
    /// into the specified configuration.
    ///
    /// @param target_config Pointer to the configuration into which the
    /// external configuration should be merged.
    /// @param seq Source configuration sequence number.
    void mergeIntoCfg(const SrvConfigPtr& taget_config, const uint32_t seq);

    /// @brief PathChecker that provides the supported DHCP data directory
    /// where data files (e.g. lease files and server-id) are stored.
    util::file::PathCheckerPtr data_dir_checker_;

    /// @brief Manages the DHCP-DDNS client and its configuration.
    D2ClientMgrPtr d2_client_mgr_;

    /// @brief Current server configuration
    ///
    /// This is a structure that will hold all configuration.
    /// @todo: migrate all other parameters to that structure.
    SrvConfigPtr configuration_;

    /// @brief Staging server configuration
    ///
    /// This is a structure that holds configuration until it is applied.
    SrvConfigPtr staging_configuration_;

    /// @name Map of external configurations.
    ///
    //@{
    /// @brief Server configuration map type.
    typedef std::map<uint32_t, SrvConfigPtr> SrvConfigMap;

    /// @brief Map of external configurations with sequence numbers used
    /// as keys.
    SrvConfigMap external_configs_;
    //@}

    /// @brief Address family.
    uint16_t family_;
};

} // namespace isc::dhcp
} // namespace isc

#endif // CFGMGR_H
