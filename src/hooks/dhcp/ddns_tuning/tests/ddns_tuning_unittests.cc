// Copyright (C) 2022-2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

/// @file This file contains tests which ddns tuning library components.

#include <config.h>
#include <asiolink/io_address.h>
#include <ddns_tuning.h>
#include <ddns_tuning_log.h>
#include <dhcp/libdhcp++.h>
#include <dhcp/option_string.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/subnet.h>
#include <eval/eval_context.h>
#include <hooks/callout_manager.h>
#include <hooks/hooks.h>
#include <testutils/gtest_utils.h>
#include <testutils/multi_threading_utils.h>

#include <boost/date_time/posix_time/posix_time.hpp>
#include <gtest/gtest.h>
#include <sstream>

using namespace std;
using namespace isc;
using namespace isc::asiolink;
using namespace isc::data;
using namespace isc::dhcp;
using namespace isc::eval;
using namespace isc::hooks;
using namespace isc::ddns_tuning;
using namespace isc::test;
using namespace boost::posix_time;

namespace {

/// @brief Test derivation of DdnsTuningImpl that allows flush time to be modified.
class TestDdnsTuningImpl : public DdnsTuningImpl {
public:
    /// @brief Constructor
    ///
    /// @param family protocol family AF_INET or AF_INET6
    TestDdnsTuningImpl (int family) : DdnsTuningImpl(family) {
    }

    /// @brief Destructor
    virtual ~TestDdnsTuningImpl() {
    }

    /// @brief Adjusts the expression cache's last flush time.
    ///
    /// This is used to ease verifying if and when flushes have occurred.
    /// @param offset signed number of seconds by which to adjust the
    /// last flush time value.
    void tweakLastFlushTime(int offset) {
        subnet_exprs_.setModificationTime(getLastFlushTime() + seconds(offset));
    }
};

/// @brief Test fixture for testing the DDNS Tuning library.
class DdnsTuningImplTest : public ::testing::Test {
public:
    /// @brief Enum that describes the expected expression returned by the cache.
    enum ExpExpressionType {
        EXPR_NULL,      // Pointer is null
        EXPR_EMPTY,     // Points to an empty Expression
        EXPR_VALID      // Points to an Expression
    };

    /// @brief Mnemonic constants used in test scenarios.
    const int offset_older = -50;
    const int offset_newer = 50;
    const bool flush = true;
    const bool no_flush = false;

    /// @brief Describes a subnet expression test scenario.
    struct Scenario {
        std::string desc_;           // Scenario description
        std::string orig_expr_;      // Subnet's pre-existing expression string
        std::string new_expr_;       // Subnet's new expression string
        int mod_time_offset;         // Offset from last_flush_time of subnet modification time
        std::string exp_hostname_;   // Expected calculated hostname
        bool exp_flush_;             // True if the cached should get flushed
        ExpExpressionType exp_type_; // Expected state of the subnet's cached expression
    };

    /// @brief Constructor.
    DdnsTuningImplTest(int family) {
        impl_.reset(new TestDdnsTuningImpl(family));
    }

    /// @brief Destructor.
    virtual ~DdnsTuningImplTest() {
    }

    /// @brief Fetches a specific test subnet instance.
    ///
    /// @param index index of the desired subnet.
    /// @return a reference to the desired subnet.
    /// @throw OutOfRange if the index is out of range.
    virtual SubnetPtr getSubnet(size_t index) {
        if (index > test_subnets_.size()) {
            isc_throw(OutOfRange, "subnet index: " << index << " is out of range");
        }

        return (test_subnets_[index]);
    }

    /// @brief Fetches a protocol specific packet.
    ///
    /// @return a pointer to the packet.
    virtual PktPtr getPacket() = 0;

    /// @brief Updates a subnet's expression.
    ///
    /// Stores the given expression string in the subnet's user context.  If the
    /// string value is "<null>" then the user context is set to an empty map.
    ///
    /// @param subnet reference to the subnet.
    /// @param expression_str string containing the desired expression or "<null>".
    /// @mod_time_offset if not zero, the subnet's modification time will be set
    /// to the cache's last_flush_time adjusted by this signed value.  A negative
    /// offset makes the subnet older than the flush time, a positive offset makes
    /// the subnet newer than the flush time.
    void setSubnetExpression(SubnetPtr subnet, const std::string expression_str,
                             int mod_time_offset = 0) {
        ASSERT_TRUE(subnet);
        ElementPtr user_context = Element::createMap();
        if (expression_str != "<null>") {
            ElementPtr ddns_tuning = Element::createMap();
            ddns_tuning->set("hostname-expr", Element::create(expression_str));
            user_context->set("ddns-tuning", ddns_tuning);
        }

        subnet->setContext(user_context);
        if (mod_time_offset) {
            subnet->setModificationTime(impl_->getLastFlushTime() + seconds(mod_time_offset));
        }
    }

    std::string evaluateExpression(SubnetID subnet_id) {
        PktPtr pkt = getPacket();

        // Look for a hostname expression first by subnet, then globally.
        auto hostname_expr = impl_->getHostnameExpression(subnet_id);

        // If there isn't an expression or the expression is empty
        // return an empty string.
        if (!hostname_expr || (hostname_expr->empty())) {
            return (std::string(""));
        }

        // We have an expression use it to calculate the hostname.
        return (isc::dhcp::evaluateString(*hostname_expr, *pkt));
    }

    /// @brief Tests DdnsTuningImpl::configure() with invalid configurations.
    void testInvalidConfigs() {
        // Config cannot be an empty pointer.
        ElementPtr config;
        ASSERT_THROW_MSG(impl_->configure(config), BadValue, "params must not be null");
        ASSERT_FALSE(impl_->getGlobalHostnameExpression());

        // Config must be a map element.
        config = Element::create("bogus");
        ASSERT_THROW_MSG(impl_->configure(config), BadValue, "params must be an Element::map");
        ASSERT_FALSE(impl_->getGlobalHostnameExpression());

        // hostname-expr must be a string.
        config = Element::createMap();
        config->set("hostname-expr", Element::create(false));
        ASSERT_THROW_MSG(impl_->configure(config), BadValue, "'hostname-expr' must be a string");
        ASSERT_FALSE(impl_->getGlobalHostnameExpression());

        // An expression parsing error should be detected.
        config = Element::createMap();
        config->set("hostname-expr", Element::create("bogus expression"));
        ASSERT_THROW_MSG(impl_->configure(config), BadValue,
                         "global expression parsing failed: error parsing expression:"
                         " [bogus expression] : <string>:1.1: Invalid character: b");
        ASSERT_FALSE(impl_->getGlobalHostnameExpression());
    }

    /// @brief Verifies that an empty map or an empty hostname-expr is OK.
    void testEmptyConfigs() {
        // An empty map should be OK.
        ElementPtr config = Element::createMap();
        ASSERT_NO_THROW_LOG(impl_->configure(config));
        EXPECT_FALSE(impl_->getGlobalHostnameExpression());

        // An empty string for global hostname-expr should be OK. It should not
        // create a global expression.
        config = Element::createMap();
        config->set("hostname-expr", Element::create(""));
        ASSERT_NO_THROW_LOG(impl_->configure(config));
        ASSERT_FALSE(impl_->getGlobalHostnameExpression());
    }

    /// @brief Verify that a global expression can be configured and used.
    void testValidGlobalExpression() {
        // Configure a global expression.
        ElementPtr config = Element::createMap();
        config->set("hostname-expr", Element::create("'global'"));
        ASSERT_NO_THROW_LOG(impl_->configure(config));
        // We should be able to fetch the expression directly.
        ExpressionPtr global_expr = impl_->getGlobalHostnameExpression();
        ASSERT_TRUE(global_expr);
        EXPECT_FALSE(global_expr->empty());

        // Scoped fetch should point to the global expression. We pass in a subnet which
        // does not define an expression.
        ExpressionPtr also_global;
        ASSERT_NO_THROW_LOG(also_global = impl_->fetchScopedHostnameExpression(getSubnet(0)));
        EXPECT_EQ(also_global, global_expr);

        // Now let's make a packet without the hostname option.
        PktPtr pkt = getPacket();
        std::string calculated_name = "orig_text";
        ASSERT_NO_THROW_LOG(calculated_name = impl_->calculateHostname(pkt, (getSubnet(0))));
        EXPECT_EQ(calculated_name, "global");
    }

    /// @brief Verify that a subnet expression can be configured and used.
    void testValidSubnetExpression() {
        // Configure with no global expression.
        ElementPtr config = Element::createMap();
        ASSERT_NO_THROW_LOG(impl_->configure(config));
        // We should not have a global expression.
        ASSERT_FALSE(impl_->getGlobalHostnameExpression());

        // Add a valid expression string to the subnet.
        SubnetPtr subnet = getSubnet(0);
        setSubnetExpression(subnet, "'subnet_100'");

        // Verify there is no subnet expression for our subnet.
        ASSERT_FALSE(impl_->getHostnameExpression(subnet->getID()));

        // A scoped fetch should return the expression.
        ExpressionPtr subnet_expr;
        ASSERT_NO_THROW_LOG(subnet_expr = impl_->fetchScopedHostnameExpression(subnet));
        ASSERT_TRUE(subnet_expr);

        // A subsequent scoped fetch should return the same expression.
        ExpressionPtr also_subnet;
        ASSERT_NO_THROW_LOG(also_subnet = impl_->fetchScopedHostnameExpression(subnet));
        EXPECT_EQ(*also_subnet, *subnet_expr);

        // Now let's make a packet without the hostname option.
        PktPtr pkt = getPacket();
        std::string calculated_name = "orig_text";
        // Calculating the hostname based on the packet and subnet use subnet expression.
        ASSERT_NO_THROW_LOG(calculated_name = impl_->calculateHostname(pkt, subnet));
        EXPECT_EQ(calculated_name, "subnet_100");

        // Now try it with a different subnet that has no expression.
        ASSERT_NO_THROW_LOG(calculated_name = impl_->calculateHostname(pkt, getSubnet(1)));
        EXPECT_EQ(calculated_name, "");

        // Now try it with a different subnet that has a different expression.
        setSubnetExpression(getSubnet(2), "'subnet_300'");
        ASSERT_NO_THROW_LOG(calculated_name = impl_->calculateHostname(pkt, getSubnet(2)));
        EXPECT_EQ(calculated_name, "subnet_300");
    }

    /// @brief Verify that global and subnet expressions work together properly.
    void testGlobalAndSubnetExpressions() {
        // Configure a simple global expression.
        ElementPtr config = Element::createMap();
        config->set("hostname-expr", Element::create("'global'"));
        ASSERT_NO_THROW_LOG(impl_->configure(config));

        // We should have a global expression.
        ASSERT_TRUE(impl_->getGlobalHostnameExpression());

        // Make a packet.
        PktPtr pkt = getPacket();
        std::string calculated_name = "orig_text";

        // Calculating for a subnet without an expression should use the global expression.
        ASSERT_NO_THROW_LOG(calculated_name = impl_->calculateHostname(pkt, getSubnet(0)));
        EXPECT_EQ(calculated_name, "global");

        // Calculating with a subnet that has an expression, should use the subnet's expression.
        setSubnetExpression(getSubnet(1), "'subnet_200'");
        ASSERT_NO_THROW_LOG(calculated_name = impl_->calculateHostname(pkt, getSubnet(1)));
        EXPECT_EQ(calculated_name, "subnet_200");

        // Calculating with a subnet with an empty expression should override the global expression.
        setSubnetExpression(getSubnet(2), "");
        ASSERT_NO_THROW_LOG(calculated_name = impl_->calculateHostname(pkt, getSubnet(2)));
        EXPECT_EQ(calculated_name, "");
    }

    /// @brief Verifies that expression caching and selection responds properly when exposed
    /// to a subnet that does not have an pre-existing entry in the cache.
    void testNewSubnetScenarios() {
        // Scenarios for the first time a subnet is seen.
        std::vector<Scenario> first_exposure_scenarios = {
            {
                "1 older than lft, no expression",
                "<null>", "<null>", offset_older, "global", no_flush, EXPR_NULL
            },
            {
                "2 older than lft, expression",
                "<null>", "'use me'", offset_older, "use me", no_flush, EXPR_VALID
            },
            {
                "3 older than lft, empty expression",
                "<null>", "", offset_older, "", no_flush, EXPR_EMPTY
            },
            {
                "4 newer than lft, no expression",
                "<null>", "<null>", offset_newer, "global", flush, EXPR_NULL
            },
            {
                "5 newer than lft, expression",
                "<null>", "'me too'", offset_newer, "me too", flush, EXPR_VALID
            },
            {
                "6 newer than lft, empty expression",
                "<null>", "", offset_newer, "", flush, EXPR_EMPTY
            }
        };

        // Iterate over the scenarios.
        for (auto const& scenario : first_exposure_scenarios) {
            SCOPED_TRACE(scenario.desc_);
            testSubnetExpressionScenario(scenario, false);
        }
    }

    /// @brief Verifies that expression caching and selection responds properly
    /// when exposed to a subnet that has a pre-existing entry in the cache.
    void testExistingSubnetScenarios() {
        // Scenarios for the first time a subnet is seen.
        std::vector<Scenario> second_exposure_scenarios = {
            {
                "1 older than lft, no existing expression, no expression",
                "<null>", "<null>", offset_older, "global", no_flush, EXPR_NULL
            },
            {
                "2 older than lft, no existing expression, expression",
                "<null>", "'not me'", offset_older, "global", no_flush, EXPR_NULL
            },
            {
                "3 older than lft, no existing expression, empty expression",
                "<null>", "", offset_older, "global", no_flush, EXPR_NULL
            },
            {
                "4 older than lft, existing expression, expression",
                "'one'", "'two'", offset_older, "one", no_flush, EXPR_VALID
            },
            {
                "5 newer than lft, no existing expression, no expression",
                "<null>", "<null>", offset_newer, "global", flush, EXPR_NULL
            },
            {
                "6 newer than lft, no existing expression, expression",
                "<null>", "'use me'", offset_newer, "use me", flush, EXPR_VALID
            },
            {
                "7 newer than lft, no existing expression, empty expression",
                "<null>", "", offset_newer, "", flush, EXPR_EMPTY
            },
            {
                "8 newer than lft, existing expression, expression",
                "'one'", "'two'", offset_newer, "two", flush, EXPR_VALID
            }
        };

        // Iterate over the scenarios.
        for (auto const& scenario : second_exposure_scenarios) {
            SCOPED_TRACE(scenario.desc_);
            testSubnetExpressionScenario(scenario, true);
        }
    }

    /// @brief Verifies expression caching and use are correct for a given subnet and packet.
    ///
    /// Prior to executing the scenario, it configures the DdnsTuningImpl with a global literal
    /// expression.  If make_pre_existing is true, it will pre-populate the cache with the
    /// expression specified in Scenario::orig_expr_ by making an initial call to
    /// @c DdnsTuningImpl::calculateHostname.  Finally, it invokes calculateHostname with the
    /// expression specified in Scenario::new_expr_, then verifies that the calculated name
    /// and cache state is as expected.
    ///
    /// @param scenario Scenario structure which describes the test scenario to execute.
    /// @param make_pre_existing when true, the expression cache is pre-populated with an
    /// expression for the given subnet.
    void testSubnetExpressionScenario(struct Scenario const& scenario, bool make_pre_existing = false) {
        SubnetPtr subnet = getSubnet(0);
        PktPtr pkt = getPacket();

        // Configure a simple global expression.
        ElementPtr config = Element::createMap();
        config->set("hostname-expr", Element::create("'global'"));
        ASSERT_NO_THROW_LOG(impl_->configure(config));
        // We should have a global expression.
        ASSERT_EQ(impl_->getCacheSize(), 1);  // global only
        ASSERT_TRUE(impl_->getGlobalHostnameExpression());

        // Flush the cache. Verify it contains only the global expression.
        impl_->flushCache();
        ASSERT_EQ(impl_->getCacheSize(), 1);  // global only
        ASSERT_TRUE(impl_->getGlobalHostnameExpression());

        if (make_pre_existing) {
            // Create first exposure of subnet. This should create the desired
            // cache entry for the subnet.
            setSubnetExpression(subnet, scenario.orig_expr_, offset_newer);

            // Calling calculate should cache the appropriate expression for the subnet.
            ASSERT_NO_THROW_LOG(impl_->calculateHostname(pkt, subnet));
            // Verify we added an entry to the cache.  We'll take it on faith that the
            // expression content is correct. First exposure tests should cover this.
            ASSERT_EQ(impl_->getCacheSize(), 2);
        }

        // Wind clock back 10 seconds.  This ensures we can verify whether
        // or not a flush occurs.
        impl_->tweakLastFlushTime(-10);
        ptime last_flush_time = impl_->getLastFlushTime();

        // Replace the subnet expression.
        setSubnetExpression(subnet, scenario.new_expr_, scenario.mod_time_offset);

        // Calculate the hostname.
        std::string calculated_name = "orig_text";
        ASSERT_NO_THROW_LOG(calculated_name = impl_->calculateHostname(pkt, subnet));

        // Verify that the calculated hostname is correct.
        EXPECT_EQ(calculated_name, scenario.exp_hostname_);

        if (scenario.exp_flush_) {
            EXPECT_GT(impl_->getLastFlushTime(), last_flush_time);
        } else {
            EXPECT_EQ(impl_->getLastFlushTime(), last_flush_time);
        }

        // Verify cache size is correct: global + subnet.
        EXPECT_EQ(impl_->getCacheSize(), 2);

        // Verify the cached expression is what we expect.
        ExpressionPtr cached_expr = impl_->getHostnameExpression(subnet->getID());
        switch (scenario.exp_type_) {
        case EXPR_NULL:
            EXPECT_FALSE(cached_expr);
            break;
        case EXPR_EMPTY:
            ASSERT_TRUE(cached_expr);
            EXPECT_TRUE(cached_expr->empty());
            break;
        case EXPR_VALID:
            ASSERT_TRUE(cached_expr);
            EXPECT_FALSE(cached_expr->empty());
            break;
        }
    }

    /// @brief Exercises repopulateCache() function
    ///
    /// Makes successive calls to DdnsTuningImpl::repopulateCache() and verifies the
    /// cache content and expression errors encountered (if any).
    ///
    /// @tparam CfgSubnetPtrType pointer type of the subnet configuration (CfgSubnets4Ptr or
    /// CfgSubnets6Ptr)
    /// @tparam CfgSubnetType class type of the subnet configuration (CfgSubnets4 or CfgSubnets6)
    /// @tparam SubnetType class type of the subnets in the configuration (Subnet4 or Subnet6)
    template<typename CfgSubnetPtrType, typename CfgSubnetType, typename SubnetType>
    void testRepopulateCache() {
        // First we prepopulate the cached with a global expression and an expression
        // for a soon to be non-existent subnet.
        // Add a global expression.
        ExpressionPtr expression = impl_->parseExpression("'global'");
        impl_->setGlobalHostnameExpression(expression);

        // Add an expression for subnet 999.
        expression = impl_->parseExpression("'999'");
        impl_->setHostnameExpression(999, expression);

        // Cache size should be two.
        EXPECT_EQ(2, impl_->getCacheSize());

        // Verify both expressions are cached correctly.
        ASSERT_EQ(evaluateExpression(0), "global");
        ASSERT_EQ(evaluateExpression(999), "999");

        // Create an empty subnet configuration.
        CfgSubnetPtrType cfg_subnets(new CfgSubnetType());

        // Call repopulateCache() with an empty list of subnets.
        // This should succeed and leave the cache with only the global
        // expression.
        int err_count = 0;
        ASSERT_NO_THROW(err_count = impl_->repopulateCache(cfg_subnets));
        EXPECT_EQ(0, err_count);

        // Make sure global is still there.
        ASSERT_EQ(evaluateExpression(0), "global");

        // Make sure 999 is no longer there.
        ASSERT_EQ(evaluateExpression(999), "");

        // Now let's add four subnets to the configuration.
        cfg_subnets->add(boost::dynamic_pointer_cast<SubnetType>(getSubnet(0)));
        cfg_subnets->add(boost::dynamic_pointer_cast<SubnetType>(getSubnet(1)));
        cfg_subnets->add(boost::dynamic_pointer_cast<SubnetType>(getSubnet(2)));
        cfg_subnets->add(boost::dynamic_pointer_cast<SubnetType>(getSubnet(3)));

        // Add valid expression to each subnet.
        setSubnetExpression(getSubnet(0), "'one'");
        setSubnetExpression(getSubnet(1), "'two'");
        setSubnetExpression(getSubnet(2), "'three'");
        setSubnetExpression(getSubnet(3), "'four'");

        // Verify that we repopulate without any errors.
        ASSERT_NO_THROW(err_count = impl_->repopulateCache(cfg_subnets));
        EXPECT_EQ(0, err_count);

        // Make sure global expresion is still there.
        ASSERT_EQ(evaluateExpression(0), "global");

        // Verify the expression cached for each subnet is correct.
        ASSERT_EQ(evaluateExpression(getSubnet(0)->getID()), "one");
        ASSERT_EQ(evaluateExpression(getSubnet(1)->getID()), "two");
        ASSERT_EQ(evaluateExpression(getSubnet(2)->getID()), "three");
        ASSERT_EQ(evaluateExpression(getSubnet(3)->getID()), "four");

        // Now let's update the subnet expressions, two of which are invalid.
        setSubnetExpression(getSubnet(0), "'one-ok'");
        setSubnetExpression(getSubnet(1), "two-broken");
        setSubnetExpression(getSubnet(2), "'three-ok'");
        setSubnetExpression(getSubnet(3), "four-broken");

        // Verify that we repopulate with two errors reported.
        ASSERT_NO_THROW(err_count = impl_->repopulateCache(cfg_subnets));
        EXPECT_EQ(2, err_count);

        // Make sure global is still there.
        ASSERT_EQ(evaluateExpression(0), "global");

        // Verify the expressions cached for one and three are updated,
        // and two and four are empty.
        ASSERT_EQ(evaluateExpression(getSubnet(0)->getID()), "one-ok");
        ASSERT_EQ(evaluateExpression(getSubnet(1)->getID()), "");
        ASSERT_EQ(evaluateExpression(getSubnet(2)->getID()), "three-ok");
        ASSERT_EQ(evaluateExpression(getSubnet(3)->getID()), "");
    }

    /// @brief Flex Option implementation.
    boost::shared_ptr<TestDdnsTuningImpl> impl_;

    /// @brief Holds pointers to subnets used in tests.
    std::vector<SubnetPtr> test_subnets_;
};

/// @brief Test fixture for testing the DDNS Tuning library.
class DdnsTuningImplTest4 : public DdnsTuningImplTest {
public:
    /// @brief Constructor.
    DdnsTuningImplTest4() : DdnsTuningImplTest(AF_INET) {
    }

    /// @brief Initializes the test after construction.
    virtual void SetUp() {
        ASSERT_EQ(impl_->getFamily(), AF_INET);
        initTestSubnets();
    }

    /// @brief Destructor.
    virtual ~DdnsTuningImplTest4() {
    }

    /// @brief Construct a new V4 packet.
    /// @return Pointer to the new packet.
    virtual PktPtr getPacket() {
        return (Pkt4Ptr(new Pkt4(DHCPDISCOVER, 12345)));
    }

    /// @brief Initialize the subnets used during testing.
    void initTestSubnets() {
        ElementPtr user_context = Element::createMap();
        Subnet4Ptr subnet(new Subnet4(IOAddress("192.0.10.0"), 24, 30, 40, 60, 100));
        subnet->setContext(user_context);
        test_subnets_.push_back(subnet);

        user_context = Element::createMap();
        subnet.reset(new Subnet4(IOAddress("192.0.20.0"), 24, 30, 40, 60, 200));
        subnet->setContext(user_context);
        test_subnets_.push_back(subnet);

        user_context = Element::createMap();
        subnet.reset(new Subnet4(IOAddress("192.0.30.0"), 24, 30, 40, 60, 300));
        subnet->setContext(user_context);
        test_subnets_.push_back(subnet);

        user_context = Element::createMap();
        subnet.reset(new Subnet4(IOAddress("192.0.40.0"), 24, 30, 40, 60, 400));
        subnet->setContext(user_context);
        test_subnets_.push_back(subnet);
    }

};

/// @brief Test fixture for testing the DDNS Tuning library.
class DdnsTuningImplTest6 : public DdnsTuningImplTest {
public:
    /// @brief Constructor.
    DdnsTuningImplTest6() : DdnsTuningImplTest(AF_INET6) {
    }

    /// @brief Initializes the test after construction.
    virtual void SetUp() {
        ASSERT_EQ(impl_->getFamily(), AF_INET6);
        initTestSubnets();
    }

    /// @brief Destructor.
    virtual ~DdnsTuningImplTest6() {
    }

    /// @brief Construct a new V6 packet.
    /// @return Pointer to the new packet.
    virtual PktPtr getPacket() {
        return (Pkt6Ptr(new Pkt6(DHCPV6_SOLICIT, 12345)));
    }

    /// @brief Initialize the subnets used during testing.
    void initTestSubnets() {
        ElementPtr user_context = Element::createMap();
        Subnet6Ptr subnet(new Subnet6(IOAddress("3001:1::"), 64, 30, 40, 50, 60, 100));
        subnet->setContext(user_context);
        test_subnets_.push_back(subnet);

        user_context = Element::createMap();
        subnet.reset(new Subnet6(IOAddress("3001:2::"), 64, 30, 40, 50, 60, 200));
        subnet->setContext(user_context);
        test_subnets_.push_back(subnet);

        user_context = Element::createMap();
        subnet.reset(new Subnet6(IOAddress("3001:3::"), 64, 30, 40, 50, 60, 300));
        subnet->setContext(user_context);
        test_subnets_.push_back(subnet);

        user_context = Element::createMap();
        subnet.reset(new Subnet6(IOAddress("3001:4::"), 64, 30, 40, 50, 60, 400));
        subnet->setContext(user_context);
        test_subnets_.push_back(subnet);
    }
};

TEST_F(DdnsTuningImplTest4, invalidConfigs) {
    testInvalidConfigs();
}

TEST_F(DdnsTuningImplTest4, invalidConfigsMultiThreading) {
    MultiThreadingTest mt(true);
    testInvalidConfigs();
}

TEST_F(DdnsTuningImplTest6, invalidConfigs) {
    testInvalidConfigs();
}

TEST_F(DdnsTuningImplTest6, invalidConfigsMultiThreading) {
    MultiThreadingTest mt(true);
    testInvalidConfigs();
}

TEST_F(DdnsTuningImplTest4, emptyConfig) {
    testEmptyConfigs();
}

TEST_F(DdnsTuningImplTest4, emptyConfigMultiThreading) {
    MultiThreadingTest mt(true);
    testEmptyConfigs();
}

TEST_F(DdnsTuningImplTest6, emptyConfig) {
    testEmptyConfigs();
}

TEST_F(DdnsTuningImplTest6, emptyConfigMultiThreading) {
    MultiThreadingTest mt(true);
    testEmptyConfigs();
}

TEST_F(DdnsTuningImplTest4, validGlobalExpression) {
    testValidGlobalExpression();
}

TEST_F(DdnsTuningImplTest4, validGlobalExpressionMultiThreading) {
    MultiThreadingTest mt(true);
    testValidGlobalExpression();
}

TEST_F(DdnsTuningImplTest6, validGlobalExpression) {
    testValidGlobalExpression();
}

TEST_F(DdnsTuningImplTest6, validGlobalExpressionMultiThreading) {
    MultiThreadingTest mt(true);
    testValidGlobalExpression();
}

TEST_F(DdnsTuningImplTest4, validSubnetExpression) {
    testValidSubnetExpression();
}

TEST_F(DdnsTuningImplTest4, validSubnetExpressionMultiThreading) {
    MultiThreadingTest mt(true);
    testValidSubnetExpression();
}

TEST_F(DdnsTuningImplTest6, validSubnetExpression) {
    testValidSubnetExpression();
}

TEST_F(DdnsTuningImplTest6, validSubnetExpressionMultiThreading) {
    MultiThreadingTest mt(true);
    testValidSubnetExpression();
}

TEST_F(DdnsTuningImplTest4, globalAndSubnetExpressions) {
    testGlobalAndSubnetExpressions();
}

TEST_F(DdnsTuningImplTest4, globalAndSubnetExpressionsMultiThreading) {
    MultiThreadingTest mt(true);
    testGlobalAndSubnetExpressions();
}

TEST_F(DdnsTuningImplTest6, globalAndSubnetExpressions) {
    testGlobalAndSubnetExpressions();
}

TEST_F(DdnsTuningImplTest6, globalAndSubnetExpressionsMultiThreading) {
    MultiThreadingTest mt(true);
    testGlobalAndSubnetExpressions();
}

TEST_F(DdnsTuningImplTest4, newSubnetScenarios) {
    testNewSubnetScenarios();
}

TEST_F(DdnsTuningImplTest4, newSubnetScenariosMultiThreading) {
    MultiThreadingTest mt(true);
    testNewSubnetScenarios();
}

TEST_F(DdnsTuningImplTest6, newSubnetScenarios) {
    testNewSubnetScenarios();
}

TEST_F(DdnsTuningImplTest6, newSubnetScenariosMultiThreading) {
    MultiThreadingTest mt(true);
    testNewSubnetScenarios();
}

TEST_F(DdnsTuningImplTest4, existingSubnetScenarios) {
    testExistingSubnetScenarios();
}

TEST_F(DdnsTuningImplTest4, existingSubnetScenariosMultiThreading) {
    MultiThreadingTest mt(true);
    testExistingSubnetScenarios();
}

TEST_F(DdnsTuningImplTest6, existingSubnetScenarios) {
    testExistingSubnetScenarios();
}

TEST_F(DdnsTuningImplTest6, existingSubnetScenariosMultiThreading) {
    MultiThreadingTest mt(true);
    testExistingSubnetScenarios();
}

TEST_F(DdnsTuningImplTest4, repopulateCache) {
    testRepopulateCache<CfgSubnets4Ptr, CfgSubnets4, Subnet4>();
}

TEST_F(DdnsTuningImplTest4, repopulateCacheMultiThreading) {
    MultiThreadingTest mt(true);
    testRepopulateCache<CfgSubnets4Ptr, CfgSubnets4, Subnet4>();
}

TEST_F(DdnsTuningImplTest6, repopulateCache) {
    testRepopulateCache<CfgSubnets6Ptr, CfgSubnets6, Subnet6>();
}

TEST_F(DdnsTuningImplTest6, repopulateCacheMuliThreading) {
    MultiThreadingTest mt(true);
    testRepopulateCache<CfgSubnets6Ptr, CfgSubnets6, Subnet6>();
}

} // end of anonymous namespace
