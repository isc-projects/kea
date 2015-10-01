// Copyright (C) 2015 Internet Systems Consortium, Inc. ("ISC")
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

#include <exceptions/exceptions.h>
#include <dhcp/option_opaque_data_tuples.h>
#include <util/buffer.h>
#include <gtest/gtest.h>

using namespace isc;
using namespace isc::dhcp;
using namespace isc::util;

namespace {

// This test checks that the DHCPv6 option constructor sets the default
// properties to the expected values.
TEST(OptionOpaqueDataTuples, constructor6) {
    OptionOpaqueDataTuples data_tuple(Option::V6, 60);
    // Option length is 2 bytes for option code + 2 bytes for option size
    EXPECT_EQ(4, data_tuple.len());
    // There should be no tuples.
    EXPECT_EQ(0, data_tuple.getTuplesNum());
}

// This test verifies that it is possible to append the opaque data tuple
// to the option and then retrieve it.
TEST(OptionOpaqueDataTuples, addTuple) {
    OptionOpaqueDataTuples data_tuple(Option::V6, 60);
    // Initially there should be no tuples (for DHCPv6).
    ASSERT_EQ(0, data_tuple.getTuplesNum());
    // Create a new tuple and add it to the option.
    OpaqueDataTuple tuple(OpaqueDataTuple::LENGTH_2_BYTES);
    tuple = "xyz";
    data_tuple.addTuple(tuple);
    // The option should now hold one tuple.
    ASSERT_EQ(1, data_tuple.getTuplesNum());
    EXPECT_EQ("xyz", data_tuple.getTuple(0).getText());
    // Add another tuple.
    tuple = "abc";
    data_tuple.addTuple(tuple);
    // The option should now hold exactly two tuples in the order in which
    // they were added.
    ASSERT_EQ(2, data_tuple.getTuplesNum());
    EXPECT_EQ("xyz", data_tuple.getTuple(0).getText());
    EXPECT_EQ("abc", data_tuple.getTuple(1).getText());

    // Check that hasTuple correctly identifies existing tuples.
    EXPECT_TRUE(data_tuple.hasTuple("xyz"));
    EXPECT_TRUE(data_tuple.hasTuple("abc"));
    EXPECT_FALSE(data_tuple.hasTuple("other"));

    // Attempt to add the tuple with 1 byte long length field should fail
    // for DHCPv6 option.
    OpaqueDataTuple tuple2(OpaqueDataTuple::LENGTH_1_BYTE);
    EXPECT_THROW(data_tuple.addTuple(tuple2), isc::BadValue);
}

// This test checks that it is possible to replace existing tuple.
TEST(OptionOpaqueDataTuples, setTuple) {
    OptionOpaqueDataTuples data_tuple(Option::V6, 60);
    // Initially there should be no tuples (for DHCPv6).
    ASSERT_EQ(0, data_tuple.getTuplesNum());
    // Add a tuple
    OpaqueDataTuple tuple(OpaqueDataTuple::LENGTH_2_BYTES);
    tuple = "xyz";
    data_tuple.addTuple(tuple);

    // Add another one.
    tuple = "abc";
    data_tuple.addTuple(tuple);
    ASSERT_EQ(2, data_tuple.getTuplesNum());
    ASSERT_EQ("abc", data_tuple.getTuple(1).getText());

    // Try to replace them with new tuples.
    tuple = "new_xyz";
    ASSERT_NO_THROW(data_tuple.setTuple(0, tuple));
    ASSERT_EQ(2, data_tuple.getTuplesNum());
    EXPECT_EQ("new_xyz", data_tuple.getTuple(0).getText());

    tuple = "new_abc";
    ASSERT_NO_THROW(data_tuple.setTuple(1, tuple));
    ASSERT_EQ(2, data_tuple.getTuplesNum());
    EXPECT_EQ("new_abc", data_tuple.getTuple(1).getText());

    // For out of range position, exception should be thrown.
    tuple = "foo";
    EXPECT_THROW(data_tuple.setTuple(2, tuple), isc::OutOfRange);
}

// Check that the returned length of the DHCPv6 option is correct.
TEST(OptionOpaqueDataTuples, len6) {
    OptionOpaqueDataTuples data_tuple(Option::V6, 60);
    ASSERT_EQ(4, data_tuple.len());
    // Add first tuple.
    OpaqueDataTuple tuple(OpaqueDataTuple::LENGTH_2_BYTES);
    tuple = "xyz";
    ASSERT_NO_THROW(data_tuple.addTuple(tuple));
    // The total length grows by 2 bytes of the length field and 3 bytes
    // consumed by 'xyz'.
    EXPECT_EQ(9, data_tuple.len());
    // Add another tuple and check that the total size gets increased.
    tuple = "abc";
    data_tuple.addTuple(tuple);
    EXPECT_EQ(14, data_tuple.len());
}

// Check that the DHCPv6 option is rendered to the buffer in wire format.
TEST(OptionOpaqueDataTuples, pack6) {
    OptionOpaqueDataTuples data_tuple(Option::V6, 60);
    ASSERT_EQ(0, data_tuple.getTuplesNum());
    // Add tuple.
    OpaqueDataTuple tuple(OpaqueDataTuple::LENGTH_2_BYTES);
    tuple = "Hello world";
    data_tuple.addTuple(tuple);
    // And add another tuple so as resulting option is a bit more complex.
    tuple = "foo";
    data_tuple.addTuple(tuple);

    // Render the data to the buffer.
    OutputBuffer buf(10);
    ASSERT_NO_THROW(data_tuple.pack(buf));
    ASSERT_EQ(22, buf.getLength());

    // Prepare reference data.
    const uint8_t ref[] = {
        0x00, 0x3C, 0x00, 0x12,             // option 60, length 18
        0x00, 0x0B,                         // tuple length is 11
        0x48, 0x65, 0x6C, 0x6C, 0x6F, 0x20, // Hello<space>
        0x77, 0x6F, 0x72, 0x6C, 0x64,       // world
        0x00, 0x03,                         // tuple length is 3
        0x66, 0x6F, 0x6F                    // foo
    };
    // Compare the buffer with reference data.
    EXPECT_EQ(0, memcmp(static_cast<const void*>(ref),
                        static_cast<const void*>(buf.getData()),
                        buf.getLength()));
}

// This function checks that the DHCPv6 option with two opaque data tuples
// is parsed correctly.
TEST(OptionOpaqueDataTuples, unpack6) {
    // Prepare data to decode.
    const uint8_t buf_data[] = {
        0x00, 0x0B,                         // tuple length is 11
        0x48, 0x65, 0x6C, 0x6C, 0x6F, 0x20, // Hello<space>
        0x77, 0x6F, 0x72, 0x6C, 0x64,       // world
        0x00, 0x03,                         // tuple length is 3
        0x66, 0x6F, 0x6F                    // foo
    };
    OptionBuffer buf(buf_data, buf_data + sizeof(buf_data));

    OptionOpaqueDataTuplesPtr data_tuple;
    ASSERT_NO_THROW(
        data_tuple = OptionOpaqueDataTuplesPtr(new OptionOpaqueDataTuples(Option::V6,
                                                                          60,
                                                                          buf.begin(),
                                                                          buf.end()));
    );
    EXPECT_EQ(D6O_BOOTFILE_PARAM, data_tuple->getType());
    ASSERT_EQ(2, data_tuple->getTuplesNum());
    EXPECT_EQ("Hello world", data_tuple->getTuple(0).getText());
    EXPECT_EQ("foo", data_tuple->getTuple(1).getText());
}

// This test checks that the DHCPv6 option with opaque data of size 0
// is correctly parsed.
TEST(OptionOpaqueDataTuples, unpack6EmptyTuple) {
    // Prepare data to decode.
    const uint8_t buf_data[] = {0x00, 0x00}; // tuple length is 0
    OptionBuffer buf(buf_data, buf_data + sizeof(buf_data));

    OptionOpaqueDataTuplesPtr data_tuple;
    ASSERT_NO_THROW(
        data_tuple = OptionOpaqueDataTuplesPtr(new OptionOpaqueDataTuples(Option::V6,
                                                                          60,
                                                                          buf.begin(),
                                                                          buf.end()));
    );
    EXPECT_EQ(D6O_BOOTFILE_PARAM, data_tuple->getType());
    ASSERT_EQ(1, data_tuple->getTuplesNum());
    EXPECT_TRUE(data_tuple->getTuple(0).getText().empty());
}

// This test checks that exception is thrown when parsing truncated DHCPv6
// bootfile-param option
TEST(OptionOpaqueDataTuples, unpack6Truncated) {
    // Prepare data to decode.
    const uint8_t buf_data[] = {
        0x00, 0x0B,                         // tuple length is 11
        0x48, 0x65, 0x6C, 0x6C, 0x6F, 0x20, // Hello<space>
        0x77, 0x6F, 0x72, 0x6C              // worl (truncated d!)
    };
    OptionBuffer buf(buf_data, buf_data + sizeof(buf_data));

    EXPECT_THROW(OptionOpaqueDataTuples (Option::V6, 60, buf.begin(), buf.end()),
                 isc::dhcp::OpaqueDataTupleError);
}

// This test checks that the DHCPv6 bootfile-param option containing no opaque
// data is parsed correctly.
TEST(OptionOpaqueDataTuples, unpack6NoTuple) {
    // Prepare data to decode.
    const uint8_t buf_data[] = {
    };
    OptionBuffer buf(buf_data,buf_data + sizeof(buf_data));

    OptionOpaqueDataTuplesPtr data_tuple;
    ASSERT_NO_THROW(
        data_tuple = OptionOpaqueDataTuplesPtr(new OptionOpaqueDataTuples(Option::V6,
                                                                          60,
                                                                          buf.begin(),
                                                                          buf.end()));
    );
    EXPECT_EQ(D6O_BOOTFILE_PARAM, data_tuple->getType());
    EXPECT_EQ(0, data_tuple->getTuplesNum());
}

// Verifies correctness of the text representation of the DHCPv6 option.
TEST(OptionOpaqueDataTuples, toText6) {
    OptionOpaqueDataTuples data_tuple(Option::V6, 60);
    ASSERT_EQ(0, data_tuple.getTuplesNum());
    // Lets add a tuple
    OpaqueDataTuple tuple(OpaqueDataTuple::LENGTH_2_BYTES);
    tuple = "Hello world";
    data_tuple.addTuple(tuple);
    // And add another tuple so as resulting option is a bit more complex.
    tuple = "foo";
    data_tuple.addTuple(tuple);
    // Check that the text representation of the option is as expected.
    EXPECT_EQ("type=60, len=18,"
              " data-len0=11, data0='Hello world',"
              " data-len1=3, data1='foo'",
              data_tuple.toText());

    // Check that indentation works.
    EXPECT_EQ("  type=60, len=18,"
              " data-len0=11, data0='Hello world',"
              " data-len1=3, data1='foo'",
              data_tuple.toText(2));
}

} // end of anonymous namespace
