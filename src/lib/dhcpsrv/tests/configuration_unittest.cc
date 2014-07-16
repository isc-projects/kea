// Copyright (C) 2012-2014 Internet Systems Consortium, Inc. ("ISC")
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

#include <dhcpsrv/configuration.h>
#include <gtest/gtest.h>

using namespace isc::dhcp;

// Those are the tests for Configuration storage. Right now they are minimal,
// but the number is expected to grow significantly once we migrate more
// parameters from CfgMgr storage to Configuration storage.

namespace {

// Check that by default there are no logging entries
TEST(ConfigurationTest, basic) {
    Configuration x;

    EXPECT_TRUE(x.logging_info_.empty());
}

// Check that Configuration can store logging information.
TEST(ConfigurationTest, loggingInfo) {

    Configuration x;

    LoggingInfo log1;
    log1.name_ = "foo";
    log1.severity_ = isc::log::WARN;
    log1.debuglevel_ = 77;

    LoggingDestination dest;
    dest.output_ = "some-logfile.txt";
    dest.maxver_ = 5;
    dest.maxsize_ = 2097152;

    log1.destinations_.push_back(dest);

    x.logging_info_.push_back(log1);

    EXPECT_EQ("foo", x.logging_info_[0].name_);
    EXPECT_EQ(isc::log::WARN, x.logging_info_[0].severity_);
    EXPECT_EQ(77, x.logging_info_[0].debuglevel_);

    EXPECT_EQ("some-logfile.txt", x.logging_info_[0].destinations_[0].output_);
    EXPECT_EQ(5, x.logging_info_[0].destinations_[0].maxver_);
    EXPECT_EQ(2097152, x.logging_info_[0].destinations_[0].maxsize_);
}

} // end of anonymous namespace
