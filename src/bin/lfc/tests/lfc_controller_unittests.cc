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

#include <lfc/lfc.h>
#include <gtest/gtest.h>

using namespace isc::lfc;
using namespace std;

namespace {

TEST(lfcControllerTest, initialValues) {
    lfcController lfcController;

    // Verify that we start with everything empty
    EXPECT_EQ(lfcController.getProtocolVersion(), 0);
    EXPECT_EQ(lfcController.getConfigFile(), "");
    EXPECT_EQ(lfcController.getPreviousFile(), "");
    EXPECT_EQ(lfcController.getCopyFile(), "");
    EXPECT_EQ(lfcController.getOutputFile(), "");
    EXPECT_EQ(lfcController.getFinishFile(), "");
    EXPECT_EQ(lfcController.getPidFile(), "");
}

TEST(lfcControllerTest, fullCommandLine) {
    lfcController lfcController;

    // Verify that standard options can be parsed without error
    char* argv[] = { const_cast<char*>("progName"),
                     const_cast<char*>("-4"),
                     const_cast<char*>("-p"),
                     const_cast<char*>("previous"),
                     const_cast<char*>("-i"),
                     const_cast<char*>("copy"),
                     const_cast<char*>("-o"),
                     const_cast<char*>("output"),
                     const_cast<char*>("-c"),
                     const_cast<char*>("config"),
                     const_cast<char*>("-f"),
                     const_cast<char*>("finish") };
    int argc = 12;

    EXPECT_NO_THROW(lfcController.parseArgs(argc, argv));

    // The parsed data
    EXPECT_EQ(lfcController.getProtocolVersion(), 4);
    EXPECT_EQ(lfcController.getConfigFile(), "config");
    EXPECT_EQ(lfcController.getPreviousFile(), "previous");
    EXPECT_EQ(lfcController.getCopyFile(), "copy");
    EXPECT_EQ(lfcController.getOutputFile(), "output");
    EXPECT_EQ(lfcController.getFinishFile(), "finish");
}

TEST(lfcControllerTest, notEnoughData) {
    lfcController lfcController;

    // The standard options we shall test what happens
    // if we don't include all of them
    char* argv[] = { const_cast<char*>("progName"),
                     const_cast<char*>("-4"),
                     const_cast<char*>("-p"),
                     const_cast<char*>("previous"),
                     const_cast<char*>("-i"),
                     const_cast<char*>("copy"),
                     const_cast<char*>("-o"),
                     const_cast<char*>("output"),
                     const_cast<char*>("-c"),
                     const_cast<char*>("config"),
                     const_cast<char*>("-f"),
                     const_cast<char*>("finish") };
    int argc = 1;

    EXPECT_THROW(lfcController.parseArgs(argc, argv), InvalidUsage);

    argc = 2;
    EXPECT_THROW(lfcController.parseArgs(argc, argv), InvalidUsage);

    argc = 3;
    EXPECT_THROW(lfcController.parseArgs(argc, argv), InvalidUsage);

    argc = 4;
    EXPECT_THROW(lfcController.parseArgs(argc, argv), InvalidUsage);

    argc = 5;
    EXPECT_THROW(lfcController.parseArgs(argc, argv), InvalidUsage);

    argc = 6;
    EXPECT_THROW(lfcController.parseArgs(argc, argv), InvalidUsage);

    argc = 7;
    EXPECT_THROW(lfcController.parseArgs(argc, argv), InvalidUsage);

    argc = 8;
    EXPECT_THROW(lfcController.parseArgs(argc, argv), InvalidUsage);

    argc = 9;
    EXPECT_THROW(lfcController.parseArgs(argc, argv), InvalidUsage);

    argc = 10;
    EXPECT_THROW(lfcController.parseArgs(argc, argv), InvalidUsage);

    argc = 11;
    EXPECT_THROW(lfcController.parseArgs(argc, argv), InvalidUsage);

}

TEST(lfcControllerTest, tooMuchData) {
    lfcController lfcController;

    // The standard options plus some others

    char* argv[] = { const_cast<char*>("progName"),
                     const_cast<char*>("-4"),
                     const_cast<char*>("-p"),
                     const_cast<char*>("previous"),
                     const_cast<char*>("-i"),
                     const_cast<char*>("copy"),
                     const_cast<char*>("-o"),
                     const_cast<char*>("output"),
                     const_cast<char*>("-c"),
                     const_cast<char*>("config"),
                     const_cast<char*>("-f"),
                     const_cast<char*>("finish"),
                     const_cast<char*>("some"),
                     const_cast<char*>("other"),
                     const_cast<char*>("args"),
    };
    int argc = 15;

    EXPECT_THROW(lfcController.parseArgs(argc, argv), InvalidUsage);
}

TEST(lfcControllerTest, someBadData) {
    lfcController lfcController;

    // The standard options plus some others

    char* argv[] = { const_cast<char*>("progName"),
                     const_cast<char*>("some"),
                     const_cast<char*>("bad"),
                     const_cast<char*>("args"),
    };
    int argc = 4;

    EXPECT_THROW(lfcController.parseArgs(argc, argv), InvalidUsage);
}

} // end of anonymous namespace
