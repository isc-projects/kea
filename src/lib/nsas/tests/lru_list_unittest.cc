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

#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

#include <gtest/gtest.h>
#include <boost/lexical_cast.hpp>

#include "../nsas_entry.h"
#include "../lru_list.h"

#include "nsas_test.h"

using namespace std;

namespace isc {
namespace nsas {

/// \brief Dropped Functor Class
///
/// Functor object is called when an object is dropped from the LRU list.
/// To prove that it has run, this function does nothing more than set the
/// MS bit on the 16-bit class value.
class Dropped : public LruList<TestEntry>::Dropped {
public:
    virtual void operator()(TestEntry* entry) const {
        entry->setClass(entry->getClass() | 0x8000);
    }
};


/// \brief Text Fixture Class
class LruListTest : public ::testing::Test {
protected:
    LruListTest() :
        entry1_(new TestEntry("alpha", 1)),
        entry2_(new TestEntry("beta", 2)),
        entry3_(new TestEntry("gamma", 3)),
        entry4_(new TestEntry("delta", 4)),
        entry5_(new TestEntry("epsilon", 5)),
        entry6_(new TestEntry("zeta", 6)),
        entry7_(new TestEntry("eta", 7))
    {}

    virtual ~LruListTest() 
    {}

    boost::shared_ptr<TestEntry>    entry1_;
    boost::shared_ptr<TestEntry>    entry2_;
    boost::shared_ptr<TestEntry>    entry3_;
    boost::shared_ptr<TestEntry>    entry4_;
    boost::shared_ptr<TestEntry>    entry5_;
    boost::shared_ptr<TestEntry>    entry6_;
    boost::shared_ptr<TestEntry>    entry7_;
};


// Test of the constructor
TEST_F(LruListTest, Constructor) {
    LruList<TestEntry>  lru(100);
    EXPECT_EQ(100, lru.getMaxSize());
    EXPECT_EQ(0, lru.size());
}

// Test of Get/Set the maximum number of entrys
TEST_F(LruListTest, GetSet) {
    LruList<TestEntry>  lru(100);
    EXPECT_EQ(100, lru.getMaxSize());
    lru.setMaxSize(42);
    EXPECT_EQ(42, lru.getMaxSize());
}

// Test that adding an entry really does add an entry
TEST_F(LruListTest, Add) {
    LruList<TestEntry>  lru(100);
    EXPECT_EQ(0, lru.size());

    lru.add(entry1_);
    EXPECT_EQ(1, lru.size());

    lru.add(entry2_);
    EXPECT_EQ(2, lru.size());
}

// Test that removing an entry really does remove it.
TEST_F(LruListTest, Remove) {
    LruList<TestEntry>  lru(100);
    EXPECT_EQ(0, lru.size());

    EXPECT_FALSE(entry1_->iteratorValid());
    lru.add(entry1_);
    EXPECT_TRUE(entry1_->iteratorValid());
    EXPECT_EQ(1, lru.size());

    EXPECT_FALSE(entry2_->iteratorValid());
    lru.add(entry2_);
    EXPECT_TRUE(entry2_->iteratorValid());
    EXPECT_EQ(2, lru.size());

    lru.remove(entry1_);
    EXPECT_FALSE(entry1_->iteratorValid());
    EXPECT_EQ(1, lru.size());
}

// Check that adding a new entry to a limited size list does delete the
// oldest entry from the list.
TEST_F(LruListTest, SizeLimit) {
    LruList<TestEntry>  lru(3);
    EXPECT_EQ(0, lru.size());

    // Add first entry and check that the shared pointer's reference count
    // has increased.  There will be two references: one from the "entry1_"
    // member in the test fixture class, and one from the list.
    EXPECT_EQ(1, entry1_.use_count());
    lru.add(entry1_);
    EXPECT_EQ(2, entry1_.use_count());
    EXPECT_EQ(1, lru.size());

    // Same for entry 2.
    EXPECT_EQ(1, entry2_.use_count());
    lru.add(entry2_);
    EXPECT_EQ(2, entry2_.use_count());
    EXPECT_EQ(2, lru.size());

    // Same for entry 3.
    EXPECT_EQ(1, entry3_.use_count());
    lru.add(entry3_);
    EXPECT_EQ(2, entry3_.use_count());
    EXPECT_EQ(3, lru.size());

    // Adding entry 4 should remove entry 1 from the list.  This will
    // delete the list's shared pointer to the entry and will therefore
    // drop the reference count back to one (from the "entry1_" member in
    // the text fixture class).
    EXPECT_EQ(2, entry1_.use_count());
    EXPECT_EQ(1, entry4_.use_count());
    lru.add(entry4_);
    EXPECT_EQ(1, entry1_.use_count());
    EXPECT_EQ(2, entry4_.use_count());
    EXPECT_EQ(3, lru.size());

    // Adding entry 5 should remove entry 2 from the list.
    EXPECT_EQ(2, entry2_.use_count());
    EXPECT_EQ(1, entry5_.use_count());
    lru.add(entry5_);
    EXPECT_EQ(1, entry2_.use_count());
    EXPECT_EQ(2, entry5_.use_count());
    EXPECT_EQ(3, lru.size());
}

// Check that "touching" an entry adds it to the back of the list.
TEST_F(LruListTest, Touch) {

    // Create the list
    LruList<TestEntry>  lru(3);
    EXPECT_EQ(0, lru.size());
    lru.add(entry1_);
    lru.add(entry2_);
    lru.add(entry3_);

    // Check the reference counts of the entrys and the list size
    EXPECT_EQ(2, entry1_.use_count());
    EXPECT_EQ(2, entry2_.use_count());
    EXPECT_EQ(2, entry3_.use_count());
    EXPECT_EQ(1, entry4_.use_count());
    EXPECT_EQ(1, entry5_.use_count());
    EXPECT_EQ(1, entry6_.use_count());
    EXPECT_EQ(1, entry7_.use_count());
    EXPECT_EQ(3, lru.size());

    // "Touch" the first entry
    lru.touch(entry1_);

    // Adding two more entries should not remove the touched entry.
    lru.add(entry4_);
    lru.add(entry5_);

    // Check the status of the entrys and the list.
    EXPECT_EQ(2, entry1_.use_count());
    EXPECT_EQ(1, entry2_.use_count());
    EXPECT_EQ(1, entry3_.use_count());
    EXPECT_EQ(2, entry4_.use_count());
    EXPECT_EQ(2, entry5_.use_count());
    EXPECT_EQ(1, entry6_.use_count());
    EXPECT_EQ(1, entry7_.use_count());
    EXPECT_EQ(3, lru.size());

    // Now touch the entry agin to move it to the back of the list.
    // This checks that the iterator stored in the entry as a result of the
    // last touch operation is valid.
    lru.touch(entry1_);

    // Check this by adding two more entrys and checking reference counts
    // to see what is stored.
    lru.add(entry6_);
    lru.add(entry7_);

    EXPECT_EQ(2, entry1_.use_count());
    EXPECT_EQ(1, entry2_.use_count());
    EXPECT_EQ(1, entry3_.use_count());
    EXPECT_EQ(1, entry4_.use_count());
    EXPECT_EQ(1, entry5_.use_count());
    EXPECT_EQ(2, entry6_.use_count());
    EXPECT_EQ(2, entry7_.use_count());
    EXPECT_EQ(3, lru.size());
}

// Dropped functor tests: tests that the function object is called when an
// object expires from the list.
TEST_F(LruListTest, Dropped) {

    // Create an object with an expiration handler.
    LruList<TestEntry> lru(3, new Dropped());

    // Fill the list
    lru.add(entry1_);
    lru.add(entry2_);
    lru.add(entry3_);

    EXPECT_EQ(1, entry1_->getClass());
    EXPECT_EQ(2, entry2_->getClass());

    // Add another entry and check that the handler runs.
    EXPECT_EQ(0, (entry1_->getClass() & 0x8000));
    lru.add(entry4_);
    EXPECT_NE(0, (entry1_->getClass() & 0x8000));

    EXPECT_EQ(0, (entry2_->getClass() & 0x8000));
    lru.add(entry5_);
    EXPECT_NE(0, (entry2_->getClass() & 0x8000));

    // Delete an entry and check that the handler does not run. 
    EXPECT_EQ(0, (entry3_->getClass() & 0x8000));
    lru.remove(entry3_);
    EXPECT_EQ(0, (entry3_->getClass() & 0x8000));
}

// Miscellaneous tests - pathological conditions
TEST_F(LruListTest, Miscellaneous) {

    // Zero size list should not allow entrys to be added
    LruList<TestEntry> lru_1(0);
    lru_1.add(entry1_);
    EXPECT_EQ(0, lru_1.size());
    EXPECT_EQ(1, entry1_.use_count());

    // Removing an uninserted entry should not affect the list.
    LruList<TestEntry> lru_2(100);
    lru_2.add(entry1_);
    lru_2.add(entry2_);
    lru_2.add(entry3_);
    EXPECT_EQ(3, lru_2.size());

    lru_2.remove(entry4_);
    EXPECT_EQ(2, entry1_.use_count());
    EXPECT_EQ(2, entry2_.use_count());
    EXPECT_EQ(2, entry3_.use_count());
    EXPECT_EQ(1, entry4_.use_count());
    EXPECT_EQ(1, entry5_.use_count());
    EXPECT_EQ(3, lru_2.size());

    // Touching an uninserted entry should not affect the list.
    lru_2.touch(entry5_);
    EXPECT_EQ(2, entry1_.use_count());
    EXPECT_EQ(2, entry2_.use_count());
    EXPECT_EQ(2, entry3_.use_count());
    EXPECT_EQ(1, entry4_.use_count());
    EXPECT_EQ(1, entry5_.use_count());
    EXPECT_EQ(3, lru_2.size());
}

}   // namespace nsas
}   // namespace isc
