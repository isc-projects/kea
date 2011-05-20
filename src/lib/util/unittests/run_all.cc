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

#include <stdlib.h>

#include <iostream>
#include <iomanip>

#include <gtest/gtest.h>
#include <exceptions/exceptions.h>
#include <util/unittests/run_all.h>

namespace isc {
namespace util {
namespace unittests {

int
run_all() {
    int ret = 0;

    if (getenv("B10TEST_CATCH_EXCEPTION") != NULL) {
        try {
            ret = RUN_ALL_TESTS();
        } catch (const isc::Exception& ex) {
            // Could output more information with typeid(), but there is no
            // guarantee that all compilers will support it without an explicit
            // flag on the command line.
            std::cerr << "*** Exception derived from isc::exception thrown:\n"
                      << "    file: " << ex.getFile() << "\n"
                      << "    line: " << ex.getLine() << "\n"
                      << "    what: " << ex.what() << std::endl;
            throw;
        } catch (const std::exception& ex) {
            std::cerr << "*** Exception derived from std::exception thrown:\n"
                      << "    what: " << ex.what() << std::endl;
            throw;
        }
    } else {
        // This is a separate path for the case where the exception is not
        // being caught.  Although the other code path re-throws the exception
        // after catching it, there is no guarantee that the state of the
        // stack is preserved - a compiler might have unwound the stack to
        // the point at which the exception is caught.  This would prove
        // awkward if trying to debug the program using a debugger.
        ret = RUN_ALL_TESTS();
    }

    return (ret);
}

} // namespace unittests
} // namespace util
} // namespace isc
