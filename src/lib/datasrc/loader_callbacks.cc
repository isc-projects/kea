// Copyright (C) 2012  Internet Systems Consortium, Inc. ("ISC")
//
// Permission to use, copy, modify, and/or distribute this software for any
// purpose with or without fee is hereby granted, provided that the above
// copyright notice and this permission notice appear in all copies.
//
// THE SOFTWARE IS PROVIDED "AS IS" AND ISC DISCLAIMS ALL WARRANTIES WITH
// REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
// AND FITNESS.  IN NO EVENT SHALL ISC BE LIABLE FOR ANY SPECIAL, DIRECT,
// INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
// LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE
// OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
// PERFORMANCE OF THIS SOFTWARE.

#include <datasrc/loader_callbacks.h>
#include <datasrc/zone.h>
#include <datasrc/logger.h>

#include <dns/name.h>
#include <dns/rrclass.h>
#include <dns/rrset.h>

#include <string>
#include <boost/bind.hpp>

namespace isc {
namespace datasrc {

namespace {

void
logError(const dns::Name& name, const dns::RRClass& rrclass, bool* ok,
         const std::string& source, size_t line, const std::string& reason)
{
    LOG_ERROR(logger, DATASRC_LOAD_CONTEXT_ERROR).arg(source).arg(line).
        arg(name).arg(rrclass).arg(reason);
    if (ok != NULL) {
        *ok = false;
    }
}

void
logWarning(const dns::Name& name, const dns::RRClass& rrclass,
         const std::string& source, size_t line, const std::string& reason)
{
    LOG_WARN(logger, DATASRC_LOAD_CONTEXT_WARN).arg(source).arg(line).
        arg(name).arg(rrclass).arg(reason);
}

}

isc::dns::LoaderCallbacks
createCallbacks(ZoneUpdater& updater, const dns::Name& name,
                const dns::RRClass& rrclass, bool* ok)
{
    return (isc::dns::LoaderCallbacks(boost::bind(&logError, name, rrclass, ok,
                                                  _1, _2, _3),
                                      boost::bind(&logWarning, name, rrclass,
                                                  _1, _2, _3),
                                      boost::bind(&ZoneUpdater::addRRset,
                                                  &updater,
                                                  // The callback provides a
                                                  // shared pointer, we need
                                                  // the object. This bind
                                                  // unpacks the object.
                                                  boost::bind(&dns::RRsetPtr::
                                                              operator*,
                                                              _1))));
}

}
}
