// Copyright (C) 2013  Internet Systems Consortium, Inc. ("ISC")
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

#ifndef RRSET_COLLECTION_DATASRC_MEMORY_H
#define RRSET_COLLECTION_DATASRC_MEMORY_H 1

#include <dns/rrset_collection_base.h>
#include <dns/rrclass.h>

#include <datasrc/memory/zone_data.h>

namespace isc {
namespace datasrc {
namespace memory {

/// \brief In-memory derivation of \c isc::dns::RRsetCollectionBase.
class RRsetCollection : public isc::dns::RRsetCollectionBase {
public:
    /// \brief Constructor.
    ///
    /// No reference (count via \c shared_ptr) to the \c ZoneData is
    /// acquired. The RRsetCollection must not be used after its
    /// \c ZoneData has been destroyed.
    ///
    /// \param zone_data The ZoneData to wrap around.
    /// \param rrclass The RRClass of the records in the zone.
    RRsetCollection(ZoneData& zone_data, const isc::dns::RRClass& rrclass) :
        zone_data_(zone_data),
        rrclass_(rrclass)
    {}

    /// \brief Destructor
    virtual ~RRsetCollection() {}

    /// \brief Find a matching RRset in the collection.
    ///
    /// Returns the RRset in the collection that exactly matches the
    /// given \c name, \c rrclass and \c rrtype.  If no matching RRset
    /// is found, \c NULL is returned.
    ///
    /// \throw isc::dns::RRsetCollectionError if \c find() results in
    /// some underlying error.
    ///
    /// \param name The name of the RRset to search for.
    /// \param rrclass The class of the RRset to search for.
    /// \param rrtype The type of the RRset to search for.
    /// \returns The RRset if found, \c NULL otherwise.
    virtual isc::dns::ConstRRsetPtr find(const isc::dns::Name& name,
                                         const isc::dns::RRClass& rrclass,
                                         const isc::dns::RRType& rrtype) const;

protected:
    virtual RRsetCollectionBase::IterPtr getBeginning() {
        isc_throw(NotImplemented, "This method is not implemented.");
    }

    virtual RRsetCollectionBase::IterPtr getEnd() {
        isc_throw(NotImplemented, "This method is not implemented.");
    }

private:
    ZoneData& zone_data_;
    isc::dns::RRClass rrclass_;
};

} // end of namespace memory
} // end of namespace datasrc
} // end of namespace isc

#endif  // RRSET_COLLECTION_DATASRC_MEMORY_H

// Local Variables:
// mode: c++
// End:
