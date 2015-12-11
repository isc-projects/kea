// Copyright (C) 2012, 2015  Internet Systems Consortium, Inc. ("ISC")
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

#include <dns/name.h>
#include <dns/labelsequence.h>
#include <dns/messagerenderer.h>
#include <oldmessagerenderer.h>

#include <cassert>
#include <vector>

using namespace std;
using namespace isc::util;
using namespace isc::bench;
using namespace isc::dns;

namespace {
// This templated test performs rendering given set of names using
// a given (templated) MessageRenderer implementation.  We can check the
// performance when we modify the renderer implementation by comparing the
// old and new implementation for the same data.
template <typename T>
class MessageRendererBenchMark {
public:
    explicit MessageRendererBenchMark(const vector<Name>& names) :
        renderer_(NULL),
        names_(names)
    {}
    ~MessageRendererBenchMark() {
        delete renderer_;
    }
    unsigned int run() {
        if (renderer_ == NULL) {
            renderer_ = new T();
        }
        renderer_->clear();
        vector<Name>::const_iterator it = names_.begin();
        const vector<Name>::const_iterator it_end = names_.end();
        for (; it != it_end; ++it) {
            renderer_->writeName(*it);
        }
        // Make sure truncation didn't accidentally happen.
        assert(!renderer_->isTruncated());
        return (names_.size());
    }
private:
    T* renderer_; // It's pointer, so we won't need to copy it.
    const vector<Name>& names_;
};

//
// Builtin benchmark data.
//
// This consists of all names contained in a response from a root server for
// the query for "www.example.com" (as of this implementing).
const char* const root_to_com_names[] = {
    // question section
    "www.example.com",
    // authority section
    "com", "a.gtld-servers.net", "com", "b.gtld-servers.net",
    "com", "c.gtld-servers.net", "com", "d.gtld-servers.net",
    "com", "e.gtld-servers.net", "com", "f.gtld-servers.net",
    "com", "g.gtld-servers.net", "com", "h.gtld-servers.net",
    "com", "i.gtld-servers.net", "com", "j.gtld-servers.net",
    "com", "k.gtld-servers.net", "com", "l.gtld-servers.net",
    "com",                      // owner name of DS
    "com",                      // owner name of RRSIG(DS)
    // additional section.  a and b has both AAAA and A; others have A only.
    "a.gtld-servers.net", "a.gtld-servers.net",
    "b.gtld-servers.net", "b.gtld-servers.net",
    "c.gtld-servers.net", "d.gtld-servers.net", "e.gtld-servers.net",
    "f.gtld-servers.net", "g.gtld-servers.net", "h.gtld-servers.net",
    "i.gtld-servers.net", "j.gtld-servers.net", "k.gtld-servers.net",
    "l.gtld-servers.net", "m.gtld-servers.net",
    NULL
};

// Names contained a typical "NXDOMAIN" response: the question, the owner
// name of SOA, and its MNAME and RNAME.
const char* const example_nxdomain_names[] = {
    "www.example.com", "example.com", "ns.example.com", "root.example.com",
    NULL
};

// Names contained a typical "SERVFAIL" response: only the question.
const char* const example_servfail_names[] = {
    "www.example.com", NULL
};

// An experimental "dumb" renderer for comparison.  It doesn't do any name
// compression.  It simply ignores all setter method, returns a dummy value
// for getter methods, and write names to the internal buffer as plain binary
// data.
class DumbMessageRenderer : public AbstractMessageRenderer {
public:
    virtual void clear() {}
    virtual size_t getLengthLimit() const { return (512); }
    virtual void setLengthLimit(const size_t) {}
    virtual bool isTruncated() const { return (false); }
    virtual void setTruncated() {}
    virtual CompressMode getCompressMode() const { return (CASE_INSENSITIVE); }
    virtual void setCompressMode(const CompressMode) {}
    virtual void writeName(const Name& name, const bool = false) {
        name.toWire(getBuffer());
    }
    virtual void writeName(const LabelSequence&, const bool) {
        // We shouldn't use this version of writeName (and we internally
        // control it, so we simply assert it here)
        assert(false);
    }
};

void
usage() {
    cerr << "Usage: message_renderer_bench [-n iterations]" << endl;
    exit (1);
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

    cout << "Parameters:" << endl;
    cout << "  Iterations: " << iteration << endl;

    typedef pair<const char* const*, string> DataSpec;
    vector<DataSpec> spec_list;
    spec_list.push_back(DataSpec(root_to_com_names, "(positive response)"));
    spec_list.push_back(DataSpec(example_nxdomain_names,
                                 "(NXDOMAIN response)"));
    spec_list.push_back(DataSpec(example_servfail_names,
                                 "(SERVFAIL response)"));
    for (vector<DataSpec>::const_iterator it = spec_list.begin();
         it != spec_list.end();
         ++it) {
        vector<Name> names;
        for (size_t i = 0; it->first[i] != NULL; ++i) {
            names.push_back(Name(it->first[i]));
        }

        typedef MessageRendererBenchMark<OldMessageRenderer>
            OldRendererBenchMark;
        cout << "Benchmark for old MessageRenderer " << it->second << endl;
        BenchMark<OldRendererBenchMark>(iteration,
                                        OldRendererBenchMark(names));

        typedef MessageRendererBenchMark<DumbMessageRenderer>
            DumbRendererBenchMark;
        cout << "Benchmark for dumb MessageRenderer " << it->second << endl;
        BenchMark<DumbRendererBenchMark>(iteration,
                                         DumbRendererBenchMark(names));

        typedef MessageRendererBenchMark<MessageRenderer> RendererBenchMark;
        cout << "Benchmark for new MessageRenderer " << it->second << endl;
        BenchMark<RendererBenchMark>(iteration, RendererBenchMark(names));
    }

    return (0);
}
