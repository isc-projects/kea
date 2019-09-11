// Copyright (C) 2018-2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <gtest/gtest.h>

#include <dhcpsrv/thread_resource_mgr.h>

#include <mutex>

using namespace isc::dhcp;
using namespace std;

namespace {

/// @brief Test Fixture for testing isc::dhcp::ThreadResourceMgr
class ThreadResourceMgrTest : public ::testing::Test {
};

template <typename T>
class Resource {
public:
    Resource() {
        lock_guard<std::mutex> lk(mutex_);
        Resource::count_++;
        Resource::created_count_++;
    }

    virtual ~Resource() {
        lock_guard<std::mutex> lk(mutex_);
        Resource::count_--;
        Resource::destroyed_count_++;
    }

    static uint32_t count() {
        lock_guard<std::mutex> lk(mutex_);
        return Resource::count_;
    }

    static uint32_t createdCount() {
        lock_guard<std::mutex> lk(mutex_);
        return Resource::created_count_;
    }

    static uint32_t destroyedCount() {
        lock_guard<std::mutex> lk(mutex_);
        return Resource::destroyed_count_;
    }

    static void reset() {
        lock_guard<std::mutex> lk(mutex_);
        Resource::count_ = 0;
        Resource::created_count_ = 0;
        Resource::destroyed_count_ = 0;
    }
private:
    /// @brief total number of instances at any given time
    static uint32_t count_;

    /// @brief total number of instances ever created
    static uint32_t created_count_;

    /// @brief total number of instances ever destroyed
    static uint32_t destroyed_count_;

    /// @brief mutex used to keep the internal state consistent
    static std::mutex mutex_;
};

// This test verifies that each thread can access it's own allocated resource
TEST(ThreadResourceMgrTest, testThreadResources) {
    ThreadResourceMgr<uint32_t> integers;
    ThreadResourceMgr<bool> bools;
}

}  // namespace
