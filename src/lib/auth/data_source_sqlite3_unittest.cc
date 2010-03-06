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

#include <stdint.h>

#include <algorithm>
#include <string>
#include <vector>

#include <gtest/gtest.h>

#include <dns/name.h>
#include <dns/message.h>
#include <dns/rdata.h>
#include <dns/rrclass.h>
#include <dns/rrtype.h>
#include <dns/rdataclass.h>
#include <dns/rrsetlist.h>

#include "query.h"
#include "data_source.h"
#include "data_source_sqlite3.h"

using namespace std;
using namespace isc::dns;
using namespace isc::dns::rdata;
using namespace isc::auth;

namespace {
static const char* SQLITE_DBFILE_EXAMPLE = "testdata/test.sqlite3";

static const string sigdata_common(" 20100322084538 20100220084538 "
                                   "33495 example.com. FAKEFAKEFAKEFAKE");

static const Name zone_name("example.com");
static const Name nomatch_name("example.org");
static const Name www_name("www.example.com");
static const Name www_upper_name("WWW.EXAMPLE.COM");

class Sqlite3DataSourceTest : public ::testing::Test {
protected:
    Sqlite3DataSourceTest() : message(Message::PARSE),
                              query(NULL), rrclass(RRClass::IN()),
                              rrtype(RRType::A()), rrttl(RRTTL(3600)),
                              find_flags(0), rrset_matched(0), rrset_count(0)
    {
        data_source.init(SQLITE_DBFILE_EXAMPLE);

        // the data source will ignore the message, and the encapsulating
        // query object so the content doesn't matter.
        // (it's a bad practice, but is a different issue)
        message.addQuestion(Question(Name("example.org"), rrclass, rrtype));
        query = new Query(message, true);

        www_data.push_back("192.0.2.1");
        www_sig_data.push_back("A 5 3 3600" + sigdata_common);
        www_nsec_data.push_back("example.com. A RRSIG NSEC");
        www_nsec_sig_data.push_back("NSEC 5 3 7200" + sigdata_common);
        apex_ns_data.push_back("dns01.example.com.");
        apex_ns_data.push_back("dns02.example.com.");
        apex_ns_data.push_back("dns03.example.com.");
        apex_ns_sig_data.push_back("NS 5 2 3600" + sigdata_common);
    }
    ~Sqlite3DataSourceTest() { delete query; }
    Sqlite3DataSrc data_source;
    Message message;
    Query* query;
    // we allow these to be modified in the test
    RRClass rrclass;
    RRType rrtype;
    RRTTL rrttl;
    RRsetList result_sets;
    uint32_t find_flags;
    unsigned rrset_matched;
    unsigned rrset_count;

    vector<RRType> types;
    vector<RRTTL> ttls;
    vector<const vector<string>* > answers;
    vector<const vector<string>* > signatures;

    vector<RRType> expected_types;
    vector<string> www_data;
    vector<string> www_sig_data;
    vector<string> www_nsec_data;
    vector<string> www_nsec_sig_data;
    vector<string> apex_ns_data;
    vector<string> apex_ns_sig_data;
};

void
checkRRset(RRsetPtr rrset, const Name& expected_name,
           const RRClass& expected_class, const RRType& expected_type,
           const RRTTL& expected_rrttl, const vector<string>& expected_data,
           const vector<string>* expected_sig_data)
{
    EXPECT_EQ(expected_name, rrset->getName());
    EXPECT_EQ(expected_class, rrset->getClass());
    EXPECT_EQ(expected_type, rrset->getType());
    EXPECT_EQ(expected_rrttl, rrset->getTTL());

    RdataIteratorPtr rdata_iterator = rrset->getRdataIterator();
    rdata_iterator->first();
    vector<string>::const_iterator data_it = expected_data.begin();
    for (; data_it != expected_data.end(); ++data_it) {
        EXPECT_FALSE(rdata_iterator->isLast());
        if (rdata_iterator->isLast()) {
            // buggy case, should stop here
            break;
        }
        EXPECT_EQ(0, (rdata_iterator->getCurrent()).compare(
                      *createRdata(expected_type, expected_class, *data_it)));
        rdata_iterator->next();
    }

    if (expected_sig_data != NULL) {
        RRsetPtr sig_rrset = rrset->getRRsig();
        EXPECT_FALSE(NULL == sig_rrset);
        // Note: we assume the TTL for RRSIG is the same as that of the
        // RRSIG target.
        checkRRset(sig_rrset, expected_name, expected_class, RRType::RRSIG(),
                   expected_rrttl, *expected_sig_data, NULL);
    } else {
        EXPECT_TRUE(NULL == rrset->getRRsig());
    }

    EXPECT_TRUE(rdata_iterator->isLast());
}

void
checkFind(const Sqlite3DataSrc& data_source, const Query& query,
          const Name& expected_name, const Name* zone_name,
          const RRClass& expected_class, const RRType& expected_type,
          const vector<RRTTL>& expected_ttls, const uint32_t expected_flags,
          const vector<RRType>& expected_types,
          const vector<const vector<string>* >& expected_answers,
          const vector<const vector<string>* >& expected_signatures)
{
    RRsetList result_sets;
    uint32_t find_flags;
    unsigned int rrset_matched = 0;
    unsigned int rrset_count = 0;

    EXPECT_EQ(DataSrc::SUCCESS,
              data_source.findRRset(query, expected_name, expected_class,
                                    expected_type, result_sets, find_flags,
                                    zone_name));
    EXPECT_EQ(expected_flags, find_flags);
    RRsetList::iterator it = result_sets.begin();
    for (; it != result_sets.end(); ++it) {
        vector<RRType>::const_iterator found_type = find(expected_types.begin(), expected_types.end(),
                          (*it)->getType());
        // there should be a match
        EXPECT_TRUE(found_type != expected_types.end());
        if (found_type != expected_types.end()) {
            unsigned int index = distance(expected_types.begin(), found_type);
            checkRRset(*it, expected_name, expected_class, (*it)->getType(),
                       expected_ttls[index], *expected_answers[index],
                       expected_signatures[index]);
            ++rrset_matched;
        }
        ++rrset_count;
    }
    EXPECT_EQ(expected_types.size(), rrset_count);
    EXPECT_EQ(expected_types.size(), rrset_matched);
}

void
checkFind(const Sqlite3DataSrc& data_source, const Query& query,
          const Name& expected_name, const Name* zone_name,
          const RRClass& expected_class, const RRType& expected_type,
          const RRTTL& expected_rrttl, const uint32_t expected_flags,
          const vector<string>& expected_data,
          const vector<string>* expected_sig_data)
{
    vector<RRType> types;
    vector<RRTTL> ttls;
    vector<const vector<string>* > answers;
    vector<const vector<string>* > signatures;

    types.push_back(expected_type);
    ttls.push_back(expected_rrttl);
    answers.push_back(&expected_data);
    signatures.push_back(expected_sig_data);

    checkFind(data_source, query, expected_name, zone_name, expected_class,
              expected_type, ttls, expected_flags, types, answers,
              signatures);
}

TEST_F(Sqlite3DataSourceTest, close) {
    EXPECT_EQ(DataSrc::SUCCESS, data_source.close());
}

TEST_F(Sqlite3DataSourceTest, findClosestEnclosure) {
    NameMatch name_match(www_name);
    data_source.findClosestEnclosure(name_match);
    EXPECT_EQ(zone_name, *name_match.closestName());
    EXPECT_EQ(&data_source, name_match.bestDataSrc());
}

TEST_F(Sqlite3DataSourceTest, findClosestEnclosureNoMatch) {
    NameMatch name_match(nomatch_name);
    data_source.findClosestEnclosure(name_match);
    EXPECT_EQ(NULL, name_match.closestName());
    EXPECT_EQ(NULL, name_match.bestDataSrc());
}

TEST_F(Sqlite3DataSourceTest, findRRsetNormal) {
    // Without specifying the zone name, and then with the zone name
    checkFind(data_source, *query, www_name, NULL, rrclass, rrtype, rrttl, 0,
              www_data, &www_sig_data);

    checkFind(data_source, *query, www_name, &zone_name, rrclass, rrtype, rrttl,
              0, www_data, &www_sig_data);

    // With a zone name that doesn't match
    EXPECT_EQ(DataSrc::SUCCESS,
              data_source.findRRset(*query, www_name, rrclass, rrtype,
                                    result_sets, find_flags, &nomatch_name));
    EXPECT_EQ(DataSrc::NO_SUCH_ZONE, find_flags);
    EXPECT_TRUE(result_sets.begin() == result_sets.end()); // should be empty
}

TEST_F(Sqlite3DataSourceTest, findRRsetNormalANY) {
    types.push_back(RRType::A());
    types.push_back(RRType::NSEC());
    ttls.push_back(RRTTL(3600));
    ttls.push_back(RRTTL(7200));
    answers.push_back(&www_data);
    answers.push_back(&www_nsec_data);
    signatures.push_back(&www_sig_data);
    signatures.push_back(&www_nsec_sig_data);

    rrtype = RRType::ANY();
    checkFind(data_source, *query, www_name, NULL, rrclass, rrtype, ttls, 0,
              types, answers, signatures);

    checkFind(data_source, *query, www_name, &zone_name, rrclass, rrtype, ttls,
              0, types, answers, signatures);
}

// Case insensitive lookup
TEST_F(Sqlite3DataSourceTest, findRRsetNormalCase) {
    checkFind(data_source, *query, www_upper_name, NULL, rrclass, rrtype, rrttl,
              0, www_data, &www_sig_data);

    checkFind(data_source, *query, www_upper_name, &zone_name, rrclass, rrtype,
              rrttl, 0, www_data, &www_sig_data);

    EXPECT_EQ(DataSrc::SUCCESS,
              data_source.findRRset(*query, www_upper_name, rrclass, rrtype,
                                    result_sets, find_flags, &nomatch_name));
    EXPECT_EQ(DataSrc::NO_SUCH_ZONE, find_flags);
    EXPECT_TRUE(result_sets.begin() == result_sets.end()); // should be empty
}

TEST_F(Sqlite3DataSourceTest, findRRsetApexNS) {
    rrtype = RRType::NS();
    checkFind(data_source, *query, zone_name, NULL, rrclass, rrtype, rrttl,
              DataSrc::REFERRAL, apex_ns_data, &apex_ns_sig_data);

    checkFind(data_source, *query, zone_name, &zone_name, rrclass, rrtype,
              rrttl, DataSrc::REFERRAL, apex_ns_data, &apex_ns_sig_data);

    EXPECT_EQ(DataSrc::SUCCESS,
              data_source.findRRset(*query, zone_name, rrclass, rrtype,
                                    result_sets, find_flags, &nomatch_name));
    EXPECT_EQ(DataSrc::NO_SUCH_ZONE, find_flags);
    EXPECT_TRUE(result_sets.begin() == result_sets.end()); // should be empty
}

}
