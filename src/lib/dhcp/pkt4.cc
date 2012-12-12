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

#include <asiolink/io_address.h>
#include <dhcp/dhcp4.h>
#include <dhcp/libdhcp++.h>
#include <dhcp/pkt4.h>
#include <exceptions/exceptions.h>

#include <algorithm>
#include <iostream>
#include <sstream>

using namespace std;
using namespace isc::dhcp;
using namespace isc::asiolink;

namespace isc {
namespace dhcp {

const IOAddress DEFAULT_ADDRESS("0.0.0.0");

Pkt4::Pkt4(uint8_t msg_type, uint32_t transid)
     :local_addr_(DEFAULT_ADDRESS),
      remote_addr_(DEFAULT_ADDRESS),
      iface_(""),
      ifindex_(0),
      local_port_(DHCP4_SERVER_PORT),
      remote_port_(DHCP4_CLIENT_PORT),
      op_(DHCPTypeToBootpType(msg_type)),
      htype_(HTYPE_ETHER),
      hlen_(0),
      hops_(0),
      transid_(transid),
      secs_(0),
      flags_(0),
      ciaddr_(DEFAULT_ADDRESS),
      yiaddr_(DEFAULT_ADDRESS),
      siaddr_(DEFAULT_ADDRESS),
      giaddr_(DEFAULT_ADDRESS),
      bufferOut_(DHCPV4_PKT_HDR_LEN),
      msg_type_(msg_type)
{
    memset(chaddr_, 0, MAX_CHADDR_LEN);
    memset(sname_, 0, MAX_SNAME_LEN);
    memset(file_, 0, MAX_FILE_LEN);
}

Pkt4::Pkt4(const uint8_t* data, size_t len)
     :local_addr_(DEFAULT_ADDRESS),
      remote_addr_(DEFAULT_ADDRESS),
      iface_(""),
      ifindex_(0),
      local_port_(DHCP4_SERVER_PORT),
      remote_port_(DHCP4_CLIENT_PORT),
      op_(BOOTREQUEST),
      transid_(0),
      secs_(0),
      flags_(0),
      ciaddr_(DEFAULT_ADDRESS),
      yiaddr_(DEFAULT_ADDRESS),
      siaddr_(DEFAULT_ADDRESS),
      giaddr_(DEFAULT_ADDRESS),
      bufferOut_(0), // not used, this is RX packet
      msg_type_(DHCPDISCOVER)
{
    if (len < DHCPV4_PKT_HDR_LEN) {
        isc_throw(OutOfRange, "Truncated DHCPv4 packet (len=" << len
                  << ") received, at least " << DHCPV4_PKT_HDR_LEN
                  << " is expected.");
    }

    data_.resize(len);
    memcpy(&data_[0], data, len);
}

size_t
Pkt4::len() {
    size_t length = DHCPV4_PKT_HDR_LEN; // DHCPv4 header

    // ... and sum of lengths of all options
    for (Option::OptionCollection::const_iterator it = options_.begin();
         it != options_.end();
         ++it) {
        length += (*it).second->len();
    }

    return (length);
}

bool
Pkt4::pack() {
    bufferOut_.writeUint8(op_);
    bufferOut_.writeUint8(htype_);
    bufferOut_.writeUint8(hlen_);
    bufferOut_.writeUint8(hops_);
    bufferOut_.writeUint32(transid_);
    bufferOut_.writeUint16(secs_);
    bufferOut_.writeUint16(flags_);
    bufferOut_.writeUint32(ciaddr_);
    bufferOut_.writeUint32(yiaddr_);
    bufferOut_.writeUint32(siaddr_);
    bufferOut_.writeUint32(giaddr_);
    bufferOut_.writeData(chaddr_, MAX_CHADDR_LEN);
    bufferOut_.writeData(sname_, MAX_SNAME_LEN);
    bufferOut_.writeData(file_, MAX_FILE_LEN);

    // write DHCP magic cookie
    bufferOut_.writeUint32(DHCP_OPTIONS_COOKIE);

    LibDHCP::packOptions(bufferOut_, options_);

    // add END option that indicates end of options
    // (End option is very simple, just a 255 octet)
    bufferOut_.writeUint8(DHO_END);

    return (true);
}

void
Pkt4::unpack() {

    // input buffer (used during message reception)
    isc::util::InputBuffer bufferIn(&data_[0], data_.size());

    if (bufferIn.getLength() < DHCPV4_PKT_HDR_LEN) {
        isc_throw(OutOfRange, "Received truncated DHCPv4 packet (len="
                  << bufferIn.getLength() << " received, at least "
                  << DHCPV4_PKT_HDR_LEN << "is expected");
    }

    op_ = bufferIn.readUint8();
    htype_ = bufferIn.readUint8();
    hlen_ = bufferIn.readUint8();
    hops_ = bufferIn.readUint8();
    transid_ = bufferIn.readUint32();
    secs_ = bufferIn.readUint16();
    flags_ = bufferIn.readUint16();
    ciaddr_ = IOAddress(bufferIn.readUint32());
    yiaddr_ = IOAddress(bufferIn.readUint32());
    siaddr_ = IOAddress(bufferIn.readUint32());
    giaddr_ = IOAddress(bufferIn.readUint32());
    bufferIn.readData(chaddr_, MAX_CHADDR_LEN);
    bufferIn.readData(sname_, MAX_SNAME_LEN);
    bufferIn.readData(file_, MAX_FILE_LEN);

    if (bufferIn.getLength() == bufferIn.getPosition()) {
        // this is *NOT* DHCP packet. It does not have any DHCPv4 options. In
        // particular, it does not have magic cookie, a 4 byte sequence that
        // differentiates between DHCP and BOOTP packets.
        isc_throw(InvalidOperation, "Recevied BOOTP packet. BOOTP is not supported.");
    }

    if (bufferIn.getLength() - bufferIn.getPosition() < 4) {
      // there is not enough data to hold magic DHCP cookie
      isc_throw(Unexpected, "Truncated or no DHCP packet.");
    }

    uint32_t magic = bufferIn.readUint32();
    if (magic != DHCP_OPTIONS_COOKIE) {
      isc_throw(Unexpected, "Invalid or missing DHCP magic cookie");
    }

    size_t opts_len = bufferIn.getLength() - bufferIn.getPosition();
    vector<uint8_t> optsBuffer;

    // First use of readVector.
    bufferIn.readVector(optsBuffer, opts_len);
    LibDHCP::unpackOptions4(optsBuffer, options_);

    // TODO: check will need to be called separately, so hooks can be called after
    // packet is parsed, but before its content is verified
    check();
}

void Pkt4::check() {
    boost::shared_ptr<Option> typeOpt = getOption(DHO_DHCP_MESSAGE_TYPE);
    if (typeOpt) {
        uint8_t msg_type = typeOpt->getUint8();
        if (msg_type>DHCPLEASEACTIVE) {
            isc_throw(BadValue, "Invalid DHCP message type received:" << msg_type);
        }
        msg_type_ = msg_type;

    } else {
        isc_throw(Unexpected, "Missing DHCP Message Type option");
    }
}

void Pkt4::repack() {
    bufferOut_.writeData(&data_[0], data_.size());
}

std::string
Pkt4::toText() {
    stringstream tmp;
    tmp << "localAddr=" << local_addr_.toText() << ":" << local_port_
        << " remoteAddr=" << remote_addr_.toText()
        << ":" << remote_port_ << ", msgtype=" << int(msg_type_)
        << ", transid=0x" << hex << transid_ << dec << endl;

    for (isc::dhcp::Option::OptionCollection::iterator opt=options_.begin();
         opt != options_.end();
         ++opt) {
        tmp << "  " << opt->second->toText() << std::endl;
    }


    return tmp.str();
}

void
Pkt4::setHWAddr(uint8_t hType, uint8_t hlen,
                const std::vector<uint8_t>& macAddr) {
    /// TODO Rewrite this once support for client-identifier option
    /// is implemented (ticket 1228?)
    if (hlen > MAX_CHADDR_LEN) {
        isc_throw(OutOfRange, "Hardware address (len=" << hlen
                  << " too long. Max " << MAX_CHADDR_LEN << " supported.");
    }
    if (macAddr.empty() && (hlen > 0) ) {
        isc_throw(OutOfRange, "Invalid HW Address specified");
    }

    htype_ = hType;
    hlen_ = hlen;
    std::copy(&macAddr[0], &macAddr[hlen], &chaddr_[0]);
    std::fill(&chaddr_[hlen], &chaddr_[MAX_CHADDR_LEN], 0);
}

void
Pkt4::setSname(const uint8_t* sname, size_t snameLen /*= MAX_SNAME_LEN*/) {
    if (snameLen > MAX_SNAME_LEN) {
        isc_throw(OutOfRange, "sname field (len=" << snameLen
                  << ") too long, Max " << MAX_SNAME_LEN << " supported.");
    }
    std::copy(&sname[0], &sname[snameLen], &sname_[0]);
    std::fill(&sname_[snameLen], &sname_[MAX_SNAME_LEN], 0);

    // no need to store snameLen as any empty space is filled with 0s
}

void
Pkt4::setFile(const uint8_t* file, size_t fileLen /*= MAX_FILE_LEN*/) {
    if (fileLen > MAX_FILE_LEN) {
        isc_throw(OutOfRange, "file field (len=" << fileLen
                  << ") too long, Max " << MAX_FILE_LEN << " supported.");
    }
    std::copy(&file[0], &file[fileLen], &file_[0]);
    std::fill(&file_[fileLen], &file_[MAX_FILE_LEN], 0);

    // no need to store fileLen as any empty space is filled with 0s
}

uint8_t
Pkt4::DHCPTypeToBootpType(uint8_t dhcpType) {
    switch (dhcpType) {
    case DHCPDISCOVER:
    case DHCPREQUEST:
    case DHCPDECLINE:
    case DHCPRELEASE:
    case DHCPINFORM:
    case DHCPLEASEQUERY:
        return (BOOTREQUEST);
    case DHCPACK:
    case DHCPNAK:
    case DHCPOFFER:
    case DHCPLEASEUNASSIGNED:
    case DHCPLEASEUNKNOWN:
    case DHCPLEASEACTIVE:
        return (BOOTREPLY);
    default:
        isc_throw(OutOfRange, "Invalid message type: "
                  << static_cast<int>(dhcpType) );
    }
}

void
Pkt4::addOption(boost::shared_ptr<Option> opt) {
    // check for uniqueness (DHCPv4 options must be unique)
    if (getOption(opt->getType())) {
        isc_throw(BadValue, "Option " << opt->getType()
                  << " already present in this message.");
    }
    options_.insert(pair<int, boost::shared_ptr<Option> >(opt->getType(), opt));
}

boost::shared_ptr<isc::dhcp::Option>
Pkt4::getOption(uint8_t type) {
    Option::OptionCollection::const_iterator x = options_.find(type);
    if (x!=options_.end()) {
        return (*x).second;
    }
    return boost::shared_ptr<isc::dhcp::Option>(); // NULL
}

void
Pkt4::updateTimestamp() {
    timestamp_ = boost::posix_time::microsec_clock::universal_time();
}

} // end of namespace isc::dhcp

} // end of namespace isc
