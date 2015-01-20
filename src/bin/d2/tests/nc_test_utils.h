// Copyright (C) 2013-2015 Internet Systems Consortium, Inc. ("ISC")
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

#include <asiolink/io_service.h>
#include <asiolink/interval_timer.h>
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
        USE_RCODE,    // Generate a response with a given RCODE
        CORRUPT_RESP, // Generate a corrupt response
        INVALID_TSIG  // Generate a repsonse with the wrong TSIG key
    };

    // Reference to IOService to use for IO processing.
    asiolink::IOService& io_service_;
    // IP address at which to listen for requests.
    const asiolink::IOAddress& address_;
    // Port on which to listen for requests.
    size_t port_;
    // Socket on which listening is done.
    SocketPtr server_socket_;
    // Stores the end point of requesting client.
    asio::ip::udp::endpoint remote_;
    // Buffer in which received packets are stuffed.
    uint8_t receive_buffer_[TEST_MSG_MAX];
    // Flag which indicates if a receive has been initiated but
    // not yet completed.
    bool receive_pending_;
    // Indicates if server is in perpetual receive mode. If true once
    // a receive has been completed, a new one will be automatically
    // initiated.
    bool perpetual_receive_;
    // TSIG Key to use to verify requests and sign responses.  If its
    // NULL TSIG is not used.
    dns::TSIGKeyPtr tsig_key_;

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
    /// @param server DnsServerInfo of server the DNS server. This supplies the
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
    /// When the receive completes the handler is invoked with the parameters
    /// listed.
    ///
    /// @param error result code of the receive (determined by asio layer)
    /// @param bytes_recvd number of bytes received, if any
    /// @param response_mode type of response the handler should produce
    /// @param response_rcode value of Rcode in the response constructed by
    /// handler
    void requestHandler(const asio::error_code& error,
                        std::size_t bytes_recvd,
                        const ResponseMode& response_mode,
                        const dns::Rcode& response_rcode);

    /// @brief Returns true if a receive has been started but not completed.
    bool isReceivePending() {
        return receive_pending_;
    }

    /// @brief Sets the TSIG key to the given value.
    ///
    /// @param tsig_key Pointer to the TSIG key to use.  If the pointer is
    /// empty, TSIG will not be used.
    void setTSIGKey (const dns::TSIGKeyPtr& tsig_key) {
        tsig_key_ = tsig_key;
    }
};

/// @brief Provides a means to process IOService IO for a finite amount of time.
///
/// This class instantiates an IOService provides a single method, runTimedIO
/// which will run the IOService for no more than a finite amount of time,
/// at least one event is executed or the IOService is stopped.
/// It provides an virtual handler for timer expiration event.  It is
/// intended to be used as a base class for test fixtures that need to process
/// IO by providing them a consistent way to do so while retaining a safety
/// valve so tests do not hang.
class TimedIO  {
public:
    asiolink::IOServicePtr io_service_;
    asiolink::IntervalTimer timer_;
    int run_time_;

    // Constructor
    TimedIO();

    // Destructor
    virtual ~TimedIO();

    /// @brief IO Timer expiration handler
    ///
    /// Stops the IOService and fails the current test.
    virtual void timesUp();

    /// @brief Processes IO till time expires or at least one handler executes.
    ///
    /// This method first polls IOService to run any ready handlers.  If no
    /// handlers are ready, it starts the internal time to run for the given
    /// amount of time and invokes service's run_one method.  This method
    /// blocks until at least one handler executes or the IO Service is stopped.
    /// Upon completion of this method the timer is cancelled.  Should the
    /// timer expires prior to run_one returning, the timesUp handler will be
    /// invoked which stops the IO service and fails the test.
    ///
    /// Note that this method closely mimics the runIO method in D2Process.
    ///
    /// @param run_time maximum length of time to run in milliseconds before
    /// timing out.
    ///
    /// @return Returns the number of handlers executed or zero. A return of
    /// zero indicates that the IOService has been stopped.
    int runTimedIO(int run_time);

};

/// @brief Base class Test fixture for testing transactions.
class TransactionTest : public TimedIO,  public ::testing::Test {
public:
    dhcp_ddns::NameChangeRequestPtr ncr_;
    DdnsDomainPtr forward_domain_;
    DdnsDomainPtr reverse_domain_;
    D2CfgMgrPtr cfg_mgr_;

    /// #brief constants used to specify change directions for a transaction.
    static const unsigned int FORWARD_CHG;      // Only forward change.
    static const unsigned int REVERSE_CHG;      // Only reverse change.
    static const unsigned int FWD_AND_REV_CHG;  // Both forward and reverse.

    TransactionTest();
    virtual ~TransactionTest();

    /// @brief Creates a transaction which requests an IPv4 DNS update.
    ///
    /// The transaction is constructed around a predefined (i.e. "canned")
    /// IPv4 NameChangeRequest. The request has both forward and reverse DNS
    /// changes requested.  Based upon the change mask, the transaction
    /// will have either the forward, reverse, or both domains populated.
    ///
    /// @param change_type selects the type of change requested, CHG_ADD or
    /// CHG_REMOVE.
    /// @param change_mask determines which change directions are requested
    /// FORWARD_CHG, REVERSE_CHG, or FWD_AND_REV_CHG.
    /// @param tsig_key_info pointer to the TSIGKeyInfo to assign to both
    /// domains in the transaction.  This will cause the transaction to
    /// use TSIG.  If the pointer is empty, TSIG will not be used.
    void setupForIPv4Transaction(dhcp_ddns::NameChangeType change_type,
                                 int change_mask,
                                 const TSIGKeyInfoPtr& tsig_key_info =
                                 TSIGKeyInfoPtr());

    /// @brief Creates a transaction which requests an IPv4 DNS update.
    ///
    /// Convenience wrapper around the above method which accepts a string
    /// key_name from which the TSIGKeyInfo is constructed.  Note the string
    /// may not be blank.
    ///
    /// @param change_type selects the type of change requested, CHG_ADD or
    /// CHG_REMOVE.
    /// @param change_mask determines which change directions are requested
    /// FORWARD_CHG, REVERSE_CHG, or FWD_AND_REV_CHG.
    /// @param key_name value to use to create TSIG key. The value may not
    /// be blank.
    void setupForIPv4Transaction(dhcp_ddns::NameChangeType change_type,
                                 int change_mask, const std::string& key_name);

    /// @brief Creates a transaction which requests an IPv6 DNS update.
    ///
    /// The transaction is constructed around a predefined (i.e. "canned")
    /// IPv6 NameChangeRequest. The request has both forward and reverse DNS
    /// changes requested.  Based upon the change mask, the transaction
    /// will have either the forward, reverse, or both domains populated.
    ///
    /// @param change_type selects the type of change requested, CHG_ADD or
    /// CHG_REMOVE.
    /// @param change_mask determines which change directions are requested
    /// FORWARD_CHG, REVERSE_CHG, or FWD_AND_REV_CHG.
    /// @param tsig_key_info pointer to the TSIGKeyInfo to assign to both
    /// domains in the transaction.  This will cause the transaction to
    /// use TSIG.  If the pointer is empty, TSIG will not be used.
    void setupForIPv6Transaction(dhcp_ddns::NameChangeType change_type,
                                 int change_mask,
                                 const TSIGKeyInfoPtr& tsig_key_info =
                                 TSIGKeyInfoPtr());

    /// @brief Creates a transaction which requests an IPv6 DNS update.
    ///
    /// Convenience wrapper around the above method which accepts a string
    /// key_name from which the TSIGKeyInfo is constructed.  Note the string
    /// may not be blank.
    ///
    /// @param change_type selects the type of change requested, CHG_ADD or
    /// CHG_REMOVE.
    /// @param change_mask determines which change directions are requested
    /// FORWARD_CHG, REVERSE_CHG, or FWD_AND_REV_CHG.
    /// @param key_name value to use to create TSIG key, if blank TSIG will not
    /// be used.
    void setupForIPv6Transaction(dhcp_ddns::NameChangeType change_type,
                                 int change_mask, const std::string& key_name);

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
/// @param has_rdata if true, RRset's rdata will be checked based on it's
/// RRType.  Set this to false if the RRset's type supports Rdata but it does
/// not contain it.  For instance, prerequisites of type NONE have no Rdata
/// where updates of type NONE may.
extern void checkRR(dns::RRsetPtr rrset, const std::string& exp_name,
                    const dns::RRClass& exp_class, const dns::RRType& exp_type,
                    unsigned int exp_ttl, dhcp_ddns::NameChangeRequestPtr ncr,
                    bool has_rdata=true);

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
extern void checkAddFwdAddressRequest(NameChangeTransaction& tran);

/// @brief Verifies a forward mapping replacement DNS update request
///
/// Tests that the DNS Update request for a given transaction, is correct for
/// replacing a forward DNS mapping.
///
/// @param tran Transaction containing the request to be verified.
extern void checkReplaceFwdAddressRequest(NameChangeTransaction& tran);

/// @brief Verifies a reverse mapping replacement DNS update request
///
/// Tests that the DNS Update request for a given transaction, is correct for
/// replacing a reverse DNS mapping.
///
/// @param tran Transaction containing the request to be verified.
extern void checkReplaceRevPtrsRequest(NameChangeTransaction& tran);

/// @brief Verifies a forward address removal DNS update request
///
/// Tests that the DNS Update request for a given transaction, is correct for
/// removing the forward address DNS entry.
///
/// @param tran Transaction containing the request to be verified.
extern void checkRemoveFwdAddressRequest(NameChangeTransaction& tran);

/// @brief Verifies a forward RR removal DNS update request
///
/// Tests that the DNS Update request for a given transaction, is correct for
/// removing forward RR DNS entries.
///
/// @param tran Transaction containing the request to be verified.
extern void checkRemoveFwdRRsRequest(NameChangeTransaction& tran);

/// @brief Verifies a reverse mapping removal DNS update request
///
/// Tests that the DNS Update request for a given transaction, is correct for
/// removing a reverse DNS mapping.
///
/// @param tran Transaction containing the request to be verified.
extern void checkRemoveRevPtrsRequest(NameChangeTransaction& tran);


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
/// @param key_name TSIG key name of the TSIG key for this domain. It will
/// create a TSIGKeyInfo based on the key_name and assign it to the domain.
///
/// @throw Underlying methods may throw.
extern DdnsDomainPtr makeDomain(const std::string& zone_name,
                                const std::string& key_name);

/// @brief Creates a DdnsDomain with the one server.
///
/// @param zone_name zone name of the domain
/// @param tsig_key_info pointer to the TSIGInfog key for this domain.
/// Defaults to an empty pointer, meaning this domain has no key.
///
/// @throw Underlying methods may throw.
extern DdnsDomainPtr makeDomain(const std::string& zone_name,
                                const TSIGKeyInfoPtr&
                                tsig_key_info = TSIGKeyInfoPtr());

/// @brief Creates a TSIGKeyInfo
///
/// @param key_name name of the key
/// @param secret key secret data as a base64 encoded string. If blank,
/// then the secret value will be generated from key_name.
/// @param algorithm algorithm to use. Defaults to MD5.
/// @return a TSIGKeyInfoPtr for the newly created key.  If key_name is blank
/// the pointer will be empty.
/// @throw Underlying methods may throw.
extern
TSIGKeyInfoPtr makeTSIGKeyInfo(const std::string& key_name,
                               const std::string& secret = "",
                               const std::string& algorithm
                               = TSIGKeyInfo::HMAC_MD5_STR);

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

/// @brief Creates a hex text dump of the given data buffer.
///
/// This method is not used for testing but is handy for debugging.  It creates
/// a pleasantly formatted string of 2-digits per byte separated by spaces with
/// 16 bytes per line.
///
/// @param data pointer to the data to dump
/// @param len size (in bytes) of data
extern std::string toHexText(const uint8_t* data, size_t len);

}; // namespace isc::d2
}; // namespace isc

#endif
