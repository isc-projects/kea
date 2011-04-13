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
    CommandOptionsTest()
    {}

    /// \brief Check Non-Limit Options
    ///
    /// Checks that the options that are NOT related to the message are set to
    /// their default values.
    void checkDefaultOtherValues() {
        EXPECT_EQ("127.0.0.1", getAddress());
        EXPECT_EQ(53, getPort());
        EXPECT_EQ(500, getTimeout());
        EXPECT_EQ("www.example.com", getQname());
    }

    /// \brief Checks the minimum and maximum value specified for an option
    ///
    /// Checks the values for one of the options whose values are stored in the
    /// class's options_ array.
    ///
    /// \param index Index of the option in the limits_ array
    /// \param minval Expected minimum value
    /// \param maxval Expected maximum value
    void checkValuePair(int index, uint32_t minval = 0, uint32_t maxval = 0) {
        EXPECT_EQ(minimum(index), minval);
        EXPECT_EQ(maximum(index), maxval);
    }

    /// \brief Checks that all options are at default values
    ///
    /// Checks that all options have both their maximum and minimum set to the
    /// default values.
    ///
    /// \param except Index not to check. (This allows options not being tested
    ///        to be checked to see that they are at the default value.)  As all
    ///        index values are positive, a negative value means check
    ///        everything.
    void checkDefaultLimitsValues(int except = -1) {
        for (int i = 0; i < OptionInfo::SIZE; ++i) {
            if (i != except) {
                checkValuePair(i, OptionInfo::defval(i),
                               OptionInfo::defval(i));
            }
        }
    }

    /// \brief Check valid command option
    ///
    /// Checks that the command line specification of one of the options taking
    /// a value correctly processes the option.
    ///
    /// \param index Option index
    /// \param optflag Option flag (in the form '--option')
    /// \param optval Value to be passed to the option.
    /// \param minval Expected minimum value
    /// \param maxval Expected maximum value
    void checkCommandValid(int index, const char* optflag, const char* optval,
                           uint32_t minval, uint32_t maxval) {

        // Set up the command line and parse it.
        const char* argv[] = {"badpacket", NULL, NULL};
        argv[1] = optflag;
        argv[2] = optval;
        int argc = 3;
        parse(argc, const_cast<char**>(argv));

        // Check the results.  Everything should be at the defaults except for
        // the specified option, where the minimum and maximum should be as
        // specified.
        checkDefaultOtherValues();
        checkDefaultLimitsValues(index);
        checkValuePair(index, minval, maxval);
    }

    /// \brief Check invalid command option
    ///
    /// Passed a command with an invalid value, checks that the parsing throws
    /// a BadValue exception.
    ///
    /// \param optflag Option flag (in the form '--option')
    /// \param optval Value to be passed to the option.
    void checkCommandInvalid(const char* optflag, const char* optval) {

        // Set up the command line and parse it.
        const char* argv[] = {"badpacket", NULL, NULL};
        argv[1] = optflag;
        argv[2] = optval;
        int argc = 3;
        EXPECT_THROW(parse(argc, const_cast<char**>(argv)), isc::BadValue);
    }

    /// \brief Check one-bit field
    ///
    /// Explicitly for those fields in the flags word that are one bit wide,
    /// perform a series of tests to check that they accept valid values and
    /// reject invalid ones.
    ///
    /// \param index Option index
    /// \param optflag Option flag (in the form '--option')
    void checkOneBitField(int index, const char* optflag) {
        checkCommandValid(index, optflag, "0", 0, 0);
        checkCommandValid(index, optflag, "1", 1, 1);
        checkCommandValid(index, optflag, "0-1", 0, 1);
        checkCommandValid(index, optflag, "1-0", 0, 1);
        checkCommandInvalid(optflag, "0-3");
        checkCommandInvalid(optflag, "4");
        checkCommandInvalid(optflag, "xyz");
    }

    /// \brief Check four-bit field
    ///
    /// Explicitly for those fields in the flags word that are four bits wide,
    /// perform a series of tests to check that they accept valid values and
    /// reject invalid ones.
    ///
    /// \param index Option index
    /// \param optflag Option flag (in the form '--option')
    void checkFourBitField(int index, const char* optflag) {
        checkCommandValid(index, optflag, "0", 0, 0);
        checkCommandValid(index, optflag, "15", 15, 15);
        checkCommandValid(index, optflag, "0-15", 0, 15);
        checkCommandValid(index, optflag, "15-0", 0, 15);
        checkCommandInvalid(optflag, "0-17");
        checkCommandInvalid(optflag, "24");
        checkCommandInvalid(optflag, "xyz");
    }

    /// \brief Check sixteen-bit field
    ///
    /// Explicitly test the parsing of the fields that can take a 16-bit
    /// value ranging from 0 to 65535.
    ///
    /// \param index Option index
    /// \param optflag Option flag (in the form '--option')
    void checkSixteenBitField(int index, const char* optflag) {
        checkCommandValid(index, optflag, "0", 0, 0);
        checkCommandValid(index, optflag, "65535", 65535, 65535);
        checkCommandValid(index, optflag, "0-65535", 0, 65535);
        checkCommandValid(index, optflag, "65535-0", 0, 65535);
        checkCommandInvalid(optflag, "0-65536");
        checkCommandInvalid(optflag, "65537");
        checkCommandInvalid(optflag, "xyz");
    }
};

// Check that each of the non-message options will be recognised

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

// Test options representing the flags fields.

TEST_F(CommandOptionsTest, qr) {
    checkOneBitField(OptionInfo::QR, "--qr");
}

TEST_F(CommandOptionsTest, op) {
    checkFourBitField(OptionInfo::OP, "--op");
}

TEST_F(CommandOptionsTest, aa) {
    checkOneBitField(OptionInfo::AA, "--aa");
}

TEST_F(CommandOptionsTest, tc) {
    checkOneBitField(OptionInfo::TC, "--tc");
}

TEST_F(CommandOptionsTest, z) {
    checkOneBitField(OptionInfo::Z, "--z");
}

TEST_F(CommandOptionsTest, ad) {
    checkOneBitField(OptionInfo::AD, "--ad");
}

TEST_F(CommandOptionsTest, cd) {
    checkOneBitField(OptionInfo::CD, "--cd");
}

TEST_F(CommandOptionsTest, rc) {
    checkFourBitField(OptionInfo::RC, "--rc");
}

// Section count options

TEST_F(CommandOptionsTest, qc) {
    checkSixteenBitField(OptionInfo::QC, "--qc");
}

TEST_F(CommandOptionsTest, ac) {
    checkSixteenBitField(OptionInfo::AC, "--ac");
}

TEST_F(CommandOptionsTest, uc) {
    checkSixteenBitField(OptionInfo::UC, "--uc");
}

TEST_F(CommandOptionsTest, dc) {
    checkSixteenBitField(OptionInfo::DC, "--dc");
}

// ... and the message size option

TEST_F(CommandOptionsTest, ms) {
    int index = OptionInfo::MS;
    const char* optflag = "--ms";

    checkCommandValid(index, optflag, "1", 1, 1);
    checkCommandValid(index, optflag, "65536", 65536, 65536);
    checkCommandValid(index, optflag, "1-65536", 1, 65536);
    checkCommandValid(index, optflag, "65536-1", 1, 65536);
    checkCommandInvalid(optflag, "0");
    checkCommandInvalid(optflag, "1-65537");
    checkCommandInvalid(optflag, "65538");
    checkCommandInvalid(optflag, "xyz");
}
