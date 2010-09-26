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

// $Id$

#include <stdlib.h>

#include <iostream>
#include <vector>

#include <boost/shared_ptr.hpp>

#include <bench/benchmark.h>
#include <bench/benchmark_util.h>

#include <dns/buffer.h>
#include <dns/message.h>
#include <dns/messagerenderer.h>
#include <dns/name.h>
#include <dns/question.h>
#include <dns/rrclass.h>

#include <xfr/xfrout_client.h>

#include <auth/auth_srv.h>
#include <auth/asio_link.h>

using namespace std;
using namespace isc;
using namespace isc::dns;
using namespace isc::xfr;
using namespace isc::bench;
using namespace asio_link;

namespace {
// Commonly used constant:
XfroutClient xfrout_client("dummy_path"); // path doesn't matter

class QueryBenchMark {
private:
    // Maintain dynamically generated objects via shared pointers because
    // QueryBenchMark objects will be copied.
    typedef boost::shared_ptr<AuthSrv> AuthSrvPtr;
    typedef boost::shared_ptr<const IOEndpoint> IOEndpointPtr;
public:
    QueryBenchMark(const int cache_slots, const char* const datasrc_file,
                   const BenchQueries& queries, Message& query_message,
                   MessageRenderer& renderer) :
        server_(new AuthSrv(cache_slots >= 0 ? true : false, xfrout_client)),
        queries_(queries),
        query_message_(query_message),
        renderer_(renderer),
        dummy_socket(IOSocket::getDummyUDPSocket()),
        dummy_endpoint(IOEndpointPtr(IOEndpoint::create(IPPROTO_UDP,
                                                        IOAddress("192.0.2.1"),
                                                        5300)))
    {
        if (cache_slots >= 0) {
            server_->setCacheSlots(cache_slots);
        }
        server_->updateConfig(Element::fromJSON("{\"database_file\": \"" +
                                                string(datasrc_file) + "\"}"));
    }
    unsigned int run() {
        BenchQueries::const_iterator query;
        const BenchQueries::const_iterator query_end = queries_.end();
        for (query = queries_.begin(); query != query_end; ++query) {
            IOMessage io_message(&(*query)[0], (*query).size(), dummy_socket,
                                 *dummy_endpoint);
            query_message_.clear(Message::PARSE);
            renderer_.clear();
            server_->processMessage(io_message, query_message_, renderer_);
        }

        return (queries_.size());
    }
private:
    AuthSrvPtr server_;
    const BenchQueries& queries_;
    Message& query_message_;
    MessageRenderer& renderer_;
    IOSocket& dummy_socket;
    IOEndpointPtr dummy_endpoint;
};
}

namespace isc {
namespace bench {
template<>
void
BenchMark<QueryBenchMark>::printResult() const {
    cout.precision(6);
    cout << "Processed " << getIteration() << " queries in "
         << fixed << getDuration() << "s";
    cout.precision(2);
    cout << " (" << fixed << getIterationPerSecond() << "qps)" << endl;
}
}
}

namespace {
void
usage() {
    cerr << "Usage: query_bench [-n iterations] datasrc_file query_datafile"
         << endl;
    exit (1);
}
}

int
main(int argc, char* argv[]) {
    int ch;
    int iteration = 1;
    while ((ch = getopt(argc, argv, "n:")) != -1) {
        switch (ch) {
        case 'n':
            iteration = atoi(optarg);
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

    BenchQueries queries;
    loadQueryData(query_data_file, queries, RRClass::IN());
    OutputBuffer buffer(4096);
    MessageRenderer renderer(buffer);
    Message message(Message::PARSE);

    cout << "Parameters:" << endl;
    cout << "  Iterations: " << iteration << endl;
    cout << "  Data Source: " << datasrc_file << endl;
    cout << "  Query data: file=" << query_data_file << " (" << queries.size()
         << " queries)" << endl << endl;

    cout << "Benchmark enabling Hot Spot Cache with unlimited slots "
         << endl;
    BenchMark<QueryBenchMark>(iteration,
                              QueryBenchMark(0, datasrc_file, queries, message,
                                             renderer));

    cout << "Benchmark enabling Hot Spot Cache with 10*#queries slots "
         << endl;
    BenchMark<QueryBenchMark>(iteration,
                              QueryBenchMark(10 * queries.size(), datasrc_file,
                                             queries, message, renderer));

    cout << "Benchmark enabling Hot Spot Cache with #queries/2 slots "
         << endl;
    BenchMark<QueryBenchMark>(iteration,
                              QueryBenchMark(queries.size() / 2, datasrc_file,
                                             queries, message, renderer));

    cout << "Benchmark disabling Hot Spot Cache" << endl;
    BenchMark<QueryBenchMark>(iteration,
                              QueryBenchMark(-1, datasrc_file, queries,
                                             message, renderer));    

    return (0);
}
