// Copyright (C) 2013 Internet Systems Consortium, Inc. ("ISC")
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

#include <dhcp/dhcp4.h>
#include <dhcp/dhcp6.h>
#include <dhcp/option_vendor.h>

using namespace isc::dhcp;

OptionVendor::OptionVendor(Option::Universe u, uint32_t vendor_id)
    :Option(u, u==Option::V4?DHO_VIVSO_SUBOPTIONS:D6O_VENDOR_OPTS), vendor_id_(vendor_id) {
}

OptionVendor::OptionVendor(Option::Universe u, OptionBufferConstIter begin,
                           OptionBufferConstIter end)
    :Option(u, u==Option::V4?DHO_VIVSO_SUBOPTIONS:D6O_VENDOR_OPTS), vendor_id_(0) {
    unpack(begin, end);
}


void OptionVendor::pack(isc::util::OutputBuffer& buf) {
    packHeader(buf);

    buf.writeUint32(vendor_id_);

    packOptions(buf);
}

void OptionVendor::unpack(OptionBufferConstIter begin, OptionBufferConstIter end) {
    if (distance(begin, end) < sizeof(uint32_t)) {
        isc_throw(OutOfRange, "Truncated vendor-specific information option");
    }

    vendor_id_ = isc::util::readUint32(&(*begin));

    OptionBuffer vendor_buffer(begin +4, end);
    
    if (universe_ == Option::V6) {
        LibDHCP::unpackVendorOptions6(vendor_id_, vendor_buffer, options_);
    } else {
        LibDHCP::unpackVendorOptions4(vendor_id_, vendor_buffer, options_);
    }
}

uint16_t OptionVendor::len() {
    uint16_t length = getHeaderLen();

    length += sizeof(uint32_t); // Vendor-id field

    // length of all suboptions
    for (OptionCollection::iterator it = options_.begin();
         it != options_.end();
         ++it) {
        length += (*it).second->len();
    }
    return (length);
}
