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

#include <string>

#include "data_source_sqlite3.h"

#include <dns/rrttl.h>
#include <dns/rdata.h>
#include <dns/rdataclass.h>
#include <dns/rrset.h>
#include <dns/rrsetlist.h>

#include <iostream>

using namespace std;
using namespace isc::dns;
using namespace isc::dns::rdata;

namespace isc {
namespace auth {

namespace {
// Note: this cannot be std::string to avoid
// "static initialization order fiasco".
static const char* DEFAULT_DB_FILE = "/tmp/zone.sqlite3";
}

//
//  Prepare a statement.  Can call release() or sqlite3_finalize()
//  directly.
//
sqlite3_stmt* Sqlite3DataSrc::prepare(const char* statement) {
    int rc;
    sqlite3_stmt* prepared = NULL;

    rc = sqlite3_prepare_v2(db, statement, -1, &prepared, NULL);
    if (rc != SQLITE_OK) {
        throw("could not prepare");
    }
    return (prepared);
}

//
//  Release memory associated with a prepared query.
//
void Sqlite3DataSrc::release(sqlite3_stmt* prepared) {
    sqlite3_finalize(prepared);
}

//
//  Get the database schema version.
//
int Sqlite3DataSrc::getVersion(void) {
    if (database_version == -1) {
        loadVersion();
    }
    return (database_version);
}

//
//  Find the exact zone match.  Return -1 if not found, or the zone's
//  ID if found.  This will always be >= 0 if found.
//
int Sqlite3DataSrc::hasExactZone(const char* name) const {
    int rc, i;
    sqlite3_reset(q_zone);
    rc = sqlite3_bind_text(q_zone, 1, name, -1, SQLITE_STATIC);
    if (rc != SQLITE_OK) {
        throw("Could not bind");
    }
    rc = sqlite3_step(q_zone);
    if (rc == SQLITE_ROW) {
        i = sqlite3_column_int(q_zone, 0);
    } else {
        i = -1;
    }
    sqlite3_reset(q_zone);
    return (i);
}

int
Sqlite3DataSrc::findRecords(const Name& name, const RRType& rdtype,
                            RRsetList& target, const Name* zonename,
                            const Mode mode, uint32_t& flags) const
{
    int rc;
    const string s_name = name.toText();
    const char* const c_name = s_name.c_str();
    sqlite3_stmt* query;

    switch (mode) {
    case ADDRESS:
        query = q_addrs;
        break;
    case DELEGATION:
        query = q_referral;
        break;
    default:
        if (rdtype == RRType::ANY()) {
            query = q_any;
        } else {
            query = q_record;
        }
        break;
    }

    flags = 0;

    int zone_id = (zonename == NULL) ? findClosest(c_name, NULL) :
        findClosest(zonename->toText().c_str(), NULL);
    if (zone_id < 0) {
        flags = NO_SUCH_ZONE;
        return (0);
    }
    
    sqlite3_reset(query);
    sqlite3_clear_bindings(query);

    rc = sqlite3_bind_int(query, 1, zone_id);
    if (rc != SQLITE_OK) {
        throw("Could not bind 1 (query)");
    }
    rc = sqlite3_bind_text(query, 2, c_name, -1, SQLITE_STATIC);
    if (rc != SQLITE_OK) {
        throw("Could not bind 2 (query)");
    }

    if (query == q_record) {
        rc = sqlite3_bind_text(query, 3, rdtype.toText().c_str(), -1,
                               SQLITE_STATIC);
        if (rc != SQLITE_OK) {
            throw("Could not bind 3 (query)");
        }
    }
  
    // loop
    int rows = 0;
    RRsetPtr rrset;
    bool any = (rdtype == RRType::ANY());

    rc = sqlite3_step(query);
    while (rc == SQLITE_ROW) {
        const char* type = (const char*)sqlite3_column_text(query, 0);
        int ttl = sqlite3_column_int(query, 1);
        const char* sigtype = (const char*)sqlite3_column_text(query, 2);
        const char* rdata = (const char*)sqlite3_column_text(query, 3);

        RRType rt(sigtype ? sigtype : type);

        // found an NS; we need to inform the caller that this might be a
        // referral, but we do not return the NS RRset to the caller
        // unless asked for it.
        if (rt == RRType::NS() && !any) {
            flags |= REFERRAL;
            if (rdtype != RRType::NS()) {
                rc = sqlite3_step(query);
                continue;
            }
        }

        ++rows;

        // Looking for something else but found CNAME
        if (rt == RRType::CNAME() && rdtype != RRType::CNAME()) {
            if (rdtype == RRType::NSEC()) {
                // NSEC query, just skip the CNAME
                rc = sqlite3_step(query);
                continue;
            } else if (!any) {
                // include the CNAME, but don't flag it for chasing if
                // this is an ANY query
                flags |= CNAME_FOUND;
            }
        }

        if (!target[rt]) {
            rrset = RRsetPtr(new RRset(name, RRClass::IN(), rt, RRTTL(ttl)));
            target.addRRset(rrset);
        }

        if (!sigtype && RRType(type) == rrset->getType()) {
            rrset->addRdata(createRdata(RRType(type), RRClass::IN(), rdata));
            if (ttl > rrset->getTTL().getValue()) {
                rrset->setTTL(RRTTL(ttl));
            }
        } else if (sigtype && RRType(sigtype) == rrset->getType()) {
            RdataPtr rrsig = createRdata(RRType::RRSIG(), RRClass::IN(), rdata);
            if (rrset->getRRsig()) {
                rrset->getRRsig()->addRdata(rrsig);
            } else {
                RRsetPtr sigs = RRsetPtr(new RRset(name, RRClass::IN(),
                                                   RRType::RRSIG(),
                                                   RRTTL(ttl)));
                sigs->addRdata(rrsig);
                rrset->addRRsig(sigs);
            }

            if (ttl > rrset->getRRsig()->getTTL().getValue()) {
                rrset->getRRsig()->setTTL(RRTTL(ttl));
            }
        }

        rc = sqlite3_step(query);
    }

    sqlite3_reset(query);
    if (rows > 0) {
        return (rows);
    }

    //
    // No rows were found.  We need to find out whether there are
    // any RRs with that name to determine whether this is NXDOMAIN or
    // NXRRSET
    //
    sqlite3_reset(q_count);
    sqlite3_clear_bindings(q_count);

    rc = sqlite3_bind_int(q_count, 1, zone_id);
    if (rc != SQLITE_OK) {
        throw("Could not bind 1 (count)");
    }

    rc = sqlite3_bind_text(q_count, 2, c_name, -1, SQLITE_STATIC);
    if (rc != SQLITE_OK) {
        throw("Could not bind 2 (count)");
    }

    rc = sqlite3_step(q_count);
    if(rc == SQLITE_ROW) {
        if (sqlite3_column_int(q_count, 0) != 0) {
            flags |= TYPE_NOT_FOUND;
            sqlite3_reset(q_count);
            return (0);
        }
    }

    flags |= NAME_NOT_FOUND;
    sqlite3_reset(q_count);
    return (0);
}

//
//  Search for the closest enclosing zone.  Will return -1 if not found,
//  >= 0 if found.  If position is not NULL, it will be filled in with the
//  longest match found.
//
int Sqlite3DataSrc::findClosest(const char* name, const char** position) const {
    const char* current = name;
    
    while (*current != 0) {
        int rc = hasExactZone(current);
        if (rc >= 0) {
            if (position != NULL) {
                *position = current;
            }
            return (rc);
        }
        while (*current != '.' && *current != 0) {
            ++current;
        }
        if (*current == '.') {
            ++current;
        }
    }

    return (-1);
}

void
Sqlite3DataSrc::loadVersion(void) {
    const char* q = "SELECT version FROM schema_version";
    sqlite3_stmt* prepared = prepare(q);
    if (sqlite3_step(prepared) != SQLITE_ROW) {
        throw("failed to find a row in schema_version table");
    }
    database_version = sqlite3_column_int(prepared, 0);
    release(prepared);
}

void
Sqlite3DataSrc::setupPreparedStatements(void) {

    const char* q_zone_str = "SELECT id FROM zones WHERE name=?1";
    try {
        q_zone = prepare(q_zone_str);
    } catch (const char* e) {
        cout << e << endl << q_zone_str << endl;
        cout << sqlite3_errmsg(db) << endl;
        throw(e);
    }

    const char* q_record_str = "SELECT rdtype, ttl, sigtype, rdata "
                               "FROM records WHERE zone_id=?1 AND name=?2 AND "
                               "((rdtype=?3 OR sigtype=?3) OR "
                               "(rdtype='CNAME' OR sigtype='CNAME') OR "
                               "(rdtype='NS' OR sigtype='NS'))";
    try {
        q_record = prepare(q_record_str);
    } catch (const char* e) {
        cout << e << endl << q_record_str << endl;
        cout << sqlite3_errmsg(db) << endl;
        throw(e);
    }

    const char* q_addrs_str = "SELECT rdtype, ttl, sigtype, rdata "
                               "FROM records WHERE zone_id=?1 AND name=?2 AND "
                               "(rdtype='A' OR sigtype='A' OR "
                               "rdtype='AAAA' OR sigtype='AAAA')";
    try {
        q_addrs = prepare(q_addrs_str);
    } catch (const char* e) {
        cout << e << endl << q_addrs_str << endl;
        cout << sqlite3_errmsg(db) << endl;
        throw(e);
    }
    const char* q_referral_str = "SELECT rdtype, ttl, sigtype, rdata FROM "
                                 "records WHERE zone_id=?1 AND name=?2 AND"
                                 "(rdtype='NS' OR sigtype='NS' OR "
                                 "rdtype='DS' OR sigtype='DS' OR "
                                 "rdtype='DNAME' OR sigtype='DNAME')";
    try {
        q_referral = prepare(q_referral_str);
    } catch (const char* e) {
        cout << e << endl << q_referral_str << endl;
        cout << sqlite3_errmsg(db) << endl;
        throw(e);
    }
    const char* q_any_str = "SELECT rdtype, ttl, sigtype, rdata "
                             "FROM records WHERE zone_id=?1 AND name=?2";
    try {
        q_any = prepare(q_any_str);
    } catch (const char* e) {
        cout << e << endl << q_any_str << endl;
        cout << sqlite3_errmsg(db) << endl;
        throw(e);
    }

    const char* q_count_str = "SELECT COUNT(*) FROM records "
                              "WHERE zone_id=?1 AND (name=?2 OR "
                              "name LIKE '%.' || ?2);";
    try {
        q_count = prepare(q_count_str);
    } catch (const char* e) {
        cout << e << endl << q_count_str << endl;
        cout << sqlite3_errmsg(db) << endl;
        throw(e);
    }

    const char* q_previous_str = "SELECT name FROM records "
                                 "WHERE zone_id=?1 AND rdtype = 'NSEC' AND "
                                 "rname < $2 ORDER BY rname DESC LIMIT 1";
    try {
        q_previous = prepare(q_previous_str);
    } catch (const char* e) {
        cout << e << endl << q_previous_str << endl;
        cout << sqlite3_errmsg(db) << endl;
        throw(e);
    }

    const char* q_nsec3_str = "SELECT rdtype, ttl, rdata FROM nsec3 "
                              "WHERE zone_id=?1 AND hash == $2";
    try {
        q_nsec3 = prepare(q_nsec3_str);
    } catch (const char* e) {
        cout << e << endl << q_nsec3_str << endl;
        cout << sqlite3_errmsg(db) << endl;
        throw(e);
    }

#ifdef notyet
    const char* q_prevnsec3_str = "SELECT rdtype, ttl, rdata FROM nsec3 "
                                  "WHERE zone_id=?1 AND hash <= $2 "
                                  "ORDER BY rhash DESC LIMIT 1";
    try {
        q_prevnsec3 = prepare(q_prevnsec3_str);
    } catch (const char* e) {
        cout << e << endl << q_prevnsec3_str << endl;
        cout << sqlite3_errmsg(db) << endl;
        throw(e);
    }
#endif
}

void
Sqlite3DataSrc::execSetupQuery(const char* query) {
    int rc;

    rc = sqlite3_exec(db, query, NULL, NULL, NULL);
    if (rc != SQLITE_OK) {
        throw(query);
    }
}

void
Sqlite3DataSrc::checkAndSetupSchema(void) {
    try {
        loadVersion();
        setupPreparedStatements();
        cout << "Loaded existing schema" << endl;
    } catch(...) {
        execSetupQuery("CREATE TABLE schema_version ("
                          "version INTEGER NOT NULL)");
        execSetupQuery("INSERT INTO schema_version VALUES (1)");
        execSetupQuery("CREATE TABLE zones ("
                          "id INTEGER PRIMARY KEY, "
                          "name STRING NOT NULL, "
                          "rdclass STRING NOT NULL DEFAULT 'IN', "
                          "dnssec BOOLEAN NOT NULL DEFAULT 0)");
        execSetupQuery("CREATE INDEX zones_byname ON zones (name)");
        execSetupQuery("CREATE TABLE records ("
                          "id INTEGER PRIMARY KEY, "
                          "zone_id INTEGER NOT NULL, "
                          "name STRING NOT NULL, "
                          "rname STRING NOT NULL, "
                          "ttl INTEGER NOT NULL, "
                          "rdtype STRING NOT NULL, "
                          "sigtype STRING, "
                          "rdata STRING NOT NULL)");
        execSetupQuery("CREATE INDEX records_byname ON records (name)");
        execSetupQuery("CREATE INDEX records_byrname ON records (rname)");
        execSetupQuery("CREATE TABLE nsec3 ("
                          "id INTEGER PRIMARY KEY, "
                          "zone_id INTEGER NOT NULL, "
                          "hash STRING NOT NULL, "
                          "owner STRING NOT NULL, "
                          "ttl INTEGER NOT NULL, "
                          "rdtype STRING NOT NULL, "
                          "rdata STRING NOT NULL)");
        execSetupQuery("CREATE INDEX nsec3_byhash ON nsec3 (hash)");

        setupPreparedStatements();
        cout << "Created new file and schema" << endl;
    }
}

Sqlite3DataSrc::Sqlite3DataSrc() :
    db(NULL)
{
    database_version = -1;
    q_zone = NULL;
    q_record = NULL;
    q_addrs = NULL;
    q_referral = NULL;
    q_any = NULL;
    q_count = NULL;
    q_previous = NULL;
    q_nsec3 = NULL;
    q_prevnsec3 = NULL;
}

Sqlite3DataSrc::~Sqlite3DataSrc() {
    close();
}

DataSrc::Result
Sqlite3DataSrc::init(const string& dbfile) {
    open(dbfile);
    cerr << "Schema version: " << getVersion() << endl;

    return (SUCCESS);
}

DataSrc::Result
Sqlite3DataSrc::init() {
    return (init(DEFAULT_DB_FILE));
}

void
Sqlite3DataSrc::findClosestEnclosure(NameMatch& match) const {
    const char* position = NULL;
    
    if (findClosest(match.qname().toText().c_str(), &position) == -1) {
        return;
    }

    match.update(*this, Name(position));
}

DataSrc::Result
Sqlite3DataSrc::findPreviousName(const Query& q,
                                 const Name& qname,
                                 Name& target,
                                 const Name* zonename) const
{
    int zone_id = (zonename == NULL) ?
        findClosest(qname.toText().c_str(), NULL) :
        findClosest(zonename->toText().c_str(), NULL);

    if (zone_id < 0) {
        return (ERROR);
    }
    
    sqlite3_reset(q_previous);
    sqlite3_clear_bindings(q_previous);

    int rc = sqlite3_bind_int(q_previous, 1, zone_id);
    if (rc != SQLITE_OK) {
        throw ("Could not bind 1 (previous)");
    }
    rc = sqlite3_bind_text(q_previous, 2, qname.reverse().toText().c_str(),
                           -1, SQLITE_STATIC);
    if (rc != SQLITE_OK) {
        throw ("Could not bind 2 (previous)");
    }
  
    rc = sqlite3_step(q_previous);
    if (rc != SQLITE_ROW) {
        sqlite3_reset(q_previous);
        return (ERROR);
    }

    // XXX: bad cast.  we should revisit this.
    target = Name((const char*)sqlite3_column_text(q_previous, 0));
    sqlite3_reset(q_previous);
    return (SUCCESS);
}

DataSrc::Result
Sqlite3DataSrc::findCoveringNSEC3(const Query& q,
                                  const string& hashstr,
                                  const Name& zonename,
                                  RRsetList& target) const
{
    int zone_id = findClosest(zonename.toText().c_str(), NULL);
    if (zone_id < 0) {
        return (ERROR);
    }

    sqlite3_reset(q_prevnsec3);
    sqlite3_clear_bindings(q_prevnsec3);

    int rc = sqlite3_bind_int(q_prevnsec3, 1, zone_id);
    if (rc != SQLITE_OK) {
        throw ("Could not bind 1 (previous NSEC3)");
    }

    rc = sqlite3_bind_text(q_prevnsec3, 2, hashstr.c_str(), -1, SQLITE_STATIC);
    if (rc != SQLITE_OK) {
        throw ("Could not bind 2 (previous NSEC3)");
    }

    rc = sqlite3_step(q_prevnsec3);
    const char* hash;
    if (rc == SQLITE_ROW) {
        hash = (const char*) sqlite3_column_text(q_prevnsec3, 0);
    } else {
        // We need to find the final NSEC3 in the chain.
        // A valid NSEC3 hash is in base32, which contains no
        // letters higher than V, so a search for the previous 
        // NSEC3 from "w" will always find it.
        sqlite3_reset(q_prevnsec3);
        rc = sqlite3_bind_text(q_prevnsec3, 2, "w", -1, SQLITE_STATIC);
        if (rc != SQLITE_OK) {
            throw ("Could not bind 2 (last NSEC3)");
        }

        rc = sqlite3_step(q_prevnsec3);
        if (rc != SQLITE_ROW) {
            return (ERROR);
        }

        hash = (const char*) sqlite3_column_text(q_prevnsec3, 0);
    }

    sqlite3_reset(q_nsec3);
    sqlite3_clear_bindings(q_nsec3);

    rc = sqlite3_bind_int(q_nsec3, 1, zone_id);
    if (rc != SQLITE_OK) {
        throw ("Could not bind 1 (NSEC3)");
    }

    rc = sqlite3_bind_text(q_nsec3, 2, hash, -1, SQLITE_STATIC);
    if (rc != SQLITE_OK) {
        throw ("Could not bind 2 (NSEC3)");
    }

    int target_ttl = -1;
    int sig_ttl = -1;
    const Name& name(Name(hash).concatenate(zonename));
    RRsetPtr rrset(new RRset(name, RRClass::IN(), RRType::NSEC3(), RRTTL(0)));
    if (!target[RRType::NSEC3()]) {
        target.addRRset(rrset);
    }

    rc = sqlite3_step(q_nsec3);
    while (rc == SQLITE_ROW) {
        RRType type((const char*)sqlite3_column_text(q_nsec3, 1));
        int ttl = sqlite3_column_int(q_nsec3, 2);
        const char* rdata = (const char*)sqlite3_column_text(q_nsec3, 3);

        if (type == RRType::NSEC3()) {
            rrset->addRdata(createRdata(type, RRClass::IN(), rdata));
            if (target_ttl == -1 || target_ttl > ttl) {
                target_ttl = ttl;
            }
            rrset->setTTL(RRTTL(target_ttl));
        } else {
            RdataPtr rrsig = createRdata(RRType::RRSIG(), RRClass::IN(), rdata);
            if (rrset->getRRsig()) {
                rrset->getRRsig()->addRdata(rrsig);
            } else {
                RRsetPtr sigs = RRsetPtr(new RRset(name, RRClass::IN(),
                                                   RRType::RRSIG(), RRTTL(0)));
                sigs->addRdata(rrsig);
                rrset->addRRsig(sigs);
            }
        }

        if (sig_ttl == -1 || sig_ttl > ttl) {
            sig_ttl = ttl;
        }
        rrset->getRRsig()->setTTL(RRTTL(sig_ttl));
        rc = sqlite3_step(q_nsec3);
    }

    sqlite3_reset(q_nsec3);
    return (SUCCESS);
}

DataSrc::Result
Sqlite3DataSrc::findRRset(const Query& q,
                          const Name& qname,
                          const RRClass& qclass,
                          const RRType& qtype,
                          RRsetList& target,
                          uint32_t& flags,
                          const Name* zonename) const
{
    findRecords(qname, qtype, target, zonename, NORMAL, flags);
    return (SUCCESS);
}

DataSrc::Result
Sqlite3DataSrc::findExactRRset(const Query& q,
                               const Name& qname,
                               const RRClass& qclass,
                               const RRType& qtype,
                               RRsetList& target,
                               uint32_t& flags,
                               const Name* zonename) const
{
    findRecords(qname, qtype, target, zonename, NORMAL, flags);

    // Ignore referrals in this case
    flags &= ~REFERRAL;

    // CNAMEs don't count in this case
    if (flags & CNAME_FOUND) {
        flags &= ~CNAME_FOUND;
        flags |= TYPE_NOT_FOUND;
    }

    return (SUCCESS);
}

DataSrc::Result
Sqlite3DataSrc::findAddrs(const Query& q,
                          const Name& qname,
                          const RRClass& qclass,
                          RRsetList& target,
                          uint32_t& flags,
                          const Name* zonename) const
{
    findRecords(qname, RRType::ANY(), target, zonename, ADDRESS, flags);
    return (SUCCESS);
}

DataSrc::Result
Sqlite3DataSrc::findReferral(const Query& q,
                             const Name& qname,
                             const RRClass& qclass,
                             RRsetList& target,
                             uint32_t& flags,
                             const Name* zonename) const
{
    findRecords(qname, RRType::ANY(), target, zonename, DELEGATION, flags);
    return (SUCCESS);
}
//
//  Open the database.
//
void
Sqlite3DataSrc::open(const string& name) {
    int rc;

    database_name = name;
    
    rc = sqlite3_open(database_name.c_str(), &db);
    if (rc) {
        cerr << "open database: " << sqlite3_errmsg(db) << "\n";
        sqlite3_close(db);
        throw("Cannot open database");
    }
    
    checkAndSetupSchema();
}

DataSrc::Result
Sqlite3DataSrc::close(void) {
    if (db == NULL) {
        return (SUCCESS);
    }

    if (q_zone != NULL) {
        release(q_zone);
        q_zone = NULL;
    }

    if (q_record) {
        release(q_record);
        q_record = NULL;
    }

    if (q_addrs) {
        release(q_addrs);
        q_addrs = NULL;
    }

    if (q_referral) {
        release(q_referral);
        q_referral = NULL;
    }

    if (q_any) {
        release(q_any);
        q_any = NULL;
    }

    if (q_count) {
        release(q_count);
        q_count = NULL;
    }

    if (q_previous) {
        release(q_previous);
        q_previous = NULL;
    }

    if (q_prevnsec3) {
        release(q_prevnsec3);
        q_prevnsec3 = NULL;
    }

    if (q_nsec3) {
        release(q_nsec3);
        q_nsec3 = NULL;
    }

    sqlite3_close(db);

    db = NULL;
    return (SUCCESS);
}

}
}
