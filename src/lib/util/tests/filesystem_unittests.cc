// Copyright (C) 2015-2024 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <exceptions/exceptions.h>
#include <testutils/gtest_utils.h>
#include <util/filesystem.h>

#include <sys/stat.h>
#include <fstream>
#include <list>
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

/// @brief Test fixture class for testing operations on umask.
struct UMaskUtilTest : ::testing::Test {
    /// @brief Constructor.
    ///
    /// Cache the original umask value.
    UMaskUtilTest() : orig_umask_(umask(S_IWGRP | S_IWOTH)) { }

    /// @brief Destructor.
    ///
    /// Restore the original umask value.
    virtual ~UMaskUtilTest() {
        static_cast<void>(umask(orig_umask_));
    }

private:
    /// @brief Original umask.
    mode_t orig_umask_;
};

/// @brief Check setUmask from 0000.
TEST_F(UMaskUtilTest, umask0) {
    static_cast<void>(umask(0));
    ASSERT_NO_THROW(setUmask());
    EXPECT_EQ(S_IWGRP | S_IRWXO, umask(0));
}

/// @brief Check setUmask from no group access.
TEST_F(UMaskUtilTest, umask077) {
    static_cast<void>(umask(S_IRWXG | S_IRWXO));
    ASSERT_NO_THROW(setUmask());
    EXPECT_EQ(S_IRWXG | S_IRWXO, umask(0));
}

/// @brief Check that the components are split correctly.
TEST(PathTest, components) {
    // Complete name
    Path fname("/alpha/beta/gamma.delta");
    EXPECT_EQ("/alpha/beta/gamma.delta", fname.str());
    EXPECT_EQ("/alpha/beta", fname.parentPath());
    EXPECT_EQ("gamma", fname.stem());
    EXPECT_EQ(".delta", fname.extension());
    EXPECT_EQ("gamma.delta", fname.filename());
}

/// @brief Check replaceExtension.
TEST(PathTest, replaceExtension) {
    Path fname("a.b");
    EXPECT_EQ("a.b", fname.str());

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
    EXPECT_EQ("/just/some/dir", fname.parentPath());
    EXPECT_EQ("/just/some/dir/a.b", fname.str());

    fname.replaceParentPath("/just/some/dir");
    EXPECT_EQ("/just/some/dir", fname.parentPath());
    EXPECT_EQ("/just/some/dir/a.b", fname.str());

    fname.replaceParentPath("/");
    EXPECT_EQ("/", fname.parentPath());
    EXPECT_EQ("/a.b", fname.str());

    fname.replaceParentPath("");
    EXPECT_EQ("", fname.parentPath());
    EXPECT_EQ("a.b", fname.str());

    fname = Path("/first/a.b");
    EXPECT_EQ("/first", fname.parentPath());
    EXPECT_EQ("/first/a.b", fname.str());

    fname.replaceParentPath("/just/some/dir");
    EXPECT_EQ("/just/some/dir", fname.parentPath());
    EXPECT_EQ("/just/some/dir/a.b", fname.str());
}

// Verifies FileManager::validatePath() when enforce_path is true.
TEST(FileManager, validatePathEnforcePath) {
    std::string def_path = std::string(TEST_DATA_BUILDDIR) + "/";
    struct Scenario {
        int line_;
        std::string lib_path_;
        std::string exp_path_;
        std::string exp_error_;
    };

    std::list<Scenario> scenarios = {
    {
        // Invalid parent path.
        __LINE__,
        "/var/lib/bs/mylib.so",
        "",
        string("invalid path specified: '/var/lib/bs', supported path is '" + def_path + "'")
    },
    {
        // No file name.
        __LINE__,
        def_path + "/",
        "",
        string ("path: '" + def_path + "/' has no filename")
    },
    {
        // File name only is valid.
        __LINE__,
        "mylib.so",
        def_path + "/mylib.so",
        ""
    },
    {
        // Valid full path.
        __LINE__,
        def_path + "/mylib.so",
        def_path + "/mylib.so",
        ""
    },
    {
        // White space for file name.
        __LINE__,
        "      ",
        "",
        string("path: '' has no filename")
    }
    };

    for (auto scenario : scenarios) {
        std::ostringstream oss;
        oss << " Scenario at line: " << scenario.line_;
        SCOPED_TRACE(oss.str());
        std::string validated_path;
        if (scenario.exp_error_.empty()) {
            ASSERT_NO_THROW_LOG(validated_path =
                                FileManager::validatePath(def_path, scenario.lib_path_));
            EXPECT_EQ(validated_path, scenario.exp_path_);
        } else {
            ASSERT_THROW_MSG(validated_path =
                             FileManager::validatePath(def_path, scenario.lib_path_),
                             BadValue, scenario.exp_error_);
        }
    }
}

// Verifies FileManager::validatePath() when enforce_path is false.
TEST(FileManager, validatePathEnforcePathFalse) {
    std::string def_path(TEST_DATA_BUILDDIR);
    struct Scenario {
        int line_;
        std::string lib_path_;
        std::string exp_path_;
        std::string exp_error_;
    };

    std::list<Scenario> scenarios = {
    {
        // Invalid parent path but shouldn't care.
        __LINE__,
        "/var/lib/bs/mylib.so",
        "/var/lib/bs/mylib.so",
        ""
    },
    {
        // No file name.
        __LINE__,
        def_path + "/",
        "",
        string ("path: '" + def_path + "/' has no filename")
    },
    {
        // File name only is valid.
        __LINE__,
        "mylib.so",
        def_path + "/mylib.so",
        ""
    },
    {
        // Valid full path.
        __LINE__,
        def_path + "/mylib.so",
        def_path + "/mylib.so",
        ""
    },
    {
        // White space for file name.
        __LINE__,
        "      ",
        "",
        string("path: '' has no filename")
    }
    };

    for (auto scenario : scenarios) {
        std::ostringstream oss;
        oss << " Scenario at line: " << scenario.line_;
        SCOPED_TRACE(oss.str());
        std::string validated_path;
        if (scenario.exp_error_.empty()) {
            ASSERT_NO_THROW_LOG(validated_path =
                                FileManager::validatePath(def_path, scenario.lib_path_, false));
            EXPECT_EQ(validated_path, scenario.exp_path_);
        } else {
            ASSERT_THROW_MSG(validated_path =
                             FileManager::validatePath(def_path, scenario.lib_path_, false),
                             BadValue, scenario.exp_error_);
        }
    }
}

}  // namespace
