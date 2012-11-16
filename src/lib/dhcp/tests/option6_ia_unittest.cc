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
#include <dhcp/option6_ia.h>
#include <dhcp/option6_iaaddr.h>
#include <util/buffer.h>

#include <gtest/gtest.h>

#include <iostream>
#include <sstream>

#include <arpa/inet.h>

using namespace std;
using namespace isc;
using namespace isc::dhcp;
using namespace isc::asiolink;
using namespace isc::util;

namespace {
class Option6IATest : public ::testing::Test {
public:
    Option6IATest(): buf_(255), outBuf_(255) {
        for (int i = 0; i < 255; i++) {
            buf_[i] = 255 - i;
        }
    }
    OptionBuffer buf_;
    OutputBuffer outBuf_;
};

TEST_F(Option6IATest, basic) {
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

    // create an option
    // unpack() is called from constructor
    Option6IA* opt = new Option6IA(D6O_IA_NA,
                                   buf_.begin(),
                                   buf_.begin() + 12);

    EXPECT_EQ(Option::V6, opt->getUniverse());
    EXPECT_EQ(D6O_IA_NA, opt->getType());
    EXPECT_EQ(0xa1a2a3a4, opt->getIAID());
    EXPECT_EQ(0x81020304, opt->getT1());
    EXPECT_EQ(0x84030201, opt->getT2());

    // pack this option again in the same buffer, but in
    // different place

    // test for pack()
    opt->pack(outBuf_);

    // 12 bytes header + 4 bytes content
    EXPECT_EQ(12, opt->len() - opt->getHeaderLen());
    EXPECT_EQ(D6O_IA_NA, opt->getType());

    EXPECT_EQ(16, outBuf_.getLength()); // lenght(IA_NA) = 16

    // check if pack worked properly:
    InputBuffer out(outBuf_.getData(), outBuf_.getLength());

    // if option type is correct
    EXPECT_EQ(D6O_IA_NA, out.readUint16());

    // if option length is correct
    EXPECT_EQ(12, out.readUint16());

    // if iaid is correct
    EXPECT_EQ(0xa1a2a3a4, out.readUint32() );

   // if T1 is correct
    EXPECT_EQ(0x81020304, out.readUint32() );

    // if T1 is correct
    EXPECT_EQ(0x84030201, out.readUint32() );

    EXPECT_NO_THROW(
        delete opt;
    );
}

TEST_F(Option6IATest, simple) {
    Option6IA * ia = new Option6IA(D6O_IA_NA, 1234);
    ia->setT1(2345);
    ia->setT2(3456);

    EXPECT_EQ(Option::V6, ia->getUniverse());
    EXPECT_EQ(D6O_IA_NA, ia->getType());
    EXPECT_EQ(1234, ia->getIAID());
    EXPECT_EQ(2345, ia->getT1());
    EXPECT_EQ(3456, ia->getT2());

    EXPECT_NO_THROW(
        delete ia;
    );
}


// test if option can build suboptions
TEST_F(Option6IATest, suboptions_pack) {
    buf_[0] = 0xff;
    buf_[1] = 0xfe;
    buf_[2] = 0xfc;

    Option6IA * ia = new Option6IA(D6O_IA_NA, 0x13579ace);
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

    EXPECT_NO_THROW(
        delete ia;
    );
}


// test if option can parse suboptions
TEST_F(Option6IATest, suboptions_unpack) {
    // sizeof (expected) = 48 bytes
    uint8_t expected[] = {
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

    Option6IA* ia = 0;
    EXPECT_NO_THROW({
            ia = new Option6IA(D6O_IA_NA, buf_.begin() + 4, buf_.begin() + sizeof(expected));
    });
    ASSERT_TRUE(ia);

    EXPECT_EQ(D6O_IA_NA, ia->getType());
    EXPECT_EQ(0x13579ace, ia->getIAID());
    EXPECT_EQ(0x2345, ia->getT1());
    EXPECT_EQ(0x3456, ia->getT2());

    OptionPtr subopt = ia->getOption(D6O_IAADDR);
    ASSERT_NE(OptionPtr(), subopt); // non-NULL

    // checks for address option
    Option6IAAddr * addr = dynamic_cast<Option6IAAddr*>(subopt.get());
    ASSERT_TRUE(NULL != addr);

    EXPECT_EQ(D6O_IAADDR, addr->getType());
    EXPECT_EQ(28, addr->len());
    EXPECT_EQ(0x5000, addr->getPreferred());
    EXPECT_EQ(0x7000, addr->getValid());
    EXPECT_EQ("2001:db8:1234:5678::abcd", addr->getAddress().toText());

    // checks for dummy option
    subopt = ia->getOption(0xcafe);
    ASSERT_TRUE(subopt); // should be non-NULL

    EXPECT_EQ(0xcafe, subopt->getType());
    EXPECT_EQ(4, subopt->len());
    // there should be no data at all
    EXPECT_EQ(0, subopt->getData().size());

    subopt = ia->getOption(1); // get option 1
    ASSERT_FALSE(subopt); // should be NULL

    EXPECT_NO_THROW(
        delete ia;
    );
}

}
