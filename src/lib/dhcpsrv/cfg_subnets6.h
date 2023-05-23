// Copyright (C) 2014-2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef CFG_SUBNETS6_H
#define CFG_SUBNETS6_H

#include <asiolink/io_address.h>
#include <dhcp/option.h>
#include <dhcp/pkt6.h>
#include <cc/cfg_to_element.h>
#include <dhcpsrv/cfg_shared_networks.h>
#include <dhcpsrv/subnet.h>
#include <dhcpsrv/subnet_id.h>
#include <dhcpsrv/subnet_selector.h>
#include <util/optional.h>
#include <boost/shared_ptr.hpp>
#include <string>

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
class CfgSubnets6 : public isc::data::CfgToElement {
public:

    /// @brief Adds new subnet to the configuration.
    ///
    /// @param subnet Pointer to the subnet being added.
    ///
    /// @throw isc::DuplicateSubnetID If the subnet id for the new subnet
    /// duplicates id of an existing subnet.
    void add(const Subnet6Ptr& subnet);

    /// @brief Replaces subnet in the configuration.
    ///
    /// This method replaces a subnet by another subnet with the same ID.
    /// The prefix should be the same too.
    ///
    /// @param subnet Pointer to the subnet being updated.
    /// @throw BadValue if the subnet to update does not exit.
    /// @return Pointer to the replaced subnet or NULL if it failed.
    Subnet6Ptr replace(const Subnet6Ptr& subnet);

    /// @brief Removes subnet from the configuration.
    ///
    /// @param subnet Pointer to the subnet to be removed.
    ///
    /// @throw isc::BadValue if such subnet doesn't exist.
    void del(const ConstSubnet6Ptr& subnet);

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
    void merge(CfgOptionDefPtr cfg_def, CfgSharedNetworks6Ptr networks,
               CfgSubnets6& other);

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
    /// @return Pointer to the @c Subnet6 object or null pointer if such
    /// subnet doesn't exist.
    ConstSubnet6Ptr getBySubnetId(const SubnetID& subnet_id) const;

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
    /// @param subnet_prefix Subnet prefix, e.g. 2001:db8:1::/64
    ///
    /// @return Pointer to the @c Subnet6 object or null pointer if such
    /// subnet doesn't exist.
    ConstSubnet6Ptr getByPrefix(const std::string& subnet_prefix) const;

    /// @brief Build selector from a client's message.
    ///
    /// @note: code moved from server.
    ///
    /// @param query client's message.
    /// @return filled selector.
    static SubnetSelector initSelector(const Pkt6Ptr& query);

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
    Subnet6Ptr selectSubnet(const SubnetSelector& selector) const;

    /// @brief Returns subnet with specified subnet-id value
    ///
    /// Warning: this method uses full scan. Its use is not recommended for
    /// packet processing.
    /// Please use @ref getBySubnetId instead when possible.
    ///
    /// @return Subnet (or NULL)
    Subnet6Ptr getSubnet(const SubnetID id) const;

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
    /// to find the one which fulfills the search criteria. The subnet storage
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
    /// and prefixes in each subnet. Other statistics may be added in the future. In
    /// general, these are statistics that are dependent only on configuration, so
    /// they are not expected to change until the next reconfiguration event.
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

    /// @brief Selects a subnet using the interface name.
    ///
    /// This method searches for the subnet using the name of the interface.
    /// If any of the subnets is explicitly associated with the interface
    /// name, the subnet is returned.
    ///
    /// @todo This method requires performance improvement! It currently
    /// iterates over all existing subnets to find the one which fulfills
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
    /// iterates over all existing subnets to find the one which fulfills
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
