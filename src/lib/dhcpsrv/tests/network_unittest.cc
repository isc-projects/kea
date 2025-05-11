// Copyright (C) 2019-2024 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <asiolink/io_address.h>
#include <cc/data.h>
#include <dhcp/dhcp6.h>
#include <dhcp/option.h>
#include <dhcpsrv/network.h>
#include <dhcpsrv/parsers/base_network_parser.h>
#include <testutils/gtest_utils.h>
#include <boost/shared_ptr.hpp>
#include <functional>
#include <gtest/gtest.h>

using namespace isc::asiolink;
using namespace isc::data;
using namespace isc::dhcp;
using namespace isc::util;
using namespace isc::test;

namespace {

class TestNetwork;

/// @brief Shared pointer to the derivation of the @c Network class
/// used in tests.
typedef boost::shared_ptr<TestNetwork> TestNetworkPtr;

/// @brief Derivation of the @c Network class allowing to set
/// the parent @c Network object.
class TestNetwork : public virtual Network {
public:

    /// @brief Associates parent network with this network.
    ///
    /// @param parent Pointer to the instance of the parent network.
    void setParent(TestNetworkPtr parent) {
        parent_network_ = boost::dynamic_pointer_cast<Network>(parent);
    }
};

/// @brief Derivation of the @c Network4 class allowing to set
/// the parent @c Network object.
class TestNetwork4 : public TestNetwork, public Network4 { };

/// @brief Derivation of the @c Network6 class allowing to set
/// the parent @c Network object.
class TestNetwork6 : public TestNetwork, public Network6 { };

/// @brief Test fixture class for testing @c Network class and
/// its derivations.
class NetworkTest : public ::testing::Test {
public:

    /// @brief Constructor.
    NetworkTest() : globals_(new CfgGlobals()) {
    }

    /// @brief Returns pointer to the function which returns configured
    /// global parameters.
    FetchNetworkGlobalsFn getFetchGlobalsFn() {
        return (std::bind(&NetworkTest::fetchGlobalsFn, this));
    }

    /// @brief Returns configured global parameters.
    ConstCfgGlobalsPtr fetchGlobalsFn() {
        return (globals_);
    }

    /// @brief Test that inheritance mechanism is used for the particular
    /// network parameter.
    ///
    /// @tparam BaseType1 Type of the network object to be tested, e.g.
    /// @c TestNetwork, @c TestNetwork4 etc.
    /// @tparam BaseType2 Type of the object to which the tested parameter
    /// belongs, e.g. @c Network, @c Network4 etc.
    /// @tparam ParameterType1 Type returned by the accessor of the parameter
    /// under test, e.g. @c Optional<std::string>.
    /// @tparam ParameterType2 Type of the value accepted by the modifier
    /// method which sets the value under test. It may be the same as
    /// @c ParameterType1 but not necessarily. For example, the @c ParameterType1
    /// may be @c Optional<std::string> while the @c ParameterType2 is
    /// @c std::string.
    ///
    /// @param GetMethodPointer Pointer to the method of the class under test
    /// which returns the particular parameter.
    /// @param SetMethodPointer Pointer to the method of the class under test
    /// used to set the particular parameter.
    /// @param network_value Value of the parameter to be assigned to the
    /// parent network.
    /// @param global_value Global value of the parameter to be assigned.
    /// @param test_global_value Boolean value indicating if the inheritance
    /// of the global value should be tested.
    template<typename BaseType1, typename BaseType2, typename ParameterType1,
             typename ParameterType2>
    void testNetworkInheritance(ParameterType1(BaseType2::*GetMethodPointer)
                                (const Network::Inheritance&) const,
                                void(BaseType2::*SetMethodPointer)(const ParameterType2&),
                                typename ParameterType1::ValueType network_value,
                                typename ParameterType1::ValueType global_value,
                                const bool test_global_value = true) {

        // Create child network object. The value retrieved from that
        // object should be unspecified until we set the value for the
        // parent network or a global value.
        boost::shared_ptr<BaseType1> net_child(new BaseType1());
        EXPECT_TRUE(((*net_child).*GetMethodPointer)(Network::Inheritance::ALL).unspecified());

        // Create parent network and set the value.
        boost::shared_ptr<BaseType1> net_parent(new BaseType1());
        ((*net_parent).*SetMethodPointer)(network_value);
        EXPECT_EQ(network_value,
                  ((*net_parent).*GetMethodPointer)(Network::Inheritance::ALL).get());

        // Assign callbacks that fetch global values to the networks.
        net_child->setFetchGlobalsFn(getFetchGlobalsFn());
        net_parent->setFetchGlobalsFn(getFetchGlobalsFn());

        // Not all parameters have the corresponding global values.
        if (test_global_value) {
            // If there is a global value it should now be returned.
            EXPECT_FALSE(((*net_child).*GetMethodPointer)(Network::Inheritance::ALL).unspecified());
            EXPECT_EQ(global_value,
                      ((*net_child).*GetMethodPointer)(Network::Inheritance::ALL).get());

            EXPECT_FALSE(((*net_child).*GetMethodPointer)(Network::Inheritance::GLOBAL).unspecified());
            EXPECT_EQ(global_value,
                      ((*net_child).*GetMethodPointer)(Network::Inheritance::GLOBAL).get());

            EXPECT_TRUE(((*net_child).*GetMethodPointer)(Network::Inheritance::NONE).unspecified());
            EXPECT_TRUE(((*net_child).*GetMethodPointer)(Network::Inheritance::PARENT_NETWORK).unspecified());
        }

        // Associated the network with its parent.
        ASSERT_NO_THROW(net_child->setParent(net_parent));

        // This time the parent specific value should be returned.
        EXPECT_FALSE(((*net_child).*GetMethodPointer)(Network::Inheritance::ALL).unspecified());
        EXPECT_EQ(network_value,
                  ((*net_child).*GetMethodPointer)(Network::Inheritance::ALL).get());
    }

    /// @brief Holds the collection of configured globals.
    CfgGlobalsPtr globals_;
};

// This test verifies that the inheritance is supported for certain
// network parameters.
TEST_F(NetworkTest, inheritanceSupport4) {
    // Set global values for each parameter.
    // One day move to indexes...
    globals_->set("valid-lifetime", Element::create(80));
    globals_->set("renew-timer", Element::create(80));
    globals_->set("rebind-timer", Element::create(80));
    globals_->set("reservations-global", Element::create(false));
    globals_->set("reservations-in-subnet", Element::create(false));
    globals_->set("reservations-out-of-pool", Element::create(false));
    globals_->set("calculate-tee-times", Element::create(false));
    globals_->set("t1-percent", Element::create(0.75));
    globals_->set("t2-percent", Element::create(0.6));
    globals_->set("match-client-id", Element::create(true));
    globals_->set("authoritative", Element::create(false));
    globals_->set("next-server", Element::create("192.0.2.3"));
    globals_->set("server-hostname", Element::create("g"));
    globals_->set("boot-file-name", Element::create("g"));
    globals_->set("ddns-send-updates", Element::create(true));
    globals_->set("ddns-override-no-update", Element::create(true));
    globals_->set("ddns-override-client-update", Element::create(true));
    globals_->set("ddns-replace-client-name", Element::create("always"));
    globals_->set("ddns-generated-prefix", Element::create("gp"));
    globals_->set("ddns-qualifying-suffix", Element::create("gs"));
    globals_->set("hostname-char-set", Element::create("gc"));
    globals_->set("hostname-char-replacement", Element::create("gr"));
    globals_->set("store-extended-info", Element::create(true));
    globals_->set("cache-threshold", Element::create(.25));
    globals_->set("cache-max-age", Element::create(20));
    globals_->set("ddns-update-on-renew", Element::create(true));
    globals_->set("ddns-conflict-resolution-mode", Element::create("check-with-dhcid"));
    globals_->set("allocator", Element::create("random"));
    globals_->set("offer-lifetime", Element::create(45));
    globals_->set("ddns-ttl-percent", Element::create(0.75));
    globals_->set("ddns-ttl", Element::create(400));
    globals_->set("ddns-ttl-min", Element::create(200));
    globals_->set("ddns-ttl-max", Element::create(600));

    // For each parameter for which inheritance is supported run
    // the test that checks if the values are inherited properly.
    {
        SCOPED_TRACE("valid-lifetime");
        testNetworkInheritance<TestNetwork>(&Network::getValid, &Network::setValid,
                                            60, 80);
    }
    {
        SCOPED_TRACE("renew-timer");
        testNetworkInheritance<TestNetwork>(&Network::getT1, &Network::setT1,
                                            60, 80);
    }
    {
        SCOPED_TRACE("rebind-timer");
        testNetworkInheritance<TestNetwork>(&Network::getT2, &Network::setT2,
                                            60, 80);
    }
    {
        SCOPED_TRACE("reservation-global");
        testNetworkInheritance<TestNetwork>(&Network::getReservationsGlobal,
                                            &Network::setReservationsGlobal,
                                            true, false);
    }
    {
        SCOPED_TRACE("reservation-in-subnet");
        testNetworkInheritance<TestNetwork>(&Network::getReservationsInSubnet,
                                            &Network::setReservationsInSubnet,
                                            true, false);
    }
    {
        SCOPED_TRACE("reservation-out-of-pool");
        testNetworkInheritance<TestNetwork>(&Network::getReservationsOutOfPool,
                                            &Network::setReservationsOutOfPool,
                                            true, false);
    }
    {
        SCOPED_TRACE("calculate-tee-times");
        testNetworkInheritance<TestNetwork>(&Network::getCalculateTeeTimes,
                                            &Network::setCalculateTeeTimes,
                                            true, false);
    }
    {
        SCOPED_TRACE("t1-percent");
        testNetworkInheritance<TestNetwork>(&Network::getT1Percent,
                                            &Network::setT1Percent,
                                            0.5, 0.75);
    }
    {
        SCOPED_TRACE("t2-percent");
        testNetworkInheritance<TestNetwork>(&Network::getT2Percent,
                                            &Network::setT2Percent,
                                            0.3, 0.6);
    }
    {
        SCOPED_TRACE("match-client-id");
        testNetworkInheritance<TestNetwork4>(&Network4::getMatchClientId,
                                             &Network4::setMatchClientId,
                                             false, true);
    }
    {
        SCOPED_TRACE("authoritative");
        testNetworkInheritance<TestNetwork4>(&Network4::getAuthoritative,
                                             &Network4::setAuthoritative,
                                             true, false);
    }
    {
        SCOPED_TRACE("next-server");
        testNetworkInheritance<TestNetwork4>(&Network4::getSiaddr,
                                             &Network4::setSiaddr,
                                             IOAddress("192.0.2.0"),
                                             IOAddress("192.0.2.3"));
    }
    {
        SCOPED_TRACE("server-hostname");
        testNetworkInheritance<TestNetwork4>(&Network4::getSname,
                                             &Network4::setSname,
                                             "n", "g");
    }
    {
        SCOPED_TRACE("boot-file-name");
        testNetworkInheritance<TestNetwork4>(&Network4::getFilename,
                                             &Network4::setFilename,
                                             "n", "g");
    }
    {
        SCOPED_TRACE("ddns-send-updates");
        testNetworkInheritance<TestNetwork4>(&Network4::getDdnsSendUpdates,
                                             &Network4::setDdnsSendUpdates,
                                             false, true);
    }
    {
        SCOPED_TRACE("ddns-override-no-update");
        testNetworkInheritance<TestNetwork4>(&Network4::getDdnsOverrideNoUpdate,
                                             &Network4::setDdnsOverrideNoUpdate,
                                             false, true);
    }
    {
        SCOPED_TRACE("ddns-override-client-update");
        testNetworkInheritance<TestNetwork4>(&Network4::getDdnsOverrideClientUpdate,
                                             &Network4::setDdnsOverrideClientUpdate,
                                             false, true);
    }

    {
        SCOPED_TRACE("ddns-replace-client-name");
        testNetworkInheritance<TestNetwork4>(&Network4::getDdnsReplaceClientNameMode,
                                             &Network4::setDdnsReplaceClientNameMode,
                                             D2ClientConfig::RCM_WHEN_PRESENT,
                                             D2ClientConfig::RCM_ALWAYS);
    }
    {
        SCOPED_TRACE("ddns-generated-prefix");
        testNetworkInheritance<TestNetwork4>(&Network4::getDdnsGeneratedPrefix,
                                             &Network4::setDdnsGeneratedPrefix,
                                             "np", "gp");
    }
    {
        SCOPED_TRACE("ddns-qualifying-suffix");
        testNetworkInheritance<TestNetwork4>(&Network4::getDdnsQualifyingSuffix,
                                             &Network4::setDdnsQualifyingSuffix,
                                             "ns", "gs");
    }
    {
        SCOPED_TRACE("hostname-char-set");
        testNetworkInheritance<TestNetwork4>(&Network4::getHostnameCharSet,
                                             &Network4::setHostnameCharSet,
                                             "nc", "gc");
    }
    {
        SCOPED_TRACE("hostname-char-replacement");
        testNetworkInheritance<TestNetwork4>(&Network4::getHostnameCharReplacement,
                                             &Network4::setHostnameCharReplacement,
                                             "nr", "gr");
    }
    {
        SCOPED_TRACE("store-extended-info");
        testNetworkInheritance<TestNetwork4>(&Network4::getStoreExtendedInfo,
                                             &Network4::setStoreExtendedInfo,
                                             false, true);
    }
    {
        SCOPED_TRACE("cache-threshold");
        testNetworkInheritance<TestNetwork4>(&Network::getCacheThreshold,
                                             &Network::setCacheThreshold,
                                             .1, .25);
    }
    {
        SCOPED_TRACE("cache-max-age");
        testNetworkInheritance<TestNetwork4>(&Network::getCacheMaxAge,
                                             &Network::setCacheMaxAge,
                                             10, 20);
    }
    {
        SCOPED_TRACE("ddns-update-on-renew");
        testNetworkInheritance<TestNetwork4>(&Network4::getDdnsUpdateOnRenew,
                                             &Network4::setDdnsUpdateOnRenew,
                                             false, true);
    }
    {
        SCOPED_TRACE("ddns-conflict-resolution-mode");
        testNetworkInheritance<TestNetwork4>(&Network4::getDdnsConflictResolutionMode,
                                             &Network4::setDdnsConflictResolutionMode,
                                             "no-check-with-dhcid", "check-with-dhcid");
    }
    {
        SCOPED_TRACE("allocator");
        testNetworkInheritance<TestNetwork4>(&Network4::getAllocatorType,
                                             &Network4::setAllocatorType,
                                             "iterative", "random");
    }
    {
        SCOPED_TRACE("default-allocator-type");
        testNetworkInheritance<TestNetwork4>(&Network::getDefaultAllocatorType,
                                             &Network::setDefaultAllocatorType,
                                             "random", "flq", false);
    }
    {
        SCOPED_TRACE("offer-lifetime");
        testNetworkInheritance<TestNetwork4>(&Network4::getOfferLft,
                                             &Network4::setOfferLft,
                                             10, 45);
    }
    {
        SCOPED_TRACE("ddns-ttl-percent");
        testNetworkInheritance<TestNetwork4>(&Network::getDdnsTtlPercent,
                                             &Network::setDdnsTtlPercent,
                                             .33, .75);
    }
    {
        SCOPED_TRACE("ddns-ttl");
        testNetworkInheritance<TestNetwork4>(&Network::getDdnsTtl,
                                             &Network::setDdnsTtl,
                                             300, 400);
    }
    {
        SCOPED_TRACE("ddns-ttl-min");
        testNetworkInheritance<TestNetwork4>(&Network::getDdnsTtlMin,
                                             &Network::setDdnsTtlMin,
                                             100, 200);
    }
    {
        SCOPED_TRACE("ddns-ttl-max");
        testNetworkInheritance<TestNetwork4>(&Network::getDdnsTtlMax,
                                             &Network::setDdnsTtlMax,
                                             500, 600);
    }
}

// This test verifies that the inheritance is supported for DHCPv6
// specific network parameters.
TEST_F(NetworkTest, inheritanceSupport6) {
    // Set global values for each parameter.
    globals_->set("preferred-lifetime", Element::create(80));
    // Note that currently rapid commit is not a global parameter.
    globals_->set("ddns-send-updates", Element::create(true));
    globals_->set("ddns-override-no-update", Element::create(true));
    globals_->set("ddns-override-client-update", Element::create(true));
    globals_->set("ddns-replace-client-name", Element::create("always"));
    globals_->set("ddns-generated-prefix", Element::create("gp"));
    globals_->set("ddns-qualifying-suffix", Element::create("gs"));
    globals_->set("hostname-char-set", Element::create("gc"));
    globals_->set("hostname-char-replacement", Element::create("gr"));
    globals_->set("store-extended-info", Element::create(true));
    globals_->set("ddns-update-on-renew", Element::create(true));
    globals_->set("allocator", Element::create("random"));
    globals_->set("pd-allocator", Element::create("random"));
    globals_->set("ddns-ttl-percent", Element::create(0.55));
    globals_->set("ddns-conflict-resolution-mode", Element::create("check-with-dhcid"));
    globals_->set("ddns-ttl", Element::create(400));
    globals_->set("ddns-ttl-min", Element::create(200));
    globals_->set("ddns-ttl-max", Element::create(600));

    // For each parameter for which inheritance is supported run
    // the test that checks if the values are inherited properly.

    {
        SCOPED_TRACE("preferred-lifetime");
        testNetworkInheritance<TestNetwork6>(&Network6::getPreferred,
                                             &Network6::setPreferred,
                                             60, 80);
    }
    {
        SCOPED_TRACE("ddns-send-updates");
        testNetworkInheritance<TestNetwork6>(&Network6::getDdnsSendUpdates,
                                             &Network6::setDdnsSendUpdates,
                                             false, true);
    }
    {
        SCOPED_TRACE("ddns-override-no-update");
        testNetworkInheritance<TestNetwork6>(&Network6::getDdnsOverrideNoUpdate,
                                             &Network6::setDdnsOverrideNoUpdate,
                                             false, true);
    }
    {
        SCOPED_TRACE("ddns-override-client-update");
        testNetworkInheritance<TestNetwork6>(&Network6::getDdnsOverrideClientUpdate,
                                             &Network6::setDdnsOverrideClientUpdate,
                                             false, true);
    }

    {
        SCOPED_TRACE("ddns-replace-client-name");
        testNetworkInheritance<TestNetwork6>(&Network6::getDdnsReplaceClientNameMode,
                                             &Network6::setDdnsReplaceClientNameMode,
                                             D2ClientConfig::RCM_WHEN_PRESENT,
                                             D2ClientConfig::RCM_ALWAYS);
    }
    {
        SCOPED_TRACE("ddns-generated-prefix");
        testNetworkInheritance<TestNetwork6>(&Network6::getDdnsGeneratedPrefix,
                                             &Network6::setDdnsGeneratedPrefix,
                                             "np", "gp");
    }
    {
        SCOPED_TRACE("ddns-qualifying-suffix");
        testNetworkInheritance<TestNetwork6>(&Network6::getDdnsQualifyingSuffix,
                                             &Network6::setDdnsQualifyingSuffix,
                                             "ns", "gs");
    }
    {
        SCOPED_TRACE("hostname-char-set");
        testNetworkInheritance<TestNetwork6>(&Network6::getHostnameCharSet,
                                             &Network6::setHostnameCharSet,
                                             "nc", "gc");
    }
    {
        SCOPED_TRACE("hostname-char-replacement");
        testNetworkInheritance<TestNetwork6>(&Network6::getHostnameCharReplacement,
                                             &Network6::setHostnameCharReplacement,
                                             "nr", "gr");
    }
    {
        SCOPED_TRACE("store-extended-info");
        testNetworkInheritance<TestNetwork6>(&Network6::getStoreExtendedInfo,
                                             &Network6::setStoreExtendedInfo,
                                             false, true);
    }
    {
        SCOPED_TRACE("ddns-update-on-renew");
        testNetworkInheritance<TestNetwork6>(&Network6::getDdnsUpdateOnRenew,
                                             &Network6::setDdnsUpdateOnRenew,
                                             false, true);
    }
    {
        SCOPED_TRACE("ddns-conflict-resolution-mode");
        testNetworkInheritance<TestNetwork6>(&Network6::getDdnsConflictResolutionMode,
                                             &Network6::setDdnsConflictResolutionMode,
                                             "no-check-with-dhcid", "check-with-dhcid");
    }
    {
        SCOPED_TRACE("allocator");
        testNetworkInheritance<TestNetwork6>(&Network6::getAllocatorType,
                                             &Network6::setAllocatorType,
                                             "iterative", "random");
    }
    {
        SCOPED_TRACE("pd-allocator");
        testNetworkInheritance<TestNetwork6>(&Network6::getPdAllocatorType,
                                             &Network6::setPdAllocatorType,
                                             "iterative", "random");
    }
    {
        SCOPED_TRACE("default-allocator-type");
        testNetworkInheritance<TestNetwork6>(&Network::getDefaultAllocatorType,
                                             &Network::setDefaultAllocatorType,
                                             "random", "iterative", false);
    }
    {
        SCOPED_TRACE("default-pd-allocator-type");
        testNetworkInheritance<TestNetwork6>(&Network6::getDefaultPdAllocatorType,
                                             &Network6::setDefaultPdAllocatorType,
                                             "random", "iterative", false);
    }
    {
        SCOPED_TRACE("ddns-ttl-percent");
        testNetworkInheritance<TestNetwork6>(&Network::getDdnsTtlPercent,
                                             &Network::setDdnsTtlPercent,
                                             .22, .55);
    }
    {
        SCOPED_TRACE("ddns-ttl");
        testNetworkInheritance<TestNetwork6>(&Network::getDdnsTtl,
                                             &Network::setDdnsTtl,
                                             300, 400);
    }
    {
        SCOPED_TRACE("ddns-ttl-min");
        testNetworkInheritance<TestNetwork6>(&Network::getDdnsTtlMin,
                                             &Network::setDdnsTtlMin,
                                             100, 200);
    }
    {
        SCOPED_TRACE("ddns-ttl-max");
        testNetworkInheritance<TestNetwork6>(&Network::getDdnsTtlMax,
                                             &Network::setDdnsTtlMax,
                                             500, 600);
    }

    // Interface-id requires special type of test.
    boost::shared_ptr<TestNetwork6> net_child(new TestNetwork6());
    EXPECT_FALSE(net_child->getInterfaceId());
    EXPECT_FALSE(net_child->getInterfaceId(Network::Inheritance::NONE));
    EXPECT_FALSE(net_child->getInterfaceId(Network::Inheritance::PARENT_NETWORK));
    EXPECT_FALSE(net_child->getInterfaceId(Network::Inheritance::GLOBAL));

    OptionPtr interface_id(new Option(Option::V6, D6O_INTERFACE_ID,
                                      OptionBuffer(10, 0xFF)));

    boost::shared_ptr<TestNetwork6> net_parent(new TestNetwork6());
    net_parent->setInterfaceId(interface_id);

    ASSERT_NO_THROW(net_child->setParent(net_parent));

    // The interface-id belongs to the parent.
    EXPECT_TRUE(net_child->getInterfaceId());
    EXPECT_FALSE(net_child->getInterfaceId(Network::Inheritance::NONE));
    EXPECT_TRUE(net_child->getInterfaceId(Network::Inheritance::PARENT_NETWORK));
    EXPECT_FALSE(net_child->getInterfaceId(Network::Inheritance::GLOBAL));

    // Check the values are expected.
    EXPECT_EQ(interface_id, net_child->getInterfaceId());
    EXPECT_EQ(interface_id, net_child->getInterfaceId(Network::Inheritance::PARENT_NETWORK));

    // Assign different interface id to a child.
    interface_id.reset(new Option(Option::V6, D6O_INTERFACE_ID,
                                  OptionBuffer(10, 0xFE)));
    net_child->setInterfaceId(interface_id);

    // This time, the child specific value can be fetched.
    EXPECT_TRUE(net_child->getInterfaceId());
    EXPECT_TRUE(net_child->getInterfaceId(Network::Inheritance::NONE));
    EXPECT_TRUE(net_child->getInterfaceId(Network::Inheritance::PARENT_NETWORK));
    EXPECT_FALSE(net_child->getInterfaceId(Network::Inheritance::GLOBAL));

    EXPECT_EQ(interface_id, net_child->getInterfaceId());
    EXPECT_EQ(interface_id, net_child->getInterfaceId(Network::Inheritance::NONE));
}

// Test that child network returns unspecified value if neither
// parent no global value exists.
TEST_F(NetworkTest, getPropertyNoParentNoChild) {
    NetworkPtr net_child(new Network());
    EXPECT_TRUE(net_child->getValid().unspecified());
}

// Test that child network returns specified value.
TEST_F(NetworkTest, getPropertyNoParentChild) {
    NetworkPtr net_child(new Network());
    net_child->setValid(12345);

    EXPECT_FALSE(net_child->getValid().unspecified());
    EXPECT_FALSE(net_child->getValid(Network::Inheritance::NONE).unspecified());
    EXPECT_TRUE(net_child->getValid(Network::Inheritance::PARENT_NETWORK).unspecified());
    EXPECT_TRUE(net_child->getValid(Network::Inheritance::GLOBAL).unspecified());

    EXPECT_EQ(12345, net_child->getValid(Network::Inheritance::NONE).get());
    EXPECT_EQ(12345, net_child->getValid().get());
}

// Test that parent specific value is returned when the value
// is not specified for the child network.
TEST_F(NetworkTest, getPropertyParentNoChild) {
    TestNetworkPtr net_child(new TestNetwork());
    EXPECT_TRUE(net_child->getValid().unspecified());

    TestNetworkPtr net_parent(new TestNetwork());
    net_parent->setValid(23456);
    EXPECT_EQ(23456, net_parent->getValid().get());

    ASSERT_NO_THROW(net_child->setParent(net_parent));

    EXPECT_FALSE(net_child->getValid().unspecified());
    EXPECT_TRUE(net_child->getValid(Network::Inheritance::NONE).unspecified());
    EXPECT_FALSE(net_child->getValid(Network::Inheritance::PARENT_NETWORK).unspecified());
    EXPECT_TRUE(net_child->getValid(Network::Inheritance::GLOBAL).unspecified());

    EXPECT_EQ(23456, net_child->getValid().get());
}

// Test that value specified for the child network takes
// precedence over the value specified for the parent network.
TEST_F(NetworkTest, getPropertyParentChild) {
    TestNetworkPtr net_child(new TestNetwork());
    net_child->setValid(12345);
    EXPECT_EQ(12345, net_child->getValid().get());

    TestNetworkPtr net_parent(new TestNetwork());
    net_parent->setValid(23456);
    EXPECT_EQ(23456, net_parent->getValid().get());

    ASSERT_NO_THROW(net_child->setParent(net_parent));

    EXPECT_FALSE(net_child->getValid().unspecified());
    EXPECT_FALSE(net_child->getValid(Network::Inheritance::NONE).unspecified());
    EXPECT_FALSE(net_child->getValid(Network::Inheritance::PARENT_NETWORK).unspecified());
    EXPECT_TRUE(net_child->getValid(Network::Inheritance::GLOBAL).unspecified());

    EXPECT_EQ(12345, net_child->getValid().get());
}

// Test that global value is inherited if there is no network
// specific value.
TEST_F(NetworkTest, getPropertyGlobalNoParentNoChild) {
    TestNetworkPtr net_child(new TestNetwork());

    globals_->set("valid-lifetime", Element::create(34567));

    net_child->setFetchGlobalsFn(getFetchGlobalsFn());

    EXPECT_FALSE(net_child->getValid().unspecified());
    EXPECT_TRUE(net_child->getValid(Network::Inheritance::NONE).unspecified());
    EXPECT_TRUE(net_child->getValid(Network::Inheritance::PARENT_NETWORK).unspecified());
    EXPECT_FALSE(net_child->getValid(Network::Inheritance::GLOBAL).unspecified());

    EXPECT_EQ(34567, net_child->getValid().get());
}

// Test that getSiaddr() never fails.
TEST_F(NetworkTest, getSiaddrNeverFail) {
    TestNetworkPtr net_child(new TestNetwork4());

    // Set the next-server textual address to the empty string.
    // Note that IOAddress("") throws IOError.
    globals_->set("next-server", Element::create(""));

    net_child->setFetchGlobalsFn(getFetchGlobalsFn());

    // Get an IPv4 view of the test network.
    auto net4_child = boost::dynamic_pointer_cast<Network4>(net_child);
    EXPECT_NO_THROW(net4_child->getSiaddr());
}

// This test verifies that the inheritance is supported for triplets.
// Note that triplets have no comparison operator.
TEST_F(NetworkTest, inheritanceTriplet) {
    NetworkPtr net(new Network());
    EXPECT_TRUE(net->getValid().unspecified());
    EXPECT_TRUE(net->getValid(Network::Inheritance::ALL).unspecified());
    EXPECT_TRUE(net->getValid(Network::Inheritance::GLOBAL).unspecified());

    // Set valid lifetime global parameter.
    globals_->set("valid-lifetime", Element::create(200));
    net->setFetchGlobalsFn(getFetchGlobalsFn());
    EXPECT_FALSE(net->getValid().unspecified());
    EXPECT_FALSE(net->getValid(Network::Inheritance::ALL).unspecified());
    EXPECT_FALSE(net->getValid(Network::Inheritance::GLOBAL).unspecified());
    EXPECT_EQ(200, net->getValid().get());
    EXPECT_EQ(200, net->getValid(Network::Inheritance::ALL).get());
    EXPECT_EQ(200, net->getValid(Network::Inheritance::GLOBAL).get());
    EXPECT_EQ(200, net->getValid().getMin());
    EXPECT_EQ(200, net->getValid(Network::Inheritance::ALL).getMin());
    EXPECT_EQ(200, net->getValid(Network::Inheritance::GLOBAL).getMin());
    EXPECT_EQ(200, net->getValid().getMax());
    EXPECT_EQ(200, net->getValid(Network::Inheritance::ALL).getMax());
    EXPECT_EQ(200, net->getValid(Network::Inheritance::GLOBAL).getMax());

    // Set all valid lifetime global parameters.
    globals_->set("min-valid-lifetime", Element::create(100));
    globals_->set("max-valid-lifetime", Element::create(300));
    EXPECT_FALSE(net->getValid().unspecified());
    EXPECT_FALSE(net->getValid(Network::Inheritance::ALL).unspecified());
    EXPECT_FALSE(net->getValid(Network::Inheritance::GLOBAL).unspecified());
    EXPECT_EQ(200, net->getValid().get());
    EXPECT_EQ(200, net->getValid(Network::Inheritance::ALL).get());
    EXPECT_EQ(200, net->getValid(Network::Inheritance::GLOBAL).get());
    EXPECT_EQ(100, net->getValid().getMin());
    EXPECT_EQ(100, net->getValid(Network::Inheritance::ALL).getMin());
    EXPECT_EQ(100, net->getValid(Network::Inheritance::GLOBAL).getMin());
    EXPECT_EQ(300, net->getValid().getMax());
    EXPECT_EQ(300, net->getValid(Network::Inheritance::ALL).getMax());
    EXPECT_EQ(300, net->getValid(Network::Inheritance::GLOBAL).getMax());
}

}
