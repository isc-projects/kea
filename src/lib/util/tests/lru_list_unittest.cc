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

#include <config.h>

#include <stdint.h>
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

#include <exceptions/exceptions.h>
#include <gtest/gtest.h>
#include <boost/lexical_cast.hpp>
#include <boost/enable_shared_from_this.hpp>

#include <util/lru_list.h>

using namespace std;

namespace isc {
namespace util {

/// \brief Invalid Iterator
///
/// Thrown if an attempt was made to access the iterator - the pointer into
/// the LRU list where this element is located - when it is marked as invalid.
class InvalidLruIterator : public isc::Exception {
public:
    InvalidLruIterator(const char* file, size_t line, const char* what) :
        Exception(file, line, what)
    {}
};

template <typename T>
class TestEntryT : public boost::enable_shared_from_this <T> {
public:

    /// \brief Constructor
    ///
    /// \param name Name that will be used for the object.  This will form
    /// part of the key.
    /// \param class_code Class associated with the object.
    TestEntryT() : valid_(false)
    {}

    /// \brief Virtual Destructor
    virtual ~TestEntryT()
        {}

    /// \brief Sets the iterator of the object
    ///
    /// Sets the iterator of an object and, as a side effect, marks it as valid.
    ///
    /// \param iterator Iterator of this element in the list
    virtual void setLruIterator(typename LruList<T>::iterator iterator) {
        iterator_ = iterator;
        valid_ = true;
    }

    /// \brief Return Iterator
    ///
    /// \return iterator Iterator of this element in the list.
    ///
    /// \exception InvalidLruIterator Thrown if the iterator is not valid.
    virtual typename LruList<T>::iterator getLruIterator() const {
        /*if (! valid_) {
            isc_throw(InvalidLruIterator,
                "pointer of element into LRU list was not valid");
        }*/
        return iterator_;
    }

    /// \brief Iterator Valid
    ///
    /// \return true if the stored iterator is valid.
    virtual bool iteratorValid() const {
        return valid_;
    }

    /// \brief Invalidate Iterator
    ///
    /// Marks the iterator as invalid; it can only be set valid again by a call
    /// to setLruIterator.
    virtual void invalidateIterator() {
        valid_ = false;
    }

private:
    typename LruList<T>::iterator  iterator_;  ///< Handle into the LRU List
    bool                           valid_;     ///< true if handle is valid
};

class TestEntry : public TestEntryT<TestEntry> {
public:
    TestEntry(std::string name, const int & code) :
        name_(name), code_(code)
    {}

    /// \brief Get the Name
    ///
    /// \return Name given to this object
    virtual std::string getName() const {
        return name_;
    }

    /// \brief Set the Name
    ///
    /// \param name New name of the object
    virtual void setName(const std::string& name) {
        name_ = name;
    }

    /// \brief Get the Class
    ///
    /// \return Class code assigned to this object
    virtual const int& getCode() const {
        return code_;
    }

    /// \brief Set the Class
    ///
    /// \param code New code of the object
    virtual void setCode(const int& code) {
        code_ = code;
    }

private:
    std::string name_;          ///< Name of the object
    int code_;    ///< Class of the object

};

/// \brief Dropped Functor Class
///
/// Functor object is called when an object is dropped from the LRU list.
/// To prove that it has run, this function does nothing more than set the
/// MS bit on the 16-bit code value.
class Dropped : public LruList<TestEntry>::Dropped {
public:
    virtual void operator()(TestEntry* entry) const {
        entry->setCode(entry->getCode() | 0x8000);
    }
};


/// \brief Text Fixture Class
class LruListTest : public ::testing::Test {
protected:
    LruListTest() :
        entry1_(new TestEntry("alpha", 1)),
        entry2_(new TestEntry("beta", 3)),
        entry3_(new TestEntry("gamma", 4)),
        entry4_(new TestEntry("delta", 1)),
        entry5_(new TestEntry("epsilon", 4)),
        entry6_(new TestEntry("zeta", 3)),
        entry7_(new TestEntry("eta", 1))
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

// Test of Get/Set the maximum number of entries
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

    // Check the reference counts of the entries and the list size
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

    // Check the status of the entries and the list.
    EXPECT_EQ(2, entry1_.use_count());
    EXPECT_EQ(1, entry2_.use_count());
    EXPECT_EQ(1, entry3_.use_count());
    EXPECT_EQ(2, entry4_.use_count());
    EXPECT_EQ(2, entry5_.use_count());
    EXPECT_EQ(1, entry6_.use_count());
    EXPECT_EQ(1, entry7_.use_count());
    EXPECT_EQ(3, lru.size());

    // Now touch the entry again to move it to the back of the list.
    // This checks that the iterator stored in the entry as a result of the
    // last touch operation is valid.
    lru.touch(entry1_);

    // Check this by adding two more entries and checking reference counts
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

    EXPECT_EQ(1, entry1_->getCode());
    EXPECT_EQ(3, entry2_->getCode());

    // Add another entry and check that the handler runs.
    EXPECT_EQ(0, (entry1_->getCode() & 0x8000));
    lru.add(entry4_);
    EXPECT_NE(0, (entry1_->getCode() & 0x8000));

    EXPECT_EQ(0, (entry2_->getCode() & 0x8000));
    lru.add(entry5_);
    EXPECT_NE(0, (entry2_->getCode() & 0x8000));

    // Delete an entry and check that the handler does not run.
    EXPECT_EQ(0, (entry3_->getCode() & 0x8000));
    lru.remove(entry3_);
    EXPECT_EQ(0, (entry3_->getCode() & 0x8000));
}

// Clear functor tests: tests whether all the elements in
// the list are dropped properly and the size of list is
// set to 0.
TEST_F(LruListTest, Clear) {
    // Create an object with an expiration handler.
    LruList<TestEntry> lru(3, new Dropped());

    // Fill the list
    lru.add(entry1_);
    lru.add(entry2_);
    lru.add(entry3_);

    EXPECT_EQ(1, entry1_->getCode());
    EXPECT_EQ(3, entry2_->getCode());
    EXPECT_EQ(4, entry3_->getCode());

    EXPECT_EQ(0, (entry1_->getCode() & 0x8000));
    EXPECT_EQ(0, (entry2_->getCode() & 0x8000));
    EXPECT_EQ(0, (entry3_->getCode() & 0x8000));

    // Clear the lru list, and check the drop handler run
    lru.clear();
    EXPECT_NE(0, (entry1_->getCode() & 0x8000));
    EXPECT_NE(0, (entry2_->getCode() & 0x8000));
    EXPECT_NE(0, (entry3_->getCode() & 0x8000));

    EXPECT_EQ(0, lru.size());
}

// Miscellaneous tests - pathological conditions
TEST_F(LruListTest, Miscellaneous) {

    // Zero size list should not allow entries to be added
    LruList<TestEntry> lru_1(0);
    lru_1.add(entry1_);
    EXPECT_EQ(0, lru_1.size());
    EXPECT_EQ(1, entry1_.use_count());

    // Removing a not-inserted entry should not affect the list.
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

    // Touching a not-inserted entry should not affect the list.
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
