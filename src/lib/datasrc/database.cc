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
#include <datasrc/data_source.h>
#include <datasrc/iterator.h>

#include <exceptions/exceptions.h>
#include <dns/name.h>
#include <dns/rrclass.h>
#include <dns/rrttl.h>

#include <string>

using namespace isc::dns;
using std::string;

namespace isc {
namespace datasrc {

DatabaseClient::DatabaseClient(std::auto_ptr<DatabaseConnection> connection) :
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
                           ZoneFinderPtr(new Finder(*connection_,
                                                    zone.second))));
    }
    // Than super domains
    // Start from 1, as 0 is covered above
    for (size_t i(1); i < name.getLabelCount(); ++i) {
        zone = connection_->getZone(name.split(i));
        if (zone.first) {
            return (FindResult(result::PARTIALMATCH,
                               ZoneFinderPtr(new Finder(*connection_,
                                                        zone.second))));
        }
    }
    // No, really nothing
    return (FindResult(result::NOTFOUND, ZoneFinderPtr()));
}

DatabaseClient::Finder::Finder(DatabaseConnection& connection, int zone_id) :
    connection_(connection),
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

namespace {

/*
 * This needs, beside of converting all data from textual representation, group
 * together rdata of the same RRsets. To do this, we hold one row of data ahead
 * of iteration. When we get a request to provide data, we create it from this
 * data and load a new one. If it is to be put to the same rrset, we add it.
 * Otherwise we just return what we have and keep the row as the one ahead
 * for next time.
 */
class Iterator : public ZoneIterator {
public:
    Iterator(const DatabaseConnection::IteratorContextPtr& context,
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
            return (ConstRRsetPtr());
        }
        string nameStr(name_), rtypeStr(rtype_);
        int ttl(ttl_);
        Name name(nameStr);
        RRType rtype(rtypeStr);
        RRsetPtr rrset(new RRset(name, class_, rtype, RRTTL(ttl)));
        while (data_ready_ && name_ == nameStr && rtypeStr == rtype_) {
            if (ttl_ != ttl) {
                isc_throw(DataSourceError, "TTLs in rrset " + nameStr + "/" +
                          rtypeStr + " differ");
            }
            rrset->addRdata(rdata::createRdata(rtype, class_, rdata_));
            getData();
        }
        return (rrset);
    }
private:
    // Load next row of data
    void getData() {
        data_ready_ = context_->getNext(name_, rtype_, ttl_, rdata_);
    }
    // The context
    const DatabaseConnection::IteratorContextPtr context_;
    // Class of the zone
    RRClass class_;
    // Status
    bool ready_, data_ready_;
    // Data of the next row
    string name_, rtype_, rdata_;
    int ttl_;
};

}

ZoneIteratorPtr
DatabaseClient::getIterator(const isc::dns::Name& name) const {
    // Get the zone
    std::pair<bool, int> zone(connection_->getZone(name));
    if (!zone.first) {
        // No such zone, can't continue
        isc_throw(DataSourceError, "Zone " + name.toText() +
                  " can not be iterated, because it doesn't exist "
                  "in this data source");
    }
    // Request the context
    DatabaseConnection::IteratorContextPtr
        context(connection_->getIteratorContext(name, zone.second));
    // It must not return NULL, that's a bug of the implementation
    if (context == DatabaseConnection::IteratorContextPtr()) {
        isc_throw(isc::Unexpected, "Iterator context null at " +
                  name.toText());
    }
    // Create the iterator and return it
    // TODO: Once #1062 is merged with this, we need to get the
    // actual zone class from the connection, as the DatabaseClient
    // doesn't know it and the iterator needs it (so it wouldn't query
    // it each time)
    return (ZoneIteratorPtr(new Iterator(context, RRClass::IN())));
}

}
}
