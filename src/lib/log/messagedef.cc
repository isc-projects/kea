// File created from messagedef.mes on Mon Feb  7 11:47:45 2011

#include <cstddef>
#include <log/message_initializer.h>

namespace {

const char* values[] = {
    "DUPLNS", "duplicate $NAMESPACE directive found",
    "DUPLPRFX", "duplicate $PREFIX directive found",
    "IDNOTFND", "could not replace message for '%s': no such message identification",
    "NSEXTRARG", "$NAMESPACE directive has too many arguments",
    "NSINVARG", "$NAMESPACE directive has an invalid argument ('%s')",
    "NSNOARG", "no arguments were given to the $NAMESPACE directive",
    "ONETOKEN", "a line containing a message ID ('%s') and nothing else was found",
    "OPENIN", "unable to open message file %s for input: %s",
    "OPENOUT", "unable to open %s for output: %s",
    "PRFEXTRARG", "$PREFIX directive has too many arguments",
    "PRFINVARG", "$PREFIX directive has an invalid argument ('%s')",
    "PRFNOARG", "no arguments were given to the $PREFIX directive",
    "READERR", "error reading from %s: %s",
    "UNRECDIR", "unrecognised directive '%s'",
    "WRITERR", "error writing to %s: %s",
    NULL
};

} // Anonymous namespace

namespace isc {
namespace log {

MessageInitializer messagedef_cc_Mon_Feb__7_11_47_45_2011(values);

} // namespace log
} // namespace isc

