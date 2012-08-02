// Copyright (C) 2011  Internet Systems Consortium, Inc. ("ISC")
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

#ifndef __UTIL_UNITTESTS_NEWHOOK_H
#define __UTIL_UNITTESTS_NEWHOOK_H 1

/**
 * \file newhook.h
 * \brief Enable the use of special operator new that throws for testing.
 *
 * This small utility allows a test case to force the global operator new
 * to throw for a given size to test a case where memory allocation fails
 * (which normally doesn't happen).  To enable the feature, everything must
 * be built with defining ENABLE_CUSTOM_OPERATOR_NEW beforehand, and set
 * \c force_throw_on_new to \c true and \c throw_size_on_new to the size
 * of data that should trigger the exception, immediately before starting
 * the specific test that needs the exception.
 *
 * Example:
 * \code #include <util/unittests/newhook.h>
 * ...
 * TEST(SomeTest, newException) {
 *        isc::util::unittests::force_throw_on_new = true;
 *        isc::util::unittests::throw_size_on_new = sizeof(Foo);
 *        try {
 *            // this will do 'new Foo()' internally and should throw
 *            createFoo();
 *            isc::util::unittests::force_throw_on_new = false;
 *            ASSERT_FALSE(true) << "Expected throw on new";
 *        } catch (const std::bad_alloc&) {
 *            isc::util::unittests::force_throw_on_new = false;
 *            // do some integrity check, etc, if necessary
 *        }
 * } \endcode
 *
 * Replacing the global operator new (and delete) is a dangerous technique,
 * and triggering an exception solely based on the allocation size is not
 * reliable, so this feature is disabled by default two-fold: The
 * ENABLE_CUSTOM_OPERATOR_NEW build time variable, and run-time
 * \c force_throw_on_new.
 */

namespace isc {
namespace util {
namespace unittests {
/// Switch to enable the use of special operator new
///
/// This is set to \c false by default.
extern bool force_throw_on_new;

/// The allocation size that triggers an exception in the special operator new
///
/// This is the exact size that causes an exception to be thrown;
/// for example, if it is set to 100, an attempt of allocating 100 bytes
/// will result in an exception, but allocation attempt for 101 bytes won't
/// (unless, of course, memory is really exhausted and allocation really
/// fails).
///
/// The default value is 0.  The value of this variable has no meaning
/// unless the use of the special operator is enabled at build time and
/// via \c force_throw_on_new.
extern size_t throw_size_on_new;
}
}
}

#endif // __UTIL_UNITTESTS_NEWHOOK_H

// Local Variables:
// mode: c++
// End:
