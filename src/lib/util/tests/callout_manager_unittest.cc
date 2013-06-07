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
#include <util/hooks/callout_handle.h>
#include <util/hooks/callout_manager.h>
#include <util/hooks/server_hooks.h>

#include <gtest/gtest.h>

#include <algorithm>
#include <string>
#include <vector>

using namespace isc;
using namespace isc::util;
using namespace std;

namespace {

class CalloutManagerTest : public ::testing::Test {
public:
    /// @brief Constructor
    ///
    /// Sets up a collection of three LibraryHandle objects to use in the test.
    CalloutManagerTest() : hooks_(new ServerHooks()) {

        // Set up the server hooks
        one_index_ = hooks_->registerHook("one");
        two_index_ = hooks_->registerHook("two");
        three_index_ = hooks_->registerHook("three");
        four_index_ = hooks_->registerHook("four");

        // Set up the callout manager with these hooks
        callout_manager_.reset(new CalloutManager(hooks_));

        // Set up four library handles.
        library_handle_.push_back(callout_manager_->createHandle());
        library_handle_.push_back(callout_manager_->createHandle());
        library_handle_.push_back(callout_manager_->createHandle());
        library_handle_.push_back(callout_manager_->createHandle());

        // Set up the callout handle.
        callout_handle_.reset(new CalloutHandle(callout_manager_));
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
    int one_index_;
    int two_index_;
    int three_index_;
    int four_index_;

private:
    /// Callout manager used for the test
    boost::shared_ptr<CalloutManager> callout_manager_;

    /// Server hooks
    boost::shared_ptr<ServerHooks> hooks_;

    /// Set up three library handles.
    std::vector<boost::shared_ptr<LibraryHandle> > library_handle_;

    /// Callout handle used in calls
    boost::shared_ptr<CalloutHandle> callout_handle_;

};

// Definition of the static variable.
int CalloutManagerTest::callout_value_ = 0;

// *** Callout Tests ***
//
// The next set of tests check that callouts can be called.

// The callouts defined here are structured in such a way that it is possible
// to determine the order in which they are called and whether they are called
// at all. The method used is simple - after a sequence of callouts, the digits
// in the value, reading left to right, determines the order of the callouts
// called.  For example, callout one followed by two followed by three followed
// by two followed by one results in a value of 12321.
//
// Functions return a zero to indicate success.

extern "C" {
int manager_general(int number) {
    CalloutManagerTest::callout_value_ =
        10 * CalloutManagerTest::callout_value_ + number;
    return (0);
}

int manager_one(CalloutHandle&) {
    return (manager_general(1));
}

int manager_two(CalloutHandle&) {
    return (manager_general(2));
}

int manager_three(CalloutHandle&) {
    return (manager_general(3));
}

int manager_four(CalloutHandle&) {
    return (manager_general(4));
}

int manager_five(CalloutHandle&) {
    return (manager_general(5));
}

int manager_six(CalloutHandle&) {
    return (manager_general(6));
}

int manager_seven(CalloutHandle&) {
    return (manager_general(7));
}

// The next functions are duplicates of some of the above, but return an error.

int manager_one_error(CalloutHandle& handle) {
    (void) manager_one(handle);
    return (1);
}

int manager_two_error(CalloutHandle& handle) {
    (void) manager_two(handle);
    return (1);
}

int manager_three_error(CalloutHandle& handle) {
    (void) manager_three(handle);
    return (1);
}

int manager_four_error(CalloutHandle& handle) {
    (void) manager_four(handle);
    return (1);
}

};  // extern "C"

// Check we can register callouts appropriately.

TEST_F(CalloutManagerTest, RegisterCallout) {
    // Ensure that no callouts are attached to any of the hooks.
    EXPECT_FALSE(getCalloutManager()->calloutsPresent(one_index_));
    EXPECT_FALSE(getCalloutManager()->calloutsPresent(two_index_));

    // Set up so that hooks "one" and "two" have callouts attached from a
    // single library.

    getCalloutManager()->registerCallout(0, "one", manager_one);
    getCalloutManager()->registerCallout(1, "two", manager_two);

    // Check all is as expected.
    EXPECT_TRUE(getCalloutManager()->calloutsPresent(one_index_));
    EXPECT_TRUE(getCalloutManager()->calloutsPresent(two_index_));
    EXPECT_FALSE(getCalloutManager()->calloutsPresent(three_index_));
    EXPECT_FALSE(getCalloutManager()->calloutsPresent(four_index_));
                 
    int status = 0;

    // Check that calling the callouts returns as expected.
    callout_value_ = 0;
    status = getCalloutManager()->callCallouts(one_index_, getCalloutHandle());
    EXPECT_EQ(0, status);
    EXPECT_EQ(1, callout_value_);

    callout_value_ = 0;
    status = getCalloutManager()->callCallouts(two_index_, getCalloutHandle());
    EXPECT_EQ(0, status);
    EXPECT_EQ(2, callout_value_);

    // Register some more callouts from different libraries on hook 1.
    getCalloutManager()->registerCallout(2, "one", manager_three);
    getCalloutManager()->registerCallout(2, "one", manager_four);
    getCalloutManager()->registerCallout(3, "one", manager_five);

    // Check it is as expected.
    callout_value_ = 0;
    status = getCalloutManager()->callCallouts(one_index_, getCalloutHandle());
    EXPECT_EQ(0, status);
    EXPECT_EQ(1345, callout_value_);

    callout_value_ = 0;
    status = getCalloutManager()->callCallouts(two_index_, getCalloutHandle());
    EXPECT_EQ(0, status);
    EXPECT_EQ(2, callout_value_);

    // Add another callout to hook one from library iindex 2 - this should
    // appear at the end of the callout list for that library.
    getCalloutManager()->registerCallout(2, "one", manager_six);
    callout_value_ = 0;
    status = getCalloutManager()->callCallouts(one_index_, getCalloutHandle());
    EXPECT_EQ(0, status);
    EXPECT_EQ(13465, callout_value_);

    // Add a callout from library index 1 - this should appear between the
    // callouts from library index 0 and linrary index 2.
    getCalloutManager()->registerCallout(1, "one", manager_seven);
    callout_value_ = 0;
    status = getCalloutManager()->callCallouts(one_index_, getCalloutHandle());
    EXPECT_EQ(0, status);
    EXPECT_EQ(173465, callout_value_);


}

// Check the "calloutsPresent()" method.

TEST_F(CalloutManagerTest, CalloutsPresent) {
    // Ensure that no callouts are attached to any of the hooks.
    EXPECT_FALSE(getCalloutManager()->calloutsPresent(one_index_));
    EXPECT_FALSE(getCalloutManager()->calloutsPresent(two_index_));
    EXPECT_FALSE(getCalloutManager()->calloutsPresent(three_index_));
    EXPECT_FALSE(getCalloutManager()->calloutsPresent(four_index_));
                 
    // Set up so that hooks "one", "two" and "four" have callouts attached
    // to them, and callout  "three" does not. (In the statements below, the
    // exact callouts attached to a hook are not relevant - only the fact
    // that some callouts are).  Chose the libraries for which the callouts
    // are registered randomly.

    getCalloutManager()->registerCallout(0, "one", manager_one);

    getCalloutManager()->registerCallout(1, "one", manager_two);
    getCalloutManager()->registerCallout(1, "two", manager_two);

    getCalloutManager()->registerCallout(3, "one", manager_three);
    getCalloutManager()->registerCallout(3, "four", manager_four);

    // Check all is as expected.
    EXPECT_TRUE(getCalloutManager()->calloutsPresent(one_index_));
    EXPECT_TRUE(getCalloutManager()->calloutsPresent(two_index_));
    EXPECT_FALSE(getCalloutManager()->calloutsPresent(three_index_));
    EXPECT_TRUE(getCalloutManager()->calloutsPresent(four_index_));

    // Check we fail on an invalid index.
    EXPECT_THROW(getCalloutManager()->calloutsPresent(42), NoSuchHook);
    EXPECT_THROW(getCalloutManager()->calloutsPresent(-1), NoSuchHook);
}

// Test that calling a hook with no callouts on it returns success.

TEST_F(CalloutManagerTest, CallNoCallouts) {
    // Ensure that no callouts are attached to any of the hooks.
    EXPECT_FALSE(getCalloutManager()->calloutsPresent(one_index_));
    EXPECT_FALSE(getCalloutManager()->calloutsPresent(two_index_));
    EXPECT_FALSE(getCalloutManager()->calloutsPresent(three_index_));
    EXPECT_FALSE(getCalloutManager()->calloutsPresent(four_index_));
                 
    // Call the callouts on an arbitrary hook and ensure that nothing happens.
    callout_value_ = 475;
    int status = getCalloutManager()->callCallouts(one_index_,
                                                   getCalloutHandle());
    EXPECT_EQ(0, status);
    EXPECT_EQ(475, callout_value_); // Unchanged
}

// Test that the callouts are called in the correct order.

TEST_F(CalloutManagerTest, CallCalloutsSuccess) {
    // Ensure that no callouts are attached to any of the hooks.
    EXPECT_FALSE(getCalloutManager()->calloutsPresent(one_index_));
    EXPECT_FALSE(getCalloutManager()->calloutsPresent(two_index_));
    EXPECT_FALSE(getCalloutManager()->calloutsPresent(three_index_));
    EXPECT_FALSE(getCalloutManager()->calloutsPresent(four_index_));
                 
    int status = 0;

    // Each library contributes one callout on hook "one".
    callout_value_ = 0;
    getCalloutManager()->registerCallout(0, "one", manager_one);
    getCalloutManager()->registerCallout(1, "one", manager_two);
    getCalloutManager()->registerCallout(2, "one", manager_three);
    getCalloutManager()->registerCallout(3, "one", manager_four);
    status = getCalloutManager()->callCallouts(one_index_, getCalloutHandle());
    EXPECT_EQ(0, status);
    EXPECT_EQ(1234, callout_value_);

    // Do a random selection of callouts on hook "two".
    callout_value_ = 0;
    getCalloutManager()->registerCallout(0, "two", manager_one);
    getCalloutManager()->registerCallout(0, "two", manager_three);
    getCalloutManager()->registerCallout(1, "two", manager_two);
    getCalloutManager()->registerCallout(3, "two", manager_four);
    status = getCalloutManager()->callCallouts(two_index_, getCalloutHandle());
    EXPECT_EQ(0, status);
    EXPECT_EQ(1324, callout_value_);

    // Ensure that calling the callouts on a hook with no callouts works.
    callout_value_ = 0;
    status = getCalloutManager()->callCallouts(three_index_,
                                               getCalloutHandle());
    EXPECT_EQ(0, status);
    EXPECT_EQ(0, callout_value_);
}

// Test that the callouts are called in order, but that callouts occurring
// after a callout that returns an error are not called.
//
// (Note: in this test, the callouts that return an error set the value of
// callout_value_ before they return the error code.)

TEST_F(CalloutManagerTest, CallCalloutsError) {
    // Ensure that no callouts are attached to any of the hooks.
    EXPECT_FALSE(getCalloutManager()->calloutsPresent(one_index_));
    EXPECT_FALSE(getCalloutManager()->calloutsPresent(two_index_));
    EXPECT_FALSE(getCalloutManager()->calloutsPresent(three_index_));
    EXPECT_FALSE(getCalloutManager()->calloutsPresent(four_index_));
                 
    int status = 0;

    // Each library contributing one callout on hook "one". The first callout
    // returns an error (after adding its value to the result).
    callout_value_ = 0;
    getCalloutManager()->registerCallout(0, "one", manager_one_error);
    getCalloutManager()->registerCallout(1, "one", manager_two);
    getCalloutManager()->registerCallout(2, "one", manager_three);
    getCalloutManager()->registerCallout(3, "one", manager_four);
    status = getCalloutManager()->callCallouts(one_index_, getCalloutHandle());
    EXPECT_EQ(1, status);
    EXPECT_EQ(1, callout_value_);

    // Each library contributing multiple callouts on hook "two". The last
    // callout on the first library returns an error.
    callout_value_ = 0;
    getCalloutManager()->registerCallout(0, "two", manager_one);
    getCalloutManager()->registerCallout(0, "two", manager_one_error);
    getCalloutManager()->registerCallout(1, "two", manager_two);
    getCalloutManager()->registerCallout(1, "two", manager_two);
    getCalloutManager()->registerCallout(1, "two", manager_three);
    getCalloutManager()->registerCallout(1, "two", manager_three);
    getCalloutManager()->registerCallout(3, "two", manager_four);
    getCalloutManager()->registerCallout(3, "two", manager_four);
    status = getCalloutManager()->callCallouts(two_index_, getCalloutHandle());
    EXPECT_EQ(1, status);
    EXPECT_EQ(11, callout_value_);

    // A callout in a random position in the callout list returns an error.
    callout_value_ = 0;
    getCalloutManager()->registerCallout(0, "three", manager_one);
    getCalloutManager()->registerCallout(0, "three", manager_one);
    getCalloutManager()->registerCallout(1, "three", manager_two);
    getCalloutManager()->registerCallout(1, "three", manager_two);
    getCalloutManager()->registerCallout(3, "three", manager_four_error);
    getCalloutManager()->registerCallout(3, "three", manager_four);
    status = getCalloutManager()->callCallouts(three_index_,
                                               getCalloutHandle());
    EXPECT_EQ(1, status);
    EXPECT_EQ(11224, callout_value_);

    // The last callout on a hook returns an error.
    callout_value_ = 0;
    getCalloutManager()->registerCallout(0, "four", manager_one);
    getCalloutManager()->registerCallout(0, "four", manager_one);
    getCalloutManager()->registerCallout(1, "four", manager_two);
    getCalloutManager()->registerCallout(1, "four", manager_two);
    getCalloutManager()->registerCallout(2, "four", manager_three);
    getCalloutManager()->registerCallout(2, "four", manager_three);
    getCalloutManager()->registerCallout(3, "four", manager_four);
    getCalloutManager()->registerCallout(3, "four", manager_four_error);
    status = getCalloutManager()->callCallouts(four_index_, getCalloutHandle());
    EXPECT_EQ(1, status);
    EXPECT_EQ(11223344, callout_value_);
}

// Now test that we can deregister a single callout on a hook.

TEST_F(CalloutManagerTest, DeregisterSingleCallout) {
    // Ensure that no callouts are attached to any of the hooks.
    EXPECT_FALSE(getCalloutManager()->calloutsPresent(one_index_));
    EXPECT_FALSE(getCalloutManager()->calloutsPresent(two_index_));
    EXPECT_FALSE(getCalloutManager()->calloutsPresent(three_index_));
    EXPECT_FALSE(getCalloutManager()->calloutsPresent(four_index_));
                 
    int status = 0;

    // Each library contributes one callout on hook "one".
    callout_value_ = 0;
    getCalloutManager()->registerCallout(0, "one", manager_two);
    status = getCalloutManager()->callCallouts(one_index_, getCalloutHandle());
    EXPECT_EQ(0, status);
    EXPECT_EQ(2, callout_value_);

    // Remove it and check that the no callouts are present.
    EXPECT_TRUE(getCalloutManager()->calloutsPresent(one_index_));
    EXPECT_TRUE(getCalloutManager()->deregisterCallout(0, "one", manager_two));
    EXPECT_FALSE(getCalloutManager()->calloutsPresent(one_index_));
}

// Now test that we can deregister a single callout on a hook that has multiple
// callouts from the same library.

TEST_F(CalloutManagerTest, DeregisterSingleCalloutSameLibrary) {
    // Ensure that no callouts are attached to any of the hooks.
    EXPECT_FALSE(getCalloutManager()->calloutsPresent(one_index_));
    EXPECT_FALSE(getCalloutManager()->calloutsPresent(two_index_));
    EXPECT_FALSE(getCalloutManager()->calloutsPresent(three_index_));
    EXPECT_FALSE(getCalloutManager()->calloutsPresent(four_index_));
                 
    int status = 0;

    // Each library contributes one callout on hook "one".
    callout_value_ = 0;
    getCalloutManager()->registerCallout(0, "one", manager_one);
    getCalloutManager()->registerCallout(0, "one", manager_two);
    getCalloutManager()->registerCallout(0, "one", manager_three);
    getCalloutManager()->registerCallout(0, "one", manager_four);
    status = getCalloutManager()->callCallouts(one_index_, getCalloutHandle());
    EXPECT_EQ(0, status);
    EXPECT_EQ(1234, callout_value_);

    // Remove the manager_two callout.
    EXPECT_TRUE(getCalloutManager()->deregisterCallout(0, "one", manager_two));
    callout_value_ = 0;
    status = getCalloutManager()->callCallouts(one_index_, getCalloutHandle());
    EXPECT_EQ(0, status);
    EXPECT_EQ(134, callout_value_);

    // Try removing it again.
    EXPECT_FALSE(getCalloutManager()->deregisterCallout(0, "one", manager_two));
    callout_value_ = 0;
    status = getCalloutManager()->callCallouts(one_index_, getCalloutHandle());
    EXPECT_EQ(0, status);
    EXPECT_EQ(134, callout_value_);

}

// Check we can deregister multiple callouts from the same library.

TEST_F(CalloutManagerTest, DeregisterMultipleCalloutsSameLibrary) {
    // Ensure that no callouts are attached to any of the hooks.
    EXPECT_FALSE(getCalloutManager()->calloutsPresent(one_index_));
    EXPECT_FALSE(getCalloutManager()->calloutsPresent(two_index_));
    EXPECT_FALSE(getCalloutManager()->calloutsPresent(three_index_));
    EXPECT_FALSE(getCalloutManager()->calloutsPresent(four_index_));
                 
    int status = 0;

    // Each library contributes one callout on hook "one".
    callout_value_ = 0;
    getCalloutManager()->registerCallout(0, "one", manager_one);
    getCalloutManager()->registerCallout(0, "one", manager_one);
    getCalloutManager()->registerCallout(0, "one", manager_two);
    getCalloutManager()->registerCallout(0, "one", manager_two);
    getCalloutManager()->registerCallout(0, "one", manager_three);
    getCalloutManager()->registerCallout(0, "one", manager_three);
    getCalloutManager()->registerCallout(0, "one", manager_four);
    getCalloutManager()->registerCallout(0, "one", manager_four);
    status = getCalloutManager()->callCallouts(one_index_, getCalloutHandle());
    EXPECT_EQ(0, status);
    EXPECT_EQ(11223344, callout_value_);

    // Remove the manager_two callout.
    EXPECT_TRUE(getCalloutManager()->deregisterCallout(0, "one", manager_two));
    callout_value_ = 0;
    status = getCalloutManager()->callCallouts(one_index_, getCalloutHandle());
    EXPECT_EQ(0, status);
    EXPECT_EQ(113344, callout_value_);

    // Try removing multiple callouts from the end of the list.
    EXPECT_TRUE(getCalloutManager()->deregisterCallout(0, "one", manager_four));
    callout_value_ = 0;
    status = getCalloutManager()->callCallouts(one_index_, getCalloutHandle());
    EXPECT_EQ(0, status);
    EXPECT_EQ(1133, callout_value_);

    // ... and from the start.
    EXPECT_TRUE(getCalloutManager()->deregisterCallout(0, "one", manager_one));
    callout_value_ = 0;
    status = getCalloutManager()->callCallouts(one_index_, getCalloutHandle());
    EXPECT_EQ(0, status);
    EXPECT_EQ(33, callout_value_);

    // ... and the remaining callouts.
    EXPECT_TRUE(getCalloutManager()->deregisterCallout(0, "one",
                                                       manager_three));
    callout_value_ = 0;
    status = getCalloutManager()->callCallouts(one_index_, getCalloutHandle());
    EXPECT_EQ(0, status);
    EXPECT_EQ(0, callout_value_);

    EXPECT_FALSE(getCalloutManager()->calloutsPresent(one_index_));
}

// Check we can deregister multiple callouts from multiple libraries

TEST_F(CalloutManagerTest, DeregisterMultipleCalloutsMultipleLibraries) {
    // Ensure that no callouts are attached to any of the hooks.
    EXPECT_FALSE(getCalloutManager()->calloutsPresent(one_index_));
    EXPECT_FALSE(getCalloutManager()->calloutsPresent(two_index_));
    EXPECT_FALSE(getCalloutManager()->calloutsPresent(three_index_));
    EXPECT_FALSE(getCalloutManager()->calloutsPresent(four_index_));
                 
    int status = 0;

    // Each library contributes two callouts to hook "one".
    callout_value_ = 0;
    getCalloutManager()->registerCallout(0, "one", manager_one);
    getCalloutManager()->registerCallout(0, "one", manager_two);
    getCalloutManager()->registerCallout(1, "one", manager_three);
    getCalloutManager()->registerCallout(1, "one", manager_four);
    getCalloutManager()->registerCallout(2, "one", manager_five);
    getCalloutManager()->registerCallout(2, "one", manager_two);
    status = getCalloutManager()->callCallouts(one_index_, getCalloutHandle());
    EXPECT_EQ(0, status);
    EXPECT_EQ(123452, callout_value_);

    // Remove the manager_two callout from library 0.  It should not affect
    // the second manager_two callout.
    EXPECT_TRUE(getCalloutManager()->deregisterCallout(0, "one", manager_two));
    callout_value_ = 0;
    status = getCalloutManager()->callCallouts(one_index_, getCalloutHandle());
    EXPECT_EQ(0, status);
    EXPECT_EQ(13452, callout_value_);
}


} // Anonymous namespace
