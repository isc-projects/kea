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

#include "rdata_field.h"

#include <exceptions/exceptions.h>

#include <dns/labelsequence.h>
#include <dns/rdata.h>
#include <dns/rrclass.h>
#include <dns/rrtype.h>

#include <boost/function.hpp>
#include <boost/noncopyable.hpp>

#include <vector>

/// \file rdata_encoder.h
/// \brief Set of utility classes for encoding RDATA in memory efficient way.
///
/// This file defines a set of interfaces (classes, types, constants) to
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
/// the other (TBD) provides an interface to iterate over encoded set of
/// RDATA for purposes such as data lookups or rendering the data into the
/// wire format to create a DNS message.
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

/// \brief RDATA encoder.
///
/// This class provides interfaces to encode a set of RDATA of a specific
/// RR class and type, possibly with their RRSIG RDATAs, in a memory-efficient
/// format.  In many cases these sets of RDATA come from a specific (signed
/// or unsigned) RRset.
///
/// It is expected for a single \c RdataEncoder object to be used multiple
/// times for different sets of RDATA, such as in loading an entire zone
/// into memory.  Each encoding session begins with the \c start() method,
/// which sets the context for the specific RR class and type to be encoded.
/// Any number of calls to \c addRdata() or \c addSIGRdata() follow, each
/// of which updates the internal state of the encoder with the encoding
/// information for the given RDATA or RRSIG RDATA, respectively.
/// The \c addRdata() is expected to be called with an
/// \c isc::dns::rdata::Rdata object
/// of the specified class and type, and \c addRdata() checks the consistency
/// for the purpose of encoding (but it's not completely type safe; for
/// example, it wouldn't distinguish TXT RDATA and HINFO RDATA.
/// Likewise, an \c isc::dns::rdata::Rdata given to \c addSIGRdata() is
/// expected to be of RRSIG, but the method does not check the assumption).
///
/// After passing the complete set of RDATA and their RRSIG, the application
/// is expected to call \c getStorageLength() to know the size of storage
/// that is sufficient to store all encoded data.  Normally the application
/// would allocate a memory region of that size, and then call \c encode()
/// with the prepared region.  The \c encode() method dumps encoded data
/// to the given memory region.
///
/// The caller can reuse the \c RdataEncoder object for another set of RDATA
/// by repeating the session from \c start().
class RdataEncoder : boost::noncopyable {
public:
    /// \brief Default constructor.
    RdataEncoder();

    /// \brief The destrcutor.
    ~RdataEncoder();

    /// \brief Start the encoding session.
    ///
    /// It re-initializes the internal encoder state for a new encoding
    /// session.  The \c rrclass and \c rrtype parameters specify the
    /// type of RDATA to be encoded in the new session.  Note that if the
    /// set of RDATA is signed, \c rrtype always specifies the "signed" type;
    /// it must not be RRSIG.
    ///
    /// \throw BadValue RRSIG is specified for rrtype.
    ///
    /// \param rrclass The RR class of RDATA to be encoded in the session.
    /// \param rrtype The RR type of RDATA to be encoded in the session.
    void start(dns::RRClass rrclass, dns::RRType rrtype);

    /// \brief Add an RDATA for encoding.
    ///
    /// This method updates internal state of the \c RdataEncoder() with the
    /// given RDATA so it will be part of the encoded data in a subsequent
    /// call to \c encode().
    ///
    /// The given \c rdata must be of the RR class and type specified at
    /// the prior call to \c start().  This method checks the assumption
    /// to some extent, but the check is not complete; this is generally
    /// the responsibility of the caller.
    ///
    /// The caller can destroy \c rdata after this call is completed.
    ///
    /// \note This implementation does not support RDATA (or any subfield of
    /// it) whose size exceeds 65535 bytes (max uint16_t value).  Such RDATA
    /// may not necessarily be considered invalid in terms of protocol
    /// specification, but in practice it's mostly useless because the
    /// corresponding RR won't fit in any valid DNS message.
    ///
    /// As long as the \c rdata is of the correct type and its size is normal,
    /// this method should normally be exception free.  If it throws, however,
    /// it doesn't always provide the strong exception guarantee.  In general,
    /// the caller needs to either destroy the encoder object or restart a
    /// new session from \c start() should this method throws an exception.
    ///
    /// \throw InvalidOperation called before start().
    /// \throw BadValue inconsistent data found.
    /// \throw RdataEncodingError A very unusual case, such as over 64KB RDATA.
    /// \throw std::bad_alloc Internal memory allocation failure.
    ///
    /// \param rdata An RDATA to be encoded in the session.
    void addRdata(const dns::rdata::Rdata& rdata);

    /// \brief Add an RRSIG RDATA for encoding.
    ///
    /// This method updates internal state of the \c RdataEncoder() with the
    /// given RDATA, which is assumed to be of type RRSIG that covers the
    /// type specified at the time of \c start() for the encoding session.
    /// The corresponding data for the RRSIG RDATA will be encoded in a
    /// subsequent call to \c encode().
    ///
    /// The passed \c sig_rdata is expected to be of type RRSIG and cover
    /// the RR type specified at the call to \c start() to this encoding
    /// session.  But this method does not check if it is the case at all;
    /// it could even accept any type of RDATA as opaque data.  It's caller's
    /// responsibility to ensure the assumption.
    ///
    /// The caller can destroy \c rdata after this call is completed.
    ///
    /// \note Like addRdata(), this implementation does not support
    /// RRSIG RDATA whose size (in the form of wire format) exceeds 65535
    /// bytes.
    ///
    /// The same note about exception safety as \c addRdata() applies.
    ///
    /// \throw InvalidOperation called before start().
    /// \throw RdataEncodingError A very unusual case, such as over 64KB RDATA.
    /// \throw std::bad_alloc Internal memory allocation failure.
    ///
    /// \param sig_rdata An RDATA to be encoded in the session.  Supposed to
    /// be of type RRSIG.
    void addSIGRdata(const dns::rdata::Rdata& sig_rdata);

    /// \brief Return the length of space for encoding for the session.
    ///
    /// It returns the size of the encoded data that would be generated for
    /// the set of RDATA (and RRSIGs) in the encoder at the call of this
    /// method.  It's ensured that a buffer of that size can be safely passed
    /// to \c encode() unless there's no other "add" method is called by then.
    ///
    /// As long as this method is called after start(), it never throws.
    ///
    /// \throw InvalidOperation called before start().
    ///
    /// \return The expected size of the encoded data at the time of the call.
    size_t getStorageLength() const;

    /// \brief Encode RDATAs of the session to a buffer.
    ///
    /// This method dumps encoded data for the stored set of RDATA and
    /// their RRSIGs to a given buffer.  The buffer must have a size
    /// at least as large as the return value of a prior call to
    /// \c getStorageLength() (it may be larger than that).
    ///
    /// The given buffer must be aligned at the natural boundary for
    /// 16-bit integers.  The method doesn't check this condition; it's
    /// caller's responsibility to ensure that.  Note: the alignment
    /// requirement may change in a future version of this implementation.
    ///
    /// As long as this method is called after start() and the buffer is
    /// valid with a sufficient size, this method never throws.
    ///
    /// \throw InvalidOperation called before start().
    /// \throw BadValue buffer is NULL or it's too short for the encoded data.
    ///
    /// \param buf A pointer to the buffer to which encoded data are to be
    /// dumped.
    /// \param buf_len The size of the buffer in bytes.
    void encode(void* buf, size_t buf_len) const;

private:
    struct RdataEncoderImpl;
    RdataEncoderImpl* impl_;
};

} // namespace memory
} // namespace datasrc
} // namespace isc

#endif // DATASRC_MEMORY_RDATA_ENCODER_H

// Local Variables:
// mode: c++
// End:
