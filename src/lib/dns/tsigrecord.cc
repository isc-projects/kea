// Copyright (C) 2011-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <ostream>
#include <string>

#include <util/buffer.h>

#include <dns/exceptions.h>
#include <dns/messagerenderer.h>
#include <dns/rrclass.h>
#include <dns/rrttl.h>
#include <dns/tsigrecord.h>

using namespace isc::util;
using namespace isc::dns::rdata;

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

namespace {
// This is a straightforward wrapper of dynamic_cast<const any::TSIG&>.
// We use this so that we can throw the DNSMessageFORMERR exception when
// unexpected type of RDATA is detected in the member initialization list
// of the constructor below.
const any::TSIG&
castToTSIGRdata(const rdata::Rdata& rdata) {
    const any::TSIG* tsig_rdata =
        dynamic_cast<const any::TSIG*>(&rdata);
    if (!tsig_rdata) {
        isc_throw(DNSMessageFORMERR,
                  "TSIG record is being constructed from "
                  "incompatible RDATA: " << rdata.toText());
    }
    return (*tsig_rdata);
}
}

TSIGRecord::TSIGRecord(const Name& name, const RRClass& rrclass,
                       const RRTTL& ttl, const rdata::Rdata& rdata,
                       size_t length) :
    key_name_(name), rdata_(castToTSIGRdata(rdata)), length_(length)
{
    if (rrclass != getClass()) {
        isc_throw(DNSMessageFORMERR, "Unexpected TSIG RR class: " << rrclass);
    }
    if (ttl != RRTTL(TSIG_TTL)) {
        isc_throw(DNSMessageFORMERR, "Unexpected TSIG TTL: " << ttl);
    }
}

const RRClass&
TSIGRecord::getClass() {
    return (RRClass::ANY());
}

const RRTTL&
TSIGRecord::getTTL() {
    static RRTTL ttl(TSIG_TTL);
    return (ttl);
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
