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
/// not be used included directly.
///
/// It is used to share the definition of encoding for RRtypes.
///
/// These are types shared by classes in rdata_encoder.h and rdata_reader.h.
/// The defyne a set of interfaces (classes, types, constants) to
/// manipulate a given set of RDATA of the same type (normally associated with
/// an RRset) that may be accompanied with RRSIGs in a memory efficient way.
///
/// The entire set of RDATA is stored in a packed form in a contiguous
/// memory region.  It's opaque data, without containing non trivial
/// data structures, so it can be located anywhere in the memory or even
/// dumped to a file.
///
/// Two main classes are provided: one is
/// \c isc::datasrc::memory::RdataEncoder, which allows
/// the application to create encoded data for a set of RDATA;
/// the isc::datasrc::memory::RdataReader provides an interface to iterate
/// over encoded set of RDATA for purposes such as data lookups or rendering
/// the data into the wire format to create a DNS message.
///
/// The actual encoding detail is private information to the implementation,
/// and the application shouldn't assume anything about that except that
/// each RDATA is considered to consist of one or more generic fields,
/// and each field is typed as either opaque data or a domain name.
/// A domain name field has additional attributes
/// (see \c isc::datasrc::memory::RdataNameAttributes)
/// so the application can change how the name should be handled in terms
/// of the DNS protocol (e.g., whether it's subject to name compression).
///
/// The following are the current implementation of internal encoding, shown
/// only for reference.  Applications must not assume this particular form
/// for the encoded data; in fact, it can change in a future version of the
/// implementation.
/// \verbatim
// The encoded data begin with a series of 16-bit length fields (values are
// stored in the host byte order).  The sequence may be empty.
// uint16_t n1_1: size of 1st variable len field (if any) of 1st RDATA
// uint16_t n1_2: size of 2nd variable len field of 1st RDATA
// ...
// uint16_t nN_M: size of last (Mth) variable len field of last (Nth) RDATA
// uint16_t ns1: size of 1st RRSIG (if any) data
// ...
// uint16_t nsL: size of last (Lth) RRSIG data
// A sequence of packed data fields follows:
// uint8_t[]: data field value, length specified by nI_J (in case it's
//            variable-length) or by the per type field spec (in case it's
//            fixed-length).
// or
// opaque data, LabelSequence::getSerializedLength() bytes: data for a name
// uint8_t[ns1]: 1st RRSIG data
// ...
// uint8_t[nsL]: last RRSIG data
// \endverbatim
///
/// As described above, this implementation treats RRSIGs as opaque data
/// that don't contain any domain names.  Technically, it has a "signer"
/// domain name field in the sense of RFC4034.  In practice, however, this
/// field is essentially mere data; it's not subject to name compression,
/// and since it's very likely to be a subdomain of (or equal to) the
/// owner name of the corresponding RR (or, if used in a DNS message,
/// some domain name that already appears before this field), so it won't
/// be a target of name compression either.  By treating the entire RRSIG
/// as single-field data we can make the implementation simpler, and probably
/// make it faster in rendering it into a DNS message.

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
