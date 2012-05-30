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

#include <exceptions/exceptions.h>
#include <dhcp/libdhcp++.h>
#include <dhcp/dhcp6.h>

#include "perf_pkt6.h"

using namespace std;
using namespace isc;

namespace isc {
namespace perfdhcp {


PerfPkt6::PositionedOption::PositionedOption(dhcp::Option::Universe u,
                                             uint16_t type,
                                             const dhcp::OptionBuffer& data) :
    dhcp::Option(u, type, data),
    position_(0) {
}

PerfPkt6::PositionedOption::PositionedOption(dhcp::Option::Universe u,
                                             uint16_t type,
                                             const dhcp::OptionBuffer& data,
                                             const size_t position) :
    dhcp::Option(u, type, data),
    position_(position) {
}

PerfPkt6::PositionedOption::PositionedOption(dhcp::Option::Universe u,
                                             uint16_t type,
                                             dhcp::OptionBufferConstIter first,
                                             dhcp::OptionBufferConstIter last) :
    dhcp::Option(u, type, first, last),
    position_(0) {
}

PerfPkt6::PositionedOption::PositionedOption(dhcp::Option::Universe u,
                                             uint16_t type,
                                             dhcp::OptionBufferConstIter first,
                                             dhcp::OptionBufferConstIter last,
                                             const size_t position) :
    dhcp::Option(u, type, first, last),
    position_(position) {
}

PerfPkt6::PerfPkt6(const uint8_t* buf, uint32_t len, size_t transid_offset) :
    Pkt6(buf, len, dhcp::Pkt6::UDP),
    transid_offset_(transid_offset) {

    // Let's reset timestamp of the packet
    memset(static_cast<void*>(&time_stamp_), 0, sizeof(time_stamp_));
}

void
PerfPkt6::stampedPack() {
    // This function simply wraps pack() function from parent class
    // and then updates timestamp.
    if (!pack()) {
        isc_throw(isc::Unexpected, "Failed to prepare packet to send");
    }
    // Update pack time for RTT calculations.
    updateTimestamp();
}

void
PerfPkt6::stampedUnpack() {
    // Update timestamp of the packet for RTT calculations.
    // We do this before unpacking the packet so as unpack
    // time will not affect the timestamp.
    updateTimestamp();

    // Unpack the incoming packet.
    if (!unpack()) {
        isc_throw(isc::Unexpected, "Failed to unpack incoming packet");
    }
}

void
PerfPkt6::stampedRawPack() {
    try {
        // Always override the packet if function is called.
        bufferOut_.clear();
        // Write whole buffer to output buffer.
        bufferOut_.writeData(&data_[0], data_.size());
        // We already have packet template stored in out buffer
        // but still some options have to be updated if client
        // specified them along with their offsets in the buffer.
        updateOptions();
    } catch (Exception& e) {
        isc_throw(isc::Unexpected, "Failed to build packet from buffer");
    }
    // Update packet timestamp for RTT calculations - do not include pack time.
    updateTimestamp();
}

void
PerfPkt6::stampedRawUnpack() {
    // Update packet timestamp for RTT calculations but do not include unpack time.
    updateTimestamp();

    // Read transaction id from the packet at the given offset.
    transid_ = ( (data_[transid_offset_]) << 16 ) +
        ((data_[transid_offset_ + 1]) << 8) + (data_[transid_offset_ + 2]);
    transid_ = transid_ & 0xffffff;

    // Get message type - assume it is first octet in the packet.
    msg_type_ = data_[0];

    rawUnpackOptions();
}


void
PerfPkt6::updateOptions() {
    try {
        // If there are any options on the list we will use provided options offsets
        // to override them in the output buffer with new contents.
        for (dhcp::Option::OptionCollection::const_iterator it = options_.begin();
             it != options_.end(); ++it) {
            // Get options with their position (offset).
            boost::shared_ptr<PositionedOption> option = boost::dynamic_pointer_cast<PositionedOption>(it->second);
            uint32_t position = option->getOptionPosition();
            // If position is specified w need to seek to it.
            if (position > 0) {
                bufferOut_.clear();
                bufferOut_.skip(position);
            }
            // Replace existing option with new value.
            option->pack(bufferOut_);
        }
    }
    catch (const Exception&) {
        isc_throw(isc::Unexpected, "Failed to build packet (Option build failed");
    }
}

void
PerfPkt6::rawUnpackOptions() {
    for (dhcp::Option::OptionCollection::const_iterator it = options_.begin();
         it != options_.end(); ++it) {

        PositionedOptionPtr option = boost::dynamic_pointer_cast<PositionedOption>(it->second);
        size_t opt_pos = option->getOptionPosition();

        if (opt_pos == 0) {
            isc_throw(isc::BadValue, "Failed to unpack packet from raw buffer "
                      "(Option position not specified)");
        } else if (opt_pos + 4 > data_.size()) {
            isc_throw(isc::BadValue, "Failed to unpack options from from raw buffer "
                      "(Option position out of bounds)");
        }

        size_t offset = opt_pos;
        //        uint16_t opt_type = data_[offset] * 256 + data_[offset + 1];
        offset += 2;
        uint16_t opt_len = data_[offset] * 256 + data_[offset + 1];
        offset += 2;

        if (offset + opt_len > data_.size()) {
            isc_throw(isc::BadValue,
                      "Failed to unpack option from raw buffer (Option truncated)");
        }
        option->setData(data_.begin() + offset, data_.begin() + offset + opt_len);
    }
}

void
PerfPkt6::updateTimestamp() {
    if (clock_gettime(CLOCK_REALTIME, &time_stamp_) < 0) {
        isc_throw(isc::Unexpected, "Failed to get timestamp for packet");
    }
}

} // namespace perfdhcp
} // namespace isc
