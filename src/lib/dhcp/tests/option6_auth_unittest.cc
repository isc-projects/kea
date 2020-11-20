// Copyright (C) 2018-2020 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <dhcp/dhcp6.h>
#include <dhcp/option.h>
#include <dhcp/option6_auth.h>
#include <util/buffer.h>

#include <gtest/gtest.h>
#include <boost/scoped_ptr.hpp>

#include <iostream>
#include <sstream>

using namespace std;
using namespace isc;
using namespace isc::dhcp;
using namespace isc::util;
using boost::scoped_ptr;

namespace {
class Option6AuthTest : public ::testing::Test {
public:
    Option6AuthTest(): buff_(28) { 
    }
    OptionBuffer buff_;
};

// check constructor, setters and getters 
TEST_F(Option6AuthTest, basic) { 

    scoped_ptr<Option6Auth> auth; 
    ASSERT_NO_THROW(auth.reset(new Option6Auth(1,2,0,0x9000,{'a','b','c','d'})));

    ASSERT_EQ(1, auth->getProtocol());
    ASSERT_EQ(2, auth->getHashAlgo());
    ASSERT_EQ(0, auth->getReplyDetectionMethod());
    ASSERT_EQ(0x9000, auth->getReplyDetectionValue());
    
    std::vector<uint8_t> test_buf = {'a','b','c','d'};
    ASSERT_EQ(test_buf, auth->getAuthInfo());

    auth->setProtocol(2);
    auth->setHashAlgo(3);
    auth->setReplyDetectionMethod(1);
    auth->setReplyDetectionValue(109034830);
    auth->setAuthInfo({1,2,3,4});

    ASSERT_EQ(2, auth->getProtocol());
    ASSERT_EQ(3, auth->getHashAlgo());
    ASSERT_EQ(1, auth->getReplyDetectionMethod());
    ASSERT_EQ(109034830, auth->getReplyDetectionValue());
    
    test_buf = {1,2,3,4};
    ASSERT_EQ(test_buf, auth->getAuthInfo());
}

//Check if all the fields are properly parsed and stored
// todo define userdefined literal and add packing function to it
TEST_F(Option6AuthTest, parseFields) { 
    buff_[0] = 0xa1; //protocol
    buff_[1] = 0xa2; //algo
    buff_[2] = 0xa3; //rdm method
    buff_[3] = 0xa4; //rdm value
    buff_[4] = 0xa5; //rdm value
    buff_[5] = 0xa6; //rdm value
    buff_[6] = 0xa7; //rdm value
    buff_[7] = 0xa8; //rdm value
    buff_[8] = 0xa9; //rdm value
    buff_[9] = 0xaa; //rdm value
    buff_[10] = 0xab; //rdm value
    for ( uint8_t i = 11; i < 27; i++ ) {
        buff_[i] = 0xa8; //auth info 16 bytes
    }

    scoped_ptr<Option6Auth> auth;
    auth.reset(new Option6Auth(1,2,0,9000,{'a','b','c','d'}));

    auth->unpack(buff_.begin(), buff_.begin()+27); //26 element is 16 byte offset from 10
    
    std::vector<uint8_t> test_buf(16,0xa8);
    ASSERT_EQ(0xa1, auth->getProtocol());
    ASSERT_EQ(0xa2, auth->getHashAlgo());
    ASSERT_EQ(0xa3, auth->getReplyDetectionMethod());
    ASSERT_EQ(0xa4a5a6a7a8a9aaab, auth->getReplyDetectionValue());
    ASSERT_EQ(test_buf, auth->getAuthInfo());
}

//Check of the options are correctly packed and set
TEST_F(Option6AuthTest, setFields) {
    scoped_ptr<Option6Auth> auth;
    std::vector<uint8_t> test_buf(16,0xa8);
    auth.reset(new Option6Auth(1,2,0,0x0090000000000000,test_buf));
    
    isc::util::OutputBuffer buf(31);//4 header + fixed 11 and key 16
    ASSERT_NO_THROW(auth->pack(buf));

    const uint8_t ref_data[] = {
        0, 11, 0, 27, 1, 2, 0, //header , proto algo method
        0, 0x90, 0, 0, 0, 0, 0, 0, //64 bit rdm field
        0xa8, 0xa8, 0xa8, 0xa8, //128 bits/16 byte key
        0xa8, 0xa8, 0xa8, 0xa8,
        0xa8, 0xa8, 0xa8, 0xa8,
        0xa8, 0xa8, 0xa8, 0xa8
    };
    //first check if they are of equal size
    ASSERT_EQ(buf.getLength(), sizeof(ref_data));

    //evaluate the contents of the option byte by byte
    ASSERT_EQ(0, memcmp(ref_data, buf.getData(), buf.getLength()));
}

TEST_F(Option6AuthTest, checkHashInput) {
    scoped_ptr<Option6Auth> auth;
    
    std::vector<uint8_t> test_buf(16,0xa8);
    std::vector<uint8_t> hash_op(16,0x00);
    auth.reset(new Option6Auth(1,2,0,0x0102030405060708,test_buf));

    isc::util::OutputBuffer buf(31); 
    ASSERT_NO_THROW(auth->packHashInput(buf));
   //auth info must be 0 for calculating the checksum
    const uint8_t ref_data[] = {
        0, 11, 0, 27, 1, 2, 0, //header , proto algo method
        0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, //64 bit rdm field
        0x00, 0x00, 0x00, 0x00, //128 bits/16 byte key
        0x00, 0x00, 0x00, 0x00, //128 bits/16 byte key
        0x00, 0x00, 0x00, 0x00, //128 bits/16 byte key
        0x00, 0x00, 0x00, 0x00, //128 bits/16 byte key
    };
    //first check if they are of equal size
    ASSERT_EQ(buf.getLength(), sizeof(ref_data));

    //evaluate the contents of the option byte by byte
    ASSERT_EQ(0, memcmp(ref_data, buf.getData(), buf.getLength()));
}

TEST_F(Option6AuthTest, negativeCase) {
     scoped_ptr<Option6Auth> auth;

     std::vector<uint8_t> test_buf(16,0xa8);
     auth.reset(new Option6Auth(1,2,0,0x0102030405060708,test_buf));
     //allocate less space to force an exception to be thrown
     isc::util::OutputBuffer buf(20);

     ASSERT_THROW(auth->pack(buf), isc::OutOfRange);
     ASSERT_THROW(auth->packHashInput(buf), isc::OutOfRange);
}

// Checks whether the to text conversion is working ok.
TEST_F(Option6AuthTest, toText) {
    scoped_ptr<Option6Auth> auth;
    auth.reset(new Option6Auth(1,2,0,9000,{'a','b','c','d'}));

    string exp_txt = "  protocol=1, algorithm=2, rdm method=0, rdm value=9000, value=61626364";

    std::cout << auth->toText(2) << std::endl;

}

} //end namespace
