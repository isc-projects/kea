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
#include "dhcp6/pkt6.h"

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
        struct Iface { // XXX: could be a class as well
            std::string name_;
            int ifindex_;
            Addr6Lst addrs_;
            char mac_[20]; //
            int mac_len_;

            Iface();
            Iface(const std::string& name, int ifindex);
            std::string getFullName() const;
            std::string getPlainMac() const;

            // next field is not needed, let's keep it in cointainers
        };

	// TODO performance improvement: we may change this into
	//      2 maps (ifindex-indexed and name-indexed)
        typedef std::list<Iface> IfaceLst;

        static IfaceMgr& instance();
        static void instanceCreate();

        Iface * getIface(int ifindex);
        Iface * getIface(const std::string& ifname);

        bool openSockets();
        void printIfaces();

        int openSocket(const std::string& ifname,
                       const isc::asiolink::IOAddress& addr,
                       int port, bool multicast);
        bool joinMcast(int sock, const std::string& ifname,
                       const std::string& mcast);

        bool send(Pkt6& pkt);
        Pkt6* receive();

	// don't use private, we need derived classes in tests
    protected:
        IfaceMgr(); // don't create IfaceMgr directly, use instance() method
        ~IfaceMgr();

        void detectIfaces();

        // XXX: having 2 maps (ifindex->iface and ifname->iface would)
        //      probably be better for performance reasons
        IfaceLst ifaces_;

        static IfaceMgr * instance_;

        int recvsock_; // XXX: should be fd_set eventually, but we have only
        int sendsock_; // 2 sockets for now. Will do for until next release

        char * control_buf_;
        int control_buf_len_;
    };
};

#endif
