// File created from log_messages.mes on Thu Jul  7 15:32:06 2011

#include <cstddef>
#include <log/message_types.h>
#include <log/message_initializer.h>

namespace isc {
namespace log {

extern const isc::log::MessageID LOG_BAD_DESTINATION = "LOG_BAD_DESTINATION";
extern const isc::log::MessageID LOG_BAD_SEVERITY = "LOG_BAD_SEVERITY";
extern const isc::log::MessageID LOG_BAD_STREAM = "LOG_BAD_STREAM";
extern const isc::log::MessageID LOG_DUPLICATE_MESSAGE_ID = "LOG_DUPLICATE_MESSAGE_ID";
extern const isc::log::MessageID LOG_DUPLICATE_NAMESPACE = "LOG_DUPLICATE_NAMESPACE";
extern const isc::log::MessageID LOG_INPUT_OPEN_FAIL = "LOG_INPUT_OPEN_FAIL";
extern const isc::log::MessageID LOG_INVALID_MESSAGE_ID = "LOG_INVALID_MESSAGE_ID";
extern const isc::log::MessageID LOG_NAMESPACE_EXTRA_ARGS = "LOG_NAMESPACE_EXTRA_ARGS";
extern const isc::log::MessageID LOG_NAMESPACE_INVALID_ARG = "LOG_NAMESPACE_INVALID_ARG";
extern const isc::log::MessageID LOG_NAMESPACE_NO_ARGS = "LOG_NAMESPACE_NO_ARGS";
extern const isc::log::MessageID LOG_NO_MESSAGE_ID = "LOG_NO_MESSAGE_ID";
extern const isc::log::MessageID LOG_NO_MESSAGE_TEXT = "LOG_NO_MESSAGE_TEXT";
extern const isc::log::MessageID LOG_NO_SUCH_MESSAGE = "LOG_NO_SUCH_MESSAGE";
extern const isc::log::MessageID LOG_OPEN_OUTPUT_FAIL = "LOG_OPEN_OUTPUT_FAIL";
extern const isc::log::MessageID LOG_PREFIX_EXTRA_ARGS = "LOG_PREFIX_EXTRA_ARGS";
extern const isc::log::MessageID LOG_PREFIX_INVALID_ARG = "LOG_PREFIX_INVALID_ARG";
extern const isc::log::MessageID LOG_READING_LOCAL_FILE = "LOG_READING_LOCAL_FILE";
extern const isc::log::MessageID LOG_READ_ERROR = "LOG_READ_ERROR";
extern const isc::log::MessageID LOG_UNRECOGNIZED_DIRECTIVE = "LOG_UNRECOGNIZED_DIRECTIVE";
extern const isc::log::MessageID LOG_WRITE_ERROR = "LOG_WRITE_ERROR";

} // namespace log
} // namespace isc

namespace {

const char* values[] = {
    "LOG_BAD_DESTINATION", "unrecognized log destination: %1",
    "LOG_BAD_SEVERITY", "unrecognized log severity: %1",
    "LOG_BAD_STREAM", "bad log console output stream: %1",
    "LOG_DUPLICATE_MESSAGE_ID", "duplicate message ID (%1) in compiled code",
    "LOG_DUPLICATE_NAMESPACE", "line %1: duplicate $NAMESPACE directive found",
    "LOG_INPUT_OPEN_FAIL", "unable to open message file %1 for input: %2",
    "LOG_INVALID_MESSAGE_ID", "line %1: invalid message identification '%2'",
    "LOG_NAMESPACE_EXTRA_ARGS", "line %1: $NAMESPACE directive has too many arguments",
    "LOG_NAMESPACE_INVALID_ARG", "line %1: $NAMESPACE directive has an invalid argument ('%2')",
    "LOG_NAMESPACE_NO_ARGS", "line %1: no arguments were given to the $NAMESPACE directive",
    "LOG_NO_MESSAGE_ID", "line %1: message definition line found without a message ID",
    "LOG_NO_MESSAGE_TEXT", "line %1: line found containing a message ID ('%2') and no text",
    "LOG_NO_SUCH_MESSAGE", "could not replace message text for '%1': no such message",
    "LOG_OPEN_OUTPUT_FAIL", "unable to open %1 for output: %2",
    "LOG_PREFIX_EXTRA_ARGS", "line %1: $PREFIX directive has too many arguments",
    "LOG_PREFIX_INVALID_ARG", "line %1: $PREFIX directive has an invalid argument ('%2')",
    "LOG_READING_LOCAL_FILE", "reading local message file %1",
    "LOG_READ_ERROR", "error reading from message file %1: %2",
    "LOG_UNRECOGNIZED_DIRECTIVE", "line %1: unrecogniszd directive '%2'",
    "LOG_WRITE_ERROR", "error writing to %1: %2",
    NULL
};

const isc::log::MessageInitializer initializer(values);

} // Anonymous namespace

