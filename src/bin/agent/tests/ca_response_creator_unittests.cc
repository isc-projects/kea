// Copyright (C) 2017-2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <agent/ca_controller.h>
#include <agent/ca_process.h>
#include <agent/ca_command_mgr.h>
#include <agent/ca_response_creator.h>
#include <cc/command_interpreter.h>
#include <cryptolink/crypto_rng.h>
#include <hooks/hooks_manager.h>
#include <http/basic_auth_config.h>
#include <http/post_request.h>
#include <http/post_request_json.h>
#include <http/response_json.h>
#include <process/testutils/d_test_stubs.h>
#include <agent/tests/test_basic_auth_libraries.h>
#include <gtest/gtest.h>
#include <boost/pointer_cast.hpp>
#include <functional>

using namespace isc;
using namespace isc::agent;
using namespace isc::config;
using namespace isc::data;
using namespace isc::hooks;
using namespace isc::http;
using namespace isc::process;
namespace ph = std::placeholders;

namespace {

/// @brief Test fixture class for @ref CtrlAgentResponseCreator.
class CtrlAgentResponseCreatorTest : public DControllerTest {
public:

    /// @brief Constructor.
    ///
    /// Creates instance of the response creator and uses this instance to
    /// create "empty" request. It also removes registered commands from the
    /// command manager.
    CtrlAgentResponseCreatorTest()
        : DControllerTest(CtrlAgentController::instance),
          response_creator_(),
          request_(response_creator_.createNewHttpRequest()) {
        // Deregisters commands.
        CtrlAgentCommandMgr::instance().deregisterAll();
        CtrlAgentCommandMgr::instance().
            registerCommand("foo", std::bind(&CtrlAgentResponseCreatorTest::
                                             fooCommandHandler,
                                             this, ph::_1, ph::_2));

        // Make sure that the request has been initialized properly.
        if (!request_) {
            ADD_FAILURE() << "CtrlAgentResponseCreator::createNewHttpRequest"
                " returns NULL!";
        }
        HttpRequest::recordBasicAuth_ = true;
        // Initialize process and cfgmgr.
        try {
            initProcess();
            static_cast<void>(getCtrlAgentCfgContext());
        } catch (const std::exception& ex) {
            ADD_FAILURE() << "Initialization failed: " << ex.what();
        }
    }

    /// @brief Destructor.
    ///
    /// Removes registered commands from the command manager.
    virtual ~CtrlAgentResponseCreatorTest() {
        HttpRequest::recordBasicAuth_ = false;
        CtrlAgentCommandMgr::instance().deregisterAll();
        HooksManager::prepareUnloadLibraries();
        static_cast<void>(HooksManager::unloadLibraries());
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

    /// @brief Returns a pointer to the configuration context.
    CtrlAgentCfgContextPtr getCtrlAgentCfgContext() {
        CtrlAgentProcessPtr process =
            boost::dynamic_pointer_cast<CtrlAgentProcess>(getProcess());
        if (!process) {
            isc_throw(Unexpected, "no process");
        }
        CtrlAgentCfgMgrPtr cfgmgr = process->getCtrlAgentCfgMgr();
        if (!cfgmgr) {
            isc_throw(Unexpected, "no cfgmgr");
        }
        CtrlAgentCfgContextPtr ctx = cfgmgr->getCtrlAgentCfgContext();
        if (!ctx) {
            isc_throw(Unexpected, "no context");
        }
        return (ctx);
    }

    /// @brief Instance of the response creator.
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

// This test verifies that Unauthorized is returned when authentication is
// required but not provided by request.
TEST_F(CtrlAgentResponseCreatorTest, noAuth) {
    setBasicContext(request_);

    // Body: "list-commands" is natively supported by the command manager.
    request_->context()->body_ = "{ \"command\": \"list-commands\" }";

    // All requests must be finalized before they can be processed.
    ASSERT_NO_THROW(request_->finalize());

    // Require authentication.
    CtrlAgentCfgContextPtr ctx = getCtrlAgentCfgContext();
    ASSERT_TRUE(ctx);
    BasicHttpAuthConfigPtr auth(new BasicHttpAuthConfig());
    ASSERT_NO_THROW(ctx->setAuthConfig(auth));
    auth->setRealm("ISC.ORG");
    auth->add("foo", "", "bar", "");

    HttpResponsePtr response;
    ASSERT_NO_THROW(response = response_creator_.createHttpResponse(request_));
    EXPECT_TRUE(request_->getBasicAuth().empty());
    ASSERT_TRUE(response);

    // Response must be convertible to HttpResponseJsonPtr.
    HttpResponseJsonPtr response_json = boost::dynamic_pointer_cast<
        HttpResponseJson>(response);
    ASSERT_TRUE(response_json);

    // Response must contain Unauthorized status code.
    std::string expected = "HTTP/1.1 401 Unauthorized";
    EXPECT_TRUE(response_json->toString().find(expected) != std::string::npos);
    // Reponse should contain WWW-Authenticate header with configured realm.
    expected = "WWW-Authenticate: Basic realm=\"ISC.ORG\"";
    EXPECT_TRUE(response_json->toString().find(expected) != std::string::npos);
}

// Test successful server response when the client is authenticated.
TEST_F(CtrlAgentResponseCreatorTest, basicAuth) {
    setBasicContext(request_);

    // Body: "list-commands" is natively supported by the command manager.
    request_->context()->body_ = "{ \"command\": \"list-commands\" }";

    // Add basic HTTP authentication header.
    const BasicHttpAuth& basic_auth = BasicHttpAuth("foo", "bar");
    const BasicAuthHttpHeaderContext& basic_auth_header =
        BasicAuthHttpHeaderContext(basic_auth);
    request_->context()->headers_.push_back(basic_auth_header);

    // All requests must be finalized before they can be processed.
    ASSERT_NO_THROW(request_->finalize());

    // Require authentication.
    CtrlAgentCfgContextPtr ctx = getCtrlAgentCfgContext();
    ASSERT_TRUE(ctx);
    BasicHttpAuthConfigPtr auth(new BasicHttpAuthConfig());
    ASSERT_NO_THROW(ctx->setAuthConfig(auth));
    // In fact the realm is used only on errors... set it anyway.
    auth->setRealm("ISC.ORG");
    auth->add("foo", "", "bar", "");

    HttpResponsePtr response;
    ASSERT_NO_THROW(response = response_creator_.createHttpResponse(request_));
    EXPECT_EQ("foo", request_->getBasicAuth());
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

// This test verifies that Unauthorized is returned when authentication is
// required but not provided by request using the hook.
TEST_F(CtrlAgentResponseCreatorTest, hookNoAuth) {
    setBasicContext(request_);

    // Body: "list-commands" is natively supported by the command manager.
    // We add a random value in the extra entry: see next unit test
    // for an explanation about how it is used.
    auto r32 = isc::cryptolink::random(4);
    ASSERT_EQ(4, r32.size());
    int extra = r32[0];
    extra = (extra << 8) | r32[1];
    extra = (extra << 8) | r32[2];
    extra = (extra << 8) | r32[3];
    request_->context()->body_ = "{ \"command\": \"list-commands\", ";
    request_->context()->body_ += "\"extra\": " + std::to_string(extra) + " }";

    // All requests must be finalized before they can be processed.
    ASSERT_NO_THROW(request_->finalize());

    // Setup hook.
    CtrlAgentCfgContextPtr ctx = getCtrlAgentCfgContext();
    ASSERT_TRUE(ctx);
    HooksConfig& hooks_cfg = ctx->getHooksConfig();
    std::string auth_cfg = "{ \"config\": {\n"
        "\"type\": \"basic\",\n"
        "\"realm\": \"ISC.ORG\",\n"
        "\"clients\": [{\n"
        " \"user\": \"foo\",\n"
        " \"password\": \"bar\"\n"
        " }]}}";
    ConstElementPtr auth_json;
    ASSERT_NO_THROW(auth_json = Element::fromJSON(auth_cfg));
    hooks_cfg.add(std::string(BASIC_AUTH_LIBRARY), auth_json);
    ASSERT_NO_THROW(hooks_cfg.loadLibraries(false));

    HttpResponsePtr response;
    ASSERT_NO_THROW(response = response_creator_.createHttpResponse(request_));
    EXPECT_TRUE(request_->getBasicAuth().empty());
    ASSERT_TRUE(response);

    // Request should have no extra.
    EXPECT_EQ("{ \"command\": \"list-commands\" }",
              request_->context()->body_);

    // Response must be convertible to HttpResponseJsonPtr.
    HttpResponseJsonPtr response_json = boost::dynamic_pointer_cast<
        HttpResponseJson>(response);
    ASSERT_TRUE(response_json);

    // Response must contain Unauthorized status code.
    std::string expected = "HTTP/1.1 401 Unauthorized";
    EXPECT_TRUE(response_json->toString().find(expected) != std::string::npos);
    // Reponse should contain WWW-Authenticate header with configured realm.
    expected = "WWW-Authenticate: Basic realm=\"ISC.ORG\"";
    EXPECT_TRUE(response_json->toString().find(expected) != std::string::npos);
}

// Test successful server response when the client is authenticated.
TEST_F(CtrlAgentResponseCreatorTest, hookBasicAuth) {
    setBasicContext(request_);

    // Body: "list-commands" is natively supported by the command manager.
    // We add a random value in the extra entry:
    //  - this proves that the auth callout can get the request argument
    //  - this proves that the auth callout can modify the request argument
    //    before the request is executed (the extra entry if still present
    //    would make the command to be rejected as malformed)
    //  - this proves that a value can be communicate between the auth
    //    and response callout points
    //  - this proves that the response callout can get the response argument
    //  - this proves that the response callout can modify the response
    //    argument
    auto r32 = isc::cryptolink::random(4);
    ASSERT_EQ(4, r32.size());
    int extra = r32[0];
    extra = (extra << 8) | r32[1];
    extra = (extra << 8) | r32[2];
    extra = (extra << 8) | r32[3];
    if (extra == 0) {
        extra = 1;
    }
    std::string extra_str = std::to_string(extra);
    request_->context()->body_ = "{ \"command\": \"list-commands\", ";
    request_->context()->body_ += "\"extra\": " + extra_str + " }";

    // Add basic HTTP authentication header.
    const BasicHttpAuth& basic_auth = BasicHttpAuth("foo", "bar");
    const BasicAuthHttpHeaderContext& basic_auth_header =
        BasicAuthHttpHeaderContext(basic_auth);
    request_->context()->headers_.push_back(basic_auth_header);

    // All requests must be finalized before they can be processed.
    ASSERT_NO_THROW(request_->finalize());

    // Setup hook.
    CtrlAgentCfgContextPtr ctx = getCtrlAgentCfgContext();
    ASSERT_TRUE(ctx);
    HooksConfig& hooks_cfg = ctx->getHooksConfig();
    std::string auth_cfg = "{ \"config\": {\n"
        "\"type\": \"basic\",\n"
        "\"realm\": \"ISC.ORG\",\n"
        "\"clients\": [{\n"
        " \"user\": \"foo\",\n"
        " \"password\": \"bar\"\n"
        " }]}}";
    ConstElementPtr auth_json;
    ASSERT_NO_THROW(auth_json = Element::fromJSON(auth_cfg));
    hooks_cfg.add(std::string(BASIC_AUTH_LIBRARY), auth_json);
    ASSERT_NO_THROW(hooks_cfg.loadLibraries(false));

    HttpResponsePtr response;
    ASSERT_NO_THROW(response = response_creator_.createHttpResponse(request_));
    EXPECT_EQ("foo", request_->getBasicAuth());
    ASSERT_TRUE(response);

    // Request should have no extra.
    EXPECT_EQ("{ \"command\": \"list-commands\" }",
              request_->context()->body_);

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
    // Response must contain JSON body with "comment": "got".
    std::string expected = "\"got\": " + extra_str + ", ";
    EXPECT_TRUE(response_json->toString().find(expected) !=
                std::string::npos);
}

}
