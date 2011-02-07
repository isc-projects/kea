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

#ifndef _ISC_RESOLVE_H
#define _ISC_RESOLVE_H 1

/// This file includes all other libresolve headers, and provides
/// several helper functions used in resolving.

#include <resolve/resolver_interface.h>
#include <resolve/resolver_callback.h>
#include <resolve/response_classifier.h>

namespace isc {
namespace resolve {

/// \brief Create an error response
///
/// Clears the answer, authority, and additional section of the
/// given MessagePtr and sets the given error code
///
/// Notes: Assuming you have already done initial preparations
/// on the given answer message (copy the opcode, qid and question
/// section), you can simply use this to create an error response.
///
/// \param answer_message The message to clear and place the error in
/// \param question The question to add to the
/// \param error_code The error Rcode
void
makeErrorMessage(isc::dns::MessagePtr answer_message,
                 const isc::dns::Rcode::Rcode& error_code);

} // namespace resolve
} // namespace isc

#endif // ISC_RESOLVE_H_
