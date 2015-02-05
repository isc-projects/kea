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
            // Index using values returned by the @c Host::getIPv4Resrvation.
            boost::multi_index::const_mem_fun<Host, const asiolink::IOAddress&,
                                               &Host::getIPv4Reservation>
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
    :resrv_(resrv), host_(host), subnet_id_(host ? host->getIPv6SubnetID() : 0) {
    }

    /// @brief Address or prefix reservation.
    const IPv6Resrv resrv_;

    /// @brief Pointer to the host object.
    HostPtr host_;

    /// @brief Value of the IPv6 Subnet-id
    const SubnetID subnet_id_;

    /// @brief Key extractor (used in the second composite key)
    const asiolink::IOAddress& getKey() const {
        return (resrv_.getPrefix());
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
                HostResrv6Tuple, const asiolink::IOAddress&, &HostResrv6Tuple::getKey>
        >,

        // Second index is used to search by (subnet_id, address) pair.
        // This is
        boost::multi_index::ordered_unique<

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
                    &HostResrv6Tuple::getKey
                >
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

}; // end of isc::dhcp namespace
}; // end of isc namespace

#endif // HOST_CONTAINER_H
