// Copyright (C) 2017-2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef NETWORK_H
#define NETWORK_H

#include <cc/cfg_to_element.h>
#include <cc/data.h>
#include <cc/element_value.h>
#include <cc/stamped_element.h>
#include <cc/user_context.h>
#include <dhcp/classify.h>
#include <dhcp/option.h>
#include <dhcpsrv/cfg_globals.h>
#include <dhcpsrv/cfg_option.h>
#include <dhcpsrv/cfg_4o6.h>
#include <dhcpsrv/d2_client_cfg.h>
#include <util/triplet.h>
#include <util/optional.h>

#include <boost/multi_index/hashed_index.hpp>
#include <boost/multi_index/identity.hpp>
#include <boost/multi_index/indexed_by.hpp>
#include <boost/multi_index/sequenced_index.hpp>
#include <boost/multi_index_container.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>

#include <cstdint>
#include <functional>
#include <string>

/// @brief Template to ignore unused arguments.
namespace {
template <typename... Args>
inline void unused(Args const& ...) {}
} // end of anonymous namespace

namespace isc {
namespace dhcp {

/// @brief Tag for the list of IO addresses as a list.
struct IOAddressListListTag { };

/// @brief Tag for the list of IO addresses as a set.
struct IOAddressListSetTag { };

/// @brief List of IO addresses
typedef boost::multi_index_container<
    // Multi index container holds IO addresses.
    asiolink::IOAddress,
    // Indexes.
    boost::multi_index::indexed_by<
        // First and default index allows for in order iteration.
        boost::multi_index::sequenced<
            boost::multi_index::tag<IOAddressListListTag>
        >,
        // Second index allows for checking existence.
        boost::multi_index::hashed_unique<
            boost::multi_index::tag<IOAddressListSetTag>,
            boost::multi_index::identity<asiolink::IOAddress>
        >
    >
> IOAddressList;

// @brief Forward declaration of the Network class.
class Network;

/// @brief Pointer to the @ref Network object.
typedef boost::shared_ptr<Network> NetworkPtr;

/// @brief Weak pointer to the @ref Network object.
typedef boost::weak_ptr<Network> WeakNetworkPtr;

/// @brief Callback function for @c Network that retrieves globally
/// configured parameters.
typedef std::function<ConstCfgGlobalsPtr()> FetchNetworkGlobalsFn;

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
/// object. Thus subnets which belong to a shared network will have
/// that shared network as its parent. Stand-alone subnets, will have
/// no parent.
///
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

    /// @brief Inheritance "mode" used when fetching an optional @c Network
    /// parameter.
    ///
    /// The following modes are currently supported:
    /// - NONE: no inheritance is used, the network specific value is returned
    ///   regardless if it is specified or not.
    /// - PARENT_NETWORK: parent network specific value is returned or unspecified
    ///   if the parent network doesn't exist.
    /// - GLOBAL: global specific value is returned.
    /// - ALL: inheritance is used on all levels: network specific value takes
    ///   precedence over parent specific value over the global value.
    enum class Inheritance {
        NONE,
        PARENT_NETWORK,
        GLOBAL,
        ALL
    };

    /// Pointer to the RelayInfo structure
    typedef boost::shared_ptr<Network::RelayInfo> RelayInfoPtr;

    /// @brief Constructor.
    Network()
        : iface_name_(), client_class_(), t1_(), t2_(), valid_(),
          reservations_global_(false, true), reservations_in_subnet_(true, true),
          reservations_out_of_pool_(false, true), cfg_option_(new CfgOption()),
          calculate_tee_times_(), t1_percent_(), t2_percent_(),
          ddns_send_updates_(), ddns_override_no_update_(), ddns_override_client_update_(),
          ddns_replace_client_name_mode_(), ddns_generated_prefix_(), ddns_qualifying_suffix_(),
          hostname_char_set_(), hostname_char_replacement_(), store_extended_info_(),
          cache_threshold_(), cache_max_age_(), ddns_update_on_renew_(),
          ddns_use_conflict_resolution_(), ddns_ttl_percent_(), allocator_type_(),
          default_allocator_type_() {
    }

    /// @brief Virtual destructor.
    ///
    /// Does nothing at the moment.
    virtual ~Network() { };

    /// @brief Sets the optional callback function used to fetch globally
    /// configured parameters.
    ///
    /// @param fetch_globals_fn Pointer to the function.
    void setFetchGlobalsFn(FetchNetworkGlobalsFn fetch_globals_fn) {
        fetch_globals_fn_ = fetch_globals_fn;
    }

    /// @brief Checks if the network is associated with a function used to
    /// fetch globally configured parameters.
    ///
    /// @return true if it is associated, false otherwise.
    bool hasFetchGlobalsFn() const {
        return (static_cast<bool>(fetch_globals_fn_));
    }

    /// @brief Sets local name of the interface for which this network is
    /// selected.
    ///
    /// If the interface is specified, the server will use the network
    /// associated with this local interface to allocate IP addresses and
    /// other resources to a client.
    /// Empty values are translated into unspecified.
    ///
    /// @param iface_name Interface name.
    void setIface(const util::Optional<std::string>& iface_name) {
        if (iface_name.empty()) {
            iface_name_ = util::Optional<std::string>("", true);
        } else {
            iface_name_ = iface_name;
        }
    }

    /// @brief Returns name of the local interface for which this network is
    /// selected.
    ///
    /// @param inheritance inheritance mode to be used.
    /// @return Interface name as optional text.
    util::Optional<std::string>
    getIface(const Inheritance& inheritance = Inheritance::ALL) const {
        return (getProperty<Network>(&Network::getIface, iface_name_,
                                     inheritance));
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
    /// @param inheritance inheritance mode to be used.
    /// @return client class @ref client_class_
    util::Optional<ClientClass>
    getClientClass(const Inheritance& inheritance = Inheritance::ALL) const {
        return (getProperty<Network>(&Network::getClientClass, client_class_,
                                     inheritance));
    }

    /// @brief Return valid-lifetime for addresses in that prefix
    ///
    /// @param inheritance inheritance mode to be used.
    isc::util::Triplet<uint32_t> getValid(const Inheritance& inheritance = Inheritance::ALL) const {
        return (getProperty<Network>(&Network::getValid, valid_, inheritance,
                                     CfgGlobals::VALID_LIFETIME,
                                     CfgGlobals::MIN_VALID_LIFETIME,
                                     CfgGlobals::MAX_VALID_LIFETIME));
    }

    /// @brief Sets new valid lifetime for a network.
    ///
    /// @param valid New valid lifetime in seconds.
    void setValid(const isc::util::Triplet<uint32_t>& valid) {
        valid_ = valid;
    }

    /// @brief Returns T1 (renew timer), expressed in seconds
    ///
    /// @param inheritance inheritance mode to be used.
    isc::util::Triplet<uint32_t> getT1(const Inheritance& inheritance = Inheritance::ALL) const {
        return (getProperty<Network>(&Network::getT1, t1_, inheritance,
                                     CfgGlobals::RENEW_TIMER));
    }

    /// @brief Sets new renew timer for a network.
    ///
    /// @param t1 New renew timer value in seconds.
    void setT1(const isc::util::Triplet<uint32_t>& t1) {
        t1_ = t1;
    }

    /// @brief Returns T2 (rebind timer), expressed in seconds
    ///
    /// @param inheritance inheritance mode to be used.
    isc::util::Triplet<uint32_t> getT2(const Inheritance& inheritance = Inheritance::ALL) const {
        return (getProperty<Network>(&Network::getT2, t2_, inheritance,
                                     CfgGlobals::REBIND_TIMER));
    }

    /// @brief Sets new rebind timer for a network.
    ///
    /// @param t2 New rebind timer value in seconds.
    void setT2(const isc::util::Triplet<uint32_t>& t2) {
        t2_ = t2;
    }

    /// @brief Returns whether global reservations should be fetched.
    ///
    /// @param inheritance inheritance mode to be used.
    util::Optional<bool>
    getReservationsGlobal(const Inheritance& inheritance = Inheritance::ALL) const {
        return (getProperty<Network>(&Network::getReservationsGlobal,
                                     reservations_global_,
                                     inheritance,
                                     CfgGlobals::RESERVATIONS_GLOBAL));
    }

    /// @brief Sets whether global reservations should be fetched.
    ///
    /// @param reservations_global new value of enabled/disabled.
    void setReservationsGlobal(const util::Optional<bool>& reservations_global) {
        reservations_global_ = reservations_global;
    }

    /// @brief Returns whether subnet reservations should be fetched.
    ///
    /// @param inheritance inheritance mode to be used.
    util::Optional<bool>
    getReservationsInSubnet(const Inheritance& inheritance = Inheritance::ALL) const {
        return (getProperty<Network>(&Network::getReservationsInSubnet,
                                     reservations_in_subnet_,
                                     inheritance,
                                     CfgGlobals::RESERVATIONS_IN_SUBNET));
    }

    /// @brief Sets whether subnet reservations should be fetched.
    ///
    /// @param reservations_in_subnet new value of enabled/disabled.
    void setReservationsInSubnet(const util::Optional<bool>& reservations_in_subnet) {
        reservations_in_subnet_ = reservations_in_subnet;
    }

    /// @brief Returns whether only out-of-pool reservations are allowed.
    ///
    /// @param inheritance inheritance mode to be used.
    util::Optional<bool>
    getReservationsOutOfPool(const Inheritance& inheritance = Inheritance::ALL) const {
        return (getProperty<Network>(&Network::getReservationsOutOfPool,
                                     reservations_out_of_pool_,
                                     inheritance,
                                     CfgGlobals::RESERVATIONS_OUT_OF_POOL));
    }

    /// @brief Sets whether only out-of-pool reservations are allowed.
    ///
    /// @param reservations_out_of_pool new value of enabled/disabled.
    void setReservationsOutOfPool(const util::Optional<bool>& reservations_out_of_pool) {
        reservations_out_of_pool_ = reservations_out_of_pool;
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
    ///
    /// @param inheritance inheritance mode to be used.
    util::Optional<bool>
    getCalculateTeeTimes(const Inheritance& inheritance = Inheritance::ALL) const {
        return (getProperty<Network>(&Network::getCalculateTeeTimes,
                                     calculate_tee_times_,
                                     inheritance,
                                     CfgGlobals::CALCULATE_TEE_TIMES));
    }

    /// @brief Sets whether or not T1/T2 calculation is enabled.
    ///
    /// @param calculate_tee_times new value of enabled/disabled.
    void setCalculateTeeTimes(const util::Optional<bool>& calculate_tee_times) {
        calculate_tee_times_ = calculate_tee_times;
    }

    /// @brief Returns percentage to use when calculating the T1 (renew timer).
    ///
    /// @param inheritance inheritance mode to be used.
    util::Optional<double>
    getT1Percent(const Inheritance& inheritance = Inheritance::ALL) const {
        return (getProperty<Network>(&Network::getT1Percent, t1_percent_,
                                     inheritance, CfgGlobals::T1_PERCENT));
    }

    /// @brief Sets new percentage for calculating T1 (renew timer).
    ///
    /// @param t1_percent New percentage to use.
    void setT1Percent(const util::Optional<double>& t1_percent) {
        t1_percent_ = t1_percent;
    }

    /// @brief Returns percentage to use when calculating the T2 (rebind timer).
    ///
    /// @param inheritance inheritance mode to be used.
    util::Optional<double>
    getT2Percent(const Inheritance& inheritance = Inheritance::ALL) const {
        return (getProperty<Network>(&Network::getT2Percent, t2_percent_,
                                     inheritance, CfgGlobals::T2_PERCENT));
    }

    /// @brief Sets new percentage for calculating T2 (rebind timer).
    ///
    /// @param t2_percent New percentage to use.
    void setT2Percent(const util::Optional<double>& t2_percent) {
        t2_percent_ = t2_percent;
    }

    /// @brief Returns ddns-send-updates
    ///
    /// @param inheritance inheritance mode to be used.
    util::Optional<bool>
    getDdnsSendUpdates(const Inheritance& inheritance = Inheritance::ALL) const {
        return (getProperty<Network>(&Network::getDdnsSendUpdates,
                                     ddns_send_updates_, inheritance,
                                     CfgGlobals::DDNS_SEND_UPDATES));
    }

    /// @brief Sets new ddns-send-updates
    ///
    /// @param ddns_send_updates New value to use.
    void setDdnsSendUpdates(const util::Optional<bool>& ddns_send_updates) {
        ddns_send_updates_ = ddns_send_updates;
    }

    /// @brief Returns ddns-override-no-update
    ///
    /// @param inheritance inheritance mode to be used.
    util::Optional<bool>
    getDdnsOverrideNoUpdate(const Inheritance& inheritance = Inheritance::ALL) const {
        return (getProperty<Network>(&Network::getDdnsOverrideNoUpdate,
                                     ddns_override_no_update_, inheritance,
                                     CfgGlobals::DDNS_OVERRIDE_NO_UPDATE));
    }

    /// @brief Sets new ddns-override-no-update
    ///
    /// @param ddns_override_no_update New value to use.
    void setDdnsOverrideNoUpdate(const util::Optional<bool>& ddns_override_no_update) {
        ddns_override_no_update_ = ddns_override_no_update;
    }

    /// @brief Returns ddns-override-client-update
    ///
    /// @param inheritance inheritance mode to be used.
    util::Optional<bool>
    getDdnsOverrideClientUpdate(const Inheritance& inheritance = Inheritance::ALL) const {
        return (getProperty<Network>(&Network::getDdnsOverrideClientUpdate,
                                     ddns_override_client_update_, inheritance,
                                     CfgGlobals::DDNS_OVERRIDE_CLIENT_UPDATE));
    }

    /// @brief Sets new ddns-override-client-update
    ///
    /// @param ddns_override_client_update New value to use.
    void setDdnsOverrideClientUpdate(const util::Optional<bool>&
                                     ddns_override_client_update) {
        ddns_override_client_update_ = ddns_override_client_update;
    }

    /// @brief Returns ddns-replace-client-name-mode
    ///
    /// @param inheritance inheritance mode to be used.
    util::Optional<D2ClientConfig::ReplaceClientNameMode>
    getDdnsReplaceClientNameMode(const Inheritance& inheritance = Inheritance::ALL) const {
        // Inheritance for ddns-replace-client-name is a little different than for other
        // parameters. The value at the global level is given as a string.
        // Thus we call getProperty here without a global name to check if it
        // is specified on network level only.
        const util::Optional<D2ClientConfig::ReplaceClientNameMode>& mode =
            getProperty<Network>(&Network::getDdnsReplaceClientNameMode,
                                 ddns_replace_client_name_mode_, inheritance);

        // If it is not specified at network level we need this special
        // case code to convert the global string value to an enum.
        if (mode.unspecified() && (inheritance != Inheritance::NONE) &&
            (inheritance != Inheritance::PARENT_NETWORK)) {
            // Get global mode.
            util::Optional<std::string> mode_label;
            mode_label = getGlobalProperty(mode_label,
                                           CfgGlobals::DDNS_REPLACE_CLIENT_NAME);
            if (!mode_label.unspecified()) {
                try {
                    // If the mode is globally configured, convert it to an enum.
                    return (D2ClientConfig::stringToReplaceClientNameMode(mode_label.get()));
                } catch (...) {
                    // This should not really happen because the configuration
                    // parser should have already verified the globally configured
                    // mode. However, we want to be 100% sure that this
                    // method doesn't throw. Let's just return unspecified.
                    return (mode);
                }
            }
        }
        return (mode);
    }

    /// @brief Sets new ddns-replace-client-name-mode
    ///
    /// @param ddns_replace_client_name_mode New value to use.
    void
    setDdnsReplaceClientNameMode(const util::Optional<D2ClientConfig::ReplaceClientNameMode>&
                                 ddns_replace_client_name_mode) {
        ddns_replace_client_name_mode_ = ddns_replace_client_name_mode;
    }

    /// @brief Returns ddns-generated-prefix
    ///
    /// @param inheritance inheritance mode to be used.
    util::Optional<std::string>
    getDdnsGeneratedPrefix(const Inheritance& inheritance = Inheritance::ALL) const {
        return (getProperty<Network>(&Network::getDdnsGeneratedPrefix,
                                     ddns_generated_prefix_, inheritance,
                                     CfgGlobals::DDNS_GENERATED_PREFIX));
    }

    /// @brief Sets new ddns-generated-prefix
    ///
    /// @param ddns_generated_prefix New value to use.
    void setDdnsGeneratedPrefix(const util::Optional<std::string>& ddns_generated_prefix) {
        ddns_generated_prefix_ = ddns_generated_prefix;
    }

    /// @brief Returns ddns-qualifying-suffix
    ///
    /// @param inheritance inheritance mode to be used.
    util::Optional<std::string>
    getDdnsQualifyingSuffix(const Inheritance& inheritance = Inheritance::ALL) const {
        return (getProperty<Network>(&Network::getDdnsQualifyingSuffix,
                                     ddns_qualifying_suffix_, inheritance,
                                     CfgGlobals::DDNS_QUALIFYING_SUFFIX));
    }

    /// @brief Sets new ddns-qualifying-suffix
    ///
    /// @param ddns_qualifying_suffix New value to use.
    void setDdnsQualifyingSuffix(const util::Optional<std::string>& ddns_qualifying_suffix) {
        ddns_qualifying_suffix_ = ddns_qualifying_suffix;
    }

    /// @brief Returns ddns-ttl-percent
    ///
    /// @param inheritance inheritance mode to be used.
    util::Optional<double>
    getDdnsTtlPercent(const Inheritance& inheritance = Inheritance::ALL) const {
        return (getProperty<Network>(&Network::getDdnsTtlPercent,
                                     ddns_ttl_percent_, inheritance,
                                     CfgGlobals::DDNS_TTL_PERCENT));
    }

    /// @brief Sets new ddns-ttl-percent
    ///
    /// @param ddns_ttl_percent New value to use.
    void setDdnsTtlPercent(const util::Optional<double>& ddns_ttl_percent) {
        ddns_ttl_percent_ = ddns_ttl_percent;
    }

    /// @brief Return the char set regexp used to sanitize client hostnames.
    util::Optional<std::string>
    getHostnameCharSet(const Inheritance& inheritance = Inheritance::ALL) const {
        return (getProperty<Network>(&Network::getHostnameCharSet,
                                     hostname_char_set_, inheritance,
                                     CfgGlobals::HOSTNAME_CHAR_SET));
    }

    /// @brief Sets new hostname-char-set
    ///
    /// @param hostname_char_set New value to use.
    void setHostnameCharSet(const util::Optional<std::string>& hostname_char_set) {
        hostname_char_set_ = hostname_char_set;
    }

    /// @brief Return the invalid char replacement used to sanitize client hostnames.
    util::Optional<std::string>
    getHostnameCharReplacement(const Inheritance& inheritance = Inheritance::ALL) const {
        return (getProperty<Network>(&Network::getHostnameCharReplacement,
                                     hostname_char_replacement_, inheritance,
                                     CfgGlobals::HOSTNAME_CHAR_REPLACEMENT));
    }

    /// @brief Sets new hostname-char-replacement
    ///
    /// @param hostname_char_replacement New value to use.
    void setHostnameCharReplacement(const util::Optional<std::string>&
                                    hostname_char_replacement) {
        hostname_char_replacement_ = hostname_char_replacement;
    }

    /// @brief Returns store-extended-info
    ///
    /// @param inheritance inheritance mode to be used.
    util::Optional<bool>
    getStoreExtendedInfo(const Inheritance& inheritance = Inheritance::ALL) const {
        return (getProperty<Network>(&Network::getStoreExtendedInfo,
                                     store_extended_info_, inheritance,
                                     CfgGlobals::STORE_EXTENDED_INFO));
    }

    /// @brief Sets new store-extended-info
    ///
    /// @param store_extended_info New value to use.
    void setStoreExtendedInfo(const util::Optional<bool>& store_extended_info) {
        store_extended_info_ = store_extended_info;
    }

    /// @brief Returns percentage to use as cache threshold.
    ///
    /// @param inheritance inheritance mode to be used.
    util::Optional<double>
    getCacheThreshold(const Inheritance& inheritance = Inheritance::ALL) const {
        return (getProperty<Network>(&Network::getCacheThreshold,
                                     cache_threshold_, inheritance,
                                     CfgGlobals::CACHE_THRESHOLD));
    }

    /// @brief Sets cache threshold for a network.
    ///
    /// @param cache_threshold New cache threshold percentage to use.
    void setCacheThreshold(const util::Optional<double>& cache_threshold) {
        cache_threshold_ = cache_threshold;
    }

    /// @brief Returns value in seconds to use as cache maximum age.
    ///
    /// @param inheritance inheritance mode to be used.
    util::Optional<uint32_t>
    getCacheMaxAge(const Inheritance& inheritance = Inheritance::ALL) const {
        return (getProperty<Network>(&Network::getCacheMaxAge, cache_max_age_,
                                     inheritance, CfgGlobals::CACHE_MAX_AGE));
    }

    /// @brief Sets cache max for a network.
    ///
    /// @param cache_max_age New cache maximum value in seconds to use.
    void setCacheMaxAge(const util::Optional<uint32_t>& cache_max_age) {
        cache_max_age_ = cache_max_age;
    }

    /// @brief Returns ddns-update-on-renew
    ///
    /// @param inheritance inheritance mode to be used.
    util::Optional<bool>
    getDdnsUpdateOnRenew(const Inheritance& inheritance = Inheritance::ALL) const {
        return (getProperty<Network>(&Network::getDdnsUpdateOnRenew,
                                     ddns_update_on_renew_, inheritance,
                                     CfgGlobals::DDNS_UPDATE_ON_RENEW));
    }

    /// @brief Sets new ddns-update-on-renew
    ///
    /// @param ddns_update_on_renew New value to use.
    void setDdnsUpdateOnRenew(const util::Optional<bool>& ddns_update_on_renew) {
        ddns_update_on_renew_ = ddns_update_on_renew;
    }

    /// @brief Returns ddns-use-conflict-resolution
    ///
    /// @param inheritance inheritance mode to be used.
    util::Optional<bool>
    getDdnsUseConflictResolution(const Inheritance& inheritance = Inheritance::ALL) const {
        return (getProperty<Network>(&Network::getDdnsUseConflictResolution,
                                     ddns_use_conflict_resolution_,
                                     inheritance,
                                     CfgGlobals::DDNS_USE_CONFLICT_RESOLUTION));
    }

    /// @brief Sets new ddns-use-conflict-resolution
    ///
    /// @param ddns_use_conflict_resolution New value to use.
    void setDdnsUseConflictResolution(const util::Optional<bool>& ddns_use_conflict_resolution) {
        ddns_use_conflict_resolution_ = ddns_use_conflict_resolution;
    }

    /// @brief Returns allocator type.
    ///
    /// @param inheritance inheritance mode to be used.
    util::Optional<std::string>
    getAllocatorType(const Inheritance& inheritance = Inheritance::ALL) const {
        return (getProperty<Network>(&Network::getAllocatorType,
                                     allocator_type_,
                                     inheritance,
                                     CfgGlobals::ALLOCATOR));
    }

    /// @brief Sets new allocator type.
    ///
    /// It doesn't set the actual allocator instance. It merely remembers the
    /// value specified in the configuration, so it can be output in the
    /// @c toElement call.
    ///
    /// @param allocator_type new allocator type to use.
    void setAllocatorType(const util::Optional<std::string>& allocator_type) {
        allocator_type_ = allocator_type;
    }

    /// @brief Returns a default allocator type.
    ///
    /// This allocator type is used when the allocator type is neither specified
    /// at the shared network nor subnet level.
    ///
    /// @return an allocator type as a string.
    util::Optional<std::string>
    getDefaultAllocatorType(const Inheritance& inheritance = Inheritance::ALL) const {
        return (getProperty<Network>(&Network::getDefaultAllocatorType,
                                     default_allocator_type_,
                                     inheritance));
    }

    /// @brief Sets a defalt allocator type.
    ///
    /// @param allocator_type a new default allocator type.
    void setDefaultAllocatorType(const std::string& allocator_type) {
        default_allocator_type_ = allocator_type;
    }

    /// @brief Unparses network object.
    ///
    /// @return A pointer to unparsed network configuration.
    virtual data::ElementPtr toElement() const;

    /// @brief Generates an identifying label for logging.
    ///
    /// @return string containing the label
    virtual std::string getLabel() const {
        return ("base-network");
    }

protected:

    /// @brief Gets the optional callback function used to fetch globally
    /// configured parameters.
    ///
    /// @return Pointer to the function.
    FetchNetworkGlobalsFn getFetchGlobalsFn() const {
        return (fetch_globals_fn_);
    }

    /// @brief Returns a value of global configuration parameter with
    /// a given index.
    ///
    /// If the @c ferch_globals_fn_ function is non-null, this method will
    /// invoke this function to retrieve a global value having the given
    /// index. Typically, this method is invoked by @c getProperty when
    /// network specific value of the parameter is not found. In some cases
    /// it may be called by other methods. One such example is the
    /// @c getDdnsReplaceClientNameMode which needs to call @c getGlobalProperty
    /// explicitly to convert the global replace client name mode value from
    /// a string to an enum.
    ///
    /// @tparam ReturnType Type of the returned value, e.g.
    /// @c Optional<std::string>.
    ///
    /// @param property Value to be returned when it is specified or when
    /// no global value is found.
    /// @param global_index Index of the global parameter which value should
    /// be returned
    /// @param min_index Index of the min global parameter which value should
    /// be returned for triplets
    /// @param max_index Index of the max global parameter which value should
    /// be returned for triplets
    ///
    /// @return Optional value fetched from the global level or the value
    /// of @c property.
    template<typename ReturnType>
    ReturnType getGlobalProperty(ReturnType property,
                                 const int global_index,
                                 const int min_index = -1,
                                 const int max_index = -1) const {
        unused(min_index, max_index);
        if ((global_index >= 0) && fetch_globals_fn_) {
            ConstCfgGlobalsPtr globals = fetch_globals_fn_();
            if (globals) {
                data::ConstElementPtr global_param = globals->get(global_index);
                if (global_param) {
                    // If there is a global parameter, convert it to the
                    // optional value of the given type and return.
                    return (data::ElementValue<typename ReturnType::ValueType>()(global_param));
                }
            }
        }
        return (property);
    }

    /// @brief The @c getGlobalProperty specialization for isc::util::Triplet<T>.
    ///
    /// @note: use overloading vs specialization because full specialization
    /// is not allowed in this scope.
    ///
    /// @tparam NumType Type of the encapsulated value(s).
    ///
    /// @param property Value to be returned when it is specified or when
    /// no global value is found.
    /// @param global_index Index of the global parameter which value should
    /// be returned
    /// @param min_index Index of the min global parameter which value should
    /// be returned for triplets
    /// @param max_index Index of the max global parameter which value should
    /// be returned for triplets
    ///
    /// @return Optional value fetched from the global level or the value
    /// of @c property.
    template<typename NumType>
    isc::util::Triplet<NumType> getGlobalProperty(isc::util::Triplet<NumType> property,
                                                  const int global_index,
                                                  const int min_index = -1,
                                                  const int max_index = -1) const {

        if ((global_index >= 0) && fetch_globals_fn_) {
            ConstCfgGlobalsPtr globals = fetch_globals_fn_();
            if (globals) {
                data::ConstElementPtr param = globals->get(global_index);
                if (param) {
                    NumType def_value = static_cast<NumType>(param->intValue());
                    if ((min_index < 0) || (max_index < 0)) {
                        return (def_value);
                    } else {
                        NumType min_value = def_value;
                        NumType max_value = def_value;
                        data::ConstElementPtr min_param = globals->get(min_index);
                        if (min_param) {
                            min_value = static_cast<NumType>(min_param->intValue());
                        }
                        data::ConstElementPtr max_param = globals->get(max_index);
                        if (max_param) {
                            max_value = static_cast<NumType>(max_param->intValue());
                        }
                        return (isc::util::Triplet<NumType>(min_value, def_value, max_value));
                    }
                }
            }
        }
        return (property);
    }

    /// @brief The @c getGlobalProperty specialization for Optional<IOAddress>.
    ///
    /// This does two things:
    ///  - uses the string value of the parameter
    ///  - falls back when the value is empty
    ///
    /// @note: use overloading vs specialization because full specialization
    /// is not allowed in this scope.
    ///
    /// @param property Value to be returned when it is specified or when
    /// no global value is found.
    /// @param global_index Index of the global parameter which value should
    /// be returned
    /// @param min_index Index of the min global parameter which value should
    /// be returned for triplets
    /// @param max_index Index of the max global parameter which value should
    /// be returned for triplets
    ///
    /// @return Optional value fetched from the global level or the value
    /// of @c property.
    util::Optional<asiolink::IOAddress>
    getGlobalProperty(util::Optional<asiolink::IOAddress> property,
                      const int global_index,
                      const int min_index = -1,
                      const int max_index = -1) const;

    /// @brief Returns a value associated with a network using inheritance.
    ///
    /// This template method provides a generic mechanism to retrieve a
    /// network parameter using inheritance. It is called from public
    /// accessor methods which return an @c OptionalValue or @c isc::util::Triplet.
    ///
    /// @tparam BaseType Type of this instance, e.g. @c Network, @c Network4
    /// etc, which exposes a method to be called.
    /// @tparam ReturnType Type of the returned value, e.g.
    /// @c Optional<std::string>.
    ///
    /// @param MethodPointer Pointer to the method of the base class which
    /// should be called on the parent network instance (typically on
    /// @c SharedNetwork4 or @c SharedNetwork6) to fetch the parent specific
    /// value if the value is unspecified for this instance.
    /// @param property Value to be returned when it is specified or when
    /// no explicit value is specified on upper inheritance levels.
    /// @param inheritance inheritance mode to be used.
    /// @param global_index Optional index of the global parameter which value
    /// should be returned if the given parameter is not specified on network
    /// level. This value is empty by default, which indicates that the
    /// global value for the given parameter is not supported and shouldn't
    /// be fetched.
    /// @param min_index Index of the min global parameter which value should
    /// be returned for triplets
    /// @param max_index Index of the max global parameter which value should
    /// be returned for triplets
    ///
    /// @return Optional value fetched from this instance level, parent
    /// network level or global level
    template<typename BaseType, typename ReturnType>
    ReturnType getProperty(ReturnType(BaseType::*MethodPointer)(const Inheritance&) const,
                           ReturnType property,
                           const Inheritance& inheritance,
                           const int global_index = -1,
                           const int min_index = -1,
                           const int max_index = -1) const {

        // If no inheritance is to be used, return the value for this
        // network regardless if it is specified or not.
        if (inheritance == Inheritance::NONE) {
            return (property);

        } else if (inheritance == Inheritance::PARENT_NETWORK) {
            ReturnType parent_property;

            // Check if this instance has a parent network.
            auto parent = boost::dynamic_pointer_cast<BaseType>(parent_network_.lock());
            if (parent) {
                parent_property = ((*parent).*MethodPointer)(Network::Inheritance::NONE);
            }
            return (parent_property);

        // If global value requested, return it.
        } else if (inheritance == Inheritance::GLOBAL) {
            return (getGlobalProperty(ReturnType(), global_index, min_index, max_index));
        }

        // We use inheritance and the value is not specified on the network level.
        // Hence, we need to get the parent network specific value or global value.
        if (property.unspecified()) {
            // Check if this instance has a parent network.
            auto parent = boost::dynamic_pointer_cast<BaseType>(parent_network_.lock());
            // If the parent network exists, let's fetch the parent specific
            // value.
            if (parent) {
                // We're using inheritance so ask for the parent specific network
                // and return it only if it is specified.
                auto parent_property = ((*parent).*MethodPointer)(inheritance);
                if (!parent_property.unspecified()) {
                    return (parent_property);
                }
            }

            // The value is not specified on network level. If the value
            // can be specified on global level and there is a callback
            // that returns the global values, try to find this parameter
            // at the global scope.
            return (getGlobalProperty(property, global_index, min_index, max_index));
        }

        // We haven't found the value at any level, so return the unspecified.
        return (property);
    }

    /// @brief Returns option pointer associated with a network using inheritance.
    ///
    /// This template method provides a generic mechanism to retrieve a
    /// network parameter using inheritance. It is called from public
    /// accessor methods which return an @c OptionPtr.
    ///
    /// @tparam BaseType Type of this instance, e.g. @c Network, @c Network4
    /// etc, which exposes a method to be called.
    ///
    /// @param MethodPointer Pointer to the method of the base class which
    /// should be called on the parent network instance (typically on
    /// @c SharedNetwork4 or @c SharedNetwork6) to fetch the parent specific
    /// value if the value is unspecified for this instance.
    /// @param property the value to return when inheritance mode is NONE, or
    /// when the mode is PARENT_NETWORK and the property has not been specified
    /// by a parent network.
    /// @param inheritance inheritance mode to be used.
    ///
    /// @return Option pointer fetched from this instance level or parent
    /// network level.
    template<typename BaseType>
    OptionPtr
    getOptionProperty(OptionPtr(BaseType::*MethodPointer)(const Inheritance& inheritance) const,
                      OptionPtr property,
                      const Inheritance& inheritance) const {
        if (inheritance == Network::Inheritance::NONE) {
            return (property);

        } else if (inheritance == Network::Inheritance::PARENT_NETWORK) {
            OptionPtr parent_property;
            // Check if this instance has a parent network.
            auto parent = boost::dynamic_pointer_cast<BaseType>(parent_network_.lock());
            // If the parent network exists, let's fetch the parent specific
            // value.
            if (parent) {
                parent_property = ((*parent).*MethodPointer)(Network::Inheritance::NONE);
            }
            return (parent_property);

        } else if (inheritance == Network::Inheritance::GLOBAL) {
            return (OptionPtr());
        }

        // We use inheritance and the value is not specified on the network level.
        // Hence, we need to get the parent network specific value.
        if (!property) {
            // Check if this instance has a parent network.
            auto parent = boost::dynamic_pointer_cast<BaseType>(parent_network_.lock());
            if (parent) {
                // We're using inheritance so ask for the parent specific network
                // and return it only if it is specified.
                OptionPtr parent_property = (((*parent).*MethodPointer)(inheritance));
                if (parent_property) {
                    return (parent_property);
                }
            }
        }

        // We haven't found the value at any level, so return the unspecified.
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

    /// @brief a isc::util::Triplet (min/default/max) holding allowed renew timer values
    isc::util::Triplet<uint32_t> t1_;

    /// @brief a isc::util::Triplet (min/default/max) holding allowed rebind timer values
    isc::util::Triplet<uint32_t> t2_;

    /// @brief a isc::util::Triplet (min/default/max) holding allowed valid lifetime values
    isc::util::Triplet<uint32_t> valid_;

    /// @brief Enables global reservations.
    util::Optional<bool> reservations_global_;

    /// @brief Enables subnet reservations.
    util::Optional<bool> reservations_in_subnet_;

    /// @brief Enables out-of-pool reservations optimization.
    ///
    /// When true only out-of-pool reservations are allowed. This allows
    /// AllocEngine to skip reservation checks when dealing with addresses
    /// that are in pool.
    util::Optional<bool> reservations_out_of_pool_;

    /// @brief Pointer to the option data configuration for this subnet.
    CfgOptionPtr cfg_option_;

    /// @brief Enables calculation of T1 and T2 timers
    util::Optional<bool> calculate_tee_times_;

    /// @brief Percentage of the lease lifetime to use when calculating T1 timer
    util::Optional<double> t1_percent_;

    /// @brief Percentage of the lease lifetime to use when calculating T2 timer
    util::Optional<double> t2_percent_;

    /// @brief Should Kea perform DNS updates. Used to provide scoped enabling
    /// and disabling of updates.
    util::Optional<bool> ddns_send_updates_;

    /// @brief Should Kea perform updates, even if client requested no updates.
    /// Overrides the client request for no updates via the N flag.
    util::Optional<bool> ddns_override_no_update_;

    /// @brief Should Kea perform updates, even if client requested delegation.
    util::Optional<bool> ddns_override_client_update_;

    /// @brief How Kea should handle the domain-name supplied by the client.
    util::Optional<D2ClientConfig::ReplaceClientNameMode> ddns_replace_client_name_mode_;

    /// @brief Prefix Kea should use when generating domain-names.
    util::Optional<std::string> ddns_generated_prefix_;

    /// @brief Suffix Kea should use when to qualify partial domain-names.
    util::Optional<std::string> ddns_qualifying_suffix_;

    /// @brief Regular expression describing invalid characters for client
    /// hostnames.
    util::Optional<std::string> hostname_char_set_;

    /// @brief A string to replace invalid characters when scrubbing hostnames.
    /// Meaningful only if hostname_char_set_ is not empty.
    util::Optional<std::string> hostname_char_replacement_;

    /// @brief Should Kea store additional client query data (e.g. relay-agent-info)
    /// on the lease.
    util::Optional<bool> store_extended_info_;

    /// @brief Percentage of the lease lifetime to use as cache threshold.
    util::Optional<double> cache_threshold_;

    /// @brief Value in seconds to use as cache maximal age.
    util::Optional<uint32_t> cache_max_age_;

    /// @brief Should Kea perform updates when leases are extended
    util::Optional<bool> ddns_update_on_renew_;

    /// @brief Used to to tell kea-dhcp-ddns whether or not to use conflict resolution.
    util::Optional<bool> ddns_use_conflict_resolution_;

    /// @brief Percentage of the lease lifetime to use for DNS TTL.
    util::Optional<double> ddns_ttl_percent_;

    /// @brief Allocator used for IP address allocations.
    util::Optional<std::string> allocator_type_;

    /// @brief Default allocator type.
    ///
    /// This value is not configurable by the user. It is used by the configuration
    /// backend internally.
    util::Optional<std::string> default_allocator_type_;

    /// @brief Pointer to another network that this network belongs to.
    ///
    /// The most common case is that this instance is a subnet which belongs
    /// to a shared network and the @c parent_network_ points to the shared
    /// network object. If the network instance (subnet) doesn't belong to
    /// a shared network this pointer is null.
    WeakNetworkPtr parent_network_;

    /// @brief Pointer to the optional callback used to fetch globally
    /// configured parameters inherited to the @c Network object.
    FetchNetworkGlobalsFn fetch_globals_fn_;
};

/// @brief Specialization of the @ref Network object for DHCPv4 case.
class Network4 : public virtual Network {
public:

    /// @brief Constructor.
    Network4()
        : Network(), match_client_id_(true, true), authoritative_(),
          siaddr_(), sname_(), filename_(), offer_lft_() {
    }

    /// @brief Returns the flag indicating if the client identifiers should
    /// be used to identify the client's lease.
    ///
    /// @param inheritance inheritance mode to be used.
    /// @return true if client identifiers should be used, false otherwise.
    util::Optional<bool>
    getMatchClientId(const Inheritance& inheritance = Inheritance::ALL) const {
        return (getProperty<Network4>(&Network4::getMatchClientId,
                                      match_client_id_,
                                      inheritance,
                                      CfgGlobals::MATCH_CLIENT_ID));
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
    /// @param inheritance inheritance mode to be used.w
    /// @return true if requests for unknown IP addresses should be rejected,
    /// false otherwise.
    util::Optional<bool>
    getAuthoritative(const Inheritance& inheritance = Inheritance::ALL) const {
        return (getProperty<Network4>(&Network4::getAuthoritative,
                                      authoritative_, inheritance,
                                      CfgGlobals::AUTHORITATIVE));
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
    util::Optional<asiolink::IOAddress>
    getSiaddr(const Inheritance& inheritance = Inheritance::ALL) const {
        return (getProperty<Network4>(&Network4::getSiaddr, siaddr_,
                                      inheritance, CfgGlobals::NEXT_SERVER));
    }

    /// @brief Sets server hostname for the network.
    ///
    /// Will be used for server hostname field (may be empty if not defined)
    void setSname(const util::Optional<std::string>& sname);

    /// @brief Returns server hostname for this network.
    ///
    /// @param inheritance inheritance mode to be used.
    /// @return server hostname value
    util::Optional<std::string>
    getSname(const Inheritance& inheritance = Inheritance::ALL) const {
        return (getProperty<Network4>(&Network4::getSname, sname_,
                                      inheritance,
                                      CfgGlobals::SERVER_HOSTNAME));
    }

    /// @brief Sets boot file name for the network.
    ///
    /// Will be used for boot file name (may be empty if not defined)
    void setFilename(const util::Optional<std::string>& filename);

    /// @brief Returns boot file name for this subnet
    ///
    /// @param inheritance inheritance mode to be used.
    /// @return boot file name value
    util::Optional<std::string>
    getFilename(const Inheritance& inheritance = Inheritance::ALL) const {
        return (getProperty<Network4>(&Network4::getFilename, filename_,
                                      inheritance,
                                      CfgGlobals::BOOT_FILE_NAME));
    }

    /// @brief Sets offer lifetime for the network.
    ///
    /// @param offer_lft the offer lifetime assigned to the class (may be empty if not defined)
    void setOfferLft(const util::Optional<uint32_t>& offer_lft) {
        offer_lft_ = offer_lft;
    }

    /// @brief Returns offer lifetime for the network
    ///
    /// @param inheritance inheritance mode to be used.
    /// @return offer lifetime value
    util::Optional<uint32_t>
    getOfferLft(const Inheritance& inheritance = Inheritance::ALL) const {
        return (getProperty<Network4>(&Network4::getOfferLft, offer_lft_,
                                      inheritance,
                                      CfgGlobals::OFFER_LIFETIME));
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
    util::Optional<bool> match_client_id_;

    /// @brief Should requests for unknown IP addresses be rejected.
    util::Optional<bool> authoritative_;

    /// @brief siaddr value for this network
    util::Optional<asiolink::IOAddress> siaddr_;

    /// @brief server hostname for this network
    util::Optional<std::string> sname_;

    /// @brief boot file name for this network
    util::Optional<std::string> filename_;

    /// @brief offer lifetime for this network
    util::Optional<uint32_t> offer_lft_;
};

/// @brief Pointer to the @ref Network4 object.
typedef boost::shared_ptr<Network4> Network4Ptr;

class Network6;

/// @brief Pointer to the @ref Network6 object.
typedef boost::shared_ptr<Network6> Network6Ptr;

/// @brief Specialization of the @ref Network object for DHCPv6 case.
class Network6 : public virtual Network {
public:

    /// @brief Constructor.
    Network6()
        : Network(), preferred_(), interface_id_(), rapid_commit_(),
          default_pd_allocator_type_(){
    }

    /// @brief Returns preferred lifetime (in seconds)
    ///
    /// @param inheritance inheritance mode to be used.
    /// @return a triplet with preferred lifetime
    isc::util::Triplet<uint32_t>
    getPreferred(const Inheritance& inheritance = Inheritance::ALL) const {
        return (getProperty<Network6>(&Network6::getPreferred, preferred_,
                                      inheritance,
                                      CfgGlobals::PREFERRED_LIFETIME,
                                      CfgGlobals::MIN_PREFERRED_LIFETIME,
                                      CfgGlobals::MAX_PREFERRED_LIFETIME));
    }

    /// @brief Sets new preferred lifetime for a network.
    ///
    /// @param preferred New preferred lifetime in seconds.
    void setPreferred(const isc::util::Triplet<uint32_t>& preferred) {
        preferred_ = preferred;
    }

    /// @brief Returns interface-id value (if specified)
    ///
    /// @param inheritance inheritance mode to be used.
    /// @return interface-id option (if defined)
    OptionPtr getInterfaceId(const Inheritance& inheritance = Inheritance::ALL) const {
        return (getOptionProperty<Network6>(&Network6::getInterfaceId, interface_id_,
                                            inheritance));
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
    /// @note This parameter does not exist at the global level.
    ///
    /// @param inheritance inheritance mode to be used.
    /// @return true if the Rapid Commit option is supported, false otherwise.
    util::Optional<bool>
    getRapidCommit(const Inheritance& inheritance = Inheritance::ALL) const {

        return (getProperty<Network6>(&Network6::getRapidCommit, rapid_commit_,
                                      inheritance));
    }

    /// @brief Enables or disables Rapid Commit option support for the subnet.
    ///
    /// @param rapid_commit A boolean value indicating that the Rapid Commit
    /// option support is enabled (if true), or disabled (if false).
    void setRapidCommit(const util::Optional<bool>& rapid_commit) {
        rapid_commit_ = rapid_commit;
    };

    /// @brief Returns allocator type for prefix delegation.
    ///
    /// @param inheritance inheritance mode to be used.
    util::Optional<std::string>
    getPdAllocatorType(const Inheritance& inheritance = Inheritance::ALL) const {
        return (getProperty<Network6>(&Network6::getPdAllocatorType,
                                      pd_allocator_type_,
                                      inheritance,
                                      CfgGlobals::PD_ALLOCATOR));
    }

    /// @brief Sets new allocator type for prefix delegation.
    ///
    /// It doesn't set the actual allocator instance. It merely remembers the
    /// value specified in the configuration, so it can be output in the
    /// @c toElement call.
    ///
    /// @param allocator_type new allocator type to use.
    void setPdAllocatorType(const util::Optional<std::string>& allocator_type) {
        pd_allocator_type_ = allocator_type;
    }

    /// @brief Returns a default allocator type for prefix delegation.
    ///
    /// This allocator type is used when the allocator type is neither specified
    /// at the shared network nor subnet level.
    ///
    /// @return an allocator type as a string.
    util::Optional<std::string>
    getDefaultPdAllocatorType(const Inheritance& inheritance = Inheritance::ALL) const {
        return (getProperty<Network6>(&Network6::getDefaultPdAllocatorType,
                                      default_pd_allocator_type_,
                                      inheritance));
    }

    /// @brief Sets a defalt allocator type for prefix delegation.
    ///
    /// @param allocator_type a new default allocator type.
    void setDefaultPdAllocatorType(const std::string& allocator_type) {
        default_pd_allocator_type_ = allocator_type;
    }

    /// @brief Unparses network object.
    ///
    /// @return A pointer to unparsed network configuration.
    virtual data::ElementPtr toElement() const;

private:

    /// @brief a triplet with preferred lifetime (in seconds)
    isc::util::Triplet<uint32_t> preferred_;

    /// @brief specifies optional interface-id
    OptionPtr interface_id_;

    /// @brief A flag indicating if Rapid Commit option is supported
    /// for this network.
    ///
    /// It's default value is false, which indicates that the Rapid
    /// Commit is disabled for the subnet.
    util::Optional<bool> rapid_commit_;

    /// @brief Allocator used for prefix delegation.
    util::Optional<std::string> pd_allocator_type_;

    // @brief Default allocator type for prefix delegation.
    util::Optional<std::string> default_pd_allocator_type_;
};

} // end of namespace isc::dhcp
} // end of namespace isc

#endif // NETWORK_H
