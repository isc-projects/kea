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
#include <boost/shared_array.hpp>
#include "io_address.h"

namespace isc {

    class Pkt6 {
    public:
        Pkt6(int len);
        ~Pkt6();

        // XXX: probably need getter/setter wrappers
        //      and hide fields as protected
        // buffer that holds memory. It is shared_array as options may
        // share pointer to this buffer
        boost::shared_array<char> data_;

        // length of the data
        int data_len_;

        // local address (destination if receiving packet, source if sending packet)
        isc::asiolink::IOAddress local_addr_;

        // remote address (source if receiving packet, destination if sending packet)
        isc::asiolink::IOAddress remote_addr_;

        // name of the network interface the packet was received/to be sent over
        std::string iface_;

        // interface index (each network interface has assigned unique ifindex
        // it is functional equvalent of name, but sometimes more useful, e.g.
        // when using crazy systems that allow spaces in interface names (Windows)
        int ifindex_;

        // local TDP or UDP port
        int local_port_;

        // remote TCP or UDP port
        int remote_port_;

        // XXX: add *a lot* here
    };
}

#endif
