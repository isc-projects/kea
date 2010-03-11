// Copyright (C) 2010  Internet Systems Consortium, Inc. ("ISC")
//
// Permission to use, copy, modify, and/or distribute this software for any
// purpose with or without fee is hereby granted, provided that the above
// copyright notice and this permission notice appear in all copies.
//
// THE SOFTWARE IS PROVIDED "AS IS" AND ISC DISCLAIMS ALL WARRANTIES WITH
// REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
// AND FITNESS.  IN NO EVENT SHALL ISC BE LIABLE FOR ANY SPECIAL, DIRECT,
// INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
// LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE
// OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
// PERFORMANCE OF THIS SOFTWARE.

// $Id$

#include <gtest/gtest.h>

#include <dns/buffer.h>
#include <dns/name.h>
#include <dns/message.h>
#include <dns/messagerenderer.h>
#include <dns/rrclass.h>
#include <dns/rrtype.h>

#include <auth/auth_srv.h>

#include <dns/tests/unittest_util.h>

using isc::UnitTestUtil;
using namespace std;
using namespace isc::dns;

namespace {
class AuthSrvTest : public ::testing::Test {
protected:
    AuthSrvTest() : request_message(Message::RENDER),
                    parse_message(Message::PARSE),
                    qname("www.example.com"),
                    qclass(RRClass::IN()), qtype(RRType::A()),
                    request_obuffer(0), request_renderer(request_obuffer),
                    response_obuffer(0), response_renderer(response_obuffer)
    {}
    AuthSrv server;
    Message request_message;
    Message parse_message;
    Name qname;
    RRClass qclass;
    RRType qtype;
    OutputBuffer request_obuffer;
    MessageRenderer request_renderer;
    OutputBuffer response_obuffer;
    MessageRenderer response_renderer;
    vector<uint8_t> data;
};

static void
createDataFromFile(const char* const datafile, vector<uint8_t>& data) {
    UnitTestUtil::readWireData(datafile, data);
    InputBuffer buffer(&data[0], data.size());
}

TEST_F(AuthSrvTest, ManyQuery) {
    createDataFromFile("testdata/iquery_fromWire", data);
    InputBuffer buffer(&data[0], data.size());
    EXPECT_EQ(0, server.processMessage(buffer, parse_message, response_renderer,
                                       true, false));
}
}
