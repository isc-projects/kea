// Copyright (C) 2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <gtest/gtest.h>

#include <exceptions/exceptions.h>
#include <util/named_callback.h>
#include <testutils/gtest_utils.h>

using namespace isc;
using namespace isc::util;
using namespace std;

namespace {

class NamedCallbackListTest : public ::testing::Test {
public:
    NamedCallbackListTest() {};

    void one() {
        invocations_.push_back(1);
    }

    void two() {
        invocations_.push_back(2);
    }

    void three() {
        invocations_.push_back(3);
    }

    void runCallbacks() {
        invocations_.clear();
        for (auto cb : cbs_.getCallbacks() ) {
            ASSERT_NO_THROW((cb.callback_)());
        }
    }

    NamedCallbackList cbs_;
    std::vector<int> invocations_;
};

TEST_F(NamedCallbackListTest, basics) {

    ASSERT_NO_THROW(cbs_.addCallback("one",
                                     std::bind(&NamedCallbackListTest::one, this)));
    ASSERT_NO_THROW(cbs_.addCallback("two",
                                     std::bind(&NamedCallbackListTest::two, this)));
    ASSERT_NO_THROW(cbs_.addCallback("three",
                                     std::bind(&NamedCallbackListTest::three, this)));

    // Can't add an empty callback.
    ASSERT_THROW_MSG(cbs_.addCallback("nadda", 0),
                     BadValue, "NamedCallbackList - callback: nadda, cannot be empty");

    // Can't add one twice.
    ASSERT_THROW_MSG(cbs_.addCallback("one",
                                      std::bind(&NamedCallbackListTest::one, this)),
                     BadValue, "NamedCallbackList - callback: one, already exists");

    for (auto cb : cbs_.getCallbacks() ) {
        ASSERT_NO_THROW((cb.callback_)());
    }

    int i = 0;
    for (auto invocation : invocations_) {
        EXPECT_EQ(invocation, ++i);
    }

    runCallbacks();

    EXPECT_EQ(3, invocations_.size());
    EXPECT_EQ(1, invocations_[0]);
    EXPECT_EQ(2, invocations_[1]);
    EXPECT_EQ(3, invocations_[2]);

    // Removing two shouldn't throw.
    ASSERT_NO_THROW(cbs_.removeCallback("two"));

    // Removing it again shouldn't throw.
    ASSERT_NO_THROW(cbs_.removeCallback("two"));

    runCallbacks();

    EXPECT_EQ(2, invocations_.size());
    EXPECT_EQ(1, invocations_[0]);
    EXPECT_EQ(3, invocations_[1]);
}

}  // namespace
