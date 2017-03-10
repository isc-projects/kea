// Copyright (C) 2017 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef GET_CONFIG_UNITTEST_H
#define GET_CONFIG_UNITTEST_H

#include <string.h>

namespace isc {
namespace dhcp {
namespace test {

/// @brief Extract a configuration as a C++ source for JSON on std::cerr
///
/// This function should be called when a configuration in an unit test
/// is interesting and should be extracted. Do nothing when extract_count
/// is negative.
void extractConfig(const std::string& config);

};
};
};

#endif // GET_CONFIG_UNITTEST_H
