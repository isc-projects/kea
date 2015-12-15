// Copyright (C) 2009, 2011, 2015  Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <gtest/gtest.h>

#include <config/module_spec.h>

#include <fstream>

#include <boost/foreach.hpp>

#include <config/tests/data_def_unittests_config.h>

using namespace isc::data;
using namespace isc::config;

std::string specfile(const std::string& name) {
    return (std::string(TEST_DATA_PATH) + "/" + name);
}

void
moduleSpecError(const std::string& file,
               const std::string& error1,
               const std::string& error2 = "",
               const std::string& error3 = "")
{
    EXPECT_THROW(moduleSpecFromFile(specfile(file)), ModuleSpecError);
    try {
        ModuleSpec dd = moduleSpecFromFile(specfile(file));
    } catch (const ModuleSpecError& dde) {
        std::string ddew = dde.what();
        EXPECT_EQ(error1 + error2 + error3, ddew);
    }
}

TEST(ModuleSpec, ReadingSpecfiles) {
    // Tests whether we can open specfiles and if we get the
    // right parse errors
    ModuleSpec dd = moduleSpecFromFile(specfile("spec1.spec"));
    EXPECT_EQ(dd.getFullSpec()->get("module_name")
                              ->stringValue(), "Spec1");
    dd = moduleSpecFromFile(specfile("spec2.spec"));
    EXPECT_EQ(dd.getFullSpec()->get("config_data")->size(), 6);
    moduleSpecError("doesnotexist",
                   "Error opening ",
                   specfile("doesnotexist"),
                   ": No such file or directory");

    dd = moduleSpecFromFile(specfile("spec2.spec"));
    EXPECT_EQ("[ { \"command_args\": [ { \"item_default\": \"\", \"item_name\": \"message\", \"item_optional\": false, \"item_type\": \"string\" } ], \"command_description\": \"Print the given message to stdout\", \"command_name\": \"print_message\" }, { \"command_args\": [  ], \"command_description\": \"Shut down Kea\", \"command_name\": \"shutdown\" } ]", dd.getCommandsSpec()->str());
    EXPECT_EQ("[ { \"item_default\": \"1970-01-01T00:00:00Z\", \"item_description\": \"A dummy date time\", \"item_format\": \"date-time\", \"item_name\": \"dummy_time\", \"item_optional\": false, \"item_title\": \"Dummy Time\", \"item_type\": \"string\" } ]", dd.getStatisticsSpec()->str());
    EXPECT_EQ("Spec2", dd.getModuleName());
    EXPECT_EQ("", dd.getModuleDescription());

    dd = moduleSpecFromFile(specfile("spec25.spec"));
    EXPECT_EQ("Spec25", dd.getModuleName());
    EXPECT_EQ("Just an empty module", dd.getModuleDescription());
    EXPECT_THROW(moduleSpecFromFile(specfile("spec26.spec")), ModuleSpecError);
    EXPECT_THROW(moduleSpecFromFile(specfile("spec34.spec")), ModuleSpecError);
    EXPECT_THROW(moduleSpecFromFile(specfile("spec35.spec")), ModuleSpecError);
    EXPECT_THROW(moduleSpecFromFile(specfile("spec36.spec")), ModuleSpecError);
    EXPECT_THROW(moduleSpecFromFile(specfile("spec37.spec")), ModuleSpecError);
    EXPECT_THROW(moduleSpecFromFile(specfile("spec38.spec")), ModuleSpecError);

    std::ifstream file;
    file.open(specfile("spec1.spec").c_str());
    dd = moduleSpecFromFile(file);
    EXPECT_EQ(dd.getFullSpec()->get("module_name")
                              ->stringValue(), "Spec1");
    EXPECT_TRUE(isNull(dd.getCommandsSpec()));
    EXPECT_TRUE(isNull(dd.getStatisticsSpec()));

    std::ifstream file2;
    file2.open(specfile("spec8.spec").c_str());
    EXPECT_THROW(moduleSpecFromFile(file2), ModuleSpecError);

}

TEST(ModuleSpec, SpecfileItems) {
    moduleSpecError("spec3.spec",
                   "item_name missing in { \"item_default\": 1, \"item_optional\": false, \"item_type\": \"integer\" }");
    moduleSpecError("spec4.spec",
                   "item_type missing in { \"item_default\": 1, \"item_name\": \"item1\", \"item_optional\": false }");
    moduleSpecError("spec5.spec",
                   "item_optional missing in { \"item_default\": 1, \"item_name\": \"item1\", \"item_type\": \"integer\" }");
    moduleSpecError("spec6.spec",
                   "item_default missing in { \"item_name\": \"item1\", \"item_optional\": false, \"item_type\": \"integer\" }");
    moduleSpecError("spec9.spec",
                   "item_default not of type integer");
    moduleSpecError("spec10.spec",
                   "item_default not of type real");
    moduleSpecError("spec11.spec",
                   "item_default not of type boolean");
    moduleSpecError("spec12.spec",
                   "item_default not of type string");
    moduleSpecError("spec13.spec",
                   "item_default not of type list");
    moduleSpecError("spec14.spec",
                   "item_default not of type map");
    moduleSpecError("spec15.spec",
                   "badname is not a valid type name");
    EXPECT_NO_THROW(moduleSpecFromFile(specfile("spec40.spec")));
}

TEST(ModuleSpec, SpecfileConfigData) {
    moduleSpecError("spec7.spec",
                   "module_name missing in {  }");
    moduleSpecError("spec8.spec",
                   "No module_spec in specification");
    moduleSpecError("spec16.spec",
                   "config_data is not a list of elements");
    moduleSpecError("spec21.spec",
                   "commands is not a list of elements");
}

TEST(ModuleSpec, SpecfileStatistics) {
    moduleSpecError("spec36.spec", "item_default not valid type of item_format");
    moduleSpecError("spec37.spec", "statistics is not a list of elements");
    moduleSpecError("spec38.spec", "item_default not valid type of item_format");
}

TEST(ModuleSpec, SpecfileCommands) {
    moduleSpecError("spec17.spec",
                   "command_name missing in { \"command_args\": [ { \"item_default\": \"\", \"item_name\": \"message\", \"item_optional\": false, \"item_type\": \"string\" } ], \"command_description\": \"Print the given message to stdout\" }");
    moduleSpecError("spec18.spec",
                   "command_args missing in { \"command_description\": \"Print the given message to stdout\", \"command_name\": \"print_message\" }");
    moduleSpecError("spec19.spec",
                   "command_args not of type list");
    moduleSpecError("spec20.spec",
                   "somethingbad is not a valid type name");
}

bool
dataTest(const ModuleSpec& dd, const std::string& data_file_name) {
    std::ifstream data_file;

    data_file.open(specfile(data_file_name).c_str());
    ConstElementPtr data = Element::fromJSON(data_file, data_file_name);
    data_file.close();

    return (dd.validateConfig(data));
}

bool
statisticsTest(const ModuleSpec& dd, const std::string& data_file_name) {
    std::ifstream data_file;

    data_file.open(specfile(data_file_name).c_str());
    ConstElementPtr data = Element::fromJSON(data_file, data_file_name);
    data_file.close();

    return (dd.validateStatistics(data));
}

bool
dataTestWithErrors(const ModuleSpec& dd, const std::string& data_file_name,
                      ElementPtr errors)
{
    std::ifstream data_file;

    data_file.open(specfile(data_file_name).c_str());
    ConstElementPtr data = Element::fromJSON(data_file, data_file_name);
    data_file.close();

    return (dd.validateConfig(data, true, errors));
}

bool
statisticsTestWithErrors(const ModuleSpec& dd, const std::string& data_file_name,
                      ElementPtr errors)
{
    std::ifstream data_file;

    data_file.open(specfile(data_file_name).c_str());
    ConstElementPtr data = Element::fromJSON(data_file, data_file_name);
    data_file.close();

    return (dd.validateStatistics(data, true, errors));
}

TEST(ModuleSpec, DataValidation) {
    ModuleSpec dd = moduleSpecFromFile(specfile("spec22.spec"));

    EXPECT_TRUE(dataTest(dd, "data22_1.data"));
    EXPECT_FALSE(dataTest(dd, "data22_2.data"));
    EXPECT_FALSE(dataTest(dd, "data22_3.data"));
    EXPECT_FALSE(dataTest(dd, "data22_4.data"));
    EXPECT_FALSE(dataTest(dd, "data22_5.data"));
    EXPECT_TRUE(dataTest(dd, "data22_6.data"));
    EXPECT_TRUE(dataTest(dd, "data22_7.data"));
    EXPECT_FALSE(dataTest(dd, "data22_8.data"));
    EXPECT_FALSE(dataTest(dd, "data22_9.data"));

    // Test if "version" is allowed in config data
    // (same data as 22_7, but added "version")
    EXPECT_TRUE(dataTest(dd, "data22_10.data"));

    ElementPtr errors = Element::createList();
    EXPECT_FALSE(dataTestWithErrors(dd, "data22_8.data", errors));
    EXPECT_EQ("[ \"Type mismatch\" ]", errors->str());

    errors = Element::createList();
    EXPECT_FALSE(dataTestWithErrors(dd, "data22_9.data", errors));
    EXPECT_EQ("[ \"Unknown item value_does_not_exist\" ]", errors->str());
}

TEST(ModuleSpec, StatisticsValidation) {
    ModuleSpec dd = moduleSpecFromFile(specfile("spec33.spec"));

    EXPECT_TRUE(statisticsTest(dd, "data33_1.data"));
    EXPECT_FALSE(statisticsTest(dd, "data33_2.data"));

    ElementPtr errors = Element::createList();
    EXPECT_FALSE(statisticsTestWithErrors(dd, "data33_2.data", errors));
    EXPECT_EQ("[ \"Format mismatch\", \"Format mismatch\", \"Format mismatch\" ]", errors->str());

    dd = moduleSpecFromFile(specfile("spec41.spec"));

    EXPECT_TRUE(statisticsTest(dd, "data41_1.data"));
    EXPECT_FALSE(statisticsTest(dd, "data41_2.data"));

    errors = Element::createList();
    EXPECT_FALSE(statisticsTestWithErrors(dd, "data41_2.data", errors));
    EXPECT_EQ("[ \"Type mismatch\" ]", errors->str());
}

TEST(ModuleSpec, CommandValidation) {
    ModuleSpec dd = moduleSpecFromFile(specfile("spec2.spec"));
    ConstElementPtr arg = Element::fromJSON("{}");
    ElementPtr errors = Element::createList();

    EXPECT_TRUE(dd.validateCommand("shutdown", arg, errors));
    EXPECT_EQ(errors->size(), 0);

    errors = Element::createList();
    EXPECT_FALSE(dd.validateCommand("unknowncommand", arg, errors));
    EXPECT_EQ(errors->size(), 1);
    EXPECT_EQ(errors->get(0)->stringValue(), "Unknown command unknowncommand");

    errors = Element::createList();
    EXPECT_FALSE(dd.validateCommand("print_message", arg, errors));
    EXPECT_EQ(errors->size(), 1);
    EXPECT_EQ(errors->get(0)->stringValue(), "Non-optional value missing");

    errors = Element::createList();
    arg = Element::fromJSON("{ \"message\": \"Hello\" }");
    EXPECT_TRUE(dd.validateCommand("print_message", arg, errors));
    EXPECT_EQ(errors->size(), 0);

    errors = Element::createList();
    arg = Element::fromJSON("{ \"message\": \"Hello\", \"unknown_second_arg\": 1 }");
    EXPECT_FALSE(dd.validateCommand("print_message", arg, errors));
    EXPECT_EQ(errors->size(), 1);
    EXPECT_EQ(errors->get(0)->stringValue(), "Unknown item unknown_second_arg");

    errors = Element::createList();
    arg = Element::fromJSON("{ \"message\": 1 }");
    EXPECT_FALSE(dd.validateCommand("print_message", arg, errors));
    EXPECT_EQ(errors->size(), 1);
    EXPECT_EQ(errors->get(0)->stringValue(), "Type mismatch");

}

TEST(ModuleSpec, NamedSetValidation) {
    ModuleSpec dd = moduleSpecFromFile(specfile("spec32.spec"));

    ElementPtr errors = Element::createList();
    EXPECT_TRUE(dataTestWithErrors(dd, "data32_1.data", errors));
    EXPECT_FALSE(dataTest(dd, "data32_2.data"));
    EXPECT_FALSE(dataTest(dd, "data32_3.data"));
}

TEST(ModuleSpec, CheckFormat) {

    const std::string json_begin = "{ \"module_spec\": { \"module_name\": \"Foo\", \"statistics\": [ { \"item_name\": \"dummy_time\", \"item_type\": \"string\", \"item_optional\": true, \"item_title\": \"Dummy Time\", \"item_description\": \"A dummy date time\"";
    const std::string json_end = " } ] } }";
    std::string item_default;
    std::string item_format;
    std::vector<std::string> specs;
    ConstElementPtr el;

    specs.clear();
    item_default = "\"item_default\": \"2011-05-27T19:42:57Z\",";
    item_format  = "\"item_format\": \"date-time\"";
    specs.push_back("," + item_default + item_format);
    item_default = "\"item_default\": \"2011-05-27\",";
    item_format  = "\"item_format\": \"date\"";
    specs.push_back("," + item_default + item_format);
    item_default = "\"item_default\": \"19:42:57\",";
    item_format  = "\"item_format\": \"time\"";
    specs.push_back("," + item_default + item_format);

    item_format  = "\"item_format\": \"date-time\"";
    specs.push_back("," + item_format);
    item_default = "";
    item_format  = "\"item_format\": \"date\"";
    specs.push_back("," + item_format);
    // cppcheck-suppress redundantAssignment
    item_default = "";
    item_format  = "\"item_format\": \"time\"";
    specs.push_back("," + item_format);

    // cppcheck-suppress redundantAssignment
    item_default = "\"item_default\": \"a\"";
    specs.push_back("," + item_default);
    item_default = "\"item_default\": \"b\"";
    specs.push_back("," + item_default);
    item_default = "\"item_default\": \"c\"";
    specs.push_back("," + item_default);

    item_format  = "\"item_format\": \"dummy\"";
    specs.push_back("," + item_format);

    specs.push_back("");

    BOOST_FOREACH(std::string s, specs) {
        el = Element::fromJSON(json_begin + s + json_end)->get("module_spec");
        EXPECT_NO_THROW(ModuleSpec(el, true));
    }

    specs.clear();
    item_default = "\"item_default\": \"2011-05-27T19:42:57Z\",";
    item_format  = "\"item_format\": \"dummy\"";
    specs.push_back("," + item_default + item_format);
    item_default = "\"item_default\": \"2011-05-27\",";
    item_format  = "\"item_format\": \"dummy\"";
    specs.push_back("," + item_default + item_format);
    item_default = "\"item_default\": \"19:42:57Z\",";
    item_format  = "\"item_format\": \"dummy\"";
    specs.push_back("," + item_default + item_format);

    item_default = "\"item_default\": \"2011-13-99T99:99:99Z\",";
    item_format  = "\"item_format\": \"date-time\"";
    specs.push_back("," + item_default + item_format);
    item_default = "\"item_default\": \"2011-13-99\",";
    item_format  = "\"item_format\": \"date\"";
    specs.push_back("," + item_default + item_format);
    item_default = "\"item_default\": \"99:99:99Z\",";
    item_format  = "\"item_format\": \"time\"";
    specs.push_back("," + item_default + item_format);

    item_default = "\"item_default\": \"1\",";
    item_format  = "\"item_format\": \"date-time\"";
    specs.push_back("," + item_default + item_format);
    item_default = "\"item_default\": \"1\",";
    item_format  = "\"item_format\": \"date\"";
    specs.push_back("," + item_default + item_format);
    item_default = "\"item_default\": \"1\",";
    item_format  = "\"item_format\": \"time\"";
    specs.push_back("," + item_default + item_format);

    item_default = "\"item_default\": \"\",";
    item_format  = "\"item_format\": \"date-time\"";
    specs.push_back("," + item_default + item_format);
    item_default = "\"item_default\": \"\",";
    item_format  = "\"item_format\": \"date\"";
    specs.push_back("," + item_default + item_format);
    item_default = "\"item_default\": \"\",";
    item_format  = "\"item_format\": \"time\"";
    specs.push_back("," + item_default + item_format);

    // wrong date-time-type format not ending with "Z"
    item_default = "\"item_default\": \"2011-05-27T19:42:57\",";
    item_format  = "\"item_format\": \"date-time\"";
    specs.push_back("," + item_default + item_format);
    // wrong date-type format ending with "T"
    item_default = "\"item_default\": \"2011-05-27T\",";
    item_format  = "\"item_format\": \"date\"";
    specs.push_back("," + item_default + item_format);
    // wrong time-type format ending with "Z"
    item_default = "\"item_default\": \"19:42:57Z\",";
    item_format  = "\"item_format\": \"time\"";
    specs.push_back("," + item_default + item_format);

    BOOST_FOREACH(std::string s, specs) {
        el = Element::fromJSON(json_begin + s + json_end)->get("module_spec");
        EXPECT_THROW(ModuleSpec(el, true), ModuleSpecError);
    }
}
