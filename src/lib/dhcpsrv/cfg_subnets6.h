// Copyright (C) 2014-2015 Internet Systems Consortium, Inc. ("ISC")
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

#ifndef CFG_SUBNETS6_H
#define CFG_SUBNETS6_H

#include <asiolink/io_address.h>
#include <dhcp/option.h>
#include <dhcpsrv/subnet.h>
#include <dhcpsrv/subnet_selector.h>
#include <util/optional_value.h>
#include <boost/shared_ptr.hpp>

namespace isc {
namespace dhcp {

/// @brief Holds subnets configured for the DHCPv6 server.
///
/// This class holds a collection of subnets configured for the DHCPv6 server.
/// It allows for retrieving a subnet for the particular client using various
/// parameters extracted from the DHCPv6 message. These parameters must be
/// assigned to the appropriate members of the @c SubnetSelector structure.
///
/// See @c CfgSubnets6::selectSubnet documentation for more details on how the subnet
/// is selected for the client.
class CfgSubnets6 {
public:

    /// @brief Adds new subnet to the configuration.
    ///
    /// @param subnet Pointer to the subnet being added.
    ///
    /// @throw isc::DuplicateSubnetID If the subnet id for the new subnet
    /// duplicates id of an existing subnet.
    void add(const Subnet6Ptr& subnet);

    /// @brief Returns pointer to the collection of all IPv6 subnets.
    ///
    /// This is used in a hook (subnet6_select), where the hook is able
    /// to choose a different subnet. Server code has to offer a list
    /// of possible choices (i.e. all subnets).
    ///
    /// @return A pointer to const Subnet6 collection
    const Subnet6Collection* getAll() const {
        return (&subnets_);
    }

    /// @brief Selects a subnet using parameters specified in the selector.
    ///
    /// This method tries to retrieve the subnet for the client using various
    /// parameters extracted from the client's message using the following
    /// logic.
    ///
    /// If the relay agent link address is set to zero it is assumed that
    /// the subnet is selected for the directly connected client.
    /// In this case it is checked if there is any subnet associated with the
    /// interface over which the message has been received. If there is no
    /// subnet explicitly associated with this interface the client's address
    /// will be used to check if the address is in range with any of the
    /// subnets.
    ///
    /// If the message was relayed it is possible that the relay agent has
    /// appended an Interface ID option. If this option is present, the method
    /// will check if it matches with any explicitly specified interface id
    /// for any subnet. If it does, the subnet is returned. Otherwise, the
    /// relay agents link address is used to select the subnet. In this case,
    /// the method will first check if this link address is explicitly
    /// associated with any subnet. If not, it is checked if the link address
    /// is in range with any of the subnets.
    ///
    /// @todo This method requires performance improvement! It currently
    /// iterates over all existing subnets (possibly a couple of times)
    /// to find the one which fulfils the search criteria. The subnet storage
    /// is implemented as a simple STL vector which precludes fast searches
    /// using specific keys. Hence, full scan is required. To improve the
    /// search performance a different container type is required, e.g.
    /// multi-index container, or something of a similar functionality.
    ///
    /// @param selector Const reference to the selector structure which holds
    /// various information extracted from the client's packet which are used
    /// to find appropriate subnet.
    ///
    /// @return Pointer to the selected subnet or NULL if no subnet found.
    Subnet6Ptr selectSubnet(const SubnetSelector& selector) const;

    /// @brief Selects the subnet using a specified address.
    ///
    /// This method searches for the subnet using the specified address. If
    /// the specified address is a link address on the relay agent (which is
    /// indicated by the 3rd argument) the method will first try to match the
    /// specified address with the relay addresses explicitly specified for
    /// existing subnets. If no match is found, the method will check if the
    /// address is in range with any of the subnets.
    ///
    /// If the address is not a relay agent link address (@c is_relay_address
    /// is set to false), the method will simply check if the address is in
    /// range with any of the subnets.
    ///
    /// @note This method is mainly to be used in unit tests, which often
    /// require sanity-checking if the subnet exists for the particular
    /// address. For other purposes the @c selectSubnet(SubnetSelector) should
    /// rather be used instead.
    ///
    /// @todo This method requires performance improvement! It currently
    /// iterates over all existing subnets (possibly a couple of times)
    /// to find the one which fulfils the search criteria. The subnet storage
    /// is implemented as a simple STL vector which precludes fast searches
    /// using specific keys. Hence, full scan is required. To improve the
    /// search performance a different container type is required, e.g.
    /// multi-index container, or something of a similar functionality.
    ///
    /// @param address Address for which the subnet is searched.
    /// @param client_classes Optional parameter specifying the classes that
    /// the client belongs to.
    /// @param is_relay_address Specifies if the provided address is an
    /// address of the relay agent (true) or not (false).
    ///
    /// @return Pointer to the selected subnet or NULL if no subnet found.
    Subnet6Ptr
    selectSubnet(const asiolink::IOAddress& address,
                 const ClientClasses& client_classes = ClientClasses(),
                 const bool is_relay_address = false) const;

    /// @brief Updates statistics.
    ///
    /// This method updates statistics that are affected by the newly committed
    /// configuration. In particular, it updates the number of available addresses
    /// and prefixes in each subnet. Other statistics may be added in the future. In
    /// general, these are statistics that are dependant only on configuration, so
    /// they are not expected to change until the next reconfiguration event.
    void updateStatistics();

    /// @brief Removes statistics.
    ///
    /// During commitment of a new configuration, we need to get rid of the old
    /// statistics for the old configuration. In particular, we need to remove
    /// anything related to subnets, as there may be fewer subnets in the new
    /// configuration and also subnet-ids may change.
    void removeStatistics();

private:

    /// @brief Selects a subnet using the interface name.
    ///
    /// This method searches for the subnet using the name of the interface.
    /// If any of the subnets is explicitly associated with the interface
    /// name, the subnet is returned.
    ///
    /// @todo This method requires performance improvement! It currently
    /// iterates over all existing subnets to find the one which fulfils
    /// the search criteria. The subnet storage is implemented as a
    /// simple STL vector which precludes fast searches using specific
    /// keys. Hence, full scan is required. To improve the search
    /// performance a different container type is required, e.g.
    /// multi-index container, or something of a similar functionality.
    ///
    /// @param iface_name Interface name.
    /// @param client_classes Optional parameter specifying the classes that
    /// the client belongs to.
    ///
    /// @return Pointer to the selected subnet or NULL if no subnet found.
    Subnet6Ptr
    selectSubnet(const std::string& iface_name,
                 const ClientClasses& client_classes) const;

    /// @brief Selects a subnet using Interface ID option.
    ///
    /// This method searches for the subnet using the Interface ID option
    /// inserted by the relay agent to the message from a client. If any
    /// of the subnets is explicitly associated with that interface id, the
    /// subnet is returned.
    ///
    /// @todo This method requires performance improvement! It currently
    /// iterates over all existing subnets to find the one which fulfils
    /// the search criteria. The subnet storage is implemented as a
    /// simple STL vector which precludes fast searches using specific
    /// keys. Hence, full scan is required. To improve the search
    /// performance a different container type is required, e.g.
    /// multi-index container, or something of a similar functionality.
    ///
    /// @param interface_id An instance of the Interface ID option received
    /// from the client.
    /// @param client_classes Optional parameter specifying the classes that
    /// the client belongs to.
    ///
    /// @return Pointer to the selected subnet or NULL if no subnet found.
    Subnet6Ptr
    selectSubnet(const OptionPtr& interface_id,
                 const ClientClasses& client_classes) const;

    /// @brief Checks that the IPv6 subnet with the given id already exists.
    ///
    /// @param subnet Subnet for which this function will check if the other
    /// subnet with equal id already exists.
    ///
    /// @return true if the duplicate subnet exists.
    bool isDuplicate(const Subnet6& subnet) const;

    /// @brief A container for IPv6 subnets.
    Subnet6Collection subnets_;

};

/// @name Pointer to the @c CfgSubnets6 objects.
//@{
/// @brief Non-const pointer.
typedef boost::shared_ptr<CfgSubnets6> CfgSubnets6Ptr;

/// @brief Const pointer.
typedef boost::shared_ptr<const CfgSubnets6> ConstCfgSubnets6Ptr;

//@}

}
}

#endif // CFG_SUBNETS6_H
