// Copyright (C) 2017 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <cc/data.h>
#include <cc/dhcp_config_error.h>
#include <hooks/hooks_parser.h>
#include <hooks/hooks_manager.h>
#include <boost/algorithm/string.hpp>
#include <boost/foreach.hpp>
#include <util/strutil.h>
#include <vector>

using namespace std;
using namespace isc::data;
using namespace isc::hooks;
using namespace isc::dhcp;

namespace isc {
namespace hooks {

// ******************** HooksLibrariesParser *************************
void
HooksLibrariesParser::parse(ConstElementPtr value) {
    // Initialize.
    libraries_.clear();

    if (!value) {
        isc_throw(DhcpConfigError, "Tried to parse null hooks libraries");
    }

    // Let's store
    position_ = value->getPosition();

    // This is the new syntax.  Iterate through it and get each map.
    BOOST_FOREACH(ConstElementPtr library_entry, value->listValue()) {
        ConstElementPtr parameters;

        // Is it a map?
        if (library_entry->getType() != Element::map) {
            isc_throw(DhcpConfigError, "hooks library configuration error:"
                " one or more entries in the hooks-libraries list is not"
                " a map (" << library_entry->getPosition() << ")");
        }

        // Iterate through each element in the map.  We check
        // whether we have found a library element.
        bool lib_found = false;

        string libname = "";

        // Let's explicitly reset the parameters, so we won't cover old
        // values from the previous loop round.
        parameters.reset();

        BOOST_FOREACH(auto entry_item, library_entry->mapValue()) {
            if (entry_item.first == "library") {
                if (entry_item.second->getType() != Element::string) {
                    isc_throw(DhcpConfigError, "hooks library configuration"
                        " error: value of 'library' element is not a string"
                        " giving the path to a hooks library (" <<
                        entry_item.second->getPosition() << ")");
                }

                // Get the name of the library and add it to the list after
                // removing quotes.
                libname = (entry_item.second)->stringValue();

                // Remove leading/trailing quotes and any leading/trailing
                // spaces.
                boost::erase_all(libname, "\"");
                libname = isc::util::str::trim(libname);
                if (libname.empty()) {
                    isc_throw(DhcpConfigError, "hooks library configuration"
                        " error: value of 'library' element must not be"
                        " blank (" <<
                        entry_item.second->getPosition() << ")");
                }

                // Note we have found the library name.
                lib_found = true;
                continue;
            }

            // If there are parameters, let's remember them.
            if (entry_item.first == "parameters") {
                parameters = entry_item.second;
                continue;
            }

            // For all other parameters we will throw.
            isc_throw(DhcpConfigError, "unknown hooks library parameter: "
                      << entry_item.first << "("
                      << library_entry->getPosition() << ")");
        }

        if (! lib_found) {
            isc_throw(DhcpConfigError, "hooks library configuration error:"
                " one or more hooks-libraries elements are missing the"
                " name of the library"  <<
                " (" << library_entry->getPosition() << ")");
        }

        libraries_.push_back(make_pair(libname, parameters));
    }
}

void HooksLibrariesParser::verifyLibraries() {
    // Check if the list of libraries has changed.  If not, nothing is done
    // - the command "DhcpN libreload" is required to reload the same
    // libraries (this prevents needless reloads when anything else in the
    // configuration is changed).

    // We no longer rely on this. Parameters can change. And even if the
    // parameters stay the same, they could point to files that could
    // change.
    vector<string> current_libraries = HooksManager::getLibraryNames();
    if (current_libraries.empty() && libraries_.empty()) {
        return;
    }

    // Library list has changed, validate each of the libraries specified.
    vector<string> lib_names = isc::hooks::extractNames(libraries_);
    vector<string> error_libs = HooksManager::validateLibraries(lib_names);
    if (!error_libs.empty()) {

        // Construct the list of libraries in error for the message.
        string error_list = error_libs[0];
        for (size_t i = 1; i < error_libs.size(); ++i) {
            error_list += (string(", ") + error_libs[i]);
        }
        isc_throw(DhcpConfigError, "hooks libraries failed to validate - "
                  "library or libraries in error are: " << error_list
                  << "(" << position_ << ")");
    }
}

void
HooksLibrariesParser::loadLibraries() {
    /// Commits the list of libraries to the configuration manager storage if
    /// the list of libraries has changed.
    /// @todo: Delete any stored CalloutHandles before reloading the
    /// libraries
    if (!HooksManager::loadLibraries(libraries_)) {
        isc_throw(DhcpConfigError, "One or more hook libraries failed to load");
    }
}

// Method for testing
void
HooksLibrariesParser::getLibraries(isc::hooks::HookLibsCollection& libraries) {
    libraries = libraries_;
}

}
}
