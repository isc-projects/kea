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

#include <dns/name.h>
#include <dns/labelsequence.h>
#include <dns/messagerenderer.h>
#include <dns/rdata.h>
#include <dns/rrclass.h>
#include <dns/rrtype.h>

#include <datasrc/memory/rdata_encoder.h>

#include <util/unittests/wiredata.h>

#include <gtest/gtest.h>

#include <boost/bind.hpp>

#include <set>
#include <string>
#include <vector>

using namespace isc::dns;
using namespace isc::dns::rdata;
using namespace isc::datasrc::memory;

using isc::util::unittests::matchWireData;
using std::string;
using std::vector;

namespace {
struct TestRdata {
    const char* const rrclass;
    const char* const rrtype;
    const char* const rdata;
    const size_t n_varlen_fields; // expected # of variable-len fields
};
const TestRdata test_rdata_list[] = {
    {"IN", "A", "192.0.2.1", 0},
    {"IN", "NS", "ns.example.com", 0},
    {"IN", "CNAME", "cname.example.com", 0},
    {"IN", "SOA", "ns.example.com root.example.com 0 0 0 0 0", 0},
    {"IN", "PTR", "reverse.example.com", 0},
    {"IN", "HINFO", "\"cpu-info\" \"OS-info\"", 1},
    {"IN", "MINFO", "root.example.com mbox.example.com", 0},
    {"IN", "MX", "10 mx.example.com", 0},
    {"IN", "TXT", "\"test1\" \"test 2\"", 1},
    {"IN", "RP", "root.example.com. rp-text.example.com", 0},
    {"IN", "AFSDB", "1 afsdb.example.com", 0},
    {"IN", "AAAA", "2001:db8::1", 0},
    {"IN", "SRV", "1 0 10 target.example.com", 0},
    {"IN", "NAPTR", "100 50 \"s\" \"http\" \"\" _http._tcp.example.com", 1},
    {"IN", "DNAME", "dname.example.com", 0},
    {"IN", "DS", "12892 5 2 5F0EB5C777586DE18DA6B5", 1},
    {"IN", "SSHFP", "1 1 dd465c09cfa51fb45020cc83316fff", 1},
    // Note: in our implementation RRSIG is treated as opaque data (including
    // the signer name).  We use "com" for signer so it won't be a compress
    // target in the test.
    {"IN", "RRSIG", "SOA 5 2 3600 20120814220826 20120715220826 12345 "
     "com. FAKEFAKEFAKE", 1},
    {"IN", "NSEC", "next.example.com. A AAAA NSEC RRSIG", 1},
    {"IN", "DNSKEY", "256 3 5 FAKEFAKE", 1},
    {"IN", "DHCID", "FAKEFAKE", 1},
    {"IN", "NSEC3", "1 1 12 AABBCCDD FAKEFAKE A RRSIG", 1},
    {"IN", "NSEC3PARAM", "1 0 12 AABBCCDD", 1},
    {"IN", "SPF", "v=spf1 +mx a:colo.example.com/28 -all", 1},
    {"IN", "DLV", "12892 5 2 5F0EB5C777586DE18DA6B5", 1},
    {"IN", "TYPE65000", "\\# 3 010203", 1}, // some "custom" type
    {"IN", "TYPE65535", "\\# 0", 1},        // max RR type, 0-length RDATA
    {"CH", "A", "\\# 2 0102", 1}, // A RR for non-IN class; varlen data
    {"CH", "NS", "ns.example.com", 0}, // class CH, generic data
    {"CH", "TXT", "BIND10", 1},        // ditto
    {"HS", "A", "\\# 5 0102030405", 1}, // A RR for non-IN class; varlen data
    {NULL, NULL, NULL, 0}
};

void
renderNameField(MessageRenderer* renderer, bool additional_required,
                const LabelSequence& labels, RdataNameAttributes attributes)
{
    EXPECT_EQ(additional_required,
              (attributes & NAMEATTR_ADDITIONAL) != 0);
    renderer->writeName(labels, (attributes & NAMEATTR_COMPRESSIBLE) != 0);
}

void
renderDataField(MessageRenderer* renderer, const uint8_t* data,
                size_t data_len)
{
    renderer->writeData(data, data_len);
}

TEST(RdataFieldSpec, checkData) {
    const Name dummy_name("com");
    const Name dummy_name2("example.com");
    MessageRenderer expected_renderer, actual_renderer;
    vector<uint8_t> encoded_data;
    vector<uint16_t> varlen_list;

    std::set<RRType> need_additionals;
    need_additionals.insert(RRType::NS());
    need_additionals.insert(RRType::MX());
    need_additionals.insert(RRType::SRV());

    for (size_t i = 1; test_rdata_list[i].rrclass != NULL; ++i) {
        SCOPED_TRACE(string(test_rdata_list[i].rrclass) + "/" +
                     test_rdata_list[i].rrtype);

        expected_renderer.clear();
        actual_renderer.clear();
        expected_renderer.writeName(dummy_name);
        actual_renderer.writeName(dummy_name);
        encoded_data.clear();
        varlen_list.clear();

        const RRClass rrclass(test_rdata_list[i].rrclass);
        const RRType rrtype(test_rdata_list[i].rrtype);
        const ConstRdataPtr rdata = createRdata(rrtype, rrclass,
                                                test_rdata_list[i].rdata);
        rdata->toWire(expected_renderer);
        expected_renderer.writeName(dummy_name2);

        const bool additional_required =
            (need_additionals.find(rrtype) != need_additionals.end());

        encodeRdata(*rdata, rrclass, rrtype, encoded_data, varlen_list);
        EXPECT_EQ(varlen_list.size(), test_rdata_list[i].n_varlen_fields);
        foreachRdataField(rrclass, rrtype, encoded_data, varlen_list,
                          boost::bind(renderNameField, &actual_renderer,
                                      additional_required, _1, _2),
                          boost::bind(renderDataField, &actual_renderer,
                                      _1, _2));

        actual_renderer.writeName(dummy_name2);
        matchWireData(expected_renderer.getData(),
                      expected_renderer.getLength(),
                      actual_renderer.getData(),
                      actual_renderer.getLength());
    }
}

}
