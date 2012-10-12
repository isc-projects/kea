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

#include <datasrc/memory/zone_data_loader.h>

#include <dns/rdataclass.h>

#include <boost/foreach.hpp>

using namespace isc::dns;
using namespace isc::dns::rdata;

namespace isc {
namespace datasrc {
namespace memory {

void
ZoneDataLoader::addFromLoad(const ConstRRsetPtr& rrset) {
    // If we see a new name, flush the temporary holders, adding the
    // pairs of RRsets and RRSIGs of the previous name to the zone.
    if ((!node_rrsets_.empty() || !node_rrsigsets_.empty()) &&
        (getCurrentName() != rrset->getName())) {
        flushNodeRRsets();
    }

    // Store this RRset until it can be added to the zone.  The current
    // implementation requires RRs of the same RRset should be added at
    // once, so we check the "duplicate" here.
    const bool is_rrsig = rrset->getType() == RRType::RRSIG();
    NodeRRsets& node_rrsets = is_rrsig ? node_rrsigsets_ : node_rrsets_;
    const RRType& rrtype = is_rrsig ? getCoveredType(rrset) : rrset->getType();
    if (!node_rrsets.insert(NodeRRsetsVal(rrtype, rrset)).second) {
        isc_throw(ZoneDataUpdater::AddError,
                  "Duplicate add of the same type of"
                  << (is_rrsig ? " RRSIG" : "") << " RRset: "
                  << rrset->getName() << "/" << rrtype);
    }

    if (rrset->getRRsig()) {
        addFromLoad(rrset->getRRsig());
    }
}

void
ZoneDataLoader::flushNodeRRsets() {
    BOOST_FOREACH(NodeRRsetsVal val, node_rrsets_) {
        // Identify the corresponding RRSIG for the RRset, if any.  If
        // found add both the RRset and its RRSIG at once.
        ConstRRsetPtr sig_rrset;
        NodeRRsets::iterator sig_it = node_rrsigsets_.find(val.first);
        if (sig_it != node_rrsigsets_.end()) {
            sig_rrset = sig_it->second;
            node_rrsigsets_.erase(sig_it);
        }
        updater_.add(val.second, sig_rrset);
    }

    // Right now, we don't accept RRSIG without covered RRsets (this
    // should eventually allowed, but to do so we'll need to update the
    // finder).
    if (!node_rrsigsets_.empty()) {
        isc_throw(ZoneDataUpdater::AddError,
                  "RRSIG is added without covered RRset for "
                  << getCurrentName());
    }

    node_rrsets_.clear();
    node_rrsigsets_.clear();
}

RRType
ZoneDataLoader::getCoveredType(const ConstRRsetPtr& sig_rrset) {
    RdataIteratorPtr it = sig_rrset->getRdataIterator();
    // Empty RRSIG shouldn't be passed either via a master file or
    // another data source iterator, but it could still happen if the
    // iterator has a bug.  We catch and reject such cases.
    if (it->isLast()) {
        isc_throw(isc::Unexpected,
                  "Empty RRset is passed in-memory loader, name: "
                  << sig_rrset->getName());
    }
    return (dynamic_cast<const generic::RRSIG&>(it->getCurrent()).
            typeCovered());
}

const Name&
ZoneDataLoader::getCurrentName() const {
    if (!node_rrsets_.empty()) {
        return (node_rrsets_.begin()->second->getName());
    }
    assert(!node_rrsigsets_.empty());
    return (node_rrsigsets_.begin()->second->getName());
}

} // namespace memory
} // namespace datasrc
} // namespace isc
