// File created from ../../../src/bin/lfc/lfc_messages.mes on Fri Feb 08 2019 20:33

#ifndef LFC_MESSAGES_H
#define LFC_MESSAGES_H

#include <log/message_types.h>

namespace isc {
namespace lfc {

extern const isc::log::MessageID LFC_FAIL_PID_CREATE;
extern const isc::log::MessageID LFC_FAIL_PID_DEL;
extern const isc::log::MessageID LFC_FAIL_PROCESS;
extern const isc::log::MessageID LFC_FAIL_ROTATE;
extern const isc::log::MessageID LFC_PROCESSING;
extern const isc::log::MessageID LFC_READ_STATS;
extern const isc::log::MessageID LFC_ROTATING;
extern const isc::log::MessageID LFC_RUNNING;
extern const isc::log::MessageID LFC_START;
extern const isc::log::MessageID LFC_TERMINATE;
extern const isc::log::MessageID LFC_WRITE_STATS;

} // namespace lfc
} // namespace isc

#endif // LFC_MESSAGES_H
