// Copyright (C) 2011-2013 Internet Systems Consortium, Inc. ("ISC")
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

#include <asiolink/io_address.h>
#include <dhcp/option.h>

#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/shared_array.hpp>
#include <boost/shared_ptr.hpp>

#include <iostream>

#include <time.h>

namespace isc {

namespace dhcp {

class Pkt6 {
public:
    /// specifies non-relayed DHCPv6 packet header length (over UDP)
    const static size_t DHCPV6_PKT_HDR_LEN = 4;

    /// specifies relay DHCPv6 packet header length (over UDP)
    const static size_t DHCPV6_RELAY_HDR_LEN = 34;

    /// DHCPv6 transport protocol
    enum DHCPv6Proto {
        UDP = 0, // most packets are UDP
        TCP = 1  // there are TCP DHCPv6 packets (bulk leasequery, failover)
    };


    /// @brief structure that describes a single relay information
    ///
    /// Client sends messages. Each relay along its way will encapsulate the message.
    /// This structure represents all information added by a single relay.
    struct RelayInfo {

        /// @brief default constructor
        RelayInfo();
        uint8_t   msg_type_;               ///< message type (RELAY-FORW oro RELAY-REPL)
        uint8_t   hop_count_;              ///< number of traversed relays (up to 32)
        isc::asiolink::IOAddress linkaddr_;///< fixed field in relay-forw/relay-reply
        isc::asiolink::IOAddress peeraddr_;///< fixed field in relay-forw/relay-reply

        /// @brief length of the relay_msg_len
        /// Used when calculating length during pack/unpack
        uint16_t  relay_msg_len_;

        /// options received from a specified relay, except relay-msg option
        isc::dhcp::Option::OptionCollection options_;
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
    uint8_t getType() const { return (msg_type_); }

    /// Sets message type (e.g. 1 = SOLICIT)
    ///
    /// @param type message type to be set
    void setType(uint8_t type) { msg_type_=type; };

    /// @brief Sets transaction-id value
    ///
    /// @param transid transaction-id to be set.
    void setTransid(uint32_t transid) { transid_ = transid; }

    /// Returns value of transaction-id field
    ///
    /// @return transaction-id
    uint32_t getTransid() const { return (transid_); };

    /// Adds an option to this packet.
    ///
    /// @param opt option to be added.
    void addOption(const OptionPtr& opt);

    /// @brief Returns the first option of specified type.
    ///
    /// Returns the first option of specified type. Note that in DHCPv6 several
    /// instances of the same option are allowed (and frequently used).
    /// Also see \ref getOptions().
    ///
    /// @param type option type we are looking for
    ///
    /// @return pointer to found option (or NULL)
    OptionPtr getOption(uint16_t type);

    /// @brief returns option inserted by relay
    ///
    /// Returns an option from specified relay scope (inserted by a given relay
    /// if this is received packet or to be decapsulated by a given relay if
    /// this is a transmitted packet). nesting_level specifies which relay
    /// scope is to be used. 0 is the outermost encapsulation (relay closest to
    /// the server). pkt->relay_info_.size() - 1 is the innermost encapsulation
    /// (relay closest to the client).
    ///
    /// @throw isc::OutOfRange if nesting level has invalid value.
    ///
    /// @param option_code code of the requested option
    /// @param nesting_level see description above
    ///
    /// @return pointer to the option (or NULL if there is no such option)
    OptionPtr getRelayOption(uint16_t option_code, uint8_t nesting_level);

    /// @brief Returns all instances of specified type.
    ///
    /// Returns all instances of options of the specified type. DHCPv6 protocol
    /// allows (and uses frequently) multiple instances.
    ///
    /// @param type option type we are looking for
    /// @return instance of option collection with requested options
    isc::dhcp::Option::OptionCollection getOptions(uint16_t type);

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
    const isc::asiolink::IOAddress& getRemoteAddr() const {
        return (remote_addr_);
    }

    /// @brief Sets local address.
    ///
    /// @param local specifies local address
    void setLocalAddr(const isc::asiolink::IOAddress& local) { local_addr_ = local; }

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

    /// @brief Returns packet timestamp.
    ///
    /// Returns packet timestamp value updated when
    /// packet is received or sent.
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

    /// @brief add information about one traversed relay
    ///
    /// This adds information about one traversed relay, i.e.
    /// one relay-forw or relay-repl level of encapsulation.
    ///
    /// @param relay structure with necessary relay information
    void addRelayInfo(const RelayInfo& relay);

    /// collection of options present in this message
    ///
    /// @todo: Text mentions protected, but this is really public
    ///
    /// @warning This protected member is accessed by derived
    /// classes directly. One of such derived classes is
    /// @ref perfdhcp::PerfPkt6. The impact on derived clasess'
    /// behavior must be taken into consideration before making
    /// changes to this member such as access scope restriction or
    /// data format change etc.
    isc::dhcp::Option::OptionCollection options_;

    /// @brief Update packet timestamp.
    ///
    /// Updates packet timestamp. This method is invoked
    /// by interface manager just before sending or
    /// just after receiving it.
    /// @throw isc::Unexpected if timestamp update failed
    void updateTimestamp();

    /// @brief Return textual type of packet.
    ///
    /// Returns the name of valid packet received by the server (e.g. SOLICIT).
    /// If the packet is unknown - or if it is a valid DHCP packet but not one
    /// expected to be received by the server (such as an ADVERTISE), the string
    /// "UNKNOWN" is returned.  This method is used in debug messages.
    ///
    /// As the operation of the method does not depend on any server state, it
    /// is declared static. There is also non-static getName() method that
    /// works on Pkt6 objects.
    ///
    /// @param type DHCPv6 packet type
    ///
    /// @return Pointer to "const" string containing the packet name.
    ///         Note that this string is statically allocated and MUST NOT
    ///         be freed by the caller.
    static const char* getName(uint8_t type);

    /// @brief returns textual representation of packet type.
    ///
    /// This method requires an object. There is also static version, which
    /// requires one parameter (type).
    ///
    /// @return Pointer to "const" string containing packet name.
    ///         Note that this string is statically allocated and MUST NOT
    ///         be freed by the caller.
    const char* getName() const;

    /// relay information
    ///
    /// this is a public field. Otherwise we hit one of the two problems:
    /// we return reference to an internal field (and that reference could
    /// be potentially used past Pkt6 object lifetime causing badness) or
    /// we return a copy (which is inefficient and also causes any updates
    /// to be impossible). Therefore public field is considered the best
    /// (or least bad) solution.
    std::vector<RelayInfo> relay_info_;
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

    /// @brief unpacks direct (non-relayed) message
    ///
    /// This method unpacks specified buffer range as a direct
    /// (e.g. solicit or request) message. This method is called from
    /// unpackUDP() when received message is detected to be direct.
    ///
    /// @param begin start of the buffer
    /// @param end end of the buffer
    /// @return true if parsing was successful and there are no leftover bytes
    bool unpackMsg(OptionBuffer::const_iterator begin,
                   OptionBuffer::const_iterator end);

    /// @brief unpacks relayed message (RELAY-FORW or RELAY-REPL)
    ///
    /// This method is called from unpackUDP() when received message
    /// is detected to be relay-message. It goes iteratively over
    /// all relays (if there are multiple encapsulation levels).
    ///
    /// @return true if parsing was successful
    bool unpackRelayMsg();

    /// @brief calculates overhead introduced in specified relay
    ///
    /// It is used when calculating message size and packing message
    /// @param relay RelayInfo structure that holds information about relay
    /// @return number of bytes needed to store relay information
    uint16_t getRelayOverhead(const RelayInfo& relay) const;

    /// @brief calculates overhead for all relays defined for this message
    /// @return number of bytes needed to store all relay information
    uint16_t calculateRelaySizes();

    /// @brief calculates size of the message as if it was not relayed at all
    ///
    /// This is equal to len() if the message was not relayed.
    /// @return number of bytes required to store the message
    uint16_t directLen() const;

    /// UDP (usually) or TCP (bulk leasequery or failover)
    DHCPv6Proto proto_;

    /// DHCPv6 message type
    uint8_t msg_type_;

    /// DHCPv6 transaction-id
    uint32_t transid_;

    /// unparsed data (in received packets)
    ///
    /// @warning This protected member is accessed by derived
    /// classes directly. One of such derived classes is
    /// @ref perfdhcp::PerfPkt6. The impact on derived clasess'
    /// behavior must be taken into consideration before making
    /// changes to this member such as access scope restriction or
    /// data format change etc.
    OptionBuffer data_;

    /// name of the network interface the packet was received/to be sent over
    std::string iface_;

    /// @brief interface index
    ///
    /// interface index (each network interface has assigned unique ifindex
    /// it is functional equivalent of name, but sometimes more useful, e.g.
    /// when using crazy systems that allow spaces in interface names
    /// e.g. windows
    int ifindex_;

    /// local address (dst if receiving packet, src if sending packet)
    isc::asiolink::IOAddress local_addr_;

    /// remote address (src if receiving packet, dst if sending packet)
    isc::asiolink::IOAddress remote_addr_;

    /// local TDP or UDP port
    uint16_t local_port_;

    /// remote TCP or UDP port
    uint16_t remote_port_;

    /// output buffer (used during message transmission)
    ///
    /// @warning This protected member is accessed by derived
    /// classes directly. One of such derived classes is
    /// @ref perfdhcp::PerfPkt6. The impact on derived clasess'
    /// behavior must be taken into consideration before making
    /// changes to this member such as access scope restriction or
    /// data format change etc.
    isc::util::OutputBuffer bufferOut_;

    /// packet timestamp
    boost::posix_time::ptime timestamp_;
}; // Pkt6 class

typedef boost::shared_ptr<Pkt6> Pkt6Ptr;

} // isc::dhcp namespace

} // isc namespace

#endif
