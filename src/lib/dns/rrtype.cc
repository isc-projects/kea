// Copyright (C) 2010-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <stdint.h>

#include <string>
#include <ostream>

#include <exceptions/exceptions.h>

#include <util/buffer.h>
#include <dns/messagerenderer.h>
#include <dns/rrparamregistry.h>
#include <dns/rrtype.h>

using namespace std;
using namespace isc::util;
using isc::dns::RRType;

namespace isc {
namespace dns {

RRType::RRType(const std::string& type_str) {
    uint16_t typecode;
    if (!RRParamRegistry::getRegistry().textToTypeCode(type_str, typecode)) {
        isc_throw(InvalidRRType,
                  "Unrecognized RR type string: " + type_str);
    }
    typecode_ = typecode;
}

RRType::RRType(InputBuffer& buffer) {
    if (buffer.getLength() - buffer.getPosition() < sizeof(uint16_t)) {
        isc_throw(IncompleteRRType, "incomplete wire-format RR type");
    }
    typecode_ = buffer.readUint16();
}

const string
RRType::toText() const {
    return (RRParamRegistry::getRegistry().codeToTypeText(typecode_));
}

void
RRType::toWire(OutputBuffer& buffer) const {
    buffer.writeUint16(typecode_);
}

void
RRType::toWire(AbstractMessageRenderer& renderer) const {
    renderer.writeUint16(typecode_);
}

ostream&
operator<<(ostream& os, const RRType& rrtype) {
    os << rrtype.toText();
    return (os);
}
}
}
