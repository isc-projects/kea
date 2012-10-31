// Copyright (C) 2012  Internet Systems Consortium, Inc. ("ISC")
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

#include <bench/benchmark.h>

#include <util/buffer.h>
#include <util/memory_segment_local.h>

#include <dns/name.h>
#include <dns/messagerenderer.h>
#include <dns/rrset.h>
#include <dns/rrclass.h>
#include <dns/masterload.h>

#include <datasrc/memory/rdata_serialization.h>
#include <datasrc/memory/rdataset.h>
#include <datasrc/memory/treenode_rrset.h>
#include <datasrc/memory/zone_data.h>

#include <boost/bind.hpp>

#include <cassert>
#include <vector>
#include <sstream>

#include <unistd.h>

using std::vector;
using namespace isc::bench;
using namespace isc::datasrc::memory;
using namespace isc::dns;

namespace {
// A simple benchmark just repeating rendering a given set of RRsets.
class RRsetRenderBenchMark {
public:
    RRsetRenderBenchMark(const vector<ConstRRsetPtr>& rrsets,
                         MessageRenderer& renderer) :
        rrsets_(rrsets), renderer_(renderer)
    {}
    unsigned int run() {
        renderer_.clear();
        vector<ConstRRsetPtr>::const_iterator it;
        const vector<ConstRRsetPtr>::const_iterator it_end = rrsets_.end();
        for (it = rrsets_.begin(); it != it_end; ++it) {
            (*it)->toWire(renderer_);
        }
        return (1);
    }
private:
    const vector<ConstRRsetPtr>& rrsets_;
    MessageRenderer& renderer_;
};

// Builtin benchmark data.  This is a list of RDATA (of RRs) in a response
// from a root server for the query for "www.example.com" (as of this
// implementation).  We use a real world example to make the case practical.
const char* const delegation_rrsets_txt =
    // AUTHORITY SECTION (NS)
    "com. 172800 IN NS a.gtld-servers.net.\n"
    "com. 172800 IN NS b.gtld-servers.net.\n"
    "com. 172800 IN NS c.gtld-servers.net.\n"
    "com. 172800 IN NS d.gtld-servers.net.\n"
    "com. 172800 IN NS e.gtld-servers.net.\n"
    "com. 172800 IN NS f.gtld-servers.net.\n"
    "com. 172800 IN NS g.gtld-servers.net.\n"
    "com. 172800 IN NS h.gtld-servers.net.\n"
    "com. 172800 IN NS i.gtld-servers.net.\n"
    "com. 172800 IN NS j.gtld-servers.net.\n"
    "com. 172800 IN NS k.gtld-servers.net.\n"
    "com. 172800 IN NS l.gtld-servers.net.\n"
    "com. 172800 IN NS m.gtld-servers.net.\n"
    // AUTHORITY SECTION (DS)
    "com. 86400 IN DS 30909 8 2 "
    "E2D3C916F6DEEAC73294E8268FB5885044A833FC5459588F4A9184CFC41A5766\n"
    // AUTHORITY SECTION (RRSIG for DS)
    "com. 86400 IN RRSIG DS 8 1 86400 20120822000000 20120814230000 50398 . "
    "lcIpLRq4s91Fh1FihDXiDvVMMRqgy2jjlpiP4Y6sSjIrLue6Boi7xraj"
    "Ouka34ubpl4KuIcopWe99LI/7Npvq0MYr9DaqfnX9dTW6Vc2C7/hKSsz"
    "POYjraZZA3SCApgfNVzq+AscYlShi56f1vm7DQWw1eh1wHLdatidrQwNyDo=\n"
    // ADDITIONAL SECTION
    "a.gtld-servers.net. 172800 IN A 192.5.6.30\n"
    "b.gtld-servers.net. 172800 IN A 192.33.14.30\n"
    "c.gtld-servers.net. 172800 IN A 192.26.92.30\n"
    "d.gtld-servers.net. 172800 IN A 192.31.80.30\n"
    "e.gtld-servers.net. 172800 IN A 192.12.94.30\n"
    "f.gtld-servers.net. 172800 IN A 192.35.51.30\n"
    "g.gtld-servers.net. 172800 IN A 192.42.93.30\n"
    "h.gtld-servers.net. 172800 IN A 192.54.112.30\n"
    "i.gtld-servers.net. 172800 IN A 192.43.172.30\n"
    "j.gtld-servers.net. 172800 IN A 192.48.79.30\n"
    "k.gtld-servers.net. 172800 IN A 192.52.178.30\n"
    "l.gtld-servers.net. 172800 IN A 192.41.162.30\n"
    "m.gtld-servers.net. 172800 IN A 192.55.83.30\n"
    "a.gtld-servers.net. 172800 IN AAAA 2001:503:a83e::2:30\n"
    "b.gtld-servers.net. 172800 IN AAAA 2001:503:231d::2:30";

// Likewise, it's a response from a root server for www.example.notexistent.
// An example that involves a few more RRSIGs.
const char* const nxdomain_rrsets_txt =
    // AUTHORITY SECTION (NS)
    ". 86400 IN SOA a.root-servers.net. nstld.verisign-grs.com. 2012082901 1800 900 604800 86400\n"
    ". 86400 IN RRSIG SOA 8 0 86400 20120905000000 20120828230000 50398 . Wj6NgkA2TyJug9XfWYG/Cjh4d1JI99/Dv9S1TClbrhLdeMI4s9BEcBSA xdlPJN6L4uaupcYeEyRWGx3p0iq7VWFyjL4xy/+jXpUoHCgj0NlWa6eu C2litcnfcumTI97XJ5iod3ET+6vWnhwZQHDnz1fj4FuS8PPEJJ+Oy3M5 mcM=\n"
    ". 86400 IN NSEC ac. NS SOA RRSIG NSEC DNSKEY\n"
    ". 86400 IN RRSIG NSEC 8 0 86400 20120905000000 20120828230000 50398 . f8FEG1HzQtn/shZCdDgkB7TIpHAmH2hGlp5RubczukzD8XI3EGMVNoaf 2cUNPLpyhoBQkO1Rz+hANzI6Jkqq8PzhiQnLcW+y2Wl/BU2SaBQ2Otb2 5+VOOXux1veKaCZsRRU1VJnTUYguDayAgcS7BtB/rc7ez4nokkK98MA9 zcw=\n"
    "no. 86400 IN NSEC np. NS RRSIG NSEC\n"
    "no. 86400 IN RRSIG NSEC 8 1 86400 20120905000000 20120828230000 50398 . Z/E4hb6MMSpueGGjGoCWwnN2uKsQf88HPS1gbwVHBEhR+5eSn0BGqExs fQsjYL47SF/6pwMXjzmXCt8NPXXf9ImY/93GUuFL6j5OuL2MDIxt24MS u6hfxxiYTn+zF0dM8cn+UK5n1VEBB5JVJXf7FOr3OmaRLMD33Gl6yZJ/ l1E=";

void
usage() {
    std::cerr << "Usage: rrset_render_bench [-n iterations]" << std::endl;
    exit (1);
}

// Helper callback for masterLoad() used in main() to build test data.
void
setRRset(vector<ConstRRsetPtr>* rrsets, ConstRRsetPtr rrset) {
    rrsets->push_back(rrset);
}

void
buildZone(isc::util::MemorySegmentLocal& mem_sgmt,
          ZoneData* zone_data, const vector<ConstRRsetPtr>& rrsets,
          vector<ConstRRsetPtr>& rrsets_build)
{
    RdataEncoder encoder;

    for (vector<ConstRRsetPtr>::const_iterator it = rrsets.begin();
         it != rrsets.end();
         ++it)
    {
        ConstRRsetPtr rrset = *it;
        ZoneNode* node;
        zone_data->insertName(mem_sgmt, rrset->getName(), &node);

        // For simplicity, we assume that if the current RRset has a next
        // one that is of type RRSIG, that RRSIG should be associated with
        // the current RRset (which should be the case for our test data).
        ConstRRsetPtr sig_rrset;
        if ((it + 1) != rrsets.end() &&
            (*(it + 1))->getType() == RRType::RRSIG()) {
            sig_rrset = *(++it);
            assert(it != rrsets.end()); // to be safe, and silence cppcheck
        }
        RdataSet* rdataset =
            RdataSet::create(mem_sgmt, encoder, rrset, sig_rrset);
        rdataset->next = node->getData();
        node->setData(rdataset);

        rrsets_build.push_back(
            ConstRRsetPtr(new TreeNodeRRset(rrset->getClass(), node, rdataset,
                                            true)));
    }
}
}

int
main(int argc, char* argv[]) {
    int ch;
    int iteration = 100000;
    while ((ch = getopt(argc, argv, "n:")) != -1) {
        switch (ch) {
        case 'n':
            iteration = atoi(optarg);
            break;
        default:
            usage();
        }
    }
    argc -= optind;
    if (argc != 0) {
        usage();
    }

    // Build test data.  rrsets will consist of a list of RRsets corresponding
    // to the text defined above.
    vector<ConstRRsetPtr> delegation_rrsets;
    std::stringstream rrsets_stream(delegation_rrsets_txt);
    masterLoad(rrsets_stream, Name::ROOT_NAME(), RRClass::IN(),
               boost::bind(setRRset, &delegation_rrsets, _1));

    vector<ConstRRsetPtr> nxdomain_rrsets;
    std::stringstream rrsets_stream2(nxdomain_rrsets_txt);
    masterLoad(rrsets_stream2, Name::ROOT_NAME(), RRClass::IN(),
               boost::bind(setRRset, &nxdomain_rrsets, _1));

    // Build in-memory zone using RRsets constructed above, storing
    // the same set of RRsets as TreeNodeRRsets in separate vectors.
    // This code below is not 100% exception safe (for simplicity), but at
    // least it shouldn't leak memory in normal cases.
    isc::util::MemorySegmentLocal mem_sgmt;
    ZoneData* zone_data = ZoneData::create(mem_sgmt, Name::ROOT_NAME());
    vector<ConstRRsetPtr> delegation_treenode_rrsets;
    buildZone(mem_sgmt, zone_data, delegation_rrsets,
              delegation_treenode_rrsets);
    vector<ConstRRsetPtr> nxdomain_treenode_rrsets;
    buildZone(mem_sgmt, zone_data, nxdomain_rrsets,
              nxdomain_treenode_rrsets);

    // The benchmark test uses a message renderer.  Create it now and keep
    // using it throughout the test.
    isc::util::OutputBuffer buffer(4096); // 4096 should be sufficiently large
    MessageRenderer renderer;
    renderer.setBuffer(&buffer);

    std::cout << "Benchmark for rendering basic RRsets (delegation)"
              << std::endl;
    BenchMark<RRsetRenderBenchMark>(iteration,
                                    RRsetRenderBenchMark(delegation_rrsets,
                                                         renderer));

    std::cout << "Benchmark for rendering tree node RRsets (delegation)"
              << std::endl;
    BenchMark<RRsetRenderBenchMark>(iteration,
                                    RRsetRenderBenchMark(
                                        delegation_treenode_rrsets, renderer));

    std::cout << "Benchmark for rendering basic RRsets (nxdomain)"
              << std::endl;
    BenchMark<RRsetRenderBenchMark>(iteration,
                                    RRsetRenderBenchMark(nxdomain_rrsets,
                                                         renderer));

    std::cout << "Benchmark for rendering tree node RRsets (nxdomain)"
              << std::endl;
    BenchMark<RRsetRenderBenchMark>(iteration,
                                    RRsetRenderBenchMark(
                                        nxdomain_treenode_rrsets, renderer));

    // Cleanup, and memory leak check
    ZoneData::destroy(mem_sgmt, zone_data, RRClass::IN());
    assert(mem_sgmt.allMemoryDeallocated());

    return (0);
}
