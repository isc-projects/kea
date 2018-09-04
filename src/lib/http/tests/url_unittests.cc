// Copyright (C) 2017-2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <http/url.h>
#include <gtest/gtest.h>
#include <string>

using namespace isc::http;

namespace {

/// @brief Test fixture class for @c Url class.
class UrlTest : public ::testing::Test {
public:

    /// @brief Test valid URL.
    ///
    /// @param text_url URL is the text form.
    /// @param expected_scheme Expected scheme.
    /// @param expected_hostname Expected hostname.
    /// @param expected_port Expected port.
    /// @param expected_path Expected path.
    void testValidUrl(const std::string& text_url,
                      const Url::Scheme& expected_scheme,
                      const std::string& expected_hostname,
                      const unsigned expected_port,
                      const std::string& expected_path) {
        Url url(text_url);
        ASSERT_TRUE(url.isValid()) << url.getErrorMessage();
        EXPECT_EQ(expected_scheme, url.getScheme());
        EXPECT_EQ(expected_hostname, url.getStrippedHostname());
        EXPECT_EQ(expected_port, url.getPort());
        EXPECT_EQ(expected_path, url.getPath());
    }

    /// @brief Test invalid URL.
    ///
    /// @param text_url URL is the text form.
    void testInvalidUrl(const std::string& text_url) {
        Url url(text_url);
        EXPECT_FALSE(url.isValid());
    }
};

// URL contains scheme and hostname.
TEST_F(UrlTest, schemeHostname) {
    testValidUrl("http://example.org", Url::HTTP, "example.org", 0, "");
}

// URL contains scheme, hostname and slash.
TEST_F(UrlTest, schemeHostnameSlash) {
    testValidUrl("http://example.org/", Url::HTTP, "example.org", 0, "/");
}

// URL contains scheme, IPv6 address and slash.
TEST_F(UrlTest, schemeIPv6AddressSlash) {
    testValidUrl("http://[2001:db8:1::100]/", Url::HTTP, "2001:db8:1::100", 0, "/");
}

// URL contains scheme, IPv4 address and slash.
TEST_F(UrlTest, schemeIPv4AddressSlash) {
    testValidUrl("http://192.0.2.2/", Url::HTTP, "192.0.2.2", 0, "/");
}

// URL contains scheme, hostname and path.
TEST_F(UrlTest, schemeHostnamePath) {
    testValidUrl("http://example.org/some/path", Url::HTTP, "example.org", 0,
                 "/some/path");
}

// URL contains scheme, hostname and port.
TEST_F(UrlTest, schemeHostnamePort) {
    testValidUrl("http://example.org:8080/", Url::HTTP, "example.org", 8080, "/");
}

// URL contains scheme, hostname, port and slash.
TEST_F(UrlTest, schemeHostnamePortSlash) {
    testValidUrl("http://example.org:8080/", Url::HTTP, "example.org", 8080, "/");
}

// URL contains scheme, IPv6 address and port.
TEST_F(UrlTest, schemeIPv6AddressPort) {
    testValidUrl("http://[2001:db8:1::1]:8080/", Url::HTTP, "2001:db8:1::1", 8080, "/");
}

// URL contains scheme, hostname, port and path.
TEST_F(UrlTest, schemeHostnamePortPath) {
    testValidUrl("http://example.org:8080/path/", Url::HTTP, "example.org", 8080,
                 "/path/");
}

// URL contains https scheme, hostname, port and path.
TEST_F(UrlTest, secureSchemeHostnamePortPath) {
    testValidUrl("https://example.org:8080/path/", Url::HTTPS, "example.org", 8080,
                 "/path/");
}

// Tests various invalid URLS.
TEST_F(UrlTest, invalidUrls) {
    testInvalidUrl("example.org");
    testInvalidUrl("file://example.org");
    testInvalidUrl("http//example.org");
    testInvalidUrl("http:/example.org");
    testInvalidUrl("http://");
    testInvalidUrl("http://[]");
    testInvalidUrl("http://[2001:db8:1::1");
    testInvalidUrl("http://example.org:");
    testInvalidUrl("http://example.org:abc");
}

}
