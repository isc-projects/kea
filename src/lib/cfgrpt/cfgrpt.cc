// Copyright (C) 2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <sstream>

#include <cfgrpt/config_report.h>

namespace isc {
namespace detail {

// The config_report array ends with an empty line ("")
// Each line before this final one starts with four semicolons (;;;;)
// in order to be easy to extract from binaries.
std::string
getConfigReport() {
    std::stringstream tmp;

    size_t linenum = 0;
    for (;;) {
        const char* const line = config_report[linenum++];
        if (line[0] == '\0')
            break;
        tmp << line + 4 << std::endl;
    }
    return (tmp.str());
}

}
}
