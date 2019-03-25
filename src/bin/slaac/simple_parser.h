// Copyright (C) 2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef SLAAC_SIMPLE_PARSER_H
#define SLAAC_SIMPLE_PARSER_H

#include <cc/simple_parser.h>
#include <slaac/slaac_cfg_mgr.h>

using namespace isc::data;

namespace isc {
namespace slaac {

/// @brief SimpleParser specialized for Slaac
///
/// This class is a @ref isc::data::SimpleParser dedicated to Slaac.
/// In particular, it contains all the default values for the whole
/// slaac defaults.
///
/// For the actual values, see @file slaac/simple_parser.cc
class SlaacSimpleParser : public isc::data::SimpleParser {
public:
    /// @brief Sets all defaults for Slaac configuration
    ///
    /// This method sets global, option data and option definitions defaults.
    ///
    /// @param global scope to be filled in with defaults.
    /// @return number of default values added
    static size_t setAllDefaults(const isc::data::ElementPtr& global);

    /// @brief Derives (inherits) all parameters from global to more specific scopes.
    ///
    /// This method currently does the following:
    /// - derives global parameters to managed servers (flags for now)
    /// @param global scope to be modified if needed
    /// @return number of default values derived
    static size_t deriveParameters(isc::data::ConstElementPtr global);

    /// @brief Parses the slaac configuration
    ///
    /// @param ctx - parsed information will be stored here
    /// @param config - Element tree structure that holds configuration
    /// @param check_only - if true the configuration is verified only, not applied
    ///
    /// @throw ConfigError if any issues are encountered.
    void parse(const SlaacConfigPtr& ctx,
               const isc::data::ConstElementPtr& config,
               bool check_only);

    // see simple_parser.cc for comments for those parameters
    static const isc::data::SimpleKeywords SLAAC_PARAMETERS;
    static const isc::data::SimpleDefaults SLAAC_DEFAULTS;
    static const isc::data::SimpleRequiredKeywords PREFIX_INFO_REQUIRED;
    static const isc::data::SimpleKeywords PREFIX_INFO_PARAMETERS;
    static const isc::data::SimpleDefaults PREFIX_INFO_DEFAULTS;

private:
    void parsePrefixInfos(const SlaacConfigPtr& config,
                          const ConstElementPtr& json);

    void parseExperimental(const SlaacConfigPtr& config,
                           const ConstElementPtr& json);

    void parseInterfaces(const SlaacConfigPtr& config,
                         const ConstElementPtr& json);

};

};
};
#endif
