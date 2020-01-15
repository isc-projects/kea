// Copyright (C) 2018-2019 Internet Systems Consortium, Inc. ("ISC")
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
      session_(NULL), ssl_(NULL), consistency_(CASS_CONSISTENCY_QUORUM),
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

    // If SSL is not enabled, then free resources.
    if (ssl_) {
        cass_ssl_free(ssl_);
        ssl_ = NULL;
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

std::pair<uint32_t, uint32_t>
CqlConnection::getVersion(const ParameterMap& parameters) {
    // Get a connection.
    CqlConnection conn(parameters);

    // Open the database.
    conn.openDatabase();

    // Prepare statement.
    conn.prepareStatements(CqlVersionExchange::tagged_statements_);

    std::unique_ptr<CqlVersionExchange> version_exchange(new CqlVersionExchange());
    return version_exchange->retrieveVersion(conn);
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

    std::string sssl_on;
    try {
        sssl_on = getParameter("ssl");
    } catch (...) {
        // SSL not enabled.
    }

    const char* ssl_ca_file = NULL;
    std::string sssl_ca_file;
    const char* ssl_cert_file = NULL;
    std::string sssl_cert_file;
    const char* ssl_key_file = NULL;
    std::string sssl_key_file;
    const char* ssl_key_password = NULL;
    std::string sssl_key_password;

    if ( sssl_on == "true" ) {
        try {
            sssl_ca_file = getParameter("ssl-ca");
            ssl_ca_file = sssl_ca_file.c_str();
        } catch (...) {
            // No ssl-ca. Fine, we'll disable the ssl verification.
        }

        try {
            sssl_cert_file = getParameter("ssl-cert");
            ssl_cert_file = sssl_cert_file.c_str();
        } catch (...) {
            // No ssl-cert. Fine, we'll disable the ssl authentication.
        }

        try {
            sssl_key_file = getParameter("ssl-key");
            ssl_key_file = sssl_key_file.c_str();
        } catch (...) {
            // No ssl-key. Fine, we'll disable the ssl authentication.
        }

        try {
            sssl_key_password = getParameter("ssl-password");
            ssl_key_password = sssl_key_password.c_str();
        } catch (...) {
            // No ssl-password. Fine, assuming keyfile does not have password on it.
        }
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

    if ( sssl_on == "true" ) {
        bool ssl_error = false;

        ssl_ = cass_ssl_new();

        // should we do peer-verification?
        if (ssl_ca_file) {
            char* ssl_ca;

            long ssl_ca_size;
            size_t bytes_read;

            FILE *ssl_ca_file_h = fopen(ssl_ca_file, "rb");
            if (ssl_ca_file_h == NULL) {
                cass_ssl_free(ssl_);
                ssl_ = NULL;
                cass_cluster_free(cluster_);
                cluster_ = NULL;
                isc_throw(DbOperationError,
                          "CqlConnection::openDatabase(): "
                          "invalid ssl CA certificate file: "
                              << sssl_ca_file);
            }

            fseek(ssl_ca_file_h, 0, SEEK_END);
            ssl_ca_size = ftell(ssl_ca_file_h);
            rewind(ssl_ca_file_h);

            ssl_ca = new char[ssl_ca_size];
            bytes_read = fread(ssl_ca, 1, ssl_ca_size, ssl_ca_file_h);
            fclose(ssl_ca_file_h);


            if (bytes_read == (size_t) ssl_ca_size) {
                rc = cass_ssl_add_trusted_cert_n(ssl_, ssl_ca, ssl_ca_size);
                if (rc != CASS_OK) {
                    ssl_error = true;
                }
            } else {
                ssl_error = true;
            }
            delete[] ssl_ca;
            cass_ssl_set_verify_flags(ssl_, CASS_SSL_VERIFY_PEER_CERT);
        } else {
            cass_ssl_set_verify_flags(ssl_, CASS_SSL_VERIFY_NONE);
        }

        // should we do SSL authentication?
        if (ssl_cert_file && ssl_key_file) {
            char* ssl_cert;
            char* ssl_key;

            long ssl_cert_size;
            long ssl_key_size;
            size_t bytes_read;

            // read user cert file
            FILE *ssl_cert_file_h = fopen(ssl_cert_file, "rb");
            if (ssl_cert_file_h == NULL) {
                cass_ssl_free(ssl_);
                ssl_ = NULL;
                cass_cluster_free(cluster_);
                cluster_ = NULL;
                isc_throw(DbOperationError,
                          "CqlConnection::openDatabase(): "
                          "invalid ssl certificate file: "
                              << sssl_cert_file);
            }

            fseek(ssl_cert_file_h, 0, SEEK_END);
            ssl_cert_size = ftell(ssl_cert_file_h);
            rewind(ssl_cert_file_h);

            ssl_cert = new char[ssl_cert_size];
            bytes_read = fread(ssl_cert, 1, ssl_cert_size, ssl_cert_file_h);
            fclose(ssl_cert_file_h);

            if (bytes_read == (size_t) ssl_cert_size) {
                rc = cass_ssl_set_cert_n(ssl_, ssl_cert, ssl_cert_size);
                if (rc != CASS_OK) {
                    ssl_error = true;
                }
            } else {
                ssl_error = true;
            }
            delete[] ssl_cert;

            // read user key file
            FILE *ssl_key_file_h = fopen(ssl_key_file, "rb");
            if (ssl_key_file_h == NULL) {
                cass_ssl_free(ssl_);
                ssl_ = NULL;
                cass_cluster_free(cluster_);
                cluster_ = NULL;
                isc_throw(DbOperationError,
                          "CqlConnection::openDatabase(): "
                          "invalid ssl key file: "
                              << sssl_key_file);
            }

            fseek(ssl_key_file_h, 0, SEEK_END);
            ssl_key_size = ftell(ssl_key_file_h);
            rewind(ssl_key_file_h);

            ssl_key = new char[ssl_key_size];
            bytes_read = fread(ssl_key, 1, ssl_key_size, ssl_key_file_h);
            fclose(ssl_key_file_h);

            size_t ssl_key_password_l;
            if ( ssl_key_password ) {
                ssl_key_password_l = std::strlen(ssl_key_password);
            } else {
                ssl_key_password_l = 0;
                ssl_key_password = NULL;
            }

            if (bytes_read == (size_t) ssl_key_size) {
                rc = cass_ssl_set_private_key_n(ssl_, ssl_key, ssl_key_size, ssl_key_password, ssl_key_password_l);
                if (rc != CASS_OK) {
                    ssl_error = true;
                }
            } else {
                ssl_error = true;
            }
            delete[] ssl_key;
        }

        if (ssl_error) {
            cass_ssl_free(ssl_);
            ssl_ = NULL;
            cass_cluster_free(cluster_);
            cluster_ = NULL;
            isc_throw(DbOperationError,
                      "CqlConnection::openDatabase(): "
                      "SSL setup failed for CQL ");
        }

        cass_cluster_set_ssl(cluster_, ssl_);
    } else {
        ssl_ = NULL;
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
        if (ssl_) {
            cass_ssl_free(ssl_);
        }
        ssl_ = NULL;

        const char* e_message;
        size_t e_message_length;
        cass_future_error_message(connect_future, &e_message, &e_message_length);
        LOG_ERROR(database_logger,  e_message);

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
    LOG_DEBUG(database_logger, isc::log::DBGLVL_TRACE_BASIC, "Successfully connected to Cassandra database.");
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
