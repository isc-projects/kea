// Copyright (C) 2011-2024 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

/// \brief Test of asiolink utilities
///
/// Tests the functionality of the asiolink utilities code by comparing them
/// with the equivalent methods in isc::dns::[Input/Output]Buffer.

#include <config.h>

#include <testutils/gtest_utils.h>
#include <util/buffer.h>
#include <util/io.h>

#include <bitset>
#include <cstddef>
#include <cstdint>
#include <string>

#include <arpa/inet.h>
#include <gtest/gtest.h>

using namespace isc;
using namespace isc::util;
using namespace std;

namespace {

struct ReadWriteUintTest : ::testing::Test {
    template <typename uint_t>
    string showDiff(uint_t const left, uint8_t* const right) {
        bitset<8 * sizeof(uint_t)> const bitset_left(left);
        bitset<8 * sizeof(uint_t)> const bitset_right(*(reinterpret_cast<uint_t*>(right)));
        string const bitstring_left(separateBytes(bitset_left.to_string()));
        string const bitstring_right(separateBytes(bitset_right.to_string()));
        string const diff(::testing::internal::edit_distance::CreateUnifiedDiff({bitstring_left},
                                                                                {bitstring_right}));
        return (diff);
    }

private:
    string separateBytes(string const& input) {
        size_t const position(8);
        stringstream ss;
        for (size_t i = 0; i < input.size(); i = i + position) {
            if (i) {
                ss << " ";
            }
            ss << input.substr(i, position);
        }
        return (ss.str());
    }
};

/// @brief Check whether uint16_t can be read from a buffer properly.
TEST_F(ReadWriteUintTest, readUint16) {
    uint16_t const test16[] = {0, 1, 2000, 0x8000, 0xffff};
    uint8_t data[] = {0, 0, 0, 0};

    // Make sure that we can read data, regardless of the memory alignment.
    // That is why we need to repeat it 2 times.
    for (size_t offset = 0; offset < sizeof(uint16_t); ++offset) {
        for (size_t i = 0; i < sizeof(test16) / sizeof(uint16_t); ++i) {
            SCOPED_TRACE("offset " + to_string(offset) + ", iteration " + to_string(i));

            uint16_t tmp = htons(test16[i]);
            memcpy(&data[offset], &tmp, sizeof(uint16_t));

            EXPECT_EQ(test16[i], readUint16(&data[offset], sizeof(uint16_t)));
        }
    }
}

/// @brief Check whether reading an uint16_t results in an exception.
TEST_F(ReadWriteUintTest, readUint16OutOfRange) {
    uint8_t data[] = {0};
    EXPECT_THROW_MSG(readUint16(data, 1), OutOfRange,
                     "Expected buffer to be long enough to read a 2-byte integer, but got 1 byte "
                     "instead");
}

/// @brief Check whether uint16_t can be written to a buffer properly.
TEST_F(ReadWriteUintTest, writeUint16) {
    uint16_t const test16[] = {0, 1, 2000, 0x8000, 0xffff};
    uint8_t data[4];

    // Make sure that we can write data, regardless of the memory alignment.
    // That's why we need to repeat 2 times.
    for (size_t offset = 0; offset < sizeof(uint16_t); ++offset) {
        for (size_t i = 0; i < sizeof(test16) / sizeof(uint16_t); ++i) {
            SCOPED_TRACE("offset " + to_string(offset) + ", iteration " + to_string(i));

            uint8_t* ptr = writeUint16(test16[i], &data[offset], sizeof(uint16_t));

            EXPECT_EQ(&data[offset] + sizeof(uint16_t), ptr);

            uint16_t tmp = htons(test16[i]);

            EXPECT_EQ(0, memcmp(&tmp, &data[offset], sizeof(uint16_t)))
                << showDiff(tmp, &data[offset]);
        }
    }
}

/// @brief Check whether writing an uint16_t results in an exception.
TEST_F(ReadWriteUintTest, writeUint16OutOfRange) {
    uint16_t i16 = 42;
    uint8_t data[1];
    EXPECT_THROW_MSG(writeUint16(i16, data, sizeof(data)), OutOfRange,
                     "Expected buffer to be long enough to write a 2-byte integer, but got 1 byte "
                     "instead");
}

/// @brief Check whether uint32_t can be read from a buffer properly.
TEST_F(ReadWriteUintTest, readUint32) {
    uint32_t const test32[] = {0, 1, 2000, 0x80000000, 0xffffffff};
    uint8_t data[] = {0, 0, 0, 0, 0, 0, 0, 0};

    // Make sure that we can read data, regardless of the memory alignment.
    // That is why we need to repeat it 4 times.
    for (size_t offset = 0; offset < sizeof(uint32_t); ++offset) {
        for (size_t i = 0; i < sizeof(test32) / sizeof(uint32_t); ++i) {
            SCOPED_TRACE("offset " + to_string(offset) + ", iteration " + to_string(i));

            uint32_t tmp = htonl(test32[i]);
            memcpy(&data[offset], &tmp, sizeof(uint32_t));

            EXPECT_EQ(test32[i], readUint32(&data[offset], sizeof(uint32_t)));
        }
    }
}

/// @brief Check whether reading an uint32_t results in an exception.
TEST_F(ReadWriteUintTest, readUint32OutOfRange) {
    uint8_t data[] = {0, 0, 0};
    EXPECT_THROW_MSG(readUint32(data, 3), OutOfRange,
                     "Expected buffer to be long enough to read a 4-byte integer, but got 3 bytes "
                     "instead");
}

/// @brief Check whether uint32_t can be written to a buffer properly.
TEST_F(ReadWriteUintTest, writeUint32) {
    uint32_t const test32[] = {0, 1, 2000, 0x80000000, 0xffffffff};
    uint8_t data[8];

    // Make sure that we can write data, regardless of the memory alignment.
    // That's why we need to repeat 4 times.
    for (size_t offset = 0; offset < sizeof(uint32_t); ++offset) {
        for (size_t i = 0; i < sizeof(test32) / sizeof(uint32_t); ++i) {
            SCOPED_TRACE("offset " + to_string(offset) + ", iteration " + to_string(i));

            uint8_t* ptr = writeUint32(test32[i], &data[offset], sizeof(uint32_t));

            EXPECT_EQ(&data[offset] + sizeof(uint32_t), ptr);

            uint32_t tmp = htonl(test32[i]);

            EXPECT_EQ(0, memcmp(&tmp, &data[offset], sizeof(uint32_t)))
                << showDiff(tmp, &data[offset]);
        }
    }
}

/// @brief Check whether writing an uint32_t results in an exception.
TEST_F(ReadWriteUintTest, writeUint32OutOfRange) {
    uint32_t i32 = 28;
    uint8_t data[3];
    EXPECT_THROW_MSG(writeUint32(i32, data, sizeof(data)), OutOfRange,
                     "Expected buffer to be long enough to write a 4-byte integer, but got 3 bytes "
                     "instead");
}

/// @brief Check whether uint64_t can be read from a buffer properly.
TEST_F(ReadWriteUintTest, readUint64) {
    uint64_t const test64[] = {0, 1, 2000, 0x80000000, 0xffffffff, 0xfffffffffffffff};
    uint8_t data[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    // Make sure that we can read data, regardless of the memory alignment.
    // That is why we need to repeat it 8 times.
    for (size_t offset = 0; offset < sizeof(uint64_t); ++offset) {
        for (size_t i = 0; i < sizeof(test64) / sizeof(uint64_t); ++i) {
            SCOPED_TRACE("offset " + to_string(offset) + ", iteration " + to_string(i));

            uint64_t tmp = (uint64_t(htonl(test64[i])) << 32) | htonl(test64[i] >> 32);
            memcpy(&data[offset], &tmp, sizeof(uint64_t));

            EXPECT_EQ(test64[i], readUint64(&data[offset], sizeof(uint64_t)));
        }
    }
}

/// @brief Check whether reading an uint64_t results in an exception.
TEST_F(ReadWriteUintTest, readUint64OutOfRange) {
    uint8_t buf[] = {0, 0, 0, 0, 0, 0, 0};

    EXPECT_THROW_MSG(readUint64(buf, 7), OutOfRange,
                     "Expected buffer to be long enough to read a 8-byte integer, but got 7 bytes "
                     "instead");
}

/// @brief Check whether uint64 can be written to a buffer properly.
TEST_F(ReadWriteUintTest, writeUint64) {
    uint64_t const test64[] = {0, 1, 2000, 0x80000000, 0xffffffff, 0xfffffffffffffff};
    uint8_t data[16];

    // Make sure that we can write data, regardless of the memory alignment.
    // That's why we need to repeat 8 times.
    for (size_t offset = 0; offset < sizeof(uint64_t); ++offset) {
        for (size_t i = 0; i < sizeof(test64) / sizeof(uint64_t); ++i) {
            SCOPED_TRACE("offset " + to_string(offset) + ", iteration " + to_string(i));

            uint8_t* ptr = writeUint64(test64[i], &data[offset], sizeof(uint64_t));

            EXPECT_EQ(&data[offset] + sizeof(uint64_t), ptr);

            uint64_t tmp = (uint64_t(htonl(test64[i])) << 32) | htonl(test64[i] >> 32);

            EXPECT_EQ(0, memcmp(&tmp, &data[offset], sizeof(uint64_t)))
                << showDiff(tmp, &data[offset]);
        }
    }
}

/// @brief Check whether writing an uint64_t results in an exception.
TEST_F(ReadWriteUintTest, writeUint64OutOfRange) {
    uint64_t i64 = 28;
    uint8_t data[7];
    EXPECT_THROW_MSG(writeUint64(i64, data, sizeof(data)), OutOfRange,
                     "Expected buffer to be long enough to write a 8-byte integer, but got 7 bytes "
                     "instead");
}

}  // namespace
