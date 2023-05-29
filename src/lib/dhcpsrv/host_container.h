// Copyright (C) 2014-2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef HOST_CONTAINER_H
#define HOST_CONTAINER_H

#include <dhcpsrv/host.h>
#include <dhcpsrv/subnet_id.h>
#include <boost/multi_index_container.hpp>
#include <boost/multi_index/composite_key.hpp>
#include <boost/multi_index/mem_fun.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/hashed_index.hpp>

namespace isc {
namespace dhcp {

/// @brief Multi-index container holding host reservations.
///
/// This container holds a collection of @c Host objects which can be retrieved
/// using various parameters. The typical use of this container is to search for
/// all @c Host objects which are identified by a specified identifier, i.e.
/// HW address or DUID.
///
/// @todo This container will be extended to search for @c Host objects
/// associated with a specific IPv4 address or IPv6 prefix/length.
///
/// @see http://www.boost.org/doc/libs/1_56_0/libs/multi_index/doc/index.html
typedef boost::multi_index_container<
    // This container stores pointers to Host objects.
    HostPtr,
    // Start specification of indexes here.
    boost::multi_index::indexed_by<
        // First index is used to search for the host using one of the
        // identifiers, i.e. HW address or DUID. The elements of this
        // index are non-unique because there may be multiple reservations
        // for the same host belonging to a different subnets.
        boost::multi_index::ordered_non_unique<
            // The index comprises actual identifier (HW address or DUID) in
            // a binary form and a type of the identifier which indicates
            // that it is HW address or DUID.
            boost::multi_index::composite_key<
                // Composite key uses members of the Host class.
                Host,
                // Binary identifier is retrieved from the Host class using
                // a getIdentifier method.
                boost::multi_index::const_mem_fun<
                    Host, const std::vector<uint8_t>&,
                    &Host::getIdentifier
                >,
                // Identifier type is retrieved from the Host class using
                // a getIdentifierType method.
                boost::multi_index::const_mem_fun<
                    Host, Host::IdentifierType,
                    &Host::getIdentifierType
                >
            >
        >,

        // Second index is used to search for the host using reserved IPv4
        // address.
        boost::multi_index::ordered_non_unique<
            // Index using values returned by the @c Host::getIPv4Reservation.
            boost::multi_index::const_mem_fun<Host, const asiolink::IOAddress&,
                                               &Host::getIPv4Reservation>
        >,

        // Third index is used to search for the host using IPv4 subnet id
        boost::multi_index::ordered_non_unique<
            // Index using values returned by the @c Host::getIPv4SubnetID
            boost::multi_index::const_mem_fun<Host, SubnetID,
                                              &Host::getIPv4SubnetID>
        >,

        // Forth index is used to search for the host using IPv6 subnet id
        boost::multi_index::ordered_non_unique<
            // Index using values returned by the @c Host::getIPv6SubnetID
            boost::multi_index::const_mem_fun<Host, SubnetID,
                                              &Host::getIPv6SubnetID>
        >,

        // Fifth index is used to search by increasing host id
        boost::multi_index::ordered_unique<
            // Index using values returned by the @c Host::getHostId
            boost::multi_index::const_mem_fun<Host, uint64_t,
                                              &Host::getHostId>
        >,

        // Sixth index is used to search for the host using hostname
        // (case-sensitive compare so the key is in lower case).
        boost::multi_index::ordered_non_unique<
            // Index using values returned by the @c Host::getLowerHostname
            boost::multi_index::const_mem_fun<Host, std::string,
                                              &Host::getLowerHostname>
        >
    >
> HostContainer;

/// @brief First index type in the @c HostContainer.
///
/// This index allows for searching for @c Host objects using an
/// identifier + identifier type tuple.
typedef HostContainer::nth_index<0>::type HostContainerIndex0;

/// @brief Results range returned using the @c HostContainerIndex0.
typedef std::pair<HostContainerIndex0::iterator,
                  HostContainerIndex0::iterator> HostContainerIndex0Range;

/// @brief Second index type in the @c HostContainer.
///
/// This index allows for searching for @c Host objects using a
/// reserved IPv4 address.
typedef HostContainer::nth_index<1>::type HostContainerIndex1;

/// @brief Results range returned using the @c HostContainerIndex1.
typedef std::pair<HostContainerIndex1::iterator,
                  HostContainerIndex1::iterator> HostContainerIndex1Range;

/// @brief Third index type in the @c HostContainer.
///
/// This index allows for searching for @c Host objects using a
/// IPv4 subnet id.
typedef HostContainer::nth_index<2>::type HostContainerIndex2;

/// @brief Results range returned using the @c HostContainerIndex2.
typedef std::pair<HostContainerIndex2::iterator,
                  HostContainerIndex2::iterator> HostContainerIndex2Range;

/// @brief Forth index type in the @c HostContainer.
///
/// This index allows for searching for @c Host objects using a
/// IPv6 subnet id.
typedef HostContainer::nth_index<3>::type HostContainerIndex3;

/// @brief Results range returned using the @c HostContainerIndex3.
typedef std::pair<HostContainerIndex3::iterator,
                  HostContainerIndex3::iterator> HostContainerIndex3Range;

/// @brief Fifth index type in the @c HostContainer.
///
/// This index allows for searching for @c Host objects using a host id.
typedef HostContainer::nth_index<4>::type HostContainerIndex4;

/// @brief Results range returned using the @c HostContainerIndex4.
typedef std::pair<HostContainerIndex4::iterator,
                  HostContainerIndex4::iterator> HostContainerIndex4Range;

/// @brief Sixth index type in the @c HostContainer.
///
/// This index allows for searching for @c Host objects using a hostname.
typedef HostContainer::nth_index<5>::type HostContainerIndex5;

/// @brief Defines one entry for the Host Container for v6 hosts
///
/// It's essentially a pair of (IPv6 reservation, Host pointer).
/// This structure is used as an intermediate structure in HostContainer6.
/// For a single host that has reservations for X addresses or prefixes, there
/// will be X HostResrv6Tuple structures.
struct HostResrv6Tuple {

    /// @brief Default constructor.
    ///
    /// @param resrv IPv6 address/prefix reservation
    /// @param host pointer to the host object
    HostResrv6Tuple(const IPv6Resrv& resrv, const HostPtr& host)
    : resrv_(resrv), host_(host), subnet_id_(host ? host->getIPv6SubnetID() : SUBNET_ID_GLOBAL) {
    }

    /// @brief Address or prefix reservation.
    const IPv6Resrv resrv_;

    /// @brief Pointer to the host object.
    HostPtr host_;

    /// @brief Value of the IPv6 Subnet-id
    const SubnetID subnet_id_;

    /// @brief Key extractor used in the second composite key
    const asiolink::IOAddress& getPrefix() const {
        return (resrv_.getPrefix());
    }

    /// @brief Key extractor used in the fourth composite key
    HostID getHostId() const {
        return (host_->getHostId());
    }
};

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

            // Address is extracted by calling IPv6Resrv::getPrefix()
            // and it will return an IOAddress object.
            boost::multi_index::const_mem_fun<
                HostResrv6Tuple, const asiolink::IOAddress&, &HostResrv6Tuple::getPrefix>
        >,

        // Second index is used to search by (subnet_id, address) pair.
        // This is
        boost::multi_index::ordered_non_unique<

            /// This is a composite key. It uses two keys: subnet-id and
            /// IPv6 address reservation.
            boost::multi_index::composite_key<

                // Composite key uses members of the HostResrv6Tuple class.
                HostResrv6Tuple,

                // First key extractor. Gets subnet-id as a member of the
                // HostResrv6Tuple structure.
                boost::multi_index::member<HostResrv6Tuple, const SubnetID,
                    &HostResrv6Tuple::subnet_id_>,

                // Second key extractor. Address is extracted by calling
                // IPv6Resrv::getPrefix() and it will return an IOAddress object.
                boost::multi_index::const_mem_fun<
                    HostResrv6Tuple, const asiolink::IOAddress&,
                    &HostResrv6Tuple::getPrefix
                >
           >
        >,

        // Third index is used to search for the host using IPv6 subnet id
        boost::multi_index::ordered_non_unique<
            // Index using values returned by the @c Host::getIPv6SubnetID
            boost::multi_index::member<HostResrv6Tuple, const SubnetID,
                                       &HostResrv6Tuple::subnet_id_>
        >,

        // Fourth index is used to search by increasing host id
        boost::multi_index::ordered_non_unique<
            // Index using values returned by the @c Host::getHostId
            boost::multi_index::const_mem_fun<HostResrv6Tuple, uint64_t,
                                              &HostResrv6Tuple::getHostId>
        >,

        // Fifth index is used to search by the reserved address.
        boost::multi_index::ordered_non_unique<
            boost::multi_index::const_mem_fun<
                HostResrv6Tuple, const asiolink::IOAddress&,
                &HostResrv6Tuple::getPrefix
            >
        >
    >
> HostContainer6;

/// @brief First index type in the @c HostContainer6.
///
/// This index allows for searching for @c Host objects using an
/// address.
typedef HostContainer6::nth_index<0>::type HostContainer6Index0;

/// @brief Results range returned using the @c HostContainer6Index0.
typedef std::pair<HostContainer6Index0::iterator,
                  HostContainer6Index0::iterator> HostContainer6Index0Range;

/// @brief Second index type in the @c HostContainer6.
///
/// This index allows for searching for @c Host objects using a
/// reserved (SubnetID, IPv6 address) tuple.
typedef HostContainer6::nth_index<1>::type HostContainer6Index1;

/// @brief Results range returned using the @c HostContainer6Index1.
typedef std::pair<HostContainer6Index1::iterator,
                  HostContainer6Index1::iterator> HostContainer6Index1Range;

/// @brief Third index type in the @c HostContainer6.
///
/// This index allows for searching for @c Host objects using a
/// IPv6 subnet id.
typedef HostContainer6::nth_index<2>::type HostContainer6Index2;

/// @brief Results range returned using the @c HostContainer6Index2.
typedef std::pair<HostContainer6Index2::iterator,
                  HostContainer6Index2::iterator> HostContainer6Index2Range;

/// @brief Fourth index type in the @c HostContainer6.
///
/// This index allows for searching for @c Host objects using a host id.
typedef HostContainer6::nth_index<3>::type HostContainer6Index3;

/// @brief Results range returned using the @c HostContainer6Index3.
typedef std::pair<HostContainer6Index3::iterator,
                  HostContainer6Index3::iterator> HostContainer6Index3Range;

/// @brief Fifth index type in the @c HostContainer6.
///
/// This index allows for searching for @c Host objects using an IP address.
typedef HostContainer6::nth_index<4>::type HostContainer6Index4;

/// @brief Results range returned using the @c HostContainer6Index4.
typedef std::pair<HostContainer6Index4::iterator,
                  HostContainer6Index4::iterator> HostContainer6Index4Range;

}; // end of isc::dhcp namespace
}; // end of isc namespace

#endif // HOST_CONTAINER_H
