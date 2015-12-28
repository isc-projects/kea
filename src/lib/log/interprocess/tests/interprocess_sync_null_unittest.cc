// Copyright (C) 2012-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <log/interprocess/interprocess_sync_null.h>
#include <gtest/gtest.h>

using namespace std;
using namespace isc::log::interprocess;

namespace {

TEST(InterprocessSyncNullTest, TestNull) {
  InterprocessSyncNull sync("test1");
  InterprocessSyncLocker locker(sync);

  // Check if the is_locked_ flag is set correctly during lock().
  EXPECT_FALSE(locker.isLocked());
  EXPECT_TRUE(locker.lock());
  EXPECT_TRUE(locker.isLocked());

  // lock() must always return true (this is called 4 times, just an
  // arbitrary number)
  EXPECT_TRUE(locker.lock());
  EXPECT_TRUE(locker.lock());
  EXPECT_TRUE(locker.lock());
  EXPECT_TRUE(locker.lock());

  // Check if the is_locked_ flag is set correctly during unlock().
  EXPECT_TRUE(locker.isLocked());
  EXPECT_TRUE(locker.unlock());
  EXPECT_FALSE(locker.isLocked());

  // unlock() must always return true (this is called 4 times, just an
  // arbitrary number)
  EXPECT_TRUE(locker.unlock());
  EXPECT_TRUE(locker.unlock());
  EXPECT_TRUE(locker.unlock());
  EXPECT_TRUE(locker.unlock());

  // Check if the is_locked_ flag is set correctly during tryLock().
  EXPECT_FALSE(locker.isLocked());
  EXPECT_TRUE(locker.tryLock());
  EXPECT_TRUE(locker.isLocked());

  // tryLock() must always return true (this is called 4 times, just an
  // arbitrary number)
  EXPECT_TRUE(locker.tryLock());
  EXPECT_TRUE(locker.tryLock());
  EXPECT_TRUE(locker.tryLock());
  EXPECT_TRUE(locker.tryLock());

  // Random order (should all return true)
  EXPECT_TRUE(locker.unlock());
  EXPECT_TRUE(locker.lock());
  EXPECT_TRUE(locker.tryLock());
  EXPECT_TRUE(locker.lock());
  EXPECT_TRUE(locker.unlock());
  EXPECT_TRUE(locker.lock());
  EXPECT_TRUE(locker.tryLock());
  EXPECT_TRUE(locker.unlock());
  EXPECT_TRUE(locker.unlock());
}

}
