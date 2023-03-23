// Copyright (C) 2015-2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <exceptions/exceptions.h>
#include <dhcp/option_opaque_data_tuples.h>
#include <util/buffer.h>
#include <gtest/gtest.h>

using namespace isc;
using namespace isc::dhcp;
using namespace isc::util;

namespace {

// This test checks that the DHCPv4 option constructor sets the default
// properties to the expected values.
TEST(OptionOpaqueDataTuples, constructor4) {
    OptionOpaqueDataTuples data_tuple(Option::V4, DHO_VIVCO_SUBOPTIONS);
    // Option length is 1 byte for option code + 1 byte for option size
    EXPECT_EQ(2, data_tuple.len());
    // There should be no tuples.
    EXPECT_EQ(0, data_tuple.getTuplesNum());
}

// This test checks that the DHCPv4 option constructor sets the default
// properties to the expected values.
TEST(OptionOpaqueDataTuples, constructor4_with_ltf) {
    OptionOpaqueDataTuples data_tuple(Option::V4, DHO_V4_SZTP_REDIRECT,
                                      OpaqueDataTuple::LENGTH_2_BYTES);
    // Option length is 1 byte for option code + 1 byte for option size
    EXPECT_EQ(2, data_tuple.len());
    // There should be no tuples.
    EXPECT_EQ(0, data_tuple.getTuplesNum());
}

// This test checks that the DHCPv6 option constructor sets the default
// properties to the expected values.
TEST(OptionOpaqueDataTuples, constructor6) {
    OptionOpaqueDataTuples data_tuple(Option::V6, D6O_BOOTFILE_PARAM);
    // Option length is 2 bytes for option code + 2 bytes for option size
    EXPECT_EQ(4, data_tuple.len());
    // There should be no tuples.
    EXPECT_EQ(0, data_tuple.getTuplesNum());
}

// This test verifies that it is possible to append the opaque data tuple
// to the option and then retrieve it.
TEST(OptionOpaqueDataTuples, addTuple4) {
    OptionOpaqueDataTuples data_tuple(Option::V4, DHO_VIVCO_SUBOPTIONS);
    // Initially there should be no tuples (for DHCPv4).
    ASSERT_EQ(0, data_tuple.getTuplesNum());
    // Create a new tuple and add it to the option.
    OpaqueDataTuple tuple(OpaqueDataTuple::LENGTH_1_BYTE);
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

    // Attempt to add the tuple with 2 byte long length field should fail
    // for DHCPv4 option.
    OpaqueDataTuple tuple2(OpaqueDataTuple::LENGTH_2_BYTES);
    EXPECT_THROW(data_tuple.addTuple(tuple2), isc::BadValue);

    // Similarly, adding a tuple with 1 bytes long length field should
    // fail for DHCPv6 option.
    OptionOpaqueDataTuples data_tuple2(Option::V6, D6O_BOOTFILE_PARAM);
    OpaqueDataTuple tuple3(OpaqueDataTuple::LENGTH_1_BYTE);
    EXPECT_THROW(data_tuple2.addTuple(tuple3), isc::BadValue);
}

// This test verifies that it is possible to append the opaque data tuple
// to the option and then retrieve it.
TEST(OptionOpaqueDataTuples, addTuple6) {
    OptionOpaqueDataTuples data_tuple(Option::V6, D6O_BOOTFILE_PARAM);
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

    // Similarly, adding a tuple with 2 bytes long length field should
    // fail for DHCPv4 option.
    OptionOpaqueDataTuples data_tuple2(Option::V4, DHO_VIVCO_SUBOPTIONS);
    OpaqueDataTuple tuple3(OpaqueDataTuple::LENGTH_2_BYTES);
    EXPECT_THROW(data_tuple2.addTuple(tuple3), isc::BadValue);
}

// This test checks that it is possible to replace existing tuple.
TEST(OptionOpaqueDataTuples, setTuple4) {
    OptionOpaqueDataTuples data_tuple(Option::V4, DHO_VIVCO_SUBOPTIONS);
    // Initially there should be no tuples (for DHCPv4).
    ASSERT_EQ(0, data_tuple.getTuplesNum());
    // Add a tuple
    OpaqueDataTuple tuple(OpaqueDataTuple::LENGTH_1_BYTE);
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

// This test checks that it is possible to replace existing tuple.
TEST(OptionOpaqueDataTuples, setTuple6) {
    OptionOpaqueDataTuples data_tuple(Option::V6, D6O_BOOTFILE_PARAM);
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

// Check that the returned length of the DHCPv4 option is correct.
TEST(OptionOpaqueDataTuples, len4) {
    OptionOpaqueDataTuples data_tuple(Option::V4, DHO_VIVCO_SUBOPTIONS);
    ASSERT_EQ(2, data_tuple.len());
    // Add first tuple.
    OpaqueDataTuple tuple(OpaqueDataTuple::LENGTH_1_BYTE);
    tuple = "xyz";
    ASSERT_NO_THROW(data_tuple.addTuple(tuple));
    // The total length grows by 1 byte of the length field and 3 bytes
    // consumed by 'xyz'.
    EXPECT_EQ(6, data_tuple.len());
    // Add another tuple and check that the total size gets increased.
    tuple = "abc";
    data_tuple.addTuple(tuple);
    EXPECT_EQ(10, data_tuple.len());
}

// Check that the returned length of the DHCPv4 option is correct when
// LTF is passed explicitly in constructor.
TEST(OptionOpaqueDataTuples, len4_constructor_with_ltf) {
    // Prepare data to decode.
    const uint8_t buf_data[] = {
        0x00, 0x0B,                         // tuple length is 11
        0x48, 0x65, 0x6C, 0x6C, 0x6F, 0x20, // Hello<space>
        0x77, 0x6F, 0x72, 0x6C, 0x64,       // world
        0x00, 0x03,                         // tuple length is 3
        0x66, 0x6F, 0x6F                    // foo
    };

    OptionBuffer buf(buf_data, buf_data + sizeof(buf_data));
    OptionOpaqueDataTuples data_tuple(Option::V4, DHO_V4_SZTP_REDIRECT, buf.begin(),
                                      buf.end(), OpaqueDataTuple::LENGTH_2_BYTES);
    // Expected len = 20 = 2 (v4 headers) + 2 (LFT) + 11 (1st tuple) + 2 (LFT) + 3 (2nd tuple)
    ASSERT_EQ(20, data_tuple.len());
}

// Check that the returned length of the DHCPv6 option is correct.
TEST(OptionOpaqueDataTuples, len6) {
    OptionOpaqueDataTuples data_tuple(Option::V6, D6O_BOOTFILE_PARAM);
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

// Check that the DHCPv4 option is rendered to the buffer in wire format.
TEST(OptionOpaqueDataTuples, pack4) {
    OptionOpaqueDataTuples data_tuple(Option::V4, DHO_VIVCO_SUBOPTIONS);
    ASSERT_EQ(0, data_tuple.getTuplesNum());
    // Add tuple.
    OpaqueDataTuple tuple(OpaqueDataTuple::LENGTH_1_BYTE);
    tuple = "Hello world";
    data_tuple.addTuple(tuple);
    // And add another tuple so as resulting option is a bit more complex.
    tuple = "foo";
    data_tuple.addTuple(tuple);

    // Render the data to the buffer.
    OutputBuffer buf(10);
    ASSERT_NO_THROW(data_tuple.pack(buf));
    ASSERT_EQ(18, buf.getLength());

    // Prepare reference data.
    const uint8_t ref[] = {
        0x7C, 0x10,                         // option 124, length 16
        0x0B,                               // tuple length is 11
        0x48, 0x65, 0x6C, 0x6C, 0x6F, 0x20, // Hello<space>
        0x77, 0x6F, 0x72, 0x6C, 0x64,       // world
        0x03,                               // tuple length is 3
        0x66, 0x6F, 0x6F                    // foo
    };
    // Compare the buffer with reference data.
    EXPECT_EQ(0, memcmp(static_cast<const void*>(ref),
                        static_cast<const void*>(buf.getData()),
                        buf.getLength()));
}

// Check that the DHCPv4 option is rendered to the buffer in wire format,
// when tuple's length field is coded on 2 octets.
TEST(OptionOpaqueDataTuples, pack4_with_ltf) {
    OptionOpaqueDataTuples data_tuple(Option::V4, DHO_V4_SZTP_REDIRECT,
                                      OpaqueDataTuple::LENGTH_2_BYTES);
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
    ASSERT_EQ(20, buf.getLength());

    // Prepare reference data.
    const uint8_t ref[] = {
        0x8F, 0x12,                         // option 143, length 18
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

// Check that the DHCPv6 option is rendered to the buffer in wire format.
TEST(OptionOpaqueDataTuples, pack6) {
    OptionOpaqueDataTuples data_tuple(Option::V6, D6O_BOOTFILE_PARAM);
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

// This function checks that the DHCPv4 option with two opaque data tuples
// is parsed correctly.
TEST(OptionOpaqueDataTuples, unpack4) {
    // Prepare data to decode.
    const uint8_t buf_data[] = {
        0x0B,                               // tuple length is 11
        0x48, 0x65, 0x6C, 0x6C, 0x6F, 0x20, // Hello<space>
        0x77, 0x6F, 0x72, 0x6C, 0x64,       // world
        0x03,                               // tuple length is 3
        0x66, 0x6F, 0x6F                    // foo
    };
    OptionBuffer buf(buf_data, buf_data + sizeof(buf_data));

    OptionOpaqueDataTuplesPtr data_tuple;
    ASSERT_NO_THROW(
        data_tuple = OptionOpaqueDataTuplesPtr(new OptionOpaqueDataTuples(Option::V4,
                                                                          DHO_VIVCO_SUBOPTIONS,
                                                                          buf.begin(),
                                                                          buf.end()));
    );
    EXPECT_EQ(DHO_VIVCO_SUBOPTIONS, data_tuple->getType());
    ASSERT_EQ(2, data_tuple->getTuplesNum());
    EXPECT_EQ("Hello world", data_tuple->getTuple(0).getText());
    EXPECT_EQ("foo", data_tuple->getTuple(1).getText());
}

// This function checks that the DHCPv4 option with two opaque data tuples
// is parsed correctly. Tuple's LTF is passed explicitly in constructor.
TEST(OptionOpaqueDataTuples, unpack4_constructor_with_ltf) {
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
        data_tuple = OptionOpaqueDataTuplesPtr(new OptionOpaqueDataTuples(Option::V4,
                                                                          DHO_V4_SZTP_REDIRECT,
                                                                          buf.begin(),
                                                                          buf.end(),
                                                                          OpaqueDataTuple::LENGTH_2_BYTES));
    );
    EXPECT_EQ(DHO_V4_SZTP_REDIRECT, data_tuple->getType());
    ASSERT_EQ(2, data_tuple->getTuplesNum());
    EXPECT_EQ("Hello world", data_tuple->getTuple(0).getText());
    EXPECT_EQ("foo", data_tuple->getTuple(1).getText());
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
                                                                          D6O_BOOTFILE_PARAM,
                                                                          buf.begin(),
                                                                          buf.end()));
    );
    EXPECT_EQ(D6O_BOOTFILE_PARAM, data_tuple->getType());
    ASSERT_EQ(2, data_tuple->getTuplesNum());
    EXPECT_EQ("Hello world", data_tuple->getTuple(0).getText());
    EXPECT_EQ("foo", data_tuple->getTuple(1).getText());
}

// This test checks that the DHCPv4 option with opaque data of size 0
// is correctly parsed.
TEST(OptionOpaqueDataTuples, unpack4EmptyTuple) {
    // Prepare data to decode.
    const uint8_t buf_data[] = {0x00}; // tuple length is 0
    OptionBuffer buf(buf_data, buf_data + sizeof(buf_data));

    OptionOpaqueDataTuplesPtr data_tuple;
    ASSERT_NO_THROW(
        data_tuple = OptionOpaqueDataTuplesPtr(new OptionOpaqueDataTuples(Option::V4,
                                                                          DHO_VIVCO_SUBOPTIONS,
                                                                          buf.begin(),
                                                                          buf.end()));
    );
    EXPECT_EQ(DHO_VIVCO_SUBOPTIONS, data_tuple->getType());
    ASSERT_EQ(1, data_tuple->getTuplesNum());
    EXPECT_TRUE(data_tuple->getTuple(0).getText().empty());
}

// This test checks that the DHCPv4 option with opaque data of size 0
// is correctly parsed. Tuple's LTF is passed explicitly in constructor.
TEST(OptionOpaqueDataTuples, unpack4EmptyTuple_constructor_with_ltf) {
    // Prepare data to decode.
    const uint8_t buf_data[] = {0x00, 0x00}; // tuple length is 0
    OptionBuffer buf(buf_data, buf_data + sizeof(buf_data));

    OptionOpaqueDataTuplesPtr data_tuple;
    ASSERT_NO_THROW(
        data_tuple = OptionOpaqueDataTuplesPtr(new OptionOpaqueDataTuples(Option::V4,
                                                                          DHO_V4_SZTP_REDIRECT,
                                                                          buf.begin(),
                                                                          buf.end(),
                                                                          OpaqueDataTuple::LENGTH_2_BYTES));
    );
    EXPECT_EQ(DHO_V4_SZTP_REDIRECT, data_tuple->getType());
    ASSERT_EQ(1, data_tuple->getTuplesNum());
    EXPECT_TRUE(data_tuple->getTuple(0).getText().empty());
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
                                                                          D6O_BOOTFILE_PARAM,
                                                                          buf.begin(),
                                                                          buf.end()));
    );
    EXPECT_EQ(D6O_BOOTFILE_PARAM, data_tuple->getType());
    ASSERT_EQ(1, data_tuple->getTuplesNum());
    EXPECT_TRUE(data_tuple->getTuple(0).getText().empty());
}

// This test checks that exception is thrown when parsing truncated DHCPv4 option
TEST(OptionOpaqueDataTuples, unpack4Truncated) {
    // Prepare data to decode.
    const uint8_t buf_data[] = {
        0x0B,                               // tuple length is 11
        0x48, 0x65, 0x6C, 0x6C, 0x6F, 0x20, // Hello<space>
        0x77, 0x6F, 0x72, 0x6C              // worl (truncated d!)
    };
    OptionBuffer buf(buf_data, buf_data + sizeof(buf_data));

    EXPECT_THROW(OptionOpaqueDataTuples(Option::V4,
                                        DHO_VIVCO_SUBOPTIONS,
                                        buf.begin(),
                                        buf.end()),
                 isc::dhcp::OpaqueDataTupleError);
}

// This test checks that exception is thrown when parsing truncated DHCPv4 option,
// when tuple's length field is coded on 2 octets.
TEST(OptionOpaqueDataTuples, unpack4Truncated_with_ltf) {
    // Prepare data to decode.
    const uint8_t buf_data[] = {
        0x00, 0x0B,                         // tuple length is 11
        0x48, 0x65, 0x6C, 0x6C, 0x6F, 0x20, // Hello<space>
        0x77, 0x6F, 0x72, 0x6C              // worl (truncated d!)
    };
    OptionBuffer buf(buf_data, buf_data + sizeof(buf_data));

    EXPECT_THROW(OptionOpaqueDataTuples(Option::V4,
                                        DHO_V4_SZTP_REDIRECT,
                                        buf.begin(),
                                        buf.end(),
                                        OpaqueDataTuple::LENGTH_2_BYTES),
                 isc::dhcp::OpaqueDataTupleError);
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

    EXPECT_THROW(OptionOpaqueDataTuples(Option::V6,
                                        D6O_BOOTFILE_PARAM,
                                        buf.begin(),
                                        buf.end()),
                 isc::dhcp::OpaqueDataTupleError);
}

// This test checks that the DHCPv4 option containing no opaque
// data is parsed correctly.
TEST(OptionOpaqueDataTuples, unpack4NoTuple) {
    // Prepare data to decode.
    const uint8_t buf_data[] = {
    };
    OptionBuffer buf(buf_data, buf_data + sizeof(buf_data));

    OptionOpaqueDataTuplesPtr data_tuple;
    ASSERT_NO_THROW(
        data_tuple = OptionOpaqueDataTuplesPtr(new OptionOpaqueDataTuples(Option::V4,
                                                                          DHO_VIVCO_SUBOPTIONS,
                                                                          buf.begin(),
                                                                          buf.end()));
    );
    EXPECT_EQ(DHO_VIVCO_SUBOPTIONS, data_tuple->getType());
    EXPECT_EQ(0, data_tuple->getTuplesNum());
}

// This test checks that the DHCPv4 option containing no opaque
// data is parsed correctly when tuple's length field is coded on 2 octets.
TEST(OptionOpaqueDataTuples, unpack4NoTuple_with_ltf) {
    // Prepare data to decode.
    const uint8_t buf_data[] = {
    };
    OptionBuffer buf(buf_data, buf_data + sizeof(buf_data));

    OptionOpaqueDataTuplesPtr data_tuple;
    ASSERT_NO_THROW(
        data_tuple = OptionOpaqueDataTuplesPtr(new OptionOpaqueDataTuples(Option::V4,
                                                                          DHO_V4_SZTP_REDIRECT,
                                                                          buf.begin(),
                                                                          buf.end(),
                                                                          OpaqueDataTuple::LENGTH_2_BYTES));
    );
    EXPECT_EQ(DHO_V4_SZTP_REDIRECT, data_tuple->getType());
    EXPECT_EQ(0, data_tuple->getTuplesNum());
}

// This test checks that the DHCPv6 bootfile-param option containing no opaque
// data is parsed correctly.
TEST(OptionOpaqueDataTuples, unpack6NoTuple) {
    // Prepare data to decode.
    const uint8_t buf_data[] = {
    };
    OptionBuffer buf(buf_data, buf_data + sizeof(buf_data));

    OptionOpaqueDataTuplesPtr data_tuple;
    ASSERT_NO_THROW(
        data_tuple = OptionOpaqueDataTuplesPtr(new OptionOpaqueDataTuples(Option::V6,
                                                                          D6O_BOOTFILE_PARAM,
                                                                          buf.begin(),
                                                                          buf.end()));
    );
    EXPECT_EQ(D6O_BOOTFILE_PARAM, data_tuple->getType());
    EXPECT_EQ(0, data_tuple->getTuplesNum());
}

// Verifies correctness of the text representation of the DHCPv4 option.
TEST(OptionOpaqueDataTuples, toText4) {
    OptionOpaqueDataTuples data_tuple(Option::V4, DHO_VIVCO_SUBOPTIONS);
    ASSERT_EQ(0, data_tuple.getTuplesNum());
    // Lets add a tuple
    OpaqueDataTuple tuple(OpaqueDataTuple::LENGTH_1_BYTE);
    tuple = "Hello world";
    data_tuple.addTuple(tuple);
    // And add another tuple so as resulting option is a bit more complex.
    tuple = "foo";
    data_tuple.addTuple(tuple);
    // Check that the text representation of the option is as expected.
    EXPECT_EQ("type=124, len=16,"
              " data-len0=11, data0='Hello world',"
              " data-len1=3, data1='foo'",
              data_tuple.toText());

    // Check that indentation works.
    EXPECT_EQ("  type=124, len=16,"
              " data-len0=11, data0='Hello world',"
              " data-len1=3, data1='foo'",
              data_tuple.toText(2));
}

// Verifies correctness of the text representation of the DHCPv4 option when
// tuple's length field is coded on 2 octets.
TEST(OptionOpaqueDataTuples, toText4_with_ltf) {
    OptionOpaqueDataTuples data_tuple(Option::V4, DHO_V4_SZTP_REDIRECT, OpaqueDataTuple::LENGTH_2_BYTES);
    ASSERT_EQ(0, data_tuple.getTuplesNum());
    // Lets add a tuple
    OpaqueDataTuple tuple(OpaqueDataTuple::LENGTH_2_BYTES);
    tuple = "Hello world";
    data_tuple.addTuple(tuple);
    // And add another tuple so as resulting option is a bit more complex.
    tuple = "foo";
    data_tuple.addTuple(tuple);
    // Check that the text representation of the option is as expected.
    EXPECT_EQ("type=143, len=18,"
              " data-len0=11, data0='Hello world',"
              " data-len1=3, data1='foo'",
              data_tuple.toText());

    // Check that indentation works.
    EXPECT_EQ("  type=143, len=18,"
              " data-len0=11, data0='Hello world',"
              " data-len1=3, data1='foo'",
              data_tuple.toText(2));
}

// Verifies correctness of the text representation of the DHCPv6 option.
TEST(OptionOpaqueDataTuples, toText6) {
    OptionOpaqueDataTuples data_tuple(Option::V6, D6O_BOOTFILE_PARAM);
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
