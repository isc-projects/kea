// Copyright (C) 2018-2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <dhcp/packet_queue_ring.h>
#include <dhcp/packet_queue_mgr6.h>
#include <dhcp/tests/packet_queue_testutils.h>

#include <boost/shared_ptr.hpp>
#include <gtest/gtest.h>

using namespace std;
using namespace isc;
using namespace isc::dhcp;
using namespace isc::dhcp::test;

namespace {

/// @brief Test fixture for exercising the DHCPv6 Packet Queue Manager (PQM)
class PacketQueueMgr6Test : public ::testing::Test {
public:
    /// @brief Constructor
    ///
    /// Note that it instantiates the PQM singleton.
    PacketQueueMgr6Test()
        : default_queue_type_(PacketQueueMgr6::DEFAULT_QUEUE_TYPE6) {
        packet_queue_mgr6_.reset(new PacketQueueMgr6());

    }

    /// @brief Destructor
    ///
    /// It destroys the PQM singleton.
    virtual ~PacketQueueMgr6Test(){}

    /// @brief Registers a queue type factory
    ///
    /// @param queue_type logical name of the queue implementation
    ///
    /// @return true if the registration succeeded, false otherwise
    bool addCustomQueueType(const std::string& queue_type) {
        bool did_it =
            mgr().registerPacketQueueFactory(queue_type,
                                            [](data::ConstElementPtr parameters)
                                            -> PacketQueue6Ptr {
                std::string queue_type ;
                try {
                    queue_type = data::SimpleParser::getString(parameters, "queue-type");
                } catch (const std::exception& ex) {
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

                return (PacketQueue6Ptr(new PacketQueueRing6(queue_type, capacity)));
            });

        return did_it;
    }

    /// @brief Fetches a pointer to the PQM singleton
    PacketQueueMgr6& mgr() {
        return (*packet_queue_mgr6_);
    };

    /// @brief Tests the current packet queue info against expected content
    ///
    /// @param exp_json JSON text describing the expected packet queue info
    /// contents
    void checkMyInfo(const std::string& exp_json) {
        checkInfo((mgr().getPacketQueue()), exp_json);
    }

    /// @brief default queue type used for a given test
    std::string default_queue_type_;

    /// @brief Packet Queue manager instance
    PacketQueueMgr6Ptr packet_queue_mgr6_;
};

// Verifies that DHCPv6 PQM provides a default queue factory
TEST_F(PacketQueueMgr6Test, defaultQueue) {
    // Should not be a queue at start-up
    ASSERT_FALSE(mgr().getPacketQueue());

    // Verify that we can create a queue with default factory.
    data::ConstElementPtr config = makeQueueConfig(default_queue_type_, 2000);
    ASSERT_NO_THROW(mgr().createPacketQueue(config));
    CHECK_QUEUE_INFO (mgr().getPacketQueue(), "{ \"capacity\": 2000, \"queue-type\": \""
                      << default_queue_type_ << "\", \"size\": 0 }");
}

// Verifies that PQM registry and creation of custom queue implementations.
TEST_F(PacketQueueMgr6Test, customQueueType) {

    // Verify that we cannot create a queue for a non-existant type
    data::ConstElementPtr config = makeQueueConfig("custom-queue", 2000);
    ASSERT_THROW(mgr().createPacketQueue(config), InvalidQueueType);

    // Register our adjustable-type factory
    ASSERT_TRUE(addCustomQueueType("custom-queue"));

    // Verify that we can create a custom queue.
    ASSERT_NO_THROW(mgr().createPacketQueue(config));
    checkMyInfo("{ \"capacity\": 2000, \"queue-type\": \"custom-queue\", \"size\": 0 }");

    // Now unregister the factory.
    ASSERT_NO_THROW(mgr().unregisterPacketQueueFactory("custom-queue"));
    // Queue should be gone too.
    ASSERT_FALSE(mgr().getPacketQueue());

    // Try and recreate the custom queue, type should be invalid.
    ASSERT_THROW(mgr().createPacketQueue(config), InvalidQueueType);

    // Verify we can create a default type queue with non-default capacity.
    config = makeQueueConfig(default_queue_type_, 2000);
    ASSERT_NO_THROW(mgr().createPacketQueue(config));
    CHECK_QUEUE_INFO (mgr().getPacketQueue(), "{ \"capacity\": 2000, \"queue-type\": \""
                      << default_queue_type_ << "\", \"size\": 0 }");
}

} // end of anonymous namespace
