// Copyright (C) 2017 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef NETWORK_H
#define NETWORK_H

#include <asiolink/io_address.h>
#include <cc/cfg_to_element.h>
#include <cc/data.h>
#include <cc/user_context.h>
#include <dhcp/classify.h>
#include <dhcp/option.h>
#include <dhcpsrv/cfg_option.h>
#include <dhcpsrv/cfg_4o6.h>
#include <dhcpsrv/triplet.h>
#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>
#include <cstdint>
#include <string>

namespace isc {
namespace dhcp {

/// @brief Common interface representing a network to which the DHCP clients
/// are connected.
///
/// The most common type of network, in Kea's terminology, is a subnet. The
/// @ref Subnet implements this interface. Another types of objects implementing
/// this interface are @ref SharedNetwork4 and @ref SharedNetwork6 objects.
/// They group multiple subnets together to provide means for
/// extending available address pools (a single client may obtain IP
/// address from any of the pools belonging to subnets in the shared
/// network), or for selecting a subnet on a given link, depending on the
/// class of the client (e.g. cable network case: different subnet is
/// selected for cable modems, different one for routers).
///
/// The subnets and shared networks share many data structures, e.g. DHCP
/// options, local interface name, address manipulation methods, thus this
/// class provides an abstract interface that must be implemented by derived
/// classes and, where appropriate, implements common methods used by the
/// derived classes.
class Network : public virtual UserContext, public data::CfgToElement {
public:

    /// @brief Holds optional information about relay.
    ///
    /// In some cases it is beneficial to have additional information about
    /// a relay configured in the subnet. For now, the structure holds only
    /// IP address, but there may potentially be additional parameters added
    /// later, e.g. relay interface-id or relay-id.
    struct RelayInfo {

        /// @brief default and the only constructor
        ///
        /// @param addr an IP address of the relay (may be :: or 0.0.0.0)
        RelayInfo(const isc::asiolink::IOAddress& addr);

        /// @brief IP address of the relay
        isc::asiolink::IOAddress addr_;
    };

    /// @brief Specifies allowed host reservation mode.
    ///
    typedef enum  {

        /// None - host reservation is disabled. No reservation types
        /// are allowed.
        HR_DISABLED,

        /// Only out-of-pool reservations is allowed. This mode
        /// allows AllocEngine to skip reservation checks when
        /// dealing with with addresses that are in pool.
        HR_OUT_OF_POOL,

        /// Both out-of-pool and in-pool reservations are allowed. This is the
        /// most flexible mode, where sysadmin have biggest liberty. However,
        /// there is a non-trivial performance penalty for it, as the
        /// AllocEngine code has to check whether there are reservations, even
        /// when dealing with reservations from within the dynamic pools.
        HR_ALL
    } HRMode;

    /// Pointer to the RelayInfo structure
    typedef boost::shared_ptr<Network::RelayInfo> RelayInfoPtr;

    /// @brief Constructor.
    Network()
        : iface_name_(), relay_(asiolink::IOAddress::IPV4_ZERO_ADDRESS()),
          white_list_(), t1_(0), t2_(0), valid_(0),
          host_reservation_mode_(HR_ALL), cfg_option_(new CfgOption()) {
    }

    /// @brief Virtual destructor.
    ///
    /// Does nothing at the moment.
    virtual ~Network() { };

    /// @brief Sets local name of the interface for which this network is
    /// selected.
    ///
    /// If the interface is specified, the server will use the network
    /// associated with this local interface to allocate IP addresses and
    /// other resources to a client.
    ///
    /// @param iface_name Interface name.
    void setIface(const std::string& iface_name) {
        iface_name_ = iface_name;
    }

    /// @brief Returns name of the local interface for which this network is
    /// selected.
    ///
    /// @return Interface name as text.
    std::string getIface() const {
        return (iface_name_);
    };

    /// @brief Sets information about relay
    ///
    /// In some situations where there are shared subnets (i.e. two different
    /// subnets are available on the same physical link), there is only one
    /// relay that handles incoming requests from clients. In such a case,
    /// the usual subnet selection criteria based on relay belonging to the
    /// subnet being selected are no longer sufficient and we need to explicitly
    /// specify a relay. One notable example of such uncommon, but valid
    /// scenario is a cable network, where there is only one CMTS (one relay),
    /// but there are 2 distinct subnets behind it: one for cable modems
    /// and another one for CPEs and other user equipment behind modems.
    /// From manageability perspective, it is essential that modems get addresses
    /// from different subnet, so users won't tinker with their modems.
    ///
    /// Setting this parameter is not needed in most deployments.
    /// This structure holds IP address only for now, but it is expected to
    /// be extended in the future.
    ///
    /// @param relay structure that contains relay information
    void setRelayInfo(const RelayInfo& relay) {
        relay_ = relay;
    }

    /// @brief Returns const reference to relay information
    ///
    /// @note The returned reference is only valid as long as the object
    /// returned it is valid.
    ///
    /// @return const reference to the relay information
    const RelayInfo& getRelayInfo() const {
        return (relay_);
    }

    /// @brief Checks whether this network supports client that belongs to
    /// specified classes.
    ///
    /// This method checks whether a client that belongs to given classes can
    /// use this network. For example, if this class is reserved for client
    /// class "foo" and the client belongs to classes "foo", "bar" and "baz",
    /// it is supported. On the other hand, client belonging to classes
    /// "foobar" and "zyxxy" is not supported.
    ///
    /// @todo: Currently the logic is simple: client is supported if it belongs
    /// to any class mentioned in white_list_. We will eventually need a
    /// way to specify more fancy logic (e.g. to meet all classes, not just
    /// any)
    ///
    /// @param client_classes list of all classes the client belongs to
    /// @return true if client can be supported, false otherwise
    virtual bool
    clientSupported(const isc::dhcp::ClientClasses& client_classes) const;

    /// @brief Adds class class_name to the list of supported classes
    ///
    /// Also see explanation note in @ref white_list_.
    ///
    /// @param class_name client class to be supported by this subnet
    void allowClientClass(const isc::dhcp::ClientClass& class_name);

    /// @brief returns the client class white list
    ///
    /// @note The returned reference is only valid as long as the object
    /// returned it is valid.
    ///
    /// @return client classes @ref white_list_
    const isc::dhcp::ClientClasses& getClientClasses() const {
        return (white_list_);
    }

    /// @brief Return valid-lifetime for addresses in that prefix
    Triplet<uint32_t> getValid() const {
        return (valid_);
    }

    /// @brief Sets new valid lifetime for a network.
    ///
    /// @param valid New valid lifetime in seconds.
    void setValid(const Triplet<uint32_t>& valid) {
        valid_ = valid;
    }

    /// @brief Returns T1 (renew timer), expressed in seconds
    Triplet<uint32_t> getT1() const {
        return (t1_);
    }

    /// @brief Sets new renew timer for a network.
    ///
    /// @param t1 New renew timer value in seconds.
    void setT1(const Triplet<uint32_t>& t1) {
        t1_ = t1;
    }

    /// @brief Returns T2 (rebind timer), expressed in seconds
    Triplet<uint32_t> getT2() const {
        return (t2_);
    }

    /// @brief Sets new rebind timer for a network.
    ///
    /// @param t2 New rebind timer value in seconds.
    void setT2(const Triplet<uint32_t>& t2) {
        t2_ = t2;
    }

    /// @brief Specifies what type of Host Reservations are supported.
    ///
    /// Host reservations may be either in-pool (they reserve an address that
    /// is in the dynamic pool) or out-of-pool (they reserve an address that is
    /// not in the dynamic pool). HR may also be completely disabled for
    /// performance reasons.
    ///
    /// @return whether in-pool host reservations are allowed.
    HRMode
    getHostReservationMode() const {
        return (host_reservation_mode_);
    }

    /// @brief Sets host reservation mode.
    ///
    /// See @ref getHostReservationMode for details.
    ///
    /// @param mode mode to be set
    void setHostReservationMode(HRMode mode) {
        host_reservation_mode_ = mode;
    }

    /// @brief Returns pointer to the option data configuration for this subnet.
    CfgOptionPtr getCfgOption() {
        return (cfg_option_);
    }

    /// @brief Returns const pointer to the option data configuration for this
    /// subnet.
    ConstCfgOptionPtr getCfgOption() const {
        return (cfg_option_);
    }

    /// @brief Unparses network object.
    ///
    /// @return A pointer to unparsed network configuration.
    virtual data::ElementPtr toElement() const;

protected:

    /// @brief Holds interface name for which this network is selected.
    std::string iface_name_;

    /// @brief Relay information
    ///
    /// See @ref RelayInfo for detailed description.
    RelayInfo relay_;

    /// @brief Optional definition of a client class
    ///
    /// If defined, only clients belonging to that class will be allowed to use
    /// this particular network. The default value for this is an empty list,
    /// which means that any client is allowed, regardless of its class.
    ///
    /// @todo This is just a single list of allowed classes. We'll also need
    /// to add a black-list (only classes on the list are rejected, the rest
    /// are allowed). Implementing this will require more fancy parser logic,
    /// so it may be a while until we support this.
    ClientClasses white_list_;

    /// @brief a Triplet (min/default/max) holding allowed renew timer values
    Triplet<uint32_t> t1_;

    /// @brief a Triplet (min/default/max) holding allowed rebind timer values
    Triplet<uint32_t> t2_;

    /// @brief a Triplet (min/default/max) holding allowed valid lifetime values
    Triplet<uint32_t> valid_;

    /// @brief Specifies host reservation mode
    ///
    /// See @ref HRMode type for details.
    HRMode host_reservation_mode_;

    /// @brief Pointer to the option data configuration for this subnet.
    CfgOptionPtr cfg_option_;
};

/// @brief Pointer to the @ref Network object.
typedef boost::shared_ptr<Network> NetworkPtr;

/// @brief Weak pointer to the @ref Network object.
typedef boost::weak_ptr<Network> WeakNetworkPtr;

/// @brief Specialization of the @ref Network object for DHCPv4 case.
class Network4 : public Network {
public:

    /// @brief Constructor.
    Network4()
        : Network(), match_client_id_(true) {
    }

    /// @brief Returns the flag indicating if the client identifiers should
    /// be used to identify the client's lease.
    ///
    /// @return true if client identifiers should be used, false otherwise.
    bool getMatchClientId() const {
        return (match_client_id_);
    }

    /// @brief Sets the flag indicating if the client identifier should be
    /// used to identify the client's lease.
    ///
    /// @param match If this value is true, the client identifiers are not
    /// used for lease lookup.
    void setMatchClientId(const bool match) {
        match_client_id_ = match;
    }

    /// @brief Unparses network object.
    ///
    /// @return A pointer to unparsed network configuration.
    virtual data::ElementPtr toElement() const;

    /// @brief Returns binary representation of the dhcp-server-identifier option (54).
    ///
    /// @return Server identifier option as IPv4 address. Zero IPv4 address
    /// indicates that server identifier hasn't been specified.
    virtual asiolink::IOAddress getServerId() const;

private:

    /// @brief Should server use client identifiers for client lease
    /// lookup.
    bool match_client_id_;
};

/// @brief Specialization of the @ref Network object for DHCPv6 case.
class Network6 : public Network {
public:

    /// @brief Constructor.
    Network6()
        : Network(), preferred_(0), interface_id_(), rapid_commit_(false) {
        setRelayInfo(asiolink::IOAddress::IPV6_ZERO_ADDRESS());
    }

    /// @brief Returns preferred lifetime (in seconds)
    ///
    /// @return a triplet with preferred lifetime
    Triplet<uint32_t> getPreferred() const {
        return (preferred_);
    }

    /// @brief Sets new preferred lifetime for a network.
    ///
    /// @param preferred New preferred lifetime in seconds.
    void setPreferred(const Triplet<uint32_t>& preferred) {
        preferred_ = preferred;
    }

    /// @brief Returns interface-id value (if specified)
    ///
    /// @return interface-id option (if defined)
    OptionPtr getInterfaceId() const {
        return (interface_id_);
    }

    /// @brief sets interface-id option (if defined)
    ///
    /// @param ifaceid pointer to interface-id option
    void setInterfaceId(const OptionPtr& ifaceid) {
        interface_id_ = ifaceid;
    }

    /// @brief Returns boolean value indicating that the Rapid Commit option
    /// is supported or unsupported for the subnet.
    ///
    /// @return true if the Rapid Commit option is supported, false otherwise.
    bool getRapidCommit() const {
        return (rapid_commit_);
    }

    /// @brief Enables or disables Rapid Commit option support for the subnet.
    ///
    /// @param rapid_commit A boolean value indicating that the Rapid Commit
    /// option support is enabled (if true), or disabled (if false).
    void setRapidCommit(const bool rapid_commit) {
        rapid_commit_ = rapid_commit;
    };

    /// @brief Unparses network object.
    ///
    /// @return A pointer to unparsed network configuration.
    virtual data::ElementPtr toElement() const;

private:

    /// @brief a triplet with preferred lifetime (in seconds)
    Triplet<uint32_t> preferred_;

    /// @brief specifies optional interface-id
    OptionPtr interface_id_;

    /// @brief A flag indicating if Rapid Commit option is supported
    /// for this network.
    ///
    /// It's default value is false, which indicates that the Rapid
    /// Commit is disabled for the subnet.
    bool rapid_commit_;
};

} // end of namespace isc::dhcp
} // end of namespace isc

#endif // NETWORK_H
