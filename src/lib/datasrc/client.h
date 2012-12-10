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

#ifndef DATA_SOURCE_CLIENT_H
#define DATA_SOURCE_CLIENT_H 1

#include <utility>

#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>

#include <exceptions/exceptions.h>

#include <datasrc/zone.h>

/// \file
/// Datasource clients
///
/// The data source client API is specified in client.h, and provides the
/// functionality to query and modify data in the data sources. There are
/// multiple datasource implementations, and by subclassing DataSourceClient or
/// DatabaseClient, more can be added.
///
/// All datasources are implemented as loadable modules, with a name of the
/// form "<type>_ds.so". This has been chosen intentionally, to minimize
/// confusion and potential mistakes.
///
/// In order to use a datasource client backend, the class
/// DataSourceClientContainer is provided in factory.h; this will load the
/// library, set up the instance, and clean everything up once it is destroyed.
///
/// Access to the actual instance is provided with the getInstance() method
/// in DataSourceClientContainer
///
/// \note Depending on actual usage, we might consider making the container
/// a transparent abstraction layer, so it can be used as a DataSourceClient
/// directly. This has some other implications though so for now the only access
/// provided is through getInstance()).
///
/// For datasource backends, we use a dynamically loaded library system (with
/// dlopen()). This library must contain the following things;
/// - A subclass of DataSourceClient or DatabaseClient (which itself is a
///   subclass of DataSourceClient)
/// - A creator function for an instance of that subclass, of the form:
/// \code
/// extern "C" DataSourceClient* createInstance(isc::data::ConstElementPtr cfg);
/// \endcode
/// - A destructor for said instance, of the form:
/// \code
/// extern "C" void destroyInstance(isc::data::DataSourceClient* instance);
/// \endcode
///
/// See the documentation for the \link DataSourceClient \endlink class for
/// more information on implementing subclasses of it.
///

namespace isc {
namespace datasrc {

// The iterator.h is not included on purpose, most application won't need it
class ZoneIterator;
typedef boost::shared_ptr<ZoneIterator> ZoneIteratorPtr;

/// \brief The base class of data source clients.
///
/// This is an abstract base class that defines the common interface for
/// various types of data source clients.  A data source client is a top level
/// access point to a data source, allowing various operations on the data
/// source such as lookups, traversing or updates.  The client class itself
/// has limited focus and delegates the responsibility for these specific
/// operations to other classes; in general methods of this class act as
/// factories of these other classes.
///
/// See \link datasrc/client.h datasrc/client.h \endlink for more information
/// on adding datasource implementations.
///
/// The following derived classes are currently (expected to be) provided:
/// - \c InMemoryClient: A client of a conceptual data source that stores
/// all necessary data in memory for faster lookups
/// - \c DatabaseClient: A client that uses a real database backend (such as
/// an SQL database).  It would internally hold a connection to the underlying
/// database system.
///
/// \note It is intentional that while the term these derived classes don't
/// contain "DataSource" unlike their base class.  It's also noteworthy
/// that the naming of the base class is somewhat redundant because the
/// namespace \c datasrc would indicate that it's related to a data source.
/// The redundant naming comes from the observation that namespaces are
/// often omitted with \c using directives, in which case "Client"
/// would be too generic.  On the other hand, concrete derived classes are
/// generally not expected to be referenced directly from other modules and
/// applications, so we'll give them more concise names such as InMemoryClient.
///
/// A single \c DataSourceClient object is expected to handle only a single
/// RR class even if the underlying data source contains records for multiple
/// RR classes.  Likewise, (when we support views) a \c DataSourceClient
/// object is expected to handle only a single view.
///
/// If the application uses multiple threads, each thread will need to
/// create and use a separate DataSourceClient.  This is because some
/// database backend doesn't allow multiple threads to share the same
/// connection to the database.
///
/// \note For a client using an in memory backend, this may result in
/// having a multiple copies of the same data in memory, increasing the
/// memory footprint substantially.  Depending on how to support multiple
/// CPU cores for concurrent lookups on the same single data source (which
/// is not fully fixed yet, and for which multiple threads may be used),
/// this design may have to be revisited.
///
/// This class (and therefore its derived classes) are not copyable.
/// This is because the derived classes would generally contain attributes
/// that are not easy to copy (such as a large size of in memory data or a
/// network connection to a database server).  In order to avoid a surprising
/// disruption with a naive copy it's prohibited explicitly.  For the expected
/// usage of the client classes the restriction should be acceptable.
///
/// \todo This class is still not complete. It will need more factory methods,
/// e.g. for (re)loading a zone.
class DataSourceClient : boost::noncopyable {
public:
    /// \brief A helper structure to represent the search result of
    /// \c find().
    ///
    /// This is a straightforward pair of the result code and a share pointer
    /// to the found zone to represent the result of \c find().
    /// We use this in order to avoid overloading the return value for both
    /// the result code ("success" or "not found") and the found object,
    /// i.e., avoid using \c NULL to mean "not found", etc.
    ///
    /// This is a simple value class with no internal state, so for
    /// convenience we allow the applications to refer to the members
    /// directly.
    ///
    /// See the description of \c find() for the semantics of the member
    /// variables.
    struct FindResult {
        FindResult(result::Result param_code,
                   const ZoneFinderPtr param_zone_finder) :
            code(param_code), zone_finder(param_zone_finder)
        {}
        const result::Result code;
        const ZoneFinderPtr zone_finder;
    };

    ///
    /// \name Constructors and Destructor.
    ///
protected:
    /// Default constructor.
    ///
    /// This is intentionally defined as protected as this base class
    /// should never be instantiated directly.
    ///
    /// The constructor of a concrete derived class may throw an exception.
    /// This interface does not specify which exceptions can happen (at least
    /// at this moment), and the caller should expect any type of exception
    /// and react accordingly.
    DataSourceClient() {}

public:
    /// The destructor.
    virtual ~DataSourceClient() {}
    //@}

    /// Returns a \c ZoneFinder for a zone that best matches the given name.
    ///
    /// A concrete derived version of this method gets access to its backend
    /// data source to search for a zone whose origin gives the longest match
    /// against \c name.  It returns the search result in the form of a
    /// \c FindResult object as follows:
    /// - \c code: The result code of the operation.
    ///   - \c result::SUCCESS: A zone that gives an exact match is found
    ///   - \c result::PARTIALMATCH: A zone whose origin is a
    ///   super domain of \c name is found (but there is no exact match)
    ///   - \c result::NOTFOUND: For all other cases.
    /// - \c zone_finder: Pointer to a \c ZoneFinder object for the found zone
    /// if one is found; otherwise \c NULL.
    ///
    /// A specific derived version of this method may throw an exception.
    /// This interface does not specify which exceptions can happen (at least
    /// at this moment), and the caller should expect any type of exception
    /// and react accordingly.
    ///
    /// \param name A domain name for which the search is performed.
    /// \return A \c FindResult object enclosing the search result (see above).
    virtual FindResult findZone(const isc::dns::Name& name) const = 0;

    /// \brief Returns an iterator to the given zone
    ///
    /// This allows for traversing the whole zone. The returned object can
    /// provide the RRsets one by one.
    ///
    /// This throws DataSourceError when the zone does not exist in the
    /// datasource.
    ///
    /// The default implementation throws isc::NotImplemented. This allows
    /// for easy and fast deployment of minimal custom data sources, where
    /// the user/implementator doesn't have to care about anything else but
    /// the actual queries. Also, in some cases, it isn't possible to traverse
    /// the zone from logic point of view (eg. dynamically generated zone
    /// data).
    ///
    /// It is not fixed if a concrete implementation of this method can throw
    /// anything else.
    ///
    /// \param name The name of zone apex to be traversed. It doesn't do
    ///     nearest match as findZone.
    /// \param separate_rrs If true, the iterator will return each RR as a
    ///                     new RRset object. If false, the iterator will
    ///                     combine consecutive RRs with the name and type
    ///                     into 1 RRset. The capitalization of the RRset will
    ///                     be that of the first RR read, and TTLs will be
    ///                     adjusted to the lowest one found.
    /// \return Pointer to the iterator.
    virtual ZoneIteratorPtr getIterator(const isc::dns::Name& name,
                                        bool separate_rrs = false) const {
        // This is here to both document the parameter in doxygen (therefore it
        // needs a name) and avoid unused parameter warning.
        static_cast<void>(name);
        static_cast<void>(separate_rrs);

        isc_throw(isc::NotImplemented,
                  "Data source doesn't support iteration");
    }

    /// Return an updater to make updates to a specific zone.
    ///
    /// The RR class of the zone is the one that the client is expected to
    /// handle (see the detailed description of this class).
    ///
    /// If the specified zone is not found via the client, a NULL pointer
    /// will be returned; in other words a completely new zone cannot be
    /// created using an updater.  It must be created beforehand (even if
    /// it's an empty placeholder) in a way specific to the underlying data
    /// source.
    ///
    /// Conceptually, the updater will trigger a separate transaction for
    /// subsequent updates to the zone within the context of the updater
    /// (the actual implementation of the "transaction" may vary for the
    /// specific underlying data source).  Until \c commit() is performed
    /// on the updater, the intermediate updates won't affect the results
    /// of other methods (and the result of the object's methods created
    /// by other factory methods).  Likewise, if the updater is destructed
    /// without performing \c commit(), the intermediate updates will be
    /// effectively canceled and will never affect other methods.
    ///
    /// If the underlying data source allows concurrent updates, this method
    /// can be called multiple times while the previously returned updater(s)
    /// are still active.  In this case each updater triggers a different
    /// "transaction".  Normally it would be for different zones for such a
    /// case as handling multiple incoming AXFR streams concurrently, but
    /// this interface does not even prohibit an attempt of getting more than
    /// one updater for the same zone, as long as the underlying data source
    /// allows such an operation (and any conflict resolution is left to the
    /// specific derived class implementation).
    ///
    /// If \c replace is true, any existing RRs of the zone will be
    /// deleted on successful completion of updates (after \c commit() on
    /// the updater); if it's false, the existing RRs will be
    /// intact unless explicitly deleted by \c deleteRRset() on the updater.
    ///
    /// A data source can be "read only" or can prohibit partial updates.
    /// In such cases this method will result in an \c isc::NotImplemented
    /// exception unconditionally or when \c replace is false).
    ///
    /// If \c journaling is true, the data source should store a journal
    /// of changes. These can be used later on by, for example, IXFR-out.
    /// However, the parameter is a hint only. It might be unable to store
    /// them and they would be silently discarded. Or it might need to
    /// store them no matter what (for example a git-based data source would
    /// store journal implicitly). When the \c journaling is true, it
    /// requires that the following update be formatted as IXFR transfer
    /// (SOA to be removed, bunch of RRs to be removed, SOA to be added,
    /// bunch of RRs to be added, and possibly repeated). However, it is not
    /// required that the updater checks that. If it is false, it must not
    /// require so and must accept any order of changes.
    ///
    /// We don't support erasing the whole zone (by replace being true) and
    /// saving a journal at the same time. In such situation, BadValue is
    /// thrown.
    ///
    /// \note To avoid throwing the exception accidentally with a lazy
    /// implementation, we still keep this method pure virtual without
    /// an implementation.  All derived classes must explicitly define this
    /// method, even if it simply throws the NotImplemented exception.
    ///
    /// \exception NotImplemented The underlying data source does not support
    /// updates.
    /// \exception DataSourceError Internal error in the underlying data
    /// source.
    /// \exception std::bad_alloc Resource allocation failure.
    /// \exception BadValue if both replace and journaling are true.
    ///
    /// \param name The zone name to be updated
    /// \param replace Whether to delete existing RRs before making updates
    /// \param journaling The zone updater should store a journal of the
    ///     changes.
    ///
    /// \return A pointer to the updater; it will be NULL if the specified
    /// zone isn't found.
    virtual ZoneUpdaterPtr getUpdater(const isc::dns::Name& name,
                                      bool replace, bool journaling = false)
        const = 0;

    /// Return a journal reader to retrieve differences of a zone.
    ///
    /// A derived version of this method creates a concrete
    /// \c ZoneJournalReader object specific to the underlying data source
    /// for the specified name of zone and differences between the versions
    /// specified by the beginning and ending serials of the corresponding
    /// SOA RRs.
    /// The RR class of the zone is the one that the client is expected to
    /// handle (see the detailed description of this class).
    ///
    /// Note that the SOA serials are compared by the semantics of the serial
    /// number arithmetic.  So, for example, \c begin_serial can be larger than
    /// \c end_serial as bare unsigned integers.  The underlying data source
    /// implementation is assumed to keep track of sufficient history to
    /// identify (if exist) the corresponding difference between the specified
    /// versions.
    ///
    /// This method returns the result as a pair of a result code and
    /// a pointer to a \c ZoneJournalReader object.  On success, the result
    /// code is \c SUCCESS and the pointer must be non NULL; otherwise
    /// the result code is something other than \c SUCCESS and the pinter
    /// must be NULL.
    ///
    /// If the specified zone is not found in the data source, the result
    /// code is \c NO_SUCH_ZONE.
    /// Otherwise, if specified range of difference for the zone is not found
    /// in the data source, the result code is \c NO_SUCH_VERSION.
    ///
    /// Handling differences is an optional feature of data source.
    /// If the underlying data source does not support difference handling,
    /// this method for that type of data source can throw an exception of
    /// class \c NotImplemented.
    ///
    /// \exception NotImplemented The data source does not support differences.
    /// \exception DataSourceError Other operational errors at the data source
    /// level.
    ///
    /// \param zone The name of the zone for which the difference should be
    /// retrieved.
    /// \param begin_serial The SOA serial of the beginning version of the
    /// differences.
    /// \param end_serial The SOA serial of the ending version of the
    /// differences.
    ///
    /// \return A pair of result code and a pointer to \c ZoneJournalReader.
    virtual std::pair<ZoneJournalReader::Result, ZoneJournalReaderPtr>
    getJournalReader(const isc::dns::Name& zone, uint32_t begin_serial,
                     uint32_t end_serial) const = 0;

    /// Return the number of zones currently known to this datasource
    ///
    /// This is an optional convenience method, currently only implemented
    /// by the InMemory datasource. By default, it throws NotImplemented
    ///
    /// \exception NotImplemented Thrown if this method is not supported
    ///            by the datasource
    ///
    /// \note This is a tentative API, and this method may likely to be
    ///       removed in the near future.
    /// \return The number of zones known to this datasource
    virtual unsigned int getZoneCount() const {
        isc_throw(isc::NotImplemented,
                  "Data source doesn't support getZoneCount");
    }

    // It first checks if the specified name of the zone exists.  If it
    // exists it returns false; otherwise it adds information of the
    // new zone in backend-dependent manner and returns true.
    // The DB-based version of this method would perform the check and add in
    // a single transaction.
    //
    // Throws on any unexpected failure.
    // Default implementation throws isc::NotImplemented

    virtual bool createZone(const dns::Name&) {
        isc_throw(isc::NotImplemented,
                  "Data source doesn't support addZone");
    };
};
}
}
#endif  // DATA_SOURCE_CLIENT_H
// Local Variables:
// mode: c++
// End:
