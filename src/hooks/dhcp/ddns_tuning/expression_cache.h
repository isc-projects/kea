// Copyright (C) 2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef EXPRESSION_CACHE_H
#define EXPRESSION_CACHE_H

#include <cc/base_stamped_element.h>
#include <cc/data.h>
#include <eval/evaluate.h>
#include <eval/token.h>
#include <dhcpsrv/subnet.h>

#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>

#include <map>
#include <mutex>
#include <string>

namespace isc {
namespace ddns_tuning {

/// @brief ExpressionCache stores expressions per subnet
///
/// For every subnet (lazy init) we store:
///
/// -# subnet id
/// -# expression pointer
/// where:
///     - empty pointer means that subnet does not define an expression
///     - empty expression means that subnet overrides a global expression
///     with no expression
///     - non-empty means subnet overrides a global expression with an
///     expression
///
/// Each time we clear the cache we update the modification time.
///
/// When presented with a subnet:
///
/// 1. no cache entry:
///     cache it
///
/// 2. entry exists:
///     subnet mod time >= last flush
///         cache is stale flush it
///         cache it
///
///     subnet mod time < last flush
///         use it
///
class ExpressionCache : public data::BaseStampedElement {
public:
    /// @brief Constructor
    ExpressionCache() : expressions_() {
    }

    /// @brief Destructor
    virtual ~ExpressionCache() {
    }

    /// @brief Fetches the expression for a given subnet.
    ///
    /// @param subnet_id ID of the subnet for which the expression is desired.
    /// @param[out] expression a reference to a pointer in which to store the
    /// expression if found. If there is no entry for the subnet, it will be set
    /// to an empty pointer.
    /// @return True if an entry for subnet was found, false otherwise.  This
    /// allows callers to distinguish between unknown subnets (entries that do
    /// not exist) and subnets that are known but do not define an expression.
    bool findExpression(const dhcp::SubnetID& subnet_id,
                        dhcp::ExpressionPtr& expression);

    /// @brief Parses an expression string and caches for the given subnet.
    ///
    /// @param subnet_id ID of the subnet for which the expression is desired.
    /// @param expression_str string containing the expression to parse and cache.
    /// @param family protocol family (AF_INET or AF_INET6) of the subnet/expression.
    /// @return pointer to the parsed expression.
    /// @throw  BadValue if an error occurred during expression parsing.
    dhcp::ExpressionPtr parseAndCacheExpression(const dhcp::SubnetID& subnet_id,
                                        const std::string& expression_str,
                                        uint32_t family);

    /// @brief Adds (or replaces) the expression for a given subnet to the cache.
    ///
    /// @param subnet_id ID of the subnet for which the expression is desired.
    /// @param expression pointer to the expression to store. This may be an
    /// empty pointer.
    void cacheExpression(const dhcp::SubnetID& subnet_id,
                         dhcp::ExpressionPtr& expression);

    /// @brief Delete all the entries in the cache.
    void clear();

    /// @brief Returns number of entries in the cache.
    size_t size();

    /// @brief Returns the last time the cache was flushed (or
    /// the time it was created if it has never been flushed).
    boost::posix_time::ptime getLastFlushTime();

private:
    /// @brief Fetches the expression for a given subnet.
    ///
    /// Must be called from with a thread-safe context.
    ///
    /// @param subnet_id ID of the subnet for which the expression is desired.
    /// @param[out] expression a reference to a pointer in which to store the
    /// expression if found. If there is no entry for the subnet, it will be set
    /// to an empty pointer.
    /// @return True if an entry for subnet was found, false otherwise.  This
    /// allows callers to distinguish between unknown subnets (entries that do
    /// not exist) and subnets that are known but do not define an expression.
    bool findExpressionInternal(const dhcp::SubnetID& subnet_id, dhcp::ExpressionPtr& expression) const;

    /// @brief Per subnet expression cache.  Note we store the global
    /// expression in here under SUBNET_ID_GLOBAL.
    std::map<dhcp::SubnetID, dhcp::ExpressionPtr> expressions_;

    /// @brief Mutex to protect the internal state.
    std::mutex mutex_;
};

} // end of namespace ddns_tuning
} // end of namespace isc
#endif
