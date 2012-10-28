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

#ifndef HASH_H
#define HASH_H

#include <stdint.h>
#include <vector>

#include <exceptions/exceptions.h>

#include "hash_key.h"

namespace isc {
namespace nsas {

/// \brief Too Long Key Length
///
/// Thrown if the expected maximum key length is too long for the data types
/// declared in the class.
class KeyLengthTooLong : public isc::Exception {
public:
    KeyLengthTooLong(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what)
    {}
};


/// \brief Hash Calculation
///
/// Class abstracting the mechanics of the hash calculation.
class Hash {
public:

    /// \brief Constructor
    ///
    /// Constructs the hash table and initialises all data structures needed
    /// for the hashing.
    ///
    /// \param tablesize Size of the hash table.  For best performance, this
    /// should be a prime number.
    /// \param maxkeylen Maximum length (in bytes) of a key to be hashed.
    /// calculation will return a value between 0 and N-1.  The default
    /// value of 255 is the maximum size of a DNS name.
    /// \param randomise If true (the default), the pseudo-random number
    /// generator is seeded with the current time.  Otherwise it is initialised
    /// to a known sequence.  This is principally for unit tests, where a random
    /// sequence could lead to problems in checking results.
    Hash(uint32_t tablesize, uint32_t maxkeylen = 255, bool randomise = true);

    /// \brief Virtual Destructor
    virtual ~Hash()
    {}

    /// \brief Return Size
    ///
    /// \return The hash table size with which this object was initialized
    virtual uint32_t tableSize() const {
        return tablesize_;
    }

    /// \brief Return Key Length
    ///
    /// \return Maximum length of a key that this class can cope with.
    virtual uint32_t maxKeyLength() const {
        return maxkeylen_;
    }

    /// \brief Hash Value
    ///
    /// \param key Parameters comprising the key to be hashed.
    /// \param ignorecase true for case to be ignored when calculating the
    /// hash value, false for it to be taken into account.
    ///
    /// \return Hash value, a number between 0 and N-1.
    virtual uint32_t operator()(const HashKey& key, 
        bool ignorecase = true) const;

    /// \brief Map Lower Case to Upper Case
    ///
    /// Equivalent of tolower(), but using a table lookup instead of a
    /// function call.  This should make the mapping faster.
    ///
    /// \param inchar Input character
    ///
    /// \return Mapped character
    virtual unsigned char mapLower(unsigned char inchar) const {
        return casemap_[inchar];
    }

private:

    ///  \name Local Typedefs
    ///
    /// Typedefs for use in the code.  This makes it easier to compare the
    /// hashing code with that in BIND-9.
    //@{
    typedef uint32_t hash_accum_t;  ///< Accumulator
    typedef uint16_t hash_random_t; ///< Random number used in hash
    //@}

    uint32_t        tablesize_;     ///< Size of the hash table
    uint32_t        maxkeylen_;     ///< Maximum key length
    std::vector<unsigned char> casemap_; ///< Case mapping table
    std::vector<hash_random_t> randvec_; ///< Vector of random numbers

    static const uint32_t prime32_ = 0xfffffffb;    ///< 2^32 - 5
                                    ///< Specifies range of hash output
};

} // namspace nsas
} // namespace isc

#endif // HASH_H
