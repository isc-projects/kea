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
#include <util/hooks/library_handle.h>
#include <util/hooks/server_hooks.h>

#include <gtest/gtest.h>

#include <algorithm>
#include <string>
#include <vector>

using namespace isc;
using namespace isc::util;
using namespace std;

namespace {

/// @brief No such hook
///
/// Thrown if an attempt it made to obtain an invalid library handle.
class InvalidIndex : public isc::Exception {
public:
    InvalidIndex(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) {}
};

class LibraryHandleCollectionTest : public ::testing::Test {
public:
    /// @brief Constructor
    ///
    /// Sets up a collection of three LibraryHandle objects to use in the test.
    LibraryHandleCollectionTest()
        : collection_(new LibraryHandleCollection()), handles_(),
          hooks_(new ServerHooks()) {

        // Set up the server hooks
        hooks_->registerHook("one");
        hooks_->registerHook("two");
        hooks_->registerHook("three");
        hooks_->registerHook("four");

        // Set up the library handles and collection.
        for (int i = 0; i < 4; ++i) {
            boost::shared_ptr<LibraryHandle> handle(new LibraryHandle(hooks_));
            handles_.push_back(handle);
            collection_->addLibraryHandle(handle);
        }

        callout_value_ = 0;
    }

    /// @brief Obtain constructed server hooks
    ///
    /// @return Reference to shared pointer pointing to server hooks object.
    boost::shared_ptr<ServerHooks>& getServerHooks() {
        return (hooks_);
    }

    /// @brief Obtain LibraryHandleCollection object
    ///
    /// @return Reference to shared pointer pointing to handle collection
    boost::shared_ptr<LibraryHandleCollection>& getLibraryHandleCollection() {
        return (collection_);
    }

    /// @brief Obtain individual LibraryHandle.
    ///
    /// @param i Index of the library handle required.
    ///
    /// @return Reference to shared pointer pointing to the relevant handle.
    ///
    /// @throws InvalidIndex if the requeste dindex is not valid.
    boost::shared_ptr<LibraryHandle>& getLibraryHandle(int i) {
        if ((i < 0) || (i >= handles_.size())) {
            isc_throw(InvalidIndex, "handle index of " << i << " not valid for "
                      " size of handle vector (" << handles_.size() << ")");
        }
        return (handles_[i]);
    }

    /// Variable for callouts test. This is public and static to allow non-
    /// member functions to access it.  It is initialized every time a
    /// new test starts.
    static int callout_value_;

private:

    /// Library handle collection and the individual handles (as the
    /// collection has no method for accessing an individual member).
    boost::shared_ptr<LibraryHandleCollection> collection_;
    std::vector<boost::shared_ptr<LibraryHandle> > handles_;

    /// Server hooks and hooks manager
    boost::shared_ptr<ServerHooks> hooks_;
};

// Definition of the static variable.
int LibraryHandleCollectionTest::callout_value_ = 0;

// *** Callout Tests ***
//
// The next set of tests check that callouts can be called.

// Supply callouts structured in such a way that we can determine the order
// that they are called and whether they are called at all. The method used
// is simple - after a sequence of callouts, the digits in the value, reading
// left to right, determines the order of the callouts and whether they were
// called at all.  So:
//
// * one followed by two, the resulting value is 12
// * two followed by one, the resuling value is 21
// * one and two is not called, the resulting value is 1
// * two and one is not called, the resulting value is 2
// * neither called, the resulting value is 0
//
// ... and extending beyond two callouts:
//
// * one followed by two followed by three followed by two followed by one
//   results in a value of 12321.
//
// Functions return a zero indicating success.

extern "C" {
int collection_one(CalloutHandle&) {
    LibraryHandleCollectionTest::callout_value_ =
        10 * LibraryHandleCollectionTest::callout_value_ + 1;
    return (0);
}

int collection_two(CalloutHandle&) {
    LibraryHandleCollectionTest::callout_value_ =
        10 * LibraryHandleCollectionTest::callout_value_ + 2;
    return (0);
}

int collection_three(CalloutHandle&) {
    LibraryHandleCollectionTest::callout_value_ =
        10 * LibraryHandleCollectionTest::callout_value_ + 3;
    return (0);
}

int collection_four(CalloutHandle&) {
    LibraryHandleCollectionTest::callout_value_ =
        10 * LibraryHandleCollectionTest::callout_value_ + 4;
    return (0);
}

// The next functions are duplicates of the above, but return an error.

int collection_one_error(CalloutHandle& handle) {
    (void) collection_one(handle);
    return (1);
}

int collection_two_error(CalloutHandle& handle) {
    (void) collection_two(handle);
    return (1);
}

int collection_three_error(CalloutHandle& handle) {
    (void) collection_three(handle);
    return (1);
}

int collection_four_error(CalloutHandle& handle) {
    (void) collection_four(handle);
    return (1);
}

// The next functions are duplicates of the above, but set the skip flag.

int collection_one_skip(CalloutHandle& handle) {
    handle.setSkip(true);
    return (collection_one(handle));
}

int collection_two_skip(CalloutHandle& handle) {
    handle.setSkip(true);
    return (collection_two(handle));
}

int collection_three_skip(CalloutHandle& handle) {
    handle.setSkip(true);
    return (collection_three(handle));
}

int collection_four_skip(CalloutHandle& handle) {
    handle.setSkip(true);
    return (collection_four(handle));
}

};  // extern "C"

// Check that we know which hooks have callouts attached to them.
// Note: as we needed to use the addHandleMethod() to set up the handles to
// which the callouts are attached, this can also be construed as a test
// of the addLibraryHandle method as well.

TEST_F(LibraryHandleCollectionTest, CalloutsPresent) {
    const int one_index = getServerHooks()->getIndex("one");
    const int two_index = getServerHooks()->getIndex("two");
    const int three_index = getServerHooks()->getIndex("three");
    const int four_index = getServerHooks()->getIndex("four");

    // Ensure that no callouts are attached to any of the hooks.
    EXPECT_FALSE(getLibraryHandleCollection()->calloutsPresent(one_index));
    EXPECT_FALSE(getLibraryHandleCollection()->calloutsPresent(two_index));
    EXPECT_FALSE(getLibraryHandleCollection()->calloutsPresent(three_index));
    EXPECT_FALSE(getLibraryHandleCollection()->calloutsPresent(four_index));
                 
    // Set up so that hooks "one", "two" and "four" have callouts attached
    // to them, and callout  "three" does not. (In the statements below, the
    // exact callouts attached to a hook are not relevant - only the fact
    // that some callouts are).

    getLibraryHandle(0)->registerCallout("one", collection_one);

    getLibraryHandle(1)->registerCallout("one", collection_two);
    getLibraryHandle(1)->registerCallout("two", collection_two);

    getLibraryHandle(3)->registerCallout("one", collection_four);
    getLibraryHandle(3)->registerCallout("four", collection_two);

    // Check all is as expected.
    EXPECT_TRUE(getLibraryHandleCollection()->calloutsPresent(one_index));
    EXPECT_TRUE(getLibraryHandleCollection()->calloutsPresent(two_index));
    EXPECT_FALSE(getLibraryHandleCollection()->calloutsPresent(three_index));
    EXPECT_TRUE(getLibraryHandleCollection()->calloutsPresent(four_index));

    // Check we fail on an invalid index.
    EXPECT_THROW(getLibraryHandleCollection()->calloutsPresent(42), NoSuchHook);
    EXPECT_THROW(getLibraryHandleCollection()->calloutsPresent(-1), NoSuchHook);

    // Check we get a negative result on an empty collection.
    LibraryHandleCollection empty_collection;
    EXPECT_FALSE(empty_collection.calloutsPresent(-1));
}

// Test that the callouts are called in order.

TEST_F(LibraryHandleCollectionTest, CallCalloutsSuccess) {
    const int one_index = getServerHooks()->getIndex("one");
    const int two_index = getServerHooks()->getIndex("two");
    const int three_index = getServerHooks()->getIndex("three");
    const int four_index = getServerHooks()->getIndex("four");

    // Ensure that no callouts are attached to any of the hooks.
    EXPECT_FALSE(getLibraryHandleCollection()->calloutsPresent(one_index));
    EXPECT_FALSE(getLibraryHandleCollection()->calloutsPresent(two_index));
    EXPECT_FALSE(getLibraryHandleCollection()->calloutsPresent(three_index));
    EXPECT_FALSE(getLibraryHandleCollection()->calloutsPresent(four_index));
                 
    // Set up different sequences of callouts on different handles.
    CalloutHandle callout_handle(getLibraryHandleCollection());
    int status;

    // Each library contributing one callout on hook "one".
    callout_value_ = 0;
    getLibraryHandle(0)->registerCallout("one", collection_one);
    getLibraryHandle(1)->registerCallout("one", collection_two);
    getLibraryHandle(2)->registerCallout("one", collection_three);
    getLibraryHandle(3)->registerCallout("one", collection_four);
    status = getLibraryHandleCollection()->callCallouts(one_index,
                                                        callout_handle);
    EXPECT_EQ(0, status);
    EXPECT_EQ(1234, callout_value_);

    // Do a random selection of callouts on hook "two".
    callout_value_ = 0;
    getLibraryHandle(0)->registerCallout("two", collection_one);
    getLibraryHandle(0)->registerCallout("two", collection_one);
    getLibraryHandle(1)->registerCallout("two", collection_two);
    getLibraryHandle(3)->registerCallout("two", collection_four);
    status = getLibraryHandleCollection()->callCallouts(two_index,
                                                        callout_handle);
    EXPECT_EQ(0, status);
    EXPECT_EQ(1124, callout_value_);

    // Ensure that calling the callouts on a hook with no callouts works,
    // even though it does not return any value.
    callout_value_ = 0;
    status = getLibraryHandleCollection()->callCallouts(three_index,
                                                        callout_handle);
    EXPECT_EQ(0, status);
    EXPECT_EQ(0, callout_value_);
}

// Test that the callouts are called in order, but not after a callout
// returing an error code.

TEST_F(LibraryHandleCollectionTest, CallCalloutsError) {
    const int one_index = getServerHooks()->getIndex("one");
    const int two_index = getServerHooks()->getIndex("two");
    const int three_index = getServerHooks()->getIndex("three");
    const int four_index = getServerHooks()->getIndex("four");

    // Ensure that no callouts are attached to any of the hooks.
    EXPECT_FALSE(getLibraryHandleCollection()->calloutsPresent(one_index));
    EXPECT_FALSE(getLibraryHandleCollection()->calloutsPresent(two_index));
    EXPECT_FALSE(getLibraryHandleCollection()->calloutsPresent(three_index));
    EXPECT_FALSE(getLibraryHandleCollection()->calloutsPresent(four_index));
                 
    // Set up different sequences of callouts on different handles.
    CalloutHandle callout_handle(getLibraryHandleCollection());
    int status;

    // Each library contributing one callout on hook "one". First callout
    // returns an error.
    callout_value_ = 0;
    getLibraryHandle(0)->registerCallout("one", collection_one_error);
    getLibraryHandle(1)->registerCallout("one", collection_two);
    getLibraryHandle(2)->registerCallout("one", collection_three);
    getLibraryHandle(3)->registerCallout("one", collection_four);
    status = getLibraryHandleCollection()->callCallouts(one_index,
                                                        callout_handle);
    EXPECT_EQ(1, status);
    EXPECT_EQ(1, callout_value_);

    // Each library contributing multiple callouts on hook "two". Last callout
    // on first library returns an error after updating the value.
    callout_value_ = 0;
    getLibraryHandle(0)->registerCallout("two", collection_one);
    getLibraryHandle(0)->registerCallout("two", collection_one_error);
    getLibraryHandle(1)->registerCallout("two", collection_two);
    getLibraryHandle(1)->registerCallout("two", collection_two);
    getLibraryHandle(1)->registerCallout("two", collection_three);
    getLibraryHandle(1)->registerCallout("two", collection_three);
    getLibraryHandle(3)->registerCallout("two", collection_four);
    getLibraryHandle(3)->registerCallout("two", collection_four);
    status = getLibraryHandleCollection()->callCallouts(two_index,
                                                        callout_handle);
    EXPECT_EQ(1, status);
    EXPECT_EQ(11, callout_value_);

    // Random callout returns an error.
    callout_value_ = 0;
    getLibraryHandle(0)->registerCallout("three", collection_one);
    getLibraryHandle(0)->registerCallout("three", collection_one);
    getLibraryHandle(1)->registerCallout("three", collection_two);
    getLibraryHandle(1)->registerCallout("three", collection_two);
    getLibraryHandle(3)->registerCallout("three", collection_four_error);
    getLibraryHandle(3)->registerCallout("three", collection_four);
    status = getLibraryHandleCollection()->callCallouts(three_index,
                                                        callout_handle);
    EXPECT_EQ(1, status);
    EXPECT_EQ(11224, callout_value_);

    // Last callout returns an error.
    callout_value_ = 0;
    getLibraryHandle(0)->registerCallout("four", collection_one);
    getLibraryHandle(0)->registerCallout("four", collection_one);
    getLibraryHandle(1)->registerCallout("four", collection_two);
    getLibraryHandle(1)->registerCallout("four", collection_two);
    getLibraryHandle(2)->registerCallout("four", collection_three);
    getLibraryHandle(2)->registerCallout("four", collection_three);
    getLibraryHandle(3)->registerCallout("four", collection_four);
    getLibraryHandle(3)->registerCallout("four", collection_four_error);
    status = getLibraryHandleCollection()->callCallouts(four_index,
                                                        callout_handle);
    EXPECT_EQ(1, status);
    EXPECT_EQ(11223344, callout_value_);
}

// Same test as CallCalloutsSucess, but with functions returning a "skip"
// instead.

TEST_F(LibraryHandleCollectionTest, CallCalloutsSkip) {
    const int one_index = getServerHooks()->getIndex("one");
    const int two_index = getServerHooks()->getIndex("two");
    const int three_index = getServerHooks()->getIndex("three");
    const int four_index = getServerHooks()->getIndex("four");

    // Ensure that no callouts are attached to any of the hooks.
    EXPECT_FALSE(getLibraryHandleCollection()->calloutsPresent(one_index));
    EXPECT_FALSE(getLibraryHandleCollection()->calloutsPresent(two_index));
    EXPECT_FALSE(getLibraryHandleCollection()->calloutsPresent(three_index));
    EXPECT_FALSE(getLibraryHandleCollection()->calloutsPresent(four_index));
                 
    // Set up different sequences of callouts on different handles.
    CalloutHandle callout_handle(getLibraryHandleCollection());
    int status;

    // Each library contributing one callout on hook "one". First callout
    // returns an error.
    callout_value_ = 0;
    getLibraryHandle(0)->registerCallout("one", collection_one_skip);
    getLibraryHandle(1)->registerCallout("one", collection_two);
    getLibraryHandle(2)->registerCallout("one", collection_three);
    getLibraryHandle(3)->registerCallout("one", collection_four);
    status = getLibraryHandleCollection()->callCallouts(one_index,
                                                        callout_handle);
    EXPECT_EQ(0, status);
    EXPECT_EQ(1, callout_value_);

    // Each library contributing multiple callouts on hook "two". Last callout
    // on first library returns an error after updating the value.
    callout_value_ = 0;
    getLibraryHandle(0)->registerCallout("two", collection_one);
    getLibraryHandle(0)->registerCallout("two", collection_one_skip);
    getLibraryHandle(1)->registerCallout("two", collection_two);
    getLibraryHandle(1)->registerCallout("two", collection_two);
    getLibraryHandle(1)->registerCallout("two", collection_three);
    getLibraryHandle(1)->registerCallout("two", collection_three);
    getLibraryHandle(3)->registerCallout("two", collection_four);
    getLibraryHandle(3)->registerCallout("two", collection_four);
    status = getLibraryHandleCollection()->callCallouts(two_index,
                                                        callout_handle);
    EXPECT_EQ(0, status);
    EXPECT_EQ(11, callout_value_);

    // Random callout returns an error.
    callout_value_ = 0;
    getLibraryHandle(0)->registerCallout("three", collection_one);
    getLibraryHandle(0)->registerCallout("three", collection_one);
    getLibraryHandle(1)->registerCallout("three", collection_two);
    getLibraryHandle(1)->registerCallout("three", collection_two);
    getLibraryHandle(3)->registerCallout("three", collection_four_skip);
    getLibraryHandle(3)->registerCallout("three", collection_four);
    status = getLibraryHandleCollection()->callCallouts(three_index,
                                                        callout_handle);
    EXPECT_EQ(0, status);
    EXPECT_EQ(11224, callout_value_);

    // Last callout returns an error.
    callout_value_ = 0;
    getLibraryHandle(0)->registerCallout("four", collection_one);
    getLibraryHandle(0)->registerCallout("four", collection_one);
    getLibraryHandle(1)->registerCallout("four", collection_two);
    getLibraryHandle(1)->registerCallout("four", collection_two);
    getLibraryHandle(2)->registerCallout("four", collection_three);
    getLibraryHandle(2)->registerCallout("four", collection_three);
    getLibraryHandle(3)->registerCallout("four", collection_four);
    getLibraryHandle(3)->registerCallout("four", collection_four_skip);
    status = getLibraryHandleCollection()->callCallouts(four_index,
                                                        callout_handle);
    EXPECT_EQ(0, status);
    EXPECT_EQ(11223344, callout_value_);
}

} // Anonymous namespace
