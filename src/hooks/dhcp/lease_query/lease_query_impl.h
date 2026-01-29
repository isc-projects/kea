// Copyright (C) 2020-2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef LEASE_QUERY_IMPL_H
#define LEASE_QUERY_IMPL_H

#include <exceptions/exceptions.h>
#include <asiolink/io_address.h>
#include <asiolink/io_service.h>
#include <dhcp/pkt.h>
#include <dhcpsrv/pool.h>
#include <cc/data.h>
#include <cc/simple_parser.h>

#include <boost/functional/hash.hpp>
#include <unordered_set>

namespace isc {
namespace lease_query {

/// @brief Thrown on hook termination.
class QueryTerminated : public isc::Exception {
public:
    QueryTerminated(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) {
    }
};

#define CHECK_TERMINATED \
    if (LeaseQueryImpl::terminated_) { \
        isc_throw(isc::lease_query::QueryTerminated, "terminated"); \
    }

/// @brief Manages a unique list of IP addresses.
class AddressList {
public:
    /// @brief Constructor
    ///
    /// @param family protocol family of the list (AF_INET or AF_INET6)
    AddressList(uint16_t family)
    : family_(family) { };

    /// @brief Inserts an address into the list.
    ///
    /// Adds the given address to the list.
    ///
    /// @param address address to add
    /// @throw BadValue if the address's family does not match
    /// the list's family or the address is already in the list.
    void insert(const isc::asiolink::IOAddress& address);

    /// @brief Checks if an address is present in the list
    ///
    /// @param address  address for which to search
    /// @return true if the address is in the list, false otherwise
    /// @throw BadValue if the address's family does not match
    /// the list's family.
    bool contains(const isc::asiolink::IOAddress& address) const;

    /// @brief Returns the number of addresses in the list.
    size_t size() const {
        return (addresses_.size());
    }

    /// @brief Returns the protocol family of the address list.
    uint16_t getFamily() {
        return (family_);
    }

private:
    /// @brief protocol family of the list (AF_INET or AF_INET6)
    uint16_t family_;

    /// @brief Set of unique addresses in the list.
    std::unordered_set<asiolink::IOAddress, asiolink::IOAddress::Hash> addresses_;
};

/// @brief Hash for a Pool based on it's address range.
struct PoolRangeHash {
    std::size_t operator()(const isc::dhcp::PoolPtr& p) const noexcept {
        const auto& f = p->getFirstAddress();
        const auto& l = p->getLastAddress();

        isc::asiolink::IOAddress::Hash haddr;
        std::size_t h1 = haddr(f);
        std::size_t h2 = haddr(l);

        // hash_combine
        return h1 ^ (h2 + 0x9e3779b97f4a7c15ULL + (h1 << 6) + (h1 >> 2));
    }
};

/// @brief Equality comparator for two pools based on their address range.
struct PoolRangeEqual {
    bool operator()(const isc::dhcp::PoolPtr& a,
                    const isc::dhcp::PoolPtr& b) const noexcept {
        return a->getFirstAddress() == b->getFirstAddress() &&
               a->getLastAddress()  == b->getLastAddress();
    }
};

/// @brief Defines an alias for a set of pools hashed by range.
using PoolRangeSet = std::unordered_set<isc::dhcp::PoolPtr,
                                        PoolRangeHash,
                                        PoolRangeEqual>;

/// @brief Manages a unique set of Pools of a given protocol family.
/// The pools are hashed by their address range.
class PoolSet {
public:
    /// @brief Constructor
    ///
    /// @param family protocol family of the set (AF_INET or AF_INET6)
    PoolSet(uint16_t family)
    : family_(family) { };

    /// @brief Inserts an pool into the set.
    ///
    /// Creates a pool and adds it to the set, assuming it is not
    /// already in the set.
    ///
    /// @param prefix prefix of the pool
    /// @param prefix_len length of the pool prefix
    /// @throw BadValue if the prefix family does not match
    /// the set's family, prefix length is invalid, or the pool is
    /// already in the set.
    void insert(const isc::asiolink::IOAddress& prefix, uint8_t prefix_len);

    /// @brief Checks if an address is present in the set.
    ///
    /// @param address address to look for.
    /// @return true if the address is within a pool in the pool set
    /// @throw BadValue if the address's family does not match
    /// the set's family.
    bool contains(const isc::asiolink::IOAddress& address) const;

    /// @brief Returns the number of pools in the set.
    size_t size() const {
        return (pools_.size());
    }

    /// @brief Returns the protocol family of the address set.
    uint16_t getFamily() const {
        return (family_);
    }

private:
    /// @brief protocol family of the set (AF_INET or AF_INET6)
    uint16_t family_;

    /// @brief Unique set of pools.
    PoolRangeSet pools_;
};

/// @brief Provides configuration and control flow for processing queries.
class LeaseQueryImpl : public boost::noncopyable {
public:
    /// @brief Constructor
    ///
    /// @param family protocol family we're handling (AF_INET or AF_INET6)
    /// @param config input configuration
    LeaseQueryImpl(uint16_t family, const isc::data::ConstElementPtr config);

    /// @brief Destructor
    virtual ~LeaseQueryImpl();

    /// @brief Checks if the given address belongs to a valid requester.
    ///
    /// @param address address to verify
    /// @return true if the address is in the list of requesters, false
    /// otherwise.
    bool isRequester(const isc::asiolink::IOAddress& address) const;

    /// @brief Returns the number of valid requester.
    size_t getNumRequesters() const {
        return (address_list_.size());
    }

    /// @brief Returns the number of valid requester pools.
    size_t getNumRequesterPools() const {
        return (pool_set_.size());
    }

    /// @brief Processes a single client Lease Query
    ///
    /// - Validates query content
    /// - Determines is the query is permitted
    /// - Queries matching lease(s)
    /// - Constructs the reply
    /// - Sends the reply
    ///
    /// @param base_query lease query to process. (Implementations
    /// must use dynamic_casting).
    /// @param invalid Reference to a flag set to true when the query
    /// is invalid (used to detect unexpected exceptions).
    virtual void processQuery(isc::dhcp::PktPtr base_query,
                              bool& invalid) const = 0;

    /// @brief Keywords for Lease Query configuration.
    static const isc::data::SimpleKeywords LEASE_QUERY_KEYWORDS;

    /// @brief Returns the protocol family of the impl.
    uint16_t getFamily() {
        return (address_list_.getFamily());
    }

    /// @brief Get the hook I/O service.
    ///
    /// @return the hook I/O service.
    isc::asiolink::IOServicePtr getIOService() {
        return (io_service_);
    }

    /// @brief Set the hook I/O service.
    ///
    /// @param io_service the hook I/O service.
    void setIOService(isc::asiolink::IOServicePtr io_service) {
        io_service_ = io_service;
    }

    /// @brief Terminated flag.
    static bool terminated_;

    /// @brief Page size to commands.
    static size_t PageSize;

private:
    /// @brief Parses 'requesters' list element.
    ///
    /// @param requesters pointer to the list element containing requester
    /// entries. Entries may be a mix of IP addresses or subnets in CIDR format.
    ///
    /// @throw BadValue if the list is empty or if any of the entries are
    /// not valid addresses or  CIDRs.
    void parserRequesters(isc::data::ConstElementPtr requesters);

    /// @brief The I/O context.
    isc::asiolink::IOServicePtr io_service_;

    /// @param list of addresses from which queries can be accepted.
    AddressList address_list_;

    /// @param set of valid requester pools.
    PoolSet pool_set_;
};

/// @brief Defines a smart pointer to LeaseQueryImpl instance.
typedef boost::shared_ptr<LeaseQueryImpl> LeaseQueryImplPtr;

} // end of namespace isc::lease_query
} // end of namespace isc

#endif // LEASE_QUERY_IMPL_H
