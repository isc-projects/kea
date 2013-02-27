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

#include <exceptions/exceptions.h>

#include <util/buffer.h>

#include <dns/name.h>
#include <dns/labelsequence.h>
#include <dns/messagerenderer.h>
#include <dns/rdata.h>
#include <dns/rdataclass.h>
#include <dns/rrclass.h>
#include <dns/rrtype.h>

#include <datasrc/memory/rdata_serialization.h>

#include <util/unittests/wiredata.h>

#include <gtest/gtest.h>

#include <boost/bind.hpp>
#include <boost/foreach.hpp>

#include <cstring>
#include <algorithm>
#include <set>
#include <stdexcept>
#include <string>
#include <vector>

using namespace isc::dns;
using namespace isc::dns::rdata;
using namespace isc::datasrc::memory;

using isc::util::unittests::matchWireData;
using std::string;
using std::vector;

// A trick to steal some private definitions of the implementation we use here

namespace isc {
namespace datasrc{
namespace memory {

#include <datasrc/memory/rdata_serialization_priv.cc>

}
}
}

namespace {
// This defines a tuple of test data used in test_rdata_list below.
struct TestRdata {
    const char* const rrclass;  // RR class, textual form
    const char* const rrtype;   // RR type, textual form
    const char* const rdata;    // textual RDATA
    const size_t n_varlen_fields; // expected # of variable-len fields
};

// This test data consist of (almost) all supported types of RDATA (+ some
// unusual and corner cases).
const TestRdata test_rdata_list[] = {
    {"IN", "A", "192.0.2.1", 0},
    {"IN", "NS", "ns.example.com.", 0},
    {"IN", "CNAME", "cname.example.com.", 0},
    {"IN", "SOA", "ns.example.com. root.example.com. 0 0 0 0 0", 0},
    {"IN", "PTR", "reverse.example.com.", 0},
    {"IN", "HINFO", "\"cpu-info\" \"OS-info\"", 1},
    {"IN", "MINFO", "root.example.com. mbox.example.com.", 0},
    {"IN", "MX", "10 mx.example.com.", 0},
    {"IN", "TXT", "\"test1\" \"test 2\"", 1},
    {"IN", "RP", "root.example.com. rp-text.example.com.", 0},
    {"IN", "AFSDB", "1 afsdb.example.com.", 0},
    {"IN", "AAAA", "2001:db8::1", 0},
    {"IN", "SRV", "1 0 10 target.example.com.", 0},
    {"IN", "NAPTR", "100 50 \"s\" \"http\" \"\" _http._tcp.example.com.", 1},
    {"IN", "DNAME", "dname.example.com.", 0},
    {"IN", "DS", "12892 5 2 5F0EB5C777586DE18DA6B5", 1},
    {"IN", "SSHFP", "1 1 dd465c09cfa51fb45020cc83316fff", 1},
    // We handle RRSIG separately, so it's excluded from the list
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
    {"CH", "NS", "ns.example.com.", 0}, // class CH, generic data
    {"CH", "TXT", "BIND10", 1},        // ditto
    {"HS", "A", "\\# 5 0102030405", 1}, // A RR for non-IN class; varlen data
    {NULL, NULL, NULL, 0}
};

// The following two functions will be used to generate wire format data
// from encoded representation of each RDATA.
void
renderNameField(MessageRenderer* renderer, bool additional_required,
                const LabelSequence& labels, RdataNameAttributes attributes)
{
    EXPECT_EQ(additional_required, (attributes & NAMEATTR_ADDITIONAL) != 0);
    renderer->writeName(labels, (attributes & NAMEATTR_COMPRESSIBLE) != 0);
}

void
renderDataField(MessageRenderer* renderer, const void* data, size_t data_len) {
    renderer->writeData(data, data_len);
}

class RdataSerializationTest : public ::testing::Test {
protected:
    RdataSerializationTest() : a_rdata_(createRdata(RRType::A(), RRClass::IN(),
                                                    "192.0.2.53")),
                         aaaa_rdata_(createRdata(RRType::AAAA(), RRClass::IN(),
                                                 "2001:db8::53")),
                         rrsig_rdata_(createRdata(
                                          RRType::RRSIG(), RRClass::IN(),
                                          "A 5 2 3600 20120814220826 "
                                          "20120715220826 12345 com. FAKE"))
    {}

    // A wrapper for RdataEncoder::encode() with buffer overrun check.
    void encodeWrapper(size_t data_len);

    // Some commonly used RDATA
    const ConstRdataPtr a_rdata_;
    const ConstRdataPtr aaaa_rdata_;
    const ConstRdataPtr rrsig_rdata_;

    RdataEncoder encoder_;
    vector<uint8_t> encoded_data_;
    MessageRenderer expected_renderer_;
    MessageRenderer actual_renderer_;
    vector<ConstRdataPtr> rdata_list_;
};

// There are several ways to decode the data. For one, there are
// more interfaces uses for RdataReader, and we use our own decoder,
// to check the actual encoded data.
//
// These decoding ways are provided by the template parameter.
template<class DecoderStyle>
class RdataEncodeDecodeTest : public RdataSerializationTest {
public:
    // This helper test method encodes the given list of RDATAs
    // (in rdata_list), and then iterates over the data, rendering the fields
    // in the wire format.  It then compares the wire data with the one
    // generated by the normal libdns++ interface to see the encoding/decoding
    // works as intended.
    // By default it encodes the given RDATAs from the scratch; if old_data
    // is non NULL, the test case assumes it points to previously encoded data
    // and the given RDATAs are to be merged with it.  old_rdata/rrsig_count
    // will be set to the number of RDATAs and RRSIGs encoded in old_data.
    // These "count" variables must not be set to non 0 unless old_data is
    // non NULL, but it's not checked in this methods; it's the caller's
    // responsibility to ensure that.  rdata_list and rrsig_list should contain
    // all RDATAs and RRSIGs included those stored in old_data.
    void checkEncode(RRClass rrclass, RRType rrtype,
                     const vector<ConstRdataPtr>& rdata_list,
                     size_t expected_varlen_fields,
                     const vector<ConstRdataPtr>& rrsig_list =
                     vector<ConstRdataPtr>(),
                     const void* old_data = NULL,
                     size_t old_rdata_count = 0,
                     size_t old_rrsig_count = 0);

    void addRdataCommon(const vector<ConstRdataPtr>& rrsigs);
    void addRdataMultiCommon(const vector<ConstRdataPtr>& rrsigs,
                             bool duplicate = false);
    void mergeRdataCommon(const vector<ConstRdataPtr>& old_rrsigs,
                          const vector<ConstRdataPtr>& rrsigs);
};

// Used across more classes and scopes. But it's just uninteresting
// constant.
const Name& dummyName2() {
    static const Name result("example.com");
    return (result);
}

bool
additionalRequired(const RRType& type) {
    // The set of RR types that require additional section processing.
    // We'll use it to determine what value should the renderNameField get
    // and, if the stored attributes are as expected.
    static std::set<RRType> need_additionals;
    if (need_additionals.empty()) {
        need_additionals.insert(RRType::NS());
        need_additionals.insert(RRType::MX());
        need_additionals.insert(RRType::SRV());
    }

    return (need_additionals.find(type) != need_additionals.end());
}

// A decoder that does not use RdataReader. Not recommended for use,
// but it allows the tests to check the internals of the data.
class ManualDecoderStyle {
public:
    static void foreachRdataField(RRClass rrclass, RRType rrtype,
                                  size_t rdata_count,
                                  const vector<uint8_t>& encoded_data,
                                  const vector<uint16_t>& varlen_list,
                                  RdataReader::NameAction name_callback,
                                  RdataReader::DataAction data_callback)
    {
        const RdataEncodeSpec& encode_spec = getRdataEncodeSpec(rrclass,
                                                                rrtype);

        size_t off = 0;
        size_t varlen_count = 0;
        size_t name_count = 0;
        for (size_t count = 0; count < rdata_count; ++count) {
            for (size_t i = 0; i < encode_spec.field_count; ++i) {
                const RdataFieldSpec& field_spec = encode_spec.fields[i];
                switch (field_spec.type) {
                    case RdataFieldSpec::FIXEDLEN_DATA:
                        if (data_callback) {
                            data_callback(&encoded_data.at(off),
                                          field_spec.fixeddata_len);
                        }
                        off += field_spec.fixeddata_len;
                        break;
                    case RdataFieldSpec::VARLEN_DATA:
                        {
                            const size_t varlen = varlen_list.at(varlen_count);
                            if (data_callback && varlen > 0) {
                                data_callback(&encoded_data.at(off), varlen);
                            }
                            off += varlen;
                            ++varlen_count;
                            break;
                        }
                    case RdataFieldSpec::DOMAIN_NAME:
                        {
                            ++name_count;
                            const LabelSequence labels(&encoded_data.at(off));
                            if (name_callback) {
                                name_callback(labels,
                                              field_spec.name_attributes);
                            }
                            off += labels.getSerializedLength();
                            break;
                        }
                }
            }
        }
        assert(name_count == encode_spec.name_count * rdata_count);
        assert(varlen_count == encode_spec.varlen_count * rdata_count);
    }

    static void foreachRRSig(const vector<uint8_t>& encoded_data,
                             const vector<uint16_t>& rrsiglen_list,
                             RdataReader::DataAction data_callback)
    {
        size_t rrsig_totallen = 0;
        for (vector<uint16_t>::const_iterator it = rrsiglen_list.begin();
             it != rrsiglen_list.end();
             ++it) {
            rrsig_totallen += *it;
        }
        assert(encoded_data.size() >= rrsig_totallen);

        const uint8_t* dp = &encoded_data[encoded_data.size() -
            rrsig_totallen];
        for (size_t i = 0; i < rrsiglen_list.size(); ++i) {
            data_callback(dp, rrsiglen_list[i]);
            dp += rrsiglen_list[i];
        }
    }

    static void decode(const isc::dns::RRClass& rrclass,
                       const isc::dns::RRType& rrtype,
                       size_t rdata_count,
                       size_t rrsig_count,
                       size_t expected_varlen_fields,
                       const vector<uint8_t>& encoded_data_orig, size_t,
                       MessageRenderer& renderer)
    {
        // Make a manual copy, which we're going to modify.
        vector<uint8_t> encoded_data = encoded_data_orig;

        // If this type of RDATA is expected to contain variable-length fields,
        // we brute force the encoded data, exploiting our knowledge of actual
        // encoding, then adjust the encoded data excluding the list of length
        // fields.  This is ugly, but for tests only.
        vector<uint16_t> varlen_list;
        if (expected_varlen_fields > 0) {
            const size_t varlen_list_size =
                rdata_count * expected_varlen_fields * sizeof(uint16_t);
            ASSERT_LE(varlen_list_size, encoded_data.size());
            varlen_list.resize(rdata_count * expected_varlen_fields);
            std::memcpy(&varlen_list[0], &encoded_data[0], varlen_list_size);
            encoded_data.assign(encoded_data.begin() + varlen_list_size,
                                encoded_data.end());
        }

        // If RRSIGs are given, we need to extract the list of the RRSIG
        // lengths and adjust encoded_data_ further.
        vector<uint16_t> rrsiglen_list;
        if (rrsig_count > 0) {
            const size_t rrsig_len_size = rrsig_count * sizeof(uint16_t);
            ASSERT_LE(rrsig_len_size, encoded_data.size());
            rrsiglen_list.resize(rrsig_count * rrsig_len_size);
            std::memcpy(&rrsiglen_list[0], &encoded_data[0], rrsig_len_size);
            encoded_data.assign(encoded_data.begin() + rrsig_len_size,
                                encoded_data.end());
        }

        // Create wire-format data from the encoded data
        foreachRdataField(rrclass, rrtype, rdata_count, encoded_data,
                          varlen_list,
                          boost::bind(renderNameField, &renderer,
                                      additionalRequired(rrtype), _1, _2),
                          boost::bind(renderDataField, &renderer, _1, _2));

        // 2nd dummy name
        renderer.writeName(dummyName2());
        // Finally, dump any RRSIGs in wire format.
        foreachRRSig(encoded_data, rrsiglen_list,
                     boost::bind(renderDataField, &renderer, _1, _2));
    }
};

// Check using callbacks and calling next until the end.
class CallbackDecoder {
public:
    static void decode(const isc::dns::RRClass& rrclass,
                       const isc::dns::RRType& rrtype,
                       size_t rdata_count, size_t sig_count, size_t,
                       const vector<uint8_t>& encoded_data, size_t,
                       MessageRenderer& renderer)
    {
        RdataReader reader(rrclass, rrtype, &encoded_data[0], rdata_count,
                           sig_count,
                           boost::bind(renderNameField, &renderer,
                                       additionalRequired(rrtype), _1, _2),
                           boost::bind(renderDataField, &renderer, _1, _2));
        while (reader.next() != RdataReader::RRSET_BOUNDARY) {}
        renderer.writeName(dummyName2());
        while (reader.nextSig() != RdataReader::RRSET_BOUNDARY) {}
    }
};

// Check using callbacks and calling iterate.
class IterateDecoder {
public:
    static void decode(const isc::dns::RRClass& rrclass,
                       const isc::dns::RRType& rrtype,
                       size_t rdata_count, size_t sig_count, size_t,
                       const vector<uint8_t>& encoded_data, size_t,
                       MessageRenderer& renderer)
    {
        RdataReader reader(rrclass, rrtype, &encoded_data[0],
                           rdata_count, sig_count,
                           boost::bind(renderNameField, &renderer,
                                       additionalRequired(rrtype), _1, _2),
                           boost::bind(renderDataField, &renderer, _1, _2));
        reader.iterate();
        renderer.writeName(dummyName2());
        reader.iterateAllSigs();
    }
};

namespace {

// Render the data to renderer, if one is set, or put it inside
// a data buffer.
void
appendOrRenderData(vector<uint8_t>* where, MessageRenderer** renderer,
                   const void* data, size_t size)
{
    if (*renderer != NULL) {
        (*renderer)->writeData(data, size);
    } else {
        where->insert(where->end(), reinterpret_cast<const uint8_t*>(data),
                      reinterpret_cast<const uint8_t*>(data) + size);
    }
}

}

// Similar to IterateDecoder, but it first iterates a little and rewinds
// before actual rendering.
class RewindAndDecode {
private:
    static void writeName(MessageRenderer** renderer,
                          const LabelSequence& labels,
                          RdataNameAttributes attributes)
    {
        (*renderer)->writeName(labels,
                               (attributes & NAMEATTR_COMPRESSIBLE) != 0);
    }
public:
    static void decode(const isc::dns::RRClass& rrclass,
                       const isc::dns::RRType& rrtype,
                       size_t rdata_count, size_t sig_count, size_t,
                       const vector<uint8_t>& encoded_data, size_t,
                       MessageRenderer& renderer)
    {
        MessageRenderer dump; // A place to dump the extra data from before
                              // actual rendering.
        MessageRenderer* current = &dump;
        vector<uint8_t> placeholder; // boost::bind does not like NULL
        RdataReader reader(rrclass, rrtype, &encoded_data[0],
                           rdata_count, sig_count,
                           boost::bind(writeName, &current, _1, _2),
                           boost::bind(appendOrRenderData, &placeholder,
                                       &current, _1, _2));
        // Iterate a little and rewind
        reader.next();
        reader.nextSig();
        reader.rewind();
        // Do the actual rendering
        // cppcheck-suppress unreadVariable
        current = &renderer;
        reader.iterate();
        renderer.writeName(dummyName2());
        reader.iterateAllSigs();
    }
};

// Decode using the iteration over one rdata each time.
// We also count there's the correct count of Rdatas.
class SingleIterateDecoder {
public:
    static void decode(const isc::dns::RRClass& rrclass,
                       const isc::dns::RRType& rrtype,
                       size_t rdata_count, size_t sig_count, size_t,
                       const vector<uint8_t>& encoded_data, size_t,
                       MessageRenderer& renderer)
    {
        RdataReader reader(rrclass, rrtype, &encoded_data[0],
                           rdata_count, sig_count,
                           boost::bind(renderNameField, &renderer,
                                       additionalRequired(rrtype), _1, _2),
                           boost::bind(renderDataField, &renderer, _1, _2));
        size_t actual_count = 0;
        while (reader.iterateRdata()) {
            ++actual_count;
        }
        EXPECT_EQ(rdata_count, actual_count);
        actual_count = 0;
        renderer.writeName(dummyName2());
        while (reader.iterateSingleSig()) {
            ++actual_count;
        }
        EXPECT_EQ(sig_count, actual_count);
    }
};

// This one does not adhere to the usual way the reader is used, trying
// to confuse it. It iterates part of the data manually and then reads
// the rest through iterate. It also reads the signatures in the middle
// of rendering.
template<bool start_data, bool start_sig>
class HybridDecoder {
public:
    static void decode(const isc::dns::RRClass& rrclass,
                       const isc::dns::RRType& rrtype,
                       size_t rdata_count, size_t sig_count, size_t,
                       const vector<uint8_t>& encoded_data,
                       size_t encoded_data_len,
                       MessageRenderer& renderer)
    {
        vector<uint8_t> data;
        MessageRenderer* current;
        RdataReader reader(rrclass, rrtype, &encoded_data[0],
                           rdata_count, sig_count,
                           boost::bind(renderNameField, &renderer,
                                       additionalRequired(rrtype), _1, _2),
                           boost::bind(appendOrRenderData, &data, &current, _1,
                                       _2));
        // The size matches
        EXPECT_EQ(encoded_data_len, reader.getSize());
        if (start_sig) {
            current = NULL;
            reader.nextSig();
        }
        // Render first part of data. If there's none, return empty Result and
        // do nothing.
        if (start_data) {
            current = &renderer;
            reader.next();
        }
        // Now, we let all sigs to be copied to data. We disable the
        // renderer for this.
        current = NULL;
        reader.iterateAllSigs();
        // Now return the renderer and render the rest of the data
        // cppcheck-suppress redundantAssignment
        // cppcheck-suppress unreadVariable
        current = &renderer;
        reader.iterate();
        // Now, this should not break anything and should be valid, but should
        // return ends.
        EXPECT_EQ(RdataReader::RRSET_BOUNDARY, reader.next());
        EXPECT_EQ(RdataReader::RRSET_BOUNDARY, reader.nextSig());
        // Render the name and the sigs
        renderer.writeName(dummyName2());
        renderer.writeData(&data[0], data.size());
        // The size matches even after use
        EXPECT_EQ(encoded_data_len, reader.getSize());
    }
};

typedef ::testing::Types<ManualDecoderStyle,
                         CallbackDecoder, IterateDecoder, SingleIterateDecoder,
                         HybridDecoder<true, true>, HybridDecoder<true, false>,
                         HybridDecoder<false, true>,
                         HybridDecoder<false, false> >
    DecoderStyles;
// Each decoder style must contain a decode() method. Such method is expected
// to decode the passed data, first render the Rdata into the passed renderer,
// then write the dummyName2() there and write the RRSig data after that.
// It may do other checks too.
//
// There are some slight differences to how to do the decoding, that's why we
// have the typed test.
TYPED_TEST_CASE(RdataEncodeDecodeTest, DecoderStyles);

void
RdataSerializationTest::encodeWrapper(size_t data_len) {
    // make sure the data buffer is large enough for the canary
    encoded_data_.resize(data_len + 2);
    // set the canary data
    encoded_data_.at(data_len) = 0xde;
    encoded_data_.at(data_len + 1) = 0xad;
    // encode, then check the canary is intact
    encoder_.encode(&encoded_data_[0], data_len);
    EXPECT_EQ(0xde, encoded_data_.at(data_len));
    EXPECT_EQ(0xad, encoded_data_.at(data_len + 1));
    // shrink the data buffer to the originally expected size (some tests
    // expect that).  the actual encoded data should be intact.
    encoded_data_.resize(data_len);
}

bool
rdataMatch(ConstRdataPtr rdata1, ConstRdataPtr rdata2) {
    return (rdata1->compare(*rdata2) == 0);
}

template<class DecoderStyle>
void
RdataEncodeDecodeTest<DecoderStyle>::
checkEncode(RRClass rrclass, RRType rrtype,
            const vector<ConstRdataPtr>& rdata_list,
            size_t expected_varlen_fields,
            const vector<ConstRdataPtr>& rrsig_list,
            const void* old_data, size_t old_rdata_count,
            size_t old_rrsig_count)
{
    // These two names will be rendered before and after the test RDATA,
    // to check in case the RDATA contain a domain name whether it's
    // compressed or not correctly.  The names in the RDATA should basically
    // a subdomain of example.com, so it can be compressed due to dummyName2().
    // Likewise, dummyName2() should be able to be fully compressed due to
    // the name in the RDATA.
    const Name dummy_name("com");

    expected_renderer_.clear();
    actual_renderer_.clear();
    encoded_data_.clear();

    // Build expected wire-format data, skipping duplicate Rdata.
    expected_renderer_.writeName(dummy_name);
    vector<ConstRdataPtr> rdata_uniq_list;
    BOOST_FOREACH(const ConstRdataPtr& rdata, rdata_list) {
        if (std::find_if(rdata_uniq_list.begin(), rdata_uniq_list.end(),
                         boost::bind(rdataMatch, rdata, _1)) ==
            rdata_uniq_list.end()) {
            rdata_uniq_list.push_back(rdata);
            rdata->toWire(expected_renderer_);
        }
    }
    expected_renderer_.writeName(dummyName2());
    vector<ConstRdataPtr> rrsig_uniq_list;
    BOOST_FOREACH(const ConstRdataPtr& rdata, rrsig_list) {
        if (std::find_if(rrsig_uniq_list.begin(), rrsig_uniq_list.end(),
                         boost::bind(rdataMatch, rdata, _1)) ==
            rrsig_uniq_list.end()) {
            rrsig_uniq_list.push_back(rdata);
            rdata->toWire(expected_renderer_);
        }
    }

    // Then build wire format data using the encoded data.
    // 1st dummy name
    actual_renderer_.writeName(dummy_name);

    // Create encoded data.  If old_xxx_count > 0, that part should be in
    // old_data, so should be excluded from addRdata/addSIGRdata.
    if (old_data) {
        encoder_.start(rrclass, rrtype, old_data, old_rdata_count,
                       old_rrsig_count);
    } else {
        encoder_.start(rrclass, rrtype);
    }
    size_t count = 0;
    std::vector<ConstRdataPtr> encoded; // for duplicate check include old
    BOOST_FOREACH(const ConstRdataPtr& rdata, rdata_list) {
        if (++count > old_rdata_count) {
            const bool uniq =
                (std::find_if(encoded.begin(), encoded.end(),
                              boost::bind(rdataMatch, rdata, _1)) ==
                 encoded.end());
            EXPECT_EQ(uniq, encoder_.addRdata(*rdata));
        }
        encoded.push_back(rdata); // we need to remember old rdata too
    }
    count = 0;
    encoded.clear();
    BOOST_FOREACH(const ConstRdataPtr& rdata, rrsig_list) {
        if (++count > old_rrsig_count) {
            const bool uniq =
                (std::find_if(encoded.begin(), encoded.end(),
                              boost::bind(rdataMatch, rdata, _1)) ==
                 encoded.end());
            EXPECT_EQ(uniq, encoder_.addSIGRdata(*rdata));
        }
        encoded.push_back(rdata);
    }
    const size_t storage_len = encoder_.getStorageLength();
    encodeWrapper(storage_len);

    DecoderStyle::decode(rrclass, rrtype, rdata_uniq_list.size(),
                         rrsig_uniq_list.size(), expected_varlen_fields,
                         encoded_data_, storage_len, actual_renderer_);

    // Two sets of wire-format data should be identical.
    matchWireData(expected_renderer_.getData(), expected_renderer_.getLength(),
                  actual_renderer_.getData(), actual_renderer_.getLength());
}

template<class DecoderStyle>
void
RdataEncodeDecodeTest<DecoderStyle>::
addRdataCommon(const vector<ConstRdataPtr>& rrsigs) {
    // Basic check on the encoded data for (most of) all supported RR types,
    // in a comprehensive manner.
    for (size_t i = 0; test_rdata_list[i].rrclass != NULL; ++i) {
        SCOPED_TRACE(string(test_rdata_list[i].rrclass) + "/" +
                     test_rdata_list[i].rrtype);
        const RRClass rrclass(test_rdata_list[i].rrclass);
        const RRType rrtype(test_rdata_list[i].rrtype);
        const ConstRdataPtr rdata = createRdata(rrtype, rrclass,
                                                test_rdata_list[i].rdata);
        rdata_list_.clear();
        rdata_list_.push_back(rdata);
        checkEncode(rrclass, rrtype, rdata_list_,
                    test_rdata_list[i].n_varlen_fields, rrsigs);
    }
}

TYPED_TEST(RdataEncodeDecodeTest, addRdata) {
    vector<ConstRdataPtr> rrsigs;
    this->addRdataCommon(rrsigs); // basic tests without RRSIGs (empty vector)

    // Test with RRSIGs (covered type doesn't always match, but the encoder
    // doesn't check that)
    rrsigs.push_back(this->rrsig_rdata_);
    this->addRdataCommon(rrsigs);
}

template<class DecoderStyle>
void
RdataEncodeDecodeTest<DecoderStyle>::
addRdataMultiCommon(const vector<ConstRdataPtr>& rrsigs, bool duplicate) {
    // Similar to addRdata(), but test with multiple RDATAs.
    // Four different cases are tested: a single fixed-len RDATA (A),
    // fixed-len data + domain name (MX), variable-len data only (TXT),
    // variable-len data + domain name (NAPTR).
    ConstRdataPtr a_rdata2 = createRdata(RRType::A(), RRClass::IN(),
                                         "192.0.2.54");
    rdata_list_.clear();
    rdata_list_.push_back(a_rdata_);
    rdata_list_.push_back(a_rdata2);
    if (duplicate) {      // if duplicate is true, add duplicate Rdata
        rdata_list_.push_back(a_rdata_);
    }
    checkEncode(RRClass::IN(), RRType::A(), rdata_list_, 0, rrsigs);

    ConstRdataPtr mx_rdata1 = createRdata(RRType::MX(), RRClass::IN(),
                                          "5 mx1.example.com.");
    ConstRdataPtr mx_rdata2 = createRdata(RRType::MX(), RRClass::IN(),
                                          "10 mx2.example.com.");
    if (duplicate) { // check duplicate detection is case insensitive for names
        rdata_list_.push_back(createRdata(RRType::MX(), RRClass::IN(),
                                          "5 MX1.example.COM."));
    }
    rdata_list_.clear();
    rdata_list_.push_back(mx_rdata1);
    rdata_list_.push_back(mx_rdata2);
    checkEncode(RRClass::IN(), RRType::MX(), rdata_list_, 0, rrsigs);

    ConstRdataPtr txt_rdata1 = createRdata(RRType::TXT(), RRClass::IN(),
                                           "foo bar baz");
    ConstRdataPtr txt_rdata2 = createRdata(RRType::TXT(), RRClass::IN(),
                                          "another text data");
    if (duplicate) {
        rdata_list_.push_back(txt_rdata1);
    }
    rdata_list_.clear();
    rdata_list_.push_back(txt_rdata1);
    rdata_list_.push_back(txt_rdata2);
    checkEncode(RRClass::IN(), RRType::TXT(), rdata_list_, 1, rrsigs);

    ConstRdataPtr naptr_rdata1 =
        createRdata(RRType::NAPTR(), RRClass::IN(),
                    "100 50 \"s\" \"http\" \"\" _http._tcp.example.com");
    ConstRdataPtr naptr_rdata2 =
        createRdata(RRType::NAPTR(), RRClass::IN(),
                    "200 100 \"s\" \"http\" \"\" _http._tcp.example.com");
    if (duplicate) {
        rdata_list_.push_back(naptr_rdata1);
    }
    rdata_list_.clear();
    rdata_list_.push_back(naptr_rdata1);
    rdata_list_.push_back(naptr_rdata2);
    checkEncode(RRClass::IN(), RRType::NAPTR(), rdata_list_, 1, rrsigs);
}

void ignoreName(const LabelSequence&, unsigned) {
}

void
checkLargeData(const in::DHCID* decoded, bool* called, const void* encoded,
               size_t length)
{
    EXPECT_FALSE(*called); // Called exactly once
    *called = true;

    // Reconstruct the Rdata and check it.
    isc::util::InputBuffer ib(encoded, length);
    const in::DHCID reconstructed(ib, ib.getLength());
    EXPECT_EQ(0, reconstructed.compare(*decoded));
}

TEST_F(RdataSerializationTest, encodeLargeRdata) {
    // There should be no reason for a large RDATA to fail in encoding,
    // but we check such a case explicitly.

    encoded_data_.resize(65535); // max unsigned 16-bit int
    isc::util::InputBuffer buffer(&encoded_data_[0], encoded_data_.size());
    const in::DHCID large_dhcid(buffer, encoded_data_.size());

    encoder_.start(RRClass::IN(), RRType::DHCID());
    encoder_.addRdata(large_dhcid);
    encodeWrapper(encoder_.getStorageLength());

    // The encoded data should be identical to the original one.
    bool called = false;
    RdataReader reader(RRClass::IN(), RRType::DHCID(), &encoded_data_[0], 1, 0,
                       ignoreName, boost::bind(checkLargeData, &large_dhcid,
                                               &called, _1, _2));
    reader.iterate();
    EXPECT_TRUE(called);
    called = false;
    reader.iterateAllSigs();
    EXPECT_FALSE(called);
}

TYPED_TEST(RdataEncodeDecodeTest, addRdataMulti) {
    vector<ConstRdataPtr> rrsigs;
    this->addRdataMultiCommon(rrsigs); // test without RRSIGs (empty vector)

    this->addRdataMultiCommon(rrsigs, true); // ditto, but with duplicated data

    // Tests with two RRSIGs
    rrsigs.push_back(this->rrsig_rdata_);
    rrsigs.push_back(createRdata(RRType::RRSIG(), RRClass::IN(),
                                 "A 5 2 3600 20120814220826 "
                                 "20120715220826 54321 com. FAKE"));
    this->addRdataMultiCommon(rrsigs);

    // Similar to the previous, but with duplicate RRSIG.
    rrsigs.push_back(this->rrsig_rdata_);
    this->addRdataMultiCommon(rrsigs, true);
}

TEST_F(RdataSerializationTest, badAddRdata) {
    // Some operations must follow start().
    EXPECT_THROW(encoder_.addRdata(*a_rdata_), isc::InvalidOperation);
    EXPECT_THROW(encoder_.getStorageLength(), isc::InvalidOperation);
    // will allocate space of some arbitrary size (256 bytes)
    EXPECT_THROW(encodeWrapper(256), isc::InvalidOperation);

    // Bad buffer for encode
    encoder_.start(RRClass::IN(), RRType::A());
    encoder_.addRdata(*a_rdata_);
    const size_t buf_len = encoder_.getStorageLength();
    // NULL buffer for encode
    EXPECT_THROW(encoder_.encode(NULL, buf_len), isc::BadValue);
    // buffer length is too short (we don't use the wrraper because we don't
    // like to tweak the length arg to encode()).
    encoded_data_.resize(buf_len - 1);
    EXPECT_THROW(encoder_.encode(&encoded_data_[0], buf_len - 1),
                 isc::BadValue);

    // Some of the following checks confirm that adding an Rdata of the
    // wrong RR type will be rejected.  Several different cases are checked,
    // but there shouldn't be any essential difference among these cases in
    // the tested code; these cases were considered because in an older version
    // of implementation rejected them for possibly different reasons, and
    // we simply keep these cases as they are not so many (and may help detect
    // future possible regression).
    encoder_.start(RRClass::IN(), RRType::AAAA());
    EXPECT_THROW(encoder_.addRdata(*a_rdata_), std::bad_cast);

    encoder_.start(RRClass::IN(), RRType::A());
    EXPECT_THROW(encoder_.addRdata(*aaaa_rdata_), std::bad_cast);

    const ConstRdataPtr rp_rdata =
        createRdata(RRType::RP(), RRClass::IN(), "a.example. b.example");
    encoder_.start(RRClass::IN(), RRType::NS());
    EXPECT_THROW(encoder_.addRdata(*rp_rdata), std::bad_cast);

    encoder_.start(RRClass::IN(), RRType::DHCID());
    EXPECT_THROW(encoder_.addRdata(*rp_rdata), std::bad_cast);

    const ConstRdataPtr txt_rdata = createRdata(RRType::TXT(), RRClass::IN(),
                                                "a");
    encoder_.start(RRClass::IN(), RRType::MX());
    EXPECT_THROW(encoder_.addRdata(*txt_rdata), std::bad_cast);

    encoder_.start(RRClass::IN(), RRType::NS());
    EXPECT_THROW(encoder_.addRdata(*txt_rdata), std::bad_cast);

    const ConstRdataPtr ns_rdata =
        createRdata(RRType::NS(), RRClass::IN(), "ns.example.");
    encoder_.start(RRClass::IN(), RRType::DNAME());
    EXPECT_THROW(encoder_.addRdata(*ns_rdata), std::bad_cast);

    const ConstRdataPtr dname_rdata =
        createRdata(RRType::DNAME(), RRClass::IN(), "dname.example.");
    encoder_.start(RRClass::IN(), RRType::NS());
    EXPECT_THROW(encoder_.addRdata(*dname_rdata), std::bad_cast);

    // RDATA len exceeds the 16-bit range.  Technically not invalid, but
    // we don't support that (and it's practically useless anyway).
    encoded_data_.resize(65536); // use encoded_data_ for placeholder
    isc::util::InputBuffer buffer(&encoded_data_[0], encoded_data_.size());
    encoder_.start(RRClass::IN(), RRType::DHCID());
    EXPECT_THROW(encoder_.addRdata(in::DHCID(buffer, encoded_data_.size())),
                                   RdataEncodingError);

    // RRSIG cannot be used as the main RDATA type (can only be added as
    // a signature for some other type of RDATAs).
    EXPECT_THROW(encoder_.start(RRClass::IN(), RRType::RRSIG()),
                 isc::BadValue);
}

struct MergeTestData {
    const char* const type_txt; // "AAAA", "NS", etc
    const char* const rdata_txt1; // RDATA possibly used for old data
    const char* const rdata_txt2; // RDATA possibly used for new data
    const char* const rdata_txt3; // optional data to check with multi-RDATAs
    const size_t varlen_fields; // number of variable-len fields in RDATA
} merge_test_data[] = {
    // For test with fixed-length RDATA
    {"A", "192.0.2.53", "192.0.2.54", "192.0.2.55", 0},
    // For test with variable-length RDATA
    {"TXT", "foo bar baz", "another text data", "yet another", 1},
    // For test with RDATA containing domain name
    {"MX", "5 mx1.example.com.", "10 mx2.example.com.", "20 mx.example.", 0},
    {NULL, NULL, NULL, NULL, 0}
};

// Identifier for slightly difference modes of "merge data" test below.
// We test various combinations on # of old (before merge) and new (being
// merged) RDATAs.
enum MergeTestMode {
    ONE_OLD_ONE_NEW = 0,
    MULTI_OLD_NO_NEW,
    ONE_OLD_MULTI_NEW,
    DUPLICATE_NEW,      // The new RDATA is a duplicate of the old one
    NO_OLD_ONE_NEW,     // no old RDATA; this can also cover the case where
                        // the resulting RdataSet is RRSIG-only.
    ONE_OLD_NO_NEW
};

// A helper to build vectors of Rata's for the given test mode.
void
createMergeData(int mode, const MergeTestData& data,
                const RRClass& rrclass, const RRType& rrtype,
                vector<ConstRdataPtr>& old_list,
                vector<ConstRdataPtr>& new_list)
{
    old_list.clear();
    new_list.clear();
    old_list.push_back(createRdata(rrtype, rrclass, data.rdata_txt1));
    new_list.push_back(createRdata(rrtype, rrclass, data.rdata_txt2));
    switch (static_cast<MergeTestMode>(mode)) {
    case ONE_OLD_ONE_NEW:
        break;
    case MULTI_OLD_NO_NEW:
        old_list.push_back(createRdata(rrtype, rrclass, data.rdata_txt3));
        break;
    case ONE_OLD_MULTI_NEW:
        new_list.push_back(createRdata(rrtype, rrclass, data.rdata_txt3));
        break;
    case DUPLICATE_NEW:
        new_list.push_back(createRdata(rrtype, rrclass, data.rdata_txt1));
        break;
    case NO_OLD_ONE_NEW:
        old_list.clear();
        break;
    case ONE_OLD_NO_NEW:
        new_list.clear();
        break;
    }
}

template<class DecoderStyle>
void
RdataEncodeDecodeTest<DecoderStyle>::
mergeRdataCommon(const vector<ConstRdataPtr>& old_rrsigs,
                 const vector<ConstRdataPtr>& rrsigs)
{
    const RRClass rrclass(RRClass::IN()); // class is fixed in the test
    vector<uint8_t> old_encoded_data;
    vector<ConstRdataPtr> rrsigs_all;
    vector<ConstRdataPtr> old_list;
    vector<ConstRdataPtr> new_list;

    // For each type of test Rdata, we check all modes of test scenarios.
    for (const MergeTestData* data = merge_test_data;
         data->type_txt;
         ++data) {
        const RRType rrtype(data->type_txt);

        for (int mode = 0; mode <= ONE_OLD_NO_NEW; ++mode) {
            createMergeData(mode, *data, rrclass, rrtype, old_list, new_list);

            // Encode the old data
            rdata_list_ = old_list;
            checkEncode(rrclass, RRType(data->type_txt), rdata_list_,
                        data->varlen_fields, old_rrsigs);
            old_encoded_data = encoded_data_; // make a copy of the data

            // Prepare new data.  rrsigs_all is set to "old_rrsigs + rrsigs".
            // Then check the behavior in the "merge" mode.
            const size_t old_rdata_count = rdata_list_.size();
            rdata_list_.insert(rdata_list_.end(), new_list.begin(),
                               new_list.end());
            rrsigs_all = old_rrsigs;
            rrsigs_all.insert(rrsigs_all.end(), rrsigs.begin(), rrsigs.end());
            checkEncode(rrclass, rrtype, rdata_list_, data->varlen_fields,
                        rrsigs_all, &old_encoded_data[0], old_rdata_count,
                        old_rrsigs.size());
        }
    }
}

TYPED_TEST(RdataEncodeDecodeTest, mergeRdata) {
    vector<ConstRdataPtr> old_rrsigs;
    vector<ConstRdataPtr> rrsigs;

    // Test without RRSIGs, either for old or new.
    this->mergeRdataCommon(old_rrsigs, rrsigs);

    // Test without RRSIG for old and with RRSIG for new.
    rrsigs.push_back(this->rrsig_rdata_);
    this->mergeRdataCommon(old_rrsigs, rrsigs);

    // Test with RRSIG for old and without RRSIG for new.
    rrsigs.clear();
    old_rrsigs.push_back(this->rrsig_rdata_);
    this->mergeRdataCommon(old_rrsigs, rrsigs);

    // Tests with RRSIGs for both old and new.
    old_rrsigs.clear();
    rrsigs.push_back(createRdata(RRType::RRSIG(), RRClass::IN(),
                                 "A 5 2 3600 20120814220826 "
                                 "20120715220826 54321 com. FAKE"));
    this->mergeRdataCommon(old_rrsigs, rrsigs);

    // Tests with multiple old RRSIGs.
    rrsigs.clear();
    old_rrsigs.clear();
    old_rrsigs.push_back(this->rrsig_rdata_);
    old_rrsigs.push_back(createRdata(RRType::RRSIG(), RRClass::IN(),
                                     "A 5 2 3600 20120814220826 "
                                     "20120715220826 54321 com. FAKE"));
    this->mergeRdataCommon(old_rrsigs, rrsigs);

    // Tests with duplicate RRSIG in new one (keeping the old_rrsigs)
    rrsigs.push_back(this->rrsig_rdata_);
    this->mergeRdataCommon(old_rrsigs, rrsigs);
}

TEST_F(RdataSerializationTest, mergeRdataFromDuplicate) {
    // create encoded data containing duplicate Rdata and try to start a
    // new encoding session in the merge mode with that data.  It breaks the
    // assumption and should result in an exception.
    const uint8_t data[] = { 192, 0, 2, 1, 192, 0, 2, 1 };
    EXPECT_THROW(encoder_.start(RRClass::IN(), RRType::A(), data, 2, 0),
                 isc::Unexpected);

    // Same for duplicate RRSIG
    isc::util::OutputBuffer buffer(0);
    vector<uint8_t> sigdata;
    rrsig_rdata_->toWire(buffer);
    const uint16_t sig_len = buffer.getLength();
    // Encode lengths of RRSIGs, 2 bytes each, in host byte order
    const uint8_t* const lp = static_cast<const uint8_t*>(
        static_cast<const void*>(&sig_len));
    sigdata.insert(sigdata.end(), lp, lp + sizeof(sig_len));
    sigdata.insert(sigdata.end(), lp, lp + sizeof(sig_len));
    // then the RRSIG data
    const uint8_t* const dp = static_cast<const uint8_t*>(buffer.getData());
    sigdata.insert(sigdata.end(), dp, dp + sig_len);
    sigdata.insert(sigdata.end(), dp, dp + sig_len);

    EXPECT_THROW(encoder_.start(RRClass::IN(), RRType::A(), &sigdata[0], 0, 2),
                 isc::Unexpected);
}

void
checkSigData(const ConstRdataPtr& decoded, bool* called, const void* encoded,
             size_t length)
{
    EXPECT_FALSE(*called); // Called exactly once
    *called = true;

    // Reconstruct the RRSig and check it.
    isc::util::InputBuffer ib(encoded, length);
    const generic::RRSIG reconstructed(ib, ib.getLength());
    EXPECT_EQ(0, reconstructed.compare(*decoded));
}

TEST_F(RdataSerializationTest, addSIGRdataOnly) {
    // Encoded data that only contain RRSIGs.  Mostly useless, but can happen
    // (in a partially broken zone) and it's accepted.
    encoder_.start(RRClass::IN(), RRType::A());
    encoder_.addSIGRdata(*rrsig_rdata_);
    encodeWrapper(encoder_.getStorageLength());
    ASSERT_LT(sizeof(uint16_t), encoder_.getStorageLength());

    bool called = false;
    RdataReader reader(RRClass::IN(), RRType::A(), &encoded_data_[0], 0, 1,
                       ignoreName, boost::bind(checkSigData, rrsig_rdata_,
                                               &called, _1, _2));
    reader.iterate();
    EXPECT_FALSE(called);
    reader.iterateAllSigs();
    EXPECT_TRUE(called);
}

TEST_F(RdataSerializationTest, badAddSIGRdata) {
    // try adding SIG before start
    EXPECT_THROW(encoder_.addSIGRdata(*rrsig_rdata_), isc::InvalidOperation);

    // Very big RRSIG.  This implementation rejects it.
    isc::util::OutputBuffer ob(0);
    rrsig_rdata_->toWire(ob);
    // append dummy trailing signature to make it too big
    vector<uint8_t> dummy_sig(65536 - ob.getLength());
    ob.writeData(&dummy_sig[0], dummy_sig.size());
    ASSERT_EQ(65536, ob.getLength());

    isc::util::InputBuffer ib(ob.getData(), ob.getLength());
    const generic::RRSIG big_sigrdata(ib, ob.getLength());
    encoder_.start(RRClass::IN(), RRType::A());
    EXPECT_THROW(encoder_.addSIGRdata(big_sigrdata), RdataEncodingError);
}
}
