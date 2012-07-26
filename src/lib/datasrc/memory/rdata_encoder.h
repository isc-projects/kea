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

#ifndef DATASRC_MEMORY_RDATA_ENCODER_H
#define DATASRC_MEMORY_RDATA_ENCODER_H 1

#include <exceptions/exceptions.h>

#include <dns/labelsequence.h>
#include <dns/rdata.h>
#include <dns/rrclass.h>
#include <dns/rrtype.h>

#include <boost/function.hpp>
#include <boost/noncopyable.hpp>

#include <vector>

namespace isc {
namespace datasrc {
namespace memory {

/// \brief General error in RDATA encoding.
///
/// This is thrown when \c RdataEncoder encounters a rare, unsupported
/// situation. a method is called for a name or RRset which
/// is not in or below the zone.
class RdataEncodingError : public Exception {
public:
    RdataEncodingError(const char* file, size_t line, const char* what) :
        Exception(file, line, what) {}
};

/// \brief Attributes of domain name fields of encoded RDATA.
///
/// The enum values define special traits of the name that can affect how
/// it should be handled in rendering or query processing.
enum RdataNameAttributes {
    NAMEATTR_COMPRESSIBLE = 1,  ///< Name should be compressed when rendered
    NAMEATTR_ADDITIONAL = (NAMEATTR_COMPRESSIBLE << 1) ///< Name requires
                                                      ///< Additional section
                                                      ///< handling
};

/// \brief TBD
///
/// Encoding, FYI:
/// uint16_t n1_1: size of 1st variable len field (if any) of 1st RDATA
/// uint16_t n1_2: size of 2nd variable len field of 1st RDATA
/// ...
/// uint16_t nN_M: size of last (Mth) variable len field of last (Nth) RDATA
/// A sequence of packed data fields follow:
/// uint8_t[]: data field value, length specified by nI_J (in case it's
///            variable) or by the field spec (in case it's fixed-length).
/// or
/// opaque data, LabelSequence::getSerializedLength() bytes: data for a name
/// (a possible 1-byte padding)
/// uint16_t ns1: size of 1st RRSIG data
/// ...
/// uint16_t nsL: size of last (Lth) RRSIG data
/// uint8_t[ns1]: 1st RRSIG data
/// ...
/// uint8_t[nsL]: last RRSIG data
class RdataEncoder : boost::noncopyable {
public:
    /// \brief Default constructor.
    RdataEncoder();

    /// \brief The destrcutor.
    ~RdataEncoder();

    /// \brief TBD
    ///
    /// \throw BadValue RRSIG is specified as rrtype.
    void start(dns::RRClass rrclass, dns::RRType rrtype);

    /// \brief TBD
    ///
    /// This implementation does not support RDATA (or any subfield of it)
    /// whose size exceeds 65535 bytes (max uint16_t value).  Such RDATA
    /// may not necessarily considered invalid in terms of protocol
    /// specification, but in practice it's mostly useless because the
    /// corresponding RR won't fit in any valid DNS message.
    ///
    /// \throw InvalidOperation called before start().
    /// \throw BadValue inconsistent data found.
    /// \throw RdataEncodingError A very unusual case, such as over 64KB RDATA.
    /// \throw std::bad_alloc Internal memory allocation failure.
    void addRdata(const dns::rdata::Rdata& rdata);

    void addSIGRdata(const dns::rdata::Rdata& sig_rdata);

    /// \brief TBD
    ///
    /// \throw InvalidOperation called before start().
    size_t getStorageLength() const;

    /// \brief TBD
    ///
    /// \throw InvalidOperation called before start().
    /// \throw BadValue buffer is NULL or it's too short for the encoded data.
    void encode(void* buf, size_t buf_len) const;

private:
    struct RdataEncoderImpl;
    RdataEncoderImpl* impl_;
};

// We use the following quick-hack version of encoder and "foreach"
// operator until we implement the complete versions.  The plan is to
// update the test cases that use these functions with the complete
// functions/classes, and then remove the entire namespace.
namespace testing {
// Callbacks used in foreachRdataField.
typedef boost::function<void(const dns::LabelSequence&,
                             RdataNameAttributes)> NameCallback;
typedef boost::function<void(const uint8_t*, size_t)> DataCallback;

// Iterate over each field (in terms of the internal encoding) of each
// RDATA stored in encoded_data, and call the given callback for each
// data (for domain name fields, name_callback will be called; for
// normal data fields data_callback will be called).  rdata_count is
// the number of RDATAs.  If the encoded data contain variable-length
// data fields, varlen_list should store a sequence of their lengths,
// in the order of the appearance.
void foreachRdataField(dns::RRClass rrclass, dns::RRType rrtype,
                       size_t rdata_count,
                       const std::vector<uint8_t>& encoded_data,
                       const std::vector<uint16_t>& varlen_list,
                       NameCallback name_callback, DataCallback data_callback);

// Iterate over each RRSIG stored in encoded_data, and call the given
// callback for each.  rrsiglen_list should store a sequence of their lengths,
// in the order of the appearance.  Its size is the number of RRSIGs.
// The list can be empty, in which case this function does nothing.
void foreachRRSig(const std::vector<uint8_t>& encoded_data,
                  const std::vector<uint16_t>& rrsiglen_list,
                  DataCallback data_callback);
}

} // namespace memory
} // namespace datasrc
} // namespace isc

#endif // DATASRC_MEMORY_RDATA_ENCODER_H

// Local Variables:
// mode: c++
// End:
