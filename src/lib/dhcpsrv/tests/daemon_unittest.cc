// Copyright (C) 2014 Internet Systems Consortium, Inc. ("ISC")
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
#include <exceptions/exceptions.h>
#include <dhcpsrv/daemon.h>
#include <gtest/gtest.h>
#include <fstream>

using namespace isc;
using namespace isc::dhcp;

namespace {

/// @brief Test-friendly version of the daemon
///
/// This class exposes internal Daemon class methods.
class NakedDaemon: public Daemon {
public:
    using Daemon::readFile;
};

/// @brief Test class for testing Deamon class
class DaemonTest : public ::testing::Test {
public:

    /// @brief writes specified text to a file
    ///
    /// That is an auxilliary funtion used in fileRead() tests.
    ///
    /// @param content text to be written to disk
    void writeFile(const std::string& content) {
        // Write sample content to disk
        unlink(TEMP_FILE);
        std::ofstream write_me(TEMP_FILE);
        EXPECT_TRUE(write_me.is_open());
        write_me << content;
        write_me.close();
    }

    /// destructor
    ~DaemonTest() {
        static_cast<void>(unlink(TEMP_FILE));
    }

    /// Name of the temporary file
    static const char* TEMP_FILE;

    /// The daemon implementation being tested
    NakedDaemon daemon_;
};

/// Temporary file name used in some tests
const char* DaemonTest::TEMP_FILE="temp-file.json";

// Test checks whether a text file can be read from disk.
TEST_F(DaemonTest, readFile) {

    const char* content = "Horse doesn't eat cucumber salad";

    writeFile(content);

    // Check that the read content is correct
    EXPECT_EQ(std::string(content), daemon_.readFile(TEMP_FILE));

    unlink(TEMP_FILE);
}

// Test checks whether a text file can be read from disk.
TEST_F(DaemonTest, readFileMultiline) {

    const char* no_endline = "A text\nwithout\nendline in the last line";
    const char* with_endline = "A text\nwith\endline in the last line\n";

    // Write sample content to disk
    writeFile(no_endline);

    // Check that the read content is correct
    EXPECT_EQ(std::string(no_endline), daemon_.readFile(TEMP_FILE));

    // Write sample content to disk
    writeFile(with_endline);

    // Check that the read content is correct
    EXPECT_EQ(std::string(with_endline), daemon_.readFile(TEMP_FILE));
}


// Test checks whether comments in file are ignored as expected.
TEST_F(DaemonTest, readFileComments) {
    NakedDaemon x;

    const char* commented_content = "# This is a comment\n"
        "this is a normal line\n"
        "Second line\n"
        "# another comment";

    // The same as above with comments removed and comment lines
    // substituted with empty lines.
    const char* filtered_content ="\nthis is a normal line\nSecond line\n\n";

    // Write sample content to disk
    writeFile(commented_content);

    // Check that the read content is correct (without comment elimination)
    EXPECT_EQ(std::string(commented_content), x.readFile(TEMP_FILE, false));

    // Check that the read content is correct (with comment elimination)
    EXPECT_EQ(std::string(filtered_content), x.readFile(TEMP_FILE, true));



}

// This test checks that missing file will generate an exception.
TEST_F(DaemonTest, readFileError) {

    // Check that the read content is correct
    EXPECT_THROW(daemon_.readFile("no-such-file.txt"), isc::InvalidOperation);
}

};
