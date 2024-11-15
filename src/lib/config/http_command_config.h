// Copyright (C) 2024 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef HTTP_COMMAND_CONFIG_H
#define HTTP_COMMAND_CONFIG_H

#include <asiolink/io_address.h>
#include <cc/cfg_to_element.h>
#include <cc/user_context.h>
#include <http/auth_config.h>
#include <http/cfg_http_header.h>

namespace isc {
namespace config {

/// @brief HTTP command config aka HTTP control socket info class.
class HttpCommandConfig : public isc::data::UserContext,
                          public isc::data::CfgToElement {
public:
    /// @brief Constructor.
    ///
    /// @param config Pointer to the configuration to parse.
    HttpCommandConfig(isc::data::ConstElementPtr config);

    /// @brief Virtual destructor.
    ~HttpCommandConfig() = default;

    /// @brief Returns socket type.
    ///
    /// @return The socket type ("http" or "https").
    std::string getSocketType() const {
        return (socket_type_);
    }

    /// @brief Sets socket type.
    ///
    /// @param socket_type The new socket type (should be "http" or "https").
    void setSocketType(const std::string& socket_type) {
        socket_type_ = socket_type;
    }

    /// @brief Returns socket address.
    ///
    /// @return IP address where the HTTP service is available.
    isc::asiolink::IOAddress getSocketAddress() const {
        return (socket_address_);
    }

    /// @brief Sets socket address.
    ///
    /// @param socket_address The new socket address.
    void setSocketAddress(const isc::asiolink::IOAddress& socket_address) {
        socket_address_ = socket_address;
    }

    /// @brief Returns socket port.
    ///
    /// @return TCP port where the HTTP service is available.
    uint16_t getSocketPort() const {
        return (socket_port_);
    }

    /// @brief Sets socket port.
    ///
    /// @param socket_port The new socket port.
    void setSocketPort(const uint16_t socket_port) {
        socket_port_ = socket_port;
    }

    /// @brief Returns http-headers configuration.
    ///
    /// @return Collection of config HTTP headers.
    const isc::http::CfgHttpHeaders& getHttpHeaders() const {
        return (http_headers_);
    }

    /// @brief Sets http-headers configuration.
    ///
    /// @param headers Collection of config HTTP headers.
    void setHttpHeaders(const isc::http::CfgHttpHeaders& headers) {
        http_headers_ = headers;
    }

    /// @brief Returns HTTP authentication configuration.
    ///
    /// @note Only the basic HTTP authentication is supported.
    ///
    /// @return HTTP authentication configuration.
    const isc::http::HttpAuthConfigPtr& getAuthConfig() const {
        return (auth_config_);
    }

    /// @brief Sets HTTP authentication configuration.
    ///
    /// @note Only the basic HTTP authentication is supported.
    ///
    /// @param auth_config HTTP authentication configuration.
    void setAuthConfig(const isc::http::HttpAuthConfigPtr& auth_config) {
        auth_config_ = auth_config;
    }

    /// @brief Returns trust-anchor TLS parameter.
    ///
    /// @return Trust anchor aka Certificate Authority.
    std::string getTrustAnchor() const {
        return (trust_anchor_);
    }

    /// @brief Sets trust-anchor TLS parameter.
    ///
    /// @param ca Trust anchor aka Certificate Authority (can be a file name
    /// or a directory path).
    void setTrustAnchor(const std::string& ca) {
        trust_anchor_ = ca;
    }

    /// @brief Returns cert-file TLS parameter.
    ///
    /// @return Server certificate file name.
    std::string getCertFile() const {
        return (cert_file_);
    }

    /// @brief Sets cert-file TLS parameter.
    ///
    /// @param cert Server certificate file name.
    void setCertFile(const std::string& cert) {
        cert_file_ = cert;
    }

    /// @brief Returns key-file TLS parameter.
    ///
    /// @return Server private key file name.
    std::string getKeyFile() const {
        return (key_file_);
    }

    /// @brief Sets key-file TLS parameter.
    ///
    /// @param key Server private key file name.
    void setKeyFile(const std::string& key) {
        key_file_ = key;
    }

    /// @brief Returns cert-required TLS parameter.
    ///
    /// @return True when client certificates are required, false when they
    /// are optional, the default is to require them (true).
    bool getCertRequired() const {
        return (cert_required_);
    }

    /// @brief Sets cert-required TLS parameter.
    ///
    /// @param required Client certificates are required when true
    /// (the default) or optional when false.
    void setCertRequired(bool required) {
        cert_required_ = required;
    }

    /// @brief Returns emulate agent response flag.
    ///
    /// @return True when responses for normal command outcomes are
    /// guaranteed to be wrapped in an Element::list. This emulates
    /// how kea-ctrl-agent forms responses. Defaults to true.
    bool getEmulateAgentResponse() const {
        return (emulate_agent_response_);
    }

    /// @brief Sets emulate agent response flag.
    ///
    /// @param emulate_agent_response The new value of the emulation flag.
    void setEmulateAgentResponse(const bool emulate_agent_response) {
        emulate_agent_response_ = emulate_agent_response;
    }

    /// @brief Unparse a configuration object.
    ///
    /// @return A pointer to configuration.
    virtual isc::data::ElementPtr toElement() const;

    /// @brief Default socket address (127.0.0.1).
    static isc::asiolink::IOAddress DEFAULT_SOCKET_ADDRESS;

    /// @brief Default socket port.
    static uint16_t DEFAULT_SOCKET_PORT;

    /// @brief Default HTTP authentication realm.
    static std::string DEFAULT_AUTHENTICATION_REALM;

private:
    /// @brief Check TLS configuration.
    ///
    /// @param require_tls When true TLS is required.
    void checkTlsSetup(bool require_tls) const;

    /// @brief Socket type ("http" or "https").
    std::string socket_type_;

    /// @brief Socket address.
    isc::asiolink::IOAddress socket_address_;

    /// @brief Socket port.
    uint16_t socket_port_;

    /// Config HTTP headers.
    isc::http::CfgHttpHeaders http_headers_;

    /// @brief HTTP authentication configuration.
    isc::http::HttpAuthConfigPtr auth_config_;

    /// @brief Trust anchor aka Certificate Authority.
    std::string trust_anchor_;

    /// @brief Server certificate file name.
    std::string cert_file_;

    /// @brief Server private key file name.
    std::string key_file_;

    /// @brief Require client certificates flag.
    bool cert_required_;

    /// @brief Emulation flag.
    bool emulate_agent_response_;
};

/// @brief Pointer to a HttpCommandConfig object.
typedef boost::shared_ptr<HttpCommandConfig> HttpCommandConfigPtr;

} // end of isc::config namespace
} // end of isc namespace
#endif
