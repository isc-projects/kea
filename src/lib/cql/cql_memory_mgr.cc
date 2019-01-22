// Copyright (C) 2018 Deutsche Telekom AG.
//
// Authors: Andrei Pavel <andrei.pavel@qualitance.com>
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

#include <cql/cql_memory_mgr.h>

namespace isc {
namespace db {

CassClusterPtr MakePtr(CassCluster* cluster) {
    return CassClusterPtr(cluster, [](CassCluster* c) {
        if (c) {
            cass_cluster_free(c);
        }
    });
}

CassFuturePtr MakePtr(CassFuture* future) {
    return CassFuturePtr(future, [](CassFuture* f) {
        if (f) {
            cass_future_free(f);
        }
    });
}

CassIteratorPtr MakePtr(CassIterator* iterator) {
    return CassIteratorPtr(iterator, [](CassIterator* i) {
        if (i) {
            cass_iterator_free(i);
        }
    });
}

CassPreparedPtr MakePtr(CassPrepared const* prepared) {
    return CassPreparedPtr(prepared, [](CassPrepared const* p) {
        if (p) {
            cass_prepared_free(p);
        }
    });
}

CassResultPtr MakePtr(CassResult const* result) {
    return CassResultPtr(result, [](CassResult const* r) {
        if (r) {
            cass_result_free(r);
        }
    });
}

CassStatementPtr MakePtr(CassStatement* statement) {
    return CassStatementPtr(statement, [](CassStatement* s) {
        if (s) {
            cass_statement_free(s);
        }
    });
}

CassSslPtr MakePtr(CassSsl* ssl) {
    return CassSslPtr(ssl, [](CassSsl* s) {
        if (s) {
            cass_ssl_free(s);
        }
    });
}

CassSessionPtr MakePtr(CassSession* session) {
    return CassSessionPtr(session, [](CassSession* s) {
        if (s) {
            auto f = MakePtr(cass_session_close(s));
            cass_future_wait(f.get());
            cass_session_free(s);
        }
    });
}

CassUuidGenPtr MakePtr(CassUuidGen* gen) {
    return CassUuidGenPtr(gen, [](CassUuidGen* g) {
        if (g) {
            cass_uuid_gen_free(g);
        }
    });
}

}  // namespace db
}  // namespace isc
