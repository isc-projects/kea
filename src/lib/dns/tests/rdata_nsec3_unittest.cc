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

#include <string>

#include <exceptions/exceptions.h>

#include <dns/buffer.h>
#include <dns/exceptions.h>
#include <dns/util/hex.h>
#include <dns/messagerenderer.h>
#include <dns/rdata.h>
#include <dns/rdataclass.h>
#include <dns/rrclass.h>
#include <dns/rrtype.h>

#include <gtest/gtest.h>

#include <dns/tests/unittest_util.h>
#include <dns/tests/rdata_unittest.h>

using isc::UnitTestUtil;
using namespace std;
using namespace isc;
using namespace isc::dns;
using namespace isc::dns::rdata;

namespace {
class Rdata_NSEC3_Test : public RdataTest {
    // there's nothing to specialize
public:
    Rdata_NSEC3_Test() :
        nsec3_txt("1 1 1 D399EAAB H9RSFB7FPF2L8HG35CMPC765TDK23RP6 "
                  "NS SOA RRSIG DNSKEY NSEC3PARAM") {}
    string nsec3_txt;
};

TEST_F(Rdata_NSEC3_Test, toText) {
    const generic::NSEC3 rdata_nsec3(nsec3_txt);
    EXPECT_EQ(nsec3_txt, rdata_nsec3.toText());
}

TEST_F(Rdata_NSEC3_Test, badText) {
    EXPECT_THROW(generic::NSEC3 rdata_nsec3("1 1 1 ADDAFEEE "
                                            "0123456789ABCDEFGHIJKLMNOPQRSTUV "
                                            "BIFF POW SPOON"),
                 InvalidRdataText);
    EXPECT_THROW(generic::NSEC3 rdata_nsec3("1 1 1 ADDAFEE "
                                            "WXYZWXYZWXYZ=WXYZWXYZ==WXYZWXYZW "
                                            "A NS SOA"),
                 BadValue);     // bad hex
    EXPECT_THROW(generic::NSEC3 rdata_nsec3("1 1 1 ADDAFEEE "
                                            "WXYZWXYZWXYZ=WXYZWXYZ==WXYZWXYZW "
                                            "A NS SOA"),
                 BadValue);     // bad base32hex
    EXPECT_THROW(generic::NSEC3 rdata_nsec3("1000000 1 1 ADDAFEEE "
                                            "0123456789ABCDEFGHIJKLMNOPQRSTUV "
                                            "A NS SOA"),
                 InvalidRdataText);
    EXPECT_THROW(generic::NSEC3 rdata_nsec3("1 1000000 1 ADDAFEEE "
                                            "0123456789ABCDEFGHIJKLMNOPQRSTUV "
                                            "A NS SOA"),
                 InvalidRdataText);
    EXPECT_THROW(generic::NSEC3 rdata_nsec3("1 1 1000000 ADDAFEEE "
                                            "0123456789ABCDEFGHIJKLMNOPQRSTUV "
                                            "A NS SOA"),
                 InvalidRdataText);
}

TEST_F(Rdata_NSEC3_Test, DISABLED_badText) { // this currently fails
    EXPECT_THROW(generic::NSEC3(
                     "1 1 1D399EAAB H9RSFB7FPF2L8HG35CMPC765TDK23RP6 "
                     "NS SOA RRSIG DNSKEY NSEC3PARAM"), InvalidRdataText);
}

TEST_F(Rdata_NSEC3_Test, createFromWire) {
    const generic::NSEC3 rdata_nsec3(nsec3_txt);
    EXPECT_EQ(0, rdata_nsec3.compare(
                  *rdataFactoryFromFile(RRType::NSEC3(), RRClass::IN(),
                                        "rdata_nsec3_fromWire1")));

    // Too short RDLENGTH
    EXPECT_THROW(rdataFactoryFromFile(RRType::NSEC3(), RRClass::IN(),
                                      "rdata_nsec3_fromWire2"),
                 InvalidRdataLength);

    // Invalid type bits
    EXPECT_THROW(rdataFactoryFromFile(RRType::NSEC3(), RRClass::IN(),
                                      "rdata_nsec3_fromWire3"),
                 DNSMessageFORMERR);
}

TEST_F(Rdata_NSEC3_Test, toWireRenderer) {
    renderer.skip(2);
    const generic::NSEC3 rdata_nsec3(nsec3_txt);
    rdata_nsec3.toWire(renderer);

    vector<unsigned char> data;
    UnitTestUtil::readWireData("rdata_nsec3_fromWire1", data);
    EXPECT_PRED_FORMAT4(UnitTestUtil::matchWireData,
                        static_cast<const uint8_t *>(obuffer.getData()) + 2,
                        obuffer.getLength() - 2, &data[2], data.size() - 2);
}

TEST_F(Rdata_NSEC3_Test, toWireBuffer) {
    const generic::NSEC3 rdata_nsec3(nsec3_txt);
    rdata_nsec3.toWire(obuffer);
}

TEST_F(Rdata_NSEC3_Test, assign) {
    generic::NSEC3 rdata_nsec3(nsec3_txt);
    generic::NSEC3 other_nsec3 = rdata_nsec3;
    EXPECT_EQ(0, rdata_nsec3.compare(other_nsec3));
}

}
