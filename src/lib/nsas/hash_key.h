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

#ifndef HASH_KEY_H
#define HASH_KEY_H

#include <dns/rrclass.h>

#include <stdint.h>
#include <string>

namespace isc {
namespace nsas {

/// \brief Hash Key
///
/// In the nameserver address store, an object is placed into a hash table
/// according to its key (name) and class.
///
/// The key comprises two elements, a pointer to the start of a char string
/// holding the data that describes the key and a length.  This has been
/// chosen over a std::string because:
///
/// # The key may not be a string, it may be binary data
/// # The overhead of creating std::string objects from such data.
///
/// "key" is declared as "const char*" - rather than the more semantically
/// correct "const uint8_t*" - simply because if std::strings are used, then
/// the c_str function will return a "const char*".
///
/// To avoid passing round three elements (key, key length, and class), they
/// have been combined into this simple struct.
struct HashKey {

    /// \brief Constructor
    ///
    /// Basic constructor to make the hash key.
    ///
    /// \param the_key Array of bytes for which key is to be constructed
    /// \param the_keylen Length of the byte array
    /// \param the_class_code Class of this entry
    HashKey(const char* the_key, uint32_t the_keylen,
        const isc::dns::RRClass& the_class_code) :
        key(the_key),
        keylen(the_keylen),
        class_code(the_class_code)
    {}

    /// \brief String Constructor
    ///
    /// Convenience constructor using a std::string.
    ///
    /// \param the_key Name to use as the key for the hash
    /// \param the_class_code Class of this entry
    HashKey(const std::string& the_key,
        const isc::dns::RRClass& the_class_code) :
        key(the_key.c_str()),
        keylen(the_key.size()),
        class_code(the_class_code)
    {}

    /// \brief Equality
    ///
    /// Convenience for unit testing, this matches two hash keys as being
    /// equal if the key strings match on a case-independent basis and the
    /// classes match.
    ///
    /// Note that the class strings may include null bytes; the match is
    /// done on a byte-by-byte basis, with codes in the range 'A' to 'Z' being
    /// mapped to 'a' to 'z'.
    ///
    /// \param other Hash key to compare against.
    ///
    /// \return true if the two hash key objects are the same.
    bool operator==(const isc::nsas::HashKey& other);

    const char* key;        ///< Pointer to the start of the key string
    uint32_t    keylen;     ///< Length of the key string
    isc::dns::RRClass class_code; ///< Class associated with the key
};

} // namespace nsas
} // namespace isc

#endif // HASH_KEY_H
