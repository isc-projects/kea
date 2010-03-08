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
#include <cc/data.h>

#include "query.h"
#include "data_source.h"
#include "data_source_static.h"

using namespace std;
using namespace isc::dns;
using namespace isc::dns::rdata;
using namespace isc::auth;

namespace {
class StaticDataSourceTest : public ::testing::Test {
protected:
    StaticDataSourceTest() : message(Message::PARSE),
                             query(NULL),
                             version_name("version.bind"),
                             authors_name("authors.bind"),
                             nomatch_name("example.com"),
                             rrclass(RRClass::CH()), rrtype(RRType::TXT()),
                             rrttl(RRTTL(0)), find_flags(0), matched_rdata(0)
    {
        // static data source will ignore the message, and the encapsulating
        // query object so the content doesn't matter.
        // (it's a bad practice, but it's a different issue)
        message.addQuestion(Question(Name(version_name), rrclass, rrtype));
        query = new Query(message, true);

        // XXX: the following values can change as release/developers change,
        // in which case the test code must be updated accordingly.
        version_data.push_back("BIND10 0.0.0 (pre-alpha)");

        // XXX: in addition, the order the following items matter.
        authors_data.push_back("Evan Hunt");
        authors_data.push_back("Han Feng");
        authors_data.push_back("Jelte Jansen");
        authors_data.push_back("Jeremy C. Reed"); 
        authors_data.push_back("Jin Jian");
        authors_data.push_back("JINMEI Tatuya");
        authors_data.push_back("Kazunori Fujiwara");
        authors_data.push_back("Michael Graff");
        authors_data.push_back("Naoki Kambe");
        authors_data.push_back("Shane Kerr");
        authors_data.push_back("Zhang Likun");

        version_ns_data.push_back("version.bind.");
        authors_ns_data.push_back("authors.bind.");
    }
    ~StaticDataSourceTest() { delete query; }
    StaticDataSrc data_source;
    Message message;
    Query* query;
    const Name version_name;
    const Name authors_name;
    const Name nomatch_name;
    const RRClass rrclass;
    RRType rrtype;              // we allow this to be modified in the test
    RRTTL rrttl;
    RRsetList result_sets;
    uint32_t find_flags;
    unsigned matched_rdata;
    vector<string> version_data;
    vector<string> authors_data;
    vector<string> version_ns_data;
    vector<string> authors_ns_data;
};

void
checkRRset(ConstRRsetPtr rrset, const Name& expected_name,
           const RRClass& expected_class, const RRType& expected_type,
           const RRTTL& rrttl, const vector<string>& expected_data)
{
    EXPECT_EQ(expected_name, rrset->getName());
    EXPECT_EQ(expected_class, rrset->getClass());
    EXPECT_EQ(expected_type, rrset->getType());
    EXPECT_EQ(rrttl, rrset->getTTL());

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
                      *createRdata(expected_type,
                                   expected_class,
                                   *data_it)));
        rdata_iterator->next();
    }

    EXPECT_TRUE(rdata_iterator->isLast());
}

TEST_F(StaticDataSourceTest, init) {
    EXPECT_EQ(DataSrc::SUCCESS, data_source.init());
}

TEST_F(StaticDataSourceTest, close) {
    EXPECT_EQ(DataSrc::SUCCESS, data_source.init());
}

TEST_F(StaticDataSourceTest, findClosestEnclosureForVersion) {
    NameMatch name_match(version_name);
    data_source.findClosestEnclosure(name_match, rrclass);
    EXPECT_EQ(version_name, *name_match.closestName());
    EXPECT_EQ(&data_source, name_match.bestDataSrc());
}

TEST_F(StaticDataSourceTest, findClosestEnclosureForVersionPartial) {
    NameMatch name_match(Name("foo").concatenate(version_name));
    data_source.findClosestEnclosure(name_match, rrclass);
    EXPECT_EQ(version_name, *name_match.closestName());
    EXPECT_EQ(&data_source, name_match.bestDataSrc());
}

TEST_F(StaticDataSourceTest, findClosestEnclosureForAuthors) {
    NameMatch name_match(authors_name);
    data_source.findClosestEnclosure(name_match, rrclass);
    EXPECT_EQ(authors_name, *name_match.closestName());
    EXPECT_EQ(&data_source, name_match.bestDataSrc());
}

TEST_F(StaticDataSourceTest, findClosestEnclosureForAuthorsPartial) {
    NameMatch name_match(Name("foo").concatenate(authors_name));
    data_source.findClosestEnclosure(name_match, rrclass);
    EXPECT_EQ(authors_name, *name_match.closestName());
    EXPECT_EQ(&data_source, name_match.bestDataSrc());
}

TEST_F(StaticDataSourceTest, findClosestEnclosureNoMatch) {
    NameMatch name_match(nomatch_name);
    data_source.findClosestEnclosure(name_match, rrclass);
    EXPECT_EQ(NULL, name_match.closestName());
    EXPECT_EQ(NULL, name_match.bestDataSrc());
}

TEST_F(StaticDataSourceTest, findRRsetVersionTXT) {
    EXPECT_EQ(DataSrc::SUCCESS,
              data_source.findRRset(*query, version_name, rrclass, rrtype,
                                    result_sets, find_flags, NULL));
    EXPECT_EQ(0, find_flags);
    // There should be only item in result_sets, which should be
    // version_name/TXT.
    RRsetList::iterator it = result_sets.begin();
    for (; it != result_sets.end(); ++it) {
        if ((*it)->getType() == rrtype) {
            checkRRset(*it, version_name, rrclass, rrtype, rrttl, version_data);
            ++matched_rdata;
        }
    }
    EXPECT_EQ(1, matched_rdata);
}

TEST_F(StaticDataSourceTest, findRRsetVersionNS) {
    rrtype = RRType::NS();
    EXPECT_EQ(DataSrc::SUCCESS,
              data_source.findRRset(*query, version_name, rrclass, rrtype,
                                    result_sets, find_flags, NULL));
    EXPECT_EQ(0, find_flags);
    RRsetList::iterator it = result_sets.begin();
    for (; it != result_sets.end(); ++it) {
        if ((*it)->getType() == rrtype) {
            checkRRset(*it, version_name, rrclass, rrtype, rrttl,
                       version_ns_data);
            ++matched_rdata;
        }
    }
    EXPECT_EQ(1, matched_rdata);
}

TEST_F(StaticDataSourceTest, findRRsetAuthorsTXT) {
    EXPECT_EQ(DataSrc::SUCCESS,
              data_source.findRRset(*query, authors_name, rrclass, rrtype,
                                    result_sets, find_flags, NULL));
    EXPECT_EQ(0, find_flags);
    RRsetList::iterator it = result_sets.begin();
    for (; it != result_sets.end(); ++it) {
        if ((*it)->getType() == rrtype) {
            checkRRset(*it, authors_name, rrclass, rrtype, rrttl, authors_data);
            ++matched_rdata;
        }
    }
    EXPECT_EQ(1, matched_rdata);
}

TEST_F(StaticDataSourceTest, findRRsetAuthorsNS) {
    rrtype = RRType::NS();
    EXPECT_EQ(DataSrc::SUCCESS,
              data_source.findRRset(*query, authors_name, rrclass, rrtype,
                                    result_sets, find_flags, NULL));
    EXPECT_EQ(0, find_flags);
    RRsetList::iterator it = result_sets.begin();
    for (; it != result_sets.end(); ++it) {
        if ((*it)->getType() == rrtype) {
            checkRRset(*it, authors_name, rrclass, rrtype, rrttl,
                       authors_ns_data);
            ++matched_rdata;
        }
    }
    EXPECT_EQ(1, matched_rdata);
}

}
