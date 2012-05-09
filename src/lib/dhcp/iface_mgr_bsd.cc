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

#include <config.h>

#if defined(OS_BSD)

#include <dhcp/iface_mgr.h>
#include <exceptions/exceptions.h>

using namespace std;
using namespace isc;
using namespace isc::asiolink;
using namespace isc::dhcp;

namespace isc {

void
IfaceMgr::detectIfaces() {
    // TODO do the actual detection on BSDs. Currently just calling
    // stub implementation.
    stubDetectIfaces();
}

void IfaceMgr::os_send4_setup(struct msghdr& ,
                              boost::scoped_array<char>& ,
                              size_t , const Pkt4Ptr& ) {
    // do nothing here. There's nothing BSD specific to do and os_send4_setup()
    // interface is there only to not mix Linux-specific code in common
    // IfaceMgr file.
}


}

#endif
