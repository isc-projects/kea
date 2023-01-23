// Copyright (C) 2013-2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef OPTION_VENDOR_H
#define OPTION_VENDOR_H

#include <dhcp/libdhcp++.h>
#include <dhcp/option.h>
#include <dhcp/option_data_types.h>
#include <util/io_utilities.h>

#include <stdint.h>

namespace isc {
namespace dhcp {

/// Indexes for fields in vendor-class (17) DHCPv6 option
const int VENDOR_CLASS_ENTERPRISE_ID_INDEX = 0;
const int VENDOR_CLASS_DATA_LEN_INDEX = 1;
const int VENDOR_CLASS_STRING_INDEX = 2;

/// @brief This class represents vendor-specific information option.
///
/// As specified in RFC3925, the option formatting is slightly different
/// for DHCPv4 than DHCPv6. The DHCPv4 Option includes additional field
/// holding vendor data length.
class OptionVendor: public Option {
public:
    /// @brief Constructor.
    ///
    /// @param u universe (V4 or V6)
    /// @param vendor_id vendor enterprise-id (unique 32 bit integer)
    OptionVendor(Option::Universe u, const uint32_t vendor_id);

    /// @brief Constructor.
    ///
    /// This constructor creates option from a buffer. This constructor
    /// may throw exception if \ref unpack function throws during buffer
    /// parsing.
    ///
    /// @param u universe (V4 or V6)
    /// @param begin iterator to first byte of option data.
    /// @param end iterator to end of option data (first byte after option end).
    ///
    /// @throw isc::OutOfRange if provided buffer is shorter than data size.
    /// @todo Extend constructor to set encapsulated option space name.
    OptionVendor(Option::Universe u, OptionBufferConstIter begin,
                 OptionBufferConstIter end);

    /// @brief Copies this option and returns a pointer to the copy.
    OptionPtr clone() const;

    /// @brief Writes option in wire-format to buf, returns pointer to first
    /// unused byte after stored option.
    ///
    /// @param [out] buf buffer (option will be stored here)
    /// @param check if set to false, allows options larger than 255 for v4
    virtual void pack(isc::util::OutputBuffer& buf, bool check = true) const;

    /// @brief Parses received buffer
    ///
    /// Parses received buffer and returns offset to the first unused byte after
    /// parsed option.
    ///
    /// @param begin iterator to first byte of option data
    /// @param end iterator to end of option data (first byte after option end)
    ///
    /// @throw isc::SkipRemainingOptionsBuffer if an error is encountered
    /// unpacking the option.  This exception is thrown to indicate to the
    /// caller that a: remaining options cannot be parsed and b: the packet
    /// should be considered for processing anyway.
    virtual void unpack(OptionBufferConstIter begin, OptionBufferConstIter end);

    /// @brief Sets enterprise identifier
    ///
    /// @param vendor_id vendor identifier
    void setVendorId(const uint32_t vendor_id) {
        vendor_id_ = vendor_id;
    }

    /// @brief Returns enterprise identifier
    ///
    /// @return enterprise identifier
    uint32_t getVendorId() const {
        return (vendor_id_);
    }

    /// @brief returns complete length of option
    ///
    /// Returns length of this option, including option header and suboptions
    ///
    /// @return length of this option
    virtual uint16_t len() const;

    /// @brief Returns the option in the textual format.
    ///
    /// @param indent Number of spaces to be inserted before the text.
    ///
    /// @return Vendor option in the textual format.
    virtual std::string toText(int indent = 0) const;

private:

    /// @brief Enterprise-id
    uint32_t vendor_id_;
};

/// Pointer to a vendor option
typedef boost::shared_ptr<OptionVendor> OptionVendorPtr;

} // isc::dhcp namespace
} // isc namespace

#endif // OPTION_VENDOR_H
