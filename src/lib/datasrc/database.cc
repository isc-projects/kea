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
#include <dns/nsec3hash.h>

#include <datasrc/data_source.h>
#include <datasrc/logger.h>

#include <boost/foreach.hpp>
#include <boost/scoped_ptr.hpp>

using namespace isc::dns;
using namespace std;
using namespace isc::dns::rdata;
using boost::lexical_cast;
using boost::scoped_ptr;

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
                                  const string* construct_name, bool any,
                                  DatabaseAccessor::IteratorContextPtr context)
{
    RRsigStore sig_store;
    bool records_found = false;
    std::map<RRType, RRsetPtr> result;

    // Request the context in case we didn't get one
    if (!context) {
        context = accessor_->getRecords(name, zone_id_);
    }
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
    bool seen_other(false);

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
            } else if (cur_type != RRType::RRSIG() &&
                       cur_type != RRType::NSEC3() &&
                       cur_type != RRType::NSEC()) {
                // NSEC and RRSIG can coexist with anything, otherwise
                // we've seen something that can't live together with potential
                // CNAME.
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
    if (seen_cname && seen_other) {
        isc_throw(DataSourceError, "CNAME shares domain " << name <<
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
NSEC3_TYPES() {
    static bool initialized(false);
    static WantedTypes result;

    if (!initialized) {
        result.insert(RRType::NSEC3());
        initialized = true;
    }
    return (result);
}

const WantedTypes&
NSEC3PARAM_TYPES() {
    static bool initialized(false);
    static WantedTypes result;

    if (!initialized) {
        result.insert(RRType::NSEC3PARAM());
        initialized = true;
    }
    return (result);
}

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
                                             findInternal(name, type, NULL,
                                                          options))));
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
    // that indicate a delegation (.e. NS or DNAME).  Note that we only check
    // pure superdomains; delegation on an exact match will be detected later.
    for (int i = remove_labels; i > 0; --i) {
        const Name superdomain(name.split(i));

        // Look if there's NS or DNAME at this point of the tree, but ignore
        // the NS RRs at the apex of the zone.
        const FoundRRsets found = getRRsets(superdomain.toText(),
                                            DELEGATION_TYPES());
        if (found.first) {
            // This node contains either NS or DNAME RRs so it does exist.
            const FoundIterator nsi(found.second.find(RRType::NS()));
            const FoundIterator dni(found.second.find(RRType::DNAME()));

            // Note if this is the origin. (We don't count NS records at the
            // origin as a delegation so this controls whether NS RRs are
            // included in the results of some searches.)
            const bool not_origin = (i != remove_labels);

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
    const Name& name, const RRType& type, const FindOptions options,
    const DelegationSearchResult& dresult, vector<ConstRRsetPtr>* target,
    FindDNSSECContext& dnssec_ctx)
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
        const FoundRRsets found = getRRsets(wildcard, final_types,
                                            &construct_name,
                                            type == RRType::ANY());
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
                return (ResultContext(DELEGATION,
                                      stripRRsigs(dresult.first_ns, options)));
            } else if (!hasSubdomains(name.split(i - 1).toText())) {
                // The wildcard match is the best one, find the final result
                // at it.  Note that wildcard should never be the zone origin.
                return (findOnNameResult(name, type, options, false, found,
                                         &wildcard, target, dnssec_ctx));
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
            const FindResultFlags flags = (RESULT_WILDCARD |
                                           dnssec_ctx.getResultFlags());
            return (ResultContext(NXRRSET,
                                  dnssec_ctx.getDNSSECRRset(Name(wildcard),
                                                            true), flags));
        }
    }

    // Nothing found at any level.
    return (ResultContext(NXDOMAIN, ConstRRsetPtr()));
}

ZoneFinder::ResultContext
DatabaseClient::Finder::logAndCreateResult(
    const Name& name, const string* wildname, const RRType& type,
    ZoneFinder::Result code, ConstRRsetPtr rrset, const FindOptions options,
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
    return (ResultContext(code, stripRRsigs(rrset, options), flags));
}

DatabaseClient::Finder::FindDNSSECContext::FindDNSSECContext(
    DatabaseClient::Finder& finder,
    const FindOptions options) :
    finder_(finder),
    need_dnssec_((options & FIND_DNSSEC) != 0),
    is_nsec3_(false),
    is_nsec_(false),
    probed_(false)
{}

void
DatabaseClient::Finder::FindDNSSECContext::probe() {
    if (!probed_) {
        probed_ = true;
        if (need_dnssec_) {
            // If an NSEC3PARAM RR exists at the zone apex, it's quite likely
            // that the zone is signed with NSEC3.  (If not the zone is more
            // or less broken, but it's caller's responsibility how to handle
            // such cases).
            const string origin = finder_.getOrigin().toText();
            const FoundRRsets nsec3_found =
                finder_.getRRsets(origin, NSEC3PARAM_TYPES());
            const FoundIterator nfi=
                nsec3_found.second.find(RRType::NSEC3PARAM());
            is_nsec3_ = (nfi != nsec3_found.second.end());

            // Likewise for NSEC, depending on the apex has an NSEC RR.
            // If we know the zone is NSEC3-signed, however, we don't bother
            // to check that.  This is aligned with the transition guideline
            // described in Section 10.4 of RFC 5155.
            if (!is_nsec3_) {
                const FoundRRsets nsec_found =
                    finder_.getRRsets(origin, NSEC_TYPES());
                const FoundIterator nfi =
                    nsec_found.second.find(RRType::NSEC());
                is_nsec_ = (nfi != nsec_found.second.end());
            }
        }
    }
}

bool
DatabaseClient::Finder::FindDNSSECContext::isNSEC3() {
    if (!probed_) {
        probe();
    }
    return (is_nsec3_);
}

bool
DatabaseClient::Finder::FindDNSSECContext::isNSEC() {
    if (!probed_) {
        probe();
    }
    return (is_nsec_);
}

isc::dns::ConstRRsetPtr
DatabaseClient::Finder::FindDNSSECContext::getDNSSECRRset(
    const FoundRRsets& found_set)
{
    if (!isNSEC()) {
        return (ConstRRsetPtr());
    }

    const FoundIterator nci = found_set.second.find(RRType::NSEC());
    if (nci != found_set.second.end()) {
        return (nci->second);
    } else {
        return (ConstRRsetPtr());
    }
}

isc::dns::ConstRRsetPtr
DatabaseClient::Finder::FindDNSSECContext::getDNSSECRRset(const Name &name,
                                                          bool covering)
{
    if (!isNSEC()) {
        return (ConstRRsetPtr());
    }

    try {
        const Name& nsec_name =
            covering ? finder_.findPreviousName(name) : name;
        const FoundRRsets found = finder_.getRRsets(nsec_name.toText(),
                                                    NSEC_TYPES());
        const FoundIterator nci = found.second.find(RRType::NSEC());
        if (nci != found.second.end()) {
            return (nci->second);
        }
    } catch (const isc::NotImplemented&) {
        // This happens when the underlying database accessor doesn't support
        // findPreviousName() (it probably doesn't support DNSSEC at all) but
        // there is somehow an NSEC RR at the zone apex.  We log the fact but
        // otherwise let the caller decide what to do (so, for example, a
        // higher level query processing won't completely fail but can return
        // anything it can get).
        LOG_INFO(logger, DATASRC_DATABASE_COVER_NSEC_UNSUPPORTED).
            arg(finder_.accessor_->getDBName()).arg(name);
    }
    return (ConstRRsetPtr());
}

ZoneFinder::FindResultFlags
DatabaseClient::Finder::FindDNSSECContext::getResultFlags() {
    if (isNSEC3()) {
        return (RESULT_NSEC3_SIGNED);
    } else if (isNSEC()) {
        return (RESULT_NSEC_SIGNED);
    }
    return (RESULT_DEFAULT);
}

ZoneFinder::ResultContext
DatabaseClient::Finder::findOnNameResult(const Name& name,
                                         const RRType& type,
                                         const FindOptions options,
                                         const bool is_origin,
                                         const FoundRRsets& found,
                                         const string* wildname,
                                         std::vector<isc::dns::ConstRRsetPtr>*
                                         target, FindDNSSECContext& dnssec_ctx)
{
    const bool wild = (wildname != NULL);
    // For wildcard case with DNSSEC required, the caller would need to
    // know whether it's NSEC or NSEC3 signed.  getResultFlags returns
    // appropriate flag based on the query context and zone status.
    const FindResultFlags flags =
        wild ? (RESULT_WILDCARD | dnssec_ctx.getResultFlags()) : RESULT_DEFAULT;

    // Get iterators for the different types of records we are interested in -
    // CNAME, NS and Wanted types.
    const FoundIterator nsi(found.second.find(RRType::NS()));
    const FoundIterator cni(found.second.find(RRType::CNAME()));
    const FoundIterator wti(found.second.find(type));

    if (!is_origin && (options & FIND_GLUE_OK) == 0 && type != RRType::DS() &&
        nsi != found.second.end()) {
        // A NS RRset was found at the domain we were searching for.  As it is
        // not at the origin of the zone, it is a delegation and indicates that
        // this zone is not authoritative for the data. Just return the
        // delegation information, except:
        // - when we are looking for glue records (FIND_GLUE_OK), or
        // - when the query type is DS (which cancels the delegation)
        return (logAndCreateResult(name, wildname, type, DELEGATION,
                                   nsi->second, options,
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
        return (logAndCreateResult(name, wildname, type, CNAME,
                                   cni->second, options,
                                   wild ? DATASRC_DATABASE_WILDCARD_CNAME :
                                   DATASRC_DATABASE_FOUND_CNAME,
                                   flags));
    } else if (wti != found.second.end()) {
        bool any(type == RRType::ANY());
        if (any) {
            // An ANY query, copy everything to the target instead of returning
            // directly.
            for (FoundIterator it(found.second.begin());
                 it != found.second.end(); ++it) {
                if (it->second) {
                    // Skip over the empty ANY
                    target->push_back(stripRRsigs(it->second, options));
                }
            }
            if (wild) {
                LOG_DEBUG(logger, DBG_TRACE_DETAILED,
                          DATASRC_DATABASE_WILDCARD_ANY).
                    arg(accessor_->getDBName()).arg(name);
            } else {
                LOG_DEBUG(logger, DBG_TRACE_DETAILED,
                          DATASRC_DATABASE_FOUND_ANY).
                    arg(accessor_->getDBName()).arg(name);
            }
        } else {
            if (wild) {
                LOG_DEBUG(logger, DBG_TRACE_DETAILED,
                          DATASRC_DATABASE_WILDCARD_MATCH).
                    arg(accessor_->getDBName()).arg(*wildname).
                    arg(wti->second);
            } else {
                LOG_DEBUG(logger, DBG_TRACE_DETAILED,
                          DATASRC_DATABASE_FOUND_RRSET).
                    arg(accessor_->getDBName()).arg(wti->second);
            }
        }
        // Found an RR matching the query, so return it.  (Note that this
        // includes the case where we were explicitly querying for a CNAME and
        // found it.  It also includes the case where we were querying for an
        // NS RRset and found it at the apex of the zone.)
        return (ResultContext(SUCCESS, stripRRsigs(wti->second, options),
                              flags));
    }

    // If we get here, we have found something at the requested name but not
    // one of the RR types we were interested in. This is the NXRRSET case so
    // return the appropriate status.  If DNSSEC information was requested,
    // provide the NSEC records.  If it's for wildcard, we need to get the
    // NSEC records in the name of the wildcard, not the substituted one,
    // so we need to search the tree again.
    const ConstRRsetPtr dnssec_rrset =
        wild ? dnssec_ctx.getDNSSECRRset(Name(*wildname), false) :
        dnssec_ctx.getDNSSECRRset(found);
    if (dnssec_rrset) {
        // This log message covers both normal and wildcard cases, so we pass
        // NULL for 'wildname'.
        return (logAndCreateResult(name, NULL, type, NXRRSET,
                                   dnssec_rrset, options,
                                   DATASRC_DATABASE_FOUND_NXRRSET_NSEC,
                                   flags | RESULT_NSEC_SIGNED));
    }
    return (logAndCreateResult(name, wildname, type, NXRRSET,
                               dnssec_rrset, options,
                               wild ? DATASRC_DATABASE_WILDCARD_NXRRSET :
                               DATASRC_DATABASE_FOUND_NXRRSET,
                               flags | dnssec_ctx.getResultFlags()));
}

ZoneFinder::ResultContext
DatabaseClient::Finder::findNoNameResult(const Name& name, const RRType& type,
                                         FindOptions options,
                                         const DelegationSearchResult& dresult,
                                         std::vector<isc::dns::ConstRRsetPtr>*
                                         target, FindDNSSECContext& dnssec_ctx)
{
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
        return (ResultContext(NXRRSET, dnssec_ctx.getDNSSECRRset(name, true),
                              dnssec_ctx.getResultFlags()));
    } else if ((options & NO_WILDCARD) == 0) {
        // It's not an empty non-terminal and wildcard matching is not
        // disabled, so check for wildcards. If there is a wildcard match
        // (i.e. all results except NXDOMAIN) return it; otherwise fall
        // through to the NXDOMAIN case below.
        const ResultContext wcontext =
            findWildcardMatch(name, type, options, dresult, target,
                              dnssec_ctx);
        if (wcontext.code != NXDOMAIN) {
            return (wcontext);
        }
    }

    // All avenues to find a match are now exhausted, return NXDOMAIN (plus
    // NSEC records if requested).
    LOG_DEBUG(logger, DBG_TRACE_DETAILED, DATASRC_DATABASE_NO_MATCH).
              arg(accessor_->getDBName()).arg(name).arg(type).arg(getClass());
    return (ResultContext(NXDOMAIN, dnssec_ctx.getDNSSECRRset(name, true),
                          dnssec_ctx.getResultFlags()));
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
        isc_throw(OutOfZone, name.toText() << " not in " << getOrigin());
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
        return (ResultContext(dresult.code,
                              stripRRsigs(dresult.rrset, options)));
    }

    // If there is no delegation, look for the exact match to the request
    // name/type/class.  However, there are special cases:
    // - Requested name has a singleton CNAME record associated with it
    // - Requested name is a delegation point (NS only but not at the zone
    //   apex - DNAME is ignored here as it redirects DNS names subordinate to
    //   the owner name - the owner name itself is not redirected.)
    WantedTypes final_types(FINAL_TYPES());
    final_types.insert(type);
    const FoundRRsets found = getRRsets(name.toText(), final_types,
                                        NULL, type == RRType::ANY());
    FindDNSSECContext dnssec_ctx(*this, options);
    if (found.first) {
        // Something found at the domain name.  Look into it further to get
        // the final result.
        const bool is_origin = (name == getOrigin());
        return (findOnNameResult(name, type, options, is_origin, found, NULL,
                                 target, dnssec_ctx));
    } else {
        // Did not find anything at all at the domain name, so check for
        // subdomains or wildcards.
        return (findNoNameResult(name, type, options, dresult, target,
                                 dnssec_ctx));
    }
}

// The behaviour is inspired by the one in the in-memory implementation.
ZoneFinder::FindNSEC3Result
DatabaseClient::Finder::findNSEC3(const Name& name, bool recursive) {
    LOG_DEBUG(logger, DBG_TRACE_BASIC, DATASRC_DATABASE_FINDNSEC3).arg(name).
        arg(recursive ? "recursive" : "non-recursive");

    // First, validate the input
    const NameComparisonResult cmp_result(name.compare(getOrigin()));
    if (cmp_result.getRelation() != NameComparisonResult::EQUAL &&
        cmp_result.getRelation() != NameComparisonResult::SUBDOMAIN) {
        isc_throw(OutOfZone, "findNSEC3 attempt for out-of-zone name: " <<
                  name << ", zone: " << getOrigin() << "/" << getClass());
    }

    // Now, we need to get the NSEC3 params from the apex and create the hash
    // creator for it.
    const FoundRRsets nsec3param(getRRsets(getOrigin().toText(),
                                           NSEC3PARAM_TYPES()));
    const FoundIterator param(nsec3param.second.find(RRType::NSEC3PARAM()));
    if (!nsec3param.first || param == nsec3param.second.end()) {
        // No NSEC3 params? :-(
        isc_throw(DataSourceError, "findNSEC3 attempt for non NSEC3 signed " <<
                  "zone: " << getOrigin() << "/" << getClass());
    }
    // This takes the RRset received from the find method, takes the first RR
    // in it, casts it to NSEC3PARAM (as it should be that one) and then creates
    // the hash calculator class from it.
    const scoped_ptr<NSEC3Hash> calculator(NSEC3Hash::create(
        dynamic_cast<const generic::NSEC3PARAM&>(
            param->second->getRdataIterator()->getCurrent())));

    // Few shortcut variables
    const unsigned olabels(getOrigin().getLabelCount());
    const unsigned qlabels(name.getLabelCount());
    const string otext(getOrigin().toText());

    // This will be set to the one covering the query name
    ConstRRsetPtr covering_proof;

    // We keep stripping the leftmost label until we find something.
    // In case it is recursive, we'll exit the loop at the first iteration.
    for (unsigned labels(qlabels); labels >= olabels; -- labels) {
        const string hash(calculator->calculate(labels == qlabels ? name :
                                                name.split(qlabels - labels,
                                                           labels)));
        // Get the exact match for the name.
        LOG_DEBUG(logger, DBG_TRACE_BASIC, DATASRC_DATABASE_FINDNSEC3_TRYHASH).
            arg(name).arg(labels).arg(hash);

        DatabaseAccessor::IteratorContextPtr
            context(accessor_->getNSEC3Records(hash, zone_id_));

        if (!context) {
            isc_throw(Unexpected, "Iterator context null for hash " + hash);
        }

        const FoundRRsets nsec3(getRRsets(hash + "." + otext, NSEC3_TYPES(),
                                          NULL, false, context));

        if (nsec3.first) {
            // We found an exact match against the current label.
            const FoundIterator it(nsec3.second.find(RRType::NSEC3()));
            if (it == nsec3.second.end()) {
                isc_throw(DataSourceError, "Hash " + hash +
                          "exists, but no NSEC3 there");
            }

            LOG_DEBUG(logger, DBG_TRACE_BASIC,
                      DATASRC_DATABASE_FINDNSEC3_MATCH).arg(name).arg(labels).
                arg(*it->second);
            // Yes, we win
            return (FindNSEC3Result(true, labels, it->second, covering_proof));
        } else {
            // There's no exact match. We try a previous one. We must find it
            // (if the zone is properly signed).
            const string prevHash(accessor_->findPreviousNSEC3Hash(zone_id_,
                                                                   hash));
            LOG_DEBUG(logger, DBG_TRACE_BASIC,
                      DATASRC_DATABASE_FINDNSEC3_TRYHASH_PREV).arg(name).
                arg(labels).arg(prevHash);
            context = accessor_->getNSEC3Records(prevHash, zone_id_);
            const FoundRRsets prev_nsec3(getRRsets(prevHash + "." + otext,
                                                   NSEC3_TYPES(), NULL, false,
                                                   context));

            if (!prev_nsec3.first) {
                isc_throw(DataSourceError, "Hash " + prevHash + " returned "
                          "from findPreviousNSEC3Hash, but it is empty");
            }
            const FoundIterator
                prev_it(prev_nsec3.second.find(RRType::NSEC3()));
            if (prev_it == prev_nsec3.second.end()) {
                isc_throw(DataSourceError, "The previous hash " + prevHash +
                          "exists, but does not contain the NSEC3");
            }

            covering_proof = prev_it->second;
            // In case it is recursive, we try to get an exact match a level
            // up. If it is not recursive, the caller is ok with a covering
            // one, so we just return it.
            if (!recursive) {
                LOG_DEBUG(logger, DBG_TRACE_BASIC,
                          DATASRC_DATABASE_FINDNSEC3_COVER).arg(name).
                    arg(labels).arg(*covering_proof);
                return (FindNSEC3Result(false, labels, covering_proof,
                                        ConstRRsetPtr()));
            }
        }
    }

    // The zone must contain at least the apex and that one should match
    // exactly. If that doesn't happen, we have a problem.
    isc_throw(DataSourceError, "recursive findNSEC3 mode didn't stop, likely a "
              "broken NSEC3 zone: " << otext << "/" << getClass());
}

Name
DatabaseClient::Finder::findPreviousName(const Name& name) const {
    const string str(accessor_->findPreviousName(zone_id_,
                                                 name.reverse().toText()));
    try {
        return (Name(str));
    } catch (const isc::dns::NameParserException&) {
        isc_throw(DataSourceError, "Bad name " + str +
                  " from findPreviousName");
    }
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
            LOG_DEBUG(logger, DBG_TRACE_DETAILED, DATASRC_DATABASE_ITERATE_END);
            return (ConstRRsetPtr());
        }
        const RRType rtype(rtype_txt_);
        RRsetPtr rrset(new RRset(Name(name_txt_), class_, rtype,
                                 RRTTL(ttl_txt_)));
        // Remember the first RDATA of the RRset for comparison:
        const ConstRdataPtr rdata_base = rdata_;
        while (true) {
            // Extend the RRset with the new RDATA.
            rrset->addRdata(rdata_);

            // Retrieve the next record from the database.  If we reach the
            // end of the zone, done; if we were requested to separate all RRs,
            // just remember this record and return the single RR.
            getData();
            if (separate_rrs_ || !data_ready_) {
                break;
            }

            // Check if the next record belongs to the same RRset.  If not,
            // we are done.  The next RDATA has been stored in rdata_, which
            // is used within this loop (if it belongs to the same RRset) or
            // in the next call.
            if (Name(name_txt_) != rrset->getName() ||
                !isSameType(rtype, rdata_base, RRType(rtype_txt_), rdata_)) {
                break;
            }

            // Adjust TTL if necessary
            const RRTTL next_ttl(ttl_txt_);
            if (next_ttl != rrset->getTTL()) {
                if (next_ttl < rrset->getTTL()) {
                    rrset->setTTL(next_ttl);
                }
                LOG_WARN(logger, DATASRC_DATABASE_ITERATE_TTL_MISMATCH).
                    arg(name_txt_).arg(class_).arg(rtype).arg(rrset->getTTL());
            }
        }
        LOG_DEBUG(logger, DBG_TRACE_DETAILED, DATASRC_DATABASE_ITERATE_NEXT).
            arg(rrset->getName()).arg(rrset->getType());
        return (rrset);
    }

private:
    // Check two RDATA types are equivalent.  Basically it's a trivial
    // comparison, but if both are of RRSIG, we should also compare the types
    // covered.
    static bool isSameType(RRType type1, ConstRdataPtr rdata1,
                           RRType type2, ConstRdataPtr rdata2)
    {
        if (type1 != type2) {
            return (false);
        }
        if (type1 == RRType::RRSIG()) {
            return (dynamic_cast<const generic::RRSIG&>(*rdata1).typeCovered()
                    == dynamic_cast<const generic::RRSIG&>(*rdata2).
                    typeCovered());
        }
        return (true);
    }

    // Load next row of data
    void getData() {
        string data[DatabaseAccessor::COLUMN_COUNT];
        data_ready_ = context_->getNext(data);
        if (data_ready_) {
            name_txt_ = data[DatabaseAccessor::NAME_COLUMN];
            rtype_txt_ = data[DatabaseAccessor::TYPE_COLUMN];
            ttl_txt_ = data[DatabaseAccessor::TTL_COLUMN];
            rdata_ = rdata::createRdata(RRType(rtype_txt_), class_,
                                        data[DatabaseAccessor::RDATA_COLUMN]);
        }
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
    string name_txt_, rtype_txt_, ttl_txt_;
    // RDATA of the next row
    ConstRdataPtr rdata_;
    // Whether to modify differing TTL values, or treat a different TTL as
    // a different RRset
    const bool separate_rrs_;
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

// This is a helper class used in adding/deleting RRsets to/from a database.
// The purpose of this class is to provide conversion interface from various
// parameters of the RRset to corresponding textual representations that the
// underlying database interface expects.  The necessary parameters and how
// to convert them depend on several things, such as whether it's NSEC3 related
// or not, or whether journaling is requested.  In order to avoid unnecessary
// conversion, this class also performs the conversion in a lazy manner.
// Also, in order to avoid redundant conversion when the conversion is
// requested for the same parameter multiple times, it remembers the
// conversion result first time, and reuses it for subsequent requests
// (this implicitly assumes copying std::string objects is not very expensive;
// this is often the case in some common implementations that have
// copy-on-write semantics for the string class).
class RRParameterConverter {
public:
    RRParameterConverter(const AbstractRRset& rrset) : rrset_(rrset)
    {}
    const string& getName() {
        if (name_.empty()) {
            name_ = rrset_.getName().toText();
        }
        return (name_);
    }
    const string& getNSEC3Name() {
        if (nsec3_name_.empty()) {
            nsec3_name_ = rrset_.getName().split(0, 1).toText(true);
        }
        return (nsec3_name_);
    }
    const string& getRevName() {
        if (revname_.empty()) {
            revname_ = rrset_.getName().reverse().toText();
        }
        return (revname_);
    }
    const string& getTTL() {
        if (ttl_.empty()) {
            ttl_ = rrset_.getTTL().toText();
        }
        return (ttl_);
    }
    const string& getType() {
        if (type_.empty()) {
            type_ = rrset_.getType().toText();
        }
        return (type_);
    }

private:
    string name_;
    string nsec3_name_;
    string revname_;
    string ttl_;
    string type_;
    const AbstractRRset& rrset_;
};

namespace {
// A shared shortcut to detect if the given type of RDATA is NSEC3 or
// RRSIG covering NSEC3.  RRSIG for NSEC3 should go to the (conceptual)
// separate namespace, so we need to check the covered type.
// Note: in principle the type covered should be the same for
// all RDATA, but the RRset interface doesn't ensure that condition.
// So we explicitly check that for every RDATA below.
bool
isNSEC3KindType(RRType rrtype, const Rdata& rdata) {
    if (rrtype == RRType::NSEC3()) {
        return (true);
    }
    if (rrtype == RRType::RRSIG() &&
        dynamic_cast<const generic::RRSIG&>(rdata).typeCovered() ==
        RRType::NSEC3())
    {
        return (true);
    }
    return (false);
}
}

void
DatabaseUpdater::addRRset(const AbstractRRset& rrset) {
    validateAddOrDelete("add", rrset, DELETE, ADD);

    // It's guaranteed rrset has at least one RDATA at this point.
    RdataIteratorPtr it = rrset.getRdataIterator();
    if (journaling_) {
        diff_phase_ = ADD;
        if (rrset.getType() == RRType::SOA()) {
            serial_ = dynamic_cast<const generic::SOA&>(it->getCurrent()).
                getSerial();
        }
    }

    RRParameterConverter cvtr(rrset);
    for (; !it->isLast(); it->next()) {
        const Rdata& rdata = it->getCurrent();
        const bool nsec3_type = isNSEC3KindType(rrset.getType(), rdata);

        string sigtype;
        if (rrset.getType() == RRType::RRSIG()) {
            // XXX: the current interface (based on the current sqlite3
            // data source schema) requires a separate "sigtype" column,
            // even though it won't be used in a newer implementation.
            // We should eventually clean up the schema design and simplify
            // the interface, but until then we have to conform to the schema.
            sigtype = dynamic_cast<const generic::RRSIG&>(rdata).
                typeCovered().toText();
        }
        const string& rdata_txt = rdata.toText();
        if (journaling_) {
            const string journal[Accessor::DIFF_PARAM_COUNT] =
                { cvtr.getName(), cvtr.getType(), cvtr.getTTL(), rdata_txt };
            accessor_->addRecordDiff(zone_id_, serial_.getValue(),
                                     Accessor::DIFF_ADD, journal);
        }
        if (nsec3_type) {
            const string nsec3_columns[Accessor::ADD_NSEC3_COLUMN_COUNT] =
                { cvtr.getNSEC3Name(), cvtr.getTTL(), cvtr.getType(),
                  rdata_txt };
            accessor_->addNSEC3RecordToZone(nsec3_columns);
        } else {
            const string columns[Accessor::ADD_COLUMN_COUNT] =
                { cvtr.getName(), cvtr.getRevName(), cvtr.getTTL(),
                  cvtr.getType(), sigtype, rdata_txt };
            accessor_->addRecordToZone(columns);
        }
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
    if (journaling_) {
        diff_phase_ = DELETE;
        if (rrset.getType() == RRType::SOA()) {
            serial_ =
                dynamic_cast<const generic::SOA&>(it->getCurrent()).
                getSerial();
        }
    }

    RRParameterConverter cvtr(rrset);
    for (; !it->isLast(); it->next()) {
        const Rdata& rdata = it->getCurrent();
        const bool nsec3_type = isNSEC3KindType(rrset.getType(), rdata);
        const string& rdata_txt = it->getCurrent().toText();

        if (journaling_) {
            const string journal[Accessor::DIFF_PARAM_COUNT] =
                { cvtr.getName(), cvtr.getType(), cvtr.getTTL(), rdata_txt };
            accessor_->addRecordDiff(zone_id_, serial_.getValue(),
                                     Accessor::DIFF_DELETE, journal);
        }
        const string params[Accessor::DEL_PARAM_COUNT] =
            { nsec3_type ? cvtr.getNSEC3Name() : cvtr.getName(),
              cvtr.getType(), rdata_txt };
        if (nsec3_type) {
            accessor_->deleteNSEC3RecordInZone(params);
        } else {
            accessor_->deleteRecordInZone(params);
        }
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
