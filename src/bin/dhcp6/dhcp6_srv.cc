// Copyright (C) 2011-2012 Internet Systems Consortium, Inc. ("ISC")
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

#include <config.h>

#include <asiolink/io_address.h>
#include <dhcp/dhcp6.h>
#include <dhcp/duid.h>
#include <dhcp/iface_mgr.h>
#include <dhcp/libdhcp++.h>
#include <dhcp/option6_addrlst.h>
#include <dhcp/option6_ia.h>
#include <dhcp/option6_iaaddr.h>
#include <dhcp/option6_iaaddr.h>
#include <dhcp/option_custom.h>
#include <dhcp/option_int_array.h>
#include <dhcp/pkt6.h>
#include <dhcp6/dhcp6_log.h>
#include <dhcp6/dhcp6_srv.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/lease_mgr.h>
#include <dhcpsrv/lease_mgr_factory.h>
#include <dhcpsrv/subnet.h>
#include <exceptions/exceptions.h>
#include <util/io_utilities.h>
#include <util/range_utilities.h>

#include <boost/foreach.hpp>

#include <stdlib.h>
#include <time.h>

using namespace isc;
using namespace isc::asiolink;
using namespace isc::dhcp;
using namespace isc::util;
using namespace std;

namespace isc {
namespace dhcp {

Dhcpv6Srv::Dhcpv6Srv(uint16_t port, const char* dbconfig)
    : alloc_engine_(), serverid_(), shutdown_(true) {

    LOG_DEBUG(dhcp6_logger, DBG_DHCP6_START, DHCP6_OPEN_SOCKET).arg(port);

    // Initialize objects required for DHCP server operation.
    try {
        // Port 0 is used for testing purposes. It means that the server should
        // not open any sockets at all. Some tests, e.g. configuration parser,
        // require Dhcpv6Srv object, but they don't really need it to do
        // anything. This speed up and simplifies the tests.
        if (port > 0) {
            if (IfaceMgr::instance().countIfaces() == 0) {
                LOG_ERROR(dhcp6_logger, DHCP6_NO_INTERFACES);
                return;
            }
            IfaceMgr::instance().openSockets6(port);
        }

        setServerID();

        // Instantiate LeaseMgr
        LeaseMgrFactory::create(dbconfig);
        LOG_INFO(dhcp6_logger, DHCP6_DB_BACKEND_STARTED)
            .arg(LeaseMgrFactory::instance().getType())
            .arg(LeaseMgrFactory::instance().getName());

        // Instantiate allocation engine
        alloc_engine_.reset(new AllocEngine(AllocEngine::ALLOC_ITERATIVE, 100));

    } catch (const std::exception &e) {
        LOG_ERROR(dhcp6_logger, DHCP6_SRV_CONSTRUCT_ERROR).arg(e.what());
        return;
    }

    // All done, so can proceed
    shutdown_ = false;
}

Dhcpv6Srv::~Dhcpv6Srv() {
    IfaceMgr::instance().closeSockets();

    LeaseMgrFactory::destroy();
}

void Dhcpv6Srv::shutdown() {
    LOG_DEBUG(dhcp6_logger, DBG_DHCP6_BASIC, DHCP6_SHUTDOWN_REQUEST);
    shutdown_ = true;
}

bool Dhcpv6Srv::run() {
    while (!shutdown_) {
        /// @todo: calculate actual timeout to the next event (e.g. lease
        /// expiration) once we have lease database. The idea here is that
        /// it is possible to do everything in a single process/thread.
        /// For now, we are just calling select for 1000 seconds. There
        /// were some issues reported on some systems when calling select()
        /// with too large values. Unfortunately, I don't recall the details.
        int timeout = 1000;

        // client's message and server's response
        Pkt6Ptr query;
        Pkt6Ptr rsp;

        try {
            query = IfaceMgr::instance().receive6(timeout);
        } catch (const std::exception& e) {
            LOG_ERROR(dhcp6_logger, DHCP6_PACKET_RECEIVE_FAIL).arg(e.what());
        }

        if (query) {
            if (!query->unpack()) {
                LOG_DEBUG(dhcp6_logger, DBG_DHCP6_DETAIL,
                          DHCP6_PACKET_PARSE_FAIL);
                continue;
            }
            LOG_DEBUG(dhcp6_logger, DBG_DHCP6_DETAIL, DHCP6_PACKET_RECEIVED)
                      .arg(query->getName());
            LOG_DEBUG(dhcp6_logger, DBG_DHCP6_DETAIL_DATA, DHCP6_QUERY_DATA)
                      .arg(static_cast<int>(query->getType()))
                      .arg(query->getBuffer().getLength())
                      .arg(query->toText());

            try {
                switch (query->getType()) {
                case DHCPV6_SOLICIT:
                    rsp = processSolicit(query);
                    break;

                case DHCPV6_REQUEST:
                    rsp = processRequest(query);
                    break;

                case DHCPV6_RENEW:
                    rsp = processRenew(query);
                    break;

                case DHCPV6_REBIND:
                    rsp = processRebind(query);
                    break;

                case DHCPV6_CONFIRM:
                    rsp = processConfirm(query);
                    break;

                case DHCPV6_RELEASE:
                rsp = processRelease(query);
                break;

                case DHCPV6_DECLINE:
                    rsp = processDecline(query);
                    break;

                case DHCPV6_INFORMATION_REQUEST:
                    rsp = processInfRequest(query);
                    break;

                default:
                    // Only action is to output a message if debug is enabled,
                    // and that will be covered by the debug statement before
                    // the "switch" statement.
                    ;
                }
            } catch (const RFCViolation& e) {
                LOG_DEBUG(dhcp6_logger, DBG_DHCP6_BASIC, DHCP6_REQUIRED_OPTIONS_CHECK_FAIL)
                    .arg(query->getName())
                    .arg(query->getRemoteAddr())
                    .arg(e.what());
            }

            if (rsp) {
                rsp->setRemoteAddr(query->getRemoteAddr());
                rsp->setLocalAddr(query->getLocalAddr());
                rsp->setRemotePort(DHCP6_CLIENT_PORT);
                rsp->setLocalPort(DHCP6_SERVER_PORT);
                rsp->setIndex(query->getIndex());
                rsp->setIface(query->getIface());

                LOG_DEBUG(dhcp6_logger, DBG_DHCP6_DETAIL_DATA,
                          DHCP6_RESPONSE_DATA)
                          .arg(rsp->getType()).arg(rsp->toText());

                if (rsp->pack()) {
                    try {
                        IfaceMgr::instance().send(rsp);
                    } catch (const std::exception& e) {
                        LOG_ERROR(dhcp6_logger, DHCP6_PACKET_SEND_FAIL).arg(e.what());
                    }
                } else {
                    LOG_ERROR(dhcp6_logger, DHCP6_PACK_FAIL);
                }
            }
        }
    }

    return (true);
}

void Dhcpv6Srv::setServerID() {

    /// @todo: DUID should be generated once and then stored, rather
    /// than generated each time

    /// @todo: This code implements support for DUID-LLT (the recommended one).
    /// We should eventually add support for other DUID types: DUID-LL, DUID-EN
    /// and DUID-UUID

    const IfaceMgr::IfaceCollection& ifaces = IfaceMgr::instance().getIfaces();

    // Let's find suitable interface.
    for (IfaceMgr::IfaceCollection::const_iterator iface = ifaces.begin();
         iface != ifaces.end(); ++iface) {
        // All the following checks could be merged into one multi-condition
        // statement, but let's keep them separated as perhaps one day
        // we will grow knobs to selectively turn them on or off. Also,
        // this code is used only *once* during first start on a new machine
        // and then server-id is stored. (or at least it will be once
        // DUID storage is implemente

        // I wish there was a this_is_a_real_physical_interface flag...

        // MAC address should be at least 6 bytes. Although there is no such
        // requirement in any RFC, all decent physical interfaces (Ethernet,
        // WiFi, Infiniband, etc.) have 6 bytes long MAC address. We want to
        // base our DUID on real hardware address, rather than virtual
        // interface that pretends that underlying IP address is its MAC.
        if (iface->getMacLen() < MIN_MAC_LEN) {
            continue;
        }

        // Let's don't use loopback.
        if (iface->flag_loopback_) {
            continue;
        }

        // Let's skip downed interfaces. It is better to use working ones.
        if (!iface->flag_up_) {
            continue;
        }

        // Some interfaces (like lo on Linux) report 6-bytes long
        // MAC adress 00:00:00:00:00:00. Let's not use such weird interfaces
        // to generate DUID.
        if (isRangeZero(iface->getMac(), iface->getMac() + iface->getMacLen())) {
            continue;
        }

        // Ok, we have useful MAC. Let's generate DUID-LLT based on
        // it. See RFC3315, Section 9.2 for details.

        // DUID uses seconds since midnight of 01-01-2000, time() returns
        // seconds since 01-01-1970. DUID_TIME_EPOCH substution corrects that.
        time_t seconds = time(NULL);
        seconds -= DUID_TIME_EPOCH;

        OptionBuffer srvid(8 + iface->getMacLen());
        writeUint16(DUID::DUID_LLT, &srvid[0]);
        writeUint16(HWTYPE_ETHERNET, &srvid[2]);
        writeUint32(static_cast<uint32_t>(seconds), &srvid[4]);
        memcpy(&srvid[0] + 8, iface->getMac(), iface->getMacLen());

        serverid_ = OptionPtr(new Option(Option::V6, D6O_SERVERID,
                                         srvid.begin(), srvid.end()));
        return;
    }

    // If we reached here, there are no suitable interfaces found.
    // Either interface detection is not supported on this platform or
    // this is really weird box. Let's use DUID-EN instead.
    // See Section 9.3 of RFC3315 for details.

    OptionBuffer srvid(12);
    writeUint16(DUID::DUID_EN, &srvid[0]);
    writeUint32(ENTERPRISE_ID_ISC, &srvid[2]);

    // Length of the identifier is company specific. I hereby declare
    // ISC "standard" of 6 bytes long pseudo-random numbers.
    srandom(time(NULL));
    fillRandom(&srvid[6], &srvid[12]);

    serverid_ = OptionPtr(new Option(Option::V6, D6O_SERVERID,
                                     srvid.begin(), srvid.end()));
}

void Dhcpv6Srv::copyDefaultOptions(const Pkt6Ptr& question, Pkt6Ptr& answer) {
    // Add client-id.
    OptionPtr clientid = question->getOption(D6O_CLIENTID);
    if (clientid) {
        answer->addOption(clientid);
    }

    // TODO: Should throw if there is no client-id (except anonymous INF-REQUEST)
}

void Dhcpv6Srv::appendDefaultOptions(const Pkt6Ptr& question, Pkt6Ptr& answer) {
    // add server-id
    answer->addOption(getServerID());

    // Get the subnet object. It holds options to be sent to the client
    // that belongs to the particular subnet.
    Subnet6Ptr subnet = CfgMgr::instance().getSubnet6(question->getRemoteAddr());
    // Warn if subnet is not supported and quit.
    if (!subnet) {
        LOG_WARN(dhcp6_logger, DHCP6_NO_SUBNET_DEF_OPT)
            .arg(question->getRemoteAddr().toText());
        return;
    }

}

void Dhcpv6Srv::appendRequestedOptions(const Pkt6Ptr& question, Pkt6Ptr& answer) {
    // Get the subnet for a particular address.
    Subnet6Ptr subnet = CfgMgr::instance().getSubnet6(question->getRemoteAddr());
    if (!subnet) {
        LOG_WARN(dhcp6_logger, DHCP6_NO_SUBNET_REQ_OPT)
            .arg(question->getRemoteAddr().toText());
        return;
    }

    // Client requests some options using ORO option. Try to
    // get this option from client's message.
    boost::shared_ptr<OptionIntArray<uint16_t> > option_oro =
        boost::dynamic_pointer_cast<OptionIntArray<uint16_t> >(question->getOption(D6O_ORO));
    // Option ORO not found. Don't do anything then.
    if (!option_oro) {
        return;
    }
    // Get the list of options that client requested.
    const std::vector<uint16_t>& requested_opts = option_oro->getValues();
    // Get the list of options configured for a subnet.
    const Subnet::OptionContainer& options = subnet->getOptions();
    const Subnet::OptionContainerTypeIndex& idx = options.get<1>();
    // Try to match requested options with those configured for a subnet.
    // If match is found, append configured option to the answer message.
    BOOST_FOREACH(uint16_t opt, requested_opts) {
        const Subnet::OptionContainerTypeRange& range = idx.equal_range(opt);
        BOOST_FOREACH(Subnet::OptionDescriptor desc, range) {
            answer->addOption(desc.option);
        }
    }
}

OptionPtr Dhcpv6Srv::createStatusCode(uint16_t code, const std::string& text) {
    // @todo This function uses OptionCustom class to manage contents
    // of the data fields. Since this this option is frequently used
    // it may be good to implement dedicated class to avoid performance
    // impact.

    // Get the definition of the option holding status code.
    OptionDefinitionPtr status_code_def =
        LibDHCP::getOptionDef(Option::V6, D6O_STATUS_CODE);
    // This definition is assumed to be initialized in LibDHCP.
    assert(status_code_def);

    // As there is no dedicated class to represent Status Code
    // the OptionCustom class should be returned here.
    boost::shared_ptr<OptionCustom> option_status =
        boost::dynamic_pointer_cast<
            OptionCustom>(status_code_def->optionFactory(Option::V6, D6O_STATUS_CODE));
    assert(option_status);

    // Set status code to 'code' (0 - means data field #0).
    option_status->writeInteger(code, 0);
    // Set a message (1 - means data field #1).
    option_status->writeString(text, 1);
    return (option_status);
}

void Dhcpv6Srv::sanityCheck(const Pkt6Ptr& pkt, RequirementLevel clientid,
                            RequirementLevel serverid) {
    Option::OptionCollection client_ids = pkt->getOptions(D6O_CLIENTID);
    switch (clientid) {
    case MANDATORY:
        if (client_ids.size() != 1) {
            isc_throw(RFCViolation, "Exactly 1 client-id option expected in "
                      << pkt->getName() << ", but " << client_ids.size()
                      << " received");
        }
        break;
    case OPTIONAL:
        if (client_ids.size() > 1) {
            isc_throw(RFCViolation, "Too many (" << client_ids.size()
                      << ") client-id options received in " << pkt->getName());
        }
        break;

    case FORBIDDEN:
        // doesn't make sense - client-id is always allowed
        break;
    }

    Option::OptionCollection server_ids = pkt->getOptions(D6O_SERVERID);
    switch (serverid) {
    case FORBIDDEN:
        if (server_ids.size() > 0) {
            isc_throw(RFCViolation, "Exactly 1 server-id option expected, but "
                      << server_ids.size() << " received in " << pkt->getName());
        }
        break;

    case MANDATORY:
        if (server_ids.size() != 1) {
            isc_throw(RFCViolation, "Invalid number of server-id options received ("
                      << server_ids.size() << "), exactly 1 expected in message "
                      << pkt->getName());
        }
        break;

    case OPTIONAL:
        if (server_ids.size() > 1) {
            isc_throw(RFCViolation, "Too many (" << server_ids.size()
                      << ") server-id options received in " << pkt->getName());
        }
    }
}

Subnet6Ptr Dhcpv6Srv::selectSubnet(const Pkt6Ptr& question) {
    Subnet6Ptr subnet = CfgMgr::instance().getSubnet6(question->getRemoteAddr());

    return (subnet);
}

void Dhcpv6Srv::assignLeases(const Pkt6Ptr& question, Pkt6Ptr& answer) {

    // We need to allocate addresses for all IA_NA options in the client's
    // question (i.e. SOLICIT or REQUEST) message.

    // We need to select a subnet the client is connected in.
    Subnet6Ptr subnet = selectSubnet(question);
    if (!subnet) {
        // This particular client is out of luck today. We do not have
        // information about the subnet he is connected to. This likely means
        // misconfiguration of the server (or some relays). We will continue to
        // process this message, but our response will be almost useless: no
        // addresses or prefixes, no subnet specific configuration etc. The only
        // thing this client can get is some global information (like DNS
        // servers).

        // perhaps this should be logged on some higher level? This is most likely
        // configuration bug.
        LOG_ERROR(dhcp6_logger, DHCP6_SUBNET_SELECTION_FAILED);
    } else {
        LOG_DEBUG(dhcp6_logger, DBG_DHCP6_DETAIL_DATA, DHCP6_SUBNET_SELECTED)
            .arg(subnet->toText());
    }

    // @todo: We should implement Option6Duid some day, but we can do without it
    // just fine for now

    // Let's find client's DUID. Client is supposed to include its client-id
    // option almost all the time (the only exception is an anonymous inf-request,
    // but that is mostly a theoretical case). Our allocation engine needs DUID
    // and will refuse to allocate anything to anonymous clients.
    DuidPtr duid;
    OptionPtr opt_duid = question->getOption(D6O_CLIENTID);
    if (opt_duid) {
        duid = DuidPtr(new DUID(opt_duid->getData()));
    } else {
        LOG_DEBUG(dhcp6_logger, DBG_DHCP6_BASIC, DHCP6_CLIENTID_MISSING);
        // Let's drop the message. This client is not sane.
        isc_throw(RFCViolation, "Mandatory client-id is missing in received message");
    }

    // Now that we have all information about the client, let's iterate over all
    // received options and handle IA_NA options one by one and store our
    // responses in answer message (ADVERTISE or REPLY).
    //
    // @todo: expand this to cover IA_PD and IA_TA once we implement support for
    // prefix delegation and temporary addresses.
    for (Option::OptionCollection::iterator opt = question->options_.begin();
         opt != question->options_.end(); ++opt) {
        switch (opt->second->getType()) {
        case D6O_IA_NA: {
            OptionPtr answer_opt = assignIA_NA(subnet, duid, question,
                                   boost::dynamic_pointer_cast<Option6IA>(opt->second));
            if (answer_opt) {
                answer->addOption(answer_opt);
            }
            break;
        }
        default:
            break;
        }
    }
}

OptionPtr Dhcpv6Srv::assignIA_NA(const Subnet6Ptr& subnet, const DuidPtr& duid,
                                 Pkt6Ptr question, boost::shared_ptr<Option6IA> ia) {
    // If there is no subnet selected for handling this IA_NA, the only thing to do left is
    // to say that we are sorry, but the user won't get an address. As a convenience, we
    // use a different status text to indicate that (compare to the same status code,
    // but different wording below)
    if (!subnet) {
        // Create empty IA_NA option with IAID matching the request.
        // Note that we don't use OptionDefinition class to create this option.
        // This is because we prefer using a constructor of Option6IA that
        // initializes IAID. Otherwise we would have to use setIAID() after
        // creation of the option which has some performance implications.
        boost::shared_ptr<Option6IA> ia_rsp(new Option6IA(D6O_IA_NA, ia->getIAID()));

        // Insert status code NoAddrsAvail.
        ia_rsp->addOption(createStatusCode(STATUS_NoAddrsAvail, "Sorry, no subnet available."));
        return (ia_rsp);
    }

    // Check if the client sent us a hint in his IA_NA. Clients may send an
    // address in their IA_NA options as a suggestion (e.g. the last address
    // they used before).
    boost::shared_ptr<Option6IAAddr> hintOpt = boost::dynamic_pointer_cast<Option6IAAddr>
                                        (ia->getOption(D6O_IAADDR));
    IOAddress hint("::");
    if (hintOpt) {
        hint = hintOpt->getAddress();
    }

    LOG_DEBUG(dhcp6_logger, DBG_DHCP6_DETAIL, DHCP6_PROCESS_IA_NA_REQUEST)
        .arg(duid?duid->toText():"(no-duid)").arg(ia->getIAID())
        .arg(hintOpt?hint.toText():"(no hint)");

    // "Fake" allocation is processing of SOLICIT message. We pretend to do an
    // allocation, but we do not put the lease in the database. That is ok,
    // because we do not guarantee that the user will get that exact lease. If
    // the user selects this server to do actual allocation (i.e. sends REQUEST)
    // it should include this hint. That will help us during the actual lease
    // allocation.
    bool fake_allocation = false;
    if (question->getType() == DHCPV6_SOLICIT) {
        /// @todo: Check if we support rapid commit
        fake_allocation = true;
    }

    // Use allocation engine to pick a lease for this client. Allocation engine
    // will try to honour the hint, but it is just a hint - some other address
    // may be used instead. If fake_allocation is set to false, the lease will
    // be inserted into the LeaseMgr as well.
    Lease6Ptr lease = alloc_engine_->allocateAddress6(subnet, duid, ia->getIAID(),
                                                      hint, fake_allocation);

    // Create IA_NA that we will put in the response.
    // Do not use OptionDefinition to create option's instance so
    // as we can initialize IAID using a constructor.
    boost::shared_ptr<Option6IA> ia_rsp(new Option6IA(D6O_IA_NA, ia->getIAID()));

    if (lease) {
        // We have a lease! Let's wrap its content into IA_NA option
        // with IAADDR suboption.
        LOG_DEBUG(dhcp6_logger, DBG_DHCP6_DETAIL, fake_allocation?
                  DHCP6_LEASE_ADVERT:DHCP6_LEASE_ALLOC)
            .arg(lease->addr_.toText())
            .arg(duid?duid->toText():"(no-duid)")
            .arg(ia->getIAID());

        ia_rsp->setT1(subnet->getT1());
        ia_rsp->setT2(subnet->getT2());

        boost::shared_ptr<Option6IAAddr>
            addr(new Option6IAAddr(D6O_IAADDR,
                                   lease->addr_,
                                   lease->preferred_lft_,
                                   lease->valid_lft_));
        ia_rsp->addOption(addr);

        // It would be possible to insert status code=0(success) as well,
        // but this is considered waste of bandwidth as absence of status
        // code is considered a success.
    } else {
        // Allocation engine did not allocate a lease. The engine logged
        // cause of that failure. The only thing left is to insert
        // status code to pass the sad news to the client.

        LOG_DEBUG(dhcp6_logger, DBG_DHCP6_DETAIL, fake_allocation?
                  DHCP6_LEASE_ADVERT_FAIL:DHCP6_LEASE_ALLOC_FAIL)
            .arg(duid?duid->toText():"(no-duid)")
            .arg(ia->getIAID())
            .arg(subnet->toText());

        ia_rsp->addOption(createStatusCode(STATUS_NoAddrsAvail,
                          "Sorry, no address could be allocated."));
    }
    return (ia_rsp);
}

OptionPtr Dhcpv6Srv::renewIA_NA(const Subnet6Ptr& subnet, const DuidPtr& duid,
                                Pkt6Ptr question, boost::shared_ptr<Option6IA> ia) {
    Lease6Ptr lease = LeaseMgrFactory::instance().getLease6(*duid, ia->getIAID(),
                                                            subnet->getID());

    if (!lease) {
        // client renewing a lease that we don't know about.

        // Create empty IA_NA option with IAID matching the request.
        boost::shared_ptr<Option6IA> ia_rsp(new Option6IA(D6O_IA_NA, ia->getIAID()));

        // Insert status code NoAddrsAvail.
        ia_rsp->addOption(createStatusCode(STATUS_NoAddrsAvail,
                          "Sorry, no known leases for this duid/iaid."));

        LOG_DEBUG(dhcp6_logger, DBG_DHCP6_DETAIL, DHCP6_UNKNOWN_RENEW)
            .arg(duid->toText())
            .arg(ia->getIAID())
            .arg(subnet->toText());

        return (ia_rsp);
    }

    lease->preferred_lft_ = subnet->getPreferred();
    lease->valid_lft_ = subnet->getValid();
    lease->t1_ = subnet->getT1();
    lease->t2_ = subnet->getT2();
    lease->cltt_ = time(NULL);

    LeaseMgrFactory::instance().updateLease6(lease);

    // Create empty IA_NA option with IAID matching the request.
    boost::shared_ptr<Option6IA> ia_rsp(new Option6IA(D6O_IA_NA, ia->getIAID()));

    ia_rsp->setT1(subnet->getT1());
    ia_rsp->setT2(subnet->getT2());

    boost::shared_ptr<Option6IAAddr> addr(new Option6IAAddr(D6O_IAADDR,
                                          lease->addr_, lease->preferred_lft_,
                                          lease->valid_lft_));
    ia_rsp->addOption(addr);
    return (ia_rsp);
}

void Dhcpv6Srv::renewLeases(const Pkt6Ptr& renew, Pkt6Ptr& reply) {

    // We need to renew addresses for all IA_NA options in the client's
    // RENEW message.

    // We need to select a subnet the client is connected in.
    Subnet6Ptr subnet = selectSubnet(renew);
    if (!subnet) {
        // This particular client is out of luck today. We do not have
        // information about the subnet he is connected to. This likely means
        // misconfiguration of the server (or some relays). We will continue to
        // process this message, but our response will be almost useless: no
        // addresses or prefixes, no subnet specific configuration etc. The only
        // thing this client can get is some global information (like DNS
        // servers).

        // perhaps this should be logged on some higher level? This is most likely
        // configuration bug.
        LOG_ERROR(dhcp6_logger, DHCP6_SUBNET_SELECTION_FAILED);
    } else {
        LOG_DEBUG(dhcp6_logger, DBG_DHCP6_DETAIL_DATA, DHCP6_SUBNET_SELECTED)
            .arg(subnet->toText());
    }

    // Let's find client's DUID. Client is supposed to include its client-id
    // option almost all the time (the only exception is an anonymous inf-request,
    // but that is mostly a theoretical case). Our allocation engine needs DUID
    // and will refuse to allocate anything to anonymous clients.
    OptionPtr opt_duid = renew->getOption(D6O_CLIENTID);
    if (!opt_duid) {
        // This should not happen. We have checked this before.
        reply->addOption(createStatusCode(STATUS_UnspecFail,
                         "You did not include mandatory client-id"));
        return;
    }
    DuidPtr duid(new DUID(opt_duid->getData()));

    for (Option::OptionCollection::iterator opt = renew->options_.begin();
         opt != renew->options_.end(); ++opt) {
        switch (opt->second->getType()) {
        case D6O_IA_NA: {
            OptionPtr answer_opt = renewIA_NA(subnet, duid, renew,
                                   boost::dynamic_pointer_cast<Option6IA>(opt->second));
            if (answer_opt) {
                reply->addOption(answer_opt);
            }
            break;
        }
        default:
            break;
        }
    }



}

Pkt6Ptr Dhcpv6Srv::processSolicit(const Pkt6Ptr& solicit) {

    sanityCheck(solicit, MANDATORY, FORBIDDEN);

    Pkt6Ptr advertise(new Pkt6(DHCPV6_ADVERTISE, solicit->getTransid()));

    copyDefaultOptions(solicit, advertise);
    appendDefaultOptions(solicit, advertise);
    appendRequestedOptions(solicit, advertise);

    assignLeases(solicit, advertise);

    return (advertise);
}

Pkt6Ptr Dhcpv6Srv::processRequest(const Pkt6Ptr& request) {

    sanityCheck(request, MANDATORY, MANDATORY);

    Pkt6Ptr reply(new Pkt6(DHCPV6_REPLY, request->getTransid()));

    copyDefaultOptions(request, reply);
    appendDefaultOptions(request, reply);
    appendRequestedOptions(request, reply);

    assignLeases(request, reply);

    return (reply);
}

Pkt6Ptr Dhcpv6Srv::processRenew(const Pkt6Ptr& renew) {

    sanityCheck(renew, MANDATORY, MANDATORY);

    Pkt6Ptr reply(new Pkt6(DHCPV6_REPLY, renew->getTransid()));

    copyDefaultOptions(renew, reply);
    appendDefaultOptions(renew, reply);
    appendRequestedOptions(renew, reply);

    renewLeases(renew, reply);

    return reply;
}

Pkt6Ptr Dhcpv6Srv::processRebind(const Pkt6Ptr& rebind) {
    /// @todo: Implement this
    Pkt6Ptr reply(new Pkt6(DHCPV6_REPLY, rebind->getTransid()));
    return reply;
}

Pkt6Ptr Dhcpv6Srv::processConfirm(const Pkt6Ptr& confirm) {
    /// @todo: Implement this
    Pkt6Ptr reply(new Pkt6(DHCPV6_REPLY, confirm->getTransid()));
    return reply;
}

Pkt6Ptr Dhcpv6Srv::processRelease(const Pkt6Ptr& release) {
    /// @todo: Implement this
    Pkt6Ptr reply(new Pkt6(DHCPV6_REPLY, release->getTransid()));
    return reply;
}

Pkt6Ptr Dhcpv6Srv::processDecline(const Pkt6Ptr& decline) {
    /// @todo: Implement this
    Pkt6Ptr reply(new Pkt6(DHCPV6_REPLY, decline->getTransid()));
    return reply;
}

Pkt6Ptr Dhcpv6Srv::processInfRequest(const Pkt6Ptr& infRequest) {
    /// @todo: Implement this
    Pkt6Ptr reply(new Pkt6(DHCPV6_REPLY, infRequest->getTransid()));
    return reply;
}

};
};
