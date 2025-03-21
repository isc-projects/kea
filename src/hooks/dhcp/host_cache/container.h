// Copyright (C) 2018-2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef CONTAINER_H
#define CONTAINER_H

#include <dhcpsrv/host.h>
#include <dhcpsrv/subnet_id.h>
#include <boost/multi_index_container.hpp>
#include <boost/multi_index/composite_key.hpp>
#include <boost/multi_index/mem_fun.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/sequenced_index.hpp>
#include <boost/multi_index/hashed_index.hpp>
#include <boost/multi_index/identity.hpp>

namespace isc {
namespace host_cache {

/// @brief Tag for the sequenced index.
struct HostSequencedIndexTag { };

/// @brief Tag for the hashed index.
struct HostHashedIndexTag { };

/// @brief Tag for the index for searching by identifier.
struct HostIdentifierIndexTag { };

/// @brief Tag for the index for searching by reserved IPv4 address.
struct HostAddress4IndexTag { };

/// @brief Multi-index container holding host cache entries.
///
/// From host_container with least-recently-used support. This container
/// is similar to isc::dhcp::HostContainer, but there are two significant
/// differences: this one manages the order of the entries, so it's possible
/// to find the oldest ones and it's possible to find a host from IPv6
/// reservation. We could implement those changes in isc::dhcp::HostContainer,
/// but then the code would be slower. Here's a specialized clone of that
/// container here.
typedef boost::multi_index_container<
    // This container stores pointers to Host objects.
    dhcp::HostPtr,
    // Start specification of indexes here.
    boost::multi_index::indexed_by<
        // Sequenced index implements least-recently-used.
        boost::multi_index::sequenced<
            boost::multi_index::tag<HostSequencedIndexTag>
        >,
        // Hash index for direct retrieval.
        boost::multi_index::hashed_unique<
            boost::multi_index::tag<HostHashedIndexTag>,
            boost::multi_index::identity<dhcp::HostPtr>
        >,
        // This index is used to search for the host using one of the
        // identifiers, i.e. HW address or DUID. The elements of this
        // index are non-unique because there may be multiple reservations
        // for the same host belonging to a different subnets.
        boost::multi_index::ordered_non_unique<
            boost::multi_index::tag<HostIdentifierIndexTag>,
            // The index comprises actual identifier (HW address or DUID) in
            // a binary form and a type of the identifier which indicates
            // that it is HW address or DUID.
            boost::multi_index::composite_key<
                // Composite key uses members of the Host class.
                dhcp::Host,
                // Binary identifier is retrieved from the Host class using
                // a getIdentifier method.
                boost::multi_index::const_mem_fun<
                    dhcp::Host, const std::vector<uint8_t>&,
                    &dhcp::Host::getIdentifier
                >,
                // Identifier type is retrieved from the Host class using
                // a getIdentifierType method.
                boost::multi_index::const_mem_fun<
                    dhcp::Host, dhcp::Host::IdentifierType,
                    &dhcp::Host::getIdentifierType
                >
            >
        >,

        // This index is used to search for the host using reserved IPv4
        // address.
        boost::multi_index::ordered_non_unique<
            boost::multi_index::tag<HostAddress4IndexTag>,
            // Index using values returned by the @c Host::getIPv4Reservation.
            boost::multi_index::const_mem_fun<dhcp::Host,
                                              const asiolink::IOAddress&,
                                              &dhcp::Host::getIPv4Reservation>
        >
    >
> HostContainer;

/// @brief Sequenced index type in the @c HostContainer.
///
/// This index allows for searching for @c Host objects in sequence.
typedef HostContainer::index<HostSequencedIndexTag>::type HostContainerSequencedIndex;

/// @brief Hashed index type in the @c HostContainer.
///
/// This index allows for searching for @c Host objects by itself.
typedef HostContainer::index<HostHashedIndexTag>::type HostContainerHashedIndex;

/// @brief Identifier index type in the @c HostContainer.
///
/// This index allows for searching for @c Host objects using an
/// identifier + identifier type tuple.
typedef HostContainer::index<HostIdentifierIndexTag>::type HostContainerIdentifierIndex;

/// @brief Results range returned using the @c HostContainerIdentifierIndex.
typedef std::pair<HostContainerIdentifierIndex::iterator,
                  HostContainerIdentifierIndex::iterator> HostContainerIdentifierIndexRange;

/// @brief Reserved Ipv4 address index type in the @c HostContainer.
///
/// This index allows for searching for @c Host objects using a
/// reserved IPv4 address.
typedef HostContainer::index<HostAddress4IndexTag>::type HostContainerAddress4Index;

/// @brief Results range returned using the @c HostContainerAddress4Index.
typedef std::pair<HostContainerAddress4Index::iterator,
                  HostContainerAddress4Index::iterator> HostContainerAddress4IndexRange;

/// @brief Defines one entry for the Host Container for v6 hosts
///
/// It's essentially a pair of (IPv6 reservation, Host pointer).
/// This structure is used as an intermediate structure in Resv6Container.
/// For a single host that has reservations for X addresses or prefixes, there
/// will be X HostResrv6Tuple structures.
struct HostResrv6Tuple {

    /// @brief Default constructor.
    ///
    /// @param resrv IPv6 address/prefix reservation
    /// @param host pointer to the host object
    HostResrv6Tuple(const dhcp::IPv6Resrv& resrv, const dhcp::HostPtr& host)
    : resrv_(resrv), host_(host),
      subnet_id_(host ? host->getIPv6SubnetID() : dhcp::SUBNET_ID_UNUSED) {
    }

    /// @brief Address or prefix reservation.
    const dhcp::IPv6Resrv resrv_;

    /// @brief Pointer to the host object.
    dhcp::HostPtr host_;

    /// @brief Value of the IPv6 Subnet-id
    const dhcp::SubnetID subnet_id_;

    /// @brief Key extractor (used in the second composite key)
    const asiolink::IOAddress& getKey() const {
        return (resrv_.getPrefix());
    }
};

/// @brief Tag for the index for searching by address.
struct Resv6AddressIndexTag { };

/// @brief Tag for the index for searching by subnet and address
struct Resv6SubnetAddressIndexTag { };

/// @brief Multi-index container holding IPv6 reservations.
///
/// This container holds HostResrv6Tuples, i.e. pairs of (IPv6Resrv, HostPtr)
/// pieces of information. This is needed for efficiently finding a host
/// for a given IPv6 address or prefix.
typedef boost::multi_index_container<

    // This containers stores (IPv6Resrv, HostPtr) tuples
    HostResrv6Tuple,

    // Start specification of indexes here.
    boost::multi_index::indexed_by<

        // First index is used to search by an address.
        boost::multi_index::ordered_non_unique<
            boost::multi_index::tag<Resv6AddressIndexTag>,

            // Address is extracted by calling IPv6Resrv::getPrefix()
            // and it will return an IOAddress object.
            boost::multi_index::const_mem_fun<
                HostResrv6Tuple, const asiolink::IOAddress&, &HostResrv6Tuple::getKey>
        >,

        // Second index is used to search by (subnet_id, address) pair.
        boost::multi_index::ordered_unique<
            boost::multi_index::tag<Resv6SubnetAddressIndexTag>,

            /// This is a composite key. It uses two keys: subnet-id and
            /// IPv6 address reservation.
            boost::multi_index::composite_key<

                // Composite key uses members of the HostResrv6Tuple class.
                HostResrv6Tuple,

                // First key extractor. Gets subnet-id as a member of the
                // HostResrv6Tuple structure.
                boost::multi_index::member<HostResrv6Tuple,
                                           const dhcp::SubnetID,
                                           &HostResrv6Tuple::subnet_id_>,

                // Second key extractor. Address is extracted by calling
                // IPv6Resrv::getPrefix() and it will return an IOAddress object.
                boost::multi_index::const_mem_fun<
                    HostResrv6Tuple, const asiolink::IOAddress&,
                    &HostResrv6Tuple::getKey
                >
           >
        >
    >
> Resv6Container;

/// @brief First index type in the @c Resv6Container.
///
/// This index allows for searching for @c Host objects using an
/// address.
typedef Resv6Container::index<Resv6AddressIndexTag>::type
    Resv6ContainerAddressIndex;

/// @brief Results range returned using the @c Resv6ContainerAddressIndex.
typedef std::pair<Resv6ContainerAddressIndex::iterator,
                  Resv6ContainerAddressIndex::iterator> Resv6ContainerAddressIndexRange;

/// @brief Second index type in the @c Resv6Container.
///
/// This index allows for searching for @c Host objects using a
/// reserved (SubnetID, IPv6 address) tuple.
typedef Resv6Container::index<Resv6SubnetAddressIndexTag>::type
    Resv6ContainerSubnetAddressIndex;

/// @brief Results range returned using the @c Resv6ContainerSubnetAddressIndex.
typedef std::pair<Resv6ContainerSubnetAddressIndex::iterator,
                  Resv6ContainerSubnetAddressIndex::iterator> Resv6ContainerSubnetAddressIndexRange;

}; // end of isc::dhcp namespace
}; // end of isc namespace

#endif // CONTAINER_H
