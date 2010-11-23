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

#include <dns/buffer.h>
#include <dns/name.h>
#include <dns/rrset.h>
#include <dns/message.h>

#include <cc/data.h>

#include <datasrc/query.h>

using namespace isc::dns;

namespace isc {
namespace datasrc {

QueryTask::QueryTask(const Query& qry, const isc::dns::Name& n,
                     const isc::dns::RRType& t,
                     const isc::dns::Message::Section sect) :
    q(qry), qname(n), qclass(qry.qclass()), qtype(t), section(sect),
    op(AUTH_QUERY), state(GETANSWER), flags(0)
{}

QueryTask::QueryTask(const Query& qry, const isc::dns::Name& n, 
                     const isc::dns::RRType& t,
                     const isc::dns::Message::Section sect,
                     const Op o) :
    q(qry), qname(n), qclass(qry.qclass()), qtype(t), section(sect), op(o),
    state(GETANSWER), flags(0)
{}

QueryTask::QueryTask(const Query& qry, const isc::dns::Name& n,
                     const isc::dns::RRType& t,
                     const isc::dns::Message::Section sect,
                     const State st) :
    q(qry), qname(n), qclass(qry.qclass()), qtype(t), section(sect),
    op(AUTH_QUERY), state(st), flags(0)
{}

QueryTask::QueryTask(const Query& qry, const isc::dns::Name& n,
                     const isc::dns::RRType& t,
                     const isc::dns::Message::Section sect,
                     const Op o, const State st) :
    q(qry), qname(n), qclass(qry.qclass()), qtype(t), section(sect), op(o),
    state(st), flags(0) 
{}

QueryTask::QueryTask(const Query& qry, const isc::dns::Name& n, 
                     const isc::dns::RRType& t, const Op o) :
    q(qry), qname(n), qclass(qry.qclass()), qtype(t),
    section(Message::SECTION_ANSWER), op(o), state(GETANSWER), flags(0)
{
    if (op != SIMPLE_QUERY) {
        isc_throw(Unexpected, "invalid constructor for this task operation");
    }
}

// A referral query doesn't need to specify section, state, or type.
QueryTask::QueryTask(const Query& qry, const isc::dns::Name& n, const Op o) :
    q(qry), qname(n), qclass(qry.qclass()), qtype(RRType::ANY()),
    section(Message::SECTION_ANSWER), op(o), state(GETANSWER), flags(0)
{
    if (op != REF_QUERY) {
        isc_throw(Unexpected, "invalid constructor for this task operation");
    }
}

QueryTask::QueryTask(const Query& qry, const isc::dns::Name& n,
                     const isc::dns::Message::Section sect, const Op o,
                     const State st) :
        q(qry), qname(n), qclass(qry.qclass()), qtype(RRType::ANY()),
        section(sect), op(o), state(st), flags(0)
{
    if (op != GLUE_QUERY && op != NOGLUE_QUERY) {
        isc_throw(Unexpected, "invalid constructor for this task operation");
    }
}

QueryTask::~QueryTask() {}

Query::Query(Message& m, HotCache& c, bool dnssec) :
    status_(PENDING), qname_(NULL), qclass_(NULL), qtype_(NULL),
    cache_(&c), message_(&m), want_additional_(true), want_dnssec_(dnssec)
{
    // Check message formatting
    if (message_->getRRCount(Message::SECTION_QUESTION) != 1) {
        isc_throw(Unexpected, "malformed message: too many questions");
    }

    // Populate the query task queue with the initial question
    QuestionPtr question = *message_->beginQuestion();
    qname_ = &question->getName();
    qclass_ = &question->getClass();
    qtype_ = &question->getType();
    restarts_ = 0;

    querytasks_.push(QueryTaskPtr(new QueryTask(*this, *qname_, *qtype_,
                                                Message::SECTION_ANSWER)));
}

Query::~Query() {}

}
}
