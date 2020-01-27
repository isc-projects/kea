// Copyright (C) 2012-2020 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef OPTION_SPACE_H
#define OPTION_SPACE_H

#include <dhcp/std_option_defs.h>
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

/// @brief DHCP option space.
///
/// This class represents single option space. The option spaces are used
/// to group DHCP options having unique option codes. The special type
/// of the option space is so called "vendor specific option space".
/// It groups sub-options being sent within Vendor Encapsulated Options.
/// For DHCPv4 it is the option with code 43. The option spaces are
/// assigned to option instances represented by isc::dhcp::Option and
/// other classes derived from it. Each particular option may belong to
/// multiple option spaces.
/// This class may be used to represent any DHCPv4 option space. If the
/// option space is to group DHCPv4 Vendor Encapsulated Options then
/// "vendor space" flag must be set using \ref OptionSpace::setVendorSpace
/// or the argument passed to the constructor. In theory, this class can
/// be also used to represent non-vendor specific DHCPv6 option space
/// but this is discouraged. For DHCPv6 option spaces the OptionSpace6
/// class should be used instead.
///
/// @note this class is intended to be used to represent DHCPv4 option
/// spaces only. However, it hasn't been called OptionSpace4 (that would
/// suggest that it is specific to DHCPv4) because it can be also
/// used to represent some DHCPv6 option spaces and is a base class
/// for \ref OptionSpace6. Thus, if one declared the container as follows:
/// @code
/// std::vector<OptionSpace4> container;
/// @endcode
/// it would suggest that the container holds DHCPv4 option spaces while
/// it could hold both DHCPv4 and DHCPv6 option spaces as the OptionSpace6
/// object could be upcast to OptionSpace4. This confusion does not appear
/// when OptionSpace is used as a name for the base class.
class OptionSpace {
public:

    /// @brief Constructor.
    ///
    /// @param name option space name.
    /// @param vendor_space boolean value that indicates that the object
    /// describes the vendor specific option space.
    ///
    /// @throw isc::dhcp::InvalidOptionSpace if given option space name
    /// contains invalid characters or is empty. This constructor uses
    /// \ref validateName function to check that the specified name is
    /// correct.
    OptionSpace(const std::string& name, const bool vendor_space = false);

    /// @brief Return option space name.
    ///
    /// @return option space name.
    const std::string& getName() const { return (name_); }

    /// @brief Mark option space as non-vendor space.
    void clearVendorSpace() {
        vendor_space_ = false;
    }

    /// @brief Check if option space is vendor specific.
    ///
    /// @return boolean value that indicates if the object describes
    /// the vendor specific option space.
    bool isVendorSpace() const { return (vendor_space_); }

    /// @brief Mark option space as vendor specific.
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

/// @brief DHCPv6 option space with enterprise number assigned.
///
/// This class extends the base class with the support for enterprise numbers.
/// The enterprise numbers are assigned by IANA to various organizations
/// and they are carried as uint32_t integers in DHCPv6 Vendor Specific
/// Information Options (VSIO). For more information refer to RFC 8415.
/// All option spaces that group VSIO options must have enterprise number
/// set. It can be set using a constructor or \ref setVendorSpace function.
/// The extra functionality of this class (enterprise numbers) allows to
/// represent DHCPv6 vendor-specific option spaces but this class is also
/// intended to be used for all other DHCPv6 option spaces. That way all
/// DHCPv6 option spaces can be stored in the container holding OptionSpace6
/// objects. Also, it is easy to mark vendor-specific option space as non-vendor
/// specific option space (and the other way around) without a need to cast
/// between OptionSpace and OptionSpace6 types.
class OptionSpace6 : public OptionSpace {
public:

    /// @brief Constructor for non-vendor-specific options.
    ///
    /// This constructor marks option space as non-vendor specific.
    ///
    /// @param name option space name.
    ///
    /// @throw isc::dhcp::InvalidOptionSpace if given option space name
    /// contains invalid characters or is empty. This constructor uses
    /// \ref OptionSpace::validateName function to check that the specified
    /// name is correct.
    OptionSpace6(const std::string& name);

    /// @brief Constructor for vendor-specific options.
    ///
    /// This constructor marks option space as vendor specific and sets
    /// enterprise number to a given value.
    ///
    /// @param name option space name.
    /// @param enterprise_number enterprise number.
    ///
    /// @throw isc::dhcp::InvalidOptionSpace if given option space name
    /// contains invalid characters or is empty. This constructor uses
    /// \ref OptionSpace::validateName function to check that the specified
    /// name is correct.
    OptionSpace6(const std::string& name, const uint32_t enterprise_number);

    /// @brief Return enterprise number for the option space.
    ///
    /// @return enterprise number.
    uint32_t getEnterpriseNumber() const { return (enterprise_number_); }

    /// @brief Mark option space as vendor specific.
    ///
    /// @param enterprise_number enterprise number.
    void setVendorSpace(const uint32_t enterprise_number);

private:

    uint32_t enterprise_number_; ///< IANA assigned enterprise number.
};

}  // namespace dhcp
}  // namespace isc

#endif // OPTION_SPACE_H
