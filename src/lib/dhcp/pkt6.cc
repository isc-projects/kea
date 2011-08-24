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
#include "dhcp/libdhcp.h"
#include "exceptions/exceptions.h"
#include <iostream>
#include <sstream>

using namespace std;
using namespace isc::dhcp;

namespace isc {

/**
 * Constructor.
 *
 * @param dataLen size of buffer to be allocated for this packet.
 * @param proto protocol (usually UDP, but TCP will be supported eventually)
 */
Pkt6::Pkt6(unsigned int dataLen, DHCPv6Proto_ proto /* = UDP */)
    :local_addr_("::"),
     remote_addr_("::"),
     proto_(proto)
{
    try {
        data_ = boost::shared_array<char>(new char[dataLen]);
        data_len_ = dataLen;
    } catch (const std::exception& ex) {
        // TODO move to LOG_FATAL()
        // let's continue with empty pkt for now
        std::cout << "Failed to allocate " << dataLen << " bytes."
                  << std::endl;
        data_len_ = 0;
    }
}


/**
 * Returns calculated length of the packet.
 *
 * This function returns size of required buffer to buld this packet.
 * To use that function, options_ field must be set.
 *
 * @return number of bytes required to build this packet
 */
unsigned short Pkt6::len() {
    unsigned int length = 4; // DHCPv6 header

    for (Option::Option6Lst::iterator it = options_.begin();
         it != options_.end();
         ++it) {
        length += (*it).second->len();
    }

    return (length);
}


/**
 * Builds on wire packet.
 *
 * Prepares on wire packet format.
 *
 * @return true if preparation was successful
 */
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


/**
 * Build on wire packet (in UDP format).
 *
 * @return true if packet build was successful, false otherwise
 */
bool
Pkt6::packUDP() {
    unsigned short length = len();
    if (data_len_ < length) {
        // we have too small buffer, let's allocate bigger one
        data_ = boost::shared_array<char>(new char[length]);
        data_len_ = length;
    }

    // DHCPv6 header: message-type (1 octect) + transaction id (3 octets)
    data_[0] = msg_type_;
    data_[1] = (transid_ >> 16) & 0xff;
    data_[2] = (transid_ >> 8) & 0xff;
    data_[3] = (transid_) & 0xff;

    try {
        // the rest are options
        unsigned short offset = LibDHCP::packOptions6(data_, length, 4/*offset*/, options_);

        // sanity check
        if (offset != length) {
            isc_throw(OutOfRange, "Packet build failed: expected size=" << length
                      << ", actual len=" << offset);
        }
    }
    catch (Exception e) {
        cout << "Packet build failed." << endl;
        return (false);
    }
    cout << "Packet built, len=" << len() << endl;
    return (true);
}


/**
 * Builds on wire packet for TCP transmission.
 *
 * @note This function is not implemented yet.
 *
 * @return
 */
bool
Pkt6::packTCP() {
    /// TODO Implement this function.
    isc_throw(Unexpected, "DHCPv6 over TCP (bulk leasequery and failover) not implemented yet.");
}

/**
 * Dispatch method that handles binary packet parsing.
 *
 * This method calls appropriate dispatch function (unpackUDP or unpackTCP)
 *
 * @return true, if parsing was successful, false otherwise
 */
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

/**
 * This method unpacks UDP packet.
 *
 * @return true, if parsing was successful, false otherwise
 */
bool
Pkt6::unpackUDP() {
    if (data_len_ < 4) {
        std::cout << "DHCPv6 packet truncated. Only " << data_len_
                  << " bytes. Need at least 4." << std::endl;
        return (false);
    }
    msg_type_ = data_[0];
    transid_ = (data_[1] << 16) + (data_[2] << 8) + data_[3];

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

/**
 * This method unpacks TDP packet.
 *
 * @return true, if parsing was successful, false otherwise
 */
bool
Pkt6::unpackTCP() {
    isc_throw(Unexpected, "DHCPv6 over TCP (bulk leasequery and failover) not implemented yet.");
}


/**
 * Returns text representation of the packet.
 *
 * This function is useful mainly for debugging.
 *
 * @return string with text representation
 */
std::string
Pkt6::toText() {
    stringstream tmp;
    tmp << "msgtype=" << msg_type_ << ", transid=0x" << hex << transid_
        << dec << endl;
    for (isc::dhcp::Option::Option6Lst::iterator opt=options_.begin();
         opt != options_.end();
         ++opt) {
        tmp << opt->second->toText() << std::endl;
    }
    return tmp.str();
}

/**
 * Returns the first option of specified type.
 *
 * Returns the first option of specified type. Note that in DHCPv6 several
 * instances of the same option are allowed (and frequently used).
 * See getOptions().
 *
 * @param opt_type option type we are looking for
 *
 * @return pointer to found option (or NULL)
 */
boost::shared_ptr<isc::dhcp::Option>
Pkt6::getOption(unsigned short opt_type) {
    isc::dhcp::Option::Option6Lst::const_iterator x = options_.find(opt_type);
    if (x!=options_.end()) {
        return (*x).second;
    }
    return boost::shared_ptr<isc::dhcp::Option>(); // NULL
}

/**
 * Returns message type.
 *
 * @return message type.
 */
unsigned char
Pkt6::getType() {
    return (msg_type_);
}

Pkt6::~Pkt6() {
    // no need to delete anything shared_ptr will take care of data_
}

};
