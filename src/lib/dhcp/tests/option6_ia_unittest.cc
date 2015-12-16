// Copyright (C) 2011-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <dhcp/dhcp6.h>
#include <dhcp/option.h>
#include <dhcp/option6_ia.h>
#include <dhcp/option6_iaaddr.h>
#include <dhcp/option6_iaprefix.h>
#include <util/buffer.h>

#include <boost/scoped_ptr.hpp>
#include <gtest/gtest.h>

#include <iostream>
#include <sstream>

#include <arpa/inet.h>

using namespace std;
using namespace isc;
using namespace isc::dhcp;
using namespace isc::asiolink;
using namespace isc::util;
using boost::scoped_ptr;

namespace {
class Option6IATest : public ::testing::Test {
public:
    Option6IATest(): buf_(255), outBuf_(255) {
        for (unsigned i = 0; i < 255; i++) {
            buf_[i] = 255 - i;
        }
    }

    /// @brief performs basic checks on IA option
    ///
    /// Check that an option can be built based on incoming buffer and that
    /// the option contains expected values.
    /// @param type specifies option type (IA_NA or IA_PD)
    void checkIA(uint16_t type) {
        buf_[0] = 0xa1; // iaid
        buf_[1] = 0xa2;
        buf_[2] = 0xa3;
        buf_[3] = 0xa4;

        buf_[4] = 0x81; // T1
        buf_[5] = 0x02;
        buf_[6] = 0x03;
        buf_[7] = 0x04;

        buf_[8] = 0x84; // T2
        buf_[9] = 0x03;
        buf_[10] = 0x02;
        buf_[11] = 0x01;

        // Create an option
        // unpack() is called from constructor
        scoped_ptr<Option6IA> opt;
        ASSERT_NO_THROW(opt.reset(new Option6IA(type, buf_.begin(),
                                                buf_.begin() + 12)));

        EXPECT_EQ(Option::V6, opt->getUniverse());
        EXPECT_EQ(type, opt->getType());
        EXPECT_EQ(0xa1a2a3a4, opt->getIAID());
        EXPECT_EQ(0x81020304, opt->getT1());
        EXPECT_EQ(0x84030201, opt->getT2());

        // Pack this option again in the same buffer, but in
        // different place

        // Test for pack()
        ASSERT_NO_THROW(opt->pack(outBuf_));

        // 12 bytes header + 4 bytes content
        EXPECT_EQ(12, opt->len() - opt->getHeaderLen());
        EXPECT_EQ(type, opt->getType());

        EXPECT_EQ(16, outBuf_.getLength()); // lenght(IA_NA) = 16

        // Check if pack worked properly:
        InputBuffer out(outBuf_.getData(), outBuf_.getLength());

        // - if option type is correct
        EXPECT_EQ(type, out.readUint16());

        // - if option length is correct
        EXPECT_EQ(12, out.readUint16());

        // - if iaid is correct
        EXPECT_EQ(0xa1a2a3a4, out.readUint32() );

        // - if T1 is correct
        EXPECT_EQ(0x81020304, out.readUint32() );

        // - if T1 is correct
        EXPECT_EQ(0x84030201, out.readUint32() );

        EXPECT_NO_THROW(opt.reset());
    }

    OptionBuffer buf_;
    OutputBuffer outBuf_;
};

TEST_F(Option6IATest, basic) {
    checkIA(D6O_IA_NA);
}

TEST_F(Option6IATest, pdBasic) {
    checkIA(D6O_IA_PD);
}

// Check that this class cannot be used for IA_TA (IA_TA has no T1, T2 fields
// and people tend to think that if it's good for IA_NA and IA_PD, it can
// be used for IA_TA as well and that is not true)
TEST_F(Option6IATest, taForbidden) {
    EXPECT_THROW(Option6IA(D6O_IA_TA, buf_.begin(), buf_.begin() + 50),
                 BadValue);

    EXPECT_THROW(Option6IA(D6O_IA_TA, 123), BadValue);
}

// Check that getters/setters are working as expected.
TEST_F(Option6IATest, simple) {
    scoped_ptr<Option6IA> ia(new Option6IA(D6O_IA_NA, 1234));

    // Check that the values are really different than what we are about
    // to set them to.
    EXPECT_NE(2345, ia->getT1());
    EXPECT_NE(3456, ia->getT2());

    ia->setT1(2345);
    ia->setT2(3456);

    EXPECT_EQ(Option::V6, ia->getUniverse());
    EXPECT_EQ(D6O_IA_NA, ia->getType());
    EXPECT_EQ(1234, ia->getIAID());
    EXPECT_EQ(2345, ia->getT1());
    EXPECT_EQ(3456, ia->getT2());

    ia->setIAID(890);
    EXPECT_EQ(890, ia->getIAID());

    EXPECT_NO_THROW(ia.reset());
}

// test if the option can build suboptions
TEST_F(Option6IATest, suboptionsPack) {

    scoped_ptr<Option6IA> ia(new Option6IA(D6O_IA_NA, 0x13579ace));
    ia->setT1(0x2345);
    ia->setT2(0x3456);

    OptionPtr sub1(new Option(Option::V6, 0xcafe));

    boost::shared_ptr<Option6IAAddr> addr1(
        new Option6IAAddr(D6O_IAADDR, IOAddress("2001:db8:1234:5678::abcd"), 0x5000, 0x7000));

    ia->addOption(sub1);
    ia->addOption(addr1);

    ASSERT_EQ(28, addr1->len());
    ASSERT_EQ(4, sub1->len());
    ASSERT_EQ(48, ia->len());

    // This contains expected on-wire format
    uint8_t expected[] = {
        D6O_IA_NA/256, D6O_IA_NA%256, // type
        0, 44, // length
        0x13, 0x57, 0x9a, 0xce, // iaid
        0, 0, 0x23, 0x45,  // T1
        0, 0, 0x34, 0x56,  // T2

        // iaaddr suboption
        D6O_IAADDR/256, D6O_IAADDR%256, // type
        0, 24, // len
        0x20, 0x01, 0xd, 0xb8, 0x12,0x34, 0x56, 0x78,
        0, 0, 0, 0, 0, 0, 0xab, 0xcd, // IP address
        0, 0, 0x50, 0, // preferred-lifetime
        0, 0, 0x70, 0, // valid-lifetime

        // suboption
        0xca, 0xfe, // type
        0, 0 // len
    };

    ia->pack(outBuf_);

    ASSERT_EQ(48, outBuf_.getLength());
    EXPECT_EQ(0, memcmp(outBuf_.getData(), expected, 48));
    EXPECT_NO_THROW(ia.reset());
}

// test if IA_PD option can build IAPREFIX suboptions
TEST_F(Option6IATest, pdSuboptionsPack) {

    // Let's build IA_PD
    scoped_ptr<Option6IA> ia;
    ASSERT_NO_THROW(ia.reset(new Option6IA(D6O_IA_PD, 0x13579ace)));
    ia->setT1(0x2345);
    ia->setT2(0x3456);

    // Put some dummy option in it
    OptionPtr sub1(new Option(Option::V6, 0xcafe));

    // Put a valid IAPREFIX option in it
    boost::shared_ptr<Option6IAPrefix> addr1(
        new Option6IAPrefix(D6O_IAPREFIX, IOAddress("2001:db8:1234:5678::abcd"),
                            91, 0x5000, 0x7000));

    ia->addOption(sub1);
    ia->addOption(addr1);

    ASSERT_EQ(29, addr1->len());
    ASSERT_EQ(4, sub1->len());
    ASSERT_EQ(49, ia->len());

    uint8_t expected[] = {
        D6O_IA_PD/256, D6O_IA_PD%256, // type
        0, 45, // length
        0x13, 0x57, 0x9a, 0xce, // iaid
        0, 0, 0x23, 0x45,  // T1
        0, 0, 0x34, 0x56,  // T2

        // iaprefix suboption
        D6O_IAPREFIX/256, D6O_IAPREFIX%256, // type
        0, 25, // len
        0, 0, 0x50, 0, // preferred-lifetime
        0, 0, 0x70, 0, // valid-lifetime
        91, // prefix length
        0x20, 0x01, 0xd, 0xb8, 0x12,0x34, 0x56, 0x78,
        0, 0, 0, 0, 0, 0, 0xab, 0xcd, // IP address

        // suboption
        0xca, 0xfe, // type
        0, 0 // len
    };

    ia->pack(outBuf_);
    ASSERT_EQ(49, outBuf_.getLength());

    EXPECT_EQ(0, memcmp(outBuf_.getData(), expected, 49));

    EXPECT_NO_THROW(ia.reset());
}

// test if option can parse suboptions
TEST_F(Option6IATest, suboptionsUnpack) {
    // sizeof (expected) = 48 bytes
    const uint8_t expected[] = {
        D6O_IA_NA / 256, D6O_IA_NA % 256, // type
        0, 28, // length
        0x13, 0x57, 0x9a, 0xce, // iaid
        0, 0, 0x23, 0x45,  // T1
        0, 0, 0x34, 0x56,  // T2

        // iaaddr suboption
        D6O_IAADDR / 256, D6O_IAADDR % 256, // type
        0, 24, // len
        0x20, 0x01, 0xd, 0xb8, 0x12,0x34, 0x56, 0x78,
        0, 0, 0, 0, 0, 0, 0xab, 0xcd, // IP address
        0, 0, 0x50, 0, // preferred-lifetime
        0, 0, 0x70, 0, // valid-lifetime

        // suboption
        0xca, 0xfe, // type
        0, 0 // len
    };
    ASSERT_EQ(48, sizeof(expected));

    memcpy(&buf_[0], expected, sizeof(expected));

    scoped_ptr<Option6IA> ia;
    EXPECT_NO_THROW(
        ia.reset(new Option6IA(D6O_IA_NA, buf_.begin() + 4,
                               buf_.begin() + sizeof(expected)));
    );
    ASSERT_TRUE(ia);

    EXPECT_EQ(D6O_IA_NA, ia->getType());
    EXPECT_EQ(0x13579ace, ia->getIAID());
    EXPECT_EQ(0x2345, ia->getT1());
    EXPECT_EQ(0x3456, ia->getT2());

    OptionPtr subopt = ia->getOption(D6O_IAADDR);
    ASSERT_NE(OptionPtr(), subopt); // non-NULL

    // Checks for address option
    Option6IAAddr * addr = dynamic_cast<Option6IAAddr*>(subopt.get());
    ASSERT_TRUE(NULL != addr);

    EXPECT_EQ(D6O_IAADDR, addr->getType());
    EXPECT_EQ(28, addr->len());
    EXPECT_EQ(0x5000, addr->getPreferred());
    EXPECT_EQ(0x7000, addr->getValid());
    EXPECT_EQ("2001:db8:1234:5678::abcd", addr->getAddress().toText());

    // Checks for dummy option
    subopt = ia->getOption(0xcafe);
    ASSERT_TRUE(subopt); // should be non-NULL

    EXPECT_EQ(0xcafe, subopt->getType());
    EXPECT_EQ(4, subopt->len());
    // There should be no data at all
    EXPECT_EQ(0, subopt->getData().size());

    subopt = ia->getOption(1); // get option 1
    ASSERT_FALSE(subopt); // should be NULL

    EXPECT_NO_THROW(ia.reset());
}

// This test checks that the IA_NA option is correctly converted to the
// textual format.
TEST_F(Option6IATest, toTextNA) {
    Option6IA ia(D6O_IA_NA, 1234);
    ia.setT1(200);
    ia.setT2(300);

    ia.addOption(OptionPtr(new Option6IAAddr(D6O_IAADDR, IOAddress("2001:db8:1::1"),
                                             500, 600)));
    ia.addOption(OptionPtr(new Option6IAAddr(D6O_IAADDR, IOAddress("2001:db8:1::2"),
                                             450, 550)));

    EXPECT_EQ("type=00003(IA_NA), len=00068: iaid=1234, t1=200, t2=300,\n"
              "options:\n"
              "  type=00005(IAADDR), len=00024: address=2001:db8:1::1, "
              "preferred-lft=500, valid-lft=600\n"
              "  type=00005(IAADDR), len=00024: address=2001:db8:1::2, "
              "preferred-lft=450, valid-lft=550", ia.toText());
}

// This test checks that the IA_PD option is correctly converted to the
// textual format.
TEST_F(Option6IATest, toTextPD) {
    Option6IA ia(D6O_IA_PD, 2345);
    ia.setT1(200);
    ia.setT2(300);

    ia.addOption(OptionPtr(new Option6IAPrefix(D6O_IAPREFIX, IOAddress("2001:db8:1::"),
                                               72, 500, 600)));
    ia.addOption(OptionPtr(new Option6IAPrefix(D6O_IAPREFIX, IOAddress("2001:db8:1::"),
                                               64, 450, 550)));

    EXPECT_EQ("type=00025(IA_PD), len=00070: iaid=2345, t1=200, t2=300,\n"
              "options:\n"
              "  type=00026(IAPREFIX), len=00025: prefix=2001:db8:1::/72, "
              "preferred-lft=500, valid-lft=600\n"
              "  type=00026(IAPREFIX), len=00025: prefix=2001:db8:1::/64, "
              "preferred-lft=450, valid-lft=550",
              ia.toText());
}

}
