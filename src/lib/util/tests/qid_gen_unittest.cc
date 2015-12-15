// Copyright (C) 2011  Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

// Copyright (C) 2011  Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.


/// \brief Test of QidGenerator
///

#include <gtest/gtest.h>

#include <util/random/qid_gen.h>

using namespace isc::util::random;

// Tests the operation of the Qid generator

// Check that getInstance returns a singleton
TEST(QidGenerator, singleton) {
    QidGenerator& g1 = QidGenerator::getInstance();
    QidGenerator& g2 = QidGenerator::getInstance();

    EXPECT_TRUE(&g1 == &g2);
}

TEST(QidGenerator, generate) {
    // We'll assume that boost's generator is 'good enough', and won't
    // do full statistical checking here. Let's just call it the xkcd
    // test (http://xkcd.com/221/), and check if three consecutive
    // generates are not all the same.
    uint16_t one, two, three;
    QidGenerator& gen = QidGenerator::getInstance();
    one = gen.generateQid();
    two = gen.generateQid();
    three = gen.generateQid();
    ASSERT_FALSE((one == two) && (one == three));
}
