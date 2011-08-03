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
#include <datasrc/data_source.h>

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

ZoneFinder::FindResult
DatabaseClient::Finder::find(const isc::dns::Name& name,
                             const isc::dns::RRType& type,
                             isc::dns::RRsetList*,
                             const FindOptions) const
{
    bool records_found = false;
    connection_.searchForRecords(zone_id_, name.toText());

    isc::dns::RRsetPtr result_rrset;

    std::vector<std::string> columns;
    while (connection_.getNextRecord(columns)) {
        if (!records_found) {
            records_found = true;
        }

        if (columns.size() != 4) {
            isc_throw(DataSourceError,
                      "Datasource backend did not return 4 columns in getNextRecord()");
        }

        const isc::dns::RRType cur_type(columns[0]);
        const isc::dns::RRTTL cur_ttl(columns[1]);
        //cur_sigtype(columns[2]);

        if (cur_type == type) {
            if (!result_rrset) {
                result_rrset = isc::dns::RRsetPtr(new isc::dns::RRset(name,
                                                                      getClass(),
                                                                      cur_type,
                                                                      cur_ttl));
            } else {
                // We have existing data from earlier calls, do some checks
                // and updates if necessary
                if (cur_ttl < result_rrset->getTTL()) {
                    result_rrset->setTTL(cur_ttl);
                }
            }

            result_rrset->addRdata(isc::dns::rdata::createRdata(cur_type,
                                                                getClass(),
                                                                columns[3]));
        } else if (cur_type == isc::dns::RRType::CNAME()) {
            // There should be no other data, so cur_rrset should be empty,
            // except for signatures
            if (result_rrset && result_rrset->getRdataCount() > 0) {
                isc_throw(DataSourceError, "CNAME found but it is not the only record for " + name.toText());
            }
            result_rrset = isc::dns::RRsetPtr(new isc::dns::RRset(name,
                                                                  getClass(),
                                                                  cur_type,
                                                                  cur_ttl));
            result_rrset->addRdata(isc::dns::rdata::createRdata(cur_type,
                                                                getClass(),
                                                                columns[3]));
        }
    }

    if (result_rrset) {
        return (FindResult(SUCCESS, result_rrset));
    } else if (records_found) {
        return (FindResult(NXRRSET, isc::dns::ConstRRsetPtr()));
    } else {
        return (FindResult(NXDOMAIN, isc::dns::ConstRRsetPtr()));
    }
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
