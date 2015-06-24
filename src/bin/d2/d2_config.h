// Copyright (C) 2013-2015 Internet Systems Consortium, Inc. ("ISC")
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

#ifndef D2_CONFIG_H
#define D2_CONFIG_H

#include <asiolink/io_service.h>
#include <cc/data.h>
#include <d2/d_cfg_mgr.h>
#include <dhcpsrv/parsers/dhcp_parsers.h>
#include <dns/tsig.h>
#include <exceptions/exceptions.h>

#include <boost/foreach.hpp>

#include <stdint.h>
#include <string>

namespace isc {
namespace d2 {

/// @file d2_config.h
/// @brief A collection of classes for housing and parsing the application
/// configuration necessary for the DHCP-DDNS application (aka D2).
///
/// This file contains the class declarations for the class hierarchy created
/// from the D2 configuration and the parser classes used to create it.
/// The application configuration consists of a set of scalar parameters,
/// a list of TSIG keys, and two managed lists of domains: one list for
/// forward domains and one list for reverse domains.
///
/// The key list consists of one or more TSIG keys, each entry described by
/// a name, the algorithm method name, optionally the minimum truncated
/// length, and its secret key component.
///
/// @todo  NOTE that TSIG configuration parsing is functional, the use of
/// TSIG Keys during the actual DNS update transactions is not.  This will be
/// implemented in a future release.
///
/// Each managed domain list consists of a list one or more domains and is
/// represented by the class DdnsDomainListMgr.
///
/// Each domain consists of a set of scalars parameters and a list of DNS
/// servers which support that domain. Among its scalars, is key_name, which
/// is the name of the TSIG Key to use for with this domain.  This value should
/// map to one of the TSIG Keys in the key list.  Domains are represented by
/// the class, DdnsDomain.
///
/// Each server consists of a set of scalars used to describe the server such
/// that the application can carry out DNS update exchanges with it. Servers
/// are represented by the class, DnsServerInfo.
///
/// The configuration specification for use with Kea is detailed in the file
/// dhcp-ddns.spec.
///
/// The parsing class hierarchy reflects this same scheme.  Working top down:
///
/// A DdnsDomainListMgrParser parses a managed domain list entry. It handles
/// any scalars which belong to the manager as well as creating and invoking a
/// DdnsDomainListParser to parse its list of domain entries.
///
/// A DdnsDomainListParser creates and invokes a DdnsDomainParser for each
/// domain entry in its list.
///
/// A DdnsDomainParser handles the scalars which belong to the domain as well as
/// creating and invoking a DnsSeverInfoListParser to parse its list of server
/// entries.
///
/// A DnsServerInfoListParser creates and invokes a DnsServerInfoParser for
/// each server entry in its list.
///
/// A DdnsServerInfoParser handles the scalars which belong to the server.
/// The following is sample configuration in JSON form with extra spacing
/// for clarity:
///
/// @code
/// {
///  "interface" : "eth1" ,
///  "ip_address" : "192.168.1.33" ,
///  "port" : 88 ,
///  "tsig_keys":
//// [
///    {
///     "name": "d2_key.tmark.org" ,
///     "algorithm": "md5" ,
///     "secret": "0123456989"
///    }
///  ],
///  "forward_ddns" :
///  {
///    "ddns_domains":
///    [
///      {
///        "name": "tmark.org." ,
///        "key_name": "d2_key.tmark.org" ,
///        "dns_servers" :
///        [
///          { "hostname": "fserver.tmark.org" },
///          { "hostname": "f2server.tmark.org" }
///        ]
///      },
///      {
///        "name": "pub.tmark.org." ,
///        "key_name": "d2_key.tmark.org" ,
///        "dns_servers" :
///        [
///          { "hostname": "f3server.tmark.org" }
///        ]
///      }
///    ]
///  },
///  "reverse_ddns" :
///  {
///    "ddns_domains":
///    [
///      {
///        "name": " 0.168.192.in.addr.arpa." ,
///        "key_name": "d2_key.tmark.org" ,
///        "dns_servers" :
///        [
///          { "ip_address": "127.0.0.101" , "port": 100 }
///        ]
///      }
///    ]
///  }
/// }
/// @endcode

/// @brief Exception thrown when the error during configuration handling
/// occurs.
class D2CfgError : public isc::Exception {
public:
    D2CfgError(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) { };
};

/// @brief Acts as a storage vault for D2 global scalar parameters
class D2Params {
public:
    /// @brief Default configuration constants.
    //@{
    /// @todo For now these are hard-coded as configuration layer cannot
    /// readily provide them (see Trac #3358).
    static const char *DFT_IP_ADDRESS;
    static const size_t DFT_PORT;
    static const size_t DFT_DNS_SERVER_TIMEOUT;
    static const char *DFT_NCR_PROTOCOL;
    static const char *DFT_NCR_FORMAT;
    //@}

    /// @brief Constructor
    ///
    /// @param ip_address IP address at which D2 should listen for NCRs
    /// @param port port on which D2 should listen NCRs
    /// @param dns_server_timeout  maximum amount of time in milliseconds to
    /// wait for a response to a single DNS update request.
    /// @param ncr_protocol socket protocol D2 should use to receive NCRS
    /// @param ncr_format packet format of the inbound NCRs
    ///
    /// @throw D2CfgError if:
    /// -# ip_address is 0.0.0.0 or ::
    /// -# port is 0
    /// -# dns_server_timeout is < 1
    /// -# ncr_protocol is invalid, currently only NCR_UDP is supported
    /// -# ncr_format is invalid, currently only FMT_JSON is supported
    D2Params(const isc::asiolink::IOAddress& ip_address,
                   const size_t port,
                   const size_t dns_server_timeout,
                   const dhcp_ddns::NameChangeProtocol& ncr_protocol,
                   const dhcp_ddns::NameChangeFormat& ncr_format);

    /// @brief Default constructor
    /// The default constructor creates an instance that has updates disabled.
    D2Params();

    /// @brief Destructor
    virtual ~D2Params();

    /// @brief Return the IP address D2 listens on.
    const isc::asiolink::IOAddress& getIpAddress() const {
        return(ip_address_);
    }

    /// @brief Return the TCP/UPD port D2 listens on.
    size_t getPort() const {
        return(port_);
    }

    /// @brief Return the DNS server timeout value.
    size_t getDnsServerTimeout() const {
        return(dns_server_timeout_);
    }

    /// @brief Return the socket protocol in use.
    const dhcp_ddns::NameChangeProtocol& getNcrProtocol() const {
         return(ncr_protocol_);
    }

    /// @brief Return the expected format of inbound requests (NCRs).
    const dhcp_ddns::NameChangeFormat& getNcrFormat() const {
        return(ncr_format_);
    }

    /// @brief Return summary of the configuration used by D2.
    ///
    /// The returned summary of the configuration is meant to be appended to
    /// the log message informing about the successful completion of the
    /// D2 configuration.
    ///
    /// @return Configuration summary in the textual format.
    std::string getConfigSummary() const;

    /// @brief Compares two D2Paramss for equality
    bool operator == (const D2Params& other) const;

    /// @brief Compares two D2Paramss for inequality
    bool operator != (const D2Params& other) const;

    /// @brief Generates a string representation of the class contents.
    std::string toText() const;

protected:
    /// @brief Validates member values.
    ///
    /// Method is used by the constructor to validate member contents.
    /// Currently checks:
    /// -# ip_address is not 0.0.0.0 or ::
    /// -# port is not 0
    /// -# dns_server_timeout is 0
    /// -# ncr_protocol is UDP
    /// -# ncr_format is JSON
    ///
    /// @throw D2CfgError if contents are invalid
    virtual void validateContents();

private:
    /// @brief IP address D2 listens on.
    isc::asiolink::IOAddress ip_address_;

    /// @brief IP port D2 listens on.
    size_t port_;

    /// @brief Timeout for a single DNS packet exchange in milliseconds.
    size_t dns_server_timeout_;

    /// @brief The socket protocol to use.
    /// Currently only UDP is supported.
    dhcp_ddns::NameChangeProtocol ncr_protocol_;

    /// @brief Format of the inbound requests (NCRs).
    /// Currently only JSON format is supported.
    dhcp_ddns::NameChangeFormat ncr_format_;
};

/// @brief Dumps the contents of a D2Params as text to an output stream
///
/// @param os output stream to which text should be sent
/// @param config D2Param instnace to dump
std::ostream&
operator<<(std::ostream& os, const D2Params& config);

/// @brief Defines a pointer for D2Params instances.
typedef boost::shared_ptr<D2Params> D2ParamsPtr;

/// @brief Represents a TSIG Key.
///
/// Acts as both a storage class containing the basic attributes which
/// describe a TSIG Key, as well as owning and providing access to an
/// instance of the actual key (@ref isc::dns::TSIGKey) that can be used
/// by the IO layer for signing and verifying messages.
///
class TSIGKeyInfo {
public:
    /// @brief Defines string values for the supported TSIG algorithms
    //@{
    static const char* HMAC_MD5_STR;
    static const char* HMAC_SHA1_STR;
    static const char* HMAC_SHA256_STR;
    static const char* HMAC_SHA224_STR;
    static const char* HMAC_SHA384_STR;
    static const char* HMAC_SHA512_STR;
    //}@

    /// @brief Constructor
    ///
    /// @param name the unique label used to identify this key
    /// @param algorithm the id of the encryption alogirthm this key uses.
    /// Currently supported values are (case insensitive):
    /// -# "HMAC-MD5"
    /// -# "HMAC-SHA1"
    /// -# "HMAC-SHA224"
    /// -# "HMAC-SHA256"
    /// -# "HMAC-SHA384"
    /// -# "HMAC-SHA512"
    ///
    /// @param secret  The base-64 encoded secret component for this key.
    /// (A suitable string for use here could be obtained by running the
    /// BIND 9 dnssec-keygen program; the contents of resulting key file
    /// will look similar to:
    /// @code
    ///   Private-key-format: v1.3
    ///   Algorithm: 157 (HMAC_MD5)
    ///   Key: LSWXnfkKZjdPJI5QxlpnfQ==
    ///   Bits: AAA=
    ///   Created: 20140515143700
    ///   Publish: 20140515143700
    ///   Activate: 20140515143700
    /// @endcode
    /// where the value the "Key:" entry is the secret component of the key.)
    /// @param digestbits the minimum truncated length in bits
    ///
    /// @throw D2CfgError if values supplied are invalid:
    /// name cannot be blank, algorithm must be a supported value,
    /// secret must be a non-blank, base64 encoded string.
    TSIGKeyInfo(const std::string& name, const std::string& algorithm,
                const std::string& secret, uint32_t digestbits = 0);

    /// @brief Destructor
    virtual ~TSIGKeyInfo();

    /// @brief Getter which returns the key's name.
    ///
    /// @return returns the name as a std::string.
    const std::string getName() const {
        return (name_);
    }

    /// @brief Getter which returns the key's algorithm string ID
    ///
    /// @return returns the algorithm as a std::string.
    const std::string getAlgorithm() const {
        return (algorithm_);
    }

    /// @brief Getter which returns the key's minimum truncated length
    ///
    /// @return returns the minimum truncated length or 0 as an uint32_t
    uint32_t getDigestbits() const {
        return (digestbits_);
    }

    /// @brief Getter which returns the key's secret.
    ///
    /// @return returns the secret as a std::string.
    const std::string getSecret() const {
        return (secret_);
    }

    /// @brief Getter which returns the TSIG key used to sign and verify
    /// messages
    ///
    /// @return const pointer reference to dns::TSIGKey.
    const dns::TSIGKeyPtr& getTSIGKey() const {
        return (tsig_key_);
    }

    /// @brief Converts algorithm id to dns::TSIGKey algorithm dns::Name
    ///
    /// @param algorithm_id string value to translate into an algorithm name.
    /// Currently supported values are (case insensitive):
    /// -# "HMAC-MD5"
    /// -# "HMAC-SHA1"
    /// -# "HMAC-SHA224"
    /// -# "HMAC-SHA256"
    /// -# "HMAC-SHA384"
    /// -# "HMAC-SHA512"
    ///
    /// @return const reference to a dns::Name containing the algorithm name
    /// @throw BadValue if ID isn't recognized.
    static const dns::Name& stringToAlgorithmName(const std::string&
                                                  algorithm_id);

private:
    /// @brief Creates the actual TSIG key instance member
    ///
    /// Replaces this tsig_key member with a key newly created using the key
    /// name, algorithm id, digest bits, and secret.
    /// This method is currently only called by the constructor, however it
    /// could be called post-construction should keys ever support expiration.
    ///
    /// @throw D2CfgError with an explanation if the key could not be created.
    void remakeKey();

    /// @brief The name of the key.
    ///
    /// This value is the unique identifier that domains use to
    /// to specify which TSIG key they need.
    std::string name_;

    /// @brief The string ID of the algorithm that should be used for this key.
    std::string algorithm_;

    /// @brief The base64 encoded string secret value component of this key.
    std::string secret_;

    /// @brief The minimum truncated length in bits
    /// (0 means no truncation is allowed and is the default)
    uint32_t digestbits_;

    /// @brief The actual TSIG key.
    dns::TSIGKeyPtr tsig_key_;
};

/// @brief Defines a pointer for TSIGKeyInfo instances.
typedef boost::shared_ptr<TSIGKeyInfo> TSIGKeyInfoPtr;

/// @brief Defines a map of TSIGKeyInfos, keyed by the name.
typedef std::map<std::string, TSIGKeyInfoPtr> TSIGKeyInfoMap;

/// @brief Defines a iterator pairing of name and TSIGKeyInfo
typedef std::pair<std::string, TSIGKeyInfoPtr> TSIGKeyInfoMapPair;

/// @brief Defines a pointer to map of TSIGkeyInfos
typedef boost::shared_ptr<TSIGKeyInfoMap> TSIGKeyInfoMapPtr;


/// @brief Represents a specific DNS Server.
/// It provides information about the server's network identity and typically
/// belongs to a list of servers supporting DNS for a given domain. It will
/// be used to establish communications with the server to carry out DNS
/// updates.
class DnsServerInfo {
public:

    /// @brief defines DNS standard port value
    static const uint32_t STANDARD_DNS_PORT = 53;

    /// @brief defines an "empty" string version of an ip address.
    static const char* EMPTY_IP_STR;


    /// @brief Constructor
    ///
    /// @param hostname is the resolvable name of the server. If not blank,
    /// then the server address should be resolved at runtime.
    /// @param ip_address is the static IP address of the server. If hostname
    /// is blank, then this address should be used to connect to the server.
    /// @param port is the port number on which the server listens.
    /// primarily meant for testing purposes.  Normally, DNS traffic is on
    /// is port 53. (NOTE the constructing code is responsible for setting
    /// the default.)
    /// @param enabled is a flag that indicates whether this server is
    /// enabled for use. It defaults to true.
    DnsServerInfo(const std::string& hostname,
                  isc::asiolink::IOAddress ip_address,
                  uint32_t port = STANDARD_DNS_PORT,
                  bool enabled=true);

    /// @brief Destructor
    virtual ~DnsServerInfo();

    /// @brief Getter which returns the server's hostname.
    ///
    /// @return returns the hostname as as std::string.
    const std::string getHostname() const {
        return (hostname_);
    }

    /// @brief Getter which returns the server's port number.
    ///
    /// @return returns the port number as a unsigned integer.
    uint32_t getPort() const {
        return (port_);
    }

    /// @brief Getter which returns the server's ip_address.
    ///
    /// @return returns the address as an IOAddress reference.
    const isc::asiolink::IOAddress& getIpAddress() const {
        return (ip_address_);
    }

    /// @brief Convenience method which returns whether or not the
    /// server is enabled.
    ///
    /// @return returns true if the server is enabled, false otherwise.
    bool isEnabled() const {
        return (enabled_);
    }

    /// @brief Sets the server's enabled flag to true.
    void enable() {
        enabled_ = true;
    }

    /// @brief Sets the server's enabled flag to false.
    void disable() {
        enabled_ = false;
    }

    /// @brief Returns a text representation for the server.
    std::string toText() const;


private:
    /// @brief The resolvable name of the server. If not blank, then the
    /// server's IP address should be dynamically resolved at runtime.
    std::string hostname_;

    /// @brief The static IP address of the server. When hostname is blank,
    /// then this address should be used to connect to the server.
    isc::asiolink::IOAddress ip_address_;

    /// @brief The port number on which the server listens for DNS traffic.
    uint32_t port_;

    /// @param enabled is a flag that indicates whether this server is
    /// enabled for use. It defaults to true.
    bool enabled_;
};

std::ostream&
operator<<(std::ostream& os, const DnsServerInfo& server);

/// @brief Defines a pointer for DnsServerInfo instances.
typedef boost::shared_ptr<DnsServerInfo> DnsServerInfoPtr;

/// @brief Defines a storage container for DnsServerInfo pointers.
typedef std::vector<DnsServerInfoPtr> DnsServerInfoStorage;

/// @brief Defines a pointer to DnsServerInfo storage containers.
typedef boost::shared_ptr<DnsServerInfoStorage> DnsServerInfoStoragePtr;


/// @brief Represents a DNS domain that is may be updated dynamically.
/// This class specifies a DNS domain and the list of DNS servers that support
/// it.  It's primary use is to map a domain to the DNS server(s) responsible
/// for it.
/// @todo Currently the name entry for a domain is just an std::string. It
/// may be worthwhile to change this to a dns::Name for purposes of better
/// validation and matching capabilities.
class DdnsDomain {
public:
    /// @brief Constructor
    ///
    /// @param name is the domain name of the domain.
    /// @param servers is the list of server(s) supporting this domain.
    /// @param tsig_key_info pointer to the TSIGKeyInfo for the dommain's key
    /// It defaults to an empty pointer, signifying the domain has no key.
    DdnsDomain(const std::string& name,
               DnsServerInfoStoragePtr servers,
               const TSIGKeyInfoPtr& tsig_key_info = TSIGKeyInfoPtr());

    /// @brief Destructor
    virtual ~DdnsDomain();

    /// @brief Getter which returns the domain's name.
    ///
    /// @return returns the name in an std::string.
    const std::string getName() const {
        return (name_);
    }

    /// @brief Convenience method which returns the domain's TSIG key name.
    ///
    /// @return returns the key name in an std::string. If domain has no
    /// TSIG key, the string will empty.
    const std::string getKeyName() const;

    /// @brief Getter which returns the domain's list of servers.
    ///
    /// @return returns the pointer to the server storage.
    const DnsServerInfoStoragePtr& getServers() {
        return (servers_);
    }

    /// @brief Getter which returns the domain's TSIGKey info
    ///
    /// @return returns the pointer to the server storage.  If the domain
    /// is not configured to use TSIG the pointer will be empty.
    const TSIGKeyInfoPtr& getTSIGKeyInfo() {
        return (tsig_key_info_);
    }

private:
    /// @brief The domain name of the domain.
    std::string name_;

    /// @brief The list of server(s) supporting this domain.
    DnsServerInfoStoragePtr servers_;

    /// @brief Pointer to domain's the TSIGKeyInfo.
    /// Value is empty if the domain is not configured for TSIG.
    TSIGKeyInfoPtr tsig_key_info_;
};

/// @brief Defines a pointer for DdnsDomain instances.
typedef boost::shared_ptr<DdnsDomain> DdnsDomainPtr;

/// @brief Defines a map of DdnsDomains, keyed by the domain name.
typedef std::map<std::string, DdnsDomainPtr> DdnsDomainMap;

/// @brief Defines a iterator pairing domain name and DdnsDomain
typedef std::pair<std::string, DdnsDomainPtr> DdnsDomainMapPair;

/// @brief Defines a pointer to DdnsDomain storage containers.
typedef boost::shared_ptr<DdnsDomainMap> DdnsDomainMapPtr;

/// @brief Provides storage for and management of a list of DNS domains.
/// In addition to housing the domain list storage, it provides domain matching
/// services.  These services are used to match a FQDN to a domain.  Currently
/// it supports a single matching service, which will return the matching
/// domain or a wild card domain if one is specified.  The wild card domain is
/// specified as a domain whose name is "*".  The wild card domain will match
/// any entry and is provided for flexibility in FQDNs  If for instance, all
/// forward requests are handled by the same servers, the configuration could
/// specify the wild card domain as the only forward domain. All forward DNS
/// updates would be sent to that one list of servers, regardless of the FQDN.
/// As matching capabilities evolve this class is expected to expand.
class DdnsDomainListMgr {
public:
    /// @brief defines the domain name for denoting the wildcard domain.
    static const char* wildcard_domain_name_;

    /// @brief Constructor
    ///
    /// @param name is an arbitrary label assigned to this manager.
    DdnsDomainListMgr(const std::string& name);

    /// @brief Destructor
    virtual ~DdnsDomainListMgr ();

    /// @brief Matches a given name to a domain based on a longest match
    /// scheme.
    ///
    /// Given a FQDN, search the list of domains, successively removing a
    /// sub-domain from the FQDN until a match is found.  If no match is found
    /// and the wild card domain is present in the list, then return it as the
    /// match.  If the wild card domain is the only domain in the list, then
    /// it will be returned immediately for any FQDN.
    ///
    /// @param fqdn is the name for which to look.
    /// @param domain receives the matching domain. If no match is found its
    /// contents will be unchanged.
    ///
    /// @return returns true if a match is found, false otherwise.
    /// @todo This is a very basic match method, which expects valid FQDNs
    /// both as input and for the DdnsDomain::getName().  Currently both are
    /// simple strings and there is no normalization (i.e. added trailing dots
    /// if missing).
    virtual bool matchDomain(const std::string& fqdn, DdnsDomainPtr& domain);

    /// @brief Fetches the manager's name.
    ///
    /// @return returns a std::string containing the name of the manager.
    const std::string getName() const {
        return (name_);
    }

    /// @brief Returns the number of domains in the domain list.
    ///
    /// @brief returns an unsigned int containing the domain count.
    uint32_t size() const {
        return (domains_->size());
    }

    /// @brief Fetches the wild card domain.
    ///
    /// @return returns a pointer reference to the domain.  The pointer will
    /// empty if the wild card domain is not present.
    const DdnsDomainPtr& getWildcardDomain() {
        return (wildcard_domain_);
    }

    /// @brief Fetches the domain list.
    ///
    /// @return returns a pointer reference to the list of domains.
    const DdnsDomainMapPtr &getDomains() {
        return (domains_);
    }

    /// @brief Sets the manger's domain list to the given list of domains.
    /// This method will scan the inbound list for the wild card domain and
    /// set the internal wild card domain pointer accordingly.
    void setDomains(DdnsDomainMapPtr domains);

private:
    /// @brief An arbitrary label assigned to this manager.
    std::string name_;

    /// @brief Map of the domains, keyed by name.
    DdnsDomainMapPtr domains_;

    /// @brief Pointer to the wild card domain.
    DdnsDomainPtr wildcard_domain_;
};

/// @brief Defines a pointer for DdnsDomain instances.
typedef boost::shared_ptr<DdnsDomainListMgr> DdnsDomainListMgrPtr;

/// @brief Storage container for scalar configuration parameters.
///
/// This class is useful for implementing parsers for more complex configuration
/// elements (e.g. those of item type "map").  It provides a convenient way to
/// add storage to the parser for an arbitrary number and variety of scalar
/// configuration items (e.g. ints, bools, strings...) without explicitly adding
/// storage for each individual type needed by the parser.
///
/// This class implements a concrete version of the base class by supplying a
/// "clone" method.
class DScalarContext : public DCfgContextBase {
public:

    /// @brief Constructor
    DScalarContext() {
    };

    /// @brief Destructor
    virtual ~DScalarContext() {
    }

    /// @brief Creates a clone of a DStubContext.
    ///
    /// @return returns a pointer to the new clone.
    virtual DCfgContextBasePtr clone() {
        return (DCfgContextBasePtr(new DScalarContext(*this)));
    }

protected:
    /// @brief Copy constructor
    DScalarContext(const DScalarContext& rhs) : DCfgContextBase(rhs) {
    }

private:
    /// @brief Private assignment operator, not implemented.
    DScalarContext& operator=(const DScalarContext& rhs);
};

/// @brief Defines a pointer for DScalarContext instances.
typedef boost::shared_ptr<DScalarContext> DScalarContextPtr;

/// @brief Parser for  TSIGKeyInfo
///
/// This class parses the configuration element "tsig_key" defined in
/// src/bin/d2/dhcp-ddns.spec and creates an instance of a TSIGKeyInfo.
class TSIGKeyInfoParser : public  isc::dhcp::DhcpConfigParser {
public:
    /// @brief Constructor
    ///
    /// @param entry_name is an arbitrary label assigned to this configuration
    /// definition. Since servers are specified in a list this value is likely
    /// be something akin to "key:0", set during parsing.
    /// @param keys is a pointer to the storage area to which the parser
    /// should commit the newly created TSIGKeyInfo instance.
    TSIGKeyInfoParser(const std::string& entry_name, TSIGKeyInfoMapPtr keys);

    /// @brief Destructor
    virtual ~TSIGKeyInfoParser();

    /// @brief Performs the actual parsing of the given  "tsig_key" element.
    ///
    /// Parses a configuration for the elements needed to instantiate a
    /// TSIGKeyInfo, validates those entries, creates a TSIGKeyInfo instance
    /// then attempts to add to a list of keys
    ///
    /// @param key_config is the "tsig_key" configuration to parse
    virtual void build(isc::data::ConstElementPtr key_config);

    /// @brief Creates a parser for the given "tsig_key" member element id.
    ///
    /// The key elements currently supported are(see dhcp-ddns.spec):
    ///   1. name
    ///   2. algorithm
    ///   3. digestbits
    ///   4. secret
    ///
    /// @param config_id is the "item_name" for a specific member element of
    /// the "tsig_key" specification.
    /// @param pos position within the configuration text (or file) of element
    /// to be parsed.  This is passed for error messaging.
    ///
    /// @return returns a pointer to newly created parser.
    ///
    /// @throw D2CfgError if configuration contains an unknown parameter
    virtual isc::dhcp::ParserPtr
    createConfigParser(const std::string& config_id,
                       const isc::data::Element::Position& pos =
                       isc::data::Element::ZERO_POSITION());

    /// @brief Commits the TSIGKeyInfo configuration
    /// Currently this method is a NOP, as the key instance is created and
    /// then added to a local list of keys in build().
    virtual void commit();

private:
    /// @brief Arbitrary label assigned to this parser instance.
    /// Since servers are specified in a list this value is likely be something
    /// akin to "key:0", set during parsing.  Primarily here for diagnostics.
    std::string entry_name_;

    /// @brief Pointer to the storage area to which the parser should commit
    /// the newly created TSIGKeyInfo instance. This is given to us as a
    /// constructor argument by an upper level.
    TSIGKeyInfoMapPtr keys_;

    /// @brief Local storage area for scalar parameter values. Use to hold
    /// data until time to commit.
    DScalarContext local_scalars_;
};

/// @brief Parser for a list of TSIGKeyInfos
///
/// This class parses a list of "tsig_key" configuration elements.
/// (see src/bin/d2/dhcp-ddns.spec). The TSIGKeyInfo instances are added
/// to the given storage upon commit.
class TSIGKeyInfoListParser : public isc::dhcp::DhcpConfigParser {
public:

    /// @brief Constructor
    ///
    /// @param list_name is an arbitrary label assigned to this parser instance.
    /// @param keys is a pointer to the storage area to which the parser
    /// should commit the newly created TSIGKeyInfo instance.
    TSIGKeyInfoListParser(const std::string& list_name, TSIGKeyInfoMapPtr keys);

    /// @brief Destructor
    virtual ~TSIGKeyInfoListParser();

    /// @brief Performs the parsing of the given list "tsig_key" elements.
    ///
    /// It iterates over each key entry in the list:
    ///   1. Instantiate a TSIGKeyInfoParser for the entry
    ///   2. Pass the element configuration to the parser's build method
    ///   3. Add the parser instance to local storage
    ///
    /// The net effect is to parse all of the key entries in the list
    /// prepping them for commit.
    ///
    /// @param key_list_config is the list of "tsig_key" elements to parse.
    virtual void build(isc::data::ConstElementPtr key_list_config);

    /// @brief Commits the list of TSIG keys
    ///
    /// Iterates over the internal list of TSIGKeyInfoParsers, invoking
    /// commit on each one.  Then commits the local list of keys to
    /// storage.
    virtual void commit();

private:
    /// @brief Arbitrary label assigned to this parser instance.
    std::string list_name_;

    /// @brief Pointer to the storage area to which the parser should commit
    /// the list of newly created TSIGKeyInfo instances. This is given to us
    /// as a constructor argument by an upper level.
    TSIGKeyInfoMapPtr keys_;

    /// @brief Local storage area to which individual key parsers commit.
    TSIGKeyInfoMapPtr local_keys_;

    /// @brief Local storage of TSIGKeyInfoParser instances
    isc::dhcp::ParserCollection parsers_;
};

/// @brief Parser for  DnsServerInfo
///
/// This class parses the configuration element "dns_server" defined in
/// src/bin/d2/dhcp-ddns.spec and creates an instance of a DnsServerInfo.
class DnsServerInfoParser : public  isc::dhcp::DhcpConfigParser {
public:
    /// @brief Constructor
    ///
    /// @param entry_name is an arbitrary label assigned to this configuration
    /// definition. Since servers are specified in a list this value is likely
    /// be something akin to "server:0", set during parsing.
    /// @param servers is a pointer to the storage area to which the parser
    /// should commit the newly created DnsServerInfo instance.
    DnsServerInfoParser(const std::string& entry_name,
                        DnsServerInfoStoragePtr servers);

    /// @brief Destructor
    virtual ~DnsServerInfoParser();

    /// @brief Performs the actual parsing of the given  "dns_server" element.
    ///
    /// Parses a configuration for the elements needed to instantiate a
    /// DnsServerInfo, validates those entries, creates a DnsServerInfo instance
    /// then attempts to add to a list of  servers.
    ///
    /// @param server_config is the "dns_server" configuration to parse
    ///
    /// @throw D2CfgError if:
    /// -# hostname is not blank, hostname is not yet supported
    /// -# ip_address is invalid
    /// -# port is 0
    virtual void build(isc::data::ConstElementPtr server_config);

    /// @brief Creates a parser for the given "dns_server" member element id.
    ///
    /// The server elements currently supported are(see dhcp-ddns.spec):
    ///   1. hostname
    ///   2. ip_address
    ///   3. port
    ///
    /// @param config_id is the "item_name" for a specific member element of
    /// the "dns_server" specification.
    /// @param pos position within the configuration text (or file) of element
    /// to be parsed.  This is passed for error messaging.
    ///
    /// @return returns a pointer to newly created parser.
    ///
    /// @throw D2CfgError if configuration contains an unknown parameter
    virtual isc::dhcp::ParserPtr
    createConfigParser(const std::string& config_id,
                       const isc::data::Element::Position& =
                       isc::data::Element::ZERO_POSITION());

    /// @brief Commits the configured DnsServerInfo
    /// Currently this method is a NOP, as the server instance is created and
    /// then added to the list of servers in build().
    virtual void commit();

private:
    /// @brief Arbitrary label assigned to this parser instance.
    /// Since servers are specified in a list this value is likely be something
    /// akin to "server:0", set during parsing.  Primarily here for diagnostics.
    std::string entry_name_;

    /// @brief Pointer to the storage area to which the parser should commit
    /// the newly created DnsServerInfo instance. This is given to us as a
    /// constructor argument by an upper level.
    DnsServerInfoStoragePtr servers_;

    /// @brief Local storage area for scalar parameter values. Use to hold
    /// data until time to commit.
    DScalarContext local_scalars_;
};

/// @brief Parser for a list of DnsServerInfos
///
/// This class parses a list of "dns_server" configuration elements.
/// (see src/bin/d2/dhcp-ddns.spec). The DnsServerInfo instances are added
/// to the given storage upon commit.
class DnsServerInfoListParser : public isc::dhcp::DhcpConfigParser {
public:

    /// @brief Constructor
    ///
    /// @param list_name is an arbitrary label assigned to this parser instance.
    /// @param servers is a pointer to the storage area to which the parser
    /// should commit the newly created DnsServerInfo instance.
    DnsServerInfoListParser(const std::string& list_name,
                            DnsServerInfoStoragePtr servers);

    /// @brief Destructor
    virtual ~DnsServerInfoListParser();

    /// @brief Performs the actual parsing of the given list "dns_server"
    /// elements.
    /// It iterates over each server entry in the list:
    ///   1. Instantiate a DnsServerInfoParser for the entry
    ///   2. Pass the element configuration to the parser's build method
    ///   3. Add the parser instance to local storage
    ///
    /// The net effect is to parse all of the server entries in the list
    /// prepping them for commit.
    ///
    /// @param server_list_config is the list of "dns_server" elements to parse.
    virtual void build(isc::data::ConstElementPtr server_list_config);

    /// @brief Commits the list of DnsServerInfos
    ///
    /// Iterates over the internal list of DdnsServerInfoParsers, invoking
    /// commit on each one.
    virtual void commit();

private:
    /// @brief Arbitrary label assigned to this parser instance.
    std::string list_name_;

    /// @brief Pointer to the storage area to which the parser should commit
    /// the list of newly created DnsServerInfo instances. This is given to us
    /// as a constructor argument by an upper level.
    DnsServerInfoStoragePtr servers_;

    /// @brief Local storage of DnsServerInfoParser instances
    isc::dhcp::ParserCollection parsers_;
};

/// @brief Parser for  DdnsDomain
///
/// This class parses the configuration element "ddns_domain" defined in
/// src/bin/d2/dhcp-ddns.spec and creates an instance of a DdnsDomain.
class DdnsDomainParser : public isc::dhcp::DhcpConfigParser {
public:
    /// @brief Constructor
    ///
    /// @param entry_name is an arbitrary label assigned to this configuration
    /// definition. Since domains are specified in a list this value is likely
    /// be something akin to "forward_ddns:0", set during parsing.
    /// @param domains is a pointer to the storage area to which the parser
    /// @param keys is a pointer to a map of the defined TSIG keys.
    /// should commit the newly created DdnsDomain instance.
    DdnsDomainParser(const std::string& entry_name, DdnsDomainMapPtr domains,
                     TSIGKeyInfoMapPtr keys);

    /// @brief Destructor
    virtual ~DdnsDomainParser();

    /// @brief Performs the actual parsing of the given  "ddns_domain" element.
    ///
    /// Parses a configuration for the elements needed to instantiate a
    /// DdnsDomain, validates those entries, creates a DdnsDomain instance
    /// then attempts to add it to a list of domains.
    ///
    /// @param domain_config is the "ddns_domain" configuration to parse
    virtual void build(isc::data::ConstElementPtr domain_config);

    /// @brief Creates a parser for the given "ddns_domain" member element id.
    ///
    /// The domain elements currently supported are(see dhcp-ddns.spec):
    ///   1. name
    ///   2. key_name
    ///   3. dns_servers
    ///
    /// @param config_id is the "item_name" for a specific member element of
    /// the "ddns_domain" specification.
    /// @param pos position within the configuration text (or file) of element
    /// to be parsed.  This is passed for error messaging.
    ///
    /// @return returns a pointer to newly created parser.
    ///
    /// @throw D2CfgError if configuration contains an unknown parameter
    virtual isc::dhcp::ParserPtr
    createConfigParser(const std::string& config_id,
                       const isc::data::Element::Position& pos =
                       isc::data::Element::ZERO_POSITION());

    /// @brief Commits the configured DdnsDomain
    /// Currently this method is a NOP, as the domain instance is created and
    /// then added to the list of domains in build().
    virtual void commit();

private:

    /// @brief Arbitrary label assigned to this parser instance.
    std::string entry_name_;

    /// @brief Pointer to the storage area to which the parser should commit
    /// the newly created DdnsDomain instance. This is given to us as a
    /// constructor argument by an upper level.
    DdnsDomainMapPtr domains_;

    /// @brief Pointer to the map of defined TSIG keys.
    /// This map is passed into us and contains all of the TSIG keys defined
    /// for this configuration.  It is used to validate the key name entry of
    /// DdnsDomains that specify one.
    TSIGKeyInfoMapPtr keys_;

    /// @brief Local storage for DnsServerInfo instances. This is passed into
    /// DnsServerInfoListParser(s), which in turn passes it into each
    /// DnsServerInfoParser.  When the DnsServerInfoParsers "commit" they add
    /// their server instance to this storage.
    DnsServerInfoStoragePtr local_servers_;

    /// @brief Local storage area for scalar parameter values. Use to hold
    /// data until time to commit.
    DScalarContext local_scalars_;
};

/// @brief Parser for a list of DdnsDomains
///
/// This class parses a list of "ddns_domain" configuration elements.
/// (see src/bin/d2/dhcp-ddns.spec). The DdnsDomain instances are added
/// to the given storage upon commit.
class DdnsDomainListParser : public isc::dhcp::DhcpConfigParser {
public:

    /// @brief Constructor
    ///
    /// @param list_name is an arbitrary label assigned to this parser instance.
    /// @param domains is a pointer to the storage area to which the parser
    /// @param keys is a pointer to a map of the defined TSIG keys.
    /// should commit the newly created DdnsDomain instance.
    DdnsDomainListParser(const std::string& list_name,
                         DdnsDomainMapPtr domains, TSIGKeyInfoMapPtr keys);

    /// @brief Destructor
    virtual ~DdnsDomainListParser();

    /// @brief Performs the actual parsing of the given list "ddns_domain"
    /// elements.
    /// It iterates over each domain entry in the list:
    ///   1. Instantiate a DdnsDomainParser for the entry
    ///   2. Pass the element configuration to the parser's build method
    ///   3. Add the parser instance to local storage
    ///
    /// The net effect is to parse all of the domain entries in the list
    /// prepping them for commit.
    ///
    /// @param domain_list_config is the list of "ddns_domain" elements to
    /// parse.
    virtual void build(isc::data::ConstElementPtr domain_list_config);

    /// @brief Commits the list of DdnsDomains
    ///
    /// Iterates over the internal list of DdnsDomainParsers, invoking
    /// commit on each one.
    virtual void commit();

private:
    /// @brief Arbitrary label assigned to this parser instance.
    std::string list_name_;

    /// @brief Pointer to the storage area to which the parser should commit
    /// the list of newly created DdnsDomain instances. This is given to us
    /// as a constructor argument by an upper level.
    DdnsDomainMapPtr domains_;

    /// @brief Pointer to the map of defined TSIG keys.
    /// This map is passed into us and contains all of the TSIG keys defined
    /// for this configuration.  It is used to validate the key name entry of
    /// DdnsDomains that specify one.
    TSIGKeyInfoMapPtr keys_;

    /// @brief Local storage of DdnsDomainParser instances
    isc::dhcp::ParserCollection parsers_;
};

/// @brief Parser for DdnsDomainListMgr
///
/// This class parses the configuration elements "forward_ddns" and
/// "reverse_ddns" as defined in src/bin/d2/dhcp-ddns.spec.  It populates the
/// given DdnsDomainListMgr with parsed information upon commit.  Note that
/// unlike other parsers, this parser does NOT instantiate the final object
/// during the commit phase, it populates it.  It must pre-exist.
class DdnsDomainListMgrParser : public isc::dhcp::DhcpConfigParser {
public:
    /// @brief Constructor
    ///
    /// @param entry_name is an arbitrary label assigned to this configuration
    /// definition.
    /// @param mgr is a pointer to the DdnsDomainListMgr to populate.
    /// @param keys is a pointer to a map of the defined TSIG keys.
    /// @throw throws D2CfgError if mgr pointer is empty.
    DdnsDomainListMgrParser(const std::string& entry_name,
                     DdnsDomainListMgrPtr mgr, TSIGKeyInfoMapPtr keys);

    /// @brief Destructor
    virtual ~DdnsDomainListMgrParser();

    /// @brief Performs the actual parsing of the given manager element.
    ///
    /// Parses a configuration for the elements needed to instantiate a
    /// DdnsDomainListMgr, validates those entries, then creates a
    /// DdnsDomainListMgr.
    ///
    /// @param mgr_config is the manager configuration to parse
    virtual void build(isc::data::ConstElementPtr mgr_config);

    /// @brief Creates a parser for the given manager member element id.
    ///
    /// The manager elements currently supported are (see dhcp-ddns.spec):
    ///     1. ddns_domains
    ///
    /// @param config_id is the "item_name" for a specific member element of
    /// the manager specification.
    /// @param pos position within the configuration text (or file) of element
    /// to be parsed.  This is passed for error messaging.
    ///
    /// @return returns a pointer to newly created parser.
    ///
    /// @throw D2CfgError if configuration contains an unknown parameter
    virtual isc::dhcp::ParserPtr
    createConfigParser(const std::string& config_id,
                       const isc::data::Element::Position& pos =
                       isc::data::Element::ZERO_POSITION());

    /// @brief Commits the configured DdsnDomainListMgr
    /// Currently this method is a NOP, as the manager instance is created
    /// in build().
    virtual void commit();

private:
    /// @brief Arbitrary label assigned to this parser instance.
    std::string entry_name_;

    /// @brief Pointer to manager instance to which the parser should commit
    /// the parsed data. This is given to us as a constructor argument by an
    /// upper level.
    DdnsDomainListMgrPtr mgr_;

    /// @brief Pointer to the map of defined TSIG keys.
    /// This map is passed into us and contains all of the TSIG keys defined
    /// for this configuration.  It is used to validate the key name entry of
    /// DdnsDomains that specify one.
    TSIGKeyInfoMapPtr keys_;

    /// @brief Local storage for DdnsDomain instances. This is passed into a
    /// DdnsDomainListParser(s), which in turn passes it into each
    /// DdnsDomainParser.  When the DdnsDomainParsers "commit" they add their
    /// domain instance to this storage.
    DdnsDomainMapPtr local_domains_;

    /// @brief Local storage area for scalar parameter values. Use to hold
    /// data until time to commit.
    /// @todo Currently, the manager has no scalars but this is likely to
    /// change as matching capabilities expand.
    DScalarContext local_scalars_;
};


}; // end of isc::d2 namespace
}; // end of isc namespace

#endif // D2_CONFIG_H
