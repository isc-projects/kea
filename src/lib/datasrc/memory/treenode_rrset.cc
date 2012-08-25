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

#include <string>

using namespace isc::dns;
using namespace isc::dns::rdata;

namespace isc {
namespace datasrc {
namespace memory {

const Name&
TreeNodeRRset::getName() const {
    isc_throw(Unexpected, "unexpected method called on TreeNodeRRset");
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


// needed
unsigned int
TreeNodeRRset::toWire(AbstractMessageRenderer& /*renderer*/) const {
    isc_throw(Unexpected, "unexpected method called on TreeNodeRRset");
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
