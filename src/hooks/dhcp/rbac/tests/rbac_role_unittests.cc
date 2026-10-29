// Copyright (C) 2026 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <testutils/gtest_utils.h>

#include <rbac/rbac_role.h>

using namespace isc;
using namespace isc::data;
using namespace isc::http;
using namespace isc::rbac;
using namespace std;

namespace {

/// @brief Test fixture for checking RBAC roles.
class RoleTest : public ::testing::Test {
public:

    /// @brief Constructor.
    RoleTest() {
    }

    /// @brief Destructor.
    virtual ~RoleTest() = default;

    /// @brief Create HTTP Request.
    ///
    /// @return The HTTP request.
    HttpRequestPtr createHttpRequest() {
        HttpRequestPtr request(new HttpRequest());
        return (request);
    }
};

/// @brief This test verifies that role assignment by remote address works
/// as expected.
TEST_F(RoleTest, remote) {
    RolePtr role(new RemoteRole());
    HttpRequestPtr request = createHttpRequest();
    string ret;
    ASSERT_NO_THROW(ret = role->assign(request));
    EXPECT_TRUE(ret.empty());
    request->setRemote("foo");
    ASSERT_NO_THROW(ret = role->assign(request));
    EXPECT_EQ("foo", ret);
}

/// @brief This test verifies that role assignment by subject name works
/// as expected.
TEST_F(RoleTest, subject) {
    RolePtr role(new SubjectRole());
    HttpRequestPtr request = createHttpRequest();
    string ret;
    ASSERT_NO_THROW(ret = role->assign(request));
    EXPECT_TRUE(ret.empty());
    request->setSubject("foo");
    ASSERT_NO_THROW(ret = role->assign(request));
    EXPECT_EQ("foo", ret);

    EXPECT_FALSE(HttpRequest::recordSubject_);
    role->setup(true);
    EXPECT_TRUE(HttpRequest::recordSubject_);
    role->setup(false);
    EXPECT_FALSE(HttpRequest::recordSubject_);
}

/// @brief This test verifies that role assignment by issuer name works
/// as expected.
TEST_F(RoleTest, issuer) {
    RolePtr role(new IssuerRole());
    HttpRequestPtr request = createHttpRequest();
    string ret;
    ASSERT_NO_THROW(ret = role->assign(request));
    EXPECT_TRUE(ret.empty());
    request->setIssuer("foo");
    ASSERT_NO_THROW(ret = role->assign(request));
    EXPECT_EQ("foo", ret);

    EXPECT_FALSE(HttpRequest::recordIssuer_);
    role->setup(true);
    EXPECT_TRUE(HttpRequest::recordIssuer_);
    role->setup(false);
    EXPECT_FALSE(HttpRequest::recordIssuer_);
}

/// @brief This test verifies that role assignment by basic auth works
/// as expected.
TEST_F(RoleTest, basicAuth) {
    RolePtr role(new BasicAuthRole());
    HttpRequestPtr request = createHttpRequest();
    string ret;
    ASSERT_NO_THROW(ret = role->assign(request));
    EXPECT_TRUE(ret.empty());
    request->setBasicAuth("foo");
    ASSERT_NO_THROW(ret = role->assign(request));
    EXPECT_EQ("foo", ret);

    EXPECT_FALSE(HttpRequest::recordBasicAuth_);
    role->setup(true);
    EXPECT_TRUE(HttpRequest::recordBasicAuth_);
    role->setup(false);
    EXPECT_FALSE(HttpRequest::recordBasicAuth_);
}

/// @brief This test verifies that role assignment by custom value works
/// as expected.
TEST_F(RoleTest, custom) {
    RolePtr role(new CustomRole());
    HttpRequestPtr request = createHttpRequest();
    string ret;
    ASSERT_NO_THROW(ret = role->assign(request));
    EXPECT_TRUE(ret.empty());
    request->setCustom("foo");
    ASSERT_NO_THROW(ret = role->assign(request));
    EXPECT_EQ("foo", ret);
}

/// @brief This test verifies that static role assignment works as expected.
TEST_F(RoleTest, staticValue) {
    RolePtr role(new StaticRole("foo"));
    HttpRequestPtr request = createHttpRequest();
    string ret;
    ASSERT_NO_THROW(ret = role->assign(request));
    EXPECT_EQ("foo", ret);

    boost::shared_ptr<StaticRole> srole =
        boost::dynamic_pointer_cast<StaticRole>(role);
    ASSERT_TRUE(srole);
    EXPECT_EQ("foo", srole->getRole());
}

/// @brief This test verifies that TLS requirement works as expected.
TEST_F(RoleTest, requireTls) {
    HttpRequestPtr request = createHttpRequest();
    EXPECT_FALSE(Role::requireTls(request));
    request->setTls(true);
    EXPECT_TRUE(Role::requireTls(request));
}

/// @brief This test verifies that null request works as expected.
TEST_F(RoleTest, nullRequest) {
    HttpRequestPtr request;
    RolePtr role(new RemoteRole());
    EXPECT_EQ("remote", role->getName());
    string ret;
    ASSERT_NO_THROW(ret = role->assign(request));
    EXPECT_TRUE(ret.empty());

    role.reset(new SubjectRole());
    EXPECT_EQ("subject", role->getName());
    ASSERT_NO_THROW(ret = role->assign(request));
    EXPECT_TRUE(ret.empty());

    role.reset(new IssuerRole());
    EXPECT_EQ("issuer", role->getName());
    ASSERT_NO_THROW(ret = role->assign(request));
    EXPECT_TRUE(ret.empty());

    role.reset(new BasicAuthRole());
    EXPECT_EQ("basic-auth", role->getName());
    ASSERT_NO_THROW(ret = role->assign(request));
    EXPECT_TRUE(ret.empty());

    role.reset(new CustomRole());
    EXPECT_EQ("custom", role->getName());
    ASSERT_NO_THROW(ret = role->assign(request));
    EXPECT_TRUE(ret.empty());

    role.reset(new StaticRole("foo"));
    EXPECT_EQ("static", role->getName());
    ASSERT_NO_THROW(ret = role->assign(request));
    EXPECT_TRUE(ret.empty());

    EXPECT_FALSE(Role::requireTls(request));
}

/// @brief This test verifies that role assignment parsing works as expected.
TEST_F(RoleTest, parse) {
    ConstElementPtr cfg;
    string expected = "parse null role assignment config";
    EXPECT_THROW_MSG(Role::parse(cfg), BadValue, expected);

    cfg = Element::createMap();
    expected = "role assignment config is not a string";
    EXPECT_THROW_MSG(Role::parse(cfg), BadValue, expected);

    cfg = Element::create(string("foobar"));
    expected = "unknown role assignment keyword 'foobar'";
    EXPECT_THROW_MSG(Role::parse(cfg), BadValue, expected);

    cfg = Element::create(string("remote-address"));
    RolePtr role;
    EXPECT_NO_THROW(role = Role::parse(cfg));
    ASSERT_TRUE(role);
    EXPECT_EQ("remote", role->getName());

    cfg = Element::create(string("cert-subject"));
    role.reset();
    EXPECT_NO_THROW(role = Role::parse(cfg));
    ASSERT_TRUE(role);
    EXPECT_EQ("subject", role->getName());

    cfg = Element::create(string("cert-issuer"));
    role.reset();
    EXPECT_NO_THROW(role = Role::parse(cfg));
    ASSERT_TRUE(role);
    EXPECT_EQ("issuer", role->getName());

    cfg = Element::create(string("basic-authentication"));
    role.reset();
    EXPECT_NO_THROW(role = Role::parse(cfg));
    ASSERT_TRUE(role);
    EXPECT_EQ("basic-auth", role->getName());

    cfg = Element::create(string("custom-value"));
    role.reset();
    EXPECT_NO_THROW(role = Role::parse(cfg));
    ASSERT_TRUE(role);
    EXPECT_EQ("custom", role->getName());
}

} // end of anonymous namespace
