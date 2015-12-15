// Copyright (C) 2012, 2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <dhcp/libdhcp++.h>
#include <dhcp/dhcp4.h>

#include "perf_pkt4.h"

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
                               buffer_out_));
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

void
PerfPkt4::writeAt(size_t dest_pos,
                  std::vector<uint8_t>::iterator first,
                  std::vector<uint8_t>::iterator last) {
    return (PktTransform::writeAt(data_, dest_pos, first, last));
}



} // namespace perfdhcp
} // namespace isc
