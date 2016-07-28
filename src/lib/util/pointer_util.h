// Copyright (C) 2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef POINTER_UTIL_H
#define POINTER_UTIL_H

namespace isc {
namespace util {

/// @brief This function checks if two pointers are non-null and values
/// are equal.
///
/// This function performs the typical comparison of values encapsulated by
/// the smart pointers, with checking if the pointers are non-null.
///
/// @param ptr1 First pointer.
/// @param ptr2 Second pointer.
///
/// @tparam T Pointer type, e.g. boost::shared_ptr, or boost::scoped_ptr.
///
/// @return true only if both pointers are non-null and the values which they
/// point to are equal.
template<typename T>
inline bool equalValues(const T& ptr1, const T& ptr2) {
    return (ptr1 && ptr2 && (*ptr1 == *ptr2));
}

/// @brief This function checks if two pointers are both null or both
/// are non-null and they point to equal values.
///
/// @param ptr1 First pointer.
/// @param ptr2 Second pointer.
///
/// @tparam T Pointer type, e.g. boost::shared_ptr, or boost::scoped_ptr.
///
/// @return true if both pointers are null or if they are both non-null
/// and the values pointed to are equal.
template<typename T>
inline bool nullOrEqualValues(const T& ptr1, const T& ptr2) {
    return ((!ptr1 && !ptr2) || equalValues(ptr1, ptr2));
}

} // end of namespace isc::util
} // end of namespace isc

#endif
