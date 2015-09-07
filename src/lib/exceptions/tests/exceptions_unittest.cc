// Copyright (C) 2009, 2015  Internet Systems Consortium, Inc. ("ISC")
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

#include <stdexcept>
#include <string>

#include <exceptions/exceptions.h>
#include <sstream>

#include <gtest/gtest.h>

using isc::Exception;

namespace {

class ExceptionTest : public ::testing::Test {
protected:
    ExceptionTest() : teststring("test") {}
    const char* teststring;
};

void raise_foobar() {
    isc_throw(isc::BadValue, "foobar");
}

TEST_F(ExceptionTest, basicMethods) {
    try {
        isc_throw(Exception, teststring);
    } catch (Exception& ex) {
        EXPECT_EQ(ex.getMessage(), std::string(teststring));
        EXPECT_EQ(ex.getFile(), std::string(__FILE__));
        EXPECT_EQ(ex.getLine(), __LINE__ - 4);
    }
}

// Test to see if it works as a proper derived class of std::exception.
TEST_F(ExceptionTest, stdInheritance) {
    try {
        isc_throw(Exception, teststring);
    } catch (std::exception& ex) {
        EXPECT_EQ(std::string(ex.what()), std::string(teststring));
    }
}

// Tests whether verbose is disabled by default and can be enabled, if
// needed.
TEST_F(ExceptionTest, verbose) {

    // This code is line numbers sensitive. Make sure no edits are done between
    // this line and isc_throw below. Update that +3 offset, if needed.
    std::stringstream expected;
    expected << teststring << "[" << std::string(__FILE__)
             << ":" << int(__LINE__ + 3) << "]";

    try {
        isc_throw(Exception, teststring);
    } catch (const isc::Exception& ex) {
        EXPECT_EQ(std::string(ex.what()), std::string(teststring));
        EXPECT_EQ(std::string(ex.what(false)), std::string(teststring));
        EXPECT_EQ(expected.str(), std::string(ex.what(true)));
    }

}

// Test matching message.
TEST_F(ExceptionTest, message) {
    try {
        raise_foobar();
        ADD_FAILURE() << "Expected " "raise_foobar()" \
            " throws an exception of type " "BadValue" \
            ".\n Actual: it throws nothing.";
    } catch (const isc::BadValue& ex) {
        EXPECT_EQ(std::string(ex.getMessage()), "foobar");
    } catch (...) {
        ADD_FAILURE() << "Expected " "raise_foobar()" \
            " throws an exception of type " "BadValue" \
            ".\n Actual: it throws a different type.";
    }
}

}
