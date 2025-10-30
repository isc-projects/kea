// Copyright (C) 2020-2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <lease_query_impl.h>
#include <blq_service.h>

using namespace isc;
using namespace isc::asiolink;
using namespace isc::data;
using namespace isc::dhcp;
using namespace isc::lease_query;

void
AddressList::insert(const IOAddress& address) {
    // Check for duplicates as inserts into set do not.
    // Proper family check is done in by contains().
    if (contains(address)) {
        isc_throw(BadValue, "address is already in the list");
    }

    static_cast<void>(addresses_.insert(address));
}

bool
AddressList::contains(const IOAddress& address) const {
    // Make sure we have the right family.
    if (address.getFamily() != family_) {
        isc_throw(BadValue, "not a " << (family_ == AF_INET ? "IPv4" : "IPv6")
                   << " address");
    }

    return (addresses_.count(address));
}

void
PoolSet::insert(const isc::asiolink::IOAddress& prefix, uint8_t prefix_len) {
    PoolPtr pool;
    if (getFamily() == AF_INET) {
        pool = Pool4::create(prefix, prefix_len);
    } else {
        pool = Pool6::create(Lease::TYPE_NA, prefix, prefix_len);
    }

    if (pools_.find(pool) != pools_.end()) {
        isc_throw(BadValue, "entry already exists");
    }

    pools_.emplace(pool);
}

bool
PoolSet::contains(const IOAddress& address) const {
    if (address.getFamily() != family_) {
        isc_throw(BadValue, "not a " << (family_ == AF_INET ? "IPv4" : "IPv6")
                   << " address");
    }

    for (auto pool : pools_) {
        if (pool->inRange(address)) {
            return (true);
        }
    }

    return (false);
}

const SimpleKeywords
LeaseQueryImpl::LEASE_QUERY_KEYWORDS =
{
    { "requesters",     Element::list   },
    { "advanced",       Element::map    },
    { "comment",        Element::string },
    { "prefix-lengths", Element::list   }, // v6 only
};

LeaseQueryImpl::LeaseQueryImpl(uint16_t family,
                               const ConstElementPtr config)
    : io_service_(new IOService()), address_list_(family), pool_set_(family) {

    if (!config || (config->getType() != Element::map)) {
        isc_throw(BadValue, "Lease Query config is empty or not a map");
    }

    parserRequesters(config-get("requesters"));

    ConstElementPtr advanced = config->get("advanced");
    if (advanced) {
        BulkLeaseQueryService::create(this, advanced);
    }
}

LeaseQueryImpl::~LeaseQueryImpl() {
    io_service_->stopAndPoll();
}

void
LeaseQueryImpl::parserRequesters(ConstElementPtr requesters) {
    if (!requesters || (requesters->getType() != Element::list)) {
        isc_throw(BadValue,
                  "'requesters' address list is missing or not a list");
    }

    for (auto const& address_elem : requesters->listValue()) {
        auto entry_txt = address_elem->stringValue();
        // first let's remove any whitespaces
        boost::erase_all(entry_txt, " "); // space
        boost::erase_all(entry_txt, "\t"); // tabulation

        // Is this just an address or is it CIDR?
        size_t pos = entry_txt.find("/");
        if (pos == std::string::npos) {
            try {
                IOAddress address(entry_txt);
                address_list_.insert(address);
            } catch (const std::exception& ex) {
                isc_throw(BadValue,
                      "'requesters' address entry '" << address_elem->stringValue()
                      << "' is invalid: " << ex.what());
            }
        } else {
            try {
                IOAddress prefix = IOAddress(entry_txt.substr(0, pos));

                // start with the first character after /
                auto len_txt = entry_txt.substr(pos + 1);
                int prefix_len = boost::lexical_cast<int>(len_txt);
                if ((prefix_len < std::numeric_limits<uint8_t>::min()) ||
                    (prefix_len > std::numeric_limits<uint8_t>::max())) {
                    // This exception will be handled 4 line later!
                    isc_throw(OutOfRange, "prefix length " << len_txt << " is out of range");
                }

                pool_set_.insert(prefix, prefix_len);
            } catch (const std::exception& ex) {
                isc_throw(BadValue,
                      "'requesters' CIDR entry '" << entry_txt
                      << "' is invalid: " << ex.what());
            }
        }
    }

    if (address_list_.size() == 0 && pool_set_.size() == 0) {
        isc_throw(BadValue, "'requesters' list cannot be empty");
    }
}

bool
LeaseQueryImpl::isRequester(const IOAddress& address) const {
    if (address_list_.contains(address)) {
        return (true);
    }

    return (pool_set_.contains(address));
}

bool
LeaseQueryImpl::terminated_ = false;

size_t
LeaseQueryImpl::PageSize = 100;
