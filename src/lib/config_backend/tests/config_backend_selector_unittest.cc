// Copyright (C) 2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.


#include <config.h>
#include <config_backend/base_config_backend_pool.h>
#include <boost/scoped_ptr.hpp>
#include <gtest/gtest.h>

using namespace isc;
using namespace isc::cb;
using namespace isc::data;

namespace {

TEST(BackendSelectorTest, defaults) {
    BackendSelector sel;
    EXPECT_EQ(BackendSelector::Type::UNSPEC, sel.getBackendType());
    EXPECT_TRUE(sel.getBackendHost().empty());
    EXPECT_EQ(0, sel.getBackendPort());
    EXPECT_TRUE(sel.amUnspecified());
    EXPECT_EQ("unspecified", sel.toText());
}

TEST(BackendSelectorTest, unspec) {
    BackendSelector sel = BackendSelector::UNSPEC();
    EXPECT_EQ(BackendSelector::Type::UNSPEC, sel.getBackendType());
    EXPECT_TRUE(sel.getBackendHost().empty());
    EXPECT_EQ(0, sel.getBackendPort());
    EXPECT_TRUE(sel.amUnspecified());
    EXPECT_EQ("unspecified", sel.toText());
}

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

TEST(BackendSelectorTest, accessMapPortSpec) {
    ElementPtr access_map = Element::createMap();
    access_map->set("port", Element::create(int64_t(1234)));
    boost::scoped_ptr<BackendSelector> sel;
    EXPECT_THROW(sel.reset(new BackendSelector(access_map)),
                 BadValue);
}

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

TEST(BackendSelectorTest, backendTypeToString) {
    EXPECT_EQ("mysql",
              BackendSelector::backendTypeToString(BackendSelector::Type::MYSQL));
    EXPECT_EQ("pgsql",
              BackendSelector::backendTypeToString(BackendSelector::Type::PGSQL));
    EXPECT_EQ("cql",
              BackendSelector::backendTypeToString(BackendSelector::Type::CQL));
}


}

