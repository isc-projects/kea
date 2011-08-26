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

#ifndef __DATA_SOURCE_CLIENT_H
#define __DATA_SOURCE_CLIENT_H 1

#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>

#include <exceptions/exceptions.h>

#include <datasrc/zone.h>

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
/// \todo This class is not complete. It needs more factory methods, for
///     accessing the whole zone, updating it, loading it, etc.
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
    /// \return Pointer to the iterator.
    virtual ZoneIteratorPtr getIterator(const isc::dns::Name& name) const {
        // This is here to both document the parameter in doxygen (therefore it
        // needs a name) and avoid unused parameter warning.
        static_cast<void>(name);

        isc_throw(isc::NotImplemented,
                  "Data source doesn't support iteration");
    }

    /// TBD
    ///
    /// We allow having a read-only data source.  For such data source
    /// this method will result in a NotImplemented exception.
    ///
    /// To avoid throwing the exception accidentally with a lazy
    /// implementation, we still keep this method pure virtual without
    /// an implementation.  All derived classes must explicitly write the
    /// definition of this method, even if it simply throws the NotImplemented
    /// exception.
    virtual ZoneUpdaterPtr startUpdateZone(const isc::dns::Name& name,
                                           bool replace)
        const = 0;
};
}
}
#endif  // DATA_SOURCE_CLIENT_H
// Local Variables:
// mode: c++
// End:
