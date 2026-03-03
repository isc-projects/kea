// Copyright (C) 2025 Ada Logcis Ltd.
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
////////////////////////////////////////////////////////////////////////////////
#include <fuzzer/FuzzedDataProvider.h>

#include <mariadb/mysql.h>

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>

struct StmtState;

static thread_local FuzzedDataProvider* g_fdp = nullptr;
static thread_local std::string g_mysql_error;
static thread_local std::string g_stmt_error;
static thread_local std::string g_tls_cipher;

struct MockResRow {
    enum ColKind {
        CK_UINT64, CK_UINT32, CK_UINT8, CK_STRING, CK_BLOB
    } kind;
    std::string s;
    std::vector<uint8_t> blob;
    uint64_t u64 = 0;
    uint32_t u32 = 0;
    uint8_t u8 = 0;
};

struct StmtState {
    MYSQL* mysql;
    std::string sql;
    std::vector<std::vector<MockResRow>> rows;
    size_t fetch_index = 0;
    MYSQL_BIND* res_binds = nullptr;
    size_t res_binds_count = 0;
    bool has_rows = false;
    bool is_version_stmt = false;
    unsigned int field_count = 0;
};

static thread_local std::unordered_map<MYSQL_STMT*, StmtState*> g_stmt_state;
static thread_local std::vector<MYSQL_STMT*> g_all_stmts;
static thread_local std::vector<StmtState*> g_live_stmts;

extern "C" void mysqlmock_load_bytes(const uint8_t* data, size_t size) {
    for (auto* st : g_all_stmts) {
       free(st);
    }
    g_all_stmts.clear();
    for (auto& kv : g_stmt_state) {
        delete kv.second;
    }
    g_stmt_state.clear();
    g_stmt_state.rehash(0);
    delete g_fdp;
    g_fdp = new FuzzedDataProvider(data, size);
}

static bool is_like(const std::string& hay, const char* needle) {
    std::string h = hay;
    std::string n = needle ? needle : "";
    std::transform(h.begin(), h.end(), h.begin(), ::tolower);
    std::transform(n.begin(), n.end(), n.begin(), ::tolower);
    return h.find(n) != std::string::npos;
}

static MYSQL_STMT* make_stmt() {
    auto s = new StmtState();
    s->mysql = reinterpret_cast<MYSQL*>(0x1);
    g_live_stmts.push_back(s);
    return reinterpret_cast<MYSQL_STMT*>(s);
}

static StmtState* SS(MYSQL_STMT* st) {
    if (!st) {
        return nullptr;
    }
    auto it = g_stmt_state.find(st);
    return (it == g_stmt_state.end()) ? nullptr : it->second;
}

static StmtState* ensure_state(MYSQL_STMT* st) {
    auto s = SS(st);
    if (s) return s;
    s = new StmtState();
    s->mysql = reinterpret_cast<MYSQL*>(0x1);
    g_stmt_state[st] = s;
    g_live_stmts.push_back(s);
    return s;
}

static unsigned int infer_field_count_from_sql(const std::string& sql) {
    std::string s = sql;
    std::transform(s.begin(), s.end(), s.begin(), ::tolower);
    auto psel = s.find("select");
    if (psel == std::string::npos) {
        return 0;
    }
    auto pfrom = s.find(" from ", psel);
    if (pfrom == std::string::npos) {
        return 0;
    }
    std::string proj = s.substr(psel + 6, pfrom - (psel + 6));

    proj.erase(0, proj.find_first_not_of(" \t\r\n"));
    proj.erase(proj.find_last_not_of(" \t\r\n")+1);
    if (proj.rfind("distinct", 0) == 0) {
        proj.erase(0, 8);
        proj.erase(0, proj.find_first_not_of(" \t\r\n"));
    }

    unsigned int cols = 0;
    int paren = 0;
    bool in_s = false, in_d = false;
    for (size_t i = 0; i < proj.size(); ++i) {
        char c = proj[i];
        if (!in_d && c=='\'' && (i==0 || proj[i-1] != '\\')) {
            in_s = !in_s;
        } else if (!in_s && c=='"' && (i==0 || proj[i-1] != '\\')) {
            in_d = !in_d;
        } else if (!in_s && !in_d) {
            if (c=='(') {
                paren++;
            } else if (c==')' && paren>0) {
                paren--;
            } else if (c==',' && paren==0) {
                cols++;
            }
        }
    }
    if (!proj.empty()) {
        cols++;
    }
    return cols;
}

static void fill_version_stmt(StmtState* s) {
    s->is_version_stmt = true;
    s->has_rows = true;
    s->rows.clear();
    s->field_count = 2;
    std::vector<MockResRow> r;
    MockResRow c1;
    c1.kind = MockResRow::CK_UINT32;
    c1.u32 = 32;
    MockResRow c2;
    c2.kind = MockResRow::CK_UINT32;
    c2.u32 = 0;
    r.push_back(c1);
    r.push_back(c2);
    s->rows.push_back(r);
}

static void fill_no_rows(StmtState* s, unsigned int cols = 0) {
    s->is_version_stmt = false;
    s->has_rows = false;
    s->rows.clear();
    s->fetch_index = 0;
    s->field_count = cols;
}

static void fill_fuzz_rows(StmtState* s, unsigned int ncols) {
    s->is_version_stmt = false;
    s->has_rows = true;
    s->rows.clear();
    s->fetch_index = 0;
    s->field_count = ncols ? ncols : 1;;
    unsigned int nrows = g_fdp->ConsumeIntegralInRange<unsigned int>(1, 3);
    for (unsigned int r = 0; r < nrows; ++r) {
        std::vector<MockResRow> row;
        row.reserve(ncols);
        for (unsigned int c = 0; c < ncols; ++c) {
            int k = g_fdp->ConsumeIntegralInRange<int>(0, 4);
            MockResRow cell;
            switch (k) {
                case 0:
                    cell.kind = MockResRow::CK_UINT64;
                    cell.u64 = g_fdp->ConsumeIntegral<uint64_t>();
                    break;
                case 1:
                    cell.kind = MockResRow::CK_UINT32;
                    cell.u32 = g_fdp->ConsumeIntegral<uint32_t>();
                    break;
                case 2:
                    cell.kind = MockResRow::CK_UINT8;
                    cell.u8 = g_fdp->ConsumeIntegral<uint8_t>();
                    break;
                case 3:
                    cell.kind = MockResRow::CK_STRING;
                    cell.s = g_fdp->ConsumeRandomLengthString(32);
                    break;
                case 4: {
                    cell.kind = MockResRow::CK_BLOB;
                    size_t n = g_fdp->ConsumeIntegralInRange<size_t>(0, 32);
                    cell.blob = g_fdp->ConsumeBytes<uint8_t>(n);
                    break;
                }
            }
            row.push_back(cell);
        }
        s->rows.push_back(std::move(row));
    }
}

extern "C" {
    int mysql_server_init(int argc, char **argv, char **groups) {
        return 0;
    }

    MYSQL* mysql_init(MYSQL* in) {
        return in ? in : reinterpret_cast<MYSQL*>(0x1);
    }

    void mysql_close(MYSQL*) {}

    void mysql_free_result(MYSQL_RES*) {}

    void mysql_server_end(void) {}

    MYSQL* mysql_real_connect(MYSQL* mysql,
                              const char*,
                              const char*,
                              const char*,
                              const char*,
                              unsigned int,
                              const char*,
                              unsigned long) {
        return mysql ? mysql : reinterpret_cast<MYSQL*>(0x1);
    }

    unsigned int mysql_errno(MYSQL*) {
        return 0;
    }

    const char* mysql_error(MYSQL*) {
        g_mysql_error = g_fdp ? g_fdp->ConsumeRandomLengthString(32) : std::string();
        return g_mysql_error.c_str();
    }

    MYSQL_STMT* mysql_stmt_init(MYSQL*) {
        auto* stmt = static_cast<MYSQL_STMT*>(std::calloc(1, sizeof(MYSQL_STMT)));
        if (!stmt) {
            return nullptr;
        }
        stmt->mysql = reinterpret_cast<MYSQL*>(0x1);
        g_all_stmts.push_back(stmt);
        auto* s = ensure_state(stmt);
        s->mysql = stmt->mysql;
        return stmt;
    }

    int mysql_stmt_prepare(MYSQL_STMT* stmt, const char* q, unsigned long len) {
        if (!stmt) {
            return 1;
        }
        stmt->mysql = reinterpret_cast<MYSQL*>(0x1);
        auto* s = ensure_state(stmt);

        const uintptr_t pq = reinterpret_cast<uintptr_t>(q);
        const bool ptr_ok  = (q != nullptr) && (pq > 0x10000);
        const bool len_ok  = (len > 0);
        if (ptr_ok && len_ok) {
            size_t copy_len = std::min<size_t>(len, 4096);
            s->sql.assign(q, copy_len);
        } else {
            s->sql = "SELECT version, minor FROM schema_version";
        }

        if (is_like(s->sql, "schema_version") || is_like(s->sql, "select version") || is_like(s->sql, "get_version")) {
            fill_version_stmt(s);
            return 0;
        }

        unsigned int cols = infer_field_count_from_sql(s->sql);
        if (cols == 0) {
            cols = g_fdp->ConsumeIntegralInRange<unsigned int>(1, 8);
        }
        s->field_count = cols;

        if (g_fdp->ConsumeBool()) {
            fill_fuzz_rows(s, cols);
        } else {
            fill_no_rows(s);
        }
        return 0;
    }

    my_bool mysql_stmt_close(MYSQL_STMT* stmt) {
        if (stmt) {
            auto it = g_stmt_state.find(stmt);
            if (it != g_stmt_state.end()) {
                delete it->second;
                g_stmt_state.erase(it);
                if (g_stmt_state.empty()) {
                    g_stmt_state.rehash(0);
                }
            }
            auto it2 = std::find(g_all_stmts.begin(), g_all_stmts.end(), stmt);
            if (it2 != g_all_stmts.end()) {
                g_all_stmts.erase(it2);
            }
            free(stmt);
        }
        return 0;
    }

    my_bool mysql_stmt_bind_result(MYSQL_STMT* stmt, MYSQL_BIND* bnd) {
        auto* s = ensure_state(stmt);
        s->res_binds = bnd;
        s->res_binds_count = bnd ? static_cast<size_t>(mysql_stmt_field_count(stmt)) : 0;
        return 0;
    }

    int mysql_stmt_execute(MYSQL_STMT*) {
        return 0;
    }

    int mysql_stmt_store_result(MYSQL_STMT*) {
        return 0;
    }

    my_bool mysql_stmt_free_result(MYSQL_STMT* stmt) {
        auto s = SS(stmt);
        if (s) {
            s->fetch_index = 0;
        }
        if (stmt) {
            stmt->mysql = reinterpret_cast<MYSQL*>(0x1);
        }
        return 0;
    }

    my_ulonglong mysql_stmt_affected_rows(MYSQL_STMT*) {
        return 0ULL;
    }

    my_bool mysql_stmt_reset(MYSQL_STMT* stmt) {
        auto s = SS(stmt);
        if (s) {
            s->fetch_index = 0;
        }
        if (stmt) {
            stmt->mysql = reinterpret_cast<MYSQL*>(0x1);
        }
        return 0;
    }

    unsigned int mysql_stmt_errno(MYSQL_STMT*) {
        return 0;
    }

    const char* mysql_stmt_error(MYSQL_STMT*) {
        g_stmt_error = g_fdp ? g_fdp->ConsumeRandomLengthString(32) : std::string();
        return g_stmt_error.c_str();
    }

    int mysql_options(MYSQL*, enum mysql_option, const void*) {
        return 0;
    }

    my_bool mysql_autocommit(MYSQL*, my_bool) {
        return 0;
    }

    my_bool mysql_commit(MYSQL*) {
        return 0;
    }

    my_bool mysql_rollback(MYSQL*) {
        return 0;
    }

    int mysql_query(MYSQL*, const char*) {
        return 0;
    }

    my_bool mysql_stmt_bind_param(MYSQL_STMT*, MYSQL_BIND*) {
        return 0;
    }

    unsigned int mysql_stmt_field_count(MYSQL_STMT* stmt) {
        auto s = SS(stmt);
        return s ? s->field_count : 0u;
    }

    MYSQL_RES* mysql_stmt_result_metadata(MYSQL_STMT* stmt) {
        auto s = SS(stmt);
        if (!s) {
            return reinterpret_cast<MYSQL_RES*>(0x1);
        }
        if (s->is_version_stmt) {
            return reinterpret_cast<MYSQL_RES*>(0x1);
        }
        return nullptr;
    }

    my_ulonglong mysql_insert_id(MYSQL*) {
        return g_fdp ? g_fdp->ConsumeIntegral<my_ulonglong>() : 0ULL;
    }

    const char* mysql_get_ssl_cipher(MYSQL*) {
        if (g_fdp && g_fdp->ConsumeBool()) {
            g_tls_cipher = g_fdp->ConsumeRandomLengthString(64);
            return g_tls_cipher.c_str();
        }
        return "TLS_FAKE_CIPHER_WITH_FAKE_SHA256";
    }

    int mysql_stmt_fetch(MYSQL_STMT* stmt) {
        auto s = SS(stmt);

        if (!s || !s->has_rows){
             return MYSQL_NO_DATA;
        }
        if (s->fetch_index >= s->rows.size()) {
            return MYSQL_NO_DATA;
        }
        if (!s->res_binds) {
            return MYSQL_NO_DATA;
        }

        const auto& row = s->rows[s->fetch_index++];
        size_t cols = row.size();
        if (s->field_count && cols > s->field_count) {
            cols = s->field_count;
        }
        if (cols > s->res_binds_count) {
            cols = s->res_binds_count;
        }

        for (size_t i = 0; i < cols; ++i) {
            const auto& cell = row[i];
            MYSQL_BIND& b = s->res_binds[i];
            if (!b.buffer) {
                continue;
            }
            switch (cell.kind) {
                case MockResRow::CK_UINT32: {
                    uint32_t v = cell.u32;
                    if (b.buffer_length == 0 || b.buffer_length >= sizeof(v)) {
                        memcpy(b.buffer, &v, sizeof(v));
                        if (b.length) *b.length = sizeof(v);
                    }
                    break;
                }
                case MockResRow::CK_UINT64: {
                    uint64_t v = cell.u64;
                    if (b.buffer_length == 0 || b.buffer_length >= sizeof(v)) {
                        memcpy(b.buffer, &v, sizeof(v));
                        if (b.length) *b.length = sizeof(v);
                    }
                    break;
                }
                case MockResRow::CK_UINT8: {
                    uint8_t v = cell.u8;
                    if (b.buffer_length == 0 || b.buffer_length >= sizeof(v)) {
                        memcpy(b.buffer, &v, sizeof(v));
                        if (b.length) *b.length = sizeof(v);
                    }
                    break;
                }
                case MockResRow::CK_STRING: {
                    if (b.buffer_length > 0) {
                        size_t n = std::min<size_t>(b.buffer_length - 1, cell.s.size());
                        memcpy(b.buffer, cell.s.data(), n);
                        reinterpret_cast<char*>(b.buffer)[n] = '\0';
                        if (b.length) *b.length = n;
                    }
                    break;
                }
                case MockResRow::CK_BLOB: {
                    if (b.buffer_length > 0) {
                        size_t n = std::min<size_t>(b.buffer_length, cell.blob.size());
                        memcpy(b.buffer, cell.blob.data(), n);
                        if (b.length) *b.length = n;
                    }
                    break;
                }
            }
        }
        return 0;
    }
}
