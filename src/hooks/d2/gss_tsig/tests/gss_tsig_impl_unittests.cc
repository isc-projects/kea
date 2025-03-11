// Copyright (C) 2021-2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <cc/command_interpreter.h>
#include <gss_tsig_impl.h>
#include <hooks/hooks_manager.h>
#include <gss_tsig_api_utils.h>
#include <testutils/gss_tsig_dns_server.h>
#include <testutils/gtest_utils.h>
#include <gtest/gtest.h>

using namespace std;
using namespace std::chrono;
using namespace isc;
using namespace isc::asiodns;
using namespace isc::asiolink;
using namespace isc::config;
using namespace isc::data;
using namespace isc::gss_tsig;
using namespace isc::gss_tsig::test;
using namespace isc::hooks;

namespace {

const char* TEST_ADDRESS = "127.0.0.1";
const uint16_t TEST_PORT = 5376;
const std::chrono::hours HOUR(1);
const std::chrono::seconds SECOND(1);

/// @brief Test class derived from GssTsigImpl.
class TestGssTsigImpl : public GssTsigImpl {
public:
    /// Export the cfg_ and keys_ fields.
    using GssTsigImpl::cfg_;
    using GssTsigImpl::keys_;
};

/// @brief Type of pointers to TestGssTsigImpl.
typedef unique_ptr<TestGssTsigImpl> TestGssTsigImplPtr;

/// @brief Test fixture for testing the GSS-TSIG hook implementation.
class GssTsigImplTest : public GssApiBaseTest {
public:
    /// @brief Constructor.
    GssTsigImplTest() : impl_(new TestGssTsigImpl()), expected_keys_(-1),
            io_service_(new IOService()), go_on_(true) {
        setKeytab();
        setAdministratorCCache();
        impl_->setIOService(io_service_);
        impl_->start();
        io_service_->stopAndPoll();
    }

    /// @brief Destructor.
    virtual ~GssTsigImplTest() {
        impl_.reset();
        if (test_timer_) {
            test_timer_->cancel();
        }
        io_service_->stopAndPoll();
    }

    /// @brief The implementation.
    TestGssTsigImplPtr impl_;

    /// @brief The expected number of keys.
    int32_t expected_keys_;

    /// @brief The IOService which handles IO operations.
    IOServicePtr io_service_;

    /// @brief The test timer.
    asiolink::IntervalTimerPtr test_timer_;

    /// @brief The flag which indicates if the test should go on.
    bool go_on_;

    /// @brief Dummy DNS server.
    boost::shared_ptr<DummyDNSServer> dns_server_;

    /// @brief Start the test interval timer to check key renewal.
    ///
    /// @param interval The time interval to check the current number of keys.
    /// @param restart The flag which indicates if the internal key manager
    /// timers should be restarted (after updating the configuration).
    /// @param server If not null, add the server to the configuration if doing
    /// restart.
    void startTimer(uint32_t interval, bool restart = false,
                    DnsServerPtr server = DnsServerPtr()) {
        cout << "started " << interval << " ms timer" << endl;
        if (test_timer_) {
            test_timer_->cancel();
        }
        io_service_->stopAndPoll();
        if (restart) {
            impl_->stop();
            if (server) {
                impl_->cfg_.addServer(server);
            }
            impl_->start();
        }
        io_service_->stopAndPoll();
        test_timer_.reset(new IntervalTimer(io_service_));
        test_timer_->setup(std::bind(&GssTsigImplTest::testTimerHandler,
                                     this), interval);
    }

    /// @brief Handler invoked when test time interval is hit.
    ///
    /// This callback stops all running (hanging) tasks on IO service.
    void testTimerHandler() {
        io_service_->stop();
        try {
            io_service_->poll();
        } catch (...) {
        }
        if (expected_keys_ != -1) {
            if (static_cast<int32_t>(impl_->keys_.size()) != expected_keys_) {
                go_on_ = false;
                FAIL() << "The number of expected keys " << expected_keys_
                       << " is different than actual " << impl_->keys_.size();
            }
        } else {
            go_on_ = false;
            FAIL() << "Test timeout hit.";
        }
    }

    /// @brief Check keys.
    ///
    /// @param expected_not_ready The number of keys in NOT_READY state.
    /// @param expected_usable The number of keys in USABLE state.
    /// @param expected_expired The number of keys in EXPIRED state.
    /// @param expected_in_error The number ok keys in IN_ERROR state.
    void checkKeys(uint32_t expected_not_ready, uint32_t expected_usable,
                   uint32_t expected_expired, uint32_t expected_in_error) {
        uint32_t not_ready = 0;
        uint32_t usable = 0;
        uint32_t expired = 0;
        uint32_t in_error = 0;
        for (auto const& key : impl_->keys_) {
            if (key->getStatus() == ManagedKey::NOT_READY) {
                not_ready++;
            } else if (key->getStatus() == ManagedKey::USABLE) {
                usable++;
            } else if (key->getStatus() == ManagedKey::EXPIRED) {
                expired++;
            } else if (key->getStatus() == ManagedKey::IN_ERROR) {
                in_error++;
            }
        }
        EXPECT_EQ(not_ready, expected_not_ready);
        EXPECT_EQ(usable, expected_usable);
        EXPECT_EQ(expired, expected_expired);
        EXPECT_EQ(in_error, expected_in_error);
        EXPECT_EQ(impl_->keys_.size(), not_ready + usable + expired + in_error);
    }

    /// @brief Check command answer.
    ///
    /// @param answer Command answer.
    /// @param exp_status Expected status.
    /// @param exp_txt Expected text.
    /// @param exp_args Expected arguments.
    void checkAnswer(const ConstElementPtr& answer, int exp_status,
                     const string& exp_txt, const ConstElementPtr& exp_args) {
        ASSERT_TRUE(answer);
        ASSERT_EQ(Element::map, answer->getType());

        ConstElementPtr result = answer->get(CONTROL_RESULT);
        ASSERT_TRUE(result);
        ASSERT_EQ(Element::integer, result->getType());
        EXPECT_EQ(exp_status, result->intValue());

        ConstElementPtr txt = answer->get(CONTROL_TEXT);
        ASSERT_TRUE(txt);
        ASSERT_EQ(Element::string, txt->getType());
        EXPECT_EQ(exp_txt, txt->stringValue());

        ConstElementPtr args = answer->get(CONTROL_ARGUMENTS);
        if (exp_args) {
            ASSERT_TRUE(args);
            EXPECT_EQ(exp_args->str(), args->str());
        } else {
            EXPECT_FALSE(args);
        }
    }
};

/// @brief Check the constructor builds what is expected.
TEST_F(GssTsigImplTest, basic) {
    ASSERT_TRUE(impl_);
}

/// @brief Check the configure method can set and restore environment variables.
TEST_F(GssTsigImplTest, envVars) {
    // Set values which should be overwritten by configure and restored by stop.
    setenv("KRB5_CLIENT_KTNAME", "foo", 1);
    setenv("KRB5CCNAME", "bar", 1);

    // A configuration with environment variable settings.
    string config = "{\n"
        " \"client-keytab\": \"my-client-keytab\",\n"
        " \"credentials-cache\": \"my-ccache\"\n"
        "}";
    ConstElementPtr cfg = Element::fromJSON(config);
    EXPECT_NO_THROW(impl_->configure(cfg));

    // Check new values.
    EXPECT_EQ("my-client-keytab", impl_->cfg_.getClientKeyTab());
    EXPECT_EQ("my-ccache", impl_->cfg_.getCredsCache());

    // Restore values.
    EXPECT_NO_THROW(impl_->stop());
    char* ktname = getenv("KRB5_CLIENT_KTNAME");
    ASSERT_TRUE(ktname);
    EXPECT_EQ("foo", string(ktname));
    char* ccname = getenv("KRB5CCNAME");
    ASSERT_TRUE(ccname);
    EXPECT_EQ("bar", string(ccname));
}

/// @brief Tests status-get command processed handler.
TEST_F(GssTsigImplTest, commandProcess) {
    string command = "foo-bar";
    string response = "{ \"arguments\": { \"pid\": 1 }, \"result\": 0 }";
    ConstElementPtr resp = Element::fromJSON(response);
    ASSERT_TRUE(resp);

    // Only status-get is handled.
    CalloutHandlePtr callout_handle = HooksManager::createCalloutHandle();
    callout_handle->setArgument("name", command);
    callout_handle->setArgument("response", resp);
    ASSERT_NO_THROW(impl_->commandProcessed(*callout_handle));
    ConstElementPtr got;
    callout_handle->getArgument("response", got);
    ASSERT_TRUE(got);
    EXPECT_EQ(resp->str(), got->str());

    // Status-get has "gss-tsig": true new entry.
    command = "status-get";
    callout_handle->setArgument("name", command);
    callout_handle->setArgument("response", resp);
    ASSERT_NO_THROW(impl_->commandProcessed(*callout_handle));
    callout_handle->getArgument("response", got);
    ASSERT_TRUE(got);
    string expected_str = "{ ";
    expected_str += "\"arguments\": { \"pid\": 1,  \"gss-tsig\": true },";
    expected_str += "\"result\": 0 }";
    ElementPtr expected = Element::fromJSON(expected_str);
    EXPECT_EQ(expected->str(), got->str());

    // Check soft failure cases (there is no hard failure case).

    {
        SCOPED_TRACE("Null response.");
        resp = ConstElementPtr();
        callout_handle->setArgument("response", resp);
        ASSERT_NO_THROW(impl_->commandProcessed(*callout_handle));
        callout_handle->getArgument("response", got);
        EXPECT_FALSE(got);
    }

    {
        SCOPED_TRACE("Not a map.");
        resp = Element::createList();
        callout_handle->setArgument("response", resp);
        ASSERT_NO_THROW(impl_->commandProcessed(*callout_handle));
        callout_handle->getArgument("response", got);
        ASSERT_TRUE(got);
        expected = Element::createList();
        EXPECT_EQ(expected->str(), got->str());
    }

    {
        SCOPED_TRACE("No arguments.");
        resp = Element::createMap();
        callout_handle->setArgument("response", resp);
        ASSERT_NO_THROW(impl_->commandProcessed(*callout_handle));
        callout_handle->getArgument("response", got);
        ASSERT_TRUE(got);
        expected = Element::createMap();
        EXPECT_EQ(expected->str(), got->str());
    }

    {
        SCOPED_TRACE("Not map arguments.");
        response = "{ \"arguments\": [ ] }";
        resp = Element::fromJSON(response);
        callout_handle->setArgument("response", resp);
        ASSERT_NO_THROW(impl_->commandProcessed(*callout_handle));
        callout_handle->getArgument("response", got);
        ASSERT_TRUE(got);
        EXPECT_EQ(resp->str(), got->str());
    }
}

/// @brief Tests gss-tsig-get-all command handler.
TEST_F(GssTsigImplTest, getAllHandler) {
    string command_str = "{ \"command\": \"gss-tsig-get-all\" }";
    ElementPtr command = Element::fromJSON(command_str);
    ASSERT_TRUE(command);
    CalloutHandlePtr callout_handle = HooksManager::createCalloutHandle();
    int expected_status = CONTROL_RESULT_EMPTY;
    string expected_txt = "0 GSS-TSIG servers";
    ElementPtr expected = Element::createMap();
    ElementPtr exp_list = Element::createList();
    expected->set("gss-tsig-servers", exp_list);

    {
        SCOPED_TRACE("Empty config.");
        callout_handle->setArgument("command", command);
        ASSERT_NO_THROW(impl_->getAllHandler(*callout_handle));
        ConstElementPtr response;
        callout_handle->getArgument("response", response);
        ASSERT_TRUE(response);
        checkAnswer(response, expected_status, expected_txt, expected);
    }

    {
        SCOPED_TRACE("One empty server.");
        DnsServerPtr srv;
        const string& id("foo");
        set<string> domains;
        IOAddress addr("192.1.2.3");
        ASSERT_NO_THROW(srv.reset(new DnsServer(id, domains, addr)));
        ASSERT_TRUE(srv);
        impl_->cfg_.addServer(srv);
        callout_handle->setArgument("command", command);
        ASSERT_NO_THROW(impl_->getAllHandler(*callout_handle));
        ConstElementPtr response;
        callout_handle->getArgument("response", response);
        ASSERT_TRUE(response);
        expected_status = CONTROL_RESULT_SUCCESS;
        expected_txt = "1 GSS-TSIG servers and 0 keys";
        ElementPtr desc = srv->toElement();
        desc->set("keys", Element::createList());
        exp_list->add(desc);
        checkAnswer(response, expected_status, expected_txt, expected);
    }

    {
        SCOPED_TRACE("Two servers, second with a key.");
        DnsServerPtr srv;
        const string& id("bar");
        set<string> domains = { "foo" };
        IOAddress addr("192.1.2.4");
        ASSERT_NO_THROW(srv.reset(new DnsServer(id, domains, addr)));
        ASSERT_TRUE(srv);
        impl_->cfg_.addServer(srv);
        ManagedKeyPtr key;
        string name = "1234.sig-foo.example.com.";
        ASSERT_NO_THROW(key.reset(new ManagedKey(name)));
        system_clock::time_point now = system_clock::now();
        key->setInception(now);
        system_clock::time_point tomorrow = now + 24 * HOUR;
        key->setExpire(tomorrow);
        key->setParentID(id);
        impl_->keys_.insert(key);
        callout_handle->setArgument("command", command);
        ASSERT_NO_THROW(impl_->getAllHandler(*callout_handle));
        ConstElementPtr response;
        callout_handle->getArgument("response", response);
        ASSERT_TRUE(response);
        expected_status = CONTROL_RESULT_SUCCESS;
        expected_txt = "2 GSS-TSIG servers and 1 keys";
        ElementPtr desc = srv->toElement();
        ElementPtr keys = Element::createList();
        keys->add(key->toElement());
        desc->set("keys", keys);
        exp_list->add(desc);
        checkAnswer(response, expected_status, expected_txt, expected);
    }
}

/// @brief Tests gss-tsig-get command handler.
TEST_F(GssTsigImplTest, getHandler) {
    ElementPtr command = Element::createMap();
    command->set("command", Element::create(string("gss-tsig-get")));
    CalloutHandlePtr callout_handle = HooksManager::createCalloutHandle();
    int expected_status = CONTROL_RESULT_ERROR;
    string expected_txt;
    ElementPtr expected;

    {
        SCOPED_TRACE("No arguments.");
        // Force template instance.
        callout_handle->setArgument<ConstElementPtr>("command", command);
        ASSERT_NO_THROW(impl_->getHandler(*callout_handle));
        ConstElementPtr response;
        callout_handle->getArgument("response", response);
        ASSERT_TRUE(response);
        expected_txt = "arguments not found in the '";
        expected_txt += "{ \"command\": \"gss-tsig-get\" }' command";
        checkAnswer(response, expected_status, expected_txt, expected);
    }

    {
        SCOPED_TRACE("Arguments is not a map.");
        command->set("arguments", Element::createList());
        // Force template instance.
        callout_handle->setArgument<ConstElementPtr>("command", command);
        ASSERT_NO_THROW(impl_->getHandler(*callout_handle));
        ConstElementPtr response;
        callout_handle->getArgument("response", response);
        ASSERT_TRUE(response);
        expected_txt = "arguments in the '{ \"arguments\": [  ], ";
        expected_txt += "\"command\": \"gss-tsig-get\" }' ";
        expected_txt += "command are not a map";
        checkAnswer(response, expected_status, expected_txt, expected);
    }

    ElementPtr args = Element::createMap();
    command->set("arguments", args);

    {
        SCOPED_TRACE("Empty arguments.");
        // Force template instance.
        callout_handle->setArgument<ConstElementPtr>("command", command);
        ASSERT_NO_THROW(impl_->getHandler(*callout_handle));
        ConstElementPtr response;
        callout_handle->getArgument("response", response);
        ASSERT_TRUE(response);
        expected_txt = "'server-id' is mandatory for the '";
        expected_txt += "{ \"arguments\": {  }, ";
        expected_txt += "\"command\": \"gss-tsig-get\" }' command";
        checkAnswer(response, expected_status, expected_txt, expected);
    }

    {
        SCOPED_TRACE("Bad server-id.");
        args->set("server-id", Element::create(12345));
        // Force template instance.
        callout_handle->setArgument<ConstElementPtr>("command", command);
        ASSERT_NO_THROW(impl_->getHandler(*callout_handle));
        ConstElementPtr response;
        callout_handle->getArgument("response", response);
        ASSERT_TRUE(response);
        expected_txt = "'server-id' must be a string in the '";
        expected_txt += "{ \"arguments\": { ";
        expected_txt += "\"server-id\": 12345 }, ";
        expected_txt += "\"command\": \"gss-tsig-get\" }' command";
        checkAnswer(response, expected_status, expected_txt, expected);
    }

    {
        SCOPED_TRACE("No server");
        args->set("server-id", Element::create(string("foo")));
        // Force template instance.
        callout_handle->setArgument<ConstElementPtr>("command", command);
        ASSERT_NO_THROW(impl_->getHandler(*callout_handle));
        ConstElementPtr response;
        callout_handle->getArgument("response", response);
        ASSERT_TRUE(response);
        expected_status = CONTROL_RESULT_EMPTY;
        expected_txt = "GSS-TSIG server[foo] not found";
        checkAnswer(response, expected_status, expected_txt, expected);
    }

    {
        SCOPED_TRACE("Matching server");
        DnsServerPtr srv;
        const string& id("foo");
        set<string> domains;
        IOAddress addr("192.1.2.3");
        ASSERT_NO_THROW(srv.reset(new DnsServer(id, domains, addr)));
        ASSERT_TRUE(srv);
        impl_->cfg_.addServer(srv);
        args->set("server-id", Element::create(id));
        // Force template instance.
        callout_handle->setArgument<ConstElementPtr>("command", command);
        ASSERT_NO_THROW(impl_->getHandler(*callout_handle));
        ConstElementPtr response;
        callout_handle->getArgument("response", response);
        ASSERT_TRUE(response);
        expected_status = CONTROL_RESULT_SUCCESS;
        expected_txt = "GSS-TSIG server[" + id + "] found";
        expected = srv->toElement();
        expected->set("keys", Element::createList());
        checkAnswer(response, expected_status, expected_txt, expected);
    }
}

/// @brief Tests gss-tsig-list command handler.
TEST_F(GssTsigImplTest, listHandler) {
    string command_str = "{ \"command\": \"gss-tsig-list\" }";
    ElementPtr command = Element::fromJSON(command_str);
    ASSERT_TRUE(command);
    CalloutHandlePtr callout_handle = HooksManager::createCalloutHandle();
    int expected_status = CONTROL_RESULT_EMPTY;
    string expected_txt = "0 GSS-TSIG servers and 0 keys";
    ElementPtr expected = Element::createMap();
    ElementPtr exp_servers = Element::createList();
    expected->set("gss-tsig-servers", exp_servers);
    ElementPtr exp_keys = Element::createList();
    expected->set("gss-tsig-keys", exp_keys);

    {
        SCOPED_TRACE("Empty config.");
        callout_handle->setArgument("command", command);
        ASSERT_NO_THROW(impl_->listHandler(*callout_handle));
        ConstElementPtr response;
        callout_handle->getArgument("response", response);
        ASSERT_TRUE(response);
        checkAnswer(response, expected_status, expected_txt, expected);
    }

    {
        SCOPED_TRACE("One empty server.");
        DnsServerPtr srv;
        const string& id("foo");
        set<string> domains;
        IOAddress addr("192.1.2.3");
        ASSERT_NO_THROW(srv.reset(new DnsServer(id, domains, addr)));
        ASSERT_TRUE(srv);
        impl_->cfg_.addServer(srv);
        callout_handle->setArgument("command", command);
        ASSERT_NO_THROW(impl_->listHandler(*callout_handle));
        ConstElementPtr response;
        callout_handle->getArgument("response", response);
        ASSERT_TRUE(response);
        expected_status = CONTROL_RESULT_SUCCESS;
        expected_txt = "1 GSS-TSIG servers and 0 keys";
        exp_servers->add(Element::create(id));
        checkAnswer(response, expected_status, expected_txt, expected);
    }

    {
        SCOPED_TRACE("Two servers, second with a key.");
        DnsServerPtr srv;
        const string& id("bar");
        set<string> domains = { "foo" };
        IOAddress addr("192.1.2.4");
        ASSERT_NO_THROW(srv.reset(new DnsServer(id, domains, addr)));
        ASSERT_TRUE(srv);
        impl_->cfg_.addServer(srv);
        ManagedKeyPtr key;
        string name = "1234.sig-foo.example.com.";
        ASSERT_NO_THROW(key.reset(new ManagedKey(name)));
        system_clock::time_point now = system_clock::now();
        key->setInception(now);
        system_clock::time_point tomorrow = now + 24 * HOUR;
        key->setExpire(tomorrow);
        key->setParentID(id);
        impl_->keys_.insert(key);
        callout_handle->setArgument("command", command);
        ASSERT_NO_THROW(impl_->listHandler(*callout_handle));
        ConstElementPtr response;
        callout_handle->getArgument("response", response);
        ASSERT_TRUE(response);
        expected_status = CONTROL_RESULT_SUCCESS;
        expected_txt = "2 GSS-TSIG servers and 1 keys";
        exp_servers->add(Element::create(id));
        exp_keys->add(Element::create(name));
        checkAnswer(response, expected_status, expected_txt, expected);
    }
}

/// @brief Tests gss-tsig-key-get command handler.
TEST_F(GssTsigImplTest, keyGetHandler) {
    ElementPtr command = Element::createMap();
    command->set("command", Element::create(string("gss-tsig-key-get")));
    CalloutHandlePtr callout_handle = HooksManager::createCalloutHandle();
    int expected_status = CONTROL_RESULT_ERROR;
    string expected_txt;
    ElementPtr expected;

    {
        SCOPED_TRACE("No arguments.");
        // Force template instance.
        callout_handle->setArgument<ConstElementPtr>("command", command);
        ASSERT_NO_THROW(impl_->keyGetHandler(*callout_handle));
        ConstElementPtr response;
        callout_handle->getArgument("response", response);
        ASSERT_TRUE(response);
        expected_txt = "arguments not found in the '";
        expected_txt += "{ \"command\": \"gss-tsig-key-get\" }' command";
        checkAnswer(response, expected_status, expected_txt, expected);
    }

    {
        SCOPED_TRACE("Arguments is not a map.");
        command->set("arguments", Element::createList());
        // Force template instance.
        callout_handle->setArgument<ConstElementPtr>("command", command);
        ASSERT_NO_THROW(impl_->keyGetHandler(*callout_handle));
        ConstElementPtr response;
        callout_handle->getArgument("response", response);
        ASSERT_TRUE(response);
        expected_txt = "arguments in the '{ \"arguments\": [  ], ";
        expected_txt += "\"command\": \"gss-tsig-key-get\" }' ";
        expected_txt += "command are not a map";
        checkAnswer(response, expected_status, expected_txt, expected);
    }

    ElementPtr args = Element::createMap();
    command->set("arguments", args);

    {
        SCOPED_TRACE("Empty arguments.");
        // Force template instance.
        callout_handle->setArgument<ConstElementPtr>("command", command);
        ASSERT_NO_THROW(impl_->keyGetHandler(*callout_handle));
        ConstElementPtr response;
        callout_handle->getArgument("response", response);
        ASSERT_TRUE(response);
        expected_txt = "'key-name' is mandatory for the '";
        expected_txt += "{ \"arguments\": {  }, ";
        expected_txt += "\"command\": \"gss-tsig-key-get\" }' command";
        checkAnswer(response, expected_status, expected_txt, expected);
    }

    {
        SCOPED_TRACE("Bad key-name.");
        args->set("key-name", Element::create(12345));
        // Force template instance.
        callout_handle->setArgument<ConstElementPtr>("command", command);
        ASSERT_NO_THROW(impl_->keyGetHandler(*callout_handle));
        ConstElementPtr response;
        callout_handle->getArgument("response", response);
        ASSERT_TRUE(response);
        expected_txt = "'key-name' must be a string in the '";
        expected_txt += "{ \"arguments\": { ";
        expected_txt += "\"key-name\": 12345 }, ";
        expected_txt += "\"command\": \"gss-tsig-key-get\" }' command";
        checkAnswer(response, expected_status, expected_txt, expected);
    }

    string name = "foo.bar.";
    args->set("key-name", Element::create(name));

    {
        SCOPED_TRACE("No key");
        // Force template instance.
        callout_handle->setArgument<ConstElementPtr>("command", command);
        ASSERT_NO_THROW(impl_->keyGetHandler(*callout_handle));
        ConstElementPtr response;
        callout_handle->getArgument("response", response);
        ASSERT_TRUE(response);
        expected_status = CONTROL_RESULT_EMPTY;
        expected_txt = "GSS-TSIG key '" + name + "' not found";
        checkAnswer(response, expected_status, expected_txt, expected);
    }

    {
        SCOPED_TRACE("Matching key");
        ManagedKeyPtr key;
        ASSERT_NO_THROW(key.reset(new ManagedKey(name)));
        system_clock::time_point now = system_clock::now();
        key->setInception(now);
        system_clock::time_point tomorrow = now + 24 * HOUR;
        key->setExpire(tomorrow);
        key->setParentID("foo");
        impl_->keys_.insert(key);
        // Force template instance.
        callout_handle->setArgument<ConstElementPtr>("command", command);
        ASSERT_NO_THROW(impl_->keyGetHandler(*callout_handle));
        ConstElementPtr response;
        callout_handle->getArgument("response", response);
        ASSERT_TRUE(response);
        expected_status = CONTROL_RESULT_SUCCESS;
        expected_txt = "GSS-TSIG key '" + name + "' found";
        expected = key->toElement();
        checkAnswer(response, expected_status, expected_txt, expected);
    }
}

/// @brief Tests gss-tsig-key-expire command handler.
TEST_F(GssTsigImplTest, keyExpireHandler) {
    ElementPtr command = Element::createMap();
    command->set("command", Element::create(string("gss-tsig-key-expire")));
    CalloutHandlePtr callout_handle = HooksManager::createCalloutHandle();
    int expected_status = CONTROL_RESULT_ERROR;
    string expected_txt;
    ElementPtr expected;

    {
        SCOPED_TRACE("No arguments.");
        // Force template instance.
        callout_handle->setArgument<ConstElementPtr>("command", command);
        ASSERT_NO_THROW(impl_->keyExpireHandler(*callout_handle));
        ConstElementPtr response;
        callout_handle->getArgument("response", response);
        ASSERT_TRUE(response);
        expected_txt = "arguments not found in the '";
        expected_txt += "{ \"command\": \"gss-tsig-key-expire\" }' command";
        checkAnswer(response, expected_status, expected_txt, expected);
    }

    {
        SCOPED_TRACE("Arguments is not a map.");
        command->set("arguments", Element::createList());
        // Force template instance.
        callout_handle->setArgument<ConstElementPtr>("command", command);
        ASSERT_NO_THROW(impl_->keyExpireHandler(*callout_handle));
        ConstElementPtr response;
        callout_handle->getArgument("response", response);
        ASSERT_TRUE(response);
        expected_txt = "arguments in the '{ \"arguments\": [  ], ";
        expected_txt += "\"command\": \"gss-tsig-key-expire\" }' ";
        expected_txt += "command are not a map";
        checkAnswer(response, expected_status, expected_txt, expected);
    }

    ElementPtr args = Element::createMap();
    command->set("arguments", args);

    {
        SCOPED_TRACE("Empty arguments.");
        // Force template instance.
        callout_handle->setArgument<ConstElementPtr>("command", command);
        ASSERT_NO_THROW(impl_->keyExpireHandler(*callout_handle));
        ConstElementPtr response;
        callout_handle->getArgument("response", response);
        ASSERT_TRUE(response);
        expected_txt = "'key-name' is mandatory for the '";
        expected_txt += "{ \"arguments\": {  }, ";
        expected_txt += "\"command\": \"gss-tsig-key-expire\" }' command";
        checkAnswer(response, expected_status, expected_txt, expected);
    }

    {
        SCOPED_TRACE("Bad key-name.");
        args->set("key-name", Element::create(12345));
        // Force template instance.
        callout_handle->setArgument<ConstElementPtr>("command", command);
        ASSERT_NO_THROW(impl_->keyExpireHandler(*callout_handle));
        ConstElementPtr response;
        callout_handle->getArgument("response", response);
        ASSERT_TRUE(response);
        expected_txt = "'key-name' must be a string in the '";
        expected_txt += "{ \"arguments\": { ";
        expected_txt += "\"key-name\": 12345 }, ";
        expected_txt += "\"command\": \"gss-tsig-key-expire\" }' command";
        checkAnswer(response, expected_status, expected_txt, expected);
    }

    string name = "foo.bar.";
    args->set("key-name", Element::create(name));

    {
        SCOPED_TRACE("No key");
        // Force template instance.
        callout_handle->setArgument<ConstElementPtr>("command", command);
        ASSERT_NO_THROW(impl_->keyExpireHandler(*callout_handle));
        ConstElementPtr response;
        callout_handle->getArgument("response", response);
        ASSERT_TRUE(response);
        expected_status = CONTROL_RESULT_EMPTY;
        expected_txt = "GSS-TSIG key '" + name + "' not found";
        checkAnswer(response, expected_status, expected_txt, expected);
    }

    system_clock::time_point now = system_clock::now();
    system_clock::time_point tomorrow = now + 24 * HOUR;

    {
        SCOPED_TRACE("Matching in error key");
        ManagedKeyPtr key;
        ASSERT_NO_THROW(key.reset(new ManagedKey(name)));
        key->setStatus(ManagedKey::IN_ERROR);
        key->setInception(now);
        key->setExpire(tomorrow);
        key->setParentID("foo");
        impl_->keys_.insert(key);
        ASSERT_TRUE(impl_->findKey(name));
        EXPECT_EQ(key, impl_->findKey(name));
        // Force template instance.
        callout_handle->setArgument<ConstElementPtr>("command", command);
        ASSERT_NO_THROW(impl_->keyExpireHandler(*callout_handle));
        ConstElementPtr response;
        callout_handle->getArgument("response", response);
        ASSERT_TRUE(response);
        expected_status = CONTROL_RESULT_EMPTY;
        expected_txt = "GSS-TSIG key '" + name + "' can't be expired";
        checkAnswer(response, expected_status, expected_txt, expected);
        EXPECT_NE(ManagedKey::EXPIRED, key->getStatus());
        EXPECT_EQ(key, impl_->findKey(name));
    }

    {
        SCOPED_TRACE("Matching key");
        ManagedKeyPtr key;
        ASSERT_NO_THROW(key.reset(new ManagedKey(name)));
        key->setInception(now);
        key->setExpire(tomorrow);
        ASSERT_NE(ManagedKey::EXPIRED, key->getStatus());
        key->setParentID("foo");
        impl_->keys_.clear();
        impl_->keys_.insert(key);
        ASSERT_TRUE(impl_->findKey(name));
        EXPECT_EQ(key, impl_->findKey(name));
        // Force template instance.
        callout_handle->setArgument<ConstElementPtr>("command", command);
        ASSERT_NO_THROW(impl_->keyExpireHandler(*callout_handle));
        ConstElementPtr response;
        callout_handle->getArgument("response", response);
        ASSERT_TRUE(response);
        expected_status = CONTROL_RESULT_SUCCESS;
        expected_txt = "GSS-TSIG key '" + name + "' expired";
        checkAnswer(response, expected_status, expected_txt, expected);
        EXPECT_EQ(ManagedKey::EXPIRED, key->getStatus());
        EXPECT_EQ(key, impl_->findKey(name));
    }
}

/// @brief Tests gss-tsig-key-del command handler.
TEST_F(GssTsigImplTest, keyDelHandler) {
    ElementPtr command = Element::createMap();
    command->set("command", Element::create(string("gss-tsig-key-del")));
    CalloutHandlePtr callout_handle = HooksManager::createCalloutHandle();
    int expected_status = CONTROL_RESULT_ERROR;
    string expected_txt;
    ElementPtr expected;

    {
        SCOPED_TRACE("No arguments.");
        // Force template instance.
        callout_handle->setArgument<ConstElementPtr>("command", command);
        ASSERT_NO_THROW(impl_->keyDelHandler(*callout_handle));
        ConstElementPtr response;
        callout_handle->getArgument("response", response);
        ASSERT_TRUE(response);
        expected_txt = "arguments not found in the '";
        expected_txt += "{ \"command\": \"gss-tsig-key-del\" }' command";
        checkAnswer(response, expected_status, expected_txt, expected);
    }

    {
        SCOPED_TRACE("Arguments is not a map.");
        command->set("arguments", Element::createList());
        // Force template instance.
        callout_handle->setArgument<ConstElementPtr>("command", command);
        ASSERT_NO_THROW(impl_->keyDelHandler(*callout_handle));
        ConstElementPtr response;
        callout_handle->getArgument("response", response);
        ASSERT_TRUE(response);
        expected_txt = "arguments in the '{ \"arguments\": [  ], ";
        expected_txt += "\"command\": \"gss-tsig-key-del\" }' ";
        expected_txt += "command are not a map";
        checkAnswer(response, expected_status, expected_txt, expected);
    }

    ElementPtr args = Element::createMap();
    command->set("arguments", args);

    {
        SCOPED_TRACE("Empty arguments.");
        // Force template instance.
        callout_handle->setArgument<ConstElementPtr>("command", command);
        ASSERT_NO_THROW(impl_->keyDelHandler(*callout_handle));
        ConstElementPtr response;
        callout_handle->getArgument("response", response);
        ASSERT_TRUE(response);
        expected_txt = "'key-name' is mandatory for the '";
        expected_txt += "{ \"arguments\": {  }, ";
        expected_txt += "\"command\": \"gss-tsig-key-del\" }' command";
        checkAnswer(response, expected_status, expected_txt, expected);
    }

    {
        SCOPED_TRACE("Bad key-name.");
        args->set("key-name", Element::create(12345));
        // Force template instance.
        callout_handle->setArgument<ConstElementPtr>("command", command);
        ASSERT_NO_THROW(impl_->keyDelHandler(*callout_handle));
        ConstElementPtr response;
        callout_handle->getArgument("response", response);
        ASSERT_TRUE(response);
        expected_txt = "'key-name' must be a string in the '";
        expected_txt += "{ \"arguments\": { ";
        expected_txt += "\"key-name\": 12345 }, ";
        expected_txt += "\"command\": \"gss-tsig-key-del\" }' command";
        checkAnswer(response, expected_status, expected_txt, expected);
    }

    string name = "foo.bar.";
    args->set("key-name", Element::create(name));

    {
        SCOPED_TRACE("No key");
        // Force template instance.
        callout_handle->setArgument<ConstElementPtr>("command", command);
        ASSERT_NO_THROW(impl_->keyDelHandler(*callout_handle));
        ConstElementPtr response;
        callout_handle->getArgument("response", response);
        ASSERT_TRUE(response);
        expected_status = CONTROL_RESULT_EMPTY;
        expected_txt = "GSS-TSIG key '" + name + "' not found";
        checkAnswer(response, expected_status, expected_txt, expected);
    }

    {
        SCOPED_TRACE("Matching key");
        ManagedKeyPtr key;
        ASSERT_NO_THROW(key.reset(new ManagedKey(name)));
        system_clock::time_point now = system_clock::now();
        key->setInception(now);
        system_clock::time_point tomorrow = now + 24 * HOUR;
        key->setExpire(tomorrow);
        key->setParentID("foo");
        impl_->keys_.insert(key);
        ASSERT_TRUE(impl_->findKey(name));
        EXPECT_EQ(key, impl_->findKey(name));
        // Force template instance.
        callout_handle->setArgument<ConstElementPtr>("command", command);
        ASSERT_NO_THROW(impl_->keyDelHandler(*callout_handle));
        ConstElementPtr response;
        callout_handle->getArgument("response", response);
        ASSERT_TRUE(response);
        expected_status = CONTROL_RESULT_SUCCESS;
        expected_txt = "GSS-TSIG key '" + name + "' deleted";
        checkAnswer(response, expected_status, expected_txt, expected);
        EXPECT_FALSE(impl_->findKey(name));
    }
}

/// @brief Tests gss-tsig-purge command handler.
TEST_F(GssTsigImplTest, purgeHandler) {
    ElementPtr command = Element::createMap();
    command->set("command", Element::create(string("gss-tsig-purge")));
    CalloutHandlePtr callout_handle = HooksManager::createCalloutHandle();
    int expected_status = CONTROL_RESULT_ERROR;
    string expected_txt;
    ElementPtr expected;

    {
        SCOPED_TRACE("No arguments.");
        // Force template instance.
        callout_handle->setArgument<ConstElementPtr>("command", command);
        ASSERT_NO_THROW(impl_->purgeHandler(*callout_handle));
        ConstElementPtr response;
        callout_handle->getArgument("response", response);
        ASSERT_TRUE(response);
        expected_txt = "arguments not found in the '";
        expected_txt += "{ \"command\": \"gss-tsig-purge\" }' command";
        checkAnswer(response, expected_status, expected_txt, expected);
    }

    {
        SCOPED_TRACE("Arguments is not a map.");
        command->set("arguments", Element::createList());
        // Force template instance.
        callout_handle->setArgument<ConstElementPtr>("command", command);
        ASSERT_NO_THROW(impl_->purgeHandler(*callout_handle));
        ConstElementPtr response;
        callout_handle->getArgument("response", response);
        ASSERT_TRUE(response);
        expected_txt = "arguments in the '{ \"arguments\": [  ], ";
        expected_txt += "\"command\": \"gss-tsig-purge\" }' ";
        expected_txt += "command are not a map";
        checkAnswer(response, expected_status, expected_txt, expected);
    }

    ElementPtr args = Element::createMap();
    command->set("arguments", args);

    {
        SCOPED_TRACE("Empty arguments.");
        // Force template instance.
        callout_handle->setArgument<ConstElementPtr>("command", command);
        ASSERT_NO_THROW(impl_->purgeHandler(*callout_handle));
        ConstElementPtr response;
        callout_handle->getArgument("response", response);
        ASSERT_TRUE(response);
        expected_txt = "'server-id' is mandatory for the '";
        expected_txt += "{ \"arguments\": {  }, ";
        expected_txt += "\"command\": \"gss-tsig-purge\" }' command";
        checkAnswer(response, expected_status, expected_txt, expected);
    }

    {
        SCOPED_TRACE("Bad server-id.");
        args->set("server-id", Element::create(12345));
        // Force template instance.
        callout_handle->setArgument<ConstElementPtr>("command", command);
        ASSERT_NO_THROW(impl_->purgeHandler(*callout_handle));
        ConstElementPtr response;
        callout_handle->getArgument("response", response);
        ASSERT_TRUE(response);
        expected_txt = "'server-id' must be a string in the '";
        expected_txt += "{ \"arguments\": { ";
        expected_txt += "\"server-id\": 12345 }, ";
        expected_txt += "\"command\": \"gss-tsig-purge\" }' command";
        checkAnswer(response, expected_status, expected_txt, expected);
    }

    {
        SCOPED_TRACE("No key");
        args->set("server-id", Element::create(string("foo")));
        // Force template instance.
        callout_handle->setArgument<ConstElementPtr>("command", command);
        ASSERT_NO_THROW(impl_->purgeHandler(*callout_handle));
        ConstElementPtr response;
        callout_handle->getArgument("response", response);
        ASSERT_TRUE(response);
        expected_status = CONTROL_RESULT_EMPTY;
        expected_txt = "0 purged keys for GSS-TSIG server[foo]";
        checkAnswer(response, expected_status, expected_txt, expected);
    }

    {
        SCOPED_TRACE("2 servers, 3 keys and one candidate.");
        const string& id("foo");
        args->set("server-id", Element::create(id));
        const string& name1("foo1.bar.");
        ManagedKeyPtr key1;
        ASSERT_NO_THROW(key1.reset(new ManagedKey(name1)));
        system_clock::time_point now = system_clock::now();
        key1->setInception(now);
        system_clock::time_point tomorrow = now + 24 * HOUR;
        key1->setExpire(tomorrow);
        key1->setParentID(id);
        impl_->keys_.insert(key1);
        ASSERT_TRUE(impl_->findKey(name1));
        EXPECT_EQ(key1, impl_->findKey(name1));

        const string& name2("foo2.bar.");
        ManagedKeyPtr key2;
        ASSERT_NO_THROW(key2.reset(new ManagedKey(name2)));
        key2->setInception(now);
        key2->setExpire(tomorrow);
        key2->setParentID(id);
        key2->setStatus(ManagedKey::IN_ERROR);
        impl_->keys_.insert(key2);
        ASSERT_TRUE(impl_->findKey(name2));
        EXPECT_EQ(key2, impl_->findKey(name2));

        const string& name3("foo3.bar.");
        ManagedKeyPtr key3;
        ASSERT_NO_THROW(key3.reset(new ManagedKey(name3)));
        key3->setInception(now);
        key3->setExpire(tomorrow);
        key3->setParentID("bar");
        key3->setStatus(ManagedKey::EXPIRED);
        impl_->keys_.insert(key3);
        ASSERT_TRUE(impl_->findKey(name3));
        EXPECT_EQ(key3, impl_->findKey(name3));

        // Force template instance.
        callout_handle->setArgument<ConstElementPtr>("command", command);
        ASSERT_NO_THROW(impl_->purgeHandler(*callout_handle));
        ConstElementPtr response;
        callout_handle->getArgument("response", response);
        ASSERT_TRUE(response);
        expected_status = CONTROL_RESULT_SUCCESS;
        expected_txt = "1 purged keys for GSS-TSIG server[foo]";
        checkAnswer(response, expected_status, expected_txt, expected);
        ASSERT_TRUE(impl_->findKey(name1));
        EXPECT_EQ(key1, impl_->findKey(name1));
        EXPECT_FALSE(impl_->findKey(name2));
        ASSERT_TRUE(impl_->findKey(name3));
        EXPECT_EQ(key3, impl_->findKey(name3));
        EXPECT_EQ(2, impl_->keys_.size());
    }
}

/// @brief Tests gss-tsig-purge-all command handler.
TEST_F(GssTsigImplTest, purgeAllHandler) {
    ElementPtr command = Element::createMap();
    command->set("command", Element::create(string("gss-tsig-purge-all")));
    CalloutHandlePtr callout_handle = HooksManager::createCalloutHandle();
    int expected_status = CONTROL_RESULT_ERROR;
    string expected_txt;
    ElementPtr expected;

    {
        SCOPED_TRACE("No key");
        // Force template instance.
        callout_handle->setArgument<ConstElementPtr>("command", command);
        ASSERT_NO_THROW(impl_->purgeAllHandler(*callout_handle));
        ConstElementPtr response;
        callout_handle->getArgument("response", response);
        ASSERT_TRUE(response);
        expected_status = CONTROL_RESULT_EMPTY;
        expected_txt = "0 purged GSS-TSIG keys";
        checkAnswer(response, expected_status, expected_txt, expected);
    }

    {
        SCOPED_TRACE("2 servers, 3 keys and one candidate.");
        const string& name1("foo1.bar.");
        ManagedKeyPtr key1;
        ASSERT_NO_THROW(key1.reset(new ManagedKey(name1)));
        system_clock::time_point now = system_clock::now();
        key1->setInception(now);
        system_clock::time_point tomorrow = now + 24 * HOUR;
        key1->setExpire(tomorrow);
        key1->setParentID("foo");
        impl_->keys_.insert(key1);
        ASSERT_TRUE(impl_->findKey(name1));
        EXPECT_EQ(key1, impl_->findKey(name1));

        const string& name2("foo2.bar.");
        ManagedKeyPtr key2;
        ASSERT_NO_THROW(key2.reset(new ManagedKey(name2)));
        key2->setInception(now);
        key2->setExpire(tomorrow);
        key2->setParentID("foo");
        key2->setStatus(ManagedKey::IN_ERROR);
        impl_->keys_.insert(key2);
        ASSERT_TRUE(impl_->findKey(name2));
        EXPECT_EQ(key2, impl_->findKey(name2));

        const string& name3("foo3.bar.");
        ManagedKeyPtr key3;
        ASSERT_NO_THROW(key3.reset(new ManagedKey(name3)));
        key3->setInception(now);
        key3->setExpire(tomorrow);
        key3->setParentID("bar");
        key3->setStatus(ManagedKey::EXPIRED);
        impl_->keys_.insert(key3);
        ASSERT_TRUE(impl_->findKey(name3));
        EXPECT_EQ(key3, impl_->findKey(name3));

        // Force template instance.
        callout_handle->setArgument<ConstElementPtr>("command", command);
        ASSERT_NO_THROW(impl_->purgeAllHandler(*callout_handle));
        ConstElementPtr response;
        callout_handle->getArgument("response", response);
        ASSERT_TRUE(response);
        expected_status = CONTROL_RESULT_SUCCESS;
        expected_txt = "2 purged GSS-TSIG keys";
        checkAnswer(response, expected_status, expected_txt, expected);
        ASSERT_TRUE(impl_->findKey(name1));
        EXPECT_EQ(key1, impl_->findKey(name1));
        EXPECT_FALSE(impl_->findKey(name2));
        EXPECT_FALSE(impl_->findKey(name3));
        EXPECT_EQ(1, impl_->keys_.size());
    }
}

/// @brief Tests gss-tsig-rekey command handler.
TEST_F(GssTsigImplTest, rekeyHandler) {
    ElementPtr command = Element::createMap();
    command->set("command", Element::create(string("gss-tsig-rekey")));
    CalloutHandlePtr callout_handle = HooksManager::createCalloutHandle();
    int expected_status = CONTROL_RESULT_ERROR;
    string expected_txt;
    ElementPtr expected;

    {
        SCOPED_TRACE("No arguments.");
        // Force template instance.
        callout_handle->setArgument<ConstElementPtr>("command", command);
        ASSERT_NO_THROW(impl_->rekeyHandler(*callout_handle));
        ConstElementPtr response;
        callout_handle->getArgument("response", response);
        ASSERT_TRUE(response);
        expected_txt = "arguments not found in the '";
        expected_txt += "{ \"command\": \"gss-tsig-rekey\" }' command";
        checkAnswer(response, expected_status, expected_txt, expected);
    }

    {
        SCOPED_TRACE("Arguments is not a map.");
        command->set("arguments", Element::createList());
        // Force template instance.
        callout_handle->setArgument<ConstElementPtr>("command", command);
        ASSERT_NO_THROW(impl_->rekeyHandler(*callout_handle));
        ConstElementPtr response;
        callout_handle->getArgument("response", response);
        ASSERT_TRUE(response);
        expected_txt = "arguments in the '{ \"arguments\": [  ], ";
        expected_txt += "\"command\": \"gss-tsig-rekey\" }' ";
        expected_txt += "command are not a map";
        checkAnswer(response, expected_status, expected_txt, expected);
    }

    ElementPtr args = Element::createMap();
    command->set("arguments", args);

    {
        SCOPED_TRACE("Empty arguments.");
        // Force template instance.
        callout_handle->setArgument<ConstElementPtr>("command", command);
        ASSERT_NO_THROW(impl_->rekeyHandler(*callout_handle));
        ConstElementPtr response;
        callout_handle->getArgument("response", response);
        ASSERT_TRUE(response);
        expected_txt = "'server-id' is mandatory for the '";
        expected_txt += "{ \"arguments\": {  }, ";
        expected_txt += "\"command\": \"gss-tsig-rekey\" }' command";
        checkAnswer(response, expected_status, expected_txt, expected);
    }

    {
        SCOPED_TRACE("Bad server-id.");
        args->set("server-id", Element::create(12345));
        // Force template instance.
        callout_handle->setArgument<ConstElementPtr>("command", command);
        ASSERT_NO_THROW(impl_->rekeyHandler(*callout_handle));
        ConstElementPtr response;
        callout_handle->getArgument("response", response);
        ASSERT_TRUE(response);
        expected_txt = "'server-id' must be a string in the '";
        expected_txt += "{ \"arguments\": { ";
        expected_txt += "\"server-id\": 12345 }, ";
        expected_txt += "\"command\": \"gss-tsig-rekey\" }' command";
        checkAnswer(response, expected_status, expected_txt, expected);
    }

    {
        SCOPED_TRACE("No server");
        args->set("server-id", Element::create(string("foo")));
        // Force template instance.
        callout_handle->setArgument<ConstElementPtr>("command", command);
        ASSERT_NO_THROW(impl_->rekeyHandler(*callout_handle));
        ConstElementPtr response;
        callout_handle->getArgument("response", response);
        ASSERT_TRUE(response);
        expected_status = CONTROL_RESULT_EMPTY;
        expected_txt = "GSS-TSIG server[foo] not found";
        checkAnswer(response, expected_status, expected_txt, expected);
    }

    {
        SCOPED_TRACE("Matching server");
        DnsServerPtr srv;
        const string& id("foo");
        set<string> domains;
        IOAddress addr("192.1.2.3");
        ASSERT_NO_THROW(srv.reset(new DnsServer(id, domains, addr)));
        ASSERT_TRUE(srv);
        srv->setServerPrincipal("DNS/example.nil@EXAMPLE.NIL");
        impl_->cfg_.addServer(srv);
        args->set("server-id", Element::create(id));
        // Force template instance.
        callout_handle->setArgument<ConstElementPtr>("command", command);
        ASSERT_NO_THROW(impl_->rekeyHandler(*callout_handle));
        ConstElementPtr response;
        callout_handle->getArgument("response", response);
        ASSERT_TRUE(response);
        expected_status = CONTROL_RESULT_SUCCESS;
        expected_txt = "GSS-TSIG server[" + id + "] rekeyed";
        checkAnswer(response, expected_status, expected_txt, expected);
        EXPECT_EQ(impl_->keys_.size(), 1);
        impl_->keys_.clear();
    }
}

/// @brief Tests gss-tsig-rekey-all command handler.
TEST_F(GssTsigImplTest, rekeyAllHandler) {
    ElementPtr command = Element::createMap();
    command->set("command", Element::create(string("gss-tsig-rekey-all")));
    CalloutHandlePtr callout_handle = HooksManager::createCalloutHandle();
    int expected_status = CONTROL_RESULT_SUCCESS;
    string expected_txt = "rekeyed";
    ElementPtr expected;

    {
        SCOPED_TRACE("Empty config.");
        callout_handle->setArgument("command", command);
        ASSERT_NO_THROW(impl_->rekeyAllHandler(*callout_handle));
        ConstElementPtr response;
        callout_handle->getArgument("response", response);
        ASSERT_TRUE(response);
        checkAnswer(response, expected_status, expected_txt, expected);
        io_service_->poll();
        EXPECT_EQ(impl_->keys_.size(), 0);
        impl_->keys_.clear();
    }

    {
        SCOPED_TRACE("One empty server.");
        DnsServerPtr srv;
        const string& id("foo");
        set<string> domains;
        IOAddress addr("192.1.2.3");
        ASSERT_NO_THROW(srv.reset(new DnsServer(id, domains, addr)));
        ASSERT_TRUE(srv);
        srv->setServerPrincipal("DNS/blu.example.nil@EXAMPLE.NIL");
        impl_->cfg_.addServer(srv);
        callout_handle->setArgument("command", command);
        ASSERT_NO_THROW(impl_->rekeyAllHandler(*callout_handle));
        ConstElementPtr response;
        callout_handle->getArgument("response", response);
        ASSERT_TRUE(response);
        checkAnswer(response, expected_status, expected_txt, expected);
        io_service_->poll();
        EXPECT_EQ(impl_->keys_.size(), 1);
        for (auto const& key : impl_->keys_) {
            key->getTKeyExchange().reset();
        }
        impl_->keys_.clear();
    }

    {
        SCOPED_TRACE("Two servers, second with a key.");
        DnsServerPtr srv;
        const string& id("bar");
        set<string> domains = { "foo" };
        IOAddress addr("192.1.2.4");
        ASSERT_NO_THROW(srv.reset(new DnsServer(id, domains, addr)));
        ASSERT_TRUE(srv);
        srv->setServerPrincipal("DNS/blu.example.nil@EXAMPLE.NIL");
        impl_->cfg_.addServer(srv);
        ManagedKeyPtr key;
        string name = "1234.sig-foo.example.com.";
        ASSERT_NO_THROW(key.reset(new ManagedKey(name)));
        system_clock::time_point now = system_clock::now();
        key->setInception(now);
        system_clock::time_point tomorrow = now + 24 * HOUR;
        key->setExpire(tomorrow);
        key->setParentID(id);
        impl_->keys_.insert(key);
        callout_handle->setArgument("command", command);
        ASSERT_NO_THROW(impl_->rekeyAllHandler(*callout_handle));
        ConstElementPtr response;
        callout_handle->getArgument("response", response);
        ASSERT_TRUE(response);
        checkAnswer(response, expected_status, expected_txt, expected);
        io_service_->poll();
        EXPECT_EQ(impl_->keys_.size(), 3);
        for (auto const& temp_key : impl_->keys_) {
            temp_key->getTKeyExchange().reset();
        }
        impl_->keys_.clear();
    }
}

/// @brief Tests renew and retry timer with no keys.
TEST_F(GssTsigImplTest, timersNoKeys) {
    // t = t0
    expected_keys_ = 0;
    startTimer(1500, true);
    io_service_->run();
    // t = t0 + 1.5s
    // No TKEY exchange has been initialized and no key has been created.
    checkKeys(0, 0, 0, 0);
}

/// @brief Tests retry timer.
TEST_F(GssTsigImplTest, retryTimer) {
    DnsServerPtr srv;
    ASSERT_NO_THROW(srv.reset(new DnsServer("foo", {}, IOAddress(TEST_ADDRESS),
                                            TEST_PORT)));
    ASSERT_TRUE(srv);
    srv->setServerPrincipal("DNS/blu.example.nil@EXAMPLE.NIL");
    srv->setKeyProto(IOFetch::Protocol::UDP);
    srv->setKeyLifetime(30);
    srv->setRekeyInterval(20);
    srv->setRetryInterval(1);
    // t = t0
    // Adding a server should initialize a new TKEY exchange and create a new
    // key.
    expected_keys_ = 1;
    io_service_->restart();
    startTimer(500, true, srv);
    io_service_->run();
    // t = t0 + 0.5s
    // The new TKEY exchange has been initialized and has not yet timeout and a
    // new key has been created.
    checkKeys(1, 0, 0, 0);
    ASSERT_TRUE(go_on_);
    io_service_->restart();
    // After the next 1s, the TKEY exchange has not yet timeout and no new key
    // should be created.
    startTimer(1000);
    io_service_->run();
    // t = t0 + 1.5s
    // The TKEY exchange has not yet timeout.
    checkKeys(1, 0, 0, 0);
    ASSERT_TRUE(go_on_);
    io_service_->restart();
    // After the next 1s, the TKEY exchange has not yet timeout and no new key
    // should be created.
    startTimer(1000);
    io_service_->run();
    // t = t0 + 2.5s
    // The TKEY exchange has not yet timeout.
    checkKeys(1, 0, 0, 0);
    ASSERT_TRUE(go_on_);
    io_service_->restart();
    // Starting the dummy DNS server will result in a successful TKEY exchange.
    dns_server_.reset(new DummyDNSServer(io_service_, true, true, true, true, false));
    dns_server_->start();
    expected_keys_ = 2;
    // After the next 2s, the TKEY exchange has timeout and the retry timer
    // should initialize a new TKEY exchange and create a new key.
    startTimer(2000);
    io_service_->run();
    // t = t0 + 4.5s
    // The TKEY exchange has timeout and the new TKEY exchange has been
    // initialized and has ended and a new key has been created.
    checkKeys(0, 1, 0, 1);
    ASSERT_TRUE(go_on_);
    io_service_->restart();
    // After the next 1s, no new key should be created.
    startTimer(1000);
    io_service_->run();
    // t = t0 + 5.5s
    // No new key has been created.
    checkKeys(0, 1, 0, 1);
    ASSERT_TRUE(go_on_);
    io_service_->restart();
    // After the next 1s, no new key should be created.
    startTimer(1000);
    io_service_->run();
    // t = t0 + 6.5s
    // No new key has been created.
    checkKeys(0, 1, 0, 1);
    ASSERT_TRUE(go_on_);
}

/// @brief Tests rekey timer.
TEST_F(GssTsigImplTest, rekeyTimer) {
    DnsServerPtr srv;
    ASSERT_NO_THROW(srv.reset(new DnsServer("foo", {}, IOAddress(TEST_ADDRESS),
                                            TEST_PORT)));
    ASSERT_TRUE(srv);
    srv->setServerPrincipal("DNS/blu.example.nil@EXAMPLE.NIL");
    srv->setKeyProto(IOFetch::Protocol::UDP);
    srv->setKeyLifetime(10);
    srv->setRekeyInterval(6);
    srv->setRetryInterval(2);
    dns_server_.reset(new DummyDNSServer(io_service_, true, true, true, true, false));
    dns_server_->start();
    // t = t0
    // Adding a server should initialize a new TKEY exchange and create a new
    // key.
    expected_keys_ = 1;
    io_service_->restart();
    startTimer(500, true, srv);
    io_service_->run();
    // t = t0 + 0.5s
    // The new TKEY exchange has been initialized and has ended and a new key
    // has been created.
    checkKeys(0, 1, 0, 0);
    ASSERT_TRUE(go_on_);
    io_service_->restart();
    // After the next 2s, no new key should be created.
    startTimer(2000);
    io_service_->run();
    // t = t0 + 2.5s
    // No new key has been created.
    checkKeys(0, 1, 0, 0);
    ASSERT_TRUE(go_on_);
    io_service_->restart();
    // After the next 2s, no new key should be created.
    startTimer(2000);
    io_service_->run();
    // t = t0 + 4.5s
    // No new key has been created.
    checkKeys(0, 1, 0, 0);
    ASSERT_TRUE(go_on_);
    io_service_->restart();
    expected_keys_ = 2;
    // After the next 2s, the key lifetime will almost have expired, so the
    // renew timer should initialize a new TKEY exchange and create a new key.
    startTimer(2000);
    io_service_->run();
    // t = t0 + 6.5s
    // The new TKEY exchange has been initialized and has ended and a new key
    // has been created.
    checkKeys(0, 2, 0, 0);
    ASSERT_TRUE(go_on_);
    io_service_->restart();
    // After the next 2s, no new key should be created.
    startTimer(2000);
    io_service_->run();
    // t = t0 + 8.5s
    // No new key has been created.
    checkKeys(0, 2, 0, 0);
    ASSERT_TRUE(go_on_);
    io_service_->restart();
    // After the next 2s, no new key should be created.
    startTimer(2000);
    io_service_->run();
    // t = t0 + 10.5s
    // No new key has been created.
    checkKeys(0, 2, 0, 0);
    ASSERT_TRUE(go_on_);
    io_service_->restart();
    expected_keys_ = 3;
    // After the next 2s, the initial key has expired and a new key should be
    // created.
    startTimer(2000);
    io_service_->run();
    // t = t0 + 12.5s
    // The initial key has expired and a new key has been created.
    checkKeys(0, 2, 1, 0);
    ASSERT_TRUE(go_on_);
}

/// @brief Tests purgeKeys timer handler.
TEST_F(GssTsigImplTest, purgeKeys) {
    impl_->cfg_.setMaxKeyLifetime(3600);
    const string& name1("foo1.bar.");
    ManagedKeyPtr key1;
    ASSERT_NO_THROW(key1.reset(new ManagedKey(name1)));
    system_clock::time_point now = system_clock::now();
    system_clock::time_point now_plus1 = now + HOUR;
    key1->setInception(now);
    key1->setExpire(now_plus1);
    key1->setParentID("foo");
    impl_->keys_.insert(key1);
    ASSERT_TRUE(impl_->findKey(name1));
    EXPECT_EQ(key1, impl_->findKey(name1));

    const string& name2("foo2.bar.");
    ManagedKeyPtr key2;
    ASSERT_NO_THROW(key2.reset(new ManagedKey(name2)));
    system_clock::time_point now_minus24 = now - 24 * HOUR;
    system_clock::time_point now_minus23 = now_minus24 + HOUR;
    key2->setInception(now_minus24);
    key2->setExpire(now_minus23);
    key2->setParentID("foo");
    impl_->keys_.insert(key2);
    ASSERT_TRUE(impl_->findKey(name2));
    EXPECT_EQ(key2, impl_->findKey(name2));

    const string& name3("foo3.bar.");
    ManagedKeyPtr key3;
    ASSERT_NO_THROW(key3.reset(new ManagedKey(name3)));
    key3->setInception(now_minus24);
    key3->setExpire(now_minus23);
    key3->setParentID("bar");
    impl_->keys_.insert(key3);
    ASSERT_TRUE(impl_->findKey(name3));
    EXPECT_EQ(key3, impl_->findKey(name3));

    const string& name4("foo4.bar.");
    ManagedKeyPtr key4;
    ASSERT_NO_THROW(key4.reset(new ManagedKey(name4)));
    system_clock::time_point now_minus4 = now - 4 * HOUR;
    system_clock::time_point now_minus3 = now_minus4 + HOUR;
    key4->setInception(now_minus4);
    key4->setExpire(now_minus3);
    key4->setParentID("foo");
    impl_->keys_.insert(key4);
    ASSERT_TRUE(impl_->findKey(name4));
    EXPECT_EQ(key4, impl_->findKey(name4));

    const string& name5("foo5.bar.");
    ManagedKeyPtr key5;
    ASSERT_NO_THROW(key5.reset(new ManagedKey(name5)));
    key5->setInception(now_minus4 + SECOND);
    key5->setExpire(now_minus3 + SECOND);
    key5->setParentID("foo");
    impl_->keys_.insert(key5);
    ASSERT_TRUE(impl_->findKey(name5));
    EXPECT_EQ(key5, impl_->findKey(name5));

    EXPECT_EQ(5, impl_->keys_.size());
    ASSERT_NO_THROW(impl_->purgeKeys());
    EXPECT_EQ(2, impl_->keys_.size());
    EXPECT_EQ(key1, impl_->findKey(name1));
    EXPECT_EQ(key5, impl_->findKey(name5));
}

}
