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

#include <unistd.h>             // for getpid

#include <cstdlib>              // for rand
#include <algorithm>
#include <iostream>
#include <vector>
#include <set>

#include <exceptions/exceptions.h>

#include <bench/benchmark.h>

using namespace std;
using namespace isc::bench;

namespace {
template <bool Sorted>
class VectorSearchBenchMark {
public:
    VectorSearchBenchMark(const vector<int>& data,
                          const vector<int>& keys) :
        data_(data), keys_(keys)
    {}
    unsigned int run() {
        vector<int>::const_iterator iter;
        vector<int>::const_iterator end_key = keys_.end();
        for (iter = keys_.begin(); iter != end_key; ++iter) {
            if (Sorted) {
                binary_search(data_.begin(), data_.end(), *iter);
            } else {
                find(data_.begin(), data_.end(), *iter);
            }
        }
        return (keys_.size());
    }
private:
    const vector<int>& data_;
    const vector<int>& keys_;
};

class SetSearchBenchMark {
public:
    SetSearchBenchMark(const set<int>& data, const vector<int>& keys) :
        data_(data), keys_(keys)
    {}
    unsigned int run() {
        vector<int>::const_iterator iter;
        vector<int>::const_iterator end_key = keys_.end();
        for (iter = keys_.begin(); iter != end_key; ++iter) {
            data_.find(*iter);
        }        
        return (keys_.size());
    }
public:   // make it visible to the BenchMark class
    const set<int>& data_;
private:
    const vector<int>& keys_;
};
}

namespace isc {
namespace bench {
template<>
void
BenchMark<SetSearchBenchMark>::setUp() {
    cout << "Benchmark for searching std::set (size="
         << target_.data_.size() << ")" << endl;    
}
}
}

namespace {
const int DEFAULT_ITERATION = 100;
const int DEFAULT_SIZE = 10000;

void
usage() {
    cerr << "Usage: search_bench [-n iterations] [-s data_size]" << endl;
    exit (1);
}
}

int
main(int argc, char* argv[]) {
    int ch;
    int iteration = DEFAULT_ITERATION;
    int size = DEFAULT_SIZE;
    while ((ch = getopt(argc, argv, "n:s:")) != -1) {
        switch (ch) {
        case 'n':
            iteration = atoi(optarg);
            break;
        case 's':
            size = atoi(optarg);
            break;
        case '?':
        default:
            usage();
        }
    }
    argc -= optind;
    argv += optind;
    if (argc != 0) {
        usage();
    }

    srand(getpid());
    vector<int> data_vector;
    set<int> data_set;
    vector<int> keys;
    for (int i = 0; i < size; ++i) {
        data_vector.push_back(i);
        data_set.insert(i);
        keys.push_back(rand() % size);
    }

    cout << "Benchmark for linear search" << endl;
    BenchMark<VectorSearchBenchMark<false> >(iteration,
                                             VectorSearchBenchMark<false>(
                                                 data_vector, keys));
    cout << "Benchmark for binary search" << endl;
    BenchMark<VectorSearchBenchMark<true> >(iteration,
                                             VectorSearchBenchMark<true>(
                                                 data_vector, keys));
    BenchMark<SetSearchBenchMark>(iteration,
                                  SetSearchBenchMark(data_set, keys));
    return (0);
}
