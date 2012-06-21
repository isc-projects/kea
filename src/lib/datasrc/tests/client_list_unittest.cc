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
#include <datasrc/data_source.h>

#include <dns/rrclass.h>

#include <gtest/gtest.h>

#include <set>

using namespace isc::datasrc;
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
    // Constructor from a list of zones.
    MockDataSourceClient(const char* zone_names[]) {
        for (const char** zone(zone_names); *zone; ++zone) {
            zones.insert(Name(*zone));
        }
    }
    // Constructor from configuration. The list of zones will be empty, but
    // it will keep the configuration inside for further inspection.
    MockDataSourceClient(const string& type,
                         const ConstElementPtr& configuration) :
        type_(type),
        configuration_(configuration)
    {}
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
    const string type_;
    const ConstElementPtr configuration_;
private:
    set<Name> zones;
};


// The test version is the same as the normal version. We, however, add
// some methods to dig directly in the internals, for the tests.
class TestedList : public ConfigurableClientList {
public:
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
        // The empty list corresponds to a list with no elements inside
        list_(new TestedList()),
        config_elem_(Element::fromJSON("["
            "{"
            "   \"type\": \"test_type\","
            "   \"cache\": \"off\","
            "   \"params\": {}"
            "}]"))
    {
        for (size_t i(0); i < ds_count; ++ i) {
            shared_ptr<MockDataSourceClient>
                ds(new MockDataSourceClient(ds_zones[i]));
            ds_.push_back(ds);
            ds_info_.push_back(ConfigurableClientList::DataSourceInfo(ds.get(),
                DataSourceClientContainerPtr()));
        }
    }
    // Check the positive result is as we expect it.
    void positiveResult(const ClientList::FindResult& result,
                        const shared_ptr<MockDataSourceClient>& dsrc,
                        const Name& name, bool exact,
                        const char* test)
    {
        SCOPED_TRACE(test);
        EXPECT_EQ(dsrc.get(), result.dsrc_client_);
        ASSERT_NE(ZoneFinderPtr(), result.finder_);
        EXPECT_EQ(name, result.finder_->getOrigin());
        EXPECT_EQ(exact, result.exact_match_);
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
    void checkDS(size_t index, const string& type, const string& params) const
    {
        ASSERT_GT(list_->getDataSources().size(), index);
        MockDataSourceClient* ds(dynamic_cast<MockDataSourceClient*>(
            list_->getDataSources()[index].data_src_client_));

        // Comparing with NULL does not work
        ASSERT_NE(ds, static_cast<const MockDataSourceClient*>(NULL));
        EXPECT_EQ(type, ds->type_);
        EXPECT_TRUE(Element::fromJSON(params)->equals(*ds->configuration_));
    }
    shared_ptr<TestedList> list_;
    const ClientList::FindResult negativeResult_;
    vector<shared_ptr<MockDataSourceClient> > ds_;
    vector<ConfigurableClientList::DataSourceInfo> ds_info_;
    const ConstElementPtr config_elem_;
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
    EXPECT_TRUE(negativeResult_ == list_->find(Name("example.org"), false,
                                               false));
    EXPECT_TRUE(negativeResult_ == list_->find(Name("example.org"), false,
                                               true));
    EXPECT_TRUE(negativeResult_ == list_->find(Name("example.org"), true,
                                               false));
    EXPECT_TRUE(negativeResult_ == list_->find(Name("example.org"), true,
                                               true));
}

// Put a single data source inside the list and check it can find an
// exact match if there's one.
TEST_F(ListTest, singleDSExactMatch) {
    list_->getDataSources().push_back(ds_info_[0]);
    // This zone is not there
    EXPECT_TRUE(negativeResult_ == list_->find(Name("org."), true));
    // But this one is, so check it.
    positiveResult(list_->find(Name("example.org"), true), ds_[0],
                   Name("example.org"), true, "Exact match");
    // When asking for a sub zone of a zone there, we get nothing
    // (we want exact match, this would be partial one)
    EXPECT_TRUE(negativeResult_ == list_->find(Name("sub.example.org."),
                                               true));
}

// When asking for a partial match, we get all that the exact one, but more.
TEST_F(ListTest, singleDSBestMatch) {
    list_->getDataSources().push_back(ds_info_[0]);
    // This zone is not there
    EXPECT_TRUE(negativeResult_ == list_->find(Name("org.")));
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
        EXPECT_TRUE(negativeResult_ == list_->find(Name("org."), true));
        // This one is there exactly.
        positiveResult(list_->find(Name("example.org"), true), ds_[0],
                       Name("example.org"), true, "Exact match");
        // This one too, but in a different data source.
        positiveResult(list_->find(Name("sub.example.org."), true), ds_[1],
                       Name("sub.example.org"), true, "Subdomain match");
        // But this one is in neither data source.
        EXPECT_TRUE(negativeResult_ ==
                    list_->find(Name("sub.example.com."), true));
    }
}

TEST_F(ListTest, multiBestMatch) {
    // Run through all the multi-configurations
    for (size_t i(0); i < 4; ++ i) {
        SCOPED_TRACE(test_names[i]);
        multiConfiguration(i);
        // Something that is nowhere there
        EXPECT_TRUE(negativeResult_ == list_->find(Name("org.")));
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
    ConstElementPtr elem(new ListElement);
    list_->configure(*elem, true);
    EXPECT_TRUE(list_->getDataSources().empty());
}

// Check we can get multiple data sources and they are in the right order.
TEST_F(ListTest, configureMulti) {
    ConstElementPtr elem(Element::fromJSON("["
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
    list_->configure(*elem, true);
    EXPECT_EQ(2, list_->getDataSources().size());
    checkDS(0, "type1", "{}");
    checkDS(1, "type2", "{}");
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
        list_->configure(*elem, true);
        EXPECT_EQ(1, list_->getDataSources().size());
        checkDS(0, "t", *param);
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
        // TODO: Once cache is supported, add some invalid cache values
        NULL
    };
    // Put something inside to see it survives the exception
    list_->configure(*config_elem_, true);
    checkDS(0, "test_type", "{}");
    for (const char** config(configs); *config; ++config) {
        SCOPED_TRACE(*config);
        ConstElementPtr elem(Element::fromJSON(*config));
        EXPECT_THROW(list_->configure(*elem, true),
                     ConfigurableClientList::ConfigurationError);
        // Still untouched
        checkDS(0, "test_type", "{}");
        EXPECT_EQ(1, list_->getDataSources().size());
    }
}

// The param thing defaults to null. Cache is not used yet.
TEST_F(ListTest, defaults) {
    ConstElementPtr elem(Element::fromJSON("["
        "{"
        "   \"type\": \"type1\""
        "}]"));
    list_->configure(*elem, true);
    EXPECT_EQ(1, list_->getDataSources().size());
    checkDS(0, "type1", "null");
}

// Check we can call the configure multiple times, to change the configuration
TEST_F(ListTest, reconfigure) {
    ConstElementPtr empty(new ListElement);
    list_->configure(*config_elem_, true);
    checkDS(0, "test_type", "{}");
    list_->configure(*empty, true);
    EXPECT_TRUE(list_->getDataSources().empty());
    list_->configure(*config_elem_, true);
    checkDS(0, "test_type", "{}");
}

// Make sure the data source error exception from the factory is propagated
TEST_F(ListTest, dataSrcError) {
    ConstElementPtr elem(Element::fromJSON("["
        "{"
        "   \"type\": \"error\""
        "}]"));
    list_->configure(*config_elem_, true);
    checkDS(0, "test_type", "{}");
    EXPECT_THROW(list_->configure(*elem, true), DataSourceError);
    checkDS(0, "test_type", "{}");
}

}
