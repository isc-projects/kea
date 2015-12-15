// Copyright (C) 2010, 2015  Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

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
