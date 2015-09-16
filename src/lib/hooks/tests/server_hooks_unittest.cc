// Copyright (C) 2013, 2015  Internet Systems Consortium, Inc. ("ISC")
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
    ServerHooks& hooks = ServerHooks::getServerHooks();
    hooks.reset();

    // Ensure we can't duplicate one of the existing names.
    EXPECT_THROW(hooks.registerHook("context_create"), DuplicateHook);

    // Check we can't duplicate a newly registered hook.
    int gamma = hooks.registerHook("gamma");
    EXPECT_EQ(2, gamma);
    EXPECT_THROW(hooks.registerHook("gamma"), DuplicateHook);
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

} // Anonymous namespace
