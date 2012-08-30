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


#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

#include <boost/date_time/posix_time/posix_time.hpp>

#include <exceptions/exceptions.h>
#include <asiolink/io_address.h>
#include <dhcp/libdhcp++.h>
#include <dhcp/iface_mgr.h>
#include <dhcp/dhcp4.h>
#include <dhcp/option6_ia.h>
#include "test_control.h"
#include "command_options.h"
#include "perf_pkt4.h"
#include "perf_pkt6.h"

using namespace std;
using namespace boost::posix_time;
using namespace isc;
using namespace isc::dhcp;
using namespace isc::asiolink;

namespace isc {
namespace perfdhcp {

bool TestControl::interrupted_ = false;

TestControl::TestControlSocket::TestControlSocket(const int socket) :
    SocketInfo(socket, asiolink::IOAddress("127.0.0.1"), 0),
    ifindex_(0), valid_(true) {
    try {
        initSocketData();
    } catch (const Exception&) {
        valid_ = false;
    }
}

TestControl::TestControlSocket::~TestControlSocket() {
    IfaceMgr::Iface* iface = IfaceMgr::instance().getIface(ifindex_);
    if (iface) {
        iface->delSocket(sockfd_);
    }
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
            if (s->sockfd_ == sockfd_) {
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

TestControl::TestControl() {
    reset();
}

std::string
TestControl::byte2Hex(const uint8_t b) const {
    const int b1 = b / 16;
    const int b0 = b % 16;
    ostringstream stream;
    stream << std::hex << b1 << b0 << std::dec;
    return (stream.str());
}

bool
TestControl::checkExitConditions() const {
    if (interrupted_) {
        return (true);
    }
    CommandOptions& options = CommandOptions::instance();
    bool test_period_reached = false;
    // Check if test period passed.
    if (options.getPeriod() != 0) {
        if (options.getIpVersion() == 4) {
            time_period period(stats_mgr4_->getTestPeriod());
            if (period.length().total_seconds() >= options.getPeriod()) {
                test_period_reached = true;
            }
        } else if (options.getIpVersion() == 6) {
            time_period period = stats_mgr6_->getTestPeriod();
            if (period.length().total_seconds() >= options.getPeriod()) {
                test_period_reached = true;
            }
        }
    }
    if (test_period_reached) {
        if (testDiags('e')) {
            std::cout << "reached test-period." << std::endl;
        }
        return (true);
    }

    bool max_requests = false;
    // Check if we reached maximum number of DISCOVER/SOLICIT sent.
    if (options.getNumRequests().size() > 0) {
        if (options.getIpVersion() == 4) {
            if (getSentPacketsNum(StatsMgr4::XCHG_DO) >=
                options.getNumRequests()[0]) {
                max_requests = true;
            }
        } else if (options.getIpVersion() == 6) {
            if (stats_mgr6_->getSentPacketsNum(StatsMgr6::XCHG_SA) >=
                options.getNumRequests()[0]) {
                max_requests = true;
            }
        }
    }
    // Check if we reached maximum number REQUEST packets.
    if (options.getNumRequests().size() > 1) {
        if (options.getIpVersion() == 4) {
            if (stats_mgr4_->getSentPacketsNum(StatsMgr4::XCHG_RA) >=
                options.getNumRequests()[1]) {
                max_requests = true;
            }
        } else if (options.getIpVersion() == 6) {
            if (stats_mgr6_->getSentPacketsNum(StatsMgr6::XCHG_RR) >=
                options.getNumRequests()[1]) {
                max_requests = true;
            }
        }
    }
    if (max_requests) {
        if (testDiags('e')) {
            std::cout << "Reached max requests limit." << std::endl;
        }
        return (true);
    }

    // Check if we reached maximum number of drops of OFFER/ADVERTISE packets.
    bool max_drops = false;
    if (options.getMaxDrop().size() > 0) {
        if (options.getIpVersion() == 4) {
            if (stats_mgr4_->getDroppedPacketsNum(StatsMgr4::XCHG_DO) >=
                options.getMaxDrop()[0]) {
                max_drops = true;
            }
        } else if (options.getIpVersion() == 6) {
            if (stats_mgr6_->getDroppedPacketsNum(StatsMgr6::XCHG_SA) >=
                options.getMaxDrop()[0]) {
                max_drops = true;
            }
        }
    }
    // Check if we reached maximum number of drops of ACK/REPLY packets.
    if (options.getMaxDrop().size() > 1) {
        if (options.getIpVersion() == 4) {
            if (stats_mgr4_->getDroppedPacketsNum(StatsMgr4::XCHG_RA) >=
                options.getMaxDrop()[1]) {
                max_drops = true;
            }
        } else if (options.getIpVersion() == 6) {
            if (stats_mgr6_->getDroppedPacketsNum(StatsMgr6::XCHG_RR) >=
                options.getMaxDrop()[1]) {
                max_drops = true;
            }
        }
    }
    if (max_drops) {
        if (testDiags('e')) {
            std::cout << "Reached maximum drops number." << std::endl;
        }
        return (true);
    }

    // Check if we reached maximum drops percentage of OFFER/ADVERTISE packets.
    bool max_pdrops = false;
    if (options.getMaxDropPercentage().size() > 0) {
        if (options.getIpVersion() == 4) {
            if ((stats_mgr4_->getSentPacketsNum(StatsMgr4::XCHG_DO) > 10) &&
                ((100. * stats_mgr4_->getDroppedPacketsNum(StatsMgr4::XCHG_DO) /
                 stats_mgr4_->getSentPacketsNum(StatsMgr4::XCHG_DO)) >=
                 options.getMaxDropPercentage()[0])) {
                max_pdrops = true;

            }
        } else if (options.getIpVersion() == 6) {
            if ((stats_mgr6_->getSentPacketsNum(StatsMgr6::XCHG_SA) > 10) &&
                ((100. * stats_mgr6_->getDroppedPacketsNum(StatsMgr6::XCHG_SA) /
                  stats_mgr6_->getSentPacketsNum(StatsMgr6::XCHG_SA)) >=
                 options.getMaxDropPercentage()[0])) {
                max_pdrops = true;
            }
        }
    }
    // Check if we reached maximum drops percentage of ACK/REPLY packets.
    if (options.getMaxDropPercentage().size() > 1) {
        if (options.getIpVersion() == 4) {
            if ((stats_mgr4_->getSentPacketsNum(StatsMgr4::XCHG_RA) > 10) &&
                ((100. * stats_mgr4_->getDroppedPacketsNum(StatsMgr4::XCHG_RA) /
                 stats_mgr4_->getSentPacketsNum(StatsMgr4::XCHG_RA)) >=
                 options.getMaxDropPercentage()[1])) {
                max_pdrops = true;
            }
        } else if (options.getIpVersion() == 6) {
            if ((stats_mgr6_->getSentPacketsNum(StatsMgr6::XCHG_RR) > 10) &&
                ((100. * stats_mgr6_->getDroppedPacketsNum(StatsMgr6::XCHG_RR) /
                  stats_mgr6_->getSentPacketsNum(StatsMgr6::XCHG_RR)) >=
                 options.getMaxDropPercentage()[1])) {
                max_pdrops = true;
            }
        }
    }
    if (max_pdrops) {
        if (testDiags('e')) {
            std::cout << "Reached maximum percentage of drops." << std::endl;
        }
        return (true);
    }
    return (false);
}

OptionPtr
TestControl::factoryElapsedTime6(Option::Universe, uint16_t,
                                 const OptionBuffer& buf) {
    if (buf.size() == 2) {
        return (OptionPtr(new Option(Option::V6, D6O_ELAPSED_TIME, buf)));
    } else if (buf.size() == 0) {
        return (OptionPtr(new Option(Option::V6, D6O_ELAPSED_TIME,
                                     OptionBuffer(2, 0))));
    }
    isc_throw(isc::BadValue,
              "elapsed time option buffer size has to be 0 or 2");
}

OptionPtr
TestControl::factoryGeneric(Option::Universe u, uint16_t type,
                            const OptionBuffer& buf) {
    OptionPtr opt(new Option(u, type, buf));
    return (opt);
}

OptionPtr
TestControl::factoryIana6(Option::Universe, uint16_t,
                          const OptionBuffer& buf) {
    // @todo allow different values of T1, T2 and IAID.
    const uint8_t buf_array[] = {
        0, 0, 0, 1,                     // IAID = 1
        0, 0, 3600 >> 8, 3600 & 0xff,  // T1 = 3600
        0, 0, 5400 >> 8, 5400 & 0xff,   // T2 = 5400
    };
    OptionBuffer buf_ia_na(buf_array, buf_array + sizeof(buf_array));
    for (int i = 0;  i < buf.size(); ++i) {
        buf_ia_na.push_back(buf[i]);
    }
    return (OptionPtr(new Option(Option::V6, D6O_IA_NA, buf_ia_na)));
}

OptionPtr
TestControl::factoryRapidCommit6(Option::Universe, uint16_t,
                                 const OptionBuffer&) {
    return (OptionPtr(new Option(Option::V6, D6O_RAPID_COMMIT, OptionBuffer())));
}

OptionPtr
TestControl::factoryOptionRequestOption6(Option::Universe,
                                         uint16_t,
                                         const OptionBuffer&) {
    const uint8_t buf_array[] = {
        0, D6O_NAME_SERVERS,
        0, D6O_DOMAIN_SEARCH,
    };
    OptionBuffer buf_with_options(buf_array, buf_array + sizeof(buf_array));
    return (OptionPtr(new Option(Option::V6, D6O_ORO, buf_with_options)));
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
    return (opt);
}

std::vector<uint8_t>
TestControl::generateMacAddress(uint8_t& randomized) const {
    CommandOptions& options = CommandOptions::instance();
    uint32_t clients_num = options.getClientsNum();
    if (clients_num < 2) {
        return (options.getMacTemplate());
    }
    // Get the base MAC address. We are going to randomize part of it.
    std::vector<uint8_t> mac_addr(options.getMacTemplate());
    if (mac_addr.size() != HW_ETHER_LEN) {
        isc_throw(BadValue, "invalid MAC address template specified");
    }
    uint32_t r = macaddr_gen_->generate();
    randomized = 0;
    // Randomize MAC address octets.
    for (std::vector<uint8_t>::iterator it = mac_addr.end() - 1;
         it >= mac_addr.begin();
         --it) {
        // Add the random value to the current octet.
        (*it) += r;
        ++randomized;
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
    return (mac_addr);
}

std::vector<uint8_t>
TestControl::generateDuid(uint8_t& randomized) const {
    CommandOptions& options = CommandOptions::instance();
    uint32_t clients_num = options.getClientsNum();
    if ((clients_num == 0) || (clients_num == 1)) {
        return (options.getDuidTemplate());
    }
    // Get the base DUID. We are going to randomize part of it.
    std::vector<uint8_t> duid(options.getDuidTemplate());
    // @todo: add support for DUIDs of different sizes.
    std::vector<uint8_t> mac_addr(generateMacAddress(randomized));
    duid.resize(duid.size());
    std::copy(mac_addr.begin(), mac_addr.end(),
              duid.begin() + duid.size() - mac_addr.size());
    return (duid);
}

template<class T>
uint32_t
TestControl::getElapsedTime(const T& pkt1, const T& pkt2) {
    using namespace boost::posix_time;
    ptime pkt1_time = pkt1->getTimestamp();
    ptime pkt2_time = pkt2->getTimestamp();
    if (pkt1_time.is_not_a_date_time() ||
        pkt2_time.is_not_a_date_time()) {
        isc_throw(InvalidOperation, "packet timestamp not set");;
    }
    time_period elapsed_period(pkt1_time, pkt2_time);
    if (elapsed_period.is_null()) {
        isc_throw(InvalidOperation, "unable to calculate time elapsed"
                  " between packets");
    }
    return(elapsed_period.length().total_milliseconds());
}


uint64_t
TestControl::getNextExchangesNum() const {
    CommandOptions& options = CommandOptions::instance();
    // Reset number of exchanges.
    uint64_t due_exchanges = 0;
    // Get current time.
    ptime now(microsec_clock::universal_time());
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
            if (due_exchanges == 0) {
                due_exchanges = 1;
            }
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
        return (stats_mgr4_->getRcvdPacketsNum(xchg_type));
    }
    return (stats_mgr6_->
            getRcvdPacketsNum(static_cast<StatsMgr6::ExchangeType>(xchg_type)));
}

uint64_t
TestControl::getSentPacketsNum(const ExchangeType xchg_type) const {
    uint8_t ip_version = CommandOptions::instance().getIpVersion();
    if (ip_version == 4) {
        return (stats_mgr4_->getSentPacketsNum(xchg_type));
    }
    return (stats_mgr6_->
            getSentPacketsNum(static_cast<StatsMgr6::ExchangeType>(xchg_type)));
}

TestControl::TemplateBuffer
TestControl::getTemplateBuffer(const size_t idx) const {
    if (template_buffers_.size() > idx) {
        return (template_buffers_[idx]);
    }
    isc_throw(OutOfRange, "invalid buffer index");
}

void
TestControl::handleChild(int) {
    int status = 0;
    while (wait3(&status, WNOHANG, NULL) > 0) {
        // continue
    }
}

void
TestControl::handleInterrupt(int) {
    interrupted_ = true;
}

void
TestControl::initPacketTemplates() {
    template_buffers_.clear();
    CommandOptions& options = CommandOptions::instance();
    std::vector<std::string> template_files = options.getTemplateFiles();
    for (std::vector<std::string>::const_iterator it = template_files.begin();
         it != template_files.end(); ++it) {
        readPacketTemplate(*it);
    }
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
    if (testDiags('i')) {
        if (options.getIpVersion() == 4) {
            stats_mgr4_->addCustomCounter("latesend", "Late sent packets");
            stats_mgr4_->addCustomCounter("shortwait", "Short waits for packets");
            stats_mgr4_->addCustomCounter("multircvd", "Multiple packets receives");
            //            stats_mgr4_->addCustomCounter("latercvd", "Late received packets");
        } else if (options.getIpVersion() == 6) {
            stats_mgr6_->addCustomCounter("latesend", "Late sent packets");
            stats_mgr6_->addCustomCounter("shortwait", "Short waits for packets");
            stats_mgr6_->addCustomCounter("multircvd", "Multiple packets receives");
            //            stats_mgr6_->addCustomCounter("latercvd", "Late received packets");
        }
    }
}

int
TestControl::openSocket() const {
    CommandOptions& options = CommandOptions::instance();
    std::string localname = options.getLocalName();
    std::string servername = options.getServerName();
    uint16_t port = options.getLocalPort();
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

    return (sock);
}

void
TestControl::printDiagnostics() const {
    CommandOptions& options = CommandOptions::instance();
    if (testDiags('a')) {
        // Print all command line parameters.
        options.printCommandLine();
        // Print MAC and DUID.
        std::cout << "Set MAC to " << vector2Hex(options.getMacTemplate(), "::")
                  << std::endl;
        if (options.getDuidTemplate().size() > 0) {
            std::cout << "Set DUID to " << vector2Hex(options.getDuidTemplate()) << std::endl; 
        }
    }
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
TestControl::printIntermediateStats() {
    CommandOptions& options = CommandOptions::instance();
    int delay = options.getReportDelay();
    ptime now = microsec_clock::universal_time();
    time_period time_since_report(last_report_, now);
    if (time_since_report.length().total_seconds() >= delay) {
        if (options.getIpVersion() == 4) {
            stats_mgr4_->printIntermediateStats();
        } else if (options.getIpVersion() == 6) {
            stats_mgr6_->printIntermediateStats();
        }
        last_report_ = now;
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
        if (testDiags('i')) {
            stats_mgr4_->printCustomCounters();
        }
    } else if (options.getIpVersion() == 6) {
        if (!stats_mgr6_) {
            isc_throw(InvalidOperation, "Statistics Manager for DHCPv6 "
                      "hasn't been initialized");
        }
        stats_mgr6_->printStats();
        if (testDiags('i')) {
            stats_mgr6_->printCustomCounters();
        }
    }
}

std::string
TestControl::vector2Hex(const std::vector<uint8_t>& vec,
                        const std::string& separator /* ="" */) const {
    std::ostringstream stream;
    for (std::vector<uint8_t>::const_iterator it = vec.begin();
         it != vec.end();
         ++it) {
        if (it == vec.begin()) {
            stream << byte2Hex(*it);
        } else {
            stream << separator << byte2Hex(*it);
        }
    }
    return (stream.str());
}

void
TestControl::readPacketTemplate(const std::string& file_name) {
    std::ifstream temp_file;
    temp_file.open(file_name.c_str(), ios::in | ios::binary | ios::ate);
    if (!temp_file.is_open()) {
        isc_throw(BadValue, "unable to open template file " << file_name);
    }
    std::ifstream::pos_type temp_size = temp_file.tellg();
    if (temp_size % 2 != 0) {
        temp_file.close();
        isc_throw(BadValue, "odd number of digits in template file");
    }
    temp_file.seekg(0, ios::beg);
    std::vector<char> hex_digits(temp_size);
    std::vector<uint8_t> binary_stream;
    temp_file.read(&hex_digits[0], temp_size);
    temp_file.close();
    for (int i = 0; i < hex_digits.size(); i += 2) {
        if (!isxdigit(hex_digits[i]) || !isxdigit(hex_digits[i+1])) {
            isc_throw(BadValue, "the '" << hex_digits[i] << hex_digits[i+1]
                      << "' is not hexadecimal digit");
        }
        stringstream s;
        s << "0x" << hex_digits[i] << hex_digits[i+1];
        int b;
        s >> std::hex >> b;
        binary_stream.push_back(static_cast<uint8_t>(b));
    }
    template_buffers_.push_back(binary_stream);
}

void
TestControl::processReceivedPacket4(const TestControlSocket& socket,
                            const Pkt4Ptr& pkt4) {
    if (pkt4->getType() == DHCPOFFER) {
        Pkt4Ptr discover_pkt4(stats_mgr4_->passRcvdPacket(StatsMgr4::XCHG_DO,
                                                          pkt4));
        CommandOptions::ExchangeMode xchg_mode =
            CommandOptions::instance().getExchangeMode();
        if ((xchg_mode == CommandOptions::DORA_SARR) && discover_pkt4) {
            if (template_buffers_.size() < 2) {
                sendRequest4(socket, discover_pkt4, pkt4);
            } else {
                // @todo add defines for packet type index that can be
                // used to access template_buffers_.
                sendRequest4(socket, template_buffers_[1], discover_pkt4, pkt4);
            }
        }
    } else if (pkt4->getType() == DHCPACK) {
        stats_mgr4_->passRcvdPacket(StatsMgr4::XCHG_RA, pkt4);
    }
}

void
TestControl::processReceivedPacket6(const TestControlSocket& socket,
                            const Pkt6Ptr& pkt6) {
    uint8_t packet_type = pkt6->getType();
    if (packet_type == DHCPV6_ADVERTISE) {
        Pkt6Ptr solicit_pkt6(stats_mgr6_->passRcvdPacket(StatsMgr6::XCHG_SA,
                                                         pkt6));
        CommandOptions::ExchangeMode xchg_mode =
            CommandOptions::instance().getExchangeMode();
        if ((xchg_mode == CommandOptions::DORA_SARR) && solicit_pkt6) {
            // \todo check whether received ADVERTISE packet is sane.
            // We might want to check if STATUS_CODE option is non-zero
            // and if there is IAADR option in IA_NA.
            if (template_buffers_.size() < 2) {
                sendRequest6(socket, pkt6);
            } else {
                // @todo add defines for packet type index that can be
                // used to access template_buffers_.
                sendRequest6(socket, template_buffers_[1], pkt6);
            }
        }
    } else if (packet_type == DHCPV6_REPLY) {
        stats_mgr6_->passRcvdPacket(StatsMgr6::XCHG_RR, pkt6);
    }
}

void
TestControl::receivePackets(const TestControlSocket& socket) {
    int timeout = 0;
    bool receiving = true;
    uint64_t received = 0;
    while (receiving) {
        if (CommandOptions::instance().getIpVersion() == 4) {
            Pkt4Ptr pkt4 = IfaceMgr::instance().receive4(timeout);
            if (!pkt4) {
                receiving = false;
            } else {
                ++received;
                if ((received > 1) && testDiags('i')) {
                    stats_mgr4_->incrementCounter("multircvd");
                }
                pkt4->unpack();
                processReceivedPacket4(socket, pkt4);
            }
        } else if (CommandOptions::instance().getIpVersion() == 6) {
            Pkt6Ptr pkt6 = IfaceMgr::instance().receive6(timeout);
            if (!pkt6) {
                receiving  = false;
            } else {
                ++received;
                if ((received > 1) && testDiags('i')) {
                    stats_mgr6_->incrementCounter("multircvd");
                }
                if (pkt6->unpack()) {
                    processReceivedPacket6(socket, pkt6);
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
        // DHCP_SERVER_IDENTIFIER option factory.
        LibDHCP::OptionFactoryRegister(Option::V4,
                                       DHO_DHCP_SERVER_IDENTIFIER,
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
        // D60_ELAPSED_TIME
        LibDHCP::OptionFactoryRegister(Option::V6,
                                       D6O_ELAPSED_TIME,
                                       &TestControl::factoryElapsedTime6);
        // D6O_RAPID_COMMIT
        LibDHCP::OptionFactoryRegister(Option::V6,
                                       D6O_RAPID_COMMIT,
                                       &TestControl::factoryRapidCommit6);
        // D6O_ORO (option request option) factory.
        LibDHCP::OptionFactoryRegister(Option::V6,
                                       D6O_ORO,
                                       &TestControl::factoryOptionRequestOption6);
        // D6O_CLIENTID option factory.
        LibDHCP::OptionFactoryRegister(Option::V6,
                                       D6O_CLIENTID,
                                       &TestControl::factoryGeneric);
        // D6O_SERVERID option factory.
        LibDHCP::OptionFactoryRegister(Option::V6,
                                       D6O_SERVERID,
                                       &TestControl::factoryGeneric);
        // D6O_IA_NA option factory.
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
TestControl::reset() {
    send_due_ = microsec_clock::universal_time();
    last_sent_ = send_due_;
    last_report_ = send_due_;
    transid_gen_.reset();
    // Actual generators will have to be set later on because we need to
    // get command line parameters first.
    setTransidGenerator(NumberGeneratorPtr());
    setMacAddrGenerator(NumberGeneratorPtr());
    first_packet_serverid_.clear();
    interrupted_ = false;
}

void
TestControl::run() {
    // Reset singleton state before test starts.
    reset();

    CommandOptions& options = CommandOptions::instance();
    // Ip version is not set ONLY in case the command options
    // were not parsed. This surely means that parse() function
    // was not called prior to starting the test. This is fatal
    // error.
    if (options.getIpVersion() == 0) {
        isc_throw(InvalidOperation,
                  "command options must be parsed before running a test");
    } else if (options.getIpVersion() == 4) {
        setTransidGenerator(NumberGeneratorPtr(new SequencialGenerator()));
    } else {
        setTransidGenerator(NumberGeneratorPtr(new SequencialGenerator(0x00FFFFFF)));
    }

    uint32_t clients_num = options.getClientsNum() == 0 ?
        1 : options.getClientsNum();
    setMacAddrGenerator(NumberGeneratorPtr(new SequencialGenerator(clients_num)));

    // Diagnostics are command line options mainly.
    printDiagnostics();
    // Option factories have to be registered.
    registerOptionFactories();
    TestControlSocket socket(openSocket());
    if (!socket.valid_) {
        isc_throw(Unexpected, "invalid socket descriptor");
    }
    // Initialize packet templates.
    initPacketTemplates();
    // Initialize randomization seed.
    if (options.isSeeded()) {
        srandom(options.getSeed());
    } else {
        // Seed with current time.
        time_period duration(from_iso_string("20111231T235959"),
                             microsec_clock::universal_time());
        srandom(duration.length().total_seconds()
                + duration.length().fractional_seconds());
    }
    // If user interrupts the program we will exit gracefully.
    signal(SIGINT, TestControl::handleInterrupt);
    // Preload server with number of packets.
    const bool do_preload = true;
    for (int i = 0; i < options.getPreload(); ++i) {
        if (options.getIpVersion() == 4) {
            // No template buffer means no -T option specified.
            // We will build packet ourselves.
            if (template_buffers_.size() == 0) {
                sendDiscover4(socket, do_preload);
            } else {
                // Pick template #0 if Discover is being sent.
                // For Request it would be #1.
                // @todo add defines for packet type index that can be
                // used to access template_buffers_.
                sendDiscover4(socket, template_buffers_[0],
                              do_preload);
            }
        } else if (options.getIpVersion() == 6) {
            // No template buffer means no -T option specified.
            // We will build packet ourselfs.
            if (template_buffers_.size() == 0) {
                sendSolicit6(socket, do_preload);
            } else {
                // Pick template #0 if Solicit is being sent.
                // For Request it would be #1.
                // @todo add defines for packet type index that can be
                // used to access template_buffers_.
                sendSolicit6(socket, template_buffers_[0],
                             do_preload);
            }
        }
    }

    // Fork and run command specified with -w<wrapped-command>
    if (!options.getWrapped().empty()) {
        runWrapped();
    }

    // Initialize Statistics Manager. Release previous if any.
    initializeStatsMgr();
    for (;;) {
        // Calculate send due based on when last exchange was initiated.
        updateSendDue();
        // If test period finished, maximum number of packet drops
        // has been reached or test has been interrupted we have to
        // finish the test.
        if (checkExitConditions()) {
            break;
        }
        // Calculate number of packets to be sent to stay
        // catch up with rate.
        uint64_t packets_due = getNextExchangesNum();
        if ((packets_due == 0) && testDiags('i')) {
            if (options.getIpVersion() == 4) {
                stats_mgr4_->incrementCounter("shortwait");
            } else if (options.getIpVersion() == 6) {
                stats_mgr6_->incrementCounter("shortwait");
            }
        }

        // @todo: set non-zero timeout for packets once we implement
        // microseconds timeout in IfaceMgr.
        receivePackets(socket);
        // Send packets.
        for (uint64_t i = packets_due; i > 0; --i) {
            if (options.getIpVersion() == 4) {
                // No template packets means that no -T option was specified.
                // We have to build packets ourselfs.
                if (template_buffers_.size() == 0) {
                    sendDiscover4(socket);
                } else {
                    // @todo add defines for packet type index that can be
                    // used to access template_buffers_.
                    sendDiscover4(socket, template_buffers_[0]);
                }
            } else {
                // No template packets means that no -T option was specified.
                // We have to build packets ourselfs.
                if (template_buffers_.size() == 0) {
                    sendSolicit6(socket);
                } else {
                    // @todo add defines for packet type index that can be
                    // used to access template_buffers_.
                    sendSolicit6(socket, template_buffers_[0]);
                }
            }
        }
        // Report delay means that user requested printing number
        // of sent/received/dropped packets repeatedly.
        if (options.getReportDelay() > 0) {
            printIntermediateStats();
        }
    }
    printStats();

    if (!options.getWrapped().empty()) {
        const bool do_stop = true;
        runWrapped(do_stop);
    }

    // Print server id.
    if (testDiags('s') && (first_packet_serverid_.size() > 0)) {
        std::cout << "Server id: " << vector2Hex(first_packet_serverid_) << std::endl;
    }
    // Diagnostics flag 'e' means show exit reason.
    if (testDiags('e')) {
        std::cout << "Interrupted" << std::endl;
    }
}

void
TestControl::runWrapped(bool do_stop /*= false */) const {
    CommandOptions& options = CommandOptions::instance();
    if (!options.getWrapped().empty()) {
        pid_t pid = 0;
        signal(SIGCHLD, handleChild);
        pid = fork();
        if (pid < 0) {
            isc_throw(Unexpected, "unable to fork");
        } else if (pid == 0) {
            execlp(options.getWrapped().c_str(), 
                   do_stop ? "stop" : "start",
                   NULL);
        }
    }
}

void
TestControl::sendDiscover4(const TestControlSocket& socket,
                           const bool preload /*= false*/) {
    last_sent_ = microsec_clock::universal_time();
    // Generate the MAC address to be passed in the packet.
    uint8_t randomized = 0;
    std::vector<uint8_t> mac_address = generateMacAddress(randomized);
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

    // Set hardware address
    pkt4->setHWAddr(HTYPE_ETHER, mac_address.size(), mac_address);

    pkt4->pack();
    IfaceMgr::instance().send(pkt4);
    if (!preload) {
        if (!stats_mgr4_) {
            isc_throw(InvalidOperation, "Statistics Manager for DHCPv4 "
                      "hasn't been initialized");
        }
        stats_mgr4_->passSentPacket(StatsMgr4::XCHG_DO, pkt4);
    }
}

void
TestControl::sendDiscover4(const TestControlSocket& socket,
                           const std::vector<uint8_t>& template_buf,
                           const bool preload /* = false */) {
    // last_sent_ has to be updated for each function that initiates
    // new transaction. The packet exchange synchronization relies on this.
    last_sent_ = microsec_clock::universal_time();
    CommandOptions& options = CommandOptions::instance();
    // Get the first argument if mulitple the same arguments specified
    // in the command line. First one refers to DISCOVER packets.
    const uint8_t arg_idx = 0;
    // Generate the MAC address to be passed in the packet.
    uint8_t randomized = 0;
    std::vector<uint8_t> mac_address = generateMacAddress(randomized);
    // Generate trasnaction id to be set for the new exchange.
    const uint32_t transid = generateTransid();
    // Get transaction id offset.
    size_t transid_offset = DHCPV4_TRANSID_OFFSET;
    if (options.getTransactionIdOffset().size() > arg_idx) {
        transid_offset = options.getTransactionIdOffset()[arg_idx];
    }
    // Calculate randomization offset.
    size_t rand_offset = DHCPV4_RANDOMIZATION_OFFSET;
    if (options.getRandomOffset().size() > arg_idx) {
        rand_offset = options.getRandomOffset()[arg_idx];
    }
    // We need to go back by HW_ETHER_LEN (MAC address length)
    // because this offset points to last octet of MAC address.
    rand_offset -= HW_ETHER_LEN + 1;
    // Create temporary buffer with template contents. We will
    // modify this temporary buffer but we don't want to modify
    // the original template.
    std::vector<uint8_t> in_buf(template_buf.begin(),
                                template_buf.end());
    // Check if we are not going out of bounds.
    if (rand_offset + HW_ETHER_LEN > in_buf.size()) {
        isc_throw(OutOfRange, "randomization offset is out of bounds");
    }
    PerfPkt4Ptr pkt4(new PerfPkt4(&in_buf[0], in_buf.size(),
                                  transid_offset,
                                  transid));

    // Replace MAC address in the template with actual MAC address.
    pkt4->writeAt(rand_offset, mac_address.begin(), mac_address.end());
    // Create a packet from the temporary buffer.
    setDefaults4(socket, boost::static_pointer_cast<Pkt4>(pkt4));
    // Pack the input packet buffer to output buffer so as it can
    // be sent to server.
    pkt4->rawPack();
    IfaceMgr::instance().send(boost::static_pointer_cast<Pkt4>(pkt4));
    if (!preload) {
        if (!stats_mgr4_) {
            isc_throw(InvalidOperation, "Statistics Manager for DHCPv4 "
                      "hasn't been initialized");
        }
        // Update packet stats.
        stats_mgr4_->passSentPacket(StatsMgr4::XCHG_DO,
                                    boost::static_pointer_cast<Pkt4>(pkt4));
    }
}

void
TestControl::sendRequest4(const TestControlSocket& socket,
                          const dhcp::Pkt4Ptr& discover_pkt4,
                          const dhcp::Pkt4Ptr& offer_pkt4) {
    const uint32_t transid = generateTransid();
    Pkt4Ptr pkt4(new Pkt4(DHCPREQUEST, transid));
    OptionBuffer buf_msg_type;
    buf_msg_type.push_back(DHCPREQUEST);
    OptionPtr opt_msg_type = Option::factory(Option::V4, DHO_DHCP_MESSAGE_TYPE,
                                             buf_msg_type);
    pkt4->addOption(opt_msg_type);
    if (CommandOptions::instance().isUseFirst() &&
        (first_packet_serverid_.size() > 0)) {
        pkt4->addOption(Option::factory(Option::V4, DHO_DHCP_SERVER_IDENTIFIER,
                                        first_packet_serverid_));
    } else {
        OptionPtr opt_serverid =
            offer_pkt4->getOption(DHO_DHCP_SERVER_IDENTIFIER);
        if (!opt_serverid) {
            isc_throw(BadValue, "there is no SERVER_IDENTIFIER option "
                      << "in OFFER message");
        }
        if (stats_mgr4_->getRcvdPacketsNum(StatsMgr4::XCHG_DO) == 1) {
            first_packet_serverid_ = opt_serverid->getData();
        }
        pkt4->addOption(opt_serverid);
    }

    /// Set client address.
    asiolink::IOAddress yiaddr = offer_pkt4->getYiaddr();
    if (!yiaddr.getAddress().is_v4()) {
        isc_throw(BadValue, "the YIADDR returned in OFFER packet is not "
                  " IPv4 address");
    }
    OptionPtr opt_requested_address =
        OptionPtr(new Option(Option::V4, DHO_DHCP_REQUESTED_ADDRESS,
                             OptionBuffer()));
    opt_requested_address->setUint32(static_cast<uint32_t>(yiaddr));
    pkt4->addOption(opt_requested_address);
    OptionPtr opt_parameter_list =
        Option::factory(Option::V4, DHO_DHCP_PARAMETER_REQUEST_LIST);
    pkt4->addOption(opt_parameter_list);
    // Set client's and server's ports as well as server's address,
    // and local (relay) address.
    setDefaults4(socket, pkt4);

    // Set hardware address
    const uint8_t* chaddr = offer_pkt4->getChaddr();
    std::vector<uint8_t> mac_address(chaddr, chaddr + HW_ETHER_LEN);
    pkt4->setHWAddr(HTYPE_ETHER, mac_address.size(), mac_address);
    // Set elapsed time.
    uint32_t elapsed_time = getElapsedTime<Pkt4Ptr>(discover_pkt4, offer_pkt4);
    pkt4->setSecs(static_cast<uint16_t>(elapsed_time / 1000));
    // Prepare on wire data to send.
    pkt4->pack();
    IfaceMgr::instance().send(pkt4);
    if (!stats_mgr4_) {
        isc_throw(InvalidOperation, "Statistics Manager for DHCPv4 "
                  "hasn't been initialized");
    }
    stats_mgr4_->passSentPacket(StatsMgr4::XCHG_RA, pkt4);
}

void
TestControl::sendRequest4(const TestControlSocket& socket,
                          const std::vector<uint8_t>& template_buf,
                          const dhcp::Pkt4Ptr& discover_pkt4,
                          const dhcp::Pkt4Ptr& offer_pkt4) {
    CommandOptions& options = CommandOptions::instance();
    // Get the second argument if multiple the same arguments specified
    // in the command line. Second one refers to REQUEST packets.
    const uint8_t arg_idx = 1;
    // Generate new transaction id.
    const uint32_t transid = generateTransid();
    // Get transaction id offset.
    size_t transid_offset = DHCPV4_TRANSID_OFFSET;
    if (options.getTransactionIdOffset().size() > arg_idx) {
        transid_offset = options.getTransactionIdOffset()[arg_idx];
    }
    // Get the offset of MAC's last octet.
    size_t rand_offset = DHCPV4_RANDOMIZATION_OFFSET;
    if (options.getRandomOffset().size() > arg_idx) {
        rand_offset = options.getRandomOffset()[arg_idx];
    }
    // We need to go back by HW_ETHER_LEN (MAC address length)
    // because this offset points to last octet of MAC address.
    rand_offset -= HW_ETHER_LEN + 1;
    // Create temporaru buffer from the template.
    std::vector<uint8_t> in_buf(template_buf.begin(),
                                template_buf.end());
    // Check if given randomization offset is not out of bounds.
    if (rand_offset + HW_ETHER_LEN > in_buf.size()) {
        isc_throw(OutOfRange, "randomization offset is out of bounds");
    }

    // Create packet from the temporary buffer.
    PerfPkt4Ptr pkt4(new PerfPkt4(&in_buf[0], in_buf.size(),
                                  transid_offset,
                                  transid));

     // Set hardware address from OFFER packet received.
    const uint8_t* chaddr = offer_pkt4->getChaddr();
    std::vector<uint8_t> mac_address(chaddr, chaddr + HW_ETHER_LEN);
    pkt4->writeAt(rand_offset, mac_address.begin(), mac_address.end());

    // Set elapsed time.
    size_t elp_offset = 0;
    if (options.getElapsedTimeOffset() > 0) {
        elp_offset = options.getElapsedTimeOffset();
    }
    uint32_t elapsed_time = getElapsedTime<Pkt4Ptr>(discover_pkt4, offer_pkt4);
    pkt4->writeValueAt<uint16_t>(elp_offset,
                                 static_cast<uint16_t>(elapsed_time / 1000));

    // Get the actual server id offset.
    size_t sid_offset = DHCPV4_SERVERID_OFFSET;
    if (options.getServerIdOffset() > 0) {
        sid_offset = options.getServerIdOffset();
    }
    if (CommandOptions::instance().isUseFirst() &&
        (first_packet_serverid_.size() > 0)) {
        boost::shared_ptr<LocalizedOption>
            opt_serverid(new LocalizedOption(Option::V4,
                                             DHO_DHCP_SERVER_IDENTIFIER,
                                             first_packet_serverid_,
                                             sid_offset));
        pkt4->addOption(opt_serverid);
    } else {
        // Copy the contents of server identifier received in
        // OFFER packet to put this into REQUEST.
        OptionPtr opt_serverid_offer =
            offer_pkt4->getOption(DHO_DHCP_SERVER_IDENTIFIER);
        if (!opt_serverid_offer) {
            isc_throw(BadValue, "there is no SERVER_IDENTIFIER option "
                      << "in OFFER message");
        }
        boost::shared_ptr<LocalizedOption>
            opt_serverid(new LocalizedOption(Option::V4,
                                             DHO_DHCP_SERVER_IDENTIFIER,
                                             opt_serverid_offer->getData(),
                                             sid_offset));
        pkt4->addOption(opt_serverid);
        if (stats_mgr4_->getRcvdPacketsNum(StatsMgr4::XCHG_DO) == 1) {
            first_packet_serverid_ = opt_serverid_offer->getData();
        }
    }

    /// Set client address.
    asiolink::IOAddress yiaddr = offer_pkt4->getYiaddr();
    if (!yiaddr.getAddress().is_v4()) {
        isc_throw(BadValue, "the YIADDR returned in OFFER packet is not "
                  " IPv4 address");
    }

    // Get the actual offset of requested ip.
    size_t rip_offset = DHCPV4_REQUESTED_IP_OFFSET;
    if (options.getRequestedIpOffset() > 0) {
        rip_offset = options.getRequestedIpOffset();
    }
    // Place requested IP option at specified position (rip_offset).
    boost::shared_ptr<LocalizedOption>
        opt_requested_ip(new LocalizedOption(Option::V4,
                                             DHO_DHCP_REQUESTED_ADDRESS,
                                             OptionBuffer(),
                                             rip_offset));
    // The IOAddress is castable to uint32_t and returns exactly what we need.
    opt_requested_ip->setUint32(static_cast<uint32_t>(yiaddr));
    pkt4->addOption(opt_requested_ip);

    setDefaults4(socket, boost::static_pointer_cast<Pkt4>(pkt4));
    // Prepare on-wire data.
    pkt4->rawPack();
    IfaceMgr::instance().send(boost::static_pointer_cast<Pkt4>(pkt4));
    if (!stats_mgr4_) {
        isc_throw(InvalidOperation, "Statistics Manager for DHCPv4 "
                  "hasn't been initialized");
    }
    // Update packet stats.
    stats_mgr4_->passSentPacket(StatsMgr4::XCHG_RA,
                                boost::static_pointer_cast<Pkt4>(pkt4));
}

void
TestControl::sendRequest6(const TestControlSocket& socket,
                          const Pkt6Ptr& advertise_pkt6) {
    const uint32_t transid = generateTransid();
    Pkt6Ptr pkt6(new Pkt6(DHCPV6_REQUEST, transid));
    // Set elapsed time.
    OptionPtr opt_elapsed_time =
        Option::factory(Option::V6, D6O_ELAPSED_TIME);
    pkt6->addOption(opt_elapsed_time);
    // Set client id.
    OptionPtr opt_clientid = advertise_pkt6->getOption(D6O_CLIENTID);
    if (!opt_clientid) {
        isc_throw(Unexpected, "client id not found in received packet");
    }
    pkt6->addOption(opt_clientid);

    // Use first flags indicates that we want to use the server
    // id captured in fisrt packet.
    if (CommandOptions::instance().isUseFirst() &&
        (first_packet_serverid_.size() > 0)) {
        pkt6->addOption(Option::factory(Option::V6, D6O_SERVERID,
                                        first_packet_serverid_));
    } else {
        OptionPtr opt_serverid = advertise_pkt6->getOption(D6O_SERVERID);
        if (!opt_serverid) {
            isc_throw(Unexpected, "server id not found in received packet");
        }
        if (stats_mgr6_->getRcvdPacketsNum(StatsMgr6::XCHG_SA) == 1) {
            first_packet_serverid_ = opt_serverid->getData();
        }
        pkt6->addOption(opt_serverid);
    }
    // Set IA_NA option.
    OptionPtr opt_ia_na = advertise_pkt6->getOption(D6O_IA_NA);
    if (!opt_ia_na) {
        isc_throw(Unexpected, "DHCPv6 IA_NA option not found in received "
                  "packet");
    }
    pkt6->addOption(opt_ia_na);

    // Set default packet data.
    setDefaults6(socket, pkt6);
    // Prepare on-wire data.
    pkt6->pack();
    IfaceMgr::instance().send(pkt6);
    if (!stats_mgr6_) {
        isc_throw(InvalidOperation, "Statistics Manager for DHCPv6 "
                  "hasn't been initialized");
    }
    stats_mgr6_->passSentPacket(StatsMgr6::XCHG_RR, pkt6);
}

void
TestControl::sendRequest6(const TestControlSocket& socket,
                          const std::vector<uint8_t>& template_buf,
                          const Pkt6Ptr& advertise_pkt6) {
    CommandOptions& options = CommandOptions::instance();
    // Get the second argument if multiple the same arguments specified
    // in the command line. Second one refers to REQUEST packets.
    const uint8_t arg_idx = 1;
    // Generate transaction id.
    const uint32_t transid = generateTransid();
    // Get transaction id offset.
    size_t transid_offset = DHCPV6_TRANSID_OFFSET;
    if (options.getTransactionIdOffset().size() > arg_idx) {
        transid_offset = options.getTransactionIdOffset()[arg_idx];
    }
    PerfPkt6Ptr pkt6(new PerfPkt6(&template_buf[0], template_buf.size(),
                                  transid_offset, transid));
    // Set elapsed time.
    size_t elp_offset = DHCPV6_ELAPSED_TIME_OFFSET;
    if (options.getElapsedTimeOffset() > 0) {
        elp_offset = options.getElapsedTimeOffset();
    }
    boost::shared_ptr<LocalizedOption>
        opt_elapsed_time(new LocalizedOption(Option::V6, D6O_ELAPSED_TIME,
                                             OptionBuffer(), elp_offset));
    pkt6->addOption(opt_elapsed_time);

    // Get the actual server id offset.
    size_t sid_offset = DHCPV6_SERVERID_OFFSET;
    if (options.getServerIdOffset() > 0) {
        sid_offset = options.getServerIdOffset();
    }
    if (CommandOptions::instance().isUseFirst() &&
        (first_packet_serverid_.size() > 0)) {
        boost::shared_ptr<LocalizedOption>
            opt_serverid(new LocalizedOption(Option::V6,
                                             D6O_SERVERID,
                                             first_packet_serverid_,
                                             sid_offset));
        pkt6->addOption(opt_serverid);

    } else {
        // Copy the contents of server identifier received in
        // ADVERTISE packet to put this into REQUEST.
        OptionPtr opt_serverid_advertise =
            advertise_pkt6->getOption(D6O_SERVERID);
        if (!opt_serverid_advertise) {
            isc_throw(BadValue, "there is no SERVERID option "
                      << "in ADVERTISE message");
        }
        boost::shared_ptr<LocalizedOption>
            opt_serverid(new LocalizedOption(Option::V6,
                                             D6O_SERVERID,
                                             opt_serverid_advertise->getData(),
                                             sid_offset));
        pkt6->addOption(opt_serverid);
        if (stats_mgr6_->getRcvdPacketsNum(StatsMgr6::XCHG_SA) == 1) {
            first_packet_serverid_ = opt_serverid_advertise->getData();
        }
    }
    // Set IA_NA
    boost::shared_ptr<Option6IA> opt_ia_na_advertise =
        boost::static_pointer_cast<Option6IA>(advertise_pkt6->getOption(D6O_IA_NA));
    if (!opt_ia_na_advertise) {
        isc_throw(Unexpected, "DHCPv6 IA_NA option not found in received "
                  "packet");
    }
    size_t addr_offset = DHCPV6_IA_NA_OFFSET;
    if (options.getRequestedIpOffset() > 0) {
        addr_offset = options.getRequestedIpOffset();
    }
    boost::shared_ptr<LocalizedOption>
        opt_ia_na(new LocalizedOption(opt_ia_na_advertise, addr_offset));
    if (!opt_ia_na->valid()) {
        isc_throw(BadValue, "Option IA_NA in advertise packet is invalid");
    }
    pkt6->addOption(opt_ia_na);
    // Set server id.
    OptionPtr opt_serverid_advertise = advertise_pkt6->getOption(D6O_SERVERID);
    if (!opt_serverid_advertise) {
        isc_throw(Unexpected, "DHCPV6 SERVERID option not found in received "
                  "packet");
    }
    size_t srvid_offset = DHCPV6_SERVERID_OFFSET;
    if (options.getServerIdOffset() > 0) {
        srvid_offset = options.getServerIdOffset();
    }
    boost::shared_ptr<LocalizedOption>
        opt_serverid(new LocalizedOption(Option::V6, D6O_SERVERID,
                                         opt_serverid_advertise->getData(),
                                         srvid_offset));
    pkt6->addOption(opt_serverid);
    // Get randomization offset.
    size_t rand_offset = DHCPV6_RANDOMIZATION_OFFSET;
    if (options.getRandomOffset().size() > arg_idx) {
        rand_offset = options.getRandomOffset()[arg_idx];
    }
    OptionPtr opt_clientid_advertise = advertise_pkt6->getOption(D6O_CLIENTID);
    if (!opt_clientid_advertise) {
        isc_throw(Unexpected, "DHCPV6 CLIENTID option not found in received packet");
    }
    rand_offset -= (opt_clientid_advertise->len() - 1);
    // Set client id.
    boost::shared_ptr<LocalizedOption>
        opt_clientid(new LocalizedOption(Option::V6, D6O_CLIENTID,
                                         opt_clientid_advertise->getData(),
                                         rand_offset));
    pkt6->addOption(opt_clientid);
    // Set default packet data.
    setDefaults6(socket, pkt6);
    // Prepare on wire data.
    pkt6->rawPack();
    // Send packet.
    IfaceMgr::instance().send(pkt6);
    if (!stats_mgr6_) {
        isc_throw(InvalidOperation, "Statistics Manager for DHCPv6 "
                  "hasn't been initialized");
    }
    // Update packet stats.
    stats_mgr6_->passSentPacket(StatsMgr6::XCHG_RR, pkt6);

}

void
TestControl::sendSolicit6(const TestControlSocket& socket,
                          const bool preload /*= false*/) {
    last_sent_ = microsec_clock::universal_time();
    // Generate DUID to be passed to the packet
    uint8_t randomized = 0;
    std::vector<uint8_t> duid = generateDuid(randomized);
    // Generate trasnaction id to be set for the new exchange.
    const uint32_t transid = generateTransid();
    Pkt6Ptr pkt6(new Pkt6(DHCPV6_SOLICIT, transid));
    if (!pkt6) {
        isc_throw(Unexpected, "failed to create SOLICIT packet");
    }
    pkt6->addOption(Option::factory(Option::V6, D6O_ELAPSED_TIME));
    if (CommandOptions::instance().isRapidCommit()) {
        pkt6->addOption(Option::factory(Option::V6, D6O_RAPID_COMMIT));
    }
    pkt6->addOption(Option::factory(Option::V6, D6O_CLIENTID, duid));
    pkt6->addOption(Option::factory(Option::V6, D6O_ORO));
    pkt6->addOption(Option::factory(Option::V6, D6O_IA_NA));

    setDefaults6(socket, pkt6);
    pkt6->pack();
    IfaceMgr::instance().send(pkt6);
    if (!preload) {
        if (!stats_mgr6_) {
            isc_throw(InvalidOperation, "Statistics Manager for DHCPv6 "
                      "hasn't been initialized");
        }
        stats_mgr6_->passSentPacket(StatsMgr6::XCHG_SA, pkt6);
    }
}

void
TestControl::sendSolicit6(const TestControlSocket& socket,
                          const std::vector<uint8_t>& template_buf,
                          const bool preload /*= false*/) {
    last_sent_ = microsec_clock::universal_time();
    CommandOptions& options = CommandOptions::instance();
    const int arg_idx = 0;
    // Get transaction id offset.
    size_t transid_offset = DHCPV6_TRANSID_OFFSET;
    if (options.getTransactionIdOffset().size() > arg_idx) {
        transid_offset = options.getTransactionIdOffset()[arg_idx];
    }
    // Generate trasnaction id to be set for the new exchange.
    const uint32_t transid = generateTransid();
    // Create packet.
    PerfPkt6Ptr pkt6(new PerfPkt6(&template_buf[0], template_buf.size(),
                                  transid_offset, transid));
    if (!pkt6) {
        isc_throw(Unexpected, "failed to create SOLICIT packet");
    }
    size_t rand_offset = DHCPV6_RANDOMIZATION_OFFSET;
    if (options.getRandomOffset().size() > arg_idx) {
        rand_offset = options.getRandomOffset()[arg_idx];
    }
    // randomized will pick number of bytes randomized so we can
    // just use part of the generated duid and substitude a few bytes
    /// in template.
    uint8_t randomized = 0;
    std::vector<uint8_t> duid = generateDuid(randomized);
    if (rand_offset > template_buf.size()) {
        isc_throw(OutOfRange, "randomization offset is out of bounds");
    }
    // Store random part of the DUID into the packet.
    pkt6->writeAt(rand_offset - randomized + 1,
                  duid.end() - randomized, duid.end());

    // Prepare on-wire data.
    pkt6->rawPack();
    setDefaults6(socket, pkt6);
    // Send solicit packet.
    IfaceMgr::instance().send(pkt6);
    if (!preload) {
        if (!stats_mgr6_) {
            isc_throw(InvalidOperation, "Statistics Manager for DHCPv6 "
                      "hasn't been initialized");
        }
        // Update packet stats.
        stats_mgr6_->passSentPacket(StatsMgr6::XCHG_SA, pkt6);
    }
}


void
TestControl::setDefaults4(const TestControlSocket& socket,
                          const Pkt4Ptr& pkt) {
    CommandOptions& options = CommandOptions::instance();
    // Interface name.
    IfaceMgr::Iface* iface = IfaceMgr::instance().getIface(socket.ifindex_);
    if (iface == NULL) {
        isc_throw(BadValue, "unable to find interface with given index");
    }
    pkt->setIface(iface->getName());
    // Interface index.
    pkt->setIndex(socket.ifindex_);
    // Local client's port (68)
    pkt->setLocalPort(DHCP4_CLIENT_PORT);
    // Server's port (67)
    pkt->setRemotePort(DHCP4_SERVER_PORT);
    // The remote server's name or IP.
    pkt->setRemoteAddr(IOAddress(options.getServerName()));
    // Set local addresss.
    pkt->setLocalAddr(IOAddress(socket.addr_));
    // Set relay (GIADDR) address to local address.
    pkt->setGiaddr(IOAddress(socket.addr_));
    // Pretend that we have one relay (which is us).
    pkt->setHops(1);
}

void
TestControl::setDefaults6(const TestControlSocket& socket,
                          const Pkt6Ptr& pkt) {
    CommandOptions& options = CommandOptions::instance();
    // Interface name.
    IfaceMgr::Iface* iface = IfaceMgr::instance().getIface(socket.ifindex_);
    if (iface == NULL) {
        isc_throw(BadValue, "unable to find interface with given index");
    }
    pkt->setIface(iface->getName());
    // Interface index.
    pkt->setIndex(socket.ifindex_);
    // Local client's port (547)
    pkt->setLocalPort(DHCP6_CLIENT_PORT);
    // Server's port (548)
    pkt->setRemotePort(DHCP6_SERVER_PORT);
    // Set local address.
    pkt->setLocalAddr(socket.addr_);
    // The remote server's name or IP.
    pkt->setRemoteAddr(IOAddress(options.getServerName()));
}

bool
TestControl::testDiags(const char diag) const {
    std::string diags(CommandOptions::instance().getDiags());
    if (diags.find(diag) != std::string::npos) {
        return (true);
    }
    return (false);
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
    // Check if it is already due.
    ptime now(microsec_clock::universal_time());
    // \todo verify if this condition is not too tight. In other words
    // verify if this will not produce too many late sends.
    // We might want to look at this once we are done implementing
    // microsecond timeouts in IfaceMgr.
    if (now > send_due_) {
        if (testDiags('i')) {
            if (options.getIpVersion() == 4) {
                stats_mgr4_->incrementCounter("latesend");
            } else if (options.getIpVersion() == 6) {
                stats_mgr6_->incrementCounter("latesend");
            }
        }
    }
}


} // namespace perfdhcp
} // namespace isc
