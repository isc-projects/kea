// Copyright (C) 2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef ND_PKT_H
#define ND_PKT_H

#include <asiolink/io_address.h>
#include <util/buffer.h>

#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/shared_ptr.hpp>

#include <utility>

namespace isc {

namespace slaac {

class OptionPtr;

/// @brief Base class for classes representing ND messages.
///
/// @note This is abstract class. Please instantiate derived classes
/// such as @c RaPkt or @c RsPkt.
class NDPkt {
protected:

    /// @brief Constructor.
    ///
    /// This constructor is typically used for transmitted messages as it
    /// creates an empty (no options) packet. The constructor is protected,
    /// so only derived classes can call it. Pkt class cannot be instantiated
    /// anyway, because it is an abstract class.
    ///
    /// @param local_addr local IPv6 address
    /// @param remote_addr remote IPv6 address
    NDPkt(const isc::asiolink::IOAddress& local_addr,
        const isc::asiolink::IOAddress& remote_addr);

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
    NDPkt(const uint8_t* buf, uint32_t len,
          const isc::asiolink::IOAddress& local_addr,
          const isc::asiolink::IOAddress& remote_addr);

public:

    /// @brief Prepares on-wire format of ND packet.
    ///
    /// Prepares on-wire format of message and all its options.
    /// A caller must ensure that options are stored in options_ field
    /// prior to calling this method.
    ///
    /// Output buffer will be stored in buffer_out_.
    /// The buffer_out_ should be cleared before writing to the buffer
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

    /// @brief Returns message type (e.g. 133 = Router Solicitation).
    ///
    /// @note This is a pure virtual method and must be implemented in
    /// the derived classes. The @c Pkt4 and @c Pkt6 class have respective
    /// implementations of this method.
    ///
    /// @return message type
    virtual uint8_t getType() const = 0;

    /// @brief Sets message type (e.g. 133 = RS).
    ///
    /// @note This is a pure virtual method and must be implemented in
    /// the derived classes. The @c RAPkt and @c RSPkt class have respective
    /// implementations of this method.
    ///
    /// @param type message type to be set
    virtual void setType(uint8_t type) = 0;

    /// @brief Returns name of the ND message.
    ///
    /// For all unsupported messages the derived classes must return
    /// "UNKNOWN".
    ///
    /// @return Pointer to "const" string containing DHCP message name.
    /// The implementations in the derived classes should statically
    /// allocate returned strings and the caller must not release the
    /// returned pointer.
    virtual const char* getName() const = 0;

    /// @brief Unparsed data (in received packets).
    ///
    /// @warning This public member is accessed by derived
    /// classes directly. One of such derived classes is
    /// @ref perfdhcp::PerfPkt6. The impact on derived classes'
    /// behavior must be taken into consideration before making
    /// changes to this member such as access scope restriction or
    /// data format change etc.
    OptionBuffer data_;

public:

    /// @brief Returns the first option of specified type.
    ///
    /// Returns the first option of specified type. Note that in DHCPv6 several
    /// instances of the same option are allowed (and frequently used).
    /// Also see @ref Pkt6::getOptions().
    ///
    /// The options will be only returned after unpack() is called.
    ///
    /// @param type option type we are looking for
    ///
    /// @return pointer to found option (or NULL)
    OptionPtr getOption(const uint16_t type);

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

    /// @brief Set packet timestamp.
    ///
    /// Sets packet timestamp to arbitrary value.
    /// It is used by perfdhcp tool and should not be used elsewhere.
    void setTimestamp(boost::posix_time::ptime& timestamp) {
        timestamp_ = timestamp;
    }

    /// @brief Copies content of input buffer to output buffer.
    ///
    /// This is mostly a diagnostic function. It is being used for sending
    /// received packet. Received packet is stored in data_, but
    /// transmitted data is stored in buffer_out_. If we want to send packet
    /// that we just received, a copy between those two buffers is necessary.
    void repack();

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

    /// @brief Sets interface index.
    ///
    /// @param ifindex specifies interface index.
    void setIndex(uint32_t ifindex) {
        ifindex_ = ifindex;
    };

    /// @brief Resets interface index to negative value.
    void resetIndex() {
        ifindex_ = -1;
    }

    /// @brief Returns interface index.
    ///
    /// @return interface index
    uint32_t getIndex() const {
        return (ifindex_);
    };

    /// @brief Checks if interface index has been set.
    ///
    /// @return true if interface index set, false otherwise.
    bool indexSet() const {
        return (ifindex_ >= 0);
    }

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

    /// @brief Virtual destructor.
    ///
    /// There is nothing to clean up here, but since there are virtual methods,
    /// we define virtual destructor to ensure that derived classes will have
    /// a virtual one, too.
    virtual ~NDPkt() {
    }

    /// @brief Collection of options present in this message.
    ///
    /// @warning This public member is accessed by derived
    /// classes directly. One of such derived classes is
    /// @ref perfdhcp::PerfPkt6. The impact on derived classes'
    /// behavior must be taken into consideration before making
    /// changes to this member such as access scope restriction or
    /// data format change etc.
    isc::slaac::OptionCollection options_;

protected:

    /// Name of the network interface the packet was received/to be sent over.
    std::string iface_;

    /// @brief Interface index.
    ///
    /// Each network interface has assigned an unique ifindex.
    /// It is a functional equivalent of a name, but sometimes more useful, e.g.
    /// when using odd systems that allow spaces in interface names.
    int64_t ifindex_;

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

    /// Output buffer (used during message transmission)
    ///
    /// @warning This protected member is accessed by derived
    /// classes directly. One of such derived classes is
    /// @ref perfdhcp::PerfPkt6. The impact on derived classes'
    /// behavior must be taken into consideration before making
    /// changes to this member such as access scope restriction or
    /// data format change etc.
    isc::util::OutputBuffer buffer_out_;

    /// packet timestamp
    boost::posix_time::ptime timestamp_;

};

/// @brief A pointer to either ND packet
typedef boost::shared_ptr<isc::slaac::NDPkt> NDPktPtr;

}; // namespace isc::slaac
}; // namespace isc

#endif
