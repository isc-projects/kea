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

#ifndef __ZONETABLE_H
#define __ZONETABLE_H 1

#include <boost/shared_ptr.hpp>

namespace isc {
namespace dns {
class Name;
class RRClass;
};

namespace datasrc {

/// \brief A single authoritative zone
///
/// The \c Zone class represents a DNS zone as part of %data source.
///
/// At the moment this is provided mainly for making the \c ZoneTable class
/// testable, and only provides a minimal set of features.
/// This is why this class is defined in the same header file, but it may
/// have to move to a separate header file when we understand what is
/// necessary for this class for actual operation.
/// Likewise, it will have more features.  For example, it will maintain
/// information about the location of a zone file, whether it's loaded in
/// memory, etc.
class Zone {
    ///
    /// \name Constructors and Destructor.
    ///
    /// \b Note:
    /// The copy constructor and the assignment operator are intentionally
    /// defined as private, making this class non copyable.
    //@{
private:
    Zone(const Zone& source);
    Zone& operator=(const Zone& source);
public:
    /// \brief Constructor from zone parameters.
    ///
    /// This constructor internally involves resource allocation, and if
    /// it fails, a corresponding standard exception will be thrown.
    /// It never throws an exception otherwise.
    ///
    /// \param rrclass The RR class of the zone.
    /// \param origin The origin name of the zone.
    Zone(const isc::dns::RRClass& rrclass, const isc::dns::Name& origin);

    /// The destructor.
    ~Zone();
    //@}

    ///
    /// \name Getter Methods
    ///
    /// These methods never throw an exception.
    //@{
    /// \brief Return the origin name of the zone.
    const isc::dns::Name& getOrigin() const;

    /// \brief Return the RR class of the zone.
    const isc::dns::RRClass& getClass() const;
    //@}

private:
    struct ZoneImpl;
    ZoneImpl* impl_;
};

/// \brief A pointer-like type pointing to a \c Zone object.
typedef boost::shared_ptr<Zone> ZonePtr;

/// \brief A pointer-like type pointing to a \c Zone object.
typedef boost::shared_ptr<const Zone> ConstZonePtr;

/// \brief A set of authoritative zones.
///
/// The \c ZoneTable class represents a set of zones of the same RR class
/// and provides a basic interface to help DNS lookup processing.
/// For a given domain name, its \c find() method searches the set for a zone
/// that gives a longest match against that name.
///
/// The set of zones are assumed to be of the same RR class, but the
/// \c ZoneTable class does not enforce the assumption through its interface.
/// For example, the \c add() method does not check if the new zone
/// is of the same RR class as that of the others already in the table.
/// It is caller's responsibility to ensure this assumption.
///
/// <b>Notes to developer:</b>
///
/// The add() method takes a (Boost) shared pointer because it would be
/// inconvenient to require the caller to maintain the ownership of zones,
/// while it wouldn't be safe to delete unnecessary zones inside the zone
/// table.
///
/// On the other hand, the find() method returns a bare pointer, rather than
/// the shared pointer, in order to minimize the dependency on Boost
/// definitions in our public interfaces.  This means the caller can only
/// refer to the returned object (via the pointer) for a short period.
///  It should be okay for simple lookup purposes, but if we see the need
/// for keeping a \c Zone object for a longer period of context, we may
/// have to revisit this decision.
///
/// Currently, \c FindResult::zone is immutable for safety.
/// In future versions we may want to make it changeable.  For example,
/// we may want to allow configuration update on an existing zone.
///
/// In BIND 9's "zt" module, the equivalent of \c find() has an "option"
/// parameter.  The only defined option is the one to specify the "no exact"
/// mode, and the only purpose of that mode is to prefer a second longest match
/// even if there is an exact match in order to deal with type DS query.
/// This trick may help enhance performance, but it also seems to make the
/// implementation complicated for a very limited, minor case.  So, for now,
/// we don't introduce the special mode, and, since it was the only reason to
/// have search options in BIND 9, our initial implementation doesn't provide
/// a switch for options.
class ZoneTable {
public:
    /// Result codes of various public methods of \c ZoneTable.
    ///
    /// The detailed semantics may differ in different methods.
    /// See the description of specific methods for more details.
    enum Result {
        SUCCESS,  ///< The operation is successful.
        EXIST,    ///< A zone is already stored in \c ZoneTable.
        NOTFOUND, ///< The specified zone is not found in \c ZoneTable.
        PARTIALMATCH ///< \c Only a partial match is found in \c find(). 
    };

    /// \brief A helper structure to represent the search result of
    /// <code>ZoneTable::find()</code>.
    ///
    /// This is a straightforward pair of the result code and a pointer
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
        FindResult(Result param_code, const Zone* param_zone) :
            code(param_code), zone(param_zone)
        {}
        const Result const code;
        const Zone* const zone;
    };

    ///
    /// \name Constructors and Destructor.
    ///
    /// \b Note:
    /// The copy constructor and the assignment operator are intentionally
    /// defined as private, making this class non copyable.
    //@{
private:
    ZoneTable(const ZoneTable& source);
    ZoneTable& operator=(const ZoneTable& source);

public:
    /// Default constructor.
    ///
    /// This constructor internally involves resource allocation, and if
    /// it fails, a corresponding standard exception will be thrown.
    /// It never throws an exception otherwise.
    ZoneTable();

    /// The destructor.
    ~ZoneTable();
    //@}

    /// Add a \c Zone to the \c ZoneTable.
    ///
    /// \c zone must not be associated with a NULL pointer; otherwise
    /// an exception of class \c InvalidParameter will be thrown.
    /// If internal resource allocation fails, a corresponding standard
    /// exception will be thrown.
    /// This method never throws an exception otherwise.
    ///
    /// \param zone A \c Zone object to be added.
    /// \return \c SUCCESS If the zone is successfully added to the zone table.
    /// \return \c EXIST The zone table already stores a zone that has the
    /// same origin.
    Result add(ZonePtr zone);

    /// Remove a \c Zone of the given origin name from the \c ZoneTable.
    ///
    /// This method never throws an exception.
    ///
    /// \param origin The origin name of the zone to be removed.
    /// \return \c SUCCESS If the zone is successfully removed from the
    /// zone table.
    /// \return \c NOTFOUND The zone table does not store the zone that matches
    /// \c origin.
    Result remove(const isc::dns::Name& origin);

    /// Find a \c Zone that best matches the given name in the \c ZoneTable.
    ///
    /// It searches the internal storage for a \c Zone that gives the
    /// longest match against \c origin, and returns the result in the
    /// form of a \c FindResult object as follows:
    /// - \c code: The result code of the operation.
    ///   - \c SUCCESS: A zone that gives an exact match is found
    ///   - \c PARTIALMATCH: A zone whose origin is a super domain of
    ///     \c zone is found (but there is no exact match)
    ///   - \c NOTFOUND: For all other cases.
    /// - \c zone: A pointer to the found \c Zone object if one is found;
    /// otherwise \c NULL.
    ///
    /// The pointer returned in the \c FindResult object is only valid until
    /// the corresponding zone is removed from the zone table.
    /// The caller must ensure that the zone is held in the zone table while
    /// it needs to refer to it.
    ///
    /// This method never throws an exception.
    ///
    /// \param name A domain name for which the search is performed.
    /// \return A \c FindResult object enclosing the search result (see above).
    FindResult find(const isc::dns::Name& name) const;

private:
    struct ZoneTableImpl;
    ZoneTableImpl* impl_;
};
}
}
#endif  // __ZONETABLE_H

// Local Variables:
// mode: c++
// End:
