// Copyright (C) 2016 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <hooks/libinfo.h>

namespace isc {
namespace hooks {

/// @brief Extracts names from HookLibsCollection
///
/// @param libraries Hook libraries collection
/// @return vector of strings with library names
std::vector<std::string>
extractNames(const isc::hooks::HookLibsCollection& libraries) {
    std::vector<std::string> names;

    for (isc::hooks::HookLibsCollection::const_iterator it = libraries.begin();
         it != libraries.end(); ++it) {
        names.push_back(it->first);
    }
    return (names);
}

};
};
