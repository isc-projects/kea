// Copyright (C) 2017 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef HOOKS_PARSER_H
#define HOOKS_PARSER_H

#include <cc/data.h>
#include <cc/simple_parser.h>
#include <hooks/hooks_config.h>

namespace isc {
namespace hooks {

/// @brief Parser for hooks library list
///
/// This parser handles the list of hooks libraries.  This is an optional list,
/// which may be empty, and is encapsulated into a @ref HooksConfig object.
class HooksLibrariesParser : public isc::data::SimpleParser {
public:

    /// @brief Parses parameters value
    ///
    /// Parses configuration entry (list of parameters) and adds each element
    /// to the hooks libraries list.  The method also checks whether the
    /// list of libraries is the same as that already loaded.  If not, it
    /// checks each of the libraries in the list for validity (they exist and
    /// have a "version" function that returns the correct value).
    ///
    /// The syntax for specifying hooks libraries allow for library-specific
    /// parameters to be specified along with the library, e.g.
    ///
    /// @code
    ///      "hooks-libraries": [
    ///          {
    ///              "library": "hook-lib-1.so",
    ///              "parameters": {
    ///                  "alpha": "a string",
    ///                  "beta": 42
    ///              }
    ///          },
    ///          :
    ///      ]
    /// @endcode
    ///
    /// The parsing code only checks that:
    ///
    /// -# Each element in the hooks-libraries list is a map
    /// -# The map contains an element "library" whose value is a not blank string
    /// -# That there is an optional 'parameters' element.
    /// -# That there are no other element.
    ///
    /// This method stores parsed libraries in libraries.
    ///
    /// @param libraries parsed libraries information will be stored here
    /// @param value pointer to the content to be parsed
    void parse(HooksConfig& libraries, isc::data::ConstElementPtr value);
};

}; // namespace isc::hooks
}; // namespace isc

#endif
