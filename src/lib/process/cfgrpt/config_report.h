// Copyright (C) 2015-2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef CONFIG_REPORT_H
#define CONFIG_REPORT_H

#include <string>

namespace isc {
namespace detail {

extern const char* const config_report[];

// The config_report array ends with an empty line ("")
// Each line before this final one starts with four semicolons (;;;;)
// in order to be easy to extract from binaries.
std::string getConfigReport();

}
}

#endif // CONFIG_REPORT_H
