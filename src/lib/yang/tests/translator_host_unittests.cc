// Copyright (C) 2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <yang/translator_host.h>
#include <yang/yang_models.h>
#include <yang/tests/sysrepo_setup.h>

#include <gtest/gtest.h>
#include <sstream>

using namespace std;
using namespace isc;
using namespace isc::data;
using namespace isc::yang;
using namespace isc::yang::test;

namespace {

/// @brief Translator name.
extern char const host_reservations[] = "host reservations";

/// @brief Test fixture class for @ref TranslatorHosts.
class TranslatorHostsTest :
    public GenericTranslatorTest<host_reservations, TranslatorHosts> {
public:

    /// Constructor.
    TranslatorHostsTest() { }

    /// Destructor (does nothing).
    virtual ~TranslatorHostsTest() { }
};

// This test verifies that an empty host reservation list can be properly
// translated from YANG to JSON.
TEST_F(TranslatorHostsTest, getEmpty) {
    useModel(KEA_DHCP6_SERVER);

    // Get the host reservation list and checks it is empty.
    const string& xpath =
        "/kea-dhcp6-server:config/subnet6/subnet6[id='111']/reservations";
    ConstElementPtr hosts;
    EXPECT_NO_THROW(hosts = t_obj_->getHosts(xpath));
    ASSERT_TRUE(hosts);
    ASSERT_EQ(Element::list, hosts->getType());
    EXPECT_EQ(0, hosts->size());
}

// This test verifies that one host reservation can be properly
// translated from YANG to JSON.
TEST_F(TranslatorHostsTest, get) {
    useModel(KEA_DHCP6_SERVER);

    // Create the subnet 2001:db8::/48 #111.
    const string& subnet =
        "/kea-dhcp6-server:config/subnet6/subnet6[id='111']";
    S_Val v_subnet(new Val("2001:db8::/48", SR_STRING_T));
    const string& xsubnet = subnet + "/subnet";
    EXPECT_NO_THROW(sess_->set_item(xsubnet.c_str(), v_subnet));

    // Create the host reservation for 2001:db8::1.
    const string& xpath = subnet + "/reservations";
    ostringstream shost;
    shost << xpath + "/host[identifier-type='hw-address']"
          << "[identifier='00:01:02:03:04:05']";
    const string& xaddr = shost.str() + "/ip-addresses";
    S_Val s_addr(new Val("2001:db8::1"));
    EXPECT_NO_THROW(sess_->set_item(xaddr.c_str(), s_addr));

    // Get the host.
    ConstElementPtr host;
    EXPECT_NO_THROW(host = t_obj_->getHost(shost.str()));
    ASSERT_TRUE(host);
    ElementPtr expected = Element::createMap();
    ElementPtr addresses = Element::createList();
    addresses->add(Element::create(string("2001:db8::1")));
    expected->set("hw-address", Element::create(string("00:01:02:03:04:05")));
    expected->set("ip-addresses", addresses);
    EXPECT_TRUE(expected->equals(*host));

    // Get the host reservation list and checks the host reservation is in it.
    ConstElementPtr hosts;
    EXPECT_NO_THROW(hosts = t_obj_->getHosts(xpath));
    ASSERT_TRUE(hosts);
    ASSERT_EQ(Element::list, hosts->getType());
    ASSERT_EQ(1, hosts->size());
    EXPECT_TRUE(host->equals(*hosts->get(0)));
}

// This test verifies that an empty host reservation list can be properly
// translated from JSON to YANG.
TEST_F(TranslatorHostsTest, setEmpty) {
    useModel(KEA_DHCP6_SERVER);

    // Create the subnet 2001:db8::/48 #111.
    const string& subnet =
        "/kea-dhcp6-server:config/subnet6/subnet6[id='111']";
    S_Val v_subnet(new Val("2001:db8::/48", SR_STRING_T));
    const string& xsubnet = subnet + "/subnet";
    EXPECT_NO_THROW(sess_->set_item(xsubnet.c_str(), v_subnet));

    // Set empty list.
    const string& xpath = subnet + "/reservations";
    ConstElementPtr hosts = Element::createList();
    EXPECT_NO_THROW(t_obj_->setHosts(xpath, hosts));

    // Get it back.
    hosts.reset();
    EXPECT_NO_THROW(hosts = t_obj_->getHosts(xpath));
    ASSERT_TRUE(hosts);
    ASSERT_EQ(Element::list, hosts->getType());
    EXPECT_EQ(0, hosts->size());
}

// This test verifies that one host reservation can be properly
// translated from JSON to YANG.
TEST_F(TranslatorHostsTest, set) {
    useModel(KEA_DHCP4_SERVER);

    // Create the subnet 10.0.0.0/14 #111.
    const string& subnet =
        "/kea-dhcp4-server:config/subnet4/subnet4[id='111']";
    S_Val v_subnet(new Val("10.0.0.0/24", SR_STRING_T));
    const string& xsubnet = subnet + "/subnet";
    EXPECT_NO_THROW(sess_->set_item(xsubnet.c_str(), v_subnet));

    // Set one host.
    const string& xpath = subnet + "/reservations";
    ElementPtr hosts = Element::createList();
    ElementPtr host = Element::createMap();
    host->set("flex-id", Element::create(string("00:ff")));
    host->set("ip-address", Element::create(string("10.0.0.1")));
    host->set("hostname", Element::create(string("foo")));
    hosts->add(host);
    EXPECT_NO_THROW(t_obj_->setHosts(xpath, hosts));

    // Get it back.
    hosts.reset();
    EXPECT_NO_THROW(hosts = t_obj_->getHosts(xpath));
    ASSERT_TRUE(hosts);
    ASSERT_EQ(Element::list, hosts->getType());
    ASSERT_EQ(1, hosts->size());
    EXPECT_TRUE(host->equals(*hosts->get(0)));

    // Check the tree representation.
    S_Tree tree;
    EXPECT_NO_THROW(tree = sess_->get_subtree("/kea-dhcp4-server:config"));
    ASSERT_TRUE(tree);
    string expected =
        "kea-dhcp4-server:config (container)\n"
        " |\n"
        " -- subnet4 (container)\n"
        "     |\n"
        "     -- subnet4 (list instance)\n"
        "         |\n"
        "         -- id = 111\n"
        "         |\n"
        "         -- subnet = 10.0.0.0/24\n"
        "         |\n"
        "         -- reservations (container)\n"
        "             |\n"
        "             -- host (list instance)\n"
        "                 |\n"
        "                 -- identifier-type = flex-id\n"
        "                 |\n"
        "                 -- identifier = 00:ff\n"
        "                 |\n"
        "                 -- hostname = foo\n"
        "                 |\n"
        "                 -- ip-address = 10.0.0.1\n";
    EXPECT_EQ(expected, tree->to_string(100));

    // Check it validates.
    EXPECT_NO_THROW(sess_->validate());
}

}; // end of anonymous namespace
