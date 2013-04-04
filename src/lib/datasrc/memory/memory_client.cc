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
#include <datasrc/memory/zone_data_loader.h>
#include <datasrc/memory/zone_table_segment.h>

#include <util/memory_segment_local.h>

#include <datasrc/exceptions.h>
#include <datasrc/factory.h>
#include <datasrc/result.h>

#include <dns/name.h>
#include <dns/rdataclass.h>
#include <dns/rrclass.h>

#include <algorithm>
#include <utility>
#include <cctype>
#include <cassert>

using namespace std;
using namespace isc::dns;
using namespace isc::dns::rdata;
using namespace isc::datasrc::memory;
using namespace isc::util;

namespace isc {
namespace datasrc {
namespace memory {

using detail::SegmentObjectHolder;
using boost::shared_ptr;

namespace { // unnamed namespace

// A helper internal class used by the memory client, used for deleting
// filenames stored in an internal tree.
class FileNameDeleter {
public:
    FileNameDeleter() {}

    void operator()(std::string* filename) const {
        delete filename;
    }
};

} // end of unnamed namespace

InMemoryClient::InMemoryClient(shared_ptr<ZoneTableSegment> ztable_segment,
                               RRClass rrclass) :
    ztable_segment_(ztable_segment),
    rrclass_(rrclass),
    file_name_tree_(FileNameTree::create(
        ztable_segment_->getMemorySegment(), false))
{}

InMemoryClient::~InMemoryClient() {
    MemorySegment& mem_sgmt = ztable_segment_->getMemorySegment();
    FileNameDeleter deleter;
    FileNameTree::destroy(mem_sgmt, file_name_tree_, deleter);
}

result::Result
InMemoryClient::loadInternal(const isc::dns::Name& zone_name,
                             const std::string& filename,
                             ZoneData* zone_data)
{
    MemorySegment& mem_sgmt = ztable_segment_->getMemorySegment();
    SegmentObjectHolder<ZoneData, RRClass> holder(
        mem_sgmt, zone_data, rrclass_);

    LOG_DEBUG(logger, DBG_TRACE_BASIC, DATASRC_MEMORY_MEM_ADD_ZONE).
        arg(zone_name).arg(rrclass_);

    // Set the filename in file_name_tree_ now, so that getFileName()
    // can use it (during zone reloading).
    FileNameNode* node(NULL);
    switch (file_name_tree_->insert(mem_sgmt, zone_name, &node)) {
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

    const std::string* tstr = node->setData(new std::string(filename));
    delete tstr;

    ZoneTable* zone_table = ztable_segment_->getHeader().getTable();
    const ZoneTable::AddResult result(zone_table->addZone(mem_sgmt, rrclass_,
                                                          zone_name,
                                                          holder.release()));
    // Destroy the old instance of the zone if there was any
    if (result.zone_data != NULL) {
        ZoneData::destroy(mem_sgmt, result.zone_data, rrclass_);
    }

    return (result.code);
}

RRClass
InMemoryClient::getClass() const {
    return (rrclass_);
}

unsigned int
InMemoryClient::getZoneCount() const {
    const ZoneTable* zone_table = ztable_segment_->getHeader().getTable();
    return (zone_table->getZoneCount());
}

isc::datasrc::DataSourceClient::FindResult
InMemoryClient::findZone(const isc::dns::Name& zone_name) const {
    LOG_DEBUG(logger, DBG_TRACE_DATA,
              DATASRC_MEMORY_MEM_FIND_ZONE).arg(zone_name);

    const ZoneTable* zone_table = ztable_segment_->getHeader().getTable();
    const ZoneTable::FindResult result(zone_table->findZone(zone_name));

    ZoneFinderPtr finder;
    if (result.code != result::NOTFOUND) {
        finder.reset(new InMemoryZoneFinder(*result.zone_data, getClass()));
    }

    return (DataSourceClient::FindResult(result.code, finder));
}

const ZoneData*
InMemoryClient::findZoneData(const isc::dns::Name& zone_name) {
    const ZoneTable* zone_table = ztable_segment_->getHeader().getTable();
    const ZoneTable::FindResult result(zone_table->findZone(zone_name));
    return (result.zone_data);
}

result::Result
InMemoryClient::load(const isc::dns::Name& zone_name,
                     const std::string& filename)
{
    LOG_DEBUG(logger, DBG_TRACE_BASIC, DATASRC_MEMORY_MEM_LOAD).arg(zone_name).
        arg(filename);

    MemorySegment& mem_sgmt = ztable_segment_->getMemorySegment();
    ZoneData* zone_data = loadZoneData(mem_sgmt, rrclass_, zone_name,
                                       filename);
    return (loadInternal(zone_name, filename, zone_data));
}

result::Result
InMemoryClient::load(const isc::dns::Name& zone_name, ZoneIterator& iterator) {
    MemorySegment& mem_sgmt = ztable_segment_->getMemorySegment();
    ZoneData* zone_data = loadZoneData(mem_sgmt, rrclass_, zone_name,
                                       iterator);
    return (loadInternal(zone_name, string(), zone_data));
}

const std::string
InMemoryClient::getFileName(const isc::dns::Name& zone_name) const {
    const FileNameNode* node(NULL);
    const FileNameTree::Result result = file_name_tree_->find(zone_name,
                                                              &node);
    if (result == FileNameTree::EXACTMATCH) {
        return (*node->getData());
    } else {
        return (std::string());
    }
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
    bool examined_rrsigs_;
    // In case there's nsec3 namespace in the zone, it is represented the same
    // way as the usual namespace. So we reuse the iterator implementation for
    // it.
    ZoneIteratorPtr nsec3_namespace_;
public:
    MemoryIterator(const RRClass& rrclass,
                   const ZoneTree& tree, const NSEC3Data* nsec3_data,
                   const Name& origin, bool separate_rrs) :
        rrclass_(rrclass),
        tree_(tree),
        separate_rrs_(separate_rrs),
        ready_(true),
        examined_rrsigs_(false)
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

        // If we have the NSEC3 namespace, get an iterator for it so we can
        // delegate to it later.
        if (nsec3_data != NULL) {
            nsec3_namespace_ =
                ZoneIteratorPtr(new MemoryIterator(rrclass,
                                                   nsec3_data->getNSEC3Tree(),
                                                   NULL, origin,
                                                   separate_rrs));
        }
    }

    virtual ConstRRsetPtr getNextRRset() {
        if (!ready_) {
            // We are done iterating. But in case there's the nsec3 one,
            // iterate through that one.
            if (nsec3_namespace_ != ZoneIteratorPtr()) {
                return (nsec3_namespace_->getNextRRset());
            }
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
                    examined_rrsigs_ = false;
                }
            }
        }
        if (node_ == NULL) {
            // That's all, folks
            ready_ = false;
            if (nsec3_namespace_ != ZoneIteratorPtr()) {
                // In case we have the NSEC3 namespace, get one from there.
                return (nsec3_namespace_->getNextRRset());
            } else {
                return (ConstRRsetPtr());
            }
        }

        if (separate_rrs_) {
            // For separate rrs, reconstruct a new RRset with just the
            // 'current' rdata
            RRsetPtr result(new RRset(rrset_->getName(),
                                      rrset_->getClass(),
                                      // If we are looking into the signature,
                                      // we need to adjust the type too.
                                      examined_rrsigs_ ? RRType::RRSIG() :
                                          rrset_->getType(),
                                      rrset_->getTTL()));
            result->addRdata(rdata_iterator_->getCurrent());
            rdata_iterator_->next();
            if (!examined_rrsigs_ && rdata_iterator_->isLast()) {
                // We got to the last RR of the RRset, but we need to look at
                // the signatures too, if there are any.
                examined_rrsigs_ = true;
                const ConstRRsetPtr rrsig = rrset_->getRRsig();
                if (rrsig != ConstRRsetPtr()) {
                    rrset_ = rrsig;
                    rdata_iterator_ = rrsig->getRdataIterator();
                } // else - no RRSIG. rdata_iterator_ stays at last, next
                  // condition applies
            }
            if (rdata_iterator_->isLast()) {
                // all used up, next.
                set_node_ = set_node_->getNext();
                // New RRset, so get a new rdata iterator, but only if this
                // was not the final RRset in the chain
                if (set_node_ != NULL) {
                    rrset_.reset(new TreeNodeRRset(rrclass_,
                                                   node_, set_node_, true));
                    rdata_iterator_ = rrset_->getRdataIterator();
                    examined_rrsigs_ = false;
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
    const ZoneTable* zone_table = ztable_segment_->getHeader().getTable();
    const ZoneTable::FindResult result(zone_table->findZone(name));
    if (result.code != result::SUCCESS) {
        isc_throw(DataSourceError, "No such zone: " + name.toText());
    }

    return (ZoneIteratorPtr(new MemoryIterator(
                                getClass(),
                                result.zone_data->getZoneTree(),
                                result.zone_data->getNSEC3Data(), name,
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
