// Copyright (C) 2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <yang/translator_pool.h>
#include <yang/yang_models.h>
#include <yang/tests/sysrepo_setup.h>

#include <gtest/gtest.h>
#include <sstream>

using namespace std;
using namespace isc;
using namespace isc::data;
using namespace isc::yang;
using namespace isc::yang::test;
#ifndef HAVE_PRE_0_7_6_SYSREPO
using namespace sysrepo;
#endif

namespace {

/// @brief Translator name.
extern char const pool_list[] = "pool list";

/// @brief Test fixture class for @ref TranslatorPools.
class TranslatorPoolsTest :
    public GenericTranslatorTest<pool_list, TranslatorPools> {
public:

    /// Constructor.
    TranslatorPoolsTest() { }

    /// Destructor (does nothing).
    virtual ~TranslatorPoolsTest() { }
};

// This test verifies that an empty pool list can be properly
// translated from YANG to JSON using IETF model.
TEST_F(TranslatorPoolsTest, getEmptyIetf) {
    useModel(IETF_DHCPV6_SERVER);

    // Get the pool list and check if it is empty.
    const string& xpath = "/ietf-dhcpv6-server:server/server-config/"
        "network-ranges/network-range[network-range-id='111']/address-pools";
    ConstElementPtr pools;
    EXPECT_NO_THROW(pools = t_obj_->getPools(xpath));
    ASSERT_TRUE(pools);
    ASSERT_EQ(Element::list, pools->getType());
    EXPECT_EQ(0, pools->size());
}

// This test verifies that an empty pool list can be properly
// translated from YANG to JSON using Kea ad hoc model.
TEST_F(TranslatorPoolsTest, getEmptyKea) {
    useModel(KEA_DHCP6_SERVER);

    // Get the pool list and check if it is empty.
    const string& xpath = "/kea-dhcp6-server:config/subnet6[id='111']";
    ConstElementPtr pools;
    EXPECT_NO_THROW(pools = t_obj_->getPools(xpath));
    ASSERT_TRUE(pools);
    ASSERT_EQ(Element::list, pools->getType());
    EXPECT_EQ(0, pools->size());
}

// This test verifies that one pool can be properly
// translated from YANG to JSON using IETF model.
TEST_F(TranslatorPoolsTest, getIetf) {
    useModel(IETF_DHCPV6_SERVER);

    // Create the subnet 2001:db8::/48 #111.
    const string& subnet = "/ietf-dhcpv6-server:server/server-config/"
        "network-ranges/network-range[network-range-id='111']";
    S_Val v_subnet(new Val("2001:db8::/48", SR_STRING_T));
    const string& subnet_subnet = subnet + "/network-prefix";
    EXPECT_NO_THROW(sess_->set_item(subnet_subnet.c_str(), v_subnet));

    // Create the pool 2001:db8::1:0/112 #222.
    const string& xpath = subnet + "/address-pools";
    const string& prefix = xpath + "/address-pool[pool-id='222']/pool-prefix";
    S_Val s_val(new Val("2001:db8::1:0/112"));
    EXPECT_NO_THROW(sess_->set_item(prefix.c_str(), s_val));

    // Get the pool.
    ConstElementPtr pool;
    EXPECT_NO_THROW(pool = t_obj_->getPool(xpath + "/address-pool[pool-id='222']"));
    ASSERT_TRUE(pool);
    EXPECT_EQ("{ \"pool\": \"2001:db8::1:0/112\" }", pool->str());

    // Get the pool list and check if the pool is in it.
    ConstElementPtr pools;
    EXPECT_NO_THROW(pools = t_obj_->getPools(xpath));
    ASSERT_TRUE(pools);
    ASSERT_EQ(Element::list, pools->getType());
    ASSERT_EQ(1, pools->size());
    EXPECT_TRUE(pool->equals(*pools->get(0)));
}

// This test verifies that one pool can be properly
// translated from YANG to JSON using Kea ad hoc model.
TEST_F(TranslatorPoolsTest, getKea) {
    useModel(KEA_DHCP6_SERVER);

    // Create the subnet 2001:db8::/48 #111.
    const string& xpath =
        "/kea-dhcp6-server:config/subnet6[id='111']";
    S_Val v_subnet(new Val("2001:db8::/48", SR_STRING_T));
    const string& subnet = xpath + "/subnet";
    EXPECT_NO_THROW(sess_->set_item(subnet.c_str(), v_subnet));

    // Create the pool 2001:db8::1:0/112.
    const string& prefix = "2001:db8::1:0/112";
    string start_addr;
    string end_addr;
    ASSERT_NO_THROW(TranslatorPool::getAddresses(prefix,
                                                 start_addr, end_addr));
    EXPECT_EQ("2001:db8::1:0", start_addr);
    EXPECT_EQ("2001:db8::1:ffff", end_addr);
    ostringstream spool;
    spool << xpath + "/pool[start-address='" << start_addr
          << "'][end-address='" << end_addr << "']";
    const string& x_prefix = spool.str() + "/prefix";
    S_Val s_prefix(new Val("2001:db8::1:0/112", SR_STRING_T));
    EXPECT_NO_THROW(sess_->set_item(x_prefix.c_str(), s_prefix));

    // Get the pool.
    ConstElementPtr pool;
    EXPECT_NO_THROW(pool = t_obj_->getPool(spool.str()));
    ASSERT_TRUE(pool);
    ElementPtr expected = Element::createMap();
    expected->set("pool", Element::create(string("2001:db8::1:0/112")));
    EXPECT_TRUE(expected->equals(*pool));

    // Get the pool list and check if the pool is in it.
    ConstElementPtr pools;
    EXPECT_NO_THROW(pools = t_obj_->getPools(xpath));
    ASSERT_TRUE(pools);
    ASSERT_EQ(Element::list, pools->getType());
    ASSERT_EQ(1, pools->size());
    EXPECT_TRUE(pool->equals(*pools->get(0)));
}

// This test verifies that an empty pool list can be properly
// translated from JSON to YANG using IETF model.
TEST_F(TranslatorPoolsTest, setEmptyIetf) {
    useModel(IETF_DHCPV6_SERVER);

    // Create the subnet 2001:db8::/48 #111.
    const string& subnet = "/ietf-dhcpv6-server:server/server-config/"
        "network-ranges/network-range[network-range-id='111']";
    S_Val v_subnet(new Val("2001:db8::/48", SR_STRING_T));
    const string& subnet_subnet = subnet + "/network-prefix";
    EXPECT_NO_THROW(sess_->set_item(subnet_subnet.c_str(), v_subnet));

    // Set empty list.
    const string& xpath = subnet + "/address-pools";
    ConstElementPtr pools = Element::createList();
    EXPECT_NO_THROW(t_obj_->setPools(xpath, pools));

    // Get it back.
    pools.reset();
    EXPECT_NO_THROW(pools = t_obj_->getPools(xpath));
    ASSERT_TRUE(pools);
    ASSERT_EQ(Element::list, pools->getType());
    EXPECT_EQ(0, pools->size());
}

// This test verifies that an empty pool list can be properly
// translated from JSON to YANG using Kea ad hoc model.
TEST_F(TranslatorPoolsTest, setEmptyKea) {
    useModel(KEA_DHCP6_SERVER);

    // Create the subnet 2001:db8::/48 #111.
    const string& xpath =
        "/kea-dhcp6-server:config/subnet6[id='111']";
    S_Val v_subnet(new Val("2001:db8::/48", SR_STRING_T));
    const string& subnet = xpath + "/subnet";
    EXPECT_NO_THROW(sess_->set_item(subnet.c_str(), v_subnet));

    // Set empty list.
    ConstElementPtr pools = Element::createList();
    EXPECT_NO_THROW(t_obj_->setPools(xpath, pools));

    // Get it back.
    pools.reset();
    EXPECT_NO_THROW(pools = t_obj_->getPools(xpath));
    ASSERT_TRUE(pools);
    ASSERT_EQ(Element::list, pools->getType());
    EXPECT_EQ(0, pools->size());
}

// This test verifies that one pool can be properly
// translated from JSON to YANG using IETF model.
TEST_F(TranslatorPoolsTest, setIetf) {
    useModel(IETF_DHCPV6_SERVER);

    // Create the subnet 2001:db8::/48 #111.
    const string& subnet = "/ietf-dhcpv6-server:server/server-config/"
        "network-ranges/network-range[network-range-id='111']";
    S_Val v_subnet(new Val("2001:db8::/48", SR_STRING_T));
    const string& subnet_subnet = subnet + "/network-prefix";
    EXPECT_NO_THROW(sess_->set_item(subnet_subnet.c_str(), v_subnet));

    // Set one pool.
    const string& xpath = subnet + "/address-pools";
    ElementPtr pools = Element::createList();
    ElementPtr pool = Element::createMap();
    pool->set("pool", Element::create(string("2001:db8::1:0/112")));
    pools->add(pool);
    EXPECT_NO_THROW(t_obj_->setPools(xpath, pools));

    // Get it back.
    pools.reset();
    EXPECT_NO_THROW(pools = t_obj_->getPools(xpath));
    ASSERT_TRUE(pools);
    ASSERT_EQ(Element::list, pools->getType());
    ASSERT_EQ(1, pools->size());
    EXPECT_TRUE(pool->equals(*pools->get(0)));

    // Check the tree representation.
    S_Tree tree;
    EXPECT_NO_THROW(tree = sess_->get_subtree("/ietf-dhcpv6-server:server"));
    ASSERT_TRUE(tree);
    string expected =
        "ietf-dhcpv6-server:server (container)\n"
        " |\n"
        " -- server-config (container)\n"
        "     |\n"
        "     -- network-ranges (container)\n"
        "         |\n"
        "         -- network-range (list instance)\n"
        "             |\n"
        "             -- network-range-id = 111\n"
        "             |\n"
        "             -- network-prefix = 2001:db8::/48\n"
        "             |\n"
        "             -- address-pools (container)\n"
        "                 |\n"
        "                 -- address-pool (list instance)\n"
        "                     |\n"
        "                     -- pool-id = 0\n"
        "                     |\n"
        "                     -- pool-prefix = 2001:db8::1:0/112\n"
        "                     |\n"
        "                     -- start-address = 2001:db8::1:0\n"
        "                     |\n"
        "                     -- end-address = 2001:db8::1:ffff\n"
        "                     |\n"
        "                     -- max-address-count = disabled\n";
    EXPECT_EQ(expected, tree->to_string(100));
}

// This test verifies that one pool can be properly
// translated from JSON to YANG using Kea ad hoc model.
TEST_F(TranslatorPoolsTest, setKea) {
    useModel(KEA_DHCP6_SERVER);

    // Create the subnet 2001:db8::/48 #111.
    const string& xpath =
        "/kea-dhcp6-server:config/subnet6[id='111']";
    S_Val v_subnet(new Val("2001:db8::/48", SR_STRING_T));
    const string& subnet = xpath + "/subnet";
    EXPECT_NO_THROW(sess_->set_item(subnet.c_str(), v_subnet));

    // Set one pool.
    ElementPtr pools = Element::createList();
    ElementPtr pool = Element::createMap();
    pool->set("pool",
              Element::create(string("2001:db8::1 - 2001:db8::100")));
    pools->add(pool);
    EXPECT_NO_THROW(t_obj_->setPools(xpath, pools));

    // Get it back.
    pools.reset();
    EXPECT_NO_THROW(pools = t_obj_->getPools(xpath));
    ASSERT_TRUE(pools);
    ASSERT_EQ(Element::list, pools->getType());
    ASSERT_EQ(1, pools->size());
    EXPECT_TRUE(pool->equals(*pools->get(0)));

    // Check the tree representation.
    S_Tree tree;
    EXPECT_NO_THROW(tree = sess_->get_subtree("/kea-dhcp6-server:config"));
    ASSERT_TRUE(tree);
    string expected =
        "kea-dhcp6-server:config (container)\n"
        " |\n"
        " -- subnet6 (list instance)\n"
        "     |\n"
        "     -- id = 111\n"
        "     |\n"
        "     -- subnet = 2001:db8::/48\n"
        "     |\n"
        "     -- pool (list instance)\n"
        "         |\n"
        "         -- start-address = 2001:db8::1\n"
        "         |\n"
        "         -- end-address = 2001:db8::100\n";
    EXPECT_EQ(expected, tree->to_string(100));

    // Check it validates.
    EXPECT_NO_THROW(sess_->validate());
}

}; // end of anonymous namespace
