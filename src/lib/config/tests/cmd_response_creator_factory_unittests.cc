// Copyright (C) 2021-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <config/cmd_response_creator_factory.h>
#include <boost/pointer_cast.hpp>

#include <gtest/gtest.h>

using namespace isc::config;

namespace {

// This test verifies the default factory constructor and
// the create() method.
TEST(CmdResponseCreatorFactory, createDefault) {
    // Create the factory.
    CmdResponseCreatorFactory factory;

    // Create a response creator.
    CmdResponseCreatorPtr response1;
    ASSERT_NO_THROW(response1 = boost::dynamic_pointer_cast<
                    CmdResponseCreator>(factory.create()));
    ASSERT_TRUE(response1);

    // Agent response emulation should be enabled by default.
    EXPECT_TRUE(response1->emulateAgentResponse());

    // Authorization configuration should be an empty pointer.
    EXPECT_FALSE(CmdResponseCreator::http_auth_config_);

    // By default all commands are accepted.
    EXPECT_TRUE(CmdResponseCreator::command_accept_list_.empty());

    // Invoke create() again.
    CmdResponseCreatorPtr response2;
    ASSERT_NO_THROW(response2 = boost::dynamic_pointer_cast<
                    CmdResponseCreator>(factory.create()));
    ASSERT_TRUE(response2);

    // And it must always return the same object.
    EXPECT_TRUE(response1 == response2);
}

// This test verifies that agent response emulation can
// be turned off.
TEST(CmdResponseCreatorFactory, createAgentEmulationDisabled) {
    // Instantiate the factory with agent emulation disabled.
    CmdResponseCreatorFactory factory(false);

    // Create the response creator.
    CmdResponseCreatorPtr response;
    ASSERT_NO_THROW(response = boost::dynamic_pointer_cast<
                    CmdResponseCreator>(factory.create()));
    ASSERT_TRUE(response);

    // Agent response emulation should be disabled.
    EXPECT_FALSE(response->emulateAgentResponse());

    // Authorization configuration should be an empty pointer.
    EXPECT_FALSE(CmdResponseCreator::http_auth_config_);

    // By default all commands are accepted.
    EXPECT_TRUE(CmdResponseCreator::command_accept_list_.empty());
}

} // end of anonymous namespace
