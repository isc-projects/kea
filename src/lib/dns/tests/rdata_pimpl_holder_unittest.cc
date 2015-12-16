// Copyright (C) 2014-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <dns/rdata_pimpl_holder.h>

#include <gtest/gtest.h>

using namespace isc::dns::rdata;

namespace {

TEST(RdataPimplHolderTest, all) {
    // Let's check with an integer
    int* i1 = new int(42);
    RdataPimplHolder<int> holder1(i1);
    // The same pointer must be returned.
    EXPECT_EQ(i1, holder1.get());
    // Obviously the value should match too.
    EXPECT_EQ(42, *holder1.get());
    // We don't explictly delete i or holder1, so it should not leak
    // anything when the test is done (checked by Valgrind).

    // The following cases are similar:

    // Test no-argument reset()
    int* i2 = new int(43);
    RdataPimplHolder<int> holder2(i2);
    holder2.reset();
    EXPECT_EQ(NULL, holder2.get());

    // Test reset() with argument
    int* i3 = new int(44);
    int* i4 = new int(45);
    RdataPimplHolder<int> holder3(i3);
    EXPECT_EQ(i3, holder3.get());
    holder3.reset(i4);
    EXPECT_EQ(i4, holder3.get());
    EXPECT_EQ(45, *holder3.get());

    // Test release()
    RdataPimplHolder<int> holder4(new int(46));
    EXPECT_NE(static_cast<void*>(NULL), holder4.get());
    EXPECT_EQ(46, *holder4.get());
    int* i5 = holder4.release();
    EXPECT_EQ(NULL, holder4.get());
    EXPECT_NE(static_cast<void*>(NULL), i5);
    EXPECT_EQ(46, *i5);
    delete i5;
}

}
