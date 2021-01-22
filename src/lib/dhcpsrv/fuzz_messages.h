// File created from ../../../src/lib/dhcpsrv/fuzz_messages.mes

#ifndef FUZZ_MESSAGES_H
#define FUZZ_MESSAGES_H

#include <log/message_types.h>

namespace isc {
namespace dhcp {

extern const isc::log::MessageID FUZZ_DATA_READ;
extern const isc::log::MessageID FUZZ_INIT_COMPLETE;
extern const isc::log::MessageID FUZZ_INIT_FAIL;
extern const isc::log::MessageID FUZZ_READ_FAIL;
extern const isc::log::MessageID FUZZ_SEND;
extern const isc::log::MessageID FUZZ_SEND_ERROR;
extern const isc::log::MessageID FUZZ_SHORT_SEND;
extern const isc::log::MessageID FUZZ_SOCKET_CREATE_FAIL;

} // namespace dhcp
} // namespace isc

#endif // FUZZ_MESSAGES_H
