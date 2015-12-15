// Copyright (C) 2013  Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include "marker_file.h"

#include <gtest/gtest.h>

#include <fstream>
#include <string>

namespace isc {
namespace dhcp {
namespace test {

using namespace std;

// Check the marker file.

bool
checkMarkerFile(const char* name, const char* expected) {
    // Open the file for input
    fstream file(name, fstream::in);

    // Is it open?
    if (!file.is_open()) {
        ADD_FAILURE() << "Unable to open " << name << ". It was expected "
                      << "to be present and to contain the string '"
                      << expected << "'";
        return (false);
    }

    // OK, is open, so read the data and see what we have.  Compare it
    // against what is expected.
    string content;
    getline(file, content);

    string expected_str(expected);
    EXPECT_EQ(expected_str, content) << "Marker file " << name
        << "did not contain the expected data";
    file.close();

    return (expected_str == content);
}

// Check if the marker file exists - this is a wrapper for "access(2)" and
// really tests if the file exists and is accessible

bool
checkMarkerFileExists(const char* name) {
    return (access(name, F_OK) == 0);
}

} // namespace test
} // namespace dhcp
} // namespace isc
