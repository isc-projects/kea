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

#ifndef DHCPV6_SRV_H
#define DHCPV6_SRV_H

#include <iostream>

namespace isc {
    class Dhcpv6Srv {
    private:
        // defined private on purpose. We don't want to have more than
        // one copy
        Dhcpv6Srv(const Dhcpv6Srv& src);
        Dhcpv6Srv& operator=(const Dhcpv6Srv& src);

    public:
        // default constructor
        Dhcpv6Srv();
        ~Dhcpv6Srv();

        bool run();

    protected:
        bool shutdown;
    };
};

#endif // DHCP6_SRV_H
