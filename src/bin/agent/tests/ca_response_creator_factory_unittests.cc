// Copyright (C) 2017 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <agent/ca_response_creator.h>
#include <agent/ca_response_creator_factory.h>
#include <boost/pointer_cast.hpp>
#include <gtest/gtest.h>

using namespace isc::agent;

namespace {

// This test verifies that create() method always returns the same
// instance of the CtrlAgentResponseCreator object.
TEST(CtrlAgentResponseCreatorFactory, create) {
    CtrlAgentResponseCreatorFactory factory;

    // Invoke twice.
    CtrlAgentResponseCreatorPtr response1;
    CtrlAgentResponseCreatorPtr response2;
    ASSERT_NO_THROW(response1 = boost::dynamic_pointer_cast<
                    CtrlAgentResponseCreator>(factory.create()));
    ASSERT_NO_THROW(response2 = boost::dynamic_pointer_cast<
                    CtrlAgentResponseCreator>(factory.create()));

    // It must always return non-null object.
    ASSERT_TRUE(response1);
    ASSERT_TRUE(response2);

    // And it must always return the same object.
    EXPECT_TRUE(response1 == response2);

}

}
