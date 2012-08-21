// Copyright (C) 2012 Internet Systems Consortium, Inc. ("ISC")
//
// Permission to use, copy, modify, and/or distribute this software for any
// purpose with or without fee is hereby granted, provided that the above
// copyright notice and this permission notice appear in all copies.
//
// THE SOFTWARE IS PROVIDED "AS IS" AND ISC DISCLAIMS ALL WARRANTIES WITH
// REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
// AND FITNESS.  IN NO EVENT SHALL ISC BE LIABLE FOR ANY SPECIAL, DIRECT,
// INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
// LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE
// OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
// PERFORMANCE OF THIS SOFTWARE.

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>

#include <boost/date_time/posix_time/posix_time.hpp>

#include <exceptions/exceptions.h>
#include <asiolink/io_address.h>
#include <dhcp/libdhcp++.h>
#include <dhcp/iface_mgr.h>
#include <dhcp/dhcp4.h>
#include "test_control.h"
#include "command_options.h"

using namespace std;
using namespace boost;
using namespace boost::posix_time;
using namespace isc;
using namespace isc::dhcp;
using namespace isc::asiolink;

namespace isc {
namespace perfdhcp {

TestControl::TestControlSocket::TestControlSocket(int socket) :
    socket_(socket),
    addr_("127.0.0.1") {
    initSocketData();
}

TestControl::TestControlSocket::~TestControlSocket() {
    IfaceMgr::instance().closeSockets();
}

void
TestControl::TestControlSocket::initSocketData() {
    const IfaceMgr::IfaceCollection& ifaces =
        IfaceMgr::instance().getIfaces();
    for (IfaceMgr::IfaceCollection::const_iterator it = ifaces.begin();
         it != ifaces.end();
         ++it) {
        const IfaceMgr::SocketCollection& socket_collection =
            it->getSockets();
        for (IfaceMgr::SocketCollection::const_iterator s =
                 socket_collection.begin();
             s != socket_collection.end();
             ++s) {
            if (s->sockfd_ == socket_) {
                iface_ = it->getName();
                ifindex_ = it->getIndex();
                addr_ = s->addr_;
                return;
            }
        }
    }
    isc_throw(BadValue, "interface for for specified socket "
              "descriptor not found");
}

TestControl&
TestControl::instance() {
    static TestControl test_control;
    return (test_control);
}

TestControl::TestControl() :
    send_due_(microsec_clock::universal_time()),
    last_sent_(send_due_),
    transid_gen_(new TransidGenerator()) {
}

bool
TestControl::checkExitConditions() const {
    CommandOptions& options = CommandOptions::instance();
    // Check if we reached maximum number of DISCOVER/SOLICIT sent.
    if (options.getNumRequests().size() > 0) {
        if (options.getIpVersion() == 4) {
            if (getSentPacketsNum(StatsMgr4::XCHG_DO) >=
                options.getNumRequests()[0]) {
                return(true);
            }
        } else if (options.getIpVersion() == 6) {
            if (stats_mgr6_->getSentPacketsNum(StatsMgr6::XCHG_SA) >=
                options.getNumRequests()[0]) {
                return(true);
            }
        }
    }
    // Check if we reached maximum number REQUEST packets.
    if (options.getNumRequests().size() == 2) {
        if (options.getIpVersion() == 4) {
            if (stats_mgr4_->getSentPacketsNum(StatsMgr4::XCHG_RA) >=
                options.getNumRequests()[1]) {
                return(true);
            }
        } else if (options.getIpVersion() == 6) {
            if (stats_mgr6_->getSentPacketsNum(StatsMgr6::XCHG_RR) >=
                options.getNumRequests()[1]) {
                return(true);
            }
        }
    }
    // Check if we reached maximum number of drops of OFFER/ADVERTISE packets.
    if (options.getMaxDrop().size() > 0) {
        if (options.getIpVersion() == 4) {
            if (stats_mgr4_->getDroppedPacketsNum(StatsMgr4::XCHG_DO) >=
                options.getMaxDrop()[0]) {
                return(true);
            }
        } else if (options.getIpVersion() == 6) {
            if (stats_mgr6_->getDroppedPacketsNum(StatsMgr6::XCHG_SA) >=
                options.getMaxDrop()[0]) {
                return(true);
            }
        }
    }
    // Check if we reached maximum number of drops of ACK/REPLY packets.
    if (options.getMaxDrop().size() == 2) {
        if (options.getIpVersion() == 4) {
            if (stats_mgr4_->getDroppedPacketsNum(StatsMgr4::XCHG_RA) >=
                options.getMaxDrop()[1]) {
                return(true);
            }
        } else if (options.getIpVersion() == 6) {
            if (stats_mgr6_->getDroppedPacketsNum(StatsMgr6::XCHG_RR) >=
                options.getMaxDrop()[1]) {
                return(true);
            }
        }
    }
    // Check if we reached maximum drops percentage of OFFER/ADVERTISE packets.
    if (options.getMaxDropPercentage().size() > 0) {
        if (options.getIpVersion() == 4) {
            if ((stats_mgr4_->getSentPacketsNum(StatsMgr4::XCHG_DO) > 10) &&
                ((100. * stats_mgr4_->getDroppedPacketsNum(StatsMgr4::XCHG_DO) /
                 stats_mgr4_->getSentPacketsNum(StatsMgr4::XCHG_DO)) >=
                 options.getMaxDropPercentage()[0])) {
                return(true);
            }
        } else if (options.getIpVersion() == 6) {
            if ((stats_mgr6_->getSentPacketsNum(StatsMgr6::XCHG_SA) > 10) &&
                ((100. * stats_mgr6_->getDroppedPacketsNum(StatsMgr6::XCHG_SA) /
                  stats_mgr6_->getSentPacketsNum(StatsMgr6::XCHG_SA)) >=
                 options.getMaxDropPercentage()[0])) {
                return(true);
            }
        }
    }
    // Check if we reached maximum drops percentage of ACK/REPLY packets.
    if (options.getMaxDropPercentage().size() == 2) {
        if (options.getIpVersion() == 4) {
            if ((stats_mgr4_->getSentPacketsNum(StatsMgr4::XCHG_RA) > 10) &&
                ((100. * stats_mgr4_->getDroppedPacketsNum(StatsMgr4::XCHG_RA) /
                 stats_mgr4_->getSentPacketsNum(StatsMgr4::XCHG_RA)) >=
                 options.getMaxDropPercentage()[0])) {
                return(true);
            }
        } else if (options.getIpVersion() == 6) {
            if ((stats_mgr6_->getSentPacketsNum(StatsMgr6::XCHG_RR) > 10) &&
                ((100. * stats_mgr6_->getDroppedPacketsNum(StatsMgr6::XCHG_RR) /
                  stats_mgr6_->getSentPacketsNum(StatsMgr6::XCHG_RR)) >=
                 options.getMaxDropPercentage()[0])) {
                return(true);
            }
        }
    }
    return(false);
}

OptionPtr
TestControl::factoryElapsedTime6(Option::Universe, uint16_t,
                                 const OptionBuffer& buf) {
    if (buf.size() == 2) {
        return OptionPtr(new Option(Option::V6, D6O_ELAPSED_TIME, buf));
    } else if (buf.size() == 0) {
        return OptionPtr(new Option(Option::V6, D6O_ELAPSED_TIME,
                                    OptionBuffer(2, 0)));
    }
    isc_throw(isc::BadValue,
              "elapsed time option buffer size has to be 0 or 2");
}

OptionPtr
TestControl::factoryGeneric(Option::Universe u, uint16_t type,
                            const OptionBuffer& buf) {
    OptionPtr opt(new Option(u, type, buf));
    return opt;
}

OptionPtr
TestControl::factoryIana6(Option::Universe, uint16_t,
                          const OptionBuffer& buf) {
    const uint8_t buf_array[] = {
        0, 0, 0, 1,                     // IAID = 1
        0, 0, 3600 >> 8, 3600 && 0xff,  // T1 = 3600
        0, 0, 5400 >> 8, 5400 & 0xff,   // T2 = 5400
    };
    OptionBuffer buf_ia_na(buf_array, buf_array + sizeof(buf_array));
    for (int i = 0;  i < buf.size(); ++i) {
        buf_ia_na.push_back(buf[i]);
    }
    return OptionPtr(new Option(Option::V6, D6O_IA_NA, buf_ia_na));
}

OptionPtr
TestControl::factoryRapidCommit6(Option::Universe, uint16_t,
                                 const OptionBuffer&) {
    return OptionPtr(new Option(Option::V6, D6O_RAPID_COMMIT, OptionBuffer()));
}

OptionPtr
TestControl::factoryOptionRequestOption6(Option::Universe,
                                         uint16_t,
                                         const OptionBuffer&) {
    const uint8_t buf_array[] = {
        D6O_NAME_SERVERS,
        D6O_DOMAIN_SEARCH
    };
    OptionBuffer buf_with_options(buf_array, buf_array + sizeof(buf_array));
    return OptionPtr(new Option(Option::V6, D6O_ORO, buf_with_options));
}


OptionPtr
TestControl::factoryRequestList4(Option::Universe u,
                                 uint16_t type,
                                 const OptionBuffer& buf) {
    const uint8_t buf_array[] = {
        DHO_SUBNET_MASK,
        DHO_BROADCAST_ADDRESS,
        DHO_TIME_OFFSET,
        DHO_ROUTERS,
        DHO_DOMAIN_NAME,
        DHO_DOMAIN_NAME_SERVERS,
        DHO_HOST_NAME
    };

    OptionBuffer buf_with_options(buf_array, buf_array + sizeof(buf_array));
    OptionPtr opt(new Option(u, type, buf));
    opt->setData(buf_with_options.begin(), buf_with_options.end());
    return opt;
}

std::vector<uint8_t>
TestControl::generateMacAddress() const {
    CommandOptions& options = CommandOptions::instance();
    uint32_t clients_num = options.getClientsNum();
    if ((clients_num == 0) || (clients_num == 1)) {
        return options.getMacPrefix();
    }
    // Get the base MAC address. We are going to randomize part of it.
    std::vector<uint8_t> mac_addr(options.getMacPrefix());
    if (mac_addr.size() != HW_ETHER_LEN) {
        isc_throw(BadValue, "invalid MAC address prefix specified");
    }
    uint32_t r = random();
    // The random number must be in the range 0..clients_num. This
    // will guarantee that every client has exactly one random MAC
    // address assigned.
    r %= clients_num;
    // Randomize MAC address octets.
    for (std::vector<uint8_t>::iterator it = mac_addr.end() - 1;
         it >= mac_addr.begin();
         --it) {
        // Add the random value to the current octet.
        (*it) += r;
        if (r < 256) {
            // If we are here it means that there is no sense
            // to randomize the remaining octets of MAC address
            // because the following bytes of random value
            // are zero and it will have no effect.
            break;
        }
        // Randomize the next octet with the following
        // byte of random value.
        r >>= 8;
    }
    return mac_addr;
}

std::vector<uint8_t>
TestControl::generateDuid() const {
    CommandOptions& options = CommandOptions::instance();
    uint32_t clients_num = options.getClientsNum();
    if ((clients_num == 0) || (clients_num == 1)) {
        return options.getDuidPrefix();
    }
    // Get the base DUID. We are going to randomize part of it.
    std::vector<uint8_t> duid(options.getDuidPrefix());
    std::vector<uint8_t> mac_addr(generateMacAddress());
    duid.resize(duid.size() - mac_addr.size());
    for (int i = 0; i < mac_addr.size(); ++i) {
        duid.push_back(mac_addr[i]);
    }
    return duid;
}

uint64_t
TestControl::getNextExchangesNum() const {
    CommandOptions& options = CommandOptions::instance();
    // Reset number of exchanges.
    uint64_t due_exchanges = 0;
    // Get current time.
    ptime now(microsec_clock::universal_time());
    // The due time indicates when we should start sending next chunk
    // of packets. If it is already due time, we should calculate
    // how many packets to send.
    if (now >= send_due_) {
        // If rate is specified from the command line we have to
        // synchornize with it.
        if (options.getRate() != 0) {
            time_period period(send_due_, now);
            time_duration duration = period.length();
            // due_factor indicates the number of seconds that
            // sending next chunk of packets will take.
            double due_factor = duration.fractional_seconds() /
                time_duration::ticks_per_second();
            due_factor += duration.total_seconds();
            // Multiplying due_factor by expected rate gives the number
            // of exchanges to be initiated.
            due_exchanges = static_cast<uint64_t>(due_factor * options.getRate());
            // We want to make sure that at least one packet goes out.
            due_exchanges += 1;
            // We should not exceed aggressivity as it could have been
            // restricted from command line.
            if (due_exchanges > options.getAggressivity()) {
                due_exchanges = options.getAggressivity();
            }
        } else {
            // Rate is not specified so we rely on aggressivity
            // which is the number of packets to be sent in
            // one chunk.
            due_exchanges = options.getAggressivity();
        }
        return (due_exchanges);
    }
    return (0);
}

uint64_t
TestControl::getRcvdPacketsNum(const ExchangeType xchg_type) const {
    uint8_t ip_version = CommandOptions::instance().getIpVersion();
    if (ip_version == 4) {
        return(stats_mgr4_->getRcvdPacketsNum(xchg_type));
    }
    return(stats_mgr6_->
           getRcvdPacketsNum(static_cast<StatsMgr6::ExchangeType>(xchg_type)));
}

uint64_t
TestControl::getSentPacketsNum(const ExchangeType xchg_type) const {
    uint8_t ip_version = CommandOptions::instance().getIpVersion();
    if (ip_version == 4) {
        return(stats_mgr4_->getSentPacketsNum(xchg_type));
    }
    return(stats_mgr6_->
           getSentPacketsNum(static_cast<StatsMgr6::ExchangeType>(xchg_type)));
}

void
TestControl::initializeStatsMgr() {
    CommandOptions& options = CommandOptions::instance();
    if (options.getIpVersion() == 4) {
        stats_mgr4_.reset();
        stats_mgr4_ = StatsMgr4Ptr(new StatsMgr4());
        stats_mgr4_->addExchangeStats(StatsMgr4::XCHG_DO);
        if (options.getExchangeMode() == CommandOptions::DORA_SARR) {
            stats_mgr4_->addExchangeStats(StatsMgr4::XCHG_RA);
        }

    } else if (options.getIpVersion() == 6) {
        stats_mgr6_.reset();
        stats_mgr6_ = StatsMgr6Ptr(new StatsMgr6());
        stats_mgr6_->addExchangeStats(StatsMgr6::XCHG_SA);
        if (options.getExchangeMode() == CommandOptions::DORA_SARR) {
            stats_mgr6_->addExchangeStats(StatsMgr6::XCHG_RR);
        }
    }
}

int
TestControl::openSocket(uint16_t port) const {
    CommandOptions& options = CommandOptions::instance();
    std::string localname = options.getLocalName();
    std::string servername = options.getServerName();
    uint8_t family = AF_INET;
    int sock = 0;
    IOAddress remoteaddr(servername);
    if (port == 0) {
        if (options.getIpVersion() == 6) {
            port = DHCP6_CLIENT_PORT;
        } else if (options.getIpVersion() == 4) {
            port = 67; //  TODO: find out why port 68 is wrong here.
        }
    }
    if (options.getIpVersion() == 6) {
        family = AF_INET6;
    }
    // Local name is specified along with '-l' option.
    // It may point to interface name or local address.
    if (!localname.empty()) {
        // CommandOptions should be already aware wether local name
        // is interface name or address because it uses IfaceMgr to
        // scan interfaces and get's their names.
        if (options.isInterface()) {
            sock = IfaceMgr::instance().openSocketFromIface(localname,
                                                            port,
                                                            family);
        } else {
            IOAddress localaddr(localname);
            sock = IfaceMgr::instance().openSocketFromAddress(localaddr,
                                                              port);
        }
    } else if (!servername.empty()) {
        // If only server name is given we will need to try to resolve
        // the local address to bind socket to based on remote address.
        sock = IfaceMgr::instance().openSocketFromRemoteAddress(remoteaddr,
                                                                port);
    }
    if (sock <= 0) {
        isc_throw(BadValue, "unable to open socket to communicate with "
                  "DHCP server");
    }

    // IfaceMgr does not set broadcast option on the socket. We rely
    // on CommandOptions object to find out if socket has to have
    // broadcast enabled.
    if ((options.getIpVersion() == 4) && options.isBroadcast()) {
        int broadcast_enable = 1;
        int ret = setsockopt(sock, SOL_SOCKET, SO_BROADCAST,
                             &broadcast_enable, sizeof(broadcast_enable));
        if (ret < 0) {
            isc_throw(InvalidOperation,
                      "unable to set broadcast option on the socket");
        }
    } else if (options.getIpVersion() == 6) {
        // If remote address is multicast we need to enable it on
        // the socket that has been created.
        asio::ip::address_v6 remote_v6 = remoteaddr.getAddress().to_v6();
        if (remote_v6.is_multicast()) {
            int hops = 1;
            int ret = setsockopt(sock, IPPROTO_IPV6, IPV6_MULTICAST_HOPS,
                                 &hops, sizeof(hops));
            // If user specified interface name with '-l' the
            // IPV6_MULTICAST_IF has to be set.
            if ((ret >= 0)  && options.isInterface()) {
                IfaceMgr::Iface* iface =
                    IfaceMgr::instance().getIface(options.getLocalName());
                if (iface == NULL) {
                    isc_throw(Unexpected, "unknown interface "
                              << options.getLocalName());
                }
                int idx = iface->getIndex();
                ret = setsockopt(sock, IPPROTO_IPV6, IPV6_MULTICAST_IF,
                                     &idx, sizeof(idx));
            }
            if (ret < 0) {
                isc_throw(InvalidOperation,
                          "unable to enable multicast on socket " <<  sock
                          << ". errno = " << errno);
            }
        }
    }

    return(sock);
}

void
TestControl::printRate() const {
    double rate = 0;
    CommandOptions& options = CommandOptions::instance();
    if (options.getIpVersion() == 4) {
        double duration =
            stats_mgr4_->getTestPeriod().length().total_nanoseconds() / 1e9;
        rate = stats_mgr4_->getRcvdPacketsNum(StatsMgr4::XCHG_DO) / duration;
    } else if (options.getIpVersion() == 6) {
        double duration =
            stats_mgr6_->getTestPeriod().length().total_nanoseconds() / 1e9;
        rate = stats_mgr6_->getRcvdPacketsNum(StatsMgr6::XCHG_SA) / duration;
    }
    std::cout << "***Rate statistics***" << std::endl;
    if (options.getRate() > 0) {
        std::cout << "Rate: " << rate << ", expected rate: "
                  << options.getRate() << std::endl << std::endl;
    } else {
        std::cout << "Rate: " << rate << std::endl << std::endl;
    }
}

void
TestControl::printStats() const {
    printRate();
    CommandOptions& options = CommandOptions::instance();
    if (options.getIpVersion() == 4) {
        if (!stats_mgr4_) {
            isc_throw(InvalidOperation, "Statistics Manager for DHCPv4 "
                      "hasn't been initialized");
        }
        stats_mgr4_->printStats();
    } else if (options.getIpVersion() == 6) {
        if (!stats_mgr6_) {
            isc_throw(InvalidOperation, "Statistics Manager for DHCPv6 "
                      "hasn't been initialized");
        }
        stats_mgr6_->printStats();
    }
}

void
TestControl::receivePacket4(const TestControlSocket&,
                            const Pkt4Ptr& pkt4) {
    switch(pkt4->getType()) {
    case DHCPOFFER :
        stats_mgr4_->passRcvdPacket(StatsMgr4::XCHG_DO, pkt4);
        break;
    case DHCPACK :
        stats_mgr4_->passRcvdPacket(StatsMgr4::XCHG_RA, pkt4);
        break;
    default:
        isc_throw(BadValue, "unknown type " << pkt4->getType()
                  << " of received DHCPv4 packet");
    }
}

void
TestControl::receivePacket6(const TestControlSocket& socket,
                            const Pkt6Ptr& pkt6) {
    uint8_t packet_type = pkt6->getType();
    if (packet_type == DHCPV6_ADVERTISE) {
        Pkt6Ptr solicit_pkt6(stats_mgr6_->passRcvdPacket(StatsMgr6::XCHG_SA,
                                                         pkt6));
        if (solicit_pkt6) {
            sendRequest6(socket, solicit_pkt6, pkt6);
        }
    } else if (packet_type == DHCPV6_REPLY) {
        stats_mgr6_->passRcvdPacket(StatsMgr6::XCHG_RR, pkt6);
    } else {
        isc_throw(BadValue, "unknown type " << pkt6->getType()
                  << " of received DHCPv6 packet");
    }
}

void
TestControl::receivePackets(const TestControlSocket& socket) {
    int timeout = 0;
    bool receiving = true;
    while (receiving) {
        if (CommandOptions::instance().getIpVersion() == 4) {
            Pkt4Ptr pkt4 = IfaceMgr::instance().receive4(timeout);
            if (!pkt4) {
                receiving = false;
            } else {
                pkt4->unpack();
                receivePacket4(socket, pkt4);
            }
        } else if (CommandOptions::instance().getIpVersion() == 6) {
            Pkt6Ptr pkt6 = IfaceMgr::instance().receive6(timeout);
            if (!pkt6) {
                receiving  = false;
            } else {
                if (pkt6->unpack()) {
                    receivePacket6(socket, pkt6);
                }
            }
        }
    }
}

void
TestControl::registerOptionFactories4() const {
    static bool factories_registered = false;
    if (!factories_registered) {
        // DHCP_MESSAGE_TYPE option factory.
        LibDHCP::OptionFactoryRegister(Option::V4,
                                       DHO_DHCP_MESSAGE_TYPE,
                                       &TestControl::factoryGeneric);
        // DHCP_PARAMETER_REQUEST_LIST option factory.
        LibDHCP::OptionFactoryRegister(Option::V4,
                                       DHO_DHCP_PARAMETER_REQUEST_LIST,
                                       &TestControl::factoryRequestList4);
    }
    factories_registered = true;
}

void
TestControl::registerOptionFactories6() const {
    static bool factories_registered = false;
    if (!factories_registered) {
        LibDHCP::OptionFactoryRegister(Option::V6,
                                       D6O_ELAPSED_TIME,
                                       &TestControl::factoryElapsedTime6);
        LibDHCP::OptionFactoryRegister(Option::V6,
                                       D6O_RAPID_COMMIT,
                                       &TestControl::factoryRapidCommit6);
        LibDHCP::OptionFactoryRegister(Option::V6,
                                       D6O_ORO,
                                       &TestControl::factoryOptionRequestOption6);
        LibDHCP::OptionFactoryRegister(Option::V6,
                                       D6O_CLIENTID,
                                       &TestControl::factoryGeneric);

        LibDHCP::OptionFactoryRegister(Option::V6,
                                       D6O_IA_NA,
                                       &TestControl::factoryIana6);


    }
    factories_registered = true;
}

void
TestControl::registerOptionFactories() const {
    CommandOptions& options = CommandOptions::instance();
    switch(options.getIpVersion()) {
    case 4:
        registerOptionFactories4();
        break;
    case 6:
        registerOptionFactories6();
        break;
    default:
        isc_throw(InvalidOperation, "command line options have to be parsed "
                  "before DHCP option factories can be registered");
    }
}

void
TestControl::run() {
    sent_packets_0_ = 0;
    sent_packets_1_ = 0;
    CommandOptions& options = CommandOptions::instance();
    // Ip version is not set ONLY in case the command options
    // were not parsed. This surely means that parse() function
    // was not called prior to starting the test. This is fatal
    // error.
    if (options.getIpVersion() == 0) {
        isc_throw(InvalidOperation,
                  "command options must be parsed before running a test");
    }
    registerOptionFactories();
    TestControlSocket socket(openSocket());

    initializeStatsMgr();
    uint64_t packets_sent = 0;
    for (;;) {
        updateSendDue();
        if (checkExitConditions()) {
            break;
        }
        uint64_t packets_due = getNextExchangesNum();

        receivePackets(socket);

        for (uint64_t i = packets_due; i > 0; --i) {
            if (options.getIpVersion() == 4) {
                sendDiscover4(socket);
            } else {
                sendSolicit6(socket);
            }
            ++packets_sent;
        }
    }
    printStats();
}

void
TestControl::sendDiscover4(const TestControlSocket& socket) {
    ++sent_packets_0_;
    last_sent_ = microsec_clock::universal_time();
    // Generate the MAC address to be passed in the packet.
    std::vector<uint8_t> mac_address = generateMacAddress();
    // Generate trasnaction id to be set for the new exchange.
    const uint32_t transid = generateTransid();
    Pkt4Ptr pkt4(new Pkt4(DHCPDISCOVER, transid));
    if (!pkt4) {
        isc_throw(Unexpected, "failed to create DISCOVER packet");
    }
    // Set options: DHCP_MESSAGE_TYPE and DHCP_PARAMETER_REQUEST_LIST
    OptionBuffer buf_msg_type;
    buf_msg_type.push_back(DHCPDISCOVER);
    pkt4->addOption(Option::factory(Option::V4, DHO_DHCP_MESSAGE_TYPE,
                                    buf_msg_type));
    pkt4->addOption(Option::factory(Option::V4,
                                    DHO_DHCP_PARAMETER_REQUEST_LIST));

    // Set client's and server's ports as well as server's address,
    // and local (relay) address.
    setDefaults4(socket, pkt4);
    pkt4->pack();
    IfaceMgr::instance().send(pkt4);
    if (!stats_mgr4_) {
        isc_throw(InvalidOperation, "Statistics Manager for DHCPv4 "
                  "hasn't been initialized");
    }
    stats_mgr4_->passSentPacket(StatsMgr4::XCHG_DO, pkt4);
}

void
TestControl::sendRequest6(const TestControlSocket& socket,
                          const Pkt6Ptr& solicit_pkt6,
                          const Pkt6Ptr& advertise_pkt6) {
    const uint32_t transid = static_cast<uint32_t>(random() % 0x00FFFFFF);
    Pkt6Ptr pkt6(new Pkt6(DHCPV6_REQUEST, transid));
    // Calculate elapsed time
    ptime solicit_time = solicit_pkt6->getTimestamp();
    ptime advertise_time = advertise_pkt6->getTimestamp();
    if (solicit_time.is_not_a_date_time()) {
        isc_throw(Unexpected, "timestamp was not set for SOLICIT packet");
    }
    if (advertise_time.is_not_a_date_time()) {
        isc_throw(Unexpected, "timestamp was not set for ADVERTISE packet");
    }
    time_period period(solicit_time, advertise_time);
    if (period.is_null()) {
        pkt6->addOption(Option::factory(Option::V6, D6O_ELAPSED_TIME));
    } else {
        OptionBuffer buf();
        const uint32_t elapsed_time = period.length().total_seconds();
        OptionPtr opt_elapsed_time =
            Option::factory(Option::V6, D6O_ELAPSED_TIME);
        opt_elapsed_time->setUint16(static_cast<uint16_t>(elapsed_time));
        pkt6->addOption(opt_elapsed_time);
    }
    OptionPtr opt_clientid = advertise_pkt6->getOption(D6O_CLIENTID);
    if (!opt_clientid) {
        isc_throw(Unexpected, "client id not found in received packet");
    }
    pkt6->addOption(opt_clientid);
    OptionPtr opt_serverid = advertise_pkt6->getOption(D6O_SERVERID);
    if (!opt_serverid) {
        isc_throw(Unexpected, "server id not found in received packet");
    }
    pkt6->addOption(opt_serverid);
    OptionPtr opt_ia_na = advertise_pkt6->getOption(D6O_IA_NA);
    if (!opt_ia_na) {
        isc_throw(Unexpected, "DHCPv6 IA_NA option not found in received "
                  "packet");
    }
    pkt6->addOption(opt_ia_na);
    setDefaults6(socket, pkt6);

    pkt6->pack();
    IfaceMgr::instance().send(pkt6);
    if (!stats_mgr6_) {
        isc_throw(InvalidOperation, "Statistics Manager for DHCPv6 "
                  "hasn't been initialized");
    }
    stats_mgr6_->passSentPacket(StatsMgr6::XCHG_RR, pkt6);
}

void
TestControl::sendSolicit6(const TestControlSocket& socket) {
    ++sent_packets_0_;
    last_sent_ = microsec_clock::universal_time();
    // Generate the MAC address to be passed in the packet.
    std::vector<uint8_t> mac_address = generateMacAddress();
    // Generate DUID to be passed to the packet
    std::vector<uint8_t> duid = generateDuid();
    // Generate trasnaction id to be set for the new exchange.
    const uint32_t transid = generateTransid();
    Pkt6Ptr pkt6(new Pkt6(DHCPV6_SOLICIT, transid));
    if (!pkt6) {
        isc_throw(Unexpected, "failed to create SOLICIT packet");
    }
    pkt6->addOption(Option::factory(Option::V6, D6O_ELAPSED_TIME));
    //    pkt6->addOption(Option::factory(Option::V6, D6O_RAPID_COMMIT));
    pkt6->addOption(Option::factory(Option::V6, D6O_CLIENTID, duid));
    pkt6->addOption(Option::factory(Option::V6, D6O_ORO));
    pkt6->addOption(Option::factory(Option::V6, D6O_IA_NA));

    setDefaults6(socket, pkt6);
    pkt6->pack();
    IfaceMgr::instance().send(pkt6);
    if (!stats_mgr6_) {
        isc_throw(InvalidOperation, "Statistics Manager for DHCPv6 "
                  "hasn't been initialized");
    }
    stats_mgr6_->passSentPacket(StatsMgr6::XCHG_SA, pkt6);
}

void
TestControl::setDefaults4(const TestControlSocket& socket,
                          const Pkt4Ptr& pkt) {
    CommandOptions& options = CommandOptions::instance();
    // Interface name.
    pkt->setIface(socket.getIface());
    // Interface index.
    pkt->setIndex(socket.getIfIndex());
    // Local client's port (68)
    pkt->setLocalPort(DHCP4_CLIENT_PORT);
    // Server's port (67)
    pkt->setRemotePort(DHCP4_SERVER_PORT);
    // The remote server's name or IP.
    pkt->setRemoteAddr(IOAddress(options.getServerName()));
    // Set local addresss.
    pkt->setLocalAddr(IOAddress(socket.getAddress()));
    // Set relay (GIADDR) address to local address.
    pkt->setGiaddr(IOAddress(socket.getAddress()));
    // Pretend that we have one relay (which is us).
    pkt->setHops(1);
}

void
TestControl::setDefaults6(const TestControlSocket& socket,
                          const Pkt6Ptr& pkt) {
    CommandOptions& options = CommandOptions::instance();
    // Interface name.
    pkt->setIface(socket.getIface());
    // Interface index.
    pkt->setIndex(socket.getIfIndex());
    // Local client's port (547)
    pkt->setLocalPort(DHCP6_CLIENT_PORT);
    // Server's port (548)
    pkt->setRemotePort(DHCP6_SERVER_PORT);
    // Set local address.
    pkt->setLocalAddr(socket.getAddress());
    // The remote server's name or IP.
    pkt->setRemoteAddr(IOAddress(options.getServerName()));
}

void
TestControl::updateSendDue() {
    // If default constructor was called, this should not happen but
    // if somebody has changed default constructor it is better to
    // keep this check.
    if (last_sent_.is_not_a_date_time()) {
        isc_throw(Unexpected, "time of last sent packet not initialized");
    }
    // Get the expected exchange rate.
    CommandOptions& options = CommandOptions::instance();
    int rate = options.getRate();
    // If rate was not specified we will wait just one clock tick to
    // send next packet. This simulates best effort conditions.
    long duration = 1;
    if (rate != 0) {
        // We use number of ticks instead of nanoseconds because
        // nanosecond resolution may not be available on some
        // machines. Number of ticks guarantees the highest possible
        // timer resolution.
        duration = time_duration::ticks_per_second() / rate;
    }
    // Calculate due time to initate next chunk of exchanges.
    send_due_ = last_sent_ + time_duration(0, 0, 0, duration);
}


} // namespace perfdhcp
} // namespace isc
