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
#include <dns/rdata.h>
#include <dns/rrclass.h>
#include <dns/rrtype.h>

#include <util/buffer.h>        // for test functions

#include "rdata_encoder.h"

#include <vector>

#include <stdint.h>

using namespace isc::dns;
using std::vector;

namespace isc {
namespace datasrc {
namespace memory {

namespace {
#ifdef notyet
inline RdataNameAttributes
operator&(RdataNameAttributes a1, RdataNameAttributes a2) {
    return (static_cast<RdataNameAttributes>(
                static_cast<unsigned int>(a1) &
                static_cast<unsigned int>(a2)));
}
#endif
struct RdataFieldSpec {
    enum FieldType {
        FIXEDLEN_DATA = 0,
        VARLEN_DATA,
        DOMAIN_NAME
    };
        
    FieldType type;
    union {
        uint16_t fixeddata_len;
        RdataNameAttributes name_attributes;
    };
};

struct RdataEncodeSpec {
    uint16_t field_count;
    uint16_t name_count;
    uint16_t varlen_count;
    const RdataFieldSpec* fields;
};

const uint16_t NAMEATTR_NOATTRIBUTE_INITIALIZER = static_cast<uint16_t>(0);
const uint16_t NAMEATTR_COMPRESSIBLE_INITIALIZER =
    static_cast<uint16_t>(NAMEATTR_COMPRESSIBLE);
const uint16_t NAMEATTR_ADDITIONAL_INITIALIZER =
    static_cast<uint16_t>(NAMEATTR_ADDITIONAL);
const uint16_t NAMEATTR_COMPADDITIONAL_INITIALIZER =
    static_cast<uint16_t>(NAMEATTR_COMPRESSIBLE | NAMEATTR_ADDITIONAL);

// TBD
const RdataFieldSpec generic_data_fields[] = {
    {RdataFieldSpec::VARLEN_DATA, {0}}
};
const uint16_t generic_data_fields_count =
    sizeof(generic_data_fields) / sizeof(RdataFieldSpec);

// TBD
const RdataFieldSpec single_ipv4_fields[] = {
    {RdataFieldSpec::FIXEDLEN_DATA, {sizeof(uint32_t)}}
};
const uint16_t single_ipv4_fields_count =
    sizeof(single_ipv4_fields) / sizeof(RdataFieldSpec);

// TBD
const RdataFieldSpec generic_single_name_fields[] = {
    {RdataFieldSpec::DOMAIN_NAME, {NAMEATTR_COMPADDITIONAL_INITIALIZER}}
};
const uint16_t generic_single_name_fields_count =
    sizeof(generic_single_name_fields) / sizeof(RdataFieldSpec);

// Class IN encode specs
const RdataEncodeSpec encode_spec_list_in[] = {
    {generic_data_fields_count, 0, 0, generic_data_fields}, // #0
    {single_ipv4_fields_count, 0, 0, single_ipv4_fields},   // #1: A
    {generic_single_name_fields_count, 0, 0, generic_single_name_fields} // NS
};

inline
const RdataEncodeSpec&
getRdataEncodeSpec(RRClass rrclass, RRType rrtype) {
    if (rrclass == RRClass::IN()) {
        return (encode_spec_list_in[rrtype.getCode()]);
    }
    return (encode_spec_list_in[0]);
}
} // end of unnamed namespace

void
encodeRdata(const rdata::Rdata& rdata, RRClass rrclass, RRType rrtype,
            vector<uint8_t>& data_result, vector<uint16_t>& /*len_result*/)
{
    util::OutputBuffer buffer(0);
    rdata.toWire(buffer);
    util::InputBuffer ibuffer(buffer.getData(), buffer.getLength());
    vector<uint8_t> tmp;        // used as temporary placeholder below

    const RdataEncodeSpec& encode_spec = getRdataEncodeSpec(rrclass, rrtype);
    for (size_t i = 0; i < encode_spec.field_count; ++i) {
        const RdataFieldSpec& field_spec = encode_spec.fields[i];
        switch (field_spec.type) {
        case RdataFieldSpec::FIXEDLEN_DATA:
            tmp.resize(field_spec.fixeddata_len);
            ibuffer.readData(&tmp[0], tmp.size());
            data_result.insert(data_result.end(), tmp.begin(), tmp.end());
            break;
        case RdataFieldSpec::DOMAIN_NAME:
        {
            const Name name(ibuffer);
            const LabelSequence labels(name);
            size_t nlen;
            const uint8_t* ndata = labels.getData(&nlen);
            size_t olen;
            uint8_t offset_holder[Name::MAX_LABELS];
            labels.getOffsetData(&olen, offset_holder);
            data_result.push_back(nlen);
            data_result.push_back(olen);
            data_result.insert(data_result.end(), ndata, ndata + nlen);
            data_result.insert(data_result.end(), offset_holder,
                               offset_holder + olen);
            break;
        }
        default:
            assert(false);
        }
    }
}

void
foreachRdataField(RRClass rrclass, RRType rrtype,
                  const vector<uint8_t>& encoded_data,
                  const vector<uint16_t>& /*varlen_list*/,
                  NameCallback name_callback, DataCallback data_callback)
{
    const RdataEncodeSpec& encode_spec = getRdataEncodeSpec(rrclass, rrtype);

    size_t off = 0;
    for (size_t i = 0; i < encode_spec.field_count; ++i) {
        const RdataFieldSpec& field_spec = encode_spec.fields[i];
        switch (field_spec.type) {
        case RdataFieldSpec::FIXEDLEN_DATA:
            if (data_callback) {
                data_callback(&encoded_data[off], field_spec.fixeddata_len);
            }
            off += field_spec.fixeddata_len;
            break;
        case RdataFieldSpec::DOMAIN_NAME:
        {
            const uint8_t nlen = encoded_data.at(off);
            const uint8_t olen = encoded_data.at(off + 1);
            if (name_callback) {
                const uint8_t* ndata = &encoded_data.at(off + 2);
                const uint8_t* odata = &encoded_data.at(off + 2 + nlen);
                name_callback(LabelSequence(ndata, odata, olen),
                              field_spec.name_attributes);
            }
            off += (2 + nlen + olen);
            break;
        }
        default:
            assert(false);
        }
    }
}

} // namespace memory
} // namespace datasrc
} // datasrc isc
