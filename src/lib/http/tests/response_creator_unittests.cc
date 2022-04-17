// Copyright (C) 2016-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <http/basic_auth.h>
#include <http/basic_auth_config.h>
#include <http/http_types.h>
#include <http/request.h>
#include <http/response.h>
#include <http/response_creator.h>
#include <http/response_json.h>
#include <http/tests/response_test.h>
#include <testutils/log_utils.h>
#include <boost/shared_ptr.hpp>
#include <gtest/gtest.h>

using namespace isc::dhcp::test;
using namespace isc::http;
using namespace isc::http::test;
using namespace std;

namespace {

/// @brief Test HTTP response.
typedef TestHttpResponseBase<HttpResponseJson> Response;

/// @brief Pointer to test HTTP response.
typedef boost::shared_ptr<Response> ResponsePtr;

/// @brief Implementation of the @ref HttpResponseCreator.
class TestHttpResponseCreator : public HttpResponseCreator {
public:

    /// @brief Create a new request.
    ///
    /// @return Pointer to the new instance of the @ref HttpRequest.
    virtual HttpRequestPtr
    createNewHttpRequest() const {
        return (HttpRequestPtr(new HttpRequest()));
    }

private:

    /// @brief Creates HTTP response.
    ///
    /// @param request Pointer to the HTTP request.
    /// @return Pointer to the generated HTTP response.
    virtual HttpResponsePtr
    createStockHttpResponse(const HttpRequestPtr& request,
                            const HttpStatusCode& status_code) const {
        // The request hasn't been finalized so the request object
        // doesn't contain any information about the HTTP version number
        // used. But, the context should have this data (assuming the
        // HTTP version is parsed ok).
        HttpVersion http_version(request->context()->http_version_major_,
                                 request->context()->http_version_minor_);
        // This will generate the response holding JSON content.
        ResponsePtr response(new Response(http_version, status_code));
        response->finalize();
        return (response);
    }

    /// @brief Creates HTTP response.
    ///
    /// @param request Pointer to the HTTP request.
    /// @return Pointer to the generated HTTP OK response with no content.
    virtual HttpResponsePtr
    createDynamicHttpResponse(HttpRequestPtr request) {
        // The simplest thing is to create a response with no content.
        // We don't need content to test our class.
        ResponsePtr response(new Response(request->getHttpVersion(),
                                          HttpStatusCode::OK));
        response->finalize();
        return (response);
    }
};

/// @brief Pointer to test HTTP response creator.
typedef boost::shared_ptr<TestHttpResponseCreator> TestHttpResponseCreatorPtr;

// This test verifies that Bad Request status is generated when the request
// hasn't been finalized.
TEST(HttpResponseCreatorTest, badRequest) {
    HttpResponsePtr response;
    // Create a request but do not finalize it.
    HttpRequestPtr request(new HttpRequest());
    request->context()->http_version_major_ = 1;
    request->context()->http_version_minor_ = 0;
    request->context()->method_ = "GET";
    request->context()->uri_ = "/foo";

    // Use test specific implementation of Response Creator. It should
    // generate HTTP error 400.
    TestHttpResponseCreator creator;
    ASSERT_NO_THROW(response = creator.createHttpResponse(request));
    ASSERT_TRUE(response);

    EXPECT_EQ("HTTP/1.0 400 Bad Request\r\n"
              "Content-Length: 40\r\n"
              "Content-Type: application/json\r\n"
              "Date: Tue, 19 Dec 2016 18:53:35 GMT\r\n\r\n"
              "{ \"result\": 400, \"text\": \"Bad Request\" }",
              response->toString());
}

// This test verifies that response is generated successfully from the
// finalized/parsed request.
TEST(HttpResponseCreatorTest, goodRequest) {
    // There is no credentials so it checks also what happens when
    // authentication is not required.

    HttpResponsePtr response;
    // Create request and finalize it.
    HttpRequestPtr request(new HttpRequest());
    request->context()->http_version_major_ = 1;
    request->context()->http_version_minor_ = 0;
    request->context()->method_ = "GET";
    request->context()->uri_ = "/foo";
    ASSERT_NO_THROW(request->finalize());

    // Use test specific implementation of the Response Creator to generate
    // a response.
    TestHttpResponseCreator creator;
    ASSERT_NO_THROW(response = creator.createHttpResponse(request));
    ASSERT_TRUE(response);

    EXPECT_EQ("HTTP/1.0 200 OK\r\n"
              "Content-Length: 0\r\n"
              "Content-Type: application/json\r\n"
              "Date: Tue, 19 Dec 2016 18:53:35 GMT\r\n\r\n",
              response->toString());
}

/// @brief Test fixture for HTTP response creator authentication.
class HttpResponseCreatorAuthTest : public LogContentTest { };

// This test verifies that missing required authentication header gives
// unauthorized error.
TEST_F(HttpResponseCreatorAuthTest, noAuth) {
    // Create basic HTTP authentication configuration.
    BasicHttpAuthConfigPtr auth_config(new BasicHttpAuthConfig());
    EXPECT_NO_THROW(auth_config->add("test", "", "123\xa3", ""));
    const BasicHttpAuthMap& credentials = auth_config->getCredentialMap();
    auto cred = credentials.find("dGVzdDoxMjPCow==");
    EXPECT_NE(cred, credentials.end());
    EXPECT_EQ(cred->second, "test");
    auth_config->setRealm("ISC.ORG");

    // Create request and finalize it.
    HttpRequestPtr request(new HttpRequest());
    request->context()->http_version_major_ = 1;
    request->context()->http_version_minor_ = 0;
    request->context()->method_ = "GET";
    request->context()->uri_ = "/foo";
    ASSERT_NO_THROW(request->finalize());
    HttpRequest::recordBasicAuth_ = true;

    HttpResponsePtr response;
    TestHttpResponseCreatorPtr creator(new TestHttpResponseCreator());;
    ASSERT_NO_THROW(response = auth_config->checkAuth(*creator, request));
    ASSERT_TRUE(response);

    EXPECT_EQ("HTTP/1.0 401 Unauthorized\r\n"
              "Content-Length: 41\r\n"
              "Content-Type: application/json\r\n"
              "Date: Tue, 19 Dec 2016 18:53:35 GMT\r\n"
              "WWW-Authenticate: Basic realm=\"ISC.ORG\"\r\n\r\n"
              "{ \"result\": 401, \"text\": \"Unauthorized\" }",
              response->toString());

    EXPECT_TRUE(request->getBasicAuth().empty());
    addString("HTTP_CLIENT_REQUEST_NO_AUTH_HEADER received HTTP request "
              "without required authentication header");
    EXPECT_TRUE(checkFile());
}

// This test verifies that too short authentication header is rejected.
TEST_F(HttpResponseCreatorAuthTest, authTooShort) {
    // Create basic HTTP authentication configuration.
    BasicHttpAuthConfigPtr auth_config(new BasicHttpAuthConfig());
    EXPECT_NO_THROW(auth_config->add("test", "", "123\xa3", ""));
    const BasicHttpAuthMap& credentials = auth_config->getCredentialMap();
    auto cred = credentials.find("dGVzdDoxMjPCow==");
    EXPECT_NE(cred, credentials.end());
    EXPECT_EQ(cred->second, "test");
    auth_config->setRealm("ISC.ORG");

    // Create request and finalize it.
    HttpRequestPtr request(new HttpRequest());
    request->context()->http_version_major_ = 1;
    request->context()->http_version_minor_ = 0;
    request->context()->method_ = "GET";
    request->context()->uri_ = "/foo";
    HttpHeaderContext auth("Authorization", "Basic =");
    request->context()->headers_.push_back(auth);
    ASSERT_NO_THROW(request->finalize());
    HttpRequest::recordBasicAuth_ = true;

    HttpResponsePtr response;
    TestHttpResponseCreatorPtr creator(new TestHttpResponseCreator());;
    ASSERT_NO_THROW(response = auth_config->checkAuth(*creator, request));
    ASSERT_TRUE(response);

    EXPECT_EQ("HTTP/1.0 401 Unauthorized\r\n"
              "Content-Length: 41\r\n"
              "Content-Type: application/json\r\n"
              "Date: Tue, 19 Dec 2016 18:53:35 GMT\r\n"
              "WWW-Authenticate: Basic realm=\"ISC.ORG\"\r\n\r\n"
              "{ \"result\": 401, \"text\": \"Unauthorized\" }",
              response->toString());

    EXPECT_TRUE(request->getBasicAuth().empty());
    addString("HTTP_CLIENT_REQUEST_BAD_AUTH_HEADER received HTTP request "
              "with malformed authentication header: "
              "header content is too short");
    EXPECT_TRUE(checkFile());
}

// This test verifies that another authentication schema is rejected.
TEST_F(HttpResponseCreatorAuthTest, badScheme) {
    // Create basic HTTP authentication configuration.
    BasicHttpAuthConfigPtr auth_config(new BasicHttpAuthConfig());
    EXPECT_NO_THROW(auth_config->add("test", "", "123\xa3", ""));
    const BasicHttpAuthMap& credentials = auth_config->getCredentialMap();
    auto cred = credentials.find("dGVzdDoxMjPCow==");
    EXPECT_NE(cred, credentials.end());
    EXPECT_EQ(cred->second, "test");
    auth_config->setRealm("ISC.ORG");

    // Create request and finalize it.
    HttpRequestPtr request(new HttpRequest());
    request->context()->http_version_major_ = 1;
    request->context()->http_version_minor_ = 0;
    request->context()->method_ = "GET";
    request->context()->uri_ = "/foo";
    HttpHeaderContext auth("Authorization", "Basis dGVzdDoxMjPCow==");
    request->context()->headers_.push_back(auth);
    ASSERT_NO_THROW(request->finalize());
    HttpRequest::recordBasicAuth_ = true;

    HttpResponsePtr response;
    TestHttpResponseCreatorPtr creator(new TestHttpResponseCreator());;
    ASSERT_NO_THROW(response = auth_config->checkAuth(*creator, request));
    ASSERT_TRUE(response);

    EXPECT_EQ("HTTP/1.0 401 Unauthorized\r\n"
              "Content-Length: 41\r\n"
              "Content-Type: application/json\r\n"
              "Date: Tue, 19 Dec 2016 18:53:35 GMT\r\n"
              "WWW-Authenticate: Basic realm=\"ISC.ORG\"\r\n\r\n"
              "{ \"result\": 401, \"text\": \"Unauthorized\" }",
              response->toString());

    EXPECT_TRUE(request->getBasicAuth().empty());
    addString("HTTP_CLIENT_REQUEST_BAD_AUTH_HEADER received HTTP request "
              "with malformed authentication header: "
              "not basic authentication");
    EXPECT_TRUE(checkFile());
}

// This test verifies that not matching credential is rejected.
TEST_F(HttpResponseCreatorAuthTest, notMatching) {
    // Create basic HTTP authentication configuration.
    BasicHttpAuthConfigPtr auth_config(new BasicHttpAuthConfig());
    EXPECT_NO_THROW(auth_config->add("test", "", "123\xa3", ""));
    const BasicHttpAuthMap& credentials = auth_config->getCredentialMap();
    auto cred = credentials.find("dGVzdDoxMjPCow==");
    EXPECT_NE(cred, credentials.end());
    EXPECT_EQ(cred->second, "test");
    auth_config->setRealm("ISC.ORG");

    // Create request and finalize it.
    HttpRequestPtr request(new HttpRequest());
    request->context()->http_version_major_ = 1;
    request->context()->http_version_minor_ = 0;
    request->context()->method_ = "GET";
    request->context()->uri_ = "/foo";
    // Slightly different credential...
    HttpHeaderContext auth("Authorization", "Basic dGvZdDoxMjPcOw==");
    request->context()->headers_.push_back(auth);
    ASSERT_NO_THROW(request->finalize());
    HttpRequest::recordBasicAuth_ = true;

    HttpResponsePtr response;
    TestHttpResponseCreatorPtr creator(new TestHttpResponseCreator());;
    ASSERT_NO_THROW(response = auth_config->checkAuth(*creator, request));
    ASSERT_TRUE(response);

    EXPECT_EQ("HTTP/1.0 401 Unauthorized\r\n"
              "Content-Length: 41\r\n"
              "Content-Type: application/json\r\n"
              "Date: Tue, 19 Dec 2016 18:53:35 GMT\r\n"
              "WWW-Authenticate: Basic realm=\"ISC.ORG\"\r\n\r\n"
              "{ \"result\": 401, \"text\": \"Unauthorized\" }",
              response->toString());

    EXPECT_TRUE(request->getBasicAuth().empty());
    addString("HTTP_CLIENT_REQUEST_NOT_AUTHORIZED received HTTP request "
              "with not matching authentication header");
    EXPECT_TRUE(checkFile());
}

// This test verifies that matching credential is accepted.
TEST_F(HttpResponseCreatorAuthTest, matching) {
    // Create basic HTTP authentication configuration.
    BasicHttpAuthConfigPtr auth_config(new BasicHttpAuthConfig());
    EXPECT_NO_THROW(auth_config->add("test", "", "123\xa3", ""));
    const BasicHttpAuthMap& credentials = auth_config->getCredentialMap();
    auto cred = credentials.find("dGVzdDoxMjPCow==");
    EXPECT_NE(cred, credentials.end());
    EXPECT_EQ(cred->second, "test");
    auth_config->setRealm("ISC.ORG");

    // Create request and finalize it.
    HttpRequestPtr request(new HttpRequest());
    request->context()->http_version_major_ = 1;
    request->context()->http_version_minor_ = 0;
    request->context()->method_ = "GET";
    request->context()->uri_ = "/foo";
    HttpHeaderContext auth("Authorization", "Basic dGVzdDoxMjPCow==");
    request->context()->headers_.push_back(auth);
    ASSERT_NO_THROW(request->finalize());
    HttpRequest::recordBasicAuth_ = true;

    HttpResponsePtr response;
    TestHttpResponseCreatorPtr creator(new TestHttpResponseCreator());;
    ASSERT_NO_THROW(response = auth_config->checkAuth(*creator, request));
    EXPECT_FALSE(response);

    EXPECT_EQ("test", request->getBasicAuth());
    addString("HTTP_CLIENT_REQUEST_AUTHORIZED received HTTP request "
              "authorized for 'test'");
    EXPECT_TRUE(checkFile());
    HttpRequest::recordBasicAuth_ = false;
}

}
