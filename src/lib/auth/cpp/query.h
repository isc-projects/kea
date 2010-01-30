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

#ifndef __QUERY_H
#define __QUERY_H

#include <queue>

#include <dns/cpp/exceptions.h>
#include <dns/cpp/name.h>
#include <dns/cpp/message.h>
#include <dns/cpp/rrset.h>
#include <dns/cpp/rrclass.h>
#include <dns/cpp/rrtype.h>

namespace isc {
namespace dns {

enum QueryStatus {
    QUERY_INCOMPLETE,
    QUERY_FINISHING,
    QUERY_DONE,
    QUERY_NODATA
};

///
/// \brief exception to throw if a DNS Message is malformed
/// 
class MalformedMessage : public Exception {
public:
    MalformedMessage(const char* file, size_t line, const char* what) :
        isc::dns::Exception(file, line, what) {}
};

// An individual task to be carried out by the query logic
class QueryTask {
public:
    QueryTask(const Name& n, const RRClass& c,
              const RRType& t, const Section& s);
    virtual ~QueryTask();

    const Name& qname;
    const RRClass& qclass;
    const RRType& qtype;
    const Section& section;
};

typedef boost::shared_ptr<QueryTask> QueryTaskPtr;
typedef std::queue<QueryTaskPtr> QueryTaskQueue;

class Query;
typedef boost::shared_ptr<Query> QueryPtr;

// Data Source query
class Query {
public:
    Query(Message& m, bool dnssec) {
        message_ = &m;
        want_additional = true;
        want_dnssec = dnssec;
        status_ = QUERY_INCOMPLETE;

        // Check message formatting
        QuestionIterator qid = message_->beginQuestion();
        qid++;
        if (qid != message_->endQuestion())
                dns_throw(MalformedMessage, "too many questions");

        // Populate the query tasks queue with the initial question
        QuestionPtr query = *message_->beginQuestion();
        qname_ = &query->getName();
        qclass_ = &query->getClass();
        qtype_ = &query->getType();
        QueryTask *qt = new QueryTask(*qname_, *qclass_, *qtype_,
                                      Section::ANSWER());
        querytasks.push(QueryTaskPtr(qt));
    };

    virtual ~Query() {}

    // wantAdditional() == true indicates that additional-section data
    // should be looked up while processing this query.  false indicates
    // that we're only interested in answer-section data
    bool wantAdditional() { return want_additional; }
    void setWantAdditional(bool d) { want_additional = d; }

    // wantDnssec() == true indicates that DNSSEC data should be retrieved
    // from the data source when this query is being processed
    bool wantDnssec() { return want_dnssec; }
    void setWantDnssec(bool d) { want_dnssec = d; }

    const Name& qname() { return *qname_; }
    const RRClass& qclass() { return *qclass_; }
    const RRType& qtype() { return *qtype_; }

    Message& message() { return *message_; }
    QueryTaskQueue& tasks() { return querytasks; }

    QueryStatus status() { return status_; }
    void setStatus(QueryStatus s) { status_ = s; }

protected:
    QueryStatus status_;

private:
    const Name* qname_;
    const RRClass* qclass_;
    const RRType* qtype_;

    Message* message_;
    QueryTaskQueue querytasks;

    bool want_additional;
    bool want_dnssec;
};

}
}

#endif
