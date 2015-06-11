// Copyright (C) 2011, 2015  Internet Systems Consortium, Inc. ("ISC")
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

#include <vector>
#include <sstream>

#include <gtest/gtest.h>

#include <util/buffer.h>

#include <dns/exceptions.h>
#include <dns/messagerenderer.h>
#include <dns/name.h>
#include <dns/rdata.h>
#include <dns/rdataclass.h>
#include <dns/tsig.h>
#include <dns/tsigkey.h>
#include <dns/tsigrecord.h>

#include <dns/tests/unittest_util.h>
#include <util/unittests/wiredata.h>
#include <util/unittests/test_exceptions.h>

using namespace std;
using namespace isc::util;
using namespace isc::dns;
using namespace isc::dns::rdata;
using isc::UnitTestUtil;
using isc::util::unittests::matchWireData;

namespace {
class TSIGRecordTest : public ::testing::Test {
protected:
    TSIGRecordTest() :
        test_name("www.example.com"), test_mac(16, 0xda),
        test_rdata(any::TSIG(TSIGKey::HMACMD5_NAME(), 0x4da8877a,
                             TSIGContext::DEFAULT_FUDGE,
                             test_mac.size(), &test_mac[0],
                             0x2d65, 0, 0, NULL)),
        test_record(test_name, test_rdata),
        buffer(0)
    {}
    const Name test_name;
    vector<unsigned char> test_mac;
    const any::TSIG test_rdata;
    const TSIGRecord test_record;
    OutputBuffer buffer;
    MessageRenderer renderer;
    vector<unsigned char> data;
};

TEST_F(TSIGRecordTest, getName) {
    EXPECT_EQ(test_name, test_record.getName());
}

TEST_F(TSIGRecordTest, getLength) {
    // 85 = 17 + 26 + 16 + 26
    // len(www.example.com) = 17
    // len(hmac-md5.sig-alg.reg.int) = 26
    // len(MAC) = 16
    // the rest are fixed length fields (26 in total)
    EXPECT_EQ(85, test_record.getLength());
}

TEST_F(TSIGRecordTest, fromParams) {
    // Construct the same TSIG RR as test_record from parameters.
    // See the getLength test for the magic number of 85 (although it
    // actually doesn't matter)
    const TSIGRecord record(test_name, TSIGRecord::getClass(),
                            TSIGRecord::getTTL(), test_rdata, 85);
    // Perform straight sanity checks
    EXPECT_EQ(test_name, record.getName());
    EXPECT_EQ(85, record.getLength());
    EXPECT_EQ(0, test_rdata.compare(record.getRdata()));

    // The constructor doesn't check the length...
    EXPECT_NO_THROW(TSIGRecord(test_name, TSIGRecord::getClass(),
                               TSIGRecord::getTTL(), test_rdata, 82));
    // ...even for impossibly small values...
    EXPECT_NO_THROW(TSIGRecord(test_name, TSIGRecord::getClass(),
                               TSIGRecord::getTTL(), test_rdata, 1));
    // ...or too large values.
    EXPECT_NO_THROW(TSIGRecord(test_name, TSIGRecord::getClass(),
                               TSIGRecord::getTTL(), test_rdata, 65536));

    // RDATA must indeed be TSIG
    EXPECT_THROW_WITH(TSIGRecord(test_name, TSIGRecord::getClass(),
                                 TSIGRecord::getTTL(), in::A("192.0.2.1"), 85),
                      DNSMessageFORMERR,
                      "TSIG record is being constructed from "
                      "incompatible RDATA: 192.0.2.1");

    // Unexpected class
    EXPECT_THROW_WITH(TSIGRecord(test_name, RRClass::IN(),
                                 TSIGRecord::getTTL(),
                                 test_rdata, 85),
                      DNSMessageFORMERR,
                      "Unexpected TSIG RR class: " << RRClass::IN());

    // Unexpected TTL
    EXPECT_THROW_WITH(TSIGRecord(test_name, TSIGRecord::getClass(),
                                 RRTTL(3600), test_rdata, 85),
                      DNSMessageFORMERR,
                      "Unexpected TSIG TTL: " << RRTTL(3600));
}

TEST_F(TSIGRecordTest, recordToWire) {
    UnitTestUtil::readWireData("tsigrecord_toWire1.wire", data);
    EXPECT_EQ(1, test_record.toWire(renderer));
    matchWireData(&data[0], data.size(),
                  renderer.getData(), renderer.getLength());

    // Same test for a dumb buffer
    buffer.clear();
    EXPECT_EQ(1, test_record.toWire(buffer));
    matchWireData(&data[0], data.size(),
                  buffer.getData(), buffer.getLength());
}

TEST_F(TSIGRecordTest, recordToOLongToWire) {
    // By setting the limit to "record length - 1", it will fail, and the
    // renderer will be marked as "truncated".
    renderer.setLengthLimit(test_record.getLength() - 1);
    EXPECT_FALSE(renderer.isTruncated()); // not marked before render attempt
    EXPECT_EQ(0, test_record.toWire(renderer));
    EXPECT_TRUE(renderer.isTruncated());
}

TEST_F(TSIGRecordTest, recordToWireAfterNames) {
    // A similar test but the TSIG RR follows some domain names that could
    // cause name compression inside TSIG.  Our implementation shouldn't
    // compress either owner (key) name or the algorithm name.  This test
    // confirms that.

    UnitTestUtil::readWireData("tsigrecord_toWire2.wire", data);
    renderer.writeName(TSIGKey::HMACMD5_NAME());
    renderer.writeName(Name("foo.example.com"));
    EXPECT_EQ(1, test_record.toWire(renderer));
    matchWireData(&data[0], data.size(),
                  renderer.getData(), renderer.getLength());
}

TEST_F(TSIGRecordTest, toText) {
    EXPECT_EQ("www.example.com. 0 ANY TSIG hmac-md5.sig-alg.reg.int. "
              "1302890362 300 16 2tra2tra2tra2tra2tra2g== 11621 NOERROR 0\n",
              test_record.toText());
}

// test operator<<.  We simply confirm it appends the result of toText().
TEST_F(TSIGRecordTest, LeftShiftOperator) {
    ostringstream oss;
    oss << test_record;
    EXPECT_EQ(test_record.toText(), oss.str());
}
} // end namespace
