// Copyright (C) 2013-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef D2_CONFIG_H
#define D2_CONFIG_H

#include <asiolink/io_service.h>
#include <cc/data.h>
#include <cc/simple_parser.h>
#include <cc/cfg_to_element.h>
#include <cc/user_context.h>
#include <d2srv/d2_tsig_key.h>
#include <dhcpsrv/parsers/dhcp_parsers.h>
#include <exceptions/exceptions.h>
#include <process/d_cfg_mgr.h>

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
///  "ip-address" : "192.168.1.33" ,
///  "port" : 88 ,
///  "control-socket":
///  {
///    "socket-type": "unix" ,
///    "socket-name": "/tmp/kea-ddns-ctrl-socket"
//// },
///  "tsig-keys":
//// [
///    {
///     "name": "d2_key.tmark.org" ,
///     "algorithm": "md5" ,
///     "secret": "0123456989"
///    }
///  ],
///  "forward-ddns" :
///  {
///    "ddns-domains":
///    [
///      {
///        "name": "tmark.org." ,
///        "key-name": "d2_key.tmark.org" ,
///        "dns-servers" :
///        [
///          { "hostname": "fserver.tmark.org" },
///          { "hostname": "f2server.tmark.org" }
///        ]
///      },
///      {
///        "name": "pub.tmark.org." ,
///        "key-name": "d2_key.tmark.org" ,
///        "dns-servers" :
///        [
///          { "hostname": "f3server.tmark.org" }
///        ]
///      }
///    ]
///  },
///  "reverse-ddns" :
///  {
///    "ddns-domains":
///    [
///      {
///        "name": " 0.168.192.in.addr.arpa." ,
///        "key-name": "d2_key.tmark.org" ,
///        "dns-servers" :
///        [
///          { "ip-address": "127.0.0.101" , "port": 100 ,
///            "key-name": "d2_key.tmark.org" }
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

    /// @brief Compares two D2Params's for equality
    bool operator == (const D2Params& other) const;

    /// @brief Compares two D2Params's for inequality
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
/// @param config D2Param instance to dump
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
class TSIGKeyInfo : public isc::data::UserContext, public isc::data::CfgToElement {
public:
    /// @brief Defines string values for the supported TSIG algorithms
    /// @{
    static const char* HMAC_MD5_STR;
    static const char* HMAC_SHA1_STR;
    static const char* HMAC_SHA256_STR;
    static const char* HMAC_SHA224_STR;
    static const char* HMAC_SHA384_STR;
    static const char* HMAC_SHA512_STR;
    /// @}

    /// @brief Constructor
    ///
    /// @param name the unique label used to identify this key
    /// @param algorithm the id of the encryption algorithm this key uses.
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
    /// @return const pointer reference to @c D2TsigKeyPtr
    const D2TsigKeyPtr& getTSIGKey() const {
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

    /// @brief Unparse a configuration object
    ///
    /// @return a pointer to a configuration
    virtual isc::data::ElementPtr toElement() const;

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
    D2TsigKeyPtr tsig_key_;
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
class DnsServerInfo : public isc::data::UserContext, public isc::data::CfgToElement {
public:
    /// @brief defines DNS standard port value
    static const uint32_t STANDARD_DNS_PORT = 53;

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
    /// @param tsig_key_info pointer to the TSIGKeyInfo for the server's key
    /// It defaults to an empty pointer, signifying the server has no key.
    /// @param inherited_key is a flag that indicates whether the key was
    /// inherited from the domain or not. It defaults to true i.e. inherited.
    DnsServerInfo(const std::string& hostname,
                  isc::asiolink::IOAddress ip_address,
                  uint32_t port = STANDARD_DNS_PORT,
                  bool enabled = true,
                  const TSIGKeyInfoPtr& tsig_key_info = TSIGKeyInfoPtr(),
                  bool inherited_key = true);

    /// @brief Destructor
    virtual ~DnsServerInfo();

    /// @brief Getter which returns the server's hostname.
    ///
    /// @return the hostname as a std::string.
    const std::string getHostname() const {
        return (hostname_);
    }

    /// @brief Getter which returns the server's port number.
    ///
    /// @return the port number as a unsigned integer.
    uint32_t getPort() const {
        return (port_);
    }

    /// @brief Getter which returns the server's ip_address.
    ///
    /// @return the address as an IOAddress reference.
    const isc::asiolink::IOAddress& getIpAddress() const {
        return (ip_address_);
    }

    /// @brief Convenience method which returns whether or not the
    /// server is enabled.
    ///
    /// @return true if the server is enabled, false otherwise.
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

    /// @brief Convenience method which returns the server's TSIG key name.
    ///
    /// @return the key name in a std::string. If server has no TSIG key,
    /// the string will be empty.
    const std::string getKeyName() const;

    /// @brief Getter which returns the server's TSIGKey info.
    ///
    /// @return the pointer to the server storage. If the server
    /// is not configured to use TSIG the pointer will be empty.
    const TSIGKeyInfoPtr& getTSIGKeyInfo() {
        return (tsig_key_info_);
    }

    /// @brief Returns a text representation for the server.
    std::string toText() const;

    /// @brief Unparse a configuration object
    ///
    /// @return a pointer to a configuration
    virtual isc::data::ElementPtr toElement() const;

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

    /// @brief Pointer to the server TSIGKeyInfo.
    /// Value is empty if the server is not configured for TSIG.
    TSIGKeyInfoPtr tsig_key_info_;

    /// @brief Inherited key. When true the key was inherited from the domain,
    /// false otherwise.
    bool inherited_key_;
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
/// it.  Its primary use is to map a domain to the DNS server(s) responsible
/// for it.
/// @todo Currently the name entry for a domain is just a std::string. It
/// may be worthwhile to change this to a dns::Name for purposes of better
/// validation and matching capabilities.
class DdnsDomain : public isc::data::UserContext, public isc::data::CfgToElement {
public:
    /// @brief Constructor
    ///
    /// @param name is the domain name of the domain.
    /// @param servers is the list of server(s) supporting this domain.
    /// @param key_name is the TSIG key name of the domain.
    DdnsDomain(const std::string& name, DnsServerInfoStoragePtr servers,
               const std::string& key_name = "");

    /// @brief Destructor
    virtual ~DdnsDomain();

    /// @brief Getter which returns the domain's name.
    ///
    /// @return returns the name in a std::string.
    const std::string getName() const {
        return (name_);
    }

    /// @brief Getter which returns the domain's TSIG key name.
    ///
    /// @note: TSIG key infos are in servers.
    ///
    /// @return returns the key name in a std::string. If domain has no
    /// TSIG key, the string will be empty.
    const std::string getKeyName() const {
        return (key_name_);
    }

    /// @brief Getter which returns the domain's list of servers.
    ///
    /// @return returns the pointer to the server storage.
    const DnsServerInfoStoragePtr& getServers() {
        return (servers_);
    }

    /// @brief Unparse a configuration object
    ///
    /// @return a pointer to a configuration
    virtual isc::data::ElementPtr toElement() const;

private:
    /// @brief The domain name of the domain.
    std::string name_;

    /// @brief The list of server(s) supporting this domain.
    DnsServerInfoStoragePtr servers_;

    /// @brief The TSIG key name (empty when there is no key for the domain).
    std::string key_name_;
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
class DdnsDomainListMgr : public isc::data::CfgToElement {
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

    /// @brief Unparse a configuration object
    ///
    /// @return a pointer to a configuration
    virtual isc::data::ElementPtr toElement() const;

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
class DScalarContext : public process::ConfigBase {
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
    virtual process::ConfigPtr clone() {
        return (process::ConfigPtr(new DScalarContext(*this)));
    }

    /// @brief Unparse a configuration object
    ///
    /// @return a pointer to a configuration
    virtual isc::data::ElementPtr toElement() const {
        isc_throw(isc::NotImplemented, "DScalarContext::ElementPtr");
    }

protected:
    /// @brief Copy constructor
    DScalarContext(const DScalarContext& rhs) : ConfigBase(rhs) {
    }

private:
    /// @brief Private assignment operator, not implemented.
    DScalarContext& operator=(const DScalarContext& rhs);
};

/// @brief Defines a pointer for DScalarContext instances.
typedef boost::shared_ptr<DScalarContext> DScalarContextPtr;

/// @brief Parser for TSIGKeyInfo
///
/// This class parses the configuration element "tsig-key"
/// and creates an instance of a TSIGKeyInfo.
class TSIGKeyInfoParser : public data::SimpleParser {
public:
    /// @brief Performs the actual parsing of the given "tsig-key" element.
    ///
    /// Parses a configuration for the elements needed to instantiate a
    /// TSIGKeyInfo, validates those entries, creates a TSIGKeyInfo instance
    ///
    /// @param key_config is the "tsig-key" configuration to parse
    ///
    /// @return pointer to the new TSIGKeyInfo instance
    TSIGKeyInfoPtr parse(data::ConstElementPtr key_config);

};

/// @brief Parser for a list of TSIGKeyInfos
///
/// This class parses a list of "tsig-key" configuration elements.
/// The TSIGKeyInfo instances are added to the given storage upon commit.
class TSIGKeyInfoListParser : public data::SimpleParser {
public:
    /// @brief Performs the parsing of the given list "tsig-key" elements.
    ///
    /// Creates an empty TSIGKeyInfoMap
    ///
    /// Instantiates a TSIGKeyInfoParser
    /// It iterates over each key entry in the list:
    ///   2. Pass the element configuration to the parser's parse method
    ///   3. Add the new TSIGKeyInfo instance to the key map
    ///
    /// @param key_list_config is the list of "tsig_key" elements to parse.
    ///
    /// @return a map containing the TSIGKeyInfo instances
    TSIGKeyInfoMapPtr parse(data::ConstElementPtr key_list_config);
};

/// @brief Parser for  DnsServerInfo
///
/// This class parses the configuration element "dns-server"
/// and creates an instance of a DnsServerInfo.
class DnsServerInfoParser : public data::SimpleParser {
public:
    /// @brief Performs the actual parsing of the given  "dns-server" element.
    ///
    /// Parses a configuration for the elements needed to instantiate a
    /// DnsServerInfo, validates those entries, creates a DnsServerInfo instance
    /// and returns it.
    ///
    /// @param server_config is the "dns-server" configuration to parse
    /// @param domain_config the parent domain's configuration
    /// @param keys map of defined TSIG keys
    ///
    /// @return a pointer to the newly created server instance
    ///
    /// @throw D2CfgError if:
    /// -# hostname is not blank, hostname is not yet supported
    /// -# ip_address is invalid
    /// -# port is 0
    DnsServerInfoPtr parse(data::ConstElementPtr server_config,
                           data::ConstElementPtr domain_config,
                           const TSIGKeyInfoMapPtr keys);
};

/// @brief Parser for a list of DnsServerInfos
///
/// This class parses a list of "dns-server" configuration elements.
/// The DnsServerInfo instances are added
/// to the given storage upon commit.
class DnsServerInfoListParser : public data::SimpleParser {
public:
    /// @brief Performs the actual parsing of the given list "dns-server"
    /// elements.
    ///
    /// Creates an empty server list
    /// It iterates over each server entry in the list:
    ///   1. Creates a server instance by passing the entry to @c
    ///   DnsSeverInfoParser::parse()
    ///   2. Adds the server to the server list
    ///
    /// @param server_list_config is the list of "dns-server" elements to parse.
    /// @param domain_config the parent domain's configuration
    /// @param keys map of defined TSIG keys
    /// @return A pointer to the new, populated server list
    DnsServerInfoStoragePtr parse(data::ConstElementPtr server_list_config,
                                  data::ConstElementPtr domain_config,
                                  const TSIGKeyInfoMapPtr keys);
};

/// @brief Parser for  DdnsDomain
///
/// This class parses the configuration element "ddns-domain"
/// and creates an instance of a DdnsDomain.
class DdnsDomainParser : public data::SimpleParser {
public:
    /// @brief Performs the actual parsing of the given  "ddns-domain" element.
    ///
    /// Parses a configuration for the elements needed to instantiate a
    /// DdnsDomain, validates those entries, and creates a DdnsDomain instance.
    ///
    /// @param domain_config is the "ddns-domain" configuration to parse
    /// @param keys map of defined TSIG keys
    ///
    /// @return a pointer to the new domain instance
    DdnsDomainPtr parse(data::ConstElementPtr domain_config,
                        const TSIGKeyInfoMapPtr keys);
};

/// @brief Parser for a list of DdnsDomains
///
/// This class parses a list of "ddns-domain" configuration elements
/// into a map of DdnsDomains.
class DdnsDomainListParser : public data::SimpleParser {
public:
    /// @brief Performs the actual parsing of the given list "ddns-domain"
    /// elements.
    /// Creates a new DdnsDomain map
    /// It iterates over each domain entry in the list:
    ///   1. Creates a DdnsDomain instance by passing the entry into @c
    ///   DdnsDomainParser::parser()
    ///   2. Adds the DdnsDomain instance to the domain map
    ///
    /// @param domain_list_config is the list of "ddns-domain" elements to
    /// parse.
    /// @param keys map of defined TSIG keys
    /// @return a pointer to the newly populated domain map
    DdnsDomainMapPtr parse(data::ConstElementPtr domain_list_config,
                           const TSIGKeyInfoMapPtr keys);
};

/// @brief Parser for DdnsDomainListMgr
///
/// This class parses the configuration elements "forward-ddns" and
/// "reverse-ddns".  It populates the given DdnsDomainListMgr with parsed
/// information.
class DdnsDomainListMgrParser : public data::SimpleParser {
public:
    /// @brief Performs the actual parsing of the given manager element.
    ///
    /// Parses a configuration for the elements needed to instantiate a
    /// DdnsDomainListMgr, validates those entries, then creates a
    /// DdnsDomainListMgr.
    ///
    /// @param mgr_config manager configuration to parse
    /// @param mgr_name convenience label for the manager instance
    /// @param keys map of defined TSIG keys
    ///
    /// @return a pointer to the new manager instance
    DdnsDomainListMgrPtr parse(data::ConstElementPtr mgr_config,
                               const std::string& mgr_name,
                               const TSIGKeyInfoMapPtr keys);
};

} // end of isc::d2 namespace
} // end of isc namespace

#endif // D2_CONFIG_H
