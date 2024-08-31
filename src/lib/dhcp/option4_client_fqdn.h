// Copyright (C) 2013-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef OPTION4_CLIENT_FQDN_H
#define OPTION4_CLIENT_FQDN_H

#include <dhcp/option.h>
#include <dns/name.h>

#include <string>
#include <utility>

namespace isc {
namespace dhcp {

/// @brief Exception thrown when invalid flags have been specified for
/// DHCPv4 Client FQDN %Option.
class InvalidOption4FqdnFlags : public Exception {
public:
    InvalidOption4FqdnFlags(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) {}
};

/// @brief Exception thrown when invalid domain name is specified.
class InvalidOption4FqdnDomainName : public Exception {
public:
    InvalidOption4FqdnDomainName(const char* file, size_t line,
                                 const char* what) :
        isc::Exception(file, line, what) {}
};

/// Forward declaration to implementation of @c Option4ClientFqdn class.
class Option4ClientFqdnImpl;

/// @brief Represents DHCPv4 Client FQDN %Option (code 81).
///
/// This option has been defined in the RFC 4702 and it has a following
/// structure:
/// - Code (1 octet) - option code (always equal to 81).
/// - Len (1 octet) - a length of the option.
/// - Flags (1 octet) - a field carrying "NEOS" flags described below.
/// - RCODE1 (1 octet) - deprecated field which should be set to 0 by the client
/// and set to 255 by the server.
/// - RCODE2 (1 octet) - deprecated, should be used in the same way as RCODE1.
/// - Domain Name - variable length field comprising partial or fully qualified
/// domain name.
///
/// The flags field has the following structure:
/// @code
///        0 1 2 3 4 5 6 7
///       +-+-+-+-+-+-+-+-+
///       |  MBZ  |N|E|O|S|
///       +-+-+-+-+-+-+-+-+
/// @endcode
/// where:
/// - N flag specifies whether server should (0) or should not (1) perform DNS
///  Update,
/// - E flag specifies encoding of the Domain Name field. If this flag is set
/// to 1 it indicates canonical wire format without compression. 0 indicates
/// the deprecated ASCII format.
/// - O flag is set by the server to indicate that it has overridden client's
/// preference set with the S bit.
/// - S flag specifies whether server should (1) or should not (0) perform
/// forward (FQDN-to-address) updates.
///
/// This class exposes a set of functions to modify flags and check their
/// correctness.
///
/// Domain names being carried by DHCPv4 Client Fqdn %Option can be fully
/// qualified or partial. Partial domain names are encoded similar to the
/// fully qualified domain names, except that they lack terminating zero
/// at the end of their wire representation (or lack of dot at the end, in
/// case of ASCII encoding). It is also accepted to create an instance of
/// this option which has empty domain-name. Clients use empty domain-names
/// to indicate that server should generate complete fully qualified
/// domain-name.
///
/// Since domain names are case insensitive (see RFC 4343), this class
/// converts them to lower case format regardless if they are received over
/// the wire or created from strings.
///
/// @warning: The RFC4702 section 2.3.1 states that the clients and servers
/// should use character sets specified in RFC952, section 2.1 for ASCII-encoded
/// domain-names. This class doesn't detect the character set violation for
/// ASCII-encoded domain-name. It could be implemented in the future but it is
/// not important now for two reasons:
/// - ASCII encoding is deprecated
/// - clients SHOULD obey restrictions but if they don't, server may still
///   process the option
///
/// RFC 4702 mandates that the DHCP client sets RCODE1 and RCODE2 to 0 and that
/// server sets them to 255. This class allows to set the value for these
/// fields and both fields are always set to the same value. There is no way
/// to set them separately (e.g. set different value for RCODE1 and RCODE2).
/// However, there are no use cases which would require it.
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
class Option4ClientFqdn : public Option {
public:

    ///
    /// @name A set of constants used to identify and set bits in the flags field
    //@{
    static const uint8_t FLAG_S = 0x01; ///< Bit S
    static const uint8_t FLAG_O = 0x02; ///< Bit O
    static const uint8_t FLAG_E = 0x04; ///< Bit E
    static const uint8_t FLAG_N = 0x08; ///< Bit N
    //@}

    /// @brief Mask which zeroes MBZ flag bits.
    static const uint8_t FLAG_MASK = 0xF;

    /// @brief Represents the value of one of the RCODE1 or RCODE2 fields.
    ///
    /// Typically, RCODE values are set to 255 by the server and to 0 by the
    /// clients (as per RFC 4702).
    class Rcode {
    public:
        Rcode(const uint8_t rcode)
            : rcode_(rcode) { }

        /// @brief Returns the value of the RCODE.
        ///
        /// Returned value can be directly used to create the on-wire format
        /// of the DHCPv4 Client FQDN %Option.
        uint8_t getCode() const {
            return (rcode_);
        }

    private:
        uint8_t rcode_;
    };


    /// @brief Type of the domain-name: partial or full.
    enum DomainNameType {
        PARTIAL,
        FULL
    };

    /// @brief The size in bytes of the fixed fields within DHCPv4 Client Fqdn
    /// %Option.
    ///
    /// The fixed fields are:
    /// - Flags
    /// - RCODE1
    /// - RCODE2
    static const uint16_t FIXED_FIELDS_LEN = 3;

    /// @brief Constructor, creates option instance using flags and domain name.
    ///
    /// This constructor is used to create an instance of the option which will
    /// be included in outgoing messages.
    ///
    /// Note that the RCODE values are encapsulated by the Rcode object (not a
    /// simple uint8_t value). This helps to prevent a caller from confusing the
    /// flags value with rcode value (both are uint8_t values). For example:
    /// if caller swaps the two, it will be detected in the compilation time.
    /// Also, this API encourages the caller to use two predefined functions:
    /// @c RCODE_SERVER and @c RCODE_CLIENT to set the value of RCODE. These
    /// functions generate objects which represent the only valid values to be
    /// be passed to the constructor (255 and 0 respectively). Other
    /// values should not be used. However, it is still possible that the other
    /// entity (client or server) sends the option with invalid value. Although,
    /// the RCODE values are ignored, there should be a way to represent such
    /// invalid RCODE value. The Rcode class is capable of representing it.
    ///
    /// @param flags a combination of flags to be stored in flags field.
    /// @param rcode @c Rcode object representing a value for RCODE1 and RCODE2
    /// fields of the option. Both fields are assigned the same value
    /// encapsulated by the parameter.
    /// @param domain_name a name to be stored in the domain-name field.
    /// @param domain_name_type indicates if the domain name is partial
    /// or full.
    /// @throw InvalidOption4FqdnFlags if value of the flags field is wrong.
    /// @throw InvalidOption4FqdnDomainName if the domain-name is invalid.
    explicit Option4ClientFqdn(const uint8_t flags,
                               const Rcode& rcode,
                               const std::string& domain_name,
                               const DomainNameType domain_name_type = FULL);

    /// @brief Constructor, creates option instance with empty domain name.
    ///
    /// This constructor creates an instance of the option with empty
    /// domain-name. This domain-name is marked partial.
    ///
    /// @param flags a combination of flags to be stored in flags field.
    /// @param rcode @c Rcode object representing a value for RCODE1 and RCODE2
    /// fields. Both fields are assigned the same value encapsulated by this
    /// parameter.
    /// @throw InvalidOption4FqdnFlags if value of the flags field is invalid.
    Option4ClientFqdn(const uint8_t flags, const Rcode& rcode);

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
    /// @throw InvalidOption4FqdnFlags if value of the flags field is invalid.
    /// @throw InvalidOption4FqdnDomainName if the domain-name carried by the
    /// option is invalid.
    /// @throw OutOfRange if the option is truncated.
    explicit Option4ClientFqdn(OptionBufferConstIter first,
                               OptionBufferConstIter last);

    /// @brief Copy constructor
    Option4ClientFqdn(const Option4ClientFqdn& source);

    /// @brief Copies this option and returns a pointer to the copy.
    virtual OptionPtr clone() const;

    /// @brief Destructor
    virtual ~Option4ClientFqdn();

    /// @brief Assignment operator
    Option4ClientFqdn& operator=(const Option4ClientFqdn& source);

    /// @brief Checks if the specified flag of the DHCPv4 Client FQDN %Option
    /// is set.
    ///
    /// @param flag A value specifying a bit within flags field to be checked.
    /// It must be one of the following @c FLAG_S, @c FLAG_E, @c FLAG_O,
    /// @c FLAG_N.
    ///
    /// @return true if the bit of the specified flags bit is set, false
    /// otherwise.
    /// @throw InvalidOption4ClientFlags if specified flag which value is to be
    /// returned is invalid (is not one of the FLAG_S, FLAG_N, FLAG_O).
    bool getFlag(const uint8_t flag) const;

    /// @brief Modifies the value of the specified DHCPv4 Client Fqdn %Option
    /// flag.
    ///
    /// @param flag A value specifying a bit within flags field to be set. It
    /// must be one of the following @c FLAG_S, @c FLAG_E, @c FLAG_O, @c FLAG_N.
    /// @param set a boolean value which indicates whether flag should be
    /// set (true), or cleared (false).
    /// @throw InvalidOption4ClientFlags if specified flag which value is to be
    /// set is invalid (is not one of the FLAG_S, FLAG_N, FLAG_O).
    void setFlag(const uint8_t flag, const bool set);

    /// @brief Sets the flag field value to 0.
    void resetFlags();

    /// @brief Returns @c Rcode objects representing value of RCODE1 and RCODE2.
    ///
    /// @return Pair of Rcode objects of which first is the RCODE1 and the
    /// second is RCODE2.
    std::pair<Rcode, Rcode> getRcode() const;

    /// @brief Set Rcode value.
    ///
    /// @param rcode An @c Rcode object representing value of RCODE1 and RCODE2.
    /// Both fields are assigned the same value.
    void setRcode(const Rcode& rcode);

    /// @brief Returns the domain-name in the text format.
    ///
    /// If domain-name is partial, it lacks the dot at the end (e.g. myhost).
    /// If domain-name is fully qualified, it has the dot at the end (e.g.
    /// myhost.example.com.).
    ///
    /// @return domain-name in the text format.
    std::string getDomainName() const;

    /// @brief Writes domain-name in the wire format into a buffer.
    ///
    /// The data being written are appended at the end of the buffer.
    ///
    /// @param [out] buf buffer where domain-name will be written.
    void packDomainName(isc::util::OutputBuffer& buf) const;

    /// @brief Set new domain-name.
    ///
    /// @param domain_name domain name field value in the text format.
    /// @param domain_name_type type of the domain name: partial or fully
    /// qualified.
    /// @throw InvalidOption4FqdnDomainName if the specified domain-name is
    /// invalid.
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
    /// @param check if set to false, allows options larger than 255 for v4
    virtual void pack(isc::util::OutputBuffer& buf, bool check = true) const;

    /// @brief Parses option from the received buffer.
    ///
    /// Method creates an instance of the DHCPv4 Client FQDN %Option from the
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
    virtual std::string toText(int indent = 0) const;

    /// @brief Returns length of the complete option (data length +
    /// DHCPv4 option header).
    ///
    /// @return length of the option.
    virtual uint16_t len() const;

    ///
    /// @name Well known Rcode declarations for DHCPv4 Client FQDN %Option
    ///
    //@{
    /// @brief Rcode being set by the server.
    inline static const Rcode& RCODE_SERVER() {
        static Rcode rcode(255);
        return (rcode);
    }

    /// @brief Rcode being set by the client.
    inline static const Rcode& RCODE_CLIENT() {
        static Rcode rcode(0);
        return (rcode);
    }
    //@}

private:

    /// @brief A pointer to the implementation.
    Option4ClientFqdnImpl* impl_;
};

/// A pointer to the @c Option4ClientFqdn object.
typedef boost::shared_ptr<Option4ClientFqdn> Option4ClientFqdnPtr;

} // namespace isc::dhcp
} // namespace isc

#endif // OPTION4_CLIENT_FQDN_H
