// Copyright (C) 2013 Internet Systems Consortium, Inc. ("ISC")
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

#ifndef OPTION6_CLIENT_FQDN_H
#define OPTION6_CLIENT_FQDN_H

#include <dhcp/option.h>
#include <dns/name.h>

#include <string>

namespace isc {
namespace dhcp {

/// @brief Exception thrown when invalid flags have been specified for
/// DHCPv6 Client Fqdn %Option.
class InvalidFqdnOptionFlags : public Exception {
public:
    InvalidFqdnOptionFlags(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) {}
};

/// @brief Exception thrown when invalid domain name is specified.
class InvalidFqdnOptionDomainName : public Exception {
public:
    InvalidFqdnOptionDomainName(const char* file, size_t line,
                                const char* what) :
        isc::Exception(file, line, what) {}
};

/// Forward declaration to implementation of @c Option6ClientFqdn class.
class Option6ClientFqdnImpl;

/// @brief Represents DHCPv6 Client FQDN %Option (code 39).
///
/// This option has been defined in the RFC 4704 and it has a following
/// structure:
/// - option-code = 39 (2 octets)
/// - option-len (2 octets)
/// - flags (1 octet)
/// - domain-name - variable length field comprising partial or fully qualified
/// domain name.
///
/// The flags field has the following structure:
/// @code
///        0 1 2 3 4 5 6 7
///       +-+-+-+-+-+-+-+-+
///       |  MBZ    |N|O|S|
///       +-+-+-+-+-+-+-+-+
/// @endcode
/// where:
/// - N flag specifies whether server should (0) or should not (1) perform DNS
///  Update,
/// - O flag is set by the server to indicate that it has overridden client's
/// preference set with the S bit.
/// - S flag specifies whether server should (1) or should not (0) perform
/// forward (FQDN-to-address) updates.
///
/// This class exposes a set of functions to modify flags and check their
/// correctness.
///
/// Domain names being carried by DHCPv6 Client Fqdn %Option can be fully
/// qualified or partial. Partial domain names are encoded similar to the
/// fully qualified domain names, except that they lack terminating zero
/// at the end of their wire representation. It is also accepted to create an
/// instance of this option which has empty domain-name. Clients use empty
/// domain-names to indicate that server should generate complete fully
/// qualified domain-name.
///
/// <b>Design choice:</b> This class uses pimpl idiom to separate the interface
/// from implementation specifics. Implementations may use different approaches
/// to handle domain names (mostly validation of the domain-names). The existing
/// @c isc::dns::Name class is a natural (and the simplest) choice to handle
/// domain-names. Use of this class however, implies that libdhcp must be linked
/// with libdns. At some point these libraries may need to be separated, i.e. to
/// support compilation and use of standalone DHCP server. This will require
/// that the part of implementation which deals with domain-names is modified to
/// not use classes from libdns. These changes will be transparent for this
/// interface.
class Option6ClientFqdn : public Option {
public:

    /// @brief Enumeration holding different flags used in the Client
    /// FQDN %Option.
    enum Flag {
        FLAG_S = 0x01,
        FLAG_O = 0x02,
        FLAG_N = 0x04
    };

    /// @brief Type of the domain-name: partial or full.
    enum DomainNameType {
        PARTIAL,
        FULL
    };

    /// @brief Mask which zeroes MBZ flag bits.
    static const uint8_t FLAG_MASK = 0x7;

    /// @brief The length of the flag field within DHCPv6 Client Fqdn %Option.
    static const uint16_t FLAG_FIELD_LEN = 1;

    /// @brief Constructor, creates option instance using flags and domain name.
    ///
    /// This constructor is used to create instance of the option which will be
    /// included in outgoing messages.
    ///
    /// @param flag a combination of flags to be stored in flags field.
    /// @param domain_name a name to be stored in the domain-name field.
    /// @param partial_domain_name indicates if the domain name is partial
    /// (if true) or full (false).
    explicit Option6ClientFqdn(const uint8_t flag,
                               const std::string& domain_name,
                               const DomainNameType domain_name_type = FULL);

    /// @brief Constructor, creates option instance using flags.
    ///
    /// This constructor creates an instance of the option with empty
    /// domain-name. This domain-name is marked partial.
    ///
    /// @param flag a combination of flags to be stored in flags field.
    Option6ClientFqdn(const uint8_t flag);

    /// @brief Constructor, creates an option instance from part of the buffer.
    ///
    /// This constructor is mainly used to parse options in the received
    /// messages. Function parameters specify buffer bounds from which the
    /// option should be created. The size of the buffer chunk, specified by
    /// the constructor's parameters should be equal or larger than the size
    /// of the option. Otherwise, constructor will throw an exception.
    ///
    /// @param first the lower bound of the buffer to create option from.
    /// @param last the upper bound of the buffer to create option from.
    explicit Option6ClientFqdn(OptionBufferConstIter first,
                               OptionBufferConstIter last);

   /// @brief Copy constructor
    Option6ClientFqdn(const Option6ClientFqdn& source);

    /// @brief Destructor
    virtual ~Option6ClientFqdn();

    /// @brief Assignment operator
    Option6ClientFqdn& operator=(const Option6ClientFqdn& source);

    /// @brief Checks if the specified flag of the DHCPv6 Client FQDN %Option
    /// is set.
    ///
    /// @param flag an enum value specifying the flag to be checked.
    ///
    /// @return true if the bit of the specified flag is set, false otherwise.
    bool getFlag(const Flag flag) const;

    /// @brief Modifies the value of the specified DHCPv6 Client Fqdn %Option
    /// flag.
    ///
    /// @param flag an enum value specifying the flag to be modified.
    /// @param set a boolean value which indicates whether flag should be
    /// set (true), or cleared (false).
    void setFlag(const Flag flag, const bool set);

    /// @brief Sets the flag field value to 0.
    void resetFlags();

    /// @brief Returns the domain-name in the text format.
    ///
    /// If domain-name is partial, it lacks the dot at the end (e.g. myhost).
    /// If domain-name is fully qualified, it has the dot at the end (e.g.
    /// myhost.example.com.).
    ///
    /// @return domain-name in the text format.
    std::string getDomainName() const;

    /// @brief Set new domain-name.
    ///
    /// @param domain_name domain name field value in the text format.
    /// @param domain_name_type type of the domain name: partial or fully
    /// qualified.
    void setDomainName(const std::string& domain_name,
                       const DomainNameType domain_name_type);

    /// @brief Set empty domain-name.
    ///
    /// This function is equivalent to @c Option6ClientFqdn::setDomainName
    /// with empty partial domain-name. It is exception safe.
    void resetDomainName();

    /// @brief Returns enumerator value which indicates whether domain-name is
    /// partial or full.
    ///
    /// @return An enumerator value indicating whether domain-name is partial
    /// or full.
    DomainNameType getDomainNameType() const;

   /// @brief Writes option in the wire format into a buffer.
    ///
    /// @param [out] buf output buffer where option data will be stored.
    virtual void pack(isc::util::OutputBuffer& buf);

    /// @brief Parses option from the received buffer.
    ///
    /// Method creates an instance of the DHCPv6 Client FQDN %Option from the
    /// wire format. Parameters specify the bounds of the buffer to read option
    /// data from. The size of the buffer limited by the specified parameters
    /// should be equal or larger than size of the option (including its
    /// header). Otherwise exception will be thrown.
    ///
    /// @param first lower bound of the buffer to parse option from.
    /// @param last upper bound of the buffer to parse option from.
    virtual void unpack(OptionBufferConstIter first,
                        OptionBufferConstIter last);

    /// @brief Returns string representation of the option.
    ///
    /// The string returned by the method comprises the bit value of each
    /// option flag and the domain-name.
    ///
    /// @param indent number of spaces before printed text.
    ///
    /// @return string with text representation.
    virtual std::string toText(int indent = 0);

    /// @brief Returns length of the complete option (data length +
    /// DHCPv6 option header).
    ///
    /// @return length of the option.
    virtual uint16_t len();

private:

    /// @brief A pointer to the implementation.
    Option6ClientFqdnImpl* impl_;
};

/// A pointer to the @c Option6ClientFqdn object.
typedef boost::shared_ptr<Option6ClientFqdn> Option6ClientFqdnPtr;

} // namespace isc::dhcp
} // namespace isc

#endif // OPTION6_CLIENT_FQDN_H
