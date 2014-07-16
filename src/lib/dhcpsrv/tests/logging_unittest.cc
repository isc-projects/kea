// Copyright (C) 2014 Internet Systems Consortium, Inc. ("ISC")
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

#include <config.h>
#include <exceptions/exceptions.h>
#include <cc/data.h>
#include <dhcpsrv/logging.h>
#include <gtest/gtest.h>

using namespace isc;
using namespace isc::dhcp;
using namespace isc::data;

namespace {

// Checks that contructor is able to process specified storage properly
TEST(LoggingTest, constructor) {

    ConfigurationPtr nullPtr;
    EXPECT_THROW(LogConfigParser parser(nullPtr), InvalidOperation);

    ConfigurationPtr nonnull(new Configuration());

    EXPECT_NO_THROW(LogConfigParser parser(nonnull));
}

// Checks if the LogConfigParser class is able to transform JSON structures
// into Configuration usable by log4cplus. This test checks for output
// configured to stdout on debug level.
TEST(LoggingTest, parsingConsoleOutput) {

    const char* config_txt = 
    "{ \"loggers\": ["
    "    {"
    "        \"name\": \"kea\","
    "        \"output_options\": ["
    "            {"
    "                \"output\": \"stdout\""
    "            }"
    "        ],"
    "        \"debuglevel\": 99,"
    "        \"severity\": \"DEBUG\""
    "    }"
    "]}";

    ConfigurationPtr storage(new Configuration());

    LogConfigParser parser(storage);

    // We need to parse properly formed JSON and then extract
    // "loggers" element from it. For some reason fromJSON is
    // throwing at opening square bracket 
    ConstElementPtr config = Element::fromJSON(config_txt);
    config = config->get("loggers");

    EXPECT_NO_THROW(parser.parseConfiguration(config));

    ASSERT_EQ(1, storage->logging_info_.size());

    EXPECT_EQ("kea", storage->logging_info_[0].name_);
    EXPECT_EQ(99, storage->logging_info_[0].debuglevel_);
    EXPECT_EQ(isc::log::DEBUG, storage->logging_info_[0].severity_);

    ASSERT_EQ(1, storage->logging_info_[0].destinations_.size());
    EXPECT_EQ("stdout" , storage->logging_info_[0].destinations_[0].output_);
}

// Checks if the LogConfigParser class is able to transform JSON structures
// into Configuration usable by log4cplus. This test checks for output
// configured to a file on INFO level.
TEST(LoggingTest, parsingFile) {

    const char* config_txt = 
    "{ \"loggers\": ["
    "    {"
    "        \"name\": \"kea\","
    "        \"output_options\": ["
    "            {"
    "                \"output\": \"logfile.txt\""
    "            }"
    "        ],"
    "        \"severity\": \"INFO\""
    "    }"
    "]}";

    ConfigurationPtr storage(new Configuration());

    LogConfigParser parser(storage);

    // We need to parse properly formed JSON and then extract
    // "loggers" element from it. For some reason fromJSON is
    // throwing at opening square bracket 
    ConstElementPtr config = Element::fromJSON(config_txt);
    config = config->get("loggers");

    EXPECT_NO_THROW(parser.parseConfiguration(config));

    ASSERT_EQ(1, storage->logging_info_.size());

    EXPECT_EQ("kea", storage->logging_info_[0].name_);
    EXPECT_EQ(0, storage->logging_info_[0].debuglevel_);
    EXPECT_EQ(isc::log::INFO, storage->logging_info_[0].severity_);

    ASSERT_EQ(1, storage->logging_info_[0].destinations_.size());
    EXPECT_EQ("logfile.txt" , storage->logging_info_[0].destinations_[0].output_);
}

// There is no easy way to test applyConfiguration() and defaultLogging().
// To test them, it would require instrumenting log4cplus to actually fake
// the logging set up. Alternatively, we could develop set of test suites
// that check each logging destination spearately (e.g. configure log file, then
// check if the file is indeed created or configure stdout destination, then
// swap console file descriptors and check that messages are really logged.

};
