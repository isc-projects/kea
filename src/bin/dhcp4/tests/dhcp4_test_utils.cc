// Copyright (C) 2013-2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <asiolink/io_address.h>
#include <cc/data.h>
#include <cc/command_interpreter.h>
#include <dhcp4/json_config_parser.h>
#include <dhcp4/tests/dhcp4_test_utils.h>
#include <dhcp/libdhcp++.h>
#include <dhcp/option4_addrlst.h>
#include <dhcp/option_int.h>
#include <dhcp/option_int_array.h>
#include <dhcp/option_custom.h>
#include <dhcp/iface_mgr.h>
#include <dhcp/tests/iface_mgr_test_config.h>
#include <dhcp/tests/pkt_captures.h>
#include <dhcpsrv/cfg_db_access.h>
#include <dhcpsrv/cfg_multi_threading.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/lease.h>
#include <dhcpsrv/lease_mgr.h>
#include <dhcpsrv/lease_mgr_factory.h>
#include <log/logger_support.h>
#include <stats/stats_mgr.h>
#include <sstream>

using namespace std;
using namespace isc::asiolink;
using namespace isc::data;
using namespace isc::util;

namespace isc {
namespace dhcp {
namespace test {

BaseServerTest::BaseServerTest()
    : original_datadir_(CfgMgr::instance().getDataDir()) {
    CfgMgr::instance().setDataDir(TEST_DATA_BUILDDIR);
}

BaseServerTest::~BaseServerTest() {
    // Remove default lease file.
    std::ostringstream s2;
    s2 << CfgMgr::instance().getDataDir() << "/kea-leases4.csv";
    static_cast<void>(::remove(s2.str().c_str()));

    // Revert to original data directory.
    CfgMgr::instance().setDataDir(original_datadir_);

    // Revert to unit test logging, in case the test reconfigured it.
    isc::log::initLogger();
}

Dhcpv4SrvTest::Dhcpv4SrvTest()
    : rcode_(-1), srv_(0), multi_threading_(false) {

    // Wipe any existing statistics
    isc::stats::StatsMgr::instance().removeAll();

    subnet_ = Subnet4Ptr(new Subnet4(IOAddress("192.0.2.0"), 24, 1000,
                                     2000, 3000));
    pool_ = Pool4Ptr(new Pool4(IOAddress("192.0.2.100"), IOAddress("192.0.2.110")));
    subnet_->addPool(pool_);

    // Add Router option.
    Option4AddrLstPtr opt_routers(new Option4AddrLst(DHO_ROUTERS));
    opt_routers->setAddress(IOAddress("192.0.2.2"));
    subnet_->getCfgOption()->add(opt_routers, false, DHCP4_OPTION_SPACE);

    CfgMgr::instance().clear();
    CfgMgr::instance().setFamily(AF_INET);
    CfgMgr::instance().getStagingCfg()->getCfgSubnets4()->add(subnet_);
    CfgMgr::instance().commit();

    LibDHCP::clearRuntimeOptionDefs();

    // Let's wipe all existing statistics.
    isc::stats::StatsMgr::instance().removeAll();

    // Reset the thread pool.
    MultiThreadingMgr::instance().apply(false, 0, 0);
}

Dhcpv4SrvTest::~Dhcpv4SrvTest() {

    // Make sure that we revert to default value
    CfgMgr::instance().clear();

    LibDHCP::clearRuntimeOptionDefs();

    // Let's wipe all existing statistics.
    isc::stats::StatsMgr::instance().removeAll();

    // Reset the thread pool.
    MultiThreadingMgr::instance().apply(false, 0, 0);
}

void Dhcpv4SrvTest::addPrlOption(Pkt4Ptr& pkt) {

    OptionUint8ArrayPtr option_prl =
        OptionUint8ArrayPtr(new OptionUint8Array(Option::V4,
                                                 DHO_DHCP_PARAMETER_REQUEST_LIST));

    // Let's request options that have been configured for the subnet.
    option_prl->addValue(DHO_DOMAIN_NAME_SERVERS);
    option_prl->addValue(DHO_DOMAIN_NAME);
    option_prl->addValue(DHO_LOG_SERVERS);
    option_prl->addValue(DHO_COOKIE_SERVERS);
    // Let's also request the option that hasn't been configured. In such
    // case server should ignore request for this particular option.
    option_prl->addValue(DHO_LPR_SERVERS);
    // And add 'Parameter Request List' option into the DISCOVER packet.
    pkt->addOption(option_prl);
}

void
Dhcpv4SrvTest::configureRequestedOptions() {
    // dns-servers
    Option4AddrLstPtr
        option_dns_servers(new Option4AddrLst(DHO_DOMAIN_NAME_SERVERS));
    option_dns_servers->addAddress(IOAddress("192.0.2.1"));
    option_dns_servers->addAddress(IOAddress("192.0.2.100"));
    ASSERT_NO_THROW(subnet_->getCfgOption()->add(option_dns_servers, false, DHCP4_OPTION_SPACE));

    // domain-name
    OptionDefinition def("domain-name", DHO_DOMAIN_NAME, DHCP4_OPTION_SPACE,
                         OPT_FQDN_TYPE);
    OptionCustomPtr option_domain_name(new OptionCustom(def, Option::V4));
    option_domain_name->writeFqdn("example.com");
    subnet_->getCfgOption()->add(option_domain_name, false, DHCP4_OPTION_SPACE);

    // log-servers
    Option4AddrLstPtr option_log_servers(new Option4AddrLst(DHO_LOG_SERVERS));
    option_log_servers->addAddress(IOAddress("192.0.2.2"));
    option_log_servers->addAddress(IOAddress("192.0.2.10"));
    ASSERT_NO_THROW(subnet_->getCfgOption()->add(option_log_servers, false, DHCP4_OPTION_SPACE));

    // cookie-servers
    Option4AddrLstPtr option_cookie_servers(new Option4AddrLst(DHO_COOKIE_SERVERS));
    option_cookie_servers->addAddress(IOAddress("192.0.2.1"));
    ASSERT_NO_THROW(subnet_->getCfgOption()->add(option_cookie_servers, false, DHCP4_OPTION_SPACE));
}

void
Dhcpv4SrvTest::configureServerIdentifier() {
    CfgMgr& cfg_mgr = CfgMgr::instance();
    CfgSubnets4Ptr subnets = cfg_mgr.getStagingCfg()->getCfgSubnets4();

    // Build and add subnet2.
    Subnet4Ptr subnet2(new Subnet4(IOAddress("192.0.2.0"), 24, 1200, 2400, 3600, 2));
    Pool4Ptr pool(new Pool4(IOAddress("192.0.2.100"), IOAddress("192.0.2.200")));
    // Add server identifier to the pool.
    OptionCustomPtr server_id = makeServerIdOption(IOAddress("192.0.2.254"));
    CfgOptionPtr cfg_option = pool->getCfgOption();
    cfg_option->add(server_id, false, DHCP4_OPTION_SPACE);
    subnet2->addPool(pool);

    // Add a second pool.
    pool.reset(new Pool4(IOAddress("192.0.2.201"), IOAddress("192.0.2.220")));
    subnet2->addPool(pool);

    subnets->add(subnet2);

    // Build and add subnet3.
    Triplet<uint32_t> unspec;
    Subnet4Ptr subnet3(new Subnet4(IOAddress("192.0.3.0"), 24, unspec, unspec, 3600, 3));
    pool.reset(new Pool4(IOAddress("192.0.3.100"), IOAddress("192.0.3.200")));
    subnet3->addPool(pool);
    subnet3->setT1Percent(0.5);
    subnet3->setT2Percent(0.75);
    subnet3->setCalculateTeeTimes(true);

    // Add server identifier.
    server_id = makeServerIdOption(IOAddress("192.0.3.254"));
    cfg_option = subnet3->getCfgOption();
    cfg_option->add(server_id, false, DHCP4_OPTION_SPACE);

    subnets->add(subnet3);

    // Build and add subnet4.
    Subnet4Ptr subnet4(new Subnet4(IOAddress("192.0.4.0"), 24, unspec, unspec, 3600, 4));
    pool.reset(new Pool4(IOAddress("192.0.4.100"), IOAddress("192.0.4.200")));
    subnet4->addPool(pool);
    subnet4->setCalculateTeeTimes(false);

    subnets->add(subnet4);

    // Build and add subnet5.
    Subnet4Ptr subnet5(new Subnet4(IOAddress("192.0.5.0"), 24, unspec, unspec, 3600, 5));
    pool.reset(new Pool4(IOAddress("192.0.5.100"), IOAddress("192.0.5.200")));
    subnet5->addPool(pool);
    subnet5->setCalculateTeeTimes(false);

    subnets->add(subnet5);

    CfgOptionPtr options(new CfgOption());
    OptionDescriptor desc(false);
    desc.option_ = makeServerIdOption(IOAddress("192.0.5.254"));
    options->add(desc, DHCP4_OPTION_SPACE);
    CfgMgr::instance().getStagingCfg()->getClientClassDictionary()->addClass("foo", ExpressionPtr(), "", true, false, options);
    subnet5->requireClientClass("foo");

    // Build and add subnet6.
    Subnet4Ptr subnet6(new Subnet4(IOAddress("192.0.6.0"), 24, unspec, unspec, 3600, 6));
    pool.reset(new Pool4(IOAddress("192.0.6.100"), IOAddress("192.0.6.200")));
    subnet6->addPool(pool);
    subnet6->setCalculateTeeTimes(false);

    subnets->add(subnet6);

    options.reset(new CfgOption());
    OptionDescriptor desc_other(false);
    desc_other.option_ = makeFqdnListOption();
    options->add(desc_other, DHCP4_OPTION_SPACE);
    CfgMgr::instance().getStagingCfg()->getClientClassDictionary()->addClass("bar", ExpressionPtr(), "", true, false, options);
    subnet6->requireClientClass("bar");

    // Build and add subnet7.
    Subnet4Ptr subnet7(new Subnet4(IOAddress("192.0.7.0"), 24, unspec, unspec, 3600, 7));
    pool.reset(new Pool4(IOAddress("192.0.7.100"), IOAddress("192.0.7.200")));
    subnet7->addPool(pool);
    subnet7->setCalculateTeeTimes(false);

    subnets->add(subnet7);

    options.reset();
    CfgMgr::instance().getStagingCfg()->getClientClassDictionary()->addClass("xyz", ExpressionPtr(), "", true, false, options);
    subnet7->requireClientClass("xyz");

    // Build and add a shared-network.
    CfgSharedNetworks4Ptr networks = cfg_mgr.getStagingCfg()->getCfgSharedNetworks4();
    SharedNetwork4Ptr network1(new SharedNetwork4("one"));
    network1->add(subnet4);

    // Add server identifier.
    server_id = makeServerIdOption(IOAddress("192.0.4.254"));
    cfg_option = network1->getCfgOption();
    cfg_option->add(server_id, false, DHCP4_OPTION_SPACE);

    networks->add(network1);

    // Add a global server identifier.
    cfg_option = cfg_mgr.getStagingCfg()->getCfgOption();
    server_id = makeServerIdOption(IOAddress("10.0.0.254"));
    cfg_option->add(server_id, false, DHCP4_OPTION_SPACE);

    // Commit the config.
    cfg_mgr.commit();
}

void
Dhcpv4SrvTest::messageCheck(const Pkt4Ptr& q, const Pkt4Ptr& a) {
    ASSERT_TRUE(q);
    ASSERT_TRUE(a);

    EXPECT_EQ(q->getHops(),   a->getHops());
    EXPECT_EQ(q->getIface(),  a->getIface());
    EXPECT_EQ(q->getIndex(),  a->getIndex());
    EXPECT_EQ(q->getGiaddr(), a->getGiaddr());
    // When processing an incoming packet the remote address
    // is copied as a src address, and the source address is
    // copied as a remote address to the response.
    EXPECT_TRUE(q->getLocalHWAddr() == a->getLocalHWAddr());
    EXPECT_TRUE(q->getRemoteHWAddr() == a->getRemoteHWAddr());

    // Check that the server identifier is present in the response.
    // Presence (or absence) of other options is checked elsewhere.
    EXPECT_TRUE(a->getOption(DHO_DHCP_SERVER_IDENTIFIER));

    // Check that something is offered
    EXPECT_NE("0.0.0.0", a->getYiaddr().toText());
}

::testing::AssertionResult
Dhcpv4SrvTest::basicOptionsPresent(const Pkt4Ptr& pkt) {
    std::ostringstream errmsg;
    errmsg << "option missing in the response";
    if (!pkt->getOption(DHO_DOMAIN_NAME)) {
        return (::testing::AssertionFailure(::testing::Message()
                                            << "domain-name " << errmsg.str()));

    } else if (!pkt->getOption(DHO_DOMAIN_NAME_SERVERS)) {
        return (::testing::AssertionFailure(::testing::Message()
                                            << "dns-servers " << errmsg.str()));

    } else if (!pkt->getOption(DHO_SUBNET_MASK)) {
        return (::testing::AssertionFailure(::testing::Message()
                                            << "subnet-mask " << errmsg.str()));

    } else if (!pkt->getOption(DHO_ROUTERS)) {
        return (::testing::AssertionFailure(::testing::Message() << "routers "
                                            << errmsg.str()));

    } else if (!pkt->getOption(DHO_DHCP_LEASE_TIME)) {
        return (::testing::AssertionFailure(::testing::Message() <<
                                            "dhcp-lease-time " << errmsg.str()));

    }
    return (::testing::AssertionSuccess());

}

::testing::AssertionResult
Dhcpv4SrvTest::noBasicOptions(const Pkt4Ptr& pkt) {
    std::ostringstream errmsg;
    errmsg << "option present in the response";
    if (pkt->getOption(DHO_DOMAIN_NAME)) {
        return (::testing::AssertionFailure(::testing::Message()
                                            << "domain-name " << errmsg.str()));

    } else if (pkt->getOption(DHO_DOMAIN_NAME_SERVERS)) {
        return (::testing::AssertionFailure(::testing::Message()
                                            << "dns-servers " << errmsg.str()));

    } else if (pkt->getOption(DHO_SUBNET_MASK)) {
        return (::testing::AssertionFailure(::testing::Message()
                                            << "subnet-mask " << errmsg.str()));

    } else if (pkt->getOption(DHO_ROUTERS)) {
        return (::testing::AssertionFailure(::testing::Message() << "routers "
                                            << errmsg.str()));

    } else if (pkt->getOption(DHO_DHCP_LEASE_TIME)) {
        return (::testing::AssertionFailure(::testing::Message()
                                            << "dhcp-lease-time " << errmsg.str()));

    }
    return (::testing::AssertionSuccess());
}

::testing::AssertionResult
Dhcpv4SrvTest::requestedOptionsPresent(const Pkt4Ptr& pkt) {
    std::ostringstream errmsg;
    errmsg << "option missing in the response";
    if (!pkt->getOption(DHO_LOG_SERVERS)) {
        return (::testing::AssertionFailure(::testing::Message()
                                            << "log-servers " << errmsg.str()));

    } else if (!pkt->getOption(DHO_COOKIE_SERVERS)) {
        return (::testing::AssertionFailure(::testing::Message()
                                            << "cookie-servers " << errmsg.str()));

    }
    return (::testing::AssertionSuccess());
}

::testing::AssertionResult
Dhcpv4SrvTest::noRequestedOptions(const Pkt4Ptr& pkt) {
    std::ostringstream errmsg;
    errmsg << "option present in the response";
    if (pkt->getOption(DHO_LOG_SERVERS)) {
        return (::testing::AssertionFailure(::testing::Message()
                                            << "log-servers " << errmsg.str()));

    } else if (pkt->getOption(DHO_COOKIE_SERVERS)) {
        return (::testing::AssertionFailure(::testing::Message()
                                            << "cookie-servers " << errmsg.str()));

    }
    return (::testing::AssertionSuccess());
}

OptionPtr
Dhcpv4SrvTest::generateClientId(size_t size /*= 4*/) {

    OptionBuffer clnt_id(size);
    for (size_t i = 0; i < size; i++) {
        clnt_id[i] = 100 + i;
    }

    client_id_ = ClientIdPtr(new ClientId(clnt_id));

    return (OptionPtr(new Option(Option::V4, DHO_DHCP_CLIENT_IDENTIFIER,
                                 clnt_id.begin(),
                                 clnt_id.begin() + size)));
}

HWAddrPtr
Dhcpv4SrvTest::generateHWAddr(size_t size /*= 6*/) {
    const uint8_t hw_type = 123; // Just a fake number (typically 6=HTYPE_ETHER, see dhcp4.h)
    OptionBuffer mac(size);
    for (size_t i = 0; i < size; ++i) {
        mac[i] = 50 + i;
    }
    return (HWAddrPtr(new HWAddr(mac, hw_type)));
}

OptionCustomPtr
Dhcpv4SrvTest::makeServerIdOption(const IOAddress& address) {
    OptionDefinitionPtr option_def = LibDHCP::getOptionDef(DHCP4_OPTION_SPACE,
                                                           DHO_DHCP_SERVER_IDENTIFIER);
    OptionCustomPtr server_id(new OptionCustom(*option_def, Option::V4));
    server_id->writeAddress(address);
    return (server_id);
}

OptionPtr
Dhcpv4SrvTest::makeFqdnListOption() {
    OptionDefinitionPtr def = LibDHCP::getOptionDef(DHCP4_OPTION_SPACE,
                                                    DHO_DOMAIN_SEARCH);

    // Prepare buffer holding an array of FQDNs.
    const uint8_t fqdn[] = {
        8, 109, 121, 100, 111, 109, 97, 105, 110, // "mydomain"
        7, 101, 120, 97, 109, 112, 108, 101,      // "example"
        3, 99, 111, 109,                          // "com"
        0
    };

    // Initialize a vector with the FQDN data.
    std::vector<uint8_t> fqdn_buf(fqdn, fqdn + sizeof(fqdn));

    OptionPtr option = def->optionFactory(Option::V4, DHO_DOMAIN_SEARCH,
                                          fqdn_buf.begin(), fqdn_buf.end());

    return (option);
}

void
Dhcpv4SrvTest::checkAddressParams(const Pkt4Ptr& rsp,
                                  const Subnet4Ptr subnet,
                                  bool t1_present,
                                  bool t2_present,
                                  uint32_t expected_valid) {

    // Technically inPool implies inRange, but let's be on the safe
    // side and check both.
    EXPECT_TRUE(subnet->inRange(rsp->getYiaddr()));
    EXPECT_TRUE(subnet->inPool(Lease::TYPE_V4, rsp->getYiaddr()));

    // Check lease time
    OptionUint32Ptr opt = boost::dynamic_pointer_cast<
        OptionUint32>(rsp->getOption(DHO_DHCP_LEASE_TIME));
    if (!opt) {
        ADD_FAILURE() << "Lease time option missing in response or the"
            " option has unexpected type";
    } else if (subnet->getValid().getMin() != subnet->getValid().getMax()) {
        EXPECT_GE(opt->getValue(), subnet->getValid().getMin());
        EXPECT_LE(opt->getValue(), subnet->getValid().getMax());
    } else {
        EXPECT_EQ(opt->getValue(), subnet->getValid());
    }

    // Check expected value when wanted.
    if (opt && expected_valid) {
      EXPECT_EQ(opt->getValue(), expected_valid);
    }

    // Check T1 timer
    opt = boost::dynamic_pointer_cast<
        OptionUint32>(rsp->getOption(DHO_DHCP_RENEWAL_TIME));
    if (t1_present) {
        ASSERT_TRUE(opt) << "Required T1 option missing or it has"
            " an unexpected type";
        EXPECT_EQ(opt->getValue(), subnet->getT1());
    } else {
        EXPECT_FALSE(opt);
    }

    // Check T2 timer
    opt = boost::dynamic_pointer_cast<
        OptionUint32>(rsp->getOption(DHO_DHCP_REBINDING_TIME));
    if (t2_present) {
        ASSERT_TRUE(opt) << "Required T2 option missing or it has"
            " an unexpected type";
        EXPECT_EQ(opt->getValue(), subnet->getT2());
    } else {
        EXPECT_FALSE(opt);
    }
}

void
Dhcpv4SrvTest::checkResponse(const Pkt4Ptr& rsp, int expected_message_type,
                             uint32_t expected_transid) {
    ASSERT_TRUE(rsp);
    EXPECT_EQ(expected_message_type,
              static_cast<int>(rsp->getType()));
    EXPECT_EQ(expected_transid, rsp->getTransid());
}

Lease4Ptr
Dhcpv4SrvTest::checkLease(const Pkt4Ptr& rsp, const OptionPtr& client_id,
                          const HWAddrPtr&, const IOAddress& expected_addr) {

    ClientIdPtr id;
    if (client_id) {
        OptionBuffer data = client_id->getData();
        id.reset(new ClientId(data));
    }

    Lease4Ptr lease = LeaseMgrFactory::instance().getLease4(expected_addr);
    if (!lease) {
        cout << "Lease for " << expected_addr
             << " not found in the database backend.";
        return (Lease4Ptr());
    }

    EXPECT_EQ(rsp->getYiaddr(), expected_addr);

    EXPECT_EQ(expected_addr, lease->addr_);
    if (client_id) {
        EXPECT_TRUE(*lease->client_id_ == *id);
    }
    EXPECT_EQ(subnet_->getID(), lease->subnet_id_);

    return (lease);
}

void
Dhcpv4SrvTest::checkServerId(const Pkt4Ptr& rsp, const OptionPtr& expected_srvid) {
    // Check that server included its server-id
    OptionPtr opt = rsp->getOption(DHO_DHCP_SERVER_IDENTIFIER);
    ASSERT_TRUE(opt);
    EXPECT_EQ(opt->getType(), expected_srvid->getType() );
    EXPECT_EQ(opt->len(), expected_srvid->len() );
    EXPECT_TRUE(opt->getData() == expected_srvid->getData());
}

void
Dhcpv4SrvTest::checkClientId(const Pkt4Ptr& rsp, const OptionPtr& expected_clientid) {

    bool include_clientid =
        CfgMgr::instance().getCurrentCfg()->getEchoClientId();

    // check that server included our own client-id
    OptionPtr opt = rsp->getOption(DHO_DHCP_CLIENT_IDENTIFIER);
    if (include_clientid) {
        // Normal mode: echo back (see RFC6842)
        ASSERT_TRUE(opt);
        EXPECT_EQ(expected_clientid->getType(), opt->getType());
        EXPECT_EQ(expected_clientid->len(), opt->len());
        EXPECT_TRUE(expected_clientid->getData() == opt->getData());
    } else {
        // Backward compatibility mode for pre-RFC6842 devices
        ASSERT_FALSE(opt);
    }
}

void
Dhcpv4SrvTest::checkServerIdOption(const Pkt4Ptr& packet, const IOAddress& expected_address) {
    OptionPtr opt = packet->getOption(DHO_DHCP_SERVER_IDENTIFIER);
    ASSERT_TRUE(opt) << "no server-id option";

    OptionCustomPtr server_id_opt = boost::dynamic_pointer_cast<OptionCustom>(opt);
    ASSERT_TRUE(server_id_opt) << "server-id option is not an instance of OptionCustom";

    EXPECT_EQ(expected_address, server_id_opt->readAddress());
}

::testing::AssertionResult
Dhcpv4SrvTest::createPacketFromBuffer(const Pkt4Ptr& src_pkt,
                                      Pkt4Ptr& dst_pkt) {
    // Create on-wire format of the packet. If pack() has been called
    // on this instance of the packet already, the next call to pack()
    // should remove all contents of the output buffer.
    try {
        src_pkt->pack();
    } catch (const Exception& ex) {
        return (::testing::AssertionFailure(::testing::Message()
                                            << "Failed to parse source packet: "
                                            << ex.what()));
    }
    // Get the output buffer from the source packet.
    const util::OutputBuffer& buf = src_pkt->getBuffer();
    // Create a copy of the packet using the output buffer from the source
    // packet.
    try {
        dst_pkt.reset(new Pkt4(static_cast<const uint8_t*>(buf.getData()),
                               buf.getLength()));
    } catch (const Exception& ex) {
        return (::testing::AssertionFailure(::testing::Message()
                                            << "Failed to create a"
                                            " destination packet from"
                                            " the buffer: "
                                            << ex.what()));
    }

    try {
        // Parse the new packet and return to the caller.
        dst_pkt->unpack();
    } catch (const Exception& ex) {
        return (::testing::AssertionFailure(::testing::Message()
                                            << "Failed to parse a"
                                            << " destination packet: "
                                            << ex.what()));
    }

    return (::testing::AssertionSuccess());
}

void
// cppcheck-suppress unusedFunction
Dhcpv4SrvTest::TearDown() {

    CfgMgr::instance().clear();

    // Close all open sockets.
    IfaceMgr::instance().closeSockets();

    // Some unit tests override the default packet filtering class, used
    // by the IfaceMgr. The dummy class, called PktFilterTest, reports the
    // capability to directly respond to the clients without IP address
    // assigned. This capability is not supported by the default packet
    // filtering class: PktFilterInet. Therefore setting the dummy class
    // allows to test scenarios, when server responds to the broadcast address
    // on client's request, despite having support for direct response.
    // The following call restores the use of original packet filtering class
    // after the test.
    try {
        IfaceMgr::instance().setPacketFilter(PktFilterPtr(new PktFilterInet()));

    } catch (const Exception& ex) {
        FAIL() << "Failed to restore the default (PktFilterInet) packet filtering"
               << " class after the test. Exception has been caught: "
               << ex.what();
    }
}

void
Dhcpv4SrvTest::testDiscoverRequest(const uint8_t msg_type) {
    IfaceMgrTestConfig test_config(true);
    IfaceMgr::instance().openSockets4();

    // Create an instance of the tested class.
    boost::scoped_ptr<NakedDhcpv4Srv> srv(new NakedDhcpv4Srv(0));

    // Initialize the source HW address.
    vector<uint8_t> mac(6);
    for (uint8_t i = 0; i < 6; ++i) {
        mac[i] = i * 10;
    }
    // Initialized the destination HW address.
    vector<uint8_t> dst_mac(6);
    for (uint8_t i = 0; i < 6; ++i) {
        dst_mac[i] = i * 20;
    }
    // Create a DHCP message. It will be used to simulate the
    // incoming message.
    boost::shared_ptr<Pkt4> req(new Pkt4(msg_type, 1234));
    // Create a response message. It will hold a response packet.
    // Initially, set it to NULL.
    boost::shared_ptr<Pkt4> rsp;
    // Set the name of the interface on which packet is received.
    req->setIface("eth0");
    // Set the interface index.
    req->setIndex(ETH0_INDEX);
    // Set the target HW address. This value is normally used to
    // construct the data link layer header.
    req->setRemoteHWAddr(1, 6, dst_mac);
    // Set the HW address. This value is set on DHCP level (in chaddr).
    req->setHWAddr(1, 6, mac);
    // Set local HW address. It is used to construct the data link layer
    // header.
    req->setLocalHWAddr(1, 6, mac);
    // Set target IP address.
    req->setRemoteAddr(IOAddress("192.0.2.55"));
    // Set relay address and hops.
    req->setGiaddr(IOAddress("192.0.2.10"));
    req->setHops(1);

    // We are going to test that certain options are returned
    // in the response message when requested using 'Parameter
    // Request List' option. Let's configure those options that
    // are returned when requested.
    configureRequestedOptions();

    // Create a copy of the original packet by parsing its wire format.
    // This simulates the real life scenario when we process the packet
    // which was parsed from its wire format.
    Pkt4Ptr received;
    ASSERT_TRUE(createPacketFromBuffer(req, received));
    // Set interface. It is required for the server to generate server id.
    received->setIface("eth0");
    received->setIndex(ETH0_INDEX);
    if (msg_type == DHCPDISCOVER) {
        ASSERT_NO_THROW(rsp = srv->processDiscover(received));

        // Should return OFFER
        ASSERT_TRUE(rsp);
        EXPECT_EQ(DHCPOFFER, rsp->getType());

    } else {
        ASSERT_NO_THROW(rsp = srv->processRequest(received));

        // Should return ACK
        ASSERT_TRUE(rsp);
        EXPECT_EQ(DHCPACK, rsp->getType());

    }

    messageCheck(received, rsp);

    // Basic options should be present when we got the lease.
    EXPECT_TRUE(basicOptionsPresent(rsp));
    // We did not request any options so these should not be present
    // in the RSP.
    EXPECT_TRUE(noRequestedOptions(rsp));

    // Repeat the test but request some options.
    // Add 'Parameter Request List' option.
    addPrlOption(req);

    ASSERT_TRUE(createPacketFromBuffer(req, received));
    ASSERT_TRUE(received->getOption(DHO_DHCP_PARAMETER_REQUEST_LIST));

    // Set interface. It is required for the server to generate server id.
    received->setIface("eth0");
    received->setIndex(ETH0_INDEX);

    if (msg_type == DHCPDISCOVER) {
        ASSERT_NO_THROW(rsp = srv->processDiscover(received));

        // Should return non-NULL packet.
        ASSERT_TRUE(rsp);
        EXPECT_EQ(DHCPOFFER, rsp->getType());

    } else {
        ASSERT_NO_THROW(rsp = srv->processRequest(received));

        // Should return non-NULL packet.
        ASSERT_TRUE(rsp);
        EXPECT_EQ(DHCPACK, rsp->getType());
    }

    // Check that the requested options are returned.
    EXPECT_TRUE(basicOptionsPresent(rsp));
    EXPECT_TRUE(requestedOptionsPresent(rsp));

    // The following part of the test will test that the NAK is sent when
    // there is no address pool configured. In the same time, we expect
    // that the requested options are not included in NAK message, but that
    // they are only included when yiaddr is set to non-zero value.
    ASSERT_NO_THROW(subnet_->delPools(Lease::TYPE_V4));

    // There has been a lease allocated for the particular client. So,
    // even though we deleted the subnet, the client would get the
    // existing lease (not a NAK). Therefore, we have to change the chaddr
    // in the packet so as the existing lease is not returned.
    req->setHWAddr(1, 6, std::vector<uint8_t>(2, 6));
    ASSERT_TRUE(createPacketFromBuffer(req, received));
    ASSERT_TRUE(received->getOption(DHO_DHCP_PARAMETER_REQUEST_LIST));

    // Set interface. It is required for the server to generate server id.
    received->setIface("eth0");
    received->setIndex(ETH0_INDEX);

    if (msg_type == DHCPDISCOVER) {
        ASSERT_NO_THROW(rsp = srv->processDiscover(received));
        // Should return NULL packet.
        ASSERT_FALSE(rsp);

    } else {
        ASSERT_NO_THROW(rsp = srv->processRequest(received));
        // Should return non-NULL packet.
        ASSERT_TRUE(rsp);
        // We should get the NAK packet with yiaddr set to 0.
        EXPECT_EQ(DHCPNAK, rsp->getType());
        ASSERT_EQ("0.0.0.0", rsp->getYiaddr().toText());

        // Make sure that none of the requested options is returned in NAK.
        // Also options such as Routers or Subnet Mask should not be there,
        // because lease hasn't been acquired.
        EXPECT_TRUE(noRequestedOptions(rsp));
        EXPECT_TRUE(noBasicOptions(rsp));
    }
}

void
Dhcpv4SrvTest::buildCfgOptionTest(IOAddress expected_server_id,
                                  Pkt4Ptr& query,
                                  IOAddress requested,
                                  IOAddress server_id) {
    OptionDefinitionPtr req_addr_def = LibDHCP::getOptionDef(DHCP4_OPTION_SPACE,
                                                             DHO_DHCP_REQUESTED_ADDRESS);
    ASSERT_TRUE(req_addr_def);

    OptionDefinitionPtr sbnsel_def = LibDHCP::getOptionDef(DHCP4_OPTION_SPACE,
                                                           DHO_SUBNET_SELECTION);
    ASSERT_TRUE(sbnsel_def);

    OptionCustomPtr req_addr(new OptionCustom(*req_addr_def, Option::V4));
    req_addr->writeAddress(requested);

    OptionCustomPtr sbnsel(new OptionCustom(*sbnsel_def, Option::V4));
    sbnsel->writeAddress(requested);

    query->addOption(req_addr);
    query->addOption(sbnsel);
    query->addOption(makeServerIdOption(server_id));

    Pkt4Ptr response;
    ASSERT_NO_THROW(response = srv_.processRequest(query));

    checkServerIdOption(response, expected_server_id);

    ASSERT_NO_THROW(query->delOption(DHO_DHCP_REQUESTED_ADDRESS));
    ASSERT_NO_THROW(query->delOption(DHO_SUBNET_SELECTION));
    ASSERT_NO_THROW(query->delOption(DHO_DHCP_SERVER_IDENTIFIER));
}

void
Dhcpv4SrvTest::configure(const std::string& config,
                         const bool commit,
                         const bool open_sockets) {
    configure(config, srv_, commit, open_sockets);
}

void
Dhcpv4SrvTest::configure(const std::string& config,
                         NakedDhcpv4Srv& srv,
                         const bool commit,
                         const bool open_sockets) {
    setenv("KEA_LFC_EXECUTABLE", KEA_LFC_EXECUTABLE, 1);
    MultiThreadingCriticalSection cs;
    ConstElementPtr json;
    try {
        json = parseJSON(config);
    } catch (const std::exception& ex){
        // Fatal failure on parsing error
        FAIL() << "parsing failure:"
                << "config:" << config << std::endl
                << "error: " << ex.what();
    }

    ConstElementPtr status;

    // Disable the re-detect flag
    disableIfacesReDetect(json);

    // Set up multi-threading
    configureMultiThreading(multi_threading_, json);

    // Configure the server and make sure the config is accepted
    EXPECT_NO_THROW(status = configureDhcp4Server(srv, json));
    ASSERT_TRUE(status);
    int rcode;
    ConstElementPtr comment = config::parseAnswer(rcode, status);
    ASSERT_EQ(0, rcode) << comment->stringValue();

    // Use specified lease database backend.
    ASSERT_NO_THROW( {
        CfgDbAccessPtr cfg_db = CfgMgr::instance().getStagingCfg()->getCfgDbAccess();
        cfg_db->setAppendedParameters("universe=4");
        cfg_db->createManagers();
    } );

    try {
        CfgMultiThreading::apply(CfgMgr::instance().getStagingCfg()->getDHCPMultiThreading());
    } catch (const std::exception& ex) {
        ADD_FAILURE() << "Error applying multi threading settings: "
            << ex.what();
    }

    if (commit) {
        CfgMgr::instance().commit();
    }

    // Opening sockets.
    if (open_sockets) {
        IfaceMgr::instance().openSockets4();
    }
}

std::pair<int, std::string>
Dhcpv4SrvTest::configureWithStatus(const std::string& config, NakedDhcpv4Srv& srv,
                                   const bool commit, const int exp_rcode) {
    ConstElementPtr json;
    try {
        json = parseJSON(config);
    } catch (const std::exception& ex){
        // Fatal failure on parsing error

        std::stringstream tmp;
        tmp << "parsing failure:"
            << "config:" << config << std::endl
            << "error: " << ex.what();
        ADD_FAILURE() << tmp.str();
        return (std::make_pair(-1, tmp.str()));
    }

    ConstElementPtr status;

    // Disable the re-detect flag
    disableIfacesReDetect(json);

    // Configure the server and make sure the config is accepted
    EXPECT_NO_THROW(status = configureDhcp4Server(srv, json));
    EXPECT_TRUE(status);
    if (!status) {
        return (make_pair(-1, "configureDhcp4Server didn't return anything"));
    }

    int rcode;
    ConstElementPtr comment = config::parseAnswer(rcode, status);
    EXPECT_EQ(exp_rcode, rcode) << comment->stringValue();

    // Use specified lease database backend.
    if (rcode == 0) {
        EXPECT_NO_THROW( {
            CfgDbAccessPtr cfg_db = CfgMgr::instance().getStagingCfg()->getCfgDbAccess();
            cfg_db->setAppendedParameters("universe=4");
            cfg_db->createManagers();
            } );
        if (commit) {
            CfgMgr::instance().commit();
        }
    }

    return (std::make_pair(rcode, comment->stringValue()));
}

Dhcpv4Exchange
Dhcpv4SrvTest::createExchange(const Pkt4Ptr& query) {
    bool drop = false;
    Subnet4Ptr subnet = srv_.selectSubnet(query, drop);
    EXPECT_FALSE(drop);
    Dhcpv4Exchange ex(srv_.alloc_engine_, query, subnet, drop);
    EXPECT_FALSE(drop);
    return (ex);
}

void
Dhcpv4SrvTest::pretendReceivingPkt(NakedDhcpv4Srv& srv, const std::string& config,
                                   uint8_t pkt_type, const std::string& stat_name) {

    IfaceMgrTestConfig test_config(true);
    IfaceMgr::instance().openSockets4();

    // Apply the configuration we just received.
    configure(config);

    // Let's just use one of the actual captured packets that we have.
    Pkt4Ptr pkt = PktCaptures::captureRelayedDiscover();

    // We just need to tweak it a it, to pretend that its type is as desired.
    // Note that when receiving a packet, its on-wire form is stored in data_
    // field. Most methods (including setType()) operates on option objects
    // (objects stored in options_ after unpack() is called). Finally, outgoing
    // packets are stored in out_buffer_. So we need to go through the full
    // unpack/tweak/pack cycle and do repack, i.e. move the output buffer back
    // to incoming buffer.
    pkt->unpack();
    pkt->setType(pkt_type); // Set message type.
    pkt->pack();
    pkt->data_.resize(pkt->getBuffer().getLength());
    // Copy out_buffer_ to data_ to pretend that it's what was just received.
    memcpy(&pkt->data_[0], pkt->getBuffer().getData(), pkt->getBuffer().getLength());

    // Simulate that we have received that traffic
    srv.fakeReceive(pkt);
    srv.run();

    using namespace isc::stats;
    StatsMgr& mgr = StatsMgr::instance();
    ObservationPtr pkt4_rcvd = mgr.getObservation("pkt4-received");
    ObservationPtr tested_stat = mgr.getObservation(stat_name);

    // All expected statistics must be present.
    ASSERT_TRUE(pkt4_rcvd);
    ASSERT_TRUE(tested_stat);

    // They also must have expected values.
    EXPECT_EQ(1, pkt4_rcvd->getInteger().first);
    EXPECT_EQ(1, tested_stat->getInteger().first);
}

} // end of isc::dhcp::test namespace
} // end of isc::dhcp namespace
} // end of isc namespace
