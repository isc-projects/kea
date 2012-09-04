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

class InMemoryZoneFinder : boost::noncopyable, public ZoneFinder {
public:
    InMemoryZoneFinder(const ZoneData& zone_data) : zone_data_(zone_data) {}

    virtual boost::shared_ptr<ZoneFinder::Context> find(
        const isc::dns::Name& name,
        const isc::dns::RRType& type,
        const FindOptions options = FIND_DEFAULT);

    virtual boost::shared_ptr<ZoneFinder::Context> findAll(
        const isc::dns::Name& name,
        std::vector<isc::dns::ConstRRsetPtr>& target,
        const FindOptions options = FIND_DEFAULT);

    virtual FindNSEC3Result
    findNSEC3(const isc::dns::Name& name, bool recursive);

    virtual isc::dns::Name getOrigin() const {
        return zone_data_.getOriginNode()->getName();
    }

    virtual isc::dns::RRClass getClass() const {
        isc_throw(isc::NotImplemented, "this method is not relevant and should "
                                       "probably be removed from the API");
    }

    class Context;

private:
    ZoneFinderResultContext find_internal(const isc::dns::Name& name,
                                          const isc::dns::RRType& type,
                                          std::vector<isc::dns::ConstRRsetPtr>* target,
                                          const FindOptions options =
                                          FIND_DEFAULT);

    const ZoneData& zone_data_;
};

} // namespace memory
} // namespace datasrc
} // namespace isc

#endif // DATASRC_MEMORY_ZONE_FINDER_H
