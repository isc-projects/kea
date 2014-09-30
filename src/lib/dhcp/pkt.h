// Copyright (C) 2014 Internet Systems Consortium, Inc. ("ISC")
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

/// @brief Base class for DHCPv4 (Pkt4) and DHCPv6 (Pkt6) classes
///
/// This is a base class that holds all common information (e.g. source and
/// destination ports) and operations (e.g. add, get, delete options).
/// This class is purely virtual. Please instantiate Pkt4, Pkt6 or any
/// other derived classes.
class Pkt {
protected:
Pkt(uint32_t transid, const isc::asiolink::IOAddress& local_addr,
    const isc::asiolink::IOAddress& remote_addr, uint16_t local_port,
    uint16_t remote_port)
        :transid_(transid),
        iface_(""),
        ifindex_(-1),
        local_addr_(local_addr),
        remote_addr_(remote_addr),
        local_port_(local_port),
        remote_port_(remote_port),
        buffer_out_(0)
        {
        }

    Pkt(const uint8_t* buf, uint32_t len, const isc::asiolink::IOAddress& local_addr,
        const isc::asiolink::IOAddress& remote_addr, uint16_t local_port,
        uint16_t remote_port)
       :transid_(0),
        iface_(""),
        ifindex_(-1),
        local_addr_(local_addr),
        remote_addr_(remote_addr),
        local_port_(local_port),
        remote_port_(remote_port),
        buffer_out_(0)
    {
        data_.resize(len);
        memcpy(&data_[0], buf, len);
    }

public:

    /// @brief Prepares on-wire format of DHCP (either v4 or v6) packet.
    ///
    /// Prepares on-wire format of message and all its options.
    /// Options must be stored in options_ field.
    /// Output buffer will be stored in buffer_out_.
    /// The buffer_out_ is cleared before writting to the buffer.
    ///
    /// @note This is a pure virtual method. Actual implementations are in
    /// Pkt4 and Pkt6 class.
    ///
    /// @throw InvalidOperation if packing fails
    virtual void pack() = 0;

    /// @brief Parses on-wire form of DHCP (either v4 or v6) packet.
    ///
    /// Parses received packet, stored in on-wire format in bufferIn_.
    ///
    /// Will create a collection of option objects that will
    /// be stored in options_ container.
    ///
    /// @note This is a pure virtual method. Actual implementations are in
    /// Pkt4 and Pkt6 class.
    ///
    /// Method with throw exception if packet parsing fails.
    ///
    /// @todo Pkt4 throws exceptions when unpacking fails, while Pkt6
    ///       catches exceptions and returns false. We need to unify that
    ///       behavior one day (most likely using exceptions and turning
    ///       return type to void).
    ///
    /// @return true if unpack was successful
    virtual bool unpack() = 0;

    /// @brief Returns reference to output buffer.
    ///
    /// Returned buffer will contain reasonable data only for
    /// output (TX) packet and after pack() was called. This buffer
    /// is only valid till Pkt{4,6} object is valid.
    ///
    /// RX packet or TX packet before pack() will return buffer with
    /// zero length. This buffer is returned as non-const, so hooks
    /// framework (and user's callouts) can modify them if needed
    ///
    /// @return reference to output buffer
    isc::util::OutputBuffer& getBuffer() { return (buffer_out_); };

    /// Adds an option to this packet.
    ///
    /// Sadly, we need to have 2 versions of that method. One that
    /// accepts duplicates (DHCPv6) and one that does not (DHCPv4)
    ///
    /// @param opt option to be added.
    virtual void addOption(const OptionPtr& opt);

    /// Attempts to delete first suboption of requested type
    ///
    /// @param type Type of option to be deleted.
    ///
    /// @return true if option was deleted, false if no such option existed
    bool delOption(uint16_t type);

    /// @brief Returns text representation of the packet.
    ///
    /// This function is useful mainly for debugging.
    ///
    /// @note This is pure virtual method. Actual implementations are in
    ///       Pkt4 and Pkt6 classes.
    ///
    /// @return string with text representation
    virtual std::string toText() = 0;

    /// Returns packet type
    ///
    /// For DHCPv6, this is a straightforward operation (read packet field), but
    /// for DHCPv4 it requires finding appropriate option (that may or may not
    /// be present).
    virtual size_t len() = 0;

    /// Returns message type (e.g. 1 = SOLICIT)
    ///
    /// This is a pure virtual method. DHCPv4 stores type in option 53 and
    /// DHCPv6 stores it in the header.
    ///
    /// @return message type
    virtual uint8_t getType() const = 0;

    /// Sets message type (e.g. 1 = SOLICIT)
    ///
    /// This is a pure virtual method. DHCPv4 stores type in option 53 and
    /// DHCPv6 stores it in the header.
    ///
    /// @param type message type to be set
    virtual void setType(uint8_t type) = 0;

    /// @brief Sets transaction-id value
    ///
    /// @param transid transaction-id to be set.
    void setTransid(uint32_t transid) { transid_ = transid; }

    /// Returns value of transaction-id field
    ///
    /// @return transaction-id
    uint32_t getTransid() const { return (transid_); };

    /// @brief Classes this packet belongs to.
    ///
    /// This field is public, so the code outside of Pkt4 or Pkt6 class can
    /// iterate over existing classes. Having it public also solves the problem
    /// of returned reference lifetime. It is preferred to use @ref inClass and
    /// @ref addClass should be used to operate on this field.
    ClientClasses classes_;

    /// @brief Checks whether a client belongs to a given class
    ///
    /// @param client_class name of the class
    /// @return true if belongs
    bool inClass(const isc::dhcp::ClientClass& client_class);

    /// @brief Adds packet to a specified class
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

    /// unparsed data (in received packets)
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
    /// Also see \ref getOptions().
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
    /// received packet. Received packet is stored in bufferIn_, but
    /// transmitted data is stored in buffer_out_. If we want to send packet
    /// that we just received, a copy between those two buffers is necessary.
    void repack();

    /// collection of options present in this message
    ///
    /// @warning This public member is accessed by derived
    /// classes directly. One of such derived classes is
    /// @ref perfdhcp::PerfPkt6. The impact on derived clasess'
    /// behavior must be taken into consideration before making
    /// changes to this member such as access scope restriction or
    /// data format change etc.
    isc::dhcp::OptionCollection options_;

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

    /// @brief Returns remote IP address
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

    /// @brief Sets local port.
    ///
    /// @param local specifies local port
    void setLocalPort(uint16_t local) {
        local_port_ = local;
    }

    /// @brief Returns local port.
    ///
    /// @return local port
    uint16_t getLocalPort() const {
        return (local_port_);
    }

    /// @brief Sets remote port.
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
    std::string getIface() const { return iface_; };

    /// @brief Sets interface name.
    ///
    /// Sets interface name over which packet was received or is
    /// going to be transmitted.
    ///
    /// @return interface name
    void setIface(const std::string& iface ) { iface_ = iface; };

    /// @brief Sets remote HW address.
    ///
    /// Sets hardware address from an existing HWAddr structure.
    /// The remote address is a destination address for outgoing
    /// packet and source address for incoming packet. When this
    /// is an outgoing packet, this address will be used to
    /// construct the link layer header.
    ///
    /// @param addr structure representing HW address.
    ///
    /// @throw BadValue if addr is null
    void setRemoteHWAddr(const HWAddrPtr& addr);

    /// @brief Sets remote HW address.
    ///
    /// Sets the destination HW address for the outgoing packet
    /// or source HW address for the incoming packet. When this
    /// is an outgoing packet this address will be used to construct
    /// the link layer header.
    ///
    /// @note mac_addr must be a buffer of at least hlen bytes.
    ///
    /// @param htype hardware type (will be sent in htype field)
    /// @param hlen hardware length (will be sent in hlen field)
    /// @param mac_addr pointer to hardware address
    void setRemoteHWAddr(const uint8_t htype, const uint8_t hlen,
                         const std::vector<uint8_t>& mac_addr);

    /// @brief Returns the remote HW address.
    ///
    /// @return remote HW address.
    HWAddrPtr getRemoteHWAddr() const {
        return (remote_hwaddr_);
    }

    /// @brief virtual desctructor
    ///
    /// There is nothing to clean up here, but since there are virtual methods,
    /// we define virtual destructor to ensure that derived classes will have
    /// a virtual one, too.
    virtual ~Pkt() {
    }

protected:

    /// transaction-id (32 bits for v4, 24 bits for v6)
    uint32_t transid_;

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

    /// Output buffer (used during message transmission)
    ///
    /// @warning This protected member is accessed by derived
    /// classes directly. One of such derived classes is
    /// @ref perfdhcp::PerfPkt6. The impact on derived clasess'
    /// behavior must be taken into consideration before making
    /// changes to this member such as access scope restriction or
    /// data format change etc.
    ///
    /// @warning This public member is accessed by derived
    /// classes directly. One of such derived classes is
    /// @ref perfdhcp::PerfPkt4. The impact on derived clasess'
    /// behavior must be taken into consideration before making
    /// changes to this member such as access scope restriction or
    /// data format change etc. This field is also public, because
    /// it may be modified by callouts (which are written in C++ now,
    /// but we expect to also have them in Python, so any accesibility
    /// methods would overly complicate things here and degrade
    /// performance).
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
    /// @param mac_addr pointer to actual hardware address.
    /// @param [out] hw_addr pointer to a class member to be modified.
    ///
    /// @trow isc::OutOfRange if invalid HW address specified.
    virtual void setHWAddrMember(const uint8_t htype, const uint8_t hlen,
                                 const std::vector<uint8_t>& mac_addr,
                                 HWAddrPtr& hw_addr);
};

}; // namespace isc::dhcp
}; // namespace isc

#endif
