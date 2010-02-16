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

#include <data_def.h>

#include <fstream>

#include "data_def_unittests_config.h"

using namespace isc::data;

std::string specfile(const std::string name) {
    return std::string(TEST_DATA_PATH) + "/" + name;
}

void
data_def_error(const std::string& file,
               const std::string& error1,
               const std::string& error2 = "",
               const std::string& error3 = "")
{
    EXPECT_THROW(DataDefinition(specfile(file)), DataDefinitionError);
    try {
        DataDefinition dd = DataDefinition(specfile(file));
    } catch (DataDefinitionError dde) {
        std::string ddew = dde.what();
        EXPECT_EQ(error1 + error2 + error3, ddew);
    }
}

TEST(DataDefinition, ReadingSpecfiles) {
    // Tests whether we can open specfiles and if we get the
    // right parse errors
    DataDefinition dd = DataDefinition(specfile("spec1.spec"));
    EXPECT_EQ(dd.getDefinition()->get("module_spec")
                                ->get("module_name")
                                ->stringValue(), "Spec1");
    dd = DataDefinition(specfile("spec2.spec"));
    EXPECT_EQ(dd.getDefinition()->get("module_spec")
                                ->get("config_data")->size(), 6);
    data_def_error("doesnotexist",
                   "Error opening ",
                   specfile("doesnotexist"),
                   ": No such file or directory");

    std::ifstream file;
    file.open(specfile("spec1.spec").c_str());
    dd = DataDefinition(file);
    EXPECT_EQ(dd.getDefinition()->get("module_spec")
                                ->get("module_name")
                                ->stringValue(), "Spec1");
}

TEST(DataDefinition, SpecfileItems) {
    data_def_error("spec3.spec",
                   "item_name missing in {\"item_default\": 1, \"item_optional\": False, \"item_type\": \"integer\"}");
    data_def_error("spec4.spec",
                   "item_type missing in {\"item_default\": 1, \"item_name\": \"item1\", \"item_optional\": False}");
    data_def_error("spec5.spec",
                   "item_optional missing in {\"item_default\": 1, \"item_name\": \"item1\", \"item_type\": \"integer\"}");
    data_def_error("spec6.spec",
                   "item_default missing in {\"item_name\": \"item1\", \"item_optional\": False, \"item_type\": \"integer\"}");
    data_def_error("spec9.spec",
                   "item_default not of type integer");
    data_def_error("spec10.spec",
                   "item_default not of type real");
    data_def_error("spec11.spec",
                   "item_default not of type boolean");
    data_def_error("spec12.spec",
                   "item_default not of type string");
    data_def_error("spec13.spec",
                   "item_default not of type list");
    data_def_error("spec14.spec",
                   "item_default not of type map");
    data_def_error("spec15.spec",
                   "badname is not a valid type name");
}

TEST(DataDefinition, SpecfileConfigData)
{
    data_def_error("spec7.spec",
                   "module_name missing in {}");
    data_def_error("spec8.spec",
                   "Data specification does not contain module_spec element");
    data_def_error("spec16.spec",
                   "config_data is not a list of elements");
    data_def_error("spec21.spec",
                   "commands is not a list of elements");
}

TEST(DataDefinition, SpecfileCommands)
{
    data_def_error("spec17.spec",
                   "command_name missing in {\"command_args\": [ {\"item_default\": \"\", \"item_name\": \"message\", \"item_optional\": False, \"item_type\": \"string\"} ], \"command_description\": \"Print the given message to stdout\"}");
    data_def_error("spec18.spec",
                   "command_args missing in {\"command_description\": \"Print the given message to stdout\", \"command_name\": \"print_message\"}");
    data_def_error("spec19.spec",
                   "command_args not of type list");
    data_def_error("spec20.spec",
                   "somethingbad is not a valid type name");
/*
    data_def_error("spec22.spec",
                   "");
*/
}

bool
data_test(DataDefinition dd, const std::string& data_file_name)
{
    std::ifstream data_file;

    data_file.open(specfile(data_file_name).c_str());
    ElementPtr data = Element::createFromString(data_file, data_file_name);
    data_file.close();

    return dd.validate(data);
}

TEST(DataDefinition, DataValidation) {
    DataDefinition dd = DataDefinition(specfile("spec22.spec"));

    EXPECT_TRUE(data_test(dd, "data22_1.data"));
    EXPECT_FALSE(data_test(dd, "data22_2.data"));
    EXPECT_FALSE(data_test(dd, "data22_3.data"));
    EXPECT_FALSE(data_test(dd, "data22_4.data"));
    EXPECT_FALSE(data_test(dd, "data22_5.data"));
    EXPECT_TRUE(data_test(dd, "data22_6.data"));
    EXPECT_TRUE(data_test(dd, "data22_7.data"));
    EXPECT_FALSE(data_test(dd, "data22_8.data"));
}
