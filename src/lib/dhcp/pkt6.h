// Copyright (C) 2011  Internet Systems Consortium, Inc. ("ISC")
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

#ifndef PKT6_H
#define PKT6_H

#include <iostream>
#include <boost/shared_ptr.hpp>
#include <boost/shared_array.hpp>
#include "asiolink/io_address.h"
#include "dhcp/option.h"

namespace isc {

namespace dhcp {

class Pkt6 {
public:
    /// specifes DHCPv6 packet header length
    const static size_t DHCPV6_PKT_HDR_LEN = 4;

    /// DHCPv6 transport protocol
    enum DHCPv6Proto {
        UDP = 0, // most packets are UDP
        TCP = 1  // there are TCP DHCPv6 packets (bulk leasequery, failover)
    };

    /// Constructor, used in replying to a message
    ///
    /// @param msg_type type of message (SOLICIT=1, ADVERTISE=2, ...)
    /// @param transid transaction-id
    /// @param proto protocol (TCP or UDP)
    Pkt6(uint8_t msg_type,
         uint32_t transid,
         DHCPv6Proto proto = UDP);

    /// Constructor, used in message transmission
    ///
    /// Creates new message. Transaction-id will randomized.
    ///
    /// @param len size of buffer to be allocated for this packet.
    /// @param proto protocol (usually UDP, but TCP will be supported eventually)
    Pkt6(unsigned int len, DHCPv6Proto proto = UDP);

    /// @brief Prepares on-wire format.
    ///
    /// Prepares on-wire format of message and all its options.
    /// Options must be stored in options_ field.
    /// Output buffer will be stored in data_. Length
    /// will be set in data_len_.
    ///
    /// @return true if packing procedure was successful
    bool
    pack();

    /// @brief Dispatch method that handles binary packet parsing.
    ///
    /// This method calls appropriate dispatch function (unpackUDP or
    /// unpackTCP).
    ///
    /// @return true if parsing was successful
    bool
    unpack();

    /// Returns protocol of this packet (UDP or TCP)
    ///
    /// @return protocol type
    DHCPv6Proto
    getProto();

    /// Sets protocol of this packet.
    ///
    /// @param proto protocol (UDP or TCP)
    ///
    void
    setProto(DHCPv6Proto proto = UDP) { proto_ = proto; }

    /// @brief Returns text representation of the packet.
    ///
    /// This function is useful mainly for debugging.
    ///
    /// @return string with text representation
    std::string
    toText();

    /// @brief Returns calculated length of the packet.
    ///
    /// This function returns size of required buffer to buld this packet.
    /// To use that function, options_ field must be set.
    ///
    /// @return number of bytes required to build this packet
    unsigned short
    len();

    /// Returns message type (e.g. 1 = SOLICIT)
    ///
    /// @return message type
    uint8_t
    getType() { return (msg_type_); }

    /// Sets message type (e.g. 1 = SOLICIT)
    ///
    /// @param type message type to be set
    void setType(uint8_t type) { msg_type_=type; };

    /// Returns value of transaction-id field
    ///
    /// @return transaction-id
    uint32_t getTransid() { return (transid_); };

    /// Adds an option to this packet.
    ///
    /// @param opt option to be added.
    void addOption(boost::shared_ptr<isc::dhcp::Option> opt);

    /// @brief Returns the first option of specified type.
    ///
    /// Returns the first option of specified type. Note that in DHCPv6 several
    /// instances of the same option are allowed (and frequently used).
    /// See getOptions().
    ///
    /// @param type option type we are looking for
    ///
    /// @return pointer to found option (or NULL)
    boost::shared_ptr<isc::dhcp::Option>
    getOption(uint16_t type);

    /// Attempts to delete first suboption of requested type
    ///
    /// @param type Type of option to be deleted.
    ///
    /// @return true if option was deleted, false if no such option existed
    bool
    delOption(uint16_t type);

    /// TODO need getter/setter wrappers
    ///      and hide following fields as protected

    /// buffer that holds memory. It is shared_array as options may
    /// share pointer to this buffer
    boost::shared_array<uint8_t> data_;

    /// length of the data
    unsigned int data_len_;

    /// local address (dst if receiving packet, src if sending packet)
    isc::asiolink::IOAddress local_addr_;

    /// remote address (src if receiving packet, dst if sending packet)
    isc::asiolink::IOAddress remote_addr_;

    /// name of the network interface the packet was received/to be sent over
    std::string iface_;

    /// @brief interface index
    ///
    /// interface index (each network interface has assigned unique ifindex
    /// it is functional equvalent of name, but sometimes more useful, e.g.
    /// when using crazy systems that allow spaces in interface names
    /// e.g. windows
    int ifindex_;

    /// local TDP or UDP port
    uint16_t local_port_;

    /// remote TCP or UDP port
    uint16_t remote_port_;

    /// TODO Need to implement getOptions() as well

    /// collection of options present in this message
    isc::dhcp::Option::OptionCollection options_;

protected:
    /// Builds on wire packet for TCP transmission.
    ///
    /// TODO This function is not implemented yet.
    ///
    /// @return true, if build was successful
    bool packTCP();

    /// Builds on wire packet for UDP transmission.
    ///
    /// @return true, if build was successful
    bool packUDP();

    /// @brief Parses on-wire form of TCP DHCPv6 packet.
    ///
    /// Parses received packet, stored in on-wire format in data_.
    /// data_len_ must be set to indicate data length.
    /// Will create a collection of option objects that will
    /// be stored in options_ container.
    ///
    /// TODO This function is not implemented yet.
    ///
    /// @return true, if build was successful
    bool unpackTCP();

    /// @brief Parses on-wire form of UDP DHCPv6 packet.
    ///
    /// Parses received packet, stored in on-wire format in data_.
    /// data_len_ must be set to indicate data length.
    /// Will create a collection of option objects that will
    /// be stored in options_ container.
    ///
    /// @return true, if build was successful
    bool unpackUDP();

    /// UDP (usually) or TCP (bulk leasequery or failover)
    DHCPv6Proto proto_;

    /// DHCPv6 message type
    uint8_t msg_type_;

    /// DHCPv6 transaction-id
    uint32_t transid_;
}; // Pkt6 class

} // isc::dhcp namespace

} // isc namespace

#endif
