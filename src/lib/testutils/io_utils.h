// Copyright (C) 2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef TEST_IO_UTILS_H
#define TEST_IO_UTILS_H

#include <string>

namespace isc {
namespace dhcp {
namespace test {

/// @brief Checks if specified file exists.
///
/// @param file_path Path to a file.
/// @return true if the file exists, false otherwise.
bool fileExists(const std::string& file_path);

/// @brief Reads contents of the specified file.
///
/// @param file_path Path to a file.
/// @return File contents.
std::string readFile(const std::string& file_path);

}; // end of isc::dhcp::test namespace
}; // end of isc::dhcp namespace
}; // end of isc namespace

#endif // TEST_IO_UTILS_H
