// Copyright (C) 2017-2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <cc/data.h>
#include <cc/dhcp_config_error.h>
#include <hooks/hooks_parser.h>
#include <boost/algorithm/string.hpp>
#include <util/filesystem.h>
#include <util/str.h>

#include <vector>

using namespace std;
using namespace isc::data;
using namespace isc::hooks;
using namespace isc::dhcp;
using namespace isc::util::file;

namespace isc {
namespace hooks {

namespace {
    // Singleton PathChecker to set and hold valid hooks library path.
    PathCheckerPtr hooks_path_checker_;
};

std::string
HooksLibrariesParser::getHooksPath(bool reset /* = false */, const std::string explicit_path /* = "" */) {
    if (!hooks_path_checker_ || reset) {
        hooks_path_checker_.reset(new PathChecker(DEFAULT_HOOKS_PATH, "KEA_HOOKS_PATH"));
        if (!explicit_path.empty()) {
            hooks_path_checker_->getPath(true, explicit_path);
        }
    }

    return (hooks_path_checker_->getPath());
}

std::string
HooksLibrariesParser::validatePath(const std::string libpath) {
    if (!hooks_path_checker_) {
        getHooksPath();
    }

    return (hooks_path_checker_->validatePath(libpath));
}

// @todo use the flat style, split into list and item

void
HooksLibrariesParser::parse(HooksConfig& libraries, ConstElementPtr value) {
    // Initialize.
    libraries.clear();

    if (!value) {
        isc_throw(DhcpConfigError, "Tried to parse null hooks libraries");
    }

    // This is the new syntax.  Iterate through it and get each map.
    for (auto const& library_entry : value->listValue()) {
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

        string cfgname = "";
        string libname = "";

        // Let's explicitly reset the parameters, so we won't cover old
        // values from the previous loop round.
        parameters.reset();

        for (auto const& entry_item : library_entry->mapValue()) {
            if (entry_item.first == "library") {
                if (entry_item.second->getType() != Element::string) {
                    isc_throw(DhcpConfigError, "hooks library configuration"
                        " error: value of 'library' element is not a string"
                        " giving the path to a hooks library (" <<
                        entry_item.second->getPosition() << ")");
                }

                // Get the name of the library and add it to the list after
                // removing quotes.
                try {
                    cfgname = (entry_item.second)->stringValue();
                    libname = validatePath(cfgname);
                } catch  (const std::exception& ex) {
                    isc_throw(DhcpConfigError, "hooks library configuration"
                        " error: " << ex.what() << " ("
                        << entry_item.second->getPosition() << ")");
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

        libraries.add(libname, parameters, cfgname);
    }
}

}
}
