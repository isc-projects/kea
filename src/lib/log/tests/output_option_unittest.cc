// Copyright (C) 2011-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <string>

#include <gtest/gtest.h>

#include <log/output_option.h>

using namespace isc::log;
using namespace std;

// As OutputOption is a struct, the only meaningful test is to check that it
// initializes correctly.

TEST(OutputOptionTest, Initialization) {
    OutputOption option;

    EXPECT_EQ(OutputOption::DEST_CONSOLE, option.destination);
    EXPECT_EQ(OutputOption::STR_STDERR, option.stream);
    EXPECT_TRUE(option.flush);
    EXPECT_EQ(string("LOCAL0"), option.facility);
    EXPECT_EQ(string(""), option.filename);
    EXPECT_EQ(0, option.maxsize);
    EXPECT_EQ(0, option.maxver);
}

TEST(OutputOption, getDestination) {
    EXPECT_EQ(OutputOption::DEST_CONSOLE, getDestination("console"));
    EXPECT_EQ(OutputOption::DEST_CONSOLE, getDestination("CONSOLE"));
    EXPECT_EQ(OutputOption::DEST_CONSOLE, getDestination("CoNSoLE"));
    EXPECT_EQ(OutputOption::DEST_FILE, getDestination("file"));
    EXPECT_EQ(OutputOption::DEST_FILE, getDestination("FILE"));
    EXPECT_EQ(OutputOption::DEST_FILE, getDestination("fIlE"));
    EXPECT_EQ(OutputOption::DEST_SYSLOG, getDestination("syslog"));
    EXPECT_EQ(OutputOption::DEST_SYSLOG, getDestination("SYSLOG"));
    EXPECT_EQ(OutputOption::DEST_SYSLOG, getDestination("SYSlog"));

    // bad values should default to DEST_CONSOLE
    EXPECT_EQ(OutputOption::DEST_CONSOLE, getDestination("SOME_BAD_VALUE"));
}

TEST(OutputOption, getStream) {
    EXPECT_EQ(OutputOption::STR_STDOUT, getStream("stdout"));
    EXPECT_EQ(OutputOption::STR_STDOUT, getStream("STDOUT"));
    EXPECT_EQ(OutputOption::STR_STDOUT, getStream("STdouT"));
    EXPECT_EQ(OutputOption::STR_STDERR, getStream("stderr"));
    EXPECT_EQ(OutputOption::STR_STDERR, getStream("STDERR"));
    EXPECT_EQ(OutputOption::STR_STDERR, getStream("StDeRR"));

    // bad values should default to stdout
    EXPECT_EQ(OutputOption::STR_STDOUT, getStream("some bad value"));
    EXPECT_EQ(OutputOption::STR_STDOUT, getStream(""));
}

