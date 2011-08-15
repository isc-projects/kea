// Copyright (C) 2011  Internet Systems Consortium, Inc. ("ISC")
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

#include <dns/rrset.h>

#include <boost/noncopyable.hpp>

namespace isc {
namespace datasrc {

/**
 * \brief Read-only iterator to a zone.
 *
 * You can get an instance of (descendand of) ZoneIterator from
 * DataSourceClient::getIterator() method. The actual concrete implementation
 * will be different depending on the actual data source used. This is the
 * abstract interface.
 *
 * There's no way to start iterating from the beginning again or return.
 */
class ZoneIterator : public boost::noncopyable {
public:
    /**
     * \brief Destructor
     *
     * Virtual destructor. It is empty, but ensures the right destructor from
     * descendant is called.
     */
    virtual ~ ZoneIterator() { }

    /**
     * \brief Get next RRset from the zone.
     *
     * This returns the next RRset in the zone as a shared pointer. The
     * shared pointer is used to allow both accessing in-memory data and
     * automatic memory management.
     *
     * Any special order is not guaranteed.
     *
     * While this can potentially throw anything (including standard allocation
     * errors), it should be rare.
     *
     * \return Pointer to the next RRset or NULL pointer when the iteration
     *     gets to the end of the zone.
     */
    virtual isc::dns::ConstRRsetPtr getNextRRset() = 0;
};

}
}
