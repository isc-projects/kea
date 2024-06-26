// File created from ../../../src/lib/asiodns/asiodns_messages.mes

#ifndef ASIODNS_MESSAGES_H
#define ASIODNS_MESSAGES_H

#include <log/message_types.h>

namespace isc {
namespace asiodns {

extern const isc::log::MessageID ASIODNS_FETCH_COMPLETED;
extern const isc::log::MessageID ASIODNS_FETCH_STOPPED;
extern const isc::log::MessageID ASIODNS_OPEN_SOCKET;
extern const isc::log::MessageID ASIODNS_READ_DATA;
extern const isc::log::MessageID ASIODNS_READ_TIMEOUT;
extern const isc::log::MessageID ASIODNS_SEND_DATA;
extern const isc::log::MessageID ASIODNS_UNKNOWN_ORIGIN;
extern const isc::log::MessageID ASIODNS_UNKNOWN_RESULT;

} // namespace asiodns
} // namespace isc

#endif // ASIODNS_MESSAGES_H
