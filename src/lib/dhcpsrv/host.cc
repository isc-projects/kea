// Copyright (C) 2014-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <dhcp/pkt4.h>
#include <dhcpsrv/host.h>
#include <util/encode/hex.h>
#include <util/strutil.h>
#include <asiolink/io_address.h>
#include <cryptolink/crypto_rng.h>
#include <exceptions/exceptions.h>

#include <sstream>

using namespace isc::data;
using namespace isc::asiolink;

namespace isc {
namespace dhcp {

AuthKey::AuthKey(const std::vector<uint8_t>& key) {
    setAuthKey(key);
}

AuthKey::AuthKey(const std::string& key) {
    setAuthKey(key);
}

AuthKey::AuthKey() {
    authKey_ = AuthKey::getRandomKeyString();
}

std::vector<uint8_t>
AuthKey::getRandomKeyString() {
    return (isc::cryptolink::random(AUTH_KEY_LEN));
}

std::string
AuthKey::toText() const {
    if (authKey_.empty()) {
        return ("");
    }
    return (util::encode::encodeHex(authKey_));
}

void
AuthKey::setAuthKey(const std::vector<uint8_t>& key) {
    authKey_ = key;
    if (authKey_.size() > AUTH_KEY_LEN) {
        authKey_.resize(AUTH_KEY_LEN);
    }
}

void
AuthKey::setAuthKey(const std::string& key) {
    if (key.empty()) {
        authKey_.clear();
        return;
    }
    try {
        std::vector<uint8_t> bin;
        util::encode::decodeHex(key, bin);
        setAuthKey(bin);
    } catch (const std::exception& ex) {
        isc_throw(BadValue, "bad auth key: " << ex.what());
    }
}

bool
AuthKey::operator==(const AuthKey& other) const {
    return (authKey_ == other.authKey_);
}

bool
AuthKey::operator!=(const AuthKey& other) const {
    return (authKey_ != other.authKey_);
}

IPv6Resrv::IPv6Resrv(const Type& type,
                     const asiolink::IOAddress& prefix,
                     const uint8_t prefix_len)
    : type_(type), prefix_(asiolink::IOAddress("::")), prefix_len_(128) {
    // Validate and set the actual values.
    set(type, prefix, prefix_len);
}

void
IPv6Resrv::set(const Type& type, const asiolink::IOAddress& prefix,
               const uint8_t prefix_len) {
    if (!prefix.isV6() || prefix.isV6Multicast()) {
        isc_throw(isc::BadValue, "invalid prefix '" << prefix
                  << "' for new IPv6 reservation");

    } else if (prefix_len > 128) {
        isc_throw(isc::BadValue, "invalid prefix length '"
                  << static_cast<int>(prefix_len)
                  << "' for new IPv6 reservation");

    } else if ((type == TYPE_NA) && (prefix_len != 128)) {
        isc_throw(isc::BadValue, "invalid prefix length '"
                  << static_cast<int>(prefix_len)
                  << "' for reserved IPv6 address, expected 128");
    }

    type_ = type;
    prefix_ = prefix;
    prefix_len_ = prefix_len;
}

std::string
IPv6Resrv::toText() const {
    std::ostringstream s;
    s << prefix_;
    // For PD, append prefix length.
    if (getType() == TYPE_PD) {
        s << "/" << static_cast<int>(prefix_len_);
    }
    return (s.str());
}

bool
IPv6Resrv::operator==(const IPv6Resrv& other) const {
    return (type_ == other.type_ &&
            prefix_ == other.prefix_ &&
            prefix_len_ == other.prefix_len_);
}

bool
IPv6Resrv::operator!=(const IPv6Resrv& other) const {
    return (!operator==(other));
}

Host::Host(const uint8_t* identifier, const size_t identifier_len,
           const IdentifierType& identifier_type,
           const SubnetID ipv4_subnet_id, const SubnetID ipv6_subnet_id,
           const asiolink::IOAddress& ipv4_reservation,
           const std::string& hostname,
           const std::string& dhcp4_client_classes,
           const std::string& dhcp6_client_classes,
           const asiolink::IOAddress& next_server,
           const std::string& server_host_name,
           const std::string& boot_file_name,
           const AuthKey& auth_key)

    : identifier_type_(identifier_type),
      identifier_value_(), ipv4_subnet_id_(ipv4_subnet_id),
      ipv6_subnet_id_(ipv6_subnet_id),
      ipv4_reservation_(asiolink::IOAddress::IPV4_ZERO_ADDRESS()),
      hostname_(hostname), dhcp4_client_classes_(dhcp4_client_classes),
      dhcp6_client_classes_(dhcp6_client_classes),
      next_server_(asiolink::IOAddress::IPV4_ZERO_ADDRESS()),
      server_host_name_(server_host_name), boot_file_name_(boot_file_name),
      host_id_(0), cfg_option4_(new CfgOption()),
      cfg_option6_(new CfgOption()), negative_(false),
      key_(auth_key) {

    // Initialize host identifier.
    setIdentifier(identifier, identifier_len, identifier_type);

    if (!ipv4_reservation.isV4Zero()) {
        // Validate and set IPv4 address reservation.
        setIPv4Reservation(ipv4_reservation);
    }

    if (!next_server.isV4Zero()) {
        // Validate and set next server address.
        setNextServer(next_server);
    }
}

Host::Host(const std::string& identifier, const std::string& identifier_name,
           const SubnetID ipv4_subnet_id, const SubnetID ipv6_subnet_id,
           const asiolink::IOAddress& ipv4_reservation,
           const std::string& hostname,
           const std::string& dhcp4_client_classes,
           const std::string& dhcp6_client_classes,
           const asiolink::IOAddress& next_server,
           const std::string& server_host_name,
           const std::string& boot_file_name,
           const AuthKey& auth_key)
    : identifier_type_(IDENT_HWADDR),
      identifier_value_(), ipv4_subnet_id_(ipv4_subnet_id),
      ipv6_subnet_id_(ipv6_subnet_id),
      ipv4_reservation_(asiolink::IOAddress::IPV4_ZERO_ADDRESS()),
      hostname_(hostname), dhcp4_client_classes_(dhcp4_client_classes),
      dhcp6_client_classes_(dhcp6_client_classes),
      next_server_(asiolink::IOAddress::IPV4_ZERO_ADDRESS()),
      server_host_name_(server_host_name), boot_file_name_(boot_file_name),
      host_id_(0), cfg_option4_(new CfgOption()),
      cfg_option6_(new CfgOption()), negative_(false),
      key_(auth_key) {

    // Initialize host identifier.
    setIdentifier(identifier, identifier_name);

    if (!ipv4_reservation.isV4Zero()) {
        // Validate and set IPv4 address reservation.
        setIPv4Reservation(ipv4_reservation);
    }

    if (!next_server.isV4Zero()) {
        // Validate and set next server address.
        setNextServer(next_server);
    }
}

size_t
Host::getIdentifierMaxLength(const IdentifierType& type) {
    switch (type) {
    case IDENT_HWADDR:
        return (HWAddr::MAX_HWADDR_LEN);
    case IDENT_DUID:
        return (DUID::MAX_DUID_LEN);
    default:
        // In fact it is backend dependent but for compatibility we take
        // the lowest value.
        return (128);
    }
}

const std::vector<uint8_t>&
Host::getIdentifier() const {
    return (identifier_value_);
}

Host::IdentifierType
Host::getIdentifierType() const {
    return (identifier_type_);
}

Host::IdentifierType
Host::getIdentifierType(const std::string& identifier_name) {
    if (identifier_name == "hw-address") {
        return (IDENT_HWADDR);

    } else if (identifier_name == "duid") {
        return (IDENT_DUID);

    } else if (identifier_name == "circuit-id") {
        return (IDENT_CIRCUIT_ID);

    } else if (identifier_name == "client-id") {
        return (IDENT_CLIENT_ID);
    } else if (identifier_name == "flex-id") {
        return (IDENT_FLEX);
    } else {
        isc_throw(isc::BadValue, "invalid client identifier type '"
                  << identifier_name << "'");
    }
}

HWAddrPtr
Host::getHWAddress() const {
    return ((identifier_type_ == IDENT_HWADDR) ?
            HWAddrPtr(new HWAddr(identifier_value_, HTYPE_ETHER)) : HWAddrPtr());
}

DuidPtr
Host::getDuid() const {
    return ((identifier_type_ == IDENT_DUID) ?
            DuidPtr(new DUID(identifier_value_)) : DuidPtr());
}


std::string
Host::getIdentifierAsText() const {
    return (getIdentifierAsText(identifier_type_, &identifier_value_[0],
                                identifier_value_.size()));
}

std::string
Host::getIdentifierAsText(const IdentifierType& type, const uint8_t* value,
                          const size_t length) {
    // Convert identifier into <type>=<value> form.
    std::ostringstream s;
    switch (type) {
    case IDENT_HWADDR:
        s << "hwaddr";
        break;
    case IDENT_DUID:
        s << "duid";
        break;
    case IDENT_CIRCUIT_ID:
        s << "circuit-id";
        break;
    case IDENT_CLIENT_ID:
        s << "client-id";
        break;
    case IDENT_FLEX:
        s << "flex-id";
        break;
    default:
        // This should never happen actually, unless we add new identifier
        // and forget to add a case for it above.
        s << "(invalid-type)";
    }
    std::vector<uint8_t> vec(value, value + length);
    s << "=" << (length > 0 ? util::encode::encodeHex(vec) : "(null)");
    return (s.str());
}

std::string
Host::getIdentifierName(const IdentifierType& type) {
    switch (type) {
    case Host::IDENT_HWADDR:
        return ("hw-address");

    case Host::IDENT_DUID:
        return ("duid");

    case Host::IDENT_CIRCUIT_ID:
        return ("circuit-id");

    case Host::IDENT_CLIENT_ID:
        return ("client-id");

    case Host::IDENT_FLEX:
        return ("flex-id");

    default:
        ;
    }
    return ("(unknown)");
}


void
Host::setIdentifier(const uint8_t* identifier, const size_t len,
                    const IdentifierType& type) {
    if (len < 1) {
        isc_throw(BadValue, "invalid client identifier length 0");
    } else if (len > getIdentifierMaxLength(type)) {
        isc_throw(BadValue, "too long client identifier type "
                  << getIdentifierName(type)
                  << " length " << len);
    }

    identifier_type_ = type;
    identifier_value_.assign(identifier, identifier + len);
}

void
Host::setIdentifier(const std::string& identifier, const std::string& name) {
    // Empty identifier is not allowed.
    if (identifier.empty()) {
        isc_throw(isc::BadValue, "empty host identifier used");
    }

    // Set identifier type.
    identifier_type_ = getIdentifierType(name);

    // Identifier value can either be specified as string of hexadecimal
    // digits or a string in quotes. The latter is copied to a vector excluding
    // quote characters.

    // Try to convert the values in quotes into a vector of ASCII codes.
    // If the identifier lacks opening and closing quote, this will return
    // an empty value, in which case we'll try to decode it as a string of
    // hexadecimal digits.
    bool too_long = false;
    try {
        std::vector<uint8_t> binary = util::str::quotedStringToBinary(identifier);
        if (binary.empty()) {
            util::str::decodeFormattedHexString(identifier, binary);
        }

        size_t len = binary.size();
        if (len > getIdentifierMaxLength(identifier_type_)) {
            // Message does not matter as it will be replaced below...
            too_long = true;
            isc_throw(BadValue, "too long client identifier type " << name
                      << " length " << len);
        }

        // Successfully decoded the identifier, so let's use it.
        identifier_value_.swap(binary);

    } catch (...) {
        // The string doesn't match any known pattern, so we have to
        // report an error at this point.
        if (too_long) {
            throw;
        }
        isc_throw(isc::BadValue, "invalid host identifier value '"
                  << identifier << "'");
    }
}

void
Host::setIdentifierType(const IdentifierType& type) {
    identifier_type_ = type;
}

void
Host::setIPv4Reservation(const asiolink::IOAddress& address) {
    if (!address.isV4()) {
        isc_throw(isc::BadValue, "address '" << address << "' is not a valid"
                  " IPv4 address");
    } else if (address.isV4Zero() || address.isV4Bcast()) {
        isc_throw(isc::BadValue, "must not make reservation for the '"
                  << address << "' address");
    }
    ipv4_reservation_ = address;
}

void
Host::removeIPv4Reservation() {
    ipv4_reservation_ = asiolink::IOAddress::IPV4_ZERO_ADDRESS();
}

void
Host::addReservation(const IPv6Resrv& reservation) {
    // Check if it is not duplicating existing reservation.
    if (hasReservation(reservation)) {
        isc_throw(isc::InvalidOperation, "failed on attempt to add a duplicated"
                  " host reservation for " << reservation.toText());
    }
    // Add it.
    ipv6_reservations_.insert(IPv6ResrvTuple(reservation.getType(),
                                             reservation));
}

IPv6ResrvRange
Host::getIPv6Reservations(const IPv6Resrv::Type& type) const {
    return (ipv6_reservations_.equal_range(type));
}

IPv6ResrvRange
Host::getIPv6Reservations() const {
    return (IPv6ResrvRange(ipv6_reservations_.begin(),
                           ipv6_reservations_.end()));
}

bool
Host::hasIPv6Reservation() const {
    return (!ipv6_reservations_.empty());
}

bool
Host::hasReservation(const IPv6Resrv& reservation) const {
    IPv6ResrvRange reservations = getIPv6Reservations(reservation.getType());
    if (std::distance(reservations.first, reservations.second) > 0) {
        for (IPv6ResrvIterator it = reservations.first;
             it != reservations.second; ++it) {
            if (it->second == reservation) {
                return (true);
            }
        }
    }

    // No matching reservations found.
    return (false);
}

void
Host::addClientClass4(const std::string& class_name) {
    addClientClassInternal(dhcp4_client_classes_, class_name);
}


void
Host::addClientClass6(const std::string& class_name) {
    addClientClassInternal(dhcp6_client_classes_, class_name);
}

void
Host::addClientClassInternal(ClientClasses& classes,
                             const std::string& class_name) {
    std::string trimmed = util::str::trim(class_name);
    if (!trimmed.empty()) {
        classes.insert(ClientClass(trimmed));
    }
}

void
Host::setNextServer(const asiolink::IOAddress& next_server) {
    if (!next_server.isV4()) {
        isc_throw(isc::BadValue, "next server address '" << next_server
                  << "' is not a valid IPv4 address");
    } else if (next_server.isV4Bcast()) {
        isc_throw(isc::BadValue, "invalid next server address '"
                  << next_server << "'");
    }

    next_server_ = next_server;
}

void
Host::setServerHostname(const std::string& server_host_name) {
    if (server_host_name.size() > Pkt4::MAX_SNAME_LEN - 1) {
        isc_throw(isc::BadValue, "server hostname length must not exceed "
                  << (Pkt4::MAX_SNAME_LEN - 1));
    }
    server_host_name_ = server_host_name;
}

void
Host::setBootFileName(const std::string& boot_file_name) {
    if (boot_file_name.size() > Pkt4::MAX_FILE_LEN - 1) {
        isc_throw(isc::BadValue, "boot file length must not exceed "
                  << (Pkt4::MAX_FILE_LEN - 1));
    }
    boot_file_name_ = boot_file_name;
}

ElementPtr
Host::toElement4() const {

    // Prepare the map
    ElementPtr map = Element::createMap();
    // Set the user context
    contextToElement(map);
    // Set the identifier
    Host::IdentifierType id_type = getIdentifierType();
    if (id_type == Host::IDENT_HWADDR) {
        HWAddrPtr hwaddr = getHWAddress();
        map->set("hw-address", Element::create(hwaddr->toText(false)));
    } else if (id_type == Host::IDENT_DUID) {
        DuidPtr duid = getDuid();
        map->set("duid", Element::create(duid->toText()));
    } else if (id_type == Host::IDENT_CIRCUIT_ID) {
        const std::vector<uint8_t>& bin = getIdentifier();
        std::string circuit_id = util::encode::encodeHex(bin);
        map->set("circuit-id", Element::create(circuit_id));
    } else if (id_type == Host::IDENT_CLIENT_ID) {
        const std::vector<uint8_t>& bin = getIdentifier();
        std::string client_id = util::encode::encodeHex(bin);
        map->set("client-id", Element::create(client_id));
    } else if (id_type == Host::IDENT_FLEX) {
        const std::vector<uint8_t>& bin = getIdentifier();
        std::string flex = util::encode::encodeHex(bin);
        map->set("flex-id", Element::create(flex));
    } else {
        isc_throw(ToElementError, "invalid identifier type: " << id_type);
    }
    // Set the reservation (if not 0.0.0.0 which may not be re-read)
    const IOAddress& address = getIPv4Reservation();
    if (!address.isV4Zero()) {
        map->set("ip-address", Element::create(address.toText()));
    }
    // Set the hostname
    const std::string& hostname = getHostname();
    map->set("hostname", Element::create(hostname));
    // Set next-server
    const IOAddress& next_server = getNextServer();
    map->set("next-server", Element::create(next_server.toText()));
    // Set server-hostname
    const std::string& server_hostname = getServerHostname();
    map->set("server-hostname", Element::create(server_hostname));
    // Set boot-file-name
    const std::string& boot_file_name = getBootFileName();
    map->set("boot-file-name", Element::create(boot_file_name));
    // Set client-classes
    const ClientClasses& cclasses = getClientClasses4();
    ElementPtr classes = Element::createList();
    for (ClientClasses::const_iterator cclass = cclasses.cbegin();
         cclass != cclasses.cend(); ++cclass) {
        classes->add(Element::create(*cclass));
    }
    map->set("client-classes", classes);
    // Set option-data
    ConstCfgOptionPtr opts = getCfgOption4();
    map->set("option-data", opts->toElement());

    return (map);
}

ElementPtr
Host::toElement6() const {
    // Prepare the map
    ElementPtr map = Element::createMap();
    // Set the user context
    contextToElement(map);
    // Set the identifier
    Host::IdentifierType id_type = getIdentifierType();
    if (id_type == Host::IDENT_HWADDR) {
        HWAddrPtr hwaddr = getHWAddress();
        map->set("hw-address", Element::create(hwaddr->toText(false)));
    } else if (id_type == Host::IDENT_DUID) {
        DuidPtr duid = getDuid();
        map->set("duid", Element::create(duid->toText()));
    } else if (id_type == Host::IDENT_CIRCUIT_ID) {
        isc_throw(ToElementError, "unexpected circuit-id DUID type");
    } else if (id_type == Host::IDENT_CLIENT_ID) {
        isc_throw(ToElementError, "unexpected client-id DUID type");
    } else if (id_type == Host::IDENT_FLEX) {
        const std::vector<uint8_t>& bin = getIdentifier();
        std::string flex = util::encode::encodeHex(bin);
        map->set("flex-id", Element::create(flex));
    } else {
        isc_throw(ToElementError, "invalid DUID type: " << id_type);
    }
    // Set reservations (ip-addresses)
    IPv6ResrvRange na_resv = getIPv6Reservations(IPv6Resrv::TYPE_NA);
    ElementPtr resvs = Element::createList();
    for (IPv6ResrvIterator resv = na_resv.first;
         resv != na_resv.second; ++resv) {
        resvs->add(Element::create(resv->second.toText()));
    }
    map->set("ip-addresses", resvs);
    // Set reservations (prefixes)
    IPv6ResrvRange pd_resv = getIPv6Reservations(IPv6Resrv::TYPE_PD);
    resvs = Element::createList();
    for (IPv6ResrvIterator resv = pd_resv.first;
         resv != pd_resv.second; ++resv) {
        resvs->add(Element::create(resv->second.toText()));
    }
    map->set("prefixes", resvs);
    // Set the hostname
    const std::string& hostname = getHostname();
    map->set("hostname", Element::create(hostname));
    // Set client-classes
    const ClientClasses& cclasses = getClientClasses6();
    ElementPtr classes = Element::createList();
    for (ClientClasses::const_iterator cclass = cclasses.cbegin();
         cclass != cclasses.cend(); ++cclass) {
        classes->add(Element::create(*cclass));
    }
    map->set("client-classes", classes);

    // Set option-data
    ConstCfgOptionPtr opts = getCfgOption6();
    map->set("option-data", opts->toElement());

    // Set auth key
    //@todo: uncomment once storing in configuration file is enabled
    //map->set("auth-key", Element::create(getKey().toText()));

    return (map);
}

std::string
Host::toText() const {
    std::ostringstream s;

    // Add HW address or DUID.
    s << getIdentifierAsText();

    // Add IPv4 subnet id if exists.
    if (ipv4_subnet_id_ != SUBNET_ID_UNUSED) {
        s << " ipv4_subnet_id=" << ipv4_subnet_id_;
    }

    // Add IPv6 subnet id if exists.
    if (ipv6_subnet_id_ != SUBNET_ID_UNUSED) {
        s << " ipv6_subnet_id=" << ipv6_subnet_id_;
    }

    // Add hostname.
    s << " hostname=" << (hostname_.empty() ? "(empty)" : hostname_);

    // Add IPv4 reservation.
    s << " ipv4_reservation=" << (ipv4_reservation_.isV4Zero() ? "(no)" :
                                  ipv4_reservation_.toText());

    // Add next server.
    s << " siaddr=" << (next_server_.isV4Zero() ? "(no)" :
                             next_server_.toText());

    // Add server host name.
    s << " sname=" << (server_host_name_.empty() ? "(empty)" : server_host_name_);

    // Add boot file name.
    s << " file=" << (boot_file_name_.empty() ? "(empty)" : boot_file_name_);

    s << " key=" << (key_.toText().empty() ? "(empty)" : key_.toText());

    if (ipv6_reservations_.empty()) {
        s << " ipv6_reservations=(none)";

    } else {
        // Add all IPv6 reservations.
        for (IPv6ResrvIterator resrv = ipv6_reservations_.begin();
             resrv != ipv6_reservations_.end(); ++resrv) {
            s << " ipv6_reservation"
              << std::distance(ipv6_reservations_.begin(), resrv)
              << "=" << resrv->second.toText();
        }
    }

    // Add DHCPv4 client classes.
    for (ClientClasses::const_iterator cclass = dhcp4_client_classes_.cbegin();
         cclass != dhcp4_client_classes_.cend(); ++cclass) {
        s << " dhcp4_class"
          << std::distance(dhcp4_client_classes_.cbegin(), cclass)
          << "=" << *cclass;
    }

    // Add DHCPv6 client classes.
    for (ClientClasses::const_iterator cclass = dhcp6_client_classes_.cbegin();
         cclass != dhcp6_client_classes_.cend(); ++cclass) {
        s << " dhcp6_class"
          << std::distance(dhcp6_client_classes_.cbegin(), cclass)
          << "=" << *cclass;
    }

    // Add negative cached.
    if (negative_) {
        s << " negative cached";
    }

    return (s.str());
}

} // end of namespace isc::dhcp
} // end of namespace isc
