// Copyright (C) 2010, 2015  Internet Systems Consortium, Inc. ("ISC")
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

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include <boost/shared_ptr.hpp>

#include <bench/benchmark.h>

#include <util/buffer.h>
#include <dns/messagerenderer.h>
#include <dns/rdata.h>
#include <dns/rdatafields.h>
#include <dns/rrclass.h>
#include <dns/rrtype.h>

using namespace std;
using namespace isc::bench;
using namespace isc::dns;
using namespace isc::dns::rdata;
using isc::util::OutputBuffer;

namespace {
// This templated benchmark class is constructed with a vector of Rdata-like
// (pointer) objects which should have a "toWire()" method.  In its run(),
// it calls toWire() for each element of the vector.
template <typename T>
class RdataRenderBenchMark {
public:
    explicit RdataRenderBenchMark(const vector<T>& dataset) :
        dataset_(dataset),
        renderer_(NULL)
    {}
    ~RdataRenderBenchMark() {
        delete renderer_;
    }
    unsigned int run() {
        if (renderer_ == NULL) {
            renderer_ = new MessageRenderer();
        }
        typename vector<T>::const_iterator data;
        typename vector<T>::const_iterator data_end = dataset_.end();
        for (data = dataset_.begin(); data != data_end; ++data) {
            renderer_->clear();
            (*data)->toWire(*renderer_);
        }
        return (dataset_.size());
    }
private:
    const vector<T>& dataset_;
    // Just-in-time initialized pointer, so no copy
    MessageRenderer* renderer_;
};

// This supplemental class emulates an RRset like class that internally
// uses RdataFields.  On construction it stores RDATA information in the
// form of RdataFields fields.  Its toWire() method restores the data as
// an RdataFields object for the rendering.
class RdataFieldsStore {
public:
    explicit RdataFieldsStore(ConstRdataPtr rdata) {
        const RdataFields fields(*rdata);

        spec_size_ = fields.getFieldSpecDataSize();
        spec_store_.resize(spec_size_);
        void* cp_spec = &spec_store_[0];
        memcpy(cp_spec, fields.getFieldSpecData(), spec_store_.size());
        spec_ptr_ = cp_spec;

        data_length_ = fields.getDataLength();
        data_store_.resize(data_length_);
        void* cp_data = &data_store_[0];
        memcpy(cp_data, fields.getData(), data_store_.size());
        // Vector guarantees that the elements are stored in continuous array
        // in memory, so this is actually correct by the standard
        data_ptr_ = cp_data;
    }
    void toWire(MessageRenderer& renderer) const {
        RdataFields(spec_ptr_, spec_size_,
                    data_ptr_, data_length_).toWire(renderer);
    }
private:
    vector<unsigned char> spec_store_;
    vector<unsigned char> data_store_;
    const void* spec_ptr_;
    const void* data_ptr_;
    unsigned int spec_size_;
    size_t data_length_;
};

// We wouldn't necessarily have to use a shared pointer, but it's easier
// to use pointer-like values to adjust them with the RdataRenderBenchMark
// template.
typedef boost::shared_ptr<const RdataFieldsStore> ConstRdataFieldsStorePtr;

void
readInputFile(const char* const input_file, vector<ConstRdataPtr>& rdata_sets,
              vector<ConstRdataFieldsStorePtr>& fields_sets)
{
    ifstream ifs;
    ifs.open(input_file, ios_base::in);
    if ((ifs.rdstate() & istream::failbit) != 0) {
        cerr << "Failed to read input file: " << input_file << endl;
        exit (1);
    }
    string line;
    unsigned int linenum = 0;
    while (getline(ifs, line), !ifs.eof()) {
        ++linenum;
        if (ifs.bad() || ifs.fail()) {
            cerr << "Unexpected input at line " << linenum << endl;
            exit (1);
        }
        if (line.empty() || line[0] == '#') {
            continue;           // skip comment and blank lines
        }
        istringstream iss(line);
        string rrclass_string, rrtype_string;
        stringbuf rdatabuf;
        iss >> rrclass_string >> rrtype_string >> &rdatabuf;
        if (iss.bad() || iss.fail()) {
            cerr << "Unexpected input at line " << linenum << endl;
            exit (1);
        }
        ConstRdataPtr rdata = createRdata(RRType(rrtype_string),
                                          RRClass(rrclass_string),
                                          rdatabuf.str());
        rdata_sets.push_back(rdata);
        fields_sets.push_back(ConstRdataFieldsStorePtr(
                                  new RdataFieldsStore(rdata)));
    }
    ifs.close();
}

void
usage() {
    cerr << "Usage: rdatafields_bench [-n iterations] input_file" << endl;
    exit (1);
}
}

int
main(int argc, char* argv[]) {
    int ch;
    int iteration = 10000;
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
    if (argc < 1) {
        usage();
    }
    const char* const input_file = argv[0];

    vector<ConstRdataPtr> rdata_sets;
    vector<ConstRdataFieldsStorePtr> fields_sets;

    readInputFile(input_file, rdata_sets, fields_sets);

    cout << "Parameters:" << endl;
    cout << "  Iterations: " << iteration << endl;
    cout << "  Input File: " << input_file << endl;

    typedef RdataRenderBenchMark<ConstRdataPtr> RdataBenchMark;
    cout << "Benchmark for rendering with standard Rdata" << endl;
    BenchMark<RdataBenchMark>(iteration, RdataBenchMark(rdata_sets));

    typedef RdataRenderBenchMark<ConstRdataFieldsStorePtr> FieldsBenchMark;
    cout << "Benchmark for rendering with RdataFields" << endl;
    BenchMark<FieldsBenchMark>(iteration, FieldsBenchMark(fields_sets));

    return (0);
}
