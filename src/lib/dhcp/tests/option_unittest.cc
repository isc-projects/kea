// Copyright (C) 2011  Internet Systems Consortium, Inc. ("ISC")
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
#include <iostream>
#include <sstream>

#include <arpa/inet.h>
#include <gtest/gtest.h>
#include <boost/shared_ptr.hpp>
#include <exceptions/exceptions.h>
#include <util/buffer.h>

#include "dhcp/dhcp6.h"
#include "dhcp/option.h"

using namespace std;
using namespace isc;
using namespace isc::dhcp;
using namespace isc::util;

namespace {
class OptionTest : public ::testing::Test {
public:
    OptionTest() {
    }
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
    if (opt) {
        delete opt;
        opt = 0;
    }
}

const uint8_t dummyPayload[] =
{ 1, 2, 3, 4};

TEST_F(OptionTest, v4_data1) {

    vector<uint8_t> data(dummyPayload, dummyPayload + sizeof(dummyPayload));

    Option* opt = 0;

    // create DHCPv4 option of type 123
    // that contains 4 bytes of data
    ASSERT_NO_THROW(
        opt= new Option(Option::V4,
                        123, // type
                        data);
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
        opt= new Option(Option::V4,
                        123, // type
                        data.begin() + 1,
                        data.end() - 1);
    );

    // check that content is reported properly
    EXPECT_EQ(123, opt->getType());
    vector<uint8_t> optData = opt->getData();
    ASSERT_EQ(optData.size(), expData.size());
    EXPECT_EQ(optData, expData);
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
    boost::shared_array<uint8_t> buf(new uint8_t[32]);
    for (int i = 0; i < 32; i++)
        buf[i] = 100+i;
    Option* opt = new Option(Option::V6, 333, //type
                             buf,
                             3, // offset
                             7); // 7 bytes of data
    EXPECT_EQ(333, opt->getType());

    ASSERT_EQ(11, opt->len());
    ASSERT_EQ(7, opt->getData().size());
    EXPECT_EQ(0, memcmp(&buf[3], &opt->getData()[0], 7) );

    int offset = opt->pack(buf, 32, 20);
    EXPECT_EQ(31, offset);

    EXPECT_EQ(buf[20], 333/256); // type
    EXPECT_EQ(buf[21], 333%256);

    EXPECT_EQ(buf[22], 0); // len
    EXPECT_EQ(buf[23], 7);

    // payload
    EXPECT_EQ(0, memcmp(&buf[3], &buf[24], 7) );

    EXPECT_NO_THROW(
        delete opt;
    );
}

// another text that tests the same thing, just
// with different input parameters
TEST_F(OptionTest, v6_data2) {

    boost::shared_array<uint8_t> simple_buf(new uint8_t[128]);
    for (int i = 0; i < 128; i++)
        simple_buf[i] = 0;
    simple_buf[0] = 0xa1;
    simple_buf[1] = 0xa2;
    simple_buf[2] = 0xa3;
    simple_buf[3] = 0xa4;

    // create an option (unpack content)
    Option* opt = new Option(Option::V6,
                             D6O_CLIENTID,
                             simple_buf,
                             0,
                             4);

    // pack this option again in the same buffer, but in
    // different place
    int offset18 = opt->pack(simple_buf, 128, 10);

    // 4 bytes header + 4 bytes content
    EXPECT_EQ(8, opt->len());
    EXPECT_EQ(D6O_CLIENTID, opt->getType());

    EXPECT_EQ(offset18, 18);

    // check if pack worked properly:
    // if option type is correct
    EXPECT_EQ(D6O_CLIENTID, simple_buf[10]*256 + simple_buf[11]);

    // if option length is correct
    EXPECT_EQ(4, simple_buf[12]*256 + simple_buf[13]);

    // if option content is correct
    EXPECT_EQ(0, memcmp(&simple_buf[0], &simple_buf[14],4));

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
    boost::shared_array<uint8_t> buf(new uint8_t[128]);
    for (int i=0; i<128; i++)
        buf[i] = 100+i;
    Option* opt1 = new Option(Option::V6, 65535, //type
                              buf,
                              0, // offset
                              3); // 3 bytes of data
    boost::shared_ptr<Option> opt2(new Option(Option::V6, 13));
    boost::shared_ptr<Option> opt3(new Option(Option::V6, 7,
                                              buf,
                                              3, // offset
                                              5)); // 5 bytes of data
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

    int offset = opt1->pack(buf, 128, 20);
    EXPECT_EQ(40, offset);

    // payload
    EXPECT_EQ(0, memcmp(&buf[20], expected, 20) );

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
    boost::shared_array<uint8_t> buf(new uint8_t[128]);
    for (int i=0; i<128; i++)
        buf[i] = 100+i;
    Option* opt1 = new Option(Option::V6, 65535, //type
                              buf,
                              0, // offset
                              3); // 3 bytes of data
    boost::shared_ptr<Option> opt2(new Option(Option::V6, 13));
    boost::shared_ptr<Option> opt3(new Option(Option::V6, 7,
                                              buf,
                                              3, // offset
                                              5)); // 5 bytes of data
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

    int offset = opt1->pack(buf, 128, 20);
    EXPECT_EQ(40, offset);

    // payload
    EXPECT_EQ(0, memcmp(&buf[20], expected, 20) );

    EXPECT_NO_THROW(
        delete opt1;
    );
}

TEST_F(OptionTest, v6_addgetdel) {
    boost::shared_array<uint8_t> buf(new uint8_t[128]);
    for (int i=0; i<128; i++)
        buf[i] = 100+i;
    Option* parent = new Option(Option::V6, 65535); //type
    boost::shared_ptr<Option> opt1(new Option(Option::V6, 1));
    boost::shared_ptr<Option> opt2(new Option(Option::V6, 2));
    boost::shared_ptr<Option> opt3(new Option(Option::V6, 2));

    parent->addOption(opt1);
    parent->addOption(opt2);

    // getOption() test
    EXPECT_EQ(opt1, parent->getOption(1));
    EXPECT_EQ(opt2, parent->getOption(2));

    // expect NULL
    EXPECT_EQ(boost::shared_ptr<Option>(), parent->getOption(4));

    // now there are 2 options of type 2
    parent->addOption(opt3);

    // let's delete one of them
    EXPECT_EQ(true, parent->delOption(2));

    // there still should be the other option 2
    EXPECT_NE(boost::shared_ptr<Option>(), parent->getOption(2));

    // let's delete the other option 2
    EXPECT_EQ(true, parent->delOption(2));

    // no more options with type=2
    EXPECT_EQ(boost::shared_ptr<Option>(), parent->getOption(2));

    // let's try to delete - should fail
    EXPECT_TRUE(false ==  parent->delOption(2));
}

}

TEST_F(OptionTest, v6_toText) {
    boost::shared_array<uint8_t> buf(new uint8_t[3]);
    buf[0] = 0;
    buf[1] = 0xf;
    buf[2] = 0xff;

    boost::shared_ptr<Option> opt(new Option(Option::V6, 258,
                                             buf, 0, 3));

    EXPECT_EQ("type=258, len=3: 00:0f:ff", opt->toText());
}
