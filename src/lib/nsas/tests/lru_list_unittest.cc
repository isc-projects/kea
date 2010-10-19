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

#include "lru_list.h"

using namespace std;

namespace isc {
namespace nsas {

/// \brief Element Class
///
/// This is an object that will be stored in the list.
struct DataStore : public LruList<DataStore>::Element {
    int         value_;
    std::string text_;

    /// \brief Constructor
    DataStore(uint32_t value = 0, string text = "") : value_(value), text_(text)
    {}
};

/// \brief Expired Functor Class
///
/// Functor object is called when an object in the list becomes expired.
/// To prove that it has run, this function does nothing more than negate the
/// the value of the data store.
class Expired : public LruList<DataStore>::Expired {
public:
    virtual void operator()(boost::shared_ptr<DataStore>& element) {
        element.get()->value_ = -element.get()->value_;
    }
};


/// \brief Text Fixture Class
class LruListTest : public ::testing::Test {
protected:
    LruListTest() :
        element1_(new DataStore(1, "alpha")),
        element2_(new DataStore(2, "beta")),
        element3_(new DataStore(3, "gamma")),
        element4_(new DataStore(4, "delta")),
        element5_(new DataStore(5, "epsilon")),
        element6_(new DataStore(6, "zeta")),
        element7_(new DataStore(7, "eta"))
    {}


    boost::shared_ptr<DataStore>    element1_;
    boost::shared_ptr<DataStore>    element2_;
    boost::shared_ptr<DataStore>    element3_;
    boost::shared_ptr<DataStore>    element4_;
    boost::shared_ptr<DataStore>    element5_;
    boost::shared_ptr<DataStore>    element6_;
    boost::shared_ptr<DataStore>    element7_;
};


// Test of the constructor
TEST_F(LruListTest, Constructor) {
    LruList<DataStore>  lru(100);
    EXPECT_EQ(100, lru.getMaxSize());
    EXPECT_EQ(0, lru.size());
}

// Test of Get/Set the maximum number of elements
TEST_F(LruListTest, GetSet) {
    LruList<DataStore>  lru(100);
    EXPECT_EQ(100, lru.getMaxSize());

    lru.setMaxSize(42);
    EXPECT_EQ(42, lru.getMaxSize());
}

// Test that adding an element really does add an element
TEST_F(LruListTest, Add) {
    LruList<DataStore>  lru(100);
    EXPECT_EQ(0, lru.size());

    lru.add(element1_);
    EXPECT_EQ(1, lru.size());

    lru.add(element2_);
    EXPECT_EQ(2, lru.size());
}

// Test that removing an element really does remove it.
TEST_F(LruListTest, Remove) {
    LruList<DataStore>  lru(100);
    EXPECT_EQ(0, lru.size());

    lru.add(element1_);
    EXPECT_EQ(1, lru.size());

    lru.add(element2_);
    EXPECT_EQ(2, lru.size());

    lru.remove(element1_);
    EXPECT_EQ(1, lru.size());
}

// Check that adding a new element to a limited size list does delete the
// oldest element from the list.
TEST_F(LruListTest, SizeLimit) {
    LruList<DataStore>  lru(3);
    EXPECT_EQ(0, lru.size());

    // Add first element and check that the shared pointer's reference count
    // has increased.  There will be two references: one from the "element1_"
    // member in the test fixture class, and one from the list.
    EXPECT_EQ(1, element1_.use_count());
    lru.add(element1_);
    EXPECT_EQ(2, element1_.use_count());
    EXPECT_EQ(1, lru.size());

    // Same for element 2.
    EXPECT_EQ(1, element2_.use_count());
    lru.add(element2_);
    EXPECT_EQ(2, element2_.use_count());
    EXPECT_EQ(2, lru.size());

    // Same for element 3.
    EXPECT_EQ(1, element3_.use_count());
    lru.add(element3_);
    EXPECT_EQ(2, element3_.use_count());
    EXPECT_EQ(3, lru.size());

    // Adding element 4 should remove element 1 from the list.  This will
    // delete the list's shared pointer to the element and will therefore
    // drop the reference count back to one (from the "element1_" member in
    // the text fixture class).
    EXPECT_EQ(2, element1_.use_count());
    EXPECT_EQ(1, element4_.use_count());
    lru.add(element4_);
    EXPECT_EQ(1, element1_.use_count());
    EXPECT_EQ(2, element4_.use_count());
    EXPECT_EQ(3, lru.size());

    // Adding element 5 should remove element 2 from the list.
    EXPECT_EQ(2, element2_.use_count());
    EXPECT_EQ(1, element5_.use_count());
    lru.add(element5_);
    EXPECT_EQ(1, element2_.use_count());
    EXPECT_EQ(2, element5_.use_count());
    EXPECT_EQ(3, lru.size());
}

// Check that "touching" an entry adds it to the back of the list.
TEST_F(LruListTest, Touch) {

    // Create the list
    LruList<DataStore>  lru(3);
    EXPECT_EQ(0, lru.size());
    lru.add(element1_);
    lru.add(element2_);
    lru.add(element3_);

    // Check the reference counts of the elements and the list size
    EXPECT_EQ(2, element1_.use_count());
    EXPECT_EQ(2, element2_.use_count());
    EXPECT_EQ(2, element3_.use_count());
    EXPECT_EQ(1, element4_.use_count());
    EXPECT_EQ(1, element5_.use_count());
    EXPECT_EQ(1, element6_.use_count());
    EXPECT_EQ(1, element7_.use_count());
    EXPECT_EQ(3, lru.size());

    // "Touch" the first element
    lru.touch(element1_);

    // Adding two more entries should not remove the touched element.
    lru.add(element4_);
    lru.add(element5_);

    // Check the status of the elements and the list.
    EXPECT_EQ(2, element1_.use_count());
    EXPECT_EQ(1, element2_.use_count());
    EXPECT_EQ(1, element3_.use_count());
    EXPECT_EQ(2, element4_.use_count());
    EXPECT_EQ(2, element5_.use_count());
    EXPECT_EQ(1, element6_.use_count());
    EXPECT_EQ(1, element7_.use_count());
    EXPECT_EQ(3, lru.size());

    // Now touch the element agin to move it to the back of the list.
    // This checks that the iterator stored in the element as a result of the
    // last touch operation is valid.
    lru.touch(element1_);

    // Check this by adding two more elements and checking reference counts
    // to see what is stored.
    lru.add(element6_);
    lru.add(element7_);

    EXPECT_EQ(2, element1_.use_count());
    EXPECT_EQ(1, element2_.use_count());
    EXPECT_EQ(1, element3_.use_count());
    EXPECT_EQ(1, element4_.use_count());
    EXPECT_EQ(1, element5_.use_count());
    EXPECT_EQ(2, element6_.use_count());
    EXPECT_EQ(2, element7_.use_count());
    EXPECT_EQ(3, lru.size());
}

// Expired functor tests: tests that the function object is called when an
// object expires from the list.
TEST_F(LruListTest, Expired) {

    // Create an object with an expiration handler.
    LruList<DataStore> lru(3, new Expired());

    // Fill the list
    lru.add(element1_);
    lru.add(element2_);
    lru.add(element3_);

    EXPECT_EQ(1, element1_.get()->value_);
    EXPECT_EQ(2, element2_.get()->value_);

    // Add another element and check that the handler runs.
    lru.add(element4_);
    EXPECT_EQ(-1, element1_.get()->value_);

    lru.add(element5_);
    EXPECT_EQ(-2, element2_.get()->value_);

    // Delete an element and check that the handler does not run. 
    EXPECT_EQ(3, element3_.get()->value_);
    lru.remove(element3_);
    EXPECT_EQ(3, element3_.get()->value_);
}

// Miscellaneous tests - pathological conditions
TEST_F(LruListTest, Miscellaneous) {

    // Zero size list should not allow elements to be added
    LruList<DataStore> lru_1(0);
    lru_1.add(element1_);
    EXPECT_EQ(0, lru_1.size());
    EXPECT_EQ(1, element1_.use_count());

    // Removing an uninserted element should not affect the list.
    LruList<DataStore> lru_2(100);
    lru_2.add(element1_);
    lru_2.add(element2_);
    lru_2.add(element3_);
    EXPECT_EQ(3, lru_2.size());

    lru_2.remove(element4_);
    EXPECT_EQ(2, element1_.use_count());
    EXPECT_EQ(2, element2_.use_count());
    EXPECT_EQ(2, element3_.use_count());
    EXPECT_EQ(1, element4_.use_count());
    EXPECT_EQ(1, element5_.use_count());
    EXPECT_EQ(3, lru_2.size());

    // Touching an uninserted element should not affect the list.
    lru_2.touch(element5_);
    EXPECT_EQ(2, element1_.use_count());
    EXPECT_EQ(2, element2_.use_count());
    EXPECT_EQ(2, element3_.use_count());
    EXPECT_EQ(1, element4_.use_count());
    EXPECT_EQ(1, element5_.use_count());
    EXPECT_EQ(3, lru_2.size());
}

}   // namespace nsas
}   // namespace isc
