// Copyright (C) 2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <slaac/nd.h>
#include <slaac/nd_pkt_ra.h>

#include <sstream>

using namespace std;
using namespace isc;
using namespace isc::util;

namespace isc {
namespace slaac {

RAPkt::RAPkt(const isc::asiolink::IOAddress& local_addr,
             const isc::asiolink::IOAddress& remote_addr)
    : NDPkt(local_addr, remote_addr)
{
    type_ = ND_RT_ADV;
}

RAPkt::RAPkt(const uint8_t* buf, uint32_t len,
             const isc::asiolink::IOAddress& local_addr,
             const isc::asiolink::IOAddress& remote_addr)
    : NDPkt(buf, len, local_addr, remote_addr)
{
    type_ = ND_RT_ADV;
}

void
RAPkt::pack() {
    try {
        // Make sure that the buffer is empty before we start writing to it.
        buffer_out_.clear();

        // Put type, code, checksum and hop limit.
        buffer_out_.writeUint8(type_);
        buffer_out_.writeUint8(code_);
        buffer_out_.writeUint16(0);
        buffer_out_.writeUint8(hop_limit_);

        // Put flags.
        uint8_t flags = 0;
        if (managed_flag_) {
            flags |= MANAGED_FLAG;
        }
        if (other_flag_) {
            flags |= OTHER_FLAG;
        }
        buffer_out_.writeUint8(flags);

        // Put router lifetime, reachable time and retrans timer.
        buffer_out_.writeUint16(router_lifetime_);
        buffer_out_.writeUint32(reachable_time_);
        buffer_out_.writeUint32(retrans_timer_);

        // Append options.
        packOptions(buffer_out_, options_);
    } catch(const Exception& ex) {
        // An exception is thrown and message will be written to Logger.
        isc_throw(InvalidOperation, ex.what());
    }
}

void
RAPkt::unpack() {
    // Check length.
    if (data_.size() < RA_MIN_LEN) {
        isc_throw(BadValue, "Received truncated RA packet of size "
                  <<  data_.size() << ", RA header alone has 16 bytes.");
    }

    // Input buffer (used during message reception).
    InputBuffer buffer(&data_[0], RA_MIN_LEN);

    // Get type (ND_RT_ADV (134)).
    type_ = buffer.readUint8();
    if (type_ != ND_RT_ADV) {
        isc_throw(BadValue, "Received RA packet has type "
                  << static_cast<unsigned>(type_)
                  << ", expected " << ND_RT_ADV);
    }

    // Get code (0).
    code_ = buffer.readUint8();
    if (code_ != 0) {
        isc_throw(BadValue, "Received RA packet has code "
                  << static_cast<unsigned>(code_) << ", expected 0.");
    }

    // Skip checksum.
    static_cast<void>(buffer.readUint16());

    // Get hop limit.
    hop_limit_ = buffer.readUint8();

    // Get flags.
    uint8_t flags = buffer.readUint8();
    managed_flag_ = ((flags & MANAGED_FLAG) != 0);
    other_flag_ = ((flags & OTHER_FLAG) != 0);

    // Get router lifetime.
    router_lifetime_ = buffer.readUint16();

    // Get reachable time.
    reachable_time_ = buffer.readUint32();

    // Get retrans timer.
    retrans_timer_ = buffer.readUint32();

    // Get options.
    unpackOptions(data_, RA_MIN_LEN, options_);
}

string
RAPkt::toText() const
{
    stringstream tmp;

    // First print basic
    tmp << "RA (type=" << static_cast<unsigned>(type_)
        << ", code=" << static_cast<unsigned>(code_)
        << ") localAddr=" << local_addr_
        << ", remoteAddr=" << remote_addr_
        << " on " << iface_
        << "(" << ifindex_
        << ")" << endl;

    // Then print parameters,
    tmp << "hop_limit=" << static_cast<unsigned>(hop_limit_)
        << " flags=" << (managed_flag_ ? "M" : "") << (other_flag_ ? "O" : "")
        << " router_lifetime=" << router_lifetime_ << endl
        << "reachable_time=" << reachable_time_
        << " retrans_timer=" << retrans_timer_ << endl;

    // Finally print the options.
    if (!options_.empty()) {
        tmp << "options:" << endl;
        printOptions(options_, 1, tmp);
    }

    return (tmp.str());
}

size_t
RAPkt::len() {
    return (RA_MIN_LEN + lenOptions(options_));
}

};
};
