// Copyright (C) 2010  Internet Systems Consortium, Inc. ("ISC")
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

// $Id$

#include <string>

#include <stdint.h>

#include "buffer.h"
#include "exceptions.h"
#include "messagerenderer.h"
#include "rrparamregistry.h"
#include "rrtype.h"

using namespace std;
using isc::dns::RRType;
using isc::dns::OutputBuffer;

namespace isc {
namespace dns {

RRType::RRType(const string& typestr)
{
    typecode_ = RRParamRegistry::getRegistry().textToTypeCode(typestr);
}

RRType::RRType(InputBuffer& buffer)
{
    if (buffer.getLength() - buffer.getPosition() < sizeof(uint16_t)) {
        dns_throw(IncompleteRRType, "incomplete wire-format RR type");
    }
    typecode_ = buffer.readUint16();
}

const string
RRType::toText() const
{
    return (RRParamRegistry::getRegistry().codeToTypeText(typecode_));
}

void
RRType::toWire(OutputBuffer& buffer) const
{
    buffer.writeUint16(typecode_);
}

void
RRType::toWire(MessageRenderer& renderer) const
{
    renderer.writeUint16(typecode_);
}

ostream&
operator<<(ostream& os, const RRType& rrtype)
{
    os << rrtype.toText();
    return (os);
}
}
}
