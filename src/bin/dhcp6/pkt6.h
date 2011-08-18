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

#ifndef PKT6_H
#define PKT6_H

#include <iostream>
#include "io_address.h"

namespace isc {

    class Pkt6 {
    public:
        Pkt6(char * data, int dataLen);
        Pkt6(int len);
        ~Pkt6();

        // XXX: probably need getter/setter wrappers
        //      and hide fields as protected
        char * data_;
        int data_len_;

        isc::asiolink::IOAddress local_addr_;
        isc::asiolink::IOAddress remote_addr_;

        std::string iface_;
        int ifindex_;

        int local_port_;
        int remote_port_;

        // XXX: add *a lot* here

    };
}

#endif
