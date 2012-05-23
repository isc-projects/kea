// Copyright (C) 2012  Internet Systems Consortium, Inc. ("ISC")
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

#include "util/interprocess_sync_file.h"
#include <gtest/gtest.h>

using namespace std;

namespace isc {
namespace util {

class InterprocessSyncFileTest : public ::testing::Test {
protected:
    InterprocessSyncFileTest() {}
};

TEST_F(InterprocessSyncFileTest, TestLock) {
  InterprocessSync* sync = new InterprocessSyncFile("test");
  InterprocessSyncLocker* locker = sync->getLocker();

  EXPECT_TRUE(locker->lock());

  int fds[2];

  // Here, we check that a lock has been taken by forking and
  // checking from the child that a lock exists. This has to be
  // done from a separate process as we test by trying to lock the
  // range again on the lock file. The lock attempt would pass if
  // done from the same process for the granted range. The lock
  // attempt must fail to pass our check.

  bool was_locked(false);

  pipe(fds);

  if (fork() == 0) {
      unsigned char locked = 0;
      // Child writes to pipe
      close(fds[0]);

      InterprocessSync* sync2 = new InterprocessSyncFile("test");
      InterprocessSyncLocker* locker2 = sync2->getLocker();

      if (!locker2->tryLock()) {
          locked = 1;
      }

      delete locker2;
      delete sync2;

      write(fds[1], &locked, sizeof(locked));
      close(fds[1]);
      exit(0);
  } else {
      unsigned char locked = 0;
      // Parent reads from pipe
      close(fds[1]);

      // Read status and set flag
      read(fds[0], &locked, sizeof(locked));
      if (locked == 1) {
        was_locked = true;
      } else {
        was_locked = false;
      }

      close(fds[0]);
  }

  EXPECT_TRUE(was_locked);
  EXPECT_TRUE(locker->unlock());

  delete locker;
  delete sync;
}

TEST_F(InterprocessSyncFileTest, TestMultipleFilesDirect) {
  InterprocessSync* sync = new InterprocessSyncFile("test1");
  InterprocessSyncLocker* locker = sync->getLocker();

  EXPECT_TRUE(locker->lock());

  InterprocessSync* sync2 = new InterprocessSyncFile("test2");
  InterprocessSyncLocker* locker2 = sync2->getLocker();
  EXPECT_TRUE(locker2->lock());
  EXPECT_TRUE(locker2->unlock());
  delete sync2;
  delete locker2;

  EXPECT_TRUE(locker->unlock());

  delete locker;
  delete sync;
}

TEST_F(InterprocessSyncFileTest, TestMultipleFilesForked) {
  InterprocessSync* sync = new InterprocessSyncFile("test");
  InterprocessSyncLocker* locker = sync->getLocker();

  EXPECT_TRUE(locker->lock());

  int fds[2];

  bool was_not_locked(true);

  pipe(fds);

  if (fork() == 0) {
      unsigned char locked = 0xff;
      // Child writes to pipe
      close(fds[0]);

      InterprocessSync* sync2 = new InterprocessSyncFile("test2");
      InterprocessSyncLocker* locker2 = sync2->getLocker();

      if (locker2->tryLock()) {
          locked = 0;
      }

      delete locker2;
      delete sync2;

      write(fds[1], &locked, sizeof(locked));
      close(fds[1]);
      exit(0);
  } else {
      unsigned char locked = 0xff;
      // Parent reads from pipe
      close(fds[1]);

      // Read status and set flag
      read(fds[0], &locked, sizeof(locked));
      if (locked == 0) {
        was_not_locked = true;
      } else {
        was_not_locked = false;
      }

      close(fds[0]);
  }

  EXPECT_TRUE(was_not_locked);
  EXPECT_TRUE(locker->unlock());

  delete locker;
  delete sync;
}

} // namespace util
} // namespace isc
