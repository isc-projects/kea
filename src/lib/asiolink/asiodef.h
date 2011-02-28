// File created from asiodef.msg on Mon Feb 28 17:15:30 2011

#ifndef __ASIODEF_H
#define __ASIODEF_H

#include <log/message_types.h>

namespace asiolink {

extern const isc::log::MessageID ASIO_FETCHCOMP;
extern const isc::log::MessageID ASIO_FETCHSTOP;
extern const isc::log::MessageID ASIO_OPENSOCK;
extern const isc::log::MessageID ASIO_RECVSOCK;
extern const isc::log::MessageID ASIO_RECVTMO;
extern const isc::log::MessageID ASIO_SENDSOCK;
extern const isc::log::MessageID ASIO_UNKORIGIN;
extern const isc::log::MessageID ASIO_UNKRESULT;

} // namespace asiolink

#endif // __ASIODEF_H
