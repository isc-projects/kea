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
#include <algorithm>
#include <cstring>
#include <new>                  // for the placement new

using namespace isc::dns;
using namespace isc::dns::rdata;

namespace isc {
namespace datasrc {
namespace memory {

namespace {
RRType
getCoveredType(const Rdata& rdata) {
    const generic::RRSIG* rrsig_rdata =
        dynamic_cast<const generic::RRSIG*>(&rdata);
    if (!rrsig_rdata) {
        isc_throw(BadValue, "Non RRSIG is given where it's expected");
    }
    return (rrsig_rdata->typeCovered());
}

// A helper for lowestTTL: restore RRTTL object from wire-format 32-bit data.
RRTTL
restoreTTL(const void* ttl_data) {
    isc::util::InputBuffer b(ttl_data, sizeof(uint32_t));
    return (RRTTL(b));
}

// A helper function for create(): return the TTL that has lowest value
// amount the given those of given rdataset (if non NULL), rrset, sig_rrset.
RRTTL
lowestTTL(const RdataSet* rdataset, ConstRRsetPtr& rrset,
          ConstRRsetPtr& sig_rrset)
{
    if (rrset && sig_rrset) {
        const RRTTL tmp(std::min(rrset->getTTL(), sig_rrset->getTTL()));
        return (rdataset ?
                std::min(restoreTTL(rdataset->getTTLData()), tmp) : tmp);
    } else if (rrset) {
        return (rdataset ? std::min(restoreTTL(rdataset->getTTLData()),
                                    rrset->getTTL()) : rrset->getTTL());
    } else {
        return (rdataset ? std::min(restoreTTL(rdataset->getTTLData()),
                                    sig_rrset->getTTL()) :
                sig_rrset->getTTL());
    }
}
}

RdataSet*
RdataSet::create(util::MemorySegment& mem_sgmt, RdataEncoder& encoder,
                 ConstRRsetPtr rrset, ConstRRsetPtr sig_rrset,
                 const RdataSet* old_rdataset)
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

    const RRClass rrclass = rrset ? rrset->getClass() : sig_rrset->getClass();
    const RRType rrtype = rrset ? rrset->getType() :
        getCoveredType(sig_rrset->getRdataIterator()->getCurrent());
    if (old_rdataset && old_rdataset->type != rrtype) {
        isc_throw(BadValue, "RR type doesn't match for merging RdataSet");
    }
    const RRTTL rrttl = lowestTTL(old_rdataset, rrset, sig_rrset);
    if (old_rdataset) {
        encoder.start(rrclass, rrtype, old_rdataset->getDataBuf(),
                      old_rdataset->getRdataCount(),
                      old_rdataset->getSigRdataCount());
    } else {
        encoder.start(rrclass, rrtype);
    }

    // Store RDATAs to be added and check assumptions on the number of them
    size_t rdata_count = old_rdataset ? old_rdataset->getRdataCount() : 0;
    if (rrset) {
        for (RdataIteratorPtr it = rrset->getRdataIterator();
             !it->isLast();
             it->next()) {
            if (encoder.addRdata(it->getCurrent())) {
                ++rdata_count;
            }
        }
    }
    if (rdata_count > MAX_RDATA_COUNT) {
        isc_throw(RdataSetError, "Too many RDATAs for RdataSet: "
                  << rrset->getRdataCount() << ", must be <= "
                  << MAX_RDATA_COUNT);
    }

    // Same for RRSIG
    size_t rrsig_count = old_rdataset ? old_rdataset->getSigRdataCount() : 0;
    if (sig_rrset) {
        for (RdataIteratorPtr it = sig_rrset->getRdataIterator();
             !it->isLast();
             it->next())
        {
            if (getCoveredType(it->getCurrent()) != rrtype) {
                isc_throw(BadValue, "Type covered doesn't match");
            }
            if (encoder.addSIGRdata(it->getCurrent())) {
                ++rrsig_count;
            }
        }
    }
    if (rrsig_count > MAX_RRSIG_COUNT) {
        isc_throw(RdataSetError, "Too many RRSIGs for RdataSet: "
                  << sig_rrset->getRdataCount() << ", must be <= "
                  << MAX_RRSIG_COUNT);
    }

    const size_t ext_rrsig_count_len =
        rrsig_count >= MANY_RRSIG_COUNT ? sizeof(uint16_t) : 0;
    const size_t data_len = encoder.getStorageLength();
    void* p = mem_sgmt.allocate(sizeof(RdataSet) + ext_rrsig_count_len +
                                data_len);
    RdataSet* rdataset = new(p) RdataSet(rrtype, rdata_count, rrsig_count,
                                         rrttl);
    if (rrsig_count >= MANY_RRSIG_COUNT) {
        *rdataset->getExtSIGCountBuf() = rrsig_count;
    }
    encoder.encode(rdataset->getDataBuf(), data_len);
    return (rdataset);
}

void
RdataSet::destroy(util::MemorySegment& mem_sgmt, RdataSet* rdataset,
                  RRClass rrclass)
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
