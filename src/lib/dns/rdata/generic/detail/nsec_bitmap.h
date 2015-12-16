// Copyright (C) 2011-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef NSECBITMAP_H
#define NSECBITMAP_H 1

#include <dns/master_lexer.h>

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

/// \brief Convert textual sequence of RR types read from a lexer into
/// type bitmaps.
///
/// See the other variant above for description. If \c allow_empty is
/// true and there are no mnemonics, \c typebits is left untouched.
///
/// \exception InvalidRdataText Data read from the given lexer does not
/// meet the assumption (e.g. including invalid form of RR type, not
/// ending with an RR type string).
///
/// \param rrtype_name Either "NSEC" or "NSEC3"; used as part of exception
/// messages.
/// \param lexer MasterLexer that provides consists of a complete
/// sequence of textual lexemes of RR types for which the corresponding
/// bits are set.
/// \param typebits A placeholder for the resulting bitmaps.  Expected to be
/// empty, but it's not checked.
/// \param allow_empty If true, the function simply returns if no RR
/// type mnemonics are found. Otherwise, it throws an exception if no RR
/// type mnemonics are found.
void buildBitmapsFromLexer(const char* const rrtype_name,
                           isc::dns::MasterLexer& lexer,
                           std::vector<uint8_t>& typebits,
                           bool allow_empty = false);

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

#endif  // NSECBITMAP_H

// Local Variables:
// mode: c++
// End:
