// File created from ../../../src/lib/asiodns/asiodns_messages.mes

#ifndef ASIODNS_MESSAGES_H
#define ASIODNS_MESSAGES_H

#include <log/message_types.h>

namespace isc {
namespace asiodns {

extern const isc::log::MessageID ASIODNS_FD_ADD_TCP;
extern const isc::log::MessageID ASIODNS_FD_ADD_UDP;
extern const isc::log::MessageID ASIODNS_FETCH_COMPLETED;
extern const isc::log::MessageID ASIODNS_FETCH_STOPPED;
extern const isc::log::MessageID ASIODNS_OPEN_SOCKET;
extern const isc::log::MessageID ASIODNS_READ_DATA;
extern const isc::log::MessageID ASIODNS_READ_TIMEOUT;
extern const isc::log::MessageID ASIODNS_SEND_DATA;
extern const isc::log::MessageID ASIODNS_SYNC_UDP_CLOSE_FAIL;
extern const isc::log::MessageID ASIODNS_TCP_ACCEPT_FAIL;
extern const isc::log::MessageID ASIODNS_TCP_CLEANUP_CLOSE_FAIL;
extern const isc::log::MessageID ASIODNS_TCP_CLOSE_ACCEPTOR_FAIL;
extern const isc::log::MessageID ASIODNS_TCP_CLOSE_FAIL;
extern const isc::log::MessageID ASIODNS_TCP_CLOSE_NORESP_FAIL;
extern const isc::log::MessageID ASIODNS_TCP_GETREMOTE_FAIL;
extern const isc::log::MessageID ASIODNS_TCP_READDATA_FAIL;
extern const isc::log::MessageID ASIODNS_TCP_READLEN_FAIL;
extern const isc::log::MessageID ASIODNS_TCP_WRITE_FAIL;
extern const isc::log::MessageID ASIODNS_UDP_ASYNC_SEND_FAIL;
extern const isc::log::MessageID ASIODNS_UDP_CLOSE_FAIL;
extern const isc::log::MessageID ASIODNS_UDP_RECEIVE_FAIL;
extern const isc::log::MessageID ASIODNS_UDP_SYNC_RECEIVE_FAIL;
extern const isc::log::MessageID ASIODNS_UDP_SYNC_SEND_FAIL;
extern const isc::log::MessageID ASIODNS_UNKNOWN_ORIGIN;
extern const isc::log::MessageID ASIODNS_UNKNOWN_RESULT;

} // namespace asiodns
} // namespace isc

#endif // ASIODNS_MESSAGES_H
