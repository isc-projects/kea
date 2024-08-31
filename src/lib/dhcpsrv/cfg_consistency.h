// Copyright (C) 2018-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef CFG_CONSISTENCY_H
#define CFG_CONSISTENCY_H

#include <cc/cfg_to_element.h>
#include <cc/user_context.h>

namespace isc {
namespace dhcp {


/// @brief Parameters for various consistency checks.
///
class CfgConsistency : public isc::data::UserContext, public isc::data::CfgToElement {

    public:

    /// @brief Values for subnet-id sanity checks done for leases.
    enum LeaseSanity {
        LEASE_CHECK_NONE, // Skip sanity checks
        LEASE_CHECK_WARN, // Print a warning if subnet-id is incorrect.
        LEASE_CHECK_FIX, // If subnet-id is incorrect, try to fix it (try to pick
                              // appropriate subnet, but if it fails, keep the lease,
                              // despite its broken subnet-id.
        LEASE_CHECK_FIX_DEL,  // If subnet-id is incorrect, try to fix it (try to pick
                              // appropriate subnet.  If it fails, delete broken lease.
        LEASE_CHECK_DEL       // Delete leases with invalid subnet-id.
    };

    /// @brief Values for extended info sanity checks done for leases.
    enum ExtendedInfoSanity {
        EXTENDED_INFO_CHECK_NONE, // Skip sanity checks.
        EXTENDED_INFO_CHECK_FIX, // Fix extended info common inconsistencies.
        EXTENDED_INFO_CHECK_STRICT, // Fix extended info inconsistencies which
                                    // have an impact for Bulk Lease Query.
        EXTENDED_INFO_CHECK_PEDANTIC // Fix all extended info inconsistencies.
    };

    /// @brief Constructor
    CfgConsistency()
        : lease_sanity_check_(LEASE_CHECK_NONE),
          extended_info_sanity_check_(EXTENDED_INFO_CHECK_FIX) {
    }

    /// @brief Returns JSON representation
    ///
    /// @return Element pointer
    virtual isc::data::ElementPtr toElement() const;

    /// @brief Sets specific sanity checks mode for leases.
    ///
    /// @param l sanity checks mode
    void setLeaseSanityCheck(LeaseSanity l) {
        lease_sanity_check_ = l;
    }

    /// @brief Returns specific sanity checks mode for leases.
    ///
    /// @return sanity checks mode
    LeaseSanity getLeaseSanityCheck() const {
        return (lease_sanity_check_);
    }

    /// @brief Converts lease sanity check value to printable text.
    ///
    /// @param check_type sanity mode to be converted
    static std::string sanityCheckToText(LeaseSanity check_type);

    /// @brief Sets specific sanity checks mode for extended info.
    ///
    /// @param l sanity checks mode
    void setExtendedInfoSanityCheck(ExtendedInfoSanity l) {
        extended_info_sanity_check_ = l;
    }

    /// @brief Returns specific sanity checks mode for extended info.
    ///
    /// @return sanity checks mode
    ExtendedInfoSanity getExtendedInfoSanityCheck() const {
        return (extended_info_sanity_check_);
    }

    /// @brief Converts extended info sanity check value to printable text.
    ///
    /// @param check_type sanity mode to be converted
    static std::string sanityCheckToText(ExtendedInfoSanity check_type);

 private:

    /// @brief lease sanity checks mode.
    LeaseSanity lease_sanity_check_;

    /// @brief extended info sanity checks mode.
    ExtendedInfoSanity extended_info_sanity_check_;
};

/// @brief Type used to for pointing to CfgConsistency structure
typedef boost::shared_ptr<CfgConsistency> CfgConsistencyPtr;

/// @brief Type used to for pointing to const CfgConsistency structure
typedef boost::shared_ptr<const CfgConsistency> ConstCfgConsistencyPtr;

} // namespace isc::dhcp
} // namespace isc

#endif /* CFG_CONSISTENCY_H */
