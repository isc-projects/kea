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

#include "dhcp/dhcp6.h"
#include "dhcp/option.h"

using namespace std;
using namespace isc;
using namespace isc::dhcp;

namespace {
class OptionTest : public ::testing::Test {
public:
    OptionTest() {
    }
};

// v4 is not really implemented yet. A simple test will do for now
TEST_F(OptionTest, basic4) {

    Option* opt = new Option(Option::V4, 17);

    EXPECT_EQ(17, opt->getType());
    EXPECT_EQ(NULL, opt->getData());
    EXPECT_EQ(2, opt->len()); // just v4 header

    delete opt;
}

// tests simple constructor
TEST_F(OptionTest, basic6) {

    Option* opt = new Option(Option::V6, 1);

    EXPECT_EQ(1, opt->getType());
    EXPECT_EQ(NULL, opt->getData());
    EXPECT_EQ(4, opt->len()); // just v6 header

    delete opt;
}

// tests contructor used in pkt reception
// option contains actual data
TEST_F(OptionTest, data1) {
    boost::shared_array<uint8_t> buf(new uint8_t[32]);
    for (int i=0; i<32; i++)
        buf[i] = 100+i;
    Option* opt = new Option(Option::V6, 333, //type
                             buf,
                             3, // offset
                             7); // 7 bytes of data
    EXPECT_EQ(333, opt->getType());
    ASSERT_EQ(&buf[3], opt->getData());
    ASSERT_EQ(11, opt->len());
    EXPECT_EQ(0, memcmp(&buf[3], opt->getData(), 7) );

    int offset = opt->pack(buf, 32, 20);
    EXPECT_EQ(31, offset);

    EXPECT_EQ(buf[20], 333/256); // type
    EXPECT_EQ(buf[21], 333%256);

    EXPECT_EQ(buf[22], 0); // len
    EXPECT_EQ(buf[23], 7);

    // payload
    EXPECT_EQ(0, memcmp(&buf[3], &buf[24], 7) );

    delete opt;
}

// another text that tests the same thing, just
// with different input parameters
TEST_F(OptionTest, data2) {

    boost::shared_array<uint8_t> simple_buf(new uint8_t[128]);
    for (int i=0; i<128; i++)
        simple_buf[i] = 0;
    simple_buf[0]=0xa1;
    simple_buf[1]=0xa2;
    simple_buf[2]=0xa3;
    simple_buf[3]=0xa4;

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

    delete opt;
}

// check that an option can contain 2 suboptions:
// opt1
//  +----opt2
//  |
//  +----opt3
//
TEST_F(OptionTest, suboptions1) {
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

    delete opt1;
}

// check that an option can contain 2 suboptions:
// opt1
//  +----opt2
//        |
//        +----opt3
//
TEST_F(OptionTest, suboptions2) {
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

    delete opt1;
}

TEST_F(OptionTest, addgetdel) {
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
