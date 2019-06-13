// File created from ../../../src/lib/dhcpsrv/fuzz_messages.mes on Thu Jun 13 2019 12:34

#ifndef FUZZ_MESSAGES_H
#define FUZZ_MESSAGES_H

#include <log/message_types.h>

namespace isc {
namespace dhcp {

extern const isc::log::MessageID FUZZ_DATA_READ;
extern const isc::log::MessageID FUZZ_INIT_COMPLETE;
extern const isc::log::MessageID FUZZ_INIT_FAIL;
extern const isc::log::MessageID FUZZ_INTERFACE;
extern const isc::log::MessageID FUZZ_LOOP_EXIT;
extern const isc::log::MessageID FUZZ_LOOP_MAX;
extern const isc::log::MessageID FUZZ_PACKET_PROCESSED_CALLED;
extern const isc::log::MessageID FUZZ_READ_FAIL;
extern const isc::log::MessageID FUZZ_SEND;
extern const isc::log::MessageID FUZZ_SEND_ERROR;
extern const isc::log::MessageID FUZZ_SET;
extern const isc::log::MessageID FUZZ_SETTING;
extern const isc::log::MessageID FUZZ_SHORT_SEND;
extern const isc::log::MessageID FUZZ_SHUTDOWN_INITIATED;
extern const isc::log::MessageID FUZZ_SOCKET_CREATE_FAIL;
extern const isc::log::MessageID FUZZ_THREAD_NOT_TERMINATED;
extern const isc::log::MessageID FUZZ_THREAD_TERMINATED;
extern const isc::log::MessageID FUZZ_THREAD_WAIT;
extern const isc::log::MessageID FUZZ_WAITED;
extern const isc::log::MessageID FUZZ_WAITING;

} // namespace dhcp
} // namespace isc

#endif // FUZZ_MESSAGES_H
