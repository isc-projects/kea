// File created from ../../../src/bin/d2/d2_messages.mes on Fri Feb 08 2019 20:33

#include <cstddef>
#include <log/message_types.h>
#include <log/message_initializer.h>

namespace isc {
namespace d2 {

extern const isc::log::MessageID DHCP_DDNS_ADD_FAILED = "DHCP_DDNS_ADD_FAILED";
extern const isc::log::MessageID DHCP_DDNS_ADD_SUCCEEDED = "DHCP_DDNS_ADD_SUCCEEDED";
extern const isc::log::MessageID DHCP_DDNS_ALREADY_RUNNING = "DHCP_DDNS_ALREADY_RUNNING";
extern const isc::log::MessageID DHCP_DDNS_AT_MAX_TRANSACTIONS = "DHCP_DDNS_AT_MAX_TRANSACTIONS";
extern const isc::log::MessageID DHCP_DDNS_CLEARED_FOR_SHUTDOWN = "DHCP_DDNS_CLEARED_FOR_SHUTDOWN";
extern const isc::log::MessageID DHCP_DDNS_COMMAND = "DHCP_DDNS_COMMAND";
extern const isc::log::MessageID DHCP_DDNS_CONFIGURE = "DHCP_DDNS_CONFIGURE";
extern const isc::log::MessageID DHCP_DDNS_CONFIG_CHECK_FAIL = "DHCP_DDNS_CONFIG_CHECK_FAIL";
extern const isc::log::MessageID DHCP_DDNS_CONFIG_FAIL = "DHCP_DDNS_CONFIG_FAIL";
extern const isc::log::MessageID DHCP_DDNS_FAILED = "DHCP_DDNS_FAILED";
extern const isc::log::MessageID DHCP_DDNS_FORWARD_ADD_BAD_DNSCLIENT_STATUS = "DHCP_DDNS_FORWARD_ADD_BAD_DNSCLIENT_STATUS";
extern const isc::log::MessageID DHCP_DDNS_FORWARD_ADD_BUILD_FAILURE = "DHCP_DDNS_FORWARD_ADD_BUILD_FAILURE";
extern const isc::log::MessageID DHCP_DDNS_FORWARD_ADD_IO_ERROR = "DHCP_DDNS_FORWARD_ADD_IO_ERROR";
extern const isc::log::MessageID DHCP_DDNS_FORWARD_ADD_REJECTED = "DHCP_DDNS_FORWARD_ADD_REJECTED";
extern const isc::log::MessageID DHCP_DDNS_FORWARD_ADD_RESP_CORRUPT = "DHCP_DDNS_FORWARD_ADD_RESP_CORRUPT";
extern const isc::log::MessageID DHCP_DDNS_FORWARD_REMOVE_ADDRS_BAD_DNSCLIENT_STATUS = "DHCP_DDNS_FORWARD_REMOVE_ADDRS_BAD_DNSCLIENT_STATUS";
extern const isc::log::MessageID DHCP_DDNS_FORWARD_REMOVE_ADDRS_BUILD_FAILURE = "DHCP_DDNS_FORWARD_REMOVE_ADDRS_BUILD_FAILURE";
extern const isc::log::MessageID DHCP_DDNS_FORWARD_REMOVE_ADDRS_IO_ERROR = "DHCP_DDNS_FORWARD_REMOVE_ADDRS_IO_ERROR";
extern const isc::log::MessageID DHCP_DDNS_FORWARD_REMOVE_ADDRS_REJECTED = "DHCP_DDNS_FORWARD_REMOVE_ADDRS_REJECTED";
extern const isc::log::MessageID DHCP_DDNS_FORWARD_REMOVE_ADDRS_RESP_CORRUPT = "DHCP_DDNS_FORWARD_REMOVE_ADDRS_RESP_CORRUPT";
extern const isc::log::MessageID DHCP_DDNS_FORWARD_REMOVE_RRS_BAD_DNSCLIENT_STATUS = "DHCP_DDNS_FORWARD_REMOVE_RRS_BAD_DNSCLIENT_STATUS";
extern const isc::log::MessageID DHCP_DDNS_FORWARD_REMOVE_RRS_BUILD_FAILURE = "DHCP_DDNS_FORWARD_REMOVE_RRS_BUILD_FAILURE";
extern const isc::log::MessageID DHCP_DDNS_FORWARD_REMOVE_RRS_IO_ERROR = "DHCP_DDNS_FORWARD_REMOVE_RRS_IO_ERROR";
extern const isc::log::MessageID DHCP_DDNS_FORWARD_REMOVE_RRS_REJECTED = "DHCP_DDNS_FORWARD_REMOVE_RRS_REJECTED";
extern const isc::log::MessageID DHCP_DDNS_FORWARD_REMOVE_RRS_RESP_CORRUPT = "DHCP_DDNS_FORWARD_REMOVE_RRS_RESP_CORRUPT";
extern const isc::log::MessageID DHCP_DDNS_FORWARD_REPLACE_BAD_DNSCLIENT_STATUS = "DHCP_DDNS_FORWARD_REPLACE_BAD_DNSCLIENT_STATUS";
extern const isc::log::MessageID DHCP_DDNS_FORWARD_REPLACE_BUILD_FAILURE = "DHCP_DDNS_FORWARD_REPLACE_BUILD_FAILURE";
extern const isc::log::MessageID DHCP_DDNS_FORWARD_REPLACE_IO_ERROR = "DHCP_DDNS_FORWARD_REPLACE_IO_ERROR";
extern const isc::log::MessageID DHCP_DDNS_FORWARD_REPLACE_REJECTED = "DHCP_DDNS_FORWARD_REPLACE_REJECTED";
extern const isc::log::MessageID DHCP_DDNS_FORWARD_REPLACE_RESP_CORRUPT = "DHCP_DDNS_FORWARD_REPLACE_RESP_CORRUPT";
extern const isc::log::MessageID DHCP_DDNS_FWD_REQUEST_IGNORED = "DHCP_DDNS_FWD_REQUEST_IGNORED";
extern const isc::log::MessageID DHCP_DDNS_INVALID_RESPONSE = "DHCP_DDNS_INVALID_RESPONSE";
extern const isc::log::MessageID DHCP_DDNS_NOT_ON_LOOPBACK = "DHCP_DDNS_NOT_ON_LOOPBACK";
extern const isc::log::MessageID DHCP_DDNS_NO_ELIGIBLE_JOBS = "DHCP_DDNS_NO_ELIGIBLE_JOBS";
extern const isc::log::MessageID DHCP_DDNS_NO_FWD_MATCH_ERROR = "DHCP_DDNS_NO_FWD_MATCH_ERROR";
extern const isc::log::MessageID DHCP_DDNS_NO_MATCH = "DHCP_DDNS_NO_MATCH";
extern const isc::log::MessageID DHCP_DDNS_NO_REV_MATCH_ERROR = "DHCP_DDNS_NO_REV_MATCH_ERROR";
extern const isc::log::MessageID DHCP_DDNS_PROCESS_INIT = "DHCP_DDNS_PROCESS_INIT";
extern const isc::log::MessageID DHCP_DDNS_QUEUE_MGR_QUEUE_FULL = "DHCP_DDNS_QUEUE_MGR_QUEUE_FULL";
extern const isc::log::MessageID DHCP_DDNS_QUEUE_MGR_QUEUE_RECEIVE = "DHCP_DDNS_QUEUE_MGR_QUEUE_RECEIVE";
extern const isc::log::MessageID DHCP_DDNS_QUEUE_MGR_RECONFIGURING = "DHCP_DDNS_QUEUE_MGR_RECONFIGURING";
extern const isc::log::MessageID DHCP_DDNS_QUEUE_MGR_RECOVERING = "DHCP_DDNS_QUEUE_MGR_RECOVERING";
extern const isc::log::MessageID DHCP_DDNS_QUEUE_MGR_RECV_ERROR = "DHCP_DDNS_QUEUE_MGR_RECV_ERROR";
extern const isc::log::MessageID DHCP_DDNS_QUEUE_MGR_RESUME_ERROR = "DHCP_DDNS_QUEUE_MGR_RESUME_ERROR";
extern const isc::log::MessageID DHCP_DDNS_QUEUE_MGR_RESUMING = "DHCP_DDNS_QUEUE_MGR_RESUMING";
extern const isc::log::MessageID DHCP_DDNS_QUEUE_MGR_STARTED = "DHCP_DDNS_QUEUE_MGR_STARTED";
extern const isc::log::MessageID DHCP_DDNS_QUEUE_MGR_START_ERROR = "DHCP_DDNS_QUEUE_MGR_START_ERROR";
extern const isc::log::MessageID DHCP_DDNS_QUEUE_MGR_STOPPED = "DHCP_DDNS_QUEUE_MGR_STOPPED";
extern const isc::log::MessageID DHCP_DDNS_QUEUE_MGR_STOPPING = "DHCP_DDNS_QUEUE_MGR_STOPPING";
extern const isc::log::MessageID DHCP_DDNS_QUEUE_MGR_STOP_ERROR = "DHCP_DDNS_QUEUE_MGR_STOP_ERROR";
extern const isc::log::MessageID DHCP_DDNS_QUEUE_MGR_UNEXPECTED_HANDLER_ERROR = "DHCP_DDNS_QUEUE_MGR_UNEXPECTED_HANDLER_ERROR";
extern const isc::log::MessageID DHCP_DDNS_QUEUE_MGR_UNEXPECTED_STOP = "DHCP_DDNS_QUEUE_MGR_UNEXPECTED_STOP";
extern const isc::log::MessageID DHCP_DDNS_REMOVE_FAILED = "DHCP_DDNS_REMOVE_FAILED";
extern const isc::log::MessageID DHCP_DDNS_REMOVE_SUCCEEDED = "DHCP_DDNS_REMOVE_SUCCEEDED";
extern const isc::log::MessageID DHCP_DDNS_REQUEST_DROPPED = "DHCP_DDNS_REQUEST_DROPPED";
extern const isc::log::MessageID DHCP_DDNS_REVERSE_REMOVE_BAD_DNSCLIENT_STATUS = "DHCP_DDNS_REVERSE_REMOVE_BAD_DNSCLIENT_STATUS";
extern const isc::log::MessageID DHCP_DDNS_REVERSE_REMOVE_BUILD_FAILURE = "DHCP_DDNS_REVERSE_REMOVE_BUILD_FAILURE";
extern const isc::log::MessageID DHCP_DDNS_REVERSE_REMOVE_IO_ERROR = "DHCP_DDNS_REVERSE_REMOVE_IO_ERROR";
extern const isc::log::MessageID DHCP_DDNS_REVERSE_REMOVE_REJECTED = "DHCP_DDNS_REVERSE_REMOVE_REJECTED";
extern const isc::log::MessageID DHCP_DDNS_REVERSE_REMOVE_RESP_CORRUPT = "DHCP_DDNS_REVERSE_REMOVE_RESP_CORRUPT";
extern const isc::log::MessageID DHCP_DDNS_REVERSE_REPLACE_BAD_DNSCLIENT_STATUS = "DHCP_DDNS_REVERSE_REPLACE_BAD_DNSCLIENT_STATUS";
extern const isc::log::MessageID DHCP_DDNS_REVERSE_REPLACE_BUILD_FAILURE = "DHCP_DDNS_REVERSE_REPLACE_BUILD_FAILURE";
extern const isc::log::MessageID DHCP_DDNS_REVERSE_REPLACE_IO_ERROR = "DHCP_DDNS_REVERSE_REPLACE_IO_ERROR";
extern const isc::log::MessageID DHCP_DDNS_REVERSE_REPLACE_REJECTED = "DHCP_DDNS_REVERSE_REPLACE_REJECTED";
extern const isc::log::MessageID DHCP_DDNS_REVERSE_REPLACE_RESP_CORRUPT = "DHCP_DDNS_REVERSE_REPLACE_RESP_CORRUPT";
extern const isc::log::MessageID DHCP_DDNS_REV_REQUEST_IGNORED = "DHCP_DDNS_REV_REQUEST_IGNORED";
extern const isc::log::MessageID DHCP_DDNS_RUN_EXIT = "DHCP_DDNS_RUN_EXIT";
extern const isc::log::MessageID DHCP_DDNS_SHUTDOWN_COMMAND = "DHCP_DDNS_SHUTDOWN_COMMAND";
extern const isc::log::MessageID DHCP_DDNS_STARTED = "DHCP_DDNS_STARTED";
extern const isc::log::MessageID DHCP_DDNS_STARTING_TRANSACTION = "DHCP_DDNS_STARTING_TRANSACTION";
extern const isc::log::MessageID DHCP_DDNS_STATE_MODEL_UNEXPECTED_ERROR = "DHCP_DDNS_STATE_MODEL_UNEXPECTED_ERROR";
extern const isc::log::MessageID DHCP_DDNS_TRANS_SEND_ERROR = "DHCP_DDNS_TRANS_SEND_ERROR";
extern const isc::log::MessageID DHCP_DDNS_UPDATE_REQUEST_SENT = "DHCP_DDNS_UPDATE_REQUEST_SENT";
extern const isc::log::MessageID DHCP_DDNS_UPDATE_RESPONSE_RECEIVED = "DHCP_DDNS_UPDATE_RESPONSE_RECEIVED";

} // namespace d2
} // namespace isc

namespace {

const char* values[] = {
    "DHCP_DDNS_ADD_FAILED", "DHCP_DDNS Request ID %1: Transaction outcome %2",
    "DHCP_DDNS_ADD_SUCCEEDED", "DHCP_DDNS Request ID %1: successfully added the DNS mapping addition for this request: %2",
    "DHCP_DDNS_ALREADY_RUNNING", "%1 already running? %2",
    "DHCP_DDNS_AT_MAX_TRANSACTIONS", "application has %1 queued requests but has reached maximum number of %2 concurrent transactions",
    "DHCP_DDNS_CLEARED_FOR_SHUTDOWN", "application has met shutdown criteria for shutdown type: %1",
    "DHCP_DDNS_COMMAND", "command directive received, command: %1 - args: %2",
    "DHCP_DDNS_CONFIGURE", "configuration %1 received: %2",
    "DHCP_DDNS_CONFIG_CHECK_FAIL", "DHCP-DDNS server configuration check failed: %1",
    "DHCP_DDNS_CONFIG_FAIL", "DHCP-DDNS server configuration failed: %1",
    "DHCP_DDNS_FAILED", "application experienced a fatal error: %1",
    "DHCP_DDNS_FORWARD_ADD_BAD_DNSCLIENT_STATUS", "DHCP_DDNS Request ID %1: received an unknown DNSClient status: %2, while adding a forward address mapping for FQDN %3 to DNS server %4",
    "DHCP_DDNS_FORWARD_ADD_BUILD_FAILURE", "DNS Request ID %1:  update message to add a forward DNS entry could not be constructed for this request: %2, reason: %3",
    "DHCP_DDNS_FORWARD_ADD_IO_ERROR", "DHCP_DDNS Request ID %1: encountered an IO error sending a forward mapping add for FQDN %2 to DNS server %3",
    "DHCP_DDNS_FORWARD_ADD_REJECTED", "DNS Request ID %1: Server, %2, rejected a DNS update request to add the address mapping for FQDN, %3, with an RCODE: %4",
    "DHCP_DDNS_FORWARD_ADD_RESP_CORRUPT", "DHCP_DDNS Request ID %1: received a corrupt response from the DNS server, %2, while adding forward address mapping for FQDN, %3",
    "DHCP_DDNS_FORWARD_REMOVE_ADDRS_BAD_DNSCLIENT_STATUS", "DHCP_DDNS Request ID %1: received an unknown DNSClient status: %2, while removing a forward address mapping for FQDN %3 to DNS server %4",
    "DHCP_DDNS_FORWARD_REMOVE_ADDRS_BUILD_FAILURE", "DNS Request ID %1: update message to remove a forward DNS Address entry could not be constructed for this request: %2, reason: %3",
    "DHCP_DDNS_FORWARD_REMOVE_ADDRS_IO_ERROR", "DHCP_DDNS Request ID %1: encountered an IO error sending a forward mapping address removal for FQDN %2 to DNS server %3",
    "DHCP_DDNS_FORWARD_REMOVE_ADDRS_REJECTED", "DNS Request ID %1: Server, %2, rejected a DNS update request to remove the forward address mapping for FQDN, %3, with an RCODE: %4",
    "DHCP_DDNS_FORWARD_REMOVE_ADDRS_RESP_CORRUPT", "DHCP_DDNS Request ID %1: received a corrupt response from the DNS server, %2, while removing forward address mapping for FQDN, %3",
    "DHCP_DDNS_FORWARD_REMOVE_RRS_BAD_DNSCLIENT_STATUS", "DHCP_DDNS Request ID %1: received an unknown DNSClient status: %2, while removing forward RRs for FQDN %3 to DNS server %4",
    "DHCP_DDNS_FORWARD_REMOVE_RRS_BUILD_FAILURE", "DNS Request ID %1: update message to remove forward DNS RR entries could not be constructed for this request: %2,  reason: %3",
    "DHCP_DDNS_FORWARD_REMOVE_RRS_IO_ERROR", "DHCP_DDNS Request ID %1: encountered an IO error sending a forward RR removal for FQDN %2 to DNS server %3",
    "DHCP_DDNS_FORWARD_REMOVE_RRS_REJECTED", "DNS Request ID %1: Server, %2, rejected a DNS update request to remove forward RR entries for FQDN, %3, with an RCODE: %4",
    "DHCP_DDNS_FORWARD_REMOVE_RRS_RESP_CORRUPT", "DHCP_DDNS Request ID %1: received a corrupt response from the DNS server, %2, while removing forward RRs for FQDN, %3",
    "DHCP_DDNS_FORWARD_REPLACE_BAD_DNSCLIENT_STATUS", "DHCP_DDNS Request ID %1: received an unknown DNSClient status: %2, while replacing forward address mapping for FQDN %3 to DNS server %4",
    "DHCP_DDNS_FORWARD_REPLACE_BUILD_FAILURE", "DNS Request ID %1: update message to replace a forward DNS entry could not be constructed from this request: %2, reason: %3",
    "DHCP_DDNS_FORWARD_REPLACE_IO_ERROR", "DHCP_DDNS Request ID %1: encountered an IO error sending a forward mapping replace for FQDN %2 to DNS server %3",
    "DHCP_DDNS_FORWARD_REPLACE_REJECTED", "DNS Request ID %1: Server, %2, rejected a DNS update request to replace the address mapping for FQDN, %3, with an RCODE: %4",
    "DHCP_DDNS_FORWARD_REPLACE_RESP_CORRUPT", "DHCP_DDNS Request ID %1: received a corrupt response from the DNS server, %2, while replacing forward address mapping for FQDN, %3",
    "DHCP_DDNS_FWD_REQUEST_IGNORED", "Request ID %1: Forward updates are disabled, the forward portion of request will be ignored: %2",
    "DHCP_DDNS_INVALID_RESPONSE", "received response to DNS Update message is malformed: %1",
    "DHCP_DDNS_NOT_ON_LOOPBACK", "the DHCP-DDNS server has been configured to listen on %1 which is not the local loopback.  This is an insecure configuration supported for testing purposes only",
    "DHCP_DDNS_NO_ELIGIBLE_JOBS", "although there are queued requests, there are pending transactions for each, Queue count: %1  Transaction count: %2",
    "DHCP_DDNS_NO_FWD_MATCH_ERROR", "Request ID %1: the configured list of forward DDNS domains does not contain a match for: %2  The request has been discarded.",
    "DHCP_DDNS_NO_MATCH", "No DNS servers match FQDN %1",
    "DHCP_DDNS_NO_REV_MATCH_ERROR", "Request ID %1: the configured list of reverse DDNS domains does not contain a match for: %2  The request has been discarded.",
    "DHCP_DDNS_PROCESS_INIT", "application init invoked",
    "DHCP_DDNS_QUEUE_MGR_QUEUE_FULL", "application request queue has reached maximum number of entries %1",
    "DHCP_DDNS_QUEUE_MGR_QUEUE_RECEIVE", "Request ID %1: received and queued a request.",
    "DHCP_DDNS_QUEUE_MGR_RECONFIGURING", "application is reconfiguring the queue manager",
    "DHCP_DDNS_QUEUE_MGR_RECOVERING", "application is attempting to recover from a queue manager IO error",
    "DHCP_DDNS_QUEUE_MGR_RECV_ERROR", "application's queue manager was notified of a request receive error by its listener.",
    "DHCP_DDNS_QUEUE_MGR_RESUME_ERROR", "application could not restart the queue manager, reason: %1",
    "DHCP_DDNS_QUEUE_MGR_RESUMING", "application is resuming listening for requests now that the request queue size has reached %1 of a maximum %2 allowed",
    "DHCP_DDNS_QUEUE_MGR_STARTED", "application's queue manager has begun listening for requests.",
    "DHCP_DDNS_QUEUE_MGR_START_ERROR", "application could not start the queue manager, reason: %1",
    "DHCP_DDNS_QUEUE_MGR_STOPPED", "application's queue manager has stopped listening for requests.",
    "DHCP_DDNS_QUEUE_MGR_STOPPING", "application is stopping the queue manager for %1",
    "DHCP_DDNS_QUEUE_MGR_STOP_ERROR", "application encountered an error stopping the queue manager: %1",
    "DHCP_DDNS_QUEUE_MGR_UNEXPECTED_HANDLER_ERROR", "application's queue manager request receive handler experienced an unexpected exception %1:",
    "DHCP_DDNS_QUEUE_MGR_UNEXPECTED_STOP", "application's queue manager receive was",
    "DHCP_DDNS_REMOVE_FAILED", "DHCP_DDNS Request ID %1: Transaction outcome: %2",
    "DHCP_DDNS_REMOVE_SUCCEEDED", "DHCP_DDNS Request ID %1: successfully removed the DNS mapping addition for this request: %2",
    "DHCP_DDNS_REQUEST_DROPPED", "Request ID %1: Request contains no enabled update requests and will be dropped: %2",
    "DHCP_DDNS_REVERSE_REMOVE_BAD_DNSCLIENT_STATUS", "DHCP_DDNS Request ID %1: received an unknown DNSClient status: %2, while removing reverse address mapping for FQDN %3 to DNS server %4",
    "DHCP_DDNS_REVERSE_REMOVE_BUILD_FAILURE", "DNS Request ID %1: update message to remove a reverse DNS entry could not be constructed from this request: %2,  reason: %3",
    "DHCP_DDNS_REVERSE_REMOVE_IO_ERROR", "DHCP_DDNS Request ID %1: encountered an IO error sending a reverse mapping remove for FQDN %2 to DNS server %3",
    "DHCP_DDNS_REVERSE_REMOVE_REJECTED", "DNS Request ID %1: Server, %2, rejected a DNS update request to remove the reverse mapping for FQDN, %3, with an RCODE: %4",
    "DHCP_DDNS_REVERSE_REMOVE_RESP_CORRUPT", "DHCP_DDNS Request ID %1: received a corrupt response from the DNS server, %2, while removing reverse address mapping for FQDN, %3",
    "DHCP_DDNS_REVERSE_REPLACE_BAD_DNSCLIENT_STATUS", "DHCP_DDNS Request ID %1: received an unknown DNSClient status: %2, while replacing reverse address mapping for FQDN %3 to DNS server %4",
    "DHCP_DDNS_REVERSE_REPLACE_BUILD_FAILURE", "DNS Request ID %1: update message to replace a reverse DNS entry could not be constructed from this request: %2, reason: %3",
    "DHCP_DDNS_REVERSE_REPLACE_IO_ERROR", "DHCP_DDNS Request ID %1: encountered an IO error sending a reverse mapping replacement for FQDN %2 to DNS server %3",
    "DHCP_DDNS_REVERSE_REPLACE_REJECTED", "DNS Request ID %1: Server, %2, rejected a DNS update request to replace the reverse mapping for FQDN, %3, with an RCODE: %4",
    "DHCP_DDNS_REVERSE_REPLACE_RESP_CORRUPT", "DHCP_DDNS Request ID %1: received a corrupt response from the DNS server, %2, while replacing reverse address mapping for FQDN, %3",
    "DHCP_DDNS_REV_REQUEST_IGNORED", "Request ID %1: Reverse updates are disabled, the reverse portion of request will be ignored: %2",
    "DHCP_DDNS_RUN_EXIT", "application is exiting the event loop",
    "DHCP_DDNS_SHUTDOWN_COMMAND", "application received shutdown command with args: %1",
    "DHCP_DDNS_STARTED", "Kea DHCP-DDNS server version %1 started",
    "DHCP_DDNS_STARTING_TRANSACTION", "Request ID %1:",
    "DHCP_DDNS_STATE_MODEL_UNEXPECTED_ERROR", "Request ID %1: application encountered an unexpected error while carrying out a NameChangeRequest: %2",
    "DHCP_DDNS_TRANS_SEND_ERROR", "Request ID %1: application encountered an unexpected error while attempting to send a DNS update: %2",
    "DHCP_DDNS_UPDATE_REQUEST_SENT", "Request ID %1: %2 to server: %3",
    "DHCP_DDNS_UPDATE_RESPONSE_RECEIVED", "Request ID %1: to server: %2 status: %3",
    NULL
};

const isc::log::MessageInitializer initializer(values);

} // Anonymous namespace

