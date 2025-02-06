// Copyright (C) 2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <lease_cmds.h>
#include <hooks/hooks_manager.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/lease_mgr_factory.h>
#include <exceptions/exceptions.h>
#include <cc/data.h>
#include <dhcp/dhcp6.h>
#include <dhcp/pkt4.h>
#include <dhcp/pkt6.h>
#include <dhcpsrv/lease.h>

#include <testutils/gtest_utils.h>
#include <testutils/user_context_utils.h>
#include <testutils/multi_threading_utils.h>

#include <gtest/gtest.h>

using namespace std;
using namespace isc;
using namespace isc::dhcp;
using namespace isc::data;
using namespace isc::test;
using namespace isc::asiolink;
using namespace isc::hooks;

using namespace isc::lease_cmds;

namespace {

#define SCOPED_LINE(line) \
    std::stringstream ss; \
    ss << "Scenario at line: " << line; \
    SCOPED_TRACE(ss.str());

/// @brief Test BindingVariable valid construction scenarios.
TEST(BindingVariableTest, validConstructor) {
    BindingVariablePtr bv;

    struct Scenario {
        uint32_t line_;
        std::string name_;
        std::string expression_str_;
        BindingVariable::Source source_;
        uint32_t family_;
    };

    std::string valid_v4_exp = "pkt4.mac";
    std::string valid_v6_exp = "pkt6.transid";

    std::list<Scenario> scenarios = {
        {
           __LINE__,  "my-var", valid_v4_exp, BindingVariable::QUERY ,AF_INET
        },
        {
           __LINE__,  "my-var", valid_v4_exp, BindingVariable::RESPONSE ,AF_INET
        },
        {
           __LINE__,  "my-var", valid_v6_exp, BindingVariable::QUERY, AF_INET6
        },
        {
           __LINE__,  "my-var", valid_v6_exp, BindingVariable::RESPONSE, AF_INET6
        },
        {
           __LINE__,  "my-var", "'woo hoo'", BindingVariable::RESPONSE, AF_INET6
        }
    };

    for (auto const& scenario : scenarios) {
        SCOPED_LINE(scenario.line_);
        ASSERT_NO_THROW_LOG(bv.reset(new BindingVariable(scenario.name_,
                                                         scenario.expression_str_,
                                                         scenario.source_,
                                                         scenario.family_)));
        ASSERT_TRUE(bv);
        EXPECT_EQ(bv->getName(), scenario.name_);
        EXPECT_EQ(bv->getExpressionStr(), scenario.expression_str_);
        ASSERT_TRUE(bv->getExpression());
        EXPECT_EQ(bv->getSource(), scenario.source_);
        EXPECT_EQ(bv->getFamily(), scenario.family_);
    }
}

/// @brief Test BindingVariable invalid construction scenarios.
TEST(BindingVariableTest, invalidConstructor) {
    BindingVariablePtr bv;

    struct Scenario {
        uint32_t line_;
        std::string name_;
        std::string expression_str_;
        uint32_t family_;
        std::string expected_error_;
    };

    std::string valid_v4_exp = "pkt4.mac";
    std::string valid_v6_exp = "pkt6.transid";

    std::list<Scenario> scenarios = {
        {
           __LINE__,  "", valid_v4_exp, AF_INET,
           "BindingVariable - name cannot be empty"
        },
        {
           __LINE__,  "my-var", "", AF_INET,
           "BindingVariable - 'my-var' expression_str cannot be empty"
        },
        {
           __LINE__,  "my-var", "bogus + stuff", AF_INET,
           "BindingVariable - 'my-var', error parsing expression: "
           "'bogus + stuff' : <string>:1.1: Invalid character: b"
        },
        {
           __LINE__,  "my-var", valid_v4_exp, 99,
           "BindingVariable - 'my-var', invalid family: 99"
        },
        {
           __LINE__,  "my-var", valid_v4_exp, AF_INET6,
           "BindingVariable - 'my-var', error parsing expression: "
           "'pkt4.mac' : <string>:1.1-4: pkt4 can only be used in DHCPv4."
        },
        {
           __LINE__,  "my-var", valid_v6_exp, AF_INET,
           "BindingVariable - 'my-var', error parsing expression: "
           "'pkt6.transid' : <string>:1.1-4: pkt6 can only be used in DHCPv6."
        }
    };

    for (auto const& scenario : scenarios) {
        SCOPED_LINE(scenario.line_);
        ASSERT_THROW_MSG(bv.reset(new BindingVariable(scenario.name_,
                                                      scenario.expression_str_,
                                                      BindingVariable::QUERY,
                                                      scenario.family_)),
                        BadValue, scenario.expected_error_);
    }
}

/// @brief Tests BindingVariable::toElement().
TEST(BindingVariableTest, toElement) {
    BindingVariablePtr bv;

    ASSERT_NO_THROW_LOG(bv.reset(new BindingVariable("myvar",
                                                     "pkt4.mac",
                                                     BindingVariable::QUERY,
                                                     AF_INET)));
    ASSERT_TRUE(bv);
    ElementPtr elem;

    ASSERT_NO_THROW_LOG(elem = bv->toElement());
    std::stringstream ss;
    elem->toJSON(ss);
    std::string expected_json = "{ \"expression\": \"pkt4.mac\","
                                " \"name\": \"myvar\", \"source\": \"query\" }";
    EXPECT_EQ(ss.str(), expected_json);
}

/// @brief Checks BindingVariable::parse with valid scenarios.
TEST(BindingVariableTest, validParsing) {
    struct Scenario {
        uint32_t line_;
        std::string config_;
        uint32_t family_;
        std::string expected_json_;
    };

    std::list<Scenario> scenarios = {
        {
           __LINE__,
           R"({ "name": "one", "expression" : "pkt4.mac", "source": "query"})",
            AF_INET,
           "{ \"expression\": \"pkt4.mac\", \"name\": \"one\", \"source\": \"query\" }"
        },
        {
           __LINE__,
           R"({ "name": "two", "expression" : "pkt4.mac", "source": "response"})",
            AF_INET,
           "{ \"expression\": \"pkt4.mac\", \"name\": \"two\", \"source\": \"response\" }"
        },
        {
           __LINE__,
           R"({ "name": "three", "expression" : "pkt6.transid", "source": "query"})",
            AF_INET6,
           "{ \"expression\": \"pkt6.transid\", \"name\": \"three\", \"source\": \"query\" }"
        },
        {
           __LINE__,
           R"({ "name": "four", "expression" : "pkt6.transid", "source": "response"})",
            AF_INET6,
           "{ \"expression\": \"pkt6.transid\", \"name\": \"four\", \"source\": \"response\" }"
        }
    };

    for (auto const& scenario : scenarios) {
        SCOPED_LINE(scenario.line_);
        BindingVariablePtr var;
        ElementPtr config;
        ASSERT_NO_THROW_LOG(config = Element::fromJSON(scenario.config_));
        ASSERT_NO_THROW_LOG(var = BindingVariable::parse(config, scenario.family_));
        ASSERT_TRUE(var);
        std::stringstream js;
        var->toElement()->toJSON(js);
        EXPECT_EQ(js.str(), scenario.expected_json_);
    }
}

/// @brief Checks BindingVariable::parse with invalid scenarios.
TEST(BindingVariableTest, invalidParsing) {
    struct Scenario {
        uint32_t line_;
        std::string config_;
        uint32_t family_;
        std::string expected_error_;
    };

    std::list<Scenario> scenarios = {
        {
            __LINE__,
            R"({ "name": "", "expression" : "pkt4.mac", "source": "query"})",
            AF_INET,
            "invalid config: BindingVariable - name cannot be empty"
        },
        {
            __LINE__,
            R"({ "name": "myvar", "expression" : "", "source": "response"})",
            AF_INET,
            "invalid config: BindingVariable - 'myvar' expression_str cannot be empty"
        },
        {
            __LINE__,
            R"({ "name": "myvar", "expression" : "pkt5.bogus", "source": "query"})",
            AF_INET,
            "invalid config: BindingVariable - 'myvar', error parsing expression:"
            " 'pkt5.bogus' : <string>:1.4: syntax error, unexpected integer, expecting ."
        },
        {
            __LINE__,
            R"({ "name": "myvar", "expression" : "pkt4.mac", "source": "BOGUS"})",
            AF_INET,
            "invalid config: invalid source 'BOGUS', must be either 'query' or 'response'"
        },
        {
            __LINE__,
            R"({ "name": "myvar", "expression" : "pkt4.mac", "source": "query", "bogus" : "foo" })",
            AF_INET,
            "spurious 'bogus' parameter"
        }
    };

    for (auto const& scenario : scenarios) {
        SCOPED_LINE(scenario.line_);
        ElementPtr config;
        ASSERT_NO_THROW_LOG(config = Element::fromJSON(scenario.config_));
        ASSERT_THROW_MSG(BindingVariable::parse(config, scenario.family_),
                         DhcpConfigError, scenario.expected_error_);
    }
}

/// @brief Verifies basic operation of the cache including
/// construction, all getters and cache clearing.
TEST(BindingVariableCacheTest, basics) {
    // Save start time of test.  We use seconds because that's that
    // BaseStampedElement uses.
    auto ref_time = boost::posix_time::second_clock::local_time();

    // Create a new cache.
    BindingVariableCachePtr cache(new BindingVariableCache());

    // Verify last flush time has been set to approximately now.
    EXPECT_GE(cache->getLastFlushTime(), ref_time);
    ref_time = cache->getLastFlushTime();

    // Ensure getters return empty lists or pointers without harm.
    BindingVariableListPtr var_list;
    ASSERT_NO_THROW_LOG(var_list = cache->getAll());
    ASSERT_TRUE(var_list);
    EXPECT_EQ(var_list->size(), 0);

    BindingVariablePtr var;
    ASSERT_NO_THROW_LOG(var = cache->getByName("foo"));
    ASSERT_FALSE(var);

    ASSERT_NO_THROW_LOG(var_list = cache->getBySource(BindingVariable::QUERY));
    ASSERT_TRUE(var_list);
    EXPECT_EQ(var_list->size(), 0);

    ASSERT_NO_THROW_LOG(var_list = cache->getBySource(BindingVariable::RESPONSE));
    ASSERT_TRUE(var_list);
    EXPECT_EQ(var_list->size(), 0);

    // Add four variables.
    std::string valid_v6_exp = "pkt6.transid";
    BindingVariableList ref_list;
    ref_list.push_back(BindingVariablePtr(new BindingVariable("one", valid_v6_exp,
                                                              BindingVariable::QUERY,
                                                              AF_INET6)));

    ref_list.push_back(BindingVariablePtr(new BindingVariable("two", valid_v6_exp,
                                                              BindingVariable::RESPONSE,
                                                              AF_INET6)));

    ref_list.push_back(BindingVariablePtr(new BindingVariable("three", valid_v6_exp,
                                                              BindingVariable::RESPONSE,
                                                              AF_INET6)));

    ref_list.push_back(BindingVariablePtr(new BindingVariable("four", valid_v6_exp,
                                                              BindingVariable::QUERY,
                                                              AF_INET6)));

    for (auto const& ref_iter : ref_list) {
        ASSERT_NO_THROW_LOG(cache->add(ref_iter));
    }

    // Make sure getAll() returns all four in order added.
    ASSERT_NO_THROW_LOG(var_list = cache->getAll());
    ASSERT_TRUE(var_list);
    EXPECT_EQ(var_list->size(), 4);

    auto var_iter = var_list->begin();
    for (auto const& ref_iter : ref_list) {
        EXPECT_EQ((*var_iter)->getName(), ref_iter->getName());
        EXPECT_EQ((*var_iter)->getSource(), ref_iter->getSource());
        ++var_iter;
    }

    // Make sure getByName() can return each one.
    for (auto const& ref_iter : ref_list) {
        ASSERT_NO_THROW_LOG(var = cache->getByName(ref_iter->getName()));
        ASSERT_TRUE(var);
        EXPECT_EQ(var->getName(), ref_iter->getName());
    }

    // Make sure getBySource() works for QUERY.
    ASSERT_NO_THROW_LOG(var_list = cache->getBySource(BindingVariable::QUERY));
    ASSERT_TRUE(var_list);
    ASSERT_EQ(var_list->size(), 2);

    var_iter = var_list->begin();
    for (auto const& ref_iter : ref_list) {
        if (ref_iter->getSource() == BindingVariable::QUERY) {
            EXPECT_EQ((*var_iter)->getName(), ref_iter->getName());
            ++var_iter;
        }
    }

    // Make sure getBySource() works for RESPONSE.
    ASSERT_NO_THROW_LOG(var_list = cache->getBySource(BindingVariable::RESPONSE));
    ASSERT_TRUE(var_list);
    ASSERT_EQ(var_list->size(), 2);

    var_iter = var_list->begin();
    for (auto const& ref_iter : ref_list) {
        if (ref_iter->getSource() == BindingVariable::RESPONSE) {
            EXPECT_EQ((*var_iter)->getName(), ref_iter->getName());
            ++var_iter;
        }
    }

    // Make sure last flush time hasn't been touched.
    EXPECT_EQ(cache->getLastFlushTime(), ref_time);

    // Sleep 1s so we can check flush time gets updated.
    usleep(1000000);
    ASSERT_NO_THROW_LOG(cache->clear());
    EXPECT_EQ(cache->size(), 0);

    EXPECT_GT(cache->getLastFlushTime(), ref_time);
}

/// @brief Verifies cache behavior for handling duplicate
/// entries.
TEST(BindingVariableCacheTest, duplicateEntries) {
    // Create a new cache.
    BindingVariableCachePtr cache(new BindingVariableCache());


    std::string valid_v4_exp = "pkt4.mac";
    BindingVariablePtr var1(new BindingVariable("one", valid_v4_exp,
                                                BindingVariable::QUERY,
                                                AF_INET));

    BindingVariablePtr var2(new BindingVariable("one", valid_v4_exp,
                                                BindingVariable::RESPONSE,
                                                AF_INET));

    bool add_flag;
    ASSERT_NO_THROW_LOG(add_flag = cache->add(var1));
    EXPECT_TRUE(add_flag);
    EXPECT_EQ(cache->size(), 1);

    // Make sure getByName returns the added variable.
    BindingVariablePtr found_var;
    ASSERT_NO_THROW_LOG(found_var = cache->getByName("one"));
    ASSERT_EQ(found_var->getSource(), BindingVariable::QUERY);

    // Adding a duplicate should fail.
    ASSERT_NO_THROW_LOG(add_flag = cache->add(var2));
    EXPECT_FALSE(add_flag);
    EXPECT_EQ(cache->size(), 1);

    // Make sure getByName returns the original variable.
    ASSERT_NO_THROW_LOG(found_var = cache->getByName("one"));
    ASSERT_EQ(found_var->getSource(), BindingVariable::QUERY);
}

/// @brief Tests BindingVariableMgr::configure() with valid
/// configuration scenarios.
TEST(BindingVariableMgrTest, validConfigure) {
    struct Scenario {
        uint32_t line_;
        uint32_t family_;
        std::string config_;
        std::list<std::string> expected_vars_;
    };

    std::list<Scenario> scenarios = {
    {
        __LINE__,
        AF_INET,
        R"({})",
        {}
    },{
        __LINE__,
        AF_INET,
        R"({"binding-variables":[]})",
        {}
    },{
        __LINE__,
        AF_INET,
        R"({"binding-variables":[
            {
                "name": "one",
                "expression": "pkt4.mac",
                "source": "query"
            },
            {
                "name": "two",
                "expression": "pkt4.mac",
                "source": "response"
            } ]})",
        { "one", "two" }
    },{
        __LINE__,
        AF_INET6,
        R"({"binding-variables":[
            {
                "name": "three",
                "expression": "pkt6.transid",
                "source": "query"
            },
            {
                "name": "four",
                "expression": "pkt6.transid",
                "source": "response"
            } ]})",
        { "three", "four" }
    }};

    for (auto const& scenario : scenarios) {
        SCOPED_LINE(scenario.line_);
        BindingVariableMgrPtr mgr;
        ASSERT_NO_THROW_LOG(mgr.reset(new BindingVariableMgr(scenario.family_)));
        ConstElementPtr config;
        ASSERT_NO_THROW_LOG(config = Element::fromJSON(scenario.config_));
        ASSERT_NO_THROW_LOG(mgr->configure(config));
        auto cache = mgr->getCache();
        ASSERT_TRUE(cache);
        ASSERT_EQ(cache->size(), scenario.expected_vars_.size());
        for (auto const& exp_name : scenario.expected_vars_) {
            auto const& found_var = cache->getByName(exp_name);
            ASSERT_TRUE(found_var);
            EXPECT_EQ(found_var->getName(), exp_name);
        }
    }
}

/// @brief Verifies that BindingVariableMgr::configure() clears the
/// cache first.
TEST(BindingVariableMgrTest, clearOnConfigure) {
    std::string cfg1 =
        R"({"binding-variables":[
            {
                "name": "one",
                "expression": "pkt4.mac",
                "source": "query"
            },
            {
                "name": "two",
                "expression": "pkt4.mac",
                "source": "response"
            } ]})";

    std::string cfg2 =
        R"({"binding-variables":[
            {
                "name": "three",
                "expression": "pkt4.mac",
                "source": "query"
            },
            {
                "name": "four",
                "expression": "pkt4.mac",
                "source": "response"
            } ]})";

    BindingVariableMgrPtr mgr;
    ASSERT_NO_THROW_LOG(mgr.reset(new BindingVariableMgr(AF_INET)));

    ConstElementPtr config;
    ASSERT_NO_THROW_LOG(config = Element::fromJSON(cfg1));
    ASSERT_NO_THROW_LOG(mgr->configure(config));
    auto cache = mgr->getCache();
    ASSERT_TRUE(cache);
    ASSERT_EQ(cache->size(), 2);
    ASSERT_TRUE(cache->getByName("one"));
    ASSERT_TRUE(cache->getByName("two"));

    ASSERT_NO_THROW_LOG(config = Element::fromJSON(cfg2));
    ASSERT_NO_THROW_LOG(mgr->configure(config));
    cache = mgr->getCache();
    ASSERT_TRUE(cache);
    ASSERT_EQ(cache->size(), 2);
    ASSERT_FALSE(cache->getByName("one"));
    ASSERT_FALSE(cache->getByName("two"));
    ASSERT_TRUE(cache->getByName("three"));
    ASSERT_TRUE(cache->getByName("four"));
}

/// @brief Tests BindingVariableMgr::configure() with valid
/// configuration scenarios.
TEST(BindingVariableMgrTest, invalidConfigure) {
    struct Scenario {
        uint32_t line_;
        uint32_t family_;
        std::string config_;
        std::string expected_error_;
    };

    std::list<Scenario> scenarios = {
    {
        __LINE__,
        AF_INET,
        R"({"binding-variables": "bogus"})",
        "'binding-variables' must be a list"
    },{
        __LINE__,
        AF_INET,
        R"({"binding-variables":[
            {
                "name": "",
                "expression": "pkt4.mac",
                "source": "query"
            } ]})",
        "cannot add BindingVariable to cache: invalid config:"
        " BindingVariable - name cannot be empty"
    }};

    for (auto const& scenario : scenarios) {
        SCOPED_LINE(scenario.line_);
        BindingVariableMgrPtr mgr;
        ASSERT_NO_THROW_LOG(mgr.reset(new BindingVariableMgr(scenario.family_)));
        ConstElementPtr config;
        ASSERT_NO_THROW_LOG(config = Element::fromJSON(scenario.config_));
        ASSERT_THROW_MSG(mgr->configure(config), DhcpConfigError,
                         scenario.expected_error_);
        auto cache = mgr->getCache();
        ASSERT_TRUE(cache);
        EXPECT_EQ(cache->size(), 0);
    }
}

/// @brief Tests BindingVariableMgr::evaluateVariables() for V4 scenarios.
TEST(BindingVariableMgrTest, evaluateVariables4) {
    struct Scenario {
        uint32_t line_;
        std::string config_;
        std::string orig_context_;
        std::string exp_context_;
    };

    std::list<Scenario> scenarios = {
    {
        // No variables configured, nothing in lease context.
        __LINE__,
        R"({})",
        R"({})",
        R"({})"
    },{
        // lease context has no binding-variables, two configured
        __LINE__,
        R"^({"binding-variables":[
            {
                "name": "hwaddr",
                "expression": "hexstring(pkt4.mac,':')",
                "source": "query"
            },
            {
                "name": "yiaddr",
                "expression": "addrtotext(pkt4.yiaddr)",
                "source": "response"
            }]})^",
        R"({})",
        R"({"ISC":{
            "binding-variables":{
                "hwaddr": "01:02:03:04:05:06",
                "yiaddr": "192.0.1.1"
            }
        }})",
    },
    {
        // lease context has binding-variables, none configured
        // Current logic leaves lease untouched.
        __LINE__,
        R"({})",
        R"({"ISC":{
            "binding-variables":{
                "hwaddr": "01:02:03:04:05:06",
                "yiaddr": "192.0.1.1"
            }
        }})",
        R"({"ISC":{
            "binding-variables":{
                "hwaddr": "01:02:03:04:05:06",
                "yiaddr": "192.0.1.1"
            }
        }})",
    },
    {
        // Evaluated variable value is an empty string.
        __LINE__,
        R"^({"binding-variables":[
            {
                "name": "hwaddr",
                "expression": "''",
                "source": "query"
            }]})^",
        R"({"ISC":{
            "binding-variables":{
                "hwaddr": "01:02:03:04:05:06"
            }
        }})",
        R"({"ISC":{
            "binding-variables":{
                "hwaddr": ""
            }
        }})",
    }};

    // Create packet pair and lease.
    Pkt4Ptr query(new Pkt4(DHCPDISCOVER, 1234));
    query->setHWAddr(1, 6, { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06 });

    Pkt4Ptr response(new Pkt4(DHCPOFFER, 1234));
    IOAddress yiaddr("192.0.1.1");
    response->setYiaddr(yiaddr);

    Lease4Ptr lease(new Lease4());

    // Iterater over scenarios.
    for (auto const& scenario : scenarios) {
        SCOPED_LINE(scenario.line_);

        // Create and configure the manager.
        BindingVariableMgrPtr mgr;
        ASSERT_NO_THROW_LOG(mgr.reset(new BindingVariableMgr(AF_INET)));
        ConstElementPtr config;
        ASSERT_NO_THROW_LOG(config = Element::fromJSON(scenario.config_));
        ASSERT_NO_THROW_LOG(mgr->configure(config));

        // Set the lease context to its original content.
        ConstElementPtr orig_context;
        ASSERT_NO_THROW_LOG(orig_context = Element::fromJSON(scenario.orig_context_));
        lease->setContext(orig_context);

        ConstElementPtr exp_context;
        ASSERT_NO_THROW_LOG(exp_context = Element::fromJSON(scenario.exp_context_));

        // Evaluate the variables.
        bool changed;
        ASSERT_NO_THROW_LOG(changed = mgr->evaluateVariables(query, response, lease));

        // If the original and expected lease contexts the same the lease should
        // not have been changed, otherwse its context should have been updated.
        if (*orig_context == *exp_context) {
            ASSERT_FALSE(changed);
            ASSERT_EQ(*lease->getContext(), *orig_context);
        } else {
            ASSERT_TRUE(changed);
            ASSERT_EQ(*lease->getContext(), *exp_context);
        }
    }
}

/// @brief Tests BindingVariableMgr::evaluateVariables() for V6 scenarios.
TEST(BindingVariableMgrTest, evaluateVariables6) {
    struct Scenario {
        uint32_t line_;
        std::string config_;
        std::string orig_context_;
        std::string exp_context_;
    };

    std::list<Scenario> scenarios = {
    {
        // No variables configured, nothing in lease context.
        __LINE__,
        R"({})",
        R"({})",
        R"({})"
    },
    {
        // lease context has no binding-variables, two configured
        __LINE__,
        R"^({"binding-variables":[
            {
                "name": "client-id",
                "expression": "hexstring(option[1].hex,':')",
                "source": "query"
            },
            {
                "name": "transid",
                "expression": "uint32totext(pkt6.transid)",
                "source": "response"
            }]})^",
        R"({})",
        R"({"ISC":{
            "binding-variables":{
                "client-id": "05:06:07:08",
                "transid": "4321"
            }
        }})",
    },
    {
        // lease context has binding-variables, none configured
        // Current logic leaves lease untouched.
        __LINE__,
        R"({})",
        R"({"ISC":{
            "binding-variables":{
                "client-id": "05:06:07:08",
                "transid": "4321"
            }
        }})",
        R"({"ISC":{
            "binding-variables":{
                "client-id": "05:06:07:08",
                "transid": "4321"
            }
        }})",
    },
    {
        // Evaluated variable value is an empty string.
        __LINE__,
        R"^({"binding-variables":[
            {
                "name": "client-id",
                "expression": "''",
                "source": "query"
            }]})^",
        R"({"ISC":{
            "binding-variables":{
                "client-id": "05:06:07:08"
            }
        }})",
        R"({"ISC":{
            "binding-variables":{
                "client-id": ""
            }
        }})",
    }};

    // Create packet pair and lease.
    Pkt6Ptr query(new Pkt6(DHCPV6_SOLICIT, 1234));
    query->addOption(OptionPtr(new Option(Option::V6,
                                          D6O_CLIENTID,
                                          { 0x05, 0x06, 0x07, 0x08 })));

    Pkt6Ptr response(new Pkt6(DHCPV6_ADVERTISE, 4321));
    Lease6Ptr lease(new Lease6());

    // Iterater over scenarios.
    for (auto const& scenario : scenarios) {
        SCOPED_LINE(scenario.line_);

        // Create and configure the manager.
        BindingVariableMgrPtr mgr;
        ASSERT_NO_THROW_LOG(mgr.reset(new BindingVariableMgr(AF_INET6)));
        ConstElementPtr config;
        ASSERT_NO_THROW_LOG(config = Element::fromJSON(scenario.config_));
        ASSERT_NO_THROW_LOG(mgr->configure(config));

        // Set the lease context to its original content.
        ConstElementPtr orig_context;
        ASSERT_NO_THROW_LOG(orig_context = Element::fromJSON(scenario.orig_context_));
        lease->setContext(orig_context);

        ConstElementPtr exp_context;
        ASSERT_NO_THROW_LOG(exp_context = Element::fromJSON(scenario.exp_context_));

        // Evaluate the variables.
        bool changed;
        ASSERT_NO_THROW_LOG(changed = mgr->evaluateVariables(query, response, lease));

        // If the original and expected lease contexts the same the lease should
        // not have been changed, otherwse its context should have been updated.
        if (*orig_context == *exp_context) {
            ASSERT_FALSE(changed);
            ASSERT_EQ(*lease->getContext(), *orig_context);
        } else {
            ASSERT_TRUE(changed);
            ASSERT_EQ(*lease->getContext(), *exp_context);
        }
    }
}

#if 0
class BindingVariableHandlerTest :  public ::testing::Test { 
public:

    /// @brief Pointer to the lease manager
    isc::dhcp::LeaseMgr* lmptr_;

    /// @brief Constructor
    BindingVariableHandlerTest() {
        isc::dhcp::LeaseMgrFactory::destroy();
        lmptr_ = 0;
    }

    /// @brief Destructor
    ///
    virtual ~BindingVariableHandlerTest() {
        isc::dhcp::LeaseMgrFactory::destroy();
        lmptr_ = 0;
    }

    /// @brief Creates an IPv4 lease
    ///
    /// Lease parameters: valid lifetime = 0xFFFFFFFE, cltt = 1923222072, fqdn-fwd = false,
    /// fqdn-rev = true, hostname = myhost.example.com
    ///
    /// @param ip_address IP address for the lease.
    /// @param subnet_id subnet identifier
    /// @param hw_address_pattern value to be used for generating HW address by repeating
    /// it 6 times.
    /// @param client_id_pattern value to be used for generating client identifier by
    /// repeating it 8 times.
    /// @param declined controls whether the lease should be in declined state.
    ///
    /// @return Returns the lease created
    isc::dhcp::Lease4Ptr createLease4(const std::string& ip_address,
                                      const isc::dhcp::SubnetID& subnet_id,
                                      const uint8_t hw_address_pattern,
                                      const uint8_t client_id_pattern,
                                      uint32_t pool_id = 0) {
        isc::dhcp::Lease4Ptr lease(new isc::dhcp::Lease4());

        lease->addr_ = isc::asiolink::IOAddress(ip_address);

        lease->hwaddr_.reset(new isc::dhcp::HWAddr(std::vector<uint8_t>(6, hw_address_pattern), isc::dhcp::HTYPE_ETHER));
        lease->client_id_ = isc::dhcp::ClientIdPtr(new isc::dhcp::ClientId(std::vector<uint8_t>(8, client_id_pattern)));
        lease->valid_lft_ = 2400;
        lease->updateCurrentExpirationTime();
        lease->subnet_id_ = subnet_id;
        lease->pool_id_ = pool_id;
        return (lease);
    }

    /// @brief Creates an IPv6 lease
    ///
    /// @param ip_address IP address for the lease.
    /// @param subnet_id subnet identifier
    /// @param duid_address_pattern value to be used for generating DUID by
    /// repeating it 8 times
    /// @param declined controls whether the lease should be in declined state.
    ///
    /// @return Returns the lease created
    isc::dhcp::Lease6Ptr createLease6(const std::string& ip_address,
                                      const isc::dhcp::SubnetID& subnet_id,
                                      const uint8_t duid_pattern,
                                      uint32_t pool_id = 0) {
        isc::dhcp::Lease6Ptr lease(new isc::dhcp::Lease6());

        lease->addr_ = isc::asiolink::IOAddress(ip_address);
        lease->type_ = isc::dhcp::Lease::TYPE_NA;
        lease->prefixlen_ = 128;
        lease->iaid_ = 42;
        lease->duid_ = isc::dhcp::DuidPtr(new isc::dhcp::DUID(std::vector<uint8_t>(8, duid_pattern)));
        lease->preferred_lft_ = 1800;
        lease->valid_lft_ = 2400;
        lease->subnet_id_ = subnet_id;
        lease->pool_id_ = pool_id;

        return (lease);
    }

    /// @brief Initializes lease manager (and optionally populates it with a lease)
    ///
    /// Creates a lease manager (memfile, trimmed down to keep everything in memory
    /// only) and optionally can create a lease, which is useful for leaseX-get and
    /// leaseX-del type of tests. For lease details, see @ref createLease4 and
    /// @ref createLease6.
    ///
    /// @param famiily protocol family AF_INET or AF_INET6
    /// @param insert_lease governs whether a lease should be pre-inserted
    /// @param declined governs whether a lease should be in declined state
    void initLeaseMgr(int family) {
        isc::dhcp::LeaseMgrFactory::destroy();
        if (family == AF_INET6) {
            isc::dhcp::LeaseMgrFactory::create("type=memfile persist=false " 
                                               "universe=6 extended-info-tables=true");
            lmptr_ = &(isc::dhcp::LeaseMgrFactory::instance());
            ASSERT_TRUE(lmptr_);
            lmptr_->addLease(createLease6("2001:db8:1::1", 66, 0x42));
            lmptr_->addLease(createLease6("2001:db8:1::2", 66, 0x56));
            lmptr_->addLease(createLease6("2001:db8:2::1", 99, 0x42));
            lmptr_->addLease(createLease6("2001:db8:2::2", 99, 0x56));
        } else {
            isc::dhcp::LeaseMgrFactory::create("type=memfile persist=false universe=4");
            lmptr_ = &(isc::dhcp::LeaseMgrFactory::instance());
            ASSERT_TRUE(lmptr_);
            lmptr_->addLease(createLease4("192.0.2.1", 44, 0x08, 0x42));
            lmptr_->addLease(createLease4("192.0.2.2", 44, 0x09, 0x56));
            lmptr_->addLease(createLease4("192.0.3.1", 88, 0x08, 0x42));
            lmptr_->addLease(createLease4("192.0.3.2", 88, 0x09, 0x56));
        }
    }

#if 0
    /// @brief Check that lease4_offer handler works as expected with
    /// valid inputs.
    void testValidLease4Offer();

    /// @brief Check that leases4_committed handler works as expected with
    /// valid inputs.
    void testValidLeases4Committed();

    /// @brief Check that leases4_committed handler does not throw or alter
    /// the lease under NOP conditions: 
    /// 1. There is no repsonse packet
    /// 2. Response packet is a DHCPACK 
    /// 3. There is no active lease
    void testNopLeases4Committed();
#endif

    /// @brief Check that leases6_committed handler works as expected with
    /// valid inputs.
    void testValidLeases6Committed();

    /// @brief Check that leases6_committed handler does not throw or alter
    /// leases under NOP conditions:
    /// 1. There is no repsonse packet
    /// 2. There are no leases
    /// 3. There are leases but none active
    void testNopLeases6Committed();

    void testLeases6CommittedErrors();
};

#if 0
void
BindingVariableHandlerTest::testValidLease4Offer() {
    initLeaseMgr(AF_INET);

    struct Scenario {
        uint32_t line_;
        std::string config_;
        std::string orig_context_;
        std::string exp_context_;
        uint32_t offer_lifetime_;
    };

    std::list<Scenario> scenarios = {
    {
        // No variables configured, nothing in lease context.
        __LINE__,
        R"({})",
        R"({})",
        R"({})",
        500
    },
    {
        // lease context has no binding-variables, two configured
        __LINE__,
        R"^({"binding-variables":[
            {
                "name": "hwaddr",
                "expression": "hexstring(pkt4.mac,':')",
                "source": "query"
            },
            {
                "name": "yiaddr",
                "expression": "addrtotext(pkt4.yiaddr)",
                "source": "response"
            }]})^",
        R"({})",
        R"({"ISC":{
            "binding-variables":{
                "hwaddr": "01:02:03:04:05:06",
                "yiaddr": "192.0.2.1"
            }
        }})",
        500
    },
    {
        // lease context has no binding-variables, two configured
        // offer lifetime is 0.
        __LINE__,
        R"^({"binding-variables":[
            {
                "name": "hwaddr",
                "expression": "hexstring(pkt4.mac,':')",
                "source": "query"
            },
            {
                "name": "yiaddr",
                "expression": "addrtotext(pkt4.yiaddr)",
                "source": "response"
            }]})^",
        R"({})",
        R"({})",
        0
    },
    {
        // lease context has binding-variables, none configured
        // Current logic leaves lease untouched.
        __LINE__,
        R"({})",
        R"({"ISC":{
            "binding-variables":{
                "hwaddr": "01:02:03:04:05:06",
                "yiaddr": "192.0.2.1"
            }
        }})",
        R"({"ISC":{
            "binding-variables":{
                "hwaddr": "01:02:03:04:05:06",
                "yiaddr": "192.0.2.1"
            }
        }})",
        500
    },
    {
        // Evaluated variable value is an empty string.
        __LINE__,
        R"^({"binding-variables":[
            {
                "name": "hwaddr",
                "expression": "''",
                "source": "query"
            }]})^",
        R"({"ISC":{
            "binding-variables":{
                "hwaddr": "01:02:03:04:05:06"
            }
        }})",
        R"({"ISC":{
            "binding-variables":{
                "hwaddr": ""
            }
        }})",
        500
    }};

    // Create packet pair and lease.
    Pkt4Ptr query(new Pkt4(DHCPDISCOVER, 1234));
    query->setHWAddr(1, 6, { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06 });

    Pkt4Ptr response(new Pkt4(DHCPOFFER, 1234));
    IOAddress yiaddr("192.0.2.1");
    response->setYiaddr(yiaddr);

    // Iterater over scenarios.
    for (auto const& scenario : scenarios) {
        SCOPED_LINE(scenario.line_);

        // Create and configure the manager.
        BindingVariableMgrPtr mgr;
        ASSERT_NO_THROW_LOG(mgr.reset(new BindingVariableMgr(AF_INET)));
        ConstElementPtr config;
        ASSERT_NO_THROW_LOG(config = Element::fromJSON(scenario.config_));
        ASSERT_NO_THROW_LOG(mgr->configure(config));

        // Fetch the lease and set its user-context to the original content.
        Lease4Ptr orig_lease = lmptr_->getLease4(yiaddr);
        ASSERT_TRUE(orig_lease);
        ConstElementPtr orig_context;
        ASSERT_NO_THROW_LOG(orig_context = Element::fromJSON(scenario.orig_context_));
        orig_lease->setContext(orig_context);
        ASSERT_NO_THROW_LOG(lmptr_->updateLease4(orig_lease));

        Lease4CollectionPtr leases(new Lease4Collection());
        leases->push_back(orig_lease);

        // Create a callout handle and add the expected arguments.
        CalloutHandlePtr callout_handle = HooksManager::createCalloutHandle();
        callout_handle->setArgument("query4", query);
        callout_handle->setArgument("response4", response);
        callout_handle->setArgument("leases4", leases);
        callout_handle->setArgument("offer_lifetime", scenario.offer_lifetime_);

        // Invoke the leases4Committed handler.
        LeaseCmds cmds;
        ASSERT_NO_THROW_LOG(cmds.lease4Offer(*callout_handle, mgr));

        // Fetch the lease.
        Lease4Ptr after_lease = lmptr_->getLease4(yiaddr);
        ASSERT_TRUE(after_lease);

        // Context contents should match the expected context content.
        ConstElementPtr exp_context;
        ASSERT_NO_THROW_LOG(exp_context = Element::fromJSON(scenario.exp_context_));
        ASSERT_EQ(*(after_lease->getContext()), *exp_context);
    }
}

void
BindingVariableHandlerTest::testValidLeases4Committed() {
    initLeaseMgr(AF_INET);

    struct Scenario {
        uint32_t line_;
        std::string config_;
        std::string orig_context_;
        std::string exp_context_;
    };

    std::list<Scenario> scenarios = {
    {
        // No variables configured, nothing in lease context.
        __LINE__,
        R"({})",
        R"({})",
        R"({})"
    },
    {
        // lease context has no binding-variables, two configured
        __LINE__,
        R"^({"binding-variables":[
            {
                "name": "hwaddr",
                "expression": "hexstring(pkt4.mac,':')",
                "source": "query"
            },
            {
                "name": "yiaddr",
                "expression": "addrtotext(pkt4.yiaddr)",
                "source": "response"
            }]})^",
        R"({})",
        R"({"ISC":{
            "binding-variables":{
                "hwaddr": "01:02:03:04:05:06",
                "yiaddr": "192.0.2.1"
            }
        }})",
    },
    {
        // lease context has binding-variables, none configured
        // Current logic leaves lease untouched.
        __LINE__,
        R"({})",
        R"({"ISC":{
            "binding-variables":{
                "hwaddr": "01:02:03:04:05:06",
                "yiaddr": "192.0.2.1"
            }
        }})",
        R"({"ISC":{
            "binding-variables":{
                "hwaddr": "01:02:03:04:05:06",
                "yiaddr": "192.0.2.1"
            }
        }})",
    },
    {
        // Evaluated variable value is an empty string.
        __LINE__,
        R"^({"binding-variables":[
            {
                "name": "hwaddr",
                "expression": "''",
                "source": "query"
            }]})^",
        R"({"ISC":{
            "binding-variables":{
                "hwaddr": "01:02:03:04:05:06"
            }
        }})",
        R"({"ISC":{
            "binding-variables":{
                "hwaddr": ""
            }
        }})",
    }};

    // Create packet pair and lease.
    Pkt4Ptr query(new Pkt4(DHCPREQUEST, 1234));
    query->setHWAddr(1, 6, { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06 });

    Pkt4Ptr response(new Pkt4(DHCPACK, 1234));
    IOAddress yiaddr("192.0.2.1");
    response->setYiaddr(yiaddr);

    // Iterater over scenarios.
    for (auto const& scenario : scenarios) {
        SCOPED_LINE(scenario.line_);

        // Create and configure the manager.
        BindingVariableMgrPtr mgr;
        ASSERT_NO_THROW_LOG(mgr.reset(new BindingVariableMgr(AF_INET)));
        ConstElementPtr config;
        ASSERT_NO_THROW_LOG(config = Element::fromJSON(scenario.config_));
        ASSERT_NO_THROW_LOG(mgr->configure(config));

        // Fetch the lease and set its user-context to the original content.
        Lease4Ptr orig_lease = lmptr_->getLease4(yiaddr);
        ASSERT_TRUE(orig_lease);
        ConstElementPtr orig_context;
        ASSERT_NO_THROW_LOG(orig_context = Element::fromJSON(scenario.orig_context_));
        orig_lease->setContext(orig_context);
        ASSERT_NO_THROW_LOG(lmptr_->updateLease4(orig_lease));

        Lease4CollectionPtr leases(new Lease4Collection());
        leases->push_back(orig_lease);

        // Create a callout handle and add the expected arguments.
        CalloutHandlePtr callout_handle = HooksManager::createCalloutHandle();
        callout_handle->setArgument("query4", query);
        callout_handle->setArgument("response4", response);
        callout_handle->setArgument("leases4", leases);

        // Invoke the leases4Committed handler.
        LeaseCmds cmds;
        ASSERT_NO_THROW_LOG(cmds.leases4Committed(*callout_handle, mgr));

        // Fetch the lease.
        Lease4Ptr after_lease = lmptr_->getLease4(yiaddr);
        ASSERT_TRUE(after_lease);

        // Context contents should match the expected context content.
        ConstElementPtr exp_context;
        ASSERT_NO_THROW_LOG(exp_context = Element::fromJSON(scenario.exp_context_));
        ASSERT_EQ(*(after_lease->getContext()), *exp_context);
    }
}

void
BindingVariableHandlerTest::testNopLeases4Committed() {
    initLeaseMgr(AF_INET);

    struct Scenario {
        uint32_t line_;
        DHCPMessageType response_type_;
        bool send_lease_;
    };

    // Configure a single variable.
    std::string config =
    R"^({"binding-variables":[
    {
        "name": "hwaddr",
        "expression": "hexstring(pkt4.mac,':')",
        "source": "query"
    }]})^";

    // Create and configure the manager.
    BindingVariableMgrPtr mgr;
    ASSERT_NO_THROW_LOG(mgr.reset(new BindingVariableMgr(AF_INET)));
    ASSERT_NO_THROW_LOG(mgr->configure(Element::fromJSON(config)));

    // Scenarios should all result in no change to the lease.
    std::list<Scenario> scenarios = {
    {
        // Response is not a DHCPACK.
        __LINE__,
        DHCPNAK,
        true
    },
    {
        // No active lease.
        __LINE__,
        DHCPACK,
        false
    },
    {
        // No response.
        __LINE__,
        DHCP_NOTYPE,
        false
    }};

    // Create packet pair and lease.
    Pkt4Ptr query(new Pkt4(DHCPREQUEST, 1234));
    query->setHWAddr(1, 6, { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06 });
    IOAddress yiaddr("192.0.2.1");
    for (auto const& scenario : scenarios) {
        SCOPED_LINE(scenario.line_);

        Pkt4Ptr response;
        if (scenario.response_type_ != DHCP_NOTYPE) {
            response.reset(new Pkt4(scenario.response_type_, 1234));
        }

        // Fetch the lease and set its user-context to the original content.
        Lease4Ptr orig_lease = lmptr_->getLease4(yiaddr);
        ASSERT_TRUE(orig_lease);
        ASSERT_FALSE(orig_lease->getContext());

        Lease4CollectionPtr leases(new Lease4Collection());
        if (scenario.send_lease_) {
            leases->push_back(orig_lease);
        }

        // Create a callout handle and add the expected arguments.
        CalloutHandlePtr callout_handle = HooksManager::createCalloutHandle();
        callout_handle->setArgument("query4", query);
        callout_handle->setArgument("response4", response);
        callout_handle->setArgument("leases4", leases);

        // Invoke the leases4Committed handler.
        LeaseCmds cmds;
        ASSERT_NO_THROW_LOG(cmds.leases4Committed(*callout_handle, mgr));

        // Fetch the lease. Context should still be empty.
        Lease4Ptr after_lease = lmptr_->getLease4(yiaddr);
        ASSERT_TRUE(after_lease);
        ASSERT_FALSE(after_lease->getContext());
    }
}
#endif

void
BindingVariableHandlerTest::testValidLeases6Committed() {
    initLeaseMgr(AF_INET6);

    struct Scenario {
        uint32_t line_;
        std::string config_;
        std::string orig_context_;
        std::string exp_context_;
    };

    std::list<Scenario> scenarios = {
    {
        // No variables configured, nothing in lease context.
        __LINE__,
        R"({})",
        R"({})",
        R"({})"
    },
    {
        // Lease context has no binding-variables, two configured.
        __LINE__,
        R"^({"binding-variables":[
            {
                "name": "duid",
                "expression": "hexstring(option[1].hex,':')",
                "source": "query"
            },
            {
                "name": "sub-id",
                "expression": "hexstring(option[38].hex, ':')",
                "source": "response"
            }]})^",
        R"({})",
        R"({"ISC":{
            "binding-variables":{
                "duid": "01:02:03:04",
                "sub-id": "05:06:07:08"
            }
        }})",
    },
    {
        // Lease context has binding-variables, none configured.
        // Current logic leaves lease untouched.
        __LINE__,
        R"({})",
        R"({"ISC":{
            "binding-variables":{
                "duid": "01:02:03:04",
                "sub-id": "05:06:07:08"
            }
        }})",
        R"({"ISC":{
            "binding-variables":{
                "duid": "01:02:03:04",
                "sub-id": "05:06:07:08"
            }
        }})",
    },
    {
        // Evaluated variable value is an empty string.
        __LINE__,
        R"^({"binding-variables":[
            {
                "name": "my-var",
                "expression": "''",
                "source": "query"
            }]})^",
        R"({"ISC":{
            "binding-variables":{
                "my-var": "pre-existing value"
            }
        }})",
        R"({"ISC":{
            "binding-variables":{
                "my-var": ""
            }
        }})",
    }
    };

    // Create packet pair and lease.
    Pkt6Ptr query(new Pkt6(DHCPV6_REQUEST, 1234));
    OptionPtr client_id(new Option(Option::V6, D6O_CLIENTID,
                                   { 0x01, 0x02, 0x03, 0x04 }));
    query->addOption(client_id);

    Pkt6Ptr response(new Pkt6(DHCPV6_REPLY, 7890));
    OptionPtr subscriber_id(new Option(Option::V6, D6O_SUBSCRIBER_ID,
                                       { 0x05, 0x06, 0x07, 0x08 }));
    response->addOption(subscriber_id);

    // Create a list of the lease addresses.
    std::list<IOAddress> lease_addrs;
    lease_addrs.push_back(IOAddress("2001:db8:1::1"));
    lease_addrs.push_back(IOAddress("2001:db8:1::2"));
    lease_addrs.push_back(IOAddress("2001:db8:2::2"));

    // Iterater over scenarios.
    for (auto const& scenario : scenarios) {
        SCOPED_LINE(scenario.line_);

        // Create and configure the manager.
        BindingVariableMgrPtr mgr;
        ASSERT_NO_THROW_LOG(mgr.reset(new BindingVariableMgr(AF_INET6)));
        ConstElementPtr config;
        ASSERT_NO_THROW_LOG(config = Element::fromJSON(scenario.config_));
        ASSERT_NO_THROW_LOG(mgr->configure(config));

        // Fetch the lease and set its user-context to the original content.
        Lease6CollectionPtr orig_leases(new Lease6Collection());
        for (auto const& address : lease_addrs) {
            Lease6Ptr orig_lease = lmptr_->getLease6(Lease::TYPE_NA, address);
            ASSERT_TRUE(orig_lease);
            ASSERT_TRUE(orig_lease->valid_lft_ > 0);

            ConstElementPtr orig_context;
            ASSERT_NO_THROW_LOG(orig_context = Element::fromJSON(scenario.orig_context_));
            orig_lease->setContext(orig_context);
            ASSERT_NO_THROW_LOG(lmptr_->updateLease6(orig_lease));
            orig_leases->push_back(orig_lease);
        }

        // Create a callout handle and add the expected arguments.
        CalloutHandlePtr callout_handle = HooksManager::createCalloutHandle();
        callout_handle->setArgument("query6", query);
        callout_handle->setArgument("response6", response);
        callout_handle->setArgument("leases6", orig_leases);

        // Invoke the leases6Committed handler.
        LeaseCmds cmds;
        ASSERT_NO_THROW_LOG(cmds.leases6Committed(*callout_handle, mgr));

        // Iterate over the leases and make sure the user-contexts are as expected.
        for (auto const& lease : *orig_leases) {
            // Fetch the lease.
            Lease6Ptr after_lease = lmptr_->getLease6(Lease::TYPE_NA, lease->addr_);
            ASSERT_TRUE(after_lease);

            // Context contents should match the expected context content.
            ConstElementPtr exp_context;
            ASSERT_NO_THROW_LOG(exp_context = Element::fromJSON(scenario.exp_context_));
            ASSERT_EQ(*(after_lease->getContext()), *exp_context);
        }
    }
}

void
BindingVariableHandlerTest::testNopLeases6Committed() {
    initLeaseMgr(AF_INET6);

    struct Scenario {
        uint32_t line_;
        DHCPv6MessageType response_type_;
        bool send_lease_;
        uint32_t valid_lft_;
    };

    // Configure a single variable.
    std::string config =
    R"^({"binding-variables":[
    {
        "name": "duid",
        "expression": "hexstring(option[1].hex,':')",
        "source": "query"
    }]})^";

    // Create and configure the manager.
    BindingVariableMgrPtr mgr;
    ASSERT_NO_THROW_LOG(mgr.reset(new BindingVariableMgr(AF_INET6)));
    ASSERT_NO_THROW_LOG(mgr->configure(Element::fromJSON(config)));

    // Scenarios should all result in no change to the lease.
    std::list<Scenario> scenarios = {
    {
        // No leases.
        __LINE__,
        DHCPV6_REPLY,
        false,
        0
    },
    {
        // No active leases.
        __LINE__,
        DHCPV6_REPLY,
        true,
        0
    },
    {
        // No response.
        __LINE__,
        DHCPV6_NOTYPE,
        true,
        1000
    }};

    // Create query packet.
    Pkt6Ptr query(new Pkt6(DHCPV6_REQUEST, 1234));
    OptionPtr client_id(new Option(Option::V6, D6O_CLIENTID,
                                   { 0x01, 0x02, 0x03, 0x04 }));
    query->addOption(client_id);

    IOAddress na_addr("2001:db8:1::1");
    for (auto const& scenario : scenarios) {
        SCOPED_LINE(scenario.line_);

        // Create the response packet, if one.
        Pkt6Ptr response;
        if (scenario.response_type_ != DHCPV6_NOTYPE) {
            response.reset(new Pkt6(scenario.response_type_, 1234));
        }


        // Fetch the lease and verify there is no context content.
        Lease6Ptr orig_lease = lmptr_->getLease6(Lease::TYPE_NA, na_addr);
        ASSERT_TRUE(orig_lease);
        ASSERT_FALSE(orig_lease->getContext());
        orig_lease->valid_lft_ =  scenario.valid_lft_;

        Lease6CollectionPtr leases(new Lease6Collection());
        if (scenario.send_lease_) {
            leases->push_back(orig_lease);
        }

        // Create a callout handle and add the expected arguments.
        CalloutHandlePtr callout_handle = HooksManager::createCalloutHandle();
        callout_handle->setArgument("query6", query);
        callout_handle->setArgument("response6", response);
        callout_handle->setArgument("leases6", leases);

        // Invoke the leases6Committed handler.
        LeaseCmds cmds;
        ASSERT_NO_THROW_LOG(cmds.leases6Committed(*callout_handle, mgr));

        // Fetch the lease. Context should still be empty.
        Lease6Ptr after_lease = lmptr_->getLease6(Lease::TYPE_NA, na_addr);
        ASSERT_TRUE(after_lease);
        ASSERT_FALSE(after_lease->getContext());
    }
}

void
BindingVariableHandlerTest::testLeases6CommittedErrors() {
    initLeaseMgr(AF_INET6);

    // Create a config with two binding variables.
    std::string config_str =
        R"^({"binding-variables":[
            {
                "name": "duid",
                "expression": "hexstring(option[1].hex,':')",
                "source": "query"
            },
            {
                "name": "sub-id",
                "expression": "hexstring(option[38].hex, ':')",
                "source": "response"
            }]})^";

    ConstElementPtr config;
    ASSERT_NO_THROW_LOG(config = Element::fromJSON(config_str));

    // Create the expected context contents.
    std::string exp_context_str =
        R"({"ISC":{
            "binding-variables":{
                "duid": "01:02:03:04",
                "sub-id": "05:06:07:08"
            }
        }})";


    ConstElementPtr exp_context;
    ASSERT_NO_THROW_LOG(exp_context = Element::fromJSON(exp_context_str));

    // Create packet pair and lease.
    Pkt6Ptr query(new Pkt6(DHCPV6_REQUEST, 1234));
    OptionPtr client_id(new Option(Option::V6, D6O_CLIENTID,
                                   { 0x01, 0x02, 0x03, 0x04 }));
    query->addOption(client_id);

    Pkt6Ptr response(new Pkt6(DHCPV6_REPLY, 7890));
    OptionPtr subscriber_id(new Option(Option::V6, D6O_SUBSCRIBER_ID,
                                       { 0x05, 0x06, 0x07, 0x08 }));
    response->addOption(subscriber_id);

    // Create and configure the manager.
    BindingVariableMgrPtr mgr;
    ASSERT_NO_THROW_LOG(mgr.reset(new BindingVariableMgr(AF_INET6)));
    ASSERT_NO_THROW_LOG(mgr->configure(config));

    // Fetch the leases.
    std::list<IOAddress> lease_addrs;
    lease_addrs.push_back(IOAddress("2001:db8:1::1"));
    lease_addrs.push_back(IOAddress("2001:db8:1::2"));
    lease_addrs.push_back(IOAddress("2001:db8:2::2"));

    Lease6CollectionPtr orig_leases(new Lease6Collection());
    for (auto const& address : lease_addrs) {
        Lease6Ptr orig_lease = lmptr_->getLease6(Lease::TYPE_NA, address);
        ASSERT_TRUE(orig_lease);
        orig_leases->push_back(orig_lease);
    }

    // Delete the middle lease from the back end. This should cause a conflict error.
    ASSERT_NO_THROW_LOG(lmptr_->deleteLease((*orig_leases)[1]));

    // Create a callout handle and add the expected arguments.
    CalloutHandlePtr callout_handle = HooksManager::createCalloutHandle();
    callout_handle->setArgument("query6", query);
    callout_handle->setArgument("response6", response);
    callout_handle->setArgument("leases6", orig_leases);

    // Invoke the leases6Committed handler.
    LeaseCmds cmds;
    ASSERT_THROW_MSG(cmds.leases6Committed(*callout_handle, mgr),
                     Unexpected,
                     "1 out of 3 leases failed to update for "
                     "duid=[01:02:03:04], [no hwaddr info], tid=0x4d2");

    for (auto const& lease : *orig_leases) {
        // Fetch the lease.
        Lease6Ptr after_lease = lmptr_->getLease6(Lease::TYPE_NA, lease->addr_);
        if (after_lease) {
            // Context contents should match the expected context content.
            ASSERT_EQ(*(after_lease->getContext()), *exp_context);
        } else {
            // Middle lease should not be found.
            EXPECT_EQ(lease->addr_, (*orig_leases)[1]->addr_);
        }
    }
}

TEST_F(BindingVariableHandlerTest, validLeases6Committed) {
    testValidLeases6Committed();
}

TEST_F(BindingVariableHandlerTest, validLeases6CommittedMultiThreading) {
    MultiThreadingTest mt(true);
    testValidLeases6Committed();
}

TEST_F(BindingVariableHandlerTest, nopLeases6Committed) {
    testNopLeases6Committed();
}

TEST_F(BindingVariableHandlerTest, nopLeases6CommittedMultiThreading) {
    MultiThreadingTest mt(true);
    testNopLeases6Committed();
}

TEST_F(BindingVariableHandlerTest, leases6CommittedErrors) {
    testLeases6CommittedErrors();
}

TEST_F(BindingVariableHandlerTest, leases6CommittedErrorsMultiThreading) {
    MultiThreadingTest mt(true);
    testLeases6CommittedErrors();
}
#endif

} // end of anonymous namespace
