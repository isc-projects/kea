// Copyright (C) 2018 Internet Systems Consortium, Inc. ("ISC")
// Copyright (C) 2015-2018 Deutsche Telekom AG.
//
// Authors: Razvan Becheriu <razvan.becheriu@qualitance.com>
//          Andrei Pavel <andrei.pavel@qualitance.com>
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

#include <cql/cql_connection.h>
#include <cql/cql_exchange.h>
#include <database/db_exceptions.h>
#include <database/db_log.h>

#include <string>

namespace isc {
namespace db {

CqlConnection::CqlConnection(const ParameterMap& parameters)
    : DatabaseConnection(parameters), statements_(), cluster_(NULL),
      session_(NULL), consistency_(CASS_CONSISTENCY_QUORUM),
      serial_consistency_(CASS_CONSISTENCY_UNKNOWN), schema_meta_(NULL),
      keyspace_meta_(NULL), force_consistency_(true) {
}

CqlConnection::~CqlConnection() {
    // Free up the prepared statements, ignoring errors. Session and connection
    // resources are deallocated.
    CassError rc = CASS_OK;
    std::string error;

    // Let's free the prepared statements.
    for (StatementMapEntry s : statements_) {
        CqlTaggedStatement statement = s.second;
        if (statement.prepared_statement_) {
            cass_prepared_free(statement.prepared_statement_);
        }
    }

    // If there's a session, tear it down and free the resources.
    if (session_) {
        cass_schema_meta_free(schema_meta_);
        CassFuture* close_future = cass_session_close(session_);
        cass_future_wait(close_future);
        error = checkFutureError(
            "CqlConnection::~CqlConnection(): cass_sesssion_close() != CASS_OK",
            close_future);
        rc = cass_future_error_code(close_future);
        cass_future_free(close_future);
        cass_session_free(session_);
        session_ = NULL;
    }

    // Free the cluster if there's one.
    if (cluster_) {
        cass_cluster_free(cluster_);
        cluster_ = NULL;
    }

    if (rc != CASS_OK) {
        // We're closing the connection anyway. Let's not throw at this stage.
        DB_LOG_ERROR(CQL_DEALLOC_ERROR).arg(error);
    }
}

CassConsistency CqlConnection::parseConsistency(std::string value) {
    static std::map<std::string, CassConsistency> consistency_map {
        {"any", CASS_CONSISTENCY_ANY},
        {"one", CASS_CONSISTENCY_ONE},
        {"two", CASS_CONSISTENCY_TWO},
        {"three", CASS_CONSISTENCY_THREE},
        {"quorum", CASS_CONSISTENCY_QUORUM},
        {"all", CASS_CONSISTENCY_ALL},
        {"local-quorum", CASS_CONSISTENCY_LOCAL_QUORUM},
        {"each-quorum", CASS_CONSISTENCY_EACH_QUORUM},
        {"serial", CASS_CONSISTENCY_SERIAL},
        {"local-serial", CASS_CONSISTENCY_LOCAL_SERIAL},
        {"local-one", CASS_CONSISTENCY_LOCAL_ONE}
    };
    if (consistency_map.find(value) == consistency_map.end()) {
        return CASS_CONSISTENCY_UNKNOWN;
    }
    return consistency_map[value];
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

    const char* consistency = NULL;
    std::string sconsistency;
    try {
        sconsistency = getParameter("consistency");
        consistency = sconsistency.c_str();
    } catch (...) {
        // No consistency. Fine, we'll use "quorum".
    }

    const char* serial_consistency = NULL;
    std::string sserial_consistency;
    try {
        sserial_consistency = getParameter("serial-consistency");
        serial_consistency = sserial_consistency.c_str();
    } catch (...) {
        // No serial consistency. Fine, we'll use "serial".
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
        int32_t port_number;
        try {
            port_number = boost::lexical_cast<int32_t>(port);
            if (port_number < 1 || port_number > 65535) {
                isc_throw(DbOperationError,
                          "CqlConnection::openDatabase(): "
                          "port outside of range, expected "
                          "1-65535, instead got "
                              << port);
            }
        } catch (const boost::bad_lexical_cast& ex) {
            isc_throw(DbOperationError,
                      "CqlConnection::openDatabase(): invalid "
                      "port, expected castable to int, instead got "
                      "\"" << port
                           << "\", " << ex.what());
        }
        cass_cluster_set_port(cluster_, port_number);
    }

    if (consistency) {
        CassConsistency desired_consistency = CqlConnection::parseConsistency(sconsistency);
        CassConsistency desired_serial_consistency = CASS_CONSISTENCY_UNKNOWN;
        if (serial_consistency) {
            desired_serial_consistency = CqlConnection::parseConsistency(sserial_consistency);
        }
        if (desired_consistency != CASS_CONSISTENCY_UNKNOWN) {
            setConsistency(true, desired_consistency, desired_serial_consistency);
        }
    }

    if (reconnect_wait_time) {
        int32_t reconnect_wait_time_number;
        try {
            reconnect_wait_time_number =
                boost::lexical_cast<int32_t>(reconnect_wait_time);
            if (reconnect_wait_time_number < 0) {
                isc_throw(DbOperationError,
                          "CqlConnection::openDatabase(): invalid reconnect "
                          "wait time, expected positive number, instead got "
                              << reconnect_wait_time);
            }
        } catch (const boost::bad_lexical_cast& ex) {
            isc_throw(DbOperationError,
                      "CqlConnection::openDatabase(): "
                      "invalid reconnect wait time, expected "
                      "castable to int, instead got \""
                          << reconnect_wait_time << "\", " << ex.what());
        }
        cass_cluster_set_reconnect_wait_time(cluster_,
                                             reconnect_wait_time_number);
    }

    if (connect_timeout) {
        int32_t connect_timeout_number;
        try {
            connect_timeout_number =
                boost::lexical_cast<int32_t>(connect_timeout);
            if (connect_timeout_number < 0) {
                isc_throw(DbOperationError,
                          "CqlConnection::openDatabase(): "
                          "invalid connect timeout, expected "
                          "positive number, instead got "
                              << connect_timeout);
            }
        } catch (const boost::bad_lexical_cast& ex) {
            isc_throw(DbOperationError,
                      "CqlConnection::openDatabase(): invalid connect timeout, "
                      "expected castable to int, instead got \""
                          << connect_timeout << "\", " << ex.what());
        }
        cass_cluster_set_connect_timeout(cluster_, connect_timeout_number);
    }

    if (request_timeout) {
        int32_t request_timeout_number;
        try {
            request_timeout_number =
                boost::lexical_cast<int32_t>(request_timeout);
            if (request_timeout_number < 0) {
                isc_throw(DbOperationError,
                          "CqlConnection::openDatabase(): "
                          "invalid request timeout, expected "
                          "positive number, instead got "
                              << request_timeout);
            }
        } catch (const boost::bad_lexical_cast& ex) {
            isc_throw(DbOperationError,
                      "CqlConnection::openDatabase(): invalid request timeout, "
                      "expected castable to int, instead got \""
                          << request_timeout << "\", " << ex.what());
        }
        cass_cluster_set_request_timeout(cluster_, request_timeout_number);
    }

    if (tcp_keepalive) {
        int32_t tcp_keepalive_number;
        try {
            tcp_keepalive_number = boost::lexical_cast<int32_t>(tcp_keepalive);
            if (tcp_keepalive_number < 0) {
                isc_throw(DbOperationError,
                          "CqlConnection::openDatabase(): "
                          "invalid TCP keepalive, expected "
                          "positive number, instead got "
                              << tcp_keepalive);
            }
        } catch (const boost::bad_lexical_cast& ex) {
            isc_throw(DbOperationError,
                      "CqlConnection::openDatabase(): invalid TCP keepalive, "
                      "expected castable to int, instead got \""
                          << tcp_keepalive << "\", " << ex.what());
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
    const std::string error =
        checkFutureError("CqlConnection::openDatabase(): "
                         "cass_session_connect_keyspace() != CASS_OK",
                         connect_future);
    rc = cass_future_error_code(connect_future);
    cass_future_free(connect_future);
    if (rc != CASS_OK) {
        cass_session_free(session_);
        session_ = NULL;
        cass_cluster_free(cluster_);
        cluster_ = NULL;
        isc_throw(DbOpenError, error);
    }

    // Get keyspace meta.
    schema_meta_ = cass_session_get_schema_meta(session_);
    keyspace_meta_ = cass_schema_meta_keyspace_by_name(schema_meta_, keyspace);
    if (!keyspace_meta_) {
        isc_throw(DbOpenError, "CqlConnection::openDatabase(): "
                               "!cass_schema_meta_keyspace_by_name()");
    }
}

void
CqlConnection::prepareStatements(StatementMap& statements) {
    CassError rc = CASS_OK;
    for (StatementMapEntry it : statements) {
        CqlTaggedStatement& tagged_statement = it.second;
        if (statements_.find(tagged_statement.name_) != statements_.end()) {
            isc_throw(DbOperationError,
                      "CqlConnection::prepareStatements(): "
                      "duplicate statement with name "
                          << tagged_statement.name_);
        }

        CassFuture* future =
            cass_session_prepare(session_, tagged_statement.text_);
        cass_future_wait(future);
        const std::string error =
            checkFutureError("CqlConnection::prepareStatements():"
                             " cass_session_prepare() != CASS_OK",
                             future, tagged_statement.name_);
        rc = cass_future_error_code(future);
        if (rc != CASS_OK) {
            cass_future_free(future);
            isc_throw(DbOperationError, error);
        }

        tagged_statement.prepared_statement_ = cass_future_get_prepared(future);
        statements_.insert(it);
        cass_future_free(future);
    }
}

void
CqlConnection::setConsistency(bool force,
                              CassConsistency consistency,
                              CassConsistency serial_consistency) {
    force_consistency_ = force;
    consistency_ = consistency;
    serial_consistency_ = serial_consistency;
}

void
CqlConnection::startTransaction() {
    DB_LOG_DEBUG(DB_DBG_TRACE_DETAIL, CQL_CONNECTION_BEGIN_TRANSACTION);
}

void
CqlConnection::commit() {
    DB_LOG_DEBUG(DB_DBG_TRACE_DETAIL, CQL_CONNECTION_COMMIT);
}

void
CqlConnection::rollback() {
    DB_LOG_DEBUG(DB_DBG_TRACE_DETAIL, CQL_CONNECTION_ROLLBACK);
}

const std::string
CqlConnection::checkFutureError(const std::string& what,
                                CassFuture* future,
                                StatementTag statement_tag /* = NULL */) {
    CassError cass_error = cass_future_error_code(future);
    const char* error_message;
    size_t error_message_size;
    cass_future_error_message(future, &error_message, &error_message_size);

    std::stringstream stream;
    if (statement_tag && std::strlen(statement_tag) > 0) {
        // future is from cass_session_execute() call.
        stream << "Statement ";
        stream << statement_tag;
    } else {
        // future is from cass_session_*() call.
        stream << "Session action ";
    }
    if (cass_error == CASS_OK) {
        stream << " executed succesfully.";
    } else {
        stream << " failed, Kea error: " << what
               << ", Cassandra error code: " << cass_error_desc(cass_error)
               << ", Cassandra future error: " << error_message;
    }
    return stream.str();
}

}  // namespace dhcp
}  // namespace isc
