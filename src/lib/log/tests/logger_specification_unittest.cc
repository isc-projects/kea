// Copyright (C) 2011  Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <string>

#include <gtest/gtest.h>

#include <log/logger_specification.h>
#include <log/output_option.h>

using namespace isc::log;
using namespace std;

// Check default initialization.
TEST(LoggerSpecificationTest, DefaultInitialization) {
    LoggerSpecification spec;

    EXPECT_EQ(string(""), spec.getName());
    EXPECT_EQ(isc::log::INFO, spec.getSeverity());
    EXPECT_EQ(0, spec.getDbglevel());
    EXPECT_FALSE(spec.getAdditive());
    EXPECT_EQ(0, spec.optionCount());
}

// Non-default initialization
TEST(LoggerSpecificationTest, Initialization) {
    LoggerSpecification spec("alpha", isc::log::ERROR, 42, true);

    EXPECT_EQ(string("alpha"), spec.getName());
    EXPECT_EQ(isc::log::ERROR, spec.getSeverity());
    EXPECT_EQ(42, spec.getDbglevel());
    EXPECT_TRUE(spec.getAdditive());
    EXPECT_EQ(0, spec.optionCount());
}

// Get/Set tests
TEST(LoggerSpecificationTest, SetGet) {
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
TEST(LoggerSpecificationTest, AddOption) {
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
