// Copyright (C) 2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef CONFIG_CACHE_H
#define CONFIG_CACHE_H

#include <ping_check_config.h>
#include <cc/base_stamped_element.h>
#include <cc/data.h>
#include <dhcpsrv/subnet.h>

#include <map>
#include <mutex>

namespace isc {
namespace ping_check {

/// @brief ConfigCache stores ping check config per subnet
///
/// The intent is parse subnet ping-check parameters from its user-context
/// as few times as possible rather than on every ping check request, while
/// also allowing for run time updates via config back end or subnet cmds.
///
/// For every subnet we store:
///
/// -# subnet id
/// -# PingCheckConfig pointer
/// where:
///     - empty config pointer means that subnet does not specify ping check config
///     - non-empty means subnet specifies at least some ping check parameters
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
class ConfigCache : public data::BaseStampedElement {
public:
    /// @brief Constructor
    ConfigCache() : configs_(), global_config_(new PingCheckConfig()), mutex_(new std::mutex) {
    }

    /// @brief Destructor
    virtual ~ConfigCache() = default;

    /// @brief Get the config for a given subnet.
    ///
    /// @param subnet_id ID of the subnet for which the config is desired.
    /// @param[out] config a reference to a pointer in which to store the
    /// config if found. If there is no entry for the subnet, it will be set
    /// to an empty pointer.
    ///
    /// @return True if an entry for subnet was found, false otherwise.  This
    /// allows callers to distinguish between unknown subnets (entries that do
    /// not exist) and subnets that are known but do not define a config.
    bool findConfig(const dhcp::SubnetID& subnet_id,
                    PingCheckConfigPtr& config);

    /// @brief Parses a config string and caches for the given subnet.
    ///
    /// @param subnet_id ID of the subnet for which the config is desired.
    /// @param user_context user-context Element map of the subnet.
    ///
    /// @return pointer to the parsed config.
    /// @throw BadValue if an error occurred during config parsing.
    PingCheckConfigPtr parseAndCacheConfig(const dhcp::SubnetID& subnet_id,
                                           data::ConstElementPtr& user_context);

    /// @brief Adds (or replaces) the config for a given subnet to the cache.
    ///
    /// @param subnet_id ID of the subnet for which the config is desired.
    /// @param config pointer to the config to store. This may be an
    /// empty pointer.
    void cacheConfig(const dhcp::SubnetID& subnet_id,
                     PingCheckConfigPtr& config);

    /// @brief Discards the subnet entries in the cache.
    void flush();

    /// @brief Get the number of entries in the cache.
    ///
    /// @return number of entries in the cache.
    size_t size();

    /// @brief Get the last time the cache was flushed.
    ///
    /// @return the last time the cache was flushed (or the time it was
    /// created if it has never been flushed).
    boost::posix_time::ptime getLastFlushTime();

    /// @brief Get the global level configuration.
    ///
    /// @return pointer to the global configuration.
    PingCheckConfigPtr& getGlobalConfig();

    /// @brief Set the global level configuration.
    ///
    /// @param config configuration to store as the global configuration.
    void setGlobalConfig(PingCheckConfigPtr& config);

private:
    /// @brief Get the config for a given subnet.
    ///
    /// Must be called from with a thread-safe context.
    ///
    /// @param subnet_id ID of the subnet for which the config is desired.
    /// @param[out] config a reference to a pointer in which to store the
    /// config if found. If there is no entry for the subnet, it will be set
    /// to an empty pointer.
    ///
    /// @return True if an entry for subnet was found, false otherwise.  This
    /// allows callers to distinguish between unknown subnets (entries that do
    /// not exist) and subnets that are known but do not define a config.
    bool findConfigInternal(const dhcp::SubnetID& subnet_id,
                            PingCheckConfigPtr& config) const;

    /// @brief Per subnet config cache.  Note that the global config in stored
    /// using SUBNET_ID_GLOBAL.
    std::map<dhcp::SubnetID, PingCheckConfigPtr> configs_;

    /// @brief Stores the global configuration parameters.
    PingCheckConfigPtr global_config_;

    /// @brief The mutex used to protect internal state.
    const boost::scoped_ptr<std::mutex> mutex_;
};

/// @brief Defines a shared pointer to a ConfigCache.
typedef boost::shared_ptr<ConfigCache> ConfigCachePtr;

} // end of namespace ping_check
} // end of namespace isc
#endif
