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
#include <list>
#include <string>

#include <gtest/gtest.h>

using namespace isc;
using namespace isc::util::file;
using namespace std;

namespace {

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

/// @brief Test fixture for testing PathChecker.
class PathCheckerTest : public ::testing::Test {
public:
    /// @brief Constructor
    PathCheckerTest() {
        env_name_ = "KEA_PATCHECKER_TEST_PATH";
        // Save current value of the environment path.
        char* env_path = std::getenv(env_name_.c_str());
        if (env_path) {
            original_path_ = std::string(env_name_.c_str());
        }

        // Clear the environment path.
        unsetenv(env_name_.c_str());
    }

    /// @brief Destructor
    ~PathCheckerTest() {
        // Restore the original environment path.
        if (!original_path_.empty()) {
            setenv(env_name_.c_str(), original_path_.c_str(), 1);
        } else {
            unsetenv(env_name_.c_str());
        }
    }

    /// @brief Name of env variable for overriding default path.
    std::string env_name_;

    /// @brief Retains the environment variable's original value.
    std::string original_path_;

};

TEST_F(PathCheckerTest, getPathDefault) {
    // No environment variable or explicit path should
    // return the default path after construction.
    ASSERT_FALSE(std::getenv(env_name_.c_str()));
    PathChecker checker("/tmp/def_path", env_name_.c_str());
    ASSERT_EQ(checker.getPath(), checker.getDefaultPath());

    // A subsequent call with reset=true should do the same.
    EXPECT_EQ(checker.getPath(true), checker.getDefaultPath());
}

TEST_F(PathCheckerTest, getPathEnvVariable) {
    // Override default with an env variable upon construction.
    setenv(env_name_.c_str(), "/tmp/override", 1);
    ASSERT_TRUE(std::getenv(env_name_.c_str()));
    PathChecker checker("/tmp/def_path", env_name_.c_str());
    ASSERT_EQ(checker.getPath(), "/tmp/override");

    // A subsequent call with reset=true should do the same.
    EXPECT_EQ(checker.getPath(true), "/tmp/override");
}

TEST_F(PathCheckerTest, getPathExplicit) {
    // Default construction with no env variable.
    ASSERT_FALSE(std::getenv(env_name_.c_str()));
    PathChecker checker("/tmp/def_path", env_name_.c_str());
    ASSERT_EQ(checker.getPath(), checker.getDefaultPath());

    // A subsequent call with reset=true and an explicit path
    // should return the explicit path.
    ASSERT_EQ(checker.getPath(true, "/tmp/explicit"),
              "/tmp/explicit");

    // A subsequent call with no arguments should do the same.
    EXPECT_EQ(checker.getPath(), "/tmp/explicit");
}

// Verifies PathChecker::validatePath() when enforce_path is true.
TEST(PathChecker, validatePathEnforcePath) {
    std::string def_path(TEST_DATA_BUILDDIR);
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
    },
    {
        // Invalid relative path.
        __LINE__,
        "../kea/mylib.so",
        "",
        string("invalid path specified: '../kea', supported path is '" +
               def_path + "'")
    }
    };

    // Create a PathChecker with a supported path of def_path.
    PathChecker checker(def_path);
    for (auto scenario : scenarios) {
        std::ostringstream oss;
        oss << " Scenario at line: " << scenario.line_;
        SCOPED_TRACE(oss.str());
        std::string validated_path;
        if (scenario.exp_error_.empty()) {
            ASSERT_NO_THROW_LOG(validated_path =
                                checker.validatePath(scenario.lib_path_));
            EXPECT_EQ(validated_path, scenario.exp_path_);
        } else {
            ASSERT_THROW_MSG(validated_path =
                             checker.validatePath(scenario.lib_path_),
                             BadValue, scenario.exp_error_);
        }
    }
}

// Verifies PathChecker::validatePath() when enforce_path is false.
TEST(PathChecker, validatePathEnforcePathFalse) {
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

    // Create a PathChecker with a supported path of def_path.
    PathChecker checker(def_path);
    for (auto scenario : scenarios) {
        std::ostringstream oss;
        oss << " Scenario at line: " << scenario.line_;
        SCOPED_TRACE(oss.str());
        std::string validated_path;
        if (scenario.exp_error_.empty()) {
            ASSERT_NO_THROW_LOG(validated_path =
                                checker.validatePath(scenario.lib_path_, false));
            EXPECT_EQ(validated_path, scenario.exp_path_);
        } else {
            ASSERT_THROW_MSG(validated_path =
                             checker.validatePath(scenario.lib_path_, false),
                             BadValue, scenario.exp_error_);
        }
    }
}

}  // namespace
