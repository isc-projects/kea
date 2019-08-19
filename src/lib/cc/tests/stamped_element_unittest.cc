// Copyright (C) 2018-2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <cc/stamped_element.h>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <gtest/gtest.h>

using namespace isc::data;

namespace {

// Tests that the modification timestamp is by default set to current
// time and the identifier is set to 0.
TEST(StampedElementTest, create) {
    StampedElement element;

    // Default identifier is 0.
    EXPECT_EQ(0, element.getId());

    // By default there is no server tag.
    EXPECT_TRUE(element.getServerTags().empty());

    // Checking that the delta between now and the timestamp is within
    // 5s range should be sufficient.
    boost::posix_time::time_duration delta =
        boost::posix_time::second_clock::local_time() -
        element.getModificationTime();
    EXPECT_LT(delta.seconds(), 5);
}

// Tests that default id can be overridden by a new value.
TEST(StampedElementTest, setId) {
    StampedElement element;
    element.setId(123);
    EXPECT_EQ(123, element.getId());
}

// Tests that the modification timestamp can be set to an arbitrary
// value.
TEST(StampedElementTest, setModificationTime) {
    boost::posix_time::ptime
        modification_time(boost::gregorian::date(2002, boost::date_time::Jan, 10),
                          boost::posix_time::time_duration(1,2,3));
    StampedElement element;
    element.setModificationTime(modification_time);
    EXPECT_TRUE(element.getModificationTime() == modification_time);
}

// Tests that updating modification timestamp sets it to the current
// time.
TEST(StampedElementTest, update) {
    boost::posix_time::ptime
        modification_time(boost::gregorian::date(2002, boost::date_time::Jan, 10),
                          boost::posix_time::time_duration(1,2,3));
    StampedElement element;
    element.setModificationTime(modification_time);
    element.updateModificationTime();

    // Checking that the delta between now and the timestamp is within
    // 5s range should be sufficient.
    boost::posix_time::time_duration delta =
        boost::posix_time::second_clock::local_time() -
        element.getModificationTime();
    EXPECT_LT(delta.seconds(), 5);
}

// Tests that one or more server tag can be specified.
TEST(StampedElementTest, setServerTag) {
    StampedElement element;
    element.setServerTag("foo");
    EXPECT_EQ(1, element.getServerTags().size());
    EXPECT_EQ("foo", element.getServerTags().begin()->get());

    element.setServerTag("bar");
    EXPECT_EQ(2, element.getServerTags().size());

    EXPECT_TRUE(element.hasServerTag(ServerTag("foo")));
    EXPECT_TRUE(element.hasServerTag(ServerTag("bar")));
    EXPECT_FALSE(element.hasServerTag(ServerTag("xyz")));
    EXPECT_FALSE(element.hasAllServerTag());

    element.setServerTag(ServerTag::ALL);
    EXPECT_TRUE(element.hasAllServerTag());
}

// Tests that a server tag can be deleted.
TEST(StampedElementTest, delServerTag) {
    StampedElement element;
    EXPECT_THROW(element.delServerTag("foo"), isc::NotFound);
    element.setServerTag("foo");
    element.setServerTag("bar");

    ASSERT_EQ(2, element.getServerTags().size());
    EXPECT_TRUE(element.hasServerTag(ServerTag("foo")));
    EXPECT_TRUE(element.hasServerTag(ServerTag("bar")));

    EXPECT_NO_THROW(element.delServerTag("foo"));
    ASSERT_EQ(1, element.getServerTags().size());
    EXPECT_TRUE(element.hasServerTag(ServerTag("bar")));

    EXPECT_NO_THROW(element.delServerTag("bar"));
    EXPECT_EQ(0, element.getServerTags().size());
    EXPECT_THROW(element.delServerTag("bar"), isc::NotFound);
}


// Test that metadata can be created from the StampedElement.
TEST(StampedElementTest, getMetadata) {
    StampedElement element;
    element.setServerTag("world");
    auto metadata = element.getMetadata();
    ASSERT_TRUE(metadata);
    ASSERT_EQ(Element::map, metadata->getType());

    auto server_tags_element = metadata->get("server-tags");
    ASSERT_TRUE(server_tags_element);
    EXPECT_EQ(Element::list, server_tags_element->getType());
    EXPECT_EQ(1, server_tags_element->size());

    auto server_tag_element = server_tags_element->get(0);
    ASSERT_TRUE(server_tag_element);
    EXPECT_EQ(Element::string, server_tag_element->getType());
    EXPECT_EQ("world", server_tag_element->stringValue());
}

}
