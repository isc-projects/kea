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

#include <log/logger_specification.h>
#include <log/output_option.h>

using namespace isc::log;
using namespace std;

/// \brief LoggerSpecification Test
class LoggerSpecificationTest : public ::testing::Test {
public:
    LoggerSpecificationTest()
    {}
    ~LoggerSpecificationTest()
    {}
};


// Check default initialization.
TEST_F(LoggerSpecificationTest, DefaultInitialization) {
    LoggerSpecification spec;

    EXPECT_EQ(string(""), spec.getName());
    EXPECT_EQ(isc::log::INFO, spec.getSeverity());
    EXPECT_EQ(0, spec.getDbglevel());
    EXPECT_FALSE(spec.getAdditive());
    EXPECT_EQ(0, spec.optionCount());
}

// Non-default initialization
TEST_F(LoggerSpecificationTest, Initialization) {
    LoggerSpecification spec("alpha", isc::log::ERROR, 42, true);

    EXPECT_EQ(string("alpha"), spec.getName());
    EXPECT_EQ(isc::log::ERROR, spec.getSeverity());
    EXPECT_EQ(42, spec.getDbglevel());
    EXPECT_TRUE(spec.getAdditive());
    EXPECT_EQ(0, spec.optionCount());
}

// Get/Set tests
TEST_F(LoggerSpecificationTest, SetGet) {
    LoggerSpecification spec;

    spec.setName("gamma");
    EXPECT_EQ(string("gamma"), spec.getName());

    spec.setSeverity(isc::log::FATAL);
    EXPECT_EQ(isc::log::FATAL, spec.getSeverity());

    spec.setDbglevel(7);
    EXPECT_EQ(7, spec.getDbglevel());

    spec.setAdditive(true);
    EXPECT_TRUE(spec.getAdditive());

    // Should not affect option count
    EXPECT_EQ(0, spec.optionCount());
}

// Check option setting
TEST_F(LoggerSpecificationTest, AddOption) {
    OutputOption option1;
    option1.destination = OutputOption::DEST_FILE;
    option1.filename = "/tmp/example.log";
    option1.maxsize = 123456;

    OutputOption option2;
    option2.destination = OutputOption::DEST_SYSLOG;
    option2.facility = "LOCAL7";

    LoggerSpecification spec;
    spec.addOutputOption(option1);
    spec.addOutputOption(option2);
    EXPECT_EQ(2, spec.optionCount());

    // Iterate through them
    LoggerSpecification::const_iterator i = spec.begin();

    EXPECT_EQ(OutputOption::DEST_FILE, i->destination);
    EXPECT_EQ(string("/tmp/example.log"), i->filename);
    EXPECT_EQ(123456, i->maxsize);

    ++i;
    EXPECT_EQ(OutputOption::DEST_SYSLOG, i->destination);
    EXPECT_EQ(string("LOCAL7"), i->facility);

    ++i;
    EXPECT_TRUE(i == spec.end());
}


TEST(LoggerSpecification, getSeverity) {
    EXPECT_EQ(DEBUG, getSeverity("DEBUG"));
    EXPECT_EQ(DEBUG, getSeverity("debug"));
    EXPECT_EQ(DEBUG, getSeverity("DeBuG"));
    EXPECT_EQ(INFO, getSeverity("INFO"));
    EXPECT_EQ(INFO, getSeverity("info"));
    EXPECT_EQ(INFO, getSeverity("iNfO"));
    EXPECT_EQ(WARN, getSeverity("WARN"));
    EXPECT_EQ(WARN, getSeverity("warn"));
    EXPECT_EQ(WARN, getSeverity("wARn"));
    EXPECT_EQ(ERROR, getSeverity("ERROR"));
    EXPECT_EQ(ERROR, getSeverity("error"));
    EXPECT_EQ(ERROR, getSeverity("ERRoR"));
    EXPECT_EQ(FATAL, getSeverity("FATAL"));
    EXPECT_EQ(FATAL, getSeverity("fatal"));
    EXPECT_EQ(FATAL, getSeverity("FAtaL"));

    // bad values should default to stdout
    EXPECT_EQ(INFO, getSeverity("some bad value"));
    EXPECT_EQ(INFO, getSeverity(""));
}
