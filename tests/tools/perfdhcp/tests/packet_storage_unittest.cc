// Copyright (C) 2013 Internet Systems Consortium, Inc. ("ISC")
//
// Permission to use, copy, modify, and/or distribute this software for any
// purpose with or without fee is hereby granted, provided that the above
// copyright notice and this permission notice appear in all copies.
//
// THE SOFTWARE IS PROVIDED "AS IS" AND ISC DISCLAIMS ALL WARRANTIES WITH
// REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
// AND FITNESS.  IN NO EVENT SHALL ISC BE LIABLE FOR ANY SPECIAL, DIRECT,
// INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
// LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE
// OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
// PERFORMANCE OF THIS SOFTWARE.

#include "../packet_storage.h"
#include <dhcp/dhcp6.h>
#include <dhcp/pkt6.h>

#include <gtest/gtest.h>

namespace {

using namespace isc;
using namespace isc::dhcp;
using namespace perfdhcp;

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
    EXPECT_FALSE(storage_.getNext());
    EXPECT_FALSE(storage_.getNext());

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
    for (int i = 0; i < STORAGE_SIZE; ++i) {
        Pkt6Ptr packet = storage_.getRandom();
        ASSERT_TRUE(packet) << "NULL packet returned by storage_.getRandom()"
            " for iteration number " << i;
        EXPECT_EQ(STORAGE_SIZE - i - 1, storage_.size());
    }
    EXPECT_TRUE(storage_.empty());
    EXPECT_FALSE(storage_.getRandom());
    EXPECT_FALSE(storage_.getRandom());

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
        EXPECT_EQ(STORAGE_SIZE - 2 * i - 1, storage_.size());
        uint32_t random_packet_transid = packet_random->getTransid();
        Pkt6Ptr packet_seq = storage_.getNext();
        ASSERT_TRUE(packet_seq) << "NULL packet returned by"
            " storage_.getNext()  for iteration number " << i;
        EXPECT_EQ(STORAGE_SIZE - 2 * i - 2, storage_.size());
    }
    EXPECT_TRUE(storage_.empty());
    EXPECT_FALSE(storage_.getRandom());
    EXPECT_FALSE(storage_.getNext());

    storage_.append(createPacket6(DHCPV6_REPLY, 100));
    storage_.append(createPacket6(DHCPV6_REPLY, 101));
    ASSERT_EQ(2, storage_.size());
    Pkt6Ptr packet_random = storage_.getRandom();
    ASSERT_TRUE(packet_random);
    EXPECT_EQ(100, packet_random->getTransid());
    Pkt6Ptr packet_next = storage_.getNext();
    ASSERT_TRUE(packet_next);
    EXPECT_EQ(101, packet_next->getTransid());
    EXPECT_FALSE(storage_.getRandom());
    EXPECT_FALSE(storage_.getNext());
}

// This test verifies that all packets are removed from the storage when
// clear() function is invoked.
TEST_F(PacketStorageTest, clear) {
    ASSERT_EQ(STORAGE_SIZE, storage_.size());
    ASSERT_NO_THROW(storage_.clear());
    EXPECT_TRUE(storage_.empty());
}


} // anonymous namespace
