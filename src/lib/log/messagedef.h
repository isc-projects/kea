// File created from messagedef.mes on Mon Feb  7 11:18:04 2011

#ifndef __MESSAGEDEF_H
#define __MESSAGEDEF_H

#include <log/message_types.h>
#include <log/message_initializer.h>

namespace isc {
namespace log {

static const isc::log::MessageID MSG_DUPLNS = "DUPLNS";
static const isc::log::MessageID MSG_DUPLPRFX = "DUPLPRFX";
static const isc::log::MessageID MSG_IDNOTFND = "IDNOTFND";
static const isc::log::MessageID MSG_NSEXTRARG = "NSEXTRARG";
static const isc::log::MessageID MSG_NSINVARG = "NSINVARG";
static const isc::log::MessageID MSG_NSNOARG = "NSNOARG";
static const isc::log::MessageID MSG_ONETOKEN = "ONETOKEN";
static const isc::log::MessageID MSG_OPENIN = "OPENIN";
static const isc::log::MessageID MSG_OPENOUT = "OPENOUT";
static const isc::log::MessageID MSG_PRFEXTRARG = "PRFEXTRARG";
static const isc::log::MessageID MSG_PRFINVARG = "PRFINVARG";
static const isc::log::MessageID MSG_PRFNOARG = "PRFNOARG";
static const isc::log::MessageID MSG_READERR = "READERR";
static const isc::log::MessageID MSG_UNRECDIR = "UNRECDIR";
static const isc::log::MessageID MSG_WRITERR = "WRITERR";

} // namespace log
} // namespace isc

namespace isc {
namespace log {

extern MessageInitializer messagedef_cc_Mon_Feb__7_11_18_04_2011;
static MessageInstantiator m(&messagedef_cc_Mon_Feb__7_11_18_04_2011);

} // namespace log
} // namespace isc

#endif // __MESSAGEDEF_H
