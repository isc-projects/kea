// Copyright (C) 2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <slaac/nd.h>
#include <slaac/nd_pkt_rs.h>

#include <sstream>

using namespace std;

namespace isc {
namespace slaac {

RSPkt::RSPkt(const isc::asiolink::IOAddress& local_addr,
             const isc::asiolink::IOAddress& remote_addr)
    : NDPkt(local_addr, remote_addr)
{
    type_ = ND_RT_SOL;
}

RSPkt::RSPkt(const uint8_t* buf, uint32_t len,
             const isc::asiolink::IOAddress& local_addr,
             const isc::asiolink::IOAddress& remote_addr)
    : NDPkt(buf, len, local_addr, remote_addr)
{
    unpack();
}

void
RSPkt::pack() {
    try {
        // Make sure that the buffer is empty before we start writing to it.
        buffer_out_.clear();

        // Put type, code, checksum and reserved.
        buffer_out_.writeUint8(type_);
        buffer_out_.writeUint8(code_);
        buffer_out_.writeUint16(0);
        buffer_out_.writeUint32(0);

        // Append options.
        packOptions(buffer_out_, options_);
    } catch(const Exception& ex) {
        // An exception is thrown and message will be written to Logger.
        isc_throw(InvalidOperation, ex.what());
    }
}

void
RSPkt::unpack() {
    // Check length.
    if (data_.size() < RS_MIN_LEN) {
        isc_throw(BadValue, "Received truncated RS packet of size "
                  <<  data_.size() << ", RS header alone has 8 bytes.");
    }

    // Get type (ND_RT_SOL (133)).
    type_ = data_[0];
    if (type_ != ND_RT_SOL) {
        isc_throw(BadValue, "Received RS packet has type "
                  << static_cast<unsigned>(type_)
                  << ", expected " << ND_RT_SOL);
    }

    // Get code (0).
    code_ = data_[1];
    if (code_ != 0) {
        isc_throw(BadValue, "Received RS packet has code "
                  << static_cast<unsigned>(code_) << ", expected 0.");
    }

    // Skip checksum and reserved.

    // Get options.
    unpackOptions(data_, RS_MIN_LEN, options_);
}

string
RSPkt::toText() const
{
    stringstream tmp;

    // First print basic
    tmp << "RS (type=" << static_cast<unsigned>(type_)
        << ", code=" << static_cast<unsigned>(code_)
        << ") localAddr=" << local_addr_
        << ", remoteAddr=" << remote_addr_
        << " on " << iface_
        << "(" << ifindex_
        << ")" << endl;

    // Then print the options.
    printOptions(options_, tmp);

    return (tmp.str());
}

size_t
RSPkt::len() {
    return (RS_MIN_LEN + lenOptions(options_));
}

};
};
