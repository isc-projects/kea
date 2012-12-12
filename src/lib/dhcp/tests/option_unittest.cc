// Copyright (C) 2011-2012 Internet Systems Consortium, Inc. ("ISC")
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
#include <exceptions/exceptions.h>
#include <util/buffer.h>

#include <boost/shared_ptr.hpp>
#include <gtest/gtest.h>

#include <iostream>
#include <sstream>

#include <arpa/inet.h>

using namespace std;
using namespace isc;
using namespace isc::dhcp;
using namespace isc::util;

namespace {
class OptionTest : public ::testing::Test {
public:
    OptionTest(): buf_(255), outBuf_(255) {
        for (int i = 0; i < 255; i++) {
            buf_[i] = 255 - i;
        }
    }
    OptionBuffer buf_;
    OutputBuffer outBuf_;
};

// v4 is not really implemented yet. A simple test will do for now
TEST_F(OptionTest, v4_basic) {

    Option* opt = 0;
    EXPECT_NO_THROW(
        opt = new Option(Option::V4, 17);
    );

    EXPECT_EQ(Option::V4, opt->getUniverse());
    EXPECT_EQ(17, opt->getType());
    EXPECT_EQ(0, opt->getData().size());
    EXPECT_EQ(2, opt->len()); // just v4 header

    EXPECT_NO_THROW(
        delete opt;
    );
    opt = 0;

    // V4 options have type 0...255
    EXPECT_THROW(
        opt = new Option(Option::V4, 256),
        BadValue
    );

    delete opt;
    opt = 0;

    // 0 is a special PAD option
    EXPECT_THROW(
        opt = new Option(Option::V4, 0),
        BadValue
    );

    delete opt;
    opt = 0;

    // 255 is a special END option
    EXPECT_THROW(
        opt = new Option(Option::V4, 255),
        BadValue
    );

    delete opt;
    opt = 0;
}

const uint8_t dummyPayload[] =
{ 1, 2, 3, 4};

TEST_F(OptionTest, v4_data1) {

    vector<uint8_t> data(dummyPayload, dummyPayload + sizeof(dummyPayload));

    Option* opt = 0;

    // create DHCPv4 option of type 123
    // that contains 4 bytes of data
    ASSERT_NO_THROW(
        opt= new Option(Option::V4, 123, data);
    );

    // check that content is reported properly
    EXPECT_EQ(123, opt->getType());
    vector<uint8_t> optData = opt->getData();
    ASSERT_EQ(optData.size(), data.size());
    EXPECT_TRUE(optData == data);
    EXPECT_EQ(2, opt->getHeaderLen());
    EXPECT_EQ(6, opt->len());

    // now store that option into a buffer
    OutputBuffer buf(100);
    EXPECT_NO_THROW(
        opt->pack4(buf);
    );

    // check content of that buffer

    // 2 byte header + 4 bytes data
    ASSERT_EQ(6, buf.getLength());

    // that's how this option is supposed to look like
    uint8_t exp[] = { 123, 4, 1, 2, 3, 4 };

    /// TODO: use vector<uint8_t> getData() when it will be implemented
    EXPECT_EQ(0, memcmp(exp, buf.getData(), 6));

    // check that we can destroy that option
    EXPECT_NO_THROW(
        delete opt;
    );
}

// this is almost the same test as v4_data1, but it uses
// different constructor
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

    Option* opt = 0;

    // Create DHCPv4 option of type 123 that contains
    // 4 bytes (sizeof(dummyPayload).
    ASSERT_NO_THROW(
        opt= new Option(Option::V4, 123, data.begin() + 1, data.end() - 1);
    );

    // check that content is reported properly
    EXPECT_EQ(123, opt->getType());
    vector<uint8_t> optData = opt->getData();
    ASSERT_EQ(optData.size(), expData.size());
    EXPECT_TRUE(optData == expData);
    EXPECT_EQ(2, opt->getHeaderLen());
    EXPECT_EQ(6, opt->len());

    // now store that option into a buffer
    OutputBuffer buf(100);
    EXPECT_NO_THROW(
        opt->pack4(buf);
    );

    // check content of that buffer

    // 2 byte header + 4 bytes data
    ASSERT_EQ(6, buf.getLength());

    // that's how this option is supposed to look like
    uint8_t exp[] = { 123, 4, 1, 2, 3, 4 };

    /// TODO: use vector<uint8_t> getData() when it will be implemented
    EXPECT_EQ(0, memcmp(exp, buf.getData(), 6));

    // check that we can destroy that option
    EXPECT_NO_THROW(
        delete opt;
    );
}

TEST_F(OptionTest, v4_toText) {

    vector<uint8_t> buf(3);
    buf[0] = 0;
    buf[1] = 0xf;
    buf[2] = 0xff;

    Option opt(Option::V4, 253, buf);

    EXPECT_EQ("type=253, len=3: 00:0f:ff", opt.toText());
}

// tests simple constructor
TEST_F(OptionTest, v6_basic) {

    Option* opt = new Option(Option::V6, 1);

    EXPECT_EQ(Option::V6, opt->getUniverse());
    EXPECT_EQ(1, opt->getType());
    EXPECT_EQ(0, opt->getData().size());
    EXPECT_EQ(4, opt->len()); // just v6 header

    EXPECT_NO_THROW(
        delete opt;
    );
}

// tests contructor used in pkt reception
// option contains actual data
TEST_F(OptionTest, v6_data1) {
    for (int i = 0; i < 32; i++)
        buf_[i] = 100+i;
    Option* opt = new Option(Option::V6, 333,   //type
                             buf_.begin() + 3,  // begin offset
                             buf_.begin() + 10); // end offset (7 bytes of data)
    EXPECT_EQ(333, opt->getType());

    ASSERT_EQ(11, opt->len());
    ASSERT_EQ(7, opt->getData().size());
    EXPECT_EQ(0, memcmp(&buf_[3], &opt->getData()[0], 7) );

    opt->pack(outBuf_);
    EXPECT_EQ(11, outBuf_.getLength());

    const uint8_t* out = (const uint8_t*)outBuf_.getData();
    EXPECT_EQ(out[0], 333/256); // type
    EXPECT_EQ(out[1], 333%256);

    EXPECT_EQ(out[2], 0); // len
    EXPECT_EQ(out[3], 7);

    // payload
    EXPECT_EQ(0, memcmp(&buf_[3], out+4, 7) );

    EXPECT_NO_THROW(
        delete opt;
    );
}

// another text that tests the same thing, just
// with different input parameters
TEST_F(OptionTest, v6_data2) {

    buf_[0] = 0xa1;
    buf_[1] = 0xa2;
    buf_[2] = 0xa3;
    buf_[3] = 0xa4;

    // create an option (unpack content)
    Option* opt = new Option(Option::V6,
                             D6O_CLIENTID,
                             buf_.begin(),
                             buf_.begin() + 4);

    // pack this option
    opt->pack(outBuf_);

    // 4 bytes header + 4 bytes content
    EXPECT_EQ(8, opt->len());
    EXPECT_EQ(D6O_CLIENTID, opt->getType());

    EXPECT_EQ(8, outBuf_.getLength());

    // check if pack worked properly:
    // if option type is correct
    const uint8_t* out = (const uint8_t*)outBuf_.getData();

    EXPECT_EQ(D6O_CLIENTID, out[0]*256 + out[1]);

    // if option length is correct
    EXPECT_EQ(4, out[2]*256 + out[3]);

    // if option content is correct
    EXPECT_EQ(0, memcmp(&buf_[0], out + 4, 4));

    EXPECT_NO_THROW(
        delete opt;
    );
}

// check that an option can contain 2 suboptions:
// opt1
//  +----opt2
//  |
//  +----opt3
//
TEST_F(OptionTest, v6_suboptions1) {
    for (int i=0; i<128; i++)
        buf_[i] = 100+i;
    Option* opt1 = new Option(Option::V6, 65535, //type
                              buf_.begin(), // 3 bytes of data
                              buf_.begin() + 3);
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

    // payload
    EXPECT_EQ(0, memcmp(outBuf_.getData(), expected, 20) );

    EXPECT_NO_THROW(
        delete opt1;
    );
}

// check that an option can contain nested suboptions:
// opt1
//  +----opt2
//        |
//        +----opt3
//
TEST_F(OptionTest, v6_suboptions2) {
    for (int i=0; i<128; i++)
        buf_[i] = 100+i;
    Option* opt1 = new Option(Option::V6, 65535, //type
                              buf_.begin(),
                              buf_.begin() + 3);
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

    // payload
    EXPECT_EQ(0, memcmp(outBuf_.getData(), expected, 20) );

    EXPECT_NO_THROW(
        delete opt1;
    );
}

TEST_F(OptionTest, v6_addgetdel) {
    for (int i=0; i<128; i++)
        buf_[i] = 100+i;
    Option* parent = new Option(Option::V6, 65535); //type
    OptionPtr opt1(new Option(Option::V6, 1));
    OptionPtr opt2(new Option(Option::V6, 2));
    OptionPtr opt3(new Option(Option::V6, 2));

    parent->addOption(opt1);
    parent->addOption(opt2);

    // getOption() test
    EXPECT_EQ(opt1, parent->getOption(1));
    EXPECT_EQ(opt2, parent->getOption(2));

    // expect NULL
    EXPECT_EQ(OptionPtr(), parent->getOption(4));

    // now there are 2 options of type 2
    parent->addOption(opt3);

    // let's delete one of them
    EXPECT_EQ(true, parent->delOption(2));

    // there still should be the other option 2
    EXPECT_NE(OptionPtr(), parent->getOption(2));

    // let's delete the other option 2
    EXPECT_EQ(true, parent->delOption(2));

    // no more options with type=2
    EXPECT_EQ(OptionPtr(), parent->getOption(2));

    // let's try to delete - should fail
    EXPECT_TRUE(false ==  parent->delOption(2));

    delete parent;
}

TEST_F(OptionTest, v6_toText) {
    buf_[0] = 0;
    buf_[1] = 0xf;
    buf_[2] = 0xff;

    OptionPtr opt(new Option(Option::V6, 258,  buf_.begin(), buf_.begin() + 3 ));

    EXPECT_EQ("type=258, len=3: 00:0f:ff", opt->toText());
}


TEST_F(OptionTest, getUintX) {

    buf_[0] = 0x5;
    buf_[1] = 0x4;
    buf_[2] = 0x3;
    buf_[3] = 0x2;
    buf_[4] = 0x1;

    // five options with varying lengths
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

    // the same as for 4-byte long, just get first 1,2 or 4 bytes
    EXPECT_EQ(5, opt5->getUint8());
    EXPECT_EQ(0x0504, opt5->getUint16());
    EXPECT_EQ(0x05040302, opt5->getUint32());

}

TEST_F(OptionTest, setUintX) {
    OptionPtr opt1(new Option(Option::V4, 125));
    OptionPtr opt2(new Option(Option::V4, 125));
    OptionPtr opt4(new Option(Option::V4, 125));

    // verify setUint8
    opt1->setUint8(255);
    EXPECT_EQ(255, opt1->getUint8());
    opt1->pack4(outBuf_);
    EXPECT_EQ(3, opt1->len());
    EXPECT_EQ(3, outBuf_.getLength());
    uint8_t exp1[] = {125, 1, 255};
    EXPECT_TRUE(0 == memcmp(exp1, outBuf_.getData(), 3));

    // verify getUint16
    outBuf_.clear();
    opt2->setUint16(12345);
    opt2->pack4(outBuf_);
    EXPECT_EQ(12345, opt2->getUint16());
    EXPECT_EQ(4, opt2->len());
    EXPECT_EQ(4, outBuf_.getLength());
    uint8_t exp2[] = {125, 2, 12345/256, 12345%256};
    EXPECT_TRUE(0 == memcmp(exp2, outBuf_.getData(), 4));

    // verify getUint32
    outBuf_.clear();
    opt4->setUint32(0x12345678);
    opt4->pack4(outBuf_);
    EXPECT_EQ(0x12345678, opt4->getUint32());
    EXPECT_EQ(6, opt4->len());
    EXPECT_EQ(6, outBuf_.getLength());
    uint8_t exp4[] = {125, 4, 0x12, 0x34, 0x56, 0x78};
    EXPECT_TRUE(0 == memcmp(exp4, outBuf_.getData(), 6));
}

TEST_F(OptionTest, setData) {
    // verify data override with new buffer larger than
    // initial option buffer size
    OptionPtr opt1(new Option(Option::V4, 125,
                              buf_.begin(), buf_.begin() + 10));
    buf_.resize(20, 1);
    opt1->setData(buf_.begin(), buf_.end());
    opt1->pack4(outBuf_);
    ASSERT_EQ(outBuf_.getLength() - opt1->getHeaderLen(), buf_.size());
    const uint8_t* test_data = static_cast<const uint8_t*>(outBuf_.getData());
    EXPECT_TRUE(0 == memcmp(&buf_[0], test_data + opt1->getHeaderLen(),
                            buf_.size()));

    // verify data override with new buffer shorter than
    // initial option buffer size
    OptionPtr opt2(new Option(Option::V4, 125,
                              buf_.begin(), buf_.begin() + 10));
    outBuf_.clear();
    buf_.resize(5, 1);
    opt2->setData(buf_.begin(), buf_.end());
    opt2->pack4(outBuf_);
    ASSERT_EQ(outBuf_.getLength() - opt1->getHeaderLen(), buf_.size());
    test_data = static_cast<const uint8_t*>(outBuf_.getData());
    EXPECT_TRUE(0 == memcmp(&buf_[0], test_data + opt1->getHeaderLen(),
                            buf_.size()));
}

// This test verifies that options can be compared using equal() method.
TEST_F(OptionTest, equal) {

    // five options with varying lengths
    OptionPtr opt1(new Option(Option::V6, 258, buf_.begin(), buf_.begin() + 1));
    OptionPtr opt2(new Option(Option::V6, 258, buf_.begin(), buf_.begin() + 2));
    OptionPtr opt3(new Option(Option::V6, 258, buf_.begin(), buf_.begin() + 3));

    // the same content as opt2, but different type
    OptionPtr opt4(new Option(Option::V6, 1, buf_.begin(), buf_.begin() + 2));

    // another instance with the same type and content as opt2
    OptionPtr opt5(new Option(Option::V6, 258, buf_.begin(), buf_.begin() + 2));

    EXPECT_TRUE(opt1->equal(opt1));

    EXPECT_FALSE(opt1->equal(opt2));
    EXPECT_FALSE(opt1->equal(opt3));
    EXPECT_FALSE(opt1->equal(opt4));

    EXPECT_TRUE(opt2->equal(opt5));
}
}
