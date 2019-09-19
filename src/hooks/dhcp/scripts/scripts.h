// Copyright (C) 2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef VARIABLES_H
#define VARIABLES_H

#include <string>
#include <vector>

namespace hooks {
namespace scripts {

    /// @brief keeps a list of variables.
    ///
    /// Each entry is supposed to have a string containing VARIABLE=VALUE
    typedef std::vector<std::string> Variables;

    /// @brief calls the actual scripts
    ///
    /// @param vars environment variables to be passed to the script.
    /// @return true if successful, false otherwise
    bool callScript(const Variables& vars);
};
};

#endif
