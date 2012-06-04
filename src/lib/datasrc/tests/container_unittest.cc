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

// The test version is the same as the normal version. We, however, add
// some methods to dig directly in the internals, for the tests.
class TestedContainer : public ConfigurableContainer {
public:
    TestedContainer(const ConstElementPtr& configuration,
                    bool allow_cache) :
        ConfigurableContainer(configuration, allow_cache)
    { }
    DataSources& dataSources() { return (data_sources_); }
};

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
    TestDS(const char* zone_names[]) {
        for (const char** zone(zone_names); *zone; ++ zone) {
            zones.insert(Name(*zone));
        }
    }
    virtual FindResult findZone(const Name& name) const {
        set<Name>::const_iterator it(zones.lower_bound(name));
        if (it == zones.end()) {
            return (FindResult(result::NOTFOUND, ZoneFinderPtr()));
        } else {
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
private:
    set<Name> zones;
};

const char* ds1_zones[] = {
    "example.org.",
    "example.com."
};

class ContainerTest : public ::testing::Test {
public:
    ContainerTest() :
        // The empty list corresponds to a container with no elements inside
        container_(new TestedContainer(ConstElementPtr(new ListElement()),
                                       true)),
        ds1_(new TestDS(ds1_zones))
    {
        ds1_info_.data_src_ = ds1_;
    }
    // Check the positive result is as we expect it.
    void positiveResult(const Container::SearchResult& result,
                        const shared_ptr<TestDS>& dsrc,
                        const Name& name, bool exact,
                        const char* test)
    {
        SCOPED_TRACE(test);
        EXPECT_EQ(dsrc, result.datasrc_);
        ASSERT_NE(ZoneFinderPtr(), result.finder_);
        EXPECT_EQ(name, result.finder_->getOrigin());
        EXPECT_EQ(name.getLabelCount(), result.matched_labels_);
        EXPECT_EQ(exact, result.exact_match_);
    }
    shared_ptr<TestedContainer> container_;
    const Container::SearchResult negativeResult_;
    shared_ptr<TestDS> ds1_;
    ConfigurableContainer::DataSourceInfo ds1_info_;
};

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
    container_->dataSources().push_back(ds1_info_);
    // This zone is not there
    EXPECT_EQ(negativeResult_, container_->search(Name("org."), true));
    // But this one is, so check it.
    positiveResult(container_->search(Name("example.org"), true),
                   ds1_, Name("example.org"), true, "Exact match");
    // When asking for a sub zone of a zone there, we get nothing
    // (we want exact match, this would be partial one)
    EXPECT_EQ(negativeResult_, container_->search(Name("sub.example.org."),
                                                  true));
}

// When asking for a partial match, we get all that the exact one, but more.
TEST_F(ContainerTest, singleDSBestMatch) {
    container_->dataSources().push_back(ds1_info_);
    // This zone is not there
    EXPECT_EQ(negativeResult_, container_->search(Name("org.")));
    // But this one is, so check it.
    positiveResult(container_->search(Name("example.org")),
                   ds1_, Name("example.org"), true, "Exact match");
    // When asking for a sub zone of a zone there, we get nothing
    // (we want exact match, this would be partial one)
    positiveResult(container_->search(Name("sub.example.org.")),
                   ds1_, Name("example.org"), false, "Subdomain match");
}

}
