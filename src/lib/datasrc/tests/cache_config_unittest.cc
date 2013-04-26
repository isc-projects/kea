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

#include <datasrc/cache_config.h>
#include <datasrc/exceptions.h>
#include <datasrc/memory/load_action.h>
#include <datasrc/memory/zone_data.h>
#include <datasrc/tests/mock_client.h>

#include <cc/data.h>
#include <util/memory_segment_local.h>
#include <dns/name.h>
#include <dns/rrclass.h>

#include <gtest/gtest.h>

#include <iterator>             // for std::distance

using namespace isc::datasrc;
using namespace isc::data;
using namespace isc::dns;
using isc::datasrc::unittest::MockDataSourceClient;
using isc::datasrc::internal::CacheConfig;
using isc::datasrc::internal::CacheConfigError;
using isc::datasrc::memory::LoadAction;
using isc::datasrc::memory::ZoneData;

namespace {

const char* zones[] = {
    "example.org.",
    "example.com.",
    "null.org",                 // test for bad iterator case
    NULL
};

class CacheConfigTest : public ::testing::Test {
protected:
    CacheConfigTest() :
        mock_client_(zones),
        master_config_(Element::fromJSON(
                           "{\"cache-enable\": true,"
                           " \"params\": "
                           "  {\".\": \"" TEST_DATA_DIR "/root.zone\"}"
                           "}")),
        mock_config_(Element::fromJSON("{\"cache-enable\": true,"
                                       " \"cache-zones\": [\".\"]}"))
    {}

    virtual void TearDown() {
        EXPECT_TRUE(msgmt_.allMemoryDeallocated());
    }

    MockDataSourceClient mock_client_;
    const ConstElementPtr master_config_; // valid config for MasterFiles
    const ConstElementPtr mock_config_; // valid config for MasterFiles
    isc::util::MemorySegmentLocal msgmt_;
};

size_t
countZones(const CacheConfig& cache_config) {
    return (std::distance(cache_config.begin(), cache_config.end()));
}

TEST_F(CacheConfigTest, constructMasterFiles) {
    // A simple case: configuring a MasterFiles table with a single zone
    const CacheConfig cache_conf("MasterFiles", 0, *master_config_, true);
    EXPECT_EQ(1, countZones(cache_conf));

    // With multiple zones.  Note that the constructor doesn't check if the
    // file exists, so they can be anything.
    const ConstElementPtr config_elem_multi(
        Element::fromJSON("{\"cache-enable\": true,"
                          " \"params\": "
                          "{\"example.com\": \"file1\","
                          " \"example.org\": \"file2\","
                          " \"example.info\": \"file3\"}"
                          "}"));
    const CacheConfig cache_conf2("MasterFiles", 0, *config_elem_multi, true);
    EXPECT_EQ(3, countZones(cache_conf2));

    // A bit unusual, but acceptable case: empty parameters, so no zones.
    const CacheConfig cache_conf3("MasterFiles", 0,
                                  *Element::fromJSON("{\"cache-enable\": true,"
                                                     " \"params\": {}}"),
                                  true);
    EXPECT_EQ(0, countZones(cache_conf3));
}

TEST_F(CacheConfigTest, badConstructMasterFiles) {
    // no "params"
    EXPECT_THROW(CacheConfig("MasterFiles", 0,
                             *Element::fromJSON("{\"cache-enable\": true}"),
                             true),
                 isc::data::TypeError);

    // no "cache-enable"
    EXPECT_THROW(CacheConfig("MasterFiles", 0,
                             *Element::fromJSON("{\"params\": {}}"), true),
                 CacheConfigError);
    // cache disabled for MasterFiles
    EXPECT_THROW(CacheConfig("MasterFiles", 0,
                             *Element::fromJSON("{\"cache-enable\": false,"
                                                " \"params\": {}}"), true),
                 CacheConfigError);
    // cache enabled but not "allowed"
    EXPECT_THROW(CacheConfig("MasterFiles", 0,
                             *Element::fromJSON("{\"cache-enable\": false,"
                                                " \"params\": {}}"), false),
                 CacheConfigError);
    // type error for cache-enable
    EXPECT_THROW(CacheConfig("MasterFiles", 0,
                             *Element::fromJSON("{\"cache-enable\": 1,"
                                                " \"params\": {}}"), true),
                 isc::data::TypeError);

    // "params" is not a map
    EXPECT_THROW(CacheConfig("MasterFiles", 0,
                             *Element::fromJSON("{\"cache-enable\": true,"
                                                " \"params\": []}"), true),
                 isc::data::TypeError);

    // bogus zone name
    const ConstElementPtr bad_config(Element::fromJSON(
                                         "{\"cache-enable\": true,"
                                         " \"params\": "
                                         "{\"bad..name\": \"file1\"}}"));
    EXPECT_THROW(CacheConfig("MasterFiles", 0, *bad_config, true),
                 isc::dns::EmptyLabel);

    // file name is not a string
    const ConstElementPtr bad_config2(Element::fromJSON(
                                          "{\"cache-enable\": true,"
                                          " \"params\": {\".\": 1}}"));
    EXPECT_THROW(CacheConfig("MasterFiles", 0, *bad_config2, true),
                 isc::data::TypeError);

    // Specify data source client (must be null for MasterFiles)
    EXPECT_THROW(CacheConfig("MasterFiles", &mock_client_,
                             *Element::fromJSON("{\"cache-enable\": true,"
                                                " \"params\": {}}"), true),
                 isc::InvalidParameter);
}

TEST_F(CacheConfigTest, getLoadActionWithMasterFiles) {
    uint8_t labels_buf[LabelSequence::MAX_SERIALIZED_LENGTH];

    const CacheConfig cache_conf("MasterFiles", 0, *master_config_, true);

    // Check getLoadAction.  Since it returns a mere functor, we can only
    // check the behavior by actually calling it.  For the purpose of this
    // test, it should suffice if we confirm the call succeeds and shows
    // some reasonably valid behavior (we'll check the origin name for that).
    LoadAction action = cache_conf.getLoadAction(RRClass::IN(),
                                                 Name::ROOT_NAME());
    ZoneData* zone_data = action(msgmt_);
    ASSERT_TRUE(zone_data);
    EXPECT_EQ(".", zone_data->getOriginNode()->
              getAbsoluteLabels(labels_buf).toText());
    ZoneData::destroy(msgmt_, zone_data, RRClass::IN());

    // If the specified zone name is not configured to be cached,
    // getLoadAction returns empty (false) functor.
    EXPECT_FALSE(cache_conf.getLoadAction(RRClass::IN(), Name("example.com")));
}

TEST_F(CacheConfigTest, constructWithMock) {
    // Performing equivalent set of tests as constructMasterFiles

    // Configure with a single zone.
    const CacheConfig cache_conf("mock", &mock_client_, *mock_config_, true);
    EXPECT_EQ(1, countZones(cache_conf));
    EXPECT_TRUE(cache_conf.isEnabled());

    // Configure with multiple zones.
    const ConstElementPtr config_elem_multi(
        Element::fromJSON("{\"cache-enable\": true,"
                          " \"cache-zones\": "
                          "[\"example.com\", \"example.org\",\"example.info\"]"
                          "}"));
    const CacheConfig cache_conf2("mock", &mock_client_, *config_elem_multi,
                                  true);
    EXPECT_EQ(3, countZones(cache_conf2));

    // Empty
    const CacheConfig cache_conf3(
        "mock", &mock_client_,
        *Element::fromJSON("{\"cache-enable\": true,"
                           " \"cache-zones\": []}"), true);
    EXPECT_EQ(0, countZones(cache_conf3));

    // disabled.  value of cache-zones are ignored.
    const ConstElementPtr config_elem_disabled(
        Element::fromJSON("{\"cache-enable\": false,"
                          " \"cache-zones\": [\"example.com\"]}"));
    EXPECT_FALSE(CacheConfig("mock", &mock_client_, *config_elem_disabled,
                             true).isEnabled());
    // enabled but not "allowed".  same effect.
    EXPECT_FALSE(CacheConfig("mock", &mock_client_,
                             *Element::fromJSON("{\"cache-enable\": true,"
                                                " \"cache-zones\": []}"),
                             false).isEnabled());
}

TEST_F(CacheConfigTest, badConstructWithMock) {
    // no "cache-zones" (may become valid in future, but for now "notimp")
    EXPECT_THROW(CacheConfig("mock", &mock_client_,
                             *Element::fromJSON("{\"cache-enable\": true}"),
                             true),
                 isc::NotImplemented);

    // "cache-zones" is not a list
    EXPECT_THROW(CacheConfig("mock", &mock_client_,
                             *Element::fromJSON("{\"cache-enable\": true,"
                                                " \"cache-zones\": {}}"),
                             true),
                 isc::data::TypeError);

    // "cache-zone" entry is not a string
    EXPECT_THROW(CacheConfig("mock", &mock_client_,
                             *Element::fromJSON("{\"cache-enable\": true,"
                                                " \"cache-zones\": [1]}"),
                             true),
                 isc::data::TypeError);

    // bogus zone name
    const ConstElementPtr bad_config(Element::fromJSON(
                                         "{\"cache-enable\": true,"
                                         " \"cache-zones\": [\"bad..\"]}"));
    EXPECT_THROW(CacheConfig("mock", &mock_client_, *bad_config, true),
                 isc::dns::EmptyLabel);

    // duplicate zone name (note that comparison is case insensitive)
    const ConstElementPtr dup_config(Element::fromJSON(
                                         "{\"cache-enable\": true,"
                                         " \"cache-zones\": "
                                         " [\"example\", \"EXAMPLE\"]}"));
    EXPECT_THROW(CacheConfig("mock", &mock_client_, *dup_config, true),
                 CacheConfigError);

    // datasrc is null
    EXPECT_THROW(CacheConfig("mock", 0, *mock_config_, true),
                 isc::InvalidParameter);
}

TEST_F(CacheConfigTest, getLoadActionWithMock) {
    uint8_t labels_buf[LabelSequence::MAX_SERIALIZED_LENGTH];

    // Similar to MasterFiles counterpart, but using underlying source
    // data source.

    // Note: there's a mismatch between this configuration and the actual
    // mock data source content: example.net doesn't exist in the data source.
    const ConstElementPtr config(Element::fromJSON(
                                     "{\"cache-enable\": true,"
                                     " \"cache-zones\": [\"example.org\","
                                     " \"example.net\", \"null.org\"]}"));
    const CacheConfig cache_conf("mock", &mock_client_, *config, true);
    LoadAction action = cache_conf.getLoadAction(RRClass::IN(),
                                                 Name("example.org"));
    ZoneData* zone_data = action(msgmt_);
    ASSERT_TRUE(zone_data);
    EXPECT_EQ("example.org.", zone_data->getOriginNode()->
              getAbsoluteLabels(labels_buf).toText());
    ZoneData::destroy(msgmt_, zone_data, RRClass::IN());

    // Zone not configured for the cache
    EXPECT_FALSE(cache_conf.getLoadAction(RRClass::IN(), Name("example.com")));

    // Zone configured for the cache but doesn't exist in the underling data
    // source.
    EXPECT_THROW(cache_conf.getLoadAction(RRClass::IN(), Name("example.net")),
                 DataSourceError);

    // buggy data source client: it returns a null pointer from getIterator.
    EXPECT_THROW(cache_conf.getLoadAction(RRClass::IN(), Name("null.org")),
                 isc::Unexpected);
}

TEST_F(CacheConfigTest, getSegmentType) {
    // Default type
    EXPECT_EQ("local",
              CacheConfig("MasterFiles", 0,
                          *master_config_, true).getSegmentType());

    // If we explicitly configure it, that value should be used.
    ConstElementPtr config(Element::fromJSON("{\"cache-enable\": true,"
                                             " \"cache-type\": \"mapped\","
                                             " \"params\": {}}" ));
    EXPECT_EQ("mapped",
              CacheConfig("MasterFiles", 0, *config, true).getSegmentType());

    // Wrong types: should be rejected at construction time
    ConstElementPtr badconfig(Element::fromJSON("{\"cache-enable\": true,"
                                                " \"cache-type\": 1,"
                                                " \"params\": {}}"));
    EXPECT_THROW(CacheConfig("MasterFiles", 0, *badconfig, true),
                 isc::data::TypeError);
}

}
