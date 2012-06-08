// Copyright (C) 2012 Internet Systems Consortium, Inc. ("ISC")
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
#include <dhcp/option.h>
#include <dhcp/libdhcp++.h>
#include <dhcp/dhcp6.h>

#include "pkt_transform.h"
#include "localized_option.h"

using namespace std;
using namespace isc;
using namespace dhcp;

namespace isc {
namespace perfdhcp {

bool
PktTransform::pack(const Option::Universe universe,
                   const OptionBuffer& in_buffer,
                   const Option::OptionCollection& options,
                   const size_t transid_offset,
                   const uint32_t transid,
                   util::OutputBuffer& out_buffer) {

    // Always override the packet if function is called.
    out_buffer.clear();
    // Write whole buffer to output buffer.
    out_buffer.writeData(&in_buffer[0], in_buffer.size());

    uint8_t transid_len = (universe == Option::V6) ? 3 : 4;

    if ((transid_offset + transid_len + 1 > in_buffer.size()) ||
        (transid_offset == 0)) {
        cout << "Failed to build packet: provided transaction id offset: "
             << transid_offset <<  " is out of bounds (expected 1.."
             << in_buffer.size()-1 << ")." << endl;
        return (false);
    }

    // Seek to the transaction id position in output buffer.
    out_buffer.clear();
    out_buffer.skip(transid_offset);

    try {
        if (universe == Option::V4) {
            out_buffer.writeUint8(transid >> 24 & 0xFF);
        }
        out_buffer.writeUint8(transid >> 16 & 0xFF);
        out_buffer.writeUint8(transid >> 8 & 0xFF);
        out_buffer.writeUint8(transid & 0xFF);

        // Buffer pointer is at the end of transaction id.
        // We have to seek to the end of buffer so as data don't
        // get truncated.
        out_buffer.skip(in_buffer.size() - out_buffer.getLength());

        // We already have packet template stored in output buffer
        // but still some options have to be updated if client
        // specified them along with their offsets in the buffer.
        PktTransform::packOptions(in_buffer, options, out_buffer);
    } catch (const isc::BadValue& e) {
        cout << "Building packet failed: " << e.what() << endl;
        return (false);
    }
    return (true);
}

bool
PktTransform::unpack(const Option::Universe universe,
                     const OptionBuffer& in_buffer,
                     const Option::OptionCollection& options,
                     const size_t transid_offset,
                     uint32_t& transid) {

    uint8_t transid_len = (universe == Option::V6) ? 3 : 4;

    // Validate transaction id offset.
    if ((transid_offset + transid_len + 1 > in_buffer.size()) ||
        (transid_offset == 0)) {
        cout << "Failed to parse packet: provided transaction id offset: "
             << transid_offset <<  " is out of bounds (expected 1.."
             << in_buffer.size()-1 << ")." << endl;
        return (false);
    }

    if (universe == Option::V6) {
        transid = ((in_buffer[transid_offset] << 16) +
                   (in_buffer[transid_offset + 1] << 8) +
                   (in_buffer[transid_offset + 2]))
            & 0xFFFFFF;
    } else {
        transid = ((in_buffer[transid_offset] << 24) +
                   (in_buffer[transid_offset + 1] << 16) +
                   (in_buffer[transid_offset + 2] << 8) +
                   (in_buffer[transid_offset + 3]));
    }

    try {
        PktTransform::unpackOptions(in_buffer, options);
    } catch (const isc::BadValue& e) {
        cout << "Packet parsing failed: " << e.what() << endl;
        return (false);
    }

    return (true);
}

void
PktTransform::packOptions(const OptionBuffer& in_buffer,
                          const Option::OptionCollection& options,
                          util::OutputBuffer& out_buffer) {
    try {
        // If there are any options on the list, we will use provided
        // options offsets to override them in the output buffer
        // with new contents.
        for (Option::OptionCollection::const_iterator it = options.begin();
             it != options.end(); ++it) {
            // Get options with their position (offset).
            boost::shared_ptr<LocalizedOption> option =
                boost::dynamic_pointer_cast<LocalizedOption>(it->second);
            uint32_t offset = option->getOffset();
            if ((offset == 0) ||
                (offset + option->len() > in_buffer.size())) {
                isc_throw(isc::BadValue,
                          "option offset for option: " << option->getType()
                          << " is out of bounds (expected 1.."
                          << in_buffer.size() - option->len() << ")");
            }
            out_buffer.clear();
            out_buffer.skip(offset);

            // Replace existing option with new value.
            option->pack(out_buffer);
        }
        // Seek to the end of the buffer to make sure its size is correct.
        out_buffer.skip(in_buffer.size() - out_buffer.getLength());
    }
    catch (const Exception&) {
        isc_throw(isc::BadValue, "failed to pack options into buffer.");
    }
}

void
PktTransform::unpackOptions(const OptionBuffer& in_buffer,
                            const Option::OptionCollection& options) {
    for (Option::OptionCollection::const_iterator it = options.begin();
         it != options.end(); ++it) {

        boost::shared_ptr<LocalizedOption> option =
            boost::dynamic_pointer_cast<LocalizedOption>(it->second);
        size_t opt_pos = option->getOffset();
        if (opt_pos == 0) {
            isc_throw(isc::BadValue, "failed to unpack packet from raw buffer "
                      "(Option position not specified)");
        } else if (opt_pos + option->getHeaderLen() > in_buffer.size()) {
            isc_throw(isc::BadValue,
                      "failed to unpack options from from raw buffer "
                      "(Option position out of bounds)");
        }

        size_t offset = opt_pos;
        size_t offset_step = 1;
        uint16_t opt_type = 0;
        if (option->getUniverse() == Option::V6) {
            offset_step = 2;
            // For DHCPv6 option type is in first two octets.
            opt_type = in_buffer[offset] * 256 + in_buffer[offset + 1];
        } else {
            // For DHCPv4 option type is in first octet.
            opt_type = in_buffer[offset];
        }
        // Check if we got expected option type.
        if (opt_type != option->getType()) {
            isc_throw(isc::BadValue,
                      "failed to unpack option from raw buffer "
                      "(option type mismatch)");
        }

        // Get option length which is supposed to be after option type.
        offset += offset_step;
        uint16_t opt_len = in_buffer[offset] * 256 + in_buffer[offset + 1];
        if (option->getUniverse() == Option::V6) {
            opt_len = in_buffer[offset] * 256 + in_buffer[offset + 1];
        } else {
            opt_len = in_buffer[offset];
        }

        // Check if packet is not truncated.
        if (offset + option->getHeaderLen() + opt_len > in_buffer.size()) {
            isc_throw(isc::BadValue,
                      "failed to unpack option from raw buffer "
                      "(option truncated)");
        }

        // Seek to actual option data and replace it.
        offset += offset_step;
        option->setData(in_buffer.begin() + offset,
                        in_buffer.begin() + offset + opt_len);
    }
}


} // namespace perfdhcp
} // namespace isc
