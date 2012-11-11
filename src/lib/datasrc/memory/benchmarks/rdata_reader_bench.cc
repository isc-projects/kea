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

#include <dns/name.h>
#include <dns/messagerenderer.h>
#include <dns/rrset.h>
#include <dns/rrclass.h>
#include <dns/masterload.h>

#include <datasrc/memory/rdata_serialization.h>

#include <boost/bind.hpp>

#include <vector>
#include <sstream>

#include <unistd.h>

using std::vector;
using namespace isc::bench;
using namespace isc::datasrc::memory;
using namespace isc::dns;

namespace {
struct EncodeParam {
    EncodeParam(RdataEncoder& encoder, ConstRRsetPtr rrset,
                ConstRRsetPtr sig_rrset = ConstRRsetPtr()) :
        rrclass(rrset->getClass()), rrtype(rrset->getType()),
        rdata_count(rrset->getRdataCount()),
        sig_count(sig_rrset ? sig_rrset->getRdataCount() : 0)
    {
        encoder.start(rrclass, rrtype);
        for (RdataIteratorPtr it = rrset->getRdataIterator();
             !it->isLast();
             it->next()) {
            encoder.addRdata(it->getCurrent());
        }
        if (sig_rrset) {
            for (RdataIteratorPtr it = sig_rrset->getRdataIterator();
                 !it->isLast();
                 it->next())
            {
                encoder.addSIGRdata(it->getCurrent());
            }
        }
        const size_t data_len = encoder.getStorageLength();
        data.resize(data_len);
        encoder.encode(&data[0], data.size());
    }
    RRClass rrclass;
    RRType rrtype;
    size_t rdata_count;
    size_t sig_count;
    vector<uint8_t> data;
};

// Encapsulating parameters for a RdataReader.  It extracts from the given
// RRset and its RRSIGs parameters that are necessary construct an RdataReader.
// RDATA data will be stored in the 'data' vector.
// members are defined as non const so we can use the object of this struct
// in a vector.
class ReaderBenchMark {
public:
    ReaderBenchMark(const vector<EncodeParam>& encode_params,
                    MessageRenderer& renderer) :
        encode_params_(encode_params), renderer_(renderer)
    {}
    unsigned int run() {
        vector<EncodeParam>::const_iterator it;
        const vector<EncodeParam>::const_iterator it_end =
            encode_params_.end();
        renderer_.clear();
        for (it = encode_params_.begin(); it != it_end; ++it) {
            RdataReader reader(it->rrclass, it->rrtype, &it->data[0],
                               it->rdata_count, it->sig_count,
                               boost::bind(&ReaderBenchMark::renderName,
                                           this, _1, _2),
                               boost::bind(&ReaderBenchMark::renderData,
                                           this, _1, _2));
            reader.iterate();
            reader.iterateAllSigs();
        }
        return (1);
    }
    void renderName(const LabelSequence& labels,
                    RdataNameAttributes attributes)
    {
        const bool compress =
            (attributes & NAMEATTR_COMPRESSIBLE) != 0;
        renderer_.writeName(labels, compress);
    }
    void renderData(const void* data, size_t data_len) {
        renderer_.writeData(data, data_len);
    }
private:
    const vector<EncodeParam>& encode_params_;
    MessageRenderer& renderer_;
};

// Builtin benchmark data.  This is a list of RDATA (of RRs) in a response
// from a root server for the query for "www.example.com" (as of this
// implementation).  We use a real world example to make the case practical.
const char* const rrsets_txt =
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

void
usage() {
    std::cerr << "Usage: rdata_reader_bench [-n iterations]" << std::endl;
    exit (1);
}

// Helper callback for masterLoad() used in main() to build test data.
void
setRRset(vector<ConstRRsetPtr>* rrsets, ConstRRsetPtr rrset) {
    rrsets->push_back(rrset);
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
        case '?':
        default:
            usage();
        }
    }
    argc -= optind;
    if (argc != 0) {
        usage();
    }

    // Build test data.  rrsets will consist of a list of RRsets corresponding
    // to rrsets_txt defined above.
    vector<ConstRRsetPtr> rrsets;
    std::stringstream rrsets_stream(rrsets_txt);
    masterLoad(rrsets_stream, Name::ROOT_NAME(), RRClass::IN(),
               boost::bind(setRRset, &rrsets, _1));

    // Create EncodeParam for each RRset (possibly with RRSIG) in rrsets,
    // and store them in encode_param_list.  It's the direct test input.
    vector<EncodeParam> encode_param_list;
    RdataEncoder encoder;
    encode_param_list.push_back(EncodeParam(encoder, rrsets.at(0)));
    encode_param_list.push_back(EncodeParam(encoder, rrsets.at(1),
                                            rrsets.at(2)));
    for (vector<ConstRRsetPtr>::const_iterator it = rrsets.begin() + 3;
         it != rrsets.end();
         ++it) {
        encode_param_list.push_back(EncodeParam(encoder, *it));
    }

    // The benchmark test uses a message renderer.  Create it now and keep
    // using it throughout the test.
    isc::util::OutputBuffer buffer(4096); // 4096 should be sufficiently large
    MessageRenderer renderer;
    renderer.setBuffer(&buffer);

    std::cout << "Benchmark for RdataReader" << std::endl;
    BenchMark<ReaderBenchMark>(iteration,
                                ReaderBenchMark(encode_param_list, renderer));
    return (0);
}
