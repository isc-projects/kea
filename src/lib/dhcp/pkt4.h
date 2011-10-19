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

#ifndef PKT4_H
#define PKT4_H

#include <iostream>
#include <boost/shared_ptr.hpp>
#include <boost/shared_array.hpp>
#include "asiolink/io_address.h"
#include "util/buffer.h"
#include "dhcp/option.h"

namespace isc {

namespace dhcp {

class Pkt4 {
public:

    // length of the CHADDR field in DHCPv4 message
    const static size_t MAX_CHADDR_LEN = 16;

    // length of the SNAME field in DHCPv4 message
    const static size_t MAX_SNAME_LEN = 64;

    // length of the FILE field in DHCPv4 message
    const static size_t MAX_FILE_LEN = 128;

    /// specifes DHCPv4 packet header length (fixed part)
    const static size_t DHCPV4_PKT_HDR_LEN = 236;

    /// Constructor, used in replying to a message
    ///
    /// @param msg_type type of message (e.g. DHCPDISOVER=1)
    /// @param transid transaction-id
    Pkt4(uint8_t msg_type, uint32_t transid);

    /// Constructor, used in message transmission
    ///
    /// Creates new message. Transaction-id will randomized.
    ///
    /// @param data pointer to received data
    /// @param len size of buffer to be allocated for this packet.
    Pkt4(const uint8_t* data, size_t len);

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

    /// @brief Parses on-wire form of UDP DHCPv6 packet.
    ///
    /// Parses received packet, stored in on-wire format in data_.
    /// data_len_ must be set to indicate data length.
    /// Will create a collection of option objects that will
    /// be stored in options_ container.
    ///
    /// @return true, if build was successful
    bool 
    unpack();

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
    size_t
    len();

    /// Sets hops field
    ///
    /// @param hops value to be set
    void
    setHops(uint8_t hops) { hops_ = hops; };

    /// Returns hops field
    ///
    /// @return hops field
    uint8_t
    getHops() { return (hops_); };

    // Note: There's no need to manipulate OP field directly,
    // thus no setOp() method. See op_ comment.

    /// Returns op field
    ///
    /// @return op field
    uint8_t
    getOp() { return (op_); };

    /// Sets secs field
    ///
    /// @param secs value to be set
    void
    setSecs(uint16_t secs) { secs_ = secs; };

    /// Returns secs field
    ///
    /// @return secs field
    uint16_t
    getSecs() { return (secs_); };

    /// Sets flags field
    ///
    /// @param flags value to be set
    void
    setFlags(uint16_t flags) { flags_ = flags; };

    /// Returns flags field
    ///
    /// @return flags field
    uint16_t
    getFlags() { return (flags_); };


    /// Returns ciaddr field
    ///
    /// @return ciaddr field
    isc::asiolink::IOAddress&
    getCiaddr() { return (ciaddr_); };

    /// Sets ciaddr field
    ///
    /// @param ciaddr value to be set
    void
    setCiaddr(const isc::asiolink::IOAddress& ciaddr) { ciaddr_ = ciaddr; };


    /// Returns siaddr field
    ///
    /// @return siaddr field
    isc::asiolink::IOAddress&
    getSiaddr() { return (siaddr_); };

    /// Sets siaddr field
    ///
    /// @param siaddr value to be set
    void
    setSiaddr(const isc::asiolink::IOAddress& siaddr) { siaddr_ = siaddr; };


    /// Returns yiaddr field
    ///
    /// @return yiaddr field
    isc::asiolink::IOAddress&
    getYiaddr() { return (yiaddr_); };

    /// Sets yiaddr field
    ///
    /// @param yiaddr value to be set
    void
    setYiaddr(const isc::asiolink::IOAddress& yiaddr) { yiaddr_ = yiaddr; };


    /// Returns giaddr field
    ///
    /// @return giaddr field
    isc::asiolink::IOAddress&
    getGiaddr() { return (giaddr_); };

    /// Sets giaddr field
    ///
    /// @param giaddr value to be set
    void
    setGiaddr(const isc::asiolink::IOAddress& giaddr) { giaddr_ = giaddr; };

    /// Returns value of transaction-id field
    ///
    /// @return transaction-id
    uint32_t getTransid() { return (transid_); };

    /// Returns message type (e.g. 1 = DHCPDISCOVER)
    ///
    /// @return message type
    uint8_t
    getType() { return (msg_type_); }

    /// Sets message type (e.g. 1 = DHCPDISCOVER)
    ///
    /// @param type message type to be set
    void setType(uint8_t type) { msg_type_=type; };

    /// @brief Returns sname field
    ///
    /// Note: This is 64 bytes long field. It doesn't have to be
    /// null-terminated. Do no use strlen() or similar on it.
    ///
    /// @return sname field
    const uint8_t*
    getSname() { return (sname_); };

    /// Sets sname field
    ///
    /// @param sname value to be set
    void
    setSname(const uint8_t* sname, size_t snameLen = MAX_SNAME_LEN);

    /// @brief Returns file field
    ///
    /// Note: This is 128 bytes long field. It doesn't have to be
    /// null-terminated. Do no use strlen() or similar on it.
    ///
    /// @return pointer to file field
    const uint8_t*
    getFile() { return (file_); };

    /// Sets file field
    ///
    /// @param file value to be set
    void
    setFile(const uint8_t* file, size_t fileLen = MAX_FILE_LEN);

    /// Sets hardware address
    ///
    /// @param hwType hardware type (will be sent in htype field)
    /// @param hlen hardware length (will be sent in hlen field)
    /// @param macAddr pointer to hardware address
    void setHWAddr(uint8_t hType, uint8_t hlen,
                   const uint8_t* macAddr);

    /// Returns htype field
    ///
    /// @return hardware type
    uint8_t
    getHtype() { return (htype_); };

    /// Returns hlen field
    ///
    /// @return hardware address length
    uint8_t
    getHlen() { return (hlen_); };

    /// @brief Returns chaddr field
    ///
    /// Note: This is 16 bytes long field. It doesn't have to be
    /// null-terminated. Do no use strlen() or similar on it.
    ///
    /// @return pointer to hardware address
    const uint8_t*
    getChaddr() { return (chaddr_); };


protected:

    /// converts DHCP message type to BOOTP op type
    ///
    /// @param dhcpType DHCP message type (e.g. DHCPDISCOVER)
    ///
    /// @return BOOTP type (BOOTREQUEST or BOOTREPLY)
    uint8_t
    DHCPTypeToBootpType(uint8_t dhcpType);

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

    /// local UDP port
    int local_port_;

    /// remote UDP port
    int remote_port_;

    /// message operation code (kept due to BOOTP format, this is NOT DHCPv4 type)
    ///
    /// Note: This is legacy BOOTP field. There's no need to manipulate it 
    /// directly. Its value is set based on DHCP message type.
    uint8_t op_;

    /// link-layer address type
    uint8_t htype_;

    /// link-layer address length
    uint8_t hlen_;

    /// Number of relay agents traversed
    uint8_t hops_;

    /// DHCPv4 transaction-id (32 bits, not 24 bits as in DHCPv6)
    uint32_t transid_;

    /// elapsed (number of seconds since beginning of transmission)
    uint16_t secs_;

    /// flags
    uint16_t flags_;

    // ciaddr field (32 bits): Client's IP address
    isc::asiolink::IOAddress ciaddr_;

    // yiaddr field (32 bits): Client's IP address ("your"), set by server
    isc::asiolink::IOAddress yiaddr_;

    // siaddr field (32 bits): next server IP address in boot process(e.g.TFTP)
    isc::asiolink::IOAddress siaddr_;

    // giaddr field (32 bits): Gateway IP address
    isc::asiolink::IOAddress giaddr_;

    // ciaddr field (32 bits): Client's IP address
    uint8_t chaddr_[16]; 
    
    // sname 64 bytes
    uint8_t sname_[64];

    // file
    uint8_t file_[128];

    // end of real DHCPv4 fields

    /// input buffer (used during message reception)
    /// Note that it must be modifiable as hooks can modify incoming buffer),
    /// thus OutputBuffer, not InputBuffer
    isc::util::OutputBuffer bufferIn_;

    /// output buffer (used during message 
    isc::util::OutputBuffer bufferOut_;

    /// message type (e.g. 1=DHCPDISCOVER)
    /// TODO: this will eventually be replaced with DHCP Message Type 
    /// option (option 53)
    uint8_t msg_type_;

    /// collection of options present in this message
    isc::dhcp::Option::Option4Collection options_;
}; // Pkt4 class

} // isc::dhcp namespace

} // isc namespace

#endif
