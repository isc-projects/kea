// Copyright (C) 2014-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <exceptions/exceptions.h>
#include <dhcp/option_vendor_class.h>
#include <util/buffer.h>
#include <gtest/gtest.h>

using namespace isc;
using namespace isc::dhcp;
using namespace isc::util;

namespace {

// This test checks that the DHCPv4 option constructor sets the default
// properties to the expected values. This constructor should add an
// empty opaque data tuple (it is essentially the same as adding a 1-byte
// long field which carries a value of 0).
TEST(OptionVendorClass, constructor4) {
    OptionVendorClass vendor_class(Option::V4, 1234);
    EXPECT_EQ(1234, vendor_class.getVendorId());
    // Option length is 1 byte for header + 1 byte for option size +
    // 4 bytes of enterprise id + 1 byte for opaque data.
    EXPECT_EQ(7, vendor_class.len());
    // There should be one empty tuple.
    ASSERT_EQ(1, vendor_class.getTuplesNum());
    EXPECT_EQ(0, vendor_class.getTuple(0).getLength());
}

// This test checks that the DHCPv6 option constructor sets the default
// properties to the expected values.
TEST(OptionVendorClass, constructor6) {
    OptionVendorClass vendor_class(Option::V6, 2345);
    EXPECT_EQ(2345, vendor_class.getVendorId());
    // Option length is 2 bytes for option code + 2 bytes for option size +
    // 4 bytes of enterprise id.
    EXPECT_EQ(8, vendor_class.len());
    // There should be no tuples.
    EXPECT_EQ(0, vendor_class.getTuplesNum());
}

// This test verifies that it is possible to append the opaque data tuple
// to the option and then retrieve it.
TEST(OptionVendorClass, addTuple) {
    OptionVendorClass vendor_class(Option::V6, 2345);
    // Initially there should be no tuples (for DHCPv6).
    ASSERT_EQ(0, vendor_class.getTuplesNum());
    // Create a new tuple and add it to the option.
    OpaqueDataTuple tuple(OpaqueDataTuple::LENGTH_2_BYTES);
    tuple = "xyz";
    vendor_class.addTuple(tuple);
    // The option should now hold one tuple.
    ASSERT_EQ(1, vendor_class.getTuplesNum());
    EXPECT_EQ("xyz", vendor_class.getTuple(0).getText());
    // Add another tuple.
    tuple = "abc";
    vendor_class.addTuple(tuple);
    // The option should now hold exactly two tuples in the order in which
    // they were added.
    ASSERT_EQ(2, vendor_class.getTuplesNum());
    EXPECT_EQ("xyz", vendor_class.getTuple(0).getText());
    EXPECT_EQ("abc", vendor_class.getTuple(1).getText());

    // Check that hasTuple correctly identifies existing tuples.
    EXPECT_TRUE(vendor_class.hasTuple("xyz"));
    EXPECT_TRUE(vendor_class.hasTuple("abc"));
    EXPECT_FALSE(vendor_class.hasTuple("other"));

    // Attempt to add the tuple with 1 byte long length field should fail
    // for DHCPv6 option.
    OpaqueDataTuple tuple2(OpaqueDataTuple::LENGTH_1_BYTE);
    EXPECT_THROW(vendor_class.addTuple(tuple2), isc::BadValue);
}

// This test checks that it is possible to replace existing tuple.
TEST(OptionVendorClass, setTuple) {
    OptionVendorClass vendor_class(Option::V4, 1234);
    // The DHCPv4 option should carry one empty tuple.
    ASSERT_EQ(1, vendor_class.getTuplesNum());
    ASSERT_TRUE(vendor_class.getTuple(0).getText().empty());
    // Replace the empty tuple with non-empty one.
    OpaqueDataTuple tuple(OpaqueDataTuple::LENGTH_1_BYTE);
    tuple = "xyz";
    ASSERT_NO_THROW(vendor_class.setTuple(0, tuple));
    // There should be one tuple with updated data.
    ASSERT_EQ(1, vendor_class.getTuplesNum());
    EXPECT_EQ("xyz", vendor_class.getTuple(0).getText());

    // Add another one.
    tuple = "abc";
    vendor_class.addTuple(tuple);
    ASSERT_EQ(2, vendor_class.getTuplesNum());
    ASSERT_EQ("abc", vendor_class.getTuple(1).getText());

    // Try to replace them with new tuples.
    tuple = "new_xyz";
    ASSERT_NO_THROW(vendor_class.setTuple(0, tuple));
    ASSERT_EQ(2, vendor_class.getTuplesNum());
    EXPECT_EQ("new_xyz", vendor_class.getTuple(0).getText());

    tuple = "new_abc";
    ASSERT_NO_THROW(vendor_class.setTuple(1, tuple));
    ASSERT_EQ(2, vendor_class.getTuplesNum());
    EXPECT_EQ("new_abc", vendor_class.getTuple(1).getText());

    // For out of range position, exception should be thrown.
    tuple = "foo";
    EXPECT_THROW(vendor_class.setTuple(2, tuple), isc::OutOfRange);

    // Attempt to add the tuple with 2 byte long length field should fail
    // for DHCPv4 option.
    OpaqueDataTuple tuple2(OpaqueDataTuple::LENGTH_2_BYTES);
    EXPECT_THROW(vendor_class.addTuple(tuple2), isc::BadValue);
}

// Check that the returned length of the DHCPv4 option is correct.
TEST(OptionVendorClass, len4) {
    OptionVendorClass vendor_class(Option::V4, 1234);
    ASSERT_EQ(7, vendor_class.len());
    // Replace the default empty tuple.
    OpaqueDataTuple tuple(OpaqueDataTuple::LENGTH_1_BYTE);
    tuple = "xyz";
    ASSERT_NO_THROW(vendor_class.setTuple(0, tuple));
    // The total length should get increased by the size of 'xyz'.
    EXPECT_EQ(10, vendor_class.len());
    // Add another tuple.
    tuple = "abc";
    vendor_class.addTuple(tuple);
    // The total size now grows by the additional enterprise id and the
    // 1 byte of the tuple length field and 3 bytes of 'abc'.
    EXPECT_EQ(18, vendor_class.len());
}

// Check that the returned length of the DHCPv6 option is correct.
TEST(OptionVendorClass, len6) {
    OptionVendorClass vendor_class(Option::V6, 1234);
    ASSERT_EQ(8, vendor_class.len());
    // Add first tuple.
    OpaqueDataTuple tuple(OpaqueDataTuple::LENGTH_2_BYTES);
    tuple = "xyz";
    ASSERT_NO_THROW(vendor_class.addTuple(tuple));
    // The total length grows by 2 bytes of the length field and 3 bytes
    // consumed by 'xyz'.
    EXPECT_EQ(13, vendor_class.len());
    // Add another tuple and check that the total size gets increased.
    tuple = "abc";
    vendor_class.addTuple(tuple);
    EXPECT_EQ(18, vendor_class.len());
}

// Check that the option is rendered to the buffer in wire format.
TEST(OptionVendorClass, pack4) {
    OptionVendorClass vendor_class(Option::V4, 1234);
    ASSERT_EQ(1, vendor_class.getTuplesNum());
    // By default, there is an empty tuple in the option. Let's replace
    // it with the tuple with some data.
    OpaqueDataTuple tuple(OpaqueDataTuple::LENGTH_1_BYTE);
    tuple = "Hello world";
    vendor_class.setTuple(0, tuple);
    // And add another tuple so as resulting option is a bit more complex.
    tuple = "foo";
    vendor_class.addTuple(tuple);

    // Render the data to the buffer.
    OutputBuffer buf(10);
    ASSERT_NO_THROW(vendor_class.pack(buf));
    ASSERT_EQ(26, buf.getLength());

    // Prepare reference data.
    const uint8_t ref[] = {
        0x7C, 0x18,                         // option 124, length 24
        0, 0, 0x4, 0xD2,                    // enterprise id 1234
        0x0B,                               // tuple length is 11
        0x48, 0x65, 0x6C, 0x6C, 0x6F, 0x20, // Hello<space>
        0x77, 0x6F, 0x72, 0x6C, 0x64,       // world
        0, 0, 0x4, 0xD2,                    // enterprise id 1234
        3,                                  // tuple length is 3
        0x66, 0x6F, 0x6F                    // foo
    };
    // Compare the buffer with reference data.
    EXPECT_EQ(0, memcmp(static_cast<const void*>(ref),
                        static_cast<const void*>(buf.getData()), 26));
}

// Check that the DHCPv6 option is rendered to the buffer in wire format.
TEST(OptionVendorClass, pack6) {
    OptionVendorClass vendor_class(Option::V6, 1234);
    ASSERT_EQ(0, vendor_class.getTuplesNum());
    // Add tuple.
    OpaqueDataTuple tuple(OpaqueDataTuple::LENGTH_2_BYTES);
    tuple = "Hello world";
    vendor_class.addTuple(tuple);
    // And add another tuple so as resulting option is a bit more complex.
    tuple = "foo";
    vendor_class.addTuple(tuple);

    // Render the data to the buffer.
    OutputBuffer buf(10);
    ASSERT_NO_THROW(vendor_class.pack(buf));
    ASSERT_EQ(26, buf.getLength());

    // Prepare reference data.
    const uint8_t ref[] = {
        0x00, 0x10, 0x00, 0x16,             // option 16, length 22
        0x00, 0x00, 0x04, 0xD2,             // enterprise id 1234
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
TEST(OptionVendorClass, unpack4) {
    // Prepare data to decode.
    const uint8_t buf_data[] = {
        0, 0, 0x4, 0xD2,                    // enterprise id 1234
        0x0B,                               // tuple length is 11
        0x48, 0x65, 0x6C, 0x6C, 0x6F, 0x20, // Hello<space>
        0x77, 0x6F, 0x72, 0x6C, 0x64,       // world
        0, 0, 0x4, 0xD2,                    // enterprise id 1234
        3,                                  // tuple length is 3
        0x66, 0x6F, 0x6F                    // foo
    };
    OptionBuffer buf(buf_data, buf_data + sizeof(buf_data));

    OptionVendorClassPtr vendor_class;
    ASSERT_NO_THROW(
        vendor_class = OptionVendorClassPtr(new OptionVendorClass(Option::V4,
                                                                  buf.begin(),
                                                                  buf.end()));
    );
    EXPECT_EQ(DHO_VIVCO_SUBOPTIONS, vendor_class->getType());
    EXPECT_EQ(1234, vendor_class->getVendorId());
    ASSERT_EQ(2, vendor_class->getTuplesNum());
    EXPECT_EQ("Hello world", vendor_class->getTuple(0).getText());
    EXPECT_EQ("foo", vendor_class->getTuple(1).getText());
}

// This function checks that the DHCPv4 option with two opaque data tuples
// is parsed correctly.
TEST(OptionVendorClass, unpack6) {
    // Prepare data to decode.
    const uint8_t buf_data[] = {
        0, 0, 0x4, 0xD2,                    // enterprise id 1234
        0x00, 0x0B,                         // tuple length is 11
        0x48, 0x65, 0x6C, 0x6C, 0x6F, 0x20, // Hello<space>
        0x77, 0x6F, 0x72, 0x6C, 0x64,       // world
        0x00, 0x03,                         // tuple length is 3
        0x66, 0x6F, 0x6F                    // foo
    };
    OptionBuffer buf(buf_data, buf_data + sizeof(buf_data));

    OptionVendorClassPtr vendor_class;
    ASSERT_NO_THROW(
        vendor_class = OptionVendorClassPtr(new OptionVendorClass(Option::V6,
                                                                  buf.begin(),
                                                                  buf.end()));
    );
    EXPECT_EQ(D6O_VENDOR_CLASS, vendor_class->getType());
    EXPECT_EQ(1234, vendor_class->getVendorId());
    ASSERT_EQ(2, vendor_class->getTuplesNum());
    EXPECT_EQ("Hello world", vendor_class->getTuple(0).getText());
    EXPECT_EQ("foo", vendor_class->getTuple(1).getText());
}


// This test checks that the DHCPv4 option with opaque data of size 0
// is correctly parsed.
TEST(OptionVendorClass, unpack4EmptyTuple) {
    // Prepare data to decode.
    const uint8_t buf_data[] = {
        0, 0, 0x4, 0xD2,                    // enterprise id 1234
        0x00,                               // tuple length is 0
    };
    OptionBuffer buf(buf_data, buf_data + sizeof(buf_data));

    OptionVendorClassPtr vendor_class;
    ASSERT_NO_THROW(
        vendor_class = OptionVendorClassPtr(new OptionVendorClass(Option::V4,
                                                                  buf.begin(),
                                                                  buf.end()));
    );
    EXPECT_EQ(DHO_VIVCO_SUBOPTIONS, vendor_class->getType());
    EXPECT_EQ(1234, vendor_class->getVendorId());
    ASSERT_EQ(1, vendor_class->getTuplesNum());
    EXPECT_TRUE(vendor_class->getTuple(0).getText().empty());
}

// This test checks that the DHCPv6 option with opaque data of size 0
// is correctly parsed.
TEST(OptionVendorClass, unpack6EmptyTuple) {
    // Prepare data to decode.
    const uint8_t buf_data[] = {
        0, 0, 0x4, 0xD2,  // enterprise id 1234
        0x00, 0x00        // tuple length is 0
    };
    OptionBuffer buf(buf_data, buf_data + sizeof(buf_data));

    OptionVendorClassPtr vendor_class;
    ASSERT_NO_THROW(
        vendor_class = OptionVendorClassPtr(new OptionVendorClass(Option::V6,
                                                                  buf.begin(),
                                                                  buf.end()));
    );
    EXPECT_EQ(D6O_VENDOR_CLASS, vendor_class->getType());
    EXPECT_EQ(1234, vendor_class->getVendorId());
    ASSERT_EQ(1, vendor_class->getTuplesNum());
    EXPECT_TRUE(vendor_class->getTuple(0).getText().empty());
}

// This test checks that exception is thrown when parsing truncated DHCPv4
// V-I Vendor Class option.
TEST(OptionVendorClass, unpack4Truncated) {
    // Prepare data to decode.
    const uint8_t buf_data[] = {
        0, 0, 0x4, 0xD2,                    // enterprise id 1234
        0x0B,                               // tuple length is 11
        0x48, 0x65, 0x6C, 0x6C, 0x6F, 0x20, // Hello<space>
        0x77, 0x6F, 0x72, 0x6C, 0x64,       // world
        0, 0, 0x4, 0xD2,                    // enterprise id 1234
    };
    OptionBuffer buf(buf_data, buf_data + sizeof(buf_data));

    EXPECT_THROW(OptionVendorClass (Option::V4, buf.begin(), buf.end()),
                 isc::OutOfRange);
}

// This test checks that exception is thrown when parsing truncated DHCPv6
// Vendor Class option.
TEST(OptionVendorClass, unpack6Truncated) {
    // Prepare data to decode.
    const uint8_t buf_data[] = {
        0, 0, 0x4, 0xD2,                    // enterprise id 1234
        0x00, 0x0B,                         // tuple length is 11
        0x48, 0x65, 0x6C, 0x6C, 0x6F, 0x20, // Hello<space>
        0x77, 0x6F, 0x72, 0x6C              // worl (truncated d!)
    };
    OptionBuffer buf(buf_data, buf_data + sizeof(buf_data));

    EXPECT_THROW(OptionVendorClass (Option::V6, buf.begin(), buf.end()),
                 isc::dhcp::OpaqueDataTupleError);
}

// This test checks that exception is thrown when parsing DHCPv4 V-I Vendor
// Class option which doesn't have opaque data length. This test is different
// from the corresponding test for v6 in that, the v4 test expects that
// exception is thrown when parsing DHCPv4 option without data-len field
// (has no tuples), whereas for DHCPv6 option it is perfectly ok that
// option has no tuples (see class constructor).
TEST(OptionVendorClass, unpack4NoTuple) {
    // Prepare data to decode.
    const uint8_t buf_data[] = {
        0, 0, 0x4, 0xD2  // enterprise id 1234
    };
    OptionBuffer buf(buf_data, buf_data + sizeof(buf_data));

    ASSERT_THROW(OptionVendorClass (Option::V4, buf.begin(), buf.end()),
                 isc::OutOfRange);
}

// This test checks that the DHCPv6 Vendor Class option containing no opaque
// data is parsed correctly. This test is different from the corresponding
// test for v4 in that, the v6 test checks that the option parsing succeeds
// when option has no opaque data tuples, whereas the v4 test expects that
// parsing fails for DHCPv4 option which doesn't have opaque-data (see
// class constructor).
TEST(OptionVendorClass, unpack6NoTuple) {
    // Prepare data to decode.
    const uint8_t buf_data[] = {
        0, 0, 0x4, 0xD2  // enterprise id 1234
    };
    OptionBuffer buf(buf_data, buf_data + sizeof(buf_data));

    OptionVendorClassPtr vendor_class;
    ASSERT_NO_THROW(
        vendor_class = OptionVendorClassPtr(new OptionVendorClass(Option::V6,
                                                                  buf.begin(),
                                                                  buf.end()));
    );
    EXPECT_EQ(D6O_VENDOR_CLASS, vendor_class->getType());
    EXPECT_EQ(1234, vendor_class->getVendorId());
    EXPECT_EQ(0, vendor_class->getTuplesNum());
}

// Verifies correctness of the text representation of the DHCPv4 option.
TEST(OptionVendorClass, toText4) {
    OptionVendorClass vendor_class(Option::V4, 1234);
    ASSERT_EQ(1, vendor_class.getTuplesNum());
    // By default, there is an empty tuple in the option. Let's replace
    // it with the tuple with some data.
    OpaqueDataTuple tuple(OpaqueDataTuple::LENGTH_1_BYTE);
    tuple = "Hello world";
    vendor_class.setTuple(0, tuple);
    // And add another tuple so as resulting option is a bit more complex.
    tuple = "foo";
    vendor_class.addTuple(tuple);
    // Check that the text representation of the option is as expected.
    EXPECT_EQ("type=124, len=24,  enterprise id=0x4d2,"
              " data-len0=11, vendor-class-data0='Hello world',"
              " enterprise id=0x4d2, data-len1=3, vendor-class-data1='foo'",
              vendor_class.toText());

    // Check that indentation works.
    EXPECT_EQ("   type=124, len=24,  enterprise id=0x4d2,"
              " data-len0=11, vendor-class-data0='Hello world',"
              " enterprise id=0x4d2, data-len1=3, vendor-class-data1='foo'",
              vendor_class.toText(3));
}

// Verifies correctness of the text representation of the DHCPv4 option.
TEST(OptionVendorClass, toText6) {
    OptionVendorClass vendor_class(Option::V6, 1234);
    ASSERT_EQ(0, vendor_class.getTuplesNum());
    // By default, there is an empty tuple in the option. Let's replace
    // it with the tuple with some data.
    OpaqueDataTuple tuple(OpaqueDataTuple::LENGTH_2_BYTES);
    tuple = "Hello world";
    vendor_class.addTuple(tuple);
    // And add another tuple so as resulting option is a bit more complex.
    tuple = "foo";
    vendor_class.addTuple(tuple);
    // Check that the text representation of the option is as expected.
    EXPECT_EQ("type=16, len=22,  enterprise id=0x4d2,"
              " data-len0=11, vendor-class-data0='Hello world',"
              " data-len1=3, vendor-class-data1='foo'",
              vendor_class.toText());

    // Check that indentation works.
    EXPECT_EQ("  type=16, len=22,  enterprise id=0x4d2,"
              " data-len0=11, vendor-class-data0='Hello world',"
              " data-len1=3, vendor-class-data1='foo'",
              vendor_class.toText(2));
}

} // end of anonymous namespace

