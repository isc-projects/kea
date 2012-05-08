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


#include "dhcp/dhcp6.h"
#include "dhcp/pkt6.h"
#include "dhcp/libdhcp++.h"
#include "exceptions/exceptions.h"
#include <iostream>
#include <sstream>

using namespace std;
using namespace isc::dhcp;

namespace isc {
namespace dhcp {

Pkt6::Pkt6(unsigned int dataLen, DHCPv6Proto proto /* = UDP */)
    :data_len_(dataLen),
     local_addr_("::"),
     remote_addr_("::"),
     iface_(""),
     ifindex_(-1),
     local_port_(-1),
     remote_port_(-1),
     proto_(proto),
     msg_type_(-1),
     transid_(rand()%0xffffff)
{

    data_ = boost::shared_array<uint8_t>(new uint8_t[dataLen]);
    data_len_ = dataLen;
}

Pkt6::Pkt6(uint8_t msg_type,
           uint32_t transid,
           DHCPv6Proto proto /*= UDP*/)
    :local_addr_("::"),
     remote_addr_("::"),
     iface_(""),
     ifindex_(-1),
     local_port_(0),
     remote_port_(0),
     proto_(proto),
     msg_type_(msg_type),
     transid_(transid) {

    data_ = boost::shared_array<uint8_t>(new uint8_t[4]);
    data_len_ = 4;
}

unsigned short
Pkt6::len() {
    unsigned int length = DHCPV6_PKT_HDR_LEN; // DHCPv6 header

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

    unsigned short length = len();
    if (data_len_ < length) {
        cout << "Previous len=" << data_len_ << ", allocating new buffer: len="
             << length << endl;

        // May throw exception if out of memory. That is rather fatal,
        // so we don't catch this
        data_ = boost::shared_array<uint8_t>(new uint8_t[length]);
        data_len_ = length;
    }

    data_len_ = length;
    try {
        // DHCPv6 header: message-type (1 octect) + transaction id (3 octets)
        data_[0] = msg_type_;

        // store 3-octet transaction-id
        data_[1] = (transid_ >> 16) & 0xff;
        data_[2] = (transid_ >> 8) & 0xff;
        data_[3] = (transid_) & 0xff;

        // the rest are options
        unsigned short offset = LibDHCP::packOptions6(data_, length,
                                                      4/*offset*/,
                                                      options_);

        // sanity check
        if (offset != length) {
            isc_throw(OutOfRange, "Packet build failed: expected size="
                      << length << ", actual len=" << offset);
        }
    }
    catch (const Exception& e) {
        cout << "Packet build failed:" << e.what() << endl;
        return (false);
    }
    // Limited verbosity of this method
    // cout << "Packet built, len=" << len() << endl;
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
    if (data_len_ < 4) {
        std::cout << "DHCPv6 packet truncated. Only " << data_len_
                  << " bytes. Need at least 4." << std::endl;
        return (false);
    }
    msg_type_ = data_[0];
    transid_ = ( (data_[1]) << 16 ) +
        ((data_[2]) << 8) + (data_[3]);
    transid_ = transid_ & 0xffffff;

    unsigned int offset = LibDHCP::unpackOptions6(data_,
                                                  data_len_,
                                                  4, //offset
                                                  data_len_ - 4,
                                                  options_);
    if (offset != data_len_) {
        cout << "DHCPv6 packet contains trailing garbage. Parsed "
             << offset << " bytes, packet is " << data_len_ << " bytes."
             << endl;
        // just a warning. Ignore trailing garbage and continue
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

} // end of isc::dhcp namespace
} // end of isc namespace
