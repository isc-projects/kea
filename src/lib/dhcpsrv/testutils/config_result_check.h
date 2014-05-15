// Copyright (C) 2014 Internet Systems Consortium, Inc. ("ISC")
//
// Permission to use, copy, modify, and/or distribute this software for any
// purpose with or without fee is hereby granted, provided that the above
// copyright notice and this permission notice appear in all copies.
//
// THE SOFTWARE IS PROVIDED "AS IS" AND ISC DISCLAIMS ALL WARRANTIES WITH
// REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
// AND FITNESS.  IN NO EVENT SHALL ISC BE LIABLE FOR ANY SPECIAL, DIRECT,
// INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
// LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE
// OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
// PERFORMANCE OF THIS SOFTWARE.

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
