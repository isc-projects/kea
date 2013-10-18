// Copyright (C) 2011-2013 Internet Systems Consortium, Inc. ("ISC")
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
#include <dhcp/dhcp6.h>
#include <dhcp/option.h>
#include <dhcp/option_custom.h>
#include <dhcp/option6_ia.h>
#include <dhcp/option_int.h>
#include <dhcp/option_int_array.h>
#include <dhcp/pkt6.h>
#include <util/range_utilities.h>

#include <boost/bind.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/scoped_ptr.hpp>
#include <util/encode/hex.h>
#include <gtest/gtest.h>

#include <iostream>
#include <sstream>

#include <arpa/inet.h>

using namespace std;
using namespace isc;
using namespace isc::asiolink;
using namespace isc::dhcp;
using boost::scoped_ptr;

namespace {

/// @brief A class which contains a custom callback function to unpack options.
///
/// This is a class used by the tests which verify that the custom callback
/// functions can be installed to unpack options from a message. When the
/// callback function is called, the executed_ member is set to true to allow
/// verification that the callback was really called. Internally, this class
/// uses libdhcp++ to unpack options so the options parsing algorithm remains
/// unchanged after installation of the callback.
class CustomUnpackCallback {
public:

    /// @brief Constructor
    ///
    /// Marks that callback hasn't been called.
    CustomUnpackCallback()
        : executed_(false) {
    }

    /// @brief A callback
    ///
    /// Contains custom implementation of the callback.
    ///
    /// @param buf a A buffer holding options in on-wire format.
    /// @param option_space A name of the option space encapsulated by the
    /// option being parsed.
    /// @param [out] options A reference to the collection where parsed options
    /// will be stored.
    /// @param relay_msg_offset Reference to a size_t structure. If specified,
    /// offset to beginning of relay_msg option will be stored in it.
    /// @param relay_msg_len reference to a size_t structure. If specified,
    /// length of the relay_msg option will be stored in it.
    /// @return An offset to the first byte after last parsed option.
    size_t execute(const OptionBuffer& buf,
                   const std::string& option_space,
                   isc::dhcp::OptionCollection& options,
                   size_t* relay_msg_offset,
                   size_t* relay_msg_len) {
        // Set the executed_ member to true to allow verification that the
        // callback has been actually called.
        executed_ = true;
        // Use default implementation of the unpack algorithm to parse options.
        return (LibDHCP::unpackOptions6(buf, option_space, options, relay_msg_offset,
                                        relay_msg_len));
    }

    /// A flag which indicates if callback function has been called.
    bool executed_;
};

class Pkt6Test : public ::testing::Test {
public:
    Pkt6Test() {
    }

    /// @brief generates an option with given code (and length) and random content
    ///
    /// @param code option code
    /// @param len data length (data will be randomized)
    ///
    /// @return pointer to the new option
    OptionPtr generateRandomOption(uint16_t code, size_t len = 10) {
        OptionBuffer data(len);
        util::fillRandom(data.begin(), data.end());
        return OptionPtr(new Option(Option::V6, code, data));
    }

    /// @brief Create a wire representation of the test packet and clone it.
    ///
    /// The purpose of this function is to create a packet to be used to
    /// check that packet parsing works correctly. The unpack() function
    /// requires that the data_ field of the object holds the data to be
    /// parsed. This function creates an on-wire representation of the
    /// packet by calling pack(). But, the pack() function stores the
    /// on-wire representation into the output buffer (not the data_ field).
    /// For this reason, it is not enough to return the packet on which
    /// pack() is called. This function returns a clone of this packet
    /// which is created using a constructor taking a buffer and buffer
    /// length as an input. This constructor is normally used to parse
    /// received packets. It stores the packet in a data_ field and
    /// therefore unpack() can be called to parse it.
    Pkt6Ptr packAndClone() {
        Pkt6Ptr parent(new Pkt6(DHCPV6_SOLICIT, 0x020304));

        OptionPtr opt1(new Option(Option::V6, 1));
        OptionPtr opt2(new Option(Option::V6, 2));
        OptionPtr opt3(new Option(Option::V6, 100));
        // Let's not use zero-length option type 3 as it is IA_NA

        parent->addOption(opt1);
        parent->addOption(opt2);
        parent->addOption(opt3);

        EXPECT_EQ(DHCPV6_SOLICIT, parent->getType());

        // Calculated length should be 16
        EXPECT_EQ(Pkt6::DHCPV6_PKT_HDR_LEN + 3 * Option::OPTION6_HDR_LEN,
                  parent->len());

        EXPECT_NO_THROW(parent->pack());

        EXPECT_EQ(Pkt6::DHCPV6_PKT_HDR_LEN + 3 * Option::OPTION6_HDR_LEN,
                  parent->len());

        // Create second packet,based on assembled data from the first one
        Pkt6Ptr clone(new Pkt6(static_cast<const uint8_t*>
                               (parent->getBuffer().getData()),
                               parent->getBuffer().getLength()));
        return (clone);

    }
};

TEST_F(Pkt6Test, constructor) {
    uint8_t data[] = { 0, 1, 2, 3, 4, 5 };
    scoped_ptr<Pkt6> pkt1(new Pkt6(data, sizeof(data)));

    EXPECT_EQ(6, pkt1->data_.size());
    EXPECT_EQ(0, memcmp( &pkt1->data_[0], data, sizeof(data)));
}

/// @brief returns captured actual SOLICIT packet
///
/// Captured SOLICIT packet with transid=0x3d79fb and options: client-id,
/// in_na, dns-server, elapsed-time, option-request
/// This code was autogenerated (see src/bin/dhcp6/tests/iface_mgr_unittest.c),
/// but we spent some time to make is less ugly than it used to be.
///
/// @return pointer to Pkt6 that represents received SOLICIT
Pkt6* capture1() {
    Pkt6* pkt;
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

    pkt = new Pkt6(data, sizeof(data));
    pkt->setRemotePort(546);
    pkt->setRemoteAddr(IOAddress("fe80::21e:8cff:fe9b:7349"));
    pkt->setLocalPort(0);
    pkt->setLocalAddr(IOAddress("ff02::1:2"));
    pkt->setIndex(2);
    pkt->setIface("eth0");

    return (pkt);
}

/// @brief creates doubly relayed solicit message
///
/// This is a traffic capture exported from wireshark. It includes a SOLICIT
/// message that passed through two relays. Each relay include interface-id,
/// remote-id and relay-forw encapsulation. It is especially interesting,
/// because of the following properties:
/// - double encapsulation
/// - first relay inserts relay-msg before extra options
/// - second relay inserts relay-msg after extra options
/// - both relays are from different vendors
/// - interface-id are different for each relay
/// - first relay inserts valid remote-id
/// - second relay inserts remote-id with empty vendor data
/// - the solicit message requests for custom options in ORO
/// - there are option types in RELAY-FORW that do not appear in SOLICIT
/// - there are option types in SOLICT that do not appear in RELAY-FORW
///
/// RELAY-FORW
///  - relay message option
///      - RELAY-FORW
///          - interface-id option
///          - remote-id option
///          - RELAY-FORW
///              SOLICIT
///                  - client-id option
///                  - ia_na option
///                  - elapsed time
///                  - ORO
///  - interface-id option
///  - remote-id option
///
/// The original capture was posted to dibbler users mailing list.
///
/// @return created double relayed SOLICIT message
Pkt6* capture2() {

    // string exported from Wireshark
    string hex_string =
        "0c01200108880db800010000000000000000fe80000000000000020021fffe5c18a900"
        "09007d0c0000000000000000000000000000000000fe80000000000000020021fffe5c"
        "18a9001200154953414d3134342065746820312f312f30352f30310025000400000de9"
        "00090036016b4fe20001000e0001000118b033410000215c18a90003000c00000001ff"
        "ffffffffffffff00080002000000060006001700f200f30012001c4953414d3134347c"
        "3239397c697076367c6e743a76703a313a313130002500120000197f0001000118b033"
        "410000215c18a9";

    std::vector<uint8_t> bin;

    // Decode the hex string and store it in bin (which happens
    // to be OptionBuffer format)
    isc::util::encode::decodeHex(hex_string, bin);

    Pkt6* pkt = new Pkt6(&bin[0], bin.size());
    pkt->setRemotePort(547);
    pkt->setRemoteAddr(IOAddress("fe80::1234"));
    pkt->setLocalPort(547);
    pkt->setLocalAddr(IOAddress("ff05::1:3"));
    pkt->setIndex(2);
    pkt->setIface("eth0");
    return (pkt);
}

TEST_F(Pkt6Test, unpack_solicit1) {
    scoped_ptr<Pkt6> sol(capture1());

    ASSERT_EQ(true, sol->unpack());

    // Check for length
    EXPECT_EQ(98, sol->len() );

    // Check for type
    EXPECT_EQ(DHCPV6_SOLICIT, sol->getType() );

    // Check that all present options are returned
    EXPECT_TRUE(sol->getOption(D6O_CLIENTID)); // client-id is present
    EXPECT_TRUE(sol->getOption(D6O_IA_NA));    // IA_NA is present
    EXPECT_TRUE(sol->getOption(D6O_ELAPSED_TIME));  // elapsed is present
    EXPECT_TRUE(sol->getOption(D6O_NAME_SERVERS));
    EXPECT_TRUE(sol->getOption(D6O_ORO));

    // Let's check that non-present options are not returned
    EXPECT_FALSE(sol->getOption(D6O_SERVERID)); // server-id is missing
    EXPECT_FALSE(sol->getOption(D6O_IA_TA));
    EXPECT_FALSE(sol->getOption(D6O_IAADDR));
}

TEST_F(Pkt6Test, packUnpack) {
    // Create an on-wire representation of the test packet and clone it.
    Pkt6Ptr clone = packAndClone();

    // Now recreate options list
    EXPECT_TRUE(clone->unpack());

    // transid, message-type should be the same as before
    EXPECT_EQ(0x020304, clone->getTransid());
    EXPECT_EQ(DHCPV6_SOLICIT, clone->getType());

    EXPECT_TRUE(clone->getOption(1));
    EXPECT_TRUE(clone->getOption(2));
    EXPECT_TRUE(clone->getOption(100));
    EXPECT_FALSE(clone->getOption(4));
}

// This test verifies that it is possible to specify custom implementation of
// the option parsing algorithm by installing a callback function.
TEST_F(Pkt6Test, packUnpackWithCallback) {
    // Create an on-wire representation of the test packet and clone it.
    Pkt6Ptr clone = packAndClone();

    // Install the custom callback function. We expect that this function
    // will be called to parse options in the packet instead of
    // LibDHCP::unpackOptions6.
    CustomUnpackCallback cb;
    clone->setCallback(boost::bind(&CustomUnpackCallback::execute, &cb,
                                   _1, _2, _3, _4, _5));
    // Make sure that the flag which indicates if the callback function has
    // been called is not set. Otherwise, our test doesn't make sense.
    ASSERT_FALSE(cb.executed_);

    // Now recreate options list
    EXPECT_TRUE(clone->unpack());

    // An object which holds a callback should now have a flag set which
    // indicates that callback has been called.
    EXPECT_TRUE(cb.executed_);

    // transid, message-type should be the same as before
    EXPECT_EQ(0x020304, clone->getTransid());
    EXPECT_EQ(DHCPV6_SOLICIT, clone->getType());

    EXPECT_TRUE(clone->getOption(1));
    EXPECT_TRUE(clone->getOption(2));
    EXPECT_TRUE(clone->getOption(100));
    EXPECT_FALSE(clone->getOption(4));

    // Reset the indicator to perform another check: uninstall the callback.
    cb.executed_ = false;
    // By setting the callback to NULL we effectively uninstall the callback.
    clone->setCallback(NULL);
    // Do another unpack.
    EXPECT_TRUE(clone->unpack());
    // Callback should not be executed.
    EXPECT_FALSE(cb.executed_);
}

// This test verifies that options can be added (addOption()), retrieved
// (getOption(), getOptions()) and deleted (delOption()).
TEST_F(Pkt6Test, addGetDelOptions) {
    scoped_ptr<Pkt6> parent(new Pkt6(DHCPV6_SOLICIT, random()));

    OptionPtr opt1(new Option(Option::V6, 1));
    OptionPtr opt2(new Option(Option::V6, 2));
    OptionPtr opt3(new Option(Option::V6, 2));

    parent->addOption(opt1);
    parent->addOption(opt2);

    // getOption() test
    EXPECT_EQ(opt1, parent->getOption(1));
    EXPECT_EQ(opt2, parent->getOption(2));

    // Expect NULL
    EXPECT_EQ(OptionPtr(), parent->getOption(4));

    // Now there are 2 options of type 2
    parent->addOption(opt3);

    OptionCollection options = parent->getOptions(2);
    EXPECT_EQ(2, options.size()); // there should be 2 instances

    // Both options must be of type 2 and there must not be
    // any other type returned
    for (OptionCollection::const_iterator x= options.begin();
         x != options.end(); ++x) {
        EXPECT_EQ(2, x->second->getType());
    }

    // Try to get a single option. Normally for singular options
    // it is better to use getOption(), but getOptions() must work
    // as well
    options = parent->getOptions(1);
    ASSERT_EQ(1, options.size());

    EXPECT_EQ(1, (*options.begin()).second->getType());
    EXPECT_EQ(opt1, options.begin()->second);

    // Let's delete one of them
    EXPECT_EQ(true, parent->delOption(2));

    // There still should be the other option 2
    EXPECT_NE(OptionPtr(), parent->getOption(2));

    // Let's delete the other option 2
    EXPECT_EQ(true, parent->delOption(2));

    // No more options with type=2
    EXPECT_EQ(OptionPtr(), parent->getOption(2));

    // Let's try to delete - should fail
    EXPECT_TRUE(false ==  parent->delOption(2));

    // Finally try to get a non-existent option
    options = parent->getOptions(1234);
    EXPECT_EQ(0, options.size());
}

TEST_F(Pkt6Test, Timestamp) {
    boost::scoped_ptr<Pkt6> pkt(new Pkt6(DHCPV6_SOLICIT, 0x020304));

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

// This test verifies that getName() method returns proper
// packet type names.
TEST_F(Pkt6Test, getName) {
    // Check all possible packet types
    for (int itype = 0; itype < 256; ++itype) {
        uint8_t type = itype;

        switch (type) {
        case DHCPV6_CONFIRM:
            EXPECT_STREQ("CONFIRM", Pkt6::getName(type));
            break;

        case DHCPV6_DECLINE:
            EXPECT_STREQ("DECLINE", Pkt6::getName(type));
            break;

        case DHCPV6_INFORMATION_REQUEST:
            EXPECT_STREQ("INFORMATION_REQUEST",
                         Pkt6::getName(type));
            break;

        case DHCPV6_REBIND:
            EXPECT_STREQ("REBIND", Pkt6::getName(type));
            break;

        case DHCPV6_RELEASE:
            EXPECT_STREQ("RELEASE", Pkt6::getName(type));
            break;

        case DHCPV6_RENEW:
            EXPECT_STREQ("RENEW", Pkt6::getName(type));
            break;

        case DHCPV6_REQUEST:
            EXPECT_STREQ("REQUEST", Pkt6::getName(type));
            break;

        case DHCPV6_SOLICIT:
            EXPECT_STREQ("SOLICIT", Pkt6::getName(type));
            break;

        default:
            EXPECT_STREQ("UNKNOWN", Pkt6::getName(type));
        }
    }
}

// This test verifies that a fancy solicit that passed through two
// relays can be parsed properly. See capture2() method description
// for details regarding the packet.
TEST_F(Pkt6Test, relayUnpack) {
    boost::scoped_ptr<Pkt6> msg(capture2());

    EXPECT_NO_THROW(msg->unpack());

    EXPECT_EQ(DHCPV6_SOLICIT, msg->getType());
    EXPECT_EQ(217, msg->len());

    ASSERT_EQ(2, msg->relay_info_.size());

    OptionPtr opt;

    // Part 1: Check options inserted by the first relay

    // There should be 2 options in first relay
    EXPECT_EQ(2, msg->relay_info_[0].options_.size());

    // There should be interface-id option
    ASSERT_TRUE(opt = msg->getRelayOption(D6O_INTERFACE_ID, 0));
    OptionBuffer data = opt->getData();
    EXPECT_EQ(32, opt->len()); // 28 bytes of data + 4 bytes header
    EXPECT_EQ(data.size(), 28);
    // That's a strange interface-id, but this is a real life example
    EXPECT_TRUE(0 == memcmp("ISAM144|299|ipv6|nt:vp:1:110", &data[0], 28));

    // Get the remote-id option
    ASSERT_TRUE(opt = msg->getRelayOption(D6O_REMOTE_ID, 0));
    EXPECT_EQ(22, opt->len()); // 18 bytes of data + 4 bytes header
    boost::shared_ptr<OptionCustom> custom = boost::dynamic_pointer_cast<OptionCustom>(opt);

    uint32_t vendor_id = custom->readInteger<uint32_t>(0);
    EXPECT_EQ(6527, vendor_id); // 6527 = Panthera Networks

    uint8_t expected_remote_id[] = { 0x00, 0x01, 0x00, 0x01, 0x18, 0xb0, 0x33, 0x41, 0x00,
                                     0x00, 0x21, 0x5c, 0x18, 0xa9 };
    OptionBuffer remote_id = custom->readBinary(1);
    ASSERT_EQ(sizeof(expected_remote_id), remote_id.size());
    ASSERT_EQ(0, memcmp(expected_remote_id, &remote_id[0], remote_id.size()));

    // Part 2: Check options inserted by the second relay

    // Get the interface-id from the second relay
    ASSERT_TRUE(opt = msg->getRelayOption(D6O_INTERFACE_ID, 1));
    data = opt->getData();
    EXPECT_EQ(25, opt->len()); // 21 bytes + 4 bytes header
    EXPECT_EQ(data.size(), 21);
    EXPECT_TRUE(0 == memcmp("ISAM144 eth 1/1/05/01", &data[0], 21));

    // Get the remote-id option
    ASSERT_TRUE(opt = msg->getRelayOption(D6O_REMOTE_ID, 1));
    EXPECT_EQ(8, opt->len());
    custom = boost::dynamic_pointer_cast<OptionCustom>(opt);

    vendor_id = custom->readInteger<uint32_t>(0);
    EXPECT_EQ(3561, vendor_id); // 3561 = Broadband Forum
    // @todo: See if we can validate empty remote-id field

    // Let's check if there is no leak between options stored in
    // the SOLICIT message and the relay.
    EXPECT_FALSE(opt = msg->getRelayOption(D6O_IA_NA, 1));


    // Part 3: Let's check options in the message itself
    // This is not redundant compared to other direct messages tests,
    // as we parsed it differently
    EXPECT_EQ(DHCPV6_SOLICIT, msg->getType());
    EXPECT_EQ(0x6b4fe2, msg->getTransid());

    ASSERT_TRUE(opt = msg->getOption(D6O_CLIENTID));
    EXPECT_EQ(18, opt->len()); // 14 bytes of data + 4 bytes of header
    uint8_t expected_client_id[] = { 0x00, 0x01, 0x00, 0x01, 0x18, 0xb0, 0x33, 0x41, 0x00,
                                     0x00, 0x21, 0x5c, 0x18, 0xa9 };
    data = opt->getData();
    ASSERT_EQ(data.size(), sizeof(expected_client_id));
    ASSERT_EQ(0, memcmp(&data[0], expected_client_id, data.size()));

    ASSERT_TRUE(opt = msg->getOption(D6O_IA_NA));
    boost::shared_ptr<Option6IA> ia =
        boost::dynamic_pointer_cast<Option6IA>(opt);
    ASSERT_TRUE(ia);
    EXPECT_EQ(1, ia->getIAID());
    EXPECT_EQ(0xffffffff, ia->getT1());
    EXPECT_EQ(0xffffffff, ia->getT2());

    ASSERT_TRUE(opt = msg->getOption(D6O_ELAPSED_TIME));
    EXPECT_EQ(6, opt->len()); // 2 bytes of data + 4 bytes of header
    boost::shared_ptr<OptionInt<uint16_t> > elapsed =
        boost::dynamic_pointer_cast<OptionInt<uint16_t> > (opt);
    ASSERT_TRUE(elapsed);
    EXPECT_EQ(0, elapsed->getValue());

    ASSERT_TRUE(opt = msg->getOption(D6O_ORO));
    boost::shared_ptr<OptionIntArray<uint16_t> > oro =
        boost::dynamic_pointer_cast<OptionIntArray<uint16_t> > (opt);
    const std::vector<uint16_t> oro_list = oro->getValues();
    EXPECT_EQ(3, oro_list.size());
    EXPECT_EQ(23, oro_list[0]);
    EXPECT_EQ(242, oro_list[1]);
    EXPECT_EQ(243, oro_list[2]);
}

// This test verified that message with relay information can be
// packed and then unpacked.
TEST_F(Pkt6Test, relayPack) {

    scoped_ptr<Pkt6> parent(new Pkt6(DHCPV6_ADVERTISE, 0x020304));

    Pkt6::RelayInfo relay1;
    relay1.msg_type_ = DHCPV6_RELAY_REPL;
    relay1.hop_count_ = 17; // not very miningful, but useful for testing
    relay1.linkaddr_ = IOAddress("2001:db8::1");
    relay1.peeraddr_ = IOAddress("fe80::abcd");

    uint8_t relay_opt_data[] = { 1, 2, 3, 4, 5, 6, 7, 8};
    vector<uint8_t> relay_data(relay_opt_data,
                               relay_opt_data + sizeof(relay_opt_data));

    OptionPtr optRelay1(new Option(Option::V6, 200, relay_data));

    relay1.options_.insert(make_pair(optRelay1->getType(), optRelay1));

    OptionPtr opt1(new Option(Option::V6, 100));
    OptionPtr opt2(new Option(Option::V6, 101));
    OptionPtr opt3(new Option(Option::V6, 102));
    // Let's not use zero-length option type 3 as it is IA_NA

    parent->addRelayInfo(relay1);

    parent->addOption(opt1);
    parent->addOption(opt2);
    parent->addOption(opt3);

    EXPECT_EQ(DHCPV6_ADVERTISE, parent->getType());

    EXPECT_NO_THROW(parent->pack());

    EXPECT_EQ(Pkt6::DHCPV6_PKT_HDR_LEN + 3 * Option::OPTION6_HDR_LEN // ADVERTISE
              + Pkt6::DHCPV6_RELAY_HDR_LEN // Relay header
              + Option::OPTION6_HDR_LEN // Relay-msg
              + optRelay1->len(),
              parent->len());

    // Create second packet,based on assembled data from the first one
    scoped_ptr<Pkt6> clone(new Pkt6(static_cast<const uint8_t*>(
                                    parent->getBuffer().getData()),
                                    parent->getBuffer().getLength()));

    // Now recreate options list
    EXPECT_TRUE( clone->unpack() );

    // transid, message-type should be the same as before
    EXPECT_EQ(parent->getTransid(), parent->getTransid());
    EXPECT_EQ(DHCPV6_ADVERTISE, clone->getType());

    EXPECT_TRUE( clone->getOption(100));
    EXPECT_TRUE( clone->getOption(101));
    EXPECT_TRUE( clone->getOption(102));
    EXPECT_FALSE(clone->getOption(103));

    // Now check relay info
    ASSERT_EQ(1, clone->relay_info_.size());
    EXPECT_EQ(DHCPV6_RELAY_REPL, clone->relay_info_[0].msg_type_);
    EXPECT_EQ(17, clone->relay_info_[0].hop_count_);
    EXPECT_EQ("2001:db8::1", clone->relay_info_[0].linkaddr_.toText());
    EXPECT_EQ("fe80::abcd", clone->relay_info_[0].peeraddr_.toText());

    // There should be exactly one option
    EXPECT_EQ(1, clone->relay_info_[0].options_.size());
    OptionPtr opt = clone->getRelayOption(200, 0);
    EXPECT_TRUE(opt);
    EXPECT_EQ(opt->getType() , optRelay1->getType());
    EXPECT_EQ(opt->len(), optRelay1->len());
    OptionBuffer data = opt->getData();
    ASSERT_EQ(data.size(), sizeof(relay_opt_data));
    EXPECT_EQ(0, memcmp(relay_opt_data, relay_opt_data, sizeof(relay_opt_data)));
}


// This test verified that options added by relays to the message can be
// accessed and retrieved properly
TEST_F(Pkt6Test, getAnyRelayOption) {

    boost::scoped_ptr<Pkt6> msg(new Pkt6(DHCPV6_ADVERTISE, 0x020304));
    msg->addOption(generateRandomOption(300));

    // generate options for relay1
    Pkt6::RelayInfo relay1;

    // generate 3 options with code 200,201,202 and random content
    OptionPtr relay1_opt1(generateRandomOption(200));
    OptionPtr relay1_opt2(generateRandomOption(201));
    OptionPtr relay1_opt3(generateRandomOption(202));

    relay1.options_.insert(make_pair(200, relay1_opt1));
    relay1.options_.insert(make_pair(201, relay1_opt2));
    relay1.options_.insert(make_pair(202, relay1_opt3));
    msg->addRelayInfo(relay1);

    // generate options for relay2
    Pkt6::RelayInfo relay2;
    OptionPtr relay2_opt1(new Option(Option::V6, 100));
    OptionPtr relay2_opt2(new Option(Option::V6, 101));
    OptionPtr relay2_opt3(new Option(Option::V6, 102));
    OptionPtr relay2_opt4(new Option(Option::V6, 200)); // the same code as relay1_opt3
    relay2.options_.insert(make_pair(100, relay2_opt1));
    relay2.options_.insert(make_pair(101, relay2_opt2));
    relay2.options_.insert(make_pair(102, relay2_opt3));
    relay2.options_.insert(make_pair(200, relay2_opt4));
    msg->addRelayInfo(relay2);

    // generate options for relay3
    Pkt6::RelayInfo relay3;
    OptionPtr relay3_opt1(generateRandomOption(200, 7));
    relay3.options_.insert(make_pair(200, relay3_opt1));
    msg->addRelayInfo(relay3);

    // Ok, so we now have a packet that traversed the following network:
    // client---relay3---relay2---relay1---server

    // First check that the getAnyRelayOption does not confuse client options
    // and relay options
    // 300 is a client option, present in the message itself.
    OptionPtr opt = msg->getAnyRelayOption(300, Pkt6::RELAY_SEARCH_FROM_CLIENT);
    EXPECT_FALSE(opt);
    opt = msg->getAnyRelayOption(300, Pkt6::RELAY_SEARCH_FROM_SERVER);
    EXPECT_FALSE(opt);
    opt = msg->getAnyRelayOption(300, Pkt6::RELAY_GET_FIRST);
    EXPECT_FALSE(opt);
    opt = msg->getAnyRelayOption(300, Pkt6::RELAY_GET_LAST);
    EXPECT_FALSE(opt);

    // Option 200 is added in every relay.

    // We want to get that one inserted by relay3 (first match, starting from
    // closest to the client.
    opt = msg->getAnyRelayOption(200, Pkt6::RELAY_SEARCH_FROM_CLIENT);
    ASSERT_TRUE(opt);
    EXPECT_TRUE(opt->equal(relay3_opt1));

    // We want to ge that one inserted by relay1 (first match, starting from
    // closest to the server.
    opt = msg->getAnyRelayOption(200, Pkt6::RELAY_SEARCH_FROM_SERVER);
    ASSERT_TRUE(opt);
    EXPECT_TRUE(opt->equal(relay1_opt1));

    // We just want option from the first relay (closest to the client)
    opt = msg->getAnyRelayOption(200, Pkt6::RELAY_GET_FIRST);
    ASSERT_TRUE(opt);
    EXPECT_TRUE(opt->equal(relay3_opt1));

    // We just want option from the last relay (closest to the server)
    opt = msg->getAnyRelayOption(200, Pkt6::RELAY_GET_LAST);
    ASSERT_TRUE(opt);
    EXPECT_TRUE(opt->equal(relay1_opt1));

    // Let's try to ask for something that is inserted by the middle relay
    // only.
    opt = msg->getAnyRelayOption(100, Pkt6::RELAY_SEARCH_FROM_SERVER);
    ASSERT_TRUE(opt);
    EXPECT_TRUE(opt->equal(relay2_opt1));

    opt = msg->getAnyRelayOption(100, Pkt6::RELAY_SEARCH_FROM_CLIENT);
    ASSERT_TRUE(opt);
    EXPECT_TRUE(opt->equal(relay2_opt1));

    opt = msg->getAnyRelayOption(100, Pkt6::RELAY_GET_FIRST);
    EXPECT_FALSE(opt);

    opt = msg->getAnyRelayOption(100, Pkt6::RELAY_GET_LAST);
    EXPECT_FALSE(opt);

    // Finally, try to get an option that does not exist
    opt = msg->getAnyRelayOption(500, Pkt6::RELAY_GET_FIRST);
    EXPECT_FALSE(opt);

    opt = msg->getAnyRelayOption(500, Pkt6::RELAY_GET_LAST);
    EXPECT_FALSE(opt);

    opt = msg->getAnyRelayOption(500, Pkt6::RELAY_SEARCH_FROM_SERVER);
    EXPECT_FALSE(opt);

    opt = msg->getAnyRelayOption(500, Pkt6::RELAY_SEARCH_FROM_CLIENT);
    EXPECT_FALSE(opt);
}

// Tests whether a packet can be assigned to a class and later
// checked if it belongs to a given class
TEST_F(Pkt6Test, clientClasses) {
    Pkt6 pkt(DHCPV6_ADVERTISE, 1234);

    // Default values (do not belong to any class)
    EXPECT_FALSE(pkt.inClass("eRouter1.0"));
    EXPECT_FALSE(pkt.inClass("docsis3.0"));
    EXPECT_TRUE(pkt.classes_.empty());

    // Add to the first class
    pkt.addClass("eRouter1.0");
    EXPECT_TRUE(pkt.inClass("eRouter1.0"));
    EXPECT_FALSE(pkt.inClass("docsis3.0"));
    ASSERT_FALSE(pkt.classes_.empty());

    // Add to a second class
    pkt.addClass("docsis3.0");
    EXPECT_TRUE(pkt.inClass("eRouter1.0"));
    EXPECT_TRUE(pkt.inClass("docsis3.0"));

    // Check that it's ok to add to the same class repeatedly
    EXPECT_NO_THROW(pkt.addClass("foo"));
    EXPECT_NO_THROW(pkt.addClass("foo"));
    EXPECT_NO_THROW(pkt.addClass("foo"));
}

}
