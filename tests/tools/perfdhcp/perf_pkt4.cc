// Copyright (C) 2012 Internet Systems Consortium, Inc. ("ISC")
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

#include <dhcp/libdhcp++.h>
#include <dhcp/dhcp6.h>

#include "perf_pkt4.h"
#include "pkt_transform.h"

using namespace std;
using namespace isc;
using namespace dhcp;

namespace isc {
namespace perfdhcp {

PerfPkt4::PerfPkt4(const uint8_t* buf,
                   size_t len,
                   size_t transid_offset,
                   uint32_t transid) :
    Pkt4(buf, len),
    transid_offset_(transid_offset) {
    setTransid(transid);
}

bool
PerfPkt4::rawPack() {
    return (PktTransform::pack(dhcp::Option::V4,
                               data_,
                               options_,
                               getTransidOffset(),
                               getTransid(),
                               bufferOut_));
}

bool
PerfPkt4::rawUnpack() {
    uint32_t transid = getTransid();
    bool res = PktTransform::unpack(dhcp::Option::V4,
                                    data_,
                                    options_,
                                    getTransidOffset(),
                                    transid);
    if (res) {
        setTransid(transid);
    }
    return (res);
}

} // namespace perfdhcp
} // namespace isc
