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

#include <string.h>
#include <log/message_types.h>

namespace isc {
namespace log {

// Compare MessageID for Equality

bool equalMessageID(const MessageID& m1, const MessageID& m2) {

    // Attempt to optimise the check.  If both are the same instance of the
    // message ID, the check for addresses will successed.  If both are the
    // same message ID but declared in a separate files (so different
    // addresses but pointing to the same string), the string equality check
    // will work.
    return ((m1 == m2) || (strcmp(m1, m2) == 0));
}

} // namespace log
} // namespace isc



