// Copyright (C) 2013 Internet Systems Consortium, Inc. ("ISC")
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

#include <config.h>
#include <dhcp/iface_mgr.h>
#include <dhcp/pkt4.h>
#include <dhcp/pkt_filter_lpf.h>

namespace isc {
namespace dhcp {

int
PktFilterLPF::openSocket(const Iface&, const isc::asiolink::IOAddress&,
                         const uint16_t, const bool,
                         const bool) {
    isc_throw(isc::NotImplemented,
              "Linux Packet Filtering is not implemented yet");
}

Pkt4Ptr
PktFilterLPF::receive(const Iface&, const SocketInfo&) {
    isc_throw(isc::NotImplemented,
              "Linux Packet Filtering is not implemented yet");
}

int
PktFilterLPF::send(uint16_t, const Pkt4Ptr&) {
    isc_throw(isc::NotImplemented,
              "Linux Packet Filtering is not implemented yet");
}


} // end of isc::dhcp namespace
} // end of isc namespace
