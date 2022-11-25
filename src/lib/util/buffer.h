// Copyright (C) 2009-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef BUFFER_H
#define BUFFER_H 1

#include <stdlib.h>
#include <cstring>
#include <vector>

#include <stdint.h>

#include <exceptions/exceptions.h>

#include <boost/shared_ptr.hpp>

namespace isc {
namespace util {

///
/// \brief A standard DNS module exception that is thrown if an out-of-range
/// buffer operation is being performed.
///
class InvalidBufferPosition : public Exception {
public:
    InvalidBufferPosition(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) {}
};

///\brief The \c InputBuffer class is a buffer abstraction for manipulating
/// read-only data.
///
/// The main purpose of this class is to provide a safe placeholder for
/// examining wire-format data received from a network.
///
/// Applications normally use this class only in a limited situation: as an
/// interface between legacy I/O operation (such as receiving data from a BSD
/// socket) and the rest of the Kea DNS library.  One common usage of this
/// class for an application would therefore be something like this:
///
/// \code unsigned char buf[1024];
/// struct sockaddr addr;
/// socklen_t addrlen = sizeof(addr);
/// int cc = recvfrom(s, buf, sizeof(buf), 0, &addr, &addrlen);
/// InputBuffer buffer(buf, cc);
/// // pass the buffer to a DNS message object to parse the message \endcode
///
/// Other Kea DNS classes will then use methods of this class to get access
/// to the data, but the application normally doesn't have to care about the
/// details.
///
/// An \c InputBuffer object internally holds a reference to the given data,
/// rather than make a local copy of the data.  Also, it does not have an
/// ownership of the given data.  It is application's responsibility to ensure
/// the data remains valid throughout the lifetime of the \c InputBuffer
/// object.  Likewise, this object generally assumes the data isn't modified
/// throughout its lifetime; if the application modifies the data while this
/// object retains a reference to it, the result is undefined.  The application
/// will also be responsible for releasing the data when it's not needed if it
/// was dynamically acquired.
///
/// This is a deliberate design choice: although it's safer to make a local
/// copy of the given data on construction, it would cause unacceptable
/// performance overhead, especially considering that a DNS message can be
/// as large as a few KB.  Alternatively, we could allow the object to allocate
/// memory internally and expose it to the application to store network data
/// in it.  This is also a bad design, however, in that we would effectively
/// break the abstraction employed in the class, and do so by publishing
/// "read-only" stuff as a writable memory region.  Since there doesn't seem to
/// be a perfect solution, we have adopted what we thought a "least bad" one.
///
/// Methods for reading data from the buffer generally work like an input
/// stream: it begins with the head of the data, and once some length of data
/// is read from the buffer, the next read operation will take place from the
/// head of the unread data.  An object of this class internally holds (a
/// notion of) where the next read operation should start.  We call it the
/// <em>read position</em> in this document.
class InputBuffer {
public:
    ///
    /// \name Constructors and Destructor
    //@{
    /// \brief Constructor from variable length of data.
    ///
    /// It is caller's responsibility to ensure that the data is valid as long
    /// as the buffer exists.
    /// \param data A pointer to the data stored in the buffer.
    /// \param len The length of the data in bytes.
    InputBuffer(const void* data, size_t len) :
        position_(0), data_(static_cast<const uint8_t*>(data)), len_(len) {}
    //@}

    ///
    /// \name Getter Methods
    //@{
    /// \brief Return the length of the data stored in the buffer.
    size_t getLength() const { return (len_); }
    /// \brief Return the current read position.
    size_t getPosition() const { return (position_); }
    //@}

    ///
    /// \name Setter Methods
    ///
    //@{
    /// \brief Set the read position of the buffer to the given value.
    ///
    /// The new position must be in the valid range of the buffer; otherwise
    /// an exception of class \c isc::dns::InvalidBufferPosition will be thrown.
    /// \param position The new position (offset from the beginning of the
    /// buffer).
    void setPosition(size_t position) {
        if (position > len_) {
            throwError("position is too large");
        }
        position_ = position;
    }
    //@}

    ///
    /// \name Methods for reading data from the buffer.
    //@{
    /// \brief Read an unsigned 8-bit integer from the buffer and return it.
    ///
    /// If the remaining length of the buffer is smaller than 8-bit, an
    /// exception of class \c isc::dns::InvalidBufferPosition will be thrown.
    uint8_t readUint8() {
        if (position_ + sizeof(uint8_t) > len_) {
            throwError("read beyond end of buffer");
        }

        return (data_[position_++]);
    }
    /// \brief Read an unsigned 16-bit integer in network byte order from the
    /// buffer, convert it to host byte order, and return it.
    ///
    /// If the remaining length of the buffer is smaller than 16-bit, an
    /// exception of class \c isc::dns::InvalidBufferPosition will be thrown.
    uint16_t readUint16() {
        uint16_t data;
        const uint8_t* cp;

        if (position_ + sizeof(data) > len_) {
            throwError("read beyond end of buffer");
        }

        cp = &data_[position_];
        data = ((unsigned int)(cp[0])) << 8;
        data |= ((unsigned int)(cp[1]));
        position_ += sizeof(data);

        return (data);
    }
    /// \brief Read an unsigned 32-bit integer in network byte order from the
    /// buffer, convert it to host byte order, and return it.
    ///
    /// If the remaining length of the buffer is smaller than 32-bit, an
    /// exception of class \c isc::dns::InvalidBufferPosition will be thrown.
    uint32_t readUint32() {
        uint32_t data;
        const uint8_t* cp;

        if (position_ + sizeof(data) > len_) {
            throwError("read beyond end of buffer");
        }

        cp = &data_[position_];
        data = ((unsigned int)(cp[0])) << 24;
        data |= ((unsigned int)(cp[1])) << 16;
        data |= ((unsigned int)(cp[2])) << 8;
        data |= ((unsigned int)(cp[3]));
        position_ += sizeof(data);

        return (data);
    }
    /// \brief Read data of the specified length from the buffer and copy it to
    /// the caller supplied buffer.
    ///
    /// The data is copied as stored in the buffer; no conversion is performed.
    /// If the remaining length of the buffer is smaller than the specified
    /// length, an exception of class \c isc::dns::InvalidBufferPosition will
    /// be thrown.
    void readData(void* data, size_t len) {
        if (position_ + len > len_) {
            throwError("read beyond end of buffer");
        }

        static_cast<void>(std::memmove(data, &data_[position_], len));
        position_ += len;
    }
    //@}

    /// @brief Read specified number of bytes as a vector.
    ///
    /// If specified buffer is too short, it will be expanded
    /// using vector::resize() method.
    ///
    /// @param data Reference to a buffer (data will be stored there).
    /// @param len Size specified number of bytes to read in a vector.
    ///
    void readVector(std::vector<uint8_t>& data, size_t len) {
        if (position_ + len > len_) {
            throwError("read beyond end of buffer");
        }

        data.resize(len);
        readData(&data[0], len);
    }

private:
    /// \brief A common helper to throw an exception on invalid operation.
    ///
    /// Experiments showed that throwing from each method makes the buffer
    /// operation slower, so we consolidate it here, and let the methods
    /// call this.
    static void throwError(const char* msg) {
        isc_throw(InvalidBufferPosition, msg);
    }

    size_t position_;

    // XXX: The following must be private, but for a short term workaround with
    // Boost.Python binding, we changed it to protected.  We should soon
    // revisit it.
protected:
    const uint8_t* data_;
    size_t len_;
};

///
///\brief The \c OutputBuffer class is a buffer abstraction for manipulating
/// mutable data.
///
/// The main purpose of this class is to provide a safe workplace for
/// constructing wire-format data to be sent out to a network.  Here,
/// <em>safe</em> means that it automatically allocates necessary memory and
/// avoid buffer overrun.
///
/// Like for the \c InputBuffer class, applications normally use this class only
/// in a limited situation.  One common usage of this class for an application
/// would be something like this:
///
/// \code OutputBuffer buffer(4096); // give a sufficiently large initial size
/// // pass the buffer to a DNS message object to construct a wire-format
/// // DNS message.
/// struct sockaddr to;
/// sendto(s, buffer.getData(), buffer.getLength(), 0, &to, sizeof(to));
/// \endcode
///
/// where the \c getData() method gives a reference to the internal memory
/// region stored in the \c buffer object.  This is a suboptimal design in that
/// it exposes an encapsulated "handle" of an object to its user.
/// Unfortunately, there is no easy way to avoid this without involving
/// expensive data copy if we want to use this object with a legacy API such as
/// a BSD socket interface.  And, indeed, this is one major purpose for this
/// object.  Applications should use this method only under such a special
/// circumstance.  It should also be noted that the memory region returned by
/// \c getData() may be invalidated after a subsequent write operation.
///
/// An \c OutputBuffer class object automatically extends its memory region when
/// data is written beyond the end of the current buffer.  However, it will
/// involve performance overhead such as reallocating more memory and copying
/// data.  It is therefore recommended to construct the buffer object with a
/// sufficiently large initial size.
/// The \c getCapacity() method provides the current maximum size of data
/// (including the portion already written) that can be written into the buffer
/// without causing memory reallocation.
///
/// Methods for writing data into the buffer generally work like an output
/// stream: it begins with the head of the buffer, and once some length of data
/// is written into the buffer, the next write operation will take place from
/// the end of the buffer.  Other methods to emulate "random access" are also
/// provided (e.g., \c writeUint16At()).  The normal write operations are
/// normally exception-free as this class automatically extends the buffer
/// when necessary.  However, in extreme cases such as an attempt of writing
/// multi-GB data, a separate exception (e.g., \c std::bad_alloc) may be thrown
/// by the system.  This also applies to the constructor with a very large
/// initial size.
///
/// Note to developers: it may make more sense to introduce an abstract base
/// class for the \c OutputBuffer and define the simple implementation as a
/// concrete derived class.  That way we can provide flexibility for future
/// extension such as more efficient buffer implementation or allowing users
/// to have their own customized version without modifying the source code.
/// We in fact considered that option, but at the moment chose the simpler
/// approach with a single concrete class because it may make the
/// implementation unnecessarily complicated while we were still not certain
/// if we really want that flexibility.  We may revisit the class design as
/// we see more applications of the class.  The same considerations apply to
/// the \c InputBuffer and \c MessageRenderer classes.
class OutputBuffer {
public:
    ///
    /// \name Constructors and Destructor
    ///
    //@{
    /// \brief Constructor from the initial size of the buffer.
    ///
    /// \param len The initial length of the buffer in bytes.
    OutputBuffer(size_t len) :
        buffer_(NULL),
        size_(0),
        allocated_(len)
    {
        // We use malloc and free instead of C++ new[] and delete[].
        // This way we can use realloc, which may in fact do it without a copy.
        if (allocated_ != 0) {
            buffer_ = static_cast<uint8_t*>(malloc(allocated_));
            if (buffer_ == NULL) {
                throw std::bad_alloc();
            }
        }
    }

    /// \brief Copy constructor
    ///
    /// \param other Source object from which to make a copy.
    ///
    /// \note It is assumed that the source object is consistent, i.e.
    /// size_ <= allocated_, and that if allocated_ is greater than zero,
    /// buffer_ points to valid memory.
    OutputBuffer(const OutputBuffer& other) :
        buffer_(NULL),
        size_(other.size_),
        allocated_(other.allocated_)
    {
        if (allocated_ != 0) {
            buffer_ = static_cast<uint8_t*>(malloc(allocated_));
            if (buffer_ == NULL) {
                throw std::bad_alloc();
            }
            static_cast<void>(std::memmove(buffer_, other.buffer_, other.size_));
        }
    }

    /// \brief Destructor
    ~OutputBuffer() {
        free(buffer_);
    }
    //@}

    /// \brief Assignment operator
    ///
    /// \param other Object to copy into "this".
    ///
    /// \note It is assumed that the source object is consistent, i.e.
    /// size_ <= allocated_, and that if allocated_ is greater than zero,
    /// buffer_ points to valid memory.
    OutputBuffer& operator =(const OutputBuffer& other) {
        if (this != &other) {
            // Not self-assignment.
            if (other.allocated_ != 0) {

                // There is something in the source object, so allocate memory
                // and copy it.  The pointer to the allocated memory is placed
                // in a temporary variable so that if the allocation fails and
                // an exception is thrown, the destination object ("this") is
                // unchanged.
                uint8_t* newbuff = static_cast<uint8_t*>(malloc(other.allocated_));
                if (newbuff == NULL) {
                    throw std::bad_alloc();
                }

                // Memory allocated, update the source object and copy data
                // across.
                free(buffer_);
                buffer_ = newbuff;
                static_cast<void>(std::memmove(buffer_, other.buffer_, other.size_));

            } else {

                // Nothing allocated in the source object, so zero the buffer
                // in the destination.
                free(buffer_);
                buffer_ = NULL;
            }

            // Update the other member variables.
            size_ = other.size_;
            allocated_ = other.allocated_;
        }
        return (*this);
    }

    ///
    /// \name Getter Methods
    ///
    //@{
    /// \brief Return the current capacity of the buffer.
    size_t getCapacity() const { return (allocated_); }
    /// \brief Return a pointer to the head of the data stored in the buffer.
    ///
    /// The caller can assume that the subsequent \c getLength() bytes are
    /// identical to the stored data of the buffer.
    ///
    /// Note: The pointer returned by this method may be invalidated after a
    /// subsequent write operation.
    const void* getData() const { return (buffer_); }
    /// \brief Return the length of data written in the buffer.
    size_t getLength() const { return (size_); }
    /// \brief Return the value of the buffer at the specified position.
    ///
    /// \c pos must specify the valid position of the buffer; otherwise an
    /// exception class of \c InvalidBufferPosition will be thrown.
    ///
    /// \param pos The position in the buffer to be returned.
    uint8_t operator[](size_t pos) const {
        if (pos >= size_) {
            isc_throw(InvalidBufferPosition,
                      "[]: pos (" << pos << ") >= size (" << size_ << ")");
        }
        return (buffer_[pos]);
    }
    //@}

    ///
    /// \name Methods for writing data into the buffer.
    ///
    //@{
    /// \brief Insert a specified length of gap at the end of the buffer.
    ///
    /// The caller should not assume any particular value to be inserted.
    /// This method is provided as a shortcut to make a hole in the buffer
    /// that is to be filled in later, e.g, by \ref writeUint16At().
    /// \param len The length of the gap to be inserted in bytes.
    void skip(size_t len) {
        ensureAllocated(size_ + len);
        size_ += len;
    }

    /// \brief Trim the specified length of data from the end of the buffer.
    ///
    /// The specified length must not exceed the current data size of the
    /// buffer; otherwise an exception of class \c isc::OutOfRange will
    /// be thrown.
    ///
    /// \param len The length of data that should be trimmed.
    void trim(size_t len) {
        if (len > size_) {
            isc_throw(OutOfRange, "trimming too large from output buffer");
        }
        size_ -= len;
    }
    /// \brief Clear buffer content.
    ///
    /// This method can be used to re-initialize and reuse the buffer without
    /// constructing a new one. Note it must keep current content.
    void clear() { size_ = 0; }

    /// \brief Wipe buffer content.
    ///
    /// This method is the destructive alternative to clear().
    void wipe() {
        if (buffer_ != NULL) {
            static_cast<void>(std::memset(buffer_, 0, allocated_));
        }
        size_ = 0;
    }

    /// \brief Write an unsigned 8-bit integer into the buffer.
    ///
    /// \param data The 8-bit integer to be written into the buffer.
    void writeUint8(uint8_t data) {
        ensureAllocated(size_ + 1);
        buffer_[size_ ++] = data;
    }

    /// \brief Write an unsigned 8-bit integer into the buffer.
    ///
    /// The position must be lower than the size of the buffer,
    /// otherwise an exception of class \c isc::dns::InvalidBufferPosition
    /// will be thrown.
    ///
    /// \param data The 8-bit integer to be written into the buffer.
    /// \param pos The position in the buffer to write the data.
    void writeUint8At(uint8_t data, size_t pos) {
        if (pos + sizeof(data) > size_) {
            isc_throw(InvalidBufferPosition, "write at invalid position");
        }
        buffer_[pos] = data;
    }

    /// \brief Write an unsigned 16-bit integer in host byte order into the
    /// buffer in network byte order.
    ///
    /// \param data The 16-bit integer to be written into the buffer.
    void writeUint16(uint16_t data) {
        ensureAllocated(size_ + sizeof(data));
        buffer_[size_ ++] = static_cast<uint8_t>((data & 0xff00U) >> 8);
        buffer_[size_ ++] = static_cast<uint8_t>(data & 0x00ffU);
    }

    /// \brief Write an unsigned 16-bit integer in host byte order at the
    /// specified position of the buffer in network byte order.
    ///
    /// The buffer must have a sufficient room to store the given data at the
    /// given position, that is, <code>pos + 2 < getLength()</code>;
    /// otherwise an exception of class \c isc::dns::InvalidBufferPosition will
    /// be thrown.
    /// Note also that this method never extends the buffer.
    ///
    /// \param data The 16-bit integer to be written into the buffer.
    /// \param pos The beginning position in the buffer to write the data.
    void writeUint16At(uint16_t data, size_t pos) {
        if (pos + sizeof(data) > size_) {
            isc_throw(InvalidBufferPosition, "write at invalid position");
        }

        buffer_[pos] = static_cast<uint8_t>((data & 0xff00U) >> 8);
        buffer_[pos + 1] = static_cast<uint8_t>(data & 0x00ffU);
    }

    /// \brief Write an unsigned 32-bit integer in host byte order
    /// into the buffer in network byte order.
    ///
    /// \param data The 32-bit integer to be written into the buffer.
    void writeUint32(uint32_t data) {
        ensureAllocated(size_ + sizeof(data));
        buffer_[size_ ++] = static_cast<uint8_t>((data & 0xff000000) >> 24);
        buffer_[size_ ++] = static_cast<uint8_t>((data & 0x00ff0000) >> 16);
        buffer_[size_ ++] = static_cast<uint8_t>((data & 0x0000ff00) >> 8);
        buffer_[size_ ++] = static_cast<uint8_t>(data & 0x000000ff);
    }

    /// \brief Write an unsigned 64-bit integer in host byte order
    /// into the buffer in network byte order.
    ///
    /// \param data The 64-bit integer to be written into the buffer.
    void writeUint64(uint64_t data) {
        ensureAllocated(size_ + sizeof(data));
        buffer_[size_ ++] = static_cast<uint8_t>((data & 0xff00000000000000) >> 56);
        buffer_[size_ ++] = static_cast<uint8_t>((data & 0x00ff000000000000) >> 48);
        buffer_[size_ ++] = static_cast<uint8_t>((data & 0x0000ff0000000000) >> 40);
        buffer_[size_ ++] = static_cast<uint8_t>((data & 0x000000ff00000000) >> 32);
        buffer_[size_ ++] = static_cast<uint8_t>((data & 0x00000000ff000000) >> 24);
        buffer_[size_ ++] = static_cast<uint8_t>((data & 0x0000000000ff0000) >> 16);
        buffer_[size_ ++] = static_cast<uint8_t>((data & 0x000000000000ff00) >> 8);
        buffer_[size_ ++] = static_cast<uint8_t>(data &  0x00000000000000ff);
    }

    /// \brief Copy an arbitrary length of data into the buffer.
    ///
    /// No conversion on the copied data is performed.
    ///
    /// \param data A pointer to the data to be copied into the buffer.
    /// \param len The length of the data in bytes.
    void writeData(const void *data, size_t len) {
        if (len == 0) {
            return;
        }

        ensureAllocated(size_ + len);
        static_cast<void>(std::memmove(buffer_ + size_, data, len));
        size_ += len;
    }
    //@}

private:
    /// The actual data
    uint8_t* buffer_;
    /// How many bytes are used
    size_t size_;
    /// How many bytes do we have preallocated (eg. the capacity)
    size_t allocated_;

    /// \brief Ensure buffer is appropriate size
    ///
    /// Checks that the buffer equal to or larger than the size given as
    /// argument and extends it to at least that size if not.
    ///
    /// \param needed_size The number of bytes required in the buffer
    void ensureAllocated(size_t needed_size) {
        if (allocated_ < needed_size) {
            // Guess some bigger size
            size_t new_size = (allocated_ == 0) ? 1024 : allocated_;
            while (new_size < needed_size) {
                new_size *= 2;
            }
            // Allocate bigger space.  Note that buffer_ may be NULL,
            // in which case realloc acts as malloc.
            uint8_t* new_buffer_(static_cast<uint8_t*>(realloc(buffer_,
                new_size)));
            if (new_buffer_ == NULL) {
                // If it fails, the original block is left intact by it
                throw std::bad_alloc();
            }
            buffer_ = new_buffer_;
            allocated_ = new_size;
        }
    }
};

/// \brief Pointer-like types pointing to \c InputBuffer or \c OutputBuffer
///
/// These types are expected to be used as an argument in asynchronous
/// callback functions.  The internal reference-counting will ensure that
/// that ongoing state information will not be lost if the object
/// that originated the asynchronous call falls out of scope.
typedef boost::shared_ptr<InputBuffer> InputBufferPtr;
typedef boost::shared_ptr<OutputBuffer> OutputBufferPtr;

} // namespace util
} // namespace isc
#endif  // BUFFER_H

// Local Variables:
// mode: c++
// End:
