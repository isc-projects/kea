// Copyright (C) 2017 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <dhcpsrv/cfg_hooks_libraries.h>
#include <hooks/hooks_manager.h>

using namespace std;
using namespace isc;
using namespace isc::data;
using namespace isc::hooks;

namespace isc {
namespace dhcp {

void
CfgHooksLibraries::verifyLibraries(const Element::Position& position) const {
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
        isc_throw(InvalidHooksLibraries,
                  "hooks libraries failed to validate - "
                  "library or libraries in error are: "
                  << error_list << "(" << position << ")");
    }
}

void
CfgHooksLibraries::loadLibraries() const {
    /// Commits the list of libraries to the configuration manager storage if
    /// the list of libraries has changed.
    /// @todo: Delete any stored CalloutHandles before reloading the
    /// libraries
    if (!HooksManager::loadLibraries(libraries_)) {
        isc_throw(InvalidHooksLibraries,
                  "One or more hook libraries failed to load");
    }
}

};
};
