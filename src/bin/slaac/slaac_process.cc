// Copyright (C) 2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <asiolink/asio_wrapper.h>
#include <slaac/slaac_process.h>
#include <slaac/slaac_controller.h>
#include <slaac/slaac_log.h>
#include <slaac/nd.h>
#include <slaac/nd_pkt_rs.h>
#include <slaac/nd_pkt_ra.h>
#include <slaac/nd_option_univ_ra.h>
#include <slaac/json.hpp>
#include <process/d_cfg_mgr.h>
#include <asiolink/io_address.h>
#include <asiolink/io_error.h>
#include <cc/command_interpreter.h>
#include <boost/pointer_cast.hpp>
#include <process/config_base.h>
#include <cc/data.h>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/asio/ip/icmp.hpp>
#include <boost/asio/ip/address_v6.hpp>
#include <boost/asio/ip/address.hpp>

#include "nd_pkt_rs.h"
#include "nd_pkt_ra.h"

using namespace isc::asiolink;
using namespace isc::process;
using namespace isc::data;

using namespace boost::asio;

using json = nlohmann::json;

namespace isc {
namespace slaac {

SlaacProcess::SlaacProcess(const char* name,
                           const asiolink::IOServicePtr& io_service) :
    DProcessBase(name, io_service, DCfgMgrBasePtr(new SlaacCfgMgr())),
    req_hdlr_(io_service->get_io_service())
{
}

SlaacProcess::~SlaacProcess() {
}

void
SlaacProcess::init() {
}

void
SlaacProcess::run() {
    LOG_INFO(slaac_logger, SLAAC_STARTED).arg(VERSION);

    try {
        // Register commands.
        SlaacControllerPtr controller =
            boost::dynamic_pointer_cast<SlaacController>(SlaacController::instance());
        controller->registerCommands();

        // Let's process incoming data or expiring timers in a loop until
        // shutdown condition is detected.
        while (!shouldShutdown()) {
            // Remove unused listeners within the main loop because new listeners
            // are created in within a callback method. This avoids removal the
            // listeners within a callback.
            runIO();
        }
        stopIOService();
    } catch (const std::exception& ex) {
        LOG_FATAL(slaac_logger, SLAAC_FAILED).arg(ex.what());
        try {
            stopIOService();
        } catch (...) {
            // Ignore double errors
        }
        isc_throw(DProcessBaseError, "Process run method failed: " << ex.what());
    }

    try {
        // Deregister commands.
        SlaacControllerPtr controller =
            boost::dynamic_pointer_cast<SlaacController>(SlaacController::instance());
        controller->deregisterCommands();
    } catch (const std::exception&) {
        // What to do? Simply ignore...
    }

    LOG_DEBUG(slaac_logger, isc::log::DBGLVL_START_SHUT, SLAAC_RUN_EXIT);
}

size_t
SlaacProcess::runIO() {
    size_t cnt = getIoService()->get_io_service().poll();
    if (!cnt) {
        cnt = getIoService()->get_io_service().run_one();
    }
    return (cnt);
}

isc::data::ConstElementPtr
SlaacProcess::shutdown(isc::data::ConstElementPtr /*args*/) {
    setShutdownFlag(true);
    return (isc::config::createAnswer(0, "Slaac is shutting down"));
}

// vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
RequestHandler::RequestHandler(boost::asio::io_service& io_service):
    socket_(io_service)
{
//    boost::asio::ip::multicast::join_group mo(boost::asio::ip::address_v6::from_string("ff02::2"));
    socket_.open(boost::asio::ip::icmp::socket::protocol_type::v6());
    //socket_.set_option(odtone::net::ip::icmp::filter(true, ND_ROUTER_SOLICIT));
//    socket_.set_option(mo);

    // struct ifreq ifr;
    // memset(&ifr, 0, sizeof(ifr));
    // strncpy(ifr.ifr_name, "enp0s10", sizeof(ifr.ifr_name) - 1);
    // if (setsockopt(socket_.native(), SOL_SOCKET, SO_BINDTODEVICE, (void *)&ifr, sizeof(ifr)) < 0) {
    //     //log_(0, "Cannot bind to specific interface.");
    //     throw("Cannot bind to specific interface.");
    // }

    buffer_.consume(buffer_.size());
}

void
RequestHandler::start_receiving()
{
    socket_.async_receive_from(
                buffer_.prepare(65536),
                endpoint_,
                boost::bind(&RequestHandler::handle_receive, this, _1, _2));
}


void
RequestHandler::handle_receive(const boost::system::error_code &err_code, std::size_t size)
{
    LOG_INFO(slaac_logger, "Received err: %1 size: %2").arg(err_code.message()).arg(size);
    if (err_code) {
        return;
    }

    if (size == 0) {
        return;
    }

    buffer_.commit(size);
    uint8_t buf[size];
    std::istream is(&buffer_);
    is.read((char*)buf, size);

    // check if this is ICMP ND RS
    if (buf[0] == ND_RT_SOL) {
        printf("bingo\n");
        RSPkt rs_pkt(buf, size, IOAddress::IPV6_ZERO_ADDRESS(), IOAddress::IPV6_ZERO_ADDRESS());
        rs_pkt.unpack();
        std::cout << rs_pkt.toText() << std::endl;

        // prepare and send response
        RAPkt ra_pkt(IOAddress::IPV6_ZERO_ADDRESS(), IOAddress::IPV6_ZERO_ADDRESS());
        ra_pkt.setHopLimit(0);
        ra_pkt.setManagedFlag(false);
        ra_pkt.setOtherFlag(false);
        ra_pkt.setRouterLifetime(123);
        ra_pkt.setReachableTime(456);
        ra_pkt.setRetransTimer(789);

        std::string sample = "{"
        "    \"ietf\": {"
        "        \"dns\": {"
        "            \"dnssl\": ["
        "                \"example.com\""
        "            ],"
        "            \"rdnss\": ["
        "                \"2001:db8::1\","
        "                \"2001:db8::2\""
        "            ],"
        "            \"nat64\": {"
        "                \"prefix\": \"64:ff9b::/96\""
        "            }"
        "        }"
        "    }"
        "}";
        json ura_json = json::parse(sample);
        std::vector<uint8_t> cbor = json::to_cbor(ura_json);
        // Pad to 6 modulo 8.
        size_t round = ((cbor.size() + 1) | 7) - 1;
        if (round > cbor.size()) {
            cbor.resize(round, 0);
        }
        OptionUnivRaPtr ura(new OptionUnivRa(cbor));
        ra_pkt.addOption(ura);
        ra_pkt.pack();
        socket_.send_to(buffer(ra_pkt.getBuffer().getData(), ra_pkt.len()), endpoint_);
        std::cout << ra_pkt.toText() << std::endl;
    } else {
        printf("not bingo %d - drop\n", buf[0]);
    }

    start_receiving();
}
// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^


isc::data::ConstElementPtr
SlaacProcess::configure(isc::data::ConstElementPtr config_set,
                            bool check_only) {
    // System reconfiguration often poses an interesting issue whereby the
    // configuration parsing is successful, but an attempt to use a new
    // configuration is not. This will leave us in the inconsistent state
    // when the configuration is in fact only partially applied and the
    // system's ability to operate is impaired. The use of C++ lambda is
    // a way to resolve this problem by injecting the code to the
    // simpleParseConfig which performs an attempt to open new instance
    // of the listener (if required). The lambda code will throw an
    // exception if it fails and cause the simpleParseConfig to rollback
    // configuration changes and report an error.
    ConstElementPtr answer = getCfgMgr()->simpleParseConfig(config_set,
                                                            check_only,
                                                            [this]() {
        SlaacCfgMgrPtr cfg_mgr = boost::dynamic_pointer_cast<SlaacCfgMgr>(getCfgMgr());
        if (!cfg_mgr) {
            isc_throw(Unexpected, "Internal logic error: bad CfgMgr type");
        }

        SlaacConfigPtr ctx = cfg_mgr->getSlaacConfig();

        if (!ctx) {
            isc_throw(Unexpected, "Internal logic error: bad context type");
        }

        /// @todo: Start the actual thing here.

        req_hdlr_.start_receiving();


        std::string interfaces = "eth0 eth1 eth2";

        // Ok, seems we're good to go.
        LOG_INFO(slaac_logger, SLAAC_SERVICE_STARTED).arg(interfaces);

    });

    int rcode = 0;
    config::parseAnswer(rcode, answer);
    return (answer);
}

SlaacCfgMgrPtr
SlaacProcess::getSlaacCfgMgr() {
    return (boost::dynamic_pointer_cast<SlaacCfgMgr>(getCfgMgr()));
}

} // namespace isc::agent
} // namespace isc
