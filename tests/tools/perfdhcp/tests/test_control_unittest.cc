// Copyright (C) 2012 Internet Systems Consortium, Inc. ("ISC")
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

#include <cstddef>
#include <stdint.h>
#include <string>
#include <gtest/gtest.h>

#include "../test_control.h"
#include "../command_options.h"
#include "exceptions/exceptions.h"

using namespace std;
using namespace isc;
using namespace isc::perfdhcp;

/// \brief Test Fixture Class
///
/// This test fixture class is used to perform
/// unit tests on perfdhcp TestControl class.
class TestControlTest : public virtual ::testing::Test
{
public:
    /// \brief Default Constructor
    TestControlTest() { }

protected:
};

TEST_F(TestControlTest, Run) {
    // Get the instance of TestControl object.
    TestControl& test_control = TestControl::instance();
    // Running test without parsing command line arguments is
    // expected to cause exception.
    EXPECT_THROW(test_control.run(), isc::InvalidOperation);

    // The command line is to run single test iteration and exit.
    // We have to declare argv as const walk around the problem
    // of deprecated conversion from string to char*.
    const char* argv[] = { "perfdhcp", "-l", "eth0", "-r", "10", "-n", "1" };
    const int argc = sizeof(argv) / sizeof(argv[0]);
    CommandOptions& options = CommandOptions::instance();

    // const_cast is odd but it seems to be the most straight forward way
    // to achive the goal. In the future we might think about creating
    // a tokenizing function that would dynamically produce non-const
    // argv value.
    ASSERT_NO_THROW(options.parse(argc, const_cast<char**>(argv)));
    EXPECT_NO_THROW(test_control.run());

    // This is ok to run the test again with the same parameters.
    // It may trigger exception if TestControl singleton is in
    // invalid state after test run. We want to make sure it is
    // safe to rerun the test.
    EXPECT_NO_THROW(test_control.run());
}
