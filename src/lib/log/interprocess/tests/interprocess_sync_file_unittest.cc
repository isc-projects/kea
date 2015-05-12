// Copyright (C) 2012, 2015  Internet Systems Consortium, Inc. ("ISC")
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

#include <log/interprocess/interprocess_sync_file.h>

#include <util/unittests/check_valgrind.h>
#include <util/unittests/interprocess_util.h>
#include <gtest/gtest.h>
#include <unistd.h>

using namespace std;
using namespace isc::log::interprocess;
using isc::util::unittests::parentReadState;

namespace {
TEST(InterprocessSyncFileTest, TestLock) {
    InterprocessSyncFile sync("test");
    InterprocessSyncLocker locker(sync);

    EXPECT_FALSE(locker.isLocked());
    EXPECT_TRUE(locker.lock());
    EXPECT_TRUE(locker.isLocked());

    if (!isc::util::unittests::runningOnValgrind()) {

        int fds[2];

        // Here, we check that a lock has been taken by forking and
        // checking from the child that a lock exists. This has to be
        // done from a separate process as we test by trying to lock the
        // range again on the lock file. The lock attempt would pass if
        // done from the same process for the granted range. The lock
        // attempt must fail to pass our check.

        EXPECT_EQ(0, pipe(fds));

        if (fork() == 0) {
            unsigned char locked = 0;
            // Child writes to pipe
            close(fds[0]);

            InterprocessSyncFile sync2("test");
            InterprocessSyncLocker locker2(sync2);

            if (!locker2.tryLock()) {
                EXPECT_FALSE(locker2.isLocked());
                locked = 1;
            } else {
                EXPECT_TRUE(locker2.isLocked());
            }

            ssize_t bytes_written = write(fds[1], &locked, sizeof(locked));
            EXPECT_EQ(sizeof(locked), bytes_written);

            close(fds[1]);
            exit(0);
        } else {
            // Parent reads from pipe
            close(fds[1]);

            const unsigned char locked = parentReadState(fds[0]);

            close(fds[0]);

            EXPECT_EQ(1, locked);
        }
    }

    EXPECT_TRUE(locker.unlock());
    EXPECT_FALSE(locker.isLocked());

    EXPECT_EQ (0, remove(TEST_DATA_TOPBUILDDIR "/test_lockfile"));
}

TEST(InterprocessSyncFileTest, TestMultipleFilesDirect) {
  InterprocessSyncFile sync("test1");
  InterprocessSyncLocker locker(sync);

  EXPECT_TRUE(locker.lock());

  InterprocessSyncFile sync2("test2");
  InterprocessSyncLocker locker2(sync2);
  EXPECT_TRUE(locker2.lock());
  EXPECT_TRUE(locker2.unlock());

  EXPECT_TRUE(locker.unlock());

  EXPECT_EQ (0, remove(TEST_DATA_TOPBUILDDIR "/test1_lockfile"));
  EXPECT_EQ (0, remove(TEST_DATA_TOPBUILDDIR "/test2_lockfile"));
}

TEST(InterprocessSyncFileTest, TestMultipleFilesForked) {
    InterprocessSyncFile sync("test1");
    InterprocessSyncLocker locker(sync);

    EXPECT_TRUE(locker.lock());

    if (!isc::util::unittests::runningOnValgrind()) {

        int fds[2];

        EXPECT_EQ(0, pipe(fds));

        if (fork() == 0) {
            unsigned char locked = 0xff;
            // Child writes to pipe
            close(fds[0]);

            InterprocessSyncFile sync2("test2");
            InterprocessSyncLocker locker2(sync2);

            if (locker2.tryLock()) {
                locked = 0;
            }

            ssize_t bytes_written = write(fds[1], &locked, sizeof(locked));
            EXPECT_EQ(sizeof(locked), bytes_written);

            close(fds[1]);
            exit(0);
        } else {
            // Parent reads from pipe
            close(fds[1]);

            const unsigned char locked = parentReadState(fds[0]);

            close(fds[0]);

            EXPECT_EQ(0, locked);
        }

        EXPECT_EQ (0, remove(TEST_DATA_TOPBUILDDIR "/test2_lockfile"));
    }

    EXPECT_TRUE(locker.unlock());

    EXPECT_EQ (0, remove(TEST_DATA_TOPBUILDDIR "/test1_lockfile"));
}

} // unnamed namespace
