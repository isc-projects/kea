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

#include <dns/message.h>
#include <dns/rcode.h>

#include <datasrc/memory_datasrc.h>

#include <auth/query.h>

using namespace isc::dns;
using namespace isc::datasrc;

namespace isc {
namespace auth {

struct Query::QueryImpl {
    QueryImpl(const MemoryDataSrc& memory_datasrc, const Name& qname,
              const RRType& qtype, Message& response) :
        memory_datasrc_(memory_datasrc), qname_(qname), qtype_(qtype),
        response_(response)
    {}

    const MemoryDataSrc& memory_datasrc_;
    const Name& qname_;
    const RRType& qtype_;
    Message& response_;
};

Query::Query(const MemoryDataSrc& memory_datasrc, const Name& qname,
             const RRType& qtype, Message& response) :
    impl_(new QueryImpl(memory_datasrc, qname, qtype, response))
{}

Query::~Query() {
    delete impl_;
}

void
Query::process() const {
    const MemoryDataSrc::FindResult result =
        impl_->memory_datasrc_.findZone(impl_->qname_);
    bool keep_doing = true;

    if (result.code != result::SUCCESS &&
        result.code != result::PARTIALMATCH) {
        impl_->response_.setRcode(Rcode::SERVFAIL());
        return;
    }

    while (keep_doing) {
        keep_doing = false;
        Zone::FindResult db_result = result.zone->find(impl_->qname_,
                                                       impl_->qtype_);
        switch (db_result.code) {
            case Zone::SUCCESS:
                impl_->response_.setRcode(Rcode::NOERROR());
                impl_->response_.addRRset(Message::SECTION_ANSWER,
                            boost::const_pointer_cast<RRset>(db_result.rrset));
                // TODO : fill in authority and addtional sections.
                break;
            case Zone::DELEGATION:
                // TODO : add NS to authority section, fill in additional section.
                break;
            case Zone::NXDOMAIN:
                impl_->response_.setRcode(Rcode::NXDOMAIN());
                // TODO : add SOA to authority section
                break;
            case Zone::NXRRSET:
                impl_->response_.setRcode(Rcode::NXRRSET());
                // TODO : add SOA to authority section
                break;
            case Zone::CNAME:
            case Zone::DNAME:
                // TODO : replace qname, continue lookup
                keep_doing = true;
                break;
            // should not happen, catch programming error here.
            default:
                break;
                isc_throw(Unexpected,
                          "Zone::find return unexpected result.");
        }
    }
}
}
}
