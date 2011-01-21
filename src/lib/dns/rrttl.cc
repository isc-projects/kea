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

#include <stdint.h>

#include <sstream>
#include <ostream>

#include <dns/buffer.h>
#include <dns/messagerenderer.h>
#include <dns/rrttl.h>

using namespace std;
using namespace isc::dns;

namespace isc {
namespace dns {

RRTTL::RRTTL(const string& ttlstr) {
    // Some systems (at least gcc-4.4) flow negative values over into
    // unsigned integer, where older systems failed to parse. We want
    // that failure here, so we extract into int64 and check the value
    int64_t val;

    istringstream iss(ttlstr);
    iss >> dec >> val;
    if (iss.rdstate() == ios::eofbit && val >= 0 && val <= 0xffffffff) {
        ttlval_ = static_cast<uint32_t>(val);
    } else {
        isc_throw(InvalidRRTTL, "invalid TTL");
    }
}

RRTTL::RRTTL(InputBuffer& buffer) {
    if (buffer.getLength() - buffer.getPosition() < sizeof(uint32_t)) {
        isc_throw(IncompleteRRTTL, "incomplete wire-format TTL value");
    }
    ttlval_ = buffer.readUint32();
}

const string
RRTTL::toText() const {
    ostringstream oss;
    oss << ttlval_;
    return (oss.str());
}

void
RRTTL::toWire(OutputBuffer& buffer) const {
    buffer.writeUint32(ttlval_);
}

void
RRTTL::toWire(MessageRenderer& renderer) const {
    renderer.writeUint32(ttlval_);
}

ostream&
operator<<(ostream& os, const RRTTL& rrttl) {
    os << rrttl.toText();
    return (os);
}
}
}
