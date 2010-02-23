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
#include <string>
#include <vector>

#include <boost/shared_ptr.hpp>

#include "buffer.h"
#include "messagerenderer.h"
#include "name.h"
#include "rrclass.h"
#include "rrtype.h"
#include "rrttl.h"
#include "rrset.h"

using namespace std;
using namespace isc::dns;
using namespace isc::dns::rdata;

namespace isc {
namespace dns {
void
AbstractRRset::addRdata(const Rdata& rdata)
{
    addRdata(createRdata(getType(), getClass(), rdata));
}

string
AbstractRRset::toText() const
{
    string s;
    RdataIteratorPtr it = getRdataIterator();

    it->first();
    if (it->isLast()) {
        dns_throw(EmptyRRset, "ToText() is attempted for an empty RRset");
    }

    do {
        s += getName().toText() + " " + getTTL().toText() + " " +
            getClass().toText() + " " + getType().toText() + " " +
            it->getCurrent().toText() + "\n";
        it->next();
    } while (!it->isLast());

    return (s);
}   

namespace {
template <typename T>
inline unsigned int
rrsetToWire(const AbstractRRset& rrset, T& output)
{
    unsigned int n = 0;
    RdataIteratorPtr it = rrset.getRdataIterator();

    it->first();
    if (it->isLast()) {
        dns_throw(EmptyRRset, "ToWire() is attempted for an empty RRset");
    }

    // sort the set of Rdata based on rrset-order and sortlist, and possible
    // other options.  Details to be considered.
    do {
        rrset.getName().toWire(output);
        rrset.getType().toWire(output);
        rrset.getClass().toWire(output);
        rrset.getTTL().toWire(output);

        size_t pos = output.getLength();
        output.skip(sizeof(uint16_t)); // leave the space for RDLENGTH
        it->getCurrent().toWire(output);
        output.writeUint16At(output.getLength() - pos - sizeof(uint16_t), pos);

        it->next();
        ++n;
    } while (!it->isLast());

    return (n);
}
}

unsigned int
AbstractRRset::toWire(OutputBuffer& buffer) const
{
    return (rrsetToWire<OutputBuffer>(*this, buffer));
}

unsigned int
AbstractRRset::toWire(MessageRenderer& renderer) const
{
    return (rrsetToWire<MessageRenderer>(*this, renderer));
}

ostream&
operator<<(ostream& os, const AbstractRRset& rrset)
{
    os << rrset.toText();
    return (os);
}

/// \brief This encapsulates the actual implementation of the \c BasicRRset
/// class.  It's hidden from applications.
class BasicRRsetImpl {
public:
    BasicRRsetImpl(const Name& name, const RRClass& rrclass,
                   const RRType& rrtype, const RRTTL& ttl) :
        name_(name), rrclass_(rrclass), rrtype_(rrtype), ttl_(ttl) {}
    Name name_;
    RRClass rrclass_;
    RRType rrtype_;
    RRTTL ttl_;
    // XXX: "list" is not a good name: It in fact isn't a list; more conceptual
    // name than a data structure name is generally better.  But since this
    // is only used in the internal implementation we'll live with it.
    vector<ConstRdataPtr> rdatalist_;
};

BasicRRset::BasicRRset(const Name& name, const RRClass& rrclass,
                       const RRType& rrtype, const RRTTL& ttl)
{
    impl_ = new BasicRRsetImpl(name, rrclass, rrtype, ttl);
}

BasicRRset::~BasicRRset()
{
    delete impl_;
}

void
BasicRRset::addRdata(ConstRdataPtr rdata)
{
    impl_->rdatalist_.push_back(rdata);
}

void
BasicRRset::addRdata(const Rdata& rdata)
{
    AbstractRRset::addRdata(rdata);
}

unsigned int
BasicRRset::getRdataCount() const
{
    return (impl_->rdatalist_.size());
}

const Name&
BasicRRset::getName() const
{
    return (impl_->name_);
}

const RRClass&
BasicRRset::getClass() const
{
    return (impl_->rrclass_);
}

const RRType&
BasicRRset::getType() const
{
    return (impl_->rrtype_);
}

const RRTTL&
BasicRRset::getTTL() const
{
    return (impl_->ttl_);
}

void
BasicRRset::setName(const Name& name)
{
    impl_->name_ = name;
}

void
BasicRRset::setTTL(const RRTTL& ttl)
{
    impl_->ttl_ = ttl;
}

string
BasicRRset::toText() const
{
    return (AbstractRRset::toText());
}

unsigned int
BasicRRset::toWire(OutputBuffer& buffer) const
{
    return (AbstractRRset::toWire(buffer));
}

unsigned int
BasicRRset::toWire(MessageRenderer& renderer) const
{
    return (AbstractRRset::toWire(renderer));
}

namespace {
class BasicRdataIterator : public RdataIterator {
private:
    BasicRdataIterator() {}
public:
    BasicRdataIterator(const std::vector<rdata::ConstRdataPtr>& datavector) :
        datavector_(&datavector) {}
    ~BasicRdataIterator() {}
    virtual void first() { it_ = datavector_->begin(); }
    virtual void next() { ++it_; }
    virtual const rdata::Rdata& getCurrent() const { return (**it_); }
    virtual bool isLast() const { return (it_ == datavector_->end()); }
private:
    const std::vector<rdata::ConstRdataPtr>* datavector_;
    std::vector<rdata::ConstRdataPtr>::const_iterator it_;
};
}

RdataIteratorPtr
BasicRRset::getRdataIterator() const
{
    return (RdataIteratorPtr(new BasicRdataIterator(impl_->rdatalist_)));
}
}
}
