// Copyright (C) 2013-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef KEY_FROM_KEY_H
#define KEY_FROM_KEY_H

#include <functional>

namespace isc {
namespace dhcp {

/// @brief Utility class which cascades two key extractors.
///
/// The key extractor (a.k.a. key extraction class) is used by the
/// key-based indices to obtain the indexing keys from the elements of
/// a multi_index_container. The standard key extractors can be used
/// to retrieve indexing key values by accessing members or methods
/// exposed by the elements (objects or structures) stored in a
/// multi_index_container. For example, if a container holds objects
/// of type A, then the public members of object A or its accessors can
/// be used by the standard extractor classes such as "member" or
/// "const_mem_fun" respectively. Assume more complex scenario, where
/// multi_index_container holds objects of a type A, object A exposes
/// its public member B, which in turn exposes the accessor function
/// returning object C. One may want to use the value C (e.g. integer)
/// to index objects A in the container. This can't be solved by using
/// standard key extractors because object C is nested in B and thus
/// it is not directly accessible from A. However, it is possible
/// to specify two distinct key extractors, one used to extract value
/// C from B, another one to extract value B from A. These two extractors
/// can be then wrapped by another key extractor which can be used
/// to obtain index key C from object A. This key extractor is implemented
/// as a functor class. The functor calls functors specified as
/// template parameters to retrieve the index value from the cascaded
/// structure.
///
/// @tparam KeyExtractor1 extractor used to extract the key value from
/// the object containing it.
/// @tparam KeyExtractor2 extractor used to extract the nested object
/// containing a key.
template<typename KeyExtractor1, typename KeyExtractor2>
class KeyFromKeyExtractor {
public:
    typedef typename KeyExtractor1::result_type result_type;

    /// @brief Constructor.
    KeyFromKeyExtractor()
        : key1_(KeyExtractor1()), key2_(KeyExtractor2()) { };

    /// @brief Extract key value from the object hierarchy.
    ///
    /// @param arg the key value.
    ///
    /// @tparam key value type.
    template<typename T>
    result_type operator() (T& arg) const {
        return (key1_(key2_(arg)));
    }
private:
    /// Key Extractor used to extract the key value from the
    /// object containing it.
    KeyExtractor1 key1_;
    /// Key Extractor used to extract the nested object
    /// containing a key.
    KeyExtractor2 key2_;
};

} // end of isc::dhcp namespace
} // end of isc namespace

#endif // KEY_FROM_KEY_H
