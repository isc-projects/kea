// Copyright (C) 2015-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <exceptions/exceptions.h>
#include <util/file_utilities.h>
#include <gtest/gtest.h>
#include <fstream>

using namespace isc;
using namespace isc::util::file;
using namespace std;

namespace {

/// @brief Test fixture class for testing operations on files.
class FileUtilTest : public ::testing::Test {
public:

    /// @brief Destructor.
    ///
    /// Deletes the test file if any.
    virtual ~FileUtilTest();
};

FileUtilTest::~FileUtilTest() {
    string test_file_name = string(TEST_DATA_BUILDDIR) + "/fu.test";
    static_cast<void>(remove(test_file_name.c_str()));
}

/// @brief Check an error is returned by getContent on not existent file.
TEST_F(FileUtilTest, notExists) {
    string file_name("/this/does/not/exists");
    try {
        string c = getContent(file_name);
        FAIL() << "this test must throw before this line";
    } catch (const BadValue& ex) {
        string expected = "can't open file '" + file_name;
        expected += "': No such file or directory";
        EXPECT_EQ(string(ex.what()), expected);
    } catch (const std::exception& ex) {
        FAIL() << "unexpected exception: " << ex.what();
    }
}

/// @note No easy can't stat.

/// @brief Check an error is returned by getContent on not regular file.
TEST_F(FileUtilTest, notRegular) {
    string file_name("/");
    try {
        string c = getContent(file_name);
        FAIL() << "this test must throw before this line";
    } catch (const BadValue& ex) {
        string expected = "'" + file_name + "' must be a regular file";
        EXPECT_EQ(string(ex.what()), expected);
    } catch (const std::exception& ex) {
        FAIL() << "unexpected exception: " << ex.what();
    }
}

/// @brief Check getContent works.
TEST_F(FileUtilTest, basic) {
    string file_name = string(TEST_DATA_BUILDDIR) + "/fu.test";
    ofstream fs(file_name.c_str(), ofstream::out | ofstream::trunc);
    ASSERT_TRUE(fs.is_open());
    fs << "abdc";
    fs.close();
    string content;
    EXPECT_NO_THROW(content = getContent(file_name));
    EXPECT_EQ("abdc", content);
}

/// @brief Check isDir works.
TEST_F(FileUtilTest, isDir) {
    EXPECT_TRUE(isDir("/dev"));
    EXPECT_FALSE(isDir("/dev/null"));
    EXPECT_FALSE(isDir("/this/does/not/exists"));
    EXPECT_FALSE(isDir("/etc/hosts"));
}

}
