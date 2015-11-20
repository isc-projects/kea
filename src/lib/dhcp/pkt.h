// Copyright (C) 2014-2015 Internet Systems Consortium, Inc. ("ISC")
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

#ifndef PKT_H
#define PKT_H

#include <asiolink/io_address.h>
#include <util/buffer.h>
#include <dhcp/option.h>
#include <dhcp/hwaddr.h>
#include <dhcp/classify.h>

#include <boost/date_time/posix_time/posix_time.hpp>

namespace isc {

namespace dhcp {

/// @brief Base class for classes representing DHCP messages.
///
/// This is a base class that holds common information (e.g. source
/// and destination ports) and operations (e.g. add, get, delete options)
/// for derived classes representing both DHCPv4 and DHCPv6 messages.
/// The @c Pkt4 and @c Pkt6 classes derive from it.
///
/// @note This is abstract class. Please instantiate derived classes
/// such as @c Pkt4 or @c Pkt6.
class Pkt {
protected:

    /// @brief Constructor.
    ///
    /// This constructor is typically used for transmitted messages as it
    /// creates an empty (no options) packet. The constructor is protected,
    /// so only derived classes can call it. Pkt class cannot be instantiated
    /// anyway, because it is an abstract class.
    ///
    /// @param transid transaction-id
    /// @param local_addr local IPv4 or IPv6 address
    /// @param remote_addr remote IPv4 or IPv6 address
    /// @param local_port local UDP (one day also TCP) port
    /// @param remote_port remote UDP (one day also TCP) port
    Pkt(uint32_t transid, const isc::asiolink::IOAddress& local_addr,
        const isc::asiolink::IOAddress& remote_addr, uint16_t local_port,
        uint16_t remote_port);

    /// @brief Constructor.
    ///
    /// This constructor is typically used for received messages as it takes
    /// a buffer that's going to be parsed as one of arguments. The constructor
    /// is protected, so only derived classes can call it. Pkt class cannot be
    /// instantiated anyway, because it is an abstract class.
    ///
    /// @param buf pointer to a buffer that contains on-wire data
    /// @param len length of the pointer specified in buf
    /// @param local_addr local IPv4 or IPv6 address
    /// @param remote_addr remote IPv4 or IPv6 address
    /// @param local_port local UDP (one day also TCP) port
    /// @param remote_port remote UDP (one day also TCP) port
    Pkt(const uint8_t* buf, uint32_t len,
        const isc::asiolink::IOAddress& local_addr,
        const isc::asiolink::IOAddress& remote_addr, uint16_t local_port,
        uint16_t remote_port);

public:

    /// @brief Prepares on-wire format of DHCP (either v4 or v6) packet.
    ///
    /// Prepares on-wire format of message and all its options.
    /// A caller must ensure that options are stored in options_ field
    /// prior to calling this method.
    ///
    /// Output buffer will be stored in buffer_out_.
    /// The buffer_out_ should be cleared before writting to the buffer
    /// in the derived classes.
    ///
    /// @note This is a pure virtual method and must be implemented in
    /// the derived classes. The @c Pkt4 and @c Pkt6 class have respective
    /// implementations of this method.
    ///
    /// @throw InvalidOperation if packing fails
    virtual void pack() = 0;

    /// @brief Parses on-wire form of DHCP (either v4 or v6) packet.
    ///
    /// Parses received packet, stored in on-wire format in data_.
    ///
    /// Will create a collection of option objects that will
    /// be stored in options_ container.
    ///
    /// @note This is a pure virtual method and must be implemented in
    /// the derived classes. The @c Pkt4 and @c Pkt6 class have respective
    /// implementations of this method.
    ///
    /// Method will throw exception if packet parsing fails.
    ///
    /// @throw tbd
    virtual void unpack() = 0;

    /// @brief Returns reference to output buffer.
    ///
    /// Returned buffer will contain reasonable data only for
    /// output (TX) packet and after pack() was called.
    ///
    /// RX packet or TX packet before pack() will return buffer with
    /// zero length. This buffer is returned as non-const, so hooks
    /// framework (and user's callouts) can modify them if needed
    ///
    /// @note This buffer is only valid till object that returned it exists.
    ///
    /// @return reference to output buffer
    isc::util::OutputBuffer& getBuffer() { return (buffer_out_); };

    /// @brief Adds an option to this packet.
    ///
    /// Derived classes may provide more specialized implementations.
    /// In particular @c Pkt4 provides one that checks if option is
    /// unique.
    ///
    /// @param opt option to be added.
    virtual void addOption(const OptionPtr& opt);

    /// @brief Attempts to delete first suboption of requested type.
    ///
    /// If there are several options of the same type present, only
    /// the first option will be deleted.
    ///
    /// @param type Type of option to be deleted.
    ///
    /// @return true if option was deleted, false if no such option existed
    bool delOption(uint16_t type);

    /// @brief Returns text representation primary packet identifiers
    ///
    /// This method is intended to be used to provide as a consistent way to
    /// identify packets within log statements.  Derivations should supply
    /// there own implementation.
    ///
    /// @return string with text representation
    virtual std::string getLabel() const {
        isc_throw(NotImplemented, "Pkt::getLabel()");
    }

    /// @brief Returns text representation of the packet.
    ///
    /// This function is useful mainly for debugging.
    ///
    /// @note This is a pure virtual method and must be implemented in
    /// the derived classes. The @c Pkt4 and @c Pkt6 class have respective
    /// implementations of this method.
    ///
    /// @return string with text representation
    virtual std::string toText() const = 0;

    /// @brief Returns packet size in binary format.
    ///
    /// Returns size of the packet in on-wire format or size needed to store
    /// it in on-wire format.
    ///
    /// @note This is a pure virtual method and must be implemented in
    /// the derived classes. The @c Pkt4 and @c Pkt6 class have respective
    /// implementations of this method.
    ///
    /// @return packet size in bytes
    virtual size_t len() = 0;

    /// @brief Returns message type (e.g. 1 = SOLICIT).
    ///
    /// @note This is a pure virtual method and must be implemented in
    /// the derived classes. The @c Pkt4 and @c Pkt6 class have respective
    /// implementations of this method.
    ///
    /// @return message type
    virtual uint8_t getType() const = 0;

    /// @brief Sets message type (e.g. 1 = SOLICIT).
    ///
    /// @note This is a pure virtual method and must be implemented in
    /// the derived classes. The @c Pkt4 and @c Pkt6 class have respective
    /// implementations of this method.
    ///
    /// @param type message type to be set
    virtual void setType(uint8_t type) = 0;

    /// @brief Returns name of the DHCP message.
    ///
    /// For all unsupported messages the derived classes must return
    /// "UNKNOWN".
    ///
    /// @return Ponter to "const" string containing DHCP message name.
    /// The implementations in the derived classes should statically
    /// allocate returned strings and the caller must not release the
    /// returned pointer.
    virtual const char* getName() const = 0;

    /// @brief Sets transaction-id value.
    ///
    /// @param transid transaction-id to be set.
    void setTransid(uint32_t transid) { transid_ = transid; }

    /// @brief Returns value of transaction-id field.
    ///
    /// @return transaction-id
    uint32_t getTransid() const { return (transid_); };

    /// @brief Checks whether a client belongs to a given class.
    ///
    /// @param client_class name of the class
    /// @return true if belongs
    bool inClass(const isc::dhcp::ClientClass& client_class);

    /// @brief Adds packet to a specified class.
    ///
    /// A packet can be added to the same class repeatedly. Any additional
    /// attempts to add to a class the packet already belongs to, will be
    /// ignored silently.
    ///
    /// @note It is a matter of naming convention. Conceptually, the server
    /// processes a stream of packets, with some packets belonging to given
    /// classes. From that perspective, this method adds a packet to specifed
    /// class. Implementation wise, it looks the opposite - the class name
    /// is added to the packet. Perhaps the most appropriate name for this
    /// method would be associateWithClass()? But that seems overly long,
    /// so I decided to stick with addClass().
    ///
    /// @param client_class name of the class to be added
    void addClass(const isc::dhcp::ClientClass& client_class);

    /// @brief Returns the class set
    ///
    /// @note This should be used only to iterate over the class set.
    /// @return
    const ClientClasses& getClasses() const { return (classes_); }

    /// @brief Unparsed data (in received packets).
    ///
    /// @warning This public member is accessed by derived
    /// classes directly. One of such derived classes is
    /// @ref perfdhcp::PerfPkt6. The impact on derived clasess'
    /// behavior must be taken into consideration before making
    /// changes to this member such as access scope restriction or
    /// data format change etc.
    OptionBuffer data_;

    /// @brief Returns the first option of specified type.
    ///
    /// Returns the first option of specified type. Note that in DHCPv6 several
    /// instances of the same option are allowed (and frequently used).
    /// Also see \ref Pkt6::getOptions().
    ///
    /// The options will be only returned after unpack() is called.
    ///
    /// @param type option type we are looking for
    ///
    /// @return pointer to found option (or NULL)
    OptionPtr getOption(uint16_t type) const;

    /// @brief Update packet timestamp.
    ///
    /// Updates packet timestamp. This method is invoked
    /// by interface manager just before sending or
    /// just after receiving it.
    /// @throw isc::Unexpected if timestamp update failed
    void updateTimestamp();

    /// @brief Returns packet timestamp.
    ///
    /// Returns packet timestamp value updated when
    /// packet is received or send.
    ///
    /// @return packet timestamp.
    const boost::posix_time::ptime& getTimestamp() const {
        return timestamp_;
    }

    /// @brief Copies content of input buffer to output buffer.
    ///
    /// This is mostly a diagnostic function. It is being used for sending
    /// received packet. Received packet is stored in data_, but
    /// transmitted data is stored in buffer_out_. If we want to send packet
    /// that we just received, a copy between those two buffers is necessary.
    void repack();

    /// @brief Set callback function to be used to parse options.
    ///
    /// @param callback An instance of the callback function or NULL to
    /// uninstall callback.
    void setCallback(UnpackOptionsCallback callback) {
        callback_ = callback;
    }

    /// @brief Sets remote IP address.
    ///
    /// @param remote specifies remote address
    void setRemoteAddr(const isc::asiolink::IOAddress& remote) {
        remote_addr_ = remote;
    }

    /// @brief Returns remote IP address.
    ///
    /// @return remote address
    const isc::asiolink::IOAddress& getRemoteAddr() const {
        return (remote_addr_);
    }

    /// @brief Sets local IP address.
    ///
    /// @param local specifies local address
    void setLocalAddr(const isc::asiolink::IOAddress& local) {
        local_addr_ = local;
    }

    /// @brief Returns local IP address.
    ///
    /// @return local address
    const isc::asiolink::IOAddress& getLocalAddr() const {
        return (local_addr_);
    }

    /// @brief Sets local UDP (and soon TCP) port.
    ///
    /// This sets a local port, i.e. destination port for recently received
    /// packet or a source port for to be transmitted packet.
    ///
    /// @param local specifies local port
    void setLocalPort(uint16_t local) {
        local_port_ = local;
    }

    /// @brief Returns local UDP (and soon TCP) port.
    ///
    /// This sets a local port, i.e. destination port for recently received
    /// packet or a source port for to be transmitted packet.
    ///
    /// @return local port
    uint16_t getLocalPort() const {
        return (local_port_);
    }

    /// @brief Sets remote UDP (and soon TCP) port.
    ///
    /// This sets a remote port, i.e. source port for recently received
    /// packet or a destination port for to be transmitted packet.
    ///
    /// @param remote specifies remote port
    void setRemotePort(uint16_t remote) {
        remote_port_ = remote;
    }

    /// @brief Returns remote port.
    ///
    /// @return remote port
    uint16_t getRemotePort() const {
        return (remote_port_);
    }

    /// @brief Sets interface index.
    ///
    /// @param ifindex specifies interface index.
    void setIndex(uint32_t ifindex) {
        ifindex_ = ifindex;
    };

    /// @brief Returns interface index.
    ///
    /// @return interface index
    uint32_t getIndex() const {
        return (ifindex_);
    };

    /// @brief Returns interface name.
    ///
    /// Returns interface name over which packet was received or is
    /// going to be transmitted.
    ///
    /// @return interface name
    std::string getIface() const { return (iface_); };

    /// @brief Sets interface name.
    ///
    /// Sets interface name over which packet was received or is
    /// going to be transmitted.
    ///
    /// @return interface name
    void setIface(const std::string& iface ) { iface_ = iface; };

    /// @brief Sets remote hardware address.
    ///
    /// Sets hardware address (MAC) from an existing HWAddr structure.
    /// The remote address is a destination address for outgoing
    /// packet and source address for incoming packet. When this
    /// is an outgoing packet, this address will be used to
    /// construct the link layer header.
    ///
    /// @param hw_addr structure representing HW address.
    ///
    /// @throw BadValue if addr is null
    void setRemoteHWAddr(const HWAddrPtr& hw_addr);

    /// @brief Sets remote hardware address.
    ///
    /// Sets the destination hardware (MAC) address for the outgoing packet
    /// or source HW address for the incoming packet. When this
    /// is an outgoing packet this address will be used to construct
    /// the link layer header.
    ///
    /// @note mac_addr must be a buffer of at least hlen bytes.
    ///
    /// In a typical case, hlen field would be redundant, as it could
    /// be extracted from mac_addr.size(). However, the difference is
    /// when running on exotic hardware, like Infiniband, that had
    /// MAC addresses 20 bytes long. In that case, hlen is set to zero
    /// in DHCPv4.
    ///
    /// @param htype hardware type (will be sent in htype field)
    /// @param hlen hardware length (will be sent in hlen field)
    /// @param hw_addr pointer to hardware address
    void setRemoteHWAddr(const uint8_t htype, const uint8_t hlen,
                         const std::vector<uint8_t>& hw_addr);

    /// @brief Returns the remote HW address obtained from raw sockets.
    ///
    /// @return remote HW address.
    HWAddrPtr getRemoteHWAddr() const {
        return (remote_hwaddr_);
    }

    /// @brief Returns MAC address.
    ///
    /// The difference between this method and getRemoteHWAddr() is that
    /// getRemoteHWAddr() returns only what was obtained from raw sockets.
    /// This method is more generic and can attempt to obtain MAC from
    /// varied sources: raw sockets, client-id, link-local IPv6 address,
    /// and various relay options.
    ///
    /// @note Technically the proper term for this information is a link layer
    /// address, but it is frequently referred to MAC or hardware address.
    /// Since we're calling the feature "MAC addresses in DHCPv6", we decided
    /// to keep the name of getMAC().
    ///
    /// hw_addr_src takes a combination of bit values specified in
    /// HWADDR_SOURCE_* constants.
    ///
    /// @param hw_addr_src a bitmask that specifies hardware address source
    HWAddrPtr getMAC(uint32_t hw_addr_src);

    /// @brief Virtual desctructor.
    ///
    /// There is nothing to clean up here, but since there are virtual methods,
    /// we define virtual destructor to ensure that derived classes will have
    /// a virtual one, too.
    virtual ~Pkt() {
    }

    /// @brief Classes this packet belongs to.
    ///
    /// This field is public, so the code outside of Pkt4 or Pkt6 class can
    /// iterate over existing classes. Having it public also solves the problem
    /// of returned reference lifetime. It is preferred to use @ref inClass and
    /// @ref addClass should be used to operate on this field.
    ClientClasses classes_;

    /// @brief Collection of options present in this message.
    ///
    /// @warning This public member is accessed by derived
    /// classes directly. One of such derived classes is
    /// @ref perfdhcp::PerfPkt6. The impact on derived clasess'
    /// behavior must be taken into consideration before making
    /// changes to this member such as access scope restriction or
    /// data format change etc.
    isc::dhcp::OptionCollection options_;

protected:

    /// @brief Attempts to obtain MAC address from source link-local
    /// IPv6 address
    ///
    /// This method is called from getMAC(HWADDR_SOURCE_IPV6_LINK_LOCAL)
    /// and should not be called directly. It is not 100% reliable.
    /// The source IPv6 address does not necessarily have to be link-local
    /// (may be global or ULA) and even if it's link-local, it doesn't
    /// necessarily be based on EUI-64. For example, Windows supports
    /// RFC4941, which randomized IID part of the link-local address.
    /// If this method fails, it will return NULL.
    ///
    /// For direct message, it attempts to use remote_addr_ field. For relayed
    /// message, it uses peer-addr of the first relay.
    ///
    /// @note This is a pure virtual method and must be implemented in
    /// the derived classes. The @c Pkt6 class have respective implementation.
    /// This method is not applicable to DHCPv4.
    ///
    /// @return hardware address (or NULL)
    virtual HWAddrPtr getMACFromSrcLinkLocalAddr() = 0;

    /// @brief Attempts to obtain MAC address from relay option
    /// client-linklayer-addr
    ///
    /// This method is called from getMAC(HWADDR_SOURCE_CLIENT_ADDR_RELAY_OPTION)
    /// and should not be called directly. It will extract the client's
    /// MAC/Hardware address from option client_linklayer_addr (RFC6939)
    /// inserted by the relay agent closest to the client.
    /// If this method fails, it will return NULL.
    ///
    /// @note This is a pure virtual method and must be implemented in
    /// the derived classes. The @c Pkt6 class have respective implementation.
    /// This method is not applicable to DHCPv4.
    ///
    /// @return hardware address (or NULL)
    virtual HWAddrPtr getMACFromIPv6RelayOpt() = 0;

    /// @brief Attempts to obtain MAC address from DUID-LL or DUID-LLT.
    ///
    /// This method is called from getMAC(HWADDR_SOURCE_DUID) and should not be
    /// called directly. It will attempt to extract MAC address information
    /// from DUID if its type is LLT or LL. If this method fails, it will
    /// return NULL.
    ///
    /// @note This is a pure virtual method and must be implemented in
    /// the derived classes. The @c Pkt6 class have respective implementation.
    /// This method is not applicable to DHCPv4.
    ///
    /// @return hardware address (or NULL)
    virtual HWAddrPtr getMACFromDUID() = 0;

    /// @brief Attempts to obtain MAC address from remote-id relay option.
    ///
    /// This method is called from getMAC(HWADDR_SOURCE_REMOTE_ID) and should not be
    /// called directly. It will attempt to extract MAC address information
    /// from remote-id option inserted by a relay agent closest to the client.
    /// If this method fails, it will return NULL.
    ///
    /// @note This is a pure virtual method and must be implemented in
    /// the derived classes. The @c Pkt6 class have respective implementation.
    /// This method is not applicable to DHCPv4.
    ///
    /// @return hardware address (or NULL)
    virtual HWAddrPtr getMACFromRemoteIdRelayOption() = 0;

    /// @brief Attempts to convert IPv6 address into MAC.
    ///
    /// Utility method that attempts to convert link-local IPv6 address to the
    /// MAC address. That works only for link-local IPv6 addresses that are
    /// based on EUI-64.
    ///
    /// @note This method uses hardware type of the interface the packet was
    /// received on. If you have multiple access technologies in your network
    /// (e.g. client connected to WiFi that relayed the traffic to the server
    /// over Ethernet), hardware type may be invalid.
    ///
    /// @param addr IPv6 address to be converted
    /// @return hardware address (or NULL)
    HWAddrPtr
    getMACFromIPv6(const isc::asiolink::IOAddress& addr);

    /// @brief Attempts to extract MAC/Hardware address from DOCSIS options
    ///        inserted by the modem itself.
    ///
    /// This is a generic mechanism for extracting hardware address from the
    /// DOCSIS options.
    ///
    /// @note This is a pure virtual method and must be implemented in
    /// the derived classes. The @c Pkt6 class have respective implementation.
    /// This method is currently not implemented in DHCPv4.
    ///
    /// @return hardware address (if necessary DOCSIS suboptions are present)
    virtual HWAddrPtr getMACFromDocsisModem() = 0;

    /// @brief Attempts to extract MAC/Hardware address from DOCSIS options
    ///        inserted by the CMTS (the relay agent)
    ///
    /// This is a generic mechanism for extracting hardware address from the
    /// DOCSIS options.
    ///
    /// @note This is a pure virtual method and must be implemented in
    /// the derived classes. The @c Pkt6 class have respective implementation.
    /// This method is currently not implemented in DHCPv4.
    ///
    /// @return hardware address (if necessary DOCSIS suboptions are present)
    virtual HWAddrPtr getMACFromDocsisCMTS() = 0;

    /// Transaction-id (32 bits for v4, 24 bits for v6)
    uint32_t transid_;

    /// Name of the network interface the packet was received/to be sent over.
    std::string iface_;

    /// @brief Interface index.
    ///
    /// Each network interface has assigned an unique ifindex.
    /// It is a functional equivalent of a name, but sometimes more useful, e.g.
    /// when using odd systems that allow spaces in interface names.
    int ifindex_;

    /// @brief Local IP (v4 or v6) address.
    ///
    /// Specifies local IPv4 or IPv6 address. It is a destination address for
    /// received packet, and a source address if it packet is being transmitted.
    isc::asiolink::IOAddress local_addr_;

    /// @brief Remote IP address.
    ///
    /// Specifies local IPv4 or IPv6 address. It is source address for received
    /// packet and a destination address for packet being transmitted.
    isc::asiolink::IOAddress remote_addr_;

    /// local TDP or UDP port
    uint16_t local_port_;

    /// remote TCP or UDP port
    uint16_t remote_port_;

    /// Output buffer (used during message transmission)
    ///
    /// @warning This protected member is accessed by derived
    /// classes directly. One of such derived classes is
    /// @ref perfdhcp::PerfPkt6. The impact on derived clasess'
    /// behavior must be taken into consideration before making
    /// changes to this member such as access scope restriction or
    /// data format change etc.
    isc::util::OutputBuffer buffer_out_;

    /// packet timestamp
    boost::posix_time::ptime timestamp_;

    // remote HW address (src if receiving packet, dst if sending packet)
    HWAddrPtr remote_hwaddr_;

    /// A callback to be called to unpack options from the packet.
    UnpackOptionsCallback callback_;

private:

    /// @brief Generic method that validates and sets HW address.
    ///
    /// This is a generic method used by all modifiers of this class
    /// which set class members representing HW address.
    ///
    /// @param htype hardware type.
    /// @param hlen hardware length.
    /// @param hw_addr pointer to actual hardware address.
    /// @param [out] storage pointer to a class member to be modified.
    ///
    /// @trow isc::OutOfRange if invalid HW address specified.
    virtual void setHWAddrMember(const uint8_t htype, const uint8_t hlen,
                                 const std::vector<uint8_t>& hw_addr,
                                 HWAddrPtr& storage);
};

}; // namespace isc::dhcp
}; // namespace isc

#endif
