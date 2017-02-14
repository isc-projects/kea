// Copyright (C) 2017 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef HOOKS_PARSER_H
#define HOOKS_PARSER_H

#include <cc/data.h>
#include <cc/simple_parser.h>
#include <hooks/libinfo.h>

namespace isc {
namespace hooks {

/// @brief Parser for hooks library list
///
/// This parser handles the list of hooks libraries.  This is an optional list,
/// which may be empty.
///
/// However, the parser does more than just check the list of library names.
/// It does two other things:
///
/// -# The problem faced with the hooks libraries is that we wish to avoid
/// reloading the libraries if they have not changed.  (This would cause the
/// "unload" and "load" methods to run.  Although libraries should be written
/// to cope with this, it is feasible that such an action may be costly in
/// terms of time and resources, or may cause side effects such as clearing
/// an internal cache.)  To this end, the parser also checks the list against
/// the list of libraries current loaded and notes if there are changes.
/// -# If there are, the parser validates the libraries; it opens them and
/// checks that the "version" function exists and returns the correct value.
///
/// Only if the library list has changed and the libraries are valid will the
/// change be applied.
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
    /// If you want to check whether the library is really present (if the file
    /// is on disk, it is really a library and that it could be loaded), call
    /// @ref verifyLibraries().
    ///
    /// This method stores parsed libraries in libraries_.
    ///
    /// @param value pointer to the content of parsed values
    void parse(isc::data::ConstElementPtr value);

    /// @brief Verifies that libraries stored in libraries_ are valid.
    ///
    /// This method is a smart wrapper around @ref
    /// isc::hooks::HooksManager::validateLibraries().
    /// It tries to validate all the libraries stored in libraries_.
    /// @throw DhcpConfigError if any issue is discovered.
    void verifyLibraries();

    /// @brief Commits hooks libraries data
    ///
    /// This method calls necessary methods in HooksManager that will unload
    /// any libraries that may be currently loaded and will load the actual
    /// libraries. Providing that the specified libraries are valid and are
    /// different to those already loaded, this method loads the new set of
    /// libraries (and unloads the existing set).
    ///
    /// @throw DhcpConfigError if the call to HooksManager fails.
    void loadLibraries();

    /// @brief Returns list of parsed libraries
    ///
    /// Principally for testing, this returns the list of libraries as well as
    /// an indication as to whether the list is different from the list of
    /// libraries already loaded.
    ///
    /// @param [out] libraries List of libraries that were specified in the
    ///        new configuration.
    void getLibraries(isc::hooks::HookLibsCollection& libraries);

private:
    /// List of hooks libraries with their configuration parameters
    isc::hooks::HookLibsCollection libraries_;

    /// Position of the original element is stored in case we need to report an
    /// error later.
    isc::data::Element::Position position_;
};

}; // namespace isc::hooks
}; // namespace isc

#endif
