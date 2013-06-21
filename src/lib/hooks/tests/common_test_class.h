// Copyright (C) 2013  Internet Systems Consortium, Inc. ("ISC")
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

#ifndef COMMON_HOOKS_TEST_CLASS_H
#define COMMON_HOOKS_TEST_CLASS_H

#include <hooks/callout_handle.h>
#include <hooks/callout_manager.h>
#include <hooks/server_hooks.h>
#include <hooks/tests/marker_file.h>

#include <boost/shared_ptr.hpp>
#include <gtest/gtest.h>

/// @brief Common hooks test class
///
/// This class is a shared parent of the test fixture class in the tests of the
/// higher-level hooks classes (LibraryManager, LibraryManagerCollection and
/// HooksManager).  It
///
/// - sets the the ServerHooks object with three hooks and stores their
///   indexes.
/// - executes the callouts (which are assumed to perform a calculation)
///   and checks the results.

class HooksCommonTestClass {
public:
    /// @brief Constructor
    HooksCommonTestClass() {

        // Set up the server hooks.  ServerHooks is a singleton, so we reset it
        // between each test.
        isc::hooks::ServerHooks& hooks =
            isc::hooks::ServerHooks::getServerHooks();
        hooks.reset();
        lm_one_index_ = hooks.registerHook("lm_one");
        lm_two_index_ = hooks.registerHook("lm_two");
        lm_three_index_ = hooks.registerHook("lm_three");
    }

    /// @brief Call callouts test
    ///
    /// All of the loaded libraries for which callouts are called register four
    /// callouts: a context_create callout and three callouts that are attached
    /// to hooks lm_one, lm_two and lm_three.  These four callouts, executed
    /// in sequence, perform a series of calculations. Data is passed between
    /// callouts in the argument list, in a variable named "result".
    ///
    /// context_create initializes the calculation by setting a seed
    /// value, called r0 here.  This value is dependent on the library being
    /// loaded.  Prior to that, the argument "result" is initialized to -1,
    /// the purpose being to avoid exceptions when running this test with no
    /// libraries loaded.
    ///
    /// Callout lm_one is passed a value d1 and performs a simple arithmetic
    /// operation on it and r0 yielding a result r1.  Hence we can say that
    /// @f[ r1 = lm1(r0, d1) @f]
    ///
    /// Callout lm_two is passed a value d2 and peforms another simple
    /// arithmetic operation on it and d2, yielding r2, i.e.
    /// @f[ r2 = lm2(d1, d2) @f]
    ///
    /// lm_three does a similar operation giving @f[ r3 = lm3(r2, d3) @f].
    ///
    /// The details of the operations lm1, lm2 and lm3 depend on the library.
    /// However the sequence of calls needed to do this set of calculations
    /// is identical regardless of the exact functions. This method performs
    /// those operations and checks the results of each step.
    ///
    /// It is assumed that callout_manager_ has been set up appropriately.
    ///
    /// @note The CalloutHandle used in the calls is declared locally here.
    ///       The advantage of this (apart from scope reduction) is that on
    ///       exit, it is destroyed.  This removes any references to memory
    ///       allocated by loaded libraries while they are still loaded.
    ///
    /// @param manager CalloutManager to use for the test
    /// @param r0...r3, d1..d3 Values and intermediate values expected.  They
    ///        are ordered so that the variables appear in the argument list in
    ///        the order they are used.
    void executeCallCallouts(
            const boost::shared_ptr<isc::hooks::CalloutManager>& manager,
            int r0, int d1, int r1, int d2, int r2, int d3, int r3) {
        static const char* COMMON_TEXT = " callout returned the wong value";
        static const char* RESULT = "result";

        int result;

        // Set up a callout handle for the calls.
        isc::hooks::CalloutHandle handle(manager);

        // Initialize the argument RESULT.  This simplifies testing by
        // eliminating the generation of an exception when we try the unload
        // test.  In that case, RESULT is unchanged.
        handle.setArgument(RESULT, -1);

        // Seed the calculation.
        manager->callCallouts(isc::hooks::ServerHooks::CONTEXT_CREATE, handle);
        handle.getArgument(RESULT, result);
        EXPECT_EQ(r0, result) << "context_create" << COMMON_TEXT;

        // Perform the first calculation.
        handle.setArgument("data_1", d1);
        manager->callCallouts(lm_one_index_, handle);
        handle.getArgument(RESULT, result);
        EXPECT_EQ(r1, result) << "lm_one" << COMMON_TEXT;

        // ... the second ...
        handle.setArgument("data_2", d2);
        manager->callCallouts(lm_two_index_, handle);
        handle.getArgument(RESULT, result);
        EXPECT_EQ(r2, result) << "lm_two" << COMMON_TEXT;

        // ... and the third.
        handle.setArgument("data_3", d3);
        manager->callCallouts(lm_three_index_, handle);
        handle.getArgument(RESULT, result);
        EXPECT_EQ(r3, result) << "lm_three" << COMMON_TEXT;
    }

    /// Hook indexes.  These are are made public for ease of reference.
    int lm_one_index_;
    int lm_two_index_;
    int lm_three_index_;
};

#endif // COMMON_HOOKS_TEST_CLASS_H
