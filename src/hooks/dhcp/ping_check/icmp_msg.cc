// Copyright (C) 2023-2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <icmp_msg.h>
#include <util/io.h>
#include <exceptions/exceptions.h>

#include <netinet/ip_icmp.h>
#include <iostream>

using namespace isc;
using namespace isc::asiolink;
using namespace isc::util;

namespace isc {
namespace ping_check {

ICMPMsg::ICMPMsg()
    : source_(IOAddress::IPV4_ZERO_ADDRESS()),
      destination_(IOAddress::IPV4_ZERO_ADDRESS()),
      msg_type_(0), code_(0), check_sum_(0), id_(0), sequence_(0),
      payload_(0) {
}

ICMPMsgPtr
ICMPMsg::unpack(const uint8_t* wire_data, size_t length) {
    ICMPMsgPtr msg(new ICMPMsg());
    if (length < sizeof(struct ip)) {
        isc_throw(BadValue,
                  "ICMPMsg::unpack - truncated ip header, length: "
                  << length);
    }

    // Find the IP header length...
    struct ip* ip_header = (struct ip*)(wire_data);
    auto hlen = (ip_header->ip_hl << 2);

    // Make sure we received enough data.
    if (length < (hlen + sizeof(struct icmp))) {
        isc_throw(BadValue, "ICMPMsg::truncated packet? length: "
                  << length << ", hlen: " << hlen);
    }

    // Grab the source and destination addresses.
    msg->setSource(IOAddress(ntohl(ip_header->ip_src.s_addr)));
    msg->setDestination(IOAddress(ntohl(ip_header->ip_dst.s_addr)));

    // Get the message type.
    struct icmp* reply = (struct icmp*)(wire_data + hlen);
    msg->setType(reply->icmp_type);
    msg->setCode(reply->icmp_code);

    msg->setChecksum(ntohs(reply->icmp_cksum));
    msg->setId(ntohs(reply->icmp_hun.ih_idseq.icd_id));
    msg->setSequence(ntohs(reply->icmp_hun.ih_idseq.icd_seq));

    auto payload_len = length - hlen - ICMP_HEADER_SIZE;
    msg->setPayload((const uint8_t*)(&reply->icmp_dun), payload_len);

    return (msg);
}

ICMPPtr
ICMPMsg::pack() const {
    ICMPPtr outbound(new struct icmp());
    memset(outbound.get(), 0x00, sizeof(struct icmp));
    outbound->icmp_type = msg_type_;
    outbound->icmp_id = htons(id_);
    outbound->icmp_seq = htons(sequence_);
    /// @todo copy in payload - not needed for ECHO REQUEST
    outbound->icmp_cksum = htons(~calcChecksum((const uint8_t*)(outbound.get()), sizeof(struct icmp)));
    return (outbound);
}

void
ICMPMsg::setPayload(const uint8_t* data, size_t length) {
    payload_.insert(payload_.end(), data, data + length);
}

uint32_t
ICMPMsg::calcChecksum(const uint8_t* buf, size_t length) {
    uint32_t sum = 0;

    /* Checksum all the pairs of bytes first... */
    size_t i;
    for (i = 0; i < (length & ~1U); i += 2) {
        sum += static_cast<uint32_t>(readUint16(buf + i, sizeof(uint16_t)));
        /* Add carry. */
        if (sum > 0xFFFF) {
            sum -= 0xFFFF;
        }
    }

    /* If there's a single byte left over, checksum it, too.   Network
       byte order is big-endian, so the remaining byte is the high byte. */
    if (i < length) {
        sum += buf[i] << 8;
        /* Add carry. */
        if (sum > 0xFFFF) {
            sum -= 0xFFFF;
        }
    }

    return (sum);
}

} // end of namespace ping_check
} // end of namespace isc
