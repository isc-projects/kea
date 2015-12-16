// Copyright (C) 2011-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <gtest/gtest.h>

#include <dns/serial.h>

using namespace isc::dns;

class SerialTest : public ::testing::Test {
public:
    SerialTest() : one(1), one_2(1), two(2),
                   date_zero(1980120100), date_one(1980120101),
                   min(0), max(4294967295u),
                   number_low(12345),
                   number_medium(2000000000),
                   number_high(4000000000u)
    {}
    Serial one, one_2, two, date_zero, date_one, min, max, number_low, number_medium, number_high;
};

//
// Basic tests
//

TEST_F(SerialTest, get_value) {
    EXPECT_EQ(1, one.getValue());
    EXPECT_NE(2, one.getValue());
    EXPECT_EQ(2, two.getValue());
    EXPECT_EQ(1980120100, date_zero.getValue());
    EXPECT_EQ(1980120101, date_one.getValue());
    EXPECT_EQ(0, min.getValue());
    EXPECT_EQ(4294967295u, max.getValue());
    EXPECT_EQ(12345, number_low.getValue());
    EXPECT_EQ(2000000000, number_medium.getValue());
    EXPECT_EQ(4000000000u, number_high.getValue());
}

TEST_F(SerialTest, equals) {
    EXPECT_EQ(one, one);
    EXPECT_EQ(one, one_2);
    EXPECT_NE(one, two);
    EXPECT_NE(two, one);
    EXPECT_EQ(Serial(12345), number_low);
    EXPECT_NE(Serial(12346), number_low);
}

TEST_F(SerialTest, comparison) {
    // These should be true/false even without serial arithmetic
    EXPECT_LE(one, one);
    EXPECT_LE(one, one_2);
    EXPECT_LT(one, two);
    EXPECT_LE(one, two);
    EXPECT_GE(two, two);
    EXPECT_GT(two, one);
    EXPECT_GE(two, one);
    EXPECT_LT(one, number_low);
    EXPECT_LT(number_low, number_medium);
    EXPECT_LT(number_medium, number_high);

    // now let's try some that 'wrap', as it were
    EXPECT_GT(min, max);
    EXPECT_LT(max, min);
    EXPECT_LT(number_high, number_low);
}

//
// RFC 1982 Section 3.1
//
TEST_F(SerialTest, addition) {
    EXPECT_EQ(two, one + one);
    EXPECT_EQ(two, one + one_2);
    EXPECT_EQ(max, max + min);
    EXPECT_EQ(min, max + one);
    EXPECT_EQ(one, max + two);
    EXPECT_EQ(one, max + one + one);

    EXPECT_EQ(one + 100, max + 102);
    EXPECT_EQ(min + 2147483645, max + 2147483646);
    EXPECT_EQ(min + 2147483646, max + MAX_SERIAL_INCREMENT);
}

//
// RFC 1982 Section 3.2 has been checked by the basic tests above
//

//
// RFC 1982 Section 4.1
//

// Helper function for addition_always_larger test, add some numbers
// and check that the result is always larger than the original
void do_addition_larger_test(const Serial& number) {
    EXPECT_GE(number + 0, number);
    EXPECT_EQ(number + 0, number);
    EXPECT_GT(number + 1, number);
    EXPECT_GT(number + 2, number);
    EXPECT_GT(number + 100, number);
    EXPECT_GT(number + 1111111, number);
    EXPECT_GT(number + 2147483646, number);
    EXPECT_GT(number + MAX_SERIAL_INCREMENT, number);
    // Try MAX_SERIAL_INCREMENT as a hardcoded number as well
    EXPECT_GT(number + 2147483647, number);
}

TEST_F(SerialTest, addition_always_larger) {
    do_addition_larger_test(one);
    do_addition_larger_test(two);
    do_addition_larger_test(date_zero);
    do_addition_larger_test(date_one);
    do_addition_larger_test(min);
    do_addition_larger_test(max);
    do_addition_larger_test(number_low);
    do_addition_larger_test(number_medium);
    do_addition_larger_test(number_high);
}

//
// RFC 1982 Section 4.2
//

// Helper function to do the second addition
void
do_two_additions_test_second(const Serial &original,
                             const Serial &number)
{
    EXPECT_NE(original, number);
    EXPECT_NE(original, number + 0);
    EXPECT_NE(original, number + 1);
    EXPECT_NE(original, number + 2);
    EXPECT_NE(original, number + 100);
    EXPECT_NE(original, number + 1111111);
    EXPECT_NE(original, number + 2147483646);
    EXPECT_NE(original, number + MAX_SERIAL_INCREMENT);
    EXPECT_NE(original, number + 2147483647);
}

void do_two_additions_test_first(const Serial &number) {
    do_two_additions_test_second(number, number + 1);
    do_two_additions_test_second(number, number + 2);
    do_two_additions_test_second(number, number + 100);
    do_two_additions_test_second(number, number + 1111111);
    do_two_additions_test_second(number, number + 2147483646);
    do_two_additions_test_second(number, number + MAX_SERIAL_INCREMENT);
    do_two_additions_test_second(number, number + 2147483647);
}

TEST_F(SerialTest, two_additions_never_equal) {
    do_two_additions_test_first(one);
    do_two_additions_test_first(two);
    do_two_additions_test_first(date_zero);
    do_two_additions_test_first(date_one);
    do_two_additions_test_first(min);
    do_two_additions_test_first(max);
    do_two_additions_test_first(number_low);
    do_two_additions_test_first(number_medium);
    do_two_additions_test_first(number_high);
}

//
// RFC 1982 Section 4.3 and 4.4 have nothing to test
//

//
// Tests from RFC 1982 examples
//
TEST(SerialTextRFCExamples, rfc_example_tests) {
}
