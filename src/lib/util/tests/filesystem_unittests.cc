// Copyright (C) 2015-2024 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <exceptions/exceptions.h>
#include <testutils/gtest_utils.h>
#include <util/filesystem.h>

#include <fstream>
#include <string>

#include <gtest/gtest.h>

using namespace isc;
using namespace isc::util::file;
using namespace std;

namespace {

/// @brief Test fixture class for testing operations on files.
struct FileUtilTest : ::testing::Test {
    /// @brief Destructor.
    ///
    /// Deletes the test file if any.
    virtual ~FileUtilTest() {
        string test_file_name(TEST_DATA_BUILDDIR "/fu.test");
        static_cast<void>(remove(test_file_name.c_str()));
    }
};

/// @brief Check that an error is returned by getContent on non-existent file.
TEST_F(FileUtilTest, notExist) {
    EXPECT_THROW_MSG(getContent("/does/not/exist"), BadValue,
                     "Expected a file at path '/does/not/exist'");
}

/// @brief Check that an error is returned by getContent on not regular file.
TEST_F(FileUtilTest, notRegular) {
    EXPECT_THROW_MSG(getContent("/"), BadValue, "Expected '/' to be a regular file");
}

/// @brief Check getContent.
TEST_F(FileUtilTest, getContent) {
    string file_name(TEST_DATA_BUILDDIR "/fu.test");
    ofstream fs(file_name.c_str(), ofstream::out | ofstream::trunc);
    ASSERT_TRUE(fs.is_open());
    fs << "abdc";
    fs.close();
    string content;
    EXPECT_NO_THROW_LOG(content = getContent(file_name));
    EXPECT_EQ("abdc", content);
}

/// @brief Check isDir.
TEST_F(FileUtilTest, isDir) {
    EXPECT_TRUE(isDir("/dev"));
    EXPECT_FALSE(isDir("/dev/null"));
    EXPECT_FALSE(isDir("/this/does/not/exist"));
    EXPECT_FALSE(isDir("/etc/hosts"));
}

/// @brief Check isFile.
TEST_F(FileUtilTest, isFile) {
    EXPECT_TRUE(isFile(ABS_SRCDIR "/filesystem_unittests.cc"));
    EXPECT_FALSE(isFile(TEST_DATA_BUILDDIR));
}

/// @brief Check that the components are split correctly.
TEST(PathTest, components) {
    // Complete name
    Path fname("/alpha/beta/gamma.delta");
    EXPECT_EQ("/alpha/beta/", fname.parentPath());
    EXPECT_EQ("gamma", fname.stem());
    EXPECT_EQ(".delta", fname.extension());
    EXPECT_EQ("gamma.delta", fname.filename());
}

/// @brief Check replaceExtension.
TEST(PathTest, replaceExtension) {
    Path fname("a.b");

    EXPECT_EQ("a", fname.replaceExtension("").str());
    EXPECT_EQ("a.f", fname.replaceExtension(".f").str());
    EXPECT_EQ("a.f", fname.replaceExtension("f").str());
    EXPECT_EQ("a./c/d/", fname.replaceExtension(" /c/d/  ").str());
    EXPECT_EQ("a.f", fname.replaceExtension("/c/d/e.f").str());
    EXPECT_EQ("a.f", fname.replaceExtension("e.f").str());
}

/// @brief Check replaceParentPath.
TEST(PathTest, replaceParentPath) {
    Path fname("a.b");
    EXPECT_EQ("", fname.parentPath());
    EXPECT_EQ("a.b", fname.str());

    fname.replaceParentPath("/just/some/dir/");
    EXPECT_EQ("/just/some/dir/", fname.parentPath());
    EXPECT_EQ("/just/some/dir/a.b", fname.str());

    fname.replaceParentPath("/just/some/dir");
    EXPECT_EQ("/just/some/dir/", fname.parentPath());
    EXPECT_EQ("/just/some/dir/a.b", fname.str());

    fname.replaceParentPath("/");
    EXPECT_EQ("/", fname.parentPath());
    EXPECT_EQ("/a.b", fname.str());

    fname.replaceParentPath("");
    EXPECT_EQ("", fname.parentPath());
    EXPECT_EQ("a.b", fname.str());

    fname = Path("/first/a.b");
    EXPECT_EQ("/first/", fname.parentPath());
    EXPECT_EQ("/first/a.b", fname.str());

    fname.replaceParentPath("/just/some/dir");
    EXPECT_EQ("/just/some/dir/", fname.parentPath());
    EXPECT_EQ("/just/some/dir/a.b", fname.str());
}

}  // namespace
