// Copyright (C) 2014 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef CONFIG_RESULT_CHECK_H
#define CONFIG_RESULT_CHECK_H

#include <cc/data.h>

namespace isc {
namespace dhcp {
namespace test {

/// @brief Checks that the error string created by the configuration parsers
/// contains the location of the data element...
///
/// This function checks that the error string returned by the configuration
/// parsers contains the position of the element which caused an error. The
/// error string is expected to contain at least one occurence of the following:
///
/// @code
///     [filename]:[linenum]:[pos]
/// @endcode
///
/// where:
/// - [filename] is a configuration file name (provided by a caller),
/// - [linenum] is a line number of the element,
/// - [pos] is a position of the element within the line.
///
/// Both [linenum] and [pos] must contain decimal digits. The [filename]
/// must match the name provided by the caller.
///
/// @param error_element A result returned by the configuration.
/// @param file_name A configuration file name.
///
/// @return true if the provided configuration result comprises a string
/// which holds a position of the data element which caused the error;
/// false otherwise.
bool errorContainsPosition(isc::data::ConstElementPtr error_element,
                           const std::string& file_name);

}
}
}

#endif
