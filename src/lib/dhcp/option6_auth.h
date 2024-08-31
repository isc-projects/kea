// Copyright (C) 2018-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef OPTION6_AUTH_H
#define OPTION6_AUTH_H
#endif

#include <dhcp/option.h>
#include <boost/shared_ptr.hpp>

#include <vector>

namespace isc {
namespace dhcp {

class Option6Auth;

/// A pointer to the @c isc::dhcp::Option6Auth object.
typedef boost::shared_ptr<Option6Auth> Option6AuthPtr;

/// @brief This class represents Authentication (11) DHCPv6 option.
///
/// For details, see RFC 8415 Section 21.11.
class Option6Auth: public Option {

public:
    static const uint8_t OPTION6_AUTH_MIN_LEN  = 11;
    static const uint8_t OPTION6_HASH_MSG_LEN  = 16;
    static const uint8_t OPTION6_HDR = 4;
    /// @brief Constructor, used for auth options while transmitting
    ///
    /// @param proto protocol type
    /// @param algo algorithm type
    /// @param method remote detection method
    /// @param rdm replay detection value
    /// @param info authentication info.
    Option6Auth(const uint8_t proto, const uint8_t algo, const uint8_t method,
                const uint64_t rdm, const std::vector<uint8_t>& info);

    /// @brief Copies this option and returns a pointer to the copy.
    virtual OptionPtr clone() const;

    /// Writes option in wire-format to buf, returns pointer to first unused
    /// byte after stored option.
    ///
    /// @param buf buffer (option will be stored here)
    /// @param check if set to false, allows options larger than 255 for v4
    void pack(isc::util::OutputBuffer& buf, bool check = true) const;

    /// Writes option in wire-format to buf, for computing hash
    /// auth info filled with 0 for a length of 128 bits
    /// returns with pointer to first unused
    /// byte after stored option.
    ///
    /// @param buf buffer (option will be stored here)
    void packHashInput(isc::util::OutputBuffer& buf) const;

    /// @brief Parses received buffer
    ///
    /// Parses received buffer and returns offset to the first unused byte after
    /// parsed option.
    ///
    /// @param begin iterator to first byte of option data
    /// @param end iterator to end of option data (first byte after option end)
    virtual void unpack(OptionBufferConstIter begin, OptionBufferConstIter end);

    /// Provides human readable text representation
    ///
    /// @param indent number of leading space characters
    ///
    /// @return string with text representation
    virtual std::string toText(int indent = 0) const;

    /// Set protocol type
    ///
    /// @param proto protocol type to be set
    void setProtocol(uint8_t proto) { protocol_ = proto; }

    /// Set hash algorithm type
    ///
    /// @param algo hash algorithm type to be set
    void setHashAlgo(uint8_t algo) { algorithm_ = algo; }

    /// Set replay detection method type
    ///
    /// @param method replay detection method to be set
    void setReplyDetectionMethod(uint8_t method) { rdm_method_ = method; }

    /// Set replay detection method value
    ///
    /// @param value replay detection method value to be set
    void setReplyDetectionValue(uint64_t value) { rdm_value_ = value; }

    /// Set authentication information
    ///
    /// @param auth_info authentication information to be set
    void setAuthInfo(const std::vector<uint8_t>& auth_info) { auth_info_ = auth_info; }

    /// Returns protocol type
    ///
    /// @return protocol value
    uint8_t getProtocol() const { return protocol_; }

    /// Returns hash algorithm type
    ///
    /// @return hash algorithm value
    uint8_t getHashAlgo() const { return algorithm_; }

    /// Returns replay detection method type
    ///
    /// @return replay detection method type value
    uint8_t getReplyDetectionMethod() const { return rdm_method_; }

    /// Return replay detection mechanism
    ///
    /// @return replay detection method value
    uint64_t getReplyDetectionValue() const { return rdm_value_; }

    /// Return authentication information
    ///
    /// @return authentication information value
    std::vector<uint8_t> getAuthInfo() const { return auth_info_; }

protected:
    /// keeps protocol type
    uint8_t protocol_;

    /// keeps hash algorithm value
    uint8_t algorithm_;

    /// keeps replay detection method type
    uint8_t rdm_method_;

    /// keeps replay detection method value
    uint64_t rdm_value_;

    /// keeps authentication information
    std::vector<uint8_t> auth_info_;
};

} // isc::dhcp namespace
} // isc namespace
