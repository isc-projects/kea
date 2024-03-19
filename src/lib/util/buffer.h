// Copyright (C) 2009-2024 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef BUFFER_H
#define BUFFER_H

#include <exceptions/exceptions.h>

#include <boost/shared_ptr.hpp>

#include <cstring>
#include <stdint.h>
#include <stdlib.h>
#include <vector>

namespace isc {
namespace util {

/// @brief The @c InputBuffer class is a buffer abstraction for
/// manipulating read-only data.
///
/// The main purpose of this class is to provide a safe placeholder
/// for examining wire-format data received from a network.
///
/// Applications normally use this class only in a limited situation:
/// as an interface between legacy I/O operation (such as receiving
/// data from a BSD socket) and the rest of the Kea DNS library.  One
/// common usage of this class for an application would therefore be
/// something like this:
///
/// @code
///  unsigned char buf[1024];
///  struct sockaddr addr;
///  socklen_t addrlen = sizeof(addr);
///  int cc = recvfrom(s, buf, sizeof(buf), 0, &addr, &addrlen);
///  InputBuffer buffer(buf, cc);
///  // pass the buffer to a DNS message object to parse the message
/// @endcode
///
/// Other Kea DNS classes will then use methods of this class to get
/// access to the data, but the application normally doesn't have to
/// care about the details.
///
/// An @c InputBuffer object internally holds a reference to the given
/// data, rather than make a local copy of the data.  Also, it does
/// not have an ownership of the given data.  It is application's
/// responsibility to ensure the data remains valid throughout the
/// lifetime of the @c InputBuffer object.  Likewise, this object
/// generally assumes the data isn't modified throughout its lifetime;
/// if the application modifies the data while this object retains a
/// reference to it, the result is undefined.  The application will
/// also be responsible for releasing the data when it's not needed if
/// it was dynamically acquired.
///
/// This is a deliberate design choice: although it's safer to make a
/// local copy of the given data on construction, it would cause
/// unacceptable performance overhead, especially considering that a
/// DNS message can be as large as a few KB.  Alternatively, we could
/// allow the object to allocate memory internally and expose it to
/// the application to store network data in it.  This is also a bad
/// design, however, in that we would effectively break the
/// abstraction employed in the class, and do so by publishing
/// "read-only" stuff as a writable memory region.  Since there
/// doesn't seem to be a perfect solution, we have adopted what we
/// thought a "least bad" one.
///
/// Methods for reading data from the buffer generally work like an
/// input stream: it begins with the head of the data, and once some
/// length of data is read from the buffer, the next read operation
/// will take place from the head of the unread data.  An object of
/// this class internally holds (a notion of) where the next read
/// operation should start.  We call it the <em>current pointer</em>
/// in this document.
///
/// The inequality base_ <= current_ <= end_ is enforced, current_ ==
/// base_ at the initial state, current_ == end_ when the whole buffer
/// was read.  Even the difference of two pointers is a std::ptrdiff_t
/// it is safe to cast to a size_t because of the inequality.
class InputBuffer {
public:
    /// @brief Constructor.
    ///
    /// It is caller's responsibility to ensure that the data is valid
    /// as long as the buffer exists.
    /// @param data A pointer to the data stored in the buffer.
    /// @param len The length of the data in bytes.
    InputBuffer(const void* data, size_t len)
        : base_(static_cast<const uint8_t*>(data)), current_(base_),
          end_(base_ + len) {
    }

    /// @brief Return the length of the data stored in the buffer.
    size_t getLength() const {
        return (static_cast<size_t>(end_ - base_));
    }

    /// @brief Return the current read position.
    size_t getPosition() const {
        return (static_cast<size_t>(current_ - base_));
    }

    /// @brief Set the read position of the buffer to the given value.
    ///
    /// The new position must be in the valid range of the buffer;
    /// otherwise an exception of class @c isc::OutOfRange will be thrown.
    ///
    /// @param position The new position (offset from the beginning of
    /// the buffer).
    void setPosition(size_t position) {
        if (base_ + position > end_) {
            isc_throw(OutOfRange,
                      "InputBuffer::setPosition position is too large");
        }
        current_ = base_ + position;
    }

    /// @brief Peek an unsigned 8-bit integer from the buffer and return it.
    ///
    /// If the remaining length of the buffer is smaller than 8-bit,
    /// an exception of class @c isc::OutOfRange will be thrown.
    uint8_t peekUint8() {
        if (current_ + sizeof(uint8_t) > end_) {
            isc_throw(OutOfRange,
                      "InputBuffer::peekUint8 read beyond end of buffer");
        }

        return (*current_);
    }

    /// @brief Read an unsigned 8-bit integer from the buffer and return it.
    ///
    /// If the remaining length of the buffer is smaller than 8-bit,
    /// an exception of class @c isc::OutOfRange will be thrown.
    uint8_t readUint8() {
        uint8_t ret = peekUint8();
        current_ += sizeof(uint8_t);

        return (ret);
    }

    /// @brief Peek an unsigned 16-bit integer in network byte order
    /// from the buffer, and return it.
    ///
    /// If the remaining length of the buffer is smaller than 16-bit,
    /// an exception of class @c isc::OutOfRange will be thrown.
    uint16_t peekUint16() {
        if (current_ + sizeof(uint16_t) > end_) {
            isc_throw(OutOfRange,
                      "InputBuffer::peekUint16 read beyond end of buffer");
        }

        uint16_t ret;
        ret = (static_cast<uint16_t>(current_[0])) << 8;
        ret |= (static_cast<uint16_t>(current_[1]));

        return (ret);
    }

    /// @brief Read an unsigned 16-bit integer in network byte order
    /// from the buffer, and return it.
    ///
    /// If the remaining length of the buffer is smaller than 16-bit,
    /// an exception of class @c isc::OutOfRange will be thrown.
    uint16_t readUint16() {
        uint16_t ret = peekUint16();
        current_ += sizeof(uint16_t);

        return (ret);
    }

    /// @brief Read an unsigned 32-bit integer in network byte order
    /// from the buffer, and return it.
    ///
    /// If the remaining length of the buffer is smaller than 32-bit,
    /// an exception of class @c isc::OutOfRange will be thrown.
    uint32_t peekUint32() {
        if (current_ + sizeof(uint32_t) > end_) {
            isc_throw(OutOfRange,
                      "InputBuffer::peekUint32 read beyond end of buffer");
        }

        uint32_t ret;
        ret = (static_cast<uint32_t>(current_[0])) << 24;
        ret |= (static_cast<uint32_t>(current_[1])) << 16;
        ret |= (static_cast<uint32_t>(current_[2])) << 8;
        ret |= (static_cast<uint32_t>(current_[3]));

        return (ret);
    }

    /// @brief Read an unsigned 32-bit integer in network byte order
    /// from the buffer, and return it.
    ///
    /// If the remaining length of the buffer is smaller than 32-bit,
    /// an exception of class @c isc::OutOfRange will be thrown.
    uint32_t readUint32() {
        uint32_t ret = peekUint32();
        current_ += sizeof(uint32_t);

        return (ret);
    }

    /// @brief Peek data of the specified length from the buffer and
    /// copy it to the caller supplied buffer.
    ///
    /// The data is copied as stored in the buffer; no conversion is
    /// performed.  If the remaining length of the buffer is smaller
    /// than the specified length, an exception of class @c isc::OutOfRange
    /// will be thrown.
    void peekData(void* data, size_t len) {
        if (current_ + len > end_) {
            isc_throw(OutOfRange,
                      "InputBuffer::peekData read beyond end of buffer");
        }

        static_cast<void>(std::memmove(data, current_, len));
    }

    /// @brief Read data of the specified length from the buffer and
    /// copy it to the caller supplied buffer.
    ///
    /// The data is copied as stored in the buffer; no conversion is
    /// performed.  If the remaining length of the buffer is smaller
    /// than the specified length, an exception of class @c isc::OutOfRange
    /// will be thrown.
    void readData(void* data, size_t len) {
        peekData(data, len);
        current_ += len;
    }

    /// @brief Peek specified number of bytes as a vector.
    ///
    /// If specified buffer is too short, it will be expanded using
    /// vector::resize() method. If the remaining length of the buffer
    /// is smaller than the specified length, an exception of class
    /// @c isc::OutOfRange will be thrown.
    ///
    /// @param data Reference to a buffer (data will be stored there).
    /// @param len Size specified number of bytes to read in a vector.
    void peekVector(std::vector<uint8_t>& data, size_t len) {
        if (current_ + len > end_) {
            isc_throw(OutOfRange,
                      "InputBuffer::peekVector read beyond end of buffer");
        }

        data.resize(len);
        peekData(&data[0], len);
    }

    /// @brief Read specified number of bytes as a vector.
    ///
    /// If specified buffer is too short, it will be expanded using
    /// vector::resize() method. If the remaining length of the buffer
    /// is smaller than the specified length, an exception of class
    /// @c isc::OutOfRange will be thrown.
    ///
    /// @param data Reference to a buffer (data will be stored there).
    /// @param len Size specified number of bytes to read in a vector.
    void readVector(std::vector<uint8_t>& data, size_t len) {
        peekVector(data, len);
        current_ += len;
    }

private:
    /// @brief Base of the buffer.
    const uint8_t* base_;

    /// @brief Current poisition in the buffer.
    const uint8_t* current_;

    /// @brief End of the buffer (address of the byte after).
    const uint8_t* end_;
};

/// @brief Type of pointers to input buffer.
typedef boost::shared_ptr<InputBuffer> InputBufferPtr;

/// @brief The @c OutputBuffer class is a buffer abstraction for
/// manipulating mutable data.
///
/// The main purpose of this class is to provide a safe workplace for
/// constructing wire-format data to be sent out to a network.  Here,
/// <em>safe</em> means that it automatically allocates necessary
/// memory and avoid buffer overrun.
///
/// Like for the @c InputBuffer class, applications normally use this
/// class only in a limited situation.  One common usage of this class
/// for an application would be something like this:
///
/// @code
///  OutputBuffer buffer(4096); // give a sufficiently large initial size
///  // pass the buffer to a DNS message object to construct a wire-format
///  // DNS message.
///  struct sockaddr to;
///  sendto(s, buffer.getDataAsVoidPtr(), buffer.getLength(), 0, &to, sizeof(to));
/// @endcode
///
/// where the @c getData() (in fact @getDataAsVoidPtr()) method gives
/// a reference to the internal memory region stored in the @c buffer
/// object.  This is a suboptimal design in that it exposes an
/// encapsulated "handle" of an object to its user.  Unfortunately,
/// there is no easy way to avoid this without involving expensive
/// data copy if we want to use this object with a legacy API such as
/// a BSD socket interface.  And, indeed, this is one major purpose
/// for this object.  Applications should use this method only under
/// such a special circumstance.  It should also be noted that the
/// memory region returned by @c getData() may be invalidated after a
/// subsequent write operation.
///
/// An @c OutputBuffer class object automatically extends its memory
/// region when data is written beyond the end of the current buffer.
/// However, it will involve performance overhead such as reallocating
/// more memory and copying data.  It is therefore recommended to
/// construct the buffer object with a sufficiently large initial
/// size.  The @c getCapacity() method provides the current maximum
/// size of data (including the portion already written) that can be
/// written into the buffer without causing memory reallocation.
///
/// Methods for writing data into the buffer generally work like an
/// output stream: it begins with the head of the buffer, and once
/// some length of data is written into the buffer, the next write
/// operation will take place from the end of the buffer.  Other
/// methods to emulate "random access" are also provided (e.g., @c
/// writeUint16At()).  The normal write operations are normally
/// exception-free as this class automatically extends the buffer when
/// necessary.  However, in extreme cases such as an attempt of
/// writing multi-GB data, a separate exception (e.g., @c
/// std::bad_alloc) may be thrown by the system.  This also applies to
/// the constructor with a very large initial size.
///
/// Note to developers: it may make more sense to introduce an
/// abstract base class for the @c OutputBuffer and define the simple
/// implementation as a concrete derived class.  That way we can
/// provide flexibility for future extension such as more efficient
/// buffer implementation or allowing users to have their own
/// customized version without modifying the source code.  We in fact
/// considered that option, but at the moment chose the simpler
/// approach with a single concrete class because it may make the
/// implementation unnecessarily complicated while we were still not
/// certain if we really want that flexibility.  We may revisit the
/// class design as we see more applications of the class.  The same
/// considerations apply to the @c InputBuffer and @c MessageRenderer
/// classes.
class OutputBuffer {
public:
    /// @brief Constructor.
    ///
    /// @param len The initial allocated length of the buffer in bytes.
    OutputBuffer(size_t len) : buffer_() {
        if (len != 0) {
            buffer_.reserve(len);
        }
    }

    /// @brief Copy constructor.
    ///
    /// @param other Source object from which to make a copy.
    OutputBuffer(const OutputBuffer& other) : buffer_(other.buffer_) {
        size_t len = other.buffer_.capacity();
        if (len != 0) {
            buffer_.reserve(len);
        }
    }

    /// @brief Destructor.
    ~OutputBuffer() = default;

    /// @brief Assignment operator.
    ///
    /// @param other Object to copy into "this".
    OutputBuffer& operator =(const OutputBuffer& other) {
        if (this != &other) {
            // Not self-assignment.
            buffer_ = other.buffer_;
            size_t len = other.buffer_.capacity();
            if (len != 0) {
                buffer_.reserve(len);
            }
        }
        return (*this);
    }

    /// @brief Return the current capacity of the buffer.
    size_t getCapacity() const {
        return (buffer_.capacity());
    }

    /// @brief Return a pointer to the head of the data stored in the buffer.
    ///
    /// The caller can assume that the subsequent @c getLength() bytes
    /// are identical to the stored data of the buffer.
    ///
    /// Note: The pointer returned by this method may be invalidated
    /// after a subsequent write operation.
    const uint8_t* getData() const {
        if (!buffer_.empty()) {
            return (&buffer_[0]);
        } else {
            return (0);
        }
    }

    /// @brief Return data as a pointer to void.
    const void* getDataAsVoidPtr() const {
        return (static_cast<const void*>(getData()));
    }

    /// @brief Return the length of data written in the buffer.
    size_t getLength() const {
        return (buffer_.size());
    }

    /// @brief Return the value of the buffer at the specified position.
    ///
    /// @c pos must specify the valid position of the buffer;
    /// otherwise an exception class of @c isc::OutOfRange will
    /// be thrown.
    ///
    /// @param pos The position in the buffer to be returned.
    uint8_t operator[](size_t pos) const {
        if (pos >= buffer_.size()) {
            isc_throw(OutOfRange,
                      "OutputBuffer::[]: pos (" << pos
                      << ") >= size (" << buffer_.size() << ")");
        }
        return (buffer_[pos]);
    }

    /// @brief Return the buffer.
    ///
    /// @note The main use is to avoid a copy.
    const std::vector<uint8_t>& getVector() const {
        return (buffer_);
    }

    /// @brief Insert a specified length of gap at the end of the buffer.
    ///
    /// The caller should not assume any particular value to be
    /// inserted.  This method is provided as a shortcut to make a
    /// hole in the buffer that is to be filled in later, e.g, by
    /// @ref writeUint16At().
    ///
    /// @param len The length of the gap to be inserted in bytes.
    void skip(size_t len) {
        buffer_.resize(buffer_.size() + len);
    }

    /// @brief Trim the specified length of data from the end of the buffer.
    ///
    /// The specified length must not exceed the current data size of
    /// the buffer; otherwise an exception of class @c isc::OutOfRange
    /// will be thrown.
    ///
    /// @param len The length of data that should be trimmed.
    void trim(size_t len) {
        if (len > buffer_.size()) {
            isc_throw(OutOfRange,
                      "OutputBuffer::trim length too large from output buffer");
        }
        buffer_.resize(buffer_.size() - len);
    }

    /// @brief Clear buffer content.
    void clear() {
        buffer_.clear();
    }

    /// @brief Write an unsigned 8-bit integer into the buffer.
    ///
    /// @param data The 8-bit integer to be written into the buffer.
    void writeUint8(uint8_t data) {
        buffer_.push_back(data);
    }

    /// @brief Write an unsigned 8-bit integer into the buffer.
    ///
    /// The position must be lower than the size of the buffer,
    /// otherwise an exception of class @c isc::OutOfRange will
    /// be thrown.
    ///
    /// @param data The 8-bit integer to be written into the buffer.
    /// @param pos The position in the buffer to write the data.
    void writeUint8At(uint8_t data, size_t pos) {
        if (pos + sizeof(data) > buffer_.size()) {
            isc_throw(OutOfRange,
                      "OutputBuffer::writeUint8At write at invalid position");
        }
        buffer_[pos] = data;
    }

    /// @brief Write an unsigned 16-bit integer in host byte order
    /// into the buffer in network byte order.
    ///
    /// @param data The 16-bit integer to be written into the buffer.
    void writeUint16(uint16_t data) {
        buffer_.push_back(static_cast<uint8_t>((data & 0xff00U) >> 8));
        buffer_.push_back(static_cast<uint8_t>(data & 0x00ffU));
    }

    /// @brief Write an unsigned 16-bit integer in host byte order at
    /// the specified position of the buffer in network byte order.
    ///
    /// The buffer must have a sufficient room to store the given data
    /// at the given position, that is, <code>pos + 2 <
    /// getLength()</code>; otherwise an exception of class
    /// @c isc::OutOfRange will be thrown.
    /// Note also that this method never extends the buffer.
    ///
    /// @param data The 16-bit integer to be written into the buffer.
    /// @param pos The beginning position in the buffer to write the data.
    void writeUint16At(uint16_t data, size_t pos) {
        if (pos + sizeof(data) > buffer_.size()) {
            isc_throw(OutOfRange,
                      "OutputBuffer::writeUint16At write at invalid position");
        }

        buffer_[pos] = static_cast<uint8_t>((data & 0xff00U) >> 8);
        buffer_[pos + 1] = static_cast<uint8_t>(data & 0x00ffU);
    }

    /// @brief Write an unsigned 32-bit integer in host byte order
    /// into the buffer in network byte order.
    ///
    /// @param data The 32-bit integer to be written into the buffer.
    void writeUint32(uint32_t data) {
        buffer_.push_back(static_cast<uint8_t>((data & 0xff000000) >> 24));
        buffer_.push_back(static_cast<uint8_t>((data & 0x00ff0000) >> 16));
        buffer_.push_back(static_cast<uint8_t>((data & 0x0000ff00) >> 8));
        buffer_.push_back(static_cast<uint8_t>(data & 0x000000ff));
    }

    /// @brief Write an unsigned 64-bit integer in host byte order
    /// into the buffer in network byte order.
    ///
    /// @param data The 64-bit integer to be written into the buffer.
    void writeUint64(uint64_t data) {
        buffer_.push_back(static_cast<uint8_t>((data & 0xff00000000000000) >> 56));
        buffer_.push_back(static_cast<uint8_t>((data & 0x00ff000000000000) >> 48));
        buffer_.push_back(static_cast<uint8_t>((data & 0x0000ff0000000000) >> 40));
        buffer_.push_back(static_cast<uint8_t>((data & 0x000000ff00000000) >> 32));
        buffer_.push_back(static_cast<uint8_t>((data & 0x00000000ff000000) >> 24));
        buffer_.push_back(static_cast<uint8_t>((data & 0x0000000000ff0000) >> 16));
        buffer_.push_back(static_cast<uint8_t>((data & 0x000000000000ff00) >> 8));
        buffer_.push_back(static_cast<uint8_t>(data &  0x00000000000000ff));
    }

    /// @brief Copy an arbitrary length of data into the buffer.
    ///
    /// No conversion on the copied data is performed.
    ///
    /// @param data A pointer to the data to be copied into the buffer.
    /// @param len The length of the data in bytes.
    void writeData(const void *data, size_t len) {
        if (len == 0) {
            return;
        }

        const uint8_t* ptr = static_cast<const uint8_t*>(data);
        buffer_.insert(buffer_.end(), ptr, ptr + len);
    }

private:
    /// The actual data.
    std::vector<uint8_t> buffer_;
};

/// @brief Type of pointers to output buffers.
typedef boost::shared_ptr<OutputBuffer> OutputBufferPtr;

} // end of namespace util
} // end of namespace isc

#endif // BUFFER_H
