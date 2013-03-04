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

#include <datasrc/master_loader_callbacks.h>
#include <datasrc/memory/zone_data_loader.h>
#include <datasrc/memory/zone_data_updater.h>
#include <datasrc/memory/logger.h>
#include <datasrc/memory/segment_object_holder.h>
#include <datasrc/memory/util_internal.h>
#include <datasrc/memory/rrset_collection.h>

#include <dns/master_loader.h>
#include <dns/rrcollator.h>
#include <dns/rdataclass.h>
#include <dns/rrset.h>
#include <dns/zone_checker.h>

#include <boost/foreach.hpp>
#include <boost/bind.hpp>
#include <boost/noncopyable.hpp>

#include <map>

using namespace isc::dns;
using namespace isc::dns::rdata;

namespace isc {
namespace datasrc {
namespace memory {

using detail::SegmentObjectHolder;
using detail::getCoveredType;

namespace { // unnamed namespace

// A functor type used for loading.
typedef boost::function<void(isc::dns::ConstRRsetPtr)> LoadCallback;

// A helper internal class for \c loadZoneData().  make it non-copyable
// to avoid accidental copy.
//
// The current internal implementation expects that both a normal
// (non RRSIG) RRset and (when signed) its RRSIG are added at once.
// Also in the current implementation, the input sequence of RRsets
// are grouped with their owner name (so once a new owner name is encountered,
// no subsequent RRset has the previous owner name), but the ordering
// in the same group is not fixed.  So we hold all RRsets of the same
// owner name in node_rrsets_ and node_rrsigsets_, and add the matching
// pairs of RRsets to the zone when we see a new owner name.
//
// The caller is responsible for adding the RRsets of the last group
// in the input sequence by explicitly calling flushNodeRRsets() at the
// end.  It's cleaner and more robust if we let the destructor of this class
// do it, but since we cannot guarantee the adding operation is exception free,
// we don't choose that option to maintain the common expectation for
// destructors.
class ZoneDataLoader : boost::noncopyable {
public:
    ZoneDataLoader(util::MemorySegment& mem_sgmt,
                   const isc::dns::RRClass rrclass,
                   const isc::dns::Name& zone_name, ZoneData& zone_data) :
        updater_(mem_sgmt, rrclass, zone_name, zone_data)
    {}

    void addFromLoad(const isc::dns::ConstRRsetPtr& rrset);
    void flushNodeRRsets();

private:
    typedef std::vector<isc::dns::ConstRRsetPtr> NodeRRsets;

    // A helper to identify the covered type of an RRSIG.
    const isc::dns::Name& getCurrentName() const;

private:
    NodeRRsets node_rrsets_;
    NodeRRsets node_rrsigsets_;
    ZoneDataUpdater updater_;
};

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

    // Store this RRset until it can be added to the zone.
    node_rrsets.insert(node_rrsets.begin(), rrset);

    if (rrset->getRRsig()) {
        addFromLoad(rrset->getRRsig());
    }
}

void
ZoneDataLoader::flushNodeRRsets() {
    BOOST_FOREACH(ConstRRsetPtr rrset, node_rrsets_) {
        updater_.add(rrset, ConstRRsetPtr());
    }

    BOOST_FOREACH(ConstRRsetPtr rrset, node_rrsigsets_) {
        updater_.add(ConstRRsetPtr(), rrset);
    }

    node_rrsets_.clear();
    node_rrsigsets_.clear();
}

const Name&
ZoneDataLoader::getCurrentName() const {
    if (!node_rrsets_.empty()) {
        return (node_rrsets_.front()->getName());
    }
    assert(!node_rrsigsets_.empty());
    return (node_rrsigsets_.front()->getName());
}

void
logWarning(const dns::Name* zone_name, const dns::RRClass* rrclass,
           const std::string& reason)
{
    LOG_WARN(logger, DATASRC_MEMORY_CHECK_WARNING).arg(*zone_name).
        arg(*rrclass).arg(reason);
}

void
logError(const dns::Name* zone_name, const dns::RRClass* rrclass,
         const std::string& reason)
{
    LOG_ERROR(logger, DATASRC_MEMORY_CHECK_ERROR).arg(*zone_name).arg(*rrclass).
        arg(reason);
}

ZoneData*
loadZoneDataInternal(util::MemorySegment& mem_sgmt,
                     const isc::dns::RRClass& rrclass,
                     const Name& zone_name,
                     boost::function<void(LoadCallback)> rrset_installer)
{
    SegmentObjectHolder<ZoneData, RRClass> holder(
        mem_sgmt, ZoneData::create(mem_sgmt, zone_name), rrclass);

    ZoneDataLoader loader(mem_sgmt, rrclass, zone_name, *holder.get());
    rrset_installer(boost::bind(&ZoneDataLoader::addFromLoad, &loader, _1));
    // Add any last RRsets that were left
    loader.flushNodeRRsets();

    const ZoneNode* origin_node = holder.get()->getOriginNode();
    const RdataSet* rdataset = origin_node->getData();
    // If the zone is NSEC3-signed, check if it has NSEC3PARAM
    if (holder.get()->isNSEC3Signed()) {
        if (RdataSet::find(rdataset, RRType::NSEC3PARAM()) == NULL) {
            LOG_WARN(logger, DATASRC_MEMORY_MEM_NO_NSEC3PARAM).
                arg(zone_name).arg(rrclass);
        }
    }

    RRsetCollection collection(*(holder.get()), rrclass);
    const dns::ZoneCheckerCallbacks
        callbacks(boost::bind(&logError, &zone_name, &rrclass, _1),
                  boost::bind(&logWarning, &zone_name, &rrclass, _1));
    if (!dns::checkZone(zone_name, rrclass, collection, callbacks)) {
        isc_throw(ZoneValidationError,
                  "Errors found when validating zone: "
                  << zone_name << "/" << rrclass);
    }

    return (holder.release());
}

// A wrapper for dns::MasterLoader used by loadZoneData() below.  Essentially
// it converts the two callback types.  Note the mostly redundant wrapper of
// boost::bind.  It converts function<void(ConstRRsetPtr)> to
// function<void(RRsetPtr)> (MasterLoader expects the latter).  SunStudio
// doesn't seem to do this conversion if we just pass 'callback'.
void
masterLoaderWrapper(const char* const filename, const Name& origin,
                    const RRClass& zone_class, LoadCallback callback)
{
    bool load_ok = false;       // (we don't use it)
    dns::RRCollator collator(boost::bind(callback, _1));

    try {
        dns::MasterLoader(filename, origin, zone_class,
                          createMasterLoaderCallbacks(origin, zone_class,
                                                      &load_ok),
                          collator.getCallback()).load();
        collator.flush();
    } catch (const dns::MasterLoaderError& e) {
        isc_throw(ZoneLoaderException, e.what());
    }
}

// The installer called from the iterator version of loadZoneData().
void
generateRRsetFromIterator(ZoneIterator* iterator, LoadCallback callback) {
    ConstRRsetPtr rrset;
    while ((rrset = iterator->getNextRRset()) != NULL) {
        callback(rrset);
    }
}

} // end of unnamed namespace

ZoneData*
loadZoneData(util::MemorySegment& mem_sgmt,
             const isc::dns::RRClass& rrclass,
             const isc::dns::Name& zone_name,
             const std::string& zone_file)
{
     return (loadZoneDataInternal(mem_sgmt, rrclass, zone_name,
                                 boost::bind(masterLoaderWrapper,
                                             zone_file.c_str(),
                                             zone_name, rrclass,
                                             _1)));
}

ZoneData*
loadZoneData(util::MemorySegment& mem_sgmt,
             const isc::dns::RRClass& rrclass,
             const isc::dns::Name& zone_name,
             ZoneIterator& iterator)
{
    return (loadZoneDataInternal(mem_sgmt, rrclass, zone_name,
                                 boost::bind(generateRRsetFromIterator,
                                             &iterator, _1)));
}

} // namespace memory
} // namespace datasrc
} // namespace isc
