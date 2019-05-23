// Copyright (C) 2012-2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <dhcp/option_data_types.h>
#include <gtest/gtest.h>
#include <utility>

using namespace isc;
using namespace isc::asiolink;
using namespace isc::dhcp;

namespace {

/// @brief Default (zero) prefix tuple.
const PrefixTuple
ZERO_PREFIX_TUPLE(std::make_pair(PrefixLen(0),
                                 IOAddress(IOAddress::IPV6_ZERO_ADDRESS())));

/// @brief Test class for option data type utilities.
class OptionDataTypesTest : public ::testing::Test {
public:

    /// @brief Constructor.
    OptionDataTypesTest() { }

    /// @brief Write IP address into a buffer.
    ///
    /// @param address address to be written.
    /// @param [out] buf output buffer.
    void writeAddress(const asiolink::IOAddress& address,
                      std::vector<uint8_t>& buf) {
        const std::vector<uint8_t>& vec = address.toBytes();
        buf.insert(buf.end(), vec.begin(), vec.end());
    }

    /// @brief Write integer (signed or unsigned) into a buffer.
    ///
    /// @param value integer value.
    /// @param [out] buf output buffer.
    /// @tparam integer type.
    template<typename T>
    void writeInt(T value, std::vector<uint8_t>& buf) {
        switch (sizeof(T)) {
        case 4:
            buf.push_back((value >> 24) & 0xFF);
            /* falls through */
        case 3:
            buf.push_back((value >> 16) & 0xFF);
            /* falls through */
        case 2:
            buf.push_back((value >> 8) & 0xFF);
            /* falls through */
        case 1:
            buf.push_back(value & 0xFF);
            break;
        default:
            // This loop is incorrectly compiled by some old g++?!
            for (int i = 0; i < sizeof(T); ++i) {
                buf.push_back(value >> ((sizeof(T) - i - 1) * 8) & 0xFF);
            }
        }
    }

    /// @brief Write a string into a buffer.
    ///
    /// @param value string to be written into a buffer.
    /// @param buf output buffer.
    void writeString(const std::string& value,
                     std::vector<uint8_t>& buf) {
        buf.resize(buf.size() + value.size());
        std::copy_backward(value.c_str(), value.c_str() + value.size(),
                           buf.end());
    }
};

// The goal of this test is to verify that the getLabelCount returns the
// correct number of labels in the domain name specified as a string
// parameter.
TEST_F(OptionDataTypesTest, getLabelCount) {
    EXPECT_EQ(0, OptionDataTypeUtil::getLabelCount(""));
    EXPECT_EQ(1, OptionDataTypeUtil::getLabelCount("."));
    EXPECT_EQ(2, OptionDataTypeUtil::getLabelCount("example"));
    EXPECT_EQ(3, OptionDataTypeUtil::getLabelCount("example.com"));
    EXPECT_EQ(3, OptionDataTypeUtil::getLabelCount("example.com."));
    EXPECT_EQ(4, OptionDataTypeUtil::getLabelCount("myhost.example.com"));
    EXPECT_THROW(OptionDataTypeUtil::getLabelCount(".abc."),
                 isc::dhcp::BadDataTypeCast);
}

// The goal of this test is to verify that an IPv4 address being
// stored in a buffer (wire format) can be read into IOAddress
// object.
TEST_F(OptionDataTypesTest, readAddress) {
    // Create some IPv4 address.
    asiolink::IOAddress address("192.168.0.1");
    // And store it in a buffer in a wire format.
    std::vector<uint8_t> buf;
    writeAddress(address, buf);

    // Now, try to read the IP address with a utility function
    // being under test.
    asiolink::IOAddress address_out("127.0.0.1");
    EXPECT_NO_THROW(address_out = OptionDataTypeUtil::readAddress(buf, AF_INET));

    // Check that the read address matches address that
    // we used as input.
    EXPECT_EQ(address, address_out);

    // Check that an attempt to read the buffer as IPv6 address
    // causes an error as the IPv6 address needs at least 16 bytes
    // long buffer.
    EXPECT_THROW(
        OptionDataTypeUtil::readAddress(buf, AF_INET6),
        isc::dhcp::BadDataTypeCast
    );

    buf.clear();

    // Do another test like this for IPv6 address.
    address = asiolink::IOAddress("2001:db8:1:0::1");
    writeAddress(address, buf);
    EXPECT_NO_THROW(address_out = OptionDataTypeUtil::readAddress(buf, AF_INET6));
    EXPECT_EQ(address, address_out);

    // Truncate the buffer and expect an error to be reported when
    // trying to read it.
    buf.resize(buf.size() - 1);
    EXPECT_THROW(
        OptionDataTypeUtil::readAddress(buf, AF_INET6),
        isc::dhcp::BadDataTypeCast
    );
}

// The goal of this test is to verify that an IPv6 address
// is properly converted to wire format and stored in a
// buffer.
TEST_F(OptionDataTypesTest, writeAddress) {
    // Encode an IPv6 address 2001:db8:1::1 in wire format.
    // This will be used as reference data to validate if
    // an IPv6 address is stored in a buffer properly.
    const uint8_t data[] = {
        0x20, 0x01, 0x0d, 0xb8, 0x0, 0x1, 0x0, 0x0,
        0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x1
    };
    std::vector<uint8_t> buf_in(data, data + sizeof(data));

    // Create IPv6 address object.
    asiolink::IOAddress address("2001:db8:1::1");
    // Define the output buffer to write IP address to.
    std::vector<uint8_t> buf_out;
    // Write the address to the buffer.
    ASSERT_NO_THROW(OptionDataTypeUtil::writeAddress(address, buf_out));
    // Make sure that input and output buffers have the same size
    // so we can compare them.
    ASSERT_EQ(buf_in.size(), buf_out.size());
    // And finally compare them.
    EXPECT_TRUE(std::equal(buf_in.begin(), buf_in.end(), buf_out.begin()));

    buf_out.clear();

    // Do similar test for IPv4 address.
    address = asiolink::IOAddress("192.168.0.1");
    ASSERT_NO_THROW(OptionDataTypeUtil::writeAddress(address, buf_out));
    ASSERT_EQ(4, buf_out.size());
    // Verify that the IP address has been written correctly.
    EXPECT_EQ(192, buf_out[0]);
    EXPECT_EQ(168, buf_out[1]);
    EXPECT_EQ(0, buf_out[2]);
    EXPECT_EQ(1, buf_out[3]);
}

// The purpose of this test is to verify that binary data represented
// as a string of hexadecimal digits can be written to a buffer.
TEST_F(OptionDataTypesTest, writeBinary) {
    // Prepare the reference data.
    const char data[] = {
        0x0, 0x1, 0x2, 0x3, 0x4, 0x5,
        0x6, 0x7, 0x8, 0x9, 0xA, 0xB
    };
    std::vector<uint8_t> buf_ref(data, data + sizeof(data));
    // Create empty vector where binary data will be written to.
    std::vector<uint8_t> buf;
    ASSERT_NO_THROW(
        OptionDataTypeUtil::writeBinary("000102030405060708090A0B", buf)
    );
    // Verify that the buffer contains valid data.
    ASSERT_EQ(buf_ref.size(), buf.size());
    EXPECT_TRUE(std::equal(buf_ref.begin(), buf_ref.end(), buf.begin()));
}

// The purpose of this test is to verify that the tuple value stored
TEST_F(OptionDataTypesTest, readTuple) {
    // The string
    std::string value = "hello world";
    // Create an input buffer.
    std::vector<uint8_t> buf;
    // DHCPv4 tuples use 1 byte length
    writeInt<uint8_t>(static_cast<uint8_t>(value.size()), buf);
    writeString(value, buf);

    // Read the string from the buffer.
    std::string result;
    ASSERT_NO_THROW(
        result = OptionDataTypeUtil::readTuple(buf, OpaqueDataTuple::LENGTH_1_BYTE);
    );
    // Check that it is valid.
    EXPECT_EQ(value, result);

    // Read the tuple from the buffer.
    OpaqueDataTuple tuple4(OpaqueDataTuple::LENGTH_1_BYTE);
    ASSERT_NO_THROW(OptionDataTypeUtil::readTuple(buf, tuple4));
    // Check that it is valid.
    EXPECT_EQ(value, tuple4.getText());

    buf.clear();

    // DHCPv6 tuples use 2 byte length
    writeInt<uint16_t>(static_cast<uint16_t>(value.size()), buf);
    writeString(value, buf);

    // Read the string from the buffer.
    ASSERT_NO_THROW(
        result = OptionDataTypeUtil::readTuple(buf, OpaqueDataTuple::LENGTH_2_BYTES);
    );
    // Check that it is valid.
    EXPECT_EQ(value, result);

    // Read the tuple from the buffer.
    OpaqueDataTuple tuple6(OpaqueDataTuple::LENGTH_2_BYTES);
    ASSERT_NO_THROW(OptionDataTypeUtil::readTuple(buf, tuple6));
    // Check that it is valid.
    EXPECT_EQ(value, tuple6.getText());
}

// The purpose of this test is to verify that a tuple value
// are correctly encoded in a buffer (string version)
TEST_F(OptionDataTypesTest, writeTupleString) {
    // The string
    std::string value = "hello world";
    // Create an output buffer.
    std::vector<uint8_t> buf;

    // Encode it in DHCPv4
    OptionDataTypeUtil::writeTuple(value, OpaqueDataTuple::LENGTH_1_BYTE, buf);

    // Check that it is valid.
    ASSERT_EQ(value.size() + 1, buf.size());
    std::vector<uint8_t> expected;
    writeInt<uint8_t>(static_cast<uint8_t>(value.size()), expected);
    writeString(value, expected);
    EXPECT_EQ(0, std::memcmp(&buf[0], &expected[0], buf.size()));

    buf.clear();

    // Encode it in DHCPv6
    OptionDataTypeUtil::writeTuple(value, OpaqueDataTuple::LENGTH_2_BYTES, buf);

    // Check that it is valid.
    ASSERT_EQ(value.size() + 2, buf.size());
    expected.clear();
    writeInt<uint16_t>(static_cast<uint16_t>(value.size()), expected);
    writeString(value, expected);
    EXPECT_EQ(0, std::memcmp(&buf[0], &expected[0], buf.size()));
}

// The purpose of this test is to verify that a tuple value
// are correctly encoded in a buffer (tuple version)
TEST_F(OptionDataTypesTest, writeTuple) {
    // The string
    std::string value = "hello world";
    // Create a DHCPv4 tuple
    OpaqueDataTuple tuple4(OpaqueDataTuple::LENGTH_1_BYTE);
    tuple4.append(value);
    // Create an output buffer.
    std::vector<uint8_t> buf;

    // Encode it in DHCPv4
    OptionDataTypeUtil::writeTuple(tuple4, buf);

    // Check that it is valid.
    ASSERT_EQ(value.size() + 1, buf.size());
    std::vector<uint8_t> expected;
    writeInt<uint8_t>(static_cast<uint8_t>(value.size()), expected);
    writeString(value, expected);
    EXPECT_EQ(0, std::memcmp(&buf[0], &expected[0], buf.size()));

    buf.clear();

    // Create a DHCPv6 tuple
    OpaqueDataTuple tuple6(OpaqueDataTuple::LENGTH_2_BYTES);
    tuple6.append(value);

    // Encode it in DHCPv6
    OptionDataTypeUtil::writeTuple(tuple6, buf);

    // Check that it is valid.
    ASSERT_EQ(value.size() + 2, buf.size());
    expected.clear();
    writeInt<uint16_t>(static_cast<uint16_t>(value.size()), expected);
    writeString(value, expected);
    EXPECT_EQ(0, std::memcmp(&buf[0], &expected[0], buf.size()));
}

// The purpose of this test is to verify that the boolean value stored
// in a buffer is correctly read from this buffer.
TEST_F(OptionDataTypesTest, readBool) {
    // Create an input buffer.
    std::vector<uint8_t> buf;
    // 'true' value is encoded as 1 ('false' is encoded as 0)
    buf.push_back(1);

    // Read the value from the buffer.
    bool value = false;
    ASSERT_NO_THROW(
        value = OptionDataTypeUtil::readBool(buf);
    );
    // Verify the value.
    EXPECT_TRUE(value);
    // Check if 'false' is read correctly either.
    buf[0] = 0;
    ASSERT_NO_THROW(
        value = OptionDataTypeUtil::readBool(buf);
    );
    EXPECT_FALSE(value);

    // Check that invalid value causes exception.
    buf[0] = 5;
    ASSERT_THROW(
        OptionDataTypeUtil::readBool(buf),
        isc::dhcp::BadDataTypeCast
    );
}

// The purpose of this test is to verify that boolean values
// are correctly encoded in a buffer as '1' for 'true' and
// '0' for 'false' values.
TEST_F(OptionDataTypesTest, writeBool) {
    // Create a buffer we will write to.
    std::vector<uint8_t> buf;
    // Write the 'true' value to the buffer.
    ASSERT_NO_THROW(OptionDataTypeUtil::writeBool(true, buf));
    // We should now have 'true' value stored in a buffer.
    ASSERT_EQ(1, buf.size());
    EXPECT_EQ(buf[0], 1);
    // Let's append another value to make sure that it is not always
    // 'true' value being written.
    ASSERT_NO_THROW(OptionDataTypeUtil::writeBool(false, buf));
    ASSERT_EQ(2, buf.size());
    // Check that the first value has not changed.
    EXPECT_EQ(buf[0], 1);
    // Check the the second value is correct.
    EXPECT_EQ(buf[1], 0);
}

// The purpose of this test is to verify that the integer values
// of different types are correctly read from a buffer.
TEST_F(OptionDataTypesTest, readInt) {
    std::vector<uint8_t> buf;

    // Write an 8-bit unsigned integer value to the buffer.
    writeInt<uint8_t>(129, buf);
    uint8_t valueUint8 = 0;
    // Read the value and check that it is valid.
    ASSERT_NO_THROW(
        valueUint8 = OptionDataTypeUtil::readInt<uint8_t>(buf);
    );
    EXPECT_EQ(129, valueUint8);

    // Try to read 16-bit value from a buffer holding 8-bit value.
    // This should result in an exception.
    EXPECT_THROW(
        OptionDataTypeUtil::readInt<uint16_t>(buf),
        isc::dhcp::BadDataTypeCast
    );

    // Clear the buffer for the next check we are going to do.
    buf.clear();

    // Test uint16_t value.
    writeInt<uint16_t>(1234, buf);
    uint16_t valueUint16 = 0;
    ASSERT_NO_THROW(
        valueUint16 = OptionDataTypeUtil::readInt<uint16_t>(buf);
    );
    EXPECT_EQ(1234, valueUint16);

    // Try to read 32-bit value from a buffer holding 16-bit value.
    // This should result in an exception.
    EXPECT_THROW(
        OptionDataTypeUtil::readInt<uint32_t>(buf),
        isc::dhcp::BadDataTypeCast
    );

    buf.clear();

    // Test uint32_t value.
    writeInt<uint32_t>(56789, buf);
    uint32_t valueUint32 = 0;
    ASSERT_NO_THROW(
        valueUint32 = OptionDataTypeUtil::readInt<uint32_t>(buf);
    );
    EXPECT_EQ(56789, valueUint32);
    buf.clear();

    // Test int8_t value.
    writeInt<int8_t>(-65, buf);
    int8_t valueInt8 = 0;
    ASSERT_NO_THROW(
        valueInt8 = OptionDataTypeUtil::readInt<int8_t>(buf);
    );
    EXPECT_EQ(-65, valueInt8);
    buf.clear();

    // Try to read 16-bit value from a buffer holding 8-bit value.
    // This should result in an exception.
    EXPECT_THROW(
        OptionDataTypeUtil::readInt<int16_t>(buf),
        isc::dhcp::BadDataTypeCast
    );

    // Test int16_t value.
    writeInt<int16_t>(2345, buf);
    int32_t valueInt16 = 0;
    ASSERT_NO_THROW(
        valueInt16 = OptionDataTypeUtil::readInt<int16_t>(buf);
    );
    EXPECT_EQ(2345, valueInt16);
    buf.clear();

    // Try to read 32-bit value from a buffer holding 16-bit value.
    // This should result in an exception.
    EXPECT_THROW(
        OptionDataTypeUtil::readInt<int32_t>(buf),
        isc::dhcp::BadDataTypeCast
    );

    // Test int32_t value.
    writeInt<int32_t>(-16543, buf);
    int32_t valueInt32 = 0;
    ASSERT_NO_THROW(
        valueInt32 = OptionDataTypeUtil::readInt<int32_t>(buf);
    );
    EXPECT_EQ(-16543, valueInt32);

    buf.clear();
}

// The purpose of this test is to verify that integer values of different
// types are correctly written to a buffer.
TEST_F(OptionDataTypesTest, writeInt) {
    // Prepare the reference buffer.
    const uint8_t data[] = {
        0x7F, // 127
        0x03, 0xFF, // 1023
        0x00, 0x00, 0x10, 0x00, // 4096
        0xFF, 0xFF, 0xFC, 0x00, // -1024
        0x02, 0x00, // 512
        0x81 // -127
    };
    std::vector<uint8_t> buf_ref(data, data + sizeof(data));

    // Fill in the buffer with data. Each write operation appends an
    // integer value. Eventually the buffer holds all values and should
    // match with the reference buffer.
    std::vector<uint8_t> buf;
    ASSERT_NO_THROW(OptionDataTypeUtil::writeInt<uint8_t>(127, buf));
    ASSERT_NO_THROW(OptionDataTypeUtil::writeInt<uint16_t>(1023, buf));
    ASSERT_NO_THROW(OptionDataTypeUtil::writeInt<uint32_t>(4096, buf));
    ASSERT_NO_THROW(OptionDataTypeUtil::writeInt<int32_t>(-1024, buf));
    ASSERT_NO_THROW(OptionDataTypeUtil::writeInt<int16_t>(512, buf));
    ASSERT_NO_THROW(OptionDataTypeUtil::writeInt<int8_t>(-127, buf));

    // Make sure that the buffer has the same size as the reference
    // buffer.
    ASSERT_EQ(buf_ref.size(), buf.size());
    // Compare buffers.
    EXPECT_TRUE(std::equal(buf_ref.begin(), buf_ref.end(), buf.begin()));
}

// The purpose of this test is to verify that FQDN is read from
// a buffer and returned as a text. The representation of the FQDN
// in the buffer complies with RFC1035, section 3.1.
// This test also checks that if invalid (truncated) FQDN is stored
// in a buffer the appropriate exception is returned when trying to
// read it as a string.
TEST_F(OptionDataTypesTest, readFqdn) {
    // The binary representation of the "mydomain.example.com".
    // Values: 8, 7, 3 and 0 specify the lengths of subsequent
    // labels within the FQDN.
    const char data[] = {
        8, 109, 121, 100, 111, 109, 97, 105, 110, // "mydomain"
        7, 101, 120, 97, 109, 112, 108, 101,      // "example"
        3, 99, 111, 109,                          // "com"
        0
    };

    // Make a vector out of the data.
    std::vector<uint8_t> buf(data, data + sizeof(data));

    // Read the buffer as FQDN and verify its correctness.
    std::string fqdn;
    EXPECT_NO_THROW(fqdn = OptionDataTypeUtil::readFqdn(buf));
    EXPECT_EQ("mydomain.example.com.", fqdn);

    // By resizing the buffer we simulate truncation. The first
    // length field (8) indicate that the first label's size is
    // 8 but the actual buffer size is 5. Expect that conversion
    // fails.
    buf.resize(5);
    EXPECT_THROW(
        OptionDataTypeUtil::readFqdn(buf),
        isc::dhcp::BadDataTypeCast
    );

    // Another special case: provide an empty buffer.
    buf.clear();
    EXPECT_THROW(
        OptionDataTypeUtil::readFqdn(buf),
        isc::dhcp::BadDataTypeCast
    );
}

// The purpose of this test is to verify that FQDN's syntax is validated
// and that FQDN is correctly written to a buffer in a format described
// in RFC1035 section 3.1.
TEST_F(OptionDataTypesTest, writeFqdn) {
    // Create empty buffer. The FQDN will be written to it.
    OptionBuffer buf;
    // Write a domain name into the buffer in the format described
    // in RFC1035 section 3.1. This function should not throw
    // exception because domain name is well formed.
    EXPECT_NO_THROW(
        OptionDataTypeUtil::writeFqdn("mydomain.example.com", buf)
    );
    // The length of the data is 22 (8 bytes for "mydomain" label,
    // 7 bytes for "example" label, 3 bytes for "com" label and
    // finally 4 bytes positions between labels where length
    // information is stored.
    ASSERT_EQ(22, buf.size());

    // Verify that length fields between labels hold valid values.
    EXPECT_EQ(8, buf[0]);  // length of "mydomain"
    EXPECT_EQ(7, buf[9]);  // length of "example"
    EXPECT_EQ(3, buf[17]); // length of "com"
    EXPECT_EQ(0, buf[21]); // zero byte at the end.

    // Verify that labels are valid.
    std::string label0(buf.begin() + 1, buf.begin() + 9);
    EXPECT_EQ("mydomain", label0);

    std::string label1(buf.begin() + 10, buf.begin() + 17);
    EXPECT_EQ("example", label1);

    std::string label2(buf.begin() + 18, buf.begin() + 21);
    EXPECT_EQ("com", label2);

    // The tested function is supposed to append data to a buffer
    // so let's check that it is a case by appending another domain.
    OptionDataTypeUtil::writeFqdn("hello.net", buf);

    // The buffer length should be now longer.
    ASSERT_EQ(33, buf.size());

    // Check the length fields for new labels being appended.
    EXPECT_EQ(5, buf[22]);
    EXPECT_EQ(3, buf[28]);

    // And check that labels are ok.
    std::string label3(buf.begin() + 23, buf.begin() + 28);
    EXPECT_EQ("hello", label3);

    std::string label4(buf.begin() + 29, buf.begin() + 32);
    EXPECT_EQ("net", label4);

    // Check that invalid (empty) FQDN is rejected and expected
    // exception type is thrown.
    buf.clear();
    EXPECT_THROW(
        OptionDataTypeUtil::writeFqdn("", buf),
        isc::dhcp::BadDataTypeCast
    );

    // Check another invalid domain name (with repeated dot).
    buf.clear();
    EXPECT_THROW(
        OptionDataTypeUtil::writeFqdn("example..com", buf),
        isc::dhcp::BadDataTypeCast
    );
}

// The purpose of this test is to verify that the variable length prefix
// can be read from a buffer correctly.
TEST_F(OptionDataTypesTest, readPrefix) {
    std::vector<uint8_t> buf;

    // Prefix 2001:db8::/64
    writeInt<uint8_t>(64, buf);
    writeInt<uint32_t>(0x20010db8, buf);
    writeInt<uint32_t>(0, buf);

    PrefixTuple prefix(ZERO_PREFIX_TUPLE);
    ASSERT_NO_THROW(prefix = OptionDataTypeUtil::readPrefix(buf));
    EXPECT_EQ(64, prefix.first.asUnsigned());
    EXPECT_EQ("2001:db8::", prefix.second.toText());

    buf.clear();

    // Prefix 2001:db8::/63
    writeInt<uint8_t>(63, buf);
    writeInt<uint32_t>(0x20010db8, buf);
    writeInt<uint32_t>(0, buf);

    ASSERT_NO_THROW(prefix = OptionDataTypeUtil::readPrefix(buf));
    EXPECT_EQ(63, prefix.first.asUnsigned());
    EXPECT_EQ("2001:db8::", prefix.second.toText());

    buf.clear();

    // Prefix 2001:db8:c0000. Note that the last four bytes are filled with
    // 0xFF (all bits set). When the prefix is read those non-significant
    // bits (beyond prefix length) should be ignored (read as 0). Only first
    // two bits of 0xFFFFFFFF should be read, thus 0xC000, rather than 0xFFFF.
    writeInt<uint8_t>(34, buf);
    writeInt<uint32_t>(0x20010db8, buf);
    writeInt<uint32_t>(0xFFFFFFFF, buf);

    ASSERT_NO_THROW(prefix = OptionDataTypeUtil::readPrefix(buf));
    EXPECT_EQ(34, prefix.first.asUnsigned());
    EXPECT_EQ("2001:db8:c000::", prefix.second.toText());

    buf.clear();

    // Prefix having a length of 0.
    writeInt<uint8_t>(0, buf);
    writeInt<uint16_t>(0x2001, buf);

    ASSERT_NO_THROW(prefix = OptionDataTypeUtil::readPrefix(buf));
    EXPECT_EQ(0, prefix.first.asUnsigned());
    EXPECT_EQ("::", prefix.second.toText());

    buf.clear();

    // Prefix having a maximum length of 128.
    writeInt<uint8_t>(128, buf);
    buf.insert(buf.end(), 16, 0x11);

    ASSERT_NO_THROW(prefix = OptionDataTypeUtil::readPrefix(buf));
    EXPECT_EQ(128, prefix.first.asUnsigned());
    EXPECT_EQ("1111:1111:1111:1111:1111:1111:1111:1111",
              prefix.second.toText());

    buf.clear();

    // Prefix length is greater than 128. This should result in an
    // error.
    writeInt<uint8_t>(129, buf);
    writeInt<uint16_t>(0x3000, buf);
    buf.resize(17);

    EXPECT_THROW(static_cast<void>(OptionDataTypeUtil::readPrefix(buf)),
                 BadDataTypeCast);

    buf.clear();

    // Buffer truncated. Prefix length of 10 requires at least 2 bytes,
    // but there is only one byte.
    writeInt<uint8_t>(10, buf);
    writeInt<uint8_t>(1, buf);

    EXPECT_THROW(static_cast<void>(OptionDataTypeUtil::readPrefix(buf)),
                 BadDataTypeCast);
}

// The purpose of this test is to verify that the variable length prefix
// is written to a buffer correctly.
TEST_F(OptionDataTypesTest, writePrefix) {
    // Initialize a buffer and store some value in it. We'll want to make
    // sure that the prefix being written will not override this value, but
    // will rather be appended.
    std::vector<uint8_t> buf(1, 1);

    // Prefix 2001:db8:FFFF::/34 is equal to 2001:db8:C000::/34 because
    // there are only 34 significant bits. All other bits must be zeroed.
    ASSERT_NO_THROW(OptionDataTypeUtil::writePrefix(PrefixLen(34),
                                                    IOAddress("2001:db8:FFFF::"),
                                                    buf));
    ASSERT_EQ(7, buf.size());

    EXPECT_EQ(1, static_cast<unsigned>(buf[0]));
    EXPECT_EQ(34, static_cast<unsigned>(buf[1]));
    EXPECT_EQ(0x20, static_cast<unsigned>(buf[2]));
    EXPECT_EQ(0x01, static_cast<unsigned>(buf[3]));
    EXPECT_EQ(0x0D, static_cast<unsigned>(buf[4]));
    EXPECT_EQ(0xB8, static_cast<unsigned>(buf[5]));
    EXPECT_EQ(0xC0, static_cast<unsigned>(buf[6]));

    buf.clear();

    // Prefix length is 0. The entire prefix should be ignored.
    ASSERT_NO_THROW(OptionDataTypeUtil::writePrefix(PrefixLen(0),
                                                    IOAddress("2001:db8:FFFF::"),
                                                    buf));
    ASSERT_EQ(1, buf.size());
    EXPECT_EQ(0, static_cast<unsigned>(buf[0]));

    buf.clear();

    // Prefix having a maximum length of 128.
    ASSERT_NO_THROW(OptionDataTypeUtil::writePrefix(PrefixLen(128),
                                                    IOAddress("2001:db8::FF"),
                                                    buf));

    // We should now have a 17 bytes long buffer. 1 byte goes for a prefix
    // length field, the remaining ones hold the prefix.
    ASSERT_EQ(17, buf.size());
    // Because the prefix is 16 bytes long, we can simply use the
    // IOAddress convenience function to read it back and compare
    // it with the textual representation. This is simpler than
    // comparing each byte separately.
    IOAddress prefix_read = IOAddress::fromBytes(AF_INET6, &buf[1]);
    EXPECT_EQ("2001:db8::ff", prefix_read.toText());

    buf.clear();

    // It is illegal to use IPv4 address as prefix.
    EXPECT_THROW(OptionDataTypeUtil::writePrefix(PrefixLen(4),
                                                 IOAddress("10.0.0.1"), buf),
                 BadDataTypeCast);
}

// The purpose of this test is to verify that the
// PSID-len/PSID tuple can be read from a buffer.
TEST_F(OptionDataTypesTest, readPsid) {
    std::vector<uint8_t> buf;

    // PSID length is 6 (bits)
    writeInt<uint8_t>(6, buf);
    // 0xA400 is represented as 1010010000000000b, which is equivalent
    // of portset 0x29 (101001b).
    writeInt<uint16_t>(0xA400, buf);

    PSIDTuple psid;
    ASSERT_NO_THROW(psid = OptionDataTypeUtil::readPsid(buf));
    EXPECT_EQ(6, psid.first.asUnsigned());
    EXPECT_EQ(0x29, psid.second.asUint16());

    buf.clear();

    // PSID length is 0, in which case PSID should be ignored.
    writeInt<uint8_t>(0, buf);
    // Let's put some junk into the PSID field to make sure it will
    // be ignored.
    writeInt<uint16_t>(0x1234, buf);
    ASSERT_NO_THROW(psid = OptionDataTypeUtil::readPsid(buf));
    EXPECT_EQ(0, psid.first.asUnsigned());
    EXPECT_EQ(0, psid.second.asUint16());

    buf.clear();

    // PSID length greater than 16 is not allowed.
    writeInt<uint8_t>(17, buf);
    writeInt<uint16_t>(0, buf);
    EXPECT_THROW(static_cast<void>(OptionDataTypeUtil::readPsid(buf)),
                 BadDataTypeCast);

    buf.clear();

    // PSID length is 3 bits, but the PSID value is 11 (1011b), so it
    // is encoded on 4 bits, rather than 3.
    writeInt<uint8_t>(3, buf);
    writeInt<uint16_t>(0xB000, buf);
    EXPECT_THROW(static_cast<void>(OptionDataTypeUtil::readPsid(buf)),
                 BadDataTypeCast);

    buf.clear();

    // Buffer is truncated -  2 bytes instead of 3.
    writeInt<uint8_t>(4, buf);
    writeInt<uint8_t>(0xF0, buf);
    EXPECT_THROW(static_cast<void>(OptionDataTypeUtil::readPsid(buf)),
                 BadDataTypeCast);
}

// The purpose of this test is to verify that the PSID-len/PSID
// tuple is written to a buffer correctly.
TEST_F(OptionDataTypesTest, writePsid) {
    // Let's create a buffer with some data in it. We want to make
    // sure that the existing data remain untouched when we write
    // PSID to the buffer.
    std::vector<uint8_t> buf(1, 1);
    // PSID length is 4 (bits), PSID value is 8.
    ASSERT_NO_THROW(OptionDataTypeUtil::writePsid(PSIDLen(4), PSID(8), buf));
    ASSERT_EQ(4, buf.size());
    // The byte which existed in the buffer should still hold the
    // same value.
    EXPECT_EQ(1, static_cast<unsigned>(buf[0]));
    // PSID length should be written as specified in the function call.
    EXPECT_EQ(4, static_cast<unsigned>(buf[1]));
    // The PSID structure is as follows:
    // UUUUPPPPPPPPPPPP, where "U" are useful bits on which we code
    // the PSID. "P" are zero padded bits. The PSID value 8 is coded
    // on four useful bits as '1000b'. That means that the PSID value
    // encoded in the PSID field is: '1000000000000000b', which is
    // 0x8000. The next two EXPECT_EQ statements verify that.
    EXPECT_EQ(0x80, static_cast<unsigned>(buf[2]));
    EXPECT_EQ(0x00, static_cast<unsigned>(buf[3]));

    // Clear the buffer to make sure we don't append to the
    // existing data.
    buf.clear();

    // The PSID length of 0 causes the PSID value (of 6) to be ignored.
    // As a result, the buffer should hold only zeros.
    ASSERT_NO_THROW(OptionDataTypeUtil::writePsid(PSIDLen(0), PSID(6), buf));
    ASSERT_EQ(3, buf.size());
    EXPECT_EQ(0, static_cast<unsigned>(buf[0]));
    EXPECT_EQ(0, static_cast<unsigned>(buf[1]));
    EXPECT_EQ(0, static_cast<unsigned>(buf[2]));

    buf.clear();

    // Another test case, to verify that we can use the maximum length
    // of PSID (16 bits).
    ASSERT_NO_THROW(OptionDataTypeUtil::writePsid(PSIDLen(16), PSID(5), buf));
    ASSERT_EQ(3, buf.size());
    // PSID length should be written with no change.
    EXPECT_EQ(16, static_cast<unsigned>(buf[0]));
    // Check PSID value.
    EXPECT_EQ(0x00, static_cast<unsigned>(buf[1]));
    EXPECT_EQ(0x05, static_cast<unsigned>(buf[2]));

    // PSID length of 17 exceeds the maximum allowed value of 16.
    EXPECT_THROW(OptionDataTypeUtil::writePsid(PSIDLen(17), PSID(1), buf),
                 OutOfRange);

    // PSID length is 1, which allows for coding up to two (2^1)
    // port sets. These are namely port set 0 and port set 1. The
    // value of 2 is out of that range.
    EXPECT_THROW(OptionDataTypeUtil::writePsid(PSIDLen(1), PSID(2), buf),
                 BadDataTypeCast);
}

// The purpose of this test is to verify that the string
// can be read from a buffer correctly.
TEST_F(OptionDataTypesTest, readString) {

    // Prepare a buffer with some string in it.
    std::vector<uint8_t> buf;
    writeString("hello world", buf);

    // Read the string from the buffer.
    std::string value;
    ASSERT_NO_THROW(
        value = OptionDataTypeUtil::readString(buf);
    );
    // Check that it is valid.
    EXPECT_EQ("hello world", value);

    // Only nulls should throw.
    OptionBuffer buffer = { 0, 0 };
    ASSERT_THROW(OptionDataTypeUtil::readString(buffer), isc::OutOfRange);

    // One trailing null should trim off.
    buffer = {'o', 'n', 'e', 0 };
    ASSERT_NO_THROW(value = OptionDataTypeUtil::readString(buffer));
    EXPECT_EQ(3, value.length());
    EXPECT_EQ(value, std::string("one"));

    // More than one trailing null should trim off.
    buffer = { 't', 'h', 'r', 'e', 'e', 0, 0, 0 };
    ASSERT_NO_THROW(value = OptionDataTypeUtil::readString(buffer));
    EXPECT_EQ(5, value.length());
    EXPECT_EQ(value, std::string("three"));

    // Embedded null should be left in place.
    buffer = { 'e', 'm', 0, 'b', 'e', 'd' };
    ASSERT_NO_THROW(value = OptionDataTypeUtil::readString(buffer));
    EXPECT_EQ(6, value.length());
    EXPECT_EQ(value, (std::string{"em\0bed", 6}));

    // Leading null should be left in place.
    buffer = { 0, 'l', 'e', 'a', 'd', 'i', 'n', 'g' };
    ASSERT_NO_THROW(value = OptionDataTypeUtil::readString(buffer));
    EXPECT_EQ(8, value.length());
    EXPECT_EQ(value, (std::string{"\0leading", 8}));
}

// The purpose of this test is to verify that a string can be
// stored in a buffer correctly.
TEST_F(OptionDataTypesTest, writeString) {
    // Prepare a buffer with a reference data.
    std::vector<uint8_t> buf_ref;
    writeString("hello world!", buf_ref);
    // Create empty buffer we will write to.
    std::vector<uint8_t> buf;
    ASSERT_NO_THROW(OptionDataTypeUtil::writeString("hello world!", buf));
    // Compare two buffers.
    ASSERT_EQ(buf_ref.size(), buf.size());
    EXPECT_TRUE(std::equal(buf_ref.begin(), buf_ref.end(), buf.begin()));
}

} // anonymous namespace
