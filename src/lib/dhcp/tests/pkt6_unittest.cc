// Copyright (C) 2011-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <asiolink/io_address.h>
#include <dhcp/dhcp6.h>
#include <dhcp/option.h>
#include <dhcp/option_custom.h>
#include <dhcp/option6_ia.h>
#include <dhcp/option_int.h>
#include <dhcp/option_int_array.h>
#include <dhcp/option_vendor.h>
#include <dhcp/iface_mgr.h>
#include <dhcp/pkt6.h>
#include <dhcp/hwaddr.h>
#include <dhcp/docsis3_option_defs.h>
#include <dhcp/tests/pkt_captures.h>
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
using namespace isc::dhcp::test;
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
        return (LibDHCP::unpackOptions6(buf, option_space, options,
                                        relay_msg_offset, relay_msg_len));
    }

    /// A flag which indicates if callback function has been called.
    bool executed_;
};

class Pkt6Test : public ::testing::Test {
public:
    Pkt6Test() {
    }

    /// @brief generates an option with given code (and length) and
    /// random content
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
    ///
    /// @param parent Packet from which the new packet should be created.
    Pkt6Ptr packAndClone(Pkt6Ptr& parent) {
        OptionPtr opt1(new Option(Option::V6, 1));
        OptionPtr opt2(new Option(Option::V6, 2));
        OptionPtr opt3(new Option(Option::V6, 100));
        // Let's not use zero-length option type 3 as it is IA_NA

        parent->addOption(opt1);
        parent->addOption(opt2);
        parent->addOption(opt3);

        EXPECT_NO_THROW(parent->pack());

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
        "0c01200108880db800010000000000000000fe80000000000000020021fffe5c"
        "18a90009007d0c0000000000000000000000000000000000fe80000000000000"
        "020021fffe5c18a9001200154953414d3134342065746820312f312f30352f30"
        "310025000400000de900090036016b4fe20001000e0001000118b03341000021"
        "5c18a90003000c00000001ffffffffffffffff00080002000000060006001700"
        "f200f30012001c4953414d3134347c3239397c697076367c6e743a76703a313a"
        "313130002500120000197f0001000118b033410000215c18a9";

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

    ASSERT_NO_THROW(sol->unpack());

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
    Pkt6Ptr pkt(new Pkt6(DHCPV6_SOLICIT, 0x020304));
    Pkt6Ptr clone = packAndClone(pkt);

    // Now recreate options list
    ASSERT_NO_THROW(clone->unpack());

    // transid, message-type should be the same as before
    EXPECT_EQ(0x020304, clone->getTransid());
    EXPECT_EQ(DHCPV6_SOLICIT, clone->getType());

    EXPECT_TRUE(clone->getOption(1));
    EXPECT_TRUE(clone->getOption(2));
    EXPECT_TRUE(clone->getOption(100));
    EXPECT_FALSE(clone->getOption(4));
}

// Checks if the code is able to handle malformed packet
TEST_F(Pkt6Test, unpackMalformed) {
    // Get a packet. We're really interested in its on-wire
    // representation only.
    scoped_ptr<Pkt6> donor(capture1());

    // That's our original content. It should be sane.
    OptionBuffer orig = donor->data_;

    Pkt6Ptr success(new Pkt6(&orig[0], orig.size()));
    EXPECT_NO_THROW(success->unpack());

    // Insert trailing garbage.
    OptionBuffer malform1 = orig;
    malform1.push_back(123);

    // Let's check a truncated packet. Moderately sane DHCPv6 packet should at
    // least have four bytes header. Zero bytes is definitely not a valid one.
    OptionBuffer empty(1); // Let's allocate one byte, so we won't be
                           // dereferencing an empty buffer.

    Pkt6Ptr empty_pkt(new Pkt6(&empty[0], 0));
    EXPECT_THROW(empty_pkt->unpack(), isc::BadValue);

    // Neither is 3 bytes long.
    OptionBuffer shorty;
    shorty.push_back(DHCPV6_SOLICIT);
    shorty.push_back(1);
    shorty.push_back(2);
    Pkt6Ptr too_short_pkt(new Pkt6(&shorty[0], shorty.size()));
    EXPECT_THROW(too_short_pkt->unpack(), isc::BadValue);

    // The code should complain about remaining bytes that can't be parsed
    // but doesn't do so yet.
    Pkt6Ptr trailing_garbage(new Pkt6(&malform1[0], malform1.size()));
    EXPECT_NO_THROW(trailing_garbage->unpack());

    // A strict approach would assume the code will reject the whole packet,
    // but we decided to follow Jon Postel's law and be silent about
    // received malformed or truncated options.

    // Add an option that is truncated
    OptionBuffer malform2 = orig;
    malform2.push_back(0);
    malform2.push_back(123); // 0, 123 - option code = 123
    malform2.push_back(0);
    malform2.push_back(1);   // 0, 1 - option length = 1
    // Option content would go here, but it's missing

    Pkt6Ptr trunc_option(new Pkt6(&malform2[0], malform2.size()));

    // The unpack() operation should succeed...
    EXPECT_NO_THROW(trunc_option->unpack());

    // ... but there should be no option 123 as it was malformed.
    EXPECT_FALSE(trunc_option->getOption(123));

    // Check with truncated length field
    Pkt6Ptr trunc_length(new Pkt6(&malform2[0], malform2.size() - 1));
    EXPECT_NO_THROW(trunc_length->unpack());
    EXPECT_FALSE(trunc_length->getOption(123));

    // Check with missing length field
    Pkt6Ptr no_length(new Pkt6(&malform2[0], malform2.size() - 2));
    EXPECT_NO_THROW(no_length->unpack());
    EXPECT_FALSE(no_length->getOption(123));

    // Check with truncated type field
    Pkt6Ptr trunc_type(new Pkt6(&malform2[0], malform2.size() - 3));
    EXPECT_NO_THROW(trunc_type->unpack());
    EXPECT_FALSE(trunc_type->getOption(123));
}

// Checks if the code is able to handle a malformed vendor option
TEST_F(Pkt6Test, unpackVendorMalformed) {
    // Get a packet. We're really interested in its on-wire
    // representation only.
    scoped_ptr<Pkt6> donor(capture1());

    // Add a vendor option
    OptionBuffer orig = donor->data_;

    orig.push_back(0); // vendor options
    orig.push_back(17);
    orig.push_back(0);
    size_t len_index = orig.size();
    orig.push_back(18); // length=18
    orig.push_back(1); // vendor_id=0x1020304
    orig.push_back(2);
    orig.push_back(3);
    orig.push_back(4);
    orig.push_back(1); // suboption type=0x101
    orig.push_back(1); 
    orig.push_back(0); // suboption length=3
    orig.push_back(3);
    orig.push_back(102); // data="foo"
    orig.push_back(111);
    orig.push_back(111);
    orig.push_back(1); // suboption type=0x102
    orig.push_back(2);
    orig.push_back(0); // suboption length=3
    orig.push_back(3);
    orig.push_back(99); // data="bar'
    orig.push_back(98);
    orig.push_back(114);

    Pkt6Ptr success(new Pkt6(&orig[0], orig.size()));
    EXPECT_NO_THROW(success->unpack());

    // Truncated vendor option is not accepted but doesn't throw
    vector<uint8_t> shortv = orig;
    shortv[len_index] = 20;
    Pkt6Ptr too_short_vendor_pkt(new Pkt6(&shortv[0], shortv.size()));
    EXPECT_NO_THROW(too_short_vendor_pkt->unpack());
    
    // Truncated option header is not accepted
    vector<uint8_t> shorth = orig;
    shorth.resize(orig.size() - 4);
    shorth[len_index] = 12;
    Pkt6Ptr too_short_header_pkt(new Pkt6(&shorth[0], shorth.size()));
    EXPECT_THROW(too_short_header_pkt->unpack(), OutOfRange);

    // Truncated option data is not accepted
    vector<uint8_t> shorto = orig;
    shorto.resize(orig.size() - 2);
    shorto[len_index] = 16;
    Pkt6Ptr too_short_option_pkt(new Pkt6(&shorto[0], shorto.size()));
    EXPECT_THROW(too_short_option_pkt->unpack(), OutOfRange);
}

// This test verifies that it is possible to specify custom implementation of
// the option parsing algorithm by installing a callback function.
TEST_F(Pkt6Test, packUnpackWithCallback) {
    // Create an on-wire representation of the test packet and clone it.
    Pkt6Ptr pkt(new Pkt6(DHCPV6_SOLICIT, 0x020304));
    Pkt6Ptr clone = packAndClone(pkt);

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
    ASSERT_NO_THROW(clone->unpack());

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
    ASSERT_NO_THROW(clone->unpack());
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
    for (unsigned itype = 0; itype < 256; ++itype) {
        uint8_t type = itype;

        switch (type) {
        case DHCPV6_ADVERTISE:
            EXPECT_STREQ("ADVERTISE", Pkt6::getName(type));
            break;

        case DHCPV6_CONFIRM:
            EXPECT_STREQ("CONFIRM", Pkt6::getName(type));
            break;

        case DHCPV6_DECLINE:
            EXPECT_STREQ("DECLINE", Pkt6::getName(type));
            break;

        case DHCPV6_DHCPV4_QUERY:
            EXPECT_STREQ("DHCPV4_QUERY", Pkt6::getName(type));
            break;

        case DHCPV6_DHCPV4_RESPONSE:
            EXPECT_STREQ("DHCPV4_RESPONSE", Pkt6::getName(type));
            break;

        case DHCPV6_INFORMATION_REQUEST:
            EXPECT_STREQ("INFORMATION_REQUEST",
                         Pkt6::getName(type));
            break;

        case DHCPV6_LEASEQUERY:
            EXPECT_STREQ("LEASEQUERY", Pkt6::getName(type));
            break;

        case DHCPV6_LEASEQUERY_REPLY:
            EXPECT_STREQ("LEASEQUERY_REPLY", Pkt6::getName(type));
            break;

        case DHCPV6_REBIND:
            EXPECT_STREQ("REBIND", Pkt6::getName(type));
            break;

        case DHCPV6_RECONFIGURE:
            EXPECT_STREQ("RECONFIGURE", Pkt6::getName(type));
            break;

        case DHCPV6_RELAY_FORW:
            EXPECT_STREQ("RELAY_FORWARD", Pkt6::getName(type));
            break;

        case DHCPV6_RELAY_REPL:
            EXPECT_STREQ("RELAY_REPLY", Pkt6::getName(type));
            break;

        case DHCPV6_RELEASE:
            EXPECT_STREQ("RELEASE", Pkt6::getName(type));
            break;

        case DHCPV6_RENEW:
            EXPECT_STREQ("RENEW", Pkt6::getName(type));
            break;

        case DHCPV6_REPLY:
            EXPECT_STREQ("REPLY", Pkt6::getName(type));
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

    uint8_t expected_remote_id[] = { 0x00, 0x01, 0x00, 0x01, 0x18, 0xb0,
                                     0x33, 0x41, 0x00, 0x00, 0x21, 0x5c,
                                     0x18, 0xa9 };
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
    uint8_t expected_client_id[] = { 0x00, 0x01, 0x00, 0x01, 0x18, 0xb0,
                                     0x33, 0x41, 0x00, 0x00, 0x21, 0x5c,
                                     0x18, 0xa9 };
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

    EXPECT_EQ(Pkt6::DHCPV6_PKT_HDR_LEN
              + 3 * Option::OPTION6_HDR_LEN // ADVERTISE
              + Pkt6::DHCPV6_RELAY_HDR_LEN // Relay header
              + Option::OPTION6_HDR_LEN // Relay-msg
              + optRelay1->len(),
              parent->len());

    // Create second packet,based on assembled data from the first one
    scoped_ptr<Pkt6> clone(new Pkt6(static_cast<const uint8_t*>(
                                    parent->getBuffer().getData()),
                                    parent->getBuffer().getLength()));

    // Now recreate options list
    EXPECT_NO_THROW( clone->unpack() );

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
    EXPECT_EQ(0, memcmp(&data[0], relay_opt_data, sizeof(relay_opt_data)));
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
    OptionPtr relay2_opt4(new Option(Option::V6, 200));
    // the same code as relay1_opt3
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
    OptionPtr opt =
        msg->getAnyRelayOption(300, Pkt6::RELAY_SEARCH_FROM_CLIENT);
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
    EXPECT_TRUE(opt->equals(relay3_opt1));

    // We want to ge that one inserted by relay1 (first match, starting from
    // closest to the server.
    opt = msg->getAnyRelayOption(200, Pkt6::RELAY_SEARCH_FROM_SERVER);
    ASSERT_TRUE(opt);
    EXPECT_TRUE(opt->equals(relay1_opt1));

    // We just want option from the first relay (closest to the client)
    opt = msg->getAnyRelayOption(200, Pkt6::RELAY_GET_FIRST);
    ASSERT_TRUE(opt);
    EXPECT_TRUE(opt->equals(relay3_opt1));

    // We just want option from the last relay (closest to the server)
    opt = msg->getAnyRelayOption(200, Pkt6::RELAY_GET_LAST);
    ASSERT_TRUE(opt);
    EXPECT_TRUE(opt->equals(relay1_opt1));

    // Let's try to ask for something that is inserted by the middle relay
    // only.
    opt = msg->getAnyRelayOption(100, Pkt6::RELAY_SEARCH_FROM_SERVER);
    ASSERT_TRUE(opt);
    EXPECT_TRUE(opt->equals(relay2_opt1));

    opt = msg->getAnyRelayOption(100, Pkt6::RELAY_SEARCH_FROM_CLIENT);
    ASSERT_TRUE(opt);
    EXPECT_TRUE(opt->equals(relay2_opt1));

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
    EXPECT_FALSE(pkt.inClass(DOCSIS3_CLASS_EROUTER));
    EXPECT_FALSE(pkt.inClass(DOCSIS3_CLASS_MODEM));
    EXPECT_TRUE(pkt.classes_.empty());

    // Add to the first class
    pkt.addClass(DOCSIS3_CLASS_EROUTER);
    EXPECT_TRUE(pkt.inClass(DOCSIS3_CLASS_EROUTER));
    EXPECT_FALSE(pkt.inClass(DOCSIS3_CLASS_MODEM));
    ASSERT_FALSE(pkt.classes_.empty());

    // Add to a second class
    pkt.addClass(DOCSIS3_CLASS_MODEM);
    EXPECT_TRUE(pkt.inClass(DOCSIS3_CLASS_EROUTER));
    EXPECT_TRUE(pkt.inClass(DOCSIS3_CLASS_MODEM));

    // Check that it's ok to add to the same class repeatedly
    EXPECT_NO_THROW(pkt.addClass("foo"));
    EXPECT_NO_THROW(pkt.addClass("foo"));
    EXPECT_NO_THROW(pkt.addClass("foo"));

    // Check that the packet belongs to 'foo'
    EXPECT_TRUE(pkt.inClass("foo"));
}

// Tests whether MAC can be obtained and that MAC sources are not
// confused.
TEST_F(Pkt6Test, getMAC) {
    Pkt6 pkt(DHCPV6_ADVERTISE, 1234);

    // DHCPv6 packet by default doens't have MAC address specified.
    EXPECT_FALSE(pkt.getMAC(HWAddr::HWADDR_SOURCE_ANY));
    EXPECT_FALSE(pkt.getMAC(HWAddr::HWADDR_SOURCE_RAW));

    // We haven't specified source IPv6 address, so this method should
    // fail, too
    EXPECT_FALSE(pkt.getMAC(HWAddr::HWADDR_SOURCE_IPV6_LINK_LOCAL));

    // Let's check if setting IPv6 address improves the situation.
    IOAddress linklocal_eui64("fe80::204:06ff:fe08:0a0c");
    pkt.setRemoteAddr(linklocal_eui64);
    EXPECT_TRUE(pkt.getMAC(HWAddr::HWADDR_SOURCE_ANY));
    EXPECT_TRUE(pkt.getMAC(HWAddr::HWADDR_SOURCE_IPV6_LINK_LOCAL));
    EXPECT_TRUE(pkt.getMAC(HWAddr::HWADDR_SOURCE_IPV6_LINK_LOCAL |
                           HWAddr::HWADDR_SOURCE_RAW));
    pkt.setRemoteAddr(IOAddress("::"));

    // Let's invent a MAC
    const uint8_t hw[] = { 2, 4, 6, 8, 10, 12 }; // MAC
    const uint8_t hw_type = 123; // hardware type
    HWAddrPtr dummy_hwaddr(new HWAddr(hw, sizeof(hw), hw_type));

    // Now let's pretend that we obtained it from raw sockets
    pkt.setRemoteHWAddr(dummy_hwaddr);

    // Now we should be able to get something
    ASSERT_TRUE(pkt.getMAC(HWAddr::HWADDR_SOURCE_ANY));
    ASSERT_TRUE(pkt.getMAC(HWAddr::HWADDR_SOURCE_RAW));
    EXPECT_TRUE(pkt.getMAC(HWAddr::HWADDR_SOURCE_IPV6_LINK_LOCAL |
                           HWAddr::HWADDR_SOURCE_RAW));

    // Check that the returned MAC is indeed the expected one
    ASSERT_TRUE(*dummy_hwaddr == *pkt.getMAC(HWAddr::HWADDR_SOURCE_ANY));
    ASSERT_TRUE(*dummy_hwaddr == *pkt.getMAC(HWAddr::HWADDR_SOURCE_RAW));
}

// Test checks whether getMACFromIPv6LinkLocal() returns the hardware (MAC)
// address properly (for direct message).
TEST_F(Pkt6Test, getMACFromIPv6LinkLocal_direct) {
    Pkt6 pkt(DHCPV6_ADVERTISE, 1234);

    // Let's get the first interface
    IfacePtr iface = IfaceMgr::instance().getIface(1);
    ASSERT_TRUE(iface);

    // and set source interface data properly. getMACFromIPv6LinkLocal attempts
    // to use source interface to obtain hardware type
    pkt.setIface(iface->getName());
    pkt.setIndex(iface->getIndex());

    // Note that u and g bits (the least significant ones of the most
    // significant byte) have special meaning and must not be set in MAC.
    // u bit is always set in EUI-64. g is always cleared.
    IOAddress global("2001:db8::204:06ff:fe08:0a:0c");
    IOAddress linklocal_eui64("fe80::f204:06ff:fe08:0a0c");
    IOAddress linklocal_noneui64("fe80::f204:0608:0a0c:0e10");

    // If received from a global address, this method should fail
    pkt.setRemoteAddr(global);
    EXPECT_FALSE(pkt.getMAC(HWAddr::HWADDR_SOURCE_IPV6_LINK_LOCAL));

    // If received from link-local that is EUI-64 based, it should succeed
    pkt.setRemoteAddr(linklocal_eui64);
    HWAddrPtr found = pkt.getMAC(HWAddr::HWADDR_SOURCE_IPV6_LINK_LOCAL);
    ASSERT_TRUE(found);

    stringstream tmp;
    tmp << "hwtype=" << (int)iface->getHWType() << " f0:04:06:08:0a:0c";
    EXPECT_EQ(tmp.str(), found->toText(true));
}

// Test checks whether getMACFromIPv6LinkLocal() returns the hardware (MAC)
// address properly (for relayed message).
TEST_F(Pkt6Test, getMACFromIPv6LinkLocal_singleRelay) {

    // Let's create a Solicit first...
    Pkt6 pkt(DHCPV6_SOLICIT, 1234);

    // ... and pretend it was relayed by a single relay.
    Pkt6::RelayInfo info;
    pkt.addRelayInfo(info);
    ASSERT_EQ(1, pkt.relay_info_.size());

    // Let's get the first interface
    IfacePtr iface = IfaceMgr::instance().getIface(1);
    ASSERT_TRUE(iface);

    // and set source interface data properly. getMACFromIPv6LinkLocal attempts
    // to use source interface to obtain hardware type
    pkt.setIface(iface->getName());
    pkt.setIndex(iface->getIndex());

    IOAddress global("2001:db8::204:06ff:fe08:0a:0c"); // global address
    IOAddress linklocal_noneui64("fe80::f204:0608:0a0c:0e10"); // no fffe
    IOAddress linklocal_eui64("fe80::f204:06ff:fe08:0a0c"); // valid EUI-64

    // If received from a global address, this method should fail
    pkt.relay_info_[0].peeraddr_ = global;
    EXPECT_FALSE(pkt.getMAC(HWAddr::HWADDR_SOURCE_IPV6_LINK_LOCAL));

    // If received from a link-local that does not use EUI-64, it should fail
    pkt.relay_info_[0].peeraddr_ = linklocal_noneui64;
    EXPECT_FALSE(pkt.getMAC(HWAddr::HWADDR_SOURCE_IPV6_LINK_LOCAL));

    // If received from link-local that is EUI-64 based, it should succeed
    pkt.relay_info_[0].peeraddr_ = linklocal_eui64;
    HWAddrPtr found = pkt.getMAC(HWAddr::HWADDR_SOURCE_IPV6_LINK_LOCAL);
    ASSERT_TRUE(found);

    stringstream tmp;
    tmp << "hwtype=" << (int)iface->getHWType() << " f0:04:06:08:0a:0c";
    EXPECT_EQ(tmp.str(), found->toText(true));
}

// Test checks whether getMACFromIPv6LinkLocal() returns the hardware (MAC)
// address properly (for a message relayed multiple times).
TEST_F(Pkt6Test, getMACFromIPv6LinkLocal_multiRelay) {

    // Let's create a Solicit first...
    Pkt6 pkt(DHCPV6_SOLICIT, 1234);

    // ... and pretend it was relayed via 3 relays. Keep in mind that
    // the relays are stored in relay_info_ in the encapsulation order
    // rather than in traverse order. The following simulates:
    // client --- relay1 --- relay2 --- relay3 --- server
    IOAddress linklocal1("fe80::200:ff:fe00:1"); // valid EUI-64
    IOAddress linklocal2("fe80::200:ff:fe00:2"); // valid EUI-64
    IOAddress linklocal3("fe80::200:ff:fe00:3"); // valid EUI-64

    // Let's add info about relay3. This was the last relay, so it added the
    // outermost encapsulation layer, so it was parsed first during reception.
    // Its peer-addr field contains an address of relay2, so it's useless for
    // this method.
    Pkt6::RelayInfo info;
    info.peeraddr_ = linklocal3;
    pkt.addRelayInfo(info);

    // Now add info about relay2. Its peer-addr contains an address of the
    // previous relay (relay1). Still useless for us.
    info.peeraddr_ = linklocal2;
    pkt.addRelayInfo(info);

    // Finally add the first relay. This is the relay that received the packet
    // from the client directly, so its peer-addr field contains an address of
    // the client. The method should get that address and build MAC from it.
    info.peeraddr_ = linklocal1;
    pkt.addRelayInfo(info);
    ASSERT_EQ(3, pkt.relay_info_.size());

    // Let's get the first interface
    IfacePtr iface = IfaceMgr::instance().getIface(1);
    ASSERT_TRUE(iface);

    // and set source interface data properly. getMACFromIPv6LinkLocal attempts
    // to use source interface to obtain hardware type
    pkt.setIface(iface->getName());
    pkt.setIndex(iface->getIndex());

    // The method should return MAC based on the first relay that was closest
    HWAddrPtr found = pkt.getMAC(HWAddr::HWADDR_SOURCE_IPV6_LINK_LOCAL);
    ASSERT_TRUE(found);

    // Let's check the info now.
    stringstream tmp;
    tmp << "hwtype=" << iface->getHWType() << " 00:00:00:00:00:01";
    EXPECT_EQ(tmp.str(), found->toText(true));
}

// Test checks whether getMACFromIPv6RelayOpt() returns the hardware (MAC)
// address properly from a single relayed message.
TEST_F(Pkt6Test, getMACFromIPv6RelayOpt_singleRelay) {

    // Let's create a Solicit first...
    Pkt6 pkt(DHCPV6_SOLICIT, 1234);

    // Packets that are not relayed should fail
    EXPECT_FALSE(pkt.getMAC(HWAddr::HWADDR_SOURCE_CLIENT_ADDR_RELAY_OPTION));

    // Now pretend it was relayed by a single relay.
    Pkt6::RelayInfo info;

    // generate options with code 79 and client link layer address
    const uint8_t opt_data[] = {
        0x00, 0x01,  // Ethertype
        0x0a, 0x1b, 0x0b, 0x01, 0xca, 0xfe // MAC
    };
    OptionPtr relay_opt(new Option(Option::V6, 79,
                            OptionBuffer(opt_data, opt_data + sizeof(opt_data))));
    info.options_.insert(make_pair(relay_opt->getType(), relay_opt));

    pkt.addRelayInfo(info);
    ASSERT_EQ(1, pkt.relay_info_.size());

    HWAddrPtr found = pkt.getMAC(HWAddr::HWADDR_SOURCE_CLIENT_ADDR_RELAY_OPTION);
    ASSERT_TRUE(found);

    stringstream tmp;
    tmp << "hwtype=1 0a:1b:0b:01:ca:fe";
    EXPECT_EQ(tmp.str(), found->toText(true));
}

// Test checks whether getMACFromIPv6RelayOpt() returns the hardware (MAC)
// address properly from a message relayed by multiple servers.
TEST_F(Pkt6Test, getMACFromIPv6RelayOpt_multipleRelay) {

    // Let's create a Solicit first...
    Pkt6 pkt(DHCPV6_SOLICIT, 1234);

    // Now pretend it was relayed two times. The relay closest to the server
    // adds link-layer-address information against the RFC, the process fails.
    Pkt6::RelayInfo info1;
    uint8_t opt_data[] = {
        0x00, 0x01,  // Ethertype
        0x1a, 0x30, 0x0b, 0xfa, 0xc0, 0xfe // MAC
    };
    OptionPtr relay_opt1(new Option(Option::V6, D6O_CLIENT_LINKLAYER_ADDR,
                            OptionBuffer(opt_data, opt_data + sizeof(opt_data))));

    info1.options_.insert(make_pair(relay_opt1->getType(), relay_opt1));
    pkt.addRelayInfo(info1);

    // Second relay, closest to the client has not implemented RFC6939
    Pkt6::RelayInfo info2;
    pkt.addRelayInfo(info2);
    ASSERT_EQ(2, pkt.relay_info_.size());

    EXPECT_FALSE(pkt.getMAC(HWAddr::HWADDR_SOURCE_CLIENT_ADDR_RELAY_OPTION));

    // Let's envolve the packet with a third relay (now the closest to the client)
    // that inserts the correct client_linklayer_addr option.
    Pkt6::RelayInfo info3;

    // We reuse the option and modify the MAC to be sure we get the right address
    opt_data[2] = 0xfa;
    OptionPtr relay_opt3(new Option(Option::V6, D6O_CLIENT_LINKLAYER_ADDR,
                            OptionBuffer(opt_data, opt_data + sizeof(opt_data))));
    info3.options_.insert(make_pair(relay_opt3->getType(), relay_opt3));
    pkt.addRelayInfo(info3);
    ASSERT_EQ(3, pkt.relay_info_.size());

    // Now extract the MAC address from the relayed option
    HWAddrPtr found = pkt.getMAC(HWAddr::HWADDR_SOURCE_CLIENT_ADDR_RELAY_OPTION);
    ASSERT_TRUE(found);

    stringstream tmp;
    tmp << "hwtype=1 fa:30:0b:fa:c0:fe";
    EXPECT_EQ(tmp.str(), found->toText(true));
}

TEST_F(Pkt6Test, getMACFromDUID) {
    Pkt6 pkt(DHCPV6_ADVERTISE, 1234);

    // Although MACs are typically 6 bytes long, let's make this test a bit
    // more challenging and use odd MAC lengths.

    uint8_t duid_llt[] = { 0, 1, // type (DUID-LLT)
                           0, 7, // hwtype (7 - just a randomly picked value)
                           1, 2, 3, 4, // timestamp
                           0xa, 0xb, 0xc, 0xd, 0xe, 0xf, 0x10 // MAC address (7 bytes)
    };

    uint8_t duid_ll[] = { 0, 3, // type (DUID-LL)
                        0, 11, // hwtype (11 - just a randomly picked value)
                        0xa, 0xb, 0xc, 0xd, 0xe // MAC address (5 bytes)
    };

    uint8_t duid_en[] = { 0, 2, // type (DUID-EN)
                        1, 2, 3, 4, // enterprise-id
                        0xa, 0xb, 0xc // opaque data
    };

    OptionPtr clientid1(new Option(Option::V6, D6O_CLIENTID, OptionBuffer(
                                       duid_llt, duid_llt + sizeof(duid_llt))));
    OptionPtr clientid2(new Option(Option::V6, D6O_CLIENTID, OptionBuffer(
                                       duid_ll, duid_ll + sizeof(duid_ll))));
    OptionPtr clientid3(new Option(Option::V6, D6O_CLIENTID, OptionBuffer(
                                       duid_en, duid_en + sizeof(duid_en))));

    // Packet does not have any client-id, this call should fail
    EXPECT_FALSE(pkt.getMAC(HWAddr::HWADDR_SOURCE_DUID));

    // Let's test DUID-LLT. This should work.
    pkt.addOption(clientid1);
    HWAddrPtr mac = pkt.getMAC(HWAddr::HWADDR_SOURCE_DUID);
    ASSERT_TRUE(mac);
    EXPECT_EQ("hwtype=7 0a:0b:0c:0d:0e:0f:10", mac->toText(true));

    // Let's test DUID-LL. This should work.
    ASSERT_TRUE(pkt.delOption(D6O_CLIENTID));
    pkt.addOption(clientid2);
    mac = pkt.getMAC(HWAddr::HWADDR_SOURCE_DUID);
    ASSERT_TRUE(mac);
    EXPECT_EQ("hwtype=11 0a:0b:0c:0d:0e", mac->toText(true));

    // Finally, let's try DUID-EN. This should fail, as EN type does not
    // contain any MAC address information.
    ASSERT_TRUE(pkt.delOption(D6O_CLIENTID));
    pkt.addOption(clientid3);
    EXPECT_FALSE(pkt.getMAC(HWAddr::HWADDR_SOURCE_DUID));
}

// Test checks whether getMAC(DOCSIS_MODEM) is working properly.
// We only have a small number of actual traffic captures from
// cable networks, so the scope of unit-tests is somewhat limited.
TEST_F(Pkt6Test, getMAC_DOCSIS_Modem) {

    // Let's use a captured traffic. The one we have comes from a
    // modem with MAC address 10:0d:7f:00:07:88.
    Pkt6Ptr pkt = PktCaptures::captureDocsisRelayedSolicit();
    ASSERT_NO_THROW(pkt->unpack());

    // The method should return MAC based on the vendor-specific info,
    // suboption 36, which is inserted by the modem itself.
    HWAddrPtr found = pkt->getMAC(HWAddr::HWADDR_SOURCE_DOCSIS_MODEM);
    ASSERT_TRUE(found);

    // Let's check the info.
    EXPECT_EQ("hwtype=1 10:0d:7f:00:07:88", found->toText(true));

    // Now let's remove the option
    OptionVendorPtr vendor = boost::dynamic_pointer_cast<
        OptionVendor>(pkt->getOption(D6O_VENDOR_OPTS));
    ASSERT_TRUE(vendor);
    ASSERT_TRUE(vendor->delOption(DOCSIS3_V6_DEVICE_ID));

    // Ok, there's no more suboption 36. Now getMAC() should fail.
    EXPECT_FALSE(pkt->getMAC(HWAddr::HWADDR_SOURCE_DOCSIS_MODEM));
}

// Test checks whether getMAC(DOCSIS_CMTS) is working properly.
// We only have a small number of actual traffic captures from
// cable networks, so the scope of unit-tests is somewhat limited.
TEST_F(Pkt6Test, getMAC_DOCSIS_CMTS) {

    // Let's use a captured traffic. The one we have comes from a
    // modem with MAC address 20:e5:2a:b8:15:14.
    Pkt6Ptr pkt = PktCaptures::captureeRouterRelayedSolicit();
    ASSERT_NO_THROW(pkt->unpack());

    // The method should return MAC based on the vendor-specific info,
    // suboption 36, which is inserted by the modem itself.
    HWAddrPtr found = pkt->getMAC(HWAddr::HWADDR_SOURCE_DOCSIS_CMTS);
    ASSERT_TRUE(found);

    // Let's check the info.
    EXPECT_EQ("hwtype=1 20:e5:2a:b8:15:14", found->toText(true));

    // Now let's remove the suboption 1026 that is inserted by the
    // relay.
    OptionVendorPtr vendor = boost::dynamic_pointer_cast<
        OptionVendor>(pkt->getAnyRelayOption(D6O_VENDOR_OPTS,
                          isc::dhcp::Pkt6::RELAY_SEARCH_FROM_CLIENT));
    ASSERT_TRUE(vendor);
    EXPECT_TRUE(vendor->delOption(DOCSIS3_V6_CMTS_CM_MAC));

    EXPECT_FALSE(pkt->getMAC(HWAddr::HWADDR_SOURCE_DOCSIS_CMTS));
}

// Test checks whether getMACFromRemoteIdRelayOption() returns the hardware (MAC)
// address properly from a relayed message.
TEST_F(Pkt6Test, getMACFromRemoteIdRelayOption) {

    // Create a solicit message.
    Pkt6 pkt(DHCPV6_SOLICIT, 1234);

    // This should fail as the message is't relayed yet.
    EXPECT_FALSE(pkt.getMAC(HWAddr::HWADDR_SOURCE_REMOTE_ID));

    // Let's get the first interface
    IfacePtr iface = IfaceMgr::instance().getIface(1);
    ASSERT_TRUE(iface);

    // and set source interface data properly. getMACFromIPv6LinkLocal attempts
    // to use source interface to obtain hardware type
    pkt.setIface(iface->getName());
    pkt.setIndex(iface->getIndex());

    // Generate option data with randomly picked enterprise number and MAC address
    const uint8_t opt_data[] = {
        1, 2, 3, 4,  // enterprise-number
        0xa, 0xb, 0xc, 0xd, 0xe, 0xf // MAC
    };

    // Create option with number 37 (remote-id relay agent option)
    OptionPtr relay_opt(new Option(Option::V6, D6O_REMOTE_ID,
                        OptionBuffer(opt_data, opt_data + sizeof(opt_data))));

    // First simulate relaying message without adding remote-id option
    Pkt6::RelayInfo info;
    pkt.addRelayInfo(info);
    ASSERT_EQ(1, pkt.relay_info_.size());

    // This should fail as the remote-id option isn't there
    EXPECT_FALSE(pkt.getMAC(HWAddr::HWADDR_SOURCE_REMOTE_ID));

    // Now add this option to the relayed message
    info.options_.insert(make_pair(relay_opt->getType(), relay_opt));
    pkt.addRelayInfo(info);
    ASSERT_EQ(2, pkt.relay_info_.size());

    // This should work now
    HWAddrPtr mac = pkt.getMAC(HWAddr::HWADDR_SOURCE_REMOTE_ID);
    ASSERT_TRUE(mac);

    stringstream tmp;
    tmp << "hwtype=" << (int)iface->getHWType() << " 0a:0b:0c:0d:0e:0f";

    EXPECT_EQ(tmp.str(), mac->toText(true));
}

// This test verifies that a solicit that passed through two relays is parsed
// properly. In particular the second relay (outer encapsulation) included RSOO
// (Relay Supplied Options option). This test checks whether it was parsed
// properly. See captureRelayed2xRSOO() description for details.
TEST_F(Pkt6Test, rsoo) {
    Pkt6Ptr msg = test::PktCaptures::captureRelayed2xRSOO();

    EXPECT_NO_THROW(msg->unpack());

    EXPECT_EQ(DHCPV6_SOLICIT, msg->getType());
    EXPECT_EQ(217, msg->len());

    ASSERT_EQ(2, msg->relay_info_.size());

    // There should be an RSOO option in the outermost relay
    OptionPtr opt = msg->getRelayOption(D6O_RSOO, 1);
    ASSERT_TRUE(opt);

    EXPECT_EQ(D6O_RSOO, opt->getType());
    const OptionCollection& rsoo = opt->getOptions();
    ASSERT_EQ(2, rsoo.size());

    OptionPtr rsoo1 = opt->getOption(255);
    OptionPtr rsoo2 = opt->getOption(256);

    ASSERT_TRUE(rsoo1);
    ASSERT_TRUE(rsoo2);

    EXPECT_EQ(8, rsoo1->len()); // 4 bytes of data + header
    EXPECT_EQ(13, rsoo2->len()); // 9 bytes of data + header

}

// Verify that the DUID can be extracted from the DHCPv6 packet
// holding Client Identifier option.
TEST_F(Pkt6Test, getClientId) {
    // Create a packet.
    Pkt6Ptr pkt(new Pkt6(DHCPV6_SOLICIT, 0x2312));
    // Initially, the packet should hold no DUID.
    EXPECT_FALSE(pkt->getClientId());

    // Create DUID and add it to the packet.
    const uint8_t duid_data[] = { 1, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 0 };
    OptionBuffer duid_vec(duid_data, duid_data + sizeof(duid_data) - 1);
    pkt->addOption(OptionPtr(new Option(Option::V6, D6O_CLIENTID,
                                        duid_vec.begin(),
                                        duid_vec.end())));

    // Simulate the packet transmission over the wire, i.e. create on
    // wire representation of the packet, and then parse it.
    Pkt6Ptr pkt_clone = packAndClone(pkt);
    ASSERT_NO_THROW(pkt_clone->unpack());

    // This time the DUID should be returned.
    DuidPtr duid = pkt_clone->getClientId();
    ASSERT_TRUE(duid);

    // And it should be equal to the one that we used to create
    // the packet.
    EXPECT_TRUE(duid->getDuid() == duid_vec);
}

// This test verfies that it is possible to obtain the packet
// identifiers (DUID, HW Address, transaction id) in the textual
// format.
TEST_F(Pkt6Test, makeLabel) {
    DuidPtr duid(new DUID(DUID::fromText("0102020202030303030303")));
    HWAddrPtr hwaddr(new HWAddr(HWAddr::fromText("01:02:03:04:05:06",
                                                 HTYPE_ETHER)));

    // Specify DUID and no HW Address.
    EXPECT_EQ("duid=[01:02:02:02:02:03:03:03:03:03:03], tid=0x123",
              Pkt6::makeLabel(duid, 0x123, HWAddrPtr()));

    // Specify HW Address and no DUID.
    EXPECT_EQ("duid=[no info], [hwtype=1 01:02:03:04:05:06], tid=0x123",
              Pkt6::makeLabel(DuidPtr(), 0x123, hwaddr));

    // Specify both DUID and HW Address.
    EXPECT_EQ("duid=[01:02:02:02:02:03:03:03:03:03:03], "
              "[hwtype=1 01:02:03:04:05:06], tid=0x123",
              Pkt6::makeLabel(duid, 0x123, hwaddr));

    // Specify neither DUID nor HW Address.
    EXPECT_EQ("duid=[no info], tid=0x0",
              Pkt6::makeLabel(DuidPtr(), 0x0, HWAddrPtr()));
}

// Tests that the variant of makeLabel which doesn't include transaction
// id produces expected output.
TEST_F(Pkt6Test, makeLabelWithoutTransactionId) {
    DuidPtr duid(new DUID(DUID::fromText("0102020202030303030303")));
    HWAddrPtr hwaddr(new HWAddr(HWAddr::fromText("01:02:03:04:05:06",
                                                 HTYPE_ETHER)));

    // Specify DUID and no HW Address.
    EXPECT_EQ("duid=[01:02:02:02:02:03:03:03:03:03:03]",
              Pkt6::makeLabel(duid, HWAddrPtr()));

    // Specify HW Address and no DUID.
    EXPECT_EQ("duid=[no info], [hwtype=1 01:02:03:04:05:06]",
              Pkt6::makeLabel(DuidPtr(), hwaddr));

    // Specify both DUID and HW Address.
    EXPECT_EQ("duid=[01:02:02:02:02:03:03:03:03:03:03], "
              "[hwtype=1 01:02:03:04:05:06]",
              Pkt6::makeLabel(duid, hwaddr));

    // Specify neither DUID nor HW Address.
    EXPECT_EQ("duid=[no info]", Pkt6::makeLabel(DuidPtr(), HWAddrPtr()));
}

// This test verifies that it is possible to obtain the packet
// identifiers in the textual format from the packet instance.
TEST_F(Pkt6Test, getLabel) {
    // Create a packet.
    Pkt6Ptr pkt(new Pkt6(DHCPV6_SOLICIT, 0x2312));
    EXPECT_EQ("duid=[no info], tid=0x2312",
              pkt->getLabel());

    DuidPtr duid(new DUID(DUID::fromText("0102020202030303030303")));
    pkt->addOption(OptionPtr(new Option(Option::V6, D6O_CLIENTID,
                                        duid->getDuid().begin(),
                                        duid->getDuid().end())));

    // Simulate the packet transmission over the wire, i.e. create on
    // wire representation of the packet, and then parse it.
    Pkt6Ptr pkt_clone = packAndClone(pkt);
    ASSERT_NO_THROW(pkt_clone->unpack());

    EXPECT_EQ("duid=[01:02:02:02:02:03:03:03:03:03:03], tid=0x2312",
              pkt_clone->getLabel());

}

// Test that empty client identifier option doesn't cause an exception from
// Pkt6::getLabel.
TEST_F(Pkt6Test, getLabelEmptyClientId) {
    // Create a packet.
    Pkt6 pkt(DHCPV6_SOLICIT, 0x2312);

    // Add empty client idenitifier option.
    pkt.addOption(OptionPtr(new Option(Option::V6, D6O_CLIENTID)));
    EXPECT_EQ("duid=[no info], tid=0x2312", pkt.getLabel());
}

}
