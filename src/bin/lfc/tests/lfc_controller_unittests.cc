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
#include <util/csv_file.h>
#include <gtest/gtest.h>
#include <fstream>
#include <cerrno>

using namespace isc::lfc;
using namespace std;

namespace {

class LFCControllerTest : public ::testing::Test {
public:
    string pstr_; ///< String for name for pid file
    string xstr_; ///< String for name for previous file
    string istr_; ///< String for name for copy file
    string ostr_; ///< String for name for output file
    string fstr_; ///< String for name for finish file
    string cstr_; ///< String for name for config file

    string v4_hdr_; ///< String for the header of the v4 csv test file
    string v6_hdr_; ///< String for the header of the v6 csv test file

    /// @brief Create a file and write the given string into it.
    void writeFile(const std::string& filename, const std::string& contents) const;

    /// @brief Read a string from a file
    std::string readFile(const std::string& contents) const;

protected:
    /// @brief Sets up the file names and header string and removes 
    /// any old test files before the test
    virtual void SetUp() {
        // set up the test files we need
        string base_dir = TEST_DATA_BUILDDIR;
        string lf = "lease_file.";

        pstr_ = base_dir + "/" + lf + "pid";        // pid
        xstr_ = base_dir + "/" + lf + "2";          // previous
        istr_ = base_dir + "/" + lf + "1";          // copy
        ostr_ = base_dir + "/" + lf + "output";     // output
        fstr_ = base_dir + "/" + lf + "completed";  // finish
        cstr_ = base_dir + "/" + "config_file";     // config

        v4_hdr_ = "address,hwaddr,client_id,valid_lifetime,expire,subnet_id,"
                  "fqdn_fwd,fqdn_rev,hostname\n";

        v6_hdr_ = "address,duid,valid_lifetime,expire,subnet_id,"
                  "pref_lifetime,lease_type,iaid,prefix_len,fqdn_fwd,"
                  "fqdn_rev,hostname,hwaddr\n";

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
        remove(xstr_.c_str());
        remove(istr_.c_str());
        remove(ostr_.c_str());
        remove(fstr_.c_str());
    }

};

std::string
LFCControllerTest::readFile(const std::string& filename) const {
    std::ifstream fs;

    fs.open(filename, std::ifstream::in);
    std::string contents((std::istreambuf_iterator<char>(fs)),
                         std::istreambuf_iterator<char>());
    fs.close();
    return (contents);
}

void
LFCControllerTest::writeFile(const std::string& filename,
                             const std::string& contents) const {
    std::ofstream fs(filename, std::ofstream::out);

    if (fs.is_open()) {
        fs << contents;
        fs.close();
    }
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
    // as the files get redone for each subtest.  We leave "-d" in the arg
    // list but don't pass it as we use 14 as the argument count.  This
    // makes it easy to turn it on by simply increasing argc below to 15
    char* argv[] = { const_cast<char*>("progName"),
                     const_cast<char*>("-4"),
                     const_cast<char*>("-x"),
                     const_cast<char*>(xstr_.c_str()),
                     const_cast<char*>("-i"),
                     const_cast<char*>(istr_.c_str()),
                     const_cast<char*>("-o"),
                     const_cast<char*>(ostr_.c_str()),
                     const_cast<char*>("-c"),
                     const_cast<char*>(cstr_.c_str()),
                     const_cast<char*>("-f"),
                     const_cast<char*>(fstr_.c_str()),
                     const_cast<char*>("-p"),
                     const_cast<char*>(pstr_.c_str()),
                     const_cast<char*>("-d")
    };
    int argc = 14;
    lfc_controller.parseArgs(argc, argv);

    // Test 1: Start with no files - we expect an execption as there
    // is no file to copy.
    EXPECT_THROW(lfc_controller.fileCleanup(), RunTimeFail);


    // Test 2: Create a file for each of previous, copy and finish.  We should
    // delete the previous and copy files then move finish to previous.
    writeFile(xstr_.c_str(), "1");
    writeFile(istr_.c_str(), "2");
    writeFile(fstr_.c_str(), "3");

    lfc_controller.fileCleanup();

    // verify finish is now previous and copy and finish are gone
    EXPECT_EQ(readFile(xstr_.c_str()), "3");
    EXPECT_TRUE((remove(istr_.c_str()) != 0) && (errno == ENOENT));
    EXPECT_TRUE((remove(fstr_.c_str()) != 0) && (errno == ENOENT));
    remove(xstr_.c_str());


    // Test 3: Create a file for previous and finish but not copy.
    writeFile(xstr_.c_str(), "4");
    writeFile(fstr_.c_str(), "6");

    lfc_controller.fileCleanup();

    // verify finish is now previous and copy and finish are gone
    EXPECT_EQ(readFile(xstr_.c_str()), "6");
    EXPECT_TRUE((remove(istr_.c_str()) != 0) && (errno == ENOENT));
    EXPECT_TRUE((remove(fstr_.c_str()) != 0) && (errno == ENOENT));
    remove(xstr_.c_str());


    // Test 4: Create a file for copy and finish but not previous.
    writeFile(istr_.c_str(), "8");
    writeFile(fstr_.c_str(), "9");

    lfc_controller.fileCleanup();

    // verify finish is now previous and copy and finish are gone
    EXPECT_EQ(readFile(xstr_.c_str()), "9");
    EXPECT_TRUE((remove(istr_.c_str()) != 0) && (errno == ENOENT));
    EXPECT_TRUE((remove(fstr_.c_str()) != 0) && (errno == ENOENT));
    remove(xstr_.c_str());


    // Test 5: rerun test 2 but using launch instead of cleanup
    // as we already have a finish file we shouldn't do any extra
    // processing
    writeFile(xstr_.c_str(), "10");
    writeFile(istr_.c_str(), "11");
    writeFile(fstr_.c_str(), "12");

    lfc_controller_launch.launch(argc, argv);

    // verify finish is now previous and copy and finish are gone
    // as we ran launch we also check to see if the pid is gone.
    EXPECT_EQ(readFile(xstr_.c_str()), "12");
    EXPECT_TRUE((remove(istr_.c_str()) != 0) && (errno == ENOENT));
    EXPECT_TRUE((remove(fstr_.c_str()) != 0) && (errno == ENOENT));
    EXPECT_TRUE((remove(pstr_.c_str()) != 0) && (errno == ENOENT));
    remove(xstr_.c_str());
}

/// @brief Verify that we properly combine and clean up files
///
/// This is mostly a retest as we already test that the loader and
/// writer functions work in their own tests but we combine it all
/// here.  We check: both files available, only previous, only copy
/// neither and one of them having many lease errors.  This is the
/// v4 version.

TEST_F(LFCControllerTest, launch4) {
    LFCController lfc_controller;

    // The arg list for our test.  We generally use the
    // same file names to make it easy.  We include the -d
    // in the argv list in case we want to enable verbose
    // for debugging purposes.  To enable it change argc from
    // 14 to 15
    char* argv[] = { const_cast<char*>("progName"),
                     const_cast<char*>("-4"),
                     const_cast<char*>("-x"),
                     const_cast<char*>(xstr_.c_str()),
                     const_cast<char*>("-i"),
                     const_cast<char*>(istr_.c_str()),
                     const_cast<char*>("-o"),
                     const_cast<char*>(ostr_.c_str()),
                     const_cast<char*>("-c"),
                     const_cast<char*>(cstr_.c_str()),
                     const_cast<char*>("-f"),
                     const_cast<char*>(fstr_.c_str()),
                     const_cast<char*>("-p"),
                     const_cast<char*>(pstr_.c_str()),
                     const_cast<char*>("-d")
    };
    int argc = 14;
    string test_str, astr;

    // Create the various strings we want to use, the header is predefined.
    // We have several entries for different leases, the naming is:
    // <lease letter>_<version#>
    string A_1 = "192.0.2.1,06:07:08:09:0a:bc,,"
                 "200,200,8,1,1,host.example.com\n";
    string A_2 = "192.0.2.1,06:07:08:09:0a:bc,,"
                 "200,500,8,1,1,host.example.com\n";
    string A_3 = "192.0.2.1,06:07:08:09:0a:bc,,"
                 "200,800,8,1,1,host.example.com\n";

    string B_1 = "192.0.3.15,dd:de:ba:0d:1b:2e:3e:4f,0a:00:01:04,"
                 "100,100,7,0,0,\n";
    string B_2 = "192.0.3.15,dd:de:ba:0d:1b:2e:3e:4f,0a:00:01:04,"
                 "100,135,7,0,0,\n";
    string B_3 = "192.0.3.15,dd:de:ba:0d:1b:2e:3e:4f,0a:00:01:04,"
                 "100,150,7,0,0,\n";

    string C_1 = "192.0.2.3,,a:11:01:04,"
                 "200,200,8,1,1,host.example.com\n";

    string D_1 = "192.0.2.5,16:17:18:19:1a:bc,,"
                 "200,200,8,1,1,host.example.com\n";
    string D_2 = "192.0.2.5,16:17:18:19:1a:bc,,"
                 "0,200,8,1,1,host.example.com\n";

    // Subtest 1: both previous and copy available.
    // Create the test previous file
    test_str = v4_hdr_ + A_1 + B_1 + C_1 + B_2 + A_2 + D_1;
    writeFile(xstr_.c_str(), test_str);

    // Create the test copy file
    test_str = v4_hdr_ + A_3 + B_3 + D_2;
    writeFile(istr_.c_str(), test_str);

    // Run the cleanup
    lfc_controller.launch(argc, argv);

    // Compare the results, we expect the last lease for each ip
    // except for C which was invalid and D which has expired
    test_str = v4_hdr_ + A_3 + B_3;
    EXPECT_EQ(readFile(xstr_.c_str()), test_str);
    remove(xstr_.c_str());


    // Subtest 2: only previous available
    // Create the test previous file
    test_str = v4_hdr_ + A_1 + B_1 + C_1 + B_2 + A_2 + D_1;
    writeFile(xstr_.c_str(), test_str);

    // No copy file

    // Run the cleanup
    lfc_controller.launch(argc, argv);

    // Compare the results, we expect the last lease for each ip
    // except for C which was invalid and D which has expired
    test_str = v4_hdr_ + A_2 + D_1 + B_2;
    EXPECT_EQ(readFile(xstr_.c_str()), test_str);
    remove(xstr_.c_str());


    // Subtest 3: only copy available
    // No previous file

    // Create the test copy file
    test_str = v4_hdr_ + D_1 + A_1 + B_1 + B_3 + D_2 + A_3;
    writeFile(istr_.c_str(), test_str);

    // Run the cleanup
    lfc_controller.launch(argc, argv);

    // Compare the results, we expect the last lease for each ip
    // except for C which was invalid and D which has expired
    test_str = v4_hdr_ + A_3 + B_3;
    EXPECT_EQ(readFile(xstr_.c_str()), test_str);
    remove(xstr_.c_str());


    // Subtest 4: neither available
    // No previous file

    // No copy file

    // Run the cleanup
    lfc_controller.launch(argc, argv);

    // Compare the results, we expect a header and no leaes
    test_str = v4_hdr_;
    EXPECT_EQ(readFile(xstr_.c_str()), test_str);
    remove(xstr_.c_str());


    // Subtest 5: a file with a lot of errors
    // A previous file with a lot of errors
    astr = "1,\n2,\n3,\n4,\n5,\n6,\n7,\n7,\n8,\n9,\n10,\n";
    test_str = v4_hdr_ + astr + astr + astr + astr + astr +
               astr + astr + astr + astr + astr + astr;
    writeFile(xstr_.c_str(), test_str);

    // No copy file

    // Run the cleanup, the file should fail but we should
    // catch the error and properly cleanup.
    lfc_controller.launch(argc, argv);

    // And we shouldn't have deleted the previous file, but should
    // have deleted the pid file
    EXPECT_EQ(readFile(xstr_.c_str()), test_str);
    EXPECT_TRUE((remove(pstr_.c_str()) != 0) && (errno == ENOENT));
}

/// @brief Verify that we properly combine and clean up files
///
/// This is mostly a retest as we already test that the loader and
/// writer functions work in their own tests but we combine it all
/// here.  We check: both files available, only previous, only copy
/// neither and one of them having many lease errors.  This is the
/// v6 version.

TEST_F(LFCControllerTest, launch6) {
    LFCController lfc_controller;

    // The arg list for our test.  We generally use the
    // same file names to make it easy.  We include the -d
    // in the argv list in case we want to enable verbose
    // for debugging purposes.  To enable it change argc from
    // 14 to 15
    char* argv[] = { const_cast<char*>("progName"),
                     const_cast<char*>("-6"),
                     const_cast<char*>("-x"),
                     const_cast<char*>(xstr_.c_str()),
                     const_cast<char*>("-i"),
                     const_cast<char*>(istr_.c_str()),
                     const_cast<char*>("-o"),
                     const_cast<char*>(ostr_.c_str()),
                     const_cast<char*>("-c"),
                     const_cast<char*>(cstr_.c_str()),
                     const_cast<char*>("-f"),
                     const_cast<char*>(fstr_.c_str()),
                     const_cast<char*>("-p"),
                     const_cast<char*>(pstr_.c_str()),
                     const_cast<char*>("-d")
    };
    int argc = 14;
    string test_str, astr;

    // Create the various strings we want to use, the header is predefined.
    // We have several entries for different leases, the naming is:
    // <lease letter>_<version#>.
    string A_1 = "2001:db8:1::1,00:01:02:03:04:05:06:0a:0b:0c:0d:0e:0f,"
                 "200,200,8,100,0,7,0,1,1,host.example.com,\n";
    string A_2 = "2001:db8:1::1,,200,200,8,100,0,7,0,1,1,host.example.com,\n";
    string A_3 = "2001:db8:1::1,00:01:02:03:04:05:06:0a:0b:0c:0d:0e:0f,"
                 "200,400,8,100,0,7,0,1,1,host.example.com,\n";
    string A_4 = "2001:db8:1::1,00:01:02:03:04:05:06:0a:0b:0c:0d:0e:0f,"
                 "0,200,8,100,0,7,0,1,1,host.example.com,\n";

    string B_1 = "2001:db8:2::10,01:01:01:01:0a:01:02:03:04:05,"
                 "300,300,6,150,0,8,0,0,0,,\n";
    string B_2 = "2001:db8:2::10,01:01:01:01:0a:01:02:03:04:05,"
                 "300,800,6,150,0,8,0,0,0,,\n";
    string B_3 = "2001:db8:2::10,01:01:01:01:0a:01:02:03:04:05,"
                 "300,1000,6,150,0,8,0,0,0,,\n";

    string C_1 = "3000:1::,00:01:02:03:04:05:06:0a:0b:0c:0d:0e:0f,100,200,8,0,2,"
                 "16,64,0,0,,\n";
    string C_2 = "3000:1::,00:01:02:03:04:05:06:0a:0b:0c:0d:0e:0f,100,400,8,0,2,"
                 "16,64,0,0,,\n";

    string D_1 = "2001:db8:1::3,00:01:02:03:04:05:06:0a:0b:0c:0d:0e:0f,"
                 "200,600,8,100,0,7,0,1,1,host.example.com,\n";

    // Subtest 1: bot previous and copy available
    // Create the test previous file
    test_str = v6_hdr_ + A_1 + B_1 + A_2 + C_1 + A_3 + B_2;
    writeFile(xstr_.c_str(), test_str);

    // Create the test copy file
    test_str = v6_hdr_ + B_3 + A_4 + D_1 + C_2;
    writeFile(istr_.c_str(), test_str);

    // Run the cleanup
    lfc_controller.launch(argc, argv);

    // Compare the results, we expect the last lease for each ip
    // except for A which has expired
    test_str = v6_hdr_ + D_1 + B_3 + C_2;
    EXPECT_EQ(readFile(xstr_.c_str()), test_str);
    remove(xstr_.c_str());


    // Subtest 2: only previous available
    // Create the test previous file
    test_str = v6_hdr_ + A_1 + B_1 + A_2 + C_1 + A_3 + B_2;
    writeFile(xstr_.c_str(), test_str);

    // No copy file

    // Run the cleanup
    lfc_controller.launch(argc, argv);

    // Compare the results, we expect the last lease for each ip
    // except for A which has expired
    test_str = v6_hdr_ + A_3 + B_2 + C_1;
    EXPECT_EQ(readFile(xstr_.c_str()), test_str);
    remove(xstr_.c_str());


    // Subtest 3: only copy available
    // No previous file

    // Create the test copy file
    test_str = v6_hdr_ + A_1 + B_2 + B_3 + A_4 + D_1 + C_2;
    writeFile(istr_.c_str(), test_str);

    // Run the cleanup
    lfc_controller.launch(argc, argv);

    // Compare the results, we expect the last lease for each ip
    // except for A which has expired
    test_str = v6_hdr_ + D_1 + B_3 + C_2;
    EXPECT_EQ(readFile(xstr_.c_str()), test_str);
    remove(xstr_.c_str());


    // Subtest 4: neither available
    // No previous file

    // No copy file

    // Run the cleanup
    lfc_controller.launch(argc, argv);

    // Compare the results, we expect a header and no leases
    test_str = v6_hdr_;
    EXPECT_EQ(readFile(xstr_.c_str()), test_str);
    remove(xstr_.c_str());


    // Subtest 5: a file with a lot of errors
    // A previous file with a lot of errors
    astr = "1,\n2,\n3,\n4,\n5,\n6,\n7,\n7,\n8,\n9,\n10,\n";
    test_str = v6_hdr_ + astr + astr + astr + astr + astr +
               astr + astr + astr + astr + astr + astr;
    writeFile(xstr_.c_str(), test_str);

    // No copy file

    // Run the cleanup, the file should fail but we should
    // catch the error and properly cleanup.
    lfc_controller.launch(argc, argv);

    // And we shouldn't have deleted the previous file, but should
    // have deleted the pid file
    EXPECT_EQ(readFile(xstr_.c_str()), test_str);
    EXPECT_TRUE((remove(pstr_.c_str()) != 0) && (errno == ENOENT));

}

} // end of anonymous namespace
