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

#ifndef __MESSAGERENDERER_H
#define __MESSAGERENDERER_H 1

namespace isc {
namespace dns {
// forward declarations
class OutputBuffer;
class Name;

/// \brief The \c AbstractMessageRenderer class is an abstract base class
/// that provides common interfaces for rendering a DNS message into a buffer
/// in wire format.
///
/// A specific derived class of \c AbstractMessageRenderer (we call it
/// a renderer class hereafter) is simply responsible for name compression at
/// least in the current design.  A renderer class object (conceptually)
/// manages the positions of names rendered in some sort of buffer and uses
/// that information to render subsequent names with compression.
///
/// A renderer class is mainly intended to be used as a helper for a more
/// comprehensive \c Message class internally; normal applications won't have
/// to care about details of this class.
///
/// Once a renderer class object is constructed with a buffer, it is
/// generally expected that all rendering operations are performed via that
/// object.  If the application modifies the buffer in
/// parallel with the renderer, the result will be undefined.
///
/// Note to developers: we introduced a separate class for name compression
/// because previous benchmark with BIND9 showed compression affects overall
/// response performance very much.  By having a separate class dedicated for
/// this purpose, we'll be able to change the internal implementation of name
/// compression in the future without affecting other part of the API and
/// implementation.
///
/// In addition, by introducing a class hierarchy from
/// \c AbstractMessageRenderer, we allow an application to use a customized
/// renderer class for specific purposes.  For example, a high performance
/// DNS server may want to use an optimized renderer class assuming some
/// specific underlying data representation.
class AbstractMessageRenderer {
public:
    /// \brief Compression mode constants.
    ///
    /// The \c CompressMode enum type represents the name compression mode
    /// for renderer classes.
    /// \c CASE_INSENSITIVE means compress names in case-insensitive manner;
    /// \c CASE_SENSITIVE means compress names in case-sensitive manner.
    /// By default, a renderer compresses names in case-insensitive
    /// manner.
    /// Compression mode can be dynamically modified by the
    /// \c setCompressMode() method.
    /// The mode can be changed even in the middle of rendering, although this
    /// is not an intended usage.  In this case the names already compressed
    /// are intact; only names being compressed after the mode change are
    /// affected by the change.
    /// If a renderer class object is reinitialized by the \c clear()
    /// method, the compression mode will be reset to the default, which is
    /// \c CASE_INSENSITIVE
    ///
    /// One specific case where case-sensitive compression is required is
    /// AXFR as described in draft-ietf-dnsext-axfr-clarify.  A primary
    /// authoritative DNS server implementation using this API would specify
    /// \c CASE_SENSITIVE before rendering outgoing AXFR messages.
    ///
    enum CompressMode {
        CASE_INSENSITIVE,  //!< Compress names case-insensitive manner (default)
        CASE_SENSITIVE     //!< Compress names case-sensitive manner
    };
protected:
    ///
    /// \name Constructors and Destructor
    //@{
    /// \brief The default constructor.
    ///
    /// This is intentionally defined as \c protected as this base class should
    /// never be instantiated (except as part of a derived class).
    AbstractMessageRenderer() {}
public:
    /// \brief The destructor.
    virtual ~AbstractMessageRenderer() {}
    //@}

    ///
    /// \name Getter Methods
    ///
    //@{
    /// \brief Return a pointer to the head of the data stored in the internal
    /// buffer.
    ///
    /// This method works exactly same as the same method of the \c OutputBuffer
    /// class; all notes for \c OutputBuffer apply.
    virtual const void* getData() const = 0;

    /// \brief Return the length of data written in the internal buffer.
    virtual size_t getLength() const = 0;

    /// \brief Return whether truncation has occurred while rendering.
    ///
    /// Once the return value of this method is \c true, it doesn't make sense
    /// to try rendering more data, although this class itself doesn't reject
    /// the attempt.
    ///
    /// This method never throws an exception.
    ///
    /// \return true if truncation has occurred; otherwise \c false.
    virtual bool isTruncated() const = 0;

    /// \brief Return the maximum length of rendered data that can fit in the
    /// corresponding DNS message without truncation.
    ///
    /// This method never throws an exception.
    ///
    /// \return The maximum length in bytes.
    virtual size_t getLengthLimit() const = 0;

    /// \brief Return the compression mode of the renderer class object.
    ///
    /// This method never throws an exception.
    ///
    /// \return The current compression mode.
    virtual CompressMode getCompressMode() const = 0;
    //@}

    ///
    /// \name Setter Methods
    ///
    //@{
    /// \brief Mark the renderer to indicate truncation has occurred while
    /// rendering.
    ///
    /// This method never throws an exception.
    virtual void setTruncated() = 0;

    /// \brief Set the maximum length of rendered data that can fit in the
    /// corresponding DNS message without truncation.
    ///
    /// This method never throws an exception.
    ///
    /// \param len The maximum length in bytes.
    virtual void setLengthLimit(size_t len) = 0;

    /// \brief Set the compression mode of the renderer class object.
    ///
    /// This method never throws an exception.
    ///
    /// \param mode A \c CompressMode value representing the compression mode.
    virtual void setCompressMode(CompressMode mode) = 0;
    //@}

    ///
    /// \name Methods for writing data into the internal buffer.
    ///
    //@{
    /// \brief Insert a specified length of gap at the end of the buffer.
    ///
    /// The caller should not assume any particular value to be inserted.
    /// This method is provided as a shortcut to make a hole in the buffer
    /// that is to be filled in later, e.g, by \ref writeUint16At().
    ///
    /// \param len The length of the gap to be inserted in bytes.
    virtual void skip(size_t len) = 0;

    /// \brief Trim the specified length of data from the end of the internal
    /// buffer.
    ///
    /// This method is provided for such cases as DNS message truncation.
    ///
    /// The specified length must not exceed the current data size of the
    /// buffer; otherwise an exception of class \c isc::OutOfRange will
    /// be thrown.
    ///
    /// \param len The length of data that should be trimmed.
    virtual void trim(size_t len) = 0;

    /// \brief Clear the internal buffer and other internal resources.
    ///
    /// This method can be used to re-initialize and reuse the renderer
    /// without constructing a new one.
    virtual void clear() = 0;

    /// \brief Write an unsigned 8-bit integer into the internal buffer.
    ///
    /// \param data The 8-bit integer to be written into the internal buffer.
    virtual void writeUint8(uint8_t data) = 0;

    /// \brief Write an unsigned 16-bit integer in host byte order into the
    /// internal buffer in network byte order.
    ///
    /// \param data The 16-bit integer to be written into the buffer.
    virtual void writeUint16(uint16_t data) = 0;

    /// \brief Write an unsigned 16-bit integer in host byte order at the
    /// specified position of the internal buffer in network byte order.
    ///
    /// The buffer must have a sufficient room to store the given data at the
    /// given position, that is, <code>pos + 2 < getLength()</code>;
    /// otherwise an exception of class \c isc::dns::InvalidBufferPosition will
    /// be thrown.
    /// Note also that this method never extends the internal buffer.
    ///
    /// \param data The 16-bit integer to be written into the internal buffer.
    /// \param pos The beginning position in the buffer to write the data.
    virtual void writeUint16At(uint16_t data, size_t pos) = 0;

    /// \brief Write an unsigned 32-bit integer in host byte order into the
    /// internal buffer in network byte order.
    ///
    /// \param data The 32-bit integer to be written into the buffer.
    virtual void writeUint32(uint32_t data) = 0;

    /// \brief Copy an arbitrary length of data into the internal buffer
    /// of the renderer object.
    ///
    /// No conversion on the copied data is performed.
    ///
    /// \param data A pointer to the data to be copied into the internal buffer.
    /// \param len The length of the data in bytes.
    virtual void writeData(const void *data, size_t len) = 0;

    /// \brief Write a \c Name object into the internal buffer in wire format,
    /// with or without name compression.
    ///
    /// If the optional parameter \c compress is \c true, this method tries to
    /// compress the \c name if possible, searching the entire message that has
    /// been rendered.  Otherwise name compression is omitted.  Its default
    /// value is \c true.
    ///
    /// Note: even if \c compress is \c true, the position of the \c name (and
    /// possibly its ancestor names) in the message is recorded and may be used
    /// for compressing subsequent names.
    ///
    /// \param name A \c Name object to be written.
    /// \param compress A boolean indicating whether to enable name compression.
    virtual void writeName(const Name& name, bool compress = true) = 0;
    //@}
};

/// The \c MessageRenderer is a concrete derived class of
/// \c AbstractMessageRenderer as a general purpose implementation of the
/// renderer interfaces.
///
/// A \c MessageRenderer object is constructed with a \c OutputBuffer
/// object, which is the buffer into which the rendered %data will be written.
/// Normally the buffer is expected to be empty on construction, but it doesn't
/// have to be so; the renderer object will start rendering from the
/// end of the buffer at the time of construction.  However, if the
/// pre-existing portion of the buffer contains DNS names, these names won't
/// be considered for name compression.
class MessageRenderer : public AbstractMessageRenderer {
public:
    using AbstractMessageRenderer::CASE_INSENSITIVE;
    using AbstractMessageRenderer::CASE_SENSITIVE;

    /// \brief Constructor from an output buffer.
    ///
    /// \param buffer An \c OutputBuffer object to which wire format data is
    /// written.
    MessageRenderer(OutputBuffer& buffer);

    virtual ~MessageRenderer();
    virtual const void* getData() const;
    virtual size_t getLength() const;
    virtual bool isTruncated() const;
    virtual size_t getLengthLimit() const;
    virtual CompressMode getCompressMode() const;
    virtual void setTruncated();
    virtual void setLengthLimit(size_t len);
    virtual void setCompressMode(CompressMode mode);
    virtual void skip(size_t len);
    virtual void trim(size_t len);
    virtual void clear();
    virtual void writeUint8(uint8_t data);
    virtual void writeUint16(uint16_t data);
    virtual void writeUint16At(uint16_t data, size_t pos);
    virtual void writeUint32(uint32_t data);
    virtual void writeData(const void *data, size_t len);
    virtual void writeName(const Name& name, bool compress = true);
private:
    struct MessageRendererImpl;
    MessageRendererImpl* impl_;
};
}
}
#endif // __MESSAGERENDERER_H

// Local Variables: 
// mode: c++
// End: 
