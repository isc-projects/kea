// Copyright (C) 2012-2013 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <dhcp/option_data_types.h>
#include <gtest/gtest.h>

using namespace isc;
using namespace isc::dhcp;

namespace {

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
        for (int i = 0; i < sizeof(T); ++i) {
            buf.push_back(value >> ((sizeof(T) - i - 1) * 8) & 0xFF);
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
