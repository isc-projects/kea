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
#include <testutils/multi_threading_utils.h>
#include <testutils/gtest_utils.h>

#include <gtest/gtest.h>

#include <chrono>
#include <thread>

namespace {

using namespace isc::dhcp;
using namespace isc::hooks;
using namespace isc::limits;
using namespace isc::util;

using isc::asiolink::IOAddress;
using isc::data::ConstElementPtr;
using isc::test::MultiThreadingTest;

// Fixture for loading, unloading libraries and for testing callouts.
template <isc::util::DhcpSpace D>
struct RateLimitFixture : ::testing::Test {
    // Parse a text representation of a configuration with user contexts in client classes and
    // subnets that resembles a Kea configuration, add it to staging and commit it.
    void parseConfig(std::string const& configuration) {
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
    /// @param use_template_classes if the test should use template classes or regular client
    ///     classes. Default: false.
    void sendPacketAndExpectStatus(boost::shared_ptr<CalloutManager> const& manager,
                                   std::vector<ClientClass> const& client_classes,
                                   CalloutHandle::CalloutNextStep expected_status,
                                   bool use_template_classes = false) {
        // Simulate a handle.
        CalloutHandle handle(manager);
        isc::dhcp::PktTPtr<D> packet(boost::make_shared<isc::dhcp::PktT<D>>(1, 128));
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
        handle.setArgument(isc::util::formatDhcpSpace<D>("query{}"), packet);
        handle.setArgument(isc::util::formatDhcpSpace<D>("subnet{}"), subnet);

        // Call the callouts of interest. The same handle is used for both which is not what
        // happens in real situations, but makes for a simplistic test.
        EXPECT_NO_THROW_LOG(LimitManager::instance().pkt_receive<D>(handle));
        EXPECT_NO_THROW_LOG(LimitManager::instance().subnet_select<D>(handle));

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
    /// @param use_template_classes if the test should use template classes or regular client
    ///     classes. Default: false.
    void
    test(std::string const& configuration,
         std::vector<std::tuple<unsigned int, CalloutHandle::CalloutNextStep>> const& expected_results,
         bool use_template_classes = false) {
        // Make a callout manager.
        boost::shared_ptr<CalloutManager> manager(boost::make_shared<CalloutManager>());

        // Configure.
        parseConfig(configuration);

        for (auto const& expected_result : expected_results) {
            for (unsigned int i = 0; i < std::get<0>(expected_result); ++i) {
                sendPacketAndExpectStatus(manager, {"foo", "bar"},
                                          std::get<1>(expected_result),
                                          use_template_classes);
            }
        }
    }

private:
    /// @brief convenience function to encapsulate creation of Subnet4 and Subnet6
    SubnetTPtr<D> createSubnet();
};

template <>
SubnetTPtr<DHCPv4>
RateLimitFixture<DHCPv4>::createSubnet() {
    return (boost::make_shared<isc::dhcp::Subnet4>(IOAddress("192.168.0.0"), 24, 900, 1800, 3600, 1));
}

template <>
SubnetTPtr<DHCPv6>
RateLimitFixture<DHCPv6>::createSubnet() {
    return (boost::make_shared<isc::dhcp::Subnet6>(IOAddress("2001:db8::"), 64, 450, 900, 1800, 3600, 1));
}

using RateLimitV4 = RateLimitFixture<DHCPv4>;
using RateLimitV6 = RateLimitFixture<DHCPv6>;

// Check that an empty configuration does not limit v4 packets.
TEST_F(RateLimitV4, emptyConfiguration) {
    test("{}", {std::make_tuple(4, CalloutHandle::NEXT_STEP_CONTINUE)});
}

TEST_F(RateLimitV4, emptyConfigurationMultiThreading) {
    MultiThreadingTest mt;
    test("{}", {std::make_tuple(4, CalloutHandle::NEXT_STEP_CONTINUE)});
}

// Check that an empty configuration does not limit v6 packets.
TEST_F(RateLimitV6, emptyConfiguration) {
    test("{}", {std::make_tuple(4, CalloutHandle::NEXT_STEP_CONTINUE)});
}

TEST_F(RateLimitV6, emptyConfigurationMultiThreading) {
    MultiThreadingTest mt;
    test("{}", {std::make_tuple(4, CalloutHandle::NEXT_STEP_CONTINUE)});
}

// Check that no limit by client class works as expected for v4 packets.
TEST_F(RateLimitV4, noLimitPerClientClass) {
    test(R"( { "client-classes": [ { "name": "foo",
                                     "user-context": { } } ] } )", {
        std::make_tuple(2, CalloutHandle::NEXT_STEP_CONTINUE)
    });
}

TEST_F(RateLimitV4, noLimitPerClientClassMultiThreading) {
    MultiThreadingTest mt;
    test(R"( { "client-classes": [ { "name": "foo",
                                     "user-context": { } } ] } )", {
        std::make_tuple(2, CalloutHandle::NEXT_STEP_CONTINUE)
    });
}

// Check that no limit by client class works as expected for v6 packets.
TEST_F(RateLimitV6, noLimitPerClientClass) {
    test(R"( { "client-classes": [ { "name": "foo",
                                     "user-context": { } } ] } )", {
        std::make_tuple(2, CalloutHandle::NEXT_STEP_CONTINUE)
    });
}

TEST_F(RateLimitV6, noLimitPerClientClassMultiThreading) {
    MultiThreadingTest mt;
    test(R"( { "client-classes": [ { "name": "foo",
                                     "user-context": { } } ] } )", {
        std::make_tuple(2, CalloutHandle::NEXT_STEP_CONTINUE)
    });
}

// Check that no limit by subnet ID works as expected for v4 packets.
TEST_F(RateLimitV4, noLimitPerSubnet) {
    test(R"( { "subnet4": [ { "id": 1,
                              "user-context": { } } ] } )", {
        std::make_tuple(2, CalloutHandle::NEXT_STEP_CONTINUE)
    });
}

TEST_F(RateLimitV4, noLimitPerSubnetMultiThreading) {
    MultiThreadingTest mt;
    test(R"( { "subnet4": [ { "id": 1,
                              "user-context": { } } ] } )", {
        std::make_tuple(2, CalloutHandle::NEXT_STEP_CONTINUE)
    });
}

// Check that no limit by subnet ID works as expected for v6 packets.
TEST_F(RateLimitV6, noLimitPerSubnet) {
    test(R"( { "subnet6": [ { "id": 1,
                              "user-context": { } } ] } )", {
        std::make_tuple(2, CalloutHandle::NEXT_STEP_CONTINUE)
    });
}

TEST_F(RateLimitV6, noLimitPerSubnetMultiThreading) {
    MultiThreadingTest mt;
    test(R"( { "subnet6": [ { "id": 1,
                              "user-context": { } } ] } )", {
        std::make_tuple(2, CalloutHandle::NEXT_STEP_CONTINUE)
    });
}

// Check that a limit by built-in client class works as expected for v4 packets.
TEST_F(RateLimitV4, oneLimitPerBuiltInClientClass) {
    test(R"( { "client-classes": [ { "name": "ALL",
                                     "user-context": { "limits": { "rate-limit": "2 packets per year" } } } ] } )", {
        std::make_tuple(2, CalloutHandle::NEXT_STEP_CONTINUE),
        std::make_tuple(2, CalloutHandle::NEXT_STEP_DROP),
    });
}

TEST_F(RateLimitV4, oneLimitPerBuiltInClientClassMultiThreading) {
    MultiThreadingTest mt;
    test(R"( { "client-classes": [ { "name": "ALL",
                                     "user-context": { "limits": { "rate-limit": "2 packets per year" } } } ] } )", {
        std::make_tuple(2, CalloutHandle::NEXT_STEP_CONTINUE),
        std::make_tuple(2, CalloutHandle::NEXT_STEP_DROP),
    });
}

// Check that a limit by built-in client class works as expected for v6 packets.
TEST_F(RateLimitV6, oneLimitPerBuiltInClientClass) {
    test(R"( { "client-classes": [ { "name": "ALL",
                                     "user-context": { "limits": { "rate-limit": "2 packets per year" } } } ] } )", {
        std::make_tuple(2, CalloutHandle::NEXT_STEP_CONTINUE),
        std::make_tuple(2, CalloutHandle::NEXT_STEP_DROP),
    });
}

TEST_F(RateLimitV6, oneLimitPerBuiltInClientClassMultiThreading) {
    MultiThreadingTest mt;
    test(R"( { "client-classes": [ { "name": "ALL",
                                     "user-context": { "limits": { "rate-limit": "2 packets per year" } } } ] } )", {
        std::make_tuple(2, CalloutHandle::NEXT_STEP_CONTINUE),
        std::make_tuple(2, CalloutHandle::NEXT_STEP_DROP),
    });
}

// Check that a limit by client class works as expected for v4 packets.
TEST_F(RateLimitV4, oneLimitPerClientClass) {
    test(R"( { "client-classes": [ { "name": "foo",
                                     "user-context": { "limits": { "rate-limit": "2 packets per year" } } } ] } )", {
        std::make_tuple(2, CalloutHandle::NEXT_STEP_CONTINUE),
        std::make_tuple(2, CalloutHandle::NEXT_STEP_DROP),
    });
}

TEST_F(RateLimitV4, oneLimitPerClientClassMultiThreading) {
    MultiThreadingTest mt;
    test(R"( { "client-classes": [ { "name": "foo",
                                     "user-context": { "limits": { "rate-limit": "2 packets per year" } } } ] } )", {
        std::make_tuple(2, CalloutHandle::NEXT_STEP_CONTINUE),
        std::make_tuple(2, CalloutHandle::NEXT_STEP_DROP),
    });
}

// Check that a limit by client class works as expected for v6 packets.
TEST_F(RateLimitV6, oneLimitPerClientClass) {
    test(R"( { "client-classes": [ { "name": "foo",
                                     "user-context": { "limits": { "rate-limit": "2 packets per year" } } } ] } )", {
        std::make_tuple(2, CalloutHandle::NEXT_STEP_CONTINUE),
        std::make_tuple(2, CalloutHandle::NEXT_STEP_DROP),
    });
}

TEST_F(RateLimitV6, oneLimitPerClientClassMultiThreading) {
    MultiThreadingTest mt;
    test(R"( { "client-classes": [ { "name": "foo",
                                     "user-context": { "limits": { "rate-limit": "2 packets per year" } } } ] } )", {
        std::make_tuple(2, CalloutHandle::NEXT_STEP_CONTINUE),
        std::make_tuple(2, CalloutHandle::NEXT_STEP_DROP),
    });
}

// Check that a limit by subnet ID works as expected for v4 packets.
TEST_F(RateLimitV4, oneLimitPerSubnet) {
    test(R"( { "subnet4": [ { "id": 1,
                              "user-context": { "limits": { "rate-limit": "2 packets per year" } } } ] } )", {
        std::make_tuple(2, CalloutHandle::NEXT_STEP_CONTINUE),
        std::make_tuple(2, CalloutHandle::NEXT_STEP_DROP),
    });
}

TEST_F(RateLimitV4, oneLimitPerSubnetMultiThreading) {
    MultiThreadingTest mt;
    test(R"( { "subnet4": [ { "id": 1,
                              "user-context": { "limits": { "rate-limit": "2 packets per year" } } } ] } )", {
        std::make_tuple(2, CalloutHandle::NEXT_STEP_CONTINUE),
        std::make_tuple(2, CalloutHandle::NEXT_STEP_DROP),
    });
}

// Check that a limit by subnet ID works as expected for v6 packets.
TEST_F(RateLimitV6, oneLimitPerSubnet) {
    test(R"( { "subnet6": [ { "id": 1,
                              "user-context": { "limits": { "rate-limit": "2 packets per year" } } } ] } )", {
        std::make_tuple(2, CalloutHandle::NEXT_STEP_CONTINUE),
        std::make_tuple(2, CalloutHandle::NEXT_STEP_DROP),
    });
}

TEST_F(RateLimitV6, oneLimitPerSubnetMultiThreading) {
    MultiThreadingTest mt;
    test(R"( { "subnet6": [ { "id": 1,
                              "user-context": { "limits": { "rate-limit": "2 packets per year" } } } ] } )", {
        std::make_tuple(2, CalloutHandle::NEXT_STEP_CONTINUE),
        std::make_tuple(2, CalloutHandle::NEXT_STEP_DROP),
    });
}

// Check that v4 packets matched by multiple limits by both client class and subnet ID result in the
// stricter limit having effect.
TEST_F(RateLimitV4, limitingPerClientClassAndSubnetID) {
    test(R"( { "client-classes": [ { "name": "foo",
                                     "user-context": { "limits": { "rate-limit": "2 packets per year" } } } ],
               "subnet4": [ { "id": 1,
                              "user-context": { "limits": { "rate-limit": "4 packets per year" } } } ] } )", {
        std::make_tuple(2, CalloutHandle::NEXT_STEP_CONTINUE),
        std::make_tuple(6, CalloutHandle::NEXT_STEP_DROP),
    });
}

TEST_F(RateLimitV4, limitingPerClientClassAndSubnetIDMultiThreading) {
    MultiThreadingTest mt;
    test(R"( { "client-classes": [ { "name": "foo",
                                     "user-context": { "limits": { "rate-limit": "2 packets per year" } } } ],
               "subnet4": [ { "id": 1,
                              "user-context": { "limits": { "rate-limit": "4 packets per year" } } } ] } )", {
        std::make_tuple(2, CalloutHandle::NEXT_STEP_CONTINUE),
        std::make_tuple(6, CalloutHandle::NEXT_STEP_DROP),
    });
}

// Check that v6 packets matched by multiple limits by both client class and subnet ID result in the
// stricter limit having effect.
TEST_F(RateLimitV6, limitingPerClientClassAndSubnetID) {
    test(R"( { "client-classes": [ { "name": "foo",
                                     "user-context": { "limits": { "rate-limit": "2 packets per year" } } } ],
               "subnet6": [ { "id": 1,
                              "user-context": { "limits": { "rate-limit": "4 packets per year" } } } ] } )", {
        std::make_tuple(2, CalloutHandle::NEXT_STEP_CONTINUE),
        std::make_tuple(6, CalloutHandle::NEXT_STEP_DROP),
    });
}

TEST_F(RateLimitV6, limitingPerClientClassAndSubnetIDMultiThreading) {
    MultiThreadingTest mt;
    test(R"( { "client-classes": [ { "name": "foo",
                                     "user-context": { "limits": { "rate-limit": "2 packets per year" } } } ],
               "subnet6": [ { "id": 1,
                              "user-context": { "limits": { "rate-limit": "4 packets per year" } } } ] } )", {
        std::make_tuple(2, CalloutHandle::NEXT_STEP_CONTINUE),
        std::make_tuple(6, CalloutHandle::NEXT_STEP_DROP),
    });
}

// Check that v4 packets matched by multiple limits by both client class and subnet ID result in the
// stricter limit having effect.
TEST_F(RateLimitV4, limitingPerSubnetAndClientClass) {
    test(R"( { "client-classes": [ { "name": "foo",
                                     "user-context": { "limits": { "rate-limit": "4 packets per year" } } } ],
               "subnet4": [ { "id": 1,
                              "user-context": { "limits": { "rate-limit": "2 packets per year" } } } ] } )", {
        std::make_tuple(2, CalloutHandle::NEXT_STEP_CONTINUE),
        std::make_tuple(6, CalloutHandle::NEXT_STEP_DROP),
    });
}

TEST_F(RateLimitV4, limitingPerSubnetAndClientClassMultiThreading) {
    MultiThreadingTest mt;
    test(R"( { "client-classes": [ { "name": "foo",
                                     "user-context": { "limits": { "rate-limit": "4 packets per year" } } } ],
               "subnet4": [ { "id": 1,
                              "user-context": { "limits": { "rate-limit": "2 packets per year" } } } ] } )", {
        std::make_tuple(2, CalloutHandle::NEXT_STEP_CONTINUE),
        std::make_tuple(6, CalloutHandle::NEXT_STEP_DROP),
    });
}

// Check that v6 packets matched by multiple limits by both client class and subnet ID result in the
// stricter limit having effect.
TEST_F(RateLimitV6, limitingPerSubnetAndClientClass) {
    test(R"( { "client-classes": [ { "name": "foo",
                                     "user-context": { "limits": { "rate-limit": "4 packets per year" } } } ],
               "subnet6": [ { "id": 1,
                              "user-context": { "limits": { "rate-limit": "2 packets per year" } } } ] } )", {
        std::make_tuple(2, CalloutHandle::NEXT_STEP_CONTINUE),
        std::make_tuple(6, CalloutHandle::NEXT_STEP_DROP),
    });
}

TEST_F(RateLimitV6, limitingPerSubnetAndClientClassMultiThreading) {
    MultiThreadingTest mt;
    test(R"( { "client-classes": [ { "name": "foo",
                                     "user-context": { "limits": { "rate-limit": "4 packets per year" } } } ],
               "subnet6": [ { "id": 1,
                              "user-context": { "limits": { "rate-limit": "2 packets per year" } } } ] } )", {
        std::make_tuple(2, CalloutHandle::NEXT_STEP_CONTINUE),
        std::make_tuple(6, CalloutHandle::NEXT_STEP_DROP),
    });
}

// Check that a limit of zero applied to built-in client classes effectively drops all v4 packets.
TEST_F(RateLimitV4, zeroLimitPerBuiltInClientClass) {
    test(R"( { "client-classes": [ { "name": "ALL",
                                     "user-context": { "limits": { "rate-limit": "0 packets per year" } } } ],
               "subnet4": [ { "id": 1,
                              "user-context": { "limits": { "rate-limit": "2 packets per year" } } } ] } )", {
        std::make_tuple(4, CalloutHandle::NEXT_STEP_DROP),
    });
}

TEST_F(RateLimitV4, zeroLimitPerBuiltInClientClassMultiThreading) {
    MultiThreadingTest mt;
    test(R"( { "client-classes": [ { "name": "ALL",
                                     "user-context": { "limits": { "rate-limit": "0 packets per year" } } } ],
               "subnet4": [ { "id": 1,
                              "user-context": { "limits": { "rate-limit": "2 packets per year" } } } ] } )", {
        std::make_tuple(4, CalloutHandle::NEXT_STEP_DROP),
    });
}

// Check that a limit of zero applied to built-in client classes effectively drops all v6 packets.
TEST_F(RateLimitV6, zeroLimitPerBuiltInClientClass) {
    test(R"( { "client-classes": [ { "name": "ALL",
                                     "user-context": { "limits": { "rate-limit": "0 packets per year" } } } ],
               "subnet6": [ { "id": 1,
                              "user-context": { "limits": { "rate-limit": "2 packets per year" } } } ] } )", {
        std::make_tuple(4, CalloutHandle::NEXT_STEP_DROP),
    });
}

TEST_F(RateLimitV6, zeroLimitPerBuiltInClientClassMultiThreading) {
    test(R"( { "client-classes": [ { "name": "ALL",
                                     "user-context": { "limits": { "rate-limit": "0 packets per year" } } } ],
               "subnet6": [ { "id": 1,
                              "user-context": { "limits": { "rate-limit": "2 packets per year" } } } ] } )", {
        std::make_tuple(4, CalloutHandle::NEXT_STEP_DROP),
    });
}

// Check that a limit of zero applied to client classes effectively drops all v4 packets.
TEST_F(RateLimitV4, zeroLimitPerClientClass) {
    test(R"( { "client-classes": [ { "name": "foo",
                                     "user-context": { "limits": { "rate-limit": "0 packets per year" } } } ],
               "subnet4": [ { "id": 1,
                              "user-context": { "limits": { "rate-limit": "2 packets per year" } } } ] } )", {
        std::make_tuple(4, CalloutHandle::NEXT_STEP_DROP),
    });
}

TEST_F(RateLimitV4, zeroLimitPerClientClassMultiThreading) {
    MultiThreadingTest mt;
    test(R"( { "client-classes": [ { "name": "foo",
                                     "user-context": { "limits": { "rate-limit": "0 packets per year" } } } ],
               "subnet4": [ { "id": 1,
                              "user-context": { "limits": { "rate-limit": "2 packets per year" } } } ] } )", {
        std::make_tuple(4, CalloutHandle::NEXT_STEP_DROP),
    });
}

// Check that a limit of zero applied to client classes effectively drops all v6 packets.
TEST_F(RateLimitV6, zeroLimitPerClientClass) {
    test(R"( { "client-classes": [ { "name": "foo",
                                     "user-context": { "limits": { "rate-limit": "0 packets per year" } } } ],
               "subnet6": [ { "id": 1,
                              "user-context": { "limits": { "rate-limit": "2 packets per year" } } } ] } )", {
        std::make_tuple(4, CalloutHandle::NEXT_STEP_DROP),
    });
}

TEST_F(RateLimitV6, zeroLimitPerClientClassMultiThreading) {
    test(R"( { "client-classes": [ { "name": "foo",
                                     "user-context": { "limits": { "rate-limit": "0 packets per year" } } } ],
               "subnet6": [ { "id": 1,
                              "user-context": { "limits": { "rate-limit": "2 packets per year" } } } ] } )", {
        std::make_tuple(4, CalloutHandle::NEXT_STEP_DROP),
    });
}

// Check that a limit of zero applied to subnet IDs effectively drops all v4 packets.
TEST_F(RateLimitV4, zeroLimitPerSubnet) {
    test(R"( { "client-classes": [ { "name": "foo",
                                     "user-context": { "limits": { "rate-limit": "2 packets per year" } } } ],
               "subnet4": [ { "id": 1,
                              "user-context": { "limits": { "rate-limit": "0 packets per year" } } } ] } )", {
        std::make_tuple(4, CalloutHandle::NEXT_STEP_DROP),
    });
}

TEST_F(RateLimitV4, zeroLimitPerSubnetMultiThreading) {
    MultiThreadingTest mt;
    test(R"( { "client-classes": [ { "name": "foo",
                                     "user-context": { "limits": { "rate-limit": "2 packets per year" } } } ],
               "subnet4": [ { "id": 1,
                              "user-context": { "limits": { "rate-limit": "0 packets per year" } } } ] } )", {
        std::make_tuple(4, CalloutHandle::NEXT_STEP_DROP),
    });
}

// Check that a limit of zero applied to subnet IDs effectively drops all v6 packets.
TEST_F(RateLimitV6, zeroLimitPerSubnet) {
    test(R"( { "client-classes": [ { "name": "foo",
                                     "user-context": { "limits": { "rate-limit": "2 packets per year" } } } ],
               "subnet6": [ { "id": 1,
                              "user-context": { "limits": { "rate-limit": "0 packets per year" } } } ] } )", {
        std::make_tuple(4, CalloutHandle::NEXT_STEP_DROP),
    });
}

TEST_F(RateLimitV6, zeroLimitPerSubnetMultiThreading) {
    MultiThreadingTest mt;
    test(R"( { "client-classes": [ { "name": "foo",
                                     "user-context": { "limits": { "rate-limit": "2 packets per year" } } } ],
               "subnet6": [ { "id": 1,
                              "user-context": { "limits": { "rate-limit": "0 packets per year" } } } ] } )", {
        std::make_tuple(4, CalloutHandle::NEXT_STEP_DROP),
    });
}

// Check that a drop caused by a limit applied to a subsequently assigned client class, here
// "bar", does not affect the internal packet counts for client classes that were assigned
// before it, here "foo". The v4 version.
TEST_F(RateLimitV4, noSideEffectOfPacketsDroppedByClientClass) {
    // Make a callout manager.
    boost::shared_ptr<CalloutManager> manager(boost::make_shared<CalloutManager>());

    // Configure.
    parseConfig(R"( { "client-classes": [ { "name": "foo",
                                            "user-context": { "limits": { "rate-limit": "2 packets per year" } } },
                                          { "name": "bar",
                                            "user-context": { "limits": { "rate-limit": "1 packets per year" } } } ] } )");

    // Should be accepted.
    sendPacketAndExpectStatus(manager, {"foo", "bar"}, CalloutHandle::NEXT_STEP_CONTINUE);

    // Should be dropped because of the "bar" limit.
    sendPacketAndExpectStatus(manager, {"foo", "bar"}, CalloutHandle::NEXT_STEP_DROP);

    // Should be accepted.
    sendPacketAndExpectStatus(manager, {"foo"}, CalloutHandle::NEXT_STEP_CONTINUE);

    // Should be dropped because of the "foo" limit.
    sendPacketAndExpectStatus(manager, {"foo"}, CalloutHandle::NEXT_STEP_DROP);
}

TEST_F(RateLimitV4, noSideEffectOfPacketsDroppedByClientClassMultiThreading) {
    MultiThreadingTest mt;

    // Make a callout manager.
    boost::shared_ptr<CalloutManager> manager(boost::make_shared<CalloutManager>());

    // Configure.
    parseConfig(R"( { "client-classes": [ { "name": "foo",
                                            "user-context": { "limits": { "rate-limit": "2 packets per year" } } },
                                          { "name": "bar",
                                            "user-context": { "limits": { "rate-limit": "1 packets per year" } } } ] } )");

    // Should be accepted.
    sendPacketAndExpectStatus(manager, {"foo", "bar"}, CalloutHandle::NEXT_STEP_CONTINUE);

    // Should be dropped because of the "bar" limit.
    sendPacketAndExpectStatus(manager, {"foo", "bar"}, CalloutHandle::NEXT_STEP_DROP);

    // Should be accepted.
    sendPacketAndExpectStatus(manager, {"foo"}, CalloutHandle::NEXT_STEP_CONTINUE);

    // Should be dropped because of the "foo" limit.
    sendPacketAndExpectStatus(manager, {"foo"}, CalloutHandle::NEXT_STEP_DROP);
}

// Check that a drop caused by a limit applied to a subsequently assigned client class, here
// "bar", does not affect the internal packet counts for client classes that were assigned
// before it, here "foo". The v6 version.
TEST_F(RateLimitV6, noSideEffectOfPacketsDroppedByClientClass) {
    // Make a callout manager.
    boost::shared_ptr<CalloutManager> manager(boost::make_shared<CalloutManager>());

    // Configure.
    parseConfig(R"( { "client-classes": [ { "name": "foo",
                                            "user-context": { "limits": { "rate-limit": "2 packets per year" } } },
                                          { "name": "bar",
                                            "user-context": { "limits": { "rate-limit": "1 packets per year" } } } ] } )");

    // Should be accepted.
    sendPacketAndExpectStatus(manager, {"foo", "bar"}, CalloutHandle::NEXT_STEP_CONTINUE);

    // Should be dropped because of the "bar" limit.
    sendPacketAndExpectStatus(manager, {"foo", "bar"}, CalloutHandle::NEXT_STEP_DROP);

    // Should be accepted.
    sendPacketAndExpectStatus(manager, {"foo"}, CalloutHandle::NEXT_STEP_CONTINUE);

    // Should be dropped because of the "foo" limit.
    sendPacketAndExpectStatus(manager, {"foo"}, CalloutHandle::NEXT_STEP_DROP);
}

TEST_F(RateLimitV6, noSideEffectOfPacketsDroppedByClientClassMultiThreading) {
    MultiThreadingTest mt;

    // Make a callout manager.
    boost::shared_ptr<CalloutManager> manager(boost::make_shared<CalloutManager>());

    // Configure.
    parseConfig(R"( { "client-classes": [ { "name": "foo",
                                            "user-context": { "limits": { "rate-limit": "2 packets per year" } } },
                                          { "name": "bar",
                                            "user-context": { "limits": { "rate-limit": "1 packets per year" } } } ] } )");

    // Should be accepted.
    sendPacketAndExpectStatus(manager, {"foo", "bar"}, CalloutHandle::NEXT_STEP_CONTINUE);

    // Should be dropped because of the "bar" limit.
    sendPacketAndExpectStatus(manager, {"foo", "bar"}, CalloutHandle::NEXT_STEP_DROP);

    // Should be accepted.
    sendPacketAndExpectStatus(manager, {"foo"}, CalloutHandle::NEXT_STEP_CONTINUE);

    // Should be dropped because of the "foo" limit.
    sendPacketAndExpectStatus(manager, {"foo"}, CalloutHandle::NEXT_STEP_DROP);
}

// Check that v4 packets are correctly counted when the limit expires. Test is time-sensitive.
TEST_F(RateLimitV4, limitExpires) {
    // Make a callout manager.
    boost::shared_ptr<CalloutManager> manager(boost::make_shared<CalloutManager>());

    // Configure.
    parseConfig(R"( { "client-classes": [ { "name": "foo",
                                            "user-context": { "limits": { "rate-limit": "2 packets per second" } } } ] } )");

    sendPacketAndExpectStatus(manager, {"bar", "foo"}, CalloutHandle::NEXT_STEP_CONTINUE);
    sendPacketAndExpectStatus(manager, {"foo", "bar"}, CalloutHandle::NEXT_STEP_CONTINUE);
    sendPacketAndExpectStatus(manager, {"bar", "foo"}, CalloutHandle::NEXT_STEP_DROP);
    sendPacketAndExpectStatus(manager, {"foo", "bar"}, CalloutHandle::NEXT_STEP_DROP);

    std::this_thread::sleep_for(std::chrono::seconds(1));

    sendPacketAndExpectStatus(manager, {"bar", "foo"}, CalloutHandle::NEXT_STEP_CONTINUE);
    sendPacketAndExpectStatus(manager, {"foo", "bar"}, CalloutHandle::NEXT_STEP_CONTINUE);
    sendPacketAndExpectStatus(manager, {"bar", "foo"}, CalloutHandle::NEXT_STEP_DROP);
    sendPacketAndExpectStatus(manager, {"foo", "bar"}, CalloutHandle::NEXT_STEP_DROP);
}

TEST_F(RateLimitV4, limitExpiresMultiThreading) {
    MultiThreadingTest mt;

    // Make a callout manager.
    boost::shared_ptr<CalloutManager> manager(boost::make_shared<CalloutManager>());

    // Configure.
    parseConfig(R"( { "client-classes": [ { "name": "foo",
                                            "user-context": { "limits": { "rate-limit": "2 packets per second" } } } ] } )");

    sendPacketAndExpectStatus(manager, {"bar", "foo"}, CalloutHandle::NEXT_STEP_CONTINUE);
    sendPacketAndExpectStatus(manager, {"foo", "bar"}, CalloutHandle::NEXT_STEP_CONTINUE);
    sendPacketAndExpectStatus(manager, {"bar", "foo"}, CalloutHandle::NEXT_STEP_DROP);
    sendPacketAndExpectStatus(manager, {"foo", "bar"}, CalloutHandle::NEXT_STEP_DROP);

    std::this_thread::sleep_for(std::chrono::seconds(1));

    sendPacketAndExpectStatus(manager, {"bar", "foo"}, CalloutHandle::NEXT_STEP_CONTINUE);
    sendPacketAndExpectStatus(manager, {"foo", "bar"}, CalloutHandle::NEXT_STEP_CONTINUE);
    sendPacketAndExpectStatus(manager, {"bar", "foo"}, CalloutHandle::NEXT_STEP_DROP);
    sendPacketAndExpectStatus(manager, {"foo", "bar"}, CalloutHandle::NEXT_STEP_DROP);
}

// Check that v6 packets are correctly counted when the limit expires. Test is time-sensitive.
TEST_F(RateLimitV6, limitExpires) {
    // Make a callout manager.
    boost::shared_ptr<CalloutManager> manager(boost::make_shared<CalloutManager>());

    // Configure.
    parseConfig(R"( { "client-classes": [ { "name": "foo",
                                            "user-context": { "limits": { "rate-limit": "2 packets per second" } } } ] } )");

    sendPacketAndExpectStatus(manager, {"bar", "foo"}, CalloutHandle::NEXT_STEP_CONTINUE);
    sendPacketAndExpectStatus(manager, {"foo", "bar"}, CalloutHandle::NEXT_STEP_CONTINUE);
    sendPacketAndExpectStatus(manager, {"bar", "foo"}, CalloutHandle::NEXT_STEP_DROP);
    sendPacketAndExpectStatus(manager, {"foo", "bar"}, CalloutHandle::NEXT_STEP_DROP);

    std::this_thread::sleep_for(std::chrono::seconds(1));

    sendPacketAndExpectStatus(manager, {"bar", "foo"}, CalloutHandle::NEXT_STEP_CONTINUE);
    sendPacketAndExpectStatus(manager, {"foo", "bar"}, CalloutHandle::NEXT_STEP_CONTINUE);
    sendPacketAndExpectStatus(manager, {"bar", "foo"}, CalloutHandle::NEXT_STEP_DROP);
    sendPacketAndExpectStatus(manager, {"foo", "bar"}, CalloutHandle::NEXT_STEP_DROP);
}

TEST_F(RateLimitV6, limitExpiresMultiThreading) {
    MultiThreadingTest mt;

    // Make a callout manager.
    boost::shared_ptr<CalloutManager> manager(boost::make_shared<CalloutManager>());

    // Configure.
    parseConfig(R"( { "client-classes": [ { "name": "foo",
                                            "user-context": { "limits": { "rate-limit": "2 packets per second" } } } ] } )");

    sendPacketAndExpectStatus(manager, {"bar", "foo"}, CalloutHandle::NEXT_STEP_CONTINUE);
    sendPacketAndExpectStatus(manager, {"foo", "bar"}, CalloutHandle::NEXT_STEP_CONTINUE);
    sendPacketAndExpectStatus(manager, {"bar", "foo"}, CalloutHandle::NEXT_STEP_DROP);
    sendPacketAndExpectStatus(manager, {"foo", "bar"}, CalloutHandle::NEXT_STEP_DROP);

    std::this_thread::sleep_for(std::chrono::seconds(1));

    sendPacketAndExpectStatus(manager, {"bar", "foo"}, CalloutHandle::NEXT_STEP_CONTINUE);
    sendPacketAndExpectStatus(manager, {"foo", "bar"}, CalloutHandle::NEXT_STEP_CONTINUE);
    sendPacketAndExpectStatus(manager, {"bar", "foo"}, CalloutHandle::NEXT_STEP_DROP);
    sendPacketAndExpectStatus(manager, {"foo", "bar"}, CalloutHandle::NEXT_STEP_DROP);
}

// Check that a limit by client class works as expected for v4 packets.
TEST_F(RateLimitV4, oneLimitPerTemplateClientClass) {
    test(R"( { "client-classes": [ { "name": "foo",
                                     "template-test": "",
                                     "user-context": { "limits": { "rate-limit": "2 packets per year" } } } ] } )", {
        std::make_tuple(2, CalloutHandle::NEXT_STEP_CONTINUE),
        std::make_tuple(2, CalloutHandle::NEXT_STEP_DROP),
    }, true);
}

TEST_F(RateLimitV4, oneLimitPerTemplateClientClassMultiThreading) {
    MultiThreadingTest mt;
    test(R"( { "client-classes": [ { "name": "foo",
                                     "template-test": "",
                                     "user-context": { "limits": { "rate-limit": "2 packets per year" } } } ] } )", {
        std::make_tuple(2, CalloutHandle::NEXT_STEP_CONTINUE),
        std::make_tuple(2, CalloutHandle::NEXT_STEP_DROP),
    }, true);
}

// Check that a limit by client class works as expected for v6 packets.
TEST_F(RateLimitV6, oneLimitPerTemplateClientClass) {
    test(R"( { "client-classes": [ { "name": "foo",
                                     "template-test": "",
                                     "user-context": { "limits": { "rate-limit": "2 packets per year" } } } ] } )", {
        std::make_tuple(2, CalloutHandle::NEXT_STEP_CONTINUE),
        std::make_tuple(2, CalloutHandle::NEXT_STEP_DROP),
    }, true);
}

TEST_F(RateLimitV6, oneLimitPerTemplateClientClassMultiThreading) {
    MultiThreadingTest mt;
    test(R"( { "client-classes": [ { "name": "foo",
                                     "template-test": "",
                                     "user-context": { "limits": { "rate-limit": "2 packets per year" } } } ] } )", {
        std::make_tuple(2, CalloutHandle::NEXT_STEP_CONTINUE),
        std::make_tuple(2, CalloutHandle::NEXT_STEP_DROP),
    }, true);
}

// Check that v4 packets matched by multiple limits by both client class and subnet ID result in the
// stricter limit having effect.
TEST_F(RateLimitV4, limitingPerTemplateClientClassAndSubnetID) {
    test(R"( { "client-classes": [ { "name": "foo",
                                     "template-test": "",
                                     "user-context": { "limits": { "rate-limit": "2 packets per year" } } } ],
               "subnet4": [ { "id": 1,
                              "user-context": { "limits": { "rate-limit": "4 packets per year" } } } ] } )", {
        std::make_tuple(2, CalloutHandle::NEXT_STEP_CONTINUE),
        std::make_tuple(6, CalloutHandle::NEXT_STEP_DROP),
    }, true);
}

TEST_F(RateLimitV4, limitingPerTemplateClientClassAndSubnetIDMultiThreading) {
    MultiThreadingTest mt;
    test(R"( { "client-classes": [ { "name": "foo",
                                     "template-test": "",
                                     "user-context": { "limits": { "rate-limit": "2 packets per year" } } } ],
               "subnet4": [ { "id": 1,
                              "user-context": { "limits": { "rate-limit": "4 packets per year" } } } ] } )", {
        std::make_tuple(2, CalloutHandle::NEXT_STEP_CONTINUE),
        std::make_tuple(6, CalloutHandle::NEXT_STEP_DROP),
    }, true);
}

// Check that v6 packets matched by multiple limits by both client class and subnet ID result in the
// stricter limit having effect.
TEST_F(RateLimitV6, limitingPerTemplateClientClassAndSubnetID) {
    test(R"( { "client-classes": [ { "name": "foo",
                                     "template-test": "",
                                     "user-context": { "limits": { "rate-limit": "2 packets per year" } } } ],
               "subnet6": [ { "id": 1,
                              "user-context": { "limits": { "rate-limit": "4 packets per year" } } } ] } )", {
        std::make_tuple(2, CalloutHandle::NEXT_STEP_CONTINUE),
        std::make_tuple(6, CalloutHandle::NEXT_STEP_DROP),
    }, true);
}

TEST_F(RateLimitV6, limitingPerTemplateClientClassAndSubnetIDMultiThreading) {
    MultiThreadingTest mt;
    test(R"( { "client-classes": [ { "name": "foo",
                                     "template-test": "",
                                     "user-context": { "limits": { "rate-limit": "2 packets per year" } } } ],
               "subnet6": [ { "id": 1,
                              "user-context": { "limits": { "rate-limit": "4 packets per year" } } } ] } )", {
        std::make_tuple(2, CalloutHandle::NEXT_STEP_CONTINUE),
        std::make_tuple(6, CalloutHandle::NEXT_STEP_DROP),
    }, true);
}

// Check that v4 packets matched by multiple limits by both client class and subnet ID result in the
// stricter limit having effect.
TEST_F(RateLimitV4, limitingPerSubnetAndTemplateClientClass) {
    test(R"( { "client-classes": [ { "name": "foo",
                                     "template-test": "",
                                     "user-context": { "limits": { "rate-limit": "4 packets per year" } } } ],
               "subnet4": [ { "id": 1,
                              "user-context": { "limits": { "rate-limit": "2 packets per year" } } } ] } )", {
        std::make_tuple(2, CalloutHandle::NEXT_STEP_CONTINUE),
        std::make_tuple(6, CalloutHandle::NEXT_STEP_DROP),
    }, true);
}

TEST_F(RateLimitV4, limitingPerSubnetAndTemplateClientClassMultiThreading) {
    MultiThreadingTest mt;
    test(R"( { "client-classes": [ { "name": "foo",
                                     "template-test": "",
                                     "user-context": { "limits": { "rate-limit": "4 packets per year" } } } ],
               "subnet4": [ { "id": 1,
                              "user-context": { "limits": { "rate-limit": "2 packets per year" } } } ] } )", {
        std::make_tuple(2, CalloutHandle::NEXT_STEP_CONTINUE),
        std::make_tuple(6, CalloutHandle::NEXT_STEP_DROP),
    }, true);
}

// Check that v6 packets matched by multiple limits by both client class and subnet ID result in the
// stricter limit having effect.
TEST_F(RateLimitV6, limitingPerSubnetAndTemplateClientClass) {
    test(R"( { "client-classes": [ { "name": "foo",
                                     "template-test": "",
                                     "user-context": { "limits": { "rate-limit": "4 packets per year" } } } ],
               "subnet6": [ { "id": 1,
                              "user-context": { "limits": { "rate-limit": "2 packets per year" } } } ] } )", {
        std::make_tuple(2, CalloutHandle::NEXT_STEP_CONTINUE),
        std::make_tuple(6, CalloutHandle::NEXT_STEP_DROP),
    }, true);
}

TEST_F(RateLimitV6, limitingPerSubnetAndTemplateClientClassMultiThreading) {
    MultiThreadingTest mt;
    test(R"( { "client-classes": [ { "name": "foo",
                                     "template-test": "",
                                     "user-context": { "limits": { "rate-limit": "4 packets per year" } } } ],
               "subnet6": [ { "id": 1,
                              "user-context": { "limits": { "rate-limit": "2 packets per year" } } } ] } )", {
        std::make_tuple(2, CalloutHandle::NEXT_STEP_CONTINUE),
        std::make_tuple(6, CalloutHandle::NEXT_STEP_DROP),
    }, true);
}

// Check that a limit of zero applied to client classes effectively drops all v4 packets.
TEST_F(RateLimitV4, zeroLimitPerTemplateClientClass) {
    test(R"( { "client-classes": [ { "name": "foo",
                                     "template-test": "",
                                     "user-context": { "limits": { "rate-limit": "0 packets per year" } } } ],
               "subnet4": [ { "id": 1,
                              "user-context": { "limits": { "rate-limit": "2 packets per year" } } } ] } )", {
        std::make_tuple(4, CalloutHandle::NEXT_STEP_DROP),
    }, true);
}

TEST_F(RateLimitV4, zeroLimitPerTemplateClientClassMultiThreading) {
    MultiThreadingTest mt;
    test(R"( { "client-classes": [ { "name": "foo",
                                     "template-test": "",
                                     "user-context": { "limits": { "rate-limit": "0 packets per year" } } } ],
               "subnet4": [ { "id": 1,
                              "user-context": { "limits": { "rate-limit": "2 packets per year" } } } ] } )", {
        std::make_tuple(4, CalloutHandle::NEXT_STEP_DROP),
    }, true);
}

// Check that a limit of zero applied to client classes effectively drops all v6 packets.
TEST_F(RateLimitV6, zeroLimitPerTemplateClientClass) {
    test(R"( { "client-classes": [ { "name": "foo",
                                     "template-test": "",
                                     "user-context": { "limits": { "rate-limit": "0 packets per year" } } } ],
               "subnet6": [ { "id": 1,
                              "user-context": { "limits": { "rate-limit": "2 packets per year" } } } ] } )", {
        std::make_tuple(4, CalloutHandle::NEXT_STEP_DROP),
    }, true);
}

TEST_F(RateLimitV6, zeroLimitPerTemplateClientClassMultiThreading) {
    test(R"( { "client-classes": [ { "name": "foo",
                                     "template-test": "",
                                     "user-context": { "limits": { "rate-limit": "0 packets per year" } } } ],
               "subnet6": [ { "id": 1,
                              "user-context": { "limits": { "rate-limit": "2 packets per year" } } } ] } )", {
        std::make_tuple(4, CalloutHandle::NEXT_STEP_DROP),
    }, true);
}

// Check that a limit of zero applied to subnet IDs effectively drops all v4 packets.
TEST_F(RateLimitV4, zeroLimitPerSubnetWithTemplateClientClass) {
    test(R"( { "client-classes": [ { "name": "foo",
                                     "template-test": "",
                                     "user-context": { "limits": { "rate-limit": "2 packets per year" } } } ],
               "subnet4": [ { "id": 1,
                              "user-context": { "limits": { "rate-limit": "0 packets per year" } } } ] } )", {
        std::make_tuple(4, CalloutHandle::NEXT_STEP_DROP),
    }, true);
}

TEST_F(RateLimitV4, zeroLimitPerSubnetWithTemplateClientClassMultiThreading) {
    MultiThreadingTest mt;
    test(R"( { "client-classes": [ { "name": "foo",
                                     "template-test": "",
                                     "user-context": { "limits": { "rate-limit": "2 packets per year" } } } ],
               "subnet4": [ { "id": 1,
                              "user-context": { "limits": { "rate-limit": "0 packets per year" } } } ] } )", {
        std::make_tuple(4, CalloutHandle::NEXT_STEP_DROP),
    }, true);
}

// Check that a limit of zero applied to subnet IDs effectively drops all v6 packets.
TEST_F(RateLimitV6, zeroLimitPerSubnetWithTemplateClientClass) {
    test(R"( { "client-classes": [ { "name": "foo",
                                     "template-test": "",
                                     "user-context": { "limits": { "rate-limit": "2 packets per year" } } } ],
               "subnet6": [ { "id": 1,
                              "user-context": { "limits": { "rate-limit": "0 packets per year" } } } ] } )", {
        std::make_tuple(4, CalloutHandle::NEXT_STEP_DROP),
    }, true);
}

TEST_F(RateLimitV6, zeroLimitPerSubnetWithTemplateClientClassMultiThreading) {
    MultiThreadingTest mt;
    test(R"( { "client-classes": [ { "name": "foo",
                                     "template-test": "",
                                     "user-context": { "limits": { "rate-limit": "2 packets per year" } } } ],
               "subnet6": [ { "id": 1,
                              "user-context": { "limits": { "rate-limit": "0 packets per year" } } } ] } )", {
        std::make_tuple(4, CalloutHandle::NEXT_STEP_DROP),
    }, true);
}

// Check that a drop caused by a limit applied to a subsequently assigned client class, here
// "bar", does not affect the internal packet counts for client classes that were assigned
// before it, here "foo". The v4 version.
TEST_F(RateLimitV4, noSideEffectOfPacketsDroppedByTemplateClientClass) {
    // Make a callout manager.
    boost::shared_ptr<CalloutManager> manager(boost::make_shared<CalloutManager>());

    // Configure.
    parseConfig(R"( { "client-classes": [ { "name": "foo",
                                            "template-test": "",
                                            "user-context": { "limits": { "rate-limit": "2 packets per year" } } },
                                          { "name": "bar",
                                            "template-test": "",
                                            "user-context": { "limits": { "rate-limit": "1 packets per year" } } } ] } )");

    // Should be accepted.
    sendPacketAndExpectStatus(manager, {"foo", "bar"}, CalloutHandle::NEXT_STEP_CONTINUE, true);

    // Should be dropped because of the "bar" limit.
    sendPacketAndExpectStatus(manager, {"foo", "bar"}, CalloutHandle::NEXT_STEP_DROP, true);

    // Should be accepted.
    sendPacketAndExpectStatus(manager, {"foo"}, CalloutHandle::NEXT_STEP_CONTINUE, true);

    // Should be dropped because of the "foo" limit.
    sendPacketAndExpectStatus(manager, {"foo"}, CalloutHandle::NEXT_STEP_DROP, true);
}

TEST_F(RateLimitV4, noSideEffectOfPacketsDroppedByTemplateClientClassMultiThreading) {
    MultiThreadingTest mt;

    // Make a callout manager.
    boost::shared_ptr<CalloutManager> manager(boost::make_shared<CalloutManager>());

    // Configure.
    parseConfig(R"( { "client-classes": [ { "name": "foo",
                                            "template-test": "",
                                            "user-context": { "limits": { "rate-limit": "2 packets per year" } } },
                                          { "name": "bar",
                                            "template-test": "",
                                            "user-context": { "limits": { "rate-limit": "1 packets per year" } } } ] } )");

    // Should be accepted.
    sendPacketAndExpectStatus(manager, {"foo", "bar"}, CalloutHandle::NEXT_STEP_CONTINUE, true);

    // Should be dropped because of the "bar" limit.
    sendPacketAndExpectStatus(manager, {"foo", "bar"}, CalloutHandle::NEXT_STEP_DROP, true);

    // Should be accepted.
    sendPacketAndExpectStatus(manager, {"foo"}, CalloutHandle::NEXT_STEP_CONTINUE, true);

    // Should be dropped because of the "foo" limit.
    sendPacketAndExpectStatus(manager, {"foo"}, CalloutHandle::NEXT_STEP_DROP, true);
}

// Check that a drop caused by a limit applied to a subsequently assigned client class, here
// "bar", does not affect the internal packet counts for client classes that were assigned
// before it, here "foo". The v6 version.
TEST_F(RateLimitV6, noSideEffectOfPacketsDroppedByTemplateClientClass) {
    // Make a callout manager.
    boost::shared_ptr<CalloutManager> manager(boost::make_shared<CalloutManager>());

    // Configure.
    parseConfig(R"( { "client-classes": [ { "name": "foo",
                                            "template-test": "",
                                            "user-context": { "limits": { "rate-limit": "2 packets per year" } } },
                                          { "name": "bar",
                                            "template-test": "",
                                            "user-context": { "limits": { "rate-limit": "1 packets per year" } } } ] } )");

    // Should be accepted.
    sendPacketAndExpectStatus(manager, {"foo", "bar"}, CalloutHandle::NEXT_STEP_CONTINUE, true);

    // Should be dropped because of the "bar" limit.
    sendPacketAndExpectStatus(manager, {"foo", "bar"}, CalloutHandle::NEXT_STEP_DROP, true);

    // Should be accepted.
    sendPacketAndExpectStatus(manager, {"foo"}, CalloutHandle::NEXT_STEP_CONTINUE, true);

    // Should be dropped because of the "foo" limit.
    sendPacketAndExpectStatus(manager, {"foo"}, CalloutHandle::NEXT_STEP_DROP, true);
}

TEST_F(RateLimitV6, noSideEffectOfPacketsDroppedByTemplateClientClassMultiThreading) {
    MultiThreadingTest mt;

    // Make a callout manager.
    boost::shared_ptr<CalloutManager> manager(boost::make_shared<CalloutManager>());

    // Configure.
    parseConfig(R"( { "client-classes": [ { "name": "foo",
                                            "template-test": "",
                                            "user-context": { "limits": { "rate-limit": "2 packets per year" } } },
                                          { "name": "bar",
                                            "template-test": "",
                                            "user-context": { "limits": { "rate-limit": "1 packets per year" } } } ] } )");

    // Should be accepted.
    sendPacketAndExpectStatus(manager, {"foo", "bar"}, CalloutHandle::NEXT_STEP_CONTINUE, true);

    // Should be dropped because of the "bar" limit.
    sendPacketAndExpectStatus(manager, {"foo", "bar"}, CalloutHandle::NEXT_STEP_DROP, true);

    // Should be accepted.
    sendPacketAndExpectStatus(manager, {"foo"}, CalloutHandle::NEXT_STEP_CONTINUE, true);

    // Should be dropped because of the "foo" limit.
    sendPacketAndExpectStatus(manager, {"foo"}, CalloutHandle::NEXT_STEP_DROP, true);
}

// Check that v4 packets are correctly counted when the limit expires. Test is time-sensitive.
TEST_F(RateLimitV4, limitExpiresWithTemplateClientClass) {
    // Make a callout manager.
    boost::shared_ptr<CalloutManager> manager(boost::make_shared<CalloutManager>());

    // Configure.
    parseConfig(R"( { "client-classes": [ { "name": "foo",
                                            "template-test": "",
                                            "user-context": { "limits": { "rate-limit": "2 packets per second" } } } ] } )");

    sendPacketAndExpectStatus(manager, {"bar", "foo"}, CalloutHandle::NEXT_STEP_CONTINUE, true);
    sendPacketAndExpectStatus(manager, {"foo", "bar"}, CalloutHandle::NEXT_STEP_CONTINUE, true);
    sendPacketAndExpectStatus(manager, {"bar", "foo"}, CalloutHandle::NEXT_STEP_DROP, true);
    sendPacketAndExpectStatus(manager, {"foo", "bar"}, CalloutHandle::NEXT_STEP_DROP, true);

    std::this_thread::sleep_for(std::chrono::seconds(1));

    sendPacketAndExpectStatus(manager, {"bar", "foo"}, CalloutHandle::NEXT_STEP_CONTINUE, true);
    sendPacketAndExpectStatus(manager, {"foo", "bar"}, CalloutHandle::NEXT_STEP_CONTINUE, true);
    sendPacketAndExpectStatus(manager, {"bar", "foo"}, CalloutHandle::NEXT_STEP_DROP, true);
    sendPacketAndExpectStatus(manager, {"foo", "bar"}, CalloutHandle::NEXT_STEP_DROP, true);
}

TEST_F(RateLimitV4, limitExpiresWithTemplateClientClassMultiThreading) {
    MultiThreadingTest mt;

    // Make a callout manager.
    boost::shared_ptr<CalloutManager> manager(boost::make_shared<CalloutManager>());

    // Configure.
    parseConfig(R"( { "client-classes": [ { "name": "foo",
                                            "template-test": "",
                                            "user-context": { "limits": { "rate-limit": "2 packets per second" } } } ] } )");

    sendPacketAndExpectStatus(manager, {"bar", "foo"}, CalloutHandle::NEXT_STEP_CONTINUE, true);
    sendPacketAndExpectStatus(manager, {"foo", "bar"}, CalloutHandle::NEXT_STEP_CONTINUE, true);
    sendPacketAndExpectStatus(manager, {"bar", "foo"}, CalloutHandle::NEXT_STEP_DROP, true);
    sendPacketAndExpectStatus(manager, {"foo", "bar"}, CalloutHandle::NEXT_STEP_DROP, true);

    std::this_thread::sleep_for(std::chrono::seconds(1));

    sendPacketAndExpectStatus(manager, {"bar", "foo"}, CalloutHandle::NEXT_STEP_CONTINUE, true);
    sendPacketAndExpectStatus(manager, {"foo", "bar"}, CalloutHandle::NEXT_STEP_CONTINUE, true);
    sendPacketAndExpectStatus(manager, {"bar", "foo"}, CalloutHandle::NEXT_STEP_DROP, true);
    sendPacketAndExpectStatus(manager, {"foo", "bar"}, CalloutHandle::NEXT_STEP_DROP, true);
}

// Check that v6 packets are correctly counted when the limit expires. Test is time-sensitive.
TEST_F(RateLimitV6, limitExpiresWithTemplateClientClass) {
    // Make a callout manager.
    boost::shared_ptr<CalloutManager> manager(boost::make_shared<CalloutManager>());

    // Configure.
    parseConfig(R"( { "client-classes": [ { "name": "foo",
                                            "template-test": "",
                                            "user-context": { "limits": { "rate-limit": "2 packets per second" } } } ] } )");

    sendPacketAndExpectStatus(manager, {"bar", "foo"}, CalloutHandle::NEXT_STEP_CONTINUE, true);
    sendPacketAndExpectStatus(manager, {"foo", "bar"}, CalloutHandle::NEXT_STEP_CONTINUE, true);
    sendPacketAndExpectStatus(manager, {"bar", "foo"}, CalloutHandle::NEXT_STEP_DROP, true);
    sendPacketAndExpectStatus(manager, {"foo", "bar"}, CalloutHandle::NEXT_STEP_DROP, true);

    std::this_thread::sleep_for(std::chrono::seconds(1));

    sendPacketAndExpectStatus(manager, {"bar", "foo"}, CalloutHandle::NEXT_STEP_CONTINUE, true);
    sendPacketAndExpectStatus(manager, {"foo", "bar"}, CalloutHandle::NEXT_STEP_CONTINUE, true);
    sendPacketAndExpectStatus(manager, {"bar", "foo"}, CalloutHandle::NEXT_STEP_DROP, true);
    sendPacketAndExpectStatus(manager, {"foo", "bar"}, CalloutHandle::NEXT_STEP_DROP, true);
}

TEST_F(RateLimitV6, limitExpiresWithTemplateClientClassMultiThreading) {
    MultiThreadingTest mt;

    // Make a callout manager.
    boost::shared_ptr<CalloutManager> manager(boost::make_shared<CalloutManager>());

    // Configure.
    parseConfig(R"( { "client-classes": [ { "name": "foo",
                                            "template-test": "",
                                            "user-context": { "limits": { "rate-limit": "2 packets per second" } } } ] } )");

    sendPacketAndExpectStatus(manager, {"bar", "foo"}, CalloutHandle::NEXT_STEP_CONTINUE, true);
    sendPacketAndExpectStatus(manager, {"foo", "bar"}, CalloutHandle::NEXT_STEP_CONTINUE, true);
    sendPacketAndExpectStatus(manager, {"bar", "foo"}, CalloutHandle::NEXT_STEP_DROP, true);
    sendPacketAndExpectStatus(manager, {"foo", "bar"}, CalloutHandle::NEXT_STEP_DROP, true);

    std::this_thread::sleep_for(std::chrono::seconds(1));

    sendPacketAndExpectStatus(manager, {"bar", "foo"}, CalloutHandle::NEXT_STEP_CONTINUE, true);
    sendPacketAndExpectStatus(manager, {"foo", "bar"}, CalloutHandle::NEXT_STEP_CONTINUE, true);
    sendPacketAndExpectStatus(manager, {"bar", "foo"}, CalloutHandle::NEXT_STEP_DROP, true);
    sendPacketAndExpectStatus(manager, {"foo", "bar"}, CalloutHandle::NEXT_STEP_DROP, true);
}

}  // namespace
