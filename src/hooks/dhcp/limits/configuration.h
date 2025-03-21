// Copyright (C) 2022-2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef ISC_LIMITS_CONFIGURATION_H
#define ISC_LIMITS_CONFIGURATION_H

#include <cc/base_stamped_element.h>
#include <cc/data.h>
#include <dhcp/classify.h>
#include <dhcpsrv/srv_config.h>
#include <dhcpsrv/subnet_id.h>

#include <limits>

namespace isc {
namespace limits {

/// @brief Throw an exception if limit is not within boundaries.
///
/// @param limit the limit being checked
///
/// @throw ConfigError when limit is negative
template <typename limit_t>
static void checkForLimitBoundaries(int64_t const limit) {
    if (limit < 0) {
        isc_throw(ConfigError,
                  "expected positive limit configured, got negative limit " << limit);
    }

    if (std::numeric_limits<limit_t>::max() < limit) {
        isc_throw(ConfigError, "expected limit in range [0, "
                                              << std::numeric_limits<limit_t>::max()
                                              << "], got limit " << limit);
    }
}

/// @brief a single lease-limiting entry configured as an integer
using LeaseLimit = uint32_t;

/// @brief a single rate-limiting entry configured as "rate-limit": "<n> packet[s] per <time-unit>"
struct RateLimit {
    /// @brief Constructor.
    RateLimit() : allowed_packets_(0) {
    }

    /// @brief Constructs a pragmatic rate limit data structure from text of
    /// "<n> packet[s] per <time-unit>" format.
    RateLimit(std::string const& text);

    /// @brief the configured limit
    uint32_t allowed_packets_;

    /// @brief Seconds of one time unit's worth.
    /// For simplicity, one month is always 30 days and one year is always 365 days.
    std::chrono::seconds time_unit_;

    /// @brief a string representation of the rate limit as specified in the configuration used for
    /// logging purposes
    std::string text_;
};

/// @brief a datastore used for configuring functionally dedicated parts of the limits library
template <typename limit_t>
struct Configuration {
    /// @brief Destructor. Declared only to be marked as virtual.
    virtual ~Configuration() = default;

    /// @brief Handles all the parsing of the Kea configuration required for limiting functionality.
    ///
    /// @brief the configuration to be parsed - usually current or staging
    void parse(isc::dhcp::SrvConfigPtr const& config) {
        if (config) {
            // Check limits for all client classes.
            isc::dhcp::ClientClassDefListPtr const& client_classes(
                config->getClientClassDictionary()->getClasses());
            for (isc::dhcp::ClientClassDefPtr const& c : *client_classes) {
                logClientClassLimit(c->getName(), parseUserContext(c->getContext()));
            }

            // Check limits for all v4 subnets.
            isc::dhcp::Subnet4Collection const* const subnets4(config->getCfgSubnets4()->getAll());
            for (isc::dhcp::Subnet4Ptr const& s : *subnets4) {
                logSubnetLimit(s->getID(), parseUserContext(s->getContext()));
            }

            // Check limits for all v6 subnets.
            isc::dhcp::Subnet6Collection const* const subnets6(config->getCfgSubnets6()->getAll());
            for (isc::dhcp::Subnet6Ptr const& s : *subnets6) {
                logSubnetLimit(s->getID(), parseUserContext(s->getContext()));
            }
        }
    }

    /// @brief Abstract method that takes a user context from any configuration element and returns
    /// the value of the element of interest inside it - most often a limit.
    ///
    /// @param user_context the element's user context
    ///
    /// @return the value of the element of interest
    isc::data::ConstElementPtr const
    parseUserContext(isc::data::ConstElementPtr const& user_context) const {
        if (!user_context) {
            return (isc::data::ConstElementPtr());
        }
        isc::data::ConstElementPtr const& limits(user_context->get("limits"));
        if (!limits) {
            return (isc::data::ConstElementPtr());
        }
        return (limits->get(key()));
    }

    /// @brief Returns the key required to configure the limit in the user context.
    ///
    /// @return the key
    virtual const std::string& key() const = 0;

    /// @brief Abstract method that checks and logs limit which is to be applied to a client class.
    ///
    /// @param client_class
    /// @param user_context
    virtual void logClientClassLimit(isc::dhcp::ClientClass const& client_class,
                                     isc::data::ConstElementPtr const& user_context) = 0;

    /// @brief Abstract method that checks and logs limit which is to be applied to a client class.
    ///
    /// @param subnet_id
    /// @param user_context
    virtual void logSubnetLimit(isc::dhcp::SubnetID const subnet_id,
                                isc::data::ConstElementPtr const& user_context) = 0;
};

/// @brief the configuration manager for address limiting
struct AddressLimitConfiguration : Configuration<LeaseLimit> {
    /// @brief Returns the key required to configure the limit in the user context.
    ///
    /// @return the key
    const std::string& key() const override;

    /// @brief Method that checks and logs limit which is to be applied to a client class.
    ///
    /// @param client_class
    /// @param user_context
    virtual void logClientClassLimit(isc::dhcp::ClientClass const& client_class,
                                     isc::data::ConstElementPtr const& user_context) override;

    /// @brief Method that checks and logs limit which is to be applied to a client class.
    ///
    /// @param subnet_id
    /// @param user_context
    virtual void logSubnetLimit(isc::dhcp::SubnetID const subnet_id,
                                isc::data::ConstElementPtr const& user_context) override;
};

/// @brief the configuration manager for prefix limiting
struct PrefixLimitConfiguration : Configuration<LeaseLimit> {
    /// @brief Returns the key required to configure the limit in the user context.
    ///
    /// @return the key
    const std::string& key() const override;

    /// @brief Method that checks and logs limit which is to be applied to a client class.
    ///
    /// @param client_class
    /// @param user_context
    virtual void logClientClassLimit(isc::dhcp::ClientClass const& client_class,
                                     isc::data::ConstElementPtr const& user_context) override;

    /// @brief Method that checks and logs limit which is to be applied to a client class.
    ///
    /// @param subnet_id
    /// @param user_context
    virtual void logSubnetLimit(isc::dhcp::SubnetID const subnet_id,
                                isc::data::ConstElementPtr const& user_context) override;
};

/// @brief the configuration manager for rate limiting
struct RateLimitConfiguration : Configuration<RateLimit> {
    /// @brief Returns the key required to configure the limit in the user context.
    ///
    /// @return the key
    const std::string& key() const override;

    /// @brief Method that checks and logs limit which is to be applied to a client class.
    ///
    /// @param client_class
    /// @param user_context
    virtual void logClientClassLimit(isc::dhcp::ClientClass const& client_class,
                                     isc::data::ConstElementPtr const& user_context) override;

    /// @brief Method that checks and logs limit which is to be applied to a client class.
    ///
    /// @param subnet_id
    /// @param user_context
    virtual void logSubnetLimit(isc::dhcp::SubnetID const subnet_id,
                                isc::data::ConstElementPtr const& user_context) override;
};

}  // namespace limits
}  // namespace isc

#endif  // ISC_LIMITS_CONFIGURATION_H
