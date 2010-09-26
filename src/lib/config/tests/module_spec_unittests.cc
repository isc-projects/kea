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

#include <config/module_spec.h>

#include <fstream>

#include <config/tests/data_def_unittests_config.h>

using namespace isc::data;
using namespace isc::config;

std::string specfile(const std::string name) {
    return (std::string(TEST_DATA_PATH) + "/" + name);
}

void
module_spec_error(const std::string& file,
               const std::string& error1,
               const std::string& error2 = "",
               const std::string& error3 = "")
{
    EXPECT_THROW(moduleSpecFromFile(specfile(file)), ModuleSpecError);
    try {
        ModuleSpec dd = moduleSpecFromFile(specfile(file));
    } catch (ModuleSpecError dde) {
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
    module_spec_error("doesnotexist",
                   "Error opening ",
                   specfile("doesnotexist"),
                   ": No such file or directory");

    dd = moduleSpecFromFile(specfile("spec2.spec"));
    EXPECT_EQ("[ { \"command_args\": [ { \"item_default\": \"\", \"item_name\": \"message\", \"item_optional\": false, \"item_type\": \"string\" } ], \"command_description\": \"Print the given message to stdout\", \"command_name\": \"print_message\" }, { \"command_args\": [  ], \"command_description\": \"Shut down BIND 10\", \"command_name\": \"shutdown\" } ]", dd.getCommandsSpec()->str());
    EXPECT_EQ("Spec2", dd.getModuleName());
    EXPECT_EQ("", dd.getModuleDescription());

    dd = moduleSpecFromFile(specfile("spec25.spec"));
    EXPECT_EQ("Spec25", dd.getModuleName());
    EXPECT_EQ("Just an empty module", dd.getModuleDescription());
    EXPECT_THROW(moduleSpecFromFile(specfile("spec26.spec")), ModuleSpecError);

    std::ifstream file;
    file.open(specfile("spec1.spec").c_str());
    dd = moduleSpecFromFile(file);
    EXPECT_EQ(dd.getFullSpec()->get("module_name")
                              ->stringValue(), "Spec1");
    EXPECT_TRUE(isNull(dd.getCommandsSpec()));

    std::ifstream file2;
    file2.open(specfile("spec8.spec").c_str());
    EXPECT_THROW(moduleSpecFromFile(file2), ModuleSpecError);

}

TEST(ModuleSpec, SpecfileItems) {
    module_spec_error("spec3.spec",
                   "item_name missing in { \"item_default\": 1, \"item_optional\": false, \"item_type\": \"integer\" }");
    module_spec_error("spec4.spec",
                   "item_type missing in { \"item_default\": 1, \"item_name\": \"item1\", \"item_optional\": false }");
    module_spec_error("spec5.spec",
                   "item_optional missing in { \"item_default\": 1, \"item_name\": \"item1\", \"item_type\": \"integer\" }");
    module_spec_error("spec6.spec",
                   "item_default missing in { \"item_name\": \"item1\", \"item_optional\": false, \"item_type\": \"integer\" }");
    module_spec_error("spec9.spec",
                   "item_default not of type integer");
    module_spec_error("spec10.spec",
                   "item_default not of type real");
    module_spec_error("spec11.spec",
                   "item_default not of type boolean");
    module_spec_error("spec12.spec",
                   "item_default not of type string");
    module_spec_error("spec13.spec",
                   "item_default not of type list");
    module_spec_error("spec14.spec",
                   "item_default not of type map");
    module_spec_error("spec15.spec",
                   "badname is not a valid type name");
}

TEST(ModuleSpec, SpecfileConfigData)
{
    module_spec_error("spec7.spec",
                   "module_name missing in {  }");
    module_spec_error("spec8.spec",
                   "No module_spec in specification");
    module_spec_error("spec16.spec",
                   "config_data is not a list of elements");
    module_spec_error("spec21.spec",
                   "commands is not a list of elements");
}

TEST(ModuleSpec, SpecfileCommands)
{
    module_spec_error("spec17.spec",
                   "command_name missing in { \"command_args\": [ { \"item_default\": \"\", \"item_name\": \"message\", \"item_optional\": false, \"item_type\": \"string\" } ], \"command_description\": \"Print the given message to stdout\" }");
    module_spec_error("spec18.spec",
                   "command_args missing in { \"command_description\": \"Print the given message to stdout\", \"command_name\": \"print_message\" }");
    module_spec_error("spec19.spec",
                   "command_args not of type list");
    module_spec_error("spec20.spec",
                   "somethingbad is not a valid type name");
/*
    module_spec_error("spec22.spec",
                   "");
*/
}

bool
data_test(const ModuleSpec& dd, const std::string& data_file_name) {
    std::ifstream data_file;

    data_file.open(specfile(data_file_name).c_str());
    ConstElementPtr data = Element::fromJSON(data_file, data_file_name);
    data_file.close();

    return (dd.validate_config(data));
}

bool
data_test_with_errors(const ModuleSpec& dd, const std::string& data_file_name,
                      ElementPtr errors)
{
    std::ifstream data_file;

    data_file.open(specfile(data_file_name).c_str());
    ConstElementPtr data = Element::fromJSON(data_file, data_file_name);
    data_file.close();

    return (dd.validate_config(data, true, errors));
}

TEST(ModuleSpec, DataValidation) {
    ModuleSpec dd = moduleSpecFromFile(specfile("spec22.spec"));

    EXPECT_TRUE(data_test(dd, "data22_1.data"));
    EXPECT_FALSE(data_test(dd, "data22_2.data"));
    EXPECT_FALSE(data_test(dd, "data22_3.data"));
    EXPECT_FALSE(data_test(dd, "data22_4.data"));
    EXPECT_FALSE(data_test(dd, "data22_5.data"));
    EXPECT_TRUE(data_test(dd, "data22_6.data"));
    EXPECT_TRUE(data_test(dd, "data22_7.data"));
    EXPECT_FALSE(data_test(dd, "data22_8.data"));

    ElementPtr errors = Element::createList();
    EXPECT_FALSE(data_test_with_errors(dd, "data22_8.data", errors));
    EXPECT_EQ("[ \"Type mismatch\" ]", errors->str());
}
