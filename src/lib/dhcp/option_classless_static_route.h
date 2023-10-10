// Copyright (C) 2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef OPTION_CLASSLESS_STATIC_ROUTE_H
#define OPTION_CLASSLESS_STATIC_ROUTE_H

#include <dhcp/dhcp4.h>
#include <dhcp/option.h>
#include <dhcp/option_data_types.h>

namespace isc {
namespace dhcp {

/// @brief Defines a tuple of Subnet number, Subnet mask width and IPv4 router address.
typedef std::tuple<asiolink::IOAddress, uint8_t, asiolink::IOAddress> StaticRouteTuple;

/// @brief Represents DHCPv4 Classless Static Route %Option (code 121).
class OptionClasslessStaticRoute : public Option {
public:
    /// @brief Empty Constructor
    OptionClasslessStaticRoute() : Option(V4, DHO_CLASSLESS_STATIC_ROUTE), static_routes_(), data_len_(0) {}

    /// @brief Constructor of the %Option from on-wire data.
    ///
    /// This constructor creates an instance of the option using a buffer with
    /// on-wire data. It may throw an exception if the @c unpack method throws.
    ///
    /// @param begin Iterator pointing to the beginning of the buffer holding an
    /// option.
    /// @param end Iterator pointing to the end of the buffer holding an option.
    OptionClasslessStaticRoute(OptionBufferConstIter begin, OptionBufferConstIter end);

    /// @brief Copies this option and returns a pointer to the copy.
    ///
    /// @return Pointer to the copy of the option.
    OptionPtr clone() const override;

    /// @brief Writes option in wire-format to a buffer.
    ///
    /// Writes option in wire-format to buffer, returns pointer to first unused
    /// byte after stored option (that is useful for writing options one after
    /// another).
    ///
    /// @param buf pointer to a buffer
    /// @param check flag which indicates if checking the option length is
    /// required (used only in V4)
    ///
    /// @throw
    void pack(util::OutputBuffer& buf, bool check = true) const override;

    /// @brief Parses received wire data buffer.
    ///
    /// @param begin iterator to first byte of option data
    /// @param end iterator to end of option data (first byte after option end)
    /// @throw
    void unpack(OptionBufferConstIter begin, OptionBufferConstIter end) override;

    /// @brief Returns string representation of the option.
    ///
    /// @param indent number of spaces before printing text
    ///
    /// @return string with text representation.
    std::string toText(int indent = 0) const override;

    /// @brief Returns length of the complete option (data length + DHCPv4
    /// option header)
    ///
    /// @return length of the option
    uint16_t len() const override;

    /// @brief Adds static route to collection of all static routes.
    /// @param route A tuple defining new static route
    void addRoute(const StaticRouteTuple& route);

private:
    /// @brief Container holding all static routes.
    std::vector<StaticRouteTuple> static_routes_;

    /// @brief Length in octets of all encoded static routes.
    uint16_t data_len_;

    /// @brief Calculates subnet mask width from given uint_32 representation of subnet mask.
    /// @param subnet_mask uint_32 representation of a subnet mask IPv4 address
    /// @return width of subnet mask in a range of 0-32
    static uint8_t calcMaskWidth(uint32_t subnet_mask);

    /// @brief Encodes destination descriptor as per RFC3442.
    /// @param route static route tuple
    /// @return Contents of the destination descriptor as a vector
    /// of bytes in network-byte order.
    static std::vector<uint8_t> encodeDestinationDescriptor(const StaticRouteTuple& route);

    /// @brief Calculates number of significant octets of the subnet as per RFC3442.
    ///
    /// The significant portion of the subnet number is simply all of the
    /// octets of the subnet number where the corresponding octet in the
    /// subnet mask is non-zero. The number of significant octets is the
    /// width of the subnet mask divided by eight, rounding up.
    ///
    /// @param mask_width width of subnet mask
    /// @return number of significant octets
    static uint8_t calcSignificantOctets(const uint8_t& mask_width);

    /// @brief Calculates length in octets of all encoded static routes and stores it in @c data_len_
    ///
    /// Calculation is done according to static routes encoding rules in RFC3442.
    /// This should be called whenever @c static_routes_ is changed.
    void calcDataLen();
};

/// A pointer to the @c OptionClasslessStaticRoute object.
typedef boost::shared_ptr<OptionClasslessStaticRoute> OptionClasslessStaticRoutePtr;

}  // namespace dhcp
}  // namespace isc

#endif  // OPTION_CLASSLESS_STATIC_ROUTE_H
