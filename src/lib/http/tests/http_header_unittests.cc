// Copyright (C) 2017 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <exceptions/exceptions.h>
#include <http/http_header.h>
#include <gtest/gtest.h>

using namespace isc;
using namespace isc::http;

namespace {

// Test that HTTP header can be created.
TEST(HttpHeader, create) {
    HttpHeader hdr("Content-Type", "application/json");
    EXPECT_EQ("Content-Type", hdr.getName());
    EXPECT_EQ("application/json", hdr.getValue());
}

// Test that the numeric value can be retrieved from a header and that
// an exception is thrown if the header value is not a valid number.
TEST(HttpHeader, getUint64Value) {
    HttpHeader hdr64("Content-Length", "64");
    EXPECT_EQ(64, hdr64.getUint64Value());

    HttpHeader hdr_foo("Content-Length", "foo");
    EXPECT_THROW(hdr_foo.getUint64Value(), isc::BadValue);
}

// Test that header name can be retrieved in lower case.
TEST(HttpHeader, getLowerCaseName) {
    HttpHeader hdr("ConnectioN", "Keep-Alive");
    EXPECT_EQ("connection", hdr.getLowerCaseName());
}

// Test that header value can be retrieved in lower case.
TEST(HttpHeader, getLowerCaseValue) {
    HttpHeader hdr("Connection", "Keep-Alive");
    EXPECT_EQ("keep-alive", hdr.getLowerCaseValue());
}

// Test that header value comparison is case insensitive.
TEST(HttpHeader, equalsCaseInsensitive) {
    HttpHeader hdr("Connection", "KeEp-ALIve");
    EXPECT_TRUE(hdr.isValueEqual("keep-alive"));
    EXPECT_TRUE(hdr.isValueEqual("KEEP-ALIVE"));
    EXPECT_TRUE(hdr.isValueEqual("kEeP-AlIvE"));
}

} // end of anonymous namespace
