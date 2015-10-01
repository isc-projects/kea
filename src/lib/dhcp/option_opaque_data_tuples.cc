// Copyright (C) 2015 Internet Systems Consortium, Inc. ("ISC")
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
#include <dhcp/opaque_data_tuple.h>
#include <dhcp/option_opaque_data_tuples.h>
#include <sstream>

namespace isc {
namespace dhcp {

OptionOpaqueDataTuples::OptionOpaqueDataTuples(Option::Universe u,
                                               const uint16_t type)
    : Option(u, type) {
}

OptionOpaqueDataTuples::OptionOpaqueDataTuples(Option::Universe u,
                                               const uint16_t type,
                                               OptionBufferConstIter begin,
                                               OptionBufferConstIter end)
    : Option(u, type) {
    unpack(begin, end);
}

void
OptionOpaqueDataTuples::pack(isc::util::OutputBuffer& buf) {
    packHeader(buf);

    for (TuplesCollection::const_iterator it = tuples_.begin();
         it != tuples_.end(); ++it) {
        it->pack(buf);
    }

}

void
OptionOpaqueDataTuples::unpack(OptionBufferConstIter begin,
                               OptionBufferConstIter end) {
    if (std::distance(begin, end) < getMinimalLength() - getHeaderLen()) {
        isc_throw(OutOfRange, "parsed data tuples option data truncated to"
                  " size " << std::distance(begin, end));
    }

    // Start reading opaque data.
    size_t offset = 0;
    while (offset < std::distance(begin, end)) {
        // Parse a tuple.
        OpaqueDataTuple tuple(getLengthFieldType(), begin + offset, end);
        addTuple(tuple);
        // The tuple has been parsed correctly which implies that it is safe to
        // advance the offset by its total length.
        offset += tuple.getTotalLength();
    }
}

void
OptionOpaqueDataTuples::addTuple(const OpaqueDataTuple& tuple) {
    if (tuple.getLengthFieldType() != getLengthFieldType()) {
        isc_throw(isc::BadValue, "attempted to add opaque data tuple having"
                  " invalid size of the length field "
                  << tuple.getDataFieldSize() << " to Vendor Class option");
    }

    tuples_.push_back(tuple);
}


void
OptionOpaqueDataTuples::setTuple(const size_t at, const OpaqueDataTuple& tuple) {
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
OptionOpaqueDataTuples::getTuple(const size_t at) const {
    if (at >= getTuplesNum()) {
        isc_throw(isc::OutOfRange, "attempted to get an opaque data for the"
                  " vendor option at position " << at << " which is out of"
                  " range. There are only " << getTuplesNum() << " tuples");
    }
    return (tuples_[at]);
}

bool
OptionOpaqueDataTuples::hasTuple(const std::string& tuple_str) const {
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
OptionOpaqueDataTuples::len() {
    // The option starts with the header.
    uint16_t length = getHeaderLen();
    // Now iterate over existing tuples and add their size.
    for (TuplesCollection::const_iterator it = tuples_.begin();
         it != tuples_.end(); ++it) {
        length += it->getTotalLength();
    }

    return (length);
}

std::string
OptionOpaqueDataTuples::toText(int indent) {
    std::ostringstream s;

    // Apply indentation
    s << std::string(indent, ' ');



    // Print type and length
    s << "type=" << getType() << ", len=" << len() - getHeaderLen() << std::dec;
    // Iterate over all tuples and print their size and contents.
    for (unsigned i = 0; i < getTuplesNum(); ++i) {
        // Print the tuple.
        s << ", data-len" << i << "=" << getTuple(i).getLength();
        s << ", data" << i << "='" << getTuple(i) << "'";
    }

    return (s.str());
}

} // namespace isc::dhcp
} // namespace isc
