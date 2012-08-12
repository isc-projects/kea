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

#include <dns/rrtype.h>
#include <dns/rrset.h>

#include "rdataset.h"
#include "rdata_encoder.h"

#include <boost/static_assert.hpp>

#include <stdint.h>
#include <cstring>
#include <new>                  // for the placement new

using namespace isc::dns;

namespace isc {
namespace datasrc {
namespace memory {

RdataSet*
RdataSet::create(util::MemorySegment& mem_sgmt, RdataEncoder& encoder,
                 ConstRRsetPtr rrset, ConstRRsetPtr sig_rrset)
{
    encoder.start(rrset->getClass(), rrset->getType());
    for (RdataIteratorPtr it = rrset->getRdataIterator();
         !it->isLast();
         it->next()) {
        encoder.addRdata(it->getCurrent());
    }

    const size_t data_len = encoder.getStorageLength();
    assert(data_len == 4);
    void* p = mem_sgmt.allocate(sizeof(RdataSet) + data_len);
    RdataSet* rdataset = new(p) RdataSet(rrset->getType(),
                                         rrset->getRdataCount(),
                                         sig_rrset ?
                                         sig_rrset->getRdataCount() : 0,
                                         rrset->getTTL());
    encoder.encode(rdataset + 1, data_len);
    return (rdataset);
}

void
RdataSet::destroy(util::MemorySegment& mem_sgmt, RdataSet* rdataset) {
    rdataset->~RdataSet();
    mem_sgmt.deallocate(rdataset, sizeof(RdataSet) + 4);
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
}

} // namespace memory
} // namespace datasrc
} // datasrc isc
