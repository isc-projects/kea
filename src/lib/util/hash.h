// Copyright (C) 2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef HASH_H
#define HASH_H

#include <cstddef>
#include <cstdint>
#include <string>

namespace isc {
namespace util {

/// @brief Hash implementation based on Fowler-Noll-Vo hash function
///
struct Hash64 {
    /// @brief Compute the hash
    ///
    /// FNV-1a hash function
    ///
    /// @param data data to hash
    /// @param length length of data
    /// @return the hash value
    static uint64_t hash(const uint8_t* data, size_t length) {
        uint64_t hash = FNV_offset_basis;
        for (size_t i = 0; i < length; ++i) {
            hash = hash ^ data[i];
            hash = hash * FNV_prime;
        }
        return (hash);
    }

    /// @brief Compute the hash
    ///
    /// FNV-1a hash function
    ///
    /// @param str not empty string to hash
    /// @return the hash value
    static uint64_t hash(const std::string& str) {
        return (hash(reinterpret_cast<const uint8_t*>(str.c_str()),
                     str.size()));
    }

    /// @brief Offset basis
    static const uint64_t FNV_offset_basis = 14695981039346656037ull;

    /// @brief Prime
    static const uint64_t FNV_prime = 1099511628211ull;
};

} // end of namespace isc::util
} // end of namespace isc

#endif
