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

#include <datasrc/zone_loader.h>
#include <datasrc/data_source.h>

#include <datasrc/memory/zone_table_segment.h>
#include <datasrc/memory/memory_client.h>

#include <dns/rrclass.h>
#include <dns/name.h>
#include <dns/rrset.h>
#include <util/memory_segment_local.h>
#include <exceptions/exceptions.h>

#include <gtest/gtest.h>

#include <boost/shared_ptr.hpp>
#include <string>
#include <vector>

using isc::dns::RRClass;
using isc::dns::Name;
using std::string;
using std::vector;
using namespace isc::datasrc;

namespace {

class MockClient : public DataSourceClient {
public:
    MockClient() :
        commit_called_(false)
    {}
    virtual FindResult findZone(const Name&) const {
        isc_throw(isc::NotImplemented, "Method not used in tests");
    };
    virtual std::pair<ZoneJournalReader::Result, ZoneJournalReaderPtr>
        getJournalReader(const Name&, uint32_t, uint32_t) const
    {
        isc_throw(isc::NotImplemented, "Method not used in tests");
    }
    virtual ZoneUpdaterPtr getUpdater(const Name& name, bool replace,
                                      bool journaling) const;
    // We store some information about what was happening here.
    // It is publicly accessible, since this is private testing class
    // anyway, so no need to dress it fancy into getters. Some are mutable,
    // since many client methods are const, but we still want to know they
    // were called.
    mutable vector<Name> provided_updaters_;
    // We store string representations of the RRsets. This is simpler than
    // copying them and we can't really put them into shared pointers, because
    // we get them as references.
    vector<string> rrsets_;
    bool commit_called_;
};

// The updater isn't really correct according to the API. For example,
// the whole client can be committed only once in its lifetime. The
// updaters would influence each other if there were more. But we
// don't need more updaters in the same test, so it doesn't matter
// and this way, it is much simpler.
class Updater : public ZoneUpdater {
public:
    Updater(MockClient* client) :
        client_(client)
    {}
    virtual ZoneFinder& getFinder() {
        isc_throw(isc::NotImplemented, "Method not used in tests");
    }
    virtual void addRRset(const isc::dns::AbstractRRset& rrset) {
        if (client_->commit_called_) {
            isc_throw(DataSourceError, "Add after commit");
        }
        client_->rrsets_.push_back(rrset.toText());
    }
    virtual void deleteRRset(const isc::dns::AbstractRRset&) {
        isc_throw(isc::NotImplemented, "Method not used in tests");
    }
    virtual void commit() {
        client_->commit_called_ = true;
    }
private:
    MockClient* client_;
};

ZoneUpdaterPtr
MockClient::getUpdater(const Name& name, bool replace, bool journaling) const {
    EXPECT_TRUE(replace);
    EXPECT_FALSE(journaling);
    provided_updaters_.push_back(name);
    // const_cast is bad. But the const on getUpdater seems wrong in the first
    // place, since updater will be modifying the data there. And the updater
    // wants to store data into the client so we can examine it later.
    return (ZoneUpdaterPtr(new Updater(const_cast<MockClient*>(this))));
}

class ZoneLoaderTest : public ::testing::Test {
protected:
    ZoneLoaderTest() :
        rrclass_(RRClass::IN()),
        ztable_segment_(memory::ZoneTableSegment::
                        create(isc::data::NullElement(), rrclass_)),
        source_client_(ztable_segment_, rrclass_)
    {}
    void prepareSource(const Name& zone, const char* filename) {
        // TODO:
        // Currently, load uses an urelated implementation. In the long term,
        // the method will probably be deprecated. At that time, we should
        // probably prepare the data in some other way (using sqlite3 or
        // something). This is simpler for now.
        source_client_.load(zone, string(TEST_DATA_DIR) + "/" + filename);
    }
private:
    const RRClass rrclass_;
    // This is because of the in-memory client. We use it to read data
    // from. It is still easier than setting up sqlite3 client, since
    // we have this one in the linked library.

    // FIXME: We should be destroying it by ZoneTableSegment::destroy.
    // But the shared pointer won't let us, will it?
    boost::shared_ptr<memory::ZoneTableSegment> ztable_segment_;
protected:
    memory::InMemoryClient source_client_;
    // This one is mocked. It will help us see what is happening inside.
    // Also, mocking it is simpler than setting up an sqlite3 client.
    MockClient destination_client_;
};

// Use the loader to load an unsigned zone.
TEST_F(ZoneLoaderTest, copyUnsigned) {
    prepareSource(Name::ROOT_NAME(), "root.zone");
    ZoneLoader loader(destination_client_, Name::ROOT_NAME(),
                      source_client_);
    // It gets the updater directly in the constructor
    ASSERT_EQ(1, destination_client_.provided_updaters_.size());
    EXPECT_EQ(Name::ROOT_NAME(), destination_client_.provided_updaters_[0]);
    // Now load the whole zone
    loader.load();
    EXPECT_TRUE(destination_client_.commit_called_);
    // We don't check the whole zone. We check the first and last and the
    // count, which should be enough.

    // The count is 34 because we expect the RRs to be separated.
    EXPECT_EQ(34, destination_client_.rrsets_.size());
    // Ensure known order.
    std::sort(destination_client_.rrsets_.begin(),
              destination_client_.rrsets_.end());
    EXPECT_EQ(". 518400 IN NS a.root-servers.net.\n",
              destination_client_.rrsets_.front());
    EXPECT_EQ("m.root-servers.net. 3600000 IN AAAA 2001:dc3::35\n",
              destination_client_.rrsets_.back());

    // It isn't possible to try again now
    EXPECT_THROW(loader.load(), isc::InvalidOperation);
    EXPECT_THROW(loader.loadIncremental(1), isc::InvalidOperation);
    // Even 0, which should load nothing, returns the error
    EXPECT_THROW(loader.loadIncremental(0), isc::InvalidOperation);
}

}
