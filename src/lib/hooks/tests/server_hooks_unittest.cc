// Copyright (C) 2013-2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <hooks/server_hooks.h>

#include <gtest/gtest.h>

#include <algorithm>
#include <string>
#include <vector>

using namespace isc;
using namespace isc::hooks;
using namespace std;

namespace {

// Checks the registration of hooks and the interrogation methods.  As the
// constructor registers two hooks, this is also a test of the constructor.

TEST(ServerHooksTest, RegisterHooks) {
    ServerHooks& hooks = ServerHooks::getServerHooks();
    hooks.reset();

    // There should be two hooks already registered, with indexes 0 and 1.
    EXPECT_EQ(2, hooks.getCount());
    EXPECT_EQ(0, hooks.getIndex("context_create"));
    EXPECT_EQ(0, hooks.findIndex("context_create"));
    EXPECT_EQ(1, hooks.getIndex("context_destroy"));
    EXPECT_EQ(1, hooks.findIndex("context_destroy"));

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
// This test has been updated. See #5251 for details. The old
// code is retained in case we decide to get back to it.
TEST(ServerHooksTest, DISABLED_OldDuplicateHooks) {
    ServerHooks& hooks = ServerHooks::getServerHooks();
    hooks.reset();

    // Ensure we can't duplicate one of the existing names.
    EXPECT_THROW(hooks.registerHook("context_create"), DuplicateHook);

    // Check we can't duplicate a newly registered hook.
    int gamma = hooks.registerHook("gamma");
    EXPECT_EQ(2, gamma);
    EXPECT_THROW(hooks.registerHook("gamma"), DuplicateHook);
}

// Check that duplicate names are handled properly. The code used to throw,
// but it now returns the existing index. See #5251 for details.
TEST(ServerHooksTest, NewDuplicateHooks) {
    ServerHooks& hooks = ServerHooks::getServerHooks();
    hooks.reset();

    int index = hooks.getIndex("context_create");

    // Ensure we can duplicate one of the existing names.
    // Instead of throwing, we just check that a reasonable
    // index has been returned.
    EXPECT_EQ(index, hooks.registerHook("context_create"));

    // Check that mutiple attempts to register the same hook will return
    // existing index.
    int gamma = hooks.registerHook("gamma");
    EXPECT_EQ(2, gamma);
    EXPECT_EQ(gamma, hooks.registerHook("gamma"));
    EXPECT_EQ(gamma, hooks.registerHook("gamma"));
    EXPECT_EQ(gamma, hooks.registerHook("gamma"));
    EXPECT_EQ(gamma, hooks.registerHook("gamma"));
}

// Checks that we can get the name of the hooks.

TEST(ServerHooksTest, GetHookNames) {
    ServerHooks& hooks = ServerHooks::getServerHooks();
    hooks.reset();
    vector<string> expected_names;

    // Add names into the hooks object and to the set of expected names.
    expected_names.push_back("alpha");
    expected_names.push_back("beta");
    expected_names.push_back("gamma");
    expected_names.push_back("delta");
    for (size_t i = 0; i < expected_names.size(); ++i) {
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

// Test the inverse hooks functionality (i.e. given an index, get the name).

TEST(ServerHooksTest, GetHookIndexes) {
    ServerHooks& hooks = ServerHooks::getServerHooks();
    hooks.reset();

    int alpha = hooks.registerHook("alpha");
    int beta = hooks.registerHook("beta");
    int gamma = hooks.registerHook("gamma");

    EXPECT_EQ(std::string("context_create"),
              hooks.getName(ServerHooks::CONTEXT_CREATE));
    EXPECT_EQ(std::string("context_destroy"),
              hooks.getName(ServerHooks::CONTEXT_DESTROY));
    EXPECT_EQ(std::string("alpha"), hooks.getName(alpha));
    EXPECT_EQ(std::string("beta"), hooks.getName(beta));
    EXPECT_EQ(std::string("gamma"), hooks.getName(gamma));

    // Check for an invalid index
    EXPECT_THROW(hooks.getName(-1), NoSuchHook);
    EXPECT_THROW(hooks.getName(42), NoSuchHook);
}

// Test the reset functionality.

TEST(ServerHooksTest, Reset) {
    ServerHooks& hooks = ServerHooks::getServerHooks();
    hooks.reset();

    int alpha = hooks.registerHook("alpha");
    int beta = hooks.registerHook("beta");
    int gamma = hooks.registerHook("gamma");

    EXPECT_EQ(std::string("alpha"), hooks.getName(alpha));
    EXPECT_EQ(std::string("beta"), hooks.getName(beta));
    EXPECT_EQ(std::string("gamma"), hooks.getName(gamma));

    // Check the counts before and after a reset.
    EXPECT_EQ(5, hooks.getCount());
    hooks.reset();
    EXPECT_EQ(2, hooks.getCount());

    // ... and check that the hooks are as expected.
    EXPECT_EQ(0, hooks.getIndex("context_create"));
    EXPECT_EQ(1, hooks.getIndex("context_destroy"));
}

// Check that getting an unknown name throws an exception.

TEST(ServerHooksTest, UnknownHookName) {
    ServerHooks& hooks = ServerHooks::getServerHooks();
    hooks.reset();

    EXPECT_THROW(static_cast<void>(hooks.getIndex("unknown")), NoSuchHook);
    EXPECT_EQ(-1, hooks.findIndex("unknown"));
}

// Check that the count of hooks is correct.

TEST(ServerHooksTest, HookCount) {
    ServerHooks& hooks = ServerHooks::getServerHooks();
    hooks.reset();

    // Insert the names into the hooks object
    hooks.registerHook("alpha");
    hooks.registerHook("beta");
    hooks.registerHook("gamma");
    hooks.registerHook("delta");

    // Should be two more hooks that the number we have registered.
    EXPECT_EQ(6, hooks.getCount());
}

// Check that the hook name is correctly generated for a control command name
// and vice versa.

TEST(ServerHooksTest, CommandToHookName) {
    EXPECT_EQ("$x_y_z", ServerHooks::commandToHookName("x-y-z"));
    EXPECT_EQ("$foo_bar_foo", ServerHooks::commandToHookName("foo-bar_foo"));
    EXPECT_EQ("$", ServerHooks::commandToHookName(""));
}

TEST(ServerHooksTest, HookToCommandName) {
    // Underscores replaced by hyphens.
    EXPECT_EQ("x-y-z", ServerHooks::hookToCommandName("$x_y_z"));
    EXPECT_EQ("foo-bar-foo", ServerHooks::hookToCommandName("$foo_bar-foo"));
    // Single dollar is converted to empty string.
    EXPECT_TRUE(ServerHooks::hookToCommandName("$").empty());
    // If no dollar, it is not a hook name. Return empty string.
    EXPECT_TRUE(ServerHooks::hookToCommandName("abc").empty());
}

TEST(ServerHooksTest, getParkingLots) {
    ServerHooks& hooks = ServerHooks::getServerHooks();
    hooks.reset();
    int alpha_hook = hooks.registerHook("alpha");

    ASSERT_TRUE(hooks.getParkingLotsPtr());
    ASSERT_TRUE(hooks.getParkingLotPtr(alpha_hook));
    ASSERT_TRUE(hooks.getParkingLotPtr("alpha"));
}

} // Anonymous namespace
