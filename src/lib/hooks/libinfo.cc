// Copyright (C) 2016-2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <hooks/libinfo.h>

namespace isc {
namespace hooks {

HookLibInfo::HookLibInfo(const std::string& libname,
                         isc::data::ConstElementPtr parameters,
                         const std::string& cfgname /* = "" */)
    : libname_(libname), parameters_(parameters),
     cfgname_ (cfgname.empty() ? libname : cfgname) {
}

/// @brief Extracts names from HookLibsCollection
///
/// @param libraries Hook libraries collection
/// @return vector of strings with library names
std::vector<std::string>
extractNames(const isc::hooks::HookLibsCollection& libraries) {
    std::vector<std::string> names;

    for (auto const& it : libraries) {
        names.push_back(it.libname_);
    }
    return (names);
}

bool
HookLibInfo::operator==(const HookLibInfo& other) const {
    return ((libname_ == other.libname_) &&
            (cfgname_ == other.cfgname_) &&
            ((!parameters_ && !other.parameters_) ||
             (parameters_ && other.parameters_ &&
              parameters_->equals(*(other.parameters_)))));
}

};
};
