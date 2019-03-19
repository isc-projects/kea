// Copyright (C) 2011-2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <kea_version.h>

#include <dhcp/dhcp4.h>
#include <dhcp/duid.h>
#include <dhcp/hwaddr.h>
#include <dhcp/iface_mgr.h>
#include <dhcp/libdhcp++.h>
#include <dhcp/option4_addrlst.h>
#include <dhcp/option_custom.h>
#include <dhcp/option_int.h>
#include <dhcp/option_int_array.h>
#include <dhcp/option_vendor.h>
#include <dhcp/option_string.h>
#include <dhcp/pkt4.h>
#include <dhcp/pkt4o6.h>
#include <dhcp/pkt6.h>
#include <dhcp/docsis3_option_defs.h>
#include <dhcp4/dhcp4to6_ipc.h>
#include <dhcp4/dhcp4_log.h>
#include <dhcp4/dhcp4_srv.h>
#include <asiolink/addr_utilities.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/cfg_host_operations.h>
#include <dhcpsrv/cfg_iface.h>
#include <dhcpsrv/cfg_shared_networks.h>
#include <dhcpsrv/cfg_subnets4.h>
#include <dhcpsrv/lease_mgr.h>
#include <dhcpsrv/lease_mgr_factory.h>
#include <dhcpsrv/ncr_generator.h>
#include <dhcpsrv/shared_network.h>
#include <dhcpsrv/subnet.h>
#include <dhcpsrv/subnet_selector.h>
#include <dhcpsrv/utils.h>
#include <dhcpsrv/utils.h>
#include <eval/evaluate.h>
#include <eval/eval_messages.h>
#include <hooks/callout_handle.h>
#include <hooks/hooks_log.h>
#include <hooks/hooks_manager.h>
#include <stats/stats_mgr.h>
#include <util/strutil.h>
#include <stats/stats_mgr.h>
#include <log/logger.h>
#include <cryptolink/cryptolink.h>
#include <cfgrpt/config_report.h>

#ifdef HAVE_MYSQL
#include <dhcpsrv/mysql_lease_mgr.h>
#endif
#ifdef HAVE_PGSQL
#include <dhcpsrv/pgsql_lease_mgr.h>
#endif
#ifdef HAVE_CQL
#include <dhcpsrv/cql_lease_mgr.h>
#endif
#include <dhcpsrv/memfile_lease_mgr.h>

#include <boost/algorithm/string.hpp>
#include <boost/bind.hpp>
#include <boost/foreach.hpp>
#include <boost/pointer_cast.hpp>
#include <boost/shared_ptr.hpp>

#include <iomanip>

using namespace isc;
using namespace isc::asiolink;
using namespace isc::cryptolink;
using namespace isc::dhcp;
using namespace isc::dhcp_ddns;
using namespace isc::hooks;
using namespace isc::log;
using namespace isc::stats;
using namespace std;

namespace {

/// Structure that holds registered hook indexes
struct Dhcp4Hooks {
    int hook_index_buffer4_receive_;   ///< index for "buffer4_receive" hook point
    int hook_index_pkt4_receive_;      ///< index for "pkt4_receive" hook point
    int hook_index_subnet4_select_;    ///< index for "subnet4_select" hook point
    int hook_index_leases4_committed_; ///< index for "leases4_committed" hook point
    int hook_index_lease4_release_;    ///< index for "lease4_release" hook point
    int hook_index_pkt4_send_;         ///< index for "pkt4_send" hook point
    int hook_index_buffer4_send_;      ///< index for "buffer4_send" hook point
    int hook_index_lease4_decline_;    ///< index for "lease4_decline" hook point
    int hook_index_host4_identifier_;  ///< index for "host4_identifier" hook point

    /// Constructor that registers hook points for DHCPv4 engine
    Dhcp4Hooks() {
        hook_index_buffer4_receive_   = HooksManager::registerHook("buffer4_receive");
        hook_index_pkt4_receive_      = HooksManager::registerHook("pkt4_receive");
        hook_index_subnet4_select_    = HooksManager::registerHook("subnet4_select");
        hook_index_leases4_committed_ = HooksManager::registerHook("leases4_committed");
        hook_index_pkt4_send_         = HooksManager::registerHook("pkt4_send");
        hook_index_lease4_release_    = HooksManager::registerHook("lease4_release");
        hook_index_buffer4_send_      = HooksManager::registerHook("buffer4_send");
        hook_index_lease4_decline_    = HooksManager::registerHook("lease4_decline");
        hook_index_host4_identifier_  = HooksManager::registerHook("host4_identifier");
    }
};

} // end of anonymous namespace

// Declare a Hooks object. As this is outside any function or method, it
// will be instantiated (and the constructor run) when the module is loaded.
// As a result, the hook indexes will be defined before any method in this
// module is called.
Dhcp4Hooks Hooks;


namespace isc {
namespace dhcp {

Dhcpv4Exchange::Dhcpv4Exchange(const AllocEnginePtr& alloc_engine,
                               const Pkt4Ptr& query,
                               const Subnet4Ptr& subnet)
    : alloc_engine_(alloc_engine), query_(query), resp_(),
      context_(new AllocEngine::ClientContext4()) {

    if (!alloc_engine_) {
        isc_throw(BadValue, "alloc_engine value must not be NULL"
                  " when creating an instance of the Dhcpv4Exchange");
    }

    if (!query_) {
        isc_throw(BadValue, "query value must not be NULL when"
                  " creating an instance of the Dhcpv4Exchange");
    }

    // Create response message.
    initResponse();
    // Select subnet for the query message.
    context_->subnet_ = subnet;
    // Hardware address.
    context_->hwaddr_ = query->getHWAddr();
    // Pointer to client's query.
    context_->query_ = query;

    // If subnet found, retrieve client identifier which will be needed
    // for allocations and search for reservations associated with a
    // subnet/shared network.
    if (subnet) {
        OptionPtr opt_clientid = query->getOption(DHO_DHCP_CLIENT_IDENTIFIER);
        if (opt_clientid) {
            context_->clientid_.reset(new ClientId(opt_clientid->getData()));
        }

        // Find static reservations if not disabled for our subnet.
        if (subnet->getHostReservationMode() != Network::HR_DISABLED) {
            // Before we can check for static reservations, we need to prepare a set
            // of identifiers to be used for this.
            setHostIdentifiers();

            // Check for static reservations.
            alloc_engine->findReservation(*context_);
        }
    }

    // Set KNOWN builtin class if something was found, UNKNOWN if not.
    if (!context_->hosts_.empty()) {
        query->addClass("KNOWN");
        LOG_DEBUG(dhcp4_logger, DBG_DHCP4_BASIC, DHCP4_CLASS_ASSIGNED)
            .arg(query->getLabel())
            .arg("KNOWN");
    } else {
        query->addClass("UNKNOWN");
        LOG_DEBUG(dhcp4_logger, DBG_DHCP4_BASIC, DHCP4_CLASS_ASSIGNED)
            .arg(query->getLabel())
            .arg("UNKNOWN");
    }

    // Perform second pass of classification.
    Dhcpv4Srv::evaluateClasses(query, true);

    const ClientClasses& classes = query_->getClasses();
    if (!classes.empty()) {
        LOG_DEBUG(dhcp4_logger, DBG_DHCP4_BASIC, DHCP4_CLASS_ASSIGNED)
            .arg(query_->getLabel())
            .arg(classes.toText());
    }
};

void
Dhcpv4Exchange::initResponse() {
    uint8_t resp_type = 0;
    switch (getQuery()->getType()) {
    case DHCPDISCOVER:
        resp_type = DHCPOFFER;
        break;
    case DHCPREQUEST:
    case DHCPINFORM:
        resp_type = DHCPACK;
        break;
    default:
        ;
    }
    // Only create a response if one is required.
    if (resp_type > 0) {
        resp_.reset(new Pkt4(resp_type, getQuery()->getTransid()));
        copyDefaultFields();
        copyDefaultOptions();

        if (getQuery()->isDhcp4o6()) {
            initResponse4o6();
        }
    }
}

void
Dhcpv4Exchange::initResponse4o6() {
    Pkt4o6Ptr query = boost::dynamic_pointer_cast<Pkt4o6>(getQuery());
    if (!query) {
        return;
    }
    const Pkt6Ptr& query6 = query->getPkt6();
    Pkt6Ptr resp6(new Pkt6(DHCPV6_DHCPV4_RESPONSE, query6->getTransid()));
    // Don't add client-id or server-id
    // But copy relay info
    if (!query6->relay_info_.empty()) {
        resp6->copyRelayInfo(query6);
    }
    // Copy interface, and remote address and port
    resp6->setIface(query6->getIface());
    resp6->setIndex(query6->getIndex());
    resp6->setRemoteAddr(query6->getRemoteAddr());
    resp6->setRemotePort(query6->getRemotePort());
    resp_.reset(new Pkt4o6(resp_, resp6));
}

void
Dhcpv4Exchange::copyDefaultFields() {
    resp_->setIface(query_->getIface());
    resp_->setIndex(query_->getIndex());

    // explicitly set this to 0
    resp_->setSiaddr(IOAddress::IPV4_ZERO_ADDRESS());
    // ciaddr is always 0, except for the Renew/Rebind state when it may
    // be set to the ciaddr sent by the client.
    resp_->setCiaddr(IOAddress::IPV4_ZERO_ADDRESS());
    resp_->setHops(query_->getHops());

    // copy MAC address
    resp_->setHWAddr(query_->getHWAddr());

    // relay address
    resp_->setGiaddr(query_->getGiaddr());

    // If src/dest HW addresses are used by the packet filtering class
    // we need to copy them as well. There is a need to check that the
    // address being set is not-NULL because an attempt to set the NULL
    // HW would result in exception. If these values are not set, the
    // the default HW addresses (zeroed) should be generated by the
    // packet filtering class when creating Ethernet header for
    // outgoing packet.
    HWAddrPtr src_hw_addr = query_->getLocalHWAddr();
    if (src_hw_addr) {
        resp_->setLocalHWAddr(src_hw_addr);
    }
    HWAddrPtr dst_hw_addr = query_->getRemoteHWAddr();
    if (dst_hw_addr) {
        resp_->setRemoteHWAddr(dst_hw_addr);
    }

    // Copy flags from the request to the response per RFC 2131
    resp_->setFlags(query_->getFlags());
}

void
Dhcpv4Exchange::copyDefaultOptions() {
    // Let's copy client-id to response. See RFC6842.
    // It is possible to disable RFC6842 to keep backward compatibility
    bool echo = CfgMgr::instance().getCurrentCfg()->getEchoClientId();
    OptionPtr client_id = query_->getOption(DHO_DHCP_CLIENT_IDENTIFIER);
    if (client_id && echo) {
        resp_->addOption(client_id);
    }

    // If this packet is relayed, we want to copy Relay Agent Info option
    // when it is not empty.
    OptionPtr rai = query_->getOption(DHO_DHCP_AGENT_OPTIONS);
    if (rai && (rai->len() > Option::OPTION4_HDR_LEN)) {
        resp_->addOption(rai);
    }

    // RFC 3011 states about the Subnet Selection Option

    // "Servers configured to support this option MUST return an
    //  identical copy of the option to any client that sends it,
    //  regardless of whether or not the client requests the option in
    //  a parameter request list. Clients using this option MUST
    //  discard DHCPOFFER or DHCPACK packets that do not contain this
    //  option."
    OptionPtr subnet_sel = query_->getOption(DHO_SUBNET_SELECTION);
    if (subnet_sel) {
        resp_->addOption(subnet_sel);
    }
}

void
Dhcpv4Exchange::setHostIdentifiers() {
    const ConstCfgHostOperationsPtr cfg =
        CfgMgr::instance().getCurrentCfg()->getCfgHostOperations4();

    // Collect host identifiers. The identifiers are stored in order of preference.
    // The server will use them in that order to search for host reservations.
    BOOST_FOREACH(const Host::IdentifierType& id_type,
                  cfg->getIdentifierTypes()) {
        switch (id_type) {
        case Host::IDENT_HWADDR:
            if (context_->hwaddr_ && !context_->hwaddr_->hwaddr_.empty()) {
                context_->addHostIdentifier(id_type, context_->hwaddr_->hwaddr_);
            }
            break;

        case Host::IDENT_DUID:
            if (context_->clientid_) {
                const std::vector<uint8_t>& vec = context_->clientid_->getDuid();
                if (!vec.empty()) {
                    // Client identifier type = DUID? Client identifier holding a DUID
                    // comprises Type (1 byte), IAID (4 bytes), followed by the actual
                    // DUID. Thus, the minimal length is 6.
                    if ((vec[0] == CLIENT_ID_OPTION_TYPE_DUID) && (vec.size() > 5)) {
                        // Extract DUID, skip IAID.
                        context_->addHostIdentifier(id_type,
                                                    std::vector<uint8_t>(vec.begin() + 5,
                                                                         vec.end()));
                    }
                }
            }
            break;

        case Host::IDENT_CIRCUIT_ID:
            {
                OptionPtr rai = query_->getOption(DHO_DHCP_AGENT_OPTIONS);
                if (rai) {
                    OptionPtr circuit_id_opt = rai->getOption(RAI_OPTION_AGENT_CIRCUIT_ID);
                    if (circuit_id_opt) {
                        const OptionBuffer& circuit_id_vec = circuit_id_opt->getData();
                        if (!circuit_id_vec.empty()) {
                            context_->addHostIdentifier(id_type, circuit_id_vec);
                        }
                    }
                }
            }
            break;

        case Host::IDENT_CLIENT_ID:
            if (context_->clientid_) {
                const std::vector<uint8_t>& vec = context_->clientid_->getDuid();
                if (!vec.empty()) {
                    context_->addHostIdentifier(id_type, vec);
                }
            }
            break;
        case Host::IDENT_FLEX:
            {
                if (!HooksManager::calloutsPresent(Hooks.hook_index_host4_identifier_)) {
                    break;
                }

                CalloutHandlePtr callout_handle = getCalloutHandle(context_->query_);

                Host::IdentifierType type = Host::IDENT_FLEX;
                std::vector<uint8_t> id;

                // Use the RAII wrapper to make sure that the callout handle state is
                // reset when this object goes out of scope. All hook points must do
                // it to prevent possible circular dependency between the callout
                // handle and its arguments.
                ScopedCalloutHandleState callout_handle_state(callout_handle);

                // Pass incoming packet as argument
                callout_handle->setArgument("query4", context_->query_);
                callout_handle->setArgument("id_type", type);
                callout_handle->setArgument("id_value", id);

                // Call callouts
                HooksManager::callCallouts(Hooks.hook_index_host4_identifier_,
                                           *callout_handle);

                callout_handle->getArgument("id_type", type);
                callout_handle->getArgument("id_value", id);

                if ((callout_handle->getStatus() == CalloutHandle::NEXT_STEP_CONTINUE) &&
                    !id.empty()) {

                    LOG_DEBUG(packet4_logger, DBGLVL_TRACE_BASIC, DHCP4_FLEX_ID)
                        .arg(Host::getIdentifierAsText(type, &id[0], id.size()));

                    context_->addHostIdentifier(type, id);
                }
                break;
            }
        default:
            ;
        }
    }
}

void
Dhcpv4Exchange::setReservedClientClasses() {
    if (context_->currentHost() && query_) {
        const ClientClasses& classes = context_->currentHost()->getClientClasses4();
        for (ClientClasses::const_iterator cclass = classes.cbegin();
             cclass != classes.cend(); ++cclass) {
            query_->addClass(*cclass);
        }
    }
}

void
Dhcpv4Exchange::setReservedMessageFields() {
    ConstHostPtr host = context_->currentHost();
    // Nothing to do if host reservations not specified for this client.
    if (host) {
        if (!host->getNextServer().isV4Zero()) {
            resp_->setSiaddr(host->getNextServer());
        }

        std::string sname = host->getServerHostname();
        if (!sname.empty()) {
            resp_->setSname(reinterpret_cast<const uint8_t*>(sname.c_str()),
                            sname.size());
        }

        std::string bootfile = host->getBootFileName();
        if (!bootfile.empty()) {
            resp_->setFile(reinterpret_cast<const uint8_t*>(bootfile.c_str()),
                           bootfile.size());
        }
    }
}

const std::string Dhcpv4Srv::VENDOR_CLASS_PREFIX("VENDOR_CLASS_");

Dhcpv4Srv::Dhcpv4Srv(uint16_t server_port, uint16_t client_port,
                     const bool use_bcast, const bool direct_response_desired)
    : io_service_(new IOService()), shutdown_(true), alloc_engine_(),
      server_port_(server_port), use_bcast_(use_bcast),
      client_port_(client_port),
      network_state_(new NetworkState(NetworkState::DHCPv4)),
      cb_control_(new CBControlDHCPv4()) {

    LOG_DEBUG(dhcp4_logger, DBG_DHCP4_START, DHCP4_OPEN_SOCKET)
        .arg(server_port);
    try {
        // Port 0 is used for testing purposes where we don't open broadcast
        // capable sockets. So, set the packet filter handling direct traffic
        // only if we are in non-test mode.
        if (server_port) {
            // First call to instance() will create IfaceMgr (it's a singleton)
            // it may throw something if things go wrong.
            // The 'true' value of the call to setMatchingPacketFilter imposes
            // that IfaceMgr will try to use the mechanism to respond directly
            // to the client which doesn't have address assigned. This capability
            // may be lacking on some OSes, so there is no guarantee that server
            // will be able to respond directly.
            IfaceMgr::instance().setMatchingPacketFilter(direct_response_desired);
        }

        // Instantiate allocation engine. The number of allocation attempts equal
        // to zero indicates that the allocation engine will use the number of
        // attempts depending on the pool size.
        alloc_engine_.reset(new AllocEngine(AllocEngine::ALLOC_ITERATIVE, 0,
                                            false /* false = IPv4 */));

        /// @todo call loadLibraries() when handling configuration changes

    } catch (const std::exception &e) {
        LOG_ERROR(dhcp4_logger, DHCP4_SRV_CONSTRUCT_ERROR).arg(e.what());
        shutdown_ = true;
        return;
    }

    shutdown_ = false;
}

Dhcpv4Srv::~Dhcpv4Srv() {
    // Discard any cached packets or parked packets
    discardPackets();

    try {
        stopD2();
    } catch(const std::exception& ex) {
        // Highly unlikely, but lets Report it but go on
        LOG_ERROR(dhcp4_logger, DHCP4_SRV_D2STOP_ERROR).arg(ex.what());
    }

    try {
        Dhcp4to6Ipc::instance().close();
    } catch(const std::exception& ex) {
        // Highly unlikely, but lets Report it but go on
        LOG_ERROR(dhcp4_logger, DHCP4_SRV_DHCP4O6_ERROR).arg(ex.what());
    }

    IfaceMgr::instance().closeSockets();

    // The lease manager was instantiated during DHCPv4Srv configuration,
    // so we should clean up after ourselves.
    LeaseMgrFactory::destroy();

    // Explicitly unload hooks
    HooksManager::getHooksManager().unloadLibraries();
}

void
Dhcpv4Srv::shutdown() {
    LOG_DEBUG(dhcp4_logger, DBG_DHCP4_BASIC, DHCP4_SHUTDOWN_REQUEST);
    shutdown_ = true;
}

isc::dhcp::Subnet4Ptr
Dhcpv4Srv::selectSubnet(const Pkt4Ptr& query, bool& drop,
                        bool sanity_only) const {

    // DHCPv4-over-DHCPv6 is a special (and complex) case
    if (query->isDhcp4o6()) {
        return (selectSubnet4o6(query, drop, sanity_only));
    }

    Subnet4Ptr subnet;

    const SubnetSelector& selector = CfgSubnets4::initSelector(query);

    CfgMgr& cfgmgr = CfgMgr::instance();
    subnet = cfgmgr.getCurrentCfg()->getCfgSubnets4()->selectSubnet(selector);

    // Let's execute all callouts registered for subnet4_select
    // (skip callouts if the selectSubnet was called to do sanity checks only)
    if (!sanity_only &&
        HooksManager::calloutsPresent(Hooks.hook_index_subnet4_select_)) {
        CalloutHandlePtr callout_handle = getCalloutHandle(query);

        // Use the RAII wrapper to make sure that the callout handle state is
        // reset when this object goes out of scope. All hook points must do
        // it to prevent possible circular dependency between the callout
        // handle and its arguments.
        ScopedCalloutHandleState callout_handle_state(callout_handle);

        // Enable copying options from the packet within hook library.
        ScopedEnableOptionsCopy<Pkt4> query4_options_copy(query);

        // Set new arguments
        callout_handle->setArgument("query4", query);
        callout_handle->setArgument("subnet4", subnet);
        callout_handle->setArgument("subnet4collection",
                                    cfgmgr.getCurrentCfg()->
                                    getCfgSubnets4()->getAll());

        // Call user (and server-side) callouts
        HooksManager::callCallouts(Hooks.hook_index_subnet4_select_,
                                   *callout_handle);

        // Callouts decided to skip this step. This means that no subnet
        // will be selected. Packet processing will continue, but it will
        // be severely limited (i.e. only global options will be assigned)
        if (callout_handle->getStatus() == CalloutHandle::NEXT_STEP_SKIP) {
            LOG_DEBUG(hooks_logger, DBG_DHCP4_HOOKS,
                      DHCP4_HOOK_SUBNET4_SELECT_SKIP)
                .arg(query->getLabel());
            return (Subnet4Ptr());
        }

        // Callouts decided to drop the packet. It is a superset of the
        // skip case so no subnet will be selected.
        if (callout_handle->getStatus() == CalloutHandle::NEXT_STEP_DROP) {
            LOG_DEBUG(hooks_logger, DBG_DHCP4_HOOKS,
                      DHCP4_HOOK_SUBNET4_SELECT_DROP)
                .arg(query->getLabel());
            drop = true;
            return (Subnet4Ptr());
        }

        // Use whatever subnet was specified by the callout
        callout_handle->getArgument("subnet4", subnet);
    }

    if (subnet) {
        // Log at higher debug level that subnet has been found.
        LOG_DEBUG(packet4_logger, DBG_DHCP4_BASIC_DATA, DHCP4_SUBNET_SELECTED)
            .arg(query->getLabel())
            .arg(subnet->getID());
        // Log detailed information about the selected subnet at the
        // lower debug level.
        LOG_DEBUG(packet4_logger, DBG_DHCP4_DETAIL_DATA, DHCP4_SUBNET_DATA)
            .arg(query->getLabel())
            .arg(subnet->toText());

    } else {
        LOG_DEBUG(packet4_logger, DBG_DHCP4_DETAIL,
                  DHCP4_SUBNET_SELECTION_FAILED)
            .arg(query->getLabel());
    }

    return (subnet);
}

isc::dhcp::Subnet4Ptr
Dhcpv4Srv::selectSubnet4o6(const Pkt4Ptr& query, bool& drop,
                           bool sanity_only) const {

    Subnet4Ptr subnet;

    SubnetSelector selector;
    selector.ciaddr_ = query->getCiaddr();
    selector.giaddr_ = query->getGiaddr();
    selector.local_address_ = query->getLocalAddr();
    selector.client_classes_ = query->classes_;
    selector.iface_name_ = query->getIface();
    // Mark it as DHCPv4-over-DHCPv6
    selector.dhcp4o6_ = true;
    // Now the DHCPv6 part
    selector.remote_address_ = query->getRemoteAddr();
    selector.first_relay_linkaddr_ = IOAddress("::");

    // Handle a DHCPv6 relayed query
    Pkt4o6Ptr query4o6 = boost::dynamic_pointer_cast<Pkt4o6>(query);
    if (!query4o6) {
        isc_throw(Unexpected, "Can't get DHCP4o6 message");
    }
    const Pkt6Ptr& query6 = query4o6->getPkt6();

    // Initialize fields specific to relayed messages.
    if (query6 && !query6->relay_info_.empty()) {
        BOOST_REVERSE_FOREACH(Pkt6::RelayInfo relay, query6->relay_info_) {
            if (!relay.linkaddr_.isV6Zero() &&
                !relay.linkaddr_.isV6LinkLocal()) {
                selector.first_relay_linkaddr_ = relay.linkaddr_;
                break;
            }
        }
        selector.interface_id_ =
            query6->getAnyRelayOption(D6O_INTERFACE_ID,
                                      Pkt6::RELAY_GET_FIRST);
    }

    // If the Subnet Selection option is present, extract its value.
    OptionPtr sbnsel = query->getOption(DHO_SUBNET_SELECTION);
    if (sbnsel) {
        OptionCustomPtr oc = boost::dynamic_pointer_cast<OptionCustom>(sbnsel);
        if (oc) {
            selector.option_select_ = oc->readAddress();
        }
    }

    CfgMgr& cfgmgr = CfgMgr::instance();
    subnet = cfgmgr.getCurrentCfg()->getCfgSubnets4()->selectSubnet4o6(selector);

    // Let's execute all callouts registered for subnet4_select.
    // (skip callouts if the selectSubnet was called to do sanity checks only)
    if (!sanity_only &&
        HooksManager::calloutsPresent(Hooks.hook_index_subnet4_select_)) {
        CalloutHandlePtr callout_handle = getCalloutHandle(query);

        // Use the RAII wrapper to make sure that the callout handle state is
        // reset when this object goes out of scope. All hook points must do
        // it to prevent possible circular dependency between the callout
        // handle and its arguments.
        ScopedCalloutHandleState callout_handle_state(callout_handle);

        // Set new arguments
        callout_handle->setArgument("query4", query);
        callout_handle->setArgument("subnet4", subnet);
        callout_handle->setArgument("subnet4collection",
                                    cfgmgr.getCurrentCfg()->
                                    getCfgSubnets4()->getAll());

        // Call user (and server-side) callouts
        HooksManager::callCallouts(Hooks.hook_index_subnet4_select_,
                                   *callout_handle);

        // Callouts decided to skip this step. This means that no subnet
        // will be selected. Packet processing will continue, but it will
        // be severely limited (i.e. only global options will be assigned)
        if (callout_handle->getStatus() == CalloutHandle::NEXT_STEP_SKIP) {
            LOG_DEBUG(hooks_logger, DBG_DHCP4_HOOKS,
                      DHCP4_HOOK_SUBNET4_SELECT_SKIP)
                .arg(query->getLabel());
            return (Subnet4Ptr());
        }

        // Callouts decided to drop the packet. It is a superset of the
        // skip case so no subnet will be selected.
        if (callout_handle->getStatus() == CalloutHandle::NEXT_STEP_DROP) {
            LOG_DEBUG(hooks_logger, DBG_DHCP4_HOOKS,
                      DHCP4_HOOK_SUBNET4_SELECT_DROP)
                .arg(query->getLabel());
            drop = true;
            return (Subnet4Ptr());
        }

        // Use whatever subnet was specified by the callout
        callout_handle->getArgument("subnet4", subnet);
    }

    if (subnet) {
        // Log at higher debug level that subnet has been found.
        LOG_DEBUG(packet4_logger, DBG_DHCP4_BASIC_DATA, DHCP4_SUBNET_SELECTED)
            .arg(query->getLabel())
            .arg(subnet->getID());
        // Log detailed information about the selected subnet at the
        // lower debug level.
        LOG_DEBUG(packet4_logger, DBG_DHCP4_DETAIL_DATA, DHCP4_SUBNET_DATA)
            .arg(query->getLabel())
            .arg(subnet->toText());

    } else {
        LOG_DEBUG(packet4_logger, DBG_DHCP4_DETAIL,
                  DHCP4_SUBNET_SELECTION_FAILED)
            .arg(query->getLabel());
    }

    return (subnet);
}

Pkt4Ptr
Dhcpv4Srv::receivePacket(int timeout) {
    return (IfaceMgr::instance().receive4(timeout));
}

void
Dhcpv4Srv::sendPacket(const Pkt4Ptr& packet) {
    IfaceMgr::instance().send(packet);
}

bool
Dhcpv4Srv::run() {
    while (!shutdown_) {
        try {
            run_one();
            getIOService()->poll();
        } catch (const std::exception& e) {
            // General catch-all exception that are not caught by more specific
            // catches. This one is for exceptions derived from std::exception.
            LOG_ERROR(packet4_logger, DHCP4_PACKET_PROCESS_STD_EXCEPTION)
                .arg(e.what());
        } catch (...) {
            // General catch-all exception that are not caught by more specific
            // catches. This one is for other exceptions, not derived from
            // std::exception.
            LOG_ERROR(packet4_logger, DHCP4_PACKET_PROCESS_EXCEPTION);
        }
    }

    return (true);
}

void
Dhcpv4Srv::run_one() {
    // client's message and server's response
    Pkt4Ptr query;
    Pkt4Ptr rsp;

    try {
        // Set select() timeout to 1s. This value should not be modified
        // because it is important that the select() returns control
        // frequently so as the IOService can be polled for ready handlers.
        uint32_t timeout = 1;
        query = receivePacket(timeout);

        // Log if packet has arrived. We can't log the detailed information
        // about the DHCP message because it hasn't been unpacked/parsed
        // yet, and it can't be parsed at this point because hooks will
        // have to process it first. The only information available at this
        // point are: the interface, source address and destination addresses
        // and ports.
        if (query) {
            LOG_DEBUG(packet4_logger, DBG_DHCP4_BASIC, DHCP4_BUFFER_RECEIVED)
                .arg(query->getRemoteAddr().toText())
                .arg(query->getRemotePort())
                .arg(query->getLocalAddr().toText())
                .arg(query->getLocalPort())
                .arg(query->getIface());

        }
        // We used to log that the wait was interrupted, but this is no longer
        // the case. Our wait time is 1s now, so the lack of query packet more
        // likely means that nothing new appeared within a second, rather than
        // we were interrupted. And we don't want to print a message every
        // second.

    } catch (const SignalInterruptOnSelect&) {
        // Packet reception interrupted because a signal has been received.
        // This is not an error because we might have received a SIGTERM,
        // SIGINT, SIGHUP or SIGCHLD which are handled by the server. For
        // signals that are not handled by the server we rely on the default
        // behavior of the system.
        LOG_DEBUG(packet4_logger, DBG_DHCP4_DETAIL, DHCP4_BUFFER_WAIT_SIGNAL)
            .arg(signal_set_->getNext());
    } catch (const std::exception& e) {
        // Log all other errors.
        LOG_ERROR(packet4_logger, DHCP4_BUFFER_RECEIVE_FAIL).arg(e.what());
    }

    // Handle next signal received by the process. It must be called after
    // an attempt to receive a packet to properly handle server shut down.
    // The SIGTERM or SIGINT will be received prior to, or during execution
    // of select() (select is invoked by receivePacket()). When that
    // happens, select will be interrupted. The signal handler will be
    // invoked immediately after select(). The handler will set the
    // shutdown flag and cause the process to terminate before the next
    // select() function is called. If the function was called before
    // receivePacket the process could wait up to the duration of timeout
    // of select() to terminate.
    try {
        handleSignal();
    } catch (const std::exception& e) {
        // Standard exception occurred. Let's be on the safe side to
        // catch std::exception.
        LOG_ERROR(dhcp4_logger, DHCP4_HANDLE_SIGNAL_EXCEPTION)
            .arg(e.what());
    }

    // Timeout may be reached or signal received, which breaks select()
    // with no reception occurred. No need to log anything here because
    // we have logged right after the call to receivePacket().
    if (!query) {
        return;
    }

    // If the DHCP service has been globally disabled, drop the packet.
    if (!network_state_->isServiceEnabled()) {
        LOG_DEBUG(bad_packet4_logger, DBG_DHCP4_BASIC,
                  DHCP4_PACKET_DROP_0008)
            .arg(query->getLabel());
        return;
    } else {
        processPacket(query, rsp);
    }

    if (!rsp) {
        return;
    }

    CalloutHandlePtr callout_handle = getCalloutHandle(query);
    processPacketBufferSend(callout_handle, rsp);
}

void
Dhcpv4Srv::processPacket(Pkt4Ptr& query, Pkt4Ptr& rsp, bool allow_packet_park) {
    // Log reception of the packet. We need to increase it early, as any
    // failures in unpacking will cause the packet to be dropped. We
    // will increase type specific statistic further down the road.
    // See processStatsReceived().
    isc::stats::StatsMgr::instance().addValue("pkt4-received",
                                              static_cast<int64_t>(1));

    bool skip_unpack = false;

    // The packet has just been received so contains the uninterpreted wire
    // data; execute callouts registered for buffer4_receive.
    if (HooksManager::calloutsPresent(Hooks.hook_index_buffer4_receive_)) {
        CalloutHandlePtr callout_handle = getCalloutHandle(query);

        // Use the RAII wrapper to make sure that the callout handle state is
        // reset when this object goes out of scope. All hook points must do
        // it to prevent possible circular dependency between the callout
        // handle and its arguments.
        ScopedCalloutHandleState callout_handle_state(callout_handle);

        // Enable copying options from the packet within hook library.
        ScopedEnableOptionsCopy<Pkt4> query4_options_copy(query);

        // Pass incoming packet as argument
        callout_handle->setArgument("query4", query);

        // Call callouts
        HooksManager::callCallouts(Hooks.hook_index_buffer4_receive_,
                                   *callout_handle);

        // Callouts decided to drop the received packet.
        // The response (rsp) is null so the caller (run_one) will
        // immediately return too.
        if (callout_handle->getStatus() == CalloutHandle::NEXT_STEP_DROP) {
            LOG_DEBUG(hooks_logger, DBG_DHCP4_DETAIL,
                      DHCP4_HOOK_BUFFER_RCVD_DROP)
                .arg(query->getRemoteAddr().toText())
                .arg(query->getLocalAddr().toText())
                .arg(query->getIface());
            return;
        }

        // Callouts decided to skip the next processing step. The next
        // processing step would to parse the packet, so skip at this
        // stage means that callouts did the parsing already, so server
        // should skip parsing.
        if (callout_handle->getStatus() == CalloutHandle::NEXT_STEP_SKIP) {
            LOG_DEBUG(hooks_logger, DBG_DHCP4_DETAIL,
                      DHCP4_HOOK_BUFFER_RCVD_SKIP)
                .arg(query->getRemoteAddr().toText())
                .arg(query->getLocalAddr().toText())
                .arg(query->getIface());
            skip_unpack = true;
        }

        callout_handle->getArgument("query4", query);
    }

    // Unpack the packet information unless the buffer4_receive callouts
    // indicated they did it
    if (!skip_unpack) {
        try {
            LOG_DEBUG(options4_logger, DBG_DHCP4_DETAIL, DHCP4_BUFFER_UNPACK)
                .arg(query->getRemoteAddr().toText())
                .arg(query->getLocalAddr().toText())
                .arg(query->getIface());
            query->unpack();
        } catch (const SkipRemainingOptionsError& e) {
            // An option failed to unpack but we are to attempt to process it
            // anyway.  Log it and let's hope for the best.
            LOG_DEBUG(options4_logger, DBG_DHCP4_DETAIL,
                      DHCP4_PACKET_OPTIONS_SKIPPED)
                .arg(e.what());
        } catch (const std::exception& e) {
            // Failed to parse the packet.
            LOG_DEBUG(bad_packet4_logger, DBG_DHCP4_DETAIL,
                      DHCP4_PACKET_DROP_0001)
                .arg(query->getRemoteAddr().toText())
                .arg(query->getLocalAddr().toText())
                .arg(query->getIface())
                .arg(e.what());

            // Increase the statistics of parse failures and dropped packets.
            isc::stats::StatsMgr::instance().addValue("pkt4-parse-failed",
                                                      static_cast<int64_t>(1));
            isc::stats::StatsMgr::instance().addValue("pkt4-receive-drop",
                                                      static_cast<int64_t>(1));
            return;
        }
    }

    // Update statistics accordingly for received packet.
    processStatsReceived(query);

    // Assign this packet to one or more classes if needed. We need to do
    // this before calling accept(), because getSubnet4() may need client
    // class information.
    classifyPacket(query);

    // Now it is classified the deferred unpacking can be done.
    deferredUnpack(query);

    // Check whether the message should be further processed or discarded.
    // There is no need to log anything here. This function logs by itself.
    if (!accept(query)) {
        // Increase the statistic of dropped packets.
        isc::stats::StatsMgr::instance().addValue("pkt4-receive-drop",
                                                  static_cast<int64_t>(1));
        return;
    }

    // We have sanity checked (in accept() that the Message Type option
    // exists, so we can safely get it here.
    int type = query->getType();
    LOG_DEBUG(packet4_logger, DBG_DHCP4_BASIC_DATA, DHCP4_PACKET_RECEIVED)
        .arg(query->getLabel())
        .arg(query->getName())
        .arg(type)
        .arg(query->getRemoteAddr())
        .arg(query->getLocalAddr())
        .arg(query->getIface());
    LOG_DEBUG(packet4_logger, DBG_DHCP4_DETAIL_DATA, DHCP4_QUERY_DATA)
        .arg(query->getLabel())
        .arg(query->toText());

    // Let's execute all callouts registered for pkt4_receive
    if (HooksManager::calloutsPresent(Hooks.hook_index_pkt4_receive_)) {
        CalloutHandlePtr callout_handle = getCalloutHandle(query);

        // Use the RAII wrapper to make sure that the callout handle state is
        // reset when this object goes out of scope. All hook points must do
        // it to prevent possible circular dependency between the callout
        // handle and its arguments.
        ScopedCalloutHandleState callout_handle_state(callout_handle);

        // Enable copying options from the packet within hook library.
        ScopedEnableOptionsCopy<Pkt4> query4_options_copy(query);

        // Pass incoming packet as argument
        callout_handle->setArgument("query4", query);

        // Call callouts
        HooksManager::callCallouts(Hooks.hook_index_pkt4_receive_,
                                   *callout_handle);

        // Callouts decided to skip the next processing step. The next
        // processing step would to process the packet, so skip at this
        // stage means drop.
        if ((callout_handle->getStatus() == CalloutHandle::NEXT_STEP_SKIP) ||
            (callout_handle->getStatus() == CalloutHandle::NEXT_STEP_DROP)) {
            LOG_DEBUG(hooks_logger, DBG_DHCP4_HOOKS,
                      DHCP4_HOOK_PACKET_RCVD_SKIP)
                .arg(query->getLabel());
            return;
        }

        callout_handle->getArgument("query4", query);
    }

    AllocEngine::ClientContext4Ptr ctx;

    try {
        switch (query->getType()) {
        case DHCPDISCOVER:
            rsp = processDiscover(query);
            break;

        case DHCPREQUEST:
            // Note that REQUEST is used for many things in DHCPv4: for
            // requesting new leases, renewing existing ones and even
            // for rebinding.
            rsp = processRequest(query, ctx);
            break;

        case DHCPRELEASE:
            processRelease(query, ctx);
            break;

        case DHCPDECLINE:
            processDecline(query, ctx);
            break;

        case DHCPINFORM:
            rsp = processInform(query);
            break;

        default:
            // Only action is to output a message if debug is enabled,
            // and that is covered by the debug statement before the
            // "switch" statement.
            ;
        }
    } catch (const std::exception& e) {

        // Catch-all exception (we used to call only isc::Exception, but
        // std::exception could potentially be raised and if we don't catch
        // it here, it would be caught in main() and the process would
        // terminate).  Just log the problem and ignore the packet.
        // (The problem is logged as a debug message because debug is
        // disabled by default - it prevents a DDOS attack based on the
        // sending of problem packets.)
        LOG_DEBUG(bad_packet4_logger, DBG_DHCP4_BASIC,
                  DHCP4_PACKET_DROP_0007)
            .arg(query->getLabel())
            .arg(e.what());

        // Increase the statistic of dropped packets.
        isc::stats::StatsMgr::instance().addValue("pkt4-receive-drop",
                                                  static_cast<int64_t>(1));
    }

    bool packet_park = false;

    if (ctx && HooksManager::calloutsPresent(Hooks.hook_index_leases4_committed_)) {
        CalloutHandlePtr callout_handle = getCalloutHandle(query);

        // Use the RAII wrapper to make sure that the callout handle state is
        // reset when this object goes out of scope. All hook points must do
        // it to prevent possible circular dependency between the callout
        // handle and its arguments.
        ScopedCalloutHandleState callout_handle_state(callout_handle);

        ScopedEnableOptionsCopy<Pkt4> query4_options_copy(query);

        // Also pass the corresponding query packet as argument
        callout_handle->setArgument("query4", query);

        Lease4CollectionPtr new_leases(new Lease4Collection());
        if (ctx->new_lease_) {
            new_leases->push_back(ctx->new_lease_);
        }
        callout_handle->setArgument("leases4", new_leases);

        Lease4CollectionPtr deleted_leases(new Lease4Collection());
        if (ctx->old_lease_) {
            if ((!ctx->new_lease_) || (ctx->new_lease_->addr_ != ctx->old_lease_->addr_)) {
                deleted_leases->push_back(ctx->old_lease_);
            }
        }
        callout_handle->setArgument("deleted_leases4", deleted_leases);

        // Call all installed callouts
        HooksManager::callCallouts(Hooks.hook_index_leases4_committed_,
                                   *callout_handle);

        if (callout_handle->getStatus() == CalloutHandle::NEXT_STEP_DROP) {
            LOG_DEBUG(hooks_logger, DBG_DHCP4_HOOKS,
                      DHCP4_HOOK_LEASES4_COMMITTED_DROP)
                .arg(query->getLabel());
            rsp.reset();

        } else if ((callout_handle->getStatus() == CalloutHandle::NEXT_STEP_PARK)
                   && allow_packet_park) {
            packet_park = true;
        }
    }

    if (!rsp) {
        return;
    }

    // PARKING SPOT after leases4_committed hook point.
    CalloutHandlePtr callout_handle = getCalloutHandle(query);
    if (packet_park) {
        LOG_DEBUG(hooks_logger, DBG_DHCP4_HOOKS,
                  DHCP4_HOOK_LEASES4_COMMITTED_PARK)
            .arg(query->getLabel());

        // Park the packet. The function we bind here will be executed when the hook
        // library unparks the packet.
        HooksManager::park("leases4_committed", query,
        [this, callout_handle, query, rsp]() mutable {
            processPacketPktSend(callout_handle, query, rsp);
            processPacketBufferSend(callout_handle, rsp);
        });

        // If we have parked the packet, let's reset the pointer to the
        // response to indicate to the caller that it should return, as
        // the packet processing will continue via the callback.
        rsp.reset();

    } else {
        processPacketPktSend(callout_handle, query, rsp);
    }
}

void
Dhcpv4Srv::processPacketPktSend(hooks::CalloutHandlePtr& callout_handle,
                                Pkt4Ptr& query, Pkt4Ptr& rsp) {
    if (!rsp) {
        return;
    }

    // Specifies if server should do the packing
    bool skip_pack = false;

    // Execute all callouts registered for pkt4_send
    if (HooksManager::calloutsPresent(Hooks.hook_index_pkt4_send_)) {

        // Use the RAII wrapper to make sure that the callout handle state is
        // reset when this object goes out of scope. All hook points must do
        // it to prevent possible circular dependency between the callout
        // handle and its arguments.
        ScopedCalloutHandleState callout_handle_state(callout_handle);

        // Enable copying options from the query and response packets within
        // hook library.
        ScopedEnableOptionsCopy<Pkt4> query_resp_options_copy(query, rsp);

        // Set our response
        callout_handle->setArgument("response4", rsp);

        // Also pass the corresponding query packet as argument
        callout_handle->setArgument("query4", query);

        // Call all installed callouts
        HooksManager::callCallouts(Hooks.hook_index_pkt4_send_,
                                   *callout_handle);

        // Callouts decided to skip the next processing step. The next
        // processing step would to send the packet, so skip at this
        // stage means "drop response".
        if ((callout_handle->getStatus() == CalloutHandle::NEXT_STEP_SKIP) ||
            (callout_handle->getStatus() == CalloutHandle::NEXT_STEP_DROP)) {
            LOG_DEBUG(hooks_logger, DBG_DHCP4_HOOKS,
                      DHCP4_HOOK_PACKET_SEND_SKIP)
                .arg(query->getLabel());
            skip_pack = true;
        }
    }

    if (!skip_pack) {
        try {
            LOG_DEBUG(options4_logger, DBG_DHCP4_DETAIL, DHCP4_PACKET_PACK)
                .arg(rsp->getLabel());
            rsp->pack();
        } catch (const std::exception& e) {
            LOG_ERROR(options4_logger, DHCP4_PACKET_PACK_FAIL)
                .arg(rsp->getLabel())
                .arg(e.what());
        }
    }
}

void
Dhcpv4Srv::processPacketBufferSend(CalloutHandlePtr& callout_handle,
                                   Pkt4Ptr& rsp) {
    if (!rsp) {
        return;
    }

    try {
        // Now all fields and options are constructed into output wire buffer.
        // Option objects modification does not make sense anymore. Hooks
        // can only manipulate wire buffer at this stage.
        // Let's execute all callouts registered for buffer4_send
        if (HooksManager::calloutsPresent(Hooks.hook_index_buffer4_send_)) {

            // Use the RAII wrapper to make sure that the callout handle state is
            // reset when this object goes out of scope. All hook points must do
            // it to prevent possible circular dependency between the callout
            // handle and its arguments.
            ScopedCalloutHandleState callout_handle_state(callout_handle);

            // Enable copying options from the packet within hook library.
            ScopedEnableOptionsCopy<Pkt4> resp4_options_copy(rsp);

            // Pass incoming packet as argument
            callout_handle->setArgument("response4", rsp);

            // Call callouts
            HooksManager::callCallouts(Hooks.hook_index_buffer4_send_,
                                       *callout_handle);

            // Callouts decided to skip the next processing step. The next
            // processing step would to parse the packet, so skip at this
            // stage means drop.
            if ((callout_handle->getStatus() == CalloutHandle::NEXT_STEP_SKIP) ||
                (callout_handle->getStatus() == CalloutHandle::NEXT_STEP_DROP)) {
                LOG_DEBUG(hooks_logger, DBG_DHCP4_HOOKS,
                          DHCP4_HOOK_BUFFER_SEND_SKIP)
                    .arg(rsp->getLabel());
                return;
            }

            callout_handle->getArgument("response4", rsp);
        }

        LOG_DEBUG(packet4_logger, DBG_DHCP4_BASIC, DHCP4_PACKET_SEND)
            .arg(rsp->getLabel())
            .arg(rsp->getName())
            .arg(static_cast<int>(rsp->getType()))
            .arg(rsp->getLocalAddr().isV4Zero() ? "*" : rsp->getLocalAddr().toText())
            .arg(rsp->getLocalPort())
            .arg(rsp->getRemoteAddr())
            .arg(rsp->getRemotePort())
            .arg(rsp->getIface().empty() ? "to be determined from routing" :
                 rsp->getIface());

        LOG_DEBUG(packet4_logger, DBG_DHCP4_DETAIL_DATA,
                  DHCP4_RESPONSE_DATA)
            .arg(rsp->getLabel())
            .arg(rsp->getName())
            .arg(static_cast<int>(rsp->getType()))
            .arg(rsp->toText());
        sendPacket(rsp);

        // Update statistics accordingly for sent packet.
        processStatsSent(rsp);

    } catch (const std::exception& e) {
        LOG_ERROR(packet4_logger, DHCP4_PACKET_SEND_FAIL)
            .arg(rsp->getLabel())
            .arg(e.what());
    }
}

string
Dhcpv4Srv::srvidToString(const OptionPtr& srvid) {
    if (!srvid) {
        isc_throw(BadValue, "NULL pointer passed to srvidToString()");
    }
    boost::shared_ptr<Option4AddrLst> generated =
        boost::dynamic_pointer_cast<Option4AddrLst>(srvid);
    if (!srvid) {
        isc_throw(BadValue, "Pointer to invalid option passed to srvidToString()");
    }

    Option4AddrLst::AddressContainer addrs = generated->getAddresses();
    if (addrs.size() != 1) {
        isc_throw(BadValue, "Malformed option passed to srvidToString(). "
                  << "Expected to contain a single IPv4 address.");
    }

    return (addrs[0].toText());
}

void
Dhcpv4Srv::appendServerID(Dhcpv4Exchange& ex) {

    // Do not append generated server identifier if there is one appended already.
    // This is when explicitly configured server identifier option is present.
    if (ex.getResponse()->getOption(DHO_DHCP_SERVER_IDENTIFIER)) {
        return;
    }

    // Use local address on which the packet has been received as a
    // server identifier. In some cases it may be a different address,
    // e.g. broadcast packet or DHCPv4o6 packet.
    IOAddress local_addr = ex.getQuery()->getLocalAddr();
    Pkt4Ptr query = ex.getQuery();

    if (local_addr.isV4Bcast() || query->isDhcp4o6()) {
        SocketInfo sock_info = IfaceMgr::instance().getSocket(*query);
        local_addr = sock_info.addr_;
    }

    OptionPtr opt_srvid(new Option4AddrLst(DHO_DHCP_SERVER_IDENTIFIER,
                                           local_addr));
    ex.getResponse()->addOption(opt_srvid);
}

void
Dhcpv4Srv::buildCfgOptionList(Dhcpv4Exchange& ex) {
    CfgOptionList& co_list = ex.getCfgOptionList();

    // Retrieve subnet.
    Subnet4Ptr subnet = ex.getContext()->subnet_;
    if (!subnet) {
        // All methods using the CfgOptionList object return soon when
        // there is no subnet so do the same
        return;
    }

    // Firstly, host specific options.
    const ConstHostPtr& host = ex.getContext()->currentHost();
    if (host && !host->getCfgOption4()->empty()) {
        co_list.push_back(host->getCfgOption4());
    }

    // Secondly, pool specific options.
    Pkt4Ptr resp = ex.getResponse();
    IOAddress addr = IOAddress::IPV4_ZERO_ADDRESS();
    if (resp) {
        addr = resp->getYiaddr();
    }
    if (!addr.isV4Zero()) {
        PoolPtr pool = subnet->getPool(Lease::TYPE_V4, addr, false);
        if (pool && !pool->getCfgOption()->empty()) {
            co_list.push_back(pool->getCfgOption());
        }
    }

    // Thirdly, subnet configured options.
    if (!subnet->getCfgOption()->empty()) {
        co_list.push_back(subnet->getCfgOption());
    }

    // Forthly, shared network specific options.
    SharedNetwork4Ptr network;
    subnet->getSharedNetwork(network);
    if (network && !network->getCfgOption()->empty()) {
        co_list.push_back(network->getCfgOption());
    }

    // Each class in the incoming packet
    const ClientClasses& classes = ex.getQuery()->getClasses();
    for (ClientClasses::const_iterator cclass = classes.cbegin();
         cclass != classes.cend(); ++cclass) {
        // Find the client class definition for this class
        const ClientClassDefPtr& ccdef = CfgMgr::instance().getCurrentCfg()->
            getClientClassDictionary()->findClass(*cclass);
        if (!ccdef) {
            // Not found: the class is built-in or not configured
            if (!isClientClassBuiltIn(*cclass)) {
                LOG_DEBUG(dhcp4_logger, DBG_DHCP4_BASIC, DHCP4_CLASS_UNCONFIGURED)
                    .arg(ex.getQuery()->getLabel())
                    .arg(*cclass);
            }
            // Skip it
            continue;
        }
        if (ccdef->getCfgOption()->empty()) {
            // Skip classes which don't configure options
            continue;
        }
        co_list.push_back(ccdef->getCfgOption());
    }

    // Last global options
    if (!CfgMgr::instance().getCurrentCfg()->getCfgOption()->empty()) {
        co_list.push_back(CfgMgr::instance().getCurrentCfg()->getCfgOption());
    }
}

void
Dhcpv4Srv::appendRequestedOptions(Dhcpv4Exchange& ex) {
    // Get the subnet relevant for the client. We will need it
    // to get the options associated with it.
    Subnet4Ptr subnet = ex.getContext()->subnet_;
    // If we can't find the subnet for the client there is no way
    // to get the options to be sent to a client. We don't log an
    // error because it will be logged by the assignLease method
    // anyway.
    if (!subnet) {
        return;
    }

    // Unlikely short cut
    const CfgOptionList& co_list = ex.getCfgOptionList();
    if (co_list.empty()) {
        return;
    }

    Pkt4Ptr query = ex.getQuery();
    Pkt4Ptr resp = ex.getResponse();
    std::vector<uint8_t> requested_opts;

    // try to get the 'Parameter Request List' option which holds the
    // codes of requested options.
    OptionUint8ArrayPtr option_prl = boost::dynamic_pointer_cast<
        OptionUint8Array>(query->getOption(DHO_DHCP_PARAMETER_REQUEST_LIST));
    // Get the codes of requested options.
    if (option_prl) {
        requested_opts = option_prl->getValues();
    }
    // Iterate on the configured option list to add persistent options
    for (CfgOptionList::const_iterator copts = co_list.begin();
         copts != co_list.end(); ++copts) {
        const OptionContainerPtr& opts = (*copts)->getAll(DHCP4_OPTION_SPACE);
        if (!opts) {
            continue;
        }
        // Get persistent options
        const OptionContainerPersistIndex& idx = opts->get<2>();
        const OptionContainerPersistRange& range = idx.equal_range(true);
        for (OptionContainerPersistIndex::const_iterator desc = range.first;
             desc != range.second; ++desc) {
            // Add the persistent option code to requested options
            if (desc->option_) {
                uint8_t code = static_cast<uint8_t>(desc->option_->getType());
                requested_opts.push_back(code);
            }
        }
    }

    // For each requested option code get the instance of the option
    // to be returned to the client.
    for (std::vector<uint8_t>::const_iterator opt = requested_opts.begin();
         opt != requested_opts.end(); ++opt) {
        // Add nothing when it is already there
        if (!resp->getOption(*opt)) {
            // Iterate on the configured option list
            for (CfgOptionList::const_iterator copts = co_list.begin();
                 copts != co_list.end(); ++copts) {
                OptionDescriptor desc = (*copts)->get(DHCP4_OPTION_SPACE, *opt);
                // Got it: add it and jump to the outer loop
                if (desc.option_) {
                    resp->addOption(desc.option_);
                    break;
                }
            }
        }
    }
}

void
Dhcpv4Srv::appendRequestedVendorOptions(Dhcpv4Exchange& ex) {
    // Get the configured subnet suitable for the incoming packet.
    Subnet4Ptr subnet = ex.getContext()->subnet_;
    // Leave if there is no subnet matching the incoming packet.
    // There is no need to log the error message here because
    // it will be logged in the assignLease() when it fails to
    // pick the suitable subnet. We don't want to duplicate
    // error messages in such case.
    if (!subnet) {
        return;
    }

    // Unlikely short cut
    const CfgOptionList& co_list = ex.getCfgOptionList();
    if (co_list.empty()) {
        return;
    }

    uint32_t vendor_id = 0;

    // Try to get the vendor option from the client packet. This is how it's
    // supposed to be done. Client sends vivso, we look at the vendor-id and
    // then send back the vendor options specific to that client.
    boost::shared_ptr<OptionVendor> vendor_req = boost::dynamic_pointer_cast<
        OptionVendor>(ex.getQuery()->getOption(DHO_VIVSO_SUBOPTIONS));
    if (vendor_req) {
        vendor_id = vendor_req->getVendorId();
    }

    // Something is fishy. Client was supposed to send vivso, but didn't.
    // Let's try an alternative. It's possible that the server already
    // inserted vivso in the response message, (e.g. by using client
    // classification or perhaps a hook inserted it).
    boost::shared_ptr<OptionVendor> vendor_rsp = boost::dynamic_pointer_cast<
        OptionVendor>(ex.getResponse()->getOption(DHO_VIVSO_SUBOPTIONS));
    if (vendor_rsp) {
        vendor_id = vendor_rsp->getVendorId();
    }

    if (!vendor_req && !vendor_rsp) {
        // Ok, we're out of luck today. Neither client nor server packets
        // have vivso.  There is no way to figure out vendor-id here.
        // We give up.
        return;
    }

    std::vector<uint8_t> requested_opts;

    // Let's try to get ORO within that vendor-option
    /// @todo This is very specific to vendor-id=4491 (Cable Labs). Other
    /// vendors may have different policies.
    OptionUint8ArrayPtr oro;
    if (vendor_req) {
        oro = boost::dynamic_pointer_cast<OptionUint8Array>(vendor_req->getOption(DOCSIS3_V4_ORO));
    }
    // Get the list of options that client requested.
    if (oro) {
        requested_opts = oro->getValues();
    }
    // Iterate on the configured option list to add persistent options
    for (CfgOptionList::const_iterator copts = co_list.begin();
         copts != co_list.end(); ++copts) {
        const OptionContainerPtr& opts = (*copts)->getAll(vendor_id);
        if (!opts) {
            continue;
        }

        // Get persistent options
        const OptionContainerPersistIndex& idx = opts->get<2>();
        const OptionContainerPersistRange& range = idx.equal_range(true);
        for (OptionContainerPersistIndex::const_iterator desc = range.first;
             desc != range.second; ++desc) {
            // Add the persistent option code to requested options
            if (desc->option_) {
                uint8_t code = static_cast<uint8_t>(desc->option_->getType());
                requested_opts.push_back(code);
            }
        }
    }

    // If there is nothing to add don't do anything then.
    if (requested_opts.empty()) {
        return;
    }

    if (!vendor_rsp) {
        // It's possible that vivso was inserted already by client class or
        // a hook. If that is so, let's use it.
        vendor_rsp.reset(new OptionVendor(Option::V4, vendor_id));
    }

    // Get the list of options that client requested.
    bool added = false;
    for (std::vector<uint8_t>::const_iterator code = requested_opts.begin();
         code != requested_opts.end(); ++code) {
        if  (!vendor_rsp->getOption(*code)) {
            for (CfgOptionList::const_iterator copts = co_list.begin();
                 copts != co_list.end(); ++copts) {
                OptionDescriptor desc = (*copts)->get(vendor_id, *code);
                if (desc.option_) {
                    vendor_rsp->addOption(desc.option_);
                    added = true;
                    break;
                }
            }
        }

        // If we added some sub-options and the vivso option is not in
        // the response already, then add it.
        if (added && !ex.getResponse()->getOption(DHO_VIVSO_SUBOPTIONS)) {
            ex.getResponse()->addOption(vendor_rsp);
        }
    }
}


void
Dhcpv4Srv::appendBasicOptions(Dhcpv4Exchange& ex) {
    // Identify options that we always want to send to the
    // client (if they are configured).
    static const uint16_t required_options[] = {
        DHO_ROUTERS,
        DHO_DOMAIN_NAME_SERVERS,
        DHO_DOMAIN_NAME,
        DHO_DHCP_SERVER_IDENTIFIER };

    static size_t required_options_size =
        sizeof(required_options) / sizeof(required_options[0]);

    // Get the subnet.
    Subnet4Ptr subnet = ex.getContext()->subnet_;
    if (!subnet) {
        return;
    }

    // Unlikely short cut
    const CfgOptionList& co_list = ex.getCfgOptionList();
    if (co_list.empty()) {
        return;
    }

    Pkt4Ptr resp = ex.getResponse();

    // Try to find all 'required' options in the outgoing
    // message. Those that are not present will be added.
    for (int i = 0; i < required_options_size; ++i) {
        OptionPtr opt = resp->getOption(required_options[i]);
        if (!opt) {
            // Check whether option has been configured.
            for (CfgOptionList::const_iterator copts = co_list.begin();
                 copts != co_list.end(); ++copts) {
                OptionDescriptor desc = (*copts)->get(DHCP4_OPTION_SPACE,
                                                      required_options[i]);
                if (desc.option_) {
                    resp->addOption(desc.option_);
                    break;
                }
            }
        }
    }
}

void
Dhcpv4Srv::processClientName(Dhcpv4Exchange& ex) {
    // It is possible that client has sent both Client FQDN and Hostname
    // option. In such case, server should prefer Client FQDN option and
    // ignore the Hostname option.
    try {
        Pkt4Ptr resp = ex.getResponse();
        Option4ClientFqdnPtr fqdn = boost::dynamic_pointer_cast<Option4ClientFqdn>
            (ex.getQuery()->getOption(DHO_FQDN));
        if (fqdn) {
            LOG_DEBUG(ddns4_logger, DBG_DHCP4_DETAIL, DHCP4_CLIENT_FQDN_PROCESS)
                .arg(ex.getQuery()->getLabel());
            processClientFqdnOption(ex);

        } else {
            LOG_DEBUG(ddns4_logger, DBG_DHCP4_DETAIL,
                      DHCP4_CLIENT_HOSTNAME_PROCESS)
                    .arg(ex.getQuery()->getLabel());
            processHostnameOption(ex);
        }
    } catch (const Exception& e) {
        // In some rare cases it is possible that the client's name processing
        // fails. For example, the Hostname option may be malformed, or there
        // may be an error in the server's logic which would cause multiple
        // attempts to add the same option to the response message. This
        // error message aggregates all these errors so they can be diagnosed
        // from the log. We don't want to throw an exception here because,
        // it will impact the processing of the whole packet. We rather want
        // the processing to continue, even if the client's name is wrong.
        LOG_DEBUG(ddns4_logger, DBG_DHCP4_DETAIL_DATA, DHCP4_CLIENT_NAME_PROC_FAIL)
            .arg(ex.getQuery()->getLabel())
            .arg(e.what());
    }
}

void
Dhcpv4Srv::processClientFqdnOption(Dhcpv4Exchange& ex) {
    // Obtain the FQDN option from the client's message.
    Option4ClientFqdnPtr fqdn = boost::dynamic_pointer_cast<
        Option4ClientFqdn>(ex.getQuery()->getOption(DHO_FQDN));

    LOG_DEBUG(ddns4_logger, DBG_DHCP4_DETAIL_DATA, DHCP4_CLIENT_FQDN_DATA)
        .arg(ex.getQuery()->getLabel())
        .arg(fqdn->toText());

    // Create the DHCPv4 Client FQDN Option to be included in the server's
    // response to a client.
    Option4ClientFqdnPtr fqdn_resp(new Option4ClientFqdn(*fqdn));

    // Set the server S, N, and O flags based on client's flags and
    // current configuration.
    D2ClientMgr& d2_mgr = CfgMgr::instance().getD2ClientMgr();
    d2_mgr.adjustFqdnFlags<Option4ClientFqdn>(*fqdn, *fqdn_resp);

    // Carry over the client's E flag.
    fqdn_resp->setFlag(Option4ClientFqdn::FLAG_E,
                       fqdn->getFlag(Option4ClientFqdn::FLAG_E));

    if (ex.getContext()->currentHost() &&
        !ex.getContext()->currentHost()->getHostname().empty()) {
        D2ClientMgr& d2_mgr = CfgMgr::instance().getD2ClientMgr();
        fqdn_resp->setDomainName(d2_mgr.qualifyName(ex.getContext()->currentHost()->getHostname(),
                                                    true), Option4ClientFqdn::FULL);

    } else {
        // Adjust the domain name based on domain name value and type sent by the
        // client and current configuration.
        d2_mgr.adjustDomainName<Option4ClientFqdn>(*fqdn, *fqdn_resp);
    }

    // Add FQDN option to the response message. Note that, there may be some
    // cases when server may choose not to include the FQDN option in a
    // response to a client. In such cases, the FQDN should be removed from the
    // outgoing message. In theory we could cease to include the FQDN option
    // in this function until it is confirmed that it should be included.
    // However, we include it here for simplicity. Functions used to acquire
    // lease for a client will scan the response message for FQDN and if it
    // is found they will take necessary actions to store the FQDN information
    // in the lease database as well as to generate NameChangeRequests to DNS.
    // If we don't store the option in the response message, we will have to
    // propagate it in the different way to the functions which acquire the
    // lease. This would require modifications to the API of this class.
    LOG_DEBUG(ddns4_logger, DBG_DHCP4_DETAIL_DATA, DHCP4_RESPONSE_FQDN_DATA)
        .arg(ex.getQuery()->getLabel())
        .arg(fqdn_resp->toText());
    ex.getResponse()->addOption(fqdn_resp);
}

void
Dhcpv4Srv::processHostnameOption(Dhcpv4Exchange& ex) {
    // Fetch D2 configuration.
    D2ClientMgr& d2_mgr = CfgMgr::instance().getD2ClientMgr();

    // Obtain the Hostname option from the client's message.
    OptionStringPtr opt_hostname = boost::dynamic_pointer_cast<OptionString>
        (ex.getQuery()->getOption(DHO_HOST_NAME));

    if (opt_hostname) {
        LOG_DEBUG(ddns4_logger, DBG_DHCP4_DETAIL_DATA, DHCP4_CLIENT_HOSTNAME_DATA)
            .arg(ex.getQuery()->getLabel())
            .arg(opt_hostname->getValue());
    }

    AllocEngine::ClientContext4Ptr ctx = ex.getContext();

    // Hostname reservations take precedence over any other configuration,
    // i.e. DDNS configuration.
    if (ctx->currentHost() && !ctx->currentHost()->getHostname().empty()) {
        // In order to send a reserved hostname value we expect that at least
        // one of the following is the case: the client has sent us a hostname
        // option, or the client has sent Parameter Request List option with
        // the hostname option code included.

        // It is going to be less expensive to first check the presence of the
        // hostname option.
        bool should_send_hostname = static_cast<bool>(opt_hostname);
        // Hostname option is not present, so we have to check PRL option.
        if (!should_send_hostname) {
            OptionUint8ArrayPtr
                option_prl = boost::dynamic_pointer_cast<OptionUint8Array>
                (ex.getQuery()->getOption(DHO_DHCP_PARAMETER_REQUEST_LIST));
            if (option_prl) {
                // PRL option exists, so check if the hostname option code is
                // included in it.
                const std::vector<uint8_t>&
                    requested_opts = option_prl->getValues();
                if (std::find(requested_opts.begin(), requested_opts.end(),
                              DHO_HOST_NAME) != requested_opts.end()) {
                    // Client has requested hostname via Parameter Request
                    // List option.
                    should_send_hostname = true;
                }
            }
        }

        // If the hostname or PRL option indicates that the server should
        // send back a hostname option, send this option with a reserved
        // name for this client.
        if (should_send_hostname) {
            std::string hostname =
                d2_mgr.qualifyName(ctx->currentHost()->getHostname(), false);

            // Convert hostname to lower case.
            boost::algorithm::to_lower(hostname);

            LOG_DEBUG(ddns4_logger, DBG_DHCP4_DETAIL_DATA,
                      DHCP4_RESERVED_HOSTNAME_ASSIGNED)
                .arg(ex.getQuery()->getLabel())
                .arg(hostname);
            OptionStringPtr opt_hostname_resp(new OptionString(Option::V4,
                                                               DHO_HOST_NAME,
                                                               hostname));
            ex.getResponse()->addOption(opt_hostname_resp);

            // We're done here.
            return;
        }
    }

    // There is no reservation for this client or the client hasn't requested
    // hostname option. There is still a possibility that we'll have to send
    // hostname option to this client if the client has included hostname option
    // but there is no reservation, or the configuration of the server requires
    // that we send the option regardless.

    D2ClientConfig::ReplaceClientNameMode replace_name_mode =
            d2_mgr.getD2ClientConfig()->getReplaceClientNameMode();

    // If we don't have a hostname then either we'll supply it or do nothing.
    if (!opt_hostname) {
        // If we're configured to supply it then add it to the response.
        // Use the root domain to signal later on that we should replace it.
        if (replace_name_mode == D2ClientConfig::RCM_ALWAYS ||
            replace_name_mode == D2ClientConfig::RCM_WHEN_NOT_PRESENT) {
            LOG_DEBUG(ddns4_logger, DBG_DHCP4_DETAIL_DATA,
                      DHCP4_GENERATE_FQDN)
                .arg(ex.getQuery()->getLabel());
            OptionStringPtr opt_hostname_resp(new OptionString(Option::V4,
                                                               DHO_HOST_NAME,
                                                               "."));
            ex.getResponse()->addOption(opt_hostname_resp);
        }

        return;
    }

    // Client sent us a hostname option so figure out what to do with it.
    LOG_DEBUG(ddns4_logger, DBG_DHCP4_DETAIL_DATA, DHCP4_CLIENT_HOSTNAME_DATA)
        .arg(ex.getQuery()->getLabel())
        .arg(opt_hostname->getValue());

    std::string hostname = isc::util::str::trim(opt_hostname->getValue());
    unsigned int label_count = OptionDataTypeUtil::getLabelCount(hostname);
    // The hostname option sent by the client should be at least 1 octet long.
    // If it isn't we ignore this option. (Per RFC 2131, section 3.14)
    /// @todo It would be more liberal to accept this and let it fall into
    /// the case  of replace or less than two below.
    if (label_count == 0) {
        LOG_DEBUG(ddns4_logger, DBG_DHCP4_DETAIL_DATA, DHCP4_EMPTY_HOSTNAME)
            .arg(ex.getQuery()->getLabel());
        return;
    }

    // Stores the value we eventually use, so we can send it back.
    OptionStringPtr opt_hostname_resp;

    // The hostname option may be unqualified or fully qualified. The lab_count
    // holds the number of labels for the name. The number of 1 means that
    // there is only root label "." (even for unqualified names, as the
    // getLabelCount function treats each name as a fully qualified one).
    // By checking the number of labels present in the hostname we may infer
    // whether client has sent the fully qualified or unqualified hostname.

    if ((replace_name_mode == D2ClientConfig::RCM_ALWAYS ||
         replace_name_mode == D2ClientConfig::RCM_WHEN_PRESENT)
        || label_count < 2) {
        // Set to root domain to signal later on that we should replace it.
        // DHO_HOST_NAME is a string option which cannot be empty.
        /// @todo We may want to reconsider whether it is appropriate for the
        /// client to send a root domain name as a Hostname. There are
        /// also extensions to the auto generation of the client's name,
        /// e.g. conversion to the puny code which may be considered at some
        /// point.
        /// For now, we just remain liberal and expect that the DNS will handle
        /// conversion if needed and possible.
        opt_hostname_resp.reset(new OptionString(Option::V4, DHO_HOST_NAME, "."));
    } else {
        // Sanitize the name the client sent us, if we're configured to do so.
        isc::util::str::StringSanitizerPtr sanitizer = d2_mgr.getD2ClientConfig()
                                                       ->getHostnameSanitizer();
        if (sanitizer) {
            hostname = sanitizer->scrub(hostname);
        }

        // Convert hostname to lower case.
        boost::algorithm::to_lower(hostname);

        if (label_count == 2) {
            // If there are two labels, it means that the client has specified
            // the unqualified name. We have to concatenate the unqualified name
            // with the domain name. The false value passed as a second argument
            // indicates that the trailing dot should not be appended to the
            // hostname. We don't want to append the trailing dot because
            // we don't know whether the hostname is partial or not and some
            // clients do not handle the hostnames with the trailing dot.
            opt_hostname_resp.reset(new OptionString(Option::V4, DHO_HOST_NAME,
                                                     d2_mgr.qualifyName(hostname, false)));
        } else {
            opt_hostname_resp.reset(new OptionString(Option::V4, DHO_HOST_NAME, hostname));
        }
    }

    LOG_DEBUG(ddns4_logger, DBG_DHCP4_DETAIL_DATA, DHCP4_RESPONSE_HOSTNAME_DATA)
        .arg(ex.getQuery()->getLabel())
        .arg(opt_hostname_resp->getValue());
    ex.getResponse()->addOption(opt_hostname_resp);
}

void
Dhcpv4Srv::createNameChangeRequests(const Lease4Ptr& lease,
                                    const Lease4Ptr& old_lease) {
    if (!lease) {
        isc_throw(isc::Unexpected,
                  "NULL lease specified when creating NameChangeRequest");

    } else if (!old_lease || !lease->hasIdenticalFqdn(*old_lease)) {
        if (old_lease) {
            // Queue's up a remove of the old lease's DNS (if needed)
            queueNCR(CHG_REMOVE, old_lease);
        }

        // We may need to generate the NameChangeRequest for the new lease. It
        // will be generated only if hostname is set and if forward or reverse
        // update has been requested.
        queueNCR(CHG_ADD, lease);
    }
}

void
Dhcpv4Srv::assignLease(Dhcpv4Exchange& ex) {
    // Get the pointers to the query and the response messages.
    Pkt4Ptr query = ex.getQuery();
    Pkt4Ptr resp = ex.getResponse();

    // Get the context.
    AllocEngine::ClientContext4Ptr ctx = ex.getContext();

    // Subnet should have been already selected when the context was created.
    Subnet4Ptr subnet = ctx->subnet_;
    if (!subnet) {
        // This particular client is out of luck today. We do not have
        // information about the subnet he is connected to. This likely means
        // misconfiguration of the server (or some relays).

        // Perhaps this should be logged on some higher level?
        LOG_ERROR(bad_packet4_logger, DHCP4_PACKET_NAK_0001)
            .arg(query->getLabel())
            .arg(query->getRemoteAddr().toText())
            .arg(query->getName());
        resp->setType(DHCPNAK);
        resp->setYiaddr(IOAddress::IPV4_ZERO_ADDRESS());
        return;
    }


    // Get the server identifier. It will be used to determine the state
    // of the client.
    OptionCustomPtr opt_serverid = boost::dynamic_pointer_cast<
        OptionCustom>(query->getOption(DHO_DHCP_SERVER_IDENTIFIER));

    // Check if the client has sent a requested IP address option or
    // ciaddr.
    OptionCustomPtr opt_requested_address = boost::dynamic_pointer_cast<
        OptionCustom>(query->getOption(DHO_DHCP_REQUESTED_ADDRESS));
    IOAddress hint(IOAddress::IPV4_ZERO_ADDRESS());
    if (opt_requested_address) {
        hint = opt_requested_address->readAddress();

    } else if (!query->getCiaddr().isV4Zero()) {
        hint = query->getCiaddr();

    }

    HWAddrPtr hwaddr = query->getHWAddr();

    // "Fake" allocation is processing of DISCOVER message. We pretend to do an
    // allocation, but we do not put the lease in the database. That is ok,
    // because we do not guarantee that the user will get that exact lease. If
    // the user selects this server to do actual allocation (i.e. sends REQUEST)
    // it should include this hint. That will help us during the actual lease
    // allocation.
    bool fake_allocation = (query->getType() == DHCPDISCOVER);

    // Get client-id. It is not mandatory in DHCPv4.
    ClientIdPtr client_id = ex.getContext()->clientid_;

    // If there is no server id and there is a Requested IP Address option
    // the client is in the INIT-REBOOT state in which the server has to
    // determine whether the client's notion of the address is correct
    // and whether the client is known, i.e., has a lease.
    if (!fake_allocation && !opt_serverid && opt_requested_address) {

        LOG_INFO(lease4_logger, DHCP4_INIT_REBOOT)
            .arg(query->getLabel())
            .arg(hint.toText());

        Lease4Ptr lease;
        Subnet4Ptr original_subnet = subnet;

        // We used to issue a separate query (two actually: one for client-id
        // and another one for hw-addr for) each subnet in the shared network.
        // That was horribly inefficient if the client didn't have any lease
        // (or there were many subnets and the client happended to be in one
        // of the last subnets).
        //
        // We now issue at most two queries: get all the leases for specific
        // client-id and then get all leases for specific hw-address.
        if (client_id) {

            // Get all the leases for this client-id
            Lease4Collection leases_client_id = LeaseMgrFactory::instance().getLease4(*client_id);
            if (!leases_client_id.empty()) {
                Subnet4Ptr s = original_subnet;

                // Among those returned try to find a lease that belongs to
                // current shared network.
                while (s) {
                    for (auto l = leases_client_id.begin(); l != leases_client_id.end(); ++l) {
                        if ((*l)->subnet_id_ == s->getID()) {
                            lease = *l;
                            break;
                        }
                    }

                    if (lease) {
                        break;

                    } else {
                        s = s->getNextSubnet(original_subnet, query->getClasses());
                    }
                }
            }
        }

        // If we haven't found a lease yet, try again by hardware-address.
        // The logic is the same.
        if (!lease && hwaddr) {

            // Get all leases for this particular hw-address.
            Lease4Collection leases_hwaddr = LeaseMgrFactory::instance().getLease4(*hwaddr);
            if (!leases_hwaddr.empty()) {
                Subnet4Ptr s = original_subnet;

                // Pick one that belongs to a subnet in this shared network.
                while (s) {
                    for (auto l = leases_hwaddr.begin(); l != leases_hwaddr.end(); ++l) {
                        if ((*l)->subnet_id_ == s->getID()) {
                            lease = *l;
                            break;
                        }
                    }

                    if (lease) {
                        break;

                    } else {
                        s = s->getNextSubnet(original_subnet, query->getClasses());
                    }
                }
            }
        }

        // Check the first error case: unknown client. We check this before
        // validating the address sent because we don't want to respond if
        // we don't know this client, except if we're authoritative.
        bool authoritative = original_subnet->getAuthoritative();
        bool known_client = lease && lease->belongsToClient(hwaddr, client_id);
        if (!authoritative && !known_client) {
            LOG_DEBUG(bad_packet4_logger, DBG_DHCP4_DETAIL,
                      DHCP4_NO_LEASE_INIT_REBOOT)
                .arg(query->getLabel())
                .arg(hint.toText());

            ex.deleteResponse();
            return;
        }

        // If we know this client, check if his notion of the IP address is
        // correct, if we don't know him, check if we are authoritative.
        if ((known_client && (lease->addr_ != hint)) ||
            (!known_client && authoritative)) {
            LOG_DEBUG(bad_packet4_logger, DBG_DHCP4_DETAIL,
                      DHCP4_PACKET_NAK_0002)
                .arg(query->getLabel())
                .arg(hint.toText());

            resp->setType(DHCPNAK);
            resp->setYiaddr(IOAddress::IPV4_ZERO_ADDRESS());
            return;
        }
    }


    CalloutHandlePtr callout_handle = getCalloutHandle(query);

    std::string hostname;
    bool fqdn_fwd = false;
    bool fqdn_rev = false;
    OptionStringPtr opt_hostname;
    Option4ClientFqdnPtr fqdn = boost::dynamic_pointer_cast<
        Option4ClientFqdn>(resp->getOption(DHO_FQDN));
    if (fqdn) {
        hostname = fqdn->getDomainName();
        CfgMgr::instance().getD2ClientMgr().getUpdateDirections(*fqdn,
                                                                fqdn_fwd,
                                                                fqdn_rev);
    } else {
        opt_hostname = boost::dynamic_pointer_cast<OptionString>
            (resp->getOption(DHO_HOST_NAME));

        if (opt_hostname) {
            hostname = opt_hostname->getValue();
            // DHO_HOST_NAME is string option which cannot be blank,
            // we use "." to know we should replace it with a fully
            // generated name. The local string variable needs to be
            // blank in logic below.
            if (hostname == ".") {
                hostname = "";
            }
            /// @todo It could be configurable what sort of updates the
            /// server is doing when Hostname option was sent.
            fqdn_fwd = true;
            fqdn_rev = true;
        }
    }

    // We need to set these values in the context as they haven't been set yet.
    ctx->requested_address_ = hint;
    ctx->fwd_dns_update_ = fqdn_fwd;
    ctx->rev_dns_update_ = fqdn_rev;
    ctx->hostname_ = hostname;
    ctx->fake_allocation_ = fake_allocation;
    ctx->callout_handle_ = callout_handle;

    Lease4Ptr lease = alloc_engine_->allocateLease4(*ctx);

    // Subnet may be modified by the allocation engine, if the initial subnet
    // belongs to a shared network.
    if (subnet->getID() != ctx->subnet_->getID()) {
        SharedNetwork4Ptr network;
        subnet->getSharedNetwork(network);
        if (network) {
            LOG_DEBUG(packet4_logger, DBG_DHCP4_BASIC_DATA, DHCP4_SUBNET_DYNAMICALLY_CHANGED)
                .arg(query->getLabel())
                .arg(subnet->toText())
                .arg(ctx->subnet_->toText())
                .arg(network->getName());
        }
        subnet = ctx->subnet_;
    }

    if (lease) {
        // We have a lease! Let's set it in the packet and send it back to
        // the client.
        LOG_INFO(lease4_logger, fake_allocation ? DHCP4_LEASE_ADVERT : DHCP4_LEASE_ALLOC)
            .arg(query->getLabel())
            .arg(lease->addr_.toText());

        // We're logging this here, because this is the place where we know
        // which subnet has been actually used for allocation. If the
        // client identifier matching is disabled, we want to make sure that
        // the user is notified.
        if (!ctx->subnet_->getMatchClientId()) {
            LOG_DEBUG(dhcp4_logger, DBG_DHCP4_DETAIL, DHCP4_CLIENTID_IGNORED_FOR_LEASES)
                .arg(ctx->query_->getLabel())
                .arg(ctx->subnet_->getID());
        }

        resp->setYiaddr(lease->addr_);

        /// @todo The server should check what ciaddr the client has supplied
        /// in ciaddr. Currently the ciaddr is ignored except for the subnet
        /// selection. If the client supplied an invalid address, the server
        /// will also return an invalid address here.
        if (!fake_allocation) {
            // If this is a renewing client it will set a ciaddr which the
            // server may include in the response. If this is a new allocation
            // the client will set ciaddr to 0 and this will also be propagated
            // to the server's resp.
            resp->setCiaddr(query->getCiaddr());
        }

        // We may need to update FQDN or hostname if the server is to generate
        // new name from the allocated IP address or if the allocation engine
        // has switched to a different subnet (from the same shared network)
        // where the client has hostname reservations.
        if (fqdn || opt_hostname) {
            bool should_update = false;

            // If there is a reservation in the current subnet for a hostname,
            // we need to use this reserved name.
            if (ctx->currentHost() && !ctx->currentHost()->getHostname().empty()) {

                lease->hostname_ = CfgMgr::instance().getD2ClientMgr()
                    .qualifyName(ctx->currentHost()->getHostname(),
                                 static_cast<bool>(fqdn));
                should_update = true;

            // If there has been Client FQDN or Hostname option sent, but the
            // hostname is empty, it means that server is responsible for
            // generating the entire hostname for the client. The example of the
            // client's name, generated from the IP address is: host-192-0-2-3.
            } else if (lease->hostname_.empty()) {

                // Note that if we have received the hostname option, rather than
                // Client FQDN the trailing dot is not appended to the generated
                // hostname because some clients don't handle the trailing dot in
                // the hostname. Whether the trailing dot is appended or not is
                // controlled by the second argument to the generateFqdn().
                lease->hostname_ = CfgMgr::instance().getD2ClientMgr()
                    .generateFqdn(lease->addr_, static_cast<bool>(fqdn));

                LOG_DEBUG(ddns4_logger, DBG_DHCP4_DETAIL, DHCP4_RESPONSE_HOSTNAME_GENERATE)
                    .arg(query->getLabel())
                    .arg(lease->hostname_);

                should_update = true;
            }

            if (should_update) {

                // The operations below are rather safe, but we want to catch
                // any potential exceptions (e.g. invalid lease database backend
                // implementation) and log an error.
                try {
                    if (!fake_allocation) {
                        // The lease update should be safe, because the lease should
                        // be already in the database. In most cases the exception
                        // would be thrown if the lease was missing.
                        LeaseMgrFactory::instance().updateLease4(lease);
                    }

                    // The name update in the option should be also safe,
                    // because the generated name is well formed.
                    if (fqdn) {
                        fqdn->setDomainName(lease->hostname_,
                                            Option4ClientFqdn::FULL);
                    } else if (opt_hostname) {
                        opt_hostname->setValue(lease->hostname_);
                    }

                } catch (const Exception& ex) {
                    LOG_ERROR(ddns4_logger, DHCP4_POST_ALLOCATION_NAME_UPDATE_FAIL)
                        .arg(query->getLabel())
                        .arg(lease->hostname_)
                        .arg(ex.what());
                }
            }
        }

        // IP Address Lease time (type 51)
        OptionPtr opt(new OptionUint32(Option::V4, DHO_DHCP_LEASE_TIME,
                                       lease->valid_lft_));
        resp->addOption(opt);

        // Subnet mask (type 1)
        resp->addOption(getNetmaskOption(subnet));

        // Set T1 and T2 per configuration.
        setTeeTimes(lease, subnet, resp);

        // Create NameChangeRequests if DDNS is enabled and this is a
        // real allocation.
        if (!fake_allocation && CfgMgr::instance().ddnsEnabled()) {
            try {
                LOG_DEBUG(ddns4_logger, DBG_DHCP4_DETAIL, DHCP4_NCR_CREATE)
                    .arg(query->getLabel());
                createNameChangeRequests(lease, ctx->old_lease_);

            } catch (const Exception& ex) {
                LOG_ERROR(ddns4_logger, DHCP4_NCR_CREATION_FAILED)
                    .arg(query->getLabel())
                    .arg(ex.what());
            }
        }

    } else {
        // Allocation engine did not allocate a lease. The engine logged
        // cause of that failure.
        LOG_DEBUG(bad_packet4_logger, DBG_DHCP4_DETAIL, fake_allocation ?
                  DHCP4_PACKET_NAK_0003 : DHCP4_PACKET_NAK_0004)
            .arg(query->getLabel())
            .arg(query->getCiaddr().toText())
            .arg(opt_requested_address ?
                 opt_requested_address->readAddress().toText() : "(no address)");

        resp->setType(DHCPNAK);
        resp->setYiaddr(IOAddress::IPV4_ZERO_ADDRESS());

        resp->delOption(DHO_FQDN);
        resp->delOption(DHO_HOST_NAME);
    }
}

void
Dhcpv4Srv::setTeeTimes(const Lease4Ptr& lease, const Subnet4Ptr& subnet, Pkt4Ptr resp) {

    uint32_t t2_time = 0;
    // If T2 is explicitly configured we'll use try value.
    if (!subnet->getT2().unspecified()) {
        t2_time = subnet->getT2();
    } else if (subnet->getCalculateTeeTimes()) {
        // Calculating tee times is enabled, so calculated it.
        t2_time = static_cast<uint32_t>(subnet->getT2Percent() * (lease->valid_lft_));
    }

    // Send the T2 candidate value only if it's sane: to be sane it must be less than
    // the valid life time.
    uint32_t timer_ceiling = lease->valid_lft_;
    if (t2_time > 0 && t2_time < timer_ceiling) {
        OptionUint32Ptr t2(new OptionUint32(Option::V4, DHO_DHCP_REBINDING_TIME, t2_time));
        resp->addOption(t2);
        // When we send T2, timer ceiling for T1 becomes T2.
        timer_ceiling = t2_time;
    }

    uint32_t t1_time = 0;
    // If T1 is explicitly configured we'll use try value.
    if (!subnet->getT1().unspecified()) {
        t1_time = subnet->getT1();
    } else if (subnet->getCalculateTeeTimes()) {
        // Calculating tee times is enabled, so calculate it.
        t1_time = static_cast<uint32_t>(subnet->getT1Percent() * (lease->valid_lft_));
    }

    // Send T1 if it's sane: If we sent T2, T1 must be less than that.  If not it must be
    // less than the valid life time.
    if (t1_time > 0 && t1_time < timer_ceiling) {
        OptionUint32Ptr t1(new OptionUint32(Option::V4, DHO_DHCP_RENEWAL_TIME, t1_time));
        resp->addOption(t1);
    }
}


uint16_t
Dhcpv4Srv::checkRelayPort(const Dhcpv4Exchange& ex) {

    // Look for a relay-port RAI sub-option in the query.
    const Pkt4Ptr& query = ex.getQuery();
    const OptionPtr& rai = query->getOption(DHO_DHCP_AGENT_OPTIONS);
    if (rai && rai->getOption(RAI_OPTION_RELAY_PORT)) {
        // Got the sub-option so use the remote port set by the relay.
        return (query->getRemotePort());
    }
    return (0);
}

void
Dhcpv4Srv::adjustIfaceData(Dhcpv4Exchange& ex) {
    adjustRemoteAddr(ex);

    // Initialize the pointers to the client's message and the server's
    // response.
    Pkt4Ptr query = ex.getQuery();
    Pkt4Ptr response = ex.getResponse();

    // The DHCPINFORM is generally unicast to the client. The only situation
    // when the server is unable to unicast to the client is when the client
    // doesn't include ciaddr and the message is relayed. In this case the
    // server has to reply via relay agent. For other messages we send back
    // through relay if message is relayed, and unicast to the client if the
    // message is not relayed.
    // If client port was set from the command line enforce all responses
    // to it. Of course it is only for testing purposes.
    // Note that the call to this function may throw if invalid combination
    // of hops and giaddr is found (hops = 0 if giaddr = 0 and hops != 0 if
    // giaddr != 0). The exception will propagate down and eventually cause the
    // packet to be discarded.
    if (client_port_) {
        response->setRemotePort(client_port_);
    } else if (((query->getType() == DHCPINFORM) &&
         ((!query->getCiaddr().isV4Zero()) ||
          (!query->isRelayed() && !query->getRemoteAddr().isV4Zero()))) ||
        ((query->getType() != DHCPINFORM) && !query->isRelayed())) {
        response->setRemotePort(DHCP4_CLIENT_PORT);

    } else {
        // RFC 8357 section 5.1
        uint16_t relay_port = checkRelayPort(ex);
        response->setRemotePort(relay_port ? relay_port : DHCP4_SERVER_PORT);
    }

    CfgIfacePtr cfg_iface = CfgMgr::instance().getCurrentCfg()->getCfgIface();
    if (query->isRelayed() &&
        (cfg_iface->getSocketType() == CfgIface::SOCKET_UDP) &&
        (cfg_iface->getOutboundIface() == CfgIface::USE_ROUTING)) {

        // Mark the response to follow routing
        response->setLocalAddr(IOAddress::IPV4_ZERO_ADDRESS());
        response->resetIndex();
        // But keep the interface name
        response->setIface(query->getIface());

    } else {

        IOAddress local_addr = query->getLocalAddr();

        // In many cases the query is sent to a broadcast address. This address
        // appears as a local address in the query message. We can't simply copy
        // this address to a response message and use it as a source address.
        // Instead we will need to use the address assigned to the interface
        // on which the query has been received. In other cases, we will just
        // use this address as a source address for the response.
        // Do the same for DHCPv4-over-DHCPv6 exchanges.
        if (local_addr.isV4Bcast() || query->isDhcp4o6()) {
            SocketInfo sock_info = IfaceMgr::instance().getSocket(*query);
            local_addr = sock_info.addr_;
        }

        // We assume that there is an appropriate socket bound to this address
        // and that the address is correct. This is safe assumption because
        // the local address of the query is set when the query is received.
        // The query sent to an incorrect address wouldn't have been received.
        // However, if socket is closed for this address between the reception
        // of the query and sending a response, the IfaceMgr should detect it
        // and return an error.
        response->setLocalAddr(local_addr);
        // In many cases the query is sent to a broadcast address. This address
        // appears as a local address in the query message. Therefore we can't
        // simply copy local address from the query and use it as a source
        // address for the response. Instead, we have to check what address our
        // socket is bound to and use it as a source address. This operation
        // may throw if for some reason the socket is closed.
        /// @todo Consider an optimization that we use local address from
        /// the query if this address is not broadcast.
        response->setIndex(query->getIndex());
        response->setIface(query->getIface());
    }

    response->setLocalPort(DHCP4_SERVER_PORT);
}

void
Dhcpv4Srv::adjustRemoteAddr(Dhcpv4Exchange& ex) {
    // Initialize the pointers to the client's message and the server's
    // response.
    Pkt4Ptr query = ex.getQuery();
    Pkt4Ptr response = ex.getResponse();

    // DHCPv4-over-DHCPv6 is simple
    if (query->isDhcp4o6()) {
        response->setRemoteAddr(query->getRemoteAddr());
        return;
    }

    // The DHCPINFORM is slightly different than other messages in a sense
    // that the server should always unicast the response to the ciaddr.
    // It appears however that some clients don't set the ciaddr. We still
    // want to provision these clients and we do what we can't to send the
    // packet to the address where client can receive it.
    if (query->getType() == DHCPINFORM) {
        // If client adheres to RFC2131 it will set the ciaddr and in this
        // case we always unicast our response to this address.
        if (!query->getCiaddr().isV4Zero()) {
            response->setRemoteAddr(query->getCiaddr());

        // If we received DHCPINFORM via relay and the ciaddr is not set we
        // will try to send the response via relay. The caveat is that the
        // relay will not have any idea where to forward the packet because
        // the yiaddr is likely not set. So, the broadcast flag is set so
        // as the response may be broadcast.
        } else if (query->isRelayed()) {
            response->setRemoteAddr(query->getGiaddr());
            response->setFlags(response->getFlags() | BOOTP_BROADCAST);

        // If there is no ciaddr and no giaddr the only thing we can do is
        // to use the source address of the packet.
        } else {
            response->setRemoteAddr(query->getRemoteAddr());
        }
        // Remote address is now set so return.
        return;
    }

    // If received relayed message, server responds to the relay address.
    if (query->isRelayed()) {
        // The client should set the ciaddr when sending the DHCPINFORM
        // but in case he didn't, the relay may not be able to determine the
        // address of the client, because yiaddr is not set when responding
        // to Confirm and the only address available was the source address
        // of the client. The source address is however not used here because
        // the message is relayed. Therefore, we set the BROADCAST flag so
        // as the relay can broadcast the packet.
        if ((query->getType() == DHCPINFORM) &&
            query->getCiaddr().isV4Zero()) {
            response->setFlags(BOOTP_BROADCAST);
        }
        response->setRemoteAddr(query->getGiaddr());

    // If giaddr is 0 but client set ciaddr, server should unicast the
    // response to ciaddr.
    } else if (!query->getCiaddr().isV4Zero()) {
        response->setRemoteAddr(query->getCiaddr());

    // We can't unicast the response to the client when sending NAK,
    // because we haven't allocated address for him. Therefore,
    // NAK is broadcast.
    } else if (response->getType() == DHCPNAK) {
        response->setRemoteAddr(IOAddress::IPV4_BCAST_ADDRESS());

    // If yiaddr is set it means that we have created a lease for a client.
    } else if (!response->getYiaddr().isV4Zero()) {
        // If the broadcast bit is set in the flags field, we have to
        // send the response to broadcast address. Client may have requested it
        // because it doesn't support reception of messages on the interface
        // which doesn't have an address assigned. The other case when response
        // must be broadcasted is when our server does not support responding
        // directly to a client without address assigned.
        const bool bcast_flag = ((query->getFlags() & Pkt4::FLAG_BROADCAST_MASK) != 0);
        if (!IfaceMgr::instance().isDirectResponseSupported() || bcast_flag) {
            response->setRemoteAddr(IOAddress::IPV4_BCAST_ADDRESS());

        // Client cleared the broadcast bit and we support direct responses
        // so we should unicast the response to a newly allocated address -
        // yiaddr.
        } else {
            response->setRemoteAddr(response ->getYiaddr());

        }

    // In most cases, we should have the remote address found already. If we
    // found ourselves at this point, the rational thing to do is to respond
    // to the address we got the query from.
    } else {
        response->setRemoteAddr(query->getRemoteAddr());

    }
}

void
Dhcpv4Srv::setFixedFields(Dhcpv4Exchange& ex) {
    Pkt4Ptr query = ex.getQuery();
    Pkt4Ptr response = ex.getResponse();

    // Step 1: Start with fixed fields defined on subnet level.
    Subnet4Ptr subnet = ex.getContext()->subnet_;
    if (subnet) {
        IOAddress subnet_next_server = subnet->getSiaddr();
        if (!subnet_next_server.isV4Zero()) {
            response->setSiaddr(subnet_next_server);
        }

        const string& sname = subnet->getSname();
        if (!sname.empty()) {
            // Converting string to (const uint8_t*, size_t len) format is
            // tricky. reinterpret_cast is not the most elegant solution,
            // but it does avoid us making unnecessary copy. We will convert
            // sname and file fields in Pkt4 to string one day and life
            // will be easier.
            response->setSname(reinterpret_cast<const uint8_t*>(sname.c_str()),
                               sname.size());
        }

        const string& filename = subnet->getFilename();
        if (!filename.empty()) {
            // Converting string to (const uint8_t*, size_t len) format is
            // tricky. reinterpret_cast is not the most elegant solution,
            // but it does avoid us making unnecessary copy. We will convert
            // sname and file fields in Pkt4 to string one day and life
            // will be easier.
            response->setFile(reinterpret_cast<const uint8_t*>(filename.c_str()),
                              filename.size());
        }
    }

    // Step 2: Try to set the values based on classes.
    // Any values defined in classes will override those from subnet level.
    const ClientClasses classes = query->getClasses();
    if (!classes.empty()) {

        // Let's get class definitions
        const ClientClassDictionaryPtr& dict =
            CfgMgr::instance().getCurrentCfg()->getClientClassDictionary();

        // Now we need to iterate over the classes assigned to the
        // query packet and find corresponding class definitions for it.
        for (ClientClasses::const_iterator name = classes.cbegin();
             name != classes.cend(); ++name) {

            ClientClassDefPtr cl = dict->findClass(*name);
            if (!cl) {
                // Let's skip classes that don't have definitions. Currently
                // these are automatic classes VENDOR_CLASS_something, but there
                // may be other classes assigned under other circumstances, e.g.
                // by hooks.
                continue;
            }

            IOAddress next_server = cl->getNextServer();
            if (!next_server.isV4Zero()) {
                response->setSiaddr(next_server);
            }

            const string& sname = cl->getSname();
            if (!sname.empty()) {
                // Converting string to (const uint8_t*, size_t len) format is
                // tricky. reinterpret_cast is not the most elegant solution,
                // but it does avoid us making unnecessary copy. We will convert
                // sname and file fields in Pkt4 to string one day and life
                // will be easier.
                response->setSname(reinterpret_cast<const uint8_t*>(sname.c_str()),
                                   sname.size());
            }

            const string& filename = cl->getFilename();
            if (!filename.empty()) {
                // Converting string to (const uint8_t*, size_t len) format is
                // tricky. reinterpret_cast is not the most elegant solution,
                // but it does avoid us making unnecessary copy. We will convert
                // sname and file fields in Pkt4 to string one day and life
                // will be easier.
                response->setFile(reinterpret_cast<const uint8_t*>(filename.c_str()),
                                  filename.size());
            }
        }
    }

    // Step 3: try to set values using HR. Any values coming from there will override
    // the subnet or class values.
    ex.setReservedMessageFields();
}

OptionPtr
Dhcpv4Srv::getNetmaskOption(const Subnet4Ptr& subnet) {
    uint32_t netmask = getNetmask4(subnet->get().second).toUint32();

    OptionPtr opt(new OptionInt<uint32_t>(Option::V4,
                  DHO_SUBNET_MASK, netmask));

    return (opt);
}

Pkt4Ptr
Dhcpv4Srv::processDiscover(Pkt4Ptr& discover) {
    sanityCheck(discover, FORBIDDEN);

    bool drop = false;
    Dhcpv4Exchange ex(alloc_engine_, discover, selectSubnet(discover, drop));

    // Stop here if selectSubnet decided to drop the packet
    if (drop) {
        return (Pkt4Ptr());
    }

    // If DHCPDISCOVER message contains the FQDN or Hostname option, server
    // may respond to the client with the appropriate FQDN or Hostname
    // option to indicate that whether it will take responsibility for
    // updating DNS when the client sends DHCPREQUEST message.
    processClientName(ex);

    assignLease(ex);

    if (!ex.getResponse()) {
        // The offer is empty so return it *now*!
        return (Pkt4Ptr());
    }

    // Adding any other options makes sense only when we got the lease.
    if (!ex.getResponse()->getYiaddr().isV4Zero()) {
        // Assign reserved classes.
        ex.setReservedClientClasses();
        // Required classification
        requiredClassify(ex);

        buildCfgOptionList(ex);
        appendRequestedOptions(ex);
        appendRequestedVendorOptions(ex);
        // There are a few basic options that we always want to
        // include in the response. If client did not request
        // them we append them for him.
        appendBasicOptions(ex);

        // Set fixed fields (siaddr, sname, filename) if defined in
        // the reservation, class or subnet specific configuration.
        setFixedFields(ex);

    } else {
        // If the server can't offer an address, it drops the packet.
        return (Pkt4Ptr());

    }

    // Set the src/dest IP address, port and interface for the outgoing
    // packet.
    adjustIfaceData(ex);

    appendServerID(ex);

    return (ex.getResponse());
}

Pkt4Ptr
Dhcpv4Srv::processRequest(Pkt4Ptr& request, AllocEngine::ClientContext4Ptr& context) {
    /// @todo Uncomment this (see ticket #3116)
    /// sanityCheck(request, MANDATORY);

    bool drop = false;
    Dhcpv4Exchange ex(alloc_engine_, request, selectSubnet(request, drop));

    // Stop here if selectSubnet decided to drop the packet
    if (drop) {
        return (Pkt4Ptr());
    }

    // If DHCPREQUEST message contains the FQDN or Hostname option, server
    // should respond to the client with the appropriate FQDN or Hostname
    // option to indicate if it takes responsibility for the DNS updates.
    // This is performed by the function below.
    processClientName(ex);

    // Note that we treat REQUEST message uniformly, regardless if this is a
    // first request (requesting for new address), renewing existing address
    // or even rebinding.
    assignLease(ex);

    if (!ex.getResponse()) {
        // The ack is empty so return it *now*!
        return (Pkt4Ptr());
    }

    // Adding any other options makes sense only when we got the lease.
    if (!ex.getResponse()->getYiaddr().isV4Zero()) {
        // Assign reserved classes.
        ex.setReservedClientClasses();
        // Required classification
        requiredClassify(ex);

        buildCfgOptionList(ex);
        appendRequestedOptions(ex);
        appendRequestedVendorOptions(ex);
        // There are a few basic options that we always want to
        // include in the response. If client did not request
        // them we append them for him.
        appendBasicOptions(ex);

        // Set fixed fields (siaddr, sname, filename) if defined in
        // the reservation, class or subnet specific configuration.
        setFixedFields(ex);
    }

    // Set the src/dest IP address, port and interface for the outgoing
    // packet.
    adjustIfaceData(ex);

    appendServerID(ex);

    // Return the pointer to the context, which will be required by the
    // leases4_comitted callouts.
    context = ex.getContext();

    return (ex.getResponse());
}

void
Dhcpv4Srv::processRelease(Pkt4Ptr& release, AllocEngine::ClientContext4Ptr& context) {
    /// @todo Uncomment this (see ticket #3116)
    /// sanityCheck(release, MANDATORY);

    // Try to find client-id. Note that for the DHCPRELEASE we don't check if the
    // match-client-id configuration parameter is disabled because this parameter
    // is configured for subnets and we don't select subnet for the DHCPRELEASE.
    // Bogus clients usually generate new client identifiers when they first
    // connect to the network, so whatever client identifier has been used to
    // acquire the lease, the client identifier carried in the DHCPRELEASE is
    // likely to be the same and the lease will be correctly identified in the
    // lease database. If supplied client identifier differs from the one used
    // to acquire the lease then the lease will remain in the database and
    // simply expire.
    ClientIdPtr client_id;
    OptionPtr opt = release->getOption(DHO_DHCP_CLIENT_IDENTIFIER);
    if (opt) {
        client_id = ClientIdPtr(new ClientId(opt->getData()));
    }

    try {
        // Do we have a lease for that particular address?
        Lease4Ptr lease = LeaseMgrFactory::instance().getLease4(release->getCiaddr());

        if (!lease) {
            // No such lease - bogus release
            LOG_DEBUG(lease4_logger, DBG_DHCP4_DETAIL, DHCP4_RELEASE_FAIL_NO_LEASE)
                .arg(release->getLabel())
                .arg(release->getCiaddr().toText());
            return;
        }

        if (!lease->belongsToClient(release->getHWAddr(), client_id)) {
            LOG_DEBUG(lease4_logger, DBG_DHCP4_DETAIL, DHCP4_RELEASE_FAIL_WRONG_CLIENT)
                .arg(release->getLabel())
                .arg(release->getCiaddr().toText());
            return;
        }

        bool skip = false;

        // Execute all callouts registered for lease4_release
        if (HooksManager::calloutsPresent(Hooks.hook_index_lease4_release_)) {
            CalloutHandlePtr callout_handle = getCalloutHandle(release);

            // Use the RAII wrapper to make sure that the callout handle state is
            // reset when this object goes out of scope. All hook points must do
            // it to prevent possible circular dependency between the callout
            // handle and its arguments.
            ScopedCalloutHandleState callout_handle_state(callout_handle);

            // Enable copying options from the packet within hook library.
            ScopedEnableOptionsCopy<Pkt4> query4_options_copy(release);

            // Pass the original packet
            callout_handle->setArgument("query4", release);

            // Pass the lease to be updated
            callout_handle->setArgument("lease4", lease);

            // Call all installed callouts
            HooksManager::callCallouts(Hooks.hook_index_lease4_release_,
                                       *callout_handle);

            // Callouts decided to skip the next processing step. The next
            // processing step would to send the packet, so skip at this
            // stage means "drop response".
            if ((callout_handle->getStatus() == CalloutHandle::NEXT_STEP_SKIP) ||
                (callout_handle->getStatus() == CalloutHandle::NEXT_STEP_DROP)) {
                skip = true;
                LOG_DEBUG(hooks_logger, DBG_DHCP4_HOOKS,
                          DHCP4_HOOK_LEASE4_RELEASE_SKIP)
                    .arg(release->getLabel());
            }
        }

        // Callout didn't indicate to skip the release process. Let's release
        // the lease.
        if (!skip) {
            bool success = LeaseMgrFactory::instance().deleteLease(lease->addr_);

            if (success) {

                context.reset(new AllocEngine::ClientContext4());
                context->old_lease_ = lease;

                // Release successful
                LOG_INFO(lease4_logger, DHCP4_RELEASE)
                    .arg(release->getLabel())
                    .arg(lease->addr_.toText());

                // Need to decrease statistic for assigned addresses.
                StatsMgr::instance().addValue(
                    StatsMgr::generateName("subnet", lease->subnet_id_, "assigned-addresses"),
                    static_cast<int64_t>(-1));

                // Remove existing DNS entries for the lease, if any.
                queueNCR(CHG_REMOVE, lease);

            } else {
                // Release failed
                LOG_ERROR(lease4_logger, DHCP4_RELEASE_FAIL)
                    .arg(release->getLabel())
                    .arg(lease->addr_.toText());
            }
        }
    } catch (const isc::Exception& ex) {
        LOG_ERROR(lease4_logger, DHCP4_RELEASE_EXCEPTION)
            .arg(release->getLabel())
            .arg(release->getCiaddr())
            .arg(ex.what());
    }
}

void
Dhcpv4Srv::processDecline(Pkt4Ptr& decline, AllocEngine::ClientContext4Ptr& context) {

    // Server-id is mandatory in DHCPDECLINE (see table 5, RFC2131)
    /// @todo Uncomment this (see ticket #3116)
    // sanityCheck(decline, MANDATORY);

    // Client is supposed to specify the address being declined in
    // Requested IP address option, but must not set its ciaddr.
    // (again, see table 5 in RFC2131).

    OptionCustomPtr opt_requested_address = boost::dynamic_pointer_cast<
        OptionCustom>(decline->getOption(DHO_DHCP_REQUESTED_ADDRESS));
    if (!opt_requested_address) {

        isc_throw(RFCViolation, "Mandatory 'Requested IP address' option missing"
                  "in DHCPDECLINE sent from " << decline->getLabel());
    }
    IOAddress addr(opt_requested_address->readAddress());

    // We could also extract client's address from ciaddr, but that's clearly
    // against RFC2131.

    // Now we need to check whether this address really belongs to the client
    // that attempts to decline it.
    const Lease4Ptr lease = LeaseMgrFactory::instance().getLease4(addr);

    if (!lease) {
        // Client tried to decline an address, but we don't have a lease for
        // that address. Let's ignore it.
        //
        // We could assume that we're recovering from a mishandled migration
        // to a new server and mark the address as declined, but the window of
        // opportunity for that to be useful is small and the attack vector
        // would be pretty severe.
        LOG_WARN(dhcp4_logger, DHCP4_DECLINE_LEASE_NOT_FOUND)
            .arg(addr.toText()).arg(decline->getLabel());
        return;
    }

    // Get client-id, if available.
    OptionPtr opt_clientid = decline->getOption(DHO_DHCP_CLIENT_IDENTIFIER);
    ClientIdPtr client_id;
    if (opt_clientid) {
        client_id.reset(new ClientId(opt_clientid->getData()));
    }

    // Check if the client attempted to decline a lease it doesn't own.
    if (!lease->belongsToClient(decline->getHWAddr(), client_id)) {

        // Get printable hardware addresses
        string client_hw = decline->getHWAddr() ?
            decline->getHWAddr()->toText(false) : "(none)";
        string lease_hw = lease->hwaddr_ ?
            lease->hwaddr_->toText(false) : "(none)";

        // Get printable client-ids
        string client_id_txt = client_id ? client_id->toText() : "(none)";
        string lease_id_txt = lease->client_id_ ?
            lease->client_id_->toText() : "(none)";

        // Print the warning and we're done here.
        LOG_WARN(dhcp4_logger, DHCP4_DECLINE_LEASE_MISMATCH)
            .arg(addr.toText()).arg(decline->getLabel())
            .arg(client_hw).arg(lease_hw).arg(client_id_txt).arg(lease_id_txt);

        return;
    }

    // Ok, all is good. The client is reporting its own address. Let's
    // process it.
    declineLease(lease, decline, context);
}

void
Dhcpv4Srv::declineLease(const Lease4Ptr& lease, const Pkt4Ptr& decline,
                        AllocEngine::ClientContext4Ptr& context) {

    // Let's check if there are hooks installed for decline4 hook point.
    // If they are, let's pass the lease and client's packet. If the hook
    // sets status to drop, we reject this Decline.
    if (HooksManager::calloutsPresent(Hooks.hook_index_lease4_decline_)) {
        CalloutHandlePtr callout_handle = getCalloutHandle(decline);

        // Use the RAII wrapper to make sure that the callout handle state is
        // reset when this object goes out of scope. All hook points must do
        // it to prevent possible circular dependency between the callout
        // handle and its arguments.
        ScopedCalloutHandleState callout_handle_state(callout_handle);

        // Enable copying options from the packet within hook library.
        ScopedEnableOptionsCopy<Pkt4> query4_options_copy(decline);

        // Pass incoming Decline and the lease to be declined.
        callout_handle->setArgument("lease4", lease);
        callout_handle->setArgument("query4", decline);

        // Call callouts
        HooksManager::callCallouts(Hooks.hook_index_lease4_decline_,
                                   *callout_handle);

        // Check if callouts decided to skip the next processing step.
        // If any of them did, we will drop the packet.
        if ((callout_handle->getStatus() == CalloutHandle::NEXT_STEP_SKIP) ||
            (callout_handle->getStatus() == CalloutHandle::NEXT_STEP_DROP)) {
            LOG_DEBUG(hooks_logger, DBG_DHCP4_HOOKS, DHCP4_HOOK_DECLINE_SKIP)
                .arg(decline->getLabel()).arg(lease->addr_.toText());
            return;
        }
    }

    // Remove existing DNS entries for the lease, if any.
    // queueNCR will do the necessary checks and will skip the update, if not needed.
    queueNCR(CHG_REMOVE, lease);

    // Bump up the statistics.

    // Per subnet declined addresses counter.
    StatsMgr::instance().addValue(
        StatsMgr::generateName("subnet", lease->subnet_id_, "declined-addresses"),
        static_cast<int64_t>(1));

    // Global declined addresses counter.
    StatsMgr::instance().addValue("declined-addresses", static_cast<int64_t>(1));

    // We do not want to decrease the assigned-addresses at this time. While
    // technically a declined address is no longer allocated, the primary usage
    // of the assigned-addresses statistic is to monitor pool utilization. Most
    // people would forget to include declined-addresses in the calculation,
    // and simply do assigned-addresses/total-addresses. This would have a bias
    // towards under-representing pool utilization, if we decreased allocated
    // immediately after receiving DHCPDECLINE, rather than later when we recover
    // the address.

    // @todo: Call hooks.

    // We need to disassociate the lease from the client. Once we move a lease
    // to declined state, it is no longer associated with the client in any
    // way.
    lease->decline(CfgMgr::instance().getCurrentCfg()->getDeclinePeriod());

    LeaseMgrFactory::instance().updateLease4(lease);

    context.reset(new AllocEngine::ClientContext4());
    context->new_lease_ = lease;

    LOG_INFO(lease4_logger, DHCP4_DECLINE_LEASE).arg(lease->addr_.toText())
        .arg(decline->getLabel()).arg(lease->valid_lft_);
}

Pkt4Ptr
Dhcpv4Srv::processInform(Pkt4Ptr& inform) {
    // DHCPINFORM MUST not include server identifier.
    sanityCheck(inform, FORBIDDEN);

    bool drop = false;
    Dhcpv4Exchange ex(alloc_engine_, inform, selectSubnet(inform, drop));

    // Stop here if selectSubnet decided to drop the packet
    if (drop) {
        return (Pkt4Ptr());
    }

    Pkt4Ptr ack = ex.getResponse();

    ex.setReservedClientClasses();
    requiredClassify(ex);

    buildCfgOptionList(ex);
    appendRequestedOptions(ex);
    appendRequestedVendorOptions(ex);
    appendBasicOptions(ex);
    adjustIfaceData(ex);

    // Set fixed fields (siaddr, sname, filename) if defined in
    // the reservation, class or subnet specific configuration.
    setFixedFields(ex);

    // There are cases for the DHCPINFORM that the server receives it via
    // relay but will send the response to the client's unicast address
    // carried in the ciaddr. In this case, the giaddr and hops field should
    // be cleared (these fields were copied by the copyDefaultFields function).
    // Also Relay Agent Options should be removed if present.
    if (ack->getRemoteAddr() != inform->getGiaddr()) {
        LOG_DEBUG(packet4_logger, DBG_DHCP4_DETAIL, DHCP4_INFORM_DIRECT_REPLY)
            .arg(inform->getLabel())
            .arg(ack->getRemoteAddr())
            .arg(ack->getIface());
        ack->setHops(0);
        ack->setGiaddr(IOAddress::IPV4_ZERO_ADDRESS());
        ack->delOption(DHO_DHCP_AGENT_OPTIONS);
    }

    // The DHCPACK must contain server id.
    appendServerID(ex);

    return (ex.getResponse());
}

bool
Dhcpv4Srv::accept(const Pkt4Ptr& query) const {
    // Check that the message type is accepted by the server. We rely on the
    // function called to log a message if needed.
    if (!acceptMessageType(query)) {
        return (false);
    }
    // Check if the message from directly connected client (if directly
    // connected) should be dropped or processed.
    if (!acceptDirectRequest(query)) {
        LOG_DEBUG(bad_packet4_logger, DBG_DHCP4_DETAIL, DHCP4_PACKET_DROP_0002)
            .arg(query->getLabel())
            .arg(query->getIface());
        return (false);
    }

    // Check if the DHCPv4 packet has been sent to us or to someone else.
    // If it hasn't been sent to us, drop it!
    if (!acceptServerId(query)) {
        LOG_DEBUG(bad_packet4_logger, DBG_DHCP4_DETAIL, DHCP4_PACKET_DROP_0003)
            .arg(query->getLabel())
            .arg(query->getIface());
        return (false);
    }

    return (true);
}

bool
Dhcpv4Srv::acceptDirectRequest(const Pkt4Ptr& pkt) const {
    // Accept all relayed messages.
    if (pkt->isRelayed()) {
        return (true);
    }

    // Accept all DHCPv4-over-DHCPv6 messages.
    if (pkt->isDhcp4o6()) {
        return (true);
    }

    // The source address must not be zero for the DHCPINFORM message from
    // the directly connected client because the server will not know where
    // to respond if the ciaddr was not present.
    try {
        if (pkt->getType() == DHCPINFORM) {
            if (pkt->getRemoteAddr().isV4Zero() &&
                pkt->getCiaddr().isV4Zero()) {
                return (false);
            }
        }
    } catch (...) {
        // If we got here, it is probably because the message type hasn't
        // been set. But, this should not really happen assuming that
        // we validate the message type prior to calling this function.
        return (false);
    }
    bool drop = false;
    bool result = (!pkt->getLocalAddr().isV4Bcast() ||
                   selectSubnet(pkt, drop, true));
    if (drop) {
        // The packet must be dropped but as sanity_only is true it is dead code.
        return (false);
    }
    return (result);
}

bool
Dhcpv4Srv::acceptMessageType(const Pkt4Ptr& query) const {
    // When receiving a packet without message type option, getType() will
    // throw.
    int type;
    try {
        type = query->getType();

    } catch (...) {
        LOG_DEBUG(bad_packet4_logger, DBG_DHCP4_DETAIL, DHCP4_PACKET_DROP_0004)
            .arg(query->getLabel())
            .arg(query->getIface());
        return (false);
    }

    // Once we know that the message type is within a range of defined DHCPv4
    // messages, we do a detailed check to make sure that the received message
    // is targeted at server. Note that we could have received some Offer
    // message broadcasted by the other server to a relay. Even though, the
    // server would rather unicast its response to a relay, let's be on the
    // safe side. Also, we want to drop other messages which we don't support.
    // All these valid messages that we are not going to process are dropped
    // silently.

    switch(type) {
        case DHCPDISCOVER:
        case DHCPREQUEST:
        case DHCPRELEASE:
        case DHCPDECLINE:
        case DHCPINFORM:
            return (true);
            break;

        case DHCP_NOTYPE:
            LOG_INFO(bad_packet4_logger, DHCP4_PACKET_DROP_0009)
                     .arg(query->getLabel());
            break;

        default:
            // If we receive a message with a non-existing type, we are logging it.
            if (type >= DHCP_TYPES_EOF) {
                LOG_DEBUG(bad_packet4_logger, DBG_DHCP4_DETAIL, DHCP4_PACKET_DROP_0005)
                          .arg(query->getLabel())
                          .arg(type);
            } else {
                // Exists but we don't support it.
                LOG_DEBUG(bad_packet4_logger, DBG_DHCP4_DETAIL, DHCP4_PACKET_DROP_0006)
                      .arg(query->getLabel())
                      .arg(type);
            }
            break;
    }

    return (false);
}

bool
Dhcpv4Srv::acceptServerId(const Pkt4Ptr& query) const {
    // This function is meant to be called internally by the server class, so
    // we rely on the caller to sanity check the pointer and we don't check
    // it here.

    // Check if server identifier option is present. If it is not present
    // we accept the message because it is targeted to all servers.
    // Note that we don't check cases that server identifier is mandatory
    // but not present. This is meant to be sanity checked in other
    // functions.
    OptionPtr option = query->getOption(DHO_DHCP_SERVER_IDENTIFIER);
    if (!option) {
        return (true);
    }
    // Server identifier is present. Let's convert it to 4-byte address
    // and try to match with server identifiers used by the server.
    OptionCustomPtr option_custom =
        boost::dynamic_pointer_cast<OptionCustom>(option);
    // Unable to convert the option to the option type which encapsulates it.
    // We treat this as non-matching server id.
    if (!option_custom) {
        return (false);
    }
    // The server identifier option should carry exactly one IPv4 address.
    // If the option definition for the server identifier doesn't change,
    // the OptionCustom object should have exactly one IPv4 address and
    // this check is somewhat redundant. On the other hand, if someone
    // breaks option it may be better to check that here.
    if (option_custom->getDataFieldsNum() != 1) {
        return (false);
    }

    // The server identifier MUST be an IPv4 address. If given address is
    // v6, it is wrong.
    IOAddress server_id = option_custom->readAddress();
    if (!server_id.isV4()) {
        return (false);
    }

    // This function iterates over all interfaces on which the
    // server is listening to find the one which has a socket bound
    // to the address carried in the server identifier option.
    // This has some performance implications. However, given that
    // typically there will be just a few active interfaces the
    // performance hit should be acceptable. If it turns out to
    // be significant, we will have to cache server identifiers
    // when sockets are opened.
    if (IfaceMgr::instance().hasOpenSocket(server_id)) {
        return (true);
    }

    // There are some cases when an administrator explicitly sets server
    // identifier (option 54) that should be used for a given, subnet,
    // network etc. It doesn't have to be an address assigned to any of
    // the server interfaces. Thus, we have to check if the server
    // identifier received is the one that we explicitly set in the
    // server configuration. At this point, we don't know which subnet
    // the client belongs to so we can't match the server id with any
    // subnet. We simply check if this server identifier is configured
    // anywhere. This should be good enough to eliminate exchanges
    // with other servers in the same network.

    /// @todo Currently we only check subnet identifiers configured on the
    /// subnet level, shared network level and global level. This should
    /// be sufficient for most of cases. At this point, trying to support
    /// server identifiers on the class level seems to be an overkill and
    /// is probably not needed. Same with host reservations. In fact,
    /// at this point we don't know the reservations for the client
    /// communicating with the server. We may revise some of these choices
    /// in the future.

    SrvConfigPtr cfg = CfgMgr::instance().getCurrentCfg();

    // Check if there is at least one subnet configured with this server
    // identifier.
    ConstCfgSubnets4Ptr cfg_subnets = cfg->getCfgSubnets4();
    if (cfg_subnets->hasSubnetWithServerId(server_id)) {
        return (true);
    }

    // This server identifier is not configured for any of the subnets, so
    // check on the shared network level.
    CfgSharedNetworks4Ptr cfg_networks = cfg->getCfgSharedNetworks4();
    if (cfg_networks->hasNetworkWithServerId(server_id)) {
        return (true);
    }

    // Finally, it is possible that the server identifier is specified
    // on the global level.
    ConstCfgOptionPtr cfg_global_options = cfg->getCfgOption();
    OptionCustomPtr opt_server_id = boost::dynamic_pointer_cast<OptionCustom>
        (cfg_global_options->get(DHCP4_OPTION_SPACE, DHO_DHCP_SERVER_IDENTIFIER).option_);

    return (opt_server_id && (opt_server_id->readAddress() == server_id));
}

void
Dhcpv4Srv::sanityCheck(const Pkt4Ptr& query, RequirementLevel serverid) {
    OptionPtr server_id = query->getOption(DHO_DHCP_SERVER_IDENTIFIER);
    switch (serverid) {
    case FORBIDDEN:
        if (server_id) {
            isc_throw(RFCViolation, "Server-id option was not expected, but "
                      << "received in "
                      << query->getName());
        }
        break;

    case MANDATORY:
        if (!server_id) {
            isc_throw(RFCViolation, "Server-id option was expected, but not "
                      " received in message "
                      << query->getName());
        }
        break;

    case OPTIONAL:
        // do nothing here
        ;
    }

    // If there is HWAddress set and it is non-empty, then we're good
    if (query->getHWAddr() && !query->getHWAddr()->hwaddr_.empty()) {
        return;
    }

    // There has to be something to uniquely identify the client:
    // either non-zero MAC address or client-id option present (or both)
    OptionPtr client_id = query->getOption(DHO_DHCP_CLIENT_IDENTIFIER);

    // If there's no client-id (or a useless one is provided, i.e. 0 length)
    if (!client_id || client_id->len() == client_id->getHeaderLen()) {
        isc_throw(RFCViolation, "Missing or useless client-id and no HW address "
                  " provided in message "
                  << query->getName());
    }
}

void Dhcpv4Srv::classifyByVendor(const Pkt4Ptr& pkt) {
    // Built-in vendor class processing
    boost::shared_ptr<OptionString> vendor_class =
        boost::dynamic_pointer_cast<OptionString>(pkt->getOption(DHO_VENDOR_CLASS_IDENTIFIER));

    if (!vendor_class) {
        return;
    }

    pkt->addClass(VENDOR_CLASS_PREFIX + vendor_class->getValue());
}

void Dhcpv4Srv::classifyPacket(const Pkt4Ptr& pkt) {
    // All packets belongs to ALL.
    pkt->addClass("ALL");

    // First: built-in vendor class processing.
    classifyByVendor(pkt);

    // Run match expressions on classes not depending on KNOWN/UNKNOWN.
    evaluateClasses(pkt, false);
}

void Dhcpv4Srv::evaluateClasses(const Pkt4Ptr& pkt, bool depend_on_known) {
    // Note getClientClassDictionary() cannot be null
    const ClientClassDictionaryPtr& dict =
        CfgMgr::instance().getCurrentCfg()->getClientClassDictionary();
    const ClientClassDefListPtr& defs_ptr = dict->getClasses();
    for (ClientClassDefList::const_iterator it = defs_ptr->cbegin();
         it != defs_ptr->cend(); ++it) {
        // Note second cannot be null
        const ExpressionPtr& expr_ptr = (*it)->getMatchExpr();
        // Nothing to do without an expression to evaluate
        if (!expr_ptr) {
            continue;
        }
        // Not the right time if only when required
        if ((*it)->getRequired()) {
            continue;
        }
        // Not the right pass.
        if ((*it)->getDependOnKnown() != depend_on_known) {
            continue;
        }
        // Evaluate the expression which can return false (no match),
        // true (match) or raise an exception (error)
        try {
            bool status = evaluateBool(*expr_ptr, *pkt);
            if (status) {
                LOG_INFO(options4_logger, EVAL_RESULT)
                    .arg((*it)->getName())
                    .arg(status);
                // Matching: add the class
                pkt->addClass((*it)->getName());
            } else {
                LOG_DEBUG(options4_logger, DBG_DHCP4_DETAIL, EVAL_RESULT)
                    .arg((*it)->getName())
                    .arg(status);
            }
        } catch (const Exception& ex) {
            LOG_ERROR(options4_logger, EVAL_RESULT)
                .arg((*it)->getName())
                .arg(ex.what());
        } catch (...) {
            LOG_ERROR(options4_logger, EVAL_RESULT)
                .arg((*it)->getName())
                .arg("get exception?");
        }
    }
}

void Dhcpv4Srv::requiredClassify(Dhcpv4Exchange& ex) {
    // First collect required classes
    Pkt4Ptr query = ex.getQuery();
    ClientClasses classes = query->getClasses(true);
    Subnet4Ptr subnet = ex.getContext()->subnet_;

    if (subnet) {
        // Begin by the shared-network
        SharedNetwork4Ptr network;
        subnet->getSharedNetwork(network);
        if (network) {
            const ClientClasses& to_add = network->getRequiredClasses();
            for (ClientClasses::const_iterator cclass = to_add.cbegin();
                 cclass != to_add.cend(); ++cclass) {
                classes.insert(*cclass);
            }
        }

        // Followed by the subnet
        const ClientClasses& to_add = subnet->getRequiredClasses();
        for(ClientClasses::const_iterator cclass = to_add.cbegin();
            cclass != to_add.cend(); ++cclass) {
            classes.insert(*cclass);
        }

        // And finish by the pool
        Pkt4Ptr resp = ex.getResponse();
        IOAddress addr = IOAddress::IPV4_ZERO_ADDRESS();
        if (resp) {
            addr = resp->getYiaddr();
        }
        if (!addr.isV4Zero()) {
            PoolPtr pool = subnet->getPool(Lease::TYPE_V4, addr, false);
            if (pool) {
                const ClientClasses& to_add = pool->getRequiredClasses();
                for (ClientClasses::const_iterator cclass = to_add.cbegin();
                     cclass != to_add.cend(); ++cclass) {
                    classes.insert(*cclass);
                }
            }
        }

        // host reservation???
    }

    // Run match expressions
    // Note getClientClassDictionary() cannot be null
    const ClientClassDictionaryPtr& dict =
        CfgMgr::instance().getCurrentCfg()->getClientClassDictionary();
    for (ClientClasses::const_iterator cclass = classes.cbegin();
         cclass != classes.cend(); ++cclass) {
        const ClientClassDefPtr class_def = dict->findClass(*cclass);
        if (!class_def) {
            LOG_DEBUG(dhcp4_logger, DBG_DHCP4_BASIC, DHCP4_CLASS_UNDEFINED)
                .arg(*cclass);
            continue;
        }
        const ExpressionPtr& expr_ptr = class_def->getMatchExpr();
        // Nothing to do without an expression to evaluate
        if (!expr_ptr) {
            LOG_DEBUG(dhcp4_logger, DBG_DHCP4_BASIC, DHCP4_CLASS_UNTESTABLE)
                .arg(*cclass);
            continue;
        }
        // Evaluate the expression which can return false (no match),
        // true (match) or raise an exception (error)
        try {
            bool status = evaluateBool(*expr_ptr, *query);
            if (status) {
                LOG_INFO(options4_logger, EVAL_RESULT)
                    .arg(*cclass)
                    .arg(status);
                // Matching: add the class
                query->addClass(*cclass);
            } else {
                LOG_DEBUG(options4_logger, DBG_DHCP4_DETAIL, EVAL_RESULT)
                    .arg(*cclass)
                    .arg(status);
            }
        } catch (const Exception& ex) {
            LOG_ERROR(options4_logger, EVAL_RESULT)
                .arg(*cclass)
                .arg(ex.what());
        } catch (...) {
            LOG_ERROR(options4_logger, EVAL_RESULT)
                .arg(*cclass)
                .arg("get exception?");
        }
    }
}

void
Dhcpv4Srv::deferredUnpack(Pkt4Ptr& query)
{
    // Iterate on the list of deferred option codes
    BOOST_FOREACH(const uint16_t& code, query->getDeferredOptions()) {
        OptionDefinitionPtr def;
        // Iterate on client classes
        const ClientClasses& classes = query->getClasses();
        for (ClientClasses::const_iterator cclass = classes.cbegin();
             cclass != classes.cend(); ++cclass) {
            // Get the client class definition for this class
            const ClientClassDefPtr& ccdef =
                CfgMgr::instance().getCurrentCfg()->
                getClientClassDictionary()->findClass(*cclass);
            // If not found skip it
            if (!ccdef) {
                continue;
            }
            // If there is no option definition skip it
            if (!ccdef->getCfgOptionDef()) {
                continue;
            }
            def = ccdef->getCfgOptionDef()->get(DHCP4_OPTION_SPACE, code);
            // Stop at the first client class with a defition
            if (def) {
                break;
            }
        }
        // If not found try the global definition
        if (!def) {
            def = LibDHCP::getOptionDef(DHCP4_OPTION_SPACE, code);
        }
        if (!def) {
            def = LibDHCP::getRuntimeOptionDef(DHCP4_OPTION_SPACE, code);
        }
        // Finish by last resort definition
        if (!def) {
            def = LibDHCP::getLastResortOptionDef(DHCP4_OPTION_SPACE, code);
        }
        // If not defined go to the next option
        if (!def) {
            continue;
        }
        // Get the existing option for its content and remove all
        OptionPtr opt = query->getOption(code);
        if (!opt) {
            // should not happen but do not crash anyway
            continue;
        }
        const OptionBuffer buf = opt->getData();
        while (query->delOption(code)) {
            // continue
        }
        // Unpack the option and add it
        opt = def->optionFactory(Option::V4, code, buf.cbegin(), buf.cend());
        query->addOption(opt);
    }
}

void
Dhcpv4Srv::startD2() {
    D2ClientMgr& d2_mgr = CfgMgr::instance().getD2ClientMgr();
    if (d2_mgr.ddnsEnabled()) {
        // Updates are enabled, so lets start the sender, passing in
        // our error handler.
        // This may throw so wherever this is called needs to ready.
        d2_mgr.startSender(boost::bind(&Dhcpv4Srv::d2ClientErrorHandler,
                                       this, _1, _2));
    }
}

void
Dhcpv4Srv::stopD2() {
    D2ClientMgr& d2_mgr = CfgMgr::instance().getD2ClientMgr();
    if (d2_mgr.ddnsEnabled()) {
        // Updates are enabled, so lets stop the sender
        d2_mgr.stopSender();
    }
}

void
Dhcpv4Srv::d2ClientErrorHandler(const
                                dhcp_ddns::NameChangeSender::Result result,
                                dhcp_ddns::NameChangeRequestPtr& ncr) {
    LOG_ERROR(ddns4_logger, DHCP4_DDNS_REQUEST_SEND_FAILED).
              arg(result).arg((ncr ? ncr->toText() : " NULL "));
    // We cannot communicate with kea-dhcp-ddns, suspend further updates.
    /// @todo We may wish to revisit this, but for now we will simply turn
    /// them off.
    CfgMgr::instance().getD2ClientMgr().suspendUpdates();
}

// Refer to config_report so it will be embedded in the binary
const char* const* dhcp4_config_report = isc::detail::config_report;

std::string
Dhcpv4Srv::getVersion(bool extended) {
    std::stringstream tmp;

    tmp << VERSION;
    if (extended) {
        tmp << endl << EXTENDED_VERSION << endl;
        tmp << "linked with:" << endl;
        tmp << Logger::getVersion() << endl;
        tmp << CryptoLink::getVersion() << endl;
        tmp << "database:" << endl;
#ifdef HAVE_MYSQL
        tmp << MySqlLeaseMgr::getDBVersion() << endl;
#endif
#ifdef HAVE_PGSQL
        tmp << PgSqlLeaseMgr::getDBVersion() << endl;
#endif
#ifdef HAVE_CQL
        tmp << CqlLeaseMgr::getDBVersion() << endl;
#endif
        tmp << Memfile_LeaseMgr::getDBVersion();

        // @todo: more details about database runtime
    }

    return (tmp.str());
}

void Dhcpv4Srv::processStatsReceived(const Pkt4Ptr& query) {
    // Note that we're not bumping pkt4-received statistic as it was
    // increased early in the packet reception code.

    string stat_name = "pkt4-unknown-received";
    try {
        switch (query->getType()) {
        case DHCPDISCOVER:
            stat_name = "pkt4-discover-received";
            break;
        case DHCPOFFER:
            // Should not happen, but let's keep a counter for it
            stat_name = "pkt4-offer-received";
            break;
        case DHCPREQUEST:
            stat_name = "pkt4-request-received";
            break;
        case DHCPACK:
            // Should not happen, but let's keep a counter for it
            stat_name = "pkt4-ack-received";
            break;
        case DHCPNAK:
            // Should not happen, but let's keep a counter for it
            stat_name = "pkt4-nak-received";
            break;
        case DHCPRELEASE:
            stat_name = "pkt4-release-received";
        break;
        case DHCPDECLINE:
            stat_name = "pkt4-decline-received";
            break;
        case DHCPINFORM:
            stat_name = "pkt4-inform-received";
            break;
        default:
            ; // do nothing
        }
    }
    catch (...) {
        // If the incoming packet doesn't have option 53 (message type)
        // or a hook set pkt4_receive_skip, then Pkt4::getType() may
        // throw an exception. That's ok, we'll then use the default
        // name of pkt4-unknown-received.
    }

    isc::stats::StatsMgr::instance().addValue(stat_name,
                                              static_cast<int64_t>(1));
}

void Dhcpv4Srv::processStatsSent(const Pkt4Ptr& response) {
    // Increase generic counter for sent packets.
    isc::stats::StatsMgr::instance().addValue("pkt4-sent",
                                              static_cast<int64_t>(1));

    // Increase packet type specific counter for packets sent.
    string stat_name;
    switch (response->getType()) {
    case DHCPOFFER:
        stat_name = "pkt4-offer-sent";
        break;
    case DHCPACK:
        stat_name = "pkt4-ack-sent";
        break;
    case DHCPNAK:
        stat_name = "pkt4-nak-sent";
        break;
    default:
        // That should never happen
        return;
    }

    isc::stats::StatsMgr::instance().addValue(stat_name,
                                              static_cast<int64_t>(1));
}

int Dhcpv4Srv::getHookIndexBuffer4Receive() {
    return (Hooks.hook_index_buffer4_receive_);
}

int Dhcpv4Srv::getHookIndexPkt4Receive() {
    return (Hooks.hook_index_pkt4_receive_);
}

int Dhcpv4Srv::getHookIndexSubnet4Select() {
    return (Hooks.hook_index_subnet4_select_);
}

int Dhcpv4Srv::getHookIndexLease4Release() {
    return (Hooks.hook_index_lease4_release_);
}

int Dhcpv4Srv::getHookIndexPkt4Send() {
    return (Hooks.hook_index_pkt4_send_);
}

int Dhcpv4Srv::getHookIndexBuffer4Send() {
    return (Hooks.hook_index_buffer4_send_);
}

int Dhcpv4Srv::getHookIndexLease4Decline() {
    return (Hooks.hook_index_lease4_decline_);
}

void Dhcpv4Srv::discardPackets() {
    // Clear any packets held by the callhout handle store and
    // all parked packets
    isc::dhcp::Pkt4Ptr pkt4ptr_empty;
    isc::dhcp::getCalloutHandle(pkt4ptr_empty);
    HooksManager::clearParkingLots();
}

}   // namespace dhcp
}   // namespace isc
