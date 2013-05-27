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

#include <boost/shared_ptr.hpp>

#include <gtest/gtest.h>

using namespace isc::util;
using namespace std;

// Dummy class for testing
namespace isc {
namespace util {
class HookManager {
public:
    HookManager() {}
};
}
}

using namespace isc::util;
using namespace std;

namespace {

class CalloutHandleTest : public ::testing::Test {
public:
    /// @brief Constructor
    ///
    /// Sets up an appropriate number of server hooks to pass to the
    /// constructed callout handle objects.
    CalloutHandleTest() : manager_(new HookManager()) {
    }

    /// Obtain hook manager
    boost::shared_ptr<HookManager>& getHookManager() {
        return (manager_);
    }

private:
    boost::shared_ptr<HookManager> manager_;
};

// *** Argument Tests ***
//
// The first set of tests check that the CalloutHandle can store and retrieve
// arguments.  These are very similar to the LibraryHandle context tests.

// Test that we can store multiple values of the same type and that they
// are distinct.

TEST_F(CalloutHandleTest, ArgumentDistinctSimpleType) {
    CalloutHandle handle(getHookManager());

    // Store and retrieve an int (random value).
    int a = 42;
    handle.setArgument("integer1", a);
    EXPECT_EQ(42, a);

    int b = 0;
    handle.getArgument("integer1", b);
    EXPECT_EQ(42, b);

    // Add another integer (another random value).
    int c = 142;
    handle.setArgument("integer2", c);
    EXPECT_EQ(142, c);

    int d = -1;
    handle.getArgument("integer2", d);
    EXPECT_EQ(142, d);

    // Add a short (random value).
    short e = 81; 
    handle.setArgument("short", e);
    EXPECT_EQ(81, e);

    short f = -1;
    handle.getArgument("short", f);
    EXPECT_EQ(81, f);
}

// Test that trying to get something with an incorrect name throws an
// exception.

TEST_F(CalloutHandleTest, ArgumentUnknownName) {
    CalloutHandle handle(getHookManager());

    // Set an integer
    int a = 42;
    handle.setArgument("integer1", a);
    EXPECT_EQ(42, a);

    // Check we can retrieve it
    int b = 0;
    handle.getArgument("integer1", b);
    EXPECT_EQ(42, b);

    // Check that getting an unknown name throws an exception.
    int c = -1;
    EXPECT_THROW(handle.getArgument("unknown", c), NoSuchArgument);
}

// Test that trying to get something with an incorrect type throws an exception.

TEST_F(CalloutHandleTest, ArgumentIncorrectType) {
    CalloutHandle handle(getHookManager());

    // Set an integer
    int a = 42;
    handle.setArgument("integer1", a);
    EXPECT_EQ(42, a);

    // Check we can retrieve it
    long b = 0;
    EXPECT_THROW(handle.getArgument("integer1", b), boost::bad_any_cast);
}

// Now try with some very complex types.  The types cannot be defined within
// the function and they should contain a copy constructor.  For this reason,
// a simple "struct" is used.

struct Alpha {
    int a;
    int b;
    Alpha(int first = 0, int second = 0) : a(first), b(second) {}
};

struct Beta {
    int c;
    int d;
    Beta(int first = 0, int second = 0) : c(first), d(second) {}
};

TEST_F(CalloutHandleTest, ComplexTypes) {
    CalloutHandle handle(getHookManager());

    // Declare two variables of different (complex) types. (Note as to the
    // variable names: aleph and beth are the first two letters of the Hebrew
    // alphabet.)
    Alpha aleph(1, 2);
    EXPECT_EQ(1, aleph.a);
    EXPECT_EQ(2, aleph.b);
    handle.setArgument("aleph", aleph);

    Beta beth(11, 22);
    EXPECT_EQ(11, beth.c);
    EXPECT_EQ(22, beth.d);
    handle.setArgument("beth", beth);

    // Ensure we can extract the data correctly
    Alpha aleph2;
    EXPECT_EQ(0, aleph2.a);
    EXPECT_EQ(0, aleph2.b);
    handle.getArgument("aleph", aleph2);
    EXPECT_EQ(1, aleph2.a);
    EXPECT_EQ(2, aleph2.b);

    Beta beth2;
    EXPECT_EQ(0, beth2.c);
    EXPECT_EQ(0, beth2.d);
    handle.getArgument("beth", beth2);
    EXPECT_EQ(11, beth2.c);
    EXPECT_EQ(22, beth2.d);

    // Ensure that complex types also thrown an exception if we attempt to
    // get a context element of the wrong type.
    EXPECT_THROW(handle.getArgument("aleph", beth), boost::bad_any_cast);
}

// Check that the context can store pointers. And also check that it respects
// that a "pointer to X" is not the same as a "pointer to const X".

TEST_F(CalloutHandleTest, PointerTypes) {
    CalloutHandle handle(getHookManager());

    // Declare a couple of variables, const and non-const.
    Alpha aleph(5, 10);
    const Beta beth(15, 20);

    Alpha* pa = &aleph;
    const Beta* pcb = &beth;

    // Check pointers can be set and retrieved OK
    handle.setArgument("non_const_pointer", pa);
    handle.setArgument("const_pointer", pcb);

    Alpha* pa2 = 0;
    handle.getArgument("non_const_pointer", pa2);
    EXPECT_TRUE(pa == pa2);

    const Beta* pcb2 = 0;
    handle.getArgument("const_pointer", pcb2);
    EXPECT_TRUE(pcb == pcb2);

    // Check that the "const" is protected in the context.
    const Alpha* pca3;
    EXPECT_THROW(handle.getArgument("non_const_pointer", pca3),
                 boost::bad_any_cast);

    Beta* pb3;
    EXPECT_THROW(handle.getArgument("const_pointer", pb3),
                 boost::bad_any_cast);
}

// Check that we can get the names of the arguments.

TEST_F(CalloutHandleTest, ContextItemNames) {
    CalloutHandle handle(getHookManager());

    vector<string> expected_names;
    int value = 42;

    expected_names.push_back("faith");
    handle.setArgument("faith", value++);
    expected_names.push_back("hope");
    handle.setArgument("hope", value++);
    expected_names.push_back("charity");
    handle.setArgument("charity", value++);

    // Get the names and check against the expected names.  We'll sort
    // both arrays to simplify the checking.
    vector<string> actual_names = handle.getArgumentNames();

    sort(actual_names.begin(), actual_names.end());
    sort(expected_names.begin(), expected_names.end());
    EXPECT_TRUE(expected_names == actual_names);
}

// Test that we can delete and argument.

TEST_F(CalloutHandleTest, DeleteArgument) {
    CalloutHandle handle(getHookManager());

    int one = 1;
    int two = 2;
    int three = 3;
    int four = 4;
    int value;      // Return value

    handle.setArgument("one", one);
    handle.setArgument("two", two);
    handle.setArgument("three", three);
    handle.setArgument("four", four);

    // Delete "one"
    handle.getArgument("one", value);
    EXPECT_EQ(1, value);
    handle.deleteArgument("one");

    EXPECT_THROW(handle.getArgument("one", value), NoSuchArgument);
    handle.getArgument("two", value);
    EXPECT_EQ(2, value);
    handle.getArgument("three", value);
    EXPECT_EQ(3, value);
    handle.getArgument("four", value);
    EXPECT_EQ(4, value);

    // Delete "three".
    handle.getArgument("three", value);
    EXPECT_EQ(3, value);
    handle.deleteArgument("three");

    EXPECT_THROW(handle.getArgument("one", value), NoSuchArgument);
    handle.getArgument("two", value);
    EXPECT_EQ(2, value);
    EXPECT_THROW(handle.getArgument("three", value), NoSuchArgument);
    handle.getArgument("four", value);
    EXPECT_EQ(4, value);
}

// Test that we can delete all arguments

TEST_F(CalloutHandleTest, DeleteAllArguments) {
    CalloutHandle handle(getHookManager());

    int one = 1;
    int two = 2;
    int three = 3;
    int four = 4;
    int value;      // Return value

    // Set the arguments.  The previous test verifies that this works.
    handle.setArgument("one", one);
    handle.setArgument("two", two);
    handle.setArgument("three", three);
    handle.setArgument("four", four);

    // Delete all arguments...
    handle.deleteAllArguments();

    // ... and check that none are left.
    EXPECT_THROW(handle.getArgument("one", value), NoSuchArgument);
    EXPECT_THROW(handle.getArgument("two", value), NoSuchArgument);
    EXPECT_THROW(handle.getArgument("three", value), NoSuchArgument);
    EXPECT_THROW(handle.getArgument("four", value), NoSuchArgument);
}

// Test the "skip" flag.

TEST_F(CalloutHandleTest, SkipFlag) {
    CalloutHandle handle(getHookManager());

    // Should be false on construction.
    EXPECT_FALSE(handle.getSkip());

    handle.setSkip(true);
    EXPECT_TRUE(handle.getSkip());

    handle.setSkip(false);
    EXPECT_FALSE(handle.getSkip());
}

} // Anonymous namespace
