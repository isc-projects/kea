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

#include <cstddef>
#include <cstdint>

#include <arpa/inet.h>
#include <gtest/gtest.h>

using namespace isc;
using namespace isc::util;

namespace {

/// @brief Check whether uint16_t can be read from a buffer properly.
TEST(asioutil, readUint16) {
    // Reference buffer
    uint8_t data[2] = {0, 0};
    InputBuffer buffer(data, sizeof(data));

    // Avoid possible compiler warnings by only setting uint8_t variables to
    // uint8_t values.
    uint8_t i8 = 0;
    uint8_t j8 = 0;
    for (int i = 0; i < (2 << 8); ++i, ++i8) {
        for (int j = 0; j < (2 << 8); ++j, ++j8) {
            data[0] = i8;
            data[1] = j8;
            buffer.setPosition(0);
            EXPECT_EQ(buffer.readUint16(), readUint16(data, sizeof(data)));
        }
    }
}

/// @brief Check whether reading an uint16_t results in an exception.
TEST(asioutil, readUint16OutOfRange) {
    uint8_t data = 0;
    EXPECT_THROW_MSG(readUint16(&data, sizeof(data)), OutOfRange,
                     "Expected buffer to be long enough to read a 2-byte integer, but got 1 byte "
                     "instead");
}

/// @brief Check whether uint16_t can be written to a buffer properly.
TEST(asioutil, writeUint16) {
    // Reference buffer
    OutputBuffer buffer(2);
    uint8_t test[2];

    // Avoid possible compiler warnings by only setting uint16_t variables to
    // uint16_t values.
    uint16_t i16 = 0;
    for (uint32_t i = 0; i < (2 << 16); ++i, ++i16) {
        // Write the reference data
        buffer.clear();
        buffer.writeUint16(i16);

        // ... and the test data
        writeUint16(i16, test, sizeof(test));

        // ... and compare
        const uint8_t* ref = static_cast<const uint8_t*>(buffer.getData());
        EXPECT_EQ(ref[0], test[0]);
        EXPECT_EQ(ref[1], test[1]);
    }
}

/// @brief Check whether writing an uint16_t results in an exception.
TEST(asioutil, writeUint16OutOfRange) {
    uint16_t i16 = 42;
    uint8_t data;
    EXPECT_THROW_MSG(writeUint16(i16, &data, sizeof(data)), OutOfRange,
                     "Expected buffer to be long enough to write a 2-byte integer, but got 1 byte "
                     "instead");
}

/// @brief Test data shared amount readUint32 and writeUint32 tests.
const static uint32_t test32[] = {0, 1, 2000, 0x80000000, 0xffffffff};

/// @brief Check whether uint32_t can be read from a buffer properly.
TEST(asioutil, readUint32) {
    uint8_t data[8] = {0, 0, 0, 0, 0, 0, 0, 0};

    // Make sure that we can read data, regardless of
    // the memory alignment. That is why we need to repeat
    // it 4 times.
    for (int offset = 0; offset < 4; offset++) {
        for (size_t i = 0; i < sizeof(test32) / sizeof(uint32_t); i++) {
            uint32_t tmp = htonl(test32[i]);
            memcpy(&data[offset], &tmp, sizeof(uint32_t));

            EXPECT_EQ(test32[i], readUint32(&data[offset], sizeof(uint32_t)));
        }
    }
}

/// @brief Check whether reading an uint32_t results in an exception.
TEST(asioutil, readUint32OutOfRange) {
    uint8_t data[3] = {0, 0, 0};
    EXPECT_THROW_MSG(readUint32(data, sizeof(data)), OutOfRange,
                     "Expected buffer to be long enough to read a 4-byte integer, but got 3 bytes "
                     "instead");
}

/// @brief Check whether uint32_t can be written to a buffer properly.
TEST(asioutil, writeUint32) {
    uint8_t data[8];

    // make sure that we can write data, regardless of
    // the memory alignment. That's why we need to repeat
    // it 4 times.
    for (int offset = 0; offset < 4; offset++) {
        for (size_t i = 0; i < sizeof(test32) / sizeof(uint32_t); i++) {
            uint8_t* ptr = writeUint32(test32[i], &data[offset], sizeof(uint32_t));

            EXPECT_EQ(&data[offset] + sizeof(uint32_t), ptr);

            uint32_t tmp = htonl(test32[i]);

            EXPECT_EQ(0, memcmp(&tmp, &data[offset], sizeof(uint32_t)));
        }
    }
}

/// @brief Check whether writing an uint32_t results in an exception.
TEST(asioutil, writeUint32OutOfRange) {
    uint32_t i32 = 28;
    uint8_t data[3];
    EXPECT_THROW_MSG(writeUint32(i32, data, sizeof(data)), OutOfRange,
                     "Expected buffer to be long enough to write a 4-byte integer, but got 3 bytes "
                     "instead");
}

/// @brief Check whether uint64_t can be read from a buffer properly.
TEST(asioutil, readUint64) {
    uint8_t buf[8];
    for (size_t offset = 0; offset < sizeof(buf); offset++) {
        buf[offset] = offset + 1;
    }

    // Now check if a real value could be read.
    const uint64_t exp_val = 0x0102030405060708ul;
    uint64_t val;

    EXPECT_NO_THROW_LOG(val = readUint64(buf, 8));
    EXPECT_EQ(val, exp_val);

    // Now check if there are no buffer overflows.
    memset(buf, 0xff, 8);

    EXPECT_NO_THROW_LOG(val = readUint64(buf, 8));
    EXPECT_EQ(0xfffffffffffffffful, val);
}

/// @brief Check whether reading an uint64_t results in an exception.
TEST(asioutil, readUint64OutOfRange) {
    uint8_t buf[8];

    // Let's do some simple sanity checks first.
    EXPECT_THROW_MSG(readUint64(NULL, 0), OutOfRange,
                     "Expected buffer to be long enough to read a 8-byte integer, but got 0 bytes "
                     "instead");
    EXPECT_THROW_MSG(readUint64(buf, 7), OutOfRange,
                     "Expected buffer to be long enough to read a 8-byte integer, but got 7 bytes "
                     "instead");
}

/// @brief Check whether uint64 can be written to a buffer properly.
TEST(asioutil, writeUint64) {
    uint8_t data[8];

    // make sure that we can write data, regardless of
    // the memory alignment. That's why we need to repeat
    // it 4 times.
    for (int offset = 0; offset < 4; offset++) {
        for (size_t i = 0; i < sizeof(test32) / sizeof(uint32_t); i++) {
            uint8_t* ptr = writeUint32(test32[i], &data[offset], sizeof(uint32_t));

            EXPECT_EQ(&data[offset] + sizeof(uint32_t), ptr);

            uint32_t tmp = htonl(test32[i]);

            EXPECT_EQ(0, memcmp(&tmp, &data[offset], sizeof(uint32_t)));
        }
    }
}

/// @brief Check whether writing an uint64_t results in an exception.
TEST(asioutil, writeUint64OutOfRange) {
    uint32_t i32 = 28;
    uint8_t data[3];
    EXPECT_THROW_MSG(writeUint32(i32, data, sizeof(data)), OutOfRange,
                     "Expected buffer to be long enough to write a 4-byte integer, but got 3 bytes "
                     "instead");
}

}  // namespace
