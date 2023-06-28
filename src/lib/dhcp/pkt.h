// Copyright (C) 2014-2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef PKT_H
#define PKT_H

#include <asiolink/io_address.h>
#include <util/buffer.h>
#include <dhcp/option.h>
#include <dhcp/hwaddr.h>
#include <dhcp/classify.h>
#include <hooks/callout_handle_associate.h>

#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/shared_ptr.hpp>

#include <limits>
#include <utility>

namespace isc {

namespace dhcp {

/// @brief A value used to signal that the interface index was not set.
/// That means that more than UNSET_IFINDEX interfaces are not supported.
/// That's fine, since it would have overflowed with UNSET_IFINDEX + 1 anyway.
constexpr unsigned int UNSET_IFINDEX = std::numeric_limits<unsigned int>::max();

/// @brief RAII object enabling copying options retrieved from the
/// packet.
///
/// This object enables copying retrieved options from a packet within
/// a scope in which this object exists. When the object goes out of scope
/// copying options is disabled. This is applicable in cases when the
/// server is going to invoke a callout (hook library) where copying options
/// must be enabled by default. When the callouts return copying options
/// should be disabled. The use of RAII object eliminates the need for
/// explicitly re-disabling options copying and is safer in case of
/// exceptions thrown by callouts and a presence of multiple exit points.
///
/// @tparam PktType Type of the packet, e.g. Pkt4, Pkt6, Pkt4o6.
template<typename PktType>
class ScopedEnableOptionsCopy {
public:

    /// @brief Pointer to an encapsulated packet.
    typedef boost::shared_ptr<PktType> PktTypePtr;

    /// @brief Constructor.
    ///
    /// Enables options copying on a packet(s).
    ///
    /// @param pkt1 Pointer to first packet.
    /// @param pkt2 Optional pointer to the second packet.
    ScopedEnableOptionsCopy(const PktTypePtr& pkt1,
                            const PktTypePtr& pkt2 = PktTypePtr())
        : pkts_(pkt1, pkt2) {
        if (pkt1) {
            pkt1->setCopyRetrievedOptions(true);
        }
        if (pkt2) {
            pkt2->setCopyRetrievedOptions(true);
        }
    }

    /// @brief Destructor.
    ///
    /// Disables options copying on a packets.
    ~ScopedEnableOptionsCopy() {
        if (pkts_.first) {
            pkts_.first->setCopyRetrievedOptions(false);
        }
        if (pkts_.second) {
            pkts_.second->setCopyRetrievedOptions(false);
        }
    }

private:

    /// @brief Holds a pair of pointers of the packets.
    std::pair<PktTypePtr, PktTypePtr> pkts_;
};

/// @brief Base class for classes representing DHCP messages.
///
/// This is a base class that holds common information (e.g. source
/// and destination ports) and operations (e.g. add, get, delete options)
/// for derived classes representing both DHCPv4 and DHCPv6 messages.
/// The @c Pkt4 and @c Pkt6 classes derive from it.
///
/// @note This is abstract class. Please instantiate derived classes
/// such as @c Pkt4 or @c Pkt6.
class Pkt : public hooks::CalloutHandleAssociate {
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
    isc::util::OutputBuffer& getBuffer() {
        return (buffer_out_);
    }

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
    /// @return Pointer to "const" string containing DHCP message name.
    /// The implementations in the derived classes should statically
    /// allocate returned strings and the caller must not release the
    /// returned pointer.
    virtual const char* getName() const = 0;

    /// @brief Sets transaction-id value.
    ///
    /// @param transid transaction-id to be set.
    void setTransid(uint32_t transid) {
        transid_ = transid;
    }

    /// @brief Returns value of transaction-id field.
    ///
    /// @return transaction-id
    uint32_t getTransid() const {
        return (transid_);
    }

    /// @brief Checks whether a client belongs to a given class.
    ///
    /// @param client_class name of the class
    /// @return true if belongs
    bool inClass(const isc::dhcp::ClientClass& client_class);

    /// @brief Adds a specified class to the packet.
    ///
    /// A class can be added to the same packet repeatedly. Any additional
    /// attempts to add to a packet the class already added, will be
    /// ignored silently.
    ///
    /// @param client_class name of the class to be added
    /// @param required the class is marked for required evaluation
    void addClass(const isc::dhcp::ClientClass& client_class,
                  bool required = false);

    /// @brief Adds a specified subclass to the packet.
    ///
    /// A subclass can be added to the same packet repeatedly. Any additional
    /// attempts to add to a packet the subclass already added, will be
    /// ignored silently.
    ///
    /// @param class_def name of the class definition to be added
    /// @param subclass name of the subclass to be added
    void addSubClass(const isc::dhcp::ClientClass& class_def,
                     const isc::dhcp::ClientClass& subclass);

    /// @brief Returns the class set
    ///
    /// @note This should be used only to iterate over the class set.
    /// @param required return classes or required to be evaluated classes.
    /// @return if required is false (the default) the classes the
    /// packet belongs to else the classes which are required to be
    /// evaluated.
    const ClientClasses& getClasses(bool required = false) const {
        return (!required ? classes_ : required_classes_);
    }

    /// @brief Returns the class set including template classes associated with
    /// subclasses
    ///
    /// @note This should be used only to iterate over the class set.
    /// @note SubClasses are always last.
    /// @param required return classes or required to be evaluated classes.
    /// @return if required is false (the default) the classes the
    /// packet belongs to else the classes which are required to be
    /// evaluated.
    const SubClassRelationContainer& getSubClassesRelations() const {
        return (subclasses_);
    }

    /// @brief Unparsed data (in received packets).
    ///
    /// @warning This public member is accessed by derived
    /// classes directly. One of such derived classes is
    /// @ref perfdhcp::PerfPkt6. The impact on derived classes'
    /// behavior must be taken into consideration before making
    /// changes to this member such as access scope restriction or
    /// data format change etc.
    OptionBuffer data_;

protected:

    /// @brief Returns the first option of specified type without copying.
    ///
    /// This method is internally used by the @ref Pkt class and derived
    /// classes to retrieve a pointer to the specified option. This
    /// method doesn't copy the option before returning it to the
    /// caller.
    ///
    /// @param type Option type.
    ///
    /// @return Pointer to the option of specified type or NULL pointer
    /// if such option is not present.
    OptionPtr getNonCopiedOption(const uint16_t type) const;

    /// @brief Returns all option instances of specified type without
    /// copying.
    ///
    /// This is a variant of @ref getOptions method, which returns a collection
    /// of options without copying them. This method should be only used by
    /// the @ref Pkt6 class and derived classes. Any external callers should
    /// use @ref getOptions which copies option instances before returning them
    /// when the @ref Pkt::copy_retrieved_options_ flag is set to true.
    ///
    /// @param opt_type Option code.
    ///
    /// @return Collection of options found.
    OptionCollection getNonCopiedOptions(const uint16_t opt_type) const;

public:

    /// @brief Clones all options so that they can be safely modified.
    ///
    /// @return A container with option clones.
    OptionCollection cloneOptions();

    /// @brief Returns the first option of specified type.
    ///
    /// Returns the first option of specified type. Note that in DHCPv6 several
    /// instances of the same option are allowed (and frequently used).
    ///
    /// The options will be only returned after unpack() is called.
    ///
    /// @param type option type we are looking for
    ///
    /// @return pointer to found option (or NULL)
    OptionPtr getOption(const uint16_t type);

    /// @brief Returns all instances of specified type.
    ///
    /// Returns all instances of options of the specified type. DHCPv6 protocol
    /// allows (and uses frequently) multiple instances.
    ///
    /// @param type option type we are looking for
    /// @return instance of option collection with requested options
    isc::dhcp::OptionCollection getOptions(const uint16_t type);

    /// @brief Controls whether the option retrieved by the @ref Pkt::getOption
    /// should be copied before being returned.
    ///
    /// Setting this value to true enables the mechanism of copying options
    /// retrieved from the packet to prevent accidental modifications of
    /// options that shouldn't be modified. The typical use case for this
    /// mechanism is to prevent hook library from modifying instance of
    /// an option within the packet that would also affect the value for
    /// this option within the Kea configuration structures.
    ///
    /// Kea doesn't copy option instances which it stores in the packet.
    /// It merely copy pointers into the packets. Thus, any modification
    /// to an option would change the value of this option in the
    /// Kea configuration. To prevent this, option copying should be
    /// enabled prior to passing the pointer to a packet to a hook library.
    ///
    /// Not only does this method cause the server to copy
    /// an option, but the copied option also replaces the original
    /// option within the packet. The option can be then freely modified
    /// and the modifications will only affect the instance of this
    /// option within the packet but not within the server configuration.
    ///
    /// @param copy Indicates if the options should be copied when
    /// retrieved (if true), or not copied (if false).
    virtual void setCopyRetrievedOptions(const bool copy) {
        copy_retrieved_options_ = copy;
    }

    /// @brief Returns whether the copying of retrieved options is enabled.
    ///
    /// Also see @ref setCopyRetrievedOptions.
    ///
    /// @return true if retrieved options are copied.
    bool isCopyRetrievedOptions() const {
        return (copy_retrieved_options_);
    }

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
    void setIndex(const unsigned int ifindex) {
        ifindex_ = ifindex;
    }

    /// @brief Resets interface index to negative value.
    void resetIndex() {
        ifindex_ = UNSET_IFINDEX;
    }

    /// @brief Returns interface index.
    ///
    /// @return interface index
    int getIndex() const {
        return (ifindex_);
    }

    /// @brief Checks if interface index has been set.
    ///
    /// @return true if interface index set, false otherwise.
    bool indexSet() const {
        return (ifindex_ != UNSET_IFINDEX);
    }

    /// @brief Returns interface name.
    ///
    /// Returns interface name over which packet was received or is
    /// going to be transmitted.
    ///
    /// @return interface name
    std::string getIface() const {
        return (iface_);
    }

    /// @brief Sets interface name.
    ///
    /// Sets interface name over which packet was received or is
    /// going to be transmitted.
    ///
    /// @param iface The interface name
    void setIface(const std::string& iface) {
        iface_ = iface;
    }

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

    /// @brief Virtual destructor.
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
    /// @ref addClass to operate on this field.
    ClientClasses classes_;

    /// @brief Classes which are required to be evaluated.
    ///
    /// The comment on @ref classes_ applies here.
    ///
    /// Before output option processing these classes will be evaluated
    /// and if evaluation status is true added to the previous collection.
    ClientClasses required_classes_;

    /// @brief SubClasses this packet belongs to.
    ///
    /// This field is public, so the code outside of Pkt4 or Pkt6 class can
    /// iterate over existing classes. Having it public also solves the problem
    /// of returned reference lifetime. It is preferred to use @ref inClass and
    /// @ref addSubClass to operate on this field.
    SubClassRelationContainer subclasses_;

    /// @brief Collection of options present in this message.
    ///
    /// @warning This public member is accessed by derived
    /// classes directly. One of such derived classes is
    /// @ref perfdhcp::PerfPkt6. The impact on derived classes'
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
    unsigned int ifindex_;

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
    /// @ref perfdhcp::PerfPkt6. The impact on derived classes'
    /// behavior must be taken into consideration before making
    /// changes to this member such as access scope restriction or
    /// data format change etc.
    isc::util::OutputBuffer buffer_out_;

    /// @brief Indicates if a copy of the retrieved option should be
    /// returned when @ref Pkt::getOption is called.
    ///
    /// @see the documentation for @ref Pkt::setCopyRetrievedOptions.
    bool copy_retrieved_options_;

    /// packet timestamp
    boost::posix_time::ptime timestamp_;

    // remote HW address (src if receiving packet, dst if sending packet)
    HWAddrPtr remote_hwaddr_;

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
    /// @throw isc::OutOfRange if invalid HW address specified.
    virtual void setHWAddrMember(const uint8_t htype, const uint8_t hlen,
                                 const std::vector<uint8_t>& hw_addr,
                                 HWAddrPtr& storage);
};

/// @brief A pointer to either Pkt4 or Pkt6 packet
typedef boost::shared_ptr<isc::dhcp::Pkt> PktPtr;

/// @brief RAII object enabling duplication of the stored options and restoring
/// the original options on destructor.
///
/// This object enables duplication of the stored options and restoring the
/// original options on destructor. When the object goes out of scope, the
/// initial options are restored. This is applicable in cases when the server is
/// going to invoke a callout (hook library) where the list of options in the
/// packet will be modified. This can also be used to restore the initial
/// suboptions of an option when the suboptions are changed (e.g. when splitting
/// long options and suboptions). The use of RAII object eliminates the need for
/// explicitly copying and restoring the list of options and is safer in case of
/// exceptions thrown by callouts and a presence of multiple exit points.
class ScopedSubOptionsCopy {
public:

    /// @brief Constructor.
    ///
    /// Creates a copy of the initial options on an option.
    ///
    /// @param opt Pointer to the option.
    ScopedSubOptionsCopy(const OptionPtr& opt) : option_(opt) {
        if (opt) {
            options_ = opt->getMutableOptions();
        }
    }

    /// @brief Destructor.
    ///
    /// Restores the initial options on a packet.
    ~ScopedSubOptionsCopy() {
        if (option_) {
            option_->getMutableOptions() = options_;
        }
    }

private:

    /// @brief Holds a pointer to the option.
    OptionPtr option_;

    /// @brief Holds the initial options.
    OptionCollection options_;
};

/// @brief RAII object enabling duplication of the stored options and restoring
/// the original options on destructor.
///
/// This object enables duplication of the stored options and restoring the
/// original options on destructor. When the object goes out of scope, the
/// initial options are restored. This is applicable in cases when the server is
/// going to invoke a callout (hook library) where the list of options in the
/// packet will be modified. The use of RAII object eliminates the need for
/// explicitly copying and restoring the list of options and is safer in case of
/// exceptions thrown by callouts and a presence of multiple exit points.
///
/// @tparam PktType Type of the packet, e.g. Pkt4, Pkt6, Pkt4o6.
template<typename PktType>
class ScopedPktOptionsCopy {
public:

    /// @brief Constructor.
    ///
    /// Creates a copy of the initial options on a packet.
    ///
    /// @param pkt Pointer to the packet.
    ScopedPktOptionsCopy(PktType& pkt) : pkt_(pkt), options_(pkt.options_) {
        pkt_.options_ = pkt_.cloneOptions();
    }

    /// @brief Destructor.
    ///
    /// Restores the initial options on a packet.
    ~ScopedPktOptionsCopy() {
        pkt_.options_ = options_;
    }

private:

    /// @brief Holds a reference to the packet.
    PktType& pkt_;

    /// @brief Holds the initial options.
    OptionCollection options_;
};

} // end of namespace isc::dhcp
} // end of namespace isc

#endif
