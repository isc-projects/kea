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

#include "dhcp/dhcp6.h"
#include "dhcp/option.h"
#include "dhcp/option6_ia.h"

using namespace std;
using namespace isc;
using namespace isc::dhcp;

namespace {
class Option6IATest : public ::testing::Test {
public:
    Option6IATest() {
    }
};

TEST_F(Option6IATest, basic) {

    boost::shared_array<char> simple_buf(new char[128]);
    for (int i=0; i<128; i++)
        simple_buf[i] = 0;
    simple_buf[0]=0xa1; // iaid
    simple_buf[1]=0xa2;
    simple_buf[2]=0xa3;
    simple_buf[3]=0xa4;

    simple_buf[4]=0x81; // T1
    simple_buf[5]=0x02;
    simple_buf[6]=0x03;
    simple_buf[7]=0x04;

    simple_buf[8]=0x84; // T2
    simple_buf[9]=0x03;
    simple_buf[10]=0x02;
    simple_buf[11]=0x01;

    // create an option (unpack content)
    Option6IA* opt = new Option6IA(Option::V6, 
                                   D6O_IA_NA,
                                   simple_buf,
                                   128,
                                   0, 
                                   12);

    EXPECT_EQ(D6O_IA_NA, opt->getType());
    EXPECT_EQ(0xa1a2a3a4, opt->getIAID());
    EXPECT_EQ(0x81020304, opt->getT1());
    EXPECT_EQ(0x84030201, opt->getT2());
    
    // pack this option again in the same buffer, but in
    // different place
    int offset = opt->pack(simple_buf, 128, 60);

    // 4 bytes header + 4 bytes content
    EXPECT_EQ(12, opt->len() - 4);
    EXPECT_EQ(D6O_IA_NA, opt->getType());

    EXPECT_EQ(offset, 76); // 60 + lenght(IA_NA) = 76

    // check if pack worked properly:
    // if option type is correct
    EXPECT_EQ(D6O_IA_NA, simple_buf[60]*256 + simple_buf[61]);

    // if option length is correct
    EXPECT_EQ(12, simple_buf[62]*256 + simple_buf[63]);
    
    // if iaid is correct
    unsigned int iaid = htonl(*(unsigned int*)&simple_buf[64]);
    EXPECT_EQ(0xa1a2a3a4, iaid );
 
   // if T1 is correct
    EXPECT_EQ(0x81020304, (simple_buf[68] << 24) +
                          (simple_buf[69] << 16) +
                          (simple_buf[70] << 8) + 
                          (simple_buf[71]) );

    // if T1 is correct
    EXPECT_EQ(0x84030201, (simple_buf[72] << 24) +
                          (simple_buf[73] << 16) +
                          (simple_buf[74] << 8) + 
                          (simple_buf[75]) );

    delete opt;
}

}
