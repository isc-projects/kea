// Copyright (C) 2013-2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <dhcp/tests/pkt_captures.h>
#include <string>
#include <asiolink/io_address.h>
#include <util/encode/hex.h>

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
/// 7. Make sure you describe the capture appropriately
/// 8. Follow whatever rest of the methods are doing (set ports, ifaces etc.)
/// 9. To easily copy packet description, click File... -> Extract packet
///    dissections -> as plain text file...
///    (Make sure that the packet is expanded in the view. The text file will
///    contain whatever expansion level you have in the graphical tree.)

using namespace std;
using namespace isc::dhcp;
using namespace isc::asiolink;

namespace isc {
namespace dhcp {
namespace test {

Pkt4Ptr PktCaptures::packetFromCapture(const std::string& hex_string) {
    std::vector<uint8_t> bin;

    // Decode the hex string and store it in bin (which happens
    // to be OptionBuffer format)
    isc::util::encode::decodeHex(hex_string, bin);

    Pkt4Ptr pkt(new Pkt4(&bin[0], bin.size()));
    captureSetDefaultFields(pkt);

    return (pkt);
}

void PktCaptures::captureSetDefaultFields(const Pkt4Ptr& pkt) {
    pkt->setRemotePort(546);
    pkt->setRemoteAddr(IOAddress("10.0.0.2"));
    pkt->setLocalPort(0);
    pkt->setLocalAddr(IOAddress("10.0.0.1"));
    pkt->setIndex(2);
    pkt->setIface("eth0");
}

Pkt4Ptr PktCaptures::captureRelayedDiscover() {

/* This is packet 1 from capture
   dhcp-val/pcap/docsis-*-CG3000DCR-Registration-Filtered.cap

string exported from Wireshark:

User Datagram Protocol, Src Port: bootps (67), Dst Port: bootps (67)
    Source port: bootps (67)
    Destination port: bootps (67)
    Length: 541
    Checksum: 0x2181 [validation disabled]

Bootstrap Protocol
    Message type: Boot Request (1)
    Hardware type: Ethernet
    Hardware address length: 6
    Hops: 1
    Transaction ID: 0x5d05478d
    Seconds elapsed: 0
    Bootp flags: 0x0000 (Unicast)
    Client IP address: 0.0.0.0 (0.0.0.0)
    Your (client) IP address: 0.0.0.0 (0.0.0.0)
    Next server IP address: 0.0.0.0 (0.0.0.0)
    Relay agent IP address: 10.254.226.1 (10.254.226.1)
    Client MAC address: Netgear_b8:15:14 (20:e5:2a:b8:15:14)
    Client hardware address padding: 00000000000000000000
    Server host name not given
    Boot file name not given
    Magic cookie: DHCP
    Option: (53) DHCP Message Type
    Option: (55) Parameter Request List
    Option: (60) Vendor class identifier (docsis3.0)
    Option: (125) V-I Vendor-specific Information
      - suboption 1 (Option Request): requesting option 2
      - suboption 5 (Modem Caps): 117 bytes
    Option: (43) Vendor-Specific Information (CableLabs)
    Option: (61) Client identifier
    Option: (57) Maximum DHCP Message Size
    Option: (82) Agent Information Option
    Option: (255) End */

    string hex_string =
        "010106015d05478d000000000000000000000000000000000afee20120e52ab8151400"
        "0000000000000000000000000000000000000000000000000000000000000000000000"
        "0000000000000000000000000000000000000000000000000000000000000000000000"
        "0000000000000000000000000000000000000000000000000000000000000000000000"
        "0000000000000000000000000000000000000000000000000000000000000000000000"
        "0000000000000000000000000000000000000000000000000000000000000000000000"
        "0000000000000000000000000000000000000000000000000000638253633501013707"
        "0102030407067d3c0a646f63736973332e303a7d7f0000118b7a010102057501010102"
        "010303010104010105010106010107010f0801100901030a01010b01180c01010d0200"
        "400e0200100f010110040000000211010014010015013f160101170101180104190104"
        "1a01041b01201c01021d01081e01201f01102001102101022201012301002401002501"
        "01260200ff2701012b59020345434d030b45434d3a45524f55544552040d3242523232"
        "39553430303434430504312e3034060856312e33332e30330707322e332e3052320806"
        "30303039354209094347333030304443520a074e657467656172fe01083d0fff2ab815"
        "140003000120e52ab81514390205dc5219010420000002020620e52ab8151409090000"
        "118b0401020300ff";

    return (packetFromCapture(hex_string));
}

Pkt4Ptr PktCaptures::captureRelayedDiscover2() {

/* This is packet 5 from capture
   dhcp-val/pcap/docsis-*-CG3000DCR-Registration-Filtered.cap

string exported from Wireshark:

User Datagram Protocol, Src Port: bootps (67), Dst Port: bootps (67)
Bootstrap Protocol
    Message type: Boot Request (1)
    Hardware type: Ethernet (0x01)
    Hardware address length: 6
    Hops: 1
    Transaction ID: 0x5d05478f
    Seconds elapsed: 5
    Bootp flags: 0x0000 (Unicast)
    Client IP address: 0.0.0.0 (0.0.0.0)
    Your (client) IP address: 0.0.0.0 (0.0.0.0)
    Next server IP address: 0.0.0.0 (0.0.0.0)
    Relay agent IP address: 10.254.226.1 (10.254.226.1)
    Client MAC address: Netgear_b8:15:15 (20:e5:2a:b8:15:15)
    Client hardware address padding: 00000000000000000000
    Server host name not given
    Boot file name not given
    Magic cookie: DHCP
    Option: (53) DHCP Message Type
    Option: (55) Parameter Request List
    Option: (43) Vendor-Specific Information
    Option: (60) Vendor class identifier (eRouter1.0)
    Option: (15) Domain Name
    Option: (61) Client identifier
    Option: (57) Maximum DHCP Message Size
    Option: (82) Agent Information Option
    Option: (255) End */

    string hex_string =
        "010106015d05478f000500000000000000000000000000000afee20120e52ab8151500"
        "0000000000000000000000000000000000000000000000000000000000000000000000"
        "0000000000000000000000000000000000000000000000000000000000000000000000"
        "0000000000000000000000000000000000000000000000000000000000000000000000"
        "0000000000000000000000000000000000000000000000000000000000000000000000"
        "0000000000000000000000000000000000000000000000000000000000000000000000"
        "000000000000000000000000000000000000000000000000000063825363350101370e"
        "480102030406070c0f171a36337a2b63020745524f55544552030b45434d3a45524f55"
        "544552040d324252323239553430303434430504312e3034060856312e33332e303307"
        "07322e332e305232080630303039354209094347333030304443520a074e6574676561"
        "720f0745524f555445523c0a65526f75746572312e300f14687364312e70612e636f6d"
        "636173742e6e65742e3d0fff2ab815150003000120e52ab81515390205dc5219010420"
        "000002020620e52ab8151409090000118b0401020300ff";

    return (packetFromCapture(hex_string));
}

Pkt4Ptr PktCaptures::captureBadRelayedDiscover() {

/* Modified packet 1 with a bad RAI.

Bootstrap Protocol
    Message type: Boot Request (1)
    Hardware type: Ethernet
    Hardware address length: 6
    Hops: 1
    Transaction ID: 0x5d05478d
    Seconds elapsed: 0
    Bootp flags: 0x0000 (Unicast)
    Client IP address: 0.0.0.0 (0.0.0.0)
    Your (client) IP address: 0.0.0.0 (0.0.0.0)
    Next server IP address: 0.0.0.0 (0.0.0.0)
    Relay agent IP address: 10.254.226.1 (10.254.226.1)
    Client MAC address: Netgear_b8:15:14 (20:e5:2a:b8:15:14)
    Client hardware address padding: 00000000000000000000
    Server host name not given
    Boot file name not given
    Magic cookie: DHCP
    Option: (53) DHCP Message Type
    Option: (55) Parameter Request List
    Option: (60) Vendor class identifier (docsis3.0)
    Option: (125) V-I Vendor-specific Information
      - suboption 1 (Option Request): requesting option 2
      - suboption 5 (Modem Caps): 117 bytes
    Option: (43) Vendor-Specific Information (CableLabs)
    Option: (61) Client identifier
    Option: (57) Maximum DHCP Message Size
    Option: (82) Agent Information Option */

    string hex_string =
        "010106015d05478d000000000000000000000000000000000afee20120e52ab8151400"
        "0000000000000000000000000000000000000000000000000000000000000000000000"
        "0000000000000000000000000000000000000000000000000000000000000000000000"
        "0000000000000000000000000000000000000000000000000000000000000000000000"
        "0000000000000000000000000000000000000000000000000000000000000000000000"
        "0000000000000000000000000000000000000000000000000000000000000000000000"
        "0000000000000000000000000000000000000000000000000000638253633501013707"
        "0102030407067d3c0a646f63736973332e303a7d7f0000118b7a010102057501010102"
        "010303010104010105010106010107010f0801100901030a01010b01180c01010d0200"
        "400e0200100f010110040000000211010014010015013f160101170101180104190104"
        "1a01041b01201c01021d01081e01201f01102001102101022201012301002401002501"
        "01260200ff2701012b59020345434d030b45434d3a45524f55544552040d3242523232"
        "39553430303434430504312e3034060856312e33332e30330707322e332e3052320806"
        "30303039354209094347333030304443520a074e657467656172fe01083d0fff2ab815"
        "140003000120e52ab81514390205dc52205141000102030405060708090a0b0c0d0e0f"
        "101112131415161718191a1b1c1d";

    return (packetFromCapture(hex_string));
}

Pkt4Ptr PktCaptures::discoverWithValidVIVSO() {
/* DISCOVER that contains a valid VIVSO option 125
User    Datagram    Protocol,   Src Port:   67, Dst Port:   67
Bootstrap   Protocol    (Discover)
    Message type:   Boot    Request (1)
    Hardware    type:   Ethernet    (0x01)
    Hardware    address length: 6
    Hops:   1
    Transaction ID: 0x2d5d43cb
    Seconds elapsed:    0
    Bootp   flags:  0x8000, Broadcast   flag    (Broadcast)
    Client  IP  address:    0.0.0.0
    Your    (client)    IP  address:    0.0.0.0
    Next    server  IP  address:    0.0.0.0
    Relay   agent   IP  address:    10.206.80.1
    Client  MAC address:    ArrisGro_5e:f7:af   (78:96:84:5e:f7:af)
    Client  hardware    address padding:    00000000000000000000
    Server  host    name    not given
    Boot    file    name    not given
    Magic   cookie: DHCP
    Option: (53)    DHCP    Message Type    (Discover)
    Option: (55)    Parameter   Request List
    Option: (60)    Vendor  class   identifier
    Option: (125)   V-I Vendor-specific Information
    Option: (43)    Vendor-Specific Information (CableLabs)
    Option: (61)    Client  identifier
    Option: (57)    Maximum DHCP    Message Size
    Option: (82)    Agent   Information Option
    Option: (255)   End
*/
    string hex_string =
        "010106012d5d43cb000080000000000000000000000000000ace50017896845ef7af0"
        "000000000000000000000000000000000000000000000000000000000000000000000"
        "000000000000000000000000000000000000000000000000000000000000000000000"
        "000000000000000000000000000000000000000000000000000000000000000000000"
        "000000000000000000000000000000000000000000000000000000000000000000000"
        "000000000000000000000000000000000000000000000000000000000000000000000"
        "000000000000000000000000000000000000000000000000000000000063825363350"
        "10137070102030407067d3c0a646f63736973332e303a7d850000118b80010102057b"
        "01010102010303010104010105010106010107010f0801100901030a01010b01180c0"
        "1010d0201000e0201000f010110040000000211010113010114010015013f16010117"
        "01011801041901041a01041b01201c01021d01081e01201f011020011021010222010"
        "1230100240100250101260200ff2701012801d82b7c020345434d030b45434d3a4552"
        "4f5554455208030020400418333936373739343234343335353037373031303134303"
        "035050131061e534247365838322d382e362e302e302d47412d30312d3937312d4e4f"
        "5348070432343030090a534247363738322d41430a144d6f746f726f6c6120436f727"
        "06f726174696f6e3d0fff845ef7af000300017896845ef7af390205dc521b01048005"
        "03f802067896845ef7af090b0000118b06010401020300ff";

    return (packetFromCapture(hex_string));
}

Pkt4Ptr PktCaptures::discoverWithTruncatedVIVSO() {
/* DISCOVER that contains VIVSO option 125 with an INVALID length of 01
User    Datagram    Protocol,   Src Port:   67, Dst Port:   67
Bootstrap   Protocol    (Discover)
    Message type:   Boot    Request (1)
    Hardware    type:   Ethernet    (0x01)
    Hardware    address length: 6
    Hops:   1
    Transaction ID: 0x2d5d43cb
    Seconds elapsed:    0
    Bootp   flags:  0x8000, Broadcast   flag    (Broadcast)
    Client  IP  address:    0.0.0.0
    Your    (client)    IP  address:    0.0.0.0
    Next    server  IP  address:    0.0.0.0
    Relay   agent   IP  address:    10.206.80.1
    Client  MAC address:    ArrisGro_5e:f7:af   (78:96:84:5e:f7:af)
    Client  hardware    address padding:    00000000000000000000
    Server  host    name    not given
    Boot    file    name    not given
    Magic   cookie: DHCP
    Option: (53)    DHCP    Message Type    (Discover)
    Option: (55)    Parameter   Request List
    Option: (60)    Vendor  class   identifier
    Option: (125)   V-I Vendor-specific Information
    Option: (43)    Vendor-Specific Information (CableLabs)
    Option: (61)    Client  identifier
    Option: (57)    Maximum DHCP    Message Size
    Option: (82)    Agent   Information Option
    Option: (255)   End
*/
    string hex_string =
        "010106012d5d43cb000080000000000000000000000000000ace50017896845ef7af0"
        "000000000000000000000000000000000000000000000000000000000000000000000"
        "000000000000000000000000000000000000000000000000000000000000000000000"
        "000000000000000000000000000000000000000000000000000000000000000000000"
        "000000000000000000000000000000000000000000000000000000000000000000000"
        "000000000000000000000000000000000000000000000000000000000000000000000"
        "000000000000000000000000000000000000000000000000000000000063825363350"
        "10137070102030407067d3c0a646f63736973332e303a7d010000118b80010102057b"
        "01010102010303010104010105010106010107010f0801100901030a01010b01180c0"
        "1010d0201000e0201000f010110040000000211010113010114010015013f16010117"
        "01011801041901041a01041b01201c01021d01081e01201f011020011021010222010"
        "1230100240100250101260200ff2701012801d82b7c020345434d030b45434d3a4552"
        "4f5554455208030020400418333936373739343234343335353037373031303134303"
        "035050131061e534247365838322d382e362e302e302d47412d30312d3937312d4e4f"
        "5348070432343030090a534247363738322d41430a144d6f746f726f6c6120436f727"
        "06f726174696f6e3d0fff845ef7af000300017896845ef7af390205dc521b01048005"
        "03f802067896845ef7af090b0000118b06010401020300ff";

    return (packetFromCapture(hex_string));
}

Pkt4Ptr PktCaptures::discoverGenexis() {

/* Bootstrap Protocol (Discover)
    Message type: Boot Request (1)
    Hardware type: Ethernet (0x01)
    Hardware address length: 6
    Hops: 0
    Transaction ID: 0x946a5b5a
    Seconds elapsed: 0
    Bootp flags: 0x8000, Broadcast flag (Broadcast)
    Client IP address: 0.0.0.0
    Your (client) IP address: 0.0.0.0
    Next server IP address: 0.0.0.0
    Relay agent IP address: 0.0.0.0
    Client MAC address: GenexisB_6a:1a:93 (00:0f:94:6a:1a:93)
    Client hardware address padding: 00000000000000000000
    Server host name not given
    Boot file name not given
    Magic cookie: DHCP
    Option: (53) DHCP Message Type (Discover)
    Option: (60) Vendor class identifier (HMC1000.v1.3.0-R,Element-P1090,genexis.eu)
    Option: (51) IP Address Lease Time
    Option: (55) Parameter Request List
    Option: (255) End
    Padding: 000000000000000000000000000000000000000000000000... */

    string hex_string =
        "01010600946a5b5a0000800000000000000000000000000000000000000f946a1a9300"
        "0000000000000000000000000000000000000000000000000000000000000000000000"
        "0000000000000000000000000000000000000000000000000000000000000000000000"
        "0000000000000000000000000000000000000000000000000000000000000000000000"
        "0000000000000000000000000000000000000000000000000000000000000000000000"
        "0000000000000000000000000000000000000000000000000000000000000000000000"
        "0000000000000000000000000000000000000000000000000000638253633501013c29"
        "484d43313030302e76312e332e302d522c456c656d656e742d50313039302c67656e65"
        "7869732e65753304ffffffff37040103067dff00000000000000000000000000000000"
        "0000000000000000000000000000000000000000000000000000000000000000000000"
        "0000000000000000000000000000000000000000000000000000000000000000000000"
        "0000000000000000000000000000000000000000000000000000000000000000000000"
        "0000000000000000000000000000000000000000000000000000000000000000000000"
        "0000000000000000000000000000000000000000000000000000000000000000000000"
        "0000000000000000000000000000000000000000000000000000000000000000000000"
        "0000000000000000000000000000000000000000000000000000000000000000000000"
        "00000000000000000000000000000000";
    return (packetFromCapture(hex_string));
}

}; // end of isc::dhcp::test namespace
}; // end of isc::dhcp namespace
}; // end of isc namespace
