
// Copyright (C) 2009  Internet Systems Consortium, Inc. ("ISC")
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

// $Id$

#include <gtest/gtest.h>

#include <config/tests/data_def_unittests_config.h>
#include <config/config_data.h>

#include <iostream>

using namespace isc::data;
using namespace isc::config;

ConfigData
setupSpec2() {
    ModuleSpec spec2 = moduleSpecFromFile(std::string(TEST_DATA_PATH) + "/spec22.spec");
    return (ConfigData(spec2));
}

TEST(ConfigData, Creation) {
    ConfigData cd = setupSpec2();
    EXPECT_TRUE(true);
}

TEST(ConfigData, getValue) {
    ModuleSpec spec22 = moduleSpecFromFile(std::string(TEST_DATA_PATH) + "/spec22.spec");
    ConfigData cd = ConfigData(spec22);
    //std::cout << "[XX] SPEC2: " << cd.getModuleSpec().getFullSpec() << std::endl;
    bool is_default;
    //ElementPtr value = cd.getValue(is_default, "item1");
    EXPECT_EQ(9, cd.getValue("value1")->intValue());
    EXPECT_EQ(9, cd.getValue(is_default, "value1")->intValue());
    EXPECT_TRUE(is_default);
    EXPECT_EQ(9.9, cd.getValue("value2")->doubleValue());
    EXPECT_EQ(9.9, cd.getValue(is_default, "value2")->doubleValue());
    EXPECT_TRUE(is_default);
    EXPECT_FALSE(cd.getValue("value3")->boolValue());
    EXPECT_FALSE(cd.getValue(is_default, "value3")->boolValue());
    EXPECT_TRUE(is_default);
    EXPECT_EQ("default_string", cd.getValue("value4")->stringValue());
    EXPECT_EQ("default_string", cd.getValue(is_default, "value4")->stringValue());
    EXPECT_TRUE(is_default);
    EXPECT_EQ("a", cd.getValue("value5")->get(0)->stringValue());
    EXPECT_EQ("a", cd.getValue(is_default, "value5")->get(0)->stringValue());
    EXPECT_TRUE(is_default);
    EXPECT_EQ("b", cd.getValue("value5")->get(1)->stringValue());
    EXPECT_EQ("b", cd.getValue(is_default, "value5")->get(1)->stringValue());
    EXPECT_EQ("b", cd.getValue(is_default, "value5/")->get(1)->stringValue());
    EXPECT_TRUE(is_default);
    EXPECT_EQ("{  }", cd.getValue("value6")->str());
    EXPECT_EQ("{  }", cd.getValue(is_default, "value6")->str());
    EXPECT_EQ("{  }", cd.getValue(is_default, "value6/")->str());
    EXPECT_TRUE(is_default);
    EXPECT_EQ("[  ]", cd.getValue("value8")->str());

    EXPECT_THROW(cd.getValue("")->str(), DataNotFoundError);
    EXPECT_THROW(cd.getValue("/")->str(), DataNotFoundError);
    EXPECT_THROW(cd.getValue("no_such_item")->str(), DataNotFoundError);
    EXPECT_THROW(cd.getValue("value6/a")->str(), DataNotFoundError);
    EXPECT_THROW(cd.getValue("value6/no_such_item")->str(), DataNotFoundError);
    EXPECT_THROW(cd.getValue("value8/a")->str(), DataNotFoundError);
    EXPECT_THROW(cd.getValue("value8/a")->str(), DataNotFoundError);
    EXPECT_THROW(cd.getValue("value8/a")->str(), DataNotFoundError);

    ModuleSpec spec1 = moduleSpecFromFile(std::string(TEST_DATA_PATH) + "/spec1.spec");
    ConfigData cd1 = ConfigData(spec1);
    EXPECT_THROW(cd1.getValue("anything")->str(), DataNotFoundError);
}

TEST(ConfigData, setLocalConfig) {
    ModuleSpec spec2 = moduleSpecFromFile(std::string(TEST_DATA_PATH) + "/spec2.spec");
    ConfigData cd = ConfigData(spec2);
    bool is_default;

    ElementPtr my_config = Element::fromJSON("{ \"item1\": 2 }");
    ElementPtr my_config2 = Element::fromJSON("{ \"item6\": { \"value1\": \"a\" } }");

    EXPECT_EQ("{  }", cd.getValue("item6")->str());

    cd.setLocalConfig(my_config);
    EXPECT_EQ(2, cd.getValue(is_default, "item1")->intValue());
    EXPECT_FALSE(is_default);
    EXPECT_EQ("{  }", cd.getValue("item6")->str());
    EXPECT_EQ(1.1, cd.getValue(is_default, "item2")->doubleValue());
    EXPECT_TRUE(is_default);

    cd.setLocalConfig(my_config2);
    EXPECT_EQ("{ \"value1\": \"a\" }", cd.getValue("item6")->str());
}

TEST(ConfigData, getLocalConfig) {
    ModuleSpec spec2 = moduleSpecFromFile(std::string(TEST_DATA_PATH) + "/spec2.spec");
    ConfigData cd = ConfigData(spec2);
    EXPECT_EQ("{  }", cd.getLocalConfig()->str());
    
    ElementPtr my_config = Element::fromJSON("{ \"item1\": 2 }");
    cd.setLocalConfig(my_config);
    EXPECT_EQ("{ \"item1\": 2 }", cd.getLocalConfig()->str());

    ElementPtr my_config2 = Element::fromJSON("{ \"item6\": { \"value1\": \"a\" } }");
    cd.setLocalConfig(my_config2);
    EXPECT_EQ("{ \"item6\": { \"value1\": \"a\" } }", cd.getLocalConfig()->str());
}

TEST(ConfigData, getItemList) {
    ModuleSpec spec2 = moduleSpecFromFile(std::string(TEST_DATA_PATH) + "/spec2.spec");
    ConfigData cd = ConfigData(spec2);

    EXPECT_EQ("[ \"item1\", \"item2\", \"item3\", \"item4\", \"item5/\", \"item6/\" ]", cd.getItemList()->str());
    EXPECT_EQ("[ \"item1\", \"item2\", \"item3\", \"item4\", \"item5/\", \"item6/value1\", \"item6/value2\" ]", cd.getItemList("", true)->str());
    EXPECT_EQ("[ \"item6/value1\", \"item6/value2\" ]", cd.getItemList("item6")->str());
}

TEST(ConfigData, getFullConfig) {
    ModuleSpec spec2 = moduleSpecFromFile(std::string(TEST_DATA_PATH) + "/spec2.spec");
    ConfigData cd = ConfigData(spec2);

    EXPECT_EQ("{ \"item1\": 1, \"item2\": 1.1, \"item3\": true, \"item4\": \"test\", \"item5/\": [ \"a\", \"b\" ], \"item6/value1\": \"default\", \"item6/value2\": None }", cd.getFullConfig()->str());
    ElementPtr my_config = Element::fromJSON("{ \"item1\": 2 }");
    cd.setLocalConfig(my_config);
    EXPECT_EQ("{ \"item1\": 2, \"item2\": 1.1, \"item3\": true, \"item4\": \"test\", \"item5/\": [ \"a\", \"b\" ], \"item6/value1\": \"default\", \"item6/value2\": None }", cd.getFullConfig()->str());
    ElementPtr my_config2 = Element::fromJSON("{ \"item6\": { \"value1\": \"a\" } }");
    cd.setLocalConfig(my_config2);
    EXPECT_EQ("{ \"item1\": 1, \"item2\": 1.1, \"item3\": true, \"item4\": \"test\", \"item5/\": [ \"a\", \"b\" ], \"item6/value1\": \"a\", \"item6/value2\": None }", cd.getFullConfig()->str());
}

