// Copyright (C) 2016 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <http/http_types.h>
#include <http/response.h>
#include <gtest/gtest.h>
#include <sstream>

using namespace isc::http;

namespace {

TEST(HttpResponseTest, construction) {
    const std::string sample_body =
        "<html>"
        "<head><title>Kea page title</title></head>"
        "<body><h1>Some header</h1></body>"
        "</html>";

    HttpResponse response(HttpVersion(1, 0), HttpStatusCode::OK);
    response.addHeader("Content-Type", "text/html");
    response.addHeader("Host", "kea.example.org");
    response.setBody(sample_body);

    std::ostringstream response_string;
    response_string <<
        "HTTP/1.0 200 OK\r\n"
        "Content-Type: text/html\r\n"
        "Host: kea.example.org\r\n"
        "Content-Length: " << sample_body.length()
                    << "\r\n\r\n" << sample_body;
    EXPECT_EQ(response_string.str(), response.toString());
}

}
