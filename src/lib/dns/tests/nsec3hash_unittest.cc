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

#include <gtest/gtest.h>

#include <dns/nsec3hash.h>
#include <dns/rdataclass.h>

using namespace isc::dns;
using namespace isc::dns::rdata;

namespace {
class NSEC3HashTest : public ::testing::Test {
protected:
    NSEC3HashTest() : test_hash(generic::NSEC3PARAM("1 0 12 aabbccdd"))
    {}

    // An NSEC3Hash object commonly used in tests.  Parameters are borrowed
    // from the RFC5155 example.  Construction of this object implicitly
    // checks a successful case of the constructor.
    const NSEC3Hash test_hash;
};

TEST_F(NSEC3HashTest, unknownAlgorithm) {
    EXPECT_THROW(NSEC3Hash(generic::NSEC3PARAM("2 0 12 aabbccdd")),
                 UnknownNSEC3HashAlgorithm);
}

TEST_F(NSEC3HashTest, calculate) {
    // A couple of normal cases from the RFC5155 example.
    EXPECT_EQ("0P9MHAVEQVM6T7VBL5LOP2U3T2RP3TOM",
              test_hash.calculate(Name("example")));
    EXPECT_EQ("35MTHGPGCU1QG68FAB165KLNSNK3DPVL",
              test_hash.calculate(Name("a.example")));

    // Check case-insensitiveness
    EXPECT_EQ("0P9MHAVEQVM6T7VBL5LOP2U3T2RP3TOM",
              test_hash.calculate(Name("EXAMPLE")));

    // Some boundary cases: 0-iteration and empty salt.  Borrowed from the
    // .com zone data.
    EXPECT_EQ("CK0POJMG874LJREF7EFN8430QVIT8BSM",
              NSEC3Hash(generic::NSEC3PARAM("1 0 0 -")).
              calculate(Name("com")));

    // Using unusually large iterations, something larger than the 8-bit range.
    // (expected hash value generated by BIND 9's dnssec-signzone)
    EXPECT_EQ("COG6A52MJ96MNMV3QUCAGGCO0RHCC2Q3",
              NSEC3Hash(generic::NSEC3PARAM("1 0 256 AABBCCDD")).
              calculate(Name("example.org")));
}

} // end namespace
