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
#include <dns/rdataclass.h>     // for a test function
#include <dns/rrclass.h>
#include <dns/rrtype.h>

#include <util/buffer.h>        // for test functions

#include "rdata_encoder.h"

#include <boost/static_assert.hpp>

#include <cassert>
#include <utility>
#include <vector>

#include <stdint.h>

using namespace isc::dns;
using std::pair;
using std::vector;

namespace isc {
namespace datasrc {
namespace memory {

namespace {
/// Specification of a single RDATA field in terms of internal encoding.
struct RdataFieldSpec {
    enum FieldType {
        FIXEDLEN_DATA = 0,      // fixed-length data field
        VARLEN_DATA,            // variable-length data field
        DOMAIN_NAME             // domain name
    };

    const FieldType type;       // field type

    // type specific data.  We use a union so it'll be clear only one of them
    // (determined by the type) is valid.  Since we want to make it as
    // lightweight as possible, we use a relatively lower-level primitives
    // here.
    union {
        // The length of fixed-length data field.  Only valid for FIXEDLEN_DATA
        const uint16_t fixeddata_len;

        // Attributes of the name.  Only valid for DOMAIN_NAME.
        const RdataNameAttributes name_attributes;
    };
};

/// Specification of RDATA in terms of internal encoding.
struct RdataEncodeSpec {
    const uint16_t field_count; // total number of fields (# of fields member)
    const uint16_t name_count;  // number of domain name fields
    const uint16_t varlen_count; // number of variable-length data fields
    const RdataFieldSpec* const fields; // list of field specs
};

// These constants are convenient shortcut to initialize the name_attributes
// member of RdataFieldSpec (since it's a union, we can only directly
// initialize fixeddata_len member, so we need to convert it to its type).
// These are essentially small integers, so the cast should be safe.
const uint16_t NAMEATTR_NOATTRIBUTE_INITIALIZER = static_cast<uint16_t>(0);
const uint16_t NAMEATTR_COMPRESSIBLE_INITIALIZER =
    static_cast<uint16_t>(NAMEATTR_COMPRESSIBLE);
const uint16_t NAMEATTR_ADDITIONAL_INITIALIZER =
    static_cast<uint16_t>(NAMEATTR_ADDITIONAL);
const uint16_t NAMEATTR_COMPADDITIONAL_INITIALIZER =
    static_cast<uint16_t>(NAMEATTR_COMPRESSIBLE | NAMEATTR_ADDITIONAL);

// Many types of RDATA can be treated as a single-field, variable length
// field (in terms of our encoding).  The following define such most general
// form of field spec.
const RdataFieldSpec generic_data_fields[] = {
    {RdataFieldSpec::VARLEN_DATA, {0}}
};
const uint16_t n_generic_data_fields =
    sizeof(generic_data_fields) / sizeof(RdataFieldSpec);
const RdataEncodeSpec generic_data_spec = {
    n_generic_data_fields, 0, 1, generic_data_fields
};

// RDATA consist of a single IPv4 address field.
const RdataFieldSpec single_ipv4_fields[] = {
    {RdataFieldSpec::FIXEDLEN_DATA, {sizeof(uint32_t)}}
};
const uint16_t n_ipv4_fields =
    sizeof(single_ipv4_fields) / sizeof(RdataFieldSpec);

// RDATA consist of a single IPv6 address field.
const RdataFieldSpec single_ipv6_fields[] = {
    {RdataFieldSpec::FIXEDLEN_DATA, {16}} // 128bits = 16 bytes
};
const uint16_t n_ipv6_fields =
    sizeof(single_ipv6_fields) / sizeof(RdataFieldSpec);

// There are several RR types that consist of a single domain name.
const RdataFieldSpec single_noattr_name_fields[] = {
    {RdataFieldSpec::DOMAIN_NAME, {NAMEATTR_NOATTRIBUTE_INITIALIZER}}
};
const RdataFieldSpec single_compressible_name_fields[] = {
    {RdataFieldSpec::DOMAIN_NAME, {NAMEATTR_COMPRESSIBLE_INITIALIZER}}
};
const RdataFieldSpec single_compadditional_name_fields[] = {
    {RdataFieldSpec::DOMAIN_NAME,
     {NAMEATTR_COMPRESSIBLE_INITIALIZER|NAMEATTR_COMPADDITIONAL_INITIALIZER}}
};
const uint16_t n_single_name_fields =
    sizeof(single_noattr_name_fields) / sizeof(RdataFieldSpec);

// RDATA consisting of two names.  There are some of this type.
const RdataFieldSpec double_compressible_name_fields[] = {
    {RdataFieldSpec::DOMAIN_NAME, {NAMEATTR_COMPRESSIBLE_INITIALIZER}},
    {RdataFieldSpec::DOMAIN_NAME, {NAMEATTR_COMPRESSIBLE_INITIALIZER}}
};
const RdataFieldSpec double_noattr_name_fields[] = {
    {RdataFieldSpec::DOMAIN_NAME, {NAMEATTR_NOATTRIBUTE_INITIALIZER}},
    {RdataFieldSpec::DOMAIN_NAME, {NAMEATTR_NOATTRIBUTE_INITIALIZER}}
};
const uint16_t n_double_name_fields =
    sizeof(double_compressible_name_fields) / sizeof(RdataFieldSpec);

// SOA specific: two compressible names + 5*32-bit data
const RdataFieldSpec soa_fields[] = {
    {RdataFieldSpec::DOMAIN_NAME, {NAMEATTR_COMPRESSIBLE_INITIALIZER}},
    {RdataFieldSpec::DOMAIN_NAME, {NAMEATTR_COMPRESSIBLE_INITIALIZER}},
    {RdataFieldSpec::FIXEDLEN_DATA, {sizeof(uint32_t) * 5}}
};
const uint16_t n_soa_fields = sizeof(soa_fields) / sizeof(RdataFieldSpec);

// MX specific: 16-bit data + compressible/additional name
const RdataFieldSpec mx_fields[] = {
    {RdataFieldSpec::FIXEDLEN_DATA, {sizeof(uint16_t)}},
    {RdataFieldSpec::DOMAIN_NAME, {NAMEATTR_COMPADDITIONAL_INITIALIZER}}
};
const uint16_t n_mx_fields = sizeof(mx_fields) / sizeof(RdataFieldSpec);

// AFSDB specific: 16-bit data + no-attribute name
const RdataFieldSpec afsdb_fields[] = {
    {RdataFieldSpec::FIXEDLEN_DATA, {sizeof(uint16_t)}},
    {RdataFieldSpec::DOMAIN_NAME, {NAMEATTR_NOATTRIBUTE_INITIALIZER}}
};
const uint16_t n_afsdb_fields = sizeof(afsdb_fields) / sizeof(RdataFieldSpec);

// SRV specific: 3*16-bit data + additional name
const RdataFieldSpec srv_fields[] = {
    {RdataFieldSpec::FIXEDLEN_DATA, {sizeof(uint16_t) * 3}},
    {RdataFieldSpec::DOMAIN_NAME, {NAMEATTR_ADDITIONAL_INITIALIZER}}
};
const uint16_t n_srv_fields = sizeof(srv_fields) / sizeof(RdataFieldSpec);

// NAPTR specific: (multi-field) variable data + (additional) name
// NAPTR requires complicated additional section handling; for now, we skip
// the additional handling completely.
const RdataFieldSpec naptr_fields[] = {
    {RdataFieldSpec::VARLEN_DATA, {0}},
    {RdataFieldSpec::DOMAIN_NAME, {NAMEATTR_NOATTRIBUTE_INITIALIZER}}
};
const uint16_t n_naptr_fields = sizeof(naptr_fields) / sizeof(RdataFieldSpec);

// NSEC specific: no-attribute name + varlen data
const RdataFieldSpec nsec_fields[] = {
    {RdataFieldSpec::DOMAIN_NAME, {NAMEATTR_NOATTRIBUTE_INITIALIZER}},
    {RdataFieldSpec::VARLEN_DATA, {0}}
};
const uint16_t n_nsec_fields = sizeof(nsec_fields) / sizeof(RdataFieldSpec);

// Class IN encode specs.  This gives a shortcut to the encode spec for
// some well-known types of RDATA specific to class IN (most of which are
// generic and can be used for other classes).  The array index is the
// RR type code.
const RdataEncodeSpec encode_spec_list_in[] = {
    generic_data_spec,                         // #0: (NONE)
    {n_ipv4_fields, 0, 0, single_ipv4_fields},   // #1: A
    {n_single_name_fields, 1, 0, single_compadditional_name_fields}, // #2: NS
    generic_data_spec,          // #3
    generic_data_spec,          // #4
    {n_single_name_fields, 1, 0, single_compressible_name_fields}, // #5: CNAME
    {n_soa_fields, 2, 0, soa_fields}, // #6: SOA
    generic_data_spec,                // #7
    generic_data_spec,                // #8
    generic_data_spec,                // #9
    generic_data_spec,                // #10
    generic_data_spec,                // #11
    {n_single_name_fields, 1, 0, single_compressible_name_fields}, // #12: PTR
    generic_data_spec,          // #13: HINFO
    {n_double_name_fields, 2, 0, double_compressible_name_fields}, // #14:HINFO
    {n_mx_fields, 1, 0, mx_fields}, // #15: MX
    generic_data_spec, // #16: TXT
    {n_double_name_fields, 2, 0, double_noattr_name_fields}, // 17: RP
    {n_afsdb_fields, 1, 0, afsdb_fields}, // #18: AFSDB
    // #19-#26
    generic_data_spec, generic_data_spec, generic_data_spec, generic_data_spec,
    generic_data_spec, generic_data_spec, generic_data_spec, generic_data_spec,
    generic_data_spec,                // #27
    {n_ipv6_fields, 0, 0, single_ipv6_fields},   // #28: AAAA
    // #29-#32
    generic_data_spec, generic_data_spec, generic_data_spec, generic_data_spec,
    {n_srv_fields, 1, 0, srv_fields},   // #33: SRV
    generic_data_spec,                  // #34
    {n_naptr_fields, 1, 1, naptr_fields}, // #35: NAPTR
    generic_data_spec,                  // #36
    generic_data_spec,                  // #37
    generic_data_spec,                  // #38
    {n_single_name_fields, 1, 0, single_noattr_name_fields}, // #39 DNAME
    generic_data_spec,                  // #40
    generic_data_spec,                  // #41 (OPT)
    generic_data_spec,                  // #42
    generic_data_spec, // #43: DS (this is opaque for encoding purposes)
    generic_data_spec, // #44: SSHFP (this is opaque for encoding purposes)
    generic_data_spec,                  // #45
    generic_data_spec, // #46: RRSIG (this is opaque for encoding purposes)
    {n_nsec_fields, 1, 1, nsec_fields} // #47: NSEC

    // All others can be treated as single-field variable length data, at
    // least for currently supported RR types.
};

// # of entries in encode_spec_list_in
const size_t encode_spec_list_in_size =
    sizeof(encode_spec_list_in) / sizeof(encode_spec_list_in[0]);
BOOST_STATIC_ASSERT(encode_spec_list_in_size == 48);

inline
const RdataEncodeSpec&
getRdataEncodeSpec(RRClass rrclass, RRType rrtype) {
    // Special case: for classes other than IN, we treat RDATA of RR types
    // that are class-IN specific as generic opaque data.
    if (rrclass != RRClass::IN() &&
        (rrtype == RRType::A() || rrtype == RRType::AAAA() ||
         rrtype == RRType::SRV())) {
        return (generic_data_spec);
    }

    // Otherwise, if the type is in the pre-defined range, we use the defined
    // spec; otherwise we treat it as opaque data.
    const uint16_t typecode = rrtype.getCode();
    if (typecode < encode_spec_list_in_size) {
        return (encode_spec_list_in[rrtype.getCode()]);
    }
    return (generic_data_spec);
}

// This class is used to divide the content of RDATA into \c RdataField
// fields via message rendering logic.
// The idea is to identify domain name fields in the writeName() method,
// and determine whether they are compressible using the "compress"
// parameter.
// Other types of data are simply copied into the internal buffer, and
// consecutive such fields are combined into a single \c RdataField field.
//
// Technically, this use of inheritance may be considered a violation of
// Liskov Substitution Principle in that it doesn't actually compress domain
// names, and some of the methods are not expected to be used.
// In fact, skip() or trim() may not be make much sense in this context.
// Nevertheless we keep this idea at the moment.  Since the usage is limited
// (it's only used within this file, and only used with \c Rdata variants),
// it's hopefully an acceptable practice.
class RdataFieldComposer : public AbstractMessageRenderer {
public:
    RdataFieldComposer() : last_data_pos_(0), encode_spec_(NULL),
                           current_field_(0)
    {}
    virtual ~RdataFieldComposer() {}
    virtual bool isTruncated() const { return (false); }
    virtual size_t getLengthLimit() const { return (65535); }
    virtual CompressMode getCompressMode() const { return (CASE_INSENSITIVE); }
    virtual void setTruncated() {}
    virtual void setLengthLimit(size_t) {}
    virtual void setCompressMode(CompressMode) {}
    virtual void writeName(const Name& name, bool /*compress*/) {
        assert(current_field_ < encode_spec_->field_count); // TBD

        extendData();

        const RdataFieldSpec& field =
            encode_spec_->fields[current_field_++];
        assert(field.type == RdataFieldSpec::DOMAIN_NAME); // TBD

        const LabelSequence labels(name);
        labels.serialize(labels_placeholder_, sizeof(labels_placeholder_));
        writeData(labels_placeholder_, labels.getSerializedLength());
        names_.push_back(pair<size_t, Name>(0, name));

        last_data_pos_ += labels.getSerializedLength();
    }
    void clearLocal(const RdataEncodeSpec* encode_spec) {
        AbstractMessageRenderer::clear();
        encode_spec_ = encode_spec;
        data_positions_.clear();
        names_.clear();
        data_lengths_.clear();
        last_data_pos_ = 0;
    }
    void startRdata() {
        current_field_ = 0;
    }
    void endRdata() {
        if (current_field_ < encode_spec_->field_count) {
            extendData();
        }
        assert(current_field_ == encode_spec_->field_count); // TBD
    }
    vector<pair<size_t, size_t> > data_positions_;
    vector<pair<size_t, Name> > names_;
    vector<uint16_t> data_lengths_;

private:
    // We use generict write* methods, with the exception of writeName.
    // So new data can arrive without us knowing it, this considers all new
    // data to be just data and extends the fields to take it into account.
    size_t last_data_pos_;
    void extendData() {
        assert(current_field_ < encode_spec_->field_count); // must be true

        const size_t cur_pos = getLength();
        size_t data_len = cur_pos - last_data_pos_;
        while (current_field_ < encode_spec_->field_count) {
            const RdataFieldSpec& field = encode_spec_->fields[current_field_];
            if (field.type == RdataFieldSpec::DOMAIN_NAME) {
                return;
            }
            ++current_field_;
            if (field.type == RdataFieldSpec::FIXEDLEN_DATA) {
                // TBD: validation
                data_len -= field.fixeddata_len;
                continue;
            }
            // We are looking at a variable-length data field.
            // TBD: 16bit len check
            data_lengths_.push_back(data_len);
            data_len = 0;
            break;
        }
        // TBD: data_len must be 0;
        assert(data_len == 0);

        // We added this much data from last time
        data_positions_.push_back(
            pair<size_t, size_t>(last_data_pos_, cur_pos - last_data_pos_));
        last_data_pos_ = cur_pos;
    }

    const RdataEncodeSpec* encode_spec_;
    size_t current_field_;
    uint8_t labels_placeholder_[LabelSequence::MAX_SERIALIZED_LENGTH];
};
} // end of unnamed namespace

struct RdataEncoder::RdataEncoderImpl {
    RdataEncoderImpl() : encode_spec_(NULL), rdata_count_(0)
    {}

    const RdataEncodeSpec* encode_spec_; // encode spec of current RDATA set
    RdataFieldComposer field_composer_;
    size_t rdata_count_;
};

RdataEncoder::RdataEncoder() :
    impl_(new RdataEncoderImpl)
{}

RdataEncoder::~RdataEncoder() {
    delete impl_;
}

void
RdataEncoder::start(RRClass rrclass, RRType rrtype) {
    impl_->encode_spec_ = &getRdataEncodeSpec(rrclass, rrtype);
    impl_->field_composer_.clearLocal(impl_->encode_spec_);
    impl_->rdata_count_ = 0;
}

void
RdataEncoder::addRdata(const rdata::Rdata& rdata) {
    impl_->field_composer_.startRdata();
    rdata.toWire(impl_->field_composer_);
    impl_->field_composer_.endRdata();
    ++impl_->rdata_count_;
}

size_t
RdataEncoder::getStorageLength() const {
    return (sizeof(uint16_t) * impl_->field_composer_.data_lengths_.size() +
            impl_->field_composer_.getLength());
}

void
RdataEncoder::encode(void* buf, size_t buf_len) const {
    // validation

    const uint8_t* const dp_beg = reinterpret_cast<uint8_t*>(buf);
    uint8_t* dp = reinterpret_cast<uint8_t*>(buf);
    if (!impl_->field_composer_.data_lengths_.empty()) {
        const size_t varlen_fields_len =
            impl_->field_composer_.data_lengths_.size() * sizeof(uint16_t);
        uint16_t* lenp = reinterpret_cast<uint16_t*>(buf);
        memcpy(lenp, &impl_->field_composer_.data_lengths_[0],
               varlen_fields_len);
        dp += varlen_fields_len;
    }
    memcpy(dp, impl_->field_composer_.getData(),
           impl_->field_composer_.getLength());
    dp += impl_->field_composer_.getLength();

    assert(buf_len >= dp - dp_beg);
}

namespace testing {
void
foreachRdataField(RRClass rrclass, RRType rrtype,
                  size_t rdata_count,
                  const vector<uint8_t>& encoded_data,
                  const vector<uint16_t>& varlen_list,
                  NameCallback name_callback, DataCallback data_callback)
{
    const RdataEncodeSpec& encode_spec = getRdataEncodeSpec(rrclass, rrtype);

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
                    name_callback(labels, field_spec.name_attributes);
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
} // namespace testing

} // namespace memory
} // namespace datasrc
} // datasrc isc
