// Copyright (C) 2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <asiolink/io_address.h>
#include <dhcp/dhcp6.h>
#include <dhcp/option.h>
#include <dhcpsrv/network.h>
#include <boost/shared_ptr.hpp>
#include <functional>
#include <gtest/gtest.h>

using namespace isc::asiolink;
using namespace isc::data;
using namespace isc::dhcp;
using namespace isc::util;

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
    NetworkTest()
        : globals_(Element::createMap()) {
    }

    /// @brief Returns pointer to the function which returns configured
    /// global parameters.
    FetchNetworkGlobalsFn getFetchGlobalsFn() {
        return (std::bind(&NetworkTest::fetchGlobalsFn, this));
    }

    /// @brief Returns configured global parameters.
    ConstElementPtr fetchGlobalsFn() {
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
    void testNetworkInheritance(ParameterType1(BaseType2::*GetMethodPointer)() const,
                                void(BaseType2::*SetMethodPointer)(const ParameterType2&),
                                typename ParameterType1::ValueType network_value,
                                typename ParameterType1::ValueType global_value,
                                const bool test_global_value = true) {

        // Create child network object. The value retrieved from that
        // object should be unspecified until we set the value for the
        // parent network or a global value.
        boost::shared_ptr<BaseType1> net_child(new BaseType1());
        EXPECT_TRUE(((*net_child).*GetMethodPointer)().unspecified());

        // Create parent network and set the value.
        boost::shared_ptr<BaseType1> net_parent(new BaseType1());
        ((*net_parent).*SetMethodPointer)(network_value);
        EXPECT_EQ(network_value, ((*net_parent).*GetMethodPointer)().get());

        // Assign callbacks that fetch global values to the networks.
        net_child->setFetchGlobalsFn(getFetchGlobalsFn());
        net_parent->setFetchGlobalsFn(getFetchGlobalsFn());

        // Not all parameters have the corresponding global values.
        if (test_global_value) {
            // If there is a global value it should now be returned.
            EXPECT_FALSE(((*net_child).*GetMethodPointer)().unspecified());
            EXPECT_EQ(global_value, ((*net_child).*GetMethodPointer)().get());
        }

        // Associated the network with its parent.
        ASSERT_NO_THROW(net_child->setParent(net_parent));

        // This time the parent specific value should be returned.
        EXPECT_FALSE(((*net_child).*GetMethodPointer)().unspecified());
        EXPECT_EQ(network_value, ((*net_child).*GetMethodPointer)().get());
    }

    /// @brief Holds the collection of configured globals.
    ElementPtr globals_;
};

// This test verifies that the inheritance is supported for certain
// network parameters.
TEST_F(NetworkTest, inheritanceSupport4) {
    // Set global values for each parameter.
    globals_->set("interface", Element::create("g"));
    globals_->set("valid-lifetime", Element::create(80));
    globals_->set("renew-timer", Element::create(80));
    globals_->set("rebind-timer", Element::create(80));
    globals_->set("reservation-mode", Element::create(static_cast<int>(Network::HR_DISABLED)));
    globals_->set("calculate-tee-times", Element::create(false));
    globals_->set("t1-percent", Element::create(0.75));
    globals_->set("t2-percent", Element::create(0.6));
    globals_->set("match-client-id", Element::create(true));
    globals_->set("authoritative", Element::create(false));
    globals_->set("next-server", Element::create("192.0.2.3"));
    globals_->set("server-hostname", Element::create("g"));
    globals_->set("boot-file-name", Element::create("g"));

    // For each parameter for which inheritance is supported run
    // the test that checks if the values are inherited properly.

    {
        SCOPED_TRACE("interface");
        testNetworkInheritance<TestNetwork>(&Network::getIface, &Network::setIface,
                                            "n", "g");
    }
    {
        SCOPED_TRACE("client_class");
        testNetworkInheritance<TestNetwork>(&Network::getClientClass,
                                            &Network::allowClientClass,
                                            "n", "g", false);
    }
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
        SCOPED_TRACE("reservation-mode");
        testNetworkInheritance<TestNetwork>(&Network::getHostReservationMode,
                                            &Network::setHostReservationMode,
                                            Network::HR_OUT_OF_POOL,
                                            Network::HR_DISABLED);
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
}

// This test verifies that the inheritance is supported for DHCPv6
// specific network parameters.
TEST_F(NetworkTest, inheritanceSupport6) {
    // Set global values for each parameter.
    globals_->set("preferred-lifetime", Element::create(80));
    globals_->set("rapid-commit", Element::create(false));

    // For each parameter for which inheritance is supported run
    // the test that checks if the values are inherited properly.

    {
        SCOPED_TRACE("preferred-lifetime");
        testNetworkInheritance<TestNetwork6>(&Network6::getPreferred,
                                             &Network6::setPreferred,
                                             60, 80);
    }
    {
        SCOPED_TRACE("rapid-commit");
        testNetworkInheritance<TestNetwork6>(&Network6::getRapidCommit,
                                             &Network6::setRapidCommit,
                                             true, false);
    }

    // Interface-id requires special type of test.
    boost::shared_ptr<TestNetwork6> net_child(new TestNetwork6());
    EXPECT_TRUE(net_child->getIface().unspecified());

    OptionPtr interface_id(new Option(Option::V6, D6O_INTERFACE_ID,
                                      OptionBuffer(10, 0xFF)));

    boost::shared_ptr<TestNetwork6> net_parent(new TestNetwork6());
    net_parent->setInterfaceId(interface_id);

    ASSERT_NO_THROW(net_child->setParent(net_parent));

    EXPECT_TRUE(net_child->getInterfaceId());
    EXPECT_EQ(interface_id, net_child->getInterfaceId());
}

// Test that child network returns unspecified value if neither
// parent no global value exists.
TEST_F(NetworkTest, getPropertyNoParentNoChild) {
    NetworkPtr net_child(new Network());
    EXPECT_TRUE(net_child->getIface().unspecified());
}

// Test that child network returns specified value.
TEST_F(NetworkTest, getPropertyNoParentChild) {
    NetworkPtr net_child(new Network());
    net_child->setIface("child_iface");
    EXPECT_EQ("child_iface", net_child->getIface().get());
}

// Test that parent specific value is returned when the value
// is not specified for the child network.
TEST_F(NetworkTest, getPropertyParentNoChild) {
    TestNetworkPtr net_child(new TestNetwork());
    EXPECT_TRUE(net_child->getIface().unspecified());

    TestNetworkPtr net_parent(new TestNetwork());
    net_parent->setIface("parent_iface");
    EXPECT_EQ("parent_iface", net_parent->getIface().get());

    ASSERT_NO_THROW(net_child->setParent(net_parent));

    EXPECT_FALSE(net_child->getIface().unspecified());
    EXPECT_EQ("parent_iface", net_child->getIface().get());
}

// Test that value specified for the child network takes
// precedence over the value specified for the parent network.
TEST_F(NetworkTest, getPropertyParentChild) {
    TestNetworkPtr net_child(new TestNetwork());
    net_child->setIface("child_iface");
    EXPECT_EQ("child_iface", net_child->getIface().get());

    TestNetworkPtr net_parent(new TestNetwork());
    net_parent->setIface("parent_iface");
    EXPECT_EQ("parent_iface", net_parent->getIface().get());

    ASSERT_NO_THROW(net_child->setParent(net_parent));

    EXPECT_FALSE(net_child->getIface().unspecified());
    EXPECT_EQ("child_iface", net_child->getIface().get());
}

// Test that global value is inherited if there is no network
// specific value.
TEST_F(NetworkTest, getPropertyGlobalNoParentNoChild) {
    TestNetworkPtr net_child(new TestNetwork());

    globals_->set("interface", Element::create("global_iface"));

    net_child->setFetchGlobalsFn(getFetchGlobalsFn());

    EXPECT_FALSE(net_child->getIface().unspecified());
    EXPECT_EQ("global_iface", net_child->getIface().get());
}

}
