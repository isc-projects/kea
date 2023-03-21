// Copyright (C) 2014-2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <exceptions/exceptions.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/parsers/base_network_parser.h>
#include <dhcpsrv/parsers/simple_parser4.h>
#include <dhcpsrv/srv_config.h>
#include <dhcpsrv/lease_mgr_factory.h>
#include <dhcpsrv/dhcpsrv_log.h>
#include <dhcpsrv/cfg_hosts_util.h>
#include <process/logging_info.h>
#include <log/logger_manager.h>
#include <log/logger_specification.h>
#include <dhcp/pkt.h> // Needed for HWADDR_SOURCE_*
#include <stats/stats_mgr.h>
#include <util/strutil.h>

#include <boost/make_shared.hpp>

#include <list>
#include <sstream>

using namespace isc::log;
using namespace isc::data;
using namespace isc::process;

namespace isc {
namespace dhcp {

SrvConfig::SrvConfig()
    : sequence_(0), cfg_iface_(new CfgIface()),
      cfg_option_def_(new CfgOptionDef()), cfg_option_(new CfgOption()),
      cfg_subnets4_(new CfgSubnets4()), cfg_subnets6_(new CfgSubnets6()),
      cfg_shared_networks4_(new CfgSharedNetworks4()),
      cfg_shared_networks6_(new CfgSharedNetworks6()),
      cfg_hosts_(new CfgHosts()), cfg_rsoo_(new CfgRSOO()),
      cfg_expiration_(new CfgExpiration()), cfg_duid_(new CfgDUID()),
      cfg_db_access_(new CfgDbAccess()),
      cfg_host_operations4_(CfgHostOperations::createConfig4()),
      cfg_host_operations6_(CfgHostOperations::createConfig6()),
      class_dictionary_(new ClientClassDictionary()),
      decline_timer_(0), echo_v4_client_id_(true), dhcp4o6_port_(0),
      d2_client_config_(new D2ClientConfig()),
      configured_globals_(new CfgGlobals()), cfg_consist_(new CfgConsistency()),
      lenient_option_parsing_(false), ignore_dhcp_server_identifier_(false),
      ignore_rai_link_selection_(false), exclude_first_last_24_(false),
      reservations_lookup_first_(false) {
}

SrvConfig::SrvConfig(const uint32_t sequence)
    : sequence_(sequence), cfg_iface_(new CfgIface()),
      cfg_option_def_(new CfgOptionDef()), cfg_option_(new CfgOption()),
      cfg_subnets4_(new CfgSubnets4()), cfg_subnets6_(new CfgSubnets6()),
      cfg_shared_networks4_(new CfgSharedNetworks4()),
      cfg_shared_networks6_(new CfgSharedNetworks6()),
      cfg_hosts_(new CfgHosts()), cfg_rsoo_(new CfgRSOO()),
      cfg_expiration_(new CfgExpiration()), cfg_duid_(new CfgDUID()),
      cfg_db_access_(new CfgDbAccess()),
      cfg_host_operations4_(CfgHostOperations::createConfig4()),
      cfg_host_operations6_(CfgHostOperations::createConfig6()),
      class_dictionary_(new ClientClassDictionary()),
      decline_timer_(0), echo_v4_client_id_(true), dhcp4o6_port_(0),
      d2_client_config_(new D2ClientConfig()),
      configured_globals_(new CfgGlobals()), cfg_consist_(new CfgConsistency()),
      lenient_option_parsing_(false), ignore_dhcp_server_identifier_(false),
      ignore_rai_link_selection_(false), exclude_first_last_24_(false),
      reservations_lookup_first_(false) {
}

std::string
SrvConfig::getConfigSummary(const uint32_t selection) const {
    std::ostringstream s;
    size_t subnets_num;
    if ((selection & CFGSEL_SUBNET4) == CFGSEL_SUBNET4) {
        subnets_num = getCfgSubnets4()->getAll()->size();
        if (subnets_num > 0) {
            s << "added IPv4 subnets: " << subnets_num;
        } else {
            s << "no IPv4 subnets!";
        }
        s << "; ";
    }

    if ((selection & CFGSEL_SUBNET6) == CFGSEL_SUBNET6) {
        subnets_num = getCfgSubnets6()->getAll()->size();
        if (subnets_num > 0) {
            s << "added IPv6 subnets: " << subnets_num;
        } else {
            s << "no IPv6 subnets!";
        }
        s << "; ";
    }

    if ((selection & CFGSEL_DDNS) == CFGSEL_DDNS) {
        bool ddns_enabled = getD2ClientConfig()->getEnableUpdates();
        s << "DDNS: " << (ddns_enabled ? "enabled" : "disabled") << "; ";
    }

    if (s.tellp() == static_cast<std::streampos>(0)) {
        s << "no config details available";
    }

    std::string summary = s.str();
    size_t last_separator_pos = summary.find_last_of(";");
    if (last_separator_pos == summary.length() - 2) {
        summary.erase(last_separator_pos);
    }
    return (summary);
}

bool
SrvConfig::sequenceEquals(const SrvConfig& other) {
    return (getSequence() == other.getSequence());
}

void
SrvConfig::copy(SrvConfig& new_config) const {
    ConfigBase::copy(new_config);

    // Replace interface configuration.
    new_config.cfg_iface_.reset(new CfgIface(*cfg_iface_));
    // Replace option definitions.
    cfg_option_def_->copyTo(*new_config.cfg_option_def_);
    cfg_option_->copyTo(*new_config.cfg_option_);
    // Replace the client class dictionary
    new_config.class_dictionary_.reset(new ClientClassDictionary(*class_dictionary_));
    // Replace the D2 client configuration
    new_config.setD2ClientConfig(getD2ClientConfig());
    // Replace configured hooks libraries.
    new_config.hooks_config_.clear();
    using namespace isc::hooks;
    for (HookLibsCollection::const_iterator it = hooks_config_.get().begin();
         it != hooks_config_.get().end(); ++it) {
        new_config.hooks_config_.add(it->first, it->second);
    }
}

bool
SrvConfig::equals(const SrvConfig& other) const {

    // Checks common elements: logging & config control
    if (!ConfigBase::equals(other)) {
        return (false);
    }

    // Common information is equal between objects, so check other values.
    if ((*cfg_iface_ != *other.cfg_iface_) ||
        (*cfg_option_def_ != *other.cfg_option_def_) ||
        (*cfg_option_ != *other.cfg_option_) ||
        (*class_dictionary_ != *other.class_dictionary_) ||
        (*d2_client_config_ != *other.d2_client_config_)) {
        return (false);
    }
    // Now only configured hooks libraries can differ.
    // If number of configured hooks libraries are different, then
    // configurations aren't equal.
    if (hooks_config_.get().size() != other.hooks_config_.get().size()) {
        return (false);
    }
    // Pass through all configured hooks libraries.
    return (hooks_config_.equal(other.hooks_config_));
}

void
SrvConfig::merge(ConfigBase& other) {
    ConfigBase::merge(other);
    try {
        SrvConfig& other_srv_config = dynamic_cast<SrvConfig&>(other);
        // We merge objects in order of dependency (real or theoretical).
        // First we merge the common stuff.

        // Merge globals.
        mergeGlobals(other_srv_config);

        // Merge option defs. We need to do this next so we
        // pass these into subsequent merges so option instances
        // at each level can be created based on the merged
        // definitions.
        cfg_option_def_->merge((*other_srv_config.getCfgOptionDef()));

        // Merge options.
        cfg_option_->merge(cfg_option_def_, (*other_srv_config.getCfgOption()));

        if (!other_srv_config.getClientClassDictionary()->empty()) {
            // Client classes are complicated because they are ordered and may
            // depend on each other. Merging two lists of classes with preserving
            // the order would be very involved and could result in errors. Thus,
            // we simply replace the current list of classes with a new list.
            setClientClassDictionary(boost::make_shared
                                     <ClientClassDictionary>(*other_srv_config.getClientClassDictionary()));
        }

        if (CfgMgr::instance().getFamily() == AF_INET) {
            merge4(other_srv_config);
        } else {
            merge6(other_srv_config);
        }
    } catch (const std::bad_cast&) {
        isc_throw(InvalidOperation, "internal server error: must use derivation"
                  " of the SrvConfig as an argument of the call to"
                  " SrvConfig::merge()");
    }
}

void
SrvConfig::merge4(SrvConfig& other) {
    // Merge shared networks.
    cfg_shared_networks4_->merge(cfg_option_def_, *(other.getCfgSharedNetworks4()));

    // Merge subnets.
    cfg_subnets4_->merge(cfg_option_def_, getCfgSharedNetworks4(),
                         *(other.getCfgSubnets4()));

    /// @todo merge other parts of the configuration here.
}

void
SrvConfig::merge6(SrvConfig& other) {
    // Merge shared networks.
    cfg_shared_networks6_->merge(cfg_option_def_, *(other.getCfgSharedNetworks6()));

    // Merge subnets.
    cfg_subnets6_->merge(cfg_option_def_, getCfgSharedNetworks6(),
                         *(other.getCfgSubnets6()));

    /// @todo merge other parts of the configuration here.
}

void
SrvConfig::mergeGlobals(SrvConfig& other) {
    auto config_set = getConfiguredGlobals();
    // If the deprecated reservation-mode is found in database, overwrite other
    // reservation flags so there is no conflict when merging to new flags.
    if (other.getConfiguredGlobal(CfgGlobals::RESERVATION_MODE)) {
        config_set->set(CfgGlobals::RESERVATIONS_GLOBAL, ConstElementPtr());
        config_set->set(CfgGlobals::RESERVATIONS_IN_SUBNET, ConstElementPtr());
        config_set->set(CfgGlobals::RESERVATIONS_OUT_OF_POOL, ConstElementPtr());
    }
    // Iterate over the "other" globals, adding/overwriting them into
    // this config's list of globals.
    for (auto other_global : other.getConfiguredGlobals()->valuesMap()) {
        addConfiguredGlobal(other_global.first, other_global.second);
    }

    // Merge the reservation-mode to new reservation flags.
    BaseNetworkParser::moveReservationMode(config_set);

    // A handful of values are stored as members in SrvConfig. So we'll
    // iterate over the merged globals, setting appropriate members.
    for (auto merged_global : getConfiguredGlobals()->valuesMap()) {
        std::string name = merged_global.first;
        ConstElementPtr element = merged_global.second;
        try {
            if (name == "decline-probation-period") {
                setDeclinePeriod(element->intValue());
            } else if (name == "echo-client-id") {
                // echo-client-id is v4 only, but we'll let upstream
                // worry about that.
                setEchoClientId(element->boolValue());
            } else if (name == "dhcp4o6-port") {
                setDhcp4o6Port(element->intValue());
            } else if (name == "server-tag") {
                setServerTag(element->stringValue());
            } else if (name == "ip-reservations-unique") {
                setIPReservationsUnique(element->boolValue());
            } else if (name == "reservations-lookup-first") {
                setReservationsLookupFirst(element->boolValue());
            }
        } catch(const std::exception& ex) {
            isc_throw (BadValue, "Invalid value:" << element->str()
                       << " explicit global:" << name);
        }
    }
}

void
SrvConfig::removeStatistics() {
    // Removes statistics for v4 and v6 subnets
    getCfgSubnets4()->removeStatistics();

    getCfgSubnets6()->removeStatistics();
}

void
SrvConfig::updateStatistics() {
    // Update default sample limits.
    stats::StatsMgr& stats_mgr = stats::StatsMgr::instance();
    ConstElementPtr samples =
        getConfiguredGlobal("statistic-default-sample-count");
    uint32_t max_samples = 0;
    if (samples) {
        max_samples = samples->intValue();
        stats_mgr.setMaxSampleCountDefault(max_samples);
        if (max_samples != 0) {
            stats_mgr.setMaxSampleCountAll(max_samples);
        }
    }
    ConstElementPtr duration =
        getConfiguredGlobal("statistic-default-sample-age");
    if (duration) {
        int64_t time_duration = duration->intValue();
        auto max_age = std::chrono::seconds(time_duration);
        stats_mgr.setMaxSampleAgeDefault(max_age);
        if (max_samples == 0) {
            stats_mgr.setMaxSampleAgeAll(max_age);
        }
    }

    // Updating subnet statistics involves updating lease statistics, which
    // is done by the LeaseMgr.  Since servers with subnets, must have a
    // LeaseMgr, we do not bother updating subnet stats for servers without
    // a lease manager, such as D2. @todo We should probably examine why
    // "SrvConfig" is being used by D2.
    if (LeaseMgrFactory::haveInstance()) {
        // Updates  statistics for v4 and v6 subnets
        getCfgSubnets4()->updateStatistics();

        getCfgSubnets6()->updateStatistics();
    }
}

void
SrvConfig::applyDefaultsConfiguredGlobals(const SimpleDefaults& defaults) {
    // Code from SimpleParser::setDefaults
    // This is the position representing a default value. As the values
    // we're inserting here are not present in whatever the config file
    // came from, we need to make sure it's clearly labeled as default.
    const Element::Position pos("<default-value>", 0, 0);

    // Let's go over all parameters we have defaults for.
    for (auto def_value : defaults) {

        // Try if such a parameter is there. If it is, let's
        // skip it, because user knows best *cough*.
        ConstElementPtr x = getConfiguredGlobal(def_value.name_);
        if (x) {
            // There is such a value already, skip it.
            continue;
        }

        // There isn't such a value defined, let's create the default
        // value...
        switch (def_value.type_) {
        case Element::string: {
            x.reset(new StringElement(def_value.value_, pos));
            break;
        }
        case Element::integer: {
            try {
                int int_value = boost::lexical_cast<int>(def_value.value_);
                x.reset(new IntElement(int_value, pos));
            }
            catch (const std::exception& ex) {
                isc_throw(BadValue,
                          "Internal error. Integer value expected for: "
                          << def_value.name_ << ", value is: "
                          << def_value.value_ );
            }

            break;
        }
        case Element::boolean: {
            bool bool_value;
            if (def_value.value_ == std::string("true")) {
                bool_value = true;
            } else if (def_value.value_ == std::string("false")) {
                bool_value = false;
            } else {
                isc_throw(BadValue,
                          "Internal error. Boolean value for "
                          << def_value.name_ << " specified as "
                          << def_value.value_ << ", expected true or false");
            }
            x.reset(new BoolElement(bool_value, pos));
            break;
        }
        case Element::real: {
            double dbl_value = boost::lexical_cast<double>(def_value.value_);
            x.reset(new DoubleElement(dbl_value, pos));
            break;
        }
        default:
            // No default values for null, list or map
            isc_throw(BadValue,
                      "Internal error. Incorrect default value type for "
                      << def_value.name_);
        }
        addConfiguredGlobal(def_value.name_, x);
    }
}

void
SrvConfig::extractConfiguredGlobals(isc::data::ConstElementPtr config) {
    if (config->getType() != Element::map) {
        isc_throw(BadValue, "extractConfiguredGlobals must be given a map element");
    }

    const std::map<std::string, ConstElementPtr>& values = config->mapValue();
    for (auto value = values.begin(); value != values.end(); ++value) {
        if (value->second->getType() != Element::list &&
            value->second->getType() != Element::map) {
                addConfiguredGlobal(value->first, value->second);
        }
    }
}

void
SrvConfig::sanityChecksLifetime(const std::string& name) const {
    // Initialize as some compilers complain otherwise.
    uint32_t value = 0;
    ConstElementPtr has_value = getConfiguredGlobal(name);
    if (has_value) {
        value = has_value->intValue();
    }

    uint32_t min_value = 0;
    ConstElementPtr has_min = getConfiguredGlobal("min-" + name);
    if (has_min) {
        min_value = has_min->intValue();
    }

    uint32_t max_value = 0;
    ConstElementPtr has_max = getConfiguredGlobal("max-" + name);
    if (has_max) {
        max_value = has_max->intValue();
    }

    if (!has_value && !has_min && !has_max) {
        return;
    }
    if (has_value) {
        if (!has_min && !has_max) {
            // default only.
            return;
        } else if (!has_min) {
            // default and max.
            min_value = value;
        } else if (!has_max) {
            // default and min.
            max_value = value;
        }
    } else if (has_min) {
        if (!has_max) {
            // min only.
            return;
        } else {
            // min and max.
            isc_throw(BadValue, "have min-" << name << " and max-"
                      << name << " but no " << name << " (default)");
        }
    } else {
        // max only.
        return;
    }

    // Check that min <= max.
    if (min_value > max_value) {
        if (has_min && has_max) {
            isc_throw(BadValue, "the value of min-" << name << " ("
                      << min_value << ") is not less than max-" << name << " ("
                      << max_value << ")");
        } else if (has_min) {
            // Only min and default so min > default.
            isc_throw(BadValue, "the value of min-" << name << " ("
                      << min_value << ") is not less than (default) " << name
                      << " (" << value << ")");
        } else {
            // Only default and max so default > max.
            isc_throw(BadValue, "the value of (default) " << name
                      << " (" << value << ") is not less than max-" << name
                      << " (" << max_value << ")");
        }
    }

    // Check that value is between min and max.
    if ((value < min_value) || (value > max_value)) {
        isc_throw(BadValue, "the value of (default) " << name << " ("
                  << value << ") is not between min-" << name << " ("
                  << min_value << ") and max-" << name << " ("
                  << max_value << ")");
    }
}

void
SrvConfig::sanityChecksLifetime(const SrvConfig& target_config,
                                const std::string& name) const {
    // Three cases:
    //  - the external/source config has the parameter: use it.
    //  - only the target config has the parameter: use this one.
    //  - no config has the parameter.
    uint32_t value = 0;
    ConstElementPtr has_value = getConfiguredGlobal(name);
    bool new_value = true;
    if (!has_value) {
        has_value = target_config.getConfiguredGlobal(name);
        new_value = false;
    }
    if (has_value) {
        value = has_value->intValue();
    }

    uint32_t min_value = 0;
    ConstElementPtr has_min = getConfiguredGlobal("min-" + name);
    bool new_min = true;
    if (!has_min) {
        has_min = target_config.getConfiguredGlobal("min-" + name);
        new_min = false;
    }
    if (has_min) {
        min_value = has_min->intValue();
    }

    uint32_t max_value = 0;
    ConstElementPtr has_max = getConfiguredGlobal("max-" + name);
    bool new_max = true;
    if (!has_max) {
        has_max = target_config.getConfiguredGlobal("max-" + name);
        new_max = false;
    }
    if (has_max) {
        max_value = has_max->intValue();
    }

    if (!has_value && !has_min && !has_max) {
        return;
    }
    if (has_value) {
        if (!has_min && !has_max) {
            // default only.
            return;
        } else if (!has_min) {
            // default and max.
            min_value = value;
        } else if (!has_max) {
            // default and min.
            max_value = value;
        }
    } else if (has_min) {
        if (!has_max) {
            // min only.
            return;
        } else {
            // min and max.
            isc_throw(BadValue, "have min-" << name << " and max-"
                      << name << " but no " << name << " (default)");
        }
    } else {
        // max only.
        return;
    }

    // Check that min <= max.
    if (min_value > max_value) {
        if (has_min && has_max) {
            std::string from_min = (new_min ? "new" : "previous");
            std::string from_max = (new_max ? "new" : "previous");
            isc_throw(BadValue, "the value of " << from_min
                      << " min-" << name << " ("
                      << min_value << ") is not less than "
                      << from_max << " max-" << name
                      << " (" << max_value << ")");
        } else if (has_min) {
            // Only min and default so min > default.
            std::string from_min = (new_min ? "new" : "previous");
            std::string from_value = (new_value ? "new" : "previous");
            isc_throw(BadValue, "the value of " << from_min
                      << " min-" << name << " ("
                      << min_value << ") is not less than " << from_value
                      << " (default) " << name
                      << " (" << value << ")");
        } else {
            // Only default and max so default > max.
            std::string from_max = (new_max ? "new" : "previous");
            std::string from_value = (new_value ? "new" : "previous");
            isc_throw(BadValue, "the value of " << from_value
                      << " (default) " << name
                      << " (" << value << ") is not less than " << from_max
                      << " max-" << name << " (" << max_value << ")");
        }
    }

    // Check that value is between min and max.
    if ((value < min_value) || (value > max_value)) {
        std::string from_value = (new_value ? "new" : "previous");
        std::string from_min = (new_min ? "new" : "previous");
        std::string from_max = (new_max ? "new" : "previous");
        isc_throw(BadValue, "the value of " << from_value
                  <<" (default) " << name << " ("
                  << value << ") is not between " << from_min
                  << " min-" << name << " (" << min_value
                  << ") and " << from_max << " max-"
                  << name << " (" << max_value << ")");
    }
}

ElementPtr
SrvConfig::toElement() const {
    // Top level map
    ElementPtr result = Element::createMap();

    // Get family for the configuration manager
    uint16_t family = CfgMgr::instance().getFamily();

    // DhcpX global map initialized from configured globals
    ElementPtr dhcp = configured_globals_->toElement();

    auto loggers_info = getLoggingInfo();
    // Was in the Logging global map.
    if (!loggers_info.empty()) {
        // Set loggers list
        ElementPtr loggers = Element::createList();
        for (LoggingInfoStorage::const_iterator logger =
                loggers_info.cbegin();
             logger != loggers_info.cend(); ++logger) {
            loggers->add(logger->toElement());
        }
        dhcp->set("loggers", loggers);
    }

    // Set user-context
    contextToElement(dhcp);

    // Set data directory if DHCPv6 and specified.
    if (family == AF_INET6) {
        const util::Optional<std::string>& datadir =
            CfgMgr::instance().getDataDir();
        if (!datadir.unspecified()) {
            dhcp->set("data-directory", Element::create(datadir));
        }
    }

    // Set compatibility flags.
    ElementPtr compatibility = Element::createMap();
    if (getLenientOptionParsing()) {
        compatibility->set("lenient-option-parsing", Element::create(true));
    }
    if (getIgnoreServerIdentifier()) {
        compatibility->set("ignore-dhcp-server-identifier", Element::create(true));
    }
    if (getIgnoreRAILinkSelection()) {
        compatibility->set("ignore-rai-link-selection", Element::create(true));
    }
    if (getExcludeFirstLast24()) {
        compatibility->set("exclude-first-last-24", Element::create(true));
    }
    if (compatibility->size() > 0) {
        dhcp->set("compatibility", compatibility);
    }

    // Set decline-probation-period
    dhcp->set("decline-probation-period",
              Element::create(static_cast<long long>(decline_timer_)));
    // Set echo-client-id (DHCPv4)
    if (family == AF_INET) {
        dhcp->set("echo-client-id", Element::create(echo_v4_client_id_));
    }
    // Set dhcp4o6-port
    dhcp->set("dhcp4o6-port",
              Element::create(static_cast<int>(dhcp4o6_port_)));
    // Set dhcp-ddns
    dhcp->set("dhcp-ddns", d2_client_config_->toElement());
    // Set interfaces-config
    dhcp->set("interfaces-config", cfg_iface_->toElement());
    // Set option-def
    dhcp->set("option-def", cfg_option_def_->toElement());
    // Set option-data
    dhcp->set("option-data", cfg_option_->toElement());

    // Set subnets and shared networks.

    // We have two problems to solve:
    //   - a subnet is unparsed once:
    //       * if it is a plain subnet in the global subnet list
    //       * if it is a member of a shared network in the shared network
    //         subnet list
    //   - unparsed subnets must be kept to add host reservations in them.
    //     Of course this can be done only when subnets are unparsed.

    // The list of all unparsed subnets
    std::vector<ElementPtr> sn_list;

    if (family == AF_INET) {
        // Get plain subnets
        ElementPtr plain_subnets = Element::createList();
        const Subnet4Collection* subnets = cfg_subnets4_->getAll();
        for (Subnet4Collection::const_iterator subnet = subnets->cbegin();
             subnet != subnets->cend(); ++subnet) {
            // Skip subnets which are in a shared-network
            SharedNetwork4Ptr network;
            (*subnet)->getSharedNetwork(network);
            if (network) {
                continue;
            }
            ElementPtr subnet_cfg = (*subnet)->toElement();
            sn_list.push_back(subnet_cfg);
            plain_subnets->add(subnet_cfg);
        }
        dhcp->set("subnet4", plain_subnets);

        // Get shared networks
        ElementPtr shared_networks = cfg_shared_networks4_->toElement();
        dhcp->set("shared-networks", shared_networks);

        // Get subnets in shared network subnet lists
        const std::vector<ElementPtr> networks = shared_networks->listValue();
        for (auto network = networks.cbegin();
             network != networks.cend(); ++network) {
            const std::vector<ElementPtr> sh_list =
                (*network)->get("subnet4")->listValue();
            for (auto subnet = sh_list.cbegin();
                 subnet != sh_list.cend(); ++subnet) {
                sn_list.push_back(*subnet);
            }
        }

    } else {
        // Get plain subnets
        ElementPtr plain_subnets = Element::createList();
        const Subnet6Collection* subnets = cfg_subnets6_->getAll();
        for (Subnet6Collection::const_iterator subnet = subnets->cbegin();
             subnet != subnets->cend(); ++subnet) {
            // Skip subnets which are in a shared-network
            SharedNetwork6Ptr network;
            (*subnet)->getSharedNetwork(network);
            if (network) {
                continue;
            }
            ElementPtr subnet_cfg = (*subnet)->toElement();
            sn_list.push_back(subnet_cfg);
            plain_subnets->add(subnet_cfg);
        }
        dhcp->set("subnet6", plain_subnets);

        // Get shared networks
        ElementPtr shared_networks = cfg_shared_networks6_->toElement();
        dhcp->set("shared-networks", shared_networks);

        // Get subnets in shared network subnet lists
        const std::vector<ElementPtr> networks = shared_networks->listValue();
        for (auto network = networks.cbegin();
             network != networks.cend(); ++network) {
            const std::vector<ElementPtr> sh_list =
                (*network)->get("subnet6")->listValue();
            for (auto subnet = sh_list.cbegin();
                 subnet != sh_list.cend(); ++subnet) {
                sn_list.push_back(*subnet);
            }
        }
    }

    // Host reservations
    CfgHostsList resv_list;
    resv_list.internalize(cfg_hosts_->toElement());

    // Insert global reservations
    ConstElementPtr global_resvs = resv_list.get(SUBNET_ID_GLOBAL);
    if (global_resvs->size() > 0) {
        dhcp->set("reservations", global_resvs);
    }

    // Insert subnet reservations
    for (std::vector<ElementPtr>::const_iterator subnet = sn_list.cbegin();
         subnet != sn_list.cend(); ++subnet) {
        ConstElementPtr id = (*subnet)->get("id");
        if (isNull(id)) {
            isc_throw(ToElementError, "subnet has no id");
        }
        SubnetID subnet_id = id->intValue();
        ConstElementPtr resvs = resv_list.get(subnet_id);
        (*subnet)->set("reservations", resvs);
    }

    // Set expired-leases-processing
    ConstElementPtr expired = cfg_expiration_->toElement();
    dhcp->set("expired-leases-processing", expired);
    if (family == AF_INET6) {
        // Set server-id (DHCPv6)
        dhcp->set("server-id", cfg_duid_->toElement());

        // Set relay-supplied-options (DHCPv6)
        dhcp->set("relay-supplied-options", cfg_rsoo_->toElement());
    }
    // Set lease-database
    CfgLeaseDbAccess lease_db(*cfg_db_access_);
    dhcp->set("lease-database", lease_db.toElement());
    // Set hosts-databases
    CfgHostDbAccess host_db(*cfg_db_access_);
    ConstElementPtr hosts_databases = host_db.toElement();
    if (hosts_databases->size() > 0) {
        dhcp->set("hosts-databases", hosts_databases);
    }
    // Set host-reservation-identifiers
    ConstElementPtr host_ids;
    if (family == AF_INET) {
        host_ids = cfg_host_operations4_->toElement();
    } else {
        host_ids = cfg_host_operations6_->toElement();
    }
    dhcp->set("host-reservation-identifiers", host_ids);
    // Set mac-sources (DHCPv6)
    if (family == AF_INET6) {
        dhcp->set("mac-sources", cfg_mac_source_.toElement());
    }
    // Set control-socket (skip if null as empty is not legal)
    if (!isNull(control_socket_)) {
        dhcp->set("control-socket", UserContext::toElement(control_socket_));
    }
    // Set client-classes
    ConstElementPtr client_classes = class_dictionary_->toElement();
    /// @todo accept empty list
    if (!client_classes->empty()) {
        dhcp->set("client-classes", client_classes);
    }
    // Set hooks-libraries
    ConstElementPtr hooks_libs = hooks_config_.toElement();
    dhcp->set("hooks-libraries", hooks_libs);
    // Set DhcpX
    result->set(family == AF_INET ? "Dhcp4" : "Dhcp6", dhcp);

    ConstElementPtr cfg_consist = cfg_consist_->toElement();
    dhcp->set("sanity-checks", cfg_consist);

    // Set config-control (if it exists)
    ConstConfigControlInfoPtr info = getConfigControlInfo();
    if (info) {
        ConstElementPtr info_elem = info->toElement();
        dhcp->set("config-control", info_elem);
    }

    // Set dhcp-packet-control (if it exists)
    data::ConstElementPtr dhcp_queue_control = getDHCPQueueControl();
    if (dhcp_queue_control) {
        dhcp->set("dhcp-queue-control", dhcp_queue_control);
    }

    // Set multi-threading (if it exists)
    data::ConstElementPtr dhcp_multi_threading = getDHCPMultiThreading();
    if (dhcp_multi_threading) {
        dhcp->set("multi-threading", dhcp_multi_threading);
    }

    return (result);
}

DdnsParamsPtr
SrvConfig::getDdnsParams(const Subnet4Ptr& subnet) const {
    return (DdnsParamsPtr(new DdnsParams(subnet,
                                         getD2ClientConfig()->getEnableUpdates())));
}

DdnsParamsPtr
SrvConfig::getDdnsParams(const Subnet6Ptr& subnet) const {
   return(DdnsParamsPtr(new DdnsParams(subnet,
                                       getD2ClientConfig()->getEnableUpdates())));
}

void
SrvConfig::moveDdnsParams(isc::data::ElementPtr srv_elem) {
    if (!srv_elem || (srv_elem->getType() != Element::map)) {
        isc_throw(BadValue, "moveDdnsParams server config must be given a map element");
    }

    if (!srv_elem->contains("dhcp-ddns")) {
        /* nothing to do */
        return;
    }

    ElementPtr d2_elem = boost::const_pointer_cast<Element>(srv_elem->get("dhcp-ddns"));
    if (!d2_elem || (d2_elem->getType() != Element::map)) {
        isc_throw(BadValue, "moveDdnsParams dhcp-ddns is not a map");
    }

    struct Param {
        std::string from_name;
        std::string to_name;
    };

    std::vector<Param> params {
        { "override-no-update", "ddns-override-no-update" },
        { "override-client-update", "ddns-override-client-update" },
        { "replace-client-name", "ddns-replace-client-name" },
        { "generated-prefix", "ddns-generated-prefix" },
        { "qualifying-suffix", "ddns-qualifying-suffix" },
        { "hostname-char-set", "hostname-char-set" },
        { "hostname-char-replacement", "hostname-char-replacement" }
    };

    for (auto param : params) {
        if (d2_elem->contains(param.from_name)) {
            if (!srv_elem->contains(param.to_name)) {
                // No global value for it already, so let's add it.
                srv_elem->set(param.to_name, d2_elem->get(param.from_name));
                LOG_INFO(dhcpsrv_logger, DHCPSRV_CFGMGR_DDNS_PARAMETER_MOVED)
                        .arg(param.from_name).arg(param.to_name);
            } else {
                // Already a global value, we'll use it and ignore this one.
                LOG_INFO(dhcpsrv_logger, DHCPSRV_CFGMGR_DDNS_PARAMETER_IGNORED)
                        .arg(param.from_name).arg(param.to_name);
            }

            // Now remove it from d2_data, so D2ClientCfg won't complain.
            d2_elem->remove(param.from_name);
        }
    }
}

void
SrvConfig::setIPReservationsUnique(const bool unique) {
    if (!getCfgDbAccess()->getIPReservationsUnique() && unique) {
        LOG_WARN(dhcpsrv_logger, DHCPSRV_CFGMGR_IP_RESERVATIONS_UNIQUE_DUPLICATES_POSSIBLE);
    }
    getCfgHosts()->setIPReservationsUnique(unique);
    getCfgDbAccess()->setIPReservationsUnique(unique);
}

void
SrvConfig::configureLowerLevelLibraries() const {
    Option::lenient_parsing_ = lenient_option_parsing_;
}

bool
DdnsParams::getEnableUpdates() const {
    if (!subnet_) {
        return (false);
    }

    return (d2_client_enabled_ && subnet_->getDdnsSendUpdates().get());
}

bool
DdnsParams::getOverrideNoUpdate() const {
    if (!subnet_) {
        return (false);
    }

    return (subnet_->getDdnsOverrideNoUpdate().get());
}

bool DdnsParams::getOverrideClientUpdate() const {
    if (!subnet_) {
        return (false);
    }

    return (subnet_->getDdnsOverrideClientUpdate().get());
}

D2ClientConfig::ReplaceClientNameMode
DdnsParams::getReplaceClientNameMode() const {
    if (!subnet_) {
        return (D2ClientConfig::RCM_NEVER);
    }

    return (subnet_->getDdnsReplaceClientNameMode().get());
}

std::string
DdnsParams::getGeneratedPrefix() const {
    if (!subnet_) {
        return ("");
    }

    return (subnet_->getDdnsGeneratedPrefix().get());
}

std::string
DdnsParams::getQualifyingSuffix() const {
    if (!subnet_) {
        return ("");
    }

    return (subnet_->getDdnsQualifyingSuffix().get());
}

std::string
DdnsParams::getHostnameCharSet() const {
    if (!subnet_) {
        return ("");
    }

    return (subnet_->getHostnameCharSet().get());
}

std::string
DdnsParams::getHostnameCharReplacement() const {
    if (!subnet_) {
        return ("");
    }

    return (subnet_->getHostnameCharReplacement().get());
}

util::str::StringSanitizerPtr
DdnsParams::getHostnameSanitizer() const {
    util::str::StringSanitizerPtr sanitizer;
    if (subnet_) {
        std::string char_set = getHostnameCharSet();
        if (!char_set.empty()) {
            try {
                sanitizer.reset(new util::str::StringSanitizer(char_set,
                                                               getHostnameCharReplacement()));
            } catch (const std::exception& ex) {
                isc_throw(BadValue, "hostname_char_set_: '" << char_set <<
                                    "' is not a valid regular expression");
            }
        }
    }

    return (sanitizer);
}

bool
DdnsParams::getUpdateOnRenew() const {
    if (!subnet_) {
        return (false);
    }

    return (subnet_->getDdnsUpdateOnRenew().get());
}

bool
DdnsParams::getUseConflictResolution() const {
    if (!subnet_) {
        return (true);
    }

    return (subnet_->getDdnsUseConflictResolution().get());
}

util::Optional<double>
DdnsParams::getTtlPercent() const {
    if (!subnet_) {
        return (util::Optional<double>());
    }

    return (subnet_->getDdnsTtlPercent());
}

} // namespace dhcp
} // namespace isc
