// Copyright (C) 2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <slaac/nd_pkt.h>
#include <dhcp/iface_mgr.h>
#include <vector>

namespace isc {
namespace slaac {

RSPkt::RSPkt(const isc::asiolink::IOAddress& local_addr,
             const isc::asiolink::IOAddress& remote_addr)
    : NDPkt(local_addr, remote_addr), type_(ND_RT_SOL), code_(0)
{
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
	for (OptionCollection::const_iterator it = options_.begin();
	     it != options.end(); ++it) {
	    it->second->pack(buffer_out_);
	}
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
		  << static_cast<unisgned>(type_)
		  << ", expected " << ND_RT_SOL);
    }

    // Get code (0).
    code_ = data_[1];
    if (code_ != 0) {
	isc_throw(BadValue, "Received RS packet has code "
		  << static_cast<unisgned>(code_) << ", expected 0.");
    }

    // Skip checksum and reserved.

    // Get options.
    unpack

};
};
