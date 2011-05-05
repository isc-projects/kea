// Copyright (C) 2011  Internet Systems Consortium, Inc. ("ISC")
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

#include <ostream>
#include <string>

#include <util/buffer.h>

#include <dns/messagerenderer.h>
#include <dns/rrclass.h>
#include <dns/rrttl.h>
#include <dns/tsigrecord.h>

using namespace isc::util;

namespace {
// Internally used constants:

// Size in octets for the RR type, class TTL, RDLEN fields.
const size_t RR_COMMON_LEN = 10;

// Size in octets for the fixed part of TSIG RDATAs.
// - Time Signed (6)
// - Fudge (2)
// - MAC Size (2)
// - Original ID (2)
// - Error (2)
// - Other Len (2)
const size_t RDATA_COMMON_LEN = 16;
}

namespace isc {
namespace dns {
TSIGRecord::TSIGRecord(const Name& key_name,
                       const rdata::any::TSIG& tsig_rdata) :
    key_name_(key_name), rdata_(tsig_rdata),
    length_(RR_COMMON_LEN + RDATA_COMMON_LEN + key_name_.getLength() +
            rdata_.getAlgorithm().getLength() +
            rdata_.getMACSize() + rdata_.getOtherLen())
{}

const RRClass&
TSIGRecord::getClass() {
    return (RRClass::ANY());
}

namespace {
template <typename OUTPUT>
void
toWireCommon(OUTPUT& output, const rdata::any::TSIG& rdata) {
    // RR type, class, TTL are fixed constants.
    RRType::TSIG().toWire(output);
    TSIGRecord::getClass().toWire(output);
    output.writeUint32(TSIGRecord::TSIG_TTL);

    // RDLEN
    output.writeUint16(RDATA_COMMON_LEN + rdata.getAlgorithm().getLength() +
                       rdata.getMACSize() + rdata.getOtherLen());

    // TSIG RDATA
    rdata.toWire(output);
}
}

int
TSIGRecord::toWire(AbstractMessageRenderer& renderer) const {
    // If adding the TSIG would exceed the size limit, don't do it.
    if (renderer.getLength() + length_ > renderer.getLengthLimit()) {
        renderer.setTruncated();
        return (0);
    }

    // key name = owner.  note that we disable compression.
    renderer.writeName(key_name_, false);
    toWireCommon(renderer, rdata_);
    return (1);
}

int
TSIGRecord::toWire(OutputBuffer& buffer) const {
    key_name_.toWire(buffer);
    toWireCommon(buffer, rdata_);
    return (1);
}

std::string
TSIGRecord::toText() const {
    return (key_name_.toText() + " " + RRTTL(TSIG_TTL).toText() + " " +
            getClass().toText() + " " + RRType::TSIG().toText() + " " +
            rdata_.toText() + "\n");
}

std::ostream&
operator<<(std::ostream& os, const TSIGRecord& record) {
    return (os << record.toText());
}
} // namespace dns
} // namespace isc
