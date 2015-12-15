// Copyright (C) 2013,2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <dhcp/dhcp4.h>
#include <dhcp/dhcp6.h>
#include <dhcp/option_vendor.h>
#include <sstream>

using namespace isc::dhcp;

OptionVendor::OptionVendor(Option::Universe u, const uint32_t vendor_id)
    :Option(u, u==Option::V4?DHO_VIVSO_SUBOPTIONS:D6O_VENDOR_OPTS), vendor_id_(vendor_id) {
}

OptionVendor::OptionVendor(Option::Universe u, OptionBufferConstIter begin,
                           OptionBufferConstIter end)
    :Option(u, u==Option::V4?DHO_VIVSO_SUBOPTIONS:D6O_VENDOR_OPTS), vendor_id_(0) {
    unpack(begin, end);
}


void OptionVendor::pack(isc::util::OutputBuffer& buf) {
    packHeader(buf);

    // Store vendor-id
    buf.writeUint32(vendor_id_);

    // The format is slightly different for v4
    if (universe_ == Option::V4) {
        // Calculate and store data-len as follows:
        // data-len = total option length - header length
        //            - enterprise id field length - data-len field size
        buf.writeUint8(dataLen());
    }

    packOptions(buf);
}

void OptionVendor::unpack(OptionBufferConstIter begin,
                          OptionBufferConstIter end) {
    if (distance(begin, end) < sizeof(uint32_t)) {
        isc_throw(OutOfRange, "Truncated vendor-specific information option"
                  << ", length=" << distance(begin, end));
    }

    vendor_id_ = isc::util::readUint32(&(*begin), distance(begin, end));

    OptionBuffer vendor_buffer(begin + 4, end);

    if (universe_ == Option::V6) {
        LibDHCP::unpackVendorOptions6(vendor_id_, vendor_buffer, options_);
    } else {
        LibDHCP::unpackVendorOptions4(vendor_id_, vendor_buffer, options_);
    }
}

uint16_t OptionVendor::len() {
    uint16_t length = getHeaderLen();

    length += sizeof(uint32_t); // Vendor-id field

    // Data-len field exists in DHCPv4 vendor options only
    if (universe_ == Option::V4) {
        length += sizeof(uint8_t);  // data-len
    }

    // length of all suboptions
    for (OptionCollection::iterator it = options_.begin();
         it != options_.end();
         ++it) {
        length += (*it).second->len();
    }
    return (length);
}

uint8_t
OptionVendor::dataLen() {
    // Calculate and store data-len as follows:
    // data-len = total option length - header length
    //            - enterprise id field length - data-len field size
    return (len() - getHeaderLen() - sizeof(uint32_t) - sizeof(uint8_t));
}

std::string
OptionVendor::toText(int indent) {
    std::stringstream output;
    output << headerToText(indent) << ": "
           << getVendorId() << " (uint32)";

    // For the DHCPv4 there is one more field.
    if (getUniverse() == Option::V4) {
        output << " " << static_cast<int>(dataLen()) << " (uint8)";
    }

    // Append suboptions.
    output << suboptionsToText(indent + 2);

    return (output.str());
}
