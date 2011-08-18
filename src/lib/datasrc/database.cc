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

using namespace std;
using boost::shared_ptr;
using namespace isc::dns;
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
    std::pair<bool, int> zone(accessor_->getZone(name));
    // Try exact first
    if (zone.first) {
        return (FindResult(result::SUCCESS,
                           ZoneFinderPtr(new Finder(accessor_,
                                                    zone.second))));
    }
    // Than super domains
    // Start from 1, as 0 is covered above
    for (size_t i(1); i < name.getLabelCount(); ++i) {
        zone = accessor_->getZone(name.split(i));
        if (zone.first) {
            return (FindResult(result::PARTIALMATCH,
                               ZoneFinderPtr(new Finder(accessor_,
                                                        zone.second))));
        }
    }
    // No, really nothing
    return (FindResult(result::NOTFOUND, ZoneFinderPtr()));
}

DatabaseClient::Finder::Finder(boost::shared_ptr<DatabaseAccessor> accessor,
                               int zone_id) :
    accessor_(accessor),
    zone_id_(zone_id)
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
            logger.info(DATASRC_DATABASE_FIND_TTL_MISMATCH)
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


ZoneFinder::FindResult
DatabaseClient::Finder::find(const isc::dns::Name& name,
                             const isc::dns::RRType& type,
                             isc::dns::RRsetList*,
                             const FindOptions)
{
    // This variable is used to determine the difference between
    // NXDOMAIN and NXRRSET
    bool records_found = false;
    isc::dns::RRsetPtr result_rrset;
    ZoneFinder::Result result_status = SUCCESS;
    RRsigStore sig_store;
    logger.debug(DBG_TRACE_DETAILED, DATASRC_DATABASE_FIND_RECORDS)
        .arg(accessor_->getDBName()).arg(name).arg(type);

    try {
        accessor_->searchForRecords(zone_id_, name.toText());

        std::string columns[DatabaseAccessor::COLUMN_COUNT];
        while (accessor_->getNextRecord(columns,
                                        DatabaseAccessor::COLUMN_COUNT)) {
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

                if (cur_type == type) {
                    if (result_rrset &&
                        result_rrset->getType() == isc::dns::RRType::CNAME()) {
                        isc_throw(DataSourceError, "CNAME found but it is not "
                                  "the only record for " + name.toText());
                    }
                    addOrCreate(result_rrset, name, getClass(), cur_type,
                                cur_ttl, columns[DatabaseAccessor::
                                                 RDATA_COLUMN],
                                *accessor_);
                } else if (cur_type == isc::dns::RRType::CNAME()) {
                    // There should be no other data, so result_rrset should
                    // be empty.
                    if (result_rrset) {
                        isc_throw(DataSourceError, "CNAME found but it is not "
                                  "the only record for " + name.toText());
                    }
                    addOrCreate(result_rrset, name, getClass(), cur_type,
                                cur_ttl, columns[DatabaseAccessor::
                                                 RDATA_COLUMN],
                                *accessor_);
                    result_status = CNAME;
                } else if (cur_type == isc::dns::RRType::RRSIG()) {
                    // If we get signatures before we get the actual data, we
                    // can't know which ones to keep and which to drop...
                    // So we keep a separate store of any signature that may be
                    // relevant and add them to the final RRset when we are
                    // done.
                    // A possible optimization here is to not store them for
                    // types we are certain we don't need
                    sig_store.addSig(isc::dns::rdata::createRdata(cur_type,
                                    getClass(),
                                    columns[DatabaseAccessor::
                                            RDATA_COLUMN]));
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
    } catch (const DataSourceError& dse) {
        logger.error(DATASRC_DATABASE_FIND_ERROR)
            .arg(accessor_->getDBName()).arg(dse.what());
        // call cleanup and rethrow
        accessor_->resetSearch();
        throw;
    } catch (const isc::Exception& isce) {
        logger.error(DATASRC_DATABASE_FIND_UNCAUGHT_ISC_ERROR)
            .arg(accessor_->getDBName()).arg(isce.what());
        // cleanup, change it to a DataSourceError and rethrow
        accessor_->resetSearch();
        isc_throw(DataSourceError, isce.what());
    } catch (const std::exception& ex) {
        logger.error(DATASRC_DATABASE_FIND_UNCAUGHT_ERROR)
            .arg(accessor_->getDBName()).arg(ex.what());
        accessor_->resetSearch();
        throw;
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
        sig_store.appendSignatures(result_rrset);
        logger.debug(DBG_TRACE_DETAILED,
                     DATASRC_DATABASE_FOUND_RRSET)
                    .arg(accessor_->getDBName()).arg(*result_rrset);
    }
    return (FindResult(result_status, result_rrset));
}

Name
DatabaseClient::Finder::getOrigin() const {
    // TODO Implement
    return (Name("."));
}

isc::dns::RRClass
DatabaseClient::Finder::getClass() const {
    // TODO Implement
    return isc::dns::RRClass::IN();
}

ZoneUpdaterPtr
DatabaseClient::startUpdateZone(const isc::dns::Name& name,
                                bool replace) const
{
    shared_ptr<DatabaseAccessor> update_accessor(accessor_->clone());
    const std::pair<bool, int> zone(update_accessor->startUpdateZone(
                                        name.toText(), replace));
    if (!zone.first) {
        return (ZoneUpdaterPtr());
    }

     return (ZoneUpdaterPtr(new Updater(update_accessor, zone.second,
                                        name.toText(), rrclass_)));
}

DatabaseClient::Updater::Updater(shared_ptr<DatabaseAccessor> accessor,
                                 int zone_id, const string& zone_name,
                                 const RRClass& zone_class) :
    committed_(false), accessor_(accessor), zone_id_(zone_id),
    db_name_(accessor->getDBName()), zone_name_(zone_name),
    zone_class_(zone_class),
    finder_(new Finder(accessor_, zone_id_)),
    add_columns_(DatabaseAccessor::ADD_COLUMN_COUNT),
    del_params_(DatabaseAccessor::DEL_PARAM_COUNT)
{
    logger.debug(DBG_TRACE_DATA, DATASRC_DATABASE_UPDATER_CREATED)
        .arg(zone_name_).arg(zone_class_).arg(db_name_);
}

DatabaseClient::Updater::~Updater() {
    if (!committed_) {
        accessor_->rollbackUpdateZone();
        logger.info(DATASRC_DATABASE_UPDATER_ROLLBACK)
            .arg(zone_name_).arg(zone_class_).arg(db_name_);
    }

    logger.debug(DBG_TRACE_DATA, DATASRC_DATABASE_UPDATER_DESTROYED)
        .arg(zone_name_).arg(zone_class_).arg(db_name_);
}

ZoneFinder&
DatabaseClient::Updater::getFinder() {
    return (*finder_);
}

void
DatabaseClient::Updater::addRRset(const RRset& rrset) {
    if (committed_) {
        isc_throw(DataSourceError, "Add attempt after commit to zone: "
                  << zone_name_ << "/" << zone_class_);
    }
    if (rrset.getClass() != zone_class_) {
        isc_throw(DataSourceError, "An RRset of a different class is being "
                  << "added to " << zone_name_ << "/" << zone_class_ << ": "
                  << rrset.toText());
    }

    RdataIteratorPtr it = rrset.getRdataIterator();
    if (it->isLast()) {
        isc_throw(DataSourceError, "An empty RRset is being added for "
                  << rrset.getName() << "/" << zone_class_ << "/"
                  << rrset.getType());
    }

    add_columns_.assign(DatabaseAccessor::ADD_COLUMN_COUNT, "");
    add_columns_.at(DatabaseAccessor::ADD_NAME) = rrset.getName().toText();
    add_columns_.at(DatabaseAccessor::ADD_REV_NAME) =
        rrset.getName().reverse().toText();
    add_columns_.at(DatabaseAccessor::ADD_TTL) = rrset.getTTL().toText();
    add_columns_.at(DatabaseAccessor::ADD_TYPE) = rrset.getType().toText();
    for (; !it->isLast(); it->next()) {
        if (rrset.getType() == RRType::RRSIG()) {
            // XXX: the current interface (based on the current sqlite3
            // data source schema) requires a separate "sigtype" column,
            // even though it won't be used in a newer implementation.
            // We should eventually clean up the schema design and simplify
            // the interface, but until then we have to conform to the schema.
            const generic::RRSIG& rrsig_rdata =
                dynamic_cast<const generic::RRSIG&>(it->getCurrent());
            add_columns_.at(DatabaseAccessor::ADD_SIGTYPE) =
                rrsig_rdata.typeCovered().toText();
        }
        add_columns_.at(DatabaseAccessor::ADD_RDATA) =
            it->getCurrent().toText();
        accessor_->addRecordToZone(add_columns_);
    }
}

void
DatabaseClient::Updater::deleteRRset(const RRset& rrset) {
    if (committed_) {
        isc_throw(DataSourceError, "Delete attempt after commit on zone: "
                  << zone_name_ << "/" << zone_class_);
    }
    if (rrset.getClass() != zone_class_) {
        isc_throw(DataSourceError, "An RRset of a different class is being "
                  << "deleted from " << zone_name_ << "/" << zone_class_
                  << ": " << rrset.toText());
    }

    RdataIteratorPtr it = rrset.getRdataIterator();
    if (it->isLast()) {
        isc_throw(DataSourceError, "An empty RRset is being deleted for "
                  << rrset.getName() << "/" << zone_class_ << "/"
                  << rrset.getType());
    }

    del_params_.assign(DatabaseAccessor::DEL_PARAM_COUNT, "");
    del_params_.at(DatabaseAccessor::DEL_NAME) = rrset.getName().toText();
    del_params_.at(DatabaseAccessor::DEL_TYPE) = rrset.getType().toText();
    for (; !it->isLast(); it->next()) {
        del_params_.at(DatabaseAccessor::DEL_RDATA) =
            it->getCurrent().toText();
        accessor_->deleteRecordInZone(del_params_);
    }
}

void
DatabaseClient::Updater::commit() {
    if (committed_) {
        isc_throw(DataSourceError, "Duplicate commit attempt for "
                  << zone_name_ << "/" << zone_class_ << " on "
                  << db_name_);
    }
    accessor_->commitUpdateZone();

    // We release the accessor immediately after commit is completed so that
    // we don't hold the possible internal resource any longer.
    accessor_.reset();

    committed_ = true;

    logger.debug(DBG_TRACE_DATA, DATASRC_DATABASE_UPDATER_COMMIT)
        .arg(zone_name_).arg(zone_class_).arg(db_name_);
}
}
}
