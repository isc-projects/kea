// Copyright (C) 2015 Internet Systems Consortium, Inc. ("ISC")
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

#include <lfc/lfc_controller.h>
#include <gtest/gtest.h>
#include <fstream>
#include <cerrno>

using namespace isc::lfc;
using namespace std;

namespace {

// Filenames used for testing.
const char* PREVIOUS = "lease_file.2";
const char* COPY   = "lease_file.1";
const char* FINISH = "lease_file.completed";
const char* OUTPUT = "lease_file.output";
const char* PID    = "lease_file.pid";

class LFCControllerTest : public ::testing::Test {
public:
    string pstr_;
    string cstr_;
    string fstr_;
    string ostr_;
    string istr_;

    /// @brief Create a file and write the filename into it.
    void touchFile(const std::string& filename, int);

    /// @brief check the file to see if i matches what was written to it.
    bool checkFile(const std::string& filename, int);

protected:
    /// @brief Sets up the file names and Removes any old test
    /// files before the test
    virtual void SetUp() {
        // set up the test files we need
        std::ostringstream prev_str;
        std::ostringstream copy_str;
        std::ostringstream fin_str;
        std::ostringstream out_str;
        std::ostringstream pid_str;

        prev_str << TEST_DATA_BUILDDIR << "/" << PREVIOUS;
        pstr_ = prev_str.str();

        copy_str << TEST_DATA_BUILDDIR << "/" << COPY;
        cstr_ = copy_str.str();

        fin_str << TEST_DATA_BUILDDIR << "/" << FINISH;
        fstr_ = fin_str.str();

        out_str << TEST_DATA_BUILDDIR << "/" << OUTPUT;
        ostr_ = out_str.str();

        pid_str << TEST_DATA_BUILDDIR << "/" << PID;
        istr_ = pid_str.str();

        // and remove any outstanding test files
        removeTestFile();
    }

    /// @brief Removes any remaining test files after the test
    virtual void TearDown() {
        removeTestFile();
    }

private:

    /// @brief Removes any remaining test files
    void removeTestFile() const {
        remove(pstr_.c_str());
        remove(cstr_.c_str());
        remove(fstr_.c_str());
        remove(ostr_.c_str());
        remove(istr_.c_str());
    }

};

void
LFCControllerTest::touchFile(const std::string& filename, int i) {
    std::ofstream fs;

    fs.open(filename, std::ofstream::out);
    fs << i << std::endl;
    fs.close();
}

bool
LFCControllerTest::checkFile(const std::string& filename, int i) {
    std::ifstream fs;
    int j;

    fs.open(filename, std::ifstream::in);
    fs >> j;
    fs.close();

    if (i == j)
        return (true);
    return (false);
}


/// @brief Verify initial state of LFC controller.
/// Create an instance of the controller and see that
/// all of the initial values are empty as expected.
TEST_F(LFCControllerTest, initialValues) {
    LFCController lfc_controller;

    // Verify that we start with all the private variables empty
    EXPECT_EQ(lfc_controller.getProtocolVersion(), 0);
    EXPECT_TRUE(lfc_controller.getConfigFile().empty());
    EXPECT_TRUE(lfc_controller.getPreviousFile().empty());
    EXPECT_TRUE(lfc_controller.getCopyFile().empty());
    EXPECT_TRUE(lfc_controller.getOutputFile().empty());
    EXPECT_TRUE(lfc_controller.getFinishFile().empty());
    EXPECT_TRUE(lfc_controller.getPidFile().empty());
}

/// @brief Verify that parsing a full command line works.
/// Parse a complete command line then verify the parsed
/// and saved data matches our expectations.
TEST_F(LFCControllerTest, fullCommandLine) {
    LFCController lfc_controller;

    // Verify that standard options can be parsed without error
    char* argv[] = { const_cast<char*>("progName"),
                     const_cast<char*>("-4"),
                     const_cast<char*>("-x"),
                     const_cast<char*>("previous"),
                     const_cast<char*>("-i"),
                     const_cast<char*>("copy"),
                     const_cast<char*>("-o"),
                     const_cast<char*>("output"),
                     const_cast<char*>("-c"),
                     const_cast<char*>("config"),
                     const_cast<char*>("-f"),
                     const_cast<char*>("finish"),
                     const_cast<char*>("-p"),
                     const_cast<char*>("pid") };
    int argc = 14;

    ASSERT_NO_THROW(lfc_controller.parseArgs(argc, argv));

    // Check all the parsed data from above to the known values
    EXPECT_EQ(lfc_controller.getProtocolVersion(), 4);
    EXPECT_EQ(lfc_controller.getConfigFile(), "config");
    EXPECT_EQ(lfc_controller.getPreviousFile(), "previous");
    EXPECT_EQ(lfc_controller.getCopyFile(), "copy");
    EXPECT_EQ(lfc_controller.getOutputFile(), "output");
    EXPECT_EQ(lfc_controller.getFinishFile(), "finish");
    EXPECT_EQ(lfc_controller.getPidFile(), "pid");
}

/// @brief Verify that parsing a correct but incomplete line fails.
/// Parse a command line that is correctly formatted but isn't complete
/// (doesn't include some options or an some option arguments).  We
/// expect that the parse will fail with an InvalidUsage exception.
TEST_F(LFCControllerTest, notEnoughData) {
    LFCController lfc_controller;

    // Test the results if we don't include all of the required arguments
    // This argument list is correct but we shall only suppy part of it
    // to the parse routine via the argc variable.
    char* argv[] = { const_cast<char*>("progName"),
                     const_cast<char*>("-4"),
                     const_cast<char*>("-x"),
                     const_cast<char*>("previous"),
                     const_cast<char*>("-i"),
                     const_cast<char*>("copy"),
                     const_cast<char*>("-o"),
                     const_cast<char*>("output"),
                     const_cast<char*>("-c"),
                     const_cast<char*>("config"),
                     const_cast<char*>("-f"),
                     const_cast<char*>("finish"),
                     const_cast<char*>("-p"),
                     const_cast<char*>("pid") };

    int argc = 1;

    for (; argc < 14; ++argc) {
        EXPECT_THROW(lfc_controller.parseArgs(argc, argv), InvalidUsage)
            << "test failed for argc = " << argc;
    }

    // Verify we can still parse the full string properly
    ASSERT_NO_THROW(lfc_controller.parseArgs(argc, argv));
}

/// @brief Verify that extra arguments cause the parse to fail.
/// Parse a full command line plus some extra arguments on the end
/// to verify that we don't stop parsing when we find all of the
/// required arguments.  We exepct the parse to fail with an
/// InvalidUsage exception.
TEST_F(LFCControllerTest, tooMuchData) {
    LFCController lfc_controller;

    // The standard options plus some others

    char* argv[] = { const_cast<char*>("progName"),
                     const_cast<char*>("-4"),
                     const_cast<char*>("-x"),
                     const_cast<char*>("previous"),
                     const_cast<char*>("-i"),
                     const_cast<char*>("copy"),
                     const_cast<char*>("-o"),
                     const_cast<char*>("output"),
                     const_cast<char*>("-c"),
                     const_cast<char*>("config"),
                     const_cast<char*>("-f"),
                     const_cast<char*>("finish"),
                     const_cast<char*>("-p"),
                     const_cast<char*>("pid"),
                     const_cast<char*>("some"),
                     const_cast<char*>("other"),
                     const_cast<char*>("args"),
    };
    int argc = 17;

    // We expect an error as we have arguments that aren't valid
    EXPECT_THROW(lfc_controller.parseArgs(argc, argv), InvalidUsage);
}

/// @brief Verify that unknown arguments cause the parse to fail.
/// Parse some unknown arguments to verify that we generate the
/// proper InvalidUsage exception.
TEST_F(LFCControllerTest, someBadData) {
    LFCController lfc_controller;

    // Some random arguments

    char* argv[] = { const_cast<char*>("progName"),
                     const_cast<char*>("some"),
                     const_cast<char*>("bad"),
                     const_cast<char*>("args"),
    };
    int argc = 4;

    // We expect an error as the arguments aren't valid
    EXPECT_THROW(lfc_controller.parseArgs(argc, argv), InvalidUsage);
}

/// @brief Verify that we do file_cleanup correctly.  We create different
/// files and see if we properly delete and move them.
TEST_F(LFCControllerTest, fileCleanup) {
    LFCController lfc_controller, lfc_controller_launch;

    // We can use the same arguments and controller for all of the tests
    // as the files get redone for each subtest.
    char* argv[] = { const_cast<char*>("progName"),
                     const_cast<char*>("-4"),
                     const_cast<char*>("-x"),
                     const_cast<char*>(pstr_.c_str()),
                     const_cast<char*>("-i"),
                     const_cast<char*>(cstr_.c_str()),
                     const_cast<char*>("-o"),
                     const_cast<char*>(ostr_.c_str()),
                     const_cast<char*>("-c"),
                     const_cast<char*>("config"),
                     const_cast<char*>("-f"),
                     const_cast<char*>(fstr_.c_str()),
                     const_cast<char*>("-p"),
                     const_cast<char*>(istr_.c_str()),
                     const_cast<char*>("-d")
    };
    int argc = 15;
    lfc_controller.parseArgs(argc, argv);

    // Test 1: Start with no files - we expect an execption as there
    // is no file to copy.
    EXPECT_THROW(lfc_controller.fileCleanup(), RunTimeFail);


    // Test 2: Create a file for each of previous, copy and finish.  We should
    // delete the previous and copy files then move finish to previous.
    touchFile(pstr_.c_str(), 1);
    touchFile(cstr_.c_str(), 2);
    touchFile(fstr_.c_str(), 3);

    lfc_controller.fileCleanup();

    // verify finish is now previous and copy and finish are gone
    EXPECT_TRUE(checkFile(pstr_.c_str(), 3));
    EXPECT_TRUE((remove(cstr_.c_str()) != 0) && (errno == ENOENT));
    EXPECT_TRUE((remove(fstr_.c_str()) != 0) && (errno == ENOENT));
    remove(pstr_.c_str());


    // Test 3: Create a file for previous and finish but not copy.
    touchFile(pstr_.c_str(), 4);
    touchFile(fstr_.c_str(), 6);

    lfc_controller.fileCleanup();

    // verify finish is now previous and copy and finish are gone
    EXPECT_TRUE(checkFile(pstr_.c_str(), 6));
    EXPECT_TRUE((remove(cstr_.c_str()) != 0) && (errno == ENOENT));
    EXPECT_TRUE((remove(fstr_.c_str()) != 0) && (errno == ENOENT));
    remove(pstr_.c_str());


    // Test 4: Create a file for copy and finish but not previous.
    touchFile(cstr_.c_str(), 8);
    touchFile(fstr_.c_str(), 9);

    lfc_controller.fileCleanup();

    // verify finish is now previous and copy and finish are gone
    EXPECT_TRUE(checkFile(pstr_.c_str(), 9));
    EXPECT_TRUE((remove(cstr_.c_str()) != 0) && (errno == ENOENT));
    EXPECT_TRUE((remove(fstr_.c_str()) != 0) && (errno == ENOENT));
    remove(pstr_.c_str());


    // Test 5: rerun test 2 but using launch instead of cleanup
    // as we already have a finish file we shouldn't do any extra
    // processing
    touchFile(pstr_.c_str(), 10);
    touchFile(cstr_.c_str(), 11);
    touchFile(fstr_.c_str(), 12);

    lfc_controller_launch.launch(argc, argv);

    // verify finish is now previous and copy and finish are gone
    // as we ran launch we also check to see if the pid is gone.
    EXPECT_TRUE(checkFile(pstr_.c_str(), 12));
    EXPECT_TRUE((remove(cstr_.c_str()) != 0) && (errno == ENOENT));
    EXPECT_TRUE((remove(fstr_.c_str()) != 0) && (errno == ENOENT));
    EXPECT_TRUE((remove(istr_.c_str()) != 0) && (errno == ENOENT));
    remove(pstr_.c_str());
}

} // end of anonymous namespace
