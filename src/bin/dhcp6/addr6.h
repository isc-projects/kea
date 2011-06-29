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

#ifndef ADDR6_H
#define ADDR6_H

#include <ostream>
#include <string>
#include <list>

namespace isc {

    static const int MAX_ADDRESS_STRING_LEN =
        sizeof("ffff:ffff:ffff:ffff:ffff:ffff:255.255.255.255");

    class Addr6 {
    public:
        Addr6(const char * addr, bool plain=false);
        Addr6(struct in6_addr* addr);
        Addr6(struct sockaddr_in6 * addr);
        Addr6();
        inline const char * get() const { return addr_; }
        std::string getPlain() const;
        char * get() { return addr_; }
        bool operator==(const Addr6& other) const;

        bool linkLocal() const;
        bool multicast() const;

        // no dtor necessary (no allocations done)
    private:
        char addr_[MAX_ADDRESS_STRING_LEN];
    };

    std::ostream & operator << (std::ostream & out, const Addr6& addr);

    typedef std::list<Addr6> Addr6Lst;

};


#endif
