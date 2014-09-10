// Copyright (C) 2011-2014  Internet Systems Consortium, Inc. ("ISC")
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
#include <dhcp/dhcp4.h>
#include <dhcp/dhcp6.h>
#include <dhcp/libdhcp++.h>
#include <dhcp/docsis3_option_defs.h>
#include <dhcp/option_string.h>
#include <dhcp/pkt4.h>
#include <dhcp/pkt6.h>
#include <dhcp/option.h>
#include <exceptions/exceptions.h>
#include <util/buffer.h>
#include <dhcp/pkt4o6.h>
#include <boost/shared_array.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/static_assert.hpp>
#include <gtest/gtest.h>

#include <iostream>
#include <sstream>

#include <arpa/inet.h>

using namespace std;
using namespace isc;
using namespace isc::asiolink;
using namespace isc::dhcp;
using namespace isc::util;

namespace {

//Test buffer length
const int LENGTH = 250;

/// @brief A test fixture class for Pkt4o6.
class Pkt4o6Test : public ::testing::Test {
public:
    
    /// @brief Constructor.
    Pkt4o6Test() {
        for (int i = 0; i < LENGTH; i++) {
            testData[i] = i;
        }
    }
    
    /// @brief Generate a 4o6 packet for testing.
    ///
    /// It first generates a Pkt6, and then generates a Pkt4o6 from the Pkt6.
    ///
    /// @return A pointer to allocated Pkt4o6 object
    Pkt4o6Ptr generatePkt4o6(){
	    //First generate a Pkt6
        Pkt6Ptr pkt6(new Pkt6(testData, LENGTH));
        pkt6->setType(DHCPV4_QUERY);
        pkt6->setRemotePort(546);
        pkt6->setRemoteAddr(IOAddress("fe80::21e:8cff:fe9b:7349"));
        pkt6->setLocalPort(0);
        pkt6->setLocalAddr(IOAddress("ff02::1:2"));
        pkt6->setIndex(2);
        pkt6->setIface("eth0");
        
        //Then generate a Pkt4, and put it into a OPTION_DHCPV4_MSG of the pkt6
        Pkt4Ptr pkt4(new Pkt4(testData, LENGTH));
        pkt4->repack();
        isc::util::OutputBuffer tmp = pkt4->getBuffer();
        OptionBuffer p((uint8_t*)tmp.getData(),
                       (uint8_t*)tmp.getData() + tmp.getLength());
        OptionPtr opt = OptionPtr(new Option(Option::V6, OPTION_DHCPV4_MSG, p));
        pkt6->addOption(opt);
        
	    //Finally generate a Pkt4o6
        Pkt4o6Ptr pkt4o6(new Pkt4o6(pkt6));
        return pkt4o6;
    }

    /// @brief Generate a 4o6 packet for testing.
    ///
    /// It generates a Pkt4o6 directly from raw data.
    ///
    /// @return A pointer to allocated Pkt4o6 object
    Pkt4o6Ptr generatePkt4o6_2(){
        Pkt4o6Ptr pkt4o6(new Pkt4o6(testData, LENGTH, testData, LENGTH));
        return pkt4o6;
    }

protected:    
    ///Buffer for test data
    uint8_t testData[LENGTH];
};


//Test Pkt4o6 class constructor
TEST_F(Pkt4o6Test, constructor) {
    Pkt4o6Ptr pkt4o6;
    uint8_t* data;
    Pkt6Ptr pkt6;
    Pkt4Ptr pkt4;

    //Case 1:test Pkt4o6::Pkt4o6(const Pkt6Ptr& pkt6)
    pkt6 = Pkt6Ptr(new Pkt6(testData, LENGTH));
    pkt4 = Pkt4Ptr(new Pkt4(testData, LENGTH));
    pkt4->repack();
    isc::util::OutputBuffer tmp = pkt4->getBuffer();
    OptionBuffer buf((uint8_t*)tmp.getData(),
                     (uint8_t*)tmp.getData() + tmp.getLength());
    OptionPtr opt(new Option(Option::V6, OPTION_DHCPV4_MSG, buf));
    
    EXPECT_THROW(
        pkt4o6 = Pkt4o6Ptr(new Pkt4o6(pkt6)),
        Pkt4o6ConstructError
    );
    pkt6->setType(DHCPV4_QUERY);
    EXPECT_THROW(
        pkt4o6 = Pkt4o6Ptr(new Pkt4o6(pkt6)),
        Pkt4o6ConstructError
    );
    pkt6->addOption(opt);
    EXPECT_NO_THROW(
        pkt4o6 = Pkt4o6Ptr(new Pkt4o6(pkt6))
    );
    pkt4 = pkt4o6->getPkt4();
    ASSERT_EQ(LENGTH, pkt4->getBuffer().getLength());
    data = (uint8_t*)pkt4->getBuffer().getData();
    for(int i = 0;i < LENGTH;i++)
	    EXPECT_EQ(i, data[i]);

	//Case 2: test Pkt4o6::Pkt4o6(const uint8_t* data4, size_t len4, 
	//                            const uint8_t* data6, size_t len6)
    
    pkt4o6 = Pkt4o6Ptr(new Pkt4o6(testData, LENGTH, testData, LENGTH));
    pkt4 = pkt4o6->getPkt4();
    pkt6 = pkt4o6->getPkt6();
    
    ASSERT_EQ(LENGTH, pkt4->getBuffer().getLength());
    ASSERT_EQ(LENGTH, pkt6->getBuffer().getLength());
    data = (uint8_t*)pkt4->getBuffer().getData();
    for(int i = 0;i < LENGTH;i++)
	    EXPECT_EQ(i, data[i]);
    data = (uint8_t*)pkt6->getBuffer().getData();
    for(int i = 0;i < LENGTH;i++){
	    EXPECT_EQ(i,data[i]);
    }

    //Case 3:test Pkt4o6::Pkt4o6(const Pkt4o6Ptr& pkt4o6, const Pkt4Ptr& pkt4)
    const int LEN2 = 240;
    uint8_t newData[LEN2];
    for(int i = 0 ;i < LEN2;i++)
	    newData[i] = i + 2;

    pkt4 = Pkt4Ptr(new Pkt4(newData, LEN2));
	
	//Create testing PKt4o6 now 
    pkt4o6 = Pkt4o6Ptr(new Pkt4o6(pkt4o6, pkt4));
    pkt4 = pkt4o6->getPkt4();
    pkt6 = pkt4o6->getPkt6();
    pkt4->repack();
    //pkt6->repack();
    ASSERT_EQ(LEN2, pkt4->getBuffer().getLength());
    ASSERT_EQ(LENGTH, pkt6->getBuffer().getLength());
    data = (uint8_t*)pkt4->getBuffer().getData();
    for(int i = 0;i < LEN2;i++)
	    EXPECT_EQ(i + 2, data[i]);
    data = (uint8_t*)pkt6->getBuffer().getData();
    for(int i = 0;i < LENGTH;i++){
	    EXPECT_EQ(i,data[i]);
    }

}

//Test setJsonAttribute and getJsonAttribute
TEST_F(Pkt4o6Test, jsonAttribute) {

    Pkt4o6Ptr pkt4o6 = generatePkt4o6();
	
	//store pkt4o6 josn info.
    std::string json = pkt4o6->getJsonAttribute();
    Pkt4o6Ptr pkt4o6_ = generatePkt4o6_2();
    pkt4o6_->setJsonAttribute(json);
    int RemotePort = 546; 
    std::string RemoteAddr("fe80::21e:8cff:fe9b:7349");
    int LocalPort = 0;
    std::string LocalAddr("ff02::1:2");
    int Index = 2;
    std::string Iface("eth0");
	
	// test current pkt4o6 json info.
    Pkt6Ptr v6(pkt4o6_->getPkt6());
    EXPECT_EQ(RemotePort,v6->getRemotePort());
    EXPECT_EQ(RemoteAddr,v6->getRemoteAddr().toText());
    EXPECT_EQ(LocalPort,v6->getLocalPort());
    EXPECT_EQ(LocalAddr,v6->getLocalAddr().toText());
    EXPECT_EQ(Index,v6->getIndex());
    EXPECT_EQ(Iface,v6->getIface());
}

//Test DHCPv4MsgOption
TEST_F(Pkt4o6Test, generateDHCPv4MsgOption) {
    Pkt4o6Ptr pkt4o6 = generatePkt4o6();
	
	//get DHCPv4MsgOption from Pkt4o6
    OptionBuffer buf(pkt4o6->getDHCPv4MsgOption());
    for(int i = 0;i < LENGTH;i++)
	    EXPECT_EQ(i,buf[i]);

}

//Test unicast/broadcast flag
TEST_F(Pkt4o6Test, unicastFlag) {
    //create and test a broadcast packet
    uint8_t buf0[] = {DHCPV4_QUERY, 0, 0, 0};//U=0
    Pkt4o6Ptr pkt4o6;
    pkt4o6 = Pkt4o6Ptr(new Pkt4o6(testData, LENGTH, buf0, sizeof(buf0)));
    pkt4o6->setPkt4LocalAddr();
    EXPECT_EQ("255.255.255.255", pkt4o6->getPkt4()->getLocalAddr().toText());
    
    //create and test a unicast packet
    uint8_t buf1[] = {DHCPV4_QUERY, 0x80, 0, 0};//U=1
    pkt4o6 = Pkt4o6Ptr(new Pkt4o6(testData, LENGTH, buf1, sizeof(buf0)));
    pkt4o6->setPkt4LocalAddr();
    EXPECT_NE("255.255.255.255", pkt4o6->getPkt4()->getLocalAddr().toText());
}

} // end of anonymous namespace
