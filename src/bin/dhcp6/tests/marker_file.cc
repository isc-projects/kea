// Copyright (C) 2013  Internet Systems Consortium, Inc. ("ISC")
//
// Permission to use, copy, modify, and/or distribute this software for any
// purpose with or without fee is hereby granted, provided that the above
// copyright notice and this permission notice appear in all copies.
//
// THE SOFTWARE IS PROVIDED "AS IS" AND ISC DISCLAIMS ALL WARRANTIES WITH
// REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
// AND FITNESS.  IN NO EVENT SHALL ISC BE LIABLE FOR ANY SPECIAL, DIRECT,
// INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
// LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE
// OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
// PERFORMANCE OF THIS SOFTWARE.

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
