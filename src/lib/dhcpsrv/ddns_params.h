// Copyright (C) 2014-2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef DDNS_PARAMS_H
#define DDNS_PARAMS_H

#include <cc/data.h>
#include <dhcpsrv/subnet.h>
#include <util/optional.h>
#include <util/str.h>

#include <boost/shared_ptr.hpp>

namespace isc {
namespace dhcp {

/// @brief Convenience container for conveying DDNS behavioral parameters
/// It is intended to be created per Packet exchange using the selected
/// subnet passed into functions that require them
class DdnsParams {
public:
    /// @brief Default constructor
    DdnsParams() : subnet_(), d2_client_enabled_(false) {}

    /// @brief Constructor
    ///
    /// @param subnet Pointer to subnet instance to use for fetching
    /// parameter values (typically this is the selected subnet).
    /// @param d2_client_enabled flag which indicates whether or not
    /// D2Client is enabled (typically the value should come from
    /// global D2Client configuration).
    DdnsParams(const ConstSubnetPtr& subnet, bool d2_client_enabled)
        : subnet_(subnet),
          d2_client_enabled_(d2_client_enabled) {}

    /// @brief Returns whether or not DHCP DDNS updating is enabled.
    /// The value is the logical AND of d2_client_enabled_ and
    /// the value returned by subnet_'s getDdnsSendUpdates().
    ///
    /// @return True if updates are enabled, false otherwise or if
    /// subnet_ is empty.
    bool getEnableUpdates() const;

    /// @brief Returns whether or not Kea should perform updates, even if
    /// client requested no updates.
    ///
    /// @return The value from the subnet_ or false if subnet_ is empty.
    bool getOverrideNoUpdate() const;

    /// @brief Returns whether or not Kea should perform updates, even if
    /// client requested delegation.
    ///
    /// @return The value from the subnet_ or false if subnet_ is empty.
    bool getOverrideClientUpdate() const;

    /// @brief Returns how Kea should handle the domain-name supplied by
    /// the client.
    ///
    /// @return The value from the subnet_ or RCM_NEVER if subnet_ is empty.
    D2ClientConfig::ReplaceClientNameMode getReplaceClientNameMode() const;

    /// @brief Returns the Prefix Kea should use when generating domain-names.
    ///
    /// @return The value from the subnet_ or an empty string if subnet_ is empty.
    std::string getGeneratedPrefix() const;

    /// @brief Returns the suffix Kea should use when to qualify partial
    /// domain-names.
    ///
    /// @return The value from the subnet_ or an empty string if subnet_ is empty.
    std::string getQualifyingSuffix() const;

    /// @brief Returns the regular expression describing invalid characters
    /// for client hostnames.  If empty, host name scrubbing should not be done.
    ///
    /// @return The value from the subnet_ or an empty string if subnet_ is empty.
    std::string getHostnameCharSet() const;

    /// @brief Returns the string to replace invalid characters when scrubbing
    /// hostnames. Meaningful only if hostname_char_set_ is not empty.
    ///
    /// @return The value from the subnet_ or an empty string if subnet_ is empty.
    std::string getHostnameCharReplacement() const;

    /// @brief Returns a regular expression string sanitizer
    ///
    /// If the value returned by getHostnameCharSet() is not empty, then it is
    /// used in conjunction the value returned by getHostnameCharReplacment()
    /// (which may be empty) to create and return a StringSanitizer instance.
    /// Otherwise it will return an empty pointer.
    ///
    /// @return pointer to the StringSanitizer instance or an empty pointer
    /// @throw BadValue if the compilation fails.
    isc::util::str::StringSanitizerPtr getHostnameSanitizer() const;

    /// @brief Returns whether or not DNS should be updated when leases renew.
    ///
    /// If this is true, DNS should always be updated when leases are
    /// extended (i.e. renewed/rebound) even if the DNS information
    /// has not changed.
    ///
    /// @return True if updates should always be performed.
    bool getUpdateOnRenew() const;

    /// @brief Returns percent of lease lifetime to use for TTL
    ///
    /// This value, if greater than zero, is used to calculate the lease lifetime
    /// passed to D2 in the NCR.  Otherwise the value is calculated per RFC 4702.
    ///
    /// @return TTL percent as an Optional.
    util::Optional<double> getTtlPercent() const;

    /// @brief Returns explicit TTL to use
    ///
    /// This value, if greater than zero, is used as the lifetime
    /// passed to D2 in the NCR.
    ///
    /// @return TTL as an Optional.
    util::Optional<uint32_t> getTtl() const;

    /// @brief Returns the minimum TTL to use
    ///
    /// This value, if greater than zero, is used as the lower boundary
    /// for calculated TTLs.
    ///
    /// @return TTL minimum as an Optional.
    util::Optional<uint32_t> getTtlMin() const;

    /// @brief Returns the maximum TTL to use
    ///
    /// This value, if greater than zero, is used as the upper boundary
    /// for calculated TTLs.
    ///
    /// @return TTL maximum as an Optional.
    util::Optional<uint32_t> getTtlMax() const;

    /// @brief Returns the DDNS config resolution mode for kea-dhcp-ddns
    ///
    /// This value is communicated to D2 via the NCR.
    ///
    /// @return the DDNS conflict resolution mode
    std::string getConflictResolutionMode() const;

    /// @brief Returns the subnet-id of the subnet associated with these parameters
    ///
    /// @return value of subnet-id (or 0 if no subnet is associated)
    SubnetID getSubnetId() const {
        if (subnet_) {
            return (subnet_->getID());
        } else {
            return (0);
        }
    }

    /// @brief Sets the pool based on the current subnet and given address
    ///
    /// @param address lease address for which the pool is desired.
    /// @return a pointer to the newly set current pool or an
    /// empty pointer if there is either no subnet or no matching
    /// pool.
    PoolPtr setPoolFromAddress(const asiolink::IOAddress& address);

    /// @brief Resets the current pool.
    void resetPool() {
        pool_.reset();
    }

    /// @brief Fetches the current pool.
    ///
    /// @return Pointer to the current pool, may be an empty
    /// pointer.
    PoolPtr getPool() const {
        return (pool_);
    }

private:
    /// @brief Subnet from which values should be fetched.
    ConstSubnetPtr subnet_;

    /// @brief Flag indicating whether or not the D2Client is enabled.
    bool d2_client_enabled_;

    /// @brief Pool within the subnet from which values should be fetched.
    PoolPtr pool_;
};

/// @brief Defines a pointer for DdnsParams instances.
typedef boost::shared_ptr<DdnsParams> DdnsParamsPtr;

}  // namespace dhcp
}  // namespace isc

#endif // DDNS_PARAMS_H
