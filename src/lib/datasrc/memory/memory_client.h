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

#include <datasrc/iterator.h>
#include <datasrc/client.h>
#include <datasrc/memory/zone_table.h>
#include <datasrc/memory/zone_data.h>

#include <string>

namespace isc {

namespace dns {
class Name;
class RRsetList;
};

namespace datasrc {
namespace memory {

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
    /// \name Constructors and Destructor.
    ///
    //@{

    /// Default constructor.
    ///
    /// This constructor internally involves resource allocation, and if
    /// it fails, a corresponding standard exception will be thrown.
    /// It never throws an exception otherwise.
    InMemoryClient(util::MemorySegment& mem_sgmt,
                   isc::dns::RRClass rrclass);

    /// The destructor.
    ~InMemoryClient();
    //@}

    /// \brief Returns the class of the data source client.
    virtual isc::dns::RRClass getClass() const;

    /// Return the number of zones stored in the client.
    ///
    /// This method never throws an exception.
    ///
    /// \return The number of zones stored in the client.
    virtual unsigned int getZoneCount() const;

    /// \brief Load zone from masterfile.
    ///
    /// This loads data from masterfile specified by filename. It replaces
    /// current content. The masterfile parsing ability is kind of limited,
    /// see isc::dns::masterLoad.
    ///
    /// This throws isc::dns::MasterLoadError if there is problem with loading
    /// (missing file, malformed, it contains different zone, etc - see
    /// isc::dns::masterLoad for details).
    ///
    /// In case of internal problems, OutOfZone, NullRRset or AssertError could
    /// be thrown, but they should not be expected. Exceptions caused by
    /// allocation may be thrown as well.
    ///
    /// If anything is thrown, the previous content is preserved (so it can
    /// be used to update the data, but if user makes a typo, the old one
    /// is kept).
    ///
    /// \param filename The master file to load.
    ///
    /// \todo We may need to split it to some kind of build and commit/abort.
    ///     This will probably be needed when a better implementation of
    ///     configuration reloading is written.
    result::Result load(const isc::dns::Name& zone_name,
                        const std::string& filename);

    /// \brief Load zone from another data source.
    ///
    /// This is similar to the other version, but zone's RRsets are provided
    /// by an iterator of another data source.  On successful load, the
    /// internal filename will be cleared.
    ///
    /// This implementation assumes the iterator produces combined RRsets,
    /// that is, there should exactly one RRset for the same owner name and
    /// RR type.  This means the caller is expected to create the iterator
    /// with \c separate_rrs being \c false.  This implementation also assumes
    /// RRsets of different names are not mixed; so if the iterator produces
    /// an RRset of a different name than that of the previous RRset, that
    /// previous name must never appear in the subsequent sequence of RRsets.
    /// Note that the iterator API does not ensure this.  If the underlying
    /// implementation does not follow it, load() will fail.  Note, however,
    /// that this whole interface is tentative.  in-memory zone loading will
    /// have to be revisited fundamentally, and at that point this restriction
    /// probably won't matter.
    result::Result load(const isc::dns::Name& zone_name,
                        ZoneIterator& iterator);

    /// Return the master file name of the zone
    ///
    /// This method returns the name of the zone's master file to be loaded.
    /// The returned string will be an empty unless the data source client has
    /// successfully loaded the \c zone_name zone from a file before.
    ///
    /// This method should normally not throw an exception.  But the creation
    /// of the return string may involve a resource allocation, and if it
    /// fails, the corresponding standard exception will be thrown.
    ///
    /// \return The name of the zone file corresponding to the zone, or
    /// an empty string if the client hasn't loaded the \c zone_name
    /// zone from a file before.
    const std::string getFileName(const isc::dns::Name& zone_name) const;

    /// \brief Inserts an rrset into the zone.
    ///
    /// It puts another RRset into the zone.
    ///
    /// In the current implementation, this method doesn't allow an existing
    /// RRset to be updated or overridden.  So the caller must make sure that
    /// all RRs of the same type and name must be given in the form of a
    /// single RRset.  The current implementation will also require that
    /// when an RRSIG is added, the RRset to be covered has already been
    /// added.  These restrictions are probably too strict when this data
    /// source accepts various forms of input, so they should be revisited
    /// later.
    ///
    /// Except for NullRRset and OutOfZone, this method does not guarantee
    /// strong exception safety (it is currently not needed, if it is needed
    /// in future, it should be implemented).
    ///
    /// \throw NullRRset \c rrset is a NULL pointer.
    /// \throw OutOfZone The owner name of \c rrset is outside of the
    /// origin of the zone.
    /// \throw AddError Other general errors.
    /// \throw Others This method might throw standard allocation exceptions.
    ///
    /// \param rrset The set to add.
    /// \return SUCCESS or EXIST (if an rrset for given name and type already
    ///    exists).
    result::Result add(const isc::dns::Name& zone_name,
                       const isc::dns::ConstRRsetPtr& rrset);

    /// \brief RRset is NULL exception.
    ///
    /// This is thrown if the provided RRset parameter is NULL.
    struct NullRRset : public InvalidParameter {
        NullRRset(const char* file, size_t line, const char* what) :
            InvalidParameter(file, line, what)
        { }
    };

    /// \brief Zone is empty exception.
    ///
    /// This is thrown if we have an empty zone created as a result of
    /// load().
    struct EmptyZone : public InvalidParameter {
        EmptyZone(const char* file, size_t line, const char* what) :
            InvalidParameter(file, line, what)
        { }
    };

    /// \brief General failure exception for \c add().
    ///
    /// This is thrown against general error cases in adding an RRset
    /// to the zone.
    ///
    /// Note: this exception would cover cases for \c OutOfZone or
    /// \c NullRRset.  We'll need to clarify and unify the granularity
    /// of exceptions eventually.  For now, exceptions are added as
    /// developers see the need for it.
    struct AddError : public InvalidParameter {
        AddError(const char* file, size_t line, const char* what) :
            InvalidParameter(file, line, what)
        { }
    };

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
    // TODO: Do we still need the PImpl if nobody should manipulate this class
    // directly any more (it should be handled through DataSourceClient)?
    class InMemoryClientImpl;
    InMemoryClientImpl* impl_;

    // A helper internal class used by load().  It maintains some intermediate
    // states while loading RRs of the zone.
    class Loader;
};

} // namespace memory
} // namespace datasrc
} // namespace isc

#endif // DATASRC_MEMORY_CLIENT_H

// Local Variables:
// mode: c++
// End:
