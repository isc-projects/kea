// Copyright (C) 2012, 2015 Internet Systems Consortium, Inc. ("ISC")
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
#include <dhcp/dhcp4.h>

#include "../localized_option.h"
#include "../perf_pkt4.h"

using namespace std;
using namespace isc;
using namespace isc::asiolink;
using namespace isc::dhcp;
using namespace isc::perfdhcp;

typedef PerfPkt4::LocalizedOptionPtr LocalizedOptionPtr;

namespace {

// A dummy MAC address, padded with 0s
const uint8_t dummyChaddr[16] = {0, 1, 2, 3, 4, 5, 0, 0,
                                 0, 0, 0, 0, 0, 0, 0, 0 };

// Let's use some creative test content here (128 chars + \0)
const uint8_t dummyFile[] = "Lorem ipsum dolor sit amet, consectetur "
    "adipiscing elit. Proin mollis placerat metus, at "
    "lacinia orci ornare vitae. Mauris amet.";

// Yet another type of test content (64 chars + \0)
const uint8_t dummySname[] = "Lorem ipsum dolor sit amet, consectetur "
    "adipiscing elit posuere.";

class PerfPkt4Test : public ::testing::Test {
public:
    PerfPkt4Test() {
    }

    /// \brief Returns buffer with sample DHCPDISCOVER message.
    ///
    /// This method creates buffer containing on-wire data of
    /// DHCPDICOSVER message. This buffer is used by tests below
    /// to create DHCPv4 test packets.
    ///
    /// \return vector containing on-wire data
    std::vector<uint8_t>& capture() {

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

        uint8_t v4Opts[] = {
            DHO_HOST_NAME, 3, 0,   1,  2,  // Host name option.
            DHO_BOOT_SIZE, 3, 10, 11, 12,  // Boot file size option
            DHO_MERIT_DUMP, 3, 20, 21, 22, // Merit dump file
            DHO_DHCP_MESSAGE_TYPE, 1, 1,   // DHCP message type.
            128, 3, 30, 31, 32,
            254, 3, 40, 41, 42,
        };

        // Initialize the vector with the header fields defined above.
        static std::vector<uint8_t> buf(hdr, hdr + sizeof(hdr));

        // If this is a first call to this function. Initialize
        // remaining data.
        if (buf.size() == sizeof(hdr)) {

            // Append the large header fields.
            std::copy(dummyChaddr, dummyChaddr + Pkt4::MAX_CHADDR_LEN,
                      back_inserter(buf));
            std::copy(dummySname, dummySname + Pkt4::MAX_SNAME_LEN,
                      back_inserter(buf));
            std::copy(dummyFile, dummyFile + Pkt4::MAX_FILE_LEN,
                      back_inserter(buf));

            // Append magic cookie.
            buf.push_back(0x63);
            buf.push_back(0x82);
            buf.push_back(0x53);
            buf.push_back(0x63);

            // Append options.
            std::copy(v4Opts, v4Opts + sizeof(v4Opts), back_inserter(buf));
        }
        return buf;
    }
};

TEST_F(PerfPkt4Test, Constructor) {
    // Initialize some dummy payload.
    uint8_t data[250];
    for (uint8_t i = 0; i < 250; ++i) {
        data[i] = i;
    }

    // Test constructor to be used for incoming messages.
    // Use default (1) offset value and don't specify transaction id.
    const size_t offset_transid[] = { 1, 10 };
    boost::scoped_ptr<PerfPkt4> pkt1(new PerfPkt4(data,
                                                  sizeof(data),
                                                  offset_transid[0]));
    EXPECT_EQ(1, pkt1->getTransidOffset());

    // Test constructor to be used for outgoing messages.
    // Use non-zero offset and specify transaction id.
    const uint32_t transid = 0x010203;
    boost::scoped_ptr<PerfPkt4> pkt2(new PerfPkt4(data, sizeof(data),
                                                  offset_transid[1],
                                                  transid));
    EXPECT_EQ(transid, pkt2->getTransid());
    EXPECT_EQ(offset_transid[1], pkt2->getTransidOffset());

    // Test default constructor. Transaction id offset is expected to be 1.
    boost::scoped_ptr<PerfPkt4> pkt3(new PerfPkt4(data, sizeof(data)));
    EXPECT_EQ(1, pkt3->getTransidOffset());
}

TEST_F(PerfPkt4Test, RawPack) {
    // Create new packet.
    std::vector<uint8_t> buf = capture();
    boost::scoped_ptr<PerfPkt4> pkt(new PerfPkt4(&buf[0], buf.size()));

    // Initialize options data.
    uint8_t buf_hostname[] = { DHO_HOST_NAME, 3, 4, 5, 6 };
    uint8_t buf_boot_filesize[] = { DHO_BOOT_SIZE, 3, 1, 2, 3 };
    OptionBuffer vec_hostname(buf_hostname + 2,
                              buf_hostname + sizeof(buf_hostname));
    OptionBuffer vec_boot_filesize(buf_boot_filesize + 2,
                                   buf_boot_filesize + sizeof(buf_hostname));

    // Create options objects.
    const size_t offset_hostname = 240;
    LocalizedOptionPtr pkt_hostname(new LocalizedOption(Option::V4,
                                                        DHO_HOST_NAME,
                                                        vec_hostname,
                                                        offset_hostname));
    const size_t offset_boot_filesize = 245;
    LocalizedOptionPtr pkt_boot_filesize(new LocalizedOption(Option::V4,
                                                             DHO_BOOT_SIZE,
                                                             vec_boot_filesize,
                                                             offset_boot_filesize));

    // Try to add options to packet.
    ASSERT_NO_THROW(pkt->addOption(pkt_boot_filesize));
    ASSERT_NO_THROW(pkt->addOption(pkt_hostname));

    // We have valid options addedwith valid offsets so
    // pack operation should succeed.
    ASSERT_TRUE(pkt->rawPack());

    // Buffer should now contain new values of DHO_HOST_NAME and
    // DHO_BOOT_SIZE options.
    util::OutputBuffer pkt_output = pkt->getBuffer();
    ASSERT_EQ(buf.size(), pkt_output.getLength());
    const uint8_t* out_buf_data =
        static_cast<const uint8_t*>(pkt_output.getData());

    // Check if options we read from buffer is valid.
    EXPECT_EQ(0, memcmp(buf_hostname,
                        out_buf_data + offset_hostname,
                        sizeof(buf_hostname)));
    EXPECT_EQ(0, memcmp(buf_boot_filesize,
                        out_buf_data + offset_boot_filesize,
                        sizeof(buf_boot_filesize)));
}

TEST_F(PerfPkt4Test, RawUnpack) {
    // Create new packet.
    std::vector<uint8_t> buf = capture();
    boost::scoped_ptr<PerfPkt4> pkt(new PerfPkt4(&buf[0], buf.size()));

    // Create options (existing in the packet) and specify their offsets.
    const size_t offset_merit = 250;
    LocalizedOptionPtr opt_merit(new LocalizedOption(Option::V4,
                                                     DHO_MERIT_DUMP,
                                                     OptionBuffer(),
                                                     offset_merit));

    const size_t  offset_msg_type = 255;
    LocalizedOptionPtr opt_msg_type(new LocalizedOption(Option::V4,
                                                        DHO_DHCP_MESSAGE_TYPE,
                                                        OptionBuffer(),
                                                        offset_msg_type));
    // Addition should be successful
    ASSERT_NO_THROW(pkt->addOption(opt_merit));
    ASSERT_NO_THROW(pkt->addOption(opt_msg_type));

    // Option fit to packet boundaries and offsets are valid,
    // so this should unpack successfully.
    ASSERT_TRUE(pkt->rawUnpack());

    // At this point we should have updated options data (read from buffer).
    // Let's try to retrieve them.
    opt_merit = boost::dynamic_pointer_cast<LocalizedOption>
        (pkt->getOption(DHO_MERIT_DUMP));
    opt_msg_type = boost::dynamic_pointer_cast<LocalizedOption>
        (pkt->getOption(DHO_DHCP_MESSAGE_TYPE));
    ASSERT_TRUE(opt_merit);
    ASSERT_TRUE(opt_msg_type);

    // Get first option payload.
    OptionBuffer opt_merit_data = opt_merit->getData();

    // Define reference data.
    uint8_t buf_merit[] = { 20, 21, 22 };

    // Validate first option data.
    ASSERT_EQ(sizeof(buf_merit), opt_merit_data.size());
    EXPECT_TRUE(std::equal(opt_merit_data.begin(),
                           opt_merit_data.end(),
                           buf_merit));

    // Get second option payload.
    OptionBuffer opt_msg_type_data = opt_msg_type->getData();

    // Expect one byte of message type payload.
    ASSERT_EQ(1, opt_msg_type_data.size());
    EXPECT_EQ(1, opt_msg_type_data[0]);
}

TEST_F(PerfPkt4Test, InvalidOptions) {
    // Create new packet.
    std::vector<uint8_t> buf = capture();
    boost::scoped_ptr<PerfPkt4> pkt1(new PerfPkt4(&buf[0], buf.size()));

    // Create option with invalid offset.
    // This option is at offset 250 (not 251).
    const size_t offset_merit = 251;
    LocalizedOptionPtr opt_merit(new LocalizedOption(Option::V4,
                                                     DHO_MERIT_DUMP,
                                                     OptionBuffer(),
                                                     offset_merit));
    ASSERT_NO_THROW(pkt1->addOption(opt_merit));

    cout << "Testing unpack of invalid options. "
         << "This may produce spurious errors." << endl;

    // Unpack is expected to fail because it is supposed to read
    // option type from buffer and match it with DHO_MERIT_DUMP.
    // It will not match because option is shifted by on byte.
    ASSERT_FALSE(pkt1->rawUnpack());

    // Create another packet.
    boost::scoped_ptr<PerfPkt4> pkt2(new PerfPkt4(&buf[0], buf.size()));

    // Create DHO_DHCP_MESSAGE_TYPE option that has the wrong offset.
    // With this offset, option goes beyond packet size (268).
    const size_t offset_msg_type = 266;
    LocalizedOptionPtr opt_msg_type(new LocalizedOption(Option::V4,
                                                        DHO_DHCP_MESSAGE_TYPE,
                                                        OptionBuffer(1, 2),
                                                        offset_msg_type));
    // Adding option is expected to be successful because no
    // offset validation takes place at this point.
    ASSERT_NO_THROW(pkt2->addOption(opt_msg_type));

    // This is expected to fail because option is out of bounds.
    ASSERT_FALSE(pkt2->rawPack());
}

TEST_F(PerfPkt4Test, TruncatedPacket) {
    // Get the whole packet and truncate it to 249 bytes.
    std::vector<uint8_t> buf = capture();
    buf.resize(249);
    boost::scoped_ptr<PerfPkt4> pkt(new PerfPkt4(&buf[0], buf.size()));

    // Option DHO_BOOT_SIZE is now truncated because whole packet
    // is truncated. This option ends at 249 while last index of
    // truncated packet is now 248.
    const size_t offset_boot_filesize = 245;
    LocalizedOptionPtr opt_boot_filesize(new LocalizedOption(Option::V4,
                                                             DHO_BOOT_SIZE,
                                                             OptionBuffer(3, 1),
                                                             offset_boot_filesize));
    ASSERT_NO_THROW(pkt->addOption(opt_boot_filesize));

    cout << "Testing pack and unpack of options in truncated "
         << "packet. This may produce spurious errors." << endl;

    // Both pack and unpack are expected to fail because
    // added option is out of bounds.
    EXPECT_FALSE(pkt->rawUnpack());
    EXPECT_FALSE(pkt->rawPack());
}

TEST_F(PerfPkt4Test, PackTransactionId) {
    // Create dummy packet that consists of zeros.
    std::vector<uint8_t> buf(268, 0);

    const size_t offset_transid[] = { 10, 265 };
    const uint32_t transid = 0x0102;
    // Initialize transaction id 0x00000102 at offset 10.
    boost::scoped_ptr<PerfPkt4> pkt1(new PerfPkt4(&buf[0], buf.size(),
                                                  offset_transid[0],
                                                  transid));

    // Pack will inject transaction id at offset 10 into the
    // packet buffer.
    ASSERT_TRUE(pkt1->rawPack());

    // Get packet's output buffer and make sure it has valid size.
    util::OutputBuffer out_buf = pkt1->getBuffer();
    ASSERT_EQ(buf.size(), out_buf.getLength());
    const uint8_t *out_buf_data =
        static_cast<const uint8_t*>(out_buf.getData());

    // Initialize reference data for transaction id.
    const uint8_t ref_data[] = { 0, 0, 1, 2 };

    // Expect that reference transaction id matches what we have
    // read from buffer.
    EXPECT_EQ(0, memcmp(ref_data, out_buf_data + offset_transid[0], 4));

    cout << "Testing pack with invalid transaction id offset. "
         << "This may produce spurious errors" << endl;

    // Create packet with invalid transaction id offset.
    // Packet length is 268, transaction id is 4 bytes long so last byte of
    // transaction id is out of bounds.
    boost::scoped_ptr<PerfPkt4> pkt2(new PerfPkt4(&buf[0], buf.size(),
                                                  offset_transid[1],
                                                  transid));
    EXPECT_FALSE(pkt2->rawPack());
}

TEST_F(PerfPkt4Test, UnpackTransactionId) {
    // Initialize packet data, lebgth 268, zeros only.
    std::vector<uint8_t> in_data(268, 0);

    // Assume that transaction id is at offset 100.
    // Fill 4 bytes at offset 100 with dummy transaction id.
    for (uint8_t i = 100; i < 104; ++i) {
        in_data[i] = i - 99;
    }

    // Create packet from initialized buffer.
    const size_t offset_transid[] = { 100, 270 };
    boost::scoped_ptr<PerfPkt4> pkt1(new PerfPkt4(&in_data[0],
                                                  in_data.size(),
                                                  offset_transid[0]));
    ASSERT_TRUE(pkt1->rawUnpack());

    // Get unpacked transaction id and compare with reference.
    EXPECT_EQ(0x01020304, pkt1->getTransid());

    // Create packet with transaction id at invalid offset.
    boost::scoped_ptr<PerfPkt4> pkt2(new PerfPkt4(&in_data[0],
                                                  in_data.size(),
                                                  offset_transid[1]));

    cout << "Testing unpack of transaction id at invalid offset. "
         << "This may produce spurious errors." << endl;

    // Unpack is supposed to fail because transaction id is at
    // out of bounds offset.
    EXPECT_FALSE(pkt2->rawUnpack());
}

TEST_F(PerfPkt4Test, Writes) {
    // Initialize intput buffer with 260 elements set to value 1.
    dhcp::OptionBuffer in_data(260, 1);
    // Initialize buffer to be used for write: 1,2,3,4,...,9
    dhcp::OptionBuffer write_buf(10);
    for (size_t i = 0; i < write_buf.size(); ++i) {
        write_buf[i] = i;
    }
    // Create packet from the input buffer.
    const size_t transid_offset = 4;
    boost::scoped_ptr<PerfPkt4> pkt1(new PerfPkt4(&in_data[0],
                                                  in_data.size(),
                                                  transid_offset));
    // Write numbers 4,5,6,7 to the packet's input buffer at position 10.
    pkt1->writeAt(10, write_buf.begin() + 3, write_buf.begin() + 7);
    // We have to pack data to output buffer here because Pkt4 provides no
    // way to retrieve input buffer. If we pack data it will go to
    // output buffer that has getter available.
    ASSERT_TRUE(pkt1->rawPack());
    const util::OutputBuffer& out_buf = pkt1->getBuffer();
    ASSERT_EQ(in_data.size(), out_buf.getLength());
    // Verify that 4,5,6,7 has been written to the packet's buffer.
    const char* out_data = static_cast<const char*>(out_buf.getData());
    EXPECT_TRUE(std::equal(write_buf.begin() + 3, write_buf.begin() + 7,
                          out_data + 10));
    // Write 1 octet (0x51) at position 10.
    pkt1->writeValueAt<uint8_t>(10, 0x51);
    ASSERT_TRUE(pkt1->rawPack());
    ASSERT_EQ(in_data.size(), pkt1->getBuffer().getLength());
    EXPECT_EQ(0x51, pkt1->getBuffer()[10]);
    // Write 2 octets (0x5251) at position 20.
    pkt1->writeValueAt<uint16_t>(20, 0x5251);
    ASSERT_TRUE(pkt1->rawPack());
    ASSERT_EQ(in_data.size(), pkt1->getBuffer().getLength());
    EXPECT_EQ(0x52, pkt1->getBuffer()[20]);
    EXPECT_EQ(0x51, pkt1->getBuffer()[21]);
    // Write 4 octets (0x54535251) at position 30.
    pkt1->writeValueAt<uint32_t>(30, 0x54535251);
    ASSERT_TRUE(pkt1->rawPack());
    ASSERT_EQ(in_data.size(), pkt1->getBuffer().getLength());
    EXPECT_EQ(0x54, pkt1->getBuffer()[30]);
    EXPECT_EQ(0x53, pkt1->getBuffer()[31]);
    EXPECT_EQ(0x52, pkt1->getBuffer()[32]);
    EXPECT_EQ(0x51, pkt1->getBuffer()[33]);
}

}
