// Copyright (C) 2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <dhcp/packet_queue_mgr6.h>

#include <boost/shared_ptr.hpp>
#include <gtest/gtest.h>

using namespace std;
using namespace isc;
using namespace isc::dhcp;

namespace {

class PacketQueueMgr6Test : public ::testing::Test {
public:
    PacketQueueMgr6Test(){
        PacketQueueMgr6::create();
    }

    ~PacketQueueMgr6Test(){
        PacketQueueMgr6::destroy();
    }

    /// @brief Registers a queue type factory 
    bool addCustomQueueType(const std::string& queue_type) {
        bool did_it =
            mgr().registerPacketQueueFactory(queue_type, 
                                            [](const QueueControl& control)
                                            -> PacketQueue6Ptr {
                return (PacketQueue6Ptr(new PacketQueueRing6(control.getQueueType(),
                                                             control.getCapacity())));
            });

        return did_it; 
    }

    PacketQueueMgr6& mgr() {
        return (PacketQueueMgr6::instance());
    };

    void checkInfo(const std::string& exp_json) {
        // Fetch the queue info and verify it has all the expected values.
        ASSERT_TRUE(mgr().getPacketQueue()) << " no packet queue!";  
        data::ElementPtr info;
        ASSERT_NO_THROW(info = mgr().getPacketQueue()->getInfo());
        ASSERT_TRUE(info);
        data::ElementPtr exp_elems;
        ASSERT_NO_THROW(exp_elems = data::Element::fromJSON(exp_json))
                        << " exp_elems is invalid JSON : " << exp_json 
                        << " test is broken";
        EXPECT_TRUE(exp_elems->equals(*info));
    }

};

TEST_F(PacketQueueMgr6Test, defaultQueue) {

    // Verify that we have a default queue and its info is correct.
    checkInfo("{ \"capacity\": 500, \"queue-type\": \"kea-ring6\", \"size\": 0 }");

    QueueControl control;
    control.setQueueType("kea-ring6");
    control.setCapacity(2000);

    // Verify that we can replace the default queue with different capacity queue
    ASSERT_NO_THROW(mgr().createPacketQueue(control));
    checkInfo("{ \"capacity\": 2000, \"queue-type\": \"kea-ring6\", \"size\": 0 }");

    // We should be able to recreate the manager.
    ASSERT_NO_THROW(PacketQueueMgr6::create());  

    // And be back to having the default queue.
    checkInfo("{ \"capacity\": 500, \"queue-type\": \"kea-ring6\", \"size\": 0 }");
}

TEST_F(PacketQueueMgr6Test, customQueueType) {
    QueueControl control;
    control.setQueueType("custom-queue");
    control.setCapacity(2000);

    // Verify that we cannot create a queue for a non-existant type
    ASSERT_THROW(mgr().createPacketQueue(control), InvalidQueueType);

    // Register our adjustable-type factory
    ASSERT_TRUE(addCustomQueueType("custom-queue"));

    // We still have our default queue.
    checkInfo("{ \"capacity\": 500, \"queue-type\": \"kea-ring6\", \"size\": 0 }");

    // Verify that we can replace the default queue with a "custom-queue" queue
    ASSERT_NO_THROW(mgr().createPacketQueue(control));
    checkInfo("{ \"capacity\": 2000, \"queue-type\": \"custom-queue\", \"size\": 0 }");

    // Now unregister the factory.
    ASSERT_NO_THROW(mgr().unregisterPacketQueueFactory("custom-queue"));

    // Verify we did not lose the queue.
    checkInfo("{ \"capacity\": 2000, \"queue-type\": \"custom-queue\", \"size\": 0 }");

    // Try and recreate the custom queue, type should be invalid.
    ASSERT_THROW(mgr().createPacketQueue(control), InvalidQueueType);

    // Verify we can create a default type queue.
    control.setQueueType("kea-ring6");
    ASSERT_NO_THROW(mgr().createPacketQueue(control));
    checkInfo("{ \"capacity\": 2000, \"queue-type\": \"kea-ring6\", \"size\": 0 }");
}

} // end of anonymous namespace
