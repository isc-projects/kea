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
#include <boost/shared_ptr.hpp>
#include <boost/shared_array.hpp>
#include "io_address.h"
#include "option.h"

namespace isc {


    class Pkt6 {
    public:
        enum DHCPv6Proto_ {
            UDP = 0, // most packets are UDP
            TCP = 1  // there are TCP DHCPv6 packet (bulk leasequery, failover)
        };

        Pkt6(unsigned char msg_type,
             unsigned int transid,
             DHCPv6Proto_ proto = UDP);
        Pkt6(unsigned int len, DHCPv6Proto_ proto = UDP);
        ~Pkt6();

        bool pack();
        bool unpack();

        DHCPv6Proto_ getProto();
        void setProto(DHCPv6Proto_ proto = Pkt6::UDP);

        // returns text representation, useful for debugging
        std::string toText();

        unsigned short len();

        unsigned char getType();
        unsigned int getTransid() { return transid_; };

        boost::shared_ptr<isc::dhcp::Option> getOption(unsigned short opt_type);

        /// TODO Need to implement getOptions() as well

        /// TODO need getter/setter wrappers
        ///      and hide following fields as protected
        /// buffer that holds memory. It is shared_array as options may
        /// share pointer to this buffer
        boost::shared_array<char> data_;

        // length of the data
        unsigned int data_len_;

        // local address (dst if receiving packet, src if sending packet)
        isc::asiolink::IOAddress local_addr_;

        // remote address (src if receiving packet, dst if sending packet)
        isc::asiolink::IOAddress remote_addr_;

        // name of the network interface the packet was received/to be sent over
        std::string iface_;

        // interface index (each network interface has assigned unique ifindex
        // it is functional equvalent of name, but sometimes more useful, e.g.
        // when using crazy systems that allow spaces in interface names
        // e.g. windows
        int ifindex_;

        // local TDP or UDP port
        int local_port_;

        // remote TCP or UDP port
        int remote_port_;

        // XXX: add *a lot* here
        isc::dhcp::Option::Option6Lst options_;

    protected:
        bool packTCP();
        bool packUDP();
        bool unpackTCP();
        bool unpackUDP();

        DHCPv6Proto_ proto_; // UDP (most) or TCP (bulk leasequery or failover)
        int msg_type_; // DHCPv6 message type
        int transid_;  // DHCPv6 transaction-id

    };
}

#endif
