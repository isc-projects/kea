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

// $Id$

#ifndef __ZONE_ENTRY_H
#define __ZONE_ENTRY_H

#include <string>
#include <vector>
#include <boost/thread.h>
#include <boost/shared_ptr.h>

class NameserverEntry;

/// \brief Zone Entry
///
/// The zone entry object describes a zone for which nameserver address
/// information is held.
///
/// Although the interface is simple, the internal processing is fairly
/// complicated, in that the class takes account of triggering fetches for
/// addresses of nameservers when the address records expire.

class ZoneEntry {
public:

    /// \brief Constructor
    ///
    /// Creates a zone entry object with an RRset representing the nameservers,
    /// plus possibly additional RRsets holding address information.
    ZoneEntry(AbstractRRset* nsrrset, const std::vector<AbstractRRSet*>& additional);

    /// \brief Lookup Address
    ///
    /// Returns the address with the lowest RTT.
    IOAddress getAddress() const;

public:
    void updateNS

private:
    boost::mutex    mutex_;     ///< Mutex protecting this zone entry
    std::string     name_;      ///< Canonical zone name
    short           classCode_; ///< Class code
    std::vector<boost::shared_ptr<NameserverEntry> > nameservers_; ///< Nameservers
    time_t          expiry_;    ///< Expiry time of this entry
};
 
#endif // __ZONE_ENTRY_H
