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

TEST(DataDefinition, Specfiles) {
    // Tests whether we can open specfiles and if we get the
    // right parse errors
    DataDefinition dd = DataDefinition(specfile("spec1.spec"));
    EXPECT_EQ(dd.getDefinition()->get("data_specification")
                                ->get("module_name")
                                ->stringValue(), "Spec1");
    dd = DataDefinition(specfile("spec2.spec"));
    EXPECT_EQ(dd.getDefinition()->get("data_specification")
                                ->get("config_data")->size(), 6);
    data_def_error("doesnotexist",
                   "Error opening ",
                   specfile("doesnotexist"),
                   ": No such file or directory");
    data_def_error("spec3.spec",
                   "item_name missing in {\"item_default\": 1, \"item_optional\": False, \"item_type\": \"integer\"}");
    data_def_error("spec4.spec",
                   "item_type missing in {\"item_default\": 1, \"item_name\": \"item1\", \"item_optional\": False}");
    data_def_error("spec5.spec",
                   "item_optional missing in {\"item_default\": 1, \"item_name\": \"item1\", \"item_type\": \"integer\"}");
    data_def_error("spec6.spec",
                   "item_default missing in {\"item_name\": \"item1\", \"item_optional\": False, \"item_type\": \"integer\"}");
    data_def_error("spec7.spec",
                   "module_name missing in {}");
    data_def_error("spec8.spec",
                   "Data specification does not contain data_specification element");
}
