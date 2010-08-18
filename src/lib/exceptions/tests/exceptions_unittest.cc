// Copyright (C) 2009  Internet Systems Consortium, Inc. ("ISC")
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

// $Id$

#include <stdexcept>
#include <string>

#include <exceptions/exceptions.h>

#include <gtest/gtest.h>

using isc::Exception;

namespace {

class ExceptionTest : public ::testing::Test {
protected:
    ExceptionTest() : teststring("test") {}
    const char* teststring;
};

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
}
