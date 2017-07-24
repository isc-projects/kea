// Copyright (C) 2009-2017 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef MESSAGERENDERER_H
#define MESSAGERENDERER_H 1

#include <util/buffer.h>

#include <boost/noncopyable.hpp>

namespace isc {

namespace dns {
// forward declarations
class Name;
class LabelSequence;

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
/// By default any (derived) renderer class object is associated with
/// an internal buffer, and subsequent write operations will be performed
/// on that buffer.  The rendering result can be retrieved via the
/// \c getData() method.
///
/// If an application wants a separate buffer can be (normally temporarily)
/// set for rendering operations via the \c setBuffer() method.  In that case,
/// it is generally expected that all rendering operations are performed via
/// that object.  If the application modifies the buffer in
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
///
/// \note Some functions (like writeUint8) are not virtual. It is because
///     it is hard to imagine any version of message renderer that would
///     do anything else than just putting the data into a buffer, so we
///     provide a default implementation and having them virtual would only
///     hurt the performance with no real gain. If it would happen a different
///     implementation is really needed, we can make them virtual in future.
///     The only one that is virtual is writeName and it's because this
///     function is much more complicated, therefore there's a lot of space
///     for different implementations or different behavior.
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
    AbstractMessageRenderer();

public:
    /// \brief The destructor.
    virtual ~AbstractMessageRenderer() {}
    //@}
protected:
    /// \brief Return the output buffer we render into.
    const isc::util::OutputBuffer& getBuffer() const { return (*buffer_); }
    isc::util::OutputBuffer& getBuffer() { return (*buffer_); }
private:
    /// \brief Local (default) buffer to store data.
    isc::util::OutputBuffer local_buffer_;

    /// \brief Buffer to store data.
    ///
    /// Note that the class interface ensures this pointer is never NULL;
    /// it either refers to \c local_buffer_ or to an application-supplied
    /// buffer by \c setBuffer().
    ///
    /// It was decided that there's no need to have this in every subclass,
    /// at least not now, and this reduces code size and gives compiler a
    /// better chance to optimize.
    isc::util::OutputBuffer* buffer_;
public:
    ///
    /// \name Getter Methods
    ///
    //@{
    /// \brief Return a pointer to the head of the data stored in the internal
    /// buffer.
    ///
    /// This method works exactly same as the same method of the \c OutputBuffer
    /// class; all notes for \c OutputBuffer apply.
    const void* getData() const {
        return (buffer_->getData());
    }

    /// \brief Return the length of data written in the internal buffer.
    size_t getLength() const {
        return (buffer_->getLength());
    }

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
    /// \brief Set or reset a temporary output buffer.
    ///
    /// This method can be used for an application that manages an output
    /// buffer separately from the message renderer and wants to keep reusing
    /// the renderer.  When the renderer is associated with the default buffer
    /// and the given pointer is non NULL, the given buffer will be
    /// (temporarily) used for subsequent message rendering; if the renderer
    /// is associated with a temporary buffer and the given pointer is NULL,
    /// the renderer will be reset with the default buffer.  In the latter
    /// case any additional resources (possibly specific to a derived renderer
    /// class) will be cleared, but the temporary buffer is kept as the latest
    /// state (which would normally store the rendering result).
    ///
    /// This method imposes some restrictions to prevent accidental misuse
    /// that could cause disruption such as dereferencing an invalid object.
    /// First, a temporary buffer must not be set when the associated buffer
    /// is in use, that is, any data are stored in the buffer.  Also, the
    /// default buffer cannot be "reset"; when NULL is specified a temporary
    /// buffer must have been set beforehand.  If these conditions aren't met
    /// an isc::InvalidParameter exception will be thrown.  This method is
    /// exception free otherwise.
    ///
    /// \throw isc::InvalidParameter A restrictions of the method usage isn't
    /// met.
    ///
    /// \param buffer A pointer to a temporary output buffer or NULL for reset
    /// it.
    void setBuffer(isc::util::OutputBuffer* buffer);

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
    void skip(size_t len) {
        buffer_->skip(len);
    }

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
    void trim(size_t len) {
        buffer_->trim(len);
    }

    /// \brief Clear the internal buffer and other internal resources.
    ///
    /// This method can be used to re-initialize and reuse the renderer
    /// without constructing a new one.
    virtual void clear();

    /// \brief Write an unsigned 8-bit integer into the internal buffer.
    ///
    /// \param data The 8-bit integer to be written into the internal buffer.
    void writeUint8(const uint8_t data) {
        buffer_->writeUint8(data);
    }

    /// \brief Write an unsigned 16-bit integer in host byte order into the
    /// internal buffer in network byte order.
    ///
    /// \param data The 16-bit integer to be written into the buffer.
    void writeUint16(uint16_t data) {
        buffer_->writeUint16(data);
    }

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
    void writeUint16At(uint16_t data, size_t pos) {
        buffer_->writeUint16At(data, pos);
    }

    /// \brief Write an unsigned 32-bit integer in host byte order into the
    /// internal buffer in network byte order.
    ///
    /// \param data The 32-bit integer to be written into the buffer.
    void writeUint32(uint32_t data) {
        buffer_->writeUint32(data);
    }

    /// \brief Copy an arbitrary length of data into the internal buffer
    /// of the renderer object.
    ///
    /// No conversion on the copied data is performed.
    ///
    /// \param data A pointer to the data to be copied into the internal buffer.
    /// \param len The length of the data in bytes.
    void writeData(const void *data, size_t len) {
        buffer_->writeData(data, len);
    }

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
    /// \param compress A boolean indicating whether to enable name
    /// compression.
    virtual void writeName(const Name& name, bool compress = true) = 0;

    /// \brief Write a \c LabelSequence object into the internal buffer
    /// in wire format, with or without name compression.
    ///
    /// This is the same as the other version, which takes \c Name instead
    /// of \c LabelSequence, except for the parameter type.  The passed
    /// \c LabelSequence must be absolute.
    ///
    /// \param ls A \c LabelSequence object to be written.
    /// \param compress A boolean indicating whether to enable name
    /// compression.
    virtual void writeName(const LabelSequence& ls, bool compress = true) = 0;
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
class MessageRenderer : public AbstractMessageRenderer,
    public boost::noncopyable { // Can crash if copied
public:
    using AbstractMessageRenderer::CASE_INSENSITIVE;
    using AbstractMessageRenderer::CASE_SENSITIVE;

    MessageRenderer();

    virtual ~MessageRenderer();
    virtual bool isTruncated() const;
    virtual size_t getLengthLimit() const;
    virtual CompressMode getCompressMode() const;
    virtual void setTruncated();
    virtual void setLengthLimit(size_t len);

    /// This implementation does not allow this call in the middle of
    /// rendering (i.e. after at least one name is rendered) due to
    /// restriction specific to the internal implementation.  Such attempts
    /// will result in an \c isc::InvalidParameter exception.
    ///
    /// This shouldn't be too restrictive in practice; there's no known
    /// practical case for such a mixed compression policy in a single
    /// message.
    virtual void setCompressMode(CompressMode mode);

    virtual void clear();
    virtual void writeName(const Name& name, bool compress = true);
    virtual void writeName(const LabelSequence& ls, bool compress = true);

private:
    struct MessageRendererImpl;
    MessageRendererImpl* impl_;
};
}
}
#endif // MESSAGERENDERER_H

// Local Variables:
// mode: c++
// End:
