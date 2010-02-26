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

#include <exceptions/exceptions.h>
#include <dns/name.h>
#include <dns/message.h>
#include <dns/rrset.h>
#include <dns/rrclass.h>
#include <dns/rrtype.h>

using namespace isc::dns;

namespace isc {
namespace auth {

// An individual task to be carried out by the query logic
class QueryTask {
public:
    // XXX: Members are currently public, but should probably be
    // moved to private and wrapped in get() functions later.

    // The standard query tuple: qname/qclass/qtype.
    // Note that qtype is ignored in the GLUE_QUERY/NOGLUE_QUERY case.
    const Name& qname;
    const RRClass& qclass;
    const RRType& qtype;

    // Optional: name for the containing zone, if known.
    // This is particularly needed when looking up data in a
    // zone other than the closest enclosure (such as getting
    // DS queries from a parent zone on a server which serves
    // both parent and child).
    Name* zone;

    // The section of the reply into which the data should be
    // written after it has been fetched from the data source.
    const Section& section;

    // The op field indicates the operation to be carried out by
    // this query task:
    //
    // - SIMPLE_QUERY: look for a match for qname/qclass/qtype
    //   in local data (regardless of whether it is above or below
    //   a zone cut).
    //
    // - AUTH_QUERY: look for a match for qname/qclass/qtype, or
    //   for qname/qclass/CNAME, or for a referral.
    //
    // - GLUE_QUERY: look for matches with qname/qclass/A
    //   OR qname/class/AAAA in local data, regardless of
    //   authority, for use in glue.  (This can be implemented
    //   as two successive SIMPLE_QUERY tasks, but might be
    //   optimized by the concrete data source implementation
    //   by turning it into a single database lookup.)
    //
    // - NOGLUE_QUERY: same as GLUE_QUERY except that answers
    //   are rejected if they are below a zone cut.
    //
    // - REF_QUERY: look for matches for qname/qclass/NS,
    //   qname/qclass/DS, and qname/qclass/DNAME.  Used
    //   to search for a zone cut.

    const enum Op {
        SIMPLE_QUERY,
        AUTH_QUERY,
        GLUE_QUERY,
        NOGLUE_QUERY,
        REF_QUERY,
    } op;

    // The state field indicates the state of the query; it controls
    // the next step after processing each query task.
    //
    // - GETANSWER: We are looking for the answer to a primary query.
    //   (The qname of the task should exactly match the qname of the
    //   query.)  If we have no match, the query has failed.
    //
    // - GETADDITIONAL: We are filling in additional data, either
    //   as a result of finding NS or MX records via a GETANSWER
    //   query task, or as a result of finding NS records when
    //   getting authority-section data.
    //
    // - FOLLOWCNAME: We are looking for the target of a CNAME RR that
    //   was found via a previous GETANSWER query task.  If we have no
    //   match, the query is still successful.
    //
    // (NOTE: It is only necessary to set a task state when pushing
    // tasks onto the query task queue, which in turn is only necessary
    // when it's uncertain which data source will be authoritative for the
    // data.  That's why there is no GETAUTHORITY task state; when
    // processing an answer, either positive or negative, the authoritative
    // data source will already have been discovered, and can be queried
    // directly.)

    enum State {
        GETANSWER,
        GETADDITIONAL,
        FOLLOWCNAME
    } state;

    // Response flags to indicate conditions encountered while
    // processing this task.
    uint32_t flags;

    // Constructors
    QueryTask(const Name& n, const RRClass& c,
              const RRType& t, const Section& sect) :
        qname(n), qclass(c), qtype(t), zone(NULL),
        section(sect), op(AUTH_QUERY), state(GETANSWER), flags(0) {}
    QueryTask(const Name& n, const RRClass& c,
              const RRType& t, const Section& sect, const Op o) :
        qname(n), qclass(c), qtype(t), zone(NULL),
        section(sect), op(o), state(GETANSWER), flags(0) {}
    QueryTask(const Name& n, const RRClass& c,
              const RRType& t, const Section& sect, const State st) :
        qname(n), qclass(c), qtype(t), zone(NULL),
        section(sect), op(AUTH_QUERY), state(st), flags(0) {}
    QueryTask(const Name& n, const RRClass& c,
              const RRType& t, const Section& sect,
              const Op o, const State st) :
        qname(n), qclass(c), qtype(t), zone(NULL),
        section(sect), op(o), state(st), flags(0) {}

    // These are special constructors for particular query task types,
    // to simplify the code.
    //
    // A simple query doesn't need to specify section or state.
    QueryTask(const Name& n, const RRClass& c, const RRType& t, const Op o) :
        qname(n), qclass(c), qtype(t), zone(NULL),
        section(Section::ANSWER()), op(o), state(GETANSWER), flags(0) {
        if (op != SIMPLE_QUERY) {
            throw "invalid constructor for this task operation";
        }
    }
    // A referral query doesn't need to specify section, state, or type.
    QueryTask(const Name& n, const RRClass& c, const Op o) :
        qname(n), qclass(c), qtype(RRType::ANY()), zone(NULL),
        section(Section::ANSWER()), op(o), state(GETANSWER), flags(0) {
        if (op != REF_QUERY) {
            throw "invalid constructor for this task operation";
        }
    }
    // A glue (or noglue) query doesn't need to specify type.
    QueryTask(const Name& n, const RRClass& c,
              const Section& sect, const Op o, const State st) :
        qname(n), qclass(c), qtype(RRType::ANY()), zone(NULL),
        section(sect), op(o), state(st), flags(0) {
        if (op != GLUE_QUERY && op != NOGLUE_QUERY) {
            throw "invalid constructor for this task operation";
        }
    }

    virtual ~QueryTask();
};

typedef boost::shared_ptr<QueryTask> QueryTaskPtr;
typedef std::queue<QueryTaskPtr> QueryTaskQueue;

class Query;
typedef boost::shared_ptr<Query> QueryPtr;

// Data Source query
class Query {
public:
    // The state of a query: pending or answered.
    enum Status {
        PENDING,
        ANSWERED
    };

    // Query constructor
    Query(Message& m, bool dnssec) {
        message_ = &m;
        want_additional = true;
        want_dnssec = dnssec;
        status_ = PENDING;

        // Check message formatting
        if (message_->getRRCount(Section::QUESTION()) != 1) {
            dns_throw(Unexpected, "malformed message: too many questions");
        }

        // Populate the query task queue with the initial question
        QuestionPtr query = *message_->beginQuestion();
        qname_ = &query->getName();
        qclass_ = &query->getClass();
        qtype_ = &query->getType();

        QueryTaskPtr initial_task(new QueryTask(*qname_, *qclass_, *qtype_,
                                                Section::ANSWER()));
        querytasks.push(initial_task);
    };

    virtual ~Query();

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

    Status status() { return status_; }
    void setStatus(Status s) { status_ = s; }

private:
    Status status_;

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
