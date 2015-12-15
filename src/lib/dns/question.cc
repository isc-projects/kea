// Copyright (C) 2010  Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <iostream>
#include <string>

#include <util/buffer.h>
#include <dns/messagerenderer.h>
#include <dns/name.h>
#include <dns/question.h>
#include <dns/rrclass.h>
#include <dns/rrtype.h>

using namespace std;
using namespace isc::util;

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

std::string
Question::toText(bool newline) const {
    std::string r(name_.toText() + " " + rrclass_.toText() + " " +
                  rrtype_.toText());
    if (newline) {
        r.append("\n");
    }

    return (r);
}

unsigned int
Question::toWire(OutputBuffer& buffer) const {
    name_.toWire(buffer);
    rrtype_.toWire(buffer);
    rrclass_.toWire(buffer);    // number of "entries", which is always 1

    return (1);
}

unsigned int
Question::toWire(AbstractMessageRenderer& renderer) const {
    const size_t pos0 = renderer.getLength();

    renderer.writeName(name_);
    rrtype_.toWire(renderer);
    rrclass_.toWire(renderer);

    // Make sure the renderer has a room for the question
    if (renderer.getLength() > renderer.getLengthLimit()) {
        renderer.trim(renderer.getLength() - pos0);
        renderer.setTruncated();
        return (0);
    }

    return (1);                 // number of "entries"
}

ostream&
operator<<(std::ostream& os, const Question& question) {
    os << question.toText();
    return (os);
}
}
}
