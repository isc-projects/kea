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

using isc::dns::Name;

namespace isc {
namespace datasrc {

DatabaseClient::DatabaseClient(boost::shared_ptr<DatabaseAccessor>
                               database) :
    database_(database)
{
    if (database_.get() == NULL) {
        isc_throw(isc::InvalidParameter,
                  "No database provided to DatabaseClient");
    }
}

DataSourceClient::FindResult
DatabaseClient::findZone(const Name& name) const {
    std::pair<bool, int> zone(database_->getZone(name));
    // Try exact first
    if (zone.first) {
        return (FindResult(result::SUCCESS,
                           ZoneFinderPtr(new Finder(database_,
                                                    zone.second))));
    }
    // Than super domains
    // Start from 1, as 0 is covered above
    for (size_t i(1); i < name.getLabelCount(); ++i) {
        zone = database_->getZone(name.split(i));
        if (zone.first) {
            return (FindResult(result::PARTIALMATCH,
                               ZoneFinderPtr(new Finder(database_,
                                                        zone.second))));
        }
    }
    // No, really nothing
    return (FindResult(result::NOTFOUND, ZoneFinderPtr()));
}

DatabaseClient::Finder::Finder(boost::shared_ptr<DatabaseAccessor>
                               database, int zone_id) :
    database_(database),
    zone_id_(zone_id)
{ }

ZoneFinder::FindResult
DatabaseClient::Finder::find(const isc::dns::Name&,
                             const isc::dns::RRType&,
                             isc::dns::RRsetList*,
                             const FindOptions) const
{
    // TODO Implement
    return (FindResult(SUCCESS, isc::dns::ConstRRsetPtr()));
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
