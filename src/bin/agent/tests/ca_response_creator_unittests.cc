// Copyright (C) 2017 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <agent/ca_command_mgr.h>
#include <agent/ca_response_creator.h>
#include <cc/command_interpreter.h>
#include <http/post_request.h>
#include <http/post_request_json.h>
#include <http/response_json.h>
#include <gtest/gtest.h>
#include <boost/bind.hpp>
#include <boost/pointer_cast.hpp>

using namespace isc::agent;
using namespace isc::config;
using namespace isc::data;
using namespace isc::http;

namespace {

/// @brief Test fixture class for @ref CtrlAgentResponseCreator.
class CtrlAgentResponseCreatorTest : public ::testing::Test {
public:

    /// @brief Constructor.
    ///
    /// Creates instance of the response creator and uses this instance to
    /// create "empty" request. It also removes registered commands from the
    /// command manager.
    CtrlAgentResponseCreatorTest()
        : response_creator_(),
          request_(response_creator_.createNewHttpRequest()) {
        // Deregisters commands.
        CtrlAgentCommandMgr::instance().deregisterAll();
        CtrlAgentCommandMgr::instance().
            registerCommand("foo", boost::bind(&CtrlAgentResponseCreatorTest::
                                               fooCommandHandler,
                                               this, _1, _2));

        // Make sure that the request has been initialized properly.
        if (!request_) {
            ADD_FAILURE() << "CtrlAgentResponseCreator::createNewHttpRequest"
                " returns NULL!";
        }
    }

    /// @brief Destructor.
    ///
    /// Removes registered commands from the command manager.
    virtual ~CtrlAgentResponseCreatorTest() {
        CtrlAgentCommandMgr::instance().deregisterAll();
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
                           const std::string& must_contain) {
        HttpResponsePtr response;
        ASSERT_NO_THROW(
            response = response_creator_.createStockHttpResponse(request_,
                                                                 status_code)
        );
        ASSERT_TRUE(response);
        HttpResponseJsonPtr response_json = boost::dynamic_pointer_cast<
            HttpResponseJson>(response);
        ASSERT_TRUE(response_json);
        // Make sure the response contains the string specified as argument.
        EXPECT_TRUE(response_json->toString().find(must_contain) != std::string::npos);

    }

    /// @brief Handler for the 'foo' test command.
    ///
    /// @param command_name Command name, i.e. 'foo'.
    /// @param command_arguments Command arguments (empty).
    ///
    /// @return Returns response with a single string "bar".
    ConstElementPtr fooCommandHandler(const std::string& /*command_name*/,
                                      const ConstElementPtr& /*command_arguments*/) {
        ElementPtr arguments = Element::createList();
        arguments->add(Element::create("bar"));
        return (createAnswer(CONTROL_RESULT_SUCCESS, arguments));
    }

    /// @brief Instance of the response crator.
    CtrlAgentResponseCreator response_creator_;

    /// @brief Instance of the "empty" request.
    ///
    /// The context belonging to this request may be modified by the unit
    /// tests to verify various scenarios of response creation.
    HttpRequestPtr request_;

};

// This test verifies that the created "empty" request has valid type.
TEST_F(CtrlAgentResponseCreatorTest, createNewHttpRequest) {
    // The request must be of PostHttpRequestJson type.
    PostHttpRequestJsonPtr request_json = boost::dynamic_pointer_cast<
        PostHttpRequestJson>(request_);
    ASSERT_TRUE(request_json);
}

// Test that HTTP version of stock response is set to 1.0 if the request
// context doesn't specify any version.
TEST_F(CtrlAgentResponseCreatorTest, createStockHttpResponseNoVersion) {
    testStockResponse(HttpStatusCode::BAD_REQUEST, "HTTP/1.0 400 Bad Request");
}

// Test that HTTP version of stock response is set to 1.0 if the request
// version is higher than 1.1.
TEST_F(CtrlAgentResponseCreatorTest, createStockHttpResponseHighVersion) {
    request_->context()->http_version_major_ = 2;
    testStockResponse(HttpStatusCode::REQUEST_TIMEOUT,
                      "HTTP/1.0 408 Request Timeout");
}

// Test that the server responds with version 1.1 if request version is 1.1.
TEST_F(CtrlAgentResponseCreatorTest, createStockHttpResponseCorrectVersion) {
    request_->context()->http_version_major_ = 1;
    request_->context()->http_version_minor_ = 1;
    testStockResponse(HttpStatusCode::NO_CONTENT, "HTTP/1.1 204 No Content");
}

// Test successful server response when the client specifies valid command.
TEST_F(CtrlAgentResponseCreatorTest, createDynamicHttpResponse) {
    setBasicContext(request_);

    // Body: "foo" command has been registered in the test fixture constructor.
    request_->context()->body_ = "{ \"command\": \"foo\" }";

    // All requests must be finalized before they can be processed.
    ASSERT_NO_THROW(request_->finalize());

    // Create response from the request.
    HttpResponsePtr response;
    ASSERT_NO_THROW(response = response_creator_.createHttpResponse(request_));
    ASSERT_TRUE(response);

    // Response must be convertible to HttpResponseJsonPtr.
    HttpResponseJsonPtr response_json = boost::dynamic_pointer_cast<
        HttpResponseJson>(response);
    ASSERT_TRUE(response_json);

    // Response must be successful.
    EXPECT_TRUE(response_json->toString().find("HTTP/1.1 200 OK") !=
                std::string::npos);
    // Response must contain JSON body with "result" of 0.
    EXPECT_TRUE(response_json->toString().find("\"result\": 0") !=
                std::string::npos);
}

// This test verifies that Internal Server Error is returned when invalid C++
// request type is used. This is considered an error in the server logic.
TEST_F(CtrlAgentResponseCreatorTest, createDynamicHttpResponseInvalidType) {
    PostHttpRequestPtr request(new PostHttpRequest());
    setBasicContext(request);

    // Body: "list-commands" is natively supported by the command manager.
    request->context()->body_ = "{ \"command\": \"list-commands\" }";

    // All requests must be finalized before they can be processed.
    ASSERT_NO_THROW(request->finalize());

    HttpResponsePtr response;
    ASSERT_NO_THROW(response = response_creator_.createHttpResponse(request));
    ASSERT_TRUE(response);

    // Response must be convertible to HttpResponseJsonPtr.
    HttpResponseJsonPtr response_json = boost::dynamic_pointer_cast<
        HttpResponseJson>(response);
    ASSERT_TRUE(response_json);

    // Response must contain Internal Server Error status code.
    EXPECT_TRUE(response_json->toString().find("HTTP/1.1 500 Internal Server Error") !=
                std::string::npos);

}

}
