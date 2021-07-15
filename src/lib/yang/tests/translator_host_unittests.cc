// Copyright (C) 2018-2021 Internet Systems Consortium, Inc. ("ISC")
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
using namespace sysrepo;

namespace {

/// @brief Translator name.
extern char const host_reservations[] = "host reservations";

/// @brief Test fixture class for @ref TranslatorHosts.
class TranslatorHostsTestv4 :
    public GenericTranslatorTest<host_reservations, TranslatorHosts> {
public:

    /// Constructor.
    TranslatorHostsTestv4() {
        model_ = KEA_DHCP4_SERVER;
    }
};

class TranslatorHostsTestv6 :
    public GenericTranslatorTest<host_reservations, TranslatorHosts> {
public:

    /// Constructor.
    TranslatorHostsTestv6() {
        model_ = KEA_DHCP6_SERVER;
    }
};

// This test verifies that an empty host reservation list can be properly
// translated from YANG to JSON.
TEST_F(TranslatorHostsTestv6, getEmpty) {
    // Get the host reservation list and check if it is empty.
    const string& xpath =
        "/kea-dhcp6-server:config/subnet6[id='111']";
    ConstElementPtr hosts;
    EXPECT_NO_THROW(hosts = t_obj_->getHosts(xpath));
    ASSERT_FALSE(hosts);
}

// This test verifies that one host reservation can be properly
// translated from YANG to JSON.
TEST_F(TranslatorHostsTestv6, get) {
    // Create the subnet 2001:db8::/48 #111.
    const string& xpath =
        "/kea-dhcp6-server:config/subnet6[id='111']";
    S_Val v_subnet(new Val("2001:db8::/48", SR_STRING_T));
    const string& subnet = xpath + "/subnet";
    EXPECT_NO_THROW(sess_->set_item(subnet.c_str(), v_subnet));

    // Create the host reservation for 2001:db8::1.
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

    // Get the host reservation list and check if the host reservation
    // is in it.
    ConstElementPtr hosts;
    EXPECT_NO_THROW(hosts = t_obj_->getHosts(xpath));
    ASSERT_TRUE(hosts);
    ASSERT_EQ(Element::list, hosts->getType());
    ASSERT_EQ(1, hosts->size());
    EXPECT_TRUE(host->equals(*hosts->get(0)));
}

// This test verifies that an empty host reservation list can be properly
// translated from JSON to YANG.
TEST_F(TranslatorHostsTestv6, setEmpty) {
    // Create the subnet 2001:db8::/48 #111.
    const string& xpath =
        "/kea-dhcp6-server:config/subnet6[id='111']";
    S_Val v_subnet(new Val("2001:db8::/48", SR_STRING_T));
    const string& subnet = xpath + "/subnet";
    EXPECT_NO_THROW(sess_->set_item(subnet.c_str(), v_subnet));

    // Set empty list.
    ConstElementPtr hosts = Element::createList();
    EXPECT_NO_THROW(t_obj_->setHosts(xpath, hosts));

    // Get it back.
    hosts.reset();
    EXPECT_NO_THROW(hosts = t_obj_->getHosts(xpath));
    ASSERT_FALSE(hosts);
}

// This test verifies that one host reservation can be properly
// translated from JSON to YANG.
TEST_F(TranslatorHostsTestv4, set) {
    // Create the subnet 10.0.0.0/14 #111.
    const string& xpath =
        "/kea-dhcp4-server:config/subnet4[id='111']";
    S_Val v_subnet(new Val("10.0.0.0/24", SR_STRING_T));
    const string& subnet = xpath + "/subnet";
    EXPECT_NO_THROW(sess_->set_item(subnet.c_str(), v_subnet));

    // Set one host.
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

    // Check it validates.
    EXPECT_NO_THROW(sess_->validate());
}

// This test verifies that several host reservations can be properly
// translated from YANG to JSON.
TEST_F(TranslatorHostsTestv6, getMany) {
    // Create the subnet 2001:db8::/48 #111.
    const string& xpath =
        "/kea-dhcp6-server:config/subnet6[id='111']";
    S_Val v_subnet(new Val("2001:db8::/48", SR_STRING_T));
    const string& subnet = xpath + "/subnet";
    EXPECT_NO_THROW(sess_->set_item(subnet.c_str(), v_subnet));

    // Create the host reservation for 2001:db8::1.
    ostringstream shost;
    shost << xpath + "/host[identifier-type='hw-address']"
          << "[identifier='00:01:02:03:04:05']";
    const string& xaddr = shost.str() + "/ip-addresses";
    S_Val s_addr(new Val("2001:db8::1"));
    EXPECT_NO_THROW(sess_->set_item(xaddr.c_str(), s_addr));

    // Create another reservation for 2001:db8::2
    ostringstream shost2;
    shost2 << xpath + "/host[identifier-type='hw-address']"
           << "[identifier='00:01:0a:0b:0c:0d']";
    const string xaddr2 = shost2.str() + "/ip-addresses";
    S_Val s_addr2(new Val("2001:db8::2"));
    EXPECT_NO_THROW(sess_->set_item(xaddr2.c_str(), s_addr2));

    // Get the host.
    ConstElementPtr hosts;
    EXPECT_NO_THROW(hosts = t_obj_->getHosts(xpath));
    ASSERT_TRUE(hosts);

    EXPECT_EQ(hosts->str(),
              "[ { \"hw-address\": \"00:01:02:03:04:05\", "
              "\"ip-addresses\": [ \"2001:db8::1\" ] }, "
              "{ \"hw-address\": \"00:01:0a:0b:0c:0d\", "
              "\"ip-addresses\": [ \"2001:db8::2\" ] } ]");
}

}; // end of anonymous namespace
