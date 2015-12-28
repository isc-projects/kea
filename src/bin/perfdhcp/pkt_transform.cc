// Copyright (C) 2012-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

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
                   const OptionCollection& options,
                   const size_t transid_offset,
                   const uint32_t transid,
                   util::OutputBuffer& out_buffer) {

    // Always override the packet if function is called.
    out_buffer.clear();
    // Write whole buffer to output buffer.
    out_buffer.writeData(&in_buffer[0], in_buffer.size());

    uint8_t transid_len = (universe == Option::V6) ? 3 : 4;

    if ((transid_offset + transid_len >= in_buffer.size()) ||
        (transid_offset == 0)) {
        cout << "Failed to build packet: provided transaction id offset: "
             << transid_offset <<  " is out of bounds (expected 1.."
             << in_buffer.size()-1 << ")." << endl;
        return (false);
    }

    try {
        size_t offset_ptr = transid_offset;
        if (universe == Option::V4) {
            out_buffer.writeUint8At(transid >> 24 & 0xFF, offset_ptr++);
        }
        out_buffer.writeUint8At(transid >> 16 & 0xFF, offset_ptr++);
        out_buffer.writeUint8At(transid >> 8 & 0xFF, offset_ptr++);
        out_buffer.writeUint8At(transid & 0xFF, offset_ptr++);

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
                     const OptionCollection& options,
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

    // Read transaction id from the buffer.
    // For DHCPv6 we transaction id is 3 bytes long so the high byte
    // of transid will be zero.
    OptionBufferConstIter it = in_buffer.begin() + transid_offset;
    transid = 0;
    for (int i = 0; i < transid_len; ++i, ++it) {
        // Read next byte and shift it left to its position in
        // transid (shift by the number of bytes read so far.
        transid += *it << (transid_len - i - 1) * 8;
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
                          const OptionCollection& options,
                          util::OutputBuffer& out_buffer) {
    try {
        // If there are any options on the list, we will use provided
        // options offsets to override them in the output buffer
        // with new contents.
        for (OptionCollection::const_iterator it = options.begin();
             it != options.end(); ++it) {
            // Get options with their position (offset).
            boost::shared_ptr<LocalizedOption> option =
                boost::dynamic_pointer_cast<LocalizedOption>(it->second);
            if (option == NULL) {
                isc_throw(isc::BadValue, "option is null");
            }
            uint32_t offset = option->getOffset();
            if ((offset == 0) ||
                (offset + option->len() > in_buffer.size())) {
                isc_throw(isc::BadValue,
                          "option offset for option: " << option->getType()
                          << " is out of bounds (expected 1.."
                          << in_buffer.size() - option->len() << ")");
            }

            // Create temporary buffer to store option contents.
            util::OutputBuffer buf(option->len());
            // Pack option contents into temporary buffer.
            option->pack(buf);
            // OutputBuffer class has nice functions that write
            // data at the specified position so we can use it to
            // inject contents of temporary buffer to output buffer.
            const uint8_t *buf_data =
                static_cast<const uint8_t*>(buf.getData());
            for (size_t i = 0; i < buf.getLength(); ++i) {
                out_buffer.writeUint8At(buf_data[i], offset + i);
            }
        }
    }
    catch (const Exception&) {
        isc_throw(isc::BadValue, "failed to pack options into buffer.");
    }
}

void
PktTransform::unpackOptions(const OptionBuffer& in_buffer,
                            const OptionCollection& options) {
    for (OptionCollection::const_iterator it = options.begin();
         it != options.end(); ++it) {

        boost::shared_ptr<LocalizedOption> option =
            boost::dynamic_pointer_cast<LocalizedOption>(it->second);
        if (option == NULL) {
            isc_throw(isc::BadValue, "option is null");
        }
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
        const uint16_t opt_len =
            (option->getUniverse() == Option::V6) ?
            in_buffer[offset] * 256 + in_buffer[offset + 1] :
            in_buffer[offset];

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

void
PktTransform::writeAt(dhcp::OptionBuffer& in_buffer, size_t dest_pos,
                      dhcp::OptionBuffer::iterator first,
                      dhcp::OptionBuffer::iterator last) {
    memcpy(&in_buffer[dest_pos], &(*first), std::distance(first, last));
}

} // namespace perfdhcp
} // namespace isc
