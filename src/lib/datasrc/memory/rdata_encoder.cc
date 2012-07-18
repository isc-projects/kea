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

#include <dns/rrclass.h>
#include <dns/rrtype.h>

#include "rdata_encoder.h"

#include <stdint.h>

using namespace isc::dns;

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

const uint16_t NAME_NOATTRIBUTE_INITIALIZER = static_cast<uint16_t>(0);
const uint16_t NAME_COMPRESSIBLE_INITIALIZER =
    static_cast<uint16_t>(NAME_COMPRESSIBLE);
const uint16_t NAME_ADDITIONAL_INITIALIZER =
    static_cast<uint16_t>(NAME_ADDITIONAL);
const uint16_t NAME_COMPADDITIONAL_INITIALIZER =
    static_cast<uint16_t>(NAME_COMPRESSIBLE | NAME_ADDITIONAL);

const RdataFieldSpec generic_data_fields[] = {
    {RdataFieldSpec::VARLEN_DATA, {0}}
};
const uint16_t generic_data_fields_count =
    sizeof(generic_data_fields) / sizeof(RdataFieldSpec);

const RdataFieldSpec generic_single_name_fields[] = {
    {RdataFieldSpec::VARLEN_DATA, {NAME_COMPADDITIONAL_INITIALIZER}}
};

// Class IN encode specs
const RdataEncodeSpec encode_spec_list_in[] = {
    {generic_data_fields_count, 0, 0, generic_data_fields} // type #0
};

#ifdef notyet
inline
const RdataEncodeSpec&
getRdataEncodeSpec(RRClass rrclass, RRType rrtype) {
    if (rrclass == RRClass::IN()) {
        return (encode_spec_list_in[rrtype.getCode()]);
    }
    return (encode_spec_list_in[0]);
}
#endif
} // end of unnamed namespace

#ifdef notyet
void
testRdataEncoder(const Rdata& rdata, RRClass rrclass, RRType rrtype,
                 vector<uint8_t>& result)
{
    const RdataEncodeSpec& encode_spec = getRdataEncodeSpec(rrclass, rrtype);
    for (size_t i = 0; i < encode_spec.field_count; ++i) {
        const RdataFieldSpec& field_spec = *encode_spec.fields[i];
        if (field_spec.type == RdataFieldSpec::FIXEDLEN_DATA)
        assert(encode_spec.fields[i] != NULL);
        
    }
}
#endif

} // namespace memory
} // namespace datasrc
} // datasrc isc
