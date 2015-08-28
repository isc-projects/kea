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

#ifndef MEMFILE_LEASE_STORAGE_H
#define MEMFILE_LEASE_STORAGE_H

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


/// @brief Tag for indexes by address.
struct AddressIndexTag { };

/// @brief Tag for indexes by DUID, IAID, lease type tuple.
struct DuidIaidTypeIndexTag { };

/// @brief Tag for indexes by expiration time.
struct ExpirationIndexTag { };

/// @brief Tag for indexes by HW address, subnet identifier tuple.
struct HWAddressSubnetIdIndexTag { };

/// @brief Tag for indexes by client and subnet identifiers.
struct ClientIdSubnetIdIndexTag { };

/// @brief Tag for indexes by client id, HW address and subnet id.
struct ClientIdHWAddressSubnetIdIndexTag { };

/// @name Multi index containers holding DHCPv4 and DHCPv6 leases.
///
//@{

/// @brief A multi index container holding DHCPv6 leases.
///
/// The leases in the container may be accessed using different indexes:
/// - using an IPv6 address,
/// - using a composite index: DUID, IAID and lease type.
/// - using a composite index: boolean flag indicating if the state is
///   "expired-reclaimed" and expiration time.
///
/// Indexes can be accessed using the index number (from 0 to 2) or a
/// name tag. It is recommended to use the tags to access indexes as
/// they do not depend on the order of indexes in the container.
typedef boost::multi_index_container<
    // It holds pointers to Lease6 objects.
    Lease6Ptr,
    boost::multi_index::indexed_by<
        // Specification of the first index starts here.
        // This index sorts leases by IPv6 addresses represented as
        // IOAddress objects.
        boost::multi_index::ordered_unique<
            boost::multi_index::tag<AddressIndexTag>,
            boost::multi_index::member<Lease, isc::asiolink::IOAddress, &Lease::addr_>
        >,

        // Specification of the second index starts here.
        boost::multi_index::ordered_non_unique<
            boost::multi_index::tag<DuidIaidTypeIndexTag>,
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
        >,

        // Specification of the third index starts here.
        boost::multi_index::ordered_non_unique<
            boost::multi_index::tag<ExpirationIndexTag>,
            // This is a composite index that will be used to search for
            // the expired leases. Depending on the value of the first component
            // of the search key, the reclaimed or not reclaimed leases will can
            // be searched.
            boost::multi_index::composite_key<
                Lease6,
                // The boolean value specifying if lease is reclaimed or not.
                boost::multi_index::const_mem_fun<Lease, bool,
                                                  &Lease::stateExpiredReclaimed>,
                // Lease expiration time.
                boost::multi_index::const_mem_fun<Lease, int64_t,
                                                  &Lease::getExpirationTime>
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
/// - using a composite index: boolean flag indicating if the state is
///   "expired-reclaimed" and expiration time.
///
/// Indexes can be accessed using the index number (from 0 to 4) or a
/// name tag. It is recommended to use the tags to access indexes as
/// they do not depend on the order of indexes in the container.
typedef boost::multi_index_container<
    // It holds pointers to Lease4 objects.
    Lease4Ptr,
    // Specification of search indexes starts here.
    boost::multi_index::indexed_by<
        // Specification of the first index starts here.
        // This index sorts leases by IPv4 addresses represented as
        // IOAddress objects.
        boost::multi_index::ordered_unique<
            boost::multi_index::tag<AddressIndexTag>,
            // The IPv4 address are held in addr_ members that belong to
            // Lease class.
            boost::multi_index::member<Lease, isc::asiolink::IOAddress, &Lease::addr_>
        >,

        // Specification of the second index starts here.
        boost::multi_index::ordered_non_unique<
            boost::multi_index::tag<HWAddressSubnetIdIndexTag>,
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
            boost::multi_index::tag<ClientIdSubnetIdIndexTag>,
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
            boost::multi_index::tag<ClientIdHWAddressSubnetIdIndexTag>,
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
        >,

        // Specification of the fifth index starts here.
        boost::multi_index::ordered_non_unique<
            boost::multi_index::tag<ExpirationIndexTag>,
            // This is a composite index that will be used to search for
            // the expired leases. Depending on the value of the first component
            // of the search key, the reclaimed or not reclaimed leases will can
            // be searched.
            boost::multi_index::composite_key<
                Lease4,
                // The boolean value specifying if lease is reclaimed or not.
                boost::multi_index::const_mem_fun<Lease, bool,
                                                  &Lease::stateExpiredReclaimed>,
                // Lease expiration time.
                boost::multi_index::const_mem_fun<Lease, int64_t,
                                                  &Lease::getExpirationTime>
            >
        >
    >
> Lease4Storage; // Specify the type name for this container.

//@}

/// @name Indexes used by the multi index containers
///
//@{

/// @brief DHCPv6 lease storage index by address.
typedef Lease6Storage::index<AddressIndexTag>::type Lease6StorageAddressIndex;

/// @brief DHCPv6 lease storage index by DUID, IAID, lease type.
typedef Lease6Storage::index<DuidIaidTypeIndexTag>::type Lease6StorageDuidIaidTypeIndex;

/// @brief DHCPv6 lease storage index by expiration time.
typedef Lease6Storage::index<ExpirationIndexTag>::type Lease6StorageExpirationIndex;

/// @brief DHCPv4 lease storage index by address.
typedef Lease4Storage::index<AddressIndexTag>::type Lease4StorageAddressIndex;

/// @brief DHCPv4 lease storage index by exiration time.
typedef Lease4Storage::index<ExpirationIndexTag>::type Lease4StorageExpirationIndex;

/// @brief DHCPv4 lease storage index by HW address and subnet identifier.
typedef Lease4Storage::index<HWAddressSubnetIdIndexTag>::type
Lease4StorageHWAddressSubnetIdIndex;

/// @brief DHCPv4 lease storage index by client and subnet identifier.
typedef Lease4Storage::index<ClientIdSubnetIdIndexTag>::type
Lease4StorageClientIdSubnetIdIndex;

/// @brief DHCPv4 lease storage index by client id, HW address and subnet id.
typedef Lease4Storage::index<ClientIdHWAddressSubnetIdIndexTag>::type
Lease4StorageClientIdHWAddressSubnetIdIndex;

//@}
} // end of isc::dhcp namespace
} // end of isc namespace

#endif // MEMFILE_LEASE_STORAGE_H
