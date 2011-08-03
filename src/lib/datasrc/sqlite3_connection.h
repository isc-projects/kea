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

#include <exceptions/exceptions.h>
#include <cc/data.h>

#include <string>

namespace isc {
namespace dns {
class RRClass;
}

namespace datasrc {

class SQLite3Error : public Exception {
public:
    SQLite3Error(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) {}
};

struct SQLite3Parameters;

class SQLite3Connection : public DatabaseConnection {
public:
    SQLite3Connection(const isc::data::ConstElementPtr& config,
                      const isc::dns::RRClass& rrclass);
    ~ SQLite3Connection();
    virtual std::pair<bool, int> getZone(const isc::dns::Name& name) const;
private:
    SQLite3Parameters* dbparameters_;
    std::string class_;
    void open(const std::string& filename);
    void close();
};

}
}

#endif
