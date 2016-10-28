// Copyright (C) 2016 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <gtest/gtest.h>
#include <cc/data.h>
#include <dhcp6/parser_context.h>

using namespace isc::data;
using namespace std;

namespace {

TEST(ParserTest, basic) {

    Parser6Context ctx;

    string txt = "{ \"Dhcp6\": { } }";

    ConstElementPtr json = ctx.parseString(txt);

    ASSERT_TRUE(json);
}

};
