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

/*! \file
 * Some parts of this code were copied from BIND-9, which in turn was derived
 * from universal hash function libraries of Rice University.

\section license UH Universal Hashing Library

Copyright ((c)) 2002, Rice University
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are
met:

    * Redistributions of source code must retain the above copyright
    notice, this list of conditions and the following disclaimer.

    * Redistributions in binary form must reproduce the above
    copyright notice, this list of conditions and the following
    disclaimer in the documentation and/or other materials provided
    with the distribution.

    * Neither the name of Rice University (RICE) nor the names of its
    contributors may be used to endorse or promote products derived
    from this software without specific prior written permission.


This software is provided by RICE and the contributors on an "as is"
basis, without any representations or warranties of any kind, express
or implied including, but not limited to, representations or
warranties of non-infringement, merchantability or fitness for a
particular purpose. In no event shall RICE or contributors be liable
for any direct, indirect, incidental, special, exemplary, or
consequential damages (including, but not limited to, procurement of
substitute goods or services; loss of use, data, or profits; or
business interruption) however caused and on any theory of liability,
whether in contract, strict liability, or tort (including negligence
or otherwise) arising in any way out of the use of this software, even
if advised of the possibility of such damage.
*/

#include <cassert>
#include <stdlib.h>
#include <algorithm>
#include <cassert>
#include <string>

#include <config.h>

#include "hash.h"

using namespace std;

namespace isc {
namespace nsas {

// Constructor.

Hash::Hash(uint32_t tablesize, uint32_t maxkeylen, bool randomise) :
    tablesize_(tablesize), maxkeylen_(min(maxkeylen, (255 - sizeof(uint16_t))))
{
    // (Code taken from BIND-9)
    //
    // Check to see that we can cope with the maximum key length which, due
    // to the limitations, should not be more than 255 in total.  The actual
    // number of characters in the name that are considered is reduced to
    // ensure that the class is taken into account in the hash.  (This accounts
    // for the "+ sizeof(uint16_t)" in the calculations below.
    //
    // Overflow check.  Since our implementation only does a modulo
    // operation at the last stage of hash calculation, the accumulator
    // must not overflow.
    hash_accum_t overflow_limit =
        1 << (((sizeof(hash_accum_t) - sizeof(hash_random_t))) * 8);
    if (overflow_limit < (maxkeylen_ + sizeof(uint16_t) + 1) * 0xff) {
        isc_throw(KeyLengthTooLong, "Hash key length too long for Hash class");
    }

    // Initialize the random number generator with the current time.
    // TODO: Use something other than pseudo-random numbers.
    union {
        unsigned int    seed;
        time_t          curtime;
    } init_value;

    if (randomise) {
        init_value.curtime = time(NULL);
    }
    else {
        init_value.seed = 0;
    }
    srandom(init_value.seed);

    // Fill in the random vector.
    randvec_.reserve(maxkeylen_ + sizeof(uint16_t) + 1);
    for (uint32_t i = 0; i < (maxkeylen + sizeof(uint16_t) + 1); ++i) {
        randvec_.push_back(static_cast<hash_random_t>(random() & 0xffff));
    }
    assert(sizeof(hash_random_t) == 2); // So that the "& 0xffff" is valid

    // Finally, initialize the mapping table for uppercase to lowercase
    // characters.  A table is used as indexing a table is faster than calling
    // the tolower() function.
    casemap_.reserve(256);
    for (int i = 0; i < 256; ++i) {
        casemap_.push_back(i);
    }
    for (int i = 'A'; i <= 'Z'; ++i) {
        casemap_[i] += ('a' - 'A');
    }
}


uint32_t Hash::operator()(const HashKey& key, bool ignorecase) const
{
    // Calculation as given in BIND-9.
    hash_accum_t partial_sum = 0;
    uint32_t i = 0;                 // Used after the end of the loop

    // Perform the hashing.  If the key length if more than the maximum we set
    // up this hash for, ignore the excess.
    if (ignorecase) {
        for (i = 0; i < min(key.keylen, maxkeylen_); ++i) {
            partial_sum += mapLower(key.key[i]) * randvec_[i];
        }
    } else {
        for (i = 0; i < min(key.keylen, maxkeylen_); ++i) {
            partial_sum += key.key[i] * randvec_[i];
        }
    }

    // Add the hash of the class code
    union {
        uint16_t    class_code;                 // Copy of the class code
        char        bytes[sizeof(uint16_t)];    // Byte equivalent
    } convert;

    convert.class_code = key.class_code;
    for (int j = 0; j < sizeof(uint16_t); ++j, ++i) {
        partial_sum += convert.bytes[j] * randvec_[i];
    }

    // ... and finish up.
    partial_sum += randvec_[i];

    // Determine the hash value
    uint32_t value = partial_sum % prime32_;

    // ... and round it to fit the table size
    return (value % tablesize_);
}

} // namespace nsas
} // namespace isc
