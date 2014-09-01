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
#include <dhcpsrv/logging_info.h>
#include <gtest/gtest.h>

using namespace isc::dhcp;

namespace {

// Checks if two destinations can be compared for equality.
TEST(LoggingDestintaion, equals) {
    LoggingDestination dest1;
    LoggingDestination dest2;

    EXPECT_TRUE(dest1.equals(dest2));

    dest1.output_ = "stderr";
    EXPECT_FALSE(dest1.equals(dest2));

    dest2.output_ = "stdout";
    EXPECT_FALSE(dest1.equals(dest2));

    dest2.output_ = "stderr";
    EXPECT_TRUE(dest1.equals(dest2));

    dest1.maxver_ = 10;
    dest2.maxver_ = 5;
    EXPECT_FALSE(dest1.equals(dest2));

    dest2.maxver_ = 10;
    EXPECT_TRUE(dest1.equals(dest2));

    dest1.maxsize_ = 64;
    dest2.maxsize_ = 32;
    EXPECT_FALSE(dest1.equals(dest2));

    dest1.maxsize_ = 32;
    EXPECT_TRUE(dest1.equals(dest2));
}

// Checks if (in)equality operators work for LoggingInfo.
TEST(LoggingInfo, equality) {
    LoggingInfo info1;
    LoggingInfo info2;

    // Initially, both objects are the same.
    EXPECT_TRUE(info1 == info2);

    // Differ by name.
    info1.name_ = "foo";
    info2.name_ = "bar";
    EXPECT_FALSE(info1 == info2);
    EXPECT_TRUE(info1 != info2);

    // Names equal.
    info2.name_ = "foo";
    EXPECT_TRUE(info1 == info2);
    EXPECT_FALSE(info1 != info2);

    // Differ by severity.
    info1.severity_ = isc::log::DEBUG;
    info2.severity_ = isc::log::INFO;
    EXPECT_FALSE(info1 == info2);
    EXPECT_TRUE(info1 != info2);

    // Severities equal.
    info2.severity_ = isc::log::DEBUG;
    EXPECT_TRUE(info1 == info2);
    EXPECT_FALSE(info1 != info2);

    // Differ by debug level.
    info1.debuglevel_ = 99;
    info2.debuglevel_ = 1;
    EXPECT_FALSE(info1 == info2);
    EXPECT_TRUE(info1 != info2);

    // Debug level equal.
    info2.debuglevel_ = 99;
    EXPECT_TRUE(info1 == info2);
    EXPECT_FALSE(info1 != info2);

    // Create two different desinations.
    LoggingDestination dest1;
    LoggingDestination dest2;
    dest1.output_ = "foo";
    dest2.output_ = "bar";

    // Push destinations in some order to info1.
    info1.destinations_.push_back(dest1);
    info1.destinations_.push_back(dest2);

    // Push in reverse order to info2. Order shouldn't matter.
    info2.destinations_.push_back(dest2);
    info2.destinations_.push_back(dest1);

    EXPECT_TRUE(info1 == info2);
    EXPECT_FALSE(info1 != info2);

    // Change one of the destinations.
    LoggingDestination dest3;
    dest3.output_ = "foobar";

    info2.destinations_[1] = dest3;

    // The should now be unequal.
    EXPECT_FALSE(info1 == info2);
    EXPECT_TRUE(info1 != info2);

}

} // end of anonymous namespace
