// Copyright (C) 2010  Internet Systems Consortium, Inc. ("ISC")
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

#include <config.h>

#include "datasrc_util.h"

#include <auth/auth_srv.h>
#include <auth/command.h>
#include <auth/datasrc_config.h>

#include <dns/name.h>
#include <dns/rrclass.h>
#include <dns/rrtype.h>
#include <dns/rrttl.h>

#include <cc/data.h>

#include <config/ccsession.h>

#include <datasrc/memory_datasrc.h>

#include <asiolink/asiolink.h>

#include <util/unittests/mock_socketsession.h>
#include <testutils/mockups.h>

#include <cassert>
#include <cstdlib>
#include <string>
#include <stdexcept>

#include <boost/bind.hpp>

#include <gtest/gtest.h>

#include <sys/types.h>
#include <unistd.h>

using namespace std;
using namespace isc::dns;
using namespace isc::data;
using namespace isc::datasrc;
using namespace isc::config;
using namespace isc::util::unittests;
using namespace isc::testutils;
using namespace isc::auth;
using namespace isc::auth::unittest;

namespace {

class AuthCommandTest : public ::testing::Test {
protected:
    AuthCommandTest() :
        server_(xfrout_, ddns_forwarder_),
        rcode_(-1),
        expect_rcode_(0),
        itimer_(server_.getIOService())
    {}
    void checkAnswer(const int expected_code, const char* name = "") {
        SCOPED_TRACE(name);

        parseAnswer(rcode_, result_);
        EXPECT_EQ(expected_code, rcode_) << result_->str();
    }
    MockXfroutClient xfrout_;
    MockSocketSessionForwarder ddns_forwarder_;
    AuthSrv server_;
    ConstElementPtr result_;
    // The shutdown command parameter
    ConstElementPtr param_;
    int rcode_, expect_rcode_;
    isc::asiolink::IntervalTimer itimer_;
public:
    void stopServer();          // need to be public for boost::bind
    void dontStopServer();          // need to be public for boost::bind
};

TEST_F(AuthCommandTest, unknownCommand) {
    result_ = execAuthServerCommand(server_, "no_such_command",
                                    ConstElementPtr());
    parseAnswer(rcode_, result_);
    EXPECT_EQ(1, rcode_);
}

TEST_F(AuthCommandTest, DISABLED_unexpectedException) {
    // execAuthServerCommand() won't catch standard exceptions.
    // Skip this test for now: ModuleCCSession doesn't seem to validate
    // commands.
    EXPECT_THROW(execAuthServerCommand(server_, "_throw_exception",
                                       ConstElementPtr()),
                 runtime_error);
}

void
AuthCommandTest::stopServer() {
    result_ = execAuthServerCommand(server_, "shutdown", param_);
    parseAnswer(rcode_, result_);
    assert(rcode_ == 0); // make sure the test stops when something is wrong
}

TEST_F(AuthCommandTest, shutdown) {
    // Param defaults to empty/null pointer on creation
    itimer_.setup(boost::bind(&AuthCommandTest::stopServer, this), 1);
    server_.getIOService().run();
    EXPECT_EQ(0, rcode_);
}

TEST_F(AuthCommandTest, shutdownCorrectPID) {
    // Put the pid parameter there
    const pid_t pid(getpid());
    ElementPtr param(new isc::data::MapElement());
    param->set("pid", ConstElementPtr(new isc::data::IntElement(pid)));
    param_ = param;
    // With the correct PID, it should act exactly the same as in case
    // of no parameter
    itimer_.setup(boost::bind(&AuthCommandTest::stopServer, this), 1);
    server_.getIOService().run();
    EXPECT_EQ(0, rcode_);
}

// This is like stopServer, but the server should not stop after the
// command, it should be running
void
AuthCommandTest::dontStopServer() {
    result_ = execAuthServerCommand(server_, "shutdown", param_);
    parseAnswer(rcode_, result_);
    EXPECT_EQ(expect_rcode_, rcode_);
    rcode_ = -1;
    // We run the stopServer now, to really stop the server.
    // If it had stopped already, it won't be run and the rcode -1 will
    // be left here.
    param_ = ConstElementPtr();
    itimer_.cancel();
    itimer_.setup(boost::bind(&AuthCommandTest::stopServer, this), 1);
}

// If we provide something not an int, the PID is not really specified, so
// act as if nothing came.
TEST_F(AuthCommandTest, shutdownNotInt) {
    // Put the pid parameter there
    ElementPtr param(new isc::data::MapElement());
    param->set("pid", ConstElementPtr(new isc::data::StringElement("pid")));
    param_ = param;
    expect_rcode_ = 1;
    // It should reject to stop if the PID is not an int.
    itimer_.setup(boost::bind(&AuthCommandTest::dontStopServer, this), 1);
    server_.getIOService().run();
    EXPECT_EQ(0, rcode_);
}

TEST_F(AuthCommandTest, shutdownIncorrectPID) {
    // The PID = 0 should be taken by init, so we are not init and the
    // PID should be different
    param_ = Element::fromJSON("{\"pid\": 0}");
    itimer_.setup(boost::bind(&AuthCommandTest::dontStopServer, this), 1);
    server_.getIOService().run();
    EXPECT_EQ(0, rcode_);
}

TEST_F(AuthCommandTest, getStats) {
    result_ = execAuthServerCommand(server_, "getstats", ConstElementPtr());
    parseAnswer(rcode_, result_);
    // Just check the command execution succeeded.  Detailed tests specific to
    // statistics are done in its own tests.
    EXPECT_EQ(0, rcode_);
}
}
