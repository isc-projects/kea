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

#include <datasrc/zone_loader.h>
#include <datasrc/master_loader_callbacks.h>

#include <datasrc/client.h>
#include <datasrc/data_source.h>
#include <datasrc/iterator.h>
#include <datasrc/zone.h>
#include <datasrc/logger.h>
#include <datasrc/rrset_collection.h>

#include <dns/rrset.h>
#include <dns/zone_checker.h>

#include <boost/bind.hpp>

using isc::dns::Name;
using isc::dns::ConstRRsetPtr;
using isc::dns::MasterLoader;

namespace isc {
namespace datasrc {

ZoneLoader::ZoneLoader(DataSourceClient& destination, const Name& zone_name,
                       DataSourceClient& source) :
    // Separate the RRsets as that is possibly faster (the data source doesn't
    // have to aggregate them) and also because our limit semantics.
    iterator_(source.getIterator(zone_name, true)),
    updater_(destination.getUpdater(zone_name, true, false)),
    complete_(false)
{
    // The getIterator should never return NULL. So we check it.
    // Or should we throw instead?
    assert(iterator_ != ZoneIteratorPtr());
    // In case the zone doesn't exist in the destination, throw
    if (updater_ == ZoneUpdaterPtr()) {
        isc_throw(DataSourceError, "Zone " << zone_name << " not found in "
                  "destination data source, can't fill it with data");
    }
    // The dereference of zone_finder is safe, if we can get iterator, we can
    // get a finder.
    //
    // TODO: We probably need a getClass on the data source itself.
    if (source.findZone(zone_name).zone_finder->getClass() !=
        updater_->getFinder().getClass()) {
        isc_throw(isc::InvalidParameter,
                  "Source and destination class mismatch");
    }
}

ZoneLoader::ZoneLoader(DataSourceClient& destination, const Name& zone_name,
                       const char* filename) :
    updater_(destination.getUpdater(zone_name, true, false)),
    complete_(false),
    loaded_ok_(true)
{
    if (updater_ == ZoneUpdaterPtr()) {
        isc_throw(DataSourceError, "Zone " << zone_name << " not found in "
                  "destination data source, can't fill it with data");
    } else {
        loader_.reset(new
                      MasterLoader(filename, zone_name,
                                   // TODO: Maybe we should have getClass()
                                   // on the data source?
                                   updater_->getFinder().getClass(),
                                   createMasterLoaderCallbacks(zone_name,
                                       updater_->getFinder().getClass(),
                                       &loaded_ok_),
                                   createMasterLoaderAddCallback(*updater_)));
    }
}

namespace {

// Copy up to limit RRsets from source to destination
bool
copyRRsets(const ZoneUpdaterPtr& destination, const ZoneIteratorPtr& source,
           size_t limit)
{
    size_t loaded = 0;
    while (loaded < limit) {
        const ConstRRsetPtr rrset(source->getNextRRset());
        if (rrset == ConstRRsetPtr()) {
            // Done loading, no more RRsets in the input.
            return (true);
        } else {
            destination->addRRset(*rrset);
        }
        ++loaded;
    }
    return (false); // Not yet, there may be more
}

void
logWarning(const dns::Name* zone_name, const dns::RRClass* rrclass,
           const std::string& reason)
{
    LOG_WARN(logger, DATASRC_VALIDATE_WARNING).arg(*zone_name).arg(*rrclass).
        arg(reason);
}

void
logError(const dns::Name* zone_name, const dns::RRClass* rrclass,
         const std::string& reason)
{
    LOG_ERROR(logger, DATASRC_VALIDATE_ERROR).arg(*zone_name).arg(*rrclass).
        arg(reason);
}

} // end unnamed namespace

bool
ZoneLoader::loadIncremental(size_t limit) {
    if (complete_) {
        isc_throw(isc::InvalidOperation,
                  "Loading has been completed previously");
    }

    if (iterator_ == ZoneIteratorPtr()) {
        assert(loader_.get() != NULL);
        try {
            complete_ = loader_->loadIncremental(limit);
        } catch (const isc::dns::MasterLoaderError& e) {
            isc_throw(MasterFileError, e.getMessage().c_str());
        }
        if (complete_ && !loaded_ok_) {
            isc_throw(MasterFileError, "Error while loading master file");
        }
    } else {
        complete_ = copyRRsets(updater_, iterator_, limit);
    }

    if (complete_) {
        // Everything is loaded. Perform some basic sanity checks on the zone.
        RRsetCollection collection(updater_);
        dns::Name zone_name(updater_->getFinder().getOrigin());
        dns::RRClass zone_class(updater_->getFinder().getClass());
        dns::ZoneCheckerCallbacks
            callbacks(boost::bind(&logError, &zone_name, &zone_class, _1),
                      boost::bind(&logWarning, &zone_name, &zone_class, _1));
        if (!dns::checkZone(zone_name, zone_class, collection, callbacks)) {
            // Validation failed.
            loaded_ok_ = false;
            isc_throw(ZoneContentError, "Errors found when validating zone " <<
                      zone_name << "/" << zone_class);
        }
        updater_->commit();
    }
    return (complete_);
}

} // end namespace datasrc
} // end namespace isc
