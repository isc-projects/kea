// Copyright (C) 2009  Internet Systems Consortium, Inc. ("ISC")
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

#include <resolver/spec_config.h>
#include <resolver/resolver.h>
#include "resolver_log.h"
#include "common.h"

#include <asiodns/asiodns.h>
#include <asiolink/asiolink.h>

#include <exceptions/exceptions.h>

#include <util/buffer.h>
#include <dns/rcode.h>
#include <dns/message.h>
#include <dns/messagerenderer.h>

#include <cc/session.h>
#include <cc/data.h>
#include <config/ccsession.h>

#include <server_common/socket_request.h>

#include <xfr/xfrout_client.h>

#include <auth/common.h>

#include <cache/resolver_cache.h>
#include <nsas/nameserver_address_store.h>

#include <log/logger_support.h>
#include <log/logger_level.h>
#include "resolver_log.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>

#include <string>
#include <iostream>

#include <boost/foreach.hpp>

using namespace std;
using namespace isc::cc;
using namespace isc::config;
using namespace isc::data;
using namespace isc::asiodns;
using namespace isc::asiolink;

namespace {

static const string PROGRAM = "Resolver";

IOService io_service;
static boost::shared_ptr<Resolver> resolver;

ConstElementPtr
my_config_handler(ConstElementPtr new_config) {
    return (resolver->updateConfig(new_config));
}

ConstElementPtr
my_command_handler(const string& command, ConstElementPtr args) {
    ConstElementPtr answer = createAnswer();

    try {
        if (command == "print_message") {
            LOG_INFO(resolver_logger, RESOLVER_PRINT_COMMAND).arg(args);
            /* let's add that message to our answer as well */
            answer = createAnswer(0, args);
        } else if (command == "shutdown") {
            // Is the pid argument provided?
            if (args && args->contains("pid")) {
                // If it is, we check it is the same as our PID
                const int pid(args->get("pid")->intValue());
                const pid_t my_pid(getpid());
                if (my_pid != pid) {
                    // It is not for us (this is expected, see auth/command.cc
                    // and the ShutdownCommand there).
                    return (answer);
                }
            }
            LOG_DEBUG(resolver_logger, RESOLVER_DBG_INIT,
                      RESOLVER_SHUTDOWN_RECEIVED);
            io_service.stop();
        }

        return (answer);
    } catch (const std::exception& e) {
        return (createAnswer(1, e.what()));
    }
}

void
usage() {
    cerr << "Usage:  b10-resolver [-u user] [-v]" << endl;
    cerr << "\t-v: verbose output" << endl;
    exit(1);
}
} // end of anonymous namespace

int
main(int argc, char* argv[]) {
    bool verbose = false;
    int ch;

    while ((ch = getopt(argc, argv, "u:v")) != -1) {
        switch (ch) {
        case 'v':
            verbose = true;
            break;
        case '?':
        default:
            usage();
        }
    }

    if (argc - optind > 0) {
        usage();
    }

    // Until proper logging comes along, initialize the logging with the
    // temporary initLogger() code.  If verbose, we'll use maximum verbosity.
    isc::log::initLogger(RESOLVER_NAME,
                         (verbose ? isc::log::DEBUG : isc::log::INFO),
                         isc::log::MAX_DEBUG_LEVEL, NULL, true);

    // Print the starting message
    string cmdline = argv[0];
    for (int i = 1; i < argc; ++ i) {
        cmdline = cmdline + " " + argv[i];
    }
    LOG_INFO(resolver_logger, RESOLVER_STARTING).arg(cmdline);

    int ret = 0;

    Session* cc_session = NULL;
    ModuleCCSession* config_session = NULL;
    try {
        string specfile;
        if (getenv("B10_FROM_BUILD")) {
            specfile = string(getenv("B10_FROM_BUILD")) +
                "/src/bin/resolver/resolver.spec";
        } else {
            specfile = string(RESOLVER_SPECFILE_LOCATION);
        }

        resolver = boost::shared_ptr<Resolver>(new Resolver());
        LOG_DEBUG(resolver_logger, RESOLVER_DBG_INIT, RESOLVER_CREATED);

        SimpleCallback* checkin = resolver->getCheckinProvider();
        DNSLookup* lookup = resolver->getDNSLookupProvider();
        DNSAnswer* answer = resolver->getDNSAnswerProvider();

        isc::nsas::NameserverAddressStore nsas(resolver);
        resolver->setNameserverAddressStore(nsas);

        isc::cache::ResolverCache cache;
        resolver->setCache(cache);

        // TODO priming query, remove root from direct
        // Fake a priming query result here (TODO2 how to flag non-expiry?)
        // propagation to runningquery. And check for forwarder mode?
        isc::dns::QuestionPtr root_question(new isc::dns::Question(
                                            isc::dns::Name("."),
                                            isc::dns::RRClass::IN(),
                                            isc::dns::RRType::NS()));
        isc::dns::RRsetPtr root_ns_rrset(new isc::dns::RRset(isc::dns::Name("."),
                                         isc::dns::RRClass::IN(),
                                         isc::dns::RRType::NS(),
                                         isc::dns::RRTTL(8888)));
        root_ns_rrset->addRdata(isc::dns::rdata::createRdata(isc::dns::RRType::NS(),
                                                             isc::dns::RRClass::IN(),
                                                             "l.root-servers.net."));
        isc::dns::RRsetPtr root_a_rrset(new isc::dns::RRset(isc::dns::Name("l.root-servers.net"),
                                        isc::dns::RRClass::IN(),
                                        isc::dns::RRType::A(),
                                        isc::dns::RRTTL(8888)));
        root_a_rrset->addRdata(isc::dns::rdata::createRdata(isc::dns::RRType::A(),
                                                             isc::dns::RRClass::IN(),
                                                             "199.7.83.42"));
        isc::dns::RRsetPtr root_aaaa_rrset(new isc::dns::RRset(isc::dns::Name("l.root-servers.net"),
                                        isc::dns::RRClass::IN(),
                                        isc::dns::RRType::AAAA(),
                                        isc::dns::RRTTL(8888)));
        root_aaaa_rrset->addRdata(isc::dns::rdata::createRdata(isc::dns::RRType::AAAA(),
                                                             isc::dns::RRClass::IN(),
                                                             "2001:500:3::42"));
        isc::dns::MessagePtr priming_result(new isc::dns::Message(isc::dns::Message::RENDER));
        priming_result->setRcode(isc::dns::Rcode::NOERROR());
        priming_result->addQuestion(root_question);
        priming_result->addRRset(isc::dns::Message::SECTION_ANSWER, root_ns_rrset);
        priming_result->addRRset(isc::dns::Message::SECTION_ADDITIONAL, root_a_rrset);
        priming_result->addRRset(isc::dns::Message::SECTION_ADDITIONAL, root_aaaa_rrset);
        cache.update(*priming_result);
        cache.update(root_ns_rrset);
        cache.update(root_a_rrset);
        cache.update(root_aaaa_rrset);

        DNSService dns_service(io_service, checkin, lookup, answer);
        resolver->setDNSService(dns_service);
        LOG_DEBUG(resolver_logger, RESOLVER_DBG_INIT, RESOLVER_SERVICE_CREATED);

        cc_session = new Session(io_service.get_io_service());
        isc::server_common::initSocketRequestor(*cc_session, RESOLVER_NAME);

        // We delay starting listening to new commands/config just before we
        // go into the main loop.   See auth/main.cc for the rationale.
        config_session = new ModuleCCSession(specfile, *cc_session,
                                             my_config_handler,
                                             my_command_handler, false);
        LOG_DEBUG(resolver_logger, RESOLVER_DBG_INIT, RESOLVER_CONFIG_CHANNEL);

        resolver->setConfigSession(config_session);
        // Install all initial configurations.  If loading configuration
        // fails, it will be logged, but we start the server anyway, giving
        // the user a second chance to correct the configuration.
        // By setting the 'startup' parameter to true, we ensure most of
        // the default configuration will be installed even if listen_on
        // fails.
        resolver->updateConfig(config_session->getFullConfig(), true);
        LOG_DEBUG(resolver_logger, RESOLVER_DBG_INIT, RESOLVER_CONFIG_LOADED);

        // Now start asynchronous read.
        config_session->start();

        LOG_INFO(resolver_logger, RESOLVER_STARTED);
        io_service.run();
    } catch (const std::exception& ex) {
        LOG_FATAL(resolver_logger, RESOLVER_FAILED).arg(ex.what());
        ret = 1;
    }

    delete config_session;
    delete cc_session;

    LOG_INFO(resolver_logger, RESOLVER_SHUTDOWN);
    return (ret);
}
