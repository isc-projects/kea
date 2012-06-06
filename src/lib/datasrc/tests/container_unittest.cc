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

#include <datasrc/container.h>
#include <datasrc/client.h>

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
class TestDS : public DataSourceClient {
public:
    class Finder : public ZoneFinder {
    public:
        Finder(const Name& origin) :
            origin_(origin)
        { }
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
        Name findPreviousName(const Name&) const {
            isc_throw(isc::NotImplemented, "Not implemented");
        }
    private:
        Name origin_;
    };
    // Constructor from a list of zones.
    TestDS(const char* zone_names[]) {
        for (const char** zone(zone_names); *zone; ++ zone) {
            zones.insert(Name(*zone));
        }
    }
    // Constructor from configuration. The list of zones will be empty, but
    // it will keep the configuration inside for further inspection.
    TestDS(const string& type, const ConstElementPtr& configuration) :
        type_(type),
        configuration_(configuration)
    { }
    virtual FindResult findZone(const Name& name) const {
        if (zones.empty()) {
            return (FindResult(result::NOTFOUND, ZoneFinderPtr()));
        }
        set<Name>::const_iterator it(zones.upper_bound(name));
        -- it;
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
class TestedContainer : public ConfigurableContainer {
public:
    TestedContainer(const ConstElementPtr& configuration,
                    bool allow_cache) :
        ConfigurableContainer(configuration, allow_cache)
    { }
    DataSources& dataSources() { return (data_sources_); }
    // Overwrite the containers method to get a data source with given type
    // and configuration. We mock the data source and don't create the
    // container. This is just to avoid some complexity in the tests.
    virtual DataSourcePair getDataSource(const string& type,
                                         const ConstElementPtr& configuration)
    {
        shared_ptr<TestDS> ds(new TestDS(type, configuration));
        // Make sure it is deleted when the test container is deleted.
        to_delete_.push_back(ds);
        return (DataSourcePair(ds.get(), DataSourceClientContainerPtr()));
    }
private:
    // Hold list of data sources created internally, so they are preserved
    // until the end of the test and then deleted.
    vector<shared_ptr<TestDS> > to_delete_;
};
const size_t ds_count = 4;

const char* ds_zones[ds_count][3] = {
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

class ContainerTest : public ::testing::Test {
public:
    ContainerTest() :
        // The empty list corresponds to a container with no elements inside
        container_(new TestedContainer(ConstElementPtr(new ListElement()),
                                       true))
    {
        for (size_t i(0); i < ds_count; ++ i) {
            shared_ptr<TestDS> ds(new TestDS(ds_zones[i]));
            ConfigurableContainer::DataSourceInfo info;
            info.data_src_ = ds.get();
            ds_.push_back(ds);
            ds_info_.push_back(info);
        }
    }
    // Check the positive result is as we expect it.
    void positiveResult(const Container::SearchResult& result,
                        const shared_ptr<TestDS>& dsrc,
                        const Name& name, bool exact,
                        const char* test)
    {
        SCOPED_TRACE(test);
        EXPECT_EQ(dsrc.get(), result.datasrc_);
        ASSERT_NE(ZoneFinderPtr(), result.finder_);
        EXPECT_EQ(name, result.finder_->getOrigin());
        EXPECT_EQ(name.getLabelCount(), result.matched_labels_);
        EXPECT_EQ(exact, result.exact_match_);
    }
    // Configure the container with multiple data sources, according to
    // some configuration. It uses the index as parameter, to be able to
    // loop through the configurations.
    void multiConfiguration(size_t index) {
        container_->dataSources().clear();
        switch (index) {
            case 2:
                container_->dataSources().push_back(ds_info_[2]);
                // The ds3 is empty. We just check that it doesn't confuse
                // us. Fall through to the case 0.
            case 0:
                container_->dataSources().push_back(ds_info_[0]);
                container_->dataSources().push_back(ds_info_[1]);
                break;
            case 1:
                // The other order
                container_->dataSources().push_back(ds_info_[1]);
                container_->dataSources().push_back(ds_info_[0]);
                break;
            case 3:
                container_->dataSources().push_back(ds_info_[1]);
                container_->dataSources().push_back(ds_info_[0]);
                // It is the same as 2, but we take from the first one.
                // The first one to match is the correct one.
                container_->dataSources().push_back(ds_info_[3]);
                break;
            default:
                FAIL() << "Unknown configuration index " << index;
        }
    }
    void checkDS(size_t index, const string& type, const string& params) {
        ASSERT_GT(container_->dataSources().size(), index);
        TestDS* ds(dynamic_cast<TestDS*>(
            container_->dataSources()[index].data_src_));
        // Comparing with NULL does not work
        ASSERT_TRUE(ds);
        EXPECT_EQ(type, ds->type_);
        EXPECT_TRUE(Element::fromJSON(params)->equals(*ds->configuration_));
    }
    shared_ptr<TestedContainer> container_;
    const Container::SearchResult negativeResult_;
    vector<shared_ptr<TestDS> > ds_;
    vector<ConfigurableContainer::DataSourceInfo> ds_info_;
};

// Test the test itself
TEST_F(ContainerTest, selfTest) {
    EXPECT_EQ(result::SUCCESS, ds_[0]->findZone(Name("example.org")).code);
    EXPECT_EQ(result::PARTIALMATCH,
              ds_[0]->findZone(Name("sub.example.org")).code);
    EXPECT_EQ(result::NOTFOUND, ds_[0]->findZone(Name("org")).code);
    EXPECT_EQ(result::NOTFOUND, ds_[1]->findZone(Name("example.org")).code);
}

// Test the container we create with empty configuration is, in fact, empty
TEST_F(ContainerTest, emptyContainer) {
    EXPECT_TRUE(container_->dataSources().empty());
}

// Check the values returned by a search on an empty container. It should be
// a negative answer (nothing found) no matter if we want an exact or inexact
// match.
TEST_F(ContainerTest, emptySearch) {
    // No matter what we try, we don't get an answer.
    EXPECT_EQ(negativeResult_, container_->search(Name("example.org"), false,
                                                 false));
    EXPECT_EQ(negativeResult_, container_->search(Name("example.org"), false,
                                                 true));
    EXPECT_EQ(negativeResult_, container_->search(Name("example.org"), true,
                                                 false));
    EXPECT_EQ(negativeResult_, container_->search(Name("example.org"), true,
                                                 true));
}

// Put a single data source inside the container and check it can find an
// exact match if there's one.
TEST_F(ContainerTest, singleDSExactMatch) {
    container_->dataSources().push_back(ds_info_[0]);
    // This zone is not there
    EXPECT_EQ(negativeResult_, container_->search(Name("org."), true));
    // But this one is, so check it.
    positiveResult(container_->search(Name("example.org"), true),
                   ds_[0], Name("example.org"), true, "Exact match");
    // When asking for a sub zone of a zone there, we get nothing
    // (we want exact match, this would be partial one)
    EXPECT_EQ(negativeResult_, container_->search(Name("sub.example.org."),
                                                  true));
}

// When asking for a partial match, we get all that the exact one, but more.
TEST_F(ContainerTest, singleDSBestMatch) {
    container_->dataSources().push_back(ds_info_[0]);
    // This zone is not there
    EXPECT_EQ(negativeResult_, container_->search(Name("org.")));
    // But this one is, so check it.
    positiveResult(container_->search(Name("example.org")),
                   ds_[0], Name("example.org"), true, "Exact match");
    // When asking for a sub zone of a zone there, we get nothing
    // (we want exact match, this would be partial one)
    positiveResult(container_->search(Name("sub.example.org.")),
                   ds_[0], Name("example.org"), false, "Subdomain match");
}

const char* test_names[] = {
    "Sub second",
    "Sub first",
    "With empty",
    "With a duplicity"
};

TEST_F(ContainerTest, multiExactMatch) {
    // Run through all the multi-configurations
    for (size_t i(0); i < 4; ++ i) {
        SCOPED_TRACE(test_names[i]);
        multiConfiguration(i);
        // Something that is nowhere there
        EXPECT_EQ(negativeResult_, container_->search(Name("org."), true));
        // This one is there exactly.
        positiveResult(container_->search(Name("example.org"), true),
                       ds_[0], Name("example.org"), true, "Exact match");
        // This one too, but in a different data source.
        positiveResult(container_->search(Name("sub.example.org."), true),
                       ds_[1], Name("sub.example.org"), true,
                       "Subdomain match");
        // But this one is in neither data source.
        EXPECT_EQ(negativeResult_, container_->search(Name("sub.example.com."),
                                                      true));
    }
}

TEST_F(ContainerTest, multiBestMatch) {
    // Run through all the multi-configurations
    for (size_t i(0); i < 4; ++ i) {
        SCOPED_TRACE(test_names[i]);
        multiConfiguration(i);
        // Something that is nowhere there
        EXPECT_EQ(negativeResult_, container_->search(Name("org.")));
        // This one is there exactly.
        positiveResult(container_->search(Name("example.org")),
                       ds_[0], Name("example.org"), true, "Exact match");
        // This one too, but in a different data source.
        positiveResult(container_->search(Name("sub.example.org.")),
                       ds_[1], Name("sub.example.org"), true,
                       "Subdomain match");
        // But this one is in neither data source. But it is a subdomain
        // of one of the zones in the first data source.
        positiveResult(container_->search(Name("sub.example.com.")),
                       ds_[0], Name("example.com."), false,
                       "Subdomain in com");
    }
}

// Check the configuration is empty when the list is empty
TEST_F(ContainerTest, configureEmpty) {
    ConstElementPtr elem(new ListElement);
    container_.reset(new TestedContainer(elem, true));
    EXPECT_TRUE(container_->dataSources().empty());
}

// Check we can get multiple data sources and they are in the right order.
TEST_F(ContainerTest, configureMulti) {
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
    container_.reset(new TestedContainer(elem, true));
    EXPECT_EQ(2, container_->dataSources().size());
    checkDS(0, "type1", "{}");
    checkDS(1, "type2", "{}");
}

// Check we can pass whatever we want to the params
TEST_F(ContainerTest, configureParams) {
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
        container_.reset(new TestedContainer(elem, true));
        EXPECT_EQ(1, container_->dataSources().size());
        checkDS(0, "t", *param);
    }
}

TEST_F(ContainerTest, wrongConfig) {
    const char* configs[] = {
        // A lot of stuff missing from there
        "[{}]",
        // Some bad types completely
        "{}",
        "true",
        "42",
        "null",
        "[true]",
        "[[]]",
        "[42]",
        // Bad type of type
        "[{\"type\": 42}]",
        "[{\"type\": true}]",
        "[{\"type\": null}]",
        "[{\"type\": []}]",
        "[{\"type\": {}}]",
        // TODO: Once cache is supported, add some invalid cache values
        NULL
    };
    for (const char** config(configs); *config; ++config) {
        SCOPED_TRACE(*config);
        ConstElementPtr elem(Element::fromJSON(*config));
        EXPECT_THROW(TestedContainer(elem, true),
                     ConfigurableContainer::ConfigurationError);
    }
}

// The param thing defaults to null. Cache is not used yet.
TEST_F(ContainerTest, defaults) {
    ConstElementPtr elem(Element::fromJSON("["
        "{"
        "   \"type\": \"type1\""
        "}]"));
    EXPECT_EQ(1, container_->dataSources().size());
    checkDS(0, "type1", "null");
}

}
