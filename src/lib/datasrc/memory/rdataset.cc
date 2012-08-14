// Copyright (C) 2012  Internet Systems Consortium, Inc. ("ISC")
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

#include <exceptions/exceptions.h>

#include <dns/rdata.h>
#include <dns/rdataclass.h>
#include <dns/rrclass.h>
#include <dns/rrtype.h>
#include <dns/rrset.h>

#include "rdataset.h"
#include "rdata_encoder.h"
#include "rdata_reader.h"

#include <boost/static_assert.hpp>

#include <stdint.h>
#include <cstring>
#include <typeinfo>             // for bad_cast
#include <new>                  // for the placement new

using namespace isc::dns;
using namespace isc::dns::rdata;

namespace isc {
namespace datasrc {
namespace memory {

namespace {
RRType
getCoveredType(const Rdata& rdata) {
    try {
        const generic::RRSIG& rrsig_rdata =
            dynamic_cast<const generic::RRSIG&>(rdata);
        return (rrsig_rdata.typeCovered());
    } catch (const std::bad_cast&) {
        isc_throw(BadValue, "Non RRSIG is given where it's expected");
    }
}
}

RdataSet*
RdataSet::create(util::MemorySegment& mem_sgmt, RdataEncoder& encoder,
                 ConstRRsetPtr rrset, ConstRRsetPtr sig_rrset)
{
    if (!rrset && !sig_rrset) {
        isc_throw(BadValue, "Both RRset and RRSIG are NULL");
    }
    if (rrset && rrset->getRdataCount() == 0) {
        isc_throw(BadValue, "Empty RRset");
    }
    if (sig_rrset && sig_rrset->getRdataCount() == 0) {
        isc_throw(BadValue, "Empty SIG RRset");
    }
    if (rrset && sig_rrset) {
        if (rrset->getClass() != sig_rrset->getClass()) {
            isc_throw(BadValue,
                      "RR class doesn't match between RRset and RRSIG");
        }
    }

    const RRClass rrclass = rrset ? rrset->getClass() : sig_rrset->getClass();
    const RRType rrtype = rrset ? rrset->getType() :
        getCoveredType(sig_rrset->getRdataIterator()->getCurrent());
    const RRTTL rrttl = rrset ? rrset->getTTL() : sig_rrset->getTTL();

    encoder.start(rrclass, rrtype);
    if (rrset) {
        for (RdataIteratorPtr it = rrset->getRdataIterator();
             !it->isLast();
             it->next()) {
            encoder.addRdata(it->getCurrent());
        }
    }
    if (sig_rrset) {
        for (RdataIteratorPtr it = sig_rrset->getRdataIterator();
             !it->isLast();
             it->next())
        {
            if (getCoveredType(it->getCurrent()) != rrtype) {
                isc_throw(BadValue, "Type covered doesn't match");
            }
            encoder.addSIGRdata(it->getCurrent());
        }
    }

    const size_t data_len = encoder.getStorageLength();
    void* p = mem_sgmt.allocate(sizeof(RdataSet) + data_len);
    RdataSet* rdataset = new(p) RdataSet(rrtype,
                                         rrset ? rrset->getRdataCount() : 0,
                                         sig_rrset ?
                                         sig_rrset->getRdataCount() : 0,
                                         rrttl);
    encoder.encode(rdataset->getDataBuf(), data_len);
    return (rdataset);
}

void
RdataSet::destroy(util::MemorySegment& mem_sgmt, RRClass rrclass,
                  RdataSet* rdataset)
{
    const size_t data_len =
        RdataReader(rrclass, rdataset->type,
                    reinterpret_cast<const uint8_t*>(rdataset->getDataBuf()),
                    rdataset->rdata_count,
                    rdataset->sig_rdata_count).getSize();
    rdataset->~RdataSet();
    mem_sgmt.deallocate(rdataset, sizeof(RdataSet) + data_len);
}

namespace {
// Convert the given RRTTL into the corresponding 32-bit unsigned integer,
// in the network byte order.  We do not use htonl() to be as portable as
// possible.
uint32_t
convertTTL(RRTTL ttl) {
    const uint32_t ttl_val = ttl.getValue();
    uint8_t buf[4];
    buf[0] = (ttl_val & 0xff000000) >> 24;
    buf[1] = (ttl_val & 0x00ff0000) >> 16;
    buf[2] = (ttl_val & 0x0000ff00) >> 8;
    buf[3] = (ttl_val & 0x000000ff);
    uint32_t ret;
    std::memcpy(&ret, buf, sizeof(ret));
    return (ret);
}
}

RdataSet::RdataSet(RRType type_param, size_t rdata_count_param,
                   size_t sig_rdata_count_param, RRTTL ttl_param) :
    type(type_param), sig_rdata_count(sig_rdata_count_param),
    rdata_count(rdata_count_param), ttl(convertTTL(ttl_param))
{
    // Make sure an RRType object is essentially a plain 16-bit value, so
    // our assumption of the size of RdataSet holds.  If it's not the case
    // we should use the bare value instead of the class object.
    BOOST_STATIC_ASSERT(sizeof(type) == sizeof(uint16_t));

    // Confirm we meet the alignment requirement for RdataEncoder
    // ("this + 1" should be safely passed to the encoder).
    BOOST_STATIC_ASSERT(sizeof(RdataSet) % sizeof(uint16_t) == 0);
}

} // namespace memory
} // namespace datasrc
} // datasrc isc
