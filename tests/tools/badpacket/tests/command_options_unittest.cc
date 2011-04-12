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


// Test fixture class

class CommandOptionsTest : public virtual ::testing::Test,
                           public virtual CommandOptions
{
public:
    CommandOptionsTest() {}
};

// Check that the getRange() method works

TEST_F(CommandOptionsTest, processOptionValue) {

    uint32_t    result[2];

    // Check valid data
    processOptionValue("dummy", "1", result, 0, 1);
    EXPECT_EQ(1, result[0]);
    EXPECT_EQ(1, result[1]);

    processOptionValue("dummy", "0-2", result, 0, 5);
    EXPECT_EQ(0, result[0]);
    EXPECT_EQ(2, result[1]);

    processOptionValue("dummy", "4-8", result, 0, 10);
    EXPECT_EQ(4, result[0]);
    EXPECT_EQ(8, result[1]);

    processOptionValue("dummy", "172-103", result, 0, 200);
    EXPECT_EQ(103, result[0]);
    EXPECT_EQ(172, result[1]);

    // Check out of range values cause a BadValue exception
    EXPECT_THROW(processOptionValue("dummy", "1", result, 3, 4),
                 isc::BadValue);    // Single value below range
    EXPECT_THROW(processOptionValue("dummy", "7", result, 3, 6),
                 isc::BadValue);    // Single value above range
    EXPECT_THROW(processOptionValue("dummy", "2-6", result, 5, 10),
                 isc::BadValue);    // Range overlaps valid range on low side
    EXPECT_THROW(processOptionValue("dummy", "4-7", result, 5, 9),
                 isc::BadValue);   // Range overlaps valid range on high side
    EXPECT_THROW(processOptionValue("dummy", "9-1", result, 4, 8),
                 isc::BadValue);   // Range overlaps valid range

    // ... and that any invalid string does the same
    EXPECT_THROW(processOptionValue("dummy", "", result, 0, 1),
                 isc::BadValue);
    EXPECT_THROW(processOptionValue("dummy", " ", result, 0, 1),
                 isc::BadValue);
    EXPECT_THROW(processOptionValue("dummy", "abc", result, 0, 1),
                 isc::BadValue);
    EXPECT_THROW(processOptionValue("dummy", "xyz-def", result, 0, 1),
                 isc::BadValue);
    EXPECT_THROW(processOptionValue("dummy", "0.7", result, 0, 1),
                 isc::BadValue);
    EXPECT_THROW(processOptionValue("dummy", "0.7-2.3", result, 0, 1),
                 isc::BadValue);
}


// Checks the minimum and maximum values specified for a flag
void
checkValuePair(const uint32_t value[2], uint32_t minval = 0,
               uint32_t maxval = 0)
{
    EXPECT_EQ(minval, value[0]);
    EXPECT_EQ(maxval, value[1]);
}

// Checks that all flag values in the command values are zero
void
checkDefaultFlagValues(const CommandOptions::FlagValues& values) {
    checkValuePair(values.qr);
    checkValuePair(values.op);
    checkValuePair(values.aa);
    checkValuePair(values.tc);
    checkValuePair(values.z);
    checkValuePair(values.ad);
    checkValuePair(values.cd);
    checkValuePair(values.rc);
}

// Checks non-flag options are set to defaults.
void
checkDefaultOtherValues(CommandOptions& options) {
    EXPECT_EQ("127.0.0.1", options.getAddress());
    EXPECT_EQ(53, options.getPort());
    EXPECT_EQ(500, options.getTimeout());
    EXPECT_EQ("www.example.com", options.getQname());
}

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
    checkDefaultFlagValues(getFlagValues());
}

TEST_F(CommandOptionsTest, port) {
    const char* argv[] = {"badpacket",  "--port", "153"};
    int argc = sizeof(argv) / sizeof(const char*);

    parse(argc, const_cast<char**>(argv));
    EXPECT_EQ("127.0.0.1", getAddress());
    EXPECT_EQ(153, getPort());
    EXPECT_EQ(500, getTimeout());
    EXPECT_EQ("www.example.com", getQname());
    checkDefaultFlagValues(getFlagValues());
}

TEST_F(CommandOptionsTest, timeout) {
    const char* argv[] = {"badpacket",  "--timeout", "250"};
    int argc = sizeof(argv) / sizeof(const char*);

    parse(argc, const_cast<char**>(argv));
    EXPECT_EQ("127.0.0.1", getAddress());
    EXPECT_EQ(53, getPort());
    EXPECT_EQ(250, getTimeout());
    EXPECT_EQ("www.example.com", getQname());
    checkDefaultFlagValues(getFlagValues());
}

TEST_F(CommandOptionsTest, parameter) {
    const char* argv[] = {"badpacket",  "ftp.example.net"};
    int argc = sizeof(argv) / sizeof(const char*);

    parse(argc, const_cast<char**>(argv));
    EXPECT_EQ("127.0.0.1", getAddress());
    EXPECT_EQ(53, getPort());
    EXPECT_EQ(500, getTimeout());
    EXPECT_EQ("ftp.example.net", getQname());
    checkDefaultFlagValues(getFlagValues());
}

// The various tests of the different flags
TEST_F(CommandOptionsTest, qr) {

    // Specifying a value of zero, we expect all flag values to be zero
    const char* argv1[] = {"badpacket",  "--qr", "0"};
    int argc1 = sizeof(argv1) / sizeof(const char*);

    parse(argc1, const_cast<char**>(argv1));
    checkDefaultOtherValues(*this);
    FlagValues values = getFlagValues();
    checkDefaultFlagValues(values);

    // Check that a value of 1 is accepted
    const char* argv2[] = {"badpacket",  "--qr", "1"};
    int argc2 = sizeof(argv2) / sizeof(const char*);

    parse(argc2, const_cast<char**>(argv2));
    checkDefaultOtherValues(*this);
    values = getFlagValues();
    checkValuePair(values.qr, 1, 1);
    checkValuePair(values.op);
    checkValuePair(values.aa);
    checkValuePair(values.tc);
    checkValuePair(values.z);
    checkValuePair(values.ad);
    checkValuePair(values.cd);
    checkValuePair(values.rc);

    // Check that a range is accepted (in this case, specified backwards)
    const char* argv3[] = {"badpacket",  "--qr", "1-0"};
    int argc3 = sizeof(argv3) / sizeof(const char*);

    parse(argc3, const_cast<char**>(argv3));
    checkDefaultOtherValues(*this);
    values = getFlagValues();
    checkValuePair(values.qr, 0, 1);
    checkValuePair(values.op);
    checkValuePair(values.aa);
    checkValuePair(values.tc);
    checkValuePair(values.z);
    checkValuePair(values.ad);
    checkValuePair(values.cd);
    checkValuePair(values.rc);
}

// The following are cut-and-pasted from the "qr" test.  (It is awkward to put
// the test into a general function because of differing string values and
// variables.)

TEST_F(CommandOptionsTest, op) {

    // Specifying a value of zero, we expect all flag values to be zero
    const char* argv1[] = {"badpacket",  "--op", "0"};
    int argc1 = sizeof(argv1) / sizeof(const char*);

    parse(argc1, const_cast<char**>(argv1));
    checkDefaultOtherValues(*this);
    FlagValues values = getFlagValues();
    checkDefaultFlagValues(values);

    // Check that a value of 1 is accepted
    const char* argv2[] = {"badpacket",  "--op", "8"};
    int argc2 = sizeof(argv2) / sizeof(const char*);

    parse(argc2, const_cast<char**>(argv2));
    checkDefaultOtherValues(*this);
    values = getFlagValues();
    checkValuePair(values.qr);
    checkValuePair(values.op, 8, 8);
    checkValuePair(values.aa);
    checkValuePair(values.tc);
    checkValuePair(values.z);
    checkValuePair(values.ad);
    checkValuePair(values.cd);
    checkValuePair(values.rc);

    // Check that a range is accepted (in this case, specified backwards)
    const char* argv3[] = {"badpacket",  "--op", "14-2"};
    int argc3 = sizeof(argv3) / sizeof(const char*);

    parse(argc3, const_cast<char**>(argv3));
    checkDefaultOtherValues(*this);
    values = getFlagValues();
    checkValuePair(values.qr);
    checkValuePair(values.op, 2, 14);
    checkValuePair(values.aa);
    checkValuePair(values.tc);
    checkValuePair(values.z);
    checkValuePair(values.ad);
    checkValuePair(values.cd);
    checkValuePair(values.rc);
}

TEST_F(CommandOptionsTest, aa) {

    // Specifying a value of zero, we expect all flag values to be zero
    const char* argv1[] = {"badpacket",  "--aa", "0"};
    int argc1 = sizeof(argv1) / sizeof(const char*);

    parse(argc1, const_cast<char**>(argv1));
    checkDefaultOtherValues(*this);
    FlagValues values = getFlagValues();
    checkDefaultFlagValues(values);

    // Check that a value of 1 is accepted
    const char* argv2[] = {"badpacket",  "--aa", "1"};
    int argc2 = sizeof(argv2) / sizeof(const char*);

    parse(argc2, const_cast<char**>(argv2));
    checkDefaultOtherValues(*this);
    values = getFlagValues();
    checkValuePair(values.qr);
    checkValuePair(values.op);
    checkValuePair(values.aa, 1, 1);
    checkValuePair(values.tc);
    checkValuePair(values.z);
    checkValuePair(values.ad);
    checkValuePair(values.cd);
    checkValuePair(values.rc);

    // Check that a range is accepted.
    const char* argv3[] = {"badpacket",  "--aa", "1-0"};
    int argc3 = sizeof(argv3) / sizeof(const char*);

    parse(argc3, const_cast<char**>(argv3));
    checkDefaultOtherValues(*this);
    values = getFlagValues();
    checkValuePair(values.qr);
    checkValuePair(values.op);
    checkValuePair(values.aa, 0, 1);
    checkValuePair(values.tc);
    checkValuePair(values.z);
    checkValuePair(values.ad);
    checkValuePair(values.cd);
    checkValuePair(values.rc);
}

TEST_F(CommandOptionsTest, tc) {

    // Specifying a value of zero, we expect all flag values to be zero
    const char* argv1[] = {"badpacket",  "--tc", "0"};
    int argc1 = sizeof(argv1) / sizeof(const char*);

    parse(argc1, const_cast<char**>(argv1));
    checkDefaultOtherValues(*this);
    FlagValues values = getFlagValues();
    checkDefaultFlagValues(values);

    // Check that a value of 1 is accepted
    const char* argv2[] = {"badpacket",  "--tc", "1"};
    int argc2 = sizeof(argv2) / sizeof(const char*);

    parse(argc2, const_cast<char**>(argv2));
    checkDefaultOtherValues(*this);
    values = getFlagValues();
    checkValuePair(values.qr);
    checkValuePair(values.op);
    checkValuePair(values.aa);
    checkValuePair(values.tc, 1, 1);
    checkValuePair(values.z);
    checkValuePair(values.ad);
    checkValuePair(values.cd);
    checkValuePair(values.rc);

    // Check that a range is accepted.
    const char* argv3[] = {"badpacket",  "--tc", "1-0"};
    int argc3 = sizeof(argv3) / sizeof(const char*);

    parse(argc3, const_cast<char**>(argv3));
    checkDefaultOtherValues(*this);
    values = getFlagValues();
    checkValuePair(values.qr);
    checkValuePair(values.op);
    checkValuePair(values.aa);
    checkValuePair(values.tc, 0, 1);
    checkValuePair(values.z);
    checkValuePair(values.ad);
    checkValuePair(values.cd);
    checkValuePair(values.rc);
}

TEST_F(CommandOptionsTest, z) {

    // Specifying a value of zero, we expect all flag values to be zero
    const char* argv1[] = {"badpacket",  "--z", "0"};
    int argc1 = sizeof(argv1) / sizeof(const char*);

    parse(argc1, const_cast<char**>(argv1));
    checkDefaultOtherValues(*this);
    FlagValues values = getFlagValues();
    checkDefaultFlagValues(values);

    // Check that a value of 1 is accepted
    const char* argv2[] = {"badpacket",  "--z", "1"};
    int argc2 = sizeof(argv2) / sizeof(const char*);

    parse(argc2, const_cast<char**>(argv2));
    checkDefaultOtherValues(*this);
    values = getFlagValues();
    checkValuePair(values.qr);
    checkValuePair(values.op);
    checkValuePair(values.aa);
    checkValuePair(values.tc);
    checkValuePair(values.z, 1, 1);
    checkValuePair(values.ad);
    checkValuePair(values.cd);
    checkValuePair(values.rc);

    // Check that a range is accepted.
    const char* argv3[] = {"badpacket",  "--z", "1-0"};
    int argc3 = sizeof(argv3) / sizeof(const char*);

    parse(argc3, const_cast<char**>(argv3));
    checkDefaultOtherValues(*this);
    values = getFlagValues();
    checkValuePair(values.qr);
    checkValuePair(values.op);
    checkValuePair(values.aa);
    checkValuePair(values.tc);
    checkValuePair(values.z, 0, 1);
    checkValuePair(values.ad);
    checkValuePair(values.cd);
    checkValuePair(values.rc);
}

TEST_F(CommandOptionsTest, ad) {

    // Specifying a value of zero, we expect all flag values to be zero
    const char* argv1[] = {"badpacket",  "--ad", "0"};
    int argc1 = sizeof(argv1) / sizeof(const char*);

    parse(argc1, const_cast<char**>(argv1));
    checkDefaultOtherValues(*this);
    FlagValues values = getFlagValues();
    checkDefaultFlagValues(values);

    // Check that a value of 1 is accepted
    const char* argv2[] = {"badpacket",  "--ad", "1"};
    int argc2 = sizeof(argv2) / sizeof(const char*);

    parse(argc2, const_cast<char**>(argv2));
    checkDefaultOtherValues(*this);
    values = getFlagValues();
    checkValuePair(values.qr);
    checkValuePair(values.op);
    checkValuePair(values.aa);
    checkValuePair(values.tc);
    checkValuePair(values.z);
    checkValuePair(values.ad, 1, 1);
    checkValuePair(values.cd);
    checkValuePair(values.rc);

    // Check that a range is accepted.
    const char* argv3[] = {"badpacket",  "--ad", "0-1"};
    int argc3 = sizeof(argv3) / sizeof(const char*);

    parse(argc3, const_cast<char**>(argv3));
    checkDefaultOtherValues(*this);
    values = getFlagValues();
    checkValuePair(values.qr);
    checkValuePair(values.op);
    checkValuePair(values.aa);
    checkValuePair(values.tc);
    checkValuePair(values.z);
    checkValuePair(values.ad, 0, 1);
    checkValuePair(values.cd);
    checkValuePair(values.rc);
}

TEST_F(CommandOptionsTest, cd) {

    // Specifying a value of zero, we expect all flag values to be zero
    const char* argv1[] = {"badpacket",  "--cd", "0"};
    int argc1 = sizeof(argv1) / sizeof(const char*);

    parse(argc1, const_cast<char**>(argv1));
    checkDefaultOtherValues(*this);
    FlagValues values = getFlagValues();
    checkDefaultFlagValues(values);

    // Check that a value of 1 is accepted
    const char* argv2[] = {"badpacket",  "--cd", "1"};
    int argc2 = sizeof(argv2) / sizeof(const char*);

    parse(argc2, const_cast<char**>(argv2));
    checkDefaultOtherValues(*this);
    values = getFlagValues();
    checkValuePair(values.qr);
    checkValuePair(values.op);
    checkValuePair(values.aa);
    checkValuePair(values.tc);
    checkValuePair(values.z);
    checkValuePair(values.ad);
    checkValuePair(values.cd, 1, 1);
    checkValuePair(values.rc);

    // Check that a range is accepted.
    const char* argv3[] = {"badpacket",  "--cd", "1-0"};
    int argc3 = sizeof(argv3) / sizeof(const char*);

    parse(argc3, const_cast<char**>(argv3));
    checkDefaultOtherValues(*this);
    values = getFlagValues();
    checkValuePair(values.qr);
    checkValuePair(values.op);
    checkValuePair(values.aa);
    checkValuePair(values.tc);
    checkValuePair(values.z);
    checkValuePair(values.ad);
    checkValuePair(values.cd, 0, 1);
    checkValuePair(values.rc);
}

TEST_F(CommandOptionsTest, rc) {

    // Specifying a value of zero, we expect all flag values to be zero
    const char* argv1[] = {"badpacket",  "--rc", "0"};
    int argc1 = sizeof(argv1) / sizeof(const char*);

    parse(argc1, const_cast<char**>(argv1));
    checkDefaultOtherValues(*this);
    FlagValues values = getFlagValues();
    checkDefaultFlagValues(values);

    // Check that a valid value is accepted.
    const char* argv2[] = {"badpacket",  "--rc", "15"};
    int argc2 = sizeof(argv2) / sizeof(const char*);

    parse(argc2, const_cast<char**>(argv2));
    checkDefaultOtherValues(*this);
    values = getFlagValues();
    checkValuePair(values.qr);
    checkValuePair(values.op);
    checkValuePair(values.aa);
    checkValuePair(values.tc);
    checkValuePair(values.z);
    checkValuePair(values.ad);
    checkValuePair(values.cd);
    checkValuePair(values.rc, 15, 15);

    // Check that a range is accepted (in this case, specified backwards and
    // outside the range - so it should be truncated).
    const char* argv3[] = {"badpacket",  "--rc", "8-4"};
    int argc3 = sizeof(argv3) / sizeof(const char*);

    parse(argc3, const_cast<char**>(argv3));
    checkDefaultOtherValues(*this);
    values = getFlagValues();
    checkValuePair(values.qr);
    checkValuePair(values.op);
    checkValuePair(values.aa);
    checkValuePair(values.tc);
    checkValuePair(values.z);
    checkValuePair(values.ad);
    checkValuePair(values.cd);
    checkValuePair(values.rc, 4, 8);
}
