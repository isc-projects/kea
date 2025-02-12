// Copyright (C) 2022-2024 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef DDNS_TUNING_H
#define DDNS_TUNING_H

#include <cc/base_stamped_element.h>
#include <cc/data.h>
#include <ddns_tuning_log.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcp/libdhcp++.h>
#include <dhcp/option.h>
#include <eval/evaluate.h>
#include <eval/token.h>
#include <dhcpsrv/subnet.h>
#include <expression_cache.h>

#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>

#include <map>
#include <string>

namespace isc {
namespace ddns_tuning {

/// @brief DDNS Tuning implementation.
///
/// The implementation can be divided into two parts:
///  - the configuration parsed and stored by load()
///  - logic to parse, cache, and evaluate hostname expressions
///
/// As features are adding, this class is likely to expand.
class DdnsTuningImpl {
public:
    /// @brief Constructor.
    ///
    /// @param family Protocol family of the server which owns this instance.
    DdnsTuningImpl(uint16_t family = AF_INET) : family_(family) {
    }

    /// @brief Destructor.
    ~DdnsTuningImpl();

    /// @brief Configure the Ddns Tuning implementation.
    ///
    /// @param params The JSON element with the expression.
    /// @throw BadValue and similar exceptions on error.
    void configure(isc::data::ConstElementPtr params);

    /// @brief Get the global hostname expression.
    ///
    /// @return the global expression or an empty pointer if no global
    /// expression has been configured.
    dhcp::ExpressionPtr getGlobalHostnameExpression();

    /// @brief Set the global hostname expression.
    ///
    /// @param expression expression to store as the global expression.
    void setGlobalHostnameExpression(dhcp::ExpressionPtr& expression);

    /// @brief Fetches the hostname for a given subnet_id.
    ///
    /// @param subnet_id ID for which the expression is desired.
    /// @return the subnet expression or an empty pointer if no subnet
    /// expression has been configured.
    dhcp::ExpressionPtr getHostnameExpression(const dhcp::SubnetID& subnet_id);

    /// @brief Set the hostname expression for a given subnet.
    ///
    /// @param subnet_id ID for which the expression is desired.
    /// @param expression pointer to the expression to store.
    void setHostnameExpression(const dhcp::SubnetID& subnet_id, dhcp::ExpressionPtr& expression);

    /// @brief Fetches the expression that is in scope for the given subnet.
    ///
    /// Hostname expressions are cached to avoid parsing them each time they might
    /// be needed. An entry is made in the cache for each subnet the first time after
    /// the cache has been flushed, that the subnet is presented. If subnet does not
    /// specify an expression, then an empty pointer is cached for it.
    ///
    /// The expression to use is determined as follows:
    ///
    /// 1. If the subnet has been modified since the cache was last flushed,
    /// (i.e. subnet state is newer than the cache) then we flush the cache
    /// and goto step 3.
    ///
    /// 2. Subnet hasn't changed since the last flush. If the cache contains
    /// an entry for the subnet that is not an empty pointer, return it.
    ///
    /// 3. If the subnet specifies an expression (via user-context) parse it,
    /// add it to the cache, and return it.  If it does not specify an
    /// expression cache an empty pointer for the subnet.
    ///
    /// 4. Return the global hostname expression or an empty pointer.
    ///
    /// @param subnet the subnet for the which expression is desired.
    /// @return pointer to the expression in scope for the subnet.
    dhcp::ExpressionPtr fetchScopedHostnameExpression(dhcp::ConstSubnetPtr subnet);

    /// @brief Caches an expression entry for a given subnet
    ///
    /// If the subnet specifies an expression string via user-context,
    /// it is parsed and if successful, the resulting expression is cached. If
    /// the parsing fails, the error is logged and an empty pointer is cached
    /// for the subnet.  If the subnet does not specify an expression string an
    /// empty pointer is cached for it.
    ///
    /// @param subnet subnet to process.
    /// @return a pointer to the parsed expression.
    dhcp::ExpressionPtr cacheExpression(dhcp::ConstSubnetPtr subnet);

    /// @brief Parses an expression string into an Expression.
    ///
    /// @param expression_str string containing the expression.
    /// @return a pointer to the parsed expression.
    /// @throw BadValue if the expression syntax is invalid.
    dhcp::ExpressionPtr parseExpression(const std::string& expression_str) const;

    /// @brief Calculate the hostname for a packet given a subnet
    ///
    /// Fetches the hostname expression that is in scope for the given subnet,
    /// and if found, uses it in conjunction with the given packet, to calculate
    /// the hostname.
    ///
    /// @param query the inbound client packet.
    /// @param subnet the subnet selected for the packet.
    /// @return string containing the calculated hostname, or an empty string
    /// if there is either no expression in scope or the expression is an empty
    /// expression.
    std::string calculateHostname(dhcp::PktPtr query,
                                  dhcp::ConstSubnetPtr subnet);

    /// @brief Flushes the cache contents.
    ///
    /// @param preserve_global if true the global expression is saved and then
    /// restored to the cache after the flushing of the subnet content.
    void flushCache(bool preserve_global = true);

    /// @brief Fetches the number of entries in the cache.
    ///
    /// @return cache entry count, including the global expression.
    size_t getCacheSize();

    /// @brief Fetches the time (in seconds) of when the cache was last flushed.
    ///
    /// The mechanism relies on the BaseStampedElement::modification_time_ which
    /// is currently the local time in seconds.
    ///
    /// @return time of the last flush.
    boost::posix_time::ptime getLastFlushTime();

    /// @brief Returns the protocol family of the address list.
    uint16_t getFamily() {
        return (family_);
    }

    /// @brief Repopulates the expression cache from the given subnet configuration
    ///
    /// Flushes the cache contents, while preserving the global expression, and
    /// then iterates over the configured subnets, parsing and caching the
    /// hostname expression for each.
    ///
    /// @tparam CfgSubnetPtrType type of the subnet configuration: CfgSubnet4Ptr
    /// or CfgSubnet6Ptr
    /// @param cfg_subnets subnet configuration containing the subnets to process
    /// @return 0 if successful, 1 otherwise
    template<typename CfgSubnetPtrType>
    int repopulateCache(const CfgSubnetPtrType cfg_subnets) {
        size_t err_count = 0;
        flushCache();
        auto const& subnets = cfg_subnets->getAll();
        for (auto const& subnet : *subnets) {
            try {
                static_cast<void>(cacheExpression(subnet));
            } catch (const std::exception& ex) {
                // Log it but keep going, so we find all that are invalid.
                LOG_ERROR(ddns_tuning_logger, DDNS_TUNING_SUBNET_EXPRESSION_PARSE_ERROR)
                        .arg(subnet->toText()).arg(ex.what());
                ++err_count;
            }
        }

        return (err_count);
    }

private:
    /// @brief protocol family of the list (AF_INET or AF_INET6)
    uint16_t family_;

protected:
    /// @brief Per subnet expression cache.  Note we store the global
    /// expression in here under SUBNET_ID_GLOBAL.
    ExpressionCache subnet_exprs_;
};

/// @brief The type of shared pointers to DDNS Tuning implementations.
typedef boost::shared_ptr<DdnsTuningImpl> DdnsTuningImplPtr;

} // end of namespace ddns_tuning
} // end of namespace isc
#endif
