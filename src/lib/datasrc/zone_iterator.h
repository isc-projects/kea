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

#ifndef DATASRC_ZONE_ITERATOR_H
#define DATASRC_ZONE_ITERATOR_H 1

#include <dns/rrset.h>

#include <boost/noncopyable.hpp>

#include <datasrc/zone.h>

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

    /**
     * \brief Return the SOA record of the zone in the iterator context.
     *
     * This method returns the zone's SOA record (if any, and a valid zone
     * should have it) in the form of an RRset object.  This SOA is identical
     * to that (again, if any) contained in the sequence of RRsets returned
     * by the iterator.  In that sense this method is redundant, but is
     * provided as a convenient utility for the application of the
     * iterator; the application may need to know the SOA serial or the
     * SOA RR itself for the purpose of protocol handling or skipping the
     * expensive iteration processing.
     *
     * If the zone doesn't have an SOA (which is broken, but some data source
     * may allow that situation), this method returns NULL.  Also, in the
     * normal and valid case, the SOA should have exactly one RDATA, but
     * this API does not guarantee it as some data source may accept such an
     * abnormal condition.  It's up to the caller whether to check the number
     * of RDATA and how to react to the unexpected case.
     *
     * Each concrete derived method must ensure that the SOA returned by this
     * method is identical to the zone's SOA returned via the iteration.
     * For example, even if another thread or process updates the SOA while
     * the iterator is working, the result of this method must not be
     * affected by the update.  For database based data sources, this can
     * be done by making the entire iterator operation as a single database
     * transaction, but the actual implementation can differ.
     *
     * \exception None
     *
     * \return A shared pointer to an SOA RRset that would be returned
     * from the iteration.  It will be NULL if the zone doesn't have an SOA.
     */
    virtual isc::dns::ConstRRsetPtr getSOA() const = 0;
};

}
}
#endif  // DATASRC_ZONE_ITERATOR_H

// Local Variables:
// mode: c++
// End:
