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

#include <dns/rrset.h>

#include <datasrc/zone.h>

namespace isc {
namespace dns {
class Name;
class RRClass;
};

namespace datasrc {

/// A derived zone class intended to be used with the memory data source.
///
/// Currently this is almost empty and is only used for testing the
/// \c ZoneTable class.  It will be substantially expanded, and will probably
/// moved to a separate header file.
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

    virtual const isc::dns::Name& getOrigin() const;
    virtual const isc::dns::RRClass& getClass() const;
    virtual FindResult find(const isc::dns::Name& name,
                            const isc::dns::RRType& type) const;

private:
    struct MemoryZoneImpl;
    MemoryZoneImpl* impl_;
};

/// \brief A set of authoritative zones.
///
/// \c ZoneTable class is primarily intended to be used as a backend for the
/// \c MemoryDataSrc class, but is exposed as a separate class in case some
/// application wants to use it directly (e.g. for a customized data source
/// implementation).
///
/// For more descriptions about its struct and interfaces, please refer to the
/// corresponding struct and interfaces of \c MemoryDataSrc.
class ZoneTable {
public:
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
    /// See the description of <code>MemoryDataSrc::addZone()</code> for more
    /// details.
    result::Result addZone(ZonePtr zone);

    /// Remove a \c Zone of the given origin name from the \c ZoneTable.
    ///
    /// This method never throws an exception.
    ///
    /// \param origin The origin name of the zone to be removed.
    /// \return \c result::SUCCESS If the zone is successfully
    /// removed from the zone table.
    /// \return \c result::NOTFOUND The zone table does not
    /// store the zone that matches \c origin.
    result::Result removeZone(const isc::dns::Name& origin);

    /// Find a \c Zone that best matches the given name in the \c ZoneTable.
    /// See the description of <code>MemoryDataSrc::findZone()</code> for more
    /// details.
    FindResult findZone(const isc::dns::Name& name) const;

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
