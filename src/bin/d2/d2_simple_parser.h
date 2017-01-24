// Copyright (C) 2017 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef D2_SIMPLE_PARSER_H
#define D2_SIMPLE_PARSER_H

#include <cc/simple_parser.h>

namespace isc {
namespace d2 {

/// @brief SimpleParser specialized for D2
///
/// This class is a @ref isc::data::SimpleParser dedicated to D2.
/// In particular, it contains all the default values and names of the
/// parameters that are to be derived (inherited) between scopes.
/// For the actual values, see @file d2_simple_parser.cc
class D2SimpleParser : public isc::data::SimpleParser {
public:

    /// @brief Sets all defaults for D2 configuration
    ///
    /// This method sets global and element defaults.
    ///
    /// @param global scope to be filled in with defaults.
    /// @return number of default values added
    static size_t setAllDefaults(isc::data::ElementPtr global);

    // see d2_simple_parser.cc for comments for those parameters
    static const isc::data::SimpleDefaults D2_GLOBAL_DEFAULTS;
};

};
};

#endif
