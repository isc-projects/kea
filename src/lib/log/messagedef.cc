// File created from messagedef.mes on Fri Jan  7 17:26:42 2011

#include <cstddef>
#include <log/message_initializer.h>

using namespace isc::log;

namespace {

const char* values[] = {
    "DUPLPRFX", "duplicate $PREFIX directive found",
    "ONETOKEN", "a line containing a message ID ('%s') and nothing else was found",
    "OPENIN", "unable to open %s for input: %s",
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

MessageInitializer messagedef_cc_Fri_Jan__7_17_26_42_2011(values);
