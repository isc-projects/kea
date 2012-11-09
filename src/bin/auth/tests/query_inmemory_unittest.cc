// Copyright (C) 2012  Internet Systems Consortium, Inc. ("ISC")
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

#include <dns/name.h>
#include <dns/message.h>
#include <dns/rcode.h>
#include <dns/opcode.h>

#include <cc/data.h>

#include <datasrc/client_list.h>

#include <auth/query.h>

#include <testutils/dnsmessage_test.h>

#include <gtest/gtest.h>

#include <string>

using namespace isc::dns;
using namespace isc::auth;
using namespace isc::testutils;
using isc::datasrc::ConfigurableClientList;
using std::string;

namespace {

// The DNAME to do tests against
const char* const dname_txt =
    "dname.example.com. 3600 IN DNAME "
    "somethinglong.dnametarget.example.com.\n";
// This is not inside the zone, this is created at runtime
const char* const synthetized_cname_txt =
    "www.dname.example.com. 3600 IN CNAME "
    "www.somethinglong.dnametarget.example.com.\n";

// This is a subset of QueryTest using (sbuset of) the same test data, but
// with the production in-memory data source.  Both tests should be eventually
// unified to avoid duplicates.
class InMemoryQueryTest : public ::testing::Test {
protected:
    InMemoryQueryTest() : list(RRClass::IN()), response(Message::RENDER) {
        response.setRcode(Rcode::NOERROR());
        response.setOpcode(Opcode::QUERY());
        list.configure(isc::data::Element::fromJSON(
                           "[{\"type\": \"MasterFiles\","
                           "  \"cache-enable\": true, "
                           "  \"params\": {\"example.com\": \"" +
                           string(TEST_OWN_DATA_DIR "/example.zone") +
                           "\"}}]"), true);
    }

    ConfigurableClientList list;
    Message response;
    Query query;
};

// A wrapper to check resulting response message commonly used in
// tests below.
// check_origin needs to be specified only when the authority section has
// an SOA RR.  The interface is not generic enough but should be okay
// for our test cases in practice.
void
responseCheck(Message& response, const isc::dns::Rcode& rcode,
              unsigned int flags, const unsigned int ancount,
              const unsigned int nscount, const unsigned int arcount,
              const char* const expected_answer,
              const char* const expected_authority,
              const char* const expected_additional,
              const Name& check_origin = Name::ROOT_NAME())
{
    // In our test cases QID, Opcode, and QDCOUNT should be constant, so
    // we don't bother the test cases specifying these values.
    headerCheck(response, response.getQid(), rcode, Opcode::QUERY().getCode(),
                flags, 0, ancount, nscount, arcount);
    if (expected_answer != NULL) {
        rrsetsCheck(expected_answer,
                    response.beginSection(Message::SECTION_ANSWER),
                    response.endSection(Message::SECTION_ANSWER),
                    check_origin);
    }
    if (expected_authority != NULL) {
        rrsetsCheck(expected_authority,
                    response.beginSection(Message::SECTION_AUTHORITY),
                    response.endSection(Message::SECTION_AUTHORITY),
                    check_origin);
    }
    if (expected_additional != NULL) {
        rrsetsCheck(expected_additional,
                    response.beginSection(Message::SECTION_ADDITIONAL),
                    response.endSection(Message::SECTION_ADDITIONAL));
    }
}

/*
 * Test a query under a domain with DNAME. We should get a synthetized CNAME
 * as well as the DNAME.
 *
 * TODO: Once we have CNAME chaining, check it works with synthetized CNAMEs
 * as well. This includes tests pointing inside the zone, outside the zone,
 * pointing to NXRRSET and NXDOMAIN cases (similarly as with CNAME).
 */
TEST_F(InMemoryQueryTest, DNAME) {
    query.process(list, Name("www.dname.example.com"), RRType::A(),
                  response);

    responseCheck(response, Rcode::NOERROR(), AA_FLAG, 2, 0, 0,
        (string(dname_txt) + synthetized_cname_txt).c_str(),
        NULL, NULL);
}
}
