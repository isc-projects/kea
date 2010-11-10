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

#include <iostream>
#include <string>

#include <dns/buffer.h>
#include <dns/messagerenderer.h>
#include <dns/name.h>
#include <dns/question.h>
#include <dns/rrclass.h>
#include <dns/rrtype.h>

using namespace std;

namespace isc {
namespace dns {
Question::Question(InputBuffer& buffer) :
    name_(buffer), rrtype_(0), rrclass_(0)
{
    // In theory, we could perform this in the member initialization list,
    // and it would be a little bit more efficient.  We don't do this, however,
    // because the initialization ordering is crucial (type must be first)
    // and the ordering in the initialization list depends on the appearance
    // order of member variables.  It's fragile to rely on such an implicit
    // dependency, so we make the initialization order explicit.
    rrtype_ = RRType(buffer);
    rrclass_ = RRClass(buffer);
}

string
Question::toText() const {
    return (name_.toText() + " " + rrclass_.toText() + " " +
            rrtype_.toText() + "\n");
}

unsigned int
Question::toWire(OutputBuffer& buffer) const {
    name_.toWire(buffer);
    rrtype_.toWire(buffer);
    rrclass_.toWire(buffer);    // number of "entries", which is always 1

    return (1);
}

unsigned int
Question::toWire(MessageRenderer& renderer) const {
    renderer.writeName(name_);
    rrtype_.toWire(renderer);
    rrclass_.toWire(renderer);

    return (1);                 // number of "entries"
}

ostream&
operator<<(std::ostream& os, const Question& question) {
    os << question.toText();
    return (os);
}
}
}
