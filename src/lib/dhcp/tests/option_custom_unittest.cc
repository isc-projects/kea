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
#include <gtest/gtest.h>

using namespace isc;
using namespace isc::asiolink;
using namespace isc::dhcp;

namespace {

/// @brief OptionCustomTest test class.
class OptionCustomTest : public ::testing::Test {
public:
    /// @brief Constructor.
    OptionCustomTest() {
        for (int i = 0; i < 255; ++i) {
            buf_.push_back(i);
        }
    }

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

    template<typename T>
    void writeInt(T value, std::vector<uint8_t>& buf) {
        for (int i = 0; i < sizeof(T); ++i) {
            buf.push_back(value >> ((sizeof(T) - i - 1) * 8) & 0xFF);
        }
    }

    void writeString(const std::string& value,
                     std::vector<uint8_t>& buf) {
        buf.resize(buf.size() + value.size());
        std::copy_backward(value.c_str(), value.c_str() + value.size(),
                           buf.end());
    }

    OptionBuffer buf_;
};

TEST_F(OptionCustomTest, constructor) {
    /*    OptionDefinition opt_def1("OPTION_FOO", 1000, "string", true);
          ASSERT_THROW(opt_def1.validate(), isc::Exception); */
}

TEST_F(OptionCustomTest, setRecordData) {
    OptionDefinition opt_def("OPTION_FOO", 1000, "record");
    ASSERT_NO_THROW(opt_def.addRecordField("uint16"));
    ASSERT_NO_THROW(opt_def.addRecordField("boolean"));
    ASSERT_NO_THROW(opt_def.addRecordField("ipv4-address"));
    ASSERT_NO_THROW(opt_def.addRecordField("ipv6-address"));
    ASSERT_NO_THROW(opt_def.addRecordField("string"));

    OptionBuffer buf;
    writeInt<uint16_t>(8712, buf);
    buf.push_back(static_cast<unsigned short>(1));
    writeAddress(IOAddress("192.168.0.1"), buf);
    writeAddress(IOAddress("2001:db8:1::1"), buf);
    writeString("ABCD", buf);

    OptionCustom option(opt_def, Option::V6, buf.begin(), buf.begin() + 27);
    ASSERT_TRUE(option.valid());

    uint16_t value0 = 0;
    ASSERT_NO_THROW(value0 = option.readInteger<uint16_t>(0));
    EXPECT_EQ(8712, value0);
    bool value1 = false;
    ASSERT_NO_THROW(value1 = option.readBoolean(1));
    EXPECT_TRUE(value1);
    IOAddress value2("127.0.0.1");
    ASSERT_NO_THROW(option.readAddress(2, value2));
    EXPECT_EQ("192.168.0.1", value2.toText());
    IOAddress value3("::1");
    ASSERT_NO_THROW(option.readAddress(3, value3));
    EXPECT_EQ("2001:db8:1::1", value3.toText());
    std::string value4;
    ASSERT_NO_THROW(option.readString(4, value4));
    EXPECT_EQ("ABCD", value4);
}

} // anonymous namespace
