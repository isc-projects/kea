// Copyright (C) 2020-2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <host_cache_parsers.h>
#include <cc/dhcp_config_error.h>
#include <dhcpsrv/parsers/option_data_parser.h>
#include <boost/pointer_cast.hpp>
#include <boost/lexical_cast.hpp>

using namespace isc::asiolink;
using namespace isc::data;
using namespace isc::dhcp;
using namespace std;

namespace isc {
namespace host_cache {

/// @brief Defaults for Host Cache configuration.
const SimpleDefaults HCConfigParser::HOST_CACHE_DEFAULTS = {
    { "maximum",       Element::integer, "0" }
};

/// @todo: Remove this duplicated code (see trac #5578)
void
HCConfigParser::parse(HostCache& hcref, const ConstElementPtr& config) {
    ElementPtr mutable_cfg;
    if (config) {
        mutable_cfg = boost::const_pointer_cast<Element>(config);
    } else {
        mutable_cfg = Element::createMap();
    }

    if (!mutable_cfg || (mutable_cfg->getType() != Element::map)) {
        isc_throw(ConfigError, "Host Cache config is not a map");
    }

    try {
        setDefaults(mutable_cfg, HOST_CACHE_DEFAULTS);

        int64_t maximum = getInteger(mutable_cfg, "maximum");
        if (maximum < 0) {
            isc_throw(ConfigError, "Host Cache maximum parameter is negative");
        }
        if (maximum > MAXIMUM) {
            isc_throw(ConfigError, "Host Cache maximum parameter is too large "
                      << "(" << maximum << " > " << MAXIMUM << ")");
        }
        hcref.setMaximum(static_cast<size_t>(maximum));
    } catch (const ConfigError&) {
        throw;
    } catch (const exception& ex) {
        isc_throw(ConfigError, ex.what());
    }
}

HostPtr
HCEntryParser::parse(const ConstElementPtr& entry) {
    try {
        // Scan critical parameters
        string identifier;
        string identifier_name;
        string hostname;
        ConstElementPtr user_context;
        auto& map = entry->mapValue();
        for (auto const& element : map) {
            if ((element.first == "hw-address") ||
                (element.first == "duid") ||
                (element.first == "circuit-id") ||
                (element.first == "client-id") ||
                (element.first == "flex-id")) {
                if (!identifier_name.empty()) {
                    isc_throw(ConfigError, "the '" << element.first
                              << "' and '" << identifier_name
                              << "' are mutually exclusive");
                }
                identifier = element.second->stringValue();
                identifier_name = element.first;
                continue;
            }

            if (element.first == "hostname") {
                hostname = element.second->stringValue();
                continue;
            }

            if (element.first == "user-context") {
                user_context = element.second;
                continue;
            }
        }

        // Host identifier is a must.
        if (identifier_name.empty()) {
            isc_throw(ConfigError, "no identifier");
        }

        // Create a host object from the basic parameters we already parsed.
        HostPtr host;
        host.reset(new Host(identifier, identifier_name,
                            SubnetID(SUBNET_ID_UNUSED),
                            SubnetID(SUBNET_ID_UNUSED),
                            IOAddress("0.0.0.0"), hostname));
        // Add user context
        if (user_context) {
            host->setContext(user_context);
        }

        // Scan other parameters
        for (auto const& element : map) {
            if ((element.first == "hw-address") ||
                (element.first == "duid") ||
                (element.first == "circuit-id") ||
                (element.first == "client-id") ||
                (element.first == "flex-id") ||
                (element.first == "hostname") ||
                (element.first == "user-context")) {
                continue;
            }

            if (element.first == "subnet-id4") {
                host->setIPv4SubnetID(element.second->intValue());
                continue;
            }

            if (element.first == "subnet-id6") {
                host->setIPv6SubnetID(element.second->intValue());
                continue;
            }

            if (element.first == "option-data4") {
                CfgOptionPtr cfg_option = host->getCfgOption4();
                OptionDataListParser parser(AF_INET);
                parser.parse(cfg_option, element.second);
                continue;
            }

            if (element.first == "option-data6") {
                CfgOptionPtr cfg_option = host->getCfgOption6();
                OptionDataListParser parser(AF_INET6);
                parser.parse(cfg_option, element.second);
                continue;
            }

            if (element.first == "ip-address") {
                host->setIPv4Reservation(IOAddress(element.second->stringValue()));
                continue;
            }

            if (element.first == "next-server") {
                host->setNextServer(IOAddress(element.second->stringValue()));
                continue;
            }

            if (element.first == "server-hostname") {
                host->setServerHostname(element.second->stringValue());
                continue;
            }

            if (element.first == "boot-file-name") {
                host->setBootFileName(element.second->stringValue());
                continue;
            }

            if (element.first == "client-classes4") {
                auto const& classes = element.second->listValue();
                for (auto const& cclass : classes) {
                    host->addClientClass4(cclass->stringValue());
                }
                continue;
            }

            if (element.first == "client-classes6") {
                auto const& classes = element.second->listValue();
                for (auto const& cclass : classes) {
                    host->addClientClass6(cclass->stringValue());
                }
                continue;
            }

            if (element.first == "ip-addresses") {
                auto const& addresses = element.second->listValue();
                for (auto const& addr : addresses) {
                  string address = addr->stringValue();
                  host->addReservation(IPv6Resrv(IPv6Resrv::TYPE_NA,
                                                   IOAddress(address),
                                                   128));
                }
                continue;
            }

            if (element.first == "prefixes") {
                auto& prefixes = element.second->listValue();
                for (auto const& pref : prefixes) {
                    string prefix = pref->stringValue();
                    uint8_t len = 128;
                    size_t pos  = prefix.find('/');
                    if (pos == string::npos) {
                        isc_throw(ConfigError, "bad prefix (no /)");
                    } else if (pos > prefix.length() - 1) {
                        isc_throw(ConfigError, "bad prefix (end /)");
                    }
                    try {
                        string preflen = prefix.substr(pos + 1);
                        len = boost::lexical_cast<unsigned>(preflen);
                    } catch (const boost::bad_lexical_cast&) {
                        isc_throw(ConfigError, "bad prefix length");
                    }
                    prefix.erase(pos);

                    host->addReservation(IPv6Resrv(IPv6Resrv::TYPE_PD,
                                                   IOAddress(prefix),
                                                   len));
                }
                continue;
            }

            if (element.first == "host-id") {
                int64_t hid = element.second->intValue();
                host->setHostId(static_cast<uint64_t>(hid));
                continue;
            }

            if (element.first == "negative") {
                host->setNegative(element.second->boolValue());
                continue;
            }

            isc_throw(ConfigError, "unknown parameter: " << element.first);
        }
        return (host);

    } catch (const ConfigError&) {
        throw;
    } catch (const exception& ex) {
        isc_throw(ConfigError, ex.what());
    }
}

} // end of namespace isc::host_cache
} // end of namespace isc
