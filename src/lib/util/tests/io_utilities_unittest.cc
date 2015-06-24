// Copyright (C) 2011  Internet Systems Consortium, Inc. ("ISC")
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

/// \brief Test of asiolink utilities
///
/// Tests the functionality of the asiolink utilities code by comparing them
/// with the equivalent methods in isc::dns::[Input/Output]Buffer.

#include <cstddef>

#include <arpa/inet.h>
#include <gtest/gtest.h>

#include <util/buffer.h>
#include <util/io_utilities.h>

using namespace isc::util;

TEST(asioutil, readUint16) {

    // Reference buffer
    uint8_t data[2];
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

TEST(asioutil, readUint16OutOfRange) {
    uint8_t data;
    EXPECT_THROW(readUint16(&data, sizeof(data)), isc::OutOfRange);
}

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

TEST(asioutil, writeUint16OutOfRange) {
    uint16_t i16 = 42;
    uint8_t data;
    EXPECT_THROW(writeUint16(i16, &data, sizeof(data)), isc::OutOfRange);
}

// test data shared amount readUint32 and writeUint32 tests
const static uint32_t test32[] = {
    0,
    1,
    2000,
    0x80000000,
    0xffffffff
};

TEST(asioutil, readUint32) {
    uint8_t data[8];

    // make sure that we can read data, regardless of
    // the memory alignment. That' why we need to repeat
    // it 4 times.
    for (int offset=0; offset < 4; offset++) {
        for (int i=0; i < sizeof(test32)/sizeof(uint32_t); i++) {
            uint32_t tmp = htonl(test32[i]);
            memcpy(&data[offset], &tmp, sizeof(uint32_t));

            EXPECT_EQ(test32[i], readUint32(&data[offset], sizeof(uint32_t)));
        }
    }
}

TEST(asioutil, readUint32OutOfRange) {
    uint8_t data[3];
    EXPECT_THROW(readUint32(data, sizeof(data)), isc::OutOfRange);
}

TEST(asioutil, writeUint32) {
    uint8_t data[8];

    // make sure that we can write data, regardless of
    // the memory alignment. That's why we need to repeat
    // it 4 times.
    for (int offset=0; offset < 4; offset++) {
        for (int i=0; i < sizeof(test32)/sizeof(uint32_t); i++) {
            uint8_t* ptr = writeUint32(test32[i], &data[offset],
                                       sizeof(uint32_t));

            EXPECT_EQ(&data[offset]+sizeof(uint32_t), ptr);

            uint32_t tmp = htonl(test32[i]);

            EXPECT_EQ(0, memcmp(&tmp, &data[offset], sizeof(uint32_t)));
        }
    }
}

TEST(asioutil, writeUint32OutOfRange) {
    uint32_t i32 = 28;
    uint8_t data[3];
    EXPECT_THROW(writeUint32(i32, data, sizeof(data)), isc::OutOfRange);
}
