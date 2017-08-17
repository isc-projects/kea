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

#include <config.h>

#include <dhcpsrv/cql_connection.h>
#include <dhcpsrv/cql_exchange.h>

#include <boost/shared_ptr.hpp>

using namespace std;

namespace isc {
namespace dhcp {

CqlConnection::CqlConnection(const ParameterMap& parameters)
    : DatabaseConnection(parameters), cluster_(NULL), session_(NULL),
      force_consistency_(true), consistency_(CASS_CONSISTENCY_QUORUM),
      tagged_statements_(NULL) {
}

CqlConnection::~CqlConnection() {
    // Free up the prepared statements, ignoring errors. Session and connection
    // resources are deallocated.
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
        checkStatementError(error, close_future, "could not close connection to"
                                                 " DB");
        rc = cass_future_error_code(close_future);
        cass_future_free(close_future);
        cass_session_free(session_);
        session_ = NULL;
    }

    if (cluster_) {
        cass_cluster_free(cluster_);
        cluster_ = NULL;
    }

    if (rc != CASS_OK) {
        // We're closing the connection anyway. Let's not throw at this stage.
        LOG_ERROR(dhcpsrv_logger, DHCPSRV_CQL_DEALLOC_ERROR).arg(error);
    }
}

void
CqlConnection::openDatabase() {
    CassError rc;
    // Set up the values of the parameters
    const char* contact_points = "127.0.0.1";
    std::string scontact_points;
    try {
        scontact_points = getParameter("contact-points");
        contact_points = scontact_points.c_str();
    } catch (...) {
        // No host. Fine, we'll use "127.0.0.1".
    }

    const char* port = NULL;
    std::string sport;
    try {
        sport = getParameter("port");
        port = sport.c_str();
    } catch (...) {
        // No port. Fine, we'll use the default "9042".
    }

    const char* user = NULL;
    std::string suser;
    try {
        suser = getParameter("user");
        user = suser.c_str();
    } catch (...) {
        // No user. Fine, we'll use NULL.
    }

    const char* password = NULL;
    std::string spassword;
    try {
        spassword = getParameter("password");
        password = spassword.c_str();
    } catch (...) {
        // No password. Fine, we'll use NULL.
    }

    const char* keyspace = "keatest";
    std::string skeyspace;
    try {
        skeyspace = getParameter("keyspace");
        keyspace = skeyspace.c_str();
    } catch (...) {
        // No keyspace name. Fine, we'll use "keatest".
    }

    const char* reconnect_wait_time = NULL;
    std::string sreconnect_wait_time;
    try {
        sreconnect_wait_time = getParameter("reconnect-wait-time");
        reconnect_wait_time = sreconnect_wait_time.c_str();
    } catch (...) {
        // No reconnect wait time. Fine, we'll use the default "2000".
    }

    const char* connect_timeout = NULL;
    std::string sconnect_timeout;
    try {
        sconnect_timeout = getParameter("connect-timeout");
        connect_timeout = sconnect_timeout.c_str();
    } catch (...) {
        // No connect timeout. Fine, we'll use the default "5000".
    }

    const char* request_timeout = NULL;
    std::string srequest_timeout;
    try {
        srequest_timeout = getParameter("request-timeout");
        request_timeout = srequest_timeout.c_str();
    } catch (...) {
        // No request timeout. Fine, we'll use the default "12000".
    }

    const char* tcp_keepalive = NULL;
    std::string stcp_keepalive;
    try {
        stcp_keepalive = getParameter("tcp-keepalive");
        tcp_keepalive = stcp_keepalive.c_str();
    } catch (...) {
        // No tcp-keepalive. Fine, we'll not use TCP keepalive.
    }

    std::string stcp_nodelay;
    try {
        stcp_nodelay = getParameter("tcp-nodelay");
    } catch (...) {
        // No tcp-nodelay. Fine, we'll use the default false.
    }

    cluster_ = cass_cluster_new();
    cass_cluster_set_contact_points(cluster_, contact_points);

    if (user && password) {
        cass_cluster_set_credentials(cluster_, user, password);
    }

    if (port) {
        int port_number;
        try {
            port_number = boost::lexical_cast<int>(port);
            if (port_number < 1 || port_number > 65535) {
                isc_throw(
                    DbOperationError,
                    "Port outside of range, expected 1-65535, instead got "
                        << port);
            }
        } catch (const boost::bad_lexical_cast& ex) {
            isc_throw(DbOperationError,
                      "Invalid port, castable to int expected, instead got \""
                          << port << "\", " << ex.what());
        }
        cass_cluster_set_port(cluster_, port_number);
    }

    if (reconnect_wait_time) {
        int reconnect_wait_time_number;
        try {
            reconnect_wait_time_number =
                boost::lexical_cast<int>(reconnect_wait_time);
            if (reconnect_wait_time_number < 0) {
                isc_throw(DbOperationError,
                          "Invalid reconnect wait time, positive number "
                          "expected, instead got "
                              << reconnect_wait_time);
            }
        } catch (const boost::bad_lexical_cast& ex) {
            isc_throw(DbOperationError, "Invalid reconnect wait time, castable "
                                        "to int expected, instead got \""
                                            << reconnect_wait_time << "\", "
                                            << ex.what());
        }
        cass_cluster_set_reconnect_wait_time(cluster_,
                                             reconnect_wait_time_number);
    }

    if (connect_timeout) {
        int connect_timeout_number;
        try {
            connect_timeout_number = boost::lexical_cast<int>(connect_timeout);
            if (connect_timeout_number < 0) {
                isc_throw(DbOperationError,
                          "Invalid connect timeout, positive number expected, "
                          "instead got "
                              << connect_timeout);
            }
        } catch (const boost::bad_lexical_cast& ex) {
            isc_throw(DbOperationError, "Invalid connect timeout, castable to "
                                        "int expected, instead got \""
                                            << connect_timeout << "\", "
                                            << ex.what());
        }
        cass_cluster_set_connect_timeout(cluster_, connect_timeout_number);
    }

    if (request_timeout) {
        int request_timeout_number;
        try {
            request_timeout_number = boost::lexical_cast<int>(request_timeout);
            if (request_timeout_number < 0) {
                isc_throw(DbOperationError,
                          "Invalid request timeout, positive number expected, "
                          "instead got "
                              << request_timeout);
            }
        } catch (const boost::bad_lexical_cast& ex) {
            isc_throw(DbOperationError, "Invalid request timeout, castable to "
                                        "int expected, instead got \""
                                            << request_timeout << "\", "
                                            << ex.what());
        }
        cass_cluster_set_request_timeout(cluster_, request_timeout_number);
    }

    if (tcp_keepalive) {
        int tcp_keepalive_number;
        try {
            tcp_keepalive_number = boost::lexical_cast<int>(tcp_keepalive);
            if (tcp_keepalive_number < 0) {
                isc_throw(DbOperationError,
                          "Invalid TCP keepalive, positive number expected, "
                          "instead got "
                              << tcp_keepalive);
            }
        } catch (const boost::bad_lexical_cast& ex) {
            isc_throw(
                DbOperationError,
                "Invalid TCP keepalive, castable to int expected, instead got "
                "\"" << tcp_keepalive
                     << "\", " << ex.what());
        }
        cass_cluster_set_tcp_keepalive(cluster_, cass_true,
                                       tcp_keepalive_number);
    }

    if (stcp_nodelay == "true") {
        cass_cluster_set_tcp_nodelay(cluster_, cass_true);
    }

    session_ = cass_session_new();

    CassFuture* connect_future =
        cass_session_connect_keyspace(session_, cluster_, keyspace);
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
CqlConnection::prepareStatements(CqlTaggedStatement* statements) {
    CassError rc = CASS_OK;
    uint32_t size = 0;
    tagged_statements_ = statements;
    for (; tagged_statements_[size].params_; size++) {
    }
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
CqlConnection::setConsistency(bool force, CassConsistency consistency) {
    force_consistency_ = force;
    consistency_ = consistency;
}

void
CqlConnection::startTransaction() {
    LOG_DEBUG(dhcpsrv_logger, DHCPSRV_DBG_TRACE_DETAIL,
              DHCPSRV_CQL_BEGIN_TRANSACTION);
    // No-op
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
CqlConnection::checkStatementError(std::string& error,
                                   CassFuture* future,
                                   uint32_t stindex,
                                   const char* what) const {
    CassError rc;
    const char* errorMessage;
    size_t errorMessageSize;
    std::stringstream stream;
    stream << "no error for statement " << tagged_statements_[stindex].name_;

    rc = cass_future_error_code(future);
    cass_future_error_message(future, &errorMessage, &errorMessageSize);

    if (rc != CASS_OK) {
        stream.str(std::string());
        stream << what << " for statement " << tagged_statements_[stindex].name_
               << ". Future error: " << errorMessage
               << ". Error description: " << cass_error_desc(rc);
    }
    error = stream.str();
}

void
CqlConnection::checkStatementError(std::string& error,
                                   CassFuture* future,
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
        stream << what << ". Future error: " << errorMessage
               << ". Error description: " << cass_error_desc(rc);
    }
    error = stream.str();
}

CqlTransaction::CqlTransaction(CqlConnection& conn)
    : conn_(conn), committed_(false) {
    conn_.startTransaction();
}

CqlTransaction::~CqlTransaction() {
    // Rollback if commit() wasn't explicitly called.
    if (!committed_) {
        conn_.rollback();
    }
}

void
CqlTransaction::commit() {
    conn_.commit();
    committed_ = true;
}

}  // namespace dhcp
}  // namespace isc
