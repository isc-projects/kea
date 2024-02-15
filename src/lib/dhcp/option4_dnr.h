// Copyright (C) 2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef OPTION4_DNR_H
#define OPTION4_DNR_H

#include <asiolink/io_address.h>
#include <dhcp/dhcp4.h>
#include <dhcp/dhcp6.h>
#include <dhcp/option.h>
#include <dhcp/option_data_types.h>
#include <dns/name.h>
#include <util/encode/utf8.h>
#include <util/strutil.h>

#include <map>
#include <set>
#include <string>
#include <unordered_set>

namespace isc {
namespace dhcp {


/// @brief Service parameters, used in DNR options in DHCPv4 and DHCPv6, but also in RA and DNS
///
/// The IANA registry is maintained at https://www.iana.org/assignments/dns-svcb/dns-svcb.xhtml
const std::map<std::string, uint16_t> SVC_PARAMS =
{
    { "mandatory", 0},       // RFC 9460, Section 14.3.2, not used in DNR
    { "alpn", 1 },           // RFC 9460, Section 14.3.2, mandatory in DNR
    { "no-default-alpn", 2}, // RFC 9460, Section 14.3.2, not used in DNR
    { "port", 3},            // RFC 9460, Section 14.3.2, optional in DNR
    { "ipv4hint", 4},        // RFC 9460, Section 14.3.2, forbidden in DNR
    { "ech", 5},             // RFC 9460, Section 14.3.2, not used in DNR
    { "ipv6hint", 6},        // RFC 9460, Section 14.3.2, forbidden in DNR
    { "dohpath", 7},         // RFC 9461, optional in DNR
    { "ohttp", 8}            // https://datatracker.ietf.org/doc/draft-ietf-ohai-svcb-config,
                             // not used in DNR
};

/// @brief Possible ALPN protocol IDs.
///
/// The IANA registry is maintained at
/// https://www.iana.org/assignments/tls-extensiontype-values/tls-extensiontype-values.xhtml#alpn-protocol-ids
static const std::unordered_set<std::string> ALPN_IDS = {
    "http/0.9",            // HTTP/0.9
    "http/1.0",            // HTTP/1.0
    "http/1.1",            // HTTP/1.1
    "spdy/1",              // SPDY/1
    "spdy/2",              // SPDY/2
    "spdy/3",              // SPDY/3
    "stun.turn",           // Traversal Using Relays around NAT (TURN)
    "stun.nat-discovery",  // NAT discovery using Session Traversal Utilities for NAT (STUN)
    "h2",                  // HTTP/2 over TLS
    "h2c",                 // HTTP/2 over TCP
    "webrtc",              // WebRTC Media and Data
    "c-webrtc",            // Confidential WebRTC Media and Data
    "ftp",                 // FTP
    "imap",                // IMAP
    "pop3",                // POP3
    "managesieve",         // ManageSieve
    "coap",                // CoAP
    "xmpp-client",         // XMPP jabber:client namespace
    "xmpp-server",         // XMPP jabber:server namespace
    "acme-tls/1",          // acme-tls/1
    "mqtt",                // OASIS Message Queuing Telemetry Transport (MQTT)
    "dot",                 // DNS-over-TLS
    "ntske/1",             // Network Time Security Key Establishment, version 1
    "sunrpc",              // SunRPC
    "h3",                  // HTTP/3
    "smb",                 // SMB2
    "irc",                 // IRC
    "nntp",                // NNTP (reading)
    "nnsp",                // NNTP (transit)
    "doq",                 // DoQ
    "sip/2",               // SIP
    "tds/8.0",             // TDS/8.0
    "dicom"                // DICOM
};

/// @brief Exception thrown when invalid domain name is specified.
class InvalidOptionDnrDomainName : public Exception {
public:
    InvalidOptionDnrDomainName(const char* file, size_t line, const char* what)
        : isc::Exception(file, line, what) {
    }
};

/// @brief Exception thrown when Service parameters have wrong format.
class InvalidOptionDnrSvcParams : public Exception {
public:
    InvalidOptionDnrSvcParams(const char* file, size_t line, const char* what)
        : isc::Exception(file, line, what) {
    }
};

/// @brief Represents DNR Instance which is used both in DHCPv4
/// and DHCPv6 Encrypted DNS %Option.
///
/// DNR Instance includes the configuration data of an encrypted DNS resolver.
/// It is used to build OPTION_V4_DNR (code 162). There may be multiple DNR Instances
/// in one OPTION_V4_DNR %Option. OPTION_V6_DNR (code 144) is using very similar structure,
/// only that there must be only one DNR Instance per one OPTION_V6_DNR %Option. That's why
/// @c Option6Dnr class can derive from this @c DnrInstance class, whereas @c Option4Dnr class
/// should have a container of @c DnrInstance's.
///
/// DNR Instance Data Format has been defined in the @c draft-ietf-add-dnr (to be replaced
/// with published RFC).
class DnrInstance {
public:
    /// @brief A Type defined for container holding IP addresses.
    typedef std::vector<isc::asiolink::IOAddress> AddressContainer;

    /// @brief Size in octets of Service Priority field.
    static const uint8_t SERVICE_PRIORITY_SIZE = 2;

    /// @brief Set of forbidden SvcParams.
    ///
    /// The service parameters MUST NOT include
    /// "ipv4hint" or "ipv6hint" SvcParams as they are superseded by the
    /// included IP addresses.
    static const std::unordered_set<std::string> FORBIDDEN_SVC_PARAMS;

    static const std::set<uint8_t> SUPPORTED_SVC_PARAMS;

    /// @brief Constructor of the empty DNR Instance.
    ///
    /// @param universe either V4 or V6 Option universe
    explicit DnrInstance(Option::Universe universe);

    /// @brief Constructor of the DNR Instance with all fields from params.
    ///
    /// Constructor of the DNR Instance where all fields
    /// i.e. Service priority, ADN, IP address(es) and Service params
    /// are provided as ctor parameters.
    ///
    /// @param universe either V4 or V6 Option universe
    /// @param service_priority Service priority
    /// @param adn ADN FQDN
    /// @param ip_addresses Container of IP addresses
    /// @param svc_params Service Parameters
    ///
    /// @throw InvalidOptionDnrDomainName Thrown in case of any issue with parsing ADN
    /// @throw InvalidOptionDnrSvcParams Thrown when @c checkSvcParams(from_wire_data) throws
    /// @throw OutOfRange Thrown in case of no IP addresses found or when IP addresses length
    /// is too big
    DnrInstance(Option::Universe universe,
                uint16_t service_priority,
                const std::string& adn,
                const AddressContainer& ip_addresses,
                const std::string& svc_params);

    /// @brief Constructor of the DNR Instance in ADN only mode.
    ///
    /// Constructor of the DNR Instance in ADN only mode
    /// i.e. only Service priority and ADN FQDN
    /// are provided as ctor parameters.
    ///
    /// @param universe either V4 or V6 Option universe
    /// @param service_priority Service priority
    /// @param adn ADN FQDN
    ///
    /// @throw InvalidOptionDnrDomainName Thrown in case of any issue with parsing ADN
    DnrInstance(Option::Universe universe, uint16_t service_priority, const std::string& adn);

    /// @brief Default destructor.
    virtual ~DnrInstance() = default;

    /// @brief Getter of the @c dnr_instance_data_length_.
    ///
    /// @return Length of all following data inside this DNR instance in octets.
    uint16_t getDnrInstanceDataLength() const {
        return (dnr_instance_data_length_);
    }

    /// @brief Getter of the @c service_priority_.
    ///
    /// @return The priority of this DNR instance compared to other instances.
    uint16_t getServicePriority() const {
        return (service_priority_);
    }

    /// @brief Getter of the @c adn_length_.
    ///
    /// @return Length of the authentication-domain-name data in octets.
    uint16_t getAdnLength() const {
        return (adn_length_);
    }

    /// @brief Returns the Authentication domain name in the text format.
    ///
    /// FQDN data stored in @c adn_ is converted into text format and returned.
    ///
    /// @return Authentication domain name in the text format.
    std::string getAdnAsText() const;

    /// @brief Returns string representation of the DNR instance.
    ///
    /// @return String with text representation.
    std::string getDnrInstanceAsText() const;

    /// @brief Getter of the @c addr_length_.
    ///
    /// @return  Length of enclosed IP addresses in octets.
    uint16_t getAddrLength() const {
        return (addr_length_);
    }

    /// @brief Getter of the @c svc_params_length_.
    ///
    /// @return Length of Service Parameters field in octets.
    uint16_t getSvcParamsLength() const {
        return (svc_params_length_);
    }

    /// @brief Returns vector with addresses.
    ///
    /// We return a copy of our list. Although this includes overhead,
    /// it also makes this list safe to use after this option object
    /// is no longer available. As options are expected to hold only
    /// a few (1-3) addresses, the overhead is not that big.
    ///
    /// @return Address container with addresses.
    AddressContainer getAddresses() const {
        return (ip_addresses_);
    }

    /// @brief Getter of the @c svc_params_ field.
    ///
    /// @return Returns Service Parameters as a string.
    const std::string& getSvcParams() const {
        return (svc_params_);
    }

    /// @brief Returns minimal length of the DNR instance data (without headers) in octets.
    ///
    /// @return Minimal length of the DNR instance data (without headers) in octets.
    uint8_t getMinimalLength() const {
        return (minimal_length_);
    }

    /// @brief Returns size in octets of Addr Length field.
    uint8_t getAddrLengthSize() const {
        return (addr_length_size_);
    }

    /// @brief Returns size in octets of DNR Instance Data Length field.
    uint8_t getDnrInstanceDataLengthSize() const {
        return (dnr_instance_data_length_size_);
    }

    /// @brief Returns size in octets of ADN Length field.
    uint8_t getAdnLengthSize() const {
        return (adn_length_size_);
    }

    /// @brief Returns Log prefix depending on V4/V6 Option universe.
    ///
    /// @return Log prefix as a string which can be used for prints when throwing an exception.
    std::string getLogPrefix() const {
        return (log_prefix_);
    }

    /// @brief Returns whether ADN only mode is enabled or disabled.
    bool isAdnOnlyMode() const {
        return (adn_only_mode_);
    }

    /// @brief Sets Authentication domain name from given string.
    ///
    /// Sets FQDN of the encrypted DNS resolver from given string.
    /// It may throw an exception if parsing of the FQDN fails or if
    /// provided FQDN length is bigger than uint16_t Max.
    /// It also calculates and sets value of Addr length field.
    ///
    /// @param adn string representation of ADN FQDN
    ///
    /// @throw InvalidOptionDnrDomainName Thrown in case of any issue with parsing ADN
    /// from given string.
    void setAdn(const std::string& adn);

    /// @brief Setter of the @c adn_only_mode_ field.
    ///
    /// @param adn_only_mode enabled/disabled setting
    void setAdnOnlyMode(bool adn_only_mode) {
        adn_only_mode_ = adn_only_mode;
    }

    /// @brief Writes the ADN FQDN in the wire format into a buffer.
    ///
    /// The Authentication Domain Name - fully qualified domain name of the encrypted
    /// DNS resolver data is appended at the end of the buffer.
    ///
    /// @param [out] buf buffer where ADN FQDN will be written.
    ///
    /// @throw InvalidOptionDnrDomainName Thrown when mandatory field ADN is empty.
    void packAdn(isc::util::OutputBuffer& buf) const;

    /// @brief Writes the IP address(es) in the wire format into a buffer.
    ///
    /// The IP address(es) (@c ip_addresses_) data is appended at the end
    /// of the buffer.
    ///
    /// @param [out] buf buffer where IP address(es) will be written.
    virtual void packAddresses(isc::util::OutputBuffer& buf) const;

    /// @brief Writes the Service Parameters in the wire format into a buffer.
    ///
    /// The Service Parameters (@c svc_params_) data is appended at the end
    /// of the buffer.
    ///
    /// @param [out] buf buffer where SvcParams will be written.
    void packSvcParams(isc::util::OutputBuffer& buf) const;

    /// @brief Unpacks DNR Instance Data Length from wire data buffer and stores
    /// it in @c dnr_instance_data_length_.
    ///
    /// It may throw in case of malformed data detected during parsing.
    ///
    /// @param begin beginning of the buffer from which the field will be read
    /// @param end end of the buffer from which the field will be read
    ///
    /// @throw OutOfRange Thrown in case of truncated data detected.
    void unpackDnrInstanceDataLength(OptionBufferConstIter& begin, OptionBufferConstIter end);

    /// @brief Unpacks Service Priority from wire data buffer and stores it in @c service_priority_.
    ///
    /// @param begin beginning of the buffer from which the field will be read
    void unpackServicePriority(OptionBufferConstIter& begin);

    /// @brief Unpacks the ADN from given wire data buffer and stores it in @c adn_ field.
    ///
    /// It may throw in case of malformed data detected during parsing.
    ///
    /// @param begin beginning of the buffer from which the ADN will be read
    /// @param end end of the buffer from which the ADN will be read
    ///
    /// @throw BadValue Thrown in case of any issue with unpacking opaque data of the ADN.
    /// @throw InvalidOptionDnrDomainName Thrown in case of any issue with parsing ADN
    /// from given wire data.
    void unpackAdn(OptionBufferConstIter& begin, OptionBufferConstIter end);

    /// @brief Unpacks IP address(es) from wire data and stores it/them in @c ip_addresses_.
    ///
    /// It may throw in case of malformed data detected during parsing.
    ///
    /// @param begin beginning of the buffer from which the field will be read
    /// @param end end of the buffer from which the field will be read
    ///
    /// @throw BadValue Thrown in case of any issue with unpacking opaque data of the IP addresses.
    /// @throw OutOfRange Thrown in case of malformed data detected during parsing e.g.
    /// Addr Len not divisible by 4, Addr Len is 0.
    virtual void unpackAddresses(OptionBufferConstIter& begin, OptionBufferConstIter end);

    /// @brief Unpacks Service Parameters from wire data buffer and stores it in @c svc_params_.
    ///
    /// It may throw in case of malformed data detected during parsing.
    ///
    /// @param begin beginning of the buffer from which the field will be read
    /// @param end end of the buffer from which the field will be read
    void unpackSvcParams(OptionBufferConstIter& begin, OptionBufferConstIter end);

    /// @brief Checks SvcParams field if encoded correctly and throws in case of issue found.
    ///
    /// The field should be encoded following the rules in
    /// Section 2.1 of [I-D.ietf-dnsop-svcb-https]. SvcParams are
    /// a whitespace-separated list, with each SvcParam consisting of
    /// a SvcParamKey=SvcParamValue pair or a standalone SvcParamKey.
    ///
    /// @note It is user's responsibility to provide correct configuration
    /// of @c SvcParams as described in Section 2.1 of [I-D.ietf-dnsop-svcb-https].
    /// Currently, SvcParamValue is not verified. Proper syntax of SvcParamValue
    /// is described in Appendix A of [I-D.ietf-dnsop-svcb-https].
    ///
    /// @param from_wire_data used to determine whether SvcParams data comes
    /// from unpacked wire data or from ctor param
    ///
    /// @throw InvalidOptionDnrSvcParams Thrown in case of any issue found when checking
    /// @c ServiceParams field syntax
    void checkSvcParams(bool from_wire_data = true);

    /// @brief Checks IP address(es) field if data is correct and throws in case of issue found.
    ///
    /// Fields lengths are also calculated and saved to member variables.
    ///
    /// @throw OutOfRange Thrown in case of no IP addresses found or when IP addresses length
    /// is too big
    /// @throw InvalidOptionDnrSvcParams Thrown when @c checkSvcParams(from_wire_data) throws
    void checkFields();

    /// @brief Adds IP address to @c ip_addresses_ container.
    ///
    /// @param ip_address IP address to be added
    void addIpAddress(const asiolink::IOAddress& ip_address);

protected:
    /// @brief Either V4 or V6 Option universe.
    Option::Universe universe_;

    /// @brief Authentication domain name field of variable length.
    ///
    /// Authentication domain name field of variable length holding
    /// a fully qualified domain name of the encrypted DNS resolver.
    /// This field is formatted as specified in Section 10 of RFC8415.
    boost::shared_ptr<isc::dns::Name> adn_;

    /// @brief Length of all following data inside this DNR instance in octets.
    ///
    /// This field is only used for DHCPv4 Encrypted DNS %Option.
    uint16_t dnr_instance_data_length_;

    /// @brief The priority of this instance compared to other DNR instances.
    uint16_t service_priority_;

    /// @brief Length of the authentication-domain-name data in octets.
    uint16_t adn_length_;

    /// @brief Length of included IP addresses in octets.
    uint16_t addr_length_;

    /// @brief Vector container holding one or more IP addresses.
    ///
    /// One or more IP addresses to reach the encrypted DNS resolver.
    /// In case of DHCPv4, both private and public IPv4 addresses can
    /// be included in this field.
    /// In case of DHCPv6, an address can be link-local, ULA, or GUA.
    AddressContainer ip_addresses_;

    /// @brief Length of Service Parameters field in octets.
    uint16_t svc_params_length_;

    /// @brief Flag stating whether ADN only mode is used or not.
    ///
    /// "Addr Length", "IP(v4/v6) Address(es)", and "Service Parameters (SvcParams)"
    /// fields are not present if the ADN-only mode is used.
    bool adn_only_mode_;

    /// @brief Service Parameters (SvcParams) (variable length) as string.
    ///
    /// Specifies a set of service parameters that are encoded
    /// following the rules in Section 2.1 of [I-D.ietf-dnsop-svcb-https].
    std::string svc_params_;

    /// @brief Service Parameters (SvcParams) (variable length) as on-wire data buffer.
    ///
    /// Specifies a set of service parameters that are encoded
    /// following the rules in Section 2.2 of RFC9460.
    OptionBuffer svc_params_buf_;

    /// @brief Service Parameters stored in a map.
    ///
    /// A set of service parameters that are encoded following the same rules
    /// for encoding SvcParams using the wire format specified in Section 2.2 of RFC9460.
    /// SvcParams are stored here in a map where the key is the SvcParamKey as an uint_16.
    /// (Defined values are in Section 14.3.2 of RFC9460 - listed in @c SVC_PARAMS).
    /// The value is an OpaqueDataTuple containing:
    /// - the length of the SvcParamValue as an uint_16 integer in network byte order
    /// - data buffer the SvcParamValue in a format determined by the SvcParamKey.
    std::map<uint16_t, OpaqueDataTuple> svc_params_map_;

    /// @brief Calculates and returns length of DNR Instance data in octets.
    /// @return length of DNR Instance data in octets.
    uint16_t dnrInstanceLen() const;

    /// @brief Indicates whether the "alpn" SvcParam contains support for HTTP.
    /// Defaults to false.
    bool alpn_http_;

private:
    /// @brief Size in octets of DNR Instance Data Length field.
    ///
    /// @note This field is used only in case of V4 DNR option.
    uint8_t dnr_instance_data_length_size_;

    /// @brief Size in octets of ADN Length field.
    uint8_t adn_length_size_;

    /// @brief Size in octets of Addr Length field.
    uint8_t addr_length_size_;

    /// @brief Minimal length of the DNR instance data (without headers) in octets.
    ///
    /// @note If the ADN-only mode is used, then "Addr Length", "ip(v4/v6)-address(es)",
    /// and "Service Parameters (SvcParams)" fields are not present.
    /// So minimal length of data is calculated by adding 2 octets for Service Priority,
    /// octets needed for ADN Length and octets needed for DNR Instance Data Length
    /// (only in case of DHCPv4).
    uint8_t minimal_length_;

    /// @brief Log prefix as a string which can be used for prints when throwing an exception.
    std::string log_prefix_;

    /// @brief Initializes private member variables basing on option's V4/V6 Universe.
    ///
    /// @note It must be called in all types of constructors of class @c DnrInstance .
    void initMembers();
};

/// @brief Represents DHCPv4 Encrypted DNS %Option (code 162).
///
/// This option has been defined in the @c draft-ietf-add-dnr (to be replaced
/// with published RFC) and it has a following structure:
/// - option-code = 162 (1 octet)
/// - option-len (1 octet)
/// - multiple (one or more) DNR Instance Data
///
/// DNR Instance Data structure:
/// - DNR Instance Data Length (2 octets)
/// - Service Priority (2 octets)
/// - ADN Length (1 octet)
/// - Authentication Domain Name (variable length)
/// - Addr Length (1 octet)
/// - IPv4 Address(es) (variable length)
/// - Service Parameters (variable length).
class Option4Dnr : public Option {
public:
    /// @brief A Type defined for container holding DNR Instances.
    typedef std::vector<DnrInstance> DnrInstanceContainer;

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
    /// @throw OutOfRange Thrown in case of truncated data. May be also thrown when
    /// @c DnrInstance::unpackDnrInstanceDataLength(begin,end) throws.
    /// @throw BadValue Thrown when @c DnrInstance::unpackAdn(begin,end) throws.
    /// @throw InvalidOptionDnrDomainName Thrown when @c DnrInstance::unpackAdn(begin,end) throws.
    Option4Dnr(OptionBufferConstIter begin,
               OptionBufferConstIter end,
               bool convenient_notation = false);

    /// @brief Constructor of the empty %Option.
    ///
    /// No DNR instances are included in the %Option when using this ctor.
    /// They must be added afterwards.
    /// No fields data included in the %Option when using this ctor.
    /// They must be added afterwards.
    Option4Dnr() : Option(V4, DHO_V4_DNR) {}

    /// @brief Adds given DNR instance to Option's DNR Instance container.
    /// @param dnr_instance DNR instance to be added
    void addDnrInstance(DnrInstance& dnr_instance);

    /// @brief Getter of the @c dnr_instances_ field.
    /// @return Reference to Option's DNR Instance container
    const DnrInstanceContainer& getDnrInstances() const {
        return (dnr_instances_);
    }

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
    /// @throw OutOfRange Thrown when @c check param set to @c true and
    /// @c Option::packHeader(buf,check) throws.
    void pack(util::OutputBuffer& buf, bool check = true) const override;

    /// @brief Parses received wire data buffer.
    ///
    /// @param begin iterator to first byte of option data
    /// @param end iterator to end of option data (first byte after option end)
    ///
    /// @throw OutOfRange Thrown in case of truncated data. May be also thrown when
    /// @c DnrInstance::unpackDnrInstanceDataLength(begin,end) throws.
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

protected:
    /// @brief Container holding DNR Instances.
    DnrInstanceContainer dnr_instances_;

private:
    /// @brief Flag stating whether the %Option was constructed with a convenient notation string,
    /// that needs custom parsing, or binary data.
    bool convenient_notation_;

    /// @brief Parses a convenient notation of the option data, which may be used in config.
    ///
    /// As an alternative to the binary format,
    /// we provide convenience option definition as a string in format:
    /// TBD
    ///
    /// @param config_txt convenient notation of the option data received as string
    ///
    /// @throw BadValue Thrown in case parser found wrong format of received string.
    void parseConfigData(const std::string& config_txt);
};

/// A pointer to the @c OptionDnr4 object.
typedef boost::shared_ptr<Option4Dnr> Option4DnrPtr;

}  // namespace dhcp
}  // namespace isc

#endif  // OPTION4_DNR_H
