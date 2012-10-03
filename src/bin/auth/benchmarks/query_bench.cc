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

#include <bench/benchmark.h>
#include <bench/benchmark_util.h>

#include <util/buffer.h>
#include <dns/message.h>
#include <dns/name.h>
#include <dns/question.h>
#include <dns/rrclass.h>

#include <log/logger_support.h>
#include <xfr/xfrout_client.h>

#include <util/unittests/mock_socketsession.h>

#include <auth/auth_srv.h>
#include <auth/auth_config.h>
#include <auth/datasrc_configurator.h>
#include <auth/query.h>

#include <asiodns/asiodns.h>
#include <asiolink/asiolink.h>

#include <boost/shared_ptr.hpp>

#include <stdlib.h>

#include <iostream>
#include <vector>

using namespace std;
using namespace isc;
using namespace isc::data;
using namespace isc::auth;
using namespace isc::dns;
using namespace isc::log;
using namespace isc::util;
using namespace isc::util::unittests;
using namespace isc::xfr;
using namespace isc::bench;
using namespace isc::asiodns;
using namespace isc::asiolink;

namespace {
// Commonly used constant:
XfroutClient xfrout_client("dummy_path"); // path doesn't matter

// Just something to pass as the server to resume
class DummyServer : public DNSServer {
    public:
        virtual void operator()(asio::error_code, size_t) {}
        virtual void resume(const bool) {}
        virtual DNSServer* clone() {
            return (new DummyServer(*this));
        }
};

class QueryBenchMark {
protected:
    // Maintain dynamically generated objects via shared pointers because
    // QueryBenchMark objects will be copied.
    typedef boost::shared_ptr<AuthSrv> AuthSrvPtr;
private:
    typedef boost::shared_ptr<const IOEndpoint> IOEndpointPtr;
protected:
    QueryBenchMark(const BenchQueries& queries, Message& query_message,
                   OutputBuffer& buffer) :
        server_(new AuthSrv(xfrout_client, ddns_forwarder)),
        datasrc_configurator_(server_.get()),
        queries_(queries),
        query_message_(query_message),
        buffer_(buffer),
        dummy_socket(IOSocket::getDummyUDPSocket()),
        dummy_endpoint(IOEndpointPtr(IOEndpoint::create(IPPROTO_UDP,
                                                        IOAddress("192.0.2.1"),
                                                        53210)))
    {}
public:
    unsigned int run() {
        BenchQueries::const_iterator query;
        const BenchQueries::const_iterator query_end = queries_.end();
        DummyServer server;
        for (query = queries_.begin(); query != query_end; ++query) {
            IOMessage io_message(&(*query)[0], (*query).size(), dummy_socket,
                                 *dummy_endpoint);
            query_message_.clear(Message::PARSE);
            buffer_.clear();
            server_->processMessage(io_message, query_message_, buffer_,
                                    &server);
        }

        return (queries_.size());
    }
private:
    MockSocketSessionForwarder ddns_forwarder;
protected:
    AuthSrvPtr server_;
    DataSourceConfigurator datasrc_configurator_;
private:
    const BenchQueries& queries_;
    Message& query_message_;
    OutputBuffer& buffer_;
    IOSocket& dummy_socket;
    IOEndpointPtr dummy_endpoint;
};

class Sqlite3QueryBenchMark  : public QueryBenchMark {
public:
    Sqlite3QueryBenchMark(const char* const datasrc_file,
                          const BenchQueries& queries,
                          Message& query_message,
                          OutputBuffer& buffer) :
        QueryBenchMark(queries, query_message, buffer)
    {
        datasrc_configurator_.reconfigure(
            Element::fromJSON("{\"IN\":"
                              "  [{\"type\": \"sqlite3\","
                              "    \"params\": {"
                              "      \"database_file\": \"" +
                              string(datasrc_file) + "\"}}]}"));
    }
};

class MemoryQueryBenchMark  : public QueryBenchMark {
public:
    MemoryQueryBenchMark(const char* const zone_file,
                         const char* const zone_origin,
                         const BenchQueries& queries,
                         Message& query_message,
                         OutputBuffer& buffer) :
        QueryBenchMark(queries, query_message, buffer)
    {
        datasrc_configurator_.reconfigure(
            Element::fromJSON("{\"IN\":"
                              "  [{\"type\": \"MasterFiles\","
                              "    \"cache-enable\": true, "
                              "    \"params\": {\"" +
                              string(zone_origin) + "\": \"" +
                              string(zone_file) + "\"}}]}"));
    }
};

void
printQPSResult(unsigned int iteration, double duration,
            double iteration_per_second)
{
    cout.precision(6);
    cout << "Processed " << iteration << " queries in "
         << fixed << duration << "s";
    cout.precision(2);
    cout << " (" << fixed << iteration_per_second << "qps)" << endl;
}
}

namespace isc {
namespace bench {
template<>
void
BenchMark<Sqlite3QueryBenchMark>::printResult() const {
    printQPSResult(getIteration(), getDuration(), getIterationPerSecond());
}

template<>
void
BenchMark<MemoryQueryBenchMark>::printResult() const {
    printQPSResult(getIteration(), getDuration(), getIterationPerSecond());
}
}
}

namespace {
const int ITERATION_DEFAULT = 1;
enum DataSrcType {
    SQLITE3,
    MEMORY
};

void
usage() {
    cerr <<
        "Usage: query_bench [-d] [-n iterations] [-t datasrc_type] [-o origin]"
        " datasrc_file query_datafile\n"
        "  -d Enable debug logging to stdout\n"
        "  -n Number of iterations per test case (default: "
         << ITERATION_DEFAULT << ")\n"
        "  -t Type of data source: sqlite3|memory (default: sqlite3)\n"
        "  -o Origin name of datasrc_file necessary for \"memory\", "
        "ignored for others\n"
        "  datasrc_file: sqlite3 DB file for \"sqlite3\", "
        "textual master file for \"memory\" datasrc\n"
        "  query_datafile: queryperf style input data"
         << endl;
    exit (1);
}
}

int
main(int argc, char* argv[]) {
    int ch;
    int iteration = ITERATION_DEFAULT;
    const char* opt_datasrc_type = "sqlite3";
    const char* origin = NULL;
    bool debug_log = false;
    while ((ch = getopt(argc, argv, "dn:t:o:")) != -1) {
        switch (ch) {
        case 'n':
            iteration = atoi(optarg);
            break;
        case 't':
            opt_datasrc_type = optarg;
            break;
        case 'o':
            origin = optarg;
            break;
        case 'd':
            debug_log = true;
            break;
        case '?':
        default:
            usage();
        }
    }
    argc -= optind;
    argv += optind;
    if (argc < 2) {
        usage();
    }
    const char* const datasrc_file = argv[0];
    const char* const query_data_file = argv[1];

    // By default disable logging to avoid unwanted noise.
    initLogger("query-bench", debug_log ? isc::log::DEBUG : isc::log::NONE,
               isc::log::MAX_DEBUG_LEVEL, NULL);

    DataSrcType datasrc_type = SQLITE3;
    if (strcmp(opt_datasrc_type, "sqlite3") == 0) {
        ;                       // no need to override
    } else if (strcmp(opt_datasrc_type, "memory") == 0) {
        datasrc_type = MEMORY;
    } else {
        cerr << "Unknown data source type: " << datasrc_type << endl;
        return (1);
    }

    if (datasrc_type == MEMORY && origin == NULL) {
        cerr << "'-o Origin' is missing for memory data source " << endl;
        return (1);
    }

    try {
        BenchQueries queries;
        loadQueryData(query_data_file, queries, RRClass::IN());
        OutputBuffer buffer(4096);
        Message message(Message::PARSE);

        cout << "Parameters:" << endl;
        cout << "  Iterations: " << iteration << endl;
        cout << "  Data Source: type=" << opt_datasrc_type << ", file=" <<
            datasrc_file << endl;
        if (origin != NULL) {
            cout << "  Origin: " << origin << endl;
        }
        cout << "  Query data: file=" << query_data_file << " ("
             << queries.size() << " queries)" << endl << endl;

        switch (datasrc_type) {
        case SQLITE3:
            cout << "Benchmark with SQLite3" << endl;
            BenchMark<Sqlite3QueryBenchMark>(
                iteration, Sqlite3QueryBenchMark(datasrc_file, queries,
                                                 message, buffer));
            break;
        case MEMORY:
            cout << "Benchmark with In Memory Data Source" << endl;
            BenchMark<MemoryQueryBenchMark>(
                iteration, MemoryQueryBenchMark(datasrc_file, origin, queries,
                                                message, buffer));
            break;
        }
    } catch (const std::exception& ex) {
        cout << "Test unexpectedly failed: " << ex.what() << endl;
        return (1);
    }

    return (0);
}
