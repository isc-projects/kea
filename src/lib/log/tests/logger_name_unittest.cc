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

#include <log/logger_name.h>

using namespace isc;
using namespace isc::log;

// Test class.  To avoid disturbing the root logger configuration in other
// tests in the suite, the root logger name is saved in the constructor and
// restored in the destructor.  However, this is a bit chicken and egg, as the
// functions used to do the save and restore are those being tested...
//
// Note that the root name is originally set by the initialization of the
// logging configuration done in main().

class LoggerNameTest : public ::testing::Test {
public:
    LoggerNameTest() :
        name_(getRootLoggerName())
    {}
    ~LoggerNameTest() {
        setRootLoggerName(name_);
    }

private:
    std::string     name_;  ///< Saved name
};

// Check setting and getting of root name

TEST_F(LoggerNameTest, RootNameSetGet) {
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

// Check expansion of name

TEST_F(LoggerNameTest, ExpandLoggerName) {
    const std::string ROOT = "example";
    const std::string NAME = "something";
    const std::string FULL_NAME = ROOT + "." + NAME;

    setRootLoggerName(ROOT);
    EXPECT_EQ(ROOT, expandLoggerName(ROOT));
    EXPECT_EQ(FULL_NAME, expandLoggerName(NAME));
    EXPECT_EQ(FULL_NAME, expandLoggerName(FULL_NAME));
}

// Checks that the default logger name is returned properly.
TEST_F(LoggerNameTest, default) {
    EXPECT_EQ("kea", getDefaultRootLoggerName());
}
