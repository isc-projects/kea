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

