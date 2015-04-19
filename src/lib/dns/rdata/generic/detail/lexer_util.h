// Copyright (C) 2013, 2015 Internet Systems Consortium, Inc. ("ISC")
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

#ifndef DNS_RDATA_LEXER_UTIL_H
#define DNS_RDATA_LEXER_UTIL_H 1

#include <dns/api.h>
#include <dns/name.h>
#include <dns/master_lexer.h>

/// \file lexer_util.h
/// \brief Utilities for extracting RDATA fields from lexer.
///
/// This file intends to define convenient small routines that can be
/// commonly used in the RDATA implementation to build RDATA fields from
/// a \c MasterLexer.

namespace isc {
namespace dns {
namespace rdata {
namespace generic {
namespace detail {

/// \brief Construct a Name object using a master lexer and optional origin.
///
/// This is a convenient shortcut of commonly used code pattern that would
/// be used to build RDATA that contain a domain name field.
///
/// Note that this function throws an exception against invalid input.
/// The (direct or indirect) caller's responsibility needs to expect and
/// handle exceptions appropriately.
///
/// \throw MasterLexer::LexerError The next token from lexer is not string.
/// \throw Other Exceptions from the \c Name class constructor if the next
/// string token from the lexer does not represent a valid name.
///
/// \param lexer A \c MasterLexer object.  Its next token is expected to be
/// a string that represent a domain name.
/// \param origin If non NULL, specifies the origin of the name to be
/// constructed.
///
/// \return A new Name object that corresponds to the next string token of
/// the \c lexer.
inline Name
createNameFromLexer(MasterLexer& lexer, const Name* origin) {
    const MasterToken::StringRegion& str_region =
        lexer.getNextToken(MasterToken::STRING).getStringRegion();
    return (Name(str_region.beg, str_region.len, origin));
}

} // namespace detail
} // namespace generic
} // namespace rdata
} // namespace dns
} // namespace isc
#endif  // DNS_RDATA_LEXER_UTIL_H

// Local Variables:
// mode: c++
// End:
