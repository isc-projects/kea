// Copyright (C) 2013  Internet Systems Consortium, Inc. ("ISC")
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

#include <d2/d2_cfg_mgr.h>
#include <dns/opcode.h>
#include <dns/messagerenderer.h>
#include <nc_test_utils.h>

#include <gtest/gtest.h>

using namespace std;
using namespace isc;
using namespace isc::d2;

namespace isc {
namespace d2 {

const char* TEST_DNS_SERVER_IP = "127.0.0.1";
size_t TEST_DNS_SERVER_PORT = 5301;

//*************************** FauxServer class ***********************

FauxServer::FauxServer(asiolink::IOService& io_service,
                       asiolink::IOAddress& address, size_t port)
    :io_service_(io_service), address_(address), port_(port),
     server_socket_() {
    server_socket_.reset(new asio::ip::udp::socket(io_service_.get_io_service(),
                                                   asio::ip::udp::v4()));
    server_socket_->set_option(asio::socket_base::reuse_address(true));
    server_socket_->bind(asio::ip::udp::endpoint(address_.getAddress(), port_));
}

FauxServer::FauxServer(asiolink::IOService& io_service,
                       DnsServerInfo& server)
    :io_service_(io_service), address_(server.getIpAddress()),
     port_(server.getPort()), server_socket_() {
    server_socket_.reset(new asio::ip::udp::socket(io_service_.get_io_service(),
                                                   asio::ip::udp::v4()));
    server_socket_->set_option(asio::socket_base::reuse_address(true));
    server_socket_->bind(asio::ip::udp::endpoint(address_.getAddress(), port_));
}


FauxServer::~FauxServer() {
}

void
FauxServer::receive (const ResponseMode& response_mode,
                     const dns::Rcode& response_rcode) {
    server_socket_->async_receive_from(asio::buffer(receive_buffer_,
                                                    sizeof(receive_buffer_)),
                                       remote_,
                                       boost::bind(&FauxServer::requestHandler,
                                                   this, _1, _2,
                                                   response_mode,
                                                   response_rcode));
}

void
FauxServer::requestHandler(const asio::error_code& error,
                           std::size_t bytes_recvd,
                           const ResponseMode& response_mode,
                           const dns::Rcode& response_rcode) {
    // If we encountered an error or received no data then fail.
    // We expect the client to send good requests.
    if (error.value() != 0 || bytes_recvd < 1) {
        ADD_FAILURE() << "FauxServer receive failed" << error.message();
        return;
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
    } catch (const std::exception& ex) {
        // If the request cannot be parsed, then fail the test.
        // We expect the client to send good requests.
        ADD_FAILURE() << "FauxServer request is corrupt:" << ex.what();
        return;
    }

    // The request parsed ok, so let's build a response.
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
    response.toWire(renderer);

    // If mode is to ship garbage, then stomp on part of the rendered
    // message.
    if (response_mode == CORRUPT_RESP) {
        response_buf.writeUint16At(0xFFFF, 2);
    }

    // Ship the reponse via synchronous send.
    try {
        int cnt = server_socket_->send_to(asio::
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
}

//********************** TransactionTest class ***********************

const unsigned int TransactionTest::FORWARD_CHG = 0x01;
const unsigned int TransactionTest::REVERSE_CHG = 0x02;
const unsigned int TransactionTest::FWD_AND_REV_CHG = REVERSE_CHG | FORWARD_CHG;

TransactionTest::TransactionTest()
    : io_service_(new isc::asiolink::IOService()), ncr_(),
    timer_(*io_service_), run_time_(0) {
}

TransactionTest::~TransactionTest() {
}

void 
TransactionTest::runTimedIO(int run_time) {
    run_time_ = run_time;
    timer_.setup(boost::bind(&TransactionTest::timesUp, this), run_time_);
    io_service_->run();
}

void 
TransactionTest::timesUp() {
    io_service_->stop();
    FAIL() << "Test Time: " << run_time_ << " expired";
}

void 
TransactionTest::setupForIPv4Transaction(dhcp_ddns::NameChangeType chg_type, 
                                         int change_mask) {
    const char* msg_str =
        "{"
        " \"change_type\" : 0 , "
        " \"forward_change\" : true , "
        " \"reverse_change\" : true , "
        " \"fqdn\" : \"my.forward.example.com.\" , "
        " \"ip_address\" : \"192.168.2.1\" , "
        " \"dhcid\" : \"0102030405060708\" , "
        " \"lease_expires_on\" : \"20130121132405\" , "
        " \"lease_length\" : 1300 "
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
        forward_domain_ = makeDomain("example.com.");
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
        reverse_domain_ = makeDomain("2.168.192.in.addr.arpa.");
        addDomainServer(reverse_domain_, "reverse.example.com",
                        "127.0.0.1", 5301);
        addDomainServer(reverse_domain_, "reverse2.example.com",
                        "127.0.0.1", 5302);
    }
}

void 
TransactionTest::setupForIPv6Transaction(dhcp_ddns::NameChangeType chg_type,
                                         int change_mask) {
    const char* msg_str =
        "{"
        " \"change_type\" : 0 , "
        " \"forward_change\" : true , "
        " \"reverse_change\" : true , "
        " \"fqdn\" : \"my6.forward.example.com.\" , "
        " \"ip_address\" : \"2001:1::100\" , "
        " \"dhcid\" : \"0102030405060708\" , "
        " \"lease_expires_on\" : \"20130121132405\" , "
        " \"lease_length\" : 1300 "
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
        forward_domain_ = makeDomain("example.com.");
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
        reverse_domain_ = makeDomain("1.2001.ip6.arpa.");
        addDomainServer(reverse_domain_, "rev6-server.example.com",
                        "::1", 5301);
        addDomainServer(reverse_domain_, "rev6-server2.example.com",
                        "::1", 5302);
    }
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
              unsigned int exp_ttl, dhcp_ddns::NameChangeRequestPtr ncr) {
    // Verify the FQDN/DHCID RR fields.
    EXPECT_EQ(exp_name, rrset->getName().toText());
    EXPECT_EQ(exp_class.getCode(), rrset->getClass().getCode());
    EXPECT_EQ(exp_type.getCode(), rrset->getType().getCode());
    EXPECT_EQ(exp_ttl, rrset->getTTL().getValue());
    if (exp_type == dns::RRType::ANY() || exp_class == dns::RRClass::ANY()) {
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
    DdnsDomainPtr domain;
    DnsServerInfoStoragePtr servers(new DnsServerInfoStorage());
    domain.reset(new DdnsDomain(zone_name, key_name, servers));
    return (domain);
}

void addDomainServer(DdnsDomainPtr& domain, const std::string& name,
                     const std::string& ip, const size_t port) {
    DnsServerInfoPtr server(new DnsServerInfo(name, asiolink::IOAddress(ip),
                                              port));
    domain->getServers()->push_back(server);
}

// Verifies that the contents of the given transaction's  DNS update request
// is correct for adding a forward DNS entry
void checkForwardAddRequest(NameChangeTransaction& tran) {
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

    // First, Verify the FQDN/IP add RR.
    ASSERT_TRUE(rrset = getRRFromSection(request, D2UpdateMessage::
                                                  SECTION_UPDATE, 0));
    checkRR(rrset, exp_fqdn, dns::RRClass::IN(), exp_ip_rr_type, 0, ncr);

    // Now, verify the DHCID add RR.
    ASSERT_TRUE(rrset = getRRFromSection(request, D2UpdateMessage::
                                                  SECTION_UPDATE, 1));
    checkRR(rrset, exp_fqdn, dns::RRClass::IN(), dns::RRType::DHCID(), 0, ncr);

    // Verify there are no RRs in the ADDITIONAL Section.
    checkRRCount(request, D2UpdateMessage::SECTION_ADDITIONAL, 0);

    // Verify that it will render toWire without throwing.
    dns::MessageRenderer renderer;
    ASSERT_NO_THROW(request->toWire(renderer));
}

// Verifies that the contents of the given transaction's  DNS update request
// is correct for replacing a forward DNS entry
void checkForwardReplaceRequest(NameChangeTransaction& tran) {
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

    // Verify the FQDN delete RR.
    ASSERT_TRUE(rrset = getRRFromSection(request, D2UpdateMessage::
                                                  SECTION_UPDATE, 0));
    checkRR(rrset, exp_fqdn, dns::RRClass::ANY(), exp_ip_rr_type, 0, ncr);

    // Verify the FQDN/IP add RR.
    ASSERT_TRUE(rrset = getRRFromSection(request, D2UpdateMessage::
                                                  SECTION_UPDATE, 1));
    checkRR(rrset, exp_fqdn, dns::RRClass::IN(), exp_ip_rr_type, 0, ncr);

    // Verify there are no RRs in the ADDITIONAL Section.
    checkRRCount(request, D2UpdateMessage::SECTION_ADDITIONAL, 0);

    // Verify that it will render toWire without throwing.
    dns::MessageRenderer renderer;
    ASSERT_NO_THROW(request->toWire(renderer));
}

// Verifies that the contents of the given transaction's  DNS update request
// is correct for replacing a reverse DNS entry
void checkReverseReplaceRequest(NameChangeTransaction& tran) {
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
            0, ncr);

    // Verify the DHCID add RR.
    ASSERT_TRUE(rrset = getRRFromSection(request, D2UpdateMessage::
                                                  SECTION_UPDATE, 3));
    checkRR(rrset, exp_rev_addr, dns::RRClass::IN(), dns::RRType::DHCID(),
            0, ncr);

    // Verify there are no RRs in the ADDITIONAL Section.
    checkRRCount(request, D2UpdateMessage::SECTION_ADDITIONAL, 0);

    // Verify that it will render toWire without throwing.
    dns::MessageRenderer renderer;
    ASSERT_NO_THROW(request->toWire(renderer));
}

void checkForwardRemoveAddrsRequest(NameChangeTransaction& tran) {
    const D2UpdateMessagePtr& request = tran.getDnsUpdateRequest();
    ASSERT_TRUE(request);

    // Safety check.
    dhcp_ddns::NameChangeRequestPtr ncr = tran.getNcr();
    ASSERT_TRUE(ncr);
}

void checkForwardRemoveRRsRequest(NameChangeTransaction& tran) {
    const D2UpdateMessagePtr& request = tran.getDnsUpdateRequest();
    ASSERT_TRUE(request);

    // Safety check.
    dhcp_ddns::NameChangeRequestPtr ncr = tran.getNcr();
    ASSERT_TRUE(ncr);
}

void checkReverseRemoveRequest(NameChangeTransaction& tran) {
    const D2UpdateMessagePtr& request = tran.getDnsUpdateRequest();
    ASSERT_TRUE(request);

    // Safety check.
    dhcp_ddns::NameChangeRequestPtr ncr = tran.getNcr();
    ASSERT_TRUE(ncr);
}


}; // namespace isc::d2
}; // namespace isc
