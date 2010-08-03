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

#include <boost/shared_ptr.hpp>

#include <datasrc/cache.h>
#include <datasrc/data_source.h>

#include <dns/name.h>
#include <dns/message.h>
#include <dns/rrtype.h>
#include <dns/rrclass.h>

#include <queue>

namespace isc {
namespace datasrc {

class Query;
typedef boost::shared_ptr<Query> QueryPtr;

// An individual task to be carried out by the query logic
class QueryTask {
private:
    /// Note: The copy constructor and the assignment operator are intentionally
    /// defined as private.
    QueryTask(const QueryTask& source);
    QueryTask& operator=(const QueryTask& source);
public:
    // XXX: Members are currently public, but should probably be
    // moved to private and wrapped in get() functions later.

    // The \c Query that this \c QueryTask was created to service.
    const Query& q;

    // The standard query tuple: qname/qclass/qtype.
    // Note that qtype is ignored in the GLUE_QUERY/NOGLUE_QUERY case.
    const isc::dns::Name qname;
    const isc::dns::RRClass qclass;
    const isc::dns::RRType qtype;

    // The section of the reply into which the data should be
    // written after it has been fetched from the data source.
    const isc::dns::Section section;

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
        REF_QUERY
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
    QueryTask(const Query& q, const isc::dns::Name& n,
              const isc::dns::RRType& t, const isc::dns::Section& sect);
    QueryTask(const Query& q, const isc::dns::Name& n,
              const isc::dns::RRType& t, const isc::dns::Section& sect, Op o);
    QueryTask(const Query& q, const isc::dns::Name& n,
              const isc::dns::RRType& t, const isc::dns::Section& sect,
              const State st);
    QueryTask(const Query& q, const isc::dns::Name& n,
              const isc::dns::RRType& t, const isc::dns::Section& sect,
              Op o, State st);

    // These are special constructors for particular query task types,
    // to simplify the code.
    //
    // A simple query doesn't need to specify section or state.
    QueryTask(const Query& q, const isc::dns::Name& n,
              const isc::dns::RRType& t, Op o);
    // A referral query doesn't need to specify section, state, or type.
    QueryTask(const Query& q, const isc::dns::Name& n, Op o);
    // A glue (or noglue) query doesn't need to specify type.
    QueryTask(const Query& q, const isc::dns::Name& n,
              const isc::dns::Section& sect, Op o, State st);

    ~QueryTask();
};

typedef boost::shared_ptr<QueryTask> QueryTaskPtr;
typedef std::queue<QueryTaskPtr> QueryTaskQueue;

// Data Source query
class Query {
public:
    // The state of a query: pending or answered.
    enum Status {
        PENDING,
        ANSWERED
    };

    ///
    /// \name Constructors, Assignment Operator and Destructor.
    ///
    /// Note: The copy constructor and the assignment operator are intentionally
    /// defined as private.
    //@{
private:
    Query(const Query& source);
    Query& operator=(const Query& source);
public:
    // Query constructor
    Query(isc::dns::Message& m, HotCache& c, bool dnssec);
    /// \brief The destructor.
    virtual ~Query();
    //@}

    // wantAdditional() == true indicates that additional-section data
    // should be looked up while processing this query.  false indicates
    // that we're only interested in answer-section data
    bool wantAdditional() { return (want_additional_); }
    void setWantAdditional(bool d) { want_additional_ = d; }

    // wantDnssec() == true indicates that DNSSEC data should be retrieved
    // from the data source when this query is being processed
    bool wantDnssec() const { return (want_dnssec_); }
    void setWantDnssec(bool d) { want_dnssec_ = d; }

    const isc::dns::Name& qname() const { return (*qname_); }
    const isc::dns::RRClass& qclass() const { return (*qclass_); }
    const isc::dns::RRType& qtype() const { return (*qtype_); }

    // Note: these can't be constant member functions because they expose
    // writable 'handles' of internal member variables.  It's questionable
    // whether we need these accessors in the first place because the
    // corresponding members are public (which itself is not a good practice
    // but it's a different topic), but at the moment we keep them.
    // We should definitely revisit the design later.
    isc::dns::Message& message() { return (*message_); }
    QueryTaskQueue& tasks() { return (querytasks_); }

    Status status() const { return (status_); }
    void setStatus(Status s) { status_ = s; }

    // Limit CNAME chains to 16 per query, to avoid loops
    inline bool tooMany() {
        if (++restarts_ > MAX_RESTARTS) {
            return (true);
        }
        return (false);
    }

    void setDatasrc(DataSrc* ds) { datasrc_ = ds; }
    DataSrc* datasrc() const { return (datasrc_); }

    // \brief The query cache.  This is a static member of class \c Query;
    // the same cache will be used by all instances.
    HotCache& getCache() const { return (*cache_); }

private:
    Status status_;

    const isc::dns::Name* qname_;
    const isc::dns::RRClass* qclass_;
    const isc::dns::RRType* qtype_;

    HotCache* cache_;
    DataSrc* datasrc_;

    isc::dns::Message* message_;
    QueryTaskQueue querytasks_;

    bool want_additional_;
    bool want_dnssec_;

    static const int MAX_RESTARTS = 16;
    int restarts_;
};

}
}


#endif

// Local Variables: 
// mode: c++
// End: 
