// Copyright (C) 2011  Internet Systems Consortium, Inc. ("ISC")
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

// Copyright (C) 2011  Internet Systems Consortium, Inc. ("ISC")
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
