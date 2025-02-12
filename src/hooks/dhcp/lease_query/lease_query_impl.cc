// Copyright (C) 2020-2024 Internet Systems Consortium, Inc. ("ISC")
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
    : io_service_(new IOService()), address_list_(family) {

    if (!config || (config->getType() != Element::map)) {
        isc_throw(BadValue, "Lease Query config is empty or not a map");
    }

    ConstElementPtr requesters = config->get("requesters");
    if (!requesters || (requesters->getType() != Element::list)) {
        isc_throw(BadValue,
                  "'requesters' address list is missing or not a list");
    }

    for (auto const& address_elem : requesters->listValue()) {
        try {
            IOAddress address(address_elem->stringValue());
            address_list_.insert(address);
        } catch (const std::exception& ex) {
            isc_throw(BadValue,
                      "'requesters' entry '" << address_elem->stringValue()
                      << "' is invalid: " << ex.what());
        }
    }

    if (address_list_.size() == 0) {
        isc_throw(BadValue, "'requesters' address list cannot be empty");
    }

    ConstElementPtr advanced = config->get("advanced");
    if (advanced) {
        BulkLeaseQueryService::create(this, advanced);
    }
}

LeaseQueryImpl::~LeaseQueryImpl() {
    io_service_->stopAndPoll();
}

bool
LeaseQueryImpl::isRequester(const IOAddress& address) const {
    return (address_list_.contains(address));
}

bool
LeaseQueryImpl::terminated_ = false;

size_t
LeaseQueryImpl::PageSize = 100;
