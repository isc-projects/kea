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

#ifndef PKT4_H
#define PKT4_H

#include <asiolink/io_address.h>
#include <util/buffer.h>
#include <dhcp/option.h>

#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/shared_ptr.hpp>

#include <iostream>
#include <vector>

#include <time.h>

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
    /// Method with throw exception if packet parsing fails.
    void unpack();

    /// @brief performs sanity check on a packet.
    ///
    /// This is usually performed after unpack(). It checks if packet is sane:
    /// required options are present, fields have sane content etc.
    /// For example verifies that DHCP_MESSAGE_TYPE is present and have
    /// reasonable value. This method is expected to grow significantly.
    /// It makes sense to separate unpack() and check() for testing purposes.
    ///
    /// @todo It is called from unpack() directly. It should be separated.
    ///
    /// Method will throw exception if anomaly is found.
    void check();

    /// @brief Copies content of input buffer to output buffer.
    ///
    /// This is mostly a diagnostic function. It is being used for sending
    /// received packet. Received packet is stored in bufferIn_, but
    /// transmitted data is stored in bufferOut_. If we want to send packet
    /// that we just received, a copy between those two buffers is necessary.
    void repack();

    /// @brief Returns text representation of the packet.
    ///
    /// This function is useful mainly for debugging.
    ///
    /// @return string with text representation
    std::string toText();

    /// @brief Returns the size of the required buffer to build the packet.
    ///
    /// Returns the size of the required buffer to build the packet with
    /// the current set of packet options.
    ///
    /// @return number of bytes required to build this packet
    size_t len();

    /// @brief Sets hops field.
    ///
    /// @param hops value to be set
    void setHops(uint8_t hops) { hops_ = hops; };

    /// @brief Returns hops field.
    ///
    /// @return hops field
    uint8_t getHops() const { return (hops_); };

    // Note: There's no need to manipulate OP field directly,
    // thus no setOp() method. See op_ comment.

    /// @brief Returns op field.
    ///
    /// @return op field
    uint8_t getOp() const { return (op_); };

    /// @brief Sets secs field.
    ///
    /// @param secs value to be set
    void setSecs(uint16_t secs) { secs_ = secs; };

    /// @brief Returns secs field.
    ///
    /// @return secs field
    uint16_t getSecs() const { return (secs_); };

    /// @brief Sets flags field.
    ///
    /// @param flags value to be set
    void setFlags(uint16_t flags) { flags_ = flags; };

    /// @brief Returns flags field.
    ///
    /// @return flags field
    uint16_t getFlags() const { return (flags_); };


    /// @brief Returns ciaddr field.
    ///
    /// @return ciaddr field
    const isc::asiolink::IOAddress&
    getCiaddr() const { return (ciaddr_); };

    /// @brief Sets ciaddr field.
    ///
    /// @param ciaddr value to be set
    void
    setCiaddr(const isc::asiolink::IOAddress& ciaddr) { ciaddr_ = ciaddr; };


    /// @brief Returns siaddr field.
    ///
    /// @return siaddr field
    const isc::asiolink::IOAddress&
    getSiaddr() const { return (siaddr_); };

    /// @brief Sets siaddr field.
    ///
    /// @param siaddr value to be set
    void
    setSiaddr(const isc::asiolink::IOAddress& siaddr) { siaddr_ = siaddr; };


    /// @brief Returns yiaddr field.
    ///
    /// @return yiaddr field
    const isc::asiolink::IOAddress&
    getYiaddr() const { return (yiaddr_); };

    /// @brief Sets yiaddr field.
    ///
    /// @param yiaddr value to be set
    void
    setYiaddr(const isc::asiolink::IOAddress& yiaddr) { yiaddr_ = yiaddr; };


    /// @brief Returns giaddr field.
    ///
    /// @return giaddr field
    const isc::asiolink::IOAddress&
    getGiaddr() const { return (giaddr_); };

    /// @brief Sets giaddr field.
    ///
    /// @param giaddr value to be set
    void
    setGiaddr(const isc::asiolink::IOAddress& giaddr) { giaddr_ = giaddr; };

    /// @brief Sets transaction-id value
    ///
    /// @param transid transaction-id to be set.
    void setTransid(uint32_t transid) { transid_ = transid; }

    /// @brief Returns value of transaction-id field.
    ///
    /// @return transaction-id
    uint32_t getTransid() const { return (transid_); };

    /// @brief Returns message type (e.g. 1 = DHCPDISCOVER).
    ///
    /// @return message type
    uint8_t
    getType() const { return (msg_type_); }

    /// @brief Sets message type (e.g. 1 = DHCPDISCOVER).
    ///
    /// @param type message type to be set
    void setType(uint8_t type) { msg_type_=type; };

    /// @brief Returns sname field
    ///
    /// Note: This is 64 bytes long field. It doesn't have to be
    /// null-terminated. Do not use strlen() or similar on it.
    ///
    /// @return sname field
    const OptionBuffer
    getSname() const { return (std::vector<uint8_t>(sname_, &sname_[MAX_SNAME_LEN])); };

    /// @brief Sets sname field.
    ///
    /// @param sname value to be set
    /// @param sname_len length of the sname buffer (up to MAX_SNAME_LEN)
    void setSname(const uint8_t* sname, size_t sname_len = MAX_SNAME_LEN);

    /// @brief Returns file field
    ///
    /// Note: This is 128 bytes long field. It doesn't have to be
    /// null-terminated. Do not use strlen() or similar on it.
    ///
    /// @return pointer to file field
    const OptionBuffer
    getFile() const { return (std::vector<uint8_t>(file_, &file_[MAX_FILE_LEN])); };

    /// Sets file field
    ///
    /// @param file value to be set
    /// @param file_len length of the file buffer (up to MAX_FILE_LEN)
    void
    setFile(const uint8_t* file, size_t file_len = MAX_FILE_LEN);

    /// @brief Sets hardware address.
    ///
    /// Sets parameters of hardware address. hlen specifies
    /// length of mac_addr buffer. Content of mac_addr buffer
    /// will be copied to appropriate field.
    ///
    /// Note: mac_addr must be a buffer of at least hlen bytes.
    ///
    /// @param hType hardware type (will be sent in htype field)
    /// @param hlen hardware length (will be sent in hlen field)
    /// @param mac_addr pointer to hardware address
    void setHWAddr(uint8_t hType, uint8_t hlen,
                   const std::vector<uint8_t>& mac_addr);

    /// Returns htype field
    ///
    /// @return hardware type
    uint8_t
    getHtype() const { return (htype_); };

    /// Returns hlen field
    ///
    /// @return hardware address length
    uint8_t
    getHlen() const { return (hlen_); };

    /// @brief Returns chaddr field.
    ///
    /// Note: This is 16 bytes long field. It doesn't have to be
    /// null-terminated. Do no use strlen() or similar on it.
    ///
    /// @return pointer to hardware address
    const uint8_t*
    getChaddr() const { return (chaddr_); };


    /// @brief Returns reference to output buffer.
    ///
    /// Returned buffer will contain reasonable data only for
    /// output (TX) packet and after pack() was called. This buffer
    /// is only valid till Pkt4 object is valid.
    ///
    /// RX packet or TX packet before pack() will return buffer with
    /// zero length
    ///
    /// @return reference to output buffer
    const isc::util::OutputBuffer&
    getBuffer() const { return (bufferOut_); };

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

    /// @brief Returns interface name.
    ///
    /// Returns interface name over which packet was received or is
    /// going to be transmitted.
    ///
    /// @return interface name
    std::string getIface() const { return iface_; };

    /// @brief Returns packet timestamp.
    ///
    /// Returns packet timestamp value updated when
    /// packet is received or send.
    ///
    /// @return packet timestamp.
    const boost::posix_time::ptime& getTimestamp() const { return timestamp_; }

    /// @brief Sets interface name.
    ///
    /// Sets interface name over which packet was received or is
    /// going to be transmitted.
    ///
    /// @return interface name
    void setIface(const std::string& iface ) { iface_ = iface; };

    /// @brief Sets interface index.
    ///
    /// @param ifindex specifies interface index.
    void setIndex(uint32_t ifindex) { ifindex_ = ifindex; };

    /// @brief Returns interface index.
    ///
    /// @return interface index
    uint32_t getIndex() const { return (ifindex_); };

    /// @brief Sets remote address.
    ///
    /// @param remote specifies remote address
    void setRemoteAddr(const isc::asiolink::IOAddress& remote) {
        remote_addr_ = remote;
    }

    /// @brief Returns remote address
    ///
    /// @return remote address
    const isc::asiolink::IOAddress& getRemoteAddr() const {
        return (remote_addr_);
    }

    /// @brief Sets local address.
    ///
    /// @param local specifies local address
    void setLocalAddr(const isc::asiolink::IOAddress& local) {
        local_addr_ = local;
    }

    /// @brief Returns local address.
    ///
    /// @return local address
    const isc::asiolink::IOAddress& getLocalAddr() const {
        return (local_addr_);
    }

    /// @brief Sets local port.
    ///
    /// @param local specifies local port
    void setLocalPort(uint16_t local) { local_port_ = local; }

    /// @brief Returns local port.
    ///
    /// @return local port
    uint16_t getLocalPort() const { return (local_port_); }

    /// @brief Sets remote port.
    ///
    /// @param remote specifies remote port
    void setRemotePort(uint16_t remote) { remote_port_ = remote; }

    /// @brief Returns remote port.
    ///
    /// @return remote port
    uint16_t getRemotePort() const { return (remote_port_); }

    /// @brief Update packet timestamp.
    ///
    /// Updates packet timestamp. This method is invoked
    /// by interface manager just before sending or
    /// just after receiving it.
    /// @throw isc::Unexpected if timestamp update failed
    void updateTimestamp();

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
    uint32_t ifindex_;

    /// local UDP port
    uint16_t local_port_;

    /// remote UDP port
    uint16_t remote_port_;

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

    /// output buffer (used during message transmission)
    ///
    /// @warning This protected member is accessed by derived
    /// classes directly. One of such derived classes is
    /// @ref perfdhcp::PerfPkt4. The impact on derived clasess'
    /// behavior must be taken into consideration before making
    /// changes to this member such as access scope restriction or
    /// data format change etc.
    isc::util::OutputBuffer bufferOut_;

    /// that's the data of input buffer used in RX packet. Note that
    /// InputBuffer does not store the data itself, but just expects that
    /// data will be valid for the whole life of InputBuffer. Therefore we
    /// need to keep the data around.
    ///
    /// @warning This protected member is accessed by derived
    /// classes directly. One of such derived classes is
    /// @ref perfdhcp::PerfPkt4. The impact on derived clasess'
    /// behavior must be taken into consideration before making
    /// changes to this member such as access scope restriction or
    /// data format change etc.
    std::vector<uint8_t> data_;

    /// message type (e.g. 1=DHCPDISCOVER)
    /// @todo this will eventually be replaced with DHCP Message Type
    /// option (option 53)
    uint8_t msg_type_;

    /// collection of options present in this message
    ///
    /// @warning This protected member is accessed by derived
    /// classes directly. One of such derived classes is
    /// @ref perfdhcp::PerfPkt4. The impact on derived clasess'
    /// behavior must be taken into consideration before making
    /// changes to this member such as access scope restriction or
    /// data format change etc.
    isc::dhcp::Option::OptionCollection options_;

    /// packet timestamp
    boost::posix_time::ptime timestamp_;
}; // Pkt4 class

typedef boost::shared_ptr<Pkt4> Pkt4Ptr;

} // isc::dhcp namespace

} // isc namespace

#endif
