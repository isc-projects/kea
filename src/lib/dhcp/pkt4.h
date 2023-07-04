// Copyright (C) 2011-2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef PKT4_H
#define PKT4_H

#include <asiolink/io_address.h>
#include <dhcp/duid.h>
#include <util/buffer.h>
#include <dhcp/option.h>
#include <dhcp/classify.h>
#include <dhcp/pkt.h>

#include <boost/shared_ptr.hpp>

#include <iostream>
#include <vector>
#include <set>
#include <list>

#include <time.h>

namespace isc {

namespace dhcp {

/// @brief Represents DHCPv4 packet
///
/// This class represents a single DHCPv4 packet. It handles both incoming
/// and transmitted packets, parsing incoming options, options handling
/// (add, get, remove), on-wire assembly, sanity checks and other operations.
/// This specific class has several DHCPv4-specific methods, but it uses a lot
/// of common operations from its base @c Pkt class that is shared with Pkt6.
class Pkt4 : public Pkt {
public:

    /// length of the CHADDR field in DHCPv4 message
    const static size_t MAX_CHADDR_LEN = 16;

    /// length of the SNAME field in DHCPv4 message
    const static size_t MAX_SNAME_LEN = 64;

    /// length of the FILE field in DHCPv4 message
    const static size_t MAX_FILE_LEN = 128;

    /// specifies DHCPv4 packet header length (fixed part)
    const static size_t DHCPV4_PKT_HDR_LEN = 236;

    /// Mask for the value of flags field in the DHCPv4 message
    /// to check whether client requested broadcast response.
    const static uint16_t FLAG_BROADCAST_MASK = 0x8000;

    /// Constructor, used in replying to a message.
    ///
    /// @param msg_type type of message (e.g. DHCPDISCOVER=1)
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
    /// Output buffer will be stored in buffer_out_.
    /// The buffer_out_ is cleared before writing to the buffer.
    ///
    /// @throw InvalidOperation if packing fails
    virtual void pack();

    /// @brief Parses on-wire form of DHCPv4 packet.
    ///
    /// Parses received packet, stored in on-wire format in bufferIn_.
    ///
    /// Will create a collection of option objects that will
    /// be stored in options_ container.
    ///
    /// Method with throw exception if packet parsing fails.
    virtual void unpack();

    /// @brief Returns text representation of the primary packet identifiers
    ///
    /// This method is intended to be used to provide a consistent way to
    /// identify packets within log statements.  It is an instance-level
    /// wrapper around static makeLabel(). See this method for string
    /// content.
    ///
    /// This method is exception safe.
    ///
    /// @return string with text representation
    std::string getLabel() const;

    /// @brief Returns text representation of the given packet identifiers
    ///
    /// @param hwaddr - hardware address to include in the string, it may be
    /// NULL.
    /// @param client_id - client id to include in the string, it may be NULL.
    /// to include in the string
    /// @param transid - numeric transaction id to include in the string
    ///
    /// @return string with text representation
    static std::string makeLabel(const HWAddrPtr& hwaddr,
                                 const ClientIdPtr& client_id,
                                 const uint32_t transid);

    /// @brief Returns text representation of the given packet identifiers.
    ///
    /// This variant of the method does not include transaction id.
    ///
    /// @param hwaddr hardware address to include in the string, it may be
    /// NULL.
    /// @param client_id client id to include in the string, it may be NULL.
    static std::string makeLabel(const HWAddrPtr& hwaddr, const ClientIdPtr& client_id);

    /// @brief Returns text representation of the packet.
    ///
    /// This function is useful mainly for debugging.
    ///
    /// @return string with text representation
    std::string toText() const;

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

    /// @brief Returns DHCP message type (e.g. 1 = DHCPDISCOVER).
    ///
    /// This method is exception safe. For packets without DHCP Message Type
    /// option, it returns DHCP_NOTYPE (0).
    ///
    /// @return message type
    uint8_t getType() const;

    /// @brief Sets DHCP message type (e.g. 1 = DHCPDISCOVER).
    ///
    /// @param type message type to be set
    void setType(uint8_t type);

    /// @brief Returns name of the DHCP message for a given type number.
    ///
    /// This method is exception safe. For messages without DHCP Message Type
    /// options, it returns UNKNOWN.
    ///
    /// @param type DHCPv4 message type which name should be returned.
    ///
    /// @return Pointer to the "const" string containing DHCP message name.
    /// If the message type is unsupported the "UNKNOWN" is returned.
    /// The caller must not release the returned pointer.
    static const char* getName(const uint8_t type);

    /// @brief Returns name of the DHCP message.
    ///
    /// @return Pointer to the "const" string containing DHCP message name.
    /// If the message type is unsupported the "UNKNOWN" is returned.
    /// The caller must not release the returned pointer.
    const char* getName() const;

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
    void setSname(const uint8_t* sname, size_t sname_len);

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
    setFile(const uint8_t* file, size_t file_len);

    /// @brief Sets hardware address.
    ///
    /// Sets parameters of hardware address. hlen specifies
    /// length of mac_addr buffer. Content of mac_addr buffer
    /// will be copied to appropriate field.
    ///
    /// Note: mac_addr must be a buffer of at least hlen bytes.
    ///
    /// @param htype hardware type (will be sent in htype field)
    /// @param hlen hardware length (will be sent in hlen field)
    /// @param mac_addr pointer to hardware address
    void setHWAddr(uint8_t htype, uint8_t hlen,
                   const std::vector<uint8_t>& mac_addr);

    /// @brief Sets hardware address
    ///
    /// Sets hardware address, based on existing HWAddr structure
    /// @param addr already filled in HWAddr structure
    /// @throw BadValue if addr is null
    void setHWAddr(const HWAddrPtr& addr);

    /// Returns htype field
    ///
    /// @return hardware type
    uint8_t
    getHtype() const;

    /// Returns hlen field
    ///
    /// @return hardware address length
    uint8_t
    getHlen() const;

    /// @brief returns hardware address information
    /// @return hardware address structure
    HWAddrPtr getHWAddr() const { return (hwaddr_); }

    /// @brief Returns text representation of the hardware address
    ///
    /// Returns text representation of the hardware address (e.g. hwaddr=00:01:02:03:04:05).
    /// If there is no defined hardware address, it returns @c hwaddr=(undefined).
    ///
    /// @return string with text representation
    std::string getHWAddrLabel() const;

    /// @brief Add an option.
    ///
    /// @note: to avoid throwing when adding multiple options
    /// with the same type use @ref Pkt::addOption.
    ///
    /// @throw BadValue if option with that type is already present.
    ///
    /// @param opt option to be added
    virtual void
    addOption(const OptionPtr& opt);

    /// @brief Sets local HW address.
    ///
    /// Sets the source HW address for the outgoing packet or
    /// destination HW address for the incoming packet.
    ///
    /// @note mac_addr must be a buffer of at least hlen bytes.
    ///
    /// @param htype hardware type (will be sent in htype field)
    /// @param hlen hardware length (will be sent in hlen field)
    /// @param mac_addr pointer to hardware address
    void setLocalHWAddr(const uint8_t htype, const uint8_t hlen,
                        const std::vector<uint8_t>& mac_addr);

    /// @brief Sets local HW address.
    ///
    /// Sets hardware address from an existing HWAddr structure.
    /// The local address is a source address for outgoing
    /// packet and destination address for incoming packet.
    ///
    /// @param addr structure representing HW address.
    ///
    /// @throw BadValue if addr is null
    void setLocalHWAddr(const HWAddrPtr& addr);

    /// @brief Returns local HW address.
    ///
    /// @return local HW addr.
    HWAddrPtr getLocalHWAddr() const {
        return (local_hwaddr_);
    }

    /// @brief Returns a reference to option codes which unpacking
    /// will be deferred.
    ///
    /// Only options 43 and 224-254 are subject of deferred
    /// unpacking: when the packet unpacking is performed, each time
    /// such an option is found, it is unpacked as an unknown option
    /// and the code added in this list.
    ///
    /// @return List of codes of options which unpacking is deferred.
    std::list<uint16_t>& getDeferredOptions() {
        return (deferred_options_);
    }

    /// @brief Checks if a DHCPv4 message has been relayed.
    ///
    /// This function returns a boolean value which indicates whether a DHCPv4
    /// message has been relayed (if true is returned) or not (if false).
    ///
    /// The message is considered relayed if the giaddr field is non-zero and
    /// non-broadcast.
    ///
    /// @return Boolean value which indicates whether the message is relayed
    /// (true) or non-relayed (false).
    bool isRelayed() const;

    /// @brief Checks if a DHCPv4 message has been transported over DHCPv6
    ///
    /// @return Boolean value which indicates whether the message is
    /// transported over DHCPv6 (true) or native DHCPv4 (false)
    virtual bool isDhcp4o6() const {
        return (false);
    }

private:

    /// @brief Generic method that validates and sets HW address.
    ///
    /// This is a generic method used by all modifiers of this class
    /// which set class members representing HW address.
    ///
    /// @param htype hardware type.
    /// @param hlen hardware length.
    /// @param mac_addr pointer to actual hardware address.
    /// @param [out] hw_addr pointer to a class member to be modified.
    ///
    /// @trow isc::OutOfRange if invalid HW address specified.
    virtual void setHWAddrMember(const uint8_t htype, const uint8_t hlen,
                                 const std::vector<uint8_t>& mac_addr,
                                 HWAddrPtr& hw_addr);

protected:

    /// converts DHCP message type to BOOTP op type
    ///
    /// @param dhcpType DHCP message type (e.g. DHCPDISCOVER)
    ///
    /// @return BOOTP type (BOOTREQUEST or BOOTREPLY)
    uint8_t
    DHCPTypeToBootpType(uint8_t dhcpType);

    /// @brief No-op
    ///
    /// This method returns hardware address generated from the IPv6 link-local
    /// address. As there is no IPv4-equivalent, it always returns NULL.
    /// We need this stub implementation here, to keep all the get hardware
    /// address logic in the base class.
    ///
    /// @return always NULL
    virtual HWAddrPtr getMACFromSrcLinkLocalAddr() {
        return (HWAddrPtr());
    }

    /// @brief No-op
    ///
    /// This method returns hardware address extracted from an IPv6 relay agent.
    /// option. As there is no IPv4-equivalent, it always returns NULL.
    /// We need this stub implementation here, to keep all the get hardware
    /// address logic in the base class.
    ///
    /// @return always NULL
    virtual HWAddrPtr getMACFromIPv6RelayOpt() {
        return (HWAddrPtr());
    }

    /// @brief No-op
    ///
    /// This is a DHCPv4 version of the function that attempts to extract
    /// MAC address from the options inserted by a cable modem. It is currently
    /// not implemented for v4.
    ///
    /// @return always NULL
    virtual HWAddrPtr getMACFromDocsisModem() {
        return (HWAddrPtr());
    }

    /// @brief No-op
    ///
    /// This method returns hardware address extracted from DUID.
    /// Currently it is a no-op, even though there's RFC that defines how to
    /// use DUID in DHCPv4 (see RFC4361). We may implement it one day.
    ///
    /// @return always NULL
    virtual HWAddrPtr getMACFromDUID(){
        return (HWAddrPtr());
    }

    /// @brief No-op
    ///
    /// This is a DHCPv4 version of the function that attempts to extract
    /// MAC address from the options inserted by a CMTS. It is currently
    /// not implemented for v4.
    ///
    /// @return always NULL
    virtual HWAddrPtr getMACFromDocsisCMTS() {
        return (HWAddrPtr());
    }

    /// @brief No-op
    ///
    /// This method returns hardware address extracted from remote-id relay option.
    /// Currently it is a no-op, it always returns NULL.
    ///
    /// @return always NULL
    virtual HWAddrPtr getMACFromRemoteIdRelayOption() {
        return (HWAddrPtr());
    }

    /// @brief local HW address (dst if receiving packet, src if sending packet)
    HWAddrPtr local_hwaddr_;

    // @brief List of deferred option codes
    std::list<uint16_t> deferred_options_;

    /// @brief message operation code
    ///
    /// Note: This is legacy BOOTP field. There's no need to manipulate it
    /// directly. Its value is set based on DHCP message type. Note that
    /// DHCPv4 protocol reuses BOOTP message format, so this field is
    /// kept due to BOOTP format. This is NOT DHCPv4 type (DHCPv4 message
    /// type is kept in message type option).
    uint8_t op_;

    /// @brief link-layer address and hardware information
    /// represents 3 fields: htype (hardware type, 1 byte), hlen (length of the
    /// hardware address, up to 16) and chaddr (hardware address field,
    /// 16 bytes)
    HWAddrPtr hwaddr_;

    /// Number of relay agents traversed
    uint8_t hops_;

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

    /// sname field (64 bytes)
    uint8_t sname_[MAX_SNAME_LEN];

    /// file field (128 bytes)
    uint8_t file_[MAX_FILE_LEN];

    // end of real DHCPv4 fields
}; // Pkt4 class

/// @brief A pointer to Pkt4 object.
typedef boost::shared_ptr<Pkt4> Pkt4Ptr;

} // isc::dhcp namespace
} // isc namespace

#endif
