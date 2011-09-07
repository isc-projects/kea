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
using boost::shared_ptr;
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

std::pair<bool, isc::dns::RRsetPtr>
DatabaseClient::Finder::getRRset(const isc::dns::Name& name,
                                 const isc::dns::RRType* type,
                                 bool want_cname, bool want_dname,
                                 bool want_ns,
                                 const isc::dns::Name* construct_name)
{
    RRsigStore sig_store;
    bool records_found = false;
    isc::dns::RRsetPtr result_rrset;

    // Request the context
    DatabaseAccessor::IteratorContextPtr
        context(accessor_->getRecords(name.toText(), zone_id_));
    // It must not return NULL, that's a bug of the implementation
    if (!context) {
        isc_throw(isc::Unexpected, "Iterator context null at " +
                  name.toText());
    }

    std::string columns[DatabaseAccessor::COLUMN_COUNT];
    if (construct_name == NULL) {
        construct_name = &name;
    }
    while (context->getNext(columns)) {
        if (!records_found) {
            records_found = true;
        }

        try {
            const isc::dns::RRType cur_type(columns[DatabaseAccessor::
                                            TYPE_COLUMN]);
            const isc::dns::RRTTL cur_ttl(columns[DatabaseAccessor::
                                          TTL_COLUMN]);
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

            // Check for delegations before checking for the right type.
            // This is needed to properly delegate request for the NS
            // record itself.
            //
            // This happens with NS only, CNAME must be alone and DNAME
            // is not checked in the exact queried domain.
            if (want_ns && cur_type == isc::dns::RRType::NS()) {
                if (result_rrset &&
                    result_rrset->getType() != isc::dns::RRType::NS()) {
                    isc_throw(DataSourceError, "NS found together with data"
                              " in non-apex domain " + name.toText());
                }
                addOrCreate(result_rrset, *construct_name, getClass(),
                            cur_type, cur_ttl,
                            columns[DatabaseAccessor::RDATA_COLUMN],
                            *accessor_);
            } else if (type != NULL && cur_type == *type) {
                if (result_rrset &&
                    result_rrset->getType() == isc::dns::RRType::CNAME()) {
                    isc_throw(DataSourceError, "CNAME found but it is not "
                              "the only record for " + name.toText());
                } else if (result_rrset && want_ns &&
                           result_rrset->getType() == isc::dns::RRType::NS()) {
                    isc_throw(DataSourceError, "NS found together with data"
                              " in non-apex domain " + name.toText());
                }
                addOrCreate(result_rrset, *construct_name, getClass(),
                            cur_type, cur_ttl,
                            columns[DatabaseAccessor::RDATA_COLUMN],
                            *accessor_);
            } else if (want_cname && cur_type == isc::dns::RRType::CNAME()) {
                // There should be no other data, so result_rrset should
                // be empty.
                if (result_rrset) {
                    isc_throw(DataSourceError, "CNAME found but it is not "
                              "the only record for " + name.toText());
                }
                addOrCreate(result_rrset, *construct_name, getClass(),
                            cur_type, cur_ttl,
                            columns[DatabaseAccessor::RDATA_COLUMN],
                            *accessor_);
            } else if (want_dname && cur_type == isc::dns::RRType::DNAME()) {
                // There should be max one RR of DNAME present
                if (result_rrset &&
                    result_rrset->getType() == isc::dns::RRType::DNAME()) {
                    isc_throw(DataSourceError, "DNAME with multiple RRs in " +
                              name.toText());
                }
                addOrCreate(result_rrset, *construct_name, getClass(),
                            cur_type, cur_ttl,
                            columns[DatabaseAccessor::RDATA_COLUMN],
                            *accessor_);
            } else if (cur_type == isc::dns::RRType::RRSIG()) {
                // If we get signatures before we get the actual data, we
                // can't know which ones to keep and which to drop...
                // So we keep a separate store of any signature that may be
                // relevant and add them to the final RRset when we are
                // done.
                // A possible optimization here is to not store them for
                // types we are certain we don't need
                sig_store.addSig(isc::dns::rdata::createRdata(cur_type,
                    getClass(), columns[DatabaseAccessor::RDATA_COLUMN]));
            }
        } catch (const isc::dns::InvalidRRType& irt) {
            isc_throw(DataSourceError, "Invalid RRType in database for " <<
                      name << ": " << columns[DatabaseAccessor::
                      TYPE_COLUMN]);
        } catch (const isc::dns::InvalidRRTTL& irttl) {
            isc_throw(DataSourceError, "Invalid TTL in database for " <<
                      name << ": " << columns[DatabaseAccessor::
                      TTL_COLUMN]);
        } catch (const isc::dns::rdata::InvalidRdataText& ird) {
            isc_throw(DataSourceError, "Invalid rdata in database for " <<
                      name << ": " << columns[DatabaseAccessor::
                      RDATA_COLUMN]);
        }
    }
    if (result_rrset) {
        sig_store.appendSignatures(result_rrset);
    }
    return (std::pair<bool, isc::dns::RRsetPtr>(records_found, result_rrset));
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

ZoneFinder::FindResult
DatabaseClient::Finder::find(const isc::dns::Name& name,
                             const isc::dns::RRType& type,
                             isc::dns::RRsetList*,
                             const FindOptions options)
{
    // This variable is used to determine the difference between
    // NXDOMAIN and NXRRSET
    bool records_found = false;
    bool glue_ok(options & FIND_GLUE_OK);
    isc::dns::RRsetPtr result_rrset;
    ZoneFinder::Result result_status = SUCCESS;
    std::pair<bool, isc::dns::RRsetPtr> found;
    logger.debug(DBG_TRACE_DETAILED, DATASRC_DATABASE_FIND_RECORDS)
        .arg(accessor_->getDBName()).arg(name).arg(type);
    // In case we are in GLUE_OK mode and start matching wildcards,
    // we can't do it under NS, so we store it here to check
    isc::dns::RRsetPtr first_ns;

    // First, do we have any kind of delegation (NS/DNAME) here?
    Name origin(getOrigin());
    size_t origin_label_count(origin.getLabelCount());
    // Number of labels in the last known non-empty domain
    size_t last_known(origin_label_count);
    size_t current_label_count(name.getLabelCount());
    // This is how many labels we remove to get origin
    size_t remove_labels(current_label_count - origin_label_count);

    // Now go trough all superdomains from origin down
    for (int i(remove_labels); i > 0; --i) {
        Name superdomain(name.split(i));
        // Look if there's NS or DNAME (but ignore the NS in origin)
        found = getRRset(superdomain, NULL, false, true,
                         i != remove_labels && !glue_ok);
        if (found.first) {
            // It contains some RRs, so it exists.
            last_known = superdomain.getLabelCount();
            // In case we are in GLUE_OK, we want to store the highest
            // encountered RRset.
            if (glue_ok && !first_ns && i != remove_labels) {
                first_ns = getRRset(superdomain, NULL, false, false,
                                    true).second;
            }
        }
        if (found.second) {
            // We found something redirecting somewhere else
            // (it can be only NS or DNAME here)
            result_rrset = found.second;
            if (result_rrset->getType() == isc::dns::RRType::NS()) {
                LOG_DEBUG(logger, DBG_TRACE_DETAILED,
                          DATASRC_DATABASE_FOUND_DELEGATION).
                    arg(accessor_->getDBName()).arg(superdomain);
                result_status = DELEGATION;
            } else {
                LOG_DEBUG(logger, DBG_TRACE_DETAILED,
                          DATASRC_DATABASE_FOUND_DNAME).
                    arg(accessor_->getDBName()).arg(superdomain);
                result_status = DNAME;
            }
            // Don't search more
            break;
        }
    }

    if (!result_rrset) { // Only if we didn't find a redirect already
        // Try getting the final result and extract it
        // It is special if there's a CNAME or NS, DNAME is ignored here
        // And we don't consider the NS in origin
        found = getRRset(name, &type, true, false, name != origin && !glue_ok);
        records_found = found.first;
        result_rrset = found.second;
        if (result_rrset && name != origin && !glue_ok &&
            result_rrset->getType() == isc::dns::RRType::NS()) {
            LOG_DEBUG(logger, DBG_TRACE_DETAILED,
                      DATASRC_DATABASE_FOUND_DELEGATION_EXACT).
                arg(accessor_->getDBName()).arg(name);
            result_status = DELEGATION;
        } else if (result_rrset && type != isc::dns::RRType::CNAME() &&
                   result_rrset->getType() == isc::dns::RRType::CNAME()) {
            result_status = CNAME;
        }

        if (!result_rrset && !records_found) {
            // Nothing lives here.
            // But check if something lives below this
            // domain and if so, pretend something is here as well.
            if (hasSubdomains(name.toText())) {
                LOG_DEBUG(logger, DBG_TRACE_DETAILED,
                          DATASRC_DATABASE_FOUND_EMPTY_NONTERMINAL).
                    arg(accessor_->getDBName()).arg(name);
                records_found = true;
            } else {
                // It's not empty non-terminal. So check for wildcards.
                // We remove labels one by one and look for the wildcard there.
                // Go up to first non-empty domain.

                remove_labels = current_label_count - last_known;
                Name star("*");
                for (size_t i(1); i <= remove_labels; ++ i) {
                    // Construct the name with *
                    // TODO: Once the underlying DatabaseAccessor takes
                    // string, do the concatenation on strings, not
                    // Names
                    Name superdomain(name.split(i));
                    Name wildcard(star.concatenate(superdomain));
                    // TODO What do we do about DNAME here?
                    found = getRRset(wildcard, &type, true, false, true,
                                     &name);
                    if (found.first) {
                        if (first_ns) {
                            // In case we are under NS, we don't
                            // wildcard-match, but return delegation
                            result_rrset = first_ns;
                            result_status = DELEGATION;
                            records_found = true;
                            // We pretend to switch to non-glue_ok mode
                            glue_ok = false;
                            LOG_DEBUG(logger, DBG_TRACE_DETAILED,
                                      DATASRC_DATABASE_WILDCARD_CANCEL_NS).
                                arg(accessor_->getDBName()).arg(wildcard).
                                arg(first_ns->getName());
                        } else if (!hasSubdomains(name.split(i - 1).toText()))
                        {
                            // Nothing we added as part of the * can exist
                            // directly, as we go up only to first existing
                            // domain, but it could be empty non-terminal. In
                            // that case, we need to cancel the match.
                            records_found = true;
                            result_rrset = found.second;
                            LOG_DEBUG(logger, DBG_TRACE_DETAILED,
                                      DATASRC_DATABASE_WILDCARD).
                                arg(accessor_->getDBName()).arg(wildcard).
                                arg(name);
                        } else {
                            LOG_DEBUG(logger, DBG_TRACE_DETAILED,
                                      DATASRC_DATABASE_WILDCARD_CANCEL_SUB).
                                arg(accessor_->getDBName()).arg(wildcard).
                                arg(name).arg(superdomain);
                        }
                        break;
                    } else if (hasSubdomains(wildcard.toText())) {
                        // Empty non-terminal asterisk
                        records_found = true;
                        LOG_DEBUG(logger, DBG_TRACE_DETAILED,
                                  DATASRC_DATABASE_WILDCARD_EMPTY).
                            arg(accessor_->getDBName()).arg(wildcard).
                            arg(name);
                        break;
                    }
                }
            }
        }
    }

    if (!result_rrset) {
        if (records_found) {
            logger.debug(DBG_TRACE_DETAILED,
                         DATASRC_DATABASE_FOUND_NXRRSET)
                        .arg(accessor_->getDBName()).arg(name)
                        .arg(getClass()).arg(type);
            result_status = NXRRSET;
        } else {
            logger.debug(DBG_TRACE_DETAILED,
                         DATASRC_DATABASE_FOUND_NXDOMAIN)
                        .arg(accessor_->getDBName()).arg(name)
                        .arg(getClass()).arg(type);
            result_status = NXDOMAIN;
        }
    } else {
        logger.debug(DBG_TRACE_DETAILED,
                     DATASRC_DATABASE_FOUND_RRSET)
                    .arg(accessor_->getDBName()).arg(*result_rrset);
    }
    return (FindResult(result_status, result_rrset));
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

/*
 * This needs, beside of converting all data from textual representation, group
 * together rdata of the same RRsets. To do this, we hold one row of data ahead
 * of iteration. When we get a request to provide data, we create it from this
 * data and load a new one. If it is to be put to the same rrset, we add it.
 * Otherwise we just return what we have and keep the row as the one ahead
 * for next time.
 */
class DatabaseIterator : public ZoneIterator {
public:
    DatabaseIterator(const DatabaseAccessor::IteratorContextPtr& context,
             const RRClass& rrclass) :
        context_(context),
        class_(rrclass),
        ready_(true)
    {
        // Prepare data for the next time
        getData();
    }

    virtual isc::dns::ConstRRsetPtr getNextRRset() {
        if (!ready_) {
            isc_throw(isc::Unexpected, "Iterating past the zone end");
        }
        if (!data_ready_) {
            // At the end of zone
            ready_ = false;
            LOG_DEBUG(logger, DBG_TRACE_DETAILED,
                      DATASRC_DATABASE_ITERATE_END);
            return (ConstRRsetPtr());
        }
        string name_str(name_), rtype_str(rtype_), ttl(ttl_);
        Name name(name_str);
        RRType rtype(rtype_str);
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

    // The context
    const DatabaseAccessor::IteratorContextPtr context_;
    // Class of the zone
    RRClass class_;
    // Status
    bool ready_, data_ready_;
    // Data of the next row
    string name_, rtype_, rdata_, ttl_;
};

}

ZoneIteratorPtr
DatabaseClient::getIterator(const isc::dns::Name& name) const {
    // Get the zone
    std::pair<bool, int> zone(accessor_->getZone(name.toText()));
    if (!zone.first) {
        // No such zone, can't continue
        isc_throw(DataSourceError, "Zone " + name.toText() +
                  " can not be iterated, because it doesn't exist "
                  "in this data source");
    }
    // Request the context
    DatabaseAccessor::IteratorContextPtr
        context(accessor_->getAllRecords(zone.second));
    // It must not return NULL, that's a bug of the implementation
    if (context == DatabaseAccessor::IteratorContextPtr()) {
        isc_throw(isc::Unexpected, "Iterator context null at " +
                  name.toText());
    }
    // Create the iterator and return it
    // TODO: Once #1062 is merged with this, we need to get the
    // actual zone class from the connection, as the DatabaseClient
    // doesn't know it and the iterator needs it (so it wouldn't query
    // it each time)
    LOG_DEBUG(logger, DBG_TRACE_DETAILED, DATASRC_DATABASE_ITERATE).
        arg(name);
    return (ZoneIteratorPtr(new DatabaseIterator(context, RRClass::IN())));
}

//
// Zone updater using some database system as the underlying data source.
//
class DatabaseUpdater : public ZoneUpdater {
public:
    DatabaseUpdater(shared_ptr<DatabaseAccessor> accessor, int zone_id,
            const Name& zone_name, const RRClass& zone_class) :
        committed_(false), accessor_(accessor), zone_id_(zone_id),
        db_name_(accessor->getDBName()), zone_name_(zone_name.toText()),
        zone_class_(zone_class),
        finder_(new DatabaseClient::Finder(accessor_, zone_id_, zone_name))
    {
        logger.debug(DBG_TRACE_DATA, DATASRC_DATABASE_UPDATER_CREATED)
            .arg(zone_name_).arg(zone_class_).arg(db_name_);
    }

    virtual ~DatabaseUpdater() {
        if (!committed_) {
            try {
                accessor_->rollbackUpdateZone();
                logger.info(DATASRC_DATABASE_UPDATER_ROLLBACK)
                    .arg(zone_name_).arg(zone_class_).arg(db_name_);
            } catch (const DataSourceError& e) {
                // We generally expect that rollback always succeeds, and
                // it should in fact succeed in a way we execute it.  But
                // as the public API allows rollbackUpdateZone() to fail and
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

    virtual void addRRset(const RRset& rrset);
    virtual void deleteRRset(const RRset& rrset);
    virtual void commit();

private:
    bool committed_;
    shared_ptr<DatabaseAccessor> accessor_;
    const int zone_id_;
    const string db_name_;
    const string zone_name_;
    const RRClass zone_class_;
    boost::scoped_ptr<DatabaseClient::Finder> finder_;
};

void
DatabaseUpdater::addRRset(const RRset& rrset) {
    if (committed_) {
        isc_throw(DataSourceError, "Add attempt after commit to zone: "
                  << zone_name_ << "/" << zone_class_);
    }
    if (rrset.getClass() != zone_class_) {
        isc_throw(DataSourceError, "An RRset of a different class is being "
                  << "added to " << zone_name_ << "/" << zone_class_ << ": "
                  << rrset.toText());
    }
    if (rrset.getRRsig()) {
        isc_throw(DataSourceError, "An RRset with RRSIG is being added to "
                  << zone_name_ << "/" << zone_class_ << ": "
                  << rrset.toText());
    }

    RdataIteratorPtr it = rrset.getRdataIterator();
    if (it->isLast()) {
        isc_throw(DataSourceError, "An empty RRset is being added for "
                  << rrset.getName() << "/" << zone_class_ << "/"
                  << rrset.getType());
    }

    string columns[DatabaseAccessor::ADD_COLUMN_COUNT]; // initialized with ""
    columns[DatabaseAccessor::ADD_NAME] = rrset.getName().toText();
    columns[DatabaseAccessor::ADD_REV_NAME] =
        rrset.getName().reverse().toText();
    columns[DatabaseAccessor::ADD_TTL] = rrset.getTTL().toText();
    columns[DatabaseAccessor::ADD_TYPE] = rrset.getType().toText();
    for (; !it->isLast(); it->next()) {
        if (rrset.getType() == RRType::RRSIG()) {
            // XXX: the current interface (based on the current sqlite3
            // data source schema) requires a separate "sigtype" column,
            // even though it won't be used in a newer implementation.
            // We should eventually clean up the schema design and simplify
            // the interface, but until then we have to conform to the schema.
            const generic::RRSIG& rrsig_rdata =
                dynamic_cast<const generic::RRSIG&>(it->getCurrent());
            columns[DatabaseAccessor::ADD_SIGTYPE] =
                rrsig_rdata.typeCovered().toText();
        }
        columns[DatabaseAccessor::ADD_RDATA] = it->getCurrent().toText();
        accessor_->addRecordToZone(columns);
    }
}

void
DatabaseUpdater::deleteRRset(const RRset& rrset) {
    if (committed_) {
        isc_throw(DataSourceError, "Delete attempt after commit on zone: "
                  << zone_name_ << "/" << zone_class_);
    }
    if (rrset.getClass() != zone_class_) {
        isc_throw(DataSourceError, "An RRset of a different class is being "
                  << "deleted from " << zone_name_ << "/" << zone_class_
                  << ": " << rrset.toText());
    }
    if (rrset.getRRsig()) {
        isc_throw(DataSourceError, "An RRset with RRSIG is being deleted from "
                  << zone_name_ << "/" << zone_class_ << ": "
                  << rrset.toText());
    }

    RdataIteratorPtr it = rrset.getRdataIterator();
    if (it->isLast()) {
        isc_throw(DataSourceError, "An empty RRset is being deleted for "
                  << rrset.getName() << "/" << zone_class_ << "/"
                  << rrset.getType());
    }

    string params[DatabaseAccessor::DEL_PARAM_COUNT]; // initialized with ""
    params[DatabaseAccessor::DEL_NAME] = rrset.getName().toText();
    params[DatabaseAccessor::DEL_TYPE] = rrset.getType().toText();
    for (; !it->isLast(); it->next()) {
        params[DatabaseAccessor::DEL_RDATA] = it->getCurrent().toText();
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
    accessor_->commitUpdateZone();
    committed_ = true; // make sure the destructor won't trigger rollback

    // We release the accessor immediately after commit is completed so that
    // we don't hold the possible internal resource any longer.
    accessor_.reset();

    logger.debug(DBG_TRACE_DATA, DATASRC_DATABASE_UPDATER_COMMIT)
        .arg(zone_name_).arg(zone_class_).arg(db_name_);
}

// The updater factory
ZoneUpdaterPtr
DatabaseClient::getUpdater(const isc::dns::Name& name, bool replace) const {
    shared_ptr<DatabaseAccessor> update_accessor(accessor_->clone());
    const std::pair<bool, int> zone(update_accessor->startUpdateZone(
                                        name.toText(), replace));
    if (!zone.first) {
        return (ZoneUpdaterPtr());
    }

    return (ZoneUpdaterPtr(new DatabaseUpdater(update_accessor, zone.second,
                                               name, rrclass_)));
}
}
}
