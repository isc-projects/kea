// Copyright (C) 2010  Internet Systems Consortium, Inc. ("ISC")
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

// $Id$

#include <algorithm>
#include <string>
#include <vector>

#include <gtest/gtest.h>
#include <boost/lexical_cast.hpp>

#include "../nsas_entry.h"
#include "../hash_table.h"
#include "../hash_key.h"
#include "../lru_list.h"
#include "../hash_deleter.h"

#include "nsas_test.h"
#include "../nsas_entry_compare.h"

using namespace std;

namespace isc {
namespace nsas {


/// \brief Text Fixture Class
class HashDeleterTest : public ::testing::Test {
protected:
    HashDeleterTest() :
        entry1_(new TestEntry("alpha", 1)),
        entry2_(new TestEntry("beta", 2)),
        entry3_(new TestEntry("gamma", 3)),
        entry4_(new TestEntry("delta", 4)),
        entry5_(new TestEntry("epsilon", 5)),
        entry6_(new TestEntry("zeta", 6)),
        entry7_(new TestEntry("eta", 7)),
        hash_table_(new NsasEntryCompare<TestEntry>()),
        lru_list_(3, new HashDeleter<TestEntry>(hash_table_))
    {}


    boost::shared_ptr<TestEntry>    entry1_;
    boost::shared_ptr<TestEntry>    entry2_;
    boost::shared_ptr<TestEntry>    entry3_;
    boost::shared_ptr<TestEntry>    entry4_;
    boost::shared_ptr<TestEntry>    entry5_;
    boost::shared_ptr<TestEntry>    entry6_;
    boost::shared_ptr<TestEntry>    entry7_;

    HashTable<TestEntry>    hash_table_;    ///< Hash table being tested
    LruList<TestEntry>      lru_list_;      ///< Associated LRU list
};


// Basic test.  The test of the constructor etc. have been done in the test
// fixture class.
TEST_F(HashDeleterTest, Constructor) {

    // Add entry1 to both the hash table and the LRU list
    EXPECT_EQ(1, entry1_.use_count());
    hash_table_.add(entry1_, entry1_->hashKey());
    EXPECT_EQ(2, entry1_.use_count());
    lru_list_.add(entry1_);
    EXPECT_EQ(3, entry1_.use_count());

    // Add entry 2.
    EXPECT_EQ(1, entry2_.use_count());
    hash_table_.add(entry2_, entry2_->hashKey());
    EXPECT_EQ(2, entry2_.use_count());
    lru_list_.add(entry2_);
    EXPECT_EQ(3, entry2_.use_count());

    // Add entry 3.
    EXPECT_EQ(1, entry3_.use_count());
    hash_table_.add(entry3_, entry3_->hashKey());
    EXPECT_EQ(2, entry3_.use_count());
    lru_list_.add(entry3_);
    EXPECT_EQ(3, entry3_.use_count());

    // Adding entry 4 should drop entry 1 from the list and from the
    // associated hash table.

    // Add entry 4.
    EXPECT_EQ(1, entry4_.use_count());
    hash_table_.add(entry4_, entry4_->hashKey());
    EXPECT_EQ(2, entry4_.use_count());
    lru_list_.add(entry4_);
    EXPECT_EQ(3, entry4_.use_count());

    // Entry 1 should only be referred to by the text fixture, being removed
    // from both the LRU list and the hash table.
    EXPECT_EQ(1, entry1_.use_count());

    // ... and check that is does not exist in the table.
    boost::shared_ptr<TestEntry> x = hash_table_.get(entry1_->hashKey());
    EXPECT_EQ(NULL, x.get());
}

} // namespace nsas
} // namespace isc
