// Copyright (C) 2012, 2013 Internet Systems Consortium, Inc. ("ISC")
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

#ifndef OPTION_SPACE_H
#define OPTION_SPACE_H

#include <exceptions/exceptions.h>
#include <boost/shared_ptr.hpp>
#include <map>
#include <stdint.h>
#include <string>

namespace isc {
namespace dhcp {

/// @brief Exception to be thrown when invalid option space
/// is specified.
class InvalidOptionSpace : public Exception {
public:
    InvalidOptionSpace(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) { };
};

/// OptionSpace forward declaration.
class OptionSpace;
/// A pointer to OptionSpace object.
typedef boost::shared_ptr<OptionSpace> OptionSpacePtr;
/// A collection of option spaces.
typedef std::map<std::string, OptionSpacePtr> OptionSpaceCollection;

/// @brief Option code space.
///
/// This class represents single option space. The option spaces are used
/// to group DHCP options having unique option codes. The special type
/// of the option space is so called "vendor option space". It groups
/// sub-options being sent within Vendor Encapsulated Options. These are
/// option with code 43 for DHCPv4 and option with code 17 for DHCPv6.
/// The option spaces are assigned to option instances represented by
/// isc::dhcp::Option and other classes derived from it. Each particular
/// option may belong to multiple option spaces.
class OptionSpace {
public:

    /// @brief Constructor.
    ///
    /// @param name option space name.
    /// @param vendor_space boolean value that indicates that the object
    /// describes the vendor space.
    ///
    /// @throw isc::dhcp::InvalidOptionSpace if given option space name
    /// contains invalid characters or is empty. This constructor uses
    /// \ref validateName function to check that the specified name is
    /// correct.
    OptionSpace(const std::string& name, const bool vendor_space = false);

    /// @brief Mark option space as non-vendor space.
    void clearVendorSpace() {
        vendor_space_ = false;
    }

    /// @brief Return option space name.
    ///
    /// @return option space name.
    const std::string& getName() const { return (name_); }

    /// @brief Check if option space is a vendor space.
    ///
    /// @return boolean value that indicates if the object describes
    /// the vendor space.
    bool isVendorSpace() const { return (vendor_space_); }

    /// @brief Mark option space as vendor space.
    void setVendorSpace() {
        vendor_space_ = true;
    }

    /// @brief Checks that the provided option space name is valid.
    ///
    /// It is expected that option space name consists of upper or
    /// lower case letters or digits. Also, it may contain underscores
    /// or dashes. Other characters are prohibited. The empty option
    /// space names are invalid.
    ///
    /// @param name option space name to be validated.
    ///
    /// @return true if the option space is valid, else it returns false.
    static bool validateName(const std::string& name);

private:
    std::string name_;  ///< Holds option space name.

    bool vendor_space_; ///< Is this the vendor space?

};

/// @brief DHCPv6 option space.
///
/// This class extends the base class with support for enterprise numbers.
/// The enterprise numbers are assigned by IANA to various organizations
/// and they are carried as uint32_t integers in DHCPv6 Vendor Specific
/// Information Options (VSIO). For more information refer to RFC3315.
/// All option spaces that group VSIO options must have enterprise number
/// set. It can be set using a constructor or \ref setVendorSpace function.
class OptionSpace6 : public OptionSpace {
public:

    /// @brief Constructor for non-vendor-specific options.
    ///
    /// This constructor marks option space as non-vendor specific.
    ///
    /// @param name option space name.
    OptionSpace6(const std::string& name);

    /// @brief Constructor for vendor-specific options.
    ///
    /// This constructor marks option space as vendor specific and sets
    /// enterprise number to a given value.
    ///
    /// @param name option space name.
    /// @param enterprise_number enterprise number.
    OptionSpace6(const std::string& name, const uint32_t enterprise_number);

    /// @brief Return enterprise number for the option space.
    ///
    /// @return enterprise number.
    uint32_t getEnterpriseNumber() const { return (enterprise_number_); }

    /// @brief Mark option space as VSIO option space.
    ///
    /// @param enterprise_number enterprise number.
    void setVendorSpace(const uint32_t enterprise_number);

private:
    
    uint32_t enterprise_number_; ///< IANA assigned enterprise number.
};

} // namespace isc::dhcp
} // namespace isc

#endif // OPTION_SPACE_H
