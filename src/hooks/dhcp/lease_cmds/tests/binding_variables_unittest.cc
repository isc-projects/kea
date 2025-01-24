// Copyright (C) 2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>


#include <binding_variables.h>
#include <exceptions/exceptions.h>
#include <cc/data.h>
#include <testutils/gtest_utils.h>
#include <testutils/user_context_utils.h>
#include <testutils/multi_threading_utils.h>

#include <gtest/gtest.h>

using namespace std;
using namespace isc;
using namespace isc::data;
using namespace isc::test;

using namespace isc::lease_cmds;

namespace {

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
        }
    };

    for (auto const& scenario : scenarios) {
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
    std::string expected_json = "{ \"expression_str\": \"pkt4.mac\","
                                " \"name\": \"myvar\", \"source\": \"query\" }";
    EXPECT_EQ(ss.str(), expected_json);
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
        ASSERT_NO_THROW_LOG(cache->cacheVariable(ref_iter));
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
    ASSERT_NO_THROW_LOG(add_flag = cache->cacheVariable(var1));
    EXPECT_TRUE(add_flag);
    EXPECT_EQ(cache->size(), 1);

    // Make sure getByName returns the added variable.
    BindingVariablePtr found_var;
    ASSERT_NO_THROW_LOG(found_var = cache->getByName("one"));
    ASSERT_EQ(found_var->getSource(), BindingVariable::QUERY);

    // Adding a duplicate should fail.
    ASSERT_NO_THROW_LOG(add_flag = cache->cacheVariable(var2));
    EXPECT_FALSE(add_flag);
    EXPECT_EQ(cache->size(), 1);

    // Make sure getByName returns the original variable.
    ASSERT_NO_THROW_LOG(found_var = cache->getByName("one"));
    ASSERT_EQ(found_var->getSource(), BindingVariable::QUERY);
}

} // end of anonymous namespace
