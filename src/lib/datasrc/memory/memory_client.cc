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
#include <datasrc/memory/zone_data.h>
#include <datasrc/memory/rdata_serialization.h>
#include <datasrc/memory/rdataset.h>
#include <datasrc/memory/domaintree.h>
#include <datasrc/memory/segment_object_holder.h>

#include <util/memory_segment_local.h>

#include <datasrc/logger.h>
#include <datasrc/iterator.h>
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
    InMemoryClientImpl(RRClass rrclass) :
        rrclass_(rrclass),
        zone_count(0),
        zone_table_(ZoneTable::create(local_mem_sgmt, rrclass)),
        file_name_tree_(FileNameTree::create(local_mem_sgmt, false))
    {}
    ~InMemoryClientImpl() {
        FileNameDeleter deleter;
        FileNameTree::destroy(local_mem_sgmt, file_name_tree_, deleter);

        ZoneTable::destroy(local_mem_sgmt, zone_table_, rrclass_);

        // see above for the assert().
        assert(local_mem_sgmt.allMemoryDeallocated());
    }

    // Memory segment to allocate/deallocate memory for the zone table.
    // (This will eventually have to be abstract; for now we hardcode the
    // specific derived segment class).
    util::MemorySegmentLocal local_mem_sgmt;
    RRClass rrclass_;
    unsigned int zone_count;
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

    // Add the necessary magic for any wildcard contained in 'name'
    // (including itself) to be found in the zone.
    //
    // In order for wildcard matching to work correctly in the zone finder,
    // we must ensure that a node for the wildcarding level exists in the
    // backend RBTree.
    // E.g. if the wildcard name is "*.sub.example." then we must ensure
    // that "sub.example." exists and is marked as a wildcard level.
    // Note: the "wildcarding level" is for the parent name of the wildcard
    // name (such as "sub.example.").
    //
    // We also perform the same trick for empty wild card names possibly
    // contained in 'name' (e.g., '*.foo.example' in 'bar.*.foo.example').
    void addWildcards(const Name& zone_name, ZoneData& zone_data,
                      const Name& name)
    {
        Name wname(name);
        const unsigned int labels(wname.getLabelCount());
        const unsigned int origin_labels(zone_name.getLabelCount());
        for (unsigned int l = labels;
             l > origin_labels;
             --l, wname = wname.split(1)) {
            if (wname.isWildcard()) {
                LOG_DEBUG(logger, DBG_TRACE_DATA, DATASRC_MEM_ADD_WILDCARD).
                    arg(name);

                // Ensure a separate level exists for the "wildcarding" name,
                // and mark the node as "wild".
                ZoneNode *node;
                zone_data.insertName(local_mem_sgmt, wname.split(1), &node);
                node->setFlag(ZoneData::WILDCARD_NODE);

                // Ensure a separate level exists for the wildcard name.
                // Note: for 'name' itself we do this later anyway, but the
                // overhead should be marginal because wildcard names should
                // be rare.
                zone_data.insertName(local_mem_sgmt, wname, &node);
            }
        }
    }

    // A helper predicate used in contextCheck() to check if a given domain
    // name has a RRset of type different than NSEC.
    static bool isNotNSEC(const DomainPair& element) {
        return (element.second->getType() != RRType::NSEC());
    }

    /*
     * Does some checks in context of the data that are already in the zone.
     * Currently checks for forbidden combinations of RRsets in the same
     * domain (CNAME+anything, DNAME+NS).
     *
     * If such condition is found, it throws AddError.
     */
    void contextCheck(const AbstractRRset& rrset, const Domain& domain) const {
        // Ensure CNAME and other type of RR don't coexist for the same
        // owner name except with NSEC, which is the only RR that can coexist
        // with CNAME (and also RRSIG, which is handled separately)
        if (rrset.getType() == RRType::CNAME()) {
            if (find_if(domain.begin(), domain.end(), isNotNSEC)
                != domain.end()) {
                LOG_ERROR(logger, DATASRC_MEM_CNAME_TO_NONEMPTY).
                    arg(rrset.getName());
                isc_throw(AddError, "CNAME can't be added with other data for "
                          << rrset.getName());
            }
        } else if (rrset.getType() != RRType::NSEC() &&
                   domain.find(RRType::CNAME()) != domain.end()) {
            LOG_ERROR(logger, DATASRC_MEM_CNAME_COEXIST).arg(rrset.getName());
            isc_throw(AddError, "CNAME and " << rrset.getType() <<
                      " can't coexist for " << rrset.getName());
        }

        /*
         * Similar with DNAME, but it must not coexist only with NS and only in
         * non-apex domains.
         * RFC 2672 section 3 mentions that it is implied from it and RFC 2181
         */
        if (rrset.getName() != origin_ &&
            // Adding DNAME, NS already there
            ((rrset.getType() == RRType::DNAME() &&
            domain.find(RRType::NS()) != domain.end()) ||
            // Adding NS, DNAME already there
            (rrset.getType() == RRType::NS() &&
            domain.find(RRType::DNAME()) != domain.end())))
        {
            LOG_ERROR(logger, DATASRC_MEM_DNAME_NS).arg(rrset.getName());
            isc_throw(AddError, "DNAME can't coexist with NS in non-apex "
                "domain " << rrset.getName());
        }
    }

    // Validate rrset before adding it to the zone.  If something is wrong
    // it throws an exception.  It doesn't modify the zone, and provides
    // the strong exception guarantee.
    void addValidation(const Name& zone_name, const ConstRRsetPtr rrset) {
        if (!rrset) {
            isc_throw(NullRRset, "The rrset provided is NULL");
        }
        if (rrset->getRdataCount() == 0) {
            isc_throw(AddError, "The rrset provided is empty: " <<
                      rrset->getName() << "/" << rrset->getType());
        }
        // Check for singleton RRs. It should probably handled at a different
        // layer in future.
        if ((rrset->getType() == RRType::CNAME() ||
            rrset->getType() == RRType::DNAME()) &&
            rrset->getRdataCount() > 1)
        {
            // XXX: this is not only for CNAME or DNAME. We should generalize
            // this code for all other "singleton RR types" (such as SOA) in a
            // separate task.
            LOG_ERROR(logger, DATASRC_MEM_SINGLETON).arg(rrset->getName()).
                arg(rrset->getType());
            isc_throw(AddError, "multiple RRs of singleton type for "
                      << rrset->getName());
        }
        // NSEC3/NSEC3PARAM is not a "singleton" per protocol, but this
        // implementation requests it be so at the moment.
        if ((rrset->getType() == RRType::NSEC3() ||
             rrset->getType() == RRType::NSEC3PARAM()) &&
            rrset->getRdataCount() > 1) {
            isc_throw(AddError, "Multiple NSEC3/NSEC3PARAM RDATA is given for "
                      << rrset->getName() << " which isn't supported");
        }

        NameComparisonResult compare(zone_name.compare(rrset->getName()));
        if (compare.getRelation() != NameComparisonResult::SUPERDOMAIN &&
            compare.getRelation() != NameComparisonResult::EQUAL)
        {
            LOG_ERROR(logger, DATASRC_MEM_OUT_OF_ZONE).arg(rrset->getName()).
                arg(zone_name);
            isc_throw(OutOfZone, "The name " << rrset->getName() <<
                " is not contained in zone " << zone_name);
        }

        // Some RR types do not really work well with a wildcard.
        // Even though the protocol specifically doesn't completely ban such
        // usage, we refuse to load a zone containing such RR in order to
        // keep the lookup logic simpler and more predictable.
        // See RFC4592 and (for DNAME) draft-ietf-dnsext-rfc2672bis-dname
        // for more technical background.  Note also that BIND 9 refuses
        // NS at a wildcard, so in that sense we simply provide compatible
        // behavior.
        if (rrset->getName().isWildcard()) {
            if (rrset->getType() == RRType::NS()) {
                LOG_ERROR(logger, DATASRC_MEM_WILDCARD_NS).
                    arg(rrset->getName());
                isc_throw(AddError, "Invalid NS owner name (wildcard): " <<
                          rrset->getName());
            }
            if (rrset->getType() == RRType::DNAME()) {
                LOG_ERROR(logger, DATASRC_MEM_WILDCARD_DNAME).
                    arg(rrset->getName());
                isc_throw(AddError, "Invalid DNAME owner name (wildcard): " <<
                          rrset->getName());
            }
        }

        // Owner names of NSEC3 have special format as defined in RFC5155,
        // and cannot be a wildcard name or must be one label longer than
        // the zone origin.  While the RFC doesn't prohibit other forms of
        // names, no sane zone would have such names for NSEC3.
        // BIND 9 also refuses NSEC3 at wildcard.
        if (rrset->getType() == RRType::NSEC3() &&
            (rrset->getName().isWildcard() ||
             rrset->getName().getLabelCount() !=
             zone_name.getLabelCount() + 1)) {
            LOG_ERROR(logger, DATASRC_BAD_NSEC3_NAME).
                arg(rrset->getName());
            isc_throw(AddError, "Invalid NSEC3 owner name: " <<
                      rrset->getName());
        }
    }

    result::Result addRRsig(const ConstRRsetPtr sig_rrset, ZoneData& zone_data)
    {
        // Check consistency of the type covered.
        // We know the RRset isn't empty, so the following check is safe.
        RdataIteratorPtr rit = sig_rrset->getRdataIterator();
        const RRType covered = dynamic_cast<const generic::RRSIG&>(
            rit->getCurrent()).typeCovered();
        for (rit->next(); !rit->isLast(); rit->next()) {
            if (dynamic_cast<const generic::RRSIG&>(
                    rit->getCurrent()).typeCovered() != covered) {
                isc_throw(AddError, "RRSIG contains mixed covered types: "
                          << sig_rrset->toText());
            }
        }

        // Find the RRset to be covered; if not found, treat it as an error
        // for now.
        ConstRRsetPtr covered_rrset;
        if (covered != RRType::NSEC3()) {
            DomainNode* node = NULL;
            if (zone_data.domains_.find(sig_rrset->getName(), &node) !=
                DomainTree::EXACTMATCH || node == NULL || !node->getData()) {
                isc_throw(AddError,
                          "RRSIG is being added, but no RR to be covered: "
                          << sig_rrset->getName());
            }
            const Domain::const_iterator it = node->getData()->find(covered);
            if (it != node->getData()->end()) {
                covered_rrset = it->second;
            }
        } else {
            // In case of NSEC3 if something is found it must be NSEC3 RRset
            // under the assumption of our current implementation.
            if (zone_data.nsec3_data_) {
                // Convert the first label to upper-cased text.  Note that
                // for a valid NSEC3 RR the label should only consist of
                // positive 8-bit char values, so using toupper(int) should be
                // safe (if it's a bogus label for NSEC3 the zone won't work
                // anyway).  Also note the '::' below: g++'s STL implementation
                // seems to require it to toupper to make this compile.
                string fst_label =
                    sig_rrset->getName().split(0, 1).toText(true);
                transform(fst_label.begin(), fst_label.end(),
                          fst_label.begin(), ::toupper);

                NSEC3Map::const_iterator found =
                    zone_data.nsec3_data_->map_.find(fst_label);
                if (found != zone_data.nsec3_data_->map_.end()) {
                    covered_rrset = found->second;
                    assert(covered_rrset->getType() == covered);
                }
            }
        }
        if (!covered_rrset) {
            isc_throw(AddError, "RRSIG is being added, but no RR of "
                      "covered type found: " << sig_rrset->toText());
        }

        // The current implementation doesn't allow an existing RRSIG to be
        // overridden (or updated with additional ones).
        if (covered_rrset->getRRsig()) {
            isc_throw(AddError,
                      "RRSIG is being added to override an existing one: "
                      << sig_rrset->toText());
        }

        // All okay, setting the RRSIG.
        // XXX: we break const-ness of the covered RRsets.  In practice the
        // ownership of these RRsets would have been given to us so it should
        // be safe, but it's still a very bad practice.
        // We'll fix this problem anyway when we update the underlying
        // representation so that it's more space efficient.
        // Note: there's a slight chance of getting an exception.
        // As noted in add(), we give up strong exception guarantee in such
        // cases.
        boost::const_pointer_cast<AbstractRRset>(covered_rrset)->addRRsig(sig_rrset);

        return (result::SUCCESS);
    }

    result::Result addNSEC3(const ConstRRsetPtr rrset, ZoneData& zone_data) {
        // We know rrset has exactly one RDATA
        const generic::NSEC3& nsec3_rdata =
            dynamic_cast<const generic::NSEC3&>(
                rrset->getRdataIterator()->getCurrent());

        NSEC3Data* nsec3_data = zone_data.getNSEC3Data();
        if (nsec3_data == NULL) {
            nsec3_data = NSEC3Data::create(local_mem_sgmt, nsec3_rdata);
            zone_data.setNSEC3Data(nsec3_data);
        } else {
            size_t salt_len = nsec3_data->getSaltLen();
            const uint8_t* salt_data = nsec3_data->getSaltData();
            const vector<uint8_t>& salt_data_2 = nsec3_rdata.getSalt();

            if ((nsec3_rdata.getHashalg() != nsec3_data->hashalg) ||
                (nsec3_rdata.getIterations() != nsec3_data->iterations) ||
                (salt_data_2.size() != salt_len) ||
                (std::memcmp(&salt_data_2[0], salt_data, salt_len) != 0)) {
                isc_throw(AddError,
                          "NSEC3 with inconsistent parameters: " <<
                          rrset->toText());
            }
        }

        string fst_label = rrset->getName().split(0, 1).toText(true);
        transform(fst_label.begin(), fst_label.end(), fst_label.begin(),
                  ::toupper);

        ZoneNode *node;
        nsec3_data->insertName(local_mem_sgmt, Name(fst_label), &node);

        RdataEncoder encoder;
        RdataSet *set = RdataSet::create(local_mem_sgmt, encoder,
                                         rrset, ConstRRsetPtr());
        RdataSet *old_set = node->setData(set);
        if (old_set != NULL) {
            RdataSet::destroy(local_mem_sgmt, rrclass_, old_set);
        }

        return (result::SUCCESS);
    }

    /*
     * Implementation of longer methods. We put them here, because the
     * access is without the impl_-> and it will get inlined anyway.
     */

    // Implementation of InMemoryClient::add()
    result::Result add(const ConstRRsetPtr& rrset,
                       const Name& zone_name, ZoneData& zone_data)
    {
        // Sanitize input.  This will cause an exception to be thrown
        // if the input RRset is empty.
        addValidation(zone_name, rrset);

        // OK, can add the RRset.
        LOG_DEBUG(logger, DBG_TRACE_DATA, DATASRC_MEM_ADD_RRSET).
            arg(rrset->getName()).arg(rrset->getType()).arg(zone_name);

        if (rrset->getType() == RRType::NSEC3()) {
            return (addNSEC3(rrset, zone_data));
        }

        // RRSIGs are special in various points, so we handle it in a
        // separate dedicated method.
        if (rrset->getType() == RRType::RRSIG()) {
            return (addRRsig(rrset, zone_data));
        }

        // Add wildcards possibly contained in the owner name to the domain
        // tree.
        // Note: this can throw an exception, breaking strong exception
        // guarantee.  (see also the note for contextCheck() below).
        addWildcards(zone_name, zone_data, rrset->getName());

        // Get the node
        DomainNode* node;
        DomainTree::Result result =
            zone_data.domains_.insert(zone_data.local_mem_sgmt_,
                                      rrset->getName(), &node);
        // Just check it returns reasonable results
        assert((result == DomainTree::SUCCESS ||
                result == DomainTree::ALREADYEXISTS) && node!= NULL);

        // Now get the domain
        DomainPtr domain;
        // It didn't exist yet, create it
        if (node->isEmpty()) {
            domain.reset(new Domain);
            node->setData(domain);
        } else { // Get existing one
            domain = node->getData();
        }

        // Checks related to the surrounding data.
        // Note: when the check fails and the exception is thrown, it may
        // break strong exception guarantee.  At the moment we prefer
        // code simplicity and don't bother to introduce complicated
        // recovery code.
        contextCheck(*rrset, *domain);

        // Try inserting the rrset there
        if (domain->insert(DomainPair(rrset->getType(), rrset)).second) {
            // Ok, we just put it in

            // If this RRset creates a zone cut at this node, mark the node
            // indicating the need for callback in find().
            if (rrset->getType() == RRType::NS() &&
                rrset->getName() != zone_name) {
                node->setFlag(DomainNode::FLAG_CALLBACK);
                // If it is DNAME, we have a callback as well here
            } else if (rrset->getType() == RRType::DNAME()) {
                node->setFlag(DomainNode::FLAG_CALLBACK);
            }

            // If we've added NSEC3PARAM at zone origin, set up NSEC3 specific
            // data or check consistency with already set up parameters.
            if (rrset->getType() == RRType::NSEC3PARAM() &&
                rrset->getName() == zone_name) {
                // We know rrset has exactly one RDATA
                const generic::NSEC3PARAM& param =
                    dynamic_cast<const generic::NSEC3PARAM&>(
                        rrset->getRdataIterator()->getCurrent());

                if (!zone_data.nsec3_data_) {
                    zone_data.nsec3_data_.reset(
                        new ZoneData::NSEC3Data(param));
                } else if (!zone_data.nsec3_data_->hash_->match(param)) {
                    isc_throw(AddError, "NSEC3PARAM with inconsistent "
                              "parameters: " << rrset->toText());
                }
            } else if (rrset->getType() == RRType::NSEC()) {
                // If it is NSEC signed zone, so we put a flag there
                // (flag is enough)
                zone_data.nsec_signed_ = true;
            }
            return (result::SUCCESS);
        } else {
            // The RRSet of given type was already there
            return (result::EXIST);
        }
    }

    /*
     * Same as above, but it checks the return value and if it already exists,
     * it throws.
     */
    void addFromLoad(const ConstRRsetPtr& set,
                     const Name& zone_name, ZoneData* zone_data)
    {
        switch (add(set, zone_name, *zone_data)) {
        case result::EXIST:
            LOG_ERROR(logger, DATASRC_MEM_DUP_RRSET).
                arg(set->getName()).arg(set->getType());
            isc_throw(dns::MasterLoadError, "Duplicate rrset: " <<
                      set->toText());
        case result::SUCCESS:
            return;
        default:
            assert(0);
        }
    }
};

result::Result
InMemoryClient::InMemoryClientImpl::load(
    const Name& zone_name,
    const string& filename,
    boost::function<void(LoadCallback)> rrset_installer)
{
    SegmentObjectHolder<ZoneData, RRClass> holder(
        local_mem_sgmt, ZoneData::create(local_mem_sgmt, zone_name), rrclass_);
    scoped_ptr<ZoneData> tmp(holder.get());

    rrset_installer(boost::bind(&InMemoryClientImpl::addFromLoad, this,
                                _1, zone_name, tmp.get()));

    // If the zone is NSEC3-signed, check if it has NSEC3PARAM
    if (tmp->nsec3_data_) {
        // Note: origin_data_ is set on creation of ZoneData, and the load
        // process only adds new nodes (and their data), so this assertion
        // should hold.
        assert(tmp->origin_data_ != NULL && !tmp->origin_data_->isEmpty());
        if (tmp->origin_data_->getData()->find(RRType::NSEC3PARAM()) ==
            tmp->origin_data_->getData()->end()) {
            LOG_WARN(logger, DATASRC_MEM_NO_NSEC3PARAM).
                arg(origin_).arg(client_.getClass());
        }
    }

    LOG_DEBUG(logger, DBG_TRACE_BASIC, DATASRC_MEM_ADD_ZONE).
        arg(zone_name).arg(getClass().toText());

    ++impl_->zone_count;

    // Set the filename in file_name_tree_ now, so that getFileName()
    // can use it (during zone reloading).
    FileNameNode* node(NULL);
    switch (impl_->file_name_tree_->insert(impl_->local_mem_sgmt,
                                           zone_name, &node)) {
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

    ZoneTable::AddResult result(zone_table_->addZone(local_mem_sgmt,
                                                     rrclass_, zone_name));
    ZoneData *data = zone_table_->setZoneData(zone_name, holder.release());
    if (data != NULL) {
        ZoneData::destroy(local_mem_sgmt, data, rrclass_);
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
    vector<ConstRRsetPtr> rrsigs; // placeholder for RRSIGs until "commitable".

    // The current internal implementation assumes an RRSIG is always added
    // after the RRset they cover.  So we store any RRSIGs in 'rrsigs' until
    // it's safe to add them; based on our assumption if the owner name
    // changes, all covered RRsets of the previous name should have been
    // installed and any pending RRSIGs can be added at that point.  RRSIGs
    // of the last name from the iterator must be added separately.
    while ((rrset = iterator->getNextRRset()) != NULL) {
        if (!rrsigs.empty() && rrset->getName() != rrsigs[0]->getName()) {
            BOOST_FOREACH(ConstRRsetPtr sig_rrset, rrsigs) {
                callback(sig_rrset);
            }
            rrsigs.clear();
        }
        if (rrset->getType() == RRType::RRSIG()) {
            rrsigs.push_back(rrset);
        } else {
            callback(rrset);
        }
    }

    BOOST_FOREACH(ConstRRsetPtr sig_rrset, rrsigs) {
        callback(sig_rrset);
    }
}
}

InMemoryClient::InMemoryClient(RRClass rrclass) :
    impl_(new InMemoryClientImpl(rrclass))
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
    return (impl_->zone_count);
}

ZoneTable::FindResult
InMemoryClient::findZone(const isc::dns::Name& zone_name) const {
    LOG_DEBUG(logger, DBG_TRACE_DATA, DATASRC_MEM_FIND_ZONE).arg(zone_name);
    ZoneTable::FindResult result(impl_->zone_table_->findZone(zone_name));
    return (result);
}

result::Result
InMemoryClient::load(const isc::dns::Name& zone_name,
                     const std::string& filename) {
    LOG_DEBUG(logger, DBG_TRACE_BASIC, DATASRC_MEM_LOAD).arg(zone_name).
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
                    const ConstRRsetPtr& rrset) {
    ZoneTable::FindResult result(impl_->zone_table_->findZone(zone_name));
    if (result.code != result::SUCCESS) {
        isc_throw(DataSourceError, "No such zone: " + zone_name.toText());
    }

    return (impl_->add(rrset, zone_name, *result.zone_data, NULL));
}

#if 0

namespace {

class MemoryIterator : public ZoneIterator {
private:
    RBTreeNodeChain<Domain> chain_;
    Domain::const_iterator dom_iterator_;
    const DomainTree& tree_;
    const DomainNode* node_;
    // Only used when separate_rrs_ is true
    RdataIteratorPtr rdata_iterator_;
    bool separate_rrs_;
    bool ready_;
public:
    MemoryIterator(const DomainTree& tree, const Name& origin, bool separate_rrs) :
        tree_(tree),
        separate_rrs_(separate_rrs),
        ready_(true)
    {
        // Find the first node (origin) and preserve the node chain for future
        // searches
        DomainTree::Result result(tree_.find(origin, &node_, chain_));
        // It can't happen that the origin is not in there
        if (result != DomainTree::EXACTMATCH) {
            isc_throw(Unexpected,
                      "In-memory zone corrupted, missing origin node");
        }
        // Initialize the iterator if there's somewhere to point to
        if (node_ != NULL && node_->getData() != DomainPtr()) {
            dom_iterator_ = node_->getData()->begin();
            if (separate_rrs_ && dom_iterator_ != node_->getData()->end()) {
                rdata_iterator_ = dom_iterator_->second->getRdataIterator();
            }
        }
    }

    virtual ConstRRsetPtr getNextRRset() {
        if (!ready_) {
            isc_throw(Unexpected, "Iterating past the zone end");
        }
        /*
         * This cycle finds the first nonempty node with yet unused RRset.
         * If it is NULL, we run out of nodes. If it is empty, it doesn't
         * contain any RRsets. If we are at the end, just get to next one.
         */
        while (node_ != NULL && (node_->getData() == DomainPtr() ||
                                 dom_iterator_ == node_->getData()->end())) {
            node_ = tree_.nextNode(chain_);
            // If there's a node, initialize the iterator and check next time
            // if the map is empty or not
            if (node_ != NULL && node_->getData() != NULL) {
                dom_iterator_ = node_->getData()->begin();
                // New RRset, so get a new rdata iterator
                if (separate_rrs_) {
                    rdata_iterator_ = dom_iterator_->second->getRdataIterator();
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
            RRsetPtr result(new RRset(dom_iterator_->second->getName(),
                                      dom_iterator_->second->getClass(),
                                      dom_iterator_->second->getType(),
                                      dom_iterator_->second->getTTL()));
            result->addRdata(rdata_iterator_->getCurrent());
            rdata_iterator_->next();
            if (rdata_iterator_->isLast()) {
                // all used up, next.
                ++dom_iterator_;
                // New RRset, so get a new rdata iterator, but only if this
                // was not the final RRset in the chain
                if (dom_iterator_ != node_->getData()->end()) {
                    rdata_iterator_ = dom_iterator_->second->getRdataIterator();
                }
            }
            return (result);
        } else {
            // The iterator points to the next yet unused RRset now
            ConstRRsetPtr result(dom_iterator_->second);

            // This one is used, move it to the next time for next call
            ++dom_iterator_;

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

    const ZoneData* data = result.zone_data;
    if (zone == NULL) {
        /*
         * TODO: This can happen only during some of the tests and only as
         * a temporary solution. This should be fixed by #1159 and then
         * this cast and check shouldn't be necessary. We don't have
         * test for handling a "can not happen" condition.
         */
        isc_throw(Unexpected, "The zone at " + name.toText() +
                  " is not InMemoryZoneFinder");
    }
    return (ZoneIteratorPtr(new MemoryIterator(
                                zone->impl_->zone_data_->domains_, name,
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

#endif

} // end of namespace memory
} // end of namespace datasrc
} // end of namespace isc
