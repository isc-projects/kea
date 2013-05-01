// Copyright (C) 2013  Internet Systems Consortium, Inc. ("ISC")
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

#include <datasrc/zone_table_accessor_cache.h>
#include <datasrc/cache_config.h>
#include <datasrc/tests/mock_client.h>

#include <exceptions/exceptions.h>

#include <cc/data.h>

#include <dns/name.h>

#include <gtest/gtest.h>

using namespace isc::dns;
using namespace isc::datasrc;
using namespace isc::datasrc::internal;
using isc::data::Element;
using isc::datasrc::unittest::MockDataSourceClient;

namespace {

// This test checks the abstract ZoneTableAccessor interface using
// ZoneTableAccessorCache instances, thereby testing the top level interface
// and the derived class behavior.  If ZoneTableAccessorCache becomes more
// complicated we may have to separate some test cases into dedicated test
// fixture.
class ZoneTableAccessorTest : public ::testing::Test {
protected:
    ZoneTableAccessorTest() :
        // The paths of the zone files are dummy and don't even exist,
        // but it doesn't matter in this test.
        config_spec_(Element::fromJSON(
                         "{\"cache-enable\": true,"
                         " \"params\": "
                         "  {\"example.com\": \"/example-com.zone\","
                         "   \"example.org\": \"/example-org.zone\"}"
                         "}")),
        cache_config_("MasterFiles", NULL, *config_spec_, true),
        accessor_(cache_config_)
    {}

private:
    const isc::data::ConstElementPtr config_spec_;
    const CacheConfig cache_config_;
protected:
    ZoneTableAccessorCache accessor_;
};

TEST_F(ZoneTableAccessorTest, iteratorFromCache) {
    // Confirm basic iterator behavior.
    ZoneTableAccessor::IteratorPtr it = accessor_.getIterator();
    ASSERT_TRUE(it);
    EXPECT_FALSE(it->isLast());
    EXPECT_EQ(0, it->getCurrent().index); // index is always 0 for this version
    EXPECT_EQ(Name("example.com"), it->getCurrent().origin);

    it->next();
    EXPECT_FALSE(it->isLast());
    EXPECT_EQ(0, it->getCurrent().index);
    EXPECT_EQ(Name("example.org"), it->getCurrent().origin);

    it->next();                 // shouldn't cause disruption
    EXPECT_TRUE(it->isLast());

    // getCurrent() and next() will be rejected once iterator reaches the end
    EXPECT_THROW(it->getCurrent(), isc::InvalidOperation);
    EXPECT_THROW(it->next(), isc::InvalidOperation);
}

TEST_F(ZoneTableAccessorTest, emptyTable) {
    // Empty zone table is possible, while mostly useless.
    const CacheConfig empty_config(
        "MasterFiles", NULL, *Element::fromJSON(
            "{\"cache-enable\": true, \"params\": {}}"), true);
    ZoneTableAccessorCache accessor(empty_config);
    ZoneTableAccessor::IteratorPtr it = accessor.getIterator();
    ASSERT_TRUE(it);
    EXPECT_TRUE(it->isLast());
    EXPECT_THROW(it->getCurrent(), isc::InvalidOperation);
    EXPECT_THROW(it->next(), isc::InvalidOperation);
}

TEST_F(ZoneTableAccessorTest, disabledTable) {
    // Zone table based on disabled cache is effectively empty.
    const char* zones[] = { "example.org.", "example.com.", NULL };
    MockDataSourceClient mock_client(zones);
    const CacheConfig mock_config(
        "mock", &mock_client, *Element::fromJSON(
            "{\"cache-enable\": false,"
            " \"cache-zones\": [\"example.com\", \"example.org\"]}"), true);
    ZoneTableAccessorCache accessor(mock_config);
    ZoneTableAccessor::IteratorPtr it = accessor.getIterator();
    ASSERT_TRUE(it);
    EXPECT_TRUE(it->isLast());
    EXPECT_THROW(it->getCurrent(), isc::InvalidOperation);
    EXPECT_THROW(it->next(), isc::InvalidOperation);
}

}
