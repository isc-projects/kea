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

namespace {

TEST(Pkt4Test, constructor) {

    ASSERT_EQ(236U, static_cast<size_t>(Pkt4::DHCPV4_PKT_HDR_LEN) );
    Pkt4* pkt = 0;

    // Just some dummy payload.
    uint8_t testData[250];
    for (int i = 0; i < 250; i++) {
        testData[i]=i;
    }

    // Positive case1. Normal received packet.
    EXPECT_NO_THROW(
        pkt = new Pkt4(testData, Pkt4::DHCPV4_PKT_HDR_LEN);
    );

    EXPECT_EQ(static_cast<size_t>(Pkt4::DHCPV4_PKT_HDR_LEN), pkt->len());

    EXPECT_NO_THROW(
        delete pkt;
        pkt = 0;
    );

    // Positive case2. Normal outgoing packet.
    EXPECT_NO_THROW(
        pkt = new Pkt4(DHCPDISCOVER, 0xffffffff);
    );

    // DHCPv4 packet must be at least 236 bytes long
    EXPECT_EQ(static_cast<size_t>(Pkt4::DHCPV4_PKT_HDR_LEN), pkt->len());
    EXPECT_EQ(DHCPDISCOVER, pkt->getType());
    EXPECT_EQ(0xffffffff, pkt->getTransid());
    EXPECT_NO_THROW(
        delete pkt;
        pkt = 0;
    );

    // Negative case. Should drop truncated messages.
    EXPECT_THROW(
        pkt = new Pkt4(testData, Pkt4::DHCPV4_PKT_HDR_LEN-1),
        OutOfRange
    );
    if (pkt) {
        // Test failed. Exception should have been thrown, but
        // object was created instead. Let's clean this up.
        delete pkt;
        pkt = 0;
    }
}

// a sample data
const static uint8_t dummyOp = BOOTREQUEST;
const static uint8_t dummyHtype = 6;
const static uint8_t dummyHlen = 6;
const static uint8_t dummyHops = 13;
const static uint32_t dummyTransid = 0x12345678;
const static uint16_t dummySecs = 42;
const static uint16_t dummyFlags = BOOTP_BROADCAST;

const static IOAddress dummyCiaddr("192.0.2.1");
const static IOAddress dummyYiaddr("1.2.3.4");
const static IOAddress dummySiaddr("192.0.2.255");
const static IOAddress dummyGiaddr("255.255.255.255");

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

/// @brief Generates test packet.
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

    vector<uint8_t> vectorMacAddr(dummyMacAddr, dummyMacAddr
                                  +sizeof(dummyMacAddr));

    // hwType = 6(ETHERNET), hlen = 6(MAC address len)
    pkt->setHWAddr(dummyHtype, dummyHlen, vectorMacAddr);
    pkt->setHops(dummyHops); // 13 relays. Wow!
    // Transaction-id is already set.
    pkt->setSecs(dummySecs);
    pkt->setFlags(dummyFlags); // all flags set
    pkt->setCiaddr(dummyCiaddr);
    pkt->setYiaddr(dummyYiaddr);
    pkt->setSiaddr(dummySiaddr);
    pkt->setGiaddr(dummyGiaddr);
    // Chaddr already set with setHWAddr().
    pkt->setSname(dummySname, 64);
    pkt->setFile(dummyFile, 128);

    return (pkt);
}

/// @brief Generates test packet.
///
/// Allocates and generates on-wire buffer that represents
/// test packet, with all fixed fields set to non-zero values.
/// Content is not always reasonable.
///
/// See generateTestPacket1() function that returns
/// exactly the same packet as Pkt4 object.
///
/// @return pointer to allocated Pkt4 object
// Returns a vector containing a DHCPv4 packet header.
#if 0
vector<uint8_t>
generateTestPacket2() {

    // That is only part of the header. It contains all "short" fields,
    // larger fields are constructed separately.
    uint8_t hdr[] = {
        1, 6, 6, 13,            // op, htype, hlen, hops,
        0x12, 0x34, 0x56, 0x78, // transaction-id
        0, 42, 0x80, 0x00,      // 42 secs, BROADCAST flags
        192, 0, 2, 1,           // ciaddr
        1, 2, 3, 4,             // yiaddr
        192, 0, 2, 255,         // siaddr
        255, 255, 255, 255,     // giaddr
    };

    // Initialize the vector with the header fields defined above.
    vector<uint8_t> buf(hdr, hdr + sizeof(hdr));

    // Append the large header fields.
    copy(dummyMacAddr, dummyMacAddr + Pkt4::MAX_CHADDR_LEN, back_inserter(buf));
    copy(dummySname, dummySname + Pkt4::MAX_SNAME_LEN, back_inserter(buf));
    copy(dummyFile, dummyFile + Pkt4::MAX_FILE_LEN, back_inserter(buf));

    // Should now have all the header, so check.  The "static_cast" is used
    // to get round an odd bug whereby the linker appears not to find the
    // definition of DHCPV4_PKT_HDR_LEN if it appears within an EXPECT_EQ().
    EXPECT_EQ(static_cast<size_t>(Pkt4::DHCPV4_PKT_HDR_LEN), buf.size());

    return (buf);
}
#endif

TEST(Pkt4Test, fixedFields) {

    shared_ptr<Pkt4> pkt = generateTestPacket1();

    // ok, let's check packet values
    EXPECT_EQ(dummyOp, pkt->getOp());
    EXPECT_EQ(dummyHtype, pkt->getHtype());
    EXPECT_EQ(dummyHlen, pkt->getHlen());
    EXPECT_EQ(dummyHops, pkt->getHops());
    EXPECT_EQ(dummyTransid, pkt->getTransid());
    EXPECT_EQ(dummySecs, pkt->getSecs());
    EXPECT_EQ(dummyFlags, pkt->getFlags());

    EXPECT_EQ(dummyCiaddr.toText(), pkt->getCiaddr().toText());
    EXPECT_EQ(dummyYiaddr.toText(), pkt->getYiaddr().toText());
    EXPECT_EQ(dummySiaddr.toText(), pkt->getSiaddr().toText());
    EXPECT_EQ(dummyGiaddr.toText(), pkt->getGiaddr().toText());

    // chaddr is always 16 bytes long and contains link-layer addr (MAC)
    EXPECT_EQ(0, memcmp(dummyChaddr, pkt->getChaddr(), 16));

    EXPECT_EQ(0, memcmp(dummySname, &pkt->getSname()[0], 64));

    EXPECT_EQ(0, memcmp(dummyFile, &pkt->getFile()[0], 128));

    EXPECT_EQ(DHCPDISCOVER, pkt->getType());
}

TEST(Pkt4Test, fixedFieldsPack) {
    shared_ptr<Pkt4> pkt = generateTestPacket1();
    vector<uint8_t> expectedFormat = generateTestPacket2();

    EXPECT_NO_THROW(
        pkt->pack();
    );

    ASSERT_EQ(static_cast<size_t>(Pkt4::DHCPV4_PKT_HDR_LEN), pkt->len());

    // redundant but MUCH easier for debug in gdb
    const uint8_t * exp = &expectedFormat[0];
    const uint8_t * got = static_cast<const uint8_t*>(pkt->getBuffer().getData());

    EXPECT_EQ(0, memcmp(exp, got, Pkt4::DHCPV4_PKT_HDR_LEN));
}

/// TODO Uncomment when ticket #1226 is implemented
TEST(Pkt4Test, fixedFieldsUnpack) {
    vector<uint8_t> expectedFormat = generateTestPacket2();

    shared_ptr<Pkt4> pkt(new Pkt4(&expectedFormat[0],
                                  Pkt4::DHCPV4_PKT_HDR_LEN));

    EXPECT_NO_THROW(
        pkt->unpack()
    );

    // ok, let's check packet values
    EXPECT_EQ(dummyOp, pkt->getOp());
    EXPECT_EQ(dummyHtype, pkt->getHtype());
    EXPECT_EQ(dummyHlen, pkt->getHlen());
    EXPECT_EQ(dummyHops, pkt->getHops());
    EXPECT_EQ(dummyTransid, pkt->getTransid());
    EXPECT_EQ(dummySecs, pkt->getSecs());
    EXPECT_EQ(dummyFlags, pkt->getFlags());

    EXPECT_EQ(dummyCiaddr.toText(), pkt->getCiaddr().toText());
    EXPECT_EQ(string("1.2.3.4"), pkt->getYiaddr().toText());
    EXPECT_EQ(string("192.0.2.255"), pkt->getSiaddr().toText());
    EXPECT_EQ(string("255.255.255.255"), pkt->getGiaddr().toText());

    // chaddr is always 16 bytes long and contains link-layer addr (MAC)
    EXPECT_EQ(0, memcmp(dummyChaddr, pkt->getChaddr(), Pkt4::MAX_CHADDR_LEN));

    ASSERT_EQ(static_cast<size_t>(Pkt4::MAX_SNAME_LEN), pkt->getSname().size());
    EXPECT_EQ(0, memcmp(dummySname, &pkt->getSname()[0], Pkt4::MAX_SNAME_LEN));

    ASSERT_EQ(static_cast<size_t>(Pkt4::MAX_FILE_LEN), pkt->getFile().size());
    EXPECT_EQ(0, memcmp(dummyFile, &pkt->getFile()[0], Pkt4::MAX_FILE_LEN));

    EXPECT_EQ(DHCPDISCOVER, pkt->getType());
}

// this test is for hardware addresses (htype, hlen and chaddr fields)
TEST(Pkt4Test, hwAddr) {

    vector<uint8_t> mac;
    uint8_t expectedChaddr[Pkt4::MAX_CHADDR_LEN];

    mac.resize(Pkt4::MAX_CHADDR_LEN);

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

        EXPECT_NO_THROW(
            pkt->pack();
        );

        // CHADDR starts at offset 28 in DHCP packet
        const uint8_t* ptr =
            static_cast<const uint8_t*>(pkt->getBuffer().getData())+28;

        EXPECT_EQ(0, memcmp(ptr, expectedChaddr, Pkt4::MAX_CHADDR_LEN));

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

    Pkt4* pkt = 0;
    // let's test each sname length, from 0 till 64
    for (int snameLen=0; snameLen < Pkt4::MAX_SNAME_LEN; snameLen++) {
        for (int i=0; i < Pkt4::MAX_SNAME_LEN; i++) {
            sname[i] = 0;
        }
        for (int i=0; i < snameLen; i++) {
            sname[i] = i;
        }

        // type and transaction doesn't matter in this test
        pkt = new Pkt4(DHCPOFFER, 1234);
        pkt->setSname(sname, snameLen);

        EXPECT_EQ(0, memcmp(sname, &pkt->getSname()[0], Pkt4::MAX_SNAME_LEN));

        EXPECT_NO_THROW(
            pkt->pack();
        );

        // SNAME starts at offset 44 in DHCP packet
        const uint8_t* ptr =
            static_cast<const uint8_t*>(pkt->getBuffer().getData())+44;
        EXPECT_EQ(0, memcmp(ptr, sname, Pkt4::MAX_SNAME_LEN));

        delete pkt;
    }
}

TEST(Pkt4Test, file) {

    uint8_t file[Pkt4::MAX_FILE_LEN];

    Pkt4* pkt = 0;
    // Let's test each file length, from 0 till 128.
    for (int fileLen=0; fileLen < Pkt4::MAX_FILE_LEN; fileLen++) {
        for (int i=0; i < Pkt4::MAX_FILE_LEN; i++) {
            file[i] = 0;
        }
        for (int i=0; i < fileLen; i++) {
            file[i] = i;
        }

        // Type and transaction doesn't matter in this test.
        pkt = new Pkt4(DHCPOFFER, 1234);
        pkt->setFile(file, fileLen);

        EXPECT_EQ(0, memcmp(file, &pkt->getFile()[0], Pkt4::MAX_FILE_LEN));

        //
        EXPECT_NO_THROW(
            pkt->pack();
        );

        // FILE starts at offset 108 in DHCP packet.
        const uint8_t* ptr =
            static_cast<const uint8_t*>(pkt->getBuffer().getData())+108;
        EXPECT_EQ(0, memcmp(ptr, file, Pkt4::MAX_FILE_LEN));

        delete pkt;
    }

}

} // end of anonymous namespace
