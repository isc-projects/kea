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

#include <algorithm>
#include <utility>
#include <vector>
#include <sstream>

#include <dns/buffer.h>
#include <dns/message.h>
#include <dns/name.h>
#include <dns/rrclass.h>
#include <dns/rrtype.h>

#include <bench/benchmark_util.h>

#include <gtest/gtest.h>

using namespace std;
using namespace isc::bench;
using namespace isc::dns;

namespace {
typedef pair<string, string> QueryParam;

class LoadQueryTest : public ::testing::Test {
protected:
    LoadQueryTest() : query_rrclass(RRClass::IN()) {
        queries.push_back(QueryParam("www.example.org", "AAAA"));
        queries.push_back(QueryParam("www.example.com", "A"));
        queries.push_back(QueryParam("test.example", "NS"));
    }
    RRClass query_rrclass;
    BenchQueries result_queries;
    vector<QueryParam> queries;
    stringstream query_stream;
    static const char* const DATA_DIR;
};

const char* const LoadQueryTest::DATA_DIR = TEST_DATA_DIR;

class QueryInserter {
public:
    QueryInserter(stringstream& stream) : stream_(stream) {}
    void operator()(const QueryParam& query) {
        stream_ << query.first << " " << query.second << endl;
    }
private:
    stringstream& stream_;
};

class QueryChecker {
public:
    QueryChecker(const vector<QueryParam>* expected, const RRClass& rrclass) :
        expected_(expected), rrclass_(rrclass)
    {
        if (expected != NULL) {
            iter_ = expected_->begin();
        }
    }
    void operator()(const vector<unsigned char>& actual_data) {
        InputBuffer buffer(&actual_data[0], actual_data.size());
        Message message(Message::PARSE);
        message.fromWire(buffer);

        // Check if the header part indicates an expected standard query.
        EXPECT_EQ(0, message.getQid());
        EXPECT_EQ(Opcode::QUERY(), message.getOpcode());
        EXPECT_EQ(Rcode::NOERROR(), message.getRcode());
        EXPECT_EQ(Rcode::NOERROR(), message.getRcode());
        EXPECT_FALSE(message.getHeaderFlag(MessageFlag::QR()));
        EXPECT_FALSE(message.getHeaderFlag(MessageFlag::AA()));
        EXPECT_EQ(1, message.getRRCount(Section::QUESTION()));
        EXPECT_EQ(0, message.getRRCount(Section::ANSWER()));
        EXPECT_EQ(0, message.getRRCount(Section::AUTHORITY()));
        EXPECT_EQ(0, message.getRRCount(Section::ADDITIONAL()));

        // Check if the question matches our original data, if the expected
        // data is given.
        if (expected_ != NULL) {
            ConstQuestionPtr question = *message.beginQuestion();;
            EXPECT_EQ(Name((*iter_).first), question->getName());
            EXPECT_EQ(RRType((*iter_).second), question->getType());
            EXPECT_EQ(rrclass_, question->getClass());
        
            ++iter_;
        }
    }
private:
    const vector<QueryParam>* expected_;
    vector<QueryParam>::const_iterator iter_;
    const RRClass rrclass_;
};

TEST_F(LoadQueryTest, load) {
    for_each(queries.begin(), queries.end(), QueryInserter(query_stream));

    loadQueryData(query_stream, result_queries, query_rrclass);

    EXPECT_EQ(queries.size(), result_queries.size());
    for_each(result_queries.begin(), result_queries.end(),
             QueryChecker(&queries, query_rrclass));
}

TEST_F(LoadQueryTest, loadForCHClass) {
    for_each(queries.begin(), queries.end(), QueryInserter(query_stream));
    query_rrclass = RRClass::CH();

    loadQueryData(query_stream, result_queries, query_rrclass);

    EXPECT_EQ(queries.size(), result_queries.size());
    for_each(result_queries.begin(), result_queries.end(),
             QueryChecker(&queries, query_rrclass));
}

TEST_F(LoadQueryTest, loadWithComment) {
    for_each(queries.begin(), queries.end(), QueryInserter(query_stream));
    // add a comment line.  this shouldn't change the result.
    query_stream << "# this is a comment" << endl;
    query_stream << endl;       // empty line.  should be ignored, too.

    loadQueryData(query_stream, result_queries, query_rrclass);
    EXPECT_EQ(queries.size(), result_queries.size());
    for_each(result_queries.begin(), result_queries.end(),
             QueryChecker(&queries, query_rrclass));
}

TEST_F(LoadQueryTest, loadWithIncompleteData) {
    for_each(queries.begin(), queries.end(), QueryInserter(query_stream));
    // RRType is missing.  It should be ignored by default.
    query_stream << "type-is-missing" << endl;

    loadQueryData(query_stream, result_queries, query_rrclass);
    EXPECT_EQ(queries.size(), result_queries.size());
    for_each(result_queries.begin(), result_queries.end(),
             QueryChecker(&queries, query_rrclass));
}

TEST_F(LoadQueryTest, loadWithIncompleteDataToBeRejected) {
    for_each(queries.begin(), queries.end(), QueryInserter(query_stream));
    // RRType is missing.  We're going to specify the "strict" check, so
    // we should receive an exception.
    query_stream << "type-is-missing" << endl;
    EXPECT_THROW(loadQueryData(query_stream, result_queries, query_rrclass,
                               true), BenchMarkError);
}

TEST_F(LoadQueryTest, loadWithBadData) {
    for_each(queries.begin(), queries.end(), QueryInserter(query_stream));
    // invalid RRType.  It should be ignored by default.
    query_stream << "www.example.com NOSUCHRRTYPE" << endl;

    loadQueryData(query_stream, result_queries, query_rrclass);
    EXPECT_EQ(queries.size(), result_queries.size());
    for_each(result_queries.begin(), result_queries.end(),
             QueryChecker(&queries, query_rrclass));
}

TEST_F(LoadQueryTest, loadWithBadDataToBeRejected) {
    for_each(queries.begin(), queries.end(), QueryInserter(query_stream));
    // invalid RRType, which should trigger an exception.
    query_stream << "www.example.com NOSUCHRRTYPE" << endl;
    EXPECT_THROW(loadQueryData(query_stream, result_queries, query_rrclass,
                               true), BenchMarkError);
}

TEST_F(LoadQueryTest, loadFromFile) {
    const string data_file = string(DATA_DIR) + string("/query.txt");
    loadQueryData(data_file.c_str(), result_queries, query_rrclass);
    EXPECT_LT(0, result_queries.size());

    // We are going to skip matching the query data; we only check the header.
    // We could check the data, too, but to do so we need to populate the
    // expected data from the file (or prepare a consistent copy locally).
    // Since the implementation is shared with the stringstream case, the
    // additional setup wouldn't be worthwhile.
    for_each(result_queries.begin(), result_queries.end(),
             QueryChecker(NULL, query_rrclass));
}

TEST_F(LoadQueryTest, loadFromFileNotExist) {
    EXPECT_THROW(loadQueryData("notexistent/query.data", result_queries,
                               query_rrclass), BenchMarkError);
}
}
