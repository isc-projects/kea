// Copyright (C) 2023-2026 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef RADIUS_CLIENT_MESSAGE_H
#define RADIUS_CLIENT_MESSAGE_H

#include <client_attribute.h>
#include <exceptions/exceptions.h>
#include <asiolink/io_address.h>
#include <tcp/wire_data.h>
#include <string>
#include <vector>

namespace isc {
namespace radius {

/// @brief Standard RADIUS message code.
enum MsgCode : uint8_t {
    PW_ACCESS_REQUEST              = 1,
    PW_ACCESS_ACCEPT               = 2,
    PW_ACCESS_REJECT               = 3,
    PW_ACCOUNTING_REQUEST          = 4,
    PW_ACCOUNTING_RESPONSE         = 5,
    PW_ACCOUNTING_STATUS           = 6,
    PW_PASSWORD_REQUEST            = 7,
    PW_PASSWORD_ACK                = 8,
    PW_PASSWORD_REJECT             = 9,
    PW_ACCOUNTING_MESSAGE          = 10,
    PW_ACCESS_CHALLENGE            = 11,
    PW_STATUS_SERVER               = 12,
    PW_STATUS_CLIENT               = 13
};

/// @brief MsgCode value -> name function.
///
/// @param code code to translate to name.
/// @return the name of the code.
std::string msgCodeToText(const uint8_t code);

/// @brief Message header size.
static constexpr size_t AUTH_HDR_LEN = 20;

/// @brief Message maximal size.
static constexpr size_t PW_MAX_MSG_SIZE = 4095;

/// @brief Message authenticator (aka vector) size.
static constexpr size_t AUTH_VECTOR_LEN = 16;

/// @brief Message maximal hidden user password size.
static constexpr size_t AUTH_PASS_LEN = 128;

/// @brief RADIUS Message.
class Message {
public:
    /// @brief Build a zero authenticator.
    ///
    /// @return an authenticator filled with 0.
    static const std::vector<uint8_t> ZERO_AUTH() {
        static std::vector<uint8_t> zero(AUTH_VECTOR_LEN, 0);
        return (zero);
    }

    /// @brief Constructor.
    ///
    /// To be used to send a  message.
    ///
    /// @brief code message code.
    /// @brief length message length (0 to be computed).
    /// @brief auth authenticator (16 octets).
    /// @brief secret associated secret (not empty).
    /// @brief attributes attributes.
    Message(const uint8_t code, uint16_t length,
            const std::vector<uint8_t>& auth,
            const std::string& secret,
            const AttributesPtr& attributes);

    /// @brief Copy constructor.
    ///
    /// Copy attributes.
    ///
    /// @brief other message to copy.
    Message(const Message& other);

    /// @brief Constructor.
    ///
    /// To be used on message reception.
    ///
    /// @param buffer buffer containing the message.
    /// @param auth authenticator (16 octets).
    /// @param secret associated secret (not empty).
    Message(const std::vector<uint8_t>& buffer,
            const std::vector<uint8_t>& auth,
            const std::string& secret);

    /// @brief Destructor.
    ///
    /// Destroy the secret.
    virtual ~Message();

    /// @brief Get code.
    ///
    /// @return code.
    uint8_t getCode() const {
        return (code_);
    }

    /// @brief Set code.
    ///
    /// @param code new code.
    void setCode(const uint8_t code) {
        code_ = code;
    }

    /// @brief Get identifier.
    ///
    /// @return identifier.
    uint8_t getIdentifier() const {
        return(identifier_);
    }

    /// @brief Set identifier.
    ///
    /// @param identifier new identifier.
    void setIdentifier(const uint8_t identifier) {
        identifier_ = identifier;
    }

    /// @brief Randomize identifier.
    void randomIdentifier();

    /// @brief Get length.
    ///
    /// @return length (field value).
    uint16_t getLength() const {
        return (length_);
    }

    /// @brief Set length.
    ///
    /// @param length new length.
    void setLength(const uint16_t length) {
        length_ = length;
    }

    /// @brief Get authenticator.
    ///
    /// @return authenticator.
    std::vector<uint8_t> getAuth() const {
        return (auth_);
    }

    /// @brief Set authenticator.
    ///
    /// @param auth new authenticator (must have 16 octets).
    void setAuth(const std::vector<uint8_t>& auth);

    /// @brief Fill authenticator with 0.
    void zeroAuth();

    /// @brief Randomize authenticator.
    void randomAuth();

    /// @brief Get secret.
    ///
    /// @return secret.
    std::string getSecret() const {
        return (secret_);
    }
    /// @brief Set secret.
    ///
    /// @param secret new secret (not empty).
    void setSecret(const std::string& secret);

    /// @brief Get attributes.
    ///
    /// @return attributes.
    AttributesPtr getAttributes() const {
        return (attributes_);
    }

    /// @brief Set attributes.
    ///
    /// @param attributes new attributes.
    void setAttributes(const AttributesPtr& attributes) {
        attributes_ = attributes;
    }

    /// @brief Get buffer.
    ///
    /// @return message content.
    std::vector<uint8_t> getBuffer() const {
        return (buffer_);
    }

    /// @brief Set buffer.
    ///
    /// @param buffer new message content.
    void setBuffer(const std::vector<uint8_t>& buffer) {
        buffer_ = buffer;
    }

    /// @brief Encode a message.
    ///
    /// @return the buffer with the message.
    /// @throw an exception when something goes wrong.
    std::vector<uint8_t> encode();

    /// @brief Decode a message.
    ///
    /// @throw an exception when something goes wrong.
    void decode();

protected:
    /// @brief Encode User-Password in an Access-Request.
    ///
    /// @param attr the User-Password attribute.
    /// @return encoded User-Password attribute.
    ConstAttributePtr encodeUserPassword(const ConstAttributePtr& attr);

    /// @brief Decode User-Password in an Access-Request.
    ///
    /// @param attr the User-Password attribute.
    /// @return decoded User-Password attribute.
    ConstAttributePtr decodeUserPassword(const ConstAttributePtr& attr);

    /// @brief Encode Message-Authenticator in an Status-Server.
    ///
    /// @param ptr the pointer to the attribute in the buffer.
    void signMessageAuthenticator(size_t ptr);

    /// @brief Decode Message-Authenticator in an Status-Server.
    ///
    /// @param ptr the pointer to the attribute in the buffer.
    void verifyMessageAuthenticator(size_t ptr);

    /// @brief Code (useful values in MsgCode): header[0].
    uint8_t code_;

    /// @brief Identifier (random): header[1].
    uint8_t identifier_;

    /// @brief Length: header[2] (16 bits, network order).
    uint16_t length_;

    /// @brief Authenticator: header[4] (16 octets).
    std::vector<uint8_t> auth_;

    /// @brief Secret (not empty).
    std::string secret_;

    /// @brief Attributes: header[20]...
    AttributesPtr attributes_;

    /// @brief Buffer (message content).
    std::vector<uint8_t> buffer_;
};

/// @brief Shared pointers to message.
typedef boost::shared_ptr<Message> MessagePtr;

} // end of namespace isc::radius
} // end of namespace isc

#endif
