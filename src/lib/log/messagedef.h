// File created from messagedef.mes on Tue Feb  8 18:01:54 2011

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

// The next two objects are needed to bring the default message
// definitions into the program.  They make sure that the file
// containing the message text is included in the link process.
//
// The objects are uniquely named (with file name and date and
// time of compilation) to avoid clashes with other objects of
// the same type, either by another #include or as a global
// symbol in another module.

extern MessageInitializer messagedef_cc_Tue_Feb__8_18_01_54_2011;
static MessageInstantiator instantiate_messagedef_cc_Tue_Feb__8_18_01_54_2011(
   &messagedef_cc_Tue_Feb__8_18_01_54_2011);

} // namespace log
} // namespace isc
#endif // __MESSAGEDEF_H
