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

#ifndef CFG_SUBNETS4_H
#define CFG_SUBNETS4_H

#include <asiolink/io_address.h>
#include <dhcpsrv/subnet.h>
#include <dhcpsrv/subnet_selector.h>
#include <boost/shared_ptr.hpp>

namespace isc {
namespace dhcp {

/// @brief Holds subnets configured for the DHCPv4 server.
///
/// This class holds a collection of subnets configured for the DHCPv4 server.
/// It allows for retrieving a subnet for the particular client using various
/// parameters extracted from the DHCPv4 message. These parameters must be
/// assigned to the appropriate members of the @c CfgSubnets4::Selector
/// structure.
///
/// See @c CfgSubnets4::selectSubnet documentation for more details on how the
/// subnet is selected for the client.
class CfgSubnets4 {
public:

    /// @brief Adds new subnet to the configuration.
    ///
    /// @param subnet Pointer to the subnet being added.
    ///
    /// @throw isc::DuplicateSubnetID If the subnet id for the new subnet
    /// duplicates id of an existing subnet.
    void add(const Subnet4Ptr& subnet);

    /// @brief Returns pointer to the collection of all IPv4 subnets.
    ///
    /// This is used in a hook (subnet4_select), where the hook is able
    /// to choose a different subnet. Server code has to offer a list
    /// of possible choices (i.e. all subnets).
    ///
    /// @return A pointer to const Subnet4 collection
    const Subnet4Collection* getAll() const {
        return (&subnets_);
    }

    /// @brief Returns pointer to the selected subnet.
    ///
    /// This method tries to retrieve the subnet for the client using various
    /// parameters extracted from the client's message using the following
    /// logic.
    ///
    /// If the giaddr value is set in the selector it means that the client's
    /// message was relayed. The subnet configuration allows for setting the
    /// relay address for each subnet to indicate that the subnet must be
    /// assigned when the packet was transmitted over the particular relay.
    /// This method first tries to match the giaddr with the relay addresses
    /// specified for all subnets. If the relay address for the subnet is equal
    /// to the address of the relay through which the message was transmitted,
    /// the particular subnet is returned.
    ///
    /// If the giaddr is not matched with any of the relay addresses in any
    /// subnet or the message was not relayed, the method will need to try to
    /// match one of the addresses in the client's message with the prefixes
    /// of the existing subnets. Depending whether it is a relayed message,
    /// message from the renewing client or a new allocation, the server will
    /// pick one of the following addresses for this matching:
    /// - giaddr - for relayed message
    /// - ciaddr - for renewing or rebinding client
    /// - source address - for the renewing client which didn't provide ciaddr
    /// - address on the local server's interface if this is a new allocation
    /// requested by the directly connected client
    ///
    /// If the address matches with a subnet, the subnet is returned.
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
    /// @throw isc::BadValue if the values in the subnet selector are invalid
    /// or they are insufficient to select a subnet.
    Subnet4Ptr selectSubnet(const SubnetSelector& selector) const;

    /// @brief Returns pointer to a subnet if provided address is in its range.
    ///
    /// This method returns a pointer to the subnet if the address passed in
    /// parameter is in range with this subnet. This is mainly used for unit
    /// testing. This method is also called by the
    /// @c selectSubnet(SubnetSelector).
    ///
    /// @todo This method requires performance improvement! It currently
    /// iterates over all existing subnets to find the one which fulfils
    /// the search criteria. The subnet storage is implemented as a simple
    /// STL vector which precludes fast searches using specific keys.
    /// Hence, full scan is required. To improve the search performance a
    /// different container type is required, e.g. multi-index container,
    /// or something of a similar functionality.
    ///
    /// @param address Address for which the subnet is searched.
    /// @param client_classes Optional parameter specifying the classes that
    /// the client belongs to.
    ///
    /// @return Pointer to the selected subnet or NULL if no subnet found.
    Subnet4Ptr selectSubnet(const asiolink::IOAddress& address,
                            const ClientClasses& client_classes
                            = ClientClasses()) const;

    /// @brief Updates statistics.
    ///
    /// This method updates statistics that are affected by the newly committed
    /// configuration. In particular, it updates the number of available addresses
    /// in each subnet. Other statistics may be added in the future. In general,
    /// these are statistics that are dependant only on configuration, so they are
    /// not expected to change until the next reconfiguration event.
    void updateStatistics();

    /// @brief Removes statistics.
    ///
    /// During commitment of a new configuration, we need to get rid of the old
    /// statistics for the old configuration. In particular, we need to remove
    /// anything related to subnets, as there may be fewer subnets in the new
    /// configuration and also subnet-ids may change.
    void removeStatistics();

private:

    /// @brief Checks that the IPv4 subnet with the given id already exists.
    ///
    /// @param subnet Subnet for which this function will check if the other
    /// subnet with equal id already exists.
    ///
    /// @return true if the duplicate subnet exists.
    bool isDuplicate(const Subnet4& subnet) const;

    /// @brief A container for IPv4 subnets.
    Subnet4Collection subnets_;

};

/// @name Pointer to the @c CfgSubnets4 objects.
//@{
/// @brief Non-const pointer.
typedef boost::shared_ptr<CfgSubnets4> CfgSubnets4Ptr;

/// @brief Const pointer.
typedef boost::shared_ptr<const CfgSubnets4> ConstCfgSubnets4Ptr;

//@}

}
}

#endif // CFG_SUBNETS4_H
