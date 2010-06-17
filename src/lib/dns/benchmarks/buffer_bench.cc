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

#include <cassert>
#include <stdint.h>

#include <iostream>

#include <bench/benchmark.h>

#include <exceptions/exceptions.h>

#include <dns/buffer.h>

using namespace std;
using namespace isc;
using namespace isc::dns;
using namespace isc::bench;

namespace {
// A simplified buffer implementation using plain old array for comparison
// (omitting some validations for brevity)
class ArrayOutputBuffer {
public:
    ArrayOutputBuffer(size_t n) : limit_(n) {
        data_ = new uint8_t[n];
    }
    ~ArrayOutputBuffer() {
        delete[] data_;
    }
    void clear() { index_ = 0; }
    void writeUint8(const uint8_t data) {
        if (index_ + 1 > limit_) {
            isc_throw(InvalidBufferPosition, "write beyond the end of buffer");
        }
        data_[index_] = data;
        ++index_;
    }
    void writeUint16(const uint16_t data) {
        if (index_ + 2 > limit_) {
            isc_throw(InvalidBufferPosition, "write beyond the end of buffer");
        }
        const uint8_t net_data[2] = { (data & 0xff00U) >> 8, data & 0x00ffU };
        memcpy(&data_[index_], net_data, 2);
        index_ += 2;
    }
    void writeUint32(const uint32_t data) {
        if (index_ + 4 > limit_) {
            isc_throw(InvalidBufferPosition, "write beyond the end of buffer");
        }
        const uint8_t net_data[4] = { (data & 0xff000000) >> 24,
                                      (data & 0x00ff0000) >> 16,
                                      (data & 0x0000ff00) >> 8,
                                      data & 0x000000ff };
        memcpy(&data_[index_], net_data, 4);
        index_ += 4;
    }
    void writeData(const void *data, const size_t len) {
        if (len > limit_ || index_ > (limit_ - len)) {
            isc_throw(InvalidBufferPosition, "write beyond the end of buffer");
        }
        memcpy(&data_[index_], data, len);
        index_ += len;
    }
    size_t getLength() const { return (index_); }
    const void* getData() const { return (data_); }
private:
    const size_t limit_;
    size_t index_;
    uint8_t* data_;
};

const uint8_t check_data[] = {
    0x00, 0x01, 0x00, 0x01, 0x00, 0x00, 0x0e, 0x10, 192, 0, 2, 1,
    0x00, 0x01, 0x00, 0x01, 0x00, 0x00, 0x0e, 0x10,
    0x20, 0x01, 0x0d, 0xb8, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x12, 0x34 };

template <typename T>
class BufferBenchMark {
public:
    BufferBenchMark(T& buffer, const bool use_writedata) :
        buffer_(buffer), use_writedata_(use_writedata) {}
    ~BufferBenchMark() {}
    unsigned int run() {
        // This test emulates writing 20 RR-like objects into the given buffer.
        buffer_.clear();
        for (int i = 0; i < 20; ++i) {
            buffer_.writeUint16(rrtype_val_);
            buffer_.writeUint16(rrclass_val_);
            buffer_.writeUint32(rrttl_val_);

            const uint8_t* data;
            size_t datalen;
            if ((i % 2) == 0) {
                data = data_a;
                datalen = sizeof(data_a);
            } else {
                data = data_aaaa;
                datalen = sizeof(data_aaaa);
            }
            if (use_writedata_) {
                buffer_.writeData(data, datalen);
            } else {
                for (int j = 0; j < datalen; ++j) {
                    buffer_.writeUint8(data[j]);
                }
            }
        }
        return (1);
    }
    bool checkData() const {
        if (buffer_.getLength() < sizeof(check_data)) {
            isc_throw(Exception, "written buffer is too short: " <<
                      buffer_.getLength());
        }
        if (memcmp(buffer_.getData(), check_data, sizeof(check_data)) != 0) {
            isc_throw(Exception, "data mismatch");
        }
        return (true);
    }
    bool isUsingWriteData() const { return (use_writedata_); }
private:
    static const uint16_t rrtype_val_ = 1;
    static const uint16_t rrclass_val_ = 1;
    static const uint32_t rrttl_val_ = 3600;
    static const uint8_t data_a[4];
    static const uint8_t data_aaaa[16];
    T& buffer_;
    const bool use_writedata_;
};

template <typename T>
const uint8_t BufferBenchMark<T>::data_a[] = { 192, 0, 2, 1 };

template <typename T>
const uint8_t BufferBenchMark<T>::data_aaaa[] = {
    0x20, 0x01, 0x0d, 0xb8, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x12, 0x34 };
}

namespace isc {
namespace bench {
template <>
void
BenchMark<BufferBenchMark<OutputBuffer> >::setUp() {
    cout << "Benchmark for write operations using libdns OutputBuffer and "
         << (target_.isUsingWriteData() ? "writeData:" :
             "explicit loop:") << endl;
}

template <>
void
BenchMark<BufferBenchMark<OutputBuffer> >::tearDown() {
    assert(target_.checkData());
}

template <>
void
BenchMark<BufferBenchMark<ArrayOutputBuffer> >::setUp() {
    cout << "Benchmark for write operations using plain old array and "
         << (target_.isUsingWriteData() ? "writeData:" :
             "explicit loop:") << endl;
}

template <>
void
BenchMark<BufferBenchMark<ArrayOutputBuffer> >::tearDown() {
    assert(target_.checkData());
}
}
}

namespace {
void
usage() {
    cerr << "Usage: buffer_bench [-n iterations]" << endl;
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
    if (argc > 0) {
        usage();
    }

    OutputBuffer dns_buffer(4096);
    BufferBenchMark<OutputBuffer> buffer_bench(dns_buffer, true);
    BenchMark<BufferBenchMark<OutputBuffer> > bench1(iteration, buffer_bench);
    bench1.run();

    ArrayOutputBuffer array_buffer(4096);
    BufferBenchMark<ArrayOutputBuffer> array_bench(array_buffer, true);
    BenchMark<BufferBenchMark<ArrayOutputBuffer> > bench2(iteration,
                                                          array_bench);
    bench2.run();

    BufferBenchMark<OutputBuffer> buffer_bench2(dns_buffer, false);
    BenchMark<BufferBenchMark<OutputBuffer> > bench3(iteration, buffer_bench2);
    bench3.run();

    BufferBenchMark<ArrayOutputBuffer> array_bench2(array_buffer, false);
    BenchMark<BufferBenchMark<ArrayOutputBuffer> > bench4(iteration,
                                                          array_bench2);
    bench4.run();

    return (0);
}
