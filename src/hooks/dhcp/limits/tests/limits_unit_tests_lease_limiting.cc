// Copyright (C) 2022-2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <asiolink/io_address.h>
#include <dhcpsrv/cfgmgr.h>
#include <hooks/callout_handle.h>
#include <hooks/callout_manager.h>
#include <hooks/library_manager_collection.h>
#include <limits/limit_manager.h>
#include <stats/stats_mgr.h>
#include <testutils/gtest_utils.h>
#include <testutils/multi_threading_utils.h>
#include <testutils/test_to_element.h>

#include <chrono>
#include <thread>

#include <gtest/gtest.h>

namespace {

using namespace isc::dhcp;
using namespace isc::hooks;
using namespace isc::limits;
using namespace isc::util;
using namespace std;

using isc::asiolink::IOAddress;
using isc::data::ConstElementPtr;
using isc::data::Element;
using isc::data::ElementPtr;
using isc::stats::StatsMgr;
using isc::test::MultiThreadingTest;
using isc::test::generateDiff;

// Fixture for loading, unloading libraries and for testing callouts.
template <isc::util::DhcpSpace D>
struct LeaseLimitFixture : ::testing::Test {
    // Parse a text representation of a configuration with user contexts in client classes and
    // subnets that resembles a Kea configuration, add it to staging and commit it.
    void parseConfig(string const& configuration) {
        // Make sure configuration is empty.
        ASSERT_TRUE(CfgMgr::instance().getStagingCfg()->getClientClassDictionary()->empty())
            << "expected empty client class configuration, found "
            << CfgMgr::instance().getStagingCfg()->getClientClassDictionary()->toElement()->str();
        ASSERT_TRUE(CfgMgr::instance().getStagingCfg()->getCfgSubnets4()->getAll()->empty());
        ASSERT_TRUE(CfgMgr::instance().getStagingCfg()->getCfgSubnets6()->getAll()->empty());

        isc::data::ElementPtr const& config(isc::data::Element::fromJSON(configuration));
        for (auto const& kv : config->mapValue()) {
            if (kv.first == "client-classes") {
                for (auto const& client_class : kv.second->listValue()) {
                    bool is_template = false;
                    if (client_class->get("template-test")) {
                        is_template = true;
                    }
                    CfgMgr::instance().getStagingCfg()->getClientClassDictionary()->addClass(
                        client_class->get("name")->stringValue(), ExpressionPtr(), "", false, false,
                        CfgOptionPtr(), CfgOptionDefPtr(), client_class->get("user-context"),
                        IOAddress("0.0.0.0"), "", "", Triplet<uint32_t>(), Triplet<uint32_t>(),
                        is_template);
                }
            } else if (kv.first == "subnet4") {
                for (auto const& s : kv.second->listValue()) {
                    Subnet4Ptr subnet(boost::make_shared<Subnet4>(IOAddress("192.168.0.0"), 24, 900,
                                                                  1800, 3600,
                                                                  s->get("id")->intValue()));
                    subnet->setContext(s->get("user-context"));
                    CfgMgr::instance().getStagingCfg()->getCfgSubnets4()->add(subnet);
                }
            } else if (kv.first == "subnet6") {
                for (auto const& s : kv.second->listValue()) {
                    Subnet6Ptr subnet(boost::make_shared<Subnet6>(IOAddress("2001:db8::"), 64, 450,
                                                                  900, 1800, 3600,
                                                                  s->get("id")->intValue()));
                    subnet->setContext(s->get("user-context"));
                    CfgMgr::instance().getStagingCfg()->getCfgSubnets6()->add(subnet);
                }
            }
        }

        // Simulate the creation of a lease manager.
        LeaseMgrFactory::create(
            isc::util::formatDhcpSpace<D>("type=memfile persist=false universe={}"));

        // Simulate load() being called again, as is the case in a real reconfiguration.
        LimitManager::instance().initialize(CfgMgr::instance().getStagingCfg());

        // In a real environment, configuration is committed after libraries are loaded.
        CfgMgr::instance().commit();
    }

    /// @brief Sends a packet with the given client classes assigned to it and expects a given
    ///     callout status.
    ///
    /// @param manager the callout manager that hosts the callout handle
    /// @param client_classes the client classes that are assigned to the packet, in the give order
    /// @param expected_status the expected callout status
    /// @param use_prefix true if the lease should be an IA_PD, false if it should be IA_NA or v4
    ///     address. Default: false.
    /// @param use_template_classes if the test should use template classes or regular client
    ///     classes. Default: false.
    void sendPacketAndExpectStatus(boost::shared_ptr<CalloutManager> const& manager,
                                   vector<ClientClass> const& client_classes,
                                   CalloutHandle::CalloutNextStep expected_status,
                                   bool use_prefix = false,
                                   bool use_template_classes = false) {
        // Simulate a handle.
        CalloutHandle handle(manager);
        PktTPtr<D> packet(boost::make_shared<PktT<D>>(1, 128));
        packet->addClass("ALL");
        if (use_template_classes) {
            for (ClientClass const& c : client_classes) {
                std::string subclass(TemplateClientClassDef::SPAWN_CLASS_PREFIX);
                subclass += c;
                subclass += "_value";
                packet->addSubClass(c, subclass);
            }
        } else {
            for (ClientClass const& c : client_classes) {
                packet->addClass(c);
            }
        }
        ConstSubnetTPtr<D> subnet(createSubnet());
        LeaseTPtr<D> lease(createLease(use_prefix));
        handle.setArgument(isc::util::formatDhcpSpace<D>("query{}"), packet);
        handle.setArgument(isc::util::formatDhcpSpace<D>("subnet{}"), subnet);
        handle.setArgument("fake_allocation", false);
        handle.setArgument(isc::util::formatDhcpSpace<D>("lease{}"), lease);

        // Simulate a leaseX_select callout call.
        EXPECT_NO_THROW_LOG(LimitManager::instance().lease_callout<D>(handle));

        // Simulate a lease allocation.
        if (handle.getStatus() == CalloutHandle::NEXT_STEP_CONTINUE) {
            addLease(lease);
        }

        // Expect the given status.
        EXPECT_EQ(handle.getStatus(), expected_status);
    }

    /// @brief the body of most of the following tests
    ///
    /// It configures the library with a given configuration, and then sends the same packet a
    /// given number of times and expects a certain result for each.
    ///
    /// @param configuration the library configuration to be used
    /// @param expected_results a vector of tuples containing the expected callout status as the
    ///     second element and as the first element - the number of consecutive packets that should
    ///     result in said callout status
    /// @param use_prefix true if the lease should be an IA_PD, false if it should be IA_NA or v4
    ///     address. Default: false.
    /// @param use_template_classes if the test should use template classes or regular client
    ///     classes. Default: false.
    void test(string const& configuration,
              vector<tuple<unsigned int,
              CalloutHandle::CalloutNextStep>> const& expected_results,
              bool use_prefix = false,
              bool use_template_classes = false) {
        // Make a callout manager.
        boost::shared_ptr<CalloutManager> manager(boost::make_shared<CalloutManager>());

        // Configure.
        parseConfig(configuration);

        for (auto const& expected_result : expected_results) {
            for (unsigned int i = 0; i < get<0>(expected_result); ++i) {
                sendPacketAndExpectStatus(manager, {"foo", "bar"}, get<1>(expected_result),
                                          use_prefix, use_template_classes);
            }
        }
    }

    /// @brief Check that classes are added to user context - various scenarios.
    void testExistingUserContext() {
        for (auto const& test_case : vector<vector<string>>({
            {
                "Test case 1. Already populated user context.",
                R"(
                    {
                      "ISC": {
                        "relay-agent-info": {
                          "remote-id": "000ACE0FBA5E",
                          "sub-options": "0x0206010203040506"
                        }
                      }
                    }
                )",
                R"(
                    {
                      "ISC": {
                        "client-classes": [
                          "ALL",
                          "foo"
                        ],
                        "relay-agent-info": {
                          "remote-id": "000ACE0FBA5E",
                          "sub-options": "0x0206010203040506"
                        }
                      }
                    }
                )",
            },
            {
                "Test case 2. No user context.",
                "",
                R"(
                    {
                      "ISC": {
                        "client-classes": [
                          "ALL",
                          "foo"
                        ]
                      }
                    }
                )",
            },
            {
                "Test case 3. Existing client classes, but they change.",
                R"(
                    {
                      "ISC": {
                        "client-classes": [
                          "ALL",
                          "bar"
                        ],
                        "relay-agent-info": {
                          "remote-id": "000ACE0FBA5E",
                          "sub-options": "0x0206010203040506"
                        }
                      }
                    }
                )",
                R"(
                    {
                      "ISC": {
                        "client-classes": [
                          "ALL",
                          "foo"
                        ],
                        "relay-agent-info": {
                          "remote-id": "000ACE0FBA5E",
                          "sub-options": "0x0206010203040506"
                        }
                      }
                    }
                )",
            },
        })) {
            SCOPED_TRACE(test_case[0]);
            ElementPtr const initial_context(test_case[1].empty() ? ElementPtr() : Element::fromJSON(test_case[1]));
            ElementPtr const expected_context(Element::fromJSON(test_case[2]));

            // Make a callout manager.
            boost::shared_ptr<CalloutManager> manager(boost::make_shared<CalloutManager>());

            // Configure a class with some limits.
            parseConfig(R"(
            {
                "client-classes": [
                {
                    "name": "foo",
                    "test": "true",
                    "user-context": {
                    "limits": {
                        "address-limit": 1,
                        "prefix-limit": 2
                    }
                    }
                },
                ]
            }
            )");

            // Simulate a handle.
            CalloutHandle handle(manager);
            PktTPtr<D> packet(boost::make_shared<PktT<D>>(1, 128));
            packet->addClass("ALL");
            packet->addClass("foo");
            ConstSubnetTPtr<D> subnet(createSubnet());
            LeaseTPtr<D> lease(createLease());
            lease->setContext(initial_context);
            handle.setArgument("fake_allocation", false);
            handle.setArgument(isc::util::formatDhcpSpace<D>("lease{}"), lease);
            handle.setArgument(isc::util::formatDhcpSpace<D>("query{}"), packet);
            handle.setArgument(isc::util::formatDhcpSpace<D>("subnet{}"), subnet);

            // Sanity check on the user context.
            if (initial_context) {
                ASSERT_TRUE(lease->getContext());
                EXPECT_TRUE(isEquivalent(lease->getContext(), initial_context))
                    << generateDiff(lease->getContext()->str(), initial_context->str());
            }

            // Simulate a leaseX_select callout call.
            EXPECT_NO_THROW_LOG(LimitManager::instance().lease_callout<D>(handle));
            EXPECT_EQ(handle.getStatus(), CalloutHandle::NEXT_STEP_CONTINUE);

            // Check that the classes were added to the user context accordingly.
            ASSERT_TRUE(lease->getContext());
            EXPECT_TRUE(isEquivalent(lease->getContext(), expected_context))
                << generateDiff(lease->getContext()->str(), expected_context->str());

            // Simulate a lease allocation.
            addLease(lease);

            // Check that the user context is the same after the lease went through the lease manager.
            ASSERT_TRUE(lease->getContext());
            EXPECT_TRUE(isEquivalent(lease->getContext(), expected_context))
                << generateDiff(lease->getContext()->str(), expected_context->str());
        }
    }

private:
    /// @brief convenience function to simulate the allocation of a lease
    ///
    /// @param lease the lease being allocated
    void addLease(LeaseTPtr<D> lease);

    /// @brief convenience function to create pointers to Lease4 and Lease6
    ///
    /// @param use_prefix true if the lease should be an IA_PD, false if it should be IA_NA or v4
    ///     address. Default: false.
    LeaseTPtr<D> createLease(bool use_prefix = false);

    /// @brief convenience function to create pointers to Subnet4 and Subnet6
    SubnetTPtr<D> createSubnet();
};

template <>
void
LeaseLimitFixture<DHCPv4>::addLease(LeaseTPtr<DHCPv4> lease) {
    LeaseMgrFactory::instance().addLease(lease);
    StatsMgr::instance().addValue(StatsMgr::generateName("subnet", lease->subnet_id_,
                                                         "assigned-addresses"),
                                  static_cast<int64_t>(1));
}

template <>
void
LeaseLimitFixture<DHCPv6>::addLease(LeaseTPtr<DHCPv6> lease) {
    LeaseMgrFactory::instance().addLease(lease);
    StatsMgr::instance().addValue(StatsMgr::generateName("subnet", lease->subnet_id_,
                                                         lease->getType() == Lease::TYPE_PD ?
                                                         "assigned-pds" : "assigned-nas"),
                                  static_cast<int64_t>(1));
}

template <>
LeaseTPtr<DHCPv4>
LeaseLimitFixture<DHCPv4>::createLease(bool /* use_prefix = false */) {
    static uint16_t counter(256);
    ++counter;
    uint8_t low = *(reinterpret_cast<uint8_t*>(&counter));
    uint8_t high = *(reinterpret_cast<uint8_t*>(&counter) + 1);
    HWAddrPtr hwaddr(new HWAddr(std::vector<uint8_t>{0x01, 0x02, 0x03, 0x04, low, high}, 1));
    ClientIdPtr client_id(new ClientId({0, 1, 2, 3, 4, low, high}));
    return (boost::make_shared<Lease4>(IOAddress("192.168." + std::to_string(low) + "." + std::to_string(high)), hwaddr,
                                       client_id, 3600, 0, 1, false, false, string()));
}

template <>
LeaseTPtr<DHCPv6>
LeaseLimitFixture<DHCPv6>::createLease(bool use_prefix /* = false */) {
    static uint16_t counter(256);
    ++counter;
    uint8_t low = *(reinterpret_cast<uint8_t*>(&counter));
    uint8_t high = *(reinterpret_cast<uint8_t*>(&counter) + 1);
    HWAddrPtr hwaddr(new HWAddr(std::vector<uint8_t>{0x01, 0x02, 0x03, 0x04, low, high}, 1));
    DuidPtr duid(new DUID({0, 1, 2, 3, 4, low, high}));
    return (boost::make_shared<Lease6>(use_prefix ? Lease::TYPE_PD : Lease::TYPE_NA,
                                       IOAddress("2001:db8:" + std::to_string(low) + ":" + std::to_string(high) + "::"), duid, 2,
                                       1800, 3600, 1, false, false, "test.hostname", hwaddr,
                                       use_prefix ? 96 : 128));
}

template <>
SubnetTPtr<DHCPv4>
LeaseLimitFixture<DHCPv4>::createSubnet() {
    return (boost::make_shared<Subnet4>(IOAddress("192.168.0.0"), 24, 900, 1800, 3600, 1));
}

template <>
SubnetTPtr<DHCPv6>
LeaseLimitFixture<DHCPv6>::createSubnet() {
    return (boost::make_shared<Subnet6>(IOAddress("2001:db8::"), 64, 450, 900, 1800, 3600, 1));
}

using LeaseLimitV4 = LeaseLimitFixture<DHCPv4>;
using LeaseLimitV6 = LeaseLimitFixture<DHCPv6>;

// Check that an empty configuration does not limit v4 packets.
TEST_F(LeaseLimitV4, emptyConfiguration) {
    test("{}", {make_tuple(4, CalloutHandle::NEXT_STEP_CONTINUE)});
}

TEST_F(LeaseLimitV4, emptyConfigurationMultiThreading) {
    MultiThreadingTest mt;
    test("{}", {make_tuple(4, CalloutHandle::NEXT_STEP_CONTINUE)});
}

// Check that an empty configuration does not limit v6 packets.
TEST_F(LeaseLimitV6, emptyConfiguration) {
    test("{}", {make_tuple(4, CalloutHandle::NEXT_STEP_CONTINUE)});
}

TEST_F(LeaseLimitV6, emptyConfigurationMultiThreading) {
    MultiThreadingTest mt;
    test("{}", {make_tuple(4, CalloutHandle::NEXT_STEP_CONTINUE)});
}

// Check that no address limit by client class works as expected for v4 packets.
TEST_F(LeaseLimitV4, noLimitPerClientClass) {
    test(R"( { "client-classes": [ { "name": "foo",
                                     "user-context": { } } ] } )",
         {
             make_tuple(2, CalloutHandle::NEXT_STEP_CONTINUE)
         });
}

TEST_F(LeaseLimitV4, noLimitPerClientClassMultiThreading) {
    MultiThreadingTest mt;
    test(R"( { "client-classes": [ { "name": "foo",
                                     "user-context": { } } ] } )",
         {
             make_tuple(2, CalloutHandle::NEXT_STEP_CONTINUE)
         });
}

// Check that no address limit by client class works as expected for v6 packets.
TEST_F(LeaseLimitV6, noLimitPerClientClass) {
    test(R"( { "client-classes": [ { "name": "foo",
                                     "user-context": { } } ] } )",
         {
             make_tuple(2, CalloutHandle::NEXT_STEP_CONTINUE)
         });
}

TEST_F(LeaseLimitV6, noLimitPerClientClassMultiThreading) {
    MultiThreadingTest mt;
    test(R"( { "client-classes": [ { "name": "foo",
                                     "user-context": { } } ] } )",
         {
             make_tuple(2, CalloutHandle::NEXT_STEP_CONTINUE)
         });
}

// Check that no address limit by subnet ID works as expected for v4 packets.
TEST_F(LeaseLimitV4, noLimitPerSubnet) {
    test(R"( { "subnet4": [ { "id": 1,
                              "user-context": { } } ] } )",
         {
             make_tuple(2, CalloutHandle::NEXT_STEP_CONTINUE)
         });
}

TEST_F(LeaseLimitV4, noLimitPerSubnetMultiThreading) {
    MultiThreadingTest mt;
    test(R"( { "subnet4": [ { "id": 1,
                              "user-context": { } } ] } )",
         {
             make_tuple(2, CalloutHandle::NEXT_STEP_CONTINUE)
         });
}

// Check that no address limit by subnet ID works as expected for v6 packets.
TEST_F(LeaseLimitV6, noLimitPerSubnet) {
    test(R"( { "subnet6": [ { "id": 1,
                              "user-context": { } } ] } )",
         {
             make_tuple(2, CalloutHandle::NEXT_STEP_CONTINUE)
         });
}

TEST_F(LeaseLimitV6, noLimitPerSubnetMultiThreading) {
    MultiThreadingTest mt;
    test(R"( { "subnet6": [ { "id": 1,
                              "user-context": { } } ] } )",
         {
             make_tuple(2, CalloutHandle::NEXT_STEP_CONTINUE)
         });
}

// Check that an address limit by built-in client class works as expected for v4 packets.
TEST_F(LeaseLimitV4, oneLimitPerBuiltInClientClass) {
    test(R"( { "client-classes": [ { "name": "ALL",
                                     "user-context": { "limits": { "address-limit": 2 } } } ] } )",
         {
             make_tuple(2, CalloutHandle::NEXT_STEP_CONTINUE),
             make_tuple(2, CalloutHandle::NEXT_STEP_SKIP),
         });
}

TEST_F(LeaseLimitV4, oneLimitPerBuiltInClientClassMultiThreading) {
    MultiThreadingTest mt;
    test(R"( { "client-classes": [ { "name": "ALL",
                                     "user-context": { "limits": { "address-limit": 2 } } } ] } )",
         {
             make_tuple(2, CalloutHandle::NEXT_STEP_CONTINUE),
             make_tuple(2, CalloutHandle::NEXT_STEP_SKIP),
         });
}

// Check that an address limit by built-in client class works as expected for v6 packets.
TEST_F(LeaseLimitV6, oneLimitPerBuiltInClientClass) {
    test(R"( { "client-classes": [ { "name": "ALL",
                                     "user-context": { "limits": { "address-limit": 2 } } } ] } )",
         {
             make_tuple(2, CalloutHandle::NEXT_STEP_CONTINUE),
             make_tuple(2, CalloutHandle::NEXT_STEP_SKIP),
         });
}

TEST_F(LeaseLimitV6, oneLimitPerBuiltInClientClassMultiThreading) {
    MultiThreadingTest mt;
    test(R"( { "client-classes": [ { "name": "ALL",
                                     "user-context": { "limits": { "address-limit": 2 } } } ] } )",
         {
             make_tuple(2, CalloutHandle::NEXT_STEP_CONTINUE),
             make_tuple(2, CalloutHandle::NEXT_STEP_SKIP),
         });
}

// Check that an address limit by client class works as expected for v4 packets.
TEST_F(LeaseLimitV4, oneLimitPerClientClass) {
    test(R"( { "client-classes": [ { "name": "foo",
                                     "user-context": { "limits": { "address-limit": 2 } } } ] } )",
         {
             make_tuple(2, CalloutHandle::NEXT_STEP_CONTINUE),
             make_tuple(2, CalloutHandle::NEXT_STEP_SKIP),
         });
}

TEST_F(LeaseLimitV4, oneLimitPerClientClassMultiThreading) {
    MultiThreadingTest mt;
    test(R"( { "client-classes": [ { "name": "foo",
                                     "user-context": { "limits": { "address-limit": 2 } } } ] } )",
         {
             make_tuple(2, CalloutHandle::NEXT_STEP_CONTINUE),
             make_tuple(2, CalloutHandle::NEXT_STEP_SKIP),
         });
}

// Check that an address limit by client class works as expected for v6 packets.
TEST_F(LeaseLimitV6, oneLimitPerClientClass) {
    test(R"( { "client-classes": [ { "name": "foo",
                                     "user-context": { "limits": { "address-limit": 2 } } } ] } )",
         {
             make_tuple(2, CalloutHandle::NEXT_STEP_CONTINUE),
             make_tuple(2, CalloutHandle::NEXT_STEP_SKIP),
         });
}

TEST_F(LeaseLimitV6, oneLimitPerClientClassMultiThreading) {
    MultiThreadingTest mt;
    test(R"( { "client-classes": [ { "name": "foo",
                                     "user-context": { "limits": { "address-limit": 2 } } } ] } )",
         {
             make_tuple(2, CalloutHandle::NEXT_STEP_CONTINUE),
             make_tuple(2, CalloutHandle::NEXT_STEP_SKIP),
         });
}

// Check that an address limit by subnet ID works as expected for v4 packets.
TEST_F(LeaseLimitV4, oneLimitPerSubnet) {
    test(R"( { "subnet4": [ { "id": 1,
                              "user-context": { "limits": { "address-limit": 2 } } } ] } )",
         {
             make_tuple(2, CalloutHandle::NEXT_STEP_CONTINUE),
             make_tuple(2, CalloutHandle::NEXT_STEP_SKIP),
         });
}

TEST_F(LeaseLimitV4, oneLimitPerSubnetMultiThreading) {
    MultiThreadingTest mt;
    test(R"( { "subnet4": [ { "id": 1,
                              "user-context": { "limits": { "address-limit": 2 } } } ] } )",
         {
             make_tuple(2, CalloutHandle::NEXT_STEP_CONTINUE),
             make_tuple(2, CalloutHandle::NEXT_STEP_SKIP),
         });
}

// Check that an address limit by subnet ID works as expected for v6 packets.
TEST_F(LeaseLimitV6, oneLimitPerSubnet) {
    test(R"( { "subnet6": [ { "id": 1,
                              "user-context": { "limits": { "address-limit": 2 } } } ] } )",
         {
             make_tuple(2, CalloutHandle::NEXT_STEP_CONTINUE),
             make_tuple(2, CalloutHandle::NEXT_STEP_SKIP),
         });
}

TEST_F(LeaseLimitV6, oneLimitPerSubnetMultiThreading) {
    MultiThreadingTest mt;
    test(R"( { "subnet6": [ { "id": 1,
                              "user-context": { "limits": { "address-limit": 2 } } } ] } )",
         {
             make_tuple(2, CalloutHandle::NEXT_STEP_CONTINUE),
             make_tuple(2, CalloutHandle::NEXT_STEP_SKIP),
         });
}

// Check that v4 packets matched by multiple limits by both client class and subnet ID result in the
// stricter limit having effect.
TEST_F(LeaseLimitV4, limitingPerClientClassAndSubnetID) {
    test(R"( { "client-classes": [ { "name": "foo",
                                     "user-context": { "limits": { "address-limit": 2 } } } ],
               "subnet4": [ { "id": 1,
                              "user-context": { "limits": { "address-limit": 4 } } } ] } )",
         {
             make_tuple(2, CalloutHandle::NEXT_STEP_CONTINUE),
             make_tuple(6, CalloutHandle::NEXT_STEP_SKIP),
         });
}

TEST_F(LeaseLimitV4, limitingPerClientClassAndSubnetIDMultiThreading) {
    MultiThreadingTest mt;
    test(R"( { "client-classes": [ { "name": "foo",
                                     "user-context": { "limits": { "address-limit": 2 } } } ],
               "subnet4": [ { "id": 1,
                              "user-context": { "limits": { "address-limit": 4 } } } ] } )",
         {
             make_tuple(2, CalloutHandle::NEXT_STEP_CONTINUE),
             make_tuple(6, CalloutHandle::NEXT_STEP_SKIP),
         });
}

// Check that v6 packets matched by multiple limits by both client class and subnet ID result in the
// stricter limit having effect.
TEST_F(LeaseLimitV6, limitingPerClientClassAndSubnetID) {
    test(R"( { "client-classes": [ { "name": "foo",
                                     "user-context": { "limits": { "address-limit": 2 } } } ],
               "subnet6": [ { "id": 1,
                              "user-context": { "limits": { "address-limit": 4 } } } ] } )",
         {
             make_tuple(2, CalloutHandle::NEXT_STEP_CONTINUE),
             make_tuple(6, CalloutHandle::NEXT_STEP_SKIP),
         });
}

TEST_F(LeaseLimitV6, limitingPerClientClassAndSubnetIDMultiThreading) {
    MultiThreadingTest mt;
    test(R"( { "client-classes": [ { "name": "foo",
                                     "user-context": { "limits": { "address-limit": 2 } } } ],
               "subnet6": [ { "id": 1,
                              "user-context": { "limits": { "address-limit": 4 } } } ] } )",
         {
             make_tuple(2, CalloutHandle::NEXT_STEP_CONTINUE),
             make_tuple(6, CalloutHandle::NEXT_STEP_SKIP),
         });
}

// Check that v4 packets matched by multiple limits by both client class and subnet ID result in the
// stricter limit having effect.
TEST_F(LeaseLimitV4, limitingPerSubnetAndClientClass) {
    test(R"( { "client-classes": [ { "name": "foo",
                                     "user-context": { "limits": { "address-limit": 4 } } } ],
               "subnet4": [ { "id": 1,
                              "user-context": { "limits": { "address-limit": 2 } } } ] } )",
         {
             make_tuple(2, CalloutHandle::NEXT_STEP_CONTINUE),
             make_tuple(6, CalloutHandle::NEXT_STEP_SKIP),
         });
}

TEST_F(LeaseLimitV4, limitingPerSubnetAndClientClassMultiThreading) {
    MultiThreadingTest mt;
    test(R"( { "client-classes": [ { "name": "foo",
                                     "user-context": { "limits": { "address-limit": 4 } } } ],
               "subnet4": [ { "id": 1,
                              "user-context": { "limits": { "address-limit": 2 } } } ] } )",
         {
             make_tuple(2, CalloutHandle::NEXT_STEP_CONTINUE),
             make_tuple(6, CalloutHandle::NEXT_STEP_SKIP),
         });
}

// Check that v6 packets matched by multiple limits by both client class and subnet ID result in the
// stricter limit having effect.
TEST_F(LeaseLimitV6, limitingPerSubnetAndClientClass) {
    test(R"( { "client-classes": [ { "name": "foo",
                                     "user-context": { "limits": { "address-limit": 4 } } } ],
               "subnet6": [ { "id": 1,
                              "user-context": { "limits": { "address-limit": 2 } } } ] } )",
         {
             make_tuple(2, CalloutHandle::NEXT_STEP_CONTINUE),
             make_tuple(6, CalloutHandle::NEXT_STEP_SKIP),
         });
}

TEST_F(LeaseLimitV6, limitingPerSubnetAndClientClassMultiThreading) {
    MultiThreadingTest mt;
    test(R"( { "client-classes": [ { "name": "foo",
                                     "user-context": { "limits": { "address-limit": 4 } } } ],
               "subnet6": [ { "id": 1,
                              "user-context": { "limits": { "address-limit": 2 } } } ] } )",
         {
             make_tuple(2, CalloutHandle::NEXT_STEP_CONTINUE),
             make_tuple(6, CalloutHandle::NEXT_STEP_SKIP),
         });
}

// Check that an address limit of zero applied to built-in client classes effectively drops all v4 packets.
TEST_F(LeaseLimitV4, zeroLimitPerBuiltInClientClass) {
    test(R"( { "client-classes": [ { "name": "ALL",
                                     "user-context": { "limits": { "address-limit": 0 } } } ],
               "subnet4": [ { "id": 1,
                              "user-context": { "limits": { "address-limit": 2 } } } ] } )",
         {
             make_tuple(4, CalloutHandle::NEXT_STEP_SKIP),
         });
}

TEST_F(LeaseLimitV4, zeroLimitPerBuiltInClientClassMultiThreading) {
    MultiThreadingTest mt;
    test(R"( { "client-classes": [ { "name": "ALL",
                                     "user-context": { "limits": { "address-limit": 0 } } } ],
               "subnet4": [ { "id": 1,
                              "user-context": { "limits": { "address-limit": 2 } } } ] } )",
         {
             make_tuple(4, CalloutHandle::NEXT_STEP_SKIP),
         });
}

// Check that an address limit of zero applied to built-in client classes effectively drops all v6 packets.
TEST_F(LeaseLimitV6, zeroLimitPerBuiltInClientClass) {
    test(R"( { "client-classes": [ { "name": "ALL",
                                     "user-context": { "limits": { "address-limit": 0 } } } ],
               "subnet6": [ { "id": 1,
                              "user-context": { "limits": { "address-limit": 2 } } } ] } )",
         {
             make_tuple(4, CalloutHandle::NEXT_STEP_SKIP),
         });
}

TEST_F(LeaseLimitV6, zeroLimitPerBuiltInClientClassMultiThreading) {
    test(R"( { "client-classes": [ { "name": "ALL",
                                     "user-context": { "limits": { "address-limit": 0 } } } ],
               "subnet6": [ { "id": 1,
                              "user-context": { "limits": { "address-limit": 2 } } } ] } )",
         {
             make_tuple(4, CalloutHandle::NEXT_STEP_SKIP),
         });
}

// Check that an address limit of zero applied to client classes effectively drops all v4 packets.
TEST_F(LeaseLimitV4, zeroLimitPerClientClass) {
    test(R"( { "client-classes": [ { "name": "foo",
                                     "user-context": { "limits": { "address-limit": 0 } } } ],
               "subnet4": [ { "id": 1,
                              "user-context": { "limits": { "address-limit": 2 } } } ] } )",
         {
             make_tuple(4, CalloutHandle::NEXT_STEP_SKIP),
         });
}

TEST_F(LeaseLimitV4, zeroLimitPerClientClassMultiThreading) {
    MultiThreadingTest mt;
    test(R"( { "client-classes": [ { "name": "foo",
                                     "user-context": { "limits": { "address-limit": 0 } } } ],
               "subnet4": [ { "id": 1,
                              "user-context": { "limits": { "address-limit": 2 } } } ] } )",
         {
             make_tuple(4, CalloutHandle::NEXT_STEP_SKIP),
         });
}

// Check that an address limit of zero applied to client classes effectively drops all v6 packets.
TEST_F(LeaseLimitV6, zeroLimitPerClientClass) {
    test(R"( { "client-classes": [ { "name": "foo",
                                     "user-context": { "limits": { "address-limit": 0 } } } ],
               "subnet6": [ { "id": 1,
                              "user-context": { "limits": { "address-limit": 2 } } } ] } )",
         {
             make_tuple(4, CalloutHandle::NEXT_STEP_SKIP),
         });
}

TEST_F(LeaseLimitV6, zeroLimitPerClientClassMultiThreading) {
    test(R"( { "client-classes": [ { "name": "foo",
                                     "user-context": { "limits": { "address-limit": 0 } } } ],
               "subnet6": [ { "id": 1,
                              "user-context": { "limits": { "address-limit": 2 } } } ] } )",
         {
             make_tuple(4, CalloutHandle::NEXT_STEP_SKIP),
         });
}

// Check that an address limit of zero applied to subnet IDs effectively drops all v4 packets.
TEST_F(LeaseLimitV4, zeroLimitPerSubnet) {
    test(R"( { "client-classes": [ { "name": "foo",
                                     "user-context": { "limits": { "address-limit": 2 } } } ],
               "subnet4": [ { "id": 1,
                              "user-context": { "limits": { "address-limit": 0 } } } ] } )",
         {
             make_tuple(4, CalloutHandle::NEXT_STEP_SKIP),
         });
}

TEST_F(LeaseLimitV4, zeroLimitPerSubnetMultiThreading) {
    MultiThreadingTest mt;
    test(R"( { "client-classes": [ { "name": "foo",
                                     "user-context": { "limits": { "address-limit": 2 } } } ],
               "subnet4": [ { "id": 1,
                              "user-context": { "limits": { "address-limit": 0 } } } ] } )",
         {
             make_tuple(4, CalloutHandle::NEXT_STEP_SKIP),
         });
}

// Check that an address limit of zero applied to subnet IDs effectively drops all v6 packets.
TEST_F(LeaseLimitV6, zeroLimitPerSubnet) {
    test(R"( { "client-classes": [ { "name": "foo",
                                     "user-context": { "limits": { "address-limit": 2 } } } ],
               "subnet6": [ { "id": 1,
                              "user-context": { "limits": { "address-limit": 0 } } } ] } )",
         {
             make_tuple(4, CalloutHandle::NEXT_STEP_SKIP),
         });
}

TEST_F(LeaseLimitV6, zeroLimitPerSubnetMultiThreading) {
    MultiThreadingTest mt;
    test(R"( { "client-classes": [ { "name": "foo",
                                     "user-context": { "limits": { "address-limit": 2 } } } ],
               "subnet6": [ { "id": 1,
                              "user-context": { "limits": { "address-limit": 0 } } } ] } )",
         {
             make_tuple(4, CalloutHandle::NEXT_STEP_SKIP),
         });
}

// Check that a drop caused by an address limit applied to a subsequently assigned client class,
// here "bar", does not affect the internal packet counts for client classes that were assigned
// before it, here "foo". The v4 version.
TEST_F(LeaseLimitV4, noSideEffectOfPacketsDroppedByClientClass) {
    // Make a callout manager.
    boost::shared_ptr<CalloutManager> manager(boost::make_shared<CalloutManager>());

    // Configure.
    parseConfig(R"( { "client-classes": [ { "name": "foo",
                                            "user-context": { "limits": { "address-limit": 2 } } },
                                          { "name": "bar",
                                            "user-context": { "limits": { "address-limit": 1 } } } ] } )");

    // Should be accepted.
    sendPacketAndExpectStatus(manager, {"foo", "bar"}, CalloutHandle::NEXT_STEP_CONTINUE);

    // Should be dropped because of the "bar" limit.
    sendPacketAndExpectStatus(manager, {"foo", "bar"}, CalloutHandle::NEXT_STEP_SKIP);

    // Should be accepted.
    sendPacketAndExpectStatus(manager, {"foo"}, CalloutHandle::NEXT_STEP_CONTINUE);

    // Should be dropped because of the "foo" limit.
    sendPacketAndExpectStatus(manager, {"foo"}, CalloutHandle::NEXT_STEP_SKIP);
}

TEST_F(LeaseLimitV4, noSideEffectOfPacketsDroppedByClientClassMultiThreading) {
    MultiThreadingTest mt;

    // Make a callout manager.
    boost::shared_ptr<CalloutManager> manager(boost::make_shared<CalloutManager>());

    // Configure.
    parseConfig(R"( { "client-classes": [ { "name": "foo",
                                            "user-context": { "limits": { "address-limit": 2 } } },
                                          { "name": "bar",
                                            "user-context": { "limits": { "address-limit": 1 } } } ] } )");

    // Should be accepted.
    sendPacketAndExpectStatus(manager, {"foo", "bar"}, CalloutHandle::NEXT_STEP_CONTINUE);

    // Should be dropped because of the "bar" limit.
    sendPacketAndExpectStatus(manager, {"foo", "bar"}, CalloutHandle::NEXT_STEP_SKIP);

    // Should be accepted.
    sendPacketAndExpectStatus(manager, {"foo"}, CalloutHandle::NEXT_STEP_CONTINUE);

    // Should be dropped because of the "foo" limit.
    sendPacketAndExpectStatus(manager, {"foo"}, CalloutHandle::NEXT_STEP_SKIP);
}

// Check that a drop caused by an address limit applied to a subsequently assigned client class,
// here "bar", does not affect the internal packet counts for client classes that were assigned
// before it, here "foo". The v6 version.
TEST_F(LeaseLimitV6, noSideEffectOfPacketsDroppedByClientClass) {
    // Make a callout manager.
    boost::shared_ptr<CalloutManager> manager(boost::make_shared<CalloutManager>());

    // Configure.
    parseConfig(R"( { "client-classes": [ { "name": "foo",
                                            "user-context": { "limits": { "address-limit": 2 } } },
                                          { "name": "bar",
                                            "user-context": { "limits": { "address-limit": 1 } } } ] } )");

    // Should be accepted.
    sendPacketAndExpectStatus(manager, {"foo", "bar"}, CalloutHandle::NEXT_STEP_CONTINUE);

    // Should be dropped because of the "bar" limit.
    sendPacketAndExpectStatus(manager, {"foo", "bar"}, CalloutHandle::NEXT_STEP_SKIP);

    // Should be accepted.
    sendPacketAndExpectStatus(manager, {"foo"}, CalloutHandle::NEXT_STEP_CONTINUE);

    // Should be dropped because of the "foo" limit.
    sendPacketAndExpectStatus(manager, {"foo"}, CalloutHandle::NEXT_STEP_SKIP);
}

TEST_F(LeaseLimitV6, noSideEffectOfPacketsDroppedByClientClassMultiThreading) {
    MultiThreadingTest mt;

    // Make a callout manager.
    boost::shared_ptr<CalloutManager> manager(boost::make_shared<CalloutManager>());

    // Configure.
    parseConfig(R"( { "client-classes": [ { "name": "foo",
                                            "user-context": { "limits": { "address-limit": 2 } } },
                                          { "name": "bar",
                                            "user-context": { "limits": { "address-limit": 1 } } } ] } )");

    // Should be accepted.
    sendPacketAndExpectStatus(manager, {"foo", "bar"}, CalloutHandle::NEXT_STEP_CONTINUE);

    // Should be dropped because of the "bar" limit.
    sendPacketAndExpectStatus(manager, {"foo", "bar"}, CalloutHandle::NEXT_STEP_SKIP);

    // Should be accepted.
    sendPacketAndExpectStatus(manager, {"foo"}, CalloutHandle::NEXT_STEP_CONTINUE);

    // Should be dropped because of the "foo" limit.
    sendPacketAndExpectStatus(manager, {"foo"}, CalloutHandle::NEXT_STEP_SKIP);
}

// Check that a prefix limit by built-in client class works as expected for packets.
TEST_F(LeaseLimitV6, onePrefixLimitPerBuiltInClientClass) {
    test(R"( { "client-classes": [ { "name": "ALL",
                                     "user-context": { "limits": { "prefix-limit": 2 } } } ] } )",
         {
             make_tuple(2, CalloutHandle::NEXT_STEP_CONTINUE),
             make_tuple(2, CalloutHandle::NEXT_STEP_SKIP),
         },
         /* use_prefix = */ true);
}

TEST_F(LeaseLimitV6, onePrefixLimitPerBuiltInClientClassMultiThreading) {
    MultiThreadingTest mt;
    test(R"( { "client-classes": [ { "name": "ALL",
                                     "user-context": { "limits": { "prefix-limit": 2 } } } ] } )",
         {
             make_tuple(2, CalloutHandle::NEXT_STEP_CONTINUE),
             make_tuple(2, CalloutHandle::NEXT_STEP_SKIP),
         },
         /* use_prefix = */ true);
}

// Check that a prefix limit by client class works as expected for packets.
TEST_F(LeaseLimitV6, onePrefixLimitPerClientClass) {
    test(R"( { "client-classes": [ { "name": "foo",
                                     "user-context": { "limits": { "prefix-limit": 2 } } } ] } )",
         {
             make_tuple(2, CalloutHandle::NEXT_STEP_CONTINUE),
             make_tuple(2, CalloutHandle::NEXT_STEP_SKIP),
         },
         /* use_prefix = */ true);
}

TEST_F(LeaseLimitV6, onePrefixLimitPerClientClassMultiThreading) {
    MultiThreadingTest mt;
    test(R"( { "client-classes": [ { "name": "foo",
                                     "user-context": { "limits": { "prefix-limit": 2 } } } ] } )",
         {
             make_tuple(2, CalloutHandle::NEXT_STEP_CONTINUE),
             make_tuple(2, CalloutHandle::NEXT_STEP_SKIP),
         },
         /* use_prefix = */ true);
}

// Check that a prefix limit by subnet ID works as expected for packets.
TEST_F(LeaseLimitV6, onePrefixLimitPerSubnet) {
    test(R"( { "subnet6": [ { "id": 1,
                              "user-context": { "limits": { "prefix-limit": 2 } } } ] } )",
         {
             make_tuple(2, CalloutHandle::NEXT_STEP_CONTINUE),
             make_tuple(2, CalloutHandle::NEXT_STEP_SKIP),
         },
         /* use_prefix = */ true);
}

TEST_F(LeaseLimitV6, onePrefixLimitPerSubnetMultiThreading) {
    MultiThreadingTest mt;
    test(R"( { "subnet6": [ { "id": 1,
                              "user-context": { "limits": { "prefix-limit": 2 } } } ] } )",
         {
             make_tuple(2, CalloutHandle::NEXT_STEP_CONTINUE),
             make_tuple(2, CalloutHandle::NEXT_STEP_SKIP),
         },
         /* use_prefix = */ true);
}

// Check that packets matched by multiple prefix limits by both client class and subnet ID result in
// the stricter limit having effect.
TEST_F(LeaseLimitV6, prefixLimitingPerClientClassAndSubnetID) {
    test(R"( { "client-classes": [ { "name": "foo",
                                     "user-context": { "limits": { "prefix-limit": 2 } } } ],
               "subnet6": [ { "id": 1,
                              "user-context": { "limits": { "prefix-limit": 4 } } } ] } )",
         {
             make_tuple(2, CalloutHandle::NEXT_STEP_CONTINUE),
             make_tuple(6, CalloutHandle::NEXT_STEP_SKIP),
         },
         /* use_prefix = */ true);
}

TEST_F(LeaseLimitV6, prefixLimitingPerClientClassAndSubnetIDMultiThreading) {
    MultiThreadingTest mt;
    test(R"( { "client-classes": [ { "name": "foo",
                                     "user-context": { "limits": { "prefix-limit": 2 } } } ],
               "subnet6": [ { "id": 1,
                              "user-context": { "limits": { "prefix-limit": 4 } } } ] } )",
         {
             make_tuple(2, CalloutHandle::NEXT_STEP_CONTINUE),
             make_tuple(6, CalloutHandle::NEXT_STEP_SKIP),
         },
         /* use_prefix = */ true);
}

// Check that packets matched by multiple prefix limits by both client class and subnet ID result in
// the stricter limit having effect.
TEST_F(LeaseLimitV6, prefixLimitingPerSubnetAndClientClass) {
    test(R"( { "client-classes": [ { "name": "foo",
                                     "user-context": { "limits": { "prefix-limit": 4 } } } ],
               "subnet6": [ { "id": 1,
                              "user-context": { "limits": { "prefix-limit": 2 } } } ] } )",
         {
             make_tuple(2, CalloutHandle::NEXT_STEP_CONTINUE),
             make_tuple(6, CalloutHandle::NEXT_STEP_SKIP),
         },
         /* use_prefix = */ true);
}

TEST_F(LeaseLimitV6, prefixLimitingPerSubnetAndClientClassMultiThreading) {
    MultiThreadingTest mt;
    test(R"( { "client-classes": [ { "name": "foo",
                                     "user-context": { "limits": { "prefix-limit": 4 } } } ],
               "subnet6": [ { "id": 1,
                              "user-context": { "limits": { "prefix-limit": 2 } } } ] } )",
         {
             make_tuple(2, CalloutHandle::NEXT_STEP_CONTINUE),
             make_tuple(6, CalloutHandle::NEXT_STEP_SKIP),
         },
         /* use_prefix = */ true);
}

// Check that a prefix limit of zero applied to built-in client classes effectively drops all packets.
TEST_F(LeaseLimitV6, zeroPrefixLimitPerBuiltInClientClass) {
    test(R"( { "client-classes": [ { "name": "ALL",
                                     "user-context": { "limits": { "prefix-limit": 0 } } } ],
               "subnet6": [ { "id": 1,
                              "user-context": { "limits": { "prefix-limit": 2 } } } ] } )",
         {
             make_tuple(4, CalloutHandle::NEXT_STEP_SKIP),
         },
         /* use_prefix = */ true);
}

TEST_F(LeaseLimitV6, zeroPrefixLimitPerBuiltInClientClassMultiThreading) {
    test(R"( { "client-classes": [ { "name": "ALL",
                                     "user-context": { "limits": { "prefix-limit": 0 } } } ],
               "subnet6": [ { "id": 1,
                              "user-context": { "limits": { "prefix-limit": 2 } } } ] } )",
         {
             make_tuple(4, CalloutHandle::NEXT_STEP_SKIP),
         },
         /* use_prefix = */ true);
}

// Check that a prefix limit of zero applied to client classes effectively drops all packets.
TEST_F(LeaseLimitV6, zeroPrefixLimitPerClientClass) {
    test(R"( { "client-classes": [ { "name": "foo",
                                     "user-context": { "limits": { "prefix-limit": 0 } } } ],
               "subnet6": [ { "id": 1,
                              "user-context": { "limits": { "prefix-limit": 2 } } } ] } )",
         {
             make_tuple(4, CalloutHandle::NEXT_STEP_SKIP),
         },
         /* use_prefix = */ true);
}

TEST_F(LeaseLimitV6, zeroPrefixLimitPerClientClassMultiThreading) {
    test(R"( { "client-classes": [ { "name": "foo",
                                     "user-context": { "limits": { "prefix-limit": 0 } } } ],
               "subnet6": [ { "id": 1,
                              "user-context": { "limits": { "prefix-limit": 2 } } } ] } )",
         {
             make_tuple(4, CalloutHandle::NEXT_STEP_SKIP),
         },
         /* use_prefix = */ true);
}

// Check that a prefix limit of zero applied to subnet IDs effectively drops all packets.
TEST_F(LeaseLimitV6, zeroPrefixLimitPerSubnet) {
    test(R"( { "client-classes": [ { "name": "foo",
                                     "user-context": { "limits": { "prefix-limit": 2 } } } ],
               "subnet6": [ { "id": 1,
                              "user-context": { "limits": { "prefix-limit": 0 } } } ] } )",
         {
             make_tuple(4, CalloutHandle::NEXT_STEP_SKIP),
         },
         /* use_prefix = */ true);
}

TEST_F(LeaseLimitV6, zeroPrefixLimitPerSubnetMultiThreading) {
    MultiThreadingTest mt;
    test(R"( { "client-classes": [ { "name": "foo",
                                     "user-context": { "limits": { "prefix-limit": 2 } } } ],
               "subnet6": [ { "id": 1,
                              "user-context": { "limits": { "prefix-limit": 0 } } } ] } )",
         {
             make_tuple(4, CalloutHandle::NEXT_STEP_SKIP),
         },
         /* use_prefix = */ true);
}

// Check that a drop caused by a prefix limit applied to a subsequently assigned client class, here
// "bar", does not affect the internal packet counts for client classes that were assigned
// before it, here "foo".
TEST_F(LeaseLimitV6, noSideEffectOfPacketsDroppedByClientClassWhenPrefixLimiting) {
    // Make a callout manager.
    boost::shared_ptr<CalloutManager> manager(boost::make_shared<CalloutManager>());

    // Configure.
    parseConfig(R"( { "client-classes": [ { "name": "foo",
                                            "user-context": { "limits": { "prefix-limit": 2 } } },
                                          { "name": "bar",
                                            "user-context": { "limits": { "prefix-limit": 1 } } } ] } )");

    // Should be accepted.
    sendPacketAndExpectStatus(manager, {"foo", "bar"}, CalloutHandle::NEXT_STEP_CONTINUE,
                              /* use_prefix = */ true);

    // Should be dropped because of the "bar" limit.
    sendPacketAndExpectStatus(manager, {"foo", "bar"}, CalloutHandle::NEXT_STEP_SKIP,
                              /* use_prefix = */ true);

    // Should be accepted.
    sendPacketAndExpectStatus(manager, {"foo"}, CalloutHandle::NEXT_STEP_CONTINUE,
                              /* use_prefix = */ true);

    // Should be dropped because of the "foo" limit.
    sendPacketAndExpectStatus(manager, {"foo"}, CalloutHandle::NEXT_STEP_SKIP,
                              /* use_prefix = */ true);
}

TEST_F(LeaseLimitV6, noSideEffectOfPacketsDroppedByClientClassWhenPrefixLimitingMultiThreading) {
    MultiThreadingTest mt;

    // Make a callout manager.
    boost::shared_ptr<CalloutManager> manager(boost::make_shared<CalloutManager>());

    // Configure.
    parseConfig(R"( { "client-classes": [ { "name": "foo",
                                            "user-context": { "limits": { "prefix-limit": 2 } } },
                                          { "name": "bar",
                                            "user-context": { "limits": { "prefix-limit": 1 } } } ] } )");

    // Should be accepted.
    sendPacketAndExpectStatus(manager, {"foo", "bar"}, CalloutHandle::NEXT_STEP_CONTINUE,
                              /* use_prefix = */ true);

    // Should be dropped because of the "bar" limit.
    sendPacketAndExpectStatus(manager, {"foo", "bar"}, CalloutHandle::NEXT_STEP_SKIP,
                              /* use_prefix = */ true);

    // Should be accepted.
    sendPacketAndExpectStatus(manager, {"foo"}, CalloutHandle::NEXT_STEP_CONTINUE,
                              /* use_prefix = */ true);

    // Should be dropped because of the "foo" limit.
    sendPacketAndExpectStatus(manager, {"foo"}, CalloutHandle::NEXT_STEP_SKIP,
                              /* use_prefix = */ true);
}

// Check that a mix of address/prefix limits set on classes/subnets behave as expected.
TEST_F(LeaseLimitV6, complex) {
    // Make a callout manager.
    boost::shared_ptr<CalloutManager> manager(boost::make_shared<CalloutManager>());

    // Configure.
    parseConfig(R"( { "client-classes": [ { "name": "foo",
                                     "user-context": { "limits": { "address-limit": 1,
                                                                   "prefix-limit": 2 } } },
                                   { "name": "bar",
                                     "user-context": { "limits": { "address-limit": 5,
                                                                   "prefix-limit": 6 } } } ],
                      "subnet6": [ { "id": 1,
                                     "user-context": { "limits": { "address-limit": 3,
                                                                   "prefix-limit": 4 } } } ] } )");

    // NA should be accepted. Counters: bar 1/5, subnet 1/3.
    sendPacketAndExpectStatus(manager, {"bar"}, CalloutHandle::NEXT_STEP_CONTINUE);

    // PD should be accepted. Counters: bar 1/6, subnet 1/4.
    sendPacketAndExpectStatus(manager, {"bar"}, CalloutHandle::NEXT_STEP_CONTINUE,
                              /* use_prefix = */ true);

    // NA should be accepted. Counters: foo 1/1, bar 2/5, subnet 2/3.
    sendPacketAndExpectStatus(manager, {"foo", "bar"}, CalloutHandle::NEXT_STEP_CONTINUE);

    // NA should be skipped for exceeding foo limit.
    sendPacketAndExpectStatus(manager, {"foo", "bar"}, CalloutHandle::NEXT_STEP_SKIP);

    // 2 x foo bar PDs should still be accepted. Counters: foo 2/2, bar 3/6, subnet 3/4.
    sendPacketAndExpectStatus(manager, {"foo", "bar"}, CalloutHandle::NEXT_STEP_CONTINUE,
                              /* use_prefix = */ true);
    sendPacketAndExpectStatus(manager, {"foo", "bar"}, CalloutHandle::NEXT_STEP_CONTINUE,
                              /* use_prefix = */ true);

    // But another one should also reach the foo limit.
    sendPacketAndExpectStatus(manager, {"foo", "bar"}, CalloutHandle::NEXT_STEP_SKIP,
                              /* use_prefix = */ true);

    // NA subnet 3/3.
    sendPacketAndExpectStatus(manager, {"bar"}, CalloutHandle::NEXT_STEP_CONTINUE);

    // NA subnet exceeded.
    sendPacketAndExpectStatus(manager, {"bar"}, CalloutHandle::NEXT_STEP_SKIP);

    // PD subnet 4/4.
    sendPacketAndExpectStatus(manager, {"bar"}, CalloutHandle::NEXT_STEP_CONTINUE,
                              /* use_prefix = */ true);

    // PD subnet exceeded.
    sendPacketAndExpectStatus(manager, {"bar"}, CalloutHandle::NEXT_STEP_SKIP,
                              /* use_prefix = */ true);
}

// Check that a mix of address/prefix limits set on classes/subnets behave as expected.
TEST_F(LeaseLimitV6, complexMultiThreading) {
    MultiThreadingTest mt;
    // Make a callout manager.
    boost::shared_ptr<CalloutManager> manager(boost::make_shared<CalloutManager>());

    // Configure.
    parseConfig(R"( { "client-classes": [ { "name": "foo",
                                     "user-context": { "limits": { "address-limit": 1,
                                                                   "prefix-limit": 2 } } },
                                   { "name": "bar",
                                     "user-context": { "limits": { "address-limit": 5,
                                                                   "prefix-limit": 6 } } } ],
                      "subnet6": [ { "id": 1,
                                     "user-context": { "limits": { "address-limit": 3,
                                                                   "prefix-limit": 4 } } } ] } )");

    // NA should be accepted. Counters: bar 1/5, subnet 1/3.
    sendPacketAndExpectStatus(manager, {"bar"}, CalloutHandle::NEXT_STEP_CONTINUE);

    // PD should be accepted. Counters: bar 1/6, subnet 1/4.
    sendPacketAndExpectStatus(manager, {"bar"}, CalloutHandle::NEXT_STEP_CONTINUE,
                              /* use_prefix = */ true);

    // NA should be accepted. Counters: foo 1/1, bar 2/5, subnet 2/3.
    sendPacketAndExpectStatus(manager, {"foo", "bar"}, CalloutHandle::NEXT_STEP_CONTINUE);

    // NA should be skipped for exceeding foo limit.
    sendPacketAndExpectStatus(manager, {"foo", "bar"}, CalloutHandle::NEXT_STEP_SKIP);

    // 2 x foo bar PDs should still be accepted. Counters: foo 2/2, bar 3/6, subnet 3/4.
    sendPacketAndExpectStatus(manager, {"foo", "bar"}, CalloutHandle::NEXT_STEP_CONTINUE,
                              /* use_prefix = */ true);
    sendPacketAndExpectStatus(manager, {"foo", "bar"}, CalloutHandle::NEXT_STEP_CONTINUE,
                              /* use_prefix = */ true);

    // But another one should also reach the foo limit.
    sendPacketAndExpectStatus(manager, {"foo", "bar"}, CalloutHandle::NEXT_STEP_SKIP,
                              /* use_prefix = */ true);

    // NA subnet 3/3.
    sendPacketAndExpectStatus(manager, {"bar"}, CalloutHandle::NEXT_STEP_CONTINUE);

    // NA subnet exceeded.
    sendPacketAndExpectStatus(manager, {"bar"}, CalloutHandle::NEXT_STEP_SKIP);

    // PD subnet 4/4.
    sendPacketAndExpectStatus(manager, {"bar"}, CalloutHandle::NEXT_STEP_CONTINUE,
                              /* use_prefix = */ true);

    // PD subnet exceeded.
    sendPacketAndExpectStatus(manager, {"bar"}, CalloutHandle::NEXT_STEP_SKIP,
                              /* use_prefix = */ true);
}

// Check that an address limit by client class works as expected for v4 packets.
TEST_F(LeaseLimitV4, oneLimitPerTemplateClientClass) {
    test(R"( { "client-classes": [ { "name": "foo",
                                     "template-test": "",
                                     "user-context": { "limits": { "address-limit": 2 } } } ] } )",
         {
             make_tuple(2, CalloutHandle::NEXT_STEP_CONTINUE),
             make_tuple(2, CalloutHandle::NEXT_STEP_SKIP),
         }, false, true);
}

TEST_F(LeaseLimitV4, oneLimitPerTemplateClientClassMultiThreading) {
    MultiThreadingTest mt;
    test(R"( { "client-classes": [ { "name": "foo",
                                     "template-test": "",
                                     "user-context": { "limits": { "address-limit": 2 } } } ] } )",
         {
             make_tuple(2, CalloutHandle::NEXT_STEP_CONTINUE),
             make_tuple(2, CalloutHandle::NEXT_STEP_SKIP),
         }, false, true);
}

// Check that an address limit by client class works as expected for v6 packets.
TEST_F(LeaseLimitV6, oneLimitPerTemplateClientClass) {
    test(R"( { "client-classes": [ { "name": "foo",
                                     "template-test": "",
                                     "user-context": { "limits": { "address-limit": 2 } } } ] } )",
         {
             make_tuple(2, CalloutHandle::NEXT_STEP_CONTINUE),
             make_tuple(2, CalloutHandle::NEXT_STEP_SKIP),
         }, false, true);
}

TEST_F(LeaseLimitV6, oneLimitPerTemplateClientClassMultiThreading) {
    MultiThreadingTest mt;
    test(R"( { "client-classes": [ { "name": "foo",
                                     "template-test": "",
                                     "user-context": { "limits": { "address-limit": 2 } } } ] } )",
         {
             make_tuple(2, CalloutHandle::NEXT_STEP_CONTINUE),
             make_tuple(2, CalloutHandle::NEXT_STEP_SKIP),
         }, false, true);
}

// Check that v4 packets matched by multiple limits by both client class and subnet ID result in the
// stricter limit having effect.
TEST_F(LeaseLimitV4, limitingPerTemplateClientClassAndSubnetID) {
    test(R"( { "client-classes": [ { "name": "foo",
                                     "template-test": "",
                                     "user-context": { "limits": { "address-limit": 2 } } } ],
               "subnet4": [ { "id": 1,
                              "user-context": { "limits": { "address-limit": 4 } } } ] } )",
         {
             make_tuple(2, CalloutHandle::NEXT_STEP_CONTINUE),
             make_tuple(6, CalloutHandle::NEXT_STEP_SKIP),
         }, false, true);
}

TEST_F(LeaseLimitV4, limitingPerTemplateClientClassAndSubnetIDMultiThreading) {
    MultiThreadingTest mt;
    test(R"( { "client-classes": [ { "name": "foo",
                                     "template-test": "",
                                     "user-context": { "limits": { "address-limit": 2 } } } ],
               "subnet4": [ { "id": 1,
                              "user-context": { "limits": { "address-limit": 4 } } } ] } )",
         {
             make_tuple(2, CalloutHandle::NEXT_STEP_CONTINUE),
             make_tuple(6, CalloutHandle::NEXT_STEP_SKIP),
         }, false, true);
}

// Check that v6 packets matched by multiple limits by both client class and subnet ID result in the
// stricter limit having effect.
TEST_F(LeaseLimitV6, limitingPerTemplateClientClassAndSubnetID) {
    test(R"( { "client-classes": [ { "name": "foo",
                                     "template-test": "",
                                     "user-context": { "limits": { "address-limit": 2 } } } ],
               "subnet6": [ { "id": 1,
                              "user-context": { "limits": { "address-limit": 4 } } } ] } )",
         {
             make_tuple(2, CalloutHandle::NEXT_STEP_CONTINUE),
             make_tuple(6, CalloutHandle::NEXT_STEP_SKIP),
         }, false, true);
}

TEST_F(LeaseLimitV6, limitingPerTemplateClientClassAndSubnetIDMultiThreading) {
    MultiThreadingTest mt;
    test(R"( { "client-classes": [ { "name": "foo",
                                     "template-test": "",
                                     "user-context": { "limits": { "address-limit": 2 } } } ],
               "subnet6": [ { "id": 1,
                              "user-context": { "limits": { "address-limit": 4 } } } ] } )",
         {
             make_tuple(2, CalloutHandle::NEXT_STEP_CONTINUE),
             make_tuple(6, CalloutHandle::NEXT_STEP_SKIP),
         }, false, true);
}

// Check that v4 packets matched by multiple limits by both client class and subnet ID result in the
// stricter limit having effect.
TEST_F(LeaseLimitV4, limitingPerSubnetAndTemplateClientClass) {
    test(R"( { "client-classes": [ { "name": "foo",
                                     "template-test": "",
                                     "user-context": { "limits": { "address-limit": 4 } } } ],
               "subnet4": [ { "id": 1,
                              "user-context": { "limits": { "address-limit": 2 } } } ] } )",
         {
             make_tuple(2, CalloutHandle::NEXT_STEP_CONTINUE),
             make_tuple(6, CalloutHandle::NEXT_STEP_SKIP),
         }, false, true);
}

TEST_F(LeaseLimitV4, limitingPerSubnetAndTemplateClientClassMultiThreading) {
    MultiThreadingTest mt;
    test(R"( { "client-classes": [ { "name": "foo",
                                     "template-test": "",
                                     "user-context": { "limits": { "address-limit": 4 } } } ],
               "subnet4": [ { "id": 1,
                              "user-context": { "limits": { "address-limit": 2 } } } ] } )",
         {
             make_tuple(2, CalloutHandle::NEXT_STEP_CONTINUE),
             make_tuple(6, CalloutHandle::NEXT_STEP_SKIP),
         }, false, true);
}

// Check that v6 packets matched by multiple limits by both client class and subnet ID result in the
// stricter limit having effect.
TEST_F(LeaseLimitV6, limitingPerSubnetAndTemplateClientClass) {
    test(R"( { "client-classes": [ { "name": "foo",
                                     "template-test": "",
                                     "user-context": { "limits": { "address-limit": 4 } } } ],
               "subnet6": [ { "id": 1,
                              "user-context": { "limits": { "address-limit": 2 } } } ] } )",
         {
             make_tuple(2, CalloutHandle::NEXT_STEP_CONTINUE),
             make_tuple(6, CalloutHandle::NEXT_STEP_SKIP),
         }, false, true);
}

TEST_F(LeaseLimitV6, limitingPerSubnetAndTemplateClientClassMultiThreading) {
    MultiThreadingTest mt;
    test(R"( { "client-classes": [ { "name": "foo",
                                     "template-test": "",
                                     "user-context": { "limits": { "address-limit": 4 } } } ],
               "subnet6": [ { "id": 1,
                              "user-context": { "limits": { "address-limit": 2 } } } ] } )",
         {
             make_tuple(2, CalloutHandle::NEXT_STEP_CONTINUE),
             make_tuple(6, CalloutHandle::NEXT_STEP_SKIP),
         }, false, true);
}

// Check that an address limit of zero applied to client classes effectively drops all v4 packets.
TEST_F(LeaseLimitV4, zeroLimitPerTemplateClientClass) {
    test(R"( { "client-classes": [ { "name": "foo",
                                     "template-test": "",
                                     "user-context": { "limits": { "address-limit": 0 } } } ],
               "subnet4": [ { "id": 1,
                              "user-context": { "limits": { "address-limit": 2 } } } ] } )",
         {
             make_tuple(4, CalloutHandle::NEXT_STEP_SKIP),
         }, false, true);
}

TEST_F(LeaseLimitV4, zeroLimitPerTemplateClientClassMultiThreading) {
    MultiThreadingTest mt;
    test(R"( { "client-classes": [ { "name": "foo",
                                     "template-test": "",
                                     "user-context": { "limits": { "address-limit": 0 } } } ],
               "subnet4": [ { "id": 1,
                              "user-context": { "limits": { "address-limit": 2 } } } ] } )",
         {
             make_tuple(4, CalloutHandle::NEXT_STEP_SKIP),
         }, false, true);
}

// Check that an address limit of zero applied to client classes effectively drops all v6 packets.
TEST_F(LeaseLimitV6, zeroLimitPerTemplateClientClass) {
    test(R"( { "client-classes": [ { "name": "foo",
                                     "template-test": "",
                                     "user-context": { "limits": { "address-limit": 0 } } } ],
               "subnet6": [ { "id": 1,
                              "user-context": { "limits": { "address-limit": 2 } } } ] } )",
         {
             make_tuple(4, CalloutHandle::NEXT_STEP_SKIP),
         }, false, true);
}

TEST_F(LeaseLimitV6, zeroLimitPerTemplateClientClassMultiThreading) {
    test(R"( { "client-classes": [ { "name": "foo",
                                     "template-test": "",
                                     "user-context": { "limits": { "address-limit": 0 } } } ],
               "subnet6": [ { "id": 1,
                              "user-context": { "limits": { "address-limit": 2 } } } ] } )",
         {
             make_tuple(4, CalloutHandle::NEXT_STEP_SKIP),
         }, false, true);
}

// Check that an address limit of zero applied to subnet IDs effectively drops all v4 packets.
TEST_F(LeaseLimitV4, zeroLimitPerSubnetWithTemplateClientClass) {
    test(R"( { "client-classes": [ { "name": "foo",
                                     "template-test": "",
                                     "user-context": { "limits": { "address-limit": 2 } } } ],
               "subnet4": [ { "id": 1,
                              "user-context": { "limits": { "address-limit": 0 } } } ] } )",
         {
             make_tuple(4, CalloutHandle::NEXT_STEP_SKIP),
         }, false, true);
}

TEST_F(LeaseLimitV4, zeroLimitPerSubnetWithTemplateClientClassMultiThreading) {
    MultiThreadingTest mt;
    test(R"( { "client-classes": [ { "name": "foo",
                                     "template-test": "",
                                     "user-context": { "limits": { "address-limit": 2 } } } ],
               "subnet4": [ { "id": 1,
                              "user-context": { "limits": { "address-limit": 0 } } } ] } )",
         {
             make_tuple(4, CalloutHandle::NEXT_STEP_SKIP),
         }, false, true);
}

// Check that an address limit of zero applied to subnet IDs effectively drops all v6 packets.
TEST_F(LeaseLimitV6, zeroLimitPerSubnetWithTemplateClientClass) {
    test(R"( { "client-classes": [ { "name": "foo",
                                     "template-test": "",
                                     "user-context": { "limits": { "address-limit": 2 } } } ],
               "subnet6": [ { "id": 1,
                              "user-context": { "limits": { "address-limit": 0 } } } ] } )",
         {
             make_tuple(4, CalloutHandle::NEXT_STEP_SKIP),
         }, false, true);
}

TEST_F(LeaseLimitV6, zeroLimitPerSubnetWithTemplateClientClassMultiThreading) {
    MultiThreadingTest mt;
    test(R"( { "client-classes": [ { "name": "foo",
                                     "template-test": "",
                                     "user-context": { "limits": { "address-limit": 2 } } } ],
               "subnet6": [ { "id": 1,
                              "user-context": { "limits": { "address-limit": 0 } } } ] } )",
         {
             make_tuple(4, CalloutHandle::NEXT_STEP_SKIP),
         }, false, true);
}

// Check that a drop caused by an address limit applied to a subsequently assigned client class,
// here "bar", does not affect the internal packet counts for client classes that were assigned
// before it, here "foo". The v4 version.
TEST_F(LeaseLimitV4, noSideEffectOfPacketsDroppedByTemplateClientClass) {
    // Make a callout manager.
    boost::shared_ptr<CalloutManager> manager(boost::make_shared<CalloutManager>());

    // Configure.
    parseConfig(R"( { "client-classes": [ { "name": "foo",
                                            "template-test": "",
                                            "user-context": { "limits": { "address-limit": 2 } } },
                                          { "name": "bar",
                                            "template-test": "",
                                            "user-context": { "limits": { "address-limit": 1 } } } ] } )");

    // Should be accepted.
    sendPacketAndExpectStatus(manager, {"foo", "bar"}, CalloutHandle::NEXT_STEP_CONTINUE, false, true);

    // Should be dropped because of the "bar" limit.
    sendPacketAndExpectStatus(manager, {"foo", "bar"}, CalloutHandle::NEXT_STEP_SKIP, false, true);

    // Should be accepted.
    sendPacketAndExpectStatus(manager, {"foo"}, CalloutHandle::NEXT_STEP_CONTINUE, false, true);

    // Should be dropped because of the "foo" limit.
    sendPacketAndExpectStatus(manager, {"foo"}, CalloutHandle::NEXT_STEP_SKIP, false, true);
}

TEST_F(LeaseLimitV4, noSideEffectOfPacketsDroppedByTemplateClientClassMultiThreading) {
    MultiThreadingTest mt;

    // Make a callout manager.
    boost::shared_ptr<CalloutManager> manager(boost::make_shared<CalloutManager>());

    // Configure.
    parseConfig(R"( { "client-classes": [ { "name": "foo",
                                            "template-test": "",
                                            "user-context": { "limits": { "address-limit": 2 } } },
                                          { "name": "bar",
                                            "template-test": "",
                                            "user-context": { "limits": { "address-limit": 1 } } } ] } )");

    // Should be accepted.
    sendPacketAndExpectStatus(manager, {"foo", "bar"}, CalloutHandle::NEXT_STEP_CONTINUE, false, true);

    // Should be dropped because of the "bar" limit.
    sendPacketAndExpectStatus(manager, {"foo", "bar"}, CalloutHandle::NEXT_STEP_SKIP, false, true);

    // Should be accepted.
    sendPacketAndExpectStatus(manager, {"foo"}, CalloutHandle::NEXT_STEP_CONTINUE, false, true);

    // Should be dropped because of the "foo" limit.
    sendPacketAndExpectStatus(manager, {"foo"}, CalloutHandle::NEXT_STEP_SKIP, false, true);
}

// Check that a drop caused by an address limit applied to a subsequently assigned client class,
// here "bar", does not affect the internal packet counts for client classes that were assigned
// before it, here "foo". The v6 version.
TEST_F(LeaseLimitV6, noSideEffectOfPacketsDroppedByTemplateClientClass) {
    // Make a callout manager.
    boost::shared_ptr<CalloutManager> manager(boost::make_shared<CalloutManager>());

    // Configure.
    parseConfig(R"( { "client-classes": [ { "name": "foo",
                                            "template-test": "",
                                            "user-context": { "limits": { "address-limit": 2 } } },
                                          { "name": "bar",
                                            "template-test": "",
                                            "user-context": { "limits": { "address-limit": 1 } } } ] } )");

    // Should be accepted.
    sendPacketAndExpectStatus(manager, {"foo", "bar"}, CalloutHandle::NEXT_STEP_CONTINUE, false, true);

    // Should be dropped because of the "bar" limit.
    sendPacketAndExpectStatus(manager, {"foo", "bar"}, CalloutHandle::NEXT_STEP_SKIP, false, true);

    // Should be accepted.
    sendPacketAndExpectStatus(manager, {"foo"}, CalloutHandle::NEXT_STEP_CONTINUE, false, true);

    // Should be dropped because of the "foo" limit.
    sendPacketAndExpectStatus(manager, {"foo"}, CalloutHandle::NEXT_STEP_SKIP, false, true);
}

TEST_F(LeaseLimitV6, noSideEffectOfPacketsDroppedByTemplateClientClassMultiThreading) {
    MultiThreadingTest mt;

    // Make a callout manager.
    boost::shared_ptr<CalloutManager> manager(boost::make_shared<CalloutManager>());

    // Configure.
    parseConfig(R"( { "client-classes": [ { "name": "foo",
                                            "template-test": "",
                                            "user-context": { "limits": { "address-limit": 2 } } },
                                          { "name": "bar",
                                            "template-test": "",
                                            "user-context": { "limits": { "address-limit": 1 } } } ] } )");

    // Should be accepted.
    sendPacketAndExpectStatus(manager, {"foo", "bar"}, CalloutHandle::NEXT_STEP_CONTINUE, false, true);

    // Should be dropped because of the "bar" limit.
    sendPacketAndExpectStatus(manager, {"foo", "bar"}, CalloutHandle::NEXT_STEP_SKIP, false, true);

    // Should be accepted.
    sendPacketAndExpectStatus(manager, {"foo"}, CalloutHandle::NEXT_STEP_CONTINUE, false, true);

    // Should be dropped because of the "foo" limit.
    sendPacketAndExpectStatus(manager, {"foo"}, CalloutHandle::NEXT_STEP_SKIP, false, true);
}

// Check that a prefix limit by client class works as expected for packets.
TEST_F(LeaseLimitV6, onePrefixLimitPerTemplateClientClass) {
    test(R"( { "client-classes": [ { "name": "foo",
                                     "template-test": "",
                                     "user-context": { "limits": { "prefix-limit": 2 } } } ] } )",
         {
             make_tuple(2, CalloutHandle::NEXT_STEP_CONTINUE),
             make_tuple(2, CalloutHandle::NEXT_STEP_SKIP),
         },
         /* use_prefix = */ true, true);
}

TEST_F(LeaseLimitV6, onePrefixLimitPerTemplateClientClassMultiThreading) {
    MultiThreadingTest mt;
    test(R"( { "client-classes": [ { "name": "foo",
                                     "template-test": "",
                                     "user-context": { "limits": { "prefix-limit": 2 } } } ] } )",
         {
             make_tuple(2, CalloutHandle::NEXT_STEP_CONTINUE),
             make_tuple(2, CalloutHandle::NEXT_STEP_SKIP),
         },
         /* use_prefix = */ true, true);
}

// Check that packets matched by multiple prefix limits by both client class and subnet ID result in
// the stricter limit having effect.
TEST_F(LeaseLimitV6, prefixLimitingPerTemplateClientClassAndSubnetID) {
    test(R"( { "client-classes": [ { "name": "foo",
                                     "template-test": "",
                                     "user-context": { "limits": { "prefix-limit": 2 } } } ],
               "subnet6": [ { "id": 1,
                              "user-context": { "limits": { "prefix-limit": 4 } } } ] } )",
         {
             make_tuple(2, CalloutHandle::NEXT_STEP_CONTINUE),
             make_tuple(6, CalloutHandle::NEXT_STEP_SKIP),
         },
         /* use_prefix = */ true, true);
}

TEST_F(LeaseLimitV6, prefixLimitingPerTemplateClientClassAndSubnetIDMultiThreading) {
    MultiThreadingTest mt;
    test(R"( { "client-classes": [ { "name": "foo",
                                     "template-test": "",
                                     "user-context": { "limits": { "prefix-limit": 2 } } } ],
               "subnet6": [ { "id": 1,
                              "user-context": { "limits": { "prefix-limit": 4 } } } ] } )",
         {
             make_tuple(2, CalloutHandle::NEXT_STEP_CONTINUE),
             make_tuple(6, CalloutHandle::NEXT_STEP_SKIP),
         },
         /* use_prefix = */ true, true);
}

// Check that packets matched by multiple prefix limits by both client class and subnet ID result in
// the stricter limit having effect.
TEST_F(LeaseLimitV6, prefixLimitingPerSubnetAndTemplateClientClass) {
    test(R"( { "client-classes": [ { "name": "foo",
                                     "template-test": "",
                                     "user-context": { "limits": { "prefix-limit": 4 } } } ],
               "subnet6": [ { "id": 1,
                              "user-context": { "limits": { "prefix-limit": 2 } } } ] } )",
         {
             make_tuple(2, CalloutHandle::NEXT_STEP_CONTINUE),
             make_tuple(6, CalloutHandle::NEXT_STEP_SKIP),
         },
         /* use_prefix = */ true, true);
}

TEST_F(LeaseLimitV6, prefixLimitingPerSubnetAndTemplateClientClassMultiThreading) {
    MultiThreadingTest mt;
    test(R"( { "client-classes": [ { "name": "foo",
                                     "template-test": "",
                                     "user-context": { "limits": { "prefix-limit": 4 } } } ],
               "subnet6": [ { "id": 1,
                              "user-context": { "limits": { "prefix-limit": 2 } } } ] } )",
         {
             make_tuple(2, CalloutHandle::NEXT_STEP_CONTINUE),
             make_tuple(6, CalloutHandle::NEXT_STEP_SKIP),
         },
         /* use_prefix = */ true, true);
}

// Check that a prefix limit of zero applied to client classes effectively drops all packets.
TEST_F(LeaseLimitV6, zeroPrefixLimitPerTemplateClientClass) {
    test(R"( { "client-classes": [ { "name": "foo",
                                     "template-test": "",
                                     "user-context": { "limits": { "prefix-limit": 0 } } } ],
               "subnet6": [ { "id": 1,
                              "user-context": { "limits": { "prefix-limit": 2 } } } ] } )",
         {
             make_tuple(4, CalloutHandle::NEXT_STEP_SKIP),
         },
         /* use_prefix = */ true, true);
}

TEST_F(LeaseLimitV6, zeroPrefixLimitPerTemplateClientClassMultiThreading) {
    test(R"( { "client-classes": [ { "name": "foo",
                                     "template-test": "",
                                     "user-context": { "limits": { "prefix-limit": 0 } } } ],
               "subnet6": [ { "id": 1,
                              "user-context": { "limits": { "prefix-limit": 2 } } } ] } )",
         {
             make_tuple(4, CalloutHandle::NEXT_STEP_SKIP),
         },
         /* use_prefix = */ true, true);
}

// Check that a prefix limit of zero applied to subnet IDs effectively drops all packets.
TEST_F(LeaseLimitV6, zeroPrefixLimitPerSubnetWithTemplateClientClass) {
    test(R"( { "client-classes": [ { "name": "foo",
                                     "template-test": "",
                                     "user-context": { "limits": { "prefix-limit": 2 } } } ],
               "subnet6": [ { "id": 1,
                              "user-context": { "limits": { "prefix-limit": 0 } } } ] } )",
         {
             make_tuple(4, CalloutHandle::NEXT_STEP_SKIP),
         },
         /* use_prefix = */ true, true);
}

TEST_F(LeaseLimitV6, zeroPrefixLimitPerSubnetWithTemplateClientClassMultiThreading) {
    MultiThreadingTest mt;
    test(R"( { "client-classes": [ { "name": "foo",
                                     "template-test": "",
                                     "user-context": { "limits": { "prefix-limit": 2 } } } ],
               "subnet6": [ { "id": 1,
                              "user-context": { "limits": { "prefix-limit": 0 } } } ] } )",
         {
             make_tuple(4, CalloutHandle::NEXT_STEP_SKIP),
         },
         /* use_prefix = */ true, true);
}

// Check that a drop caused by a prefix limit applied to a subsequently assigned client class, here
// "bar", does not affect the internal packet counts for client classes that were assigned
// before it, here "foo".
TEST_F(LeaseLimitV6, noSideEffectOfPacketsDroppedByTemplateClientClassWhenPrefixLimiting) {
    // Make a callout manager.
    boost::shared_ptr<CalloutManager> manager(boost::make_shared<CalloutManager>());

    // Configure.
    parseConfig(R"( { "client-classes": [ { "name": "foo",
                                            "template-test": "",
                                            "user-context": { "limits": { "prefix-limit": 2 } } },
                                          { "name": "bar",
                                            "template-test": "",
                                            "user-context": { "limits": { "prefix-limit": 1 } } } ] } )");

    // Should be accepted.
    sendPacketAndExpectStatus(manager, {"foo", "bar"}, CalloutHandle::NEXT_STEP_CONTINUE,
                              /* use_prefix = */ true, true);

    // Should be dropped because of the "bar" limit.
    sendPacketAndExpectStatus(manager, {"foo", "bar"}, CalloutHandle::NEXT_STEP_SKIP,
                              /* use_prefix = */ true, true);

    // Should be accepted.
    sendPacketAndExpectStatus(manager, {"foo"}, CalloutHandle::NEXT_STEP_CONTINUE,
                              /* use_prefix = */ true, true);

    // Should be dropped because of the "foo" limit.
    sendPacketAndExpectStatus(manager, {"foo"}, CalloutHandle::NEXT_STEP_SKIP,
                              /* use_prefix = */ true, true);
}

TEST_F(LeaseLimitV6, noSideEffectOfPacketsDroppedByTemplateClientClassWhenPrefixLimitingMultiThreading) {
    MultiThreadingTest mt;

    // Make a callout manager.
    boost::shared_ptr<CalloutManager> manager(boost::make_shared<CalloutManager>());

    // Configure.
    parseConfig(R"( { "client-classes": [ { "name": "foo",
                                            "template-test": "",
                                            "user-context": { "limits": { "prefix-limit": 2 } } },
                                          { "name": "bar",
                                            "template-test": "",
                                            "user-context": { "limits": { "prefix-limit": 1 } } } ] } )");

    // Should be accepted.
    sendPacketAndExpectStatus(manager, {"foo", "bar"}, CalloutHandle::NEXT_STEP_CONTINUE,
                              /* use_prefix = */ true, true);

    // Should be dropped because of the "bar" limit.
    sendPacketAndExpectStatus(manager, {"foo", "bar"}, CalloutHandle::NEXT_STEP_SKIP,
                              /* use_prefix = */ true, true);

    // Should be accepted.
    sendPacketAndExpectStatus(manager, {"foo"}, CalloutHandle::NEXT_STEP_CONTINUE,
                              /* use_prefix = */ true, true);

    // Should be dropped because of the "foo" limit.
    sendPacketAndExpectStatus(manager, {"foo"}, CalloutHandle::NEXT_STEP_SKIP,
                              /* use_prefix = */ true, true);
}

// Check that a mix of address/prefix limits set on classes/subnets behave as expected.
TEST_F(LeaseLimitV6, complexTemplateClientClasses) {
    // Make a callout manager.
    boost::shared_ptr<CalloutManager> manager(boost::make_shared<CalloutManager>());

    // Configure.
    parseConfig(R"( { "client-classes": [ { "name": "foo",
                                     "template-test": "",
                                     "user-context": { "limits": { "address-limit": 1,
                                                                   "prefix-limit": 2 } } },
                                   { "name": "bar",
                                     "template-test": "",
                                     "user-context": { "limits": { "address-limit": 5,
                                                                   "prefix-limit": 6 } } } ],
                      "subnet6": [ { "id": 1,
                                     "user-context": { "limits": { "address-limit": 3,
                                                                   "prefix-limit": 4 } } } ] } )");

    // NA should be accepted. Counters: bar 1/5, subnet 1/3.
    sendPacketAndExpectStatus(manager, {"bar"}, CalloutHandle::NEXT_STEP_CONTINUE, false, true);

    // PD should be accepted. Counters: bar 1/6, subnet 1/4.
    sendPacketAndExpectStatus(manager, {"bar"}, CalloutHandle::NEXT_STEP_CONTINUE,
                              /* use_prefix = */ true, true);

    // NA should be accepted. Counters: foo 1/1, bar 2/5, subnet 2/3.
    sendPacketAndExpectStatus(manager, {"foo", "bar"}, CalloutHandle::NEXT_STEP_CONTINUE, false, true);

    // NA should be skipped for exceeding foo limit.
    sendPacketAndExpectStatus(manager, {"foo", "bar"}, CalloutHandle::NEXT_STEP_SKIP, false, true);

    // 2 x foo bar PDs should still be accepted. Counters: foo 2/2, bar 3/6, subnet 3/4.
    sendPacketAndExpectStatus(manager, {"foo", "bar"}, CalloutHandle::NEXT_STEP_CONTINUE,
                              /* use_prefix = */ true, true);
    sendPacketAndExpectStatus(manager, {"foo", "bar"}, CalloutHandle::NEXT_STEP_CONTINUE,
                              /* use_prefix = */ true, true);

    // But another one should also reach the foo limit.
    sendPacketAndExpectStatus(manager, {"foo", "bar"}, CalloutHandle::NEXT_STEP_SKIP,
                              /* use_prefix = */ true, true);

    // NA subnet 3/3.
    sendPacketAndExpectStatus(manager, {"bar"}, CalloutHandle::NEXT_STEP_CONTINUE, false, true);

    // NA subnet exceeded.
    sendPacketAndExpectStatus(manager, {"bar"}, CalloutHandle::NEXT_STEP_SKIP, false, true);

    // PD subnet 4/4.
    sendPacketAndExpectStatus(manager, {"bar"}, CalloutHandle::NEXT_STEP_CONTINUE,
                              /* use_prefix = */ true, true);

    // PD subnet exceeded.
    sendPacketAndExpectStatus(manager, {"bar"}, CalloutHandle::NEXT_STEP_SKIP,
                              /* use_prefix = */ true, true);
}

// Check that a mix of address/prefix limits set on classes/subnets behave as expected.
TEST_F(LeaseLimitV6, complexTemplateClientClassesMultiThreading) {
    MultiThreadingTest mt;
    // Make a callout manager.
    boost::shared_ptr<CalloutManager> manager(boost::make_shared<CalloutManager>());

    // Configure.
    parseConfig(R"( { "client-classes": [ { "name": "foo",
                                     "template-test": "",
                                     "user-context": { "limits": { "address-limit": 1,
                                                                   "prefix-limit": 2 } } },
                                   { "name": "bar",
                                     "template-test": "",
                                     "user-context": { "limits": { "address-limit": 5,
                                                                   "prefix-limit": 6 } } } ],
                      "subnet6": [ { "id": 1,
                                     "user-context": { "limits": { "address-limit": 3,
                                                                   "prefix-limit": 4 } } } ] } )");

    // NA should be accepted. Counters: bar 1/5, subnet 1/3.
    sendPacketAndExpectStatus(manager, {"bar"}, CalloutHandle::NEXT_STEP_CONTINUE, false, true);

    // PD should be accepted. Counters: bar 1/6, subnet 1/4.
    sendPacketAndExpectStatus(manager, {"bar"}, CalloutHandle::NEXT_STEP_CONTINUE,
                              /* use_prefix = */ true, true);

    // NA should be accepted. Counters: foo 1/1, bar 2/5, subnet 2/3.
    sendPacketAndExpectStatus(manager, {"foo", "bar"}, CalloutHandle::NEXT_STEP_CONTINUE, false, true);

    // NA should be skipped for exceeding foo limit.
    sendPacketAndExpectStatus(manager, {"foo", "bar"}, CalloutHandle::NEXT_STEP_SKIP, false, true);

    // 2 x foo bar PDs should still be accepted. Counters: foo 2/2, bar 3/6, subnet 3/4.
    sendPacketAndExpectStatus(manager, {"foo", "bar"}, CalloutHandle::NEXT_STEP_CONTINUE,
                              /* use_prefix = */ true, true);
    sendPacketAndExpectStatus(manager, {"foo", "bar"}, CalloutHandle::NEXT_STEP_CONTINUE,
                              /* use_prefix = */ true, true);

    // But another one should also reach the foo limit.
    sendPacketAndExpectStatus(manager, {"foo", "bar"}, CalloutHandle::NEXT_STEP_SKIP,
                              /* use_prefix = */ true, true);

    // NA subnet 3/3.
    sendPacketAndExpectStatus(manager, {"bar"}, CalloutHandle::NEXT_STEP_CONTINUE, false, true);

    // NA subnet exceeded.
    sendPacketAndExpectStatus(manager, {"bar"}, CalloutHandle::NEXT_STEP_SKIP, false, true);

    // PD subnet 4/4.
    sendPacketAndExpectStatus(manager, {"bar"}, CalloutHandle::NEXT_STEP_CONTINUE,
                              /* use_prefix = */ true, true);

    // PD subnet exceeded.
    sendPacketAndExpectStatus(manager, {"bar"}, CalloutHandle::NEXT_STEP_SKIP,
                              /* use_prefix = */ true, true);
}

/// Check that limits are added to an already populated user context.
/// @{
TEST_F(LeaseLimitV4, existingUserContext) {
    testExistingUserContext();
}

TEST_F(LeaseLimitV4, existingUserContextMultiThreading) {
    MultiThreadingTest mt;
    testExistingUserContext();
}

TEST_F(LeaseLimitV6, existingUserContext) {
    testExistingUserContext();
}

TEST_F(LeaseLimitV6, existingUserContextMultiThreading) {
    MultiThreadingTest mt;
    testExistingUserContext();
}
/// @}

}  // namespace
