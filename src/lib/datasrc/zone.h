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

#ifndef __ZONE_H
#define __ZONE_H 1

#include <datasrc/result.h>
#include <dns/rrsetlist.h>

namespace isc {
namespace datasrc {

/// \brief The base class for a single authoritative zone
///
/// The \c Zone class is an abstract base class for representing
/// a DNS zone as part of data source.
///
/// At the moment this is provided mainly for making the \c ZoneTable class
/// and the authoritative query logic testable, and only provides a minimal
/// set of features.
/// This is why this class is defined in the same header file, but it may
/// have to move to a separate header file when we understand what is
/// necessary for this class for actual operation.
///
/// The idea is to provide a specific derived zone class for each data
/// source, beginning with in memory one.  At that point the derived classes
/// will have more specific features.  For example, they will maintain
/// information about the location of a zone file, whether it's loaded in
/// memory, etc.
///
/// It's not yet clear how the derived zone classes work with various other
/// data sources when we integrate these components, but one possibility is
/// something like this:
/// - If the underlying database such as some variant of SQL doesn't have an
///   explicit representation of zones (as part of public interface), we can
///   probably use a "default" zone class that simply encapsulates the
///   corresponding data source and calls a common "find" like method.
/// - Some data source may want to specialize it by inheritance as an
///   optimization.  For example, in the current schema design of the sqlite3
///   data source, its (derived) zone class would contain the information of
///   the "zone ID".
///
/// <b>Note:</b> Unlike some other abstract base classes we don't name the
/// class beginning with "Abstract".  This is because we want to have
/// commonly used definitions such as \c Result and \c ZoneFinderPtr, and we
/// want to make them look more intuitive.
class ZoneFinder {
public:
    /// Result codes of the \c find() method.
    ///
    /// Note: the codes are tentative.  We may need more, or we may find
    /// some of them unnecessary as we implement more details.
    enum Result {
        SUCCESS,                ///< An exact match is found.
        DELEGATION,             ///< The search encounters a zone cut.
        NXDOMAIN, ///< There is no domain name that matches the search name
        NXRRSET,  ///< There is a matching name but no RRset of the search type
        CNAME,    ///< The search encounters and returns a CNAME RR
        DNAME     ///< The search encounters and returns a DNAME RR
    };

    /// A helper structure to represent the search result of \c find().
    ///
    /// This is a straightforward tuple of the result code and a pointer
    /// to the found RRset to represent the result of \c find()
    /// (there will be more members in the future - see the class
    /// description).
    /// We use this in order to avoid overloading the return value for both
    /// the result code ("success" or "not found") and the found object,
    /// i.e., avoid using \c NULL to mean "not found", etc.
    ///
    /// This is a simple value class whose internal state never changes,
    /// so for convenience we allow the applications to refer to the members
    /// directly.
    ///
    /// Note: we should eventually include a notion of "zone node", which
    /// corresponds to a particular domain name of the zone, so that we can
    /// find RRsets of a different RR type for that name (e.g. for type ANY
    /// query or to include DS RRs with delegation).
    ///
    /// Note: we may also want to include the closest enclosure "node" to
    /// optimize including the NSEC for no-wildcard proof (FWIW NSD does that).
    struct FindResult {
        FindResult(Result param_code,
                   const isc::dns::ConstRRsetPtr param_rrset) :
            code(param_code), rrset(param_rrset)
        {}
        const Result code;
        const isc::dns::ConstRRsetPtr rrset;
    };

    /// Find options.
    ///
    /// The option values are used as a parameter for \c find().
    /// These are values of a bitmask type.  Bitwise operations can be
    /// performed on these values to express compound options.
    enum FindOptions {
        FIND_DEFAULT = 0,       ///< The default options
        FIND_GLUE_OK = 1        ///< Allow search under a zone cut
    };

    ///
    /// \name Constructors and Destructor.
    ///
    //@{
protected:
    /// The default constructor.
    ///
    /// This is intentionally defined as \c protected as this base class should
    /// never be instantiated (except as part of a derived class).
    ZoneFinder() {}
public:
    /// The destructor.
    virtual ~ZoneFinder() {}
    //@}

    ///
    /// \name Getter Methods
    ///
    /// These methods should never throw an exception.
    //@{
    /// Return the origin name of the zone.
    virtual isc::dns::Name getOrigin() const = 0;

    /// Return the RR class of the zone.
    virtual isc::dns::RRClass getClass() const = 0;
    //@}

    ///
    /// \name Search Method
    ///
    //@{
    /// Search the zone for a given pair of domain name and RR type.
    ///
    /// Each derived version of this method searches the underlying backend
    /// for the data that best matches the given name and type.
    /// This method is expected to be "intelligent", and identifies the
    /// best possible answer for the search key.  Specifically,
    /// - If the search name belongs under a zone cut, it returns the code
    ///   of \c DELEGATION and the NS RRset at the zone cut.
    /// - If there is no matching name, it returns the code of \c NXDOMAIN,
    ///   and, if DNSSEC is requested, the NSEC RRset that proves the
    ///   non-existence.
    /// - If there is a matching name but no RRset of the search type, it
    ///   returns the code of \c NXRRSET, and, if DNSSEC is required,
    ///   the NSEC RRset for that name.
    /// - If there is a CNAME RR of the searched name but there is no
    ///   RR of the searched type of the name (so this type is different from
    ///   CNAME), it returns the code of \c CNAME and that CNAME RR.
    ///   Note that if the searched RR type is CNAME, it is considered
    ///   a successful match, and the code of \c SUCCESS will be returned.
    /// - If the search name matches a delegation point of DNAME, it returns
    ///   the code of \c DNAME and that DNAME RR.
    /// - If the target isn't NULL, all RRsets under the domain are inserted
    ///   there and SUCCESS (or NXDOMAIN, in case of empty domain) is returned
    ///   instead of normall processing. This is intended to handle ANY query.
    ///   \note: this behavior is controversial as we discussed in
    ///   https://lists.isc.org/pipermail/bind10-dev/2011-January/001918.html
    ///   We should revisit the interface before we heavily rely on it.
    ///
    /// The \c options parameter specifies customized behavior of the search.
    /// Their semantics is as follows:
    /// - \c GLUE_OK Allow search under a zone cut.  By default the search
    ///   will stop once it encounters a zone cut.  If this option is specified
    ///   it remembers information about the highest zone cut and continues
    ///   the search until it finds an exact match for the given name or it
    ///   detects there is no exact match.  If an exact match is found,
    ///   RRsets for that name are searched just like the normal case;
    ///   otherwise, if the search has encountered a zone cut, \c DELEGATION
    ///   with the information of the highest zone cut will be returned.
    ///
    /// A derived version of this method may involve internal resource
    /// allocation, especially for constructing the resulting RRset, and may
    /// throw an exception if it fails.
    /// It throws DuplicateRRset exception if there are duplicate rrsets under
    /// the same domain.
    /// It should not throw other types of exceptions.
    ///
    /// \param name The domain name to be searched for.
    /// \param type The RR type to be searched for.
    /// \param target If target is not NULL, insert all RRs under the domain
    /// into it.
    /// \param options The search options.
    /// \return A \c FindResult object enclosing the search result (see above).
    virtual FindResult find(const isc::dns::Name& name,
                            const isc::dns::RRType& type,
                            isc::dns::RRsetList* target = NULL,
                            const FindOptions options
                            = FIND_DEFAULT) = 0;
    //@}
};

/// \brief A pointer-like type pointing to a \c ZoneFinder object.
typedef boost::shared_ptr<ZoneFinder> ZoneFinderPtr;

/// \brief A pointer-like type pointing to a \c ZoneFinder object.
typedef boost::shared_ptr<const ZoneFinder> ConstZoneFinderPtr;

}
}

#endif  // __ZONE_H

// Local Variables:
// mode: c++
// End:
