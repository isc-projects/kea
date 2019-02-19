// Copyright (C) 2012-2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <perfdhcp/basic_scen.h>


#include <boost/date_time/posix_time/posix_time.hpp>

using namespace std;
using namespace boost::posix_time;
using namespace isc;
using namespace isc::dhcp;


namespace isc {
namespace perfdhcp {


bool
BasicScen::checkExitConditions() {
    if (tc_.interrupted()) {
        return (true);
    }

    const StatsMgr& stats_mgr(tc_.getStatsMgr());

    // Check if test period passed.
    if (options_.getPeriod() != 0) {
        time_period period(stats_mgr.getTestPeriod());
        if (period.length().total_seconds() >= options_.getPeriod()) {
            if (options_.testDiags('e')) {
                std::cout << "reached test-period." << std::endl;
            }
            if (!tc_.waitToExit()) {
                return true;
            }
        }
    }

    bool max_requests = false;
    // Check if we reached maximum number of DISCOVER/SOLICIT sent.
    if (options_.getNumRequests().size() > 0) {
        if (stats_mgr.getSentPacketsNum(stage1_xchg_) >=
            options_.getNumRequests()[0]) {
            max_requests = true;
        }
    }
    // Check if we reached maximum number REQUEST packets.
    if (options_.getNumRequests().size() > 1) {
        if (stats_mgr.getSentPacketsNum(stage2_xchg_) >=
            options_.getNumRequests()[1]) {
            max_requests = true;
        }
    }
    if (max_requests) {
        if (options_.testDiags('e')) {
            std::cout << "Reached max requests limit." << std::endl;
        }
        if (!tc_.waitToExit()) {
            return true;
        }
    }

    // Check if we reached maximum number of drops of OFFER/ADVERTISE packets.
    bool max_drops = false;
    if (options_.getMaxDrop().size() > 0) {
        if (stats_mgr.getDroppedPacketsNum(stage1_xchg_) >=
            options_.getMaxDrop()[0]) {
            max_drops = true;
        }
    }
    // Check if we reached maximum number of drops of ACK/REPLY packets.
    if (options_.getMaxDrop().size() > 1) {
        if (stats_mgr.getDroppedPacketsNum(stage2_xchg_) >=
            options_.getMaxDrop()[1]) {
            max_drops = true;
        }
    }
    if (max_drops) {
        if (options_.testDiags('e')) {
            std::cout << "Reached maximum drops number." << std::endl;
        }
        if (!tc_.waitToExit()) {
            return true;
        }
    }

    // Check if we reached maximum drops percentage of OFFER/ADVERTISE packets.
    bool max_pdrops = false;
    if (options_.getMaxDropPercentage().size() > 0) {
        if ((stats_mgr.getSentPacketsNum(stage1_xchg_) > 10) &&
            ((100. * stats_mgr.getDroppedPacketsNum(stage1_xchg_) /
              stats_mgr.getSentPacketsNum(stage1_xchg_)) >=
             options_.getMaxDropPercentage()[0]))
        {
            max_pdrops = true;
        }
    }
    // Check if we reached maximum drops percentage of ACK/REPLY packets.
    if (options_.getMaxDropPercentage().size() > 1) {
        if ((stats_mgr.getSentPacketsNum(stage2_xchg_) > 10) &&
            ((100. * stats_mgr.getDroppedPacketsNum(stage2_xchg_) /
              stats_mgr.getSentPacketsNum(stage2_xchg_)) >=
             options_.getMaxDropPercentage()[1]))
        {
            max_pdrops = true;
        }
    }
    if (max_pdrops) {
        if (options_.testDiags('e')) {
            std::cout << "Reached maximum percentage of drops." << std::endl;
        }
        if (!tc_.waitToExit()) {
            return true;
        }
    }
    return (false);
}

int
BasicScen::run() {
    StatsMgr& stats_mgr(tc_.getStatsMgr());

    // Preload server with the number of packets.
    if (options_.getPreload() > 0) {
        tc_.sendPackets(options_.getPreload(), true);
    }

    // Fork and run command specified with -w<wrapped-command>
    if (!options_.getWrapped().empty()) {
        tc_.runWrapped();
    }

    tc_.start();

    for (;;) {
        // Calculate number of packets to be sent to stay
        // catch up with rate.
        uint64_t packets_due = basic_rate_control_.getOutboundMessageCount();
        if ((packets_due == 0) && options_.testDiags('i')) {
            stats_mgr.incrementCounter("shortwait");
        }

        // Pull some packets from receiver thread, process them, update some stats
        // and respond to the server if needed.
        auto pkt_count = tc_.consumeReceivedPackets();

        // If there is nothing to do in this loop iteration then do some sleep to make
        // CPU idle for a moment, to not consume 100% CPU all the time
        // but only if it is not that high request rate expected.
        if (options_.getRate() < 10000 && packets_due == 0 && pkt_count == 0) {
            /// @todo: need to implement adaptive time here, so the sleep time
            /// is not fixed, but adjusts to current situation.
            usleep(1);
        }

        // If test period finished, maximum number of packet drops
        // has been reached or test has been interrupted we have to
        // finish the test.
        if (checkExitConditions()) {
            break;
        }

        // Initiate new DHCP packet exchanges.
        tc_.sendPackets(packets_due);

        // If -f<renew-rate> option was specified we have to check how many
        // Renew packets should be sent to catch up with a desired rate.
        if (options_.getRenewRate() != 0) {
            uint64_t renew_packets_due =
                renew_rate_control_.getOutboundMessageCount();

            // Send multiple renews to satisfy the desired rate.
            if (options_.getIpVersion() == 4) {
                tc_.sendMultipleRequests(renew_packets_due);
            } else {
                tc_.sendMultipleMessages6(DHCPV6_RENEW, renew_packets_due);
            }
        }

        // If -F<release-rate> option was specified we have to check how many
        // Release messages should be sent to catch up with a desired rate.
        if ((options_.getIpVersion() == 6) && (options_.getReleaseRate() != 0)) {
            uint64_t release_packets_due =
                release_rate_control_.getOutboundMessageCount();
            // Send Release messages.
            tc_.sendMultipleMessages6(DHCPV6_RELEASE, release_packets_due);
        }

        // Report delay means that user requested printing number
        // of sent/received/dropped packets repeatedly.
        if (options_.getReportDelay() > 0) {
            tc_.printIntermediateStats();
        }

        // If we are sending Renews to the server, the Reply packets are cached
        // so as leases for which we send Renews can be identified. The major
        // issue with this approach is that most of the time we are caching
        // more packets than we actually need. This function removes excessive
        // Reply messages to reduce the memory and CPU utilization. Note that
        // searches in the long list of Reply packets increases CPU utilization.
        tc_.cleanCachedPackets();
    }

    tc_.stop();

    tc_.printStats();

    if (!options_.getWrapped().empty()) {
        // true means that we execute wrapped command with 'stop' argument.
        tc_.runWrapped(true);
    }

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
    // Print packet templates. Even if -T options have not been specified the
    // dynamically build packet will be printed if at least one has been sent.
    if (options_.testDiags('T')) {
        tc_.printTemplates();
    }

    int ret_code = 0;
    // Check if any packet drops occurred.
    ret_code = stats_mgr.droppedPackets() ? 3 : 0;
    return (ret_code);
}


}
}
