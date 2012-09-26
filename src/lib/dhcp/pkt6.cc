// Copyright (C) 2011-2012 Internet Systems Consortium, Inc. ("ISC")
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


#include <dhcp/dhcp6.h>
#include <dhcp/pkt6.h>
#include <dhcp/libdhcp++.h>
#include <exceptions/exceptions.h>
#include <iostream>
#include <sstream>

using namespace std;

namespace isc {
namespace dhcp {

Pkt6::Pkt6(const uint8_t* buf, uint32_t buf_len, DHCPv6Proto proto /* = UDP */) :
    proto_(proto),
    msg_type_(0),
    transid_(rand()%0xffffff),
    iface_(""),
    ifindex_(-1),
    local_addr_("::"),
    remote_addr_("::"),
    local_port_(0),
    remote_port_(0),
    bufferOut_(0) {
    data_.resize(buf_len);
    memcpy(&data_[0], buf, buf_len);
}

Pkt6::Pkt6(uint8_t msg_type, uint32_t transid, DHCPv6Proto proto /*= UDP*/) :
    proto_(proto),
    msg_type_(msg_type),
    transid_(transid),
    iface_(""),
    ifindex_(-1),
    local_addr_("::"),
    remote_addr_("::"),
    local_port_(0),
    remote_port_(0),
    bufferOut_(0) {
}

uint16_t Pkt6::len() {
    uint16_t length = DHCPV6_PKT_HDR_LEN; // DHCPv6 header

    for (Option::OptionCollection::iterator it = options_.begin();
         it != options_.end();
         ++it) {
        length += (*it).second->len();
    }

    return (length);
}


bool
Pkt6::pack() {
    switch (proto_) {
    case UDP:
        return packUDP();
    case TCP:
        return packTCP();
    default:
        isc_throw(BadValue, "Invalid protocol specified (non-TCP, non-UDP)");
    }
    return (false); // never happens
}

bool
Pkt6::packUDP() {

    // TODO: Once OutputBuffer is used here, some thing like this
    // will be used. Yikes! That's ugly.
    // bufferOut_.writeData(ciaddr_.getAddress().to_v6().to_bytes().data(), 16);
    // It is better to implement a method in IOAddress that extracts
    // vector<uint8_t>

    try {
        // DHCPv6 header: message-type (1 octect) + transaction id (3 octets)
        bufferOut_.writeUint8(msg_type_);
        // store 3-octet transaction-id
        bufferOut_.writeUint8( (transid_ >> 16) & 0xff );
        bufferOut_.writeUint8( (transid_ >> 8) & 0xff );
        bufferOut_.writeUint8( (transid_) & 0xff );

        // the rest are options
        LibDHCP::packOptions6(bufferOut_, options_);
    }
    catch (const Exception& e) {
        /// @todo: throw exception here once we turn this function to void.
        return (false);
    }
    return (true);
}

bool
Pkt6::packTCP() {
    /// TODO Implement this function.
    isc_throw(Unexpected, "DHCPv6 over TCP (bulk leasequery and failover)"
              "not implemented yet.");
}

bool
Pkt6::unpack() {
    switch (proto_) {
    case UDP:
        return unpackUDP();
    case TCP:
        return unpackTCP();
    default:
        isc_throw(BadValue, "Invalid protocol specified (non-TCP, non-UDP)");
    }
    return (false); // never happens
}

bool
Pkt6::unpackUDP() {
    if (data_.size() < 4) {
        // @todo: throw exception here informing that packet is truncated
        // once we turn this function to void.
        return (false);
    }
    msg_type_ = data_[0];
    transid_ = ( (data_[1]) << 16 ) +
        ((data_[2]) << 8) + (data_[3]);
    transid_ = transid_ & 0xffffff;

    try {
        OptionBuffer opt_buffer(data_.begin() + 4, data_.end());

        LibDHCP::unpackOptions6(opt_buffer, options_);
    } catch (const Exception& e) {
        // @todo: throw exception here once we turn this function to void.
        return (false);
    }
    return (true);
}

bool
Pkt6::unpackTCP() {
    isc_throw(Unexpected, "DHCPv6 over TCP (bulk leasequery and failover) "
              "not implemented yet.");
}


std::string
Pkt6::toText() {
    stringstream tmp;
    tmp << "localAddr=[" << local_addr_.toText() << "]:" << local_port_
        << " remoteAddr=[" << remote_addr_.toText()
        << "]:" << remote_port_ << endl;
    tmp << "msgtype=" << msg_type_ << ", transid=0x" << hex << transid_
        << dec << endl;
    for (isc::dhcp::Option::OptionCollection::iterator opt=options_.begin();
         opt != options_.end();
         ++opt) {
        tmp << opt->second->toText() << std::endl;
    }
    return tmp.str();
}

boost::shared_ptr<isc::dhcp::Option>
Pkt6::getOption(uint16_t opt_type) {
    isc::dhcp::Option::OptionCollection::const_iterator x = options_.find(opt_type);
    if (x!=options_.end()) {
        return (*x).second;
    }
    return boost::shared_ptr<isc::dhcp::Option>(); // NULL
}

void
Pkt6::addOption(boost::shared_ptr<Option> opt) {
    options_.insert(pair<int, boost::shared_ptr<Option> >(opt->getType(), opt));
}

bool
Pkt6::delOption(uint16_t type) {
    isc::dhcp::Option::OptionCollection::iterator x = options_.find(type);
    if (x!=options_.end()) {
        options_.erase(x);
        return (true); // delete successful
    }
    return (false); // can't find option to be deleted
}

void Pkt6::repack() {
    bufferOut_.writeData(&data_[0], data_.size());
}

void
Pkt6::updateTimestamp() {
    timestamp_ = boost::posix_time::microsec_clock::universal_time();
}


} // end of isc::dhcp namespace
} // end of isc namespace
