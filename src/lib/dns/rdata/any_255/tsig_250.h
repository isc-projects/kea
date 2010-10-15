// Copyright (C) 2010  Internet Systems Consortium, Inc. ("ISC")
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

// $Id$

// BEGIN_HEADER_GUARD

#include <stdint.h>

#include <string>

#include <dns/rdata.h>

namespace isc {
namespace dns {
class Name;
}
}

// BEGIN_ISC_NAMESPACE

// BEGIN_COMMON_DECLARATIONS
// END_COMMON_DECLARATIONS

// BEGIN_RDATA_NAMESPACE

/// \brief \c rdata::TSIG class represents the TSIG RDATA as defined %in
/// RFC2845.
///
/// This class implements the basic interfaces inherited from the abstract
/// \c rdata::Rdata class, and provides trivial accessors specific to the
/// TSIG RDATA.
class TSIG : public Rdata {
public:
    // BEGIN_COMMON_MEMBERS
    // END_COMMON_MEMBERS

    /// \brief Constructor from RDATA field parameters.
    ///
    /// The parameters are a straightforward mapping of %TSIG RDATA
    /// fields as defined %in RFC2845, but there are some implementation
    /// specific notes as follows.
    ///
    /// \c algorithm is a \c Name object that specifies the algorithm.
    /// For example, if the algorithm is HMAC-SHA256, \c algorithm would be
    /// \c Name("hmac-sha256").
    ///
    /// \c time_signed corresponds to the Time Signed field, which is of
    /// 48-bit unsigned integer type, and therefore cannot exceed 2^48-1;
    /// otherwise, an exception of type \c OutOfRange will be thrown.
    ///
    /// \c mac_size and \c mac correspond to the MAC Size and MAC fields,
    /// respectively.  When the MAC field is empty, \c mac must be NULL.
    /// \c mac_size and \c mac must be consistent %in that \c mac_size is 0 if
    /// and only if \c mac is NULL; otherwise an exception of type
    /// InvalidParameter will be thrown.
    ///
    /// The same restriction applies to \c other_len and \c other_data,
    /// which correspond to the Other Len and Other Data fields, respectively.
    ///
    /// This constructor internally involves resource allocation, and if
    /// it fails, a corresponding standard exception will be thrown.
    TSIG(const Name& algorithm, uint64_t time_signed, uint16_t fudge,
         uint16_t mac_size, const void* mac, uint16_t original_id,
         uint16_t error, uint16_t other_len, const void* other_data);

    /// \brief Assignment operator.
    ///
    /// It internally allocates a resource, and if it fails a corresponding
    /// standard exception will be thrown.
    /// This operator never throws an exception otherwise.
    ///
    /// This operator provides the strong exception guarantee: When an
    /// exception is thrown the content of the assignment target will be
    /// intact.
    TSIG& operator=(const TSIG& source);

    /// \brief The destructor.
    ~TSIG();

    /// \brief Return the algorithm name.
    ///
    /// This method never throws an exception.
    const Name& getAlgorithm() const;

    /// \brief Return the value of the Time Signed field.
    ///
    /// The returned value does not exceed 2^48-1.
    ///
    /// This method never throws an exception.
    uint64_t getTimeSigned() const;

    /// \brief Return the value of the Fudge field.
    ///
    /// This method never throws an exception.
    uint16_t getFudge() const;

    /// \brief Return the value of the MAC Size field.
    ///
    /// This method never throws an exception.
    uint16_t getMACSize() const;

    /// \brief Return the value of the MAC field.
    ///
    /// If the MAC field is empty, it returns NULL.
    /// Otherwise, the memory region beginning at the address returned by
    /// this method is valid up to the bytes specified by the return value
    /// of \c getMACSize().
    /// The memory region is only valid while the corresponding \c TSIG
    /// object is valid.  The caller must hold the \c TSIG object while
    /// it needs to refer to the region or it must make a local copy of the
    /// region.
    ///
    /// This method never throws an exception.
    const void* getMAC() const;

    /// \brief Return the value of the Original ID field.
    ///
    /// This method never throws an exception.
    uint16_t getOriginalID() const;

    /// \brief Return the value of the Error field.
    ///
    /// This method never throws an exception.
    uint16_t getError() const;

    /// \brief Return the value of the Other Len field.
    ///
    /// This method never throws an exception.
    uint16_t getOtherLen() const;

    /// \brief Return the value of the Other Data field.
    ///
    /// The same note as \c getMAC() applies.
    ///
    /// This method never throws an exception.
    const void* getOtherData() const;
private:
    struct TSIGImpl;
    TSIGImpl* impl_;
};

// END_RDATA_NAMESPACE
// END_ISC_NAMESPACE
// END_HEADER_GUARD

// Local Variables:
// mode: c++
// End:
