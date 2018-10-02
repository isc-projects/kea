// Copyright (C) 2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef GENERIC_BACKEND_UNITTEST_H
#define GENERIC_BACKEND_UNITTEST_H

#include <asiolink/io_address.h>
#include <dhcp/option.h>
#include <dhcpsrv/cfg_option.h>
#include <boost/shared_ptr.hpp>
#include <gtest/gtest.h>
#include <cstdint>
#include <sstream>
#include <string>

namespace isc {
namespace dhcp {
namespace test {

/// @brief Generic test fixture class with utility functions for
/// testing database backends.
class GenericBackendTest : public ::testing::Test {
public:

    /// @brief Constructor.
    GenericBackendTest();

    /// @brief Virtual destructor.
    virtual ~GenericBackendTest();

    /// @brief Creates an option descriptor holding an empty option.
    ///
    /// @param universe V4 or V6.
    /// @param option_type Option type.
    /// @param persist A boolean flag indicating if the option is always
    /// returned to the client or only when requested.
    ///
    /// @return Descriptor holding an empty option.
    OptionDescriptor createEmptyOption(const Option::Universe& universe,
                                       const uint16_t option_type,
                                       const bool persist) const;

    /// @brief Creates an instance of the option for which it is possible to
    /// specify universe, option type, persistence flag  and value in
    /// the constructor.
    ///
    /// Examples of options that can be created using this function are:
    /// - @ref OptionString
    /// - different variants of @ref OptionInt.
    ///
    /// @param universe V4 or V6.
    /// @param option_type Option type.
    /// @param persist A boolean flag indicating if the option is always
    /// returned to the client or only when requested.
    /// @param formatted A boolean value selecting if the formatted option
    /// value should be used (if true), or binary value (if false).
    /// @param value Option value to be assigned to the option.
    /// @tparam OptionType Class encapsulating the option.
    /// @tparam DataType Option value data type.
    ///
    /// @return Descriptor holding an instance of the option created.
    template<typename OptionType, typename DataType>
    OptionDescriptor createOption(const Option::Universe& universe,
                                  const uint16_t option_type,
                                  const bool persist,
                                  const bool formatted,
                                  const DataType& value) const {
        boost::shared_ptr<OptionType> option(new OptionType(universe, option_type,
                                                            value));
        std::ostringstream s;
        if (formatted) {
            // Using formatted option value. Convert option value to a
            // textual format.
            s << value;
        }
        OptionDescriptor desc(option, persist, s.str());
        return (desc);
    }

    /// @brief Creates an instance of the option for which it is possible to
    /// specify option type, persistence flag  and value in the constructor.
    ///
    /// Examples of options that can be created using this function are:
    /// - @ref Option4AddrLst
    /// - @ref Option6AddrLst
    ///
    /// @param option_type Option type.
    /// @param persist A boolean flag indicating if the option is always
    /// returned to the client or only when requested.
    /// @param formatted A boolean value selecting if the formatted option
    /// value should be used (if true), or binary value (if false).
    /// @param value Option value to be assigned to the option.
    /// @tparam OptionType Class encapsulating the option.
    /// @tparam DataType Option value data type.
    ///
    /// @return Descriptor holding an instance of the option created.
    template<typename OptionType, typename DataType>
    OptionDescriptor createOption(const uint16_t option_type,
                                  const bool persist,
                                  const bool formatted,
                                  const DataType& value) const {
        boost::shared_ptr<OptionType> option(new OptionType(option_type, value));

        std::ostringstream s;
        if (formatted) {
            // Using formatted option value. Convert option value to a
            // textual format.
            s << value;
        }

        OptionDescriptor desc(option, persist, s.str());
        return (desc);
    }

    /// @brief Creates an instance of the option holding list of IP addresses.
    ///
    /// @param option_type Option type.
    /// @param persist A boolean flag indicating if the option is always
    /// returned to the client or only when requested.
    /// @param formatted A boolean value selecting if the formatted option
    /// value should be used (if true), or binary value (if false).
    /// @param address1 First address to be included. If address is empty, it is
    /// not included.
    /// @param address2 Second address to be included. If address is empty, it
    /// is not included.
    /// @param address3 Third address to be included. If address is empty, it
    /// is not included.
    /// @tparam OptionType Class encapsulating the option.
    ///
    /// @return Descriptor holding an instance of the option created.
    template<typename OptionType>
    OptionDescriptor
    createAddressOption(const uint16_t option_type,
                        const bool persist,
                        const bool formatted,
                        const std::string& address1 = "",
                        const std::string& address2 = "",
                        const std::string& address3 = "") const {
        std::ostringstream s;
        // First address.
        typename OptionType::AddressContainer addresses;
        if (!address1.empty()) {
            addresses.push_back(asiolink::IOAddress(address1));
            if (formatted) {
                s << address1;
            }
        }
        // Second address.
        if (!address2.empty()) {
            addresses.push_back(asiolink::IOAddress(address2));
            if (formatted) {
                if (s.tellp() != std::streampos(0)) {
                    s << ",";
                }
                s << address2;
            }
        }
        // Third address.
        if (!address3.empty()) {
            addresses.push_back(asiolink::IOAddress(address3));
            if (formatted) {
                if (s.tellp() != std::streampos(0)) {
                    s << ",";
                }
                s << address3;
            }
        }

        boost::shared_ptr<OptionType> option(new OptionType(option_type,
                                                            addresses));
        OptionDescriptor desc(option, persist, s.str());
        return (desc);
    }

    /// @brief Creates an instance of the vendor option.
    ///
    /// @param universe V4 or V6.
    /// @param persist A boolean flag indicating if the option is always
    /// returned to the client or only when requested.
    /// @param formatted A boolean value selecting if the formatted option
    /// value should be used (if true), or binary value (if false).
    /// @param vendor_id Vendor identifier.
    ///
    /// @return Descriptor holding an instance of the option created.
    OptionDescriptor createVendorOption(const Option::Universe& universe,
                                        const bool persist,
                                        const bool formatted,
                                        const uint32_t vendor_id) const;
};

} // end of namespace isc::dhcp::test
} // end of namespace isc::dhcp
} // end of namespace isc

#endif

