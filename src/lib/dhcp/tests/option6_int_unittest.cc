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
#include <dhcp/dhcp6.h>
#include <dhcp/option.h>
#include <dhcp/option6_int.h>
#include <dhcp/option6_iaaddr.h>
#include <util/buffer.h>

#include <boost/pointer_cast.hpp>
#include <gtest/gtest.h>

using namespace std;
using namespace isc;
using namespace isc::dhcp;
using namespace isc::asiolink;
using namespace isc::util;

namespace {

/// @brief Option6Int test class.
class Option6IntTest : public ::testing::Test {
public:
    /// @brief Constructor.
    ///
    /// Initializes the option buffer with some data.
    Option6IntTest(): buf_(255), out_buf_(255) {
        for (int i = 0; i < 255; i++) {
            buf_[i] = 255 - i;
        }
    }

    OptionBuffer buf_;     ///< Option buffer
    OutputBuffer out_buf_; ///< Output buffer
};

/// @todo: below, there is a bunch of tests for options that
/// convey unsigned value. We should maybe extend these tests for
/// signed types too.

TEST_F(Option6IntTest, useInvalidType) {
    EXPECT_THROW(
        boost::scoped_ptr<Option6Int<bool> >(new Option6Int<bool>(D6O_ELAPSED_TIME, 10)),
        InvalidDataType
    );

    EXPECT_THROW(
        boost::scoped_ptr<Option6Int<int64_t> >(new Option6Int<int64_t>(D6O_ELAPSED_TIME, 10)),
        InvalidDataType
    );

}

TEST_F(Option6IntTest, basicUint8) {
    // Create option that conveys single uint8_t value.
    boost::shared_ptr<Option6Int<uint8_t> > opt;
    // Initialize buffer with this value.
    buf_[0] = 0xa1;
    // Constructor may throw in case provided buffer is too short.
    ASSERT_NO_THROW(
        opt = boost::shared_ptr<Option6Int<uint8_t> >(new Option6Int<uint8_t>(D6O_PREFERENCE,
                                                                              buf_.begin(),
                                                                              buf_.end()))
    );

    EXPECT_EQ(Option::V6, opt->getUniverse());
    EXPECT_EQ(D6O_PREFERENCE, opt->getType());
    // Option should return the same value that we initialized the first
    // byte of the buffer with.
    EXPECT_EQ(buf_[0], opt->getValue());

    // test for pack()
    opt->pack(out_buf_);

    // Data length is 1 byte.
    EXPECT_EQ(1, opt->len() - opt->getHeaderLen());
    EXPECT_EQ(D6O_PREFERENCE, opt->getType());
    // The total length is 1 byte for data and 4 bytes for header.
    EXPECT_EQ(5, out_buf_.getLength());

    // Check if pack worked properly:
    InputBuffer out(out_buf_.getData(), out_buf_.getLength());
    // if option type is correct
    EXPECT_EQ(D6O_PREFERENCE, out.readUint16());
    // if option length is correct
    EXPECT_EQ(1, out.readUint16());
    // if data is correct
    EXPECT_EQ(0xa1, out.readUint8() );
}

TEST_F(Option6IntTest, basicUint16) {
    // Create option that conveys single uint16_t value.
    boost::shared_ptr<Option6Int<uint16_t> > opt;
    // Initialize buffer with uint16_t value.
    buf_[0] = 0xa1;
    buf_[1] = 0xa2;
    // Constructor may throw in case provided buffer is too short.
    ASSERT_NO_THROW(
        opt = boost::shared_ptr<Option6Int<uint16_t> >(new Option6Int<uint16_t>(D6O_ELAPSED_TIME,
                                                                                buf_.begin(),
                                                                                buf_.end()))
    );

    EXPECT_EQ(Option::V6, opt->getUniverse());
    EXPECT_EQ(D6O_ELAPSED_TIME, opt->getType());
    // Option should return the value equal to the contents of first
    // and second byte of the buffer.
    EXPECT_EQ(0xa1a2, opt->getValue());

    // Test for pack()
    opt->pack(out_buf_);

    // Data length is 2 bytes.
    EXPECT_EQ(2, opt->len() - opt->getHeaderLen());
    EXPECT_EQ(D6O_ELAPSED_TIME, opt->getType());
    // The total length is 2 byte for data and 4 bytes for header.
    EXPECT_EQ(6, out_buf_.getLength());

    // Check if pack worked properly:
    InputBuffer out(out_buf_.getData(), out_buf_.getLength());
    // if option type is correct
    EXPECT_EQ(D6O_ELAPSED_TIME, out.readUint16());
    // if option length is correct
    EXPECT_EQ(2, out.readUint16());
    // if data is correct
    EXPECT_EQ(0xa1a2, out.readUint16() );
}

TEST_F(Option6IntTest, basicUint32) {
    // Create option that conveys single uint32_t value.
    boost::shared_ptr<Option6Int<uint32_t> > opt;
    // Initialize buffer with uint32_t value.
    buf_[0] = 0xa1;
    buf_[1] = 0xa2;
    buf_[2] = 0xa3;
    buf_[3] = 0xa4;
    // Constructor may throw in case provided buffer is too short.
    ASSERT_NO_THROW(
        opt = boost::shared_ptr<Option6Int<uint32_t> >(new Option6Int<uint32_t>(D6O_CLT_TIME,
                                                                                buf_.begin(),
                                                                                buf_.end()))
    );

    EXPECT_EQ(Option::V6, opt->getUniverse());
    EXPECT_EQ(D6O_CLT_TIME, opt->getType());
    // Option should return the value equal to the value made of
    // first 4 bytes of the buffer.
    EXPECT_EQ(0xa1a2a3a4, opt->getValue());

    // Test for pack()
    opt->pack(out_buf_);

    // Data length is 4 bytes.
    EXPECT_EQ(4, opt->len() - opt->getHeaderLen());
    EXPECT_EQ(D6O_CLT_TIME, opt->getType());
    // The total length is 4 bytes for data and 4 bytes for header.
    EXPECT_EQ(8, out_buf_.getLength());

    // Check if pack worked properly:
    InputBuffer out(out_buf_.getData(), out_buf_.getLength());
    // if option type is correct
    EXPECT_EQ(D6O_CLT_TIME, out.readUint16());
    // if option length is correct
    EXPECT_EQ(4, out.readUint16());
    // if data is correct
    EXPECT_EQ(0xa1a2a3a4, out.readUint32());
}


TEST_F(Option6IntTest, setValueUint8) {
    boost::shared_ptr<Option6Int<uint8_t> > opt(new Option6Int<uint8_t>(D6O_PREFERENCE, 123));
    // Check if constructor intitialized the option value correctly.
    EXPECT_EQ(123, opt->getValue());
    // Override the value.
    opt->setValue(111);

    EXPECT_EQ(Option::V6, opt->getUniverse());
    EXPECT_EQ(D6O_PREFERENCE, opt->getType());
    // Check if the value has been overriden.
    EXPECT_EQ(111, opt->getValue());
}

TEST_F(Option6IntTest, setValueUint16) {
    boost::shared_ptr<Option6Int<uint16_t> > opt(new Option6Int<uint16_t>(D6O_ELAPSED_TIME, 123));
    // Check if constructor intitialized the option value correctly.
    EXPECT_EQ(123, opt->getValue());
    // Override the value.
    opt->setValue(0x0102);

    EXPECT_EQ(Option::V6, opt->getUniverse());
    EXPECT_EQ(D6O_ELAPSED_TIME, opt->getType());
    // Check if the value has been overriden.
    EXPECT_EQ(0x0102, opt->getValue());
}

TEST_F(Option6IntTest, setValueUint32) {
    boost::shared_ptr<Option6Int<uint32_t> > opt(new Option6Int<uint32_t>(D6O_CLT_TIME, 123));
    // Check if constructor intitialized the option value correctly.
    EXPECT_EQ(123, opt->getValue());
    // Override the value.
    opt->setValue(0x01020304);

    EXPECT_EQ(Option::V6, opt->getUniverse());
    EXPECT_EQ(D6O_CLT_TIME, opt->getType());
    // Check if the value has been overriden.
    EXPECT_EQ(0x01020304, opt->getValue());
}

TEST_F(Option6IntTest, packSuboptions) {
    uint16_t opt_code = 80;

    boost::shared_ptr<Option6Int<uint32_t> > opt(new Option6Int<uint32_t>(opt_code, 0x01020304));
    OptionPtr sub1(new Option(Option::V6, 0xcafe));

    boost::shared_ptr<Option6IAAddr> addr1(
        new Option6IAAddr(D6O_IAADDR, IOAddress("2001:db8:1234:5678::abcd"), 0x5000, 0x7000));

    opt->addOption(sub1);
    opt->addOption(addr1);

    ASSERT_EQ(28, addr1->len());
    ASSERT_EQ(4, sub1->len());
    ASSERT_EQ(40, opt->len());

    uint8_t expected[] = {
        opt_code / 256, opt_code % 256, // type
        0, 36, // length
        0x01, 0x02, 0x03, 0x04, // uint32_t value

        // iaaddr suboption
        D6O_IAADDR / 256, D6O_IAADDR % 256, // type
        0, 24, // len
        0x20, 0x01, 0xd, 0xb8, 0x12,0x34, 0x56, 0x78,
        0, 0, 0, 0, 0, 0, 0xab, 0xcd, // IP address
        0, 0, 0x50, 0, // preferred-lifetime
        0, 0, 0x70, 0, // valid-lifetime

        // suboption
        0xca, 0xfe, // type
        0, 0 // len
    };

    // Create on-wire format of option and suboptions.
    opt->pack(out_buf_);
    // Compare the on-wire data with the reference buffer.
    ASSERT_EQ(40, out_buf_.getLength());
    EXPECT_EQ(0, memcmp(out_buf_.getData(), expected, 40));
}


TEST_F(Option6IntTest, unpackSuboptions) {
    // Create some dummy option.
    const uint16_t opt_code = 80;
    // Prepare reference data.
    uint8_t expected[] = {
        opt_code / 256, opt_code % 256, // type
        0, 34, // length
        0x01, 0x02, // uint16_t value

        // iaaddr suboption
        D6O_IAADDR / 256, D6O_IAADDR % 256, // type
        0, 24, // len
        0x20, 0x01, 0xd, 0xb8, 0x12,0x34, 0x56, 0x78,
        0, 0, 0, 0, 0, 0, 0xab, 0xcd, // IP address
        0, 0, 0x50, 0, // preferred-lifetime
        0, 0, 0x70, 0, // valid-lifetime

        // suboption
        0xca, 0xfe, // type
        0, 0 // len
    };
    ASSERT_EQ(38, sizeof(expected));

    memcpy(&buf_[0], expected, sizeof(expected));

    boost::shared_ptr<Option6Int<uint16_t> > opt;
    EXPECT_NO_THROW(
        opt = boost::shared_ptr<
            Option6Int<uint16_t> >(new Option6Int<uint16_t>(opt_code, buf_.begin() + 4,
                                                            buf_.begin() + sizeof(expected)));
    );
    ASSERT_TRUE(opt);

    EXPECT_EQ(opt_code, opt->getType());
    EXPECT_EQ(0x0102, opt->getValue());

    // Checks for address option
    OptionPtr subopt = opt->getOption(D6O_IAADDR);
    ASSERT_TRUE(subopt);
    boost::shared_ptr<Option6IAAddr> addr(boost::dynamic_pointer_cast<Option6IAAddr>(subopt));
    ASSERT_TRUE(addr);

    EXPECT_EQ(D6O_IAADDR, addr->getType());
    EXPECT_EQ(28, addr->len());
    EXPECT_EQ(0x5000, addr->getPreferred());
    EXPECT_EQ(0x7000, addr->getValid());
    EXPECT_EQ("2001:db8:1234:5678::abcd", addr->getAddress().toText());

    // Checks for dummy option
    subopt = opt->getOption(0xcafe);
    ASSERT_TRUE(subopt); // should be non-NULL

    EXPECT_EQ(0xcafe, subopt->getType());
    EXPECT_EQ(4, subopt->len());
    // There should be no data at all
    EXPECT_EQ(0, subopt->getData().size());

    // Try to get non-existent option.
    subopt = opt->getOption(1);
    // Expecting NULL which means that option does not exist.
    ASSERT_FALSE(subopt);
} 

} // anonymous namespace
