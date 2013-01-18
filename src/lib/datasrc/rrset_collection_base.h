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

#ifndef RRSET_COLLECTION_DATASRC_H
#define RRSET_COLLECTION_DATASRC_H 1

#include <dns/rrset_collection_base.h>
#include <dns/rrclass.h>
#include <datasrc/zone.h>

namespace isc {
namespace datasrc {

/// \brief A forward declaration
class ZoneUpdater;

/// \brief datasrc derivation of \c isc::dns::RRsetCollectionBase.
///
/// This is an abstract class that adds datasrc related detail to
/// \c isc::dns::RRsetCollectionBase. Derived classes need to complete
/// the implementation (add iterator support, etc.) before using it.
class RRsetCollectionBase : public isc::dns::RRsetCollectionBase {
public:
    /// \brief Constructor.
    ///
    /// No reference (count via \c shared_ptr) to the \c ZoneUpdater is
    /// acquired. The RRsetCollection must not be used after its
    /// \c ZoneUpdater has been destroyed.
    ///
    /// \param updater The ZoneUpdater to wrap around.
    /// \param rrclass The RRClass of the records in the zone.
    RRsetCollectionBase(ZoneUpdater& updater,
                        const isc::dns::RRClass& rrclass) :
        updater_(updater),
        rrclass_(rrclass),
        disabled_(false)
    {}

    /// \brief Destructor
    virtual ~RRsetCollectionBase() {}

    /// \brief Find a matching RRset in the collection.
    ///
    /// Returns the RRset in the collection that exactly matches the
    /// given \c name, \c rrclass and \c rrtype.  If no matching RRset
    /// is found, \c NULL is returned.
    ///
    /// Note that not all records added through the updater may
    /// necessarily be found by this method, such as RRs subject to
    /// DNAME substitution.
    ///
    /// \throw isc::dns::RRsetCollectionError if \c find() results in
    /// some underlying datasrc error, or if \c disable() was called.
    ///
    /// \param name The name of the RRset to search for.
    /// \param rrclass The class of the RRset to search for.
    /// \param rrtype The type of the RRset to search for.
    /// \returns The RRset if found, \c NULL otherwise.
    virtual isc::dns::ConstRRsetPtr find(const isc::dns::Name& name,
                                         const isc::dns::RRClass& rrclass,
                                         const isc::dns::RRType& rrtype) const;

protected:
    /// \brief Disable the RRsetCollection.
    ///
    /// After calling this method, calling operations such as find() or
    /// using the iterator would result in an \c
    /// isc::dns::RRsetCollectionError. This method is typically called
    /// in the \c commit() implementations of some \c ZoneUpdaters.
    void disable() {
        disabled_ = true;
    }

    /// \brief Return if the RRsetCollection is disabled.
    bool isDisabled() const {
        return (disabled_);
    }

    /// \brief See \c isc::dns::RRsetCollectionBase::getBeginning() for
    /// documentation.
    ///
    /// \throw isc::dns::RRsetCollectionError if using the iterator
    /// results in some underlying datasrc error, or if \c disable() was
    /// called.
    virtual IterPtr getBeginning() = 0;

    /// \brief See \c isc::dns::RRsetCollectionBase::getEnd() for
    /// documentation.
    ///
    /// \throw isc::dns::RRsetCollectionError if using the iterator
    /// results in some underlying datasrc error, or if \c disable() was
    /// called.
    virtual IterPtr getEnd() = 0;

private:
    ZoneUpdater& updater_;
    isc::dns::RRClass rrclass_;
    bool disabled_;
};

} // end of namespace datasrc
} // end of namespace isc

#endif  // RRSET_COLLECTION_DATASRC_H

// Local Variables:
// mode: c++
// End:
