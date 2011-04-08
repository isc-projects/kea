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

#include <gtest/gtest.h>
#include <asiodns/dns_server.h>
#include <resolve/resolver_callback.h>

using namespace isc::resolve;

// Dummy subclass for DNSServer*
// We want to check if resume is called
// Since the server will get cloned(), we want the clones to share
// our bools for whether resume got called and with what value
class DummyServer : public isc::asiodns::DNSServer {
public:
    DummyServer(DummyServer* orig) {
        resume_called_ = orig->getResumeCalled();
        resume_value_ = orig->getResumeValue();
    }
    DummyServer(bool* resume_called, bool* resume_value) :
        resume_called_(resume_called), resume_value_(resume_value)
    {}

    bool* getResumeCalled() { return resume_called_; }
    bool* getResumeValue() { return resume_value_; }

    DNSServer* clone() {
        DummyServer* n = new DummyServer(this);
        return n;
    }

    void resume(bool value) {
        *resume_called_ = true;
        *resume_value_ = value;
    }

private:
    bool* resume_called_;
    bool* resume_value_;
};

class ResolverCallbackServerTest : public ::testing::Test {
public:
    ResolverCallbackServerTest() : resume_called_(false),
                                   resume_value_(false) {
        server_ = new DummyServer(&resume_called_, &resume_value_);
        callback_ = new ResolverCallbackServer(server_);
    };

    ~ResolverCallbackServerTest() {
        delete callback_;
        delete server_;
    }

    DummyServer* getServer() { return server_; }
    ResolverCallbackServer* getCallback() { return callback_; }
    bool getResumeCalled() { return resume_called_; }
    bool getResumeValue() { return resume_value_; }

private:
    DummyServer* server_;
    ResolverCallbackServer* callback_;
    bool resume_called_;
    bool resume_value_;
};

TEST_F(ResolverCallbackServerTest, testSuccess) {
    EXPECT_FALSE(getResumeCalled());
    getCallback()->success(isc::dns::MessagePtr());
    EXPECT_TRUE(getResumeCalled());
    EXPECT_TRUE(getResumeValue());
}

TEST_F(ResolverCallbackServerTest, testFailure) {
    EXPECT_FALSE(getResumeCalled());
    getCallback()->failure();
    EXPECT_TRUE(getResumeCalled());
    EXPECT_FALSE(getResumeValue());
}
