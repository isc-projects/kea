// Copyright (C) 2012-2013  Internet Systems Consortium, Inc. ("ISC")
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

#include <datasrc/client_list.h>
#include <datasrc/client.h>
#include <datasrc/factory.h>
#include <datasrc/cache_config.h>
#include <datasrc/zone_iterator.h>
#include <datasrc/exceptions.h>
#include <datasrc/memory/memory_client.h>
#include <datasrc/memory/zone_table_segment.h>
#include <datasrc/memory/zone_finder.h>
#include <datasrc/memory/zone_writer.h>

#include <datasrc/tests/mock_client.h>

#include <dns/rrclass.h>
#include <dns/rrttl.h>
#include <dns/rdataclass.h>

#include <gtest/gtest.h>

#include <boost/format.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/interprocess/file_mapping.hpp>

#include <set>
#include <fstream>

using namespace isc::datasrc;
using isc::datasrc::unittest::MockDataSourceClient;
using isc::datasrc::memory::InMemoryClient;
using isc::datasrc::memory::ZoneTableSegment;
using isc::datasrc::memory::InMemoryZoneFinder;
using namespace isc::data;
using namespace isc::dns;
// note: don't use 'using [namespace]' for shared_ptr.  It would conflict with
// C++ std:: definitions.
using namespace std;

namespace {

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
        if (type == "library_error") {
            isc_throw(DataSourceLibraryError,
                      "The library error data source type");
        }
        if (type == "MasterFiles") {
            return (DataSourcePair(0, DataSourceClientContainerPtr()));
        }
        boost::shared_ptr<MockDataSourceClient>
            ds(new MockDataSourceClient(type, configuration));
        // Make sure it is deleted when the test list is deleted.
        to_delete_.push_back(ds);
        return (DataSourcePair(ds.get(), DataSourceClientContainerPtr()));
    }
private:
    // Hold list of data sources created internally, so they are preserved
    // until the end of the test and then deleted.
    vector<boost::shared_ptr<MockDataSourceClient> > to_delete_;
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

class SegmentType {
public:
    virtual ~SegmentType() {}
    virtual ConstElementPtr getCacheConfig(bool enabled, const Name& zone)
        const = 0;
    virtual void reset(ConfigurableClientList& list,
                       const std::string& datasrc_name,
                       ZoneTableSegment::MemorySegmentOpenMode mode,
                       ConstElementPtr config_params) = 0;
    virtual std::string getType() = 0;
};

class ListTest : public ::testing::TestWithParam<SegmentType*> {
public:
    ListTest() :
        rrclass_(RRClass::IN()),
        // The empty list corresponds to a list with no elements inside
        list_(new TestedList(rrclass_)),
        negative_result_(),
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
            "}]"))
    {
        for (size_t i(0); i < ds_count; ++ i) {
            boost::shared_ptr<MockDataSourceClient>
                ds(new MockDataSourceClient(ds_zones[i]));
            ds_.push_back(ds);
            ds_info_.push_back(ConfigurableClientList::DataSourceInfo(
                                   ds.get(), DataSourceClientContainerPtr(),
                                   boost::shared_ptr<internal::CacheConfig>(),
                                   rrclass_, ""));
        }
    }

    ~ListTest() {
        ds_info_.clear();
        for (size_t i(0); i < ds_count; ++ i) {
            ds_[i].reset();
        }
        ds_.clear();

        for (size_t i(0); i < ds_count; ++ i) {
            boost::interprocess::file_mapping::remove(
                getMappedFilename(i).c_str());
        }
    }

    static std::string getMappedFilename(size_t index) {
         return (boost::str(boost::format(TEST_DATA_BUILDDIR "/test%d.mapped")
                            % index));
    }

    // Install a "fake" cached zone using a temporary underlying data source
    // client.  If 'enabled' is set to false, emulate a disabled cache, in
    // which case there will be no data in memory.
    void prepareCache(size_t index, const Name& zone, bool enabled = true) {
        ConfigurableClientList::DataSourceInfo& dsrc_info =
                list_->getDataSources()[index];
        MockDataSourceClient* mock_client =
            static_cast<MockDataSourceClient*>(dsrc_info.data_src_client_);

        // Disable some default features of the mock to distinguish the
        // temporary case from normal case.
        mock_client->disableA();
        mock_client->disableBadIterator();

        // Build new cache config to load the specified zone, and replace
        // the data source info with the new config.
        ConstElementPtr cache_conf_elem =
            GetParam()->getCacheConfig(enabled, zone);
        boost::shared_ptr<internal::CacheConfig> cache_conf(
            new internal::CacheConfig("mock", mock_client, *cache_conf_elem,
                                      true));
        dsrc_info = ConfigurableClientList::DataSourceInfo(
            dsrc_info.data_src_client_,
            dsrc_info.container_,
            cache_conf, rrclass_, dsrc_info.name_);

        // Load the data into the zone table.
        if (enabled) {
            const ConstElementPtr config_ztable_segment(
                Element::fromJSON("{\"mapped-file\": \"" +
                                  getMappedFilename(index) +
                                  "\"}"));

            GetParam()->reset(*list_, dsrc_info.name_,
                              memory::ZoneTableSegment::CREATE,
                              config_ztable_segment);

            const ConfigurableClientList::ZoneWriterPair result =
                list_->getCachedZoneWriter(zone, false, dsrc_info.name_);

            ASSERT_EQ(ConfigurableClientList::ZONE_SUCCESS, result.first);
            result.second->load();
            result.second->install();
            // not absolutely necessary, but just in case
            result.second->cleanup();

            GetParam()->reset(*list_, dsrc_info.name_,
                              memory::ZoneTableSegment::READ_WRITE,
                              config_ztable_segment);
        }

        // On completion of load revert to the previous state of underlying
        // data source.
        mock_client->enableA();
        mock_client->enableBadIterator();
    }
    // Check the positive result is as we expect it.
    void positiveResult(const ClientList::FindResult& result,
                        const boost::shared_ptr<MockDataSourceClient>& dsrc,
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
        EXPECT_NE(boost::shared_ptr<ClientList::FindResult::LifeKeeper>(),
                  result.life_keeper_);
        if (from_cache) {
            EXPECT_NE(boost::shared_ptr<InMemoryZoneFinder>(),
                      boost::dynamic_pointer_cast<InMemoryZoneFinder>(
                          result.finder_)) << "Finder is not from cache";
            EXPECT_TRUE(NULL !=
                        dynamic_cast<InMemoryClient*>(result.dsrc_client_));
        } else {
            EXPECT_EQ(dsrc.get(), result.dsrc_client_);
        }
    }

    // check the result with empty (broken) zones.  Right now this can only
    // happen for in-memory caches.
    void emptyResult(const ClientList::FindResult& result, bool exact,
                     const char* trace_txt)
    {
        SCOPED_TRACE(trace_txt);
        ASSERT_FALSE(result.finder_);
        EXPECT_EQ(exact, result.exact_match_);
        EXPECT_TRUE(dynamic_cast<InMemoryClient*>(result.dsrc_client_));
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
                  boost::shared_ptr<InMemoryClient>());
    }
    ConfigurableClientList::CacheStatus doReload(
        const Name& origin, const string& datasrc_name = "");
    void accessorIterate(const ConstZoneTableAccessorPtr& accessor,
        int numZones, const string& zoneName);

    const RRClass rrclass_;
    boost::shared_ptr<TestedList> list_;
    const ClientList::FindResult negative_result_;
    vector<boost::shared_ptr<MockDataSourceClient> > ds_;
    vector<ConfigurableClientList::DataSourceInfo> ds_info_;
    const ConstElementPtr config_elem_, config_elem_zones_;
};

class LocalSegmentType : public SegmentType {
public:
    virtual ConstElementPtr getCacheConfig(bool enabled, const Name& zone)
        const
    {
        return (Element::fromJSON("{\"type\": \"mock\","
                                  " \"cache-enable\": " +
                                  string(enabled ? "true," : "false,") +
                                  " \"cache-zones\": "
                                  "   [\"" + zone.toText() + "\"]}"));
    }
    virtual void reset(ConfigurableClientList&, const std::string&,
                       ZoneTableSegment::MemorySegmentOpenMode,
                       ConstElementPtr) {
        // We must not call reset on local ZoneTableSegments.
    }
    virtual std::string getType() {
        return ("local");
    }
};

LocalSegmentType local_segment_type;

INSTANTIATE_TEST_CASE_P(ListTestLocal, ListTest,
                        ::testing::Values(static_cast<SegmentType*>(
                                              &local_segment_type)));

#ifdef USE_SHARED_MEMORY

class MappedSegmentType : public SegmentType {
public:
    virtual ConstElementPtr getCacheConfig(bool enabled, const Name& zone)
        const
    {
        return (Element::fromJSON("{\"type\": \"mock\","
                                  " \"cache-enable\": " +
                                  string(enabled ? "true," : "false,") +
                                  " \"cache-type\": \"mapped\"," +
                                  " \"cache-zones\": "
                                  "   [\"" + zone.toText() + "\"]}"));
    }
    virtual void reset(ConfigurableClientList& list,
                       const std::string& datasrc_name,
                       ZoneTableSegment::MemorySegmentOpenMode mode,
                       ConstElementPtr config_params) {
        EXPECT_TRUE(list.resetMemorySegment(datasrc_name, mode,
                                            config_params));
    }
    virtual std::string getType() {
        return ("mapped");
    }
};

MappedSegmentType mapped_segment_type;

INSTANTIATE_TEST_CASE_P(ListTestMapped, ListTest,
                        ::testing::Values(static_cast<SegmentType*>(
                                              &mapped_segment_type)));

#endif

// Calling reset on empty list finds no data and returns false.
TEST_P(ListTest, emptyReset) {
    EXPECT_FALSE(list_->resetMemorySegment("Something",
                                           memory::ZoneTableSegment::CREATE,
                                           Element::create()));
}

// Test the test itself
TEST_P(ListTest, selfTest) {
    EXPECT_EQ(result::SUCCESS, ds_[0]->findZone(Name("example.org")).code);
    EXPECT_EQ(result::PARTIALMATCH,
              ds_[0]->findZone(Name("sub.example.org")).code);
    EXPECT_EQ(result::NOTFOUND, ds_[0]->findZone(Name("org")).code);
    EXPECT_EQ(result::NOTFOUND, ds_[1]->findZone(Name("example.org")).code);
    EXPECT_EQ(result::NOTFOUND, ds_[0]->findZone(Name("aaa")).code);
    EXPECT_EQ(result::NOTFOUND, ds_[0]->findZone(Name("zzz")).code);
    // Nothing to keep alive here.
    EXPECT_EQ(boost::shared_ptr<ClientList::FindResult::LifeKeeper>(),
                  negative_result_.life_keeper_);
}

// Test the list we create with empty configuration is, in fact, empty
TEST_P(ListTest, emptyList) {
    EXPECT_TRUE(list_->getDataSources().empty());
}

// Check the values returned by a find on an empty list. It should be
// a negative answer (nothing found) no matter if we want an exact or inexact
// match.
TEST_P(ListTest, emptySearch) {
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
TEST_P(ListTest, singleDSExactMatch) {
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
TEST_P(ListTest, singleDSBestMatch) {
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

TEST_P(ListTest, multiExactMatch) {
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

TEST_P(ListTest, multiBestMatch) {
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
TEST_P(ListTest, configureEmpty) {
    const ConstElementPtr elem(new ListElement);
    list_->configure(elem, true);
    EXPECT_TRUE(list_->getDataSources().empty());
    // Check the exact configuration is preserved
    EXPECT_EQ(elem, list_->getConfiguration());
}

// Check we can get multiple data sources and they are in the right order.
TEST_P(ListTest, configureMulti) {
    const ConstElementPtr elem(Element::fromJSON("["
        "{"
        "   \"type\": \"type1\","
        "   \"cache-enable\": false,"
        "   \"params\": {}"
        "},"
        "{"
        "   \"type\": \"type2\","
        "   \"cache-enable\": false,"
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
TEST_P(ListTest, configureParams) {
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
            "   \"cache-enable\": false,"
            "   \"params\": ") + *param +
            "}]"));
        list_->configure(elem, true);
        EXPECT_EQ(1, list_->getDataSources().size());
        checkDS(0, "t", *param, false);
    }
}

TEST_P(ListTest, status) {
    EXPECT_TRUE(list_->getStatus().empty());
    const ConstElementPtr elem(Element::fromJSON("["
        "{"
        "   \"type\": \"type1\","
        "   \"cache-enable\": false,"
        "   \"params\": {}"
        "},"
        "{"
        "   \"type\": \"type2\","
        "   \"cache-enable\": true,"
        "   \"cache-zones\": [],"
        "   \"name\": \"Test name\","
        "   \"params\": {}"
        "}]"
    ));
    list_->configure(elem, true);
    const vector<DataSourceStatus> statuses(list_->getStatus());
    ASSERT_EQ(2, statuses.size());
    EXPECT_EQ("type1", statuses[0].getName());
    EXPECT_EQ(SEGMENT_UNUSED, statuses[0].getSegmentState());
    EXPECT_THROW(statuses[0].getSegmentType(), isc::InvalidOperation);
    EXPECT_EQ("Test name", statuses[1].getName());
    EXPECT_EQ(SEGMENT_INUSE, statuses[1].getSegmentState());
    EXPECT_EQ("local", statuses[1].getSegmentType());
}

TEST_P(ListTest, wrongConfig) {
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
TEST_P(ListTest, defaults) {
    const ConstElementPtr elem(Element::fromJSON("["
        "{"
        "   \"type\": \"type1\""
        "}]"));
    list_->configure(elem, true);
    EXPECT_EQ(1, list_->getDataSources().size());
    checkDS(0, "type1", "null", false);
}

// Check we can call the configure multiple times, to change the configuration
TEST_P(ListTest, reconfigure) {
    const ConstElementPtr empty(new ListElement);
    list_->configure(config_elem_, true);
    checkDS(0, "test_type", "{}", false);
    list_->configure(empty, true);
    EXPECT_TRUE(list_->getDataSources().empty());
    list_->configure(config_elem_, true);
    checkDS(0, "test_type", "{}", false);
}

// Make sure the data source error exception from the factory is propagated
TEST_P(ListTest, dataSrcError) {
    const ConstElementPtr elem(Element::fromJSON("["
        "{"
        "   \"type\": \"error\""
        "}]"));
    list_->configure(config_elem_, true);
    checkDS(0, "test_type", "{}", false);
    EXPECT_THROW(list_->configure(elem, true), DataSourceError);
    checkDS(0, "test_type", "{}", false);
}

// In case of library errors, the rest of the data sources should be
// unaffected.
TEST_P(ListTest, dataSrcLibraryError) {
    EXPECT_EQ(0, list_->getDataSources().size());
    const ConstElementPtr elem(Element::fromJSON("["
        "{"
        "   \"type\": \"type1\","
        "   \"cache-enable\": false,"
        "   \"params\": {}"
        "},"
        "{"
        "   \"type\": \"library_error\","
        "   \"cache-enable\": false,"
        "   \"params\": {}"
        "},"
        "{"
        "   \"type\": \"type2\","
        "   \"cache-enable\": false,"
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

// Check we can get the cache
TEST_P(ListTest, configureCacheEmpty) {
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
TEST_P(ListTest, configureCacheDisabled) {
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
TEST_P(ListTest, cacheZones) {
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

    const boost::shared_ptr<InMemoryClient> cache(
        list_->getDataSources()[0].cache_);
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
TEST_P(ListTest, badCache) {
    list_->configure(config_elem_, true);
    checkDS(0, "test_type", "{}", false);
    // First, the zone is not in the data source. configure() should still
    // succeed, and the existence zone should be cached.
    const ConstElementPtr elem1(Element::fromJSON("["
        "{"
        "   \"type\": \"test_type\","
        "   \"cache-enable\": true,"
        "   \"cache-zones\": [\"example.org\", \"example.com\"],"
        "   \"params\": [\"example.org\"]"
        "}]"));
    list_->configure(elem1, true); // shouldn't cause disruption
    checkDS(0, "test_type", "[\"example.org\"]", true);
    const boost::shared_ptr<InMemoryClient> cache(
        list_->getDataSources()[0].cache_);
    EXPECT_EQ(1, cache->getZoneCount());
    EXPECT_EQ(result::SUCCESS, cache->findZone(Name("example.org")).code);
    // Now, the zone doesn't give an iterator
    const ConstElementPtr elem2(Element::fromJSON("["
        "{"
        "   \"type\": \"type1\","
        "   \"cache-enable\": true,"
        "   \"cache-zones\": [\"noiter.org\"],"
        "   \"params\": [\"noiter.org\"]"
        "}]"));
    EXPECT_THROW(list_->configure(elem2, true), isc::NotImplemented);
    checkDS(0, "test_type", "[\"example.org\"]", true);
    // Now, the zone returns NULL iterator
    const ConstElementPtr elem3(Element::fromJSON("["
        "{"
        "   \"type\": \"type1\","
        "   \"cache-enable\": true,"
        "   \"cache-zones\": [\"null.org\"],"
        "   \"params\": [\"null.org\"]"
        "}]"));
    EXPECT_THROW(list_->configure(elem3, true), isc::Unexpected);
    checkDS(0, "test_type", "[\"example.org\"]", true);
    // The autodetection of zones is not enabled
    const ConstElementPtr elem4(Element::fromJSON("["
        "{"
        "   \"type\": \"type1\","
        "   \"cache-enable\": true,"
        "   \"params\": [\"example.org\"]"
        "}]"));
    EXPECT_THROW(list_->configure(elem4, true), isc::NotImplemented);
    checkDS(0, "test_type", "[\"example.org\"]", true);
}

// This test relies on the property of mapped type of cache.
TEST_P(ListTest,
#ifdef USE_SHARED_MEMORY
       cacheInNonWritableSegment
#else
       DISABLED_cacheInNonWritableSegment
#endif
    )
{
    // Initializing data source with non writable zone table memory segment
    // is possible.  Loading is just postponed
    const ConstElementPtr elem(Element::fromJSON("["
        "{"
        "   \"type\": \"test_type\","
        "   \"cache-enable\": true,"
        "   \"cache-type\": \"mapped\","
        "   \"cache-zones\": [\"example.org\"],"
        "   \"params\": [\"example.org\"]"
        "}]"));
    list_->configure(elem, true); // no disruption
    checkDS(0, "test_type", "[\"example.org\"]", true);
    const boost::shared_ptr<InMemoryClient> cache(
        list_->getDataSources()[0].cache_);

    // Likewise, reload attempt will fail.
    EXPECT_EQ(ConfigurableClientList::CACHE_NOT_WRITABLE,
              doReload(Name("example.org")));
}

TEST_P(ListTest, masterFiles) {
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
    positiveResult(list_->find(Name(".")), ds_[0], Name("."), true, "root",
                   true);

    // If cache is not enabled, nothing is loaded
    list_->configure(elem, false);
    EXPECT_EQ(0, list_->getDataSources().size());
}

// Test the names are set correctly and collission is detected.
TEST_P(ListTest, names) {
    // Explicit name
    const ConstElementPtr elem1(Element::fromJSON("["
        "{"
        "   \"type\": \"MasterFiles\","
        "   \"cache-enable\": true,"
        "   \"params\": {"
        "       \".\": \"" TEST_DATA_DIR "/root.zone\""
        "   },"
        "   \"name\": \"Whatever\""
        "}]"));
    list_->configure(elem1, true);
    EXPECT_EQ("Whatever", list_->getDataSources()[0].name_);

    // Default name
    const ConstElementPtr elem2(Element::fromJSON("["
        "{"
        "   \"type\": \"MasterFiles\","
        "   \"cache-enable\": true,"
        "   \"params\": {"
        "       \".\": \"" TEST_DATA_DIR "/root.zone\""
        "   }"
        "}]"));
    list_->configure(elem2, true);
    EXPECT_EQ("MasterFiles", list_->getDataSources()[0].name_);

    // Collission
    const ConstElementPtr elem3(Element::fromJSON("["
        "{"
        "   \"type\": \"MasterFiles\","
        "   \"cache-enable\": true,"
        "   \"params\": {"
        "       \".\": \"" TEST_DATA_DIR "/root.zone\""
        "   }"
        "},"
        "{"
        "   \"type\": \"MasterFiles\","
        "   \"cache-enable\": true,"
        "   \"params\": {"
        "       \".\": \"" TEST_DATA_DIR "/root.zone\""
        "   },"
        "   \"name\": \"MasterFiles\""
        "}]"));
    EXPECT_THROW(list_->configure(elem3, true),
                 ConfigurableClientList::ConfigurationError);
}

TEST_P(ListTest, BadMasterFile) {
    // Configuration should succeed, and the good zones in the list
    // below should be loaded.  Bad zones won't be "loaded" in its usual sense,
    // but are still recognized with conceptual "empty" data.
    const ConstElementPtr elem(Element::fromJSON("["
        "{"
        "   \"type\": \"MasterFiles\","
        "   \"cache-enable\": true,"
        "   \"params\": {"

        // good zone
        "       \"example.com.\": \"" TEST_DATA_DIR "/example.com.flattened\","

        // bad zone (empty file)
        "       \"example.net.\": \"" TEST_DATA_DIR "/example.net-empty\","

        // bad zone (data doesn't validate: see the file for details)
        "       \"example.edu.\": \"" TEST_DATA_DIR "/example.edu-broken\","

        // bad zone (file doesn't exist)
        "       \"example.info.\": \"" TEST_DATA_DIR "/example.info-nonexist\","

        // bad zone (data doesn't match the zone name)
        "       \"foo.bar.\": \"" TEST_DATA_DIR "/example.org.nsec3-signed\","

        // good zone
        "       \".\": \"" TEST_DATA_DIR "/root.zone\""

        "   }"
        "}]"));

    EXPECT_NO_THROW({
        // This should not throw even if there are any zone loading
        // errors.
        list_->configure(elem, true);
    });

    positiveResult(list_->find(Name("example.com."), true), ds_[0],
                   Name("example.com."), true, "example.com", true);
    // Bad cases: should result in "empty zone", whether the match is exact
    // or partial.
    emptyResult(list_->find(Name("foo.bar"), true), true, "foo.bar");
    emptyResult(list_->find(Name("example.net."), true), true, "example.net");
    emptyResult(list_->find(Name("example.edu."), true), true, "example.edu");
    emptyResult(list_->find(Name("example.info."), true), true,
                "example.info");
    emptyResult(list_->find(Name("www.example.edu."), false), false,
                "example.edu, partial");
    positiveResult(list_->find(Name(".")), ds_[0], Name("."), true, "root",
                   true);
    // This one simply doesn't exist.
    EXPECT_TRUE(list_->find(Name("example.org."), true) == negative_result_);
}

ConfigurableClientList::CacheStatus
ListTest::doReload(const Name& origin, const string& datasrc_name) {
    ConfigurableClientList::ZoneWriterPair
        result(list_->getCachedZoneWriter(origin, false, datasrc_name));
    if (result.first == ConfigurableClientList::ZONE_SUCCESS) {
        // Can't use ASSERT_NE here, it would want to return(), which
        // it can't in non-void function.
        if (result.second) {
            result.second->load();
            result.second->install();
            result.second->cleanup();
        } else {
            ADD_FAILURE() << "getCachedZoneWriter returned ZONE_SUCCESS, "
                "but the writer is NULL";
        }
    } else {
        EXPECT_EQ(static_cast<memory::ZoneWriter*>(NULL), result.second.get());
    }
    return (result.first);
}

// Check that ZoneWriter doesn't throw when asked not to
TEST_P(ListTest, checkZoneWriterCatchesExceptions) {
    const ConstElementPtr config_elem_zones_(Element::fromJSON("["
        "{"
        "   \"type\": \"MasterFiles\","
        "   \"params\": {"
        "       \"example.edu\": \"" TEST_DATA_DIR "example.edu-broken\""
        "    },"
        "   \"cache-enable\": true"
        "}]"));

    list_->configure(config_elem_zones_, true);
    ConfigurableClientList::ZoneWriterPair
        result(list_->getCachedZoneWriter(Name("example.edu"), true));
    ASSERT_EQ(ConfigurableClientList::ZONE_SUCCESS, result.first);
    ASSERT_TRUE(result.second);

    std::string error_msg;
    // Because of the way we called getCachedZoneWriter() with
    // catch_load_error=true, the following should not throw and must
    // return an error message in error_msg.
    EXPECT_NO_THROW(result.second->load(&error_msg));
    EXPECT_FALSE(error_msg.empty());
    result.second->cleanup();
}

// Check that ZoneWriter throws when asked to
TEST_P(ListTest, checkZoneWriterThrows) {
    const ConstElementPtr config_elem_zones_(Element::fromJSON("["
        "{"
        "   \"type\": \"MasterFiles\","
        "   \"params\": {"
        "       \"example.edu\": \"" TEST_DATA_DIR "example.edu-broken\""
        "    },"
        "   \"cache-enable\": true"
        "}]"));

    list_->configure(config_elem_zones_, true);
    ConfigurableClientList::ZoneWriterPair
        result(list_->getCachedZoneWriter(Name("example.edu"), false));
    ASSERT_EQ(ConfigurableClientList::ZONE_SUCCESS, result.first);
    ASSERT_TRUE(result.second);

    std::string error_msg;
    // Because of the way we called getCachedZoneWriter() with
    // catch_load_error=false, the following should throw and must not
    // modify error_msg.
    EXPECT_THROW(result.second->load(&error_msg),
                 isc::datasrc::ZoneLoaderException);
    EXPECT_TRUE(error_msg.empty());
    result.second->cleanup();
}

// Test we can reload a zone
TEST_P(ListTest, reloadSuccess) {
    list_->configure(config_elem_zones_, true);

    const vector<DataSourceStatus> statii_before(list_->getStatus());
    ASSERT_EQ(1, statii_before.size());
    EXPECT_EQ("test_type", statii_before[0].getName());
    EXPECT_EQ(SEGMENT_UNUSED, statii_before[0].getSegmentState());
    EXPECT_THROW(statii_before[0].getSegmentType(), isc::InvalidOperation);

    const Name name("example.org");
    prepareCache(0, name);
    // The cache currently contains a tweaked version of zone, which
    // doesn't have "tstzonedata" A record.  So the lookup should result
    // in NXDOMAIN.
    EXPECT_EQ(ZoneFinder::NXDOMAIN,
              list_->find(name).finder_->
                  find(Name("tstzonedata").concatenate(name),
                       RRType::A())->code);
    // Now reload the full zone. It should be there now.
    EXPECT_EQ(ConfigurableClientList::ZONE_SUCCESS, doReload(name));
    EXPECT_EQ(ZoneFinder::SUCCESS,
              list_->find(name).finder_->
                  find(Name("tstzonedata").concatenate(name),
                       RRType::A())->code);

    const vector<DataSourceStatus> statii_after(list_->getStatus());
    ASSERT_EQ(1, statii_after.size());
    EXPECT_EQ("test_type", statii_after[0].getName());
    EXPECT_EQ(SEGMENT_INUSE, statii_after[0].getSegmentState());
    EXPECT_EQ(GetParam()->getType(), statii_after[0].getSegmentType());
}

// The cache is not enabled. The load should be rejected.
//
// FIXME: This test is broken by #2853 and needs to be fixed or
// removed. Please see #2991 for details.
TEST_P(ListTest, DISABLED_reloadNotAllowed) {
    list_->configure(config_elem_zones_, false);
    const Name name("example.org");
    // We put the cache in even when not enabled. This won't confuse the thing.
    prepareCache(0, name);
    // See the reloadSuccess test.  This should result in NXDOMAIN.
    EXPECT_EQ(ZoneFinder::NXDOMAIN,
              list_->find(name).finder_->
                  find(Name("tstzonedata").concatenate(name),
                       RRType::A())->code);
    // Now reload. It should reject it.
    EXPECT_EQ(ConfigurableClientList::CACHE_DISABLED, doReload(name));
    // Nothing changed here
    EXPECT_EQ(ZoneFinder::NXDOMAIN,
              list_->find(name).finder_->
                  find(Name("tstzonedata").concatenate(name),
                       RRType::A())->code);
}

// Similar to the previous case, but the cache is disabled in config.
TEST_P(ListTest, reloadNotEnabled) {
    list_->configure(config_elem_zones_, true);
    const Name name("example.org");
    // We put the cache, actually disabling it.
    prepareCache(0, name, false);
    // In this case we cannot really look up due to the limitation of
    // the mock implementation.  We only check reload fails.
    EXPECT_EQ(ConfigurableClientList::ZONE_NOT_CACHED, doReload(name));
}

// Test several cases when the zone does not exist
TEST_P(ListTest, reloadNoSuchZone) {
    list_->configure(config_elem_zones_, true);
    const Name name("example.org");
    // We put the cache in even when not enabled. This won't confuse the
    // reload method, as that one looks at the real state of things, not
    // at the configuration.
    prepareCache(0, Name("example.com"));
    // Not in the data sources
    EXPECT_EQ(ConfigurableClientList::ZONE_NOT_FOUND,
              doReload(Name("exmaple.cz")));
    // If it's not configured to be cached, it won't be reloaded.
    EXPECT_EQ(ConfigurableClientList::ZONE_NOT_CACHED, doReload(name));
    // Partial match
    EXPECT_EQ(ConfigurableClientList::ZONE_NOT_FOUND,
              doReload(Name("sub.example.com")));
    // Nothing changed here - these zones don't exist
    EXPECT_EQ(static_cast<isc::datasrc::DataSourceClient*>(NULL),
              list_->find(name).dsrc_client_);
    EXPECT_EQ(static_cast<isc::datasrc::DataSourceClient*>(NULL),
              list_->find(Name("example.cz")).dsrc_client_);
    EXPECT_EQ(static_cast<isc::datasrc::DataSourceClient*>(NULL),
              list_->find(Name("sub.example.com"), true).dsrc_client_);
    // Not reloaded, so A record shouldn't be visible yet.
    EXPECT_EQ(ZoneFinder::NXDOMAIN,
              list_->find(Name("example.com")).finder_->
                  find(Name("tstzonedata.example.com"),
                       RRType::A())->code);
}

// Check we gracefully reject reloading (i.e. no exception) when a zone
// disappeared in the underlying data source when we want to reload it
TEST_P(ListTest, reloadZoneGone) {
    list_->configure(config_elem_zones_, true);
    const Name name("example.org");
    // We put in a cache for non-existent zone. This emulates being loaded
    // and then the zone disappearing. We prefill the cache, so we can check
    // it.
    prepareCache(0, name);
    // The (cached) zone contains zone's SOA
    EXPECT_EQ(ZoneFinder::SUCCESS,
              list_->find(name).finder_->find(name, RRType::SOA())->code);
    // Remove the zone from the data source.
    static_cast<MockDataSourceClient*>(
        list_->getDataSources()[0].data_src_client_)->eraseZone(name);

    // The zone is not there, so reload doesn't take place.
    EXPECT_EQ(ConfigurableClientList::ZONE_NOT_FOUND, doReload(name));
    // The (cached) zone is not hurt.
    EXPECT_EQ(ZoneFinder::SUCCESS,
              list_->find(name).finder_->find(name, RRType::SOA())->code);
}

TEST_P(ListTest, reloadNewZone) {
    // Test the case where a zone to be cached originally doesn't exist
    // in the underlying data source and is added later.  reload() will
    // succeed once it's available in the data source.
    const ConstElementPtr elem(Element::fromJSON("["
        "{"
        "   \"type\": \"test_type\","
        "   \"cache-enable\": true,"
        "   \"cache-zones\": [\"example.org\", \"example.com\"],"
        "   \"params\": [\"example.org\"]"
        "}]"));
    list_->configure(elem, true);
    checkDS(0, "test_type", "[\"example.org\"]", true); // no example.com

    // We can't reload it either
    EXPECT_EQ(ConfigurableClientList::ZONE_NOT_FOUND,
              doReload(Name("example.com")));

    // If we add the zone, we can now reload it
    EXPECT_TRUE(static_cast<MockDataSourceClient*>(
                    list_->getDataSources()[0].data_src_client_)->
                insertZone(Name("example.com")));
    EXPECT_EQ(ConfigurableClientList::ZONE_SUCCESS,
              doReload(Name("example.com")));
}

// The underlying data source throws. Check we don't modify the state.
TEST_P(ListTest, reloadZoneThrow) {
    list_->configure(config_elem_zones_, true);
    const Name name("noiter.org");
    prepareCache(0, name);
    // The zone contains stuff now
    EXPECT_EQ(ZoneFinder::SUCCESS,
              list_->find(name).finder_->find(name, RRType::SOA())->code);
    // The iterator throws, so abort the reload.
    EXPECT_THROW(doReload(name), isc::NotImplemented);
    // The zone is not hurt.
    EXPECT_EQ(ZoneFinder::SUCCESS,
              list_->find(name).finder_->find(name, RRType::SOA())->code);
}

TEST_P(ListTest, reloadNullIterator) {
    list_->configure(config_elem_zones_, true);
    const Name name("null.org");
    prepareCache(0, name);
    // The zone contains stuff now
    EXPECT_EQ(ZoneFinder::SUCCESS,
              list_->find(name).finder_->find(name, RRType::SOA())->code);
    // The iterator throws, so abort the reload.
    EXPECT_THROW(doReload(name), isc::Unexpected);
    // The zone is not hurt.
    EXPECT_EQ(ZoneFinder::SUCCESS,
              list_->find(name).finder_->find(name, RRType::SOA())->code);
}

// Test we can reload the master files too (special-cased)
TEST_P(ListTest, reloadMasterFile) {
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
    EXPECT_EQ(ConfigurableClientList::ZONE_SUCCESS, doReload(Name(".")));
    // It is here now.
    EXPECT_EQ(ZoneFinder::SUCCESS,
              list_->find(Name(".")).finder_->find(Name("nosuchdomain"),
                                                   RRType::TXT())->code);
}

TEST_P(ListTest, reloadByDataSourceName) {
    // We use three data sources (and their clients).  2nd and 3rd have
    // the same name of the zones.
    const ConstElementPtr config_elem = Element::fromJSON(
        "[{\"type\": \"test_type1\", \"params\": [\"example.org\"]},"
        " {\"type\": \"test_type2\", \"params\": [\"example.com\"]},"
        " {\"type\": \"test_type3\", \"params\": [\"example.com\"]}]");
    list_->configure(config_elem, true);
    // Prepare in-memory cache for the 1st and 2nd data sources.
    prepareCache(0, Name("example.org"));
    prepareCache(1, Name("example.com"));

    // Normal case: both zone name and data source name matches.
    // See the reloadSuccess test about the NXDOMAIN/SUCCESS checks.
    EXPECT_EQ(ZoneFinder::NXDOMAIN,
              list_->find(Name("tstzonedata.example.com")).finder_->
              find(Name("tstzonedata.example.com"), RRType::A())->code);
    EXPECT_EQ(ConfigurableClientList::ZONE_SUCCESS,
              doReload(Name("example.com"), "test_type2"));
    EXPECT_EQ(ZoneFinder::SUCCESS,
              list_->find(Name("tstzonedata.example.com")).finder_->
              find(Name("tstzonedata.example.com"), RRType::A())->code);

    // The specified zone exists in the first entry of the list, but a
    // different data source name is specified (in which the specified zone
    // doesn't exist), so reloading should fail, and the cache status of the
    // first data source shouldn't change.
    EXPECT_EQ(ZoneFinder::NXDOMAIN,
              list_->find(Name("tstzonedata.example.org")).finder_->
              find(Name("tstzonedata.example.org"), RRType::A())->code);
    EXPECT_EQ(ConfigurableClientList::ZONE_NOT_FOUND,
              doReload(Name("example.org"), "test_type2"));
    EXPECT_EQ(ZoneFinder::NXDOMAIN,
              list_->find(Name("tstzonedata.example.org")).finder_->
              find(Name("tstzonedata.example.org"), RRType::A())->code);

    // Likewise, if a specific data source is given, normal name matching
    // isn't suppressed and the 3rd data source will be used.  There cache
    // is disabled, so reload should fail due to "not cached".
    EXPECT_EQ(ConfigurableClientList::ZONE_NOT_CACHED,
              doReload(Name("example.com"), "test_type3"));

    // specified name of data source doesn't exist.
    EXPECT_EQ(ConfigurableClientList::DATASRC_NOT_FOUND,
              doReload(Name("example.org"), "test_type4"));
}

// This takes the accessor provided by getZoneTableAccessor(), iterates
// through the table, and verifies that the expected number of zones are
// present, as well as the named zone.
void
ListTest::accessorIterate(const ConstZoneTableAccessorPtr& accessor,
                          int numZones, const string& zoneName="")
{
    // Confirm basic iterator behavior.
    ASSERT_TRUE(accessor);
    ZoneTableAccessor::IteratorPtr it = accessor->getIterator();
    ASSERT_TRUE(it);
    // Iterator does not guarantee ordering, so we look for the target
    // name anywhere in the table.
    bool found = false;
    int i;
    for (i = 0; !it->isLast(); ++i, it->next()) {
        if (Name(zoneName) == it->getCurrent().origin) {
            found = true;
        }
    }
    EXPECT_EQ(i, numZones);
    if (numZones > 0) {
        EXPECT_TRUE(found);
    }
}

TEST_F(ListTest, zoneTableAccessor) {
    // empty configuration
    const ConstElementPtr elem(new ListElement);
    list_->configure(elem, true);
    // null pointer treated as false
    EXPECT_FALSE(list_->getZoneTableAccessor("", true));

    // empty list; expect it to return an empty list
    list_->configure(config_elem_, true);
    ConstZoneTableAccessorPtr z(list_->getZoneTableAccessor("", true));
    accessorIterate(z, 0);

    const ConstElementPtr elem2(Element::fromJSON("["
        "{"
        "   \"type\": \"type1\","
        "   \"cache-enable\": true,"
        "   \"cache-zones\": [\"example.com\"],"
        "   \"params\": [\"example.com\"]"
        "},"
        "{"
        "   \"type\": \"type2\","
        "   \"cache-enable\": false,"
        "   \"params\": [\"example.org\"]"
        "},"
        "{"
        "   \"type\": \"type3\","
        "   \"cache-enable\": true,"
        "   \"cache-zones\": [\"example.net\", \"example.info\"],"
        "   \"params\": [\"example.net\", \"example.info\"]"
        "}]"));

    // allow_cache = false
    // ask for a non-existent zone table, expect null
    list_->configure(elem2, false);
    EXPECT_FALSE(list_->getZoneTableAccessor("bogus", true));
    // ask for any zone table, expect an empty list
    z = list_->getZoneTableAccessor("", true);
    accessorIterate(z, 0);

    // allow_cache = true, use_cache = false
    list_->configure(elem2, true);
    EXPECT_THROW(list_->getZoneTableAccessor("", false), isc::NotImplemented);
    EXPECT_THROW(list_->getZoneTableAccessor("type1", false),
                 isc::NotImplemented);

    // datasrc not found, returns NULL pointer
    EXPECT_FALSE(list_->getZoneTableAccessor("bogus", true));

    // return first datasrc
    z = list_->getZoneTableAccessor("", true);
    accessorIterate(z, 1, "example.com");

    // datasrc has cache disabled, returns accessor to empty list
    z = list_->getZoneTableAccessor("type2", true);
    accessorIterate(z, 0);

    // search by name
    z = list_->getZoneTableAccessor("type3", true);
    accessorIterate(z, 2, "example.net");
}

// Check the status holds data
TEST(DataSourceStatus, status) {
    const DataSourceStatus status("Test", SEGMENT_INUSE, "local");
    EXPECT_EQ("Test", status.getName());
    EXPECT_EQ(SEGMENT_INUSE, status.getSegmentState());
    EXPECT_EQ("local", status.getSegmentType());
    const DataSourceStatus status_unused("Unused");
    EXPECT_EQ("Unused", status_unused.getName());
    EXPECT_EQ(SEGMENT_UNUSED, status_unused.getSegmentState());
    EXPECT_THROW(status_unused.getSegmentType(), isc::InvalidOperation);
}

}
