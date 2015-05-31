// Copyright (C) 2011-2015 Internet Systems Consortium, Inc. ("ISC")
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
#include <dhcp/pkt.h>

#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/shared_array.hpp>
#include <boost/shared_ptr.hpp>

#include <iostream>
#include <set>

#include <time.h>

namespace isc {

namespace dhcp {

class Pkt6;

/// @brief A pointer to Pkt6 packet
typedef boost::shared_ptr<Pkt6> Pkt6Ptr;

/// @brief Represents a DHCPv6 packet
///
/// This class represents a single DHCPv6 packet. It handles both incoming
/// and transmitted packets, parsing incoming options, options handling
/// (add, get, remove), on-wire assembly, sanity checks and other operations.
/// This specific class has several DHCPv6-specific methods, but it uses a lot
/// of common operations from its base @c Pkt class that is shared with Pkt4.
///
/// This class also handles relayed packets. For example, a RELAY-FORW message
/// with a SOLICIT inside will be represented as SOLICIT and the RELAY-FORW
/// layers will be stored in relay_info_ vector.
class Pkt6 : public Pkt {
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

    /// @brief defines relay search pattern
    ///
    /// Defines order in which options are searched in a message that
    /// passed through mulitple relays. RELAY_SEACH_FROM_CLIENT will
    /// start search from the relay that was the closest to the client
    /// (i.e. innermost in the encapsulated message, which also means
    /// this was the first relay that forwarded packet received by the
    /// server and this will be the last relay that will handle the
    /// response that server sent towards the client.).
    /// RELAY_SEARCH_FROM_SERVER is the opposite. This will be the
    /// relay closest to the server (i.e. outermost in the encapsulated
    /// message, which also means it was the last relay that relayed
    /// the received message and will be the first one to process
    /// server's response). RELAY_GET_FIRST will try to get option from
    /// the first relay only (closest to the client), RELAY_GET_LAST will
    /// try to get option form the the last relay (closest to the server).
    enum RelaySearchOrder {
        RELAY_SEARCH_FROM_CLIENT = 1,
        RELAY_SEARCH_FROM_SERVER = 2,
        RELAY_GET_FIRST = 3,
        RELAY_GET_LAST = 4
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
        isc::dhcp::OptionCollection options_;
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
    /// The output buffer is cleared before new data is written to it.
    ///
    /// @throw BadValue if packet protocol is invalid, InvalidOperation
    /// if packing fails, or NotImplemented if protocol is TCP (IPv6 over TCP is
    /// not yet supported).
    virtual void pack();

    /// @brief Dispatch method that handles binary packet parsing.
    ///
    /// This method calls appropriate dispatch function (unpackUDP or
    /// unpackTCP).
    ///
    /// @throw tbd
    virtual void unpack();

    /// @brief Returns protocol of this packet (UDP or TCP).
    ///
    /// @return protocol type
    DHCPv6Proto getProto();

    /// @brief Sets protocol of this packet.
    ///
    /// @param proto protocol (UDP or TCP)
    void setProto(DHCPv6Proto proto = UDP) {
        proto_ = proto;
    }

    /// @brief Returns text representation of the packet.
    ///
    /// This function is useful mainly for debugging.
    ///
    /// @return string with text representation
    virtual std::string toText() const;

    /// @brief Returns the begin of the (possibly relayed) packet
    const uint8_t* rawBegin() const {
        return (raw_begin_);
    }

    /// @brief Returns the end of the (possibly relayed) packet
    const uint8_t* rawEnd() const {
        return (raw_end_);
    }

    /// @brief Returns the offset of the signature option (or 0)
    size_t getSignatureOffset() const {
        return (signature_offset_);
    }

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
    virtual size_t len();

    /// @brief Returns message type (e.g. 1 = SOLICIT).
    ///
    /// @return message type
    virtual uint8_t getType() const { return (msg_type_); }

    /// @brief Sets message type (e.g. 1 = SOLICIT).
    ///
    /// @param type message type to be set
    virtual void setType(uint8_t type) { msg_type_=type; };

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

    /// @brief Return first instance of a specified option
    ///
    /// When a client's packet traverses multiple relays, each passing relay may
    /// insert extra options. This method allows the specific instance of a given
    /// option to be obtained (e.g. closest to the client, closest to the server,
    /// etc.) See @ref RelaySearchOrder for a detailed description.
    ///
    /// @param option_code searched option
    /// @param order option search order (see @ref RelaySearchOrder)
    /// @return option pointer (or NULL if no option matches specified criteria)
    OptionPtr getAnyRelayOption(uint16_t option_code, RelaySearchOrder order);

    /// @brief Returns all instances of specified type.
    ///
    /// Returns all instances of options of the specified type. DHCPv6 protocol
    /// allows (and uses frequently) multiple instances.
    ///
    /// @param type option type we are looking for
    /// @return instance of option collection with requested options
    isc::dhcp::OptionCollection getOptions(uint16_t type);

    /// @brief add information about one traversed relay
    ///
    /// This adds information about one traversed relay, i.e.
    /// one relay-forw or relay-repl level of encapsulation.
    ///
    /// @param relay structure with necessary relay information
    void addRelayInfo(const RelayInfo& relay);

    /// @brief Returns name of the DHCPv6 message.
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
    static const char* getName(const uint8_t type);

    /// @brief returns textual representation of packet type.
    ///
    /// This method requires an object. There is also static version, which
    /// requires one parameter (type).
    ///
    /// @return Pointer to "const" string containing packet name.
    ///         Note that this string is statically allocated and MUST NOT
    ///         be freed by the caller.
    const char* getName() const;

    /// @brief copies relay information from client's packet to server's response
    ///
    /// This information is not simply copied over. Some parameter are
    /// removed, msg_type_is updated (RELAY-FORW => RELAY-REPL), etc.
    ///
    /// @param question client's packet
    void copyRelayInfo(const Pkt6Ptr& question);

    /// @brief Relay information.
    ///
    /// This is a public field. Otherwise we hit one of the two problems:
    /// we return reference to an internal field (and that reference could
    /// be potentially used past Pkt6 object lifetime causing badness) or
    /// we return a copy (which is inefficient and also causes any updates
    /// to be impossible). Therefore public field is considered the best
    /// (or least bad) solution.
    ///
    /// This vector is arranged in the order packet is encapsulated, i.e.
    /// relay[0] was the outermost encapsulation (relay closest to the server),
    /// relay[last] was the innermost encapsulation (relay closest to the
    /// client).
    std::vector<RelayInfo> relay_info_;

protected:

    /// @brief Attempts to generate MAC/Hardware address from IPv6 link-local
    ///        address.
    ///
    /// This method uses source IPv6 address for direct messages and the
    /// peeraddr or the first relay that saw that packet. It may fail if the
    /// address is not link-local or does not use EUI-64 identifier.
    ///
    /// @return Hardware address (or NULL)
    virtual HWAddrPtr getMACFromSrcLinkLocalAddr();

    /// @brief Extract MAC/Hardware address from client link-layer address
    //         option inserted by a relay agent (RFC6939).
    ///
    /// This method extracts the client's hardware address from the
    //  client-linklayer-addr option inserted by the relay agent closest to
    //  the client.
    ///
    /// @return Hardware address (or NULL)
    virtual HWAddrPtr getMACFromIPv6RelayOpt();

    /// @brief Extract MAC/Hardware address from client-id.
    ///
    /// This method attempts to extract MAC/Hardware address from DUID sent
    /// as client-id. This method may fail, as only DUID-LLT and DUID-LL are
    /// based on link-layer addresses. Client may use other valid DUID types
    /// and this method will fail.
    ///
    /// @return Hardware address (or NULL)
    virtual HWAddrPtr getMACFromDUID();

    /// @brief Attempts to extract MAC/Hardware address from DOCSIS options
    ///        inserted by the modem itself.
    ///
    /// The mechanism extracts that information from DOCSIS option
    /// (vendor-specific info, vendor-id=4491, suboption 36). Note that
    /// in a DOCSIS capable network, the MAC address information is provided
    /// several times. The first is specified by the modem itself. The second
    /// is added by the CMTS, which acts as a relay agent. This method
    /// attempts to extract the former. See @ref getMACFromDocsisCMTS
    /// for a similar method that extracts from the CMTS (relay) options.
    ///
    /// @return hardware address (if DOCSIS suboption 36 is present)
    virtual HWAddrPtr getMACFromDocsisModem();

    /// @brief Attempts to extract MAC/Hardware address from DOCSIS options.
    ///
    /// The DHCPv6 mechanism extracts that information from DOCSIS option
    /// (vendor-specific info, vendor-id=4491, suboption 1026). Note that
    /// in a DOCSIS capable network, the MAC address information is provided
    /// several times. The first is specified by the modem itself. The second
    /// is added by the CMTS, which acts as a relay agent. This method
    /// attempts to extract the latter. See @ref getMACFromDocsisModem
    /// for a similar method that extracts from the modem (client) options.
    ///
    /// @return hardware address (if DOCSIS suboption 1026 is present)
    virtual HWAddrPtr getMACFromDocsisCMTS();

    /// @brief Attempts to obtain MAC address from remote-id relay option.
    ///
    /// This method is called from getMAC(HWADDR_SOURCE_REMOTE_ID) and should not be
    /// called directly. It will attempt to extract MAC address information
    /// from remote-id option inserted by a relay agent closest to the client.
    /// If this method fails, it will return NULL.
    ///
    /// @return hardware address (or NULL)
    virtual HWAddrPtr getMACFromRemoteIdRelayOption();

    /// @brief Builds on wire packet for TCP transmission.
    ///
    /// @todo This function is not implemented yet.
    ///
    /// @throw NotImplemented, IPv6 over TCP is not yet supported.
    void packTCP();

    /// @brief Builds on wire packet for UDP transmission.
    ///
    /// @throw InvalidOperation if packing fails
    void packUDP();

    /// @brief Parses on-wire form of TCP DHCPv6 packet.
    ///
    /// Parses received packet, stored in on-wire format in data_.
    /// data_len_ must be set to indicate data length.
    /// Will create a collection of option objects that will
    /// be stored in options_ container.
    ///
    /// @todo This function is not implemented yet.
    ///
    /// @throw tbd
    void unpackTCP();

    /// @brief Parses on-wire form of UDP DHCPv6 packet.
    ///
    /// Parses received packet, stored in on-wire format in data_.
    /// data_len_ must be set to indicate data length.
    /// Will create a collection of option objects that will
    /// be stored in options_ container.
    ///
    /// @throw tbd
    void unpackUDP();

    /// @brief Unpacks direct (non-relayed) message.
    ///
    /// This method unpacks specified buffer range as a direct
    /// (e.g. solicit or request) message. This method is called from
    /// unpackUDP() when received message is detected to be direct.
    ///
    /// @param begin start of the buffer
    /// @param end end of the buffer
    /// @throw tbd
    void unpackMsg(OptionBufferConstIter begin, OptionBufferConstIter end);

    /// @brief Unpacks relayed message (RELAY-FORW or RELAY-REPL).
    ///
    /// This method is called from unpackUDP() when received message
    /// is detected to be relay-message. It goes iteratively over
    /// all relays (if there are multiple encapsulation levels).
    ///
    /// @throw tbd
    void unpackRelayMsg();

    /// @brief Calculates overhead introduced in specified relay.
    ///
    /// It is used when calculating message size and packing message
    /// @param relay RelayInfo structure that holds information about relay
    /// @return number of bytes needed to store relay information
    uint16_t getRelayOverhead(const RelayInfo& relay) const;

    /// @brief Calculates overhead for all relays defined for this message.
    /// @return number of bytes needed to store all relay information
    uint16_t calculateRelaySizes();

    /// @brief Calculates size of the message as if it was not relayed at all.
    ///
    /// This is equal to len() if the message was not relayed.
    /// @return number of bytes required to store the message
    uint16_t directLen() const;

    /// UDP (usually) or TCP (bulk leasequery or failover)
    DHCPv6Proto proto_;

    /// DHCPv6 message type
    uint8_t msg_type_;

    /// Begin of the raw packet
    const uint8_t* raw_begin_;

    /// End of the raw packet
    const uint8_t* raw_end_;

    /// Offset of the signature option
    size_t signature_offset_;

}; // Pkt6 class

} // isc::dhcp namespace

} // isc namespace

#endif
