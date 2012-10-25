// Copyright (C) 2010  Internet Systems Consortium, Inc. ("ISC")
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

#ifndef MEMORY_DATA_SOURCE_H
#define MEMORY_DATA_SOURCE_H 1

#include <string>

#include <boost/noncopyable.hpp>

#include <datasrc/zonetable.h>
#include <datasrc/client.h>

#include <cc/data.h>

namespace isc {
namespace dns {
class Name;
class RRsetList;
};

namespace datasrc {

/// A derived zone finder class intended to be used with the memory data source.
///
/// Conceptually this "finder" maintains a local in-memory copy of all RRs
/// of a single zone from some kind of source (right now it's a textual
/// master file, but it could also be another data source with a database
/// backend).  This is why the class has methods like \c load() or \c add().
///
/// This class is non copyable.
class InMemoryZoneFinder : boost::noncopyable, public ZoneFinder {
    ///
    /// \name Constructors and Destructor.
public:
    /// \brief Constructor from zone parameters.
    ///
    /// This constructor internally involves resource allocation, and if
    /// it fails, a corresponding standard exception will be thrown.
    /// It never throws an exception otherwise.
    ///
    /// \param rrclass The RR class of the zone.
    /// \param origin The origin name of the zone.
    InMemoryZoneFinder(const isc::dns::RRClass& rrclass,
                       const isc::dns::Name& origin);

    /// The destructor.
    virtual ~InMemoryZoneFinder();
    //@}

    /// \brief Returns the origin of the zone.
    virtual isc::dns::Name getOrigin() const;

    /// \brief Returns the class of the zone.
    virtual isc::dns::RRClass getClass() const;

    /// \brief Find an RRset in the datasource
    virtual ZoneFinderContextPtr find(const isc::dns::Name& name,
                                      const isc::dns::RRType& type,
                                      const FindOptions options =
                                      FIND_DEFAULT);

    /// \brief Version of find that returns all types at once
    ///
    /// It acts the same as find, just that when the correct node is found,
    /// all the RRsets are filled into the target parameter instead of being
    /// returned by the result.
    virtual ZoneFinderContextPtr findAll(
        const isc::dns::Name& name,
        std::vector<isc::dns::ConstRRsetPtr>& target,
        const FindOptions options = FIND_DEFAULT);

    /// Look for NSEC3 for proving (non)existence of given name.
    ///
    /// See documentation in \c Zone.
    virtual FindNSEC3Result
    findNSEC3(const isc::dns::Name& name, bool recursive);

    /// \brief Inserts an rrset into the zone.
    ///
    /// It puts another RRset into the zone.
    ///
    /// In the current implementation, this method doesn't allow an existing
    /// RRset to be updated or overridden.  So the caller must make sure that
    /// all RRs of the same type and name must be given in the form of a
    /// single RRset.  The current implementation will also require that
    /// when an RRSIG is added the RRset to be covered has already been
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
    result::Result add(const isc::dns::ConstRRsetPtr& rrset);

    /// \brief RRset is NULL exception.
    ///
    /// This is thrown if the provided RRset parameter is NULL.
    struct NullRRset : public InvalidParameter {
        NullRRset(const char* file, size_t line, const char* what) :
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

    /// Return the master file name of the zone
    ///
    /// This method returns the name of the zone's master file to be loaded.
    /// The returned string will be an empty unless the zone finder has
    /// successfully loaded a zone.
    ///
    /// This method should normally not throw an exception.  But the creation
    /// of the return string may involve a resource allocation, and if it
    /// fails, the corresponding standard exception will be thrown.
    ///
    /// \return The name of the zone file loaded in the zone finder, or an empty
    /// string if the zone hasn't loaded any file.
    const std::string getFileName() const;

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
    void load(const std::string& filename);

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
    void load(ZoneIterator& iterator);

    /// Exchanges the content of \c this zone finder with that of the given
    /// \c zone_finder.
    ///
    /// This method never throws an exception.
    ///
    /// \param zone_finder Another \c InMemoryZone object which is to
    /// be swapped with \c this zone finder.
    void swap(InMemoryZoneFinder& zone_finder);

private:
    /// \name Hidden private data
    //@{
    struct InMemoryZoneFinderImpl;
    InMemoryZoneFinderImpl* impl_;
    //@}
    // The friend here is for InMemoryClient::getIterator. The iterator
    // needs to access the data inside the zone, so the InMemoryClient
    // extracts the pointer to data and puts it into the iterator.
    // The access is read only.
    friend class InMemoryClient;

    /// \brief In-memory version of finder context.
    ///
    /// The implementation (and any specialized interface) is completely local
    /// to the InMemoryZoneFinder class, so it's defined as private
    class Context;
};

/// \brief A data source client that holds all necessary data in memory.
///
/// The \c InMemoryClient class provides an access to a conceptual data
/// source that maintains all necessary data in a memory image, thereby
/// allowing much faster lookups.  The in memory data is a copy of some
/// real physical source - in the current implementation a list of zones
/// are populated as a result of \c addZone() calls; zone data is given
/// in a standard master file (but there's a plan to use database backends
/// as a source of the in memory data).
///
/// Although every data source client is assumed to be of the same RR class,
/// the \c InMemoryClient class does not enforce the assumption through
/// its interface.
/// For example, the \c addZone() method does not check if the new zone is of
/// the same RR class as that of the others already in memory.
/// It is caller's responsibility to ensure this assumption.
///
/// <b>Notes to developer:</b>
///
/// The addZone() method takes a (Boost) shared pointer because it would be
/// inconvenient to require the caller to maintain the ownership of zones,
/// while it wouldn't be safe to delete unnecessary zones inside the dedicated
/// backend.
///
/// The findZone() method takes a domain name and returns the best matching
/// \c InMemoryZoneFinder in the form of (Boost) shared pointer, so that it can
/// provide the general interface for all data sources.
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
    InMemoryClient();

    /// The destructor.
    ~InMemoryClient();
    //@}

    /// Return the number of zones stored in the client.
    ///
    /// This method never throws an exception.
    ///
    /// \return The number of zones stored in the client.
    virtual unsigned int getZoneCount() const;

    /// Add a zone (in the form of \c ZoneFinder) to the \c InMemoryClient.
    ///
    /// \c zone_finder must not be associated with a NULL pointer; otherwise
    /// an exception of class \c InvalidParameter will be thrown.
    /// If internal resource allocation fails, a corresponding standard
    /// exception will be thrown.
    /// This method never throws an exception otherwise.
    ///
    /// \param zone_finder A \c ZoneFinder object to be added.
    /// \return \c result::SUCCESS If the zone_finder is successfully
    /// added to the client.
    /// \return \c result::EXIST The memory data source already
    /// stores a zone that has the same origin.
    result::Result addZone(ZoneFinderPtr zone_finder);

    /// Returns a \c ZoneFinder for a zone_finder that best matches the given
    /// name.
    ///
    /// This derived version of the method never throws an exception.
    /// For other details see \c DataSourceClient::findZone().
    virtual FindResult findZone(const isc::dns::Name& name) const;

    /// \brief Implementation of the getIterator method
    virtual ZoneIteratorPtr getIterator(const isc::dns::Name& name,
                                        bool separate_rrs = false) const;

    /// In-memory data source is read-only, so this derived method will
    /// result in a NotImplemented exception.
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
};

/// \brief Creates an instance of the Memory datasource client
///
/// Currently the configuration passed here must be a MapElement, formed as
/// follows:
/// \code
/// { "type": string ("memory"),
///   "class": string ("IN"/"CH"/etc),
///   "zones": list
/// }
/// Zones list is a list of maps:
/// { "origin": string,
///   "file": string
/// }
/// \endcode
/// (i.e. the configuration that was used prior to the datasource refactor)
///
/// This configuration setup is currently under discussion and will change in
/// the near future.
///
/// \param config The configuration for the datasource instance
/// \param error This string will be set to an error message if an error occurs
///              during initialization
/// \return An instance of the memory datasource client, or NULL if there was
///         an error
extern "C" DataSourceClient* createInstance(isc::data::ConstElementPtr config,
                                            std::string& error);

/// \brief Destroy the instance created by createInstance()
extern "C" void destroyInstance(DataSourceClient* instance);


}
}
#endif  // __DATA_SOURCE_MEMORY_H
// Local Variables:
// mode: c++
// End:
