// Copyright (C) 2011  Internet Systems Consortium, Inc. ("ISC")
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

#include <stdint.h>

#include <sstream>
#include <vector>

namespace isc {
namespace dns {
namespace rdata {
namespace generic {
namespace detail {
namespace nsec {

/// \file
///
/// This helper module provides some utilities that handle NSEC and NSEC3
/// type bitmaps.  The format and processing of the type bitmaps are generally
/// the same for these two RRs, so it would make sense to consolidate
/// the processing logic into a single implementation module.
///
/// The functions defined here are essentially private and are only expected
/// to be called from the \c NSEC and \c NSEC3 class implementations.

/// \brief Check if a given "type bitmap" for NSEC/NSEC3 is valid.
///
/// This function checks given wire format data (stored in a
/// \c std::vector) is a valid type bitmaps used for the NSEC and NSEC3 RRs
/// according to RFC4034 and RFC5155.
///
/// \exception DNSMessageFORMERR The bitmap is not valid.
///
/// \param rrtype_name Either "NSEC" or "NSEC3"; used as part of exception
/// messages.
/// \param typebits The type bitmaps in wire format.  The size of vector
/// is the total length of the bitmaps.
void checkRRTypeBitmaps(const char* const rrtype_name,
                        const std::vector<uint8_t>& typebits);

/// \brief Convert textual sequence of RR types into type bitmaps.
///
/// This function extracts a sequence of strings, converts each sequence
/// into an RR type, and builds NSEC/NSEC3 type bitmaps with the corresponding
/// bits for the extracted types being on.  The resulting bitmaps (which are
/// in the wire format according to RFC4034 and RFC5155) are stored in the
/// given vector.  This function expects the given string stream ends with
/// the sequence.
///
/// \exception InvalidRdataText The given input stream does not meet the
/// assumption (e.g. including invalid form of RR type, not ending with
/// an RR type string).
///
/// \param rrtype_name Either "NSEC" or "NSEC3"; used as part of exception
/// messages.
/// \param iss Input stream that consists of a complete sequence of textual
/// RR types for which the corresponding bits are set.
/// \param typebits A placeholder for the resulting bitmaps.  Expected to be
/// empty, but it's not checked.
void buildBitmapsFromText(const char* const rrtype_name,
                          std::istringstream& iss,
                          std::vector<uint8_t>& typebits);

/// \brief Convert type bitmaps to textual sequence of RR types.
///
/// This function converts wire-format data of type bitmaps for NSEC/NSEC3
/// into a sequence of corresponding RR type strings, and inserts them
/// into the given output stream with separating them by a single space
/// character.
///
/// This function assumes the given bitmaps are valid in terms of RFC4034
/// and RFC5155 (in practice, it assumes it's from a validly constructed
/// NSEC or NSEC3 object); if it detects a format error, it aborts the
/// program with assert().
///
/// \param typebits The type bitmaps in wire format.  The size of vector
/// is the total length of the bitmaps.
/// \param oss The output stream to which the converted RR type sequence
/// are to be inserted.
void bitmapsToText(const std::vector<uint8_t>& typebits,
                   std::ostringstream& oss);
}
}
}
}
}
}

// Local Variables:
// mode: c++
// End:
