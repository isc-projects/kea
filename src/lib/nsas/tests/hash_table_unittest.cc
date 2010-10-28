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

#include <string.h>
#include <iostream>

#include "hash_table.h"
#include "hash_key.h"


namespace isc {
namespace nsas {


/// \brief Dummy Class for Use in Testing
///
/// A class that has a name and a value.  The name is used as a key in the
/// hash table, and the integer value used to check for the add/replace option.
class DummyObject {
public:

    /// Constructor
    ///
    /// \param name Name of the object
    /// \param class_code Class of the object
    /// \param value Integer value
    DummyObject(const char* name, uint16_t class_code, int value) :
        name_(name), classCode_(class_code), value_(value)
    {}

    /// \return Name of the object
    string getName() const {
        return name_;
    }

    /// \return Value of the Object
    int getValue() const {
        return value_;
    }

    /// \return Class of the object
    uint16_t getClass() const {
        return classCode_;
    }

    /// \return Hash Key of the Object
    HashKey getKey() {
        return HashKey(name_.c_str(), name_.size(), classCode_);
    }

private:
    string      name_;      ///< Object name
    uint16_t    classCode_; ///< Object class
    int         value_;     ///< Object value
};

/// \brief Comparison Class
///
/// Class to encapsulate the comparison of a DummyObject with a key and
/// key length.
class DummyObjectCompare : public HashTableCompare<DummyObject> {
public:

    /// \brief Comparison Operator
    ///
    /// Used to compare the object with a key name/length.
    ///
    /// \param object Pointer to the object being tested
    /// \param key Key string
    /// \param keylen Length of the key string
    bool operator()(DummyObject* object, const HashKey& key) {
        // Do a quick check on size first
        if (key.keylen == object->getName().size()) {

            // Size matches, does the class?
            if (key.class_code == object->getClass()) {

                // So does the memory?
                return (memcmp(object->getName().c_str(), key.key,
                    key.keylen) == 0);
            }
        }

        // Size or class do not match.
        return (false);
    }
};



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
        table_(new DummyObjectCompare()),
        dummy1_(new DummyObject("test", 1, 42)),
        dummy2_(new DummyObject("test", 1, 47)),
        dummy3_(new DummyObject("Something_Else", 1, 1332)),
        dummy4_(new DummyObject("test", 3, 42))
    {}

    // Members.
    HashTable<DummyObject> table_;
    boost::shared_ptr<DummyObject> dummy1_;
    boost::shared_ptr<DummyObject> dummy2_;
    boost::shared_ptr<DummyObject> dummy3_;
    boost::shared_ptr<DummyObject> dummy4_;
};


// Test of the constructor
TEST_F(HashTableTest, Constructor) {
    
    // Default constructor
    HashTable<DummyObject> table1(new DummyObjectCompare());
    EXPECT_EQ(1009, table1.tableSize());

    // Non default constructor
    HashTable<DummyObject> table2(new DummyObjectCompare(), 97);
    EXPECT_EQ(97, table2.tableSize());
}


// Basic test of addition
TEST_F(HashTableTest, AddTest) {

    // Using two objects with the same name and class,
    EXPECT_EQ(dummy1_->getName(), dummy2_->getName());
    EXPECT_EQ(dummy1_->getClass(), dummy2_->getClass());
    EXPECT_EQ(1, dummy1_.use_count());
    EXPECT_EQ(1, dummy2_.use_count());

    // Add first one to the hash table_
    bool result = table_.add(dummy1_, dummy1_->getKey());
    EXPECT_TRUE(result);
    EXPECT_EQ(2, dummy1_.use_count());
    EXPECT_EQ(1, dummy2_.use_count());

    // Attempt to add the second object with the same name and class fails.
    result = table_.add(dummy2_, dummy2_->getKey());
    EXPECT_FALSE(result);
    EXPECT_EQ(2, dummy1_.use_count());
    EXPECT_EQ(1, dummy2_.use_count());

    // Replacing an entry should work though
    result = table_.add(dummy2_, dummy2_->getKey(), true);
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
    bool result = table_.add(dummy1_, dummy1_->getKey());
    EXPECT_TRUE(result);
    EXPECT_EQ(2, dummy1_.use_count());
    EXPECT_EQ(1, dummy3_.use_count());

    // Now remove it.
    result = table_.remove(dummy1_->getKey());
    EXPECT_TRUE(result);
    EXPECT_EQ(1, dummy1_.use_count());
    EXPECT_EQ(1, dummy3_.use_count());

    // Attempt to remove it again.
    result = table_.remove(dummy1_->getKey());
    EXPECT_FALSE(result);
    EXPECT_EQ(1, dummy1_.use_count());
    EXPECT_EQ(1, dummy3_.use_count());

    // Add both entries to table_, then remove one (checks that it will
    // remove the correct one).
    result = table_.add(dummy1_, dummy1_->getKey());
    EXPECT_TRUE(result);
    result = table_.add(dummy3_, dummy3_->getKey());
    EXPECT_TRUE(result);
    EXPECT_EQ(2, dummy1_.use_count());
    EXPECT_EQ(2, dummy3_.use_count());

    result = table_.remove(dummy1_->getKey());
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
    bool result = table_.add(dummy1_, dummy1_->getKey());
    EXPECT_TRUE(result);
    result = table_.add(dummy3_, dummy3_->getKey());
    EXPECT_TRUE(result);

    // Lookup the first
    boost::shared_ptr<DummyObject> value = table_.get(dummy1_->getKey());
    EXPECT_EQ(value.get(), dummy1_.get());

    // ... and the second
    value = table_.get(dummy3_->getKey());
    EXPECT_EQ(value.get(), dummy3_.get());

    // Remove the first
    result = table_.remove(dummy1_->getKey());
    EXPECT_TRUE(result);

    // ... and a lookup should return empty
    value = table_.get(dummy1_->getKey());
    EXPECT_TRUE(value.get() == NULL);
}

// Test that objects with the same name and different classes are distinct.
TEST_F(HashTableTest, ClassTest) {

    // Using two objects with the same name and different classes
    EXPECT_EQ(dummy1_->getName(), dummy4_->getName());
    EXPECT_NE(dummy1_->getClass(), dummy4_->getClass());
    EXPECT_EQ(1, dummy1_.use_count());
    EXPECT_EQ(1, dummy4_.use_count());

    // Add both to the hash table
    bool result = table_.add(dummy1_, dummy1_->getKey());
    EXPECT_TRUE(result);
    EXPECT_EQ(2, dummy1_.use_count());

    result = table_.add(dummy4_, dummy4_->getKey());
    EXPECT_TRUE(result);
    EXPECT_EQ(2, dummy4_.use_count());

    // Lookup the first
    boost::shared_ptr<DummyObject> value1 = table_.get(dummy1_->getKey());
    EXPECT_EQ(value1.get(), dummy1_.get());
    EXPECT_EQ(3, dummy1_.use_count());
    EXPECT_EQ(2, dummy4_.use_count());

    // ... and the second
    boost::shared_ptr<DummyObject> value4 = table_.get(dummy4_->getKey());
    EXPECT_EQ(value4.get(), dummy4_.get());
    EXPECT_EQ(3, dummy1_.use_count());
    EXPECT_EQ(3, dummy4_.use_count());

    // ... and check they are different
    EXPECT_NE(dummy1_.get(), dummy4_.get());

    // Remove the first
    result = table_.remove(dummy1_->getKey());
    EXPECT_TRUE(result);
    EXPECT_EQ(2, dummy1_.use_count());
    EXPECT_EQ(3, dummy4_.use_count());

    // ... and a lookup should return empty
    boost::shared_ptr<DummyObject> value1a = table_.get(dummy1_->getKey());
    EXPECT_TRUE(value1a.get() == NULL);
}





} // namespace nsas
} // namespace isc
