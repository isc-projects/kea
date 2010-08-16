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

#include <config.h>

#include <gtest/gtest.h>

#include <dns/name.h>
#include <dns/message.h>
#include <dns/rdata.h>
#include <dns/rrclass.h>
#include <dns/rrtype.h>
#include <dns/rdataclass.h>
#include <dns/rrsetlist.h>
#include <cc/data.h>

#include <datasrc/query.h>
#include <datasrc/data_source.h>
#include <datasrc/static_datasrc.h>

using namespace std;
using namespace isc::dns;
using namespace isc::dns::rdata;
using namespace isc::datasrc;

namespace {
class StaticDataSourceTest : public ::testing::Test {
protected:
    StaticDataSourceTest() : version_name("version.bind"),
                             authors_name("authors.bind"),
                             nomatch_name("example.com"),
                             rrclass(RRClass::CH()), rrtype(RRType::TXT()),
                             rrttl(RRTTL(0)), find_flags(0), matched_rdata(0)
    {
        // version.bind is answered with package name+version
        // (defined as PACKAGE_STRING in config.h)
        version_data.push_back(PACKAGE_STRING);

        // XXX: in addition, the order the following items matter.
        authors_data.push_back("Chen Zhengzhang");
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
        authors_data.push_back("Shen Tingting");
        authors_data.push_back("Stephen Morris");
        authors_data.push_back("Zhang Likun");

        version_ns_data.push_back("version.bind.");
        authors_ns_data.push_back("authors.bind.");

        version_soa_data.push_back("version.bind. hostmaster.version.bind. "
                                   "0 28800 7200 604800 86400");
        authors_soa_data.push_back("authors.bind. hostmaster.authors.bind. "
                                   "0 28800 7200 604800 86400");
    }
    StaticDataSrc data_source;
    const Name version_name;
    const Name authors_name;
    const Name nomatch_name;
    const RRClass rrclass;
    RRType rrtype;              // we allow this to be modified in the test
    RRTTL rrttl;
    RRsetList result_sets;
    uint32_t find_flags;
    unsigned matched_rdata;
    vector<RRType> types;
    vector<RRTTL> ttls;
    vector<const vector<string>* > answers;
    vector<string> version_data;
    vector<string> authors_data;
    vector<string> version_ns_data;
    vector<string> authors_ns_data;
    vector<string> version_soa_data;
    vector<string> authors_soa_data;
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

void
checkFind(const DataSrc& data_source,
          const Name& qname, const Name* zone_name,
          const RRClass& qclass, const RRClass& expected_class,
          const RRType& qtype, const vector<RRTTL>& expected_ttls,
          const uint32_t expected_flags, const vector<RRType>& expected_types,
          const vector<const vector<string>* >& expected_answers)
{
    RRsetList result_sets;
    uint32_t find_flags;
    unsigned int rrset_matched = 0;
    unsigned int rrset_count = 0;

    EXPECT_EQ(DataSrc::SUCCESS,
              data_source.findRRset(qname, qclass, qtype, result_sets,
                                    find_flags, zone_name));
    EXPECT_EQ(expected_flags, find_flags);

    if ((find_flags & (DataSrc::NO_SUCH_ZONE | DataSrc::NAME_NOT_FOUND |
                       DataSrc::TYPE_NOT_FOUND)) != 0) {
        EXPECT_TRUE(result_sets.begin() == result_sets.end());
        return;
    }

    RRsetList::iterator it = result_sets.begin();
    for (; it != result_sets.end(); ++it) {
        vector<RRType>::const_iterator found_type =
            find(expected_types.begin(), expected_types.end(),
                 (*it)->getType());
        // there should be a match
        EXPECT_TRUE(found_type != expected_types.end());
        if (found_type != expected_types.end()) {
            unsigned int index = distance(expected_types.begin(), found_type);
            checkRRset(*it, qname, expected_class, (*it)->getType(),
                       expected_ttls[index], *expected_answers[index]);
            ++rrset_matched;
        }
        ++rrset_count;
    }
    EXPECT_EQ(expected_types.size(), rrset_count);
    EXPECT_EQ(expected_types.size(), rrset_matched);
}

void
checkFind(const DataSrc& data_source,
          const Name& qname, const Name* zone_name,
          const RRClass& qclass, const RRClass& expected_class,
          const RRType& qtype,  // == expected RRType
          const RRTTL& expected_ttl, const uint32_t expected_flags,
          const vector<string>& expected_answers)
{
    vector<RRType> types;
    vector<RRTTL> ttls;
    vector<const vector<string>* > answers;

    types.push_back(qtype);
    ttls.push_back(expected_ttl);
    answers.push_back(&expected_answers);

    checkFind(data_source, qname, zone_name, qclass, expected_class, qtype,
              ttls, expected_flags, types, answers);
}

TEST_F(StaticDataSourceTest, init) {
    EXPECT_EQ(DataSrc::SUCCESS, data_source.init());
}

TEST_F(StaticDataSourceTest, close) {
    EXPECT_EQ(DataSrc::SUCCESS, data_source.init());
}

TEST_F(StaticDataSourceTest, findClosestEnclosureForVersion) {
    DataSrcMatch match(version_name, rrclass);
    data_source.findClosestEnclosure(match);
    EXPECT_EQ(version_name, *match.getEnclosingZone());
    EXPECT_EQ(&data_source, match.getDataSource());
}

// Class Any query should result in the same answer.
TEST_F(StaticDataSourceTest, findClosestEnclosureForVersionClassAny) {
    DataSrcMatch match(version_name, RRClass::ANY());
    data_source.findClosestEnclosure(match);
    EXPECT_EQ(version_name, *match.getEnclosingZone());
    EXPECT_EQ(&data_source, match.getDataSource());
}

// If class doesn't match the lookup should fail.
TEST_F(StaticDataSourceTest, findClosestEnclosureForVersionClassMismatch) {
    DataSrcMatch match(version_name, RRClass::IN());
    data_source.findClosestEnclosure(match);
    EXPECT_EQ(static_cast<void*>(NULL), match.getEnclosingZone());
    EXPECT_EQ(static_cast<void*>(NULL), match.getDataSource());
}

TEST_F(StaticDataSourceTest, findClosestEnclosureForVersionPartial) {
    DataSrcMatch match(Name("foo").concatenate(version_name), rrclass);
    data_source.findClosestEnclosure(match);
    EXPECT_EQ(version_name, *match.getEnclosingZone());
    EXPECT_EQ(&data_source, match.getDataSource());
}

TEST_F(StaticDataSourceTest, findClosestEnclosureForAuthors) {
    DataSrcMatch match(authors_name, rrclass);
    data_source.findClosestEnclosure(match);
    EXPECT_EQ(authors_name, *match.getEnclosingZone());
    EXPECT_EQ(&data_source, match.getDataSource());
}

TEST_F(StaticDataSourceTest, findClosestEnclosureForAuthorsPartial) {
    DataSrcMatch match(Name("foo").concatenate(authors_name), rrclass);
    data_source.findClosestEnclosure(match);
    EXPECT_EQ(authors_name, *match.getEnclosingZone());
    EXPECT_EQ(&data_source, match.getDataSource());
}

TEST_F(StaticDataSourceTest, findClosestEnclosureNoMatch) {
    DataSrcMatch match(nomatch_name, rrclass);
    data_source.findClosestEnclosure(match);
    EXPECT_EQ(static_cast<void*>(NULL), match.getEnclosingZone());
    EXPECT_EQ(static_cast<void*>(NULL), match.getDataSource());
}

TEST_F(StaticDataSourceTest, findRRsetVersionTXT) {
    checkFind(data_source, version_name, NULL, rrclass, rrclass,
              rrtype, rrttl, 0, version_data);
    checkFind(data_source, version_name, &version_name, rrclass, rrclass,
              rrtype, rrttl, 0, version_data);
}

TEST_F(StaticDataSourceTest, findRRsetVersionNS) {
    rrtype = RRType::NS();
    checkFind(data_source, version_name, NULL, rrclass, rrclass,
              rrtype, rrttl, 0, version_ns_data);
    checkFind(data_source, version_name, &version_name, rrclass, rrclass,
              rrtype, rrttl, 0, version_ns_data);
}

TEST_F(StaticDataSourceTest, findRRsetVersionSOA) {
    rrtype = RRType::SOA();

    checkFind(data_source, version_name, NULL, rrclass, rrclass,
              rrtype, rrttl, 0, version_soa_data);
    checkFind(data_source, version_name, &version_name, rrclass, rrclass,
              rrtype, rrttl, 0, version_soa_data);
}

TEST_F(StaticDataSourceTest, findRRsetVersionANY) {
    rrtype = RRType::ANY();
    
    types.push_back(RRType::TXT());
    types.push_back(RRType::NS());
    types.push_back(RRType::SOA());
    ttls.push_back(rrttl);
    ttls.push_back(rrttl);
    ttls.push_back(rrttl);
    answers.push_back(&version_data);
    answers.push_back(&version_ns_data);
    answers.push_back(&version_soa_data);

    checkFind(data_source, version_name, NULL, rrclass, rrclass, rrtype, ttls,
              0, types, answers);
    checkFind(data_source, version_name, &version_name, rrclass, rrclass,
              rrtype, ttls, 0, types, answers);
}

TEST_F(StaticDataSourceTest, findRRsetAuthorsTXT) {
    checkFind(data_source, authors_name, NULL, rrclass, rrclass,
              rrtype, rrttl, 0, authors_data);
    checkFind(data_source, authors_name, &authors_name, rrclass, rrclass,
              rrtype, rrttl, 0, authors_data);
}

TEST_F(StaticDataSourceTest, findRRsetAuthorsNS) {
    rrtype = RRType::NS();
    checkFind(data_source, authors_name, NULL, rrclass, rrclass,
              rrtype, rrttl, 0, authors_ns_data);
    checkFind(data_source, authors_name, &authors_name, rrclass, rrclass,
              rrtype, rrttl, 0, authors_ns_data);
}

TEST_F(StaticDataSourceTest, findRRsetAuthorsSOA) {
    rrtype = RRType::SOA();
    checkFind(data_source, authors_name, NULL, rrclass, rrclass,
              rrtype, rrttl, 0, authors_soa_data);
    checkFind(data_source, authors_name, &authors_name, rrclass, rrclass,
              rrtype, rrttl, 0, authors_soa_data);
}

TEST_F(StaticDataSourceTest, findRRsetAuthorsANY) {
    rrtype = RRType::ANY();
    
    types.push_back(RRType::TXT());
    types.push_back(RRType::NS());
    types.push_back(RRType::SOA());
    ttls.push_back(rrttl);
    ttls.push_back(rrttl);
    ttls.push_back(rrttl);
    answers.push_back(&authors_data);
    answers.push_back(&authors_ns_data);
    answers.push_back(&authors_soa_data);

    checkFind(data_source, authors_name, NULL, rrclass, rrclass, rrtype, ttls,
              0, types, answers);
    checkFind(data_source, authors_name, &authors_name, rrclass, rrclass,
              rrtype, ttls, 0, types, answers);
}
// Class ANY lookup should result in the same answer.
TEST_F(StaticDataSourceTest, findRRsetVersionClassAny) {
    checkFind(data_source, version_name, NULL, RRClass::ANY(), rrclass,
              rrtype, rrttl, 0, version_data);
    checkFind(data_source, version_name, &version_name, RRClass::ANY(), rrclass,
              rrtype, rrttl, 0, version_data);
}

// If the class doesn't match, it should simply fail.
TEST_F(StaticDataSourceTest, findRRsetVersionClassMismatch) {
    EXPECT_EQ(DataSrc::ERROR,
              data_source.findRRset(version_name, RRClass::IN(), rrtype,
                                    result_sets, find_flags, &version_name));
}

TEST_F(StaticDataSourceTest, findRRsetOutOfZone) {
    // If the qname doesn't match any of the static zones, the result should
    // be "no such zone", regardless of whether the zone is explicitly
    // specified.  Other "expected" result parameters will be ignored.
    checkFind(data_source, nomatch_name, NULL, rrclass, rrclass,
              rrtype, rrttl, DataSrc::NO_SUCH_ZONE, authors_ns_data);
    checkFind(data_source, nomatch_name, &version_name, rrclass, rrclass,
              rrtype, rrttl, DataSrc::NO_SUCH_ZONE, authors_ns_data);
    checkFind(data_source, nomatch_name, &authors_name, rrclass, rrclass,
              rrtype, rrttl, DataSrc::NO_SUCH_ZONE, authors_ns_data);
}

// If a zone name is given but doesn't match any of the static zones,
// the result should be "no such zone"
TEST_F(StaticDataSourceTest, findRRsetZoneMismatch) {
    const Name& short_zonename(Name("bind"));
    checkFind(data_source, version_name, &short_zonename, rrclass, rrclass,
              rrtype, rrttl, DataSrc::NO_SUCH_ZONE, authors_ns_data);
    checkFind(data_source, authors_name, &short_zonename, rrclass, rrclass,
              rrtype, rrttl, DataSrc::NO_SUCH_ZONE, authors_ns_data);
}

// Zone matches, but name doesn't exist in the zone
TEST_F(StaticDataSourceTest, findRRsetNoName) {
    checkFind(data_source, Name("foo").concatenate(version_name), NULL, rrclass,
              rrclass, rrtype, rrttl, DataSrc::NAME_NOT_FOUND, authors_ns_data);
    checkFind(data_source, Name("foo").concatenate(version_name), &version_name,
              rrclass, rrclass, rrtype, rrttl, DataSrc::NAME_NOT_FOUND,
              authors_ns_data);
    checkFind(data_source, Name("foo").concatenate(authors_name), NULL, rrclass,
              rrclass, rrtype, rrttl, DataSrc::NAME_NOT_FOUND, authors_ns_data);
    checkFind(data_source, Name("foo").concatenate(authors_name), &authors_name,
              rrclass, rrclass, rrtype, rrttl, DataSrc::NAME_NOT_FOUND,
              authors_ns_data);
}

// Zone matches and qname exists, but type doesn't exist for the name.
TEST_F(StaticDataSourceTest, findRRsetNoType) {
    const RRType& nomatch_type = RRType::A();

    checkFind(data_source, version_name, NULL, rrclass,
              rrclass, nomatch_type, rrttl, DataSrc::TYPE_NOT_FOUND,
              authors_ns_data);
    checkFind(data_source, version_name, &version_name, rrclass,
              rrclass, nomatch_type, rrttl, DataSrc::TYPE_NOT_FOUND,
              authors_ns_data);
    checkFind(data_source, authors_name, NULL, rrclass,
              rrclass, nomatch_type, rrttl, DataSrc::TYPE_NOT_FOUND,
              authors_ns_data);
    checkFind(data_source, authors_name, &authors_name, rrclass,
              rrclass, nomatch_type, rrttl, DataSrc::TYPE_NOT_FOUND,
              authors_ns_data);
}

// Simple tests for "unsupported" tests.
TEST_F(StaticDataSourceTest, notImplemented) {
    Name target_name(version_name);
    EXPECT_EQ(DataSrc::NOT_IMPLEMENTED,
              data_source.findPreviousName(version_name, target_name,
                                           &version_name));

    string target_hash;
    EXPECT_EQ(DataSrc::NOT_IMPLEMENTED,
              data_source.findCoveringNSEC3(version_name, target_hash,
                                            result_sets));
}

}
