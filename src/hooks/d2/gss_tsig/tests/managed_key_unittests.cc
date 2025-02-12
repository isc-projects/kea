// Copyright (C) 2021-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <dns/name.h>
#include <gss_tsig_context.h>
#include <managed_key.h>
#include <testutils/gtest_utils.h>
#include <testutils/test_to_element.h>
#include <util/chrono_time_utils.h>
#include <gtest/gtest.h>

using namespace std;
using namespace std::chrono;
using namespace isc;
using namespace isc::data;
using namespace isc::dns;
using namespace isc::gss_tsig;
using namespace isc::test;
using namespace isc::util;

namespace {

/// @brief Check managed GSS-TSIG key.
TEST(ManagedKeyTest, basic) {
    ManagedKeyPtr key;
    string name = "1234.sig-foo.example.com.";
    ASSERT_NO_THROW(key.reset(new ManagedKey(name)));
    ASSERT_TRUE(key);
    EXPECT_EQ(Name(name), key->getKeyName());
    EXPECT_EQ(name, key->getKeyNameStr());

    // Parent.
    EXPECT_EQ("", key->getParentID());
    EXPECT_NO_THROW(key->setParentID("foo"));
    EXPECT_EQ("foo", key->getParentID());

    // Status.
    EXPECT_EQ(ManagedKey::NOT_READY, key->getStatus());
    EXPECT_NO_THROW(key->setStatus(ManagedKey::USABLE));
    EXPECT_EQ(ManagedKey::USABLE, key->getStatus());

    // TKEY status.
    EXPECT_EQ(TKeyExchange::OTHER, key->getTKeyStatus());
    EXPECT_NO_THROW(key->setTKeyStatus(TKeyExchange::IO_STOPPED));
    EXPECT_EQ(TKeyExchange::IO_STOPPED, key->getTKeyStatus());

    // TKEY exchange.
    EXPECT_FALSE(key->getTKeyExchange());

    // Set inception and expire.
    system_clock::time_point now = system_clock::now();
    EXPECT_NO_THROW(key->setInception(now));
    std::chrono::hours day(24);
    system_clock::time_point tomorrow = now + day;
    EXPECT_NO_THROW(key->setExpire(tomorrow));

    // TKEY completion handler.

    // Success.
    EXPECT_NO_THROW((*key)(TKeyExchange::SUCCESS));
    EXPECT_EQ(TKeyExchange::SUCCESS, key->getTKeyStatus());
    EXPECT_EQ(ManagedKey::USABLE, key->getStatus());

    // Others.
    EXPECT_NO_THROW((*key)(TKeyExchange::TIMEOUT));
    EXPECT_EQ(TKeyExchange::TIMEOUT, key->getTKeyStatus());
    EXPECT_EQ(ManagedKey::IN_ERROR, key->getStatus());

    EXPECT_NO_THROW((*key)(TKeyExchange::IO_STOPPED));
    EXPECT_EQ(TKeyExchange::IO_STOPPED, key->getTKeyStatus());
    EXPECT_EQ(ManagedKey::IN_ERROR, key->getStatus());

    EXPECT_NO_THROW((*key)(TKeyExchange::INVALID_RESPONSE));
    EXPECT_EQ(TKeyExchange::INVALID_RESPONSE, key->getTKeyStatus());
    EXPECT_EQ(ManagedKey::IN_ERROR, key->getStatus());

    EXPECT_NO_THROW((*key)(TKeyExchange::UNSIGNED_RESPONSE));
    EXPECT_EQ(TKeyExchange::UNSIGNED_RESPONSE, key->getTKeyStatus());
    EXPECT_EQ(ManagedKey::IN_ERROR, key->getStatus());

    EXPECT_NO_THROW((*key)(TKeyExchange::BAD_CREDENTIALS));
    EXPECT_EQ(TKeyExchange::BAD_CREDENTIALS, key->getTKeyStatus());
    EXPECT_EQ(ManagedKey::IN_ERROR, key->getStatus());

    EXPECT_NO_THROW((*key)(TKeyExchange::OTHER));
    EXPECT_EQ(TKeyExchange::OTHER, key->getTKeyStatus());
    EXPECT_EQ(ManagedKey::IN_ERROR, key->getStatus());

    // Note that the EXPIRED status is set by users and is in fact
    // only a shortcut i.e. can be removed leaving expire > now check.
}

/// @brief Check managed GSS-TSIG key toElement method.
TEST(ManagedKeyTest, toElement) {
    ManagedKeyPtr key;
    const string& name("1234.sig-foo.example.com.");
    ASSERT_NO_THROW(key.reset(new ManagedKey(name)));
    const string& id("foo");
    key->setParentID(id);
    system_clock::time_point now = system_clock::now();
    key->setInception(now);
    std::chrono::hours day(24);
    system_clock::time_point tomorrow = now + day;
    key->setExpire(tomorrow);
    ElementPtr expected = Element::createMap();
    expected->set("name", Element::create(name));
    expected->set("server-id", Element::create(id));
    expected->set("status", Element::create(string("not yet ready")));
    expected->set("tkey-exchange", Element::create(false));
    expected->set("inception-date", Element::create(clockToText(now)));
    expected->set("expire-date", Element::create(clockToText(tomorrow)));
    runToElementTest<ManagedKey>(expected, *key);
    expected->remove("tkey-exchange");

    // Usable.
    key->setStatus(ManagedKey::USABLE);
    expected->set("status", Element::create(string("usable")));
    runToElementTest<ManagedKey>(expected, *key);

    // Expired.
    key->setStatus(ManagedKey::EXPIRED);
    expected->set("status", Element::create(string("expired")));
    runToElementTest<ManagedKey>(expected, *key);

    // Error (timeout).
    key->setStatus(ManagedKey::IN_ERROR);
    key->setTKeyStatus(TKeyExchange::TIMEOUT);
    expected->set("status", Element::create(string("in error")));
    expected->set("tkey-status",
                  Element::create(string("no response, timeout")));
    runToElementTest<ManagedKey>(expected, *key);
}

/// @brief name generation.
TEST(ManagedKeyTest, genName) {
    string server = "foo.bar";
    string name = ManagedKey::genName(server);
    size_t dot = name.find_first_of(".");
    ASSERT_NE(dot, string::npos);
    EXPECT_EQ(server, name.substr(dot + 1));

    string name2 = ManagedKey::genName(server);
    EXPECT_NE(name, name2);
    dot = name2.find_first_of(".");
    ASSERT_NE(dot, string::npos);
    EXPECT_EQ(server, name2.substr(dot + 1));

    string name3 = ManagedKey::genName(server);
    EXPECT_NE(name, name3);
    EXPECT_NE(name2, name3);
}

/// @brief create Context.
TEST(ManagedKeyTest, createContext) {
    ManagedKeyPtr key;
    string name = "1234.sig-foo.example.com.";
    ASSERT_NO_THROW(key.reset(new ManagedKey(name)));
    ASSERT_TRUE(key);

    // Now create the context.
    TSIGContextPtr octx;
    ASSERT_NO_THROW(octx = key->createContext());
    ASSERT_TRUE(octx);
    EXPECT_EQ(TSIGContext::INIT, octx->getState());
    EXPECT_EQ(TSIGError::NOERROR(), octx->getError());
    GssTsigContextPtr ctx = boost::dynamic_pointer_cast<GssTsigContext>(octx);
    ASSERT_TRUE(ctx);
}

}
