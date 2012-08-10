// Copyright (C) 2011  Internet Systems Consortium, Inc. ("ISC")
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

#include <istream>
#include <string>
#include <sstream>

#include <gtest/gtest.h>

#ifndef __UTIL_UNITTESTS_TEXTDATA_H
#define __UTIL_UNITTESTS_TEXTDATA_H 1

/**
 * \file textdata.h
 * \brief Utilities for tests with text data.
 *
 * This utility provides convenient helper functions for unit tests using
 * textual data.
 */

namespace isc {
namespace util {
namespace unittests {

/// Line-by-line text comparison.
///
/// This templated function takes two standard input streams, extracts
/// strings from them, and compares the two sets of strings line by line.
template <typename EXPECTED_STREAM, typename ACTUAL_STREAM>
void
matchTextData(EXPECTED_STREAM& expected, ACTUAL_STREAM& actual) {
    std::string actual_line;
    std::string expected_line;
    while (std::getline(actual, actual_line), !actual.eof()) {
        std::getline(expected, expected_line);
        if (expected.eof()) {
            FAIL() << "Redundant line in actual output: " << actual_line;
            break;
        }
        if (actual.bad() || actual.fail() ||
            expected.bad() || expected.fail()) {
            throw std::runtime_error("Unexpected error in data streams");
        }
        EXPECT_EQ(expected_line, actual_line);
    }
    while (std::getline(expected, expected_line), !expected.eof()) {
        ADD_FAILURE() << "Missing line in actual output: " << expected_line;
    }
}

/// Similar to the fully templated version, but takes string for the second
/// (actual) data.
///
/// Due to the nature of textual data, it will often be the case that test
/// data is given as a string object.  This shortcut version helps such cases
/// so that the test code doesn't have to create a string stream with the
/// string data just for testing.
template <typename EXPECTED_STREAM>
void
matchTextData(EXPECTED_STREAM& expected, const std::string& actual_text) {
    std::istringstream iss(actual_text);
    matchTextData(expected, iss);
}

/// Same for the previous version, but the first argument is string.
template <typename ACTUAL_STREAM>
void
matchTextData(const std::string& expected_text, ACTUAL_STREAM& actual) {
    std::istringstream iss(expected_text);
    matchTextData(iss, actual);
}

/// Same for the previous two, but takes strings for both expected and
/// actual data.
void
matchTextData(const std::string& expected_text,
              const std::string& actual_text)
{
    std::istringstream expected_is(expected_text);
    std::istringstream actual_is(actual_text);
    matchTextData(expected_is, actual_is);
}

}
}
}

#endif // __UTIL_UNITTESTS_TEXTDATA_H

// Local Variables:
// mode: c++
// End:
