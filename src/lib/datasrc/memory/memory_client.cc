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

#include <datasrc/memory/memory_client.h>
#include <datasrc/memory/logger.h>
#include <datasrc/memory/zone_data.h>
#include <datasrc/memory/rdataset.h>
#include <datasrc/memory/segment_object_holder.h>
#include <datasrc/memory/treenode_rrset.h>
#include <datasrc/memory/zone_finder.h>
#include <datasrc/memory/zone_data_updater.h>

#include <util/memory_segment_local.h>

#include <datasrc/data_source.h>
#include <datasrc/factory.h>
#include <datasrc/result.h>

#include <dns/name.h>
#include <dns/rdataclass.h>
#include <dns/rrclass.h>
#include <dns/rrsetlist.h>
#include <dns/masterload.h>

#include <boost/bind.hpp>

#include <algorithm>
#include <utility>
#include <cctype>
#include <cassert>

using namespace std;
using namespace isc::dns;
using namespace isc::dns::rdata;
using namespace isc::datasrc::memory;

namespace isc {
namespace datasrc {
namespace memory {

using detail::SegmentObjectHolder;

class InMemoryClient::FileNameDeleter {
public:
    FileNameDeleter() {}

    void operator()(std::string* filename) const {
        delete filename;
    }
};

InMemoryClient::InMemoryClient(util::MemorySegment& mem_sgmt,
                               RRClass rrclass) :
    mem_sgmt_(mem_sgmt),
    rrclass_(rrclass),
    zone_count_(0)
{
    SegmentObjectHolder<ZoneTable, RRClass> holder(
        mem_sgmt_, ZoneTable::create(mem_sgmt_, rrclass), rrclass_);

    file_name_tree_ = FileNameTree::create(mem_sgmt_, false);

    zone_table_ = holder.release();
}

InMemoryClient::~InMemoryClient() {
    FileNameDeleter deleter;
    FileNameTree::destroy(mem_sgmt_, file_name_tree_, deleter);

    ZoneTable::destroy(mem_sgmt_, zone_table_, rrclass_);
}

result::Result
InMemoryClient::load(const Name& zone_name,
                     const string& filename,
                     boost::function<void(internal::LoadCallback)>
                         rrset_installer)
{
    SegmentObjectHolder<ZoneData, RRClass> holder(
        mem_sgmt_, ZoneData::create(mem_sgmt_, zone_name), rrclass_);

    ZoneDataUpdater::Loader loader(mem_sgmt_, rrclass_,
                                   zone_name, *holder.get());
    rrset_installer(boost::bind(&ZoneDataUpdater::Loader::addFromLoad,
                                &loader, _1));
    // Add any last RRsets that were left
    loader.flushNodeRRsets();

    const ZoneNode* origin_node = holder.get()->getOriginNode();
    const RdataSet* set = origin_node->getData();
    // If the zone is NSEC3-signed, check if it has NSEC3PARAM
    if (holder.get()->isNSEC3Signed()) {
        if (RdataSet::find(set, RRType::NSEC3PARAM()) == NULL) {
            LOG_WARN(logger, DATASRC_MEMORY_MEM_NO_NSEC3PARAM).
                arg(zone_name).arg(rrclass_);
        }
    }

    // When an empty zone file is loaded, the origin doesn't even have
    // an SOA RR. This condition should be avoided, and hence load()
    // should throw when an empty zone is loaded.
    if (RdataSet::find(set, RRType::SOA()) == NULL) {
        isc_throw(EmptyZone,
                  "Won't create an empty zone for: " << zone_name);
    }

    LOG_DEBUG(logger, DBG_TRACE_BASIC, DATASRC_MEMORY_MEM_ADD_ZONE).
        arg(zone_name).arg(rrclass_);

    // Set the filename in file_name_tree_ now, so that getFileName()
    // can use it (during zone reloading).
    FileNameNode* node(NULL);
    switch (file_name_tree_->insert(mem_sgmt_, zone_name, &node)) {
    case FileNameTree::SUCCESS:
    case FileNameTree::ALREADYEXISTS:
        // These are OK
        break;
    default:
        // Can Not Happen
        assert(false);
    }
    // node must point to a valid node now
    assert(node != NULL);

    std::string* tstr = node->setData(new std::string(filename));
    delete tstr;

    ZoneTable::AddResult result(zone_table_->addZone(mem_sgmt_, rrclass_,
                                                     zone_name));
    if (result.code == result::SUCCESS) {
        // Only increment the zone count if the zone doesn't already
        // exist.
        ++zone_count_;
    }

    ZoneTable::FindResult fr(zone_table_->setZoneData(zone_name,
                                                      holder.release()));
    assert(fr.code == result::SUCCESS);
    if (fr.zone_data != NULL) {
        ZoneData::destroy(mem_sgmt_, fr.zone_data, rrclass_);
    }

    return (result.code);
}

namespace {
// A wrapper for dns::masterLoad used by load() below.  Essentially it
// converts the two callback types.  Note the mostly redundant wrapper of
// boost::bind.  It converts function<void(ConstRRsetPtr)> to
// function<void(RRsetPtr)> (masterLoad() expects the latter).  SunStudio
// doesn't seem to do this conversion if we just pass 'callback'.
void
masterLoadWrapper(const char* const filename, const Name& origin,
                  const RRClass& zone_class,
                  internal::LoadCallback callback)
{
    masterLoad(filename, origin, zone_class, boost::bind(callback, _1));
}

// The installer called from load() for the iterator version of load().
void
generateRRsetFromIterator(ZoneIterator* iterator,
                          internal::LoadCallback callback)
{
    ConstRRsetPtr rrset;
    while ((rrset = iterator->getNextRRset()) != NULL) {
        callback(rrset);
    }
}
}

RRClass
InMemoryClient::getClass() const {
    return (rrclass_);
}

unsigned int
InMemoryClient::getZoneCount() const {
    return (zone_count_);
}

isc::datasrc::DataSourceClient::FindResult
InMemoryClient::findZone(const isc::dns::Name& zone_name) const {
    LOG_DEBUG(logger, DBG_TRACE_DATA,
              DATASRC_MEMORY_MEM_FIND_ZONE).arg(zone_name);

    ZoneTable::FindResult result(zone_table_->findZone(zone_name));

    ZoneFinderPtr finder;
    if (result.code != result::NOTFOUND) {
        finder.reset(new InMemoryZoneFinder(*result.zone_data, getClass()));
    }

    return (DataSourceClient::FindResult(result.code, finder));
}

const ZoneData*
InMemoryClient::findZoneData(const isc::dns::Name& zone_name) {
    ZoneTable::FindResult result(zone_table_->findZone(zone_name));
    return (result.zone_data);
}

result::Result
InMemoryClient::load(const isc::dns::Name& zone_name,
                     const std::string& filename) {
    LOG_DEBUG(logger, DBG_TRACE_BASIC, DATASRC_MEMORY_MEM_LOAD).arg(zone_name).
        arg(filename);

    return (load(zone_name, filename,
                 boost::bind(masterLoadWrapper, filename.c_str(),
                             zone_name, getClass(), _1)));
}

result::Result
InMemoryClient::load(const isc::dns::Name& zone_name,
                     ZoneIterator& iterator) {
    return (load(zone_name, string(),
                 boost::bind(generateRRsetFromIterator,
                             &iterator, _1)));
}

const std::string
InMemoryClient::getFileName(const isc::dns::Name& zone_name) const {
    FileNameNode* node(NULL);
    FileNameTree::Result result = file_name_tree_->find(zone_name, &node);
    if (result == FileNameTree::EXACTMATCH) {
        return (*node->getData());
    } else {
        return (std::string());
    }
}

result::Result
InMemoryClient::add(const isc::dns::Name& zone_name,
                    const ConstRRsetPtr& rrset)
{
    const ZoneTable::FindResult result = zone_table_->findZone(zone_name);
    if (result.code != result::SUCCESS) {
        isc_throw(DataSourceError, "No such zone: " + zone_name.toText());
    }

    const ConstRRsetPtr sig_rrset =
        rrset ? rrset->getRRsig() : ConstRRsetPtr();

    ZoneDataUpdater updater(mem_sgmt_, rrclass_, zone_name, *result.zone_data);
    updater.add(rrset, sig_rrset);

    // add() doesn't allow duplicate add, so we always return SUCCESS.
    return (result::SUCCESS);
}

namespace {

class MemoryIterator : public ZoneIterator {
private:
    ZoneChain chain_;
    const RdataSet* set_node_;
    const RRClass rrclass_;
    const ZoneTree& tree_;
    const ZoneNode* node_;
    // Only used when separate_rrs_ is true
    ConstRRsetPtr rrset_;
    RdataIteratorPtr rdata_iterator_;
    bool separate_rrs_;
    bool ready_;
public:
    MemoryIterator(const RRClass rrclass,
                   const ZoneTree& tree, const Name& origin,
                   bool separate_rrs) :
        rrclass_(rrclass),
        tree_(tree),
        separate_rrs_(separate_rrs),
        ready_(true)
    {
        // Find the first node (origin) and preserve the node chain for future
        // searches
        ZoneTree::Result result(tree_.find(origin, &node_, chain_));
        // It can't happen that the origin is not in there
        if (result != ZoneTree::EXACTMATCH) {
            isc_throw(Unexpected,
                      "In-memory zone corrupted, missing origin node");
        }
        // Initialize the iterator if there's somewhere to point to
        if (node_ != NULL && node_->getData() != NULL) {
            set_node_ = node_->getData();
            if (separate_rrs_ && set_node_ != NULL) {
                rrset_.reset(new TreeNodeRRset(rrclass_,
                                               node_, set_node_, true));
                rdata_iterator_ = rrset_->getRdataIterator();
            }
        }
    }

    virtual ConstRRsetPtr getNextRRset() {
        if (!ready_) {
            isc_throw(Unexpected, "Iterating past the zone end");
        }
        /*
         * This cycle finds the first nonempty node with yet unused
         * RdataSset.  If it is NULL, we run out of nodes. If it is
         * empty, it doesn't contain any RdataSets. If we are at the
         * end, just get to next one.
         */
        while (node_ != NULL &&
               (node_->getData() == NULL || set_node_ == NULL)) {
            node_ = tree_.nextNode(chain_);
            // If there's a node, initialize the iterator and check next time
            // if the map is empty or not
            if (node_ != NULL && node_->getData() != NULL) {
                set_node_ = node_->getData();
                // New RRset, so get a new rdata iterator
                if (separate_rrs_ && set_node_ != NULL) {
                    rrset_.reset(new TreeNodeRRset(rrclass_,
                                                   node_, set_node_, true));
                    rdata_iterator_ = rrset_->getRdataIterator();
                }
            }
        }
        if (node_ == NULL) {
            // That's all, folks
            ready_ = false;
            return (ConstRRsetPtr());
        }

        if (separate_rrs_) {
            // For separate rrs, reconstruct a new RRset with just the
            // 'current' rdata
            RRsetPtr result(new RRset(rrset_->getName(),
                                      rrset_->getClass(),
                                      rrset_->getType(),
                                      rrset_->getTTL()));
            result->addRdata(rdata_iterator_->getCurrent());
            rdata_iterator_->next();
            if (rdata_iterator_->isLast()) {
                // all used up, next.
                set_node_ = set_node_->getNext();
                // New RRset, so get a new rdata iterator, but only if this
                // was not the final RRset in the chain
                if (set_node_ != NULL) {
                    rrset_.reset(new TreeNodeRRset(rrclass_,
                                                   node_, set_node_, true));
                    rdata_iterator_ = rrset_->getRdataIterator();
                }
            }
            return (result);
        } else {
            ConstRRsetPtr result(new TreeNodeRRset(rrclass_,
                                                   node_, set_node_, true));

            // This one is used, move it to the next time for next call
            set_node_ = set_node_->getNext();

            return (result);
        }
    }

    virtual ConstRRsetPtr getSOA() const {
        isc_throw(NotImplemented, "Not implemented");
    }
};

} // End of anonymous namespace

ZoneIteratorPtr
InMemoryClient::getIterator(const Name& name, bool separate_rrs) const {
    ZoneTable::FindResult result(zone_table_->findZone(name));
    if (result.code != result::SUCCESS) {
        isc_throw(DataSourceError, "No such zone: " + name.toText());
    }

    return (ZoneIteratorPtr(new MemoryIterator(
                                getClass(),
                                result.zone_data->getZoneTree(), name,
                                separate_rrs)));
}

ZoneUpdaterPtr
InMemoryClient::getUpdater(const isc::dns::Name&, bool, bool) const {
    isc_throw(isc::NotImplemented, "Update attempt on in memory data source");
}

pair<ZoneJournalReader::Result, ZoneJournalReaderPtr>
InMemoryClient::getJournalReader(const isc::dns::Name&, uint32_t,
                                 uint32_t) const
{
    isc_throw(isc::NotImplemented, "Journaling isn't supported for "
              "in memory data source");
}

} // end of namespace memory
} // end of namespace datasrc
} // end of namespace isc
