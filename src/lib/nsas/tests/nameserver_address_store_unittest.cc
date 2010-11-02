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

/// \brief Test Deleter Objects
///
/// This file contains tests for the "deleter" classes within the nameserver
/// address store.  These act to delete zones from the zone hash table when
/// the element reaches the top of the LRU list.

#include <gtest/gtest.h>
#include <boost/shared_ptr.hpp>
#include <boost/lexical_cast.hpp>

#include <string.h>
#include <vector>

#include "nameserver_address_store.h"
#include "nsas_entry_compare.h"
#include "nameserver_entry.h"
#include "zone_entry.h"
#include "nsas_test.h"

namespace isc {
namespace nsas {


/// \brief NSAS Store
///
/// This is a subclass of the NameserverAddressStore class, with methods to
/// access the internal members to check that the deleter objects are working.
class DerivedNsas : public NameserverAddressStore {
public:
    /// \brief Constructor
    ///
    /// \param hashsize Size of the zone hash table
    /// \param lrusize Size of the zone hash table
    DerivedNsas(uint32_t hashsize, uint32_t lrusize) :
        NameserverAddressStore(hashsize, lrusize)
    {}

    /// \brief Virtual Destructor
    virtual ~DerivedNsas()
    {}

    /// \brief Add Nameserver Entry to Hash and LRU Tables
    void AddNameserverEntry(boost::shared_ptr<NameserverEntry>& entry) {
        HashKey h = entry->hashKey();
        nameserver_hash_.add(entry, h);
        nameserver_lru_.add(entry);
    }

    /// \brief Add Zone Entry to Hash and LRU Tables
    void AddZoneEntry(boost::shared_ptr<ZoneEntry>& entry) {
        HashKey h = entry->hashKey();
        zone_hash_.add(entry, h);
        zone_lru_.add(entry);
    }
};



/// \brief Text Fixture Class
class NameserverAddressStoreTest : public ::testing::Test {
protected:

    // Constructor - initialize a set of nameserver and zone objects.  For convenience,
    // these are stored in vectors.
    NameserverAddressStoreTest()
    {
        for (int i = 1; i <= 9; ++i) {
            std::string name = "nameserver" + boost::lexical_cast<std::string>(i);
            nameservers_.push_back(boost::shared_ptr<NameserverEntry>(new NameserverEntry(name, (40 + i))));
        }

        for (int i = 1; i <= 9; ++i) {
            std::string name = "zone" + boost::lexical_cast<std::string>(i);
            zones_.push_back(boost::shared_ptr<ZoneEntry>(new ZoneEntry(name, (40 + i))));
        }
    }

    // Vector of pointers to nameserver and zone entries.
    std::vector<boost::shared_ptr<NameserverEntry> > nameservers_;
    std::vector<boost::shared_ptr<ZoneEntry> >       zones_;
};


/// \brief Remove Zone Entry from Hash Table
///
/// Check that when an entry reaches the top of the zone LRU list, it is removed from the
/// hash table as well.
TEST_F(NameserverAddressStoreTest, ZoneDeletionCheck) {

    // Create a NSAS with a hash size of three and a LRU size of 9 (both zone and
    // nameserver tables).
    DerivedNsas nsas(2, 2);

    // Add six entries to the tables.  After addition the reference count of each element
    // should be 3 - one for the entry in the zones_ vector, and one each for the entries
    // in the LRU list and hash table.
    for (int i = 1; i <= 6; ++i) {
        EXPECT_EQ(1, zones_[i].use_count());
        nsas.AddZoneEntry(zones_[i]);
        EXPECT_EQ(3, zones_[i].use_count());
    }

    // Adding another entry should cause the first one to drop off the LRU list, which
    // should also trigger the deletion of the entry from the hash table.  This should
    // reduce its use count to 1.
    EXPECT_EQ(1, zones_[7].use_count());
    nsas.AddZoneEntry(zones_[7]);
    EXPECT_EQ(3, zones_[7].use_count());

    EXPECT_EQ(1, zones_[1].use_count());
}


/// \brief Remove Entry from Hash Table
///
/// Check that when an entry reaches the top of the LRU list, it is removed from the
/// hash table as well.
TEST_F(NameserverAddressStoreTest, NameserverDeletionCheck) {

    // Create a NSAS with a hash size of three and a LRU size of 9 (both zone and
    // nameserver tables).
    DerivedNsas nsas(2, 2);

    // Add six entries to the tables.  After addition the reference count of each element
    // should be 3 - one for the entry in the nameservers_ vector, and one each for the entries
    // in the LRU list and hash table.
    for (int i = 1; i <= 6; ++i) {
        EXPECT_EQ(1, nameservers_[i].use_count());
        nsas.AddNameserverEntry(nameservers_[i]);
        EXPECT_EQ(3, nameservers_[i].use_count());
    }

    // Adding another entry should cause the first one to drop off the LRU list, which
    // should also trigger the deletion of the entry from the hash table.  This should
    // reduce its use count to 1.
    EXPECT_EQ(1, nameservers_[7].use_count());
    nsas.AddNameserverEntry(nameservers_[7]);
    EXPECT_EQ(3, nameservers_[7].use_count());

    EXPECT_EQ(1, nameservers_[1].use_count());
}

} // namespace nsas
} // namespace isc
