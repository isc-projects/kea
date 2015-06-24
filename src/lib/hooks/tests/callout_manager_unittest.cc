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

#include <exceptions/exceptions.h>
#include <hooks/callout_handle.h>
#include <hooks/callout_manager.h>
#include <hooks/library_handle.h>
#include <hooks/server_hooks.h>

#include <boost/scoped_ptr.hpp>
#include <gtest/gtest.h>

#include <algorithm>
#include <climits>
#include <string>
#include <vector>

/// @file
/// @brief CalloutManager and LibraryHandle tests
///
/// These set of tests check the CalloutManager and LibraryHandle.  They are
/// together in the same file because the LibraryHandle is little more than a
/// restricted interface to the CalloutManager, and a lot of the support
/// structure for the tests is common.

using namespace isc;
using namespace isc::hooks;
using namespace std;

namespace {

class CalloutManagerTest : public ::testing::Test {
public:
    /// @brief Constructor
    ///
    /// Sets up a collection of three LibraryHandle objects to use in the test.
    CalloutManagerTest() {

        // Set up the server hooks.  There is one singleton for all tests,
        // so reset it and explicitly set up the hooks for the test.
        ServerHooks& hooks = ServerHooks::getServerHooks();
        hooks.reset();
        alpha_index_ = hooks.registerHook("alpha");
        beta_index_ = hooks.registerHook("beta");
        gamma_index_ = hooks.registerHook("gamma");
        delta_index_ = hooks.registerHook("delta");

        // Set up the callout manager with these hooks.  Assume a maximum of
        // four libraries.
        callout_manager_.reset(new CalloutManager(10));

        // Set up the callout handle.
        callout_handle_.reset(new CalloutHandle(callout_manager_));

        // Initialize the static variable.
        callout_value_ = 0;
    }

    /// @brief Return the callout handle
    CalloutHandle& getCalloutHandle() {
        return (*callout_handle_);
    }

    /// @brief Return the callout manager
    boost::shared_ptr<CalloutManager> getCalloutManager() {
        return (callout_manager_);
    }

    /// Static variable used for accumulating information
    static int callout_value_;

    /// Hook indexes.  These are somewhat ubiquitous, so are made public for
    /// ease of reference instead of being accessible by a function.
    int alpha_index_;
    int beta_index_;
    int gamma_index_;
    int delta_index_;

private:
    /// Callout handle used in calls
    boost::shared_ptr<CalloutHandle> callout_handle_;

    /// Callout manager used for the test
    boost::shared_ptr<CalloutManager> callout_manager_;
};

// Definition of the static variable.
int CalloutManagerTest::callout_value_ = 0;

// Callout definitions
//
// The callouts defined here are structured in such a way that it is possible
// to determine the order in which they are called and whether they are called
// at all. The method used is simple - after a sequence of callouts, the digits
// in the value, reading left to right, determines the order of the callouts
// called.  For example, callout one followed by two followed by three followed
// by two followed by one results in a value of 12321.
//
// Functions return a zero to indicate success.

extern "C" {
int callout_general(int number) {
    CalloutManagerTest::callout_value_ =
        10 * CalloutManagerTest::callout_value_ + number;
    return (0);
}

int callout_one(CalloutHandle&) {
    return (callout_general(1));
}

int callout_two(CalloutHandle&) {
    return (callout_general(2));
}

int callout_three(CalloutHandle&) {
    return (callout_general(3));
}

int callout_four(CalloutHandle&) {
    return (callout_general(4));
}

int callout_five(CalloutHandle&) {
    return (callout_general(5));
}

int callout_six(CalloutHandle&) {
    return (callout_general(6));
}

int callout_seven(CalloutHandle&) {
    return (callout_general(7));
}

// The next functions are duplicates of some of the above, but return an error.

int callout_one_error(CalloutHandle& handle) {
    (void) callout_one(handle);
    return (1);
}

int callout_two_error(CalloutHandle& handle) {
    (void) callout_two(handle);
    return (1);
}

int callout_three_error(CalloutHandle& handle) {
    (void) callout_three(handle);
    return (1);
}

int callout_four_error(CalloutHandle& handle) {
    (void) callout_four(handle);
    return (1);
}

};  // extern "C"

// *** Callout Tests ***
//
// The next set of tests check that callouts can be called.

// Constructor - check that we trap bad parameters.

TEST_F(CalloutManagerTest, BadConstructorParameters) {
    boost::scoped_ptr<CalloutManager> cm;

    // Invalid number of libraries
    EXPECT_THROW(cm.reset(new CalloutManager(-1)), BadValue);
}

// Check the number of libraries is reported successfully.

TEST_F(CalloutManagerTest, NumberOfLibraries) {
    boost::scoped_ptr<CalloutManager> cm;

    // Check two valid values of number of libraries to ensure that the
    // GetNumLibraries() returns the value set.
    EXPECT_NO_THROW(cm.reset(new CalloutManager()));
    EXPECT_EQ(0, cm->getNumLibraries());

    EXPECT_NO_THROW(cm.reset(new CalloutManager(0)));
    EXPECT_EQ(0, cm->getNumLibraries());

    EXPECT_NO_THROW(cm.reset(new CalloutManager(4)));
    EXPECT_EQ(4, cm->getNumLibraries());

    EXPECT_NO_THROW(cm.reset(new CalloutManager(42)));
    EXPECT_EQ(42, cm->getNumLibraries());
}

// Check that we can only set the current library index to the correct values.

TEST_F(CalloutManagerTest, CheckLibraryIndex) {
    // Check valid indexes.  As the callout manager is sized for 10 libraries,
    // we expect:
    //
    // -1 to be valid as it is the standard "invalid" value.
    // 0 to be valid for the pre-user library callouts
    // 1-10 to be valid for the user-library callouts
    // INT_MAX to be valid for the post-user library callouts
    //
    // All other values to be invalid.
    for (int i = -1; i < 11; ++i) {
        EXPECT_NO_THROW(getCalloutManager()->setLibraryIndex(i));
        EXPECT_EQ(i, getCalloutManager()->getLibraryIndex());
    }
    EXPECT_NO_THROW(getCalloutManager()->setLibraryIndex(INT_MAX));
    EXPECT_EQ(INT_MAX, getCalloutManager()->getLibraryIndex());

    // Check invalid ones
    EXPECT_THROW(getCalloutManager()->setLibraryIndex(-2), NoSuchLibrary);
    EXPECT_THROW(getCalloutManager()->setLibraryIndex(11), NoSuchLibrary);
}

// Check that we can only register callouts on valid hook names.

TEST_F(CalloutManagerTest, ValidHookNames) {
    getCalloutManager()->setLibraryIndex(0);
    EXPECT_NO_THROW(getCalloutManager()->registerCallout("alpha", callout_one));
    EXPECT_THROW(getCalloutManager()->registerCallout("unknown", callout_one),
                                                      NoSuchHook);
}


// Check we can register callouts appropriately.

TEST_F(CalloutManagerTest, RegisterCallout) {
    // Ensure that no callouts are attached to any of the hooks.
    EXPECT_FALSE(getCalloutManager()->calloutsPresent(alpha_index_));
    EXPECT_FALSE(getCalloutManager()->calloutsPresent(beta_index_));

    // Set up so that hooks "alpha" and "beta" have callouts attached from a
    // different libraries.
    getCalloutManager()->setLibraryIndex(0);
    getCalloutManager()->registerCallout("alpha", callout_one);
    getCalloutManager()->setLibraryIndex(1);
    getCalloutManager()->registerCallout("beta", callout_two);

    // Check all is as expected.
    EXPECT_TRUE(getCalloutManager()->calloutsPresent(alpha_index_));
    EXPECT_TRUE(getCalloutManager()->calloutsPresent(beta_index_));
    EXPECT_FALSE(getCalloutManager()->calloutsPresent(gamma_index_));
    EXPECT_FALSE(getCalloutManager()->calloutsPresent(delta_index_));

    // Check that calling the callouts returns as expected. (This is also a
    // test of the callCallouts method.)
    callout_value_ = 0;
    getCalloutManager()->callCallouts(alpha_index_, getCalloutHandle());
    EXPECT_EQ(1, callout_value_);

    callout_value_ = 0;
    getCalloutManager()->callCallouts(beta_index_, getCalloutHandle());
    EXPECT_EQ(2, callout_value_);

    // Register some more callouts from different libraries on hook "alpha".
    getCalloutManager()->setLibraryIndex(2);
    getCalloutManager()->registerCallout("alpha", callout_three);
    getCalloutManager()->registerCallout("alpha", callout_four);
    getCalloutManager()->setLibraryIndex(3);
    getCalloutManager()->registerCallout("alpha", callout_five);

    // Check it is as expected.
    callout_value_ = 0;
    getCalloutManager()->callCallouts(alpha_index_, getCalloutHandle());
    EXPECT_EQ(1345, callout_value_);

    // ... and check the additional callouts were not registered on the "beta"
    // hook.
    callout_value_ = 0;
    getCalloutManager()->callCallouts(beta_index_, getCalloutHandle());
    EXPECT_EQ(2, callout_value_);

    // Add another callout to hook "alpha" from library index 2 - this should
    // appear at the end of the callout list for that library.
    getCalloutManager()->setLibraryIndex(2);
    getCalloutManager()->registerCallout("alpha", callout_six);
    callout_value_ = 0;
    getCalloutManager()->callCallouts(alpha_index_, getCalloutHandle());
    EXPECT_EQ(13465, callout_value_);

    // Add a callout from library index 1 - this should appear between the
    // callouts from library index 0 and library index 2.
    getCalloutManager()->setLibraryIndex(1);
    getCalloutManager()->registerCallout("alpha", callout_seven);
    callout_value_ = 0;
    getCalloutManager()->callCallouts(alpha_index_, getCalloutHandle());
    EXPECT_EQ(173465, callout_value_);
}

// Check the "calloutsPresent()" method.

TEST_F(CalloutManagerTest, CalloutsPresent) {
    // Ensure that no callouts are attached to any of the hooks.
    EXPECT_FALSE(getCalloutManager()->calloutsPresent(alpha_index_));
    EXPECT_FALSE(getCalloutManager()->calloutsPresent(beta_index_));
    EXPECT_FALSE(getCalloutManager()->calloutsPresent(gamma_index_));
    EXPECT_FALSE(getCalloutManager()->calloutsPresent(delta_index_));

    // Set up so that hooks "alpha", "beta" and "delta" have callouts attached
    // to them, and callout  "gamma" does not. (In the statements below, the
    // exact callouts attached to a hook are not relevant - only the fact
    // that some callouts are).  Chose the libraries for which the callouts
    // are registered randomly.
    getCalloutManager()->setLibraryIndex(0);
    getCalloutManager()->registerCallout("alpha", callout_one);

    getCalloutManager()->setLibraryIndex(1);
    getCalloutManager()->registerCallout("alpha", callout_two);
    getCalloutManager()->registerCallout("beta", callout_two);

    getCalloutManager()->setLibraryIndex(3);
    getCalloutManager()->registerCallout("alpha", callout_three);
    getCalloutManager()->registerCallout("delta", callout_four);

    // Check all is as expected.
    EXPECT_TRUE(getCalloutManager()->calloutsPresent(alpha_index_));
    EXPECT_TRUE(getCalloutManager()->calloutsPresent(beta_index_));
    EXPECT_FALSE(getCalloutManager()->calloutsPresent(gamma_index_));
    EXPECT_TRUE(getCalloutManager()->calloutsPresent(delta_index_));

    // Check we fail on an invalid hook index.
    EXPECT_THROW(getCalloutManager()->calloutsPresent(42), NoSuchHook);
    EXPECT_THROW(getCalloutManager()->calloutsPresent(-1), NoSuchHook);
}

// Test that calling a hook with no callouts on it returns success.

TEST_F(CalloutManagerTest, CallNoCallouts) {
    // Ensure that no callouts are attached to any of the hooks.
    EXPECT_FALSE(getCalloutManager()->calloutsPresent(alpha_index_));
    EXPECT_FALSE(getCalloutManager()->calloutsPresent(beta_index_));
    EXPECT_FALSE(getCalloutManager()->calloutsPresent(gamma_index_));
    EXPECT_FALSE(getCalloutManager()->calloutsPresent(delta_index_));

    // Call the callouts on an arbitrary hook and ensure that nothing happens.
    callout_value_ = 475;
    getCalloutManager()->callCallouts(alpha_index_, getCalloutHandle());
    EXPECT_EQ(475, callout_value_); // Unchanged
}

// Test that the callouts are called in the correct order (i.e. the callouts
// from the first library in the order they were registered, then the callouts
// from the second library in the order they were registered etc.)

TEST_F(CalloutManagerTest, CallCalloutsSuccess) {
    // Ensure that no callouts are attached to any of the hooks.
    EXPECT_FALSE(getCalloutManager()->calloutsPresent(alpha_index_));
    EXPECT_FALSE(getCalloutManager()->calloutsPresent(beta_index_));
    EXPECT_FALSE(getCalloutManager()->calloutsPresent(gamma_index_));
    EXPECT_FALSE(getCalloutManager()->calloutsPresent(delta_index_));

    // Each library contributes one callout on hook "alpha".
    callout_value_ = 0;
    getCalloutManager()->setLibraryIndex(1);
    getCalloutManager()->registerCallout("alpha", callout_one);
    getCalloutManager()->setLibraryIndex(1);
    getCalloutManager()->registerCallout("alpha", callout_two);
    getCalloutManager()->setLibraryIndex(2);
    getCalloutManager()->registerCallout("alpha", callout_three);
    getCalloutManager()->setLibraryIndex(3);
    getCalloutManager()->registerCallout("alpha", callout_four);
    getCalloutManager()->callCallouts(alpha_index_, getCalloutHandle());
    EXPECT_EQ(1234, callout_value_);

    // Do a random selection of callouts on hook "beta".
    callout_value_ = 0;
    getCalloutManager()->setLibraryIndex(0);
    getCalloutManager()->registerCallout("beta", callout_one);
    getCalloutManager()->registerCallout("beta", callout_three);
    getCalloutManager()->setLibraryIndex(1);
    getCalloutManager()->registerCallout("beta", callout_two);
    getCalloutManager()->setLibraryIndex(3);
    getCalloutManager()->registerCallout("beta", callout_four);
    getCalloutManager()->callCallouts(beta_index_, getCalloutHandle());
    EXPECT_EQ(1324, callout_value_);

    // Ensure that calling the callouts on a hook with no callouts works.
    callout_value_ = 0;
    getCalloutManager()->callCallouts(gamma_index_, getCalloutHandle());
    EXPECT_EQ(0, callout_value_);
}

// Test that the callouts are called in order, but that callouts occurring
// after a callout that returns an error are not called.
//
// (Note: in this test, the callouts that return an error set the value of
// callout_value_ before they return the error code.)

TEST_F(CalloutManagerTest, CallCalloutsError) {
    // Ensure that no callouts are attached to any of the hooks.
    EXPECT_FALSE(getCalloutManager()->calloutsPresent(alpha_index_));
    EXPECT_FALSE(getCalloutManager()->calloutsPresent(beta_index_));
    EXPECT_FALSE(getCalloutManager()->calloutsPresent(gamma_index_));
    EXPECT_FALSE(getCalloutManager()->calloutsPresent(delta_index_));

    // Each library contributing one callout on hook "alpha". The first callout
    // returns an error (after adding its value to the result).
    callout_value_ = 0;
    getCalloutManager()->setLibraryIndex(0);
    getCalloutManager()->registerCallout("alpha", callout_one_error);
    getCalloutManager()->setLibraryIndex(1);
    getCalloutManager()->registerCallout("alpha", callout_two);
    getCalloutManager()->setLibraryIndex(2);
    getCalloutManager()->registerCallout("alpha", callout_three);
    getCalloutManager()->setLibraryIndex(3);
    getCalloutManager()->registerCallout("alpha", callout_four);
    getCalloutManager()->callCallouts(alpha_index_, getCalloutHandle());
    EXPECT_EQ(1234, callout_value_);

    // Each library contributing multiple callouts on hook "beta". The last
    // callout on the first library returns an error.
    callout_value_ = 0;
    getCalloutManager()->setLibraryIndex(0);
    getCalloutManager()->registerCallout("beta", callout_one);
    getCalloutManager()->registerCallout("beta", callout_one_error);
    getCalloutManager()->setLibraryIndex(1);
    getCalloutManager()->registerCallout("beta", callout_two);
    getCalloutManager()->registerCallout("beta", callout_two);
    getCalloutManager()->registerCallout("beta", callout_three);
    getCalloutManager()->registerCallout("beta", callout_three);
    getCalloutManager()->setLibraryIndex(3);
    getCalloutManager()->registerCallout("beta", callout_four);
    getCalloutManager()->registerCallout("beta", callout_four);
    getCalloutManager()->callCallouts(beta_index_, getCalloutHandle());
    EXPECT_EQ(11223344, callout_value_);

    // A callout in a random position in the callout list returns an error.
    callout_value_ = 0;
    getCalloutManager()->setLibraryIndex(0);
    getCalloutManager()->registerCallout("gamma", callout_one);
    getCalloutManager()->registerCallout("gamma", callout_one);
    getCalloutManager()->setLibraryIndex(1);
    getCalloutManager()->registerCallout("gamma", callout_two);
    getCalloutManager()->registerCallout("gamma", callout_two);
    getCalloutManager()->setLibraryIndex(3);
    getCalloutManager()->registerCallout("gamma", callout_four_error);
    getCalloutManager()->registerCallout("gamma", callout_four);
    getCalloutManager()->callCallouts(gamma_index_, getCalloutHandle());
    EXPECT_EQ(112244, callout_value_);

    // The last callout on a hook returns an error.
    callout_value_ = 0;
    getCalloutManager()->setLibraryIndex(0);
    getCalloutManager()->registerCallout("delta", callout_one);
    getCalloutManager()->registerCallout("delta", callout_one);
    getCalloutManager()->setLibraryIndex(1);
    getCalloutManager()->registerCallout("delta", callout_two);
    getCalloutManager()->registerCallout("delta", callout_two);
    getCalloutManager()->setLibraryIndex(2);
    getCalloutManager()->registerCallout("delta", callout_three);
    getCalloutManager()->registerCallout("delta", callout_three);
    getCalloutManager()->setLibraryIndex(3);
    getCalloutManager()->registerCallout("delta", callout_four);
    getCalloutManager()->registerCallout("delta", callout_four_error);
    getCalloutManager()->callCallouts(delta_index_, getCalloutHandle());
    EXPECT_EQ(11223344, callout_value_);
}

// Now test that we can deregister a single callout on a hook.

TEST_F(CalloutManagerTest, DeregisterSingleCallout) {
    // Ensure that no callouts are attached to any of the hooks.
    EXPECT_FALSE(getCalloutManager()->calloutsPresent(alpha_index_));
    EXPECT_FALSE(getCalloutManager()->calloutsPresent(beta_index_));
    EXPECT_FALSE(getCalloutManager()->calloutsPresent(gamma_index_));
    EXPECT_FALSE(getCalloutManager()->calloutsPresent(delta_index_));

    // Add a callout to hook "alpha" and check it is added correctly.
    callout_value_ = 0;
    getCalloutManager()->setLibraryIndex(0);
    getCalloutManager()->registerCallout("alpha", callout_two);
    getCalloutManager()->callCallouts(alpha_index_, getCalloutHandle());
    EXPECT_EQ(2, callout_value_);

    // Remove it and check that the no callouts are present.  We have to reset
    // the current library index here as it was invalidated by the call
    // to callCallouts().
    getCalloutManager()->setLibraryIndex(0);
    EXPECT_TRUE(getCalloutManager()->calloutsPresent(alpha_index_));
    EXPECT_TRUE(getCalloutManager()->deregisterCallout("alpha", callout_two));
    EXPECT_FALSE(getCalloutManager()->calloutsPresent(alpha_index_));
}

// Now test that we can deregister a single callout on a hook that has multiple
// callouts from the same library.

TEST_F(CalloutManagerTest, DeregisterSingleCalloutSameLibrary) {
    // Ensure that no callouts are attached to any of the hooks.
    EXPECT_FALSE(getCalloutManager()->calloutsPresent(alpha_index_));
    EXPECT_FALSE(getCalloutManager()->calloutsPresent(beta_index_));
    EXPECT_FALSE(getCalloutManager()->calloutsPresent(gamma_index_));
    EXPECT_FALSE(getCalloutManager()->calloutsPresent(delta_index_));

    // Add multiple callouts to hook "alpha".
    callout_value_ = 0;
    getCalloutManager()->setLibraryIndex(0);
    getCalloutManager()->registerCallout("alpha", callout_one);
    getCalloutManager()->registerCallout("alpha", callout_two);
    getCalloutManager()->registerCallout("alpha", callout_three);
    getCalloutManager()->registerCallout("alpha", callout_four);
    getCalloutManager()->callCallouts(alpha_index_, getCalloutHandle());
    EXPECT_EQ(1234, callout_value_);

    // Remove the callout_two callout.  We have to reset the current library
    // index here as it was invalidated by the call to callCallouts().
    getCalloutManager()->setLibraryIndex(0);
    EXPECT_TRUE(getCalloutManager()->deregisterCallout("alpha", callout_two));
    callout_value_ = 0;
    getCalloutManager()->callCallouts(alpha_index_, getCalloutHandle());
    EXPECT_EQ(134, callout_value_);

    // Try removing it again.
    getCalloutManager()->setLibraryIndex(0);
    EXPECT_FALSE(getCalloutManager()->deregisterCallout("alpha", callout_two));
    callout_value_ = 0;
    getCalloutManager()->callCallouts(alpha_index_, getCalloutHandle());
    EXPECT_EQ(134, callout_value_);

}

// Check we can deregister multiple callouts from the same library.

TEST_F(CalloutManagerTest, DeregisterMultipleCalloutsSameLibrary) {
    // Ensure that no callouts are attached to any of the hooks.
    EXPECT_FALSE(getCalloutManager()->calloutsPresent(alpha_index_));
    EXPECT_FALSE(getCalloutManager()->calloutsPresent(beta_index_));
    EXPECT_FALSE(getCalloutManager()->calloutsPresent(gamma_index_));
    EXPECT_FALSE(getCalloutManager()->calloutsPresent(delta_index_));

    // Each library contributes one callout on hook "alpha".
    callout_value_ = 0;
    getCalloutManager()->setLibraryIndex(0);
    getCalloutManager()->registerCallout("alpha", callout_one);
    getCalloutManager()->registerCallout("alpha", callout_two);
    getCalloutManager()->registerCallout("alpha", callout_one);
    getCalloutManager()->registerCallout("alpha", callout_two);
    getCalloutManager()->registerCallout("alpha", callout_three);
    getCalloutManager()->registerCallout("alpha", callout_four);
    getCalloutManager()->registerCallout("alpha", callout_three);
    getCalloutManager()->registerCallout("alpha", callout_four);
    getCalloutManager()->callCallouts(alpha_index_, getCalloutHandle());
    EXPECT_EQ(12123434, callout_value_);

    // Remove the callout_two callouts.  We have to reset the current library
    // index here as it was invalidated by the call to callCallouts().
    getCalloutManager()->setLibraryIndex(0);
    EXPECT_TRUE(getCalloutManager()->deregisterCallout("alpha", callout_two));
    callout_value_ = 0;
    getCalloutManager()->callCallouts(alpha_index_, getCalloutHandle());
    EXPECT_EQ(113434, callout_value_);

    // Try removing multiple callouts that includes one at the end of the
    // list of callouts.
    getCalloutManager()->setLibraryIndex(0);
    EXPECT_TRUE(getCalloutManager()->deregisterCallout("alpha", callout_four));
    callout_value_ = 0;
    getCalloutManager()->callCallouts(alpha_index_, getCalloutHandle());
    EXPECT_EQ(1133, callout_value_);

    // ... and from the start.
    getCalloutManager()->setLibraryIndex(0);
    EXPECT_TRUE(getCalloutManager()->deregisterCallout("alpha", callout_one));
    callout_value_ = 0;
    getCalloutManager()->callCallouts(alpha_index_, getCalloutHandle());
    EXPECT_EQ(33, callout_value_);

    // ... and the remaining callouts.
    getCalloutManager()->setLibraryIndex(0);
    EXPECT_TRUE(getCalloutManager()->deregisterCallout("alpha", callout_three));
    callout_value_ = 0;
    getCalloutManager()->callCallouts(alpha_index_, getCalloutHandle());
    EXPECT_EQ(0, callout_value_);

    EXPECT_FALSE(getCalloutManager()->calloutsPresent(alpha_index_));
}

// Check we can deregister multiple callouts from multiple libraries.

TEST_F(CalloutManagerTest, DeregisterMultipleCalloutsMultipleLibraries) {
    // Ensure that no callouts are attached to any of the hooks.
    EXPECT_FALSE(getCalloutManager()->calloutsPresent(alpha_index_));
    EXPECT_FALSE(getCalloutManager()->calloutsPresent(beta_index_));
    EXPECT_FALSE(getCalloutManager()->calloutsPresent(gamma_index_));
    EXPECT_FALSE(getCalloutManager()->calloutsPresent(delta_index_));

    // Each library contributes two callouts to hook "alpha".
    callout_value_ = 0;
    getCalloutManager()->setLibraryIndex(0);
    getCalloutManager()->registerCallout("alpha", callout_one);
    getCalloutManager()->registerCallout("alpha", callout_two);
    getCalloutManager()->setLibraryIndex(1);
    getCalloutManager()->registerCallout("alpha", callout_three);
    getCalloutManager()->registerCallout("alpha", callout_four);
    getCalloutManager()->setLibraryIndex(2);
    getCalloutManager()->registerCallout("alpha", callout_five);
    getCalloutManager()->registerCallout("alpha", callout_two);
    getCalloutManager()->callCallouts(alpha_index_, getCalloutHandle());
    EXPECT_EQ(123452, callout_value_);

    // Remove the callout_two callout from library 0.  It should not affect
    // the second callout_two callout registered by library 2.
    getCalloutManager()->setLibraryIndex(0);
    EXPECT_TRUE(getCalloutManager()->deregisterCallout("alpha", callout_two));
    callout_value_ = 0;
    getCalloutManager()->callCallouts(alpha_index_, getCalloutHandle());
    EXPECT_EQ(13452, callout_value_);
}

// Check we can deregister all callouts from a single library.

TEST_F(CalloutManagerTest, DeregisterAllCallouts) {
    // Ensure that no callouts are attached to hook one.
    EXPECT_FALSE(getCalloutManager()->calloutsPresent(alpha_index_));

    // Each library contributes two callouts to hook "alpha".
    callout_value_ = 0;
    getCalloutManager()->setLibraryIndex(0);
    getCalloutManager()->registerCallout("alpha", callout_one);
    getCalloutManager()->registerCallout("alpha", callout_two);
    getCalloutManager()->setLibraryIndex(1);
    getCalloutManager()->registerCallout("alpha", callout_three);
    getCalloutManager()->registerCallout("alpha", callout_four);
    getCalloutManager()->setLibraryIndex(2);
    getCalloutManager()->registerCallout("alpha", callout_five);
    getCalloutManager()->registerCallout("alpha", callout_six);
    getCalloutManager()->callCallouts(alpha_index_, getCalloutHandle());
    EXPECT_EQ(123456, callout_value_);

    // Remove all callouts from library index 1.
    getCalloutManager()->setLibraryIndex(1);
    EXPECT_TRUE(getCalloutManager()->deregisterAllCallouts("alpha"));
    callout_value_ = 0;
    getCalloutManager()->callCallouts(alpha_index_, getCalloutHandle());
    EXPECT_EQ(1256, callout_value_);

    // Remove all callouts from library index 2.
    getCalloutManager()->setLibraryIndex(2);
    EXPECT_TRUE(getCalloutManager()->deregisterAllCallouts("alpha"));
    callout_value_ = 0;
    getCalloutManager()->callCallouts(alpha_index_, getCalloutHandle());
    EXPECT_EQ(12, callout_value_);
}

// Check that we can register/deregister callouts on different libraries
// and different hooks, and that the callout instances are regarded as
// unique and do not affect one another.

TEST_F(CalloutManagerTest, MultipleCalloutsLibrariesHooks) {
    // Ensure that no callouts are attached to any of the hooks.
    EXPECT_FALSE(getCalloutManager()->calloutsPresent(alpha_index_));
    EXPECT_FALSE(getCalloutManager()->calloutsPresent(beta_index_));
    EXPECT_FALSE(getCalloutManager()->calloutsPresent(gamma_index_));
    EXPECT_FALSE(getCalloutManager()->calloutsPresent(delta_index_));

    // Register callouts on the alpha hook.
    callout_value_ = 0;
    getCalloutManager()->setLibraryIndex(0);
    getCalloutManager()->registerCallout("alpha", callout_one);
    getCalloutManager()->registerCallout("alpha", callout_two);
    getCalloutManager()->setLibraryIndex(1);
    getCalloutManager()->registerCallout("alpha", callout_three);
    getCalloutManager()->registerCallout("alpha", callout_four);
    getCalloutManager()->setLibraryIndex(2);
    getCalloutManager()->registerCallout("alpha", callout_five);
    getCalloutManager()->registerCallout("alpha", callout_two);
    getCalloutManager()->callCallouts(alpha_index_, getCalloutHandle());
    EXPECT_EQ(123452, callout_value_);

    // Register the same callouts on the beta hook, and check that those
    // on the alpha hook are not affected.
    callout_value_ = 0;
    getCalloutManager()->setLibraryIndex(0);
    getCalloutManager()->registerCallout("beta", callout_five);
    getCalloutManager()->registerCallout("beta", callout_one);
    getCalloutManager()->setLibraryIndex(2);
    getCalloutManager()->registerCallout("beta", callout_four);
    getCalloutManager()->registerCallout("beta", callout_three);
    getCalloutManager()->callCallouts(beta_index_, getCalloutHandle());
    EXPECT_EQ(5143, callout_value_);

    // Check that the order of callouts on the alpha hook has not been affected.
    callout_value_ = 0;
    getCalloutManager()->callCallouts(alpha_index_, getCalloutHandle());
    EXPECT_EQ(123452, callout_value_);

    // Remove callout four from beta and check that alpha is not affected.
    getCalloutManager()->setLibraryIndex(2);
    EXPECT_TRUE(getCalloutManager()->deregisterCallout("beta", callout_four));

    callout_value_ = 0;
    getCalloutManager()->callCallouts(beta_index_, getCalloutHandle());
    EXPECT_EQ(513, callout_value_);

    callout_value_ = 0;
    getCalloutManager()->callCallouts(alpha_index_, getCalloutHandle());
    EXPECT_EQ(123452, callout_value_);
}

// Library handle tests.  As by inspection the LibraryHandle can be seen to be
// little more than shell around CalloutManager, only a basic set of tests
// is done concerning registration and deregistration of functions.
//
// More extensive tests (i.e. checking that when a callout is called it can
// only register and deregister callouts within its library) require that
// the CalloutHandle object pass the appropriate LibraryHandle to the
// callout.  These tests are done in the handles_unittest tests.

TEST_F(CalloutManagerTest, LibraryHandleRegistration) {
    // Ensure that no callouts are attached to any of the hooks.
    EXPECT_FALSE(getCalloutManager()->calloutsPresent(alpha_index_));

    // Set up so that hooks "alpha" and "beta" have callouts attached from a
    // different libraries.
    getCalloutManager()->setLibraryIndex(0);
    getCalloutManager()->getLibraryHandle().registerCallout("alpha",
                                                            callout_one);
    getCalloutManager()->getLibraryHandle().registerCallout("alpha",
                                                            callout_two);
    getCalloutManager()->setLibraryIndex(1);
    getCalloutManager()->getLibraryHandle().registerCallout("alpha",
                                                            callout_three);
    getCalloutManager()->getLibraryHandle().registerCallout("alpha",
                                                            callout_four);

    // Check all is as expected.
    EXPECT_TRUE(getCalloutManager()->calloutsPresent(alpha_index_));
    EXPECT_FALSE(getCalloutManager()->calloutsPresent(beta_index_));
    EXPECT_FALSE(getCalloutManager()->calloutsPresent(gamma_index_));
    EXPECT_FALSE(getCalloutManager()->calloutsPresent(delta_index_));

    // Check that calling the callouts returns as expected. (This is also a
    // test of the callCallouts method.)
    callout_value_ = 0;
    getCalloutManager()->callCallouts(alpha_index_, getCalloutHandle());
    EXPECT_EQ(1234, callout_value_);

    // Deregister a callout on library index 0 (after we check we can't
    // deregister it through library index 1).
    getCalloutManager()->setLibraryIndex(1);
    EXPECT_FALSE(getCalloutManager()->deregisterCallout("alpha", callout_two));
    callout_value_ = 0;
    getCalloutManager()->callCallouts(alpha_index_, getCalloutHandle());
    EXPECT_EQ(1234, callout_value_);

    getCalloutManager()->setLibraryIndex(0);
    EXPECT_TRUE(getCalloutManager()->deregisterCallout("alpha", callout_two));
    callout_value_ = 0;
    getCalloutManager()->callCallouts(alpha_index_, getCalloutHandle());
    EXPECT_EQ(134, callout_value_);

    // Deregister all callouts on library index 1.
    getCalloutManager()->setLibraryIndex(1);
    EXPECT_TRUE(getCalloutManager()->deregisterAllCallouts("alpha"));
    callout_value_ = 0;
    getCalloutManager()->callCallouts(alpha_index_, getCalloutHandle());
    EXPECT_EQ(1, callout_value_);
}

// A repeat of the test above, but using the alternate constructor for the
// LibraryHandle.
TEST_F(CalloutManagerTest, LibraryHandleAlternateConstructor) {
    // Ensure that no callouts are attached to any of the hooks.
    EXPECT_FALSE(getCalloutManager()->calloutsPresent(alpha_index_));

    // Set up so that hooks "alpha" and "beta" have callouts attached from a
    // different libraries.
    LibraryHandle lh0(getCalloutManager().get(), 0);
    lh0.registerCallout("alpha", callout_one);
    lh0.registerCallout("alpha", callout_two);

    LibraryHandle lh1(getCalloutManager().get(), 1);
    lh1.registerCallout("alpha", callout_three);
    lh1.registerCallout("alpha", callout_four);

    // Check all is as expected.
    EXPECT_TRUE(getCalloutManager()->calloutsPresent(alpha_index_));
    EXPECT_FALSE(getCalloutManager()->calloutsPresent(beta_index_));
    EXPECT_FALSE(getCalloutManager()->calloutsPresent(gamma_index_));
    EXPECT_FALSE(getCalloutManager()->calloutsPresent(delta_index_));

    // Check that calling the callouts returns as expected. (This is also a
    // test of the callCallouts method.)
    callout_value_ = 0;
    getCalloutManager()->callCallouts(alpha_index_, getCalloutHandle());
    EXPECT_EQ(1234, callout_value_);

    // Deregister a callout on library index 0 (after we check we can't
    // deregister it through library index 1).
    EXPECT_FALSE(lh1.deregisterCallout("alpha", callout_two));
    callout_value_ = 0;
    getCalloutManager()->callCallouts(alpha_index_, getCalloutHandle());
    EXPECT_EQ(1234, callout_value_);

    EXPECT_TRUE(lh0.deregisterCallout("alpha", callout_two));
    callout_value_ = 0;
    getCalloutManager()->callCallouts(alpha_index_, getCalloutHandle());
    EXPECT_EQ(134, callout_value_);

    // Deregister all callouts on library index 1.
    EXPECT_TRUE(lh1.deregisterAllCallouts("alpha"));
    callout_value_ = 0;
    getCalloutManager()->callCallouts(alpha_index_, getCalloutHandle());
    EXPECT_EQ(1, callout_value_);
}

// Check that the pre- and post- user callout library handles work
// appropriately with no user libraries.

TEST_F(CalloutManagerTest, LibraryHandlePrePostNoLibraries) {
    // Create a local callout manager and callout handle to reflect no libraries
    // being loaded.
    boost::shared_ptr<CalloutManager> manager(new CalloutManager(0));
    CalloutHandle handle(manager);

    // Ensure that no callouts are attached to any of the hooks.
    EXPECT_FALSE(manager->calloutsPresent(alpha_index_));

    // Setup the pre-and post callouts.
    manager->getPostLibraryHandle().registerCallout("alpha", callout_four);
    manager->getPreLibraryHandle().registerCallout("alpha", callout_one);
    // Check all is as expected.
    EXPECT_TRUE(manager->calloutsPresent(alpha_index_));
    EXPECT_FALSE(manager->calloutsPresent(beta_index_));
    EXPECT_FALSE(manager->calloutsPresent(gamma_index_));
    EXPECT_FALSE(manager->calloutsPresent(delta_index_));

    // Check that calling the callouts returns as expected.
    callout_value_ = 0;
    manager->callCallouts(alpha_index_, handle);
    EXPECT_EQ(14, callout_value_);

    // Deregister the pre- library callout.
    EXPECT_TRUE(manager->getPreLibraryHandle().deregisterAllCallouts("alpha"));
    callout_value_ = 0;
    manager->callCallouts(alpha_index_, handle);
    EXPECT_EQ(4, callout_value_);
}

// Repeat the tests with one user library.

TEST_F(CalloutManagerTest, LibraryHandlePrePostUserLibrary) {

    // Setup the pre-, library and post callouts.
    getCalloutManager()->getPostLibraryHandle().registerCallout("alpha",
                                                                callout_four);
    getCalloutManager()->getPreLibraryHandle().registerCallout("alpha",
                                                                callout_one);

    // ... and set up a callout in between, on library number 2.
    LibraryHandle lh1(getCalloutManager().get(), 2);
    lh1.registerCallout("alpha", callout_five);

    // Check all is as expected.
    EXPECT_TRUE(getCalloutManager()->calloutsPresent(alpha_index_));
    EXPECT_FALSE(getCalloutManager()->calloutsPresent(beta_index_));
    EXPECT_FALSE(getCalloutManager()->calloutsPresent(gamma_index_));
    EXPECT_FALSE(getCalloutManager()->calloutsPresent(delta_index_));

    // Check that calling the callouts returns as expected.
    callout_value_ = 0;
    getCalloutManager()->callCallouts(alpha_index_, getCalloutHandle());
    EXPECT_EQ(154, callout_value_);
}

// The setting of the hook index is checked in the handles_unittest
// set of tests, as access restrictions mean it is not easily tested
// on its own.

} // Anonymous namespace
