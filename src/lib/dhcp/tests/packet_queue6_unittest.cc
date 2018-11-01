// Copyright (C) 2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <asiolink/io_address.h>
#include <dhcp/dhcp6.h>
#include <dhcp/packet_queue.h>

#include <boost/shared_ptr.hpp>
#include <gtest/gtest.h>

#include <iostream>
#include <sstream>

using namespace std;
using namespace isc;
using namespace isc::dhcp;

namespace {

class TestQueue6 : public PacketQueueRing<Pkt6Ptr> {
public:

    /// @brief Constructor
    ///
    /// @param queue_size maximum number of packets the queue can hold
    TestQueue6(size_t queue_size) 
        : PacketQueueRing(queue_size), drop_enabled_(false), eat_count_(0) {
    };

    /// @brief virtual Destructor
    virtual ~TestQueue6(){};

    /// @brief Determines is a packet should be dropped.
    ///
    /// If drop is enabled and either the packet transaction
    /// id or the socket source port are even numbers, drop the packet
    ///
    /// @param packet the packet under consideration
    /// @param source the socket the packet came from
    ///
    /// @return True if the packet should be dropped.
    virtual bool dropPacket(Pkt6Ptr packet,
                            const SocketInfo& source) {
        if (drop_enabled_) {
            return ((packet->getTransid() % 2 == 0) || 
                    (source.port_ % 2 == 0)); 
        }

        return (false);
    }

    /// @brief Discards a number of packets from one end of the queue
    ///
    /// Dequeue and discard eat_count_ packets from the given end of
    /// the queue_.
    ///
    /// @param from end of the queue from which packets should discarded
    ///
    /// @return The number of packets discarded.
    virtual int eatPackets(const QueueEnd& from) {
        int eaten = 0;
        for ( ; eaten < eat_count_; ++eaten) {
            Pkt6Ptr pkt = popPacket(from);
            if (!pkt) {
                break;
            }
        }

        return (eaten);
    }

    bool drop_enabled_;
    int eat_count_;
};

// Verifies basic operation of the PacketQueue interface:
// 1. Construction
// 2. Manipulation of configurable parameters
TEST(TestQueue6, interfaceBasics) {
    // Use minimum allowed 
    size_t min = TestQueue6::MIN_RING_CAPACITY;

    PacketQueue6Ptr q6(new TestQueue6(min));
    ASSERT_TRUE(q6);
    EXPECT_TRUE(q6->empty());

    ConstQueueControlPtr orig_control = q6->getQueueControl();
    ASSERT_TRUE(orig_control);
    EXPECT_EQ(min, orig_control->getCapacity());
    EXPECT_EQ(min, q6->getCapacity());
    EXPECT_EQ(0, q6->getSize());

    // Verify we cannot violate minium.
    QueueControlPtr new_control(new QueueControl());
    new_control->setCapacity(min - 1);
    ASSERT_THROW(q6->setQueueControl(new_control), BadValue);

    // Verify original control values remain
    EXPECT_TRUE(*(q6->getQueueControl()) == *orig_control);

    // Verify we can update to a valid value.
    new_control->setCapacity(min + 10);
    ASSERT_NO_THROW(q6->setQueueControl(new_control));
    ConstQueueControlPtr control = q6->getQueueControl();
    ASSERT_TRUE(control);
    EXPECT_TRUE(*control == *new_control);
    EXPECT_EQ(min + 10, control->getCapacity());
    EXPECT_EQ(min + 10, q6->getCapacity());
}

// Verifies the basic mechanics of the adding and
// removing packets to and from the ring buffer.
TEST(TestQueue6, ringTest) {
    PacketQueue6Ptr q6(new TestQueue6(3));

    EXPECT_EQ(3, q6->getCapacity());
    // Enqueue five packets.  The first two should be pushed off.
    SocketInfo sock1(isc::asiolink::IOAddress("127.0.0.1"), 777, 10);
    for (int i = 1; i < 6; ++i) {
        Pkt6Ptr pkt(new Pkt6(DHCPV6_SOLICIT, 1000+i));
        ASSERT_NO_THROW(q6->enqueuePacket(pkt, sock1));

        int exp_size = (i > 3 ? 3 : i);
        EXPECT_EQ(exp_size, q6->getSize()); 
    }

    // We should have transids 1005,1004,1003  (back to front)

    // Peek front should be transid 1003.
    Pkt6Ptr pkt;
    ASSERT_NO_THROW(pkt = q6->peek(QueueEnd::FRONT));
    ASSERT_TRUE(pkt);
    EXPECT_EQ(1003, pkt->getTransid());

    // Peek back should be transid 1005.
    ASSERT_NO_THROW(pkt = q6->peek(QueueEnd::BACK));
    ASSERT_TRUE(pkt);
    EXPECT_EQ(1005, pkt->getTransid());

    // Pop front should return transid 1003.
    ASSERT_NO_THROW(pkt = q6->popPacket(QueueEnd::FRONT));
    ASSERT_TRUE(pkt);
    EXPECT_EQ(1003, pkt->getTransid());

    // Pop back should return transid 1005.
    ASSERT_NO_THROW(pkt = q6->popPacket(QueueEnd::BACK));
    ASSERT_TRUE(pkt);
    EXPECT_EQ(1005, pkt->getTransid());

    // Peek front should be transid 1004.
    ASSERT_NO_THROW(pkt = q6->peek(QueueEnd::FRONT));
    ASSERT_TRUE(pkt);
    EXPECT_EQ(1004, pkt->getTransid());

    // Peek back should be transid 1004.
    ASSERT_NO_THROW(pkt = q6->peek(QueueEnd::BACK));
    ASSERT_TRUE(pkt);
    EXPECT_EQ(1004, pkt->getTransid());

    // Pop front should return transid 1004.
    ASSERT_NO_THROW(pkt = q6->popPacket(QueueEnd::FRONT));
    ASSERT_TRUE(pkt);
    EXPECT_EQ(1004, pkt->getTransid());

    // Pop front should return an empty pointer.
    ASSERT_NO_THROW(pkt = q6->popPacket(QueueEnd::BACK));
    ASSERT_FALSE(pkt);

    // Enqueue three packets.
    for (int i = 1; i < 3; ++i) {
        Pkt6Ptr pkt(new Pkt6(DHCPV6_SOLICIT, 1000+i));
        ASSERT_NO_THROW(q6->enqueuePacket(pkt, sock1));
        EXPECT_EQ(i, q6->getSize()); 
    }

    // Let's flush the buffer and then verify it is empty.
    q6->clear();
    EXPECT_TRUE(q6->empty()); 
    EXPECT_EQ(0, q6->getSize()); 
}

// Verifies the higher level functions of queueing and
// dequeueing with drop and skip logic disabled.
TEST(TestQueue6, enqueueDequeueTest) {
    PacketQueue6Ptr q6(new TestQueue6(100));
    EXPECT_TRUE(q6->empty());

    SocketInfo sock1(isc::asiolink::IOAddress("127.0.0.1"), 777, 10);

    // Enqueue the first packet.
    Pkt6Ptr pkt(new Pkt6(DHCPV6_SOLICIT, 1002));
    ASSERT_NO_THROW(q6->enqueuePacket(pkt, sock1));
    EXPECT_EQ(1, q6->getSize());

    // Enqueue a packet onto the front.
    pkt.reset(new Pkt6(DHCPV6_SOLICIT, 1003));
    ASSERT_NO_THROW(q6->enqueuePacket(pkt, sock1, QueueEnd::FRONT));
    EXPECT_EQ(2, q6->getSize());

    // Enqueue a packet onto the back.
    pkt.reset(new Pkt6(DHCPV6_SOLICIT, 1001));
    ASSERT_NO_THROW(q6->enqueuePacket(pkt, sock1, QueueEnd::BACK));
    EXPECT_EQ(3, q6->getSize());

    // By default we dequeue from the front. We should get transid 1003.
    ASSERT_NO_THROW(pkt = q6->dequeuePacket());
    ASSERT_TRUE(pkt);
    EXPECT_EQ(1003, pkt->getTransid());

    // Dequeue from the back, we should get transid 1001.
    ASSERT_NO_THROW(pkt = q6->dequeuePacket(QueueEnd::BACK));
    ASSERT_TRUE(pkt);
    EXPECT_EQ(1001, pkt->getTransid());

    // Dequeue from the front, we should get transid 1002.
    ASSERT_NO_THROW(pkt = q6->dequeuePacket(QueueEnd::FRONT));
    ASSERT_TRUE(pkt);
    EXPECT_EQ(1002, pkt->getTransid());

    // Queue should be empty.
    ASSERT_NO_THROW(pkt = q6->dequeuePacket());
    ASSERT_FALSE(pkt);
}

// Verifies enqueuing operations when drop logic is enabled.
TEST(TestQueue6, dropPacketTest) {
    TestQueue6 q6(100);
    EXPECT_TRUE(q6.empty());
    ASSERT_FALSE(q6.drop_enabled_);
    ASSERT_EQ(0, q6.eat_count_);

    SocketInfo sockEven(isc::asiolink::IOAddress("127.0.0.1"), 888, 10);
    SocketInfo sockOdd(isc::asiolink::IOAddress("127.0.0.1"), 777, 11);

    // Drop is not enabled. 
    // We should be able to enqueu a packet with even numbered values.
    Pkt6Ptr pkt(new Pkt6(DHCPV6_SOLICIT, 1002));
    ASSERT_NO_THROW(q6.enqueuePacket(pkt, sockEven));
    EXPECT_EQ(1, q6.getSize());

    // We should be able to enqueu a packet with odd numbered values.
    pkt.reset(new Pkt6(DHCPV6_SOLICIT, 1003));
    ASSERT_NO_THROW(q6.enqueuePacket(pkt, sockOdd));
    EXPECT_EQ(2, q6.getSize());

    // Enable drop logic.
    q6.drop_enabled_ = true;

    // We should not be able to add one with an even-numbered transid.      
    pkt.reset(new Pkt6(DHCPV6_SOLICIT, 1004));
    ASSERT_NO_THROW(q6.enqueuePacket(pkt, sockOdd));
    EXPECT_EQ(2, q6.getSize());

    // We should not be able to add one with from even-numbered port.      
    pkt.reset(new Pkt6(DHCPV6_SOLICIT, 1005));
    ASSERT_NO_THROW(q6.enqueuePacket(pkt, sockEven));
    EXPECT_EQ(2, q6.getSize());

    // We should be able to add one with an odd-numbered values.
    pkt.reset(new Pkt6(DHCPV6_SOLICIT, 1007));
    ASSERT_NO_THROW(q6.enqueuePacket(pkt, sockOdd));
    EXPECT_EQ(3, q6.getSize());

    // Dequeue them and make sure they are as expected: 1002,1003, and 1007. 
    ASSERT_NO_THROW(pkt = q6.dequeuePacket());
    ASSERT_TRUE(pkt);
    EXPECT_EQ(1002, pkt->getTransid());

    ASSERT_NO_THROW(pkt = q6.dequeuePacket());
    ASSERT_TRUE(pkt);
    EXPECT_EQ(1003, pkt->getTransid());

    ASSERT_NO_THROW(pkt = q6.dequeuePacket());
    ASSERT_TRUE(pkt);
    EXPECT_EQ(1007, pkt->getTransid());

    // Queue should be empty.
    ASSERT_NO_THROW(pkt = q6.dequeuePacket());
    ASSERT_FALSE(pkt);
}

// Verifies dequeuing operations when eat packets is enabled.
TEST(TestQueue6, eatPacketsTest) {
    TestQueue6 q6(100);
    EXPECT_TRUE(q6.empty());
    ASSERT_FALSE(q6.drop_enabled_);
    ASSERT_EQ(0, q6.eat_count_);

    SocketInfo sock(isc::asiolink::IOAddress("127.0.0.1"), 888, 10);

    Pkt6Ptr pkt;
    // Let's add five packets.
    for (int i = 1; i < 6; ++i) {
        pkt.reset(new Pkt6(DHCPV6_SOLICIT, 1000 + i));
        ASSERT_NO_THROW(q6.enqueuePacket(pkt, sock));
        EXPECT_EQ(i, q6.getSize());
    }

    // Setting eat count to two and dequeuing (from the front, by default), 
    // should discard 1001 and 1002, resulting in a dequeue of 1003.
    q6.eat_count_ = 2;
    ASSERT_NO_THROW(pkt = q6.dequeuePacket());
    ASSERT_TRUE(pkt);
    EXPECT_EQ(1003, pkt->getTransid());
    EXPECT_EQ(2, q6.getSize());

    // Setting eat count to one and dequeing from the back, should discard
    // 1005 and dequeue 104.
    q6.eat_count_ = 1;
    ASSERT_NO_THROW(pkt = q6.dequeuePacket(QueueEnd::BACK));
    ASSERT_TRUE(pkt);
    EXPECT_EQ(1004, pkt->getTransid());
    EXPECT_EQ(0, q6.getSize());
}

} // end of anonymous namespace
