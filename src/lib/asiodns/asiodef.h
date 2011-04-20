// File created from asiodef.msg on Mon Feb 28 17:15:30 2011

#ifndef __ASIODEF_H
#define __ASIODEF_H

#include <log/message_types.h>

namespace isc {
namespace asiodns {

extern const isc::log::MessageID ASIODNS_FETCHCOMP;
extern const isc::log::MessageID ASIODNS_FETCHSTOP;
extern const isc::log::MessageID ASIODNS_OPENSOCK;
extern const isc::log::MessageID ASIODNS_RECVSOCK;
extern const isc::log::MessageID ASIODNS_RECVTMO;
extern const isc::log::MessageID ASIODNS_SENDSOCK;
extern const isc::log::MessageID ASIODNS_UNKORIGIN;
extern const isc::log::MessageID ASIODNS_UNKRESULT;

} // namespace asiodns
} // namespace isc

#endif // __ASIODEF_H
