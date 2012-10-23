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

#include <datasrc/client_list.h>
#include <datasrc/client.h>
#include <datasrc/iterator.h>
#include <datasrc/data_source.h>
#include <datasrc/memory/memory_client.h>
#include <datasrc/memory/zone_table_segment.h>
#include <datasrc/memory/zone_finder.h>

#include <dns/rrclass.h>
#include <dns/rrttl.h>
#include <dns/rdataclass.h>

#include <gtest/gtest.h>

#include <set>
#include <fstream>

using namespace isc::datasrc;
using isc::datasrc::memory::InMemoryClient;
using isc::datasrc::memory::ZoneTableSegment;
using isc::datasrc::memory::InMemoryZoneFinder;
using namespace isc::data;
using namespace isc::dns;
using namespace boost;
using namespace std;

namespace {

// A test data source. It pretends it has some zones.
class MockDataSourceClient : public DataSourceClient {
public:
    class Finder : public ZoneFinder {
    public:
        Finder(const Name& origin) :
            origin_(origin)
        {}
        Name getOrigin() const { return (origin_); }
        // The rest is not to be called, so just have them
        RRClass getClass() const {
            isc_throw(isc::NotImplemented, "Not implemented");
        }
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
        Iterator(const Name& origin, bool include_ns) :
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

            if (include_ns) {
                ns_.reset(new RRset(origin_, RRClass::IN(), RRType::NS(),
                                    RRTTL(3600)));
                ns_->addRdata(rdata::generic::NS(Name::ROOT_NAME()));
                rrsets_.push_back(ns_);
            }
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
        RRsetPtr ns_;
        std::vector<ConstRRsetPtr> rrsets_;
        std::vector<ConstRRsetPtr>::const_iterator it_;
    };
    // Constructor from a list of zones.
    MockDataSourceClient(const char* zone_names[]) :
        have_ns_(true), use_baditerator_(true)
    {
        for (const char** zone(zone_names); *zone; ++zone) {
            zones.insert(Name(*zone));
        }
    }
    // Constructor from configuration. The list of zones will be empty, but
    // it will keep the configuration inside for further inspection.
    MockDataSourceClient(const string& type,
                         const ConstElementPtr& configuration) :
        type_(type),
        configuration_(configuration),
        have_ns_(true), use_baditerator_(true)
    {
        EXPECT_NE("MasterFiles", type) << "MasterFiles is a special case "
            "and it never should be created as a data source client";
        if (configuration_->getType() == Element::list) {
            for (size_t i(0); i < configuration_->size(); ++i) {
                zones.insert(Name(configuration_->get(i)->stringValue()));
            }
        }
    }
    virtual FindResult findZone(const Name& name) const {
        if (zones.empty()) {
            return (FindResult(result::NOTFOUND, ZoneFinderPtr()));
        }
        set<Name>::const_iterator it(zones.upper_bound(name));
        if (it == zones.begin()) {
            return (FindResult(result::NOTFOUND, ZoneFinderPtr()));
        }
        --it;
        NameComparisonResult compar(it->compare(name));
        const ZoneFinderPtr finder(new Finder(*it));
        switch (compar.getRelation()) {
            case NameComparisonResult::EQUAL:
                return (FindResult(result::SUCCESS, finder));
            case NameComparisonResult::SUPERDOMAIN:
                return (FindResult(result::PARTIALMATCH, finder));
            default:
                return (FindResult(result::NOTFOUND, ZoneFinderPtr()));
        }
    }
    // These methods are not used. They just need to be there to have
    // complete vtable.
    virtual ZoneUpdaterPtr getUpdater(const Name&, bool, bool) const {
        isc_throw(isc::NotImplemented, "Not implemented");
    }
    virtual pair<ZoneJournalReader::Result, ZoneJournalReaderPtr>
        getJournalReader(const Name&, uint32_t, uint32_t) const
    {
        isc_throw(isc::NotImplemented, "Not implemented");
    }
    virtual ZoneIteratorPtr getIterator(const Name& name, bool) const {
        if (use_baditerator_ && name == Name("noiter.org")) {
            isc_throw(isc::NotImplemented, "Asked not to be implemented");
        } else if (use_baditerator_ && name == Name("null.org")) {
            return (ZoneIteratorPtr());
        } else {
            FindResult result(findZone(name));
            if (result.code == isc::datasrc::result::SUCCESS) {
                return (ZoneIteratorPtr(new Iterator(name, have_ns_)));
            } else {
                isc_throw(DataSourceError, "No such zone");
            }
        }
    }
    void disableNS() { have_ns_ = false; }
    void disableBadIterator() { use_baditerator_ = false; }
    const string type_;
    const ConstElementPtr configuration_;
private:
    set<Name> zones;
    bool have_ns_; // control the iterator behavior wrt whether to include NS
    bool use_baditerator_; // whether to use bogus zone iterators for tests
};


// The test version is the same as the normal version. We, however, add
// some methods to dig directly in the internals, for the tests.
class TestedList : public ConfigurableClientList {
public:
    TestedList(const RRClass& rrclass) :
        ConfigurableClientList(rrclass)
    {}
    DataSources& getDataSources() { return (data_sources_); }
    // Overwrite the list's method to get a data source with given type
    // and configuration. We mock the data source and don't create the
    // container. This is just to avoid some complexity in the tests.
    virtual DataSourcePair getDataSourceClient(const string& type,
                                               const ConstElementPtr&
                                               configuration)
    {
        if (type == "error") {
            isc_throw(DataSourceError, "The error data source type");
        }
        shared_ptr<MockDataSourceClient>
            ds(new MockDataSourceClient(type, configuration));
        // Make sure it is deleted when the test list is deleted.
        to_delete_.push_back(ds);
        return (DataSourcePair(ds.get(), DataSourceClientContainerPtr()));
    }
private:
    // Hold list of data sources created internally, so they are preserved
    // until the end of the test and then deleted.
    vector<shared_ptr<MockDataSourceClient> > to_delete_;
};

const char* ds_zones[][3] = {
    {
        "example.org.",
        "example.com.",
        NULL
    },
    {
        "sub.example.org.",
        NULL, NULL
    },
    {
        NULL, NULL, NULL
    },
    {
        "sub.example.org.",
        NULL, NULL
    }
};

const size_t ds_count = (sizeof(ds_zones) / sizeof(*ds_zones));

class ListTest : public ::testing::Test {
public:
    ListTest() :
        rrclass_(RRClass::IN()),
        // The empty list corresponds to a list with no elements inside
        list_(new TestedList(rrclass_)),
        config_elem_(Element::fromJSON("["
            "{"
            "   \"type\": \"test_type\","
            "   \"params\": {}"
            "}]")),
        config_elem_zones_(Element::fromJSON("["
            "{"
            "   \"type\": \"test_type\","
            "   \"params\": [\"example.org\", \"example.com\", "
            "                \"noiter.org\", \"null.org\"]"
            "}]")),
        config_(Element::fromJSON("{}")),
        ztable_segment_(ZoneTableSegment::create(*config_, rrclass_))
    {
        for (size_t i(0); i < ds_count; ++ i) {
            shared_ptr<MockDataSourceClient>
                ds(new MockDataSourceClient(ds_zones[i]));
            ds_.push_back(ds);
            ds_info_.push_back(ConfigurableClientList::DataSourceInfo(
                                   ds.get(), DataSourceClientContainerPtr(),
                                   false, rrclass_, ztable_segment_));
        }
    }

    // Install a "fake" cached zone using a temporary underlying data source
    // client.
    void prepareCache(size_t index, const Name& zone) {
        // Prepare the temporary data source client
        const char* zones[2];
        const std::string zonename_txt = zone.toText();
        zones[0] = zonename_txt.c_str();
        zones[1] = NULL;
        MockDataSourceClient mock_client(zones);
        // Disable some default features of the mock to distinguish the
        // temporary case from normal case.
        mock_client.disableNS();
        mock_client.disableBadIterator();

        // Create cache from the temporary data source, and push it to the
        // client list.
        const shared_ptr<InMemoryClient> cache(
            new InMemoryClient(ztable_segment_, rrclass_));
        cache->load(zone, *mock_client.getIterator(zone, false));

        ConfigurableClientList::DataSourceInfo& dsrc_info =
                list_->getDataSources()[index];
        dsrc_info.cache_ = cache;
    }
    // Check the positive result is as we expect it.
    void positiveResult(const ClientList::FindResult& result,
                        const shared_ptr<MockDataSourceClient>& dsrc,
                        const Name& name, bool exact,
                        const char* test, bool from_cache = false)
    {
        SCOPED_TRACE(test);
        ASSERT_NE(ZoneFinderPtr(), result.finder_);
        EXPECT_EQ(name, result.finder_->getOrigin());
        EXPECT_EQ(exact, result.exact_match_);
        // If it is a positive result, there's something to keep
        // alive, even when we don't know what it is.
        // Any better idea how to test it actually keeps the thing
        // alive?
        EXPECT_NE(shared_ptr<ClientList::FindResult::LifeKeeper>(),
                  result.life_keeper_);
        if (from_cache) {
            EXPECT_NE(shared_ptr<InMemoryZoneFinder>(),
                      dynamic_pointer_cast<InMemoryZoneFinder>(
                          result.finder_)) << "Finder is not from cache";
            EXPECT_TRUE(NULL !=
                        dynamic_cast<InMemoryClient*>(result.dsrc_client_));
        } else {
            EXPECT_EQ(dsrc.get(), result.dsrc_client_);
        }
    }
    // Configure the list with multiple data sources, according to
    // some configuration. It uses the index as parameter, to be able to
    // loop through the configurations.
    void multiConfiguration(size_t index) {
        list_->getDataSources().clear();
        switch (index) {
            case 2:
                list_->getDataSources().push_back(ds_info_[2]);
                // The ds_[2] is empty. We just check that it doesn't confuse
                // us. Fall through to the case 0.
            case 0:
                list_->getDataSources().push_back(ds_info_[0]);
                list_->getDataSources().push_back(ds_info_[1]);
                break;
            case 1:
                // The other order
                list_->getDataSources().push_back(ds_info_[1]);
                list_->getDataSources().push_back(ds_info_[0]);
                break;
            case 3:
                list_->getDataSources().push_back(ds_info_[1]);
                list_->getDataSources().push_back(ds_info_[0]);
                // It is the same as ds_[1], but we take from the first one.
                // The first one to match is the correct one.
                list_->getDataSources().push_back(ds_info_[3]);
                break;
            default:
                FAIL() << "Unknown configuration index " << index;
        }
    }
    void checkDS(size_t index, const string& type, const string& params,
                 bool cache) const
    {
        ASSERT_GT(list_->getDataSources().size(), index);
        MockDataSourceClient* ds(dynamic_cast<MockDataSourceClient*>(
            list_->getDataSources()[index].data_src_client_));

        // Comparing with NULL does not work
        ASSERT_NE(ds, static_cast<const MockDataSourceClient*>(NULL));
        EXPECT_EQ(type, ds->type_);
        EXPECT_TRUE(Element::fromJSON(params)->equals(*ds->configuration_));
        EXPECT_EQ(cache, list_->getDataSources()[index].cache_ !=
                  shared_ptr<InMemoryClient>());
    }
    const RRClass rrclass_;
    shared_ptr<TestedList> list_;
    const ClientList::FindResult negative_result_;
    vector<shared_ptr<MockDataSourceClient> > ds_;
    vector<ConfigurableClientList::DataSourceInfo> ds_info_;
    const ConstElementPtr config_elem_, config_elem_zones_, config_;
    shared_ptr<ZoneTableSegment> ztable_segment_;
};

// Test the test itself
TEST_F(ListTest, selfTest) {
    EXPECT_EQ(result::SUCCESS, ds_[0]->findZone(Name("example.org")).code);
    EXPECT_EQ(result::PARTIALMATCH,
              ds_[0]->findZone(Name("sub.example.org")).code);
    EXPECT_EQ(result::NOTFOUND, ds_[0]->findZone(Name("org")).code);
    EXPECT_EQ(result::NOTFOUND, ds_[1]->findZone(Name("example.org")).code);
    EXPECT_EQ(result::NOTFOUND, ds_[0]->findZone(Name("aaa")).code);
    EXPECT_EQ(result::NOTFOUND, ds_[0]->findZone(Name("zzz")).code);
    // Nothing to keep alive here.
    EXPECT_EQ(shared_ptr<ClientList::FindResult::LifeKeeper>(),
                  negative_result_.life_keeper_);
}

// Test the list we create with empty configuration is, in fact, empty
TEST_F(ListTest, emptyList) {
    EXPECT_TRUE(list_->getDataSources().empty());
}

// Check the values returned by a find on an empty list. It should be
// a negative answer (nothing found) no matter if we want an exact or inexact
// match.
TEST_F(ListTest, emptySearch) {
    // No matter what we try, we don't get an answer.

    // Note: we don't have operator<< for the result class, so we cannot use
    // EXPECT_EQ.  Same for other similar cases.
    EXPECT_TRUE(negative_result_ == list_->find(Name("example.org"), false,
                                                false));
    EXPECT_TRUE(negative_result_ == list_->find(Name("example.org"), false,
                                                true));
    EXPECT_TRUE(negative_result_ == list_->find(Name("example.org"), true,
                                                false));
    EXPECT_TRUE(negative_result_ == list_->find(Name("example.org"), true,
                                                true));
}

// Put a single data source inside the list and check it can find an
// exact match if there's one.
TEST_F(ListTest, singleDSExactMatch) {
    list_->getDataSources().push_back(ds_info_[0]);
    // This zone is not there
    EXPECT_TRUE(negative_result_ == list_->find(Name("org."), true));
    // But this one is, so check it.
    positiveResult(list_->find(Name("example.org"), true), ds_[0],
                   Name("example.org"), true, "Exact match");
    // When asking for a sub zone of a zone there, we get nothing
    // (we want exact match, this would be partial one)
    EXPECT_TRUE(negative_result_ == list_->find(Name("sub.example.org."),
                                                true));
}

// When asking for a partial match, we get all that the exact one, but more.
TEST_F(ListTest, singleDSBestMatch) {
    list_->getDataSources().push_back(ds_info_[0]);
    // This zone is not there
    EXPECT_TRUE(negative_result_ == list_->find(Name("org.")));
    // But this one is, so check it.
    positiveResult(list_->find(Name("example.org")), ds_[0],
                   Name("example.org"), true, "Exact match");
    // When asking for a sub zone of a zone there, we get the parent
    // one.
    positiveResult(list_->find(Name("sub.example.org.")), ds_[0],
                   Name("example.org"), false, "Subdomain match");
}

const char* const test_names[] = {
    "Sub second",
    "Sub first",
    "With empty",
    "With a duplicity"
};

TEST_F(ListTest, multiExactMatch) {
    // Run through all the multi-configurations
    for (size_t i(0); i < sizeof(test_names) / sizeof(*test_names); ++i) {
        SCOPED_TRACE(test_names[i]);
        multiConfiguration(i);
        // Something that is nowhere there
        EXPECT_TRUE(negative_result_ == list_->find(Name("org."), true));
        // This one is there exactly.
        positiveResult(list_->find(Name("example.org"), true), ds_[0],
                       Name("example.org"), true, "Exact match");
        // This one too, but in a different data source.
        positiveResult(list_->find(Name("sub.example.org."), true), ds_[1],
                       Name("sub.example.org"), true, "Subdomain match");
        // But this one is in neither data source.
        EXPECT_TRUE(negative_result_ ==
                    list_->find(Name("sub.example.com."), true));
    }
}

TEST_F(ListTest, multiBestMatch) {
    // Run through all the multi-configurations
    for (size_t i(0); i < 4; ++ i) {
        SCOPED_TRACE(test_names[i]);
        multiConfiguration(i);
        // Something that is nowhere there
        EXPECT_TRUE(negative_result_ == list_->find(Name("org.")));
        // This one is there exactly.
        positiveResult(list_->find(Name("example.org")), ds_[0],
                       Name("example.org"), true, "Exact match");
        // This one too, but in a different data source.
        positiveResult(list_->find(Name("sub.example.org.")), ds_[1],
                       Name("sub.example.org"), true, "Subdomain match");
        // But this one is in neither data source. But it is a subdomain
        // of one of the zones in the first data source.
        positiveResult(list_->find(Name("sub.example.com.")), ds_[0],
                       Name("example.com."), false, "Subdomain in com");
    }
}

// Check the configuration is empty when the list is empty
TEST_F(ListTest, configureEmpty) {
    const ConstElementPtr elem(new ListElement);
    list_->configure(elem, true);
    EXPECT_TRUE(list_->getDataSources().empty());
    // Check the exact configuration is preserved
    EXPECT_EQ(elem, list_->getConfiguration());
}

// Check we can get multiple data sources and they are in the right order.
TEST_F(ListTest, configureMulti) {
    const ConstElementPtr elem(Element::fromJSON("["
        "{"
        "   \"type\": \"type1\","
        "   \"cache\": \"off\","
        "   \"params\": {}"
        "},"
        "{"
        "   \"type\": \"type2\","
        "   \"cache\": \"off\","
        "   \"params\": {}"
        "}]"
    ));
    list_->configure(elem, true);
    EXPECT_EQ(2, list_->getDataSources().size());
    checkDS(0, "type1", "{}", false);
    checkDS(1, "type2", "{}", false);
    // Check the exact configuration is preserved
    EXPECT_EQ(elem, list_->getConfiguration());
}

// Check we can pass whatever we want to the params
TEST_F(ListTest, configureParams) {
    const char* params[] = {
        "true",
        "false",
        "null",
        "\"hello\"",
        "42",
        "[]",
        "{}",
        NULL
    };
    for (const char** param(params); *param; ++param) {
        SCOPED_TRACE(*param);
        ConstElementPtr elem(Element::fromJSON(string("["
            "{"
            "   \"type\": \"t\","
            "   \"cache\": \"off\","
            "   \"params\": ") + *param +
            "}]"));
        list_->configure(elem, true);
        EXPECT_EQ(1, list_->getDataSources().size());
        checkDS(0, "t", *param, false);
    }
}

TEST_F(ListTest, wrongConfig) {
    const char* configs[] = {
        // A lot of stuff missing from there
        "[{\"type\": \"test_type\", \"params\": 13}, {}]",
        // Some bad types completely
        "{}",
        "true",
        "42",
        "null",
        "[{\"type\": \"test_type\", \"params\": 13}, true]",
        "[{\"type\": \"test_type\", \"params\": 13}, []]",
        "[{\"type\": \"test_type\", \"params\": 13}, 42]",
        // Bad type of type
        "[{\"type\": \"test_type\", \"params\": 13}, {\"type\": 42}]",
        "[{\"type\": \"test_type\", \"params\": 13}, {\"type\": true}]",
        "[{\"type\": \"test_type\", \"params\": 13}, {\"type\": null}]",
        "[{\"type\": \"test_type\", \"params\": 13}, {\"type\": []}]",
        "[{\"type\": \"test_type\", \"params\": 13}, {\"type\": {}}]",
        // Bad type of cache-enable
        "[{\"type\": \"test_type\", \"params\": 13}, "
         "{\"type\": \"x\", \"cache-enable\": 13, \"cache-zones\": []}]",
        "[{\"type\": \"test_type\", \"params\": 13}, "
         "{\"type\": \"x\", \"cache-enable\": \"xx\", \"cache-zones\": []}]",
        "[{\"type\": \"test_type\", \"params\": 13}, "
         "{\"type\": \"x\", \"cache-enable\": [], \"cache-zones\": []}]",
        "[{\"type\": \"test_type\", \"params\": 13}, "
         "{\"type\": \"x\", \"cache-enable\": {}, \"cache-zones\": []}]",
        "[{\"type\": \"test_type\", \"params\": 13}, "
         "{\"type\": \"x\", \"cache-enable\": null, \"cache-zones\": []}]",
        // Bad type of cache-zones
        "[{\"type\": \"test_type\", \"params\": 13}, "
         "{\"type\": \"x\", \"cache-enable\": true, \"cache-zones\": \"x\"}]",
        "[{\"type\": \"test_type\", \"params\": 13}, "
         "{\"type\": \"x\", \"cache-enable\": true, \"cache-zones\": true}]",
        "[{\"type\": \"test_type\", \"params\": 13}, "
         "{\"type\": \"x\", \"cache-enable\": true, \"cache-zones\": null}]",
        "[{\"type\": \"test_type\", \"params\": 13}, "
         "{\"type\": \"x\", \"cache-enable\": true, \"cache-zones\": 13}]",
        "[{\"type\": \"test_type\", \"params\": 13}, "
         "{\"type\": \"x\", \"cache-enable\": true, \"cache-zones\": {}}]",
        // Some bad inputs for MasterFiles special case

        // It must have the cache enabled
        "[{\"type\": \"test_type\", \"params\": 13}, "
         "{\"type\": \"MasterFiles\", \"cache-enable\": false,"
         "\"params\": {}}]",
        // No cache-zones allowed here
        "[{\"type\": \"test_type\", \"params\": 13}, "
         "{\"type\": \"MasterFiles\", \"cache-enable\": true,"
         "\"param\": {}, \"cache-zones\": []}]",
        // Some bad types of params
        "[{\"type\": \"test_type\", \"params\": 13}, "
         "{\"type\": \"MasterFiles\", \"cache-enable\": false,"
         "\"params\": []}]",
        "[{\"type\": \"test_type\", \"params\": 13}, "
         "{\"type\": \"MasterFiles\", \"cache-enable\": false,"
         "\"params\": 13}]",
        "[{\"type\": \"test_type\", \"params\": 13}, "
         "{\"type\": \"MasterFiles\", \"cache-enable\": false,"
         "\"params\": true}]",
        "[{\"type\": \"test_type\", \"params\": 13}, "
         "{\"type\": \"MasterFiles\", \"cache-enable\": false,"
         "\"params\": null}]",
        "[{\"type\": \"test_type\", \"params\": 13}, "
         "{\"type\": \"MasterFiles\", \"cache-enable\": false,"
         "\"params\": \"x\"}]",
        "[{\"type\": \"test_type\", \"params\": 13}, "
         "{\"type\": \"MasterFiles\", \"cache-enable\": false,"
         "\"params\": {\".\": 13}}]",
        "[{\"type\": \"test_type\", \"params\": 13}, "
         "{\"type\": \"MasterFiles\", \"cache-enable\": false,"
         "\"params\": {\".\": true}}]",
        "[{\"type\": \"test_type\", \"params\": 13}, "
         "{\"type\": \"MasterFiles\", \"cache-enable\": false,"
         "\"params\": {\".\": null}}]",
        "[{\"type\": \"test_type\", \"params\": 13}, "
         "{\"type\": \"MasterFiles\", \"cache-enable\": false,"
         "\"params\": {\".\": []}}]",
        "[{\"type\": \"test_type\", \"params\": 13}, "
         "{\"type\": \"MasterFiles\", \"cache-enable\": false,"
         "\"params\": {\".\": {}}}]",
        NULL
    };
    // Put something inside to see it survives the exception
    list_->configure(config_elem_, true);
    checkDS(0, "test_type", "{}", false);
    for (const char** config(configs); *config; ++config) {
        SCOPED_TRACE(*config);
        ConstElementPtr elem(Element::fromJSON(*config));
        EXPECT_THROW(list_->configure(elem, true),
                     ConfigurableClientList::ConfigurationError);
        // Still untouched
        checkDS(0, "test_type", "{}", false);
        EXPECT_EQ(1, list_->getDataSources().size());
    }
}

// The param thing defaults to null. Cache is not used yet.
TEST_F(ListTest, defaults) {
    const ConstElementPtr elem(Element::fromJSON("["
        "{"
        "   \"type\": \"type1\""
        "}]"));
    list_->configure(elem, true);
    EXPECT_EQ(1, list_->getDataSources().size());
    checkDS(0, "type1", "null", false);
}

// Check we can call the configure multiple times, to change the configuration
TEST_F(ListTest, reconfigure) {
    const ConstElementPtr empty(new ListElement);
    list_->configure(config_elem_, true);
    checkDS(0, "test_type", "{}", false);
    list_->configure(empty, true);
    EXPECT_TRUE(list_->getDataSources().empty());
    list_->configure(config_elem_, true);
    checkDS(0, "test_type", "{}", false);
}

// Make sure the data source error exception from the factory is propagated
TEST_F(ListTest, dataSrcError) {
    const ConstElementPtr elem(Element::fromJSON("["
        "{"
        "   \"type\": \"error\""
        "}]"));
    list_->configure(config_elem_, true);
    checkDS(0, "test_type", "{}", false);
    EXPECT_THROW(list_->configure(elem, true), DataSourceError);
    checkDS(0, "test_type", "{}", false);
}

// Check we can get the cache
TEST_F(ListTest, configureCacheEmpty) {
    const ConstElementPtr elem(Element::fromJSON("["
        "{"
        "   \"type\": \"type1\","
        "   \"cache-enable\": true,"
        "   \"cache-zones\": [],"
        "   \"params\": {}"
        "},"
        "{"
        "   \"type\": \"type2\","
        "   \"cache-enable\": false,"
        "   \"cache-zones\": [],"
        "   \"params\": {}"
        "}]"
    ));
    list_->configure(elem, true);
    EXPECT_EQ(2, list_->getDataSources().size());
    checkDS(0, "type1", "{}", true);
    checkDS(1, "type2", "{}", false);
}

// But no cache if we disallow it globally
TEST_F(ListTest, configureCacheDisabled) {
    const ConstElementPtr elem(Element::fromJSON("["
        "{"
        "   \"type\": \"type1\","
        "   \"cache-enable\": true,"
        "   \"cache-zones\": [],"
        "   \"params\": {}"
        "},"
        "{"
        "   \"type\": \"type2\","
        "   \"cache-enable\": false,"
        "   \"cache-zones\": [],"
        "   \"params\": {}"
        "}]"
    ));
    list_->configure(elem, false);
    EXPECT_EQ(2, list_->getDataSources().size());
    checkDS(0, "type1", "{}", false);
    checkDS(1, "type2", "{}", false);
}

// Put some zones into the cache
TEST_F(ListTest, cacheZones) {
    const ConstElementPtr elem(Element::fromJSON("["
        "{"
        "   \"type\": \"type1\","
        "   \"cache-enable\": true,"
        "   \"cache-zones\": [\"example.org\", \"example.com\"],"
        "   \"params\": [\"example.org\", \"example.com\", \"exmaple.cz\"]"
        "}]"));
    list_->configure(elem, true);
    checkDS(0, "type1", "[\"example.org\", \"example.com\", \"exmaple.cz\"]",
            true);

    const shared_ptr<InMemoryClient> cache(list_->getDataSources()[0].cache_);
    EXPECT_EQ(2, cache->getZoneCount());

    EXPECT_EQ(result::SUCCESS, cache->findZone(Name("example.org")).code);
    EXPECT_EQ(result::SUCCESS, cache->findZone(Name("example.com")).code);
    EXPECT_EQ(result::NOTFOUND, cache->findZone(Name("example.cz")).code);
    EXPECT_EQ(RRClass::IN(),
              cache->findZone(Name("example.org")).zone_finder->getClass());

    // These are cached and answered from the cache
    positiveResult(list_->find(Name("example.com.")), ds_[0],
                   Name("example.com."), true, "com", true);
    positiveResult(list_->find(Name("example.org.")), ds_[0],
                   Name("example.org."), true, "org", true);
    positiveResult(list_->find(Name("sub.example.com.")), ds_[0],
                   Name("example.com."), false, "Subdomain of com", true);
    // For now, the ones not cached are ignored.
    EXPECT_TRUE(negative_result_ == list_->find(Name("example.cz.")));
}

// Check the caching handles misbehaviour from the data source and
// misconfiguration gracefully
TEST_F(ListTest, badCache) {
    list_->configure(config_elem_, true);
    checkDS(0, "test_type", "{}", false);
    // First, the zone is not in the data source
    const ConstElementPtr elem1(Element::fromJSON("["
        "{"
        "   \"type\": \"type1\","
        "   \"cache-enable\": true,"
        "   \"cache-zones\": [\"example.org\"],"
        "   \"params\": []"
        "}]"));
    EXPECT_THROW(list_->configure(elem1, true),
                 ConfigurableClientList::ConfigurationError);
    checkDS(0, "test_type", "{}", false);
    // Now, the zone doesn't give an iterator
    const ConstElementPtr elem2(Element::fromJSON("["
        "{"
        "   \"type\": \"type1\","
        "   \"cache-enable\": true,"
        "   \"cache-zones\": [\"noiter.org\"],"
        "   \"params\": [\"noiter.org\"]"
        "}]"));
    EXPECT_THROW(list_->configure(elem2, true), isc::NotImplemented);
    checkDS(0, "test_type", "{}", false);
    // Now, the zone returns NULL iterator
    const ConstElementPtr elem3(Element::fromJSON("["
        "{"
        "   \"type\": \"type1\","
        "   \"cache-enable\": true,"
        "   \"cache-zones\": [\"null.org\"],"
        "   \"params\": [\"null.org\"]"
        "}]"));
    EXPECT_THROW(list_->configure(elem3, true), isc::Unexpected);
    checkDS(0, "test_type", "{}", false);
    // The autodetection of zones is not enabled
    const ConstElementPtr elem4(Element::fromJSON("["
        "{"
        "   \"type\": \"type1\","
        "   \"cache-enable\": true,"
        "   \"params\": [\"example.org\"]"
        "}]"));
    EXPECT_THROW(list_->configure(elem4, true), isc::NotImplemented);
    checkDS(0, "test_type", "{}", false);
}

TEST_F(ListTest, masterFiles) {
    const ConstElementPtr elem(Element::fromJSON("["
        "{"
        "   \"type\": \"MasterFiles\","
        "   \"cache-enable\": true,"
        "   \"params\": {"
        "       \".\": \"" TEST_DATA_DIR "/root.zone\""
        "   }"
        "}]"));
    list_->configure(elem, true);

    // It has only the cache
    EXPECT_EQ(static_cast<const DataSourceClient*>(NULL),
              list_->getDataSources()[0].data_src_client_);

    // And it can search
    positiveResult(list_->find(Name(".")), ds_[0], Name("."), true, "com",
                   true);

    // If cache is not enabled, nothing is loaded
    list_->configure(elem, false);
    EXPECT_EQ(0, list_->getDataSources().size());
}

TEST_F(ListTest, BadMasterFile) {
    // Configure two zone correctly, and one with the wrong origin
    // (resulting in an out-of-zone data error)
    // Configuration should succeed, and the correct zones should
    // be loaded. Neither the 'bad' origin or the zone it used
    // should be loaded
    const ConstElementPtr elem(Element::fromJSON("["
        "{"
        "   \"type\": \"MasterFiles\","
        "   \"cache-enable\": true,"
        "   \"params\": {"
        "       \"example.com.\": \"" TEST_DATA_DIR "/example.com.flattened\","
        "       \"foo.bar.\": \"" TEST_DATA_DIR "/example.org.nsec3-signed\","
        "       \".\": \"" TEST_DATA_DIR "/root.zone\""
        "   }"
        "}]"));
    list_->configure(elem, true);

    positiveResult(list_->find(Name("example.com."), true), ds_[0],
                   Name("example.com."), true, "example.com", true);
    EXPECT_TRUE(negative_result_ == list_->find(Name("example.org."), true));
    EXPECT_TRUE(negative_result_ == list_->find(Name("foo.bar"), true));
    positiveResult(list_->find(Name(".")), ds_[0], Name("."), true, "root",
                   true);
}

// Test we can reload a zone
TEST_F(ListTest, reloadSuccess) {
    list_->configure(config_elem_zones_, true);
    const Name name("example.org");
    prepareCache(0, name);
    // The cache currently contains a tweaked version of zone, which doesn't
    // have apex NS.  So the lookup should result in NXRRSET.
    EXPECT_EQ(ZoneFinder::NXRRSET,
              list_->find(name).finder_->find(name, RRType::NS())->code);
    // Now reload the full zone. It should be there now.
    EXPECT_EQ(ConfigurableClientList::ZONE_RELOADED, list_->reload(name));
    EXPECT_EQ(ZoneFinder::SUCCESS,
              list_->find(name).finder_->find(name, RRType::NS())->code);
}

// The cache is not enabled. The load should be rejected.
TEST_F(ListTest, reloadNotEnabled) {
    list_->configure(config_elem_zones_, false);
    const Name name("example.org");
    // We put the cache in even when not enabled. This won't confuse the thing.
    prepareCache(0, name);
    // See the reloadSuccess test.  This should result in NXRRSET.
    EXPECT_EQ(ZoneFinder::NXRRSET,
              list_->find(name).finder_->find(name, RRType::NS())->code);
    // Now reload. It should reject it.
    EXPECT_EQ(ConfigurableClientList::CACHE_DISABLED, list_->reload(name));
    // Nothing changed here
    EXPECT_EQ(ZoneFinder::NXRRSET,
              list_->find(name).finder_->find(name, RRType::NS())->code);
}

// Test several cases when the zone does not exist
TEST_F(ListTest, reloadNoSuchZone) {
    list_->configure(config_elem_zones_, true);
    const Name name("example.org");
    // We put the cache in even when not enabled. This won't confuse the
    // reload method, as that one looks at the real state of things, not
    // at the configuration.
    prepareCache(0, Name("example.com"));
    // Not in the data sources
    EXPECT_EQ(ConfigurableClientList::ZONE_NOT_FOUND,
              list_->reload(Name("example.cz")));
    // Not cached
    EXPECT_EQ(ConfigurableClientList::ZONE_NOT_FOUND, list_->reload(name));
    // Partial match
    EXPECT_EQ(ConfigurableClientList::ZONE_NOT_FOUND,
              list_->reload(Name("sub.example.com")));
    // Nothing changed here - these zones don't exist
    EXPECT_EQ(static_cast<isc::datasrc::DataSourceClient*>(NULL),
              list_->find(name).dsrc_client_);
    EXPECT_EQ(static_cast<isc::datasrc::DataSourceClient*>(NULL),
              list_->find(Name("example.cz")).dsrc_client_);
    EXPECT_EQ(static_cast<isc::datasrc::DataSourceClient*>(NULL),
              list_->find(Name("sub.example.com"), true).dsrc_client_);
    // Not reloaded, so NS shouldn't be visible yet.
    EXPECT_EQ(ZoneFinder::NXRRSET,
              list_->find(Name("example.com")).finder_->
              find(Name("example.com"), RRType::NS())->code);
}

// Check we gracefuly throw an exception when a zone disappeared in
// the underlying data source when we want to reload it
TEST_F(ListTest, reloadZoneGone) {
    list_->configure(config_elem_, true);
    const Name name("example.org");
    // We put in a cache for non-existant zone. This emulates being loaded
    // and then the zone disappearing. We prefill the cache, so we can check
    // it.
    prepareCache(0, name);
    // The (cached) zone contains zone's SOA
    EXPECT_EQ(ZoneFinder::SUCCESS,
              list_->find(name).finder_->find(name, RRType::SOA())->code);
    // The zone is not there, so abort the reload.
    EXPECT_THROW(list_->reload(name), DataSourceError);
    // The (cached) zone is not hurt.
    EXPECT_EQ(ZoneFinder::SUCCESS,
              list_->find(name).finder_->find(name, RRType::SOA())->code);
}

// The underlying data source throws. Check we don't modify the state.
TEST_F(ListTest, reloadZoneThrow) {
    list_->configure(config_elem_zones_, true);
    const Name name("noiter.org");
    prepareCache(0, name);
    // The zone contains stuff now
    EXPECT_EQ(ZoneFinder::SUCCESS,
              list_->find(name).finder_->find(name, RRType::SOA())->code);
    // The iterator throws, so abort the reload.
    EXPECT_THROW(list_->reload(name), isc::NotImplemented);
    // The zone is not hurt.
    EXPECT_EQ(ZoneFinder::SUCCESS,
              list_->find(name).finder_->find(name, RRType::SOA())->code);
}

TEST_F(ListTest, reloadNullIterator) {
    list_->configure(config_elem_zones_, true);
    const Name name("null.org");
    prepareCache(0, name);
    // The zone contains stuff now
    EXPECT_EQ(ZoneFinder::SUCCESS,
              list_->find(name).finder_->find(name, RRType::SOA())->code);
    // The iterator throws, so abort the reload.
    EXPECT_THROW(list_->reload(name), isc::Unexpected);
    // The zone is not hurt.
    EXPECT_EQ(ZoneFinder::SUCCESS,
              list_->find(name).finder_->find(name, RRType::SOA())->code);
}

// Test we can reload the master files too (special-cased)
TEST_F(ListTest, reloadMasterFile) {
    const char* const install_cmd = INSTALL_PROG " -c " TEST_DATA_DIR
        "/root.zone " TEST_DATA_BUILDDIR "/root.zone.copied";
    if (system(install_cmd) != 0) {
        // any exception will do, this is failure in test setup, but
        // nice to show the command that fails, and shouldn't be caught
        isc_throw(isc::Exception,
          "Error setting up; command failed: " << install_cmd);
    }

    const ConstElementPtr elem(Element::fromJSON("["
        "{"
        "   \"type\": \"MasterFiles\","
        "   \"cache-enable\": true,"
        "   \"params\": {"
        "       \".\": \"" TEST_DATA_BUILDDIR "/root.zone.copied\""
        "   }"
        "}]"));
    list_->configure(elem, true);
    // Add a record that is not in the zone
    EXPECT_EQ(ZoneFinder::NXDOMAIN,
              list_->find(Name(".")).finder_->find(Name("nosuchdomain"),
                                                   RRType::TXT())->code);
    ofstream f;
    f.open(TEST_DATA_BUILDDIR "/root.zone.copied", ios::out | ios::app);
    f << "nosuchdomain.\t\t3600\tIN\tTXT\ttest" << std::endl;
    f.close();
    // Do the reload.
    EXPECT_EQ(ConfigurableClientList::ZONE_RELOADED, list_->reload(Name(".")));
    // It is here now.
    EXPECT_EQ(ZoneFinder::SUCCESS,
              list_->find(Name(".")).finder_->find(Name("nosuchdomain"),
                                                   RRType::TXT())->code);
}

}
