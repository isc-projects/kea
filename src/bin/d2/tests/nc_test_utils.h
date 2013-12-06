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

#ifndef NC_TEST_UTILS_H
#define NC_TEST_UTILS_H

/// @file nc_test_utils.h prototypes for functions related transaction testing.

#include <d2/nc_trans.h>

#include <asio/ip/udp.hpp>
#include <asio/socket_base.hpp>
#include <gtest/gtest.h>

namespace isc {
namespace d2 {

extern const char* TEST_DNS_SERVER_IP;
extern size_t TEST_DNS_SERVER_PORT;

// Not extern'ed to allow use as array size
const int TEST_MSG_MAX = 1024;

typedef boost::shared_ptr<asio::ip::udp::socket> SocketPtr;

/// @brief This class simulates a DNS server.  It is capable of performing
/// an asynchronous read, governed by an IOService, and responding to received
/// requests in a given manner.
class FauxServer {
public:
    enum  ResponseMode {
        USE_RCODE,   // Generate a response with a given RCODE
        CORRUPT_RESP  // Generate a corrupt response
    };

    asiolink::IOService& io_service_;
    const asiolink::IOAddress& address_;
    size_t port_;
    SocketPtr server_socket_;
    asio::ip::udp::endpoint remote_;
    uint8_t receive_buffer_[TEST_MSG_MAX];

    /// @brief Constructor
    ///
    /// @param io_service IOService to be used for socket IO.
    /// @param address  IP address at which the server should listen.
    /// @param port Port number at which the server should listen.
    FauxServer(asiolink::IOService& io_service, asiolink::IOAddress& address,
               size_t port);

    /// @brief Constructor
    ///
    /// @param io_service IOService to be used for socket IO.
    /// @param server DnServerInfo of server the DNS server. This supplies the
    /// server's ip address and port.
    FauxServer(asiolink::IOService& io_service, DnsServerInfo& server);

    /// @brief Destructor
    virtual ~FauxServer();

    /// @brief Initiates an asynchronous receive
    ///
    /// Starts the server listening for requests.  Upon completion of the
    /// listen, the callback method, requestHandler, is invoked.
    ///
    /// @param response_mode Selects how the server responds to a request
    /// @param response_rcode The Rcode value set in the response. Not used
    /// for all modes.
    void receive (const ResponseMode& response_mode,
                  const dns::Rcode& response_rcode=dns::Rcode::NOERROR());

    /// @brief Socket IO Completion callback
    ///
    /// This method servers as the Server's UDP socket receive callback handler.
    /// When the receive completes the handler is invoked with the
    /// @param error result code of the receive (determined by asio layer)
    /// @param bytes_recvd number of bytes received, if any
    /// @param response_mode type of response the handler should produce
    /// @param response_rcode value of Rcode in the response constructed by
    /// handler
    void requestHandler(const asio::error_code& error,
                        std::size_t bytes_recvd,
                        const ResponseMode& response_mode,
                        const dns::Rcode& response_rcode);
};

/// @brief Base class Test fixture for testing transactions. 
class TransactionTest : public ::testing::Test {
public:
    IOServicePtr io_service_;
    dhcp_ddns::NameChangeRequestPtr ncr_;
    DdnsDomainPtr forward_domain_;
    DdnsDomainPtr reverse_domain_;
    asiolink::IntervalTimer timer_;
    int run_time_;

    static const unsigned int FORWARD_CHG;
    static const unsigned int REVERSE_CHG;
    static const unsigned int FWD_AND_REV_CHG; 

    TransactionTest();
    virtual ~TransactionTest();

    /// @brief Run the IO service for no more than a given amount of time.
    ///
    /// Uses an IntervalTimer to interrupt the invocation of IOService run(),
    /// after the given number of milliseconds elapse.  The timer executes
    /// the timesUp() method if it expires.
    ///
    /// @param run_time amount of time in milliseconds to allow run to execute.
    void runTimedIO(int run_time);

    /// @brief IO Timer expiration handler
    ///
    /// Stops the IOSerivce and fails the current test.
    virtual void timesUp();

    /// @todo
    /// @brief Creates a transaction which requests an IPv4 DNS update.
    ///
    /// The transaction is constructed around a predefined (i.e. "canned")
    /// IPv4 NameChangeRequest. The request has both forward and reverse DNS
    /// changes requested.  Based upon the change mask, the transaction
    /// will have either the forward, reverse, or both domains populated.
    ///
    /// @param change_mask determines which change directions are requested
    void setupForIPv4Transaction(dhcp_ddns::NameChangeType chg_type,
                                 int change_mask);

    /// @todo
    /// @brief Creates a transaction which requests an IPv6 DNS update.
    ///
    /// The transaction is constructed around a predefined (i.e. "canned")
    /// IPv6 NameChangeRequest. The request has both forward and reverse DNS
    /// changes requested.  Based upon the change mask, the transaction
    /// will have either the forward, reverse, or both domains populated.
    ///
    /// @param change_mask determines which change directions are requested
    void setupForIPv6Transaction(dhcp_ddns::NameChangeType chg_type, 
                                 int change_mask);
};


/// @brief Tests the number of RRs in a request section against a given count.
///
/// This function actually returns the number of RRsetPtrs in a section. Since
/// D2 only uses RRsets with a single RData in each (i.e. 1 RR), it is used
/// as the number of RRs.  The dns::Message::getRRCount() cannot be used for
/// this as it returns the number of RDatas in an RRSet which does NOT equate
/// to the number of RRs. RRs with no RData, those with class or type of ANY,
/// are not counted.
///
/// @param request DNS update request to test
/// @param section enum value of the section to count
/// @param count the expected number of RRs
extern void checkRRCount(const D2UpdateMessagePtr& request,
                         D2UpdateMessage::UpdateMsgSection section, int count);

/// @brief Tests the zone content of a given request.
///
/// @param request DNS update request to validate
/// @param exp_zone_name expected value of the zone name in the zone section
extern void checkZone(const D2UpdateMessagePtr& request,
                      const std::string& exp_zone_name);

/// @brief Tests the contents of an RRset
///
/// @param rrset Pointer the RRset to test
/// @param exp_name expected value of RRset name (FQDN or reverse ip)
/// @param exp_class expected RRClass value of RRset
/// @param exp_typ expected RRType value of RRset
/// @param exp_ttl  expected TTL value of RRset
/// @param ncr NameChangeRequest on which the RRset is based
extern void checkRR(dns::RRsetPtr rrset, const std::string& exp_name,
                    const dns::RRClass& exp_class, const dns::RRType& exp_type,
                    unsigned int exp_ttl, dhcp_ddns::NameChangeRequestPtr ncr);

/// @brief Fetches an RR(set) from a given section of a request
///
/// @param request DNS update request from which the RR should come
/// @param section enum value of the section from which the RR should come
/// @param index zero-based index of the RR of interest.
///
/// @return Pointer to the RR of interest, empty pointer if the index is out
/// of range.
extern dns::RRsetPtr getRRFromSection(const D2UpdateMessagePtr& request,
                                      D2UpdateMessage::UpdateMsgSection section,
                                      int index);
/// @brief Creates a NameChangeRequest from a JSON string
///
/// @param ncr_str JSON string form of a NameChangeRequest.  Example:
/// @code
///        const char* msg_str =
///            "{"
///            " \"change_type\" : 0 , "
///            " \"forward_change\" : true , "
///            " \"reverse_change\" : true , "
///            " \"fqdn\" : \"my.example.com.\" , "
///            " \"ip_address\" : \"192.168.2.1\" , "
///            " \"dhcid\" : \"0102030405060708\" , "
///            " \"lease_expires_on\" : \"20130121132405\" , "
///            " \"lease_length\" : 1300 "
///            "}";
///
/// @endcode

/// @brief Verifies a forward mapping addition DNS update request
///
/// Tests that the DNS Update request for a given transaction, is correct for
/// adding a forward DNS mapping.
///
/// @param tran Transaction containing the request to be verified.
extern void checkForwardAddRequest(NameChangeTransaction& tran);

/// @brief Verifies a forward mapping replacement DNS update request
///
/// Tests that the DNS Update request for a given transaction, is correct for
/// replacing a forward DNS mapping.
///
/// @param tran Transaction containing the request to be verified.
extern void checkForwardReplaceRequest(NameChangeTransaction& tran);

/// @brief Verifies a reverse mapping replacement DNS update request
///
/// Tests that the DNS Update request for a given transaction, is correct for
/// replacing a reverse DNS mapping.
///
/// @param tran Transaction containing the request to be verified.
extern void checkReverseReplaceRequest(NameChangeTransaction& tran);

/// @brief Verifies a forward address removal DNS update request
///
/// Tests that the DNS Update request for a given transaction, is correct for
/// removing the forward address DNS entry.
///
/// @param tran Transaction containing the request to be verified.
extern void checkForwardRemoveAddrsRequest(NameChangeTransaction& tran);

/// @brief Verifies a forward RR removal DNS update request
///
/// Tests that the DNS Update request for a given transaction, is correct for
/// removing forward RR DNS entries.
///
/// @param tran Transaction containing the request to be verified.
extern void checkForwardRemoveRRsRequest(NameChangeTransaction& tran);

/// @brief Verifies a reverse mapping removal DNS update request
///
/// Tests that the DNS Update request for a given transaction, is correct for
/// removing a reverse DNS mapping.
///
/// @param tran Transaction containing the request to be verified.
extern void checkReverseRemoveRequest(NameChangeTransaction& tran);


/// @brief Creates a NameChangeRequest from JSON string.
///
/// @param ncr_str string of JSON text from which to make the request.
///
/// @return Pointer to newly created request.
///
/// @throw Underlying methods may throw.
extern
dhcp_ddns::NameChangeRequestPtr makeNcrFromString(const std::string& ncr_str);

/// @brief Creates a DdnsDomain with the one server.
///
/// @param zone_name zone name of the domain
/// @param key_name TSIG key name of the TSIG key for this domain
///
/// @throw Underlying methods may throw.
extern DdnsDomainPtr makeDomain(const std::string& zone_name,
                                const std::string& key_name = "");

/// @brief Creates a DnsServerInfo and adds it to the given DdnsDomain.
///
/// The server is created and added to the domain, without duplicate entry
/// checking.
///
/// @param domain DdnsDomain to which to add the server
/// @param name new server's host name of the server
/// @param ip new server's ip address
/// @param port new server's port
///
/// @throw Underlying methods may throw.
extern void addDomainServer(DdnsDomainPtr& domain, const std::string& name,
                            const std::string& ip = TEST_DNS_SERVER_IP,
                            const size_t port = TEST_DNS_SERVER_PORT);

}; // namespace isc::d2
}; // namespace isc

#endif
