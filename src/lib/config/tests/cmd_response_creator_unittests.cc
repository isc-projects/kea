// Copyright (C) 2021-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <cc/command_interpreter.h>
#include <config/command_mgr.h>
#include <config/cmd_response_creator.h>
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

/// @brief Test fixture class for @ref CmdResponseCreator.
class CmdResponseCreatorTest : public ::testing::Test {
public:

    /// @brief Constructor.
    ///
    /// Creates instance of the response creator and uses this instance to
    /// create "empty" request. It also removes registered commands from the
    /// command manager.
    CmdResponseCreatorTest() {
        // Deregisters commands.
        config::CommandMgr::instance().deregisterAll();
        // Register our "foo" command.
        config::CommandMgr::instance().
            registerCommand("foo", std::bind(&CmdResponseCreatorTest::fooCommandHandler,
                                             this, ph::_1, ph::_2));
        // Clear class variables.
        CmdResponseCreator::http_auth_config_.reset();
        CmdResponseCreator::command_accept_list_.clear();
    }

    /// @brief Destructor.
    ///
    /// Removes registered commands from the command manager.
    virtual ~CmdResponseCreatorTest() {
        config::CommandMgr::instance().deregisterAll();
        CmdResponseCreator::http_auth_config_.reset();
        CmdResponseCreator::command_accept_list_.clear();
    }

    /// @brief SetUp function that wraps call to initCreator.
    ///
    /// Creates a default CmdResponseCreator and new HttpRequest.
    virtual void SetUp() {
        initCreator();
    }

    /// @brief Creates a new CmdResponseCreator and new HttpRequest.
    ///
    /// @param emulate_agent_flag enables/disables agent response emulation
    /// in the CmdResponsCreator.
    void initCreator(bool emulate_agent_flag = true) {
        response_creator_.reset(new CmdResponseCreator(emulate_agent_flag));
        request_ = response_creator_->createNewHttpRequest();
        ASSERT_TRUE(request_) << "initCreator failed to create request";
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

    /// @brief Instance of the response creator.
    CmdResponseCreatorPtr response_creator_;

    /// @brief Instance of the "empty" request.
    ///
    /// The context belonging to this request may be modified by the unit
    /// tests to verify various scenarios of response creation.
    HttpRequestPtr request_;
};

// This test verifies that the created "empty" request has valid type.
TEST_F(CmdResponseCreatorTest, createNewHttpRequest) {
    // The request must be of PostHttpRequestJson type.
    PostHttpRequestJsonPtr request_json = boost::dynamic_pointer_cast<
        PostHttpRequestJson>(request_);
    ASSERT_TRUE(request_json);
}

// Test that HTTP version of stock response is set to 1.0 if the request
// context doesn't specify any version.
TEST_F(CmdResponseCreatorTest, createStockHttpResponseNoVersion) {
    testStockResponse(HttpStatusCode::BAD_REQUEST, "HTTP/1.0 400 Bad Request");
}

// Test that HTTP version of stock response is set to 1.0 if the request
// version is higher than 1.1.
TEST_F(CmdResponseCreatorTest, createStockHttpResponseHighVersion) {
    request_->context()->http_version_major_ = 2;
    testStockResponse(HttpStatusCode::REQUEST_TIMEOUT,
                      "HTTP/1.0 408 Request Timeout");
}

// Test that the server responds with version 1.1 if request version is 1.1.
TEST_F(CmdResponseCreatorTest, createStockHttpResponseCorrectVersion) {
    request_->context()->http_version_major_ = 1;
    request_->context()->http_version_minor_ = 1;
    testStockResponse(HttpStatusCode::NO_CONTENT, "HTTP/1.1 204 No Content");
}

// Test successful server response when the client specifies valid command.
TEST_F(CmdResponseCreatorTest, createDynamicHttpResponse) {
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
    ASSERT_TRUE(response_creator_->emulateAgentResponse());
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
TEST_F(CmdResponseCreatorTest, createDynamicHttpResponseNoEmulation) {
    // Recreate the response creator setting emulate_agent_response to false;
    initCreator(false);
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
    ASSERT_FALSE(response_creator_->emulateAgentResponse());
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
TEST_F(CmdResponseCreatorTest, createDynamicHttpResponseInvalidType) {
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

// This test verifies command filtering.
TEST_F(CmdResponseCreatorTest, filterCommand) {
    initCreator(false);
    setBasicContext(request_);
    // For the log message...
    request_->setRemote("127.0.0.1");

    HttpResponseJsonPtr response;
    ConstElementPtr body;
    unordered_set<string> accept;
    ASSERT_NO_THROW(response = response_creator_->filterCommand(request_, body, accept));
    EXPECT_FALSE(response);

    accept.insert("foo");
    ASSERT_NO_THROW(response = response_creator_->filterCommand(request_, body, accept));
    EXPECT_FALSE(response);

    body = Element::createList();
    ASSERT_NO_THROW(response = response_creator_->filterCommand(request_, body, accept));
    EXPECT_FALSE(response);

    body = Element::createMap();
    ASSERT_NO_THROW(response = response_creator_->filterCommand(request_, body, accept));
    EXPECT_FALSE(response);

    body = createCommand("foo", ConstElementPtr());
    ASSERT_NO_THROW(response = response_creator_->filterCommand(request_, body, accept));
    EXPECT_FALSE(response);

    body = createCommand("bar", ConstElementPtr());
    ASSERT_NO_THROW(response = response_creator_->filterCommand(request_, body, accept));
    EXPECT_TRUE(response);
    EXPECT_EQ("HTTP/1.1 403 Forbidden", response->toBriefString());

    accept.clear();
    ASSERT_NO_THROW(response = response_creator_->filterCommand(request_, body, accept));
    EXPECT_FALSE(response);
}

// This test verifies basic HTTP authentication - reject case.
// Empty case was handled in createDynamicHttpResponseNoEmulation.
TEST_F(CmdResponseCreatorTest, basicAuthReject) {
    initCreator(false);
    setBasicContext(request_);

    // Body: "foo" command has been registered in the test fixture constructor.
    request_->context()->body_ = "{ \"command\": \"foo\" }";

    // Add no basic HTTP authentication.

    // All requests must be finalized before they can be processed.
    ASSERT_NO_THROW(request_->finalize());

    // Create basic HTTP authentication configuration.
    CmdResponseCreator::http_auth_config_.reset(new BasicHttpAuthConfig());
    BasicHttpAuthConfigPtr basic =
        boost::dynamic_pointer_cast<BasicHttpAuthConfig>(
            CmdResponseCreator::http_auth_config_);
    ASSERT_TRUE(basic);
    EXPECT_NO_THROW(basic->add("test", "", "123\xa3", ""));

    // Create response from the request.
    HttpResponsePtr response;
    ASSERT_NO_THROW(response = response_creator_->createHttpResponse(request_));
    ASSERT_TRUE(response);

    // Response must not be successful.
    EXPECT_EQ("HTTP/1.1 401 Unauthorized", response->toBriefString());
}

// This test verifies basic HTTP authentication - accept case.
// Empty case was handled in createDynamicHttpResponseNoEmulation.
TEST_F(CmdResponseCreatorTest, basicAuthAccept) {
    initCreator(false);
    setBasicContext(request_);

    // Body: "foo" command has been registered in the test fixture constructor.
    request_->context()->body_ = "{ \"command\": \"foo\" }";

    // Add basic HTTP authentication.
    HttpHeaderContext auth("Authorization", "Basic dGVzdDoxMjPCow==");
    request_->context()->headers_.push_back(auth);

    // All requests must be finalized before they can be processed.
    ASSERT_NO_THROW(request_->finalize());

    // Create basic HTTP authentication configuration.
    CmdResponseCreator::http_auth_config_.reset(new BasicHttpAuthConfig());
    BasicHttpAuthConfigPtr basic =
        boost::dynamic_pointer_cast<BasicHttpAuthConfig>(
            CmdResponseCreator::http_auth_config_);
    ASSERT_TRUE(basic);
    EXPECT_NO_THROW(basic->add("test", "", "123\xa3", ""));

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

// This test verifies command filtering at the HTTP level - reject case.
TEST_F(CmdResponseCreatorTest, filterCommandReject) {
    initCreator(false);
    setBasicContext(request_);
    // For the log message...
    request_->setRemote("127.0.0.1");

    // Body: "bar" command has been registered in the test fixture constructor.
    request_->context()->body_ = "{ \"command\": \"bar\" }";

    // All requests must be finalized before they can be processed.
    ASSERT_NO_THROW(request_->finalize());

    // Add foo in the access list.
    CmdResponseCreator::command_accept_list_.insert("foo");

    // Create response from the request.
    HttpResponsePtr response;
    ASSERT_NO_THROW(response = response_creator_->createHttpResponse(request_));
    ASSERT_TRUE(response);

    // Response must not be successful.
    EXPECT_EQ("HTTP/1.1 403 Forbidden", response->toBriefString());
}

// This test verifies command filtering at the HTTP level - accept case.
TEST_F(CmdResponseCreatorTest, filterCommandAccept) {
    initCreator(false);
    setBasicContext(request_);

    // Body: "foo" command has been registered in the test fixture constructor.
    request_->context()->body_ = "{ \"command\": \"foo\" }";

    // All requests must be finalized before they can be processed.
    ASSERT_NO_THROW(request_->finalize());

    // Add foo in the access list.
    CmdResponseCreator::command_accept_list_.insert("foo");

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
