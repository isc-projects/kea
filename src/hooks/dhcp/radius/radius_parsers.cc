// Copyright (C) 2018-2026 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <radius_parsers.h>
#include <radius_log.h>
#include <cc/data.h>
#include <cc/default_credentials.h>
#include <dhcpsrv/cfgmgr.h>
#include <eval/eval_context.h>
#include <util/encode/encode.h>

#include <limits>
#include <string>
#include <cstdlib>
#include <cstring>
#include <sstream>

using namespace std;
using namespace isc;
using namespace isc::asiolink;
using namespace isc::data;
using namespace isc::dhcp;
using namespace isc::util;

namespace isc {
namespace radius {

/// @brief Keywords for Radius configuration.
const set<string>
RadiusConfigParser::RADIUS_KEYWORDS = {
    "access", "accounting", "common-tls", // services
    "bindaddr", "canonical-mac-address", "client-id-pop0",
    "client-id-printable", "deadtime", "dictionary",
    "extract-duid", "identifier-type4", "identifier-type6",
    "nas-ports", "protocol",
    "reselect-subnet-address", "reselect-subnet-pool",
    "retries", "session-history", "thread-pool-size", "timeout",
    "comment" // not saved for toElement
};

/// @brief Defaults for Radius configuration.
const SimpleDefaults RadiusConfigParser::RADIUS_DEFAULTS = {
    { "bindaddr",                 Element::string,  "*" },
    { "canonical-mac-address",    Element::boolean, "false" },
    { "client-id-pop0",           Element::boolean, "false" },
    { "client-id-printable",      Element::boolean, "false" },
    { "deadtime",                 Element::integer, "0" },
    { "dictionary",               Element::string,  DICTIONARY },
    { "extract-duid",             Element::boolean, "true" },
    { "identifier-type4",         Element::string,  "client-id" },
    { "identifier-type6",         Element::string,  "duid" },
    { "protocol",                 Element::string,  "UDP" },
    { "reselect-subnet-address",  Element::boolean, "false" },
    { "reselect-subnet-pool",     Element::boolean, "false" },
    { "retries",                  Element::integer, "3" },
    { "session-history",          Element::string,  "" },
    { "thread-pool-size",         Element::integer, "0" },
    { "timeout",                  Element::integer, "10" }
};

/// @brief Needed standard attributes.
const AttrDefList RadiusConfigParser::USED_STANDARD_ATTR_DEFS = {
    { PW_USER_NAME,             "User-Name",             PW_TYPE_STRING },
    { PW_USER_PASSWORD,         "User-Password",         PW_TYPE_STRING },
    { PW_NAS_IP_ADDRESS,        "NAS-IP-Address",        PW_TYPE_IPADDR },
    { PW_NAS_PORT,              "NAS-Port",              PW_TYPE_INTEGER },
    { PW_SERVICE_TYPE,          "Service-Type",          PW_TYPE_INTEGER },
    { PW_FRAMED_IP_ADDRESS,     "Framed-IP-Address",     PW_TYPE_IPADDR },
    { PW_REPLY_MESSAGE,         "Reply-Message",         PW_TYPE_STRING },
    { PW_CLASS,                 "Class",                 PW_TYPE_STRING },
    { PW_VENDOR_SPECIFIC,       "Vendor-Specific",       PW_TYPE_VSA },
    { PW_CALLING_STATION_ID,    "Calling-Station-Id",    PW_TYPE_STRING },
    { PW_ACCT_STATUS_TYPE,      "Acct-Status-Type",      PW_TYPE_INTEGER },
    { PW_ACCT_DELAY_TIME,       "Acct-Delay-Time",       PW_TYPE_INTEGER },
    { PW_ACCT_SESSION_ID,       "Acct-Session-Id",       PW_TYPE_STRING },
    { PW_MESSAGE_AUTHENTICATOR, "Message-Authenticator", PW_TYPE_STRING },
    { PW_FRAMED_POOL,           "Framed-Pool",           PW_TYPE_STRING },
    { PW_NAS_IPV6_ADDRESS,      "NAS-IPv6-Address",      PW_TYPE_IPV6ADDR },
    { PW_DELEGATED_IPV6_PREFIX, "Delegated-IPv6-Prefix", PW_TYPE_IPV6PREFIX },
    { PW_FRAMED_IPV6_ADDRESS,   "Framed-IPv6-Address",   PW_TYPE_IPV6ADDR }
};

/// @brief Defaults for Radius attribute configuration.
const SimpleDefaults RadiusAttributeParser::ATTRIBUTE_DEFAULTS = {
    { "data",   Element::string, "" },
    { "expr",   Element::string, "" },
    { "raw",    Element::string, "" },
    { "vendor", Element::string, "" }
};

void
RadiusConfigParser::parse(ElementPtr& config) {
    try {
        RadiusImpl& riref = RadiusImpl::instance();

        // Set defaults.
        setDefaults(config, RADIUS_DEFAULTS);

        // dictionary (do it first).
        const ConstElementPtr& dictionary = config->get("dictionary");
        riref.dictionary_ = dictionary->stringValue();

        // Read the dictionary
        if (!AttrDefs::instance().getByType(1)) {
            uint32_t vendor = 0;
            try {
                AttrDefs::instance().readDictionary(riref.dictionary_, vendor);
            } catch (const exception& ex) {
                isc_throw(BadValue, "can't read radius dictionary: "
                          << ex.what());
            }
            if (vendor != 0) {
                isc_throw(BadValue, "vendor definitions were not properly "
                          << "closed: vendor " << vendor << " is still open");
            }
        }

        // Check it.
        AttrDefs::instance().checkStandardDefs(USED_STANDARD_ATTR_DEFS);

        // Protocol.
        const ConstElementPtr& protocol = config->get("protocol");
        string proto = protocol->stringValue();
        if (proto == "UDP") {
            riref.proto_ = PW_PROTO_UDP;
        } else if (proto == "TCP") {
            riref.proto_ = PW_PROTO_TCP;
        } else if (proto == "TLS") {
            riref.proto_ = PW_PROTO_TLS;
        } else {
            isc_throw(BadValue, "unknown protocol " << proto);
        }
        if (riref.proto_ == PW_PROTO_TCP) {
            isc_throw(NotImplemented, "protocol 'TCP' is not supported");
        }

        // bindaddr.
        const ConstElementPtr& bindaddr = config->get("bindaddr");
        riref.bindaddr_ = bindaddr->stringValue();

        // canonical-mac-address.
        const ConstElementPtr& canonical = config->get("canonical-mac-address");
        riref.canonical_mac_address_ = canonical->boolValue();

        // client-id-pop0.
        const ConstElementPtr& pop0 = config->get("client-id-pop0");
        riref.clientid_pop0_ = pop0->boolValue();

        // client-id-printable.
        const ConstElementPtr& try_printable = config->get("client-id-printable");
        riref.clientid_printable_ = try_printable->boolValue();

        // deadtime.
        const ConstElementPtr& deadtime = config->get("deadtime");
        int64_t deadtime64 = deadtime->intValue();
        if ((deadtime64 < 0) ||
            (deadtime64 > numeric_limits<unsigned>::max())) {
            isc_throw(OutOfRange, "bad deadtime " << deadtime64
                      << " not in [0.."
                      << numeric_limits<unsigned>::max() << "]");
        }
        riref.deadtime_ = static_cast<unsigned>(deadtime64);

        // extract-duid.
        const ConstElementPtr& rfc4361 = config->get("extract-duid");
        riref.extract_duid_ = rfc4361->boolValue();

        // identifier-type4.
        const ConstElementPtr& id_type4 = config->get("identifier-type4");
        riref.id_type4_ = Host::getIdentifierType(id_type4->stringValue());

        // identifier-type6.
        const ConstElementPtr& id_type6 = config->get("identifier-type6");
        riref.id_type6_ = Host::getIdentifierType(id_type6->stringValue());

        // reselect-subnet-address.
        const ConstElementPtr& resel_addr =
            config->get("reselect-subnet-address");
        riref.reselect_subnet_address_ = resel_addr->boolValue();

        // reselect-subnet-pool.
        const ConstElementPtr& resel_pool =
            config->get("reselect-subnet-pool");
        riref.reselect_subnet_pool_ = resel_pool->boolValue();

        // retries.
        const ConstElementPtr& retries = config->get("retries");
        int64_t retries64 = retries->intValue();
        if ((retries64 < 0) ||
            (retries64 > numeric_limits<unsigned>::max())) {
            isc_throw(OutOfRange, "bad retries " << retries64
                      << " not in [0.."
                      << numeric_limits<unsigned>::max() << "]");
        }
        riref.retries_ = static_cast<unsigned>(retries64);

        // session-history.
        const ConstElementPtr& session_history = config->get("session-history");
        riref.session_history_filename_ = session_history->stringValue();

        // thread-pool-size.
        const ConstElementPtr& thread_pool_size = config->get("thread-pool-size");
        riref.thread_pool_size_ = thread_pool_size->intValue();

        // timeout.
        const ConstElementPtr& timeout = config->get("timeout");
        int64_t timeout64 = timeout->intValue();
        if ((timeout64 < 0) ||
            (timeout64 > numeric_limits<long>::max() / 1000)) {
            isc_throw(OutOfRange, "bad timeout " << timeout64
                      << " not in [0.."
                      << (numeric_limits<long>::max() / 1000) << "]");
        }
        riref.timeout_ = static_cast<unsigned>(timeout64);

        // Common TLS service.
        const ConstElementPtr& common = config->get("common-tls");
        if (common) {
            if (riref.proto_ != PW_PROTO_TLS) {
                isc_throw(BadValue, "'common-tls' service can't be configured "
                          << "when protocol is not 'TLS'");
            }
            RadiusServiceParser parser;
            parser.parse(riref.common_, common);
            parser.checkAttributes(riref.common_);
        }

        // Access service.
        const ConstElementPtr& access = config->get("access");
        if (access) {
            RadiusServiceParser parser;
            parser.parse(riref.auth_, access);
            parser.checkAttributes(riref.auth_);
        }

        // Accounting service.
        const ConstElementPtr& accounting = config->get("accounting");
        if (accounting) {
            RadiusServiceParser parser;
            parser.parse(riref.acct_, accounting);
            parser.checkAttributes(riref.acct_);
        }

        // nas-ports (last so we can return when it is not present.
        const ConstElementPtr& nas_ports = config->get("nas-ports");
        if (!nas_ports) {
            return;
        }
        for (auto const& entry : nas_ports->listValue()) {
            // port is mandatory.
            const ConstElementPtr& port = entry->get("port");
            if (!port) {
                isc_throw(BadValue, "missing port in nas-ports entry: "
                          << entry->str());
            }

            // By subnet-id.
            const ConstElementPtr& id = entry->get("subnet-id");
            if (id) {
                riref.remap_[id->intValue()] = port->intValue();
                continue;
            }

            // By subnet-prefix (to be resolved into an ID).
            const ConstElementPtr& prefix = entry->get("subnet-prefix");
            if (prefix) {
                if (CfgMgr::instance().getFamily() == AF_INET) {
                    auto subnet = CfgMgr::instance().getStagingCfg()->
                        getCfgSubnets4()->getByPrefix(prefix->stringValue());
                    if (!subnet) {
                        isc_throw(BadValue, "can't find subnet for "
                                  << entry->str());
                    }
                    riref.remap_[subnet->getID()] = port->intValue();
                    continue;
                } else {
                    auto subnet = CfgMgr::instance().getStagingCfg()->
                        getCfgSubnets6()->getByPrefix(prefix->stringValue());
                    if (!subnet) {
                        isc_throw(BadValue, "can't find subnet for "
                                  << entry->str());
                    }
                    riref.remap_[subnet->getID()] = port->intValue();
                    continue;
                }
            }

            // By shared-network-name (to be resolved, add all subnets).
            const ConstElementPtr& name = entry->get("shared-network-name");
            if (name) {
                if (CfgMgr::instance().getFamily() == AF_INET) {
                    auto network = CfgMgr::instance().getStagingCfg()->
                        getCfgSharedNetworks4()->getByName(name->stringValue());
                    if (!network) {
                        isc_throw(BadValue, "can't find shared network for "
                                  << entry->str());
                    }
                    for (auto const& subnet : *network->getAllSubnets()) {
                        riref.remap_[subnet->getID()] = port->intValue();
                    }
                    continue;
                } else {
                    auto network = CfgMgr::instance().getStagingCfg()->
                        getCfgSharedNetworks6()->getByName(name->stringValue());
                    if (!network) {
                        isc_throw(BadValue, "can't find shared network for "
                                  << entry->str());
                    }
                    for (auto const& subnet : *network->getAllSubnets()) {
                        riref.remap_[subnet->getID()] = port->intValue();
                    }
                    continue;
                }
            }

            // Unknown selector.
            if (entry->size() > 1) {
                isc_throw(BadValue, "unknown selector in " << entry->str());
            }

            // Default is in subnet 0 (SUBNET_ID_DEFAULT).
            riref.remap_[SUBNET_ID_DEFAULT] = port->intValue();
        }

    } catch (const ConfigError&) {
        throw;
    } catch (const std::exception& ex) {
        isc_throw(ConfigError, ex.what());
    }
}

/// @brief Keywords for service configuration.
const set<string>
RadiusServiceParser::SERVICE_KEYWORDS = {
    "enabled", "servers", "attributes", "peer-updates", "max-pending-requests",
    "idle-timer-interval"
};

void
RadiusServiceParser::parse(const RadiusServicePtr& service,
                           const ConstElementPtr& srv_cfg) {
    try {
        RadiusImpl& riref = RadiusImpl::instance();

        // map type.
        if (srv_cfg->getType() != Element::map) {
            isc_throw(BadValue, "expected service to be map, but got "
                      << Element::typeToName(srv_cfg->getType())
                      << " instead");
        }

        // keywords.
        const set<string> keywords = RadiusServiceParser::SERVICE_KEYWORDS;
        for (auto const& entry : srv_cfg->mapValue()) {
            if (keywords.count(entry.first) == 0) {
                isc_throw(BadValue, "unknown service parameter: "
                          << entry.first);
            }
        }

        // Enabled.
        const ConstElementPtr& enabled = srv_cfg->get("enabled");
        if (enabled) {
            if (riref.proto_ != PW_PROTO_TLS) {
                isc_throw(BadValue, "'enabled' makes sense only with TLS");
            }
            if (enabled->getType() != Element::boolean) {
                isc_throw(BadValue, "expected enabled to be boolean, "
                          << "but got "
                          << Element::typeToName(enabled->getType())
                          << " instead");
            }
            if (service->name_ == "common-tls") {
                isc_throw(BadValue, "can't set enabled in 'common-tls'");
            }
            service->enabled_ = enabled->boolValue();
        } else {
            if ((riref.proto_ == PW_PROTO_TLS) &&
                (service->name_ != "common-tls")) {
                service->enabled_ = true;
            }
        }

        // servers.
        const ConstElementPtr& servers = srv_cfg->get("servers");
        if (servers) {
            if ((riref.proto_ == PW_PROTO_TLS) &&
                (service->name_ != "common-tls")) {
                isc_throw(BadValue, "can't have servers entry in '"
                          << service->name_ << "' with TLS");
            }
            RadiusServerListParser parser;
            parser.parse(service, servers);
            if (!service->servers_.empty()) {
                service->enabled_ = true;
            }
        }

        // attributes.
        const ConstElementPtr& attributes = srv_cfg->get("attributes");
        if (attributes) {
            if (service->name_ == "common-tls") {
                isc_throw(BadValue, "can't define attributes in 'common-tls'");
            }
            RadiusAttributeListParser parser;
            parser.parse(service, attributes);
        }

        // peer-updates.
        const ConstElementPtr& peer_updates = srv_cfg->get("peer-updates");
        if (peer_updates) {
            if (service->name_ != "accounting") {
                isc_throw(BadValue, "peer-updates configured for the "
                          << service->name_ << " service, but it is "
                          << "only supported for the accounting service");
            }
            if (peer_updates->getType() != Element::boolean) {
                isc_throw(BadValue, "expected peer-updates to be boolean, "
                          << "but got "
                          << Element::typeToName(peer_updates->getType())
                          << " instead");
            }
            service->peer_updates_ = peer_updates->boolValue();
        }

        // max-pending-requests.
        const ConstElementPtr& max_pending_requests =
            srv_cfg->get("max-pending-requests");
        if (max_pending_requests) {
            if (service->name_ != "access") {
                isc_throw(BadValue, "max-pending-requests configured for the "
                          << service->name_ << " service, but it is only "
                          << "supported for the access service");
            }
            if (max_pending_requests->getType() != Element::integer) {
                isc_throw(BadValue, "expected max-pending-requests to be "
                          << "integer, but got "
                          << Element::typeToName(max_pending_requests->getType())
                          << " instead");
            }
            if (max_pending_requests->intValue() < 0) {
                isc_throw(BadValue, "expected max-pending-requests to be "
                          << "positive, but got "
                          << max_pending_requests->intValue()
                          << " instead");
            }
            service->max_pending_requests_ = max_pending_requests->intValue();
        }

        // idle-timer-interval.
        const ConstElementPtr& idle_timer_interval =
            srv_cfg->get("idle-timer-interval");
        if (idle_timer_interval) {
            if ((riref.proto_ == PW_PROTO_TLS) &&
                (service->name_ != "common-tls")) {
                isc_throw(BadValue, "can't have idle-timer-interval entry in '"
                          << service->name_ << "' with TLS");
            }
            if (idle_timer_interval->getType() != Element::integer) {
                isc_throw(BadValue, "expected idle-timer-interval to be "
                          << "integer, but got "
                          << Element::typeToName(idle_timer_interval->getType())
                          << " instead");
            }
            if (idle_timer_interval->intValue() < 0) {
                isc_throw(BadValue, "expected idle-timer-interval to be "
                          << "positive, but got "
                          << idle_timer_interval->intValue()
                          << " instead");
            }
            service->idle_timer_interval_ = idle_timer_interval->intValue();
        }
    } catch (const std::exception& ex) {
        isc_throw(ConfigError, ex.what() << " (parsing "
                  << service->name_ << ")");
    }
}

void
RadiusServiceParser::checkAttributes(const RadiusServicePtr& service) {
    if (!service->enabled_) {
        return;
    }

    const CfgAttributes& cfg_attrs = service->attributes_;
    const Attributes& attrs = cfg_attrs.getAll();
    if (service->name_ == "access") {
        // Nothing yet.
    } else if (service->name_ == "accounting") {
        // Expressions have no associated attributes.
        if (cfg_attrs.size() > attrs.size()) {
            isc_throw(ConfigError,
                      "Expressions are not yet supported in accounting");
        }
    }
}

void
RadiusServerListParser::parse(const RadiusServicePtr& service,
                              const ConstElementPtr& srv_list) {
    for (auto const& srv : srv_list->listValue()) {
        RadiusServerParser parser;
        parser.parse(service, srv);
    }
}

void
RadiusServerParser::parse(const RadiusServicePtr& service,
                          const ElementPtr& server) {
    RadiusImpl& riref = RadiusImpl::instance();

    // Details will be logged.
    ostringstream msg;

    // Peer address (was name).
    IOAddress peer_addr("::");
    const string& name = getString(server, "name");
    try {
        peer_addr = IOAddress(name);
    } catch (const Exception&) {
        try {
            peer_addr = Server::getAddress(name);
        } catch (const Exception& ex) {
            isc_throw(ConfigError, "can't resolve '" << name << "': "
                      << ex.what());
        }
    }
    msg << "peer-addr=" << peer_addr.toText();

    // port.
    uint16_t port;
    if (server->contains("port")) {
        port = getUint16(server, "port");
    } else if (service->name_ == "common-tls") {
        port = PW_TLS_PORT;
    } else if (service->name_ == "access") {
        port = PW_AUTH_PORT;
    } else {
        port = PW_ACCT_PORT;
    }
    msg << " port=" << port;

    // Local address.
    IOAddress local_addr("::");
    const string& local = riref.bindaddr_;
    if (local != "*") {
        try {
            local_addr = IOAddress(local);
        } catch (const Exception& ex) {
            isc_throw(ConfigError, "bad local address '" << local << "': "
                      << ex.what());
        }
    } else {
        try {
            local_addr = Server::getSrcAddress(peer_addr);
        } catch (const Exception& ex) {
            isc_throw(ConfigError, "can't get local address: " << ex.what());
        }
    }
    msg << " local_addr=" << local_addr;

    // secret.
    string secret;
    if (!server->contains("secret") && (service->name_ == "common-tls")) {
        secret = "radsec";
    } else {
        secret = getString(server, "secret");
        try {
            DefaultCredentials::check(secret);
        } catch (const DefaultCredential& ex) {
            isc_throw(ConfigError, "illegal use of a default secret");
        }
    }
    msg << " secret=*****";

    // TLS parameters.
    TlsContextPtr tls_context;
    if (service->name_ == "common-tls") {
        string trust_anchor = getString(server, "trust-anchor");
        string cert_file = getString(server, "cert-file");
        string key_file = getString(server, "key-file");
        TlsContext::configure(tls_context, TlsRole::CLIENT,
                              trust_anchor, cert_file, key_file);
    }

    try {
        ServerPtr srv(new Server(peer_addr, port, local_addr, tls_context,
                                 secret, riref.timeout_, riref.deadtime_));
        service->servers_.push_back(srv);
    } catch (const Exception& ex) {
        isc_throw(ConfigError, "can't create " << service->name_
                  << " server '" << msg.str() << "': " << ex.what());
    }

    // Done.
    LOG_INFO(radius_logger, RADIUS_SERVER_CONFIGURED)
        .arg(service->name_)
        .arg(msg.str());
}

void
RadiusAttributeListParser::parse(const RadiusServicePtr& service,
                                 const ConstElementPtr& attr_list) {
    for (auto const& attr : attr_list->listValue()) {
        RadiusAttributeParser parser;
        parser.parse(service, attr);
    }
}

void
RadiusAttributeParser::parse(const RadiusServicePtr& service,
                             const ElementPtr& attr) {
    AttrDefPtr def;

    // Set defaults.
    setDefaults(attr, ATTRIBUTE_DEFAULTS);

    // vendor.
    uint32_t vendor = 0;
    const ConstElementPtr& vendor_elem = attr->get("vendor");
    if (!vendor_elem) {
        // Should not happen as it is added by setDefaults.
        isc_throw(Unexpected, "no vendor parameter");
    } else if (vendor_elem->getType() != Element::string) {
        // Expected to be a common error.
        isc_throw(TypeError, "vendor parameter must be a string");
    }
    const string& vendor_txt = vendor_elem->stringValue();
    if (!vendor_txt.empty()) {
        IntCstDefPtr vendor_cst =
            AttrDefs::instance().getByName(PW_VENDOR_SPECIFIC, vendor_txt);
        if (vendor_cst) {
            vendor = vendor_cst->value_;
        } else {
            try {
                int64_t val = boost::lexical_cast<int64_t>(vendor_txt);
                if ((val < numeric_limits<int32_t>::min()) ||
                    (val > numeric_limits<uint32_t>::max())) {
                    isc_throw(Unexpected, "not 32 bit " << vendor_txt);
                }
                vendor = static_cast<uint32_t>(val);
            } catch (...) {
                isc_throw(ConfigError, "can't parse vendor '"
                          << vendor_txt << "'");
            }
        }
    }

    // name.
    const ConstElementPtr& name = attr->get("name");
    if (name) {
        if (name->stringValue().empty()) {
            isc_throw(ConfigError, "attribute name is empty");
        }
        def = AttrDefs::instance().getByName(name->stringValue(), vendor);
        if (!def) {
            ostringstream msg;
            msg << "attribute '" << name->stringValue() << "'";
            if (vendor != 0) {
                msg << " in vendor '" << vendor_txt << "'";
            }
            msg << " is unknown";
            isc_throw(ConfigError, msg.str());
        }
    }

    // type.
    const ConstElementPtr& type = attr->get("type");
    if (type) {
        if ((type->intValue() < 0) || (type->intValue() > 255)) {
            isc_throw(ConfigError, "out of range attribute type "
                      << type->intValue());
        }
        uint8_t attrib = static_cast<uint8_t>(type->intValue());
        if (def && (def->type_ != attrib)) {
            ostringstream msg;
            msg << "'" << name->stringValue() << "' attribute";
            if (vendor != 0) {
                msg << " in vendor '" << vendor_txt << "'";
            }
            msg << " has type " << static_cast<unsigned>(def->type_)
                << ", not " << static_cast<unsigned>(attrib);
            isc_throw(ConfigError, msg.str());
        }
        if (!def) {
            def = AttrDefs::instance().getByType(attrib, vendor);
        }
        if (!def) {
            ostringstream msg;
            msg << "attribute type " << static_cast<unsigned>(attrib);
            if (vendor != 0) {
                msg << " in vendor '" << vendor_txt << "'";
            }
            msg << " is unknown";
            isc_throw(ConfigError, msg.str());
        }
    }

    // name or type are required.
    if (!def) {
        isc_throw(ConfigError, "name or type are required");
    }

    // data.
    const string& data_txt = getString(attr, "data");

    // raw.
    const string& raw_txt = getString(attr, "raw");

    // expr.
    const string& expr_txt = getString(attr, "expr");

    /// @todo: raw.

    ExpressionPtr expression;
    if (!expr_txt.empty()) {
        if (!data_txt.empty() || !raw_txt.empty()) {
            isc_throw(ConfigError, "data, raw and expr are exclusive");
        }
        Option::Universe universe;
        if (CfgMgr::instance().getFamily() == AF_INET) {
            universe = Option::V4;
        } else {
            universe = Option::V6;
        }
        try {
            EvalContext eval_ctx(universe);
            eval_ctx.parseString(expr_txt, EvalContext::PARSER_STRING);
            expression.reset(new Expression());
            *expression = eval_ctx.expression_;
        } catch (const std::exception& ex) {
            isc_throw(ConfigError, "expression: [" << expr_txt
                      << "] error: " << ex.what() << " for "
                      << def->name_ << " attribute");
        }

        service->attributes_.add(def, AttributePtr(), expression, expr_txt);
    } else if (!raw_txt.empty()) {
        if (!data_txt.empty()) {
            isc_throw(ConfigError, "data and raw are exclusive");
        }
        // The decodeHex function expects that the string contains an
        // even number of digits. If we don't meet this requirement,
        // we have to insert a leading 0.
        string padded = raw_txt;
        if ((padded.size() % 2) != 0) {
            padded = padded.insert(0, "0");
        }
        vector<uint8_t> binary;
        try {
            encode::decodeHex(padded, binary);
        } catch (...) {
            isc_throw(ConfigError, "can't decode raw: [" << raw_txt
                      << "] for " << def->name_ << " attribute");
        }
        try {
            AttributePtr attribute = Attribute::fromBytes(def, binary);
            service->attributes_.add(def, attribute);
        } catch (const Exception& ex) {
            isc_throw(ConfigError, "can't create " << def->name_
                      << " attribute from raw: [" << raw_txt << "]: "
                      << ex.what());
        }
    } else {
        try {
            AttributePtr attribute = Attribute::fromText(def, data_txt);
            service->attributes_.add(def, attribute);
        } catch (const Exception& ex) {
            isc_throw(ConfigError, "can't create " << def->name_
                      << " attribute from [" << data_txt << "]: "
                      << ex.what());
        }
    }
}

} // end of namespace isc::radius
} // end of namespace isc
