// Copyright (C) 2015 Internet Systems Consortium, Inc. ("ISC")
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

#ifndef INMEMORY_LEASE_STORAGE_H
#define INMEMORY_LEASE_STORAGE_H

#include <asiolink/io_address.h>
#include <dhcpsrv/lease.h>
#include <dhcpsrv/subnet_id.h>

#include <boost/multi_index/indexed_by.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/mem_fun.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index_container.hpp>
#include <boost/multi_index/composite_key.hpp>

#include <vector>

namespace isc {
namespace dhcp {

/// @brief A multi index container holding DHCPv6 leases.
///
/// The leases in the container may be accessed using different indexes:
/// - using an IPv6 address,
/// - using a composite index: DUID, IAID and lease type.
typedef boost::multi_index_container<
    // It holds pointers to Lease6 objects.
    Lease6Ptr,
    boost::multi_index::indexed_by<
        // Specification of the first index starts here.
        // This index sorts leases by IPv6 addresses represented as
        // IOAddress objects.
        boost::multi_index::ordered_unique<
            boost::multi_index::member<Lease, isc::asiolink::IOAddress, &Lease::addr_>
        >,

        // Specification of the second index starts here.
        boost::multi_index::ordered_non_unique<
            // This is a composite index that will be used to search for
            // the lease using three attributes: DUID, IAID and lease type.
            boost::multi_index::composite_key<
                Lease6,
                // The DUID can be retrieved from the Lease6 object using
                // a getDuidVector const function.
                boost::multi_index::const_mem_fun<Lease6, const std::vector<uint8_t>&,
                                                  &Lease6::getDuidVector>,
                // The two other ingredients of this index are IAID and
                // lease type.
                boost::multi_index::member<Lease6, uint32_t, &Lease6::iaid_>,
                boost::multi_index::member<Lease6, Lease::Type, &Lease6::type_>
            >
        >
     >
> Lease6Storage; // Specify the type name of this container.

/// @brief A multi index container holding DHCPv4 leases.
///
/// The leases in the container may be accessed using different indexes:
/// - IPv6 address,
/// - composite index: HW address and subnet id,
/// - composite index: client id and subnet id,
/// - composite index: HW address, client id and subnet id
typedef boost::multi_index_container<
    // It holds pointers to Lease4 objects.
    Lease4Ptr,
    // Specification of search indexes starts here.
    boost::multi_index::indexed_by<
        // Specification of the first index starts here.
        // This index sorts leases by IPv4 addresses represented as
        // IOAddress objects.
        boost::multi_index::ordered_unique<
            // The IPv4 address are held in addr_ members that belong to
            // Lease class.
            boost::multi_index::member<Lease, isc::asiolink::IOAddress, &Lease::addr_>
        >,

        // Specification of the second index starts here.
        boost::multi_index::ordered_non_unique<
            // This is a composite index that combines two attributes of the
            // Lease4 object: hardware address and subnet id.
            boost::multi_index::composite_key<
                Lease4,
                // The hardware address is held in the hwaddr_ member of the
                // Lease4 object, which is a HWAddr object. Boost does not
                // provide a key extractor for getting a member of a member,
                // so we need a simple method for that.
                boost::multi_index::const_mem_fun<Lease, const std::vector<uint8_t>&,
                                                  &Lease::getHWAddrVector>,
                // The subnet id is held in the subnet_id_ member of Lease4
                // class. Note that the subnet_id_ is defined in the base
                // class (Lease) so we have to point to this class rather
                // than derived class: Lease4.
                boost::multi_index::member<Lease, SubnetID, &Lease::subnet_id_>
            >
        >,

        // Specification of the third index starts here.
        boost::multi_index::ordered_non_unique<
            // This is a composite index that uses two values to search for a
            // lease: client id and subnet id.
            boost::multi_index::composite_key<
                Lease4,
                // The client id can be retrieved from the Lease4 object by
                // calling getClientIdVector const function.
                boost::multi_index::const_mem_fun<Lease4, const std::vector<uint8_t>&,
                                                  &Lease4::getClientIdVector>,
                // The subnet id is accessed through the subnet_id_ member.
                boost::multi_index::member<Lease, uint32_t, &Lease::subnet_id_>
            >
        >,

        // Specification of the fourth index starts here.
        boost::multi_index::ordered_non_unique<
            // This is a composite index that uses three values to search for a
            // lease: client id, HW address and subnet id.
            boost::multi_index::composite_key<
                Lease4,
                // The client id can be retrieved from the Lease4 object by
                // calling getClientIdVector const function.
                boost::multi_index::const_mem_fun<Lease4, const std::vector<uint8_t>&,
                                                  &Lease4::getClientIdVector>,
                // The hardware address is held in the hwaddr_ object. We can
                // access the raw data using lease->hwaddr_->hwaddr_, but Boost
                // doesn't seem to provide a way to use member of a member for this,
                // so we need a simple key extractor method (getHWAddrVector).
                boost::multi_index::const_mem_fun<Lease, const std::vector<uint8_t>&,
                                                  &Lease::getHWAddrVector>,
                // The subnet id is accessed through the subnet_id_ member.
                boost::multi_index::member<Lease, SubnetID, &Lease::subnet_id_>
            >
        >
    >
> Lease4Storage; // Specify the type name for this container.

} // end of isc::dhcp namespace
} // end of isc namespace

#endif // INMEMORY_LEASE_STORAGE_H
