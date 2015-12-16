// Copyright (C) 2013-2015 Internet Systems Consortium, Inc. ("ISC")
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
/// 7. Make sure you decribe the capture appropriately
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

}; // end of isc::dhcp::test namespace
}; // end of isc::dhcp namespace
}; // end of isc namespace
