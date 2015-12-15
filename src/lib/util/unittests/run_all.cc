// Copyright (C) 2011  Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

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

    // The catching of exceptions generated in tests is controlled by the
    // KEATEST_CATCH_EXCEPTION environment variable.  Setting this to
    // 1 enables the catching of exceptions; setting it to 0 disables it.
    // Anything else causes a message to be printed to stderr and the default
    // taken.  (The default is to catch exceptions if compiling with clang
    // and false if not.)
#ifdef __clang__
    bool catch_exception = true;
#else
    bool catch_exception = false;
#endif

    const char* keatest_catch_exception = getenv("KEATEST_CATCH_EXCEPTION");
    if (keatest_catch_exception != NULL) {
        if (strcmp(keatest_catch_exception, "1") == 0) {
            catch_exception = true;
        } else if (strcmp(keatest_catch_exception, "0") == 0) {
            catch_exception = false;
        } else {
            std::cerr << "***ERROR: KEATEST_CATCH_EXCEPTION is '"
                         << keatest_catch_exception
                         << "': allowed values are '1' or '0'.\n"
                      << "          The default value of "
                         << (catch_exception ?
                                "1 (exception catching enabled)":
                                "0 (exception catching disabled)")
                         << " will be used.\n";
        }
    }

    // Actually run the code
    if (catch_exception) {
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
