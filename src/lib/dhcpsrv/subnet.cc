// Copyright (C) 2012-2013 Internet Systems Consortium, Inc. ("ISC")
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

#include <asiolink/io_address.h>
#include <dhcp/option_space.h>
#include <dhcpsrv/addr_utilities.h>
#include <dhcpsrv/subnet.h>

#include <sstream>

using namespace isc::asiolink;

namespace isc {
namespace dhcp {

Subnet::Subnet(const isc::asiolink::IOAddress& prefix, uint8_t len,
               const Triplet<uint32_t>& t1,
               const Triplet<uint32_t>& t2,
               const Triplet<uint32_t>& valid_lifetime)
    :id_(getNextID()), prefix_(prefix), prefix_len_(len), t1_(t1),
     t2_(t2), valid_(valid_lifetime),
     last_allocated_(lastAddrInPrefix(prefix, len)) {
    if ((prefix.isV6() && len > 128) ||
        (prefix.isV4() && len > 32)) {
        isc_throw(BadValue, "Invalid prefix length specified for subnet: " << len);
    }
}

bool Subnet::inRange(const isc::asiolink::IOAddress& addr) const {
    IOAddress first = firstAddrInPrefix(prefix_, prefix_len_);
    IOAddress last = lastAddrInPrefix(prefix_, prefix_len_);

    return ((first <= addr) && (addr <= last));
}

void
Subnet::addOption(const OptionPtr& option, bool persistent,
                  const std::string& option_space) {
    // Check that the option space name is valid.
    if (!OptionSpace::validateName(option_space)) {
        isc_throw(isc::BadValue, "invalid option space name: '"
                  << option_space << "'");
    }
    validateOption(option);

    // Actually add new option descriptor.
    option_spaces_.addItem(OptionDescriptor(option, persistent), option_space);
}

void
Subnet::delOptions() {
    option_spaces_.clearItems();
}

Subnet::OptionContainerPtr
Subnet::getOptionDescriptors(const std::string& option_space) const {
    return (option_spaces_.getItems(option_space));
}

Subnet::OptionDescriptor
Subnet::getOptionDescriptor(const std::string& option_space,
                            const uint16_t option_code) {
    OptionContainerPtr options = getOptionDescriptors(option_space);
    if (!options || options->empty()) {
        return (OptionDescriptor(false));
    }
    const OptionContainerTypeIndex& idx = options->get<1>();
    const OptionContainerTypeRange& range = idx.equal_range(option_code);
    if (std::distance(range.first, range.second) == 0) {
        return (OptionDescriptor(false));
    }

    return (*range.first);
}

std::string Subnet::toText() const {
    std::stringstream tmp;
    tmp << prefix_.toText() << "/" << static_cast<unsigned int>(prefix_len_);
    return (tmp.str());
}

Subnet4::Subnet4(const isc::asiolink::IOAddress& prefix, uint8_t length,
                 const Triplet<uint32_t>& t1,
                 const Triplet<uint32_t>& t2,
                 const Triplet<uint32_t>& valid_lifetime)
    :Subnet(prefix, length, t1, t2, valid_lifetime) {
    if (!prefix.isV4()) {
        isc_throw(BadValue, "Non IPv4 prefix " << prefix.toText()
                  << " specified in subnet4");
    }
}

void Subnet::addPool(const PoolPtr& pool) {
    IOAddress first_addr = pool->getFirstAddress();
    IOAddress last_addr = pool->getLastAddress();

    if (!inRange(first_addr) || !inRange(last_addr)) {
        isc_throw(BadValue, "Pool (" << first_addr.toText() << "-" << last_addr.toText()
                  << " does not belong in this (" << prefix_.toText() << "/"
                  << static_cast<int>(prefix_len_) << ") subnet4");
    }

    /// @todo: Check that pools do not overlap

    pools_.push_back(pool);
}

PoolPtr Subnet::getPool(isc::asiolink::IOAddress hint) {

    PoolPtr candidate;
    for (PoolCollection::iterator pool = pools_.begin(); pool != pools_.end(); ++pool) {

        // if we won't find anything better, then let's just use the first pool
        if (!candidate) {
            candidate = *pool;
        }

        // if the client provided a pool and there's a pool that hint is valid in,
        // then let's use that pool
        if ((*pool)->inRange(hint)) {
            return (*pool);
        }
    }
    return (candidate);
}


void
Subnet4::validateOption(const OptionPtr& option) const {
    if (!option) {
        isc_throw(isc::BadValue, "option configured for subnet must not be NULL");
    } else if (option->getUniverse() != Option::V4) {
        isc_throw(isc::BadValue, "expected V4 option to be added to the subnet");
    }
}

bool Subnet::inPool(const isc::asiolink::IOAddress& addr) const {

    // Let's start with checking if it even belongs to that subnet.
    if (!inRange(addr)) {
        return (false);
    }

    for (PoolCollection::const_iterator pool = pools_.begin(); pool != pools_.end(); ++pool) {
        if ((*pool)->inRange(addr)) {
            return (true);
        }
    }
    // there's no pool that address belongs to
    return (false);
}

Subnet6::Subnet6(const isc::asiolink::IOAddress& prefix, uint8_t length,
                 const Triplet<uint32_t>& t1,
                 const Triplet<uint32_t>& t2,
                 const Triplet<uint32_t>& preferred_lifetime,
                 const Triplet<uint32_t>& valid_lifetime)
    :Subnet(prefix, length, t1, t2, valid_lifetime),
     preferred_(preferred_lifetime){
    if (!prefix.isV6()) {
        isc_throw(BadValue, "Non IPv6 prefix " << prefix.toText()
                  << " specified in subnet6");
    }
}

void
Subnet6::validateOption(const OptionPtr& option) const {
    if (!option) {
        isc_throw(isc::BadValue, "option configured for subnet must not be NULL");
    } else if (option->getUniverse() != Option::V6) {
        isc_throw(isc::BadValue, "expected V6 option to be added to the subnet");
    }
}


void Subnet6::setIface(const std::string& iface_name) {
    iface_ = iface_name;
}

std::string Subnet6::getIface() const {
    return (iface_);
}


} // end of isc::dhcp namespace
} // end of isc namespace
