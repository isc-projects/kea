// Copyright (C) 2011  Internet Systems Consortium, Inc. ("ISC")
//
// Permission to use, copy, modify, and/or distribute this software for any
// purpose with or without fee is hereby granted, provided that the above
// copyright notice and this permission notice appear in all copies.
//
// THE SOFTWARE IS PROVIDED "AS IS" AND ISC DISCLAIMS ALL WARRANTIES WITH
// REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
// AND FITNESS.  IN NO EVENT SHALL ISC BE LIABLE FOR ANY SPECIAL, DIRECT,
// INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
// LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE
// OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
// PERFORMANCE OF THIS SOFTWARE.

#include <server_common/keyring.h>
#include <server_common/tests/data_path.h>

#include <config/tests/fake_session.h>
#include <config/ccsession.h>
#include <dns/name.h>

#include <gtest/gtest.h>
#include <memory>
#include <string>

using namespace isc::data;
using namespace isc::config;
using namespace isc::server_common;
using namespace isc::dns;

namespace {

class KeyringTest : public ::testing::Test {
public:
    KeyringTest() :
        session(ElementPtr(new ListElement), ElementPtr(new ListElement),
                ElementPtr(new ListElement)),
        specfile(std::string(TEST_DATA_PATH) + "/spec.spec")
    {
        session.getMessages()->add(createAnswer());
        mccs.reset(new ModuleCCSession(specfile, session, NULL, NULL,
                                       false, false));
    }
    isc::cc::FakeSession session;
    std::auto_ptr<ModuleCCSession> mccs;
    std::string specfile;
    void doInit(bool with_key = true) {
        // Prepare the module specification for it and the config
        session.getMessages()->
            add(createAnswer(0,
                             moduleSpecFromFile(std::string(PLUGIN_DATA_PATH) +
                                                "/tsig_keys.spec").
                             getFullSpec()));
        if (with_key) {
            session.getMessages()->add(
                createAnswer(0, Element::fromJSON(
                                 "{\"keys\": [\"key:MTIzNAo=:hmac-sha1\"]}")));
        } else {
            // This emulates the case of using the spec default.  Note that
            // the default value won't be passed to the config handler, so
            // we'll pass an empty object, instead of {"keys": []}.
            session.getMessages()->add(createAnswer(0,
                                                    Element::fromJSON("{}")));
        }
        // Now load it
        EXPECT_NO_THROW(initKeyring(*mccs));
        EXPECT_NE(keyring, boost::shared_ptr<TSIGKeyRing>()) <<
            "No keyring even after init";
    }
};

// Test usual use - init, using the keyring, update, deinit
TEST_F(KeyringTest, keyring) {
    // First, initialize it
    {
        SCOPED_TRACE("Init");
        doInit();

        // Make sure it contains the correct key
        TSIGKeyRing::FindResult result(keyring->find(Name("key"),
                                                     TSIGKey::HMACSHA1_NAME()));
        EXPECT_EQ(TSIGKeyRing::SUCCESS, result.code);
    }

    {
        SCOPED_TRACE("Update");
        session.addMessage(createCommand("config_update", Element::fromJSON(
            "{\"keys\": [\"another:MTIzNAo=:hmac-sha256\"]}")),
                           "tsig_keys", "*");
        mccs->checkCommand();

        // Make sure it no longer contains the original key
        TSIGKeyRing::FindResult result(keyring->find(Name("key"),
                                                     TSIGKey::HMACSHA1_NAME()));
        EXPECT_EQ(TSIGKeyRing::NOTFOUND, result.code);
        // but it does contain the new one
        TSIGKeyRing::FindResult result2 = keyring->find(Name("another"),
            TSIGKey::HMACSHA256_NAME());
        EXPECT_EQ(TSIGKeyRing::SUCCESS, result2.code);
    }

    {
        SCOPED_TRACE("Deinit");
        deinitKeyring(*mccs);
        EXPECT_EQ(keyring, boost::shared_ptr<TSIGKeyRing>()) <<
            "The keyring didn't disappear";
    }
}

TEST_F(KeyringTest, keyringWithDefault) {
    // If we don't explicitly specify a keyring, the default (no key) will
    // be used.
    doInit(false);
    EXPECT_EQ(0, keyring->size());
    deinitKeyring(*mccs);
}

// Init twice
TEST_F(KeyringTest, initTwice) {
    // It is NULL before
    EXPECT_EQ(keyring, boost::shared_ptr<TSIGKeyRing>()) <<
        "Someone forgot to deinit it before";
    {
        SCOPED_TRACE("First init");
        doInit();
    }
    boost::shared_ptr<TSIGKeyRing> backup(keyring);
    {
        SCOPED_TRACE("Second init");
        EXPECT_NO_THROW(initKeyring(*mccs)) <<
            "It not only does something when it is already initialized, "
            "it even throws at it";
    }
    EXPECT_EQ(backup, keyring) << "The second init replaced the data";
    deinitKeyring(*mccs);
}

// deinit when not initialized
TEST_F(KeyringTest, extraDeinit) {
    // It is NULL before
    EXPECT_EQ(boost::shared_ptr<TSIGKeyRing>(), keyring) <<
        "Someone forgot to deinit it before";
    // Check that it doesn't get confused when we do not have it initialized
    EXPECT_NO_THROW(deinitKeyring(*mccs));
    // It is still NULL
    EXPECT_EQ(keyring, boost::shared_ptr<TSIGKeyRing>()) <<
        "Where did it get something after deinit?";
}

}
