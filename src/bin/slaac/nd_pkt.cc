// Copyright (C) 2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <slaac/nd_pkt.h>
#include <dhcp/iface_mgr.h>
#include <vector>

namespace isc {
namespace slaac {

NDPkt::NDPkt(const isc::asiolink::IOAddress& local_addr,
             const isc::asiolink::IOAddress& remote_addr)
    : type_(0),
      code_(0),
      iface_(""),
      ifindex_(-1),
      local_addr_(local_addr),
      remote_addr_(remote_addr),
      buffer_out_(0)
{
}

NDPkt::NDPkt(const uint8_t* buf, uint32_t len,
             const isc::asiolink::IOAddress& local_addr,
             const isc::asiolink::IOAddress& remote_addr)
    : type_(0),
      code_(0),
      iface_(""),
      ifindex_(-1),
      local_addr_(local_addr),
      remote_addr_(remote_addr),
      buffer_out_(0)
{
    if (len != 0) {
        if (buf == NULL) {
            isc_throw(InvalidParameter, "data buffer passed to NDPkt is NULL");
        }
        data_.resize(len);
        memcpy(&data_[0], buf, len);
    }
}

void
NDPkt::addOption(const OptionPtr& opt) {
    options_.insert(std::pair<uint8_t, OptionPtr>(opt->getType(), opt));
}

OptionPtr
NDPkt::getOption(const uint8_t type) {
    OptionCollection::iterator x = options_.find(type);
    if (x != options_.end()) {
        return (x->second);
    }
    return (OptionPtr()); // NULL
}

bool
NDPkt::delOption(uint8_t type) {

    OptionCollection::iterator x = options_.find(type);
    if (x != options_.end()) {
        options_.erase(x);
        return (true); // delete successful
    } else {
        return (false); // can't find option to be deleted
    }
}

void
NDPkt::updateTimestamp() {
    timestamp_ = boost::posix_time::microsec_clock::universal_time();
}

void NDPkt::repack() {
    if (!data_.empty()) {
        buffer_out_.writeData(&data_[0], data_.size());
    }
}

};
};
