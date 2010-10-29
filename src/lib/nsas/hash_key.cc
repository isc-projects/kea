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

#include <string.h>

#include "config.h"
#include "hash_key.h"

namespace isc {
namespace nsas {

/// Hash Equality Function
bool HashKey::operator==(const isc::nsas::HashKey& other) {

    // Check key lengths
    if (other.keylen == keylen) {

        // ... and classes
        if (other.class_code == class_code) {

            // ... before the expensive operation.  This involves a
            // byte-by-byte comparison, doing a case-independent match.
            // memcmp() doesn't work (exact match) nor does strcmp or its
            // variation (stops on the first null byte).
            //
            // TODO: Use a lookup table to map upper to lower case (for speed)
            for (int i = 0; i < other.keylen; ++i) {
                if (tolower(static_cast<unsigned char>(other.key[i])) !=
                    tolower(static_cast<unsigned char>(key[i]))) {
                    return false;   // Mismatch
                }
            }
            return true;    // All bytes matched
        }
    }
    return false;   // Key length or class did not match
}

} // namespace nsas
} // namespace isc
