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

// BEGIN_HEADER_GUARD

#include <stdint.h>

#include <string>

#include <dns/rdata.h>

namespace isc {
namespace dns {
class Name;
}
}

// BEGIN_ISC_NAMESPACE

// BEGIN_COMMON_DECLARATIONS
// END_COMMON_DECLARATIONS

// BEGIN_RDATA_NAMESPACE

/// \brief TSIG RDATA class.
class TSIG : public Rdata {
public:
    // BEGIN_COMMON_MEMBERS
    // END_COMMON_MEMBERS
    TSIG(const Name& algorithm, uint64_t time_signed, uint16_t fudge,
         size_t mac_size, const void* mac, uint16_t original_id,
         uint16_t error, size_t other_len, const void* other_data);
    TSIG& operator=(const TSIG& source);
    ~TSIG();

    const Name& getAlgorithm() const;
    uint64_t getTimeSigned() const;
    uint16_t getFudge() const;
    uint16_t getMACSize() const;
    const void* getMAC() const;
    uint16_t getOriginalID() const;
    uint16_t getError() const;
    uint16_t getOtherLen() const;
    const void* getOtherData() const;
private:
    struct TSIGImpl;
    TSIGImpl* impl_;
};

// END_RDATA_NAMESPACE
// END_ISC_NAMESPACE
// END_HEADER_GUARD

// Local Variables: 
// mode: c++
// End: 
