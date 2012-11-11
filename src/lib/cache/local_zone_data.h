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

#ifndef LOCAL_ZONE_DATA
#define LOCAL_ZONE_DATA

#include <map>
#include <string>
#include <boost/shared_ptr.hpp>
#include <dns/rrset.h>

namespace isc {
namespace cache {

/// \brief Local Zone Data
/// The object of LocalZoneData represents the data of one
/// local zone. It provides the interface for lookup the rrsets
/// in the zone.
class LocalZoneData {
public:
    LocalZoneData(uint16_t rrset_class) : class_(rrset_class)
    {}

    /// \brief Look up one rrset.
    ///
    /// \param qname The query name to look up
    /// \param qtype The query type to look up
    /// \return return the shared_ptr of rrset if it is
    /// found in the local zone, or else, return NULL.
    isc::dns::RRsetPtr lookup(const isc::dns::Name& qname,
                              const isc::dns::RRType& qtype);

    /// \brief Update the rrset in the local zone.
    ///
    /// If the rrset doesn't exist, it will be added.
    /// Otherwise, the existed one will be overwritten.
    ///
    /// \param rrset The rrset to update
    void update(const isc::dns::AbstractRRset& rrset);

private:
    std::map<std::string, isc::dns::RRsetPtr> rrsets_map_; // RRsets of the zone
    uint16_t class_; // The class of the zone
};

typedef boost::shared_ptr<LocalZoneData> LocalZoneDataPtr;
typedef boost::shared_ptr<const LocalZoneData> ConstLocalZoneDataPtr;

} // namespace cache
} // namespace isc

#endif // LOCAL_ZONE_DATA

