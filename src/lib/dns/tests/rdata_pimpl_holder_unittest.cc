// Copyright (C) 2014  Internet Systems Consortium, Inc. ("ISC")
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
