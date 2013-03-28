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

bool
IfaceMgr::isDirectResposeSupported() {
    return (false);
}

bool
IfaceMgr::send(const Pkt4Ptr& pkt)
{
    Iface* iface = getIface(pkt->getIface());
    if (!iface) {
        isc_throw(BadValue, "Unable to send Pkt4. Invalid interface ("
                  << pkt->getIface() << ") specified.");
    }

    memset(&control_buf_[0], 0, control_buf_len_);

    // Set the target address we're sending to.
    sockaddr_in to;
    memset(&to, 0, sizeof(to));
    to.sin_family = AF_INET;
    to.sin_port = htons(pkt->getRemotePort());
    to.sin_addr.s_addr = htonl(pkt->getRemoteAddr());

    struct msghdr m;
    // Initialize our message header structure.
    memset(&m, 0, sizeof(m));
    m.msg_name = &to;
    m.msg_namelen = sizeof(to);

    // Set the data buffer we're sending. (Using this wacky
    // "scatter-gather" stuff... we only have a single chunk
    // of data to send, so we declare a single vector entry.)
    struct iovec v;
    memset(&v, 0, sizeof(v));
    // iov_base field is of void * type. We use it for packet
    // transmission, so this buffer will not be modified.
    v.iov_base = const_cast<void *>(pkt->getBuffer().getData());
    v.iov_len = pkt->getBuffer().getLength();
    m.msg_iov = &v;
    m.msg_iovlen = 1;

    // call OS-specific routines (like setting interface index)
    os_send4(m, control_buf_, control_buf_len_, pkt);

    pkt->updateTimestamp();

    int result = sendmsg(getSocket(*pkt), &m, 0);
    if (result < 0) {
        isc_throw(SocketWriteError, "pkt4 send failed");
    }

    return (result);
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

} // end of isc::dhcp namespace
} // end of dhcp namespace

#endif
