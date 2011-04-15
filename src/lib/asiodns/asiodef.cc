// File created from asiodef.msg on Mon Feb 28 17:15:30 2011

#include <cstddef>
#include <log/message_types.h>
#include <log/message_initializer.h>

namespace isc {
namespace asiodns {

extern const isc::log::MessageID ASIODNS_FETCHCOMP = "FETCHCOMP";
extern const isc::log::MessageID ASIODNS_FETCHSTOP = "FETCHSTOP";
extern const isc::log::MessageID ASIODNS_OPENSOCK = "OPENSOCK";
extern const isc::log::MessageID ASIODNS_RECVSOCK = "RECVSOCK";
extern const isc::log::MessageID ASIODNS_RECVTMO = "RECVTMO";
extern const isc::log::MessageID ASIODNS_SENDSOCK = "SENDSOCK";
extern const isc::log::MessageID ASIODNS_UNKORIGIN = "UNKORIGIN";
extern const isc::log::MessageID ASIODNS_UNKRESULT = "UNKRESULT";

} // namespace asiodns
} // namespace isc

namespace {

const char* values[] = {
    "FETCHCOMP", "upstream fetch to %s(%d) has now completed",
    "FETCHSTOP", "upstream fetch to %s(%d) has been stopped",
    "OPENSOCK", "error %d opening %s socket to %s(%d)",
    "RECVSOCK", "error %d reading %s data from %s(%d)",
    "RECVTMO", "receive timeout while waiting for data from %s(%d)",
    "SENDSOCK", "error %d sending data using %s to %s(%d)",
    "UNKORIGIN", "unknown origin for ASIO error code %d (protocol: %s, address %s)",
    "UNKRESULT", "unknown result (%d) when IOFetch::stop() was executed for I/O to %s(%d)",
    NULL
};

const isc::log::MessageInitializer initializer(values);

} // Anonymous namespace

