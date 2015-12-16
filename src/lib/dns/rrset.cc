// Copyright (C) 2010-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <algorithm>
#include <string>
#include <vector>

#include <boost/shared_ptr.hpp>
#include <boost/foreach.hpp>

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

    // In the case of an empty rrset, just print name, ttl, class, and
    // type
    if (it->isLast()) {
        // But only for class ANY or NONE
        if (getClass() != RRClass::ANY() &&
            getClass() != RRClass::NONE()) {
            isc_throw(EmptyRRset, "toText() is attempted for an empty RRset");
        }

        s += getName().toText() + " " + getTTL().toText() + " " +
             getClass().toText() + " " + getType().toText() + "\n";
        return (s);
    }

    do {
        s += getName().toText() + " " + getTTL().toText() + " " +
             getClass().toText() + " " + getType().toText() + " " +
             it->getCurrent().toText() + "\n";
        it->next();
    } while (!it->isLast());

    if (getRRsig()) {
        s += getRRsig()->toText();
    }

    return (s);
}

namespace { // unnamed namespace

// FIXME: This method's code should somehow be unified with
// BasicRRsetImpl::toWire() below to avoid duplication.
template <typename T>
inline unsigned int
rrsetToWire(const AbstractRRset& rrset, T& output, const size_t limit) {
    unsigned int n = 0;
    RdataIteratorPtr it = rrset.getRdataIterator();

    if (it->isLast()) {
        // empty rrsets are only allowed for classes ANY and NONE
        if (rrset.getClass() != RRClass::ANY() &&
            rrset.getClass() != RRClass::NONE()) {
            isc_throw(EmptyRRset, "toWire() is attempted for an empty RRset");
        }

        // For an empty RRset, write the name, type, class and TTL once,
        // followed by empty rdata.
        rrset.getName().toWire(output);
        rrset.getType().toWire(output);
        rrset.getClass().toWire(output);
        rrset.getTTL().toWire(output);
        output.writeUint16(0);
        // Still counts as 1 'rr'; it does show up in the message
        return (1);
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

} // end of unnamed namespace

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

    unsigned int toWire(AbstractMessageRenderer& renderer, size_t limit) const;

    Name name_;
    RRClass rrclass_;
    RRType rrtype_;
    RRTTL ttl_;
    // XXX: "list" is not a good name: It in fact isn't a list; more conceptual
    // name than a data structure name is generally better.  But since this
    // is only used in the internal implementation we'll live with it.
    vector<ConstRdataPtr> rdatalist_;
};

// FIXME: This method's code should somehow be unified with
// rrsetToWire() above to avoid duplication.
unsigned int
BasicRRsetImpl::toWire(AbstractMessageRenderer& renderer, size_t limit) const {
    if (rdatalist_.empty()) {
        // empty rrsets are only allowed for classes ANY and NONE
        if (rrclass_ != RRClass::ANY() &&
            rrclass_ != RRClass::NONE()) {
            isc_throw(EmptyRRset, "toWire() is attempted for an empty RRset");
        }

        // For an empty RRset, write the name, type, class and TTL once,
        // followed by empty rdata.
        name_.toWire(renderer);
        rrtype_.toWire(renderer);
        rrclass_.toWire(renderer);
        ttl_.toWire(renderer);
        renderer.writeUint16(0);
        // Still counts as 1 'rr'; it does show up in the message
        return (1);
    }

    unsigned int n = 0;

    // sort the set of Rdata based on rrset-order and sortlist, and possible
    // other options.  Details to be considered.
    BOOST_FOREACH(const ConstRdataPtr& rdata, rdatalist_) {
        const size_t pos0 = renderer.getLength();
        assert(pos0 < 65536);

        name_.toWire(renderer);
        rrtype_.toWire(renderer);
        rrclass_.toWire(renderer);
        ttl_.toWire(renderer);

        const size_t pos = renderer.getLength();
        renderer.skip(sizeof(uint16_t)); // leave the space for RDLENGTH
        rdata->toWire(renderer);
        renderer.writeUint16At(renderer.getLength() - pos - sizeof(uint16_t),
                               pos);

        if (limit > 0 && renderer.getLength() > limit) {
            // truncation is needed
            renderer.trim(renderer.getLength() - pos0);
            return (n);
        }
        ++n;
    }

    return (n);
}

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

void
BasicRRset::addRdata(const std::string& rdata_str) {
    addRdata(createRdata(getType(), getClass(), rdata_str));
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
BasicRRset::setTTL(const RRTTL& ttl) {
    impl_->ttl_ = ttl;
}

string
BasicRRset::toText() const {
    return (AbstractRRset::toText());
}

uint16_t
BasicRRset::getLength() const {
    uint16_t length = 0;
    RdataIteratorPtr it = getRdataIterator();

    if (it->isLast()) {
        // empty rrsets are only allowed for classes ANY and NONE
        if (getClass() != RRClass::ANY() &&
            getClass() != RRClass::NONE()) {
            isc_throw(EmptyRRset, "getLength() is attempted for an empty RRset");
        }

        // For an empty RRset, write the name, type, class and TTL once,
        // followed by empty rdata.
        length += getName().getLength();
        length += 2; // TYPE field
        length += 2; // CLASS field
        length += 4; // TTL field
        length += 2; // RDLENGTH field (=0 in wire format)

        return (length);
    }

    do {
        // This is a size_t as some of the following additions may
        // overflow due to a programming mistake somewhere.
        size_t rrlen = 0;

        rrlen += getName().getLength();
        rrlen += 2; // TYPE field
        rrlen += 2; // CLASS field
        rrlen += 4; // TTL field
        rrlen += 2; // RDLENGTH field
        rrlen += it->getCurrent().getLength();

        assert(length + rrlen < 65536);
        length += rrlen;

        it->next();
    } while (!it->isLast());

    return (length);
}

unsigned int
BasicRRset::toWire(OutputBuffer& buffer) const {
    return (AbstractRRset::toWire(buffer));
}

unsigned int
BasicRRset::toWire(AbstractMessageRenderer& renderer) const {
    const unsigned int rrs_written = impl_->toWire(renderer,
                                                   renderer.getLengthLimit());
    if (impl_->rdatalist_.size() > rrs_written) {
        renderer.setTruncated();
    }
    return (rrs_written);
}

RRset::RRset(const Name& name, const RRClass& rrclass,
            const RRType& rrtype, const RRTTL& ttl) :
    BasicRRset(name, rrclass, rrtype, ttl)
{
    rrsig_ = RRsetPtr();
}

RRset::~RRset() {}

unsigned int
RRset::getRRsigDataCount() const {
    if (rrsig_) {
        return (rrsig_->getRdataCount());
    } else {
        return (0);
    }
}

uint16_t
RRset::getLength() const {
    uint16_t length = BasicRRset::getLength();

    if (rrsig_) {
        const uint16_t rrsigs_length = rrsig_->getLength();
        // the uint16_ts are promoted to ints during addition below, so
        // it won't overflow a 16-bit register.
        assert(length + rrsigs_length < 65536);
        length += rrsigs_length;
    }

    return (length);
}

unsigned int
RRset::toWire(OutputBuffer& buffer) const {
    unsigned int rrs_written = BasicRRset::toWire(buffer);
    if (getRdataCount() > rrs_written) {
        return (rrs_written);
    }

    if (rrsig_) {
        rrs_written += rrsig_->toWire(buffer);
    }

    return (rrs_written);
}

unsigned int
RRset::toWire(AbstractMessageRenderer& renderer) const {
    unsigned int rrs_written = BasicRRset::toWire(renderer);
    if (getRdataCount() > rrs_written) {
        return (rrs_written);
    }

    if (rrsig_) {
        rrs_written += rrsig_->toWire(renderer);

        if (getRdataCount() + getRRsigDataCount() > rrs_written) {
            renderer.setTruncated();
        }
    }

    return (rrs_written);
}

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
