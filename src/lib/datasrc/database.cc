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

#include <datasrc/database.h>

#include <exceptions/exceptions.h>
#include <dns/name.h>
#include <dns/rrttl.h>
#include <dns/rdata.h>
#include <dns/rdataclass.h>

#include <datasrc/data_source.h>

#include <boost/foreach.hpp>

using isc::dns::Name;

namespace isc {
namespace datasrc {

DatabaseClient::DatabaseClient(boost::shared_ptr<DatabaseConnection>
                               connection) :
    connection_(connection)
{
    if (connection_.get() == NULL) {
        isc_throw(isc::InvalidParameter,
                  "No connection provided to DatabaseClient");
    }
}

DataSourceClient::FindResult
DatabaseClient::findZone(const Name& name) const {
    std::pair<bool, int> zone(connection_->getZone(name));
    // Try exact first
    if (zone.first) {
        return (FindResult(result::SUCCESS,
                           ZoneFinderPtr(new Finder(connection_,
                                                    zone.second))));
    }
    // Than super domains
    // Start from 1, as 0 is covered above
    for (size_t i(1); i < name.getLabelCount(); ++i) {
        zone = connection_->getZone(name.split(i));
        if (zone.first) {
            return (FindResult(result::PARTIALMATCH,
                               ZoneFinderPtr(new Finder(connection_,
                                                        zone.second))));
        }
    }
    // No, really nothing
    return (FindResult(result::NOTFOUND, ZoneFinderPtr()));
}

DatabaseClient::Finder::Finder(boost::shared_ptr<DatabaseConnection>
                               connection, int zone_id) :
    connection_(connection),
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
    void addOrCreate(isc::dns::RRsetPtr& rrset,
                     const isc::dns::Name& name,
                     const isc::dns::RRClass& cls,
                     const isc::dns::RRType& type,
                     const isc::dns::RRTTL& ttl,
                     const std::string& rdata_str)
    {
        if (!rrset) {
            rrset.reset(new isc::dns::RRset(name, cls, type, ttl));
        } else {
            if (ttl < rrset->getTTL()) {
                rrset->setTTL(ttl);
            }
            // make sure the type is correct
            if (type != rrset->getType()) {
                isc_throw(DataSourceError,
                          "attempt to add multiple types to RRset in find()");
            }
        }
        if (rdata_str != "") {
            try {
                rrset->addRdata(isc::dns::rdata::createRdata(type, cls, rdata_str));
            } catch (const isc::dns::rdata::InvalidRdataText& ivrt) {
                // at this point, rrset may have been initialised for no reason,
                // and won't be used. But the caller would drop the shared_ptr
                // on such an error anyway, so we don't care.
                isc_throw(DataSourceError,
                          "bad rdata in database for " << name.toText() << " "
                          << type.toText() << " " << ivrt.what());
            }
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
        // (the caller must make sure of this)
        void addSig(isc::dns::rdata::RdataPtr sig_rdata) {
            const isc::dns::RRType& type_covered =
                static_cast<isc::dns::rdata::generic::RRSIG*>(
                    sig_rdata.get())->typeCovered();
            if (!haveSigsFor(type_covered)) {
                sigs[type_covered] = std::vector<isc::dns::rdata::RdataPtr>();
            }
            sigs.find(type_covered)->second.push_back(sig_rdata);
        }

        // Returns true if this store contains signatures covering the
        // given type
        bool haveSigsFor(isc::dns::RRType type) {
            return (sigs.count(type) > 0);
        }

        // If the store contains signatures for the type of the given
        // rrset, they are appended to it.
        void appendSignatures(isc::dns::RRsetPtr& rrset) {
            if (haveSigsFor(rrset->getType())) {
                BOOST_FOREACH(isc::dns::rdata::RdataPtr sig,
                              sigs.find(rrset->getType())->second) {
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
                             const FindOptions) const
{
    // This variable is used to determine the difference between
    // NXDOMAIN and NXRRSET
    bool records_found = false;
    isc::dns::RRsetPtr result_rrset;
    ZoneFinder::Result result_status = SUCCESS;
    RRsigStore sig_store;

    connection_->searchForRecords(zone_id_, name.toText());

    std::vector<std::string> columns;
    while (connection_->getNextRecord(columns)) {
        if (!records_found) {
            records_found = true;
        }

        if (columns.size() != 4) {
            isc_throw(DataSourceError,
                      "Datasource backend did not return 4 columns in getNextRecord()");
        }

        try {
            const isc::dns::RRType cur_type(columns[0]);
            const isc::dns::RRTTL cur_ttl(columns[1]);
            //cur_sigtype(columns[2]);

            if (cur_type == type) {
                addOrCreate(result_rrset, name, getClass(), cur_type, cur_ttl, columns[3]);
            } else if (cur_type == isc::dns::RRType::CNAME()) {
                // There should be no other data, so cur_rrset should be empty,
                if (result_rrset) {
                    isc_throw(DataSourceError,
                                "CNAME found but it is not the only record for " +
                                name.toText());
                }
                addOrCreate(result_rrset, name, getClass(), cur_type, cur_ttl, columns[3]);
                result_status = CNAME;
            } else if (cur_type == isc::dns::RRType::RRSIG()) {
                // If we get signatures before we get the actual data, we can't know
                // which ones to keep and which to drop...
                // So we keep a separate store of any signature that may be relevant
                // and add them to the final RRset when we are done.
                // A possible optimization here is to not store them for types we
                // are certain we don't need
                isc::dns::rdata::RdataPtr cur_rrsig(
                    isc::dns::rdata::createRdata(cur_type, getClass(), columns[3]));
                sig_store.addSig(cur_rrsig);
            }
        } catch (const isc::dns::InvalidRRType& irt) {
            isc_throw(DataSourceError,
                      "Invalid RRType in database for " << name << ": " << columns[0]);
        } catch (const isc::dns::InvalidRRTTL& irttl) {
            isc_throw(DataSourceError,
                      "Invalid TTL in database for " << name << ": " << columns[1]);
        }
    }

    if (!result_rrset) {
        if (records_found) {
            result_status = NXRRSET;
        } else {
            result_status = NXDOMAIN;
        }
    } else {
        sig_store.appendSignatures(result_rrset);
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

}
}
