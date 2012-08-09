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

#ifndef __DATASRC_MEMORY_ZONE_TABLE_H
#define __DATASRC_MEMORY_ZONE_TABLE_H 1

#include <util/memory_segment.h>

#include <datasrc/result.h>
#include <datasrc/memory/domaintree.h>

namespace isc {
namespace dns {
class Name;
class RRClass;
}

namespace datasrc {
namespace memory {
// forward declaration: in this header it's mostly an opaque type.
class ZoneData;

/// \brief A conceptual table of authoritative zones.
///
/// This class is actually a simple wrapper for a \c DomainTree whose data is
/// of \c ZoneData, and provides allocator, deallocator, and some basic
/// manipulation methods.
///
/// A single \c ZoneData object is intended to be used for a single specific
/// RR class, and provides a mapping from a name to a \c ZoneData (using the
/// best matching search semantics).  The \c ZoneData class itself does not
/// maintain the information of the RR class; the user of this class is
/// responsible for associating a specific RR class to a corresponding
/// \c ZoneData object.
///
/// This class is designed so an instance can be stored in a shared memory
/// region.  So it only contains straightforward data (e.g., it doesn't hold
/// a pointer to an object of some base class that contains virtual methods),
/// and some pointers (either as a direct or indirect member variable) are
/// represented as offset pointers.  For the same reason this class should
/// never has virtual methods (and as a result, should never be inherited
/// in practice).  When this class is extended these properties must be
/// retained.
///
/// This class is intended to be used as a backend for the \c MemoryDataSrc
/// class, and is not intended to be used for other general purposes.
class ZoneTable {
private:
    // The deleter for the zone data stored in the table.
    struct ZoneDataDeleter {
        ZoneDataDeleter() {}
        void operator()(util::MemorySegment& mem_sgmt,
                        ZoneData* zone_data) const;
    };

    // Type aliases to make it shorter
    typedef DomainTree<ZoneData, ZoneDataDeleter> ZoneTableTree;
    typedef DomainTreeNode<ZoneData, ZoneDataDeleter> ZoneTableNode;

public:
    /// \brief Result data of addZone() method.
    struct AddResult {
        AddResult(result::Result param_code, ZoneData* param_zone_data) :
            code(param_code), zone_data(param_zone_data)
        {}
        const result::Result code;
        ZoneData* const zone_data;
    };

    /// \brief Result data of findZone() method.
    struct FindResult {
        FindResult(result::Result param_code,
                   const ZoneData* param_zone_data) :
            code(param_code), zone_data(param_zone_data)
        {}
        const result::Result code;
        const ZoneData* const zone_data;
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

    /// Constructor.
    ///
    /// An object of this class is always expected to be created by the
    /// allocator (\c create()), so the constructor is hidden as private.
    ///
    /// This constructor internally involves resource allocation, and if
    /// it fails, a corresponding standard exception will be thrown.
    /// It never throws an exception otherwise.
    ZoneTable(ZoneTableTree* zones) : zones_(zones)
    {}
    //@}

public:
    /// \brief Allocate and construct \c ZoneTable
    ///
    /// This static method allocates memory for a new \c ZoneTable object
    /// from the given memory segment, constructs the object, and returns
    /// a pointer to it.
    ///
    /// \throw std::bad_alloc Memory allocation fails.
    ///
    /// \param mem_sgmt A \c MemorySegment from which memory for the new
    /// \c ZoneTable is allocated.
    static ZoneTable* create(util::MemorySegment& mem_sgmt);

    /// \brief Destruct and deallocate \c ZoneTable
    ///
    /// \throw none
    ///
    /// \param mem_sgmt The \c MemorySegment that allocated memory for
    /// \c ztable.
    /// \param ztable A non NULL pointer to a valid \c ZoneTable object
    /// that was originally created by the \c create() method (the behavior
    /// is undefined if this condition isn't met).
    static void destroy(util::MemorySegment& mem_sgmt, ZoneTable* ztable);

    /// Add a new zone to the \c ZoneTable.
    ///
    /// This method creates a new \c ZoneData for the given zone name and
    /// holds it in the internal table.  The newly created zone data will be
    /// returned via the \c zone_data member of the return value.  If the given
    /// zone name already exists in the table, a new data object won't be
    /// created; instead, the existing corresponding data will be returned.
    ///
    /// \throw std::bad_alloc Internal resource allocation fails.
    ///
    /// \param zone_name The name of the zone to be added.
    /// \return \c result::SUCCESS If the zone is successfully
    /// added to the zone table.
    /// \return \c result::EXIST The zone table already contains
    /// zone of the same origin.
    AddResult addZone(util::MemorySegment& mem_sgmt,
                      const dns::Name& zone_name);

    /// Find a zone that best matches the given name in the \c ZoneTable.
    ///
    /// It searches the internal storage for a zone that gives the
    /// longest match against \c name, and returns the result in the
    /// form of a \c FindResult object as follows:
    /// - \c code: The result code of the operation.
    ///   - \c result::SUCCESS: A zone that gives an exact match
    ///    is found
    ///   - \c result::PARTIALMATCH: A zone whose origin is a
    ///    super domain of \c name is found (but there is no exact match)
    ///   - \c result::NOTFOUND: For all other cases.
    /// - \c zone_data: corresponding zone data of the found zone; NULL if
    ///   no matching zone is found.
    ///
    /// \throw none
    ///
    /// \param name A domain name for which the search is performed.
    /// \return A \c FindResult object enclosing the search result (see above).
    FindResult findZone(const isc::dns::Name& name) const;

private:
    ZoneTableTree* zones_;
};
}
}
}
#endif  // __DATASRC_MEMORY_ZONE_TABLE_H

// Local Variables:
// mode: c++
// End:
