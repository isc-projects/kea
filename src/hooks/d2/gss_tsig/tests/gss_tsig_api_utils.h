// Copyright (C) 2021-2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef GSS_TSIG_API_UTILS_H
#define GSS_TSIG_API_UTILS_H

#include <gtest/gtest.h>
#include <cstdlib>

namespace isc {
namespace gss_tsig {
namespace test {

/// @brief Test fixture for testing the GSS-API with Kerberos 5.
class GssApiBaseTest : public ::testing::Test {
public:
    /// @brief Constructor.
    GssApiBaseTest() : has_tkname(false), tkname(""),
                   has_ccname(false), ccname("") {
        char* tkname_env = std::getenv("KRB5_KTNAME");
        if (tkname_env) {
            has_tkname = true;
            tkname = std::string(tkname_env);
        }
        char* ccname_env = std::getenv("KRB5CCNAME");
        if (ccname_env) {
            has_ccname = true;
            ccname = std::string(ccname_env);
        }
    }

    /// @brief Destructor.
    ~GssApiBaseTest() {
        if (has_tkname) {
            setenv("KRB5_KTNAME", tkname.c_str(), 1);
        } else {
            unsetenv("KRB5_KTNAME");
        }
        if (has_ccname) {
            setenv("KRB5CCNAME", ccname.c_str(), 1);
        } else {
            unsetenv("KRB5CCNAME");
        }
    }

    /// @brief Set the keytab.
    void setKeytab() {
        std::string keytab = std::string(TEST_DATA_DIR) + "/dns.keytab";
        setenv("KRB5_KTNAME", keytab.c_str(), 1);
    }

    /// @brief Set the administrator credential cache.
    void setAdministratorCCache() {
        std::string ccache = "FILE:";
        ccache += std::string(TEST_DATA_DIR) + "/administrator.ccache";
        setenv("KRB5CCNAME", ccache.c_str(), 1);
    }

    /// @brief Set the testdenied credential cache.
    void setTestdeniedCCache() {
        std::string ccache = "FILE:";
        ccache += std::string(TEST_DATA_DIR) + "/testdenied.ccache";
        setenv("KRB5CCNAME", ccache.c_str(), 1);
    }

    /// @brief KRB5_KTNAME environment variable existed before.
    bool has_tkname;

    /// @brief Previous value of KRB5_KTNAME environment variable.
    std::string tkname;

    /// @brief KRB5CCNAME environment variable existed before.
    bool has_ccname;

    /// @brief Previous value of KRB5CCNAME environment variable.
    std::string ccname;
};

} // end of isc::gss_tsig::test namespace
} // end of isc::gss_tsig namespace
} // end of isc namespace

#endif // GSS_TSIG_API_UTILS_H
