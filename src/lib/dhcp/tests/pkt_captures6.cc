// Copyright (C) 2013-2015 Internet Systems Consortium, Inc. ("ISC")
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
#include <dhcp/pkt6.h>
#include <util/encode/hex.h>
#include <dhcp/tests/pkt_captures.h>
#include <string>

/// @file   pkt_captures6.cc
///
/// @brief  contains packet captures imported from Wireshark
///
/// These are actual packets captured over wire. They are used in various
/// tests.
///
/// The procedure to export Wireshark -> unit-tests is manual, but rather
/// easy to follow:
/// 1. Open a file in wireshark
/// 2. Find the packet you want to export
/// 3. There's a protocol stack (Frame, Ethernet, IPv6, UDP, DHCPv6, ...)
/// 4. Right click on DHCPv6 -> Copy -> Bytes -> Hex Stream
/// 5. Paste it as: string hex_string="[paste here]";
/// 6. Coding guidelines line restrictions apply, so wrap your code as necessary
/// 7. Make sure you decribe the capture appropriately
/// 8. Follow whatever rest of the methods are doing (set ports, ifaces etc.)
/// 9. To easily copy packet description, click File... -> Extract packet
///    dissections -> as plain text file...
///    (Make sure that the packet is expanded in the view. The text file will
///    contain whatever expansion level you have in the graphical tree.)

using namespace isc::dhcp;
using namespace isc::asiolink;
using namespace std;

namespace isc {
namespace test {

void PktCaptures::captureSetDefaultFields(const Pkt6Ptr& pkt) {
    pkt->setRemotePort(546);
    pkt->setRemoteAddr(IOAddress("fe80::1"));
    pkt->setLocalPort(0);
    pkt->setLocalAddr(IOAddress("ff02::1:2"));
    pkt->setIndex(2);
    pkt->setIface("eth0");
}

// This function returns buffer for very simple Solicit
Pkt6Ptr PktCaptures::captureSimpleSolicit() {
    uint8_t data[] = {
        1,  // type 1 = SOLICIT
        0xca, 0xfe, 0x01, // trans-id = 0xcafe01
        0, 1, // option type 1 (client-id)
        0, 10, // option lenth 10
        1, 2, 3, 4, 5, 6, 7, 8, 9, 10, // DUID
        0, 3, // option type 3 (IA_NA)
        0, 12, // option length 12
        0, 0, 0, 1, // iaid = 1
        0, 0, 0, 0, // T1 = 0
        0, 0, 0, 0  // T2 = 0
    };

    Pkt6Ptr pkt(new Pkt6(data, sizeof(data)));
    captureSetDefaultFields(pkt);

    return (pkt);
}

Pkt6Ptr PktCaptures::captureRelayedSolicit() {

    // This is a very simple relayed SOLICIT message:
    // RELAY-FORW
    // - interface-id
    // - relay-message
    //   - SOLICIT
    //     - client-id
    //     - IA_NA (iaid=1, t1=0, t2=0)
    //     - ORO (7)

    // string exported from Wireshark
    string hex_string =
        "0c0500000000000000000000000000000000fc00000000000000000000000000000900"
        "12000231350009002c010517100001000e0001000151b5e46208002758f1e80003000c"
        "000000010000000000000000000600020007";

    std::vector<uint8_t> bin;

    // Decode the hex string and store it in bin (which happens
    // to be OptionBuffer format)
    isc::util::encode::decodeHex(hex_string, bin);

    Pkt6Ptr pkt(new Pkt6(&bin[0], bin.size()));
    captureSetDefaultFields(pkt);

    return (pkt);
}

/// returns a buffer with relayed SOLICIT (from DOCSIS3.0 cable modem)
Pkt6Ptr isc::test::PktCaptures::captureDocsisRelayedSolicit() {

    // This is an actual DOCSIS packet
    // RELAY-FORW (12)
    //  - Relay Message
    //    - SOLICIT (1)
    //      - client-id
    //      - IA_NA (iaid=7f000788, t2=0, t2=0)
    //        - IAAddress (::, pref=0,valid=0)
    //      - rapid-commit
    //      - elapsed
    //      - ORO
    //      - Reconfigure-accept
    //      - Vendor-Class ("docsis3.0")
    //      - Vendor-specific Info
    //        - subopt 1: Option request = 32,33,34,37,38
    //        - subopt 36: Device identifier
    //        - subopt 35: TLV5
    //        - subopt 2: Device type = ECM
    //        - subopt 3: Embedded components
    //        - subopt 4: Serial Number
    //        - subopt 5: Hardware version
    //        - subopt 6: Software version
    //        - subopt 7: Boot ROM Version
    //        - subopt 8: Organization Unique Identifier
    //        - subopt 9: Model Number
    //        - subopt 10: Vendor Name (Netgear)
    //        - subopt 15: unknown
    //  - Interface-Id
    //  - Vendor-specific Information
    //    - Suboption 1025: CMTS capabilities
    //    - Suboption 1026: Cable Modem MAC addr = 10:0d:7f:00:07:88

    // string exported from Wireshark
    string hex_string =
        "0c002a0288fe00fe00015a8d09fffe7af955fe80000000000000120d7ffffe00078800"
        "090189010d397f0001000a00030001100d7f000788000300287f000788000000000000"
        "000000050018000000000000000000000000000000000000000000000000000e000000"
        "0800020000000600020011001400000010000f0000118b0009646f63736973332e3000"
        "1101200000118b0001000a0020002100220025002600240006100d7f00078800230081"
        "0101010201030301010401010501010601010701180801080901000a01010b01180c01"
        "010d0200400e0200100f01011004000000021101011301011401001501381601011701"
        "011801041901041a01041b01281c01021d01081e01201f011020011821010222010123"
        "010124011825010126020040270101120701100d7f00078a0002000345434d0003000b"
        "45434d3a45524f555445520004000d3335463132395550303030353200050004332e31"
        "310006000956312e30312e31315400070013505350552d426f6f7420312e302e31362e"
        "323200080006303030393542000900084347343030305444000a00074e657467656172"
        "000f000745524f5554455200120012427531264361312f3000100d7f00078800000011"
        "00160000118b040100040102030004020006100d7f000788";

    std::vector<uint8_t> bin;

    // Decode the hex string and store it in bin (which happens
    // to be OptionBuffer format)
    isc::util::encode::decodeHex(hex_string, bin);

    Pkt6Ptr pkt(new Pkt6(&bin[0], bin.size()));
    captureSetDefaultFields(pkt);
    return (pkt);
}

/// returns a buffer with relayed SOLICIT (from DOCSIS3.0 eRouter)
Pkt6Ptr isc::test::PktCaptures::captureeRouterRelayedSolicit() {

/* Packet description exported from wireshark:
DHCPv6
    Message type: Relay-forw (12)
    Hopcount: 0
    Link address: 2001:558:ffa8::1 (2001:558:ffa8::1)
    Peer address: fe80::22e5:2aff:feb8:1515 (fe80::22e5:2aff:feb8:1515)
    Relay Message
        Option: Relay Message (9)
        Length: 241
        Value: 01a90044000e000000140000000600080011001700180019...
        DHCPv6
            Message type: Solicit (1)
            Transaction ID: 0xa90044
            Rapid Commit
                Option: Rapid Commit (14)
                Length: 0
            Reconfigure Accept
                Option: Reconfigure Accept (20)
                Length: 0
            Option Request
                Option: Option Request (6)
                Length: 8
                Value: 0011001700180019
                Requested Option code: Vendor-specific Information (17)
                Requested Option code: DNS recursive name server (23)
                Requested Option code: Domain Search List (24)
                Requested Option code: Identity Association for Prefix Delegation (25)
            Vendor Class
                Option: Vendor Class (16)
                Length: 16
                Value: 0000118b000a65526f75746572312e30
                Enterprise ID: Cable Television Laboratories, Inc. (4491)
                vendor-class-data: eRouter1.0
            Vendor-specific Information
                Option: Vendor-specific Information (17)
                Length: 112
                Value: 0000118b0002000745524f555445520003000b45434d3a45...
                Enterprise ID: Cable Television Laboratories, Inc. (4491)
                Suboption: Device Type =  (2)"EROUTER"
                Suboption: Embedded Components =  (3)"ECM:EROUTER"
                Suboption: Serial Number =  (4)"2BR229U40044C"
                Suboption: Hardware Version =  (5)"1.04"
                Suboption: Software Version =  (6)"V1.33.03"
                Suboption: Boot ROM Version =  (7)"2.3.0R2"
                Suboption: Organization Unique Identifier =  (8)"00095B"
                Suboption: Model Number =  (9)"CG3000DCR"
                Suboption: Vendor Name =  (10)"Netgear"
            Client Identifier
                Option: Client Identifier (1)
                Length: 10
                Value: 0003000120e52ab81515
                DUID: 0003000120e52ab81515
                DUID Type: link-layer address (3)
                Hardware type: Ethernet (1)
                Link-layer address: 20:e5:2a:b8:15:15
            Identity Association for Prefix Delegation
                Option: Identity Association for Prefix Delegation (25)
                Length: 41
                Value: 2ab815150000000000000000001a00190000000000000000...
                IAID: 2ab81515
                T1: 0
                T2: 0
                IA Prefix
                    Option: IA Prefix (26)
                    Length: 25
                    Value: 000000000000000038000000000000000000000000000000...
                    Preferred lifetime: 0
                    Valid lifetime: 0
                    Prefix length: 56
                    Prefix address: :: (::)
            Identity Association for Non-temporary Address
                Option: Identity Association for Non-temporary Address (3)
                Length: 12
                Value: 2ab815150000000000000000
                IAID: 2ab81515
                T1: 0
                T2: 0
            Elapsed time
                Option: Elapsed time (8)
                Length: 2
                Value: 0000
                Elapsed time: 0 ms
    Vendor-specific Information
        Option: Vendor-specific Information (17)
        Length: 22
        Value: 0000118b0402000620e52ab815140401000401020300
        Enterprise ID: Cable Television Laboratories, Inc. (4491)
        Suboption: CM MAC Address Option =  (1026)20:e5:2a:b8:15:14
        Suboption: CMTS Capabilities Option :  (1025)
    Interface-Id
        Option: Interface-Id (18)
        Length: 4
        Value: 00000022
        Interface-ID:
    Remote Identifier
        Option: Remote Identifier (37)
        Length: 14
        Value: 0000101300015c228d4110000122
        Enterprise ID: Arris Interactive LLC (4115)
        Remote-ID: 00015c228d4110000122
    DHCP option 53
        Option: Unknown (53)
        Length: 10
        Value: 0003000100015c228d3d
        DUID: 0003000100015c228d3d
        DUID Type: link-layer address (3)
        Hardware type: Ethernet (1)
        Link-layer address: 00:01:5c:22:8d:3d */

    // string exported from Wireshark
    string hex_string =
        "0c0020010558ffa800000000000000000001fe8000000000000022e52afffeb8151500"
        "0900f101a90044000e000000140000000600080011001700180019001000100000118b"
        "000a65526f75746572312e30001100700000118b0002000745524f555445520003000b"
        "45434d3a45524f555445520004000d3242523232395534303034344300050004312e30"
        "340006000856312e33332e303300070007322e332e3052320008000630303039354200"
        "090009434733303030444352000a00074e6574676561720001000a0003000120e52ab8"
        "1515001900292ab815150000000000000000001a001900000000000000003800000000"
        "0000000000000000000000000003000c2ab81515000000000000000000080002000000"
        "1100160000118b0402000620e52ab81514040100040102030000120004000000220025"
        "000e0000101300015c228d41100001220035000a0003000100015c228d3d";

    std::vector<uint8_t> bin;

    // Decode the hex string and store it in bin (which happens
    // to be OptionBuffer format)
    isc::util::encode::decodeHex(hex_string, bin);

    Pkt6Ptr pkt(new Pkt6(&bin[0], bin.size()));
    captureSetDefaultFields(pkt);
    return (pkt);
}

Pkt6Ptr isc::test::PktCaptures::captureCableLabsShortVendorClass() {
    // This is a simple non-relayed Solicit:
    // - client-identifier
    // - IA_NA
    // - Vendor Class (4 bytes)
    //   - enterprise-id 4491
    // - Vendor-specific Information
    //   - enterprise-id 4491
    std::string hex_string =
        "01671cb90001000e0001000152ea903a08002758f1e80003000c00004bd10000000000"
        "000000001000040000118b0011000a0000118b000100020020";

    std::vector<uint8_t> bin;

    // Decode the hex string and store it in bin (which happens
    // to be OptionBuffer format)
    isc::util::encode::decodeHex(hex_string, bin);

    Pkt6Ptr pkt(new Pkt6(&bin[0], bin.size()));
    captureSetDefaultFields(pkt);
    return (pkt);

}

/// @brief creates doubly relayed solicit message
///
/// This is a traffic capture exported from wireshark and manually modified
/// to include necessary options (RSOO). It includes a SOLICIT message
/// that passed through two relays. It is especially interesting,
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
///          - rsoo (66)
///              - option 255 (len 4)
///              - option 256 (len 9)
///          - remote-id option (37)
///          - relay message option
///             - SOLICIT
///                  - client-id option
///                  - ia_na option
///                  - elapsed time
///                  - ORO
/// - interface-id option (18)
/// - remote-id option (37)
///
/// The original capture was posted to dibbler users mailing list.
///
/// @return created double relayed SOLICIT message
isc::dhcp::Pkt6Ptr isc::test::PktCaptures::captureRelayed2xRSOO() {

    // string exported from Wireshark
    string hex_string =
        "0c01200108880db800010000000000000000fe80000000000000020021fffe5c18a9"
        "0009007d0c0000000000000000000000000000000000fe80000000000000020021fffe5c18a9"
        "00420015" // RSOO (includes ...
        "00ff000401020304" // ... option 255, len 4, content 0x01020304
        "01000009010203040506070809" // ... option 256, len 9, content 0x010203040506070809
        "0025000400000de9" // remote-id
        "00090036" // relay-msg, len 54
        "016b4fe2" // solicit"
        "0001000e0001000118b033410000215c18a9" // client-id
        "0003000c00000001ffffffffffffffff" // ia-na
        "000800020000"
        "00060006001700f200f3"
        "0012001c4953414d3134347c3239397c697076367c6e743a76703a313a" // vendor-class
        "313130002500120000197f0001000118b033410000215c18a9";

    std::vector<uint8_t> bin;

    // Decode the hex string and store it in bin (which happens
    // to be OptionBuffer format)
    isc::util::encode::decodeHex(hex_string, bin);

    Pkt6Ptr pkt(new Pkt6(&bin[0], bin.size()));
    pkt->setRemotePort(547);
    pkt->setRemoteAddr(IOAddress("fe80::1234"));
    pkt->setLocalPort(547);
    pkt->setLocalAddr(IOAddress("ff05::1:3"));
    pkt->setIndex(2);
    pkt->setIface("eth0");
    return (pkt);
}


}; // end of isc::test namespace
}; // end of isc namespace
