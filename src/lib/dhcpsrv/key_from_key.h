// Copyright (C) 2013 Internet Systems Consortium, Inc. ("ISC")
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

#ifndef KEY_FROM_KEY_H
#define KEY_FROM_KEY_H

#include <functional>

namespace isc {
namespace dhcp {

/// @brief Extractor class to extract key with another key.
///
/// This class solves the problem whereby the multi_index_container
/// must access the values stored in object nested in other object.
/// Assume that there is a multi_index_container that holds objects
/// of the type A. Each object A contains the member object B.
/// Each object B holds the member of the type C that is to be used
/// for indexing objects A. Objects C can't be accessed directly
/// from the object A as they are nested in the object B. In such case
/// there is no easy way to point in the definition of the container
/// that C should be used for indexing objects. The KeyFromKey class
/// represents the cascaded key which can be used to extract the nested
/// key value C from the object B.
/// For some more examples of complex keys see:
/// http://www.cs.brown.edu/~jwicks/boost/libs/multi_index/doc/index.html
///
/// @tparam KeyExtractor1 extractor used to access the object used as
/// a key from the other object that holds it.
/// @tparam KeyExtractor2 extractor used to access data in the object
/// holding nested object used as a key.
template<typename KeyExtractor1, typename KeyExtractor2>
class KeyFromKey {
public:
    typedef typename KeyExtractor1::result_type result_type;

    /// @brief Constructor.
    KeyFromKey()
        : key1_(KeyExtractor1()), key2_(KeyExtractor2()) { };

    /// @brief Extract key with another key.
    ///
    /// @param arg the key value.
    ///
    /// @tparam key value type.
    template<typename T>
    result_type operator() (T& arg) const {
        return (key1_(key2_(arg)));
    }
private:
    KeyExtractor1 key1_; ///< key 1.
    KeyExtractor2 key2_; ///< key 2.
};

} // end of isc::dhcp namespace
} // end of isc namespace

#endif // KEY_FROM_KEY_H
