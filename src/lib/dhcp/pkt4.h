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
#include <vector>
#include <boost/shared_ptr.hpp>
#include <boost/shared_array.hpp>
#include "asiolink/io_address.h"
#include "util/buffer.h"
#include "dhcp/option.h"

namespace isc {

namespace dhcp {

class Pkt4 {
public:

    /// length of the CHADDR field in DHCPv4 message
    const static size_t MAX_CHADDR_LEN = 16;

    /// length of the SNAME field in DHCPv4 message
    const static size_t MAX_SNAME_LEN = 64;

    /// length of the FILE field in DHCPv4 message
    const static size_t MAX_FILE_LEN = 128;

    /// specifies DHCPv4 packet header length (fixed part)
    const static size_t DHCPV4_PKT_HDR_LEN = 236;

    /// Constructor, used in replying to a message.
    ///
    /// @param msg_type type of message (e.g. DHCPDISOVER=1)
    /// @param transid transaction-id
    Pkt4(uint8_t msg_type, uint32_t transid);

    /// @brief Constructor, used in message reception.
    ///
    /// Creates new message. Pkt4 will copy data to bufferIn_
    /// buffer on creation.
    ///
    /// @param data pointer to received data
    /// @param len size of buffer to be allocated for this packet.
    Pkt4(const uint8_t* data, size_t len);

    /// @brief Prepares on-wire format of DHCPv4 packet.
    ///
    /// Prepares on-wire format of message and all its options.
    /// Options must be stored in options_ field.
    /// Output buffer will be stored in bufferOut_.
    ///
    /// @return true if packing procedure was successful
    bool
    pack();

    /// @brief Parses on-wire form of DHCPv4 packet.
    ///
    /// Parses received packet, stored in on-wire format in bufferIn_.
    ///
    /// Will create a collection of option objects that will
    /// be stored in options_ container.
    ///
    /// @return true, if parsing was successful
    bool
    unpack();

    /// @brief Returns text representation of the packet.
    ///
    /// This function is useful mainly for debugging.
    ///
    /// @return string with text representation
    std::string
    toText();

    /// @brief Returns the size of the required buffer to build the packet.
    ///
    /// Returns the size of the required buffer to build the packet with
    /// the current set of packet options.
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
    /// null-terminated. Do not use strlen() or similar on it.
    ///
    /// @return sname field
    const std::vector<uint8_t>
    getSname() { return (std::vector<uint8_t>(sname_, &sname_[MAX_SNAME_LEN])); };

    /// Sets sname field
    ///
    /// @param sname value to be set
    void
    setSname(const uint8_t* sname, size_t snameLen = MAX_SNAME_LEN);

    /// @brief Returns file field
    ///
    /// Note: This is 128 bytes long field. It doesn't have to be
    /// null-terminated. Do not use strlen() or similar on it.
    ///
    /// @return pointer to file field
    const std::vector<uint8_t>
    getFile() { return (std::vector<uint8_t>(file_, &file_[MAX_FILE_LEN])); };

    /// Sets file field
    ///
    /// @param file value to be set
    void
    setFile(const uint8_t* file, size_t fileLen = MAX_FILE_LEN);

    /// @brief Sets hardware address.
    ///
    /// Sets parameters of hardware address. hlen specifies
    /// length of macAddr buffer. Content of macAddr buffer
    /// will be copied to appropriate field.
    ///
    /// Note: macAddr must be a buffer of at least hlen bytes.
    ///
    /// @param hwType hardware type (will be sent in htype field)
    /// @param hlen hardware length (will be sent in hlen field)
    /// @param macAddr pointer to hardware address
    void setHWAddr(uint8_t hType, uint8_t hlen,
                   const std::vector<uint8_t>& macAddr);

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

    /// @brief Returns chaddr field.
    ///
    /// Note: This is 16 bytes long field. It doesn't have to be
    /// null-terminated. Do no use strlen() or similar on it.
    ///
    /// @return pointer to hardware address
    const uint8_t*
    getChaddr() { return (chaddr_); };


    /// @brief Returns reference to output buffer.
    ///
    /// Returned buffer will contain reasonable data only for
    /// output (TX) packet and after pack() was called.
    ///
    /// RX packet or TX packet before pack() will return buffer with
    /// zero length
    ///
    /// @return reference to output buffer
    isc::util::OutputBuffer&
    getBuffer() { return (bufferOut_); };

    /// @brief Add an option.
    ///
    /// Throws BadValue if option with that type is already present.
    ///
    /// @param opt option to be added
    void
    addOption(boost::shared_ptr<Option> opt);

    /// @brief Returns an option of specified type.
    ///
    /// @return returns option of requested type (or NULL)
    ///         if no such option is present

    boost::shared_ptr<Option>
    getOption(uint8_t opt_type);

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
    /// Each network interface has assigned unique ifindex. It is functional
    /// equvalent of name, but sometimes more useful, e.g. when using crazy
    /// systems that allow spaces in interface names e.g. MS Windows)
    int ifindex_;

    /// local UDP port
    int local_port_;

    /// remote UDP port
    int remote_port_;

    /// @brief message operation code
    ///
    /// Note: This is legacy BOOTP field. There's no need to manipulate it
    /// directly. Its value is set based on DHCP message type. Note that
    /// DHCPv4 protocol reuses BOOTP message format, so this field is
    /// kept due to BOOTP format. This is NOT DHCPv4 type (DHCPv4 message
    /// type is kept in message type option).
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

    /// ciaddr field (32 bits): Client's IP address
    isc::asiolink::IOAddress ciaddr_;

    /// yiaddr field (32 bits): Client's IP address ("your"), set by server
    isc::asiolink::IOAddress yiaddr_;

    /// siaddr field (32 bits): next server IP address in boot process(e.g.TFTP)
    isc::asiolink::IOAddress siaddr_;

    /// giaddr field (32 bits): Gateway IP address
    isc::asiolink::IOAddress giaddr_;

    /// Hardware address field (16 bytes)
    uint8_t chaddr_[MAX_CHADDR_LEN];

    /// sname field (64 bytes)
    uint8_t sname_[MAX_SNAME_LEN];

    /// file field (128 bytes)
    uint8_t file_[MAX_FILE_LEN];

    // end of real DHCPv4 fields

    /// input buffer (used during message reception)
    /// Note that it must be modifiable as hooks can modify incoming buffer),
    /// thus OutputBuffer, not InputBuffer
    isc::util::InputBuffer bufferIn_;

    /// output buffer (used during message
    isc::util::OutputBuffer bufferOut_;

    /// message type (e.g. 1=DHCPDISCOVER)
    /// TODO: this will eventually be replaced with DHCP Message Type
    /// option (option 53)
    uint8_t msg_type_;

    /// collection of options present in this message
    isc::dhcp::Option::Option6Collection options_;
}; // Pkt4 class

} // isc::dhcp namespace

} // isc namespace

#endif
