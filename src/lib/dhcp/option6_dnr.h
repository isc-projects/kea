// Copyright (C) 2023-2024 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef OPTION6_DNR_H
#define OPTION6_DNR_H

#include <dhcp/option4_dnr.h>

namespace isc {
namespace dhcp {

/// @brief Represents DHCPv6 Encrypted DNS %Option (code 144).
///
/// This option has been defined in the @c RFC9463 and it has a following structure:
/// - option-code = 144 (2 octets)
/// - option-len (2 octets)
/// - Service Priority (2 octets)
/// - ADN Length (2 octets)
/// - Authentication Domain Name (variable length)
/// - Addr Length (2 octets)
/// - IPv6 Address(es) (variable length)
/// - Service Parameters (variable length).
class Option6Dnr : public Option, public DnrInstance {
public:
    /// @brief Constructor of the %Option from on-wire data.
    ///
    /// This constructor creates an instance of the option using a buffer with
    /// on-wire data. It may throw an exception if the @c unpack method throws.
    ///
    /// @param begin Iterator pointing to the beginning of the buffer holding an
    /// option.
    /// @param end Iterator pointing to the end of the buffer holding an option.
    /// @param convenient_notation Flag stating whether data in buffer is a convenient
    ///                            notation string that needs custom parsing or binary
    ///                            data. Defaults to @c false.
    ///
    /// @throw OutOfRange Thrown in case of truncated data.
    /// @throw BadValue Thrown when @c DnrInstance::unpackAdn(begin,end) throws.
    /// @throw InvalidOptionDnrDomainName Thrown when @c DnrInstance::unpackAdn(begin,end) throws.
    Option6Dnr(OptionBufferConstIter begin,
               OptionBufferConstIter end,
               bool convenient_notation = false);

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
    /// @throw InvalidOptionDnrDomainName Thrown when Option's mandatory field ADN is empty.
    void pack(util::OutputBuffer& buf, bool check = false) const override;

    /// @brief Parses received wire data buffer.
    ///
    /// @param begin iterator to first byte of option data
    /// @param end iterator to end of option data (first byte after option end)
    ///
    /// @throw OutOfRange Thrown in case of truncated data.
    /// @throw BadValue Thrown when @c DnrInstance::unpackAdn(begin,end) throws.
    /// @throw InvalidOptionDnrDomainName Thrown when @c DnrInstance::unpackAdn(begin,end) throws.
    void unpack(OptionBufferConstIter begin, OptionBufferConstIter end) override;

    /// @brief Returns string representation of the option.
    ///
    /// @param indent number of spaces before printing text
    ///
    /// @return string with text representation.
    std::string toText(int indent = 0) const override;

    /// @brief Returns length of the complete option (data length + DHCPv4/DHCPv6
    /// option header)
    ///
    /// @return length of the option
    uint16_t len() const override;

    /// @brief Writes the IP address(es) in the wire format into a buffer.
    ///
    /// The IP address(es) (@c ip_addresses_) data is appended at the end
    /// of the buffer.
    ///
    /// @param [out] buf buffer where IP address(es) will be written.
    ///
    /// @throw BadValue Thrown when trying to pack address which is not an IPv6 address
    void packAddresses(isc::util::OutputBuffer& buf) const override;

    /// @brief Unpacks IP address(es) from wire data and stores it/them in @c ip_addresses_.
    ///
    /// It may throw in case of malformed data detected during parsing.
    ///
    /// @param begin beginning of the buffer from which the field will be read
    /// @param end end of the buffer from which the field will be read
    ///
    /// @throw OutOfRange Thrown in case of malformed data detected during parsing e.g.
    /// Addr Len not divisible by 16, Addr Len is 0, addresses data truncated etc.
    /// @throw BadValue Thrown when trying to unpack address which is not an IPv6 address
    void unpackAddresses(OptionBufferConstIter& begin, OptionBufferConstIter end) override;

private:
    /// @brief Flag stating whether the %Option was constructed with a convenient notation string,
    /// that needs custom parsing, or binary data.
    bool convenient_notation_;
};

/// A pointer to the @c Option6Dnr object.
typedef boost::shared_ptr<Option6Dnr> Option6DnrPtr;

}  // namespace dhcp
}  // namespace isc

#endif  // OPTION6_DNR_H
