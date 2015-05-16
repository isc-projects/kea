// File created from log_messages.mes on Thu Jul  7 15:32:06 2011

#ifndef LOG_MESSAGES_H
#define LOG_MESSAGES_H

#include <log/message_types.h>

namespace isc {
namespace log {

extern const isc::log::MessageID LOG_BAD_DESTINATION;
extern const isc::log::MessageID LOG_BAD_SEVERITY;
extern const isc::log::MessageID LOG_BAD_STREAM;
extern const isc::log::MessageID LOG_DUPLICATE_MESSAGE_ID;
extern const isc::log::MessageID LOG_DUPLICATE_NAMESPACE;
extern const isc::log::MessageID LOG_INPUT_OPEN_FAIL;
extern const isc::log::MessageID LOG_INVALID_MESSAGE_ID;
extern const isc::log::MessageID LOG_NAMESPACE_EXTRA_ARGS;
extern const isc::log::MessageID LOG_NAMESPACE_INVALID_ARG;
extern const isc::log::MessageID LOG_NAMESPACE_NO_ARGS;
extern const isc::log::MessageID LOG_NO_MESSAGE_ID;
extern const isc::log::MessageID LOG_NO_MESSAGE_TEXT;
extern const isc::log::MessageID LOG_NO_SUCH_MESSAGE;
extern const isc::log::MessageID LOG_OPEN_OUTPUT_FAIL;
extern const isc::log::MessageID LOG_PREFIX_EXTRA_ARGS;
extern const isc::log::MessageID LOG_PREFIX_INVALID_ARG;
extern const isc::log::MessageID LOG_READING_LOCAL_FILE;
extern const isc::log::MessageID LOG_READ_ERROR;
extern const isc::log::MessageID LOG_UNRECOGNIZED_DIRECTIVE;
extern const isc::log::MessageID LOG_WRITE_ERROR;

} // namespace log
} // namespace isc

#endif // LOG_MESSAGES_H
