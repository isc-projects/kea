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

// $Id$

#ifndef __BUFFER_HH
#define __BUFFER_HH 1

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>

#include <stdint.h>
#include <string.h>

#include <stdexcept>
#include <algorithm>
#include <vector>

#include <dns/exceptions.h>

namespace isc {
// Abstraction of buffers for socket I/O.  This is a tentative idea and should
// be revisited.

class Buffer {
public:
    virtual ~Buffer() {}
    virtual void reserve(size_t len) = 0;
    virtual void write_data(const void *cp, size_t len) = 0;
    virtual void write_uint32(uint32_t data) = 0;
    virtual void write_uint16(uint16_t data) = 0;
    virtual void write_uint16_at(uint16_t data, size_t pos) = 0;
    virtual void write_uint8(uint8_t data) = 0;
    virtual int send_to(int s, const struct sockaddr& to, socklen_t to_len) = 0;

    virtual size_t get_size() const = 0;
    virtual size_t get_space() const = 0;
    virtual size_t get_current() const = 0;
    virtual uint8_t read_uint8() = 0;
    virtual uint16_t read_uint16() = 0;
    virtual int recv_from(int s, struct sockaddr *from,
                          socklen_t *from_len) = 0;
};

// I/O Buffer with a single array-style storage
class SingleBuffer : public Buffer {
public:
    SingleBuffer() : _readpos(0) { buf_.reserve(4096); }

    void reserve(size_t len) // XXX: API and implementation should be revisited
    {
        buf_.resize(len);
    }
    void write_data(const void *data, size_t len)
    {
        const uint8_t* cp = static_cast<const uint8_t*>(data);
        buf_.insert(buf_.end(), cp, cp + len);
    }
    void write_uint32(uint32_t data)
    {
        data = htonl(data);
        uint8_t* cp =  static_cast<uint8_t*>((void*)&data);
        buf_.insert(buf_.end(), cp, cp + sizeof(uint32_t));
    }
    void write_uint16(uint16_t data)
    {
        data = htons(data);
        uint8_t* cp =  static_cast<uint8_t*>((void*)&data);
        buf_.insert(buf_.end(), cp, cp + sizeof(uint16_t));
    }
    void write_uint16_at(uint16_t data, size_t pos)
    {
        if (pos + sizeof(data) >= buf_.size())
            throw isc::ISCBufferInvalidPosition();

        data = htons(data);
        uint8_t* cp =  static_cast<uint8_t*>((void*)&data);
        copy(cp, cp + sizeof(uint16_t), buf_.begin() + pos);
    }
    void write_uint8(uint8_t data)
    {
        buf_.push_back(data);
    }
    int send_to(int s, const struct sockaddr& to, socklen_t to_len);

    size_t get_size() const { return (buf_.size()); }
    size_t get_space() const { return (buf_.size() - _readpos); }
    size_t get_current() const { return (_readpos); }
    uint8_t read_uint8();
    uint16_t read_uint16();
    int recv_from(int s, struct sockaddr* from, socklen_t* from_len);

private:
    size_t _readpos;
    std::vector<uint8_t> buf_;
};

inline uint8_t
SingleBuffer::read_uint8()
{
    if (_readpos + sizeof(uint8_t) > buf_.size())
        throw ISCBufferInvalidPosition();

    return (buf_[_readpos++]);
}

inline uint16_t
SingleBuffer::read_uint16()
{
    uint16_t data;

    if (_readpos + sizeof(data) > buf_.size())
        throw ISCBufferInvalidPosition();

    memcpy((void*)&data, &buf_[_readpos], sizeof(data));
    _readpos += sizeof(data);

    return (ntohs(data));
}
}
#endif  // __BUFFER_HH

// Local Variables: 
// mode: c++
// End: 
