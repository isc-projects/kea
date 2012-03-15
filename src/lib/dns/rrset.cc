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

#include <algorithm>
#include <string>
#include <vector>

#include <boost/shared_ptr.hpp>

#include <util/buffer.h>
#include <dns/messagerenderer.h>
#include <dns/name.h>
#include <dns/rrclass.h>
#include <dns/rrtype.h>
#include <dns/rrttl.h>
#include <dns/rrset.h>

using namespace std;
using namespace isc::dns;
using namespace isc::util;
using namespace isc::dns::rdata;

namespace isc {
namespace dns {
void
AbstractRRset::addRdata(const Rdata& rdata) {
    addRdata(createRdata(getType(), getClass(), rdata));
}

string
AbstractRRset::toText() const {
    string s;
    RdataIteratorPtr it = getRdataIterator();

    if (it->isLast()) {
        isc_throw(EmptyRRset, "ToText() is attempted for an empty RRset");
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
rrsetToWire(const AbstractRRset& rrset, T& output, const size_t limit) {
    unsigned int n = 0;
    RdataIteratorPtr it = rrset.getRdataIterator();

    if (it->isLast()) {
        isc_throw(EmptyRRset, "ToWire() is attempted for an empty RRset");
    }

    // sort the set of Rdata based on rrset-order and sortlist, and possible
    // other options.  Details to be considered.
    do {
        const size_t pos0 = output.getLength();
        assert(pos0 < 65536);

        rrset.getName().toWire(output);
        rrset.getType().toWire(output);
        rrset.getClass().toWire(output);
        rrset.getTTL().toWire(output);

        const size_t pos = output.getLength();
        output.skip(sizeof(uint16_t)); // leave the space for RDLENGTH
        it->getCurrent().toWire(output);
        output.writeUint16At(output.getLength() - pos - sizeof(uint16_t), pos);

        if (limit > 0 && output.getLength() > limit) {
            // truncation is needed
            output.trim(output.getLength() - pos0);
            return (n);
        }

        it->next();
        ++n;
    } while (!it->isLast());

    return (n);
}
}

unsigned int
AbstractRRset::toWire(OutputBuffer& buffer) const {
    return (rrsetToWire<OutputBuffer>(*this, buffer, 0));
}

unsigned int
AbstractRRset::toWire(AbstractMessageRenderer& renderer) const {
    const unsigned int rrs_written = rrsetToWire<AbstractMessageRenderer>(
        *this, renderer, renderer.getLengthLimit());
    if (getRdataCount() > rrs_written) {
        renderer.setTruncated();
    }
    return (rrs_written);
}

bool
AbstractRRset::isSameKind(const AbstractRRset& other) const {
  // Compare classes last as they're likely to be identical. Compare
  // names late in the list too, as these are expensive. So we compare
  // types first, names second and classes last.
  return (getType() == other.getType() &&
	  getName() == other.getName() &&
	  getClass() == other.getClass());
}

bool
AbstractRRset::lthan(const AbstractRRset& other) const {

    // Check on type first...
    const uint16_t my_type = getType().getCode();
    const uint16_t other_type = other.getType().getCode();
    if (my_type < other_type) {
        return (true);

    } else if (my_type == other_type) {
        // Types equal, so check class
        const uint16_t my_class = getClass().getCode();
        const uint16_t other_class = other.getClass().getCode();
        if (my_class < other_class) {
            return (true);

        } else if (my_class == other_class) {
            // Class equal, so check name
            return (getName().lthan(other.getName()));

        } else {
            return (false);
        }

    } else {
        return (false);
    }
}

ostream&
operator<<(ostream& os, const AbstractRRset& rrset) {
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

BasicRRset::~BasicRRset() {
    delete impl_;
}

void
BasicRRset::addRdata(ConstRdataPtr rdata) {
    impl_->rdatalist_.push_back(rdata);
}

void
BasicRRset::addRdata(const Rdata& rdata) {
    AbstractRRset::addRdata(rdata);
}

unsigned int
BasicRRset::getRdataCount() const {
    return (impl_->rdatalist_.size());
}

const Name&
BasicRRset::getName() const {
    return (impl_->name_);
}

const RRClass&
BasicRRset::getClass() const {
    return (impl_->rrclass_);
}

const RRType&
BasicRRset::getType() const {
    return (impl_->rrtype_);
}

const RRTTL&
BasicRRset::getTTL() const {
    return (impl_->ttl_);
}

void
BasicRRset::setName(const Name& name) {
    impl_->name_ = name;
}

void
BasicRRset::setTTL(const RRTTL& ttl) {
    impl_->ttl_ = ttl;
}

string
BasicRRset::toText() const {
    return (AbstractRRset::toText());
}

unsigned int
BasicRRset::toWire(OutputBuffer& buffer) const {
    return (AbstractRRset::toWire(buffer));
}

unsigned int
BasicRRset::toWire(AbstractMessageRenderer& renderer) const {
    return (AbstractRRset::toWire(renderer));
}

RRset::RRset(const Name& name, const RRClass& rrclass,
            const RRType& rrtype, const RRTTL& ttl) :
    BasicRRset(name, rrclass, rrtype, ttl)
{
    rrsig_ = RRsetPtr();
}

RRset::~RRset() {}

namespace {
class BasicRdataIterator : public RdataIterator {
private:
    BasicRdataIterator() {}
public:
    BasicRdataIterator(const std::vector<rdata::ConstRdataPtr>& datavector) :
        datavector_(&datavector), it_(datavector_->begin())
    {}
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
BasicRRset::getRdataIterator() const {
    return (RdataIteratorPtr(new BasicRdataIterator(impl_->rdatalist_)));
}
}
}
