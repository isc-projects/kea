// Copyright (C) 2021-2024 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <config/http_command_response_creator_factory.h>
#include <util/filesystem.h>
#include <boost/pointer_cast.hpp>

#include <gtest/gtest.h>

using namespace isc::config;
using namespace isc::data;
using namespace isc::util;
using namespace std;

namespace {

/// @brief Test fixture class for @ref class HttpCommandResponseCreatorFactory
class HttpCommandResponseCreatorFactoryTest : public ::testing::Test {
public:
    /// @brief Constructor.
    HttpCommandResponseCreatorFactoryTest() {
        file::PathChecker::enableEnforcement(false);
    }

    /// @brief Desstructor.
    virtual ~HttpCommandResponseCreatorFactoryTest() {
        file::PathChecker::enableEnforcement(true);
    }
};

// This test verifies the default factory constructor and
// the create() method.
TEST_F(HttpCommandResponseCreatorFactoryTest, create) {
    // Configure the HTTP control socket.
    string config = R"(
        {
            "socket-type": "http",
            "socket-address": "127.0.0.1",
            "socket-port": 8000
        }
    )";
    ElementPtr json;
    ASSERT_NO_THROW(json = Element::fromJSON(config));
    HttpCommandConfigPtr http_config;
    ASSERT_NO_THROW(http_config.reset(new HttpCommandConfig(json)));

    // Create the factory.
    HttpCommandResponseCreatorFactory factory(http_config);

    // Create a response creator.
    HttpCommandResponseCreatorPtr rcf;
    ASSERT_NO_THROW(rcf = boost::dynamic_pointer_cast<
                    HttpCommandResponseCreator>(factory.create()));
    ASSERT_TRUE(rcf);

    // Get back the HTTP control socket config.
    HttpCommandConfigPtr got = rcf->getHttpCommandConfig();
    ASSERT_TRUE(got);

    // Expect equality.
    EXPECT_EQ(http_config->toElement()->str(), got->toElement()->str());

    // The emulation flag is hidden so check it too.
    EXPECT_EQ(http_config->getEmulateAgentResponse(),
              got->getEmulateAgentResponse());

    // Get again a response creator.
    HttpCommandResponseCreatorPtr rcf2;
    ASSERT_NO_THROW(rcf2 = boost::dynamic_pointer_cast<
                    HttpCommandResponseCreator>(factory.create()));
    ASSERT_TRUE(rcf2);

    // And it must always return the same object.
    EXPECT_TRUE(rcf == rcf2);
}

} // end of anonymous namespace
