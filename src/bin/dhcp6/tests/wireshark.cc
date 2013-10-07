// Copyright (C) 2013  Internet Systems Consortium, Inc. ("ISC")
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
#include <dhcp6/tests/dhcp6_test_utils.h>
#include <string>

/// @file   wireshark.cc
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

using namespace std;

namespace isc {
namespace test {

void Dhcpv6SrvTest::captureSetDefaultFields(const Pkt6Ptr& pkt) {
    pkt->setRemotePort(546);
    pkt->setRemoteAddr(IOAddress("fe80::1"));
    pkt->setLocalPort(0);
    pkt->setLocalAddr(IOAddress("ff02::1:2"));
    pkt->setIndex(2);
    pkt->setIface("eth0");
}

// This function returns buffer for very simple Solicit
Pkt6Ptr Dhcpv6SrvTest::captureSimpleSolicit() {
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

Pkt6Ptr Dhcpv6SrvTest::captureRelayedSolicit() {

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
Pkt6Ptr isc::test::Dhcpv6SrvTest::captureDocsisRelayedSolicit() {

    // This is an actual DOCSIS packet
    // RELAY-FORW (12) 
    //  - Relay Message
    //    - SOLICIT (1)
    //      - client-id
    //      - IA_NA (iaid=7f000788, t2=0, t2=0)
    //        - IAAddress (::, pref=0,valid=0)
    //      - rapid-commit
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

}; // end of isc::test namespace
}; // end of isc namespace
