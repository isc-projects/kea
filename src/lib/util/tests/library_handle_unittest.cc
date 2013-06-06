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

#include <util/hooks/callout_handle.h>
#include <util/hooks/library_handle.h>
#include <util/hooks/server_hooks.h>

#include <gtest/gtest.h>

#include <algorithm>
#include <string>
#include <vector>

using namespace isc::util;
using namespace std;

namespace {

class LibraryHandleTest : public ::testing::Test {
public:
    /// @brief Constructor
    ///
    /// Sets up an appropriate number of server hooks to pass to the
    /// constructed callout handle objects.
    LibraryHandleTest()
        : hooks_(new ServerHooks()),
          collection_(new LibraryHandleCollection()) {
        hooks_->registerHook("alpha");
        hooks_->registerHook("beta");
        hooks_->registerHook("gamma");

        // Also initialize the variable used to pass information back from the
        // callouts to the tests.
        callout_value = 0;
    }

    /// Obtain constructed server hooks.
    boost::shared_ptr<ServerHooks>& getServerHooks() {
        return (hooks_);
    }

    /// Obtain constructed hook manager.
    boost::shared_ptr<LibraryHandleCollection>& getLibraryHandleCollection() {
        return (collection_);
    }

    /// Variable for callouts test. This is public and static to allow non-
    /// member functions to access it.  It is initialized every time a new
    /// test starts.
    static int callout_value;

private:
    boost::shared_ptr<ServerHooks> hooks_;
    boost::shared_ptr<LibraryHandleCollection> collection_;
};

// Definition of the static variable.
int LibraryHandleTest::callout_value = 0;

// The next set of tests check that callouts can be registered.

// The callouts defined here are structured in such a way that it is possible
// to determine the order in which they are called and whether they are called
// at all. The method used is simple - after a sequence of callouts, the digits
// in the value, reading left to right, determines the order of the callouts
// called.  For example, callout one followed by two followed by three followed
// by two followed by one results in a value of 12321.
//
// Functions return a zero to indicate success.

extern "C" {
int one(CalloutHandle&) {
    LibraryHandleTest::callout_value =
        10 * LibraryHandleTest::callout_value + 1;
    return (0);
}

int two(CalloutHandle&) {
    LibraryHandleTest::callout_value =
        10 * LibraryHandleTest::callout_value + 2;
    return (0);
}

int three(CalloutHandle&) {
    LibraryHandleTest::callout_value =
        10 * LibraryHandleTest::callout_value + 3;
    return (0);
}

// The next function is a duplicate of "one", but returns an error status.

int one_error(CalloutHandle& handle) {
    static_cast<void>(one(handle));
    return (1);
}

// The next function is a duplicate of "one", but sets the skip flag.

int one_skip(CalloutHandle& handle) {
    handle.setSkip(true);
    return (one(handle));
}

};  // extern "C"

// Check that we can register callouts on a particular hook.

TEST_F(LibraryHandleTest, RegisterSingleCallout) {
    LibraryHandle handle(getServerHooks());

    // Register callouts for hooks alpha and see that it is registered.
    EXPECT_FALSE(handle.calloutsPresent(getServerHooks()->getIndex("alpha")));
    handle.registerCallout("alpha", one);
    EXPECT_TRUE(handle.calloutsPresent(getServerHooks()->getIndex("alpha")));

    // Do the same for beta (which checks that the hooks are independent).
    EXPECT_FALSE(handle.calloutsPresent(getServerHooks()->getIndex("beta")));
    handle.registerCallout("beta", one);
    EXPECT_TRUE(handle.calloutsPresent(getServerHooks()->getIndex("beta")));
}

// Check that we can call a single callout on a particular hook.  Refer to the
// above definition of the callouts "one" and "two" to understand the expected
// return values.

TEST_F(LibraryHandleTest, CallSingleCallout) {
    LibraryHandle handle(getServerHooks());

    // Register callout for hook alpha...
    EXPECT_FALSE(handle.calloutsPresent(getServerHooks()->getIndex("alpha")));
    handle.registerCallout("alpha", one);
    EXPECT_TRUE(handle.calloutsPresent(getServerHooks()->getIndex("alpha")));

    // Call it.
    EXPECT_EQ(0, LibraryHandleTest::callout_value);

    int index = getServerHooks()->getIndex("alpha");
    CalloutHandle callout_handle(getLibraryHandleCollection());
    int status = handle.callCallouts(index, callout_handle);

    EXPECT_EQ(0, status);
    EXPECT_EQ(1, LibraryHandleTest::callout_value);

}

// Check that we can register two callouts for a hook and that they are called
// in order.

TEST_F(LibraryHandleTest, TwoCallouts) {
    LibraryHandle handle(getServerHooks());

    // Register two callouts for hook alpha.
    handle.registerCallout("alpha", one);
    handle.registerCallout("alpha", two);

    // Call them.
    EXPECT_EQ(0, LibraryHandleTest::callout_value);

    int index = getServerHooks()->getIndex("alpha");
    CalloutHandle callout_handle(getLibraryHandleCollection());
    int status = handle.callCallouts(index, callout_handle);

    EXPECT_EQ(0, status);
    EXPECT_EQ(12, LibraryHandleTest::callout_value);
}

// Check that we can register two callouts for a hook and that the second is not
// called if the first returns a non-zero status.

TEST_F(LibraryHandleTest, TwoCalloutsWithError) {
    LibraryHandle handle(getServerHooks());

    // Register callout for hook alpha...
    handle.registerCallout("alpha", one_error);
    handle.registerCallout("alpha", two);

    // Call them.
    EXPECT_EQ(0, LibraryHandleTest::callout_value);

    int index = getServerHooks()->getIndex("alpha");
    CalloutHandle callout_handle(getLibraryHandleCollection());
    int status = handle.callCallouts(index, callout_handle);

    EXPECT_EQ(1, status);
    EXPECT_EQ(1, LibraryHandleTest::callout_value);
}

// Check that we can register two callouts for a hook and that the second is not
// called if the first szets the callout "skip" flag.

TEST_F(LibraryHandleTest, TwoCalloutsWithSkip) {
    LibraryHandle handle(getServerHooks());

    // Register callout for hook alpha.
    handle.registerCallout("alpha", one_skip);
    handle.registerCallout("alpha", two);

    // Call them.
    EXPECT_EQ(0, LibraryHandleTest::callout_value);

    int index = getServerHooks()->getIndex("alpha");
    CalloutHandle callout_handle(getLibraryHandleCollection());
    int status = handle.callCallouts(index, callout_handle);

    EXPECT_EQ(0, status);
    EXPECT_EQ(1, LibraryHandleTest::callout_value);
}

// Check that a callout can be registered more than once.

TEST_F(LibraryHandleTest, MultipleRegistration) {
    LibraryHandle handle(getServerHooks());

    // Register callouts for hook alpha.
    handle.registerCallout("alpha", one);
    handle.registerCallout("alpha", two);
    handle.registerCallout("alpha", one);

    // Call them.
    EXPECT_EQ(0, LibraryHandleTest::callout_value);

    int index = getServerHooks()->getIndex("alpha");
    CalloutHandle callout_handle(getLibraryHandleCollection());
    int status = handle.callCallouts(index, callout_handle);

    EXPECT_EQ(0, status);
    EXPECT_EQ(121, LibraryHandleTest::callout_value);
}

// Check that a callout can be deregistered.

TEST_F(LibraryHandleTest, Deregister) {
    LibraryHandle handle(getServerHooks());

    // Register callouts for hook alpha...
    handle.registerCallout("alpha", one);
    handle.registerCallout("alpha", two);
    handle.registerCallout("alpha", one);

    // Get rid of all the "one" callbacks.
    handle.deregisterCallout("alpha", one);

    // Call it.
    EXPECT_EQ(0, LibraryHandleTest::callout_value);

    int index = getServerHooks()->getIndex("alpha");
    CalloutHandle callout_handle(getLibraryHandleCollection());
    int status = handle.callCallouts(index, callout_handle);

    EXPECT_EQ(0, status);
    EXPECT_EQ(2, LibraryHandleTest::callout_value);
}

// Check that all callouts can be deregistered.

TEST_F(LibraryHandleTest, DeregisterAll) {
    LibraryHandle handle(getServerHooks());

    // Register callouts for hook alpha...
    EXPECT_FALSE(handle.calloutsPresent(getServerHooks()->getIndex("alpha")));
    handle.registerCallout("alpha", one);
    handle.registerCallout("alpha", two);
    EXPECT_TRUE(handle.calloutsPresent(getServerHooks()->getIndex("alpha")));

    // ... and remove them.
    handle.deregisterAll("alpha");
    EXPECT_FALSE(handle.calloutsPresent(getServerHooks()->getIndex("alpha")));
}

// Add checks that invalid names etc. all throw.  With the base hooks added
// by the constructor, there are five valid hooks, with valid indexes 0 to 4.

TEST_F(LibraryHandleTest, InvalidNameAndIndex) {
    LibraryHandle handle(getServerHooks());

    EXPECT_THROW(handle.registerCallout("omega", one), NoSuchHook);
    EXPECT_THROW(handle.deregisterCallout("omega", one), NoSuchHook);
    EXPECT_THROW(handle.deregisterAll("omega"), NoSuchHook);

    EXPECT_THROW(static_cast<void>(handle.calloutsPresent(-1)), NoSuchHook);
    EXPECT_THROW(static_cast<void>(handle.calloutsPresent(5)), NoSuchHook);

    CalloutHandle callout_handle(getLibraryHandleCollection());
    EXPECT_THROW(static_cast<void>(handle.callCallouts(-1, callout_handle)),
                 NoSuchHook);
    EXPECT_THROW(static_cast<void>(handle.callCallouts(10, callout_handle)),
                 NoSuchHook);
}


} // Anonymous namespace
