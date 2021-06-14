// Copyright (C) 2012-2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <asiolink/io_address.h>
#include <dhcp/option_custom.h>

#include <boost/scoped_ptr.hpp>
#include <gtest/gtest.h>

using namespace isc;
using namespace isc::asiolink;
using namespace isc::dhcp;

namespace {

/// @brief Default (zero) prefix tuple.
const PrefixTuple
ZERO_PREFIX_TUPLE(std::make_pair(PrefixLen(0),
                                 IOAddress(IOAddress::IPV6_ZERO_ADDRESS())));

/// @brief OptionCustomTest test class.
class OptionCustomTest : public ::testing::Test {
public:
    /// @brief Constructor.
    OptionCustomTest() { }

    /// @brief Appends DHCPv4 suboption in the on-wire format to the buffer.
    ///
    /// @param buf A buffer to which suboption is appended.
    void appendV4Suboption(OptionBuffer& buf) {
        const uint8_t subopt_data[] = {
            0x01, 0x02, // Option type = 1, length = 2
            0x01, 0x02  // Two bytes of data
        };
        buf.insert(buf.end(), subopt_data, subopt_data + sizeof(subopt_data));
    }

    /// @brief Check if the parsed option has a suboption.
    ///
    /// @param opt An option in which suboption is expected.
    /// @return Assertion result indicating that the suboption is
    /// present (success) or missing (failure).
    ::testing::AssertionResult hasV4Suboption(OptionCustom* opt) {
        OptionPtr subopt = opt->getOption(1);
        if (!subopt) {
            return (::testing::AssertionFailure(::testing::Message()
                                                << "Suboption of OptionCustom"
                                                " is missing"));
        }
        return (::testing::AssertionSuccess());
    }

    /// @brief Appends DHCPv6 suboption in the on-wire format to the buffer.
    ///
    /// @param buf A buffer to which suboption is appended.
    void appendV6Suboption(OptionBuffer& buf) {
        const uint8_t subopt_data[] = {
            0x00, 0x01, // Option type = 1
            0x00, 0x04, // Option length = 4
            0x01, 0x02, 0x03, 0x04 // Four bytes of data
        };
        buf.insert(buf.end(), subopt_data, subopt_data + sizeof(subopt_data));
    }

    /// @brief Check if the parsed option has a suboption.
    ///
    /// @param opt An option in which suboption is expected.
    /// @return Assertion result indicating that the suboption is
    /// present (success) or missing (failure).
    ::testing::AssertionResult hasV6Suboption(OptionCustom* opt) {
        OptionPtr subopt = opt->getOption(1);
        if (!subopt) {
            return (::testing::AssertionFailure(::testing::Message()
                                                << "Suboption of OptionCustom"
                                                " is missing"));
        }
        return (::testing::AssertionSuccess());
    }

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

// The purpose of this test is to check that parameters passed to
// a custom option's constructor are used to initialize class
// members.
TEST_F(OptionCustomTest, constructor) {
    // Create option definition for a DHCPv6 option.
    OptionDefinition opt_def1("OPTION_FOO", 1000, "my-space", "boolean", true);

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
    OptionDefinition opt_def2("OPTION_FOO", 232, "my-space", "boolean");

    ASSERT_NO_THROW(
        option.reset(new OptionCustom(opt_def2, Option::V4, buf.begin(), buf.end()));
    );
    ASSERT_TRUE(option);

    EXPECT_EQ(Option::V4, option->getUniverse());
    EXPECT_EQ(232, option->getType());

    // Try to create an option using 'empty data' constructor
    OptionDefinition opt_def3("OPTION_FOO", 1000, "my-space", "uint32");

    ASSERT_NO_THROW(
        option.reset(new OptionCustom(opt_def3, Option::V6));
    );
    ASSERT_TRUE(option);

    EXPECT_EQ(Option::V6, option->getUniverse());
    EXPECT_EQ(1000, option->getType());
}

// The purpose of this test is to verify that 'empty' option definition can
// be used to create an instance of custom option.
TEST_F(OptionCustomTest, emptyData) {
    OptionDefinition opt_def("option-foo", 232, "my-space", "empty",
                             "option-foo-space");

    // Create a buffer holding 1 suboption.
    OptionBuffer buf;
    appendV4Suboption(buf);

    boost::scoped_ptr<OptionCustom> option;
    ASSERT_NO_THROW(
        option.reset(new OptionCustom(opt_def, Option::V4, buf.begin(),
                                      buf.end()));
    );

    ASSERT_TRUE(option);

    // Option is 'empty' so no data fields are expected.
    EXPECT_EQ(0, option->getDataFieldsNum());

    // Check that suboption has been parsed.
    EXPECT_TRUE(hasV4Suboption(option.get()));
}

// The purpose of this test is to verify that the option definition comprising
// a binary value can be used to create an instance of custom option.
TEST_F(OptionCustomTest, binaryData) {
    OptionDefinition opt_def("option-foo", 231, "my-space", "binary",
                             "option-foo-space");

    // Create a buffer holding some binary data. This data will be
    // used as reference when we read back the data from a created
    // option.
    OptionBuffer buf_in(14);
    for (unsigned i = 0; i < 14; ++i) {
        buf_in[i] = i;
    }

    // Append suboption data. This data should NOT be recognized when
    // option has a binary format.
    appendV4Suboption(buf_in);

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

    // Check that option with "no data" is rejected.
    buf_in.clear();
    EXPECT_THROW(
        option.reset(new OptionCustom(opt_def, Option::V4, buf_in.begin(),
                                      buf_in.end())),
        isc::OutOfRange
    );

    // Suboptions are not recognized for the binary formats because as it is
    // a variable length format. Therefore, we expect that there are no
    // suboptions in the parsed option.
    EXPECT_FALSE(option->getOption(1));
}

// The purpose of this test is to verify that an option definition comprising
// a single boolean value can be used to create an instance of custom option.
TEST_F(OptionCustomTest, booleanData) {
    OptionDefinition opt_def("option-foo", 1000, "my-space", "boolean",
                             "option-foo-space");

    OptionBuffer buf;
    // Push back the value that represents 'false'.
    buf.push_back(0);

    // Append suboption. It should be present in the parsed packet.
    appendV6Suboption(buf);

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

    // There should be one suboption present.
    EXPECT_TRUE(hasV6Suboption(option.get()));

    // Check that the option with "no data" is rejected.
    buf.clear();
    EXPECT_THROW(
        option.reset(new OptionCustom(opt_def, Option::V6, buf.begin(),
                                      buf.end())),
        isc::OutOfRange
    );
}

// The purpose of this test is to verify that the data from a buffer
// can be read as a DHCPv4 tuple.
TEST_F(OptionCustomTest, tupleData4) {
    OptionDefinition opt_def("option-foo", 232, "my-space", "tuple",
                             "option-foo-space");

    const char data[] = {
        6, 102, 111, 111, 98, 97, 114 // "foobar"
    };

    std::vector<uint8_t> buf(data, data + sizeof(data));

    // Append suboption. It should be present in the parsed packet.
    appendV4Suboption(buf);

    boost::scoped_ptr<OptionCustom> option;
    ASSERT_NO_THROW(
        option.reset(new OptionCustom(opt_def, Option::V4, buf));
    );
    ASSERT_TRUE(option);

    // We should have just one data field.
    ASSERT_EQ(1, option->getDataFieldsNum());

    // Check it
    std::string value;
    ASSERT_NO_THROW(value = option->readTuple(0));
    EXPECT_EQ("foobar", value);

    // Now as a tuple
    OpaqueDataTuple tuple(OpaqueDataTuple::LENGTH_1_BYTE);
    EXPECT_NO_THROW(option->readTuple(tuple, 0));
    EXPECT_EQ("foobar", tuple.getText());

    // There should be one suboption present.
    EXPECT_TRUE(hasV4Suboption(option.get()));

    // Check that the option with truncated data can't be created.
    EXPECT_THROW(
        option.reset(new OptionCustom(opt_def, Option::V4,
                                      buf.begin(), buf.begin() + 6)),
        isc::dhcp::BadDataTypeCast
    );

    // Check that the option with "no data" is rejected.
    buf.clear();
    EXPECT_THROW(
        option.reset(new OptionCustom(opt_def, Option::V4,
                                      buf.begin(), buf.end())),
        isc::dhcp::BadDataTypeCast
    );
}

// The purpose of this test is to verify that the data from a buffer
// can be read as a DHCPv6 tuple.
TEST_F(OptionCustomTest, tupleData6) {
    OptionDefinition opt_def("option-foo", 1000, "my-space", "tuple",
                             "option-foo-space");

    const char data[] = {
        0, 6, 102, 111, 111, 98, 97, 114 // "foobar"
    };

    std::vector<uint8_t> buf(data, data + sizeof(data));

    // Append suboption. It should be present in the parsed packet.
    appendV6Suboption(buf);

    boost::scoped_ptr<OptionCustom> option;
    ASSERT_NO_THROW(
        option.reset(new OptionCustom(opt_def, Option::V6, buf));
    );
    ASSERT_TRUE(option);

    // We should have just one data field.
    ASSERT_EQ(1, option->getDataFieldsNum());

    // Check it
    std::string value;
    ASSERT_NO_THROW(value = option->readTuple(0));
    EXPECT_EQ("foobar", value);

    // Now as a tuple
    OpaqueDataTuple tuple(OpaqueDataTuple::LENGTH_2_BYTES);
    EXPECT_NO_THROW(option->readTuple(tuple, 0));
    EXPECT_EQ("foobar", tuple.getText());

    // There should be one suboption present.
    EXPECT_TRUE(hasV6Suboption(option.get()));

    // Check that the option with truncated data can't be created.
    EXPECT_THROW(
        option.reset(new OptionCustom(opt_def, Option::V6,
                                      buf.begin(), buf.begin() + 1)),
        isc::dhcp::BadDataTypeCast
    );

    EXPECT_THROW(
        option.reset(new OptionCustom(opt_def, Option::V6,
                                      buf.begin(), buf.begin() + 7)),
        isc::dhcp::BadDataTypeCast
    );

}

// The purpose of this test is to verify that the data from a buffer
// can be read as FQDN.
TEST_F(OptionCustomTest, fqdnData) {
    OptionDefinition opt_def("option-foo", 1000, "my-space", "fqdn",
                             "option-foo-space");

    const char data[] = {
        8, 109, 121, 100, 111, 109, 97, 105, 110, // "mydomain"
        7, 101, 120, 97, 109, 112, 108, 101,      // "example"
        3, 99, 111, 109,                          // "com"
        0,
    };

    std::vector<uint8_t> buf(data, data + sizeof(data));

    // The FQDN has a certain boundary. Right after FQDN it should be
    // possible to append suboption and parse it correctly.
    appendV6Suboption(buf);

    boost::scoped_ptr<OptionCustom> option;
    ASSERT_NO_THROW(
        option.reset(new OptionCustom(opt_def, Option::V6, buf.begin(), buf.end()));
    );
    ASSERT_TRUE(option);

    ASSERT_EQ(1, option->getDataFieldsNum());

    std::string domain0 = option->readFqdn(0);
    EXPECT_EQ("mydomain.example.com.", domain0);

    // This option should have one suboption.
    EXPECT_TRUE(hasV6Suboption(option.get()));

    // Check that the option with truncated data can't be created.
    EXPECT_THROW(
        option.reset(new OptionCustom(opt_def, Option::V6,
                                      buf.begin(), buf.begin() + 4)),
        isc::dhcp::BadDataTypeCast
    );
}

// The purpose of this test is to verify that the option definition comprising
// 16-bit signed integer value can be used to create an instance of custom option.
TEST_F(OptionCustomTest, int16Data) {
    OptionDefinition opt_def("option-foo", 1000, "my-space", "int16",
                             "option-foo-space");

    OptionBuffer buf;
    // Store signed integer value in the input buffer.
    writeInt<int16_t>(-234, buf);

    // Append suboption.
    appendV6Suboption(buf);

    // Create custom option.
    boost::scoped_ptr<OptionCustom> option;
    ASSERT_NO_THROW(
        option.reset(new OptionCustom(opt_def, Option::V6, buf));
    );
    ASSERT_TRUE(option);

    // We should have just one data field.
    ASSERT_EQ(1, option->getDataFieldsNum());

    // Initialize value to 0 explicitly to make sure that is
    // modified by readInteger function to expected -234.
    int16_t value = 0;
    ASSERT_NO_THROW(value = option->readInteger<int16_t>(0));
    EXPECT_EQ(-234, value);

    // Parsed option should have one suboption.
    EXPECT_TRUE(hasV6Suboption(option.get()));

    // Check that the option is not created when a buffer is
    // too short (1 byte instead of 2 bytes).
    EXPECT_THROW(
        option.reset(new OptionCustom(opt_def, Option::V6, buf.begin(), buf.begin() + 1)),
        isc::OutOfRange
    );
}

// The purpose of this test is to verify that the option definition comprising
// 32-bit signed integer value can be used to create an instance of custom option.
TEST_F(OptionCustomTest, int32Data) {
    OptionDefinition opt_def("option-foo", 1000, "my-space", "int32",
                             "option-foo-space");

    OptionBuffer buf;
    writeInt<int32_t>(-234, buf);

    // Append one suboption.
    appendV6Suboption(buf);

    // Create custom option.
    boost::scoped_ptr<OptionCustom> option;
    ASSERT_NO_THROW(
        option.reset(new OptionCustom(opt_def, Option::V6, buf));
    );
    ASSERT_TRUE(option);

    // We should have just one data field.
    ASSERT_EQ(1, option->getDataFieldsNum());

    // Initialize value to 0 explicitly to make sure that is
    // modified by readInteger function to expected -234.
    int32_t value = 0;
    ASSERT_NO_THROW(value = option->readInteger<int32_t>(0));
    EXPECT_EQ(-234, value);

    // The parsed option should have one suboption.
    EXPECT_TRUE(hasV6Suboption(option.get()));

    // Check that the option is not created when a buffer is
    // too short (3 bytes instead of 4 bytes).
    EXPECT_THROW(
        option.reset(new OptionCustom(opt_def, Option::V6, buf.begin(), buf.begin() + 3)),
        isc::OutOfRange
    );
}

// The purpose of this test is to verify that the option definition comprising
// single IPv4 address can be used to create an instance of custom option.
TEST_F(OptionCustomTest, ipv4AddressData) {
    OptionDefinition opt_def("OPTION_FOO", 231, "my-space", "ipv4-address",
                             "option-foo-space");

    // Create input buffer.
    OptionBuffer buf;
    writeAddress(IOAddress("192.168.100.50"), buf);

    // Append one suboption.
    appendV4Suboption(buf);

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
    ASSERT_NO_THROW(address = option->readAddress(0));

    EXPECT_EQ("192.168.100.50", address.toText());

    // Parsed option should have one suboption.
    EXPECT_TRUE(hasV4Suboption(option.get()));

    // Check that option is not created if the provided buffer is
    // too short (use 3 bytes instead of 4).
    EXPECT_THROW(
        option.reset(new OptionCustom(opt_def, Option::V4, buf.begin(), buf.begin() + 3)),
        isc::OutOfRange
    );
}

// The purpose of this test is to verify that the option definition comprising
// single IPv6 address can be used to create an instance of custom option.
TEST_F(OptionCustomTest, ipv6AddressData) {
    OptionDefinition opt_def("option-foo", 1000, "my-space", "ipv6-address",
                             "option-foo-space");

    // Initialize input buffer.
    OptionBuffer buf;
    writeAddress(IOAddress("2001:db8:1::100"), buf);

    // Append suboption.
    appendV6Suboption(buf);

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
    ASSERT_NO_THROW(address = option->readAddress(0));

    EXPECT_EQ("2001:db8:1::100", address.toText());

    // Parsed option should have one suboption.
    EXPECT_TRUE(hasV6Suboption(option.get()));

    // Check that option is not created if the provided buffer is
    // too short (use 15 bytes instead of 16).
    EXPECT_THROW(
        option.reset(new OptionCustom(opt_def, Option::V6, buf.begin(),
                                      buf.begin() + 15)),
        isc::OutOfRange
    );
}

// The purpose of this test is to verify that the option definition comprising
// single variable length prefix can be used to create an instance of custom
// option.
TEST_F(OptionCustomTest, prefixData) {
    OptionDefinition opt_def("option-foo", 1000, "my-space", "ipv6-prefix",
                             "option-foo-space");

    // Initialize input buffer.
    OptionBuffer buf;
    writeInt<uint8_t>(32, buf);
    writeInt<uint32_t>(0x30000001, buf);

    // Append suboption.
    appendV6Suboption(buf);

    // Create custom option using input buffer.
    boost::scoped_ptr<OptionCustom> option;
    ASSERT_NO_THROW(
        option.reset(new OptionCustom(opt_def, Option::V6, buf));
    );
    ASSERT_TRUE(option);

    // We should have just one data field.
    ASSERT_EQ(1, option->getDataFieldsNum());

    // Custom option should comprise exactly one buffer that represents
    // a prefix.
    PrefixTuple prefix(ZERO_PREFIX_TUPLE);
    // Read prefix from buffer #0.
    ASSERT_NO_THROW(prefix = option->readPrefix(0));

    // The prefix comprises a prefix length and prefix value.
    EXPECT_EQ(32, prefix.first.asUnsigned());
    EXPECT_EQ("3000:1::", prefix.second.toText());

    // Parsed option should have one suboption.
    EXPECT_TRUE(hasV6Suboption(option.get()));
}

// The purpose of this test is to verify that the option definition comprising
// single PSID can be used to create an instance of custom option.
TEST_F(OptionCustomTest, psidData) {
    OptionDefinition opt_def("option-foo", 1000, "my-space", "psid",
                             "option-foo-space");

    // Initialize input buffer.
    OptionBuffer buf;
    writeInt<uint8_t>(4, buf);
    writeInt<uint16_t>(0x8000, buf);

    // Append suboption.
    appendV6Suboption(buf);

    // Create custom option using input buffer.
    boost::scoped_ptr<OptionCustom> option;
    ASSERT_NO_THROW(
        option.reset(new OptionCustom(opt_def, Option::V6, buf));
    );
    ASSERT_TRUE(option);

    // We should have just one data field.
    ASSERT_EQ(1, option->getDataFieldsNum());

    // Custom option should comprise exactly one buffer that represents
    // a PSID length / PSID value tuple.
    PSIDTuple psid;
    // Read PSID length / PSID value from buffer #0.
    ASSERT_NO_THROW(psid = option->readPsid(0));

    // The PSID comprises a PSID length and PSID value.
    EXPECT_EQ(4, psid.first.asUnsigned());
    EXPECT_EQ(0x08, psid.second.asUint16());

    // Parsed option should have one suboption.
    EXPECT_TRUE(hasV6Suboption(option.get()));
}

// The purpose of this test is to verify that the option definition comprising
// string value can be used to create an instance of custom option.
TEST_F(OptionCustomTest, stringData) {
    OptionDefinition opt_def("option-foo", 1000, "my-space", "string",
                             "option-foo-space");

    // Create an input buffer holding some string value.
    OptionBuffer buf;
    writeString("hello world!", buf);

    // Append suboption. It should not be detected because the string field
    //  has variable length.
    appendV6Suboption(buf);

    // Append suboption. Since the option has variable length string field,
    // the suboption should not be recognized.

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
    ASSERT_NO_THROW(value = option->readString(0));

    // The initial part of the string should contain the actual string.
    // The rest of it is a garbage from an attempt to decode suboption
    // as a string.
    ASSERT_EQ(20, value.size());
    EXPECT_EQ("hello world!", value.substr(0, 12));

    // No suboption should be present.
    EXPECT_FALSE(option->getOption(1));

    // Check that option will not be created if empty buffer is provided.
    buf.clear();
    EXPECT_THROW(
        option.reset(new OptionCustom(opt_def, Option::V6, buf.begin(), buf.end())),
        isc::OutOfRange
    );
}

// The purpose of this test is to verify that the option definition comprising
// an array of boolean values can be used to create an instance of custom option.
TEST_F(OptionCustomTest, booleanDataArray) {
    OptionDefinition opt_def("option-foo", 1000, "my-space", "boolean", true);

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

    // Check that empty buffer can't be used to create option holding
    // array of boolean values.
    buf.clear();
    EXPECT_THROW(
         option.reset(new OptionCustom(opt_def, Option::V6, buf.begin(), buf.end())),
         isc::OutOfRange
    );
}

// The purpose of this test is to verify that the option definition comprising
// an array of 32-bit signed integer values can be used to create an instance
// of custom option.
TEST_F(OptionCustomTest, uint32DataArray) {
    OptionDefinition opt_def("option-foo", 1000, "my-space", "uint32", true);

    // Create an input buffer that holds 4 uint32 values that
    // represent an array.
    std::vector<uint32_t> values;
    values.push_back(71234);
    values.push_back(12234);
    values.push_back(54362);
    values.push_back(1234);

    // Store these values in a buffer.
    OptionBuffer buf;
    for (size_t i = 0; i < values.size(); ++i) {
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

    // Check that too short buffer can't be used to create the option.
    // Using buffer having length of 3 bytes. The length of 4 bytes is
    // a minimal length to create the option with single uint32_t value.
    EXPECT_THROW(
        option.reset(new OptionCustom(opt_def, Option::V6, buf.begin(),
                                      buf.begin() + 3)),
        isc::OutOfRange
    );
}

// The purpose of this test is to verify that the option definition comprising
// an array of IPv4 addresses can be used to create an instance of custom option.
TEST_F(OptionCustomTest, ipv4AddressDataArray) {
    OptionDefinition opt_def("OPTION_FOO", 231, "my-space", "ipv4-address",
                             true);

    // Initialize reference data.
    std::vector<IOAddress> addresses;
    addresses.push_back(IOAddress("192.168.0.1"));
    addresses.push_back(IOAddress("127.0.0.1"));
    addresses.push_back(IOAddress("10.10.1.2"));

    // Store the collection of IPv4 addresses into the buffer.
    OptionBuffer buf;
    for (size_t i = 0; i < addresses.size(); ++i) {
        writeAddress(addresses[i], buf);
    }

    // Use the input buffer to create custom option.
    boost::scoped_ptr<OptionCustom> option;
    ASSERT_NO_THROW(
        option.reset(new OptionCustom(opt_def, Option::V4, buf));
    );
    ASSERT_TRUE(option);

    // We should have 3 data fields.
    ASSERT_EQ(3, option->getDataFieldsNum());

    // We expect 3 IPv4 addresses being stored in the option.
    for (int i = 0; i < 3; ++i) {
        IOAddress address("10.10.10.10");
        ASSERT_NO_THROW(address = option->readAddress(i));
        EXPECT_EQ(addresses[i], address);
    }

    // Check that it is ok if buffer length is not a multiple of IPv4
    // address length. Resize it by two bytes.
    buf.resize(buf.size() + 2);
    EXPECT_NO_THROW(
        option.reset(new OptionCustom(opt_def, Option::V4, buf));
    );

    // Check that option is not created when the provided buffer
    // is too short. At least a buffer length of 4 bytes is needed.
    EXPECT_THROW(
        option.reset(new OptionCustom(opt_def, Option::V4, buf.begin(),
                                      buf.begin() + 2)),
        isc::OutOfRange
    );
}

// The purpose of this test is to verify that the option definition comprising
// an array of IPv6 addresses can be used to create an instance of custom option.
TEST_F(OptionCustomTest, ipv6AddressDataArray) {
    OptionDefinition opt_def("OPTION_FOO", 1000, "my-space", "ipv6-address",
                             true);

    // Initialize reference data.
    std::vector<IOAddress> addresses;
    addresses.push_back(IOAddress("2001:db8:1::3"));
    addresses.push_back(IOAddress("::1"));
    addresses.push_back(IOAddress("fe80::3"));

    // Store the collection of IPv6 addresses into the buffer.
    OptionBuffer buf;
    for (size_t i = 0; i < addresses.size(); ++i) {
        writeAddress(addresses[i], buf);
    }

    // Use the input buffer to create custom option.
    boost::scoped_ptr<OptionCustom> option;
    ASSERT_NO_THROW(
        option.reset(new OptionCustom(opt_def, Option::V6, buf));
    );
    ASSERT_TRUE(option);

    // We should have 3 data fields.
    ASSERT_EQ(3, option->getDataFieldsNum());

    // We expect 3 IPv6 addresses being stored in the option.
    for (int i = 0; i < 3; ++i) {
        IOAddress address("fe80::4");
        ASSERT_NO_THROW(address = option->readAddress(i));
        EXPECT_EQ(addresses[i], address);
    }

    // Check that it is ok if buffer length is not a multiple of IPv6
    // address length. Resize it by two bytes.
    buf.resize(buf.size() + 2);
    EXPECT_NO_THROW(
        option.reset(new OptionCustom(opt_def, Option::V6, buf));
    );

    // Check that option is not created when the provided buffer
    // is too short. At least a buffer length of 16 bytes is needed.
    EXPECT_THROW(
        option.reset(new OptionCustom(opt_def, Option::V6, buf.begin(),
                                      buf.begin() + 15)),
        isc::OutOfRange
    );
}

// The purpose of this test is to verify that the option comprising
// an array of FQDN values can be created from a buffer which holds
// multiple FQDN values encoded as described in the RFC1035, section
// 3.1
TEST_F(OptionCustomTest, fqdnDataArray) {
    OptionDefinition opt_def("OPTION_FOO", 1000, "my-space", "fqdn", true);

    const char data[] = {
        8, 109, 121, 100, 111, 109, 97, 105, 110, // "mydomain"
        7, 101, 120, 97, 109, 112, 108, 101,      // "example"
        3, 99, 111, 109,                          // "com"
        0,
        7, 101, 120, 97, 109, 112, 108, 101,      // "example"
        3, 99, 111, 109,                          // "com"
        0
    };

    // Create a buffer that holds two FQDNs.
    std::vector<uint8_t> buf(data, data + sizeof(data));

    // Create an option from using a buffer.
    boost::scoped_ptr<OptionCustom> option;
    ASSERT_NO_THROW(
        option.reset(new OptionCustom(opt_def, Option::V6, buf));
    );
    ASSERT_TRUE(option);

    // We expect that two FQDN values have been extracted
    // from a buffer.
    ASSERT_EQ(2, option->getDataFieldsNum());

    // Validate both values.
    std::string domain0 = option->readFqdn(0);
    EXPECT_EQ("mydomain.example.com.", domain0);

    std::string domain1 = option->readFqdn(1);
    EXPECT_EQ("example.com.", domain1);
}

// The purpose of this test is to verify that the option definition comprising
// an array of IPv6 prefixes can be used to create an instance of OptionCustom.
TEST_F(OptionCustomTest, prefixDataArray) {
    OptionDefinition opt_def("option-foo", 1000, "my-space", "ipv6-prefix",
                             true);

    // The following buffer comprises three prefixes with different
    // prefix lengths.
    const uint8_t data[] = {
        32, 0x30, 0x01, 0x00, 0x01,             // 3001:1::/32
        16, 0x30, 0x00,                         // 3000::/16
        48, 0x20, 0x01, 0x0d, 0xb8, 0x00, 0x01  // 2001:db8:1::/48
    };

    // Initialize input buffer
    OptionBuffer buf(data,
                     data + static_cast<size_t>(sizeof(data) / sizeof(char)));

    // Create custom option using input buffer.
    boost::scoped_ptr<OptionCustom> option;
    ASSERT_NO_THROW(
        option.reset(new OptionCustom(opt_def, Option::V6, buf));
    );
    ASSERT_TRUE(option);

    // We should have 3 data fields with 3 prefixes.
    ASSERT_EQ(3, option->getDataFieldsNum());

    PrefixTuple prefix0(ZERO_PREFIX_TUPLE);
    PrefixTuple prefix1(ZERO_PREFIX_TUPLE);
    PrefixTuple prefix2(ZERO_PREFIX_TUPLE);

    ASSERT_NO_THROW(prefix0 = option->readPrefix(0));
    ASSERT_NO_THROW(prefix1 = option->readPrefix(1));
    ASSERT_NO_THROW(prefix2 = option->readPrefix(2));

    EXPECT_EQ(32, prefix0.first.asUnsigned());
    EXPECT_EQ("3001:1::", prefix0.second.toText());

    EXPECT_EQ(16, prefix1.first.asUnsigned());
    EXPECT_EQ("3000::", prefix1.second.toText());

    EXPECT_EQ(48, prefix2.first.asUnsigned());
    EXPECT_EQ("2001:db8:1::", prefix2.second.toText());
}

// The purpose of this test is to verify that the option definition comprising
// an array of PSIDs can be used to create an instance of OptionCustom.
TEST_F(OptionCustomTest, psidDataArray) {
    OptionDefinition opt_def("option-foo", 1000, "my-space", "psid", true);

    // The following buffer comprises three PSIDs.
    const uint8_t data[] = {
        4, 0x80, 0x00,    // PSID len = 4, PSID = '1000 000000000000b'
        6, 0xD4, 0x00,    // PSID len = 6, PSID = '110101 0000000000b'
        1, 0x80, 0x00     // PSID len = 1, PSID = '1 000000000000000b'
    };
    // Initialize input buffer.
    OptionBuffer buf(data,
                     data + static_cast<size_t>(sizeof(data) / sizeof(char)));

    // Create custom option using input buffer.
    boost::scoped_ptr<OptionCustom> option;
    ASSERT_NO_THROW(
        option.reset(new OptionCustom(opt_def, Option::V6, buf));
    );
    ASSERT_TRUE(option);

    // We should have 3 data fields with 3 PSIDs.
    ASSERT_EQ(3, option->getDataFieldsNum());

    PSIDTuple psid0;
    PSIDTuple psid1;
    PSIDTuple psid2;

    ASSERT_NO_THROW(psid0 = option->readPsid(0));
    ASSERT_NO_THROW(psid1 = option->readPsid(1));
    ASSERT_NO_THROW(psid2 = option->readPsid(2));

    // PSID value is equal to '1000b' (8).
    EXPECT_EQ(4, psid0.first.asUnsigned());
    EXPECT_EQ(0x08, psid0.second.asUint16());

    // PSID value is equal to '110101b' (0x35).
    EXPECT_EQ(6, psid1.first.asUnsigned());
    EXPECT_EQ(0x35, psid1.second.asUint16());

    // PSID value is equal to '1b' (1).
    EXPECT_EQ(1, psid2.first.asUnsigned());
    EXPECT_EQ(0x01, psid2.second.asUint16());
}

// The purpose of this test is to verify that the data from a buffer
// can be read as DHCPv4 tuples.
TEST_F(OptionCustomTest, tupleDataArray4) {
    OptionDefinition opt_def("option-foo", 232, "my-space", "tuple", true);

    const char data[] = {
        5, 104, 101, 108, 108, 111, // "hello"
        1, 32,                      // " "
        5, 119, 111, 114, 108, 100   // "world"
    };

    std::vector<uint8_t> buf(data, data + sizeof(data));

    boost::scoped_ptr<OptionCustom> option;
    ASSERT_NO_THROW(
        option.reset(new OptionCustom(opt_def, Option::V4, buf));
    );
    ASSERT_TRUE(option);

    // We should have 3 data fields
    ASSERT_EQ(3, option->getDataFieldsNum());

    // Check them
    std::string value;
    ASSERT_NO_THROW(value = option->readTuple(0));
    EXPECT_EQ("hello", value);
    ASSERT_NO_THROW(value = option->readTuple(1));
    EXPECT_EQ(" ", value);
    ASSERT_NO_THROW(value = option->readTuple(2));
    EXPECT_EQ("world", value);

    // There should be no suboption present.
    EXPECT_FALSE(hasV4Suboption(option.get()));

    // Check that the option with truncated data can't be created.
    EXPECT_THROW(
        option.reset(new OptionCustom(opt_def, Option::V4,
                                      buf.begin(), buf.begin() + 12)),
        isc::dhcp::BadDataTypeCast
    );
}

// The purpose of this test is to verify that the data from a buffer
// can be read as DHCPv6 tuples.
TEST_F(OptionCustomTest, tupleDataArray6) {
    OptionDefinition opt_def("option-foo", 1000, "my-space", "tuple", true);

    const char data[] = {
        0, 5, 104, 101, 108, 108, 111, // "hello"
        0, 1, 32,                      // " "
        0, 5, 119, 111, 114, 108, 100   // "world"
    };

    std::vector<uint8_t> buf(data, data + sizeof(data));

    boost::scoped_ptr<OptionCustom> option;
    ASSERT_NO_THROW(
        option.reset(new OptionCustom(opt_def, Option::V6, buf));
    );
    ASSERT_TRUE(option);

    // We should have 3 data fields
    ASSERT_EQ(3, option->getDataFieldsNum());

    // Check them
    std::string value;
    ASSERT_NO_THROW(value = option->readTuple(0));
    EXPECT_EQ("hello", value);
    ASSERT_NO_THROW(value = option->readTuple(1));
    EXPECT_EQ(" ", value);
    ASSERT_NO_THROW(value = option->readTuple(2));
    EXPECT_EQ("world", value);

    // There should be no suboption present.
    EXPECT_FALSE(hasV6Suboption(option.get()));

    // Check that the option with truncated data can't be created.
    EXPECT_THROW(
        option.reset(new OptionCustom(opt_def, Option::V6,
                                      buf.begin(), buf.begin() + 8)),
        isc::dhcp::BadDataTypeCast
    );

    EXPECT_THROW(
        option.reset(new OptionCustom(opt_def, Option::V6,
                                      buf.begin(), buf.begin() + 16)),
        isc::dhcp::BadDataTypeCast
    );
}

// The purpose of this test is to verify that the option definition comprising
// a record of fixed-size fields can be used to create an option with a
// suboption.
TEST_F(OptionCustomTest, recordDataWithSuboption) {
    OptionDefinition opt_def("option-foo", 1000, "my-space", "record",
                             "option-foo-space");
    ASSERT_NO_THROW(opt_def.addRecordField("uint32"));
    ASSERT_NO_THROW(opt_def.addRecordField("ipv4-address"));

    // Create a buffer with two fields: 4-byte number and IPv4 address.
    OptionBuffer buf;
    writeInt<uint32_t>(0x01020304, buf);
    writeAddress(IOAddress("192.168.0.1"), buf);

    // Append a suboption. It should be correctly parsed because option fields
    // preceding this option have fixed (known) size.
    appendV6Suboption(buf);

    boost::scoped_ptr<OptionCustom> option;
    ASSERT_NO_THROW(
         option.reset(new OptionCustom(opt_def, Option::V6, buf.begin(),
                                       buf.end()));
    );
    ASSERT_TRUE(option);

    // We should have two data fields parsed.
    ASSERT_EQ(2, option->getDataFieldsNum());

    // Validate values in fields.
    uint32_t value0 = 0;
    ASSERT_NO_THROW(value0 = option->readInteger<uint32_t>(0));
    EXPECT_EQ(0x01020304, value0);

    IOAddress value1 = 0;
    ASSERT_NO_THROW(value1 = option->readAddress(1));
    EXPECT_EQ("192.168.0.1", value1.toText());

    // Parsed option should have one suboption.
    EXPECT_TRUE(hasV6Suboption(option.get()));

}

// The purpose of this test is to verify that the option definition comprising
// a record of various data fields can be used to create an instance of
// custom option.
TEST_F(OptionCustomTest, recordData) {
    // Create the definition of an option which comprises
    // a record of fields of different types.
    OptionDefinition opt_def("OPTION_FOO", 1000, "my-space", "record");
    ASSERT_NO_THROW(opt_def.addRecordField("uint16"));
    ASSERT_NO_THROW(opt_def.addRecordField("boolean"));
    ASSERT_NO_THROW(opt_def.addRecordField("fqdn"));
    ASSERT_NO_THROW(opt_def.addRecordField("ipv4-address"));
    ASSERT_NO_THROW(opt_def.addRecordField("ipv6-address"));
    ASSERT_NO_THROW(opt_def.addRecordField("psid"));
    ASSERT_NO_THROW(opt_def.addRecordField("string"));

    const char fqdn_data[] = {
        8, 109, 121, 100, 111, 109, 97, 105, 110, // "mydomain"
        7, 101, 120, 97, 109, 112, 108, 101,      // "example"
        3, 99, 111, 109,                          // "com"
        0,
    };

    OptionBuffer buf;
    // Initialize field 0 to 8712.
    writeInt<uint16_t>(8712, buf);
    // Initialize field 1 to 'true'
    buf.push_back(static_cast<unsigned short>(1));
    // Initialize field 2 to 'mydomain.example.com'.
    buf.insert(buf.end(), fqdn_data, fqdn_data + sizeof(fqdn_data));
    // Initialize field 3 to IPv4 address.
    writeAddress(IOAddress("192.168.0.1"), buf);
    // Initialize field 4 to IPv6 address.
    writeAddress(IOAddress("2001:db8:1::1"), buf);
    // Initialize field 5 PSID len and PSID value.
    writeInt<uint8_t>(6, buf);
    writeInt<uint16_t>(0xD400, buf);
    // Initialize field 6 to string value.
    writeString("ABCD", buf);

    boost::scoped_ptr<OptionCustom> option;
    ASSERT_NO_THROW(
         option.reset(new OptionCustom(opt_def, Option::V6, buf.begin(), buf.end()));
    );
    ASSERT_TRUE(option);

    // We should have 6 data fields.
    ASSERT_EQ(7, option->getDataFieldsNum());

    // Verify value in the field 0.
    uint16_t value0 = 0;
    ASSERT_NO_THROW(value0 = option->readInteger<uint16_t>(0));
    EXPECT_EQ(8712, value0);

    // Verify value in the field 1.
    bool value1 = false;
    ASSERT_NO_THROW(value1 = option->readBoolean(1));
    EXPECT_TRUE(value1);

    // Verify value in the field 2.
    std::string value2 = "";
    ASSERT_NO_THROW(value2 = option->readFqdn(2));
    EXPECT_EQ("mydomain.example.com.", value2);

    // Verify value in the field 3.
    IOAddress value3("127.0.0.1");
    ASSERT_NO_THROW(value3 = option->readAddress(3));
    EXPECT_EQ("192.168.0.1", value3.toText());

    // Verify value in the field 4.
    IOAddress value4("::1");
    ASSERT_NO_THROW(value4 = option->readAddress(4));
    EXPECT_EQ("2001:db8:1::1", value4.toText());

    // Verify value in the field 5.
    PSIDTuple value5;
    ASSERT_NO_THROW(value5 = option->readPsid(5));
    EXPECT_EQ(6, value5.first.asUnsigned());
    EXPECT_EQ(0x35, value5.second.asUint16());

    // Verify value in the field 6.
    std::string value6;
    ASSERT_NO_THROW(value6 = option->readString(6));
    EXPECT_EQ("ABCD", value6);
}

// The purpose of this test is to verify that the option definition comprising
// a record of various data fields with an array for the last can be used
// to create an instance of custom option.
TEST_F(OptionCustomTest, recordArrayData) {
    // Create the definition of an option which comprises
    // a record of fields of different types.
    OptionDefinition opt_def("OPTION_FOO", 1000, "my-space", "record", true);
    ASSERT_NO_THROW(opt_def.addRecordField("uint16"));
    ASSERT_NO_THROW(opt_def.addRecordField("boolean"));
    ASSERT_NO_THROW(opt_def.addRecordField("fqdn"));
    ASSERT_NO_THROW(opt_def.addRecordField("ipv4-address"));
    ASSERT_NO_THROW(opt_def.addRecordField("ipv6-address"));
    ASSERT_NO_THROW(opt_def.addRecordField("psid"));
    ASSERT_NO_THROW(opt_def.addRecordField("uint32"));

    const char fqdn_data[] = {
        8, 109, 121, 100, 111, 109, 97, 105, 110, // "mydomain"
        7, 101, 120, 97, 109, 112, 108, 101,      // "example"
        3, 99, 111, 109,                          // "com"
        0,
    };

    OptionBuffer buf;
    // Initialize field 0 to 8712.
    writeInt<uint16_t>(8712, buf);
    // Initialize field 1 to 'true'
    writeInt<uint8_t>(1, buf);
    // Initialize field 2 to 'mydomain.example.com'.
    buf.insert(buf.end(), fqdn_data, fqdn_data + sizeof(fqdn_data));
    // Initialize field 3 to IPv4 address.
    writeAddress(IOAddress("192.168.0.1"), buf);
    // Initialize field 4 to IPv6 address.
    writeAddress(IOAddress("2001:db8:1::1"), buf);
    // Initialize field 5 PSID len and PSID value.
    writeInt<uint8_t>(6, buf);
    writeInt<uint16_t>(0xD400, buf);
    // Initialize last field 6 to a pair of int 12345678 and 87654321.
    writeInt<uint32_t>(12345678, buf);
    writeInt<uint32_t>(87654321, buf);

    boost::scoped_ptr<OptionCustom> option;
    ASSERT_NO_THROW(
         option.reset(new OptionCustom(opt_def, Option::V6, buf.begin(), buf.end()));
    );
    ASSERT_TRUE(option);

    // We should have 7+1 data fields.
    ASSERT_EQ(8, option->getDataFieldsNum());

    // Verify value in the field 0.
    uint16_t value0 = 0;
    ASSERT_NO_THROW(value0 = option->readInteger<uint16_t>(0));
    EXPECT_EQ(8712, value0);

    // Verify value in the field 1.
    bool value1 = false;
    ASSERT_NO_THROW(value1 = option->readBoolean(1));
    EXPECT_TRUE(value1);

    // Verify value in the field 2.
    std::string value2 = "";
    ASSERT_NO_THROW(value2 = option->readFqdn(2));
    EXPECT_EQ("mydomain.example.com.", value2);

    // Verify value in the field 3.
    IOAddress value3("127.0.0.1");
    ASSERT_NO_THROW(value3 = option->readAddress(3));
    EXPECT_EQ("192.168.0.1", value3.toText());

    // Verify value in the field 4.
    IOAddress value4("::1");
    ASSERT_NO_THROW(value4 = option->readAddress(4));
    EXPECT_EQ("2001:db8:1::1", value4.toText());

    // Verify value in the field 5.
    PSIDTuple value5;
    ASSERT_NO_THROW(value5 = option->readPsid(5));
    EXPECT_EQ(6, value5.first.asUnsigned());
    EXPECT_EQ(0x35, value5.second.asUint16());

    // Verify value in the field 6.
    uint32_t value6;
    ASSERT_NO_THROW(value6 = option->readInteger<uint32_t>(6));
    EXPECT_EQ(12345678, value6);

    // Verify value in the extra field 7.
    uint32_t value7;
    ASSERT_NO_THROW(value7 = option->readInteger<uint32_t>(7));
    EXPECT_EQ(87654321, value7);
}

// The purpose of this test is to verify that truncated buffer
// can't be used to create an option being a record of value of
// different types.
TEST_F(OptionCustomTest, recordDataTruncated) {
    // Create the definition of an option which comprises
    // a record of fields of different types.
    OptionDefinition opt_def("OPTION_FOO", 1000, "my-space", "record");
    ASSERT_NO_THROW(opt_def.addRecordField("uint16"));
    ASSERT_NO_THROW(opt_def.addRecordField("ipv6-address"));
    ASSERT_NO_THROW(opt_def.addRecordField("string"));

    OptionBuffer buf;
    // Initialize field 0.
    writeInt<uint16_t>(8712, buf);
    // Initialize field 1 to IPv6 address.
    writeAddress(IOAddress("2001:db8:1::1"), buf);
    // Initialize field 2 to string value.
    writeString("ABCD", buf);

    boost::scoped_ptr<OptionCustom> option;

    // Constructor should not throw exception here because the length of the
    // buffer meets the minimum length. The first 19 bytes hold data for
    // all option fields: uint16, IPv4 address and first letter of string.
    // Note that string will be truncated but this is acceptable because
    // constructor have no way to determine the length of the original string.
    EXPECT_NO_THROW(
        option.reset(new OptionCustom(opt_def, Option::V6, buf.begin(), buf.begin() + 19));
    );

    // Reduce the buffer length by one byte should cause the constructor
    // to fail. This is because 18 bytes can only hold first two data fields:
    // 2 bytes of uint16_t value and IPv6 address. Option definitions specifies
    // 3 data fields for this option but the length of the data is insufficient
    // to initialize 3 data field.

    // @todo:
    // Currently the code was modified to allow empty string or empty binary data
    // Potentially change this back to EXPECT_THROW(..., OutOfRange) once we
    // decide how to treat zero length strings and binary data (they are typically
    // valid or invalid on a per option basis, so there likely won't be a single
    // one answer to all)
    EXPECT_NO_THROW(
        option.reset(new OptionCustom(opt_def, Option::V6, buf.begin(), buf.begin() + 18))
    );

    // Try to further reduce the length of the buffer to make it insufficient
    // to even initialize the second data field.
    EXPECT_THROW(
        option.reset(new OptionCustom(opt_def, Option::V6, buf.begin(), buf.begin() + 17)),
        isc::OutOfRange
    );
}

// The purpose of this test is to verify that an option comprising
// single data field with binary data can be used and that this
// binary data is properly initialized to a default value. This
// test also checks that it is possible to override this default
// value.
TEST_F(OptionCustomTest, setBinaryData) {
    OptionDefinition opt_def("OPTION_FOO", 1000, "my-space", "binary");

    // Create an option and let the data field be initialized
    // to default value (do not provide any data buffer).
    boost::scoped_ptr<OptionCustom> option;
    ASSERT_NO_THROW(
        option.reset(new OptionCustom(opt_def, Option::V6));
    );
    ASSERT_TRUE(option);

    // Get the default binary value.
    OptionBuffer buf;
    ASSERT_NO_THROW(option->readBinary());
    // The buffer is by default empty.
    EXPECT_TRUE(buf.empty());
    // Prepare input buffer with some dummy data.
    OptionBuffer buf_in(10);
    for (size_t i = 0; i < buf_in.size(); ++i) {
        buf_in[i] = i;
    }
    // Try to override the default binary buffer.
    ASSERT_NO_THROW(option->writeBinary(buf_in));
    // And check that it has been actually overridden.
    ASSERT_NO_THROW(buf = option->readBinary());
    ASSERT_EQ(buf_in.size(), buf.size());
    EXPECT_TRUE(std::equal(buf_in.begin(), buf_in.end(), buf.begin()));
}

// The purpose of this test is to verify that an option comprising
// single boolean data field can be created and that its default
// value can be overridden by a new value.
TEST_F(OptionCustomTest, setBooleanData) {
    OptionDefinition opt_def("OPTION_FOO", 1000, "my-space", "boolean");

    // Create an option and let the data field be initialized
    // to default value (do not provide any data buffer).
    boost::scoped_ptr<OptionCustom> option;
    ASSERT_NO_THROW(
        option.reset(new OptionCustom(opt_def, Option::V6));
    );
    ASSERT_TRUE(option);
    // Check that the default boolean value is false.
    bool value = false;
    ASSERT_NO_THROW(value = option->readBoolean());
    EXPECT_FALSE(value);
    // Check that we can override the default value.
    ASSERT_NO_THROW(option->writeBoolean(true));
    // Finally, check that it has been actually overridden.
    ASSERT_NO_THROW(value = option->readBoolean());
    EXPECT_TRUE(value);
}

/// The purpose of this test is to verify that the data field value
/// can be overridden by a new value.
TEST_F(OptionCustomTest, setUint32Data) {
    // Create a definition of an option that holds single
    // uint32 value.
    OptionDefinition opt_def("OPTION_FOO", 1000, "my-space", "uint32");

    // Create an option and let the data field be initialized
    // to default value (do not provide any data buffer).
    boost::scoped_ptr<OptionCustom> option;
    ASSERT_NO_THROW(
        option.reset(new OptionCustom(opt_def, Option::V6));
    );
    ASSERT_TRUE(option);

    // The default value for integer data fields is 0.
    uint32_t value = 0;
    ASSERT_NO_THROW(option->readInteger<uint32_t>());
    EXPECT_EQ(0, value);

    // Try to set the data field value to something different
    // than 0.
    ASSERT_NO_THROW(option->writeInteger<uint32_t>(1234));

    // Verify that it has been set.
    ASSERT_NO_THROW(value = option->readInteger<uint32_t>());
    EXPECT_EQ(1234, value);
}

// The purpose of this test is to verify that an option comprising
// single IPv4 address can be created and that this address can
// be overridden by a new value.
TEST_F(OptionCustomTest, setIpv4AddressData) {
    OptionDefinition opt_def("OPTION_FOO", 232, "my-space", "ipv4-address");

    // Create an option and let the data field be initialized
    // to default value (do not provide any data buffer).
    boost::scoped_ptr<OptionCustom> option;
    ASSERT_NO_THROW(
        option.reset(new OptionCustom(opt_def, Option::V4));
    );
    ASSERT_TRUE(option);

    asiolink::IOAddress address("127.0.0.1");
    ASSERT_NO_THROW(address = option->readAddress());
    EXPECT_EQ("0.0.0.0", address.toText());

    EXPECT_NO_THROW(option->writeAddress(IOAddress("192.168.0.1")));

    EXPECT_NO_THROW(address = option->readAddress());
    EXPECT_EQ("192.168.0.1", address.toText());
}

// The purpose of this test is to verify that an option comprising
// single IPv6 address can be created and that this address can
// be overridden by a new value.
TEST_F(OptionCustomTest, setIpv6AddressData) {
    OptionDefinition opt_def("OPTION_FOO", 1000, "my-space", "ipv6-address");

    // Create an option and let the data field be initialized
    // to default value (do not provide any data buffer).
    boost::scoped_ptr<OptionCustom> option;
    ASSERT_NO_THROW(
        option.reset(new OptionCustom(opt_def, Option::V6));
    );
    ASSERT_TRUE(option);

    asiolink::IOAddress address("::1");
    ASSERT_NO_THROW(address = option->readAddress());
    EXPECT_EQ("::", address.toText());

    EXPECT_NO_THROW(option->writeAddress(IOAddress("2001:db8:1::1")));

    EXPECT_NO_THROW(address = option->readAddress());
    EXPECT_EQ("2001:db8:1::1", address.toText());
}

// The purpose of this test is to verify that an option comprising
// a prefix can be created and that the prefix can be overridden by
// a new value.
TEST_F(OptionCustomTest, setPrefixData) {
    OptionDefinition opt_def("option-foo", 1000, "my-space", "ipv6-prefix");

    // Create an option and let the data field be initialized
    // to default value (do not provide any data buffer).
    boost::scoped_ptr<OptionCustom> option;
    ASSERT_NO_THROW(
        option.reset(new OptionCustom(opt_def, Option::V6));
    );
    ASSERT_TRUE(option);

    // Make sure the default prefix is set.
    PrefixTuple prefix(ZERO_PREFIX_TUPLE);
    ASSERT_NO_THROW(prefix = option->readPrefix());
    EXPECT_EQ(0, prefix.first.asUnsigned());
    EXPECT_EQ("::", prefix.second.toText());

    // Write prefix.
    ASSERT_NO_THROW(option->writePrefix(PrefixLen(48), IOAddress("2001:db8:1::")));

    // Read prefix back and make sure it is the one we just set.
    ASSERT_NO_THROW(prefix = option->readPrefix());
    EXPECT_EQ(48, prefix.first.asUnsigned());
    EXPECT_EQ("2001:db8:1::", prefix.second.toText());
}

// The purpose of this test is to verify that an option comprising
// a single PSID can be created and that the PSID can be overridden
// by a new value.
TEST_F(OptionCustomTest, setPsidData) {
    OptionDefinition opt_def("option-foo", 1000, "my-space", "psid");

    // Create an option and let the data field be initialized
    // to default value (do not provide any data buffer).
    boost::scoped_ptr<OptionCustom> option;
    ASSERT_NO_THROW(
        option.reset(new OptionCustom(opt_def, Option::V6));
    );
    ASSERT_TRUE(option);

    // Make sure the default PSID is set.
    PSIDTuple psid;
    ASSERT_NO_THROW(psid = option->readPsid());
    EXPECT_EQ(0, psid.first.asUnsigned());
    EXPECT_EQ(0, psid.second.asUint16());

    // Write PSID.
    ASSERT_NO_THROW(option->writePsid(PSIDLen(4), PSID(8)));

    // Read PSID back and make sure it is the one we just set.
    ASSERT_NO_THROW(psid = option->readPsid());
    EXPECT_EQ(4, psid.first.asUnsigned());
    EXPECT_EQ(8, psid.second.asUint16());
}

// The purpose of this test is to verify that an option comprising
// single string value can be created and that this value
// is initialized to the default value. Also, this test checks that
// this value can be overwritten by a new value.
TEST_F(OptionCustomTest, setStringData) {
    OptionDefinition opt_def("OPTION_FOO", 1000, "my-space", "string");

    // Create an option and let the data field be initialized
    // to default value (do not provide any data buffer).
    boost::scoped_ptr<OptionCustom> option;
    ASSERT_NO_THROW(
        option.reset(new OptionCustom(opt_def, Option::V6));
    );
    ASSERT_TRUE(option);

    // Get the default value of the option.
    std::string value;
    ASSERT_NO_THROW(value = option->readString());
    // By default the string data field is empty.
    EXPECT_TRUE(value.empty());
    // Write some text to this field.
    ASSERT_NO_THROW(option->writeString("hello world"));
    // Check that it has been actually written.
    EXPECT_NO_THROW(value = option->readString());
    EXPECT_EQ("hello world", value);
}

/// The purpose of this test is to verify that an option comprising
/// a default FQDN value can be created and that this value can be
/// overridden after the option has been created.
TEST_F(OptionCustomTest, setFqdnData) {
    OptionDefinition opt_def("OPTION_FOO", 1000, "my-space", "fqdn");

    // Create an option and let the data field be initialized
    // to default value (do not provide any data buffer).
    boost::scoped_ptr<OptionCustom> option;
    ASSERT_NO_THROW(
        option.reset(new OptionCustom(opt_def, Option::V6));
    );
    ASSERT_TRUE(option);
    // Read a default FQDN value from the option.
    std::string fqdn;
    ASSERT_NO_THROW(fqdn = option->readFqdn());
    EXPECT_EQ(".", fqdn);
    // Try override the default FQDN value.
    ASSERT_NO_THROW(option->writeFqdn("example.com"));
    // Check that the value has been actually overridden.
    ASSERT_NO_THROW(fqdn = option->readFqdn());
    EXPECT_EQ("example.com.", fqdn);
}

// The purpose of this test is to verify that an option carrying
// an array of boolean values can be created with no values
// initially and that values can be later added to it.
TEST_F(OptionCustomTest, setBooleanDataArray) {
    OptionDefinition opt_def("OPTION_FOO", 1000, "my-space", "boolean", true);

    // Create an option and let the data field be initialized
    // to default value (do not provide any data buffer).
    boost::scoped_ptr<OptionCustom> option;
    ASSERT_NO_THROW(
        option.reset(new OptionCustom(opt_def, Option::V6));
    );
    ASSERT_TRUE(option);

    // Initially, the array should contain no values.
    ASSERT_EQ(0, option->getDataFieldsNum());

    // Add some boolean values to it.
    ASSERT_NO_THROW(option->addArrayDataField(true));
    ASSERT_NO_THROW(option->addArrayDataField(false));
    ASSERT_NO_THROW(option->addArrayDataField(true));

    // Verify that the new data fields can be added.
    bool value0 = false;
    ASSERT_NO_THROW(value0 = option->readBoolean(0));
    EXPECT_TRUE(value0);
    bool value1 = true;
    ASSERT_NO_THROW(value1 = option->readBoolean(1));
    EXPECT_FALSE(value1);
    bool value2 = false;
    ASSERT_NO_THROW(value2 = option->readBoolean(2));
    EXPECT_TRUE(value2);
}

// The purpose of this test is to verify that am option carrying
// an array of 16-bit signed integer values can be created with
// no values initially and that the values can be later added to it.
TEST_F(OptionCustomTest, setUint16DataArray) {
    OptionDefinition opt_def("OPTION_FOO", 1000, "my-space", "uint16", true);

    // Create an option and let the data field be initialized
    // to default value (do not provide any data buffer).
    boost::scoped_ptr<OptionCustom> option;
    ASSERT_NO_THROW(
        option.reset(new OptionCustom(opt_def, Option::V6));
    );
    ASSERT_TRUE(option);

    // Initially, the array should contain no values.
    ASSERT_EQ(0, option->getDataFieldsNum());

    // Add 3 new data fields holding integer values.
    ASSERT_NO_THROW(option->addArrayDataField<uint16_t>(67));
    ASSERT_NO_THROW(option->addArrayDataField<uint16_t>(876));
    ASSERT_NO_THROW(option->addArrayDataField<uint16_t>(32222));

    // We should now have 3 data fields.
    ASSERT_EQ(3, option->getDataFieldsNum());

    // Check that the values have been correctly set.
    uint16_t value0;
    ASSERT_NO_THROW(value0 = option->readInteger<uint16_t>(0));
    EXPECT_EQ(67, value0);
    uint16_t value1;
    ASSERT_NO_THROW(value1 = option->readInteger<uint16_t>(1));
    EXPECT_EQ(876, value1);
    uint16_t value2;
    ASSERT_NO_THROW(value2 = option->readInteger<uint16_t>(2));
    EXPECT_EQ(32222, value2);
}

/// The purpose of this test is to verify that an option comprising
/// array of IPv4 address can be created with no addresses and that
/// multiple IPv4 addresses can be added to it after creation.
TEST_F(OptionCustomTest, setIpv4AddressDataArray) {
    OptionDefinition opt_def("OPTION_FOO", 232, "my-space", "ipv4-address",
                             true);

    // Create an option and let the data field be initialized
    // to default value (do not provide any data buffer).
    boost::scoped_ptr<OptionCustom> option;
    ASSERT_NO_THROW(
        option.reset(new OptionCustom(opt_def, Option::V4));
    );
    ASSERT_TRUE(option);

    // Expect that the array does not contain any data fields yet.
    ASSERT_EQ(0, option->getDataFieldsNum());

    // Add 3 IPv4 addresses.
    ASSERT_NO_THROW(option->addArrayDataField(IOAddress("192.168.0.1")));
    ASSERT_NO_THROW(option->addArrayDataField(IOAddress("192.168.0.2")));
    ASSERT_NO_THROW(option->addArrayDataField(IOAddress("192.168.0.3")));

    ASSERT_EQ(3, option->getDataFieldsNum());

    // Check that all IP addresses have been set correctly.
    IOAddress address0("127.0.0.1");
    ASSERT_NO_THROW(address0 = option->readAddress(0));
    EXPECT_EQ("192.168.0.1", address0.toText());
    IOAddress address1("127.0.0.1");
    ASSERT_NO_THROW(address1 = option->readAddress(1));
    EXPECT_EQ("192.168.0.2", address1.toText());
    IOAddress address2("127.0.0.1");
    ASSERT_NO_THROW(address2 = option->readAddress(2));
    EXPECT_EQ("192.168.0.3", address2.toText());

    // Add invalid address (IPv6 instead of IPv4).
    EXPECT_THROW(
        option->addArrayDataField(IOAddress("2001:db8:1::1")),
        isc::dhcp::BadDataTypeCast
    );
}

/// The purpose of this test is to verify that an option comprising
/// array of IPv6 address can be created with no addresses and that
/// multiple IPv6 addresses can be added to it after creation.
TEST_F(OptionCustomTest, setIpv6AddressDataArray) {
    OptionDefinition opt_def("OPTION_FOO", 1000, "my-space", "ipv6-address",
                             true);

    // Create an option and let the data field be initialized
    // to default value (do not provide any data buffer).
    boost::scoped_ptr<OptionCustom> option;
    ASSERT_NO_THROW(
        option.reset(new OptionCustom(opt_def, Option::V6));
    );
    ASSERT_TRUE(option);

    // Initially, the array does not contain any data fields.
    ASSERT_EQ(0, option->getDataFieldsNum());

    // Add 3 new IPv6 addresses into the array.
    ASSERT_NO_THROW(option->addArrayDataField(IOAddress("2001:db8:1::1")));
    ASSERT_NO_THROW(option->addArrayDataField(IOAddress("2001:db8:1::2")));
    ASSERT_NO_THROW(option->addArrayDataField(IOAddress("2001:db8:1::3")));

    // We should have now 3 addresses added.
    ASSERT_EQ(3, option->getDataFieldsNum());

    // Check that they have correct values set.
    IOAddress address0("::1");
    ASSERT_NO_THROW(address0 = option->readAddress(0));
    EXPECT_EQ("2001:db8:1::1", address0.toText());
    IOAddress address1("::1");
    ASSERT_NO_THROW(address1 = option->readAddress(1));
    EXPECT_EQ("2001:db8:1::2", address1.toText());
    IOAddress address2("::1");
    ASSERT_NO_THROW(address2 = option->readAddress(2));
    EXPECT_EQ("2001:db8:1::3", address2.toText());

    // Add invalid address (IPv4 instead of IPv6).
    EXPECT_THROW(
        option->addArrayDataField(IOAddress("192.168.0.1")),
        isc::dhcp::BadDataTypeCast
    );
}

/// The purpose of this test is to verify that an option comprising an
/// array of PSIDs can be created with no PSIDs and that PSIDs can be
/// later added after the option has been created.
TEST_F(OptionCustomTest, setPSIDPrefixArray) {
    OptionDefinition opt_def("option-foo", 1000, "my-space", "psid", true);

    // Create an option and let the data field be initialized
    // to default value (do not provide any data buffer).
    boost::scoped_ptr<OptionCustom> option;
    ASSERT_NO_THROW(
        option.reset(new OptionCustom(opt_def, Option::V6));
    );
    ASSERT_TRUE(option);

    // Initially, the array does not contain any data fields.
    ASSERT_EQ(0, option->getDataFieldsNum());

    // Add 3 new PSIDs
    ASSERT_NO_THROW(option->addArrayDataField(PSIDLen(4), PSID(1)));
    ASSERT_NO_THROW(option->addArrayDataField(PSIDLen(0), PSID(123)));
    ASSERT_NO_THROW(option->addArrayDataField(PSIDLen(1), PSID(1)));

    // Verify the stored values.
    ASSERT_NO_THROW({
         PSIDTuple psid0 = option->readPsid(0);
         EXPECT_EQ(4, psid0.first.asUnsigned());
         EXPECT_EQ(1, psid0.second.asUint16());
    });

    ASSERT_NO_THROW({
         PSIDTuple psid1 = option->readPsid(1);
         EXPECT_EQ(0, psid1.first.asUnsigned());
         EXPECT_EQ(0, psid1.second.asUint16());
    });

    ASSERT_NO_THROW({
         PSIDTuple psid2 = option->readPsid(2);
         EXPECT_EQ(1, psid2.first.asUnsigned());
         EXPECT_EQ(1, psid2.second.asUint16());
    });
}

/// The purpose of this test is to verify that an option comprising an
/// array of IPv6 prefixes can be created with no prefixes and that
/// prefixes can be later added after the option has been created.
TEST_F(OptionCustomTest, setIPv6PrefixDataArray) {
    OptionDefinition opt_def("option-foo", 1000, "my-space", "ipv6-prefix",
                             true);

    // Create an option and let the data field be initialized
    // to default value (do not provide any data buffer).
    boost::scoped_ptr<OptionCustom> option;
    ASSERT_NO_THROW(
        option.reset(new OptionCustom(opt_def, Option::V6));
    );
    ASSERT_TRUE(option);

    // Initially, the array does not contain any data fields.
    ASSERT_EQ(0, option->getDataFieldsNum());

    // Add 3 new IPv6 prefixes into the array.
    ASSERT_NO_THROW(option->addArrayDataField(PrefixLen(64),
                                              IOAddress("2001:db8:1::")));
    ASSERT_NO_THROW(option->addArrayDataField(PrefixLen(32),
                                              IOAddress("3001:1::")));
    ASSERT_NO_THROW(option->addArrayDataField(PrefixLen(16),
                                              IOAddress("3000::")));

    // We should have now 3 addresses added.
    ASSERT_EQ(3, option->getDataFieldsNum());

    // Verify the stored values.
    ASSERT_NO_THROW({
         PrefixTuple prefix0 = option->readPrefix(0);
         EXPECT_EQ(64, prefix0.first.asUnsigned());
         EXPECT_EQ("2001:db8:1::", prefix0.second.toText());
    });

    ASSERT_NO_THROW({
         PrefixTuple prefix1 = option->readPrefix(1);
         EXPECT_EQ(32, prefix1.first.asUnsigned());
         EXPECT_EQ("3001:1::", prefix1.second.toText());
    });

    ASSERT_NO_THROW({
         PrefixTuple prefix2 = option->readPrefix(2);
         EXPECT_EQ(16, prefix2.first.asUnsigned());
         EXPECT_EQ("3000::", prefix2.second.toText());
    });
}

/// The purpose of this test is to verify that an option comprising an
/// array of DHCPv4 tuples can be created with no tuples and that
/// tuples can be later added after the option has been created.
TEST_F(OptionCustomTest, setTupleDataArray4) {
    OptionDefinition opt_def("option-foo", 232, "my-space", "tuple", true);

    // Create an option and let the data field be initialized
    // to default value (do not provide any data buffer).
    boost::scoped_ptr<OptionCustom> option;
    ASSERT_NO_THROW(
        option.reset(new OptionCustom(opt_def, Option::V4));
    );
    ASSERT_TRUE(option);

    // Initially, the array does not contain any data fields.
    ASSERT_EQ(0, option->getDataFieldsNum());

    // Add 3 new DHCPv4 tuple into the array.
    ASSERT_NO_THROW(option->addArrayDataField(std::string("hello")));
    ASSERT_NO_THROW(option->addArrayDataField(std::string(" ")));
    OpaqueDataTuple tuple(OpaqueDataTuple::LENGTH_1_BYTE);
    tuple.append("world");
    ASSERT_NO_THROW(option->addArrayDataField(tuple));

    // We should have now 3 tuples added.
    ASSERT_EQ(3, option->getDataFieldsNum());

    // Verify the stored values.
    ASSERT_NO_THROW({
        std::string value = option->readTuple(0);
        EXPECT_EQ("hello", value);
    });

    ASSERT_NO_THROW({
        std::string value = option->readTuple(1);
        EXPECT_EQ(" ", value);
    });

    ASSERT_NO_THROW({
        OpaqueDataTuple value(OpaqueDataTuple::LENGTH_1_BYTE);
        option->readTuple(value, 2);
        EXPECT_EQ("world", value.getText());
    });
}

/// The purpose of this test is to verify that an option comprising an
/// array of DHCPv6 tuples can be created with no tuples and that
/// tuples can be later added after the option has been created.
TEST_F(OptionCustomTest, setTupleDataArray6) {
    OptionDefinition opt_def("option-foo", 1000, "my-space", "tuple", true);

    // Create an option and let the data field be initialized
    // to default value (do not provide any data buffer).
    boost::scoped_ptr<OptionCustom> option;
    ASSERT_NO_THROW(
        option.reset(new OptionCustom(opt_def, Option::V6));
    );
    ASSERT_TRUE(option);

    // Initially, the array does not contain any data fields.
    ASSERT_EQ(0, option->getDataFieldsNum());

    // Add 3 new DHCPv6 tuple into the array.
    ASSERT_NO_THROW(option->addArrayDataField(std::string("hello")));
    ASSERT_NO_THROW(option->addArrayDataField(std::string(" ")));
    OpaqueDataTuple tuple(OpaqueDataTuple::LENGTH_2_BYTES);
    tuple.append("world");
    ASSERT_NO_THROW(option->addArrayDataField(tuple));

    // We should have now 3 tuples added.
    ASSERT_EQ(3, option->getDataFieldsNum());

    // Verify the stored values.
    ASSERT_NO_THROW({
        std::string value = option->readTuple(0);
        EXPECT_EQ("hello", value);
    });

    ASSERT_NO_THROW({
        std::string value = option->readTuple(1);
        EXPECT_EQ(" ", value);
    });

    ASSERT_NO_THROW({
        OpaqueDataTuple value(OpaqueDataTuple::LENGTH_2_BYTES);
        option->readTuple(value, 2);
        EXPECT_EQ("world", value.getText());
    });
}

TEST_F(OptionCustomTest, setRecordData) {
    OptionDefinition opt_def("OPTION_FOO", 1000, "my-space", "record");

    ASSERT_NO_THROW(opt_def.addRecordField("uint16"));
    ASSERT_NO_THROW(opt_def.addRecordField("boolean"));
    ASSERT_NO_THROW(opt_def.addRecordField("fqdn"));
    ASSERT_NO_THROW(opt_def.addRecordField("ipv4-address"));
    ASSERT_NO_THROW(opt_def.addRecordField("ipv6-address"));
    ASSERT_NO_THROW(opt_def.addRecordField("psid"));
    ASSERT_NO_THROW(opt_def.addRecordField("ipv6-prefix"));
    ASSERT_NO_THROW(opt_def.addRecordField("tuple"));
    ASSERT_NO_THROW(opt_def.addRecordField("string"));

    // Create an option and let the data field be initialized
    // to default value (do not provide any data buffer).
    boost::scoped_ptr<OptionCustom> option;
    ASSERT_NO_THROW(
        option.reset(new OptionCustom(opt_def, Option::V6));
    );
    ASSERT_TRUE(option);

    // The number of elements should be equal to number of elements
    // in the record.
    ASSERT_EQ(9, option->getDataFieldsNum());

    // Check that the default values have been correctly set.
    uint16_t value0;
    ASSERT_NO_THROW(value0 = option->readInteger<uint16_t>(0));
    EXPECT_EQ(0, value0);
    bool value1 = true;
    ASSERT_NO_THROW(value1 = option->readBoolean(1));
    EXPECT_FALSE(value1);
    std::string value2;
    ASSERT_NO_THROW(value2 = option->readFqdn(2));
    EXPECT_EQ(".", value2);
    IOAddress value3("127.0.0.1");
    ASSERT_NO_THROW(value3 = option->readAddress(3));
    EXPECT_EQ("0.0.0.0", value3.toText());
    IOAddress value4("2001:db8:1::1");
    ASSERT_NO_THROW(value4 = option->readAddress(4));
    EXPECT_EQ("::", value4.toText());
    PSIDTuple value5;
    ASSERT_NO_THROW(value5 = option->readPsid(5));
    EXPECT_EQ(0, value5.first.asUnsigned());
    EXPECT_EQ(0, value5.second.asUint16());
    PrefixTuple value6(ZERO_PREFIX_TUPLE);
    ASSERT_NO_THROW(value6 = option->readPrefix(6));
    EXPECT_EQ(0, value6.first.asUnsigned());
    EXPECT_EQ("::", value6.second.toText());
    std::string value7 = "abc";
    // Tuple has no default value
    EXPECT_THROW(option->readTuple(7), BadDataTypeCast);
    std::string value8 = "xyz";
    ASSERT_NO_THROW(value8 = option->readString(8));
    EXPECT_TRUE(value8.empty());

    // Override each value with a new value.
    ASSERT_NO_THROW(option->writeInteger<uint16_t>(1234, 0));
    ASSERT_NO_THROW(option->writeBoolean(true, 1));
    ASSERT_NO_THROW(option->writeFqdn("example.com", 2));
    ASSERT_NO_THROW(option->writeAddress(IOAddress("192.168.0.1"), 3));
    ASSERT_NO_THROW(option->writeAddress(IOAddress("2001:db8:1::100"), 4));
    ASSERT_NO_THROW(option->writePsid(PSIDLen(4), PSID(8), 5));
    ASSERT_NO_THROW(option->writePrefix(PrefixLen(48),
                                        IOAddress("2001:db8:1::"), 6));
    ASSERT_NO_THROW(option->writeTuple("foobar", 7));
    ASSERT_NO_THROW(option->writeString("hello world", 8));

    // Check that the new values have been correctly set.
    ASSERT_NO_THROW(value0 = option->readInteger<uint16_t>(0));
    EXPECT_EQ(1234, value0);
    ASSERT_NO_THROW(value1 = option->readBoolean(1));
    EXPECT_TRUE(value1);
    ASSERT_NO_THROW(value2 = option->readFqdn(2));
    EXPECT_EQ("example.com.", value2);
    ASSERT_NO_THROW(value3 = option->readAddress(3));
    EXPECT_EQ("192.168.0.1", value3.toText());
    ASSERT_NO_THROW(value4 = option->readAddress(4));
    EXPECT_EQ("2001:db8:1::100", value4.toText());
    ASSERT_NO_THROW(value5 = option->readPsid(5));
    EXPECT_EQ(4, value5.first.asUnsigned());
    EXPECT_EQ(8, value5.second.asUint16());
    ASSERT_NO_THROW(value6 = option->readPrefix(6));
    EXPECT_EQ(48, value6.first.asUnsigned());
    EXPECT_EQ("2001:db8:1::", value6.second.toText());
    ASSERT_NO_THROW(value7 = option->readTuple(7));
    EXPECT_EQ(value7, "foobar");
    ASSERT_NO_THROW(value8 = option->readString(8));
    EXPECT_EQ(value8, "hello world");
}

TEST_F(OptionCustomTest, setRecordArrayData) {
    OptionDefinition opt_def("OPTION_FOO", 1000, "my-space", "record", true);

    ASSERT_NO_THROW(opt_def.addRecordField("uint16"));
    ASSERT_NO_THROW(opt_def.addRecordField("boolean"));
    ASSERT_NO_THROW(opt_def.addRecordField("fqdn"));
    ASSERT_NO_THROW(opt_def.addRecordField("ipv4-address"));
    ASSERT_NO_THROW(opt_def.addRecordField("ipv6-address"));
    ASSERT_NO_THROW(opt_def.addRecordField("psid"));
    ASSERT_NO_THROW(opt_def.addRecordField("ipv6-prefix"));
    ASSERT_NO_THROW(opt_def.addRecordField("tuple"));
    ASSERT_NO_THROW(opt_def.addRecordField("uint32"));

    // Create an option and let the data field be initialized
    // to default value (do not provide any data buffer).
    boost::scoped_ptr<OptionCustom> option;
    ASSERT_NO_THROW(
        option.reset(new OptionCustom(opt_def, Option::V6));
    );
    ASSERT_TRUE(option);

    // The number of elements should be equal to number of elements
    // in the record.
    ASSERT_EQ(9, option->getDataFieldsNum());

    // Check that the default values have been correctly set.
    uint16_t value0;
    ASSERT_NO_THROW(value0 = option->readInteger<uint16_t>(0));
    EXPECT_EQ(0, value0);
    bool value1 = true;
    ASSERT_NO_THROW(value1 = option->readBoolean(1));
    EXPECT_FALSE(value1);
    std::string value2;
    ASSERT_NO_THROW(value2 = option->readFqdn(2));
    EXPECT_EQ(".", value2);
    IOAddress value3("127.0.0.1");
    ASSERT_NO_THROW(value3 = option->readAddress(3));
    EXPECT_EQ("0.0.0.0", value3.toText());
    IOAddress value4("2001:db8:1::1");
    ASSERT_NO_THROW(value4 = option->readAddress(4));
    EXPECT_EQ("::", value4.toText());
    PSIDTuple value5;
    ASSERT_NO_THROW(value5 = option->readPsid(5));
    EXPECT_EQ(0, value5.first.asUnsigned());
    EXPECT_EQ(0, value5.second.asUint16());
    PrefixTuple value6(ZERO_PREFIX_TUPLE);
    ASSERT_NO_THROW(value6 = option->readPrefix(6));
    EXPECT_EQ(0, value6.first.asUnsigned());
    EXPECT_EQ("::", value6.second.toText());
    std::string value7 = "abc";
    // Tuple has no default value
    EXPECT_THROW(option->readTuple(7), BadDataTypeCast);
    uint32_t value8;
    ASSERT_NO_THROW(value8 = option->readInteger<uint32_t>(8));
    EXPECT_EQ(0, value8);

    // Override each value with a new value.
    ASSERT_NO_THROW(option->writeInteger<uint16_t>(1234, 0));
    ASSERT_NO_THROW(option->writeBoolean(true, 1));
    ASSERT_NO_THROW(option->writeFqdn("example.com", 2));
    ASSERT_NO_THROW(option->writeAddress(IOAddress("192.168.0.1"), 3));
    ASSERT_NO_THROW(option->writeAddress(IOAddress("2001:db8:1::100"), 4));
    ASSERT_NO_THROW(option->writePsid(PSIDLen(4), PSID(8), 5));
    ASSERT_NO_THROW(option->writePrefix(PrefixLen(48),
                                        IOAddress("2001:db8:1::"), 6));
    ASSERT_NO_THROW(option->writeTuple("foobar", 7));
    ASSERT_NO_THROW(option->writeInteger<uint32_t>(12345678, 8));
    ASSERT_NO_THROW(option->addArrayDataField<uint32_t>(87654321));

    // Check that the new values have been correctly set.
    ASSERT_EQ(10, option->getDataFieldsNum());

    ASSERT_NO_THROW(value0 = option->readInteger<uint16_t>(0));
    EXPECT_EQ(1234, value0);
    ASSERT_NO_THROW(value1 = option->readBoolean(1));
    EXPECT_TRUE(value1);
    ASSERT_NO_THROW(value2 = option->readFqdn(2));
    EXPECT_EQ("example.com.", value2);
    ASSERT_NO_THROW(value3 = option->readAddress(3));
    EXPECT_EQ("192.168.0.1", value3.toText());
    ASSERT_NO_THROW(value4 = option->readAddress(4));
    EXPECT_EQ("2001:db8:1::100", value4.toText());
    ASSERT_NO_THROW(value5 = option->readPsid(5));
    EXPECT_EQ(4, value5.first.asUnsigned());
    EXPECT_EQ(8, value5.second.asUint16());
    ASSERT_NO_THROW(value6 = option->readPrefix(6));
    EXPECT_EQ(48, value6.first.asUnsigned());
    EXPECT_EQ("2001:db8:1::", value6.second.toText());
    ASSERT_NO_THROW(value7 = option->readTuple(7));
    EXPECT_EQ(value7, "foobar");
    ASSERT_NO_THROW(value8 = option->readInteger<uint32_t>(8));
    EXPECT_EQ(12345678, value8);
    uint32_t value9;
    ASSERT_NO_THROW(value9 = option->readInteger<uint32_t>(9));
    EXPECT_EQ(87654321, value9);
}

// The purpose of this test is to verify that pack function for
// DHCPv4 custom option works correctly.
TEST_F(OptionCustomTest, pack4) {
    OptionDefinition opt_def("OPTION_FOO", 234, "my-space", "record");
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
    OptionDefinition opt_def("OPTION_FOO", 1000, "my-space", "record");
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
    OptionDefinition opt_def("OPTION_FOO", 231, "my-space", "ipv4-address",
                             true);

    // Initialize reference data.
    std::vector<IOAddress> addresses;
    addresses.push_back(IOAddress("192.168.0.1"));
    addresses.push_back(IOAddress("127.0.0.1"));
    addresses.push_back(IOAddress("10.10.1.2"));

    // Store the collection of IPv4 addresses into the buffer.
    OptionBuffer buf;
    for (size_t i = 0; i < addresses.size(); ++i) {
        writeAddress(addresses[i], buf);
    }

    // Use the input buffer to create custom option.
    boost::scoped_ptr<OptionCustom> option;
    ASSERT_NO_THROW(
        option.reset(new OptionCustom(opt_def, Option::V4, buf.begin(), buf.end()));
    );
    ASSERT_TRUE(option);

    // We should have 3 data fields.
    ASSERT_EQ(3, option->getDataFieldsNum());

    // We expect 3 IPv4 addresses being stored in the option.
    for (int i = 0; i < 3; ++i) {
        IOAddress address("10.10.10.10");
        ASSERT_NO_THROW(address = option->readAddress(i));
        EXPECT_EQ(addresses[i], address);
    }

    // Remove all addresses we had added. We are going to replace
    // them with a new set of addresses.
    addresses.clear();

    // Add new addresses.
    addresses.push_back(IOAddress("10.1.2.3"));
    addresses.push_back(IOAddress("85.26.43.234"));

    // Clear the buffer as we need to store new addresses in it.
    buf.clear();
    for (size_t i = 0; i < addresses.size(); ++i) {
        writeAddress(addresses[i], buf);
    }

    // Perform 'unpack'.
    ASSERT_NO_THROW(option->unpack(buf.begin(), buf.end()));

    // Now we should have only 2 data fields.
    ASSERT_EQ(2, option->getDataFieldsNum());

    // Verify that the addresses have been overwritten.
    for (int i = 0; i < 2; ++i) {
        IOAddress address("10.10.10.10");
        ASSERT_NO_THROW(address = option->readAddress(i));
        EXPECT_EQ(addresses[i], address);
    }
}

// The purpose of this test is to verify that unpack function works
// correctly for a custom option with record and trailing array.
TEST_F(OptionCustomTest, unpackRecordArray) {
    OptionDefinition opt_def("OPTION_FOO", 231, "my-space", "record", true);

    ASSERT_NO_THROW(opt_def.addRecordField("uint16"));
    ASSERT_NO_THROW(opt_def.addRecordField("ipv4-address"));

    // Initialize reference data.
    OptionBuffer buf;
    writeInt<uint16_t>(8712, buf);

    std::vector<IOAddress> addresses;
    addresses.push_back(IOAddress("192.168.0.1"));
    addresses.push_back(IOAddress("127.0.0.1"));
    addresses.push_back(IOAddress("10.10.1.2"));

    // Store the collection of IPv4 addresses into the buffer.
    for (size_t i = 0; i < addresses.size(); ++i) {
        writeAddress(addresses[i], buf);
    }

    // Use the input buffer to create custom option.
    boost::scoped_ptr<OptionCustom> option;
    ASSERT_NO_THROW(
        option.reset(new OptionCustom(opt_def, Option::V4, buf.begin(), buf.end()));
    );
    ASSERT_TRUE(option);

    // We should have 4 data fields.
    ASSERT_EQ(4, option->getDataFieldsNum());

    // We expect a 16 bit integer
    uint16_t value0;
    ASSERT_NO_THROW(value0 = option->readInteger<uint16_t>(0));
    EXPECT_EQ(8712, value0);

    // ... and 3 IPv4 addresses being stored in the option.
    for (int i = 0; i < 3; ++i) {
        IOAddress address("10.10.10.10");
        ASSERT_NO_THROW(address = option->readAddress(i + 1));
        EXPECT_EQ(addresses[i], address);
    }

    std::string text = option->toText();
    EXPECT_EQ("type=231, len=014: 8712 (uint16) 192.168.0.1 (ipv4-address) "
              "127.0.0.1 (ipv4-address) 10.10.1.2 (ipv4-address)", text);
}

// The purpose of this test is to verify that new data can be set for
// a custom option.
TEST_F(OptionCustomTest, initialize) {
    OptionDefinition opt_def("OPTION_FOO", 1000, "my-space", "ipv6-address",
                             true);

    // Initialize reference data.
    std::vector<IOAddress> addresses;
    addresses.push_back(IOAddress("2001:db8:1::3"));
    addresses.push_back(IOAddress("::1"));
    addresses.push_back(IOAddress("fe80::3"));

    // Store the collection of IPv6 addresses into the buffer.
    OptionBuffer buf;
    for (size_t i = 0; i < addresses.size(); ++i) {
        writeAddress(addresses[i], buf);
    }

    // Use the input buffer to create custom option.
    boost::scoped_ptr<OptionCustom> option;
    ASSERT_NO_THROW(
        option.reset(new OptionCustom(opt_def, Option::V6, buf.begin(), buf.end()));
    );
    ASSERT_TRUE(option);

    // We should have 3 data fields.
    ASSERT_EQ(3, option->getDataFieldsNum());

    // We expect 3 IPv6 addresses being stored in the option.
    for (int i = 0; i < 3; ++i) {
        IOAddress address("fe80::4");
        ASSERT_NO_THROW(address = option->readAddress(i));
        EXPECT_EQ(addresses[i], address);
    }

    // Clear addresses we had previously added.
    addresses.clear();

    // Store new addresses.
    addresses.push_back(IOAddress("::1"));
    addresses.push_back(IOAddress("fe80::10"));

    // Clear the buffer as we need to store new addresses in it.
    buf.clear();
    for (size_t i = 0; i < addresses.size(); ++i) {
        writeAddress(addresses[i], buf);
    }

    // Replace the option data.
    ASSERT_NO_THROW(option->initialize(buf.begin(), buf.end()));

    // Now we should have only 2 data fields.
    ASSERT_EQ(2, option->getDataFieldsNum());

    // Check that it has been replaced.
    for (int i = 0; i < 2; ++i) {
        IOAddress address("10.10.10.10");
        ASSERT_NO_THROW(address = option->readAddress(i));
        EXPECT_EQ(addresses[i], address);
    }
}

// The purpose of this test is to verify that an invalid index
// value can't be used to access option data fields.
TEST_F(OptionCustomTest, invalidIndex) {
    OptionDefinition opt_def("OPTION_FOO", 999, "my-space", "uint32", true);

    OptionBuffer buf;
    for (int i = 0; i < 10; ++i) {
        writeInt<uint32_t>(i, buf);
    }

    // Use the input buffer to create custom option.
    boost::scoped_ptr<OptionCustom> option;
    ASSERT_NO_THROW(
        option.reset(new OptionCustom(opt_def, Option::V6, buf));
    );
    ASSERT_TRUE(option);

    // We expect that there are 10 uint32_t values stored in
    // the option. The 10th element is accessed by index eq 9.
    // Check that 9 is accepted.
    EXPECT_NO_THROW(option->readInteger<uint32_t>(9));

    // Check that index value beyond 9 is not accepted.
    EXPECT_THROW(option->readInteger<uint32_t>(10), isc::OutOfRange);
    EXPECT_THROW(option->readInteger<uint32_t>(11), isc::OutOfRange);
}

// This test checks that the custom option holding a record of data
// fields can be presented in the textual format.
TEST_F(OptionCustomTest, toTextRecord) {
    OptionDefinition opt_def("foo", 123, "my-space", "record");
    opt_def.addRecordField("uint32");
    opt_def.addRecordField("string");

    OptionCustom option(opt_def, Option::V4);
    option.writeInteger<uint32_t>(10);
    option.writeString("lorem ipsum", 1);

    EXPECT_EQ("type=123, len=015: 10 (uint32) \"lorem ipsum\" (string)",
              option.toText());
}

// This test checks that the custom option holding other data type
// than "record" be presented in the textual format.
TEST_F(OptionCustomTest, toTextNoRecord) {
    OptionDefinition opt_def("foo", 234, "my-space", "uint32");

    OptionCustom option(opt_def, Option::V6);
    option.writeInteger<uint32_t>(123456);

    OptionDefinition sub_opt_def("bar", 333, "my-space", "fqdn");
    OptionCustomPtr sub_opt(new OptionCustom(sub_opt_def, Option::V6));
    sub_opt->writeFqdn("myhost.example.org.");
    option.addOption(sub_opt);

    EXPECT_EQ("type=00234, len=00028: 123456 (uint32),\n"
              "options:\n"
              "  type=00333, len=00020: \"myhost.example.org.\" (fqdn)",
              option.toText());
}

} // anonymous namespace
