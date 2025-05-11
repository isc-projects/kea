// Copyright (C) 2021-2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <d2srv/dns_client.h>
#include <dns/messagerenderer.h>
#include <dns/opcode.h>
#include <dns/rdata.h>
#include <dns/rdataclass.h>
#include <gss_tsig_dns_server.h>

#include <gtest/gtest.h>

namespace isc {
namespace gss_tsig {
namespace test {

using namespace boost::asio;
using namespace boost::asio::ip;
using namespace isc;
using namespace isc::asiolink;
using namespace isc::d2;
using namespace isc::dns;
using namespace isc::dns::rdata;
using namespace isc::dns::rdata::generic;
using namespace isc::util;
using namespace std;
namespace ph = std::placeholders;

const char* DummyDNSServer::TEST_ADDRESS = "127.0.0.1";

void
DummyDNSServer::start() {
    // In order to perform the full test, when the client sends the request
    // and receives a response from the server, we have to emulate the
    // server's response in the test. A request will be sent via loopback
    // interface to 127.0.0.1 and known test port. Response must be sent
    // to 127.0.0.1 and the source port which has been used to send the
    // request. A new socket is created, specifically to handle sending
    // responses. The reuse address option is set so as both sockets can
    // use the same address. This new socket is bound to the test address
    // and port, where requests will be sent.
    socket_.reset(new udp::socket(io_service_->getInternalIOService(),
                                  boost::asio::ip::udp::v4()));
    socket_->set_option(socket_base::reuse_address(true));
    socket_->bind(udp::endpoint(make_address(TEST_ADDRESS), TEST_PORT));
    // Once socket is created, we can post an IO request to receive some
    // packet from this socket. This is asynchronous operation and
    // nothing is received until another IO request to send a query is
    // posted and the run() is invoked on this IO. A callback function is
    // attached to this asynchronous read. This callback function requires
    // that a socket object used to receive the request is passed to it,
    // because the same socket will be used by the callback function to send
    // a response. Also, the remote object is passed to the callback,
    // because it holds a source address and port where request originated.
    // Callback function will send a response to this address and port.
    // The last parameter holds a length of the received request. It is
    // required to construct a response.
    endpoint_.reset(new udp::endpoint());
    socket_->async_receive_from(boost::asio::buffer(receive_buffer_,
                                                    sizeof(receive_buffer_)),
                                *endpoint_,
                                std::bind(&DummyDNSServer::udpTKeyExchangeReceiveHandler,
                                          this, socket_.get(), endpoint_.get(),
                                          ph::_2));
}

void
DummyDNSServer::readTKey(InputBufferPtr inbuf, GssApiBufferPtr& intoken,
                         Name& key_name, qid_t& qid) {
    MessagePtr msg(new Message(Message::PARSE));
    msg->fromWire(*inbuf);
    qid = msg->getQid();
    // Validate the TKEY response.
    ASSERT_FALSE(msg->getHeaderFlag(Message::HEADERFLAG_QR));
    ASSERT_EQ(msg->getRcode(), Rcode::NOERROR());
    ASSERT_EQ(msg->getOpcode(), Opcode::QUERY());
    ASSERT_EQ(msg->getRRCount(Message::SECTION_QUESTION), 1);
    QuestionPtr question = *msg->beginQuestion();
    ASSERT_TRUE(question);
    ASSERT_EQ(question->getClass(), RRClass::ANY());
    ASSERT_EQ(question->getType(), RRType::TKEY());
    RRsetPtr rrset = *msg->beginSection(Message::SECTION_ADDITIONAL);
    ASSERT_TRUE(rrset);
    key_name = rrset->getName();
    ASSERT_EQ(rrset->getClass(), RRClass::ANY());
    ASSERT_EQ(rrset->getType(), RRType::TKEY());
    ASSERT_EQ(rrset->getRdataCount(), 1);
    auto rdata_it = rrset->getRdataIterator();
    const TKEY& tkey = dynamic_cast<const TKEY&>(rdata_it->getCurrent());
    ASSERT_EQ(tkey.getError(), Rcode::NOERROR_CODE);
    intoken.reset(new GssApiBuffer(tkey.getKeyLen(), tkey.getKey()));
}

void
DummyDNSServer::writeTKey(GssApiBuffer& outtoken, Name& key_name,
                          OutputBufferPtr& outbuf, GssTsigKeyPtr srv_key,
                          qid_t qid, bool sign) {
    MessagePtr msg(new Message(Message::RENDER));
    msg->setOpcode(Opcode::QUERY());
    msg->setRcode(Rcode::NOERROR());
    msg->setQid(qid);
    msg->setHeaderFlag(Message::HEADERFLAG_QR, true);
    msg->addQuestion(Question(key_name, RRClass::ANY(), RRType::TKEY()));

    // Create the TKEY Resource Record.
    RRsetPtr tkey_rrset(new RRset(key_name, RRClass::ANY(),
                                  RRType::TKEY(), RRTTL(0)));
    Name algorithm("gss-tsig.");
    uint32_t inception = static_cast<uint32_t>(time(0));
    uint32_t expire = inception + 3600;
    uint16_t mode = TKEY::GSS_API_MODE;
    uint16_t error = Rcode::NOERROR().getCode();
    uint16_t key_len = static_cast<uint16_t>(outtoken.getLength());
    ConstRdataPtr tkey_rdata(new TKEY(algorithm, inception, expire, mode, error,
                                      key_len, outtoken.getValue(), 0, 0));
    tkey_rrset->addRdata(tkey_rdata);
    msg->addRRset(Message::SECTION_ANSWER, tkey_rrset);

    // Encode the TKEY request.
    MessageRenderer renderer;
    outbuf.reset(new OutputBuffer(MAX_SIZE));
    renderer.setBuffer(outbuf.get());
    renderer.setLengthLimit(MAX_SIZE);

    if (sign && srv_key) {
        TSIGContextPtr context = srv_key->createContext();
        msg->toWire(renderer, context.get());
    } else {
        msg->toWire(renderer);
    }
}

void
DummyDNSServer::writeTKeyDuplicate(OutputBufferPtr& outbuf, qid_t qid) {
    MessagePtr msg(new Message(Message::RENDER));
    msg->setOpcode(Opcode::QUERY());
    // BADNAME Duplicate key name [RFC 2930]
    msg->setRcode(Rcode(20));
    msg->setQid(qid);
    // Encode the TKEY request.
    MessageRenderer renderer;
    outbuf.reset(new OutputBuffer(MAX_SIZE));
    renderer.setBuffer(outbuf.get());
    renderer.setLengthLimit(MAX_SIZE);
    msg->toWire(renderer);
}

void
DummyDNSServer::udpTKeyExchangeReceiveHandler(udp::socket* socket,
                                              udp::endpoint* remote,
                                              size_t receive_length) {
    OM_uint32 lifetime = 0;
    GssApiName srv_name("DNS/blu.example.nil@EXAMPLE.NIL");
    GssApiCredPtr srv_cred(new GssApiCred(srv_name, GSS_C_ACCEPT, lifetime));

    InputBufferPtr recv_buf(new InputBuffer(receive_buffer_, receive_length));

    GssApiBufferPtr intoken;
    qid_t qid;
    Name key_name("foo");
    readTKey(recv_buf, intoken, key_name, qid);
    ASSERT_TRUE(intoken);

    string key_str = key_name.toText();
    if (match_exact_key_) {
        ASSERT_EQ(key_str, "1234.sig-blu.example.nil.");
    }
    OutputBufferPtr send_buf;
    if (keys_.find(key_str) != keys_.end()) {
        ASSERT_NO_THROW(writeTKeyDuplicate(send_buf, qid));
    } else {
        keys_.insert(key_str);
        srv_key_.reset(new ManagedKey(key_str));

        GssApiBuffer outtoken;
        GssApiName client_name;
        ASSERT_NO_THROW(srv_key_->getSecCtx().accept(*srv_cred, *intoken,
                                                     client_name, outtoken));


        ASSERT_NO_THROW(writeTKey(outtoken, key_name, send_buf, srv_key_, qid,
                                  sign_tkey_));
    }
    ASSERT_TRUE(send_buf);

    // A response message is now ready to send. Send it!
    socket->send_to(boost::asio::buffer(send_buf->getData(),
                                        send_buf->getLength()),
                    *remote);

    if (!go_on_) {
        return;
    }

    if (only_tkey_) {
        socket_->async_receive_from(boost::asio::buffer(receive_buffer_,
                                                        sizeof(receive_buffer_)),
                                    *endpoint_,
                                    std::bind(&DummyDNSServer::udpTKeyExchangeReceiveHandler,
                                              this, socket_.get(), endpoint_.get(),
                                              ph::_2));
    } else {
        socket_->async_receive_from(boost::asio::buffer(receive_buffer_,
                                                        sizeof(receive_buffer_)),
                                    *endpoint_,
                                    std::bind(&DummyDNSServer::udpDNSUpdateReceiveHandler,
                                              this, socket_.get(), endpoint_.get(),
                                              ph::_2));
    }
}

void
DummyDNSServer::udpDNSUpdateReceiveHandler(udp::socket* socket,
                                           udp::endpoint* remote,
                                           size_t receive_length) {
    TSIGContextPtr context;
    if (sign_update_ && srv_key_) {
        context = srv_key_->createContext();
    }

    isc::util::InputBuffer received_data_buffer(receive_buffer_,
                                                receive_length);

    dns::Message request(Message::PARSE);
    request.fromWire(received_data_buffer);

    // If context is not NULL, then we need to verify the message.
    if (context) {
        TSIGError error = context->verify(request.getTSIGRecord(),
                                          receive_buffer_, receive_length);
        if (error != TSIGError::NOERROR()) {
            isc_throw(TSIGVerifyError, "TSIG verification failed: "
                      << error.toText());
        }
    }

    dns::Message response(Message::RENDER);
    response.setOpcode(Opcode(Opcode::UPDATE_CODE));
    response.setHeaderFlag(dns::Message::HEADERFLAG_QR, true);
    response.setQid(request.getQid());
    response.setRcode(Rcode::NOERROR());
    dns::Question question(Name("example.com."),
                                RRClass::IN(), RRType::SOA());
    response.addQuestion(question);

    MessageRenderer renderer;

    if (context) {
        response.toWire(renderer, context.get());
    } else {
        response.toWire(renderer);
    }
    // A response message is now ready to send. Send it!
    socket->send_to(boost::asio::buffer(renderer.getData(),
                    renderer.getLength()), *remote);
}
}
}

}
