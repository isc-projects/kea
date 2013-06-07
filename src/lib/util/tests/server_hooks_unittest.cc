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

#include <util/hooks/server_hooks.h>

#include <gtest/gtest.h>

#include <algorithm>
#include <string>
#include <vector>

using namespace isc;
using namespace isc::util;
using namespace std;

namespace {

// Checks the registration of hooks and the interrogation methods.  As the
// constructor registers two hooks, this is also a test of the constructor.

TEST(ServerHooksTest, RegisterHooks) {
    ServerHooks hooks;

    // There should be two hooks already registered, with indexes 0 and 1.
    EXPECT_EQ(2, hooks.getCount());
    EXPECT_EQ(0, hooks.getIndex("context_create"));
    EXPECT_EQ(1, hooks.getIndex("context_destroy"));

    // Check that the constants are as expected. (The intermediate variables
    // are used because of problems with g++ 4.6.1/Ubuntu 11.10 when resolving
    // the value of the ServerHooks constants when they appeared within the
    // gtest macro.)
    const int create_value = ServerHooks::CONTEXT_CREATE;
    const int destroy_value = ServerHooks::CONTEXT_DESTROY;
    EXPECT_EQ(0, create_value);
    EXPECT_EQ(1, destroy_value);

    // Register another couple of hooks.  The test on returned index is based
    // on knowledge that the hook indexes are assigned in ascending order.
    int alpha = hooks.registerHook("alpha");
    EXPECT_EQ(2, alpha);
    EXPECT_EQ(2, hooks.getIndex("alpha"));

    int beta = hooks.registerHook("beta");
    EXPECT_EQ(3, beta);
    EXPECT_EQ(3, hooks.getIndex("beta"));

    // Should be four hooks now
    EXPECT_EQ(4, hooks.getCount());
}

// Check that duplicate names cannot be registered.

TEST(ServerHooksTest, DuplicateHooks) {
    ServerHooks hooks;

    // Ensure we can't duplicate one of the existing names.
    EXPECT_THROW(hooks.registerHook("context_create"), DuplicateHook);

    // Check we can't duplicate a newly registered hook.
    int gamma = hooks.registerHook("gamma");
    EXPECT_EQ(2, gamma);
    EXPECT_THROW(hooks.registerHook("gamma"), DuplicateHook);
}

// Checks that we can get the name of the hooks.

TEST(ServerHooksTest, GetHookNames) {
    vector<string> expected_names;
    ServerHooks hooks;

    // Add names into the hooks object and to the set of expected names.
    expected_names.push_back("alpha");
    expected_names.push_back("beta");
    expected_names.push_back("gamma");
    expected_names.push_back("delta");
    for (int i = 0; i < expected_names.size(); ++i) {
        hooks.registerHook(expected_names[i].c_str());
    };

    // Update the expected names to include the pre-defined hook names.
    expected_names.push_back("context_create");
    expected_names.push_back("context_destroy");

    // Get the actual hook names
    vector<string> actual_names = hooks.getHookNames();

    // For comparison, sort the names into alphabetical order and do a straight
    // vector comparison.
    sort(expected_names.begin(), expected_names.end());
    sort(actual_names.begin(), actual_names.end());

    EXPECT_TRUE(expected_names == actual_names);
}

// Check that getting an unknown name throws an exception.

TEST(ServerHooksTest, UnknownHookName) {
    ServerHooks hooks;

    EXPECT_THROW(static_cast<void>(hooks.getIndex("unknown")), NoSuchHook);
}

// Check that the count of hooks is correct.

TEST(ServerHooksTest, HookCount) {
    ServerHooks hooks;

    // Insert the names into the hooks object
    hooks.registerHook("alpha");
    hooks.registerHook("beta");
    hooks.registerHook("gamma");
    hooks.registerHook("delta");

    // Should be two more hooks that the number we have registered.
    EXPECT_EQ(6, hooks.getCount());
}

// HookRegistrationFunction tests

// Declare some hook registration functions.

int alpha = 0;
int beta = 0;
int gamma = 0;
int delta = 0;

void registerAlphaBeta(ServerHooks& hooks) {
    alpha = hooks.registerHook("alpha");
    beta = hooks.registerHook("beta");
}

void registerGammaDelta(ServerHooks& hooks) {
    gamma = hooks.registerHook("gamma");
    delta = hooks.registerHook("delta");
}

// Add them to the registration vector.  This addition should happen before
// any tests are run, so we should start off with two functions in the
// registration vector.

HookRegistrationFunction f1(registerAlphaBeta);
HookRegistrationFunction f2(registerGammaDelta);

// This is not registered statically: it is used in the latter part of the
// test.

int epsilon = 0;
void registerEpsilon(ServerHooks& hooks) {
    epsilon = hooks.registerHook("epsilon");
}

// Test that the registration functions were defined and can be executed.

TEST(HookRegistrationFunction, Registration) {

    // The first part of the tests checks the static registration.  As there
    // is only one list of registration functions, we have to do this first
    // as the static registration is done outside our control, before the
    // tests are loaded.

    // Ensure that the hook numbers are initialized.
    EXPECT_EQ(0, alpha);
    EXPECT_EQ(0, beta);
    EXPECT_EQ(0, gamma);
    EXPECT_EQ(0, delta);

    // Should have two hook registration functions registered.
    EXPECT_EQ(2, HookRegistrationFunction::getFunctionVector().size());

    // Execute the functions and check that four new hooks were defined.

    ServerHooks hooks;
    EXPECT_EQ(2, hooks.getCount());
    HookRegistrationFunction::execute(hooks);
    EXPECT_EQ(6, hooks.getCount());

    // Check the hook names
    vector<string> names = hooks.getHookNames();
    ASSERT_EQ(6, names.size());
    sort(names.begin(), names.end());
    EXPECT_EQ(string("alpha"), names[0]);
    EXPECT_EQ(string("beta"), names[1]);
    EXPECT_EQ(string("context_create"), names[2]);
    EXPECT_EQ(string("context_destroy"), names[3]);
    EXPECT_EQ(string("delta"), names[4]);
    EXPECT_EQ(string("gamma"), names[5]);

    // Check that numbers in the range 2-5 inclusive were assigned as the
    // hook indexes (0 and 1 being reserved for context_create and
    // context_destroy).
    vector<int> indexes;
    indexes.push_back(alpha);
    indexes.push_back(beta);
    indexes.push_back(gamma);
    indexes.push_back(delta);
    sort(indexes.begin(), indexes.end());
    EXPECT_EQ(2, indexes[0]);
    EXPECT_EQ(3, indexes[1]);
    EXPECT_EQ(4, indexes[2]);
    EXPECT_EQ(5, indexes[3]);

    // One last check.  We'll test that the constructor of does indeed
    // add a function to the function vector and that the static initialization
    // was not somehow by chance.
    HookRegistrationFunction::getFunctionVector().clear();
    EXPECT_TRUE(HookRegistrationFunction::getFunctionVector().empty());
    epsilon = 0;

    // Register a single registration function.
    HookRegistrationFunction f3(registerEpsilon);
    EXPECT_EQ(1, HookRegistrationFunction::getFunctionVector().size());

    // Execute it and check that the hook was registered.
    ServerHooks hooks2;
    EXPECT_EQ(0, epsilon);
    EXPECT_EQ(2, hooks2.getCount());
    HookRegistrationFunction::execute(hooks2);

    // Should be three hooks, with the new one assigned an index of 2.
    names = hooks2.getHookNames();
    ASSERT_EQ(3, names.size());
    sort(names.begin(), names.end());
    EXPECT_EQ(string("context_create"), names[0]);
    EXPECT_EQ(string("context_destroy"), names[1]);
    EXPECT_EQ(string("epsilon"), names[2]);

    EXPECT_EQ(2, epsilon);
}

} // Anonymous namespace
