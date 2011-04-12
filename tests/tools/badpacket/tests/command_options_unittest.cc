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

#include <cstddef>
#include <string>
#include <gtest/gtest.h>

#include "../command_options.h"

#include "exceptions/exceptions.h"

using namespace std;
using namespace isc;
using namespace isc::badpacket;


/// \brief Test Fixture Class

class CommandOptionsTest : public virtual ::testing::Test,
                           public virtual CommandOptions
{
public:

    /// \brief Default Constructor
    CommandOptionsTest() {}

    /// \brief Checks the minimum and maximum () specified for an option
    ///
    /// Checks the () for one of the options whose values are stored in the
    /// class's limits) array.
    ///
    /// \param index Index of the option in the limits_ array
    /// \param minval Expected minimum value
    /// \param maxval Expected maximum value
    void checkValuePair(int index, uint32_t minval = 0, uint32_t maxval = 0)
    {
        EXPECT_EQ(minimum(index), minval);
        EXPECT_EQ(maximum(index), maxval);
    }

    /// \brief Checks that all options giving flags () are zero.
    ///
    /// Checks that all options whose () are stored in the class's limits_
    /// array have both their maximum and minimum () set to zero.
    void checkDefaultLimitsValues() {
        checkValuePair(OptionInfo::QR);
        checkValuePair(OptionInfo::OP);
        checkValuePair(OptionInfo::AA);
        checkValuePair(OptionInfo::TC);
        checkValuePair(OptionInfo::Z);
        checkValuePair(OptionInfo::AD);
        checkValuePair(OptionInfo::CD);
        checkValuePair(OptionInfo::RC);
    }

    /// \brief Check Non-Limit Options
    ///
    /// Checks that the options whose () are NOT stored in the limits_
    /// array are set to their default ().
    void
    checkDefaultOtherValues() {
        EXPECT_EQ("127.0.0.1", getAddress());
        EXPECT_EQ(53, getPort());
        EXPECT_EQ(500, getTimeout());
        EXPECT_EQ("www.example.com", getQname());
    }
};

// Check that each of the options will be recognised

TEST_F(CommandOptionsTest, address) {
    const char* argv[] = {"badpacket",  "--address", "192.0.2.1"};
    int argc = sizeof(argv) / sizeof(const char*);

    // The conversion is ugly but it simplifies the process of entering the
    // string constant.  The cast throws away the "const"ness of the pointed-to
    // strings in order to conform to the function signature; however, the
    // called functions all treat the strings as const.
    parse(argc, const_cast<char**>(argv));
    EXPECT_EQ("192.0.2.1", getAddress());
    EXPECT_EQ(53, getPort());
    EXPECT_EQ(500, getTimeout());
    EXPECT_EQ("www.example.com", getQname());
    checkDefaultLimitsValues();
}

TEST_F(CommandOptionsTest, port) {
    const char* argv[] = {"badpacket",  "--port", "153"};
    int argc = sizeof(argv) / sizeof(const char*);

    parse(argc, const_cast<char**>(argv));
    EXPECT_EQ("127.0.0.1", getAddress());
    EXPECT_EQ(153, getPort());
    EXPECT_EQ(500, getTimeout());
    EXPECT_EQ("www.example.com", getQname());
    checkDefaultLimitsValues();
}

TEST_F(CommandOptionsTest, timeout) {
    const char* argv[] = {"badpacket",  "--timeout", "250"};
    int argc = sizeof(argv) / sizeof(const char*);

    parse(argc, const_cast<char**>(argv));
    EXPECT_EQ("127.0.0.1", getAddress());
    EXPECT_EQ(53, getPort());
    EXPECT_EQ(250, getTimeout());
    EXPECT_EQ("www.example.com", getQname());
    checkDefaultLimitsValues();
}

TEST_F(CommandOptionsTest, parameter) {
    const char* argv[] = {"badpacket",  "ftp.example.net"};
    int argc = sizeof(argv) / sizeof(const char*);

    parse(argc, const_cast<char**>(argv));
    EXPECT_EQ("127.0.0.1", getAddress());
    EXPECT_EQ(53, getPort());
    EXPECT_EQ(500, getTimeout());
    EXPECT_EQ("ftp.example.net", getQname());
    checkDefaultLimitsValues();
}

// The various tests of the different flags
TEST_F(CommandOptionsTest, qr) {

    // Specifying a value of zero, we expect all flag () to be zero
    const char* argv1[] = {"badpacket",  "--qr", "0"};
    int argc1 = sizeof(argv1) / sizeof(const char*);

    parse(argc1, const_cast<char**>(argv1));
    checkDefaultOtherValues();
    checkDefaultLimitsValues();

    // Check that a value of 1 is accepted
    const char* argv2[] = {"badpacket",  "--qr", "1"};
    int argc2 = sizeof(argv2) / sizeof(const char*);

    parse(argc2, const_cast<char**>(argv2));
    checkDefaultOtherValues();
    checkValuePair(OptionInfo::QR, 1, 1);
    checkValuePair(OptionInfo::OP);
    checkValuePair(OptionInfo::AA);
    checkValuePair(OptionInfo::TC);
    checkValuePair(OptionInfo::Z);
    checkValuePair(OptionInfo::AD);
    checkValuePair(OptionInfo::CD);
    checkValuePair(OptionInfo::RC);

    // Check that a range is accepted (in this case, specified backwards)
    const char* argv3[] = {"badpacket",  "--qr", "1-0"};
    int argc3 = sizeof(argv3) / sizeof(const char*);

    parse(argc3, const_cast<char**>(argv3));
    checkDefaultOtherValues();
    checkValuePair(OptionInfo::QR, 0, 1);
    checkValuePair(OptionInfo::OP);
    checkValuePair(OptionInfo::AA);
    checkValuePair(OptionInfo::TC);
    checkValuePair(OptionInfo::Z);
    checkValuePair(OptionInfo::AD);
    checkValuePair(OptionInfo::CD);
    checkValuePair(OptionInfo::RC);
}

// The following are cut-and-pasted from the "qr" test.  (It is awkward to put
// the test into a general function because of differing string () and
// variables.)

TEST_F(CommandOptionsTest, op) {

    // Specifying a value of zero, we expect all flag () to be zero
    const char* argv1[] = {"badpacket",  "--op", "0"};
    int argc1 = sizeof(argv1) / sizeof(const char*);

    parse(argc1, const_cast<char**>(argv1));
    checkDefaultOtherValues();
    checkDefaultLimitsValues();

    // Check that a value of 1 is accepted
    const char* argv2[] = {"badpacket",  "--op", "8"};
    int argc2 = sizeof(argv2) / sizeof(const char*);

    parse(argc2, const_cast<char**>(argv2));
    checkDefaultOtherValues();
    checkValuePair(OptionInfo::QR);
    checkValuePair(OptionInfo::OP, 8, 8);
    checkValuePair(OptionInfo::AA);
    checkValuePair(OptionInfo::TC);
    checkValuePair(OptionInfo::Z);
    checkValuePair(OptionInfo::AD);
    checkValuePair(OptionInfo::CD);
    checkValuePair(OptionInfo::RC);

    // Check that a range is accepted (in this case, specified backwards)
    const char* argv3[] = {"badpacket",  "--op", "14-2"};
    int argc3 = sizeof(argv3) / sizeof(const char*);

    parse(argc3, const_cast<char**>(argv3));
    checkDefaultOtherValues();
    checkValuePair(OptionInfo::QR);
    checkValuePair(OptionInfo::OP, 2, 14);
    checkValuePair(OptionInfo::AA);
    checkValuePair(OptionInfo::TC);
    checkValuePair(OptionInfo::Z);
    checkValuePair(OptionInfo::AD);
    checkValuePair(OptionInfo::CD);
    checkValuePair(OptionInfo::RC);
}

TEST_F(CommandOptionsTest, aa) {

    // Specifying a value of zero, we expect all flag () to be zero
    const char* argv1[] = {"badpacket",  "--aa", "0"};
    int argc1 = sizeof(argv1) / sizeof(const char*);

    parse(argc1, const_cast<char**>(argv1));
    checkDefaultOtherValues();
    checkDefaultLimitsValues();

    // Check that a value of 1 is accepted
    const char* argv2[] = {"badpacket",  "--aa", "1"};
    int argc2 = sizeof(argv2) / sizeof(const char*);

    parse(argc2, const_cast<char**>(argv2));
    checkDefaultOtherValues();
    checkValuePair(OptionInfo::QR);
    checkValuePair(OptionInfo::OP);
    checkValuePair(OptionInfo::AA, 1, 1);
    checkValuePair(OptionInfo::TC);
    checkValuePair(OptionInfo::Z);
    checkValuePair(OptionInfo::AD);
    checkValuePair(OptionInfo::CD);
    checkValuePair(OptionInfo::RC);

    // Check that a range is accepted.
    const char* argv3[] = {"badpacket",  "--aa", "1-0"};
    int argc3 = sizeof(argv3) / sizeof(const char*);

    parse(argc3, const_cast<char**>(argv3));
    checkDefaultOtherValues();
    checkValuePair(OptionInfo::QR);
    checkValuePair(OptionInfo::OP);
    checkValuePair(OptionInfo::AA, 0, 1);
    checkValuePair(OptionInfo::TC);
    checkValuePair(OptionInfo::Z);
    checkValuePair(OptionInfo::AD);
    checkValuePair(OptionInfo::CD);
    checkValuePair(OptionInfo::RC);
}

TEST_F(CommandOptionsTest, tc) {

    // Specifying a value of zero, we expect all flag () to be zero
    const char* argv1[] = {"badpacket",  "--tc", "0"};
    int argc1 = sizeof(argv1) / sizeof(const char*);

    parse(argc1, const_cast<char**>(argv1));
    checkDefaultOtherValues();
    checkDefaultLimitsValues();

    // Check that a value of 1 is accepted
    const char* argv2[] = {"badpacket",  "--tc", "1"};
    int argc2 = sizeof(argv2) / sizeof(const char*);

    parse(argc2, const_cast<char**>(argv2));
    checkDefaultOtherValues();
    checkValuePair(OptionInfo::QR);
    checkValuePair(OptionInfo::OP);
    checkValuePair(OptionInfo::AA);
    checkValuePair(OptionInfo::TC, 1, 1);
    checkValuePair(OptionInfo::Z);
    checkValuePair(OptionInfo::AD);
    checkValuePair(OptionInfo::CD);
    checkValuePair(OptionInfo::RC);

    // Check that a range is accepted.
    const char* argv3[] = {"badpacket",  "--tc", "1-0"};
    int argc3 = sizeof(argv3) / sizeof(const char*);

    parse(argc3, const_cast<char**>(argv3));
    checkDefaultOtherValues();
    checkValuePair(OptionInfo::QR);
    checkValuePair(OptionInfo::OP);
    checkValuePair(OptionInfo::AA);
    checkValuePair(OptionInfo::TC, 0, 1);
    checkValuePair(OptionInfo::Z);
    checkValuePair(OptionInfo::AD);
    checkValuePair(OptionInfo::CD);
    checkValuePair(OptionInfo::RC);
}

TEST_F(CommandOptionsTest, z) {

    // Specifying a value of zero, we expect all flag () to be zero
    const char* argv1[] = {"badpacket",  "--z", "0"};
    int argc1 = sizeof(argv1) / sizeof(const char*);

    parse(argc1, const_cast<char**>(argv1));
    checkDefaultOtherValues();
    checkDefaultLimitsValues();

    // Check that a value of 1 is accepted
    const char* argv2[] = {"badpacket",  "--z", "1"};
    int argc2 = sizeof(argv2) / sizeof(const char*);

    parse(argc2, const_cast<char**>(argv2));
    checkDefaultOtherValues();
    checkValuePair(OptionInfo::QR);
    checkValuePair(OptionInfo::OP);
    checkValuePair(OptionInfo::AA);
    checkValuePair(OptionInfo::TC);
    checkValuePair(OptionInfo::Z, 1, 1);
    checkValuePair(OptionInfo::AD);
    checkValuePair(OptionInfo::CD);
    checkValuePair(OptionInfo::RC);

    // Check that a range is accepted.
    const char* argv3[] = {"badpacket",  "--z", "1-0"};
    int argc3 = sizeof(argv3) / sizeof(const char*);

    parse(argc3, const_cast<char**>(argv3));
    checkDefaultOtherValues();
    checkValuePair(OptionInfo::QR);
    checkValuePair(OptionInfo::OP);
    checkValuePair(OptionInfo::AA);
    checkValuePair(OptionInfo::TC);
    checkValuePair(OptionInfo::Z, 0, 1);
    checkValuePair(OptionInfo::AD);
    checkValuePair(OptionInfo::CD);
    checkValuePair(OptionInfo::RC);
}

TEST_F(CommandOptionsTest, ad) {

    // Specifying a value of zero, we expect all flag () to be zero
    const char* argv1[] = {"badpacket",  "--ad", "0"};
    int argc1 = sizeof(argv1) / sizeof(const char*);

    parse(argc1, const_cast<char**>(argv1));
    checkDefaultOtherValues();
    checkDefaultLimitsValues();

    // Check that a value of 1 is accepted
    const char* argv2[] = {"badpacket",  "--ad", "1"};
    int argc2 = sizeof(argv2) / sizeof(const char*);

    parse(argc2, const_cast<char**>(argv2));
    checkDefaultOtherValues();
    checkValuePair(OptionInfo::QR);
    checkValuePair(OptionInfo::OP);
    checkValuePair(OptionInfo::AA);
    checkValuePair(OptionInfo::TC);
    checkValuePair(OptionInfo::Z);
    checkValuePair(OptionInfo::AD, 1, 1);
    checkValuePair(OptionInfo::CD);
    checkValuePair(OptionInfo::RC);

    // Check that a range is accepted.
    const char* argv3[] = {"badpacket",  "--ad", "0-1"};
    int argc3 = sizeof(argv3) / sizeof(const char*);

    parse(argc3, const_cast<char**>(argv3));
    checkDefaultOtherValues();
    checkValuePair(OptionInfo::QR);
    checkValuePair(OptionInfo::OP);
    checkValuePair(OptionInfo::AA);
    checkValuePair(OptionInfo::TC);
    checkValuePair(OptionInfo::Z);
    checkValuePair(OptionInfo::AD, 0, 1);
    checkValuePair(OptionInfo::CD);
    checkValuePair(OptionInfo::RC);
}

TEST_F(CommandOptionsTest, cd) {

    // Specifying a value of zero, we expect all flag () to be zero
    const char* argv1[] = {"badpacket",  "--cd", "0"};
    int argc1 = sizeof(argv1) / sizeof(const char*);

    parse(argc1, const_cast<char**>(argv1));
    checkDefaultOtherValues();
    checkDefaultLimitsValues();

    // Check that a value of 1 is accepted
    const char* argv2[] = {"badpacket",  "--cd", "1"};
    int argc2 = sizeof(argv2) / sizeof(const char*);

    parse(argc2, const_cast<char**>(argv2));
    checkDefaultOtherValues();
    checkValuePair(OptionInfo::QR);
    checkValuePair(OptionInfo::OP);
    checkValuePair(OptionInfo::AA);
    checkValuePair(OptionInfo::TC);
    checkValuePair(OptionInfo::Z);
    checkValuePair(OptionInfo::AD);
    checkValuePair(OptionInfo::CD, 1, 1);
    checkValuePair(OptionInfo::RC);

    // Check that a range is accepted.
    const char* argv3[] = {"badpacket",  "--cd", "1-0"};
    int argc3 = sizeof(argv3) / sizeof(const char*);

    parse(argc3, const_cast<char**>(argv3));
    checkDefaultOtherValues();
    checkValuePair(OptionInfo::QR);
    checkValuePair(OptionInfo::OP);
    checkValuePair(OptionInfo::AA);
    checkValuePair(OptionInfo::TC);
    checkValuePair(OptionInfo::Z);
    checkValuePair(OptionInfo::AD);
    checkValuePair(OptionInfo::CD, 0, 1);
    checkValuePair(OptionInfo::RC);
}

TEST_F(CommandOptionsTest, rc) {

    // Specifying a value of zero, we expect all flag () to be zero
    const char* argv1[] = {"badpacket",  "--rc", "0"};
    int argc1 = sizeof(argv1) / sizeof(const char*);

    parse(argc1, const_cast<char**>(argv1));
    checkDefaultOtherValues();
    checkDefaultLimitsValues();

    // Check that a valid value is accepted.
    const char* argv2[] = {"badpacket",  "--rc", "15"};
    int argc2 = sizeof(argv2) / sizeof(const char*);

    parse(argc2, const_cast<char**>(argv2));
    checkDefaultOtherValues();
    checkValuePair(OptionInfo::QR);
    checkValuePair(OptionInfo::OP);
    checkValuePair(OptionInfo::AA);
    checkValuePair(OptionInfo::TC);
    checkValuePair(OptionInfo::Z);
    checkValuePair(OptionInfo::AD);
    checkValuePair(OptionInfo::CD);
    checkValuePair(OptionInfo::RC, 15, 15);

    // Check that a range is accepted (in this case, specified backwards and
    // outside the range - so it should be truncated).
    const char* argv3[] = {"badpacket",  "--rc", "8-4"};
    int argc3 = sizeof(argv3) / sizeof(const char*);

    parse(argc3, const_cast<char**>(argv3));
    checkDefaultOtherValues();
    checkValuePair(OptionInfo::QR);
    checkValuePair(OptionInfo::OP);
    checkValuePair(OptionInfo::AA);
    checkValuePair(OptionInfo::TC);
    checkValuePair(OptionInfo::Z);
    checkValuePair(OptionInfo::AD);
    checkValuePair(OptionInfo::CD);
    checkValuePair(OptionInfo::RC, 4, 8);
}

// Check that invalid () are caught.
TEST_F(CommandOptionsTest, processOptionValue) {

    // Check out of range () cause a BadValue exception
    EXPECT_THROW(processOptionValue('Q', "2"), isc::BadValue);      // Single value above range
    EXPECT_THROW(processOptionValue('O', "0-17"), isc::BadValue);   // Range overlapping valid range

    // ... and that any invalid string does the same
    EXPECT_THROW(processOptionValue('O', ""), isc::BadValue);
    EXPECT_THROW(processOptionValue('O', " "), isc::BadValue);
    EXPECT_THROW(processOptionValue('O', "1-2-3"), isc::BadValue);
    EXPECT_THROW(processOptionValue('O', "abc"), isc::BadValue);
    EXPECT_THROW(processOptionValue('O', "abc-xyz"), isc::BadValue);
    EXPECT_THROW(processOptionValue('O', "0.7"), isc::BadValue);
    EXPECT_THROW(processOptionValue('O', "0.7-2.3"), isc::BadValue);
}
