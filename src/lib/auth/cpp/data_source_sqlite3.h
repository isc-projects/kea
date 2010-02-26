// Copyright (C) 2010  Internet Systems Consortium, Inc. ("ISC")
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

// $Id$

#ifndef __SQLITE3_DATA_SOURCE_H
#define __SQLITE3_DATA_SOURCE_H

#include <sqlite3.h>

#include "data_source.h"

using namespace isc::dns;

namespace isc {
namespace auth {

class Sqlite3DataSrc : public DataSrc {
public:
    Sqlite3DataSrc();
    virtual ~Sqlite3DataSrc();

    virtual void findClosestEnclosure(NameMatch& match) const;

    virtual Result findRRset(const Query& q,
                             const Name& qname,
                             const RRClass& qclass,
                             const RRType& qtype,
                             RRsetList& target,
                             uint32_t& flags,
                             Name* zone = NULL) const;

    virtual Result findExactRRset(const Query& q,
                                  const Name& qname,
                                  const RRClass& qclass,
                                  const RRType& qtype,
                                  RRsetList& target,
                                  uint32_t& flags,
                                  Name* zone = NULL) const;

    virtual Result findAddrs(const Query& q,
                               const Name& qname,
                               const RRClass& qclass,
                               RRsetList& target,
                               uint32_t& flags,
                               Name* zone = NULL) const;

    virtual Result findReferral(const Query& q,
                                const Name& qname,
                                const RRClass& qclass,
                                RRsetList& target,
                                uint32_t& flags,
                                Name* zone = NULL) const;

    virtual DataSrc::Result findPreviousName(const Query& q,
                                             const Name& qname,
                                             Name& target,
                                             Name* zone) const;

    virtual Result init();
    virtual Result close();

private:
    enum Mode {
        NORMAL,
        ADDRESS,
        DELEGATION
    };

    void open(const std::string& name);
    sqlite3_stmt* prepare(const char *statement);
    void release(sqlite3_stmt* prepared);
    int getVersion(void);
    int hasExactZone(const char *name) const;
    int findRecords(const Name& name, const RRType& rdtype,
                    RRsetList& target, Name* zone,
                    const Mode mode, uint32_t& flags) const;
    int findClosest(const char *name, const char **position) const;
    void loadVersion(void);
    void setupPreparedStatements(void);
    void execSetupQuery(const char *query);
    void checkAndSetupSchema(void);

    sqlite3 *db;
    std::string database_name;
    int database_version;
    
    //
    // Prepared statements
    //
    sqlite3_stmt *q_zone;
    sqlite3_stmt *q_record;
    sqlite3_stmt *q_addrs;
    sqlite3_stmt *q_referral;
    sqlite3_stmt *q_any;
    sqlite3_stmt *q_count;
    sqlite3_stmt *q_previous;
};

}
}

#endif // __SQLITE3_DATA_SOURCE_H

// Local Variables: 
// mode: c++
// End: 
