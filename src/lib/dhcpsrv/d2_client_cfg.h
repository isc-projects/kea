// Copyright (C) 2013-2022 Internet Systems Consortium, Inc. ("ISC")
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
#include <cc/cfg_to_element.h>
#include <cc/user_context.h>
#include <dhcp_ddns/ncr_io.h>
#include <dhcpsrv/cfg_globals.h>
#include <exceptions/exceptions.h>
#include <util/optional.h>

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

/// @brief Callback function for @c D2ClientConfig that retrieves globally
/// configured parameters.
typedef std::function<ConstCfgGlobalsPtr()> FetchNetworkGlobalsFn;


/// @brief Acts as a storage vault for D2 client configuration
///
/// A simple container class for storing and retrieving the configuration
/// parameters associated with DHCP-DDNS and acting as a client of D2.
/// Instances of this class may be constructed through configuration parsing.
///
class D2ClientConfig : public data::UserContext, public isc::data::CfgToElement {
public:
    /// @brief Default configuration constants.
    static const char* DFT_SERVER_IP;
    static const size_t DFT_SERVER_PORT;
    static const char* DFT_V4_SENDER_IP;
    static const char* DFT_V6_SENDER_IP;
    static const size_t DFT_SENDER_PORT;
    static const size_t DFT_MAX_QUEUE_SIZE;
    static const char* DFT_NCR_PROTOCOL;
    static const char* DFT_NCR_FORMAT;
    static const bool DFT_OVERRIDE_NO_UPDATE;
    static const bool DFT_OVERRIDE_CLIENT_UPDATE;
    static const char* DFT_REPLACE_CLIENT_NAME_MODE;
    static const char* DFT_GENERATED_PREFIX;
    static const char* DFT_HOSTNAME_CHAR_SET;
    static const char* DFT_HOSTNAME_CHAR_REPLACEMENT;

    /// @brief Defines the client name replacement modes.
    enum ReplaceClientNameMode  {
        RCM_NEVER,
        RCM_ALWAYS,
        RCM_WHEN_PRESENT,
        RCM_WHEN_NOT_PRESENT
    };

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
    /// @c enable_updates is mandatory, other parameters are optional.
    ///
    /// @throw D2ClientError if given an invalid protocol or format.
    D2ClientConfig(const bool enable_updates,
                   const isc::asiolink::IOAddress& server_ip,
                   const size_t server_port,
                   const isc::asiolink::IOAddress& sender_ip,
                   const size_t sender_port,
                   const size_t max_queue_size,
                   const dhcp_ddns::NameChangeProtocol& ncr_protocol,
                   const dhcp_ddns::NameChangeFormat& ncr_format);

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

    /// @brief Return Maximum sender queue size
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

    /// @brief Converts labels to  ReplaceClientNameMode enum values.
    ///
    /// @param mode_str text to convert to an enum.
    /// Valid string values: "never", "always", "when-present",
    /// "when-not-present" (case-insensitive)
    ///
    /// @return NameChangeFormat value which maps to the given string.
    ///
    /// @throw isc::BadValue if given a string value which does not map to an
    /// enum value.
    static ReplaceClientNameMode stringToReplaceClientNameMode(const std::string& mode_str);

    /// @brief Converts NameChangeFormat enums to text labels.
    ///
    /// @param mode enum value to convert to label
    ///
    /// @return std:string containing the text label if the value is valid, or
    /// "unknown" if not.
    static std::string replaceClientNameModeToString(const ReplaceClientNameMode& mode);

    /// @brief Unparse a configuration object
    ///
    /// @return a pointer to unparsed configuration
    virtual isc::data::ElementPtr toElement() const;

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

    /// @brief Maximum number of NCRs allowed to queue waiting to send
    size_t max_queue_size_;

    /// @brief The socket protocol to use with kea-dhcp-ddns.
    /// Currently only UDP is supported.
    dhcp_ddns::NameChangeProtocol ncr_protocol_;

    /// @brief Format of the kea-dhcp-ddns requests.
    /// Currently only JSON format is supported.
    dhcp_ddns::NameChangeFormat ncr_format_;
};

std::ostream&
operator<<(std::ostream& os, const D2ClientConfig& config);

/// @brief Defines a pointer for D2ClientConfig instances.
typedef boost::shared_ptr<D2ClientConfig> D2ClientConfigPtr;

} // namespace isc
} // namespace dhcp

#endif
