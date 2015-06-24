// Copyright (C) 2011-2015 Internet Systems Consortium, Inc. ("ISC")
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
#include <dhcp/libdhcp++.h>
#include <dhcp/option.h>
#include <exceptions/exceptions.h>
#include <util/buffer.h>

#include <boost/bind.hpp>
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

/// @brief A class which contains a custom callback function to unpack options.
///
/// This is a class used by the tests which verify that the custom callback
/// functions can be installed to unpack options from a message. When the
/// callback function is called, the executed_ member is set to true to allow
/// verification that the callback was really called. Internally, this class
/// uses libdhcp++ to unpack options so the options parsing algorithm remains
/// unchanged after installation of the callback.
class CustomUnpackCallback {
public:

    /// @brief Constructor
    ///
    /// Marks that callback hasn't been called.
    CustomUnpackCallback()
        : executed_(false) {
    }

    /// @brief A callback
    ///
    /// Contains custom implementation of the callback.
    ///
    /// @param buf a A buffer holding options in on-wire format.
    /// @param option_space A name of the option space being encapsulated by
    /// the option being parsed.
    /// @param [out] options A reference to the collection where parsed options
    /// will be stored.
    /// @param relay_msg_offset Reference to a size_t structure. If specified,
    /// offset to beginning of relay_msg option will be stored in it.
    /// @param relay_msg_len reference to a size_t structure. If specified,
    /// length of the relay_msg option will be stored in it.
    /// @return An offset to the first byte after last parsed option.
    size_t execute(const OptionBuffer& buf,
                   const std::string& option_space,
                   isc::dhcp::OptionCollection& options,
                   size_t* relay_msg_offset,
                   size_t* relay_msg_len) {
        // Set the executed_ member to true to allow verification that the
        // callback has been actually called.
        executed_ = true;
        // Use default implementation of the unpack algorithm to parse options.
        return (LibDHCP::unpackOptions6(buf, option_space, options, relay_msg_offset,
                                        relay_msg_len));
    }

    /// A flag which indicates if callback function has been called.
    bool executed_;
};

/// @brief A class which derives from option and exposes protected members.
class NakedOption : public Option {
public:
    /// @brief Constructor
    ///
    /// Sets the universe and option type to arbitrary test values.
    NakedOption() : Option(Option::V6, 258) {
    }

    using Option::unpackOptions;
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
    EXPECT_THROW(opt.reset(new Option(Option::V4, 256)), BadValue);

    // 0 is a special PAD option
    EXPECT_THROW(opt.reset(new Option(Option::V4, 0)), BadValue);

    // 255 is a special END option
    EXPECT_THROW(opt.reset(new Option(Option::V4, 255)), BadValue);
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
    // ignored, as we pass interators to proper data. Only subset (limited by
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

    optv6.setEncapsulatedSpace("dhcp6");
    EXPECT_EQ("dhcp6", optv6.getEncapsulatedSpace());

    Option optv4(Option::V4, 125);
    EXPECT_TRUE(optv4.getEncapsulatedSpace().empty());

    optv4.setEncapsulatedSpace("dhcp4");
    EXPECT_EQ("dhcp4", optv4.getEncapsulatedSpace());

}

// This test verifies that it is possible to specify custom implementation of
// the option parsing algorithm by installing a callback function.
TEST_F(OptionTest, unpackCallback) {
    // Create a buffer which holds two sub options.
    const char opt_data[] = {
        0x00, 0x01,  // sub option code  = 1
        0x00, 0x02,  // sub option length = 2
        0x00, 0x01,  // sub option data (2 bytes)
        0x00, 0x02,  // sub option code = 2
        0x00, 0x02,  // sub option length = 2
        0x01, 0x01   // sub option data (2 bytes)
    };
    OptionBuffer opt_buf(opt_data, opt_data + sizeof(opt_data));

    // Make sure that the flag which indicates if the callback function has
    // been called is not set. Otherwise, our test doesn't make sense.
    CustomUnpackCallback cb;
    ASSERT_FALSE(cb.executed_);
    // Create an option and install a callback.
    NakedOption option;
    // Parameters from _1 to _5 are placeholders for the actual values
    // to be passed to the callback function. See: boost::bind documentation
    // at http://www.boost.org/doc/libs/1_54_0/libs/bind/bind.html.
    // Also, see UnpackOptionsCallback in option.h for description of the
    // parameter values.
    option.setCallback(boost::bind(&CustomUnpackCallback::execute, &cb,
                                   _1, _2, _3, _4, _5));
    // Parse options. It should result in a call to our callback function.
    // This function uses LibDHCP to parse options so they should be parsed
    // correctly.
    ASSERT_NO_THROW(option.unpackOptions(opt_buf));
    EXPECT_TRUE(option.getOption(1));
    EXPECT_TRUE(option.getOption(2));
    EXPECT_FALSE(option.getOption(3));
    // The callback should have been registered.
    EXPECT_TRUE(cb.executed_);
    // Reset the flag because now we are going to uninstall the callback and
    // verify that it was NOT called.
    cb.executed_ = false;
    // Uninstall the callback.
    option.setCallback(NULL);
    ASSERT_NO_THROW(option.unpackOptions(opt_buf));
    // Options should still get unpacked...
    EXPECT_TRUE(option.getOption(1));
    EXPECT_TRUE(option.getOption(2));
    EXPECT_FALSE(option.getOption(3));
    // ... but not via callback.
    EXPECT_FALSE(cb.executed_);
}


}
