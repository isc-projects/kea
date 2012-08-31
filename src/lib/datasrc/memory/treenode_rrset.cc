// Copyright (C) 2012  Internet Systems Consortium, Inc. ("ISC")
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

#include <exceptions/exceptions.h>

#include <util/buffer.h>

#include <dns/messagerenderer.h>
#include <dns/name.h>
#include <dns/rrclass.h>
#include <dns/rrtype.h>
#include <dns/rrttl.h>
#include <dns/rdata.h>
#include <dns/rrset.h>

#include "treenode_rrset.h"
#include "rdata_serialization.h"

#include <boost/bind.hpp>

#include <cassert>
#include <string>
#include <vector>

using namespace isc::dns;
using namespace isc::dns::rdata;

namespace isc {
namespace datasrc {
namespace memory {

const Name&
TreeNodeRRset::getName() const {
    if (realname_ != NULL) {
        return (*realname_);
    }
    if (name_ == NULL) {
        uint8_t labels_buf[LabelSequence::MAX_SERIALIZED_LENGTH];
        const LabelSequence name_labels = getOwnerLabels(labels_buf);
        size_t data_len;
        const uint8_t* data = name_labels.getData(&data_len);
        util::InputBuffer buffer(data, data_len);
        name_ = new Name(buffer);
    }
    return (*name_);
}

const RRTTL&
TreeNodeRRset::getTTL() const {
    isc_throw(Unexpected, "unexpected method called on TreeNodeRRset");
}

void
TreeNodeRRset::setName(const Name&) {
    isc_throw(Unexpected, "unexpected method called on TreeNodeRRset");
}

void
TreeNodeRRset::setTTL(const RRTTL&) {
    isc_throw(Unexpected, "unexpected method called on TreeNodeRRset");
}

std::string
TreeNodeRRset::toText() const {
    // Create TTL from internal data
    util::InputBuffer ttl_buffer(rdataset_->getTTLData(), sizeof(uint32_t));
    const RRTTL ttl(ttl_buffer);

    // Dump the main RRset, if not empty
    std::string ret;
    RRsetPtr tmp_rrset;
    for (RdataIteratorPtr rit = getRdataIterator();
         !rit->isLast();
         rit->next())
    {
        if (!tmp_rrset) {
            tmp_rrset = RRsetPtr(new RRset(getName(), rrclass_, getType(),
                                           ttl));
        }
        tmp_rrset->addRdata(rit->getCurrent());
    }
    if (tmp_rrset) {
        ret = tmp_rrset->toText();
    }

    // Dump any RRSIGs
    tmp_rrset.reset();
    for (RdataIteratorPtr rit = getSigRdataIterator();
         !rit->isLast();
         rit->next())
    {
        if (!tmp_rrset) {
            tmp_rrset = RRsetPtr(new RRset(getName(), rrclass_,
                                           RRType::RRSIG(), ttl));
        }
        tmp_rrset->addRdata(rit->getCurrent());
    }
    if (tmp_rrset) {
        ret += tmp_rrset->toText();
    }

    return (ret);
}

namespace {
void
renderName(const LabelSequence& name_labels, RdataNameAttributes attr,
           AbstractMessageRenderer* renderer)
{
    renderer->writeName(name_labels, (attr & NAMEATTR_COMPRESSIBLE) != 0);
}

void
renderData(const void* data, size_t data_len,
           AbstractMessageRenderer* renderer)
{
    renderer->writeData(data, data_len);
}

// Common code logic for rendering a single (either main or RRSIG) RRset.
size_t
writeRRs(AbstractMessageRenderer& renderer, size_t rr_count,
         const LabelSequence& name_labels, const RRType& rrtype,
         const RRClass& rrclass, const void* ttl_data,
         RdataReader& reader, bool (RdataReader::* rdata_iterate_fn)())
{
    for (size_t i = 0; i < rr_count; ++i) {
        const size_t pos0 = renderer.getLength();

        // Name, type, class, TTL
        renderer.writeName(name_labels, true);
        rrtype.toWire(renderer);
        rrclass.toWire(renderer);
        renderer.writeData(ttl_data, sizeof(uint32_t));

        // RDLEN and RDATA
        const size_t pos = renderer.getLength();
        renderer.skip(sizeof(uint16_t)); // leave the space for RDLENGTH
        const bool rendered = (reader.*rdata_iterate_fn)();
        assert(rendered == true);
        renderer.writeUint16At(renderer.getLength() - pos - sizeof(uint16_t),
                               pos);

        // Check if truncation would happen
        if (renderer.getLength() > renderer.getLengthLimit()) {
            renderer.trim(renderer.getLength() - pos0);
            renderer.setTruncated();
            return (i);
        }
    }
    return (rr_count);
}
}

unsigned int
TreeNodeRRset::toWire(AbstractMessageRenderer& renderer) const {
    RdataReader reader(rrclass_, rdataset_->type, rdataset_->getDataBuf(),
                       rdataset_->getRdataCount(), rrsig_count_,
                       boost::bind(renderName, _1, _2, &renderer),
                       boost::bind(renderData, _1, _2, &renderer));

    // Get the owner name of the RRset in the form of LabelSequence.
    uint8_t labels_buf[LabelSequence::MAX_SERIALIZED_LENGTH];
    const LabelSequence name_labels = getOwnerLabels(labels_buf);

    // Render the main (non RRSIG) RRs
    const size_t rendered_rdata_count =
        writeRRs(renderer, rdataset_->getRdataCount(), name_labels,
                 rdataset_->type, rrclass_, rdataset_->getTTLData(), reader,
                 &RdataReader::iterateRdata);
    if (renderer.isTruncated()) {
        return (rendered_rdata_count);
    }
    const bool rendered = reader.iterateRdata();
    assert(rendered == false); // we should've reached the end

    // Render any RRSIGs, if we supposed to do so
    const size_t rendered_rrsig_count = dnssec_ok_ ?
        writeRRs(renderer, rrsig_count_, name_labels, RRType::RRSIG(),
                 rrclass_, rdataset_->getTTLData(), reader,
                 &RdataReader::iterateSingleSig) : 0;

    return (rendered_rdata_count + rendered_rrsig_count);
}

unsigned int
TreeNodeRRset::toWire(isc::util::OutputBuffer&) const {
    isc_throw(Unexpected, "unexpected method called on TreeNodeRRset");
}

void
TreeNodeRRset::addRdata(rdata::ConstRdataPtr) {
    isc_throw(Unexpected, "unexpected method called on TreeNodeRRset");
}

void
TreeNodeRRset::addRdata(const rdata::Rdata&) {
    isc_throw(Unexpected, "unexpected method called on TreeNodeRRset");
}

namespace {
// In this namespace we define a set of helper stuff to implement the
// RdataIterator for the TreeNodeRRset.  We should eventually optimize
// the code so that performance sensitive path won't require the iterator,
// so, at the moment, the implementation is straightforward, but less
// efficient one: It builds a vector of Rdata objects on construction,
// and its getCurrent() returns the stored data.

class TreeNodeRdataIterator : public RdataIterator {
public:
    TreeNodeRdataIterator(const std::vector<ConstRdataPtr>& rdata_list) :
        rdata_list_(rdata_list), rdata_it_(rdata_list_.begin())
    {}
    virtual void first() { rdata_it_ = rdata_list_.begin(); }
    virtual void next() {
        ++rdata_it_;
    }
    virtual const rdata::Rdata& getCurrent() const {
        return (**rdata_it_);
    }
    virtual bool isLast() const { return (rdata_it_ == rdata_list_.end()); }
private:
    const std::vector<ConstRdataPtr> rdata_list_;
    std::vector<ConstRdataPtr>::const_iterator rdata_it_;
};

void
renderNameToBuffer(const LabelSequence& name_labels, RdataNameAttributes,
                   util::OutputBuffer* buffer)
{
    size_t data_len;
    const uint8_t *data = name_labels.getData(&data_len);
    buffer->writeData(data, data_len);
}

void
renderDataToBuffer(const void* data, size_t data_len,
                   util::OutputBuffer* buffer)
{
    buffer->writeData(data, data_len);
}
}

RdataIteratorPtr
TreeNodeRRset::getRdataIteratorInternal(bool is_rrsig, size_t count) const {
    util::OutputBuffer buffer(0);
    RdataReader reader(rrclass_, rdataset_->type, rdataset_->getDataBuf(),
                       rdataset_->getRdataCount(), rrsig_count_,
                       boost::bind(renderNameToBuffer, _1, _2, &buffer),
                       boost::bind(renderDataToBuffer, _1, _2, &buffer));

    std::vector<ConstRdataPtr> rdata_list;
    for (size_t i = 0; i < count; ++i) {
        buffer.clear();
        const bool rendered = is_rrsig ? reader.iterateSingleSig() :
            reader.iterateRdata();
        assert(rendered == true);
        util::InputBuffer ib(buffer.getData(), buffer.getLength());
        rdata_list.push_back(
            createRdata(is_rrsig ? RRType::RRSIG() : rdataset_->type, rrclass_,
                        ib, ib.getLength()));
    }
    return (RdataIteratorPtr(new TreeNodeRdataIterator(rdata_list)));
}

RdataIteratorPtr
TreeNodeRRset::getRdataIterator() const {
    return (getRdataIteratorInternal(false, rdataset_->getRdataCount()));
}

RdataIteratorPtr
TreeNodeRRset::getSigRdataIterator() const {
    return (getRdataIteratorInternal(true, dnssec_ok_ ? rrsig_count_ : 0));
}

RRsetPtr
TreeNodeRRset::getRRsig() const {
    isc_throw(Unexpected, "unexpected method called on TreeNodeRRset");
}

void
TreeNodeRRset::addRRsig(const rdata::ConstRdataPtr&) {
    isc_throw(Unexpected, "unexpected method called on TreeNodeRRset");
}

void
TreeNodeRRset::addRRsig(const rdata::RdataPtr&) {
    isc_throw(Unexpected, "unexpected method called on TreeNodeRRset");
}

void
TreeNodeRRset::addRRsig(const AbstractRRset&) {
    isc_throw(Unexpected, "unexpected method called on TreeNodeRRset");
}

void
TreeNodeRRset::addRRsig(const ConstRRsetPtr&) {
    isc_throw(Unexpected, "unexpected method called on TreeNodeRRset");
}

void
TreeNodeRRset::addRRsig(const RRsetPtr&) {
    isc_throw(Unexpected, "unexpected method called on TreeNodeRRset");
}

void
TreeNodeRRset::removeRRsig() {
    isc_throw(Unexpected, "unexpected method called on TreeNodeRRset");
}

bool
TreeNodeRRset::isSameKind(const AbstractRRset& abs_other) const {
    const TreeNodeRRset* other =
        dynamic_cast<const TreeNodeRRset*>(&abs_other);
    if (other != NULL) {
        // If type is different, they are not the same kind
        if (rdataset_ != other->rdataset_) {
            return (false);
        }
        // Same for the owner name.  Comparing the nodes also detect
        // the case where RR classes are different (see the method description
        // of the header for details).
        if (node_ != other->node_ ) {
            return (false);
        }
        // If one is constructed with a "real name" and the other isn't
        // *we consider* them different.
        if ((realname_ == NULL && other->realname_ != NULL) ||
            (realname_ != NULL && other->realname_ == NULL)) {
            return (false);
        }
        // If both are constructed with a "real name", we compare their names
        // (as label sequences) explicitly.
        if (realname_ != NULL && other->realname_ != NULL &&
            realname_->nequals(*other->realname_)) {
            return (false);
        }
        return (true);
    }
    return (AbstractRRset::isSameKind(abs_other));
}

} // namespace memory
} // namespace datasrc
} // datasrc isc
