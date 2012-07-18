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
};
const TestRdata test_rdata_list[] = {
    {"IN", "A", "192.0.2.1"},
    {"IN", "NS", "ns.example.com"},
    {NULL, NULL, NULL}
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
    const Name dummy_name("example.com");
    MessageRenderer expected_renderer, actual_renderer;
    vector<uint8_t> encoded_data;
    vector<uint16_t> varlen_list;

    std::set<RRType> need_additionals;
    need_additionals.insert(RRType::NS());
    need_additionals.insert(RRType::MX());
    need_additionals.insert(RRType::SRV());

    for (size_t i = 1; test_rdata_list[i].rrclass != NULL; ++i) {
        SCOPED_TRACE(string(test_rdata_list->rrclass) + "/" +
                     test_rdata_list->rrtype);

        expected_renderer.clear();
        actual_renderer.clear();
        expected_renderer.writeName(dummy_name);
        actual_renderer.writeName(dummy_name);

        const RRClass rrclass(test_rdata_list[i].rrclass);
        const RRType rrtype(test_rdata_list[i].rrtype);
        const ConstRdataPtr rdata = createRdata(rrtype, rrclass,
                                                test_rdata_list[i].rdata);
        rdata->toWire(expected_renderer);

        const bool additional_required =
            (need_additionals.find(rrtype) != need_additionals.end());

        encodeRdata(*rdata, rrclass, rrtype, encoded_data, varlen_list);
        foreachRdataField(rrclass, rrtype, encoded_data, varlen_list,
                          boost::bind(renderNameField, &actual_renderer,
                                      additional_required, _1, _2),
                          boost::bind(renderDataField, &actual_renderer,
                                      _1, _2));

        matchWireData(expected_renderer.getData(),
                      expected_renderer.getLength(),
                      actual_renderer.getData(),
                      actual_renderer.getLength());
    }
}

}
