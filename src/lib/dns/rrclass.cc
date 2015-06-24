// Copyright (C) 2010, 2015  Internet Systems Consortium, Inc. ("ISC")
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

#include <stdint.h>

#include <string>

#include <exceptions/exceptions.h>

#include <util/buffer.h>
#include <dns/messagerenderer.h>
#include <dns/rrparamregistry.h>
#include <dns/rrclass.h>

using namespace std;
using namespace isc::dns;
using namespace isc::util;

namespace isc {
namespace dns {

RRClass::RRClass(const std::string& class_str) {
    uint16_t classcode;
    if (!RRParamRegistry::getRegistry().textToClassCode(class_str, classcode)) {
        isc_throw(InvalidRRClass,
                  "Unrecognized RR class string: " + class_str);
    }
    classcode_ = classcode;
}

RRClass::RRClass(InputBuffer& buffer) {
    if (buffer.getLength() - buffer.getPosition() < sizeof(uint16_t)) {
        isc_throw(IncompleteRRClass, "incomplete wire-format RR class");
    }
    classcode_ = buffer.readUint16();
}

const string
RRClass::toText() const {
    return (RRParamRegistry::getRegistry().codeToClassText(classcode_));
}

void
RRClass::toWire(OutputBuffer& buffer) const {
    buffer.writeUint16(classcode_);
}

void
RRClass::toWire(AbstractMessageRenderer& renderer) const {
    renderer.writeUint16(classcode_);
}

RRClass*
RRClass::createFromText(const string& class_str) {
    uint16_t class_code;
    if (RRParamRegistry::getRegistry().textToClassCode(class_str,
                                                       class_code)) {
        return (new RRClass(class_code));
    }
    return (NULL);
}

ostream&
operator<<(ostream& os, const RRClass& rrclass) {
    os << rrclass.toText();
    return (os);
}
}
}
