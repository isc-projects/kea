// Copyright (C) 2017-2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef NETWORK_H
#define NETWORK_H

#include <asiolink/io_address.h>
#include <cc/cfg_to_element.h>
#include <cc/data.h>
#include <cc/stamped_element.h>
#include <cc/user_context.h>
#include <dhcp/classify.h>
#include <dhcp/option.h>
#include <dhcpsrv/cfg_option.h>
#include <dhcpsrv/cfg_4o6.h>
#include <dhcpsrv/triplet.h>
#include <util/optional.h>
#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>
#include <cstdint>
#include <string>

namespace isc {
namespace dhcp {

/// List of IOAddresses
typedef std::vector<isc::asiolink::IOAddress> IOAddressList;

class Network;

/// @brief Pointer to the @ref Network object.
typedef boost::shared_ptr<Network> NetworkPtr;

/// @brief Weak pointer to the @ref Network object.
typedef boost::weak_ptr<Network> WeakNetworkPtr;


/// @brief Common interface representing a network to which the DHCP clients
/// are connected.
///
/// The most common type of network, in Kea's terminology, is a subnet. The
/// @ref Subnet derives from this class. Another types of objects implementing
/// this interface are @ref SharedNetwork4 and @ref SharedNetwork6 objects.
/// They group multiple subnets together to provide means for
/// extending available address pools (a single client may obtain IP
/// address from any of the pools belonging to subnets in the shared
/// network), or for selecting a subnet on a given link, depending on the
/// class of the client (e.g. cable network case: different subnet is
/// selected for cable modems, different one for routers).
///
/// The subnets and shared networks share many data structures, e.g. DHCP
/// options, local interface name, address manipulation methods. Both subnets
/// and shared networks derive from this class to provide the common
/// functionality.
///
/// The DHCP server configuration is complex because many parameters may
/// be specified at different levels of hierarchy. The lower level values,
/// e.g. subnet specific values, take precedence over upper level values,
/// e.g. shared network specific ones. For historical reasons, the DHCP
/// servers expect that the appropriate values are inherited from the
/// upper configuration levels to the lower configuration levels upon
/// the reconfiguration. For example: if a user didn't specify
/// valid-lifetime for a subnet, calling @c Subnet4::getValid() should
/// result in returning a global value of valid-lifetime. In the early
/// Kea days it was achieved by the configuration parsers which would
/// explicitly assign the global valid lifetime to the @c Subnet4
/// instances for which the subnet specific value was not provided. This
/// approach has a major benefit that it is fast. However, it makes
/// the subnets tightly dependent on the global values (and shared
/// network specific values). Modification of the global value must
/// result in modification of this value in all subnets for which
/// there is no explicit value provided. This issue became a serious
/// road block during the implementation of the Configuration Backend.
///
/// The @c Network object has been modified to address the problem of
/// inheritance of global, shared network specific and subnet specific
/// parameters in a generic way, at the same time minimizing the need to
/// change the existing server logic.
///
/// The @c Network object now holds the pointer to the "parent" @c Network
/// object. The parent network is a shared network. The object having
/// a parent is a subnet. The subnet may or may not have a parent.
/// The general idea is that the accessor functions of the network
/// will first check if the accessed value is specified or not (that
/// is handled by @c util::Optional object). If the value is specified
/// it is returned. Otherwise, the object will check if there is a
/// parent object it belongs to and will call the appropriate method
/// of that object. If the value is present it is returned. Otherwise
/// the global value is returned.
///
/// Accessing global values from the @c Network object is troublesome.
/// There is no uniform way to access those values. For example, the
/// given network may be in a staging or current configuration and
/// it really has no means to know in which of the two it belongs.
/// In fact, an attempt to pass the pointer to the @c SrvConfig object
/// would cause a circular dependency between the @c Network and the
/// @c SrvConfig. Even if it was possible and the @c Network had
/// access to the specific @c SrvConfig instance, it doesn't handle
/// the cases when the @c SrvConfig instance was modified.
///
/// To deal with the problem of accessing the global parameters in a
/// flexible manner, we elected to use an optional callback function
/// which can be associated with the @c Network object. This callback
/// implements the logic to retrieve global parameters and return them
/// in a well known form, so as the @c Network accessors can use them.
class Network : public virtual isc::data::StampedElement,
                public virtual isc::data::UserContext,
                public isc::data::CfgToElement {
public:
    /// @brief Holds optional information about relay.
    ///
    /// In some cases it is beneficial to have additional information about
    /// a relay configured in the subnet. For now, the structure holds only
    /// IP addresses, but there may potentially be additional parameters added
    /// later, e.g. relay interface-id or relay-id.
    class RelayInfo {
    public:

        /// @brief Adds an address to the list of addresses
        ///
        /// @param addr address to add
        /// @throw BadValue if the address is already in the list
        void addAddress(const asiolink::IOAddress& addr);

        /// @brief Returns const reference to the list of addresses
        ///
        /// @return const reference to the list of addresses
        const IOAddressList& getAddresses() const;

        /// @brief Indicates whether or not the address list has entries
        ///
        /// @return True if the address list is not empty
        bool hasAddresses() const;

        /// @brief Checks the address list for the given address
        ///
        /// @return True if the address is found in the address list
        bool containsAddress(const asiolink::IOAddress& addr) const;

    private:
        /// @brief List of relay IP addresses
        IOAddressList addresses_;
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

        /// Only global reservations are allowed. This mode
        /// instructs AllocEngine to only look at global reservations.
        HR_GLOBAL,

        /// Both out-of-pool and in-pool reservations are allowed. This is the
        /// most flexible mode, where sysadmin have biggest liberty. However,
        /// there is a non-trivial performance penalty for it, as the
        /// AllocEngine code has to check whether there are reservations, even
        /// when dealing with reservations from within the dynamic pools.
        /// @todo - should ALL include global?
        HR_ALL
    } HRMode;

    /// Pointer to the RelayInfo structure
    typedef boost::shared_ptr<Network::RelayInfo> RelayInfoPtr;

    /// @brief Constructor.
    Network()
        : iface_name_(), client_class_(), t1_(), t2_(), valid_(),
          host_reservation_mode_(HR_ALL, true), cfg_option_(new CfgOption()),
          calculate_tee_times_(), t1_percent_(), t2_percent_() {
    }

    /// @brief Virtual destructor.
    ///
    /// Does nothing at the moment.
    virtual ~Network() { };

    /// @brief Retrieves pointer to a shared network associated with a subnet.
    ///
    /// By implementing it as a template function we overcome a need to
    /// include shared_network.h header file to specify return type explicitly.
    /// The header can't be included because it would cause circular dependency
    /// between subnet.h and shared_network.h.
    ///
    /// This method uses an argument to hold a return value to allow the compiler
    /// to infer the return type without a need to call this function with an
    /// explicit return type as template argument.
    ///
    /// @param [out] shared_network Pointer to the shared network where returned
    /// value should be assigned.
    ///
    /// @tparam Type of the shared network, i.e. @ref SharedNetwork4 or a
    /// @ref SharedNetwork6.
    template<typename SharedNetworkPtrType>
    void getSharedNetwork(SharedNetworkPtrType& shared_network) const {
        shared_network = boost::dynamic_pointer_cast<
            typename SharedNetworkPtrType::element_type>(parent_network_.lock());
    }

    /// @brief Assigns shared network to a subnet.
    ///
    /// This method replaces any shared network associated with a subnet with
    /// a new shared network.
    ///
    /// @param shared_network Pointer to a new shared network to be associated
    /// with the subnet.
    void setSharedNetwork(const NetworkPtr& shared_network) {
        parent_network_ = shared_network;
    }

    /// @brief Returns shared network name.
    std::string getSharedNetworkName() const {
        return (shared_network_name_);
    }

    /// @brief Sets new shared network name.
    ///
    /// In certain cases the subnet must be associated with the shared network
    /// but the shared network object is not available. In particular, subnets
    /// are returned from the configuration database with only names of the
    /// shared networks. The actual shared networks must be fetched from the
    /// database using a separate query. In order to not loose associations
    /// of subnets with shared networks, the configuration backends will use
    /// this method to store the shared network names. The servers will later
    /// use those names to associate subnets with shared network instances.
    ///
    /// @param shared_network_name New shared network name.
    void setSharedNetworkName(const std::string& shared_network_name) {
        shared_network_name_ = shared_network_name;
    }

    /// @brief Sets local name of the interface for which this network is
    /// selected.
    ///
    /// If the interface is specified, the server will use the network
    /// associated with this local interface to allocate IP addresses and
    /// other resources to a client.
    ///
    /// @param iface_name Interface name.
    void setIface(const util::Optional<std::string>& iface_name) {
        iface_name_ = iface_name;
    }

    /// @brief Returns name of the local interface for which this network is
    /// selected.
    ///
    /// @return Interface name as text.
    util::Optional<std::string> getIface() const {
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

    /// @brief Adds an address to the list addresses in the network's relay info
    ///
    /// @param addr address of the relay
    /// @throw BadValue if the address is already in the list
    void addRelayAddress(const asiolink::IOAddress& addr);

    /// @brief Returns the list of relay addresses from the network's relay info
    ///
    /// @return const reference to the list of addresses
    const IOAddressList& getRelayAddresses() const;

    /// @brief Indicates if network's relay info has relay addresses
    ///
    /// @return True the relay list is not empty, false otherwise
    bool hasRelays() const;

    /// @brief Tests if the network's relay info contains the given address
    ///
    /// @param address address to search for in the relay list
    /// @return True if a relay with the given address is found, false otherwise
    bool hasRelayAddress(const asiolink::IOAddress& address) const;

    /// @brief Checks whether this network supports client that belongs to
    /// specified classes.
    ///
    /// This method checks whether a client that belongs to given classes can
    /// use this network. For example, if this class is reserved for client
    /// class "foo" and the client belongs to classes "foo", "bar" and "baz",
    /// it is supported. On the other hand, client belonging to classes
    /// "foobar" and "zyxxy" is not supported.
    ///
    /// @note: changed the planned white and black lists idea to a simple
    /// client class name.
    ///
    /// @param client_classes list of all classes the client belongs to
    /// @return true if client can be supported, false otherwise
    virtual bool
    clientSupported(const isc::dhcp::ClientClasses& client_classes) const;

    /// @brief Sets the supported class to class class_name
    ///
    /// @param class_name client class to be supported by this network
    void allowClientClass(const isc::dhcp::ClientClass& class_name);

    /// @brief Adds class class_name to classes required to be evaluated.
    ///
    /// @param class_name client class required to be evaluated
    void requireClientClass(const isc::dhcp::ClientClass& class_name);

    /// @brief Returns classes which are required to be evaluated
    const ClientClasses& getRequiredClasses() const;

    /// @brief returns the client class
    ///
    /// @note The returned reference is only valid as long as the object
    /// returned it is valid.
    ///
    /// @return client class @ref client_class_
    const util::Optional<ClientClass>& getClientClass() const {
        return (client_class_);
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
    util::Optional<HRMode>
    getHostReservationMode() const {
        return (getProperty(&Network::getHostReservationMode, host_reservation_mode_));
    }

    /// @brief Sets host reservation mode.
    ///
    /// See @ref getHostReservationMode for details.
    ///
    /// @param mode mode to be set
    void setHostReservationMode(const util::Optional<HRMode>& mode) {
        host_reservation_mode_ = mode;
    }

    /// @brief Returns pointer to the option data configuration for this network.
    CfgOptionPtr getCfgOption() {
        return (cfg_option_);
    }

    /// @brief Returns const pointer to the option data configuration for this
    /// network.
    ConstCfgOptionPtr getCfgOption() const {
        return (cfg_option_);
    }

    /// @brief Returns whether or not T1/T2 calculation is enabled.
    util::Optional<bool> getCalculateTeeTimes() const {
        return (calculate_tee_times_);
    }

    /// @brief Sets whether or not T1/T2 calculation is enabled.
    ///
    /// @param calculate_tee_times new value of enabled/disabled.
    void setCalculateTeeTimes(const util::Optional<bool>& calculate_tee_times) {
        calculate_tee_times_ = calculate_tee_times;
    }

    /// @brief Returns percentage to use when calculating the T1 (renew timer).
    util::Optional<double> getT1Percent() const {
        return (t1_percent_);
    }

    /// @brief Sets new precentage for calculating T1 (renew timer).
    ///
    /// @param t1_percent New percentage to use.
    void setT1Percent(const util::Optional<double>& t1_percent) {
        t1_percent_ = t1_percent;
    }

    /// @brief Returns percentage to use when calculating the T2 (rebind timer).
    util::Optional<double> getT2Percent() const {
        return (t2_percent_);
    }

    /// @brief Sets new precentage for calculating T2 (rebind timer).
    ///
    /// @param t2_percent New percentage to use.
    void setT2Percent(const util::Optional<double>& t2_percent) {
        t2_percent_ = t2_percent;
    }

    /// @brief Unparses network object.
    ///
    /// @return A pointer to unparsed network configuration.
    virtual data::ElementPtr toElement() const;

protected:

    template<typename ReturnType, typename PropertyType>
    util::Optional<ReturnType>
    getProperty(util::Optional<ReturnType>(Network::*MethodPointer)() const,
                PropertyType property) const {
        if (property.unspecified()) {
            auto sn = parent_network_.lock();
            if (sn) {
                auto value = ((*sn).*MethodPointer)();
                if (!value.unspecified()) {
                    return (value);
                }
            }
        }
        return (property);

    }

    /// @brief Holds interface name for which this network is selected.
    util::Optional<std::string> iface_name_;

    /// @brief Relay information
    ///
    /// See @ref RelayInfo for detailed description.
    RelayInfo relay_;

    /// @brief Optional definition of a client class
    ///
    /// If defined, only clients belonging to that class will be allowed to use
    /// this particular network. The default value for this is an empty string,
    /// which means that any client is allowed, regardless of its class.
    util::Optional<ClientClass> client_class_;

    /// @brief Required classes
    ///
    /// If the network is selected these classes will be added to the
    /// incoming packet and their evaluation will be required.
    ClientClasses required_classes_;

    /// @brief a Triplet (min/default/max) holding allowed renew timer values
    Triplet<uint32_t> t1_;

    /// @brief a Triplet (min/default/max) holding allowed rebind timer values
    Triplet<uint32_t> t2_;

    /// @brief a Triplet (min/default/max) holding allowed valid lifetime values
    Triplet<uint32_t> valid_;

    /// @brief Specifies host reservation mode
    ///
    /// See @ref HRMode type for details.
    util::Optional<HRMode> host_reservation_mode_;

    /// @brief Pointer to the option data configuration for this subnet.
    CfgOptionPtr cfg_option_;

    /// @brief Enables calculation of T1 and T2 timers
    util::Optional<bool> calculate_tee_times_;

    /// @brief Percentage of the lease lifetime to use when calculating T1 timer
    util::Optional<double> t1_percent_;

    /// @brief Percentage of the lease lifetime to use when calculating T2 timer
    util::Optional<double> t2_percent_;

    /// @brief Pointer to another network that this network belongs to.
    ///
    /// The most common case is that this instance is a subnet which belongs
    /// to a shared network and the @c parent_network_ points to the shared
    /// network object. If the network instance (subnet) doesn't belong to
    /// a shared network this pointer is null.
    WeakNetworkPtr parent_network_;

    /// @brief Shared network name.
    std::string shared_network_name_;
};

/// @brief Specialization of the @ref Network object for DHCPv4 case.
class Network4 : public Network {
public:

    /// @brief Constructor.
    Network4()
        : Network(), match_client_id_(true, true), authoritative_(),
          siaddr_(), sname_(), filename_() {
    }

    /// @brief Returns the flag indicating if the client identifiers should
    /// be used to identify the client's lease.
    ///
    /// @return true if client identifiers should be used, false otherwise.
    util::Optional<bool> getMatchClientId() const {
        return (match_client_id_);
    }

    /// @brief Sets the flag indicating if the client identifier should be
    /// used to identify the client's lease.
    ///
    /// @param match If this value is true, the client identifiers are not
    /// used for lease lookup.
    void setMatchClientId(const util::Optional<bool>& match) {
        match_client_id_ = match;
    }

    /// @brief Returns the flag indicating if requests for unknown IP addresses
    /// should be rejected with DHCPNAK instead of ignored.
    ///
    /// @return true if requests for unknown IP addresses should be rejected,
    /// false otherwise.
    util::Optional<bool> getAuthoritative() const {
        return (authoritative_);
    }

    /// @brief Sets the flag indicating if requests for unknown IP addresses
    /// should be rejected with DHCPNAK instead of ignored.
    ///
    /// @param authoritative If this value is true, the requests for unknown IP
    /// addresses will be rejected with DHCPNAK messages
    void setAuthoritative(const util::Optional<bool>& authoritative) {
        authoritative_ = authoritative;
    }

    /// @brief Sets siaddr for the network.
    ///
    /// Will be used for siaddr field (the next server) that typically is used
    /// as TFTP server. If not specified, the default value of 0.0.0.0 is
    /// used.
    void setSiaddr(const util::Optional<asiolink::IOAddress>& siaddr);

    /// @brief Returns siaddr for this network.
    ///
    /// @return siaddr value
    const util::Optional<asiolink::IOAddress>& getSiaddr() const;

    /// @brief Sets server hostname for the network.
    ///
    /// Will be used for server hostname field (may be empty if not defined)
    void setSname(const util::Optional<std::string>& sname);

    /// @brief Returns server hostname for this network.
    ///
    /// @return server hostname value
    const util::Optional<std::string>& getSname() const;

    /// @brief Sets boot file name for the network.
    ///
    /// Will be used for boot file name (may be empty if not defined)
    void setFilename(const util::Optional<std::string>& filename);

    /// @brief Returns boot file name for this subnet
    ///
    /// @return boot file name value
    const util::Optional<std::string>& getFilename() const;

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
    util::Optional<bool> match_client_id_;

    /// @brief Should requests for unknown IP addresses be rejected.
    util::Optional<bool> authoritative_;

    /// @brief siaddr value for this subnet
    util::Optional<asiolink::IOAddress> siaddr_;

    /// @brief server hostname for this subnet
    util::Optional<std::string> sname_;

    /// @brief boot file name for this subnet
    util::Optional<std::string> filename_;
};

/// @brief Specialization of the @ref Network object for DHCPv6 case.
class Network6 : public Network {
public:

    /// @brief Constructor.
    Network6()
        : Network(), preferred_(), interface_id_(), rapid_commit_() {
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
    util::Optional<bool> getRapidCommit() const {
        return (rapid_commit_);
    }

    /// @brief Enables or disables Rapid Commit option support for the subnet.
    ///
    /// @param rapid_commit A boolean value indicating that the Rapid Commit
    /// option support is enabled (if true), or disabled (if false).
    void setRapidCommit(const util::Optional<bool>& rapid_commit) {
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
    util::Optional<bool> rapid_commit_;
};

} // end of namespace isc::dhcp
} // end of namespace isc

#endif // NETWORK_H
