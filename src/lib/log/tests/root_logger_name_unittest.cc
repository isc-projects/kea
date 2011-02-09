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

#include <string>

#include <gtest/gtest.h>

#include <log/root_logger_name.h>

using namespace isc;
using namespace isc::log;

class RootLoggerNameTest : public ::testing::Test {
protected:
    RootLoggerNameTest()
    {
    }
};

// Check of the (only) functionality of the class.

TEST_F(RootLoggerNameTest, SetGet) {
    const std::string name1 = "test1";
    const std::string name2 = "test2";

    // Check that Set/Get works
    setRootLoggerName(name1);
    EXPECT_EQ(name1, getRootLoggerName());

    // We could not test that the root logger name is initialised
    // correctly (as there is one instance of it and we don't know
    // when this test will be run) so to check that setName() actually
    // does change the name, run the test again with a different name.
    //
    // (There was always the outside chance that the root logger name
    // was initialised with name1 and that setName() has no effect.)
    setRootLoggerName(name2);
    EXPECT_EQ(name2, getRootLoggerName());
}
