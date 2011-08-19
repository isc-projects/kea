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

#ifndef IFACE_MGR_H
#define IFACE_MGR_H

#include <list>
#include "io_address.h"
#include "dhcp/pkt6.h"

namespace isc {

    /**
     * IfaceMgr is an interface manager class that detects available network
     * interfaces, configured addresses, link-local addresses, and provides
     * API for using sockets.
     *
     */
    class IfaceMgr {
    public:
        typedef std::list<isc::asiolink::IOAddress> Addr6Lst;
        struct Iface { // TODO: could be a class as well
            std::string name_; // network interface name
            int ifindex_; // interface index (a value that uniquely indentifies
                          // an interface
            Addr6Lst addrs_;
            char mac_[20]; // Infiniband used 20 bytes indentifiers
            int mac_len_;

            Iface(const std::string& name, int ifindex);
            std::string getFullName() const;
            std::string getPlainMac() const;

            int sendsock_; // socket used to sending data
            int recvsock_; // socket used for receiving data

            // next field is not needed, let's keep it in cointainers
        };

        // TODO performance improvement: we may change this into
        //      2 maps (ifindex-indexed and name-indexed) and
        //      also hide it (make it public make tests easier for now)
        typedef std::list<Iface> IfaceLst;

        static IfaceMgr& instance();

        Iface * getIface(int ifindex);
        Iface * getIface(const std::string& ifname);

        void printIfaces(std::ostream& out = std::cout);

        bool send(Pkt6& pkt);
        Pkt6* receive();

        // don't use private, we need derived classes in tests
    protected:
        IfaceMgr(); // don't create IfaceMgr directly, use instance() method
        ~IfaceMgr();

        void detectIfaces();

        int openSocket(const std::string& ifname,
                       const isc::asiolink::IOAddress& addr,
                       int port);

        // TODO: having 2 maps (ifindex->iface and ifname->iface would)
        //      probably be better for performance reasons
        IfaceLst ifaces_;

        static IfaceMgr * instance_;

        // TODO: Also keep this interface on Iface once interface detection
        // is implemented. We may need it e.g. to close all sockets on
        // specific interface
        int recvsock_; // TODO: should be fd_set eventually, but we have only
        int sendsock_; // 2 sockets for now. Will do for until next release
        // we can't use the same socket, as receiving socket
        // is bound to multicast address. And we all know what happens
        // to people who try to use multicast as source address.

        char * control_buf_;
        int control_buf_len_;

    private:
        bool openSockets();
        static void instanceCreate();
        bool joinMcast(int sock, const std::string& ifname,
                       const std::string& mcast);
    };
};

#endif
