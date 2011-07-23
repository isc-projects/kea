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

namespace isc {
namespace datasrc {

/// \brief TBD
///
/// naming note: somehow redundant with the namespace of "datasrc", but
/// namespaces are often omitted with 'using' directives.  In that case
/// "Client" would be too generic.  So we name it with some redundancy.
/// On the other hand, concrete derived classes are generally not expected
/// to be referenced directly from other modules and applications, so
/// we'll give them more concise names such as InMemoryClient.
///
/// This class is not copyable.
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
    /// \exception
    /// This constructor internally involves resource allocation, and if
    /// it fails, a corresponding standard exception will be thrown.
    /// It never throws an exception otherwise.
    DataSourceClient() {}

public:
    /// The destructor.
    virtual ~DataSourceClient() {}
    //@}

    /// Find a \c Zone that best matches the given name via this client.
    ///
    /// It searches the internal storage for a \c Zone that gives the
    /// longest match against \c name, and returns the result in the
    /// form of a \c FindResult object as follows:
    /// - \c code: The result code of the operation.
    ///   - \c result::SUCCESS: A zone that gives an exact match
    //    is found
    ///   - \c result::PARTIALMATCH: A zone whose origin is a
    //    super domain of \c name is found (but there is no exact match)
    ///   - \c result::NOTFOUND: For all other cases.
    /// - \c zone: Pointer to the found \c ZoneFinder object if one
    //    is found; otherwise \c NULL.
    ///
    /// This method never throws an exception.
    ///
    /// \param name A domain name for which the search is performed.
    /// \return A \c FindResult object enclosing the search result (see above).
    virtual FindResult findZone(const isc::dns::Name& name) const = 0;
};
}
}
#endif  // DATA_SOURCE_CLIENT_H
// Local Variables:
// mode: c++
// End:
