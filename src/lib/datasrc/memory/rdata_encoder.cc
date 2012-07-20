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
#include <dns/rdataclass.h>     // for a test function
#include <dns/rrclass.h>
#include <dns/rrtype.h>

#include <util/buffer.h>        // for test functions

#include "rdata_encoder.h"

#include <boost/static_assert.hpp>

#include <cassert>
#include <vector>

#include <stdint.h>

using namespace isc::dns;
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

// A temporary helper of temporary encodeRdata(): it calculates the length
// of the data portion of a NAPTR RDATA (i.e., the RDATA fields before the
// "replacement" name).
size_t
getNAPTRDataLen(const rdata::Rdata& rdata) {
    const rdata::generic::NAPTR& naptr_rdata =
        dynamic_cast<const rdata::generic::NAPTR&>(rdata);

    util::OutputBuffer buffer(0);
    rdata.toWire(buffer);
    return (buffer.getLength() - naptr_rdata.getReplacement().getLength());
}
} // end of unnamed namespace

namespace testing {
void
encodeRdata(const rdata::Rdata& rdata, RRClass rrclass, RRType rrtype,
            vector<uint8_t>& data_result, vector<uint16_t>& len_result)
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
        case RdataFieldSpec::VARLEN_DATA:
        {
            // In the vast majority cases of our supported RR types,
            // variable-length data fields are placed at the end of RDATA,
            // so the length of the field should be the remaining length
            // of the output buffer.  The only exception is NAPTR, for which
            // we use an ad hoc workaround (remember this function is for
            // initial testing only, and will be cleaned up eventually).
            const size_t pos = ibuffer.getPosition();
            const size_t data_len = rrtype == RRType::NAPTR() ?
                getNAPTRDataLen(rdata) : (ibuffer.getLength() - pos);
            tmp.resize(data_len);
            ibuffer.readData(&tmp[0], tmp.size());
            data_result.insert(data_result.end(), tmp.begin(), tmp.end());
            len_result.push_back(data_len);
            break;
        }
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
        }
    }
}

void
foreachRdataField(RRClass rrclass, RRType rrtype,
                  const vector<uint8_t>& encoded_data,
                  const vector<uint16_t>& varlen_list,
                  NameCallback name_callback, DataCallback data_callback)
{
    const RdataEncodeSpec& encode_spec = getRdataEncodeSpec(rrclass, rrtype);

    size_t off = 0;
    size_t varlen_count = 0;
    size_t name_count = 0;
    for (size_t i = 0; i < encode_spec.field_count; ++i) {
        const RdataFieldSpec& field_spec = encode_spec.fields[i];
        switch (field_spec.type) {
        case RdataFieldSpec::FIXEDLEN_DATA:
            if (data_callback) {
                data_callback(&encoded_data.at(off), field_spec.fixeddata_len);
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
        }
    }

    assert(name_count == encode_spec.name_count);
    assert(varlen_count == encode_spec.varlen_count);
}
} // namespace testing

} // namespace memory
} // namespace datasrc
} // datasrc isc
