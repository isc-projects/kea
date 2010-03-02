// Copyright (C) 2009  Internet Systems Consortium, Inc. ("ISC")
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

// $Id$

#include <dns/buffer.h>

#include <gtest/gtest.h>

namespace {

using isc::dns::InputBuffer;
using isc::dns::OutputBuffer;

class BufferTest : public ::testing::Test {
protected:
    BufferTest() : ibuffer(testdata, sizeof(testdata)), obuffer(0),
                   expected_size(0)
    {
        data16 = (2 << 8) | 3;
        data32 = (4 << 24) | (5 << 16) | (6 << 8) | 7;
        memset(vdata, 0, sizeof(testdata));
    }

    InputBuffer ibuffer;
    OutputBuffer obuffer;
    static const uint8_t testdata[5];
    uint8_t vdata[sizeof(testdata)];
    size_t expected_size;
    uint16_t data16;
    uint32_t data32;
};

const uint8_t BufferTest::testdata[5] = {1, 2, 3, 4, 5};

TEST_F(BufferTest, inputBufferRead)
{
    EXPECT_EQ(5, ibuffer.getLength());
    EXPECT_EQ(1, ibuffer.readUint8());
    EXPECT_EQ(1, ibuffer.getPosition());
    data16 = ibuffer.readUint16();
    EXPECT_EQ((2 << 8) | 3, data16);
    EXPECT_EQ(3, ibuffer.getPosition());
    ibuffer.setPosition(1);
    EXPECT_EQ(1, ibuffer.getPosition());
    data32 = ibuffer.readUint32();
    EXPECT_EQ((2 << 24) | (3 << 16) | (4 << 8) | 5, data32);
    ibuffer.setPosition(0);
    memset(vdata, 0, sizeof(vdata));
    ibuffer.readData(vdata, sizeof(vdata));
    EXPECT_EQ(0, memcmp(vdata, testdata, sizeof(testdata)));
}

TEST_F(BufferTest, inputBufferException)
{
    EXPECT_THROW(ibuffer.setPosition(6), isc::dns::InvalidBufferPosition);

    ibuffer.setPosition(sizeof(testdata));
    EXPECT_THROW(ibuffer.readUint8(), isc::dns::InvalidBufferPosition);

    ibuffer.setPosition(sizeof(testdata) - 1);
    EXPECT_THROW(ibuffer.readUint16(), isc::dns::InvalidBufferPosition);

    ibuffer.setPosition(sizeof(testdata) - 3);
    EXPECT_THROW(ibuffer.readUint32(), isc::dns::InvalidBufferPosition);

    ibuffer.setPosition(sizeof(testdata) - 4);
    EXPECT_THROW(ibuffer.readData(vdata, sizeof(vdata)),
                 isc::dns::InvalidBufferPosition);
}

TEST_F(BufferTest, outputBufferExtend)
{
    EXPECT_EQ(0, obuffer.getCapacity());
    EXPECT_EQ(0, obuffer.getLength());
    obuffer.writeUint8(10);
    EXPECT_LT(0, obuffer.getCapacity());
    EXPECT_EQ(1, obuffer.getLength());
}

TEST_F(BufferTest, outputBufferWrite)
{
    const uint8_t* cp;

    obuffer.writeUint8(1);
    expected_size += sizeof(uint8_t);
    EXPECT_EQ(expected_size, obuffer.getLength());
    cp = static_cast<const uint8_t*>(obuffer.getData());
    EXPECT_EQ(1, *cp);

    obuffer.writeUint16(data16);
    expected_size += sizeof(data16);
    cp = static_cast<const uint8_t*>(obuffer.getData());
    EXPECT_EQ(expected_size, obuffer.getLength());
    EXPECT_EQ(2, *(cp + 1));
    EXPECT_EQ(3, *(cp + 2));

    obuffer.writeUint32(data32);
    expected_size += sizeof(data32);
    cp = static_cast<const uint8_t*>(obuffer.getData());
    EXPECT_EQ(expected_size, obuffer.getLength());
    EXPECT_EQ(4, *(cp + 3));
    EXPECT_EQ(5, *(cp + 4));
    EXPECT_EQ(6, *(cp + 5));
    EXPECT_EQ(7, *(cp + 6));

    obuffer.writeData(testdata, sizeof(testdata));
    expected_size += sizeof(testdata);
    EXPECT_EQ(expected_size, obuffer.getLength());
    cp = static_cast<const uint8_t*>(obuffer.getData());
    EXPECT_EQ(0, memcmp(cp + 7, testdata, sizeof(testdata)));
}

TEST_F(BufferTest, outputBufferWriteat)
{
    obuffer.writeUint32(data32);
    expected_size += sizeof(data32);

    // overwrite 2nd and 3rd bytes
    obuffer.writeUint16At(data16, 1);
    EXPECT_EQ(expected_size, obuffer.getLength()); // length shouldn't change
    const uint8_t* cp = static_cast<const uint8_t*>(obuffer.getData());
    EXPECT_EQ(2, *(cp + 1));
    EXPECT_EQ(3, *(cp + 2));

    // overwrite 3rd and 4th bytes
    obuffer.writeUint16At(data16, 2);
    EXPECT_EQ(expected_size, obuffer.getLength());
    cp = static_cast<const uint8_t*>(obuffer.getData());
    EXPECT_EQ(2, *(cp + 2));
    EXPECT_EQ(3, *(cp + 3));

    EXPECT_THROW(obuffer.writeUint16At(data16, 3),
                 isc::dns::InvalidBufferPosition);
    EXPECT_THROW(obuffer.writeUint16At(data16, 4),
                 isc::dns::InvalidBufferPosition);
    EXPECT_THROW(obuffer.writeUint16At(data16, 5),
                 isc::dns::InvalidBufferPosition);
}

TEST_F(BufferTest, outputBufferSkip)
{
    obuffer.skip(4);
    EXPECT_EQ(4, obuffer.getLength());

    obuffer.skip(2);
    EXPECT_EQ(6, obuffer.getLength());
}

TEST_F(BufferTest, outputBufferReadat)
{
    obuffer.writeData(testdata, sizeof(testdata));
    for (int i = 0; i < sizeof(testdata); i ++) {
        EXPECT_EQ(testdata[i], obuffer[i]);
    }
    EXPECT_THROW(obuffer[sizeof(testdata)], isc::dns::InvalidBufferPosition);
}

TEST_F(BufferTest, outputBufferClear)
{
    obuffer.writeData(testdata, sizeof(testdata));
    obuffer.clear();
    EXPECT_EQ(0, obuffer.getLength());
}
}
