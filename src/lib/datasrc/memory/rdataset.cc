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
#include "rdata_serialization.h"

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
    // Check basic validity
    if (!rrset && !sig_rrset) {
        isc_throw(BadValue, "Both RRset and RRSIG are NULL");
    }
    if (rrset && rrset->getRdataCount() == 0) {
        isc_throw(BadValue, "Empty RRset");
    }
    if (sig_rrset && sig_rrset->getRdataCount() == 0) {
        isc_throw(BadValue, "Empty SIG RRset");
    }
    if (rrset && sig_rrset && rrset->getClass() != sig_rrset->getClass()) {
        isc_throw(BadValue, "RR class doesn't match between RRset and RRSIG");
    }

    // Check assumptions on the number of RDATAs
    if (rrset && rrset->getRdataCount() > MAX_RDATA_COUNT) {
        isc_throw(RdataSetError, "Too many RDATAs for RdataSet: "
                  << rrset->getRdataCount() << ", must be <= "
                  << MAX_RDATA_COUNT);
    }
    if (sig_rrset && sig_rrset->getRdataCount() > MAX_RRSIG_COUNT) {
        isc_throw(RdataSetError, "Too many RRSIGs for RdataSet: "
                  << sig_rrset->getRdataCount() << ", must be <= "
                  << MAX_RRSIG_COUNT);
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

    const size_t rrsig_count = sig_rrset ? sig_rrset->getRdataCount() : 0;
    const size_t ext_rrsig_count_len =
        rrsig_count >= MANY_RRSIG_COUNT ? sizeof(uint16_t) : 0;
    const size_t data_len = encoder.getStorageLength();
    void* p = mem_sgmt.allocate(sizeof(RdataSet) + ext_rrsig_count_len +
                                data_len);
    RdataSet* rdataset = new(p) RdataSet(rrtype,
                                         rrset ? rrset->getRdataCount() : 0,
                                         rrsig_count, rrttl);
    if (rrsig_count >= MANY_RRSIG_COUNT) {
        *rdataset->getExtSIGCountBuf() = rrsig_count;
    }
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
                    rdataset->getRdataCount(), rdataset->getSigRdataCount(),
                    &RdataReader::emptyNameAction,
                    &RdataReader::emptyDataAction).getSize();
    const size_t ext_rrsig_count_len =
        rdataset->sig_rdata_count_ == MANY_RRSIG_COUNT ? sizeof(uint16_t) : 0;
    rdataset->~RdataSet();
    mem_sgmt.deallocate(rdataset,
                        sizeof(RdataSet) + ext_rrsig_count_len + data_len);
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

RdataSet::RdataSet(RRType type_param, size_t rdata_count,
                   size_t sig_rdata_count, RRTTL ttl) :
    type(type_param),
    sig_rdata_count_(sig_rdata_count >= MANY_RRSIG_COUNT ?
                     MANY_RRSIG_COUNT : sig_rdata_count),
    rdata_count_(rdata_count), ttl_(convertTTL(ttl))
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
