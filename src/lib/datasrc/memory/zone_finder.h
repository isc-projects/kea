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

#ifndef DATASRC_MEMORY_ZONE_FINDER_H
#define DATASRC_MEMORY_ZONE_FINDER_H 1

#include <datasrc/memory/zone_data.h>
#include <datasrc/memory/treenode_rrset.h>

#include <datasrc/zone.h>
#include <dns/name.h>
#include <dns/rrset.h>
#include <dns/rrtype.h>

namespace isc {
namespace datasrc {
namespace memory {

class ZoneFinderResultContext {
public:
    /// \brief Constructor
    ///
    /// The first three parameters correspond to those of
    /// ZoneFinder::ResultContext.  If node is non NULL, it specifies the
    /// found RBNode in the search.
    ZoneFinderResultContext(ZoneFinder::Result code_param,
                            TreeNodeRRsetPtr rrset_param,
                            ZoneFinder::FindResultFlags flags_param,
                            const ZoneNode* node) :
        code(code_param), rrset(rrset_param), flags(flags_param),
        found_node(node)
    {}

    const ZoneFinder::Result code;
    const TreeNodeRRsetPtr rrset;
    const ZoneFinder::FindResultFlags flags;
    const ZoneNode* const found_node;
};

std::string
InMemoryZoneFinderNSEC3Calculate(const isc::dns::Name& name,
                                 const uint16_t iterations,
                                 const uint8_t* salt,
                                 size_t salt_len);

/// A derived zone finder class intended to be used with the memory data
/// source, using ZoneData for its contents.
class InMemoryZoneFinder : boost::noncopyable, public ZoneFinder {
public:
    /// \brief Constructor.
    ///
    /// Since ZoneData does not keep RRClass information, but this
    /// information is needed in order to construct actual RRsets,
    /// this needs to be passed here (the datasource client should
    /// have this information). In the future, this may be replaced
    /// by some construction to pull TreeNodeRRsets from a pool, but
    /// currently, these are created dynamically with the given RRclass
    ///
    /// \param zone_data The ZoneData containing the zone.
    /// \param rrclass The RR class of the zone
    InMemoryZoneFinder(const ZoneData& zone_data,
                       const isc::dns::RRClass& rrclass) :
        zone_data_(zone_data),
        rrclass_(rrclass),
        nsec3_calculate_(InMemoryZoneFinderNSEC3Calculate)
    {}

    /// \brief Find an RRset in the datasource
    virtual boost::shared_ptr<ZoneFinder::Context> find(
        const isc::dns::Name& name,
        const isc::dns::RRType& type,
        const FindOptions options = FIND_DEFAULT);

    /// \brief Version of find that returns all types at once
    ///
    /// It acts the same as find, just that when the correct node is found,
    /// all the RRsets are filled into the target parameter instead of being
    /// returned by the result.
    virtual boost::shared_ptr<ZoneFinder::Context> findAll(
        const isc::dns::Name& name,
        std::vector<isc::dns::ConstRRsetPtr>& target,
        const FindOptions options = FIND_DEFAULT);

    /// Look for NSEC3 for proving (non)existence of given name.
    ///
    /// See documentation in \c Zone.
    virtual FindNSEC3Result
    findNSEC3(const isc::dns::Name& name, bool recursive);

    /// \brief Returns the origin of the zone.
    virtual isc::dns::Name getOrigin() const;

    /// \brief Returns the RR class of the zone.
    virtual isc::dns::RRClass getClass() const {
        return (rrclass_);
    }

private:
    /// \brief In-memory version of finder context.
    ///
    /// The implementation (and any specialized interface) is completely local
    /// to the InMemoryZoneFinder class, so it's defined as private
    class Context;

    /// Actual implementation for both find() and findAll()
    ZoneFinderResultContext find_internal(
        const isc::dns::Name& name,
        const isc::dns::RRType& type,
        std::vector<isc::dns::ConstRRsetPtr>* target,
        const FindOptions options =
        FIND_DEFAULT);

    const ZoneData& zone_data_;
    const isc::dns::RRClass rrclass_;

protected:
    typedef std::string (NSEC3CalculateFn) (const isc::dns::Name& name,
                                            const uint16_t iterations,
                                            const uint8_t* salt,
                                            size_t salt_len);
    NSEC3CalculateFn* nsec3_calculate_;
};

} // namespace memory
} // namespace datasrc
} // namespace isc

#endif // DATASRC_MEMORY_ZONE_FINDER_H
