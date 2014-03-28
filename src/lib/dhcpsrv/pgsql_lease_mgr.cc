// Copyright (C) 2012 Internet Systems Consortium, Inc. ("ISC")
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

#include <config.h>

#include <asiolink/io_address.h>
#include <dhcp/duid.h>
#include <dhcp/hwaddr.h>
#include <dhcpsrv/dhcpsrv_log.h>
#include <dhcpsrv/pgsql_lease_mgr.h>

#include <boost/static_assert.hpp>

#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <time.h>

using namespace isc;
using namespace isc::dhcp;
using namespace std;

namespace {

// Maximum number of parameters used in any signle query
const size_t MAX_PARAMETERS_IN_QUERY = 13;

// Defines a single query
struct TaggedStatement {

    /// Query index
    /// @todo cppcheck flags index as unused
    PgSqlLeaseMgr::StatementIndex index;

    /// Number of parameters for a given query
    int nbparams;

    /// @brief OID types
    ///
    /// Sspecify parameter types. See /usr/include/postgresql/catalog/pg_type.h.
    /// For some reason that header does not export those parameters.
    /// Those OIDs must match both input and output parameters.
    const Oid types[MAX_PARAMETERS_IN_QUERY];

    /// Short name of the query.
    const char* name;

    /// Text represenation of the actual query.
    const char* text;
};

TaggedStatement tagged_statements[] = {
    {PgSqlLeaseMgr::DELETE_LEASE4, 1,
        { 20 },
        "delete_lease4",
     "DELETE FROM lease4 WHERE address = $1"},
    {PgSqlLeaseMgr::DELETE_LEASE6, 1,
        { 1043 },
        "delete_lease6",
     "DELETE FROM lease6 WHERE address = $1"},
    {PgSqlLeaseMgr::GET_LEASE4_ADDR, 1,
        { 20 },
        "get_lease4_addr",
     "DECLARE get_lease4_addr CURSOR FOR "
     "SELECT address, hwaddr, client_id, "
     "valid_lifetime, extract(epoch from expire), subnet_id, fqdn_fwd, fqdn_rev, hostname "
     "FROM lease4 "
     "WHERE address = $1"},
    {PgSqlLeaseMgr::GET_LEASE4_CLIENTID, 1,
        { 17 },
        "get_lease4_clientid",
     "DECLARE get_lease4_clientid CURSOR FOR "
     "SELECT address, hwaddr, client_id, "
     "valid_lifetime, extract(epoch from expire), subnet_id, fqdn_fwd, fqdn_rev, hostname "
     "FROM lease4 "
     "WHERE client_id = $1"},
    {PgSqlLeaseMgr::GET_LEASE4_CLIENTID_SUBID, 2,
        { 17, 20 },
        "get_lease4_clientid_subid",
     "DECLARE get_lease4_clientid_subid CURSOR FOR "
     "SELECT address, hwaddr, client_id, "
     "valid_lifetime, extract(epoch from expire)::bigint, subnet_id, fqdn_fwd, fqdn_rev, hostname "
     "FROM lease4 "
     "WHERE client_id = $1 AND subnet_id = $2"},
    {PgSqlLeaseMgr::GET_LEASE4_HWADDR, 1,
         { 17 },
         "get_lease4_hwaddr",
     "DECLARE get_lease4_hwaddr CURSOR FOR "
     "SELECT address, hwaddr, client_id, "
     "valid_lifetime, extract(epoch from expire)::bigint, subnet_id, fqdn_fwd, fqdn_rev, hostname "
     "FROM lease4 "
     "WHERE hwaddr = $1"},
    {PgSqlLeaseMgr::GET_LEASE4_HWADDR_SUBID, 2,
         { 17, 20 },
         "get_lease4_hwaddr_subid",
     "DECLARE get_lease4_hwaddr_subid CURSOR FOR "
     "SELECT address, hwaddr, client_id, "
     "valid_lifetime, extract(epoch from expire)::bigint, subnet_id, fqdn_fwd, fqdn_rev, hostname "
     "FROM lease4 "
     "WHERE hwaddr = $1 AND subnet_id = $2"},
    {PgSqlLeaseMgr::GET_LEASE6_ADDR, 2,
        { 1043, 21 },
        "get_lease6_addr",
     "DECLARE get_lease6_addr CURSOR FOR "
     "SELECT address, duid, valid_lifetime, "
     "extract(epoch from expire)::bigint, subnet_id, pref_lifetime, "
     "lease_type, iaid, prefix_len, fqdn_fwd, fqdn_rev, hostname "
     "FROM lease6 "
     "WHERE address = $1 AND lease_type = $2"},
    {PgSqlLeaseMgr::GET_LEASE6_DUID_IAID, 3,
        { 17, 20, 21 },
        "get_lease6_duid_iaid",
     "DECLARE get_lease6_duid_iaid CURSOR FOR "
     "SELECT address, duid, valid_lifetime, "
     "extract(epoch from expire)::bigint, subnet_id, pref_lifetime, "
     "lease_type, iaid, prefix_len, fqdn_fwd, fqdn_rev, hostname "
     "FROM lease6 "
     "WHERE duid = $1 AND iaid = $2 AND lease_type = $3"},
    {PgSqlLeaseMgr::GET_LEASE6_DUID_IAID_SUBID, 4,
        { 21, 17, 20, 20 },
        "get_lease6_duid_iaid_subid",
     "DECLARE get_lease6_duid_iaid_subid CURSOR FOR "
     "SELECT address, duid, valid_lifetime, "
     "extract(epoch from expire)::bigint, subnet_id, pref_lifetime, "
     "lease_type, iaid, prefix_len, fqdn_fwd, fqdn_rev, hostname "
     "FROM lease6 "
     "WHERE lease_type = $1 AND duid = $2 AND iaid = $3 AND subnet_id = $4"},
    {PgSqlLeaseMgr::GET_VERSION, 0,
        { 0 },
     "get_version",
     "DECLARE get_version CURSOR FOR "
     "SELECT version, minor FROM schema_version"},
    {PgSqlLeaseMgr::INSERT_LEASE4, 9,
         { 20, 17, 17, 20, 1114, 20, 16, 16, 1043 },
         "insert_lease4",
     "INSERT INTO lease4(address, hwaddr, client_id, "
     "valid_lifetime, expire, subnet_id, fqdn_fwd, fqdn_rev, hostname) "
     "VALUES ($1, $2, $3, $4, $5, $6, $7, $8, $9)"},
    {PgSqlLeaseMgr::INSERT_LEASE6, 12,
        { 1043, 17, 20, 1114, 20, 20, 21, 20, 21, 16, 16, 1043 },
        "insert_lease6",
     "INSERT INTO lease6(address, duid, valid_lifetime, "
     "expire, subnet_id, pref_lifetime, "
     "lease_type, iaid, prefix_len, fqdn_fwd, fqdn_rev, hostname) "
     "VALUES ($1, $2, $3, $4, $5, $6, $7, $8, $9, $10, $11, $12)"},
    {PgSqlLeaseMgr::UPDATE_LEASE4, 10,
        { 20, 17, 17, 20, 1114, 20, 16, 16, 1043, 20 },
        "update_lease4",
     "UPDATE lease4 SET address = $1, hwaddr = $2, "
     "client_id = $3, valid_lifetime = $4, expire = $5, "
     "subnet_id = $6, fqdn_fwd = $7, fqdn_rev = $8, hostname = $9 "
     "WHERE address = $10"},
    {PgSqlLeaseMgr::UPDATE_LEASE6, 13,
        { 1043, 17, 20, 1114, 20, 20, 21, 20, 21, 16, 16, 1043, 1043 },
        "update_lease6",
     "UPDATE lease6 SET address = $1, duid = $2, "
     "valid_lifetime = $3, expire = $4, subnet_id = $5, "
     "pref_lifetime = $6, lease_type = $7, iaid = $8, "
     "prefix_len = $9, fqdn_fwd = $10, fqdn_rev = $11, hostname = $12 "
     "WHERE address = $13"},

    // End of list sentinel
    {PgSqlLeaseMgr::NUM_STATEMENTS, 0,  { 0 }, NULL, NULL}
};

};

namespace isc {
namespace dhcp {

/// @brief Auxiliary PostgreSQL exchange class
class PgSqlLeaseExchange {
protected:

    /// Converts time_t structure to a text representation in local time.
    ///
    /// The format of the output string is "%Y-%m-%d %H:%M:%S".  Database
    /// table columns using this value should be typed as TIMESTAMP WITH
    /// TIME ZONE. For such columns Postgres assumes input strings without
    /// timezones should be treated as in local time and are converted to UTC
    /// when stored.  Likewise, these columns are automatically adjusted
    /// upon retrieval unless fetched via "extract(epoch from <column>))".
    ///
    /// @param time_val timestamp to be converted
    /// @return std::string containing the stringified time
    std::string
    convertToDatabaseTime(const time_t& time_val) {
        struct tm tinfo;
        char buffer[20];
        localtime_r(&time_val, &tinfo);
        strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &tinfo);
        return (std::string(buffer));
    }

    /// Converts time stamp from the database to a time_t
    /// @param db_time_val timestamp to be converted.  This value
    /// is expected to be the number of seconds since the epoch
    /// expressed as base-10 integer string.
    time_t convertFromDatabaseTime(const std::string& db_time_val) {
        // Convert string time value to time_t
        istringstream tmp;
        time_t db_time_t;
        tmp.str(db_time_val);
        tmp >> db_time_t;
        return (db_time_t);
    }

    /// Converts Postgres text boolean representations to bool
    ///
    /// Allowed values are "t" or "f", or "" which is false.
    //  Any other will throw.
    /// @param value text value to be converted
    /// @throw BadValue if passed any value other than "t" or "f"
    bool stringToBool(char* value) {
        if (!value || !strlen(value)) {
            return (false);
        }
        switch (value[0]) {
        case 't':
            return (true);
        case 'f':
            return (false);
        default:
            isc_throw(BadValue, "Received " << value[0] << " as boolean. The "
                      " only accepted values are 't', 'f' or ''");
        }
    }

    /// Compiled statement bind parameters
    bindparams params;
};

/// @brief Represents a single Lease4 exchange
class PgSqlLease4Exchange : public PgSqlLeaseExchange {
    static const size_t LEASE_COLUMNS = 9;
public:

    /// Default constructor
    PgSqlLease4Exchange() : addr4_(0), hwaddr_length_(0), client_id_length_(0) {
        memset(hwaddr_buffer_, 0, sizeof(hwaddr_buffer_));
        memset(client_id_buffer_, 0, sizeof(client_id_buffer_));

        // Set the column names (for error messages)
        columns_[0] = "address";
        columns_[1] = "hwaddr";
        columns_[2] = "client_id";
        columns_[3] = "valid_lifetime";
        columns_[4] = "expire";
        columns_[5] = "subnet_id";
        columns_[6] = "fqdn_fwd";
        columns_[7] = "fqdn_rev";
        columns_[8] = "hostname";

        BOOST_STATIC_ASSERT(8 < LEASE_COLUMNS);

        params.reserve(LEASE_COLUMNS);
    }

    bindparams
    createBindForSend(const Lease4Ptr& lease) {
        lease_ = lease;
        params.clear();
        ostringstream tmp;

        tmp << static_cast<uint32_t>(lease_->addr_);
        params.push_back(PgSqlParam(tmp.str()));
        tmp.str("");

        // Although HWADDR object will always be there, it may be just an empty vector
        if (!lease_->hwaddr_.empty()) {
            if (lease->hwaddr_.size() > HWAddr::MAX_HWADDR_LEN) {
                isc_throw(DbOperationError, "Attempted to store Hardware address longer ("
                          << lease->hwaddr_.size() << " than allowed maximum of "
                          << HWAddr::MAX_HWADDR_LEN);
            }

            params.push_back(PgSqlParam(lease_->hwaddr_));
        } else {
            params.push_back(PgSqlParam());
        }

        if (lease_->client_id_) {
            params.push_back(PgSqlParam(lease_->client_id_->getClientId()));
        } else {
            params.push_back(PgSqlParam());
        }

        tmp << static_cast<unsigned long>(lease_->valid_lft_);
        params.push_back(PgSqlParam(tmp.str()));
        tmp.str("");

        time_t expire = lease_->valid_lft_ + lease_->cltt_;
        params.push_back(PgSqlParam(convertToDatabaseTime(expire)));

        tmp << static_cast<unsigned long>(lease_->subnet_id_);
        params.push_back(PgSqlParam(tmp.str()));

        params.push_back(PgSqlParam(lease_->fqdn_fwd_ ? "TRUE" : "FALSE"));
        params.push_back(PgSqlParam(lease_->fqdn_rev_ ? "TRUE" : "FALSE"));
        params.push_back(PgSqlParam(lease_->hostname_));

        return (params);
    }

    Lease4Ptr
    convertFromDatabase(PGresult *& r, int line) {
        const char* addr4_str = PQgetvalue(r, line, 0);
        unsigned char* hwaddr_str = PQunescapeBytea((const unsigned char *)
                                                    PQgetvalue(r, line, 1),
                                                    & hwaddr_length_);
        unsigned char* client_id_str = PQunescapeBytea((const unsigned char *)
                                                       PQgetvalue(r, line, 2),
                                                       & client_id_length_);
        const char* valid_lifetime_str = PQgetvalue(r, line, 3);
        const char* expire_str = PQgetvalue(r, line, 4);
        const char* subnet_id_str = PQgetvalue(r, line, 5);
        unsigned long valid_lifetime, subnet_id;

        istringstream tmp;
        tmp.str(addr4_str);
        tmp >> addr4_;
        tmp.str("");
        tmp.clear();

        memcpy(hwaddr_buffer_, hwaddr_str, hwaddr_length_);
        memcpy(client_id_buffer_, client_id_str, client_id_length_);

        PQfreemem(client_id_str);
        PQfreemem(hwaddr_str);

        tmp.str(valid_lifetime_str);
        tmp >> valid_lifetime;
        tmp.str("");
        tmp.clear();
        valid_lifetime_ = static_cast<uint32_t>(valid_lifetime);

        expire_ = convertFromDatabaseTime(expire_str);

        tmp.str(subnet_id_str);
        tmp >> subnet_id;
        subnet_id_ = static_cast<uint32_t>(subnet_id);

        time_t cltt = expire_ - valid_lifetime_;

        // Extract fqdn_fwd, fqdn_rev
        // boolean is represented as one of 3 possible strings:
        // "" (means NULL or not set), "t" (means true), "f" (means false)
        bool fwd = stringToBool(PQgetvalue(r, line, 6));
        bool rev = stringToBool(PQgetvalue(r, line, 7));

        // Extract hostname field
        string hostname(PQgetvalue(r, line, 8));

        return (Lease4Ptr(new Lease4(addr4_, hwaddr_buffer_, hwaddr_length_,
                                     client_id_buffer_, client_id_length_,
                                     valid_lifetime_, 0, 0, cltt, subnet_id_,
                                     fwd, rev, hostname)));
    }

private:
    uint32_t        addr4_;
    string     columns_[LEASE_COLUMNS];
    vector<uint8_t> hwaddr_;
    uint8_t         hwaddr_buffer_[HWAddr::MAX_HWADDR_LEN];
    uint8_t         client_id_buffer_[ClientId::MAX_CLIENT_ID_LEN];
    Lease4Ptr       lease_;
    time_t          expire_;
    uint32_t        subnet_id_;
    uint32_t        valid_lifetime_;
    unsigned long   hwaddr_length_;
    unsigned long   client_id_length_;
    string hostname_;
};

class PgSqlLease6Exchange : public PgSqlLeaseExchange {
    static const size_t LEASE_COLUMNS = 12;
public:
    PgSqlLease6Exchange() : duid_length_(0) {
        memset(duid_buffer_, 0, sizeof(duid_buffer_));
        // Set the column names (for error messages)
        columns_[0] = "address";
        columns_[1] = "duid";
        columns_[2] = "valid_lifetime";
        columns_[3] = "expire";
        columns_[4] = "subnet_id";
        columns_[5] = "pref_lifetime";
        columns_[6] = "lease_type";
        columns_[7] = "iaid";
        columns_[8] = "prefix_len";
        columns_[9] = "fqdn_fwd";
        columns_[10]= "fqdn_rev";
        columns_[11]= "hostname";
        BOOST_STATIC_ASSERT(11 < LEASE_COLUMNS);

        params.reserve(LEASE_COLUMNS);
    }

    bindparams
    createBindForSend(const Lease6Ptr& lease) {
        lease_ = lease;
        params.clear();
        ostringstream tmp;

        params.push_back(PgSqlParam(lease_->addr_.toText()));

        params.push_back(PgSqlParam(lease_->duid_->getDuid()));

        tmp << static_cast<unsigned long>(lease_->valid_lft_);
        params.push_back(PgSqlParam(tmp.str()));
        tmp.str("");
        tmp.clear();

        time_t expire = lease_->valid_lft_ + lease_->cltt_;
        params.push_back(PgSqlParam(convertToDatabaseTime(expire)));

        tmp << static_cast<unsigned long>(lease_->subnet_id_);
        params.push_back(PgSqlParam(tmp.str()));
        tmp.str("");
        tmp.clear();

        tmp << static_cast<unsigned long>(lease_->preferred_lft_);
        params.push_back(PgSqlParam(tmp.str()));
        tmp.str("");
        tmp.clear();

        tmp << static_cast<unsigned int>(lease_->type_);
        params.push_back(PgSqlParam(tmp.str()));
        tmp.str("");
        tmp.clear();

        tmp << static_cast<unsigned long>(lease_->iaid_);
        params.push_back(PgSqlParam(tmp.str()));
        tmp.str("");
        tmp.clear();

        tmp << static_cast<unsigned int>(lease_->prefixlen_);
        params.push_back(PgSqlParam(tmp.str()));

        params.push_back(PgSqlParam(lease_->fqdn_fwd_ ? "TRUE" : "FALSE"));
        params.push_back(PgSqlParam(lease_->fqdn_rev_ ? "TRUE" : "FALSE"));
        params.push_back(PgSqlParam(lease_->hostname_));

        return (params);
    }

    Lease6Ptr
    convertFromDatabase(PGresult * r, int line) {
        const char* addr6_str = PQgetvalue(r, line, 0);
        unsigned char* duid_str =  PQunescapeBytea((const unsigned char *)
                                                   PQgetvalue(r, line, 1),
                                                   & duid_length_);
        const char* valid_lifetime_str =  PQgetvalue(r, line, 2);
        const char* expire_str = PQgetvalue(r, line, 3);
        const char* subnet_id_str = PQgetvalue(r, line, 4);
        const char* pref_lifetime_str = PQgetvalue(r, line, 5);
        const char* lease_type_str = PQgetvalue(r, line, 6);
        const char* iaid_str = PQgetvalue(r, line, 7);
        const char* prefixlen_str = PQgetvalue(r, line, 8);
        unsigned int lease_type, prefixlen;
        unsigned long valid_lifetime, subnet_id, pref_lifetime, iaid;

        istringstream tmp;

        addr6_ = addr6_str;
        isc::asiolink::IOAddress addr(addr6_);

        memcpy(duid_buffer_, duid_str, duid_length_);

        PQfreemem(duid_str);

        tmp.str(valid_lifetime_str);
        tmp >> valid_lifetime;
        tmp.str("");
        tmp.clear();
        valid_lifetime_ = static_cast<uint32_t>(valid_lifetime);

        expire_ = convertFromDatabaseTime(expire_str);

        tmp.str(subnet_id_str);
        tmp >> subnet_id;
        tmp.str("");
        tmp.clear();
        subnet_id_ = static_cast<uint32_t>(subnet_id);

        tmp.str(pref_lifetime_str);
        tmp >> pref_lifetime;
        tmp.str("");
        tmp.clear();
        pref_lifetime_ = static_cast<uint32_t>(pref_lifetime);

        tmp.str(lease_type_str);
        tmp >> lease_type;
        tmp.str("");
        tmp.clear();

        tmp.str(iaid_str);
        tmp >> iaid;
        tmp.str("");
        tmp.clear();
        iaid_ = static_cast<uint32_t>(iaid);

        tmp.str(prefixlen_str);
        tmp >> prefixlen;
        prefixlen_ = static_cast<uint8_t>(prefixlen);

        Lease6::Type type = Lease6::TYPE_NA;
        switch (lease_type) {
        case Lease6::TYPE_NA:
            type = Lease6::TYPE_NA;
            break;

        case Lease6::TYPE_TA:
            type = Lease6::TYPE_TA;
            break;

        case Lease6::TYPE_PD:
            type = Lease6::TYPE_PD;
            break;

        default:
            isc_throw(BadValue, "invalid lease type returned (" <<
                      lease_type_ << ") for lease with address " <<
                      addr6_ << ". Only 0, 1, or 2 are allowed.");
        }

        // Extract fqdn_fwd, fqdn_rev
        // boolean is represented as one of 3 possible strings:
        // "" (means NULL or not set), "t" (means true), "f" (means false)
        bool fwd = stringToBool(PQgetvalue(r, line, 9));
        bool rev = stringToBool(PQgetvalue(r, line, 10));

        // Extract hostname field
        string hostname(PQgetvalue(r, line, 11));

        // Set up DUID,
        DuidPtr duid_ptr(new DUID(duid_buffer_, duid_length_));

        Lease6Ptr result(new Lease6(type, addr, duid_ptr, iaid_,
                                    pref_lifetime_, valid_lifetime_, 0, 0,
                                    subnet_id_, fwd, rev, hostname, prefixlen_));

        time_t cltt = expire_ - valid_lifetime_;
        result->cltt_ = cltt;

        return (result);
    }

private:
    string     addr6_;
    string     columns_[LEASE_COLUMNS];
    time_t          expire_;
    vector<uint8_t> duid_;
    uint8_t         duid_buffer_[DUID::MAX_DUID_LEN];
    uint32_t        iaid_;
    Lease6Ptr       lease_;
    uint8_t         lease_type_;
    uint8_t         prefixlen_;
    uint32_t        pref_lifetime_;
    uint32_t        subnet_id_;
    uint32_t        valid_lifetime_;
    unsigned long   duid_length_;
};

PgSqlLeaseMgr::PgSqlLeaseMgr(const LeaseMgr::ParameterMap& parameters)
    : LeaseMgr(parameters){
    status = NULL;
    openDatabase();
    prepareStatements();

    exchange4_.reset(new PgSqlLease4Exchange());
    exchange6_.reset(new PgSqlLease6Exchange());
}

PgSqlLeaseMgr::~PgSqlLeaseMgr() {
    if (status) {
        // Attempt to deallocate prepared queries set previously with DEALLOCATE query
        // No internal libpq function for that, no errors checking as well
        /// @todo Can't this be done as a single string with list of statements?
        for(int i = 0; tagged_statements[i].text != NULL; ++ i) {
            string deallocate = "DEALLOCATE \"";
            deallocate += tagged_statements[i].name;
            deallocate += "\"";
            PGresult* r = PQexec(status, deallocate.c_str());
            PQclear(r);
        }

        PQfinish(status);
    }
}

void PgSqlLeaseMgr::prepareStatements() {
    statements_.clear();
    statements_.resize(NUM_STATEMENTS, PgSqlStatementBind());

    for(int i = 0; tagged_statements[i].text != NULL; ++ i) {
        /// @todo why do we bother with select here?  If they are already
        /// defined we should let the error occur because we only do this
        /// once per open anyway.
        string checkstatement = "SELECT * FROM pg_prepared_statements "
                                     "WHERE name = '";
        checkstatement += tagged_statements[i].name;
        checkstatement += "'";

        PGresult* r = PQexec(status, checkstatement.c_str());

        if(!PQntuples(r)) {
            PQclear(r);
            r = PQexec(status, "BEGIN");
            PQclear(r);
            // Prepare all statements queries with all known fields datatype
            // No need to remind them when called
            r = PQprepare(status, tagged_statements[i].name,
                                       tagged_statements[i].text,
                                       tagged_statements[i].nbparams,
                                       tagged_statements[i].types);

            if(PQresultStatus(r) != PGRES_COMMAND_OK) {
                PQclear(r);
                isc_throw(DbOperationError, "unable to prepare PostgreSQL statement <" <<
                          tagged_statements[i].text << ">, reason: " << PQerrorMessage(status));
            }

            PQclear(r);

            r = PQexec(status, "END");
            PQclear(r);

            statements_[i].stmt_name = tagged_statements[i].name;
            statements_[i].stmt_nbparams = tagged_statements[i].nbparams;
        } else {
                PQclear(r);
            }
    }
}

void
PgSqlLeaseMgr::openDatabase() {
    string dbconnparameters;
    string shost = "localhost";
    try {
        shost = getParameter("host");
    } catch(...) {
        // No host. Fine, we'll use "localhost"
    }

    dbconnparameters += "host = '" + shost + "'" ;

    string suser;
    try {
        suser = getParameter("user");
        dbconnparameters += " user = '" + suser + "'";
    } catch(...) {
        // No user. Fine, we'll use NULL
    }

    string spassword;
    try {
        spassword = getParameter("password");
        dbconnparameters += " password = '" + spassword + "'";
    } catch(...) {
        // No password. Fine, we'll use NULL
    }

    string sname;
    try {
        sname= getParameter("name");
        dbconnparameters += " dbname = '" + sname + "'";
    } catch(...) {
        // No database name.  Throw a "NoName" exception
        isc_throw(NoDatabaseName, "must specified a name for the database");
    }

    status = PQconnectdb(dbconnparameters.c_str());
    if (status == NULL) {
        isc_throw(DbOpenError, "could not allocate connection object");
    }

    if (PQstatus(status) != CONNECTION_OK) {
        // If we have a connection object, we have to call finish
        // to release it, but grab the error message first.
        std::string error_message = PQerrorMessage(status);
        PQfinish(status);
        isc_throw(DbOpenError, error_message);
    }
}

bool
PgSqlLeaseMgr::addLeaseCommon(StatementIndex stindex,
                              bindparams& params) {

    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_PGSQL_ADD_ADDR4).arg(statements_[stindex].stmt_name);

    vector<const char *> out_values;
    vector<int> out_lengths;
    vector<int> out_formats;
    convertToQuery(params, out_values, out_lengths, out_formats);

    PGresult * r = PQexecPrepared(status, statements_[stindex].stmt_name,
                                  statements_[stindex].stmt_nbparams,
                                  &out_values[0], &out_lengths[0], &out_formats[0], 0);

    int s = PQresultStatus(r);
    if (s != PGRES_COMMAND_OK) {
        const char * errorMsg = PQerrorMessage(status);
        PQclear(r);

        if(!strncmp(errorMsg, "ERROR:  duplicate key",
           sizeof("ERROR:  duplicate key") - 1)) {
            return (false);
        }

        isc_throw(DbOperationError, "unable to INSERT for <" <<
                  statements_[stindex].stmt_name << ">, " <<
                  errorMsg);
    }

    PQclear(r);

    return (true);
}

bool
PgSqlLeaseMgr::addLease(const Lease4Ptr& lease) {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_PGSQL_ADD_ADDR4).arg(lease->addr_.toText());
    bindparams params = exchange4_->createBindForSend(lease);

    return (addLeaseCommon(INSERT_LEASE4, params));
}

bool
PgSqlLeaseMgr::addLease(const Lease6Ptr& lease) {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_PGSQL_ADD_ADDR6).arg(lease->addr_.toText());
    bindparams params = exchange6_->createBindForSend(lease);

    return (addLeaseCommon(INSERT_LEASE6, params));
}

template <typename Exchange, typename LeaseCollection>
void PgSqlLeaseMgr::getLeaseCollection(StatementIndex stindex,
                                       bindparams & params,
                                       Exchange& exchange,
                                       LeaseCollection& result,
                                       bool single) const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_PGSQL_GET_ADDR4).arg(statements_[stindex].stmt_name);

    vector<const char *> out_values;
    vector<int> out_lengths;
    vector<int> out_formats;
    convertToQuery(params, out_values, out_lengths, out_formats);
    PGresult* r = PQexec(status, "BEGIN");
    PQclear(r);

    r = PQexecPrepared(status, statements_[stindex].stmt_name,
                       statements_[stindex].stmt_nbparams, &out_values[0],
                       &out_lengths[0], &out_formats[0], 0);

    checkError(r, stindex, "unable to bind WHERE clause parameter");
    PQclear(r);

    string fetchall = "FETCH ALL in ";
    fetchall += statements_[stindex].stmt_name;

    r = PQexec(status, fetchall.c_str());
    checkError(r, stindex, "unable to FETCH ALL");

    int lines = PQntuples(r);

    if(single && lines > 1) {
        PQclear(r);
        r = PQexec(status, "END");
        PQclear(r);
        isc_throw(MultipleRecords, "multiple records were found in the "
                      "database where only one was expected for query "
                      << statements_[stindex].stmt_name);
    }

    for(int i = 0; i < lines; ++ i) {
        result.push_back(exchange->convertFromDatabase(r, i));
    }

    PQclear(r);

    string closecursor = "CLOSE ";
    closecursor += statements_[stindex].stmt_name;
    r = PQexec(status, closecursor.c_str());
    PQclear(r);

    r = PQexec(status, "END");
    PQclear(r);
}

void
PgSqlLeaseMgr::getLease(StatementIndex stindex, bindparams & params,
                             Lease4Ptr& result) const {
    // Create appropriate collection object and get all leases matching
    // the selection criteria.  The "single" paraeter is true to indicate
    // that the called method should throw an exception if multiple
    // matching records are found: this particular method is called when only
    // one or zero matches is expected.
    Lease4Collection collection;
    getLeaseCollection(stindex, params, exchange4_, collection, true);

    // Return single record if present, else clear the lease.
    if (collection.empty()) {
        result.reset();
    } else {
        result = *collection.begin();
    }
}

void
PgSqlLeaseMgr::getLease(StatementIndex stindex, bindparams & params,
                             Lease6Ptr& result) const {
    // Create appropriate collection object and get all leases matching
    // the selection criteria.  The "single" paraeter is true to indicate
    // that the called method should throw an exception if multiple
    // matching records are found: this particular method is called when only
    // one or zero matches is expected.
    Lease6Collection collection;
    getLeaseCollection(stindex, params, exchange6_, collection, true);

    // Return single record if present, else clear the lease.
    if (collection.empty()) {
        result.reset();
    } else {
        result = *collection.begin();
    }
}

Lease4Ptr
PgSqlLeaseMgr::getLease4(const isc::asiolink::IOAddress& addr) const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_PGSQL_GET_ADDR4).arg(addr.toText());

    // Set up the WHERE clause value
    bindparams inparams;
    ostringstream tmp;

    tmp << static_cast<uint32_t>(addr);
    inparams.push_back(PgSqlParam(tmp.str()));

    // Get the data
    Lease4Ptr result;
    getLease(GET_LEASE4_ADDR, inparams, result);

    return (result);
}

Lease4Collection
PgSqlLeaseMgr::getLease4(const HWAddr& hwaddr) const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_PGSQL_GET_HWADDR).arg(hwaddr.toText());

    // Set up the WHERE clause value
    bindparams inparams;

    if (!hwaddr.hwaddr_.empty()) {
        inparams.push_back(PgSqlParam(hwaddr.hwaddr_));
    } else {
        inparams.push_back(PgSqlParam());
    }

    // Get the data
    Lease4Collection result;
    getLeaseCollection(GET_LEASE4_HWADDR, inparams, result);

    return (result);
}

Lease4Ptr
PgSqlLeaseMgr::getLease4(const HWAddr& hwaddr, SubnetID subnet_id) const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_PGSQL_GET_SUBID_HWADDR)
        .arg(subnet_id).arg(hwaddr.toText());

    // Set up the WHERE clause value
    bindparams inparams;
    ostringstream tmp;

    if (!hwaddr.hwaddr_.empty()) {
        inparams.push_back(PgSqlParam(hwaddr.hwaddr_));
    } else {
        inparams.push_back(PgSqlParam());
    }

    tmp << static_cast<unsigned long>(subnet_id);
    inparams.push_back(PgSqlParam(tmp.str()));

    // Get the data
    Lease4Ptr result;
    getLease(GET_LEASE4_HWADDR_SUBID, inparams, result);

    return (result);
}

Lease4Collection
PgSqlLeaseMgr::getLease4(const ClientId& clientid) const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_PGSQL_GET_CLIENTID).arg(clientid.toText());

    // Set up the WHERE clause value
    bindparams inparams;

    // CLIENT_ID
    inparams.push_back(PgSqlParam(clientid.getClientId()));

    // Get the data
    Lease4Collection result;
    getLeaseCollection(GET_LEASE4_CLIENTID, inparams, result);

    return (result);
}

Lease4Ptr
PgSqlLeaseMgr::getLease4(const ClientId& clientid, SubnetID subnet_id) const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_PGSQL_GET_SUBID_CLIENTID)
              .arg(subnet_id).arg(clientid.toText());

    // Set up the WHERE clause value
    bindparams inparams;
    ostringstream tmp;

    // CLIENT_ID
    inparams.push_back(PgSqlParam(clientid.getClientId()));

    tmp << static_cast<unsigned long>(subnet_id);
    inparams.push_back(PgSqlParam(tmp.str()));

    // Get the data
    Lease4Ptr result;
    getLease(GET_LEASE4_CLIENTID_SUBID, inparams, result);

    return (result);
}

Lease4Ptr
PgSqlLeaseMgr::getLease4(const ClientId& /*client_id*/, const HWAddr& /*hwaddr*/,
                         SubnetID /*subnet_id*/) const {
    /// @todo

    Lease4Ptr result;
    return (result);
}

Lease6Ptr
PgSqlLeaseMgr::getLease6(Lease::Type lease_type,
                         const isc::asiolink::IOAddress& addr) const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_PGSQL_GET_ADDR6)
        .arg(addr.toText()).arg(lease_type);

    // Set up the WHERE clause value
    bindparams inparams;
    ostringstream tmp;

    // ADDRESS
    inparams.push_back(PgSqlParam(addr.toText()));

    // LEASE_TYPE
    tmp << static_cast<uint16_t>(lease_type);
    inparams.push_back(PgSqlParam(tmp.str()));

    // ... and get the data
    Lease6Ptr result;
    getLease(GET_LEASE6_ADDR, inparams, result);

    return (result);
}

Lease6Collection
PgSqlLeaseMgr::getLeases6(Lease::Type type, const DUID& duid, uint32_t iaid) const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_PGSQL_GET_IAID_DUID)
        .arg(iaid).arg(duid.toText()).arg(type);

    // Set up the WHERE clause value
    bindparams inparams;
    ostringstream tmp;

    // DUID
    inparams.push_back(PgSqlParam(duid.getDuid()));

    // IAID
    tmp << static_cast<unsigned long>(iaid);
    inparams.push_back(PgSqlParam(tmp.str()));
    tmp.str("");
    tmp.clear();

    // LEASE_TYPE
    tmp << static_cast<uint16_t>(type);
    inparams.push_back(PgSqlParam(tmp.str()));

    // ... and get the data
    Lease6Collection result;
    getLeaseCollection(GET_LEASE6_DUID_IAID, inparams, result);

    return (result);
}

Lease6Collection
PgSqlLeaseMgr::getLeases6(Lease::Type lease_type, const DUID& duid, uint32_t iaid,
                          SubnetID subnet_id) const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_MYSQL_GET_IAID_SUBID_DUID)
        .arg(iaid).arg(subnet_id).arg(duid.toText()).arg(lease_type);

    // Set up the WHERE clause value
    bindparams inparams;
    ostringstream tmp;

    // LEASE_TYPE
    tmp << static_cast<uint16_t>(lease_type);
    inparams.push_back(PgSqlParam(tmp.str()));
    tmp.str("");
    tmp.clear();

    // DUID
    inparams.push_back(PgSqlParam(duid.getDuid()));

    // IAID
    tmp << static_cast<unsigned long>(iaid);
    inparams.push_back(PgSqlParam(tmp.str()));
    tmp.str("");
    tmp.clear();

    // Subnet ID
    tmp << static_cast<unsigned long>(subnet_id);
    inparams.push_back(PgSqlParam(tmp.str()));
    tmp.str("");
    tmp.clear();

    // ... and get the data
    Lease6Collection result;
    getLeaseCollection(GET_LEASE6_DUID_IAID_SUBID, inparams, result);

    return (result);
}

template <typename LeasePtr>
void
PgSqlLeaseMgr::updateLeaseCommon(StatementIndex stindex, bindparams & params,
                                 const LeasePtr& lease) {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_PGSQL_ADD_ADDR4).arg(statements_[stindex].stmt_name);

    vector<const char *> params_;
    vector<int> lengths_;
    vector<int> formats_;
    convertToQuery(params, params_, lengths_, formats_);

    PGresult * r = PQexecPrepared(status, statements_[stindex].stmt_name,
                                  statements_[stindex].stmt_nbparams,
                                  &params_[0], &lengths_[0], &formats_[0], 0);
    checkError(r, stindex, "unable to bind UPDATE parameters");
    int affected_rows = boost::lexical_cast<int>(PQcmdTuples(r));

    PQclear(r);

    if (!affected_rows) {
        isc_throw(NoSuchLease, "unable to update lease for address " <<
                  lease->addr_.toText() << " as it does not exist");
    } else if (affected_rows > 1) {
        // Should not happen - primary key constraint should only have selected
        // one row.
        isc_throw(DbOperationError, "apparently updated more than one lease "
                  "that had the address " << lease->addr_.toText());
    }
}

void
PgSqlLeaseMgr::updateLease4(const Lease4Ptr& lease) {
    const StatementIndex stindex = UPDATE_LEASE4;

    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_PGSQL_UPDATE_ADDR4).arg(lease->addr_.toText());

    // Create the MYSQL_BIND array for the data being updated
    ostringstream tmp;
    bindparams params = exchange4_->createBindForSend(lease);

    // Set up the WHERE clause and append it to the MYSQL_BIND array
    tmp << static_cast<uint32_t>(lease->addr_);
    params.push_back(PgSqlParam(tmp.str()));

    // Drop to common update code
    updateLeaseCommon(stindex, params, lease);
}

void
PgSqlLeaseMgr::updateLease6(const Lease6Ptr& lease) {
    const StatementIndex stindex = UPDATE_LEASE6;

    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_PGSQL_UPDATE_ADDR6).arg(lease->addr_.toText());

    // Create the MYSQL_BIND array for the data being updated
    bindparams params = exchange6_->createBindForSend(lease);

    // Set up the WHERE clause and append it to the MYSQL_BIND array
    params.push_back(PgSqlParam(lease->addr_.toText()));

    // Drop to common update code
    updateLeaseCommon(stindex, params, lease);
}

bool
PgSqlLeaseMgr::deleteLeaseCommon(StatementIndex stindex, bindparams & params) {
    vector<const char *> params_;
    vector<int> lengths_;
    vector<int> formats_;
    convertToQuery(params, params_, lengths_, formats_);

    PGresult * r = PQexecPrepared(status, statements_[stindex].stmt_name,
                                  statements_[stindex].stmt_nbparams,
                                  &params_[0], &lengths_[0], &formats_[0], 0);
    checkError(r, stindex, "unable to bind WHERE clause parameter");
    int affected_rows = boost::lexical_cast<int>(PQcmdTuples(r));
    PQclear(r);

    return (affected_rows > 0);
}

bool
PgSqlLeaseMgr::deleteLease(const isc::asiolink::IOAddress& addr) {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_PGSQL_DELETE_ADDR).arg(addr.toText());

    // Set up the WHERE clause value
    bindparams inparams;

    if (addr.isV4()) {
        ostringstream tmp;
        tmp << static_cast<uint32_t>(addr);
        inparams.push_back(PgSqlParam(tmp.str()));
        return (deleteLeaseCommon(DELETE_LEASE4, inparams));
    }

    inparams.push_back(PgSqlParam(addr.toText()));
    return (deleteLeaseCommon(DELETE_LEASE6, inparams));
}

string
PgSqlLeaseMgr::getName() const {
    string name = "";
    try {
        name = getParameter("name");
    } catch (...) {
        // Return an empty name
    }
    return (name);
}

void
PgSqlLeaseMgr::checkError(PGresult* r, StatementIndex index,
                          const char* what) const {
    int s = PQresultStatus(r);
    if (s != PGRES_COMMAND_OK && s != PGRES_TUPLES_OK) {
        PQclear(r);

        isc_throw(DbOperationError, what << " for <" <<
                  statements_[index].stmt_name << ">, " <<
                  PQerrorMessage(status));
    }
}

inline void
PgSqlLeaseMgr::convertToQuery(const bindparams& params,
                              std::vector<const char *>& out_values,
                              std::vector<int>& out_lengths,
                              std::vector<int>& out_formats) const {
    out_values.reserve(params.size());
    out_lengths.reserve(params.size());
    out_formats.reserve(params.size());

    for(bindparams::const_iterator it = params.begin(); it != params.end();
        ++it) {
        out_values.push_back((* it).value.c_str());
        out_lengths.push_back((* it).binarylen);
        out_formats.push_back((* it).isbinary);
    }
}

string
PgSqlLeaseMgr::getDescription() const {
    return (string("PostgreSQL Database"));
}

pair<uint32_t, uint32_t>
PgSqlLeaseMgr::getVersion() const {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_PGSQL_GET_VERSION);

    PGresult* r = PQexec(status, "BEGIN");
    PQclear(r);

    r = PQexecPrepared(status, "get_version", 0, NULL, NULL, NULL, 0);

    PQclear(r);

    r = PQexec(status, "FETCH ALL in get_version");

    const char* version_str = PQgetvalue(r, 0, 0);
    const char* minor_str = PQgetvalue(r, 0, 1);

    istringstream tmp;

    uint32_t version;
    tmp.str(version_str);
    tmp >> version;
    tmp.str("");
    tmp.clear();

    uint32_t minor;
    tmp.str(minor_str);
    tmp >> minor;

    PQclear(r);
    r = PQexec(status, "CLOSE get_version");
    PQclear(r);

    r = PQexec(status, "END");
    PQclear(r);

    return make_pair<uint32_t, uint32_t>(version, minor);
}

void
PgSqlLeaseMgr::commit() {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_MYSQL_COMMIT);
    PGresult * r = PQexec(status, "COMMIT");
    if (PQresultStatus(r) != PGRES_COMMAND_OK) {
        isc_throw(DbOperationError, "commit failed: " << PQerrorMessage(status));
    }

    PQclear(r);
}

void
PgSqlLeaseMgr::rollback() {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_MYSQL_ROLLBACK);
    PGresult * r = PQexec(status, "ROLLBACK");
    if (PQresultStatus(r) != PGRES_COMMAND_OK) {
        isc_throw(DbOperationError, "rollback failed: " << PQerrorMessage(status));
    }

    PQclear(r);
}

}; // end of isc::dhcp namespace
}; // end of isc namespace
