// Copyright (C) 2018-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <gtest/gtest.h>

#include <yang/tests/sysrepo_setup.h>
#include <yang/translator_pool.h>
#include <yang/yang_models.h>

#include <sstream>

using namespace std;
using namespace isc;
using namespace isc::data;
using namespace isc::yang;
using namespace isc::yang::test;
using namespace sysrepo;

namespace {

/// @brief Translator name.
extern char const pool_list[] = "pool list";

/// @brief Test fixture class for @ref TranslatorPools.
class TranslatorPoolsTestKeaV4 :
    public GenericTranslatorTest<pool_list, TranslatorPools> {
public:
    /// @brief Constructor
    TranslatorPoolsTestKeaV4() {
        model_ = KEA_DHCP4_SERVER;
    }
};  // TranslatorPoolsTestKeaV4
class TranslatorPoolsTestKeaV6 :
    public GenericTranslatorTest<pool_list, TranslatorPools> {
public:
    /// @brief Constructor
    TranslatorPoolsTestKeaV6() {
        model_ = KEA_DHCP6_SERVER;
    }
};  // TranslatorPoolsTestKeaV6
class TranslatorPoolsTestIetfV6 :
    public GenericTranslatorTest<pool_list, TranslatorPools> {
public:
    /// @brief Constructor
    TranslatorPoolsTestIetfV6() {
        model_ = IETF_DHCPV6_SERVER;
    }
};  // TranslatorPoolsTestIetfV6

// This test verifies that an empty pool list can be properly
// translated from YANG to JSON using IETF model.
TEST_F(TranslatorPoolsTestIetfV6, getEmptyIetf) {
    // Get the pool list and check if it is empty.
    const string& xpath = "/ietf-dhcpv6-server:server/server-config/"
        "network-ranges/network-range[network-range-id='111']/address-pools";
    ConstElementPtr pools;
    EXPECT_NO_THROW_LOG(pools = translator_->getPoolsFromAbsoluteXpath(xpath));
    ASSERT_FALSE(pools);
}

// This test verifies that an empty pool list can be properly
// translated from YANG to JSON using Kea ad hoc model.
TEST_F(TranslatorPoolsTestKeaV6, getEmptyKea) {
    // Get the pool list and check if it is empty.
    const string& xpath = "/kea-dhcp6-server:config/subnet6[id='111']";
    ConstElementPtr pools;
    EXPECT_NO_THROW_LOG(pools = translator_->getPoolsFromAbsoluteXpath(xpath));
    ASSERT_FALSE(pools);
}

// This test verifies that one pool can be properly
// translated from YANG to JSON using IETF model.
TEST_F(TranslatorPoolsTestIetfV6, getIetf) {
    // Create the subnet 2001:db8::/48 #111.
    const string& subnet = "/ietf-dhcpv6-server:server/server-config/"
        "network-ranges/network-range[network-range-id='111']";
    string const subnet_value("2001:db8::/48");
    string const& network_prefix_path = subnet + "/network-prefix";
    EXPECT_NO_THROW_LOG(sess_->setItem(network_prefix_path, subnet_value));
    sess_->applyChanges();

    // Create the pool 2001:db8::1:0/112 #222.
    const string& xpath = subnet + "/address-pools";
    const string& prefix = xpath + "/address-pool[pool-id='222']/pool-prefix";
    string const value("2001:db8::1:0/112");
    EXPECT_NO_THROW_LOG(sess_->setItem(prefix, value));
    sess_->applyChanges();

    // Get the pool.
    ConstElementPtr pool;
    EXPECT_NO_THROW_LOG(pool = translator_->getPoolFromAbsoluteXpath(xpath + "/address-pool[pool-id='222']"));
    ASSERT_TRUE(pool);
    EXPECT_EQ("{ \"pool\": \"2001:db8::1:0/112\" }", pool->str());

    // Get the pool list and check if the pool is in it.
    ConstElementPtr pools;
    EXPECT_NO_THROW_LOG(pools = translator_->getPoolsFromAbsoluteXpath(xpath));
    ASSERT_TRUE(pools);
    ASSERT_EQ(Element::list, pools->getType());
    ASSERT_EQ(1, pools->size());
    EXPECT_TRUE(pool->equals(*pools->get(0)));
}

// This test verifies that one pool can be properly
// translated from YANG to JSON using Kea ad hoc model.
TEST_F(TranslatorPoolsTestKeaV6, getKea) {
    // Create the subnet 2001:db8::/48 #111.
    const string& xpath =
        "/kea-dhcp6-server:config/subnet6[id='111']";
    string const v_subnet("2001:db8::/48");
    const string& subnet = xpath + "/subnet";
    EXPECT_NO_THROW_LOG(sess_->setItem(subnet, v_subnet));
    sess_->applyChanges();

    // Create the pool 2001:db8::1:0/112.
    const string& prefix = "2001:db8::1:0/112";
    string start_addr;
    string end_addr;
    ASSERT_NO_THROW_LOG(TranslatorPool::getAddresses(prefix,
                                                 start_addr, end_addr));
    EXPECT_EQ("2001:db8::1:0", start_addr);
    EXPECT_EQ("2001:db8::1:ffff", end_addr);
    ostringstream spool;
    spool << xpath + "/pool[start-address='" << start_addr
          << "'][end-address='" << end_addr << "']";
    const string& x_prefix = spool.str() + "/prefix";
    string const s_prefix("2001:db8::1:0/112");
    EXPECT_NO_THROW_LOG(sess_->setItem(x_prefix, s_prefix));
    sess_->applyChanges();

    // Get the pool.
    ConstElementPtr pool;
    EXPECT_NO_THROW_LOG(pool = translator_->getPoolFromAbsoluteXpath(spool.str()));
    ASSERT_TRUE(pool);
    ElementPtr expected = Element::createMap();
    expected->set("pool", Element::create("2001:db8::1:0/112"));
    EXPECT_TRUE(expected->equals(*pool));

    // Get the pool list and check if the pool is in it.
    ConstElementPtr pools;
    EXPECT_NO_THROW_LOG(pools = translator_->getPoolsFromAbsoluteXpath(xpath));
    ASSERT_TRUE(pools);
    ASSERT_EQ(Element::list, pools->getType());
    ASSERT_EQ(1, pools->size());
    EXPECT_TRUE(pool->equals(*pools->get(0)));
}

// This test verifies that an empty pool list can be properly
// translated from JSON to YANG using IETF model.
TEST_F(TranslatorPoolsTestIetfV6, setEmptyIetf) {
    // Create the subnet 2001:db8::/48 #111.
    const string& subnet = "/ietf-dhcpv6-server:server/server-config/"
        "network-ranges/network-range[network-range-id='111']";
    string const v_subnet("2001:db8::/48");
    const string& subnet_subnet = subnet + "/network-prefix";
    EXPECT_NO_THROW_LOG(sess_->setItem(subnet_subnet, v_subnet));
    sess_->applyChanges();

    // Set empty list.
    const string& xpath = subnet + "/address-pools";
    ConstElementPtr pools = Element::createList();
    EXPECT_NO_THROW_LOG(translator_->setPools(xpath, pools));

    // Get it back.
    pools.reset();
    EXPECT_NO_THROW_LOG(pools = translator_->getPoolsFromAbsoluteXpath(xpath));
    ASSERT_FALSE(pools);
}

// This test verifies that an empty pool list can be properly
// translated from JSON to YANG using Kea ad hoc model.
TEST_F(TranslatorPoolsTestKeaV6, setEmptyKea) {
    // Create the subnet 2001:db8::/48 #111.
    const string& xpath =
        "/kea-dhcp6-server:config/subnet6[id='111']";
    string const v_subnet("2001:db8::/48");
    const string& subnet = xpath + "/subnet";
    EXPECT_NO_THROW_LOG(sess_->setItem(subnet, v_subnet));
    sess_->applyChanges();

    // Set empty list.
    ConstElementPtr pools = Element::createList();
    EXPECT_NO_THROW_LOG(translator_->setPools(xpath, pools));

    // Get it back.
    pools.reset();
    EXPECT_NO_THROW_LOG(pools = translator_->getPoolsFromAbsoluteXpath(xpath));
    ASSERT_FALSE(pools);
}

// This test verifies that one pool can be properly
// translated from JSON to YANG using IETF model.
TEST_F(TranslatorPoolsTestIetfV6, setIetf) {
    // Create the subnet 2001:db8::/48 #111.
    const string& subnet = "/ietf-dhcpv6-server:server/server-config/"
        "network-ranges/network-range[network-range-id='111']";
    string const v_subnet("2001:db8::/48");
    const string& subnet_subnet = subnet + "/network-prefix";
    EXPECT_NO_THROW_LOG(sess_->setItem(subnet_subnet, v_subnet));
    sess_->applyChanges();

    // Set one pool.
    const string& xpath = subnet + "/address-pools";
    ElementPtr pools = Element::createList();
    ElementPtr pool = Element::createMap();
    pool->set("pool", Element::create("2001:db8::1:0/112"));
    pools->add(pool);
    EXPECT_NO_THROW_LOG(translator_->setPools(xpath, pools));

    // Get it back.
    pools.reset();
    EXPECT_NO_THROW_LOG(pools = translator_->getPoolsFromAbsoluteXpath(xpath));
    ASSERT_TRUE(pools);
    ASSERT_EQ(Element::list, pools->getType());
    ASSERT_EQ(1, pools->size());
    EXPECT_TRUE(pool->equals(*pools->get(0)));
}

// This test verifies that one pool can be properly
// translated from JSON to YANG using Kea ad hoc model.
TEST_F(TranslatorPoolsTestKeaV6, setKea) {
    // Create the subnet 2001:db8::/48 #111.
    const string& xpath =
        "/kea-dhcp6-server:config/subnet6[id='111']";
    string const v_subnet("2001:db8::/48");
    const string& subnet = xpath + "/subnet";
    EXPECT_NO_THROW_LOG(sess_->setItem(subnet, v_subnet));
    sess_->applyChanges();

    // Set one pool.
    ElementPtr pools = Element::createList();
    ElementPtr pool = Element::createMap();
    pool->set("pool",
              Element::create("2001:db8::1 - 2001:db8::100"));
    pools->add(pool);
    EXPECT_NO_THROW_LOG(translator_->setPools(xpath, pools));

    // Get it back.
    pools.reset();
    EXPECT_NO_THROW_LOG(pools = translator_->getPoolsFromAbsoluteXpath(xpath));
    ASSERT_TRUE(pools);
    ASSERT_EQ(Element::list, pools->getType());
    ASSERT_EQ(1, pools->size());
    EXPECT_TRUE(pool->equals(*pools->get(0)));
}

}  // namespace
