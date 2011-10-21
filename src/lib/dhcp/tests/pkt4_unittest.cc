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
#include <boost/static_assert.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/shared_array.hpp>

#include "io_address.h"
#include "dhcp/pkt4.h"
#include "dhcp/dhcp4.h"
#include "exceptions/exceptions.h"

using namespace std;
using namespace isc;
using namespace isc::asiolink;
using namespace isc::dhcp;
using namespace boost;

// can't compare const to value directly, as it gives strange
// linker errors in gtest.h

static size_t DHCPV4_PKT_HDR_LEN = Pkt4::DHCPV4_PKT_HDR_LEN;

namespace {

TEST(Pkt4Test, constructor) {

    ASSERT_EQ(236U, DHCPV4_PKT_HDR_LEN);
    Pkt4* pkt = 0;

    // minimal 
    uint8_t testData[250];
    for (int i = 0; i < 250; i++) {
        testData[i]=i; 
    }

    // positive case1. Normal received packet
    EXPECT_NO_THROW(
        pkt = new Pkt4(testData, 236);
    );

    EXPECT_EQ(236, pkt->len());

    EXPECT_NO_THROW(
        delete pkt;
        pkt = 0;
    );

    // positive case2. Normal outgoing packet
    EXPECT_NO_THROW(
        pkt = new Pkt4(DHCPDISCOVER, 0xffffffff);
    );

    // DHCPv4 packet must be at least 236 bytes long
    EXPECT_EQ(DHCPV4_PKT_HDR_LEN, pkt->len());
    EXPECT_EQ(DHCPDISCOVER, pkt->getType());
    EXPECT_EQ(0xffffffff, pkt->getTransid());
    EXPECT_NO_THROW(
        delete pkt;
        pkt = 0;
    );

    // negative case. Should drop truncated messages
    EXPECT_THROW(
        pkt = new Pkt4(testData, 235),
        OutOfRange
    );
    if (pkt) {
        // test failed. Exception should have been thrown, but
        // object was created instead. Let's clean this up
        delete pkt;
    }
}

// a sample transaction-id
const static uint32_t dummyTransid = 0x12345678;

// a dummy MAC address
const uint8_t dummyMacAddr[] = {0, 1, 2, 3, 4, 5};

// a dummy MAC address, padded with 0s
const uint8_t dummyChaddr[16] = {0, 1, 2, 3, 4, 5, 0, 0, 
                                 0, 0, 0, 0, 0, 0, 0, 0 };

// let's use some creative test content here (128 chars + \0)
const uint8_t dummyFile[] = "Lorem ipsum dolor sit amet, consectetur "
    "adipiscing elit. Proin mollis placerat metus, at "
    "lacinia orci ornare vitae. Mauris amet.";
    
// yet another type of test content (64 chars + \0)
const uint8_t dummySname[] = "Lorem ipsum dolor sit amet, consectetur "
    "adipiscing elit posuere.";

BOOST_STATIC_ASSERT(sizeof(dummyFile)  == Pkt4::MAX_FILE_LEN + 1);
BOOST_STATIC_ASSERT(sizeof(dummySname) == Pkt4::MAX_SNAME_LEN + 1);

/// Generates test packet
///
/// Allocates and generates test packet, with all fixed
/// fields set to non-zero values. Content is not always
/// reasonable.
///
/// See generateTestPacket2() function that returns
/// exactly the same packet in on-wire format.
///
/// @return pointer to allocated Pkt4 object.
boost::shared_ptr<Pkt4>
generateTestPacket1() {

    boost::shared_ptr<Pkt4> pkt(new Pkt4(DHCPDISCOVER, dummyTransid));
    // hwType = 6(ETHERNET), hlen = 6(MAC address len)
    pkt->setHWAddr(6, 6, dummyMacAddr); 
    pkt->setHops(13); // 13 relays. Wow!
    // transaction-id is already set
    pkt->setSecs(42);
    pkt->setFlags(0xffffU); // all flags set
    pkt->setCiaddr(IOAddress("192.0.2.1"));
    pkt->setYiaddr(IOAddress("1.2.3.4"));
    pkt->setSiaddr(IOAddress("192.0.2.255"));
    pkt->setGiaddr(IOAddress("255.255.255.255"));
    // chaddr already set with setHWAddr()
    pkt->setSname(dummySname, 64); 
    pkt->setFile(dummyFile, 128);

    return (pkt);
}

/// Generates test packet
///
/// Allocates and generates on-wire buffer that represents
/// test packet, with all fixed fields set to non-zero values. 
/// Content is not always reasonable.
///
/// See generateTestPacket1() function that returns
/// exactly the same packet as Pkt4 object.
///
/// @return pointer to allocated Pkt4 object
shared_array<uint8_t>
generateTestPacket2() {

    shared_array<uint8_t> buf(new uint8_t[Pkt4::DHCPV4_PKT_HDR_LEN]);

    // that is only part of the header. It contains all "short" fields, 
    // larger fields are constructed separately
    uint8_t hdr[] = {
        1, 6, 6, 13, // op, htype, hlen, hops,
        0x12, 0x34, 0x56, 0x78, // transaction-id
        0, 42, 0xff, 0xff, // 42 secs, 0xffff flags
        192, 0, 2, 1, // ciaddr
        1, 2, 3, 4, // yiaddr
        192, 0, 2, 255, // siaddr
        255, 255, 255, 255, // giaddr
    };

    BOOST_STATIC_ASSERT(28 == sizeof(hdr));

    size_t offset = 0;

    memcpy(&buf[0] + offset, hdr, sizeof(hdr));
    offset += sizeof(hdr);

    memcpy(&buf[0] + offset, dummyMacAddr, 6); // chaddr is 16 bytes
    offset += Pkt4::MAX_CHADDR_LEN;
    memcpy(&buf[0] + offset, dummySname, 64); // sname is 64 bytes
    offset += Pkt4::MAX_SNAME_LEN;
    memcpy(&buf[0] + offset, dummyFile, 128);
    offset += Pkt4::MAX_FILE_LEN;

    return (buf);
}

TEST(Pkt4Test, fixedFields) {

    shared_ptr<Pkt4> pkt = generateTestPacket1();

    // ok, let's check packet values
    EXPECT_EQ(1, pkt->getOp());
    EXPECT_EQ(6, pkt->getHtype());
    EXPECT_EQ(6, pkt->getHlen());
    EXPECT_EQ(13, pkt->getHops());
    EXPECT_EQ(dummyTransid, pkt->getTransid());
    EXPECT_EQ(42, pkt->getSecs());
    EXPECT_EQ(0xffff, pkt->getFlags());

    EXPECT_EQ(string("192.0.2.1"), pkt->getCiaddr().toText());
    EXPECT_EQ(string("1.2.3.4"), pkt->getYiaddr().toText());
    EXPECT_EQ(string("192.0.2.255"), pkt->getSiaddr().toText());
    EXPECT_EQ(string("255.255.255.255"), pkt->getGiaddr().toText());

    // chaddr is always 16 bytes long and contains link-layer addr (MAC)
    EXPECT_EQ(0, memcmp(dummyChaddr, pkt->getChaddr(), 16));

    EXPECT_EQ(0, memcmp(dummySname, &pkt->getSname()[0], 64));

    EXPECT_EQ(0, memcmp(dummyFile, &pkt->getFile()[0], 128));

    EXPECT_EQ(DHCPDISCOVER, pkt->getType());
}

#if 0
/// TODO Uncomment when ticket #1227 is implemented
TEST(Pkt4Test, fixedFieldsPack) {
    shared_ptr<Pkt4> pkt = generateTestPacket1();
    shared_array<uint8_t> expectedFormat = generateTestPacket2();

    EXPECT_NO_THROW(
        pkt->pack();
    );

    ASSERT_EQ(Pkt4::DHCPV4_PKT_HDR_LEN, pkt->len());

    EXPECT_EQ(0, memcmp(&expectedFormat[0], pkt->getData(), pkt->len()));
}

/// TODO Uncomment when ticket #1226 is implemented
TEST(Pkt4Test, fixedFieldsUnpack) {
    shared_array<uint8_t> expectedFormat = generateTestPkt2();

    shared_ptr<Pkt4> pkt(new Pkt4(&expectedFormat[0], 
                                  Pkt4::DHCPV4_PKT_HDR_LEN));

    // ok, let's check packet values
    EXPECT_EQ(1, pkt->getOp());
    EXPECT_EQ(6, pkt->getHtype());
    EXPECT_EQ(6, pkt->getHlen());
    EXPECT_EQ(13, pkt->getHops());
    EXPECT_EQ(transid, pkt->getTransid());
    EXPECT_EQ(42, pkt->getSecs());
    EXPECT_EQ(0xffff, pkt->getFlags());

    EXPECT_EQ(string("192.0.2.1"), pkt->getCiaddr.toText());
    EXPECT_EQ(string("1.2.3.4"), pkt->getYiaddr.toText());
    EXPECT_EQ(string("192.0.2.255"), pkt->getSiaddr.toText());
    EXPECT_EQ(string("255.255.255.255"), pkt->getGiaddr.toText());

    // chaddr is always 16 bytes long and contains link-layer addr (MAC)
    EXPECT_EQ(0, memcmp(expectedChaddr, pkt->getChaddr(), 16));

    EXPECT_EQ(0, memcmp(expectedSname, pkt->getSname(), 64));

    EXPECT_EQ(0, memcmp(expectedFile, pkt->getFile(), 128));

    EXPECT_EQ(DHCPSOLICIT, pkt->getType());
}
#endif

// this test is for hardware addresses (htype, hlen and chaddr fields)
TEST(Pkt4Test, hwAddr) {

    uint8_t mac[Pkt4::MAX_CHADDR_LEN];
    uint8_t expectedChaddr[Pkt4::MAX_CHADDR_LEN];

    Pkt4* pkt = 0;
    // let's test each hlen, from 0 till 16
    for (int macLen=0; macLen < Pkt4::MAX_CHADDR_LEN; macLen++) {
        for (int i=0; i < Pkt4::MAX_CHADDR_LEN; i++) {
            mac[i] = 0;
            expectedChaddr[i] = 0;
        }
        for (int i=0; i < macLen; i++) {
            mac[i] = 128+i;
            expectedChaddr[i] = 128+i;
        }
        
        // type and transaction doesn't matter in this test
        pkt = new Pkt4(DHCPOFFER, 1234);
        pkt->setHWAddr(255-macLen*10, // just weird htype
                       macLen,
                       mac);
        EXPECT_EQ(0, memcmp(expectedChaddr, pkt->getChaddr(), 
                            Pkt4::MAX_CHADDR_LEN));

#if 0
        /// TODO Uncomment when ticket #1227 is implemented)
        EXPECT_NO_THROW( 
            pkt->pack();
        );

        // CHADDR starts at offset 28 in DHCP packet
        EXPECT_EQ(0, memcmp(pkt->getData()+28, expectedChaddr, 
                            Pkt4::MAX_CHADDR_LEN));
#endif

        delete pkt;
    }

    /// TODO: extend this test once options support is implemented. HW address
    /// longer than 16 bytes should be stored in client-identifier option
}

TEST(Pkt4Test, msgTypes) {

    struct msgType {
        uint8_t dhcp;
        uint8_t bootp;
    };

    msgType types[] = {
        {DHCPDISCOVER, BOOTREQUEST},
        {DHCPOFFER, BOOTREPLY},
        {DHCPREQUEST, BOOTREQUEST},
        {DHCPDECLINE, BOOTREQUEST},
        {DHCPACK, BOOTREPLY},
        {DHCPNAK, BOOTREPLY},
        {DHCPRELEASE, BOOTREQUEST},
        {DHCPINFORM, BOOTREQUEST},
        {DHCPLEASEQUERY, BOOTREQUEST},
        {DHCPLEASEUNASSIGNED, BOOTREPLY},
        {DHCPLEASEUNKNOWN, BOOTREPLY},
        {DHCPLEASEACTIVE, BOOTREPLY}
    };

    Pkt4* pkt = 0;
    for (int i=0; i < sizeof(types)/sizeof(msgType); i++) {

        pkt = new Pkt4(types[i].dhcp, 0);
        EXPECT_EQ(types[i].dhcp, pkt->getType());

        EXPECT_EQ(types[i].bootp, pkt->getOp());

        delete pkt;
        pkt = 0;
    }

    EXPECT_THROW(
        pkt = new Pkt4(100, 0), // there's no message type 100
        OutOfRange
    );
    if (pkt) {
        delete pkt;
    }
}

// this test verifies handling of sname field
TEST(Pkt4Test, sname) {

    uint8_t sname[Pkt4::MAX_SNAME_LEN];
    uint8_t expectedSname[Pkt4::MAX_SNAME_LEN];

    Pkt4* pkt = 0;
    // let's test each sname length, from 0 till 64
    for (int snameLen=0; snameLen < Pkt4::MAX_SNAME_LEN; snameLen++) {
        for (int i=0; i < Pkt4::MAX_SNAME_LEN; i++) {
            sname[i] = 0;
            expectedSname[i] = 0;
        }
        for (int i=0; i < snameLen; i++) {
            sname[i] = i;
            expectedSname[i] = i;
        }
        
        // type and transaction doesn't matter in this test
        pkt = new Pkt4(DHCPOFFER, 1234);
        pkt->setSname(sname, snameLen);

        EXPECT_EQ(0, memcmp(expectedSname, &pkt->getSname()[0], Pkt4::MAX_SNAME_LEN));

#if 0
        /// TODO Uncomment when ticket #1227 is implemented)
        EXPECT_NO_THROW( 
            pkt->pack();
        );

        // SNAME starts at offset 44 in DHCP packet
        EXPECT_EQ(0, memcmp(pkt->getData()+44, expectedChaddr, Pkt4::MAX_SNAME_LEN));
#endif

        delete pkt;
    }
}

TEST(Pkt4Test, file) {

    uint8_t file[Pkt4::MAX_FILE_LEN];
    uint8_t expectedFile[Pkt4::MAX_FILE_LEN];

    Pkt4* pkt = 0;
    // let's test each file length, from 0 till 64
    for (int fileLen=0; fileLen < Pkt4::MAX_FILE_LEN; fileLen++) {
        for (int i=0; i < Pkt4::MAX_FILE_LEN; i++) {
            file[i] = 0;
            expectedFile[i] = 0;
        }
        for (int i=0; i < fileLen; i++) {
            file[i] = i;
            expectedFile[i] = i;
        }
        
        // type and transaction doesn't matter in this test
        pkt = new Pkt4(DHCPOFFER, 1234);
        pkt->setFile(file, fileLen);

        EXPECT_EQ(0, memcmp(expectedFile, &pkt->getFile()[0], Pkt4::MAX_FILE_LEN));

#if 0
        /// TODO Uncomment when ticket #1227 is implemented)
        EXPECT_NO_THROW( 
            pkt->pack();
        );

        // FILE starts at offset 44 in DHCP packet
        EXPECT_EQ(0, memcmp(pkt->getData()+44, expectedChaddr, Pkt4::MAX_FILE_LEN));
#endif

        delete pkt;
    }

}

} // end of anonymous namespace
