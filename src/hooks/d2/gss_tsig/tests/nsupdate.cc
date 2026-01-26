// Copyright (C) 2021-2026 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <asiodns/io_fetch.h>
#include <cryptolink/crypto_rng.h>
#include <dns/messagerenderer.h>
#include <dns/opcode.h>
#include <log/logger_support.h>
#include <stats/stats_mgr.h>
#include <gss_tsig_api.h>
#include <gss_tsig_context.h>
#include <gss_tsig_key.h>

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <limits>

using namespace isc;
using namespace isc::asiodns;
using namespace isc::asiolink;
using namespace isc::dns;
using namespace isc::dns::rdata;
using namespace isc::dns::rdata::generic;
using namespace isc::gss_tsig;
using namespace isc::stats;
using namespace isc::util;
using namespace std;

// Parameters decoded in main() from the command line.

/// @brief DNS server address (-s <addr>[/<port>]).
string named_addr("10.53.0.1");

/// @brief DNS server port (s argument).
uint16_t named_port(5300);

/// @brief DNS server principal (-p <princ>).
string named_princ("DNS/blu.example.nil@EXAMPLE.NIL");

/// @brief Key name (-d <key-domain> and -k <full-key-name>).
string key_name("sig-blu.example.nil.");

/// @brief Randomize key name (no k flag).
bool rnd_key_name(true);

/// @brief Client credential principal (-c <cred>).
string cred_princ("");

/// @brief Client credential cache specification (-C <ccache>).
string ccache_spec = string("FILE:") + string(TEST_DATA_DIR) +
  string("/administrator.ccache");

/// @brief Name to update (-n <name>).
string upd_name("testdc1.example.nil.");

/// @brief Zone to update (-z <zone>).
string upd_zone("example.nil.");

/// @brief Address of update (-a <addr4>).
string upd_addr("10.53.0.10");

/// @brief Time To Live of update (one day) (-t <ttl>).
uint32_t upd_ttl(86400);

/// @brief TKEY key lifetime (one hour) (-l <lifetime).
uint32_t tkey_lifetime(3600);

/// @brief I/O timeout (2 seconds) (-w <wait>).
unsigned io_wait(2000);

/// @brief Query ID base (-q <qid>).
///
/// @note IOFetch puts a random qid in outgoing messages.
uint16_t qid(0x1234);

/// @brief GSS-API flags (-f <flags>).
OM_uint32 flags(GSS_C_REPLAY_FLAG | GSS_C_MUTUAL_FLAG | GSS_C_INTEG_FLAG);

/// @brief IOFetch protocol (-u).
IOFetch::Protocol protocol(IOFetch::TCP);

/// @brief Verbose flag.
bool verbose(false);

// Work values.

/// @brief GSS-TSIG Key.
GssTsigKeyPtr key;

/// @brief GSS-TSIG credential.
GssApiCredPtr cred;

/// @brief GSS-TSIG TKEY context.
GssTsigContextPtr tkey_ctx;

/// @brief GSS-TSIG update context.
GssTsigContextPtr upd_ctx;

/// @brief Input token.
GssApiBufferPtr intoken;

/// @brief Output token.
GssApiBufferPtr outtoken;

/// @brief DNS message.
MessagePtr msg;

/// @brief DNS message buffer.
const void* msg_buf(0);

/// @brief DNS message length.
size_t msg_len(0);

/// @brief TKEY RRset.
RRsetPtr tkey_rrset;

/// @brief TKEY Rdata.
ConstRdataPtr tkey_rdata;

/// @brief Update RRset.
RRsetPtr upd_rrset;

/// @brief Update Rdata.
ConstRdataPtr upd_rdata;

/// @brief Current time.
time_t now(0);

/// @brief I/O service.
IOServicePtr io_service;

/// @brief I/O fetch result.
IOFetch::Result io_result;

/// @brief I/O fetch done flag.
bool io_done(false);

/// @brief I/O fetch callback class.
class IOCallback : public IOFetch::Callback {
public:
    /// @brief Callback operator.
    void operator()(IOFetch::Result result) {
        io_done = true;
        io_result = result;
    }
};

/// @brief I/O fetch callback object.
IOCallback cb;

/// @brief Clean and exit function.
[[noreturn]] void finish(int exit_code) {
    try {
        StatsMgr::instance().removeAll();
    } catch (...) {
        // Force an error.
        exit_code = 1;
    }
    exit(exit_code);
}

/// @brief Setup function.
void setup() {
    log::initLogger();
    // Usual sanity check for IOFetch wait argument.
    if (io_wait > numeric_limits<int>::max()) {
        cerr << "I/O timeout value " << io_wait << " is too large\n";
        finish(1);
    }
    // Command line setting to '' means it was already set.
    if (!ccache_spec.empty()) {
        setenv("KRB5CCNAME", ccache_spec.c_str(), 1);
    }
    // Create a random key name when not set from the command line.
    // The DNS server does not allow to reuse a key name.
    if (rnd_key_name) {
        uint32_t n;
        vector<uint8_t> r = isc::cryptolink::random(sizeof(uint32_t));
        memmove(&n, &r[0], sizeof(uint32_t));
        ostringstream s;
        s << n << "." << key_name;
        key_name = s.str();
    }
    key.reset(new GssTsigKey(key_name));
    // Get the credential when set from the command line.
    if (!cred_princ.empty()) {
        OM_uint32 lifetime(0);
        GssApiName cname(cred_princ);
        cred.reset(new GssApiCred(cname, GSS_C_INITIATE, lifetime));
        if (lifetime == 0) {
            cerr << "credential for '" << cred_princ << "' already expired\n";
        }
    }
    io_service.reset(new IOService());
}

/// @brief TKEY exchange(s).
void tkey() {
    GssApiName named_gname(named_princ);
    bool ret(false);
    intoken.reset(new GssApiBuffer());
    OutputBufferPtr outbuf;
    // GSS-API security context establishment using TKEY to transport them.
    for (;;) {
        outtoken.reset(new GssApiBuffer());
        OM_uint32 lifetime = 0;
        ret = key->getSecCtx().init(cred, named_gname, flags, *intoken,
                                    *outtoken, lifetime);
        if (ret) {
            // Established.
            break;
        }
        if (outtoken->empty()) {
            cerr << "output token is empty\n";
            finish(1);
        }

        // Create a TKEY request.
        msg.reset(new Message(Message::RENDER));
        msg->setQid(++qid);
        msg->setOpcode(Opcode::QUERY());
        msg->setRcode(Rcode::NOERROR());
        msg->setHeaderFlag(Message::HEADERFLAG_QR, false);
        msg->setHeaderFlag(Message::HEADERFLAG_RD, false);
        if (msg->getRRCount(Message::SECTION_QUESTION) > 0) {
            msg->clearSection(Message::SECTION_QUESTION);
        }
        Name qname(key_name);
        msg->addQuestion(Question(qname, RRClass::ANY(), RRType::TKEY()));

        // Create the TKEY Resource Record.
        Name key_dns_name(key_name);
        tkey_rrset.reset(new RRset(key_dns_name, RRClass::ANY(),
                                   RRType::TKEY(), RRTTL(0)));
        Name algorithm("gss-tsig.");
        now = time(0);
        uint32_t inception = static_cast<uint32_t>(now);
        uint32_t expire = inception + tkey_lifetime;
        uint16_t mode = TKEY::GSS_API_MODE;
        uint16_t error = Rcode::NOERROR().getCode();
        uint16_t key_len = static_cast<uint16_t>(outtoken->getLength());
        tkey_rdata.reset(new TKEY(algorithm, inception, expire, mode, error,
                                  key_len, outtoken->getValue(), 0, 0));
        tkey_rrset->addRdata(tkey_rdata);
        msg->addRRset(Message::SECTION_ADDITIONAL, tkey_rrset);

        // Encode the TKEY request.
        MessageRenderer renderer;
        OutputBufferPtr inbuf(new OutputBuffer(4096));
        renderer.setBuffer(inbuf.get());
        renderer.setLengthLimit(4096);
        msg->toWire(renderer);
        if (verbose) {
            cout << "sending TKEY message " << inbuf->getLength() << "\n";
        }

        // Send the TKEY request.
        IOAddress named_io_addr(named_addr);
        outbuf.reset(new OutputBuffer(4096));
        io_result = IOFetch::NOTSET;
        io_done = false;
        // Do not use msg because IOFetch code will mess it!
        IOFetch io_fetch(protocol, io_service, inbuf, named_io_addr,
                         named_port, outbuf, &cb, static_cast<int>(io_wait));
        io_service->post(io_fetch);

        // Wait for the TKEY response.
        while (!io_done) {
            io_service->runOne();
        }

        switch (io_result) {
        case IOFetch::SUCCESS:
            break;

        case IOFetch::TIME_OUT:
            cerr << "TKEY I/O timeout\n";
            finish(1);

        default:
            cerr << "TKEY I/O error " << io_result << "\n";
            finish(1);
        }

        // Decode the TKEY response.
        msg_len = outbuf->getLength();
        if (msg_len == 0) {
            cerr << "TKEY empty response\n";
            finish(1);
        }
        msg_buf = outbuf->getData();
        if (!msg_buf) {
            cerr << "TKEY null response\n";
            finish(1);
        }
        if (verbose) {
            cout << "received TKEY message " << msg_len << "\n";
        }
        msg.reset(new Message(Message::PARSE));
        InputBuffer recv_buf(msg_buf, msg_len);
        msg->fromWire(recv_buf);

        // Validate the TKEY response.
        if (!msg->getHeaderFlag(Message::HEADERFLAG_QR)) {
            cerr << "TKEY response is not a response\n";
        }
        if (msg->getRcode() != Rcode::NOERROR()) {
            cerr << "TKEY response error "
                 << msg->getRcode().toText() << "\n";
            finish(1);
        }
        if (msg->getOpcode() != Opcode::QUERY()) {
            cerr << "TKEY response opcode "
                 << msg->getRcode().toText() << "\n";
            finish(1);
        }
        if (msg->getRRCount(Message::SECTION_ANSWER) != 1) {
            cerr << "TKEY response answer count "
                 << msg->getRRCount(Message::SECTION_ANSWER) << "\n";
            finish(1);
        }
        RRsetPtr rrset = *msg->beginSection(Message::SECTION_ANSWER);
        if (!rrset) {
            cerr << "TKEY response get answer failure\n";
            finish(1);
        }
        if (rrset->getClass() != RRClass::ANY()) {
            cerr << "TKEY response answer class "
                 << rrset->getClass().toText() << "\n";
        }
        if (rrset->getType() != RRType::TKEY()) {
            cerr << "TKEY response answer type "
                 << rrset->getType().toText() << "\n";
            finish(1);
        }
        if (rrset->getTTL() != RRTTL(0)) {
            cerr << "TKEY response answer TTL "
                 << rrset->getTTL().toText() << "\n";
        }
        if (rrset->getRdataCount() != 1) {
            cerr << "TKEY response answer rdata count "
                 << rrset->getRdataCount() << "\n";
            if (rrset->getRdataCount() == 0) {
                finish(1);
            }
        }
        auto rdata_it = rrset->getRdataIterator();
        const TKEY& tkey = dynamic_cast<const TKEY&>(rdata_it->getCurrent());
        if (tkey.getError() != Rcode::NOERROR_CODE) {
            cerr << "TKEY error " << tkey.getError() << "\n";
            finish(1);
        }
        intoken.reset(new GssApiBuffer(tkey.getKeyLen(), tkey.getKey()));
        if (intoken->empty()) {
            cerr << "input token is empty\n";
            finish(1);
        }
        // The TKEY payload from the server response is used for
        // the GSS-API security context establishment.
    }
    if (!outtoken->empty()) {
        // The RFC is not consistent about this case because it specifies it
        // and at the same time requires the server to sign the last response
        // so the first security context to be established is the server one
        // and any further exchange does not make sense...
        cerr << "output token is not empty\n";
    }
    if (verbose) {
        cout << "Got GSS-API security context for "
             << key->getSecCtx().getLifetime() << " seconds\n";
    }

    // The last TKEY response must be signed.
    const TSIGRecord* tsig = msg->getTSIGRecord();
    if (!tsig) {
        cerr << "last TKEY response is not signed\n";
        finish(1);
    }
    tkey_ctx.reset(new GssTsigContext(*key));
    tkey_ctx->setState(TSIGContext::SENT_REQUEST);
    TSIGError error = tkey_ctx->verify(tsig, msg_buf, msg_len);
    if (error != TSIGError::NOERROR()) {
        cerr << "last TKEY response failed to verify\n";
        finish(1);
    }
    if (verbose) {
        cout << "verified TKEY response\n";
    }
}

/// @brief Update function.
void update() {
    // Build the Update request.
    msg.reset(new Message(Message::RENDER));
    msg->setQid(++qid);
    msg->setOpcode(Opcode::UPDATE());
    msg->setRcode(Rcode::NOERROR());
    msg->setHeaderFlag(Message::HEADERFLAG_QR, false);
    msg->setHeaderFlag(Message::HEADERFLAG_RD, false);
    if (msg->getRRCount(Message::SECTION_QUESTION) > 0) {
        msg->clearSection(Message::SECTION_QUESTION);
    }
    Name zname(upd_zone);
    /// Zone section is question.
    msg->addQuestion(Question(zname, RRClass::IN(), RRType::SOA()));

    // Build the A Resource Record to update.
    Name upd_dns_name(upd_name);
    RRTTL ttl(upd_ttl);
    upd_rrset.reset(new RRset(upd_dns_name, RRClass::IN(), RRType::A(), ttl));
    upd_rdata.reset(new in::A(upd_addr));
    upd_rrset->addRdata(upd_rdata);
    // Update section is authority.
    msg->addRRset(Message::SECTION_AUTHORITY, upd_rrset);

    // Encode the Update request.
    MessageRenderer renderer;
    OutputBufferPtr inbuf(new OutputBuffer(1024));
    renderer.setBuffer(inbuf.get());
    upd_ctx.reset(new GssTsigContext(*key));
    msg->toWire(renderer, upd_ctx.get());
    if (verbose) {
        cout << "sending Update message " << inbuf->getLength() << "\n";
    }

    // Send the Update request.
    IOAddress named_io_addr(named_addr);
    OutputBufferPtr outbuf(new OutputBuffer(1024));
    io_result = IOFetch::NOTSET;
    io_done = false;
    IOFetch io_fetch(protocol, io_service, inbuf, named_io_addr,
                     named_port, outbuf, &cb, static_cast<int>(io_wait));
    io_service->post(io_fetch);

    // Wait for the Update response.
    while (!io_done) {
        io_service->runOne();
    }

    switch (io_result) {
    case IOFetch::SUCCESS:
        break;

    case IOFetch::TIME_OUT:
        cerr << "Update I/O timeout\n";
        finish(1);

    default:
        cerr << "Update I/O error " << io_result << "\n";
        finish(1);
    }

    // Decode the Update response.
    msg_len = outbuf->getLength();
    if (msg_len == 0) {
        cerr << "Update empty response\n";
        finish(1);
    }
    msg_buf = outbuf->getData();
    if (!msg_buf) {
        cerr << "Update null response\n";
        finish(1);
    }
    if (verbose) {
        cout << "received Update message " << msg_len << "\n";
    }
    msg.reset(new Message(Message::PARSE));
    InputBuffer recv_buf(msg_buf, msg_len);
    msg->fromWire(recv_buf);

    // The Update response must be signed.
    const TSIGRecord* tsig = msg->getTSIGRecord();
    if (!tsig) {
        cerr << "Update response is not signed\n";
        finish(1);
    }
    TSIGError error = upd_ctx->verify(tsig, msg_buf, msg_len);
    if (error != TSIGError::NOERROR()) {
        cerr << "Update response failed to verify\n";
        finish(1);
    }
    if (verbose) {
        cout << "verified Update response\n";
    }
    finish(0);
}

/// @brief Prints usage and exists.
///
/// @note This function never returns. It terminates the process.
///
/// @param ret Return value.
void
usage(int ret) {
    cerr << "Usage: " << "nsupdate"
         << " -a <addr4>"
         << " -c <cred>"
         << " -C <ccache>"
         << " -d <key-domain>"
         << " -f <flags>"
         << " -h"
         << " -k <full-key-name>"
         << " -l <lifetime>"
         << " -n <name>"
         << " -p <princ>"
         << " -q <qid>"
         << " -s <addr>[/<port>]"
         << " -t <ttl>"
         << " -u"
         << " -v"
         << " -w <wait>"
         << " -z <zone>"
         << "\n";
    cerr << "Defaults are:\n"
         << "\tDNS server (-s) 10.53.0.1/5300\n"
         << "\tDNS server principal (-p) 'DNS/blu.example.nil@EXAMPLE.NIL'\n"
         << "\tClient credential principal (-c) none: use default\n"
         << "\tKey domain (-d) 'blu.example.nil.'\n"
         << "\tKey name (-k) '<random>.sig-blu.example.nil.'\n"
         << "\tCredential cache (-C) 'FILE:<pwd>/administrator.ccache'\n"
         << "\tName to update (-n) 'testdc1.example.nil.'\n"
         << "\tZone to update (-z) 'example.nil.'\n"
         << "\tIPv4 address to update (-a) '10.53.0.10'\n"
         << "\tTime To Live of update (-t) '86400' (one day)\n"
         << "\tTKEY key lifetime (-l) '3600' (one hour)\n"
         << "\tI/O timeout (-w) '2000' (in milliseconds)\n"
         << "\tQuery ID base (-q) '0x1234'\n"
         << "\tGSS-API flags (-f) '0x26'\n"
         << "\tI/O protocol (-u) TCP\n"
         << "\tverbose (-v) off\n"
         << "\thelp (-h)\n";
    exit(ret);
}

/// @brief The main routine.
///
/// It decodes the command line arguments, setup work values and
/// performs TKEY and Update exchanges.
int
main(int argc, char* argv[]) {
    int ch;
    bool set_key_name(false);
    // A bit too C style but exception free...
    while ((ch = getopt(argc, argv,
                        "a:c:C:d:f:hk:l:n:p:q:s:t:T:uvw:z:")) != -1) {
        size_t pos;
        switch (ch) {
        case 'a':
            upd_addr = optarg;
            break;

        case 'c':
            cred_princ = optarg;
            break;

        case 'C':
            ccache_spec = optarg;
            break;

        case 'd':
            if (set_key_name) {
                cerr << "key name was already set\n";
                usage(1);
            }
            set_key_name = true;
            key_name = optarg;
            break;

        case 'f':
            flags = atol(optarg);
            if (flags == 0) {
                cerr << "can't parse -f flags: " << optarg << "\n";
                usage(1);
            }
            break;

        case 'h':
        case '?':
            usage(0);
            break;

        case 'k':
            if (set_key_name) {
                cerr << "key name was already set\n";
                usage(1);
            }
            set_key_name = true;
            key_name = optarg;
            rnd_key_name = false;
            break;

        case 'l':
            tkey_lifetime = atol(optarg);
            if (flags == 0) {
                cerr << "can't parse -l lifetime: " << optarg << "\n";
                usage(1);
            }
            break;

        case 'n':
            upd_name = optarg;
            break;

        case 'p':
            named_princ = optarg;
            break;

        case 'q':
            qid = atol(optarg);
            if (qid == 0) {
                cerr << "can't parse -q qid: " << optarg << "\n";
                usage(1);
            }
            break;

        case 's':
            named_addr = optarg;
            pos = named_addr.find_first_of('/');
            if ((pos != string::npos) && (pos < named_addr.size())) {
                string port_str = named_addr.substr(pos + 1);
                named_addr = named_addr.substr(0, pos);
                long port = atol(port_str.c_str());
                if ((port <= 0) || (port > numeric_limits<uint16_t>::max())) {
                    cerr << "can't parse -s addr/port: " << optarg << "\n";
                    usage(1);
                }
                named_port = static_cast<uint16_t>(port);
            }
            break;

        case 'u':
            protocol = IOFetch::UDP;
            break;

        case 'v':
            verbose = true;
            break;

        case 'w':
            io_wait = atol(optarg);
            if (io_wait == 0) {
                cerr << "can't parse -w wait: " << optarg << "\n";
                usage(1);
            }
            break;

        case 'z':
            upd_zone = optarg;
            break;

        default:
            usage(1);
        }
    }

    try {
        setup();
        tkey();
        update();
    } catch (const exception& ex) {
        cerr << "Failed with " << ex.what() << "\n";
    }
    finish(1);
}
