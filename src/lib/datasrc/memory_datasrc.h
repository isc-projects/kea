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

#ifndef __MEMORY_DATA_SOURCE_H
#define __MEMORY_DATA_SOURCE_H 1

#include <datasrc/zonetable.h>

namespace isc {
namespace dns {
class Name;
};

namespace datasrc {

/// A derived zone class intended to be used with the memory data source.
class MemoryZone : public Zone {
    ///
    /// \name Constructors and Destructor.
    ///
    /// \b Note:
    /// The copy constructor and the assignment operator are intentionally
    /// defined as private, making this class non copyable.
    //@{
private:
    MemoryZone(const MemoryZone& source);
    MemoryZone& operator=(const MemoryZone& source);
public:
    /// \brief Constructor from zone parameters.
    ///
    /// This constructor internally involves resource allocation, and if
    /// it fails, a corresponding standard exception will be thrown.
    /// It never throws an exception otherwise.
    ///
    /// \param rrclass The RR class of the zone.
    /// \param origin The origin name of the zone.
    MemoryZone(const isc::dns::RRClass& rrclass, const isc::dns::Name& origin);

    /// The destructor.
    virtual ~MemoryZone();
    //@}

    /// \brief Returns the origin of the zone.
    virtual const isc::dns::Name& getOrigin() const;
    /// \brief Returns the class of the zone.
    virtual const isc::dns::RRClass& getClass() const;
    /// \brief Looks up an RRset in the zone.
    ///
    ///
    /// See documentation in \c Zone.
    ///
    /// It returns NULL pointer in case of NXDOMAIN and NXRRSET
    /// (the base class documentation does not seem to require that).
    ///
    /// It might throw AssertError as well, but it should not be
    /// expected (and caught), as it marks programmer error.
    virtual FindResult find(const isc::dns::Name& name,
                            const isc::dns::RRType& type) const;

    /// \brief Inserts an rrset into the zone.
    ///
    /// It puts another RRset into the zone.
    ///
    /// It throws NullRRset or OutOfZone if the provided rrset is invalid.
    /// It might throw AssertError, but that one marks programmer errors.
    ///
    /// \param rrset The set to add.
    /// \return SUCCESS or EXIST (if an rrset for given name and type already
    ///    exists).
    result::Result add(const isc::dns::ConstRRsetPtr& rrset);

    /// \brief RRSet out of zone exception.
    ///
    /// This is thrown if addition of an RRset that doesn't belong under the
    /// zone's origin is requested.
    struct OutOfZone : public InvalidParameter {
        OutOfZone(const char* file, size_t line, const char* what) :
            InvalidParameter(file, line, what)
        { }
    };

    /// \brief RRset is NULL exception.
    ///
    /// This is thrown if the provided RRset parameter is NULL.
    struct NullRRset : public InvalidParameter {
        NullRRset(const char* file, size_t line, const char* what) :
            InvalidParameter(file, line, what)
        { }
    };

    /// \brief Internal programmer error.
    ///
    /// This should not be expected. It means internal inconsistency is
    /// detected, eg. it marks the "Can Not Happen" conditions.
    struct AssertError : public Unexpected {
        AssertError(const char* file, size_t line, const char* what) :
            Unexpected(file, line, what)
        { }
    };

private:
    /// \name Hidden private data
    //@{
    struct MemoryZoneImpl;
    MemoryZoneImpl* impl_;
    //@}
};

/// \brief A data source that uses in memory dedicated backend.
///
/// The \c MemoryDataSrc class represents a data source and provides a
/// basic interface to help DNS lookup processing. For a given domain
/// name, its \c findZone() method searches the in memory dedicated backend
/// for the zone that gives a longest match against that name.
///
/// The in memory dedicated backend are assumed to be of the same RR class,
/// but the \c MemoryDataSrc class does not enforce the assumption through
/// its interface.
/// For example, the \c addZone() method does not check if the new zone is of
/// the same RR class as that of the others already in the dedicated backend.
/// It is caller's responsibility to ensure this assumption.
///
/// <b>Notes to developer:</b>
///
/// For now, we don't make it a derived class of AbstractDataSrc because the
/// interface is so different (we'll eventually consider this as part of the
/// generalization work).
///
/// The addZone() method takes a (Boost) shared pointer because it would be
/// inconvenient to require the caller to maintain the ownership of zones,
/// while it wouldn't be safe to delete unnecessary zones inside the dedicated
/// backend.
///
/// The findZone() method takes a domain name and returns the best matching \c
/// MemoryZone in the form of (Boost) shared pointer, so that it can provide
/// the general interface for all data sources.
///
/// Currently, \c FindResult::zone is immutable for safety.
/// In future versions we may want to make it changeable.  For example,
/// we may want to allow configuration update on an existing zone.
class MemoryDataSrc {
public:
    /// \brief A helper structure to represent the search result of
    /// <code>MemoryDataSrc::find()</code>.
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
        FindResult(result::Result param_code, const ConstZonePtr param_zone) :
            code(param_code), zone(param_zone)
        {}
        const result::Result code;
        const ConstZonePtr zone;
    };

    ///
    /// \name Constructors and Destructor.
    ///
    /// \b Note:
    /// The copy constructor and the assignment operator are intentionally
    /// defined as private, making this class non copyable.
    //@{
private:
    MemoryDataSrc(const MemoryDataSrc& source);
    MemoryDataSrc& operator=(const MemoryDataSrc& source);

public:
    /// Default constructor.
    ///
    /// This constructor internally involves resource allocation, and if
    /// it fails, a corresponding standard exception will be thrown.
    /// It never throws an exception otherwise.
    MemoryDataSrc();

    /// The destructor.
    ~MemoryDataSrc();
    //@}

    /// Add a \c Zone to the \c MemoryDataSrc.
    ///
    /// \c Zone must not be associated with a NULL pointer; otherwise
    /// an exception of class \c InvalidParameter will be thrown.
    /// If internal resource allocation fails, a corresponding standard
    /// exception will be thrown.
    /// This method never throws an exception otherwise.
    ///
    /// \param zone A \c Zone object to be added.
    /// \return \c result::SUCCESS If the zone is successfully
    /// added to the memory data source.
    /// \return \c result::EXIST The memory data source already
    /// stores a zone that has the same origin.
    result::Result addZone(ZonePtr zone);

    /// Find a \c Zone that best matches the given name in the \c MemoryDataSrc.
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
    /// - \c zone: A <Boost> shared pointer to the found \c Zone object if one
    //  is found; otherwise \c NULL.
    ///
    /// This method never throws an exception.
    ///
    /// \param name A domain name for which the search is performed.
    /// \return A \c FindResult object enclosing the search result (see above).
    FindResult findZone(const isc::dns::Name& name) const;

private:
    struct MemoryDataSrcImpl;
    MemoryDataSrcImpl* impl_;
};
}
}
#endif  // __DATA_SOURCE_MEMORY_H
// Local Variables:
// mode: c++
// End:
