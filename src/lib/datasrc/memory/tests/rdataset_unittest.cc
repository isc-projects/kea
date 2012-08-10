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

#include <util/memory_segment_local.h>

#include <datasrc/memory/rdataset.h>

#include <gtest/gtest.h>

using namespace isc::datasrc::memory;

namespace {

class RdataSetTest : public ::testing::Test {
protected:
    RdataSetTest() {}
    void TearDown() {
        EXPECT_TRUE(mem_sgmt_.allMemoryDeallocated());
    }

    isc::util::MemorySegmentLocal mem_sgmt_;
};

TEST_F(RdataSetTest, create) {
    RdataSet* rdataset = RdataSet::create(mem_sgmt_);
    EXPECT_NE(static_cast<RdataSet*>(NULL), rdataset);
    RdataSet::destroy(mem_sgmt_, rdataset);
}
}
