// Copyright (C) 2014-2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef CFG_SUBNETS4_H
#define CFG_SUBNETS4_H

#include <asiolink/io_address.h>
#include <cc/cfg_to_element.h>
#include <dhcp/pkt4.h>
#include <dhcpsrv/cfg_shared_networks.h>
#include <dhcpsrv/subnet.h>
#include <dhcpsrv/subnet_id.h>
#include <dhcpsrv/subnet_selector.h>
#include <boost/shared_ptr.hpp>
#include <string>

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
class CfgSubnets4 : public isc::data::CfgToElement {
public:

    /// @brief Adds new subnet to the configuration.
    ///
    /// @param subnet Pointer to the subnet being added.
    ///
    /// @throw isc::DuplicateSubnetID If the subnet id for the new subnet
    /// duplicates id of an existing subnet.
    void add(const Subnet4Ptr& subnet);

    /// @brief Replaces subnet in the configuration.
    ///
    /// This method replaces a subnet by another subnet with the same ID.
    /// The prefix should be the same too.
    ///
    /// @param subnet Pointer to the subnet being updated.
    /// @throw BadValue if the subnet to update does not exit.
    /// @return Pointer to the replaced subnet or NULL if it failed.
    Subnet4Ptr replace(const Subnet4Ptr& subnet);

    /// @brief Removes subnet from the configuration.
    ///
    /// @param subnet Pointer to the subnet to be removed.
    ///
    /// @throw isc::BadValue if such subnet doesn't exist.
    void del(const ConstSubnet4Ptr& subnet);

    /// @brief Removes subnet from the configuration.
    ///
    /// @param subnet_id Identifier of the subnet to be removed.
    ///
    /// @throw isc::BadValue if such subnet doesn't exist.
    void del(const SubnetID& subnet_id);

    /// @brief Merges specified subnet configuration into this configuration.
    ///
    /// This method merges subnets from the @c other configuration into this
    /// configuration. The general rule is that existing subnets are replaced
    /// by the subnets from @c other. If there is no corresponding subnet in
    /// this configuration the subnet from @c other configuration is inserted.
    ///
    /// The complexity of the merge process stems from the associations between
    /// the subnets and shared networks.  It is assumed that subnets in @c other
    /// are the authority on their shared network assignments. It is also
    /// assumed that @ networks is the list of shared networks that should be
    /// used in making assignments.  The general concept is that the overarching
    /// merge process will first merge shared networks and then pass that list
    /// of networks into this method. Subnets from @c other are then merged
    /// into this configuration as follows:
    ///
    /// For each subnet in @c other:
    ///
    /// - If a subnet of the same ID already exists in this configuration:
    ///    -# If it belongs to a shared network, remove it from that network
    ///    -# Remove the subnet from this configuration and discard it
    ///
    /// - Create the subnet's option instance, as well as any options
    ///   that belong to any of the subnet's pools.
    /// - Add the subnet from @c other to this configuration.
    /// - If that subnet is associated to shared network, find that network
    ///   in @ networks and add that subnet to it.
    ///
    /// @warning The merge operation affects the @c other configuration.
    /// Therefore, the caller must not rely on the data held in the @c other
    /// object after the call to @c merge. Also, the data held in @c other must
    /// not be modified after the call to @c merge because it may affect the
    /// merged configuration.
    ///
    /// @param cfg_def set of user-defined option definitions to use
    /// when creating option instances.
    /// @param networks collection of shared networks that to which assignments
    /// should be added. In other words, the list of shared networks that belong
    /// to the same SrvConfig instance we are merging into.
    /// @param other the subnet configuration to be merged into this
    /// configuration.
    void merge(CfgOptionDefPtr cfg_def, CfgSharedNetworks4Ptr networks,
               CfgSubnets4& other);

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

    /// @brief Returns const pointer to a subnet identified by the specified
    /// subnet identifier.
    ///
    /// The const pointer is returned by this method to prevent a caller from
    /// modifying the subnet configuration. Modifications to subnet configuration
    /// is dangerous and must be done carefully. The subnets' configuration is
    /// held in the multi index container and any modifications to the subnet
    /// id or subnet prefix must trigger re-indexing of multi index container.
    /// There is no possibility to enforce this when the non-const pointer is
    /// returned.
    ///
    /// @param subnet_id Subnet identifier.
    ///
    /// @return Pointer to the @c Subnet4 object or null pointer if such
    /// subnet doesn't exist.
    ConstSubnet4Ptr getBySubnetId(const SubnetID& subnet_id) const;

    /// @brief Returns const pointer to a subnet which matches the specified
    /// prefix in the canonical form.
    ///
    /// The const pointer is returned by this method to prevent a caller from
    /// modifying the subnet configuration. Modifications to subnet configuration
    /// is dangerous and must be done carefully. The subnets' configuration is
    /// held in the multi index container and any modifications to the subnet
    /// id or subnet prefix must trigger re-indexing of multi index container.
    /// There is no possibility to enforce this when the non-const pointer is
    /// returned.
    ///
    /// @param subnet_prefix Subnet prefix, e.g. 10.2.3.0/24
    ///
    /// @return Pointer to the @c Subnet4 object or null pointer if such
    /// subnet doesn't exist.
    ConstSubnet4Ptr getByPrefix(const std::string& subnet_prefix) const;

    /// @brief Checks if specified server identifier has been specified for
    /// any subnet.
    ///
    /// @param server_id Server identifier.
    ///
    /// @return true if there is a subnet with a specified server identifier.
    bool hasSubnetWithServerId(const asiolink::IOAddress& server_id) const;

    /// @brief Build selector from a client's message.
    ///
    /// @note: code moved from server.
    ///
    /// @param query client's message.
    /// @return filled selector.
    static SubnetSelector initSelector(const Pkt4Ptr& query);

    /// @brief Returns a pointer to the selected subnet.
    ///
    /// This method tries to retrieve the subnet for the client using various
    /// parameters extracted from the client's message using the following
    /// logic.
    ///
    /// First when link select suboption of relay agent information option
    /// or subnet select option in this order exists the address is used
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
    /// to find the one which fulfills the search criteria. The subnet storage
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

    /// @brief Returns subnet with specified subnet-id value
    ///
    /// Warning: this method uses full scan. Its use is not recommended for
    /// packet processing.
    /// Please use @ref getBySubnetId instead when possible.
    ///
    /// @return Subnet (or NULL)
    Subnet4Ptr getSubnet(const SubnetID id) const;

    /// @brief Returns a pointer to a subnet if provided address is in its range.
    ///
    /// This method returns a pointer to the subnet if the address passed in
    /// parameter is in range with this subnet. This is mainly used for unit
    /// testing. This method is also called by the
    /// @c selectSubnet(SubnetSelector).
    ///
    /// @todo This method requires performance improvement! It currently
    /// iterates over all existing subnets to find the one which fulfills
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

    /// @brief Returns a pointer to a subnet if provided interface name matches.
    ///
    /// This method returns a pointer to the subnet if the interface name passed
    /// in parameter iface matches that of a subnet. This is mainly used for matching
    /// local incoming traffic, even when the addresses on local interfaces do
    /// not match a subnet definition. This method is also called by the
    /// @c selectSubnet(SubnetSelector).
    ///
    /// @todo This method requires performance improvement! It currently
    /// iterates over all existing subnets to find the one which fulfills
    /// the search criteria. The subnet storage is implemented as a simple
    /// STL vector which precludes fast searches using specific keys.
    /// Hence, full scan is required. To improve the search performance a
    /// different container type is required, e.g. multi-index container,
    /// or something of a similar functionality.
    ///
    /// @param iface name of the interface to be matched.
    /// @param client_classes Optional parameter specifying the classes that
    /// the client belongs to.
    ///
    /// @return Pointer to the selected subnet or NULL if no subnet found.
    Subnet4Ptr selectSubnet(const std::string& iface,
                            const ClientClasses& client_classes) const;

    /// @brief Attempts to do subnet selection based on DHCP4o6 information
    ///
    /// The algorithm implemented is as follows:
    ///
    /// - First: try to match IPv6 subnet (4o6-subnet parameter) with the
    ///   remote IPv6 address of the incoming packet
    /// - Second: try to match interface-id (4o6-interface-id parameter)
    ///   with the interface-id option in the incoming 4o6 packet
    /// - Third: try to match interface-name (4o6-interface parameter)
    ///   with the name of the interface the incoming 4o6 packet was
    ///   received over.
    ///
    /// @todo: Add additional selection criteria. See
    ///  https://gitlab.isc.org/isc-projects/kea/wikis/designs/dhcpv4o6-design for details.
    ///
    /// @param selector Const reference to the selector structure which holds
    /// various information extracted from the client's packet which are used
    /// to find appropriate subnet.
    /// @return Pointer to the selected subnet or NULL if no subnet found.
    Subnet4Ptr
    selectSubnet4o6(const SubnetSelector& selector) const;

    /// @brief Convert a link address into a link set.
    ///
    /// Given a link address this returns the ordered list aka set of id
    /// of subnets the address belongs to. It also sets the minimum link
    /// length when there is at least one subnet.
    ///
    /// @param link_addr The link address.
    /// @param[out] link_len The minimum link length.
    /// @return The set of subnet ids the link address belongs to.
    SubnetIDSet getLinks(const asiolink::IOAddress& link_addr,
                         uint8_t& link_len) const;

    /// @brief Updates statistics.
    ///
    /// This method updates statistics that are affected by the newly committed
    /// configuration. In particular, it updates the number of available addresses
    /// in each subnet. Other statistics may be added in the future. In general,
    /// these are statistics that are dependent only on configuration, so they are
    /// not expected to change until the next reconfiguration event.
    void updateStatistics();

    /// @brief Removes statistics.
    ///
    /// During commitment of a new configuration, we need to get rid of the old
    /// statistics for the old configuration. In particular, we need to remove
    /// anything related to subnets, as there may be fewer subnets in the new
    /// configuration and also subnet-ids may change.
    void removeStatistics();

    /// @brief Calls @c initAllocatorsAfterConfigure for each subnet.
    void initAllocatorsAfterConfigure();

    /// @brief Clears all subnets from the configuration.
    void clear();

    /// @brief Unparse a configuration object
    ///
    /// @return a pointer to unparsed configuration
    virtual isc::data::ElementPtr toElement() const;

private:

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
