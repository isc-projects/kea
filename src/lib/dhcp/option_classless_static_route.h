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
    OptionClasslessStaticRoute()
        : Option(V4, DHO_CLASSLESS_STATIC_ROUTE), static_routes_(), data_len_(0) {
    }

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
    /// another). It may throw an exception if the @c packHeader method throws.
    ///
    /// @param buf pointer to a buffer
    /// @param check flag which indicates if checking the option length is
    /// required (used only in V4)
    void pack(util::OutputBuffer& buf, bool check = true) const override;

    /// @brief Parses option from the received buffer.
    ///
    /// @param begin iterator to first byte of option data
    /// @param end iterator to end of option data (first byte after option end)
    ///
    /// @throw OutOfRange Thrown in case option contents are truncated.
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

    /// @brief Calculates length in octets of all encoded static routes and stores it in @c
    /// data_len_
    ///
    /// Calculation is done according to static routes encoding rules in RFC3442.
    /// This should be called whenever @c static_routes_ is changed.
    void calcDataLen();

    /// @brief Parses received wire data buffer.
    ///
    /// It is used by @c unpack method in case received buffer with
    /// option data is in binary on-wire format.
    ///
    /// @param begin iterator to first byte of option data
    /// @param end iterator to end of option data (first byte after option end)
    ///
    /// @throw OutOfRange Thrown in case option contents are truncated.
    /// @throw BadValue Thrown in case received width of subnet mask value is invalid.
    void parseWireData(OptionBufferConstIter begin, OptionBufferConstIter end);

    /// @brief Parses a convenient notation of the option data, which may be used in config.
    ///
    /// As an alternative to the binary format,
    /// we provide convenience option definition as a string in format:
    /// subnet1 - router1 IP addr, subnet2 - router2 IP addr, ..., subnetN - routerN IP addr
    /// e.g.:
    /// 10.0.0.0/8 - 10.2.3.1, 10.229.0.128/25 - 10.1.0.3
    ///
    /// This notation may be used in the server config, thanks to the possibility of specifying
    /// data for binary option as a single-quoted text string within double quotes
    /// (@c csv-format flag must be set to @c false).
    ///
    /// @param config_txt convenient notation of the option data received as string
    ///
    /// @throw BadValue Thrown in case parser found wrong format of received string.
    void parseConfigData(const std::string& config_txt);
};

/// A shared pointer to the @c OptionClasslessStaticRoute object.
typedef boost::shared_ptr<OptionClasslessStaticRoute> OptionClasslessStaticRoutePtr;

}  // namespace dhcp
}  // namespace isc

#endif  // OPTION_CLASSLESS_STATIC_ROUTE_H
