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

#include <util/hooks/callout_handles.h>
#include <util/hooks/server_hooks.h>

#include <gtest/gtest.h>

using namespace isc::util;
using namespace std;

namespace {

class CalloutHandlesTest : public ::testing::Test {
public:
    /// @brief Constructor
    ///
    /// Sets up an appropriate number of server hooks to pass to the
    /// constructed callout handle objects.
    CalloutHandlesTest() : hooks_(new ServerHooks()) {
        hooks_->registerHook("alpha");
        hooks_->registerHook("beta");
        hooks_->registerHook("gamma");
    }

    /// Obtain constructed server hooks
    boost::shared_ptr<ServerHooks> getServerHooks() {
        return (hooks_);
    }

private:
    boost::shared_ptr<ServerHooks> hooks_;
};

// Test that we can store multiple values of the same type and that they
// are distinct.

TEST_F(CalloutHandlesTest, ContextDistinctSimpleType) {
    LibraryHandle handle(getServerHooks(), 1);

    // Store and retrieve an int (random value).
    int a = 42;
    handle.setContext("integer1", a);
    EXPECT_EQ(42, a);

    int b = 0;
    handle.getContext("integer1", b);
    EXPECT_EQ(42, b);

    // Add another integer (another random value).
    int c = 142;
    handle.setContext("integer2", c);
    EXPECT_EQ(142, c);

    int d = -1;
    handle.getContext("integer2", d);
    EXPECT_EQ(142, d);

    // Add a short (random value).
    short e = 81; 
    handle.setContext("short", e);
    EXPECT_EQ(81, e);

    short f = -1;
    handle.getContext("short", f);
    EXPECT_EQ(81, f);
}

// Test that trying to get something with an incorrect name throws an
// exception.

TEST_F(CalloutHandlesTest, ContextUnknownName) {
    LibraryHandle handle(getServerHooks(), 1);

    // Set an integer
    int a = 42;
    handle.setContext("integer1", a);
    EXPECT_EQ(42, a);

    // Check we can retrieve it
    int b = 0;
    handle.getContext("integer1", b);
    EXPECT_EQ(42, b);

    // Check that getting an unknown name throws an exception.
    int c = -1;
    EXPECT_THROW(handle.getContext("unknown", c), NoSuchContext);
}

// Test that trying to get something with an incorrect type throws an exception.

TEST_F(CalloutHandlesTest, ContextIncorrectType) {
    LibraryHandle handle(getServerHooks(), 1);

    // Set an integer
    int a = 42;
    handle.setContext("integer1", a);
    EXPECT_EQ(42, a);

    // Check we can retrieve it
    long b = 0;
    EXPECT_THROW(handle.getContext("integer1", b), boost::bad_any_cast);
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

TEST_F(CalloutHandlesTest, ComplexTypes) {
    LibraryHandle handle(getServerHooks(), 1);

    // Declare two variables of different (complex) types. (Note as to the
    // variable names: aleph and beth are the first two letters of the Hebrew
    // alphabet.)
    Alpha aleph(1, 2);
    EXPECT_EQ(1, aleph.a);
    EXPECT_EQ(2, aleph.b);
    handle.setContext("aleph", aleph);

    Beta beth(11, 22);
    EXPECT_EQ(11, beth.c);
    EXPECT_EQ(22, beth.d);
    handle.setContext("beth", beth);

    // Ensure we can extract the data correctly
    Alpha aleph2;
    EXPECT_EQ(0, aleph2.a);
    EXPECT_EQ(0, aleph2.b);
    handle.getContext("aleph", aleph2);
    EXPECT_EQ(1, aleph2.a);
    EXPECT_EQ(2, aleph2.b);

    Beta beth2;
    EXPECT_EQ(0, beth2.c);
    EXPECT_EQ(0, beth2.d);
    handle.getContext("beth", beth2);
    EXPECT_EQ(11, beth2.c);
    EXPECT_EQ(22, beth2.d);

    // Ensure that complex types also thrown an exception if we attempt to
    // get a context element of the wrong type.
    EXPECT_THROW(handle.getContext("aleph", beth), boost::bad_any_cast);
}

// Check that the context can store pointers. And also check that it respects
// that a "pointer to X" is not the same as a "pointer to const X".

TEST_F(CalloutHandlesTest, PointerTypes) {
    LibraryHandle handle(getServerHooks(), 1);

    // Declare a couple of variables, const and non-const.
    Alpha aleph(5, 10);
    const Beta beth(15, 20);

    Alpha* pa = &aleph;
    const Beta* pcb = &beth;

    // Check pointers can be set and retrieved OK
    handle.setContext("non_const_pointer", pa);
    handle.setContext("const_pointer", pcb);

    Alpha* pa2 = 0;
    handle.getContext("non_const_pointer", pa2);
    EXPECT_TRUE(pa == pa2);

    const Beta* pcb2 = 0;
    handle.getContext("const_pointer", pcb2);
    EXPECT_TRUE(pcb == pcb2);

    // Check that the "const" is protected in the context.
    const Alpha* pca3;
    EXPECT_THROW(handle.getContext("non_const_pointer", pca3),
                 boost::bad_any_cast);

    Beta* pb3;
    EXPECT_THROW(handle.getContext("const_pointer", pb3),
                 boost::bad_any_cast);
}

} // Anonymous namespace
