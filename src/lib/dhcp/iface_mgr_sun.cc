// Copyright (C) 2011, 2013 Internet Systems Consortium, Inc. ("ISC")
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

#if defined(OS_SUN)

#include <dhcp/iface_mgr.h>
#include <exceptions/exceptions.h>

using namespace std;
using namespace isc;
using namespace isc::asiolink;
using namespace isc::dhcp;

namespace isc {
namespace dhcp {

void
IfaceMgr::detectIfaces() {
    /// @todo do the actual detection on Solaris. Currently just calling
    /// stub implementation.
    stubDetectIfaces();
}

void IfaceMgr::os_send4(struct msghdr& /*m*/,
                        boost::scoped_array<char>& /*control_buf*/,
                        size_t /*control_buf_len*/,
                        const Pkt4Ptr& /*pkt*/) {
  // @todo: Are there any specific actions required before sending IPv4 packet
  // on BSDs? See iface_mgr_linux.cc for working Linux implementation.
}

bool IfaceMgr::os_receive4(struct msghdr& /*m*/, Pkt4Ptr& /*pkt*/) {
  // @todo: Are there any specific actions required before receiving IPv4 packet
  // on BSDs? See iface_mgr_linux.cc for working Linux implementation.

  return (true); // pretend that we have everything set up for reception.
}

void
IfaceMgr::setMatchingPacketFilter(const bool /* direct_response_desired */) {
    boost::shared_ptr<PktFilter> pkt_filter(new PktFilterInet());
    setPacketFilter(pkt_filter);
}

} // end of isc::dhcp namespace
} // end of dhcp namespace

#endif
