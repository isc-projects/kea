// Copyright (C) 2016-2020 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef SIMPLE_PARSER4_H
#define SIMPLE_PARSER4_H

#include <cc/simple_parser.h>

namespace isc {
namespace dhcp {

/// @brief SimpleParser specialized for DHCPv4
///
/// This class is a @ref isc::data::SimpleParser dedicated to DHCPv4 parser.
/// In particular, it contains all the default values and names of the
/// parameters that are to be derived (inherited) between scopes.
/// For the actual values, see @file simple_parser4.cc
class SimpleParser4 : public isc::data::SimpleParser {
public:

    /// @brief Sets all defaults for DHCPv4 configuration
    ///
    /// This method sets global, option data and option definitions defaults.
    ///
    /// @param global scope to be filled in with defaults.
    /// @return number of default values added
    static size_t setAllDefaults(isc::data::ElementPtr global);

    /// @brief Derives (inherits) all parameters from global to more specific scopes.
    ///
    /// This method currently does the following:
    /// - derives global parameters to subnets (lifetimes for now)
    /// @param global scope to be modified if needed (subnet4 will be extracted)
    /// @return number of default values derived
    static size_t deriveParameters(isc::data::ElementPtr global);

    // see simple_parser4.cc for comments for those parameters
    static const isc::data::SimpleKeywords GLOBAL4_PARAMETERS;
    static const isc::data::SimpleDefaults GLOBAL4_DEFAULTS;

    static const isc::data::SimpleKeywords OPTION4_DEF_PARAMETERS;
    static const isc::data::SimpleDefaults OPTION4_DEF_DEFAULTS;

    static const isc::data::SimpleKeywords OPTION4_PARAMETERS;
    static const isc::data::SimpleDefaults OPTION4_DEFAULTS;

    static const isc::data::SimpleKeywords SUBNET4_PARAMETERS;
    static const isc::data::SimpleDefaults SUBNET4_DEFAULTS;
    static const isc::data::SimpleDefaults SHARED_SUBNET4_DEFAULTS;
    static const isc::data::ParamsList INHERIT_TO_SUBNET4;

    static const isc::data::SimpleKeywords POOL4_PARAMETERS;

    static const isc::data::SimpleKeywords SHARED_NETWORK4_PARAMETERS;
    static const isc::data::SimpleDefaults SHARED_NETWORK4_DEFAULTS;

    static const isc::data::SimpleDefaults IFACE4_DEFAULTS;
    static const isc::data::SimpleDefaults DHCP_QUEUE_CONTROL4_DEFAULTS;
    static const isc::data::SimpleDefaults DHCP_MULTI_THREADING4_DEFAULTS;
    static const isc::data::SimpleDefaults SANITY_CHECKS4_DEFAULTS;
};

}  // namespace dhcp
}  // namespace isc

#endif
