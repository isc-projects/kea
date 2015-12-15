// Copyright (C) 2014, 2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <dhcp/opaque_data_tuple.h>
#include <util/buffer.h>
#include <gtest/gtest.h>
#include <algorithm>
#include <sstream>
#include <vector>

using namespace isc;
using namespace isc::dhcp;
using namespace isc::util;

namespace {

// This test checks that when the default constructor is called, the data buffer
// is empty.
TEST(OpaqueDataTuple, constructor) {
    OpaqueDataTuple tuple(OpaqueDataTuple::LENGTH_2_BYTES);
    // There should be no data in the tuple.
    EXPECT_EQ(0, tuple.getLength());
    EXPECT_TRUE(tuple.getData().empty());
    EXPECT_TRUE(tuple.getText().empty());
}

// Test that the constructor which takes the buffer as argument parses the
// wire data.
TEST(OpaqueDataTuple, constructorParse1Byte) {
    const char wire_data[] = {
        0x0B,                               // Length is 11
        0x48, 0x65, 0x6C, 0x6C, 0x6F, 0x20, // Hello<space>
        0x77, 0x6F, 0x72, 0x6C, 0x64        // world
    };

    OpaqueDataTuple tuple(OpaqueDataTuple::LENGTH_1_BYTE, wire_data,
                          wire_data + sizeof(wire_data));

    EXPECT_EQ(11, tuple.getLength());
    EXPECT_EQ("Hello world", tuple.getText());

}

// Test that the constructor which takes the buffer as argument parses the
// wire data.
TEST(OpaqueDataTuple, constructorParse2Bytes) {
    const char wire_data[] = {
        0x00, 0x0B,                         // Length is 11
        0x48, 0x65, 0x6C, 0x6C, 0x6F, 0x20, // Hello<space>
        0x77, 0x6F, 0x72, 0x6C, 0x64        // world
    };

    OpaqueDataTuple tuple(OpaqueDataTuple::LENGTH_2_BYTES, wire_data,
                          wire_data + sizeof(wire_data));

    EXPECT_EQ(11, tuple.getLength());
    EXPECT_EQ("Hello world", tuple.getText());

}


// This test checks that it is possible to set the tuple data using raw buffer.
TEST(OpaqueDataTuple, assignData) {
    OpaqueDataTuple tuple(OpaqueDataTuple::LENGTH_2_BYTES);
    // Initially the tuple buffer should be empty.
    OpaqueDataTuple::Buffer buf = tuple.getData();
    ASSERT_TRUE(buf.empty());
    // Prepare some input data and assign to the tuple.
    const uint8_t data1[] = {
        0xCA, 0xFE, 0xBE, 0xEF
    };
    tuple.assign(data1, sizeof(data1));
    // Tuple should now hold the data we assigned.
    ASSERT_EQ(sizeof(data1), tuple.getLength());
    buf = tuple.getData();
    EXPECT_TRUE(std::equal(buf.begin(), buf.end(), data1));

    // Prepare the other set of data and assign to the tuple.
    const uint8_t data2[] = {
        1, 2, 3, 4, 5, 6
    };
    tuple.assign(data2, sizeof(data2));
    // The new data should have replaced the old data.
    ASSERT_EQ(sizeof(data2), tuple.getLength());
    buf = tuple.getData();
    EXPECT_TRUE(std::equal(buf.begin(), buf.end(), data2));
}

// This test checks that it is possible to append the data to the tuple using
// raw buffer.
TEST(OpaqueDataTuple, appendData) {
    OpaqueDataTuple tuple(OpaqueDataTuple::LENGTH_2_BYTES);
    // Initially the tuple buffer should be empty.
    OpaqueDataTuple::Buffer buf = tuple.getData();
    ASSERT_TRUE(buf.empty());
    // Prepare some input data and append to the empty tuple.
    const uint8_t data1[] = {
        0xCA, 0xFE, 0xBE, 0xEF
    };
    tuple.append(data1, sizeof(data1));
    // The tuple should now hold only the data we appended.
    ASSERT_EQ(sizeof(data1), tuple.getLength());
    buf = tuple.getData();
    EXPECT_TRUE(std::equal(buf.begin(), buf.end(), data1));
    // Prepare the new set of data and append.
    const uint8_t data2[] = {
        1, 2, 3, 4, 5, 6
    };
    tuple.append(data2, sizeof(data2));
    // We expect that the tuple now has both sets of data we appended. In order
    // to verify that, we have to concatenate the input data1 and data2.
    std::vector<uint8_t> data12(data1, data1 + sizeof(data1));
    data12.insert(data12.end(), data2, data2 + sizeof(data2));
    // The size of the tuple should be a sum of data1 and data2 lengths.
    ASSERT_EQ(sizeof(data1) + sizeof(data2), tuple.getLength());
    buf = tuple.getData();
    EXPECT_TRUE(std::equal(buf.begin(), buf.end(), data12.begin()));
}

// This test checks that it is possible to assign the string to the tuple.
TEST(OpaqueDataTuple, assignString) {
    OpaqueDataTuple tuple(OpaqueDataTuple::LENGTH_2_BYTES);
    // Initially, the tuple should be empty.
    ASSERT_EQ(0, tuple.getLength());
    // Assign some string data.
    tuple.assign("Some string");
    // Verify that the data has been assigned.
    EXPECT_EQ(11, tuple.getLength());
    EXPECT_EQ("Some string", tuple.getText());
    // Assign some other string.
    tuple.assign("Different string");
    // The new string should have replaced the old string.
    EXPECT_EQ(16, tuple.getLength());
    EXPECT_EQ("Different string", tuple.getText());
}

// This test checks that it is possible to append the string to the tuple.
TEST(OpaqueDataTuple, appendString) {
    OpaqueDataTuple tuple(OpaqueDataTuple::LENGTH_2_BYTES);
    // Initially the tuple should be empty.
    ASSERT_EQ(0, tuple.getLength());
    // Append the string to it.
    tuple.append("First part");
    ASSERT_EQ(10, tuple.getLength());
    ASSERT_EQ("First part", tuple.getText());
    // Now append the other string.
    tuple.append(" and second part");
    EXPECT_EQ(26, tuple.getLength());
    // The resulting data in the tuple should be a concatenation of both
    // strings.
    EXPECT_EQ("First part and second part", tuple.getText());
}

// This test verifies that equals function correctly checks that the tuple
// holds a given string but it doesn't hold the other. This test also
// checks the assignment operator for the tuple.
TEST(OpaqueDataTuple, equals) {
    OpaqueDataTuple tuple(OpaqueDataTuple::LENGTH_2_BYTES);
    // Tuple is supposed to be empty so it is not equal xyz.
    EXPECT_FALSE(tuple.equals("xyz"));
    // Assign xyz.
    EXPECT_NO_THROW(tuple = "xyz");
    // The tuple should be equal xyz, but not abc.
    EXPECT_FALSE(tuple.equals("abc"));
    EXPECT_TRUE(tuple.equals("xyz"));
    // Assign abc to the tuple.
    EXPECT_NO_THROW(tuple = "abc");
    // It should be now opposite.
    EXPECT_TRUE(tuple.equals("abc"));
    EXPECT_FALSE(tuple.equals("xyz"));
}

// This test checks that the conversion of the data in the tuple to the string
// is performed correctly.
TEST(OpaqueDataTuple, getText) {
    OpaqueDataTuple tuple(OpaqueDataTuple::LENGTH_2_BYTES);
    // Initially the tuple should be empty.
    ASSERT_TRUE(tuple.getText().empty());
    // ASCII representation of 'Hello world'.
    const char as_ascii[] = {
        0x48, 0x65, 0x6C, 0x6C, 0x6F, 0x20, // Hello<space>
        0x77, 0x6F, 0x72, 0x6C, 0x64        // world
    };
    // Assign it to the tuple.
    tuple.assign(as_ascii, sizeof(as_ascii));
    // Conversion to string should give as the original text.
    EXPECT_EQ("Hello world", tuple.getText());
}

// This test verifies the behavior of (in)equality and assignment operators.
TEST(OpaqueDataTuple, operators) {
    OpaqueDataTuple tuple(OpaqueDataTuple::LENGTH_2_BYTES);
    // Tuple should be empty initially.
    ASSERT_EQ(0, tuple.getLength());
    // Check assignment.
    EXPECT_NO_THROW(tuple = "Hello World");
    EXPECT_EQ(11, tuple.getLength());
    EXPECT_TRUE(tuple == "Hello World");
    EXPECT_TRUE(tuple != "Something else");
    // Assign something else to make sure it affects the tuple.
    EXPECT_NO_THROW(tuple = "Something else");
    EXPECT_EQ(14, tuple.getLength());
    EXPECT_TRUE(tuple == "Something else");
    EXPECT_TRUE(tuple != "Hello World");
}

// This test verifies that the tuple is inserted in the textual format to the
// output stream.
TEST(OpaqueDataTuple, operatorOutputStream) {
    OpaqueDataTuple tuple(OpaqueDataTuple::LENGTH_2_BYTES);
    // The tuple should be empty initially.
    ASSERT_EQ(0, tuple.getLength());
    // The tuple is empty, so assigning its content to the output stream should
    // be no-op and result in the same text in the stream.
    std::ostringstream s;
    s << "Some text";
    EXPECT_NO_THROW(s << tuple);
    EXPECT_EQ("Some text", s.str());
    // Now, let's assign some text to the tuple and call operator again.
    // The new text should be added to the stream.
    EXPECT_NO_THROW(tuple = " and some other text");
    EXPECT_NO_THROW(s << tuple);
    EXPECT_EQ(s.str(), "Some text and some other text");

}

// This test verifies that the value of the tuple can be initialized from the
// input stream.
TEST(OpaqueDataTuple, operatorInputStream) {
    OpaqueDataTuple tuple(OpaqueDataTuple::LENGTH_2_BYTES);
    // The tuple should be empty initially.
    ASSERT_EQ(0, tuple.getLength());
    // The input stream has some text. This text should be appended to the
    // tuple.
    std::istringstream s;
    s.str("Some text");
    EXPECT_NO_THROW(s >> tuple);
    EXPECT_EQ("Some text", tuple.getText());
    // Now, let's assign some other text to the stream. This new text should be
    // assigned to the tuple.
    s.str("And some other");
    EXPECT_NO_THROW(s >> tuple);
    EXPECT_EQ("And some other", tuple.getText());
}

// This test checks that the tuple is correctly encoded in the wire format when
// the size of the length field is 1 byte.
TEST(OpaqueDataTuple, pack1Byte) {
    OpaqueDataTuple tuple(OpaqueDataTuple::LENGTH_1_BYTE);
    // Initially, the tuple should be empty.
    ASSERT_EQ(0, tuple.getLength());
    // The empty data doesn't make much sense, so the pack() should not
    // allow it.
    OutputBuffer out_buf(10);
    EXPECT_THROW(tuple.pack(out_buf), OpaqueDataTupleError);
    // Set the data for tuple.
    std::vector<uint8_t> data;
    for (uint8_t i = 0; i < 100; ++i) {
        data.push_back(i);
    }
    tuple.assign(data.begin(), data.size());
    // The pack should now succeed.
    ASSERT_NO_THROW(tuple.pack(out_buf));
    // The rendered buffer should be 101 bytes long - 1 byte for length,
    // 100 bytes for the actual data.
    ASSERT_EQ(101, out_buf.getLength());
    // Get the rendered data into the vector for convenience.
    std::vector<uint8_t>
        render_data(static_cast<const uint8_t*>(out_buf.getData()),
                    static_cast<const uint8_t*>(out_buf.getData()) + 101);
    // The first byte is a length byte. It should hold the length of 100.
    EXPECT_EQ(100, render_data[0]);
    // Verify that the rendered data is correct.
    EXPECT_TRUE(std::equal(render_data.begin() + 1, render_data.end(),
                           data.begin()));
    // Reset the output buffer for another test.
    out_buf.clear();
    // Fill in the tuple buffer so as it reaches maximum allowed length. The
    // maximum length is 255 when the size of the length field is one byte.
    for (uint8_t i = 100; i < 255; ++i) {
        data.push_back(i);
    }
    ASSERT_EQ(255, data.size());
    tuple.assign(data.begin(), data.size());
    // The pack() should be successful again.
    ASSERT_NO_THROW(tuple.pack(out_buf));
    // The rendered buffer should be 256 bytes long. The first byte holds the
    // opaque data length, the remaining bytes hold the actual data.
    ASSERT_EQ(256, out_buf.getLength());
    // Check that the data is correct.
    render_data.assign(static_cast<const uint8_t*>(out_buf.getData()),
                       static_cast<const uint8_t*>(out_buf.getData()) + 256);
    EXPECT_EQ(255, render_data[0]);
    EXPECT_TRUE(std::equal(render_data.begin() + 1, render_data.end(),
                           data.begin()));
    // Clear output buffer for another test.
    out_buf.clear();
    // Add one more value to the tuple. Now, the resulting buffer should exceed
    // the maximum length. An attempt to pack() should fail.
    data.push_back(255);
    tuple.assign(data.begin(), data.size());
    EXPECT_THROW(tuple.pack(out_buf), OpaqueDataTupleError);
}

// This test checks that the tuple is correctly encoded in the wire format when
// the size of the length field is 2 bytes.
TEST(OpaqueDataTuple, pack2Bytes) {
    OpaqueDataTuple tuple(OpaqueDataTuple::LENGTH_2_BYTES);
    // Initially, the tuple should be empty.
    ASSERT_EQ(0, tuple.getLength());
    // The empty data doesn't make much sense, so the pack() should not
    // allow it.
    OutputBuffer out_buf(10);
    EXPECT_THROW(tuple.pack(out_buf), OpaqueDataTupleError);
    // Set the data for tuple.
    std::vector<uint8_t> data;
    for (unsigned i = 0; i < 512; ++i) {
        data.push_back(i & 0xff);
    }
    tuple.assign(data.begin(), data.size());
    // The pack should now succeed.
    ASSERT_NO_THROW(tuple.pack(out_buf));
    // The rendered buffer should be 514 bytes long - 2 bytes for length,
    // 512 bytes for the actual data.
    ASSERT_EQ(514, out_buf.getLength());
    // Get the rendered data into the vector for convenience.
    std::vector<uint8_t>
        render_data(static_cast<const uint8_t*>(out_buf.getData()),
                    static_cast<const uint8_t*>(out_buf.getData()) + 514);
    // The first two bytes hold the length of 512.
    uint16_t len = (render_data[0] << 8) + render_data[1];
    EXPECT_EQ(512, len);
    // Verify that the rendered data is correct.
    EXPECT_TRUE(std::equal(render_data.begin() + 2, render_data.end(),
                           data.begin()));

    // Without clearing the output buffer, try to do it again. The pack should
    // append the data to the current buffer.
    ASSERT_NO_THROW(tuple.pack(out_buf));
    EXPECT_EQ(1028, out_buf.getLength());

    // Check that we can render the buffer of the maximal allowed size.
    data.assign(65535, 1);
    ASSERT_NO_THROW(tuple.assign(data.begin(), data.size()));
    ASSERT_NO_THROW(tuple.pack(out_buf));

    out_buf.clear();

    // Append one additional byte. The total length of the tuple now exceeds
    // the maximal value. An attempt to render it should throw an exception.
    data.assign(1, 1);
    ASSERT_NO_THROW(tuple.append(data.begin(), data.size()));
    EXPECT_THROW(tuple.pack(out_buf), OpaqueDataTupleError);
}

// This test verifies that the tuple is decoded from the wire format.
TEST(OpaqueDataTuple, unpack1Byte) {
    OpaqueDataTuple tuple(OpaqueDataTuple::LENGTH_1_BYTE);
    const char wire_data[] = {
        0x0B,                               // Length is 11
        0x48, 0x65, 0x6C, 0x6C, 0x6F, 0x20, // Hello<space>
        0x77, 0x6F, 0x72, 0x6C, 0x64        // world
    };

    ASSERT_NO_THROW(tuple.unpack(wire_data, wire_data + sizeof(wire_data)));
    EXPECT_EQ(11, tuple.getLength());
    EXPECT_EQ("Hello world", tuple.getText());
}

// This test verifies that the tuple having a length of 0, is decoded from
// the wire format.
TEST(OpaqueDataTuple, unpack1ByteZeroLength) {
    OpaqueDataTuple tuple(OpaqueDataTuple::LENGTH_1_BYTE);
    EXPECT_NO_THROW(tuple = "Hello world");
    ASSERT_NE(tuple.getLength(), 0);

    const char wire_data[] = {
        0
    };
    ASSERT_NO_THROW(tuple.unpack(wire_data, wire_data + sizeof(wire_data)));

    EXPECT_EQ(0, tuple.getLength());
}

// This test verfifies that exception is thrown if the empty buffer is being
// parsed.
TEST(OpaqueDataTuple, unpack1ByteEmptyBuffer) {
    OpaqueDataTuple tuple(OpaqueDataTuple::LENGTH_1_BYTE);
    const char wire_data[] = {
        1, 2, 3
    };
    EXPECT_THROW(tuple.unpack(wire_data, wire_data), OpaqueDataTupleError);
}

// This test verifies that exception is thrown when parsing truncated buffer.
TEST(OpaqueDataTuple, unpack1ByteTruncatedBuffer) {
   OpaqueDataTuple tuple(OpaqueDataTuple::LENGTH_1_BYTE);
    const char wire_data[] = {
        10, 2, 3
    };
    EXPECT_THROW(tuple.unpack(wire_data, wire_data + sizeof(wire_data)),
                 OpaqueDataTupleError);
}

// This test verifies that the tuple is decoded from the wire format.
TEST(OpaqueDataTuple, unpack2Byte) {
    OpaqueDataTuple tuple(OpaqueDataTuple::LENGTH_2_BYTES);
    std::vector<uint8_t> wire_data;
    // Set tuple length to 400 (0x190).
    wire_data.push_back(1);
    wire_data.push_back(0x90);
    // Fill in the buffer with some data.
    for (int i = 0; i < 400; ++i) {
        wire_data.push_back(i);
    }
    // The unpack shoud succeed.
    ASSERT_NO_THROW(tuple.unpack(wire_data.begin(), wire_data.end()));
    // The decoded length should be 400.
    ASSERT_EQ(400, tuple.getLength());
    // And the data should match.
    EXPECT_TRUE(std::equal(wire_data.begin() + 2, wire_data.end(),
                           tuple.getData().begin()));
}

// This test verifies that the tuple having a length of 0, is decoded from
// the wire format.
TEST(OpaqueDataTuple, unpack2ByteZeroLength) {
    OpaqueDataTuple tuple(OpaqueDataTuple::LENGTH_2_BYTES);
    // Set some data for the tuple.
    EXPECT_NO_THROW(tuple = "Hello world");
    ASSERT_NE(tuple.getLength(), 0);
    // The buffer holds just a length field with the value of 0.
    const char wire_data[] = {
        0, 0
    };
    // The empty tuple should be successfully decoded.
    ASSERT_NO_THROW(tuple.unpack(wire_data, wire_data + sizeof(wire_data)));
    // The data should be replaced with an empty buffer.
    EXPECT_EQ(0, tuple.getLength());
}

// This test verifies that exception is thrown if the empty buffer is being
// parsed.
TEST(OpaqueDataTuple, unpack2ByteEmptyBuffer) {
    OpaqueDataTuple tuple(OpaqueDataTuple::LENGTH_2_BYTES);
    //  Initialize the input buffer with some data, just to avoid initializing
    // empty array.
    const char wire_data[] = {
        1, 2, 3
    };
    // Pass empty buffer (first iterator equal to second iterator).
    // This should not be accepted.
    EXPECT_THROW(tuple.unpack(wire_data, wire_data), OpaqueDataTupleError);
}

// This test verifies that exception if thrown when parsing truncated buffer.
TEST(OpaqueDataTuple, unpack2ByteTruncatedBuffer) {
   OpaqueDataTuple tuple(OpaqueDataTuple::LENGTH_2_BYTES);
   // Specify the data with the length of 10, but limit the buffer size to
   // 2 bytes.
   const char wire_data[] = {
       0, 10, 2, 3
   };
   // This should fail because the buffer is truncated.
   EXPECT_THROW(tuple.unpack(wire_data, wire_data + sizeof(wire_data)),
                OpaqueDataTupleError);
}


} // anonymous namespace
