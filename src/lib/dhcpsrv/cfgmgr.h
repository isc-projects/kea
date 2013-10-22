// Copyright (C) 2012-2013 Internet Systems Consortium, Inc. ("ISC")
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
#include <dhcpsrv/option_space_container.h>
#include <dhcpsrv/pool.h>
#include <dhcpsrv/subnet.h>
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
    /// @param hint an address that belongs to a searched subnet
    ///
    /// @return a subnet object (or NULL if no suitable match was fount)
    Subnet6Ptr getSubnet6(const isc::asiolink::IOAddress& hint);

    /// @brief get IPv6 subnet by interface name
    ///
    /// Finds a matching local subnet, based on interface name. This
    /// is used for selecting subnets that were explicitly marked by the
    /// user as reachable over specified network interface.
    /// @param iface_name interface name
    /// @return a subnet object (or NULL if no suitable match was fount)
    Subnet6Ptr getSubnet6(const std::string& iface_name);

    /// @brief get IPv6 subnet by interface-id
    ///
    /// Another possibility to find a subnet is based on interface-id.
    ///
    /// @param interface_id content of interface-id option returned by a relay
    ///
    /// @return a subnet object
    Subnet6Ptr getSubnet6(OptionPtr interface_id);

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

    /// @brief returns const reference to all subnets6
    ///
    /// This is used in a hook (subnet4_select), where the hook is able
    /// to choose a different subnet. Server code has to offer a list
    /// of possible choices (i.e. all subnets).
    /// @return a pointer to const Subnet6 collection
    const Subnet4Collection* getSubnets4() {
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
    /// @param hint an address that belongs to a searched subnet
    ///
    /// @return a subnet object
    Subnet4Ptr getSubnet4(const isc::asiolink::IOAddress& hint);

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

    /// @brief Adds the name of the interface to the set of interfaces on which
    /// server should listen.
    ///
    /// @param iface A name of the interface being added to the listening set.
    void addActiveIface(const std::string& iface);

    /// @brief Sets the flag which indicates that server is supposed to listen
    /// on all available interfaces.
    ///
    /// This function does not close or open sockets. It simply marks that
    /// server should start to listen on all interfaces the next time sockets
    /// are reopened. Server should examine this flag when it gets reconfigured
    /// and configuration changes the interfaces that server should listen on.
    void activateAllIfaces();

    /// @brief Clear the collection of the interfaces that server should listen
    /// on.
    ///
    /// Apart from clearing the list of interfaces specified with
    /// @c CfgMgr::addListeningInterface, it also disables listening on all
    /// interfaces if it has been enabled using
    /// @c CfgMgr::activateAllInterfaces.
    /// Likewise @c CfgMgr::activateAllIfaces, this function does not close or
    /// open sockets. It marks all interfaces inactive for DHCP traffic.
    /// Server should examine this new setting when it attempts to
    /// reopen sockets (as a result of reconfiguration).
    void deleteActiveIfaces();

    /// @brief Check if specified interface should be used to listen to DHCP
    /// traffic.
    ///
    /// @param iface A name of the interface to be checked.
    ///
    /// @return true if the specified interface belongs to the set of the
    /// interfaces on which server is configured to listen.
    bool isActiveIface(const std::string& iface) const;

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

    /// @brief Checks if the specified interface is listed as active.
    ///
    /// This function searches for the specified interface name on the list of
    /// active interfaces: @c CfgMgr::active_ifaces_. It does not take into
    /// account @c CfgMgr::all_ifaces_active_ flag. If this flag is set to true
    /// but the specified interface does not belong to
    /// @c CfgMgr::active_ifaces_, it will return false.
    ///
    /// @param iface interface name.
    ///
    /// @return true if specified interface belongs to
    /// @c CfgMgr::active_ifaces_.
    bool isIfaceListedActive(const std::string& iface) const;

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

    /// @name A collection of interface names on which server listens.
    //@{
    typedef std::list<std::string> ActiveIfacesCollection;
    std::list<std::string> active_ifaces_;
    //@}

    /// A flag which indicates that server should listen on all available
    /// interfaces.
    bool all_ifaces_active_;
};

} // namespace isc::dhcp
} // namespace isc

#endif // CFGMGR_H
