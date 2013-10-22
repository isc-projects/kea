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
     last_allocated_ia_(lastAddrInPrefix(prefix, len)),
     last_allocated_ta_(lastAddrInPrefix(prefix, len)),
     last_allocated_pd_(lastAddrInPrefix(prefix, len)) {
    if ((prefix.isV6() && len > 128) ||
        (prefix.isV4() && len > 32)) {
        isc_throw(BadValue,
                  "Invalid prefix length specified for subnet: " << len);
    }
}

bool
Subnet::inRange(const isc::asiolink::IOAddress& addr) const {
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

void Subnet::addVendorOption(const OptionPtr& option, bool persistent,
                             uint32_t vendor_id){

    validateOption(option);

    vendor_option_spaces_.addItem(OptionDescriptor(option, persistent), vendor_id);
}

Subnet::OptionContainerPtr
Subnet::getVendorOptionDescriptors(uint32_t vendor_id) const {
    return (vendor_option_spaces_.getItems(vendor_id));
}

Subnet::OptionDescriptor
Subnet::getVendorOptionDescriptor(uint32_t vendor_id, uint16_t option_code) {
    OptionContainerPtr options = getVendorOptionDescriptors(vendor_id);
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

void Subnet::delVendorOptions() {
    vendor_option_spaces_.clearItems();
}

isc::asiolink::IOAddress Subnet::getLastAllocated(Lease::Type type) const {
    // check if the type is valid (and throw if it isn't)
    checkType(type);

    switch (type) {
    case Lease::TYPE_V4:
    case Lease::TYPE_NA:
        return last_allocated_ia_;
    case Lease::TYPE_TA:
        return last_allocated_ta_;
    case Lease::TYPE_PD:
        return last_allocated_pd_;
    default:
        isc_throw(BadValue, "Pool type " << type << " not supported");
    }
}

void Subnet::setLastAllocated(Lease::Type type,
                              const isc::asiolink::IOAddress& addr) {

    // check if the type is valid (and throw if it isn't)
    checkType(type);

    switch (type) {
    case Lease::TYPE_V4:
    case Lease::TYPE_NA:
        last_allocated_ia_ = addr;
        return;
    case Lease::TYPE_TA:
        last_allocated_ta_ = addr;
        return;
    case Lease::TYPE_PD:
        last_allocated_pd_ = addr;
        return;
    default:
        isc_throw(BadValue, "Pool type " << type << " not supported");
    }
}

std::string
Subnet::toText() const {
    std::stringstream tmp;
    tmp << prefix_.toText() << "/" << static_cast<unsigned int>(prefix_len_);
    return (tmp.str());
}

void Subnet4::checkType(Lease::Type type) const {
    if (type != Lease::TYPE_V4) {
        isc_throw(BadValue, "Only TYPE_V4 is allowed for Subnet4");
    }
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

const PoolCollection& Subnet::getPools(Lease::Type type) const {
    // check if the type is valid (and throw if it isn't)
    checkType(type);

    switch (type) {
    case Lease::TYPE_V4:
    case Lease::TYPE_NA:
        return (pools_);
    case Lease::TYPE_TA:
        return (pools_ta_);
    case Lease::TYPE_PD:
        return (pools_pd_);
    default:
        isc_throw(BadValue, "Unsupported pool type: "
                  << static_cast<int>(type));
    }
}

PoolCollection& Subnet::getPoolsWritable(Lease::Type type) {
    // check if the type is valid (and throw if it isn't)
    checkType(type);

    switch (type) {
    case Lease::TYPE_V4:
    case Lease::TYPE_NA:
        return (pools_);
    case Lease::TYPE_TA:
        return (pools_ta_);
    case Lease::TYPE_PD:
        return (pools_pd_);
    default:
        isc_throw(BadValue, "Invalid pool type specified: "
                  << static_cast<int>(type));
    }
}

const PoolPtr Subnet::getPool(Lease::Type type, const isc::asiolink::IOAddress& hint,
                        bool anypool /* true */) const {
    // check if the type is valid (and throw if it isn't)
    checkType(type);

    const PoolCollection& pools = getPools(type);

    PoolPtr candidate;
    for (PoolCollection::const_iterator pool = pools.begin();
         pool != pools.end(); ++pool) {

        // if we won't find anything better, then let's just use the first pool
        if (anypool && !candidate) {
            candidate = *pool;
        }

        // if the client provided a pool and there's a pool that hint is valid
        // in, then let's use that pool
        if ((*pool)->inRange(hint)) {
            return (*pool);
        }
    }
    return (candidate);
}

void
Subnet::addPool(const PoolPtr& pool) {
    IOAddress first_addr = pool->getFirstAddress();
    IOAddress last_addr = pool->getLastAddress();

    if (!inRange(first_addr) || !inRange(last_addr)) {
        isc_throw(BadValue, "Pool (" << first_addr.toText() << "-"
                  << last_addr.toText()
                  << " does not belong in this (" << prefix_.toText() << "/"
                  << static_cast<int>(prefix_len_) << ") subnet");
    }

    /// @todo: Check that pools do not overlap

    // check if the type is valid (and throw if it isn't)
    checkType(pool->getType());

    // Add the pool to the appropriate pools collection
    getPoolsWritable(pool->getType()).push_back(pool);
}

void
Subnet::delPools(Lease::Type type) {
    getPoolsWritable(type).clear();
}

void
Subnet::setIface(const std::string& iface_name) {
    iface_ = iface_name;
}

std::string
Subnet::getIface() const {
    return (iface_);
}

void
Subnet4::validateOption(const OptionPtr& option) const {
    if (!option) {
        isc_throw(isc::BadValue,
                  "option configured for subnet must not be NULL");
    } else if (option->getUniverse() != Option::V4) {
        isc_throw(isc::BadValue,
                  "expected V4 option to be added to the subnet");
    }
}

bool
Subnet::inPool(Lease::Type type, const isc::asiolink::IOAddress& addr) const {

    // Let's start with checking if it even belongs to that subnet.
    if (!inRange(addr)) {
        return (false);
    }

    const PoolCollection& pools = getPools(type);

    for (PoolCollection::const_iterator pool = pools.begin();
         pool != pools.end(); ++pool) {
        if ((*pool)->inRange(addr)) {
            return (true);
        }
    }
    // There's no pool that address belongs to
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

void Subnet6::checkType(Lease::Type type) const {
    if ( (type != Lease::TYPE_NA) && (type != Lease::TYPE_TA) &&
         (type != Lease::TYPE_PD)) {
        isc_throw(BadValue, "Invalid Pool type: " << Lease::typeToText(type)
                  << "(" << static_cast<int>(type)
                  << "), must be TYPE_NA, TYPE_TA or TYPE_PD for Subnet6");
    }
}

void
Subnet6::validateOption(const OptionPtr& option) const {
    if (!option) {
        isc_throw(isc::BadValue,
                  "option configured for subnet must not be NULL");
    } else if (option->getUniverse() != Option::V6) {
        isc_throw(isc::BadValue,
                  "expected V6 option to be added to the subnet");
    }
}

} // end of isc::dhcp namespace
} // end of isc namespace
