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

#include "query.h"

using namespace isc::dns;

namespace isc {
namespace auth {

// Destructors defined here to avoid confusing the linker
QueryTask::~QueryTask() {}
Query::~Query() {}

QueryTask::QueryTask(const isc::dns::Name& n, const isc::dns::RRClass& c,
                     const isc::dns::RRType& t, const isc::dns::Section& sect) :
    qname(n), qclass(c), qtype(t), zone(NULL),
        section(sect), op(AUTH_QUERY), state(GETANSWER), flags(0)
{}

QueryTask::QueryTask(const isc::dns::Name& n, const isc::dns::RRClass& c,
                     const isc::dns::RRType& t, const isc::dns::Section& sect,
                     const Op o) :
    qname(n), qclass(c), qtype(t), zone(NULL),
    section(sect), op(o), state(GETANSWER), flags(0)
{}

QueryTask::QueryTask(const isc::dns::Name& n, const isc::dns::RRClass& c,
                     const isc::dns::RRType& t, const isc::dns::Section& sect,
                     const State st) :
    qname(n), qclass(c), qtype(t), zone(NULL),
    section(sect), op(AUTH_QUERY), state(st), flags(0)
{}

QueryTask::QueryTask(const isc::dns::Name& n, const isc::dns::RRClass& c,
                     const isc::dns::RRType& t, const isc::dns::Section& sect,
                     const Op o, const State st) :
    qname(n), qclass(c), qtype(t), zone(NULL),
    section(sect), op(o), state(st), flags(0) 
{}

QueryTask::QueryTask(const isc::dns::Name& n, const isc::dns::RRClass& c,
                     const isc::dns::RRType& t, const Op o) :
    qname(n), qclass(c), qtype(t), zone(NULL),
    section(Section::ANSWER()),
    op(o), state(GETANSWER), flags(0)
{
    if (op != SIMPLE_QUERY) {
        throw "invalid constructor for this task operation";
    }
}

// A referral query doesn't need to specify section, state, or type.
QueryTask::QueryTask(const isc::dns::Name& n, const isc::dns::RRClass& c,
                     const Op o) :
    qname(n), qclass(c), qtype(RRType::ANY()), zone(NULL),
    section(Section::ANSWER()), op(o), state(GETANSWER),
    flags(0)
{
    if (op != REF_QUERY) {
        throw "invalid constructor for this task operation";
    }
}

QueryTask::QueryTask(const isc::dns::Name& n, const isc::dns::RRClass& c,
                     const isc::dns::Section& sect, const Op o,
                     const State st) :
        qname(n), qclass(c), qtype(RRType::ANY()), zone(NULL),
        section(sect), op(o), state(st), flags(0)
{
    if (op != GLUE_QUERY && op != NOGLUE_QUERY) {
        throw "invalid constructor for this task operation";
    }
}

Query::Query(Message& m, bool dnssec) :
    status_(PENDING), qname_(NULL), qclass_(NULL), qtype_(NULL),
    message_(&m), want_additional_(true), want_dnssec_(dnssec)
{
    // Check message formatting
    if (message_->getRRCount(Section::QUESTION()) != 1) {
        dns_throw(Unexpected, "malformed message: too many questions");
    }

    // Populate the query task queue with the initial question
    QuestionPtr question = *message_->beginQuestion();
    qname_ = &question->getName();
    qclass_ = &question->getClass();
    qtype_ = &question->getType();

    querytasks_.push(QueryTaskPtr(new QueryTask(*qname_, *qclass_, *qtype_,
                                                Section::ANSWER())));
}

}
}
