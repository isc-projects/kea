// Copyright (C) 2013, 2015  Internet Systems Consortium, Inc. ("ISC")
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

#ifndef POINTER_CONVERTER_H
#define POINTER_CONVERTER_H

#include <hooks/hooks.h>

namespace isc {
namespace hooks {

/// @brief Local class for conversion of void pointers to function pointers
///
/// Converting between void* and function pointers in C++ is fraught with
/// difficulty and pitfalls, e.g. see
/// https://groups.google.com/forum/?hl=en&fromgroups#!topic/comp.lang.c++/37o0l8rtEE0
///
/// The method given in that article - convert using a union is used here.  A
/// union is declared (and zeroed) and the appropriate member extracted when
/// needed.

class PointerConverter {
public:
    /// @brief Constructor
    ///
    /// Zeroes the union and stores the void* pointer we wish to convert (the
    /// one returned by dlsym).
    ///
    /// @param dlsym_ptr void* pointer returned by call to dlsym()
    explicit PointerConverter(void* dlsym_ptr) {
        memset(&pointers_, 0, sizeof(pointers_));
        pointers_.dlsym_ptr = dlsym_ptr;
    }

    /// @brief Constructor
    ///
    /// Zeroes the union and stores the CalloutPtr pointer we wish to convert.
    /// This constructor is used in debug messages; output of a pointer to
    /// an object (including to a function) is, on some compilers, printed as
    /// "1".
    ///
    /// @param callout_ptr Pointer to callout function
    explicit PointerConverter(CalloutPtr callout_ptr) {
        memset(&pointers_, 0, sizeof(pointers_));
        pointers_.callout_ptr = callout_ptr;
    }

    /// @name Pointer accessor functions
    ///
    /// It is up to the caller to ensure that the correct member is called so
    /// that the correct type of pointer is returned.
    ///
    ///@{

    /// @brief Return pointer returned by dlsym call
    ///
    /// @return void* pointer returned by the call to dlsym().  This can be
    ///         used in statements that print the hexadecimal value of the
    ///         symbol.
    void* dlsymPtr() const {
        return (pointers_.dlsym_ptr);
    }

    /// @brief Return pointer to callout function
    ///
    /// @return Pointer to the callout function
    CalloutPtr calloutPtr() const {
        return (pointers_.callout_ptr);
    }

    /// @brief Return pointer to load function
    ///
    /// @return Pointer to the load function
    load_function_ptr loadPtr() const {
        return (pointers_.load_ptr);
    }

    /// @brief Return pointer to unload function
    ///
    /// @return Pointer to the unload function
    unload_function_ptr unloadPtr() const {
        return (pointers_.unload_ptr);
    }

    /// @brief Return pointer to version function
    ///
    /// @return Pointer to the version function
    version_function_ptr versionPtr() const {
        return (pointers_.version_ptr);
    }

    ///@}

private:

    /// @brief Union linking void* and pointers to functions.
    union {
        void*                   dlsym_ptr;      // void* returned by dlsym
        CalloutPtr              callout_ptr;    // Pointer to callout
        load_function_ptr       load_ptr;       // Pointer to load function
        unload_function_ptr     unload_ptr;     // Pointer to unload function
        version_function_ptr    version_ptr;    // Pointer to version function
    } pointers_;
};

} // namespace hooks
} // namespace isc


#endif // POINTER_CONVERTER_H
