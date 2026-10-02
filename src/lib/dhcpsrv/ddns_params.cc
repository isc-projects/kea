// Copyright (C) 2014-2025 Internet Systems Consortium, Inc. ("ISC")
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
DdnsParams::getEnableUpdates() const {
    if (!subnet_) {
        return (false);
    }

    if (pool_) {
        auto optional = pool_->getDdnsSendUpdates();
        if (!optional.unspecified()) {
            return (optional.get());
        }
    }

    return (d2_client_enabled_ && subnet_->getDdnsSendUpdates().get());
}

bool
DdnsParams::getOverrideNoUpdate() const {
    if (!subnet_) {
        return (false);
    }

    if (pool_) {
        auto optional = pool_->getDdnsOverrideNoUpdate();
        if (!optional.unspecified()) {
            return (optional.get());
        }
    }

    return (subnet_->getDdnsOverrideNoUpdate().get());
}

bool DdnsParams::getOverrideClientUpdate() const {
    if (!subnet_) {
        return (false);
    }

    if (pool_) {
        auto optional = pool_->getDdnsOverrideClientUpdate();
        if (!optional.unspecified()) {
            return (optional.get());
        }
    }

    return (subnet_->getDdnsOverrideClientUpdate().get());
}

D2ClientConfig::ReplaceClientNameMode
DdnsParams::getReplaceClientNameMode() const {
    if (!subnet_) {
        return (D2ClientConfig::RCM_NEVER);
    }

    if (pool_) {
        auto optional = pool_->getDdnsReplaceClientNameMode();
        if (!optional.unspecified()) {
            return (optional.get());
        }
    }

    return (subnet_->getDdnsReplaceClientNameMode().get());
}

std::string
DdnsParams::getGeneratedPrefix() const {
    if (!subnet_) {
        return ("");
    }

    if (pool_) {
        auto optional = pool_->getDdnsGeneratedPrefix();
        if (!optional.unspecified()) {
            return (optional.get());
        }
    }

    return (subnet_->getDdnsGeneratedPrefix().get());
}

std::string
DdnsParams::getQualifyingSuffix() const {
    if (!subnet_) {
        return ("");
    }

    if (pool_) {
        auto optional = pool_->getDdnsQualifyingSuffix();
        if (!optional.unspecified()) {
            return (optional.get());
        }
    }

    return (subnet_->getDdnsQualifyingSuffix().get());
}

std::string
DdnsParams::getHostnameCharSet() const {
    if (!subnet_) {
        return ("");
    }

    return (subnet_->getHostnameCharSet().get());
}

std::string
DdnsParams::getHostnameCharReplacement() const {
    if (!subnet_) {
        return ("");
    }

    return (subnet_->getHostnameCharReplacement().get());
}

util::str::StringSanitizerPtr
DdnsParams::getHostnameSanitizer() const {
    util::str::StringSanitizerPtr sanitizer;
    if (subnet_) {
        std::string char_set = getHostnameCharSet();
        if (!char_set.empty()) {
            try {
                sanitizer.reset(new util::str::StringSanitizer(char_set,
                                                               getHostnameCharReplacement()));
            } catch (const std::exception& ex) {
                isc_throw(BadValue, "hostname_char_set_: '" << char_set <<
                                    "' is not a valid regular expression");
            }
        }
    }

    return (sanitizer);
}

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
