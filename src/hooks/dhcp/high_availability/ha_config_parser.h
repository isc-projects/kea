// Copyright (C) 2018-2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef HA_CONFIG_PARSER_H
#define HA_CONFIG_PARSER_H

#include <ha_config.h>
#include <cc/data.h>
#include <cc/simple_parser.h>
#include <string>

namespace isc {
namespace ha {

/// @brief Configuration parser for High Availability.
class HAConfigParser : public data::SimpleParser {
public:

    /// @brief Parses HA configuration.
    ///
    /// @param config specified configuration.
    /// @return Pointer to the object where parsed configuration is stored.
    /// @throw HAConfigValidationError when parsing fails or configuration is invalid.
    static HAConfigMapperPtr parse(const data::ConstElementPtr& config);

private:

    /// @brief Parses HA configuration and can throw various exceptions.
    ///
    /// @param [out] config_storage Pointer to the object where parsed configuration
    /// is going to be stored.
    ///
    /// @param config Specified configuration.
    static void parseAll(const HAConfigMapperPtr& config_storage,
                         const data::ConstElementPtr& config);

    /// @brief Parses HA configuration for a single relationship.
    ///
    /// This function is called multiple times from the @c parseAllInternal.
    ///
    /// @param [out] config_storage pointer to the object where parsed configuration
    /// is going to be stored.
    ///
    /// @param config specified configuration for a relationship.
    /// @throw ConfigError when parsing fails or configuration is invalid.
    static void parseOne(const HAConfigMapperPtr& config_storage,
                         const data::ElementPtr& config);

    /// @brief Validates and returns a value of the parameter.
    ///
    /// @param config configuration map from which the parameter should be
    /// retrieved.
    /// @param parameter_name parameter name to be fetched from the configuration.
    /// @tparam T parameter type, e.g. @c uint16_t, @c uint32_t etc.
    template<typename T>
    static T getAndValidateInteger(const data::ConstElementPtr& config,
                                   const std::string& parameter_name);

    /// @brief Logs various information related to the successfully parsed
    /// configuration.
    ///
    /// @param config_storage Pointer to the object where parsed configuration
    /// is stored.
    ///
    /// One example of such information is a warning message indicating that
    /// sending lease updates is disabled.
    static void logConfigStatus(const HAConfigMapperPtr& config_storage);

    /// @brief Validates dependencies between the relationships.
    ///
    /// @throw HAConfigValidationError when there are configuration errors
    /// between the relationships.
    static void validateRelationships(const HAConfigMapperPtr& config_storage);
};

} // end of namespace isc::ha
} // end of namespace isc

#endif
