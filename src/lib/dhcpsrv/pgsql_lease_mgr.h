// Copyright (C) 2013-2014 Internet Systems Consortium, Inc. ("ISC")
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

#ifndef PGSQL_LEASE_MGR_H
#define PGSQL_LEASE_MGR_H

#include <dhcp/hwaddr.h>
#include <dhcpsrv/lease_mgr.h>

#include <boost/scoped_ptr.hpp>
#include <boost/utility.hpp>
#include <libpq-fe.h>

namespace isc {
namespace dhcp {

struct PgSqlParam {
    std::string value;
    int isbinary;
    int binarylen;
};

typedef std::vector<PgSqlParam> bindparams;

struct PgSqlStatementBind {
    const char * stmt_name;
    int stmt_nbparams;
};

class PgSqlLease4Exchange;
class PgSqlLease6Exchange;

const uint32_t PG_CURRENT_VERSION = 1;
const uint32_t PG_CURRENT_MINOR = 0;

class PgSqlLeaseMgr : public LeaseMgr {
public:
    PgSqlLeaseMgr(const ParameterMap& parameters);
    virtual ~PgSqlLeaseMgr();
    virtual bool addLease(const Lease4Ptr& lease);
    virtual bool addLease(const Lease6Ptr& lease);

    virtual Lease4Ptr getLease4(const isc::asiolink::IOAddress& addr) const;
    virtual Lease4Collection getLease4(const isc::dhcp::HWAddr& hwaddr) const;
    virtual Lease4Ptr getLease4(const isc::dhcp::HWAddr& hwaddr,
                                SubnetID subnet_id) const;
    virtual Lease4Collection getLease4(const ClientId& clientid) const;
    virtual Lease4Ptr getLease4(const ClientId& client_id, const HWAddr& hwaddr,
                                SubnetID subnet_id) const;
    virtual Lease4Ptr getLease4(const ClientId& clientid,
                                SubnetID subnet_id) const;

    virtual Lease6Ptr getLease6(Lease::Type type,
                                const isc::asiolink::IOAddress& addr) const;
    virtual Lease6Collection getLeases6(Lease::Type type, const DUID& duid,
                                       uint32_t iaid) const;
    virtual Lease6Collection getLeases6(Lease::Type type, const DUID& duid,
                                        uint32_t iaid, SubnetID subnet_id) const;

    virtual void updateLease4(const Lease4Ptr& lease4);
    virtual void updateLease6(const Lease6Ptr& lease6);
    virtual bool deleteLease(const isc::asiolink::IOAddress& addr);
    virtual std::string getType() const {
        return (std::string("postgresql"));
    }
    virtual std::string getName() const;
    virtual std::string getDescription() const;
    virtual std::pair<uint32_t, uint32_t> getVersion() const;
    virtual void commit();
    virtual void rollback();
    enum StatementIndex {
        DELETE_LEASE4,              // Delete from lease4 by address
        DELETE_LEASE6,              // Delete from lease6 by address
        GET_LEASE4_ADDR,            // Get lease4 by address
        GET_LEASE4_CLIENTID,        // Get lease4 by client ID
        GET_LEASE4_CLIENTID_SUBID,  // Get lease4 by client ID & subnet ID
        GET_LEASE4_HWADDR,          // Get lease4 by HW address
        GET_LEASE4_HWADDR_SUBID,    // Get lease4 by HW address & subnet ID
        GET_LEASE6_ADDR,            // Get lease6 by address
        GET_LEASE6_DUID_IAID,       // Get lease6 by DUID and IAID
        GET_LEASE6_DUID_IAID_SUBID, // Get lease6 by DUID, IAID and subnet ID
        GET_VERSION,                // Obtain version number
        INSERT_LEASE4,              // Add entry to lease4 table
        INSERT_LEASE6,              // Add entry to lease6 table
        UPDATE_LEASE4,              // Update a Lease4 entry
        UPDATE_LEASE6,              // Update a Lease6 entry
        NUM_STATEMENTS              // Number of statements
    };
private:
    void prepareStatements();
    void openDatabase();
    bool addLeaseCommon(StatementIndex stindex, bindparams & params);
    template <typename Exchange, typename LeaseCollection>
    void getLeaseCollection(StatementIndex stindex, bindparams & params,
                            Exchange& exchange, LeaseCollection& result,
                            bool single = false) const;
    void getLeaseCollection(StatementIndex stindex, bindparams & params,
                            Lease4Collection& result) const {
        getLeaseCollection(stindex, params, exchange4_, result);
    }
    void getLeaseCollection(StatementIndex stindex, bindparams & params,
                            Lease6Collection& result) const {
        getLeaseCollection(stindex, params, exchange6_, result);
    }
    inline void checkError(PGresult * r, StatementIndex index,
                           const char* what) const {
        int s = PQresultStatus(r);
        if (s != PGRES_COMMAND_OK && s != PGRES_TUPLES_OK) {
            PQclear(r);

            isc_throw(DbOperationError, what << " for <" <<
                      statements_[index].stmt_name << ">, " <<
                      PQerrorMessage(status));
        }
    }
    inline void convertToQuery(bindparams & params,
                               std::vector<const char *>& params_,
                               std::vector<int>& lengths_,
                               std::vector<int>& formats_) const {
        params_.reserve(params.size());
        lengths_.reserve(params.size());
        formats_.reserve(params.size());

        for(bindparams::const_iterator it = params.begin(); it != params.end();
                ++ it) {
            params_.push_back((* it).value.c_str());
            lengths_.push_back((* it).binarylen);
            formats_.push_back((* it).isbinary);
        }
    }
    void getLease(StatementIndex stindex, bindparams & params,
                  Lease4Ptr& result) const;
    void getLease(StatementIndex stindex, bindparams & params,
                  Lease6Ptr& result) const;
    template <typename LeasePtr>
    void updateLeaseCommon(StatementIndex stindex, bindparams & params,
                           const LeasePtr& lease);
    bool deleteLeaseCommon(StatementIndex stindex, bindparams & params);

    boost::scoped_ptr<PgSqlLease4Exchange> exchange4_;
    boost::scoped_ptr<PgSqlLease6Exchange> exchange6_;
    std::vector<PgSqlStatementBind> statements_;
    PGconn * status;
};

}; // end of isc::dhcp namespace
}; // end of isc namespace

#endif // PGSQL_LEASE_MGR_H
