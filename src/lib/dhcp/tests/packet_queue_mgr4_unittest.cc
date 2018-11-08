// Copyright (C) 2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <dhcp/packet_queue_mgr4.h>
#include <packet_queue_testutils.h>

#include <boost/shared_ptr.hpp>
#include <gtest/gtest.h>

using namespace std;
using namespace isc;
using namespace isc::dhcp;
using namespace isc::dhcp::test;

/// @brief Convenience function for construction a dhcp-queue-control element map
///
/// @param queue_type logical name of the queue implemenation type
/// @param capacity maximum queue capacity
data::ElementPtr
isc::dhcp::test::makeQueueConfig(const std::string& queue_type, size_t capacity) {
    data::ElementPtr config = data::Element::createMap();
    config->set("queue-type", data::Element::create(queue_type));
    config->set("capacity", data::Element::create(static_cast<long int>(capacity)));
    return (config);
}

namespace {

/// @brief Test fixture for exercising the DHCPv4 Packet Queue Manager (PQM)
class PacketQueueMgr4Test : public ::testing::Test {
public:
    /// @brief Constructor
    ///
    /// Note that it instantiates the PQM singleton.
    PacketQueueMgr4Test(){
        PacketQueueMgr4::create();
    }

    /// @brief Destructor
    ///
    /// It destroys the PQM singleton.
    virtual ~PacketQueueMgr4Test(){
        PacketQueueMgr4::destroy();
    }

    /// @brief Registers a queue type factory
    ///
    /// @param queue_type logical name of the queue implementation
    ///
    /// @return true if the registration succeeded, false otherwise
    bool addCustomQueueType(const std::string& queue_type) {
        bool did_it =
            mgr().registerPacketQueueFactory(queue_type,
                                            [](data::ConstElementPtr parameters)
                                            -> PacketQueue4Ptr {
                std::string queue_type ;
                try {
                    queue_type = data::SimpleParser::getString(parameters, "queue-type");
                } catch (std::exception& ex) {
                    isc_throw(InvalidQueueParameter,
                              "queue-type missing or invalid: " << ex.what());
                }

                size_t capacity;
                try {
                    capacity = data::SimpleParser::getInteger(parameters, "capacity");
                } catch (const std::exception& ex) {
                    isc_throw(InvalidQueueParameter,
                              "'capacity' missing or invalid: " << ex.what());
                }

                return (PacketQueue4Ptr(new PacketQueueRing4(queue_type, capacity)));
            });

        return did_it;
    }

    /// @brief Fetches a pointer to the PQM singleton
    PacketQueueMgr4& mgr() {
        return (PacketQueueMgr4::instance());
    };

    /// @brief Tests the current packet queue info against expected content
    ///
    /// @param exp_json JSON text describing the expected packet queue info
    /// contents
    void checkMyInfo(const std::string& exp_json) {
        checkInfo((mgr().getPacketQueue()), exp_json);
    }

};

// Verifies that DHCPv4 PQM provides a default queue factory
// and packet queue.
TEST_F(PacketQueueMgr4Test, defaultQueue) {

    // Verify that we have a default queue and its info is correct.
    checkMyInfo("{ \"capacity\": 500, \"queue-type\": \"kea-ring4\", \"size\": 0 }");

    data::ConstElementPtr config = makeQueueConfig("kea-ring4", 2000);

    // Verify that we can replace the default queue with different capacity queue
    ASSERT_NO_THROW(mgr().createPacketQueue(config));
    checkMyInfo("{ \"capacity\": 2000, \"queue-type\": \"kea-ring4\", \"size\": 0 }");

    // We should be able to recreate the manager.
    ASSERT_NO_THROW(PacketQueueMgr4::create());

    // And be back to having the default queue.
    checkMyInfo("{ \"capacity\": 500, \"queue-type\": \"kea-ring4\", \"size\": 0 }");
}

// Verifies that PQM registry and creation of custome queue implementations.
TEST_F(PacketQueueMgr4Test, customQueueType) {

    // Verify that we cannot create a queue for a non-existant type
    data::ConstElementPtr config = makeQueueConfig("custom-queue", 2000);
    ASSERT_THROW(mgr().createPacketQueue(config), InvalidQueueType);

    // Register our adjustable-type factory
    ASSERT_TRUE(addCustomQueueType("custom-queue"));

    // We still have our default queue.
    checkMyInfo("{ \"capacity\": 500, \"queue-type\": \"kea-ring4\", \"size\": 0 }");

    // Verify that we can replace the default queue with a "custom-queue" queue
    ASSERT_NO_THROW(mgr().createPacketQueue(config));
    checkMyInfo("{ \"capacity\": 2000, \"queue-type\": \"custom-queue\", \"size\": 0 }");

    // Now unregister the factory.
    ASSERT_NO_THROW(mgr().unregisterPacketQueueFactory("custom-queue"));

    // Verify we did not lose the queue.
    checkMyInfo("{ \"capacity\": 2000, \"queue-type\": \"custom-queue\", \"size\": 0 }");

    // Try and recreate the custom queue, type should be invalid.
    ASSERT_THROW(mgr().createPacketQueue(config), InvalidQueueType);

    // Verify we can create a default type queue with non-default capacity.
    config = makeQueueConfig("kea-ring4", 2000);
    ASSERT_NO_THROW(mgr().createPacketQueue(config));
    checkMyInfo("{ \"capacity\": 2000, \"queue-type\": \"kea-ring4\", \"size\": 0 }");
}

} // end of anonymous namespace
