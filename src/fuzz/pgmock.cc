// Copyright (C) 2025 Ada Logcis Ltd.
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
////////////////////////////////////////////////////////////////////////////////
#include <fuzzer/FuzzedDataProvider.h>

#include <cstdlib>
#include <cstring>
#include <cstddef>
#include <cstdint>

struct pg_conn {};
using  PGconn = pg_conn;

struct pg_result {
    int   status;
    int   ntuples;
    int   nfields;
    char** field_names;
    char** values;
};
using PGresult = pg_result;

enum {
    PGRES_EMPTY_QUERY = 0, PGRES_COMMAND_OK = 1,
    PGRES_TUPLES_OK = 2, PGRES_FATAL_ERROR = 7
};

static thread_local FuzzedDataProvider* g_fdp = nullptr;

extern "C" void pgmock_load_bytes(const uint8_t* data, size_t size) {
    delete g_fdp;
    g_fdp = new FuzzedDataProvider(data, size);
}

// Helper to duplcate string and drop const for return
static char* dupstr(const char* s) {
    if (!s) {
        return nullptr;
    }

    size_t n = std::strlen(s) + 1;
    char* p = static_cast<char*>(std::malloc(n));
    if (p) {
        std::memcpy(p, s, n);
    }

    return p;
}

// Helper to make a fuzz row result
static PGresult* make_fuzz_result() {
    int nfields = g_fdp->ConsumeIntegralInRange<int>(2, 8);

    PGresult* r = static_cast<PGresult*>(std::calloc(1, sizeof(PGresult)));
    r->status = PGRES_TUPLES_OK;
    r->ntuples = 1;
    r->nfields = nfields;

    r->field_names = static_cast<char**>(std::calloc(nfields, sizeof(char*)));
    r->values = static_cast<char**>(std::calloc((size_t)nfields, sizeof(char*)));

    for (int i = 0; i < nfields; ++i) {
        r->field_names[i] = dupstr(g_fdp->ConsumeRandomLengthString(32).c_str());

        // Provide random type of data return
        int kind = g_fdp->ConsumeIntegralInRange<int>(0, 3);
        if (kind == 0) {
            unsigned v = g_fdp->ConsumeIntegralInRange<unsigned>(0, 9999u);
            char buf[32];
            std::snprintf(buf, sizeof(buf), "%u", v);
            r->values[i] = dupstr(buf);
        } else if (kind == 1) {
            r->values[i] = dupstr(g_fdp->ConsumeBool() ? "1" : "0");
        } else if (kind == 2) {
            // IPv4 loopback as text
            r->values[i] = dupstr("127.0.0.1");
        } else {
            // IPv6 loopback as text
            r->values[i] = dupstr("::1");
        }
    }
    return r;
}

// Helper to make fixed version query for kea
static PGresult* make_version_result() {
    PGresult* r = static_cast<PGresult*>(std::calloc(1, sizeof(PGresult)));
    r->status  = PGRES_TUPLES_OK;
    r->ntuples = 1;
    r->nfields = 2;

    r->field_names = static_cast<char**>(std::calloc(2, sizeof(char*)));
    r->field_names[0] = dupstr("version");
    r->field_names[1] = dupstr("minor");

    r->values = static_cast<char**>(std::calloc(2, sizeof(char*)));
    r->values[0] = dupstr("31");
    r->values[1] = dupstr("0");

    return r;
}

// Helper to make success reply to update or delete query
static PGresult* make_command_ok_result() {
    PGresult* r = static_cast<PGresult*>(std::calloc(1, sizeof(PGresult)));
    r->status  = PGRES_COMMAND_OK;
    r->ntuples = 0;
    r->nfields = 0;
    r->field_names = nullptr;
    r->values = nullptr;

    return r;
}

// List of mock functions
extern "C" {
    PGconn* PQconnectdb(const char*) {
        return static_cast<PGconn*>(std::calloc(1, sizeof(PGconn)));
    }

    int PQstatus(const PGconn* c) {
        return c ? 0 : 1;
    }

    void PQfinish(PGconn* c) {
        std::free(c);
    }

    char* PQerrorMessage(const PGconn*) {
        return const_cast<char*>("");
    }

    PGresult* PQexec(PGconn* , const char* query) {
        if (g_fdp->ConsumeBool()) {
            return make_version_result();
        }
        return make_fuzz_result();
    }

    PGresult* PQexecParams(PGconn*, const char* cmd, int, const void*,
                           const char* const*, const int*, const int*, int) {
        if (g_fdp->ConsumeBool()) {
            return make_version_result();
        }
        return make_fuzz_result();
    }

    PGresult* PQprepare(PGconn*, const char*, const char*, int, const unsigned int*) {
        return make_command_ok_result();
    }

    PGresult* PQexecPrepared(PGconn*, const char* name, int, const char* const*,
                             const int*, const int*, int) {
        if (g_fdp->ConsumeBool()) {
            return make_version_result();
        }
        return make_fuzz_result();
    }

    int PQresultStatus(const PGresult* r) {
        return r ? r->status : PGRES_FATAL_ERROR;
     }

    int PQntuples(const PGresult* r) {
        return r ? r->ntuples : 0;
    }

    int PQnfields(const PGresult* r) {
        return r ? r->nfields : 0;
    }

    char* PQfname(const PGresult* r, int i) {
        if (r && i >= 0 && i < r->nfields) {
            return r->field_names[i];
        }
        return const_cast<char*>("");
    }

    char* PQgetvalue(const PGresult* r, int row, int col) {
        if (r && row == 0 && col >= 0 && col < r->nfields) {
            return r->values[col];
        }
        return const_cast<char*>("");
    }

    int PQgetlength(const PGresult* r, int, int col) {
        if (r && col >= 0 && col < r->nfields && r->values && r->values[col]) {
            return static_cast<int>(std::strlen(r->values[col]));
        }
        return 0;
    }

    int PQgetisnull(const PGresult*, int, int) {
        return 0;
    }

    int PQbinaryTuples(const PGresult*) {
        return 0;
    }

    int PQfformat(const PGresult*, int) {
        return 0;
    }

    int PQfsize(const PGresult*, int) {
        return -1;
    }

    void PQclear(PGresult* r) {
        if (!r) {
            return;
        }

        if (r->field_names) {
            for (int i=0; i<r->nfields; ++i) {
                if (r->field_names[i]) {
                    std::free(r->field_names[i]);
                }
            }
            std::free(r->field_names);
            r->field_names = nullptr;
        }

        const int count = (r->ntuples > 0 && r->nfields > 0)
                           ? r->ntuples * r->nfields : 0;
        if (r->values) {
            for (int i = 0; i < count; ++i) {
                if (r->values[i]) {
                    std::free(r->values[i]);
                }
            }
            std::free(r->values);
            r->values = nullptr;
        }

        std::free(r);
    }

    const char* PQcmdTuples(const PGresult*) {
        return "0";
    }

    char* PQresultErrorField(const PGresult*, int) {
        return const_cast<char*>("");
    }

    unsigned char* PQunescapeBytea(const unsigned char*, size_t* to_length) {
        if (to_length) {
            *to_length = 0;
        }

        unsigned char* p = static_cast<unsigned char*>(std::malloc(1));
        if (p) {
            p[0] = 0;
        }

        return p;
    }

    void PQfreemem(void* p) {
        std::free(p);
    }
}
