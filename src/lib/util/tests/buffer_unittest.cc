// Copyright (C) 2009-2024 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <exceptions/exceptions.h>
#include <util/buffer.h>

#ifdef EXPECT_DEATH
#include <util/unittests/resource.h>
#include <util/unittests/check_valgrind.h>
#endif /* EXPECT_DEATH */

#include <gtest/gtest.h>

using namespace isc;
using namespace isc::util;

namespace {

class BufferTest : public ::testing::Test {
protected:
    BufferTest() : ibuffer(testdata, sizeof(testdata)), obuffer(0),
                   expected_size(0) {
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
    std::vector<uint8_t> datav;
};

const uint8_t BufferTest::testdata[5] = {1, 2, 3, 4, 5};

TEST_F(BufferTest, inputBufferRead) {
    EXPECT_EQ(5, ibuffer.getLength());
    EXPECT_EQ(1, ibuffer.peekUint8());
    EXPECT_EQ(0, ibuffer.getPosition());
    EXPECT_EQ(1, ibuffer.readUint8());
    EXPECT_EQ(1, ibuffer.getPosition());
    data16 = ibuffer.peekUint16();
    EXPECT_EQ(1, ibuffer.getPosition());
    EXPECT_EQ(data16, ibuffer.readUint16());
    EXPECT_EQ((2 << 8) | 3, data16);
    EXPECT_EQ(3, ibuffer.getPosition());
    ibuffer.setPosition(1);
    EXPECT_EQ(1, ibuffer.getPosition());
    data32 = ibuffer.peekUint32();
    EXPECT_EQ(1, ibuffer.getPosition());
    EXPECT_EQ(data32, ibuffer.readUint32());
    EXPECT_EQ((2 << 24) | (3 << 16) | (4 << 8) | 5, data32);
    ibuffer.setPosition(0);
    memset(vdata, 0, sizeof(vdata));
    ibuffer.peekData(vdata, sizeof(vdata));
    EXPECT_EQ(0, memcmp(vdata, testdata, sizeof(testdata)));
    EXPECT_EQ(0, ibuffer.getPosition());
    memset(vdata, 0, sizeof(vdata));
    ibuffer.readData(vdata, sizeof(vdata));
    EXPECT_EQ(0, memcmp(vdata, testdata, sizeof(testdata)));
    EXPECT_EQ(sizeof(vdata), ibuffer.getPosition());
    ibuffer.setPosition(0);
    datav.clear();
    ibuffer.peekVector(datav, sizeof(vdata));
    ASSERT_EQ(sizeof(vdata), datav.size());
    EXPECT_EQ(0, memcmp(&vdata[0], testdata, sizeof(testdata)));
    EXPECT_EQ(0, ibuffer.getPosition());
    datav.clear();
    ibuffer.readVector(datav, sizeof(vdata));
    ASSERT_EQ(sizeof(vdata), datav.size());
    EXPECT_EQ(0, memcmp(&vdata[0], testdata, sizeof(testdata)));
    EXPECT_EQ(sizeof(vdata), ibuffer.getPosition());
}

TEST_F(BufferTest, inputBufferException) {
    EXPECT_THROW(ibuffer.setPosition(6), isc::OutOfRange);

    ibuffer.setPosition(sizeof(testdata));
    EXPECT_THROW(ibuffer.peekUint8(), isc::OutOfRange);
    EXPECT_THROW(ibuffer.readUint8(), isc::OutOfRange);

    ibuffer.setPosition(sizeof(testdata) - 1);
    EXPECT_THROW(ibuffer.peekUint16(), isc::OutOfRange);
    EXPECT_THROW(ibuffer.readUint16(), isc::OutOfRange);

    ibuffer.setPosition(sizeof(testdata) - 3);
    EXPECT_THROW(ibuffer.peekUint32(), isc::OutOfRange);
    EXPECT_THROW(ibuffer.readUint32(), isc::OutOfRange);

    ibuffer.setPosition(sizeof(testdata) - 4);
    EXPECT_THROW(ibuffer.peekData(vdata, sizeof(vdata)), isc::OutOfRange);
    EXPECT_THROW(ibuffer.readData(vdata, sizeof(vdata)), isc::OutOfRange);
    EXPECT_THROW(ibuffer.peekVector(datav, sizeof(vdata)), isc::OutOfRange);
    EXPECT_THROW(ibuffer.readVector(datav, sizeof(vdata)), isc::OutOfRange);
}

TEST_F(BufferTest, outputBufferExtend) {
    EXPECT_EQ(0, obuffer.getCapacity());
    EXPECT_EQ(0, obuffer.getLength());
    obuffer.writeUint8(10);
    EXPECT_LT(0, obuffer.getCapacity());
    EXPECT_EQ(1, obuffer.getLength());
}

TEST_F(BufferTest, outputBufferWrite) {
    obuffer.writeUint8(1);
    expected_size += sizeof(uint8_t);
    EXPECT_EQ(expected_size, obuffer.getLength());
    const uint8_t* cp = obuffer.getData();
    EXPECT_EQ(1, *cp);

    obuffer.writeUint16(data16);
    expected_size += sizeof(data16);
    cp = obuffer.getData();
    EXPECT_EQ(expected_size, obuffer.getLength());
    EXPECT_EQ(2, *(cp + 1));
    EXPECT_EQ(3, *(cp + 2));

    obuffer.writeUint32(data32);
    expected_size += sizeof(data32);
    cp = obuffer.getData();
    EXPECT_EQ(expected_size, obuffer.getLength());
    EXPECT_EQ(4, *(cp + 3));
    EXPECT_EQ(5, *(cp + 4));
    EXPECT_EQ(6, *(cp + 5));
    EXPECT_EQ(7, *(cp + 6));

    obuffer.writeData(testdata, sizeof(testdata));
    expected_size += sizeof(testdata);
    EXPECT_EQ(expected_size, obuffer.getLength());
    cp = obuffer.getData();
    EXPECT_EQ(0, memcmp(cp + 7, testdata, sizeof(testdata)));

    datav = obuffer.getVector();
    ASSERT_EQ(expected_size, datav.size());
    std::vector<uint8_t> expected = { 1, 2, 3, 4, 5, 6, 7 };
    expected.insert(expected.end(), testdata, testdata + sizeof(testdata));
    ASSERT_EQ(expected_size, expected.size());
    EXPECT_EQ(0, memcmp(&expected[0], &datav[0], expected_size));
}

TEST_F(BufferTest, outputBufferWriteAt) {
    obuffer.writeUint32(data32);
    expected_size += sizeof(data32);

    // overwrite 2nd byte
    obuffer.writeUint8At(4, 1);
    EXPECT_EQ(expected_size, obuffer.getLength()); // length shouldn't change
    const uint8_t* cp = obuffer.getData();
    EXPECT_EQ(4, *(cp + 1));

    // overwrite 2nd and 3rd bytes
    obuffer.writeUint16At(data16, 1);
    EXPECT_EQ(expected_size, obuffer.getLength()); // length shouldn't change
    cp = obuffer.getData();
    EXPECT_EQ(2, *(cp + 1));
    EXPECT_EQ(3, *(cp + 2));

    // overwrite 3rd and 4th bytes
    obuffer.writeUint16At(data16, 2);
    EXPECT_EQ(expected_size, obuffer.getLength());
    cp = obuffer.getData();
    EXPECT_EQ(2, *(cp + 2));
    EXPECT_EQ(3, *(cp + 3));

    EXPECT_THROW(obuffer.writeUint8At(data16, 5), isc::OutOfRange);
    EXPECT_THROW(obuffer.writeUint8At(data16, 4), isc::OutOfRange);
    EXPECT_THROW(obuffer.writeUint16At(data16, 3), isc::OutOfRange);
    EXPECT_THROW(obuffer.writeUint16At(data16, 4), isc::OutOfRange);
    EXPECT_THROW(obuffer.writeUint16At(data16, 5), isc::OutOfRange);
}

TEST_F(BufferTest, outputBufferSkip) {
    obuffer.skip(4);
    EXPECT_EQ(4, obuffer.getLength());

    obuffer.skip(2);
    EXPECT_EQ(6, obuffer.getLength());
}

TEST_F(BufferTest, outputBufferTrim) {
    obuffer.writeData(testdata, sizeof(testdata));
    EXPECT_EQ(5, obuffer.getLength());

    obuffer.trim(1);
    EXPECT_EQ(4, obuffer.getLength());

    obuffer.trim(2);
    EXPECT_EQ(2, obuffer.getLength());

    EXPECT_THROW(obuffer.trim(3), OutOfRange);
}

TEST_F(BufferTest, outputBufferReadAt) {
    obuffer.writeData(testdata, sizeof(testdata));
    for (size_t i = 0; i < sizeof(testdata); ++i) {
        EXPECT_EQ(testdata[i], obuffer[i]);
    }
    EXPECT_THROW(obuffer[sizeof(testdata)], isc::OutOfRange);
}

TEST_F(BufferTest, outputBufferClear) {
    obuffer.writeData(testdata, sizeof(testdata));
    const uint8_t* cp = obuffer.getData();
    obuffer.clear();
    EXPECT_EQ(0, obuffer.getLength());
    EXPECT_FALSE(obuffer.getData());
}

TEST_F(BufferTest, outputBufferCopy) {
    EXPECT_NO_THROW({
        obuffer.writeData(testdata, sizeof(testdata));

        OutputBuffer copy(obuffer);
        ASSERT_EQ(sizeof(testdata), copy.getLength());
        ASSERT_NE(obuffer.getData(), copy.getData());
        for (size_t i = 0; i < sizeof(testdata); ++i) {
            EXPECT_EQ(testdata[i], copy[i]);
            if (i + 1 < sizeof(testdata)) {
                obuffer.writeUint16At(0, i);
            }
            EXPECT_EQ(testdata[i], copy[i]);
        }
        obuffer.clear();
        ASSERT_EQ(sizeof(testdata), copy.getLength());
    });
}

TEST_F(BufferTest, outputEmptyBufferCopy) {
    EXPECT_NO_THROW({
        OutputBuffer copy(obuffer);
        ASSERT_EQ(0, copy.getLength());
        EXPECT_FALSE(copy.getData());
    });
}

TEST_F(BufferTest, outputBufferAssign) {
    EXPECT_NO_THROW({
        OutputBuffer another(0);
        another.clear();
        obuffer.writeData(testdata, sizeof(testdata));

        another = obuffer;
        ASSERT_EQ(sizeof(testdata), another.getLength());
        ASSERT_NE(obuffer.getData(), another.getData());
        for (size_t i = 0; i < sizeof(testdata); ++i) {
            EXPECT_EQ(testdata[i], another[i]);
            if (i + 1 < sizeof(testdata)) {
                obuffer.writeUint16At(0, i);
            }
            EXPECT_EQ(testdata[i], another[i]);
        }
        obuffer.clear();
        ASSERT_EQ(sizeof(testdata), another.getLength());
    });
}

TEST_F(BufferTest, outputEmptyBufferAssign) {
    OutputBuffer copy(0);
    EXPECT_NO_THROW(copy = obuffer;);
    EXPECT_EQ(0, copy.getLength());
    EXPECT_EQ(0, copy.getData());
}

// Check assign to self doesn't break stuff
TEST_F(BufferTest, outputBufferAssignSelf) {
    EXPECT_NO_THROW(obuffer = obuffer);
}

TEST_F(BufferTest, inputBufferReadVectorChunks) {
    std::vector<uint8_t> vec;

    // check that vector can read the whole buffer
    ibuffer.readVector(vec, 3);
    EXPECT_EQ(3, vec.size());
    EXPECT_EQ(0, memcmp(&vec[0], testdata, 3));
    EXPECT_NO_THROW(ibuffer.readVector(vec, 2));
    ASSERT_EQ(2, vec.size());
    EXPECT_EQ(0, memcmp(&vec[0], &testdata[3], 2));
}

// Tests whether uint64 can be written properly.
TEST_F(BufferTest, writeUint64) {
    uint64_t val1 = 0x0102030405060708ul;
    uint64_t val2 = 0xfffffffffffffffful;
    uint8_t exp_val1[] = { 1, 2, 3, 4, 5, 6, 7, 8 };
    uint8_t exp_val2[] = { 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff };

    obuffer.writeUint64(val1);
    ASSERT_EQ(sizeof(uint64_t), obuffer.getLength());
    const uint8_t* cp = obuffer.getData();
    EXPECT_TRUE(cp);
    EXPECT_FALSE(memcmp(exp_val1, obuffer.getData(), sizeof(uint64_t)));

    EXPECT_NO_THROW(obuffer.clear());
    obuffer.writeUint64(val2);
    ASSERT_EQ(sizeof(uint64_t), obuffer.getLength());
    cp = obuffer.getData();
    EXPECT_TRUE(cp);
    EXPECT_FALSE(memcmp(exp_val2, obuffer.getData(), sizeof(uint64_t)));
}

}
