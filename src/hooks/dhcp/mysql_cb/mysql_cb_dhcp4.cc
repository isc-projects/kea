// Copyright (C) 2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <database/db_exceptions.h>
#include <mysql_cb_dhcp4.h>
#include <mysql/mysql_connection.h>
#include <mysql.h>
#include <mysqld_error.h>
#include <array>
#include <utility>
#include <vector>

using namespace isc::db;

namespace {

}

namespace isc {
namespace dhcp {

/// @brief Implementation of the MySQL Configuration Backend.
class MySqlConfigBackendDHCPv4Impl {
public:

    /// @brief Statement tags.
    ///
    /// The contents of the enum are indexes into the list of SQL statements.
    /// It is assumed that the order is such that the indices of statements
    /// reading the database are less than those of statements modifying the
    /// database.
    enum StatementIndex {
        GET_SUBNET4_ID,
        NUM_STATEMENTS
    };

    /// @brief Constructor.
    ///
    /// @param parameters A data structure relating keywords and values
    /// concerned with the database.
    MySqlConfigBackendDHCPv4Impl(const DatabaseConnection::ParameterMap& parameters);

    /// @brief Destructor.
    ~MySqlConfigBackendDHCPv4Impl();

    /// @brief Represents connection to the MySQL database.
    MySqlConnection conn_;
};

/// @brief Array of tagged statements.
typedef std::array<TaggedStatement, MySqlConfigBackendDHCPv4Impl::NUM_STATEMENTS>
TaggedStatementArray;

/// @brief Prepared MySQL statements used by the backend to insert and
/// retrieve data from the database.
TaggedStatementArray tagged_statements = { {
    { MySqlConfigBackendDHCPv4Impl::GET_SUBNET4_ID,
      "SELECT hostname FROM hosts WHERE dhcp4_subnet_id = ?" }
}
};

MySqlConfigBackendDHCPv4Impl::
MySqlConfigBackendDHCPv4Impl(const DatabaseConnection::ParameterMap& parameters)
    : conn_(parameters) {
    // Open the database.
    conn_.openDatabase();

    // Test schema version before we try to prepare statements.
    std::pair<uint32_t, uint32_t> code_version(MYSQL_SCHEMA_VERSION_MAJOR,
                                               MYSQL_SCHEMA_VERSION_MINOR);
/*    std::pair<uint32_t, uint32_t> db_version = getVersion();
    if (code_version != db_version) {
        isc_throw(DbOpenError, "MySQL schema version mismatch: need version: "
                  << code_version.first << "." << code_version.second
                  << " found version:  " << db_version.first << "."
                  << db_version.second);
    } */

    // Enable autocommit. In case transaction is explicitly used, this
    // setting will be overwritten for the transaction. However, there are
    // cases when lack of autocommit could cause transactions to hang
    // until commit or rollback is explicitly called. This already
    // caused issues for some unit tests which were unable to cleanup
    // the database after the test because of pending transactions.
    // Use of autocommit will eliminate this problem.
    my_bool result = mysql_autocommit(conn_.mysql_, 1);
    if (result != 0) {
        isc_throw(DbOperationError, mysql_error(conn_.mysql_));
    }

    // Prepare query statements. Those are will be only used to retrieve
    // information from the database, so they can be used even if the
    // database is read only for the current user.
    conn_.prepareStatements(tagged_statements.begin(),
                            tagged_statements.end());
//                            tagged_statements.begin() + WRITE_STMTS_BEGIN);
}

MySqlConfigBackendDHCPv4Impl::~MySqlConfigBackendDHCPv4Impl() {
    // Free up the prepared statements, ignoring errors. (What would we do
    // about them? We're destroying this object and are not really concerned
    // with errors on a database connection that is about to go away.)
    for (int i = 0; i < conn_.statements_.size(); ++i) {
        if (conn_.statements_[i] != NULL) {
            (void) mysql_stmt_close(conn_.statements_[i]);
            conn_.statements_[i] = NULL;
        }
    }
}

MySqlConfigBackendDHCPv4::
MySqlConfigBackendDHCPv4(const DatabaseConnection::ParameterMap& parameters)
    : impl_(new MySqlConfigBackendDHCPv4Impl(parameters)) {
}

Subnet4Ptr
MySqlConfigBackendDHCPv4::getSubnet4(const ServerSelector& selector,
                                     const std::string& subnet_prefix) const {
}

Subnet4Ptr
MySqlConfigBackendDHCPv4::getSubnet4(const ServerSelector& selector,
                                     const SubnetID& subnet_id) const {
    BindingCollection in_bindings;
    in_bindings.push_back(Binding::createString("1024"));

    BindingCollection out_bindings;
    out_bindings.push_back(Binding::createString());

    impl_->conn_.selectQuery(MySqlConfigBackendDHCPv4Impl::GET_SUBNET4_ID,
                             in_bindings, out_bindings,
                             [&out_bindings]() {
        uint32_t hostname = out_bindings[0]->getValue<uint32_t>();
    });

    return (Subnet4Ptr());
}

Subnet4Collection
MySqlConfigBackendDHCPv4::getAllSubnets4(const ServerSelector& selector) const {
}

Subnet4Collection
MySqlConfigBackendDHCPv4::getModifiedSubnets4(const ServerSelector& selector,
                                              const boost::posix_time::ptime& modification_time) const {
}

SharedNetwork4Ptr
MySqlConfigBackendDHCPv4::getSharedNetwork4(const ServerSelector& selector,
                                            const std::string& name) const {
}

SharedNetwork4Collection
MySqlConfigBackendDHCPv4::getAllSharedNetworks4(const ServerSelector& selector) const {
}

SharedNetwork4Collection
MySqlConfigBackendDHCPv4::getModifiedSharedNetworks4(const ServerSelector& selector,
                                                     const boost::posix_time::ptime& modification_time) const {
}

OptionDefinitionPtr
MySqlConfigBackendDHCPv4::getOptionDef4(const ServerSelector& selector,
                                        const uint16_t code,
                                        const std::string& space) const {
}

OptionDefContainer
MySqlConfigBackendDHCPv4::getAllOptionDefs4(const ServerSelector& selector) const {
}

OptionDefContainer
MySqlConfigBackendDHCPv4::getModifiedOptionDefs4(const ServerSelector& selector,
                                                 const boost::posix_time::ptime& modification_time) const {
}

util::OptionalValue<std::string>
MySqlConfigBackendDHCPv4::getGlobalStringParameter4(const ServerSelector& selector,
                                                    const std::string& name) const {
}
util::OptionalValue<int64_t>
MySqlConfigBackendDHCPv4::getGlobalNumberParameter4(const ServerSelector& selector,
                                                    const std::string& name) const {
}

std::map<std::string, std::string>
MySqlConfigBackendDHCPv4::getAllGlobalParameters4(const ServerSelector& selector) const {
}

void
MySqlConfigBackendDHCPv4::createUpdateSubnet4(const ServerSelector& selector,
                                              const Subnet4Ptr& subnet) {
}

void
MySqlConfigBackendDHCPv4::createUpdateSharedNetwork4(const ServerSelector& selector,
                                                     const SharedNetwork4Ptr& shared_network) {
}

void
MySqlConfigBackendDHCPv4::createUpdateOptionDef4(const ServerSelector& selector,
                                                 const OptionDefinitionPtr& option_def) {
}

void
MySqlConfigBackendDHCPv4::createUpdateOption4(const ServerSelector& selector,
                                              const OptionPtr& option) {
}

void
MySqlConfigBackendDHCPv4::createUpdateOption4(const ServerSelector& selector,
                                              const SubnetID& subnet_id,
                                              const OptionPtr& option) {
}

void
MySqlConfigBackendDHCPv4::createUpdateOption4(const ServerSelector& selector,
                                              const asiolink::IOAddress& pool_start_address,
                                              const asiolink::IOAddress& pool_end_address,
                                              const OptionPtr& option) {
}

void
MySqlConfigBackendDHCPv4::createUpdateGlobalParameter4(const ServerSelector& selector,
                                                       const std::string& name,
                                                       const std::string& value) {
}

void
MySqlConfigBackendDHCPv4::createUpdateGlobalParameter4(const ServerSelector& selector,
                                                       const std::string& name,
                                                       const int64_t value) {
}

void
MySqlConfigBackendDHCPv4::deleteSubnet4(const ServerSelector& selector,
                                        const std::string& subnet_prefix) {
}

void
MySqlConfigBackendDHCPv4::deleteSubnet4(const ServerSelector& selector,
                                        const SubnetID& subnet_id) {
}

void
MySqlConfigBackendDHCPv4::deleteAllSubnets4(const ServerSelector& selector) {
}

void
MySqlConfigBackendDHCPv4::deleteSharedNetwork4(const ServerSelector& selector,
                                               const std::string& name) {
}

void
MySqlConfigBackendDHCPv4::deleteAllSharedNetworks4(const ServerSelector& selector) {
}

void
MySqlConfigBackendDHCPv4::deleteOptionDef4(const ServerSelector& selector,
                                           const uint16_t code,
                                           const std::string& space) {
}

void
MySqlConfigBackendDHCPv4::deleteAllOptionDefs4(const ServerSelector& selector) {
}

void
MySqlConfigBackendDHCPv4::deleteOption4(const ServerSelector& selector,
                                        const uint16_t code,
                                        const std::string& space) {
}

void
MySqlConfigBackendDHCPv4::deleteOption4(const ServerSelector& selector,
                                        const SubnetID& subnet_id,
                                        const uint16_t code,
                                        const std::string& space) {
}

void
MySqlConfigBackendDHCPv4::deleteOption4(const ServerSelector& selector,
                                        const asiolink::IOAddress& pool_start_address,
                                        const asiolink::IOAddress& pool_end_address,
                                        const uint16_t code,
                                        const std::string& space) {
}

void
MySqlConfigBackendDHCPv4::deleteGlobalParameter4(const ServerSelector& selector,
                                                 const std::string& name) {
}

void
MySqlConfigBackendDHCPv4::deleteAllGlobalParameters4(const ServerSelector& selector) {
}

std::string
MySqlConfigBackendDHCPv4::getType() const {
    return ("mysql");
}

std::string
MySqlConfigBackendDHCPv4::getHost() const {
}

uint16_t
MySqlConfigBackendDHCPv4::getPort() const {
}

} // end of namespace isc::dhcp
} // end of namespace isc
