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

#include <utility>
#include <dhcp/pkt.h>

namespace isc {
namespace dhcp {

void
Pkt::addOption(const OptionPtr& opt) {
    options_.insert(std::pair<int, boost::shared_ptr<Option> >(opt->getType(), opt));
}

OptionPtr
Pkt::getOption(uint16_t type) const {
    OptionCollection::const_iterator x = options_.find(type);
    if (x != options_.end()) {
        return (*x).second;
    }
    return boost::shared_ptr<isc::dhcp::Option>(); // NULL
}

bool
Pkt::delOption(uint16_t type) {
    isc::dhcp::OptionCollection::iterator x = options_.find(type);
    if (x!=options_.end()) {
        options_.erase(x);
        return (true); // delete successful
    }
    return (false); // can't find option to be deleted
}

bool
Pkt::inClass(const std::string& client_class) {
    return (classes_.find(client_class) != classes_.end());
}

void
Pkt::addClass(const std::string& client_class) {
    if (classes_.find(client_class) == classes_.end()) {
        classes_.insert(client_class);
    }
}

void
Pkt::updateTimestamp() {
    timestamp_ = boost::posix_time::microsec_clock::universal_time();
}

void Pkt::repack() {
    buffer_out_.writeData(&data_[0], data_.size());
}

};
};
