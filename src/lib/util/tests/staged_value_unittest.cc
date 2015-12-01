// Copyright (C) 2015 Internet Systems Consortium, Inc. ("ISC")
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

#include <config.h>
#include <util/staged_value.h>
#include <boost/shared_ptr.hpp>
#include <gtest/gtest.h>

namespace {

using namespace isc::util;

// This test verifies that the value can be assigned and committed.
TEST(StagedValueTest, assignAndCommit) {
    // Initally the value should be set to a default
    StagedValue<int> value;
    ASSERT_EQ(0, value.getValue());

    // Set the new value without committing it and make sure it
    // can be retrieved.
    value.setValue(4);
    ASSERT_EQ(4, value.getValue());

    // Commit the value and make sure it still can be retrieved.
    value.commit();
    ASSERT_EQ(4, value.getValue());

    // Set new value and retrieve it.
    value.setValue(10);
    ASSERT_EQ(10, value.getValue());

    // Do it again and commit it.
    value.setValue(20);
    ASSERT_EQ(20, value.getValue());
    value.commit();
    EXPECT_EQ(20, value.getValue());
}

// This test verifies that the value can be reverted if it hasn't been
// committed.
TEST(StagedValueTest, revert) {
    // Set the value and commit.
    StagedValue<int> value;
    value.setValue(123);
    value.commit();

    // Set new value and do not commit.
    value.setValue(500);
    // The new value should be the one returned.
    ASSERT_EQ(500, value.getValue());
    // But, reverting gets us back to original value.
    value.revert();
    EXPECT_EQ(123, value.getValue());
    // Reverting again doesn't have any effect.
    value.revert();
    EXPECT_EQ(123, value.getValue());
}

// This test verifies that the value can be restored to an original one.
TEST(StagedValueTest, reset) {
    // Set the new value and commit.
    StagedValue<int> value;
    value.setValue(123);
    value.commit();

    // Override the value but do not commit.
    value.setValue(500);

    // Resetting should take us back to default value.
    value.reset();
    EXPECT_EQ(0, value.getValue());
    value.revert();
    EXPECT_EQ(0, value.getValue());
}

// This test verifies that second commit doesn't modify a value.
TEST(StagedValueTest, commit) {
    // Set the value and commit.
    StagedValue<int> value;
    value.setValue(123);
    value.commit();

    // Second commit should have no effect.
    value.commit();
    EXPECT_EQ(123, value.getValue());
}

// This test checks that type conversion operator works correctly.
TEST(StagedValueTest, conversionOperator) {
    StagedValue<int> value;
    value.setValue(244);
    EXPECT_EQ(244, value);
}

// This test checks that the assignment operator works correctly.
TEST(StagedValueTest, assignmentOperator) {
    StagedValue<int> value;
    value = 111;
    EXPECT_EQ(111, value);
}


} // end of anonymous namespace
