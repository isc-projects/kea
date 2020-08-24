// Copyright (C) 2011-2020 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <dhcp/dhcp6.h>
#include <dhcp/libdhcp++.h>
#include <dhcp/option.h>
#include <dhcp/option_int.h>
#include <dhcp/option_space.h>
#include <exceptions/exceptions.h>
#include <util/buffer.h>

#include <boost/shared_ptr.hpp>
#include <boost/scoped_ptr.hpp>
#include <gtest/gtest.h>

#include <iostream>
#include <sstream>

#include <arpa/inet.h>

using namespace std;
using namespace isc;
using namespace isc::dhcp;
using namespace isc::util;
using boost::scoped_ptr;

namespace {

/// @brief A class which derives from option and exposes protected members.
class NakedOption : public Option {
public:
    /// @brief Constructor
    ///
    /// Sets the universe and option type to arbitrary test values.
    NakedOption() : Option(Option::V6, 258) {
    }

    using Option::unpackOptions;
    using Option::cloneInternal;
};

class OptionTest : public ::testing::Test {
public:
    OptionTest(): buf_(255), outBuf_(255) {
        for (unsigned i = 0; i < 255; i++) {
            buf_[i] = 255 - i;
        }
    }
    OptionBuffer buf_;
    OutputBuffer outBuf_;
};

// Basic tests for V4 functionality
TEST_F(OptionTest, v4_basic) {

    scoped_ptr<Option> opt;
    EXPECT_NO_THROW(opt.reset(new Option(Option::V4, 17)));

    EXPECT_EQ(Option::V4, opt->getUniverse());
    EXPECT_EQ(17, opt->getType());
    EXPECT_EQ(0, opt->getData().size());
    EXPECT_EQ(2, opt->len()); // just v4 header

    EXPECT_NO_THROW(opt.reset());

    // V4 options have type 0...255
    EXPECT_THROW(opt.reset(new Option(Option::V4, 256)), OutOfRange);

    // 0 / PAD and 255 / END are no longer forbidden
    EXPECT_NO_THROW(opt.reset(new Option(Option::V4, 0)));
    EXPECT_NO_THROW(opt.reset(new Option(Option::V4, 255)));
}

const uint8_t dummyPayload[] =
{ 1, 2, 3, 4};

TEST_F(OptionTest, v4_data1) {

    vector<uint8_t> data(dummyPayload, dummyPayload + sizeof(dummyPayload));

    scoped_ptr<Option> opt;

    // Create DHCPv4 option of type 123 that contains 4 bytes of data.
    ASSERT_NO_THROW(opt.reset(new Option(Option::V4, 123, data)));

    // Check that content is reported properly
    EXPECT_EQ(123, opt->getType());
    vector<uint8_t> optData = opt->getData();
    ASSERT_EQ(optData.size(), data.size());
    EXPECT_TRUE(optData == data);
    EXPECT_EQ(2, opt->getHeaderLen());
    EXPECT_EQ(6, opt->len());

    // Now store that option into a buffer
    OutputBuffer buf(100);
    EXPECT_NO_THROW(opt->pack(buf));

    // Check content of that buffer:
    // 2 byte header + 4 bytes data
    ASSERT_EQ(6, buf.getLength());

    // That's how this option is supposed to look like
    uint8_t exp[] = { 123, 4, 1, 2, 3, 4 };

    /// TODO: use vector<uint8_t> getData() when it will be implemented
    EXPECT_EQ(0, memcmp(exp, buf.getData(), 6));

    // Check that we can destroy that option
    EXPECT_NO_THROW(opt.reset());
}

// This is almost the same test as v4_data1, but it uses a different
// constructor
TEST_F(OptionTest, v4_data2) {

    vector<uint8_t> data(dummyPayload, dummyPayload + sizeof(dummyPayload));

    vector<uint8_t> expData = data;

    // Add fake data in front and end. Main purpose of this test is to check
    // that only subset of the whole vector can be used for creating option.
    data.insert(data.begin(), 56);
    data.push_back(67);

    // Data contains extra garbage at beginning and at the end. It should be
    // ignored, as we pass iterators to proper data. Only subset (limited by
    // iterators) of the vector should be used.
    // expData contains expected content (just valid data, without garbage).
    scoped_ptr<Option> opt;

    // Create DHCPv4 option of type 123 that contains
    // 4 bytes (sizeof(dummyPayload).
    ASSERT_NO_THROW(
        opt.reset(new Option(Option::V4, 123, data.begin() + 1,
                             data.end() - 1));
    );

    // Check that content is reported properly
    EXPECT_EQ(123, opt->getType());
    vector<uint8_t> optData = opt->getData();
    ASSERT_EQ(optData.size(), expData.size());
    EXPECT_TRUE(optData == expData);
    EXPECT_EQ(2, opt->getHeaderLen());
    EXPECT_EQ(6, opt->len());

    // Now store that option into a buffer
    OutputBuffer buf(100);
    EXPECT_NO_THROW(opt->pack(buf));

    // Check content of that buffer

    // 2 byte header + 4 bytes data
    ASSERT_EQ(6, buf.getLength());

    // That's how this option is supposed to look like
    uint8_t exp[] = { 123, 4, 1, 2, 3, 4 };

    /// TODO: use vector<uint8_t> getData() when it will be implemented
    EXPECT_EQ(0, memcmp(exp, buf.getData(), 6));

    // Check that we can destroy that option
    EXPECT_NO_THROW(opt.reset());
}

TEST_F(OptionTest, v4_toText) {

    vector<uint8_t> buf(3);
    buf[0] = 0;
    buf[1] = 0xf;
    buf[2] = 0xff;

    Option opt(Option::V4, 253, buf);

    EXPECT_EQ("type=253, len=003: 00:0f:ff", opt.toText());
}

// Test converting option to the hexadecimal representation.
TEST_F(OptionTest, v4_toHexString) {
    std::vector<uint8_t> payload;
    for (unsigned int i = 0; i < 16; ++i) {
        payload.push_back(static_cast<uint8_t>(i));
    }
    Option opt(Option::V4, 122, payload);
    EXPECT_EQ("0x000102030405060708090A0B0C0D0E0F", opt.toHexString());
    EXPECT_EQ("0x7A10000102030405060708090A0B0C0D0E0F",
              opt.toHexString(true));

    // Test empty option.
    Option opt_empty(Option::V4, 65, std::vector<uint8_t>());
    EXPECT_TRUE(opt_empty.toHexString().empty());
    EXPECT_EQ("0x4100", opt_empty.toHexString(true));

    // Test too long option. We can't simply create such option by
    // providing a long payload, because class constructor would not
    // accept it. Instead we'll add two long sub options after we
    // create an option instance.
    Option opt_too_long(Option::V4, 33);
    // Both suboptions have payloads of 150 bytes.
    std::vector<uint8_t> long_payload(150, 1);
    OptionPtr sub1(new Option(Option::V4, 100, long_payload));
    OptionPtr sub2(new Option(Option::V4, 101, long_payload));
    opt_too_long.addOption(sub1);
    opt_too_long.addOption(sub2);

    // The toHexString() should throw exception.
    EXPECT_THROW(opt_too_long.toHexString(), isc::OutOfRange);
}

// Tests simple constructor
TEST_F(OptionTest, v6_basic) {

    scoped_ptr<Option> opt(new Option(Option::V6, 1));

    EXPECT_EQ(Option::V6, opt->getUniverse());
    EXPECT_EQ(1, opt->getType());
    EXPECT_EQ(0, opt->getData().size());
    EXPECT_EQ(4, opt->len()); // Just v6 header

    EXPECT_NO_THROW(opt.reset());
}

// Tests constructor used in packet reception.  Option contains actual data
TEST_F(OptionTest, v6_data1) {
    for (unsigned i = 0; i < 32; i++) {
        buf_[i] = 100 + i;
    }

    // Create option with seven bytes of data.
    scoped_ptr<Option> opt(new Option(Option::V6, 333,   // Type
                                      buf_.begin() + 3,  // Begin offset
                                      buf_.begin() + 10)); // End offset
    EXPECT_EQ(333, opt->getType());

    ASSERT_EQ(11, opt->len());
    ASSERT_EQ(7, opt->getData().size());
    EXPECT_EQ(0, memcmp(&buf_[3], &opt->getData()[0], 7) );

    opt->pack(outBuf_);
    EXPECT_EQ(11, outBuf_.getLength());

    const uint8_t* out = static_cast<const uint8_t*>(outBuf_.getData());
    EXPECT_EQ(out[0], 333 / 256); // Type
    EXPECT_EQ(out[1], 333 % 256);

    EXPECT_EQ(out[2], 0); // Length
    EXPECT_EQ(out[3], 7);

    // Payload
    EXPECT_EQ(0, memcmp(&buf_[3], out + 4, 7));

    EXPECT_NO_THROW(opt.reset());
}

// Another test that tests the same thing, just with different input parameters.
TEST_F(OptionTest, v6_data2) {

    buf_[0] = 0xa1;
    buf_[1] = 0xa2;
    buf_[2] = 0xa3;
    buf_[3] = 0xa4;

    // Create an option (unpack content)
    scoped_ptr<Option> opt(new Option(Option::V6, D6O_CLIENTID,
                                      buf_.begin(), buf_.begin() + 4));

    // Pack this option
    opt->pack(outBuf_);

    // 4 bytes header + 4 bytes content
    EXPECT_EQ(8, opt->len());
    EXPECT_EQ(D6O_CLIENTID, opt->getType());

    EXPECT_EQ(8, outBuf_.getLength());

    // Check if pack worked properly:
    // If option type is correct
    const uint8_t* out = static_cast<const uint8_t*>(outBuf_.getData());

    EXPECT_EQ(D6O_CLIENTID, out[0] * 256 + out[1]);

    // If option length is correct
    EXPECT_EQ(4, out[2] * 256 + out[3]);

    // If option content is correct
    EXPECT_EQ(0, memcmp(&buf_[0], out + 4, 4));

    EXPECT_NO_THROW(opt.reset());
}

// Check that an option can contain 2 suboptions:
// opt1
//  +----opt2
//  |
//  +----opt3
//
TEST_F(OptionTest, v6_suboptions1) {
    for (unsigned i = 0; i < 128; i++) {
        buf_[i] = 100 + i;
    }

    scoped_ptr<Option> opt1(new Option(Option::V6, 65535, // Type
                                       buf_.begin(), // 3 bytes of data
                                       buf_.begin() + 3));
    OptionPtr opt2(new Option(Option::V6, 13));
    OptionPtr opt3(new Option(Option::V6, 7,
                              buf_.begin() + 3,
                              buf_.begin() + 8)); // 5 bytes of data
    opt1->addOption(opt2);
    opt1->addOption(opt3);
    // opt2 len = 4 (just header)
    // opt3 len = 9 4(header)+5(data)
    // opt1 len = 7 + suboptions() = 7 + 4 + 9 = 20

    EXPECT_EQ(4, opt2->len());
    EXPECT_EQ(9, opt3->len());
    EXPECT_EQ(20, opt1->len());

    uint8_t expected[] = {
        0xff, 0xff, 0, 16, 100, 101, 102,
        0, 7, 0, 5, 103, 104, 105, 106, 107,
        0, 13, 0, 0 // no data at all
    };

    opt1->pack(outBuf_);
    EXPECT_EQ(20, outBuf_.getLength());

    // Payload
    EXPECT_EQ(0, memcmp(outBuf_.getData(), expected, 20) );

    EXPECT_NO_THROW(opt1.reset());
}

// Check that an option can contain nested suboptions:
// opt1
//  +----opt2
//        |
//        +----opt3
//
TEST_F(OptionTest, v6_suboptions2) {
    for (unsigned i = 0; i < 128; i++) {
        buf_[i] = 100 + i;
    }

    scoped_ptr<Option> opt1(new Option(Option::V6, 65535, // Type
                                       buf_.begin(), buf_.begin() + 3));
    OptionPtr opt2(new Option(Option::V6, 13));
    OptionPtr opt3(new Option(Option::V6, 7,
                              buf_.begin() + 3,
                              buf_.begin() + 8));
    opt1->addOption(opt2);
    opt2->addOption(opt3);
    // opt3 len = 9 4(header)+5(data)
    // opt2 len = 4 (just header) + len(opt3)
    // opt1 len = 7 + len(opt2)

    uint8_t expected[] = {
        0xff, 0xff, 0, 16, 100, 101, 102,
        0, 13, 0, 9,
        0, 7, 0, 5, 103, 104, 105, 106, 107,
    };

    opt1->pack(outBuf_);
    EXPECT_EQ(20, outBuf_.getLength());

    // Payload
    EXPECT_EQ(0, memcmp(outBuf_.getData(), expected, 20) );

    EXPECT_NO_THROW(opt1.reset());
}

TEST_F(OptionTest, v6_addgetdel) {
    for (unsigned i = 0; i < 128; i++) {
        buf_[i] = 100 + i;
    }

    scoped_ptr<Option> parent(new Option(Option::V6, 65535)); // Type
    OptionPtr opt1(new Option(Option::V6, 1));
    OptionPtr opt2(new Option(Option::V6, 2));
    OptionPtr opt3(new Option(Option::V6, 2));

    parent->addOption(opt1);
    parent->addOption(opt2);

    // getOption() test
    EXPECT_EQ(opt1, parent->getOption(1));
    EXPECT_EQ(opt2, parent->getOption(2));

    // Expect NULL
    EXPECT_EQ(OptionPtr(), parent->getOption(4));

    // Now there are 2 options of type 2
    parent->addOption(opt3);

    // Let's delete one of them
    EXPECT_EQ(true, parent->delOption(2));

    // There still should be the other option 2
    EXPECT_NE(OptionPtr(), parent->getOption(2));

    // Let's delete the other option 2
    EXPECT_EQ(true, parent->delOption(2));

    // No more options with type=2
    EXPECT_EQ(OptionPtr(), parent->getOption(2));

    // Let's try to delete - should fail
    EXPECT_TRUE(false ==  parent->delOption(2));
}

TEST_F(OptionTest, v6_toText) {
    buf_[0] = 0;
    buf_[1] = 0xf;
    buf_[2] = 0xff;

    OptionPtr opt(new Option(Option::V6, 258, buf_.begin(), buf_.begin() + 3 ));
    EXPECT_EQ("type=00258, len=00003: 00:0f:ff", opt->toText());
}

// Test converting option to the hexadecimal representation.
TEST_F(OptionTest, v6_toHexString) {
    std::vector<uint8_t> payload;
    for (unsigned int i = 0; i < 16; ++i) {
        payload.push_back(static_cast<uint8_t>(i));
    }
    Option opt(Option::V6, 12202, payload);
    EXPECT_EQ("0x000102030405060708090A0B0C0D0E0F", opt.toHexString());
    EXPECT_EQ("0x2FAA0010000102030405060708090A0B0C0D0E0F",
              opt.toHexString(true));

    // Test empty option.
    Option opt_empty(Option::V6, 65000, std::vector<uint8_t>());
    EXPECT_TRUE(opt_empty.toHexString().empty());
    EXPECT_EQ("0xFDE80000", opt_empty.toHexString(true));
}

TEST_F(OptionTest, getUintX) {

    buf_[0] = 0x5;
    buf_[1] = 0x4;
    buf_[2] = 0x3;
    buf_[3] = 0x2;
    buf_[4] = 0x1;

    // Five options with varying lengths
    OptionPtr opt1(new Option(Option::V6, 258, buf_.begin(), buf_.begin() + 1));
    OptionPtr opt2(new Option(Option::V6, 258, buf_.begin(), buf_.begin() + 2));
    OptionPtr opt3(new Option(Option::V6, 258, buf_.begin(), buf_.begin() + 3));
    OptionPtr opt4(new Option(Option::V6, 258, buf_.begin(), buf_.begin() + 4));
    OptionPtr opt5(new Option(Option::V6, 258, buf_.begin(), buf_.begin() + 5));

    EXPECT_EQ(5, opt1->getUint8());
    EXPECT_THROW(opt1->getUint16(), OutOfRange);
    EXPECT_THROW(opt1->getUint32(), OutOfRange);

    EXPECT_EQ(5, opt2->getUint8());
    EXPECT_EQ(0x0504, opt2->getUint16());
    EXPECT_THROW(opt2->getUint32(), OutOfRange);

    EXPECT_EQ(5, opt3->getUint8());
    EXPECT_EQ(0x0504, opt3->getUint16());
    EXPECT_THROW(opt3->getUint32(), OutOfRange);

    EXPECT_EQ(5, opt4->getUint8());
    EXPECT_EQ(0x0504, opt4->getUint16());
    EXPECT_EQ(0x05040302, opt4->getUint32());

    // The same as for 4-byte long, just get first 1,2 or 4 bytes
    EXPECT_EQ(5, opt5->getUint8());
    EXPECT_EQ(0x0504, opt5->getUint16());
    EXPECT_EQ(0x05040302, opt5->getUint32());

}

TEST_F(OptionTest, setUintX) {
    OptionPtr opt1(new Option(Option::V4, 125));
    OptionPtr opt2(new Option(Option::V4, 125));
    OptionPtr opt4(new Option(Option::V4, 125));

    // Verify setUint8
    opt1->setUint8(255);
    EXPECT_EQ(255, opt1->getUint8());
    opt1->pack(outBuf_);
    EXPECT_EQ(3, opt1->len());
    EXPECT_EQ(3, outBuf_.getLength());
    uint8_t exp1[] = {125, 1, 255};
    EXPECT_TRUE(0 == memcmp(exp1, outBuf_.getData(), 3));

    // Verify getUint16
    outBuf_.clear();
    opt2->setUint16(12345);
    opt2->pack(outBuf_);
    EXPECT_EQ(12345, opt2->getUint16());
    EXPECT_EQ(4, opt2->len());
    EXPECT_EQ(4, outBuf_.getLength());
    uint8_t exp2[] = {125, 2, 12345/256, 12345%256};
    EXPECT_TRUE(0 == memcmp(exp2, outBuf_.getData(), 4));

    // Verify getUint32
    outBuf_.clear();
    opt4->setUint32(0x12345678);
    opt4->pack(outBuf_);
    EXPECT_EQ(0x12345678, opt4->getUint32());
    EXPECT_EQ(6, opt4->len());
    EXPECT_EQ(6, outBuf_.getLength());
    uint8_t exp4[] = {125, 4, 0x12, 0x34, 0x56, 0x78};
    EXPECT_TRUE(0 == memcmp(exp4, outBuf_.getData(), 6));
}

TEST_F(OptionTest, setData) {
    // Verify data override with new buffer larger than initial option buffer
    // size.
    OptionPtr opt1(new Option(Option::V4, 125,
                              buf_.begin(), buf_.begin() + 10));
    buf_.resize(20, 1);
    opt1->setData(buf_.begin(), buf_.end());
    opt1->pack(outBuf_);
    ASSERT_EQ(outBuf_.getLength() - opt1->getHeaderLen(), buf_.size());
    const uint8_t* test_data = static_cast<const uint8_t*>(outBuf_.getData());
    EXPECT_TRUE(0 == memcmp(&buf_[0], test_data + opt1->getHeaderLen(),
                            buf_.size()));

    // Verify data override with new buffer shorter than initial option buffer
    // size.
    OptionPtr opt2(new Option(Option::V4, 125,
                              buf_.begin(), buf_.begin() + 10));
    outBuf_.clear();
    buf_.resize(5, 1);
    opt2->setData(buf_.begin(), buf_.end());
    opt2->pack(outBuf_);
    ASSERT_EQ(outBuf_.getLength() - opt1->getHeaderLen(), buf_.size());
    test_data = static_cast<const uint8_t*>(outBuf_.getData());
    EXPECT_TRUE(0 == memcmp(&buf_[0], test_data + opt1->getHeaderLen(),
                            buf_.size()));
}

// This test verifies that options can be compared using equals(OptionPtr)
// method.
TEST_F(OptionTest, equalsWithPointers) {

    // Five options with varying lengths
    OptionPtr opt1(new Option(Option::V6, 258, buf_.begin(), buf_.begin() + 1));
    OptionPtr opt2(new Option(Option::V6, 258, buf_.begin(), buf_.begin() + 2));
    OptionPtr opt3(new Option(Option::V6, 258, buf_.begin(), buf_.begin() + 3));

    // The same content as opt2, but different type
    OptionPtr opt4(new Option(Option::V6, 1, buf_.begin(), buf_.begin() + 2));

    // Another instance with the same type and content as opt2
    OptionPtr opt5(new Option(Option::V6, 258, buf_.begin(), buf_.begin() + 2));

    EXPECT_TRUE(opt1->equals(opt1));

    EXPECT_FALSE(opt1->equals(opt2));
    EXPECT_FALSE(opt1->equals(opt3));
    EXPECT_FALSE(opt1->equals(opt4));

    EXPECT_TRUE(opt2->equals(opt5));
}

// This test verifies that options can be compared using equals(Option) method.
TEST_F(OptionTest, equals) {

    // Five options with varying lengths
    Option opt1(Option::V6, 258, buf_.begin(), buf_.begin() + 1);
    Option opt2(Option::V6, 258, buf_.begin(), buf_.begin() + 2);
    Option opt3(Option::V6, 258, buf_.begin(), buf_.begin() + 3);

    // The same content as opt2, but different type
    Option opt4(Option::V6, 1, buf_.begin(), buf_.begin() + 2);

    // Another instance with the same type and content as opt2
    Option opt5(Option::V6, 258, buf_.begin(), buf_.begin() + 2);

    EXPECT_TRUE(opt1.equals(opt1));

    EXPECT_FALSE(opt1.equals(opt2));
    EXPECT_FALSE(opt1.equals(opt3));
    EXPECT_FALSE(opt1.equals(opt4));

    EXPECT_TRUE(opt2.equals(opt5));
}

// This test verifies that the name of the option space being encapsulated by
// the particular option can be set.
TEST_F(OptionTest, setEncapsulatedSpace) {
    Option optv6(Option::V6, 258);
    EXPECT_TRUE(optv6.getEncapsulatedSpace().empty());

    optv6.setEncapsulatedSpace(DHCP6_OPTION_SPACE);
    EXPECT_EQ(DHCP6_OPTION_SPACE, optv6.getEncapsulatedSpace());

    Option optv4(Option::V4, 125);
    EXPECT_TRUE(optv4.getEncapsulatedSpace().empty());

    optv4.setEncapsulatedSpace(DHCP4_OPTION_SPACE);
    EXPECT_EQ(DHCP4_OPTION_SPACE, optv4.getEncapsulatedSpace());
}

// This test verifies that cloneInternal returns NULL pointer if
// non-compatible type is used as a template argument.
// By non-compatible it is meant that the option instance doesn't
// dynamic_cast to the type specified as template argument.
// In our case, the NakedOption doesn't cast to OptionUint8 as the
// latter is not derived from NakedOption.
TEST_F(OptionTest, cloneInternal) {
    NakedOption option;
    OptionPtr clone;
    // This shouldn't throw nor cause segmentation fault.
    ASSERT_NO_THROW(clone = option.cloneInternal<OptionUint8>());
    EXPECT_FALSE(clone);
}

// This test verifies that empty option factory function creates
// a valid option instance.
TEST_F(OptionTest, create) {
    auto option = Option::create(Option::V4, 123);
    ASSERT_TRUE(option);
    EXPECT_EQ(Option::V4, option->getUniverse());
    EXPECT_EQ(123, option->getType());
}

// This test verifies that option factory function creates a
// valid option instance.
TEST_F(OptionTest, createPayload) {
    auto option = Option::create(Option::V4, 123, buf_);
    ASSERT_TRUE(option);
    EXPECT_EQ(Option::V4, option->getUniverse());
    EXPECT_EQ(123, option->getType());
    EXPECT_EQ(buf_, option->getData());
}

}
