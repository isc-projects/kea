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
    std::unordered_set<asiolink::IOAddress, boost::hash<asiolink::IOAddress> > addresses_;
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
    /// @param sending  Reference to a flag set to true when the query was
    /// processed and response will be built and sent.
    virtual void processQuery(isc::dhcp::PktPtr base_query,
                              bool& invalid, bool& sending) const = 0;

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

    /// @brief The I/O context.
    isc::asiolink::IOServicePtr io_service_;

    /// @param list of addresses from which queries can be accepted.
    AddressList address_list_;
};

/// @brief Defines a smart pointer to LeaseQueryImpl instance.
typedef boost::shared_ptr<LeaseQueryImpl> LeaseQueryImplPtr;

} // end of namespace isc::lease_query
} // end of namespace isc

#endif // LEASE_QUERY_IMPL_H
