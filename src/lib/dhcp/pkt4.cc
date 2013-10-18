// Copyright (C) 2011-2013  Internet Systems Consortium, Inc. ("ISC")
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
#include <dhcp/option_int.h>
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
     :buffer_out_(DHCPV4_PKT_HDR_LEN),
      local_addr_(DEFAULT_ADDRESS),
      remote_addr_(DEFAULT_ADDRESS),
      iface_(""),
      ifindex_(0),
      local_port_(DHCP4_SERVER_PORT),
      remote_port_(DHCP4_CLIENT_PORT),
      op_(DHCPTypeToBootpType(msg_type)),
      hwaddr_(new HWAddr()),
      hops_(0),
      transid_(transid),
      secs_(0),
      flags_(0),
      ciaddr_(DEFAULT_ADDRESS),
      yiaddr_(DEFAULT_ADDRESS),
      siaddr_(DEFAULT_ADDRESS),
      giaddr_(DEFAULT_ADDRESS)
{
    memset(sname_, 0, MAX_SNAME_LEN);
    memset(file_, 0, MAX_FILE_LEN);

    setType(msg_type);
}

Pkt4::Pkt4(const uint8_t* data, size_t len)
     :buffer_out_(0), // not used, this is RX packet
      local_addr_(DEFAULT_ADDRESS),
      remote_addr_(DEFAULT_ADDRESS),
      iface_(""),
      ifindex_(0),
      local_port_(DHCP4_SERVER_PORT),
      remote_port_(DHCP4_CLIENT_PORT),
      op_(BOOTREQUEST),
      hwaddr_(new HWAddr()),
      transid_(0),
      secs_(0),
      flags_(0),
      ciaddr_(DEFAULT_ADDRESS),
      yiaddr_(DEFAULT_ADDRESS),
      siaddr_(DEFAULT_ADDRESS),
      giaddr_(DEFAULT_ADDRESS)
{
    if (len < DHCPV4_PKT_HDR_LEN) {
        isc_throw(OutOfRange, "Truncated DHCPv4 packet (len=" << len
                  << ") received, at least " << DHCPV4_PKT_HDR_LEN
                  << " is expected.");

    } else if (data == NULL) {
        isc_throw(InvalidParameter, "data buffer passed to Pkt4 is NULL");
    }

    data_.resize(len);
    memcpy(&data_[0], data, len);
}

size_t
Pkt4::len() {
    size_t length = DHCPV4_PKT_HDR_LEN; // DHCPv4 header

    // ... and sum of lengths of all options
    for (OptionCollection::const_iterator it = options_.begin();
         it != options_.end();
         ++it) {
        length += (*it).second->len();
    }

    return (length);
}

void
Pkt4::pack() {
    if (!hwaddr_) {
        isc_throw(InvalidOperation, "Can't build Pkt4 packet. HWAddr not set.");
    }

    // Clear the output buffer to make sure that consecutive calls to pack()
    // will not result in concatenation of multiple packet copies.
    buffer_out_.clear();

    try {
        size_t hw_len = hwaddr_->hwaddr_.size();

        buffer_out_.writeUint8(op_);
        buffer_out_.writeUint8(hwaddr_->htype_);
        buffer_out_.writeUint8(hw_len < MAX_CHADDR_LEN ?
                              hw_len : MAX_CHADDR_LEN);
        buffer_out_.writeUint8(hops_);
        buffer_out_.writeUint32(transid_);
        buffer_out_.writeUint16(secs_);
        buffer_out_.writeUint16(flags_);
        buffer_out_.writeUint32(ciaddr_);
        buffer_out_.writeUint32(yiaddr_);
        buffer_out_.writeUint32(siaddr_);
        buffer_out_.writeUint32(giaddr_);


        if (hw_len <= MAX_CHADDR_LEN) {
            // write up to 16 bytes of the hardware address (CHADDR field is 16
            // bytes long in DHCPv4 message).
            buffer_out_.writeData(&hwaddr_->hwaddr_[0],
                                 (hw_len < MAX_CHADDR_LEN ?
                                  hw_len : MAX_CHADDR_LEN) );
            hw_len = MAX_CHADDR_LEN - hw_len;
        } else {
            hw_len = MAX_CHADDR_LEN;
        }

        // write (len) bytes of padding
        vector<uint8_t> zeros(hw_len, 0);
        buffer_out_.writeData(&zeros[0], hw_len);
        // buffer_out_.writeData(chaddr_, MAX_CHADDR_LEN);

        buffer_out_.writeData(sname_, MAX_SNAME_LEN);
        buffer_out_.writeData(file_, MAX_FILE_LEN);

        // write DHCP magic cookie
        buffer_out_.writeUint32(DHCP_OPTIONS_COOKIE);

        LibDHCP::packOptions(buffer_out_, options_);

        // add END option that indicates end of options
        // (End option is very simple, just a 255 octet)
         buffer_out_.writeUint8(DHO_END);
     } catch(const Exception& e) {
        // An exception is thrown and message will be written to Logger
         isc_throw(InvalidOperation, e.what());
    }
}

void
Pkt4::unpack() {

    // input buffer (used during message reception)
    isc::util::InputBuffer buffer_in(&data_[0], data_.size());

    if (buffer_in.getLength() < DHCPV4_PKT_HDR_LEN) {
        isc_throw(OutOfRange, "Received truncated DHCPv4 packet (len="
                  << buffer_in.getLength() << " received, at least "
                  << DHCPV4_PKT_HDR_LEN << "is expected");
    }

    op_ = buffer_in.readUint8();
    uint8_t htype = buffer_in.readUint8();
    uint8_t hlen = buffer_in.readUint8();
    hops_ = buffer_in.readUint8();
    transid_ = buffer_in.readUint32();
    secs_ = buffer_in.readUint16();
    flags_ = buffer_in.readUint16();
    ciaddr_ = IOAddress(buffer_in.readUint32());
    yiaddr_ = IOAddress(buffer_in.readUint32());
    siaddr_ = IOAddress(buffer_in.readUint32());
    giaddr_ = IOAddress(buffer_in.readUint32());

    vector<uint8_t> hw_addr(MAX_CHADDR_LEN, 0);
    buffer_in.readVector(hw_addr, MAX_CHADDR_LEN);
    buffer_in.readData(sname_, MAX_SNAME_LEN);
    buffer_in.readData(file_, MAX_FILE_LEN);

    hw_addr.resize(hlen);

    hwaddr_ = HWAddrPtr(new HWAddr(hw_addr, htype));

    if (buffer_in.getLength() == buffer_in.getPosition()) {
        // this is *NOT* DHCP packet. It does not have any DHCPv4 options. In
        // particular, it does not have magic cookie, a 4 byte sequence that
        // differentiates between DHCP and BOOTP packets.
        isc_throw(InvalidOperation, "Received BOOTP packet. BOOTP is not supported.");
    }

    if (buffer_in.getLength() - buffer_in.getPosition() < 4) {
      // there is not enough data to hold magic DHCP cookie
      isc_throw(Unexpected, "Truncated or no DHCP packet.");
    }

    uint32_t magic = buffer_in.readUint32();
    if (magic != DHCP_OPTIONS_COOKIE) {
      isc_throw(Unexpected, "Invalid or missing DHCP magic cookie");
    }

    size_t opts_len = buffer_in.getLength() - buffer_in.getPosition();
    vector<uint8_t> opts_buffer;

    // Use readVector because a function which parses option requires
    // a vector as an input.
    buffer_in.readVector(opts_buffer, opts_len);
    if (callback_.empty()) {
        LibDHCP::unpackOptions4(opts_buffer, "dhcp4", options_);
    } else {
        // The last two arguments are set to NULL because they are
        // specific to DHCPv6 options parsing. They are unused for
        // DHCPv4 case. In DHCPv6 case they hold are the relay message
        // offset and length.
        callback_(opts_buffer, "dhcp4", options_, NULL, NULL);
    }

    // @todo check will need to be called separately, so hooks can be called
    // after the packet is parsed, but before its content is verified
    check();
}

void Pkt4::check() {
    uint8_t msg_type = getType();
    if (msg_type > DHCPLEASEACTIVE) {
        isc_throw(BadValue, "Invalid DHCP message type received: "
                  << static_cast<int>(msg_type));
    }
}

uint8_t Pkt4::getType() const {
    OptionPtr generic = getOption(DHO_DHCP_MESSAGE_TYPE);
    if (!generic) {
        isc_throw(Unexpected, "Missing DHCP Message Type option");
    }

    // Check if Message Type is specified as OptionInt<uint8_t>
    boost::shared_ptr<OptionInt<uint8_t> > type_opt =
        boost::dynamic_pointer_cast<OptionInt<uint8_t> >(generic);
    if (type_opt) {
        return (type_opt->getValue());
    }

    // Try to use it as generic option
    return (generic->getUint8());
}

void Pkt4::setType(uint8_t dhcp_type) {
    OptionPtr opt = getOption(DHO_DHCP_MESSAGE_TYPE);
    if (opt) {
        // There is message type option already, update it
        opt->setUint8(dhcp_type);
    } else {
        // There is no message type option yet, add it
        std::vector<uint8_t> tmp(1, dhcp_type);
        opt = OptionPtr(new Option(Option::V4, DHO_DHCP_MESSAGE_TYPE, tmp));
        addOption(opt);
    }
}

void Pkt4::repack() {
    buffer_out_.writeData(&data_[0], data_.size());
}

std::string
Pkt4::toText() {
    stringstream tmp;
    tmp << "localAddr=" << local_addr_.toText() << ":" << local_port_
        << " remoteAddr=" << remote_addr_.toText()
        << ":" << remote_port_ << ", msgtype=" << static_cast<int>(getType())
        << ", transid=0x" << hex << transid_ << dec << endl;

    for (isc::dhcp::OptionCollection::iterator opt=options_.begin();
         opt != options_.end();
         ++opt) {
        tmp << "  " << opt->second->toText() << std::endl;
    }


    return tmp.str();
}

void
Pkt4::setHWAddr(uint8_t htype, uint8_t hlen,
                const std::vector<uint8_t>& mac_addr) {
    setHWAddrMember(htype, hlen, mac_addr, hwaddr_);
}

void
Pkt4::setHWAddr(const HWAddrPtr& addr) {
    if (!addr) {
        isc_throw(BadValue, "Setting DHCPv4 chaddr field to NULL"
                  << " is forbidden");
    }
    hwaddr_ = addr;
}

void
Pkt4::setHWAddrMember(const uint8_t htype, const uint8_t hlen,
                      const std::vector<uint8_t>& mac_addr,
                      HWAddrPtr& hw_addr) {
    /// @todo Rewrite this once support for client-identifier option
    /// is implemented (ticket 1228?)
    if (hlen > MAX_CHADDR_LEN) {
        isc_throw(OutOfRange, "Hardware address (len=" << hlen
                  << " too long. Max " << MAX_CHADDR_LEN << " supported.");

    } else if (mac_addr.empty() && (hlen > 0) ) {
        isc_throw(OutOfRange, "Invalid HW Address specified");
    }

    hw_addr.reset(new HWAddr(mac_addr, htype));
}

void
Pkt4::setLocalHWAddr(const uint8_t htype, const uint8_t hlen,
                      const std::vector<uint8_t>& mac_addr) {
    setHWAddrMember(htype, hlen, mac_addr, local_hwaddr_);
}

void
Pkt4::setLocalHWAddr(const HWAddrPtr& addr) {
    if (!addr) {
        isc_throw(BadValue, "Setting local HW address to NULL is"
                  << " forbidden.");
    }
    local_hwaddr_ = addr;
}

void
Pkt4::setRemoteHWAddr(const uint8_t htype, const uint8_t hlen,
                      const std::vector<uint8_t>& mac_addr) {
    setHWAddrMember(htype, hlen, mac_addr, remote_hwaddr_);
}

void
Pkt4::setRemoteHWAddr(const HWAddrPtr& addr) {
    if (!addr) {
        isc_throw(BadValue, "Setting remote HW address to NULL is"
                  << " forbidden.");
    }
    remote_hwaddr_ = addr;
}

void
Pkt4::setSname(const uint8_t* sname, size_t snameLen /*= MAX_SNAME_LEN*/) {
    if (snameLen > MAX_SNAME_LEN) {
        isc_throw(OutOfRange, "sname field (len=" << snameLen
                  << ") too long, Max " << MAX_SNAME_LEN << " supported.");

    } else if (sname == NULL) {
        isc_throw(InvalidParameter, "Invalid sname specified");
    }

    std::copy(&sname[0], &sname[snameLen], &sname_[0]);
    std::fill(&sname_[snameLen], &sname_[MAX_SNAME_LEN], 0);

    // No need to store snameLen as any empty space is filled with 0s
}

void
Pkt4::setFile(const uint8_t* file, size_t fileLen /*= MAX_FILE_LEN*/) {
    if (fileLen > MAX_FILE_LEN) {
        isc_throw(OutOfRange, "file field (len=" << fileLen
                  << ") too long, Max " << MAX_FILE_LEN << " supported.");

    } else if (file == NULL) {
        isc_throw(InvalidParameter, "Invalid file name specified");
    }

    std::copy(&file[0], &file[fileLen], &file_[0]);
    std::fill(&file_[fileLen], &file_[MAX_FILE_LEN], 0);

    // No need to store fileLen as any empty space is filled with 0s
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

uint8_t
Pkt4::getHtype() const {
    if (!hwaddr_) {
        isc_throw(InvalidOperation, "Can't get HType. HWAddr not defined");
    }
    return (hwaddr_->htype_);
}

uint8_t
Pkt4::getHlen() const {
    if (!hwaddr_) {
        isc_throw(InvalidOperation, "Can't get HType. HWAddr not defined");
    }
    uint8_t len = hwaddr_->hwaddr_.size();
    return (len <= MAX_CHADDR_LEN ? len : MAX_CHADDR_LEN);
}

void
Pkt4::addOption(boost::shared_ptr<Option> opt) {
    // Check for uniqueness (DHCPv4 options must be unique)
    if (getOption(opt->getType())) {
        isc_throw(BadValue, "Option " << opt->getType()
                  << " already present in this message.");
    }
    options_.insert(pair<int, boost::shared_ptr<Option> >(opt->getType(), opt));
}

boost::shared_ptr<isc::dhcp::Option>
Pkt4::getOption(uint8_t type) const {
    OptionCollection::const_iterator x = options_.find(type);
    if (x != options_.end()) {
        return (*x).second;
    }
    return boost::shared_ptr<isc::dhcp::Option>(); // NULL
}

bool
Pkt4::delOption(uint8_t type) {
    isc::dhcp::OptionCollection::iterator x = options_.find(type);
    if (x != options_.end()) {
        options_.erase(x);
        return (true); // delete successful
    }
    return (false); // can't find option to be deleted
}

void
Pkt4::updateTimestamp() {
    timestamp_ = boost::posix_time::microsec_clock::universal_time();
}

bool
Pkt4::inClass(const std::string& client_class) {
    return (classes_.find(client_class) != classes_.end());
}

void
Pkt4::addClass(const std::string& client_class) {
    if (classes_.find(client_class) == classes_.end()) {
        classes_.insert(client_class);
    }
}

} // end of namespace isc::dhcp

} // end of namespace isc
