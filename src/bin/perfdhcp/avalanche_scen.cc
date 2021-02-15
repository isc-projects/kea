// Copyright (C) 2012-2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

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
    const StatsMgr& stats_mgr(tc_.getStatsMgr());

    // get list of sent packets that potentially need to be resent
    auto sent_packets_its = stats_mgr.getSentPackets(xchg_type);
    auto begin_it = std::get<0>(sent_packets_its);
    auto end_it = std::get<1>(sent_packets_its);

    auto& retrans = retransmissions_[xchg_type];
    auto& start_times = start_times_[xchg_type];

    int still_left_cnt = 0;
    int current_cycle_resent_cnt = 0;
    for (auto it = begin_it; it != end_it; ++it) {
        still_left_cnt++;

        dhcp::PktPtr pkt = *it;
        auto trans_id = pkt->getTransid();

        // get some things from previous retransmissions
        auto start_time = pkt->getTimestamp();
        int current_pkt_resent_cnt = 0;
        auto r_it = retrans.find(trans_id);
        if (r_it != retrans.end()) {
            start_time = (*start_times.find(trans_id)).second;
            current_pkt_resent_cnt = (*r_it).second;
        } else {
            start_times[trans_id] = start_time;
        }

        // estimate back off time for resending this packet
        int delay = (1 << current_pkt_resent_cnt); // in seconds
        if (delay > 64) {
            delay = 64;
        }
        delay *= 1000;  // to miliseconds
        delay += random() % 2000 - 1000;  // adjust by random from -1000..1000 range

        // if back-off time passed then resend
        auto now = microsec_clock::universal_time();
        if (now - start_time > milliseconds(delay)) {
            current_cycle_resent_cnt++;
            total_resent_++;

            // do resend packet
            if (options_.getIpVersion() == 4) {
                Pkt4Ptr pkt4 = boost::dynamic_pointer_cast<Pkt4>(pkt);
                socket_.send(pkt4);
            } else {
                Pkt6Ptr pkt6 = boost::dynamic_pointer_cast<Pkt6>(pkt);
                socket_.send(pkt6);
            }

            // restore sending time of original packet
            pkt->setTimestamp(start_time);

            current_pkt_resent_cnt++;
            retrans[trans_id] = current_pkt_resent_cnt;
        }
    }
    if (current_cycle_resent_cnt > 0) {
        auto now = microsec_clock::universal_time();
        std::cout << now << " " << xchg_type << ": still waiting for "
                  << still_left_cnt << " answers, resent " << current_cycle_resent_cnt
                  << ", retrying " << retrans.size() << std::endl;
    }
    return still_left_cnt;
}



int
AvalancheScen::run() {
    // First indicated number of DISCOVER packets eg. 4000 are sent.
    // Then in a loop responses to received packets (this is
    // consumeReceivedPackets()) are sent and then for every 200ms it is checked
    // if responses to sent packets were received. If not packets are resent.
    // This happens in resendPackets() method. For each packet it is checked
    // how many times it was already resent and then back off time is calculated:
    // 1, 2, 4, 8, 16, 64 (max) seconds. If estimated time has elapsed
    // from previous sending then the packet is resent. Some stats are collected
    // and printed during runtime. The whole procedure is stopped when
    // all packets got responses.

    uint32_t clients_num = options_.getClientsNum() == 0 ?
        1 : options_.getClientsNum();

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
        // Wait for 200ms between subsequent check for resending.
        // This time taken based on experiments. For times 10-30ms whole scenario
        // time significantly grows. The same for times >200ms. The optimal times
        // are between 50-200ms. \todo more research is needed.
        if (now - prev_cycle_time > milliseconds(200)) { // check if 0.2s elapsed
            prev_cycle_time = now;
            int still_left_cnt = 0;
            still_left_cnt += resendPackets(stage1_xchg_);
            if (options_.getExchangeMode() == CommandOptions::DORA_SARR) {
                still_left_cnt += resendPackets(stage2_xchg_);
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
    if (options_.testDiags('t')) {
        stats_mgr.printTimestamps();
    }

    // Print server id.
    if (options_.testDiags('s') && tc_.serverIdReceived()) {
        std::cout << "Server id: " << tc_.getServerId() << std::endl;
    }

    // Diagnostics flag 'e' means show exit reason.
    if (options_.testDiags('e')) {
        std::cout << "Interrupted" << std::endl;
    }

    // Print any received leases.
    if (options_.testDiags('l')) {
        stats_mgr.printLeases();
    }

    // Calculate total stats.
    int total_sent_pkts = total_resent_; // This holds sent + resent packets counts.
    int total_rcvd_pkts = 0;  // This holds received packets count.
    // Get sent and received counts for DO/SA (stage1) exchange from StatsMgr.
    total_sent_pkts += tc_.getStatsMgr().getSentPacketsNum(stage1_xchg_);
    total_rcvd_pkts += tc_.getStatsMgr().getRcvdPacketsNum(stage1_xchg_);
    // Get sent and received counts for RA/RR (stage2) exchange from StatsMgr
    // if RA/RR was not disabled.
    if (options_.getExchangeMode() == CommandOptions::DORA_SARR) {
        total_sent_pkts += tc_.getStatsMgr().getSentPacketsNum(stage2_xchg_);
        total_rcvd_pkts += tc_.getStatsMgr().getRcvdPacketsNum(stage2_xchg_);
    }

    std::cout << "It took " << duration.length() << " to provision " << clients_num
              << " clients. " << std::endl
              << "Requests sent + resent: " << total_sent_pkts << std::endl
              << "Requests resent: " << total_resent_ << std::endl
              << "Responses received: " << total_rcvd_pkts << std::endl;

    return (0);
}

}  // namespace perfdhcp
}  // namespace isc
