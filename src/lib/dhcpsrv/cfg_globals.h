// Copyright (C) 2020 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef CFG_GLOBALS_H
#define CFG_GLOBALS_H

#include <cc/cfg_to_element.h>
#include <cc/data.h>
#include <boost/shared_ptr.hpp>
#include <map>
#include <string>
#include <vector>

namespace isc {
namespace dhcp {

/// @brief Class to store configured global parameters.
///
/// This class provides a direct access to a global parameter value
/// using a vector as soon as the parameter name is known at compile
/// time so in constant time vs in logarithm time using a map.
class CfgGlobals : public isc::data::CfgToElement {
public:

    /// Class members.

    /// @brief Enumeration of global parameters.
    ///
    /// The C++ compiler is required to start with 0 and to increment by 1
    /// so gives an index.
    ///
    /// Names taken from @c SimpleParser4::GLOBAL4_PARAMETERS and
    /// @c SimpleParser6::GLOBAL6_PARAMETERS, first part with common
    /// parameters followed by DHCPv4 and DHCPv6 specific parameters.
    /// Keep the order, enum element names is uppercase with - replaced by _.
    enum Index : int {
        // Common parameters.
        VALID_LIFETIME,
        MIN_VALID_LIFETIME,
        MAX_VALID_LIFETIME,
        RENEW_TIMER,
        REBIND_TIMER,
        DECLINE_PROBATION_PERIOD,
        SHARED_NETWORKS,
        INTERFACES_CONFIG,
        LEASE_DATABASE,
        HOSTS_DATABASE,
        HOSTS_DATABASES,
        HOST_RESERVATION_IDENTIFIERS,
        CLIENT_CLASSES,
        OPTION_DEF,
        OPTION_DATA,
        HOOKS_LIBRARIES,
        EXPIRED_LEASES_PROCESSING,
        DHCP4O6_PORT,
        CONTROL_SOCKET,
        DHCP_QUEUE_CONTROL,
        DHCP_DDNS,
        USER_CONTEXT,
        COMMENT,
        SANITY_CHECKS,
        RESERVATIONS,
        CONFIG_CONTROL,
        SERVER_TAG,
        RESERVATION_MODE,
        RESERVATIONS_GLOBAL,
        RESERVATIONS_IN_SUBNET,
        RESERVATIONS_OUT_OF_POOL,
        CALCULATE_TEE_TIMES,
        T1_PERCENT,
        T2_PERCENT,
        LOGGERS,
        HOSTNAME_CHAR_SET,
        HOSTNAME_CHAR_REPLACEMENT,
        DDNS_SEND_UPDATES,
        DDNS_OVERRIDE_NO_UPDATE,
        DDNS_OVERRIDE_CLIENT_UPDATE,
        DDNS_REPLACE_CLIENT_NAME,
        DDNS_GENERATED_PREFIX,
        DDNS_QUALIFYING_SUFFIX,
        STORE_EXTENDED_INFO,
        STATISTIC_DEFAULT_SAMPLE_COUNT,
        STATISTIC_DEFAULT_SAMPLE_AGE,
        MULTI_THREADING,
        CACHE_THRESHOLD,
        CACHE_MAX_AGE,
        IP_RESERVATIONS_UNIQUE,
        DDNS_UPDATE_ON_RENEW,
        DDNS_USE_CONFLICT_RESOLUTION,

        // DHCPv4 specific parameters.
        SUBNET4,
        ECHO_CLIENT_ID,
        MATCH_CLIENT_ID,
        AUTHORITATIVE,
        NEXT_SERVER,
        SERVER_HOSTNAME,
        BOOT_FILE_NAME,

        // DHCPv6 specific parameters.
        DATA_DIRECTORY,
        PREFERRED_LIFETIME,
        MIN_PREFERRED_LIFETIME,
        MAX_PREFERRED_LIFETIME,
        SUBNET6,
        MAC_SOURCES,
        RELAY_SUPPLIED_OPTIONS,
        SERVER_ID
    };

    /// @brief Last index.
    ///
    /// @note: please update when a new element is appended to the Index enum.
    static const int MAX_INDEX = SERVER_ID;

    /// @brief Size of configured global objects.
    static const size_t SIZE = MAX_INDEX + 1;

    /// @brief Name to index map.
    static const std::map<std::string, int> nameToIndex;

    /// Instance members.

    /// Constructor.
    ///
    /// Create a vector of null values.
    CfgGlobals();

    /// @brief Get a configured parameter value by name.
    ///
    /// @param name Name of the global parameter.
    /// @return The value of the global parameter with the given name.
    /// @throw NotFound if no global parameter has the given name.
    isc::data::ConstElementPtr get(const std::string& name) const;

    /// @brief Get a configured parameter value by index.
    ///
    /// @param index Index of the global parameter.
    /// @return The value of the global parameter with the index.
    /// @throw OutOfRange if the index is out of bounds.
    isc::data::ConstElementPtr get(int index) const;

    /// @brief Set a configured parameter value by name.
    ///
    /// @param name Name of the global parameter.
    /// @param value Value of the configured parameter to set.
    /// @throw NotFound if no global parameter has the given name.
    void set(const std::string& name, isc::data::ConstElementPtr value);

    /// @brief Set a configured parameter value by index.
    ///
    /// @param index Index of the global parameter.
    /// @param value Value of the configured parameter to set.
    /// @throw OutOfRange if the index is out of bounds.
    void set(int index, isc::data::ConstElementPtr value);

    /// @brief Clear configured parameter values.
    void clear();

    /// @brief Unparse configured globals.
    ///
    /// @return a pointer to unparsed globals.
    isc::data::ElementPtr toElement() const;

protected:
    /// @brief Vectors of values.
    std::vector<isc::data::ConstElementPtr> values_;
};

/// @brief Shared pointer to a CfgGlobals instance.
typedef boost::shared_ptr<CfgGlobals> CfgGlobalsPtr;

} // namespace isc::dhcp
} // namespace isc

#endif // CFG_GLOBALS_H
