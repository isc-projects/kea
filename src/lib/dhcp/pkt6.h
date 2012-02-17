// Copyright (C) 2011-2012 Internet Systems Consortium, Inc. ("ISC")
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
    /// @param buf pointer to a buffer of received packet content
    /// @param len size of buffer of received packet content
    /// @param proto protocol (usually UDP, but TCP will be supported eventually)
    Pkt6(const uint8_t* buf, uint32_t len, DHCPv6Proto proto = UDP);

    /// @brief Prepares on-wire format.
    ///
    /// Prepares on-wire format of message and all its options.
    /// Options must be stored in options_ field.
    /// Output buffer will be stored in data_. Length
    /// will be set in data_len_.
    ///
    /// @return true if packing procedure was successful
    bool pack();

    /// @brief Dispatch method that handles binary packet parsing.
    ///
    /// This method calls appropriate dispatch function (unpackUDP or
    /// unpackTCP).
    ///
    /// @return true if parsing was successful
    bool unpack();

    /// @brief Returns reference to output buffer.
    ///
    /// Returned buffer will contain reasonable data only for
    /// output (TX) packet and after pack() was called. This buffer
    /// is only valid till Pkt6 object is valid.
    ///
    /// RX packet or TX packet before pack() will return buffer with
    /// zero length
    ///
    /// @return reference to output buffer
    const isc::util::OutputBuffer& getBuffer() const { return (bufferOut_); };


    /// @brief Returns reference to input buffer.
    ///
    /// @return reference to input buffer
    const OptionBuffer& getData() const { return(data_); }

    /// @brief Returns protocol of this packet (UDP or TCP).
    ///
    /// @return protocol type
    DHCPv6Proto getProto();

    /// Sets protocol of this packet.
    ///
    /// @param proto protocol (UDP or TCP)
    void setProto(DHCPv6Proto proto = UDP) { proto_ = proto; }

    /// @brief Returns text representation of the packet.
    ///
    /// This function is useful mainly for debugging.
    ///
    /// @return string with text representation
    std::string toText();

    /// @brief Returns length of the packet.
    ///
    /// This function returns size required to hold this packet.
    /// It includes DHCPv6 header and all options stored in
    /// options_ field.
    ///
    /// Note: It does not return proper length of incoming packets
    /// before they are unpacked.
    ///
    /// @return number of bytes required to assemble this packet
    uint16_t len();

    /// Returns message type (e.g. 1 = SOLICIT)
    ///
    /// @return message type
    uint8_t getType() { return (msg_type_); }

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
    void addOption(OptionPtr opt);

    /// @brief Returns the first option of specified type.
    ///
    /// Returns the first option of specified type. Note that in DHCPv6 several
    /// instances of the same option are allowed (and frequently used).
    /// See getOptions().
    ///
    /// @param type option type we are looking for
    ///
    /// @return pointer to found option (or NULL)
    OptionPtr getOption(uint16_t type);

    /// Attempts to delete first suboption of requested type
    ///
    /// @param type Type of option to be deleted.
    ///
    /// @return true if option was deleted, false if no such option existed
    bool delOption(uint16_t type);

    /// @brief This method copies data from output buffer to input buffer
    ///
    /// This is useful only in testing
    void repack();

    /// @brief Sets remote address.
    ///
    /// @param remote specifies remote address
    void setRemoteAddr(const isc::asiolink::IOAddress& remote) { remote_addr_ = remote; }

    /// @brief Returns remote address
    ///
    /// @return remote address
    const isc::asiolink::IOAddress& getRemoteAddr() { return (remote_addr_); }

    /// @brief Sets local address.
    ///
    /// @param local specifies local address
    void setLocalAddr(const isc::asiolink::IOAddress& local) { local_addr_ = local; }

    /// @brief Returns local address.
    ///
    /// @return local address
    const isc::asiolink::IOAddress& getLocalAddr() { return (local_addr_); }

    /// @brief Sets local port.
    ///
    /// @param local specifies local port
    void setLocalPort(uint16_t local) { local_port_ = local; }

    /// @brief Returns local port.
    ///
    /// @return local port
    uint16_t getLocalPort() { return (local_port_); }

    /// @brief Sets remote port.
    ///
    /// @param remote specifies remote port
    void setRemotePort(uint16_t remote) { remote_port_ = remote; }

    /// @brief Returns remote port.
    ///
    /// @return remote port
    uint16_t getRemotePort() { return (remote_port_); }

    /// @brief Sets interface index.
    ///
    /// @param ifindex specifies interface index.
    void setIndex(uint32_t ifindex) { ifindex_ = ifindex; };

    /// @brief Returns interface index.
    ///
    /// @return interface index
    uint32_t getIndex() const { return (ifindex_); };

    /// @brief Returns interface name.
    ///
    /// Returns interface name over which packet was received or is
    /// going to be transmitted.
    ///
    /// @return interface name
    std::string getIface() const { return iface_; };

    /// @brief Sets interface name.
    ///
    /// Sets interface name over which packet was received or is
    /// going to be transmitted.
    ///
    /// @return interface name
    void setIface(const std::string& iface ) { iface_ = iface; };

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
    int msg_type_;

    /// DHCPv6 transaction-id
    unsigned int transid_;

    /// unparsed data (in received packets)
    OptionBuffer data_;

    /// name of the network interface the packet was received/to be sent over
    std::string iface_;

    /// @brief interface index
    ///
    /// interface index (each network interface has assigned unique ifindex
    /// it is functional equvalent of name, but sometimes more useful, e.g.
    /// when using crazy systems that allow spaces in interface names
    /// e.g. windows
    int ifindex_;

    /// local address (dst if receiving packet, src if sending packet)
    isc::asiolink::IOAddress local_addr_;

    /// remote address (src if receiving packet, dst if sending packet)
    isc::asiolink::IOAddress remote_addr_;

    /// local TDP or UDP port
    int local_port_;

    /// remote TCP or UDP port
    int remote_port_;

    /// output buffer (used during message transmission)
    isc::util::OutputBuffer bufferOut_;

}; // Pkt6 class

typedef boost::shared_ptr<Pkt6> Pkt6Ptr;

} // isc::dhcp namespace

} // isc namespace

#endif
