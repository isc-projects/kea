// Copyright (C) 2009, 2015  Internet Systems Consortium, Inc. ("ISC")
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

#include <config.h>

#include <gtest/gtest.h>

#include <exceptions/exceptions.h>

#ifdef EXPECT_DEATH
#include <util/unittests/resource.h>
#include <util/unittests/check_valgrind.h>
#endif /* EXPECT_DEATH */

#include <util/buffer.h>

using namespace isc;

namespace {

using isc::util::InputBuffer;
using isc::util::OutputBuffer;

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

TEST_F(BufferTest, inputBufferRead) {
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

TEST_F(BufferTest, inputBufferException) {
    EXPECT_THROW(ibuffer.setPosition(6), isc::util::InvalidBufferPosition);

    ibuffer.setPosition(sizeof(testdata));
    EXPECT_THROW(ibuffer.readUint8(), isc::util::InvalidBufferPosition);

    ibuffer.setPosition(sizeof(testdata) - 1);
    EXPECT_THROW(ibuffer.readUint16(), isc::util::InvalidBufferPosition);

    ibuffer.setPosition(sizeof(testdata) - 3);
    EXPECT_THROW(ibuffer.readUint32(), isc::util::InvalidBufferPosition);

    ibuffer.setPosition(sizeof(testdata) - 4);
    EXPECT_THROW(ibuffer.readData(vdata, sizeof(vdata)),
                 isc::util::InvalidBufferPosition);
}

TEST_F(BufferTest, outputBufferExtend) {
    EXPECT_EQ(0, obuffer.getCapacity());
    EXPECT_EQ(0, obuffer.getLength());
    obuffer.writeUint8(10);
    EXPECT_LT(0, obuffer.getCapacity());
    EXPECT_EQ(1, obuffer.getLength());
}

TEST_F(BufferTest, outputBufferWrite) {
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

TEST_F(BufferTest, outputBufferWriteat) {
    obuffer.writeUint32(data32);
    expected_size += sizeof(data32);

    // overwrite 2nd byte
    obuffer.writeUint8At(4, 1);
    EXPECT_EQ(expected_size, obuffer.getLength()); // length shouldn't change
    const uint8_t* cp = static_cast<const uint8_t*>(obuffer.getData());
    EXPECT_EQ(4, *(cp + 1));

    // overwrite 2nd and 3rd bytes
    obuffer.writeUint16At(data16, 1);
    EXPECT_EQ(expected_size, obuffer.getLength()); // length shouldn't change
    cp = static_cast<const uint8_t*>(obuffer.getData());
    EXPECT_EQ(2, *(cp + 1));
    EXPECT_EQ(3, *(cp + 2));

    // overwrite 3rd and 4th bytes
    obuffer.writeUint16At(data16, 2);
    EXPECT_EQ(expected_size, obuffer.getLength());
    cp = static_cast<const uint8_t*>(obuffer.getData());
    EXPECT_EQ(2, *(cp + 2));
    EXPECT_EQ(3, *(cp + 3));

    EXPECT_THROW(obuffer.writeUint8At(data16, 5),
                 isc::util::InvalidBufferPosition);
    EXPECT_THROW(obuffer.writeUint8At(data16, 4),
                 isc::util::InvalidBufferPosition);
    EXPECT_THROW(obuffer.writeUint16At(data16, 3),
                 isc::util::InvalidBufferPosition);
    EXPECT_THROW(obuffer.writeUint16At(data16, 4),
                 isc::util::InvalidBufferPosition);
    EXPECT_THROW(obuffer.writeUint16At(data16, 5),
                 isc::util::InvalidBufferPosition);
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
    for (int i = 0; i < sizeof(testdata); i ++) {
        EXPECT_EQ(testdata[i], obuffer[i]);
    }
#ifdef EXPECT_DEATH
    // We use assert now, so we check it dies
    if (!isc::util::unittests::runningOnValgrind()) {
        EXPECT_DEATH({
            isc::util::unittests::dontCreateCoreDumps();

            try {
                obuffer[sizeof(testdata)];
            } catch (...) {
                // Prevent exceptions killing the application, we need
                // to make sure it dies the real hard way
            }
            }, "");
    }
#endif
}

TEST_F(BufferTest, outputBufferClear) {
    const uint8_t* cp;

    obuffer.writeData(testdata, sizeof(testdata));
    cp = static_cast<const uint8_t*>(obuffer.getData());
    obuffer.clear();
    EXPECT_EQ(0, obuffer.getLength());
    EXPECT_EQ(*cp, 1);
}

TEST_F(BufferTest, outputBufferWipe) {
    const uint8_t* cp;

    obuffer.writeData(testdata, sizeof(testdata));
    cp = static_cast<const uint8_t*>(obuffer.getData());
    obuffer.wipe();
    EXPECT_EQ(0, obuffer.getLength());
    EXPECT_EQ(*cp, 0);
}

TEST_F(BufferTest, outputBufferCopy) {
    obuffer.writeData(testdata, sizeof(testdata));

    EXPECT_NO_THROW({
        OutputBuffer copy(obuffer);
        ASSERT_EQ(sizeof(testdata), copy.getLength());
        for (int i = 0; i < sizeof(testdata); i ++) {
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

TEST_F(BufferTest, outputBufferAssign) {
    OutputBuffer another(0);
    another.clear();
    obuffer.writeData(testdata, sizeof(testdata));

    EXPECT_NO_THROW({
        another = obuffer;
        ASSERT_EQ(sizeof(testdata), another.getLength());
        for (int i = 0; i < sizeof(testdata); i ++) {
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

// Check assign to self doesn't break stuff
TEST_F(BufferTest, outputBufferAssignSelf) {
    EXPECT_NO_THROW(obuffer = obuffer);
}

TEST_F(BufferTest, outputBufferZeroSize) {
    // Some OSes might return NULL on malloc for 0 size, so check it works
    EXPECT_NO_THROW({
        OutputBuffer first(0);
        OutputBuffer copy(first);
        OutputBuffer second(0);
        second = first;
    });
}

TEST_F(BufferTest, inputBufferReadVectorAll) {
    std::vector<uint8_t> vec;

    // check that vector can read the whole buffer
    ibuffer.readVector(vec, 5);

    ASSERT_EQ(5, vec.size());
    EXPECT_EQ(0, memcmp(&vec[0], testdata, 5));

    // ibuffer is 5 bytes long. Can't read past it.
    EXPECT_THROW(
        ibuffer.readVector(vec, 1),
        isc::util::InvalidBufferPosition
    );
}

TEST_F(BufferTest, inputBufferReadVectorChunks) {
    std::vector<uint8_t> vec;

    // check that vector can read the whole buffer
    ibuffer.readVector(vec, 3);
    EXPECT_EQ(3, vec.size());

    EXPECT_EQ(0, memcmp(&vec[0], testdata, 3));

    EXPECT_NO_THROW(
        ibuffer.readVector(vec, 2)
    );

    EXPECT_EQ(0, memcmp(&vec[0], testdata+3, 2));
}

}
