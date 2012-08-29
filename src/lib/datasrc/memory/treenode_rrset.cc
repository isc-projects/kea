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

using namespace isc::dns;
using namespace isc::dns::rdata;

namespace isc {
namespace datasrc {
namespace memory {

const Name&
TreeNodeRRset::getName() const {
    if (name_ == NULL) {
        uint8_t labels_buf[LabelSequence::MAX_SERIALIZED_LENGTH];
        const LabelSequence node_labels = node_->getAbsoluteLabels(labels_buf);
        size_t data_len;
        const uint8_t* data = node_labels.getData(&data_len);
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

// needed
std::string
TreeNodeRRset::toText() const {
    isc_throw(Unexpected, "unexpected method called on TreeNodeRRset");
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
}

unsigned int
TreeNodeRRset::toWire(AbstractMessageRenderer& renderer) const {
    RdataReader reader(rrclass_, rdataset_->type, rdataset_->getDataBuf(),
                       rdataset_->getRdataCount(), rrsig_count_,
                       boost::bind(renderName, _1, _2, &renderer),
                       boost::bind(renderData, _1, _2, &renderer));

    // Get the owner name of the RRset in the form of LabelSequence.
    uint8_t labels_buf[LabelSequence::MAX_SERIALIZED_LENGTH];
    const LabelSequence node_labels = node_->getAbsoluteLabels(labels_buf);

    size_t i = 0;
    for (; i < rdataset_->getRdataCount(); ++i) {
        //const size_t pos0 = output.getLength();

        renderer.writeName(node_labels, true);
        rdataset_->type.toWire(renderer);
        rrclass_.toWire(renderer);
        renderer.writeData(rdataset_->getTTLData(), sizeof(uint32_t));

        const size_t pos = renderer.getLength();
        renderer.skip(sizeof(uint16_t)); // leave the space for RDLENGTH
        const bool rendered = reader.iterateRdata();
        assert(rendered == true);
        renderer.writeUint16At(renderer.getLength() - pos - sizeof(uint16_t),
                               pos);

        // for truncation processing
    }
    const bool rendered = reader.iterateRdata();
    assert(rendered == false); // we should've reached the end

    size_t j = 0;
    if (dnssec_ok_) {
        for (; j < rrsig_count_; ++j) {
            // TBD: truncation consideration

            renderer.writeName(node_labels, true);
            RRType::RRSIG().toWire(renderer);
            rrclass_.toWire(renderer);
            renderer.writeData(rdataset_->getTTLData(), sizeof(uint32_t));

            const size_t pos = renderer.getLength();
            renderer.skip(sizeof(uint16_t)); // leave the space for RDLENGTH
            assert(reader.iterateSingleSig() == true);
            renderer.writeUint16At(renderer.getLength() - pos -
                                   sizeof(uint16_t), pos);
        }
        assert(reader.iterateSingleSig() == false);
    }

    return (i + j);
}

unsigned int
TreeNodeRRset::toWire(isc::util::OutputBuffer& /*buffer*/) const {
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


// needed
RdataIteratorPtr
TreeNodeRRset::getRdataIterator() const {
    isc_throw(Unexpected, "unexpected method called on TreeNodeRRset");
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

// needed
bool
TreeNodeRRset::isSameKind(const AbstractRRset& /*other*/) const {
    isc_throw(Unexpected, "unexpected method called on TreeNodeRRset");
}

} // namespace memory
} // namespace datasrc
} // datasrc isc
