// Copyright (C) 2014-2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef DHCPSRV_CONFIG_H
#define DHCPSRV_CONFIG_H

#include <cc/cfg_to_element.h>
#include <dhcpsrv/cfg_db_access.h>
#include <dhcpsrv/cfg_duid.h>
#include <dhcpsrv/cfg_expiration.h>
#include <dhcpsrv/cfg_globals.h>
#include <dhcpsrv/cfg_host_operations.h>
#include <dhcpsrv/cfg_hosts.h>
#include <dhcpsrv/cfg_iface.h>
#include <dhcpsrv/cfg_option.h>
#include <dhcpsrv/cfg_option_def.h>
#include <dhcpsrv/cfg_rsoo.h>
#include <dhcpsrv/cfg_shared_networks.h>
#include <dhcpsrv/cfg_subnets4.h>
#include <dhcpsrv/cfg_subnets6.h>
#include <dhcpsrv/cfg_mac_source.h>
#include <dhcpsrv/cfg_consistency.h>
#include <dhcpsrv/client_class_def.h>
#include <dhcpsrv/d2_client_cfg.h>
#include <process/config_base.h>
#include <hooks/hooks_config.h>
#include <cc/data.h>
#include <cc/user_context.h>
#include <cc/simple_parser.h>
#include <util/optional.h>
#include <util/strutil.h>

#include <boost/shared_ptr.hpp>
#include <vector>
#include <stdint.h>

namespace isc {
namespace dhcp {

class CfgMgr;

/// @brief Convenience container for conveying DDNS behavioral parameters
/// It is intended to be created per Packet exchange using the selected
/// subnet passed into functions that require them
class DdnsParams {
public:
    /// @brief Default constructor
    DdnsParams() : subnet_(), d2_client_enabled_(false) {};

    /// @brief Constructor for DHPCv4 subnets
    ///
    /// @param subnet Pointer to Subnet4 instance to use for fetching
    /// parameter values (typically this is the selected subnet).
    /// @param d2_client_enabled flag which indicates whether or not
    /// D2Client is enabled (typically the value should come from
    /// global D2Client configuration).
    DdnsParams(const Subnet4Ptr& subnet, bool d2_client_enabled)
        : subnet_(boost::dynamic_pointer_cast<Subnet>(subnet)),
          d2_client_enabled_(d2_client_enabled) {}

    /// @brief Constructor for DHPCv6 subnets
    ///
    /// @param subnet Pointer to Subnet6 instance to use for fetching
    /// parameter values (typically this is the selected subnet).
    /// @param d2_client_enabled flag which indicates whether or not
    /// D2Client is enabled (typically the value should come from
    /// global D2Client configuration).
    DdnsParams(const Subnet6Ptr& subnet, bool d2_client_enabled)
        : subnet_(boost::dynamic_pointer_cast<Subnet>(subnet)),
          d2_client_enabled_(d2_client_enabled) {}

    /// @brief Returns whether or not DHCP DDNS updating is enabled.
    /// The value is the logical AND of d2_client_enabled_ and
    /// the value returned by subnet_'s getDdnsSendUpdates().
    ///
    /// @return True if updates are enabled, false otherwise or if
    /// subnet_ is empty.
    bool getEnableUpdates() const;

    /// @brief Returns whether or not Kea should perform updates, even if
    /// client requested no updates.
    ///
    /// @return The value from the subnet_ or false if subnet_ is empty.
    bool getOverrideNoUpdate() const;

    /// @brief Returns whether or not Kea should perform updates, even if
    /// client requested delegation.
    ///
    /// @return The value from the subnet_ or false if subnet_ is empty.
    bool getOverrideClientUpdate() const;

    /// @brief Returns how Kea should handle the domain-name supplied by
    /// the client.
    ///
    /// @return The value from the subnet_ or RCM_NEVER if subnet_ is empty.
    D2ClientConfig::ReplaceClientNameMode getReplaceClientNameMode() const;

    /// @brief Returns the Prefix Kea should use when generating domain-names.
    ///
    /// @return The value from the subnet_ or an empty string if subnet_ is empty.
    std::string getGeneratedPrefix() const;

    /// @brief Returns the suffix Kea should use when to qualify partial
    /// domain-names.
    ///
    /// @return The value from the subnet_ or an empty string if subnet_ is empty.
    std::string getQualifyingSuffix() const;

    /// @brief Returns the regular expression describing invalid characters
    /// for client hostnames.  If empty, host name scrubbing should not be done.
    ///
    /// @return The value from the subnet_ or an empty string if subnet_ is empty.
    std::string getHostnameCharSet() const;

    /// @brief Returns the string to replace invalid characters when scrubbing
    /// hostnames. Meaningful only if hostname_char_set_ is not empty.
    ///
    /// @return The value from the subnet_ or an empty string if subnet_ is empty.
    std::string getHostnameCharReplacement() const;

    /// @brief Returns a regular expression string sanitizer
    ///
    /// If the value returned by getHostnameCharSet() is not empty, then it is
    /// used in conjunction the value returned by getHostnameCharReplacment()
    /// (which may be empty) to create and return a StringSanitizer instance.
    /// Otherwise it will return an empty pointer.
    ///
    /// @return pointer to the StringSanitizer instance or an empty pointer
    /// @throw BadValue if the compilation fails.
    isc::util::str::StringSanitizerPtr getHostnameSanitizer() const;

    /// @brief Returns whether or not DNS should be updated when leases renew.
    ///
    /// If this is true, DNS should always be updated when leases are
    /// extended (i.e. renewed/rebound) even if the DNS information
    /// has not changed.
    ///
    /// @return True if updates should always be performed.
    bool getUpdateOnRenew() const;

    /// @brief Returns whether or not keah-dhcp-ddns should use conflict resolution
    ///
    /// This value is communicated to D2 via the NCR.  When true, D2 should follow
    /// follow conflict resolution steps described in RFC 4703.  If not, it should
    /// simple add or remove entries.
    ///
    /// @return True if conflict resolution should be used.
    bool getUseConflictResolution() const;

    /// @brief Returns percent of lease lifetime to use for TTL
    ///
    /// This value, if greater than zero, is used to calculate the lease lifetime
    /// passed to D2 in the NCR.  Otherwise the value is calculated per RFC 4702.
    ///
    /// @return TTL percent as an Optional.
    util::Optional<double> getTtlPercent() const;

    /// @brief Returns the subnet-id of the subnet associated with these parameters
    ///
    /// @return value of subnet-id (or 0 if no subnet is associated)
    SubnetID getSubnetId() const {
        if (subnet_) {
            return (subnet_->getID());
        } else {
            return (0);
        }
    }

private:
    /// @brief Subnet from which values should be fetched.
    SubnetPtr subnet_;

    /// @brief Flag indicating whether or not the D2Client is enabled.
    bool d2_client_enabled_;
};

/// @brief Defines a pointer for DdnsParams instances.
typedef boost::shared_ptr<DdnsParams> DdnsParamsPtr;

/// @brief Specifies current DHCP configuration
///
/// @todo Migrate all other configuration parameters from cfgmgr.h here
class SrvConfig : public process::ConfigBase {
public:
    /// @name Constants for selection of parameters returned by @c getConfigSummary
    ///
    //@{
    /// Nothing selected
    static const uint32_t CFGSEL_NONE    = 0x00000000;
    /// Number of IPv4 subnets
    static const uint32_t CFGSEL_SUBNET4 = 0x00000001;
    /// Number of IPv6 subnets
    static const uint32_t CFGSEL_SUBNET6 = 0x00000002;
    /// Number of enabled ifaces
    static const uint32_t CFGSEL_IFACE4  = 0x00000004;
    /// Number of v6 ifaces
    static const uint32_t CFGSEL_IFACE6  = 0x00000008;
    /// DDNS enabled/disabled
    static const uint32_t CFGSEL_DDNS    = 0x00000010;
    /// Number of all subnets
    static const uint32_t CFGSEL_SUBNET  = 0x00000003;
    /// Configured globals
    static const uint32_t CFGSEL_GLOBALS = 0x00000020;
    /// Config control info
    static const uint32_t CFGSEL_CFG_CTL = 0x00000040;
    /// IPv4 related config
    static const uint32_t CFGSEL_ALL4    = 0x00000035;
    /// IPv6 related config
    static const uint32_t CFGSEL_ALL6    = 0x0000003A;
    /// Whole config
    static const uint32_t CFGSEL_ALL     = 0xFFFFFFFF;
    //@}

    /// @brief Default constructor.
    ///
    /// This constructor sets configuration sequence number to 0.
    SrvConfig();

    /// @brief Constructor.
    ///
    /// Sets arbitrary configuration sequence number.
    ///
    /// @param sequence The configuration sequence.
    SrvConfig(const uint32_t sequence);

    /// @brief Returns summary of the configuration in the textual format.
    ///
    /// This method returns the brief text describing the current configuration.
    /// It may be used for logging purposes, e.g. when the new configuration is
    /// committed to notify a user about the changes in configuration.
    ///
    /// @todo Currently this method uses @c CfgMgr accessors to get the
    /// configuration parameters. Once these parameters are migrated from the
    /// @c CfgMgr this method will have to be modified accordingly.
    ///
    /// @todo Implement reporting a summary of interfaces being used for
    /// receiving and sending DHCP messages. This will be implemented with
    /// ticket #3512.
    ///
    /// @param selection Is a bitfield which describes the parts of the
    /// configuration to be returned.
    ///
    /// @return Summary of the configuration in the textual format.
    std::string getConfigSummary(const uint32_t selection) const;

    /// @brief Returns configuration sequence number.
    ///
    /// @return The configuration sequence number.
    uint32_t getSequence() const {
        return (sequence_);
    }

    /// @brief Compares configuration sequence with other sequence.
    ///
    /// This method compares sequence numbers of two configurations for
    /// equality. The sequence numbers are meant to be unique, so if
    /// they are equal it means that they point to the same configuration.
    ///
    /// @param other Configuration which sequence number should be
    /// compared with the sequence number of this configuration.
    ///
    /// @return true if sequence numbers are equal.
    bool sequenceEquals(const SrvConfig& other);

    /// @brief Returns non-const pointer to interface configuration.
    ///
    /// This function returns a non-const pointer to the interface
    /// configuration.
    ///
    /// @return Object representing configuration of interfaces.
    CfgIfacePtr getCfgIface() {
        return (cfg_iface_);
    }

    /// @brief Returns const pointer to interface configuration.
    ///
    /// This function returns a const pointer to the interface
    /// configuration.
    ///
    /// @return Object representing configuration of interfaces.
    ConstCfgIfacePtr getCfgIface() const {
        return (cfg_iface_);
    }

    /// @brief Return pointer to non-const object representing user-defined
    /// option definitions.
    ///
    /// This function returns a pointer to the object which represents the
    /// user defined option definitions grouped by option space name.
    ///
    /// @return Pointer to an object holding option definitions.
    CfgOptionDefPtr getCfgOptionDef() {
        return (cfg_option_def_);
    }

    /// @brief Returns pointer to the const object representing user-defined
    /// option definitions.
    ///
    /// This function returns a pointer to the object which represents the
    /// user defined option definitions grouped by option space name.
    ///
    /// @return Pointer to an object holding option definitions.
    ConstCfgOptionDefPtr getCfgOptionDef() const {
        return (cfg_option_def_);
    }

    /// @brief Returns pointer to the non-const object holding options.
    ///
    /// This method returns a pointer to the object which holds instances
    /// of the options to be returned to the clients belonging to any subnet.
    ///
    /// @return Pointer to the object holding options.
    CfgOptionPtr getCfgOption() {
        return (cfg_option_);
    }

    /// @brief Returns pointer to the const object holding options.
    ///
    /// This method returns a pointer to the object which holds instances
    /// of the options to be returned to the clients belonging to any subnet.
    ///
    /// @return Pointer to the object holding options.
    const ConstCfgOptionPtr getCfgOption() const {
        return (cfg_option_);
    }

    /// @brief Returns pointer to non-const object holding subnets configuration
    /// for DHCPv4.
    ///
    /// @return Pointer to the object holding subnets configuration for DHCPv4.
    CfgSubnets4Ptr getCfgSubnets4() {
        return (cfg_subnets4_);
    }

    /// @brief Returns pointer to non-const object holding configuration of
    /// shared networks in DHCPv4;
    ///
    /// @return Pointer to the object holding shared networks configuration
    /// for DHCPv4.
    CfgSharedNetworks4Ptr getCfgSharedNetworks4() const {
        return (cfg_shared_networks4_);
    }

    /// @brief Returns pointer to non-const object holding configuration of
    /// shared networks in DHCPv6.
    ///
    /// @return Pointer to the object holding shared networks configuration
    /// for DHCPv6.
    CfgSharedNetworks6Ptr getCfgSharedNetworks6() const {
        return (cfg_shared_networks6_);
    }

    /// @brief Returns pointer to const object holding subnets configuration for
    /// DHCPv4.
    ///
    /// @return Pointer to the object holding subnets configuration for DHCPv4.
    ConstCfgSubnets4Ptr getCfgSubnets4() const {
        return (cfg_subnets4_);
    }

    /// @brief Returns pointer to non-const object holding subnets configuration
    /// for DHCPv6.
    ///
    /// @return Pointer to the object holding subnets configuration for DHCPv6.
    CfgSubnets6Ptr getCfgSubnets6() {
        return (cfg_subnets6_);
    }

    /// @brief Returns pointer to const object holding subnets configuration for
    /// DHCPv6.
    ///
    /// @return Pointer to the object holding subnets configuration for DHCPv6.
    ConstCfgSubnets6Ptr getCfgSubnets6() const {
        return (cfg_subnets6_);
    }

    /// @brief Returns pointer to the non-const objects representing host
    /// reservations for different IPv4 and IPv6 subnets.
    ///
    /// @return Pointer to the non-const object holding host reservations.
    CfgHostsPtr getCfgHosts() {
        return (cfg_hosts_);
    }

    /// @brief Returns pointer to the const objects representing host
    /// reservations for different IPv4 and IPv6 subnets.
    ///
    /// @return Pointer to the const object holding host reservations.
    ConstCfgHostsPtr getCfgHosts() const {
        return (cfg_hosts_);
    }

    /// @brief Returns pointer to the non-const object representing
    /// set of RSOO-enabled options.
    ///
    /// @return Pointer to the non-const object holding RSOO-enabled
    /// options.
    CfgRSOOPtr getCfgRSOO() {
        return (cfg_rsoo_);
    }

    /// @brief Returns pointer to the const object representing set
    /// of RSOO-enabled options.
    ///
    /// @return Pointer to the const object holding RSOO-enabled options.
    ConstCfgRSOOPtr getCfgRSOO() const {
        return (cfg_rsoo_);
    }

    /// @brief Returns pointer to the object holding configuration pertaining
    /// to processing expired leases.
    ///
    /// @return Pointer to the object holding configuration pertaining to
    /// processing expired leases.
    CfgExpirationPtr getCfgExpiration() {
        return (cfg_expiration_);
    }

    /// @brief Returns pointer to the const object holding configuration
    /// pertaining to processing expired leases.
    ///
    /// @return Pointer to the const object holding configuration pertaining to
    /// processing expired leases.
    ConstCfgExpirationPtr getCfgExpiration() const {
        return (cfg_expiration_);
    }

    /// @brief Returns pointer to the object holding configuration of the
    /// server identifier.
    ///
    /// @return Pointer to the object holding configuration of the server
    /// identifier.
    CfgDUIDPtr getCfgDUID() {
        return (cfg_duid_);
    }

    /// @brief Returns const pointer to the object holding configuration
    /// of the server identifier.
    ///
    /// @return Const pointer to the object holding configuration of the server
    /// identifier.
    ConstCfgDUIDPtr getCfgDUID() const {
        return (cfg_duid_);
    }

    /// @brief Returns pointer to the object holding configuration of the
    /// lease and host database connection parameters.
    ///
    /// @return Pointer to the object holding configuration of the lease and
    /// host database connection parameters.
    CfgDbAccessPtr getCfgDbAccess() {
        return (cfg_db_access_);
    }

    /// @brief Returns const pointer to the object holding configuration of
    /// the lease and host database connection parameters.
    ///
    /// @return Const pointer to the object holding configuration of the lease
    /// and host database connection parameters.
    ConstCfgDbAccessPtr getCfgDbAccess() const {
        return (cfg_db_access_);
    }

    /// @brief Returns pointer to the object holding general configuration
    /// for host reservations in DHCPv4.
    ///
    /// @return Pointer to the object holding general configuration for host
    /// reservations in DHCPv4.
    CfgHostOperationsPtr getCfgHostOperations4() {
        return (cfg_host_operations4_);
    }

    /// @brief Returns const pointer to the object holding general configuration
    /// for host reservations in DHCPv4.
    ///
    /// @return Const pointer to the object holding general configuration for
    /// host reservations in DHCPv4.
    ConstCfgHostOperationsPtr getCfgHostOperations4() const {
        return (cfg_host_operations4_);
    }

    /// @brief Returns pointer to the object holding general configuration
    /// for host reservations in DHCPv6.
    ///
    /// @return Pointer to the object holding general configuration for host
    /// reservations in DHCPv6.
    CfgHostOperationsPtr getCfgHostOperations6() {
        return (cfg_host_operations6_);
    }

    /// @brief Returns const pointer to the object holding general configuration
    /// for host reservations in DHCPv6.
    ///
    /// @return Const pointer to the object holding general configuration for
    /// host reservations in DHCPv6.
    ConstCfgHostOperationsPtr getCfgHostOperations6() const {
        return (cfg_host_operations6_);
    }

    /// @brief Returns non-const pointer to object holding sanity checks flags
    ///
    /// @return Pointer to object holding sanity checks flags
    CfgConsistencyPtr getConsistency() {
        return (cfg_consist_);
    }

    /// @brief Returns const pointer to object holding sanity checks flags
    ///
    /// @return Const pointer to object holding sanity checks flags
    ConstCfgConsistencyPtr getConsistency() const {
        return (cfg_consist_);
    }

    //@}

    /// @brief Returns non-const reference to an array that stores
    ///        MAC/hardware address sources.
    ///
    /// @return non-const reference to MAC/hardware address sources
    CfgMACSource& getMACSources() {
        return (cfg_mac_source_);
    }

    /// @brief Returns const reference to an array that stores
    ///        MAC/hardware address sources.
    ///
    /// @return const reference to MAC/hardware address sources
    const CfgMACSource& getMACSources() const {
        return (cfg_mac_source_);
    }

    /// @brief Returns information about control socket
    ///
    /// @return pointer to the Element that holds control-socket map
    const isc::data::ConstElementPtr getControlSocketInfo() const {
        return (control_socket_);
    }

    /// @brief Sets information about the control socket
    ///
    /// @param control_socket Element that holds control-socket map
    void setControlSocketInfo(const isc::data::ConstElementPtr& control_socket) {
        control_socket_ = control_socket;
    }

    /// @brief Returns DHCP queue control information
    ///
    /// @return pointer to the DHCP queue control information
    const isc::data::ConstElementPtr getDHCPQueueControl() const {
        return (dhcp_queue_control_);
    }

    /// @brief Sets information about the dhcp queue control
    ///
    /// @param dhcp_queue_control new dhcp queue control information
    void setDHCPQueueControl(const isc::data::ConstElementPtr dhcp_queue_control) {
        dhcp_queue_control_ = dhcp_queue_control;
    }

    /// @brief Returns DHCP multi threading information
    ///
    /// @return pointer to the DHCP multi threading information
    const isc::data::ConstElementPtr getDHCPMultiThreading() const {
        return (dhcp_multi_threading_);
    }

    /// @brief Sets information about the dhcp multi threading
    ///
    /// @param dhcp_multi_threading new dhcp multi threading information
    void setDHCPMultiThreading(const isc::data::ConstElementPtr dhcp_multi_threading) {
        dhcp_multi_threading_ = dhcp_multi_threading;
    }

    /// @brief Returns pointer to the dictionary of global client
    /// class definitions
    ///
    /// @return Pointer to the dictionary of global client class definitions
    ClientClassDictionaryPtr getClientClassDictionary() {
        return (class_dictionary_);
    }

    /// @brief Returns pointer to const dictionary of global client
    /// class definitions
    ///
    /// @return Pointer to const dictionary of global client class definitions
    const ClientClassDictionaryPtr getClientClassDictionary() const {
        return (class_dictionary_);
    }

    /// @brief Sets the client class dictionary
    ///
    /// @param dictionary pointer to the new class dictionary
    void setClientClassDictionary(const ClientClassDictionaryPtr& dictionary) {
        class_dictionary_ = dictionary;
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

    /// @brief Fetches the DDNS parameters for a given DHCPv4 subnet.
    ///
    /// Creates a DdnsParams structure which retain and thereafter
    /// use the given subnet to fetch DDNS behavioral parameters.
    /// The values are fetched with the inheritance scope mode
    /// of Network::ALL.
    ///
    /// @param subnet DHCPv4 Subnet for which DDNS parameters are desired.
    /// @return pointer to DddnParams instance
    DdnsParamsPtr getDdnsParams(const Subnet4Ptr& subnet) const;

    /// @brief Fetches the DDNS parameters for a given DHCPv6 subnet.
    ///
    /// Creates a DdnsParams structure which retain and thereafter
    /// use the given subnet to fetch DDNS behavioral parameters.
    /// The values are fetched with the inheritance scope mode
    /// of Network::ALL.
    ///
    /// @param subnet DHCPv6 Subnet for which DDNS parameters are desired.
    /// @return pointer to DddnParams instance
    DdnsParamsPtr getDdnsParams(const Subnet6Ptr& subnet) const;

    /// @brief Copies the current configuration to a new configuration.
    ///
    /// This method copies the parameters stored in the configuration to
    /// an object passed as parameter. The configuration sequence is not
    /// copied.
    ///
    /// @warning Some of the configuration objects are not copied at
    /// this point, e.g. subnets. This is because they contain quite complex
    /// data structures and they make use of pointers, so in many cases
    /// the default copy constructors can't be used. Implementing this
    /// requires quite a lot of time so this is left as is for now.
    /// The lack of ability to copy the entire configuration makes
    /// revert function of the @c CfgMgr unusable.
    ///
    /// @param [out] new_config An object to which the configuration will
    /// be copied.
    void copy(SrvConfig& new_config) const;

    /// @name Methods and operators used to compare configurations.
    ///
    //@{
    ///
    /// @brief Compares two objects for equality.
    ///
    /// It ignores the configuration sequence number when checking for
    /// equality of objects.
    ///
    /// @param other An object to be compared with this object.
    ///
    /// @return true if two objects are equal, false otherwise.
    bool equals(const SrvConfig& other) const;

    /// @brief Compares two objects for inequality.
    ///
    /// It ignores the configuration sequence number when checking for
    /// inequality of objects.
    ///
    /// @param other An object to be compared with this object.
    ///
    /// @return true if two objects are not equal, false otherwise.
    bool nequals(const SrvConfig& other) const {
        return (!equals(other));
    }

    /// @brief Equality operator.
    ///
    /// It ignores the configuration sequence number when checking for
    /// equality of objects.
    ///
    /// @param other An object to be compared with this object.
    ///
    /// @return true if two objects are equal, false otherwise.
    bool operator==(const SrvConfig& other) const {
        return (equals(other));
    }

    /// @brief other An object to be compared with this object.
    ///
    /// It ignores the configuration sequence number when checking for
    /// inequality of objects.
    ///
    /// @param other An object to be compared with this object.
    ///
    /// @return true if two objects are not equal, false otherwise.
    bool operator!=(const SrvConfig& other) const {
        return (nequals(other));
    }

    //@}

    /// @brief Merges the configuration specified as a parameter into
    /// this configuration.
    ///
    /// This method is used when two or more configurations held in the
    /// @c SrvConfig objects need to be combined into a single configuration.
    /// Specifically, when the configuration backend is used, then part of
    /// the server configuration comes from the configuration file and
    /// stored in the staging configuration. The other part of the
    /// configuration comes from the database. The configuration fetched
    /// from the database is stored in a separate @c SrvConfig instance
    /// and then merged into the staging configuration prior to committing
    /// it.
    ///
    /// The merging strategy depends on the underlying data being merged.
    /// For example: subnets are merged using the algorithm implemented
    /// in the @c CfgSubnets4. Other data structures are merged using the
    /// algorithms implemented in their respective configuration
    /// containers.
    ///
    /// The general rule is that the configuration data from the @c other
    /// object replaces configuration data held in this object instance.
    /// The data that do not overlap between the two objects is simply
    /// inserted into this configuration.
    ///
    /// Due to the nature of the client classes, i.e. they are ordered and
    /// depend on each other, individual classes are not merged. Instead,
    /// the new list of classes entirely replaces the existing list. It
    /// implies that client classes should not be defined in a config
    /// file if there are classes defined in the config backend for this
    /// server.
    ///
    /// @warning The call to @c merge may modify the data in the @c other
    /// object. Therefore, the caller must not rely on the data held
    /// in the @c other object after the call to @c merge. Also, the
    /// data held in @c other must not be modified after the call to
    /// @c merge because it may affect the merged configuration.
    ///
    /// The @c other parameter must be a @c SrvConfig or its derivation.
    ///
    /// This method calls either @c merge4 or @c merge6 based on
    ///
    /// Currently, the following parts of the configuration are merged:
    /// - globals
    /// - option definitions
    /// - options
    /// - client classes
    /// - via @c merge4 or @c merge6 depending on @c CfgMgr::family_:
    ///     - shared networks
    ///     - subnets
    ///
    /// @todo Add support for merging other configuration elements.
    ///
    /// @param other An object holding the configuration to be merged
    /// into this configuration.
    virtual void merge(ConfigBase& other);

    /// @brief Updates statistics.
    ///
    /// This method calls appropriate methods in child objects that update
    /// related statistics. See @ref CfgSubnets4::updateStatistics and
    /// @ref CfgSubnets6::updateStatistics for details.
    void updateStatistics();

    /// @brief Removes statistics.
    ///
    /// This method calls appropriate methods in child objects that remove
    /// related statistics. See @ref CfgSubnets4::removeStatistics and
    /// @ref CfgSubnets6::removeStatistics for details.
    void removeStatistics();

    /// @brief Sets decline probation-period
    ///
    /// Probation-period is the timer, expressed, in seconds, that specifies how
    /// long a lease is unavailable after reported as declined.
    ///
    /// @param decline_timer number of seconds after declined lease is restored
    void setDeclinePeriod(const uint32_t decline_timer) {
        decline_timer_ = decline_timer;
    }

    /// @brief Returns probation-period
    ///
    /// See @ref setDeclinePeriod for brief discussion.
    ///
    /// @return value of probation-period, expressed in seconds
    uint32_t getDeclinePeriod() const {
        return (decline_timer_);
    }

    /// @brief Sets whether server should send back client-id in DHCPv4
    ///
    /// This is a compatibility flag. The default (true) is compliant with
    /// RFC6842. False is for backward compatibility.
    ///
    /// @param echo should the client-id be sent or not
    void setEchoClientId(const bool echo) {
        echo_v4_client_id_ = echo;
    }

    /// @brief Returns whether server should send back client-id in DHCPv4.
    ///
    /// @return true if client-id should be returned, false otherwise.
    bool getEchoClientId() const {
        return (echo_v4_client_id_);
    }

    /// @brief Sets DHCP4o6 IPC port
    ///
    /// DHCPv4-over-DHCPv6 uses a UDP socket for inter-server communication,
    /// this socket is bound and connected to this port and port + 1
    ///
    /// @param port port and port + 1 to use
    void setDhcp4o6Port(uint16_t port) {
        dhcp4o6_port_ = port;
    }

    /// @brief Returns DHCP4o6 IPC port
    ///
    /// See @ref setDhcp4o6Port for brief discussion.
    ///
    /// @return value of DHCP4o6 IPC port
    uint16_t getDhcp4o6Port() const {
        return (dhcp4o6_port_);
    }

    /// @brief Returns pointer to the D2 client configuration
    ///
    /// @return Pointer to the D2 client configuration
    D2ClientConfigPtr getD2ClientConfig() {
        return (d2_client_config_);
    }

    /// @brief Returns pointer to const D2 client configuration
    ///
    /// @return Pointer to const D2 client configuration
    const D2ClientConfigPtr getD2ClientConfig() const {
        return (d2_client_config_);
    }

    /// @brief Sets the D2 client configuration
    ///
    /// @param d2_client_config pointer to the new D2 client configuration
    void setD2ClientConfig(const D2ClientConfigPtr& d2_client_config) {
        d2_client_config_ = d2_client_config;
    }

    /// @brief Returns non-const pointer to configured global parameters.
    ///
    /// This function returns a non-const pointer to the configured
    /// global parameters.
    ///
    /// @return Object representing configured global parameters.
    CfgGlobalsPtr getConfiguredGlobals() {
        return (configured_globals_);
    }

    /// @brief Returns const pointer to configured global parameters.
    ///
    /// This function returns a const pointer to the configured
    /// global parameters.
    ///
    /// @return Object representing configured global parameters.
    ConstCfgGlobalsPtr getConfiguredGlobals() const {
        return (configured_globals_);
    }

    /// @brief Returns pointer to a given configured global parameter
    ///
    /// @param name Name of the parameter to fetch.
    /// @return Pointer to the parameter if it exists, otherwise an
    /// empty pointer.
    isc::data::ConstElementPtr getConfiguredGlobal(std::string name) const {
        return (configured_globals_->get(name));
    }

    /// @brief Returns pointer to a given configured global parameter
    ///
    /// @param index Index of the parameter to fetch.
    /// @return Pointer to the parameter if it exists, otherwise an
    /// empty pointer.
    isc::data::ConstElementPtr getConfiguredGlobal(int index) const {
        return (configured_globals_->get(index));
    }

    /// @brief Removes all configured global parameters.
    ///
    /// @note This removes the default values too so either
    /// @c applyDefaultsConfiguredGlobals and @c mergeGlobals,
    /// or @c isc::data::SimpleParser::setDefaults and
    /// @c extractConfiguredGlobals should be called after.
    void clearConfiguredGlobals() {
        configured_globals_->clear();
    }

    /// @brief Applies defaults to global parameters.
    ///
    /// @param defaults vector of (name, type, value) defaults to apply.
    void applyDefaultsConfiguredGlobals(const isc::data::SimpleDefaults& defaults);

    /// @brief Saves scalar elements from the global scope of a configuration.
    void extractConfiguredGlobals(isc::data::ConstElementPtr config);

    /// @brief Adds a parameter to the collection configured globals
    ///
    /// @param name std::string name of the global to add.
    /// @param value ElementPtr containing the value of the global.
    void addConfiguredGlobal(const std::string& name, isc::data::ConstElementPtr value) {
        configured_globals_->set(name, value);
    }

    /// @brief Conducts sanity checks on global lifetime parameters.
    ///
    /// @param name Base name of the lifetime parameter.
    void sanityChecksLifetime(const std::string& name) const;

    /// @brief Conducts sanity checks on global lifetime parameters
    /// before merge from the external configuration to the target one.
    ///
    /// @param target_config Target configuration.
    /// @param name Base name of the lifetime parameter.
    void sanityChecksLifetime(const SrvConfig& target_config,
                              const std::string& name) const;

    /// @brief Moves deprecated parameters from dhcp-ddns element to global element
    ///
    /// Given a server configuration element map, the following parameters are moved
    /// from dhcp-ddns to top-level (i.e. global) element if they do not already
    /// exist there:
    ///
    /// @code
    /// From dhcp-ddns:            To (global):
    /// ------------------------------------------------------
    /// override-no-update         ddns-override-no-update
    /// override-client-update     ddns-override-client-update
    /// replace-client-name        ddns-replace-client-name
    /// generated-prefix           ddns-generated-prefix
    /// qualifying-suffix          ddns-qualifying-suffix
    /// hostname-char-set          hostname-char-set
    /// hostname-char-replacement  hostname-char-replacement
    /// @endcode
    ///
    /// Note that the whether or not the deprecated parameters are added
    /// to the global element, they are always removed from the dhcp-ddns
    /// element.
    ///
    /// @param srv_elem server top level map to alter
    static void moveDdnsParams(isc::data::ElementPtr srv_elem);

    /// @brief Configures the server to allow or disallow specifying multiple
    /// hosts with the same IP address/subnet.
    ///
    /// This setting is applied in @c CfgDbAccess and @c CfgHosts. This function
    /// should be called when the server is being configured using the configuration
    /// file, config-set command or via the configuration backend.
    ///
    /// @param unique Boolean value indicating if it is allowed (when false)
    /// or disallowed to specify multiple hosts with the same IP reservation.
    void setIPReservationsUnique(const bool unique);

    /// @brief Sets whether the server does host reservations lookup before lease
    /// lookup.
    ///
    /// @param first Boolean value indicating if host reservations lookup should
    /// be performed before lease lookup.
    void setReservationsLookupFirst(const bool first) {
        reservations_lookup_first_ = first;
    }

    /// @brief Returns whether the server does host reservations lookup before
    /// lease lookup.
    ///
    /// @return Boolean value indicating if host reservations lookup should be
    /// performed before lease lookup.
    bool getReservationsLookupFirst() const {
        return (reservations_lookup_first_);
    }

    /// @brief Unparse a configuration object
    ///
    /// @return a pointer to unparsed configuration
    virtual isc::data::ElementPtr toElement() const;

    /// @brief Set lenient option parsing compatibility flag.
    ///
    /// @param value the boolean value to be set when configuring lenient option
    /// parsing
    void setLenientOptionParsing(bool const value) {
        lenient_option_parsing_ = value;
    }

    /// @brief Get lenient option parsing compatibility flag.
    ///
    /// @return the configured value for lenient option parsing
    bool getLenientOptionParsing() const {
        return lenient_option_parsing_;
    }

    /// @brief Set ignore DHCP Server Identifier compatibility flag.
    ///
    /// @param value the boolean value to be set when configuring DHCP
    /// Server Identifier usage preferences.
    void setIgnoreServerIdentifier(bool const value) {
        ignore_dhcp_server_identifier_ = value;
    }

    /// @brief Get ignore DHCP Server Identifier compatibility flag.
    ///
    /// @return the configured value for DHCP Server Identifier usage preferences.
    bool getIgnoreServerIdentifier() const {
        return (ignore_dhcp_server_identifier_);
    }

    /// @brief Set ignore RAI Link Selection compatibility flag.
    ///
    /// @param value the boolean value to be set when configuring RAI Link
    /// Selection usage preferences
    void setIgnoreRAILinkSelection(bool const value) {
        ignore_rai_link_selection_ = value;
    }

    /// @brief Get ignore RAI Link Selection compatibility flag.
    ///
    /// @return the configured value for RAI Link Selection usage preferences
    bool getIgnoreRAILinkSelection() const {
        return ignore_rai_link_selection_;
    }

    /// @brief Set exclude .0 and .255 addresses in subnets bigger than /24 flag.
    ///
    /// @param value the boolean value to be set when excluding .0 .255 from
    /// subnets bigger than /24.
    void setExcludeFirstLast24(bool const value) {
        exclude_first_last_24_ = value;
    }

    /// @brief Get exclude .0 and .255 addresses in subnets bigger than /24 flag.
    ///
    /// @return the configured value for exclude .0 and .255 flag.
    bool getExcludeFirstLast24() const {
        return exclude_first_last_24_;
    }

    /// @brief Convenience method to propagate configuration parameters through
    /// inversion of control.
    ///
    /// To be used as a last resort when CfgMgr::instance().getCurrentCfg()
    /// can't be easily called from where the configuration parameter is used,
    /// usually because that particular library is lower in the dependency tree.
    /// Happens on configuration commit.
    void configureLowerLevelLibraries() const;

private:

    /// @brief Merges the DHCPv4 configuration specified as a parameter into
    /// this configuration.
    ///
    /// This is called by @c merge() to handle v4 specifics, such as
    /// networks and subnets.
    ///
    /// @param other An object holding the configuration to be merged
    /// into this configuration.
    void merge4(SrvConfig& other);

    /// @brief Merges the DHCPv6 configuration specified as a parameter into
    /// this configuration.
    ///
    /// This is called by @c merge() to handle v4 specifics, such as
    /// networks and subnets.
    ///
    /// @param other An object holding the configuration to be merged
    /// into this configuration.
    void merge6(SrvConfig& other);

    /// @brief Merges the globals specified in the given configuration
    /// into this configuration.
    ///
    /// Configurable global values may be specified either via JSON
    /// configuration (e.g. "echo-client-id":true) or as global parameters
    /// within a configuration back end.  Regardless of the source, these
    /// values once provided, are stored in @c SrvConfig::configured_globals_.
    /// Any such value that does not have an explicit specification should be
    /// considered "unspecified" at the global scope.
    ///
    /// This function adds the configured globals from the "other" config
    /// into this config's configured globals.  If a value already exists
    /// in this config, it will be overwritten with the value from the
    /// "other" config.
    ///
    /// It then iterates over this merged list of globals, setting
    /// any of the corresponding SrvConfig members that map to a
    /// a configurable parameter (e.g. c@ SrvConfig::echo_client_id_,
    /// @c SrvConfig::server_tag_).
    ///
    /// @param other An object holding the configuration to be merged
    /// into this configuration.
    void mergeGlobals(SrvConfig& other);

    /// @brief Sequence number identifying the configuration.
    uint32_t sequence_;

    /// @brief Interface configuration.
    ///
    /// Used to select interfaces on which the DHCP server will listen to
    /// queries.
    CfgIfacePtr cfg_iface_;

    /// @brief Pointer to option definitions configuration.
    ///
    /// This object holds the user-defined option definitions grouped
    /// by option space name.
    CfgOptionDefPtr cfg_option_def_;

    /// @brief Pointer to options (data) configuration.
    ///
    /// This object holds the instances of the options to be sent to clients
    /// connected to any subnet.
    CfgOptionPtr cfg_option_;

    /// @brief Pointer to subnets configuration for IPv4.
    CfgSubnets4Ptr cfg_subnets4_;

    /// @brief Pointer to subnets configuration for IPv6.
    CfgSubnets6Ptr cfg_subnets6_;

    /// @brief Pointer to IPv4 shared networks configuration.
    CfgSharedNetworks4Ptr cfg_shared_networks4_;

    /// @brief Pointer to IPv4 shared networks configuration.
    CfgSharedNetworks6Ptr cfg_shared_networks6_;

    /// @brief Pointer to the configuration for hosts reservation.
    ///
    /// This object holds a list of @c Host objects representing host
    /// reservations for different IPv4 and IPv6 subnets.
    CfgHostsPtr cfg_hosts_;

    /// @brief A list of configured MAC sources.
    CfgMACSource cfg_mac_source_;

    /// @brief Pointer to the configuration for RSOO-enabled options.
    ///
    /// This object holds a set of RSOO-enabled options. See
    /// RFC 6422 for the definition of the RSOO-enabled option.
    CfgRSOOPtr cfg_rsoo_;

    /// @brief Pointer to the configuration pertaining to processing of
    /// expired leases.
    CfgExpirationPtr cfg_expiration_;

    /// @brief Pointer to the configuration of the server identifier.
    CfgDUIDPtr cfg_duid_;

    /// @brief Pointer to the configuration of the lease and host database
    /// connection parameters.
    CfgDbAccessPtr cfg_db_access_;

    /// @brief Pointer to the general configuration for host reservations in
    /// DHCPv4.
    CfgHostOperationsPtr cfg_host_operations4_;

    /// @brief Pointer to the general configuration for host reservations in
    /// DHCPv6.
    CfgHostOperationsPtr cfg_host_operations6_;

    /// @brief Pointer to the control-socket information
    isc::data::ConstElementPtr control_socket_;

    /// @brief Pointer to the dhcp-queue-control information
    isc::data::ConstElementPtr dhcp_queue_control_;

    /// @brief Pointer to the multi-threading information
    isc::data::ConstElementPtr dhcp_multi_threading_;

    /// @brief Pointer to the dictionary of global client class definitions
    ClientClassDictionaryPtr class_dictionary_;

    /// @brief Configured hooks libraries.
    isc::hooks::HooksConfig hooks_config_;

    /// @brief Decline Period time
    ///
    /// This timer specifies decline probation period, the time after a declined
    /// lease is recovered back to available state. Expressed in seconds.
    uint32_t decline_timer_;

    /// @brief Indicates whether v4 server should send back client-id
    bool echo_v4_client_id_;

    /// @brief DHCP4o6 IPC port
    ///
    /// DHCPv4-over-DHCPv6 uses a UDP socket for interserver communication,
    /// this socket is bound and connected to this port and port + 1
    uint16_t dhcp4o6_port_;

    /// @brief Stores D2 client configuration
    D2ClientConfigPtr d2_client_config_;

    /// @brief Stores the global parameters specified via configuration
    CfgGlobalsPtr configured_globals_;

    /// @brief Pointer to the configuration consistency settings
    CfgConsistencyPtr cfg_consist_;

    /// @name Compatibility flags
    ///
    //@{
    /// @brief Indicates whether lenient option parsing is enabled
    bool lenient_option_parsing_;
    /// @brief Indicates whether DHCP server identifier option will be ignored
    bool ignore_dhcp_server_identifier_;
    /// @brief Indicates whether RAI link-selection suboptions will be ignored
    bool ignore_rai_link_selection_;
    /// @brief Indicates whether exclude .0 .255 from subnets bigger than /24.
    bool exclude_first_last_24_;
    //@}

    /// @brief Flag which indicates if the server should do host reservations
    /// lookup before lease lookup. This parameter has effect only when
    /// multi-threading is disabled. If multi-threading is enabled, host
    /// reservations lookup is always performed first.
    /// It default to false when multi-threading is disabled.
    bool reservations_lookup_first_;
};

/// @name Pointers to the @c SrvConfig object.
///
//@{
/// @brief Non-const pointer to the @c SrvConfig.
typedef boost::shared_ptr<SrvConfig> SrvConfigPtr;

/// @brief Const pointer to the @c SrvConfig.
typedef boost::shared_ptr<const SrvConfig> ConstSrvConfigPtr;
//@}

}  // namespace dhcp
}  // namespace isc

#endif // DHCPSRV_CONFIG_H
