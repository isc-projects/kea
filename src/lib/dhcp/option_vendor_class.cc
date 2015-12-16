// Copyright (C) 2014-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <exceptions/exceptions.h>
#include <dhcp/opaque_data_tuple.h>
#include <dhcp/option_vendor_class.h>
#include <sstream>

namespace isc {
namespace dhcp {

OptionVendorClass::OptionVendorClass(Option::Universe u,
                                     const uint32_t vendor_id)
    : Option(u, getOptionCode(u)), vendor_id_(vendor_id) {
    if (u == Option::V4) {
        addTuple(OpaqueDataTuple(OpaqueDataTuple::LENGTH_1_BYTE));
    }
}

    OptionVendorClass::OptionVendorClass(Option::Universe u,
                                         OptionBufferConstIter begin,
                                         OptionBufferConstIter end)
    : Option(u, getOptionCode(u)) {
    unpack(begin, end);
}

void
OptionVendorClass::pack(isc::util::OutputBuffer& buf) {
    packHeader(buf);

    buf.writeUint32(getVendorId());

    for (TuplesCollection::const_iterator it = tuples_.begin();
         it != tuples_.end(); ++it) {
        // For DHCPv4 V-I Vendor Class option, there is enterprise id before
        // every tuple.
        if ((getUniverse() == V4) && (it != tuples_.begin())) {
            buf.writeUint32(getVendorId());
        }
        it->pack(buf);

    }

}

void
OptionVendorClass::unpack(OptionBufferConstIter begin,
                          OptionBufferConstIter end) {
    if (std::distance(begin, end) < getMinimalLength() - getHeaderLen()) {
        isc_throw(OutOfRange, "parsed Vendor Class option data truncated to"
                  " size " << std::distance(begin, end));
    }
    // Option must contain at least one enterprise id. It is ok to read 4-byte
    // value here because we have checked that the buffer he minimal length.
    vendor_id_ = isc::util::readUint32(&(*begin), distance(begin, end));
    begin += sizeof(vendor_id_);

    // Start reading opaque data.
    size_t offset = 0;
    while (offset < std::distance(begin, end)) {
        // Parse a tuple.
        OpaqueDataTuple tuple(getLengthFieldType(), begin + offset, end);
        addTuple(tuple);
        // The tuple has been parsed correctly which implies that it is safe to
        // advance the offset by its total length.
        offset += tuple.getTotalLength();
        // For DHCPv4 option, there is enterprise id before every opaque data
        // tuple. Let's read it, unless we have already reached the end of
        // buffer.
        if ((getUniverse() == V4) && (begin + offset != end)) {
            // Advance the offset by the size of enterprise id.
            offset += sizeof(vendor_id_);
            // If the offset already ran over the buffer length or there is
            // no space left for the empty tuple (thus we add 1), we have
            // to signal the option truncation.
            if (offset + 1 >= std::distance(begin, end)) {
                isc_throw(isc::OutOfRange, "truncated DHCPv4 V-I Vendor Class"
                          " option - it should contain enterprise id followed"
                          " by opaque data field tuple");
            }
        }
    }
}

void
OptionVendorClass::addTuple(const OpaqueDataTuple& tuple) {
    if (tuple.getLengthFieldType() != getLengthFieldType()) {
        isc_throw(isc::BadValue, "attempted to add opaque data tuple having"
                  " invalid size of the length field "
                  << tuple.getDataFieldSize() << " to Vendor Class option");
    }

    tuples_.push_back(tuple);
}


void
OptionVendorClass::setTuple(const size_t at, const OpaqueDataTuple& tuple) {
    if (at >= getTuplesNum()) {
        isc_throw(isc::OutOfRange, "attempted to set an opaque data for the"
                  " vendor option at position " << at << " which is out of"
                  " range");

    } else if (tuple.getLengthFieldType() != getLengthFieldType()) {
        isc_throw(isc::BadValue, "attempted to set opaque data tuple having"
                  " invalid size of the length field "
                  << tuple.getDataFieldSize() << " to Vendor Class option");
    }

    tuples_[at] = tuple;
}

OpaqueDataTuple
OptionVendorClass::getTuple(const size_t at) const {
    if (at >= getTuplesNum()) {
        isc_throw(isc::OutOfRange, "attempted to get an opaque data for the"
                  " vendor option at position " << at << " which is out of"
                  " range. There are only " << getTuplesNum() << " tuples");
    }
    return (tuples_[at]);
}

bool
OptionVendorClass::hasTuple(const std::string& tuple_str) const {
    // Iterate over existing tuples (there shouldn't be many of them),
    // and try to match the searched one.
    for (TuplesCollection::const_iterator it = tuples_.begin();
         it != tuples_.end(); ++it) {
        if (*it == tuple_str) {
            return (true);
        }
    }
    return (false);
}


uint16_t
OptionVendorClass::len() {
    // The option starts with the header and enterprise id.
    uint16_t length = getHeaderLen() + sizeof(uint32_t);
    // Now iterate over existing tuples and add their size.
    for (TuplesCollection::const_iterator it = tuples_.begin();
         it != tuples_.end(); ++it) {
        // For DHCPv4 V-I Vendor Class option, there is enterprise id before
        // every tuple.
        if ((getUniverse() == V4) && (it != tuples_.begin())) {
            length += sizeof(uint32_t);
        }
        length += it->getTotalLength();

    }

    return (length);
}

std::string
OptionVendorClass::toText(int indent) {
    std::ostringstream s;

    // Apply indentation
    s << std::string(indent, ' ');
    // Print type, length and first occurence of enterprise id.
    s << "type=" << getType() << ", len=" << len() - getHeaderLen() << ", "
        " enterprise id=0x" << std::hex << getVendorId() << std::dec;
    // Iterate over all tuples and print their size and contents.
    for (unsigned i = 0; i < getTuplesNum(); ++i) {
        // The DHCPv4 V-I Vendor Class has enterprise id before every tuple.
        if ((getUniverse() == V4) && (i > 0)) {
            s << ", enterprise id=0x" << std::hex << getVendorId() << std::dec;
        }
        // Print the tuple.
        s << ", data-len" << i << "=" << getTuple(i).getLength();
        s << ", vendor-class-data" << i << "='" << getTuple(i) << "'";
    }

    return (s.str());
}

} // namespace isc::dhcp
} // namespace isc
