// Copyright (C) 2011  Internet Systems Consortium, Inc. ("ISC")
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


#ifndef __DATASRC_SQLITE3_CONNECTION_H
#define __DATASRC_SQLITE3_CONNECTION_H

#include <datasrc/database.h>

// TODO Once the whole SQLite3 thing is ported here, move the Sqlite3Error
// here and remove the header file.
#include <datasrc/sqlite3_datasrc.h>

namespace isc {
namespace datasrc {

class SQLite3Connection : public DatabaseConnection {
public:
    // TODO Should we simplify this as well and just pass config to the
    // constructor and be done? (whenever the config would change, we would
    // recreate new connections)
    Result init() { return (init(isc::data::ElementPtr())); }
    Result init(const isc::data::ConstElementPtr& config);
    Result close();

    virtual std::pair<bool, int> getZone(const isc::dns::Name& name) const;
};

}
}

#endif
