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

#ifndef CFGMGR_H
#define CFGMGR_H

#include <asiolink/io_address.h>
#include <dhcp/option.h>
#include <dhcp/option_definition.h>
#include <dhcp/option_space.h>
#include <dhcp/classify.h>
#include <dhcpsrv/d2_client_mgr.h>
#include <dhcpsrv/option_space_container.h>
#include <dhcpsrv/pool.h>
#include <dhcpsrv/subnet.h>
#include <dhcpsrv/configuration.h>
#include <util/buffer.h>

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
        isc::Exception(file, line, what) { };
};

/// @brief Exception thrown upon attempt to add subnet with an ID that belongs
/// to the subnet that already exists.
class DuplicateSubnetID : public Exception {
public:
    DuplicateSubnetID(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) { };
};

/// @brief Configuration Manager
///
/// This singleton class holds the whole configuration for DHCPv4 and DHCPv6
/// servers. It currently holds information about zero or more subnets6.
/// Each subnet may contain zero or more pools. Pool4 and Pool6 is the most
/// basic "chunk" of configuration. It contains a range of assignable
/// addresses.
///
/// Below is a sketch of configuration inheritance (not implemented yet).
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
/// Parameter inheritance is likely to be implemented in configuration handling
/// routines, so there is no storage capability in a global scope for
/// subnet-specific parameters.
///
/// @todo: Implement Subnet4 support (ticket #2237)
/// @todo: Implement option definition support
/// @todo: Implement parameter inheritance
class CfgMgr : public boost::noncopyable {
public:

    /// @brief A number of configurations held by @c CfgMgr.
    ///
    /// @todo Make it configurable.
    static const size_t CONFIG_LIST_SIZE;

    /// @brief returns a single instance of Configuration Manager
    ///
    /// CfgMgr is a singleton and this method is the only way of
    /// accessing it.
    static CfgMgr& instance();

    /// @brief Add new option definition.
    ///
    /// @param def option definition to be added.
    /// @param option_space name of the option space to add definition to.
    ///
    /// @throw isc::dhcp::DuplicateOptionDefinition when the particular
    /// option definition already exists.
    /// @throw isc::dhcp::MalformedOptionDefinition when the pointer to
    /// an option definition is NULL.
    /// @throw isc::BadValue when the option space name is empty or
    /// when trying to override the standard option (in dhcp4 or dhcp6
    /// option space).
    void addOptionDef(const OptionDefinitionPtr& def,
                      const std::string& option_space);

    /// @brief Return option definitions for particular option space.
    ///
    /// @param option_space option space.
    ///
    /// @return pointer to the collection of option definitions for
    /// the particular option space. The option collection is empty
    /// if no option exists for the option space specified.
    OptionDefContainerPtr
    getOptionDefs(const std::string& option_space) const;

    /// @brief Return option definition for a particular option space and code.
    ///
    /// @param option_space option space.
    /// @param option_code option code.
    ///
    /// @return an option definition or NULL pointer if option definition
    /// has not been found.
    OptionDefinitionPtr getOptionDef(const std::string& option_space,
                                     const uint16_t option_code) const;

    /// @brief Adds new DHCPv4 option space to the collection.
    ///
    /// @param space option space to be added.
    ///
    /// @throw isc::dhcp::InvalidOptionSpace invalid option space
    /// has been specified.
    void addOptionSpace4(const OptionSpacePtr& space);

    /// @brief Adds new DHCPv6 option space to the collection.
    ///
    /// @param space option space to be added.
    ///
    /// @throw isc::dhcp::InvalidOptionSpace invalid option space
    /// has been specified.
    void addOptionSpace6(const OptionSpacePtr& space);

    /// @brief Return option spaces for DHCPv4.
    ///
    /// @return A collection of option spaces.
    const OptionSpaceCollection& getOptionSpaces4() const {
        return (spaces4_);
    }

    /// @brief Return option spaces for DHCPv6.
    ///
    /// @return A collection of option spaces.
    const OptionSpaceCollection& getOptionSpaces6() const {
        return (spaces6_);
    }

    /// @brief get IPv6 subnet by address
    ///
    /// Finds a matching subnet, based on an address. This can be used
    /// in two cases: when trying to find an appropriate lease based on
    /// a) relay link address (that must be the address that is on link)
    /// b) our global address on the interface the message was received on
    ///    (for directly connected clients)
    ///
    /// If there are any classes specified in a subnet, that subnet
    /// will be selected only if the client belongs to appropriate class.
    ///
    /// @note The client classification is checked before any relay
    /// information checks are conducted.
    ///
    /// If relay is true then relay info overrides (i.e. value the sysadmin
    /// can configure in Dhcp6/subnet6[X]/relay/ip-address) can be used.
    /// That is applicable only for relays. Those overrides must not be used
    /// for client address or for client hints. They are for link-addr field
    /// in the RELAY_FORW message only.
    ///
    /// @param hint an address that belongs to a searched subnet
    /// @param classes classes the client belongs to
    /// @param relay true if address specified in hint is a relay
    ///
    /// @return a subnet object (or NULL if no suitable match was fount)
    Subnet6Ptr getSubnet6(const isc::asiolink::IOAddress& hint,
                          const isc::dhcp::ClientClasses& classes,
                          const bool relay = false);

    /// @brief get IPv6 subnet by interface name
    ///
    /// Finds a matching local subnet, based on interface name. This
    /// is used for selecting subnets that were explicitly marked by the
    /// user as reachable over specified network interface.
    ///
    /// If there are any classes specified in a subnet, that subnet
    /// will be selected only if the client belongs to appropriate class.
    ///
    /// @param iface_name interface name
    /// @param classes classes the client belongs to
    ///
    /// @return a subnet object (or NULL if no suitable match was fount)
    Subnet6Ptr getSubnet6(const std::string& iface_name,
                          const isc::dhcp::ClientClasses& classes);

    /// @brief get IPv6 subnet by interface-id
    ///
    /// Another possibility to find a subnet is based on interface-id.
    ///
    /// If there are any classes specified in a subnet, that subnet
    /// will be selected only if the client belongs to appropriate class.
    ///
    /// @param interface_id content of interface-id option returned by a relay
    /// @param classes classes the client belongs to
    ///
    /// @return a subnet object
    Subnet6Ptr getSubnet6(OptionPtr interface_id,
                          const isc::dhcp::ClientClasses& classes);

    /// @brief adds an IPv6 subnet
    ///
    /// @param subnet new subnet to be added.
    void addSubnet6(const Subnet6Ptr& subnet);

    /// @brief Delete all option definitions.
    void deleteOptionDefs();

    /// @todo: Add subnet6 removal routines. Currently it is not possible
    /// to remove subnets. The only case where subnet6 removal would be
    /// needed is a dynamic server reconfiguration - a use case that is not
    /// planned to be supported any time soon.

    /// @brief removes all IPv6 subnets
    ///
    /// This method removes all existing IPv6 subnets. It is used during
    /// reconfiguration - old configuration is wiped and new definitions
    /// are used to recreate subnets.
    ///
    /// @todo Implement more intelligent approach. Note that comparison
    /// between old and new configuration is tricky. For example: is
    /// 2000::/64 and 2000::/48 the same subnet or is it something
    /// completely new?
    void deleteSubnets6();

    /// @brief Returns pointer to the collection of all IPv4 subnets.
    ///
    /// This is used in a hook (subnet4_select), where the hook is able
    /// to choose a different subnet. Server code has to offer a list
    /// of possible choices (i.e. all subnets).
    /// @return a pointer to const Subnet4 collection
    const Subnet4Collection* getSubnets4() const {
        return (&subnets4_);
    }

    /// @brief returns const reference to all subnets6
    ///
    /// This is used in a hook (subnet6_select), where the hook is able
    /// to choose a different subnet. Server code has to offer a list
    /// of possible choices (i.e. all subnets).
    /// @return a pointer to const Subnet6 collection
    const Subnet6Collection* getSubnets6() {
        return (&subnets6_);
    }

    /// @brief get IPv4 subnet by address
    ///
    /// Finds a matching subnet, based on an address. This can be used
    /// in two cases: when trying to find an appropriate lease based on
    /// a) relay link address (that must be the address that is on link)
    /// b) our global address on the interface the message was received on
    ///    (for directly connected clients)
    ///
    /// If there are any classes specified in a subnet, that subnet
    /// will be selected only if the client belongs to appropriate class.
    ///
    /// If relay is true then relay info overrides (i.e. value the sysadmin
    /// can configure in Dhcp4/subnet4[X]/relay/ip-address) can be used.
    /// That is true only for relays. Those overrides must not be used
    /// for client address or for client hints. They are for giaddr only.
    ///
    /// @param hint an address that belongs to a searched subnet
    /// @param classes classes the client belongs to
    /// @param relay true if address specified in hint is a relay
    ///
    /// @return a subnet object
    Subnet4Ptr getSubnet4(const isc::asiolink::IOAddress& hint,
                          const isc::dhcp::ClientClasses& classes,
                          bool relay = false) const;

    /// @brief Returns a subnet for the specified local interface.
    ///
    /// This function checks that the IP address assigned to the specified
    /// interface belongs to any IPv4 subnet configured, and returns this
    /// subnet.
    ///
    /// @todo Implement classes support here.
    ///
    /// @param iface Short name of the interface which is being checked.
    /// @param classes classes the client belongs to
    ///
    /// @return Pointer to the subnet matching interface specified or NULL
    /// pointer if IPv4 address on the interface doesn't match any subnet.
    Subnet4Ptr getSubnet4(const std::string& iface,
                          const isc::dhcp::ClientClasses& classes) const;

    /// @brief adds a subnet4
    void addSubnet4(const Subnet4Ptr& subnet);

    /// @brief removes all IPv4 subnets
    ///
    /// This method removes all existing IPv4 subnets. It is used during
    /// reconfiguration - old configuration is wiped and new definitions
    /// are used to recreate subnets.
    ///
    /// @todo Implement more intelligent approach. Note that comparison
    /// between old and new configuration is tricky. For example: is
    /// 192.0.2.0/23 and 192.0.2.0/24 the same subnet or is it something
    /// completely new?
    void deleteSubnets4();


    /// @brief returns path do the data directory
    ///
    /// This method returns a path to writeable directory that DHCP servers
    /// can store data in.
    /// @return data directory
    std::string getDataDir();

    /// @brief Sets whether server should send back client-id in DHCPv4
    ///
    /// This is a compatibility flag. The default (true) is compliant with
    /// RFC6842. False is for backward compatibility.
    ///
    /// @param echo should the client-id be sent or not
    void echoClientId(const bool echo) {
        echo_v4_client_id_ = echo;
    }

    /// @brief Returns whether server should send back client-id in DHCPv4.
    /// @return true if client-id should be returned, false otherwise.
    bool echoClientId() const {
        return (echo_v4_client_id_);
    }

    /// @brief Updates the DHCP-DDNS client configuration to the given value.
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
    /// without affecting a currently used configuration and then commiting
    /// the configuration to replace current configuration atomically.
    /// They also allow for keeping a history of previous configurations so
    /// as the @c CfgMgr can revert to the historical configuration when
    /// required.
    ///
    /// @todo Migrate all configuration parameters to use the model supported
    /// by these functions.
    ///
    /// @todo Make the size of the configurations history configurable.
    ///
    //@{

    /// @brief Removes current, staging and all previous configurations.
    ///
    /// This function removes all configurations, including current and
    /// staging configurations. It creates a new current configuration with
    /// default settings.
    ///
    /// This function is exception safe.
    void clear();

    /// @brief Commits the staging configuration.
    ///
    /// The staging configuration becomes current configuration when this
    /// function is called. It removes the oldest configurations held in the
    /// history so as the size of the list of configuration does not excide
    /// the @c CONFIG_LIST_SIZE.
    ///
    /// This function is exception safe.
    void commit();

    /// @brief Removes staging configuration.
    ///
    /// This function should be called when there is a staging configuration
    /// (likely created in the previous configuration attempt) but the entirely
    /// new configuration should be created. It removes the existing staging
    /// configuration and the next call to @c CfgMgr::getStagingCfg will return a
    /// fresh (default) configuration.
    ///
    /// This function is exception safe.
    void rollback();

    /// @brief Reverts to one of the previous configurations.
    ///
    /// This function reverts to selected previous configuration. The previous
    /// configuration is entirely copied to a new @c Configuration instance. This
    /// new instance has a unique sequence id (sequence id is not copied). The
    /// previous configuration (being copied) is not modified by this operation.
    ///
    /// The configuration to be copied is identified by the index value which
    /// is the distance between the current (most recent) and desired
    /// configuration. If the index is out of range an exception is thrown.
    ///
    /// @warning Revert operation will rollback any changes to the staging
    /// configuration (if it exists).
    ///
    /// @throw isc::OutOfRange if the specified index is out of range.
    void revert(const size_t index);

    /// @brief Returns a pointer to the current configuration.
    ///
    /// This function returns pointer to the current configuration. If the
    /// current configuration is not set it will create a default configuration
    /// and return it. Current configuration returned is read-only.
    ///
    /// @return Non-null const pointer to the current configuration.
    ConstConfigurationPtr getCurrentCfg();

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
    ConfigurationPtr getStagingCfg();

    //@}

    /// @name Methods setting/accessing global configuration for the process.
    ///
    //@{
    /// @brief Sets verbose mode.
    ///
    /// @param verbose A boolean value indicating if the process should run
    /// in verbose (true) or non-verbose mode.
    void setVerbose(const bool verbose) {
        verbose_mode_ = verbose;
    }

    /// @brief Checks if the process has been run in verbose mode.
    ///
    /// @return true if verbose mode enabled, false otherwise.
    bool isVerbose() const {
        return (verbose_mode_);
    }

    /// @brief Sets the default logger name.
    ///
    /// This name is used in cases when a user doesn't provide a configuration
    /// for logger in the Kea configuration file.
    void setDefaultLoggerName(const std::string& name) {
        default_logger_name_ = name;
    }

    /// @brief Returns default logger name.
    std::string getDefaultLoggerName() const {
        return (default_logger_name_);
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
    virtual ~CfgMgr();

    /// @brief a container for IPv6 subnets.
    ///
    /// That is a simple vector of pointers. It does not make much sense to
    /// optimize access time (e.g. using a map), because typical search
    /// pattern will use calling inRange() method on each subnet until
    /// a match is found.
    Subnet6Collection subnets6_;

    /// @brief a container for IPv4 subnets.
    ///
    /// That is a simple vector of pointers. It does not make much sense to
    /// optimize access time (e.g. using a map), because typical search
    /// pattern will use calling inRange() method on each subnet until
    /// a match is found.
    Subnet4Collection subnets4_;

private:

    /// @brief Checks if current configuration is created and creates if needed.
    ///
    /// This private method is called to ensure that the current configuration
    /// is created. If current configuration is not set, it creates the
    /// default current configuration.
    void ensureCurrentAllocated();

    /// @brief Checks that the IPv4 subnet with the given id already exists.
    ///
    /// @param subnet Subnet for which this function will check if the other
    /// subnet with equal id already exists.
    /// @return true if the duplicate subnet exists.
    bool isDuplicate(const Subnet4& subnet) const;

    /// @brief Checks that the IPv6 subnet with the given id already exists.
    ///
    /// @param subnet Subnet for which this function will check if the other
    /// subnet with equal id already exists.
    /// @return true if the duplicate subnet exists.
    bool isDuplicate(const Subnet6& subnet) const;

    /// @brief A collection of option definitions.
    ///
    /// A collection of option definitions that can be accessed
    /// using option space name they belong to.
    OptionSpaceContainer<OptionDefContainer,
        OptionDefinitionPtr, std::string> option_def_spaces_;

    /// @brief Container for defined DHCPv6 option spaces.
    OptionSpaceCollection spaces6_;

    /// @brief Container for defined DHCPv4 option spaces.
    OptionSpaceCollection spaces4_;

    /// @brief directory where data files (e.g. server-id) are stored
    std::string datadir_;

    /// Indicates whether v4 server should send back client-id
    bool echo_v4_client_id_;

    /// @brief Manages the DHCP-DDNS client and its configuration.
    D2ClientMgr d2_client_mgr_;

    /// @brief Configuration
    ///
    /// This is a structure that will hold all configuration.
    /// @todo: migrate all other parameters to that structure.
    /// @todo: maybe this should be a vector<Configuration>, so we could keep
    ///        previous configurations and do a rollback if needed?
    ConfigurationPtr configuration_;

    /// @name Configuration List.
    ///
    //@{
    /// @brief Configuration list type.
    typedef std::list<ConfigurationPtr> ConfigurationList;

    /// @brief Container holding all previous and current configurations.
    ConfigurationList configs_;
    //@}

    /// @brief Indicates if a process has been ran in the verbose mode.
    bool verbose_mode_;

    /// @brief Default logger name.
    std::string default_logger_name_;
};

} // namespace isc::dhcp
} // namespace isc

#endif // CFGMGR_H
