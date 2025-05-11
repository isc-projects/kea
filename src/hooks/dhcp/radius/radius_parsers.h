// Copyright (C) 2020-2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef RADIUS_PARSER_H
#define RADIUS_PARSER_H

#include <radius.h>
#include <radius_access.h>
#include <radius_accounting.h>
#include <cc/data.h>
#include <cc/simple_parser.h>
#include <set>

namespace isc {
namespace radius {

/// @brief Configuration parser for Radius.
class RadiusConfigParser : public data::SimpleParser {
public:

    /// @brief Parses Radius configuration.
    ///
    /// @param config Specified configuration (mutable).
    /// @throw ConfigError when parsing fails or configuration is invalid.
    void parse(data::ElementPtr& config);

    /// @brief Keywords (aka global configuration entry names).
    static const std::set<std::string> RADIUS_KEYWORDS;

    /// @brief Defaults for Radius configuration.
    static const data::SimpleDefaults RADIUS_DEFAULTS;

    /// @brief Needed standard attributes definitions.
    static const AttrDefList USED_STANDARD_ATTR_DEFS;
};

/// @brief Service parser for Radius.
class RadiusServiceParser : public data::SimpleParser {
public:

    /// @brief Parses Radius service.
    ///
    /// @param service Pointer to the service.
    /// @param srv_cfg Service configuration.
    /// @throw ConfigError when something goes wrong.
    void parse(const RadiusServicePtr& service,
               const data::ConstElementPtr& srv_cfg);

    /// @brief Keywords (aka service configuration entry names).
    static const std::set<std::string> SERVICE_KEYWORDS;

    /// @brief Check Radius attributes.
    ///
    /// @param service Pointer to the service.
    /// @throw ConfigError when something goes wrong.
    void checkAttributes(const RadiusServicePtr& service);
};

/// @brief Server list parser for Radius.
class RadiusServerListParser : public data::SimpleParser {
public:

    /// @brief Parses Radius server list.
    ///
    /// @param service Pointer to the service.
    /// @param srv_list Server list configuration.
    /// @throw ConfigError when something goes wrong.
    void parse(const RadiusServicePtr& service,
               const data::ConstElementPtr& srv_list);
};

/// @brief Server parser for Radius.
class RadiusServerParser : public data::SimpleParser {
public:

    /// @brief Parses Radius server.
    ///
    /// @param service Pointer to the service.
    /// @param server Server configuration.
    /// @throw ConfigError when something goes wrong.
    void parse(const RadiusServicePtr& service,
               const data::ElementPtr& server);
};

/// @brief Attribute list parser for Radius.
class RadiusAttributeListParser : public data::SimpleParser {
public:

    /// @brief Parses Radius list of attribute configurations.
    ///
    /// @param service Pointer to the service.
    /// @param attr_list Attribute configuration.
    /// @throw ConfigError when something goes wrong.
    void parse(const RadiusServicePtr& service,
               const data::ConstElementPtr& attr_list);
};

/// @brief  Attribute configuration parser for Radius.
class RadiusAttributeParser : public data::SimpleParser {
public:

    /// @brief Parses Radius attribute configuration.
    ///
    /// @param service Pointer to the service.
    /// @param attr Attribute configuration.
    /// @throw ConfigError when something goes wrong.
    void parse(const RadiusServicePtr& service, const data::ElementPtr& attr);

    /// @brief Defaults for Radius attribute configuration.
    static const data::SimpleDefaults ATTRIBUTE_DEFAULTS;
};

} // end of namespace isc::radius
} // end of namespace isc

#endif
