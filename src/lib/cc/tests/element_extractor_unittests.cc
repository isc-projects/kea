// Copyright (C) 2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <cc/element_extractor.h>
#include <gtest/gtest.h>

using namespace isc::data;

namespace {

// This test verifies that integer value can be extracted.
TEST(ElementExtractor, intValue) {
    EXPECT_EQ(5, ElementExtractor<int>()(Element::create(5)));
    EXPECT_THROW(ElementExtractor<int>()(Element::create("hola!")),
                 TypeError);
}

// This test verifies that double value can be extracted.
TEST(ElementExtractor, doubleValue) {
    EXPECT_EQ(1.4, ElementExtractor<double>()(Element::create(1.4)));
    EXPECT_THROW(ElementExtractor<double>()(Element::create("hola!")),
                 TypeError);
}

// This test verifies that boolean value can be extracted.
TEST(ElementExtractor, boolValue) {
    EXPECT_TRUE(ElementExtractor<bool>()(Element::create(true)));
    EXPECT_THROW(ElementExtractor<bool>()(Element::create("hola!")),
                 TypeError);
}

// This test verifies that string value can be extracted.
TEST(ElementExtractor, stringValue) {
    EXPECT_EQ("hola!", ElementExtractor<std::string>()(Element::create("hola!")));
    EXPECT_THROW(ElementExtractor<std::string>()(Element::create(false)),
                 TypeError);
}

}
