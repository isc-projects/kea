// Copyright (C) 2015,2017 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef CFG_RSOO_H
#define CFG_RSOO_H

#include <cc/cfg_to_element.h>
#include <boost/shared_ptr.hpp>
#include <stdint.h>
#include <set>

namespace isc {
namespace dhcp {

/// @brief Represents configuration of the RSOO options for the DHCP server.
///
/// This class holds the set of RSOO-enabled options (see RFC6422). The list
/// of RSOO-enabled options is maintained by IANA and currently the option
/// 65 is officially RSSO-enabled. The list may be extended in the future
/// and this class allows for specifying any future RSOO-enabled options.
/// The administrator may also use existing options as RSOO-enabled.
class CfgRSOO : public isc::data::CfgToElement {
public:

    /// @brief Constructor.
    ///
    /// It adds the default (officially) RSOO-enabled options:
    /// - OPTION_ERP_LOCAL_DOMAIN_NAME
    CfgRSOO();

    /// @brief Removes designation of all options as RSOO_enabled.
    ///
    /// This method removes all designations of all options as being RSOO-enabled.
    void clear();

    /// @brief Returns whether specific option code is RSOO-enabled.
    ///
    /// @param code Option code to check
    /// @return true, if it is allowed in Relay-Supplied Options option
    bool enabled(const uint16_t code) const;

    /// @brief Marks specified option code as RSOO-enabled.
    ///
    /// @param code option to be enabled in RSOO
    void enable(const uint16_t code);

    /// @brief Unparse a configuration object
    ///
    /// @return a pointer to unparsed configuration
    virtual isc::data::ElementPtr toElement() const;

private:

    /// @brief Contains a set of options that are allowed in RSOO option
    ///
    /// RSOO stands for Relay-Supplied Options option. This is an option that
    /// is inserted by the relay agent with the intention that the server will
    /// echo those options back to the client. Only those options marked as
    /// RSOO-enabled may appear in the RSOO. Currently only option 65 is marked
    /// as such, but more options may be added in the future. See RFC6422 for details.
    std::set<uint16_t> rsoo_options_;

};

/// @name Pointers to the @c CfgRSOO objects.
//@{
/// @brief Pointer to the Non-const object.
typedef boost::shared_ptr<CfgRSOO> CfgRSOOPtr;

/// @brief Pointer to the const object.
typedef boost::shared_ptr<const CfgRSOO> ConstCfgRSOOPtr;

//@}

}
}

#endif // CFG_RSOO_H
