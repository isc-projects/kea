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

#ifndef DATASRC_MEMORY_RDATASET_H
#define DATASRC_MEMORY_RDATASET_H 1

#include <util/memory_segment.h>

#include <dns/rrclass.h>
#include <dns/rrtype.h>
#include <dns/rrset.h>
#include <dns/rrttl.h>

#include <boost/interprocess/offset_ptr.hpp>

#include <stdint.h>

namespace isc {
namespace datasrc {
namespace memory {
class RdataEncoder;

/// \brief General error on creating RdataSet.
///
/// This is thrown when creating \c RdataSet encounters a rare, unsupported
/// situation.
class RdataSetError : public Exception {
public:
    RdataSetError(const char* file, size_t line, const char* what) :
        Exception(file, line, what) {}
};

class RdataSet {
public:
    static RdataSet* create(util::MemorySegment& mem_sgmt,
                            RdataEncoder& encoder,
                            dns::ConstRRsetPtr rrset,
                            dns::ConstRRsetPtr sig_rrset);
    static void destroy(util::MemorySegment& mem_sgmt, dns::RRClass rrclass,
                        RdataSet* rdataset);

    typedef boost::interprocess::offset_ptr<RdataSet> RdataSetPtr;
    typedef boost::interprocess::offset_ptr<const RdataSet> ConstRdataSetPtr;

    // Note: the size and order of the members are carefully chosen to
    // maximize efficiency.  Don't change them unless there's strong reason
    // for that and the consequences are considered.

    RdataSetPtr next;
    const dns::RRType type;
private:
    const uint16_t sig_rdata_count : 3;
    const uint16_t rdata_count : 13;
    const uint32_t ttl;       ///< TTL of the RdataSet, net byte order

    static const size_t MAX_RDATA_COUNT = (1 << 13) - 1;
    static const size_t MAX_RRSIG_COUNT = (1 << 16) - 1;
    static const size_t MANY_RRSIG_COUNT = (1 << 3) - 1;
public:
    size_t getRdataCount() const { return (rdata_count); }
    size_t getSigRdataCount() const {
        if (sig_rdata_count < MANY_RRSIG_COUNT) {
            return (sig_rdata_count);
        } else {
            return (*getExtSIGCountBuf());
        }
    }
    const void* getTTLData() const { return (&ttl); }
    void* getDataBuf() {
        if (sig_rdata_count < MANY_RRSIG_COUNT) {
            return (this + 1);
        } else {
            return (getExtSIGCountBuf() + 1);
        }
    }

private:
    uint16_t* getExtSIGCountBuf() {
        return (reinterpret_cast<uint16_t*>(this + 1));
    }
    const uint16_t* getExtSIGCountBuf() const {
        return (reinterpret_cast<const uint16_t*>(this + 1));
    }

    RdataSet(dns::RRType type, size_t rdata_count, size_t sig_rdata_count,
             dns::RRTTL ttl);
    ~RdataSet() {}
};

} // namespace memory
} // namespace datasrc
} // namespace isc

#endif // DATASRC_MEMORY_RDATASET_H

// Local Variables:
// mode: c++
// End:
