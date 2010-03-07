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
#include <exceptions/exceptions.h>
#include "messagerenderer.h"
#include "rrparamregistry.h"
#include "rrclass.h"

using namespace std;
using namespace isc::dns;

namespace isc {
namespace dns {

RRClass::RRClass(const string& classstr)
{
    classcode_ = RRParamRegistry::getRegistry().textToClassCode(classstr);
}

RRClass::RRClass(InputBuffer& buffer)
{
    if (buffer.getLength() - buffer.getPosition() < sizeof(uint16_t)) {
        isc_throw(IncompleteRRClass, "incomplete wire-format RR class");
    }
    classcode_ = buffer.readUint16();
}

const string
RRClass::toText() const
{
    return (RRParamRegistry::getRegistry().codeToClassText(classcode_));
}

void
RRClass::toWire(OutputBuffer& buffer) const
{
    buffer.writeUint16(classcode_);
}

void
RRClass::toWire(MessageRenderer& renderer) const
{
    renderer.writeUint16(classcode_);
}

ostream&
operator<<(ostream& os, const RRClass& rrclass)
{
    os << rrclass.toText();
    return (os);
}
}
}
