// Copyright (C) 2015 - 2016 Deutsche Telekom AG.
//
// Author: Razvan Becheriu <razvan.becheriu@qualitance.com>
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//           http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <dhcpsrv/cql_connection.h>
#include <string>

using namespace std;

namespace isc {
namespace dhcp {

CqlConnection::CqlConnection(const ParameterMap& parameters) :
        DatabaseConnection(parameters), cluster_(NULL), session_(NULL),
        tagged_statements_(NULL) {
}

CqlConnection::~CqlConnection() {
    // Free up the prepared statements, ignoring errors.
    // Session and connection resources are deallocated.
    CassError rc = CASS_OK;
    std::string error;

    for (int i = 0; i < statements_.size(); i++) {
        if (statements_[i]) {
            cass_prepared_free(statements_[i]);
        }
        statements_[i] = NULL;
    }

    if (session_) {
        CassFuture* close_future = cass_session_close(session_);
        cass_future_wait(close_future);
        checkStatementError(error, close_future, "could not close connection to DB");
        rc = cass_future_error_code(close_future);
        cass_future_free(close_future);
        cass_session_free(session_);
        session_ = NULL;
    }

    if (cluster_) {
        cass_cluster_free(cluster_);
        cluster_ = NULL;
    }

    // We're closing the connection anyway. Let's not throw at this
    // stage
    if (rc != CASS_OK) {
        isc_throw(DbOpenError, error);
    }
}

void
CqlConnection::openDatabase() {
    CassError rc;
    // Set up the values of the parameters
    const char* contact_points = "127.0.0.1";
    string scontact_points;
    try {
        scontact_points = getParameter("contact-points");
        contact_points = scontact_points.c_str();
    } catch (...) {
        // No host. Fine, we'll use "localhost".
    }

    const char* port = NULL;
    string sport;
    try {
        sport = getParameter("port");
        port = sport.c_str();
    } catch (...) {
        // No port. Fine, we'll use "default".
    }

    const char* user = NULL;
    string suser;
    try {
        suser = getParameter("user");
        user = suser.c_str();
    } catch (...) {
        // No user. Fine, we'll use NULL.
    }

    const char* password = NULL;
    string spassword;
    try {
        spassword = getParameter("password");
        password = spassword.c_str();
    } catch (...) {
        // No password. Fine, we'll use NULL.
    }

    const char* keyspace = "keatest";
    string skeyspace;
    try {
        skeyspace = getParameter("keyspace");
        keyspace = skeyspace.c_str();
    } catch (...) {
        // No keyspace name. Fine, we'll use default "keatest".
    }

    cluster_ = cass_cluster_new();
    cass_cluster_set_contact_points(cluster_, contact_points);

    if (user != NULL && password != NULL) {
        cass_cluster_set_credentials(cluster_, user, password);
    }

    if (port != NULL) {
        int port_number;
        try {
            port_number = boost::lexical_cast<int>(port);
        } catch (const std::exception& ex) {
            isc_throw(DbOperationError, "Invalid int data: " << port
                      << " : " << ex.what());
        }
        cass_cluster_set_port(cluster_, port_number);
    }

    session_ = cass_session_new();

    CassFuture* connect_future = cass_session_connect_keyspace(session_,
        cluster_, keyspace);
    cass_future_wait(connect_future);
    std::string error;
    checkStatementError(error, connect_future, "could not connect to DB");
    rc = cass_future_error_code(connect_future);
    cass_future_free(connect_future);
    if (rc != CASS_OK) {
        cass_session_free(session_);
        session_ = NULL;
        cass_cluster_free(cluster_);
        cluster_ = NULL;
        isc_throw(DbOpenError, error);
    }
}

void
CqlConnection::prepareStatements(CqlTaggedStatement *statements) {
    CassError rc = CASS_OK;
    uint32_t size = 0;
    tagged_statements_ = statements;
    for (; tagged_statements_[size].params_; size++);
    statements_.resize(size);
    for (uint32_t i = 0; i < size; i++) {
        const char* query = tagged_statements_[i].text_;

        CassFuture* future = cass_session_prepare(session_, query);
        cass_future_wait(future);
        std::string error;
        checkStatementError(error, future, i, "could not prepare statement");
        rc = cass_future_error_code(future);
        if (rc != CASS_OK) {
            cass_future_free(future);
            statements_[i] = NULL;
            isc_throw(DbOperationError, error);
        } else {
            statements_[i] = cass_future_get_prepared(future);
        }

        cass_future_free(future);
    }
}

void
CqlConnection::commit() {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_CQL_COMMIT);
}

void
CqlConnection::rollback() {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL, DHCPSRV_CQL_ROLLBACK);
}

void
CqlConnection::checkStatementError(std::string& error, CassFuture* future,
                                   uint32_t stindex, const char* what) const {
    CassError rc;
    const char* errorMessage;
    size_t errorMessageSize;
    std::stringstream stream;
    stream << "no error for: " << tagged_statements_[stindex].name_;

    rc = cass_future_error_code(future);
    cass_future_error_message(future, &errorMessage, &errorMessageSize);

    if (rc != CASS_OK) {
        stream.str(std::string());
        stream << what << " for: " << tagged_statements_[stindex].name_
               << " reason: " << errorMessage << " error code: " << rc;
    }
    error = stream.str();
}

void
CqlConnection::checkStatementError(std::string& error, CassFuture* future,
                                   const char* what) const {
    CassError rc;
    const char* errorMessage;
    size_t errorMessageSize;
    std::stringstream stream;
    stream << "no error";

    rc = cass_future_error_code(future);
    cass_future_error_message(future, &errorMessage, &errorMessageSize);

    if (rc != CASS_OK) {
        stream.str(std::string());
        stream << what << " reason: " << errorMessage << " error code: " << rc;
    }
    error = stream.str();
}

}; // end of isc::dhcp namespace
}; // end of isc namespace
