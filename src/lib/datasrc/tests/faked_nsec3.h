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

#ifndef FAKED_NSEC3_H
#define FAKED_NSEC3_H

#include <dns/nsec3hash.h>

namespace isc {
namespace datasrc {
namespace test {

// Some faked NSEC3 hash values commonly used in tests and the faked NSEC3Hash
// object.
//
// For apex (example.org)
const char* const apex_hash = "0P9MHAVEQVM6T7VBL5LOP2U3T2RP3TOM";
const char* const apex_hash_lower = "0p9mhaveqvm6t7vbl5lop2u3t2rp3tom";
// For ns1.example.org
const char* const ns1_hash = "2T7B4G4VSA5SMI47K61MV5BV1A22BOJR";
// For w.example.org
const char* const w_hash = "01UDEMVP1J2F7EG6JEBPS17VP3N8I58H";
// For x.y.w.example.org (lower-cased)
const char* const xyw_hash = "2vptu5timamqttgl4luu9kg21e0aor3s";
// For zzz.example.org.
const char* const zzz_hash = "R53BQ7CC2UVMUBFU5OCMM6PERS9TK9EN";

// A simple faked NSEC3 hash calculator with a dedicated creator for it.
//
// This is used in some NSEC3-related tests below.
class TestNSEC3HashCreator : public isc::dns::NSEC3HashCreator {
private:
    class TestNSEC3Hash;
public:
    virtual isc::dns::NSEC3Hash* create(const
                                        isc::dns::rdata::generic::NSEC3PARAM&)
        const;
    virtual isc::dns::NSEC3Hash* create(const isc::dns::rdata::generic::NSEC3&)
        const;
};

}
}
}

#endif
