// Copyright (C) 2014-2024 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <exceptions/exceptions.h>
#include <dhcpsrv/ddns_params.h>

namespace isc {
namespace dhcp {

bool
DdnsParams::getUpdateOnRenew() const {
    if (!subnet_) {
        return (false);
    }

    if (pool_) {
        auto optional = pool_->getDdnsUpdateOnRenew();
        if (!optional.unspecified()) {
            return (optional.get());
        }
    }

    return (subnet_->getDdnsUpdateOnRenew().get());
}

std::string
DdnsParams::getConflictResolutionMode() const {
    if (!subnet_) {
        return ("check-with-dhcid");
    }

    if (pool_) {
        auto optional = pool_->getDdnsConflictResolutionMode();
        if (!optional.unspecified()) {
            return (optional.get());
        }
    }

    return (subnet_->getDdnsConflictResolutionMode().get());
}


util::Optional<double>
DdnsParams::getTtlPercent() const {
    if (!subnet_) {
        return (util::Optional<double>());
    }

    if (pool_) {
        auto optional = pool_->getDdnsTtlPercent();
        if (!optional.unspecified()) {
            return (optional.get());
        }
    }

    return (subnet_->getDdnsTtlPercent());
}

util::Optional<uint32_t>
DdnsParams::getTtl() const {
    if (!subnet_) {
        return (util::Optional<uint32_t>());
    }

    if (pool_) {
        auto optional = pool_->getDdnsTtl();
        if (!optional.unspecified()) {
            return (optional.get());
        }
    }

    return (subnet_->getDdnsTtl());
}

util::Optional<uint32_t>
DdnsParams::getTtlMin() const {
    if (!subnet_) {
        return (util::Optional<uint32_t>());
    }

    if (pool_) {
        auto optional = pool_->getDdnsTtlMin();
        if (!optional.unspecified()) {
            return (optional.get());
        }
    }

    return (subnet_->getDdnsTtlMin());
}

util::Optional<uint32_t>
DdnsParams::getTtlMax() const {
    if (!subnet_) {
        return (util::Optional<uint32_t>());
    }

    if (pool_) {
        auto optional = pool_->getDdnsTtlMax();
        if (!optional.unspecified()) {
            return (optional.get());
        }
    }

    return (subnet_->getDdnsTtlMax());
}

PoolPtr
DdnsParams::setPoolFromAddress(const asiolink::IOAddress& address) {
    if (!subnet_) {
        /// @todo  Not sure this can happen.
        isc_throw(InvalidOperation,
                  "DdnsParams::setPoolFromAddress called without a subnet");
    }

    pool_ = subnet_->getPool((address.isV4() ?  Lease::TYPE_V4 : Lease::TYPE_NA),
                              address, false);
    return (pool_);
}

} // namespace dhcp
} // namespace isc
