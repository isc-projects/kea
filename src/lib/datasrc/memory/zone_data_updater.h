// Copyright (C) 2012  Internet Systems Consortium, Inc. ("ISC")
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

#ifndef DATASRC_ZONE_DATA_UPDATER_H
#define DATASRC_ZONE_DATA_UPDATER_H 1

#include <datasrc/exceptions.h>
#include <datasrc/memory/zone_data.h>
#include <datasrc/memory/rdata_serialization.h>
#include <dns/name.h>
#include <dns/rrclass.h>
#include <dns/rrset.h>
#include <dns/nsec3hash.h>
#include <util/memory_segment.h>

#include <boost/noncopyable.hpp>

namespace isc {
namespace datasrc {
namespace memory {

/// \brief A helper class to add records to a zone.
///
/// This class provides an \c add() method that can be used to add
/// RRsets to a ZoneData instance. The RRsets are first validated for
/// correctness and consistency, and their data is made into RdataSets
/// which are added to the ZoneData for the zone.
///
/// The way to use this is to make a ZoneDataUpdater instance, and call
/// add() on it as follows:
///
/// \code
/// ZoneDataUpdater updater(mem_sgmt, rrclass, zone_origin_name, zone_data);
/// ConstRRsetPtr rrset;
/// updater.add(rrset, ConstRRsetPtr());
/// \endcode
///
/// We enforce that instances are non-copyable as it's pointless to make
/// copies.
class ZoneDataUpdater : boost::noncopyable {
public:
    ///
    /// \name Constructors and Destructor.
    ///
    //@{

    /// The constructor.
    ///
    /// \throw none
    ///
    /// \param mem_sgmt The memory segment used for the zone data.
    /// \param rrclass The RRclass of the zone data.
    /// \param zone_name The Name of the zone under which records will be
    ///                  added.
    //  \param zone_data The ZoneData object which is populated with
    //                   record data.
    ZoneDataUpdater(util::MemorySegment& mem_sgmt,
                    isc::dns::RRClass rrclass,
                    const isc::dns::Name& zone_name,
                    ZoneData& zone_data) :
       mem_sgmt_(mem_sgmt),
       rrclass_(rrclass),
       zone_name_(zone_name),
       zone_data_(zone_data),
       hash_(NULL)
    {}

    /// The destructor.
    ~ZoneDataUpdater() {
        delete hash_;
    }

    //@}

    /// This is thrown if the provided RRset parameter passed to \c
    /// add() is NULL.
    struct NullRRset : public InvalidParameter {
        NullRRset(const char* file, size_t line, const char* what) :
            InvalidParameter(file, line, what)
        {}
    };

    /// \brief General failure exception for \c add().
    ///
    /// This is thrown against general error cases in adding an RRset
    /// to the zone.
    struct AddError : public ZoneLoaderException {
        AddError(const char* file, size_t line, const char* what) :
            ZoneLoaderException(file, line, what)
        {}
    };

    /// \brief Add an RRset to the zone.
    ///
    /// This is the core method of this class. It is used to add an
    /// RRset to the ZoneData associated with this object. The RRset is
    /// first validated for correctness and consistency with the rest of
    /// the records in the zone, and then an RdataSet is created and
    /// populated with the record data and added to the ZoneData for the
    /// name in the RRset.
    ///
    /// This method throws an \c NullRRset exception (see above) if
    /// \c rrset is empty. It throws \c AddError if any of a variety of
    /// validation checks fail for the \c rrset and its associated
    /// \c sig_rrset.
    ///
    /// \param rrset The RRset to be added.
    /// \param sig_rrset An associated RRSIG RRset for the \c rrset. It
    ///                  can be empty if there is no RRSIG for the \c rrset.
    void add(const isc::dns::ConstRRsetPtr& rrset,
             const isc::dns::ConstRRsetPtr& sig_rrset);

private:
    // Add the necessary magic for any wildcard contained in 'name'
    // (including itself) to be found in the zone.
    //
    // In order for wildcard matching to work correctly in the zone finder,
    // we must ensure that a node for the wildcarding level exists in the
    // backend ZoneTree.
    // E.g. if the wildcard name is "*.sub.example." then we must ensure
    // that "sub.example." exists and is marked as a wildcard level.
    // Note: the "wildcarding level" is for the parent name of the wildcard
    // name (such as "sub.example.").
    //
    // We also perform the same trick for empty wild card names possibly
    // contained in 'name' (e.g., '*.foo.example' in 'bar.*.foo.example').
    void addWildcards(const isc::dns::Name& name);

    // Does some checks in context of the data that are already in the
    // zone.  Currently checks for forbidden combinations of RRsets in
    // the same domain (CNAME+anything, DNAME+NS).  If such condition is
    // found, it throws AddError.
    void contextCheck(const isc::dns::AbstractRRset& rrset,
                      const RdataSet* set) const;

    // Validate rrset before adding it to the zone.  If something is wrong
    // it throws an exception.  It doesn't modify the zone, and provides
    // the strong exception guarantee.
    void validate(const isc::dns::ConstRRsetPtr rrset) const;

    const isc::dns::NSEC3Hash* getNSEC3Hash();
    template <typename T>
    void setupNSEC3(const isc::dns::ConstRRsetPtr rrset);
    void addNSEC3(const isc::dns::ConstRRsetPtr rrset,
                  const isc::dns::ConstRRsetPtr rrsig);
    void addRdataSet(const isc::dns::ConstRRsetPtr rrset,
                     const isc::dns::ConstRRsetPtr rrsig);

    util::MemorySegment& mem_sgmt_;
    const isc::dns::RRClass rrclass_;
    const isc::dns::Name& zone_name_;
    ZoneData& zone_data_;
    RdataEncoder encoder_;
    const isc::dns::NSEC3Hash* hash_;
};

} // namespace memory
} // namespace datasrc
} // namespace isc

#endif // DATASRC_ZONE_DATA_UPDATER_H

// Local Variables:
// mode: c++
// End:
