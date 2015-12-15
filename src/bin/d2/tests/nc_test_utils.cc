// Copyright (C) 2013-2015  Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <d2/d2_cfg_mgr.h>
#include <dns/opcode.h>
#include <dns/messagerenderer.h>
#include <nc_test_utils.h>
#include <boost/asio.hpp>
#include <asiolink/udp_endpoint.h>
#include <util/encode/base64.h>

#include <gtest/gtest.h>

using namespace std;
using namespace isc;
using namespace isc::d2;

namespace isc {
namespace d2 {

const char* TEST_DNS_SERVER_IP = "127.0.0.1";
size_t TEST_DNS_SERVER_PORT = 5301;

//const bool HAS_RDATA = true;
const bool NO_RDATA = false;

//*************************** FauxServer class ***********************

FauxServer::FauxServer(asiolink::IOService& io_service,
                       asiolink::IOAddress& address, size_t port)
    :io_service_(io_service), address_(address), port_(port),
     server_socket_(), receive_pending_(false), perpetual_receive_(true),
     tsig_key_() {

    server_socket_.reset(new boost::asio::ip::udp::socket(io_service_.get_io_service(),
                                                   boost::asio::ip::udp::v4()));
    server_socket_->set_option(boost::asio::socket_base::reuse_address(true));

    isc::asiolink::UDPEndpoint endpoint(address_, port_);
    server_socket_->bind(endpoint.getASIOEndpoint());
}

FauxServer::FauxServer(asiolink::IOService& io_service,
                       DnsServerInfo& server)
    :io_service_(io_service), address_(server.getIpAddress()),
     port_(server.getPort()), server_socket_(), receive_pending_(false),
     perpetual_receive_(true), tsig_key_() {
    server_socket_.reset(new boost::asio::ip::udp::socket(io_service_.get_io_service(),
                                                   boost::asio::ip::udp::v4()));
    server_socket_->set_option(boost::asio::socket_base::reuse_address(true));
    isc::asiolink::UDPEndpoint endpoint(address_, port_);
    server_socket_->bind(endpoint.getASIOEndpoint());
}


FauxServer::~FauxServer() {
}

void
FauxServer::receive (const ResponseMode& response_mode,
                     const dns::Rcode& response_rcode) {
    if (receive_pending_) {
        return;
    }

    receive_pending_ = true;
    server_socket_->async_receive_from(boost::asio::buffer(receive_buffer_,
                                                    sizeof(receive_buffer_)),
                                       remote_,
                                       boost::bind(&FauxServer::requestHandler,
                                                   this, _1, _2,
                                                   response_mode,
                                                   response_rcode));
}

void
FauxServer::requestHandler(const boost::system::error_code& error,
                           std::size_t bytes_recvd,
                           const ResponseMode& response_mode,
                           const dns::Rcode& response_rcode) {
    receive_pending_ = false;
    // If we encountered an error or received no data then fail.
    // We expect the client to send good requests.
    if (error.value() != 0 || bytes_recvd < 1) {
        ADD_FAILURE() << "FauxServer receive failed: " << error.message();
        return;
    }

    // If TSIG key isn't NULL, create a context and use to verify the
    // request and sign the response.
    dns::TSIGContextPtr context;
    if (tsig_key_) {
        context.reset(new dns::TSIGContext(*tsig_key_));
    }

    // We have a successfully received data. We need to turn it into
    // a request in order to build a proper response.
    // Note D2UpdateMessage is geared towards making requests and
    // reading responses.  This is the opposite perspective so we have
    // to a bit of roll-your-own here.
    dns::Message request(dns::Message::PARSE);
    util::InputBuffer request_buf(receive_buffer_, bytes_recvd);
    try {
        request.fromWire(request_buf);

        // If contex is not NULL, then we need to verify the message.
        if (context) {
            dns::TSIGError error = context->verify(request.getTSIGRecord(),
                                                   receive_buffer_,
                                                   bytes_recvd);
            if (error != dns::TSIGError::NOERROR()) {
                isc_throw(TSIGVerifyError, "TSIG verification failed: "
                          << error.toText());
            }
        }
    } catch (const std::exception& ex) {
        // If the request cannot be parsed, then fail the test.
        // We expect the client to send good requests.
        ADD_FAILURE() << "FauxServer request is corrupt:" << ex.what();
        return;
    }

    // The request parsed OK, so let's build a response.
    // We must use the QID we received in the response or IOFetch will
    // toss the response out, resulting in eventual timeout.
    // We fill in the zone with data we know is from the "server".
    dns::Message response(dns::Message::RENDER);
    response.setQid(request.getQid());
    dns::Question question(dns::Name("response.example.com"),
                           dns::RRClass::ANY(), dns::RRType::SOA());
    response.addQuestion(question);
    response.setOpcode(dns::Opcode(dns::Opcode::UPDATE_CODE));
    response.setHeaderFlag(dns::Message::HEADERFLAG_QR, true);

    // Set the response Rcode to value passed in, default is NOERROR.
    response.setRcode(response_rcode);

    // Render the response to a buffer.
    dns::MessageRenderer renderer;
    util::OutputBuffer response_buf(TEST_MSG_MAX);
    renderer.setBuffer(&response_buf);

    if (response_mode == INVALID_TSIG) {
        // Create a different key to sign the response.
        std::string secret ("key that doesn't match");
        dns::TSIGKeyPtr key;
        ASSERT_NO_THROW(key.reset(new
                                  dns::TSIGKey(dns::Name("badkey"),
                                               dns::TSIGKey::HMACMD5_NAME(),
                                               secret.c_str(), secret.size())));
        context.reset(new dns::TSIGContext(*key));
    }

    response.toWire(renderer, context.get());

    // If mode is to ship garbage, then stomp on part of the rendered
    // message.
    if (response_mode == CORRUPT_RESP) {
        response_buf.writeUint16At(0xFFFF, 2);
    }

    // Ship the response via synchronous send.
    try {
        int cnt = server_socket_->send_to(boost::asio::
                                          buffer(response_buf.getData(),
                                                 response_buf.getLength()),
                                          remote_);
        // Make sure we sent what we expect to send.
        if (cnt != response_buf.getLength()) {
            ADD_FAILURE() << "FauxServer sent: " << cnt << " expected: "
                          << response_buf.getLength();
        }
    } catch (const std::exception& ex) {
        ADD_FAILURE() << "FauxServer send failed: " << ex.what();
    }

    if (perpetual_receive_) {
        // Schedule the next receive
        receive (response_mode, response_rcode);
    }
}



//********************** TimedIO class ***********************

TimedIO::TimedIO()
    : io_service_(new isc::asiolink::IOService()),
     timer_(*io_service_), run_time_(0) {
}

TimedIO::~TimedIO() {
}

int
TimedIO::runTimedIO(int run_time) {
    run_time_ = run_time;
    int cnt = io_service_->get_io_service().poll();
    if (cnt == 0) {
        timer_.setup(boost::bind(&TimedIO::timesUp, this), run_time_);
        cnt = io_service_->get_io_service().run_one();
        timer_.cancel();
    }

    return (cnt);
}

void
TimedIO::timesUp() {
    io_service_->stop();
    FAIL() << "Test Time: " << run_time_ << " expired";
}

//********************** TransactionTest class ***********************

const unsigned int TransactionTest::FORWARD_CHG = 0x01;
const unsigned int TransactionTest::REVERSE_CHG = 0x02;
const unsigned int TransactionTest::FWD_AND_REV_CHG = REVERSE_CHG | FORWARD_CHG;

TransactionTest::TransactionTest() : ncr_(), cfg_mgr_(new D2CfgMgr()) {
}

TransactionTest::~TransactionTest() {
}

void
TransactionTest::setupForIPv4Transaction(dhcp_ddns::NameChangeType chg_type,
                                         int change_mask,
                                         const TSIGKeyInfoPtr& tsig_key_info) {
    const char* msg_str =
        "{"
        " \"change-type\" : 0 , "
        " \"forward-change\" : true , "
        " \"reverse-change\" : true , "
        " \"fqdn\" : \"my.forward.example.com.\" , "
        " \"ip-address\" : \"192.168.2.1\" , "
        " \"dhcid\" : \"0102030405060708\" , "
        " \"lease-expires-on\" : \"20130121132405\" , "
        " \"lease-length\" : 1300 "
        "}";

    // Create NameChangeRequest from JSON string.
    ncr_ = dhcp_ddns::NameChangeRequest::fromJSON(msg_str);

    // Set the change type.
    ncr_->setChangeType(chg_type);

    // If the change mask does not include a forward change clear the
    // forward domain; otherwise create the domain and its servers.
    if (!(change_mask & FORWARD_CHG)) {
        ncr_->setForwardChange(false);
        forward_domain_.reset();
    } else {
        // Create the forward domain and then its servers.
        forward_domain_ = makeDomain("example.com.", tsig_key_info);
        addDomainServer(forward_domain_, "forward.example.com",
                        "127.0.0.1", 5301);
        addDomainServer(forward_domain_, "forward2.example.com",
                        "127.0.0.1", 5302);
    }

    // If the change mask does not include a reverse change clear the
    // reverse domain; otherwise create the domain and its servers.
    if (!(change_mask & REVERSE_CHG)) {
        ncr_->setReverseChange(false);
        reverse_domain_.reset();
    } else {
        // Create the reverse domain and its server.
        reverse_domain_ = makeDomain("2.168.192.in.addr.arpa.", tsig_key_info);
        addDomainServer(reverse_domain_, "reverse.example.com",
                        "127.0.0.1", 5301);
        addDomainServer(reverse_domain_, "reverse2.example.com",
                        "127.0.0.1", 5302);
    }
}

void
TransactionTest::setupForIPv4Transaction(dhcp_ddns::NameChangeType chg_type,
                                         int change_mask,
                                         const std::string& key_name) {
    setupForIPv4Transaction(chg_type, change_mask, makeTSIGKeyInfo(key_name));
}

void
TransactionTest::setupForIPv6Transaction(dhcp_ddns::NameChangeType chg_type,
                                         int change_mask,
                                         const TSIGKeyInfoPtr& tsig_key_info) {
    const char* msg_str =
        "{"
        " \"change-type\" : 0 , "
        " \"forward-change\" : true , "
        " \"reverse-change\" : true , "
        " \"fqdn\" : \"my6.forward.example.com.\" , "
        " \"ip-address\" : \"2001:1::100\" , "
        " \"dhcid\" : \"0102030405060708\" , "
        " \"lease-expires-on\" : \"20130121132405\" , "
        " \"lease-length\" : 1300 "
        "}";

    // Create NameChangeRequest from JSON string.
    ncr_ = makeNcrFromString(msg_str);

    // Set the change type.
    ncr_->setChangeType(chg_type);

    // If the change mask does not include a forward change clear the
    // forward domain; otherwise create the domain and its servers.
    if (!(change_mask & FORWARD_CHG)) {
        ncr_->setForwardChange(false);
        forward_domain_.reset();
    } else {
        // Create the forward domain and then its servers.
        forward_domain_ = makeDomain("example.com.", tsig_key_info);
        addDomainServer(forward_domain_, "fwd6-server.example.com",
                        "::1", 5301);
        addDomainServer(forward_domain_, "fwd6-server2.example.com",
                        "::1", 5302);
    }

    // If the change mask does not include a reverse change clear the
    // reverse domain; otherwise create the domain and its servers.
    if (!(change_mask & REVERSE_CHG)) {
        ncr_->setReverseChange(false);
        reverse_domain_.reset();
    } else {
        // Create the reverse domain and its server.
        reverse_domain_ = makeDomain("1.2001.ip6.arpa.", tsig_key_info);
        addDomainServer(reverse_domain_, "rev6-server.example.com",
                        "::1", 5301);
        addDomainServer(reverse_domain_, "rev6-server2.example.com",
                        "::1", 5302);
    }
}

void
TransactionTest::setupForIPv6Transaction(dhcp_ddns::NameChangeType chg_type,
                                         int change_mask,
                                         const std::string& key_name) {
    setupForIPv6Transaction(chg_type, change_mask, makeTSIGKeyInfo(key_name));
}


//********************** Functions ****************************

void
checkRRCount(const D2UpdateMessagePtr& request,
             D2UpdateMessage::UpdateMsgSection section, int count) {
    dns::RRsetIterator rrset_it = request->beginSection(section);
    dns::RRsetIterator rrset_end = request->endSection(section);

    ASSERT_EQ(count, std::distance(rrset_it, rrset_end));
}

void
checkZone(const D2UpdateMessagePtr& request, const std::string& exp_zone_name) {
    // Verify the zone section info.
    D2ZonePtr zone = request->getZone();
    EXPECT_TRUE(zone);
    EXPECT_EQ(exp_zone_name, zone->getName().toText());
    EXPECT_EQ(dns::RRClass::IN().getCode(), zone->getClass().getCode());
}

void
checkRR(dns::RRsetPtr rrset, const std::string& exp_name,
              const dns::RRClass& exp_class, const dns::RRType& exp_type,
              unsigned int exp_ttl, dhcp_ddns::NameChangeRequestPtr ncr,
              bool has_rdata) {
    // Verify the FQDN/DHCID RR fields.
    EXPECT_EQ(exp_name, rrset->getName().toText());
    EXPECT_EQ(exp_class.getCode(), rrset->getClass().getCode());
    EXPECT_EQ(exp_type.getCode(), rrset->getType().getCode());
    EXPECT_EQ(exp_ttl, rrset->getTTL().getValue());
    if ((!has_rdata) ||
       (exp_type == dns::RRType::ANY() || exp_class == dns::RRClass::ANY())) {
        // ANY types do not have RData
        ASSERT_EQ(0, rrset->getRdataCount());
        return;
    }

    ASSERT_EQ(1, rrset->getRdataCount());
    dns::RdataIteratorPtr rdata_it = rrset->getRdataIterator();
    ASSERT_TRUE(rdata_it);

    if ((exp_type == dns::RRType::A()) ||
        (exp_type == dns::RRType::AAAA())) {
        // should have lease rdata
        EXPECT_EQ(ncr->getIpAddress(), rdata_it->getCurrent().toText());
    } else if (exp_type == dns::RRType::PTR())  {
        // should have PTR rdata
        EXPECT_EQ(ncr->getFqdn(), rdata_it->getCurrent().toText());
    } else if (exp_type == dns::RRType::DHCID()) {
        // should have DHCID rdata
        const std::vector<uint8_t>& ncr_dhcid = ncr->getDhcid().getBytes();
        util::InputBuffer buffer(ncr_dhcid.data(), ncr_dhcid.size());
        dns::rdata::in::DHCID rdata_ref(buffer, ncr_dhcid.size());
        EXPECT_EQ(0, rdata_ref.compare(rdata_it->getCurrent()));
    } else {
        // we got a problem
        FAIL();
    }
}

dns::RRsetPtr
getRRFromSection(const D2UpdateMessagePtr& request,
                 D2UpdateMessage::UpdateMsgSection section, int index) {
    dns::RRsetIterator rrset_it = request->beginSection(section);
    dns::RRsetIterator rrset_end = request->endSection(section);

    if (std::distance(rrset_it, rrset_end) <= index) {
        // Return an empty pointer if index is out of range.
        return (dns::RRsetPtr());
    }

    std::advance(rrset_it, index);
    return (*rrset_it);
}

dhcp_ddns::NameChangeRequestPtr makeNcrFromString(const std::string& ncr_str) {
    return (dhcp_ddns::NameChangeRequest::fromJSON(ncr_str));
}

DdnsDomainPtr makeDomain(const std::string& zone_name,
                         const std::string& key_name) {
    DnsServerInfoStoragePtr servers(new DnsServerInfoStorage());
    DdnsDomainPtr domain(new DdnsDomain(zone_name, servers,
                         makeTSIGKeyInfo(key_name)));
    return (domain);
}

DdnsDomainPtr makeDomain(const std::string& zone_name,
                         const TSIGKeyInfoPtr &tsig_key_info) {
    DdnsDomainPtr domain;
    DnsServerInfoStoragePtr servers(new DnsServerInfoStorage());
    domain.reset(new DdnsDomain(zone_name, servers, tsig_key_info));
    return (domain);
}

TSIGKeyInfoPtr makeTSIGKeyInfo(const std::string& key_name,
                           const std::string& secret,
                           const std::string& algorithm) {
    TSIGKeyInfoPtr key_info;
    if (!key_name.empty()) {
        if (!secret.empty()) {
            key_info.reset(new TSIGKeyInfo(key_name, algorithm, secret));
        } else {
            // Since secret was left blank, we'll convert key_name into a
            // base64 encoded string and use that.
            const uint8_t* bytes = reinterpret_cast<const uint8_t*>
                                                   (key_name.c_str());
            size_t len = key_name.size();
            const vector<uint8_t> key_name_v(bytes, bytes + len);
            std::string key_name64
                = isc::util::encode::encodeBase64(key_name_v);

            // Now, make the TSIGKeyInfo with a real base64 secret.
            key_info.reset(new TSIGKeyInfo(key_name, algorithm, key_name64));
        }
    }

    return (key_info);

}

void addDomainServer(DdnsDomainPtr& domain, const std::string& name,
                     const std::string& ip, const size_t port) {
    DnsServerInfoPtr server(new DnsServerInfo(name, asiolink::IOAddress(ip),
                                              port));
    domain->getServers()->push_back(server);
}

// Verifies that the contents of the given transaction's  DNS update request
// is correct for adding a forward DNS entry
void checkAddFwdAddressRequest(NameChangeTransaction& tran) {
    const D2UpdateMessagePtr& request = tran.getDnsUpdateRequest();
    ASSERT_TRUE(request);

    // Safety check.
    dhcp_ddns::NameChangeRequestPtr ncr = tran.getNcr();
    ASSERT_TRUE(ncr);

    std::string exp_zone_name = tran.getForwardDomain()->getName();
    std::string exp_fqdn = ncr->getFqdn();
    const dns::RRType& exp_ip_rr_type = tran.getAddressRRType();

    // Verify the zone section.
    checkZone(request, exp_zone_name);

    // Verify the PREREQUISITE SECTION
    // Should be 1 which tests for FQDN does not exist.
    dns::RRsetPtr rrset;
    checkRRCount(request, D2UpdateMessage::SECTION_PREREQUISITE, 1);
    ASSERT_TRUE(rrset = getRRFromSection(request, D2UpdateMessage::
                                                  SECTION_PREREQUISITE, 0));
    checkRR(rrset, exp_fqdn, dns::RRClass::NONE(), dns::RRType::ANY(), 0, ncr);

    // Verify the UPDATE SECTION
    // Should be 2 RRs: 1 to add the FQDN/IP and one to add the DHCID RR
    checkRRCount(request, D2UpdateMessage::SECTION_UPDATE, 2);

    // Fetch ttl.
    uint32_t ttl = ncr->getLeaseLength();

    // First, Verify the FQDN/IP add RR.
    ASSERT_TRUE(rrset = getRRFromSection(request, D2UpdateMessage::
                                                  SECTION_UPDATE, 0));
    checkRR(rrset, exp_fqdn, dns::RRClass::IN(), exp_ip_rr_type, ttl, ncr);

    // Now, verify the DHCID add RR.
    ASSERT_TRUE(rrset = getRRFromSection(request, D2UpdateMessage::
                                                  SECTION_UPDATE, 1));
    checkRR(rrset, exp_fqdn, dns::RRClass::IN(), dns::RRType::DHCID(),
            ttl, ncr);

    // Verify there are no RRs in the ADDITIONAL Section.
    checkRRCount(request, D2UpdateMessage::SECTION_ADDITIONAL, 0);

    // Verify that it will render toWire without throwing.
    dns::MessageRenderer renderer;
    ASSERT_NO_THROW(request->toWire(renderer));
}

// Verifies that the contents of the given transaction's  DNS update request
// is correct for replacing a forward DNS entry
void checkReplaceFwdAddressRequest(NameChangeTransaction& tran) {
    const D2UpdateMessagePtr& request = tran.getDnsUpdateRequest();
    ASSERT_TRUE(request);

    // Safety check.
    dhcp_ddns::NameChangeRequestPtr ncr = tran.getNcr();
    ASSERT_TRUE(ncr);

    std::string exp_zone_name = tran.getForwardDomain()->getName();
    std::string exp_fqdn = ncr->getFqdn();
    const dns::RRType& exp_ip_rr_type = tran.getAddressRRType();

    // Verify the zone section.
    checkZone(request, exp_zone_name);

    // Verify the PREREQUISITE SECTION
    // Should be 2,  1 which tests for FQDN does exist and the other
    // checks for a matching DHCID.
    dns::RRsetPtr rrset;
    checkRRCount(request, D2UpdateMessage::SECTION_PREREQUISITE, 2);

    // Verify the FQDN test RR.
    ASSERT_TRUE(rrset = getRRFromSection(request, D2UpdateMessage::
                                                  SECTION_PREREQUISITE, 0));
    checkRR(rrset, exp_fqdn, dns::RRClass::ANY(), dns::RRType::ANY(), 0, ncr);

    // Verify the DHCID test RR.
    ASSERT_TRUE(rrset = getRRFromSection(request, D2UpdateMessage::
                                                  SECTION_PREREQUISITE, 1));
    checkRR(rrset, exp_fqdn, dns::RRClass::IN(), dns::RRType::DHCID(), 0, ncr);

    // Verify the UPDATE SECTION
    // Should be 2,  1 which deletes the existing FQDN/IP and one that
    // adds the new one.
    checkRRCount(request, D2UpdateMessage::SECTION_UPDATE, 2);

    // Fetch ttl.
    uint32_t ttl = ncr->getLeaseLength();

    // Verify the FQDN delete RR.
    ASSERT_TRUE(rrset = getRRFromSection(request, D2UpdateMessage::
                                                  SECTION_UPDATE, 0));
    checkRR(rrset, exp_fqdn, dns::RRClass::ANY(), exp_ip_rr_type, 0, ncr);

    // Verify the FQDN/IP add RR.
    ASSERT_TRUE(rrset = getRRFromSection(request, D2UpdateMessage::
                                                  SECTION_UPDATE, 1));
    checkRR(rrset, exp_fqdn, dns::RRClass::IN(), exp_ip_rr_type, ttl, ncr);

    // Verify there are no RRs in the ADDITIONAL Section.
    checkRRCount(request, D2UpdateMessage::SECTION_ADDITIONAL, 0);

    // Verify that it will render toWire without throwing.
    dns::MessageRenderer renderer;
    ASSERT_NO_THROW(request->toWire(renderer));
}

// Verifies that the contents of the given transaction's  DNS update request
// is correct for replacing a reverse DNS entry
void checkReplaceRevPtrsRequest(NameChangeTransaction& tran) {
    const D2UpdateMessagePtr& request = tran.getDnsUpdateRequest();
    ASSERT_TRUE(request);

    // Safety check.
    dhcp_ddns::NameChangeRequestPtr ncr = tran.getNcr();
    ASSERT_TRUE(ncr);

    std::string exp_zone_name = tran.getReverseDomain()->getName();
    std::string exp_rev_addr = D2CfgMgr::reverseIpAddress(ncr->getIpAddress());

    // Verify the zone section.
    checkZone(request, exp_zone_name);

    // Verify there are no RRs in the PREREQUISITE Section.
    checkRRCount(request, D2UpdateMessage::SECTION_PREREQUISITE, 0);

    // Fetch ttl.
    uint32_t ttl = ncr->getLeaseLength();

    // Verify the UPDATE Section.
    // It should contain 4 RRs:
    // 1. A delete all PTR RRs for the given IP
    // 2. A delete of all DHCID RRs for the given IP
    // 3. An add of the new PTR RR
    // 4. An add of the new DHCID RR
    dns::RRsetPtr rrset;
    checkRRCount(request, D2UpdateMessage::SECTION_UPDATE, 4);

    // Verify the PTR delete RR.
    ASSERT_TRUE(rrset = getRRFromSection(request, D2UpdateMessage::
                                                  SECTION_UPDATE, 0));
    checkRR(rrset, exp_rev_addr, dns::RRClass::ANY(), dns::RRType::PTR(),
            0, ncr);

    // Verify the DHCID delete RR.
    ASSERT_TRUE(rrset = getRRFromSection(request, D2UpdateMessage::
                                                  SECTION_UPDATE, 1));
    checkRR(rrset, exp_rev_addr, dns::RRClass::ANY(), dns::RRType::DHCID(),
            0, ncr);

    // Verify the PTR add RR.
    ASSERT_TRUE(rrset = getRRFromSection(request, D2UpdateMessage::
                                                  SECTION_UPDATE, 2));
    checkRR(rrset, exp_rev_addr, dns::RRClass::IN(), dns::RRType::PTR(),
            ttl, ncr);

    // Verify the DHCID add RR.
    ASSERT_TRUE(rrset = getRRFromSection(request, D2UpdateMessage::
                                                  SECTION_UPDATE, 3));
    checkRR(rrset, exp_rev_addr, dns::RRClass::IN(), dns::RRType::DHCID(),
            ttl, ncr);

    // Verify there are no RRs in the ADDITIONAL Section.
    checkRRCount(request, D2UpdateMessage::SECTION_ADDITIONAL, 0);

    // Verify that it will render toWire without throwing.
    dns::MessageRenderer renderer;
    ASSERT_NO_THROW(request->toWire(renderer));
}

void checkRemoveFwdAddressRequest(NameChangeTransaction& tran) {
    const D2UpdateMessagePtr& request = tran.getDnsUpdateRequest();
    ASSERT_TRUE(request);

    // Safety check.
    dhcp_ddns::NameChangeRequestPtr ncr = tran.getNcr();
    ASSERT_TRUE(ncr);

    std::string exp_zone_name = tran.getForwardDomain()->getName();
    std::string exp_fqdn = ncr->getFqdn();

    // Verify the zone section.
    checkZone(request, exp_zone_name);

    // Verify there is 1 RR in the PREREQUISITE Section.
    checkRRCount(request, D2UpdateMessage::SECTION_PREREQUISITE, 1);

    // Verify the DHCID matching assertion RR.
    dns::RRsetPtr rrset;
    ASSERT_TRUE(rrset = getRRFromSection(request, D2UpdateMessage::
                                                  SECTION_PREREQUISITE, 0));
    checkRR(rrset, exp_fqdn, dns::RRClass::IN(), dns::RRType::DHCID(),
            0, ncr);

    // Verify there is 1 RR in the UPDATE Section.
    checkRRCount(request, D2UpdateMessage::SECTION_UPDATE, 1);

    // Verify the FQDN/IP delete RR.
    const dns::RRType& exp_ip_rr_type = tran.getAddressRRType();
    ASSERT_TRUE(rrset = getRRFromSection(request, D2UpdateMessage::
                                                  SECTION_UPDATE, 0));
    checkRR(rrset, exp_fqdn, dns::RRClass::NONE(), exp_ip_rr_type,
            0, ncr);

    // Verify that it will render toWire without throwing.
    dns::MessageRenderer renderer;
    ASSERT_NO_THROW(request->toWire(renderer));
}

void checkRemoveFwdRRsRequest(NameChangeTransaction& tran) {
    const D2UpdateMessagePtr& request = tran.getDnsUpdateRequest();
    ASSERT_TRUE(request);

    // Safety check.
    dhcp_ddns::NameChangeRequestPtr ncr = tran.getNcr();
    ASSERT_TRUE(ncr);

    std::string exp_zone_name = tran.getForwardDomain()->getName();
    std::string exp_fqdn = ncr->getFqdn();

    // Verify the zone section.
    checkZone(request, exp_zone_name);

    // Verify there is 1 RR in the PREREQUISITE Section.
    checkRRCount(request, D2UpdateMessage::SECTION_PREREQUISITE, 3);

    // Verify the DHCID matches assertion.
    dns::RRsetPtr rrset;
    ASSERT_TRUE(rrset = getRRFromSection(request, D2UpdateMessage::
                                                  SECTION_PREREQUISITE, 0));
    checkRR(rrset, exp_fqdn, dns::RRClass::IN(), dns::RRType::DHCID(),
            0, ncr);

    // Verify the NO A RRs assertion.
    ASSERT_TRUE(rrset = getRRFromSection(request, D2UpdateMessage::
                                                  SECTION_PREREQUISITE, 1));
    checkRR(rrset, exp_fqdn, dns::RRClass::NONE(), dns::RRType::A(),
            0, ncr, NO_RDATA);

    // Verify the NO AAAA RRs assertion.
    ASSERT_TRUE(rrset = getRRFromSection(request, D2UpdateMessage::
                                                  SECTION_PREREQUISITE, 2));
    checkRR(rrset, exp_fqdn, dns::RRClass::NONE(), dns::RRType::AAAA(),
            0, ncr, NO_RDATA);

    // Verify there is 1 RR in the UPDATE Section.
    checkRRCount(request, D2UpdateMessage::SECTION_UPDATE, 1);

    // Verify the delete all for the FQDN RR.
    ASSERT_TRUE(rrset = getRRFromSection(request, D2UpdateMessage::
                                                  SECTION_UPDATE, 0));
    checkRR(rrset, exp_fqdn, dns::RRClass::ANY(), dns::RRType::ANY(),
            0, ncr);

    // Verify that it will render toWire without throwing.
    dns::MessageRenderer renderer;
    ASSERT_NO_THROW(request->toWire(renderer));
}

void checkRemoveRevPtrsRequest(NameChangeTransaction& tran) {
    const D2UpdateMessagePtr& request = tran.getDnsUpdateRequest();
    ASSERT_TRUE(request);

    // Safety check.
    dhcp_ddns::NameChangeRequestPtr ncr = tran.getNcr();
    ASSERT_TRUE(ncr);

    std::string exp_zone_name = tran.getReverseDomain()->getName();
    std::string exp_rev_addr = D2CfgMgr::reverseIpAddress(ncr->getIpAddress());

    // Verify the zone section.
    checkZone(request, exp_zone_name);

    // Verify there is 1 RR in the PREREQUISITE Section.
    checkRRCount(request, D2UpdateMessage::SECTION_PREREQUISITE, 1);

    // Verify the FQDN-PTRNAME assertion RR.
    dns::RRsetPtr rrset;
    ASSERT_TRUE(rrset = getRRFromSection(request, D2UpdateMessage::
                                                  SECTION_PREREQUISITE, 0));
    checkRR(rrset, exp_rev_addr, dns::RRClass::IN(), dns::RRType::PTR(),
            0, ncr);

    // Verify there is 1 RR in the UPDATE Section.
    checkRRCount(request, D2UpdateMessage::SECTION_UPDATE, 1);

    // Verify the delete all for the FQDN RR.
    ASSERT_TRUE(rrset = getRRFromSection(request, D2UpdateMessage::
                                                  SECTION_UPDATE, 0));
    checkRR(rrset, exp_rev_addr, dns::RRClass::ANY(), dns::RRType::ANY(),
            0, ncr);

    // Verify that it will render toWire without throwing.
    dns::MessageRenderer renderer;
    ASSERT_NO_THROW(request->toWire(renderer));
}

std::string toHexText(const uint8_t* data, size_t len) {
    std::ostringstream stream;
    stream << "Data length is: " << len << std::endl;
    for (int i = 0; i < len; ++i) {
        if (i > 0 && ((i % 16) == 0)) {
            stream << std::endl;
        }

        stream << setfill('0') << setw(2) << setbase(16)
               << static_cast<unsigned int>(data[i]) << " ";
    }

    return (stream.str());
}

}; // namespace isc::d2
}; // namespace isc
