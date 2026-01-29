// Copyright (C) 2020-2026 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <asiolink/addr_utilities.h>
#include <cc/simple_parser.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/host_mgr.h>
#include <dhcpsrv/subnet.h>
#include <radius_accounting.h>
#include <radius_log.h>
#include <radius_status.h>
#include <radius_utils.h>
#include <util/multi_threading_mgr.h>
#include <stdio.h>

using namespace std;
using namespace isc;
using namespace isc::asiolink;
using namespace isc::data;
using namespace isc::dhcp;
using namespace isc::util;
using namespace boost::gregorian;
using namespace boost::posix_time;
namespace ph = std::placeholders;

namespace isc {
namespace radius {

string
eventToText(Event event) {
    switch (event) {
    case EVENT_CREATE:
        return ("create");
    case EVENT_RENEW:
        return ("renew");
    case EVENT_REBIND:
        return ("rebind");
    case EVENT_EXPIRE:
        return ("expire");
    case EVENT_RELEASE:
        return ("release");
    case EVENT_DECLINE:
        return ("decline");
    case EVENT_ADD:
        return ("add");
    case EVENT_UPDATE:
        return ("update");
    case EVENT_DEL:
        return ("delete");
    default:
        return ("unknown");
    }
}

RadiusAcctEnv::RadiusAcctEnv(std::string session_id, Event event,
                             uint32_t subnet_id,
                             AttributesPtr send_attrs)
    : session_id_(session_id), event_(event), subnet_id_(subnet_id),
      send_attrs_(send_attrs), finished_(false) {
}

RadiusAcctHandler::RadiusAcctHandler(RadiusAcctEnv env,
                                     const CallbackAcct& callback)
    : env_(env), acct_() {
    acct_.reset(new RadiusAsyncAcct(env_.subnet_id_, env_.send_attrs_, callback));
    RadiusImpl::instance().registerExchange(acct_->getExchange());
    MultiThreadingLock lock(mutex_);
    ++counter_;
}

RadiusAcctHandler::~RadiusAcctHandler() {
    MultiThreadingLock lock(mutex_);
    if (counter_ > 0) {
        --counter_;
    }
}

void
RadiusAcctHandler::start() {
    acct_->start();
}

size_t
RadiusAcctHandler::getCounter() {
    MultiThreadingLock lock(mutex_);
    return (counter_);
}

size_t RadiusAcctHandler::counter_ = 0;

mutex RadiusAcctHandler::mutex_;

RadiusAccounting::RadiusAccounting()
    : RadiusService("accounting"), epoch_(date(2018, 3, 7), hours(11)), record_count_(0) {
}

void
RadiusAccounting::init(const std::string& filename) {
    filename_ = filename;
    if (!filename_.empty()) {
        file_.reset(new CSVFile(filename_));

        file_->addColumn("address");
        file_->addColumn("seconds");
        file_->addColumn("milliseconds");

        if (file_->exists()) {
            if (loadFromFile() && (container_.size() > 0)) {
                storeToFile();
            }
        }
        try {
            file_->open(true);
            LOG_INFO(radius_logger, RADIUS_SESSION_HISTORY_OPENED)
                .arg(filename_);
        } catch (const std::exception& ex) {
            LOG_ERROR(radius_logger, RADIUS_SESSION_HISTORY_OPEN_FAILED)
                .arg(filename_)
                .arg(ex.what());
            file_.reset();
        }
    }
}

RadiusAcctHandlerPtr
RadiusAccounting::buildAcct(const dhcp::Lease4Ptr& lease, Event event) {
    AttributesPtr send(new Attributes());

    // Add client-id and hardware address.
    string hwaddr = lease->hwaddr_->toText(false);
    if (RadiusImpl::instance().canonical_mac_address_) {
        hwaddr = canonize(hwaddr);
    }
    if (lease->client_id_) {
        vector<uint8_t> vec;
        bool extracted = false;
        if (RadiusImpl::instance().extract_duid_) {
            vec = extractDuid(lease->client_id_, extracted);
        }
        // If case the DUID was not extracted, we will try to get the
        // identifier using client-id.
        if (!extracted) {
            if (RadiusImpl::instance().clientid_pop0_) {
                vec = pop0(lease->client_id_);
            } else {
                vec = lease->client_id_->getClientId();
            }
        }
        string text;
        if (RadiusImpl::instance().clientid_printable_) {
            text = toPrintable(vec);
        } else {
            text = toHex(vec);
        }

        send->add(Attribute::fromString(PW_USER_NAME, text));
        send->add(Attribute::fromString(PW_CALLING_STATION_ID, hwaddr));
    } else {
        send->add(Attribute::fromString(PW_USER_NAME, hwaddr));
    }

    // Add address.
    send->add(Attribute::fromIpAddr(PW_FRAMED_IP_ADDRESS, lease->addr_));

    // Get the create timestamp.
    bool generate = false;
    if ((event == EVENT_CREATE) || (event == EVENT_ADD)) {
        generate = true;
    }
    ptime tm = getCreateTimestamp(lease->addr_, generate);

    // Build the session Id.
    ostringstream stream;
    stream << lease->addr_.toText() << '@';
    time_duration rtm(tm - epoch_);
    stream << rtm.total_seconds() << ".";
    rtm -= seconds(rtm.total_seconds());
    stream << rtm.total_milliseconds();
    send->add(Attribute::fromString(PW_ACCT_SESSION_ID, stream.str()));

    // Accounting status type.
    uint32_t status = PW_STATUS_ALIVE;
    if (generate) {
        status = PW_STATUS_START;
    } else if ((event == EVENT_EXPIRE) ||
               (event == EVENT_RELEASE) ||
               (event == EVENT_DECLINE) ||
               (event == EVENT_DEL)) {
        status = PW_STATUS_STOP;
    }
    send->add(Attribute::fromInt(PW_ACCT_STATUS_TYPE, status));

    // Add class: get host identifier.
    Host::IdentifierType id_type = RadiusImpl::instance().id_type4_;
    vector<uint8_t> host_id;
    switch (id_type) {
    case Host::IDENT_HWADDR:
        host_id = lease->hwaddr_->hwaddr_;
        break;
    case Host::IDENT_DUID:
        if (lease->client_id_) {
            host_id = lease->client_id_->getClientId();
            if ((host_id.size() <= 5) ||
                (host_id[0] != CLIENT_ID_OPTION_TYPE_DUID)) {
                host_id.clear();
            } else {
                host_id = vector<uint8_t>(host_id.begin() + 5, host_id.end());
            }
        }
        break;
    case Host::IDENT_CLIENT_ID:
        if (lease->client_id_) {
            host_id = lease->client_id_->getClientId();
        }
        break;
    case Host::IDENT_FLEX:
        if (lease->client_id_) {
            host_id = lease->client_id_->getClientId();
            if ((host_id.size() <= 1) || (host_id[0] != 0)) {
                host_id.clear();
            } else {
                host_id = vector<uint8_t>(host_id.begin() + 1, host_id.end());
            }
        }
        break;
    default:
        // not supported.
        break;
    }

    // Add class: get host entry.
    ConstHostPtr host;
    if (!host_id.empty()) {
        uint32_t subnet_id = lease->subnet_id_;
        ConstSubnet4Ptr subnet = CfgMgr::instance().getCurrentCfg()->
            getCfgSubnets4()->getBySubnetId(subnet_id);
        if (subnet && subnet->getReservationsGlobal()) {
            subnet_id = SUBNET_ID_GLOBAL;
        }
        host = HostMgr::instance().get4Any(subnet_id, id_type,
                                           &host_id[0], host_id.size());
    }
    // Add class: get cached Class attribute.
    // @todo: extend and make configurable with a list of attributes.
    if (host && host->getContext() &&
        (host->getContext()->getType() == Element::map)) {
        Attributes cached_attrs =
            Attributes::fromElement(host->getContext()->get("radius"));
        send->add(cached_attrs.get(PW_CLASS));
    }

    // Add attributes from configuration.
    send->append(RadiusImpl::instance().acct_->attributes_.getAll());

    // Return the handler.
    RadiusAcctEnv env(stream.str(), event, lease->subnet_id_, send);
    RadiusAcctHandlerPtr handler;
    handler.reset(new RadiusAcctHandler(
        env, std::bind(&RadiusAccounting::terminate, env, ph::_1)));

    // Erase create timestamp on stop.
    if (status == PW_STATUS_STOP) {
        eraseCreateTimestamp(lease->addr_);
    }

    return (handler);
}

RadiusAcctHandlerPtr
RadiusAccounting::buildAcct(const dhcp::Lease6Ptr& lease, Event event) {
    AttributesPtr send(new Attributes());

    // Add duid.
    vector<uint8_t> vec;
    if (RadiusImpl::instance().clientid_pop0_) {
        vec = pop0(lease->duid_);
    } else {
        vec = lease->duid_->getDuid();
    }
    string text;
    if (RadiusImpl::instance().clientid_printable_) {
        text = toPrintable(vec);
    } else {
        text = toHex(vec);
    }
    send->add(Attribute::fromString(PW_USER_NAME, text));

    // Add hardware address.
    if (lease->hwaddr_) {
        string hwaddr = lease->hwaddr_->toText(false);
        if (RadiusImpl::instance().canonical_mac_address_) {
            hwaddr = canonize(hwaddr);
        }
        send->add(Attribute::fromString(PW_CALLING_STATION_ID, hwaddr));
    }

    // Add address or prefix.
    if (lease->type_ != Lease::TYPE_PD) {
        send->add(Attribute::fromIpv6Addr(PW_FRAMED_IPV6_ADDRESS, lease->addr_));
    } else {
        send->add(Attribute::fromIpv6Prefix(PW_DELEGATED_IPV6_PREFIX,
                                            lease->prefixlen_, lease->addr_));
    }

    // Get the create timestamp.
    bool generate = false;
    if ((event == EVENT_CREATE) || (event == EVENT_ADD)) {
        generate = true;
    }
    ptime tm = getCreateTimestamp(lease->addr_, generate);

    // Build the session Id.
    ostringstream stream;
    stream << lease->addr_.toText() << '@';
    time_duration rtm(tm - epoch_);
    stream << rtm.total_seconds() << ".";
    rtm -= seconds(rtm.total_seconds());
    stream << rtm.total_milliseconds();
    send->add(Attribute::fromString(PW_ACCT_SESSION_ID, stream.str()));

    // Accounting status type.
    uint32_t status = PW_STATUS_ALIVE;
    if (generate) {
        status = PW_STATUS_START;
    } else if ((event == EVENT_EXPIRE) ||
               (event == EVENT_RELEASE) ||
               (event == EVENT_DECLINE) ||
               (event == EVENT_DEL)) {
        status = PW_STATUS_STOP;
    }
    send->add(Attribute::fromInt(PW_ACCT_STATUS_TYPE, status));

    // Add class: get host identifier.
    Host::IdentifierType id_type = RadiusImpl::instance().id_type6_;
    vector<uint8_t> host_id;
    switch (id_type) {
    case Host::IDENT_DUID:
        host_id = lease->duid_->getDuid();
        break;
    case Host::IDENT_HWADDR:
        if (lease->hwaddr_) {
            host_id = lease->hwaddr_->hwaddr_;
        }
        break;
    case Host::IDENT_FLEX:
        host_id = lease->duid_->getDuid();
        if ((host_id.size() <= 2) ||
            (host_id[0] != 0) || (host_id[1] != 0)) {
            host_id.clear();
        } else {
            host_id = vector<uint8_t>(host_id.begin() + 2, host_id.end());
        }
        break;
    default:
        // not supported.
        break;
    }

    // Add class: get host entry.
    ConstHostPtr host;
    if (!host_id.empty()) {
        uint32_t subnet_id = lease->subnet_id_;
        ConstSubnet6Ptr subnet = CfgMgr::instance().getCurrentCfg()->
            getCfgSubnets6()->getBySubnetId(subnet_id);
        if (subnet && subnet->getReservationsGlobal()) {
            subnet_id = SUBNET_ID_GLOBAL;
        }
        host = HostMgr::instance().get6Any(subnet_id, id_type,
                                           &host_id[0], host_id.size());
    }
    // Add class: get cached Class attribute.
    // @todo: extend and make configurable with a list of attributes.
    if (host && host->getContext() &&
        (host->getContext()->getType() == Element::map)) {
        Attributes cached_attrs =
            Attributes::fromElement(host->getContext()->get("radius"));
        send->add(cached_attrs.get(PW_CLASS));
    }

    // Add attributes from configuration.
    send->append(RadiusImpl::instance().acct_->attributes_.getAll());

    // Return the handler.
    RadiusAcctEnv env(stream.str(), event, lease->subnet_id_, send);
    RadiusAcctHandlerPtr handler;
    handler.reset(new RadiusAcctHandler(
        env, std::bind(&RadiusAccounting::terminate, env, ph::_1)));

    // Erase create timestamp on stop.
    if (status == PW_STATUS_STOP) {
        eraseCreateTimestamp(lease->addr_);
    }

    return (handler);
}

RadiusAcctHandlerPtr
RadiusAccounting::buildAcct4(const ConstElementPtr& arguments, Event event) {
    IOAddress addr(0);
    uint32_t subnet_id = SUBNET_ID_UNUSED;
    HWAddrPtr hwaddr;
    ClientIdPtr client_id;
    bool force = false;
    try {
        // Parse arguments.
        addr = SimpleParser::getAddress(arguments, "ip-address");
        subnet_id = SimpleParser::getInteger(arguments, "subnet-id");
        string hwaddr_txt = SimpleParser::getString(arguments, "hw-address");
        hwaddr.reset(new HWAddr(HWAddr::fromText(hwaddr_txt)));

        if (arguments->contains("client-id")) {
            string txt = SimpleParser::getString(arguments, "client-id");
            client_id = ClientId::fromText(txt);
        }

        if (arguments->contains("force-create")) {
            force = SimpleParser::getBoolean(arguments, "force-create");
        }
    } catch (const std::exception&) {
        return (RadiusAcctHandlerPtr());
    }
    if (!addr.isV4()) {
        return (RadiusAcctHandlerPtr());
    }

    // Fill attributes.
    AttributesPtr send(new Attributes());

    // Add client-id and hardware address.
    string mac = hwaddr->toText(false);
    if (RadiusImpl::instance().canonical_mac_address_) {
        mac = canonize(mac);
    }
    if (client_id) {
        vector<uint8_t> vec;
        bool extracted = false;
        if (RadiusImpl::instance().extract_duid_) {
            vec = extractDuid(client_id, extracted);
        }
        // If case the DUID was not extracted, we will try to get the
        // identifier using client-id.
        if (!extracted) {
            if (RadiusImpl::instance().clientid_pop0_) {
                vec = pop0(client_id);
            } else {
                vec = client_id->getClientId();
            }
        }
        string text;
        if (RadiusImpl::instance().clientid_printable_) {
            text = toPrintable(vec);
        } else {
            text = toHex(vec);
        }

        send->add(Attribute::fromString(PW_USER_NAME, text));
        send->add(Attribute::fromString(PW_CALLING_STATION_ID, mac));
    } else {
        send->add(Attribute::fromString(PW_USER_NAME, mac));
    }

    // Add address.
    send->add(Attribute::fromIpAddr(PW_FRAMED_IP_ADDRESS, addr));

    // Get the create timestamp.
    bool generate = false;
    if ((event == EVENT_ADD) && force) {
        generate = true;
    }
    ptime tm = getCreateTimestamp(addr, generate);

    // Build the session Id.
    ostringstream stream;
    stream << addr << '@';
    time_duration rtm(tm - epoch_);
    stream << rtm.total_seconds() << ".";
    rtm -= seconds(rtm.total_seconds());
    stream << rtm.total_milliseconds();
    send->add(Attribute::fromString(PW_ACCT_SESSION_ID, stream.str()));

    // Accounting status type.
    uint32_t status = PW_STATUS_ALIVE;
    if (generate) {
        status = PW_STATUS_START;
    } else if (event == EVENT_DEL) {
        status = PW_STATUS_STOP;
    }
    send->add(Attribute::fromInt(PW_ACCT_STATUS_TYPE, status));

    // Add class: get host identifier.
    Host::IdentifierType id_type = RadiusImpl::instance().id_type4_;
    vector<uint8_t> host_id;
    switch (id_type) {
    case Host::IDENT_HWADDR:
        host_id = hwaddr->hwaddr_;
        break;
    case Host::IDENT_DUID:
        if (client_id) {
            host_id = client_id->getClientId();
            if ((host_id.size() <= 5) ||
                (host_id[0] != CLIENT_ID_OPTION_TYPE_DUID)) {
                host_id.clear();
            } else {
                host_id = vector<uint8_t>(host_id.begin() + 5, host_id.end());
            }
        }
        break;
    case Host::IDENT_CLIENT_ID:
        if (client_id) {
            host_id = client_id->getClientId();
        }
        break;
    case Host::IDENT_FLEX:
        if (client_id) {
            host_id = client_id->getClientId();
            if ((host_id.size() <= 1) || (host_id[0] != 0)) {
                host_id.clear();
            } else {
                host_id = vector<uint8_t>(host_id.begin() + 1, host_id.end());
            }
        }
        break;
    default:
        // not supported.
        break;
    }

    // Add class: get host entry.
    ConstHostPtr host;
    if (!host_id.empty()) {
        ConstSubnet4Ptr subnet = CfgMgr::instance().getCurrentCfg()->
            getCfgSubnets4()->getBySubnetId(subnet_id);
        uint32_t host_subnet_id =
            ((subnet && subnet->getReservationsGlobal()) ?
             SUBNET_ID_GLOBAL : subnet_id);
        host = HostMgr::instance().get4Any(host_subnet_id, id_type,
                                           &host_id[0], host_id.size());
    }
    // Add class: get cached Class attribute.
    // @todo: extend and make configurable with a list of attributes.
    if (host && host->getContext() &&
        (host->getContext()->getType() == Element::map)) {
        Attributes cached_attrs =
            Attributes::fromElement(host->getContext()->get("radius"));
        send->add(cached_attrs.get(PW_CLASS));
    }

    // Add attributes from configuration.
    send->append(RadiusImpl::instance().acct_->attributes_.getAll());

    // Return the handler.
    RadiusAcctEnv env(stream.str(), event, subnet_id, send);
    RadiusAcctHandlerPtr handler;
    handler.reset(new RadiusAcctHandler(
        env, std::bind(&RadiusAccounting::terminate, env, ph::_1)));

    // Erase create timestamp on stop.
    if (status == PW_STATUS_STOP) {
        eraseCreateTimestamp(addr);
    }

    return (handler);
}

RadiusAcctHandlerPtr
RadiusAccounting::buildAcct6(const ConstElementPtr& arguments, Event event) {
    IOAddress addr("::");
    uint32_t subnet_id = SUBNET_ID_UNUSED;
    DuidPtr duid;
    HWAddrPtr hwaddr;
    Lease::Type type = Lease::TYPE_NA;
    uint8_t prefix_len = 128;
    bool force = false;
    try {
        // Parse arguments.
        addr = SimpleParser::getAddress(arguments, "ip-address");
        subnet_id = SimpleParser::getInteger(arguments, "subnet-id");
        string txt = SimpleParser::getString(arguments, "duid");
        duid.reset(new DUID(DUID::fromText(txt)));

        if (arguments->contains("hw-address")) {
            string hwaddr_txt = SimpleParser::getString(arguments, "hw-address");
            hwaddr.reset(new HWAddr(HWAddr::fromText(hwaddr_txt)));
        }

        if (arguments->contains("type")) {
            txt = SimpleParser::getString(arguments, "type");
            if (txt == "IA_NA") {
                type = Lease::TYPE_NA;
            } else if (txt == "IA_TA") {
                type = Lease::TYPE_TA;
            } else if (txt == "IA_PD") {
                type = Lease::TYPE_PD;

                prefix_len = SimpleParser::getInteger(arguments, "prefix-len");

                if ((prefix_len <= 0) || (prefix_len > 128)) {
                    isc_throw(OutOfRange,
                              "'prefix-len' value must be in range of [1..128]");
                }

                if (prefix_len != 128) {
                    IOAddress first_address = firstAddrInPrefix(addr, prefix_len);
                    if (first_address != addr) {
                        isc_throw(BadValue, "Prefix address: " << addr
                                  << " exceeds prefix/prefix-len pair: " << first_address
                                  << "/" << static_cast<uint32_t>(prefix_len));
                    }
                }
            } else {
                isc_throw(BadValue, "bad type" << txt);
            }
        }

        if (arguments->contains("force-create")) {
            force = SimpleParser::getBoolean(arguments, "force-create");
        }
    } catch (const std::exception&) {
        return (RadiusAcctHandlerPtr());
    }
    if (!addr.isV6()) {
        return (RadiusAcctHandlerPtr());
    }

    // Fill attributes.
    AttributesPtr send(new Attributes());

    // Add duid.
    vector<uint8_t> vec;
    if (RadiusImpl::instance().clientid_pop0_) {
        vec = pop0(duid);
    } else {
        vec = duid->getDuid();
    }
    string text;
    if (RadiusImpl::instance().clientid_printable_) {
        text = toPrintable(vec);
    } else {
        text = toHex(vec);
    }
    send->add(Attribute::fromString(PW_USER_NAME, text));

    // Add hardware address.
    if (hwaddr) {
        string mac = hwaddr->toText(false);
        if (RadiusImpl::instance().canonical_mac_address_) {
            mac = canonize(mac);
        }
        send->add(Attribute::fromString(PW_CALLING_STATION_ID, mac));
    }

    // Add address or prefix.
    if (type != Lease::TYPE_PD) {
        send->add(Attribute::fromIpv6Addr(PW_FRAMED_IPV6_ADDRESS, addr));
    } else {
        send->add(Attribute::fromIpv6Prefix(PW_DELEGATED_IPV6_PREFIX,
                                            prefix_len, addr));
    }

    // Get the create timestamp.
    bool generate = false;
    if ((event == EVENT_ADD) && force) {
        generate = true;
    }
    ptime tm = getCreateTimestamp(addr, generate);

    // Build the session Id.
    ostringstream stream;
    stream << addr << '@';
    time_duration rtm(tm - epoch_);
    stream << rtm.total_seconds() << ".";
    rtm -= seconds(rtm.total_seconds());
    stream << rtm.total_milliseconds();
    send->add(Attribute::fromString(PW_ACCT_SESSION_ID, stream.str()));

    // Accounting status type.
    uint32_t status = PW_STATUS_ALIVE;
    if (generate) {
        status = PW_STATUS_START;
    } else if (event == EVENT_DEL) {
        status = PW_STATUS_STOP;
    }
    send->add(Attribute::fromInt(PW_ACCT_STATUS_TYPE, status));

    // Add class: get host identifier.
    Host::IdentifierType id_type = RadiusImpl::instance().id_type6_;
    vector<uint8_t> host_id;
    switch (id_type) {
    case Host::IDENT_DUID:
        host_id = duid->getDuid();
        break;
    case Host::IDENT_HWADDR:
        if (hwaddr) {
            host_id = hwaddr->hwaddr_;
        }
        break;
    case Host::IDENT_FLEX:
        host_id = duid->getDuid();
        if ((host_id.size() <= 2) ||
            (host_id[0] != 0) || (host_id[1] != 0)) {
            host_id.clear();
        } else {
            host_id = vector<uint8_t>(host_id.begin() + 2, host_id.end());
        }
        break;
    default:
        // not supported.
        break;
    }

    // Add class: get host entry.
    ConstHostPtr host;
    if (!host_id.empty()) {
        ConstSubnet6Ptr subnet = CfgMgr::instance().getCurrentCfg()->
            getCfgSubnets6()->getBySubnetId(subnet_id);
        uint32_t host_subnet_id =
            ((subnet && subnet->getReservationsGlobal()) ?
             SUBNET_ID_GLOBAL : subnet_id);
        host = HostMgr::instance().get6Any(host_subnet_id, id_type,
                                           &host_id[0], host_id.size());
    }
    // Add class: get cached Class attribute.
    // @todo: extend and make configurable with a list of attributes.
    if (host && host->getContext() &&
        (host->getContext()->getType() == Element::map)) {
        Attributes cached_attrs =
            Attributes::fromElement(host->getContext()->get("radius"));
        send->add(cached_attrs.get(PW_CLASS));
    }

    // Add attributes from configuration.
    send->append(RadiusImpl::instance().acct_->attributes_.getAll());

    // Return the handler.
    RadiusAcctEnv env(stream.str(), event, subnet_id, send);
    RadiusAcctHandlerPtr handler;
    handler.reset(new RadiusAcctHandler(
        env, std::bind(&RadiusAccounting::terminate, env, ph::_1)));

    // Erase create timestamp on stop.
    if (status == PW_STATUS_STOP) {
        eraseCreateTimestamp(addr);
    }

    return (handler);
}

void
RadiusAccounting::runAsync(RadiusAcctHandlerPtr handler) {
    handler->start();
}

void
RadiusAccounting::terminate(RadiusAcctEnv env, int result) {
    env.finished_ = true;
    if (result != OK_RC) {
        LOG_ERROR(radius_logger, RADIUS_ACCOUNTING_ERROR)
            .arg(env.session_id_)
            .arg(env.event_)
            .arg(eventToText(env.event_))
            .arg(result)
            .arg(exchangeRCtoText(result));
    }
}

ptime
RadiusAccounting::getCreateTimestamp(const IOAddress& addr, bool generate) {
    MultiThreadingLock lock(mutex_);
    TMContainerAddressIndex& idx = container_.get<TMAddressIndexTag>();
    TMContainerAddressIndex::iterator it = idx.find(addr);
    if (!generate) {
        if (it == idx.end()) {
            LOG_DEBUG(radius_logger, RADIUS_DBG_TRACE,
                      RADIUS_ACCOUNTING_NO_HISTORY)
                .arg(addr.toText());
        } else {
            return (it->timestamp_);
        }
    }

    // generate is true or no address was found.
    while (it != idx.end()) {
        idx.erase(it);
        // One round should be enough as the address is unique.
        it = idx.find(addr);
    }
    ptime tm = microsec_clock::universal_time();
    auto ret = container_.insert(LeaseTS(addr, tm));
    if (!ret.second) {
        LOG_ERROR(radius_logger, RADIUS_ACCOUNTING_HISTORY_UPDATE_FAILED)
            .arg(addr.toText());
    }

    // Append to create timestamp file.
    if (file_) {
        try {
            CSVRow row(file_->getColumnCount());

            row.writeAt(file_->getColumnIndex("address"), addr);
            time_duration rtm(tm - epoch_);
            row.writeAt(file_->getColumnIndex("seconds"), rtm.total_seconds());
            rtm -= seconds(rtm.total_seconds());
            row.writeAt(file_->getColumnIndex("milliseconds"),
                        rtm.total_milliseconds());

            file_->append(row);
            ++record_count_;
        } catch (const std::exception& ex) {
            LOG_WARN(radius_logger, RADIUS_SESSION_HISTORY_APPEND_FAILED)
                .arg(addr.toText())
                .arg(ex.what());
            file_.reset();
        }
    }

    return (tm);
}

void
RadiusAccounting::eraseCreateTimestamp(const IOAddress& addr) {
    MultiThreadingLock lock(mutex_);
    TMContainerAddressIndex& idx = container_.get<TMAddressIndexTag>();
    TMContainerAddressIndex::iterator it = idx.find(addr);
    while (it != idx.end()) {
        idx.erase(it);
        // One round should be enough as the address is unique.
        it = idx.find(addr);
    }
    // Append delete marker to create timestamp file.
    if (file_) {
        try {
            CSVRow row(file_->getColumnCount());

            row.writeAt(file_->getColumnIndex("address"), addr);
            row.writeAt(file_->getColumnIndex("seconds"), 0L);
            row.writeAt(file_->getColumnIndex("milliseconds"), 0L);

            file_->append(row);
            ++record_count_;
        } catch (const std::exception& ex) {
            LOG_WARN(radius_logger, RADIUS_SESSION_HISTORY_APPEND_FAILED)
                .arg(addr.toText())
                .arg(ex.what());
            file_.reset();
        }
    }
}

bool
RadiusAccounting::loadFromFile() {
    TMContainerAddressIndex& idx = container_.get<TMAddressIndexTag>();
    bool ok = true;
    size_t adds = 0;
    size_t fails = 0;
    try {
        file_->open(false);

        for (;;) {
            CSVRow row;
            file_->next(row, true);
            // Check if done.
            if (row == CSVFile::EMPTY_ROW()) {
                if (ok) {
                    LOG_INFO(radius_logger, RADIUS_SESSION_HISTORY_LOADED)
                        .arg(adds)
                        .arg(container_.size());
                    break;
                } else {
                    isc_throw(CSVFileError, "partial load");
                }
            }

            // Get fields.
            string addr_txt = row.readAt(file_->getColumnIndex("address"));
            IOAddress addr(addr_txt);
            long secs =
                row.readAndConvertAt<long>(file_->getColumnIndex("seconds"));
            long msecs =
                row.readAndConvertAt<long>(file_->getColumnIndex("milliseconds"));

            // Get an iterator to a possible entry.
            TMContainerAddressIndex::iterator it = idx.find(addr);
            while (it != idx.end()) {
                idx.erase(it);
                // One round should be enough as the address is unique.
                it = idx.find(addr);
            }

            // Zero seconds means deleted record.
            if (secs == 0) {
                continue;
            }

            time_duration rtm (seconds(secs) + milliseconds(msecs));
            ptime tm(epoch_ + rtm);
            auto ret = container_.insert(LeaseTS(addr, tm));
            if (!ret.second) {
                ok = false;
                ++fails;
            } else {
                ++adds;
            }
        }

    } catch (const std::exception& ex) {
        LOG_ERROR(radius_logger, RADIUS_SESSION_HISTORY_LOAD_FAILED)
            .arg(adds)
            .arg(fails)
            .arg(container_.size());
        ok = false;
    }

    file_->close();

    return (ok);
}

void
RadiusAccounting::storeToFile() {
    TMContainerTimestampIndex& idx = container_.get<TMTimestampIndexTag>();
    string newfilename = filename_ + ".new";
    CSVFile newfile(newfilename);
    size_t stored = 0;
    if (container_.empty()) {
        return;
    }
    try {
        // Add columns
        newfile.addColumn("address");
        newfile.addColumn("seconds");
        newfile.addColumn("milliseconds");

        // Rename file if it exists.
        if (newfile.exists()) {
            string backfilename = filename_ + ".new~";
            rename(newfilename.c_str(), backfilename.c_str());
        }

        // Open file (seed to end in case the rename failed).
        newfile.open(true);

        // Dump container content.
        for (auto const& it : idx) {
            CSVRow row(newfile.getColumnCount());

            row.writeAt(newfile.getColumnIndex("address"), it.addr_);
            time_duration rtm(it.timestamp_ - epoch_);
            row.writeAt(newfile.getColumnIndex("seconds"),
                        rtm.total_seconds());
            rtm -= seconds(rtm.total_seconds());
            row.writeAt(newfile.getColumnIndex("milliseconds"),
                        rtm.total_milliseconds());

            newfile.append(row);
            ++stored;
        }

        // Close file.
        newfile.close();

        // Rename files.
        string backfilename = filename_ + ".bak";
        bool moved = true;
        if (rename(filename_.c_str(), backfilename.c_str()) != 0) {
            moved = false;
        }
        if (rename(newfilename.c_str(), filename_.c_str()) != 0) {
            if (moved) {
                // Try to restore current file.
                rename(backfilename.c_str(), filename_.c_str());
            }
        }

        LOG_INFO(radius_logger, RADIUS_SESSION_HISTORY_STORED)
            .arg(stored);

    } catch (const std::exception& ex) {
        LOG_ERROR(radius_logger, RADIUS_SESSION_HISTORY_STORE_FAILED)
            .arg(newfilename)
            .arg(ex.what())
            .arg(stored)
            .arg(container_.size());
    }
    record_count_ = 0;
}

void
RadiusAccounting::setIdleTimer() {
    MultiThreadingLock lock(idle_timer_mutex_);
    cancelIdleTimer();
    if (idle_timer_interval_ <= 0) {
        return;
    }
    // Cope to one day.
    long secs = idle_timer_interval_;
    if (secs > 24*60*60) {
        secs = 24*60*60;
    }
    idle_timer_.reset(new IntervalTimer(RadiusImpl::instance().getIOContext()));
    idle_timer_->setup(RadiusAccounting::IdleTimerCallback,
                       secs * 1000, IntervalTimer::REPEATING);
}

void
RadiusAccounting::IdleTimerCallback() {
    AttributesPtr send_attrs;
    RadiusAcctStatusPtr handler(new RadiusAcctStatus(send_attrs, 0));
    RadiusImpl::instance().registerExchange(handler->getExchange());
    handler->start();
}

} // end of namespace isc::radius
} // end of namespace isc
