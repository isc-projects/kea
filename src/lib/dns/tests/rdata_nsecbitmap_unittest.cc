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

#include <dns/exceptions.h>
#include <dns/rdata.h>
#include <dns/rdataclass.h>
#include <dns/rrclass.h>
#include <dns/rrtype.h>

#include <gtest/gtest.h>

#include <dns/tests/rdata_unittest.h>

using namespace isc::dns;
using namespace isc::dns::rdata;

namespace {
class Rdata_NSECBITMAP_Test : public RdataTest {
    // there's nothing to specialize
};

// Tests against various types of bogus NSEC/NSEC3 type bitmaps.
// The syntax and semantics are common for both RR types, and our
// implementation of that part is shared, so in theory it should be sufficient
// to test for only one RR type.  But we check for both just in case.
TEST_F(Rdata_NSECBITMAP_Test, createFromWire_NSEC) {
    // A malformed NSEC bitmap length field that could cause overflow.
    EXPECT_THROW(rdataFactoryFromFile(RRType::NSEC(), RRClass::IN(),
                                      "rdata_nsec_fromWire4.wire"),
                 DNSMessageFORMERR);
    EXPECT_THROW(rdataFactoryFromFile(RRType::NSEC3(), RRClass::IN(),
                                      "rdata_nsec3_fromWire4.wire"),
                 DNSMessageFORMERR);

    // The bitmap field is incomplete (only the first byte is included)
    EXPECT_THROW(rdataFactoryFromFile(RRType::NSEC(), RRClass::IN(),
                                      "rdata_nsec_fromWire5.wire"),
                 DNSMessageFORMERR);
    EXPECT_THROW(rdataFactoryFromFile(RRType::NSEC3(), RRClass::IN(),
                                      "rdata_nsec3_fromWire5.wire"),
                 DNSMessageFORMERR);

    // Bitmap length is 0, which is invalid.
    EXPECT_THROW(rdataFactoryFromFile(RRType::NSEC(), RRClass::IN(),
                                      "rdata_nsec_fromWire6.wire"),
                 DNSMessageFORMERR);
    EXPECT_THROW(rdataFactoryFromFile(RRType::NSEC3(), RRClass::IN(),
                                      "rdata_nsec3_fromWire6.wire"),
                 DNSMessageFORMERR);

    // Too large bitmap length with a short buffer.
    EXPECT_THROW(rdataFactoryFromFile(RRType::NSEC(), RRClass::IN(),
                                      "rdata_nsec_fromWire3"),
                 DNSMessageFORMERR);
    EXPECT_THROW(rdataFactoryFromFile(RRType::NSEC3(), RRClass::IN(),
                                      "rdata_nsec3_fromWire3"),
                 DNSMessageFORMERR);

    // A boundary case: longest possible bitmaps (32 maps).  This should be
    // accepted.
    EXPECT_NO_THROW(rdataFactoryFromFile(RRType::NSEC(), RRClass::IN(),
                                         "rdata_nsec_fromWire7.wire"));
    EXPECT_NO_THROW(rdataFactoryFromFile(RRType::NSEC3(), RRClass::IN(),
                                         "rdata_nsec3_fromWire7.wire"));

    // Another boundary condition: 33 bitmaps, which should be rejected.
    EXPECT_THROW(rdataFactoryFromFile(RRType::NSEC(), RRClass::IN(),
                                      "rdata_nsec_fromWire8.wire"),
                 DNSMessageFORMERR);
    EXPECT_THROW(rdataFactoryFromFile(RRType::NSEC3(), RRClass::IN(),
                                      "rdata_nsec3_fromWire8.wire"),
                 DNSMessageFORMERR);

    // Disordered bitmap window blocks.
    EXPECT_THROW(rdataFactoryFromFile(RRType::NSEC(), RRClass::IN(),
                                      "rdata_nsec_fromWire9.wire"),
                 DNSMessageFORMERR);
    EXPECT_THROW(rdataFactoryFromFile(RRType::NSEC3(), RRClass::IN(),
                                      "rdata_nsec3_fromWire9.wire"),
                 DNSMessageFORMERR);

    // Bitmap ending with all-zero bytes.  Not necessarily harmful except
    // the additional overhead of parsing, but invalid according to the
    // spec anyway.
    EXPECT_THROW(rdataFactoryFromFile(RRType::NSEC(), RRClass::IN(),
                                      "rdata_nsec_fromWire10.wire"),
                 DNSMessageFORMERR);
    EXPECT_THROW(rdataFactoryFromFile(RRType::NSEC3(), RRClass::IN(),
                                      "rdata_nsec3_fromWire10.wire"),
                 DNSMessageFORMERR);
}
}
