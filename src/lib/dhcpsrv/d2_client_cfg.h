// Copyright (C) 2013-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef D2_CLIENT_CFG_H
#define D2_CLIENT_CFG_H

/// @file d2_client_cfg.h Defines the D2ClientConfig class.
/// This file defines the classes Kea uses to manage configuration needed to
/// act as a client of the kea-dhcp-ddns module (aka D2).
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


    /// @brief Default configuration constants.
    /// @todo For now these are hard-coded as configuraiton layer cannot
    /// readily provide them (see Trac #3358).
    static const char *DFT_SERVER_IP;
    static const size_t DFT_SERVER_PORT;
    static const char *DFT_V4_SENDER_IP;
    static const char *DFT_V6_SENDER_IP;
    static const size_t DFT_SENDER_PORT;
    static const size_t DFT_MAX_QUEUE_SIZE;
    static const char *DFT_NCR_PROTOCOL;
    static const char *DFT_NCR_FORMAT;
    static const bool DFT_ALWAYS_INCLUDE_FQDN;
    static const bool DFT_OVERRIDE_NO_UPDATE;
    static const bool DFT_OVERRIDE_CLIENT_UPDATE;
    static const bool DFT_REPLACE_CLIENT_NAME;
    static const char *DFT_GENERATED_PREFIX;

    /// @brief Constructor
    ///
    /// @param enable_updates Enables DHCP-DDNS updates
    /// @param server_ip IP address of the kea-dhcp-ddns server (IPv4 or IPv6)
    /// @param server_port IP port of the kea-dhcp-ddns server
    /// @param sender_ip IP address of the kea-dhcp-ddns server (IPv4 or IPv6)
    /// @param sender_port IP port of the kea-dhcp-ddns server
    /// @param max_queue_size  maximum NCRs allowed in sender's queue
    /// @param ncr_protocol Socket protocol to use with kea-dhcp-ddns
    /// Currently only UDP is supported.
    /// @param ncr_format Format of the kea-dhcp-ddns requests.
    /// Currently only JSON format is supported.
    /// @param always_include_fqdn Enables always including the FQDN option in
    /// DHCP responses.
    /// @param override_no_update Enables updates, even if clients request no
    /// updates.
    /// @param override_client_update Perform updates, even if client requested
    /// delegation.
    /// @param replace_client_name enables replacement of the domain-name
    /// supplied by the client with a generated name.
    /// @param generated_prefix Prefix to use when generating domain-names.
    /// @param qualifying_suffix Suffix to use to qualify partial domain-names.
    ///
    /// @c enable_updates is mandatory, @c qualifying_suffix is mandatory
    /// when updates are enabled, other parameters are optional.
    ///
    /// @throw D2ClientError if given an invalid protocol or format.
    D2ClientConfig(const bool enable_updates,
                   const isc::asiolink::IOAddress& server_ip,
                   const size_t server_port,
                   const isc::asiolink::IOAddress& sender_ip,
                   const size_t sender_port,
                   const size_t max_queue_size,
                   const dhcp_ddns::NameChangeProtocol& ncr_protocol,
                   const dhcp_ddns::NameChangeFormat& ncr_format,
                   const bool always_include_fqdn,
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

    /// @brief Return the IP address of kea-dhcp-ddns (IPv4 or IPv6).
    const isc::asiolink::IOAddress& getServerIp() const {
        return(server_ip_);
    }

    /// @brief Return the IP port of kea-dhcp-ddns.
    size_t getServerPort() const {
        return(server_port_);
    }

    /// @brief Return the IP address client should use to send
    const isc::asiolink::IOAddress& getSenderIp() const {
        return(sender_ip_);
    }

    /// @brief Return the IP port client should use to send
    size_t getSenderPort() const {
        return(sender_port_);
    }

    /// @brief Return Maximun sender queue size
    size_t getMaxQueueSize() const {
        return(max_queue_size_);
    }

    /// @brief Return the socket protocol to use with kea-dhcp-ddns.
    const dhcp_ddns::NameChangeProtocol& getNcrProtocol() const {
         return(ncr_protocol_);
    }

    /// @brief Return the kea-dhcp-ddns request format.
    const dhcp_ddns::NameChangeFormat& getNcrFormat() const {
        return(ncr_format_);
    }

    /// @brief Return whether or not FQDN is always included in DHCP responses.
    bool getAlwaysIncludeFqdn() const {
        return(always_include_fqdn_);
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

    /// @brief Sets enable-updates flag to the given value.
    ///
    /// This is the only value that may be altered outside the constructor
    /// as it may be desirable to toggle it off and on when dealing with
    /// D2 IO errors.
    ///
    /// @param enable boolean value to assign to the enable-updates flag
    void enableUpdates(bool enable);

protected:
    /// @brief Validates member values.
    ///
    /// Method is used by the constructor to validate member contents.
    ///
    /// @throw D2ClientError if given an invalid protocol or format.
    virtual void validateContents();

private:
    /// @brief Indicates whether or not DHCP DDNS updating is enabled.
    bool enable_updates_;

    /// @brief IP address of the kea-dhcp-ddns server (IPv4 or IPv6).
    isc::asiolink::IOAddress server_ip_;

    /// @brief IP port of the kea-dhcp-ddns server.
    size_t server_port_;

    /// @brief IP address on which the client should send
    isc::asiolink::IOAddress sender_ip_;

    /// @brief IP port on which the client should send
    size_t sender_port_;

    /// @brief Maxium number of NCRs allowed to queue waiting to send
    size_t max_queue_size_;

    /// @brief The socket protocol to use with kea-dhcp-ddns.
    /// Currently only UDP is supported.
    dhcp_ddns::NameChangeProtocol ncr_protocol_;

    /// @brief Format of the kea-dhcp-ddns requests.
    /// Currently only JSON format is supported.
    dhcp_ddns::NameChangeFormat ncr_format_;

    /// @brief Should Kea always include the FQDN option in its response.
    bool always_include_fqdn_;

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

} // namespace isc
} // namespace dhcp

#endif
