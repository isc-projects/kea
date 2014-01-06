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

#ifndef D2_CLIENT_H
#define D2_CLIENT_H

/// @file d2_client.h Defines the D2ClientConfig and D2ClientMgr classes.
/// This file defines the classes Kea uses to act as a client of the b10-
/// dhcp-ddns module (aka D2).
///
#include <asiolink/io_address.h>
#include <dhcp_ddns/ncr_io.h>
#include <exceptions/exceptions.h>

#include <boost/shared_ptr.hpp>

#include <stdint.h>
#include <string>
#include <vector>

namespace isc {
namespace dhcp {


/// An exception that is thrown if an error occurs while configuring
/// the D2 DHCP DDNS client.
class D2ClientError : public isc::Exception {
public:

    /// @brief constructor
    ///
    /// @param file name of the file, where exception occurred
    /// @param line line of the file, where exception occurred
    /// @param what text description of the issue that caused exception
    D2ClientError(const char* file, size_t line, const char* what)
        : isc::Exception(file, line, what) {}
};

/// @brief Acts as a storage vault for D2 client configuration
///
/// A simple container class for storing and retrieving the configuration
/// parameters associated with DHCP-DDNS and acting as a client of D2.
/// Instances of this class may be constructed through configuration parsing.
///
class D2ClientConfig {
public:
    /// @brief Constructor
    ///
    /// @param enable_updates Enables DHCP-DDNS updates
    /// @param server_ip IP address of the b10-dhcp-ddns server
    /// @param server_port IP port of the b10-dhcp-ddns server
    /// @param ncr_protocol Socket protocol to use with b10-dhcp-ddns
    /// Currently only UDP is supported.
    /// @param ncr_format Format of the b10-dhcp-ddns requests.
    /// Currently only JSON format is supported.
    /// @param remove_on_renew Enables DNS Removes when renewing a lease
    /// If true, Kea should request an explicit DNS remove prior to requesting
    /// a DNS update when renewing a lease.
    /// (Note: b10-dhcp-ddns is implemented per RFC 4703 and such a remove
    /// is unnecessary).
    /// @param always_include_fqdn Enables always including the FQDN option in
    /// DHCP responses.
    /// @param allow_client_update Enables delegation of updates to clients
    /// @param override_no_update Enables updates, even if clients request no
    /// updates.
    /// @param override_client_update Perform updates, even if client requested
    /// delegation.
    /// @param replace_client_name enables replacement of the domain-name
    /// supplied by the client with a generated name.
    /// @param generated_prefix Prefix to use when generating domain-names.
    /// @param  qualifying_suffix Suffix to use to qualify partial domain-names.
    ///
    /// @throw D2ClientError if given an invalid protocol or format.
    D2ClientConfig(const bool enable_updates,
                   const isc::asiolink::IOAddress& server_ip,
                   const size_t server_port,
                   const dhcp_ddns::NameChangeProtocol& ncr_protocol,
                   const dhcp_ddns::NameChangeFormat& ncr_format,
                   const bool remove_on_renew,
                   const bool always_include_fqdn,
                   const bool allow_client_update,
                   const bool override_no_update,
                   const bool override_client_update,
                   const bool replace_client_name,
                   const std::string& generated_prefix,
                   const std::string& qualifying_suffix);

    /// @brief Default constructor
    /// The default constructor creates an instance that has updates disabled.
    D2ClientConfig();

    /// @brief Destructor
    virtual ~D2ClientConfig();

    /// @brief Return whether or not DHCP-DDNS updating is enabled.
    bool getEnableUpdates() const {
        return(enable_updates_);
    }

    /// @brief Return the IP address of b10-dhcp-ddns.
    const isc::asiolink::IOAddress& getServerIp() const {
        return(server_ip_);
    }

    /// @brief Return the IP port of b10-dhcp-ddns.
    size_t getServerPort() const {
        return(server_port_);
    }

    /// @brief Return the socket protocol to use with b10-dhcp-ddns.
    const dhcp_ddns::NameChangeProtocol& getNcrProtocol() const {
         return(ncr_protocol_);
    }

    /// @brief Return the b10-dhcp-ddns request format.
    const dhcp_ddns::NameChangeFormat& getNcrFormat() const {
        return(ncr_format_);
    }

    /// @brief Return whether or not removes should be sent for lease renewals.
    bool getRemoveOnRenew() const {
        return(remove_on_renew_);
    }

    /// @brief Return whether or not FQDN is always included in DHCP responses.
    bool getAlwaysIncludeFqdn() const {
        return(always_include_fqdn_);
    }

    /// @brief Return whether or not updates can be delegated to clients.
    bool getAllowClientUpdate() const {
        return(allow_client_update_);
    }

    /// @brief Return if updates are done even if clients request no updates.
    bool getOverrideNoUpdate() const {
        return(override_no_update_);
    }

    /// @brief Return if updates are done even when clients request delegation.
    bool getOverrideClientUpdate() const {
        return(override_client_update_);
    }

    /// @brief Return whether or not client's domain-name is always replaced.
    bool getReplaceClientName() const {
        return(replace_client_name_);
    }

    /// @brief Return the prefix to use when generating domain-names.
    const std::string& getGeneratedPrefix() const {
        return(generated_prefix_);
    }

    /// @brief Return the suffix to use to qualify partial domain-names.
    const std::string& getQualifyingSuffix() const {
        return(qualifying_suffix_);
    }

    /// @brief Compares two D2ClientConfigs for equality
    bool operator == (const D2ClientConfig& other) const;

    /// @brief Compares two D2ClientConfigs for inequality
    bool operator != (const D2ClientConfig& other) const;

    /// @brief Generates a string representation of the class contents.
    std::string toText() const;

private:
    /// @brief Indicates whether or not DHCP DDNS updating is enabled.
    bool enable_updates_;

    /// @brief IP address of the b10-dhcp-ddns server.
    isc::asiolink::IOAddress server_ip_;

    /// @brief IP port of the b10-dhcp-ddns server.
    size_t server_port_;

    /// @brief The socket protocol to use with b10-dhcp-ddns.
    /// Currently only UPD is supported.
    dhcp_ddns::NameChangeProtocol ncr_protocol_;

    /// @brief Format of the b10-dhcp-ddns requests.
    /// Currently only JSON format is supported.
    dhcp_ddns::NameChangeFormat ncr_format_;

    /// @brief Should Kea request a DNS Remove when renewing a lease.
    /// If true, Kea should request an explicit DNS remove prior to requesting
    /// a DNS update when renewing a lease.
    /// (Note: b10-dhcp-ddns is implemented per RFC 4703 and such a remove
    /// is unnecessary).
    bool remove_on_renew_;

    /// @brief Should Kea always include the FQDN option in its response.
    bool always_include_fqdn_;

    /// @brief Should Kea permit the client to do updates.
    bool allow_client_update_;

    /// @brief Should Kea perform updates, even if client requested no updates.
    /// Overrides the client request for no updates via the N flag.
    bool override_no_update_;

    /// @brief Should Kea perform updates, even if client requested delegation.
    bool override_client_update_;

    /// @brief Should Kea replace the domain-name supplied by the client.
    bool replace_client_name_;

    /// @brief Prefix Kea should use when generating domain-names.
    std::string generated_prefix_;

    /// @brief Suffix Kea should use when to qualify partial domain-names.
    std::string qualifying_suffix_;
};

std::ostream&
operator<<(std::ostream& os, const D2ClientConfig& config);

/// @brief Defines a pointer for D2ClientConfig instances.
typedef boost::shared_ptr<D2ClientConfig> D2ClientConfigPtr;

/// @brief D2ClientMgr isolates Kea from the details of being a D2 client.
///
/// Provides services for managing the current D2ClientConfig and managing
/// communications with D2. (@todo The latter will be added once communication
/// with D2 is implemented through the integration of
/// dhcp_ddns::NameChangeSender interface(s).
///
class D2ClientMgr {
public:
    /// @brief Constructor
    ///
    /// Default constructor which constructs an instance which has DHCP-DDNS
    /// updates disabled.
    D2ClientMgr();

    /// @brief Destructor.
    ~D2ClientMgr();

    /// @brief Updates the DHCP-DDNS client configuration to the given value.
    ///
    /// @param new_config pointer to the new client configuration.
    /// @throw D2ClientError if passed an empty pointer.
    void setD2ClientConfig(D2ClientConfigPtr& new_config);

    /// @brief Convenience method for checking if DHCP-DDNS is enabled.
    ///
    /// @return True if the D2 configuration is enabled.
    bool isDhcpDdnsEnabled();

    /// @brief Fetches the DHCP-DDNS configuration pointer.
    ///
    /// @return a reference to the current configuration pointer.
    const D2ClientConfigPtr& getD2ClientConfig() const;

private:
    /// @brief Container class for DHCP-DDNS configuration parameters.
    D2ClientConfigPtr d2_client_config_;
};

/// @brief Defines a pointer for D2ClientMgr instances.
typedef boost::shared_ptr<D2ClientMgr> D2ClientMgrPtr;


} // namespace isc
} // namespace dhcp

#endif
