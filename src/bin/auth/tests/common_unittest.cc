// Copyright (C) 2011  Internet Systems Consortium, Inc. ("ISC")
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

#include <gtest/gtest.h>
#include <auth/common.h>
#include <auth/spec_config.h>
#include <vector>
#include <string>
#include <cstdio>
#include <boost/foreach.hpp>

using std::pair;
using std::vector;
using std::string;

namespace {

class Paths : public ::testing::Test {
private:
    typedef pair<string, string*> Environ;
    vector<Environ> restoreEnviron;
public:
    void TearDown() {
        // Restore the original environment
        BOOST_FOREACH(const Environ &env, restoreEnviron) {
            if (env.second == NULL) {
                EXPECT_EQ(0, unsetenv(env.first.c_str())) <<
                    "Couldn't restore environment, results of other tests "
                    "are uncertain";
            } else {
                EXPECT_EQ(0, setenv(env.first.c_str(), env.second->c_str(),
                                    1)) << "Couldn't restore environment, "
                    "results of other tests are uncertain";
            }
        }
    }
protected:
    // Sets a temporary value into environment. If value is empty, it deletes
    // the variable from environment (just for simplicity).
    void setEnv(const string& name, const string& value) {
        // Backup the original environment
        char* env(getenv(name.c_str()));
        restoreEnviron.push_back(Environ(name, env == NULL ? NULL :
                                         new string(env)));
        // Set the new value
        if (value.empty()) {
            EXPECT_EQ(0, unsetenv(name.c_str()));
        } else {
            EXPECT_EQ(0, setenv(name.c_str(), value.c_str(), 1));
        }
    }
    // Test getter functions for a socket file path under given environment
    void testSocketPath(const string& fromBuild, const string& localStateDir,
                        const string& socketFile, const string& env_name,
                        const string& expected, string (*actual_fn)())
    {
        setEnv("B10_FROM_BUILD", fromBuild);
        setEnv("B10_FROM_SOURCE_LOCALSTATEDIR", localStateDir);
        setEnv(env_name, socketFile);
        EXPECT_EQ(expected, actual_fn());
    }
};

// Test that when we have no special environment, we get the default from prefix
TEST_F(Paths, xfroutNoEnv) {
    testSocketPath("", "", "", "BIND10_XFROUT_SOCKET_FILE",
                   UNIX_XFROUT_SOCKET_FILE, getXfroutSocketPath);
}

TEST_F(Paths, ddnsNoEnv) {
    testSocketPath("", "", "", "BIND10_DDNS_SOCKET_FILE",
                   UNIX_DDNS_SOCKET_FILE, getDDNSSocketPath);
}

// Override by B10_FROM_BUILD
TEST_F(Paths, xfroutFromBuild) {
    testSocketPath("/from/build", "", "/wrong/path",
                   "BIND10_XFROUT_SOCKET_FILE", "/from/build/auth_xfrout_conn",
                   getXfroutSocketPath);
}

TEST_F(Paths, ddnsFromBuild) {
    testSocketPath("/from/build", "", "/wrong/path", "BIND10_DDNS_SOCKET_FILE",
                   "/from/build/ddns_socket", getDDNSSocketPath);
}

// Override by B10_FROM_SOURCE_LOCALSTATEDIR
TEST_F(Paths, xfroutLocalStatedir) {
    testSocketPath("/wrong/path", "/state/dir", "/wrong/path",
                   "BIND10_XFROUT_SOCKET_FILE", "/state/dir/auth_xfrout_conn",
                   getXfroutSocketPath);
}

TEST_F(Paths, ddnsLocalStatedir) {
    testSocketPath("/wrong/path", "/state/dir", "/wrong/path",
                   "BIND10_DDNS_SOCKET_FILE", "/state/dir/ddns_socket",
                   getDDNSSocketPath);
}

// Override by BIND10_xxx_SOCKET_FILE explicitly
TEST_F(Paths, xfroutFromEnv) {
    testSocketPath("", "", "/the/path/to/file", "BIND10_XFROUT_SOCKET_FILE",
                   "/the/path/to/file", getXfroutSocketPath);
}

TEST_F(Paths, ddnsFromEnv) {
    testSocketPath("", "", "/the/path/to/file", "BIND10_DDNS_SOCKET_FILE",
                   "/the/path/to/file", getDDNSSocketPath);
}

}
