// Copyright (C) 2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <dhcp/dhcp6.h>
#include <dhcp/packet_queue.h>
#include <dhcp/tests/packet_queue_testutils.h>

#include <boost/shared_ptr.hpp>
#include <gtest/gtest.h>

using namespace std;
using namespace isc;
using namespace isc::dhcp;
using namespace isc::dhcp::test;

namespace {

/// @brief DHCPv6 queue with implements drop and eat logic
///
/// This class derives from the default DHCPv6 ring queue
/// and provies implementations for shouldDropPacket() and
/// eatPackets().  This permits a full exercising of the
/// PacketQueue interface as well as the basic v6 ring queue
/// mechanics.
class TestQueue6 : public PacketQueueRing6 {
public:
    /// @brief Constructor
    ///
    /// @param queue_size maximum number of packets the queue can hold
    TestQueue6(size_t queue_size)
        : PacketQueueRing6("kea-ring6", queue_size), drop_enabled_(false), eat_count_(0) {
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
    virtual bool shouldDropPacket(Pkt6Ptr packet,
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

// Verifies use of the generic PacketQueue interface to
// construct a queue implementation.
TEST(TestQueue6, interfaceBasics) {
    // Verify we can create a queue
    PacketQueue6Ptr q6(new TestQueue6(100));
    ASSERT_TRUE(q6);

    // It should be empty.
    EXPECT_TRUE(q6->empty());

    // Type should match.
    EXPECT_EQ("kea-ring6", q6->getQueueType());

    // Fetch the queue info and verify it has all the expected values.
    checkInfo(q6, "{ \"capacity\": 100, \"queue-type\": \"kea-ring6\", \"size\": 0 }");
}

// Verifies the basic mechanics of the adding and
// removing packets to and from the ring buffer.
TEST(TestQueue6, ringTest) {
    PacketQueue6Ptr q6(new TestQueue6(3));

    // Fetch the queue info and verify it has all the expected values.
    checkInfo(q6, "{ \"capacity\": 3, \"queue-type\": \"kea-ring6\", \"size\": 0 }");

    // Enqueue five packets.  The first two should be pushed off.
    SocketInfo sock1(isc::asiolink::IOAddress("127.0.0.1"), 777, 10);
    for (int i = 1; i < 6; ++i) {
        Pkt6Ptr pkt(new Pkt6(DHCPV6_SOLICIT, 1000+i));
        ASSERT_NO_THROW(q6->enqueuePacket(pkt, sock1));
        checkIntStat(q6, "size", (i > 3 ? 3 : i));
    }

    // Fetch the queue info and verify it has all the expected values.
    checkInfo(q6, "{ \"capacity\": 3, \"queue-type\": \"kea-ring6\", \"size\": 3 }");

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
        checkIntStat(q6, "size", i);
    }

    // Let's flush the buffer and then verify it is empty.
    q6->clear();
    EXPECT_TRUE(q6->empty());
    checkIntStat(q6, "size", 0);
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
    checkIntStat(q6, "size", 1);

    // Enqueue a packet onto the front.
    pkt.reset(new Pkt6(DHCPV6_SOLICIT, 1003));
    ASSERT_NO_THROW(q6->enqueuePacket(pkt, sock1, QueueEnd::FRONT));
    checkIntStat(q6, "size", 2);

    // Enqueue a packet onto the back.
    pkt.reset(new Pkt6(DHCPV6_SOLICIT, 1001));
    ASSERT_NO_THROW(q6->enqueuePacket(pkt, sock1, QueueEnd::BACK));
    checkIntStat(q6, "size", 3);

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
// This accesses it's queue instance as a TestQueue6, rather than
// a PacketQueue6Ptr, to provide access to TestQueue6 specifics.
TEST(TestQueue6, shouldDropPacketTest) {
    TestQueue6 q6(100);
    EXPECT_TRUE(q6.empty());
    ASSERT_FALSE(q6.drop_enabled_);
    ASSERT_EQ(0, q6.eat_count_);

    SocketInfo sockEven(isc::asiolink::IOAddress("127.0.0.1"), 888, 10);
    SocketInfo sockOdd(isc::asiolink::IOAddress("127.0.0.1"), 777, 11);

    // Drop is not enabled.
    // We should be able to enqueue a packet with even numbered values.
    Pkt6Ptr pkt(new Pkt6(DHCPV6_SOLICIT, 1002));
    ASSERT_NO_THROW(q6.enqueuePacket(pkt, sockEven));
    EXPECT_EQ(1, q6.getSize());

    // We should be able to enqueue a packet with odd numbered values.
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
// This accesses it's queue instance as a TestQueue6, rather than
// a PacketQueue6Ptr, to provide access to TestQueue6 specifics.
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
