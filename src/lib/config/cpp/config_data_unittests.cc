
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

#include "config_data.h"
#include "data_def_unittests_config.h"

#include <iostream>

using namespace isc::data;
using namespace isc::config;

ConfigData
setupSpec2()
{
    ModuleSpec spec2 = moduleSpecFromFile(std::string(TEST_DATA_PATH) + "/spec2.spec");
    return ConfigData(spec2);
}

TEST(ConfigData, Creation) {
    ConfigData cd = setupSpec2();
    EXPECT_TRUE(true);
}

TEST(ConfigData, getValue) {
    ModuleSpec spec2 = moduleSpecFromFile(std::string(TEST_DATA_PATH) + "/spec2.spec");
    ConfigData cd = ConfigData(spec2);
    //std::cout << "[XX] SPEC2: " << cd.getModuleSpec().getFullSpec() << std::endl;
    bool is_default;
    //ElementPtr value = cd.getValue(is_default, "item1");
    EXPECT_EQ(1, cd.getValue(is_default, "item1")->intValue());
    EXPECT_TRUE(is_default);
    EXPECT_EQ(1.1, cd.getValue(is_default, "item2")->doubleValue());
    EXPECT_TRUE(is_default);
    EXPECT_TRUE(cd.getValue(is_default, "item3")->boolValue());
    EXPECT_TRUE(is_default);
    EXPECT_EQ("test", cd.getValue(is_default, "item4")->stringValue());
    EXPECT_TRUE(is_default);
    EXPECT_EQ("a", cd.getValue(is_default, "item5")->get(0)->stringValue());
    EXPECT_TRUE(is_default);
    EXPECT_EQ("b", cd.getValue(is_default, "item5")->get(1)->stringValue());
    EXPECT_TRUE(is_default);
    EXPECT_EQ("{}", cd.getValue(is_default, "item6")->str());
    EXPECT_TRUE(is_default);
}

TEST(ConfigData, setLocalConfig) {
    ModuleSpec spec2 = moduleSpecFromFile(std::string(TEST_DATA_PATH) + "/spec2.spec");
    ConfigData cd = ConfigData(spec2);
    bool is_default;

    ElementPtr my_config = Element::createFromString("{\"item1\": 2}");
    ElementPtr my_config2 = Element::createFromString("{\"item6\": { \"value1\": \"a\" } }");

    EXPECT_EQ("{}", cd.getValue("item6")->str());

    cd.setLocalConfig(my_config);
    EXPECT_EQ(2, cd.getValue(is_default, "item1")->intValue());
    EXPECT_FALSE(is_default);
    EXPECT_EQ("{}", cd.getValue("item6")->str());
    EXPECT_EQ(1.1, cd.getValue(is_default, "item2")->doubleValue());
    EXPECT_TRUE(is_default);

    cd.setLocalConfig(my_config2);
    EXPECT_EQ("{\"value1\": \"a\"}", cd.getValue("item6")->str());
}

TEST(ConfigData, getLocalConfig) {
    ModuleSpec spec2 = moduleSpecFromFile(std::string(TEST_DATA_PATH) + "/spec2.spec");
    ConfigData cd = ConfigData(spec2);
    EXPECT_EQ("{}", cd.getLocalConfig()->str());
    
    ElementPtr my_config = Element::createFromString("{\"item1\": 2}");
    cd.setLocalConfig(my_config);
    EXPECT_EQ("{\"item1\": 2}", cd.getLocalConfig()->str());

    ElementPtr my_config2 = Element::createFromString("{\"item6\": { \"value1\": \"a\" } }");
    cd.setLocalConfig(my_config2);
    EXPECT_EQ("{\"item6\": {\"value1\": \"a\"}}", cd.getLocalConfig()->str());
}

TEST(ConfigData, getItemList) {
    ModuleSpec spec2 = moduleSpecFromFile(std::string(TEST_DATA_PATH) + "/spec2.spec");
    ConfigData cd = ConfigData(spec2);

    //EXPECT_EQ("", cd.getItemList("")->str());
}

