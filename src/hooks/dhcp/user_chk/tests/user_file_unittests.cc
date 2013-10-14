// Copyright (C) 2013  Internet Systems Consortium, Inc. ("ISC")
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

#include <exceptions/exceptions.h>
#include <test_data_files_config.h>
#include <user_file.h>

#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <gtest/gtest.h>

using namespace std;

namespace {

std::string testFilePath(const std::string& name) {
    return (std::string(USER_CHK_TEST_DIR) + "/" + name);
}

TEST(UserFile, construction) {
    ASSERT_THROW(UserFile(""), UserFileError);

    ASSERT_NO_THROW(UserFile("someName"));
}

TEST(UserFile, openFile) {
    UserFilePtr user_file;

    // Construct a user file that refers to a non existant file.
    ASSERT_NO_THROW(user_file.reset(new UserFile("NoSuchFile")));
    EXPECT_FALSE(user_file->isOpen());

    // Verify a non-existant file fails to open
    ASSERT_THROW(user_file->open(), UserFileError);
    EXPECT_FALSE(user_file->isOpen());

    // Construct a user file that should exist.
    ASSERT_NO_THROW(user_file.reset(new
                                    UserFile(testFilePath("test_users_1.txt"))));
    EXPECT_FALSE(user_file->isOpen());

    // Verify that we can open it.
    ASSERT_NO_THROW(user_file->open());
    EXPECT_TRUE(user_file->isOpen());

    // Verify that we cannot open an already open file.
    ASSERT_THROW(user_file->open(), UserFileError);

    // Verifyt we can close it.
    ASSERT_NO_THROW(user_file->close());
    EXPECT_FALSE(user_file->isOpen());

    // Verify that we can reopen it.
    ASSERT_NO_THROW(user_file->open());
    EXPECT_TRUE(user_file->isOpen());
}

TEST(UserFile, readFile) {
    UserFilePtr user_file;

    // Construct an open a known file.
    ASSERT_NO_THROW(user_file.reset(new
                                    UserFile(testFilePath("test_users_1.txt"))));
    ASSERT_NO_THROW(user_file->open());
    EXPECT_TRUE(user_file->isOpen());

    UserPtr user;
    int i = 0;
    do {
        ASSERT_NO_THROW(user = user_file->readNextUser());
        switch (i++) {
            case 0:
                EXPECT_EQ(UserId::HW_ADDRESS, user->getUserId().getType());
                EXPECT_EQ("01ac00f03344", user->getUserId().toText());
                EXPECT_EQ("true", user->getProperty("opt1"));
                break;
            case 1:
                EXPECT_EQ(UserId::CLIENT_ID, user->getUserId().getType());
                EXPECT_EQ("0899e0cc0707", user->getUserId().toText());
                EXPECT_EQ("false", user->getProperty("opt1"));
                break;
            case 2:
                EXPECT_EQ(UserId::DUID, user->getUserId().getType());
                EXPECT_EQ("225060de0a0b", user->getUserId().toText());
                EXPECT_EQ("true", user->getProperty("opt1"));
                break;
            default:
                // this is an error, TBD
                break;
        }
    } while (user);


    ASSERT_NO_THROW(user_file->close());
}



} // end of anonymous namespace
