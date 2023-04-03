// Copyright (C) 2015-2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef MEMFILE_LEASE_STORAGE_H
#define MEMFILE_LEASE_STORAGE_H

#include <asiolink/io_address.h>
#include <dhcpsrv/lease.h>
#include <dhcpsrv/subnet_id.h>

#include <boost/multi_index/indexed_by.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/mem_fun.hpp>
#include <boost/multi_index/hashed_index.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index_container.hpp>
#include <boost/multi_index/composite_key.hpp>

#include <functional>
#include <vector>

namespace isc {
namespace dhcp {

/// @brief Tag for indexes by address.
struct AddressIndexTag { };

/// @brief Tag for indexes by DUID, IAID, lease type tuple.
struct DuidIaidTypeIndexTag { };

/// @brief Tag for indexes by expiration time.
struct ExpirationIndexTag { };

/// @brief Tag for indexes by HW address, subnet-id tuple.
struct HWAddressSubnetIdIndexTag { };

/// @brief Tag for indexes by client-id, subnet-id tuple.
struct ClientIdSubnetIdIndexTag { };

/// @brief Tag for indexes by subnet-id.
struct SubnetIdIndexTag { };

/// @brief Tag for indexes by subnet-id and pool-id.
struct SubnetIdPoolIdIndexTag { };

/// @brief Tag for index using DUID.
struct DuidIndexTag { };

/// @brief Tag for index using hostname.
struct HostnameIndexTag { };

/// @brief Tag for index using remote-id.
struct RemoteIdIndexTag { };

/// @brief Tag for index using relay-id.
struct RelayIdIndexTag { };

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
/// - using subnet ID.
/// - using hostname.
///
/// Indexes can be accessed using the index number (from 0 to 5) or a
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
            // This is a composite index that is used to search for
            // the expired leases. Depending on the value of the first component
            // of the search key, the reclaimed or not reclaimed leases can
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
        >,

        // Specification of the fourth index starts here.
        // This index sorts leases by SubnetID.
        boost::multi_index::ordered_non_unique<
            boost::multi_index::tag<SubnetIdIndexTag>,
            boost::multi_index::member<Lease, isc::dhcp::SubnetID,
            &Lease::subnet_id_>
        >,

        // Specification of the fifth index starts here
        // This index is used to retrieve leases for matching duid.
        boost::multi_index::ordered_non_unique<
            boost::multi_index::tag<DuidIndexTag>,
            boost::multi_index::const_mem_fun<Lease6,
                                              const std::vector<uint8_t>&,
                                              &Lease6::getDuidVector>
        >,

        // Specification of the sixth index starts here
        // This index is used to retrieve leases for matching hostname.
        boost::multi_index::ordered_non_unique<
            boost::multi_index::tag<HostnameIndexTag>,
            boost::multi_index::member<Lease, std::string, &Lease::hostname_>
        >,

        // Specification of the seventh index starts here.
        boost::multi_index::ordered_non_unique<
            boost::multi_index::tag<SubnetIdPoolIdIndexTag>,
            // This is a composite index that combines two attributes of the
            // Lease6 object: subnet id and pool id.
            boost::multi_index::composite_key<
                Lease6,
                // The subnet id is held in the subnet_id_ member of Lease6
                // class. Note that the subnet_id_ is defined in the base
                // class (Lease) so we have to point to this class rather
                // than derived class: Lease6.
                boost::multi_index::member<Lease, SubnetID, &Lease::subnet_id_>,
                // The pool id is held in the pool_id_ member of Lease6
                // class. Note that the pool_id_ is defined in the base
                // class (Lease) so we have to point to this class rather
                // than derived class: Lease6.
                boost::multi_index::member<Lease, uint32_t, &Lease::pool_id_>
            >
        >
    >
> Lease6Storage; // Specify the type name of this container.

/// @brief A multi index container holding DHCPv4 leases.
///
/// The leases in the container may be accessed using different indexes:
/// - IPv4 address,
/// - composite index: hardware address and subnet id,
/// - composite index: client id and subnet id,
/// - using a composite index: boolean flag indicating if the state is
///   "expired-reclaimed" and expiration time.
/// - using subnet id.
/// - using hostname.
/// - using remote id.
/// - using a composite index:
///
/// Indexes can be accessed using the index number (from 0 to 5) or a
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
        >,

        // Specification of the fifth index starts here.
        // This index sorts leases by SubnetID.
        boost::multi_index::ordered_non_unique<
            boost::multi_index::tag<SubnetIdIndexTag>,
            boost::multi_index::member<Lease, isc::dhcp::SubnetID, &Lease::subnet_id_>
        >,

        // Specification of the sixth index starts here.
        // This index is used to retrieve leases for matching hostname.
        boost::multi_index::ordered_non_unique<
            boost::multi_index::tag<HostnameIndexTag>,
            boost::multi_index::member<Lease, std::string, &Lease::hostname_>
        >,

        // Specification of the seventh index starts here.
        // This index is used to retrieve leases for matching remote id
        // for Bulk Lease Query.
        boost::multi_index::hashed_non_unique<
            boost::multi_index::tag<RemoteIdIndexTag>,
            boost::multi_index::member<Lease4,
                                       std::vector<uint8_t>,
                                       &Lease4::remote_id_>
        >,

        // Specification of the eighth index starts here.
        // This index is used to retrieve leases for matching relay id
        // for Bulk Lease Query.
        boost::multi_index::ordered_non_unique<
            boost::multi_index::tag<RelayIdIndexTag>,
            boost::multi_index::composite_key<
                Lease4,
                // Relay id.
                boost::multi_index::member<Lease4,
                                           std::vector<uint8_t>,
                                           &Lease4::relay_id_>,
                // Address.
                boost::multi_index::member<Lease,
                                           isc::asiolink::IOAddress,
                                           &Lease::addr_>
            >
        >,

        // Specification of the ninth index starts here.
        boost::multi_index::ordered_non_unique<
            boost::multi_index::tag<SubnetIdPoolIdIndexTag>,
            // This is a composite index that combines two attributes of the
            // Lease4 object: subnet id and pool id.
            boost::multi_index::composite_key<
                Lease4,
                // The subnet id is held in the subnet_id_ member of Lease4
                // class. Note that the subnet_id_ is defined in the base
                // class (Lease) so we have to point to this class rather
                // than derived class: Lease4.
                boost::multi_index::member<Lease, SubnetID, &Lease::subnet_id_>,
                // The pool id is held in the pool_id_ member of Lease4
                // class. Note that the pool_id_ is defined in the base
                // class (Lease) so we have to point to this class rather
                // than derived class: Lease4.
                boost::multi_index::member<Lease, uint32_t, &Lease::pool_id_>
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

/// @brief DHCPv6 lease storage index by subnet-id.
typedef Lease6Storage::index<SubnetIdIndexTag>::type Lease6StorageSubnetIdIndex;

/// @brief DHCPv6 lease storage index subnet-id and pool-id.
typedef Lease6Storage::index<SubnetIdPoolIdIndexTag>::type Lease6StorageSubnetIdPoolIdIndex;

/// @brief DHCPv6 lease storage index by DUID.
typedef Lease6Storage::index<DuidIndexTag>::type Lease6StorageDuidIndex;

/// @brief DHCPv6 lease storage index by hostname.
typedef Lease6Storage::index<HostnameIndexTag>::type Lease6StorageHostnameIndex;

/// @brief DHCPv4 lease storage index by address.
typedef Lease4Storage::index<AddressIndexTag>::type Lease4StorageAddressIndex;

/// @brief DHCPv4 lease storage index by expiration time.
typedef Lease4Storage::index<ExpirationIndexTag>::type Lease4StorageExpirationIndex;

/// @brief DHCPv4 lease storage index by HW address and subnet-id.
typedef Lease4Storage::index<HWAddressSubnetIdIndexTag>::type
Lease4StorageHWAddressSubnetIdIndex;

/// @brief DHCPv4 lease storage index by client-id and subnet-id.
typedef Lease4Storage::index<ClientIdSubnetIdIndexTag>::type
Lease4StorageClientIdSubnetIdIndex;

/// @brief DHCPv4 lease storage index subnet-id.
typedef Lease4Storage::index<SubnetIdIndexTag>::type Lease4StorageSubnetIdIndex;

/// @brief DHCPv4 lease storage index subnet-id and pool-id.
typedef Lease4Storage::index<SubnetIdPoolIdIndexTag>::type Lease4StorageSubnetIdPoolIdIndex;

/// @brief DHCPv4 lease storage index by hostname.
typedef Lease4Storage::index<HostnameIndexTag>::type Lease4StorageHostnameIndex;

/// @brief DHCPv4 lease storage index by remote-id.
typedef Lease4Storage::index<RemoteIdIndexTag>::type Lease4StorageRemoteIdIndex;

/// @brief DHCPv4 lease storage range by remote-id.
typedef std::pair<Lease4StorageRemoteIdIndex::const_iterator,
                  Lease4StorageRemoteIdIndex::const_iterator> Lease4StorageRemoteIdRange;

/// @brief DHCPv4 lease storage index by relay-id.
typedef Lease4Storage::index<RelayIdIndexTag>::type Lease4StorageRelayIdIndex;

//@}

/// @name Multi index containers holding DHCPv6 lease extended informations
/// for Bulk Lease Query.
//@{

/// @brief Lease6 extended informations for Bulk Lease Query.
class Lease6ExtendedInfo {
public:
    /// @brief Constructor.
    ///
    /// @param lease_addr Lease address.
    /// @param id Identifier.
    Lease6ExtendedInfo(const isc::asiolink::IOAddress& lease_addr,
                       const std::vector<uint8_t>& id)
        : lease_addr_(lease_addr), id_(id) {
    }

    /// @brief Lease address.
    isc::asiolink::IOAddress lease_addr_;

    /// @brief Remote or relay opaque identifier.
    std::vector<uint8_t> id_;
};

/// @brief Pointer to a Lease6ExtendedInfo object.
typedef boost::shared_ptr<Lease6ExtendedInfo> Lease6ExtendedInfoPtr;

/// @brief Tag for indexes by lease address.
struct LeaseAddressIndexTag { };

/// @brief A multi index container holding lease6 extended info for by relay id.
///
/// The lease6 extended info may be accessed using different indexes:
/// - using relay id, and lease address for getting lower bounds.
/// - using lease address for deletes.
///
/// The choice of binary trees was governed by the fact a large number of
/// clients can be behind a relay.
///
/// Indexes can be accessed using the index number (from 0 to 5) or a
/// name tag. It is recommended to use the tags to access indexes as
/// they do not depend on the order of indexes in the container.
typedef boost::multi_index_container<
    // It holds pointers to lease6 extended info.
    Lease6ExtendedInfoPtr,
    boost::multi_index::indexed_by<
        // First index is by relay id and lease address.
        boost::multi_index::ordered_non_unique<
            boost::multi_index::tag<RelayIdIndexTag>,
            boost::multi_index::composite_key<
                Lease6ExtendedInfo,
                boost::multi_index::member<Lease6ExtendedInfo,
                                           std::vector<uint8_t>,
                                           &Lease6ExtendedInfo::id_>,
                boost::multi_index::member<Lease6ExtendedInfo,
                                           isc::asiolink::IOAddress,
                                           &Lease6ExtendedInfo::lease_addr_>
            >
        >,

        // Last index is by lease address.
        boost::multi_index::hashed_non_unique<
            boost::multi_index::tag<LeaseAddressIndexTag>,
            boost::multi_index::member<Lease6ExtendedInfo,
                                       isc::asiolink::IOAddress,
                                       &Lease6ExtendedInfo::lease_addr_>
        >
    >
> Lease6ExtendedInfoRelayIdTable;

/// @brief A multi index container holding lease6 extended info for by remote id.
///
/// The lease6 extended info may be accessed using different indexes:
/// - using remote id.
/// - using lease address for deletes.
///
/// The internal layout of remote id is not used. The choice of hash tables
/// was governed by the fact a small number of clients should share the same
/// remote id.
///
/// Indexes can be accessed using the index number (from 0 to 5) or a
/// name tag. It is recommended to use the tags to access indexes as
/// they do not depend on the order of indexes in the container.
typedef boost::multi_index_container<
    // It holds pointers to lease6 extended info.
    Lease6ExtendedInfoPtr,
    boost::multi_index::indexed_by<
        // First index is by remote id.
        boost::multi_index::hashed_non_unique<
            boost::multi_index::tag<RemoteIdIndexTag>,
            boost::multi_index::member<Lease6ExtendedInfo,
                                       std::vector<uint8_t>,
                                       &Lease6ExtendedInfo::id_>
        >,

        // Last index is by lease address.
        boost::multi_index::hashed_non_unique<
            boost::multi_index::tag<LeaseAddressIndexTag>,
            boost::multi_index::member<Lease6ExtendedInfo,
                                       isc::asiolink::IOAddress,
                                       &Lease6ExtendedInfo::lease_addr_>
        >
    >
> Lease6ExtendedInfoRemoteIdTable;

/// @brief Lease6 extended information by relay id index.
typedef Lease6ExtendedInfoRelayIdTable::index<RelayIdIndexTag>::type
    RelayIdIndex;

/// @brief Lease6 extended information by lease address index of by relay id table.
typedef Lease6ExtendedInfoRelayIdTable::index<LeaseAddressIndexTag>::type
    LeaseAddressRelayIdIndex;

/// @brief Lease6 extended information by remote id index.
typedef Lease6ExtendedInfoRemoteIdTable::index<RemoteIdIndexTag>::type
    RemoteIdIndex;

/// @brief Lease6 extended information by remote id range.
typedef std::pair<RemoteIdIndex::const_iterator, RemoteIdIndex::const_iterator>
    RemoteIdIndexRange;

/// @brief Lease6 extended information by lease address index of by remote id table.
typedef Lease6ExtendedInfoRemoteIdTable::index<LeaseAddressIndexTag>::type
    LeaseAddressRemoteIdIndex;

//@}

} // end of isc::dhcp namespace
} // end of isc namespace

#endif // MEMFILE_LEASE_STORAGE_H
