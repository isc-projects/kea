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

#include "util/interprocess_sync_null.h"
#include <gtest/gtest.h>

using namespace std;

namespace isc {
namespace util {

TEST(InterprocessSyncNullTest, TestNull) {
  InterprocessSyncNull sync("test1");
  InterprocessSyncLocker locker(sync);

  // All of these must always return true

  EXPECT_TRUE(locker.lock());
  EXPECT_TRUE(locker.lock());
  EXPECT_TRUE(locker.lock());
  EXPECT_TRUE(locker.lock());
  EXPECT_TRUE(locker.lock());

  EXPECT_TRUE(locker.unlock());
  EXPECT_TRUE(locker.unlock());
  EXPECT_TRUE(locker.unlock());
  EXPECT_TRUE(locker.unlock());
  EXPECT_TRUE(locker.unlock());

  EXPECT_TRUE(locker.tryLock());
  EXPECT_TRUE(locker.tryLock());
  EXPECT_TRUE(locker.tryLock());
  EXPECT_TRUE(locker.tryLock());
  EXPECT_TRUE(locker.tryLock());

  // Random order

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

} // namespace util
} // namespace isc
