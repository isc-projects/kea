// File created from src/hooks/d2/gss_tsig/gss_tsig_messages.mes

#ifndef GSS_TSIG_MESSAGES_H
#define GSS_TSIG_MESSAGES_H

#include <log/message_types.h>

namespace isc {
namespace gss_tsig {

extern const isc::log::MessageID BAD_CLIENT_CREDENTIALS;
extern const isc::log::MessageID GSS_TSIG_COMMAND_PROCESSED_FAILED;
extern const isc::log::MessageID GSS_TSIG_LOAD_FAILED;
extern const isc::log::MessageID GSS_TSIG_LOAD_OK;
extern const isc::log::MessageID GSS_TSIG_MANAGER_STARTED;
extern const isc::log::MessageID GSS_TSIG_MANAGER_STOPPED;
extern const isc::log::MessageID GSS_TSIG_MANAGER_STOP_ERROR;
extern const isc::log::MessageID GSS_TSIG_MANAGER_STOP_GENERAL_ERROR;
extern const isc::log::MessageID GSS_TSIG_NEW_KEY;
extern const isc::log::MessageID GSS_TSIG_NEW_KEY_SETUP_FAILED;
extern const isc::log::MessageID GSS_TSIG_NEW_KEY_SETUP_SUCCEED;
extern const isc::log::MessageID GSS_TSIG_OLD_KEY_REMOVED;
extern const isc::log::MessageID GSS_TSIG_UNLOAD_OK;
extern const isc::log::MessageID GSS_TSIG_VERIFIED;
extern const isc::log::MessageID GSS_TSIG_VERIFY_FAILED;
extern const isc::log::MessageID KEY_LOOKUP_DISABLED;
extern const isc::log::MessageID KEY_LOOKUP_FOUND;
extern const isc::log::MessageID KEY_LOOKUP_NONE;
extern const isc::log::MessageID KEY_PROCESSING_FAILED;
extern const isc::log::MessageID KEY_PROCESSING_FAILED_UNSPECIFIED_ERROR;
extern const isc::log::MessageID START_REKEY_TIMER;
extern const isc::log::MessageID START_RETRY_TIMER;
extern const isc::log::MessageID TKEY_EXCHANGE_ANSWER_CLASS;
extern const isc::log::MessageID TKEY_EXCHANGE_FAILED_TO_VERIFY;
extern const isc::log::MessageID TKEY_EXCHANGE_FAIL_EMPTY_IN_TOKEN;
extern const isc::log::MessageID TKEY_EXCHANGE_FAIL_EMPTY_OUT_TOKEN;
extern const isc::log::MessageID TKEY_EXCHANGE_FAIL_EMPTY_RESPONSE;
extern const isc::log::MessageID TKEY_EXCHANGE_FAIL_IO_ERROR;
extern const isc::log::MessageID TKEY_EXCHANGE_FAIL_IO_STOPPED;
extern const isc::log::MessageID TKEY_EXCHANGE_FAIL_IO_TIMEOUT;
extern const isc::log::MessageID TKEY_EXCHANGE_FAIL_NOT_SIGNED;
extern const isc::log::MessageID TKEY_EXCHANGE_FAIL_NO_RDATA;
extern const isc::log::MessageID TKEY_EXCHANGE_FAIL_NO_RESPONSE_ANSWER;
extern const isc::log::MessageID TKEY_EXCHANGE_FAIL_NULL_RESPONSE;
extern const isc::log::MessageID TKEY_EXCHANGE_FAIL_RESPONSE_ERROR;
extern const isc::log::MessageID TKEY_EXCHANGE_FAIL_TKEY_ERROR;
extern const isc::log::MessageID TKEY_EXCHANGE_FAIL_TO_INIT;
extern const isc::log::MessageID TKEY_EXCHANGE_FAIL_WRONG_RESPONSE_ANSWER_COUNT;
extern const isc::log::MessageID TKEY_EXCHANGE_FAIL_WRONG_RESPONSE_ANSWER_TYPE;
extern const isc::log::MessageID TKEY_EXCHANGE_FAIL_WRONG_RESPONSE_OPCODE;
extern const isc::log::MessageID TKEY_EXCHANGE_NOT_A_RESPONSE;
extern const isc::log::MessageID TKEY_EXCHANGE_OUT_TOKEN_NOT_EMPTY;
extern const isc::log::MessageID TKEY_EXCHANGE_RDATA_COUNT;
extern const isc::log::MessageID TKEY_EXCHANGE_RECEIVE_MESSAGE;
extern const isc::log::MessageID TKEY_EXCHANGE_RESPONSE_TTL;
extern const isc::log::MessageID TKEY_EXCHANGE_SEND_MESSAGE;
extern const isc::log::MessageID TKEY_EXCHANGE_VALID;
extern const isc::log::MessageID TKEY_EXCHANGE_VERIFIED;

} // namespace gss_tsig
} // namespace isc

#endif // GSS_TSIG_MESSAGES_H
