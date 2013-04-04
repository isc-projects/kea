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

#ifndef DATASRC_MEMORY_CLIENT_H
#define DATASRC_MEMORY_CLIENT_H 1

#include <util/memory_segment.h>

#include <datasrc/zone_iterator.h>
#include <datasrc/client.h>
#include <datasrc/memory/zone_table.h>
#include <datasrc/memory/zone_data.h>

#include <boost/shared_ptr.hpp>

#include <string>

namespace isc {

namespace dns {
class Name;
class RRsetList;
};

namespace datasrc {
namespace memory {

class ZoneTableSegment;

/// \brief A data source client that holds all necessary data in memory.
///
/// The \c InMemoryClient class provides an access to a conceptual data
/// source that maintains all necessary data in a memory image, thereby
/// allowing much faster lookups.  The in memory data is a copy of some
/// real physical source - in the current implementation a list of zones
/// are populated as a result of \c load() calls; zone data is given in
/// a standard master file, or as an iterator of some other datasource
/// including database backed ones.
///
/// The InMemoryClient enforces through its interface that all data
/// loaded to the data source is of the same RR class.  For example, the
/// \c load() method assumes that the zone being loaded belongs to the
/// same RR class as the memory::Client instance.
class InMemoryClient : public DataSourceClient {
public:
    ///
    /// \name Constructor.
    ///
    //@{

    /// Default constructor.
    ///
    /// This constructor internally involves resource allocation, and if
    /// it fails, a corresponding standard exception will be thrown.
    /// It never throws an exception otherwise.
    InMemoryClient(boost::shared_ptr<ZoneTableSegment> ztable_segment,
                   isc::dns::RRClass rrclass);
    //@}

    /// \brief Returns the class of the data source client.
    virtual isc::dns::RRClass getClass() const;

    /// Return the number of zones stored in the client.
    ///
    /// This method never throws an exception.
    ///
    /// \return The number of zones stored in the client.
    virtual unsigned int getZoneCount() const;

    /// Returns a \c ZoneFinder result that best matches the given name.
    ///
    /// This derived version of the method never throws an exception.
    /// For other details see \c DataSourceClient::findZone().
    virtual isc::datasrc::DataSourceClient::FindResult
    findZone(const isc::dns::Name& name) const;

    /// Returns a \c ZoneData in the result that best matches the given
    /// name.
    ///
    /// This is mainly intended for use in unit tests and should not be
    /// used in other code.
    ///
    /// \throws none
    const ZoneData* findZoneData(const isc::dns::Name& name);

    /// \brief Implementation of the getIterator method
    virtual isc::datasrc::ZoneIteratorPtr
    getIterator(const isc::dns::Name& name, bool separate_rrs = false) const;

    /// In-memory data source doesn't write back persistently, so this
    /// derived method will result in a NotImplemented exception.
    ///
    /// \note We plan to use a database-based data source as a backend
    /// persistent storage for an in-memory data source.  When it's
    /// implemented we may also want to allow the user of the in-memory client
    /// to update via its updater (this may or may not be a good idea and
    /// is subject to further discussions).
    virtual ZoneUpdaterPtr getUpdater(const isc::dns::Name& name,
                                      bool replace, bool journaling = false)
        const;

    virtual std::pair<ZoneJournalReader::Result, ZoneJournalReaderPtr>
    getJournalReader(const isc::dns::Name& zone, uint32_t begin_serial,
                     uint32_t end_serial) const;

private:
    boost::shared_ptr<ZoneTableSegment> ztable_segment_;
    const isc::dns::RRClass rrclass_;
};

} // namespace memory
} // namespace datasrc
} // namespace isc

#endif // DATASRC_MEMORY_CLIENT_H

// Local Variables:
// mode: c++
// End:
