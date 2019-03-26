// Copyright (C) 2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <dhcpsrv/network.h>
#include <boost/shared_ptr.hpp>
#include <functional>
#include <gtest/gtest.h>

using namespace isc::data;
using namespace isc::dhcp;

namespace {

class TestNetwork;
typedef boost::shared_ptr<TestNetwork> TestNetworkPtr;

class TestNetwork : public Network {
public:

    void setParent(TestNetworkPtr parent) {
        parent_network_ = boost::dynamic_pointer_cast<Network>(parent);
    }

};

class NetworkTest : public ::testing::Test {
public:

    NetworkTest()
        : globals_(Element::createMap()) {
    }

    FetchNetworkGlobalsFn getFetchGlobalsFn() {
        return (std::bind(&NetworkTest::fetchGlobalsFn, this));
    }

    ConstElementPtr fetchGlobalsFn() {
        return (globals_);
    }

    template<typename>
    void testNetworkInheritance() {
    }

    ElementPtr globals_;
};

TEST_F(NetworkTest, getPropertyNoParentNoChild) {
    NetworkPtr net_child(new Network());
    EXPECT_TRUE(net_child->getIface().unspecified());
}

TEST_F(NetworkTest, getPropertyNoParentChild) {
    NetworkPtr net_child(new Network());
    net_child->setIface("child_iface");
    EXPECT_EQ("child_iface", net_child->getIface().get());
}

TEST_F(NetworkTest, getPropertyParentNoChild) {
    TestNetworkPtr net_child(new TestNetwork());
    EXPECT_TRUE(net_child->getIface().unspecified());

    TestNetworkPtr net_parent(new TestNetwork());
    net_parent->setIface("parent_iface");
    EXPECT_EQ("parent_iface", net_parent->getIface().get());

    ASSERT_NO_THROW(net_child->setParent(net_parent));

    EXPECT_FALSE(net_child->getIface().unspecified());
    EXPECT_EQ("parent_iface", net_child->getIface().get());
}

TEST_F(NetworkTest, getPropertyParentChild) {
    TestNetworkPtr net_child(new TestNetwork());
    net_child->setIface("child_iface");
    EXPECT_EQ("child_iface", net_child->getIface().get());

    TestNetworkPtr net_parent(new TestNetwork());
    net_parent->setIface("parent_iface");
    EXPECT_EQ("parent_iface", net_parent->getIface().get());

    ASSERT_NO_THROW(net_child->setParent(net_parent));

    EXPECT_FALSE(net_child->getIface().unspecified());
    EXPECT_EQ("child_iface", net_child->getIface().get());
}

TEST_F(NetworkTest, getPropertyGlobalNoParentNoChild) {
    TestNetworkPtr net_child(new TestNetwork());

    globals_->set("interface", Element::create("global_iface"));

    net_child->setFetchGlobalsFn(getFetchGlobalsFn());

    EXPECT_FALSE(net_child->getIface().unspecified());
}

}
