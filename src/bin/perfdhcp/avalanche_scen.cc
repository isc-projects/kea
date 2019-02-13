// Copyright (C) 2012-2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <perfdhcp/avalanche_scen.h>


#include <boost/date_time/posix_time/posix_time.hpp>

using namespace std;
using namespace boost::posix_time;
using namespace isc;
using namespace isc::dhcp;


namespace isc {
namespace perfdhcp {

int
AvalancheScen::resendPackets(ExchangeType xchg_type) {
    CommandOptions& options = CommandOptions::instance();
    const StatsMgr& stats_mgr(tc_.getStatsMgr());
    auto sent_packets_its = stats_mgr.getSentPackets(xchg_type);
    auto begin_it = std::get<0>(sent_packets_its);
    auto end_it = std::get<1>(sent_packets_its);

    auto& retrans = retransmissions_[xchg_type];

    int still_left_cnt = 0;
    int resent_cnt = 0;
    for (auto it = begin_it; it != end_it; ++it) {
        still_left_cnt++;
        dhcp::PktPtr pkt = *it;
        auto trans_id = pkt->getTransid();
        int rx_times = 0;
        auto r_it = retrans.find(trans_id);
        if (r_it != retrans.end()) {
            rx_times = (*r_it).second;
        }

        int delay = (1 << rx_times); // in seconds
        if (delay > 64) {
            delay = 64;
        }
        delay *= 1000;  // to miliseconds
        delay += random() % 2000 - 1000;  // adjust by random from -1000..1000 range
        auto now = microsec_clock::universal_time();
        if (now - pkt->getTimestamp() > milliseconds(delay)) {
            resent_cnt++;
            total_resent_++;

            if (options.getIpVersion() == 4) {
                Pkt4Ptr pkt4 = boost::dynamic_pointer_cast<Pkt4>(pkt);
                IfaceMgr::instance().send(pkt4);
            } else {
                Pkt6Ptr pkt6 = boost::dynamic_pointer_cast<Pkt6>(pkt);
                IfaceMgr::instance().send(pkt6);
            }

            rx_times++;
            retrans[trans_id] = rx_times;
        }
    }
    if (resent_cnt > 0) {
        auto now = microsec_clock::universal_time();
        std::cout << now << " " << xchg_type << ": still waiting for "
                  << still_left_cnt << " answers, resent " << resent_cnt
                  << ", retrying " << retrans.size() << std::endl;
    }
    return still_left_cnt;
}



int
AvalancheScen::run() {
    CommandOptions& options = CommandOptions::instance();

    uint32_t clients_num = options.getClientsNum() == 0 ?
        1 : options.getClientsNum();

    StatsMgr& stats_mgr(tc_.getStatsMgr());

    tc_.start();

    auto start = microsec_clock::universal_time();

    // Initiate new DHCP packet exchanges.
    tc_.sendPackets(clients_num);

    auto now = microsec_clock::universal_time();
    auto prev_cycle_time = now;
    for (;;) {
        // Pull some packets from receiver thread, process them, update some stats
        // and respond to the server if needed.
        tc_.consumeReceivedPackets();

        usleep(100);

        now = microsec_clock::universal_time();
        if (now - prev_cycle_time > milliseconds(200)) { // check if 0.2s elapsed
            prev_cycle_time = now;
            int still_left_cnt = 0;
            if (options.getIpVersion() == 4) {
                still_left_cnt += resendPackets(ExchangeType::DO);
                still_left_cnt += resendPackets(ExchangeType::RA);
            } else {
                still_left_cnt += resendPackets(ExchangeType::SA);
                still_left_cnt += resendPackets(ExchangeType::RR);
            }

            if (still_left_cnt == 0) {
                break;
            }
        }

        if (tc_.interrupted()) {
            break;
        }
    }

    auto stop = microsec_clock::universal_time();
    boost::posix_time::time_period duration(start, stop);

    tc_.stop();

    tc_.printStats();

    // Print packet timestamps
    if (testDiags('t')) {
        stats_mgr.printTimestamps();
    }

    // Print server id.
    if (testDiags('s') && tc_.serverIdReceived()) {
        std::cout << "Server id: " << tc_.getServerId() << std::endl;
    }

    // Diagnostics flag 'e' means show exit reason.
    if (testDiags('e')) {
        std::cout << "Interrupted" << std::endl;
    }

    std::cout << "It took " << duration.length() << " to provision " << clients_num
              << " clients. " << (clients_num * 2 + total_resent_)
              << " packets were sent, " << total_resent_
              << " retransmissions needed, received " << (clients_num * 2)
              << " responses." << std::endl;

    return (0);
}

}
}
