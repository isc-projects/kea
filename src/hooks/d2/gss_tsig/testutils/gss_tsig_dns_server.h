// Copyright (C) 2021-2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef GSS_TSIG_DNS_SERVER_H
#define GSS_TSIG_DNS_SERVER_H

#include <asiolink/io_service.h>
#include <dns/message.h>
#include <gss_tsig_api.h>
#include <gss_tsig_context.h>
#include <managed_key.h>
#include <tkey_exchange.h>
#include <util/buffer.h>
#include <boost/asio/ip/udp.hpp>
#include <boost/asio/socket_base.hpp>

namespace isc {
namespace gss_tsig {
namespace test {

class DummyDNSServer {
public:
    /// @brief Constructor.
    ///
    /// @param io_service The IOService which handles IO operations.
    /// @param sign_tkey The flag which specifies if the server should sign the
    /// TKEY response.
    /// @param sign_update The flag which specifies if the server should sign
    /// the DNS update.
    /// @param only_tkey The flag which specifies if the server should only do
    /// TKEY exchanges.
    /// @param go_on The flag which specifies if the server should continue with
    /// receiving DNS updates.
    /// @param match_exact_key The flag which specifies if the server should
    /// check if the key name matches expected value.
    DummyDNSServer(isc::asiolink::IOServicePtr io_service,
                   bool sign_tkey = true, bool sign_update = true,
                   bool only_tkey = false, bool go_on = true,
                   bool match_exact_key = true) :
        io_service_(io_service), sign_tkey_(sign_tkey),
        sign_update_(sign_update), only_tkey_(only_tkey), go_on_(go_on),
        match_exact_key_(match_exact_key) {
    }

    /// @brief Destructor.
    ~DummyDNSServer() = default;

    /// @brief Start function which starts listening on UDP endpoint.
    ///
    /// @param io_service The IOService which handles IO operations.
    void start();

    /// @brief Read TKEY request from buffer.
    ///
    /// @param inbuf The request buffer.
    /// @param intoken The TKEY data which is extracted.
    /// @param key_name The key name.
    /// @param qid The request message qid.
    void readTKey(isc::util::InputBufferPtr inbuf,
                  isc::gss_tsig::GssApiBufferPtr& intoken,
                  isc::dns::Name& key_name, isc::dns::qid_t& qid);

    /// @brief Write TKEY reply to buffer.
    ///
    /// @param outtoken The TKEY data.
    /// @param key_name The key name.
    /// @param outbuf The reply buffer.
    /// @param srv_key The server key.
    /// @param qid The reply message qid.
    /// @param sign The flag which specifies if the server should sign the
    /// response.
    void writeTKey(isc::gss_tsig::GssApiBuffer& outtoken,
                   isc::dns::Name& key_name,
                   isc::util::OutputBufferPtr& outbuf,
                   isc::gss_tsig::GssTsigKeyPtr srv_key,
                   isc::dns::qid_t qid, bool sign);

    /// @brief Write BADNAME (20) TKEY reply to buffer in case of duplicate key.
    ///
    /// @param outbuf The reply buffer.
    /// @param qid The reply message qid.
    void writeTKeyDuplicate(isc::util::OutputBufferPtr& outbuf,
                            isc::dns::qid_t qid);

    /// @brief Handler invoked when test TKEY request is received.
    ///
    /// This callback handler is installed when performing async read on a
    /// socket to emulate reception of the TKEY request by a server.
    /// As a result, this handler will send an appropriate TKEY response
    /// message back to the address from which the request has come.
    ///
    /// @param socket A pointer to a socket used to receive a query and send a
    /// response.
    /// @param remote A pointer to an object which specifies the host (address
    /// and port) from which a request has come.
    /// @param receive_length A length (in bytes) of the received data.
    void udpTKeyExchangeReceiveHandler(boost::asio::ip::udp::socket* socket,
                                       boost::asio::ip::udp::endpoint* remote,
                                       size_t receive_length);

    /// @brief Handler invoked when test DNS update is received.
    ///
    /// This callback handler is installed when performing async read on a
    /// socket to emulate reception of the DNS Update request by a server.
    /// As a result, this handler will send an appropriate DNS Update response
    /// message back to the address from which the request has come.
    ///
    /// @param socket A pointer to a socket used to receive a query and send a
    /// response.
    /// @param remote A pointer to an object which specifies the host (address
    /// and port) from which a request has come.
    /// @param receive_length A length (in bytes) of the received data.
    void udpDNSUpdateReceiveHandler(boost::asio::ip::udp::socket* socket,
                                    boost::asio::ip::udp::endpoint* remote,
                                    size_t receive_length);

    /// @brief The IOService which handles IO operations.
    isc::asiolink::IOServicePtr io_service_;

    /// @brief The flag which specifies if the TKEY response should be signed.
    bool sign_tkey_;

    /// @brief The flag which specifies if the DNS update should be signed.
    bool sign_update_;

    /// @brief The flag which specifies if the server should only do TKEY
    /// exchanges.
    bool only_tkey_;

    /// @brief The flag which specifies if the server should continue with
    /// receiving DNS updates.
    bool go_on_;

    /// @brief The flag which specifies if the server should check if the key
    /// name matches expected value.
    bool match_exact_key_;

    /// @brief Maximum size of the internal buffers.
    static const size_t MAX_SIZE = 4096;

    /// @brief Server listening address.
    static const char* TEST_ADDRESS;

    /// @brief Server listening port.
    static const uint16_t TEST_PORT = 5376;

    /// @brief The receive buffer.
    uint8_t receive_buffer_[MAX_SIZE];

    /// @brief The UDP socket.
    std::unique_ptr<boost::asio::ip::udp::socket> socket_;

    /// @brief The UDP socket endpoint.
    std::unique_ptr<boost::asio::ip::udp::endpoint> endpoint_;

    /// @brief The GSS-TSIG server key.
    ManagedKeyPtr srv_key_;

    /// @brief The list of sent keys.
    std::set<std::string> keys_;
};

}
}
}

#endif
