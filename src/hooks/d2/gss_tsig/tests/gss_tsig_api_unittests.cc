// Copyright (C) 2021-2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <dns/time_utils.h>
#include <gss_tsig_api.h>
#include <gss_tsig_api_utils.h>
#include <testutils/gtest_utils.h>
#include <gtest/gtest.h>
#include <cstdlib>

using namespace std;
using namespace isc;
using namespace isc::gss_tsig;
using namespace isc::gss_tsig::test;
using namespace isc::util;

namespace {

/// @brief Test fixture for testing the GSS-API with Kerberos 5.
class GssApiTest : public GssApiBaseTest {
};

/// @brief Check if the GssApiBuffer constructors build the buffer properly.
TEST_F(GssApiTest, buffer) {
    GssApiBufferPtr buf;
    EXPECT_NO_THROW(buf.reset(new GssApiBuffer()));
    ASSERT_TRUE(buf);
    ASSERT_TRUE(buf->getPtr());
    EXPECT_EQ(0, buf->getLength());
    EXPECT_FALSE(buf->getValue());
    EXPECT_TRUE(buf->empty());
    const vector<uint8_t>& empty = buf->getContent();
    EXPECT_EQ(0, empty.size());

    const vector<uint8_t>& test = { 1, 2, 3, 0 };
    EXPECT_NO_THROW(buf.reset(new GssApiBuffer(test)));
    ASSERT_TRUE(buf);
    ASSERT_TRUE(buf->getPtr());
    EXPECT_EQ(4, buf->getLength());
    EXPECT_TRUE(buf->getValue());
    EXPECT_FALSE(buf->empty());
    const vector<uint8_t>& content = buf->getContent();
    ASSERT_EQ(4, content.size());
    EXPECT_EQ(0, memcmp(&test[0], &content[0], 4));

    const string& strpp = buf->getString();
    string expected("\x1\x2\x3\0");
    // Enforce the embedded nul.
    expected.resize(4);
    EXPECT_EQ(expected, strpp);
    EXPECT_EQ(4, strpp.size());
    EXPECT_EQ(3, strlen(strpp.c_str()));
    EXPECT_NO_THROW(buf.reset(new GssApiBuffer(strpp)));
    ASSERT_TRUE(buf);
    ASSERT_TRUE(buf->getPtr());
    EXPECT_EQ(4, buf->getLength());
    EXPECT_TRUE(buf->getValue());
    EXPECT_FALSE(buf->empty());
    EXPECT_EQ(0, memcmp(&test[0], buf->getValue(), 4));

    const string& str = buf->getString(true);
    // Trim the embedded nul.
    expected.resize(3);
    EXPECT_EQ(expected, str);
    EXPECT_EQ(3, str.size());
    EXPECT_EQ(3, strlen(str.c_str()));
    EXPECT_NO_THROW(buf.reset(new GssApiBuffer(str)));
    ASSERT_TRUE(buf);
    ASSERT_TRUE(buf->getPtr());
    EXPECT_EQ(3, buf->getLength());
    EXPECT_TRUE(buf->getValue());
    EXPECT_FALSE(buf->empty());
    EXPECT_EQ(0, memcmp(&test[0], buf->getValue(), 4));

    EXPECT_NO_THROW(buf.reset(new GssApiBuffer(4, &test[0])));
    ASSERT_TRUE(buf);
    ASSERT_TRUE(buf->getPtr());
    EXPECT_EQ(4, buf->getLength());
    EXPECT_TRUE(buf->getValue());
    EXPECT_FALSE(buf->empty());
    EXPECT_EQ(0, memcmp(&test[0], buf->getValue(), 4));
}

/// @brief Verify the GSS-API error message display.
TEST_F(GssApiTest, errorMessage) {
    string msg = gssApiErrMsg(GSS_S_COMPLETE, GSS_S_COMPLETE);
    string expected = "GSSAPI error: Major = '";
#ifndef WITH_HEIMDAL
    expected += "The routine completed successfully' (0).";
#else
    expected += " Function completed successfully' (0).";
#endif
    EXPECT_EQ(expected, msg);

    msg = gssApiErrMsg(GSS_S_BAD_NAME, GSS_S_COMPLETE);
    expected = "GSSAPI error: Major = '";
#ifndef WITH_HEIMDAL
    expected += "An invalid name was supplied' (131072).";
#else
    expected += " An invalid name was supplied' (131072).";
#endif
    EXPECT_EQ(expected, msg);
}

/// @brief Check the GSS-API name.
TEST_F(GssApiTest, name) {
    GssApiNamePtr name;
    EXPECT_NO_THROW(name.reset(new GssApiName()));
    ASSERT_TRUE(name);
    EXPECT_FALSE(name->get());
    EXPECT_EQ(0, name->getLastError());
    string expected = "gss_display_name failed with GSSAPI error: Major = '";
#ifndef WITH_HEIMDAL
    expected += "A required input parameter could not be read' (16908288).";
    OM_uint32 expected_major = 0x1020000;
#else
    expected += " An invalid name was supplied' (131072).";
    OM_uint32 expected_major = 0x20000;
#endif
    EXPECT_THROW_MSG(name->toString(), GssApiError, expected);
    EXPECT_EQ(expected_major, name->getLastError());

    string principal = "DNS/server.example.org@EXAMPLE.NET";
    EXPECT_NO_THROW(name.reset(new GssApiName(principal)));
    ASSERT_TRUE(name);
    ASSERT_TRUE(name->get());

    string principal2 = "DNS/server2.example.org@EXAMPLE.NET";
    GssApiNamePtr name2;
    EXPECT_NO_THROW(name2.reset(new GssApiName(principal2)));
    ASSERT_TRUE(name2);
    ASSERT_TRUE(name2->get());
    EXPECT_TRUE(name->compare(*name));
    EXPECT_TRUE(name2->compare(*name2));
    EXPECT_FALSE(name2->compare(*name));
    EXPECT_FALSE(name->compare(*name2));

    string text;
    EXPECT_NO_THROW(text = name->toString());
    expected = "DNS/server.example.org@EXAMPLE.NET";
    EXPECT_EQ(expected, text);
}

/// @brief Check the GSS-API OID.
TEST_F(GssApiTest, oid) {
    GssApiOidPtr oid;
    EXPECT_NO_THROW(oid.reset(new GssApiOid()));
    ASSERT_TRUE(oid);
    string expected = "gss_oid_to_str failed with ";
    expected += "GSSAPI error: Major = '";
#ifndef WITH_HEIMDAL
    expected += "A required input parameter could not be read' (16777216).";
#else
    expected += " Miscellaneous failure (see text)' (851968), Minor = '";
    expected += "unknown mech-code 1859794437 for mech unknown' (1859794437).";
#endif
    EXPECT_THROW_MSG(oid->toString(), GssApiError, expected);

    vector<uint8_t> bin =
        { 0x2a, 0x86, 0x48, 0x86, 0xf7, 0x12, 0x01, 0x02, 0x02 };
    EXPECT_NO_THROW(oid.reset(new GssApiOid(bin)));
    ASSERT_TRUE(oid);

    string txt;
    EXPECT_NO_THROW(txt = oid->toString());
#ifndef WITH_HEIMDAL
    EXPECT_EQ("{ 1 2 840 113554 1 2 2 }", txt);
#else
    EXPECT_EQ("1 2 840 113554 1 2 2", txt);
#endif

#ifdef HAVE_GSS_STR_TO_OID
    EXPECT_NO_THROW(oid.reset(new GssApiOid("{ 1 2 840 113554 1 2 2 }")));
    ASSERT_TRUE(oid);
#endif
}

/// @brief Check the GSS-API credential default.
/// The spec says the default credential makes sense only on the accept side
/// and Heimdal follows this a bit too much...
TEST_F(GssApiTest, credDefault) {
    setAdministratorCCache();

    GssApiCredPtr cred;
    EXPECT_NO_THROW(cred.reset(new GssApiCred()));
    ASSERT_TRUE(cred);
    EXPECT_FALSE(cred->get());
    EXPECT_EQ(0, cred->getLastError());

    GssApiName name;
    gss_cred_usage_t usage = 0;
    OM_uint32 lifetime = 0;
    EXPECT_NO_THROW(cred->inquire(name, usage, lifetime));
    EXPECT_TRUE(name.get());
    // lifetime == 0 means expired.
    EXPECT_NE(0, lifetime);
    const uint64_t now = static_cast<uint64_t>(time(0));
    // krbtgt/EXAMPLE.NIL@EXAMPLE.NIL cached credential expires at
    // Apr 6 19:04:36 2036.
    const uint64_t expire = timeFromText64("20260406190436");
    EXPECT_LE(expire, now + lifetime);
#ifndef WITH_HEIMDAL
    string admin;
    EXPECT_NO_THROW(admin = name.toString());
    EXPECT_EQ("administrator@EXAMPLE.NIL", admin);
    EXPECT_EQ(GSS_C_INITIATE, usage);
#endif
}

/// @brief Check the GSS-API credential for an explicit principal.
TEST_F(GssApiTest, credExplicit) {
    setKeytab();

    GssApiCredPtr cred;
    GssApiName name("DNS/blu.example.nil@EXAMPLE.NIL");
    OM_uint32 lifetime = 0;
    EXPECT_NO_THROW(cred.reset(new GssApiCred(name, GSS_C_ACCEPT,
                                              lifetime)));
    EXPECT_NE(0, lifetime);
    ASSERT_TRUE(cred);
    EXPECT_TRUE(cred->get());
    EXPECT_EQ(0, cred->getLastError());
    GssApiNamePtr namep(new GssApiName());
    gss_cred_usage_t usage = 0;
    lifetime = 0;
    EXPECT_NO_THROW(cred->inquire(*namep, usage, lifetime));
    EXPECT_TRUE(namep->get());
    EXPECT_TRUE(namep->compare(name));
    EXPECT_EQ(GSS_C_ACCEPT, usage);
    // lifetime == 0 means expired.
    EXPECT_NE(0, lifetime);
    const uint64_t now = static_cast<uint64_t>(time(0));
    // DNS/blu.example.nil@EXAMPLE.NIL cached credential expires at
    // Apr 6 19:04:36 2036.
    const uint64_t expire = timeFromText64("20260406190436");
    EXPECT_LE(expire, now + lifetime);
}

/// @brief Check the GSS-API credential for a principal in another realm
/// (here we use no realm as EXAMPLE.NIL is very unlikely the local default).
TEST_F(GssApiTest, credNoRealm) {
    setKeytab();

    GssApiCredPtr cred;
    GssApiName name("DNS/blu.example.nil");
    OM_uint32 lifetime = 0;
    // Various error messages explaining a reason to fail to acquire the
    // the credential.
    EXPECT_THROW(cred.reset(new GssApiCred(name, GSS_C_ACCEPT, lifetime)),
                 GssApiError);
}

/// @brief Check the GSS-API credential for a principal with another service.
TEST_F(GssApiTest, credBadService) {
    setKeytab();

    GssApiCredPtr cred;
    GssApiName name("Foo/blu.example.nil@EXAMPLE.NIL");
    OM_uint32 lifetime = 0;
    // Various error messages explaining a reason to fail to acquire the
    // the credential.
    EXPECT_THROW(cred.reset(new GssApiCred(name, GSS_C_ACCEPT, lifetime)),
                 GssApiError);
}

/// @brief Check the GSS-API credential for another principal.
TEST_F(GssApiTest, credBadName) {
    // Use the other credential cache.
    setTestdeniedCCache();

    GssApiCredPtr cred;
    GssApiName name("administrator@EXAMPLE.NIL");
    OM_uint32 lifetime = 0;
    // Various error messages explaining a reason to fail to acquire the
    // the credential.
    EXPECT_THROW(cred.reset(new GssApiCred(name, GSS_C_INITIATE, lifetime)),
                 GssApiError);
}

/// @brief Check GSS-API exchange.
TEST_F(GssApiTest, exchange) {
    setKeytab();
    setAdministratorCCache();

    // Server.
    GssApiSecCtx srv_ctx(GSS_C_NO_CONTEXT);
    GssApiCredPtr srv_cred;
    GssApiName srv_name("DNS/blu.example.nil@EXAMPLE.NIL");
    OM_uint32 srv_lifetime = 0;
    EXPECT_NO_THROW(srv_cred.reset(new GssApiCred(srv_name, GSS_C_ACCEPT,
                                                  srv_lifetime)));
    ASSERT_TRUE(srv_cred);
    ASSERT_TRUE(srv_cred->get());

    // Client.
    GssApiSecCtx clnt_ctx(GSS_C_NO_CONTEXT);
    GssApiCredPtr clnt_cred;
    GssApiName clnt_name;
    OM_uint32 flags = GSS_C_REPLAY_FLAG | GSS_C_MUTUAL_FLAG | GSS_C_INTEG_FLAG;
    /// @todo: the standard requires this sequence flag but BIND 9 code
    /// does not set it because it disturbs (disturbed) Windows DNS servers.
    /// flags |= GSS_C_SEQUENCE_FLAG;
    OM_uint32 clnt_lifetime = 0;

    // Exchange loop.
    size_t loop = 0;
    bool clnt_ret = false;
    bool srv_ret = false;
    GssApiBufferPtr clnt_to_srv(new GssApiBuffer());
    GssApiBufferPtr srv_to_clnt(new GssApiBuffer());
    while (!clnt_ret) {
        ++loop;
        clnt_to_srv.reset(new GssApiBuffer());
        clnt_ret = clnt_ctx.init(clnt_cred, srv_name, flags, *srv_to_clnt,
                                 *clnt_to_srv, clnt_lifetime);
        if (!clnt_to_srv->empty()) {
            srv_to_clnt.reset(new GssApiBuffer());
            srv_ret = srv_ctx.accept(*srv_cred, *clnt_to_srv, clnt_name,
                                     *srv_to_clnt);
            if (srv_to_clnt->empty()) {
                break;
            }
        }
    }
    EXPECT_EQ(2, loop);
    ASSERT_TRUE(clnt_ret);
    ASSERT_TRUE(clnt_ctx.get());
    EXPECT_EQ(0, clnt_ctx.getLastError());
    // lifetime == 0 means expired.
    EXPECT_NE(0, clnt_lifetime);
    uint64_t now = static_cast<uint64_t>(time(0));
    // Cached credentials expire at Apr 6 19:04:36 2036.
    const uint64_t expire = timeFromText64("20260406190436");
    EXPECT_LE(expire, now + clnt_lifetime);

    ASSERT_TRUE(srv_ret);
    ASSERT_TRUE(srv_ctx.get());
    EXPECT_EQ(0, srv_ctx.getLastError());

    // Inquire the client state.
    GssApiName source;
    GssApiName target;
    clnt_lifetime = 0;
    OM_uint32 got_flags = 0;
    bool local = false;
    bool established = false;
    EXPECT_NO_THROW(clnt_ctx.inquire(source, target, clnt_lifetime,
                                     got_flags, local, established));
    ASSERT_TRUE(source.get());
    string src_txt;
    EXPECT_NO_THROW(src_txt = source.toString());
    EXPECT_EQ("administrator@EXAMPLE.NIL", src_txt);
    ASSERT_TRUE(target.get());
    string tgt_txt;
    EXPECT_NO_THROW(tgt_txt = target.toString());
    EXPECT_EQ("DNS/blu.example.nil@EXAMPLE.NIL", tgt_txt);
    // lifetime == 0 means expired.
    EXPECT_NE(0, clnt_lifetime);
    now = static_cast<uint64_t>(time(0));
    EXPECT_LE(expire, now + clnt_lifetime);
    EXPECT_EQ(flags, (got_flags & flags));
    EXPECT_TRUE(local);
    EXPECT_TRUE(established);

    // Inquire the server state.
    GssApiName source2;
    GssApiName target2;
    srv_lifetime = 0;
    got_flags = 0;
    established = false;
    EXPECT_NO_THROW(srv_ctx.inquire(source2, target2, srv_lifetime,
                                    got_flags, local, established));
    ASSERT_TRUE(source2.get());
    src_txt.clear();
    EXPECT_NO_THROW(src_txt = source2.toString());
    EXPECT_EQ("administrator@EXAMPLE.NIL", src_txt);
    ASSERT_TRUE(target2.get());
    tgt_txt.clear();
    EXPECT_NO_THROW(tgt_txt = target2.toString());
    EXPECT_EQ("DNS/blu.example.nil@EXAMPLE.NIL", tgt_txt);
    // lifetime == 0 means expired.
    EXPECT_NE(0, srv_lifetime);
    now = static_cast<uint64_t>(time(0));
    EXPECT_LE(expire, now + srv_lifetime);
    // Server side shall expire after the client (experiments showed 300s).
    EXPECT_LE(clnt_lifetime, srv_lifetime);
    EXPECT_EQ(flags, (got_flags & flags));
    EXPECT_FALSE(local);
    EXPECT_TRUE(established);

    // Try sign/verify from client to server.
    GssApiBufferPtr tbs;
    string tbs_str = "Hi There";
    tbs.reset(new GssApiBuffer(tbs_str.size() + 1, tbs_str.c_str()));
    GssApiBuffer sign;
    EXPECT_NO_THROW(clnt_ctx.sign(*tbs, sign));
    ASSERT_FALSE(sign.empty());
    EXPECT_NO_THROW(srv_ctx.verify(*tbs, sign));

    // Try sign/verify from server to client.
    GssApiBufferPtr tbs2;
    string tbs2_str = "what do ya want for nothing?";
    tbs2.reset(new GssApiBuffer(tbs2_str.size() + 1, tbs2_str.c_str()));
    GssApiBuffer sign2;
    EXPECT_NO_THROW(srv_ctx.sign(*tbs2, sign2));
    ASSERT_FALSE(sign2.empty());
    EXPECT_NO_THROW(clnt_ctx.verify(*tbs2, sign2));
}

}
