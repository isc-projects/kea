// Copyright (C) 2009  Internet Systems Consortium, Inc. ("ISC")
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

#ifndef __ZONESET_H
#define __ZONESET_H 1

#include <set>
#include <dns/cpp/buffer.h>
#include <dns/cpp/name.h>

class ZoneSet {
public:
    void serve(const std::string& s) {
        serve(isc::dns::Name(s));
    }

    void serve(const isc::dns::Name& n) {
        elements.insert(n);
    }
    
    void forget(const std::string& s) {
        forget(isc::dns::Name(s));
    }

    void forget(const isc::dns::Name& n) {
        elements.erase(n);
    }

    void clear_zones() {
        elements.clear();
    }

    bool contains(const std::string& s) const {
        return contains(isc::dns::Name(s));
    }

    bool contains(const isc::dns::Name& n) const {
        return (elements.find(n) != elements.end());
    }

    bool findClosest(const isc::dns::Name& n, isc::dns::Name& closest);

private:
    std::set<isc::dns::Name> elements;
};

#endif // __ZONESET_H

// Local Variables:
// mode: c++
// End:
