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

#ifndef __DATA_SOURCE_SQLITE3_H
#define __DATA_SOURCE_SQLITE3_H

#include <string>

#include <exceptions/exceptions.h>

#include <sqlite3.h>

#include "data_source.h"

namespace isc {

namespace dns {
class Name;
class RRClass;
class RRType;
class RRsetList;
}

namespace auth {

class Query;

class Sqlite3Error : public Exception {
public:
    Sqlite3Error(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) {}
};

class Sqlite3DataSrc : public DataSrc {
    ///
    /// \name Constructors, Assignment Operator and Destructor.
    ///
    /// Note: The copy constructor and the assignment operator are intentionally
    /// defined as private.
    //@{
private:
    Sqlite3DataSrc(const Sqlite3DataSrc& source);
    Sqlite3DataSrc& operator=(const Sqlite3DataSrc& source);
public:
    Sqlite3DataSrc();
    ~Sqlite3DataSrc();
    //@}

    void findClosestEnclosure(NameMatch& match) const;

    Result findRRset(const Query& q,
                     const isc::dns::Name& qname,
                     const isc::dns::RRClass& qclass,
                     const isc::dns::RRType& qtype,
                     isc::dns::RRsetList& target,
                     uint32_t& flags,
                     const isc::dns::Name* zonename) const;

    Result findExactRRset(const Query& q,
                          const isc::dns::Name& qname,
                          const isc::dns::RRClass& qclass,
                          const isc::dns::RRType& qtype,
                          isc::dns::RRsetList& target,
                          uint32_t& flags,
                          const isc::dns::Name* zonename) const;

    Result findAddrs(const Query& q,
                       const isc::dns::Name& qname,
                       const isc::dns::RRClass& qclass,
                       isc::dns::RRsetList& target,
                       uint32_t& flags,
                       const isc::dns::Name* zonename) const;

    Result findReferral(const Query& q,
                        const isc::dns::Name& qname,
                        const isc::dns::RRClass& qclass,
                        isc::dns::RRsetList& target,
                        uint32_t& flags,
                        const isc::dns::Name* zonename) const;

    DataSrc::Result findPreviousName(const Query& q,
                                     const isc::dns::Name& qname,
                                     isc::dns::Name& target,
                                     const isc::dns::Name* zonename) const;

    Result findCoveringNSEC3(const Query& q,
                             const isc::dns::Name& zonename,
                             std::string& hash,
                             isc::dns::RRsetList& target) const;

    Result init();
    Result init(const std::string& dbfile);
    Result close();

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
    int findRecords(const isc::dns::Name& name, const isc::dns::RRType& rdtype,
                    isc::dns::RRsetList& target, const isc::dns::Name* zonename,
                    const Mode mode, uint32_t& flags) const;
    int findClosest(const char *name, const char **position) const;
    void loadVersion(void);
    void setupPreparedStatements(void);
    void execSetupQuery(const char *query);
    void checkAndSetupSchema(void);

    sqlite3 *db;
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
    sqlite3_stmt *q_nsec3;
    sqlite3_stmt *q_prevnsec3;
};

}
}

#endif // __DATA_SOURCE_SQLITE3_H

// Local Variables: 
// mode: c++
// End: 
