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

#ifndef D2_CONFIG_H
#define D2_CONFIG_H

#include <asiolink/io_address.h>
#include <cc/data.h>
#include <d2/d_cfg_mgr.h>
#include <dhcpsrv/dhcp_parsers.h>
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
/// The application configuration consists of a set of scalar parameters and
/// two managed lists of domains: one list for forward domains and one list for
/// reverse domains.
///
/// Each managed list consists of a list one or more domains and is represented
/// by the class DdnsDomainListMgr.
///
/// Each domain consists of a set of scalars parameters and a list of DNS
/// servers which support that domain.  Domains are represented by the class,
/// DdnsDomain.
///
/// Each server consists of a set of scalars used to describe the server such
/// that the application can carry out DNS update exchanges with it. Servers
/// are represented by the class, DnsServerInfo.
///
/// The configuration specification for use with BIND10 is detailed in the file
/// dhcp-ddns.spec.
///
/// The parsing class hierarchy reflects this same scheme.  Working top down:
///
/// A DdnsDomainListMgrParser parses a managed domain list entry. It handles
/// any scalars which belong to the manager as well as creating and invoking a
/// DdnsDomainListParser to parse its list of domain entries.
///
/// A DdnsDomainLiatParser creates and invokes DdnsDomainListParser for each
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

/// @brief Exception thrown when the error during configuration handling
/// occurs.
class D2CfgError : public isc::Exception {
public:
    D2CfgError(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) { };
};

/// @brief Represents a specific DNS Server.
/// It provides information about the server's network identity and typically
/// belongs to a list of servers supporting DNS for a given domain. It will
/// be used to establish communications with the server to carry out DNS
/// updates.
class DnsServerInfo {
public:

    /// @brief defines DNS standard port value
    static const uint32_t standard_dns_port;

    /// @brief defines an "empty" string version of an ip address.
    static const char* empty_ip_str;

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
                  isc::asiolink::IOAddress ip_address, uint32_t port,
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
class DdnsDomain {
public:
    /// @brief Constructor
    ///
    /// @param name is the domain name of the domain.
    /// @param key_name is the TSIG key name for use with this domain.
    /// (@TODO TSIG is not yet functional).
    /// @param servers is the list of server(s) supporting this domain.
    DdnsDomain(const std::string& name, const std::string& key_name,
               DnsServerInfoStoragePtr servers);

    /// @brief Destructor
    virtual ~DdnsDomain();

    /// @brief Getter which returns the domain's name.
    ///
    /// @return returns the name in an std::string.
    const std::string getName() const {
        return (name_);
    }

    /// @brief Getter which returns the domain's TSIG key name.
    ///
    /// @return returns the key name in an std::string.
    const std::string getKeyName() const {
        return (key_name_);
    }

    /// @brief Getter which returns the domain's list of servers.
    ///
    /// @return returns the pointer to the server storage.
    const DnsServerInfoStoragePtr& getServers() {
        return (servers_);
    }

private:
    /// @brief The domain name of the domain.
    std::string name_;

    /// @brief The name of the TSIG key for use with this domain.
    /// @TODO TSIG is not yet functional).
    std::string key_name_;

    /// @brief The list of server(s) supporting this domain.
    DnsServerInfoStoragePtr servers_;
};

/// @brief Defines a pointer for DdnsDomain instances.
typedef boost::shared_ptr<DdnsDomain> DdnsDomainPtr;

/// @brief Defines a storage container for DdnsDomain pointers.
typedef std::map<std::string, DdnsDomainPtr> DdnsDomainStorage;

/// @brief Defines a pointer to DdnsDomain storage containers.
typedef boost::shared_ptr<DdnsDomainStorage> DdnsDomainStoragePtr;

/// @brief Defines a domain and domain key pair for iterating.
typedef std::pair<std::string, DdnsDomainPtr> DdnsDomainPtrPair;


/// @brief Provides storage for and management of a list of DNS domains.
/// In addition to housing the domain list storage, it provides domain matching
/// services.  These services are used to match a FQDN to a domain.  Currently
/// it supports a single matching service, which will return the matching
/// domain or a wild card domain if one is specified.  The wild card domain is
/// specified as a domain whose name is "*".
/// As matching capabilities evolve this class is expected to expand.
class DdnsDomainListMgr {
public:
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
    /// the it will be returned immediately for any FQDN.
    ///
    /// @param fqdn is the name for which to look.
    /// @param domain receives the matching domain. Note that it will be reset
    /// upon entry and only set if a match is subsequently found.
    ///
    /// @return returns true if a match is found, false otherwise.
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
    const DdnsDomainStoragePtr &getDomains() {
        return (domains_);
    }

    /// @brief Sets the manger's domain list to the given list of domains.
    /// This method will scan the inbound list for the wild card domain and
    /// set the internal wild card domain pointer accordingly.
    void setDomains(DdnsDomainStoragePtr domains);

private:
    /// @brief An arbitrary label assigned to this manager.
    std::string name_;

    /// @brief Storage for the list of domains.
    DdnsDomainStoragePtr domains_;

    /// @brief Pointer to the wild card domain.
    DdnsDomainPtr wildcard_domain_;
};

/// @brief Defines a pointer for DdnsDomain instances.
typedef boost::shared_ptr<DdnsDomainListMgr> DdnsDomainListMgrPtr;

/// @brief Storage container for scalar configuration parameters.
/// This class is useful for implementing parsers for more complex configuration
/// elements (e.g. those of item type "map").  It provides a convenient way to
/// add storage to the parser for an arbitrary number and variety of simple
/// configuration items (e.g. ints, bools, strings...) without explicitly adding
/// storage for each individual type needed by the parser.
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
    /// @return returns a raw pointer to the new clone.
    virtual DScalarContext* clone() {
        return (new DScalarContext(*this));
    }

protected:
    /// @brief Copy constructor
    DScalarContext(const DScalarContext& rhs) : DCfgContextBase(rhs){
    }

private:
    /// @brief Private assignment operator, not implemented.
    DScalarContext& operator=(const DScalarContext& rhs);
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
    /// The results of the parsing are retained internally for use during
    /// commit.
    ///
    /// @param server_config is the "dns_server" configuration to parse
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
    ///
    /// @return returns a pointer to newly created parser.
    virtual isc::dhcp::ParserPtr createConfigParser(const std::string&
                                                    config_id);

    /// @brief Instantiates a DnsServerInfo from internal data values
    /// saves it to the storage area pointed to by servers_.
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
                            DnsServerInfoStoragePtr servers_);

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

    /// @brief Iterates over the internal list of DnsServerInfoParsers,
    /// invoking commit on each.  This causes each parser to instantiate a
    /// DnsServerInfo from its internal data values and add that that server
    /// instance to the storage area, servers_.
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
    /// should commit the newly created DdnsDomain instance.
    DdnsDomainParser(const std::string& entry_name,
                     DdnsDomainStoragePtr domains);

    /// @brief Destructor
    virtual ~DdnsDomainParser();

    /// @brief Performs the actual parsing of the given  "ddns_domain" element.
    /// The results of the parsing are retained internally for use during
    /// commit.
    ///
    /// @param server_config is the "ddns_domain" configuration to parse
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
    ///
    /// @return returns a pointer to newly created parser.
    virtual isc::dhcp::ParserPtr createConfigParser(const std::string&
                                                    config_id);

    /// @brief Instantiates a DdnsDomain from internal data values
    /// saves it to the storage area pointed to by domains_.
    virtual void commit();

private:

    /// @brief Arbitrary label assigned to this parser instance.
    std::string entry_name_;

    /// @brief Pointer to the storage area to which the parser should commit
    /// the newly created DdnsDomain instance. This is given to us as a
    /// constructor argument by an upper level.
    DdnsDomainStoragePtr domains_;

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
    /// should commit the newly created DdnsDomain instance.
    DdnsDomainListParser(const std::string& list_name,
                            DdnsDomainStoragePtr domains_);

    /// @brief Destructor
    virtual ~DdnsDomainListParser();

    /// @brief Performs the actual parsing of the given list "ddns_domain"
    /// elements.
    /// It iterates over each server entry in the list:
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

    /// @brief Iterates over the internal list of DdnsDomainParsers, invoking
    /// commit on each.  This causes each parser to instantiate a DdnsDomain
    /// from its internal data values and add that domain instance to the
    /// storage area, domains_.
    virtual void commit();

private:
    /// @brief Arbitrary label assigned to this parser instance.
    std::string list_name_;

    /// @brief Pointer to the storage area to which the parser should commit
    /// the list of newly created DdnsDomain instances. This is given to us
    /// as a constructor argument by an upper level.
    DdnsDomainStoragePtr domains_;

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
    /// @throw throws D2CfgError if mgr pointer is empty.
    DdnsDomainListMgrParser(const std::string& entry_name,
                     DdnsDomainListMgrPtr& mgr);

    /// @brief Destructor
    virtual ~DdnsDomainListMgrParser();

    /// @brief Performs the actual parsing of the given manager element.
    /// The results of the parsing are retained internally for use during
    /// commit.
    ///
    /// @param mgr_config is the manager configuration to parse
    virtual void build(isc::data::ConstElementPtr mgr_config);

    /// @brief Creates a parser for the given manager member element id.
    ///
    /// 
    /// The manager elements currently supported are (see dhcp-ddns.spec):
    ///     1. ddns_domains 
    ///
    /// @param config_id is the "item_name" for a specific member element of
    /// the manager specification.
    ///
    /// @return returns a pointer to newly created parser.
    virtual isc::dhcp::ParserPtr createConfigParser(const std::string&
                                                    config_id);

    /// @brief Populates the DdnsDomainListMgr from internal data values
    /// set during parsing.
    virtual void commit();

private:
    /// @brief Arbitrary label assigned to this parser instance.
    std::string entry_name_;

    /// @brief Pointer to manager instance to which the parser should commit
    /// the parsed data. This is given to us as a constructor argument by an
    /// upper level.
    DdnsDomainListMgrPtr mgr_;

    /// @brief Local storage for DdnsDomain instances. This is passed into a
    /// DdnsDomainListParser(s), which in turn passes it into each
    /// DdnsDomainParser.  When the DdnsDomainParsers "commit" they add their
    /// domain instance to this storage.
    DdnsDomainStoragePtr local_domains_;

    /// @brief Local storage area for scalar parameter values. Use to hold
    /// data until time to commit.
    /// @TODO Currently, the manager has no scalars but this is likely to
    /// change as matching capabilities expand.
    DScalarContext local_scalars_;
};



}; // end of isc::d2 namespace
}; // end of isc namespace

#endif // D2_CONFIG_H
