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

#include <exceptions/exceptions.h>

#include <util/memory_segment_local.h>

#include <dns/name.h>
#include <dns/rrclass.h>
#include <dns/masterload.h>
#include <dns/nsec3hash.h>
#include <dns/rdata.h>
#include <dns/rdataclass.h>
#include <dns/rrsetlist.h>
#include <dns/rrttl.h>
#include <dns/masterload.h>

#include <datasrc/result.h>
#include <datasrc/data_source.h>
#include <datasrc/memory/zone_data.h>
#include <datasrc/memory/zone_table.h>
#include <datasrc/memory/memory_client.h>

#include <gtest/gtest.h>

#include <new>                  // for bad_alloc

using namespace isc::dns;
using namespace isc::datasrc;
using namespace isc::datasrc::memory;

namespace {
class MemoryClientTest : public ::testing::Test {
protected:
    MemoryClientTest() : zclass_(RRClass::IN()),
                      zname1(Name("example.com")),
                      zname2(Name("example.net")),
                      zname3(Name("example")),
                      client_(new InMemoryClient(zclass_))
    {}
    ~MemoryClientTest() {
        if (client_ != NULL) {
            delete client_;
        }
    }
    void TearDown() {
        delete client_;
        client_ = NULL;
        EXPECT_TRUE(mem_sgmt_.allMemoryDeallocated()); // catch any leak here.
    }
    const RRClass zclass_;
    const Name zname1, zname2, zname3;
    isc::util::MemorySegmentLocal mem_sgmt_;
    InMemoryClient* client_;
    memory::ZoneTable* zone_table;
};

TEST_F(MemoryClientTest, loadRRsetDoesntMatchOrigin) {
    // Attempting to load example.org to example.com zone should result
    // in an exception.
    EXPECT_THROW(client_->load(Name("example.com"),
                               TEST_DATA_DIR "/example.org-empty.zone"),
                 MasterLoadError);
}

TEST_F(MemoryClientTest, getZoneCount) {
    EXPECT_EQ(0, client_->getZoneCount());
    client_->load(Name("example.org"), TEST_DATA_DIR "/example.org-empty.zone");
    EXPECT_EQ(1, client_->getZoneCount());
}

TEST_F(MemoryClientTest, getIteratorForNonExistentZone) {
    // Zone "." doesn't exist
    EXPECT_THROW(client_->getIterator(Name(".")), DataSourceError);
}

TEST_F(MemoryClientTest, getIterator) {
    client_->load(Name("example.org"), TEST_DATA_DIR "/example.org-empty.zone");
    ZoneIteratorPtr iterator(client_->getIterator(Name("example.org")));

    // First we have the SOA
    ConstRRsetPtr rrset_soa(iterator->getNextRRset());
    EXPECT_TRUE(rrset_soa);
    EXPECT_EQ(RRType::SOA(), rrset_soa->getType());

    // There's nothing else in this zone
    EXPECT_EQ(ConstRRsetPtr(), iterator->getNextRRset());

    // Iterating past the end should result in an exception
    EXPECT_THROW(iterator->getNextRRset(), isc::Unexpected);
}

TEST_F(MemoryClientTest, getIteratorGetSOAThrowsNotImplemented) {
    client_->load(Name("example.org"), TEST_DATA_DIR "/example.org-empty.zone");
    ZoneIteratorPtr iterator(client_->getIterator(Name("example.org")));

    // This method is not implemented.
    EXPECT_THROW(iterator->getSOA(), isc::NotImplemented);
}

TEST_F(MemoryClientTest, addRRsetToNonExistentZoneThrows) {
    // The zone "example.org" doesn't exist, so we can't add an RRset to
    // it.
    RRsetPtr rrset_a(new RRset(Name("example.org"), RRClass::IN(), RRType::A(),
                               RRTTL(300)));
    rrset_a->addRdata(rdata::in::A("192.0.2.1"));
    EXPECT_THROW(client_->add(Name("example.org"), rrset_a), DataSourceError);
}

TEST_F(MemoryClientTest, getUpdaterThrowsNotImplemented) {
    // This method is not implemented.
    EXPECT_THROW(client_->getUpdater(Name("."), false, false),
                 isc::NotImplemented);
}

TEST_F(MemoryClientTest, getJournalReaderNotImplemented) {
    // This method is not implemented.
    EXPECT_THROW(client_->getJournalReader(Name("."), 0, 0),
                 isc::NotImplemented);
}
}
