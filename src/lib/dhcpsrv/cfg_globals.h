// Copyright (C) 2021-2023 Internet Systems Consortium, Inc. ("ISC")
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
        DHCP4O6_PORT,
        COMMENT,
        SERVER_TAG,
        RESERVATION_MODE,
        RESERVATIONS_GLOBAL,
        RESERVATIONS_IN_SUBNET,
        RESERVATIONS_OUT_OF_POOL,
        CALCULATE_TEE_TIMES,
        T1_PERCENT,
        T2_PERCENT,
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
        CACHE_THRESHOLD,
        CACHE_MAX_AGE,
        EARLY_GLOBAL_RESERVATIONS_LOOKUP,
        IP_RESERVATIONS_UNIQUE,
        RESERVATIONS_LOOKUP_FIRST,
        DDNS_UPDATE_ON_RENEW,
        DDNS_USE_CONFLICT_RESOLUTION,
        PARKED_PACKET_LIMIT,
        ALLOCATOR,
        DDNS_TTL_PERCENT,

        // DHCPv4 specific parameters.
        ECHO_CLIENT_ID,
        MATCH_CLIENT_ID,
        AUTHORITATIVE,
        NEXT_SERVER,
        SERVER_HOSTNAME,
        BOOT_FILE_NAME,
        OFFER_LIFETIME,

        // DHCPv6 specific parameters.
        DATA_DIRECTORY,
        PREFERRED_LIFETIME,
        MIN_PREFERRED_LIFETIME,
        MAX_PREFERRED_LIFETIME,
        PD_ALLOCATOR,

        // Size sentinel.
        SIZE
    };

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

    /// @brief Type of name and value map.
    typedef std::map<std::string, isc::data::ConstElementPtr> MapType;

    /// @brief Returns configured parameters as a map.
    ///
    /// @note: the map includes only set global parameters i.e.
    /// ConstElementPtr values are never null.
    const MapType valuesMap() const;

    /// @brief Unparse configured global parameters.
    ///
    /// @return a pointer to unparsed global parameters.
    isc::data::ElementPtr toElement() const;

protected:
    /// @brief Vectors of values.
    std::vector<isc::data::ConstElementPtr> values_;
};

/// @brief Non-const shared pointer to a CfgGlobals instance.
typedef boost::shared_ptr<CfgGlobals> CfgGlobalsPtr;

/// @brief Const shared pointer to a CfgGlobals instance.
typedef boost::shared_ptr<const CfgGlobals> ConstCfgGlobalsPtr;

} // namespace isc::dhcp
} // namespace isc

#endif // CFG_GLOBALS_H
