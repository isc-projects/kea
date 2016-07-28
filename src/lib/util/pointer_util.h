// Copyright (C) 2015-2016 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef POINTER_UTIL_H
#define POINTER_UTIL_H

#include <exceptions/exceptions.h>
#include <string>

namespace isc {
namespace util {

template <typename T, typename E>
class RestrictedConstPtr {
public:

    RestrictedConstPtr(T* ptr, const std::string& error_text)
        : ptr_(ptr), const_only_(false), error_text_(error_text) {
    }

    void allowConstOnly(const bool const_only) {
        const_only_ = const_only;
    }

    T* operator->() const {
        return (ptr_);
    }

    T* operator->() {
        if (const_only_) {
            isc_throw(E, error_text_);
        }
        return (ptr_);
    }

    T* getPtr() const {
        return (ptr_);
    }

private:

    T* ptr_;

    bool const_only_;

    std::string error_text_;
};


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
