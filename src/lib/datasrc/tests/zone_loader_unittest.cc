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
using isc::dns::RRType;
using isc::dns::ConstRRsetPtr;
using std::string;
using std::vector;
using boost::shared_ptr;
using namespace isc::datasrc;

namespace {

class MockClient : public DataSourceClient {
public:
    MockClient() :
        commit_called_(false),
        missing_zone_(false),
        rrclass_(RRClass::IN())
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
    // If set to true, getUpdater returns NULL
    bool missing_zone_;
    // The pretended class of the client. Usualy IN, but can be overriden.
    RRClass rrclass_;
};

// The updater isn't really correct according to the API. For example,
// the whole client can be committed only once in its lifetime. The
// updaters would influence each other if there were more. But we
// don't need more updaters in the same test, so it doesn't matter
// and this way, it is much simpler.
class Updater : public ZoneUpdater {
public:
    Updater(MockClient* client) :
        client_(client),
        finder_(client_->rrclass_)
    {}
    virtual ZoneFinder& getFinder() {
        return (finder_);
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
    class Finder : public ZoneFinder {
    public:
        Finder(const RRClass& rrclass) :
            class_(rrclass)
        {}
        virtual RRClass getClass() const {
            return (class_);
        }
        virtual Name getOrigin() const {
            isc_throw(isc::NotImplemented, "Method not used in tests");
        }
        virtual shared_ptr<Context> find(const Name&, const RRType&,
                                         const FindOptions)
        {
            isc_throw(isc::NotImplemented, "Method not used in tests");
        }
        virtual shared_ptr<Context> findAll(const Name&,
                                            vector<ConstRRsetPtr>&,
                                            const FindOptions)
        {
            isc_throw(isc::NotImplemented, "Method not used in tests");
        }
        virtual FindNSEC3Result findNSEC3(const Name&, bool) {
            isc_throw(isc::NotImplemented, "Method not used in tests");
        }
    private:
        const RRClass class_;
    } finder_;
};

ZoneUpdaterPtr
MockClient::getUpdater(const Name& name, bool replace, bool journaling) const {
    if (missing_zone_) {
        return (ZoneUpdaterPtr());
    }
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
    shared_ptr<memory::ZoneTableSegment> ztable_segment_;
protected:
    memory::InMemoryClient source_client_;
    // This one is mocked. It will help us see what is happening inside.
    // Also, mocking it is simpler than setting up an sqlite3 client.
    MockClient destination_client_;
};

// Use the loader to load an unsigned zone.
TEST_F(ZoneLoaderTest, copyUnsigned) {
    prepareSource(Name::ROOT_NAME(), "root.zone");
    ZoneLoader loader(destination_client_, Name::ROOT_NAME(), source_client_);
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

// Try loading incrementally.
TEST_F(ZoneLoaderTest, copyUnsignedIncremental) {
    prepareSource(Name::ROOT_NAME(), "root.zone");
    ZoneLoader loader(destination_client_, Name::ROOT_NAME(), source_client_);

    // Try loading few RRs first.
    loader.loadIncremental(10);
    // We should get the 10 we asked for
    EXPECT_EQ(10, destination_client_.rrsets_.size());
    // Not committed yet, we didn't complete the loading
    EXPECT_FALSE(destination_client_.commit_called_);

    // This is unusual, but allowed. Check it doesn't do anything
    loader.loadIncremental(0);
    EXPECT_EQ(10, destination_client_.rrsets_.size());
    EXPECT_FALSE(destination_client_.commit_called_);

    // We can finish the rest
    loader.loadIncremental(30);
    EXPECT_EQ(34, destination_client_.rrsets_.size());
    EXPECT_TRUE(destination_client_.commit_called_);

    // No more loading now
    EXPECT_THROW(loader.load(), isc::InvalidOperation);
    EXPECT_THROW(loader.loadIncremental(1), isc::InvalidOperation);
    EXPECT_THROW(loader.loadIncremental(0), isc::InvalidOperation);
}

// Check we can load RRSIGs and NSEC3 (which could break due to them being
// in separate namespace)
TEST_F(ZoneLoaderTest, copySigned) {
    prepareSource(Name("example.org"), "example.org.nsec3-signed");
    ZoneLoader loader(destination_client_, Name("example.org"),
                      source_client_);
    loader.load();

    // All the RRs are there, including the ones in NSEC3 namespace
    EXPECT_EQ(14, destination_client_.rrsets_.size());
    EXPECT_TRUE(destination_client_.commit_called_);
    // Same trick with sorting to know where they are
    std::sort(destination_client_.rrsets_.begin(),
              destination_client_.rrsets_.end());
    // Due to the R at the beginning, this one should be last
    EXPECT_EQ("09GM5T42SMIMT7R8DF6RTG80SFMS1NLU.example.org. 1200 IN NSEC3 "
              "1 0 10 AABBCCDD RKOF8QMFRB5F2V9EJHFBVB2JPVSA0DJD A RRSIG\n",
              destination_client_.rrsets_[0]);
    EXPECT_EQ("09GM5T42SMIMT7R8DF6RTG80SFMS1NLU.example.org. 1200 IN RRSIG "
              "NSEC3 7 3 1200 20120301040838 20120131040838 19562 example.org."
              " EdwMeepLf//lV+KpCAN+213Scv1rrZyj4i2OwoCP4XxxS3CWGSuvYuKOyfZc8w"
              "KRcrD/4YG6nZVXE0s5O8NahjBJmDIyVt4WkfZ6QthxGg8ggLVvcD3dFksPyiKHf"
              "/WrTOZPSsxvN5m/i1Ey6+YWS01Gf3WDCMWDauC7Nmh3CTM=\n",
              destination_client_.rrsets_[1]);
}

// If the destination zone does not exist, it throws
TEST_F(ZoneLoaderTest, copyMissingDestination) {
    destination_client_.missing_zone_ = true;
    prepareSource(Name::ROOT_NAME(), "root.zone");
    EXPECT_THROW(ZoneLoader(destination_client_, Name::ROOT_NAME(),
                            source_client_), DataSourceError);
}

// If the source zone does not exist, it throws
TEST_F(ZoneLoaderTest, copyMissingSource) {
    EXPECT_THROW(ZoneLoader(destination_client_, Name::ROOT_NAME(),
                            source_client_), DataSourceError);
}

// The class of the source and destination are different
TEST_F(ZoneLoaderTest, classMismatch) {
    destination_client_.rrclass_ = RRClass::CH();
    prepareSource(Name::ROOT_NAME(), "root.zone");
    EXPECT_THROW(ZoneLoader(destination_client_, Name::ROOT_NAME(),
                            source_client_), isc::InvalidParameter);
}

// Load an unsigned zone, all at once
TEST_F(ZoneLoaderTest, loadUnsigned) {
    ZoneLoader loader(destination_client_, Name::ROOT_NAME(),
                      TEST_DATA_DIR "/root.zone");
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

// Try loading from master file incrementally.
TEST_F(ZoneLoaderTest, loadUnsignedIncremental) {
    ZoneLoader loader(destination_client_, Name::ROOT_NAME(),
                      TEST_DATA_DIR "/root.zone");

    // Try loading few RRs first.
    loader.loadIncremental(10);
    // We should get the 10 we asked for
    EXPECT_EQ(10, destination_client_.rrsets_.size());
    // Not committed yet, we didn't complete the loading
    EXPECT_FALSE(destination_client_.commit_called_);

    // This is unusual, but allowed. Check it doesn't do anything
    loader.loadIncremental(0);
    EXPECT_EQ(10, destination_client_.rrsets_.size());
    EXPECT_FALSE(destination_client_.commit_called_);

    // We can finish the rest
    loader.loadIncremental(30);
    EXPECT_EQ(34, destination_client_.rrsets_.size());
    EXPECT_TRUE(destination_client_.commit_called_);

    // No more loading now
    EXPECT_THROW(loader.load(), isc::InvalidOperation);
    EXPECT_THROW(loader.loadIncremental(1), isc::InvalidOperation);
    EXPECT_THROW(loader.loadIncremental(0), isc::InvalidOperation);
}

// If the destination zone does not exist, it throws
TEST_F(ZoneLoaderTest, loadMissingDestination) {
    destination_client_.missing_zone_ = true;
    EXPECT_THROW(ZoneLoader(destination_client_, Name::ROOT_NAME(),
                            TEST_DATA_DIR "/root.zone"), DataSourceError);
}

// Check we can load RRSIGs and NSEC3 (which could break due to them being
// in separate namespace)
TEST_F(ZoneLoaderTest, loadSigned) {
    ZoneLoader loader(destination_client_, Name("example.org"),
                      TEST_DATA_DIR "/example.org.nsec3-signed");
    loader.load();

    // All the RRs are there, including the ones in NSEC3 namespace
    EXPECT_EQ(14, destination_client_.rrsets_.size());
    EXPECT_TRUE(destination_client_.commit_called_);
    // Same trick with sorting to know where they are
    std::sort(destination_client_.rrsets_.begin(),
              destination_client_.rrsets_.end());
    // Due to the R at the beginning, this one should be last
    EXPECT_EQ("09GM5T42SMIMT7R8DF6RTG80SFMS1NLU.example.org. 1200 IN NSEC3 "
              "1 0 10 AABBCCDD RKOF8QMFRB5F2V9EJHFBVB2JPVSA0DJD A RRSIG\n",
              destination_client_.rrsets_[0]);
    EXPECT_EQ("09GM5T42SMIMT7R8DF6RTG80SFMS1NLU.example.org. 1200 IN RRSIG "
              "NSEC3 7 3 1200 20120301040838 20120131040838 19562 example.org."
              " EdwMeepLf//lV+KpCAN+213Scv1rrZyj4i2OwoCP4XxxS3CWGSuvYuKOyfZc8w"
              "KRcrD/4YG6nZVXE0s5O8NahjBJmDIyVt4WkfZ6QthxGg8ggLVvcD3dFksPyiKHf"
              "/WrTOZPSsxvN5m/i1Ey6+YWS01Gf3WDCMWDauC7Nmh3CTM=\n",
              destination_client_.rrsets_[1]);
}

// Test it throws when there's no such file
TEST_F(ZoneLoaderTest, loadNoSuchFile) {
    ZoneLoader loader(destination_client_, Name::ROOT_NAME(),
                      "This file does not exist");
    EXPECT_THROW(loader.load(), MasterFileError);
    EXPECT_FALSE(destination_client_.commit_called_);
}

// And it also throws when there's a syntax error in the master file
TEST_F(ZoneLoaderTest, loadSyntaxError) {
    ZoneLoader loader(destination_client_, Name::ROOT_NAME(),
                      // This is not a master file for sure
                      // (misusing a file that happens to be there
                      // already).
                      TEST_DATA_DIR "/example.org.sqlite3");
    EXPECT_THROW(loader.load(), MasterFileError);
    EXPECT_FALSE(destination_client_.commit_called_);
}

}
