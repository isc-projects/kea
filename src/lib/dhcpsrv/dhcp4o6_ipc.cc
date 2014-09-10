// Copyright (C) 2014 Internet Systems Consortium, Inc. ("ISC")
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

#include <dhcpsrv/dhcp4o6_ipc.h>
#include <dhcp/iface_mgr.h>

namespace isc {
namespace dhcp {

DHCP4o6IPC::DHCP4o6IPC(const std::string& local_filename, const std::string& remote_filename) :
    UnixSocket(local_filename, remote_filename) {
    open();
}

void
DHCP4o6IPC::sendPkt4o6(const Pkt4o6Ptr& pkt4o6) {
    if (!pkt4o6) {
        isc_throw(DHCP4o6IPCSendError, "NULL 4o6 Packet");
    }
    isc::util::OutputBuffer buf(0);
    const isc::util::OutputBuffer &buf4(pkt4o6->getPkt4()->getBuffer());
    size_t len = buf4.getLength();
    buf.writeData(&len, sizeof(size_t));
    buf.writeData(buf4.getData(), len);
    const isc::util::OutputBuffer &buf6(pkt4o6->getPkt6()->getBuffer());
    len = buf6.getLength();
    buf.writeData(&len, sizeof(size_t));
    buf.writeData(buf6.getData(), len);
    std::string att = pkt4o6->getJsonAttribute();
    len = att.size();
    buf.writeData(&len, sizeof(size_t));
    buf.writeData(att.c_str(), len);
    
    UnixSocket::send(buf);
}

void
DHCP4o6IPC::recvPkt4o6() {
    isc::util::InputBuffer buf = recv();
    size_t len4, len6, len_json;
    uint8_t buf4[RCVBUFSIZE];
    uint8_t buf6[RCVBUFSIZE];
    char buf_json[RCVBUFSIZE] = {0};
    buf.readData(&len4, sizeof(size_t));
    buf.readData(buf4, len4);
    buf.readData(&len6, sizeof(size_t));
    buf.readData(buf6, len6);
    buf.readData(&len_json, sizeof(size_t));
    buf.readData(buf_json, len_json);
    
    Pkt4o6Ptr p(new Pkt4o6(buf4, len4, buf6, len6));
    p->setJsonAttribute(buf_json);
    queue_.push(p);
}

Pkt4o6Ptr
DHCP4o6IPC::pop() {
    if (queue_.empty())
        return Pkt4o6Ptr();
    current_ = queue_.front();
    queue_.pop();
    return current_;
}

} // isc::dhcp namespace
} // isc namespace
