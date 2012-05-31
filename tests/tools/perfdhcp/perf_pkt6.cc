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

#include <iostream>
#include <exceptions/exceptions.h>
#include <dhcp/libdhcp++.h>
#include <dhcp/dhcp6.h>

#include "perf_pkt6.h"

using namespace std;
using namespace isc;
using namespace dhcp;

namespace isc {
namespace perfdhcp {

PerfPkt6::PerfPkt6(const uint8_t* buf, uint32_t len,
                   uint32_t transid, const Offset& transid_offset) :
    Pkt6(buf, len, Pkt6::UDP),
    transid_offset_(transid_offset.get()) {
    transid_ = transid;
}

PerfPkt6::PerfPkt6(const uint8_t* buf,
                   uint32_t len,
                   const Offset&
                   transid_offset) :
    Pkt6(buf, len, Pkt6::UDP),
    transid_offset_(transid_offset.get()) {
}

bool
PerfPkt6::rawPack() {
    // Always override the packet if function is called.
    bufferOut_.clear();
    // Write whole buffer to output buffer.
    bufferOut_.writeData(&data_[0], data_.size());

    if ((transid_offset_ + 4 > data_.size()) ||
        (transid_offset_ == 0)) {
        cout << "Failed to build packet: provided transaction id offset: "
             << transid_offset_ <<  " is out of bounds (expected 1.."
             << data_.size()-1 << ")." << endl;
        return (false);
    }

    // Seek to the transaction id position in output buffer.
    bufferOut_.clear();
    bufferOut_.skip(transid_offset_);

    try {
        // Write 3 octets of transaction id
        bufferOut_.writeUint8(transid_ >> 16 & 0xFF);
        bufferOut_.writeUint8(transid_ >> 8 & 0xFF);
        bufferOut_.writeUint8(transid_ & 0xFF);

        // Buffer pointer is at the end of transaction id.
        // We have to seek to the end of buffer so as data don't
        // get truncated.
        bufferOut_.skip(data_.size() - bufferOut_.getLength());

        // We already have packet template stored in output buffer
        // but still some options have to be updated if client
        // specified them along with their offsets in the buffer.
        rawPackOptions();
    } catch (isc::BadValue& e) {
        cout << "Building packet failed: " << e.what() << endl;
        return (false);
    }
    return (true);
}

bool
PerfPkt6::rawUnpack() {
    // Validate transaction id offset.
    if ((transid_offset_ + 4 > data_.size()) ||
        (transid_offset_ == 0)) {
        cout << "Failed to parse packet: provided transaction id offset: "
             << transid_offset_ <<  " is out of bounds (expected 1.."
             << data_.size()-1 << ")." << endl;
        return (false);
    }

    // Read transaction id from the packet at the given offset.
    transid_ = ( (data_[transid_offset_]) << 16 ) +
        ((data_[transid_offset_ + 1]) << 8) + (data_[transid_offset_ + 2]);
    transid_ = transid_ & 0xffffff;

    // Get message type - assume it is first octet in the packet.
    msg_type_ = data_[0];
    try {
        rawUnpackOptions();
    } catch (isc::BadValue& e) {
        cout << "Packet parsing failed: " << e.what() << endl;
        return (false);
    }
    return (true);
}


void
PerfPkt6::rawPackOptions() {
    try {
        // If there are any options on the list, we will use provided
        // options offsets to override them in the output buffer
        // with new contents.
        for (Option::OptionCollection::const_iterator it = options_.begin();
             it != options_.end(); ++it) {
            // Get options with their position (offset).
            boost::shared_ptr<LocalizedOption> option =
                boost::dynamic_pointer_cast<LocalizedOption>(it->second);
            uint32_t offset = option->getOffset();
            if ((offset == 0) ||
                (offset + option->len() > data_.size())) {
                isc_throw(isc::BadValue,
                          "option offset for option: " << option->getType()
                          << " is out of bounds (expected 1.."
                          << data_.size() - option->len() << ")");
            }
            bufferOut_.clear();
            bufferOut_.skip(offset);

            // Replace existing option with new value.
            option->pack(bufferOut_);
        }
        // Seek to the end of the buffer to make sure its size is correct.
        bufferOut_.skip(data_.size() - bufferOut_.getLength());
    }
    catch (const Exception&) {
        isc_throw(isc::BadValue, "failed to pack options into buffer.");
    }
}

void
PerfPkt6::rawUnpackOptions() {
    for (Option::OptionCollection::const_iterator it = options_.begin();
         it != options_.end(); ++it) {

        LocalizedOptionPtr option =
            boost::dynamic_pointer_cast<LocalizedOption>(it->second);
        size_t opt_pos = option->getOffset();
        if (opt_pos == 0) {
            isc_throw(isc::BadValue, "failed to unpack packet from raw buffer "
                      "(Option position not specified)");
        } else if (opt_pos + 4 > data_.size()) {
            isc_throw(isc::BadValue,
                      "failed to unpack options from from raw buffer "
                      "(Option position out of bounds)");
        }

        size_t offset = opt_pos;

        // Get option type from first two octets.
        uint16_t opt_type = data_[offset] * 256 + data_[offset + 1];
        if (opt_type != option->getType()) {
            isc_throw(isc::BadValue,
                      "failed to unpack option from raw buffer "
                      "(option type mismatch)");
        }

        // Get length from next two octets.
        offset += 2;
        uint16_t opt_len = data_[offset] * 256 + data_[offset + 1];

        if (offset + opt_len > data_.size()) {
            isc_throw(isc::BadValue,
                      "failed to unpack option from raw buffer "
                      "(option truncated)");
        }

        // Seek to actual option data and replace it.
        offset += 2;
        option->setData(data_.begin() + offset,
                        data_.begin() + offset + opt_len);
    }
}

} // namespace perfdhcp
} // namespace isc
