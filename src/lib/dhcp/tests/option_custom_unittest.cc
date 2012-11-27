// Copyright (C) 2012 Internet Systems Consortium, Inc. ("ISC")
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

#include <asiolink/io_address.h>
#include <dhcp/option_custom.h>

#include <boost/scoped_ptr.hpp>
#include <gtest/gtest.h>

using namespace isc;
using namespace isc::asiolink;
using namespace isc::dhcp;

namespace {

/// @brief OptionCustomTest test class.
class OptionCustomTest : public ::testing::Test {
public:
    /// @brief Constructor.
    OptionCustomTest() { }

    /// @brief Write IP address into a buffer.
    ///
    /// @param address address to be written.
    /// @param [out] buf output buffer.
    void writeAddress(const asiolink::IOAddress& address,
                      std::vector<uint8_t>& buf) {
        short family = address.getFamily();
        if (family == AF_INET) {
            asio::ip::address_v4::bytes_type buf_addr =
                address.getAddress().to_v4().to_bytes();
            buf.insert(buf.end(), buf_addr.begin(), buf_addr.end());
        } else if (family == AF_INET6) {
            asio::ip::address_v6::bytes_type buf_addr =
                address.getAddress().to_v6().to_bytes();
            buf.insert(buf.end(), buf_addr.begin(), buf_addr.end());
        }
    }

    /// @brief Write integer (signed or unsiged) into a buffer.
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

// The purpose of this test is to check that parameters passed to
// a custom option's constructor are used to initialize class
// members.
TEST_F(OptionCustomTest, constructor) {
    // Create option definition for a DHCPv6 option.
    OptionDefinition opt_def1("OPTION_FOO", 1000, "boolean", true);

    // Initialize some dummy buffer that holds single boolean value.
    OptionBuffer buf;
    buf.push_back(1);

    // Create DHCPv6 option.
    boost::scoped_ptr<OptionCustom> option;
    ASSERT_NO_THROW(
        option.reset(new OptionCustom(opt_def1, Option::V6, buf));
    );
    ASSERT_TRUE(option);

    // Check if constructor initialized the universe and type correctly.
    EXPECT_EQ(Option::V6, option->getUniverse());
    EXPECT_EQ(1000, option->getType());

    // Do another round of testing for DHCPv4 option.
    OptionDefinition opt_def2("OPTION_FOO", 232, "boolean");

    ASSERT_NO_THROW(
        option.reset(new OptionCustom(opt_def2, Option::V4, buf.begin(), buf.end()));
    );
    ASSERT_TRUE(option);

    EXPECT_EQ(Option::V4, option->getUniverse());
    EXPECT_EQ(232, option->getType());
}

// The purpose of this test is to verify that 'empty' option definition can
// be used to create an instance of custom option.
TEST_F(OptionCustomTest, emptyData) {
    OptionDefinition opt_def("OPTION_FOO", 232, "empty");

    boost::scoped_ptr<OptionCustom> option;
    ASSERT_NO_THROW(
        option.reset(new OptionCustom(opt_def, Option::V4, OptionBuffer()));
    );
    ASSERT_TRUE(option);

    // Option is 'empty' so no data fields are expected.
    EXPECT_EQ(0, option->getDataFieldsNum());
}

// The purpose of this test is to verify that the option definition comprising
// a binary value can be used to create an instance of custom option.
TEST_F(OptionCustomTest, binaryData) {
    OptionDefinition opt_def("OPTION_FOO", 231, "binary");

    // Create a buffer holding some binary data. This data will be
    // used as reference when we read back the data from a created
    // option.
    OptionBuffer buf_in(14);
    for (int i = 0; i < 14; ++i) {
        buf_in[i] = i;
    }
    // Use scoped pointer because it allows to declare the option
    // in the function scope and initialize it under ASSERT.
    boost::scoped_ptr<OptionCustom> option;
    // Custom option may throw exception if the provided buffer is
    // malformed.
    ASSERT_NO_THROW(
        option.reset(new OptionCustom(opt_def, Option::V4, buf_in));
    );
    ASSERT_TRUE(option);

    // We should have just one data field.
    ASSERT_EQ(1, option->getDataFieldsNum());

    // The custom option should hold just one buffer that can be
    // accessed using index 0.
    OptionBuffer buf_out;
    ASSERT_NO_THROW(buf_out = option->readBinary(0));

    // Read buffer must match exactly with the buffer used to
    // create option instance.
    ASSERT_EQ(buf_in.size(), buf_out.size());
    EXPECT_TRUE(std::equal(buf_in.begin(), buf_in.end(), buf_out.begin()));
}

// The purpose of this test is to verify that the option definition comprising
// single boolean value can be used to create an instance of custom option.
TEST_F(OptionCustomTest, booleanData) {
    OptionDefinition opt_def("OPTION_FOO", 1000, "boolean");

    OptionBuffer buf;
    // Push back the value that represents 'false'.
    buf.push_back(0);
    // Push back the 'true' value. Note that this value should
    // be ignored by custom option because it holds single boolean
    // value (according to option definition).
    buf.push_back(1);

    boost::scoped_ptr<OptionCustom> option;
    ASSERT_NO_THROW(
        option.reset(new OptionCustom(opt_def, Option::V6, buf));
    );
    ASSERT_TRUE(option);

    // We should have just one data field.
    ASSERT_EQ(1, option->getDataFieldsNum());

    // Initialize the value to true because we want to make sure
    // that it is modified to 'false' by readBoolean below.
    bool value = true;

    // Read the boolean value from only one available buffer indexed
    // with 0. It is expected to be 'false'.
    ASSERT_NO_THROW(value = option->readBoolean(0));
    EXPECT_FALSE(value);
}

// The purpose of this test is to verify that the option definition comprising
// 16-bit signed integer value can be used to create an instance of custom option.
TEST_F(OptionCustomTest, int16Data) {
    OptionDefinition opt_def("OPTION_FOO", 1000, "int16");

    OptionBuffer buf;
    // Store signed integer value in the input buffer.
    writeInt<int16_t>(-234, buf);

    // Create custom option.
    boost::scoped_ptr<OptionCustom> option;
    ASSERT_NO_THROW(
        option.reset(new OptionCustom(opt_def, Option::V6, buf));
    );
    ASSERT_TRUE(option);

    // We should have just one data field.
    ASSERT_EQ(1, option->getDataFieldsNum());

    // Initialize value to 0 explicitely to make sure that is
    // modified by readInteger function to expected -234.
    int16_t value = 0;
    ASSERT_NO_THROW(value = option->readInteger<int16_t>(0));
    EXPECT_EQ(-234, value);
}

// The purpose of this test is to verify that the option definition comprising
// single IPv4 addres can be used to create an instance of custom option.
TEST_F(OptionCustomTest, ipv4AddressData) {
    OptionDefinition opt_def("OPTION_FOO", 231, "ipv4-address");

    // Create input buffer.
    OptionBuffer buf;
    writeAddress(IOAddress("192.168.100.50"), buf);

    // Create custom option.
    boost::scoped_ptr<OptionCustom> option;
    ASSERT_NO_THROW(
        option.reset(new OptionCustom(opt_def, Option::V4, buf));
    );
    ASSERT_TRUE(option);

    // We should have just one data field.
    ASSERT_EQ(1, option->getDataFieldsNum());

    IOAddress address("127.0.0.1");
    // Read IPv4 address from using index 0.
    ASSERT_NO_THROW(option->readAddress(0, address));

    EXPECT_EQ("192.168.100.50", address.toText());
}

// The purpose of this test is to verify that the option definition comprising
// single IPv6 addres can be used to create an instance of custom option.
TEST_F(OptionCustomTest, ipv6AddressData) {
    OptionDefinition opt_def("OPTION_FOO", 1000, "ipv6-address");

    // Initialize input buffer.
    OptionBuffer buf;
    writeAddress(IOAddress("2001:db8:1::100"), buf);

    // Create custom option using input buffer.
    boost::scoped_ptr<OptionCustom> option;
    ASSERT_NO_THROW(
        option.reset(new OptionCustom(opt_def, Option::V6, buf));
    );
    ASSERT_TRUE(option);

    // We should have just one data field.
    ASSERT_EQ(1, option->getDataFieldsNum());

    // Custom option should comprise exactly one buffer that represents
    // IPv6 address.
    IOAddress address("::1");
    // Read an address from buffer #0.
    ASSERT_NO_THROW(option->readAddress(0, address));

    EXPECT_EQ("2001:db8:1::100", address.toText());
}

// The purpose of this test is to verify that the option definition comprising
// string value can be used to create an instance of custom option.
TEST_F(OptionCustomTest, stringData) {
    OptionDefinition opt_def("OPTION_FOO", 1000, "string");

    // Create an input buffer holding some string value.
    OptionBuffer buf;
    writeString("hello world!", buf);

    // Create custom option using input buffer.
    boost::scoped_ptr<OptionCustom> option;
    ASSERT_NO_THROW(
        option.reset(new OptionCustom(opt_def, Option::V6, buf.begin(), buf.end()));
    );
    ASSERT_TRUE(option);

    // We should have just one data field.
    ASSERT_EQ(1, option->getDataFieldsNum());

    // Custom option should now comprise single string value that
    // can be accessed using index 0.
    std::string value;
    ASSERT_NO_THROW(option->readString(0, value));

    EXPECT_EQ("hello world!", value);
}

// The purpose of this test is to verify that the option definition comprising
// an array of boolean values can be used to create an instance of custom option.
TEST_F(OptionCustomTest, booleanDataArray) {
    OptionDefinition opt_def("OPTION_FOO", 1000, "boolean", true);

    // Create a buffer with 5 values that represent array of
    // booleans.
    OptionBuffer buf(5);
    buf[0] = 1; // true
    buf[1] = 0; // false
    buf[2] = 0; // false
    buf[3] = 1; // true
    buf[4] = 1; // true

    // Use the input buffer to create custom option.
    boost::scoped_ptr<OptionCustom> option;
    ASSERT_NO_THROW(
        option.reset(new OptionCustom(opt_def, Option::V6, buf.begin(), buf.end()));
    );
    ASSERT_TRUE(option);

    // We should have 5 data fields.
    ASSERT_EQ(5, option->getDataFieldsNum());

    // Read values from custom option using indexes 0..4 and
    // check that they are valid.
    bool value0 = false;
    ASSERT_NO_THROW(value0 = option->readBoolean(0));
    EXPECT_TRUE(value0);

    bool value1 = true;
    ASSERT_NO_THROW(value1 = option->readBoolean(1));
    EXPECT_FALSE(value1);

    bool value2 = true;
    ASSERT_NO_THROW(value2 = option->readBoolean(2));
    EXPECT_FALSE(value2);

    bool value3 = false;
    ASSERT_NO_THROW(value3 = option->readBoolean(3));
    EXPECT_TRUE(value3);

    bool value4 = false;
    ASSERT_NO_THROW(value4 = option->readBoolean(4));
    EXPECT_TRUE(value4);
}

// The purpose of this test is to verify that the option definition comprising
// an array of 32-bit signed integer values can be used to create an instance
// of custom option.
TEST_F(OptionCustomTest, uint32DataArray) {
    OptionDefinition opt_def("OPTION_FOO", 1000, "uint32", true);

    // Create an input buffer that holds 4 uint32 values that
    // represent an array.
    std::vector<uint32_t> values;
    values.push_back(71234);
    values.push_back(12234);
    values.push_back(54362);
    values.push_back(1234);

    // Store these values in a buffer.
    OptionBuffer buf;
    for (int i = 0; i < values.size(); ++i) {
        writeInt<uint32_t>(values[i], buf);
    }
    // Create custom option using the input buffer.
    boost::scoped_ptr<OptionCustom> option;
    ASSERT_NO_THROW(
        // Note that we just use a part of the whole buffer here: 13 bytes. We want to
        // check that buffer length which is non-divisible by 4 (size of uint32_t) is
        // accepted and only 3 (instead of 4) elements will be stored in a custom option.
        option.reset(new OptionCustom(opt_def, Option::V6, buf.begin(), buf.begin() + 13));
    );
    ASSERT_TRUE(option);

    // We should have 3 data fields.
    ASSERT_EQ(3, option->getDataFieldsNum());

    // Expect only 3 values.
    for (int i = 0; i < 3; ++i) {
        uint32_t value = 0;
        ASSERT_NO_THROW(value = option->readInteger<uint32_t>(i));
        EXPECT_EQ(values[i], value);
    }
}

// The purpose of this test is to verify that the option definition comprising
// an array of IPv4 addresses can be used to create an instance of custom option.
TEST_F(OptionCustomTest, ipv4AddressDataArray) {
    OptionDefinition opt_def("OPTION_FOO", 231, "ipv4-address", true);

    // Initialize reference data.
    std::vector<IOAddress> addresses;
    addresses.push_back(IOAddress("192.168.0.1"));
    addresses.push_back(IOAddress("127.0.0.1"));
    addresses.push_back(IOAddress("10.10.1.2"));

    // Store the collection of IPv4 addresses into the buffer.
    OptionBuffer buf;
    for (int i = 0; i < addresses.size(); ++i) {
        writeAddress(addresses[i], buf);
    }

    // Use the input buffer to create custom option.
    boost::scoped_ptr<OptionCustom> option;
    ASSERT_NO_THROW(
        option.reset(new OptionCustom(opt_def, Option::V4, buf.begin(), buf.begin() + 13));
    );
    ASSERT_TRUE(option);

    // We should have 3 data fields.
    ASSERT_EQ(3, option->getDataFieldsNum());

    // We expect 3 IPv4 addresses being stored in the option.
    for (int i = 0; i < 3; ++i) {
        IOAddress address("10.10.10.10");
        ASSERT_NO_THROW(option->readAddress(i, address));
        EXPECT_EQ(addresses[i].toText(), address.toText());
    }
}

// The purpose of this test is to verify that the option definition comprising
// an array of IPv6 addresses can be used to create an instance of custom option.
TEST_F(OptionCustomTest, ipv6AddressDataArray) {
    OptionDefinition opt_def("OPTION_FOO", 1000, "ipv6-address", true);

    // Initialize reference data.
    std::vector<IOAddress> addresses;
    addresses.push_back(IOAddress("2001:db8:1::3"));
    addresses.push_back(IOAddress("::1"));
    addresses.push_back(IOAddress("fe80::3"));

    // Store the collection of IPv6 addresses into the buffer.
    OptionBuffer buf;
    for (int i = 0; i < addresses.size(); ++i) {
        writeAddress(addresses[i], buf);
    }

    // Use the input buffer to create custom option.
    boost::scoped_ptr<OptionCustom> option;
    ASSERT_NO_THROW(
        option.reset(new OptionCustom(opt_def, Option::V6, buf.begin(), buf.begin() + 50));
    );
    ASSERT_TRUE(option);

    // We should have 3 data fields.
    ASSERT_EQ(3, option->getDataFieldsNum());

    // We expect 3 IPv6 addresses being stored in the option.
    for (int i = 0; i < 3; ++i) {
        IOAddress address("fe80::4");
        ASSERT_NO_THROW(option->readAddress(i, address));
        EXPECT_EQ(addresses[i].toText(), address.toText());
    }
}

// The purpose of this test is to verify that the option definition comprising
// a record of various data fields can be used to create an instance of
// custom option.
TEST_F(OptionCustomTest, recordData) {
    // Create the definition of an option which comprises
    // a record of fields of different types.
    OptionDefinition opt_def("OPTION_FOO", 1000, "record");
    ASSERT_NO_THROW(opt_def.addRecordField("uint16"));
    ASSERT_NO_THROW(opt_def.addRecordField("boolean"));
    ASSERT_NO_THROW(opt_def.addRecordField("ipv4-address"));
    ASSERT_NO_THROW(opt_def.addRecordField("ipv6-address"));
    ASSERT_NO_THROW(opt_def.addRecordField("string"));

    OptionBuffer buf;
    // Initialize field 0.
    writeInt<uint16_t>(8712, buf);
    // Initialize field 1 to 'true'
    buf.push_back(static_cast<unsigned short>(1));
    // Initialize field 2 to IPv4 address.
    writeAddress(IOAddress("192.168.0.1"), buf);
    // Initialize field 3 to IPv6 address.
    writeAddress(IOAddress("2001:db8:1::1"), buf);
    // Initialize field 4 to string value.
    writeString("ABCD", buf);

    boost::scoped_ptr<OptionCustom> option;
    ASSERT_NO_THROW(
        option.reset(new OptionCustom(opt_def, Option::V6, buf.begin(), buf.begin() + 27));
    );
    ASSERT_TRUE(option);

    // We should have 5 data fields.
    ASSERT_EQ(5, option->getDataFieldsNum());

    // Verify value in the field 0.
    uint16_t value0 = 0;
    ASSERT_NO_THROW(value0 = option->readInteger<uint16_t>(0));
    EXPECT_EQ(8712, value0);

    // Verify value in the field 1.
    bool value1 = false;
    ASSERT_NO_THROW(value1 = option->readBoolean(1));
    EXPECT_TRUE(value1);

    // Verify value in the field 2.
    IOAddress value2("127.0.0.1");
    ASSERT_NO_THROW(option->readAddress(2, value2));
    EXPECT_EQ("192.168.0.1", value2.toText());

    // Verify value in the field 3.
    IOAddress value3("::1");
    ASSERT_NO_THROW(option->readAddress(3, value3));
    EXPECT_EQ("2001:db8:1::1", value3.toText());

    // Verify value in the field 4.
    std::string value4;
    ASSERT_NO_THROW(option->readString(4, value4));
    EXPECT_EQ("ABCD", value4);
}

// The purpose of this test is to verify that pack function for
// DHCPv4 custom option works correctly.
TEST_F(OptionCustomTest, pack4) {
    OptionDefinition opt_def("OPTION_FOO", 234, "record");
    ASSERT_NO_THROW(opt_def.addRecordField("uint8"));
    ASSERT_NO_THROW(opt_def.addRecordField("uint16"));
    ASSERT_NO_THROW(opt_def.addRecordField("uint32"));

    OptionBuffer buf;
    writeInt<uint8_t>(1, buf);
    writeInt<uint16_t>(1000, buf);
    writeInt<uint32_t>(100000, buf);

    boost::scoped_ptr<OptionCustom> option;
    ASSERT_NO_THROW(
        option.reset(new OptionCustom(opt_def, Option::V4, buf));
    );
    ASSERT_TRUE(option);

    util::OutputBuffer buf_out(7);
    ASSERT_NO_THROW(option->pack(buf_out));
    ASSERT_EQ(9, buf_out.getLength());

    // The original buffer holds the option data but it lacks a header.
    // We append data length and option code so as it can be directly
    // compared with the output buffer that holds whole option.
    buf.insert(buf.begin(), 7);
    buf.insert(buf.begin(), 234);

    // Validate the buffer.
    EXPECT_EQ(0, memcmp(&buf[0], buf_out.getData(), 7));
}

// The purpose of this test is to verify that pack function for
// DHCPv6 custom option works correctly.
TEST_F(OptionCustomTest, pack6) {
    OptionDefinition opt_def("OPTION_FOO", 1000, "record");
    ASSERT_NO_THROW(opt_def.addRecordField("boolean"));
    ASSERT_NO_THROW(opt_def.addRecordField("uint16"));
    ASSERT_NO_THROW(opt_def.addRecordField("string"));

    OptionBuffer buf;
    buf.push_back(1);
    writeInt<uint16_t>(1000, buf);
    writeString("hello world", buf);

    boost::scoped_ptr<OptionCustom> option;
    ASSERT_NO_THROW(
        option.reset(new OptionCustom(opt_def, Option::V6, buf));
    );
    ASSERT_TRUE(option);

    util::OutputBuffer buf_out(buf.size() + option->getHeaderLen());
    ASSERT_NO_THROW(option->pack(buf_out));
    ASSERT_EQ(buf.size() + option->getHeaderLen(), buf_out.getLength());

    // The original buffer holds the option data but it lacks a header.
    // We append data length and option code so as it can be directly
    // compared with the output buffer that holds whole option.
    OptionBuffer tmp;
    writeInt<uint16_t>(1000, tmp);
    writeInt<uint16_t>(buf.size(), tmp);
    buf.insert(buf.begin(), tmp.begin(), tmp.end());

    // Validate the buffer.
    EXPECT_EQ(0, memcmp(&buf[0], buf_out.getData(), 7));
}

// The purpose of this test is to verify that unpack function works
// correctly for a custom option.
TEST_F(OptionCustomTest, unpack) {
    OptionDefinition opt_def("OPTION_FOO", 231, "ipv4-address", true);

    // Initialize reference data.
    std::vector<IOAddress> addresses;
    addresses.push_back(IOAddress("192.168.0.1"));
    addresses.push_back(IOAddress("127.0.0.1"));
    addresses.push_back(IOAddress("10.10.1.2"));

    // Store the collection of IPv4 addresses into the buffer.
    OptionBuffer buf;
    for (int i = 0; i < addresses.size(); ++i) {
        writeAddress(addresses[i], buf);
    }

    // Use the input buffer to create custom option.
    boost::scoped_ptr<OptionCustom> option;
    ASSERT_NO_THROW(
        option.reset(new OptionCustom(opt_def, Option::V4, buf.begin(), buf.begin() + 13));
    );
    ASSERT_TRUE(option);

    // We should have 3 data fields.
    ASSERT_EQ(3, option->getDataFieldsNum());

    // We expect 3 IPv4 addresses being stored in the option.
    for (int i = 0; i < 3; ++i) {
        IOAddress address("10.10.10.10");
        ASSERT_NO_THROW(option->readAddress(i, address));
        EXPECT_EQ(addresses[i].toText(), address.toText());
    }

    // Remove all addresses we had added. We are going to replace
    // them with a new set of addresses.
    addresses.clear();

    // Add new addresses.
    addresses.push_back(IOAddress("10.1.2.3"));
    addresses.push_back(IOAddress("85.26.43.234"));

    // Clear the buffer as we need to store new addresses in it.
    buf.clear();
    for (int i = 0; i < addresses.size(); ++i) {
        writeAddress(addresses[i], buf);
    }

    // Perform 'unpack'.
    ASSERT_NO_THROW(option->unpack(buf.begin(), buf.end()));

    // Now we should have only 2 data fields.
    ASSERT_EQ(2, option->getDataFieldsNum());

    // Verify that the addresses have been overwritten.
    for (int i = 0; i < 2; ++i) {
        IOAddress address("10.10.10.10");
        ASSERT_NO_THROW(option->readAddress(i, address));
        EXPECT_EQ(addresses[i].toText(), address.toText());
    }
}

// The purpose of this test is to verify that new data can be set for
// a custom option.
TEST_F(OptionCustomTest, setData) 
{
    OptionDefinition opt_def("OPTION_FOO", 1000, "ipv6-address", true);

    // Initialize reference data.
    std::vector<IOAddress> addresses;
    addresses.push_back(IOAddress("2001:db8:1::3"));
    addresses.push_back(IOAddress("::1"));
    addresses.push_back(IOAddress("fe80::3"));

    // Store the collection of IPv6 addresses into the buffer.
    OptionBuffer buf;
    for (int i = 0; i < addresses.size(); ++i) {
        writeAddress(addresses[i], buf);
    }

    // Use the input buffer to create custom option.
    boost::scoped_ptr<OptionCustom> option;
    ASSERT_NO_THROW(
        option.reset(new OptionCustom(opt_def, Option::V6, buf.begin(), buf.begin() + 50));
    );
    ASSERT_TRUE(option);

    // We should have 3 data fields.
    ASSERT_EQ(3, option->getDataFieldsNum());

    // We expect 3 IPv6 addresses being stored in the option.
    for (int i = 0; i < 3; ++i) {
        IOAddress address("fe80::4");
        ASSERT_NO_THROW(option->readAddress(i, address));
        EXPECT_EQ(addresses[i].toText(), address.toText());
    }

    // Clear addresses we had previously added.
    addresses.clear();

    // Store new addresses.
    addresses.push_back(IOAddress("::1"));
    addresses.push_back(IOAddress("fe80::10"));

    // Clear the buffer as we need to store new addresses in it.
    buf.clear();
    for (int i = 0; i < addresses.size(); ++i) {
        writeAddress(addresses[i], buf);
    }

    // Replace the option data.
    ASSERT_NO_THROW(option->setData(buf.begin(), buf.end()));

    // Now we should have only 2 data fields.
    ASSERT_EQ(2, option->getDataFieldsNum());

    // Check that it has been replaced.
    for (int i = 0; i < 2; ++i) {
        IOAddress address("10.10.10.10");
        ASSERT_NO_THROW(option->readAddress(i, address));
        EXPECT_EQ(addresses[i].toText(), address.toText());
    }
}

} // anonymous namespace
