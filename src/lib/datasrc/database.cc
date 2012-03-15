// Copyright (C) 2011  Internet Systems Consortium, Inc. ("ISC")
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

#include <string>
#include <utility>
#include <vector>

#include <datasrc/database.h>
#include <datasrc/data_source.h>
#include <datasrc/iterator.h>

#include <exceptions/exceptions.h>
#include <dns/name.h>
#include <dns/rrclass.h>
#include <dns/rrttl.h>
#include <dns/rrset.h>
#include <dns/rdata.h>
#include <dns/rdataclass.h>

#include <datasrc/data_source.h>
#include <datasrc/logger.h>

#include <boost/foreach.hpp>

using namespace isc::dns;
using namespace std;
using namespace isc::dns::rdata;

namespace isc {
namespace datasrc {

DatabaseClient::DatabaseClient(RRClass rrclass,
                               boost::shared_ptr<DatabaseAccessor>
                               accessor) :
    rrclass_(rrclass), accessor_(accessor)
{
    if (!accessor_) {
        isc_throw(isc::InvalidParameter,
                  "No database provided to DatabaseClient");
    }
}

DataSourceClient::FindResult
DatabaseClient::findZone(const Name& name) const {
    std::pair<bool, int> zone(accessor_->getZone(name.toText()));
    // Try exact first
    if (zone.first) {
        return (FindResult(result::SUCCESS,
                           ZoneFinderPtr(new Finder(accessor_,
                                                    zone.second, name))));
    }
    // Then super domains
    // Start from 1, as 0 is covered above
    for (size_t i(1); i < name.getLabelCount(); ++i) {
        isc::dns::Name superdomain(name.split(i));
        zone = accessor_->getZone(superdomain.toText());
        if (zone.first) {
            return (FindResult(result::PARTIALMATCH,
                               ZoneFinderPtr(new Finder(accessor_,
                                                        zone.second,
                                                        superdomain))));
        }
    }
    // No, really nothing
    return (FindResult(result::NOTFOUND, ZoneFinderPtr()));
}

DatabaseClient::Finder::Finder(boost::shared_ptr<DatabaseAccessor> accessor,
                               int zone_id, const isc::dns::Name& origin) :
    accessor_(accessor),
    zone_id_(zone_id),
    origin_(origin)
{ }

namespace {
// Adds the given Rdata to the given RRset
// If the rrset is an empty pointer, a new one is
// created with the given name, class, type and ttl
// The type is checked if the rrset exists, but the
// name is not.
//
// Then adds the given rdata to the set
//
// Raises a DataSourceError if the type does not
// match, or if the given rdata string does not
// parse correctly for the given type and class
//
// The DatabaseAccessor is passed to print the
// database name in the log message if the TTL is
// modified
void addOrCreate(isc::dns::RRsetPtr& rrset,
                    const isc::dns::Name& name,
                    const isc::dns::RRClass& cls,
                    const isc::dns::RRType& type,
                    const isc::dns::RRTTL& ttl,
                    const std::string& rdata_str,
                    const DatabaseAccessor& db
                )
{
    if (!rrset) {
        rrset.reset(new isc::dns::RRset(name, cls, type, ttl));
    } else {
        // This is a check to make sure find() is not messing things up
        assert(type == rrset->getType());
        if (ttl != rrset->getTTL()) {
            if (ttl < rrset->getTTL()) {
                rrset->setTTL(ttl);
            }
            logger.warn(DATASRC_DATABASE_FIND_TTL_MISMATCH)
                .arg(db.getDBName()).arg(name).arg(cls)
                .arg(type).arg(rrset->getTTL());
        }
    }
    try {
        rrset->addRdata(isc::dns::rdata::createRdata(type, cls, rdata_str));
    } catch (const isc::dns::rdata::InvalidRdataText& ivrt) {
        // at this point, rrset may have been initialised for no reason,
        // and won't be used. But the caller would drop the shared_ptr
        // on such an error anyway, so we don't care.
        isc_throw(DataSourceError,
                    "bad rdata in database for " << name << " "
                    << type << ": " << ivrt.what());
    }
}

// This class keeps a short-lived store of RRSIG records encountered
// during a call to find(). If the backend happens to return signatures
// before the actual data, we might not know which signatures we will need
// So if they may be relevant, we store the in this class.
//
// (If this class seems useful in other places, we might want to move
// it to util. That would also provide an opportunity to add unit tests)
class RRsigStore {
public:
    // Adds the given signature Rdata to the store
    // The signature rdata MUST be of the RRSIG rdata type
    // (the caller must make sure of this).
    // NOTE: if we move this class to a public namespace,
    // we should add a type_covered argument, so as not
    // to have to do this cast here.
    void addSig(isc::dns::rdata::RdataPtr sig_rdata) {
        const isc::dns::RRType& type_covered =
            static_cast<isc::dns::rdata::generic::RRSIG*>(
                sig_rdata.get())->typeCovered();
        sigs[type_covered].push_back(sig_rdata);
    }

    // If the store contains signatures for the type of the given
    // rrset, they are appended to it.
    void appendSignatures(isc::dns::RRsetPtr& rrset) const {
        std::map<isc::dns::RRType,
                 std::vector<isc::dns::rdata::RdataPtr> >::const_iterator
            found = sigs.find(rrset->getType());
        if (found != sigs.end()) {
            BOOST_FOREACH(isc::dns::rdata::RdataPtr sig, found->second) {
                rrset->addRRsig(sig);
            }
        }
    }

private:
    std::map<isc::dns::RRType, std::vector<isc::dns::rdata::RdataPtr> > sigs;
};
}

DatabaseClient::Finder::FoundRRsets
DatabaseClient::Finder::getRRsets(const string& name, const WantedTypes& types,
                                  bool check_ns, const string* construct_name,
                                  bool any)
{
    RRsigStore sig_store;
    bool records_found = false;
    std::map<RRType, RRsetPtr> result;

    // Request the context
    DatabaseAccessor::IteratorContextPtr
        context(accessor_->getRecords(name, zone_id_));
    // It must not return NULL, that's a bug of the implementation
    if (!context) {
        isc_throw(isc::Unexpected, "Iterator context null at " + name);
    }

    std::string columns[DatabaseAccessor::COLUMN_COUNT];
    if (construct_name == NULL) {
        construct_name = &name;
    }

    const Name construct_name_object(*construct_name);

    bool seen_cname(false);
    bool seen_ds(false);
    bool seen_other(false);
    bool seen_ns(false);

    while (context->getNext(columns)) {
        // The domain is not empty
        records_found = true;

        try {
            const RRType cur_type(columns[DatabaseAccessor::TYPE_COLUMN]);

            if (cur_type == RRType::RRSIG()) {
                // If we get signatures before we get the actual data, we
                // can't know which ones to keep and which to drop...
                // So we keep a separate store of any signature that may be
                // relevant and add them to the final RRset when we are
                // done.
                // A possible optimization here is to not store them for
                // types we are certain we don't need
                sig_store.addSig(rdata::createRdata(cur_type, getClass(),
                     columns[DatabaseAccessor::RDATA_COLUMN]));
            }

            if (types.find(cur_type) != types.end() || any) {
                // This type is requested, so put it into result
                const RRTTL cur_ttl(columns[DatabaseAccessor::TTL_COLUMN]);
                // Ths sigtype column was an optimization for finding the
                // relevant RRSIG RRs for a lookup. Currently this column is
                // not used in this revised datasource implementation. We
                // should either start using it again, or remove it from use
                // completely (i.e. also remove it from the schema and the
                // backend implementation).
                // Note that because we don't use it now, we also won't notice
                // it if the value is wrong (i.e. if the sigtype column
                // contains an rrtype that is different from the actual value
                // of the 'type covered' field in the RRSIG Rdata).
                //cur_sigtype(columns[SIGTYPE_COLUMN]);
                addOrCreate(result[cur_type], construct_name_object,
                            getClass(), cur_type, cur_ttl,
                            columns[DatabaseAccessor::RDATA_COLUMN],
                            *accessor_);
            }

            if (cur_type == RRType::CNAME()) {
                seen_cname = true;
            } else if (cur_type == RRType::NS()) {
                seen_ns = true;
            } else if (cur_type == RRType::DS()) {
                seen_ds = true;
            } else if (cur_type != RRType::RRSIG() &&
                       cur_type != RRType::NSEC3() &&
                       cur_type != RRType::NSEC()) {
                // NSEC and RRSIG can coexist with anything, otherwise
                // we've seen something that can't live together with potential
                // CNAME or NS
                //
                // NSEC3 lives in separate namespace from everything, therefore
                // we just ignore it here for these checks as well.
                seen_other = true;
            }
        } catch (const InvalidRRType&) {
            isc_throw(DataSourceError, "Invalid RRType in database for " <<
                      name << ": " << columns[DatabaseAccessor::
                      TYPE_COLUMN]);
        } catch (const InvalidRRTTL&) {
            isc_throw(DataSourceError, "Invalid TTL in database for " <<
                      name << ": " << columns[DatabaseAccessor::
                      TTL_COLUMN]);
        } catch (const rdata::InvalidRdataText&) {
            isc_throw(DataSourceError, "Invalid rdata in database for " <<
                      name << ": " << columns[DatabaseAccessor::
                      RDATA_COLUMN]);
        }
    }
    if (seen_cname && (seen_other || seen_ns || seen_ds)) {
        isc_throw(DataSourceError, "CNAME shares domain " << name <<
                  " with something else");
    }
    if (check_ns && seen_ns && seen_other) {
        isc_throw(DataSourceError, "NS shares domain " << name <<
                  " with something else");
    }
    // Add signatures to all found RRsets
    for (std::map<RRType, RRsetPtr>::iterator i(result.begin());
         i != result.end(); ++ i) {
        sig_store.appendSignatures(i->second);
    }

    if (records_found && any) {
        result[RRType::ANY()] = RRsetPtr();
        // These will be sitting on the other RRsets.
        result.erase(RRType::RRSIG());
    }

    return (FoundRRsets(records_found, result));
}

bool
DatabaseClient::Finder::hasSubdomains(const std::string& name) {
    // Request the context
    DatabaseAccessor::IteratorContextPtr
        context(accessor_->getRecords(name, zone_id_, true));
    // It must not return NULL, that's a bug of the implementation
    if (!context) {
        isc_throw(isc::Unexpected, "Iterator context null at " + name);
    }

    std::string columns[DatabaseAccessor::COLUMN_COUNT];
    return (context->getNext(columns));
}

// Some manipulation with RRType sets
namespace {

// Bunch of functions to construct specific sets of RRTypes we will
// ask from it.
typedef std::set<RRType> WantedTypes;

const WantedTypes&
NSEC_TYPES() {
    static bool initialized(false);
    static WantedTypes result;

    if (!initialized) {
        result.insert(RRType::NSEC());
        initialized = true;
    }
    return (result);
}

const WantedTypes&
DELEGATION_TYPES() {
    static bool initialized(false);
    static WantedTypes result;

    if (!initialized) {
        result.insert(RRType::DNAME());
        result.insert(RRType::NS());
        initialized = true;
    }
    return (result);
}

const WantedTypes&
FINAL_TYPES() {
    static bool initialized(false);
    static WantedTypes result;

    if (!initialized) {
        result.insert(RRType::CNAME());
        result.insert(RRType::NS());
        result.insert(RRType::NSEC());
        initialized = true;
    }
    return (result);
}

}

ConstRRsetPtr
DatabaseClient::Finder::findNSECCover(const Name& name) {
    try {
        // Which one should contain the NSEC record?
        const Name coverName(findPreviousName(name));
        // Get the record and copy it out
        const FoundRRsets found = getRRsets(coverName.toText(), NSEC_TYPES(),
                                            coverName != getOrigin());
        const FoundIterator
            nci(found.second.find(RRType::NSEC()));
        if (nci != found.second.end()) {
            return (nci->second);
        } else {
            // The previous doesn't contain NSEC.
            // Badly signed zone or a bug?

            // FIXME: Currently, if the zone is not signed, we could get
            // here. In that case we can't really throw, but for now, we can't
            // recognize it. So we don't throw at all, enable it once
            // we have a is_signed flag or something.
#if 0
            isc_throw(DataSourceError, "No NSEC in " +
                      coverName.toText() + ", but it was "
                      "returned as previous - "
                      "accessor error? Badly signed zone?");
#endif
        }
    }
    catch (const isc::NotImplemented&) {
        // Well, they want DNSSEC, but there is no available.
        // So we don't provide anything.
        LOG_INFO(logger, DATASRC_DATABASE_COVER_NSEC_UNSUPPORTED).
            arg(accessor_->getDBName()).arg(name);
    }
    // We didn't find it, return nothing
    return (ConstRRsetPtr());
}

ZoneFinderContextPtr
DatabaseClient::Finder::findAll(const isc::dns::Name& name,
                                std::vector<isc::dns::ConstRRsetPtr>& target,
                                const FindOptions options)
{
    return (ZoneFinderContextPtr(new Context(*this, options,
                                             findInternal(name, RRType::ANY(),
                                                          &target, options),
                                             target)));
}

ZoneFinderContextPtr
DatabaseClient::Finder::find(const isc::dns::Name& name,
                             const isc::dns::RRType& type,
                             const FindOptions options)
{
    if (type == RRType::ANY()) {
        isc_throw(isc::Unexpected, "Use findAll to answer ANY");
    }
    return (ZoneFinderContextPtr(new Context(*this, options,
                                             findInternal(name, type,
                                                          NULL, options))));
}

DatabaseClient::Finder::DelegationSearchResult
DatabaseClient::Finder::findDelegationPoint(const isc::dns::Name& name,
                                            const FindOptions options)
{
    // Result of search
    isc::dns::ConstRRsetPtr result_rrset;
    ZoneFinder::Result result_status = SUCCESS;

    // Are we searching for glue?
    const bool glue_ok = ((options & FIND_GLUE_OK) != 0);

    // This next declaration is an optimisation.  When we search the database
    // for glue records, we generally ignore delegations. (This allows for
    // the case where e.g. the delegation to zone example.com refers to
    // nameservers within the zone, e.g. ns1.example.com.  When conducting the
    // search for ns1.example.com, we have to search past the NS records at
    // example.com.)
    //
    // The one case where this is forbidden is when we search past the zone
    // cut but the match we find for the glue is a wildcard match.  In that
    // case, we return the delegation instead (see RFC 1034, section 4.3.3).
    // To save a new search, we record the location of the delegation cut when
    // we encounter it here.
    isc::dns::ConstRRsetPtr first_ns;

    // We want to search from the apex down.  We are given the full domain
    // name so we have to do some manipulation to ensure that when we start
    // checking superdomains, we start from the the domain name of the zone
    // (e.g. if the name is b.a.example.com. and we are in the example.com.
    // zone, we check example.com., a.example.com. and b.a.example.com.  We
    // don't need to check com. or .).
    //
    // Set the number of labels in the origin (i.e. apex of the zone) and in
    // the last known non-empty domain (which, at this point, is the origin).
    const size_t origin_label_count = getOrigin().getLabelCount();
    size_t last_known = origin_label_count;

    // Set how many labels we remove to get origin: this is the number of
    // labels we have to process in our search.
    const size_t remove_labels = name.getLabelCount() - origin_label_count;

    // Go through all superdomains from the origin down searching for nodes
    // that indicate a delegation (.e. NS or DNAME).
    for (int i = remove_labels; i > 0; --i) {
        const Name superdomain(name.split(i));

        // Note if this is the origin. (We don't count NS records at the origin
        // as a delegation so this controls whether NS RRs are included in
        // the results of some searches.)
        const bool not_origin = (i != remove_labels);

        // Look if there's NS or DNAME at this point of the tree, but ignore
        // the NS RRs at the apex of the zone.
        const FoundRRsets found = getRRsets(superdomain.toText(),
                                            DELEGATION_TYPES(), not_origin);
        if (found.first) {
            // This node contains either NS or DNAME RRs so it does exist.
            const FoundIterator nsi(found.second.find(RRType::NS()));
            const FoundIterator dni(found.second.find(RRType::DNAME()));

            // An optimisation.  We know that there is an exact match for
            // something at this point in the tree so remember it.  If we have
            // to do a wildcard search, as we search upwards through the tree
            // we don't need to pass this point, which is an exact match for
            // the domain name.
            last_known = superdomain.getLabelCount();

            if (glue_ok && !first_ns && not_origin &&
                    nsi != found.second.end()) {
                // If we are searching for glue ("glue OK" mode), store the
                // highest NS record that we find that is not the apex.  This
                // is another optimisation for later, where we need the
                // information if the domain we are looking for matches through
                // a wildcard.
                first_ns = nsi->second;

            } else if (!glue_ok && not_origin && nsi != found.second.end()) {
                // Not searching for glue and we have found an NS RRset that is
                // not at the apex.  We have found a delegation - return that
                // fact, there is no need to search further down the tree.
                LOG_DEBUG(logger, DBG_TRACE_DETAILED,
                          DATASRC_DATABASE_FOUND_DELEGATION).
                    arg(accessor_->getDBName()).arg(superdomain);
                result_rrset = nsi->second;
                result_status = DELEGATION;
                break;

            } else if (dni != found.second.end()) {
                // We have found a DNAME so again stop searching down the tree
                // and return the information.
                LOG_DEBUG(logger, DBG_TRACE_DETAILED,
                          DATASRC_DATABASE_FOUND_DNAME).
                    arg(accessor_->getDBName()).arg(superdomain);
                result_rrset = dni->second;
                result_status = DNAME;
                if (result_rrset->getRdataCount() != 1) {
                    isc_throw(DataSourceError, "DNAME at " << superdomain <<
                              " has " << result_rrset->getRdataCount() <<
                              " rdata, 1 expected");
                }
                break;
            }
        }
    }
    return (DelegationSearchResult(result_status, result_rrset, first_ns,
                                   last_known));
}

// This method is called when we have not found an exact match and when we
// know that the name is not an empty non-terminal.  So the only way that
// the name can match something in the zone is through a wildcard match.
//
// During an earlier stage in the search for this name, we made a record of
// the lowest superdomain for which we know an RR exists. (Note the "we
// know" qualification - there may be lower superdomains (ones with more
// labels) that hold an RR, but as we weren't searching for them, we don't
// know about them.)
//
// In the search for a wildcard match (which starts at the given domain
// name and goes up the tree to successive superdomains), this is the level
// at which we can stop - there can't be a wildcard at or beyond that
// point.
//
// At each level that can stop the search, we should consider several cases:
//
// - If we found a wildcard match for a glue record below a
// delegation point, we don't return the match,
// instead we return the delegation.  (Note that if we didn't
// a wildcard match at all, we would return NXDOMAIN, not the
// the delegation.)
//
// - If we found a wildcard match and we are sure that the match
// is not an empty non-terminal, return the result taking into account CNAME,
// on a zone cut, and NXRRSET.
// (E.g. searching for a match
// for c.b.a.example.com, we found that b.a.example.com did
// not exist but that *.a.example.com. did. Checking
// b.a.example.com revealed no subdomains, so we can use the
// wilcard match we found.)
//
// - If we found a more specified match, the wildcard search
// is canceled, resulting in NXDOMAIN.  (E.g. searching for a match
// for c.b.a.example.com, we found that b.a.example.com did
// not exist but that *.a.example.com. did. Checking
// b.a.example.com found subdomains.  So b.example.com is
// an empty non-terminal and so should not be returned in
// the wildcard matching process.  In other words,
// b.example.com does exist in the DNS space, it just doesn't
// have any RRs associated with it.)
//
// - If we found a match, but it is an empty non-terminal asterisk (E.g.#
// subdomain.*.example.com.  is present, but there is nothing at
// *.example.com.),  return an NXRRSET indication;
// the wildcard exists in the DNS space, there's just nothing
// associated with it.  If DNSSEC data is required, return the
// covering NSEC record.
//
// If none of the above applies in any level, the search fails with NXDOMAIN.
ZoneFinder::ResultContext
DatabaseClient::Finder::findWildcardMatch(
    const isc::dns::Name& name, const isc::dns::RRType& type,
    const FindOptions options, const DelegationSearchResult& dresult,
    std::vector<isc::dns::ConstRRsetPtr>* target)
{
    // Note that during the search we are going to search not only for the
    // requested type, but also for types that indicate a delegation -
    // NS and DNAME.
    WantedTypes final_types(FINAL_TYPES());
    final_types.insert(type);

    const size_t remove_labels = name.getLabelCount() - dresult.last_known;
    for (size_t i = 1; i <= remove_labels; ++i) {

        // Strip off the left-more label(s) in the name and replace with a "*".
        const Name superdomain(name.split(i));
        const string wildcard("*." + superdomain.toText());
        const string construct_name(name.toText());

        // TODO Add a check for DNAME, as DNAME wildcards are discouraged (see
        // RFC 4592 section 4.4).
        // Search for a match.  The types are the same as with original query.
        FoundRRsets found = getRRsets(wildcard, final_types, true,
                                      &construct_name, type == RRType::ANY());
        if (found.first) {
            // Found something - but what?

            if (dresult.first_ns) {
                // About to use first_ns.  The only way this can be set is if
                // we are searching for glue, so do a sanity check.
                if ((options & FIND_GLUE_OK) == 0) {
                    isc_throw(Unexpected, "Inconsistent conditions during "
                              "cancel of wilcard search for " <<
                              name.toText() << ": find_ns non-null when not "
                              "processing glue request");
                }

                // Wildcard match for a glue below a delegation point
                LOG_DEBUG(logger, DBG_TRACE_DETAILED,
                          DATASRC_DATABASE_WILDCARD_CANCEL_NS).
                    arg(accessor_->getDBName()).arg(wildcard).
                    arg(dresult.first_ns->getName());
                return (ResultContext(DELEGATION, dresult.first_ns));
            } else if (!hasSubdomains(name.split(i - 1).toText())) {
                // The wildcard match is the best one, find the final result
                // at it.  Note that wildcard should never be the zone origin.
                return (findOnNameResult(name, type, options, false,
                                         found, &wildcard, target));
            } else {

                // more specified match found, cancel wildcard match
                LOG_DEBUG(logger, DBG_TRACE_DETAILED,
                          DATASRC_DATABASE_WILDCARD_CANCEL_SUB).
                    arg(accessor_->getDBName()).arg(wildcard).
                    arg(name).arg(superdomain);
                return (ResultContext(NXDOMAIN, ConstRRsetPtr()));
            }

        } else if (hasSubdomains(wildcard)) {
            // an empty non-terminal asterisk
            LOG_DEBUG(logger, DBG_TRACE_DETAILED,
                      DATASRC_DATABASE_WILDCARD_EMPTY).
                arg(accessor_->getDBName()).arg(wildcard).arg(name);
            if ((options & FIND_DNSSEC) != 0) {
                ConstRRsetPtr nsec = findNSECCover(Name(wildcard));
                if (nsec) {
                    return (ResultContext(NXRRSET, nsec,
                                          RESULT_WILDCARD |
                                          RESULT_NSEC_SIGNED));
                }
            }
            return (ResultContext(NXRRSET, ConstRRsetPtr(), RESULT_WILDCARD));
        }
    }

    // Nothing found at any level.
    return (ResultContext(NXDOMAIN, ConstRRsetPtr()));
}

ZoneFinder::ResultContext
DatabaseClient::Finder::logAndCreateResult(
    const Name& name, const string* wildname, const RRType& type,
    ZoneFinder::Result code, ConstRRsetPtr rrset,
    const isc::log::MessageID& log_id, FindResultFlags flags) const
{
    if (rrset) {
        if (wildname == NULL) {
            LOG_DEBUG(logger, DBG_TRACE_DETAILED, log_id).
                arg(accessor_->getDBName()).arg(name).arg(type).
                arg(getClass()).arg(*rrset);
        } else {
            LOG_DEBUG(logger, DBG_TRACE_DETAILED, log_id).
                arg(accessor_->getDBName()).arg(name).arg(type).
                arg(getClass()).arg(*wildname).arg(*rrset);
        }
    } else {
        if (wildname == NULL) {
            LOG_DEBUG(logger, DBG_TRACE_DETAILED, log_id).
                arg(accessor_->getDBName()).arg(name).arg(type).
                arg(getClass());
        } else {
            LOG_DEBUG(logger, DBG_TRACE_DETAILED, log_id).
                arg(accessor_->getDBName()).arg(name).arg(type).
                arg(getClass()).arg(*wildname);
        }
    }
    return (ResultContext(code, rrset, flags));
}

ZoneFinder::ResultContext
DatabaseClient::Finder::findOnNameResult(const Name& name,
                                         const RRType& type,
                                         const FindOptions options,
                                         const bool is_origin,
                                         const FoundRRsets& found,
                                         const string* wildname,
                                         std::vector<isc::dns::ConstRRsetPtr>*
                                         target)
{
    const bool wild = (wildname != NULL);
    FindResultFlags flags = wild ? RESULT_WILDCARD : RESULT_DEFAULT;

    // Get iterators for the different types of records we are interested in -
    // CNAME, NS and Wanted types.
    const FoundIterator nsi(found.second.find(RRType::NS()));
    const FoundIterator cni(found.second.find(RRType::CNAME()));
    const FoundIterator wti(found.second.find(type));
    // For wildcard case with DNSSEC required, the caller would need to know
    // whether it's NSEC or NSEC3 signed.  So we need to do an additional
    // search here, even though the NSEC RR may not be returned.
    // TODO: this part should be revised when we support NSEC3; ideally we
    // should use more effective and efficient way to identify (whether and)
    // in which way the zone is signed.
    if (wild && (options & FIND_DNSSEC) != 0 &&
        found.second.find(RRType::NSEC()) != found.second.end()) {
        flags = flags | RESULT_NSEC_SIGNED;
    }

    if (!is_origin && ((options & FIND_GLUE_OK) == 0) &&
        nsi != found.second.end()) {
        // A NS RRset was found at the domain we were searching for.  As it is
        // not at the origin of the zone, it is a delegation and indicates that
        // this zone is not authoritative for the data. Just return the
        // delegation information.
        return (logAndCreateResult(name, wildname, type, DELEGATION,
                                   nsi->second,
                                   wild ? DATASRC_DATABASE_WILDCARD_NS :
                                   DATASRC_DATABASE_FOUND_DELEGATION_EXACT,
                                   flags));

    } else if (type != RRType::CNAME() && cni != found.second.end()) {
        // We are not searching for a CNAME but nevertheless we have found one
        // at the name we are searching so we return it. (The caller may
        // want to continue the lookup by replacing the query name with the
        // canonical name and the original RR type.) First though, do a sanity
        // check to ensure that there is only one RR in the CNAME RRset.
        if (cni->second->getRdataCount() != 1) {
            isc_throw(DataSourceError, "CNAME with " <<
                      cni->second->getRdataCount() << " rdata at " << name <<
                      ", expected 1");
        }
        return (logAndCreateResult(name, wildname, type, CNAME, cni->second,
                                   wild ? DATASRC_DATABASE_WILDCARD_CNAME :
                                   DATASRC_DATABASE_FOUND_CNAME,
                                   flags));

    } else if (wti != found.second.end()) {
        bool any(type == RRType::ANY());
        isc::log::MessageID lid(wild ? DATASRC_DATABASE_WILDCARD_MATCH :
                                DATASRC_DATABASE_FOUND_RRSET);
        if (any) {
            // An ANY query, copy everything to the target instead of returning
            // directly.
            for (FoundIterator it(found.second.begin());
                 it != found.second.end(); ++it) {
                if (it->second) {
                    // Skip over the empty ANY
                    target->push_back(it->second);
                }
            }
            lid = wild ? DATASRC_DATABASE_WILDCARD_ANY :
                DATASRC_DATABASE_FOUND_ANY;
        }
        // Found an RR matching the query, so return it.  (Note that this
        // includes the case where we were explicitly querying for a CNAME and
        // found it.  It also includes the case where we were querying for an
        // NS RRset and found it at the apex of the zone.)
        return (logAndCreateResult(name, wildname, type, SUCCESS,
                                   wti->second, lid, flags));
    }

    // If we get here, we have found something at the requested name but not
    // one of the RR types we were interested in. This is the NXRRSET case so
    // return the appropriate status.  If DNSSEC information was requested,
    // provide the NSEC records.  If it's for wildcard, we need to get the
    // NSEC records in the name of the wildcard, not the substituted one,
    // so we need to search the tree again.
    ConstRRsetPtr nsec_rrset;   // possibly used with DNSSEC, otherwise NULL
    if ((options & FIND_DNSSEC) != 0) {
        if (wild) {
            const FoundRRsets wfound = getRRsets(*wildname, NSEC_TYPES(),
                                                 true);
            const FoundIterator nci = wfound.second.find(RRType::NSEC());
            if (nci != wfound.second.end()) {
                nsec_rrset = nci->second;
            }
        } else {
            const FoundIterator nci = found.second.find(RRType::NSEC());
            if (nci != found.second.end()) {
                nsec_rrset = nci->second;
            }
        }
    }
    if (nsec_rrset) {
        // This log message covers both normal and wildcard cases, so we pass
        // NULL for 'wildname'.
        return (logAndCreateResult(name, NULL, type, NXRRSET, nsec_rrset,
                                   DATASRC_DATABASE_FOUND_NXRRSET_NSEC,
                                   flags | RESULT_NSEC_SIGNED));
    }
    return (logAndCreateResult(name, wildname, type, NXRRSET, nsec_rrset,
                               wild ? DATASRC_DATABASE_WILDCARD_NXRRSET :
                               DATASRC_DATABASE_FOUND_NXRRSET, flags));
}

ZoneFinder::ResultContext
DatabaseClient::Finder::findNoNameResult(const Name& name, const RRType& type,
                                         FindOptions options,
                                         const DelegationSearchResult& dresult,
                                         std::vector<isc::dns::ConstRRsetPtr>*
                                         target)
{
    const bool dnssec_data = ((options & FIND_DNSSEC) != 0);

    // On entry to this method, we know that the database doesn't have any
    // entry for this name.  Before returning NXDOMAIN, we need to check
    // for special cases.

    if (hasSubdomains(name.toText())) {
        // Does the domain have a subdomain (i.e. it is an empty non-terminal)?
        // If so, return NXRRSET instead of NXDOMAIN (as although the name does
        // not exist in the database, it does exist in the DNS tree).
        LOG_DEBUG(logger, DBG_TRACE_DETAILED,
                  DATASRC_DATABASE_FOUND_EMPTY_NONTERMINAL).
            arg(accessor_->getDBName()).arg(name);
        const ConstRRsetPtr nsec = dnssec_data ? findNSECCover(name) :
            ConstRRsetPtr();
        return (ResultContext(NXRRSET, nsec,
                              nsec ? RESULT_NSEC_SIGNED : RESULT_DEFAULT));
    } else if ((options & NO_WILDCARD) == 0) {
        // It's not an empty non-terminal and wildcard matching is not
        // disabled, so check for wildcards. If there is a wildcard match
        // (i.e. all results except NXDOMAIN) return it; otherwise fall
        // through to the NXDOMAIN case below.
        const ResultContext wcontext =
            findWildcardMatch(name, type, options, dresult, target);
        if (wcontext.code != NXDOMAIN) {
            return (wcontext);
        }
    }

    // All avenues to find a match are now exhausted, return NXDOMAIN (plus
    // NSEC records if requested).
    LOG_DEBUG(logger, DBG_TRACE_DETAILED, DATASRC_DATABASE_NO_MATCH).
              arg(accessor_->getDBName()).arg(name).arg(type).arg(getClass());
    const ConstRRsetPtr nsec = dnssec_data ? findNSECCover(name) :
        ConstRRsetPtr();
    return (ResultContext(NXDOMAIN, nsec,
                          nsec ? RESULT_NSEC_SIGNED : RESULT_DEFAULT));
}

ZoneFinder::ResultContext
DatabaseClient::Finder::findInternal(const Name& name, const RRType& type,
                                     std::vector<ConstRRsetPtr>* target,
                                     const FindOptions options)
{
    LOG_DEBUG(logger, DBG_TRACE_DETAILED, DATASRC_DATABASE_FIND_RECORDS)
              .arg(accessor_->getDBName()).arg(name).arg(type).arg(getClass());

    // find() variants generally expect 'name' to be included in the zone.
    // Otherwise the search algorithm below won't work correctly, so we
    // reject the unexpected case first.
    const NameComparisonResult::NameRelation reln =
        name.compare(getOrigin()).getRelation();
    if (reln != NameComparisonResult::SUBDOMAIN &&
        reln != NameComparisonResult::EQUAL) {
        return (ResultContext(NXDOMAIN, ConstRRsetPtr()));
    }

    // First, go through all superdomains from the origin down, searching for
    // nodes that indicate a delegation (i.e. NS or DNAME, ignoring NS records
    // at the apex).  If one is found, the search stops there.
    //
    // (In fact there could be RRs in the database corresponding to subdomains
    // of the delegation.  The reason we do the search for the delegations
    // first is because the delegation means that another zone is authoritative
    // for the data and so should be consulted to retrieve it.  RRs below
    // this delegation point can be found in a search for glue but not
    // otherwise; in the latter case they are said to be occluded by the
    // presence of the delegation.)
    const DelegationSearchResult dresult = findDelegationPoint(name, options);
    if (dresult.rrset) {
        // In this case no special flags are needed.
        return (ResultContext(dresult.code, dresult.rrset));
    }

    // If there is no delegation, look for the exact match to the request
    // name/type/class.  However, there are special cases:
    // - Requested name has a singleton CNAME record associated with it
    // - Requested name is a delegation point (NS only but not at the zone
    //   apex - DNAME is ignored here as it redirects DNS names subordinate to
    //   the owner name - the owner name itself is not redirected.)
    const bool is_origin = (name == getOrigin());
    WantedTypes final_types(FINAL_TYPES());
    final_types.insert(type);
    const FoundRRsets found = getRRsets(name.toText(), final_types,
                                        !is_origin, NULL,
                                        type == RRType::ANY());

    if (found.first) {
        // Something found at the domain name.  Look into it further to get
        // the final result.
        return (findOnNameResult(name, type, options, is_origin, found, NULL,
                                 target));
    } else {
        // Did not find anything at all at the domain name, so check for
        // subdomains or wildcards.
        return (findNoNameResult(name, type, options, dresult, target));
    }
}

ZoneFinder::FindNSEC3Result
DatabaseClient::Finder::findNSEC3(const Name&, bool) {
    isc_throw(NotImplemented, "findNSEC3 is not yet implemented for database "
              "data source");
}

Name
DatabaseClient::Finder::findPreviousName(const Name& name) const {
    const string str(accessor_->findPreviousName(zone_id_,
                                                 name.reverse().toText()));
    try {
        return (Name(str));
    }

    // To avoid having the same code many times, we just catch all the
    // exceptions and handle them in a common code below
    catch (const isc::dns::EmptyLabel&) {}
    catch (const isc::dns::TooLongLabel&) {}
    catch (const isc::dns::BadLabelType&) {}
    catch (const isc::dns::BadEscape&) {}
    catch (const isc::dns::TooLongName&) {}
    catch (const isc::dns::IncompleteName&) {}
    isc_throw(DataSourceError, "Bad name " + str + " from findPreviousName");
}

Name
DatabaseClient::Finder::getOrigin() const {
    return (origin_);
}

isc::dns::RRClass
DatabaseClient::Finder::getClass() const {
    // TODO Implement
    return isc::dns::RRClass::IN();
}

namespace {

/// This needs, beside of converting all data from textual representation, group
/// together rdata of the same RRsets. To do this, we hold one row of data ahead
/// of iteration. When we get a request to provide data, we create it from this
/// data and load a new one. If it is to be put to the same rrset, we add it.
/// Otherwise we just return what we have and keep the row as the one ahead
/// for next time.
class DatabaseIterator : public ZoneIterator {
public:
    DatabaseIterator(boost::shared_ptr<DatabaseAccessor> accessor,
                     const Name& zone_name,
                     const RRClass& rrclass,
                     bool separate_rrs) :
        accessor_(accessor),
        class_(rrclass),
        ready_(true),
        separate_rrs_(separate_rrs)
    {
        // Get the zone
        const pair<bool, int> zone(accessor_->getZone(zone_name.toText()));
        if (!zone.first) {
            // No such zone, can't continue
            isc_throw(DataSourceError, "Zone " + zone_name.toText() +
                      " can not be iterated, because it doesn't exist "
                      "in this data source");
        }

        // Start a separate transaction.
        accessor_->startTransaction();

        // Find the SOA of the zone (may or may not succeed).  Note that
        // this must be done before starting the iteration context.
        soa_ = DatabaseClient::Finder(accessor_, zone.second, zone_name).
            find(zone_name, RRType::SOA())->rrset;

        // Request the context
        context_ = accessor_->getAllRecords(zone.second);
        // It must not return NULL, that's a bug of the implementation
        if (!context_) {
            isc_throw(isc::Unexpected, "Iterator context null at " +
                      zone_name.toText());
        }

        // Prepare data for the next time
        getData();
    }

    virtual ~DatabaseIterator() {
        if (ready_) {
            accessor_->commit();
        }
    }

    virtual ConstRRsetPtr getSOA() const {
        return (soa_);
    }

    virtual isc::dns::ConstRRsetPtr getNextRRset() {
        if (!ready_) {
            isc_throw(isc::Unexpected, "Iterating past the zone end");
        }
        if (!data_ready_) {
            // At the end of zone
            accessor_->commit();
            ready_ = false;
            LOG_DEBUG(logger, DBG_TRACE_DETAILED,
                      DATASRC_DATABASE_ITERATE_END);
            return (ConstRRsetPtr());
        }
        const string name_str(name_), rtype_str(rtype_), ttl(ttl_);
        const Name name(name_str);
        const RRType rtype(rtype_str);
        RRsetPtr rrset(new RRset(name, class_, rtype, RRTTL(ttl)));
        while (data_ready_ && name_ == name_str && rtype_str == rtype_) {
            if (ttl_ != ttl) {
                if (ttl < ttl_) {
                    ttl_ = ttl;
                    rrset->setTTL(RRTTL(ttl));
                }
                LOG_WARN(logger, DATASRC_DATABASE_ITERATE_TTL_MISMATCH).
                    arg(name_).arg(class_).arg(rtype_).arg(rrset->getTTL());
            }
            rrset->addRdata(rdata::createRdata(rtype, class_, rdata_));
            getData();
            if (separate_rrs_) {
                break;
            }
        }
        LOG_DEBUG(logger, DBG_TRACE_DETAILED, DATASRC_DATABASE_ITERATE_NEXT).
            arg(rrset->getName()).arg(rrset->getType());
        return (rrset);
    }

private:
    // Load next row of data
    void getData() {
        string data[DatabaseAccessor::COLUMN_COUNT];
        data_ready_ = context_->getNext(data);
        name_ = data[DatabaseAccessor::NAME_COLUMN];
        rtype_ = data[DatabaseAccessor::TYPE_COLUMN];
        ttl_ = data[DatabaseAccessor::TTL_COLUMN];
        rdata_ = data[DatabaseAccessor::RDATA_COLUMN];
    }

    // The dedicated accessor
    boost::shared_ptr<DatabaseAccessor> accessor_;
    // The context
    DatabaseAccessor::IteratorContextPtr context_;
    // Class of the zone
    const RRClass class_;
    // SOA of the zone, if any (it should normally exist)
    ConstRRsetPtr soa_;
    // Status
    bool ready_, data_ready_;
    // Data of the next row
    string name_, rtype_, rdata_, ttl_;
    // Whether to modify differing TTL values, or treat a different TTL as
    // a different RRset
    bool separate_rrs_;
};

}

ZoneIteratorPtr
DatabaseClient::getIterator(const isc::dns::Name& name,
                            bool separate_rrs) const
{
    ZoneIteratorPtr iterator = ZoneIteratorPtr(new DatabaseIterator(
                                                   accessor_->clone(), name,
                                                   rrclass_, separate_rrs));
    LOG_DEBUG(logger, DBG_TRACE_DETAILED, DATASRC_DATABASE_ITERATE).
        arg(name);

    return (iterator);
}

//
// Zone updater using some database system as the underlying data source.
//
class DatabaseUpdater : public ZoneUpdater {
public:
    DatabaseUpdater(boost::shared_ptr<DatabaseAccessor> accessor, int zone_id,
            const Name& zone_name, const RRClass& zone_class,
            bool journaling) :
        committed_(false), accessor_(accessor), zone_id_(zone_id),
        db_name_(accessor->getDBName()), zone_name_(zone_name.toText()),
        zone_class_(zone_class), journaling_(journaling),
        diff_phase_(NOT_STARTED), serial_(0),
        finder_(new DatabaseClient::Finder(accessor_, zone_id_, zone_name))
    {
        logger.debug(DBG_TRACE_DATA, DATASRC_DATABASE_UPDATER_CREATED)
            .arg(zone_name_).arg(zone_class_).arg(db_name_);
    }

    virtual ~DatabaseUpdater() {
        if (!committed_) {
            try {
                accessor_->rollback();
                logger.info(DATASRC_DATABASE_UPDATER_ROLLBACK)
                    .arg(zone_name_).arg(zone_class_).arg(db_name_);
            } catch (const DataSourceError& e) {
                // We generally expect that rollback always succeeds, and
                // it should in fact succeed in a way we execute it.  But
                // as the public API allows rollback() to fail and
                // throw, we should expect it.  Obviously we cannot re-throw
                // it.  The best we can do is to log it as a critical error.
                logger.error(DATASRC_DATABASE_UPDATER_ROLLBACKFAIL)
                    .arg(zone_name_).arg(zone_class_).arg(db_name_)
                    .arg(e.what());
            }
        }

        logger.debug(DBG_TRACE_DATA, DATASRC_DATABASE_UPDATER_DESTROYED)
            .arg(zone_name_).arg(zone_class_).arg(db_name_);
    }

    virtual ZoneFinder& getFinder() { return (*finder_); }

    virtual void addRRset(const AbstractRRset& rrset);
    virtual void deleteRRset(const AbstractRRset& rrset);
    virtual void commit();

private:
    // A short cut typedef only for making the code shorter.
    typedef DatabaseAccessor Accessor;

    bool committed_;
    boost::shared_ptr<DatabaseAccessor> accessor_;
    const int zone_id_;
    const string db_name_;
    const string zone_name_;
    const RRClass zone_class_;
    const bool journaling_;
    // For the journals
    enum DiffPhase {
        NOT_STARTED,
        DELETE,
        ADD
    };
    DiffPhase diff_phase_;
    Serial serial_;
    boost::scoped_ptr<DatabaseClient::Finder> finder_;

    // This is a set of validation checks commonly used for addRRset() and
    // deleteRRset to minimize duplicate code logic and to make the main
    // code concise.
    void validateAddOrDelete(const char* const op_str,
                             const AbstractRRset& rrset,
                             DiffPhase prev_phase,
                             DiffPhase current_phase) const;
};

void
DatabaseUpdater::validateAddOrDelete(const char* const op_str,
                                     const AbstractRRset& rrset,
                                     DiffPhase prev_phase,
                                     DiffPhase current_phase) const
{
    if (committed_) {
        isc_throw(DataSourceError, op_str << " attempt after commit to zone: "
                  << zone_name_ << "/" << zone_class_);
    }
    if (rrset.getRdataCount() == 0) {
        isc_throw(DataSourceError, op_str << " attempt with an empty RRset: "
                  << rrset.getName() << "/" << zone_class_ << "/"
                  << rrset.getType());
    }
    if (rrset.getClass() != zone_class_) {
        isc_throw(DataSourceError, op_str << " attempt for a different class "
                  << zone_name_ << "/" << zone_class_ << ": "
                  << rrset.toText());
    }
    if (rrset.getRRsig()) {
        isc_throw(DataSourceError, op_str << " attempt for RRset with RRSIG "
                  << zone_name_ << "/" << zone_class_ << ": "
                  << rrset.toText());
    }
    if (journaling_) {
        const RRType rrtype(rrset.getType());
        if (rrtype == RRType::SOA() && diff_phase_ != prev_phase) {
            isc_throw(isc::BadValue, op_str << " attempt in an invalid "
                      << "diff phase: " << diff_phase_ << ", rrset: " <<
                      rrset.toText());
        }
        if (rrtype != RRType::SOA() && diff_phase_ != current_phase) {
            isc_throw(isc::BadValue, "diff state change by non SOA: "
                      << rrset.toText());
        }
    }
}

void
DatabaseUpdater::addRRset(const AbstractRRset& rrset) {
    validateAddOrDelete("add", rrset, DELETE, ADD);

    // It's guaranteed rrset has at least one RDATA at this point.
    RdataIteratorPtr it = rrset.getRdataIterator();

    string columns[Accessor::ADD_COLUMN_COUNT]; // initialized with ""
    columns[Accessor::ADD_NAME] = rrset.getName().toText();
    columns[Accessor::ADD_REV_NAME] = rrset.getName().reverse().toText();
    columns[Accessor::ADD_TTL] = rrset.getTTL().toText();
    columns[Accessor::ADD_TYPE] = rrset.getType().toText();
    string journal[Accessor::DIFF_PARAM_COUNT];
    if (journaling_) {
        journal[Accessor::DIFF_NAME] = columns[Accessor::ADD_NAME];
        journal[Accessor::DIFF_TYPE] = columns[Accessor::ADD_TYPE];
        journal[Accessor::DIFF_TTL] = columns[Accessor::ADD_TTL];
        diff_phase_ = ADD;
        if (rrset.getType() == RRType::SOA()) {
            serial_ =
                dynamic_cast<const generic::SOA&>(it->getCurrent()).
                getSerial();
        }
    }
    for (; !it->isLast(); it->next()) {
        if (rrset.getType() == RRType::RRSIG()) {
            // XXX: the current interface (based on the current sqlite3
            // data source schema) requires a separate "sigtype" column,
            // even though it won't be used in a newer implementation.
            // We should eventually clean up the schema design and simplify
            // the interface, but until then we have to conform to the schema.
            const generic::RRSIG& rrsig_rdata =
                dynamic_cast<const generic::RRSIG&>(it->getCurrent());
            columns[Accessor::ADD_SIGTYPE] =
                rrsig_rdata.typeCovered().toText();
        }
        columns[Accessor::ADD_RDATA] = it->getCurrent().toText();
        if (journaling_) {
            journal[Accessor::DIFF_RDATA] = columns[Accessor::ADD_RDATA];
            accessor_->addRecordDiff(zone_id_, serial_.getValue(),
                                     Accessor::DIFF_ADD, journal);
        }
        accessor_->addRecordToZone(columns);
    }
}

void
DatabaseUpdater::deleteRRset(const AbstractRRset& rrset) {
    // If this is the first operation, pretend we are starting a new delete
    // sequence after adds.  This will simplify the validation below.
    if (diff_phase_ == NOT_STARTED) {
        diff_phase_ = ADD;
    }

    validateAddOrDelete("delete", rrset, ADD, DELETE);

    RdataIteratorPtr it = rrset.getRdataIterator();

    string params[Accessor::DEL_PARAM_COUNT]; // initialized with ""
    params[Accessor::DEL_NAME] = rrset.getName().toText();
    params[Accessor::DEL_TYPE] = rrset.getType().toText();
    string journal[Accessor::DIFF_PARAM_COUNT];
    if (journaling_) {
        journal[Accessor::DIFF_NAME] = params[Accessor::DEL_NAME];
        journal[Accessor::DIFF_TYPE] = params[Accessor::DEL_TYPE];
        journal[Accessor::DIFF_TTL] = rrset.getTTL().toText();
        diff_phase_ = DELETE;
        if (rrset.getType() == RRType::SOA()) {
            serial_ =
                dynamic_cast<const generic::SOA&>(it->getCurrent()).
                getSerial();
        }
    }
    for (; !it->isLast(); it->next()) {
        params[Accessor::DEL_RDATA] = it->getCurrent().toText();
        if (journaling_) {
            journal[Accessor::DIFF_RDATA] = params[Accessor::DEL_RDATA];
            accessor_->addRecordDiff(zone_id_, serial_.getValue(),
                                     Accessor::DIFF_DELETE, journal);
        }
        accessor_->deleteRecordInZone(params);
    }
}

void
DatabaseUpdater::commit() {
    if (committed_) {
        isc_throw(DataSourceError, "Duplicate commit attempt for "
                  << zone_name_ << "/" << zone_class_ << " on "
                  << db_name_);
    }
    if (journaling_ && diff_phase_ == DELETE) {
        isc_throw(isc::BadValue, "Update sequence not complete");
    }
    accessor_->commit();
    committed_ = true; // make sure the destructor won't trigger rollback

    // We release the accessor immediately after commit is completed so that
    // we don't hold the possible internal resource any longer.
    accessor_.reset();

    logger.debug(DBG_TRACE_DATA, DATASRC_DATABASE_UPDATER_COMMIT)
        .arg(zone_name_).arg(zone_class_).arg(db_name_);
}

// The updater factory
ZoneUpdaterPtr
DatabaseClient::getUpdater(const isc::dns::Name& name, bool replace,
                           bool journaling) const
{
    if (replace && journaling) {
        isc_throw(isc::BadValue, "Can't store journal and replace the whole "
                  "zone at the same time");
    }
    boost::shared_ptr<DatabaseAccessor> update_accessor(accessor_->clone());
    const std::pair<bool, int> zone(update_accessor->startUpdateZone(
                                        name.toText(), replace));
    if (!zone.first) {
        return (ZoneUpdaterPtr());
    }

    return (ZoneUpdaterPtr(new DatabaseUpdater(update_accessor, zone.second,
                                               name, rrclass_, journaling)));
}

//
// Zone journal reader using some database system as the underlying data
//  source.
//
class DatabaseJournalReader : public ZoneJournalReader {
private:
    // A shortcut typedef to keep the code concise.
    typedef DatabaseAccessor Accessor;
public:
    DatabaseJournalReader(boost::shared_ptr<Accessor> accessor, const Name& zone,
                          int zone_id, const RRClass& rrclass, uint32_t begin,
                          uint32_t end) :
        accessor_(accessor), zone_(zone), rrclass_(rrclass),
        begin_(begin), end_(end), finished_(false)
    {
        context_ = accessor_->getDiffs(zone_id, begin, end);
    }
    virtual ~DatabaseJournalReader() {}
    virtual ConstRRsetPtr getNextDiff() {
        if (finished_) {
            isc_throw(InvalidOperation,
                      "Diff read attempt past the end of sequence on "
                      << accessor_->getDBName());
        }

        string data[Accessor::COLUMN_COUNT];
        if (!context_->getNext(data)) {
            finished_ = true;
            LOG_DEBUG(logger, DBG_TRACE_BASIC,
                      DATASRC_DATABASE_JOURNALREADER_END).
                arg(zone_).arg(rrclass_).arg(accessor_->getDBName()).
                arg(begin_).arg(end_);
            return (ConstRRsetPtr());
        }

        try {
            RRsetPtr rrset(new RRset(Name(data[Accessor::NAME_COLUMN]),
                                     rrclass_,
                                     RRType(data[Accessor::TYPE_COLUMN]),
                                     RRTTL(data[Accessor::TTL_COLUMN])));
            rrset->addRdata(rdata::createRdata(rrset->getType(), rrclass_,
                                               data[Accessor::RDATA_COLUMN]));
            LOG_DEBUG(logger, DBG_TRACE_DETAILED,
                      DATASRC_DATABASE_JOURNALREADER_NEXT).
                arg(rrset->getName()).arg(rrset->getType()).
                arg(zone_).arg(rrclass_).arg(accessor_->getDBName());
            return (rrset);
        } catch (const Exception& ex) {
            LOG_ERROR(logger, DATASRC_DATABASE_JOURNALREADR_BADDATA).
                arg(zone_).arg(rrclass_).arg(accessor_->getDBName()).
                arg(begin_).arg(end_).arg(ex.what());
            isc_throw(DataSourceError, "Failed to create RRset from diff on "
                      << accessor_->getDBName());
        }
    }

private:
    boost::shared_ptr<Accessor> accessor_;
    const Name zone_;
    const RRClass rrclass_;
    Accessor::IteratorContextPtr context_;
    const uint32_t begin_;
    const uint32_t end_;
    bool finished_;
};

// The JournalReader factory
pair<ZoneJournalReader::Result, ZoneJournalReaderPtr>
DatabaseClient::getJournalReader(const isc::dns::Name& zone,
                                 uint32_t begin_serial,
                                 uint32_t end_serial) const
{
    boost::shared_ptr<DatabaseAccessor> jnl_accessor(accessor_->clone());
    const pair<bool, int> zoneinfo(jnl_accessor->getZone(zone.toText()));
    if (!zoneinfo.first) {
        return (pair<ZoneJournalReader::Result, ZoneJournalReaderPtr>(
                    ZoneJournalReader::NO_SUCH_ZONE,
                    ZoneJournalReaderPtr()));
    }

    try {
        const pair<ZoneJournalReader::Result, ZoneJournalReaderPtr> ret(
            ZoneJournalReader::SUCCESS,
            ZoneJournalReaderPtr(new DatabaseJournalReader(jnl_accessor,
                                                           zone,
                                                           zoneinfo.second,
                                                           rrclass_,
                                                           begin_serial,
                                                           end_serial)));
        LOG_DEBUG(logger, DBG_TRACE_BASIC,
                  DATASRC_DATABASE_JOURNALREADER_START).arg(zone).arg(rrclass_).
            arg(jnl_accessor->getDBName()).arg(begin_serial).arg(end_serial);
        return (ret);
    } catch (const NoSuchSerial&) {
        return (pair<ZoneJournalReader::Result, ZoneJournalReaderPtr>(
                    ZoneJournalReader::NO_SUCH_VERSION,
                    ZoneJournalReaderPtr()));
    }
}
}
}
