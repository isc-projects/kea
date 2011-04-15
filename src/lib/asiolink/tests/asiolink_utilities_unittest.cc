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

/// \brief Test of asiolink utilties
///
/// Tests the fuctionality of the asiolink utilities code by comparing them
/// with the equivalent methods in isc::dns::[Input/Output]Buffer.

#include <cstddef>

#include <gtest/gtest.h>

#include <dns/buffer.h>
#include <asiolink/asiolink_utilities.h>

using namespace isc::asiolink;
using namespace isc::dns;

TEST(asioutil, readUint16) {

    // Reference buffer
    uint8_t data[2];
    isc::dns::InputBuffer buffer(data, sizeof(data));

    // Avoid possible compiler warnings by only setting uint8_t variables to
    // uint8_t values.
    uint8_t i8 = 0;
    uint8_t j8 = 0;
    for (int i = 0; i < (2 << 8); ++i, ++i8) {
        for (int j = 0; j < (2 << 8); ++j, ++j8) {
            data[0] = i8;
            data[1] = j8;
            buffer.setPosition(0);
            EXPECT_EQ(buffer.readUint16(), readUint16(data));
        }
    }
}


TEST(asioutil, writeUint16) {

    // Reference buffer
    isc::dns::OutputBuffer buffer(2);
    uint8_t test[2];

    // Avoid possible compiler warnings by only setting uint16_t variables to
    // uint16_t values.
    uint16_t i16 = 0;
    for (uint32_t i = 0; i < (2 << 16); ++i, ++i16) {

        // Write the reference data
        buffer.clear();
        buffer.writeUint16(i16);

        // ... and the test data
        writeUint16(i16, test);

        // ... and compare
        const uint8_t* ref = static_cast<const uint8_t*>(buffer.getData());
        EXPECT_EQ(ref[0], test[0]);
        EXPECT_EQ(ref[1], test[1]);
    }
}
