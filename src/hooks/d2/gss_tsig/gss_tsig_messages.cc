// File created from src/hooks/d2/gss_tsig/gss_tsig_messages.mes

#include <cstddef>
#include <log/message_types.h>
#include <log/message_initializer.h>

namespace isc {
namespace gss_tsig {

extern const isc::log::MessageID BAD_CLIENT_CREDENTIALS = "BAD_CLIENT_CREDENTIALS";
extern const isc::log::MessageID GSS_TSIG_COMMAND_PROCESSED_FAILED = "GSS_TSIG_COMMAND_PROCESSED_FAILED";
extern const isc::log::MessageID GSS_TSIG_LOAD_FAILED = "GSS_TSIG_LOAD_FAILED";
extern const isc::log::MessageID GSS_TSIG_LOAD_OK = "GSS_TSIG_LOAD_OK";
extern const isc::log::MessageID GSS_TSIG_MANAGER_STARTED = "GSS_TSIG_MANAGER_STARTED";
extern const isc::log::MessageID GSS_TSIG_MANAGER_STOPPED = "GSS_TSIG_MANAGER_STOPPED";
extern const isc::log::MessageID GSS_TSIG_MANAGER_STOP_ERROR = "GSS_TSIG_MANAGER_STOP_ERROR";
extern const isc::log::MessageID GSS_TSIG_MANAGER_STOP_GENERAL_ERROR = "GSS_TSIG_MANAGER_STOP_GENERAL_ERROR";
extern const isc::log::MessageID GSS_TSIG_NEW_KEY = "GSS_TSIG_NEW_KEY";
extern const isc::log::MessageID GSS_TSIG_NEW_KEY_SETUP_FAILED = "GSS_TSIG_NEW_KEY_SETUP_FAILED";
extern const isc::log::MessageID GSS_TSIG_NEW_KEY_SETUP_SUCCEED = "GSS_TSIG_NEW_KEY_SETUP_SUCCEED";
extern const isc::log::MessageID GSS_TSIG_OLD_KEY_REMOVED = "GSS_TSIG_OLD_KEY_REMOVED";
extern const isc::log::MessageID GSS_TSIG_UNLOAD_OK = "GSS_TSIG_UNLOAD_OK";
extern const isc::log::MessageID GSS_TSIG_VERIFIED = "GSS_TSIG_VERIFIED";
extern const isc::log::MessageID GSS_TSIG_VERIFY_FAILED = "GSS_TSIG_VERIFY_FAILED";
extern const isc::log::MessageID KEY_LOOKUP_DISABLED = "KEY_LOOKUP_DISABLED";
extern const isc::log::MessageID KEY_LOOKUP_FOUND = "KEY_LOOKUP_FOUND";
extern const isc::log::MessageID KEY_LOOKUP_NONE = "KEY_LOOKUP_NONE";
extern const isc::log::MessageID KEY_PROCESSING_FAILED = "KEY_PROCESSING_FAILED";
extern const isc::log::MessageID KEY_PROCESSING_FAILED_UNSPECIFIED_ERROR = "KEY_PROCESSING_FAILED_UNSPECIFIED_ERROR";
extern const isc::log::MessageID START_REKEY_TIMER = "START_REKEY_TIMER";
extern const isc::log::MessageID START_RETRY_TIMER = "START_RETRY_TIMER";
extern const isc::log::MessageID TKEY_EXCHANGE_ANSWER_CLASS = "TKEY_EXCHANGE_ANSWER_CLASS";
extern const isc::log::MessageID TKEY_EXCHANGE_FAILED_TO_VERIFY = "TKEY_EXCHANGE_FAILED_TO_VERIFY";
extern const isc::log::MessageID TKEY_EXCHANGE_FAIL_EMPTY_IN_TOKEN = "TKEY_EXCHANGE_FAIL_EMPTY_IN_TOKEN";
extern const isc::log::MessageID TKEY_EXCHANGE_FAIL_EMPTY_OUT_TOKEN = "TKEY_EXCHANGE_FAIL_EMPTY_OUT_TOKEN";
extern const isc::log::MessageID TKEY_EXCHANGE_FAIL_EMPTY_RESPONSE = "TKEY_EXCHANGE_FAIL_EMPTY_RESPONSE";
extern const isc::log::MessageID TKEY_EXCHANGE_FAIL_IO_ERROR = "TKEY_EXCHANGE_FAIL_IO_ERROR";
extern const isc::log::MessageID TKEY_EXCHANGE_FAIL_IO_STOPPED = "TKEY_EXCHANGE_FAIL_IO_STOPPED";
extern const isc::log::MessageID TKEY_EXCHANGE_FAIL_IO_TIMEOUT = "TKEY_EXCHANGE_FAIL_IO_TIMEOUT";
extern const isc::log::MessageID TKEY_EXCHANGE_FAIL_NOT_SIGNED = "TKEY_EXCHANGE_FAIL_NOT_SIGNED";
extern const isc::log::MessageID TKEY_EXCHANGE_FAIL_NO_RDATA = "TKEY_EXCHANGE_FAIL_NO_RDATA";
extern const isc::log::MessageID TKEY_EXCHANGE_FAIL_NO_RESPONSE_ANSWER = "TKEY_EXCHANGE_FAIL_NO_RESPONSE_ANSWER";
extern const isc::log::MessageID TKEY_EXCHANGE_FAIL_NULL_RESPONSE = "TKEY_EXCHANGE_FAIL_NULL_RESPONSE";
extern const isc::log::MessageID TKEY_EXCHANGE_FAIL_RESPONSE_ERROR = "TKEY_EXCHANGE_FAIL_RESPONSE_ERROR";
extern const isc::log::MessageID TKEY_EXCHANGE_FAIL_TKEY_ERROR = "TKEY_EXCHANGE_FAIL_TKEY_ERROR";
extern const isc::log::MessageID TKEY_EXCHANGE_FAIL_TO_INIT = "TKEY_EXCHANGE_FAIL_TO_INIT";
extern const isc::log::MessageID TKEY_EXCHANGE_FAIL_WRONG_RESPONSE_ANSWER_COUNT = "TKEY_EXCHANGE_FAIL_WRONG_RESPONSE_ANSWER_COUNT";
extern const isc::log::MessageID TKEY_EXCHANGE_FAIL_WRONG_RESPONSE_ANSWER_TYPE = "TKEY_EXCHANGE_FAIL_WRONG_RESPONSE_ANSWER_TYPE";
extern const isc::log::MessageID TKEY_EXCHANGE_FAIL_WRONG_RESPONSE_OPCODE = "TKEY_EXCHANGE_FAIL_WRONG_RESPONSE_OPCODE";
extern const isc::log::MessageID TKEY_EXCHANGE_NOT_A_RESPONSE = "TKEY_EXCHANGE_NOT_A_RESPONSE";
extern const isc::log::MessageID TKEY_EXCHANGE_OUT_TOKEN_NOT_EMPTY = "TKEY_EXCHANGE_OUT_TOKEN_NOT_EMPTY";
extern const isc::log::MessageID TKEY_EXCHANGE_RDATA_COUNT = "TKEY_EXCHANGE_RDATA_COUNT";
extern const isc::log::MessageID TKEY_EXCHANGE_RECEIVE_MESSAGE = "TKEY_EXCHANGE_RECEIVE_MESSAGE";
extern const isc::log::MessageID TKEY_EXCHANGE_RESPONSE_TTL = "TKEY_EXCHANGE_RESPONSE_TTL";
extern const isc::log::MessageID TKEY_EXCHANGE_SEND_MESSAGE = "TKEY_EXCHANGE_SEND_MESSAGE";
extern const isc::log::MessageID TKEY_EXCHANGE_VALID = "TKEY_EXCHANGE_VALID";
extern const isc::log::MessageID TKEY_EXCHANGE_VERIFIED = "TKEY_EXCHANGE_VERIFIED";

} // namespace gss_tsig
} // namespace isc

namespace {

const char* values[] = {
    "BAD_CLIENT_CREDENTIALS", "bad client credentials: %1",
    "GSS_TSIG_COMMAND_PROCESSED_FAILED", "command_processed callout failed: %1.",
    "GSS_TSIG_LOAD_FAILED", "GSS-TSIG hooks library failed to load: %1.",
    "GSS_TSIG_LOAD_OK", "GSS-TSIG hooks library loaded successfully.",
    "GSS_TSIG_MANAGER_STARTED", "hooks library GSS-TSIG key periodic manager started.",
    "GSS_TSIG_MANAGER_STOPPED", "hooks library GSS-TSIG key periodic manager stopped.",
    "GSS_TSIG_MANAGER_STOP_ERROR", "manager stop error: %1",
    "GSS_TSIG_MANAGER_STOP_GENERAL_ERROR", "manager stop general error",
    "GSS_TSIG_NEW_KEY", "new GSS-TSIG key '%1' was created.",
    "GSS_TSIG_NEW_KEY_SETUP_FAILED", "new GSS-TSIG key '%1' setup failed: %2.",
    "GSS_TSIG_NEW_KEY_SETUP_SUCCEED", "new GSS-TSIG key '%1' setup succeed.",
    "GSS_TSIG_OLD_KEY_REMOVED", "%1 old GSS-TSIG keys were removed",
    "GSS_TSIG_UNLOAD_OK", "GSS-TSIG hooks library unloaded successfully.",
    "GSS_TSIG_VERIFIED", "GSS-TSIG verify successed.",
    "GSS_TSIG_VERIFY_FAILED", "GSS-TSIG verify failed: %1.",
    "KEY_LOOKUP_DISABLED", "hooks library lookup for a key: GSS-TSIG is not enabled for the current DNS server.",
    "KEY_LOOKUP_FOUND", "hooks library lookup for a key: return GSS-TSIG key '%1'.",
    "KEY_LOOKUP_NONE", "hooks library lookup for a key: found no usable key.",
    "KEY_PROCESSING_FAILED", "The GSS-TKEY processing for server %1 failed because of an error: %2",
    "KEY_PROCESSING_FAILED_UNSPECIFIED_ERROR", "The GSS-TKEY processing for server %1 failed because of an unspecified error",
    "START_REKEY_TIMER", "started timer handling rekey for server %1 in %2 seconds.",
    "START_RETRY_TIMER", "started timer handling retry for server %1 in %2 seconds.",
    "TKEY_EXCHANGE_ANSWER_CLASS", "GSS-TKEY exchange received a response with answer class: %1.",
    "TKEY_EXCHANGE_FAILED_TO_VERIFY", "GSS-TKEY exchange failed because the response failed to verify.",
    "TKEY_EXCHANGE_FAIL_EMPTY_IN_TOKEN", "GSS-TKEY exchange failed because input token is empty.",
    "TKEY_EXCHANGE_FAIL_EMPTY_OUT_TOKEN", "GSS-TKEY exchange failed because output token is empty.",
    "TKEY_EXCHANGE_FAIL_EMPTY_RESPONSE", "GSS-TKEY exchange failed because the response is empty.",
    "TKEY_EXCHANGE_FAIL_IO_ERROR", "GSS-TKEY exchange failed because of the IO error: %1.",
    "TKEY_EXCHANGE_FAIL_IO_STOPPED", "GSS-TKEY exchange failed because the IO service was stopped.",
    "TKEY_EXCHANGE_FAIL_IO_TIMEOUT", "GSS-TKEY exchange failed because of IO timeout.",
    "TKEY_EXCHANGE_FAIL_NOT_SIGNED", "GSS-TKEY exchange failed because the response is not signed.",
    "TKEY_EXCHANGE_FAIL_NO_RDATA", "GSS-TKEY exchange failed because the response contains no rdata.",
    "TKEY_EXCHANGE_FAIL_NO_RESPONSE_ANSWER", "GSS-TKEY exchange failed because the response contains no answer.",
    "TKEY_EXCHANGE_FAIL_NULL_RESPONSE", "GSS-TKEY exchange failed because the response is null.",
    "TKEY_EXCHANGE_FAIL_RESPONSE_ERROR", "GSS-TKEY exchange failed because the response contains an error: %1.",
    "TKEY_EXCHANGE_FAIL_TKEY_ERROR", "GSS-TKEY exchange failed because the response contains TKEY error: %1.",
    "TKEY_EXCHANGE_FAIL_TO_INIT", "GSS-TKEY exchange failed to initialize because of the error: %1.",
    "TKEY_EXCHANGE_FAIL_WRONG_RESPONSE_ANSWER_COUNT", "GSS-TKEY exchange failed because the response contains invalid number of RRs: %1.",
    "TKEY_EXCHANGE_FAIL_WRONG_RESPONSE_ANSWER_TYPE", "GSS-TKEY exchange failed because the response contains wrong answer type: %1.",
    "TKEY_EXCHANGE_FAIL_WRONG_RESPONSE_OPCODE", "GSS-TKEY exchange failed because the response contains invalid opcode: %1.",
    "TKEY_EXCHANGE_NOT_A_RESPONSE", "GSS-TKEY exchange received a non response type.",
    "TKEY_EXCHANGE_OUT_TOKEN_NOT_EMPTY", "GSS-TKEY exchange output token is not empty.",
    "TKEY_EXCHANGE_RDATA_COUNT", "GSS-TKEY exchange received a response with rdata count: %1.",
    "TKEY_EXCHANGE_RECEIVE_MESSAGE", "GSS-TKEY exchange receives a message of size: %1.",
    "TKEY_EXCHANGE_RESPONSE_TTL", "GSS-TKEY exchange received a response with TTL of: %1 seconds.",
    "TKEY_EXCHANGE_SEND_MESSAGE", "GSS-TKEY exchange sends a message of size: %1.",
    "TKEY_EXCHANGE_VALID", "GSS-TKEY exchange retrieved a TKEY valid for: %1 seconds.",
    "TKEY_EXCHANGE_VERIFIED", "GSS-TKEY exchange verified.",
    NULL
};

const isc::log::MessageInitializer initializer(values);

} // Anonymous namespace

