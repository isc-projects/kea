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
#include <datasrc/exceptions.h>
#include <datasrc/rrset_collection_base.h>
#include <datasrc/cache_config.h>

#include <datasrc/memory/zone_table_segment.h>
#include <datasrc/memory/memory_client.h>
#include <datasrc/memory/zone_writer.h>

#include <dns/rrclass.h>
#include <dns/name.h>
#include <dns/rrset.h>
#include <dns/rdataclass.h>
#include <util/memory_segment_local.h>
#include <exceptions/exceptions.h>

#include <cc/data.h>

#include <gtest/gtest.h>

#include <boost/shared_ptr.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/foreach.hpp>

#include <string>
#include <vector>

using namespace isc::dns;
using namespace isc::datasrc;
using isc::data::Element;
using boost::shared_ptr;
using std::string;
using std::vector;

namespace {

class MockClient : public DataSourceClient {
public:
    MockClient() :
        commit_called_(false),
        missing_zone_(false),
        rrclass_(RRClass::IN())
    {}
    class Finder : public ZoneFinder {
    public:
        Finder(const Name& origin) :
            origin_(origin)
        {}
        Name getOrigin() const {
            return (origin_);
        }
        RRClass getClass() const {
            return (RRClass::IN());
        }
        // The rest is not to be called, so they throw.
        shared_ptr<Context> find(const Name&, const RRType&,
                                 const FindOptions)
        {
            isc_throw(isc::NotImplemented, "Not implemented");
        }
        shared_ptr<Context> findAll(const Name&,
                                    vector<ConstRRsetPtr>&,
                                    const FindOptions)
        {
            isc_throw(isc::NotImplemented, "Not implemented");
        }
        FindNSEC3Result findNSEC3(const Name&, bool) {
            isc_throw(isc::NotImplemented, "Not implemented");
        }
    private:
        Name origin_;
    };
    class Iterator : public ZoneIterator {
    public:
        Iterator(const Name& origin) :
            origin_(origin),
            soa_(new RRset(origin_, RRClass::IN(), RRType::SOA(),
                           RRTTL(3600)))
        {
            // The RData here is bogus, but it is not used to anything. There
            // just needs to be some.
            soa_->addRdata(rdata::generic::SOA(Name::ROOT_NAME(),
                                               Name::ROOT_NAME(),
                                               0, 0, 0, 0, 0));
            rrsets_.push_back(soa_);

            // There is no NS record on purpose here.

            // Dummy A rrset. This is used for checking zone data after
            // reload.
            RRsetPtr rrset(new RRset(Name("tstzonedata").concatenate(origin_),
                                     RRClass::IN(), RRType::A(),
                                     RRTTL(3600)));
            rrset->addRdata(rdata::in::A("192.0.2.1"));
            rrsets_.push_back(rrset);

            rrsets_.push_back(ConstRRsetPtr());

            it_ = rrsets_.begin();
        }
        virtual isc::dns::ConstRRsetPtr getNextRRset() {
            ConstRRsetPtr result = *it_;
            ++it_;
            return (result);
        }
        virtual isc::dns::ConstRRsetPtr getSOA() const {
            return (soa_);
        }
    private:
        const Name origin_;
        const RRsetPtr soa_;
        std::vector<ConstRRsetPtr> rrsets_;
        std::vector<ConstRRsetPtr>::const_iterator it_;
    };
    virtual ZoneIteratorPtr getIterator(const isc::dns::Name& name,
                                        bool) const
    {
        if (name != Name("example.org")) {
            isc_throw(DataSourceError, "No such zone");
        }
        return (ZoneIteratorPtr(new Iterator(Name("example.org"))));
    }
    virtual FindResult findZone(const Name& name) const {
        const Name origin("example.org");
        const ZoneFinderPtr finder(new Finder(origin));
        NameComparisonResult compar(origin.compare(name));
        switch (compar.getRelation()) {
            case NameComparisonResult::EQUAL:
                return (FindResult(result::SUCCESS, finder));
            case NameComparisonResult::SUPERDOMAIN:
                return (FindResult(result::PARTIALMATCH, finder));
            default:
                return (FindResult(result::NOTFOUND, ZoneFinderPtr()));
        }
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
    vector<RRsetPtr> rrsets_;
    // List of rrsets as texts, for easier manipulation
    vector<string> rrset_texts_;
    bool commit_called_;
    // If set to true, getUpdater returns NULL
    bool missing_zone_;
    // The pretended class of the client. Usualy IN, but can be overriden.
    RRClass rrclass_;
};

// Test implementation of RRsetCollectionBase. This is currently just a
// wrapper around \c isc::datasrc::RRsetCollectionBase;
// \c isc::datasrc::RRsetCollectionBase may become an abstract class in
// the future.
class TestRRsetCollection : public isc::datasrc::RRsetCollectionBase {
public:
    TestRRsetCollection(ZoneUpdater& updater,
                        const isc::dns::RRClass& rrclass) :
        isc::datasrc::RRsetCollectionBase(updater, rrclass)
    {}
};

// The updater isn't really correct according to the API. For example,
// the whole client can be committed only once in its lifetime. The
// updaters would influence each other if there were more. But we
// don't need more updaters in the same test, so it doesn't matter
// and this way, it is much simpler.
class Updater : public ZoneUpdater {
public:
    Updater(MockClient* client, const Name& name) :
        client_(client),
        finder_(client_->rrclass_, name, client_->rrsets_)
    {}
    virtual ZoneFinder& getFinder() {
        return (finder_);
    }
    virtual isc::dns::RRsetCollectionBase& getRRsetCollection() {
        if (!rrset_collection_) {
            rrset_collection_.reset(new TestRRsetCollection(*this,
                                                            client_->rrclass_));
        }
        return (*rrset_collection_);
    }
    virtual void addRRset(const isc::dns::AbstractRRset& rrset) {
        if (client_->commit_called_) {
            isc_throw(DataSourceError, "Add after commit");
        }
        // We need to copy the RRset. We don't do it properly (we omit the
        // signature, for example), because we don't need to.
        RRsetPtr new_rrset(new isc::dns::BasicRRset(rrset.getName(),
                                                    rrset.getClass(),
                                                    rrset.getType(),
                                                    rrset.getTTL()));
        for (isc::dns::RdataIteratorPtr i(rrset.getRdataIterator());
             !i->isLast(); i->next()) {
            new_rrset->addRdata(i->getCurrent());
        }
        client_->rrsets_.push_back(new_rrset);
        client_->rrset_texts_.push_back(rrset.toText());
    }
    virtual void deleteRRset(const isc::dns::AbstractRRset&) {
        isc_throw(isc::NotImplemented, "Method not used in tests");
    }
    virtual void commit() {
        client_->commit_called_ = true;
    }
private:
    MockClient* client_;
    boost::scoped_ptr<TestRRsetCollection> rrset_collection_;
    class Finder : public ZoneFinder {
    public:
        Finder(const RRClass& rrclass, const Name& name,
               const vector<RRsetPtr>& rrsets) :
            class_(rrclass),
            name_(name),
            rrsets_(rrsets)
        {}
        virtual RRClass getClass() const {
            return (class_);
        }
        virtual Name getOrigin() const {
            return (name_);
        }
        virtual shared_ptr<Context> find(const Name& name, const RRType& type,
                                         const FindOptions options)
        {
            // The method is not completely correct. It ignores many special
            // cases and also the options except for the result. But this is
            // enough for the tests.  We care only about exact match here.
            BOOST_FOREACH(const RRsetPtr& rrset, rrsets_) {
                if (rrset->getName() == name && rrset->getType() == type) {
                    return (shared_ptr<Context>(
                        new GenericContext(*this, options,
                                           ResultContext(SUCCESS, rrset))));
                }
            }
            return (shared_ptr<Context>(
                new GenericContext(*this, options,
                                   ResultContext(NXRRSET, ConstRRsetPtr()))));
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
        const Name name_;
        const vector<RRsetPtr>& rrsets_;
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
    return (ZoneUpdaterPtr(new Updater(const_cast<MockClient*>(this), name)));
}

class ZoneLoaderTest : public ::testing::Test {
protected:
    ZoneLoaderTest() :
        rrclass_(RRClass::IN())
    {
        // Use ROOT_NAME as a placeholder; it will be ignored if filename is
        // null.
        prepareSource(Name::ROOT_NAME(), NULL);
    }
    void prepareSource(const Name& zone, const char* filename) {
        // Cleanup the existing data in the right order
        source_client_.reset();
        ztable_segment_.reset();

        // (re)configure zone table, then (re)construct the in-memory client
        // with it.
        string param_data;
        if (filename) {
            param_data = "\"" + zone.toText() + "\": \"" +
                string(TEST_DATA_DIR) + "/" + filename + "\"";
        }
        const internal::CacheConfig cache_conf(
            "MasterFiles", NULL, *Element::fromJSON(
                "{\"cache-enable\": true,"
                " \"params\": {" + param_data + "}}"), true);
        ztable_segment_.reset(memory::ZoneTableSegment::create(
                                  rrclass_, cache_conf.getSegmentType()));
        if (filename) {
            boost::scoped_ptr<memory::ZoneWriter> writer(
                ztable_segment_->getZoneWriter(cache_conf.getLoadAction(
                                                   rrclass_, zone),
                                               zone, rrclass_));
            writer->load();
            writer->install();
            writer->cleanup();
        }
        source_client_.reset(new memory::InMemoryClient(ztable_segment_,
                                                        rrclass_));
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
    boost::scoped_ptr<memory::InMemoryClient> source_client_;
    // This one is mocked. It will help us see what is happening inside.
    // Also, mocking it is simpler than setting up an sqlite3 client.
    MockClient destination_client_;
};

// Use the loader to load an unsigned zone.
TEST_F(ZoneLoaderTest, copyUnsigned) {
    prepareSource(Name::ROOT_NAME(), "root.zone");
    ZoneLoader loader(destination_client_, Name::ROOT_NAME(), *source_client_);
    // It gets the updater directly in the constructor
    ASSERT_EQ(1, destination_client_.provided_updaters_.size());
    EXPECT_EQ(Name::ROOT_NAME(), destination_client_.provided_updaters_[0]);

    // Counter is initialized to 0, progress is "unknown" in case of copy.
    EXPECT_EQ(0, loader.getRRCount());
    EXPECT_EQ(ZoneLoader::PROGRESS_UNKNOWN, loader.getProgress());

    // Now load the whole zone
    loader.load();
    EXPECT_TRUE(destination_client_.commit_called_);
    // We don't check the whole zone. We check the first and last and the
    // count, which should be enough.

    // The count is 34 because we expect the RRs to be separated.
    EXPECT_EQ(34, destination_client_.rrsets_.size());

    // Check various counters.  getRRCount should be identical of the RRs
    // we've seen. Progress is still "unknown" in the copy operation.
    EXPECT_EQ(destination_client_.rrsets_.size(), loader.getRRCount());
    EXPECT_EQ(ZoneLoader::PROGRESS_UNKNOWN, loader.getProgress());

    // Ensure known order.
    std::sort(destination_client_.rrset_texts_.begin(),
              destination_client_.rrset_texts_.end());
    EXPECT_EQ(". 518400 IN NS a.root-servers.net.\n",
              destination_client_.rrset_texts_.front());
    EXPECT_EQ("m.root-servers.net. 3600000 IN AAAA 2001:dc3::35\n",
              destination_client_.rrset_texts_.back());

    // It isn't possible to try again now
    EXPECT_THROW(loader.load(), isc::InvalidOperation);
    EXPECT_THROW(loader.loadIncremental(1), isc::InvalidOperation);
    // Even 0, which should load nothing, returns the error
    EXPECT_THROW(loader.loadIncremental(0), isc::InvalidOperation);
}

// Try loading incrementally.
TEST_F(ZoneLoaderTest, copyUnsignedIncremental) {
    prepareSource(Name::ROOT_NAME(), "root.zone");
    ZoneLoader loader(destination_client_, Name::ROOT_NAME(), *source_client_);

    // Try loading few RRs first.
    loader.loadIncremental(10);
    // We should get the 10 we asked for
    EXPECT_EQ(10, destination_client_.rrsets_.size());
    // Not committed yet, we didn't complete the loading
    EXPECT_FALSE(destination_client_.commit_called_);

    // Check we can get intermediate counters. Progress is always "unknown"
    // in case of copy.
    EXPECT_EQ(destination_client_.rrsets_.size(), loader.getRRCount());
    EXPECT_EQ(ZoneLoader::PROGRESS_UNKNOWN, loader.getProgress());

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
                      *source_client_);
    loader.load();

    // All the RRs are there, including the ones in NSEC3 namespace
    EXPECT_EQ(14, destination_client_.rrsets_.size());
    EXPECT_TRUE(destination_client_.commit_called_);
    // Same trick with sorting to know where they are
    std::sort(destination_client_.rrset_texts_.begin(),
              destination_client_.rrset_texts_.end());
    // Due to the R at the beginning, this one should be last
    EXPECT_EQ("09GM5T42SMIMT7R8DF6RTG80SFMS1NLU.example.org. 1200 IN NSEC3 "
              "1 0 10 AABBCCDD RKOF8QMFRB5F2V9EJHFBVB2JPVSA0DJD A RRSIG\n",
              destination_client_.rrset_texts_[0]);
    EXPECT_EQ("09GM5T42SMIMT7R8DF6RTG80SFMS1NLU.example.org. 1200 IN RRSIG "
              "NSEC3 7 3 1200 20120301040838 20120131040838 19562 example.org."
              " EdwMeepLf//lV+KpCAN+213Scv1rrZyj4i2OwoCP4XxxS3CWGSuvYuKOyfZc8w"
              "KRcrD/4YG6nZVXE0s5O8NahjBJmDIyVt4WkfZ6QthxGg8ggLVvcD3dFksPyiKHf"
              "/WrTOZPSsxvN5m/i1Ey6+YWS01Gf3WDCMWDauC7Nmh3CTM=\n",
              destination_client_.rrset_texts_[1]);
}

// If the destination zone does not exist, it throws
TEST_F(ZoneLoaderTest, copyMissingDestination) {
    destination_client_.missing_zone_ = true;
    prepareSource(Name::ROOT_NAME(), "root.zone");
    EXPECT_THROW(ZoneLoader(destination_client_, Name::ROOT_NAME(),
                            *source_client_), DataSourceError);
}

// If the source zone does not exist, it throws
TEST_F(ZoneLoaderTest, copyMissingSource) {
    EXPECT_THROW(ZoneLoader(destination_client_, Name::ROOT_NAME(),
                            *source_client_), DataSourceError);
}

// The class of the source and destination are different
TEST_F(ZoneLoaderTest, classMismatch) {
    destination_client_.rrclass_ = RRClass::CH();
    prepareSource(Name::ROOT_NAME(), "root.zone");
    EXPECT_THROW(ZoneLoader(destination_client_, Name::ROOT_NAME(),
                            *source_client_), isc::InvalidParameter);
}

// Load an unsigned zone, all at once
TEST_F(ZoneLoaderTest, loadUnsigned) {
    ZoneLoader loader(destination_client_, Name::ROOT_NAME(),
                      TEST_DATA_DIR "/root.zone");

    // Counter and progress are initialized to 0.
    EXPECT_EQ(0, loader.getRRCount());
    EXPECT_EQ(0, loader.getProgress());

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

    // getRRCount should be identical of the RRs we've seen.  progress
    // should reach 100% (= 1).
    EXPECT_EQ(destination_client_.rrsets_.size(), loader.getRRCount());
    EXPECT_EQ(1, loader.getProgress());

    // Ensure known order.
    std::sort(destination_client_.rrset_texts_.begin(),
              destination_client_.rrset_texts_.end());
    EXPECT_EQ(". 518400 IN NS a.root-servers.net.\n",
              destination_client_.rrset_texts_.front());
    EXPECT_EQ("m.root-servers.net. 3600000 IN AAAA 2001:dc3::35\n",
              destination_client_.rrset_texts_.back());

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

    // Counters are initialized to 0.
    EXPECT_EQ(0, loader.getRRCount());
    EXPECT_EQ(0, loader.getProgress());

    // Try loading few RRs first.
    loader.loadIncremental(10);
    // We should get the 10 we asked for
    EXPECT_EQ(10, destination_client_.rrsets_.size());
    // Not committed yet, we didn't complete the loading
    EXPECT_FALSE(destination_client_.commit_called_);

    EXPECT_EQ(10, destination_client_.rrsets_.size());
    EXPECT_FALSE(destination_client_.commit_called_);

    // Check we can get intermediate counters. Expected progress is calculated
    // based on the size of the zone file and the offset to the end of 10th RR
    // (subject to future changes to the file, but we assume it's a rare
    // event.).  The expected value should be the exact expression that
    // getProgress() should do internally, so EXPECT_EQ() should work here,
    // but floating-point comparison can be always tricky we use
    // EXPECT_DOUBLE_EQ just in case.
    EXPECT_EQ(destination_client_.rrsets_.size(), loader.getRRCount());
    // file size = 1541, offset = 428 (27.77%).
    EXPECT_DOUBLE_EQ(static_cast<double>(428) / 1541, loader.getProgress());

    // We can finish the rest
    loader.loadIncremental(30);
    EXPECT_EQ(34, destination_client_.rrsets_.size());
    EXPECT_TRUE(destination_client_.commit_called_);

    // Counters are updated accordingly. Progress should reach 100%.
    EXPECT_EQ(destination_client_.rrsets_.size(), loader.getRRCount());
    EXPECT_EQ(1, loader.getProgress());

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
    std::sort(destination_client_.rrset_texts_.begin(),
              destination_client_.rrset_texts_.end());
    // Due to the R at the beginning, this one should be last
    EXPECT_EQ("09GM5T42SMIMT7R8DF6RTG80SFMS1NLU.example.org. 1200 IN NSEC3 "
              "1 0 10 AABBCCDD RKOF8QMFRB5F2V9EJHFBVB2JPVSA0DJD A RRSIG\n",
              destination_client_.rrset_texts_[0]);
    EXPECT_EQ("09GM5T42SMIMT7R8DF6RTG80SFMS1NLU.example.org. 1200 IN RRSIG "
              "NSEC3 7 3 1200 20120301040838 20120131040838 19562 example.org."
              " EdwMeepLf//lV+KpCAN+213Scv1rrZyj4i2OwoCP4XxxS3CWGSuvYuKOyfZc8w"
              "KRcrD/4YG6nZVXE0s5O8NahjBJmDIyVt4WkfZ6QthxGg8ggLVvcD3dFksPyiKHf"
              "/WrTOZPSsxvN5m/i1Ey6+YWS01Gf3WDCMWDauC7Nmh3CTM=\n",
              destination_client_.rrset_texts_[1]);
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

// Test there's validation of the data in the zone loader.
TEST_F(ZoneLoaderTest, loadCheck) {
    ZoneLoader loader(destination_client_, Name("example.org"),
                      TEST_DATA_DIR "/novalidate.zone");
    EXPECT_THROW(loader.loadIncremental(10), ZoneContentError);
    // The messages go to the log. We don't have an easy way to examine them.
    EXPECT_FALSE(destination_client_.commit_called_);
}

// Check a warning doesn't disrupt the loading of the zone
TEST_F(ZoneLoaderTest, loadCheckWarn) {
    ZoneLoader loader(destination_client_, Name("example.org"),
                      TEST_DATA_DIR "/checkwarn.zone");
    EXPECT_TRUE(loader.loadIncremental(10));
    // The messages go to the log. We don't have an easy way to examine them.
    // But the zone was committed and contains all 3 RRs
    EXPECT_TRUE(destination_client_.commit_called_);
    EXPECT_EQ(3, destination_client_.rrsets_.size());
}

TEST_F(ZoneLoaderTest, copyCheckWarn) {
    prepareSource(Name("example.org"), "checkwarn.zone");
    ZoneLoader loader(destination_client_, Name("example.org"),
                      *source_client_);
    EXPECT_TRUE(loader.loadIncremental(10));
    // The messages go to the log. We don't have an easy way to examine them.
    // But the zone was committed and contains all 3 RRs
    EXPECT_TRUE(destination_client_.commit_called_);
    EXPECT_EQ(3, destination_client_.rrsets_.size());

}

// Test there's validation of the data in the zone loader when copying
// from another data source.
TEST_F(ZoneLoaderTest, copyCheck) {
    // In this test, my_source_client provides a zone that does not
    // validate (no NS).
    MockClient my_source_client;
    ZoneLoader loader(destination_client_, Name("example.org"),
                      my_source_client);

    EXPECT_THROW(loader.loadIncremental(10), ZoneContentError);
    // The messages go to the log. We don't have an easy way to examine them.
    EXPECT_FALSE(destination_client_.commit_called_);
}

}
