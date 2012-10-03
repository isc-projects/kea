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
#include <datasrc/memory/rdata_serialization.h>
#include <datasrc/memory/rdataset.h>
#include <datasrc/memory/domaintree.h>
#include <datasrc/memory/segment_object_holder.h>
#include <datasrc/memory/treenode_rrset.h>
#include <datasrc/memory/zone_finder.h>
#include <datasrc/memory/zone_data_updater.h>

#include <util/memory_segment_local.h>

#include <datasrc/data_source.h>
#include <datasrc/factory.h>
#include <datasrc/result.h>

#include <dns/name.h>
#include <dns/nsec3hash.h>
#include <dns/rdataclass.h>
#include <dns/rrclass.h>
#include <dns/rrsetlist.h>
#include <dns/masterload.h>

#include <boost/function.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/bind.hpp>
#include <boost/foreach.hpp>
#include <boost/noncopyable.hpp>

#include <algorithm>
#include <map>
#include <utility>
#include <cctype>
#include <cassert>

using namespace std;
using namespace isc::dns;
using namespace isc::dns::rdata;
using namespace isc::datasrc::memory;
using boost::scoped_ptr;

namespace isc {
namespace datasrc {
namespace memory {

using detail::SegmentObjectHolder;

namespace {
// Some type aliases
typedef DomainTree<std::string> FileNameTree;
typedef DomainTreeNode<std::string> FileNameNode;

// A functor type used for loading.
typedef boost::function<void(ConstRRsetPtr)> LoadCallback;

} // end of anonymous namespace

/// Implementation details for \c InMemoryClient hidden from the public
/// interface.
///
/// For now, \c InMemoryClient only contains a \c ZoneTable object, which
/// consists of (pointers to) \c InMemoryZoneFinder objects, we may add more
/// member variables later for new features.
class InMemoryClient::InMemoryClientImpl {
private:
    // The deleter for the filenames stored in the tree.
    struct FileNameDeleter {
        FileNameDeleter() {}
        void operator()(std::string* filename) const {
            delete filename;
        }
    };

public:
    InMemoryClientImpl(util::MemorySegment& mem_sgmt, RRClass rrclass) :
        mem_sgmt_(mem_sgmt),
        rrclass_(rrclass),
        zone_count_(0),
        zone_table_(ZoneTable::create(mem_sgmt_, rrclass)),
        file_name_tree_(FileNameTree::create(mem_sgmt_, false))
    {}
    ~InMemoryClientImpl() {
        FileNameDeleter deleter;
        FileNameTree::destroy(mem_sgmt_, file_name_tree_, deleter);

        ZoneTable::destroy(mem_sgmt_, zone_table_, rrclass_);
    }

    util::MemorySegment& mem_sgmt_;
    const RRClass rrclass_;
    unsigned int zone_count_;
    ZoneTable* zone_table_;
    FileNameTree* file_name_tree_;

    // Common process for zone load.
    // rrset_installer is a functor that takes another functor as an argument,
    // and expected to call the latter for each RRset of the zone.  How the
    // sequence of the RRsets is generated depends on the internal
    // details  of the loader: either from a textual master file or from
    // another data source.
    // filename is the file name of the master file or empty if the zone is
    // loaded from another data source.
    result::Result load(const Name& zone_name, const string& filename,
                        boost::function<void(LoadCallback)> rrset_installer);
};

// A helper internal class for load().  make it non-copyable to avoid
// accidental copy.
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
class InMemoryClient::Loader : boost::noncopyable {
    typedef std::map<RRType, ConstRRsetPtr> NodeRRsets;
    typedef NodeRRsets::value_type NodeRRsetsVal;
public:
    Loader(InMemoryClientImpl* client_impl, const Name& zone_name,
           ZoneData& zone_data) :
        client_impl_(client_impl), zone_name_(zone_name), zone_data_(zone_data),
        updater_(client_impl->mem_sgmt_, client_impl->rrclass_,
                 zone_name, zone_data)
    {}
    void addFromLoad(const ConstRRsetPtr& rrset) {
        // If we see a new name, flush the temporary holders, adding the
        // pairs of RRsets and RRSIGs of the previous name to the zone.
        if ((!node_rrsets_.empty() || !node_rrsigsets_.empty()) &&
            getCurrentName() != rrset->getName()) {
            flushNodeRRsets();
        }

        // Store this RRset until it can be added to the zone.  The current
        // implementation requires RRs of the same RRset should be added at
        // once, so we check the "duplicate" here.
        const bool is_rrsig = rrset->getType() == RRType::RRSIG();
        NodeRRsets& node_rrsets = is_rrsig ? node_rrsigsets_ : node_rrsets_;
        const RRType& rrtype = is_rrsig ?
            getCoveredType(rrset) : rrset->getType();
        if (!node_rrsets.insert(NodeRRsetsVal(rrtype, rrset)).second) {
            isc_throw(ZoneDataUpdater::AddError,
                      "Duplicate add of the same type of"
                      << (is_rrsig ? " RRSIG" : "") << " RRset: "
                      << rrset->getName() << "/" << rrtype);
        }
    }
    void flushNodeRRsets() {
        BOOST_FOREACH(NodeRRsetsVal val, node_rrsets_) {
            // Identify the corresponding RRSIG for the RRset, if any.
            // If found add both the RRset and its RRSIG at once.
            ConstRRsetPtr sig_rrset;
            NodeRRsets::iterator sig_it =
                node_rrsigsets_.find(val.first);
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
private:
    // A helper to identify the covered type of an RRSIG.
    static RRType getCoveredType(const ConstRRsetPtr& sig_rrset) {
        RdataIteratorPtr it = sig_rrset->getRdataIterator();
        // Empty RRSIG shouldn't be passed either via a master file or another
        // data source iterator, but it could still happen if the iterator
        // has a bug.  We catch and reject such cases.
        if (it->isLast()) {
            isc_throw(isc::Unexpected,
                      "Empty RRset is passed in-memory loader, name: "
                      << sig_rrset->getName());
        }
        return (dynamic_cast<const generic::RRSIG&>(it->getCurrent()).
                typeCovered());
    }
    const Name& getCurrentName() const {
        if (!node_rrsets_.empty()) {
            return (node_rrsets_.begin()->second->getName());
        }
        assert(!node_rrsigsets_.empty());
        return (node_rrsigsets_.begin()->second->getName());
    }

private:
    InMemoryClientImpl* client_impl_;
    const Name& zone_name_;
    ZoneData& zone_data_;
    NodeRRsets node_rrsets_;
    NodeRRsets node_rrsigsets_;
    ZoneDataUpdater updater_;
};

result::Result
InMemoryClient::InMemoryClientImpl::load(
    const Name& zone_name,
    const string& filename,
    boost::function<void(LoadCallback)> rrset_installer)
{
    SegmentObjectHolder<ZoneData, RRClass> holder(
        mem_sgmt_, ZoneData::create(mem_sgmt_, zone_name), rrclass_);

    Loader loader(this, zone_name, *holder.get());
    rrset_installer(boost::bind(&Loader::addFromLoad, &loader, _1));
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
        isc_throw(ZoneDataUpdater::EmptyZone,
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
                  const RRClass& zone_class, LoadCallback callback)
{
    masterLoad(filename, origin, zone_class, boost::bind(callback, _1));
}

// The installer called from Impl::load() for the iterator version of load().
void
generateRRsetFromIterator(ZoneIterator* iterator, LoadCallback callback) {
    ConstRRsetPtr rrset;
    while ((rrset = iterator->getNextRRset()) != NULL) {
        callback(rrset);
    }
}
}

InMemoryClient::InMemoryClient(util::MemorySegment& mem_sgmt,
                               RRClass rrclass) :
    impl_(new InMemoryClientImpl(mem_sgmt, rrclass))
{}

InMemoryClient::~InMemoryClient() {
    delete impl_;
}

RRClass
InMemoryClient::getClass() const {
    return (impl_->rrclass_);
}

unsigned int
InMemoryClient::getZoneCount() const {
    return (impl_->zone_count_);
}

isc::datasrc::DataSourceClient::FindResult
InMemoryClient::findZone(const isc::dns::Name& zone_name) const {
    LOG_DEBUG(logger, DBG_TRACE_DATA,
              DATASRC_MEMORY_MEM_FIND_ZONE).arg(zone_name);

    ZoneTable::FindResult result(impl_->zone_table_->findZone(zone_name));

    ZoneFinderPtr finder;
    if (result.code != result::NOTFOUND) {
        finder.reset(new InMemoryZoneFinder(*result.zone_data, getClass()));
    }

    return (DataSourceClient::FindResult(result.code, finder));
}

const ZoneData*
InMemoryClient::findZoneData(const isc::dns::Name& zone_name) {
    ZoneTable::FindResult result(impl_->zone_table_->findZone(zone_name));
    return (result.zone_data);
}

result::Result
InMemoryClient::load(const isc::dns::Name& zone_name,
                     const std::string& filename) {
    LOG_DEBUG(logger, DBG_TRACE_BASIC, DATASRC_MEMORY_MEM_LOAD).arg(zone_name).
        arg(filename);

    return (impl_->load(zone_name, filename,
                        boost::bind(masterLoadWrapper, filename.c_str(),
                                    zone_name, getClass(), _1)));
}

result::Result
InMemoryClient::load(const isc::dns::Name& zone_name,
                     ZoneIterator& iterator) {
    return (impl_->load(zone_name, string(),
                        boost::bind(generateRRsetFromIterator,
                                    &iterator, _1)));
}

const std::string
InMemoryClient::getFileName(const isc::dns::Name& zone_name) const {
    FileNameNode* node(NULL);
    FileNameTree::Result result = impl_->file_name_tree_->find(zone_name,
                                                               &node);
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
    const ZoneTable::FindResult result =
        impl_->zone_table_->findZone(zone_name);
    if (result.code != result::SUCCESS) {
        isc_throw(DataSourceError, "No such zone: " + zone_name.toText());
    }

    const ConstRRsetPtr sig_rrset =
        rrset ? rrset->getRRsig() : ConstRRsetPtr();

    ZoneDataUpdater updater(impl_->mem_sgmt_, impl_->rrclass_,
                            zone_name, *result.zone_data);
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
    ZoneTable::FindResult result(impl_->zone_table_->findZone(name));
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
