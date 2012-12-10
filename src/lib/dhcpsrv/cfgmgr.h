// Copyright (C) 2012 Internet Systems Consortium, Inc. ("ISC")
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
#include <dhcpsrv/pool.h>
#include <dhcpsrv/subnet.h>
#include <util/buffer.h>

#include <boost/shared_ptr.hpp>
#include <boost/noncopyable.hpp>

#include <map>
#include <string>
#include <vector>

namespace isc {
namespace dhcp {


/// @brief Configuration Manager
///
/// This singleton class holds the whole configuration for DHCPv4 and DHCPv6
/// servers. It currently holds information about zero or more subnets6.
/// Each subnet may contain zero or more pools. Pool4 and Pool6 is the most
/// basic "chunk" of configuration. It contains a range of assigneable
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

    /// @brief get IPv6 subnet by address
    ///
    /// Finds a matching subnet, based on an address. This can be used
    /// in two cases: when trying to find an appropriate lease based on
    /// a) relay link address (that must be the address that is on link)
    /// b) our global address on the interface the message was received on
    ///    (for directly connected clients)
    ///
    /// @param hint an address that belongs to a searched subnet
    Subnet6Ptr getSubnet6(const isc::asiolink::IOAddress& hint);

    /// @brief get IPv6 subnet by interface-id
    ///
    /// Another possibility to find a subnet is based on interface-id.
    ///
    /// @param interface_id content of interface-id option returned by a relay
    /// @todo This method is not currently supported.
    Subnet6Ptr getSubnet6(OptionPtr interface_id);

    /// @brief adds an IPv6 subnet
    void addSubnet6(const Subnet6Ptr& subnet);

    /// @todo: Add subnet6 removal routines. Currently it is not possible
    /// to remove subnets. The only case where subnet6 removal would be
    /// needed is a dynamic server reconfiguration - a use case that is not
    /// planned to be supported any time soon.

    /// @brief removes all subnets
    ///
    /// This method removes all existing subnets. It is used during
    /// reconfiguration - old configuration is wiped and new definitions
    /// are used to recreate subnets.
    ///
    /// @todo Implement more intelligent approach. Note that comparison
    /// between old and new configuration is tricky. For example: is
    /// 2000::/64 and 2000::/48 the same subnet or is it something
    /// completely new?
    void deleteSubnets6() {
        subnets6_.clear();
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
    Subnet4Ptr getSubnet4(const isc::asiolink::IOAddress& hint);

    /// @brief adds a subnet4
    void addSubnet4(const Subnet4Ptr& subnet);

    /// @brief removes all IPv4 subnets
    void removeSubnets4();
protected:

    /// @brief Protected constructor.
    ///
    /// This constructor is protected for 2 reasons. First, it forbids any
    /// instantiations of this class (CfgMgr is a singleton). Second, it
    /// allows derived class to instantiate it. That is useful for testing
    /// purposes.
    CfgMgr();

    /// @brief virtual desctructor
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
};

} // namespace isc::dhcp
} // namespace isc

#endif // CFGMGR_H
