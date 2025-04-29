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

}  // namespace
