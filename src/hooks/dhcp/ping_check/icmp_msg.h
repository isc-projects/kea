// Copyright (C) 2023-2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef ICMP_MSG_H
#define ICMP_MSG_H

#include <asiolink/io_address.h>

#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <unistd.h>
#include <netinet/ip_icmp.h>
#include <boost/shared_ptr.hpp>

namespace isc {
namespace ping_check {

// Forward class definition.
class ICMPMsg;

/// @brief Shared pointer type for ICMPMsg.
typedef boost::shared_ptr<ICMPMsg> ICMPMsgPtr;

/// @brief Shared pointer type for struct icmp.
typedef boost::shared_ptr<struct icmp> ICMPPtr;

/// @brief Embodies an ICMP message
///
/// Provides functions for marshalling of ICMP protocol
/// messages to and from wire form
class ICMPMsg {
public:
    /// @brief ICMP message types. We only define the ones
    /// we care about.
    enum ICMPMsgType {
        ECHO_REPLY = 0,
        TARGET_UNREACHABLE = 3,
        ECHO_REQUEST = 8
    };

    /// @brief Size in octets of ICMP message header.
    /// 1 (msg type) + 1 (code) + 2 (checksum) + 4 (either unused
    /// or used differently basing on the ICMP type and code e.g
    /// Identifier and Sequence Number for Echo or Echo Reply Message)
    constexpr static size_t ICMP_HEADER_SIZE = 8;

    /// @brief Constructor.
    ICMPMsg();

    /// @brief Destructor.
    virtual ~ICMPMsg() = default;

    /// @brief Unpacks an ICMP message from the given wire_data
    ///
    /// The wire data is expected to include the IP header followed
    /// by an ICMP message.
    ///
    /// @param wire_data raw data received from the socket
    /// @param length number of bytes in the wire_data contents
    ///
    /// @return Pointer to the newly constructed message
    /// @throw BadValue if the wire data is invalid
    static ICMPMsgPtr unpack(const uint8_t* wire_data, size_t length);

    /// @brief Packs the message into an ICMP structure.
    ///
    /// @return Pointer to the newly constructed ICMP structure.
    ICMPPtr pack() const;

    /// @brief Fetches the ICMP message type (e.g. ECHO_REQUEST, ECHO_REPLY)
    ///
    /// @return message type as a uint8_t
    uint8_t getType() const {
        return (msg_type_);
    }

    /// @brief Sets the ICMP message type
    ///
    /// @param msg_type new value for the message type
    void setType(uint8_t msg_type) {
        msg_type_ = msg_type;
    }

    /// @brief Fetches the ICMP message code
    ///
    /// @return uint8_t containing the message code
    uint8_t getCode() const {
        return (code_);
    }

    /// @brief Sets the ICMP code
    ///
    /// @param code new value for the message type
    void setCode(uint8_t code) {
        code_ = code;
    }

    /// @brief Fetches the checksum
    ///
    /// @return uint16_t containing the message checksum
    uint16_t getChecksum() const {
        return (check_sum_);
    }

    /// @brief Sets the check sum
    ///
    /// @param check_sum new value for the check sum
    void setChecksum(uint16_t check_sum) {
        check_sum_ = check_sum;
    }

    /// @brief Fetches the message id
    ///
    /// @return uint16_t containing the id
    uint16_t getId() const {
        return (id_);
    }

    /// @brief Sets the message id
    ///
    /// @param id new value for the message id
    void setId(const uint16_t id) {
        id_ = id;
    }

    /// @brief Fetches the message sequence number
    ///
    /// @return uint16_t containing the sequence number
    uint16_t getSequence() const {
        return (sequence_);
    }

    /// @brief Sets the message sequence number
    ///
    /// @param sequence new value for the message sequence number
    void setSequence(uint16_t sequence) {
        sequence_ = sequence;
    }

    /// @brief Fetches the source IP address
    ///
    /// @return IOAddress containing the IP address of the message source
    const isc::asiolink::IOAddress& getSource() const {
        return (source_);
    }

    /// @brief Sets the source IP address
    ///
    /// @param source new value for the source IP address
    void setSource(const isc::asiolink::IOAddress& source) {
        source_ = source;
    }

    /// @brief Fetches the destination IP address
    ///
    /// @return IOAddress containing the IP address of the message destination
    const isc::asiolink::IOAddress& getDestination() const {
        return (destination_);
    }

    /// @brief Sets the destination IP address
    ///
    /// @param destination new value for the destination IP address
    void setDestination(const isc::asiolink::IOAddress& destination) {
        destination_ = destination;
    }

    /// @brief Fetches the message payload
    ///
    /// @return vector containing the message payload
    const std::vector<uint8_t>& getPayload() const {
        return (payload_);
    }

    /// @brief Sets the message payload to the given data
    ///
    /// @param data pointer to data buffer from which to copy
    /// @param length number of bytes in data buffer
    void setPayload(const uint8_t* data, size_t length);

    /// @brief Calculates the checksum of the given data buffer
    ///
    /// @param data pointer to data buffer from which to copy
    /// @param length number of bytes in data buffer
    ///
    /// @return uint32_t containing the calculated checksum
    static uint32_t calcChecksum(const uint8_t* data, size_t length);

private:
    /// @brief IP address from which the message origin
    isc::asiolink::IOAddress source_;

    /// @brief IP address of the message destination
    isc::asiolink::IOAddress destination_;

    /// @brief ICMP message type
    uint8_t msg_type_;

    /// @brief ICMP message code
    uint8_t code_;

    /// @brief Checksum of the message
    uint16_t check_sum_;

    /// @brief Message ID
    uint16_t id_;

    /// @brief Message sequence number
    uint16_t sequence_;

    // data beyond the ICMP header
    std::vector<uint8_t> payload_;
};


} // end of namespace ping_check
} // end of namespace isc

#endif
