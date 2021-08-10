// Copyright (C) 2017-2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <hooks/hooks_config.h>
#include <hooks/hooks_manager.h>

using namespace std;
using namespace isc;
using namespace isc::data;

namespace isc {
namespace hooks {

void
HooksConfig::verifyLibraries(const Element::Position& position) const {
    // The code used to follow this logic:
    //
    // Check if the list of libraries has changed.  If not, nothing is done
    // - the command "DhcpN libreload" is required to reload the same
    // libraries (this prevents needless reloads when anything else in the
    // configuration is changed).
    //
    // We no longer rely on this. Parameters can change. And even if the
    // parameters stay the same, they could point to files that could
    // change. We can skip loading routines only if there were and there still
    // are no libraries specified.
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
        isc_throw(InvalidHooksLibraries,
                  "hooks libraries failed to validate - "
                  "library or libraries in error are: "
                  << error_list << " (" << position << ")");
    }
}

void
HooksConfig::loadLibraries() const {
    /// Commits the list of libraries to the configuration manager storage if
    /// the list of libraries has changed.
    /// @todo: Delete any stored CalloutHandles before reloading the
    /// libraries
    if (!HooksManager::loadLibraries(libraries_)) {
        isc_throw(InvalidHooksLibraries,
                  "One or more hook libraries failed to load");
    }
}

bool
HooksConfig::equal(const HooksConfig& other) const {

    /// @todo: This comparision assumes that the library order is not relevant,
    /// so [ lib1, lib2 ] is equal to [ lib2, lib1 ]. However, this is not strictly
    /// true, because callouts execution is called in other they're loaded. Therefore
    /// changing the libraries order may change the server behavior.
    ///
    /// We don't have any libraries that are interacting (or would change their behavior
    /// depending on the order in which their callouts are executed), so the code is
    /// ok for now.
    for (isc::hooks::HookLibsCollection::const_iterator this_it = libraries_.begin();
         this_it != libraries_.end(); ++this_it) {
        bool match = false;
        for (isc::hooks::HookLibsCollection::const_iterator other_it =
                 other.libraries_.begin(); other_it != other.libraries_.end(); ++other_it) {
            if (this_it->first != other_it->first) {
                continue;
            }
            if (isNull(this_it->second) && isNull(other_it->second)) {
                match = true;
                break;
            }
            if (isNull(this_it->second) || isNull(other_it->second)) {
                continue;
            }
            if (this_it->second->equals(*other_it->second)) {
                match = true;
                break;
            }
        }
        // No match found for the particular hooks library so return false.
        if (!match) {
            return (false);
        }
    }
    return (true);
}

ElementPtr
HooksConfig::toElement() const {
    // hooks-libraries is a list of maps
    ElementPtr result = Element::createList();
    // Iterate through libraries
    for (HookLibsCollection::const_iterator hl = libraries_.begin();
         hl != libraries_.end(); ++hl) {
        // Entries are maps
        ElementPtr map = Element::createMap();
        // Set the library name
        map->set("library", Element::create(hl->first));
        // Set parameters (not set vs set empty map)
        if (!isNull(hl->second)) {
            map->set("parameters", hl->second);
        }
        // Push to the list
        result->add(map);
    }
    return (result);
}

};
};
