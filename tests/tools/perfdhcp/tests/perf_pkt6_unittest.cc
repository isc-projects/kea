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
#include <iostream>
#include <sstream>
#include <arpa/inet.h>
#include <gtest/gtest.h>

#include <asiolink/io_address.h>
#include <dhcp/option.h>
#include <dhcp/dhcp6.h>

#include "../perf_pkt6.h"

using namespace std;
using namespace isc;
using namespace isc::dhcp;
using namespace isc::perfdhcp;

typedef PerfPkt6::PositionedOptionPtr PositionedOptionPtr;
typedef PerfPkt6::PositionedOption PositionedOption;

namespace {
class PerfPkt6Test : public ::testing::Test {
public:
    PerfPkt6Test() {
    }

/// @brief returns captured actual SOLICIT packet
///
/// Captured SOLICIT packet with transid=0x3d79fb and options: client-id,
/// in_na, dns-server, elapsed-time, option-request
/// This code was autogenerated (see src/bin/dhcp6/tests/iface_mgr_unittest.c),
/// but we spent some time to make is less ugly than it used to be.
///
/// @return pointer to Pkt6 that represents received SOLICIT
PerfPkt6* capture1() {
    uint8_t data[98];
    data[0]  = 1;
    data[1]  = 1;       data[2]  = 2;     data[3] = 3;      data[4]  = 0;
    data[5]  = 1;       data[6]  = 0;     data[7] = 14;     data[8]  = 0;
    data[9]  = 1;       data[10] = 0;     data[11] = 1;     data[12] = 21;
    data[13] = 158;     data[14] = 60;    data[15] = 22;    data[16] = 0;
    data[17] = 30;      data[18] = 140;   data[19] = 155;   data[20] = 115;
    data[21] = 73;      data[22] = 0;     data[23] = 3;     data[24] = 0;
    data[25] = 40;      data[26] = 0;     data[27] = 0;     data[28] = 0;
    data[29] = 1;       data[30] = 255;   data[31] = 255;   data[32] = 255;
    data[33] = 255;     data[34] = 255;   data[35] = 255;   data[36] = 255;
    data[37] = 255;     data[38] = 0;     data[39] = 5;     data[40] = 0;
    data[41] = 24;      data[42] = 32;    data[43] = 1;     data[44] = 13;
    data[45] = 184;     data[46] = 0;     data[47] = 1;     data[48] = 0;
    data[49] = 0;       data[50] = 0;     data[51] = 0;     data[52] = 0;
    data[53] = 0;       data[54] = 0;     data[55] = 0;     data[56] = 18;
    data[57] = 52;      data[58] = 255;   data[59] = 255;   data[60] = 255;
    data[61] = 255;     data[62] = 255;   data[63] = 255;   data[64] = 255;
    data[65] = 255;     data[66] = 0;     data[67] = 23;    data[68] = 0;
    data[69] = 16;      data[70] = 32;    data[71] = 1;     data[72] = 13;
    data[73] = 184;     data[74] = 0;     data[75] = 1;     data[76] = 0;
    data[77] = 0;       data[78] = 0;     data[79] = 0;     data[80] = 0;
    data[81] = 0;       data[82] = 0;     data[83] = 0;     data[84] = 221;
    data[85] = 221;     data[86] = 0;     data[87] = 8;     data[88] = 0;
    data[89] = 2;       data[90] = 0;     data[91] = 100;   data[92] = 0;
    data[93] = 6;       data[94] = 0;     data[95] = 2;     data[96] = 0;
    data[97] = 23;

    PerfPkt6* pkt = new PerfPkt6(data, sizeof(data), 0);

    /*    pkt->setRemotePort(546);
    pkt->setRemoteAddr(IOAddress("fe80::21e:8cff:fe9b:7349"));
    pkt->setLocalPort(0);
    pkt->setLocalAddr(IOAddress("ff02::1:2"));
    pkt->setIndex(2);
    pkt->setIface("eth0");*/

    return (pkt);
}

};

TEST_F(PerfPkt6Test, constructor) {
    uint8_t data[] = { 0, 1, 2, 3, 4, 5 };
    timespec zero_t_spec;
    memset(&zero_t_spec, 0, sizeof(zero_t_spec));

    boost::scoped_ptr<PerfPkt6> pkt1(new PerfPkt6(data, sizeof(data), 1));
    timespec packet_t_spec = pkt1->getTimestamp();

    EXPECT_EQ(6, pkt1->getData().size());
    EXPECT_EQ(0, memcmp( &pkt1->getData()[0], data, sizeof(data)));
    EXPECT_EQ(1, pkt1->getTransIdOffset());
    EXPECT_EQ(0, memcmp(&packet_t_spec, &zero_t_spec, sizeof(zero_t_spec)));
}

TEST_F(PerfPkt6Test, UnpackRawSolicit) {
    // Create packetPositionedOptionPtr
    boost::scoped_ptr<PerfPkt6> pkt1(capture1());
    // Create some input buffer to initialize options.
    uint8_t buf_elapsed_time[] = { 8, 2, 4, 5 };
    // Create options.
    dhcp::OptionBuffer buf(buf_elapsed_time, buf_elapsed_time + 4);
    PositionedOptionPtr pkt1_elapsed_time(new PositionedOption(Option::V6, 8, buf, 86));

    // Add option to packet and create on-wire format from added options.
    // Contents of options will override contents of packet buffer.
    ASSERT_NO_THROW(pkt1->addOption(pkt1_elapsed_time));
    ASSERT_NO_THROW(pkt1->stampedRawPack());

    // Let's create another packet using packed data stored in first packet.
    // We will try to unpack data into option objects.
    buf.clear();
    OptionBuffer pkt1_output = pkt1->getData();
    boost::scoped_ptr<PerfPkt6> pkt2(new PerfPkt6(&pkt1_output[0], pkt1_output.size(), 1));

    // Create partial options to specify offsets of certain options in packet.
    PositionedOptionPtr pkt2_elapsed_time(new PositionedOption(Option::V6, D6O_ELAPSED_TIME, buf, 86));
    // Add partial options.
    pkt2->addOption(pkt2_elapsed_time);
    // Get relevant parts of buffer data into option objects.
    ASSERT_NO_THROW(pkt2->stampedRawUnpack());
    // Once option data is updated we pull it out.
    pkt2_elapsed_time = boost::dynamic_pointer_cast<PositionedOption>(pkt2->getOption(D6O_ELAPSED_TIME));
    ASSERT_TRUE(pkt2_elapsed_time);
    // Expecting option contents be the same as original.
    OptionBuffer pkt2_elapsed_time_data = pkt2_elapsed_time->getData();
    ASSERT_EQ(100, pkt2_elapsed_time->getUint16());
}

}
