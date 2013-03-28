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

#include <datasrc/zone_table_config.h>
#include <datasrc/tests/mock_client.h>

#include <cc/data.h>
#include <dns/name.h>

#include <gtest/gtest.h>

using namespace isc::datasrc;
using namespace isc::data;
using namespace isc::dns;
using isc::datasrc::unittest::MockDataSourceClient;
using isc::datasrc::internal::ZoneTableConfig;

namespace {

const char* zones[] = {
    "example.org.",
    "example.com.",
    NULL
};

class ZoneTableConfigTest : public ::testing::Test {
protected:
    ZoneTableConfigTest() :
        mock_client_(zones),
        master_config_(Element::fromJSON(
                           "{\"params\": "
                           "  {\".\": \"" TEST_DATA_DIR "/root.zone\"}"
                           "}")),
        mock_config_(Element::fromJSON("{\"cache-zones\": [\".\"]}"))
    {}

    MockDataSourceClient mock_client_;
    const ConstElementPtr master_config_; // valid config for MasterFiles
    const ConstElementPtr mock_config_; // valid config for MasterFiles
};

TEST_F(ZoneTableConfigTest, constructMasterFiles) {
    // A simple case: configuring a MasterFiles table with a single zone
    const ZoneTableConfig ztconf("MasterFiles", 0, *master_config_);
    // getZoneConfig() returns a map containing exactly one entry
    // corresponding to the root zone information in the configuration.
    EXPECT_EQ(1, ztconf.getZoneConfig().size());
    EXPECT_EQ(Name::ROOT_NAME(), ztconf.getZoneConfig().begin()->first);
    EXPECT_EQ(TEST_DATA_DIR "/root.zone",
              ztconf.getZoneConfig().begin()->second);

    // With multiple zones.  There shouldn't be anything special, so we
    // only check the size of getZoneConfig.  Note that the constructor
    // doesn't check if the file exists, so they can be anything.
    const ConstElementPtr config_elem_multi(
        Element::fromJSON("{\"params\": "
                          "{\"example.com\": \"file1\","
                          " \"example.org\": \"file2\","
                          " \"example.info\": \"file3\"}"
                          "}"));
    EXPECT_EQ(3, ZoneTableConfig("MasterFiles", 0, *config_elem_multi).
              getZoneConfig().size());

    // A bit unusual, but acceptable case: empty parameters, so no zones.
    EXPECT_TRUE(ZoneTableConfig("MasterFiles", 0,
                                *Element::fromJSON("{\"params\": {}}")).
                getZoneConfig().empty());
}

TEST_F(ZoneTableConfigTest, badConstructMasterFiles) {
    // no "params"
    EXPECT_THROW(ZoneTableConfig("MasterFiles", 0, *Element::fromJSON("{}")),
                 isc::data::TypeError);

    // "params" is not a map
    EXPECT_THROW(ZoneTableConfig("MasterFiles", 0,
                                 *Element::fromJSON("{\"params\": []}")),
                 isc::data::TypeError);

    // bogus zone name
    const ConstElementPtr bad_config(Element::fromJSON(
                                         "{\"params\": "
                                         "{\"bad..name\": \"file1\"}}"));
    EXPECT_THROW(ZoneTableConfig("MasterFiles", 0, *bad_config),
                 isc::dns::EmptyLabel);

    // file name is not a string
    const ConstElementPtr bad_config2(Element::fromJSON(
                                          "{\"params\": {\".\": 1}}"));
    EXPECT_THROW(ZoneTableConfig("MasterFiles", 0, *bad_config2),
                 isc::data::TypeError);

    // Specify data source client (must be null for MasterFiles)
    EXPECT_THROW(ZoneTableConfig("MasterFiles", &mock_client_,
                                 *Element::fromJSON("{\"params\": {}}")),
                 isc::InvalidParameter);
}

TEST_F(ZoneTableConfigTest, constructWithMock) {
    // Performing equivalent set of tests as constructMasterFiles

    // Configure with a single zone.
    const ZoneTableConfig ztconf("mock", &mock_client_, *mock_config_);
    EXPECT_EQ(1, ztconf.getZoneConfig().size());
    EXPECT_EQ(Name::ROOT_NAME(), ztconf.getZoneConfig().begin()->first);
    EXPECT_EQ("", ztconf.getZoneConfig().begin()->second);

    // Configure with multiple zones.
    const ConstElementPtr config_elem_multi(
        Element::fromJSON("{\"cache-zones\": "
                          "[\"example.com\", \"example.org\",\"example.info\"]"
                          "}"));
    EXPECT_EQ(3, ZoneTableConfig("mock", &mock_client_, *config_elem_multi).
              getZoneConfig().size());

    // Empty
    EXPECT_TRUE(ZoneTableConfig("mock", &mock_client_,
                                *Element::fromJSON("{\"cache-zones\": []}")).
                getZoneConfig().empty());
}

TEST_F(ZoneTableConfigTest, badConstructWithMock) {
    // no "cache-zones" (may become valid in future, but for now "notimp")
    EXPECT_THROW(ZoneTableConfig("mock", &mock_client_,
                                 *Element::fromJSON("{}")),
                 isc::NotImplemented);

    // "cache-zones" is not a list
    EXPECT_THROW(ZoneTableConfig("mock", &mock_client_,
                                 *Element::fromJSON("{\"cache-zones\": {}}")),
                 isc::data::TypeError);

    // "cache-zone" entry is not a string
    EXPECT_THROW(ZoneTableConfig("mock", &mock_client_,
                                 *Element::fromJSON("{\"cache-zones\": [1]}")),
                 isc::data::TypeError);

    // bogus zone name
    const ConstElementPtr bad_config(Element::fromJSON(
                                         "{\"cache-zones\": [\"bad..\"]}"));
    EXPECT_THROW(ZoneTableConfig("mock", &mock_client_, *bad_config),
                 isc::dns::EmptyLabel);

    // duplicate zone name
    const ConstElementPtr dup_config(Element::fromJSON(
                                         "{\"cache-zones\": "
                                         " [\"example\", \"example\"]}"));
    EXPECT_THROW(ZoneTableConfig("mock", &mock_client_, *dup_config),
                 isc::InvalidParameter);

    // datasrc is null
    EXPECT_THROW(ZoneTableConfig("mock", 0, *mock_config_),
                 isc::InvalidParameter);
}

TEST_F(ZoneTableConfigTest, getSegmentType) {
    // Default type
    EXPECT_EQ("local",
              ZoneTableConfig("MasterFiles", 0,
                              *master_config_).getSegmentType());

    // If we explicitly configure it, that value should be used.
    ConstElementPtr config(Element::fromJSON("{\"cache-type\": \"mapped\","
                                             " \"params\": {}}" ));
    EXPECT_EQ("mapped",
              ZoneTableConfig("MasterFiles", 0, *config).getSegmentType());

    // Wrong types: should be rejected at construction time
    ConstElementPtr badconfig(Element::fromJSON("{\"cache-type\": 1,"
                                                " \"params\": {}}"));
    EXPECT_THROW(ZoneTableConfig("MasterFiles", 0, *badconfig),
                 isc::data::TypeError);
}

}
