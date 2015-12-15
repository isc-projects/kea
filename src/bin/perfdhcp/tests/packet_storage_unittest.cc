// Copyright (C) 2013, 2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include "../packet_storage.h"
#include <dhcp/dhcp6.h>
#include <dhcp/pkt6.h>

#include <gtest/gtest.h>

namespace {

using namespace isc;
using namespace isc::dhcp;
using namespace perfdhcp;

/// @todo Implement the tests which use Pkt4 objects once the support for
/// DHCPv4 renewals / releases is added.

/// The number of packets in the test storage.
const unsigned int STORAGE_SIZE = 20;

/// Test fixture class for PacketStorage container testing.
class PacketStorageTest : public ::testing::Test {
public:
    /// \brief Constructor, initializes the storage for each test.
    PacketStorageTest() {
        for (uint32_t i = 0; i < STORAGE_SIZE; ++i) {
            storage_.append(createPacket6(DHCPV6_REPLY, i));
        }
    }

    /// \brief Creates an instance of the Pkt6.
    ///
    /// \param packet_type A type of the packet.
    /// \param transid Transaction id.
    /// \return An instance of the Pkt6.
    Pkt6Ptr createPacket6(const uint16_t packet_type,
                          const uint32_t transid) {
        return (Pkt6Ptr(new Pkt6(packet_type, transid)));
    }

    /// Packet storage under test.
    PacketStorage<Pkt6> storage_;

};

// This test verifies that the packets in the storage can be accessed
// sequentially and when a packet is returned, it is removed from the
// storage. It also verifies the correctness of the behaviour of the
// empty() and size() functions.
TEST_F(PacketStorageTest, getNext) {
    ASSERT_EQ(STORAGE_SIZE, storage_.size());
    for (int i = 0; i < STORAGE_SIZE; ++i) {
        Pkt6Ptr packet = storage_.getNext();
        ASSERT_TRUE(packet) << "NULL packet returned by storage_.getNext() for"
                            << " iteration number " << i;
        EXPECT_EQ(i, packet->getTransid());
        EXPECT_EQ(STORAGE_SIZE - i - 1, storage_.size());
    }
    EXPECT_TRUE(storage_.empty());
    // When storage is empty, the attempt to get the next packet should
    // result in returning NULL pointer.
    EXPECT_FALSE(storage_.getNext());
    // Let's try it again to see if the previous call to getNext didn't
    // put the storage into the state in which the subsequent calls to
    // getNext would result in incorrect behaviour.
    EXPECT_FALSE(storage_.getNext());

    // Let's add a new packet to the empty storage to check that storage
    // "recovers" from being empty, i.e. that the internal indicator
    // which points to current packet reinitializes correctly.
    storage_.append(createPacket6(DHCPV6_REPLY, 100));
    ASSERT_EQ(1, storage_.size());
    Pkt6Ptr packet = storage_.getNext();
    EXPECT_EQ(100, packet->getTransid());
    EXPECT_FALSE(storage_.getNext());
}

// This test verifies that the packets in the storage can be accessed
// randomly and when a packet is returned, it is removed from the
// storage. It also verifies the correctness of the behaviour of the
// empty() and size() functions.
TEST_F(PacketStorageTest, getRandom) {
    ASSERT_EQ(STORAGE_SIZE, storage_.size());
    int cnt_equals = 0;
    for (int i = 0; i < STORAGE_SIZE; ++i) {
        Pkt6Ptr packet = storage_.getRandom();
        ASSERT_TRUE(packet) << "NULL packet returned by storage_.getRandom()"
            " for iteration number " << i;
        EXPECT_EQ(STORAGE_SIZE - i - 1, storage_.size());
        cnt_equals += (i == packet->getTransid() ? 1 : 0);
    }
    // If the number of times id is equal to i, is the same as the number
    // of elements then they were NOT accessed randomly.
    // The odds of 20 elements being randomly  accessed sequential order
    // is nil isn't it?
    EXPECT_NE(cnt_equals, STORAGE_SIZE);

    EXPECT_TRUE(storage_.empty());
    // When storage is empty, the attempt to get the random packet should
    // result in returning NULL pointer.
    EXPECT_FALSE(storage_.getRandom());
    // Let's try it again to see if the previous call to getRandom didn't
    // put the storage into the state in which the subsequent calls to
    // getRandom would result in incorrect behaviour.
    EXPECT_FALSE(storage_.getRandom());

    // Let's add a new packet to the empty storage to check that storage
    // "recovers" from being empty, i.e. that the internal indicator
    // which points to the current packet reinitializes correctly.
    storage_.append(createPacket6(DHCPV6_REPLY, 100));
    ASSERT_EQ(1, storage_.size());
    Pkt6Ptr packet = storage_.getRandom();
    ASSERT_TRUE(packet);
    EXPECT_EQ(100, packet->getTransid());
    EXPECT_FALSE(storage_.getRandom());
}

// This test verifies that the packets in the storage can be accessed
// either randomly or sequentially in the same time. It verifies that
// each returned packet is removed from the storage.
TEST_F(PacketStorageTest, getNextAndRandom) {
    ASSERT_EQ(STORAGE_SIZE, storage_.size());
    for (int i = 0; i < STORAGE_SIZE / 2; ++i) {
        Pkt6Ptr packet_random = storage_.getRandom();
        ASSERT_TRUE(packet_random) << "NULL packet returned by"
            " storage_.getRandom() for iteration number " << i;
        EXPECT_EQ(STORAGE_SIZE - 2 *i - 1, storage_.size());
        Pkt6Ptr packet_seq = storage_.getNext();
        ASSERT_TRUE(packet_seq) << "NULL packet returned by"
            " storage_.getNext()  for iteration number " << i;
        EXPECT_EQ(STORAGE_SIZE - 2 * i - 2, storage_.size());
    }
    EXPECT_TRUE(storage_.empty());
    EXPECT_FALSE(storage_.getRandom());
    EXPECT_FALSE(storage_.getNext());

    // Append two packets to the storage to check if it can "recover"
    // from being empty and that new elements can be accessed.
    storage_.append(createPacket6(DHCPV6_REPLY, 100));
    storage_.append(createPacket6(DHCPV6_REPLY, 101));
    ASSERT_EQ(2, storage_.size());
    // The newly added elements haven't been accessed yet. So, if we
    // call getNext the first one should be returned.
    Pkt6Ptr packet_next = storage_.getNext();
    ASSERT_TRUE(packet_next);
    // The first packet has transaction id equal to 100.
    EXPECT_EQ(100, packet_next->getTransid());
    // There should be just one packet left in the storage.
    ASSERT_EQ(1, storage_.size());
    // The call to getRandom should return the sole packet from the
    // storage.
    Pkt6Ptr packet_random = storage_.getRandom();
    ASSERT_TRUE(packet_random);
    EXPECT_EQ(101, packet_random->getTransid());
    // Any further calls to getRandom and getNext should return NULL.
    EXPECT_FALSE(storage_.getRandom());
    EXPECT_FALSE(storage_.getNext());
}

// This test verifies that all packets are removed from the storage when
// clear() function is invoked.
TEST_F(PacketStorageTest, clearAll) {
    ASSERT_EQ(STORAGE_SIZE, storage_.size());
    ASSERT_NO_THROW(storage_.clear());
    EXPECT_TRUE(storage_.empty());
}

// This test verifies that a set of packets can be removed from the
// storage when a number of packets to be removed is specified. If
// number of packets to be removed exceeds the storage size, all
// packets should be removed.
TEST_F(PacketStorageTest, clear) {
    // Initially storage should have 20 elements.
    ASSERT_EQ(STORAGE_SIZE, storage_.size());
    // Remove 10 of them.
    ASSERT_NO_THROW(storage_.clear(10));
    // We should have 10 remaining.
    ASSERT_EQ(10, storage_.size());

    // Check that the retrieval still works after partial clear.
    EXPECT_TRUE(storage_.getNext());
    EXPECT_TRUE(storage_.getRandom());
    // We should have 10 - 2 = 8 packets in the storage after retrieval.
    ASSERT_EQ(8, storage_.size());

    // Try to remove more elements that actually is. It
    // should result in removal of all elements.
    ASSERT_NO_THROW(storage_.clear(15));
    EXPECT_TRUE(storage_.empty());
}


} // anonymous namespace
