// Copyright (C) 2010-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <sstream>

#include <exceptions/exceptions.h>

#include <util/buffer.h>
#include <dns/edns.h>
#include <dns/exceptions.h>
#include <dns/message.h>
#include <dns/messagerenderer.h>
#include <dns/name.h>
#include <dns/rcode.h>
#include <dns/rdataclass.h>
#include <dns/rrclass.h>
#include <dns/rrttl.h>
#include <dns/rrtype.h>

#include <gtest/gtest.h>

#include <dns/tests/unittest_util.h>
#include <util/unittests/wiredata.h>

using namespace std;
using namespace isc::dns;
using namespace isc::util;
using namespace isc::dns::rdata;
using isc::UnitTestUtil;
using isc::util::unittests::matchWireData;

const uint8_t EDNS::SUPPORTED_VERSION;

namespace {
class EDNSTest : public ::testing::Test {
protected:
    EDNSTest() : rrtype(RRType::OPT()), buffer(NULL, 0), obuffer(0), rcode(0) {
        opt_rdata = ConstRdataPtr(new generic::OPT());
        edns_base.setUDPSize(4096);
    }
    RRType rrtype;
    EDNS edns_base;
    ConstEDNSPtr edns;
    InputBuffer buffer;
    OutputBuffer obuffer;
    MessageRenderer renderer;
    ConstRdataPtr opt_rdata;
    Rcode rcode;
    vector<unsigned char> wiredata;
};

// RRClass of EDNS OPT means UDP buffer size
const RRClass rrclass(4096);
// RRTTL of EDNS OPT encodes extended-rcode, version, and DO bit
const RRTTL rrttl_do_on(0x00008000); // DO=on
const RRTTL rrttl_do_off(0);         // DO=off
const RRTTL rrttl_badver(0x00018000); // version=1, DO=on

TEST_F(EDNSTest, badVerConstruct) {
    EXPECT_THROW(EDNS(1), isc::InvalidParameter);
}

TEST_F(EDNSTest, DNSSECDOBit) {
    // tests for EDNS from RR

    // DO bit is on, so DNSSEC should be considered to be supported.
    EXPECT_TRUE(EDNS(Name::ROOT_NAME(), rrclass, rrtype,
                     rrttl_do_on, *opt_rdata).getDNSSECAwareness());

    // DO bit is off.  DNSSEC should be considered to be unsupported.
    EXPECT_FALSE(EDNS(Name::ROOT_NAME(), rrclass, rrtype,
                      rrttl_do_off, *opt_rdata).getDNSSECAwareness());

    // tests for EDNS constructed by hand
    EXPECT_FALSE(edns_base.getDNSSECAwareness()); // false by default
    edns_base.setDNSSECAwareness(true);          // enable by hand
    EXPECT_TRUE(edns_base.getDNSSECAwareness());
    edns_base.setDNSSECAwareness(false); // disable by hand
    EXPECT_FALSE(edns_base.getDNSSECAwareness());
}

TEST_F(EDNSTest, UDPSize) {
    EXPECT_EQ(4096, EDNS(Name::ROOT_NAME(), rrclass, rrtype, rrttl_do_on,
                         *opt_rdata).getUDPSize());

    // EDNS UDP size smaller than the traditional max, 512.  Unusual, but
    // not prohibited.
    edns_base.setUDPSize(511);
    EXPECT_EQ(511, edns_base.getUDPSize());

    // Even 0 is okay.
    edns_base.setUDPSize(0);
    EXPECT_EQ(0, edns_base.getUDPSize());

    // Possible max value is also okay, although the higher layer app may
    // adjust it to a reasonably lower value
    edns_base.setUDPSize(65535);
    EXPECT_EQ(65535, edns_base.getUDPSize());
}

TEST_F(EDNSTest, getVersion) {
    // Constructed by hand
    EXPECT_EQ(EDNS::SUPPORTED_VERSION, EDNS().getVersion());

    // From RR
    EXPECT_EQ(EDNS::SUPPORTED_VERSION,
              EDNS(Name::ROOT_NAME(), rrclass, rrtype, rrttl_do_on,
                   *opt_rdata).getVersion());
}

TEST_F(EDNSTest, BadWireData) {
    // Incompatible RR type
    EXPECT_THROW(EDNS(Name::ROOT_NAME(), rrclass, RRType::A(),
                      rrttl_do_on, *opt_rdata), isc::InvalidParameter);

    // OPT RR of a non root name
    EXPECT_THROW(EDNS(Name("example.com"), rrclass, rrtype,
                      rrttl_do_on, *opt_rdata), DNSMessageFORMERR);
                 
    // Unsupported Version
    EXPECT_THROW(EDNS(Name::ROOT_NAME(), rrclass, rrtype,
                      rrttl_badver, *opt_rdata), DNSMessageBADVERS);
}

TEST_F(EDNSTest, toText) {
    // Typical case, disabling DNSSEC
    EXPECT_EQ("; EDNS: version: 0, flags:; udp: 4096\n",
              EDNS(Name::ROOT_NAME(), rrclass, rrtype, rrttl_do_off,
                   *opt_rdata).toText());

    // Typical case, enabling DNSSEC
    EXPECT_EQ("; EDNS: version: 0, flags: do; udp: 4096\n",
              EDNS(Name::ROOT_NAME(), rrclass, rrtype, rrttl_do_on,
                   *opt_rdata).toText());

    // Non-0 extended Rcode: ignored in the toText() output.
    EXPECT_EQ("; EDNS: version: 0, flags: do; udp: 4096\n",
              EDNS(Name::ROOT_NAME(), rrclass, rrtype,
                   RRTTL(0x01008000), *opt_rdata).toText());

    // Unknown flag: ignored in the toText() output.
    EXPECT_EQ("; EDNS: version: 0, flags: do; udp: 4096\n",
              EDNS(Name::ROOT_NAME(), rrclass, rrtype,
                   RRTTL(0x00008001), *opt_rdata).toText());
}

TEST_F(EDNSTest, toWireRenderer) {
    // Typical case, (explicitly) disabling DNSSEC
    edns_base.setDNSSECAwareness(false);
    EXPECT_EQ(1, edns_base.toWire(renderer,
                                  Rcode::NOERROR().getExtendedCode()));
    UnitTestUtil::readWireData("edns_toWire1.wire", wiredata);
    matchWireData(&wiredata[0], wiredata.size(),
                  renderer.getData(), renderer.getLength());

    // Typical case, enabling DNSSEC
    renderer.clear();
    wiredata.clear();
    edns_base.setDNSSECAwareness(true);
    EXPECT_EQ(1, edns_base.toWire(renderer,
                                  Rcode::NOERROR().getExtendedCode()));
    UnitTestUtil::readWireData("edns_toWire2.wire", wiredata);
    matchWireData(&wiredata[0], wiredata.size(),
                  renderer.getData(), renderer.getLength());

    // Non-0 extended Rcode
    renderer.clear();
    wiredata.clear();
    edns_base.setDNSSECAwareness(true);
    EXPECT_EQ(1, edns_base.toWire(renderer,
                                  Rcode::BADVERS().getExtendedCode()));
    UnitTestUtil::readWireData("edns_toWire3.wire", wiredata);
    matchWireData(&wiredata[0], wiredata.size(),
                  renderer.getData(), renderer.getLength());

    // Uncommon UDP buffer size
    renderer.clear();
    wiredata.clear();
    edns_base.setDNSSECAwareness(true);
    edns_base.setUDPSize(511);
    EXPECT_EQ(1, edns_base.toWire(renderer,
                                  Rcode::NOERROR().getExtendedCode()));
    UnitTestUtil::readWireData("edns_toWire4.wire", wiredata);
    matchWireData(&wiredata[0], wiredata.size(),
                  renderer.getData(), renderer.getLength());

    // From RR with unknown flag.  If used for toWire(), the unknown flag
    // should disappear.
    renderer.clear();
    wiredata.clear();
    EXPECT_EQ(1, EDNS(Name::ROOT_NAME(), rrclass, rrtype, RRTTL(0x00008001),
                      *opt_rdata).toWire(renderer,
                                         Rcode::NOERROR().getExtendedCode()));
    UnitTestUtil::readWireData("edns_toWire2.wire", wiredata);
    matchWireData(&wiredata[0], wiredata.size(),
                  renderer.getData(), renderer.getLength());

    // If the available length in the renderer is not sufficient for the OPT
    // RR, it shouldn't be inserted.
    renderer.clear();
    renderer.setLengthLimit(10); // 10 = minimum length of OPT RR - 1
    edns_base.setDNSSECAwareness(true);
    edns_base.setUDPSize(4096);
    EXPECT_EQ(0, edns_base.toWire(renderer,
                                  Rcode::NOERROR().getExtendedCode()));
    // renderer should be intact
    EXPECT_EQ(0, renderer.getLength());
}

TEST_F(EDNSTest, toWireBuffer) {
    // "to renderer" and "to buffer" should generally produce the same result.
    // for simplicity we only check one typical case to confirm that.
    EXPECT_EQ(1, edns_base.toWire(obuffer,
                                  Rcode::NOERROR().getExtendedCode()));
    UnitTestUtil::readWireData("edns_toWire1.wire", wiredata);
    matchWireData(&wiredata[0], wiredata.size(),
                  obuffer.getData(), obuffer.getLength());
}

TEST_F(EDNSTest, createFromRR) {
    uint8_t extended_rcode;

    // normal case
    edns = ConstEDNSPtr(createEDNSFromRR(Name::ROOT_NAME(), rrclass, rrtype,
                                         rrttl_do_on, *opt_rdata,
                                         extended_rcode));
    EXPECT_EQ(EDNS::SUPPORTED_VERSION, edns->getVersion());
    EXPECT_TRUE(edns->getDNSSECAwareness());
    EXPECT_EQ(4096, edns->getUDPSize());
    EXPECT_EQ(0, static_cast<int>(extended_rcode));

    // non-0 extended rcode
    extended_rcode = 0;
    ConstEDNSPtr(createEDNSFromRR(Name::ROOT_NAME(), rrclass, rrtype,
                                  RRTTL(0x01008000), *opt_rdata,
                                  extended_rcode));
    EXPECT_EQ(1, static_cast<int>(extended_rcode));

    // creation triggers an exception.  extended_rcode must be intact.
    extended_rcode = 0;
    EXPECT_THROW(createEDNSFromRR(Name::ROOT_NAME(), rrclass, rrtype,
                                  rrttl_badver, *opt_rdata, extended_rcode),
                 DNSMessageBADVERS);
    EXPECT_EQ(0, static_cast<int>(extended_rcode));
}

// test operator<<.  We simply confirm it appends the result of toText().
TEST_F(EDNSTest, LeftShiftOperator) {
    ostringstream oss;
    oss << edns_base;
    EXPECT_EQ(edns_base.toText(), oss.str());
}
}
