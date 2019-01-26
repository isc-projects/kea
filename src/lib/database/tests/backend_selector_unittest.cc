// Copyright (C) 2018-2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.


#include <config.h>
#include <database/backend_selector.h>
#include <testutils/test_to_element.h>
#include <boost/scoped_ptr.hpp>
#include <gtest/gtest.h>

using namespace isc;
using namespace isc::db;
using namespace isc::data;

namespace {

// Verifies defaults of the backend selector.
TEST(BackendSelectorTest, defaults) {
    BackendSelector sel;
    EXPECT_EQ(BackendSelector::Type::UNSPEC, sel.getBackendType());
    EXPECT_TRUE(sel.getBackendHost().empty());
    EXPECT_EQ(0, sel.getBackendPort());
    EXPECT_TRUE(sel.amUnspecified());
    EXPECT_EQ("unspecified", sel.toText());
}

// Verifies that the backend selector can be set to "unspecified".
TEST(BackendSelectorTest, unspec) {
    BackendSelector sel = BackendSelector::UNSPEC();
    EXPECT_EQ(BackendSelector::Type::UNSPEC, sel.getBackendType());
    EXPECT_TRUE(sel.getBackendHost().empty());
    EXPECT_EQ(0, sel.getBackendPort());
    EXPECT_TRUE(sel.amUnspecified());
    EXPECT_EQ("unspecified", sel.toText());
}

// Verifies that it is possible to select backend by type.
TEST(BackendSelectorTest, backendTypeSpec) {
    boost::scoped_ptr<BackendSelector> sel;
    ASSERT_NO_THROW(
        sel.reset(new BackendSelector(BackendSelector::Type::MYSQL))
    );
    EXPECT_EQ(BackendSelector::Type::MYSQL, sel->getBackendType());
    EXPECT_TRUE(sel->getBackendHost().empty());
    EXPECT_EQ(0, sel->getBackendPort());
    EXPECT_FALSE(sel->amUnspecified());
    EXPECT_EQ("type=mysql", sel->toText());
}

// Verifies that backend can be selected by host and port.
TEST(BackendSelectorTest, backendHostPortSpec) {
    boost::scoped_ptr<BackendSelector> sel;
    ASSERT_NO_THROW(
        sel.reset(new BackendSelector("myhost", 1234))
    );
    EXPECT_EQ(BackendSelector::Type::UNSPEC, sel->getBackendType());
    EXPECT_EQ("myhost", sel->getBackendHost());
    EXPECT_EQ(1234, sel->getBackendPort());
    EXPECT_FALSE(sel->amUnspecified());
    EXPECT_EQ("host=myhost,port=1234", sel->toText());
}

// Verifies that backend can be selected by host.
TEST(BackendSelectorTest, backendHostSpec) {
    boost::scoped_ptr<BackendSelector> sel;
    ASSERT_NO_THROW(
        sel.reset(new BackendSelector("otherhost"))
    );
    EXPECT_EQ(BackendSelector::Type::UNSPEC, sel->getBackendType());
    EXPECT_EQ("otherhost", sel->getBackendHost());
    EXPECT_EQ(0, sel->getBackendPort());
    EXPECT_FALSE(sel->amUnspecified());
    EXPECT_EQ("host=otherhost", sel->toText());
}

// Verifies that backend becomes unspecified if the access
// map is empty.
TEST(BackendSelectorTest, accessMapTypeUnSpec) {
    ElementPtr access_map = Element::createMap();
    boost::scoped_ptr<BackendSelector> sel;
    ASSERT_NO_THROW(
        sel.reset(new BackendSelector(access_map))
    );
    EXPECT_EQ(BackendSelector::Type::UNSPEC, sel->getBackendType());
    EXPECT_TRUE(sel->getBackendHost().empty());
    EXPECT_EQ(0, sel->getBackendPort());
    EXPECT_TRUE(sel->amUnspecified());
    EXPECT_EQ("unspecified", sel->toText());
}

// Verifies that backend can be selected by type using access map.
TEST(BackendSelectorTest, accessMapTypeSpec) {
    ElementPtr access_map = Element::createMap();
    access_map->set("type", Element::create("mysql"));
    boost::scoped_ptr<BackendSelector> sel;
    ASSERT_NO_THROW(
        sel.reset(new BackendSelector(access_map))
    );
    EXPECT_EQ(BackendSelector::Type::MYSQL, sel->getBackendType());
    EXPECT_TRUE(sel->getBackendHost().empty());
    EXPECT_EQ(0, sel->getBackendPort());
    EXPECT_FALSE(sel->amUnspecified());
    EXPECT_EQ("type=mysql", sel->toText());
}

// Verifies that backend can be selected by host and port using
// access map.
TEST(BackendSelectorTest, accessMapHostPortSpec) {
    ElementPtr access_map = Element::createMap();
    access_map->set("host", Element::create("myhost"));
    access_map->set("port", Element::create(int64_t(1234)));
    boost::scoped_ptr<BackendSelector> sel;
    ASSERT_NO_THROW(
        sel.reset(new BackendSelector(access_map))
    );
    EXPECT_EQ(BackendSelector::Type::UNSPEC, sel->getBackendType());
    EXPECT_EQ("myhost", sel->getBackendHost());
    EXPECT_EQ(1234, sel->getBackendPort());
    EXPECT_FALSE(sel->amUnspecified());
    EXPECT_EQ("host=myhost,port=1234", sel->toText());
}

// Verifies that the backend can be selected by host using access
// map.
TEST(BackendSelectorTest, accessMapHostSpec) {
    ElementPtr access_map = Element::createMap();
    access_map->set("host", Element::create("myhost"));
    boost::scoped_ptr<BackendSelector> sel;
    ASSERT_NO_THROW(
        sel.reset(new BackendSelector(access_map))
    );
    EXPECT_EQ(BackendSelector::Type::UNSPEC, sel->getBackendType());
    EXPECT_EQ("myhost", sel->getBackendHost());
    EXPECT_EQ(0, sel->getBackendPort());
    EXPECT_FALSE(sel->amUnspecified());
    EXPECT_EQ("host=myhost", sel->toText());
}

// Verifies that selecting backend by port only is not possible.
TEST(BackendSelectorTest, accessMapPortSpec) {
    ElementPtr access_map = Element::createMap();
    access_map->set("port", Element::create(int64_t(1234)));
    boost::scoped_ptr<BackendSelector> sel;
    EXPECT_THROW(sel.reset(new BackendSelector(access_map)),
                 BadValue);
}

// Tests conversions of strings to backend types.
TEST(BackendSelectorTest, stringToBackendType) {
    EXPECT_EQ(BackendSelector::Type::MYSQL,
              BackendSelector::stringToBackendType("mysql"));
    EXPECT_EQ(BackendSelector::Type::PGSQL,
              BackendSelector::stringToBackendType("pgsql"));
    EXPECT_EQ(BackendSelector::Type::CQL,
              BackendSelector::stringToBackendType("cql"));
    EXPECT_THROW(BackendSelector::stringToBackendType("unsupported"),
                 BadValue);
}

// Tests conversions of backend types to strings.
TEST(BackendSelectorTest, backendTypeToString) {
    EXPECT_EQ("mysql",
              BackendSelector::backendTypeToString(BackendSelector::Type::MYSQL));
    EXPECT_EQ("pgsql",
              BackendSelector::backendTypeToString(BackendSelector::Type::PGSQL));
    EXPECT_EQ("cql",
              BackendSelector::backendTypeToString(BackendSelector::Type::CQL));
}

// Tests toElement from backend selectors.
TEST(BackendSelectorTest, backendToElement) {
    // Unspecified.
    boost::scoped_ptr<BackendSelector> sel(new BackendSelector());
    EXPECT_THROW(sel->toElement(), BadValue);

    // Unspecified type.
    sel.reset(new BackendSelector("myhost", 1234));
    EXPECT_THROW(sel->toElement(), BadValue);

    // Type only.
    EXPECT_NO_THROW(sel.reset(new BackendSelector(BackendSelector::Type::MYSQL)));
    ElementPtr expected = Element::createMap();
    expected->set("type", Element::create("mysql"));
    test::runToElementTest<BackendSelector>(expected, *sel);

    // Add host.
    expected->set("host", Element::create("myhost"));
    EXPECT_NO_THROW(sel.reset(new BackendSelector(expected)));
    test::runToElementTest<BackendSelector>(expected, *sel);

    // Add port.
    expected->set("port", Element::create(1234L));
    EXPECT_NO_THROW(sel.reset(new BackendSelector(expected)));
    test::runToElementTest<BackendSelector>(expected, *sel);
}

}

