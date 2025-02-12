// Copyright (C) 2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef ATTRIBUTE_TEST_H
#define ATTRIBUTE_TEST_H

#include <client_attribute.h>
#include <gtest/gtest.h>

namespace isc {
namespace radius {
namespace test {

/// @brief Shared test fixture for testing code using attributes.
class AttributeTest : public ::testing::Test {
public:
    /// @brief Constructor.
    AttributeTest() {
        AttrDefs::instance().readDictionary(TEST_DICTIONARY);
    }

    /// @brief Destructor.
    virtual ~AttributeTest() {
        AttrDefs::instance().clear();
    }

    /// @brief Compare two attributes.
    ///
    /// @param first First attribute.
    /// @param second Second attribute.
    /// @return true if attributes are the same, false otherwise.
    /// @brief Compare two attribute collections.
    bool compare(ConstAttributePtr first, ConstAttributePtr second);

    /// @brief Compare two attribute collections.
    ///
    /// @param first First attribute collection.
    /// @param second Second attribute collection.
    /// @return true if collections are the same, false otherwise.
    bool compare(const Attributes& first, const Attributes& second);
};

} // end of namespace isc::radius::test
} // end of namespace isc::radius
} // end of namespace isc

#endif // ATTRIBUTE_TEST_H
