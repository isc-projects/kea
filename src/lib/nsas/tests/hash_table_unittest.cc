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

#include <gtest/gtest.h>
#include <boost/shared_ptr.hpp>
#include <boost/bind.hpp>

#include <string.h>
#include <iostream>

#include "hash_table.h"
#include "hash_key.h"

#include "nsas_entry_compare.h"
#include "nsas_test.h"

using namespace std;
using boost::shared_ptr;

namespace isc {
namespace nsas {

/// \brief Text Fixture Class
///
/// Many of the tests are based on checking reference counts.  In all tests,
/// objects named dummyN_ have a reference count of 1 because they are a member
/// of this class which has been instantiated for the test.  The reference count
/// is increased as they are added to the hash table for testing and decreased
/// as they are removed.
class HashTableTest : public ::testing::Test {
protected:

    // Constructor - initialize the objects
    HashTableTest() :
        table_(new NsasEntryCompare<TestEntry>()),
        dummy1_(new TestEntry("test", 1)),
        dummy2_(new TestEntry("test", 1)),
        dummy3_(new TestEntry("Something_Else", 1)),
        dummy4_(new TestEntry("test", 3))
    {}

    // Members.
    HashTable<TestEntry> table_;
    boost::shared_ptr<TestEntry> dummy1_;
    boost::shared_ptr<TestEntry> dummy2_;
    boost::shared_ptr<TestEntry> dummy3_;
    boost::shared_ptr<TestEntry> dummy4_;
};


// Test of the constructor
TEST_F(HashTableTest, Constructor) {
    
    // Default constructor
    HashTable<TestEntry> table1(new NsasEntryCompare<TestEntry>());
    EXPECT_EQ(HASHTABLE_DEFAULT_SIZE, table1.tableSize());

    // Non default constructor
    EXPECT_NE(42, HASHTABLE_DEFAULT_SIZE);
    HashTable<TestEntry> table2(new NsasEntryCompare<TestEntry>(), 42);
    EXPECT_EQ(42, table2.tableSize());
}


// Basic test of addition
TEST_F(HashTableTest, AddTest) {

    // Using two objects with the same name and class,
    EXPECT_EQ(dummy1_->getName(), dummy2_->getName());
    EXPECT_EQ(dummy1_->getClass(), dummy2_->getClass());
    EXPECT_EQ(1, dummy1_.use_count());
    EXPECT_EQ(1, dummy2_.use_count());

    // Add first one to the hash table_
    bool result = table_.add(dummy1_, dummy1_->hashKey());
    EXPECT_TRUE(result);
    EXPECT_EQ(2, dummy1_.use_count());
    EXPECT_EQ(1, dummy2_.use_count());

    // Attempt to add the second object with the same name and class fails.
    result = table_.add(dummy2_, dummy2_->hashKey());
    EXPECT_FALSE(result);
    EXPECT_EQ(2, dummy1_.use_count());
    EXPECT_EQ(1, dummy2_.use_count());

    // Replacing an entry should work though
    result = table_.add(dummy2_, dummy2_->hashKey(), true);
    EXPECT_TRUE(result);
    EXPECT_EQ(1, dummy1_.use_count());
    EXPECT_EQ(2, dummy2_.use_count());
}

// Test the remove functionality
TEST_F(HashTableTest, RemoveTest) {

    // Using two objects with different names but the same class
    EXPECT_NE(dummy1_->getName(), dummy3_->getName());
    EXPECT_EQ(dummy1_->getClass(), dummy3_->getClass());
    EXPECT_EQ(1, dummy1_.use_count());
    EXPECT_EQ(1, dummy3_.use_count());

    // Add first one to the hash table_
    bool result = table_.add(dummy1_, dummy1_->hashKey());
    EXPECT_TRUE(result);
    EXPECT_EQ(2, dummy1_.use_count());
    EXPECT_EQ(1, dummy3_.use_count());

    // Now remove it.
    result = table_.remove(dummy1_->hashKey());
    EXPECT_TRUE(result);
    EXPECT_EQ(1, dummy1_.use_count());
    EXPECT_EQ(1, dummy3_.use_count());

    // Attempt to remove it again.
    result = table_.remove(dummy1_->hashKey());
    EXPECT_FALSE(result);
    EXPECT_EQ(1, dummy1_.use_count());
    EXPECT_EQ(1, dummy3_.use_count());

    // Add both entries to table_, then remove one (checks that it will
    // remove the correct one).
    result = table_.add(dummy1_, dummy1_->hashKey());
    EXPECT_TRUE(result);
    result = table_.add(dummy3_, dummy3_->hashKey());
    EXPECT_TRUE(result);
    EXPECT_EQ(2, dummy1_.use_count());
    EXPECT_EQ(2, dummy3_.use_count());

    result = table_.remove(dummy1_->hashKey());
    EXPECT_TRUE(result);
    EXPECT_EQ(1, dummy1_.use_count());
    EXPECT_EQ(2, dummy3_.use_count());
}            

// Test the "get" functionality
TEST_F(HashTableTest, GetTest) {

    // Using two objects with different names but the same class
    EXPECT_NE(dummy1_->getName(), dummy3_->getName());
    EXPECT_EQ(dummy1_->getClass(), dummy3_->getClass());
    EXPECT_EQ(1, dummy1_.use_count());
    EXPECT_EQ(1, dummy3_.use_count());

    // Add both to the hash table
    bool result = table_.add(dummy1_, dummy1_->hashKey());
    EXPECT_TRUE(result);
    result = table_.add(dummy3_, dummy3_->hashKey());
    EXPECT_TRUE(result);

    // Lookup the first
    boost::shared_ptr<TestEntry> value = table_.get(dummy1_->hashKey());
    EXPECT_EQ(value.get(), dummy1_.get());

    // ... and the second
    value = table_.get(dummy3_->hashKey());
    EXPECT_EQ(value.get(), dummy3_.get());

    // Remove the first
    result = table_.remove(dummy1_->hashKey());
    EXPECT_TRUE(result);

    // ... and a lookup should return empty
    value = table_.get(dummy1_->hashKey());
    EXPECT_TRUE(value.get() == NULL);
}

shared_ptr<TestEntry>
pass(shared_ptr<TestEntry> value) {
    return (value);
}

TEST_F(HashTableTest, GetOrAddTest) {
    // Add one entry
    EXPECT_TRUE(table_.add(dummy1_, dummy1_->hashKey()));

    // Check it looks it up
    std::pair<bool, shared_ptr<TestEntry> > result = table_.getOrAdd(
        dummy1_->hashKey(), boost::bind(pass, dummy3_));
    EXPECT_TRUE(result.first);
    EXPECT_EQ(dummy1_.get(), result.second.get());

    // Check it says it adds the value
    result = table_.getOrAdd(dummy3_->hashKey(), boost::bind(pass, dummy3_));
    EXPECT_FALSE(result.first);
    EXPECT_EQ(dummy3_.get(), result.second.get());

    // Check it really did add it
    EXPECT_EQ(dummy3_.get(), table_.get(dummy3_->hashKey()).get());
}

// Test that objects with the same name and different classes are distinct.
TEST_F(HashTableTest, ClassTest) {

    // Using two objects with the same name and different classes
    EXPECT_EQ(dummy1_->getName(), dummy4_->getName());
    EXPECT_NE(dummy1_->getClass(), dummy4_->getClass());
    EXPECT_EQ(1, dummy1_.use_count());
    EXPECT_EQ(1, dummy4_.use_count());

    // Add both to the hash table
    bool result = table_.add(dummy1_, dummy1_->hashKey());
    EXPECT_TRUE(result);
    EXPECT_EQ(2, dummy1_.use_count());

    result = table_.add(dummy4_, dummy4_->hashKey());
    EXPECT_TRUE(result);
    EXPECT_EQ(2, dummy4_.use_count());

    // Lookup the first
    boost::shared_ptr<TestEntry> value1 = table_.get(dummy1_->hashKey());
    EXPECT_EQ(value1.get(), dummy1_.get());
    EXPECT_EQ(3, dummy1_.use_count());
    EXPECT_EQ(2, dummy4_.use_count());

    // ... and the second
    boost::shared_ptr<TestEntry> value4 = table_.get(dummy4_->hashKey());
    EXPECT_EQ(value4.get(), dummy4_.get());
    EXPECT_EQ(3, dummy1_.use_count());
    EXPECT_EQ(3, dummy4_.use_count());

    // ... and check they are different
    EXPECT_NE(dummy1_.get(), dummy4_.get());

    // Remove the first
    result = table_.remove(dummy1_->hashKey());
    EXPECT_TRUE(result);
    EXPECT_EQ(2, dummy1_.use_count());
    EXPECT_EQ(3, dummy4_.use_count());

    // ... and a lookup should return empty
    boost::shared_ptr<TestEntry> value1a = table_.get(dummy1_->hashKey());
    EXPECT_TRUE(value1a.get() == NULL);
}





} // namespace nsas
} // namespace isc
