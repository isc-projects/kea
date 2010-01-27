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

#include <string>
#include <vector>

#include <dns/cpp/buffer.h>
#include <dns/cpp/messagerenderer.h>
#include <dns/cpp/name.h>
#include <dns/cpp/rdata.h>
#include <dns/cpp/rrclass.h>
#include <dns/cpp/rrtype.h>
#include <dns/cpp/rrttl.h>
#include <dns/cpp/rrset.h>

#include "builtin.h"

using namespace std;
using namespace isc::dns;
using namespace isc::dns::rdata;

namespace {
const Name authors_name("authors.bind");
const Name version_name("version.bind");

const char* authors[] = {
    "Han Feng",
    "Kazunori Fujiwara",
    "Michael Graff",
    "Evan Hunt",
    "Jelte Jansen",
    "Jin Jian",
    "JINMEI Tatuya",
    "Naoki Kambe",
    "Shane Kerr",
    "Zhang Likun",
    "Jeremy C. Reed",
    NULL
};

const char* version[] = {
    "BIND10 0.0.1",
    NULL
};

const char* author_authorities[] = {
    "authors.bind",
    NULL
};

const char* version_authorities[] = {
    "version.bind",
    NULL
};

class BuiltinRRset : public AbstractRRset {
private:
    BuiltinRRset(const BuiltinRRset& source);
    void operator=(const BuiltinRRset& source);
public:
    BuiltinRRset(const Name& name, const RRType& rrtype,
                 const char** rdata_string_list);
    virtual void addRdata(const rdata::RdataPtr rdata)
    {
        // ignore it (or we might throw an exception)
    }
    virtual unsigned int getRdataCount() const { return (num_rdata_); }
    virtual const Name& getName() const { return (name_); }
    virtual const RRClass& getClass() const { return (rrclass_); }
    virtual const RRType& getType() const { return (rrtype_); }
    virtual const RRTTL& getTTL() const { return (rrttl_); }
    virtual void setTTL(const RRTTL& ttl)
    {
        // ignore it (or we might throw an exception)
    }
    virtual unsigned int toWire(MessageRenderer& renderer) const;
    virtual RdataIteratorPtr getRdataIterator() const;

    const Name name_;
    const RRType rrtype_;
    const RRClass rrclass_;
    const RRTTL rrttl_;
    vector<RdataPtr> rdatavector_;
    unsigned int num_rdata_;
    OutputBuffer wire_data_;    // pre-rendered RRset
    size_t data_offset_;        // offset to the RRset data

    static const size_t DATA_OFFSET = 12; // length of DNS header
};

class BuiltinRdataIterator : public RdataIterator {
private:
    BuiltinRdataIterator() {}
public:
    BuiltinRdataIterator(const vector<RdataPtr>& datavector) :
        datavector_(&datavector) {}
    ~BuiltinRdataIterator() {}
    virtual void first() { it_ = datavector_->begin(); }
    virtual void next() { ++it_; }
    virtual const rdata::Rdata& getCurrent() const { return (**it_); }
    virtual bool isLast() const { return (it_ == datavector_->end()); }
private:
    const vector<RdataPtr>* datavector_;
    vector<RdataPtr>::const_iterator it_;
};
}

BuiltinRRset::BuiltinRRset(const Name& name, const RRType& rrtype,
                           const char** rdata_string_list) :
    name_(name), rrtype_(rrtype), rrclass_(RRClass::CH()), rrttl_(RRTTL(0)),
    num_rdata_(0), wire_data_(512)
{
    MessageRenderer renderer(wire_data_);
    renderer.skip(DATA_OFFSET); // leave the space for the DNS header
    renderer.writeName(name);
    data_offset_ = renderer.getLength(); // remember the start position

    RRset tmprrset(name, rrclass_, rrtype_, rrttl_);

    for (int i = 0; rdata_string_list[i] != NULL; ++i) {
        RdataPtr rdata = createRdata(rrtype_, rrclass_,
                                     string(rdata_string_list[i]));
        rdatavector_.push_back(rdata);
        tmprrset.addRdata(rdata);
    }

    // pre-render the RRset
    tmprrset.toWire(renderer);
    num_rdata_ = rdatavector_.size();
}

unsigned int
BuiltinRRset::toWire(MessageRenderer& renderer) const
{
    // XXX: we should confirm the query name matches the pre-rendered data
    // and it's stored in the Question section.  This proof-of-concept
    // implementation omits the check for brevity.
    renderer.writeData(static_cast<const uint8_t*>(wire_data_.getData())
                       + data_offset_, wire_data_.getLength() - data_offset_);
    return (num_rdata_);
}

RdataIteratorPtr
BuiltinRRset::getRdataIterator() const
{
    return (RdataIteratorPtr(new BuiltinRdataIterator(rdatavector_)));
}

struct BuiltinRRsetsImpl {
    BuiltinRRsetsImpl(const Name& answer_name, const char** answers,
                      const char** authorities);
    RRsetPtr rrset_answer;
    RRsetPtr rrset_authority;
};

BuiltinRRsetsImpl::BuiltinRRsetsImpl(const Name& answer_name,
                                     const char** answers,
                                     const char** authorities)
{
    rrset_answer = RRsetPtr(new BuiltinRRset(answer_name, RRType::TXT(),
                                             answers));
    rrset_authority = RRsetPtr(new BuiltinRRset(answer_name, RRType::NS(),
                                                authorities));
}

BuiltinRRsets::BuiltinRRsets(const Name& name,
                             const char** answers,
                             const char** authorities)
{
    impl_ = new BuiltinRRsetsImpl(name, answers, authorities);
}

BuiltinRRsets::~BuiltinRRsets()
{
    delete impl_;
}

RRsetPtr
BuiltinRRsets::getAnswer() const
{
    return (impl_->rrset_answer);
}

RRsetPtr
BuiltinRRsets::getAuthority() const
{
    return (impl_->rrset_authority);
}

const BuiltinRRsets&
getBuiltinAuthors()
{
    static BuiltinRRsets builtin_authors(authors_name, authors,
                                         author_authorities);
    return (builtin_authors);
}

const BuiltinRRsets&
getBuiltinVersion()
{
    static BuiltinRRsets builtin_version(version_name, version,
                                         version_authorities);
    return (builtin_version);
}
