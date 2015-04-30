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

#include <d2/labeled_value.h>

#include <gtest/gtest.h>

using namespace std;
using namespace isc;
using namespace isc::d2;

namespace {

/// @brief Verifies basic construction and accessors for LabeledValue.
TEST(LabeledValue, construction) {
    /// Verify that an empty label is not allowed.
    ASSERT_THROW(LabeledValue(1, ""), LabeledValueError);

    /// Verify that a valid constructor works.
    LabeledValuePtr lvp;
    ASSERT_NO_THROW(lvp.reset(new LabeledValue(1, "NotBlank")));
    ASSERT_TRUE(lvp.get() != 0);

    // Verify that the value can be accessed.
    EXPECT_EQ(1, lvp->getValue());

    // Verify that the label can be accessed.
    EXPECT_EQ("NotBlank", lvp->getLabel());
}

/// @brief Verifies the logical operators defined for LabeledValue.
TEST(LabeledValue, operators) {
    LabeledValuePtr lvp1;
    LabeledValuePtr lvp1Also;
    LabeledValuePtr lvp2;

    // Create three instances, two of which have the same numeric value.
    ASSERT_NO_THROW(lvp1.reset(new LabeledValue(1, "One")));
    ASSERT_NO_THROW(lvp1Also.reset(new LabeledValue(1, "OneAlso")));
    ASSERT_NO_THROW(lvp2.reset(new LabeledValue(2, "Two")));

    // Verify each of the operators.
    EXPECT_TRUE(*lvp1 == *lvp1Also);
    EXPECT_TRUE(*lvp1 != *lvp2);
    EXPECT_TRUE(*lvp1 < *lvp2);
    EXPECT_FALSE(*lvp2 < *lvp1);
}

/// @brief Verifies the default constructor for LabeledValueSet.
TEST(LabeledValueSet, construction) {
    ASSERT_NO_THROW (LabeledValueSet());
}

/// @brief Verifies the basic operations of a LabeledValueSet.
/// Essentially we verify that we can define a set of valid entries and
/// look them up without issue.
TEST(LabeledValueSet, basicOperation) {
    const char* labels[] = {"Zero", "One", "Two", "Three" };
    LabeledValueSet lvset;
    LabeledValuePtr lvp;

    // Verify the we cannot add an empty pointer to the set.
    EXPECT_THROW(lvset.add(lvp), LabeledValueError);

    // Verify that we can add an entry to the set via pointer.
    ASSERT_NO_THROW(lvp.reset(new LabeledValue(0, labels[0])));
    EXPECT_NO_THROW(lvset.add(lvp));

    // Verify that we cannot add a duplicate entry.
    EXPECT_THROW(lvset.add(lvp), LabeledValueError);

    // Add the remaining entries using add(int,char*) variant.
    for (int i = 1; i < 3; i++) {
        EXPECT_NO_THROW(lvset.add(i, labels[i]));
    }

    // Verify that we can't add a duplicate entry this way either.
    EXPECT_THROW ((lvset.add(0, labels[0])), LabeledValueError);

    // Verify that we can look up all of the defined entries properly.
    for (int i = 1; i < 3; i++) {
        EXPECT_TRUE(lvset.isDefined(i));
        EXPECT_NO_THROW(lvp = lvset.get(i));
        EXPECT_EQ(lvp->getValue(), i);
        EXPECT_EQ(lvp->getLabel(), labels[i]);
        EXPECT_EQ(lvset.getLabel(i), labels[i]);
    }

    // Verify behavior for a value that is not defined.
    EXPECT_FALSE(lvset.isDefined(4));
    EXPECT_NO_THROW(lvp = lvset.get(4));
    EXPECT_FALSE(lvp);
    EXPECT_EQ(lvset.getLabel(4), LabeledValueSet::UNDEFINED_LABEL);
}

}
