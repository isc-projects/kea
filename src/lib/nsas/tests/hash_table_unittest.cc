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
    /// \param value Integer value
    DummyObject(const char* name, int value) : name_(name), value_(value)
    {}

    /// \return Name of the object
    string getName() const {
        return name_;
    }

    /// \return Value of the Object
    int getValue() const {
        return value_;
    }

private:
    string  name_;      ///< Object name
    int     value_;     ///< Object value
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
    bool operator()(DummyObject* object, const char* key, uint32_t keylen) {
        // Do a quick check on size first
        if (keylen != object->getName().size()) {
            return false;
        }
        return (memcmp(object->getName().c_str(), key, keylen) == 0);
    }
};



/// \brief Text Fixture Class
class HashTableTest : public ::testing::Test {
protected:

    // Constructor - initialize the objects
    HashTableTest() :
        table_(new DummyObjectCompare()),
        dummy1_(new DummyObject("test", 42)),
        dummy2_(new DummyObject("test", 47)),
        dummy3_(new DummyObject("Something_Else", 1332))
    {}

    // Members
    HashTable<DummyObject> table_;
    boost::shared_ptr<DummyObject> dummy1_;
    boost::shared_ptr<DummyObject> dummy2_;
    boost::shared_ptr<DummyObject> dummy3_;
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

    // Using two objects with the same key.
    EXPECT_EQ(1, dummy1_.use_count());
    EXPECT_EQ(1, dummy2_.use_count());

    // Add first one to the hash table_
    bool result = table_.add(dummy1_, dummy1_.get()->getName().c_str(),
        dummy1_.get()->getName().size());
    EXPECT_TRUE(result);
    EXPECT_EQ(2, dummy1_.use_count());
    EXPECT_EQ(1, dummy2_.use_count());

    // Attempt to add the second object with the same name should fail.
    result = table_.add(dummy2_, dummy2_.get()->getName().c_str(),
        dummy2_.get()->getName().size());
    EXPECT_FALSE(result);
    EXPECT_EQ(2, dummy1_.use_count());
    EXPECT_EQ(1, dummy2_.use_count());

    // Replacing an entry should work though
    result = table_.add(dummy2_, dummy2_.get()->getName().c_str(),
        dummy2_.get()->getName().size(), true);
    EXPECT_TRUE(result);
    EXPECT_EQ(1, dummy1_.use_count());
    EXPECT_EQ(2, dummy2_.use_count());
}

// Test the remove functionality
TEST_F(HashTableTest, RemoveTest) {

    // Using two objects with different keys
    EXPECT_EQ(1, dummy1_.use_count());
    EXPECT_EQ(1, dummy3_.use_count());

    // Add first one to the hash table_
    bool result = table_.add(dummy1_, dummy1_.get()->getName().c_str(),
        dummy1_.get()->getName().size());
    EXPECT_TRUE(result);
    EXPECT_EQ(2, dummy1_.use_count());
    EXPECT_EQ(1, dummy3_.use_count());

    // Now remove it.
    result = table_.remove(dummy1_.get()->getName().c_str(),
        dummy1_.get()->getName().size());
    EXPECT_TRUE(result);
    EXPECT_EQ(1, dummy1_.use_count());
    EXPECT_EQ(1, dummy3_.use_count());

    // Attempt to remove it again.
    result = table_.remove(dummy1_.get()->getName().c_str(),
        dummy1_.get()->getName().size());
    EXPECT_FALSE(result);
    EXPECT_EQ(1, dummy1_.use_count());
    EXPECT_EQ(1, dummy3_.use_count());

    // Add both entries to the table_, then remove one (checks that it will
    // remove the correct one).
    result = table_.add(dummy1_, dummy1_.get()->getName().c_str(),
        dummy1_.get()->getName().size());
    EXPECT_TRUE(result);
    result = table_.add(dummy3_, dummy3_.get()->getName().c_str(),
        dummy3_.get()->getName().size());
    EXPECT_TRUE(result);
    EXPECT_EQ(2, dummy1_.use_count());
    EXPECT_EQ(2, dummy3_.use_count());

    result = table_.remove(dummy1_.get()->getName().c_str(),
        dummy1_.get()->getName().size());
    EXPECT_TRUE(result);
    EXPECT_EQ(1, dummy1_.use_count());
    EXPECT_EQ(2, dummy3_.use_count());
}            

// Test the "get" functionality
TEST_F(HashTableTest, GetTest) {

    // Using two objects with different keys
    EXPECT_EQ(1, dummy1_.use_count());
    EXPECT_EQ(1, dummy3_.use_count());

    // Add both to the hash table
    bool result = table_.add(dummy1_, dummy1_.get()->getName().c_str(),
        dummy1_.get()->getName().size());
    EXPECT_TRUE(result);
    result = table_.add(dummy3_, dummy3_.get()->getName().c_str(),
        dummy3_.get()->getName().size());
    EXPECT_TRUE(result);

    // Lookup the first
    boost::shared_ptr<DummyObject> value =
        table_.get(dummy1_.get()->getName().c_str(), 
        dummy1_.get()->getName().size());
    EXPECT_EQ(value.get(), dummy1_.get());

    // ... and the second
    value = table_.get(dummy3_.get()->getName().c_str(), 
        dummy3_.get()->getName().size());
    EXPECT_EQ(value.get(), dummy3_.get());

    // Remove the first
    result = table_.remove(dummy1_.get()->getName().c_str(),
        dummy1_.get()->getName().size());
    EXPECT_TRUE(result);

    // ... and a lookup should return empty
    value = table_.get(dummy1_.get()->getName().c_str(), 
        dummy1_.get()->getName().size());
    EXPECT_TRUE(value.get() == NULL);

}





} // namespace nsas
} // namespace isc
