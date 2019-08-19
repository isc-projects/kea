// Copyright (C) 2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <cc/server_tag.h>
#include <exceptions/exceptions.h>
#include <boost/scoped_ptr.hpp>
#include <gtest/gtest.h>
#include <string>

using namespace isc;
using namespace isc::data;

namespace {

// This test verifies that the constructors of the ServerTag class
// work properly.
TEST(ServerTagTest, constructors) {
    boost::scoped_ptr<ServerTag> tag;

    {
        SCOPED_TRACE("default constructor for all servers");
        ASSERT_NO_THROW(tag.reset(new ServerTag()));
        EXPECT_EQ(ServerTag::ALL, tag->get());
        EXPECT_TRUE(tag->amAll());
    }

    {
        SCOPED_TRACE("all servers");
        ASSERT_NO_THROW(tag.reset(new ServerTag(ServerTag::ALL)));
        EXPECT_EQ(ServerTag::ALL, tag->get());
        EXPECT_TRUE(tag->amAll());
    }

    {
        SCOPED_TRACE("no whitespace");
        ASSERT_NO_THROW(tag.reset(new ServerTag("xyz")));
        EXPECT_EQ("xyz", tag->get());
        EXPECT_FALSE(tag->amAll());
    }

    {
        SCOPED_TRACE("leading whitespace");
        ASSERT_NO_THROW(tag.reset(new ServerTag("  left")));
        EXPECT_EQ("left", tag->get());
        EXPECT_FALSE(tag->amAll());
    }

    {
        SCOPED_TRACE("terminating whitespace");
        ASSERT_NO_THROW(tag.reset(new ServerTag("right  ")));
        EXPECT_EQ("right", tag->get());
        EXPECT_FALSE(tag->amAll());
    }

    {
        SCOPED_TRACE("leading and terminating whitespace");
        ASSERT_NO_THROW(tag.reset(new ServerTag("  both left-right  ")));
        EXPECT_EQ("both left-right", tag->get());
        EXPECT_FALSE(tag->amAll());
    }

    {
        SCOPED_TRACE("upper to lower case");
        ASSERT_NO_THROW(tag.reset(new ServerTag("UPPER CASE TAG")));
        EXPECT_EQ("upper case tag", tag->get());
        EXPECT_FALSE(tag->amAll());
    }
}

// This test verifies that malformed server tags are rejected.
TEST(ServerTagTest, malformed) {
    {
        SCOPED_TRACE("empty tag");
        EXPECT_THROW(ServerTag(""), BadValue);
    }

    {
        SCOPED_TRACE("only whitespaces");
        EXPECT_THROW(ServerTag("   "), BadValue);
    }

    {
        SCOPED_TRACE("too long tag, max is 256");
        EXPECT_THROW(ServerTag(std::string(257, 'c')), BadValue);
    }

    {
        SCOPED_TRACE("use reserved keyword any as a tag");
        EXPECT_THROW(ServerTag("any"), BadValue);
    }
}

}
