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

#include <config.h>

#include <stdint.h>

#include <cassert>

#include <boost/lexical_cast.hpp>

#include <exceptions/exceptions.h>

#include <dns/edns.h>
#include <dns/exceptions.h>
#include <dns/message.h>
#include <dns/messagerenderer.h>
#include <dns/name.h>
#include <dns/rdata.h>
#include <dns/rdataclass.h>
#include <dns/rrclass.h>
#include <dns/rrttl.h>
#include <dns/rrtype.h>

using namespace std;
using namespace boost;
using namespace isc::dns::rdata;

namespace isc {
namespace dns {

namespace {
//           0             7               15                              31
//          +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//          | EXTENDED-RCODE|    VERSION     |D|               Z             |
//          +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//                                          <= VERSION_SHIFT (16 bits)
//EXTFLAG_DO:0 0 0 ....................... 0 1 0 0 0 0.....................0
const uint32_t VERSION_MASK = 0x00ff0000;
const unsigned int VERSION_SHIFT = 16;
const uint32_t EXTFLAG_DO = 0x00008000;

//     0             7       11                                      31
//    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//    | EXTENDED-RCODE| RCODE  |                                       |
//    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//                    <= EXTRCODE_SHIFT
const uint32_t EXTRCODE_MASK = 0xff000000;
const unsigned int EXTRCODE_SHIFT = 24;
}

EDNS::EDNS(const uint8_t version) :
    version_(version),
    udp_size_(Message::DEFAULT_MAX_UDPSIZE),
    dnssec_ok_(false)
{
    if (version_ > SUPPORTED_VERSION) {
        isc_throw(isc::InvalidParameter,
                  "failed to construct EDNS: unsupported version: " <<
                  static_cast<unsigned int>(version_));
    }
}

EDNS::EDNS(const Name& name, const RRClass& rrclass, const RRType& rrtype,
           const RRTTL& ttl, const Rdata& rdata UNUSED_PARAM) :
    version_((ttl.getValue() & VERSION_MASK) >> VERSION_SHIFT)
{
    if (rrtype != RRType::OPT()) {
        isc_throw(isc::InvalidParameter,
                  "EDNS is being created with incompatible RR type: "
                  << rrtype);
    }
    
    if (version_ > EDNS::SUPPORTED_VERSION) {
        isc_throw(DNSMessageBADVERS, "unsupported EDNS version: " <<
                  static_cast<unsigned int>(version_));
    }

    if (name != Name::ROOT_NAME()) {
        isc_throw(DNSMessageFORMERR, "invalid owner name for EDNS OPT RR: " <<
                  name);
    }

    dnssec_ok_ = ((ttl.getValue() & EXTFLAG_DO) != 0);
    udp_size_ = rrclass.getCode();
}

string
EDNS::toText() const {
    string ret = "; EDNS: version: ";

    ret += lexical_cast<string>(static_cast<int>(getVersion()));
    ret += ", flags:";
    if (isDNSSECSupported()) {
        ret += " do";
    }
    ret += "; udp: " + lexical_cast<string>(getUDPSize());
    
    return (ret);
}

template <typename Output>
int
EDNS::toWire(Output& output, const uint8_t extended_rcode) const {
    // Render EDNS OPT RR
    uint32_t extrcode_flags = extended_rcode << EXTRCODE_SHIFT;
    extrcode_flags |= (version_ << VERSION_SHIFT) & VERSION_MASK;
    if (dnssec_ok_) {
        extrcode_flags |= EXTFLAG_DO;
    }

    // Construct an RRset corresponding to the EDNS.
    // We don't support any options for now, so the OPT RR can be empty.
    RRsetPtr edns_rrset = RRsetPtr(new RRset(Name::ROOT_NAME(),
                                             RRClass(udp_size_), RRType::OPT(),
                                             RRTTL(extrcode_flags)));
    edns_rrset->addRdata(ConstRdataPtr(new generic::OPT()));

    edns_rrset->toWire(output);

    return (1);
}

unsigned int
EDNS::toWire(MessageRenderer& renderer, const uint8_t extended_rcode) const {
    // If adding the OPT RR would exceed the size limit, don't do it.
    // 11 = len(".") + type(2byte) + class(2byte) + TTL(4byte) + RDLEN(2byte)
    // (RDATA is empty in this simple implementation)
    if (renderer.getLength() + 11 > renderer.getLengthLimit()) {
        return (0);
    }

    return (toWire<MessageRenderer>(renderer, extended_rcode));
}

unsigned int
EDNS::toWire(OutputBuffer& buffer, const uint8_t extended_rcode) const {
    return (toWire<OutputBuffer>(buffer, extended_rcode));
}

EDNS*
createEDNSFromRR(const Name& name, const RRClass& rrclass,
                 const RRType& rrtype, const RRTTL& ttl,
                 const Rdata& rdata UNUSED_PARAM,
                 uint8_t& extended_rcode)
{
    // Create a new EDNS object first for exception guarantee.
    EDNS* edns = new EDNS(name, rrclass, rrtype, ttl, rdata);

    // At this point we can update extended_rcode safely.
    extended_rcode = ttl.getValue() >> EXTRCODE_SHIFT;

    return (edns);
}

ostream&
operator<<(std::ostream& os, const EDNS& edns) {
    os << edns.toText();
    return (os);
}

} // end of namespace dns
} // end of namespace isc
