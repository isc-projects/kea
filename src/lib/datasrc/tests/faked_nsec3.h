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

#include <datasrc/zone.h>

#include <dns/nsec3hash.h>
#include <dns/name.h>

#include <stdint.h>
#include <string>
#include <map>

namespace isc {
namespace datasrc {
namespace test {

//
// (Faked) NSEC3 hash data.  Arbitrarily borrowed from RFC515 examples.
//
// Commonly used NSEC3 suffix.  It's incorrect to use it for all NSEC3s, but
// doesn't matter for the purpose of our tests.
extern const char* const nsec3_common;
// Likewise, common RRSIG suffix for NSEC3s.
extern const char* const nsec3_rrsig_common;

// Some faked NSEC3 hash values commonly used in tests and the faked NSEC3Hash
// object.
//
// For apex (example.org)
extern const char* const apex_hash;
extern const char* const apex_hash_lower;
// For ns1.example.org
extern const char* const ns1_hash;
// For w.example.org
extern const char* const w_hash;
// For x.y.w.example.org (lower-cased)
extern const char* const xyw_hash;
// For zzz.example.org.
extern const char* const zzz_hash;

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

typedef std::map<isc::dns::Name, std::string> NSEC3HashMap;
typedef NSEC3HashMap::value_type NSEC3HashPair;

// Build the test map with the fake NSEC3 hashes.
void
buildFakeNSEC3Map(NSEC3HashMap& fmap);

// Check the result against expected values. It directly calls EXPECT_ macros
void
findNSEC3Check(bool expected_matched, uint8_t expected_labels,
               const std::string& expected_closest,
               const std::string& expected_next,
               const isc::datasrc::ZoneFinder::FindNSEC3Result& result);

// Perform the shared part of NSEC3 test (shared between in-memory and database
// tests).
void
performNSEC3Test(ZoneFinder &finder, bool rrsigs_exist = false);

}
}
}

#endif  // FAKED_NSEC3_H

// Local Variables:
// mode: c++
// End:
