// Copyright (C) 2021-2024 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <cc/command_interpreter.h>
#include <config/command_mgr.h>
#include <config/http_command_response_creator.h>
#include <http/basic_auth_config.h>
#include <http/post_request.h>
#include <http/post_request_json.h>
#include <http/response_json.h>

#include <gtest/gtest.h>
#include <boost/pointer_cast.hpp>
#include <functional>

using namespace isc;
using namespace isc::config;
using namespace isc::data;
using namespace isc::http;
using namespace std;
namespace ph = std::placeholders;

namespace {

/// @brief Basic HTTP control socket configuration.
string BASIC_CONFIG = R"(
    {
        "socket-type": "http",
        "socket-address": "127.0.0.1",
        "socket-port": 8000
    }
)";

/// @brief Test fixture class for @ref HttpCommandResponseCreator.
class HttpCommandResponseCreatorTest : public ::testing::Test {
public:

    /// @brief Constructor.
    ///
    /// Creates instance of the response creator and uses this instance to
    /// create "empty" request. It also removes registered commands from the
    /// command manager.
    HttpCommandResponseCreatorTest() {
        // Deregisters commands.
        config::CommandMgr::instance().deregisterAll();
        // Register our "foo" command.
        config::CommandMgr::instance().
            registerCommand("foo", std::bind(&HttpCommandResponseCreatorTest::fooCommandHandler,
                                             this, ph::_1, ph::_2));
    }

    /// @brief Destructor.
    ///
    /// Removes registered commands from the command manager.
    virtual ~HttpCommandResponseCreatorTest() {
        config::CommandMgr::instance().deregisterAll();
    }

    /// @brief Create HTTP control socket configuration (from text).
    ///
    /// @param emulate_agent_flag The emulation flag (default true).
    /// @param auth_config The authentication config (default null).
    void setHttpConfig(bool emulate_agent_flag = true,
                       const HttpAuthConfigPtr& auth_config =
                       HttpAuthConfigPtr()) {
        ElementPtr json;
        ASSERT_NO_THROW(json = Element::fromJSON(BASIC_CONFIG));
        ASSERT_NO_THROW(http_config_.reset(new HttpCommandConfig(json)));
        http_config_->setEmulateAgentResponse(emulate_agent_flag);
        http_config_->setAuthConfig(auth_config);
    }

    /// @brief Create HTTP response creator.
    ///
    /// @param emulate_agent_flag The emulation flag (default true).
    /// @param auth_config The authentication config (default null).
    void setHttpCreator(bool emulate_agent_flag = true,
                        const HttpAuthConfigPtr& auth_config =
                        HttpAuthConfigPtr()) {
        if (!http_config_) {
            setHttpConfig(emulate_agent_flag, auth_config);
        }
        response_creator_.reset(new HttpCommandResponseCreator(http_config_));
        request_ = response_creator_->createNewHttpRequest();
        ASSERT_TRUE(request_) << "setHttpCreator failed to create request";
    }

    /// @brief Fills request context with required data to create new request.
    ///
    /// @param request Request which context should be configured.
    void setBasicContext(const HttpRequestPtr& request) {
        request->context()->method_ = "POST";
        request->context()->http_version_major_ = 1;
        request->context()->http_version_minor_ = 1;
        request->context()->uri_ = "/foo";

        // Content-Type
        HttpHeaderContext content_type;
        content_type.name_ = "Content-Type";
        content_type.value_ = "application/json";
        request->context()->headers_.push_back(content_type);

        // Content-Length
        HttpHeaderContext content_length;
        content_length.name_ = "Content-Length";
        content_length.value_ = "0";
        request->context()->headers_.push_back(content_length);
    }

    /// @brief Test creation of stock response.
    ///
    /// @param status_code Status code to be included in the response.
    /// @param must_contain Text that must be present in the textual
    /// representation of the generated response.
    void testStockResponse(const HttpStatusCode& status_code,
                           const string& must_contain) {
        HttpResponsePtr response;
        ASSERT_NO_THROW(
            response = response_creator_->createStockHttpResponse(request_,
                                                                  status_code)
        );
        ASSERT_TRUE(response);
        HttpResponseJsonPtr response_json = boost::dynamic_pointer_cast<
            HttpResponseJson>(response);
        ASSERT_TRUE(response_json);
        // Make sure the response contains the string specified as argument.
        EXPECT_TRUE(response_json->toString().find(must_contain) != string::npos);

    }

    /// @brief Handler for the 'foo' test command.
    ///
    /// @param command_name Command name, i.e. 'foo'.
    /// @param command_arguments Command arguments (empty).
    ///
    /// @return Returns response with a single string "bar".
    ConstElementPtr fooCommandHandler(const string& /*command_name*/,
                                      const ConstElementPtr& /*command_arguments*/) {
        ElementPtr arguments = Element::createList();
        arguments->add(Element::create("bar"));
        return (createAnswer(CONTROL_RESULT_SUCCESS, arguments));
    }

    /// @brief HTTP control socket configuration.
    HttpCommandConfigPtr http_config_;

    /// @brief Instance of the response creator.
    HttpCommandResponseCreatorPtr response_creator_;

    /// @brief Instance of the "empty" request.
    ///
    /// The context belonging to this request may be modified by the unit
    /// tests to verify various scenarios of response creation.
    HttpRequestPtr request_;
};

// This test verifies that the created "empty" request has valid type.
TEST_F(HttpCommandResponseCreatorTest, createNewHttpRequest) {
    setHttpCreator();

    // The request must be of PostHttpRequestJson type.
    PostHttpRequestJsonPtr request_json = boost::dynamic_pointer_cast<
        PostHttpRequestJson>(request_);
    ASSERT_TRUE(request_json);
}

// Test that HTTP version of stock response is set to 1.0 if the request
// context doesn't specify any version.
TEST_F(HttpCommandResponseCreatorTest, createStockHttpResponseNoVersion) {
    setHttpCreator();

    testStockResponse(HttpStatusCode::BAD_REQUEST, "HTTP/1.0 400 Bad Request");
}

// Test that HTTP version of stock response is set to 1.0 if the request
// version is higher than 1.1.
TEST_F(HttpCommandResponseCreatorTest, createStockHttpResponseHighVersion) {
    setHttpCreator();

    request_->context()->http_version_major_ = 2;
    testStockResponse(HttpStatusCode::REQUEST_TIMEOUT,
                      "HTTP/1.0 408 Request Timeout");
}

// Test that the server responds with version 1.1 if request version is 1.1.
TEST_F(HttpCommandResponseCreatorTest, createStockHttpResponseCorrectVersion) {
    setHttpCreator();

    request_->context()->http_version_major_ = 1;
    request_->context()->http_version_minor_ = 1;
    testStockResponse(HttpStatusCode::NO_CONTENT, "HTTP/1.1 204 No Content");
}

// Test successful server response when the client specifies valid command.
TEST_F(HttpCommandResponseCreatorTest, createDynamicHttpResponse) {
    setHttpCreator();

    setBasicContext(request_);

    // Body: "foo" command has been registered in the test fixture constructor.
    request_->context()->body_ = "{ \"command\": \"foo\" }";

    // All requests must be finalized before they can be processed.
    ASSERT_NO_THROW(request_->finalize());

    // Create response from the request.
    HttpResponsePtr response;
    ASSERT_NO_THROW(response = response_creator_->createHttpResponse(request_));
    ASSERT_TRUE(response);

    // Response must be convertible to HttpResponseJsonPtr.
    HttpResponseJsonPtr response_json = boost::dynamic_pointer_cast<
        HttpResponseJson>(response);
    ASSERT_TRUE(response_json);

    // Response should be in a list by default.
    ASSERT_TRUE(http_config_->getEmulateAgentResponse());
    ASSERT_TRUE(response_json->getBodyAsJson()->getType() == Element::list)
                << "response is not a list: " << response_json->toString();

    // Response must be successful.
    EXPECT_TRUE(response_json->toString().find("HTTP/1.1 200 OK") !=
                string::npos);

    // Response must contain JSON body with "result" of 0.
    EXPECT_TRUE(response_json->toString().find("\"result\": 0") !=
                string::npos);
}

// Test successful server response without emulating agent response.
TEST_F(HttpCommandResponseCreatorTest, createDynamicHttpResponseNoEmulation) {
    // Create the response creator setting emulate_agent_response to false;
    setHttpCreator(false);

    setBasicContext(request_);

    // Body: "foo" command has been registered in the test fixture constructor.
    request_->context()->body_ = "{ \"command\": \"foo\" }";

    // All requests must be finalized before they can be processed.
    ASSERT_NO_THROW(request_->finalize());

    // Create response from the request.
    HttpResponsePtr response;
    ASSERT_NO_THROW(response = response_creator_->createHttpResponse(request_));
    ASSERT_TRUE(response);

    // Response must be convertible to HttpResponseJsonPtr.
    HttpResponseJsonPtr response_json = boost::dynamic_pointer_cast<
        HttpResponseJson>(response);
    ASSERT_TRUE(response_json);

    // Response should be a map that is not enclosed in a list.
    ASSERT_FALSE(http_config_->getEmulateAgentResponse());
    ASSERT_TRUE(response_json->getBodyAsJson()->getType() == Element::map)
                << "response is not a map: " << response_json->toString();

    // Response must be successful.
    EXPECT_TRUE(response_json->toString().find("HTTP/1.1 200 OK") !=
                string::npos);

    // Response must contain JSON body with "result" of 0.
    EXPECT_TRUE(response_json->toString().find("\"result\": 0") !=
                string::npos);
}

// This test verifies that Internal Server Error is returned when invalid C++
// request type is used. This is considered an error in the server logic.
TEST_F(HttpCommandResponseCreatorTest, createDynamicHttpResponseInvalidType) {
    setHttpCreator();

    PostHttpRequestPtr request(new PostHttpRequest());
    setBasicContext(request);

    // Body: "list-commands" is natively supported by the command manager.
    request->context()->body_ = "{ \"command\": \"list-commands\" }";

    // All requests must be finalized before they can be processed.
    ASSERT_NO_THROW(request->finalize());

    HttpResponsePtr response;
    ASSERT_NO_THROW(response = response_creator_->createHttpResponse(request));
    ASSERT_TRUE(response);

    // Response must be convertible to HttpResponseJsonPtr.
    HttpResponseJsonPtr response_json = boost::dynamic_pointer_cast<
        HttpResponseJson>(response);
    ASSERT_TRUE(response_json);

    // Response must contain Internal Server Error status code.
    EXPECT_TRUE(response_json->toString().find("HTTP/1.1 500 Internal Server Error") !=
                string::npos);
}

// This test verifies basic HTTP authentication - reject case.
// Empty case was handled in createDynamicHttpResponseNoEmulation.
TEST_F(HttpCommandResponseCreatorTest, basicAuthReject) {
    // Create basic HTTP authentication configuration.
    BasicHttpAuthConfigPtr basic(new BasicHttpAuthConfig());
    EXPECT_NO_THROW(basic->add("test", "", "123\xa3", ""));
    setHttpCreator(false, basic);

    setBasicContext(request_);

    // Body: "foo" command has been registered in the test fixture constructor.
    request_->context()->body_ = "{ \"command\": \"foo\" }";

    // Add no basic HTTP authentication.

    // All requests must be finalized before they can be processed.
    ASSERT_NO_THROW(request_->finalize());

    // Create response from the request.
    HttpResponsePtr response;
    ASSERT_NO_THROW(response = response_creator_->createHttpResponse(request_));
    ASSERT_TRUE(response);

    // Response must not be successful.
    EXPECT_EQ("HTTP/1.1 401 Unauthorized", response->toBriefString());
}

// This test verifies basic HTTP authentication - accept case.
// Empty case was handled in createDynamicHttpResponseNoEmulation.
TEST_F(HttpCommandResponseCreatorTest, basicAuthAccept) {
    // Create basic HTTP authentication configuration.
    BasicHttpAuthConfigPtr basic(new BasicHttpAuthConfig());
    EXPECT_NO_THROW(basic->add("test", "", "123\xa3", ""));
    setHttpCreator(false, basic);

    setBasicContext(request_);

    // Body: "foo" command has been registered in the test fixture constructor.
    request_->context()->body_ = "{ \"command\": \"foo\" }";

    // Add basic HTTP authentication.
    HttpHeaderContext auth("Authorization", "Basic dGVzdDoxMjPCow==");
    request_->context()->headers_.push_back(auth);

    // All requests must be finalized before they can be processed.
    ASSERT_NO_THROW(request_->finalize());

    // Create response from the request.
    HttpResponsePtr response;
    ASSERT_NO_THROW(response = response_creator_->createHttpResponse(request_));
    ASSERT_TRUE(response);

    // Response must be convertible to HttpResponseJsonPtr.
    HttpResponseJsonPtr response_json = boost::dynamic_pointer_cast<
        HttpResponseJson>(response);
    ASSERT_TRUE(response_json);

    // Response must be successful.
    EXPECT_TRUE(response_json->toString().find("HTTP/1.1 200 OK") !=
                string::npos);

    // Response must contain JSON body with "result" of 0.
    EXPECT_TRUE(response_json->toString().find("\"result\": 0") !=
                string::npos);
}

}
