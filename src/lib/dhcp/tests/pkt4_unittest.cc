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

#include <asiolink/io_address.h>
#include <dhcp/dhcp4.h>
#include <dhcp/pkt4.h>
#include <exceptions/exceptions.h>
#include <util/buffer.h>

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
// don't import the entire boost namespace.  It will unexpectedly hide uint8_t
// for some systems.
using boost::scoped_ptr;

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
const uint8_t dummyOp = BOOTREQUEST;
const uint8_t dummyHtype = 6;
const uint8_t dummyHlen = 6;
const uint8_t dummyHops = 13;
const uint32_t dummyTransid = 0x12345678;
const uint16_t dummySecs = 42;
const uint16_t dummyFlags = BOOTP_BROADCAST;

const IOAddress dummyCiaddr("192.0.2.1");
const IOAddress dummyYiaddr("1.2.3.4");
const IOAddress dummySiaddr("192.0.2.255");
const IOAddress dummyGiaddr("255.255.255.255");

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
    copy(dummyChaddr, dummyChaddr + Pkt4::MAX_CHADDR_LEN, back_inserter(buf));
    copy(dummySname, dummySname + Pkt4::MAX_SNAME_LEN, back_inserter(buf));
    copy(dummyFile, dummyFile + Pkt4::MAX_FILE_LEN, back_inserter(buf));

    // Should now have all the header, so check.  The "static_cast" is used
    // to get round an odd bug whereby the linker appears not to find the
    // definition of DHCPV4_PKT_HDR_LEN if it appears within an EXPECT_EQ().
    EXPECT_EQ(static_cast<size_t>(Pkt4::DHCPV4_PKT_HDR_LEN), buf.size());

    return (buf);
}

TEST(Pkt4Test, fixedFields) {

    boost::shared_ptr<Pkt4> pkt = generateTestPacket1();

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
    boost::shared_ptr<Pkt4> pkt = generateTestPacket1();
    vector<uint8_t> expectedFormat = generateTestPacket2();

    EXPECT_NO_THROW(
        pkt->pack();
    );

    ASSERT_EQ(static_cast<size_t>(Pkt4::DHCPV4_PKT_HDR_LEN), pkt->len());

    // redundant but MUCH easier for debug in gdb
    const uint8_t* exp = &expectedFormat[0];
    const uint8_t* got = static_cast<const uint8_t*>(pkt->getBuffer().getData());

    EXPECT_EQ(0, memcmp(exp, got, Pkt4::DHCPV4_PKT_HDR_LEN));
}

/// TODO Uncomment when ticket #1226 is implemented
TEST(Pkt4Test, fixedFieldsUnpack) {
    vector<uint8_t> expectedFormat = generateTestPacket2();

    expectedFormat.push_back(0x63); // magic cookie
    expectedFormat.push_back(0x82);
    expectedFormat.push_back(0x53);
    expectedFormat.push_back(0x63);

    expectedFormat.push_back(0x35); // message-type
    expectedFormat.push_back(0x1);
    expectedFormat.push_back(0x1);

    boost::shared_ptr<Pkt4> pkt(new Pkt4(&expectedFormat[0],
                                         expectedFormat.size()));;


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

    // We resize vector to specified length. It is more natural for fixed-length
    // field, than clear it (shrink size to 0) and push_back each element
    // (growing length back to MAX_CHADDR_LEN).
    mac.resize(Pkt4::MAX_CHADDR_LEN);

    Pkt4* pkt = 0;
    // let's test each hlen, from 0 till 16
    for (int macLen = 0; macLen < Pkt4::MAX_CHADDR_LEN; macLen++) {
        for (int i = 0; i < Pkt4::MAX_CHADDR_LEN; i++) {
            mac[i] = 0;
            expectedChaddr[i] = 0;
        }
        for (int i = 0; i < macLen; i++) {
            mac[i] = 128 + i;
            expectedChaddr[i] = 128 + i;
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
    for (int i = 0; i < sizeof(types) / sizeof(msgType); i++) {

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
        for (int i = 0; i < Pkt4::MAX_SNAME_LEN; i++) {
            sname[i] = 0;
        }
        for (int i = 0; i < snameLen; i++) {
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
    for (int fileLen = 0; fileLen < Pkt4::MAX_FILE_LEN; fileLen++) {
        for (int i = 0; i < Pkt4::MAX_FILE_LEN; i++) {
            file[i] = 0;
        }
        for (int i = 0; i < fileLen; i++) {
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

/// V4 Options being used for pack/unpack testing.
/// For test simplicity, all selected options have
/// variable length data so as there are no restrictions
/// on a length of their data.
static uint8_t v4Opts[] = {
    12,  3, 0,   1,  2, // Hostname
    14,  3, 10, 11, 12, // Merit Dump File
    53, 1, 1, // Message Type (required to not throw exception during unpack)
    60,  3, 20, 21, 22, // Class Id
    128, 3, 30, 31, 32, // Vendor specific
    254, 3, 40, 41, 42, // Reserved
};

TEST(Pkt4Test, options) {
    Pkt4* pkt = new Pkt4(DHCPOFFER, 0);

    vector<uint8_t> payload[5];
    for (int i = 0; i < 5; i++) {
        payload[i].push_back(i*10);
        payload[i].push_back(i*10+1);
        payload[i].push_back(i*10+2);
    }

    boost::shared_ptr<Option> opt1(new Option(Option::V4, 12, payload[0]));
    boost::shared_ptr<Option> opt3(new Option(Option::V4, 14, payload[1]));
    boost::shared_ptr<Option> optMsgType(new Option(Option::V4, DHO_DHCP_MESSAGE_TYPE));
    boost::shared_ptr<Option> opt2(new Option(Option::V4, 60, payload[2]));
    boost::shared_ptr<Option> opt5(new Option(Option::V4,128, payload[3]));
    boost::shared_ptr<Option> opt4(new Option(Option::V4,254, payload[4]));
    optMsgType->setUint8(static_cast<uint8_t>(DHCPDISCOVER));

    pkt->addOption(opt1);
    pkt->addOption(opt2);
    pkt->addOption(opt3);
    pkt->addOption(opt4);
    pkt->addOption(opt5);
    pkt->addOption(optMsgType);

    EXPECT_TRUE(pkt->getOption(12));
    EXPECT_TRUE(pkt->getOption(60));
    EXPECT_TRUE(pkt->getOption(14));
    EXPECT_TRUE(pkt->getOption(128));
    EXPECT_TRUE(pkt->getOption(254));
    EXPECT_FALSE(pkt->getOption(127)); //  no such option

    // options are unique in DHCPv4. It should not be possible
    // to add more than one option of the same type.
    EXPECT_THROW(
        pkt->addOption(opt1),
        BadValue
    );

    EXPECT_NO_THROW(
        pkt->pack();
    );

    const OutputBuffer& buf = pkt->getBuffer();
    // check that all options are stored, they should take sizeof(v4Opts),
    // DHCP magic cookie (4 bytes), and OPTION_END added (just one byte)
    ASSERT_EQ(static_cast<size_t>(Pkt4::DHCPV4_PKT_HDR_LEN) + sizeof(DHCP_OPTIONS_COOKIE)
              + sizeof(v4Opts) + 1, buf.getLength());

    // that that this extra data actually contain our options
    const uint8_t* ptr = static_cast<const uint8_t*>(buf.getData());
    ptr += Pkt4::DHCPV4_PKT_HDR_LEN + sizeof(DHCP_OPTIONS_COOKIE); // rewind to end of fixed part
    EXPECT_EQ(0, memcmp(ptr, v4Opts, sizeof(v4Opts)));
    EXPECT_EQ(DHO_END, static_cast<uint8_t>(*(ptr + sizeof(v4Opts))));

    EXPECT_NO_THROW(
        delete pkt;
    );
}

TEST(Pkt4Test, unpackOptions) {

    vector<uint8_t> expectedFormat = generateTestPacket2();

    expectedFormat.push_back(0x63);
    expectedFormat.push_back(0x82);
    expectedFormat.push_back(0x53);
    expectedFormat.push_back(0x63);

    for (int i = 0; i < sizeof(v4Opts); i++) {
        expectedFormat.push_back(v4Opts[i]);
    }

    // now expectedFormat contains fixed format and 5 options

    boost::shared_ptr<Pkt4> pkt(new Pkt4(&expectedFormat[0],
                                expectedFormat.size()));

    try {
        pkt->unpack();
    } catch (const Exception& ex) {
        std::cout << ex.what() << std::endl;
    }
    EXPECT_NO_THROW(
        pkt->unpack()
    );

    EXPECT_TRUE(pkt->getOption(12));
    EXPECT_TRUE(pkt->getOption(60));
    EXPECT_TRUE(pkt->getOption(14));
    EXPECT_TRUE(pkt->getOption(128));
    EXPECT_TRUE(pkt->getOption(254));

    boost::shared_ptr<Option> x = pkt->getOption(12);
    ASSERT_TRUE(x); // option 1 should exist
    EXPECT_EQ(12, x->getType());  // this should be option 12
    ASSERT_EQ(3, x->getData().size()); // it should be of length 3
    EXPECT_EQ(5, x->len()); // total option length 5
    EXPECT_EQ(0, memcmp(&x->getData()[0], v4Opts+2, 3)); // data len=3

    x = pkt->getOption(14);
    ASSERT_TRUE(x); // option 13 should exist
    EXPECT_EQ(14, x->getType());  // this should be option 13
    ASSERT_EQ(3, x->getData().size()); // it should be of length 3
    EXPECT_EQ(5, x->len()); // total option length 5
    EXPECT_EQ(0, memcmp(&x->getData()[0], v4Opts+7, 3)); // data len=3

    x = pkt->getOption(60);
    ASSERT_TRUE(x); // option 60 should exist
    EXPECT_EQ(60, x->getType());  // this should be option 60
    ASSERT_EQ(3, x->getData().size()); // it should be of length 3
    EXPECT_EQ(5, x->len()); // total option length 5
    EXPECT_EQ(0, memcmp(&x->getData()[0], v4Opts+15, 3)); // data len=3

    x = pkt->getOption(128);
    ASSERT_TRUE(x); // option 3 should exist
    EXPECT_EQ(128, x->getType());  // this should be option 254
    ASSERT_EQ(3, x->getData().size()); // it should be of length 3
    EXPECT_EQ(5, x->len()); // total option length 5
    EXPECT_EQ(0, memcmp(&x->getData()[0], v4Opts+20, 3)); // data len=3

    x = pkt->getOption(254);
    ASSERT_TRUE(x); // option 3 should exist
    EXPECT_EQ(254, x->getType());  // this should be option 254
    ASSERT_EQ(3, x->getData().size()); // it should be of length 3
    EXPECT_EQ(5, x->len()); // total option length 5
    EXPECT_EQ(0, memcmp(&x->getData()[0], v4Opts+25, 3)); // data len=3
}

// This test verifies methods that are used for manipulating meta fields
// i.e. fields that are not part of DHCPv4 (e.g. interface name).
TEST(Pkt4Test, metaFields) {

    Pkt4* pkt = new Pkt4(DHCPOFFER, 1234);
    pkt->setIface("loooopback");
    pkt->setIndex(42);
    pkt->setRemoteAddr(IOAddress("1.2.3.4"));
    pkt->setLocalAddr(IOAddress("4.3.2.1"));

    EXPECT_EQ("loooopback", pkt->getIface());
    EXPECT_EQ(42, pkt->getIndex());
    EXPECT_EQ("1.2.3.4", pkt->getRemoteAddr().toText());
    EXPECT_EQ("4.3.2.1", pkt->getLocalAddr().toText());

    delete pkt;
}

TEST(Pkt4Test, Timestamp) {
    scoped_ptr<Pkt4> pkt(new Pkt4(DHCPOFFER, 1234));

    // Just after construction timestamp is invalid
    ASSERT_TRUE(pkt->getTimestamp().is_not_a_date_time());

    // Update packet time.
    pkt->updateTimestamp();

    // Get updated packet time.
    boost::posix_time::ptime ts_packet = pkt->getTimestamp();

    // After timestamp is updated it should be date-time.
    ASSERT_FALSE(ts_packet.is_not_a_date_time());

    // Check current time.
    boost::posix_time::ptime ts_now =
        boost::posix_time::microsec_clock::universal_time();

    // Calculate period between packet time and now.
    boost::posix_time::time_period ts_period(ts_packet, ts_now);

    // Duration should be positive or zero.
    EXPECT_TRUE(ts_period.length().total_microseconds() >= 0);
}



} // end of anonymous namespace
