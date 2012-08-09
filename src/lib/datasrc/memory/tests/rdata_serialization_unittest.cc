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

// Note: This file tests both the rdata_encoder and rdata_reader. They are
// tested together because they form kind the oposite sides of the same
// functionality.

#include <exceptions/exceptions.h>

#include <util/buffer.h>

#include <dns/name.h>
#include <dns/labelsequence.h>
#include <dns/messagerenderer.h>
#include <dns/rdata.h>
#include <dns/rdataclass.h>
#include <dns/rrclass.h>
#include <dns/rrtype.h>

#include <datasrc/memory/rdata_encoder.h>
#include <datasrc/memory/rdata_field.h>
#include <datasrc/memory/rdata_reader.h>

#include <util/unittests/wiredata.h>

#include <gtest/gtest.h>

#include <boost/bind.hpp>
#include <boost/foreach.hpp>

#include <cstring>
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
    {"CH", "NS", "ns.example.com", 0}, // class CH, generic data
    {"CH", "TXT", "BIND10", 1},        // ditto
    {"HS", "A", "\\# 5 0102030405", 1}, // A RR for non-IN class; varlen data
    {NULL, NULL, NULL, 0}
};

// The following two functions will be used to generate wire format data
// from encoded representation of each RDATA.
void
renderNameField(MessageRenderer* renderer, bool additional_required,
                const LabelSequence& labels, unsigned attributes)
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

    // A wraper for RdataEncoder::encode() with buffer overrun check.
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
    // This helper test method constructs encodes the given list of RDATAs
    // (in rdata_list), and then iterates over the data, rendering the fields
    // in the wire format.  It then compares the wire data with the one
    // generated by the normal libdns++ interface to see the encoding/decoding
    // works as intended.
    void checkEncode(RRClass rrclass, RRType rrtype,
                     const vector<ConstRdataPtr>& rdata_list,
                     size_t expected_varlen_fields,
                     const vector<ConstRdataPtr>& rrsig_list);

    void addRdataCommon(const vector<ConstRdataPtr>& rrsigs);
    void addRdataMultiCommon(const vector<ConstRdataPtr>& rrsigs);
};

// Used across more classes and scopes. But it's just uninteresting
// constant.
const Name dummy_name2("example.com");

bool
additionalRequired(const RRType& type) {
    // The set of RR types that require additional section processing.
    // We'll pass it to renderNameField to check the stored attribute matches
    // our expectation.
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
                       // Warning: this test actualy might change the
                       // encoded_data !
                       vector<uint8_t>& encoded_data,
                       MessageRenderer& renderer)
    {
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

        // If RRSIGs are given, we need to extract the list of the RRSIG lengths
        // and adjust encoded_data_ further.
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
    renderer.writeName(dummy_name2);
    // Finally, dump any RRSIGs in wire format.
    foreachRRSig(encoded_data, rrsiglen_list,
                 boost::bind(renderDataField, &renderer, _1, _2));
    }
};

// Decode using reader with the return value of next
class NextDecoder {
public:
    static void decode(const isc::dns::RRClass& rrclass,
                       const isc::dns::RRType& rrtype,
                       size_t, size_t, size_t,
                       const vector<uint8_t>& encoded_data,
                       MessageRenderer& renderer)
    {
        RdataReader reader(rrclass, rrtype, encoded_data.size(),
                           &encoded_data[0]);
        RdataReader::Result field;
        while (field = reader.next()) {
            switch (field.type()) {
                case RdataReader::DATA:
                    renderer.writeData(field.data(), field.size());
                    break;
                case RdataReader::NAME:
                    renderer.writeName(field.label(), field.compressible());
                    break;
                default:
                    FAIL();
            }
        }

        renderer.writeName(dummy_name2);

        while (field = reader.nextSig()) {
            switch (field.type()) {
                case RdataReader::DATA:
                    renderer.writeData(field.data(), field.size());
                    break;
                default: // There are also no NAME fields in RRSigs
                    FAIL();
            }
        }
    }
};

// Check using callbacks and calling next until the end.
class CallbackDecoder {
public:
    static void decode(const isc::dns::RRClass& rrclass,
                       const isc::dns::RRType& rrtype,
                       size_t, size_t, size_t,
                       const vector<uint8_t>& encoded_data,
                       MessageRenderer& renderer)
    {
        RdataReader reader(rrclass, rrtype, encoded_data.size(),
                           &encoded_data[0],
                           boost::bind(renderNameField, &renderer,
                                       additionalRequired(rrtype), _1, _2),
                           boost::bind(renderDataField, &renderer, _1, _2));
        while (reader.next()) { }
        renderer.writeName(dummy_name2);
        while (reader.nextSig()) { }
    }
};

// Check using callbacks and calling iterate.
class IterateDecoder {
public:
    static void decode(const isc::dns::RRClass& rrclass,
                       const isc::dns::RRType& rrtype,
                       size_t, size_t, size_t,
                       const vector<uint8_t>& encoded_data,
                       MessageRenderer& renderer)
    {
        RdataReader reader(rrclass, rrtype, encoded_data.size(),
                           &encoded_data[0],
                           boost::bind(renderNameField, &renderer,
                                       additionalRequired(rrtype), _1, _2),
                           boost::bind(renderDataField, &renderer, _1, _2));
        reader.iterate();
        renderer.writeName(dummy_name2);
        reader.iterateSig();
    }
};

typedef ::testing::Types<ManualDecoderStyle, NextDecoder, CallbackDecoder,
                         IterateDecoder> DecoderStyles;
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

template<class DecoderStyle>
void
RdataEncodeDecodeTest<DecoderStyle>::
checkEncode(RRClass rrclass, RRType rrtype,
            const vector<ConstRdataPtr>& rdata_list,
            size_t expected_varlen_fields,
            const vector<ConstRdataPtr>& rrsig_list = vector<ConstRdataPtr>())
{
    // These two names will be rendered before and after the test RDATA,
    // to check in case the RDATA contain a domain name whether it's
    // compressed or not correctly.  The names in the RDATA should basically
    // a subdomain of example.com, so it can be compressed due to dummy_name.
    // Likewise, dummy_name2 should be able to be fully compressed due to
    // the name in the RDATA.
    const Name dummy_name("com");

    expected_renderer_.clear();
    actual_renderer_.clear();
    encoded_data_.clear();

    // Build expected wire-format data
    expected_renderer_.writeName(dummy_name);
    BOOST_FOREACH(const ConstRdataPtr& rdata, rdata_list) {
        rdata->toWire(expected_renderer_);
    }
    expected_renderer_.writeName(dummy_name2);
    BOOST_FOREACH(const ConstRdataPtr& rdata, rrsig_list) {
        rdata->toWire(expected_renderer_);
    }

    // Then build wire format data using the encoded data.
    // 1st dummy name
    actual_renderer_.writeName(dummy_name);

    // Create encoded data
    encoder_.start(rrclass, rrtype);
    BOOST_FOREACH(const ConstRdataPtr& rdata, rdata_list) {
        encoder_.addRdata(*rdata);
    }
    BOOST_FOREACH(const ConstRdataPtr& rdata, rrsig_list) {
        encoder_.addSIGRdata(*rdata);
    }
    encodeWrapper(encoder_.getStorageLength());

    DecoderStyle::decode(rrclass, rrtype, rdata_list.size(), rrsig_list.size(),
                         expected_varlen_fields, encoded_data_,
                         actual_renderer_);

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
    this->addRdataCommon(rrsigs);     // basic tests without RRSIGs (empty vector)

    // Test with RRSIGs (covered type doesn't always match, but the encoder
    // doesn't check that)
    rrsigs.push_back(this->rrsig_rdata_);
    this->addRdataCommon(rrsigs);
}

template<class DecoderStyle>
void
RdataEncodeDecodeTest<DecoderStyle>::
addRdataMultiCommon(const vector<ConstRdataPtr>& rrsigs) {
    // Similar to addRdata(), but test with multiple RDATAs.
    // Four different cases are tested: a single fixed-len RDATA (A),
    // fixed-len data + domain name (MX), variable-len data only (TXT),
    // variable-len data + domain name (NAPTR).
    ConstRdataPtr a_rdata2 = createRdata(RRType::A(), RRClass::IN(),
                                         "192.0.2.54");
    rdata_list_.clear();
    rdata_list_.push_back(a_rdata_);
    rdata_list_.push_back(a_rdata2);
    checkEncode(RRClass::IN(), RRType::A(), rdata_list_, 0, rrsigs);

    ConstRdataPtr mx_rdata1 = createRdata(RRType::MX(), RRClass::IN(),
                                          "5 mx1.example.com");
    ConstRdataPtr mx_rdata2 = createRdata(RRType::MX(), RRClass::IN(),
                                          "10 mx2.example.com");
    rdata_list_.clear();
    rdata_list_.push_back(mx_rdata1);
    rdata_list_.push_back(mx_rdata2);
    checkEncode(RRClass::IN(), RRType::MX(), rdata_list_, 0, rrsigs);

    ConstRdataPtr txt_rdata1 = createRdata(RRType::TXT(), RRClass::IN(),
                                           "foo bar baz");
    ConstRdataPtr txt_rdata2 = createRdata(RRType::TXT(), RRClass::IN(),
                                          "another text data");
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
    rdata_list_.clear();
    rdata_list_.push_back(naptr_rdata1);
    rdata_list_.push_back(naptr_rdata2);
    checkEncode(RRClass::IN(), RRType::NAPTR(), rdata_list_, 1, rrsigs);
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
    ASSERT_LT(sizeof(uint16_t), encoder_.getStorageLength());
    isc::util::InputBuffer ib(&encoded_data_[2], encoded_data_.size() - 2);
    const in::DHCID encoded_dhcid(ib, ib.getLength());
    EXPECT_EQ(0, encoded_dhcid.compare(large_dhcid));
}

TYPED_TEST(RdataEncodeDecodeTest, addRdataMulti) {
    vector<ConstRdataPtr> rrsigs;
    this->addRdataMultiCommon(rrsigs); // test without RRSIGs (empty vector)

    // Tests with two RRSIGs
    rrsigs.push_back(this->rrsig_rdata_);
    rrsigs.push_back(createRdata(RRType::RRSIG(), RRClass::IN(),
                                 "A 5 2 3600 20120814220826 "
                                 "20120715220826 54321 com. FAKE"));
    this->addRdataMultiCommon(rrsigs);
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

    // Type of RDATA and the specified RR type don't match.  addRdata() should
    // detect this inconsistency.
    encoder_.start(RRClass::IN(), RRType::AAAA());
    EXPECT_THROW(encoder_.addRdata(*a_rdata_), isc::BadValue);

    // Likewise.
    encoder_.start(RRClass::IN(), RRType::A());
    EXPECT_THROW(encoder_.addRdata(*aaaa_rdata_), isc::BadValue);

    // Likewise.  The encoder expects the first name completes the data, and
    // throws on the second due as an unexpected name field.
    const ConstRdataPtr rp_rdata =
        createRdata(RRType::RP(), RRClass::IN(), "a.example. b.example");
    encoder_.start(RRClass::IN(), RRType::NS());
    EXPECT_THROW(encoder_.addRdata(*rp_rdata), isc::BadValue);

    // Likewise.  The encoder considers the name data a variable length data
    // field, and throws on the first name.
    encoder_.start(RRClass::IN(), RRType::DHCID());
    EXPECT_THROW(encoder_.addRdata(*rp_rdata), isc::BadValue);

    // Likewise.  The text RDATA (2 bytes) will be treated as MX preference,
    // and the encoder will still expect to see a domain name.
    const ConstRdataPtr txt_rdata = createRdata(RRType::TXT(), RRClass::IN(),
                                                "a");
    encoder_.start(RRClass::IN(), RRType::MX());
    EXPECT_THROW(encoder_.addRdata(*txt_rdata), isc::BadValue);

    // Similar to the previous one, but in this case there's no data field
    // in the spec.
    encoder_.start(RRClass::IN(), RRType::NS());
    EXPECT_THROW(encoder_.addRdata(*txt_rdata), isc::BadValue);

    // Likewise.  Inconsistent name compression policy.
    const ConstRdataPtr ns_rdata =
        createRdata(RRType::NS(), RRClass::IN(), "ns.example");
    encoder_.start(RRClass::IN(), RRType::DNAME());
    EXPECT_THROW(encoder_.addRdata(*ns_rdata), isc::BadValue);

    // Same as the previous one, opposite inconsistency.
    const ConstRdataPtr dname_rdata =
        createRdata(RRType::DNAME(), RRClass::IN(), "dname.example");
    encoder_.start(RRClass::IN(), RRType::NS());
    EXPECT_THROW(encoder_.addRdata(*dname_rdata), isc::BadValue);

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

TEST_F(RdataSerializationTest, addSIGRdataOnly) {
    // Encoded data that only contain RRSIGs.  Mostly useless, but can happen
    // (in a partially broken zone) and it's accepted.
    encoder_.start(RRClass::IN(), RRType::A());
    encoder_.addSIGRdata(*rrsig_rdata_);
    encodeWrapper(encoder_.getStorageLength());
    ASSERT_LT(sizeof(uint16_t), encoder_.getStorageLength());

    // The encoded data should be identical to the given one.
    isc::util::InputBuffer ib(&encoded_data_[2], encoded_data_.size() - 2);
    const generic::RRSIG encoded_sig(ib, ib.getLength());
    EXPECT_EQ(0, encoded_sig.compare(*rrsig_rdata_));
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

// Test the result returns what it was constructed with.
TEST_F(RdataSerializationTest, readerResult) {
    // Default constructor
    RdataReader::Result empty;
    // Everything should be at the "empty" values, type END
    EXPECT_EQ(RdataReader::END, empty.type());
    EXPECT_EQ(NULL, empty.data());
    EXPECT_EQ(0, empty.size());
    EXPECT_TRUE(empty.label().equals(LabelSequence(Name::ROOT_NAME())));
    EXPECT_FALSE(empty);
    EXPECT_FALSE(empty.compressible());
    EXPECT_FALSE(empty.additional());
    // Constructor from label sequence
    LabelSequence seq(Name("example.org"));
    RdataReader::Result compressible(seq, NAMEATTR_COMPRESSIBLE);
    EXPECT_EQ(RdataReader::NAME, compressible.type());
    EXPECT_EQ(NULL, compressible.data());
    EXPECT_EQ(0, compressible.size());
    EXPECT_TRUE(compressible.label().equals(seq));
    EXPECT_TRUE(compressible);
    EXPECT_TRUE(compressible.compressible());
    EXPECT_FALSE(compressible.additional());
    RdataReader::Result incompressible(seq, NAMEATTR_ADDITIONAL);
    EXPECT_EQ(RdataReader::NAME, incompressible.type());
    EXPECT_EQ(NULL, incompressible.data());
    EXPECT_EQ(0, incompressible.size());
    EXPECT_TRUE(incompressible.label().equals(seq));
    EXPECT_TRUE(incompressible);
    EXPECT_FALSE(incompressible.compressible());
    EXPECT_TRUE(incompressible.additional());
    // Constructor from data
    uint8_t byte;
    RdataReader::Result data(&byte, 1);
    EXPECT_EQ(RdataReader::DATA, data.type());
    EXPECT_EQ(&byte, data.data());
    EXPECT_EQ(1, data.size());
    EXPECT_TRUE(data.label().equals(LabelSequence(Name::ROOT_NAME())));
    EXPECT_TRUE(data);
    EXPECT_FALSE(data.compressible());
    EXPECT_FALSE(data.additional());
}
}
