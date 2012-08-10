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

#ifndef DATASRC_MEMORY_RDATA_FIELD
#define DATASRC_MEMORY_RDATA_FIELD

#include <stdint.h>

/// \file rdata_field.h
///
/// This header should be considered private to the implementation and should
/// not be used from outside.
///
/// It is used to share the definition of encoding for RRtypes.

namespace isc {
namespace dns {
class RRType;
class RRClass;
}
namespace datasrc {
namespace memory {

/// \brief Attributes of domain name fields of encoded RDATA.
///
/// The enum values define special traits of the name that can affect how
/// it should be handled in rendering or query processing.
enum RdataNameAttributes {
    NAMEATTR_NONE = 0,          ///< No special attributes
    NAMEATTR_COMPRESSIBLE = 1,  ///< Name should be compressed when rendered
    NAMEATTR_ADDITIONAL = (NAMEATTR_COMPRESSIBLE << 1) ///< Name requires
                                                      ///< Additional section
                                                      ///< handling
};

/// Specification of a single RDATA field in terms of internal encoding.
struct RdataFieldSpec {
    enum FieldType {
        FIXEDLEN_DATA = 0,      // fixed-length data field
        VARLEN_DATA,            // variable-length data field
        DOMAIN_NAME             // domain name
    };

    const FieldType type;       // field type

    // The length of fixed-length data field.  Only valid for FIXEDLEN_DATA.
    // For type DOMAIN_NAME, set it to 0.
    const uint16_t fixeddata_len;

    // Attributes of the name.  Only valid for DOMAIN_NAME.
    // For type _DATA, set it to NAMEATTR_NONE.
    const RdataNameAttributes name_attributes;
};

/// Specification of RDATA in terms of internal encoding.
///
/// The fields must be a sequence of:
/// <0 or 1 fixed/var-len data field>,
/// <1 or more domain name fields>,
/// <1 fixed/var-len data field>,
/// <1 or more domain name fields>,
/// <1 fixed/var-len data field>,
/// ...and so on.
/// There must not be more than one consecutive data fields (i.e., without
/// interleaved by a domain name); it would just be inefficient in terms of
/// memory footprint and iterating over the fields, and it would break
/// some assumption within the encoder implementation.  For consecutive
/// data fields in the DNS protocol, if all fields have fixed lengths, they
/// should be combined into a single fixed-length field (like the last 20
/// bytes of SOA RDATA).  If there's a variable length field, they should be
/// combined into a single variable-length field (such as DNSKEY, which has
/// 3 fixed-length fields followed by one variable-length field).
struct RdataEncodeSpec {
    const uint16_t field_count; // total number of fields (# of fields member)
    const uint16_t name_count;  // number of domain name fields
    const uint16_t varlen_count; // number of variable-length data fields
    const RdataFieldSpec* const fields; // list of field specs
};

/// \brief Get the spec for given class and type
const RdataEncodeSpec&
getRdataEncodeSpec(const dns::RRClass& rrclass, const dns::RRType& rrtype);

}
}
}

#endif
